#ifndef LMFILEMANAGER_H
#define LMFILEMANAGER_H

// c++ includes
#include <vector>
// ROOT includes
#include "TString.h"
#include "TObjArray.h"
// project includes
// forward declarations
class TCollection;

class LmFileManager {
public:
  static LmFileManager* Instance();
  ~LmFileManager();
  
  Bool_t        IsUsed() { return (NConfigs()>0); } ///< Used to maintain classic behavior without FileManager.
  void          AddConfig (TString sConfig);
  TCollection*  GetCutset (TString sConfig);
  void          FreeCutset(TString sConfig);
  void          Clear();
  
private:
  LmFileManager();
  static LmFileManager* fgInstance; //! singleton pointer (not sure why needed / done like in AliDielectronMC)
  
  TCollection*  GetCutset(Int_t i);
  void          OpenCutset(Int_t i);
  void          FreeCutset(Int_t i);
  Int_t         FindIndex(TString sConfig);
  
  UInt_t        NConfigs()          { return fvConfigs.size(); }
  TString       FilePath(Int_t i)   { return fvPathNames.at(i)(0, fvPathNames.at(i).First(':')); }
  TString       ListPath(Int_t i)   { return fvPathNames.at(i)(0, fvPathNames.at(i).Last(':')); }
  TString       CutsetPath(Int_t i) { return fvPathNames.at(i); }
  TString       ListName(Int_t i)   { return ((TObjArray*) fvPathNames.at(i).Tokenize(":"))->At(1)->GetName(); }
  TString       CutsetName(Int_t i) { return ((TObjArray*) fvPathNames.at(i).Tokenize(":"))->At(2)->GetName(); }
  
  // vector sizes shall be equal to number of class objects (managers) which need input. (multiple entries may occur)
  std::vector<TString>      fvConfigs;        ///< Original config string. Needed for 'interface' to LmManager via GetCutset().
  std::vector<TString>      fvPathNames;      ///< Modified  path  string. Must have format 'File:List:Cutset'.
  std::vector<Bool_t>       fvDependantsDone;
  std::vector<TCollection*> fvListPtr;
  std::vector<TCollection*> fvCutsetPtr; // pointers out of this list shall be given to normal managers.
  //
  TObjArray*                foaFiles; // store pointers, only one per file
  
};

#endif
