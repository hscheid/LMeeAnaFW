#ifndef LMFITTER_H
#define LMFITTER_H

// c++ includes
#include <vector>
// ROOT includes
// project includes
#include "LmFitFunctions.h"
// forward declarations
class TH1D;
class TF1;
class TGraphErrors;

class LmFitter {
public:
  LmFitter();
  //~LmFitter();

  // function declarations
  void          PrepareFitCharm(Double_t xmin=1.2, Double_t xmax=2.5);
  void          PrepareFitVirtPhot_Normalization(Double_t xnormmin=0., Double_t xnormmax=0.04, Bool_t NormToData=kFALSE);
  void          PrepareFitVirtPhot_Extraction(Double_t xmin=0.15, Double_t xmax=0.5);
  Int_t         Process(Int_t type=kUndef);
  // output-related
  void          PrintBestFit(TString filename = "cFitBest.pdf");
  void          PrintFitI(UInt_t counter, TString filename = "");
  void          PrintCompareFits(TString filename = "cFitCompare.pdf");
  void          PrintFitStatus(UInt_t counter = 9999);

  // setters
  void          SetDatahist(const TH1D* h)        { fDatahist = new TH1D(*h); }
  void          SetXmin(Double_t val)             { fXmin = val; }
  void          SetXmax(Double_t val)             { fXmax = val; }
  void          SetNpar(Int_t n)                  { fNpar = n; }
  void          SetFixPar(int i, Double_t val)    { fbFixPar[i] = kTRUE; fFixParVal[i] = val; }
  void          SetFreePar(int i)                 { fbFixPar[i] = kFALSE; }
  void          SetFitOpt(const char* opt)        { fsFitOpt = opt; }
  void          AttachFitTemplateA(const TH1D* h) { fFitTemplateA.push_back( new TH1D(*h)); }
  void          AttachFitTemplateB(const TH1D* h) { fFitTemplateB.push_back( new TH1D(*h)); }
  void          AttachFitTemplateC(const TH1D* h) { fFitTemplateC.push_back( new TH1D(*h)); } // only first entry used so far!
  void          SetTemplateNames(TString cA, TString cB="B", TString cC="C") { fTemplNameA=cA; fTemplNameB=cB; fTemplNameC=cC; }
  void          SetParNames(TString p0, TString p1="p1", TString p2="p2") { fParNames[0]=p0; fParNames[1]=p1; fParNames[2]=p2; }
  void          SetUseOnlyTemplatePairs(bool b=kTRUE) { fUseOnlyTemplatePairs = b; }
  // getters
  TH1D*         GetDatahist() const               { return fDatahist; }
  Bool_t        GetUseOnlyTemplatePairs() const   { return fUseOnlyTemplatePairs; }
  // get best:
  TH1D*         GetBestTemplateA() const          { return fFitTemplateA.at(GetWhichA_I(fIBestFit)); }
  TH1D*         GetBestTemplateB() const          { return fFitTemplateB.at(GetWhichB_I(fIBestFit)); }
  TH1D*         GetBestTemplateC() const          { return fFitTemplateC.at(GetWhichC_I(fIBestFit)); }
  TF1*          GetBestFitFcn() const             { return fvFitFcns.at(fIBestFit); }
  Double_t      GetBestChi2NDF() const            { return fvChi2NDF.at(fIBestFit); }
  // get I / 'counter':
  UInt_t        GetIBest() const                  { return fIBestFit; }
  TH1D*         GetTemplateA_I(UInt_t I) const    { return fFitTemplateA.at(GetWhichA_I(I)); }
  TH1D*         GetTemplateB_I(UInt_t I) const    { return fFitTemplateB.at(GetWhichB_I(I)); }
  TH1D*         GetTemplateC_I(UInt_t I) const    { return fFitTemplateC.at(GetWhichC_I(I)); }
  TF1*          GetFitFcn_I(UInt_t I) const       { return fvFitFcns.at(I); }
  TGraphErrors* GetConfidenceGr_I(UInt_t I) const { return fvConfidenceGrs.at(I); }
  Double_t      GetChi2NDF_I(UInt_t I) const      { return fvChi2NDF.at(I); }
  Int_t         GetFitStatus_I(UInt_t I) const    { return fvFitStatus.at(I); }
  Int_t         GetWhichA_I(UInt_t I) const       { return fvWhichA.at(I); }
  Int_t         GetWhichB_I(UInt_t I) const       { return fvWhichB.at(I); }
  Int_t         GetWhichC_I(UInt_t I) const       { return fvWhichC.at(I); }
  Double_t      GetNormA_I(UInt_t counter) const;
  Double_t      GetNormB_I(UInt_t counter) const;
  Double_t      GetNormC_I(UInt_t counter) const;
  Double_t      GetNormAB_I(UInt_t counter) const;

  enum enType {
    kUndef=0,
    kOneTempl,
    kTwoTempl,
    kTwoTempl_OneNorm,
    kThreeTempl,
    kThreeTempl_OneNorm_PlusBaseline
  };

private:

  // functions
  void          DoOneFit(UInt_t counter, UInt_t iA, UInt_t iB, UInt_t iC);
  void          ClearVectors(Bool_t clearNormAB=kTRUE);
  void          CleanupParams();

  // variables
  // make sure to initialize all pointer variables in the constructor(s)!
  // otherwise something like 'if(fDatahist){}' will crash and it is difficult to find the reason!
  Int_t         fType;
  LmFitFunctions* fFcnClass;
  TF1*          fFcnFit;
  TH1D*         fDatahist;
  Double_t      fXmin;
  Double_t      fXmax;
  Int_t         fNpar;
  TString       fParNames[9]; // change sizes in constructor accordingly
  Bool_t        fbFixPar[9];
  Double_t      fFixParVal[9];
  TString       fsFitOpt;
  Bool_t        fUseOnlyTemplatePairs;

  std::vector<TH1D*>    fFitTemplateA;
  std::vector<TH1D*>    fFitTemplateB;
  std::vector<TH1D*>    fFitTemplateC;
  // --- one entry for every fit: (all of them must be added in ClearVectors();
  std::vector<TF1*>     fvFitFcns;
  std::vector<TGraphErrors*> fvConfidenceGrs;
  std::vector<UInt_t>   fvWhichA;
  std::vector<UInt_t>   fvWhichB;
  std::vector<UInt_t>   fvWhichC;
  std::vector<Double_t> fvChi2NDF;
  std::vector<Int_t>    fvFitStatus;
  std::vector<Double_t> fvNormAB; // needed to store and later retrieve this parameter for second fit of virtual photon extraction.
  // ---
  TString       fTemplNameA;
  TString       fTemplNameB;
  TString       fTemplNameC;
  UInt_t        fIBestFit;
};

#endif
