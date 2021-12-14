#ifndef LMSIGNAL_H
#define LMSIGNAL_H

// c++ includes
#include <vector>
#include <string>
// ROOT includes
#include "TH2.h"
// project includes
#include "LmBaseSignal.h"
#include "LmRebinner.h"
#include "LmManager.h"
#include "LmBackground.h"
#include "LmHelper.h"
// forward declarations
class TGraphAsymmErrors;
class TDirectory;


class LmSignal : public LmBaseSignal, public LmRebinner {
public:
  LmSignal(std::string name = "default", Int_t type=kNoProcess); // Do not set a 'type' which needs to be processed! (some sanity checks may not work)
  LmSignal(const LmSignal& sig, std::string name = "");
  LmSignal(LmManager &mgr, LmBackground &bkg, std::string name = "");
  ~LmSignal();
  
  LmSignal(const LmSignal &s1, const LmSignal &s2, Double_t MeeMin, Double_t MeeMax, Double_t PteeMin, Double_t PteeMax); // combination constructor -> maybe move to process

  // function declarations
  void                Process(Int_t type, Bool_t recursive=kFALSE);
  void                MakeSpectra1D(const std::vector<Double_t> bins, Bool_t projOnMee, std::vector<std::vector<Double_t>*> vBinnings);
  void                AddProjection(const TH1D *newproj, unsigned int histBit, Bool_t projOnMee); // copies the input histogram.
  void                CalcConfidenceLevel(Double_t CL, Bool_t projOnMee, Bool_t cockRef=kFALSE);
  void                InitFromRootfile(TString filename, Int_t ikey, TString dirname="");
  void                InitFromRootfile(TDirectory* dir);
  // output-related
  void                PrintUnlike(const Char_t* filename = "c2DUnlike.pdf");
  void                PrintSig(const Char_t* filename = "c2DSig.pdf");
  void                PrintSoverB(const Char_t* filename = "c2DSoverB.pdf");
  void                PrintSignif(const Char_t* filename = "c2DSignif.pdf");
  void                WriteHist1D(unsigned int histBits, const std::vector<Double_t> bins, Bool_t simplehistnames, Bool_t projOnMee, TString signame="");
  void                WriteHist2D(unsigned int histBits, Bool_t divideByBinWidth, Bool_t simplehistnames);
  void                WriteHist3D(unsigned int histBits);
  // setters
  void                SetName(const std::string name)     { fName   = name; }
  void                SetUnlike2D(const TH2D* hist)       { fUnlike = new TH2D(*hist); }
  void                SetBkg2D(   const TH2D* hist)       { fBkg    = new TH2D(*hist); }
  void                SetSubSig2D(const TH2D* hist)       { fSubSig = new TH2D(*hist); }
  void                SetUnlikeNoEffi2D(const TH2D* hist) { fUnlikeNoEffi = new TH2D(*hist); }
  void                SetBkgNoEffi2D(const TH2D* hist)    { fBkgNoEffi    = new TH2D(*hist); }
  void                SetSigNoEffi2D(const TH2D* hist)    { fSigNoEffi    = new TH2D(*hist); }
  void                SetManager(const LmManager* man, Bool_t copyHist) { fLmMgr = new LmManager(*man, copyHist); fOwnerMgr=kTRUE; } // using copy constructor of LmManager.
  void                SetDoSubtraction(bool SDS=kTRUE)    { fDoSubtraction = SDS; }
  void                SetSubtractionDone(bool SSD=kTRUE)  { fSubtractionDone = SSD; } ///< Also called by LmHandler::SetDoSystOnUnlikeSign() to compute systematics on Unlike Sign.
  void                SetEffiApplied(bool SEA=kTRUE)      { fEffiApplied = SEA; } // should be made internal(private)!
  void                SetAcceApplied(bool SAA=kTRUE)      { fAcceApplied = SAA; } // should be made internal(private)!
  void                SetDoSignifRaw(bool SDSR=kTRUE)     { fDoSignifRaw = SDSR; }
//void                SetDoAcceCorr(bool SDAC=kTRUE)      { fDoAcceCorr = SDAC; }
//void                SetNeventsPhysSel(Double_t newevts) { fNeventsPhysSel = newevts; } // in Base class
//void                SetDoNormBinwidth(bool SDNB=kTRUE)  { fDoNormBinwidth = SDNB; } // in Base class
//void                SetDoNormNevents(bool SDNN=kTRUE)   { fDoNormNevents = SDNN; } // in Base class
  void                SetSymmetricRelSystematics(TH2D *h) { fSymmetricRelSystematics = new TH2D(*h); }
  void                SetRelSystematicsLow(TH2D *h)       { fRelSystematicsLow  = new TH2D(*h); } ///< Binning may be different from SymmetricRelSystematics.
  void                SetRelSystematicsHigh(TH2D *h)      { fRelSystematicsHigh = new TH2D(*h); } ///< Binning of Low and High may be different.
  // getters
  const char*         GetName()             const { return fName.c_str(); } 
  const char*         GetTypename()         const { return fTypename.c_str(); }
  const char*         GetSigName()          const { return GetSig2D()->GetName(); }
  TH2D*               GetSig2D()            const { if (fSubSig && fSubtractionDone) return fSubSig; else return fUnlike; } ///< Checking 'fSubtractionDone' is needed for LmHandler::SetDoSystOnUnlikeSign().
  TH2D*               GetUnlike2D()         const { return fUnlike; }
  TH2D*               GetBkg2D()            const { return fBkg; }
  TH2D*               GetSubSig2D()         const { return fSubSig; }
  TH2D*               GetUnlikeNoEffi2D()   const { return fUnlikeNoEffi; }
  TH2D*               GetBkgNoEffi2D()      const { return fBkgNoEffi; }
  TH2D*               GetSigNoEffi2D()      const { return fSigNoEffi; }
  TH2D*               GetSoverB()           const { if (fSoverB) return fSoverB; else return 0x0; }
  TH2D*               GetSignif()           const { if (fSignifSplus2B) return fSignifSplus2B; else return 0x0; }
  /*const*/ LmManager*    GetManager()      const { return fLmMgr; }
 /*const*/ LmManager*   ModifyManager()           { return fLmMgr; }
  const LmBackground* GetLmBackground()     const { return fLmBkg; }
  Bool_t              GetDoSubtraction()    const { return fDoSubtraction; }
  Bool_t              GetSubtractionDone()  const { return fSubtractionDone; }
  Bool_t              GetEffiApplied()      const { return fEffiApplied; }
  Bool_t              GetAcceApplied()      const { return fAcceApplied; }
  Bool_t              GetDoSignifRaw()      const { return fDoSignifRaw; }
  //Bool_t              GetDoAcceCorr()       const { return fDoAcceCorr; }
  TH2D*               GetSystematicLow()    const { return fSystematicLow; }
  TH2D*               GetSystematicHigh()   const { return fSystematicHigh; }
  Bool_t              HasSystematic()       const { if(fSystematicLow || fSystematicHigh) return kTRUE; else return kFALSE; };
//Double_t            GetNeventsPhysSel()   const { return fNeventsPhysSel; } // in Base class
//Bool_t              GetDoNormBinwidth()   const { return fDoNormBinwidth; } // in Base class
//Bool_t              GetDoNormNevents()    const { return fDoNormNevents; } // in Base class
  LmHistogram*        GetLmHist(unsigned int histBit, Int_t bin, Bool_t projOnMee) const; // Generic getter using histBits
  TGraphAsymmErrors*  GetSystematicGraph(unsigned int histBit, Int_t bin, Bool_t projOnMee) const;
  Int_t               GetMaxBinProj(Bool_t projOnMee)         const { if (projOnMee==LmBaseSignal::kProjOnMee) return GetMaxBin_projMee(); else return GetMaxBin_projPtee(); } // not unsigned because it can be -1 in case of empty vector!
  LmHistogram*        GetSubSig(Int_t bin, Bool_t projOnMee)  const { if (projOnMee==LmBaseSignal::kProjOnMee) return GetSubSig_Mee(bin);  else return GetSubSig_Ptee(bin); }
  LmHistogram*        GetUnlike(Int_t bin, Bool_t projOnMee)  const { if (projOnMee==LmBaseSignal::kProjOnMee) return GetUnlike_Mee(bin);  else return GetUnlike_Ptee(bin); }
  LmHistogram*        GetBkg(Int_t bin, Bool_t projOnMee)     const { if (projOnMee==LmBaseSignal::kProjOnMee) return GetBkg_Mee(bin);     else return GetBkg_Ptee(bin); }
  LmHistogram*        GetRfactor(Int_t bin, Bool_t projOnMee) const { if (projOnMee==LmBaseSignal::kProjOnMee) return GetRfactor_Mee(bin); else return GetRfactor_Ptee(bin); }
  LmHistogram*        GetSoverB(Int_t bin, Bool_t projOnMee)  const { if (projOnMee==LmBaseSignal::kProjOnMee) return GetSoverB_Mee(bin);  else return GetSoverB_Ptee(bin); }
  LmHistogram*        GetSignif(Int_t bin, Bool_t projOnMee)  const { if (projOnMee==LmBaseSignal::kProjOnMee) return GetSignif_Mee(bin);  else return GetSignif_Ptee(bin); }
  LmHistogram*        GetUnlikeMix(Int_t bin, Bool_t projOnMee) const { if (projOnMee==LmBaseSignal::kProjOnMee) return GetUnlikeMix_Mee(bin); else return GetUnlikeMix_Ptee(bin); }
  LmHistogram*        GetLikeMix(Int_t bin, Bool_t projOnMee)   const { if (projOnMee==LmBaseSignal::kProjOnMee) return GetLikeMix_Mee(bin);   else return GetLikeMix_Ptee(bin); }
  TH1D*               GetUnlikeNoEffiUnnorm(Int_t bin, Bool_t projOnMee) const { if (projOnMee==LmBaseSignal::kProjOnMee) return GetUnlikeNoEffiUnnorm_Mee(bin); else return GetUnlikeNoEffiUnnorm_Ptee(bin); }
  TH1D*               GetBkgNoEffiUnnorm(Int_t bin, Bool_t projOnMee)    const { if (projOnMee==LmBaseSignal::kProjOnMee) return GetBkgNoEffiUnnorm_Mee(bin);    else return GetBkgNoEffiUnnorm_Ptee(bin); }
  TGraphAsymmErrors*  GetSubSigSystematicGraph(Int_t bin, Bool_t projOnMee) const { return GetSubSig(bin,projOnMee)->GetSystError(); }
  UInt_t              GetNVisualSig()       const { if (fLmMgr) return fLmMgr->GetNVisualSig(); else return 0; }
  LmSignal*           GetVisualSigI(UInt_t i) const; ///< Create LmSignal from some visualization histogram and return it.
  
  const char*         GetCharHistBit(unsigned int histBit, Bool_t shortname=kFALSE);
  static const char*  GetCharHistBitStatic(unsigned int histBit, Bool_t shortname=kFALSE, Bool_t subtracted=kTRUE, Bool_t signifraw=kTRUE);
  
  enum enType {
    kNoProcess=0, ///< No specific Type.
    kStd,
    kCombined,
    kAverage,
    kWeightedAverage,
    kSystematic,  ///< Make LmSignal with systematic uncertainties for plotting
    kExternalBG,
    kExternal1D,  ///< Uses 1D histograms from an external source to fill the projection vectors.
    kExternal2D,  ///< Uses 2D histograms from a rootfile to construct an almost fully functional LmSignal.
    kAcceCorrection2D,
    kMAX
  };
  
//enum projAxis { // in Base class
//  kProjOnPtee=0,
//  kProjOnMee =1
//};
  
  enum histBits {
    kSubSig   = 1<<0,
    kUnlike   = 1<<1,
    kBkg      = 1<<2,
    kRfactor  = 1<<3,
    kSoverB   = 1<<4,
    kSignif   = 1<<5,
    kUnlikeMix= 1<<6,
    kLikeMix  = 1<<7,
    kSigNoEffi    = 1<<8,
    kUnlikeNoEffi = 1<<9,
    kBkgNoEffi    = 1<<10,
    kMAXhist      = 1<<11 // Upper limit for loops & checks. To select all histograms, use kMAXhist-1.
  };
  
private:
  TH2D*         CalcSubtractedSignal(const TH2D* hUnlike, const TH2D* hLike, const Char_t* newname);
  void          UpdateTitleSubtracted(TH2D* hSub);
  TH2D*         CalcSignalBackgroundRatio2D(const TH2D* hSignal, const TH2D* hBackground, const Char_t* newname);
  TH1D*         CalcSignalBackgroundRatio1D(const TH1D* hSignal, const TH1D* hBackground, const Char_t* newname);
  TH2D*         CalcSignificance2D(const TH2D* hSignal, const TH2D* hBackground, const Char_t* newname);
  TH1D*         CalcSignificance1D(const TH1D* hSignal, const TH1D* hBackground, const Char_t* newname);
  void          ApplyEfficiency2D(TH2D& hIn, const TH2D* hEffi);
  void          ApplyEfficiency2D_all(const TH2D* hEffi);
  void          ApplyAcceptance2D(const TH2D* hAcce);
  void          Rebin2DHistogram_all();
  void          MakeSpectra1D_Mee(Double_t valmin, Double_t valmax, std::vector<Double_t> *binning=0x0);
  void          MakeSpectra1D_Ptee(Double_t valmin, Double_t valmax, std::vector<Double_t> *binning=0x0);
// in Base class:
//TH1D*         DoProjectionMee(const TH2D* hIn, Double_t lowpT, Double_t highpT, Bool_t normBinw, Bool_t normNev);
//TH1D*         DoProjectionPtee(const TH2D* hIn, Double_t lowMee, Double_t highMee, Bool_t normBinw, Bool_t normNev);
//void          NormalizeBinwidth(TH1D& hIn);
//void          NormalizeNevents(TH1D& hIn);
  void          AttachSubSig_Mee(TH1D &newproj)               { fSubSig_projMee.push_back(  new LmHistogram(&newproj)); } // these functions do not copy the input histogram. see constructor LmHistogram::LmHistogram(TH1D* datapoints).
  void          AttachSubSig_Ptee(TH1D &newproj)              { fSubSig_projPtee.push_back( new LmHistogram(&newproj)); }
  void          AttachUnlike_Mee(TH1D &newproj)               { fUnlike_projMee.push_back(  new LmHistogram(&newproj)); }
  void          AttachUnlike_Ptee(TH1D &newproj)              { fUnlike_projPtee.push_back( new LmHistogram(&newproj)); }
  void          AttachBkg_Mee(TH1D &newproj)                  { fBkg_projMee.push_back(     new LmHistogram(&newproj)); }
  void          AttachBkg_Ptee(TH1D &newproj)                 { fBkg_projPtee.push_back(    new LmHistogram(&newproj)); }
  void          AttachRfactor_Mee(TH1D &newproj)              { fRfactor_projMee.push_back( new LmHistogram(&newproj)); }
  void          AttachRfactor_Ptee(TH1D &newproj)             { fRfactor_projPtee.push_back(new LmHistogram(&newproj)); }
  void          AttachSoverB_Mee(TH1D &newproj)               { fSoverB_projMee.push_back(  new LmHistogram(&newproj)); }
  void          AttachSoverB_Ptee(TH1D &newproj)              { fSoverB_projPtee.push_back( new LmHistogram(&newproj)); }
  void          AttachSignif_Mee(TH1D &newproj)               { fSignif_projMee.push_back(  new LmHistogram(&newproj)); }
  void          AttachSignif_Ptee(TH1D &newproj)              { fSignif_projPtee.push_back( new LmHistogram(&newproj)); }
  void          AttachUnlikeMix_Mee(TH1D &newproj)            { fUnlikeMix_projMee.push_back( new LmHistogram(&newproj)); }
  void          AttachUnlikeMix_Ptee(TH1D &newproj)           { fUnlikeMix_projPtee.push_back(new LmHistogram(&newproj)); }
  void          AttachLikeMix_Mee(TH1D &newproj)              { fLikeMix_projMee.push_back(   new LmHistogram(&newproj)); }
  void          AttachLikeMix_Ptee(TH1D &newproj)             { fLikeMix_projPtee.push_back(  new LmHistogram(&newproj)); }
  void          AttachUnlikeNoEffiUnnorm_Mee(TH1D &newproj)   { fUnlikeNoEffiUnnorm_projMee.push_back( &newproj); }
  void          AttachUnlikeNoEffiUnnorm_Ptee(TH1D &newproj)  { fUnlikeNoEffiUnnorm_projPtee.push_back(&newproj); }
  void          AttachBkgNoEffiUnnorm_Mee(TH1D &newproj)      { fBkgNoEffiUnnorm_projMee.push_back(    &newproj); }
  void          AttachBkgNoEffiUnnorm_Ptee(TH1D &newproj)     { fBkgNoEffiUnnorm_projPtee.push_back(   &newproj); }
  void          MakeSystematicHistos();
  void          AttachSystematicGraph_Mee(TH1D *hSubSig, TH1D *hSysLow, TH1D *hSysHigh);
  void          AttachSystematicGraph_Ptee(TH1D *hSubSig, TH1D *hSysLow, TH1D *hSysHigh);
  
  // private getters for projections. please use generalized public version for better maintenance.
  ///@TODO:  Warning: not all projections must have the same number of entries...! should be fixed somehow.
  Int_t         GetMaxBin_projMee()                           const { return fSubSig_projMee.size()-1; } // not unsigned because it can be -1 in case of empty vector!
  Int_t         GetMaxBin_projPtee()                          const { return fSubSig_projPtee.size()-1; } // not unsigned because it can be -1 in case of empty vector!
  LmHistogram*  GetSubSig_Mee(Int_t bin)                      const { CheckRange("SubSig_Mee"  ,bin,fSubSig_projMee.size());   return fSubSig_projMee.at(bin); }
  LmHistogram*  GetSubSig_Ptee(Int_t bin)                     const { CheckRange("SubSig_Ptee" ,bin,fSubSig_projPtee.size());  return fSubSig_projPtee.at(bin); }
  LmHistogram*  GetUnlike_Mee(Int_t bin)                      const { CheckRange("Unlike_Mee"  ,bin,fUnlike_projMee.size());   return fUnlike_projMee.at(bin); }
  LmHistogram*  GetUnlike_Ptee(Int_t bin)                     const { CheckRange("Unlike_Ptee" ,bin,fUnlike_projPtee.size());  return fUnlike_projPtee.at(bin); }
  LmHistogram*  GetBkg_Mee(Int_t bin)                         const { CheckRange("Bkg_Mee"     ,bin,fBkg_projMee.size());      return fBkg_projMee.at(bin); }
  LmHistogram*  GetBkg_Ptee(Int_t bin)                        const { CheckRange("Bkg_Ptee"    ,bin,fBkg_projPtee.size());     return fBkg_projPtee.at(bin); }
  LmHistogram*  GetRfactor_Mee(Int_t bin)                     const { CheckRange("Rfactor_Mee" ,bin,fRfactor_projMee.size());  return fRfactor_projMee.at(bin); }
  LmHistogram*  GetRfactor_Ptee(Int_t bin)                    const { CheckRange("Rfactor_Ptee",bin,fRfactor_projPtee.size()); return fRfactor_projPtee.at(bin); }
  LmHistogram*  GetSoverB_Mee(Int_t bin)                      const { CheckRange("SoverB_Mee"  ,bin,fSoverB_projMee.size());   return fSoverB_projMee.at(bin); }
  LmHistogram*  GetSoverB_Ptee(Int_t bin)                     const { CheckRange("SoverB_Ptee" ,bin,fSoverB_projPtee.size());  return fSoverB_projPtee.at(bin); }
  LmHistogram*  GetSignif_Mee(Int_t bin)                      const { CheckRange("Signif_Mee"  ,bin,fSignif_projMee.size());   return fSignif_projMee.at(bin); }
  LmHistogram*  GetSignif_Ptee(Int_t bin)                     const { CheckRange("Signif_Ptee" ,bin,fSignif_projPtee.size());  return fSignif_projPtee.at(bin); }
  LmHistogram*  GetUnlikeMix_Mee(Int_t bin)                   const { CheckRange("UnlikeMix_Mee"  ,bin,fUnlikeMix_projMee.size());  return fUnlikeMix_projMee.at(bin); }
  LmHistogram*  GetUnlikeMix_Ptee(Int_t bin)                  const { CheckRange("UnlikeMix_Ptee" ,bin,fUnlikeMix_projPtee.size()); return fUnlikeMix_projPtee.at(bin); }
  LmHistogram*  GetLikeMix_Mee(Int_t bin)                     const { CheckRange("LikeMix_Mee"    ,bin,fLikeMix_projMee.size());    return fLikeMix_projMee.at(bin); }
  LmHistogram*  GetLikeMix_Ptee(Int_t bin)                    const { CheckRange("LikeMix_Ptee"   ,bin,fLikeMix_projPtee.size());   return fLikeMix_projPtee.at(bin); }
  TH1D*         GetUnlikeNoEffiUnnorm_Mee(Int_t bin)          const { CheckRange("UnlikeNoEff_Mee"  ,bin,fUnlikeNoEffiUnnorm_projMee.size());  return fUnlikeNoEffiUnnorm_projMee.at(bin); }
  TH1D*         GetUnlikeNoEffiUnnorm_Ptee(Int_t bin)         const { CheckRange("UnlikeNoEff_Ptee" ,bin,fUnlikeNoEffiUnnorm_projPtee.size()); return fUnlikeNoEffiUnnorm_projPtee.at(bin); }
  TH1D*         GetBkgNoEffiUnnorm_Mee(Int_t bin)             const { CheckRange("BkgNoEff_Mee"     ,bin,fBkgNoEffiUnnorm_projMee.size());     return fBkgNoEffiUnnorm_projMee.at(bin); }
  TH1D*         GetBkgNoEffiUnnorm_Ptee(Int_t bin)            const { CheckRange("BkgNoEff_Ptee"    ,bin,fBkgNoEffiUnnorm_projPtee.size());    return fBkgNoEffiUnnorm_projPtee.at(bin); }
  void          CheckRange(const Char_t* fcn, unsigned int bin, unsigned int size) const {
    /**/          if (bin>=size) { LmHelper::Error(Form("LmSignal::Get%s(bin=%i) out of range (size=%i)! (name=%s)",fcn,bin,size,GetName())); }
    /**/        } // would be even more elegant to make this function not void but "Type CheckRange(bin, std::vector<Type>)" and return the element after the check.
  Bool_t        CheckAndDeleteOldProjections(Bool_t projOnMe);
  
  // variables
  // make sure to initialize all pointer variables in the constructor(s)!
  // otherwise something like 'if(fSubSig){}' will crash and it is difficult to find the reason!
  std::string  	fName;
  Int_t         fType;
  std::string   fTypename;
  LmManager*    fLmMgr;
  LmBackground* fLmBkg;
  TH2D*         fUnlike; // copy of the ULS from the manager
  TH2D*         fBkg;    // copy of the Bkg from the background
  TH2D*         fSubSig;
  TH2D*         fUnlikeNoEffi;  // needed for confidence level calculations. (non-trivial to determine the correct 1D efficiency, more convenient to work with sensitivity=1.)
  TH2D*         fBkgNoEffi;     // needed for significance, which must always be done before efficiency correction, also in the 1D case!
  TH2D*         fSigNoEffi;     // (same-as-above) + Warning: could be subtracted or unsubtracted!
  TH2D*         fSoverB;        // not needed for anything except a 2D-plot. SoverB has to be calculated from projected spectra.
  TH2D*         fSignifSplusB;  // not needed for anything except a 2D-plot. Significance has to be calculated from projected spectra.
  TH2D*         fSignifSplus2B; // not needed for anything except a 2D-plot. Significance has to be calculated from projected spectra.
  Bool_t        fDoSubtraction;
  Bool_t        fSubtractionDone;
  Bool_t        fEffiApplied;
  Bool_t        fAcceApplied;
  Bool_t        fDoSignifRaw;
  //Bool_t        fDoAcceCorr;
  Bool_t        fOwnerMgr;
//Double_t      fNeventsPhysSel; // in Base class
//Bool_t        fDoNormBinwidth; // in Base class
//Bool_t        fDoNormNevents; // in Base class
  
  std::vector<LmHistogram*> fSubSig_projMee; // the last projection is integrated over all bins
  std::vector<LmHistogram*> fSubSig_projPtee;
  std::vector<LmHistogram*> fUnlike_projMee;
  std::vector<LmHistogram*> fUnlike_projPtee;
  std::vector<LmHistogram*> fBkg_projMee;
  std::vector<LmHistogram*> fBkg_projPtee;
  std::vector<LmHistogram*> fRfactor_projMee;
  std::vector<LmHistogram*> fRfactor_projPtee;
  std::vector<LmHistogram*> fSoverB_projMee;
  std::vector<LmHistogram*> fSoverB_projPtee;
  std::vector<LmHistogram*> fSignif_projMee;
  std::vector<LmHistogram*> fSignif_projPtee;
  std::vector<LmHistogram*> fUnlikeMix_projMee;
  std::vector<LmHistogram*> fUnlikeMix_projPtee;
  std::vector<LmHistogram*> fLikeMix_projMee;
  std::vector<LmHistogram*> fLikeMix_projPtee;
  std::vector<TH1D*>        fUnlikeNoEffiUnnorm_projMee;
  std::vector<TH1D*>        fUnlikeNoEffiUnnorm_projPtee;
  std::vector<TH1D*>        fBkgNoEffiUnnorm_projMee;
  std::vector<TH1D*>        fBkgNoEffiUnnorm_projPtee;
  
  // systematic uncertainties
  TH2D*                           fSymmetricRelSystematics;
  TH2D*                           fRelSystematicsLow;
  TH2D*                           fRelSystematicsHigh;
  TH2D*                           fSystematicLow;
  TH2D*                           fSystematicHigh;
  //std::vector<TGraphAsymmErrors*> fSubSigSystematic_projMee; // now stored in LmHistogram
  //std::vector<TGraphAsymmErrors*> fSubSigSystematic_projPtee;
  
};

#endif
