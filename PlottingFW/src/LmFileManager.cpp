// c++ includes
#include <iostream>
using namespace std;
// ROOT includes
#include "TString.h"
#include "TFile.h"
// project includes
#include "LmFileManager.h"
#include "LmHelper.h"

int debugFileManager=0;
LmFileManager* LmFileManager::fgInstance=0x0;

//_______________________________________________________________________________________________
LmFileManager* LmFileManager::Instance()
{
  /// return pointer to singleton implementation
  
  if (fgInstance) return fgInstance;
  
  fgInstance = new LmFileManager();
  
  return fgInstance;
}


//_______________________________________________________________________________________________
LmFileManager::LmFileManager()
{
  /// Default constructor for LmFileManager
  LmHelper::Debug("LmFileManager constructor", 5-debugFileManager);
  foaFiles = new TObjArray();
  foaFiles->SetOwner();
}


//_______________________________________________________________________________________________
LmFileManager::~LmFileManager()
{
  LmHelper::Debug("LmFileManager destructor", 5-debugFileManager);
  Clear();
}


//_______________________________________________________________________________________________
void LmFileManager::Clear()
{
  LmHelper::Debug("LmFileManager::Clear()", 5-debugFileManager);
  foaFiles->Delete();   // "Remove all objects from the array AND delete all heap based objects." (root-doc)
  fvConfigs.clear();
  fvPathNames.clear();
  fvDependantsDone.clear();
  fvListPtr.clear();
  fvCutsetPtr.clear();  // should be ok to clear, since the cutsets were closed by closing the files.
}


//_______________________________________________________________________________________________
void LmFileManager::AddConfig(TString sConfig)
{
  /// Add a new config to the FileManager.
  /// If multiple objects (like LmManager and LmQA) use the same config, the user must make sure that this config
  /// has been added the corresponding amount of times.
  
  TObjArray* oaConfig = sConfig.Tokenize(":");
  if (oaConfig->GetEntries()<4) LmHelper::Error(Form("LmFileManager: invalid config: %s", sConfig.Data()));
  fvConfigs.push_back(sConfig); // store original string.
  
  TString sfile   = oaConfig->At(1)->GetName();
  TString slist   = oaConfig->At(2)->GetName();
  TString scutset = oaConfig->At(3)->GetName();
  // If the string which specifies the cutset folder contains a '/', the second part will be used to replace the
  // unlike sign pair folder. This is needed to plot pair histograms from added AliDielectronSignalMC objects,
  // but it has to be removed from the name of the cutset folder.
  if (scutset.Contains("/")) scutset.Remove(scutset.First('/'),1000);
  
  // fvPathNames must have format 'File:List:Cutset'!
  // Otherwise the functions FilePath(), ListPath(), ListName(), CutsetPath(), CutsetName() dont work correctly!
  fvPathNames.push_back(Form("%s:%s:%s",sfile.Data(),slist.Data(),scutset.Data()));
  fvListPtr.push_back(0x0);
  fvCutsetPtr.push_back(0x0);
  fvDependantsDone.push_back(kFALSE);
}


//_______________________________________________________________________________________________
TCollection* LmFileManager::GetCutset(TString sConfig)
{
  /// Return the CutFolder corresponding to the given config.
  /// If it doesn't exist, the function will add the config, open the file, and retrieve the folder.
  
  Int_t index = FindIndex(sConfig);
  if (index<0) {
    LmHelper::Error(Form("LmFileManager: config not found: %s", sConfig.Data()));
    LmHelper::Error(Form("               -> Please first call LmFileManager::AddConfig(TString sConfig);"));
    LmHelper::Error(Form("               -> Do it for all configs at the start of your script for efficient file handling!"));
    LmHelper::Warning(Form("             -> Adding config for your convenience. Reading of multiple inputs from one file will not be efficient!"));
    AddConfig(sConfig);
    index = FindIndex(sConfig);
  }
  return GetCutset(index);
}

//_______________________________________________________________________________________________
TCollection* LmFileManager::GetCutset(Int_t iConfig)
{
  if (iConfig<0) return 0x0;
  if (fvCutsetPtr.at(iConfig)==0x0) OpenCutset(iConfig);
  return fvCutsetPtr.at(iConfig);
}


//_______________________________________________________________________________________________
void LmFileManager::OpenCutset(Int_t iConfig)
{
  LmHelper::Debug(Form("LmFileManager::OpenCutset( %d of %d )", iConfig, NConfigs()), 5-debugFileManager);
  
  TString sfile   = FilePath(iConfig);
  TString slist   = ListName(iConfig);
  TString scutset = CutsetName(iConfig);
  
  // check if identical user list and/or cutset path exists and is already open.
  // if yes, set the respective pointer(s) at current position to the existing one(s).
  Bool_t listOpen=kFALSE;
  Bool_t pathOpen=kFALSE;
  for (unsigned int i=0; i<NConfigs(); i++) {
    if (strcmp(CutsetPath(i).Data(), CutsetPath(iConfig).Data()) == 0) {
      if (fvCutsetPtr.at(i)!=0x0) {
        LmHelper::Info(Form("User list and cutset # %d already open at position # %d. Cutset named: '%s'.", iConfig, i, fvCutsetPtr.at(i)->GetName()));
        listOpen = kTRUE;
        pathOpen = kTRUE;
        fvListPtr.at(iConfig)   = fvListPtr.at(i);
        fvCutsetPtr.at(iConfig) = fvCutsetPtr.at(i);
        break;
      }
    }
    else if (strcmp(ListPath(i).Data(), ListPath(iConfig).Data()) == 0) {
      if (fvListPtr.at(i)!=0x0) {
        LmHelper::Info(Form("User list # %d already open at position # %d.", iConfig, i));
        listOpen = kTRUE;
        fvListPtr.at(iConfig)   = fvListPtr.at(i);
        break;
      }
    }
  }
  if (pathOpen) return; // nothing more to do.
  
  // check if file is already open.
  // if not, open it and add it to the array.
  TFile* ffile = (TFile*) foaFiles->FindObject(sfile.Data());
  if (!ffile) {
    ffile = LmHelper::SafelyOpenRootfile( sfile.Data() );
    foaFiles->Add( ffile );
  }
  
  // open cutset folder
  TCollection* userlist = 0x0;
  TCollection* cutfolder = 0x0;
  if (strcmp(slist.Data(), "NoList") == 0){ // compressed LMEEoutput.root without user list.
    LmHelper::Debug(Form("  getting cutset, no list: %s", scutset.Data()), 2);
    cutfolder = (TCollection*) ffile->Get(scutset.Data());
  }
  else { // typical LMEEoutput.root with user list.
    LmHelper::Debug(Form("  getting cutset, with list: %s   ( -> list %s open )", scutset.Data(), listOpen?"ALREADY":"NOT YET"), 2);
    if (listOpen) userlist = fvListPtr.at(iConfig);
    else          ffile->GetObject(slist.Data(), userlist);
    //userlist->Print();
    if (!userlist) LmHelper::Error(Form("LmFileManager: cannot find list '%s' in rootfile '%s'!", slist.Data(), sfile.Data()));
    cutfolder = (TCollection*) userlist->FindObject(scutset.Data());
  }
  if (!cutfolder) LmHelper::Error(Form("LmFileManager: cannot find cut folder '%s' in rootfile '%s'!", scutset.Data(), sfile.Data()));
  
  // add list pointer and cutset pointer to vectors
  fvListPtr.at(iConfig)   = userlist;
  fvCutsetPtr.at(iConfig) = cutfolder;
}


//_______________________________________________________________________________________________
void LmFileManager::FreeCutset(TString sConfig)
{
  /// This function will mark the first occurence of the config 'sConfig' as "Done" (due to 'FindIndex(sConfig)').
  /// If multiple objects (like LmManager and LmQA) use the same config, the user must make sure that this config
  /// has been added the same amount of times.
  
  return FreeCutset(FindIndex(sConfig));
}

//_______________________________________________________________________________________________
void LmFileManager::FreeCutset(Int_t iConfig)
{
  LmHelper::Debug("LmFileManager::FreeCutset()", 5-debugFileManager);
  
  fvDependantsDone.at(iConfig) = kTRUE;
  
  // check if identical path (file+list+cutset) exists and still needs to be processed.
  Bool_t cutsetDone=kTRUE;
  for (unsigned int i=0; i<NConfigs(); i++) {
    if (fvDependantsDone.at(i) == kTRUE) continue;
    //if (i==iConfig) continue; // this check isnt needed anymore
    if (strcmp(CutsetPath(i).Data(), CutsetPath(iConfig).Data()) == 0) {
      cutsetDone=kFALSE;
      break;
    }
  }
  if (cutsetDone) {
    LmHelper::Debug(Form("  deleting cutset from memory: %s", CutsetPath(iConfig).Data()), 3);
    if (fvCutsetPtr.at(iConfig)!=0x0) {
      //delete fvCutsetPtr.at(iConfig); // this will mess up the opened rootfile!
      //fvCutsetPtr.at(iConfig)->Clear(); // this is ok, but not checked if it frees memory.
      fvCutsetPtr.at(iConfig)->Delete(); // this is ok, but not checked if it frees memory.
      fvCutsetPtr.at(iConfig) = 0x0;
      LmHelper::Info(Form("cutset (should now be) deleted: %s", CutsetPath(iConfig).Data()));
    }
  }
  
  // check if identical file exists and still needs to be processed by different cutset.
  Bool_t fileDone=kTRUE;
  for (unsigned int i=0; i<NConfigs(); i++) {
    if (fvDependantsDone.at(i) == kTRUE) continue;
    if (strcmp(FilePath(i).Data(), FilePath(iConfig).Data()) == 0) {
      fileDone=kFALSE;
      break;
    }
  }
  if (fileDone) {
    LmHelper::Debug(Form("  closing file: %s", FilePath(iConfig).Data()), 3);
    TFile* file = (TFile*) foaFiles->FindObject(FilePath(iConfig).Data());
    if (file) {
      // closing the file will cause a segmentation violation if pointer objects were created while gDirectory
      // pointed to the file. (e.g. class pointers in main file)
      file->Close();
      foaFiles->Remove(file);
      LmHelper::Info(Form("file closed and removed from array: %s", FilePath(iConfig).Data()));
    }
  }
  
}


//_______________________________________________________________________________________________
Int_t LmFileManager::FindIndex(TString sConfig) {
  for (unsigned int i=0; i<NConfigs(); i++) {
    if (strcmp(fvConfigs.at(i).Data(), sConfig.Data()) == 0) return i;
  }
  return -1;
}


