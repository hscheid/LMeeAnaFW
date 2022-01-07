//Analysis Framework for Dilepton Spectra

// c++ includes
#include <iostream>
#include <vector>
using namespace std;
// ROOT includes
#include "TString.h"
#include "TMath.h"
#include "TF2.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TList.h"
#include "TStyle.h"
#include "TBenchmark.h"
#include "TLegend.h"

#include "TH1.h"
#include "TH2.h"
#include "TPad.h"
#include "TF1.h"
#include "TLine.h"
#include "TPaveText.h"
#include "TVirtualFitter.h"
#include "TGraph.h"
#include "TMinuit.h"
#include "TColor.h"

// project includes
// core
#include "../core/LmManager.h"
#include "../core/LmFileManager.h"
#include "../core/LmBaseSignal.h"
#include "../core/LmSignal.h"
#include "../core/LmHandler.h"
#include "../core/LmHelper.h"
#include "../core/LmQA.h"
#include "../core/LmMultiQA.h"
#include "../core/LmFitter.h"
#include "../core/LmBackground.h"
// user
#include "jerome.h"

Double_t meeMin(1.1), meeMax(2.7), pteeMin(0.), pteeMax(8.);
TH2D *hc, *hb, *hRes;

//Double_t sigma_ccbar(7.480); // 7 TeV
//Double_t sigma_bbbar(0.288); // 7 TeV
Double_t sigma_ccbar(12.16); // 13 TeV
Double_t sigma_bbbar(0.500); // 13 TeV
Double_t x1(0.65);

TString ResName = "./input/LFgen-kpp_7_ratios-Std.root";
TString ResNameLow = "./input/LFgen-kpp_7_ratios-Low.root";
TString ResNameHigh = "./input/LFgen-kpp_7_ratios-High.root";

Double_t ccbarErrLow = 0.07825; // to be updated but not used in the fit
Double_t ccbarErrHigh = 0.07934;
Double_t bbbarErrLow = 0.35724;
Double_t bbbarErrHigh = 0.33461;

struct r_Sys {
  TH1D r;
  std::string caption;
};

int Photon();
double DoVirtualPhotonFit(TH1D& h1, TH1D& reso, TH1D& photon, TH1D& charmafterscaling,
                          std::vector<double>& normRegionHigh, unsigned int standardNormRegionHigh,
                          std::vector<double>& fitRegionLow, unsigned int standardFitRegionLow,
                          std::vector<double>& fitRegionHigh, unsigned int standardFitRegionHigh,
                          double& r_error);
void PlotSignalBeforeFit(TH1D& h1, TH1D& reso, TH1D& pion, TH1D& eta, TH1D& LFrest, TH1D& HF,
                         TH1D& photon, unsigned int cut_i, unsigned int pt_i);
Double_t  TwoGaussiansConnected(Double_t* x, Double_t* par);
void      DrawRFactors(std::vector<r_Sys>& v_r_Sys, std::string filename);
void      PrintChiSquare(std::vector<r_Sys>& vec);
double    GetRMSofBin(std::vector<r_Sys>& vec, int bin);

void      SetHistoProp(TH1D* h, Int_t color, Int_t mStyle, Int_t lStyle);
Double_t  HFfunction(Double_t* x, Double_t* par);
void      SutractHisto(TH2D& h1, TH2D& h2);
void      Rebin2D(TH2D& h, TH2D& hRefBinning);
TH2D*     RebinBis(TH2D& h);
TPaveText GetTextBox(Double_t x1, Double_t y1, Double_t x2, Double_t y2);
void      Add5proc(TH2D& hup, TH2D& h);

std::vector<Double_t> binsMee_forPtee;
std::vector<Double_t> binsPtee_forMee; //{ 0.0,0.4,0.7,1.0,1.5,2.0,2.5,3.0,3.5,4.5,6.0 }

int main()
{

  LmHelper lmHelper; // for styles etc.
  TBenchmark* bench = new TBenchmark();

  //  LmQA qaData(const_cast<char*>(cconfig[0].Data()));
  //  LmQA qaMC(const_cast<char*>(cconfig[1].Data()));
  //  LmMultiQA qaCompare(qaData, qaMC);
  //  qaData.PrintPID("QAplots/PID_data");
  //  qaMC.PrintPID("QAplots/PID_MC");
  //  qaCompare.PrintQuality("QAplots/Quality");
  //  return 0;

  // define vectors to store the different class objects
  std::vector<LmManager*> mgrVec; // works when using pointers (they survive after the for-loop). otherwise fancy errors.
  std::vector<LmBackground*> bkgVec;
  std::vector<LmSignal*> sigVec;

  // set name of z dimension
  LmBaseSignal::SetInputLabelZ("#it{#phi}_{V}", "rad", "PhiV");

  std::vector<Double_t> binsMee_plotting;
  std::vector<Double_t> binsMee_plotting_0;
  std::vector<Double_t> binsMee_plotting_1;
  std::vector<Double_t> binsMee_plotting_2;
  std::vector<Double_t> binsMee_plotting_3;
  std::vector<Double_t> binsMee_plotting_4;
  std::vector<Double_t> binsMee_plotting_5;

  std::vector<Double_t> binsPtee_plotting;
  std::vector<Double_t> binsPtee_plotting_0;
  std::vector<Double_t> binsPtee_plotting_1;
  std::vector<Double_t> binsPtee_plotting_2;
  std::vector<Double_t> binsPtee_plotting_3;
  std::vector<Double_t> binsPtee_plotting_4;
  std::vector<Double_t> binsPtee_plotting_5;

  for (Int_t i = 0; i <= n_ptee_bin_plotting; i++) {
    binsPtee_plotting.push_back(ptee_bins_plotting[i]);
  }
  for (Int_t i = 0; i <= n_ptee_bin_plotting_0; i++)
    binsPtee_plotting_0.push_back(ptee_bins_plotting_0[i]);
  for (Int_t i = 0; i <= n_ptee_bin_plotting_1; i++)
    binsPtee_plotting_1.push_back(ptee_bins_plotting_1[i]);
  for (Int_t i = 0; i <= n_ptee_bin_plotting_2; i++)
    binsPtee_plotting_2.push_back(ptee_bins_plotting_2[i]);
  for (Int_t i = 0; i <= n_ptee_bin_plotting_3; i++)
    binsPtee_plotting_3.push_back(ptee_bins_plotting_3[i]);
  for (Int_t i = 0; i <= n_ptee_bin_plotting_4; i++)
    binsPtee_plotting_4.push_back(ptee_bins_plotting_4[i]);
  for (Int_t i = 0; i <= n_ptee_bin_plotting_5; i++)
    binsPtee_plotting_5.push_back(ptee_bins_plotting_5[i]);

  for (Int_t i = 0; i <= n_mee_bin_plotting; i++) {
    binsMee_plotting.push_back(mee_bins_plotting[i]);
  }
  for (Int_t i = 0; i <= n_mee_bin_plotting_0; i++)
    binsMee_plotting_0.push_back(mee_bins_plotting_0[i]);
  for (Int_t i = 0; i <= n_mee_bin_plotting_1; i++)
    binsMee_plotting_1.push_back(mee_bins_plotting_1[i]);
  for (Int_t i = 0; i <= n_mee_bin_plotting_2; i++)
    binsMee_plotting_2.push_back(mee_bins_plotting_2[i]);
  for (Int_t i = 0; i <= n_mee_bin_plotting_3; i++)
    binsMee_plotting_3.push_back(mee_bins_plotting_3[i]);
  for (Int_t i = 0; i <= n_mee_bin_plotting_4; i++)
    binsMee_plotting_4.push_back(mee_bins_plotting_4[i]);
  for (Int_t i = 0; i <= n_mee_bin_plotting_5; i++)
    binsMee_plotting_5.push_back(mee_bins_plotting_5[i]);

  Double_t ptee_bin_min = ptee_bin[0];
  Double_t ptee_bin_max = ptee_bin[n_ptee_bin];
  Double_t mee_bin_min = mee_bin[0];
  Double_t mee_bin_max = mee_bin[n_mee_bin];

  if (kDoMassSlices == kFALSE) {

    if (kDoIntegrated == kTRUE) {

      binsMee_forPtee.push_back(mee_bin_min);
      binsMee_forPtee.push_back(mee_bin_max);

      binsPtee_forMee.push_back(ptee_bin_min);
      binsPtee_forMee.push_back(ptee_bin_max);
    }

    else {

      for (Int_t i = 0; i <= n_ptee_slices; i++)
        binsPtee_forMee.push_back(ptee_slices[i]);

      binsMee_forPtee.push_back(mee_bin_min);
      binsMee_forPtee.push_back(mee_bin_max);
    }
  } else if (kDoMassSlices == kTRUE) {

    if (kDoIntegrated == kTRUE) {

      binsMee_forPtee.push_back(mee_bin_min);
      binsMee_forPtee.push_back(mee_bin_max);

      binsPtee_forMee.push_back(ptee_bin_min);
      binsPtee_forMee.push_back(ptee_bin_max);
    }

    else {
      for (Int_t i = 0; i <= n_mee_slices; i++)
        binsMee_forPtee.push_back(mee_slices[i]);

      binsPtee_forMee.push_back(ptee_bin_min);
      binsPtee_forMee.push_back(ptee_bin_max);
    }
  }

  std::vector<Double_t> binsPhiV;
  binsPhiV.push_back(0.);
  binsPhiV.push_back(TMath::Pi());
  std::vector<Double_t> binsMee_forPhiV;
  binsMee_forPhiV.push_back(0.);
  binsMee_forPhiV.push_back(0.02);
  binsMee_forPhiV.push_back(0.04);

  if (DoTOFeffPlots == kTRUE) {
    //|__________|   Plot correlations   |__________|
    //Bool_t separatePlots=kTRUE;
    TCanvas c2;
    //TH2D* haxis = new TH2D("haxis","haxis", 1000,3e-5,3e-2, 1000,1e-1,1e2);
    TH2D* haxis2 = new TH2D("haxis2", "haxis2", 1000, 0, 1e1, 1000, 0, 1e3);
    //TH2D* haxis = new TH2D("haxis","haxis", 1000,1e-4,1e4, 1000,1e-4,1e4);
    haxis2->DrawCopy();
    Int_t rebin = 10;

    LmQA Data1(const_cast<char*>(cconfig[0].Data()));
    LmQA Data2(const_cast<char*>(cconfig[1].Data()));

    //Data1.SetDoNormNEvents(kTRUE);
    //Data2.SetDoNormNEvents(kTRUE);

    Data1.SetRebinning(rebin);
    Data2.SetRebinning(rebin);

    LmMultiQA TOFeff(Data1, Data2);
    //TOFeff.SetRebinning(rebin);
    TOFeff.SetDoRatio(kTRUE);
    TOFeff.SetDoNormNEvents(kTRUE);

    Data1.PrintPtAll("data1All.pdf");
    Data2.PrintPtAll("data2All.pdf");
    Data1.PrintPtNeg("data1Neg.pdf");
    Data2.PrintPtNeg("data2Neg.pdf");
    TOFeff.PrintPtAll();
    TOFeff.PrintPtCompare();
    TOFeff.PrintPtPos();
    TOFeff.PrintPtNeg();
  }

  if (DoQA) {

    std::cout << "Processing QA()" << std::endl;
    LmQA qa_data(const_cast<char*>(cconfig[0].Data()));
    LmQA qa_mc(const_cast<char*>(cconfig[1].Data()));
    qa_data.SetColorPalette(57);
    qa_mc.SetColorPalette(58);
    //qa_data.SetDoNormNEvents(true);
    //qa_mc.SetDoNormNEvents(true);
    qa_data.SetDoNormNEntries(true);
    qa_mc.SetDoNormNEntries(true);

    LmMultiQA qa_comp(qa_data, qa_mc);
    qa_comp.SetDoNormNEvents(true);
    //qa_comp.SetDoNormNEntries(true);
    //qa_comp.PrintTrackingPrivate("QAplots/PtPos_comp.pdf", "Pt", LmQA::kPos);
    //qa_comp.PrintTrackingPrivate("QAplots/PtNeg_comp.pdf", "Pt", LmQA::kNeg);
    //qa_comp.PrintTrackingPrivate("QAplots/PtAll_comp.pdf", "Pt", LmQA::kAll);
    //qa_comp.PrintTrackingPrivate("QAplots/PtCompare_comp.pdf", "Pt", LmQA::kCompare);
    qa_comp.PrintPtPos("QAplots/PtPos_comp.pdf");
    qa_comp.PrintPtNeg("QAplots/PtNeg_comp.pdf");
    qa_comp.PrintPtAll("QAplots/Tracking_PtAll_comp.pdf");
    qa_comp.PrintEventVtxZ("QAplots/ZVertex_comp.pdf");
    //qa_comp.PrintPtCompare("QAplots/Tracking_PtCompare_comp.pdf");

    //qa_comp.PrintITSnClsPos("QAplots/ITSnClsPos_comp.pdf");
    //qa_comp.PrintITSnClsNeg("QAplots/ITSnClsNeg_comp.pdf");
    qa_comp.PrintITSnClsAll("QAplots/ITSnClsAll_comp.pdf");
    //qa_comp.PrintITSnClsCompare("QAplots/ITSnClsCompare_comp.pdf");

    //qa_comp.PrintITSnClsSPos("QAplots/ITSnClsSPos_comp.pdf");
    //qa_comp.PrintITSnClsSNeg("QAplots/ITSnClsSNeg_comp.pdf");
    //  qa_comp.PrintITSnClsSAll("QAplots/ITSnClsSAll_comp.pdf");
    //qa_comp.PrintITSnClsSCompare("QAplots/ITSnClsSCompare_comp.pdf");

    // qa.PrintCentrality("QAplots/Event_centrality.pdf");
    // qa.PrintEPTPC("QAplots/Event_epTPC.pdf");
    // qa.PrintEPV0AC("QAplots/epV0AC.pdf");
    // qa.PrintEPV0ACvsEPTPC("QAplots/epV0AC_epTPC.pdf");

    //qa_data.PrintPtPos("QAplots/PtPos.pdf");
    //qa_data.PrintPtNeg("QAplots/PtNeg.pdf");
    //qa_data.PrintPtAll("QAplots/Tracking_PtAll.pdf");
    //qa_data.PrintPtCompare("QAplots/Tracking_PtCompare.pdf");

    // qa.PrintEtaPos("QAplots/EtaPos.pdf");
    // qa.PrintEtaNeg("QAplots/EtaNeg.pdf");
    // qa.PrintEtaAll("QAplots/EtaAll.pdf");
    //qa.PrintEtaCompare("QAplots/Tracking_EtaCompare.pdf");

    // qa.PrintPhiPos("QAplots/PhiPos.pdf");
    // qa.PrintPhiNeg("QAplots/PhiNeg.pdf");
    // qa.PrintPhiAll("QAplots/PhiAll.pdf");
    //qa.PrintPhiCompare("QAplots/Tracking_PhiCompare.pdf");

    //qa.PrintEtaPhiPos("QAplots/Tracking_EtaPhiPos.pdf");
    //qa.PrintEtaPhiNeg("QAplots/Tracking_EtaPhiNeg.pdf");
    //qa.PrintEtaPhiAll("QAplots/Tracking_EtaPhiAll.pdf");
    //qa.PrintEtaPhiAll("QAplots/Tracking_EtaPhiAll.png");

    //qa_comp.PrintTPCnClsPos("QAplots/TPCnClsPos.pdf");
    //qa_comp.PrintTPCnClsNeg("QAplots/TPCnClsNeg.pdf");
    qa_comp.PrintTPCnClsAll("QAplots/TPCnClsAll.pdf");
    //qa_comp.PrintTPCnClsCompare("QAplots/TPCnClsCompare.pdf");

    //qa_comp.PrintITSChi2Pos("QAplots/ITSChi2Pos.pdf");
    //qa_comp.PrintITSChi2Neg("QAplots/ITSChi2Neg.pdf");
    qa_comp.PrintITSChi2All("QAplots/ITSChi2All.pdf");
    //qa_comp.PrintITSChi2Compare("QAplots/ITSChi2Compare.pdf");

    //qa_comp.PrintTPCChi2Pos("QAplots/TPCChi2Pos.pdf");
    //qa_comp.PrintTPCChi2Neg("QAplots/TPCChi2Neg.pdf");
    qa_comp.PrintTPCChi2All("QAplots/TPCChi2All.pdf");
    //qa_comp.PrintTPCChi2Compare("QAplots/TPCChi2Compare.pdf");

    //qa_comp.PrintTPCrowsOverFindablePos("QAplots/TPCCrossedRowsOverFindablePos.pdf");
    //qa_comp.PrintTPCrowsOverFindableNeg("QAplots/TPCCrossedRowsOverFindableNeg.pdf");
    qa_comp.PrintTPCrowsOverFindableAll("QAplots/TPCCrossedRowsOverFindableAll.pdf");
    //qa_comp.PrintTPCrowsOverFindableCompare("QAplots/Tracking_TPCCrossedRowsOverFindableCompare.pdf");

    //qa_comp.PrintTPCCrossedRowsPos("QAplots/TPCCrossedRowsPos.pdf");
    //qa_comp.PrintTPCCrossedRowsNeg("QAplots/TPCCrossedRowsNeg.pdf");
    qa_comp.PrintTPCCrossedRowsAll("QAplots/TPCCrossedRowsAll.pdf");
    //qa_comp.PrintTPCCrossedRowsCompare("QAplots/Tracking_TPCCrossedRowsCompare.pdf");

    //qa_comp.PrintZVertexPos("QAplots/ZVertexPos.pdf");
    //qa_comp.PrintZVertexNeg("QAplots/ZVertexNeg.pdf");
    qa_comp.PrintZVertexAll("QAplots/ZVertexAll.pdf");
    //qa_comp.PrintZVertexCompare("QAplots/Tracking_ZVertexCompare.pdf");

    //qa_comp.PrintXYVertexPos("QAplots/XYVertexPos.pdf");
    //qa_comp.PrintXYVertexNeg("QAplots/XYVertexNeg.pdf");
    qa_comp.PrintXYVertexAll("QAplots/XYVertexAll.pdf");
    //qa_comp.PrintXYVertexCompare("QAplots/Tracking_XYVertexCompare.pdf");

    // qa.PrintPvsPInnerWallTPC("QAplots/PrintPvsPInnerWallTPC.pdf");

    //qa.PrintITSSigmaElevsP("QAplots/ITSSigmaElevsP.pdf");
    //qa.PrintITSSigmaPionvsP("QAplots/ITSSigmaPionvsP.pdf");
    //qa.PrintITSSigmaKaonvsP("QAplots/ITSSigmaKaonvsP.pdf");

    //qa.PrintTPCSigmaElevsP("QAplots/TPCSigmaElevsP.pdf");
    //qa.PrintTPCSigmaPionvsP("QAplots/TPCSigmaPionvsP.pdf");
    //qa.PrintTPCSigmaKaonvsP("QAplots/TPCSigmaKaonvsP.pdf");

    //qa.PrintTOFSigmaElevsP("QAplots/TOFSigmaElevsP.pdf");

    //qa.PrintTPCSigmaElevsEta("QAplots/TPCSigmaElevsEta.pdf");
    // qa.PrintPIDTPCdEdxvsP("QAplots/PID_TPCdEdxvsP.pdf");
    // qa.PrintPID("QAplots");

    //qa_comp.PrintPhiEtaProjection("QAplots/Phi_ASide.pdf", "phi",  0.0, 0.8);
    //qa_comp.PrintPhiEtaProjection("QAplots/Phi_CSide.pdf", "phi", -0.8, -0.00001);
    //

    return 0;
  }

  Int_t kDoExclusionCutZ = LmManager::kNoCut; // = 0
  //if(kDoPhiVCut) kDoExclusionCutZ = LmManager::kFlatCorrSub;
  if (kDoPhiVCut) kDoExclusionCutZ = kDoPhiVCut;

  //__________________________________________________________________________________
  //
  if (doPhiVtemplates) {
    LmHelper::Info("========== extractPhiVtemplates ==========");
    //
    // save phiV template histograms (3D) to a compact rootfile.

    // define vectors to store the different class objects
    std::vector<LmManager*> mgrVec; // works when using pointers (they survive after the for-loop). otherwise fancy errors.
    std::vector<LmBackground*> bkgVec;
    std::vector<LmSignal*> sigVec;

    // Add all configs to LmFileManager for efficient file handling
    for (int ic = 0; ic < n_config; ic++) {
      LmFileManager::Instance()->AddConfig(cconfig[ic]);
    }

    {
      for (int ic = 0; ic < n_config; ic++) {
        // create manager from config string
        LmManager* mgr = new LmManager(const_cast<char*>(cconfig[ic].Data())); // (only one rootfile, instead of low+high)
        if (cconfig[ic].Contains("data_4D") || cconfig[ic].Contains("MC_4D"))
          mgr->SetInputhistAndDim("M_Pt_PhivPair_OpeningAngle", 4);
        else
          mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
        mgr->SetEnableEffiCorr(kFALSE);
        mgr->SetRebinning2D(n_mee_bin, mee_bins, n_ptee_bin, ptee_bins);
        mgr->Process(LmManager::kDontCleanUp);
        mgrVec.push_back(mgr);

        LmBackground* bkg_i = new LmBackground(*(mgrVec.at(ic)));
        //bkg_i->SetUseRfactor(kFALSE);
        bkg_i->Process(kBkgEstimator);
        bkgVec.push_back(bkg_i);

        TString signame = mgrVec.at(ic)->GetName();
        //signame.Append(" "+mgrVec.at(ic)->GetAll3DProjRanges());
        LmSignal* sig_i_Std = new LmSignal(*(mgrVec.at(ic)), *(bkgVec.at(ic)), signame.Data()); //Form("Projection_%d", ic)
        sig_i_Std->SetDoSubtraction(kTRUE);
        sig_i_Std->SetDoSignifRaw(kDoSignifRaw);
        sig_i_Std->SetDoNormBinwidth(kDoNormBinwidth);
        sig_i_Std->SetDoNormNevents(kDoNormNevents);

        //       sig_i_Std->SetCrossSection(kCrossSection);
        //       sig_i_Std->SetDoNormCrossSection(kDoNormCrossSection);
        //       sig_i_Std->SetTrgEff(kTriggerEfficiency);
        //       sig_i_Std->SetDoNormTrgEff(kDoNormTrgEff);
        //       sig_i_Std->SetDoNormRecEff(kDoNormRecEff);
        //       sig_i_Std->SetVtxRecEff(kVtxRecEff);
        //       sig_i_Std->SetDoNormVtxRecEff(kDoNormVtxRecEff);
        //       sig_i_Std->SetVtxRecEffee(kVtxRecEffee);
        //       sig_i_Std->SetDoNormVtxRecEffee(kDoNormVtxRecEffee);

        sig_i_Std->Process(LmSignal::kStd);
        sigVec.push_back(sig_i_Std);
      }

      Double_t plotMeeMin = 0., plotMeeMax = 0.7;
      Double_t plotPteeMin = 0., plotPteeMax = 4.0;

      LmHandler* han_compare = new LmHandler(binsPtee_forMee, binsMee_forPtee, plotMeeMin, plotMeeMax, plotPteeMin, plotPteeMax);
      // attach signals to compare handler. they may already be processed or not.
      for (unsigned int i = 0; i < sigVec.size(); i++) {
        han_compare->AttachSignal(*(sigVec.at(i)), sigVec.at(i)->GetName());
      }
      han_compare->SetPlotRangeRatio(0.04, 0.1);
      han_compare->SetDoRatio(kDoRatio, 0.4, kTRUE);
      han_compare->Process(LmHandler::kCompare); // not needed if the attached signals were processed by a previous handler.

      UInt_t histbits = 1;
      Bool_t kDoLegend = kTRUE;
      han_compare->SetPlotRangeYMargins(2, 50);
      //    han_compare->SetPlotRangeY(5e1, 1e6);
      for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i) {
        histbits = LmSignal::kSubSig + LmSignal::kUnlike + LmSignal::kBkg; //+LmSignal::kUnlikeMix;
        han_compare->PrintCompare(histbits, i, LmBaseSignal::kProjOnMee, "+PhiVtemp", kDoLegend);
        //histbits=LmSignal::kBkg;//+LmSignal::kLikeMix;
        //han_compare->PrintCompare(histbits, i, LmBaseSignal::kProjOnMee, Form("+%s",GetAllOptions().Data()), kDoLegend);
      }
      han_compare->ResetPlotRangeY();

      // write most important histograms to rootfile:
      // when running with option "all", there is still a bug with the subdirectories...
      const Char_t* filename = Form("./input/PhiV/templates/spectra3D_%i.root", (int)(1000 * kSetMinPtLabel));

      TFile* _fileOut = new TFile(filename, "RECREATE");
      //han_compare->SetRootfile(_fileOut);
      han_compare->Write3DHist(LmSignal::kUnlike + LmSignal::kBkg); //in 3D only Unlike and Bkg exist.
      _fileOut->Close();

      for (int ic = 0; ic < n_config; ic++) {
        mgrVec.at(ic)->Process(LmManager::kCleanUp);
      }

      std::cout << "ExtractPhiVtemplates done :-)" << std::endl;
    }
    LmFileManager::Instance()->Clear();
    mgrVec.clear();
    bkgVec.clear();
    sigVec.clear();
    return 0;
  } // ExtractPhiVtemplates
  //__________________________________________________________________________________________________________
  //

  //___________________________________________________________________________________________________
  std::vector<LmManager*> mgrVec_inputs;
  if (doPhiVstudy) {
    for (Int_t i1 = 0; i1 < n_ptee_bin; i1++) {
      LmHelper::Info("========== doPhiVstudy ==========");
      TString projOpt = "xz"; // option="ab" means: a vertical, b horizontal (ROOT-convention)
      // 'xz' means mee on y, 'yz' means ptee on y

      TFile* _fTempl = 0x0;
      TH3D *hSig = 0x0, *hConv = 0x0, *hNorm = 0x0, *hULS = 0x0, *hLS = 0x0, *hNorm2 = 0x0;
      if (kDoPhiVCut >= LmManager::kTemplUnsub) { // if templates are needed
        _fTempl = LmHelper::SafelyOpenRootfile(Form("./input/PhiV/templates/spectra3D_%i.root", (int)(1000 * kSetMinPtLabel)));
        hSig = (TH3D*)LmHelper::GetHistFromTemplateFile(_fTempl, 0, "hUnlike", kTRUE);
        hSig->SetName("hSig"); // prompt
        hConv = (TH3D*)LmHelper::GetHistFromTemplateFile(_fTempl, 1, "hUnlike", kTRUE);
        hSig->SetName("hConv"); // conversion
        hNorm = (TH3D*)hSig->Clone("hNorm");
        hNorm->Add(hConv);
        LmHelper::Info("========== templates loaded  ==========");
        hULS = (TH3D*)LmHelper::GetHistFromTemplateFile(_fTempl, 0, "hUnlike", kTRUE);
        hULS->SetName("hULS"); // prompt
        hLS = (TH3D*)LmHelper::GetHistFromTemplateFile(_fTempl, 0, "hBkg", kTRUE);
        hLS->SetName("hLS"); // prompt
      }

      LmHelper::Info("========== templates loaded  ==========");
      // Add all configs to LmFileManager for efficient file handling
      for (int ic = 0; ic < n_config; ic++) {
        LmFileManager::Instance()->AddConfig(cconfig[ic]);
      }

      // fill vector of input managers
      for (int ic = 0; ic < n_config; ic++) {
        LmManager* mgr00 = new LmManager(const_cast<char*>(cconfig[ic].Data())); // (only one rootfile, instead of low+high)
        // set further configuration for the manager
        mgr00->SetInputhistAndDim(inputhist, inputdim);
        mgr00->SetProjOption(projOpt.Data());
        mgr00->SetEnableEffiCorr(kDoEffiCorrection);
        mgr00->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
        mgr00->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
        mgr00->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
        mgr00->SetTemplateNormRegionMin(n_cutPhiVbelow, cutPhiVbelow); // only needed for some template types.
        mgr00->SetTemplateNormRegionMax(n_cutPhiVabove, cutPhiVabove); // only needed for some template types.
        if (kDoPhiVCut == LmManager::kTemplSub) mgr00->SetExclusionZTemplates(hSig, 0x0, LmManager::kTemplSub, hSig, hNorm);
        //if (kDoPhiV==LmManager::kTemplConv)  mgr->SetExclusionZTemplates(hCon    , 0x0, LmManager::kTemplConv , hSig, hNorm);
        if (kDoPhiVCut == LmManager::kTemplUnsub) mgr00->SetExclusionZTemplates(hULS, hLS, LmManager::kTemplUnsub, hSig, hNorm);
        mgr00->SetEnableExclusionCutZ(kDoExclusionCutZ);

        //mgr00->SetExclusionZTemplates(hULS, hLS);
        //mgr00->SetTemplateNormRegion(0, 1./2.*TMath::Pi());

        if (projOpt.EqualTo("xz")) // 'xz' means mee on y
          mgr00->SetRebinning2D(n_phiv_bin, phiv_bin, n_mee_bin, mee_bin.data());
        if (projOpt.EqualTo("yz")) // 'yz' means ptee on y
          mgr00->SetRebinning2D(n_phiv_bin, phiv_bin, n_ptee_bin, ptee_bin.data());
        if (projOpt.EqualTo("yx")) // 'yx' means ptee on y, mee on x (default analysis)
          mgr00->SetRebinning2D(n_mee_bin, mee_bin.data(), n_ptee_bin, ptee_bin.data());
        // read in histograms from data files
        mgr00->Process(LmManager::kReadInputOnly);
        mgrVec_inputs.push_back(mgr00);
      }

      // define 3D-projection binning
      // at least one of these two arrays should have only a single integrated bin, otherwise we get many managers...
      Double_t bins3DProjRangeX[] = {0.00, /*0.02, 0.04, 0.06,*/ /*0.10,*/ 1.}; // mee
      //Double_t bins3DProjRangeY[] = {/* 0., 1.,*/ 2.,/*3.,*/4./*, 6.,*//* 8.*/ }; // ptee
      //Double_t bins3DProjRangeY[] = { 0., 1.}; // ptee
      //Double_t bins3DProjRangeY[] = { 1., 2.}; // ptee
      //Double_t bins3DProjRangeY[] = { 2., 3.}; // ptee

      Double_t bins3DProjRangeY[] = {ptee_bins[i1], ptee_bins[i1 + 1]}; // ptee
      unsigned int n_bins3DProjRangeX = sizeof(bins3DProjRangeX) / sizeof(*bins3DProjRangeX) - 1;
      unsigned int n_bins3DProjRangeY = sizeof(bins3DProjRangeY) / sizeof(*bins3DProjRangeY) - 1;
      if (n_bins3DProjRangeX > 1) LmHelper::Error("computation of phiV-corrected spectra with templates for multiple mee slices at the same time is messed up!");
      if (n_bins3DProjRangeY > 1) LmHelper::Error("computation of phiV-corrected spectra with templates for multiple ptee slices at the same time is messed up!");

      // fill vector of managers with selected 3D subranges
      for (unsigned int iproj_x = 0; iproj_x < n_bins3DProjRangeX; iproj_x++) {
        for (unsigned int iproj_y = 0; iproj_y < n_bins3DProjRangeY; iproj_y++) {
          for (unsigned int imgr = 0; imgr < mgrVec_inputs.size(); imgr++) {
            // make a copy of the manager including its input histograms
            LmManager* mgr_i = new LmManager(*(mgrVec_inputs.at(imgr)));
            if (n_bins3DProjRangeY > 1 || bins3DProjRangeY[0] != 0 || bins3DProjRangeY[1] == 1)
              mgr_i->SetName(Form("%s (%.0f-%.0f MeV)", mgr_i->GetName(), bins3DProjRangeY[iproj_y] * 1000, bins3DProjRangeY[iproj_y + 1] * 1000)); // cannot use "/c" when saving it to rootfile.
            // select different subranges in input histograms
            mgr_i->Set3DProjRangeX(bins3DProjRangeX[iproj_x], bins3DProjRangeX[iproj_x + 1]);
            mgr_i->Set3DProjRangeY(bins3DProjRangeY[iproj_y], bins3DProjRangeY[iproj_y + 1]);
            // add new manager to vector
            mgrVec.push_back(mgr_i);
          }
          // add manager for integrated y range, if there is more than one bin in y. (nicer to have a separate loop)
          if (n_bins3DProjRangeY > 1 && iproj_y == n_bins3DProjRangeY - 1) {
            for (unsigned int imgr = 0; imgr < mgrVec_inputs.size(); imgr++) {
              LmManager* mgr_i = new LmManager(*(mgrVec_inputs.at(imgr)));
              mgr_i->SetName(Form("%s (%.0f-%.0f MeV)", mgr_i->GetName(), bins3DProjRangeY[0] * 1000, bins3DProjRangeY[iproj_y + 1] * 1000)); // cannot use "/c" when saving it to rootfile.
              mgr_i->Set3DProjRangeX(bins3DProjRangeX[0], bins3DProjRangeX[iproj_x + 1]);
              mgr_i->Set3DProjRangeY(bins3DProjRangeY[0], bins3DProjRangeY[iproj_y + 1]);
              mgrVec.push_back(mgr_i);
            }
          }
        }
      }

      // for each manager: create background and signal class from it, configure and process them, store them in vectors
      for (unsigned int iproj = 0; iproj < mgrVec.size(); iproj++) {
        //cout << " iproj = " << iproj << endl;
        // process the managers: make the projections, rebinning, corrections...
        mgrVec.at(iproj)->Process(LmManager::kDontReadInput); // dont read in rootfiles again
        //mgrVec.at(iproj)->Print2DUnlike(Form("c2DUnlike_%d.pdf",iproj));

        LmBackground* bkg_i = new LmBackground(*(mgrVec.at(iproj)));
        bkg_i->Process(kBkgEstimator);
        bkgVec.push_back(bkg_i);

        TString signame = mgrVec.at(iproj)->GetName();
        //        signame.Append(" "+mgrVec.at(iproj)->GetAll3DProjRanges());
        if (mgrVec.at(iproj)->GetExclCutType() == LmManager::kTemplUnsub) signame.Append(" matched");
        if (mgrVec.at(iproj)->GetExclCutType() == LmManager::kTemplConv) signame.Append(" - conv");
        if (mgrVec.at(iproj)->GetExclCutType() == LmManager::kTemplSub) {
          // try to add an uncut subtracted signal to help in the phiV correction of the current signal.
          if (mgrVec.at(0)->GetExclCutType() == LmManager::kNoCut)
            mgrVec.at(iproj)->AddVisualSig(sigVec.at(0)->GetSubSig2D(), "hDataOrig", "data, no #phi_{V} corr.");
        }
        LmSignal* sig_i_Std = new LmSignal(*(mgrVec.at(iproj)), *(bkgVec.at(iproj)), signame.Data()); //Form("Projection_%d", iproj)
        sig_i_Std->SetDoSubtraction(kTRUE);
        sig_i_Std->SetDoSignifRaw(kDoSignifRaw);
        sig_i_Std->SetDoNormBinwidth(kDoNormBinwidth);
        sig_i_Std->SetDoNormNevents(kDoNormNevents);

        //sig_i_Std->SetCrossSection(kCrossSection);
        //sig_i_Std->SetDoNormCrossSection(kDoNormCrossSection);
        //sig_i_Std->SetTrgEff(kTriggerEfficiency);
        //sig_i_Std->SetDoNormTrgEff(kDoNormTrgEff);
        //sig_i_Std->SetDoNormRecEff(kDoNormRecEff);
        //sig_i_Std->SetVtxRecEff(kVtxRecEff);
        //sig_i_Std->SetDoNormVtxRecEff(kDoNormVtxRecEff);
        //sig_i_Std->SetVtxRecEffee(kVtxRecEffee);
        //sig_i_Std->SetDoNormVtxRecEffee(kDoNormVtxRecEffee);

        sig_i_Std->Process(LmSignal::kStd);
        Int_t skipFirstVisual = 1;
        for (unsigned int ivis = skipFirstVisual; ivis < sig_i_Std->GetNVisualSig(); ivis++) {
          sigVec.push_back(sig_i_Std->GetVisualSigI(ivis));
        }

        sigVec.push_back(sig_i_Std);
      }

      // close rootfile(s) from input manager(s) (to free memory if many files have been opened...)
      for (unsigned int imgr = 0; imgr < mgrVec_inputs.size(); imgr++) {
        mgrVec_inputs.at(imgr)->Process(LmManager::kCleanUp);
      }

      Double_t plotMeeMin = 0., plotMeeMax = 0.50; // phiv
      Double_t plotPteeMin = 0., plotPteeMax = 8.0;
      Double_t plotPhiVMin = 0., plotPhiVMax = 3.14; // phiv
      Bool_t kDoLegend = kTRUE;
      Bool_t kDoLogY;

      LmHandler* hanCompare = new LmHandler(LmHandler::kCompare);
      // attach signals to compare handler. they may already be processed or not.
      for (unsigned int i = 0; i < sigVec.size(); i++) {
        hanCompare->AttachSignal(*(sigVec.at(i)), sigVec.at(i)->GetName());
      }
      if (projOpt.EqualTo("xz")) { // 'xz' means mee on y, phiv on x
        hanCompare->SetBinsY_forprojOnX(binsMee_forPhiV);
        hanCompare->SetBinsX_forprojOnY(binsPhiV);
        hanCompare->SetPlotRangeMee(plotPhiVMin, plotPhiVMax);
        hanCompare->SetPlotRangePtee(plotMeeMin, plotMeeMax);
        kDoLogY = kFALSE;
      }
      if (projOpt.EqualTo("yz")) {                        // 'yz' means ptee on y, phiv on x
        hanCompare->SetBinsY_forprojOnX(binsPtee_forMee); //binsPtee_forPhiV doesnt exist.
        hanCompare->SetBinsX_forprojOnY(binsPhiV);
        hanCompare->SetPlotRangeMee(plotPhiVMin, plotPhiVMax);
        hanCompare->SetPlotRangePtee(plotPteeMin, plotPteeMax);
        kDoLogY = kFALSE;
      }
      if (projOpt.EqualTo("yx")) { // 'yx' means ptee on y, mee on x (default analysis)
        hanCompare->SetBinsY_forprojOnX(binsPtee_forMee);
        hanCompare->SetBinsX_forprojOnY(binsMee_forPtee);
        hanCompare->SetPlotRangeMee(plotMeeMin, plotMeeMax);
        hanCompare->SetPlotRangePtee(plotPteeMin, plotPteeMax);
        kDoLogY = kTRUE;
      }

      //hanCompare->SetPlotRangeY(0.0, 22e-5);
      //      hanCompare->SetPlotRangeRatio(1e-2, 1e0);
      //      hanCompare->SetDoRatio(kDoRatio, 0.4, kTRUE);
      hanCompare->SetPlotRangeRatio(0.1, 2);
      hanCompare->SetDoRatio(kDoRatio, 0.3, kTRUE);
      hanCompare->Process(LmHandler::kCompare); // not needed if the attached signals were processed by a previous handler.

      UInt_t histbits = 1;
      TString s3Drange = "";
      if (n_bins3DProjRangeY == 1 && (bins3DProjRangeY[0] != 0 || bins3DProjRangeY[1] == 1)) s3Drange = Form("_ptee%.0fto%.0f", bins3DProjRangeY[0], bins3DProjRangeY[1]);
      if (kDoLogY) {
        hanCompare->SetPlotRangeYMargins(2, 50);
      } else {
        hanCompare->SetPlotRangeYMargins(0, 1.1);
      }

      for (int i = 0; i <= hanCompare->GetMaxBinProj(LmBaseSignal::kProjOnX); ++i) {
        if (projOpt.EqualTo("xz")) { // 'xz' means mee on y, phiv on x
          //hanCompare->SetPlotRangeY(-0.005, 0.02);
          Double_t yscale = 20. / TMath::Pi() * 60; // to be used when x=phiV and not normalized per radian.
          if (hanCompare->GetLmSignalI(0)->GetDoNormBinwidth()) yscale = 1;
          //if (hanCompare->GetLmSignalI(0)->GetDoNormBinwidth()) yscale = 100; // for ptee 4-6 GeV
          if (i == 0 || i == hanCompare->GetMaxBinProj(LmBaseSignal::kProjOnX)) hanCompare->SetPlotRangeY(-0.001 / yscale, 0.03 / yscale);
          //else                                                              hanCompare->SetPlotRangeY(-0.001/yscale,  0.01/yscale); //for ULS,LS
          else if (i <= 2)
            hanCompare->SetPlotRangeY(-0.001 / yscale, 0.005 / yscale);
          //else if (i<=4)                                                    hanCompare->SetPlotRangeY(-0.0005/yscale, 0.002/yscale);
          //else                                                              hanCompare->SetPlotRangeY(-0.0005/yscale, 0.001/yscale);
          else
            hanCompare->SetPlotRangeY(-0.001 / yscale, 0.005 / yscale);
          // to see all contributions:
          //hanCompare->SetPlotRangeY(0.001/yscale,  10*0.03/yscale); kDoLogY=kTRUE;
        }
        if (projOpt.EqualTo("yx")) {            // 'yx' means ptee on y, mee on x (default analysis)
          hanCompare->SetPlotRangeY(1e-6, 1e3); //1e5?
        }
        //        hanCompare->SetPlotRangeY(0.00000002, 0.0000001); //1e5?
        hanCompare->SetPlotRangeY(2, 1);           //1e5?
        histbits = LmSignal::kSubSig;              //+LmSignal::kUnlike+LmSignal::kBkg;
        hanCompare->SetRequestedSignals("012345"); // data + MC sum
        hanCompare->PrintCompare(histbits, i, LmBaseSignal::kProjOnX, Form("+PhiVStudy1-ptee%.0fto%.0f_%i_%i", bins3DProjRangeY[0] * 1000, bins3DProjRangeY[1] * 1000, kLowerCent, kUpperCent), kDoLegend, kDoLogY);
        //        histbits=LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg;//LmSignal::kUnlike+LmSignal::kUnlikeMix;
        //        hanCompare->PrintCompare(histbits, i, LmBaseSignal::kProjOnX, Form("+%s%s",GetAllOptions().Data(), s3Drange.Data()), kDoLegend, kDoLogY);
        //
        //        hanCompare->SetRequestedSignals("123"); // all MC
        //        histbits=LmSignal::kSubSig;//+LmSignal::kUnlike+LmSignal::kBkg;
        //        hanCompare->PrintCompare(histbits, i, LmBaseSignal::kProjOnX, Form("+%s%s",GetAllOptions().Data(), s3Drange.Data()), kDoLegend, kDoLogY);
        //        histbits=LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg;//LmSignal::kUnlike+LmSignal::kUnlikeMix;
        //        hanCompare->PrintCompare(histbits, i, LmBaseSignal::kProjOnX, Form("+%s%s",GetAllOptions().Data(), s3Drange.Data()), kDoLegend, kDoLogY);

        //histbits=LmSignal::kBkg;//+LmSignal::kLikeMix;
        //hanCompare->PrintCompare(histbits, i, LmBaseSignal::kProjOnX, Form("+%s%s",GetAllOptions().Data(), s3Drange.Data()), kDoLegend, kDoLogY);
      }
      hanCompare->ResetPlotRangeY();

      if (projOpt.EqualTo("xz")) { // 'xz' means mee on y, phiv on x
        //|__________|   Mee   |__________|
        //hanCompare->SetPlotRangeY(1, 0);
        // hanCompare->SetPlotRangeY(1e-4, 1e2);
        //hanCompare->SetPlotRangeY(1e-5, 1e1); // for ptee 4-6 GeV
        //hanCompare->SetPlotRangeY(1e-4, 5);
        //hanCompare->SetPlotRangeY(1e-4, 1e5);
        hanCompare->SetPlotRangeY(1e-6, 1e5);
        for (int i = 0; i <= hanCompare->GetMaxBinProj(LmBaseSignal::kProjOnY); ++i) {
          //hanCompare->SetRequestedSignals("056"); // data
          //hanCompare->SetRequestedSignals("0456"); // data + MC sum
          //    hanCompare->PrintCompare(LmSignal::kSubSig, i, LmBaseSignal::kProjOnY, "+_PhiVStudy2", kDoLegend);
          //          hanCompare->PrintCompare(LmSignal::kUnlike+LmSignal::kBkg, i, LmBaseSignal::kProjOnY, Form("+_phiVstud%s%s",GetAllOptions().Data(), s3Drange.Data()), kDoLegend);
          //          hanCompare->PrintCompare(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, i, LmBaseSignal::kProjOnY, Form("+_phiVstud%s%s",GetAllOptions().Data(), s3Drange.Data()), kDoLegend);
          //          hanCompare->SetRequestedSignals("123"); // all MC
          //          hanCompare->PrintCompare(LmSignal::kSubSig, i, LmBaseSignal::kProjOnY, Form("+_phiVstud%s%s",GetAllOptions().Data(), s3Drange.Data()), kDoLegend);
          //          hanCompare->PrintCompare(LmSignal::kUnlike+LmSignal::kBkg, i, LmBaseSignal::kProjOnY, Form("+_phiVstud%s%s",GetAllOptions().Data(), s3Drange.Data()), kDoLegend);
          //          hanCompare->PrintCompare(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, i, LmBaseSignal::kProjOnY, Form("+_phiVstud%s%s",GetAllOptions().Data(), s3Drange.Data()), kDoLegend);
        }
        hanCompare->ResetPlotRangeY();
      }

      // write most important histograms to rootfile:
      TString filename = Form("./input/PhiV/%iMeV_%i_%i/spectra1D-phiVstudy-ptee%.0fto%.0f_%iMeV.root", (int)(1000 * kSetMinPtLabel), kLowerCent, kUpperCent, bins3DProjRangeY[0] * 1000, bins3DProjRangeY[1] * 1000, (int)(1000 * kSetMinPtLabel));
      //if (n_bins3DProjRangeY==1 && (bins3DProjRangeY[0]!=0 || bins3DProjRangeY[1]==1))
      //  filename.ReplaceAll(".root", Form("_ptee%.0fto%.0f.root",bins3DProjRangeY[0],bins3DProjRangeY[1]));

      TFile* _fileOut = new TFile(filename.Data(), "RECREATE");
      hanCompare->Write1DHistSingle(LmSignal::kSubSig + LmSignal::kUnlike + LmSignal::kBkg, LmSignal::kProjOnX); // phiV
      hanCompare->Write1DHistSingle(LmSignal::kSubSig + LmSignal::kUnlike + LmSignal::kBkg, LmSignal::kProjOnY); // mee
      _fileOut->Close();

      LmFileManager::Instance()->Clear();
      mgrVec.clear();
      bkgVec.clear();
      sigVec.clear();
      mgrVec_inputs.clear();
    }

    //    UInt_t histbits=1;
    //    if (printLogY) {
    //      hanCompare->SetPlotRangeYMargins(2, 50);
    //      //hanCompare->SetPlotRangeY(1e1, 1e7);
    //    } else {
    //      hanCompare->SetPlotRangeYMargins(0, 1.1);
    //    }
    //    for (int i = 0; i <= hanCompare->GetMaxBinProj(LmBaseSignal::kProjOnX); ++i){
    //      histbits=LmSignal::kSubSig;
    //      hanCompare->PrintCompare(histbits, i, LmBaseSignal::kProjOnX, "", printLegend, printLogY);
    //      histbits=/*LmSignal::kSubSig+*/LmSignal::kUnlike+LmSignal::kBkg;//LmSignal::kUnlike+LmSignal::kUnlikeMix;
    //      hanCompare->PrintCompare(histbits, i, LmBaseSignal::kProjOnX, "", printLegend, printLogY);
    ////      histbits=LmSignal::kBkg;//+LmSignal::kLikeMix;
    ////      //      hanCompare->PrintCompare(histbits, i, LmBaseSignal::kProjOnX, "", printLegend, printLogY);
    //    }
    //    hanCompare->ResetPlotRangeY();

    //    // write most important histograms to rootfile:
    //    const Char_t* filename = "spectra1D_PhiV.root";
    //    TFile* _fileOut = new TFile(filename, "RECREATE");
    //    hanCompare->Write1DHistSingle(LmSignal::kUnlike, LmSignal::kProjOnMee);
    //    _fileOut->Close();

    std::cout << "PhiVstudy done :-)" << std::endl;
    return 0;

  } // doPhiVstudy
  //__________________________________________________________________________________

  if (doVirtualPhotonFits) {

    // CONFIG
    unsigned int standardCut = 0;
    unsigned int lowerCent = 0;
    unsigned int upperCent = 100;

    unsigned int number_sys_variation_cocktail = 100; //100
    double sys_error_pion = 0.01;                     // 3%BR, 4%Para = sqrt(0.03*0.03 + 0.04*0.04)
    double sys_error_eta_low = 0.161;                 // used conservative upper systematics // 5.8%BR, 0.05%para_upper 0.15%para_lower
    double sys_error_eta_high = 0.15;                 // used conservative upper systematics // 5.8%BR, 0.05%para_upper 0.15%para_lower

    unsigned int number_sys_variation_charm = 100; //100
    double sys_error_charm = 0.18;                 //

    std::vector<double> normRegionLow = {0.02};
    std::vector<double> normRegionHigh = {0.06, 0.08};
    unsigned int standardNormRegionLow = 0;
    unsigned int standardNormRegionHigh = 0;

    std::vector<double> fitRegionLow = {0.08, 0.10, 0.12};
    std::vector<double> fitRegionHigh = {0.2, 0.3, 0.4};
    //std::vector<double> fitRegionLow  = {0.08,0.10};
    //std::vector<double> fitRegionHigh = {0.2,0.3};
    unsigned int standardFitRegionLow = 0;
    unsigned int standardFitRegionHigh = 1;
    // std::vector<double> fitRegionLow  = {0.1, 0.14};
    // std::vector<double> fitRegionHigh = { 0.3, 0.38, 0.46};
    // unsigned int standardFitRegionLow  = 1;
    // unsigned int standardFitRegionHigh = 1;
    //
    //

    TH1::SetDefaultSumw2(true);

    binsPtee_forMee.clear();

    binsPtee_forMee.push_back(0.);
    binsPtee_forMee.push_back(0.4);
    binsPtee_forMee.push_back(1.);
    //binsPtee_forMee.push_back(1.5);
    binsPtee_forMee.push_back(2.);
    //binsPtee_forMee.push_back(2.5);
    binsPtee_forMee.push_back(3.);
    //binsPtee_forMee.push_back(3.5);
    binsPtee_forMee.push_back(4.);

    //binsPtee_forMee.push_back(6.);
    //binsPtee_forMee.push_back(8.);
    binsPtee_forMee.push_back(10.);

    LmRebinner rebinner;
    rebinner.SetRebinning2D(n_mee_bin_plotting, mee_bins_plotting, n_ptee_bin_plotting, ptee_bins_plotting);

    // ###########################################################################
    // Reading photon file
    // std::string photon_file = "photon_fit/input/LFcocktail_pt400_eta08_wRatio_newReso.root";
    //    std::string photon_file = "photon_fit/input/cocktail_LF_v2.root";
    //std::string photon_file = "photon_fit/input/LFcocktail_Jerome_75MeV_low_0404_v1.root";
    std::string photon_file = "photon_fit/input/LFcocktail_CeresComb_v11.root";
    if (kDo200MeVCocktail)
      photon_file = "photon_fit/input/LFcocktail_Jerome_200MeV_low_0404_v1.root";
    TFile* file2 = TFile::Open(photon_file.c_str(), "READ");
    TDirectoryFile* dir2 = dynamic_cast<TDirectoryFile*>(file2->Get("LMeeCocktailMC"));
    TList* list2 = dynamic_cast<TList*>(dir2->Get("LMeeCocktailMC_0.80"));

    TH1F hnEvents = *(dynamic_cast<TH1F*>(list2->FindObject("NEvents")));
    double nEvents = hnEvents.GetBinContent(1);
    std::cout << "Number of events in cocktail calculation: " << nEvents << std::endl;
    TH2D h2_photon = *(reinterpret_cast<TH2D*>(list2->FindObject("pteevsmee_Virtual_Photon")));
    std::cout << &h2_photon << std::endl;
    // h2_photon.Scale(1. / nEvents);
    rebinner.Rebin2DHistogram(h2_photon);
    std::cout << &h2_photon << std::endl;

    std::vector<TH1D> v_photon;
    for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i) {
      double value_low = -1;
      double value_high = -1;
      if (i == binsPtee_forMee.size() - 1) { // integrated pT bin
        value_low = binsPtee_forMee[0];
        value_high = binsPtee_forMee[binsPtee_forMee.size() - 1];
      } else {
        value_low = binsPtee_forMee[i];
        value_high = binsPtee_forMee[i + 1];
      }

      int bin_low = h2_photon.GetYaxis()->FindBin(value_low);
      int bin_high = h2_photon.GetYaxis()->FindBin(value_high - 0.0001);
      TH1D h1 = *(h2_photon.ProjectionX(Form("photon_bin_%d_%d", bin_low, bin_high), bin_low, bin_high, "e"));

      // TH1D h1_rebin = *((TH1D*)(h1.Rebin(n_mee_bin, Form("photon_rebinned_bin_%d_%d", bin_low, bin_high),mee_bin)));
      // std::cout << h1_rebin.GetNbinsX() << std::endl;
      // h1_rebin.Scale(1. / nEvents);
      // v_photon.emplace_back(h1_rebin);

      h1.SetTitle("VPhoton");

      h1.Scale(1. / nEvents, "width");
      v_photon.emplace_back(h1);
    }
    std::cout << "test" << std::endl;

    std::cout << "test" << std::endl;
    std::cout << "test" << std::endl;
    // ###########################################################################
    // Reading cocktail file
    std::string cocktail_file_LF = Form("photon_fit/input/spectra1D_Mee_%i-%i.root", lowerCent, upperCent);
    TFile* file3 = TFile::Open(cocktail_file_LF.c_str(), "READ");
    TDirectoryFile* dir3 = dynamic_cast<TDirectoryFile*>(file3->Get("Cocktail2D"));

    TH2D h2_sum = *(dynamic_cast<TH2D*>(dir3->Get("cocktailSum")));
    std::cout << &h2_sum << std::endl;
    TH2D h2_pion = *(dynamic_cast<TH2D*>(dir3->Get("pteevsmee_Pi0")));
    TH2D h2_eta = *(dynamic_cast<TH2D*>(dir3->Get("pteevsmee_Eta")));
    TH2D h2_etaprime = *(dynamic_cast<TH2D*>(dir3->Get("pteevsmee_EtaP")));
    TH2D h2_rho = *(dynamic_cast<TH2D*>(dir3->Get("pteevsmee_Rho")));
    TH2D h2_omega = *(dynamic_cast<TH2D*>(dir3->Get("pteevsmee_Omega")));
    TH2D h2_phi = *(dynamic_cast<TH2D*>(dir3->Get("pteevsmee_Phi")));

    //TH2D h2_sum      = *(dynamic_cast<TH2D*>(file3->Get("Sum")));
    //TH2D h2_pion     = *(dynamic_cast<TH2D*>(file3->Get("Pion")));
    //TH2D h2_eta      = *(dynamic_cast<TH2D*>(file3->Get("Eta")));
    //TH2D h2_etaprime = *(dynamic_cast<TH2D*>(file3->Get("EtaPrime")));
    //TH2D h2_rho      = *(dynamic_cast<TH2D*>(file3->Get("Rho")));
    //TH2D h2_omega    = *(dynamic_cast<TH2D*>(file3->Get("Omega")));
    //TH2D h2_phi      = *(dynamic_cast<TH2D*>(file3->Get("Phi")));

    std::cout << "test2" << std::endl;
    std::string cocktail_file_HF = Form("photon_fit/input/spectra1D_Mee_%i-%i.root", lowerCent, upperCent);
    file3 = TFile::Open(cocktail_file_HF.c_str(), "READ");
    dir3 = dynamic_cast<TDirectoryFile*>(file3->Get("Cocktail2D"));
    TH2D h2_charm = *(dynamic_cast<TH2D*>(dir3->Get("charm")));
    TH2D h2_beauty = *(dynamic_cast<TH2D*>(dir3->Get("beauty")));

    // adding everything except pion and eta
    TH2D h2_LFrest = *(dynamic_cast<TH2D*>(h2_etaprime.Clone("LFrest")));
    h2_LFrest.Add(&h2_rho);
    h2_LFrest.Add(&h2_omega);
    h2_LFrest.Add(&h2_phi);

    TH2D h2_reso = *(dynamic_cast<TH2D*>(h2_pion.Clone("reso")));
    h2_reso.Add(&h2_eta);
    h2_reso.Add(&h2_LFrest);

    TH2D h2_HF = *(dynamic_cast<TH2D*>(h2_charm.Clone("HF")));
    h2_HF.Add(&h2_charm);

    rebinner.Rebin2DHistogram(h2_reso);
    rebinner.Rebin2DHistogram(h2_pion);
    rebinner.Rebin2DHistogram(h2_eta);
    rebinner.Rebin2DHistogram(h2_LFrest);

    rebinner.Rebin2DHistogram(h2_HF);

    std::cout << "test3" << std::endl;
    std::vector<TH1D> v_reso;
    std::vector<TH1D> v_pion;
    std::vector<TH1D> v_eta;
    std::vector<TH1D> v_LFrest;
    std::vector<TH1D> v_HF;
    for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i) {
      double value_low = -1;
      double value_high = -1;
      if (i == binsPtee_forMee.size() - 1) { // integrated pT bin
        value_low = binsPtee_forMee[0];
        value_high = binsPtee_forMee[binsPtee_forMee.size() - 1];
      } else {
        value_low = binsPtee_forMee[i];
        value_high = binsPtee_forMee[i + 1];
      }

      // extracting LF
      int bin_low = h2_reso.GetYaxis()->FindBin(value_low);
      int bin_high = h2_reso.GetYaxis()->FindBin(value_high - 0.0001);
      TH1D h1 = *(h2_reso.ProjectionX(Form("reso_bin_%d_%d", bin_low, bin_high), bin_low, bin_high, "e"));
      TH1D h1_pion = *(h2_pion.ProjectionX(Form("pion_bin_%d_%d", bin_low, bin_high), bin_low, bin_high, "e"));
      TH1D h1_eta = *(h2_eta.ProjectionX(Form("eta_bin_%d_%d", bin_low, bin_high), bin_low, bin_high, "e"));
      TH1D h1_LFrest = *(h2_LFrest.ProjectionX(Form("LFrest_bin_%d_%d", bin_low, bin_high), bin_low, bin_high, "e"));
      h1.Scale(1., "width");
      h1.Scale(kCrossSection);
      h1_pion.Scale(1., "width");
      h1_pion.Scale(kCrossSection);
      h1_eta.Scale(1., "width");
      h1_eta.Scale(kCrossSection);
      h1_LFrest.Scale(1., "width");
      h1_LFrest.Scale(kCrossSection);
      h1.SetTitle("LF");
      v_reso.emplace_back(h1);
      v_pion.emplace_back(h1_pion);
      v_eta.emplace_back(h1_eta);
      v_LFrest.emplace_back(h1_LFrest);

      // extracting HF
      bin_low = h2_HF.GetYaxis()->FindBin(value_low);
      bin_high = h2_HF.GetYaxis()->FindBin(value_high - 0.0001);
      TH1D h1_central = *(h2_HF.ProjectionX(Form("HF_bin_%d_%d", bin_low, bin_high), bin_low, bin_high, "e"));
      h1_central.Scale(1., "width");
      h1_central.Scale(kCrossSection);
      h1_central.SetTitle("HF");
      v_HF.emplace_back(h1_central);
    }

    TH1D h_RGamma("RGamma", ";p_{T} [GeV/c];R_{#gamma} = #frac{1}{1-r}", binsPtee_forMee.size() - 1, binsPtee_forMee.data());
    TH1D h_RGammaSysErr("RGammaSysErr", ";p_{T} [GeV/c];R_{#gamma} = #frac{1}{1-r}", binsPtee_forMee.size() - 1, binsPtee_forMee.data());
    TH1D h_r("r", ";p_{T} [GeV/c];r = #frac{#gamma*_{dir}}{#gamma*_{dir} + #gamma*_{decay}}", binsPtee_forMee.size() - 1, binsPtee_forMee.data());
    TH1D h_rSysErr("rSysErr", ";p_{T} [GeV/c];r = #frac{#gamma*_{dir}}{#gamma*_{dir} + #gamma*_{decay}}", binsPtee_forMee.size() - 1, binsPtee_forMee.data());

    TCanvas c1("c1", "c1", 800, 800);
    c1.cd();
    c1.SetLogy();
    c1.SetLeftMargin(0.18);

    TF1 scale_gaus_pion("gaus", "[0]*exp(-0.5*((x-[1])/[2])**2)", -1, 1);
    scale_gaus_pion.SetNpx(1000);
    scale_gaus_pion.SetParameters(1, 0, sys_error_pion);
    scale_gaus_pion.Draw();
    c1.SetLogy(kFALSE);
    c1.SaveAs(Form("photon_fit/005_pion_gaus.pdf"));

    // TF1 scale_gaus_eta("gaus", "[0]*exp(-0.5*((x-[1])/[2])**2)", -1, 1);
    TF1 scale_gaus_eta("gaus", TwoGaussiansConnected, -1, 1, 4);
    scale_gaus_eta.SetNpx(1000);
    scale_gaus_eta.SetParameters(1., 0., sys_error_eta_low, sys_error_eta_high);
    scale_gaus_eta.Draw();
    c1.SetLogy(kFALSE);
    c1.SaveAs(Form("photon_fit/004_eta_gaus.pdf"));

    TF1 scale_gaus_charm("gaus", "[0]*exp(-0.5*((x-[1])/[2])**2)", -1, 1);
    scale_gaus_charm.SetNpx(1000);
    scale_gaus_charm.SetParameters(1, 0, sys_error_charm);
    scale_gaus_charm.Draw();
    c1.SetLogy(kFALSE);
    c1.SaveAs(Form("photon_fit/003_charm_gaus.pdf"));

    // Reading in 2D data for all cutsettings
    //std::vector<std::string> v_cutsettings = {"cut variation 0", "cut variation 1", "cut variation 2", "cut variation 3", "cut variation 4",
    //                                          "cut variation 5", "cut variation 6", "cut variation 7", "cut variation 8", "cut variation 9",
    //                                          "cut variation 10", "cut variation 11", "cut variation 12", "cut variation 13", "cut variation 14",
    //                                          "cut variation 15", "cut variation 16", "cut variation 17", "cut variation 18", "cut variation 19", "cut variation 20"};
    std::vector<std::string> v_cutsettings = {"Data"};
    //std::vector<std::string> v_cutsettings = {"cut variation 0"};

    std::vector<TH2D> v_data2D;

    std::vector<r_Sys> v_r_Sys_fit_region;
    std::vector<r_Sys> v_r_Sys_norm_region;
    std::vector<r_Sys> v_r_Sys_cocktail;
    std::vector<r_Sys> v_r_Sys_HF;

    for (unsigned int cut_i = 0; cut_i < v_cutsettings.size(); ++cut_i) {
      // for (unsigned int cut_i = 0; cut_i < 1; ++cut_i){
      //
      // ###########################################################################
      //     // Reading signal file
      std::string signal_file = Form("photon_fit/input/spectra1D_Mee_%i-%i.root", lowerCent, upperCent);
      TFile* file1 = TFile::Open(signal_file.c_str(), "READ");
      if (!file1) {
        LmHelper::Error(Form("Signal file %s not found", signal_file.c_str()));
        return 1;
      }
      TDirectoryFile* dir1 = dynamic_cast<TDirectoryFile*>(file1->Get(v_cutsettings[cut_i].c_str()));
      std::cout << "adws " << dir1 << std::endl;
      TH2D h2_signal = *(dynamic_cast<TH2D*>(dir1->Get("hSubSig")));
      rebinner.Rebin2DHistogram(h2_signal);
      std::cout << &h2_signal << std::endl;
      file1->Close();
      v_data2D.push_back(h2_signal);

      for (unsigned int i = 0; i < fitRegionLow.size(); ++i) {
        for (unsigned int j = 0; j < fitRegionHigh.size(); ++j) {
          v_r_Sys_fit_region.push_back({h_r, Form("Fit: %2.2f - %2.2f MeV/c^{2}, cut %d", fitRegionLow[i], fitRegionHigh[j], cut_i)});
        }
      }
      if (cut_i == standardCut) {
        for (unsigned int i = 0; i < normRegionHigh.size(); ++i) {
          v_r_Sys_norm_region.push_back({h_r, Form("Norm: %2.2f - %2.2f MeV/c^{2}, cut %d", 0., normRegionHigh[i], cut_i)});
        }

        for (unsigned int i = 0; i < number_sys_variation_cocktail; ++i) {
          v_r_Sys_cocktail.push_back({h_r, Form("cut %d", cut_i)});
        }
        for (unsigned int i = 0; i < number_sys_variation_charm; ++i) {
          v_r_Sys_HF.push_back({h_r, Form("cut %d", cut_i)});
        }
      }
    }

    for (unsigned int pt_i = 0; pt_i < binsPtee_forMee.size() - 1; ++pt_i) {

      TH1D h_RGammasPerPtSysErr("hgamma", "", 100., 0.9, 1.4);
      h_RGammasPerPtSysErr.SetTitle(";R_{#gamma} = #frac{1}{1-r}");
      TH1D h_rPerPtSysErr("r_perPt", "", 550., -0.1, 1.);
      h_rPerPtSysErr.SetTitle(";r = #frac{#gamma*_{dir}}{#gamma*_{dir} + #gamma*_{decay}}");
      TH1D h_rPerPtSysErr_FittingRegion("r_fitting", "", 550., -0.1, 1.);
      h_rPerPtSysErr_FittingRegion.SetTitle(";r = #frac{#gamma*_{dir}}{#gamma*_{dir} + #gamma*_{decay}}");
      TH1D h_rPerPtSysErr_NormalizationRegion("r_normalization", "", 550., -0.1, 1.);
      h_rPerPtSysErr_NormalizationRegion.SetTitle(";r = #frac{#gamma*_{dir}}{#gamma*_{dir} + #gamma*_{decay}}");
      TH1D h_rPerPtSysErr_CocktailVariation("cocktailVariation", "", 550., -0.1, 1.);
      h_rPerPtSysErr_CocktailVariation.SetTitle(";r = #frac{#gamma*_{dir}}{#gamma*_{dir} + #gamma*_{decay}}");
      TH1D h_rPerPtSysErr_CharmVariation("charmVariation", "", 550., -0.1, 1.);
      h_rPerPtSysErr_CharmVariation.SetTitle(";r = #frac{#gamma*_{dir}}{#gamma*_{dir} + #gamma*_{decay}}");

      double rForCurrentBin = -1;
      double rForCentralValue = -1;
      double rErrorForCentralValue = -1;

      std::cout << "\npt interval = " << binsPtee_forMee[pt_i] << "-" << binsPtee_forMee[pt_i + 1] << " GeV/c" << std::endl;
      for (unsigned int cut_i = 0; cut_i < v_data2D.size(); ++cut_i) {

        double value_low = binsPtee_forMee[pt_i];
        double value_high = binsPtee_forMee[pt_i + 1];
        int bin_low = v_data2D[cut_i].GetYaxis()->FindBin(value_low);
        int bin_high = v_data2D[cut_i].GetYaxis()->FindBin(value_high - 0.0001);
        TH1D h1 = *(v_data2D[cut_i].ProjectionX(Form("bin_%d_%d", bin_low, bin_high), bin_low, bin_high, "e"));
        //h1.Scale(1./147629176, "width");
        h1.Scale(1. / 541680768, "width");
        h1.Scale((kCrossSection * kVtxRecEff) / (kVtxRecEffee * kTriggerEfficiency));
        std::cout << "  CrossSection: " << kCrossSection << std::endl;
        std::cout << "  VtxRecEff: " << kVtxRecEff << std::endl;
        std::cout << "  VtxRecEffee: " << kVtxRecEffee << std::endl;
        std::cout << "  TriggerEfficiency: " << kTriggerEfficiency << std::endl;

        // // Drawing of unscaled histograms
        PlotSignalBeforeFit(h1, v_reso[pt_i], v_pion[pt_i], v_eta[pt_i], v_LFrest[pt_i], v_HF[pt_i], v_photon[pt_i], cut_i, pt_i);

        if (cut_i == standardCut) {
          // #########################################################################
          // #########################################################################
          // Variation of pion and eta fraction in cocktail  #########################

          for (unsigned int sys_var_j = 0; sys_var_j < number_sys_variation_cocktail; ++sys_var_j) {

            // Get scaling factor according to systematic uncertainty
            double gaus_random_pion;
            double gaus_random_eta;
            if (sys_var_j == 0) {
              gaus_random_pion = 0.;
              gaus_random_eta = 0.;
            } else {
              gaus_random_pion = scale_gaus_pion.GetRandom();
              gaus_random_eta = scale_gaus_eta.GetRandom();
            }
            double scaling_factor_pion = 1. + gaus_random_pion;
            double scaling_factor_eta = 1. + gaus_random_eta;

            TH1D pionafterscaling = *(dynamic_cast<TH1D*>(v_pion[pt_i].Clone(Form("%d_%d", pt_i, sys_var_j))));
            TH1D etaafterscaling = *(dynamic_cast<TH1D*>(v_eta[pt_i].Clone(Form("%d_%d", pt_i, sys_var_j))));

            pionafterscaling.Scale(scaling_factor_pion);
            etaafterscaling.Scale(scaling_factor_eta);

            TH1D cocktailAfterScaling = *(dynamic_cast<TH1D*>(pionafterscaling.Clone(Form("rescaled_%d_%d", pt_i, sys_var_j))));
            cocktailAfterScaling.Add(&etaafterscaling);
            cocktailAfterScaling.Add(&v_LFrest[pt_i]);
            double r_error;
            double r = DoVirtualPhotonFit(h1, cocktailAfterScaling, v_photon[pt_i], v_HF[pt_i],
                                          normRegionHigh, standardNormRegionHigh,
                                          fitRegionLow, standardFitRegionLow,
                                          fitRegionHigh, standardFitRegionHigh,
                                          r_error);
            h_rPerPtSysErr_CocktailVariation.Fill(r);

            unsigned int counter = sys_var_j;
            // std::cout << counter << std::endl;
            v_r_Sys_cocktail[counter].r.SetBinContent(v_r_Sys_cocktail[counter].r.FindBin(binsPtee_forMee[pt_i]), r);
            v_r_Sys_cocktail[counter].r.SetBinError(v_r_Sys_cocktail[counter].r.FindBin(binsPtee_forMee[pt_i]), r_error);

          } // end of variation of fraction of pion and eta

          // #########################################################################
          // #########################################################################
          // Variation of charm contribution  ########################################

          for (unsigned int sys_var_j = 0; sys_var_j < number_sys_variation_charm; ++sys_var_j) {

            // Get scaling factor according to systematic uncertainty
            double gaus_random_charm;
            if (sys_var_j == 0) {
              gaus_random_charm = 0.;
            } else {
              gaus_random_charm = scale_gaus_charm.GetRandom();
            }
            double scaling_factor_charm = 1. + gaus_random_charm;
            TH1D charmafterscaling = *(dynamic_cast<TH1D*>(v_HF[pt_i].Clone(Form("charm_%d_%d", pt_i, sys_var_j))));
            charmafterscaling.Scale(scaling_factor_charm);
            double r_error;
            double r = DoVirtualPhotonFit(h1, v_reso[pt_i], v_photon[pt_i], charmafterscaling,
                                          normRegionHigh, standardNormRegionHigh,
                                          fitRegionLow, standardFitRegionLow,
                                          fitRegionHigh, standardFitRegionHigh,
                                          r_error);

            unsigned int counter = sys_var_j;
            // std::cout << counter << std::endl;
            v_r_Sys_HF[counter].r.SetBinContent(v_r_Sys_HF[counter].r.FindBin(binsPtee_forMee[pt_i]), r);
            v_r_Sys_HF[counter].r.SetBinError(v_r_Sys_HF[counter].r.FindBin(binsPtee_forMee[pt_i]), r_error);

            h_rPerPtSysErr_CharmVariation.Fill(r);

          } // end of variation of charm contribution
          // #########################################################################
          // #########################################################################
          // Variation of normalization region  ######################################
          for (unsigned int normalization_region_i_low = 0; normalization_region_i_low < normRegionHigh.size(); ++normalization_region_i_low) {
            double r_error = -1;
            double r = DoVirtualPhotonFit(h1, v_reso[pt_i], v_photon[pt_i], v_HF[pt_i],
                                          normRegionHigh, normalization_region_i_low,
                                          fitRegionLow, standardFitRegionLow,
                                          fitRegionHigh, standardFitRegionHigh, r_error);

            unsigned int counter = normalization_region_i_low;
            // std::cout << counter << std::endl;
            v_r_Sys_norm_region[counter].r.SetBinContent(v_r_Sys_norm_region[counter].r.FindBin(binsPtee_forMee[pt_i]), r);
            v_r_Sys_norm_region[counter].r.SetBinError(v_r_Sys_norm_region[counter].r.FindBin(binsPtee_forMee[pt_i]), r_error);

            h_rPerPtSysErr_NormalizationRegion.Fill(r);

          } // end of loop over higher edge of normalization region
        }

        for (unsigned int fitting_region_i_low = 0; fitting_region_i_low < fitRegionLow.size(); ++fitting_region_i_low) {
          for (unsigned int fitting_region_i_high = 0; fitting_region_i_high < fitRegionHigh.size(); ++fitting_region_i_high) {
            LmFitter fitter;
            fitter.SetDatahist(&h1);
            fitter.AttachFitTemplateA(&v_reso[pt_i]);
            fitter.AttachFitTemplateB(&v_photon[pt_i]);
            fitter.AttachFitTemplateC(&v_HF[pt_i]);
            fitter.SetTemplateNames("resonances", "Heavy flavour", "Virtual Photon");

            //determine normalisation of reso and photon template by scaling both to the the data yield at very low mee, charm fixed
            fitter.PrepareFitVirtPhot_Normalization(normRegionLow[standardNormRegionLow], normRegionHigh[standardNormRegionHigh], kTRUE);
            //Fit function using 3 templates & parameters: 0:r 1:reso & photon scaling 2: charm scaling
            //set all parameters to 1 as start value
            //first fit performed to determine reso/photon scaling, set best fit value
            fitter.Process(LmFitter::kThreeTempl_OneNorm_PlusBaseline);
            if (fitting_region_i_low == standardFitRegionLow && fitting_region_i_high == standardFitRegionHigh && cut_i == standardCut) {
              fitter.PrintBestFit(Form("photon_fit/004_norm/norm_bin%d.pdf", pt_i));
              TCanvas c2("c2", "c2", 800, 800);
              c2.cd();
              c2.SetLogy();
              fitter.GetBestTemplateA()->GetYaxis()->SetTitle("#frac{1}{N_{ev}} #frac{dN}{N_{ev}dm_{ee}}");
              fitter.GetBestTemplateA()->GetYaxis()->SetTitleOffset(1.55);

              fitter.GetBestTemplateA()->SetAxisRange(0., 0.7, "X");
              fitter.GetBestTemplateA()->SetAxisRange(1e-6, 50., "Y");
              fitter.GetBestTemplateA()->Draw("hist");
              fitter.GetBestTemplateB()->Draw("hist same");
              fitter.GetDatahist()->Draw("p same");

              TLegend leg(0.5, 0.65, 0.85, 0.85);
              leg.AddEntry(fitter.GetBestTemplateA(), "LF Cocktail", "lpe");
              leg.AddEntry(fitter.GetBestTemplateB(), "Direct Photons", "lpe");
              leg.AddEntry((TH1D*)0x0, Form("%.2lf < #it{p}_{T,ee} < %.2lf GeV/c", binsPtee_forMee[pt_i], binsPtee_forMee[pt_i + 1]), "");
              leg.Draw("same");
              c2.SaveAs(Form("photon_fit/004_norm/norm2_bin_cut%d_mass%d.pdf", cut_i, pt_i));
            }

            fitter.PrepareFitVirtPhot_Extraction(fitRegionLow[fitting_region_i_low], fitRegionHigh[fitting_region_i_high]);
            fitter.Process(LmFitter::kThreeTempl_OneNorm_PlusBaseline);

            double r = fitter.GetBestFitFcn()->GetParameter(0); // inclusive photons
            double r_error = fitter.GetBestFitFcn()->GetParError(0);

            // unsigned int counter = fitting_region_i_high + fitting_region_i_low * fitRegionHigh.size();
            unsigned int counter = fitting_region_i_high + fitting_region_i_low * fitRegionHigh.size() + cut_i * fitRegionHigh.size() * fitRegionLow.size();
            // std::cout << counter << std::endl;
            v_r_Sys_fit_region[counter].r.SetBinContent(v_r_Sys_fit_region[counter].r.FindBin(binsPtee_forMee[pt_i]), r);
            v_r_Sys_fit_region[counter].r.SetBinError(v_r_Sys_fit_region[counter].r.FindBin(binsPtee_forMee[pt_i]), r_error);

            std::cout << " ############ r: " << r << "  fit low: " << fitting_region_i_low << "  fit high: " << fitting_region_i_high << std::endl;
            if (r > 0.001) h_rPerPtSysErr_FittingRegion.Fill(r);

            //
            if (fitting_region_i_low == standardFitRegionLow && fitting_region_i_high == standardFitRegionHigh && cut_i == standardCut) {
              rForCentralValue = r;
              rErrorForCentralValue = r_error;

              fitter.PrintBestFit(Form("photon_fit/003_best_fit/best_fit_bin%d.pdf", pt_i));
              TCanvas c2("c2", "c2", 800, 800);
              c2.cd();
              c2.SetLogy();

              TH1D cocktailPreFit = *(dynamic_cast<TH1D*>(v_reso[pt_i].Clone(Form("cocktail_preFit_bin%d", pt_i))));
              TH1D cocktailPostFit = *(dynamic_cast<TH1D*>(fitter.GetBestTemplateA()->Clone(Form("cocktail_bin%d", pt_i))));
              TH1D photonPostFit = *(dynamic_cast<TH1D*>(fitter.GetBestTemplateB()->Clone(Form("photon_bin%d", pt_i))));
              TH1D charmPostFit = *(dynamic_cast<TH1D*>(fitter.GetBestTemplateC()->Clone(Form("charm_bin%d", pt_i))));
              TH1D data = *(dynamic_cast<TH1D*>(fitter.GetDatahist()->Clone(Form("data_bin%d", pt_i))));

              cocktailPostFit.Scale(1. - r);
              photonPostFit.Scale(r);

              TH1D sumPostFit = *(dynamic_cast<TH1D*>(cocktailPostFit.Clone(Form("sum_bin%d", pt_i))));
              sumPostFit.Add(&photonPostFit);
              sumPostFit.Add(&charmPostFit);

              TH1D sumPreFit = *(dynamic_cast<TH1D*>(cocktailPreFit.Clone(Form("sum_pre_bin%d", pt_i))));
              sumPreFit.Add(&charmPostFit);

              // sumPostFit.SetLineWidth(2);
              sumPostFit.SetLineColor(kBlack);
              sumPreFit.SetLineColor(kBlack);
              sumPreFit.SetLineStyle(2);

              cocktailPreFit.SetMarkerColor(kOrange + 2);
              cocktailPreFit.SetLineWidth(2);
              cocktailPreFit.SetLineStyle(2);
              cocktailPreFit.SetLineColor(kOrange + 2);

              data.SetAxisRange(1e-6, 50, "Y");
              data.GetYaxis()->SetTitleOffset(1.55);
              // data.GetYaxis()->SetTitle("#frac{dN^{2}}{N_{ev}dm_{ee}dp_{T,ee}}");
              data.GetYaxis()->SetTitle("#frac{1}{N_{ev}} #frac{dN}{N_{ev}dm_{ee}}");
              // data.GetYaxis()->SetTitle("#frac{1}{#textrm{N_{ev}}} #frac{d#textrm{N}}{N_{ev}d#textrm{m_{ee}}}");
              data.SetAxisRange(0., 0.7, "X");
              data.Draw("p");
              cocktailPostFit.Draw("hist same");
              cocktailPreFit.Draw("hist same");
              photonPostFit.Draw("hist same");
              charmPostFit.Draw("hist same");
              sumPostFit.Draw("hist same");
              sumPreFit.Draw("hist same");
              data.Draw("p same");
              data.DrawCopy("axis same");

              TLegend leg1(0.3, 0.6, 0.85, 0.85);
              leg1.AddEntry(&data, "data", "lpe");
              leg1.AddEntry(&cocktailPreFit, "LF Cocktail before fit", "lpe");
              leg1.AddEntry(&cocktailPostFit, "LF Cocktail after fit", "lpe");
              leg1.AddEntry(&photonPostFit, "Direct #gamma after fit", "lpe");
              leg1.AddEntry(&charmPostFit, "HF Cocktail", "lpe");
              leg1.AddEntry(&sumPreFit, "Sum before fit, w/o #gamma", "lpe");
              leg1.AddEntry(&sumPostFit, "Sum after fit, with #gamma", "lpe");
              leg1.AddEntry((TH1D*)0x0, Form("%.2lf < #it{p}_{T,ee} < %.2lf GeV/c", binsPtee_forMee[pt_i], binsPtee_forMee[pt_i + 1]), "");
              leg1.SetBorderSize(0);
              leg1.Draw("same");
              c2.SaveAs(Form("photon_fit/006_compare/compare_bin%d.pdf", pt_i));

              //ratio
              c2.SetLogy(kFALSE);
              data.SetAxisRange(0.5, 2, "Y");
              data.Divide(&sumPostFit);
              cocktailPreFit.Divide(&cocktailPostFit);

              data.GetYaxis()->SetTitle("data / fitted cocktail");
              data.Draw("p");
              cocktailPreFit.Draw("hist same");

              TLine l1(0., 1., 1.09, 1.);
              l1.Draw("same");

              c2.SaveAs(Form("photon_fit/006_compare/compare_ratio_bin%d.pdf", pt_i));

              std::cout << "PreFit / PostFit: " << cocktailPreFit.GetBinContent(2) << std::endl;
            }

            if (fitting_region_i_low == standardFitRegionLow && fitting_region_i_high == standardFitRegionHigh && cut_i == standardCut) {
              rForCentralValue = r;
              rErrorForCentralValue = r_error;
            }
          } // end of loop upper edge of fitting region
        }   // end of loop lower edge of fitting region
      }

      // Calculating of r and RGamma distribution per pT Bin including their uncertainties
      TCanvas c2("c2", "", 800, 800);
      c2.SetRightMargin(0.05);

      h_rPerPtSysErr_CocktailVariation.Scale(1. / h_rPerPtSysErr_CocktailVariation.Integral());
      h_rPerPtSysErr_CharmVariation.Scale(1. / h_rPerPtSysErr_CharmVariation.Integral());
      h_rPerPtSysErr_FittingRegion.Scale(1. / h_rPerPtSysErr_FittingRegion.Integral());
      h_rPerPtSysErr_NormalizationRegion.Scale(1. / h_rPerPtSysErr_NormalizationRegion.Integral());

      h_rPerPtSysErr_CocktailVariation.SetLineWidth(2);
      h_rPerPtSysErr_CharmVariation.SetLineWidth(2);
      h_rPerPtSysErr_FittingRegion.SetLineWidth(2);
      h_rPerPtSysErr_NormalizationRegion.SetLineWidth(2);

      h_rPerPtSysErr_CocktailVariation.SetLineColor(kBlack);
      h_rPerPtSysErr_CharmVariation.SetLineColor(kGreen + 2);
      h_rPerPtSysErr_FittingRegion.SetLineColor(kRed);
      h_rPerPtSysErr_NormalizationRegion.SetLineColor(kBlue);

      h_rPerPtSysErr_CocktailVariation.SetAxisRange(0, 1, "Y");
      h_rPerPtSysErr_CocktailVariation.SetAxisRange(0, 0.1, "X");

      h_rPerPtSysErr_CocktailVariation.Draw("hist");
      h_rPerPtSysErr_CharmVariation.Draw("hist same");
      h_rPerPtSysErr_FittingRegion.Draw("hist same");
      h_rPerPtSysErr_NormalizationRegion.Draw("hist same");

      TLegend leg_r_dist(0.5, 0.6, 0.90, 0.8);
      leg_r_dist.SetBorderSize(0);
      leg_r_dist.AddEntry(&h_rPerPtSysErr_CocktailVariation, "from LF variation", "l");
      leg_r_dist.AddEntry(&h_rPerPtSysErr_CharmVariation, "from charm variation", "l");
      leg_r_dist.AddEntry(&h_rPerPtSysErr_NormalizationRegion, "from normalization variation", "l");
      leg_r_dist.AddEntry(&h_rPerPtSysErr_FittingRegion, "from fitting variation", "l");
      leg_r_dist.AddEntry((TH1D*)0x0, Form("%.2lf < #it{p}_{T,ee} < %.2lf GeV/c", binsPtee_forMee[pt_i], binsPtee_forMee[pt_i + 1]), "");
      leg_r_dist.Draw("same");
      c2.SaveAs(Form("photon_fit/002_plot_r_for_sys_unc/r_for_sys_unc_mass%d.pdf", pt_i));

      c1.cd();
      double rms_fittingRegion = GetRMSofBin(v_r_Sys_fit_region, pt_i);
      double rms_normRegion = GetRMSofBin(v_r_Sys_norm_region, pt_i);
      double rms_cocktail = GetRMSofBin(v_r_Sys_cocktail, pt_i);
      double rms_HF = GetRMSofBin(v_r_Sys_HF, pt_i);
      double rms_sum = TMath::Sqrt(rms_fittingRegion * rms_fittingRegion +
                                   rms_normRegion * rms_normRegion +
                                   rms_cocktail * rms_cocktail +
                                   rms_HF * rms_HF);

      // rErrorForCentralValue
      std::cout << "r:                          " << rForCentralValue << std::endl;
      rForCentralValue = h_rPerPtSysErr_FittingRegion.GetMean();
      Double_t mean_r_val = 0;
      Int_t filled_bins = 0;
      for (Int_t i1 = 1; i1 < h_rPerPtSysErr_FittingRegion.GetNbinsX(); i1++) {
        if (h_rPerPtSysErr_FittingRegion.GetBinContent(i1) > 0) {
          mean_r_val += h_rPerPtSysErr_FittingRegion.GetBinCenter(i1);
          filled_bins++;
        }
      }
      std::cout << mean_r_val / filled_bins << std::endl;
      std::cout << "<r>_fit: " << h_rPerPtSysErr_FittingRegion.GetMean() << std::endl;
      std::cout << "rms norm:     " << rms_normRegion << std::endl;
      std::cout << "rms fit:      " << rms_fittingRegion << std::endl;
      std::cout << "rms cocktail: " << rms_cocktail << std::endl;
      std::cout << "rms HF:       " << rms_HF << std::endl;
      std::cout << "rms Sum:      " << rms_sum << std::endl;

      std::cout << "Rel. Unc. norm:     " << 100 * rms_normRegion / rForCentralValue << " %" << std::endl;
      std::cout << "Rel. Unc. fit:      " << 100 * rms_fittingRegion / rForCentralValue << " %" << std::endl;
      std::cout << "Rel. Unc. cocktail: " << 100 * rms_cocktail / rForCentralValue << " %" << std::endl;
      std::cout << "Rel. Unc. HF:       " << 100 * rms_HF / rForCentralValue << " %" << std::endl;
      std::cout << "Rel. Unc. Sum:      " << 100 * rms_sum / rForCentralValue << " %" << std::endl;

      double RGammaForCentralValue = 1. / (1. - rForCentralValue);                                         // R_gamma
      double RGamma_errorStat = rErrorForCentralValue / ((1 - rForCentralValue) * (1 - rForCentralValue)); // delta_RGamma = r_error / (1-RGamma)^2
      double RGamma_errorSyst = rms_sum / ((1 - rForCentralValue) * (1 - rForCentralValue));               // delta_RGamma = r_error / (1-RGamma)^2

      // Setting Content for RGamma as function of pT
      h_RGamma.SetBinContent(h_RGamma.FindBin(binsPtee_forMee[pt_i]), RGammaForCentralValue);
      h_RGamma.SetBinError(h_RGamma.FindBin(binsPtee_forMee[pt_i]), RGamma_errorStat);
      h_r.SetBinContent(h_r.FindBin(binsPtee_forMee[pt_i]), rForCentralValue);
      h_r.SetBinError(h_r.FindBin(binsPtee_forMee[pt_i]), rErrorForCentralValue);

      h_RGammaSysErr.SetBinContent(h_RGamma.FindBin(binsPtee_forMee[pt_i]), RGammaForCentralValue);
      h_RGammaSysErr.SetBinError(h_RGamma.FindBin(binsPtee_forMee[pt_i]), RGamma_errorSyst);
      h_rSysErr.SetBinContent(h_r.FindBin(binsPtee_forMee[pt_i]), rForCentralValue);
      h_rSysErr.SetBinError(h_r.FindBin(binsPtee_forMee[pt_i]), rms_sum);
    }
    PrintChiSquare(v_r_Sys_fit_region);

    //
    TLine line0(binsPtee_forMee[0], 0., binsPtee_forMee[binsPtee_forMee.size() - 1], 0.);
    line0.SetLineWidth(2);

    DrawRFactors(v_r_Sys_fit_region, "photon_fit/005_r_factors/001_r-factors_fitRegion.pdf");
    DrawRFactors(v_r_Sys_norm_region, "photon_fit/005_r_factors/002_r-factors_normRegion.pdf");
    DrawRFactors(v_r_Sys_cocktail, "photon_fit/005_r_factors/003_r-factors_cocktail.pdf");
    DrawRFactors(v_r_Sys_HF, "photon_fit/005_r_factors/004_r-factors_charm.pdf");

    // #########################################################################
    // #########################################################################
    // Plotting of r and RGamma Plot ###########################################
    c1.cd();
    h_RGamma.SetAxisRange(0.9, 1.3, "Y");
    h_RGamma.SetAxisRange(0., binsPtee_forMee[binsPtee_forMee.size() - 1] - 1e10, "X");
    h_RGamma.SetMarkerSize(2);
    h_RGamma.SetMarkerStyle(20);
    h_RGamma.SetMarkerColor(kRed - 3);
    h_RGamma.SetLineColor(kRed - 3);
    h_RGamma.DrawCopy("p");

    h_RGammaSysErr.SetMarkerSize(2);
    h_RGammaSysErr.SetMarkerStyle(20);
    h_RGammaSysErr.SetMarkerColor(kRed - 3);
    h_RGammaSysErr.SetLineColor(kRed - 3);
    h_RGammaSysErr.SetFillStyle(0);
    h_RGammaSysErr.DrawCopy("p E2 same");

    TLine line1(binsPtee_forMee[0], 1., binsPtee_forMee[binsPtee_forMee.size() - 1], 1.);
    line1.SetLineWidth(2);
    line1.Draw("same");

    TLegend leg(0.2, 0.7, 0.5, 0.85);
    leg.AddEntry(&h_RGamma, "data", "pl");

    TLatex latex;
    latex.SetTextSize(0.03);
    latex.SetTextAlign(12); //align at top
    latex.DrawLatexNDC(.23, .80, "ALICE work in progress");
    latex.DrawLatexNDC(.23, .75, "pp, #sqrt{s} = 13 TeV, B = 0.2 T");
    latex.DrawLatexNDC(.23, .70, "#it{p}_{T}>75 MeV/#it{c}, |#eta|<0.8");

    c1.SaveAs("photon_fit/001_RGamma.pdf");

    TF1 f_r_fit("r-fit", "[0]*x+[1]", 0, 10);

    h_r.GetYaxis()->SetTitleOffset(2.1);
    h_r.SetAxisRange(-0.2, 0.8, "Y");
    h_r.SetAxisRange(0., binsPtee_forMee[binsPtee_forMee.size() - 1] - 1e10, "X");
    h_r.SetMarkerSize(2);
    h_r.SetMarkerStyle(20);
    h_r.SetMarkerColor(kRed - 3);
    h_r.SetLineColor(kRed - 3);
    h_r.DrawCopy("p");
    h_r.Fit(&f_r_fit, "0Q");
    std::cout << "\n fit result: " << f_r_fit.GetParameter(0) << "(+-" << f_r_fit.GetParError(0) << ") * x + " << f_r_fit.GetParameter(1) << "(+-" << f_r_fit.GetParError(1) << ")" << std::endl;

    h_rSysErr.SetMarkerSize(2);
    h_rSysErr.SetMarkerStyle(20);
    h_rSysErr.SetMarkerColor(kRed - 3);
    h_rSysErr.SetLineColor(kRed - 3);
    h_rSysErr.SetFillStyle(0);
    h_rSysErr.DrawCopy("p E2 same");

    line0.Draw("same");

    TLegend leg_r(0.16, 0.6, 0.45, 0.7);
    leg_r.AddEntry(&h_r, "data", "pl");
    leg_r.AddEntry(&h_rSysErr, "Systematic Uncertainty", "E2");
    latex.DrawLatexNDC(.23, .80, "ALICE work in progress");
    latex.DrawLatexNDC(.23, .75, "pp, #sqrt{s_} = 13 TeV");
    latex.DrawLatexNDC(.23, .70, "#it{p}_{T}>75 MeV/#it{c}, |#eta|<0.8");

    c1.SaveAs("photon_fit/002_r.pdf");

    return 0;
  } // doVirtualPhotonFits
  //__________________________________________________________________________________

  bench->Start("input_processing");

  // Add all configs to LmFileManager for efficient file handling (optional)
  for (int ic = 0; ic < n_config; ic++) {
    LmFileManager::Instance()->AddConfig(cconfig[ic]);
  }

  TFile* _fTempl = 0x0;
  TH3D *hSig = 0x0, *hCon = 0x0, *hULS = 0x0, *hLS = 0x0, *hDiffGa = 0x0, *hDiffGa_LS = 0x0, *hNorm = 0x0;
  if (kDoPhiVCut >= LmManager::kTemplUnsub) { // if templates are needed

    _fTempl = LmHelper::SafelyOpenRootfile(Form("./input/PhiV/templates/spectra3D_%i.root", (int)(1000 * kSetMinPtLabel)));
    hSig = (TH3D*)LmHelper::GetHistFromTemplateFile(_fTempl, 0, "hUnlike", kTRUE);
    hSig->SetName("hSig"); // prompt
    hULS = (TH3D*)LmHelper::GetHistFromTemplateFile(_fTempl, 0, "hUnlike", kTRUE);
    hULS->SetName("hULS"); // prompt
    hLS = (TH3D*)LmHelper::GetHistFromTemplateFile(_fTempl, 0, "hBkg", kTRUE);
    hLS->SetName("hLS"); // prompt

    //hCon       = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl, 2, "hUnlike");  hCon->SetName("hCon");                // file 5 conversions
    //hDiffGa    = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl, 4, "hUnlike");  hDiffGa->SetName("hDiffGamma");       // file 5 diff gamma ULS
    //hDiffGa_LS = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl, 4, "hBkg");     hDiffGa_LS->SetName("hDiffGamma_LS"); // file 5 diff gamma LS
    //hDiffGa->Add(hDiffGa_LS, -1); // diff gamma subtracted
    //hNorm = (TH3D*) hSig->Clone("hNorm");
    //hNorm->Add(hDiffGa);
  }

  if (kUseSuperConfig) {

    gStyle->SetErrorX(0);
    gStyle->SetEndErrorSize(0);

    Int_t Nslices = 0;
    if (kDoMassSlices)
      Nslices = n_mee_slices;
    else
      Nslices = n_ptee_slices;

    LmSignal* sig_combined = 0x0;
    LmHandler* han_combined = 0x0;
    han_combined = new LmHandler(binsPtee_forMee, binsMee_forPtee, plotMeeMin, plotMeeMax, plotPteeMin, plotPteeMax);
    han_combined->SetName("Data");

    LmHandler* hanCompare = new LmHandler(binsPtee_forMee, binsMee_forPtee, plotMeeMin, plotMeeMax, plotPteeMin, plotPteeMax);
    // attach signals to compare handler. they may already be processed or not.
    if (kDoMassSlices) {
      if (Nslices > 0) hanCompare->SetBinningPtee(0, &binsPtee_plotting_0);
      if (Nslices > 1) hanCompare->SetBinningPtee(1, &binsPtee_plotting_0);
      if (Nslices > 2) hanCompare->SetBinningPtee(2, &binsPtee_plotting_1);
      if (Nslices > 3) hanCompare->SetBinningPtee(3, &binsPtee_plotting_2);
      if (Nslices > 4) hanCompare->SetBinningPtee(4, &binsPtee_plotting_3);
      if (Nslices > 5) hanCompare->SetBinningPtee(5, &binsPtee_plotting_5);
    } else {
      if (kDoNonLogY) {
        if (Nslices > 0) hanCompare->SetBinningMee(0, &binsMee_plotting_0);
        if (Nslices > 1) hanCompare->SetBinningMee(1, &binsMee_plotting_1);
        if (Nslices > 2) hanCompare->SetBinningMee(2, &binsMee_plotting_2);
        if (Nslices > 3) hanCompare->SetBinningMee(3, &binsMee_plotting_3);
        if (Nslices > 4) hanCompare->SetBinningMee(4, &binsMee_plotting_4);
        if (Nslices > 5) hanCompare->SetBinningMee(5, &binsMee_plotting_5);
      } else {
        if (Nslices > 0) hanCompare->SetBinningMee(0, &binsMee_plotting);
        if (Nslices > 1) hanCompare->SetBinningMee(1, &binsMee_plotting);
        if (Nslices > 2) hanCompare->SetBinningMee(2, &binsMee_plotting);
        if (Nslices > 3) hanCompare->SetBinningMee(3, &binsMee_plotting);
        if (Nslices > 4) hanCompare->SetBinningMee(4, &binsMee_plotting);
        if (Nslices > 5) hanCompare->SetBinningMee(5, &binsMee_plotting);
      }
    }

    for (int ic = 0; ic < n_sconfig; ic++) {
      // create manager from config string
      LmManager* mgr_i = new LmManager(const_cast<char*>(sconfig[ic].DataConfig.Data())); // TODO: input style to be optimized
      // set all kinds of configuration for the manager
      mgr_i->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
      mgr_i->SetProjOption(projoption);
      mgr_i->SetEnableEffiCorr(kDoEffiCorrection);
      mgr_i->SetCentRange(0., 20.);
      //mgr00->SetEnableRebinning(kFALSE); // use this to disable or just comment out the setter above...
      // configure 3D exclusion cut
      mgr_i->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
      mgr_i->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
      mgr_i->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
      mgr_i->SetTemplateNormRegionMin(n_cutPhiVbelow, cutPhiVbelow); // only needed for some template types.
      mgr_i->SetTemplateNormRegionMax(n_cutPhiVabove, cutPhiVabove); // only needed for some template types.
      if (kDoPhiVCut == LmManager::kTemplSub) mgr_i->SetExclusionZTemplates(hSig, 0x0, LmManager::kTemplSub /*, hSig, hNorm*/);
      //if (kDoPhiV==LmManager::kTemplConv)  mgr->SetExclusionZTemplates(hCon    , 0x0, LmManager::kTemplConv , hSig, hNorm);
      if (kDoPhiVCut == LmManager::kTemplUnsub) mgr_i->SetExclusionZTemplates(hULS, hLS, LmManager::kTemplUnsub, hSig, hNorm);
      mgr_i->SetEnableExclusionCutZ(kDoExclusionCutZ);
      // process the manager

      if (kDoEffiCorrectionFirst)
        mgr_i->SetDoEffiCorr();
      mgr_i->SetRebinning2D(n_mee_bin, mee_bin.data(), n_ptee_bin, ptee_bin.data());
      mgr_i->SetEtaRange(-0.8, 0.8);
      mgr_i->SetPtRange(kSetMinPtLabel, kSetMaxPtLabel);
      mgr_i->Process();

      LmBackground* bkg_i = new LmBackground(*(mgr_i));
      bkg_i->SetUseRfactor(kDoRfactor);
      bkg_i->SetRfactorUnityRange(0.5);
      bkg_i->Process(sconfig[ic].BkgEstimator);
      bkgVec.push_back(bkg_i);

      // Need to give phiV-corrected subtracted raw spectra to the manager before LmSignal::Process() is called.
      // Only then the LmManager::SignalPostCorrection(hSub) modifies the subtracted yield before SoverB and Signif are
      // computed from it. The difficulty is that the phiV template fit happens in 1D (projection binning of handler),
      // while the signal is processed in 2D (2D rebinning in (base)manager). Therefore use same binning (ptee_bin_4D)!
      TFile* _fPhiVcorr[48];
      std::vector<TH1D*> vhPhiVcorr;
      if (kDoPhiVCut == LmManager::kTemplSub) {
        for (int i = 0; i < n_ptee_bin; ++i) {
          _fPhiVcorr[i] = LmHelper::SafelyOpenRootfile(Form("./input/PhiV/%iMeV_%i_%i/spectra1D-phiVstudy-ptee%.0fto%.0f_%iMeV.root", (int)(1000 * kSetMinPtLabel), sconfig[ic].LowerCent, sconfig[ic].UpperCent, ptee_bins[i] * 1000, ptee_bins[i + 1] * 1000, (int)(1000 * kSetMinPtLabel)));
          //_fPhiVcorr[i] = LmHelper::SafelyOpenRootfile(Form("./input/PhiV/%iMeV/spectra1D-phiVstudy-ptee%.0fto%.0f_%iMeV.root",(int)(1000*kSetMinPtLabel),ptee_bins[i]*1000,ptee_bins[i+1]*1000,(int)(1000*kSetMinPtLabel)));
          vhPhiVcorr.push_back((TH1D*)LmHelper::GetHistFromTemplateFile(_fPhiVcorr[i], 0, "hSubSig-mee0.00to3.14", kFALSE));
          vhPhiVcorr.at(i)->SetName(Form("hSubSig-ptee%.0fto%.0f", ptee_slices[i], ptee_slices[i + 1]));
        }
        TH2D* hSubSig_phiVcorr = LmHelper::MakeHist2Dfrom1D(vhPhiVcorr, "hSubSig_phiVcorr", n_ptee_bin, ptee_bins);
        const Char_t* filename3 = "test4.root";
        TFile* _fileOut3 = new TFile(filename3, "RECREATE");
        hSubSig_phiVcorr->Write();
        _fileOut3->Close();

        mgr_i->AddCorrectedSig(hSubSig_phiVcorr, Form("h2_correctedSignal_%i", ic));
        delete hSubSig_phiVcorr;
      }

      mgrVec.push_back(mgr_i);
      mgr_i->SetPlotRangeZ(0., 0.4);
      mgr_i->Print2DEffi();
      mgr_i->Print2DAcce();
      mgr_i->Print2DUnlike();
      mgr_i->Print2DLikePP();
      mgr_i->Print2DLikeMM();

      LmSignal* sig_i = new LmSignal(*(mgrVec.at(0)), *(bkgVec.at(0)));
      //sig_i->SetDoSubtraction(kFALSE);
      //if(kDoEffiCorrectionFirst) sig_i->SetEffiApplied(kTRUE);
      sig_i->SetDoSignifRaw(kDoSignifRaw);
      sig_i->SetDoNormBinwidth(kDoNormBinwidth);
      sig_i->SetDoNormNevents(kDoNormNevents);
      sig_i->SetCrossSection(sconfig[ic].CrossSection);
      sig_i->SetDoNormCrossSection(kDoNormCrossSection);
      sig_i->SetTrgEff(sconfig[ic].TriggerEfficiency);
      sig_i->SetDoNormTrgEff(kDoNormTrgEff);
      sig_i->SetDoNormRecEff(kDoNormRecEff);
      sig_i->SetVtxRecEff(sconfig[ic].VtxRecEff);
      sig_i->SetDoNormVtxRecEff(kDoNormVtxRecEff);
      sig_i->SetVtxRecEffee(sconfig[ic].VtxRecEffee);
      sig_i->SetDoNormVtxRecEffee(kDoNormVtxRecEffee);
      sig_i->SetDoAcceCorr(kDoAcceptanceCorrection);
      sig_i->Process(LmSignal::kStd);
      sigVec.push_back(sig_i);

      //LmHandler* han_systematic = new LmHandler(binsPtee_forMee_sys,binsMee_forPtee_sys,plotMeeMin,plotMeeMax_sys,plotPteeMin,plotPteeMax_sys);
      //han_systematic->SetName("han_systematic");

      std::vector<LmSignal*> sigVec_final;
      std::vector<TString> sigNames_final;
      TString finalSigName = "";
      if (kDoCombineSpectra) {

        if (kDoMergeMultiple) {

          std::cout << "++++++++++++++++++++++++++++++++ ENTERED MERGE MULT ++++++++++++++++++++++++++++++++" << std::endl;

          if (ic % kMergeNSettings == 0 && ic > 0) {
            std::cout << "++++++++++++++++++++++++++++++++ new combined handler ++++++++++++++++++++++++++++++++" << std::endl;
            han_combined = new LmHandler(binsPtee_forMee, binsMee_forPtee, plotMeeMin, plotMeeMax, plotPteeMin, plotPteeMax);
            han_combined->SetName(Form("combined data v%i", ic));
            std::cout << "++++++++++++++++++++++++++++++++ exiting new combined handler ++++++++++++++++++++++++++++++++" << std::endl;
          }

          if (ic < kStartMergeAt || ic >= kStopMergeAt) {
            std::cout << "++++++++++++++++++++++++++++++++ skipping this setting ++++++++++++++++++++++++++++++++" << std::endl;
            continue;
          }
          for (unsigned int iSig = 0; iSig < sigVec.size(); iSig++) {
            std::cout << "++++++++++++++++++++++++++++++++ adding setting to comb handler ++++++++++++++++++++++++++++++++" << std::endl;
            han_combined->AttachSignal(*(sigVec.at(iSig)));
          }

          han_combined->Process(LmHandler::kCompare);
          //if(ic>=(kStartMergeAt*kMergeNSettings) && ic<(kStopMergeAt*kMergeNSettings))
          //  han_combined->Process(LmHandler::kCombine);

          if (!kDoPlotCombineOnly) {
            std::cout << "++++++++++++++++++++++++++++++++ adding setting to comp handler ++++++++++++++++++++++++++++++++" << std::endl;
            if (ic < kStartMergeAt || ic >= kStopMergeAt)
              continue;
            for (unsigned int iSig = 0; iSig < sigVec.size(); iSig++)
              hanCompare->AttachSignal(*(sigVec.at(iSig)));
          }
          if (ic % kMergeNSettings == (kMergeNSettings - 1)) {
            std::cout << "++++++++++++++++++++++++++++++++ combining and adding new signal ++++++++++++++++++++++++++++++++" << std::endl;
            han_combined->Process(LmHandler::kCompare);
            han_combined->Process(LmHandler::kCombine);
            sig_combined = han_combined->GetLmSigCombined();
            hanCompare->AttachSignal(*sig_combined, Form("combined data v%i", ic));

            if (kDoCocktailSubtraction) {
              hanCompare->Process(LmHandler::kCompare);
              hanCompare->Process(LmHandler::kSubtractCocktail); // last cocktail is subtracted from data. projections are done first if needed.
              hanCompare->Process(LmHandler::kCocktail);

            } else if (kDoCocktailSubtraction2D) {
              hanCompare->Process(LmHandler::kSubtractCocktail2D);
              hanCompare->Process(LmHandler::kCompare);
              hanCompare->Process(LmHandler::kCocktail);
            } else {
              hanCompare->Process(LmHandler::kCompare);
              hanCompare->Process(LmHandler::kCocktail);
            }

            mgrVec.clear();
            bkgVec.clear();
            sigVec.clear();

          } else {
            mgrVec.clear();
            bkgVec.clear();
            sigVec.clear();
            continue;
          }

          //for(Int_t i = 0; i<ic/kMergeNSettings; i++){
          //  han_combined = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
          //  han_combined->SetName(Form("combined 2016/17 v%s", sigVec.at(kMergeNSettings*i)->GetName()));

          //for(Int_t j = 0; j <kMergeNSettings; j++){
          //  if((kMergeNSettings*i+j)<kStartMergeAt || (kMergeNSettings*i+j)>=kStopMergeAt)
          //    continue;
          //  han_combined->AttachSignal(*(sigVec.at(kMergeNSettings*i+j)));
          //}

          //han_combined->Process(LmHandler::kCompare);
          //if(i>=(kStartMergeAt*kMergeNSettings) && i<(kStopMergeAt*kMergeNSettings))
          //  han_combined->Process(LmHandler::kCombine);

          //if(!kDoPlotCombineOnly){
          //  for(Int_t j=0; j <kMergeNSettings; j++){
          //    if((kMergeNSettings*i+j)<kStartMergeAt || (kMergeNSettings*i+j)>=kStopMergeAt)
          //      continue;
          //    hanCompare->AttachSignal(*(sigVec.at(kMergeNSettings*i+j)));
          //  }
          //}
          //sig_combined = han_combined->GetLmSigCombined();

          //if (kDoFixedSystematics == kTRUE){
          //  TFile* h2_unc = TFile::Open("h2_unc_save2.root", "READ");
          //  h2_unc->cd();
          //      //    TH2D* own_systematic = (TH2D*)(h2_unc->Get("h2_sys_unc")->Clone("h2_sys_uncertainties"));
          //  TH2D* own_systematic = (TH2D*)(h2_unc->Get(Form("h2_sys_unc_%i", (int)(1000*kSetMinPtLabel)))->Clone("h2_sys_uncertainties"));
          //  sig_combined->SetSymmetricRelSystematics(own_systematic);
          //  sig_combined->Process(LmSignal::kSystematic);
          //}

          //hanCompare->AttachSignal(*sig_combined,Form("combined 2016/17 %c%c<%c%c%c", sigVec.at(2*i)->GetName()[0], sigVec.at(2*i)->GetName()[1], sigVec.at(2*i)->GetName()[2], sigVec.at(2*i)->GetName()[3], sigVec.at(2*i)->GetName()[4]));
          ////hanCompare->AttachSignal(*sig_combined, sigVec.at(kMergeNSettings*i)->GetName());
          //}
        }

        else if (ic < 4) {

          for (unsigned int iSig = 0; iSig < sigVec.size(); iSig++)
            han_combined->AttachSignal(*(sigVec.at(iSig)));

          if (!kDoPlotCombineOnly) {

            for (unsigned int i = 0; i < sigVec.size(); i++) {
              if (kDoPlotOnlyFirstIn && i == 0) break;
              //if (kDoFixedSystematics == kTRUE){
              //  TFile* h2_unc = TFile::Open("h2_unc_save2.root", "READ");
              //  h2_unc->cd();
              //            //  TH2D* own_systematic = (TH2D*)(h2_unc->Get("h2_sys_unc")->Clone("h2_sys_uncertainties"));
              //  TH2D* own_systematic = (TH2D*)(h2_unc->Get(Form("h2_sys_unc_%i", (int)(1000*kSetMinPtLabel)))->Clone("h2_sys_uncertainties"));
              //  sigVec.at(i)->SetSymmetricRelSystematics(own_systematic);
              //  sigVec.at(i)->Process(LmSignal::kSystematic);
              //  h2_unc->Close();
              //}
              hanCompare->AttachSignal(*(sigVec.at(i)));
            }
          }

          mgrVec.clear();
          bkgVec.clear();
          sigVec.clear();
        }

      }

      else {
        for (unsigned int i = 0; i < sigVec.size(); i++) {
          if (kDoPlotOnlyFirstIn && ic > 0) break;

          if (kDoFixedSystematics == kTRUE) {
            TFile* h2_unc = TFile::Open("h2_unc_save2.root", "READ");
            h2_unc->cd();
            //        TH2D* own_systematic = (TH2D*)(h2_unc->Get("h2_sys_unc")->Clone("h2_sys_uncertainties"));
            TH2D* own_systematic = (TH2D*)(h2_unc->Get(Form("h2_sys_unc_%i", (int)(1000 * kSetMinPtLabel)))->Clone("h2_sys_uncertainties"));
            sigVec.at(i)->SetSymmetricRelSystematics(own_systematic);
            sigVec.at(i)->Process(LmSignal::kSystematic);
          }
          hanCompare->AttachSignal(*(sigVec.at(i)));
        }
        mgrVec.clear();
        bkgVec.clear();
        sigVec.clear();
      }

      //mgrVec.clear();
      //bkgVec.clear();
      //sigVec.clear();

      hanCompare->SetPlotRangeRatio(kRatioLow, kRatioHigh);
      if (!kDoNormCrossSection)
        hanCompare->SetPlotRangeY(1e-6, 5);
      else {
        if (kDoMassSlices)
          hanCompare->SetPlotRangeY(1e-5, 10);
        else
          hanCompare->SetPlotRangeY(1e-5, 100);
      }

      //hanCompare->SetLabels(LmHelper::GetLabelsTemplate(LmHelper::kPreliminary));
      hanCompare->SetLegendSizeInYScaling(1.8);
      hanCompare->SetDoRatio(kDoRatio, 0.25, kDoRatioLog);
      hanCompare->SetConfidenceLevel(confLevel);
      hanCompare->SetDoConfidenceLevel(kDoConfLevel);
      if (!kDoCocktailSubtraction2D /* && kDoCombineSpectra*/)
        hanCompare->Process(LmHandler::kCompare);

      LmCocktail* cockt00 = 0x0;
      LmCocktail* cocktLF = 0x0;
      LmCocktail* cocktLFrest = 0x0;
      LmCocktail* cocktHF = 0x0;
      LmCocktail* cocktKW = 0x0;
      LmCocktail* cocktTH = 0x0;
      LmCocktail* cocktTH2 = 0x0;
      LmCocktail* cocktHB = 0x0;

      if (kDoCocktail) {

        std::cout << "CocktailVersion:" << sconfig[ic].CocktailVersion << "  name: " << (cocktail_histograms[sconfig[ic].CocktailVersion].Data()) << std::endl;

        Printf("______ process cocktail ______");
        LmCocktailMan* cocktmanReso = new LmCocktailMan();
        LmCocktailMan* cocktmanEta = new LmCocktailMan();
        LmCocktailMan* cocktmanRest = new LmCocktailMan();
        LmCocktailMan* cocktmanKW = new LmCocktailMan();
        cocktmanReso->SetInputfiles(const_cast<char*>(sconfig[ic].LFCocktail.Data()));
        cocktmanReso->SetInputfilesAndHistsLow(const_cast<char*>(sconfig[ic].LFCocktailLower.Data()), const_cast<char*>(cocktail_histograms[sconfig[ic].CocktailVersion /*+1*/ /*+13*/].Data()));  // 2D
        cocktmanReso->SetInputfilesAndHistsHigh(const_cast<char*>(sconfig[ic].LFCocktailUpper.Data()), const_cast<char*>(cocktail_histograms[sconfig[ic].CocktailVersion /*+2*/ /*+18*/].Data())); // 2D
        cocktmanReso->SetInputlists(const_cast<char*>(cocktail_list[0].Data()));
        cocktmanReso->SetInputhistAndDim(const_cast<char*>(cocktail_histograms[sconfig[ic].CocktailVersion].Data()), 2); // 2D
        if (kDoReducedCocktail) {
          cocktmanReso->SetInputhistAndDim(const_cast<char*>(cocktail_histograms[9 + 2].Data()), 2);                                                         // 2D
          cocktmanReso->SetInputfilesAndHistsLow(const_cast<char*>(sconfig[ic].LFCocktailLower.Data()), const_cast<char*>(cocktail_histograms[11].Data()));  // 2D
          cocktmanReso->SetInputfilesAndHistsHigh(const_cast<char*>(sconfig[ic].LFCocktailUpper.Data()), const_cast<char*>(cocktail_histograms[11].Data())); // 2D
        }
        cocktmanReso->SetArbitraryScaling(sconfig[ic].DoResoScaling);
        cocktmanReso->SetHistForNevents("NEvents");
        cocktmanReso->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
        if (kDoLFsum)
          cocktmanReso->Process(LmCocktailMan::kLFsum);
        else
          cocktmanReso->Process(LmCocktailMan::kResonances);

        if (kDoScaleEtaSeperate) {
          cocktmanEta->SetInputfiles(const_cast<char*>(sconfig[ic].LFCocktail.Data()));
          cocktmanEta->SetInputfilesAndHistsLow(const_cast<char*>(sconfig[ic].LFCocktailLower.Data()), const_cast<char*>(cocktail_histograms[2].Data()));  // 2D
          cocktmanEta->SetInputfilesAndHistsHigh(const_cast<char*>(sconfig[ic].LFCocktailUpper.Data()), const_cast<char*>(cocktail_histograms[2].Data())); // 2D
          cocktmanEta->SetInputlists(const_cast<char*>(cocktail_list[0].Data()));
          cocktmanEta->SetInputhistAndDim(const_cast<char*>(cocktail_histograms[2].Data()), 2); // 2D
          cocktmanEta->SetHistForNevents("NEvents");
          cocktmanEta->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
          cocktmanEta->SetArbitraryScaling(kDoEtaScaling);
          cocktmanEta->Process(LmCocktailMan::kResonances);
        }

        if (kDoReducedCocktail) {
          cocktmanRest->SetInputfiles(const_cast<char*>(sconfig[ic].LFCocktail.Data()));
          cocktmanRest->SetInputfilesAndHistsLow(const_cast<char*>(sconfig[ic].LFCocktailLower.Data()), const_cast<char*>(cocktail_histograms[12].Data()));  // 2D
          cocktmanRest->SetInputfilesAndHistsHigh(const_cast<char*>(sconfig[ic].LFCocktailUpper.Data()), const_cast<char*>(cocktail_histograms[12].Data())); // 2D

          cocktmanRest->SetInputlists(const_cast<char*>(cocktail_list[0].Data()));
          cocktmanRest->SetInputhistAndDim(const_cast<char*>(cocktail_histograms[10 + 2].Data()), 2); // 2D
          cocktmanRest->SetArbitraryScaling(sconfig[ic].DoResoScaling);
          cocktmanRest->SetHistForNevents("NEvents");
          cocktmanRest->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
          cocktmanRest->Process(LmCocktailMan::kLFsum);
        }

        std::cout << "--- HEAVY FLAVOUR COCKTAIL ---" << std::endl;
        // for heavy flavours
        LmCocktailMan* cocktmanHF = new LmCocktailMan();
        cocktmanHF->SetNormMidRap(kDoNormMidRap);
        cocktmanHF->SetInputfiles(const_cast<char*>(sconfig[ic].HFCocktail.Data()));
        cocktmanHF->SetInputlists(const_cast<char*>(heavyfl_list.Data()));
        cocktmanHF->SetInputhistAndDim(const_cast<char*>(sconfig[ic].HFCocktailHistograms.Data()), 2); // 2D
        //cocktmanHF->SetRelUncertainties("+0.11:-0.11:+0.23:-0.23");
        cocktmanHF->SetArbitraryScaling(2.0 * sconfig[ic].DoHFScaling); // was 2 edit jerome (1.09 Theo) // when using nquarks histogram instead of nevents, by which the yield gets downscaled about 2 times stronger.
        cocktmanHF->SetHistForNeventsHF(const_cast<char*>(heavyfl_hist_Nevents[0].Data()));
        cocktmanHF->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
        cocktmanHF->Process(LmCocktailMan::kHeavyFl);
        // for virtual photons
        // (not available yet)

        //for J/psi
        Printf(" * J/psi");
        LmCocktailMan* cocktmanJpsi = new LmCocktailMan();
        cocktmanJpsi->SetInputfiles(const_cast<char*>(jpsi_files[0].Data()));
        cocktmanJpsi->SetInputhistAndDim(const_cast<char*>(jpsi_histograms[3].Data()), 2);
        cocktmanJpsi->SetInputfilesAndHistsLow(const_cast<char*>(jpsi_files[1].Data()), const_cast<char*>(jpsi_histograms[3].Data()));  // 2D
        cocktmanJpsi->SetInputfilesAndHistsHigh(const_cast<char*>(jpsi_files[2].Data()), const_cast<char*>(jpsi_histograms[3].Data())); // 2D
        cocktmanJpsi->SetInputlists(const_cast<char*>(jpsi_list[1].Data()));
        cocktmanJpsi->SetArbitraryScaling(12.16 / 7.48 * sconfig[ic].DoHFScaling /** 1.076*/); //ccbar cross section 13TeV/7TeV
        //cocktmanJpsi->SetRelUncertainties("+0.16:-0.14");
        cocktmanJpsi->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
        cocktmanJpsi->Process(LmCocktailMan::kJpsi);

        LmCocktailMan* cocktmanRapp = new LmCocktailMan();
        LmCocktailMan* cocktmanRapp2 = new LmCocktailMan();
        if (kDoRapp) {
          if (!kDoMassSlices) {
            cocktmanRapp->SetInputfiles("./input/cocktail_theory/rapp_13TeV_pp_LMR_mee_30.txt");
            if (kDoMultiTheo) {
              cocktmanRapp->SetInputlists(
                "\
              %lg %*lg %*lg %*lg %*lg %*lg %*lg  %lg:\
              "); // sum
              cocktmanRapp->SetInputhistAndDim("RappSum", 1);
            } else {
              cocktmanRapp->SetInputlists(
                "\
              %lg %*lg %*lg %lg:\
              %lg %*lg %*lg %*lg %*lg %lg:\
              "); // sum
              cocktmanRapp->SetInputhistAndDim("HGmed:QGP", 1);
            }
            cocktmanRapp->SetArbitraryScaling(kRappScaling);
            //cocktman_Rapp->SetArbitraryScaling(0.797 * 1930 * cocktman_Rapp->GetArbitraryScaling() );
            cocktmanRapp->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
            cocktmanRapp->Process(LmCocktailMan::kRappMee);

            cocktmanRapp2->SetInputfiles("./input/cocktail_theory/rapp_13TeV_pp_LMR_mee_30.txt");
            if (kDoMultiTheo) {
              cocktmanRapp2->SetInputlists(
                "\
              %lg %*lg %*lg %*lg %*lg %*lg %*lg  %lg:\
              "); // sum
              cocktmanRapp2->SetInputhistAndDim("RappSumUnc", 1);
            } else {
              cocktmanRapp2->SetInputlists(
                "\
              %lg %*lg %*lg %lg:\
              %lg %*lg %*lg %*lg %*lg %lg:\
              "); // sum
              cocktmanRapp2->SetInputhistAndDim("HGmed:QGP", 1);
            }
            cocktmanRapp2->SetArbitraryScaling(kRappScaling);
            //cocktman_Rapp->SetArbitraryScaling(0.797 * 1930 * cocktman_Rapp->GetArbitraryScaling() );
            cocktmanRapp2->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
            cocktmanRapp2->Process(LmCocktailMan::kRappMee);

          } else {
            cocktmanRapp->SetInputfiles("./input/cocktail_theory/rapp_13TeV_pp_LMR_ptee_30.txt");
            //cocktmanRapp->SetInputfiles("./input/cocktail_theory/dndptM015-06pp13TeVmb.txt");
            if (kDoMultiTheo) {
              cocktmanRapp->SetInputlists(
                "\
              %lg %*lg %*lg %*lg %*lg %lg:\
              "); // sum
              cocktmanRapp->SetInputhistAndDim("RappSum", 1);
            } else {
              cocktmanRapp->SetInputlists(
                "\
              %lg %*lg %lg:\
              %lg %*lg %*lg %*lg %lg:\
              "); // sum
              cocktmanRapp->SetInputhistAndDim("HGmed:QGP", 1);
            }
            cocktmanRapp->SetArbitraryScaling(kRappScaling);
            cocktmanRapp->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
            cocktmanRapp->Process(LmCocktailMan::kRappPtee);

            cocktmanRapp2->SetInputfiles("./input/cocktail_theory/rapp_13TeV_pp_LMR_ptee_30.txt");
            //cocktmanRapp2->SetInputfiles("./input/cocktail_theory/dndptM015-06pp13TeVmb.txt");
            if (kDoMultiTheo) {
              cocktmanRapp2->SetInputlists(
                "\
              %lg %*lg %*lg %*lg %*lg %lg:\
              "); // sum
              cocktmanRapp2->SetInputhistAndDim("RappSumUnc", 1);
            } else {
              cocktmanRapp2->SetInputlists(
                "\
              %lg %*lg %lg:\
              %lg %*lg %*lg %*lg %lg:\
              "); // sum
              cocktmanRapp2->SetInputhistAndDim("HGmed:QGP", 1);
            }
            cocktmanRapp2->SetArbitraryScaling(kRappScaling);
            cocktmanRapp2->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
            cocktmanRapp2->Process(LmCocktailMan::kRappPtee);
          }
        }

        LmCocktailMan* cocktmanBrems = new LmCocktailMan();
        if (kDoBrems) {
          if (!kDoMassSlices)
            cocktmanBrems->SetInputfiles("./input/cocktail_theory/Brems_mee_wReso.txt");
          else
            cocktmanBrems->SetInputfiles("./input/cocktail_theory/Brems_ptee.txt");
          cocktmanBrems->SetInputlists(
            "\
          %lg %lg:\
          ");
          cocktmanBrems->SetInputhistAndDim("HadrBrems", 1);
          cocktmanBrems->SetArbitraryScaling(kBremsScaling);
          cocktmanBrems->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
          if (!kDoMassSlices)
            cocktmanBrems->Process(LmCocktailMan::kFromFileMee);
          else
            cocktmanBrems->Process(LmCocktailMan::kFromFilePtee);
        }

        // cocktail (handles the cocktail spectra)
        cockt00 = new LmCocktail(LmCocktail::kpp_MB_13, "Cocktail", kDoNormMidRap);
        cocktLF = new LmCocktail(LmCocktail::kpp_MB_13, "Cocktail", kDoNormMidRap);
        cocktHF = new LmCocktail(LmCocktail::kpp_MB_13, "Cocktail", kDoNormMidRap);
        cocktKW = new LmCocktail(LmCocktail::kpp_MB_13, "CocktailKW", kDoNormMidRap);
        cocktTH = new LmCocktail(LmCocktail::kpp_MB_13, "CocktailTH", kDoNormMidRap);
        cocktTH2 = new LmCocktail(LmCocktail::kpp_MB_13, "CocktailTH", kDoNormMidRap);
        cocktHB = new LmCocktail(LmCocktail::kpp_MB_13, "CocktailHB", kDoNormMidRap);

        if (kDoPublished13TeVpythia) {
          cockt00 = new LmCocktail(LmCocktail::kpp_MB_13pythia, "Cocktail", kDoNormMidRap);
          cocktLF = new LmCocktail(LmCocktail::kpp_MB_13pythia, "Cocktail", kDoNormMidRap);
          cocktHF = new LmCocktail(LmCocktail::kpp_MB_13pythia, "Cocktail", kDoNormMidRap);
          cocktKW = new LmCocktail(LmCocktail::kpp_MB_13pythia, "CocktailKW", kDoNormMidRap);
          cocktTH = new LmCocktail(LmCocktail::kpp_MB_13pythia, "CocktailTH", kDoNormMidRap);
          cocktTH2 = new LmCocktail(LmCocktail::kpp_MB_13pythia, "CocktailTH", kDoNormMidRap);
          cocktHB = new LmCocktail(LmCocktail::kpp_MB_13pythia, "CocktailHB", kDoNormMidRap);
        }
        if (kDoPublished13TeVpowheg) {
          cockt00 = new LmCocktail(LmCocktail::kpp_MB_13powheg, "Cocktail", kDoNormMidRap);
          cocktLF = new LmCocktail(LmCocktail::kpp_MB_13powheg, "Cocktail", kDoNormMidRap);
          cocktHF = new LmCocktail(LmCocktail::kpp_MB_13powheg, "Cocktail", kDoNormMidRap);
          cocktKW = new LmCocktail(LmCocktail::kpp_MB_13powheg, "CocktailKW", kDoNormMidRap);
          cocktTH = new LmCocktail(LmCocktail::kpp_MB_13powheg, "CocktailTH", kDoNormMidRap);
          cocktTH2 = new LmCocktail(LmCocktail::kpp_MB_13powheg, "CocktailTH", kDoNormMidRap);
          cocktHB = new LmCocktail(LmCocktail::kpp_MB_13powheg, "CocktailHB", kDoNormMidRap);
        }
        if (!kDoHFonly) cockt00->AttachManager(*cocktmanReso);
        if (kDoEtaScaling != 1.) cockt00->AttachManager(*cocktmanEta);
        if (!kDoLFonly) cockt00->AttachManager(*cocktmanHF);
        if (!kDoLFonly && !kDoHFonly && kDoJPsi) cockt00->AttachManager(*cocktmanJpsi);
        if (kDoRapp && kDoAddRapp) cockt00->AttachManager(*cocktmanRapp);
        if (kDoBrems && kDoAddBrems) cockt00->AttachManager(*cocktmanBrems);
        if (kDoReducedCocktail) cockt00->AttachManager(*cocktmanRest);

        cockt00->SetDrawStyleErr("E3");
        cocktLF->SetDrawStyleErr("E3");
        cocktHF->SetDrawStyleErr("E3");
        cocktTH->SetDrawStyleErr("E3");
        cocktTH2->SetDrawStyleErr("E3");
        cocktHB->SetDrawStyleErr("E3");
        cockt00->SetDrawStyle("hist c");
        cocktLF->SetDrawStyle("hist c");
        cocktHF->SetDrawStyle("hist c");
        cocktTH->SetDrawStyle("hist c");
        cocktTH2->SetDrawStyle("hist c");
        cocktHB->SetDrawStyle("hist c");

        if (kDoDrawOnlyFirstCock && ic > 1 - 1) {
          cockt00->SetDrawStyleErr("hist c");
          cocktLF->SetDrawStyleErr("hist c");
          cocktHF->SetDrawStyleErr("hist c");
          cocktTH->SetDrawStyleErr("hist c");
          cocktTH2->SetDrawStyleErr("hist c");
          cocktHB->SetDrawStyleErr("hist c");
        }
        //cocktTH->SetAdditionalRelUncertainty(LmCocktailPart::kQGP, -0., 4.15);
        //cocktTH->SetAdditionalRelUncertainty(LmCocktailPart::kHGmed, -0., 4.2);
        //if(kDoDrawOnlyFirstCock/* && ic==1*/){
        //  cockt00->SetDrawOption(LmCocktail::kAllButSum);
        //}
        cocktLF->AttachManager(*cocktmanReso);
        cocktHF->AttachManager(*cocktmanHF);
        if (kDoSUMonly || (kDoDrawOnlyFirstCock && ic > 1 - 1))
          cockt00->SetDrawOption(LmCocktail::kOnlySum);
        else if (kDoSUMnot) {
          cockt00->SetDrawOption(LmCocktail::kAllButSum);
          cockt00->SetDrawStyleErr("hist c");
          cocktTH->SetDrawOption(LmCocktail::kAllButSum);
          cocktTH->SetDrawStyleErr("hist c");
          cocktTH2->SetDrawOption(LmCocktail::kAllButSum);
          cocktTH2->SetDrawStyleErr("hist c");

          cocktHB->SetDrawOption(LmCocktail::kAllButSum);
          cocktHB->SetDrawStyleErr("hist c");
        }

        if (kDoRapp && !kDoAddRapp) {
          std::cout << "--- Rapp Cock ---" << std::endl;
          cocktTH->AttachManager(*cocktmanRapp);
          //cocktTH->AttachManager( *cocktmanRapp2 );

          cocktTH->SetDoNormBinwidth(kTRUE);
          cocktTH->SetDoNormCrossSection(kDoNormCrossSectionCocktail);
          cocktTH->SetCrossSection(kCrossSection);
          cocktTH->Process(); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...
          // only needed if cocktail shall be projected and plotted stand-alone:
          //cocktTH->SetBinsPtee_forprojMee(binsPtee_forMee);
          //cocktTH->SetBinsMee_forprojPtee(binsMee_forPtee);
          //cocktTH->MakeSpectra1D(); // do projections according to attached binning.
          std::cout << "--- Rapp Cock ---" << std::endl;

          std::cout << "--- Rapp Cock ---" << std::endl;
          cocktTH2->AttachManager(*cocktmanRapp2);
          //cocktTH->AttachManager( *cocktmanRapp2 );

          cocktTH2->SetDoNormBinwidth(kTRUE);
          cocktTH2->SetDoNormCrossSection(kDoNormCrossSectionCocktail);
          cocktTH2->SetCrossSection(kCrossSection);
          cocktTH2->Process(); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...
          // only needed if cocktail shall be projected and plotted stand-alone:
          //cocktTH->SetBinsPtee_forprojMee(binsPtee_forMee);
          //cocktTH->SetBinsMee_forprojPtee(binsMee_forPtee);
          //cocktTH->MakeSpectra1D(); // do projections according to attached binning.
          std::cout << "--- Rapp Cock ---" << std::endl;
        }

        if (kDoBrems && !kDoAddBrems) {
          std::cout << "--- Brems Cock ---" << std::endl;
          cocktHB->AttachManager(*cocktmanBrems);
          std::cout << "--- Brems Cock ---" << std::endl;
          cocktHB->SetDoNormBinwidth(kTRUE);
          //cocktTH->SetDoNormNevents(kTRUE);
          cocktHB->SetDoNormCrossSection(kDoNormCrossSectionCocktail);
          cocktHB->SetCrossSection(kCrossSection);
          std::cout << "--- Brems Cock ---" << std::endl;
          cocktHB->Process(); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...
          std::cout << "--- Brems Cock ---" << std::endl;
          // only needed if cocktail shall be projected and plotted stand-alone:
          //cocktTH->SetBinsPtee_forprojMee(binsPtee_forMee);
          //cocktTH->SetBinsMee_forprojPtee(binsMee_forPtee);
          //cocktTH->MakeSpectra1D(); // do projections according to attached binning.
          std::cout << "--- Brems Cock ---" << std::endl;
        }

        //if(ic==0 || ic==3-1){
        cockt00->SetBRRelUncertainty(LmCocktailPart::kPion, -0.0298, 0.0298);
        cockt00->SetMTscalingRelUncertainty(LmCocktailPart::kPion, -0.1000, 0.1000);
        cockt00->SetParamRelUncertainty(LmCocktailPart::kPion, -0.0300, 0.0300);
        cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kPion, -0.0200, 0.0800);

        cockt00->SetMTscalingRelUncertainty(LmCocktailPart::kEta, -0.11, 0.11); // 20 +35(ratio)
        cockt00->SetBRRelUncertainty(LmCocktailPart::kEta, -0.058, 0.058);
        cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kEta, -0.0200, 0.0800);
        cockt00->SetParamRelUncertainty(LmCocktailPart::kEta, -0.2, 0.2);

        cockt00->SetMTscalingRelUncertainty(LmCocktailPart::kEtaPrime, -0.2, +0.2);
        cockt00->SetBRRelUncertainty(LmCocktailPart::kEtaPrime, -0.0638, 0.0638);
        //cockt00->SetParamRelUncertainty     (LmCocktailPart::kEtaPrime, -0.1000, 0.1000);
        cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kEtaPrime, -0.0200, 0.0800);

        cockt00->SetMTscalingRelUncertainty(LmCocktailPart::kRho, -0.2, +0.65); //20+65(ratio)
        cockt00->SetBRRelUncertainty(LmCocktailPart::kRho, -0.011, 0.011);
        cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kRho, -0.0200, 0.0800);

        cockt00->SetMTscalingRelUncertainty(LmCocktailPart::kOmega, -0.2, +0.40); //20+42(ratio)
        cockt00->SetBRRelUncertainty(LmCocktailPart::kOmega, -0.0192, 0.0192);
        cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kOmega, -0.0200, 0.0800);

        cockt00->SetMTscalingRelUncertainty(LmCocktailPart::kPhi, -0.3, +0.3);
        cockt00->SetBRRelUncertainty(LmCocktailPart::kPhi, -0.0102, 0.0102);
        //cockt00->SetParamRelUncertainty     (LmCocktailPart::kPhi, -0.1000, 0.1000);
        cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kPhi, -0.0200, 0.0800);

        cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kJPsi, -0.1656, 0.1800); //-16.44+ 16.13%  + -2 +8%reso
        cockt00->SetBRRelUncertainty(LmCocktailPart::kJPsi, -0.0054, 0.0054);

        cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kCharm, -0.1301, 0.1514); // + 2% da norm nicht auf paarebene + 12.7 Cross section + -2 +8 reso
        cockt00->SetBRRelUncertainty(LmCocktailPart::kCharm, -0.24, 0.24);             // 24% BR

        cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kBeauty, -0.3150, 0.3244); // total cross section unc = 0.304 +- 8% scaling +- + -2 +8 reso
        cockt00->SetBRRelUncertainty(LmCocktailPart::kBeauty, -0.07, 0.07);             //

        if (kDoPublished13TeVpythia || kDoPublished13TeVpowheg) {
          cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kCharm, -0.2018, 0.2018);
          cockt00->SetBRRelUncertainty(LmCocktailPart::kCharm, -0.0, 0.0); //
          cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kBeauty, -0.2253, 0.2253);
          cockt00->SetBRRelUncertainty(LmCocktailPart::kBeauty, -0.0, 0.0); //
        }
        cockt00->SetMTscalingRelUncertainty(LmCocktailPart::kLF, -0.2, +0.2);
        cockt00->SetBRRelUncertainty(LmCocktailPart::kLF, -0.0238, 0.0238);
        //cockt00->SetParamRelUncertainty     (LmCocktailPart::kEtaPrime, -0.1000, 0.1000);
        cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kLF, -0.0200, 0.0800);

        //}

        cockt00->SetDoNormBinwidth(kTRUE);
        cockt00->SetDoNormNevents(kTRUE);
        cockt00->SetDoNormCrossSection(kDoNormCrossSection);
        cockt00->SetCrossSection(kCrossSection);
        cockt00->SetLFscaling(kLFscaling);

        cockt00->Process(); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...
                            //LmCocktailParts can only be edited after process
        if (ic > 0) {
          cockt00->GetLmCocktailPart(LmCocktailPart::kSum)->GetSpectrum2D()->SetLineStyle(6 + ic);
          //cockt00->GetLmCocktailPart(LmCocktailPart::kEta) ->GetSpectrum2D()->SetLineStyle(7);
          //cockt00->GetLmCocktailPart(LmCocktailPart::kSum) ->GetSpectrum2D()->SetLineColor(kGray+1);
        }
        //cockt00->GetLmCocktailPart(LmCocktailPart::kJPsi) ->GetSpectrum2D()->SetLineStyle(7);
        //cockt00->GetLmCocktailPart(LmCocktailPart::kJPsi) ->GetSpectrum2D()->SetLineColor(kGray+1);
        //cockt00->GetLmCocktailPart(LmCocktailPart::kJPsi) ->SetName("with #eta from  m_{T} scaling");

        //cockt00->Process(); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...

        // only needed if cocktail shall be projected and plotted stand-alone:
        cockt00->SetBinsPtee_forprojMee(binsPtee_forMee);
        cockt00->SetBinsMee_forprojPtee(binsMee_forPtee);
        cockt00->MakeSpectra1D(); // do projections according to attached binning.
                                  //for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
                                  //  cockt00->PrintCocktail_Mee(i, Form("hCocktailMee_bin%d.pdf", i));
                                  //}
        if (ic == 0) {
          cockt00->PrintUncertainties(0., 0.4, kTRUE);
          //cockt00->PrintUncertainties(0., 0.5, kTRUE);
          cockt00->PrintUncertainties(0.150, .60, kFALSE);
        }
      }

      if (kDoCocktail && !(kDoDrawOnlyFirstCock && ic > 1 - 1)) {
        if (kDoRapp && !kDoAddRapp) hanCompare->AttachCocktail(cocktTH);
        if (kDoRapp && !kDoAddRapp) hanCompare->AttachCocktail(cocktTH2);
        if (kDoBrems && !kDoAddBrems) hanCompare->AttachCocktail(cocktHB);

        hanCompare->AttachCocktail(cockt00); // attach complete cocktail to handler. call cockt00->Process() before!
        //hanCompare->AttachCocktail(cocktLF); // attach complete cocktail to handler. call cockt00->Process() before!
        //hanCompare->AttachCocktail(cocktHF); // attach complete cocktail to handler. call cockt00->Process() before!

        if (kDoBinominal)
          hanCompare->SetDivideOption("b");

        else
          hanCompare->SetDivideOption("0");
        hanCompare->SetDrawStyleCocktail("hist c", ic); // default is "hist
                                                        // if(kDoDrawOnlyFirstCock) hanCompare->SetLegendOnlyFirstCocktail(kTRUE);

        //hanCompare->SetDrawStyleCocktailErr("E2", ic); // default is "hist

        if (kDoCocktailOnly)
          hanCompare->Process(LmHandler::kCocktailOnly); // create projections of cocktail spectra in the projection binning of the handler. they are stored in each LmCocktailPart.
        else if (kDoCocktailSubtraction) {
          hanCompare->Process(LmHandler::kSubtractCocktail); // last cocktail is subtracted from data. projections are done first if needed.
          hanCompare->Process(LmHandler::kCocktail);

        } else if (kDoCocktailSubtraction2D) {
          hanCompare->Process(LmHandler::kSubtractCocktail2D);
          hanCompare->Process(LmHandler::kCompare);
          hanCompare->Process(LmHandler::kCocktail);
        } else if (!kDoCombineSpectra)
          hanCompare->Process(LmHandler::kCocktail); // create projections of cocktail spectra in the projection binning of the handler. they are stored in each LmCocktailPart.
      }

      else {
        if (kDoBinominal)
          hanCompare->SetDivideOption("b");

        else
          hanCompare->SetDivideOption("0");
        hanCompare->Process(LmHandler::kCompare);
      }
      LmHelper::Info(Form("main.cpp: handler '%s' uses divide option '%s'", hanCompare->GetName(), hanCompare->GetDivideOption()));

      if (kDoSaveData) {
        const Char_t* filename = Form("spectra1D_Mee_%i-%i.root", sconfig[ic].LowerCent, sconfig[ic].UpperCent);
        TFile* _fileOut = new TFile(filename, "RECREATE");
        hanCompare->SetSimpleHistnames(kTRUE); // use option kTRUE for short histogram names in rootfile or kFALSE for long, more informative histogram names.
        hanCompare->Write1DHistSingle(LmSignal::kSubSig + LmSignal::kSoverB + LmSignal::kSignif + LmSignal::kUnlike + LmSignal::kBkg, LmSignal::kProjOnMee);
        hanCompare->Write1DHistSingle(LmSignal::kSubSig + LmSignal::kSoverB + LmSignal::kSignif + LmSignal::kUnlike + LmSignal::kBkg, LmSignal::kProjOnPtee);
        if (kDoCocktail) {
          cockt00->WriteHist1D(LmCocktailPart::kSum, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          cockt00->WriteHist1D(LmCocktailPart::kSum, binsMee_forPtee, true, LmBaseSignal::kProjOnPtee);
          cockt00->WriteHist1D(LmCocktailPart::kEta, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          cockt00->WriteHist1D(LmCocktailPart::kEtaPrime, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          cockt00->WriteHist1D(LmCocktailPart::kRho, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          cockt00->WriteHist1D(LmCocktailPart::kOmega, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          cockt00->WriteHist1D(LmCocktailPart::kPhi, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          cockt00->WriteHist1D(LmCocktailPart::kCharm, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          cockt00->WriteHist1D(LmCocktailPart::kBeauty, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          //cockt00->WriteHist1D(LmCocktailPart::kBeauty_binary,   binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          hanCompare->Write2DHist(LmSignal::kSubSig, false, false);
          hanCompare->Write1DHistCocktail(LmBaseSignal::kProjOnPtee);
          hanCompare->Write1DHistCocktail(LmBaseSignal::kProjOnMee);
          hanCompare->Write2DHistCocktail(false);
        }
        _fileOut->Close();
      }

    } // end config loop
    cout << "__________ DONE WITH SINGLE INPUT PROCESSING __________" << endl;
    bench->Show("input_processing");

    Bool_t printLegend = kTRUE;

    if (kDoCombineSpectra && !kDoMergeMultiple) {

      han_combined->Process(LmHandler::kCompare);
      han_combined->Process(LmHandler::kCombine);
      std::cout << "------------------------------------------------------------" << std::endl;
      sig_combined = han_combined->GetLmSigCombined();
      //sig_combined->SetManager(const_cast<LmManager*>(mgrVec.at(0)), kTRUE);
      //sig_combined->SetDoAcceCorr(kDoAcceptanceCorrection);
      if (kDoCocktailSubtraction) sig_combined->Process(LmSignal::kAcceCorrection2D);
      if (kDoFixedSystematics == kTRUE) {
        TFile* h2_unc = TFile::Open("h2_unc_save2.root", "READ");
        h2_unc->cd();
        //    TH2D* own_systematic = (TH2D*)(h2_unc->Get("h2_sys_unc")->Clone("h2_sys_uncertainties"));
        TH2D* own_systematic = (TH2D*)(h2_unc->Get(Form("h2_sys_unc_%i", (int)(1000 * kSetMinPtLabel)))->Clone("h2_sys_uncertainties"));
        sig_combined->SetSymmetricRelSystematics(own_systematic);
        sig_combined->Process(LmSignal::kSystematic);
      }
      hanCompare->AttachSignal(*sig_combined, "Data"); //16

      if (kDoCocktailSubtraction) {
        hanCompare->Process(LmHandler::kCompare);
        hanCompare->Process(LmHandler::kSubtractCocktail); // last cocktail is subtracted from data. projections are done first if needed.
        hanCompare->Process(LmHandler::kCocktail);

      } else if (kDoCocktailSubtraction2D) {
        hanCompare->Process(LmHandler::kSubtractCocktail2D);
        hanCompare->Process(LmHandler::kCompare);
        hanCompare->Process(LmHandler::kCocktail);
      } else {
        hanCompare->Process(LmHandler::kCompare);
        hanCompare->Process(LmHandler::kCocktail);
      }
      if (kDoSaveData) {
        const Char_t* filename = Form("spectra1D_Mee_comb.root");
        TFile* _fileOut = new TFile(filename, "RECREATE");
        hanCompare->SetSimpleHistnames(kTRUE); // use option kTRUE for short histogram names in rootfile or kFALSE for long, more informative histogram names.
        hanCompare->Write1DHistSingle(LmSignal::kSubSig + LmSignal::kSoverB + LmSignal::kSignif + LmSignal::kUnlike + LmSignal::kBkg, LmSignal::kProjOnMee);
        hanCompare->Write1DHistSingle(LmSignal::kSubSig + LmSignal::kSoverB + LmSignal::kSignif + LmSignal::kUnlike + LmSignal::kBkg, LmSignal::kProjOnPtee);
        if (kDoCocktail) {
          hanCompare->GetCocktail(0)->WriteHist1D(LmCocktailPart::kSum, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          hanCompare->GetCocktail(0)->WriteHist1D(LmCocktailPart::kSum, binsMee_forPtee, true, LmBaseSignal::kProjOnPtee);
          //          hanCompare->GetCocktail(0)->WriteHist1D(LmCocktailPart::kEta,      binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          hanCompare->GetCocktail(0)->WriteHist1D(LmCocktailPart::kEtaPrime, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          hanCompare->GetCocktail(0)->WriteHist1D(LmCocktailPart::kRho, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          hanCompare->GetCocktail(0)->WriteHist1D(LmCocktailPart::kOmega, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          hanCompare->GetCocktail(0)->WriteHist1D(LmCocktailPart::kPhi, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          hanCompare->GetCocktail(0)->WriteHist1D(LmCocktailPart::kCharm, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          hanCompare->GetCocktail(0)->WriteHist1D(LmCocktailPart::kBeauty, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          //cockt00->WriteHist1D(LmCocktailPart::kBeauty_binary,   binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
          hanCompare->Write2DHist(LmSignal::kSubSig, false, false);
          hanCompare->Write1DHistCocktail(LmBaseSignal::kProjOnPtee);
          hanCompare->Write1DHistCocktail(LmBaseSignal::kProjOnMee);
          hanCompare->Write2DHistCocktail(false);
        }

        _fileOut->Close();
      }
    }

    //hanCompare->SetPlotRangeYMargins(2., 100.);
    hanCompare->SetPlotRangeYMargins(2., 100.);
    //hanCompare->SetPlotRangeY(5*10E-5, 400);
    hanCompare->SetPlotRangeY(3 * 10E-5, 400);
    if (kDoCocktailSubtraction) hanCompare->SetPlotRangeY(3 * 10E-6, 10);
    //hanCompare->SetPlotRangeY(5*10E-8, 0.04);
    //hanCompare->SetPlotRangeY(5*10E-7, 400);
    //hanCompare->SetPlotRangeY(10E-6, 100);
    //hanCompare->SetPlotRangeY(5*10E-8, 1);
    if (kDoMassSlices == kFALSE) {
      for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i) {
        //if(i==0) hanCompare->SetPlotRangeY(5*10E-6, 10);
        //hanCompare->SetPlotRangeYcompareMee(i);
        // hanCompare->SetPlotRangeY(2e-7,1e0);
        if (kDoNonLogY) {
          if (i == 0) hanCompare->SetPlotRangeY(0.000000001, 0.1);
          //hanCompare->ResetPlotRangeY();
          //if(i==1) hanCompare->SetPlotRangeY(0.0001, 0.45);
          //if(i==1) hanCompare->SetPlotRangeY(0.00001, 4.5);
          //if(i==2) hanCompare->SetPlotRangeY(0.00001, 0.045);
          //if(i==3) hanCompare->SetPlotRangeY(0.00001, 0.0045);
          hanCompare->SetPlotRangeY(0.000000001, 0.1);

          hanCompare->PrintCompare(LmSignal::kSubSig, i, LmBaseSignal::kProjOnMee, "+_ana_cocktail_nonLogy", kTRUE, kFALSE, !kDoNonLogX);

          if (i == 0) hanCompare->SetPlotRangeY(0., 0.1);
          if (i == 1) hanCompare->SetPlotRangeY(0., 0.05);
          if (i == 2) hanCompare->SetPlotRangeY(0., 0.008);
          if (i == 3) hanCompare->SetPlotRangeY(0., 0.005);
          if (i == 4) hanCompare->SetPlotRangeY(0., 0.001);
          if (i == 5) hanCompare->SetPlotRangeY(0., 0.1);

          hanCompare->PrintCompare(LmSignal::kSubSig + LmSignal::kUnlike + LmSignal::kBkg, i, LmBaseSignal::kProjOnMee, "+_nonLogy", kTRUE, kFALSE, !kDoNonLogX);

        } else {
          hanCompare->PrintCompareSig_Mee(i, printLegend);
        }
        hanCompare->PrintCompare(LmSignal::kBkg, i, LmBaseSignal::kProjOnMee);
        //if(kDoCocktail){
        //  cockt00->PrintCocktail_Mee(i,Form("cocktail_mee%i.pdf", i));
        //
        //}
        //hanCompare->SetPlotRangeY(1e-3,1e3);
        if (kDoCocktailOnly) {
          //  cockt00->PrintUncertainties(binsPtee_forMee[i], binsPtee_forMee[i+1], kTRUE);
          hanCompare->PrintCompareSig_Mee(i, printLegend);
          continue;
        }
        hanCompare->SetPlotRangeY(10E-3, 300);
        hanCompare->PrintCompareSoverB_Mee(i, printLegend);
        //hanCompare->SetPlotRangeY(1e-5,1e0);
        hanCompare->SetPlotRangeY(10E-6, 10E-0);
        hanCompare->SetPlotRangeY(0.1, 10E3);
        //hanCompare->SetPlotRangeY(10E-5, 0.1);
        hanCompare->PrintCompareSignif_Mee(i, printLegend);
        if (!kDoNormCrossSection)
          hanCompare->SetPlotRangeY(1e-6, 5);
        else
          hanCompare->SetPlotRangeY(1e-5, 100);
        //  hanCompare->PrintCompareSigBkg_Mee(i, printLegend);
        hanCompare->SetPlotRangeY(0.001, 1);
        if (i == 0) hanCompare->SetPlotRangeY(0.001, 0.0001);
        if (i == 1) hanCompare->SetPlotRangeY(0.001, 0.0001);
        if (i == 2) hanCompare->SetPlotRangeY(0.001, 0.00001);
        if (i == 3) hanCompare->SetPlotRangeY(0.001, 0.00001);
        if (i == 4) hanCompare->SetPlotRangeY(0.0001, 0.000001);
        if (i == 5) hanCompare->SetPlotRangeY(0.0001, 0.000001);
        if (i == 6) hanCompare->SetPlotRangeY(0.06, 0.0);

        hanCompare->PrintCompare(LmSignal::kSubSig + LmSignal::kUnlike + LmSignal::kBkg, i, LmBaseSignal::kProjOnMee);

        //hanCompare->PrintCompareRfactor_Mee(i, printLegend);

        //   hanCompare->PrintCompare(LmSignal::kSoverB, i, LmBaseSignal::kProjOnMee, "", kTRUE, kFALSE);

        //hanCompare->PrintCompare(LmSignal::kSubSig, i, LmSignal::kBkg);
      }
    } else if (kDoMassSlices == kTRUE) {
      for (unsigned int i = 0; i < binsMee_forPtee.size(); ++i) {
        //if(kDoCocktail){
        //  cockt00->PrintCocktail_Ptee(i,Form("cocktail_ptee%i.pdf", i));
        //}

        //   hanCompare->PrintCompare(LmSignal::kUnlike+LmSignal::kBkg, i, LmBaseSignal::kProjOnPtee);
        //   hanCompare->PrintCompare(LmSignal::kSoverB, i, LmBaseSignal::kProjOnPtee, "", kTRUE, kFALSE);
        // hanCompare->SetPlotRangeY(1e-5,10);
        hanCompare->SetPlotRangeY(1e-4, 1000);

        if (kDoNonLogY) {
          if (i == 0) hanCompare->SetPlotRangeY(0.00001, 4.5);
          //        if(i==1) hanCompare->SetPlotRangeY(0.00001, 0.45);
          if (i == 1) hanCompare->SetPlotRangeY(0.00001, 0.45);
          if (i == 2) hanCompare->SetPlotRangeY(0.0001, 0.045);
          if (i == 3) hanCompare->SetPlotRangeY(0.00001, 0.0045);

          hanCompare->PrintCompare(LmSignal::kSubSig, i, LmBaseSignal::kProjOnPtee, "+_ana_cocktail_nonLogy", kTRUE, kFALSE, !kDoNonLogX);
          hanCompare->PrintCompare(LmSignal::kSubSig + LmSignal::kUnlike + LmSignal::kBkg, i, LmBaseSignal::kProjOnPtee, "+_ana_cocktail_nonLogy", kTRUE, kFALSE, !kDoNonLogX);

        } else {
          hanCompare->SetPlotRangeY(0.2 * 10E-4, 0.5);
          //hanCompare->SetPlotRangeY(10E-4, 1.);
          if (kDoCocktailSubtraction) hanCompare->SetPlotRangeY(3 * 10E-6, 10);
          hanCompare->PrintCompareSig_Ptee(i, printLegend);
          hanCompare->SetPlotRangeY(0.9 * 10E-4, 10.5);
          hanCompare->PrintCompare(LmSignal::kSubSig + LmSignal::kUnlike + LmSignal::kBkg, i, LmBaseSignal::kProjOnPtee);
          hanCompare->SetPlotRangeY(0.005, 100.5);
          hanCompare->PrintCompare(LmSignal::kBkg, i, LmBaseSignal::kProjOnPtee);

          hanCompare->SetPlotRangeY(0.0001, 100);
          hanCompare->PrintCompareSoverB_Ptee(i, printLegend);
          //hanCompare->SetPlotRangeY(1e-5,1e0);
          hanCompare->SetPlotRangeY(10E-6, 10E-0);
          hanCompare->SetPlotRangeY(0.1, 10E3);
          //hanCompare->SetPlotRangeY(10E-5, 0.1);
          hanCompare->PrintCompareSignif_Ptee(i, printLegend);
          //hanCompare->PrintCompare(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, i, LmBaseSignal::kProjOnPtee);
          hanCompare->SetPlotRangeY(0.001, 1);
          //hanCompare->PrintCompareRfactor_Ptee(i, printLegend);
        }
        if (kDoCocktailOnly) {
          //  cockt00->PrintUncertainties(binsMee_forPtee[i], binsMee_forPtee[i+1], kFALSE);
          //  continue;
          hanCompare->SetPlotRangeY(0.2 * 10E-4, 0.5);
          hanCompare->PrintCompareSig_Ptee(i, printLegend);
        }
        //   hanCompare->PrintCompareSoverB_Ptee(i, printLegend);
      }
      hanCompare->SetPlotRangeY(0.00001, 140.5);
      hanCompare->PrintCompareAll(LmSignal::kSubSig, 0, 2, LmBaseSignal::kProjOnPtee, "+_comp", kFALSE);
      hanCompare->SetPlotRangeY(0.001, 1);
      hanCompare->PrintCompareRatio(LmSignal::kSubSig, 0, 2, LmBaseSignal::kProjOnPtee, "+_ratio", kFALSE);
    }

    TCanvas c1("c1", "", 800, 800);
    c1.SetLogy();
    c1.SetLogx();
    TH1D h1("h1", ";#pairs;count", 3000, 0.1, 3000.);
    auto bkg = hanCompare->GetLmSignalI(0)->GetLmBackground()->GetBkg2D();
    for (int i = 1; i < bkg->GetNbinsX() - 1; ++i) {
      for (int j = 1; j < bkg->GetNbinsY() - 1; ++j) {
        //      std::cout << "mass: " << bkg->GetXaxis()->GetBinCenter(i) << "   pTee: " << bkg->GetYaxis()->GetBinCenter(j) << "  pairs: " << bkg->GetBinContent(i, j) << std::endl;
        h1.Fill(bkg->GetBinContent(i, j) - 1e-10);
      }
    }
    bkg->Scale(1, "width");
    h1.Draw("hist");
    c1.SaveAs("background_count.pdf");
    c1.SetLogy(true);
    c1.SetLogx(true);
    c1.SetLogz(true);
    bkg->Draw("colz");
    c1.SaveAs("background.pdf");

    hanCompare->ResetPlotRangeY();

    return 0;
  }

  for (int ic = 0; ic < n_config; ic++) {
    // create manager from config string
    LmManager* mgr_i = new LmManager(const_cast<char*>(cconfig[ic].Data())); // TODO: input style to be optimized
    // set all kinds of configuration for the manager
    mgr_i->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
    mgr_i->SetProjOption(projoption);
    mgr_i->SetEnableEffiCorr(kDoEffiCorrection);

    //mgr00->SetEnableRebinning(kFALSE); // use this to disable or just comment out the setter above...
    // configure 3D exclusion cut
    mgr_i->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
    mgr_i->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
    mgr_i->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
    mgr_i->SetTemplateNormRegionMin(n_cutPhiVbelow, cutPhiVbelow); // only needed for some template types.
    mgr_i->SetTemplateNormRegionMax(n_cutPhiVabove, cutPhiVabove); // only needed for some template types.
    if (kDoPhiVCut == LmManager::kTemplSub) mgr_i->SetExclusionZTemplates(hSig, 0x0, LmManager::kTemplSub /*, hSig, hNorm*/);
    //if (kDoPhiV==LmManager::kTemplConv)  mgr->SetExclusionZTemplates(hCon    , 0x0, LmManager::kTemplConv , hSig, hNorm);
    if (kDoPhiVCut == LmManager::kTemplUnsub) mgr_i->SetExclusionZTemplates(hULS, hLS, LmManager::kTemplUnsub, hSig, hNorm);
    mgr_i->SetEnableExclusionCutZ(kDoExclusionCutZ);
    // process the manager

    mgr_i->SetRebinning2D(n_mee_bin, mee_bin.data(), n_ptee_bin, ptee_bin.data());
    mgr_i->SetEtaRange(-0.8, 0.8);
    mgr_i->SetPtRange(kSetMinPtLabel, kSetMaxPtLabel);
    mgr_i->Process();

    LmBackground* bkg_i = new LmBackground(*(mgr_i));
    bkg_i->SetUseRfactor(kTRUE);
    bkg_i->SetRfactorUnityRange(0.5);
    bkg_i->Process(kBkgEstimator);
    //bkg_i->Process(LmBackground::kArith);
    bkgVec.push_back(bkg_i);

    // Need to give phiV-corrected subtracted raw spectra to the manager before LmSignal::Process() is called.
    // Only then the LmManager::SignalPostCorrection(hSub) modifies the subtracted yield before SoverB and Signif are
    // computed from it. The difficulty is that the phiV template fit happens in 1D (projection binning of handler),
    // while the signal is processed in 2D (2D rebinning in (base)manager). Therefore use same binning (ptee_bin_4D)!
    TFile* _fPhiVcorr[48];
    std::vector<TH1D*> vhPhiVcorr;
    if (kDoPhiVCut == LmManager::kTemplSub) {
      for (int i = 0; i < n_ptee_bin; ++i) {
        _fPhiVcorr[i] = LmHelper::SafelyOpenRootfile(Form("./input/PhiV/%iMeV_%i_%i/spectra1D-phiVstudy-ptee%.0fto%.0f_%iMeV.root", (int)(1000 * kSetMinPtLabel), kLowerCent, kUpperCent, ptee_bins[i] * 1000, ptee_bins[i + 1] * 1000, (int)(1000 * kSetMinPtLabel)));
        //_fPhiVcorr[i] = LmHelper::SafelyOpenRootfile(Form("./input/PhiV/%iMeV/spectra1D-phiVstudy-ptee%.0fto%.0f_%iMeV.root",(int)(1000*kSetMinPtLabel),ptee_bins[i]*1000,ptee_bins[i+1]*1000,(int)(1000*kSetMinPtLabel)));
        vhPhiVcorr.push_back((TH1D*)LmHelper::GetHistFromTemplateFile(_fPhiVcorr[i], 0, "hSubSig-mee0.00to3.14", kFALSE));
        vhPhiVcorr.at(i)->SetName(Form("hSubSig-ptee%.0fto%.0f", ptee_slices[i], ptee_slices[i + 1]));
      }
      TH2D* hSubSig_phiVcorr = LmHelper::MakeHist2Dfrom1D(vhPhiVcorr, "hSubSig_phiVcorr", n_ptee_bin, ptee_bins);
      const Char_t* filename3 = "test3.root";
      TFile* _fileOut3 = new TFile(filename3, "RECREATE");
      hSubSig_phiVcorr->Write();
      _fileOut3->Close();

      mgr_i->AddCorrectedSig(hSubSig_phiVcorr, Form("h2_correctedSignal_%i", ic));
      delete hSubSig_phiVcorr;
    }

    mgrVec.push_back(mgr_i);
    mgr_i->SetPlotRangeZ(0., 0.4);
    mgr_i->Print2DEffi();
    mgr_i->Print2DUnlike();

    LmSignal* sig_i = new LmSignal(*(mgrVec.at(ic)), *(bkgVec.at(ic)));
    //sig_i->SetDoSubtraction(kFALSE);
    sig_i->SetDoSignifRaw(kDoSignifRaw);
    sig_i->SetDoNormBinwidth(kDoNormBinwidth);
    sig_i->SetDoNormNevents(kDoNormNevents);
    sig_i->SetCrossSection(kCrossSection);
    sig_i->SetDoNormCrossSection(kDoNormCrossSection);
    sig_i->SetTrgEff(kTriggerEfficiency);
    sig_i->SetDoNormTrgEff(kDoNormTrgEff);
    sig_i->SetDoNormRecEff(kDoNormRecEff);
    sig_i->SetVtxRecEff(kVtxRecEff);
    sig_i->SetDoNormVtxRecEff(kDoNormVtxRecEff);
    sig_i->SetVtxRecEffee(kVtxRecEffee);
    sig_i->SetDoNormVtxRecEffee(kDoNormVtxRecEffee);
    sig_i->Process(LmSignal::kStd);
    sigVec.push_back(sig_i);
  } // end config loop
  cout << "__________ DONE WITH SINGLE INPUT PROCESSING __________" << endl;
  bench->Show("input_processing");

  Int_t Nslices = 0;
  if (kDoMassSlices)
    Nslices = n_mee_slices;
  else
    Nslices = n_ptee_slices;

  LmHandler* hanCompare = new LmHandler(binsPtee_forMee, binsMee_forPtee, plotMeeMin, plotMeeMax, plotPteeMin, plotPteeMax);
  // attach signals to compare handler. they may already be processed or not.
  if (kDoMassSlices) {
    if (Nslices > 0) hanCompare->SetBinningPtee(0, &binsPtee_plotting_0);
    if (Nslices > 1) hanCompare->SetBinningPtee(1, &binsPtee_plotting_0);
    if (Nslices > 2) hanCompare->SetBinningPtee(2, &binsPtee_plotting_1);
    if (Nslices > 3) hanCompare->SetBinningPtee(3, &binsPtee_plotting_2);
    if (Nslices > 4) hanCompare->SetBinningPtee(4, &binsPtee_plotting_3);
    if (Nslices > 5) hanCompare->SetBinningPtee(5, &binsPtee_plotting_5);
  } else {
    if (Nslices > 0) hanCompare->SetBinningMee(0, &binsMee_plotting);
    if (Nslices > 1) hanCompare->SetBinningMee(1, &binsMee_plotting);
    if (Nslices > 2) hanCompare->SetBinningMee(2, &binsMee_plotting);
    if (Nslices > 3) hanCompare->SetBinningMee(3, &binsMee_plotting);
    if (Nslices > 4) hanCompare->SetBinningMee(4, &binsMee_plotting);
    if (Nslices > 5) hanCompare->SetBinningMee(5, &binsMee_plotting);
  }

  //LmHandler* han_systematic = new LmHandler(binsPtee_forMee_sys,binsMee_forPtee_sys,plotMeeMin,plotMeeMax_sys,plotPteeMin,plotPteeMax_sys);
  //han_systematic->SetName("han_systematic");

  std::vector<LmSignal*> sigVec_final;
  std::vector<TString> sigNames_final;
  TString finalSigName = "";
  LmHandler* han_combined = 0x0;
  LmSignal* sig_combined = 0x0;
  if (kDoCombineSpectra) {

    if (kDoMergeMultiple) {

      for (Int_t i = 0; i < sigVec.size() / kMergeNSettings; i++) {
        han_combined = new LmHandler(binsPtee_forMee, binsMee_forPtee, plotMeeMin, plotMeeMax, plotPteeMin, plotPteeMax);
        han_combined->SetName(Form("combined 2016/17 v%s", sigVec.at(kMergeNSettings * i)->GetName()));

        for (Int_t j = 0; j < kMergeNSettings; j++) {
          if ((kMergeNSettings * i + j) < kStartMergeAt || (kMergeNSettings * i + j) >= kStopMergeAt)
            continue;
          han_combined->AttachSignal(*(sigVec.at(kMergeNSettings * i + j)));
        }

        han_combined->Process(LmHandler::kCompare);
        if (i >= (kStartMergeAt * kMergeNSettings) && i < (kStopMergeAt * kMergeNSettings))
          han_combined->Process(LmHandler::kCombine);

        if (!kDoPlotCombineOnly) {
          for (Int_t j = 0; j < kMergeNSettings; j++) {
            if ((kMergeNSettings * i + j) < kStartMergeAt || (kMergeNSettings * i + j) >= kStopMergeAt)
              continue;
            hanCompare->AttachSignal(*(sigVec.at(kMergeNSettings * i + j)));
          }
        }
        sig_combined = han_combined->GetLmSigCombined();

        if (kDoFixedSystematics == kTRUE) {
          TFile* h2_unc = TFile::Open("h2_unc_save2.root", "READ");
          h2_unc->cd();
          //          TH2D* own_systematic = (TH2D*)(h2_unc->Get("h2_sys_unc")->Clone("h2_sys_uncertainties"));
          TH2D* own_systematic = (TH2D*)(h2_unc->Get(Form("h2_sys_unc_%i", (int)(1000 * kSetMinPtLabel)))->Clone("h2_sys_uncertainties"));
          sig_combined->SetSymmetricRelSystematics(own_systematic);
          sig_combined->Process(LmSignal::kSystematic);
        }

        hanCompare->AttachSignal(*sig_combined, Form("combined 2016/17 %c%c<%c%c%c", sigVec.at(2 * i)->GetName()[0], sigVec.at(2 * i)->GetName()[1], sigVec.at(2 * i)->GetName()[2], sigVec.at(2 * i)->GetName()[3], sigVec.at(2 * i)->GetName()[4]));
        //hanCompare->AttachSignal(*sig_combined, sigVec.at(kMergeNSettings*i)->GetName());
      }
    } else {

      han_combined = new LmHandler(binsPtee_forMee, binsMee_forPtee, plotMeeMin, plotMeeMax, plotPteeMin, plotPteeMax);
      han_combined->SetName("Data 16");

      for (unsigned int iSig = 0; iSig < sigVec.size(); iSig++)
        han_combined->AttachSignal(*(sigVec.at(iSig)));
      han_combined->Process(LmHandler::kCompare);
      han_combined->Process(LmHandler::kCombine);

      if (!kDoPlotCombineOnly) {

        if (kDoPlotOnlyFirstIn)
          hanCompare->AttachSignal(*(sigVec.at(0)));
        else {
          for (unsigned int i = 0; i < sigVec.size(); i++)
            hanCompare->AttachSignal(*(sigVec.at(i)));
        }
      }
      sig_combined = han_combined->GetLmSigCombined();

      if (kDoFixedSystematics == kTRUE) {
        TFile* h2_unc = TFile::Open("h2_unc_save2.root", "READ");
        h2_unc->cd();
        //        TH2D* own_systematic = (TH2D*)(h2_unc->Get("h2_sys_unc")->Clone("h2_sys_uncertainties"));
        TH2D* own_systematic = (TH2D*)(h2_unc->Get(Form("h2_sys_unc_%i", (int)(1000 * kSetMinPtLabel)))->Clone("h2_sys_uncertainties"));
        sig_combined->SetSymmetricRelSystematics(own_systematic);
        sig_combined->Process(LmSignal::kSystematic);
      }
      hanCompare->AttachSignal(*sig_combined, "Data");
    }
  } else {
    for (unsigned int i = 0; i < sigVec.size(); i++)
      hanCompare->AttachSignal(*(sigVec.at(i)));
  }

  hanCompare->SetPlotRangeRatio(kRatioLow, kRatioHigh);
  if (!kDoNormCrossSection)
    hanCompare->SetPlotRangeY(1e-6, 5);
  else {
    if (kDoMassSlices)
      hanCompare->SetPlotRangeY(1e-5, 10);
    else
      hanCompare->SetPlotRangeY(1e-5, 100);
  }

  hanCompare->SetDoRatio(kDoRatio, 0.3, kDoRatioLog);
  hanCompare->SetConfidenceLevel(confLevel);
  hanCompare->SetDoConfidenceLevel(kDoConfLevel);
  hanCompare->Process(LmHandler::kCompare);

  LmCocktail* cockt00 = 0x0;
  LmCocktail* cocktLF = 0x0;
  LmCocktail* cocktHF = 0x0;
  LmCocktail* cocktKW = 0x0;
  LmCocktail* cocktTH = 0x0;
  if (kDoCocktail) {

    Printf("______ process cocktail ______");
    LmCocktailMan* cocktmanReso = new LmCocktailMan();
    LmCocktailMan* cocktmanEta = new LmCocktailMan();
    LmCocktailMan* cocktmanKW = new LmCocktailMan();
    if (kDo200MeVCocktail) {
      cocktmanReso->SetInputfiles(const_cast<char*>(cocktail_files[3].Data()));
      cocktmanReso->SetInputfilesAndHistsLow(const_cast<char*>(cocktail_files[4].Data()), const_cast<char*>(cocktail_histograms[0].Data()));  // 2D
      cocktmanReso->SetInputfilesAndHistsHigh(const_cast<char*>(cocktail_files[5].Data()), const_cast<char*>(cocktail_histograms[0].Data())); // 2D
      cocktmanReso->SetInputlists(const_cast<char*>(cocktail_list[0].Data()));
      cocktmanReso->SetInputhistAndDim(const_cast<char*>(cocktail_histograms[0].Data()), 2); // 2D
    } else {
      cocktmanReso->SetInputfiles(const_cast<char*>(cocktail_files[0].Data()));
      cocktmanReso->SetInputfilesAndHistsLow(const_cast<char*>(cocktail_files[1].Data()), const_cast<char*>(cocktail_histograms[0].Data()));  // 2D
      cocktmanReso->SetInputfilesAndHistsHigh(const_cast<char*>(cocktail_files[2].Data()), const_cast<char*>(cocktail_histograms[0].Data())); // 2Di
                                                                                                                                              //      cocktmanReso->SetInputfilesAndHistsLow(const_cast<char*>(cocktail_files[1].Data()), const_cast<char*>(cocktail_histograms[1].Data())); // 2D
                                                                                                                                              //      cocktmanReso->SetInputfilesAndHistsHigh(const_cast<char*>(cocktail_files[2].Data()), const_cast<char*>(cocktail_histograms[1].Data())); // 2Di
      cocktmanReso->SetInputlists(const_cast<char*>(cocktail_list[0].Data()));
      cocktmanReso->SetInputhistAndDim(const_cast<char*>(cocktail_histograms[0].Data()), 2); // 2D
      cocktmanReso->SetArbitraryScaling(kDoResoScaling);
      //cocktmanEta->SetInputfiles(const_cast<char*>(cocktail_files[0].Data()));
      //cocktmanEta->SetInputfilesAndHistsLow(const_cast<char*>(cocktail_files[1].Data()), const_cast<char*>(cocktail_histograms[2].Data())); // 2D
      //cocktmanEta->SetInputfilesAndHistsHigh(const_cast<char*>(cocktail_files[2].Data()), const_cast<char*>(cocktail_histograms[2].Data())); // 2D
      //cocktmanEta->SetInputlists(const_cast<char*>(cocktail_list[0].Data()));
      //cocktmanEta->SetInputhistAndDim(const_cast<char*>(cocktail_histograms[2].Data()), 2); // 2D
      //cocktmanEta->SetHistForNevents("NEvents");
      //cocktmanEta->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
      //cocktmanEta->SetArbitraryScaling(kDoEtaScaling);
      //cocktmanEta->Process(LmCocktailMan::kResonances);
      if (kDoVirtGamma) {
        cocktmanKW->SetInputfiles(const_cast<char*>(cocktail_files[0].Data()));
        cocktmanKW->SetInputfilesAndHistsLow(const_cast<char*>(cocktail_files[1].Data()), "pteevsmee_Virtual_Photon");  // 2D
        cocktmanKW->SetInputfilesAndHistsHigh(const_cast<char*>(cocktail_files[2].Data()), "pteevsmee_Virtual_Photon"); // 2Di
        cocktmanKW->SetInputlists(const_cast<char*>(cocktail_list[0].Data()));
        cocktmanKW->SetInputhistAndDim("pteevsmee_Virtual_Photon", 2); // 2D
        cocktmanKW->SetArbitraryScaling(kDoKWScaling);
        cocktmanKW->SetHistForNevents("NEvents");
        cocktmanKW->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
        cocktmanKW->Process(LmCocktailMan::kVirtGamma);
      }
    }

    cocktmanReso->SetHistForNevents("NEvents");
    cocktmanReso->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
    if (kDoLFsum)
      cocktmanReso->Process(LmCocktailMan::kLFsum);
    else
      cocktmanReso->Process(LmCocktailMan::kResonances);

    std::cout << "--- HEAVY FLAVOUR COCKTAIL ---" << std::endl;
    // for heavy flavours
    LmCocktailMan* cocktmanHF = new LmCocktailMan();
    cocktmanHF->SetNormMidRap(kDoNormMidRap);
    cocktmanHF->SetInputfiles(const_cast<char*>(heavyfl_files[0].Data()));
    cocktmanHF->SetInputlists(const_cast<char*>(heavyfl_list.Data()));
    if (kDo200MeVCocktail)
      cocktmanHF->SetInputhistAndDim(const_cast<char*>(heavyfl_histograms[1].Data()), 2); // 2D
    else
      cocktmanHF->SetInputhistAndDim(const_cast<char*>(heavyfl_histograms[0].Data()), 2); // 2D
    //cocktmanHF->SetRelUncertainties("+0.11:-0.11:+0.23:-0.23");
    cocktmanHF->SetArbitraryScaling(2.0 * kDoHFScaling); // was 2 edit jerome (1.09 Theo) // when using nquarks histogram instead of nevents, by which the yield gets downscaled about 2 times stronger.
    cocktmanHF->SetHistForNeventsHF(const_cast<char*>(heavyfl_hist_Nevents[0].Data()));
    cocktmanHF->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
    cocktmanHF->Process(LmCocktailMan::kHeavyFl);
    // for virtual photons
    // (not available yet)

    //for J/psi
    Printf(" * J/psi");
    LmCocktailMan* cocktmanJpsi = new LmCocktailMan();
    cocktmanJpsi->SetInputfiles(const_cast<char*>(jpsi_files[0].Data()));
    cocktmanJpsi->SetInputhistAndDim(const_cast<char*>(jpsi_histograms[3].Data()), 2);
    cocktmanJpsi->SetInputfilesAndHistsLow(const_cast<char*>(jpsi_files[1].Data()), const_cast<char*>(jpsi_histograms[3].Data()));  // 2D
    cocktmanJpsi->SetInputfilesAndHistsHigh(const_cast<char*>(jpsi_files[2].Data()), const_cast<char*>(jpsi_histograms[3].Data())); // 2D
    if (kDo200MeVCocktail)
      cocktmanJpsi->SetInputlists(const_cast<char*>(jpsi_list[0].Data()));
    cocktmanJpsi->SetInputlists(const_cast<char*>(jpsi_list[1].Data()));

    cocktmanJpsi->SetArbitraryScaling(12.16 / 7.48 * kDoHFScaling /** 1.076*/); //ccbar cross section 13TeV/7TeV
    //cocktmanJpsi->SetRelUncertainties("+0.16:-0.14");
    cocktmanJpsi->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
    cocktmanJpsi->Process(LmCocktailMan::kJpsi);

    LmCocktailMan* cocktmanRapp = new LmCocktailMan();
    if (kDoRapp) {
      cocktmanRapp->SetInputfiles("./input/cocktail_theory/rapp_13TeV_pp_LMR_mee.txt");
      cocktmanRapp->SetInputlists(
        "\
      %lg %*lg %*lg %lg:\
      %lg %*lg %*lg %*lg %*lg %lg:\
      "); // sum
      cocktmanRapp->SetInputhistAndDim("HGmed:QGP", 1);
      cocktmanRapp->SetArbitraryScaling(7 * 57.8);
      //cocktman_Rapp->SetArbitraryScaling(0.797 * 1930 * cocktman_Rapp->GetArbitraryScaling() );
      cocktmanRapp->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail.data(), n_ptee_bin_cocktail, ptee_bin_cocktail.data());
      cocktmanRapp->Process(LmCocktailMan::kRappMee);
    }

    // cocktail (handles the cocktail spectra)
    cockt00 = new LmCocktail(LmCocktail::kpp_MB_13, "Cocktail", kDoNormMidRap);
    cocktLF = new LmCocktail(LmCocktail::kpp_MB_13, "Cocktail", kDoNormMidRap);
    cocktHF = new LmCocktail(LmCocktail::kpp_MB_13, "Cocktail", kDoNormMidRap);
    cocktKW = new LmCocktail(LmCocktail::kpp_MB_13, "CocktailKW", kDoNormMidRap);
    cocktTH = new LmCocktail(LmCocktail::kpp_MB_13, "CocktailTH", kDoNormMidRap);
    if (kDoPublished13TeVpythia) {
      cockt00 = new LmCocktail(LmCocktail::kpp_MB_13pythia, "Cocktail", kDoNormMidRap);
      cocktLF = new LmCocktail(LmCocktail::kpp_MB_13pythia, "Cocktail", kDoNormMidRap);
      cocktHF = new LmCocktail(LmCocktail::kpp_MB_13pythia, "Cocktail", kDoNormMidRap);
      cocktKW = new LmCocktail(LmCocktail::kpp_MB_13pythia, "CocktailKW", kDoNormMidRap);
      cocktTH = new LmCocktail(LmCocktail::kpp_MB_13pythia, "CocktailTH", kDoNormMidRap);
    }
    if (kDoPublished13TeVpowheg) {
      cockt00 = new LmCocktail(LmCocktail::kpp_MB_13powheg, "Cocktail", kDoNormMidRap);
      cocktLF = new LmCocktail(LmCocktail::kpp_MB_13powheg, "Cocktail", kDoNormMidRap);
      cocktHF = new LmCocktail(LmCocktail::kpp_MB_13powheg, "Cocktail", kDoNormMidRap);
      cocktKW = new LmCocktail(LmCocktail::kpp_MB_13powheg, "CocktailKW", kDoNormMidRap);
      cocktTH = new LmCocktail(LmCocktail::kpp_MB_13powheg, "CocktailTH", kDoNormMidRap);
    }
    if (!kDoHFonly) cockt00->AttachManager(*cocktmanReso);
    //cockt00->AttachManager( *cocktmanEta );
    if (!kDoLFonly) cockt00->AttachManager(*cocktmanHF);
    if (!kDoLFonly && !kDoHFonly && kDoJPsi) cockt00->AttachManager(*cocktmanJpsi);
    if (kDoRapp && kDoAddRapp) cockt00->AttachManager(*cocktmanRapp);
    cockt00->SetDrawStyleErr("E2");
    cocktLF->SetDrawStyleErr("E2");
    cocktHF->SetDrawStyleErr("E2");
    cocktTH->SetDrawStyleErr("E2");
    cocktLF->AttachManager(*cocktmanReso);
    cocktHF->AttachManager(*cocktmanHF);
    if (kDoSUMonly)
      cockt00->SetDrawOption(LmCocktail::kOnlySum);
    else if (kDoSUMnot) {
      cockt00->SetDrawOption(LmCocktail::kAllButSum);
      cockt00->SetDrawStyleErr("hist c");
    }

    if (kDoVirtGamma) {
      std::cout << "--- Virtual Gamma Cock ---" << std::endl;
      cocktKW->AttachManager(*cocktmanKW);
      std::cout << "--- Virtual Gamma Cock ---" << std::endl;
      cocktKW->SetDoNormBinwidth(kTRUE);
      cocktKW->SetDoNormNevents(kTRUE);
      cocktKW->SetDoNormCrossSection(kDoNormCrossSectionCocktail);
      cocktKW->SetCrossSection(kCrossSection);
      std::cout << "--- Virtual Gamma Cock ---" << std::endl;
      cocktKW->Process(); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...
      std::cout << "--- Virtual Gamma Cock ---" << std::endl;
      // only needed if cocktail shall be projected and plotted stand-alone:
      cocktKW->SetBinsPtee_forprojMee(binsPtee_forMee);
      cocktKW->SetBinsMee_forprojPtee(binsMee_forPtee);
      cocktKW->MakeSpectra1D(); // do projections according to attached binning.
      std::cout << "--- Virtual Gamma Cock ---" << std::endl;
    }

    if (kDoRapp && !kDoAddRapp) {
      std::cout << "--- Rapp Cock ---" << std::endl;
      cocktTH->AttachManager(*cocktmanKW);
      std::cout << "--- Rapp Cock ---" << std::endl;
      //cocktTH->SetDoNormBinwidth(kTRUE);
      //cocktTH->SetDoNormNevents(kTRUE);
      //cocktTH->SetDoNormCrossSection(kDoNormCrossSectionCocktail);
      //cocktTH->SetCrossSection(kCrossSection);
      std::cout << "--- Rapp Cock ---" << std::endl;
      cocktTH->Process(); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...
      std::cout << "--- Rapp Cock ---" << std::endl;
      // only needed if cocktail shall be projected and plotted stand-alone:
      cocktTH->SetBinsPtee_forprojMee(binsPtee_forMee);
      cocktTH->SetBinsMee_forprojPtee(binsMee_forPtee);
      cocktTH->MakeSpectra1D(); // do projections according to attached binning.
      std::cout << "--- Rapp Cock ---" << std::endl;
    }

    //  cockt00->SetCrosssection_Event(); // cross sections and ncolls should instead be specified in LmCocktail constructor.
    //  cockt00->SetCrosssection_pp();
    //  cockt00->SetNcollCharm();

    //cockt00->SetBRRelUncertainty        (LmCocktailPart::kPion, -0.0298, 0.0298);
    //cockt00->SetMTscalingRelUncertainty(LmCocktailPart::kEta, -0.2, +0.2);
    //cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kEta, -0.1, +0.1);
    //cockt00->SetBRRelUncertainty        (LmCocktailPart::kEta, 0.058, 0.058);
    //cockt00->SetMTscalingRelUncertainty (LmCocktailPart::kEtaPrime, -0.2, +0.2);
    //cockt00->SetBRRelUncertainty        (LmCocktailPart::kEtaPrime, 0.0638, 0.0638);
    //cockt00->SetMTscalingRelUncertainty (LmCocktailPart::kRho, -0.2, +0.2);
    //cockt00->SetBRRelUncertainty        (LmCocktailPart::kRho, 0.011, 0.011);
    //cockt00->SetMTscalingRelUncertainty (LmCocktailPart::kOmega, -0.2, +0.2);
    //cockt00->SetBRRelUncertainty        (LmCocktailPart::kOmega, 0.0192, 0.0192);
    //cockt00->SetMTscalingRelUncertainty (LmCocktailPart::kPhi, -0.3, +0.3);
    //cockt00->SetBRRelUncertainty        (LmCocktailPart::kPhi, 0.0102, 0.0102);

    cockt00->SetBRRelUncertainty(LmCocktailPart::kPion, -0.0298, 0.0298);
    cockt00->SetParamRelUncertainty(LmCocktailPart::kPion, -0.1000, 0.1000);
    cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kPion, -0.0200, 0.0800);

    //    cockt00->SetMTscalingRelUncertainty (LmCocktailPart::kEta, -0.20, 0.40);  // 20 +35(ratio)
    cockt00->SetMTscalingRelUncertainty(LmCocktailPart::kEta, -0.20, 0.20); // 20 +35(ratio)
    cockt00->SetBRRelUncertainty(LmCocktailPart::kEta, -0.058, 0.058);
    cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kEta, -0.0200, 0.0800);
    //cockt00->SetParamRelUncertainty     (LmCocktailPart::kEta, -0.1000, 0.1000);
    //cockt00->SetParamRelUncertainty     (LmCocktailPart::kEta, -0., 2.6666);

    cockt00->SetMTscalingRelUncertainty(LmCocktailPart::kEtaPrime, -0.2, +0.2);
    cockt00->SetBRRelUncertainty(LmCocktailPart::kEtaPrime, -0.0638, 0.0638);
    cockt00->SetParamRelUncertainty(LmCocktailPart::kEtaPrime, -0.1000, 0.1000);
    cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kEtaPrime, -0.0200, 0.0800);

    //    cockt00->SetMTscalingRelUncertainty (LmCocktailPart::kRho, -0.2, +0.68); //20+65(ratio)
    cockt00->SetMTscalingRelUncertainty(LmCocktailPart::kRho, -0.2, +0.20); //20+65(ratio)
    cockt00->SetBRRelUncertainty(LmCocktailPart::kRho, -0.011, 0.011);
    cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kRho, -0.0200, 0.0800);
    //cockt00->SetParamRelUncertainty     (LmCocktailPart::kRho, -0.1000, 0.1000);

    //    cockt00->SetMTscalingRelUncertainty (LmCocktailPart::kOmega, -0.2, +0.46); //20+42(ratio)
    cockt00->SetMTscalingRelUncertainty(LmCocktailPart::kOmega, -0.2, +0.20); //20+42(ratio)
    cockt00->SetBRRelUncertainty(LmCocktailPart::kOmega, -0.0192, 0.0192);
    cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kOmega, -0.0200, 0.0800);
    //cockt00->SetParamRelUncertainty     (LmCocktailPart::kOmega, -0.1000, 0.1000);

    cockt00->SetMTscalingRelUncertainty(LmCocktailPart::kPhi, -0.3, +0.3);
    cockt00->SetBRRelUncertainty(LmCocktailPart::kPhi, -0.0102, 0.0102);
    cockt00->SetParamRelUncertainty(LmCocktailPart::kPhi, -0.1000, 0.1000);
    cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kPhi, -0.0200, 0.0800);

    cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kJPsi, -0.1656, 0.1800); //-16.44+ 16.13%  + -2 +8%reso
    cockt00->SetBRRelUncertainty(LmCocktailPart::kJPsi, -0.0054, 0.0054);
    // cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kCharm, -0.178, 0.178); // Use this when doing total cross section normalization; Measurement with +-7.8%
    cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kCharm, -0.1301, 0.1514); // + 2% da norm nicht auf paarebene + 12.7 Cross section + -2 +8 reso
    // cockt00->SetBRRelUncertainty(LmCocktailPart::kCharm, -0.10, 0.10); // Use this when doing dsigma/dy normalization; Measurement with +-10.2% syst + 8% scaling + 9.3% Ncoll == 15,95
    cockt00->SetBRRelUncertainty(LmCocktailPart::kCharm, -0.24, 0.24);              // 24% BR
    cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kBeauty, -0.3150, 0.3244); // total cross section unc = 0.304 +- 8% scaling +- + -2 +8 reso
    cockt00->SetBRRelUncertainty(LmCocktailPart::kBeauty, -0.07, 0.07);             //

    cockt00->SetDoNormBinwidth(kTRUE);
    cockt00->SetDoNormNevents(kTRUE);
    cockt00->SetDoNormCrossSection(kDoNormCrossSection);
    cockt00->SetCrossSection(kCrossSection);
    cockt00->SetLFscaling(kLFscaling);

    cockt00->Process(); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...

    // only needed if cocktail shall be projected and plotted stand-alone:
    cockt00->SetBinsPtee_forprojMee(binsPtee_forMee);
    cockt00->SetBinsMee_forprojPtee(binsMee_forPtee);
    cockt00->MakeSpectra1D(); // do projections according to attached binning.
    //for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
    //  cockt00->PrintCocktail_Mee(i, Form("hCocktailMee_bin%d.pdf", i));
    //}
    //   cockt00->PrintUncertainties(0., 3.5, kTRUE);
    //   //cockt00->PrintUncertainties(0., 0.5, kTRUE);
    //   cockt00->PrintUncertainties(0., 8.0, kFALSE);

    cocktLF->SetBRRelUncertainty(LmCocktailPart::kPion, -0.0298, 0.0298);
    cocktLF->SetParamRelUncertainty(LmCocktailPart::kPion, -0.1000, 0.1000);
    cocktLF->SetAdditionalRelUncertainty(LmCocktailPart::kPion, -0.0200, 0.0800);

    cocktLF->SetMTscalingRelUncertainty(LmCocktailPart::kEta, -0.20, 0.20); // 20 +35(ratio)
    cocktLF->SetBRRelUncertainty(LmCocktailPart::kEta, -0.058, 0.058);
    cocktLF->SetAdditionalRelUncertainty(LmCocktailPart::kEta, -0.0200, 0.0800);

    cocktLF->SetMTscalingRelUncertainty(LmCocktailPart::kEtaPrime, -0.2, +0.2);
    cocktLF->SetBRRelUncertainty(LmCocktailPart::kEtaPrime, -0.0638, 0.0638);
    cocktLF->SetParamRelUncertainty(LmCocktailPart::kEtaPrime, -0.1000, 0.1000);
    cocktLF->SetAdditionalRelUncertainty(LmCocktailPart::kEtaPrime, -0.0200, 0.0800);

    cocktLF->SetMTscalingRelUncertainty(LmCocktailPart::kRho, -0.2, +0.20); //20+65(ratio)
    cocktLF->SetBRRelUncertainty(LmCocktailPart::kRho, -0.011, 0.011);
    cocktLF->SetAdditionalRelUncertainty(LmCocktailPart::kRho, -0.0200, 0.0800);

    cocktLF->SetMTscalingRelUncertainty(LmCocktailPart::kOmega, -0.2, +0.20); //20+42(ratio)
    cocktLF->SetBRRelUncertainty(LmCocktailPart::kOmega, -0.0192, 0.0192);
    cocktLF->SetAdditionalRelUncertainty(LmCocktailPart::kOmega, -0.0200, 0.0800);

    cocktLF->SetMTscalingRelUncertainty(LmCocktailPart::kPhi, -0.3, +0.3);
    cocktLF->SetBRRelUncertainty(LmCocktailPart::kPhi, -0.0102, 0.0102);
    cocktLF->SetParamRelUncertainty(LmCocktailPart::kPhi, -0.1000, 0.1000);
    cocktLF->SetAdditionalRelUncertainty(LmCocktailPart::kPhi, -0.0200, 0.0800);

    cocktLF->SetAdditionalRelUncertainty(LmCocktailPart::kJPsi, -0.1656, 0.1800); //-16.44+ 16.13%  + -2 +8%reso
    cocktLF->SetBRRelUncertainty(LmCocktailPart::kJPsi, -0.0054, 0.0054);
    cocktLF->SetAdditionalRelUncertainty(LmCocktailPart::kCharm, -0.1301, 0.1514);  // + 2% da norm nicht auf paarebene + 12.7 Cross section + -2 +8 reso
    cocktLF->SetBRRelUncertainty(LmCocktailPart::kCharm, -0.24, 0.24);              // 24% BR
    cocktLF->SetAdditionalRelUncertainty(LmCocktailPart::kBeauty, -0.3150, 0.3244); // total cross section unc = 0.304 +- 8% scaling +- + -2 +8 reso
    cocktLF->SetBRRelUncertainty(LmCocktailPart::kBeauty, -0.07, 0.07);             //

    cocktLF->SetDoNormBinwidth(kTRUE);
    cocktLF->SetDoNormNevents(kTRUE);
    cocktLF->SetDoNormCrossSection(kDoNormCrossSection);
    cocktLF->SetCrossSection(kCrossSection);

    cocktLF->Process(); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...

    // onLF needed if cocktail shall be projected and plotted stand-alone:
    cocktLF->SetBinsPtee_forprojMee(binsPtee_forMee);
    cocktLF->SetBinsMee_forprojPtee(binsMee_forPtee);
    cocktLF->MakeSpectra1D(); // do projections according to attached binning.

    cocktHF->SetBRRelUncertainty(LmCocktailPart::kPion, -0.0298, 0.0298);
    cocktHF->SetParamRelUncertainty(LmCocktailPart::kPion, -0.1000, 0.1000);
    cocktHF->SetAdditionalRelUncertainty(LmCocktailPart::kPion, -0.0200, 0.0800);

    cocktHF->SetMTscalingRelUncertainty(LmCocktailPart::kEta, -0.20, 0.20); // 20 +35(ratio)
    cocktHF->SetBRRelUncertainty(LmCocktailPart::kEta, -0.058, 0.058);
    cocktHF->SetAdditionalRelUncertainty(LmCocktailPart::kEta, -0.0200, 0.0800);

    cocktHF->SetMTscalingRelUncertainty(LmCocktailPart::kEtaPrime, -0.2, +0.2);
    cocktHF->SetBRRelUncertainty(LmCocktailPart::kEtaPrime, -0.0638, 0.0638);
    cocktHF->SetParamRelUncertainty(LmCocktailPart::kEtaPrime, -0.1000, 0.1000);
    cocktHF->SetAdditionalRelUncertainty(LmCocktailPart::kEtaPrime, -0.0200, 0.0800);

    cocktHF->SetMTscalingRelUncertainty(LmCocktailPart::kRho, -0.2, +0.20); //20+65(ratio)
    cocktHF->SetBRRelUncertainty(LmCocktailPart::kRho, -0.011, 0.011);
    cocktHF->SetAdditionalRelUncertainty(LmCocktailPart::kRho, -0.0200, 0.0800);

    cocktHF->SetMTscalingRelUncertainty(LmCocktailPart::kOmega, -0.2, +0.20); //20+42(ratio)
    cocktHF->SetBRRelUncertainty(LmCocktailPart::kOmega, -0.0192, 0.0192);
    cocktHF->SetAdditionalRelUncertainty(LmCocktailPart::kOmega, -0.0200, 0.0800);

    cocktHF->SetMTscalingRelUncertainty(LmCocktailPart::kPhi, -0.3, +0.3);
    cocktHF->SetBRRelUncertainty(LmCocktailPart::kPhi, -0.0102, 0.0102);
    cocktHF->SetParamRelUncertainty(LmCocktailPart::kPhi, -0.1000, 0.1000);
    cocktHF->SetAdditionalRelUncertainty(LmCocktailPart::kPhi, -0.0200, 0.0800);

    cocktHF->SetAdditionalRelUncertainty(LmCocktailPart::kJPsi, -0.1656, 0.1800); //-16.44+ 16.13%  + -2 +8%reso
    cocktHF->SetBRRelUncertainty(LmCocktailPart::kJPsi, -0.0054, 0.0054);
    cocktHF->SetAdditionalRelUncertainty(LmCocktailPart::kCharm, -0.1301, 0.1514);  // + 2% da norm nicht auf paarebene + 12.7 Cross section + -2 +8 reso
    cocktHF->SetBRRelUncertainty(LmCocktailPart::kCharm, -0.24, 0.24);              // 24% BR
    cocktHF->SetAdditionalRelUncertainty(LmCocktailPart::kBeauty, -0.3150, 0.3244); // total cross section unc = 0.304 +- 8% scaling +- + -2 +8 reso
    cocktHF->SetBRRelUncertainty(LmCocktailPart::kBeauty, -0.07, 0.07);             //

    cocktHF->SetDoNormBinwidth(kTRUE);
    cocktHF->SetDoNormNevents(kTRUE);
    cocktHF->SetDoNormCrossSection(kDoNormCrossSectionCocktail);
    cocktHF->SetCrossSection(kCrossSection);

    cocktHF->Process(); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...

    // onHF needed if cocktail shall be projected and plotted stand-alone:
    cocktHF->SetBinsPtee_forprojMee(binsPtee_forMee);
    cocktHF->SetBinsMee_forprojPtee(binsMee_forPtee);
    cocktHF->MakeSpectra1D(); // do projections according to attached binning.
  }

  if (kDoCocktail) {
    if (kDoVirtGamma) hanCompare->SetCocktail(cocktKW);
    if (kDoRapp && !kDoAddRapp) hanCompare->AttachCocktail(cocktTH);
    hanCompare->SetCocktail(cockt00); // attach complete cocktail to handler. call cockt00->Process() before!

    //hanCompare->SetCocktail(cocktLF); // attach complete cocktail to handler. call cockt00->Process() before!
    //hanCompare->SetCocktail(cocktHF); // attach complete cocktail to handler. call cockt00->Process() before!
    if (kDoBinominal)
      hanCompare->SetDivideOption("b");
    else
      hanCompare->SetDivideOption("0");

    hanCompare->SetDrawStyleCocktail("hist c", 0); // default is "hist
    hanCompare->SetDrawStyleCocktail("hist c", 1); // default is "hist
    //hanCompare->SetDrawStyleCocktailErr("hist c E5",1); // default is "hist

    if (kDoCocktailOnly)
      hanCompare->Process(LmHandler::kCocktailOnly); // create projections of cocktail spectra in the projection binning of the handler. they are stored in each LmCocktailPart.
    else if (kDoCocktailSubtraction) {
      hanCompare->Process(LmHandler::kSubtractCocktail); // last cocktail is subtracted from data. projections are done first if needed.
      hanCompare->Process(LmHandler::kCocktail);
    } else
      hanCompare->Process(LmHandler::kCocktail); // create projections of cocktail spectra in the projection binning of the handler. they are stored in each LmCocktailPart.
  }

  else {

    if (kDoBinominal)
      hanCompare->SetDivideOption("b");
    else
      hanCompare->SetDivideOption("0");

    hanCompare->Process(LmHandler::kCompare);
  }
  LmHelper::Info(Form("main.cpp: handler '%s' uses divide option '%s'", hanCompare->GetName(), hanCompare->GetDivideOption()));

  Bool_t printLegend = kTRUE;

  //hanCompare->SetPlotRangeYMargins(2., 100.);
  hanCompare->SetPlotRangeYMargins(2., 100.);
  hanCompare->SetPlotRangeY(5 * 10E-5, 400);
  //hanCompare->SetPlotRangeY(5*10E-8, 0.04);
  //hanCompare->SetPlotRangeY(5*10E-7, 400);
  //hanCompare->SetPlotRangeY(10E-6, 100);
  //hanCompare->SetPlotRangeY(5*10E-8, 1);
  if (kDoMassSlices == kFALSE) {
    for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i) {
      //hanCompare->SetPlotRangeYcompareMee(i);
      // hanCompare->SetPlotRangeY(2e-7,1e0);
      if (kDoNonLogY) {
        if (i == 0) hanCompare->SetPlotRangeY(0.000001, 0.06);
        //if(i==1) hanCompare->SetPlotRangeY(0.00001, 0.45);
        //if(i==1) hanCompare->SetPlotRangeY(0.00001, 4.5);
        //if(i==2) hanCompare->SetPlotRangeY(0.00001, 0.045);
        //if(i==3) hanCompare->SetPlotRangeY(0.00001, 0.0045);

        hanCompare->PrintCompare(LmSignal::kSubSig, i, LmBaseSignal::kProjOnMee, "+_ana_cocktail_nonLogy", kTRUE, kFALSE, !kDoNonLogX);
        hanCompare->PrintCompare(LmSignal::kSubSig + LmSignal::kUnlike + LmSignal::kBkg, i, LmBaseSignal::kProjOnMee, "+_ana_cocktail_nonLogy", kTRUE, kFALSE, !kDoNonLogX);

      } else {
        hanCompare->PrintCompareSig_Mee(i, printLegend);
      }
      hanCompare->PrintCompare(LmSignal::kSubSig + LmSignal::kUnlike + LmSignal::kBkg, i, LmBaseSignal::kProjOnMee);
      if (kDoCocktail) {
        cockt00->PrintCocktail_Mee(i, Form("cocktail_mee%i.pdf", i));
      }
      //hanCompare->SetPlotRangeY(1e-3,1e3);
      if (kDoCocktailOnly) {
        cockt00->PrintUncertainties(binsPtee_forMee[i], binsPtee_forMee[i + 1], kTRUE);
        continue;
      }
      hanCompare->SetPlotRangeY(10E-6, 300);
      hanCompare->PrintCompareSoverB_Mee(i, printLegend);
      //hanCompare->SetPlotRangeY(1e-5,1e0);
      hanCompare->SetPlotRangeY(10E-6, 10E-0);
      hanCompare->SetPlotRangeY(0.1, 10E3);
      //hanCompare->SetPlotRangeY(10E-5, 0.1);
      hanCompare->PrintCompareSignif_Mee(i, printLegend);
      if (!kDoNormCrossSection)
        hanCompare->SetPlotRangeY(1e-6, 5);
      else
        hanCompare->SetPlotRangeY(1e-5, 100);
      //  hanCompare->PrintCompareSigBkg_Mee(i, printLegend);
      //      hanCompare->PrintCompareRfactor_Mee(i, printLegend);

      //   hanCompare->PrintCompare(LmSignal::kSoverB, i, LmBaseSignal::kProjOnMee, "", kTRUE, kFALSE);

      //hanCompare->PrintCompare(LmSignal::kSubSig, i, LmSignal::kBkg);
    }
  }
  if (kDoMassSlices == kTRUE) {
    for (unsigned int i = 0; i < binsMee_forPtee.size(); ++i) {
      if (kDoCocktail) {
        cockt00->PrintCocktail_Ptee(i, Form("cocktail_ptee%i.pdf", i));
      }

      //   hanCompare->PrintCompare(LmSignal::kUnlike+LmSignal::kBkg, i, LmBaseSignal::kProjOnPtee);
      //   hanCompare->PrintCompare(LmSignal::kSoverB, i, LmBaseSignal::kProjOnPtee, "", kTRUE, kFALSE);
      // hanCompare->SetPlotRangeY(1e-5,10);
      hanCompare->SetPlotRangeY(1e-4, 1000);

      if (kDoNonLogY) {
        if (i == 0) hanCompare->SetPlotRangeY(0.00001, 4.5);
        //        if(i==1) hanCompare->SetPlotRangeY(0.00001, 0.45);
        if (i == 1) hanCompare->SetPlotRangeY(0.00001, 0.45);
        if (i == 2) hanCompare->SetPlotRangeY(0.0000001, 0.006);
        if (i == 3) hanCompare->SetPlotRangeY(0.0000001, 0.0005);

        hanCompare->PrintCompare(LmSignal::kSubSig, i, LmBaseSignal::kProjOnPtee, "+_ana_cocktail_nonLogy", kTRUE, kFALSE, !kDoNonLogX);
        if (i == 2) hanCompare->SetPlotRangeY(0.000005, 0.0005);
        hanCompare->PrintCompare(LmSignal::kSubSig + LmSignal::kUnlike + LmSignal::kBkg, i, LmBaseSignal::kProjOnPtee, "+_ana_cocktail_nonLogy", kTRUE, kFALSE, !kDoNonLogX);
        //        hanCompare->PrintCompareRfactor_Ptee(i, printLegend);
      } else {
        hanCompare->PrintCompareSig_Ptee(i, printLegend);
        //	hanCompare->PrintCompareRfactor_Ptee(i, printLegend);
      }
      if (kDoCocktailOnly) {
        cockt00->PrintUncertainties(binsMee_forPtee[i], binsMee_forPtee[i + 1], kFALSE);
        continue;
      }
      //   hanCompare->PrintCompareSoverB_Ptee(i, printLegend);
    }
  }

  TCanvas c1("c1", "", 800, 800);
  c1.SetLogy();
  c1.SetLogx();
  TH1D h1("h1", ";#pairs;count", 3000, 0.1, 3000.);
  auto bkg = hanCompare->GetLmSignalI(0)->GetLmBackground()->GetBkg2D();
  for (int i = 1; i < bkg->GetNbinsX() - 1; ++i) {
    for (int j = 1; j < bkg->GetNbinsY() - 1; ++j) {
      std::cout << "mass: " << bkg->GetXaxis()->GetBinCenter(i) << "   pTee: " << bkg->GetYaxis()->GetBinCenter(j) << "  pairs: " << bkg->GetBinContent(i, j) << std::endl;
      h1.Fill(bkg->GetBinContent(i, j) - 1e-10);
    }
  }
  bkg->Scale(1, "width");
  h1.Draw("hist");
  c1.SaveAs("background_count.pdf");
  c1.SetLogy(true);
  c1.SetLogx(true);
  c1.SetLogz(true);
  bkg->Draw("colz");
  c1.SaveAs("background.pdf");

  hanCompare->ResetPlotRangeY();

  if (DoCorrelationPlots == kTRUE) {
    //|__________|   Plot correlations   |__________|
    Bool_t separatePlots = kTRUE;
    TCanvas c1;
    c1.SetLogx();
    c1.SetLogy();
    //TH2D* haxis = new TH2D("haxis","haxis", 1000,3e-5,3e-2, 1000,1e-1,1e2);
    //  TH2D* haxis = new TH2D("haxis","haxis", 1000,1e-3,1e2, 1000,1e-5,7e-2);
    TH2D* haxis = new TH2D("haxis", "haxis", 1000, 1e-5, 1e2, 1000, 1e-4, 7e0);
    //TH2D* haxis = new TH2D("haxis","haxis", 1000,1e-8,1e8, 1000,1e-8,7e8);
    //TH2D* haxis = new TH2D("haxis","haxis", 1000,1e-6,1e-2, 1000,1e-7,1e-1);
    haxis->DrawCopy();
    hanCompare->SetPlotRangeY(1e-7, 1e-0);
    Int_t projOnAxis = LmBaseSignal::kProjOnX;
    for (int i = 0; i <= hanCompare->GetMaxBinProj(projOnAxis); ++i) {
      hanCompare->PrintCompare(LmSignal::kSubSig, i, projOnAxis); // printing the same projections of SubSig is needed for correct legend colors in correlation plot.
      hanCompare->PrintCorrelation(LmSignal::kSoverB, LmSignal::kSignif, i, projOnAxis, "", printLegend, separatePlots, &c1);
      //hanCompare->SetPlotRangeY(1e-6, 1e-1);
      //hanCompare->SetPlotRangeX(1e-7, 1e-2);
      hanCompare->PrintCorrelation(LmSignal::kBkg, LmSignal::kSubSig, i, projOnAxis, "", printLegend, separatePlots, &c1);
    }
  }

  //if(DoCorrelationPlots == kTRUE){
  //  //|__________|   Plot correlations   |__________|
  //  Bool_t separatePlots=kTRUE;
  //  TCanvas c3; c3.SetLogx(); c3.SetLogy();
  //  TH2D* haxis3 = new TH2D("haxis3","haxis3", 1000,1e-8,1e8, 1000,1e-8,1e-8);
  //  haxis3->DrawCopy();
  //  hanCompare->SetPlotRangeY(1e-7, 1e-0);
  //  Int_t projOnAxis=LmBaseSignal::kProjOnX;
  //  for (int i = 0; i <= hanCompare->GetMaxBinProj(projOnAxis); ++i){
  //    hanCompare->PrintCorrelation(LmSignal::kSubSig, LmSignal::kBkg, i, projOnAxis, "", printLegend, separatePlots, &c3);
  //  }
  //}

  /*
  //|__________|   Plot correlations   |__________|
  /// Note: In order to get plots with only one datapoint per cut setting, the LmSignals have to be processed with
  /// only a single bin in one of the dimensions. This will lead to different results compared to finer binning.
  /// @TODO: this could be avoided by plotting the correlation graphs point by point (to be implemented).
  /// Example:
  /// Double_t mee_bin[] = { 0.14, 1.1, 2.9, 3.3 };
  /// Double_t ptee_bin[] = { 0.0, 4.0 };
  for (unsigned int i = 0; i < binsMee_forPtee.size(); ++i){
    std::vector<TH1D*> vProj1 = hanCompare->CollectProjections(LmSignal::kSoverB, i, LmBaseSignal::kProjOnPtee);
    std::vector<TH1D*> vProj2 = hanCompare->CollectProjections(LmSignal::kSignif, i, LmBaseSignal::kProjOnPtee);
    TObjArray* oaCorrelGr = LmHelper::MakeCorrelationGraphs(vProj1, vProj2);
    TCanvas c1;
    c1.SetLogx();
    c1.SetLogy();
    //TH2D* haxis = new TH2D("haxis","haxis", 1000,1e-5,1e0, 1000,1e-2,1e4);
    //TH2D* haxis = new TH2D("haxis","haxis", 1000,3e-5,3e-2, 1000,1e-1,1e2);
    TH2D* haxis = new TH2D("haxis","haxis", 1000,1e-1,1e0, 1000,1e0,1e2);
    haxis->SetTitle( Form(";%s;%s",vProj1.at(0)->GetYaxis()->GetTitle(),vProj2.at(0)->GetYaxis()->GetTitle()) );
    haxis->DrawCopy();
    oaCorrelGr->DrawClone("pl same");
    c1.BuildLegend(0.15,0.98,0.98,0.7);
    //hanCompare->GetLegend()->DrawClone("same");
    c1.Print( Form("cCorrel_Mee_bin%i.pdf",i) );
    delete haxis;
  }
  */

  //
  // write most important histograms to rootfiles:
  //
  // add bits of histograms you want to store: LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg+LmSignal::kSoverB+LmSignal::kSignif
  // to store all of them, you can also use LmSignal::kMAXhist-1
  //
  if (kDoSaveData) {
    const Char_t* filename = Form("spectra1D_Mee_%i-%i.root", kLowerCent, kUpperCent);
    TFile* _fileOut = new TFile(filename, "RECREATE");
    hanCompare->SetSimpleHistnames(kTRUE); // use option kTRUE for short histogram names in rootfile or kFALSE for long, more informative histogram names.
    hanCompare->Write1DHistSingle(LmSignal::kSubSig + LmSignal::kSoverB + LmSignal::kSignif + LmSignal::kUnlike + LmSignal::kBkg, LmSignal::kProjOnMee);
    if (kDoCocktail) {
      cockt00->WriteHist1D(LmCocktailPart::kSum, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
      cockt00->WriteHist1D(LmCocktailPart::kSum, binsMee_forPtee, true, LmBaseSignal::kProjOnPtee);
      cockt00->WriteHist1D(LmCocktailPart::kEta, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
      cockt00->WriteHist1D(LmCocktailPart::kEtaPrime, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
      cockt00->WriteHist1D(LmCocktailPart::kRho, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
      cockt00->WriteHist1D(LmCocktailPart::kOmega, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
      cockt00->WriteHist1D(LmCocktailPart::kPhi, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
      cockt00->WriteHist1D(LmCocktailPart::kCharm, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
      cockt00->WriteHist1D(LmCocktailPart::kBeauty, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
      //cockt00->WriteHist1D(LmCocktailPart::kBeauty_binary,   binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
      hanCompare->Write2DHist(LmSignal::kSubSig, false, false);
      hanCompare->Write1DHistCocktail(LmBaseSignal::kProjOnPtee);
      hanCompare->Write1DHistCocktail(LmBaseSignal::kProjOnMee);
      hanCompare->Write2DHistCocktail(false);
    }
    //cockt00->WriteHist1D(LmCocktailPart::kEta,      binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
    //cockt00->WriteHist1D(LmCocktailPart::kEtaPrime, binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
    //cockt00->WriteHist1D(LmCocktailPart::kRho,      binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
    //cockt00->WriteHist1D(LmCocktailPart::kOmega,    binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
    //cockt00->WriteHist1D(LmCocktailPart::kPhi,      binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
    //cockt00->WriteHist1D(LmCocktailPart::kCharm,    binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
    //cockt00->WriteHist1D(LmCocktailPart::kBeauty,   binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
    //cockt00->WriteHist1D(LmCocktailPart::kBeauty_binary,   binsPtee_forMee, true, LmBaseSignal::kProjOnMee);
    //  hanCompare->Write2DHist(LmSignal::kSubSig, false, false);
    //  hanCompare->Write1DHistCocktail(LmBaseSignal::kProjOnPtee);
    //  hanCompare->Write1DHistCocktail(LmBaseSignal::kProjOnMee);
    //  hanCompare->Write2DHistCocktail(false);
    //hanCompare->Write2DHist(LmSignal::kPtee, LmSignal::kProjOnMee);
    //hanCompare->Write1DHistSingle(LmSignal::kRfactor, LmSignal::kProjOnMee); // kRfactor only if it is not made of combined signals!
    _fileOut->Close();
  }

  // TFile fOut_theo("./Data_TheoStyle.root","RECREATE");
  // fOut_theo.cd();
  // //TH2D signal    (*(han_combined->GetLmSigCombined()->GetSig2D()));
  // //TH2D signalLow (*(han_combined->GetLmSigCombined()->GetSig2D()));
  // //TH2D signalHigh(*(han_combined->GetLmSigCombined()->GetSig2D()));
  // TH2D signal    (*(sig_combined->GetSig2D()));
  // TH2D signalLow (*(sig_combined->GetSystematicLow()));
  // TH2D signalHigh(*(sig_combined->GetSystematicHigh()));
  // signal    .SetName("signal");
  // signalLow .SetName("systematicLow");
  // signalHigh.SetName("systematicHigh");
  // for(Int_t ix = 0; ix <= signal.GetNbinsX(); ++ix){
  //   for(Int_t iy = 0; iy <= signal.GetNbinsY(); ++iy){
  //     signalLow .SetBinError(ix,iy,signal.GetBinError(ix,iy));
  //     signalHigh.SetBinError(ix,iy,signal.GetBinError(ix,iy));
  //   }
  // }
  // Double_t nEv = han_combined->GetLmSigCombined()->GetNeventsPhysSel();
  // signal    .Scale(1./nEv);
  // signalLow .Scale(1./nEv);
  // signalHigh.Scale(1./nEv);
  //
  // signal    .Write();
  // signalLow .Write();
  // signalHigh.Write();
  // fOut_theo.Close();

  std::cout << "main.cpp done :-)" << std::endl;
}

Double_t TwoGaussiansConnected(Double_t* x, Double_t* par)
{
  Float_t xx = x[0];
  double f = 0;
  if (xx < 0) {
    f = par[0] * TMath::Exp(-0.5 * ((xx - par[1]) / par[2]) * ((xx - par[1]) / par[2]));
  } else if (xx >= 0) {
    f = par[0] * TMath::Exp(-0.5 * ((xx - par[1]) / par[3]) * ((xx - par[1]) / par[3]));
  }
  return f;
}
double DoVirtualPhotonFit(TH1D& h1, TH1D& reso, TH1D& photon, TH1D& charmafterscaling,
                          std::vector<double>& normRegionHigh, unsigned int standardNormRegionHigh,
                          std::vector<double>& fitRegionLow, unsigned int standardFitRegionLow,
                          std::vector<double>& fitRegionHigh, unsigned int standardFitRegionHigh,
                          double& r_error)
{
  LmFitter fitter;
  fitter.SetDatahist(&h1);
  fitter.AttachFitTemplateA(&reso);
  fitter.AttachFitTemplateB(&photon);
  fitter.AttachFitTemplateC(&charmafterscaling);
  fitter.SetTemplateNames("resonances", "Heavy flavour", "Virtual Photon");

  fitter.PrepareFitVirtPhot_Normalization(0., normRegionHigh[standardNormRegionHigh], kTRUE);
  fitter.Process(LmFitter::kThreeTempl_OneNorm_PlusBaseline);

  fitter.PrepareFitVirtPhot_Extraction(fitRegionLow[standardFitRegionLow], fitRegionHigh[standardFitRegionHigh]);
  fitter.Process(LmFitter::kThreeTempl_OneNorm_PlusBaseline);

  double r = fitter.GetBestFitFcn()->GetParameter(0); // inclusive photons
  r_error = fitter.GetBestFitFcn()->GetParError(0);
  return r;
}

void PlotSignalBeforeFit(TH1D& h1, TH1D& reso, TH1D& pion, TH1D& eta, TH1D& LFrest, TH1D& HF, TH1D& photon, unsigned int cut_i, unsigned int pt_i)
{
  TCanvas c1("c1", "", 800, 800);

  TH1D h_sum = *(dynamic_cast<TH1D*>(reso.Clone("sum")));
  h_sum.Add(&HF);
  //
  h1.SetMarkerColor(kBlue);
  h1.SetMarkerStyle(20);
  h1.SetMarkerSize(1.5);
  h1.Draw("p");
  //
  reso.SetMarkerColor(kOrange + 2);
  reso.SetLineWidth(4);
  reso.SetLineColor(kOrange + 2);
  reso.Draw("h same");

  pion.SetMarkerColor(kRed);
  pion.SetLineWidth(1);
  pion.SetLineColor(kRed);
  pion.Draw("h same");

  eta.SetMarkerColor(kBlue);
  eta.SetLineWidth(1);
  eta.SetLineColor(kBlue);
  eta.Draw("h same");

  LFrest.SetMarkerColor(kGreen + 2);
  LFrest.SetLineWidth(1);
  LFrest.SetLineColor(kGreen + 2);
  LFrest.Draw("h same");
  //
  HF.SetMarkerColor(kMagenta);
  HF.SetLineWidth(4);
  HF.SetLineColor(kMagenta);
  HF.Draw("h same");

  h_sum.SetLineColor(kBlack);
  h_sum.SetLineWidth(4);
  h_sum.Draw("h same");

  photon.SetMarkerColor(kGreen + 2);
  photon.SetLineColor(kGreen + 2);
  photon.SetLineWidth(4);
  photon.Draw("h same");

  h1.SetAxisRange(0., 0.7, "X");
  h1.SetAxisRange(1e-6, 50, "Y");
  h1.GetYaxis()->SetTitle("yield");
  //
  TLegend leg1(0.6, 0.7, 0.88, 0.88);
  leg1.AddEntry(&h1, "data", "lpe");
  leg1.AddEntry(&reso, "light flavour before fitting", "lpe");
  leg1.AddEntry(&h_sum, "cocktail sum before fitting", "lpe");
  leg1.AddEntry(&photon, "virtual photon before fitting", "lpe");
  leg1.AddEntry(&HF, "heavy flavour (not refitted)", "lpe");
  leg1.AddEntry((TH1D*)0x0, Form("%.2lf < p_{T,ee} < %.2lf GeV/c", binsPtee_forMee[pt_i], binsPtee_forMee[pt_i + 1]), "");
  leg1.Draw("same");

  h1.DrawCopy(" same");
  c1.SetLogy();
  c1.SaveAs(Form("photon_fit/001_plot_signal/signal_cut%d_mass%d.pdf", cut_i, pt_i));
  return;
}

void DrawRFactors(std::vector<r_Sys>& v_r_Sys, std::string filename)
{
  TCanvas c1("c1", "", 800, 800);
  c1.SetLeftMargin(0.17);
  c1.SetRightMargin(0.05);
  TLine line0(binsPtee_forMee[0], 0., binsPtee_forMee[binsPtee_forMee.size() - 1], 0.);
  line0.SetLineWidth(2);
  v_r_Sys[0].r.SetAxisRange(-0.2, 0.7, "Y");
  v_r_Sys[0].r.DrawCopy("p");
  TLegend leg_r_sys_fit_region(0.19, 0.6, 0.45, 0.88);
  // std::cout << "Number of different r-factors plotted: " << v_r_Sys.size() << std::endl;;
  for (unsigned int i = 0; i < v_r_Sys.size(); ++i) {
    v_r_Sys[i].r.SetMarkerStyle(20);
    v_r_Sys[i].r.SetMarkerSize(1.5);
    v_r_Sys[i].r.SetMarkerColor(LmHelper::GetUniformColor(i, v_r_Sys.size()));
    v_r_Sys[i].r.SetLineColor(LmHelper::GetUniformColor(i, v_r_Sys.size()));
    v_r_Sys[i].r.DrawCopy("p same E1");
    leg_r_sys_fit_region.AddEntry(&(v_r_Sys[i].r), v_r_Sys[i].caption.c_str(), "lpe");
  }
  line0.Draw("same");
  leg_r_sys_fit_region.Draw("same");
  c1.SaveAs(filename.c_str());
}

void PrintChiSquare(std::vector<r_Sys>& vec)
{

  TH1D h1_mean = *(dynamic_cast<TH1D*>(vec[0].r.Clone("mean")));

  for (int bin_i = 1; bin_i < vec[0].r.GetNbinsX() + 1; ++bin_i) {
    double sum = 0;
    for (unsigned int i = 0; i < vec.size(); ++i) {
      sum = sum + vec[i].r.GetBinContent(bin_i);
    }
    double mean = sum / (double)vec.size();
    std::cout << "mean bin " << bin_i << ": " << mean << std::endl;
    h1_mean.SetBinContent(bin_i, mean);
  }

  for (unsigned int i = 0; i < vec.size(); ++i) {
    Double_t chi2ndf = vec[i].r.Chi2Test(&h1_mean, "UU NORM CHI2/NDF");
    // Double_t chi2ndf = vec[i].r.Chi2Test(&h1_mean, "NORM UU CHI2/NDF");
    std::cout << "cut " << i << " with chi2/ndf = " << chi2ndf << std::endl;
  }
}

double GetRMSofBin(std::vector<r_Sys>& vec, int bin)
{
  // calculates RMS as sqrt(1/N * sum((x_i - mean)^2))
  double sum = 0;
  for (unsigned int i = 0; i < vec.size(); ++i) {
    sum = sum + vec[i].r.GetBinContent(bin + 1);
  }
  double mean = sum / (double)vec.size();

  double rms_sum = 0;
  for (unsigned int i = 0; i < vec.size(); ++i) {
    rms_sum = rms_sum + (vec[i].r.GetBinContent(bin + 1) - mean) * (vec[i].r.GetBinContent(bin + 1) - mean);
  }
  double rms = TMath::Sqrt(rms_sum / (double)vec.size());

  return rms;
}

Double_t HFfunction(Double_t* x, Double_t* par)
{
  Int_t xbin = hc->GetXaxis()->FindBin(x[0]);
  Int_t ybin = hc->GetYaxis()->FindBin(x[1]);

  Double_t val = par[0] * hc->GetBinContent(xbin, ybin) + par[1] * hb->GetBinContent(xbin, ybin) + hRes->GetBinContent(xbin, ybin);
  return val;
}

void SutractHisto(TH2D& h1, TH2D& h2)
{

  for (Int_t ix = 1; ix <= h1.GetNbinsX(); ++ix) {
    for (Int_t iy = 1; iy <= h1.GetNbinsY(); ++iy) {
      h1.SetBinContent(ix, iy, h1.GetBinContent(ix, iy) - h2.GetBinContent(ix, iy));
    }
  }
}

void Rebin2D(TH2D& h, TH2D& hRefBinning)
{
  Int_t n_mee_bin = hRefBinning.GetNbinsX();
  Double_t mee_bin[n_mee_bin + 1];
  for (Int_t i = 0; i <= n_mee_bin; ++i)
    mee_bin[i] = hRefBinning.GetXaxis()->GetBinUpEdge(i);
  Int_t n_ptee_bin = hRefBinning.GetNbinsY();
  Double_t ptee_bin[n_ptee_bin + 1];
  for (Int_t i = 0; i <= n_ptee_bin; ++i)
    ptee_bin[i] = hRefBinning.GetYaxis()->GetBinUpEdge(i);

  TH2D hrb(Form("%s_rb", h.GetName()), "", n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
  hrb.Sumw2();
  for (Int_t ix = 1; ix <= h.GetNbinsX(); ix++) {
    for (Int_t iy = 1; iy <= h.GetNbinsY(); iy++) {
      Double_t w(0.);
      w = h.GetBinContent(ix, iy);
      hrb.Fill(h.GetXaxis()->GetBinCenter(ix),
               h.GetYaxis()->GetBinCenter(iy), w);
    }
  }
  h = hrb;
}

TPaveText GetTextBox(Double_t x1, Double_t y1, Double_t x2, Double_t y2)
{
  TPaveText T(x1, y1, x2, y2, "brNDC");
  T.SetBorderSize(0);
  T.SetTextSize(0.017);
  T.SetFillColor(0);
  T.SetFillStyle(0);
  T.SetLineColor(kWhite);
  T.SetTextAlign(12);

  return T;
}

void SetHistoProp(TH1D* h, Int_t color, Int_t mStyle, Int_t lStyle)
{
  h->SetMarkerStyle(mStyle);
  h->SetLineStyle(lStyle);
  h->SetLineColor(color);
  h->SetMarkerColor(color);
}
void Add5proc(TH2D& hup, TH2D& h)
{

  Int_t n_mee_bin = h.GetNbinsX();
  Int_t n_ptee_bin = h.GetNbinsY();

  Double_t proc = 0.05; // Add 5 % sys

  for (Int_t ix = 1; ix <= h.GetNbinsX(); ix++) {
    for (Int_t iy = 1; iy <= h.GetNbinsY(); iy++) {

      Double_t signal = h.GetBinContent(ix, iy);
      Double_t signalup = hup.GetBinContent(ix, iy);

      Double_t sysup = TMath::Abs(signal - signalup);
      Double_t sysupnew = TMath::Sqrt(sysup * sysup + proc * proc * signal * signal);

      Double_t signalnew = 0.;
      if (signalup > signal)
        signalnew = signal + sysupnew;
      else
        signalnew = signal - sysupnew;

      hup.SetBinContent(ix, iy, signalnew);
    }
  }
  return;
}

TH2D* RebinBis(TH2D& h)
{

  Double_t mee_bin[] = {0.00, 0.04, 0.09, 0.14, 0.19, 0.24, 0.29, 0.34, 0.39, 0.44, 0.50, 0.60, 0.70, 0.75, 0.80, 0.95, 1.00, 1.05, 1.10, 1.40, 1.70, 2.00, 2.40, 2.70, 3.00, 3.10, 3.30, 3.50, 4.00};
  Double_t ptee_bin[] = {0.00, 0.40, 0.80, 1.20, 1.60, 2.00, 2.40, 2.80, 4.00, 5.50, 8.00, 10.0};

  Int_t n_mee_bin = sizeof(mee_bin) / sizeof(*mee_bin) - 1;
  Int_t n_ptee_bin = sizeof(ptee_bin) / sizeof(*ptee_bin) - 1;

  TH2D* hOut = new TH2D(Form("hOut_%s", h.GetName()), h.GetTitle(), n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
  hOut->Sumw2(); // also done by SetBinError();

  hOut->GetXaxis()->SetTitle(h.GetXaxis()->GetTitle());
  hOut->GetYaxis()->SetTitle(h.GetYaxis()->GetTitle());
  hOut->GetZaxis()->SetTitle(h.GetZaxis()->GetTitle());
  Double_t bin_content_hIn = 0;
  Double_t bin_error_hIn = 0;
  Double_t bin_center_mee = -1;
  Double_t bin_center_ptee = -1;
  Int_t hOut_previous_bin = -1;
  Int_t hOut_current_bin = -1;
  Double_t hOut_bin_err2 = 0;

  for (Int_t i_mee = 1; i_mee <= h.GetNbinsX(); ++i_mee) { //Overflow? -> would probably mess up error calculation.
    for (Int_t j_ptee = 1; j_ptee <= h.GetNbinsY(); ++j_ptee) {
      bin_content_hIn = h.GetBinContent(i_mee, j_ptee);
      bin_error_hIn = h.GetBinError(i_mee, j_ptee);
      bin_center_mee = h.GetXaxis()->GetBinCenter(i_mee);
      //printf(Form(" Bin center mee of bin %i = %f", i_mee, bin_center_mee));
      bin_center_ptee = h.GetYaxis()->GetBinCenter(j_ptee);

      // set hOut content
      // Fill(): The function returns the corresponding global bin number which has its content incremented by w
      hOut_current_bin = hOut->Fill(bin_center_mee, bin_center_ptee, bin_content_hIn);

      // set hOut error
      if (hOut_current_bin != hOut_previous_bin) { // new bin in hOut
        // set error of previous bin which is now finished
        if (hOut_previous_bin > -1) hOut->SetBinError(hOut_previous_bin, TMath::Sqrt(hOut_bin_err2)); // compute and set absolute bin error.
        // prepare error for current bin
        hOut_bin_err2 = bin_error_hIn * bin_error_hIn; // compute first squared error.
        hOut_previous_bin = hOut_current_bin;
      } else {
        // update error of current bin
        hOut_bin_err2 += bin_error_hIn * bin_error_hIn; // update squared error.
      }
    }
  }
  // set error of the very last bin, because it cannot be reached in the loop via (hOut_current_bin != hOut_previous_bin):
  hOut->SetBinError(hOut_previous_bin, TMath::Sqrt(hOut_bin_err2)); // compute and set absolute bin error.

  return hOut;
}
