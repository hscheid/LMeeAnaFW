#ifndef LMBACKGROUND_H
#define LMBACKGROUND_H

// c++ includes
// ROOT includes
#include "TH2.h"
#include "TF2.h"
// project includes
#include "LmManager.h"

class LmBackground {
public:
  LmBackground(LmManager &mgr, std::string name = "default");
  ~LmBackground();
  
  // function declarations
  void          Process(Int_t type, Bool_t recursive=kFALSE);
  void          PrintBkg2D(const Char_t* filename = "c2DBkg.pdf");
  void          PrintRfactor2D(const Char_t* filename = "c2DRfactor.pdf");
  TH1D*         CalcRfactor1D(const TH1D* hNum, const TH1D* hDenom, const Char_t* newname) { return CalcRfactorByDiv1D(hNum,hDenom,newname); }
  // setters
  void          SetName(const std::string name)                    { fName = name; }
  void          SetUseRfactor(bool SURF=kTRUE)                     { fUseRfactor = SURF; }
  void          SetUseRfactorUnity(Bool_t b)                       { fUseRfactorUnity = b; }
  void          SetRfactorUnityRange(const Double_t r)             { fRfactorUnityRadius = r; fUseRfactorUnity = kTRUE; }
  void          SetRfactorUnityRectangle(Double_t x, Double_t y)   { fRfactorUnityMee = x; fRfactorUnityPtee = y; fUseRfactorUnity = kTRUE; }
  void          AddResidualFunction(TF2* func)                     { fResidualFunction.push_back(func); fResidualFunction.at(fResidualFunction.size()-1)->GetRange(fFitMeeMin,fFitPteeMin,fFitMeeMax,fFitPteeMax); }
  void          SetFitMeeRange(Double_t min, Double_t max)         { fFitMeeMin = min; fFitMeeMax = max; }
  void          SetFitPteeRange(Double_t min, Double_t max)        { fFitPteeMin = min; fFitPteeMax = max; }
  void          SetNormalizationRegion(Double_t min, Double_t max) { fNormMin = min; fNormMax = max; }
  void          SetMakeFitQA(Bool_t b)                             { fFitQA = b; }
  void          SetBinsMee_forprojPtee(std::vector<Double_t> v)    { fQA_BinsMee_forprojPtee = v; }
  void          SetBinsPtee_forprojMee(std::vector<Double_t> v)    { fQA_BinsPtee_forprojMee = v; }
  void          SetFitQAPlotYrange(Double_t min, Double_t max)     { fFitQAPlotYmin = min; fFitQAPlotYmax = max; }
  // getters
  const char*   GetName()                     const { return fName.c_str(); }
  const char*   GetTypename()                 const { return fTypename.c_str(); }
  const char*   GetBkgName()                  const { return GetBkg2D()->GetName(); }
  TH2D*         GetBkg2D()                    const { if (fBkg/*fUseRfactor*/) return fBkg; else return fLike; }
  TH2D*         GetLike2D()                   const { return fLike; }
  TH2D*         GetLikeMix2D()                const { return fLikeMix; }
  TH2D*         GetRfactor2D()                const { return fRfactor; }
  Bool_t        GetUseRfactor()               const { return fUseRfactor; }
  Bool_t        GetUseRfactorUnity()          const { return fUseRfactorUnity; }
  Double_t      GetRfactorUnityRange()        const { return fRfactorUnityRadius; }
  TF2*          GetResidualFunction(Int_t i)  const { return fResidualFunction.at(i); }
  TH2D*         GetBkgLow2D()                 const { return fBkgLow; }
  TH2D*         GetBkgHigh2D()                const { return fBkgHigh; }
  
  
  enum enType {
    kNoProcess=0,
    kGeom,
    kArith,
    kHybrid,
    kGeomFit,
    kArithFit,
    kHybridFit,
    kMAX,
    kReal,
    kLog,
    kLSpp,
    kLSmm,
    kULSmixed
  };
  
private: 
  TH2D*         CalcLSBackgroundPositive(const TH2D* hPP, const TH2D* hPPmixed, const Char_t* newname);
  TH2D*         CalcLSBackgroundNegative(const TH2D* hMM, const TH2D* hMMmixed, const Char_t* newname);
  TH2D*         CalcULSBackgroundMixed(const TH2D* hULSmixed, const TH2D* hULSmixed1, const Char_t* newname);
  TH2D*         CalcLSBackgroundGeom(const TH2D* hPP, const TH2D* hMM, const Char_t* newname); // calculates 2*sqrt(N1*N2) and sets correct errors per bin
  TH2D*         CalcLSBackgroundArith(const TH2D* hPP, const TH2D* hMM, const Char_t* newname);
  TH2D*         CalcLSBackgroundHybrid(const TH2D* hPP, const TH2D* hMM, const Char_t* newname);
  TH2D*         CalcLSBackgroundReal(const TH2D* hPP, const TH2D* hMM, const Char_t* newname);
  TH2D*         CalcLSBackgroundLog(const TH2D* hPP, const TH2D* hMM, const Char_t* newname); 

  TH2D*         CalcRfactorByDiv2D(const TH2D* hNum, const TH2D* hDenom, const Char_t* newname);   // make sure to change 1D and 2D consistently!
  TH1D*         CalcRfactorByDiv1D(const TH1D* hNum, const TH1D* hDenom, const Char_t* newname); // make sure to change 1D and 2D consistently!
  TH2D*         CorrectByRfactor(const TH2D* hLS, const TH2D* hRfac, const Char_t* newname);
  void          SetRfactorToUnity(TH2D *hRfactor);
  void          SetRfactorToUnityRectangle(TH2D *hRfactor, Double_t meeCut, Double_t pteeCut);
  TH2D*         FitNormalizationAndResiduals(const TH2D* hLS, const TH2D* hUSmix, const Char_t* newname);
  void          PrintFitQA(TH2D &hRes, std::vector<TH2D> &vFit, std::vector<Double_t> bins,  Bool_t projOnMee);
  
  std::string   fName;
  Int_t         fType;
  std::string   fTypename;
  LmManager*    fLmMgr; ///> Manager which holds all spectra
  TH2D*         fBkg;   ///> R-factor corrected background, created during construction of an LmBackground-object if fUseRfactor is set.
  TH2D*         fLike;  ///> LikeSign-background is created during construction of an LmBackground-object. (in case of "Geom": fLike = 2*sqrt{ N_{++}*N_{--} })
  TH2D*         fLikeMix; ///> LikeSign-MixedEvent-background is created during construction of an LmBackground-object. (in case of "Geom": fLike = 2*sqrt{ N^{mix}_{++}*N^{mix}_{--} })
  TH2D*         fRfactor; ///> R-factor = ULSmix / fLikeMix, with ULSmix coming from manager-object. (in case of "Geom": R = N^{mix}_{+-} / 2 #sqrt{ N^{mix}_{++} N^{mix}_{--} })
  Bool_t        fHasMixedEvent;
  Bool_t        fUseRfactor;
  Bool_t        fUseRfactorUnity; ///> Set Rfactor to 1 in given region
  Double_t      fRfactorUnityRadius;
  Double_t      fRfactorUnityMee;
  Double_t      fRfactorUnityPtee;
  
  Double_t              fNormMin; ///> defined minimum of normalization region in mee
  Double_t              fNormMax; ///> defined maximum of normalization region in mee
  Double_t              fFitMeeMin;  ///> fit range minimum in mee set by fResidualFunction definition 
  Double_t              fFitMeeMax;  ///> fit range maximum in mee set by fResidualFunction definition 
  Double_t              fFitPteeMin;  ///> fit range minimum in mee set by fResidualFunction definition 
  Double_t              fFitPteeMax;  ///> fit range maximum in mee set by fResidualFunction definition
  std::vector<TF2*>     fResidualFunction; ///> 2 dimensional function to fit the residual correlated background in LS/US_mix. Currently only its pointer is stored.
  Bool_t                fFitQA;
  Double_t              fFitQAPlotYmin;
  Double_t              fFitQAPlotYmax;
  std::vector<Double_t> fQA_BinsMee_forprojPtee;
  std::vector<Double_t> fQA_BinsPtee_forprojMee;
  
  TH2D *fBkgLow;
  TH2D *fBkgHigh;
};

#endif
