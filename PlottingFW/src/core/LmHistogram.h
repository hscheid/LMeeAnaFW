#ifndef LMHISTOGRAM_H
#define LMHISTOGRAM_H

// c++ includes
#include <vector>
// ROOT includes
#include "TCanvas.h"
#include "TH1.h"
#include "TAxis.h"
#include "TArrow.h"
#include "TString.h"
#include "TGraphAsymmErrors.h"
// project includes

class LmHistogram{
public:
  LmHistogram();
  LmHistogram(TH1D* h1);
  LmHistogram(const LmHistogram &obj);
  ~LmHistogram();

  // function declarations
  Bool_t        Divide(/*const*/ LmHistogram* obj, TString option = "");
  Bool_t        Divide(const TH1D* obj, TString option = "");
  Bool_t        Subtract(const TH1D* obj, const TGraphAsymmErrors* err=0x0, Double_t weight=1, TString option="");
  Bool_t        Add(const TH1D* obj, const TGraphAsymmErrors* err=0x0, Double_t weight=1, TString option="");

  // output-related
  void          Draw(const char* options = "");
  void          DrawCopy(const char* options = "");
  void          DrawClone(const char* options = "");
  // setters
  void          SetDatapoints(const TH1D* hist)                  { fDatahist = new TH1D(*hist); }
  void          SetSystError(const TGraphAsymmErrors* gr)        { fSystErr = new TGraphAsymmErrors(*gr); fSystErr->SetTitle("fSystErr"); }
  void          SetSystErrorCorrel(const TGraphAsymmErrors* gr)  { fSystErrCorrel = new TGraphAsymmErrors(*gr); fSystErrCorrel->SetTitle("fSystErrCorrel"); }
  void          AttachArrow(TArrow* arrow)                       { fArrow.push_back(arrow); }
  void          AttachArrow(TArrow* arrow, Double_t width)       { AttachArrow(arrow); AttachArrowBinWidth(width); }
  void          AttachArrowBinWidth(Double_t width)              { fArrowBinWidth.push_back(width); }
  void          SetAxisRange(Double_t xmin, Double_t xmax, const char* axis);
  void          SetLineColor(Int_t color);
  void          SetLineWidth(Int_t lwidth);
  void          SetLineStyle(Int_t lstyle);
  void          SetMarkerStyle(Int_t marker);
  void          SetMarkerColor(Int_t color);
  void          SetMarkerSize(Double_t size);
  void          SetFillStyle(Int_t fstyle);
  void          SetFillColor(Int_t color);
  void          SetFillColorAlpha(Int_t color, Int_t alpha);
  void          SetDrawOptions(const char* options) { fDrawOptions = options; }
  static void   SetDrawOptionsStatic(const char* options) { fDrawOptionsDefault = options; }
  void          SetIsRatio(bool SIR=kTRUE) { fIsRatio = SIR; }
  void          SetExternalObject(TObject *obj) { fExternalObj = obj; }
  void          SetExternalSystematicObject(TObject *obj) { fExternalSystematicObj = obj; }
  // getters
  TH1D*         GetDatahist()                 { return fDatahist; }
  TGraphAsymmErrors* GetSystError()           { return fSystErr; }
  TGraphAsymmErrors* GetSystErrorCorrel()     { return fSystErrCorrel; }
  TAxis*        GetXaxis()                    { return fDatahist->GetXaxis(); }
  TAxis*        GetYaxis()                    { return fDatahist->GetYaxis(); }
  TObject*      GetExternalObject()           { return fExternalObj; }
  TObject*      GetExternalSystematicObject() { return fExternalSystematicObj; }

private:
  enum enBinning {
    kUnchecked=0,
    kIdentical,
    kCompatible,
    kIncompatible
  };

  // functions
  void          DrawArrows();
  enBinning     CheckCompatibleBinning(const TH1D* h1, const TH1D* h2);
  Bool_t        MakeIdenticalBinning(  const TH1D* h1, TH1D &h2);
  void          DivideGraph(TGraphAsymmErrors* gr, const TH1D* hDenominator, TString option);
  void          AddGraph(TGraphAsymmErrors* gr, const TH1D* hSummand, Double_t weight, TString option);

  // switches
  Bool_t        fIsRatio;

  // variables
  TH1D*                 fDatahist;
  TGraphAsymmErrors*    fSystErr;
  TGraphAsymmErrors*    fSystErrCorrel;
  std::vector<TArrow*>  fArrow;
  std::vector<Double_t> fArrowBinWidth;
  TObject*              fExternalObj;
  TObject*              fExternalSystematicObj;
  TString               fDrawOptions;
  static TString        fDrawOptionsDefault;
};

#endif
