#ifndef LMQA_H
#define LMQA_H

// c++ includes
// ROOT includes
#include "TString.h"
#include "TCollection.h"
#include "TH1D.h"
#include "TStyle.h"
// project includes
#include "LmHelper.h"
// forward declarations
class TCollection;
class TFile;
class TH1D;
class TCanvas;

class LmQA {
public:
  LmQA();
  LmQA(TString cconfig); // default argument needed for inheritance
  ~LmQA();

  // setters
  void          SetName(const std::string name)       { fName = name; }
  void          SetConfig(TString s)                  { fsConfiglong=s; }
  void          SetColorPalette(Int_t color/* = 55*/) { fColorPalette=color; gStyle->SetPalette(color); }
  void          SetDoRatio(bool SDR=1, Double_t ps=0.3/*, bool log=0*/) { fDoRatio = SDR; fRatioPadSize=ps; /*fPlotRatioLogy=log;*/ } ///< Activate plotting of ratio, set relative size of ratio pad, set logy.
  void          SetDoNormNEvents(bool norm = 0)       { fDoNormNEvents = norm; }
  void          SetDoNormNEntries(bool norm = 0)      { fDoNormNEntries = norm; }
  void          SetRebinning(Int_t rebin = 0)         { fRebin = rebin; }
  // getters
  const char*   GetName()           const { return fName.c_str(); }
  double        GetNumberOfEvents();
  Double_t      GetEtaRange_min()   const { return feta_range_min; }
  Double_t      GetEtaRange_max()   const { return feta_range_max; }
  Double_t      GetPtRange_min()    const { return fpt_range_min; }
  Double_t      GetPtRange_max()    const { return fpt_range_max; }
  Double_t      GetCentrality_min() const { return fcentrality_min; }
  Double_t      GetCentrality_max() const { return fcentrality_max; }
  Int_t         GetColorPalette()   const { return fColorPalette; }

  void          PrintCentrality(TString filename = "centrality.pdf");

  void          PrintEPTPC(TString filename = "epTPC.pdf");
  void          PrintEPV0AC(TString filename = "epV0AC.pdf");
  void          PrintEPV0ACvsEPTPC(TString filename = "epV0AC_epTPC.pdf");

  void          PrintPtAll(TString filename = "PtAll.pdf");
  void          PrintPtCompare(TString filename = "PtCompare.pdf");
  void          PrintPtPos(TString filename = "PtPos.pdf");
  void          PrintPtNeg(TString filename = "PtNeg.pdf");

  void          PrintEtaAll(TString filename = "EtaAll.pdf");
  void          PrintEtaCompare(TString filename = "EtaAll.pdf");
  void          PrintEtaPos(TString filename = "EtaPos.pdf");
  void          PrintEtaNeg(TString filename = "EtaNeg.pdf");

  void          PrintPhiAll(TString filename = "PhiAll.pdf");
  void          PrintPhiCompare(TString filename = "PhiCompare.pdf");
  void          PrintPhiPos(TString filename = "PhiPos.pdf");
  void          PrintPhiNeg(TString filename = "PhiNeg.pdf");

  void          PrintEtaPhiAll(TString filename = "EtaPhi.pdf");
  void          PrintEtaPhiPos(TString filename = "EtaPhipos.pdf");
  void          PrintEtaPhiNeg(TString filename = "EtaPhiNeg.pdf");

  void          PrintTPCrowsOverFindableAll(TString filename = "TPCCrossedRowsOverFindableAll.pdf");
  void          PrintTPCrowsOverFindableCompare(TString filename = "TPCCrossedRowsOverFindableCompare.pdf");
  void          PrintTPCrowsOverFindablePos(TString filename = "TPCCrossedRowsOverFindablePos.pdf");
  void          PrintTPCrowsOverFindableNeg(TString filename = "TPCCrossedRowsOverFindableNeg.pdf");

  void          PrintTPCCrossedRowsAll(TString filename = "TPCCrossedRowsAll.pdf");
  void          PrintTPCCrossedRowsCompare(TString filename = "TPCCrossedRowsCompare.pdf");
  void          PrintTPCCrossedRowsPos(TString filename = "TPCCrossedRowsPos.pdf");
  void          PrintTPCCrossedRowsNeg(TString filename = "TPCCrossedRowsNeg.pdf");

  void          PrintTPCnClsAll(TString filename = "TPCnClsAll.pdf");
  void          PrintTPCnClsCompare(TString filename = "TPCnClsCompare.pdf");
  void          PrintTPCnClsPos(TString filename = "TPCnClsPos.pdf");
  void          PrintTPCnClsNeg(TString filename = "TPCnClsNeg.pdf");

  void          PrintITSnClsAll(TString filename = "ITSnClsAll.pdf");
  void          PrintITSnClsCompare(TString filename = "ITSnClsCompare.pdf");
  void          PrintITSnClsPos(TString filename = "ITSnClsPos.pdf");
  void          PrintITSnClsNeg(TString filename = "ITSnClsNeg.pdf");

  void          PrintITSnClsSAll(TString filename = "ITSnClsSAll.pdf");
  void          PrintITSnClsSCompare(TString filename = "ITSnClsSCompare.pdf");
  void          PrintITSnClsSPos(TString filename = "ITSnClsSPos.pdf");
  void          PrintITSnClsSNeg(TString filename = "ITSnClsSNeg.pdf");

  void          PrintTPCChi2All(TString filename = "TPCChi2All.pdf");
  void          PrintTPCChi2Compare(TString filename = "TPCChi2Compare.pdf");
  void          PrintTPCChi2Pos(TString filename = "TPCChi2Pos.pdf");
  void          PrintTPCChi2Neg(TString filename = "TPCChi2Neg.pdf");

  void          PrintITSChi2All(TString filename = "ITSChi2All.pdf");
  void          PrintITSChi2Compare(TString filename = "ITSChi2Compare.pdf");
  void          PrintITSChi2Pos(TString filename = "ITSChi2Pos.pdf");
  void          PrintITSChi2Neg(TString filename = "ITSChi2Neg.pdf");

  void          PrintZVertexAll(TString filename = "ZVertexAll.pdf");
  void          PrintZVertexCompare(TString filename = "ZVertexCompare.pdf");
  void          PrintZVertexPos(TString filename = "ZVertexPos.pdf");
  void          PrintZVertexNeg(TString filename = "ZVertexNeg.pdf");

  void          PrintXYVertexAll(TString filename = "XYVertexAll.pdf");
  void          PrintXYVertexCompare(TString filename = "XYVertexCompare.pdf");
  void          PrintXYVertexPos(TString filename = "XYVertexPos.pdf");
  void          PrintXYVertexNeg(TString filename = "XYVertexNeg.pdf");
  void          PrintPhiEtaProjection(TString filename, TString proj_axis, double minvalue, double maxvalue);
  void          PrintPhiPtProjection(TString filename, TString proj_axis, double minvalue, double maxvalue);

  void          PrintEventVtxZ(TString filename = "EventVtxZ.pdf");

  // Groups of QA plots
  void          PrintPID(TString folder = ".");
  void          PrintQuality(TString folder = ".");

  void          PrintPvsPInnerWallTPC(TString filename = "PvsPInnerWallTPC.pdf");
  void          PrintITSSigmaElevsP(TString filename = "ITSSigmaElevsP.pdf");
  void          PrintITSSigmaPionvsP(TString filename = "ITSSigmaPionvsP.pdf");
  void          PrintITSSigmaKaonvsP(TString filename = "ITSSigmaKaonvsP.pdf");
  void          PrintPIDTPCdEdxvsP(TString filename = "TPCdEdxvsP");
  void          PrintTPCSigmaElevsP(TString filename = "TPCSigmaElevsP.pdf");
  void          PrintTPCSigmaPionvsP(TString filename = "TPCSigmaPionvsP.pdf");
  void          PrintTPCSigmaKaonvsP(TString filename = "TPCSigmaKaonvsP.pdf");
  void          PrintTOFSigmaElevsP(TString filename  = "TOFSigmaElevsP.pdf");
  void          PrintTOFSigmaPionvsP(TString filename = "TOFSigmaPionvsP.pdf");
  void          PrintTOFSigmaKaonvsP(TString filename = "TOFSigmaKaonvsP.pdf");
  void          PrintTPCSigmaElevsEta(TString filename = "TPCSigmaElevsEta.pdf");

  TH1*          GetTrackHist(TString observable, int type);
  TH1*          GetEventHist(TString observable);

  template <typename T>
  T* GetHistogram(TString list, TString histogram){
    TCollection* histColl = 0x0;
    T* h1temp = 0x0;
    histColl = static_cast<TCollection*>(fCutfolder->FindObject(list));
    if (histColl == 0x0) {
      LmHelper::Error(Form("Folder %s not found in input file", list.Data()));
      return h1temp;
    };
    // h1temp = static_cast<T*>(histColl->FindObject(histogram));
    if (histColl->FindObject(histogram) != 0x0) {
      h1temp = (T*)(static_cast<T*>(histColl->FindObject(histogram)))->Clone();
      return h1temp;
    }
    else {
      LmHelper::Error(Form("Histogram '%s' not found in list '%s'. List contains:", histogram.Data(), list.Data()));
      histColl->Print();
    }
    return 0x0;
  };

  int           LoadHistograms();
  enum          type {kNeg, kPos, kAll, kCompare, kEvent};

private:
  void          CalcEtaRange();
  void          CalcPtRange();
  void          CalcCentrality();
  void          PrintPIDSigma(TString filename, TString detector, TString particle);
  void          PrintPtPrivate(TString filename = "Pt.pdf", int type = kNeg);

  TFile*        fInputfile;
  TCollection*  fCutfolder;
  TString       fsConfiglong;

protected:
  // variables
  std::string   fName;
  Double_t      feta_range_min;
  Double_t      feta_range_max;
  Double_t      fpt_range_min;
  Double_t      fpt_range_max;
  Double_t      fcentrality_min;
  Double_t      fcentrality_max;
  TString       fcoll_system;
  TString       fcoll_energy;
  Int_t         fColorPalette;
  Bool_t        fDoRatio;
  Bool_t        fDoNormNEvents;
  Bool_t        fDoNormNEntries;
  Double_t      fRatioPadSize;
  Int_t         fRebin;
  Int_t         fNEvents;

  virtual void  PrintTrackingPrivate(TString filename, TString observable, int type);
  void          SetAxisRanges(TH1D*, TString observable, TCanvas* c1);

};

#endif // LMQA_H
