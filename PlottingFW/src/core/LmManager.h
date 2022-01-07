#ifndef LMMANAGER_H
#define LMMANAGER_H

// c++ includes
#include <vector>
// ROOT includes
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
// project includes
#include "LmBaseManager.h"
#include "LmRebinner.h"
#include "LmHelper.h"
// forward declarations
class TString;
class TFile;
class TCollection;
class TObject;

class LmManager : public LmBaseManager, public LmRebinner {
public:
  LmManager(const LmManager& man, Bool_t copyHistograms=kTRUE);
  LmManager(const char* cconfig);
  ~LmManager();
  
  // function declarations
  Int_t         Process(Int_t type=kDoEverything);
  Int_t         ReadAllHistogramsFromFiles();
  void          CopyHistogramsFrom(const LmManager& man);
  void          SignalPostCorrection(TH2D* hSignal); // Used by LmSignal
  void          AddVisualSig(TH2D* hSignal, const char* name = "", const char* title = "");
  void          AddCorrectedSig(TH2D* hSignal, const char* name = "");
  
  void          Print2DUnlike(const Char_t* filename = "c2DUnlike.pdf");
  void          Print2DLikePP(const Char_t* filename = "c2DLikePP.pdf");
  void          Print2DLikeMM(const Char_t* filename = "c2DLikeMM.pdf");
  void          Print2DLikePPMix(const Char_t* filename = "c2DLikePPMix.pdf");
  void          Print2DLikeMMMix(const Char_t* filename = "c2DLikeMMMix.pdf");
  void          Print2DUnlikeMix(const Char_t* filename = "c2DUnlikeMix.pdf");
  void          Print2DEffi(const Char_t* filename = "c2DEffi.pdf");
  void          Print2DAcce(const Char_t* filename = "c2DAcce.pdf");
//void          PrintTH2(TH2D* hIn, const Char_t* filename); // in Base class

  void      Rebin2DHistogram2(TH2D& hIn, Int_t n_bins_mee, Double_t* bins_mee, Int_t n_bins_ptee, Double_t* bins_ptee); //Hotfix



  // setters
//void          SetInputhistAndDim(const char* histname, Int_t dim); // in Base class
//void          SetRebinning2D(Int_t n_bins_mee, const Double_t* bins_mee, Int_t n_bins_ptee, const Double_t* bins_ptee); // in Base class
//void          SetEnableRebinning(bool SEVB=kTRUE) { fEnableRebinning = SEVB; } // in Base class
  void          SetEffifileAndHists(const char* filename, const char* name_gen, const char* name_rec); ///< Called internally if 'cconfig' contains efficiency information.
  void          SetAccefileAndHists(const char* filename, const char* name_gen, const char* name_rec); ///< Called internally if 'cconfig' contains efficiency information.
  void          Set3DExclusionZbelow(Int_t n_val, const Double_t* val);
  void          Set3DExclusionZabove(Int_t n_val, const Double_t* val);
  void          Set3DExclusionEdgesX(Int_t n_val, const Double_t* val);
  void          SetTemplateNormRegionMin(Int_t n_val, const Double_t* val);
  void          SetTemplateNormRegionMax(Int_t n_val, const Double_t* val);
  void          SetTemplateNormRegion(Double_t, Double_t); ///< outdated, keep for error message.
  void          SetExclusionZTemplates(TH3D* uls, TH3D* ls=0x0, UInt_t ttype=kAuto, TH3D* more1=0x0, TH3D* more2=0x0);
  void          SetCutValPhiV(Double_t val, Double_t min=0) { Set3DExclusionZabove(1, &val); Set3DExclusionZbelow(1, &min); }
  void          SetCutValMee(Double_t val)                  { Set3DExclusionEdgesX(1, &val); }
  void          SetEnableExclusionCutZ(UInt_t b=kDoCut)     { fEnable3DExclCut = b; std::cout << "~~~~~~~~~~~ " << b << std::endl;} ///< Specify exclusion cut type if automatic recognition is insufficient.
  void          SetEnablePhiVCut(bool)                      { LmHelper::Error("LmManager::SetEnablePhiVCut(bool) outdated. -> use SetEnableExclusionCutZ(UInt_t);"); }
  void          SetEnableEffiCorr(bool b=kTRUE)             { fEnableEffiCorr = b; } ///< Should only be used for deactivation.
  void          SetEnableAcceCorr(bool b=kTRUE)             { fEnableAcceCorr = b; } 
  void          SetEnableTR(bool b=kTRUE)                   { fEnableTR = b; }
  void          SetExternalInputfile(TFile* file)           { fInputfile = file; fUseExternalInputfile = kTRUE; }
  void          Set3DProjRangeX(Double_t min, Double_t max) { SetProjRange(min, max, 0); }
  void          Set3DProjRangeY(Double_t min, Double_t max) { SetProjRange(min, max, 1); }
  void          Set3DProjRangeZ(Double_t min, Double_t max) { SetProjRange(min, max, 2); }
  void          SetProjRange(Double_t min, Double_t max, UInt_t axis);
  void          SetProjOption(const char* option/*="yx"*/)  { fsProjOption = option; } ///< option="ab" means: a vertical, b horizontal (ROOT-convention)
  void          SetNeventsPhysSel(Double_t newevts)         { fNeventsPhysSel = newevts; } ///< Set number of events manually, used by external signals.
  void          SetCollSystem(TString str)                  { fcoll_system = str; } ///< Set collision system manually, used by external signals.
  void          SetCollEnergy(TString str)                  { fcoll_energy = str; } ///< Set collision energy manually, used by external signals.
  void          SetCentRange(Double_t min, Double_t max)    { fcentrality_min = min; fcentrality_max = max; } ///< Set centrality manually, used by external signals.
  void          SetPtRange(Double_t min, Double_t max)      { fpt_range_min = min; fpt_range_max = max; } ///< Set pt range manually, if automatic estimation not enough. If max < 0., no upper limit is drawn.
  void          SetEtaRange(Double_t min, Double_t max)     { feta_range_min = min; feta_range_max = max; } ///< Set eta range manually, if automatic estimation not enough.
  void          SetThetaEEmin(Double_t thetaEEmin)          { fThetaEE_min = thetaEEmin; } ///< Set opening angle manually, if automatic estimation not enough.
  void          SetDoEffiCorr (Bool_t SDEC = kTRUE)         { fDoEffiCorr = SDEC; }
  void          SetDoAcceCorr (Bool_t SDAC = kTRUE)         { fDoAcceCorr = SDAC; }
  void          SetAcce(TH2D *hAcce)                        { fhAcce = new TH2D(*hAcce); }


  // getters
  Double_t      GetNeventsPhysSel() const { return fNeventsPhysSel; }
  TString       GetCollSystem()     const { return fcoll_system; }
  TString       GetCollEnergy()     const { return fcoll_energy; }
  Double_t      GetCentrality_min() const { return fcentrality_min; }
  Double_t      GetCentrality_max() const { return fcentrality_max; }
  Double_t      GetPtRange_min()    const { return fpt_range_min; }
  Double_t      GetPtRange_max()    const { return fpt_range_max; }
  Double_t      GetEtaRange_min()   const { return feta_range_min; }
  Double_t      GetEtaRange_max()   const { return feta_range_max; }
  Double_t      GetThetaEEmin()     const { return fThetaEE_min; }
  //const TH2D* GetUnlike()         const { return fhMeePtee[0]; } // first 'const' means: return value may not be changed later (but that is needed in our code for printing).
  TH2D*         GetUnlike()         const { return fhMeePtee[0]; } // 'const' after function() means: class variables may not be changed within the function.
  TH2D*         GetLikePP()         const { return fhMeePtee[1]; }
  TH2D*         GetLikeMM()         const { return fhMeePtee[2]; }
  TH2D*         GetLikePPMix()      const { return fhMixedMeePtee[1]; }
  TH2D*         GetLikeMMMix()      const { return fhMixedMeePtee[2]; }
  TH2D*         GetUnlikePPMix()    const { return fhMixedMeePtee[0]; }
  TH2D*         GetUnlikeMMMix()    const { return fhMixedMeePtee[3]; }
  TH2D*         GetUnlikeMix()      const { return fhMixedMeePteeULS; }
  //TH2D*       GetUnlikeMix()      const { TH2D* hTmp = new TH2D(*fhMixedMeePtee[0]); hTmp->Add(fhMixedMeePtee[3]); return hTmp; } // causes memory leak if hTmp will not be deleted by calling class. 
  //const TH2D* GetUnlikeMix()      const { TH2D* hTmp = fhMixedMeePtee[0]; hTmp->Add(fhMixedMeePtee[3]); return hTmp; }
  // this above is wrong because it changes the contents of the class (even though it is const, but maybe only the pointers). noticed when calculating 1D Rfactors later.
  TH3D*         GetHist3D(Int_t i)  const { return fhXdimYdimZdim.at(i); }
  TH3D*         GetHistMix3D(Int_t i)const{ return fhMixedXdimYdimZdim.at(i); }
  TH2D*         GetEffi()           const { if (fhEffi) return fhEffi; else return 0x0; }
  TH2D*         GetAcce()           const { if (fhAcce) return fhAcce; else return 0x0; }
  Bool_t        GetEnableEffiCorr() const { return fEnableEffiCorr; }
  Bool_t        GetEnableAcceCorr() const { return fEnableAcceCorr; }
  UInt_t        GetExclCutType()    const { return fEnable3DExclCut; }
  TFile*        GetInputfilePointer()const{ return fInputfile; }
  Bool_t        HasMixedEvent()     const { return (fNmixcombs>0)?kTRUE:kFALSE; }
  Bool_t        IsSubtractedMC()    const { return fIsSubtractedMC; }
  TString       GetAll3DProjRanges() const; ///< Return a TString which contains all applied 3D projection ranges.
  UInt_t        GetNVisualSig()     const { return fhVisualSig.size(); } ///< Used by LmSignal::GetNVisualSig().
  TH2D*         GetVisualSigI(UInt_t i) const { return fhVisualSig.at(i); } ///< Used by LmSignal::GetVisualSigI().
  Bool_t        GetDoEffiCorr()     const { return fDoEffiCorr; }
  Bool_t        GetDoAcceCorr()     const { return fDoAcceCorr; }
  TString       GetConfig()               { return fsConfiglong; }

  
  enum enType {
    kDoEverything=0,  ///< Default manager type, reads input files and processes the histograms.
    kReadInputOnly,   ///< Only read in histograms. Useful when copying the manager afterwards for different 3D projections.
    kDontReadInput,   ///< Do everything except reading input. Should be used for managers which are copies of another manager.
    kDontCleanUp,     ///< Do everything except cleanup. Useful when 3D histograms are needed later.
    kCleanUp,         ///< Can be called for the manager that did 'kReadInputOnly', AFTER all other managers have been processed.
    kRebinAcce        //Rebins the acceptance histogram needed as it can only be applied on the cocktail subtracted signal
  };
  
  enum enExclCutType {
    kNoCut=0,         ///< Do not do a 3D exclusion cut.
    kAuto,            ///< For internal use: automatically pick the most reasonable cut type based on the given template(s).
    kDoCut,           ///< Do the cut, but do not correct for it.
    kFlatCorrUnsub,   ///< Correct unlike and like sign assuming flat distribution in the cut dimension.
    kFlatCorrSub,     ///< Correct subtracted signal assuming flat distribution in the cut dimension.
    kFlatCorrSubAll,  ///< Same as kFlatCorrSub, but replaces all datapoints with their average in the phiV plot.
    kTemplUnsub,      ///< Correct for cut in 3D using templates for unlike and like sign distributions.
    kTemplSub,        ///< Template for subtracted signal. Does exclusion in 3D and correction in 2D.
    kTemplConv        ///< Instead of doing the cut, subtract a given gamma conversion template from the data.
    /// please update GetExclCutTypeName() when new types are added!
  };
  
  const char*         GetExclCutTypeName() const { return GetExclCutTypeNameStatic(fEnable3DExclCut); }
  static const char*  GetExclCutTypeNameStatic(UInt_t itype);

private:
  void          GetHistogramsFromFiles3D();
  void          GetHistogramsFromFiles2D();
  void          GetEffiHistogramsFromFiles();
  void          GetAcceHistogramsFromFiles();
  TH3D*         Obtain3DHistogram(TObject* inputHist, TString newname="");
  void          SetTitlesInputhist(TH1* hist);
  void          InitProjectionRanges() /*override*/; // optional 'override' specifier since C++11.
  void          Set3DProjectionRanges();
  void          ProjectInto2D();
  void          ApplyExclusionCutIn3D();
  void          SubtractConversionTemplate();
  void          CorrectForExclusionCutIn3D();
  void          CorrectForExclusionCutIn2D(TH2D* hSignal=0x0, Bool_t doNorm=kTRUE, Bool_t doShift=kFALSE);
  void          CorrectForExclusionCutFlat(TH2D* hSignal);
  Bool_t        Find3DExclusionValues(Double_t x/*, Double_t y*/);
  Bool_t        InExclusionCutRegion(Double_t binLowEdge, Double_t binUpEdge);
  Bool_t        InTemplateNormRegion(Double_t binLowEdge, Double_t binUpEdge);
  
  void          CalcEffi();
  void          CalcAcce();
  void          CalcEtaRange();
  void          CalcPtRange();
  void          CalcPtRange_min();
  void          CalcPtRange_max();
  void          CalcCentrality();
  void          CalcOpeningAngle();
  void          Rebin2DHistogram_all();
  void          Rebin2DHistogram_acce();
//void          Rebin2DHistogram(TH2D& hIn, Int_t n_bins_mee, Double_t* bins_mee, Int_t n_bins_ptee, Double_t* bins_ptee); // in LmRebinner class
  void          CloseFileAndCleanUp();
  void          ApplyEfficiency2D(TH2D& hIn, const TH2D* hEffi);
  void          ApplyEfficiency2D_all(const TH2D* hEffi);

  // switches
  UInt_t        fEnable3DExclCut;
  Bool_t        fEnableEffiCorr;
  Bool_t        fEnableAcceCorr;
  Bool_t        fEnableTR;
//Bool_t        fEnableRebinning; // in LmRebinner class
  Bool_t        fUseExternalInputfile;
  Bool_t        fIsSubtractedMC;
  Bool_t        fDoEffiCorr;
  Bool_t        fDoAcceCorr;
 
  // variables
// in Base class:
//TString               fsInputfiles;
//TString               fsInputhists;
//Int_t                 fNdimInput;
//std::vector<Double_t> fBinsRebin_Mee; // in LmRebinner class
//std::vector<Double_t> fBinsRebin_Ptee; // in LmRebinner class
  TFile*        fInputfile;  // pointer to rootfile
  TCollection*  fCutfolder;  // hashlist for given cut setting
  Int_t         fNperiods;    // Not fully implemented. Please re-check this functionality when re-activating it.
  const Int_t   fNperiodsMAX;
  const Int_t   fNpaircombs;
  Int_t         fNmixcombs;   // Not const anymore to disable mixed event histograms (e.g. in case of MC).
  TString       fPairCombNames;
  TString       fMixCombNames;
  std::vector<TH2D*> fhMeePtee;
  std::vector<TH2D*> fhMixedMeePtee;
  std::vector<TH3D*> fhXdimYdimZdim;
  std::vector<TH3D*> fhMixedXdimYdimZdim;
  TH2D*         fhMixedMeePteeULS; // to avoid memory leak in function GetUnlikeMix().
  TH2D*         fhRotatedInvMassPt;
  Double_t      fNeventsPhysSel;
  TString       fsConfiglong;
  TString       fsEffifile;
  TString       fsEffiGen;
  TString       fsEffiRec;
  TH2D*         fhEffiGen;
  TH2D*         fhEffiRec;
  TH2D*         fhEffi;
  TString       fsAccefile;
  TString       fsAcceGen;
  TString       fsAcceRec;
  TH2D*         fhAcceGen;
  TH2D*         fhAcceRec;
  TH2D*         fhAcce;
  std::vector<Double_t> f3DExclusionZbelow;
  std::vector<Double_t> f3DExclusionZabove;
  std::vector<Double_t> f3DExclusionEdgesX;
  std::vector<Double_t> fTemplateNormRegionMin;
  std::vector<Double_t> fTemplateNormRegionMax;
  std::vector<TH3D*>    fhExclusionZTemplates;
  std::vector<TH2D*>    fhVisualSig; // can be filled to visualize steps of correction procedures.
  TH2D*         fhCorrectedSig; // for the second part of the phiV template fit correction.
  Double_t      fCutValZbelow;
  Double_t      fCutValZabove;
  Double_t      fTemplNormMin;
  Double_t      fTemplNormMax;
  Double_t      feta_range_min;
  Double_t      feta_range_max;
  Double_t      fpt_range_min;
  Double_t      fpt_range_max;
  Double_t      fThetaEE_min;
  Double_t      fcentrality_min;
  Double_t      fcentrality_max;
  TString       fcoll_system;
  TString       fcoll_energy;
  std::vector<Double_t> fProjRangeMinima;
  std::vector<Double_t> fProjRangeMaxima;
  TString       fsProjOption;
};

#endif
