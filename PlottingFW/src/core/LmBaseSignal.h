#ifndef LMBASESIGNAL_H
#define LMBASESIGNAL_H

// c++ includes
// ROOT includes
#include "TH1.h"
#include "TH2.h"
#include "TString.h"
// project includes
#include "LmHistogram.h"
#include "LmHelper.h"

class LmBaseSignal {

public:

  enum projAxis {
    kUndef=-1,
    kProjOnPtee=0,
    kProjOnY=kProjOnPtee,
    kProjOnMee =1, // the order has historic reasons (projOnMee=x=1=kTRUE was nice for coding)
    kProjOnX=kProjOnMee
  };
  
  enum inputAxis {
    kInpUndef=-1,
    kInputX=0,
    kInputY=1,
    kInputZ=2
  };
 
  enum normalisations {
    kNoNormalisation  = 0,
    kNormBinWidth     = 1,
    kNormNevents      = 2,
    kNormNentries     = 4,
    kNormCrossSection = 8,
    kNormTrgEff       = 16,
    kNormRecEff       = 32,
    kNormVtxRecEff    = 64,
    kNormVtxRecEffee  = 128 
  };

  // setters
  void          SetNeventsPhysSel(Double_t newevts)       { fNeventsPhysSel = newevts; }
  void          SetCrossSection(Double_t crosssection)    { fCrossSection   = crosssection; }
  void          SetTrgEff(Double_t TrgEff)                { fTrgEff   = TrgEff; }
  void          SetVtxRecEff(Double_t VtxRecEff)          { fVtxRecEff   = VtxRecEff; }
  void          SetVtxRecEffee(Double_t VtxRecEffee)      { fVtxRecEff_ee   = VtxRecEffee; }

  void          SetDoAcceCorr(bool SDAC=kTRUE)            { fDoAcceCorr = SDAC; }
  //void          SetDoNormBinwidth(bool SDNB=kTRUE)        { fDoNormBinwidth = SDNB; }
  //void          SetDoNormNevents (bool SDNN=kTRUE)        { fDoNormNevents  = SDNN; }
  //void          SetDoNormNentries(bool SDNN=kTRUE)        { fDoNormNentries = SDNN; }
  //void          SetDoNormCrossSection(bool SDNCS=kTRUE)   { fDoNormCrossSection = SDNCS; }
  //void          SetDoNormTrgEff(bool SDNTE=kTRUE)         { fDoNormTrgEff = SDNTE; }
  //void          SetDoNormRecEff(bool SDNRE=kTRUE)         { fDoNormRecEff = SDNRE; }
  //void          SetDoNormVtxRecEff(bool SDNVRE=kTRUE)     { fDoNormVtxRecEff = SDNVRE; }
  //void          SetDoNormVtxRecEffee(bool SDNVREee=kTRUE) { fDoNormVtxRecEff_ee = SDNVREee; }
  
  void          SetDoNormBinwidth     (bool b=kTRUE)  { b ? fNormalisations |= kNormBinWidth     : fNormalisations &= ~kNormBinWidth     ; }
  void          SetDoNormNevents      (bool b=kTRUE)  { b ? fNormalisations |= kNormNevents      : fNormalisations &= ~kNormNevents      ; } 
  void          SetDoNormNentries     (bool b=kTRUE)  { b ? fNormalisations |= kNormNentries     : fNormalisations &= ~kNormNentries     ; } 
  void          SetDoNormCrossSection (bool b=kTRUE)  { b ? fNormalisations |= kNormCrossSection : fNormalisations &= ~kNormCrossSection ; } 
  void          SetDoNormTrgEff       (bool b=kTRUE)  { b ? fNormalisations |= kNormTrgEff       : fNormalisations &= ~kNormTrgEff       ; } 
  void          SetDoNormRecEff       (bool b=kTRUE)  { b ? fNormalisations |= kNormRecEff       : fNormalisations &= ~kNormRecEff       ; } 
  void          SetDoNormVtxRecEff    (bool b=kTRUE)  { b ? fNormalisations |= kNormVtxRecEff    : fNormalisations &= ~kNormVtxRecEff    ; } 
  void          SetDoNormVtxRecEffee  (bool b=kTRUE)  { b ? fNormalisations |= kNormVtxRecEffee  : fNormalisations &= ~kNormVtxRecEffee  ; } 

  void          SetDoExtendedTitle      (bool b=kFALSE) { fDoExtendedTitle = b; }
 
  // getters
  Double_t      GetNeventsPhysSel() const     { return fNeventsPhysSel; }
  Double_t      GetCrossSection() const       { return fCrossSection; }
  Double_t      GetTrgEff() const             { return fTrgEff; }
  Double_t      GetVtxRecEff() const          { return fVtxRecEff; }
  Double_t      GetVtxRecEffee() const        { return fVtxRecEff_ee; }

  Bool_t        GetDoAcceCorr() const         { return fDoAcceCorr; }
  Bool_t        GetDoNormBinwidth() const     { return fNormalisations & kNormBinWidth    ; }
  Bool_t        GetDoNormNevents() const      { return fNormalisations & kNormNevents     ; } 
  Bool_t        GetDoNormNentries() const     { return fNormalisations & kNormNentries    ; } 
  Bool_t        GetDoNormCrossSection() const { return fNormalisations & kNormCrossSection; } 
  Bool_t        GetDoNormTrgEff() const       { return fNormalisations & kNormTrgEff      ; } 
  Bool_t        GetDoNormRecEff() const       { return fNormalisations & kNormRecEff      ; } 
  Bool_t        GetDoNormVtxRecEff() const    { return fNormalisations & kNormVtxRecEff   ; } 
  Bool_t        GetDoNormVtxRecEffee() const  { return fNormalisations & kNormVtxRecEffee ; } 

  Bool_t        GetDoExtendedTitle() const    { return fDoExtendedTitle; }
  
  // static
  static void   SetInputLabelX(const char* var, const char* unit, const char* text=""); ///< Sets x-axis label of input spectra. Specify variable and its unit without ( ). Give plain text for canvas names.
  static void   SetInputLabelY(const char* var, const char* unit, const char* text=""); ///< Sets y-axis label of input spectra. Specify variable and its unit without ( ). Give plain text for canvas names.
  static void   SetInputLabelZ(const char* var, const char* unit, const char* text=""); ///< Sets z-axis label of input spectra. Specify variable and its unit without ( ). Give plain text for canvas names.
  static void   SetInputLabelContent(const char* var="", const char* unit="a.u."); ///< Called automatically. Sets content (yield) label of input spectra. Computes it from axis labels if 'var' is empty. Give unit without ( ).
  static void   SetLabelSig(const char* var) { fsLabelSig=var; } //< To change y-label in S/B and significance plots.
  static void   SetLabelBkg(const char* var) { fsLabelBkg=var; } //< To change y-label in S/B and significance plots.
  
  static void   CorrelateAxesOfInputAndProjections(const char* option);
  
  static TString  GetInputLabelContent();
  static TString  GetInputLabelX()      { return (TString) fsInputTexX+" ("+fsInputTexXunit+")"; }
  static TString  GetInputLabelXvar()   { return (TString) fsInputTexX; }
  static TString  GetInputLabelXunit()  { return (TString) fsInputTexXunit; }
  static TString  GetInputLabelY()      { return (TString) fsInputTexY+" ("+fsInputTexYunit+")"; }
  static TString  GetInputLabelYvar()   { return (TString) fsInputTexY; }
  static TString  GetInputLabelYunit()  { return (TString) fsInputTexYunit; }
  static TString  GetInputLabelZ()      { return (TString) fsInputTexZ+" ("+fsInputTexZunit+")"; }
  static TString  GetInputLabelZvar()   { return (TString) fsInputTexZ; }
  static TString  GetInputLabelZunit()  { return (TString) fsInputTexZunit; }

  static TString  GetProjLabelContent();
  static TString  GetProjLabelX()       { return GetProjLabel(fWhatIsX); }
  static TString  GetProjLabelY()       { return GetProjLabel(fWhatIsY); }
  static TString  GetProjLabelZ()       { return GetProjLabel(fWhatIsZ); }
  static TString  GetProjLabelXvar()    { return GetProjLabelvar(fWhatIsX); }
  static TString  GetProjLabelYvar()    { return GetProjLabelvar(fWhatIsY); }
  static TString  GetProjLabelZvar()    { return GetProjLabelvar(fWhatIsZ); }
  static TString  GetProjLabelXunit()   { return GetProjLabelunit(fWhatIsX); }
  static TString  GetProjLabelYunit()   { return GetProjLabelunit(fWhatIsY); }
  static TString  GetProjLabelZunit()   { return GetProjLabelunit(fWhatIsZ); }
  
  

 
  static LmBaseSignal::projAxis  CheckWhichProjection(TH1* hist); ///< Returns if 'hist' is a x- or y-projection of the 2D-signal. Check is based on its x-axis label.
  static LmBaseSignal::inputAxis CheckWhichInputAxis(TH1* hist); ///< Returns if 'hist' is a x-, y- or z-projection of the 3D-input. Check is based on its x-axis label.
  static LmBaseSignal::inputAxis CheckWhichInputAxis(TAxis* axis);
  static TAxis*   GetInputXaxis(TH2* hist);
  static TAxis*   GetInputYaxis(TH2* hist);
  static TAxis*   GetInputZaxis(TH2* hist);
  
  static TString  GetInputAxisCode(inputAxis iaxis); // don't use enum projAxis!
  
  
protected:
  TH1D*         DoProjectionMee(const TH2D* hIn, Double_t lowpT, Double_t highpT, /*Bool_t normBinw, Bool_t normNev, Bool_t normNent = kFALSE,*/ UInt_t normalisation, Bool_t debugTitles = kFALSE, std::vector<Double_t> *binning=0x0);
  TH1D*         DoProjectionPtee(const TH2D* hIn, Double_t lowMee, Double_t highMee, /*Bool_t normBinw, Bool_t normNev, Bool_t normNent = kFALSE,*/ UInt_t normalisation, Bool_t debugTitles = kFALSE, std::vector<Double_t> *binning=0x0);
  void          NormalizeBinwidth(TH1D& hIn);
  void          NormalizeNevents(TH1D& hIn);
  void          NormalizeNentries(TH1D& hIn);
  void          NormalizeCrossSection(TH1D& hIn);
  void          NormalizeTrgEff(TH1D& hIn);
  void          NormalizeRecEff(TH1D& hIn);
  void          NormalizeVtxRecEff(TH1D& hIn);
  void          NormalizeVtxRecEffee(TH1D& hIn);
  
  static TString  GetProjLabel(inputAxis iaxis); // don't use enum projAxis!
  static TString  GetProjLabelvar(inputAxis iaxis); // don't use enum projAxis!
  static TString  GetProjLabelunit(inputAxis iaxis); // don't use enum projAxis!
  static TString  GetLabelSig() { return fsLabelSig; }
  static TString  GetLabelBkg() { return fsLabelBkg; }
  
  // variables
  Double_t      fNeventsPhysSel;
  Double_t      fCrossSection;
  Double_t      fTrgEff;
  Double_t      fVtxRecEff;
  Double_t      fVtxRecEff_ee;
  Bool_t        fDoAcceCorr;
//  Bool_t        fDoNormBinwidth;
//  Bool_t        fDoNormNevents;
//  Bool_t        fDoNormNentries;
//  Bool_t        fDoNormCrossSection;
//  Bool_t        fDoNormTrgEff;
//  Bool_t        fDoNormRecEff_ee;
//  Bool_t        fDoNormVtxRecEff;
//  Bool_t        fDoNormVtxRecEff_ee;

  UInt_t        fNormalisations;
  Bool_t        fDoExtendedTitle;
  
private:
  // static variables
  // static TString/string sometimes cause fancy trouble when calling the combining functions GetInputLabelX()/Y/Z inside a Form() statement. complete recompilation helps.
  static TString     fsInputCodeX; // default "Mee"
  static TString     fsInputCodeY; // default "Ptee"
  static TString     fsInputCodeZ; // default <empty>. set it to e.g. "PhiV" or "DCAee".
  static TString     fsInputTexX;  // default "#it{m}_{ee}"
  static TString     fsInputTexY;  // default "#it{p}_{T,ee}"
  static TString     fsInputTexZ;  // default <empty>. set it to e.g. "#it{#phi}_{V}" or "#it{dca}_{ee}".
  static TString     fsInputTexXunit;
  static TString     fsInputTexYunit;
  static TString     fsInputTexZunit;
  static TString     fsInputTexContent;      // default <empty>. will be computed automatically if empty. e.g. "unsubtr. raw d#it{N}/d#it{m}_{ee}d#it{p}_{T,ee}"
  static TString     fsInputTexContentunit;  // default a.u.
  static inputAxis   fWhatIsX;    // Stores to which input axis the x-axis of the 2D-projection corresponds.
  static inputAxis   fWhatIsY;    // Stores to which input axis the y-axis of the 2D-projection corresponds.
  static inputAxis   fWhatIsZ;    // Since the projection is only 2D, this one corresponds to the axis over which the 3D input was integrated.
  static TString     fsLabelSig;  // for y-label in S/B and significance plots
  static TString     fsLabelBkg;  // for y-label in S/B and significance plots
  
};

#endif
