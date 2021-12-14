// c++ includes
#include <iostream>
using namespace std;
// ROOT includes
#include "TString.h"
#include "TObjArray.h"
#include "TObject.h"
#include "TFile.h"
#include "TCollection.h"
#include "TList.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TString.h"
#include "THnSparse.h"
#include "THn.h"
// project includes
#include "LmManager.h"
#include "LmBaseSignal.h"
#include "LmHelper.h"
#include "LmFileManager.h"

int debugManager=0;

//_______________________________________________________________________________________________
LmManager::LmManager(const LmManager& man, Bool_t copyHistograms) :
LmBaseManager(man), // with argument 'man': use copy constructor of base class. without argument 'man': use default constructor instead. (they may only be implicitly defined)
LmRebinner(man),
fEnable3DExclCut(man.fEnable3DExclCut),
fEnableEffiCorr(man.fEnableEffiCorr),
fEnableTR(man.fEnableTR),
fUseExternalInputfile(kTRUE),   // avoid that one mgr might close the file of another mgr.
fIsSubtractedMC(man.fIsSubtractedMC),
fInputfile(man.fInputfile),
fCutfolder(0x0), // don't copy it.
fNperiods(man.fNperiods),
fNperiodsMAX(man.fNperiodsMAX), //const
fNpaircombs(man.fNpaircombs),   //const
fNmixcombs(0),                  //not const. Filled if copyHistograms==kTRUE.
fPairCombNames(man.fPairCombNames),
fMixCombNames(man.fMixCombNames),
fhMixedMeePteeULS(0x0),
fhRotatedInvMassPt(0x0),
fNeventsPhysSel(man.fNeventsPhysSel),
fsConfiglong(man.fsConfiglong),
fsEffifile(""),
fsEffiGen(""),
fsEffiRec(""),
fhEffiGen(0x0),
fhEffiRec(0x0),
fhEffi(0x0),
fDoEffiCorr(kFALSE),	
fhCorrectedSig(0x0),
fCutValZbelow(man.fCutValZbelow),
fCutValZabove(man.fCutValZabove),
fTemplNormMin(man.fTemplNormMin),
fTemplNormMax(man.fTemplNormMax),
feta_range_min(man.feta_range_min),
feta_range_max(man.feta_range_max),
fpt_range_min(man.fpt_range_min),
fpt_range_max(man.fpt_range_max),
fThetaEE_min(man.fThetaEE_min),
fcentrality_min(man.fcentrality_min),
fcentrality_max(man.fcentrality_max),
fcoll_system(man.fcoll_system),
fcoll_energy(man.fcoll_energy),
fsProjOption(man.fsProjOption)
{
  /// Copy constructor for LmManager
  /// does not copy all information, since it is not expected to read in the same rootfiles again.
  /// used by LmSignal for combined & average signal and for studies of third input dimension (e.g. phiV study).

  LmHelper::Debug("LmManager copy constructor", 5-debugManager);

  if (copyHistograms) {
    CopyHistogramsFrom(man);
  }
  for (UInt_t i=0; i<man.f3DExclusionZbelow.size(); ++i) {
    f3DExclusionZbelow.push_back(man.f3DExclusionZbelow.at(i));
    f3DExclusionZabove.push_back(man.f3DExclusionZabove.at(i));
    if (man.f3DExclusionEdgesX.size()>0)
      f3DExclusionEdgesX.push_back(man.f3DExclusionEdgesX.at(i));
  }
  for (UInt_t i=0; i<man.fTemplateNormRegionMin.size(); ++i) {
    fTemplateNormRegionMin.push_back(man.fTemplateNormRegionMin.at(i));
    fTemplateNormRegionMax.push_back(man.fTemplateNormRegionMax.at(i));
  }
  for (UInt_t i=0; i<man.fProjRangeMinima.size(); ++i) {
    fProjRangeMinima.push_back(man.fProjRangeMinima.at(i));
    fProjRangeMaxima.push_back(man.fProjRangeMaxima.at(i));
  }
}


//_______________________________________________________________________________________________
LmManager::LmManager(const char* cconfig) :
LmBaseManager(), // not needed because the compiler seems to do it for you. but once we have a LmBaseManager copy constructor, we also need to implement the default constructor!
LmRebinner(),
fEnable3DExclCut(kNoCut),
fEnableEffiCorr(kFALSE),
fEnableTR(kFALSE),
fUseExternalInputfile(kFALSE),
fIsSubtractedMC(kFALSE),
fInputfile(0x0),
fCutfolder(0x0),
fNperiods(1),
fNperiodsMAX(1), //const
fNpaircombs(3),  //const
fNmixcombs(4),   //not const
fPairCombNames("Pair_ev1+_ev1-;Pair_ev1+_ev1+;Pair_ev1-_ev1-"),
fMixCombNames("Pair_ev1-_ev2+;Pair_ev1+_ev2+;Pair_ev1-_ev2-;Pair_ev1+_ev2-"),
fhMixedMeePteeULS(0x0),
fhRotatedInvMassPt(0x0),
fNeventsPhysSel(0.),
fsConfiglong(""),
fsEffifile(""),
fsEffiGen(""),
fsEffiRec(""),
fhEffiGen(0x0),
fhEffiRec(0x0),
fhEffi(0x0),
fDoEffiCorr(kFALSE),
fhCorrectedSig(0x0),
fCutValZbelow(-1.0e20),
fCutValZabove(+1.0e20),
fTemplNormMin(-1.0e20),
fTemplNormMax(+1.0e20),
feta_range_min(0),
feta_range_max(0),
fpt_range_min(0),
fpt_range_max(0),
fThetaEE_min(-1),
fcentrality_min(-1),
fcentrality_max(-1),
fcoll_system(""),
fcoll_energy(""),
fsProjOption("yx")
{
  /// Default constructor for LmManager
  /// @param cconfig Config string which contains collision system, file & cutset names etc. (see config.h)

  LmHelper::Debug("LmManager constructor", 5-debugManager);
  // initialize inherited variables: (not needed anymore since we implemented the LmBaseManager constructor.)

  //InitProjectionRanges(); // Makes no sense before knowing the dimensions. Therefore called via SetInputhistAndDim().

  fsConfiglong = cconfig;
  if (fsConfiglong.IsNull()) return;

  TObjArray* oaConfig = fsConfiglong.Tokenize(":");
  fcoll_system = oaConfig->At(0)->GetName();
  TObjArray* oaColl_system = fcoll_system.Tokenize(",");
  if (oaColl_system->GetEntriesFast()>1) {
    fcoll_system = oaColl_system->At(0)->GetName();
    fcoll_energy = oaColl_system->At(1)->GetName();
    fcoll_energy.Remove(TString::kLeading, ' ');
  }
  // set manager name if given in cconfig.
  if (oaConfig->GetEntriesFast()>=5) SetName(oaConfig->At(4)->GetName()); // function in LmBaseManager.
  // set efficiency names if given in cconfig.
  if (oaConfig->GetEntriesFast()>=8) {
    SetEffifileAndHists(const_cast<char*>(oaConfig->At(5)->GetName()), const_cast<char*>(oaConfig->At(6)->GetName()), const_cast<char*>(oaConfig->At(7)->GetName()));
  }
}


//_______________________________________________________________________________________________
LmManager::~LmManager()
{
  LmHelper::Debug("LmManager destructor", 5);
  /// Delete all heap based objects owned by this class.
  fhMeePtee.clear();
  fhMixedMeePtee.clear();
  fhExclusionZTemplates.clear();
  fhVisualSig.clear();
  CloseFileAndCleanUp(); // usually called during Process(), but not done in certain types.
  if (fhMixedMeePteeULS)        delete fhMixedMeePteeULS;
  if (fhRotatedInvMassPt)       delete fhRotatedInvMassPt;
  if (fhEffiGen)                delete fhEffiGen;
  if (fhEffiRec)                delete fhEffiRec;
  if (fhEffi)                   delete fhEffi;
  if (fhCorrectedSig)           delete fhCorrectedSig;
  /// @TODO: Check if something is missing. Clear Double_t vectors?
}


//_______________________________________________________________________________________________
void LmManager::SetEffifileAndHists(const char* filename, const char* name_gen, const char* name_rec)
{
  fsEffifile = filename;
  fsEffiGen  = name_gen;
  fsEffiRec  = name_rec;
  SetEnableEffiCorr();
}

//_______________________________________________________________________________________________
void LmManager::Set3DExclusionZbelow(Int_t n_val, const Double_t* val) {
  /// Will cut away values which are smaller ("below") the values in the given array.
  /// Further description in ApplyExclusionCutIn3D().
  f3DExclusionZbelow.clear();
  for (Int_t i=0; i<n_val; ++i) f3DExclusionZbelow.push_back(val[i]);
  fEnable3DExclCut = kDoCut;
}
//_______________________________________________________________________________________________
void LmManager::Set3DExclusionZabove(Int_t n_val, const Double_t* val) {
  /// Will cut away values which are larger ("above") the values in the given array.
  /// Further description in ApplyExclusionCutIn3D().
  f3DExclusionZabove.clear();
  for (Int_t i=0; i<n_val; ++i) f3DExclusionZabove.push_back(val[i]);
  fEnable3DExclCut = kDoCut;
}
//_______________________________________________________________________________________________
void LmManager::Set3DExclusionEdgesX(Int_t n_val, const Double_t* val) {
  /// The x value at array position i is the limit up to which the lower & upper cut value at position i is applied.
  /// All arrays must have the same size.
  /// Further description in ApplyExclusionCutIn3D().
  f3DExclusionEdgesX.clear();
  for (Int_t i=0; i<n_val; ++i) f3DExclusionEdgesX.push_back(val[i]);
}

//_______________________________________________________________________________________________
void LmManager::SetTemplateNormRegionMin(Int_t n_val, const Double_t* val) {
  /// Set lower edge of the range in which the templates shall be normalized to the data. Normalization is done for
  /// each x and y bin individually, because the spectral shapes may be different. Therefore only the z values are needed.
  /// Further description in CorrectForExclusionCutIn3D().
  fTemplateNormRegionMin.clear();
  for (Int_t i=0; i<n_val; ++i) fTemplateNormRegionMin.push_back(val[i]);
}
//_______________________________________________________________________________________________
void LmManager::SetTemplateNormRegionMax(Int_t n_val, const Double_t* val) {
  /// Set upper edge of the range in which the templates shall be normalized to the data. Normalization is done for
  /// each x and y bin individually, because the spectral shapes may be different. Therefore only the z values are needed.
  /// Further description in CorrectForExclusionCutIn3D().
  fTemplateNormRegionMax.clear();
  for (Int_t i=0; i<n_val; ++i) fTemplateNormRegionMax.push_back(val[i]);
}
//_______________________________________________________________________________________________
void LmManager::SetTemplateNormRegion(Double_t, Double_t) {
  LmHelper::Error(Form("LmManager::SetTemplateNormRegion(Double_t, Double_t) outdated. -> use SetTemplateNormRegionMin/Max(Int_t n_val, const Double_t* val);"));
  LmHelper::Error(Form("     Hint: for the largest possible region, use the same double arrays as for the functions LmManager::Set3DExclusionZbelow/above();"));
}


//_______________________________________________________________________________________________
void LmManager::SetExclusionZTemplates(TH3D* uls, TH3D* ls, UInt_t ttype, TH3D* more1, TH3D* more2) {
  /// Template(s) must have identical dimensions as the input histograms.
  /// Binning of templates may be finer than of data (with compatible edges), but not coarser (function uses integral).
  /// Further description in CorrectForExclusionCutIn3D().
  /// Templates may have to be scaled before usage! (esp. for addition/subtraction, see comments in SubtractConversionTemplate().)
  /// Hint: Templates can directly be taken from a Dielectron Framework output file, ideally having used an
  /// AliDielectronSignalMC. See ReadAllHistogramsFromFiles() how to read them in, and use LmHandler::Write3DHist()
  /// to store them in a handy file for re-usage.
  /// [version with 2D histograms was commit #441 (b0498d3e346336de5308dc70d4ec407ecbb484c2)]
  fhExclusionZTemplates.clear();
  if (!uls && !more1 && !more2) return;
  if (uls)
    fhExclusionZTemplates.push_back((TH3D*) uls->Clone("hTemplateULS"));
  if (ls) {
    fhExclusionZTemplates.push_back((TH3D*) ls->Clone("hTemplateLSpp"));
    fhExclusionZTemplates.push_back((TH3D*) ls->Clone("hTemplateLSmm")); // twice for convenience (loop over fNpaircombs)...
  }
  if (more1) fhExclusionZTemplates.push_back((TH3D*) more1->Clone(more1->GetName()));
  if (more2) fhExclusionZTemplates.push_back((TH3D*) more2->Clone(more2->GetName()));
  // set correction type
  if (ttype==kAuto) {
    if (ls) fEnable3DExclCut = kTemplUnsub; // assume ULS-LS if two templates are given.
    else    fEnable3DExclCut = kTemplSub;   // assume subtracted signal template if only one is given.
  }
  else {    fEnable3DExclCut = ttype; }
}

//_______________________________________________________________________________________________
Int_t LmManager::Process(Int_t type)
{
  LmHelper::Debug("LmManager Process()", 5-debugManager);

  if (type==kCleanUp) {
    CloseFileAndCleanUp();
    return 0;
  }

  if (type!=kDontReadInput) {
    ReadAllHistogramsFromFiles();
  }
  if (type==kReadInputOnly) return 0;

  if (fNdimInput>=3) {
    Set3DProjectionRanges();          // Mainly used to project only a subset of the 3D histograms, if specified.
    if (fEnable3DExclCut>=kDoCut && fEnable3DExclCut<=kTemplSub){
      ApplyExclusionCutIn3D();        // Do exclusion cut in 3rd dimension (e.g. PhiV), if specified.

    }
    //else if (fEnable3DExclCut==kTemplConv)
    SubtractConversionTemplate();     // Subtract expected undesired yield, if specified. (e.g. from same or different conversion...)
    if (fEnable3DExclCut==kTemplUnsub)
      CorrectForExclusionCutIn3D();   // 3D correction, if templates are available. Otherwise switches to 2D correction.
    ProjectInto2D();                  // Projection of input according to option 'fsProjOption' and given 3D ranges.
    CorrectForExclusionCutIn2D();     // Different correction methods chosen inside, if specified.
  }

  if (   type!=kDontReadInput         // avoid case when multiple managers process the same rootfile.
      && type!=kDontCleanUp ) {
    CloseFileAndCleanUp();
  }


  //if (fDoEffiCorr){
  //  std::cout << "Trying to apply Eff first" << std::endl; 
  //  if (fEnableEffiCorr){    CalcEffi(); // must be done after rebinning, because it is wrong to rebin an efficiency histogram itself!
  //    std::cout << "Efficiency calculated" << std::endl; 
  //  }
  //  ApplyEfficiency2D_all(GetEffi());
  //  std::cout << "Eff applied" << std::endl; 
  //  if (fEnableRebinning){   Rebin2DHistogram_all(); // warning: too large bins will cause an incorrect (averaged) efficiency correction!
  //                                                  // warning: too small bins will cause bias in the background estimation
  //    std::cout << "Everything rebinned" << std::endl; 
  //  }
  //}
  //else {
    std::cout << "Everything normal" << std::endl; 
    if (fEnableRebinning){   Rebin2DHistogram_all(); // warning: too large bins will cause an incorrect (averaged) efficiency correction!
      std::cout << "Rebinning" << std::endl;
    }
                                                    // warning: too small bins will cause bias in the background estimation
    if (fEnableEffiCorr){    CalcEffi(); // must be done after rebinning, because it is wrong to rebin an efficiency histogram itself!
      std::cout << "EffCalc" << std::endl; 
    }
  //}
  return 0;
}






//_______________________________________________________________________________________________
void LmManager::CloseFileAndCleanUp()
{
  LmHelper::Debug(" CloseFileAndCleanUp()", 5-debugManager);

  if (LmFileManager::Instance()->IsUsed()) {
    LmFileManager::Instance()->FreeCutset(fsConfiglong);
  }
  else { // default behaviour
    if(fCutfolder){
      delete fCutfolder;
      fCutfolder = 0x0;
    }
    if(fInputfile && !fUseExternalInputfile){
      fInputfile->Close();
      delete fInputfile;
    }
  }

  fhXdimYdimZdim.clear();
//  fhXdimYdimZdim.shrink_to_fit();
  fhMixedXdimYdimZdim.clear();
//  fhMixedXdimYdimZdim.shrink_to_fit();
}


//_______________________________________________________________________________________________
Int_t LmManager::ReadAllHistogramsFromFiles()
{
  /// Main function to read in histograms, obtain kinematics and other information, all based on the config string.
  /// Special usage for MC:
  /// If the string which specifies the cutset folder contains a '/', the second part will be used to replace the
  /// unlike sign pair folder. This is needed to plot pair histograms from added AliDielectronSignalMC objects.
  /// By default, the LmSignal constructed from such a manager will assume that no further subtraction is required.
  /// This can be changed by adding '/ULS' after the MC pair folder.
  /// One can also specify the corresponding like sign folders, the complete format of 'scutset' then has to be:
  /// '<cutset name>/Pair_<MCsignal for ULS>/ULS/Pair_<MCsignal for LS++>/Pair_<MCsignal for LS-->'
  LmHelper::Debug(" ReadAllHistogramsFromFiles()", 5-debugManager);

  LmHelper::Debug(Form(" read data file, using config:\n%s", fsConfiglong.Data()), 1);
  TObjArray* oaConfig = fsConfiglong.Tokenize(":");

  fcoll_system = oaConfig->At(0)->GetName();
  TObjArray* oaColl_system = fcoll_system.Tokenize(",");
  if (oaColl_system->GetEntriesFast()>1) {
    fcoll_system = oaColl_system->At(0)->GetName();
    fcoll_energy = oaColl_system->At(1)->GetName();
    fcoll_energy.Remove(TString::kLeading, ' ');
  }
  LmHelper::Debug(Form(" coll_system = %s, coll_energy = %s", fcoll_system.Data(), fcoll_energy.Data()), 3);

  TString scutset = oaConfig->At(3)->GetName();
  // check if we have the special case of an MC signal input:
  TObjArray* oaCutset = scutset.Tokenize("/");
  if (oaCutset->GetEntriesFast()>1) {
    scutset = oaCutset->At(0)->GetName();
    fPairCombNames.Remove(0,fPairCombNames.First(';')); // remove unlike sign pair folder.
    fPairCombNames.Prepend(oaCutset->At(1)->GetName()); // replace it with AliDielectronSignalMC folder.
    fIsSubtractedMC = kTRUE;
    if (oaCutset->GetEntriesFast()>2 && TString(oaCutset->At(2)->GetName()).EqualTo("ULS")) {
      fIsSubtractedMC = kFALSE;
      if (oaCutset->GetEntriesFast()==5) { // assume that entry 4+5 are the LS++ and LS-- of the given MC signal.
        fPairCombNames = Form("%s;%s;%s",oaCutset->At(1)->GetName(),oaCutset->At(3)->GetName(),oaCutset->At(4)->GetName());
      }
    }
    LmHelper::Info(Form("LmManager: using pairs from AliDielectronSignalMC '%s' for -> %s.", oaCutset->At(1)->GetName(), fIsSubtractedMC?"subtracted signal":"unlike sign"));
  }


  if (LmFileManager::Instance()->IsUsed()) {
    fCutfolder = LmFileManager::Instance()->GetCutset(fsConfiglong);
  }
  else { // default behaviour
    // updated to handle also rootfiles which were opened by previous manager
    if (fInputfile==0x0) {
      //if (!(fInputfile->IsOpen())) {
      LmHelper::Debug(Form(" opening rootfile: %s", oaConfig->At(1)->GetName()), 2);
      fInputfile = LmHelper::SafelyOpenRootfile( oaConfig->At(1)->GetName() );
    } else {
      LmHelper::Debug(Form(" using already opened rootfile: %s", oaConfig->At(1)->GetName()), 2);
    }

    TList* lCutset = 0x0;
    if (strcmp(oaConfig->At(2)->GetName(), "NoList") == 0){ // compressed LMEEoutput.root without user list.
      LmHelper::Debug(Form("  getting cutset, no list: %s", scutset.Data()), 2);
      fCutfolder = (TCollection*) fInputfile->Get(scutset.Data());
    }
    else { // typical LMEEoutput.root with user list.
      LmHelper::Debug(Form(" getting list: %s", oaConfig->At(2)->GetName()), 2);
      fInputfile->GetObject(oaConfig->At(2)->GetName(), lCutset);
      if (!lCutset) LmHelper::Error(Form("LmManager: cannot find list '%s' in rootfile '%s'!", oaConfig->At(2)->GetName(), oaConfig->At(1)->GetName()));
      LmHelper::Debug(Form("  getting cutset, with list: %s", scutset.Data()), 2);
      fCutfolder = (TCollection*) lCutset->FindObject(scutset.Data());
    }
  }
  if (!fCutfolder) LmHelper::Error(Form("LmManager: cannot find cut folder '%s' in rootfile '%s'!", scutset.Data(), oaConfig->At(1)->GetName()));

  CalcEtaRange();
  LmHelper::Debug(Form("   Eta_min = %4.2f           Eta_max = %4.2f", GetEtaRange_min(), GetEtaRange_max()), 3);
  CalcPtRange();
  LmHelper::Debug(Form("   Pt_min  = %4.2f GeV/c      Pt_max  = %4.2f GeV/c", GetPtRange_min(), GetPtRange_max()), 3);
  CalcCentrality();
  LmHelper::Debug(Form("   Centrality_min = %2.0f%%      Centrality_max = %2.0f%%", GetCentrality_min(), GetCentrality_max()), 3);
  if (fThetaEE_min<0) CalcOpeningAngle();
  LmHelper::Debug(Form("   Opening angle (#theta_{ee}) > %3.2f", GetThetaEEmin()), 3);

  // read in the histograms
  if (fNdimInput==2)      GetHistogramsFromFiles2D();
  else if (fNdimInput>=3) GetHistogramsFromFiles3D();
  else { LmHelper::Error("LmManager: invalid input dimension given."); return 1; }

  if (fEnableEffiCorr)    GetEffiHistogramsFromFiles();

  // done (later) in CloseFileAndCleanUp().
  //if (!fUseExternalInputfile) { fInputfile->Close(); delete fInputfile; }

  return 0;
}


//_______________________________________________________________________________________________
void LmManager::CopyHistogramsFrom(const LmManager& man)
{
  /// Copy histograms from other LmManager
  /// (extend if needed)

  LmHelper::Debug(" CopyHistogramsFrom()", 5-debugManager);
  //cout << "  man.fNeventsPhysSel = " << man.fNeventsPhysSel << endl;
  //cout << "  man.fhXdimYdimZdim.size() = " << man.fhXdimYdimZdim.size() << endl;
  //cout << "  man.fhXdimYdimZdim.at(0)->GetName() = " << man.fhXdimYdimZdim.at(0)->GetName() << endl;

  Bool_t copiedEffi=kFALSE;
  Bool_t copied3D  =kFALSE;
  Bool_t copied2D  =kFALSE;
  Bool_t copiedMix =kFALSE;
  Bool_t copiedZtemplates=kFALSE;

  if (man.fhEffiGen) fhEffiGen = new TH2D(*(man.fhEffiGen));
  if (man.fhEffiRec) fhEffiRec = new TH2D(*(man.fhEffiRec));
  if (fhEffiRec&&fhEffiGen) copiedEffi=kTRUE;
  //cout << "  fhEffiRec->GetName(), GetEntries() = " << fhEffiRec->GetName() << " " << fhEffiRec->GetEntries() << endl;

  if (man.fhExclusionZTemplates.size()>0) {
    fhExclusionZTemplates.resize(man.fhExclusionZTemplates.size());
    for (UInt_t i=0;i<man.fhExclusionZTemplates.size();i++) {
      fhExclusionZTemplates[i] = new TH3D(*(man.fhExclusionZTemplates[i]));
    }
    copiedZtemplates=kTRUE;
  }

  if (fNdimInput>=3) {
    if (fhXdimYdimZdim.size()>0) LmHelper::Warning("LmManager::CopyHistogramsFrom(): 3D histograms already present, they will be overwritten! (probably memory leak)");
    if ((Int_t)man.fhXdimYdimZdim.size()==fNpaircombs) {
      fhXdimYdimZdim.resize(fNpaircombs); // resize vector to access elements with '[i]'
      for (Int_t i=0;i<fNpaircombs;i++) {
        fhXdimYdimZdim[i] = new TH3D(*(man.fhXdimYdimZdim[i])); //static_cast<TH3D*> (man.fhXdimYdimZdim[i]->Clone());
      }
      copied3D=kTRUE;
    }
    else LmHelper::Error("LmManager::CopyHistogramsFrom(): 3D-input (same event) not available for copy!");

    if (fhMixedXdimYdimZdim.size()>0) LmHelper::Warning("LmManager::CopyHistogramsFrom(): 3D histograms mixed event already present, they will be overwritten! (probably memory leak)");
    fNmixcombs = (Int_t)man.fhMixedXdimYdimZdim.size();
    if (fNmixcombs>0) {
      fhMixedXdimYdimZdim.resize(fNmixcombs); // resize vector to access elements with '[i]'
      for (Int_t i=0;i<fNmixcombs;i++) {
        fhMixedXdimYdimZdim[i] = new TH3D(*(man.fhMixedXdimYdimZdim[i])); //static_cast<TH3D*> (man.fhMixedXdimYdimZdim[i]->Clone());
      }
      copiedMix=kTRUE;
    }
    //else LmHelper::Error("LmManager::CopyHistogramsFrom(): 3D-input (mixed event) not available for copy!");
  }

  LmHelper::Info(Form("LmManager::CopyHistogramsFrom(): copied histograms of:%s%s%s%s%s.", (copied3D)?" 3D-spectra":"", (copied2D)?" 2D-spectra":"", (copiedMix)?" + mixed-event":"", (copiedEffi)?" + efficiency":"", (copiedZtemplates)?" + Ztemplates":""));
}


//_______________________________________________________________________________________________
void LmManager::SignalPostCorrection(TH2D* hSignal)
{
  /// Called within LmSignal::CalcSubtractedSignal() during LmSignal::Process().
  if (fEnable3DExclCut==kTemplSub || fEnable3DExclCut==kFlatCorrSub || fEnable3DExclCut==kFlatCorrSubAll) {
    CorrectForExclusionCutIn2D(hSignal, kTRUE, kFALSE); // only scale (good enough, if shapes are similar)
    //CorrectForExclusionCutIn2D(hSignal, kTRUE, kTRUE); // both (compensation of different shapes, but unstable)
    //CorrectForExclusionCutIn2D(hSignal, kFALSE, kTRUE); // only shift (bad and not physical, see comments in function)
    //CorrectForExclusionCutIn2D(hSignal, kFALSE, kFALSE); // no scale or shift, just compute and view MCsum.
  }
}


//_______________________________________________________________________________________________
void LmManager::AddVisualSig(TH2D* hSignal, const char* name, const char* title) {
  /// Add a histogram to the vector, which is used mainly for visualizing the 3D exclusion cut correction.
  /// If the first histogram is called 'hDataOrig', it will be used as baseline to normalize the MC templates.
  TString sName(name);
  TString sTitle(title);
  fhVisualSig.push_back((TH2D*) hSignal->Clone( sName.IsNull()?hSignal->GetName():sName.Data() ));
  if (!sTitle.IsNull()) fhVisualSig.back()->SetTitle(sTitle.Data());
}


//_______________________________________________________________________________________________
void LmManager::AddCorrectedSig(TH2D* hSignal, const char* name) {
  /// Provide datapoints which were modified by a previous correction procedure, such as the phiV template fit, which
  /// is done in "STEP 1" of CorrectForExclusionCutIn2D(). In that case they are needed without efficiency correction.
  /// These datapoints are then used in "STEP 2" of CorrectForExclusionCutIn2D() (further explanations in that function).
  TString sName(name);
  if (fhCorrectedSig) delete fhCorrectedSig;
  fhCorrectedSig = (TH2D*) hSignal->Clone( sName.IsNull()?hSignal->GetName():sName.Data() );
}


//_______________________________________________________________________________________________
void LmManager::GetEffiHistogramsFromFiles()
{
  LmHelper::Debug(" GetEffiHistogramsFromFiles()", 5-debugManager);
  if (gSystem->Exec( Form("ls %s > /dev/null",fsEffifile.Data()) )!=0) // file is available if Exec()==0
  {
    LmHelper::Error(Form("LmManager::GetEffiHistogramsFromFiles(): efficiency file '%s' not found. Correction disabled.",fsEffifile.Data()));
    SetEnableEffiCorr(kFALSE);
    return;
  }
  else {
    // By using LmHelper::SafelyOpenRootfile(), all histograms below will be created in a path that still exists after the file is closed.
    TFile* _fileEffi = LmHelper::SafelyOpenRootfile( fsEffifile.Data() );
    LmHelper::Debug(Form("  getting efficiency histograms: gen: %s ,   rec: %s", fsEffiGen.Data(), fsEffiRec.Data()), 2);

    TObjArray* oaEffiGen = fsEffiGen.Tokenize(":");
    if(oaEffiGen->GetEntries()>1){
      for(int i = 0; i<oaEffiGen->GetEntries(); i++){

        TString EffiGen_Tstr = oaEffiGen->At(i)->GetName();
        TObjArray *arrNames_gen = EffiGen_Tstr.Tokenize("/");
        if  (arrNames_gen->GetEntriesFast() > 1){
          TList* llist = dynamic_cast<TList*>(_fileEffi->Get(arrNames_gen->At(0)->GetName()));
          if (llist) llist->SetName(arrNames_gen->At(0)->GetName()); // Otherwise the listname would in most cases be "TList".
          else { LmHelper::Error(Form("LmHelper::GetList(): list '%s' not found in file '%s'.", arrNames_gen->At(0)->GetName(), _fileEffi->GetName())); }
          for (Int_t i=1; i<arrNames_gen->GetEntriesFast() - 1; i++) {
            TList* templist = (TList*) llist->FindObject(arrNames_gen->At(i)->GetName());
            if (templist) {
              llist = templist;
              llist->SetName(arrNames_gen->At(i)->GetName());
            }
            else LmHelper::Warning(Form("LmHelper::GetList(): specified sublist '%s' not found in file '%s'.", arrNames_gen->At(i)->GetName(), _fileEffi->GetName()));
          }
          if(i==0){
            fhEffiGen = new TH2D(*(static_cast<TH2D*> ( llist->FindObject(arrNames_gen->At(arrNames_gen->GetEntries()-1)->GetName()) )));
            if (!fhEffiGen) LmHelper::Error(Form("LmManager::GetEffiHistogramsFromFiles(): histogram for generated ele '%s' not found in file '%s'.", fsEffiGen.Data(),fsEffifile.Data()));
          }
          else
            fhEffiGen->Add((static_cast<TH2D*> ( llist->FindObject(arrNames_gen->At(arrNames_gen->GetEntries()-1)->GetName()) )));
          delete llist;
        }
        else{
          if (!_fileEffi->Get(fsEffiGen.Data())) LmHelper::Error(Form("LmManager::GetEffiHistogramsFromFiles(): histogram for generated ele '%s' not found in file '%s'.", fsEffiGen.Data(),fsEffifile.Data()));
          fhEffiGen = new TH2D(*(static_cast<TH2D*> (_fileEffi->Get(fsEffiGen.Data())/*->Clone("fhEffiGen")*/)));
          fhEffiGen->SetName("fhEffiGen");
        }
      }
    }
    else{

      TObjArray *arrNames_gen = fsEffiGen.Tokenize("/");
      if  (arrNames_gen->GetEntriesFast() > 1){
        TList* llist = dynamic_cast<TList*>(_fileEffi->Get(arrNames_gen->At(0)->GetName()));
        if (llist) llist->SetName(arrNames_gen->At(0)->GetName()); // Otherwise the listname would in most cases be "TList".
        else { LmHelper::Error(Form("LmHelper::GetList(): list '%s' not found in file '%s'.", arrNames_gen->At(0)->GetName(), _fileEffi->GetName())); }
        for (Int_t i=1; i<arrNames_gen->GetEntriesFast() - 1; i++) {
          TList* templist = (TList*) llist->FindObject(arrNames_gen->At(i)->GetName());
          if (templist) {
            llist = templist;
            llist->SetName(arrNames_gen->At(i)->GetName());
          }
          else LmHelper::Warning(Form("LmHelper::GetList(): specified sublist '%s' not found in file '%s'.", arrNames_gen->At(i)->GetName(), _fileEffi->GetName()));
        }
        fhEffiGen = new TH2D(*(static_cast<TH2D*> ( llist->FindObject(arrNames_gen->At(arrNames_gen->GetEntries()-1)->GetName()) )));
        if (!fhEffiGen) LmHelper::Error(Form("LmManager::GetEffiHistogramsFromFiles(): histogram for generated ele '%s' not found in file '%s'.", fsEffiGen.Data(),fsEffifile.Data()));
        delete llist;
      }
      else{
        if (!_fileEffi->Get(fsEffiGen.Data())) LmHelper::Error(Form("LmManager::GetEffiHistogramsFromFiles(): histogram for generated ele '%s' not found in file '%s'.", fsEffiGen.Data(),fsEffifile.Data()));
        fhEffiGen = new TH2D(*(static_cast<TH2D*> (_fileEffi->Get(fsEffiGen.Data())/*->Clone("fhEffiGen")*/)));
        fhEffiGen->SetName("fhEffiGen");
      }
    }

    TObjArray* oaEffiRec = fsEffiRec.Tokenize(":");
    if(oaEffiRec->GetEntries()>1){
      for(int i = 0; i<oaEffiRec->GetEntries(); i++){

        TString EffiRec_Tstr = oaEffiRec->At(i)->GetName();
        TObjArray *arrNames_rec = EffiRec_Tstr.Tokenize("/");

        if  (arrNames_rec->GetEntriesFast() > 1){
          TList* llist = dynamic_cast<TList*>(_fileEffi->Get(arrNames_rec->At(0)->GetName()));
          if (llist) llist->SetName(arrNames_rec->At(0)->GetName()); // Otherwise the listname would in most cases be "TList".
          else { LmHelper::Error(Form("LmHelper::GetList(): list '%s' not found in file '%s'.", arrNames_rec->At(0)->GetName(), _fileEffi->GetName())); }
          for (Int_t i=1; i<arrNames_rec->GetEntriesFast() - 1; i++) {
            TList* templist = (TList*) llist->FindObject(arrNames_rec->At(i)->GetName());
            if (templist) {
              llist = templist;
              llist->SetName(arrNames_rec->At(i)->GetName());
            }
            else LmHelper::Warning(Form("LmHelper::GetList(): specified sublist '%s' not found in file '%s'.", arrNames_rec->At(i)->GetName(), _fileEffi->GetName()));
          }
          if(i==0){
            fhEffiRec = new TH2D(*(static_cast<TH2D*> ( llist->FindObject(arrNames_rec->At(arrNames_rec->GetEntries()-1)->GetName()) )));
            if (!fhEffiRec) LmHelper::Error(Form("LmManager::GetEffiHistogramsFromFiles(): histogram for reconstructed ele '%s' not found in file '%s'.", fsEffiRec.Data(),fsEffifile.Data()));
          }
          else
            fhEffiRec->Add((static_cast<TH2D*> ( llist->FindObject(arrNames_rec->At(arrNames_rec->GetEntries()-1)->GetName()) )));
          delete llist;
        }
        else {
          if (!_fileEffi->Get(fsEffiRec.Data())) LmHelper::Error(Form("LmManager::GetEffiHistogramsFromFiles(): histogram for reconstructed ele '%s' not found in file '%s'.", fsEffiRec.Data(),fsEffifile.Data()));
          fhEffiRec = new TH2D(*(static_cast<TH2D*> (_fileEffi->Get(fsEffiRec.Data())/*->Clone("fhEffiRec")*/)));
          fhEffiRec->SetName("fhEffiRec");
        }
      }
    }

    else{

      TObjArray *arrNames_rec = fsEffiRec.Tokenize("/");
      if  (arrNames_rec->GetEntriesFast() > 1){
        TList* llist = dynamic_cast<TList*>(_fileEffi->Get(arrNames_rec->At(0)->GetName()));
        if (llist) llist->SetName(arrNames_rec->At(0)->GetName()); // Otherwise the listname would in most cases be "TList".
        else { LmHelper::Error(Form("LmHelper::GetList(): list '%s' not found in file '%s'.", arrNames_rec->At(0)->GetName(), _fileEffi->GetName())); }
        for (Int_t i=1; i<arrNames_rec->GetEntriesFast() - 1; i++) {
          TList* templist = (TList*) llist->FindObject(arrNames_rec->At(i)->GetName());
          if (templist) {
            llist = templist;
            llist->SetName(arrNames_rec->At(i)->GetName());
          }
          else LmHelper::Warning(Form("LmHelper::GetList(): specified sublist '%s' not found in file '%s'.", arrNames_rec->At(i)->GetName(), _fileEffi->GetName()));
        }
        fhEffiRec = new TH2D(*(static_cast<TH2D*> ( llist->FindObject(arrNames_rec->At(arrNames_rec->GetEntries()-1)->GetName()) )));
        if (!fhEffiRec) LmHelper::Error(Form("LmManager::GetEffiHistogramsFromFiles(): histogram for reconstructed ele '%s' not found in file '%s'.", fsEffiRec.Data(),fsEffifile.Data()));
        delete llist;
      }
      else {
        if (!_fileEffi->Get(fsEffiRec.Data())) LmHelper::Error(Form("LmManager::GetEffiHistogramsFromFiles(): histogram for reconstructed ele '%s' not found in file '%s'.", fsEffiRec.Data(),fsEffifile.Data()));
        fhEffiRec = new TH2D(*(static_cast<TH2D*> (_fileEffi->Get(fsEffiRec.Data())/*->Clone("fhEffiRec")*/)));
        fhEffiRec->SetName("fhEffiRec");
      }
    }

    // now it is save to close the file and delete the pointer.
    _fileEffi->Close();
    delete _fileEffi;
    SetEnableEffiCorr();
    // the actual efficiency histogram will be calculated later only on request
  }
}


//_______________________________________________________________________________________________
TH3D* LmManager::Obtain3DHistogram(TObject* inputHist, TString newname)
{
  if (!inputHist) LmHelper::Error(Form("LmManager::Obtain3DHistogram(): input histogram '%s' not found.", fsInputhists.Data()));
  TH3D* hist3D = 0x0;
  if(inputHist->IsA() == TH3F::Class() || inputHist->IsA() == TH3D::Class()) {
    LmHelper::Debug("Input is TH3F/TH3D. Creating copy.", 10-debugManager);
    hist3D = new TH3D(*(static_cast<TH3D*>(inputHist)));
  }
  if(inputHist->IsA() == THnSparseT<TArrayD>::Class()) { // Theo
    LmHelper::Debug("Input is THnSparse! Projecting to TH3D.", 10-debugManager);
    THnSparse *sparse = (THnSparse*) inputHist;
    if(sparse->GetNdimensions() > 3) LmHelper::Warning("Sparse with more than 3 Dimensions. Check Input!");
    hist3D = new TH3D(*(static_cast<TH3D*> (sparse->Projection(0,1,2))));
  }
  if(inputHist->IsA() == THnT<Double_t>::Class()) { // Patrick
    LmHelper::Debug("Input is THnD! Projecting to TH3D.", 10-debugManager);
    THnD *hTHn = (THnD*) inputHist;
    if(hTHn->GetNdimensions() > 3) {
      for (UInt_t idim=3; idim<fProjRangeMinima.size(); idim++) {
        Int_t from_bin = hTHn->GetAxis(idim)->FindBin(fProjRangeMinima.at(idim));
        Int_t to_bin   = hTHn->GetAxis(idim)->FindBin(fProjRangeMaxima.at(idim)-LmHelper::kSmallDelta); // subtract a small delta because the upper bin edge already belongs to the next bin!
        LmHelper::Info(Form("LmManager: setting range of input dimension '%i' from bin '%i' to bin '%i'. (dim 0=x etc.)", idim, from_bin, to_bin));
        hTHn->GetAxis(idim)->SetRange(from_bin, to_bin);
      }
    }
    //hist3D = new TH3D(*(static_cast<TH3D*> (hTHn->Projection(0,1,2)))); // Causes warnings about potential memory leak.
    hist3D = static_cast<TH3D*> (hTHn->Projection(0,1,2)); // No copy needed, since a new histogram is created in function Projection(). Make sure to rename.
  }
  if (!hist3D) LmHelper::Error(Form("LmManager::Obtain3DHistogram: could not create TH3D from input object '%s'.", inputHist->GetName()));
  if (!newname.IsNull()) hist3D->SetName(newname.Data());
  return hist3D;
}


//_______________________________________________________________________________________________
void LmManager::GetHistogramsFromFiles3D()
{
  /// Read in 3D histograms from rootfile.

  LmHelper::Debug(" GetHistogramsFromFiles3D()", 5-debugManager);

  TObjArray* oaPairCombNames = fPairCombNames.Tokenize(";");
  TObjArray* oaMixCombNames  = fMixCombNames.Tokenize(";");
  //const Char_t *PairCombNames[] = {"Pair_ev1+_ev1-","Pair_ev1+_ev1+","Pair_ev1-_ev1-"};
  //const Char_t *MixCombNames[] = {"Pair_ev1-_ev2+","Pair_ev1+_ev2+","Pair_ev1-_ev2-","Pair_ev1+_ev2-"};
  //Color_t *PairCombColors[fNpaircombs] = {kBlack,kBlue,kRed};

  // resize vectors to have space for histograms
  // (using '.reserve' doesnt change the vector size so the '.size' command still returns 0):
  fhXdimYdimZdim.resize(fNpaircombs);
  fhMixedXdimYdimZdim.resize(fNmixcombs);
  //cout << "  fhXdimYdimZdim.size() = " << fhXdimYdimZdim.size() << endl;

  //--------------------------------------------
  //Get 3D mee-pt-phiv histograms for all periods
  //
  // the code for reading in multiple periods was inherited from Christoph, but should be checked if actually used again with more than 1 period.
  //
  TH3D* hMeePteePeriod[fNperiodsMAX][fNpaircombs];
  TH3D* hMixedMeePteePeriod[fNperiodsMAX][fNmixcombs];

  LmHelper::Debug(Form("  read in nEvents and pair histograms named: %s", fsInputhists.Data()), 10-debugManager);
  Double_t nEventsThisCut=0;
  for (int j=0; j < fNperiods; j++) {
    //    TCollection* fCutfolder;
    TCollection* histFolderTemp;
    TCollection* histFolderPair[fNpaircombs];
    TCollection* histFolderMix[fNmixcombs];

    //Get nEvents for this Cut
    // Folder with histogram class "Event" (Hashlists)
    histFolderTemp = (TCollection*) fCutfolder->FindObject("Event");
    TH1D* hNevents = (TH1D*) histFolderTemp->FindObject("nEvents");
    nEventsThisCut+=hNevents->GetBinContent(1); //After PhysicsSelection // old comment by Christoph: "nevents getter may be wrong"

    for (Int_t i=0;i<fNpaircombs;i++) {
      LmHelper::Debug(Form(" %s",oaPairCombNames->At(i)->GetName()), 10-debugManager);
      histFolderPair[i] = (TCollection*) fCutfolder->FindObject(oaPairCombNames->At(i)->GetName());
      if (!histFolderPair[i]) {
        LmHelper::Error(Form("LmManager::GetHistogramsFromFiles3D(): no pair histogram folder '%s' available.", oaPairCombNames->At(i)->GetName()));
      }
      hMeePteePeriod[j][i] = Obtain3DHistogram(histFolderPair[i]->FindObject(fsInputhists.Data()), Form("%s_%s",fsInputhists.Data(),oaPairCombNames->At(i)->GetName()));
    }
    for (Int_t i=0;i<fNmixcombs;i++) {
      LmHelper::Debug(Form(" %s",oaMixCombNames->At(i)->GetName()), 10-debugManager);
      histFolderMix[i] = (TCollection*) fCutfolder->FindObject(oaMixCombNames->At(i)->GetName());
      if (!histFolderMix[i]) {
        LmHelper::Warning("LmManager::GetHistogramsFromFiles3D(): no mixed event histograms available.");
        fNmixcombs=0;
        fhMixedXdimYdimZdim.resize(fNmixcombs); // needed for check in function CopyHistogramsFrom().
        break;
      }
      hMixedMeePteePeriod[j][i] = Obtain3DHistogram(histFolderMix[i]->FindObject(fsInputhists.Data()), Form("%s_%s",fsInputhists.Data(),oaMixCombNames->At(i)->GetName()));
    }
  }
  fNeventsPhysSel=nEventsThisCut; //After PhysicsSelection
  //LmHelper::Debug(Form("  fNeventsPhysSel = %f", fNeventsPhysSel), 10);

  //-----------------------------------------------------
  //Add 3d Histograms of all periods
  for (int j=0; j < fNperiods; j++) {
    for (Int_t i=0;i<fNpaircombs;i++) {
      if (j==0) {
        fhXdimYdimZdim[i] = new TH3D(*(hMeePteePeriod[j][i])); //static_cast<TH3D*> (hMeePteePeriod[j][i]->Clone());
        // modify title according to specifications in LmBaseSignal
        SetTitlesInputhist(fhXdimYdimZdim[i]);
        //fhXdimYdimZdim[i]->SetTitle(Form("%s;%s;%s;%s",fhXdimYdimZdim[i]->GetName(),LmBaseSignal::GetInputLabelX().Data(),LmBaseSignal::GetInputLabelY().Data(),LmBaseSignal::GetInputLabelZ().Data()));
        // @TODO warning: the functions LmBaseSignal::GetInputLabelX()Y/Z sometimes interact in a fancy way when called within one form statement. may want to use some casts to fix this somehow.
      }
      else {
        fhXdimYdimZdim[i]->Add(hMeePteePeriod[j][i]);
      }
    }
    for (Int_t i=0;i<fNmixcombs;i++) {
      if (j==0) {
        fhMixedXdimYdimZdim[i] = new TH3D(*(hMixedMeePteePeriod[j][i])); //static_cast<TH3D*> (hMixedMeePteePeriod[j][i]->Clone());
        // modify title according to specifications in LmBaseSignal
        SetTitlesInputhist(fhMixedXdimYdimZdim[i]);
      }
      else {
        fhMixedXdimYdimZdim[i]->Add(hMixedMeePteePeriod[j][i]);
      }
    }
  }
  //Delete 3d Histograms per period
  for (int j=0; j < fNperiods; j++) {
    for (Int_t i=0;i<fNpaircombs;i++) {
      delete hMeePteePeriod[j][i];
    }
    for (Int_t i=0;i<fNmixcombs;i++) {
      delete hMixedMeePteePeriod[j][i];
    }
  }
//  TH3F* hist = fhXdimYdimZdim[0];
//  LmHelper::Debug(" LmManager::GetHistogramsFromFiles3D()", 3);
//  LmHelper::Debug(Form(" |-> title: %s,   x: %s,   y: %s,   z: %s", hist->GetTitle(), hist->GetXaxis()->GetTitle(), hist->GetYaxis()->GetTitle(), hist->GetZaxis()->GetTitle()), 3);

}



//_______________________________________________________________________________________________
void LmManager::SetProjRange(Double_t min, Double_t max, UInt_t axis) {
  /// Set the projection range of one axis (x=0, y=1 etc). Use max <= min to reset the range.
  /// The ranges for X, Y, and Z dimension are used in Set3DProjectionRanges() & ProjectInto2D() during Process().
  /// The ranges for higher dimensions are used in Obtain3DHistogram() during GetHistogramsFromFiles3D().
  if (axis >= GetNdimInput()) {
    LmHelper::Warning(Form("LmManager::SetProjRange(): axis '%i'(0=x,1=y,...) is beyond input dimension N='%i'. Ignoring range.", axis, GetNdimInput()));
    return;
  }
  if (axis >= fProjRangeMinima.size()) {
    fProjRangeMinima.resize(axis+1);
    fProjRangeMaxima.resize(axis+1);
  }
  if (max <= min) { // For initializing and resetting the range.
    // Please keep "<=", because a delta is subtracted from max later, causing max<min if it was equal.
    // Initial values must all be negative so that Set3DProjectionRanges() doesn't do anything by default.
    // The same numbers are used for checks, e.g. in GetAll3DProjRanges(), so change consistently if needed.
    fProjRangeMinima.at(axis) = -1.0e20;
    fProjRangeMaxima.at(axis) = -1.0e20;
  }
  else {
    fProjRangeMinima.at(axis) = min;
    fProjRangeMaxima.at(axis) = max;
  }
}


//_______________________________________________________________________________________________
void LmManager::InitProjectionRanges() {
  /// Called inside LmBaseManager::SetInputhistAndDim().
  /// Ranges for X, Y, Z (depending on GetNdimInput()) have to be initialized, because they are automatically used.
  fProjRangeMinima.clear();
  fProjRangeMaxima.clear();
  if (GetNdimInput()>2) SetProjRange(-1, -1, 2); // init z first, so that the vector needs only one resize().
  if (GetNdimInput()>1) SetProjRange(-1, -1, 1);
  SetProjRange(-1, -1, 0);
}


//_______________________________________________________________________________________________
void LmManager::Set3DProjectionRanges()
{
  /// Can modify the projection ranges of all 3D input histograms to analyze only a subset of the data after projection.
  /// For the full axis range, min and max must be negative (in the underflow bin).
  Double_t xminbin = fhXdimYdimZdim[0]->GetXaxis()->FindBin(fProjRangeMinima[0]);
  Double_t xmaxbin = fhXdimYdimZdim[0]->GetXaxis()->FindBin(fProjRangeMaxima[0]-LmHelper::kSmallDelta); // subtract a small delta because the upper bin edge already belongs to the next bin!
  Double_t yminbin = fhXdimYdimZdim[0]->GetYaxis()->FindBin(fProjRangeMinima[1]);
  Double_t ymaxbin = fhXdimYdimZdim[0]->GetYaxis()->FindBin(fProjRangeMaxima[1]-LmHelper::kSmallDelta);
  Double_t zminbin = fhXdimYdimZdim[0]->GetZaxis()->FindBin(fProjRangeMinima[2]);
  Double_t zmaxbin = fhXdimYdimZdim[0]->GetZaxis()->FindBin(fProjRangeMaxima[2]-LmHelper::kSmallDelta);
  //cout << " zminbin = " << zminbin  << " zmaxbin = " << zmaxbin << endl;
  // modify projection ranges.
  for (Int_t i=0;i<fNpaircombs;i++) {
    fhXdimYdimZdim[i]->GetXaxis()->SetRange(xminbin, xmaxbin);
    fhXdimYdimZdim[i]->GetYaxis()->SetRange(yminbin, ymaxbin);
    fhXdimYdimZdim[i]->GetZaxis()->SetRange(zminbin, zmaxbin);
  }
  for (Int_t i=0;i<fNmixcombs;i++) {
    fhMixedXdimYdimZdim[i]->GetXaxis()->SetRange(xminbin, xmaxbin);
    fhMixedXdimYdimZdim[i]->GetYaxis()->SetRange(yminbin, ymaxbin);
    fhMixedXdimYdimZdim[i]->GetZaxis()->SetRange(zminbin, zmaxbin);
  }
  for (UInt_t i=0;i<fhExclusionZTemplates.size();i++) {
    fhExclusionZTemplates[i]->GetXaxis()->SetRange(xminbin, xmaxbin);
    fhExclusionZTemplates[i]->GetYaxis()->SetRange(yminbin, ymaxbin);
    fhExclusionZTemplates[i]->GetZaxis()->SetRange(zminbin, zmaxbin);
  }
}


//_______________________________________________________________________________________________
void LmManager::ProjectInto2D()
{
  /// Project 3D histograms into 2D histograms for further analysis.

  LmHelper::Debug(" ProjectInto2D()", 5-debugManager);

  // resize vectors to have space for histograms
  // (using '.reserve' doesnt change the vector size so the '.size' command still returns 0):
  fhMeePtee.resize(fNpaircombs);
  fhMixedMeePtee.resize(fNmixcombs);
  // store the correct axis labels for the projected histograms
  LmBaseSignal::CorrelateAxesOfInputAndProjections(fsProjOption);

  TString option=fsProjOption;
  option.ReplaceAll(" ",""); // delete spaces
  TString sHistName = fsInputhists;
  sHistName.Append("_"+option);

  // extend name depending on which projection ranges have been set
  if (fhXdimYdimZdim[0]->GetXaxis()->TestBit(TAxis::kAxisRange)) sHistName.Append(Form("_x%.3fto%.3f",fProjRangeMinima[0],fProjRangeMaxima[0]));
  if (fhXdimYdimZdim[0]->GetYaxis()->TestBit(TAxis::kAxisRange)) sHistName.Append(Form("_y%.3fto%.3f",fProjRangeMinima[1],fProjRangeMaxima[1]));
  if (fhXdimYdimZdim[0]->GetZaxis()->TestBit(TAxis::kAxisRange)) sHistName.Append(Form("_z%.3fto%.3f",fProjRangeMinima[2],fProjRangeMaxima[2]));
  //cout << " sHistName = " << sHistName.Data() << endl;

  for (Int_t i=0;i<fNpaircombs;i++) {
    //Project Histograms into 2D
    fhMeePtee[i] = static_cast<TH2D*> (fhXdimYdimZdim[i]->Project3D(option));
    fhMeePtee[i]->SetName(Form("%s_%d",sHistName.Data(),i)); // without this renaming, root is confused and will later rebin the same histogram many times...
    // set the content label (e.g. yield). seems not possible to set it in 3D-histograms already.
    // the other axis labels are correctly taken from the 3D-histogram.
    fhMeePtee[i]->GetZaxis()->SetTitle(LmBaseSignal::GetProjLabelContent().Data());
  }

  for (Int_t i=0;i<fNmixcombs;i++) {
    //Project Histograms into 2D
    fhMixedMeePtee[i] = static_cast<TH2D*> (fhMixedXdimYdimZdim[i]->Project3D(option));
    fhMixedMeePtee[i]->SetName(Form("%s_Mix%d",sHistName.Data(),i));
    // set the content label (e.g. yield). seems not possible to set it in 3D-histograms already.
    // the other axis labels are correctly taken from the 3D-histogram.
    fhMixedMeePtee[i]->GetZaxis()->SetTitle(LmBaseSignal::GetProjLabelContent().Data());
  }
  if (HasMixedEvent()) { // create sum of mixed event ULS +- and -+ for function GetUnlikeMix().
    if (fhMixedMeePteeULS) delete fhMixedMeePteeULS;
    fhMixedMeePteeULS = new TH2D(*fhMixedMeePtee[0]);
    fhMixedMeePteeULS->Add(fhMixedMeePtee[3]);
    fhMixedMeePteeULS->SetName(Form("%s_MixULS",sHistName.Data()));
  }

//  TH2D* hist = fhMeePtee[0];
//  LmHelper::Debug(" LmManager::ProjectInto2D()", 3);
//  LmHelper::Debug(Form(" |-> title: %s,   x: %s,   y: %s,   z: %s", hist->GetTitle(), hist->GetXaxis()->GetTitle(), hist->GetYaxis()->GetTitle(), hist->GetZaxis()->GetTitle()), 3);

}


//_______________________________________________________________________________________________
Bool_t LmManager::Find3DExclusionValues(Double_t x/*, Double_t y*/) {
  /// Searches in vector f3DExclusionEdgesX for the first edge which is above the given x. (i.e.: use bin low edge)
  /// The corresponding values in the vectors f3DExclusionZbelow and f3DExclusionZabove are then used as the 3D cut
  /// values, i.e. the variables 'fCutValZbelow' and 'fCutValZabove' are updated by each function call.
  /// Same is done for the template normalization region if applicable ('fTemplNormMin' and 'fTemplNormMax').
  /// (y not implemented. Calls of this function then must be moved into the y-axis loops and logic re-checked.)
  LmHelper::Debug(Form(" Find3DExclusionValues( x = %.3f )", x), 7-debugManager);
  // shortcut, if already above the last cut value.
  if (x >= f3DExclusionEdgesX.back() ) return kFALSE; // "back" gives the last element.
  for (UInt_t iCutEdgeX=0; iCutEdgeX<f3DExclusionEdgesX.size(); ++iCutEdgeX) {
    if (x < f3DExclusionEdgesX.at(iCutEdgeX) ) {
      //fCutValMee  = f3DExclusionEdgesX.at(iCutEdgeX);
      fCutValZbelow = f3DExclusionZbelow.at(iCutEdgeX);
      fCutValZabove = f3DExclusionZabove.at(iCutEdgeX);
      if (iCutEdgeX<fTemplateNormRegionMin.size()) {
        fTemplNormMin = fTemplateNormRegionMin.at(iCutEdgeX);
        fTemplNormMax = fTemplateNormRegionMax.at(iCutEdgeX);
      }
      else { // use all remaining yield for normalization.
        fTemplNormMin = fCutValZbelow;
        fTemplNormMax = fCutValZabove;
      }
//      cout << " iCutEdgeX = " << iCutEdgeX << flush;
//      cout << "   f3DExclusionEdgesX = " << f3DExclusionEdgesX.at(iCutEdgeX) << flush;
//      cout << "   f3DExclusionZbelow = " << f3DExclusionZbelow.at(iCutEdgeX) << flush;
//      cout << "   f3DExclusionZabove = " << f3DExclusionZabove.at(iCutEdgeX) << endl;
      return kTRUE;
    }
  }
  return kFALSE;
}

//_______________________________________________________________________________________________
Bool_t LmManager::InExclusionCutRegion(Double_t binLowEdge, Double_t binUpEdge) {
  /// Always call Find3DExclusionValues(x) beforehand to buffer the correct exclusion values corresponding to the current x value!
  /// For the moment, two exclusion zones are foreseen, which means one inclusion zone in between them.
  /// @TODO: implement possibility of one exclusion zone in the middle and two inclusion zones below and above it.
  ///        To distinguish the two cases, one must check if fCutValZabove is larger or smaller than fCutValZbelow [also in CorrectForExclusionCutIn2D()].
  /// @TODO: give warning if bin is partly inside and outside of cut region.
  if (   binLowEdge+LmHelper::kSmallDelta < fCutValZabove
      && binUpEdge -LmHelper::kSmallDelta > fCutValZbelow )
    return kFALSE;
  return kTRUE;
}

//_______________________________________________________________________________________________
Bool_t LmManager::InTemplateNormRegion(Double_t binLowEdge, Double_t binUpEdge) {
  /// Always call Find3DExclusionValues(x) beforehand to buffer the correct normalization region corresponding to the current x value!
  /// One connected normalization region is foreseen. Its min and max is set for each bin in 'f3DExclusionEdgesX'.
  /// @TODO: give warning if bin is partly inside and outside of cut region.
  if (   binLowEdge+LmHelper::kSmallDelta > fTemplNormMin
      && binUpEdge -LmHelper::kSmallDelta < fTemplNormMax )
    return kTRUE;
  return kFALSE;
}


//_______________________________________________________________________________________________
void LmManager::ApplyExclusionCutIn3D()
{
  /// Apply an exclusion cut in the Z dimension of 3D input histograms. The cut can be a function of x by setting
  /// one or multiple cut edges via Set3DExclusionEdgesX(), otherwise the cut is done over the full x range (<1e20).
  /// Specify the same number of Z dimension cut values via Set3DExclusionZbelow() and ...Zabove().
  /// Excluded bins are set to 0. The yield is recovered by CorrectForExclusionCut...() either assuming a flat Z
  /// distribution (only roughly ok for soft phiV cut) or by template histograms given via SetExclusionZTemplates().
  ///
  /// This example, assuming X=Mee and Z=phiV, will keep bins with 0<phiV<1/2pi for mee<0.04,
  /// 0<phiV<3/4pi for mee=0.04-0.1, and keep all bins above 0.1 GeV.
  /// (For phiV, a lower exclusion cut!=0 is not needed for output from the official Dielectron Framework.)
  /// Double_t cutPhiVbelow[] = { 0.,                0. };
  /// Double_t cutPhiVabove[] = { 1./2.*TMath::Pi(), 3./4.*TMath::Pi() };
  /// Double_t cutEdgesMee[]  = { 0.04,              0.10 };
  /// Int_t    n_cutPhiVbelow = sizeof(cutPhiVbelow)/sizeof(*cutPhiVbelow);
  /// Int_t    n_cutPhiVabove = sizeof(cutPhiVabove)/sizeof(*cutPhiVabove);
  /// Int_t    n_cutEdgesMee  = sizeof(cutEdgesMee)/sizeof(*cutEdgesMee);
  /// mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
  /// mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
  /// mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
  //
  {
    LmHelper::Debug(" ApplyExclusionCutIn3D()", 5-debugManager);
    if (f3DExclusionZbelow.size()==0) f3DExclusionZbelow.push_back(-1.0e20);
    if (f3DExclusionZabove.size()==0) f3DExclusionZabove.push_back(+1.0e20);
    if (f3DExclusionEdgesX.size()==0) { f3DExclusionEdgesX.push_back(-1.0e20);
      LmHelper::Warning(Form("LmManager: no x value for Z exclusion cut given. Cut will not be executed. To change this, call Set3DExclusionEdgesX()."));
    }
    if (f3DExclusionZbelow.size()!=f3DExclusionEdgesX.size() || f3DExclusionZabove.size()!=f3DExclusionEdgesX.size()) {
      LmHelper::Error(Form("LmManager: number of Z exclusion cut values different from cut edges. Call Set3DExclusionZbelow/Zabove/EdgesX with same array sizes."));
      LmHelper::Error(Form("           ---> Z exclusion cut disabled!"));
      fEnable3DExclCut = kNoCut;
      return;
    }

    // Canvas for debugging
    //  TCanvas* cMeePtPhiV = new TCanvas("cMeePtPhiV","cMeePtPhiV",1200,400);
    //  cMeePtPhiV->Divide(4,1);

    Double_t myBinningPi = fhXdimYdimZdim[0]->GetZaxis()->GetBinUpEdge(fhXdimYdimZdim[0]->GetNbinsZ());
    LmHelper::Debug(Form("  fhXdimYdimZdim highest PhiV: 'myBinningPi' = %f", myBinningPi), 10);
    // should be pi for new outputs, but 3.2 for preliminary outputs, so some corrections are needed...

    TObjArray* oaConfig = fsConfiglong.Tokenize(":");
    TString sTrainNr = oaConfig->At(1)->GetName();
    sTrainNr.Remove(0, sTrainNr.First('-')+1);
    if(sTrainNr.First('-') >= 0) sTrainNr.Remove(sTrainNr.First('-'), sTrainNr.Length());
    Bool_t oldDef = (fsConfiglong.Contains("2.76") && (atoi(sTrainNr.Data())>0) && (atoi(sTrainNr.Data())<494));
    if (oldDef) LmHelper::Warning(Form("LmManager: found Pb-Pb Run1 train (# %s) with old PhiV definition (correct?) -> flipping Like-Sign cut!", sTrainNr.Data()));
    if (oldDef) LmHelper::Warning(Form(" -> the correction of this cut in 3D via templates will be wrong, unless a symmetric cut is applied and the LS template is flipped."));

    //-----------------------------------------------------
    //Apply the exclusion cut
    for (Int_t i=0;i<fNpaircombs;i++) {
      for(Int_t ix = 1; ix <= fhXdimYdimZdim[i]->GetNbinsX(); ++ix){
        Bool_t validCuts = Find3DExclusionValues(fhXdimYdimZdim[i]->GetXaxis()->GetBinLowEdge(ix));
        if (!validCuts) break; // safety check and shortcut, if already above the last cut value.
        for(Int_t iy = 1; iy <= fhXdimYdimZdim[i]->GetNbinsY(); ++iy){
          for(Int_t iz = 1; iz <= fhXdimYdimZdim[i]->GetNbinsZ(); ++iz) //for(Int_t iz = fhXdimYdimZdim[i]->GetNbinsZ(); iz >= 1; --iz)
          {
            if (oldDef && i>0) { // inverted behaviour for old LS definition: 'fCutValZabove' cuts on low side of PhiV and vice versa.
              if (   fhXdimYdimZdim[i]->GetZaxis()->GetBinUpEdge(iz) -LmHelper::kSmallDelta > (myBinningPi /*TMath::Pi()*/ - fCutValZabove)
                  && fhXdimYdimZdim[i]->GetZaxis()->GetBinLowEdge(iz)+LmHelper::kSmallDelta < (myBinningPi /*TMath::Pi()*/ - fCutValZbelow) )
                continue;
            }
            else { // 'fCutValZabove' cuts on high side of PhiV, same behaviour for ULS and (new) LS
              if ( !InExclusionCutRegion(fhXdimYdimZdim[i]->GetZaxis()->GetBinLowEdge(iz), fhXdimYdimZdim[i]->GetZaxis()->GetBinUpEdge(iz)) ) continue;
            }
            //if (ix==1 && iy==1) Printf("applying Z exclusion cut. i=%i. Exclude bin: Z = [ %5.3f, %5.3f ]", i, fhXdimYdimZdim[i]->GetZaxis()->GetBinLowEdge(iz), fhXdimYdimZdim[i]->GetZaxis()->GetBinUpEdge(iz));
            fhXdimYdimZdim[i]->SetBinContent(ix,iy,iz, 0);
            fhXdimYdimZdim[i]->SetBinError(ix,iy,iz, 0);
          }
        }
      }
      //    cMeePtPhiV->cd(i+1);
      //    fhXdimYdimZdim[i]->DrawClone();
    }
    LmHelper::Debug(" ApplyExclusionCutIn3D() done.", 6-debugManager);
  }
}


//_______________________________________________________________________________________________
void LmManager::SubtractConversionTemplate()
{
  /// Warning: when templates shall be added or subtracted, they have to be based on the same number of events.
  /// This is usually not the case between data and MC. Therefore:
  /// 1) Scale the templates per 1 event before giving them to the manager.
  /// 2) Make sure that inside this function the templates are scaled to the number of data events where needed.
  if (fEnable3DExclCut<kDoCut) return;
  LmHelper::Debug(" SubtractConversionTemplate()", 5-debugManager);
  /// Special case kTemplConv: subtract conversion yield from data.
  if (fEnable3DExclCut==kTemplConv) {
    if (fhExclusionZTemplates.size()==0) {
      LmHelper::Warning("LmManager: no template for conversion subtraction available. Deactivating 3D cut and correction.");
      fEnable3DExclCut = kNoCut;
      return;
    }
    fhExclusionZTemplates[0]->Scale( GetNeventsPhysSel() ); // assumes that the template was scaled to one event before.
    fhXdimYdimZdim[0]->Add(fhExclusionZTemplates[0], -1);
  }
  /// Cases depending on the template histogram name(s):
  /// Feel free to add other cases...
  ///
  /// Case A: if 2 prompt templates are given (without and with prefilter cut) -> scale the unfiltered to the filtered. Must/should be done bin by bin during correction.
  //  if (TString(fhExclusionZTemplates[0]->GetName()).EqualTo("hSigNoPF")) {
  //    for (UInt_t i=1; i<fhExclusionZTemplates.size(); i++) {
  //      if (TString(fhExclusionZTemplates[i]->GetName()).EqualTo("hSig")) {
  //      }
  //    }
  //  }
}

//_______________________________________________________________________________________________
void LmManager::CorrectForExclusionCutIn3D()
{
  /// The yield in the input histograms which was removed by the 3D exclusion cut is recovered by using templates,
  /// which are specified via SetExclusionZTemplates().
  /// Templates are scaled to the data for each x and y bin individually, because the spectral shapes may be different.
  /// This scaling is done in the normalization region, which is specified using SetTemplateNormRegionMin/Max().
  /// Please note that statistics (empty bins) may become an issue, even though the procedure is robust to a certain degree.
  {
    LmHelper::Debug(" CorrectForExclusionCutIn3D()", 5-debugManager);
    if (fhExclusionZTemplates.size()==0) {
      LmHelper::Error("LmManager: no templates for 3D correction of Z exclusion cut available. Choose different exclusion cut type.");
      return;
      // Tried to implement the flat correction for 3D histograms. The commented-out code in this function is ok but
      // one also has to do it for mixed-events and especially also for the histogram 'fhMixedMeePteeULS'.
    }

    // Canvas for debugging
    //  TCanvas* canTempl = new TCanvas("canTempl","canTempl",400,800);
    //  canTempl->Divide(1,2);
    //  canTempl->cd(1)->SetRightMargin(0.15);
    //  fhExclusionZTemplates.at(0)->DrawCopy("colz");
    //  canTempl->cd(2)->SetRightMargin(0.15);
    //  fhExclusionZTemplates.at(1)->DrawCopy("colz");
    //  canTempl->Print("templates.pdf");

    if (fTemplateNormRegionMin.size()==0) {
      LmHelper::Error("LmManager: no normalization region for Z exclusion cut correction templates given. Call SetTemplateNormRegionMin/Max().");
      return;
    }

    Double_t yieldData_norm(0), yieldTempl_norm(0), yieldTempl_corr(0); // yields in normalization and correction region.
    Int_t nEmptyBinsTempl[3]={0,0,0};
    Int_t templ_binx1, templ_binx2, templ_biny1, templ_biny2, templ_binz1_norm, templ_binz2_norm, templ_binz1_corr, templ_binz2_corr;
    Int_t data_binz1_norm, data_binz2_norm;
    Double_t xval_low(-1), xval_up(-1), yval_low(-1), yval_up(-1), zval_low(-1), zval_up(-1);

    for (Int_t i=0;i<fNpaircombs;i++) {

      // loop only over the x range which is requested via Set3DProjRangeX (=full range if unset).
      for(Int_t ix = fhXdimYdimZdim[i]->GetXaxis()->GetFirst(); ix <= fhXdimYdimZdim[i]->GetXaxis()->GetLast(); ++ix){
        Bool_t validCuts = Find3DExclusionValues(fhXdimYdimZdim[i]->GetXaxis()->GetBinLowEdge(ix));
        if (!validCuts) break; // safety check and shortcut, if already above the last cut value.
        xval_low = fhXdimYdimZdim[i]->GetXaxis()->GetBinLowEdge(ix);
        xval_up  = fhXdimYdimZdim[i]->GetXaxis()->GetBinUpEdge(ix);
        //if (fEnable3DExclCut!=kFlatCorr) {
        templ_binx1 = fhExclusionZTemplates[i]->GetXaxis()->FindBin(xval_low);
        templ_binx2 = fhExclusionZTemplates[i]->GetXaxis()->FindBin(xval_up-LmHelper::kSmallDelta);
        // store normalization region in current x-axis bin (the z range for normalization stays identical throughout all y bins).
        templ_binz1_norm = fhExclusionZTemplates[i]->GetZaxis()->FindBin(fTemplNormMin);
        templ_binz2_norm = fhExclusionZTemplates[i]->GetZaxis()->FindBin(fTemplNormMax-LmHelper::kSmallDelta);
        //}
        data_binz1_norm = fhXdimYdimZdim[i]->GetZaxis()->FindBin(fTemplNormMin);
        data_binz2_norm = fhXdimYdimZdim[i]->GetZaxis()->FindBin(fTemplNormMax-LmHelper::kSmallDelta);
        //Int_t nDataBins_norm = data_binz2_norm - data_binz1_norm + 1;
        //Int_t nDataBins_cut = fhXdimYdimZdim[i]->GetNbinsZ() - nDataBins_norm;
        //LmHelper::Debug(Form("  nDataBins_norm = %i \t nDataBins_cut = %i", nDataBins_norm, nDataBins_cut), 10-debugManager);

        // loop only over the y range which is requested via Set3DProjRangeY (=full range if unset).
        for(Int_t iy = fhXdimYdimZdim[i]->GetYaxis()->GetFirst(); iy <= fhXdimYdimZdim[i]->GetYaxis()->GetLast(); ++iy){
          yval_low = fhXdimYdimZdim[i]->GetYaxis()->GetBinLowEdge(iy);
          yval_up  = fhXdimYdimZdim[i]->GetYaxis()->GetBinUpEdge(iy);
          //if (fEnable3DExclCut!=kFlatCorr) {
          templ_biny1 = fhExclusionZTemplates[i]->GetYaxis()->FindBin(yval_low);
          templ_biny2 = fhExclusionZTemplates[i]->GetYaxis()->FindBin(yval_up-LmHelper::kSmallDelta);
          yieldTempl_norm = fhExclusionZTemplates[i]->Integral(templ_binx1, templ_binx2, templ_biny1, templ_biny2, templ_binz1_norm, templ_binz2_norm);
          //}
          yieldData_norm  = fhXdimYdimZdim[i]->Integral(ix, ix, iy, iy, data_binz1_norm, data_binz2_norm);
          LmHelper::Debug(Form("  x=[%.3f,%.3f], y=[%.3f,%.3f]. \t norm. yield data = %f \t template = %f   (i=%i)", xval_low, xval_up, yval_low, yval_up, yieldData_norm, yieldTempl_norm, i), 10-debugManager);

          // If the data yield in the normalization region is zero, we assume that this x-y-bin is completely empty and skip it.
          // This is expected due to low statistics at high mee and/or ptee or possibly phase space when using other variables.
          if (yieldData_norm==0) continue;
          // However if the data is non-zero, the template should ideally also be filled in this region, so we benchmark exceptions.
          if (yieldTempl_norm==0 /*&& fEnable3DExclCut!=kFlatCorr*/) {
            LmHelper::Debug(Form("  normalization template yield = 0 for bin at x=[%.3f,%.3f], y=[%.3f,%.3f]. Skip this bin.", xval_low, xval_up, yval_low, yval_up), 7-debugManager);
            nEmptyBinsTempl[i]++;
            continue;
          }

          for(Int_t iz = 1; iz <= fhXdimYdimZdim[i]->GetNbinsZ(); ++iz){
            // Shortcut: if the data yield in the current z bin is non-zero, then we are not in the correction region.
            if (! (fhXdimYdimZdim[i]->GetBinContent(ix,iy,iz)==0) ) continue;
            zval_low = fhXdimYdimZdim[i]->GetZaxis()->GetBinLowEdge(iz);
            zval_up  = fhXdimYdimZdim[i]->GetZaxis()->GetBinUpEdge(iz);
            // Check if in cut region. (data yield of zero is not a valid check, due to possible empty bins anywhere.)
            if ( !InExclusionCutRegion(zval_low, zval_up) ) continue;
            //if (fEnable3DExclCut==kFlatCorr) {
            //  fhXdimYdimZdim[i]->SetBinContent(ix,iy,iz, yieldData_norm/nDataBins_norm);
            //  fhXdimYdimZdim[i]->SetBinError  (ix,iy,iz, TMath::Sqrt(yieldData_norm) * (nDataBins_cut+2*nDataBins_norm)/(nDataBins_norm*nDataBins_norm));
            //  // Error calculated by hand such that the total relative error after the projection should stay the same...
            //} else {
            templ_binz1_corr = fhExclusionZTemplates[i]->GetZaxis()->FindBin(zval_low);
            templ_binz2_corr = fhExclusionZTemplates[i]->GetZaxis()->FindBin(zval_up-LmHelper::kSmallDelta);
            yieldTempl_corr  = fhExclusionZTemplates[i]->Integral(templ_binx1, templ_binx2, templ_biny1, templ_biny2, templ_binz1_corr, templ_binz2_corr);
            // Set corrected bin content and error (@TODO: think about error again...):
            fhXdimYdimZdim[i]->SetBinContent(ix,iy,iz, yieldTempl_corr*yieldData_norm/yieldTempl_norm);
            fhXdimYdimZdim[i]->SetBinError  (ix,iy,iz, TMath::Sqrt(yieldTempl_corr*yieldData_norm/yieldTempl_norm));
            //}
          }
        } // iy
      } // ix
    } // fNpaircombs
    if (nEmptyBinsTempl[0]>0 || nEmptyBinsTempl[1]>0 || nEmptyBinsTempl[2]>0) {
      LmHelper::Warning(Form("LmManager::CorrectForExclusionCutIn3D(): template yield = 0 in normalization region for %i ULS, %i LS++, %i LS-- bins of input histograms. Please check robustness of correction / rebin 3D input histograms / increase template statistics / enlarge normalization region.", nEmptyBinsTempl[0], nEmptyBinsTempl[1], nEmptyBinsTempl[2]));
    }
  }
}

//_______________________________________________________________________________________________
void LmManager::CorrectForExclusionCutIn2D(TH2D* hSignal, Bool_t doScale, Bool_t doShift)
{
  /// Different cases:
  /// kFlatCorrUnsub: Correct the unsubtracted histograms for the excluded phase space, assuming a flat distribution of the z dimension.
  /// kFlatCorrSub:   Correct the subtracted signal for the excluded phase space, assuming a flat distribution of the z dimension.
  /// kTemplSub:      Template(s) will be used to correct the subtracted yield during LmSignal::Process().
  /// The procedures depend on which dimensions are kept after the projection, see comments in sourcecode.
  ///
  /// @param doScale Scale the normalization template (= MC sum) to match the data yield, done in the full phiV-range.
  /// @param doShift Shift the (maybe already scaled) norm. template to match the data yield in the normalization region.
  /// @param doShift Meant for correcting a residual difference in case of slightly mismatching shapes between data and MC,
  /// @param doShift but is unstable if shapes are too different, giving unreasonable results.

  // Sanity check, because this function is called from LmManager::Process() and from LmSignal::CalcSubtractedSignal():
  if ( !hSignal && (fEnable3DExclCut==kFlatCorrSub || fEnable3DExclCut==kFlatCorrSubAll || fEnable3DExclCut==kTemplSub) ) {
    LmHelper::Debug(Form(" CorrectForExclusionCutIn2D(): will correct subtracted yield during LmSignal::Process()."), 5-debugManager);
    return;
  }

  switch (fEnable3DExclCut) {

    case kFlatCorrUnsub: {
      LmHelper::Debug(Form(" CorrectForExclusionCutIn2D(): assume flat distribution of z dimension '%s' for unsubtracted yields.",LmBaseSignal::GetInputLabelZvar().Data()), 5-debugManager);
      for (Int_t i=0;i<fNpaircombs;i++) CorrectForExclusionCutFlat(fhMeePtee[i]);
      for (Int_t i=0;i<fNmixcombs;i++) CorrectForExclusionCutFlat(fhMixedMeePtee[i]);
      if (fhMixedMeePteeULS) CorrectForExclusionCutFlat(fhMixedMeePteeULS);
      break;
    }

    case kFlatCorrSubAll:
    case kFlatCorrSub: {
      LmHelper::Debug(Form(" CorrectForExclusionCutIn2D(): assume flat distribution of z dimension '%s' for subtracted yield.",LmBaseSignal::GetInputLabelZvar().Data()), 5-debugManager);
      CorrectForExclusionCutFlat(hSignal);
      break;
    }

    case kTemplSub: {
      LmHelper::Debug(Form(" CorrectForExclusionCutIn2D(): using template to correct subtracted yield."), 5-debugManager);

      /// ----------------------------------------------------------------------------------------------------
      /// We have to distinguish different cases depending on which dimensions the 2D projection contains.
      /// Changes & updates have to be implemented consistently for all cases!
      /// ----------------------------------------------------------------------------------------------------
      LmBaseSignal::inputAxis sigXaxisIs = LmBaseSignal::CheckWhichInputAxis( hSignal->GetXaxis() );
      LmBaseSignal::inputAxis sigYaxisIs = LmBaseSignal::CheckWhichInputAxis( hSignal->GetYaxis() );

      if (sigXaxisIs==LmBaseSignal::kInputX && sigYaxisIs==LmBaseSignal::kInputY) {
        /// ----- STEP 2 -----
        /// Default case: x and y stay the same, and the z-axis, in which the exclusion cut was done, was removed by the projection.
        /// Procedure: The contents of the yx-projection are modified based on output from running the xz-projection-correction.
        ///   The correction is only done up to the mass bin which is configured in this manager.
        ///   The relative bin errors are preserved. The phiV cut has to be applied to the data of this manager to
        ///   have the statistical uncertainties of the remaining data, not including the conversion peak.
        /// Preparation:
        ///  a) The correction (i.e. the phiV template fit) should be done in y-dim-slices (i.e. ptee) and the 1D
        ///     projections stored to files.
        ///  b) The slices are joined into a 2D signal.
        ///  c) The corrected 2D signal has to be given to the LmManager via AddCorrectedSig() before
        ///     LmSignal::Process() is called. Only then the LmManager::SignalPostCorrection(hSub) modifies the
        ///     subtracted yield before SoverB and Signif are computed from it.
        /// Example usage: a) in patrick.cpp PhiVstudy(), b)+c) in pat_sys.h ProcessOneInput().
        ///
        /// Note: Version which tries to do a blind phiV correction was commit e6d2c36ee00b4d47f86be82efa664f1f76de14dd
        ///   but it gave slightly inconsistent results. Therefore we have to use this 2-step procedure to be certain.

        if (!fhCorrectedSig) {
          LmHelper::Error(Form("LmManager::CorrectForExclusionCutIn2D(): corrected datapoints from STEP 1 of this procedure not available."));
          LmHelper::Error(Form("           ---> Run analysis with x=phiV, y=mee first (projoption=\"xz\"), then use AddCorrectedSig()."));
          LmHelper::Error(Form(" (This is needed for correct SoverB and Signif computation. Also, a blind phiV correction with templates was uncontrollable.)"));
          return;
        }

        Double_t bc_sig=0, be_rel=0, bc_corr=0;
        // loop over the input-x-axis (by default mee, so that's what we call its variables).
        Int_t meeFirst = LmBaseSignal::GetInputXaxis(hSignal)->GetFirst();
        Int_t meeLast  = LmBaseSignal::GetInputXaxis(hSignal)->GetLast();
        Int_t pteeFirst = LmBaseSignal::GetInputYaxis(hSignal)->GetFirst();
        Int_t pteeLast  = LmBaseSignal::GetInputYaxis(hSignal)->GetLast();
        for(Int_t imee = meeFirst; imee <= meeLast; ++imee){
          // Check up to which mass bin the correction is configured in this manager and break when it is exceeded.
          // Of course the upmost meaningful value is the one used for the first correction step (with x=phiV).
          Bool_t validCuts = Find3DExclusionValues(LmBaseSignal::GetInputXaxis(hSignal)->GetBinLowEdge(imee));
          if (!validCuts) break; // safety check and shortcut, if already above the last cut value.
          // loop over ptee
          for(Int_t iptee = pteeFirst; iptee <= pteeLast; ++iptee){
            bc_sig  = hSignal->GetBinContent(imee, iptee);
            be_rel  = hSignal->GetBinError(imee, iptee) / bc_sig;
            bc_corr = fhCorrectedSig->GetBinContent(imee, iptee);
            cout << "~+~ " << imee << "  " << iptee << " -> " << bc_corr << endl;
            bc_corr*= fhCorrectedSig->GetXaxis()->GetBinWidth(imee); // Undo binwidth normalization from original 1D histograms.
            bc_corr*= GetNeventsPhysSel(); // Scale to yield of current signal, which is not yet normalized per event.
            // to check one ptee-slice if needed:
            //if (iptee==2) cout << " [imee="<<imee<<",iptee="<<iptee<<"]: bc_sig = " << bc_sig << "  bc_corr = " << bc_corr << "  bc_sig/bc_corr = " << bc_sig/bc_corr << endl;
            hSignal->SetBinContent(imee, iptee, bc_corr);
            //hSignal->SetBinError(  imee, iptee, bc_corr * be_rel); // Preserve relative bin error.
            hSignal->SetBinError(  imee, iptee, 0.01); // Preserve relative bin error.
          }
        }
      }
      else if (sigXaxisIs==LmBaseSignal::kInputZ && sigYaxisIs==LmBaseSignal::kInputX) {
        /// ----- STEP 1 -----
        /// Special case: The exclusion cut correction shall be visualized by setting it as the x-axis.
        ///   The y-axis then has to be the input-x-axis, because the exclusion cut is usually limited to a small
        ///   region in x, e.g. low mass in case of phiV-cut, and this has to be considered for the correction.
        /// Procedure: The template is integrated over input-y (like the 2D-signal), then normalized to the data in
        ///   the accepted region, then the missing data points are recovered by using the template points.
        ///   Warning: This procedure mixes data with MC in one histogram, be sure not to present it as pure data!
        ///   In case of an additional normalization template, use yield from prompt template also in normalization
        ///   region, where we expect some oversubtraction from different conversions.
        ///
        /// Idea:
        /// We have constructed a "prompt template" which contains all desired signals and represents their shape.
        /// We have constructed a "normalization template" which contains all MC contributions that are expected
        /// to create the yield seen in data in the normalization region (which is not influenced by conversions).
        ///
        /// Simple case: Norm = Prompt
        /// Normalize the template to the data in the normalization region and recover the excluded data points
        /// with the points from the template.
        ///
        /// Harder Case: Norm = Prompt + Different Gamma
        /// Different Gamma is found to be negative in the normalization region in some (mee,ptee)-bins, so we
        /// know that our data contains a negative contribution, which we have to correct for: we replace all
        /// datapoints by the ones from the prompt template, but it has to be properly normalized before.
        ///
        /// Most reasonably, one would SCALE the normalization template to the data in the normalization region,
        /// then apply that same scaling to the prompt template and be done. But we observe that the scale factor
        /// may become very large (or negative) for a very small (or oversubtracted) template yield in the
        /// normalization region.
        /// So instead, we have to use the full phiv-range for a more stable normalization, which is now done:
        /// we match the MC to data by scaling it based on the full yield in each mee bin.
        /// The relative sizes of the MC templates are not modified, assumeing that the fraction prompt/diff_gamma
        /// is correct. This makes sense, physicswise, because prompt pi0 -> gamma+gamma causes conversions, and
        /// we can assume that the material budget is reasonably well described in MC.
        ///
        /// In addition/alternatively, one can SHIFT the normalization template to the data in the normalization region.
        /// If we shift the prompt template by that full amount, we assume that the diff_gamma-yield is correctly
        /// modelled by MC, independent of the prompt yield. But this contradicts the previous argument.
        ///
        /// It turns out that SCALING is good enough in most cases, so at the moment no shifting is applied.
        /// You can change this for testing purposes in LmManager::SignalPostCorrection() or implement a setter...

        if (fhExclusionZTemplates.size()==0) {
          LmHelper::Error(Form("LmManager::CorrectForExclusionCutIn2D(): no template given. Skip correction of signal '%s'.", hSignal->GetName()));
          return;
        }

        LmHelper::Warning(Form("LmManager::CorrectForExclusionCutIn2D(): some of the datapoints in the histogram '%s' will not be datapoints anymore, but MC points!",hSignal->GetName()));

        // bunch of needed variables
        Double_t yieldData_full(0), yieldTemplNorm_full(0); // yields in full region.
        Double_t yieldData_norm(0), yieldTemplNorm_norm(0), yieldTemplPrompt_norm(1), yieldTemplPromptPF_norm(1); // yields in normalization region.
        Double_t yieldTemplNorm_bin(0), yieldTemplNorm_err(0), yieldTemplPrompt_bin(0), yieldTemplPrompt_err(0); // yields in given data bin.
        Int_t templ_phivBin1, templ_phivBin2, templ_meeBin1, templ_meeBin2;
        Int_t templ_phivBin1_norm, templ_phivBin2_norm, data_phivBin1_norm, data_phivBin2_norm;
        Double_t phiv_low(-1), phiv_up(-1), mee_low(-1), mee_up(-1);

        // Select template histogram(s)
        TH3D* h3DTemplPrompt   = fhExclusionZTemplates[0];
        TH3D* h3DTemplNorm     = h3DTemplPrompt; // per default, the prompt template will be used itself for normalization to the data.
        TH3D* h3DTemplPromptPF = 0x0;
        // ... but other options are possible to change the normalization and/or correction behaviour:
        for (UInt_t i=1; i<fhExclusionZTemplates.size(); i++) {
          /// If an additional normalization template is given, then it will be used for that purpose.
          if (TString(fhExclusionZTemplates[i]->GetName()).EqualTo("hNorm")) {
            h3DTemplNorm = fhExclusionZTemplates[i];
          }
          /// If an additional prompt template (with prefilter) is given, then it is assumed that the first one is
          /// unfiltered and an additional scaling needs to be applied (bin by bin) to account for the "prefilter efficiency".
          if (   TString(fhExclusionZTemplates[i]->GetName()).EqualTo("hSigPF")
              || TString(fhExclusionZTemplates[i]->GetName()).EqualTo("hPromptPF") ) {
            h3DTemplPromptPF = fhExclusionZTemplates[i];
          }
        }

        // Select template histogram(s), depending on which 3D templates are available (see above), and project them into 2D.
        TH2D* h2DTemplPrompt   = static_cast<TH2D*> (h3DTemplPrompt->Project3D(fsProjOption));
        TH2D* h2DTemplNorm     = h2DTemplPrompt; // per default, the prompt template will be used itself for normalization to the data.
        TH2D* h2DTemplPromptPF = 0x0;
        h2DTemplPrompt->GetZaxis()->SetTitle(LmBaseSignal::GetProjLabelContent().Data());
        if (h3DTemplNorm!=h3DTemplPrompt) { // ... but if an additional 3D template exists, this will be used instead.
          h2DTemplNorm = static_cast<TH2D*> (h3DTemplNorm->Project3D(fsProjOption));
          h2DTemplNorm->GetZaxis()->SetTitle(LmBaseSignal::GetProjLabelContent().Data());
        }
        if (h3DTemplPromptPF) {
          h2DTemplPromptPF = static_cast<TH2D*> (h3DTemplPromptPF->Project3D(fsProjOption));
          h2DTemplPromptPF->GetZaxis()->SetTitle(LmBaseSignal::GetProjLabelContent().Data());
        }
        // --------------------------------------------------
        // If any re-normalization (scaling) of templates is done, make sure to undo it at the end of the loop!
        // Whenever possible, just use any needed correction factors in hSignal->SetBinContent/Error().
        // --------------------------------------------------
 
        // Create histograms to visualize the correction procedure later.
        // They are added to the vector 'fhVisualSig' as needed.
        TH2D* hVisualNorm = (TH2D*) hSignal->Clone("hVisualNorm"); hVisualNorm->Reset(); // binning of hSignal
        TH2D* hVisualNormShif = (TH2D*) hSignal->Clone("hVisualNormShif"); hVisualNormShif->Reset(); // binning of hSignal

        // loop over the input-x-axis (by default mee, so that's what we call its variables).
        // use the function 'LmBaseSignal::GetInputXaxis()' instead of GetYaxis() to be more generic and avoid confusion (hopefully).
        Int_t meeFirst = LmBaseSignal::GetInputXaxis(hSignal)->GetFirst();
        Int_t meeLast  = LmBaseSignal::GetInputXaxis(hSignal)->GetLast();
        Int_t phivFirst = LmBaseSignal::GetInputZaxis(hSignal)->GetFirst();
        Int_t phivLast  = LmBaseSignal::GetInputZaxis(hSignal)->GetLast();
        for(Int_t imee = meeFirst; imee <= meeLast; ++imee){
          Bool_t validCuts = Find3DExclusionValues(LmBaseSignal::GetInputXaxis(hSignal)->GetBinLowEdge(imee));
          if (!validCuts) break; // safety check and shortcut, if already above the last cut value.
          mee_low = LmBaseSignal::GetInputXaxis(hSignal)->GetBinLowEdge(imee);
          mee_up  = LmBaseSignal::GetInputXaxis(hSignal)->GetBinUpEdge(imee);
          templ_meeBin1 = LmBaseSignal::GetInputXaxis(h2DTemplPrompt)->FindBin(mee_low);
          templ_meeBin2 = LmBaseSignal::GetInputXaxis(h2DTemplPrompt)->FindBin(mee_up-LmHelper::kSmallDelta);
          templ_phivBin1_norm = LmBaseSignal::GetInputZaxis(h2DTemplPrompt)->FindBin(fTemplNormMin);
          templ_phivBin2_norm = LmBaseSignal::GetInputZaxis(h2DTemplPrompt)->FindBin(fTemplNormMax-LmHelper::kSmallDelta);
          data_phivBin1_norm  = LmBaseSignal::GetInputZaxis(hSignal)->FindBin(fTemplNormMin);
          data_phivBin2_norm  = LmBaseSignal::GetInputZaxis(hSignal)->FindBin(fTemplNormMax-LmHelper::kSmallDelta);

          /// Scale the templates to data based on the full phiV range, which is hopefully stable.
          /// Need the subtracted data without explicit phiV cut (but consistent prefilter), otherwise we have
          /// non-zero yield only in the normalization region, which turned out to be unstable in most cases.
          Bool_t hasUncutData = (fhVisualSig.size()>0 && TString(fhVisualSig[0]->GetName()).Contains("hDataOrig"));
          Bool_t recoverUncutData=kFALSE;
          Bool_t doUnscale=kFALSE;
          Double_t mcOverestimate=1;
          if (doScale) {
            if (hasUncutData && (h2DTemplNorm!=h2DTemplPrompt)) {
              yieldData_full      = fhVisualSig[0]->Integral(phivFirst, phivLast, imee, imee);
              yieldTemplNorm_full = h2DTemplNorm->Integral(LmBaseSignal::GetInputZaxis(h2DTemplNorm)->GetFirst(),
                                                           LmBaseSignal::GetInputZaxis(h2DTemplNorm)->GetLast(),
                                                           templ_meeBin1, templ_meeBin2);
            } else { // fallback, if uncut data or normalization histogram is not available:
              // Use only the normalization region for scaling - which is expected to be unstable!
              LmHelper::Warning("LmManager::CorrectForExclusionCutIn2D(): provide subtracted data without explicit phiV cut (but consistent prefilter) via AddVisualSig().");
              yieldData_full      = hSignal->Integral(data_phivBin1_norm, data_phivBin2_norm, imee, imee);
              yieldTemplNorm_full = h2DTemplNorm->Integral(templ_phivBin1_norm, templ_phivBin2_norm, templ_meeBin1, templ_meeBin2);
            }
            if (yieldTemplNorm_full<=0) {
              LmHelper::Warning(Form("LmManager::CorrectForExclusionCutIn2D(): integrated template yield <= 0 for bin at mee=[%.3f,%.3f].", mee_low, mee_up));
              recoverUncutData=kTRUE;
            }
            if (yieldData_full<=0) {
              LmHelper::Warning(Form("LmManager::CorrectForExclusionCutIn2D(): integrated data yield <= 0 for bin at mee=[%.3f,%.3f].", mee_low, mee_up));
              recoverUncutData=kTRUE;
            }
            if (recoverUncutData) {
              if (hasUncutData) {
                LmHelper::Info( Form("   ... Recovering uncut data from the provided VisualSig[0] for this bin."));
              } else {
                LmHelper::Error(Form("   ... This bin will be wrong! Provide subtracted data without explicit phiV cut (but consistent prefilter) via AddVisualSig() or change phiV cut window to exclude this bin."));
                continue;
              }
            }
            mcOverestimate = (yieldTemplNorm_full>0&&yieldData_full>0) ? (yieldTemplNorm_full*GetNeventsPhysSel()/yieldData_full) : 1;
            if ( TMath::Abs(mcOverestimate-1) > 0.01) { // do scaling if the deviation is more than 1%.
              LmHelper::Debug(Form(" scaling MC templates by 1./%.2f to match data yield in bin at mee=[%.3f,%.3f].", mcOverestimate, mee_low, mee_up), 6-debugManager);
              //LmHelper::Debug(Form(" yieldData_full/nevents = %.2e, yieldTemplNorm_full = %.2e.", yieldData_full/GetNeventsPhysSel(), yieldTemplNorm_full), 6-debugManager);
              ////hVisualNorm->SetTitle(Form("MC sum norm. (#times 1/%.2f)", mcOverestimate)); // this makes no sense, because the value is different for each mee bin.
              doUnscale=kTRUE;
              // --- always synchronize with the unscale block further below! ---
              h2DTemplPrompt->Scale(1./mcOverestimate);
              if (h2DTemplNorm!=h2DTemplPrompt) h2DTemplNorm->Scale(1./mcOverestimate);
              if (h2DTemplPromptPF) h2DTemplPromptPF->Scale(1./mcOverestimate);
              // --- always synchronize with the unscale block further below! ---
            }
          }

          /// Compute the difference between the original data and the normalization template.
          /// The number of data bins in the normalization region has to be taken into account.
          Int_t nDataBins_norm = data_phivBin2_norm - data_phivBin1_norm + 1;
          Double_t diffPerDataBin = 0;
          if (doShift) {
            yieldData_norm      = hSignal->Integral(data_phivBin1_norm, data_phivBin2_norm, imee, imee);
            yieldTemplNorm_norm = h2DTemplNorm->Integral(templ_phivBin1_norm, templ_phivBin2_norm, templ_meeBin1, templ_meeBin2);
            diffPerDataBin      = (yieldData_norm - yieldTemplNorm_norm*GetNeventsPhysSel()) / nDataBins_norm;
            LmHelper::Debug(Form(" shifting MC templates by %+.2e (1/event) to match data yield in normalization region in bin at mee=[%.3f,%.3f].",
                                 diffPerDataBin/GetNeventsPhysSel(), mee_low, mee_up), 6-debugManager);
            //hVisualNormShif->SetTitle(Form("MC shifted (%+.2e)", diffPerDataBin/GetNeventsPhysSel())); // this makes no sense, because the value is different for each mee bin.
          }

          if (h2DTemplPromptPF!=0x0) {
            /// --------------------------------------------------
            /// When using a prefilter, we may need an unfiltered prompt template to cover the full phasespace, as well
            /// as a filtered prompt template to combine consistently with further templates, like from different gamma.
            /// In that case, the factor between both prompt templates is needed to account for random rejection.
            /// --------------------------------------------------
            yieldTemplPrompt_norm   = 1;
            yieldTemplPromptPF_norm = 1;
            yieldTemplPrompt_norm   = h2DTemplPrompt->Integral(templ_phivBin1_norm, templ_phivBin2_norm, templ_meeBin1, templ_meeBin2);
            yieldTemplPromptPF_norm = h2DTemplPromptPF->Integral(templ_phivBin1_norm, templ_phivBin2_norm, templ_meeBin1, templ_meeBin2);
            if (yieldTemplPrompt_norm==0) { yieldTemplPrompt_norm=1; yieldTemplPromptPF_norm=1; } // avoid nan during division.
            LmHelper::Debug(Form(" using unfiltered prompt template, scaled by %.2f to account for random rejection.", yieldTemplPromptPF_norm/yieldTemplPrompt_norm), 6-debugManager);
          }

          // loop over phiV-axis.
          for(Int_t iphiv = phivFirst; iphiv <= phivLast; ++iphiv){
            if (recoverUncutData) {
              hSignal->SetBinContent(iphiv,imee, fhVisualSig[0]->GetBinContent(iphiv,imee));
              hSignal->SetBinError  (iphiv,imee, fhVisualSig[0]->GetBinError(iphiv,imee));
              continue;
            }
            phiv_low = LmBaseSignal::GetInputZaxis(hSignal)->GetBinLowEdge(iphiv);
            phiv_up  = LmBaseSignal::GetInputZaxis(hSignal)->GetBinUpEdge(iphiv);

            /// --------------------------------------------------
            /// If only one template is given, then skip modification inside normalization region, otherwise modify the whole range.
            /// --------------------------------------------------
            if ( h2DTemplNorm==h2DTemplPrompt && !InExclusionCutRegion(phiv_low, phiv_up) ) continue;
            templ_phivBin1 = LmBaseSignal::GetInputZaxis(h2DTemplPrompt)->FindBin(phiv_low);
            templ_phivBin2 = LmBaseSignal::GetInputZaxis(h2DTemplPrompt)->FindBin(phiv_up-LmHelper::kSmallDelta);

            /// Compute the corrected yield and its relative error.
            /// The error is tricky, keeping in mind how to correct the final spectrum where phiV does not show up.
            /// The data contains unwanted yield in mee-bins where the cut shall be applied, on the other hand it
            /// contains empty phiV-bins, if for example a phiV-prefilter was used.
            /// For the moment, we just take the relative error of the template, which is also not correct...

            /// Compute the prompt template yield in the current data bin.
            yieldTemplPrompt_bin = 0;
            yieldTemplPrompt_err = 0;
            yieldTemplPrompt_bin = h2DTemplPrompt->IntegralAndError(templ_phivBin1, templ_phivBin2, templ_meeBin1, templ_meeBin2, yieldTemplPrompt_err);
            if (yieldTemplPrompt_bin!=0) yieldTemplPrompt_err /= yieldTemplPrompt_bin; // compute relative error.
            yieldTemplPrompt_bin *= GetNeventsPhysSel(); // normalize template yield to data events.
            yieldTemplPrompt_bin *= yieldTemplPromptPF_norm/yieldTemplPrompt_norm; // account for random rejection when using two prompt templates.
            /// At this point 'yieldTemplPrompt_bin' has the value of the (prefiltered) prompt template in that bin.
            /// Now add the difference between the data and the normalization template, thereby using the measured
            /// yield to set the absolute scale, rather than the MC yield.
            yieldTemplPrompt_bin += diffPerDataBin;

            // Fill some histograms for visualization.
            // normalization template:
            yieldTemplNorm_bin = 0;
            yieldTemplNorm_err = 0;
            yieldTemplNorm_bin = h2DTemplNorm->IntegralAndError(templ_phivBin1, templ_phivBin2, templ_meeBin1, templ_meeBin2, yieldTemplNorm_err);
            if (yieldTemplNorm_bin!=0) yieldTemplNorm_err /= yieldTemplNorm_bin; // compute relative error.
            yieldTemplNorm_bin *= GetNeventsPhysSel(); // normalize template yield to data events.
            hVisualNorm->SetBinContent(iphiv,imee, yieldTemplNorm_bin);
            hVisualNorm->SetBinError  (iphiv,imee, yieldTemplNorm_bin*yieldTemplNorm_err);
            // normalization template shifted to data:
            if (yieldTemplNorm_bin!=0) yieldTemplNorm_bin += diffPerDataBin; // keep empty bins empty, which looks better.
            hVisualNormShif->SetBinContent(iphiv,imee, yieldTemplNorm_bin);
            hVisualNormShif->SetBinError  (iphiv,imee, yieldTemplNorm_bin*yieldTemplNorm_err);

            // Set bin content and error (@TODO: think about error again...):
            hSignal->SetBinContent(iphiv,imee, yieldTemplPrompt_bin);
            hSignal->SetBinError  (iphiv,imee, yieldTemplPrompt_bin*yieldTemplPrompt_err); // preserve relative error
            hSignal->SetBinError  (iphiv,imee, 0); // preserve relative error
          } // phiV loop

          if (doUnscale) {
            h2DTemplPrompt->Scale(mcOverestimate);
            if (h2DTemplNorm!=h2DTemplPrompt) h2DTemplNorm->Scale(mcOverestimate);
            if (h2DTemplPromptPF) h2DTemplPromptPF->Scale(mcOverestimate);
          }

        } // mee loop

        if (doScale) {
          AddVisualSig(hVisualNorm, "hVisNorm", "MC sum norm.");
          if (doShift) AddVisualSig(hVisualNormShif, "hVisNormShif", "MC sum norm. shifted");
        } else {
          if (doShift) AddVisualSig(hVisualNormShif, "hVisNormShif", "MC sum shifted");
          else         AddVisualSig(hVisualNormShif, "hVisNormShif", "MC sum");
        }
        delete hVisualNorm;
        delete hVisualNormShif;
      }
      else {
        LmHelper::Error(Form("LmManager::CorrectForExclusionCutIn2D(): correction not implemented for 2D-signal with x=%s and y=%s. Refer to sourcecode.",LmBaseSignal::GetInputAxisCode(sigXaxisIs).Data(),LmBaseSignal::GetInputAxisCode(sigYaxisIs).Data()));
        return;
      }

      break;
    }
    default:
      break;
  }
}

//_______________________________________________________________________________________________
void LmManager::CorrectForExclusionCutFlat(TH2D* hSignal)
{
  /// Internally used by CorrectForExclusionCutIn2D().
  if (!fhXdimYdimZdim[0]) {
    LmHelper::Error(Form("LmManager::CorrectForExclusionCutFlat(): correction not possible if 3D input not available to determine z-axis range."));
    return;
  }
  if (!fsProjOption.Contains("x", TString::kIgnoreCase)) {
    LmHelper::Error(Form("LmManager::CorrectForExclusionCutFlat(): correction not implemented for 2D-signal which does not contain the input-x-axis (per default mee)."));
    return;
  }

  Double_t zRange_full, zRange_cut, phiv_low, phiv_up;
  Int_t    phivBin1_norm, phivBin2_norm, nPhivBins_norm;
  Double_t yieldData_norm;

  zRange_full = (  fhXdimYdimZdim[0]->GetZaxis()->GetBinUpEdge(fhXdimYdimZdim[0]->GetZaxis()->GetLast())
                 - fhXdimYdimZdim[0]->GetZaxis()->GetBinLowEdge(fhXdimYdimZdim[0]->GetZaxis()->GetFirst()) );

  // loop over the input-x-axis (by default mee, so that's what we call its variables).
  // it will be used as x- or y-bin counter depending on the selected projection option.
  Int_t meeFirst = LmBaseSignal::GetInputXaxis(hSignal)->GetFirst();
  Int_t meeLast  = LmBaseSignal::GetInputXaxis(hSignal)->GetLast();
  for(Int_t imee = meeFirst; imee <= meeLast; ++imee){
    Bool_t validCuts = Find3DExclusionValues(LmBaseSignal::GetInputXaxis(hSignal)->GetBinLowEdge(imee));
    if (!validCuts) break; // safety check and shortcut, if already above the last cut value.
    zRange_cut = fCutValZabove-fCutValZbelow;

    /// ----------------------------------------------------------------------------------------------------
    /// We have to distinguish different cases depending on which dimensions the 2D projection contains.
    /// Changes & updates have to be implemented consistently for all cases!
    /// ----------------------------------------------------------------------------------------------------
    if (fsProjOption.EqualTo("yx", TString::kIgnoreCase)) { // x=mee, y=ptee (default)
      // Scale up each bin by the missing phase space fraction.
      for(Int_t iptee = 1; iptee <= LmBaseSignal::GetInputYaxis(hSignal)->GetNbins(); ++iptee){
        hSignal->SetBinContent(imee, iptee, hSignal->GetBinContent(imee,iptee)*zRange_full/zRange_cut);
        hSignal->SetBinError  (imee, iptee, hSignal->GetBinError  (imee,iptee)*zRange_full/zRange_cut);
      }
    }
    else if (fsProjOption.EqualTo("xz", TString::kIgnoreCase)) { // x=phiV, y=mee
      // Compute yield in the normalization region (which is usually all remaining yield) and fill each bin of the
      // exclusion region with the average yield per bin.
      phivBin1_norm  = LmBaseSignal::GetInputZaxis(hSignal)->FindBin(fTemplNormMin);
      phivBin2_norm  = LmBaseSignal::GetInputZaxis(hSignal)->FindBin(fTemplNormMax-LmHelper::kSmallDelta);
      nPhivBins_norm = phivBin2_norm - phivBin1_norm + 1;
      yieldData_norm = hSignal->Integral(phivBin1_norm, phivBin2_norm, imee, imee);

      for(Int_t iphiv = 1; iphiv <= LmBaseSignal::GetInputZaxis(hSignal)->GetNbins(); ++iphiv){
        phiv_low = LmBaseSignal::GetInputZaxis(hSignal)->GetBinLowEdge(iphiv);
        phiv_up  = LmBaseSignal::GetInputZaxis(hSignal)->GetBinUpEdge(iphiv);
        if (fEnable3DExclCut==kFlatCorrSubAll && !InExclusionCutRegion(phiv_low, phiv_up)) {
          hSignal->SetBinContent(iphiv, imee, yieldData_norm/nPhivBins_norm); // set all datapoints to average.
          // keep original bin errors (assuming a flatish distribution), instead of redistributing them.
        }
        if (!InExclusionCutRegion(phiv_low, phiv_up)) continue;
        // NOTE: for this we assume uniform binning!
        hSignal->SetBinContent(iphiv, imee, yieldData_norm/nPhivBins_norm);
        hSignal->SetBinError  (iphiv, imee, 0);
      }
    }
    else break; // should never reach here.
  }
}


//_______________________________________________________________________________________________
void LmManager::GetHistogramsFromFiles2D()
{
  LmHelper::Debug(" GetHistogramsFromFiles2D()", 5-debugManager);

  TObjArray* oaPairCombNames = fPairCombNames.Tokenize(";");
  TObjArray* oaMixCombNames  = fMixCombNames.Tokenize(";");
  //const Char_t *PairCombNames[] = {"Pair_ev1+_ev1-","Pair_ev1+_ev1+","Pair_ev1-_ev1-"};
  //const Char_t *MixCombNames[] = {"Pair_ev1-_ev2+","Pair_ev1+_ev2+","Pair_ev1-_ev2-","Pair_ev1+_ev2-"};
  //Color_t *PairCombColors[fNpaircombs] = {kBlack,kBlue,kRed};

  // resize vectors to have space for histograms
  // (using '.reserve' doesnt change the vector size so the '.size' command still returns 0):
  fhMeePtee.resize(fNpaircombs);
  fhMixedMeePtee.resize(fNmixcombs);

  //cout << "READING OF TRACK ROTATION IS " <<( (fEnableTR)?"":"NOT ") << "ENABLED " << endl;
  //--------------------------------------------
  //Get 2D mee-pt histograms for all periods
  //
  // the code for reading in multiple periods was inherited from Christoph, but should be checked if actually used again with more than 1 period.
  //
  TH2D* hMeePteePeriod[fNperiodsMAX][fNpaircombs];
  TH2D* hMixedMeePteePeriod[fNperiodsMAX][fNmixcombs];
  TH2D* hRotatedInvMassPtPeriod[fNperiodsMAX];

  LmHelper::Debug(Form("  read in nEvents and pair histograms named: %s", fsInputhists.Data()), 10);
  Double_t nEventsThisCut=0;
  for (int j=0; j < fNperiods; j++) {
    //    TCollection* fCutfolder;
    TCollection* histFolderTemp;
    TCollection* histFolderPair[fNpaircombs];
    TCollection* histFolderMix[fNmixcombs];

    //Get nEvents for this Cut
    // Folder with histogram class "Event" (Hashlists)
    histFolderTemp = (TCollection*) fCutfolder->FindObject("Event");
    TH1D* hNevents = (TH1D*) histFolderTemp->FindObject("nEvents");
    nEventsThisCut+=hNevents->GetBinContent(1); //After PhysicsSelection

    for (Int_t i=0;i<fNpaircombs;i++) {
      LmHelper::Debug(Form(" %s",oaPairCombNames->At(i)->GetName()), 10);
      histFolderPair[i] = (TCollection*) fCutfolder->FindObject(oaPairCombNames->At(i)->GetName());
      if (!histFolderPair[i]) {
        LmHelper::Error(Form("LmManager::GetHistogramsFromFiles2D(): no pair histogram folder '%s' available.", oaPairCombNames->At(i)->GetName()));
      }
      hMeePteePeriod[j][i] = (TH2D*) histFolderPair[i]->FindObject(fsInputhists.Data());
    }
    for (Int_t i=0;i<fNmixcombs;i++) {
      LmHelper::Debug(Form(" %s",oaMixCombNames->At(i)->GetName()), 10);
      histFolderMix[i] = (TCollection*) fCutfolder->FindObject(oaMixCombNames->At(i)->GetName());
      if (!histFolderMix[i]) {
        LmHelper::Warning("LmManager::GetHistogramsFromFiles2D(): no mixed event histograms available.");
        fNmixcombs=0;
        break;
      }
      hMixedMeePteePeriod[j][i] = (TH2D*) histFolderMix[i]->FindObject(fsInputhists.Data());
    }
    if (fEnableTR) hRotatedInvMassPtPeriod[j] = (TH2D*) fCutfolder->FindObject("Pair_ev1+_ev1-_TR")->FindObject(fsInputhists.Data());
  }

  fNeventsPhysSel=nEventsThisCut; //After PhysicsSelection
  LmHelper::Debug(Form("  fNeventsPhysSel = %f", fNeventsPhysSel), 10);

  //-----------------------------------------------------
  //Add 2d Histograms of all periods
  for (int j=0; j < fNperiods; j++) {
    for (Int_t i=0;i<fNpaircombs;i++) {
      if (j==0) {
        fhMeePtee[i] = new TH2D(*(hMeePteePeriod[j][i])); //(TH2D*) hMeePteePeriod[j][i]->Clone();
      }
      else {
        fhMeePtee[i]->Add(hMeePteePeriod[j][i]);
      }
    }
    for (Int_t i=0;i<fNmixcombs;i++) {
      if (j==0) {
        fhMixedMeePtee[i] = new TH2D(*(hMixedMeePteePeriod[j][i])); //(TH2D*) hMixedMeePteePeriod[j][i]->Clone();
      }
      else {
        fhMixedMeePtee[i]->Add(hMixedMeePteePeriod[j][i]);
      }
    }

    if (j==0) {
      if (fEnableTR){
        fhRotatedInvMassPt = new TH2D(*(hRotatedInvMassPtPeriod[j])); //(TH2D*) hRotatedInvMassPtPeriod[j]->Clone("fhRotatedInvMassPt");
        fhRotatedInvMassPt->SetName("fhRotatedInvMassPt");
      }
    }
    else {
      if (fEnableTR) fhRotatedInvMassPt->Add(hRotatedInvMassPtPeriod[j]);
    }

  }

  TString sHistName = fsInputhists;

  for (Int_t i=0;i<fNpaircombs;i++) {
    fhMeePtee[i]->SetName(Form("%s_%d",sHistName.Data(),i)); // in 3D case this is mandatory, not sure here, but shouldn't hurt.
    SetTitlesInputhist(fhMeePtee[i]);
    //fhMeePtee[i]->SetTitle(Form("%s;%s;%s;%s",fhMeePtee[i]->GetName(),LmBaseSignal::GetProjLabelX().Data(),LmBaseSignal::GetProjLabelY().Data(),LmBaseSignal::GetProjLabelContent().Data()));
    //warning: the functions LmBaseSignal::GetInputLabelX()Y/Z sometimes interact in a fancy way when called within one form statement. may want to use some casts to fix this somehow.
  }
  for (Int_t i=0;i<fNmixcombs;i++) {
    fhMixedMeePtee[i]->SetName(Form("%s_Mix%d",sHistName.Data(),i));
    SetTitlesInputhist(fhMixedMeePtee[i]);
  }
  if (HasMixedEvent()) { // create sum of mixed event ULS +- and -+ for function GetUnlikeMix().
    if (fhMixedMeePteeULS) delete fhMixedMeePteeULS;
    fhMixedMeePteeULS = new TH2D(*fhMixedMeePtee[0]);
    fhMixedMeePteeULS->Add(fhMixedMeePtee[3]);
    fhMixedMeePteeULS->SetName(Form("%s_MixULS",sHistName.Data()));
  }

//  TH2D* hist = fhMeePtee[0];
//  LmHelper::Debug(" LmManager::GetHistogramsFromFiles2D()", 3);
//  LmHelper::Debug(Form(" |-> title: %s,   x: %s,   y: %s,   z: %s", hist->GetTitle(), hist->GetXaxis()->GetTitle(), hist->GetYaxis()->GetTitle(), hist->GetZaxis()->GetTitle()), 3);

}


//_______________________________________________________________________________________________
void LmManager::Print2DUnlike(const Char_t* filename){
  PrintTH2(GetUnlike(), filename);
  return;
}

void LmManager::Print2DLikePP(const Char_t* filename){
  PrintTH2(GetLikePP(), filename);
  return;
}

void LmManager::Print2DLikeMM(const Char_t* filename){
  PrintTH2(GetLikeMM(), filename);
  return;
}

void LmManager::Print2DLikePPMix(const Char_t* filename){
  PrintTH2(GetLikePPMix(), filename);
  return;
}

void LmManager::Print2DLikeMMMix(const Char_t* filename){
  PrintTH2(GetLikeMMMix(), filename);
  return;
}

void LmManager::Print2DUnlikeMix(const Char_t* filename){
  PrintTH2(GetUnlikeMix(), filename);
  return;
}

void LmManager::Print2DEffi(const Char_t* filename){
  if (!fEnableEffiCorr) return;
  PrintTH2(GetEffi(), filename);
  return;
}


//_______________________________________________________________________________________________
void LmManager::SetTitlesInputhist(TH1* hist) {
//  LmHelper::Debug(" LmManager::SetTitlesInputhist()", 3);
  hist->SetTitle(hist->GetName());
  hist->SetXTitle(LmBaseSignal::GetInputLabelX().Data());
  hist->SetYTitle(LmBaseSignal::GetInputLabelY().Data());
  if ( hist->IsA()==TH3F::Class() || hist->IsA()==TH3D::Class() ) {
    if (LmBaseSignal::GetInputLabelZvar().IsNull()) {
      LmHelper::Warning(Form("LmManager::SetTitlesInputhist(): histogram is 3D but Z-axis label unset! Please set via LmBaseSignal::SetInputLabelZ(const char* var, const char* unit) in your <user>.cpp"));
    } else {
      hist->SetZTitle(LmBaseSignal::GetInputLabelZ().Data());
    }
  }
//  LmHelper::Debug(Form(" |-> title: %s,   x: %s,   y: %s,   z: %s", hist->GetTitle(), hist->GetXaxis()->GetTitle(), hist->GetYaxis()->GetTitle(), hist->GetZaxis()->GetTitle()), 3);
}


//_______________________________________________________________________________________________
void LmManager::CalcEffi()
{
  LmHelper::Debug(" CalcEffi()", 5-debugManager);

  if (!fhEffiRec || !fhEffiGen) {
    LmHelper::Error(Form("LmManager::CalcEffi(): histograms for efficiency not available."));
    SetEnableEffiCorr(kFALSE);
    return;
  }

  if (fhEffi) delete fhEffi;
  fhEffi = new TH2D(*fhEffiRec);
  fhEffi->SetName("fhEffi");
  fhEffi->Divide(fhEffiGen);
  for (Int_t i = 0; i <= (fhEffi->GetNbinsX()*fhEffi->GetNbinsY()); ++i){
    fhEffi->SetBinError(i, 0);
  }
  return;
}

//_______________________________________________________________________________________________
void LmManager::CalcEtaRange()
{
  Int_t eta_bin = -1;
  TCollection* histFolderTemp = 0x0;
  histFolderTemp = (TCollection*) fCutfolder->FindObject("Track_ev1-");
  if (histFolderTemp->FindObject("Eta") != 0)  {
    TH1D* hEtaRange = (TH1D*) histFolderTemp->FindObject("Eta");
    eta_bin = hEtaRange->FindFirstBinAbove(0); //first bin with entries
    feta_range_min = hEtaRange->GetBinLowEdge(eta_bin);
    eta_bin = hEtaRange->FindLastBinAbove(0); //last bin with entries
    feta_range_max = hEtaRange->GetBinLowEdge(eta_bin+1);
  }
  else if (histFolderTemp->FindObject("Eta_Phi") != 0) {
    TH2D* hEta_Phi = (TH2D*) histFolderTemp->FindObject("Eta_Phi");
    TH1D* hEtaRange = (TH1D*) hEta_Phi->ProjectionX();
    eta_bin = hEtaRange->FindFirstBinAbove(0); //first bin with entries
    feta_range_min = hEtaRange->GetBinLowEdge(eta_bin);
    eta_bin = hEtaRange->FindLastBinAbove(0); //last bin with entries
    feta_range_max = hEtaRange->GetBinLowEdge(eta_bin+1);
  }
}

//_______________________________________________________________________________________________
void LmManager::CalcPtRange()
{
  Int_t pt_bin = -1;
  TCollection* histFolderTemp;
  histFolderTemp = (TCollection*) fCutfolder->FindObject("Track_ev1+");
  if (histFolderTemp->FindObject("Pt") != 0){
    TH1D* hPtRange = (TH1D*) histFolderTemp->FindObject("Pt");
    pt_bin = hPtRange->FindFirstBinAbove(0); //first bin with entries
    fpt_range_min = hPtRange->GetBinLowEdge(pt_bin);
    pt_bin = hPtRange->FindLastBinAbove(0); //last bin with entries
    fpt_range_max = hPtRange->GetBinLowEdge(pt_bin+1);
  }
}

//_______________________________________________________________________________________________
void LmManager::CalcCentrality(){
  Int_t centrality_range_bin = -1;
  TCollection* histFolderTemp;
  histFolderTemp = (TCollection*) fCutfolder->FindObject("Event");
  // check if there is a centrality histogram. pPb + pp dont have one
  if (histFolderTemp->FindObject("centrality") == 0){
    fcentrality_min = -1;
    fcentrality_max = -1;
  }
  else {
    TH1D* hCentralityRange = (TH1D*) histFolderTemp->FindObject("centrality");
    centrality_range_bin = hCentralityRange->FindFirstBinAbove(0); //First bin with entries
    fcentrality_min = hCentralityRange->GetBinLowEdge(centrality_range_bin);
    centrality_range_bin = hCentralityRange->FindLastBinAbove(0); //last bin with entries
    fcentrality_max = hCentralityRange->GetBinLowEdge(centrality_range_bin+1);
  }
}

//_______________________________________________________________________________________________
void LmManager::CalcOpeningAngle(){
  Int_t thetaEE_bin = -1;
  TCollection* histFolderTemp;
  histFolderTemp = (TCollection*) fCutfolder->FindObject("Pair_ev1+_ev1-");
  if (histFolderTemp->FindObject("pOpeningAngle") != 0){
    TH1D* hThetaEE = (TH1D*) histFolderTemp->FindObject("pOpeningAngle");
    thetaEE_bin = hThetaEE->FindFirstBinAbove(0); //First bin with entries
    fThetaEE_min = hThetaEE->GetBinLowEdge(thetaEE_bin);
  }
}

//_______________________________________________________________________________________________
void LmManager::Rebin2DHistogram_all()
{
  /// Rebin all 2D histograms according to binning given by LmRebinner::SetRebinning2D()/SetRebinningX()/SetRebinningY().
  /// Uses function LmRebinner::Rebin2DHistogram().
  LmHelper::Debug(" LmManager::Rebin2DHistogram_all()", 5);

  Rebin2DHistogram(*(GetUnlike()));
  Rebin2DHistogram(*GetLikePP());
  Rebin2DHistogram(*GetLikeMM());
  //LmHelper::Debug(Form("  rebin mixed-event"), 7);
  if (HasMixedEvent()) {
    Rebin2DHistogram(*GetLikePPMix());
    Rebin2DHistogram(*GetLikeMMMix());
    Rebin2DHistogram(*GetUnlikePPMix());
    Rebin2DHistogram(*GetUnlikeMMMix());
    Rebin2DHistogram(*GetUnlikeMix());
  }
  if (fEnableEffiCorr) {
    LmHelper::Debug(Form("  rebin Effi gen"), 7);
    Rebin2DHistogram(*fhEffiGen);
    LmHelper::Debug(Form("  rebin Effi reco"), 7);
    Rebin2DHistogram(*fhEffiRec);
  }
  return;
}


//_______________________________________________________________________________________________
void LmManager::ApplyEfficiency2D(TH2D& hIn, const TH2D* hEffi)
{
  //LmHelper::Debug(Form(" ApplyEfficiency2D(hIn:'%s')",hIn.GetName()), 5-debugSignal);
  TH2D* hOut = new TH2D(hIn);

  //check binning first:
  //cout << "  x in: " << hOut->GetXaxis()->GetBinLowEdge(10) << "  effi: " << hEffi->GetXaxis()->GetBinLowEdge(10) << endl;
  //cout << "  y in: " << hOut->GetYaxis()->GetBinLowEdge(5) << "  effi: " << hEffi->GetYaxis()->GetBinLowEdge(5) << endl;
  if ( TMath::Abs(hEffi->GetXaxis()->GetBinLowEdge(10) - hOut->GetXaxis()->GetBinLowEdge(10)) > 0.00001 ) {
    LmHelper::Error("LmSignal::ApplyEfficiency2D(): inconsistent binning in X! not correcting for efficiency!"); return;
  }
  if ( TMath::Abs(hEffi->GetYaxis()->GetBinLowEdge(5) - hOut->GetYaxis()->GetBinLowEdge(5)) > 0.00001 ) {
    LmHelper::Error("LmSignal::ApplyEfficiency2D(): inconsistent binning in Y! not correcting for efficiency!"); return;
  }

  for(Int_t ix = 1; ix <= hEffi->GetNbinsX(); ++ix){
    for(Int_t iy = 1; iy <= hEffi->GetNbinsY(); ++iy){
      if (ix > hOut->GetNbinsX()) break;
      if (iy > hOut->GetNbinsY()) break;
      Double_t eff(0.),val(0.),valerr(0.);
      eff    = hEffi->GetBinContent(ix,iy);

      val    = hOut->GetBinContent(ix,iy);
      valerr = hOut->GetBinError(ix,iy);
      if(eff > 0.) {
        val/=eff; valerr/=eff;
      }
      hOut->SetBinContent(ix,iy,val);
      hOut->SetBinError(ix,iy,valerr); // may not be meaningful, statistics have to be recomputed!
    }
  }

  //const char* texEffi="#epsilon_{corr} ";
  TString sTitle(hOut->GetZaxis()->GetTitle());
  sTitle.ReplaceAll("raw ","");
  //sTitle.Prepend(texEffi);
  hOut->SetZTitle(sTitle.Data());
  hOut->SetTitle(sTitle.Data());
  hIn = *hOut;
  delete hOut;
  return;
}


//_______________________________________________________________________________________________
void LmManager::ApplyEfficiency2D_all(const TH2D* hEffi)
{
  /// Note that efficiency correction for unsubtracted spectra may not be really meaningful, because the efficiency
  /// is typically determined based on signal pairs, and the one for background pairs may be different.
  
  ApplyEfficiency2D(*GetUnlike(), hEffi);
  ApplyEfficiency2D(*GetLikePP(), hEffi);
  ApplyEfficiency2D(*GetLikeMM(), hEffi);	
  return;
}




//_______________________________________________________________________________________________
TString LmManager::GetAll3DProjRanges() const {
  TString sproj("");
  if (fProjRangeMinima[0]>-1.0e20) sproj.Append(Form("%.2f #leq %s #leq %.2f %s & ",fProjRangeMinima[0],LmBaseSignal::GetInputLabelXvar().Data(),fProjRangeMaxima[0],LmBaseSignal::GetInputLabelXunit().Data()));
  if (GetNdimInput()>1) { if (fProjRangeMinima[1]>-1.0e20) sproj.Append(Form("%.2f #leq %s #leq %.2f %s & ",fProjRangeMinima[1],LmBaseSignal::GetInputLabelYvar().Data(),fProjRangeMaxima[1],LmBaseSignal::GetInputLabelYunit().Data())); }
  if (GetNdimInput()>2) { if (fProjRangeMinima[2]>-1.0e20) sproj.Append(Form("%.2f #leq %s #leq %.2f %s & ",fProjRangeMinima[2],LmBaseSignal::GetInputLabelZvar().Data(),fProjRangeMaxima[2],LmBaseSignal::GetInputLabelZunit().Data())); }
  // This is more elegant, but crashes when the manager was created without 3D histograms, e.g. via LmSignal::InitFromRootfile().
  //  if (fhXdimYdimZdim[0]->GetXaxis()->TestBit(TAxis::kAxisRange)) sproj.Append(Form("%.2f #leq %s #leq %.2f %s & ",fProjRangeMinima[0],LmBaseSignal::GetInputLabelXvar().Data(),fProjRangeMaxima[0],LmBaseSignal::GetInputLabelXunit().Data()));
  //  if (fhXdimYdimZdim[0]->GetYaxis()->TestBit(TAxis::kAxisRange)) sproj.Append(Form("%.2f #leq %s #leq %.2f %s & ",fProjRangeMinima[1],LmBaseSignal::GetInputLabelYvar().Data(),fProjRangeMaxima[1],LmBaseSignal::GetInputLabelYunit().Data()));
  //  if (fhXdimYdimZdim[0]->GetZaxis()->TestBit(TAxis::kAxisRange)) sproj.Append(Form("%.2f #leq %s #leq %.2f %s & ",fProjRangeMinima[2],LmBaseSignal::GetInputLabelZvar().Data(),fProjRangeMaxima[2],LmBaseSignal::GetInputLabelZunit().Data()));
  if (sproj.Length()>3) sproj.Resize(sproj.Length()-3); // remove the last ' & '
  // remove lower ptee bound if it is zero, to be consistent with labels in normal plots.
  sproj.ReplaceAll("0.00 #leq #it{p}_{T,ee}", "#it{p}_{T,ee}");
  return sproj;
}

//_______________________________________________________________________________________________
const char* LmManager::GetExclCutTypeNameStatic(UInt_t itype)
{
  switch (itype) {
    case kNoCut     : return "NoCut";
    case kAuto      : return "Auto";
    case kDoCut     : return "DoCut";
    case kFlatCorrUnsub : return "FlatCorrUnsub";
    case kFlatCorrSub   : return "FlatCorrSub";
    case kFlatCorrSubAll: return "FlatCorrSubAll";
    case kTemplUnsub: return "TemplUnsub";
    case kTemplSub  : return "TemplSub";
    case kTemplConv : return "TemplConv";
  }
  return "undefined";
}
