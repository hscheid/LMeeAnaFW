#ifndef LMCOCKTAILMAN_H
#define LMCOCKTAILMAN_H

// c++ includes
#include <vector>
#include <string>
// ROOT includes
#include "TH2.h"
// project includes
#include "LmBaseManager.h"
#include "LmRebinner.h"
#include "LmHelper.h"

class LmCocktailMan : public LmBaseManager, public LmRebinner {
public:
  LmCocktailMan();
  LmCocktailMan(TString InFiles,TString InHistNames,Int_t Ndim,Int_t nRebinM,const Double_t *newBinsM,Int_t nRebinPt,const Double_t *newBinsPt,TString NeventsHistNames="");
  ~LmCocktailMan();

  // function declarations
  Int_t         Process(Int_t type, Bool_t recursive=kFALSE);
  void          RemoveEntry(unsigned int i_spec); ///< Call after Process() to remove a contribution from the cocktail. Not feasible to implement in LmCocktail atm..
  // setters
  void          SetNormMidRap(bool DoNormMidRap) { fDoNormMidRap = DoNormMidRap;}
  void          SetHistForNevents(const char* histnames) { fsHistForNevents = histnames; } ///< Optional: Set a histogram from which a normalization factor is obtained. See CalcNevents().
  void          SetHistForNeventsHF(const char* histnames) { SetHistForNevents(histnames); }
  void          SetUndoBinwidthNormalizationMee(bool undo=kTRUE) { fUndoBinwidthNormalizationMee = undo; } ///< Needed when 2D cocktail spectra were already normalized per GeV/c^2.
  void          SetInputfilesAndHistsLow(const char* files, const char* histnames)  { fsInputfilesLow=files;  fsInputhistsLow=histnames; }
  void          SetInputfilesAndHistsHigh(const char* files, const char* histnames) { fsInputfilesHigh=files; fsInputhistsHigh=histnames; }
  void          SetRelUncertainties(const char* unc)  { fsRelUncertainties=unc; } ///< Can be used instead of or in addition to specifying additional files for systematics. E.g.: "+0.2:-0.1[:+0.3:-0.3:...]".
  void          SetArbitraryScaling(Double_t val)     { fArbitraryScaling=val; }
  void          SetType(Int_t type); // better solved in LmCocktailPart.

  // getters
  const char*   GetTypename() const                   { return fTypename.c_str(); } ///< Returns default name for each type. Also useful for Error messages.
  Int_t         GetNEntries() const                   { return fhMeePtee.size(); }
  Double_t      GetArbitraryScaling() const           { return fArbitraryScaling; }
  TH2D*         GetSpectrumI(unsigned int i_spec) const {
		/**/          if (i_spec>=fhMeePtee.size()) { LmHelper::Error(Form("LmCocktailMan::GetSpectrumI(i_spec=%u): out of range!", i_spec)); }
		/**/          return fhMeePtee.at(i_spec);
		/**/        }
  TH2D*         GetSpectrumILow(unsigned int i_spec) const  { if(i_spec>=fhMeePteeLow.size())  return 0x0; else return fhMeePteeLow.at(i_spec); }
  TH2D*         GetSpectrumIHigh(unsigned int i_spec) const { if(i_spec>=fhMeePteeHigh.size()) return 0x0; else return fhMeePteeHigh.at(i_spec); }
  Bool_t        HasSystematics() const { return (fhMeePteeLow.size()>0 && fhMeePteeHigh.size()==fhMeePteeLow.size()); }

  enum enType {
    kUndef=0,
    kResonances,
    kLFsum,
    kJpsi,
    kHeavyFl,
    kVirtGamma,
    kRappMee,
    kRappPtee,
    kHFsum,
    kFromFileMee,
    kFromFilePtee
    // always update function SetType() when new types are added.
  };

  enum enInput {
    kAdd=0,     ///< Adds identical histograms from multiple files and stores them in a vector.
    kOneByOne   ///< Reads one specified histogram from each file. See comments in GetHistogramsFromFiles2D().
  };

private:
  // functions
  void          GetHistogramsFromFiles2D(Int_t setting, Int_t doSys=0);
  void          GetHistogramsFromFiles1D(Bool_t IsMee);
  void          GetHistogramsRapp1D_Mee();
  void          GetHistogramsRapp1D_Ptee();
  void          GetHistogramsRapp2D();
  void          CalcSumAndClearOthers(const char* histname);
  Double_t      CalcNevents(TList* llist, Int_t posi);
  Bool_t        HasValidSysInput(); ///< Only checks the strings, not if the files exist.
  std::vector<Double_t> GetRelUncertainties(Int_t doSys, Int_t nSpectra);
  void          FindMeeAxisIn2DHist(TH2D* hIn, Double_t mass);
  void          FlipAxes();
  void          Rebin2DHistogram_all();

  // switches
  Bool_t        fMeeIsOnXaxis;
  Bool_t        fUndoBinwidthNormalizationMee;

  // variables
  Int_t         fType;
  std::string   fTypename;
  TString       fsHistForNevents;
  std::vector<TH2D*>    fhMeePtee;
  TString               fsInputfilesLow;
  TString               fsInputhistsLow;
  TString               fsInputfilesHigh;
  TString               fsInputhistsHigh;
  TString               fsRelUncertainties;
  std::vector<TH2D*>    fhMeePteeLow;
  std::vector<TH2D*>    fhMeePteeHigh;
  Double_t      fArbitraryScaling;
  Bool_t        fDoNormMidRap;
  // If more variables per cocktail component are added (e.g. std::vector), please update RemoveEntry() accordingly.
  
};

#endif
