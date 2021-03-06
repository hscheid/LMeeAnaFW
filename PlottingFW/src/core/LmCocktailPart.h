#ifndef LMCOCKTAILPART_H
#define LMCOCKTAILPART_H

// c++ includes
#include <vector>
#include <string>
// ROOT includes
#include "TH1.h"
#include "TH2.h"
#include "TGraphAsymmErrors.h"
// project includes
#include "LmBaseSignal.h"
#include "LmHelper.h"

class LmCocktailPart : public LmBaseSignal {
public:
  LmCocktailPart(const LmCocktailPart& part);
  LmCocktailPart(std::string name = "default");
  ~LmCocktailPart();
  LmCocktailPart* Copy(std::string newname = "", Int_t color = -1);

  // function declarations
  void          Process(Int_t type);
  void          MakeSpectra1D(const std::vector<Double_t> bins, Bool_t projOnMee);
  // setters
  void          SetName(const std::string name)        { fName = name; }
  void          SetSpectrum2D(const TH2D* newspec)     { fSpectrum = new TH2D(*newspec); } // using copy constructor of TH2D.
  void          SetSpectrum2DLow(const TH2D* newspec)  { fSpectrumLow = new TH2D(*newspec); }
  void          SetSpectrum2DHigh(const TH2D* newspec) { fSpectrumHigh = new TH2D(*newspec); }
  void          SetType(Int_t type);
  void          SetMTscalingRelUncertainty(double low, double high)  {fMTscalingUnc.at(0)=low;fMTscalingUnc.at(1)=high; }
  void          SetBRRelUncertainty(double low, double high)         {fBRUnc.at(0)=low;fBRUnc.at(1)=high; }
  void          SetParamRelUncertainty(double low, double high)         {fParamUnc.at(0)=low;fParamUnc.at(1)=high; }
  void          SetAdditionalRelUncertainty(double low, double high) {fAddUnc.at(0)=low;fAddUnc.at(1)=high; }
  static void   SetUseShortLegendNames(bool b=kTRUE)   { fUseShortLegendNames = b; }

  // getters
  const char*   GetName()             const { return fName.c_str(); }
  Int_t         GetType()             const { return fType; }
  const char*   GetTypename()         const { return GetTypenameStatic(fType); } ///< Returns default name for current type. Also useful for Error messages.
  static const char* GetTypenameStatic(Int_t type); ///< Returns default name for given type. Also useful for Error messages.
  static const char* GetLegendnameStatic(Int_t type); ///< Returns default legend entry name for given type, depending on fUseShortLegendNames.
  static bool   GetUseShortLegendNames()    { return fUseShortLegendNames; }
  TH2D*         GetSpectrum2D()       const { return fSpectrum; } // after calling this, the member fSpectrum can be modified from outside! (which is needed)
  TH2D*         GetSpectrum2DLow()    const { return fSpectrumLow; } // after calling this, the member fSpectrum can be modified from outside! (which is needed)
  TH2D*         GetSpectrum2DHigh()   const { return fSpectrumHigh; } // after calling this, the member fSpectrum can be modified from outside! (which is needed)
  TH2D*         GetSpectrum2DCopy()     const { return (dynamic_cast<TH2D*>(fSpectrum->Clone(Form("copy_%s", this->GetTypename())))); } // <<<bitte nicht die doku mit kopieren, ohne sie entsprechend anzupassen!>>>
  TH2D*         GetSpectrum2DLowCopy()  const {
    // <<<bitte nicht die doku mit kopieren, ohne sie entsprechend anzupassen!>>>
    // fix fuer null-safety, hoffe das ist "fachlich" auch ok.
    if (fSpectrumLow) return (dynamic_cast<TH2D*>(fSpectrumLow->Clone(Form("copy_%s", this->GetTypename()))));
    else              return (dynamic_cast<TH2D*>(fSpectrum   ->Clone(Form("copy_%s", this->GetTypename()))));
  }
  TH2D*         GetSpectrum2DHighCopy() const {
    // <<<bitte nicht die doku mit kopieren, ohne sie entsprechend anzupassen!>>>
    // fix fuer null-safety, hoffe das ist "fachlich" auch ok.
    if (fSpectrumHigh) return (dynamic_cast<TH2D*>(fSpectrumHigh->Clone(Form("copy_%s", this->GetTypename()))));
    else               return (dynamic_cast<TH2D*>(fSpectrum    ->Clone(Form("copy_%s", this->GetTypename()))));
  }
  Bool_t        HasSystematics()      const { return (GetSpectrum2DLow() && GetSpectrum2DHigh()); } // modify or extend if needed -> check consequences for LmCocktail and LmHandler.
  Int_t         GetMaxBinProj(Bool_t projOnMee)           const { if (projOnMee==LmBaseSignal::kProjOnMee) return GetMaxBin_projMee();  else return GetMaxBin_projPtee(); }
  TH1D*         GetSpectrum(Int_t bin, Bool_t projOnMee)  const { if (projOnMee==LmBaseSignal::kProjOnMee) return GetSpectrum_Mee(bin); else return GetSpectrum_Ptee(bin); }
  TGraphAsymmErrors* GetSpectrumErr(Int_t bin, Bool_t projOnMee)  const { if (projOnMee==LmBaseSignal::kProjOnMee) return GetSpectrumErr_Mee(bin); else return GetSpectrumErr_Ptee(bin); }

  std::vector<TGraphAsymmErrors*> GetTmp(){ return fSpectrumErr_projMee; }
  std::vector<double>             GetMTscalingRelUncertainty(){return fMTscalingUnc;}
  std::vector<double>             GetBRRelUncertainty(){return fBRUnc;}
  std::vector<double>             GetAdditionalRelUncertainty(){return fAddUnc;}
  std::vector<double>             GetParamRelUncertainty(){return fParamUnc;}

  enum enType {
    kUndef        = 0,
    kSum          = 1<<0,
    kLF           = 1<<1,
    kPion         = 1<<2,
    kEta          = 1<<3,
    kEtaPrime     = 1<<4,
    kRho          = 1<<5,
    kOmega        = 1<<6,
    kOmegaDalitz  = 1<<7,
    kPhi          = 1<<8,
    kPhiDalitz    = 1<<9,
    kJPsiDalitz   = 1<<10,
    kJPsi         = 1<<11,
    kCharm        = 1<<12,
    kBeauty       = 1<<13,
    kVirtGamma    = 1<<14,
    kHGvac        = 1<<15,
    kHGmed        = 1<<16,
    kHGdrop       = 1<<17,
    kQGP          = 1<<18,
    kSystematic   = 1<<19,
    kHF           = 1<<20,
    kHadrBrems    = 1<<21,
    kRappSum      = 1<<22,
    kRappSumUnc   = 1<<23,
    kSmashSum     = 1<<24,
    kMAXpart      = 1<<25 // Upper limit for loops & checks. To select all particles, use kMAXpart-1.
    // always update function GetTypenameStatic() when new types are added.
  };

private:
  // functions
  void          ApplyCommonStyle();
  void          InheritStyleFrom2D(TH1* hProj);
  void          MakeSpectra1D_Mee(Double_t valmin, Double_t valmax);
  void          MakeSpectra1D_Ptee(Double_t valmin, Double_t valmax);
  void          MakeSpectraErr1D_Mee(Double_t valmin, Double_t valmax);
  void          MakeSpectraErr1D_Ptee(Double_t valmin, Double_t valmax);
  void          AttachSpectrum_Mee(TH1D &newproj)   { fSpectrum_projMee.push_back(&newproj); }
  void          AttachSpectrum_Ptee(TH1D &newproj)  { fSpectrum_projPtee.push_back(&newproj); }
  void          AttachSpectrumErr_Mee(TGraphAsymmErrors *newproj)   { fSpectrumErr_projMee.push_back(newproj); }
  void          AttachSpectrumErr_Ptee(TGraphAsymmErrors *newproj)  { fSpectrumErr_projPtee.push_back(newproj); }
  // private getters for projections. please use generalized public version for better maintenance.
  Int_t         GetMaxBin_projMee()         const { return fSpectrum_projMee.size()-1; } // not unsigned because it can be -1 in case of empty vector!
  Int_t         GetMaxBin_projPtee()        const { return fSpectrum_projPtee.size()-1; } // not unsigned because it can be -1 in case of empty vector!
  TH1D*         GetSpectrum_Mee(Int_t bin)  const { CheckRange(bin,fSpectrum_projMee.size());   return fSpectrum_projMee.at(bin); }
  TH1D*         GetSpectrum_Ptee(Int_t bin) const { CheckRange(bin,fSpectrum_projPtee.size());  return fSpectrum_projPtee.at(bin); }
  TGraphAsymmErrors* GetSpectrumErr_Mee(UInt_t i)  const { if(i+1 > fSpectrumErr_projMee.size())  return 0x0; else return fSpectrumErr_projMee.at(i); }
  TGraphAsymmErrors* GetSpectrumErr_Ptee(UInt_t i) const { if(i+1 > fSpectrumErr_projPtee.size()) return 0x0; else return fSpectrumErr_projPtee.at(i); }

  void          CheckRange(unsigned int bin, unsigned int size) const {
    /**/          if (bin>=size) { LmHelper::Error(Form("LmCocktailPart::Get...(bin=%i) out of range (size=%i)!",bin,size)); }
    /**/        } // would be even more elegant to make this function not void but "Type CheckRange(bin, std::vector<Type>)" and return the element after the check.
  Bool_t        CheckAndDeleteOldProjections(Bool_t projOnMe);

  // switches
  // variables
  std::string  	fName; // name for the legend.
  Int_t         fType;
  TH2D*         fSpectrum;
  static Bool_t fUseShortLegendNames;
  //
  // It would be great to store projections including errors as LmHistograms - as done in LmSignal.
  // Then one could natively use the divide functionality also for error bands in PrintCompare() if (fDoRatio) ...
  //
  std::vector<TH1D*> fSpectrum_projMee; // the last projection is integrated over all bins
  std::vector<TH1D*> fSpectrum_projPtee;
  TH2D*         fSpectrumLow;
  TH2D*         fSpectrumHigh;

  std::vector<double> fMTscalingUnc;
  std::vector<double> fBRUnc;
  std::vector<double> fAddUnc;
  std::vector<double> fParamUnc;

  std::vector<TGraphAsymmErrors*> fSpectrumErr_projMee; // the last projection is integrated over all bins
  std::vector<TGraphAsymmErrors*> fSpectrumErr_projPtee;
};

#endif
