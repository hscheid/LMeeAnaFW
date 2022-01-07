#include <iostream>

#include "../core/LmQA.h"
#include "TLegend.h"
#include "carsten_sys.h"
#include "TSystem.h"
#include "TMinuit.h"
#include "TVirtualFitter.h"
#include "TGraph.h"
#include "TPaveText.h"
#include "../core/LmFitter.h"

void Init();
void Analyse();
int QA();
int QA2();
int PhiVstudy();
int Photon();
int HF_Fit();
int ExtractPhiVtemplates();

int main(int argc, char* argv[]){
  gErrorIgnoreLevel = kWarning;
  gStyle->SetNumberContours(255);
  if (argc == 2){
    if (std::string(argv[1]) == "QA"){
      QA();
    }
    else if (std::string(argv[1]) == "Analysis"){
      Init();
      Analyse();
    }
    else if (std::string(argv[1]) == "PhiV"){
      Init();
      PhiVstudy();
    }
    else if (std::string(argv[1]) == "Photon"){
      Init();
      Photon();
    }
    else if (std::string(argv[1]) == "HF_Fit"){
      Init();
      HF_Fit();
    }
    else if (std::string(argv[1]) == "PhiV_Templates"){
      Init();
      ExtractPhiVtemplates();
    }
  }
  else{
    std::cout << "Specify 'QA' or 'Analysis'" << std::endl;
  }

  return 0;
}


void Init()
{
  gErrorIgnoreLevel = kWarning;
  LmHelper lmHelper;
  LmHelper::SetCanvasHeight(800);
  LmHelper::SetCanvasWidth(800);
  LmHistogram::SetDrawOptionsStatic("p E same;p E2 same;p E[] same");

  // manual settings
  printLegend  = kTRUE;
  plotAverage  = kFALSE;
  plotWeightAv = kFALSE;

  // plotting
  plotMeeMin  = 0.; plotMeeMax  = 3.99;   plotMeeMax_sys  = 3.3; //mee_bin_systematic[n_mee_bin_systematic];
  // plotMeeMin  = 0.; plotMeeMax  = 1.1;   plotMeeMax_sys  = 3.3; //mee_bin_systematic[n_mee_bin_systematic];
  plotPteeMin = 0.; plotPteeMax = 8.000; plotPteeMax_sys = ptee_bin_systematic[n_ptee_bin_systematic];
  // plotPteeMin = 0.; plotPteeMax = 4.000; plotPteeMax_sys = ptee_bin_systematic[n_ptee_bin_systematic];
  LmBaseSignal::SetInputLabelZ("#it{#phi}_{V}","rad", "PhiV");
  // LmBaseSignal::SetLabelSig("#it{N}_{S}");
  // LmBaseSignal::SetLabelBkg("#it{N}_{B}");
  // binning
  binsMee_forPtee_sys.push_back(0.);
  binsMee_forPtee_sys.push_back(0.14);
  binsMee_forPtee_sys.push_back(5.);

  binsPtee_forMee_sys.push_back(0.);
  binsPtee_forMee_sys.push_back(8.);



  // binsPtee_forMee.push_back(0.);
  // binsPtee_forMee.push_back(1.);
  // binsPtee_forMee.push_back(2.);
  // binsPtee_forMee.push_back(3.);
  // binsPtee_forMee.push_back(6.);
  // binsPtee_forMee.push_back(8.);

  binsPtee_forMee.push_back(0.);
  binsPtee_forMee.push_back(1.);
  binsPtee_forMee.push_back(2.);
  binsPtee_forMee.push_back(3.);
  binsPtee_forMee.push_back(5.);
  binsPtee_forMee.push_back(8.);
  // binsPtee_forMee.push_back(4.);

  // binsPtee_forMee.push_back(0.);
  // binsPtee_forMee.push_back(1.);
  // binsPtee_forMee.push_back(2.);
  // binsPtee_forMee.push_back(3.);
  // binsPtee_forMee.push_back(4.);

  binsMee_forPtee.push_back(0.);
  // binsMee_forPtee.push_back(0.08);
  binsMee_forPtee.push_back(0.14);
  // binsMee_forPtee.push_back(0.22);
  binsMee_forPtee.push_back(0.38);
  binsMee_forPtee.push_back(0.7);
  binsMee_forPtee.push_back(1.1);
  binsMee_forPtee.push_back(2.7);
  binsMee_forPtee.push_back(3.3);
  binsMee_forPtee.push_back(5.0);


  binsMee_forPhiV.push_back(0.);
  //  binsMee_forPhiV.push_back(0.01); // test
  binsMee_forPhiV.push_back(0.02);
  //  binsMee_forPhiV.push_back(0.03); // test
  binsMee_forPhiV.push_back(0.04);
  // binsMee_forPhiV.push_back(0.06);
  binsMee_forPhiV.push_back(0.08);
  // binsMee_forPhiV.push_back(0.10);
  // binsMee_forPhiV.push_back(0.14);
  // binsMee_forPhiV.push_back(0.22);


  binsPhiV.push_back(0.);
  binsPhiV.push_back(TMath::Pi());


  // n_mee_bin  = sizeof(mee_bin)/sizeof(*mee_bin) -1;
  // n_ptee_bin = sizeof(ptee_bin)/sizeof(*ptee_bin) -1;

  if (kDo200MeV == kTRUE && kCentrality == kCent::kCent0080){
    LmHelper::Info("Binning for pt>200 MeV/c and 00-80% Centrality set");
    mee_bin = mee_bin;
    // mee_bin = mee_bin0020;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent0010){
    LmHelper::Info("Binning for pt>200 MeV/c and 00-10% Centrality set");
    mee_bin = mee_bin0010;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent1050){
    LmHelper::Info("Binning for pt>200 MeV/c and 10-50% Centrality set");
    mee_bin = mee_bin1050;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent5080){
    LmHelper::Info("Binning for pt>200 MeV/c and 50-80% Centrality set");
    mee_bin = mee_bin5080;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent0020){
    LmHelper::Info("Binning for pt>200 MeV/c and 00-20% Centrality set");
    mee_bin = mee_bin0020;
    // mee_bin = mee_bin;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent2040){
    LmHelper::Info("Binning for pt>200 MeV/c and 20-40% Centrality set");
    mee_bin = mee_bin;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent4080){
    LmHelper::Info("Binning for pt>200 MeV/c and 40-80% Centrality set");
    // mee_bin = mee_bin4080;
    mee_bin = mee_bin;
  }
  else {
    LmHelper::Info("Binning for pt>200 MeV/c and any centrality");
    mee_bin = mee_bin;
  }
}

void Analyse(){

  // kCent0080, kCent0010, kCent1050, kCent5080
  if      (kCentrality == kCent0080) sOptCent = "0080";
  else if (kCentrality == kCent0010) sOptCent = "0010";
  else if (kCentrality == kCent1050) sOptCent = "1050";
  else if (kCentrality == kCent5080) sOptCent = "5080";
  else if (kCentrality == kCent0020) sOptCent = "0020";
  else if (kCentrality == kCent2040) sOptCent = "2040";
  else if (kCentrality == kCent4080) sOptCent = "4080";
  else if (kCentrality == kCent1020) sOptCent = "1020";
  else if (kCentrality == kCent4050) sOptCent = "4050";
  else if (kCentrality == kCent5060) sOptCent = "5060";
  else if (kCentrality == kCent6080) sOptCent = "6080";

  if (kDo200MeV == kTRUE) sOptPt = "pt200";
  else                    sOptPt = "pt400";

  filename2D_sys = Form("spectra2D_sys_%s_%s_%s_%s.root",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data());
  filename2D_ana = Form("spectra2D_ana_%s_%s_%s_%s.root",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data());
  extpath_sys    = TString("./input/data_2Dsignals/"+filename2D_sys);
  extpath_ana    = TString("./input/data_2Dsignals/"+filename2D_ana);


  std::cout << " ______ CONFIGURATION ______ " << std::endl;
  std::cout << " centrality   =   " << sOptCent.Data() << std::endl;
  std::cout << " pt-cut       =   " << sOptPt.Data() << std::endl;
  std::cout << " prefilter    =   " << sOptPref.Data() << std::endl;
  std::cout << " efficiency   =   " << sOptEff.Data() << std::endl;
  std::cout << " plotAverage  =   " << (plotAverage?"YES":"NO") << std::endl;
  std::cout << " plotWeightAv =   " << (plotWeightAv?"YES":"NO") << std::endl;
  std::cout << std::endl;


  LmHandler* han_systematic = new LmHandler(binsPtee_forMee_sys,binsMee_forPtee_sys,plotMeeMin,plotMeeMax_sys,plotPteeMin,plotPteeMax_sys);
  han_systematic->SetName("han_systematic");
  LmHandler* han_analysis = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  han_analysis->SetName("han_analysis");


  if (kDoReadFromRootFile){
    // check if pre-processed files exist
    if (   (gSystem->Exec( Form("ls %s > /dev/null",extpath_sys.Data()) )==0) // file is available if Exec()==0
        && (gSystem->Exec( Form("ls %s > /dev/null",extpath_ana.Data()) )==0) )
    {
      std::cout << "InitFromRootfile()" << std::endl;
      han_systematic->InitFromRootfile(extpath_sys.Data());
      han_analysis->InitFromRootfile(extpath_ana.Data());
    }
  }
  else {
    std::cout << "Read input files" << std::endl;
    ProcessInputfiles(han_systematic, han_analysis);
  }


  std::cout << "Postprocess input handlers" << std::endl;
  // postprocess analysis binning
  std::cout << "Configure Analysis Handler" << std::endl;
  han_analysis->Process(LmHandler::kCompare); // make projections of all spectra
  han_analysis->SetPlotRangeRatio(0.2, 4.2);
  han_analysis->SetDoRatio(kDoRatio, 0.3, kFALSE);
  han_analysis->SetFileType("png");

  std::cout << "Configure Systematic Handler" << std::endl;
  han_systematic->Process(LmHandler::kCompare); // make projections of all spectra
  han_systematic->SetCompareSignalsToAverage();
  han_systematic->SetBinningMee(0,&mee_bin_systematic_coarse);
  han_systematic->SetBinningPtee(0,&ptee_bin_systematic_coarse);
  han_systematic->Process(LmHandler::kCompare); // make projections of all spectra
  han_systematic->SetFileType("pdf");

  double legendSize = 1.2;
  double markerSize = 1.5;

  han_analysis->SetLabels(GetLabelsTemplate(kPerformance)); // size of legend is in carsten_sys.h
  han_analysis->SetRatioTitle("ratio to first input");
  han_analysis->SetRatioTitleSize(0.8);
  han_analysis->SetRatioTitleOffset(1.1);
  han_analysis->SetMarkerSize(markerSize);
  han_analysis->SetLegendSize(legendSize);
  han_analysis->SetLegendOffsetY(-0.015);
  han_analysis->SetLegendOffsetX(-0.025);
  han_analysis->SetLegendEntryDrawOption("p");
  han_analysis->SetUseDifferentMarkers(true);

  for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj){
    // han_analysis->SetPlotRangeY(5e-6, 5);
    han_analysis->PrintCompareSig_Mee   (iProj, printLegend, Form("+_ana_%s_%s",sOptCent.Data(),sOptPt.Data()), 2, 20);
    //
    // han_analysis->SetPlotRangeY(5e-6, 500);
    // han_analysis->PrintCompare(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, iProj, LmBaseSignal::kProjOnMee, Form("+_Signal_ULS_LS_%s_%s",sOptCent.Data(),sOptPt.Data()), true, true);
    //
    han_analysis->PrintCompareSoverB_Mee(iProj, printLegend, Form("+_ana_%s_%s",sOptCent.Data(),sOptPt.Data()), 2, 20);
    han_analysis->PrintCompareSignif_Mee(iProj, printLegend, Form("+_ana_%s_%s",sOptCent.Data(),sOptPt.Data()), 2, 20);
    // han_analysis->PrintCompareRfactor_Mee(iProj, printLegend, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 0.9, 1.1);
    // han_analysis->PrintCompare(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, iProj, LmBaseSignal::kProjOnMee, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), true, true);
    // han_analysis->PrintCompare(LmSignal::kUnlike+LmSignal::kBkg, iProj, LmBaseSignal::kProjOnMee, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), true, true);
    // han_analysis->PrintCorrelation(LmSignal::kSignif, LmSignal::kSoverB, iProj, LmBaseSignal::kProjOnMee, Form("xbin%d_ybin%d"), optional Bool_t printLegend, optional Bool_t separatePlots, optional TCanvas *can)

    // han_systematic->SetPlotRangeY(1e-4, 10);
    // han_systematic->PrintCompareSig_Mee(iProj, printLegend, Form("+_sys_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 2, 20);
  }
  for(UInt_t iProj = 0; iProj < binsMee_forPtee.size(); ++iProj){
    // han_analysis->PrintCompareSig_Ptee(iProj, printLegend, Form("+_ana_%s_%s",sOptCent.Data(),sOptPt.Data()), 2, 20);
  }

  // #############################################################
  // Save signals to ROOT Files
  // TFile* file_signal_all = TFile::Open("signal_all.root", "RECREATE");
  // han_analysis->SetRootfile(file_signal_all);
  // han_analysis->Write2DHist(LmSignal::kSubSig, false, true);
  // han_analysis->Write2DHist(LmSignal::kUnlikeMix, false, true);
  // han_analysis->Write1DHistSingle(LmSignal::kSubSig, true, true);
  // han_analysis->Write1DHistSingle(LmSignal::kUnlikeMix, true, true);
  // file_signal_all->Close();
  // delete file_signal_all;


  // #############################################################
  // Create new handler with one chosen signal and the systematics
  std::cout << "Creating new Handler with chosen signal and systematics" << std::endl;
  LmHandler* handler_to_combine_signals = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  std::vector<LmSignal*> vec_signals;

  if (kDo200MeV == kTRUE && kCentrality == kCent::kCent0080) {
    vec_signals.push_back(han_analysis->GetLmSignalI(0));
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent0020) {vec_signals.push_back(han_analysis->GetLmSignalI(0)); }//
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent2040) {vec_signals.push_back(han_analysis->GetLmSignalI(0)); }//
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent4080) {vec_signals.push_back(han_analysis->GetLmSignalI(0)); }//
  else {
    vec_signals.push_back(han_analysis->GetLmSignalI(0));
  }
  for (unsigned int i = 0; i < vec_signals.size(); ++i){
    handler_to_combine_signals->AttachSignal( *(vec_signals[i]), Form("data"));
  }
  handler_to_combine_signals->Process(LmHandler::kCombine);


  handler_to_combine_signals->SetPlotRangeY(6e-6, 2e2);


  if (kDoCombineHandler){

    // TCanvas c1("c1", "c1", 1200, 1200);
    TFile* h2_unc = TFile::Open("h2_unc.root", "RECREATE");
    h2_unc->cd();
    TH2D* sys_unc = dynamic_cast<TH2D*>(han_systematic->GetRelSystematics()->Clone("h2_sys_unc"));
    sys_unc->Write();
    // h2_unc->Close();
    std::cout << "Systematic: " << sys_unc->GetBinContent(1,1) << std::endl;
    std::cout << "Systematic: " << sys_unc->GetBinContent(2,1) << std::endl;
    std::cout << "Systematic: " << sys_unc->GetBinContent(3,1) << std::endl;
    std::cout << "Systematic: " << sys_unc->GetBinContent(4,1) << std::endl;
    std::cout << "Systematic: " << sys_unc->GetBinContent(5,1) << std::endl;
    // c1.SetRightMargin(0.2);
    // sys_unc->DrawCopy("colz text");
    // c1.SaveAs("SysUnc.png");
  }

    LmSignal* sig_combined = handler_to_combine_signals->GetLmSigCombined();

    if (kDoSystematics) {
      if (kDoOwnSystematics == kTRUE){
        std::vector<double> unc_bins_mee  = {0., 0.14, 5};
        std::vector<double> unc_bins_ptee = {0., 8};
        TH2D* own_systematic = new TH2D("sys_by_hand", "", unc_bins_mee.size()-1, unc_bins_mee.data(), unc_bins_ptee.size()-1, unc_bins_ptee.data());
        own_systematic->SetBinContent(1, 1, 0.12);
        own_systematic->SetBinContent(2, 1, 0.15);
        sig_combined->SetSymmetricRelSystematics(own_systematic);
      }
      else {
        han_systematic->Process(LmHandler::kSystematic_Average);
        // han_systematic->Process(LmHandler::kSystematic_WeightedAverage);

        TH2D* sys_unc = dynamic_cast<TH2D*>(han_systematic->GetRelSystematics()->Clone("clone"));
        std::cout << "Systematic: " << sys_unc->GetBinContent(1,1) << std::endl;
        sig_combined->SetSymmetricRelSystematics(han_systematic->GetRelSystematics());
      }
      sig_combined->Process(LmSignal::kSystematic);
    }
    handler_to_combine_signals->Process(LmHandler::kNoProcess);



    LmHandler* han_combine = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);

    han_combine->SetRatioTitleSize(0.8);
    han_combine->SetRatioTitleOffset(1.1);
    han_combine->SetMarkerSize(markerSize);

    han_combine->SetLegendSize(1);
    han_combine->SetLegendLineSize(0.75);
    han_combine->SetLegendSizeInYScaling(1.3);
    han_combine->SetLegendOffsetX(+0.37);

    han_combine->SetLabelsOffsetX(-0.39);
    // han_combine->SetLegendEntryDrawOption("p");

    han_combine->SetBinningPtee(0,&ptee_bin_LookingAtPtee_0_140);
    // han_combine->SetBinningPtee(1,&ptee_bin_LookingAtPtee_0_140);
    han_combine->SetBinningPtee(1,&ptee_bin_LookingAtPtee_140_380);
    han_combine->SetBinningPtee(2,&ptee_bin_LookingAtPtee_380_740);
    han_combine->SetBinningPtee(3,&ptee_bin_LookingAtPtee_740_1100);
    han_combine->SetBinningPtee(4,&ptee_bin_LookingAtPtee_1100_2900);
    han_combine->SetBinningPtee(5,&ptee_bin_LookingAtPtee_2900_3300);
    han_combine->SetBinningPtee(6,&ptee_bin_LookingAtPtee_3300_5000);

    han_combine->AttachSignal( *(handler_to_combine_signals->GetLmSigCombined()), "data");
    // han_combine->GetLmSignalI(0)->SetCentRange(0, 80);
    han_combine->SetName("han_signal");
    han_combine->SetPlotRangeRatio(0.1, 2.6);
    han_combine->Process(LmHandler::kCompare);
    han_combine->SetFileType("png");



    // Add Cocktail
    LmCocktail* cockt00 = 0x0;
    if (kDoCocktail) {
      std::cout << "Calculating Cocktail" << std::endl;
      cockt00 = ProcessCocktail();

      // // Add cocktail to old handler
      han_combine->SetCocktail(cockt00); // attach complete cocktail to handler. call cockt00->Process() before!
      han_combine->SetDivideOption("0");
      han_combine->SetDrawStyleCocktail("hist c"); // default is "hist"
      if (kDoCocktailOnly)
        han_combine->Process(LmHandler::kCocktailOnly); // create projections of cocktail spectra in the projection binning of the handler. they are stored in each LmCocktailPart.
      else
        han_combine->Process(LmHandler::kCocktail);

      // Add cocktail to old handler
      han_analysis->SetCocktail(cockt00); // attach complete cocktail to handler. call cockt00->Process() before!
      han_analysis->SetDivideOption("0");
      han_analysis->SetDrawStyleCocktail("hist c"); // default is "hist"
      if (kDoCocktailOnly)
        han_analysis->Process(LmHandler::kCocktailOnly); // create projections of cocktail spectra in the projection binning of the handler. they are stored in each LmCocktailPart.
      else
        han_analysis->Process(LmHandler::kCocktail);
    }





    if (kDoCocktail && kDoSystematics){
      std::cout << "Printing spectra for cocktail + systematics" << std::endl;
      // Print with included Cocktail
      han_combine->SetPlotRangeY(1.01e-5, 100); // Normal invariant mass

      han_combine->SetPlotRangeRatio(0.1, 2.99);
      han_combine->SetDoRatio(kDoRatio, 0.3);

      han_systematic->SetPlotRangeY(1e-4, 10);
      han_analysis->SetPlotRangeRatio(0.5, 2);


      for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj){
        // han_combine->PrintCompareSig_Mee(iProj, printLegend, Form("+_ana_cocktail_%s_%s",sOptCent.Data(),sOptPt.Data()), 2, 20);
        han_analysis->PrintCompareSig_Mee(iProj, printLegend, Form("+_all_cocktail_%s_%s",sOptCent.Data(),sOptPt.Data()), 2, 20);

        // han_combine->PrintCompare(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, iProj, LmBaseSignal::kProjOnMee, Form("+_ana_cocktail_%s_%s",sOptCent.Data(),sOptPt.Data()), true, true);

        // han_combine->PrintCompare(LmSignal::kRfactor, iProj, printLegend, "+_ana_cocktail", kTRUE, kFALSE, kFALSE);
        // han_combine->PrintCompareSoverB_Mee(iProj, printLegend, Form("+_analysis_ana_%s_%s",sOptCent.Data(),sOptPt.Data()), 2, 20);
        // han_combine->PrintCompareSignif_Mee(iProj, printLegend, Form("+_analysis_ana_%s_%s",sOptCent.Data(),sOptPt.Data()), 2, 20);

      }

      han_combine->SetPlotRangeMee(0.1, 1.1);
      han_combine->SetPlotRangeY(-0.01, 2e-1);
      for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj){
        // han_combine->PrintCompare(LmSignal::kSubSig, iProj, LmBaseSignal::kProjOnMee, "+_ana_cocktail_nonLogy", kTRUE, kFALSE, kFALSE);
      }

      // Pair pT histograms
      han_combine->ResetPlotRangeY();
      han_combine->SetPlotRangeY(1e-4, 1e2);
      for(UInt_t iProj = 0; iProj < binsMee_forPtee.size(); ++iProj){
        han_combine->PrintCompareSig_Ptee(iProj, printLegend, Form("+_ana_cocktail_%s_%s",sOptCent.Data(),sOptPt.Data()));
        // han_analysis->PrintCompareSig_Ptee(iProj, printLegend, Form("+_all_cocktail_%s_%s",sOptCent.Data(),sOptPt.Data()));
      }

      // pt wise R-Factor
      han_analysis->SetPlotRangeY(0.99, 1.01); // Normal invariant mass
      for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj){
        // han_analysis->PrintCompare(LmSignal::kRfactor, iProj, printLegend, "+_ana_cocktail", kTRUE, kFALSE, kFALSE);
      }

    }

    cockt00->WriteHist2D();

    // ///////////////////////////////
    // // //   // RFACTOR PT WISE
    //   TCanvas c1;
    //   // std::vector<TH1D*> vProjX = han_analysis->CollectProjections(LmSignal::kRfactor, 5, LmBaseSignal::kProjOnMee);
    //   // std::vector<TH1D*> vProjX = han_analysis->CollectProjections(LmSignal::kRfactor, 5, LmBaseSignal::kProjOnPtee);
    //   std::vector<TH1D*> vProjX;
    //   vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(0, LmSignal::kProjOnMee)->GetDatahist());
    //   vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(1, LmSignal::kProjOnMee)->GetDatahist());
    //   vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(2, LmSignal::kProjOnMee)->GetDatahist());
    //   vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(3, LmSignal::kProjOnMee)->GetDatahist());
    //   // vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(4, LmSignal::kProjOnMee)->GetDatahist());
    //   TH1D* h_axis = new TH1D("r factor", "r factor", 1, 0, 3);
    //   h_axis->SetAxisRange(0.9, 1.05, "Y");
    //   h_axis->SetTitle("R-Factor;m_{ee} (GeV/#it{c}^{2});R-Factor");
    //   h_axis->Draw();
    //
    //   for (unsigned int i = 0; i < vProjX.size(); ++i){
    //     vProjX.at(i)->SetMarkerStyle(20);
    //     vProjX.at(i)->SetMarkerColor(LmHelper::GetUniformColor(i, vProjX.size()));
    //     vProjX.at(i)->SetLineColor(LmHelper::GetUniformColor(i, vProjX.size()));
    //     vProjX.at(i)->Draw("same p");
    //   }
    //
    //   TLegend leg(0.5,0.15,0.9,0.4);
    //   leg.AddEntry(vProjX.at(0), "0 < p_{T,ee} < 1 GeV/c", "lpe");
    //   leg.AddEntry(vProjX.at(1), "1 < p_{T,ee} < 2 GeV/c", "lpe");
    //   leg.AddEntry(vProjX.at(2), "2 < p_{T,ee} < 3 GeV/c", "lpe");
    //   leg.AddEntry(vProjX.at(3), "3 < p_{Tee} < 8 GeV/c", "lpe");
    //   // leg.AddEntry(vProjX.at(4), "5 < p_{Tee} < 8 GeV/c", "lpe");
    //   // leg.AddEntry(vProjX.at(0), "0 < m_{ee} < 0.14 GeV/c", "lpe");
    //   // leg.AddEntry(vProjX.at(1), "1 < m_{ee} < 2 GeV/c", "lpe");
    //   // leg.AddEntry(vProjX.at(2), "2 < m_{ee} < 3 GeV/c", "lpe");
    //   // leg.AddEntry(vProjX.at(3), "3 < m_{ee} < 5 GeV/c", "lpe");
    //   // leg.AddEntry(vProjX.at(4), "5 < m_{ee} < 8 GeV/c", "lpe");
    //   leg.DrawClone("same");
    //
    //
    //   std::cout << vProjX.size() << std::endl;
    //   // vProjX.at(3)->Draw("same");
    //   c1.SaveAs("r-factor.pdf");
    // // // /////////////////////////////////////////////
    // // //

  }

}


//_______________________________________________________________________________________________
int ExtractPhiVtemplates()
{
  LmHelper::Info("========== extractPhiVtemplates ==========");
  //
  // save phiV template histograms (3D) to a compact rootfile.
  //
  // define vectors to store the different class objects
  std::vector<LmManager*>     mgrVec; // works when using pointers (they survive after the for-loop). otherwise fancy errors.
  std::vector<LmBackground*>  bkgVec;
  std::vector<LmSignal*>      sigVec;

  // Add all configs to LmFileManager for efficient file handling
  for (int ic=1; ic<3; ic++) {
    LmFileManager::Instance()->AddConfig( cconfig_phiV[ic] );
  }
  std::cout << "Read in configs" << std::endl;
  {
    for (int ic=0; ic<2; ic++)
    {
      // create manager from config string
      LmManager* mgr = new LmManager(const_cast<char*>(cconfig_phiV[ic+1].Data()));// (only one rootfile, instead of low+high)
      if (cconfig_phiV[ic].Contains("data_4D") || cconfig_phiV[ic].Contains("MC_4D"))
        mgr->SetInputhistAndDim("M_Pt_PhivPair_OpeningAngle", 4);
      else
        mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
      mgr->SetEnableEffiCorr(kFALSE);
      mgr->SetRebinning2D(mee_bin0020.size()-1, mee_bin0020.data(), n_ptee_bin, ptee_bin);
      mgr->Process(LmManager::kDontCleanUp);
      mgrVec.push_back(mgr);

      LmBackground* bkg_i = new LmBackground(*(mgrVec.at(ic)));
      //bkg_i->SetUseRfactor(kFALSE);
      bkg_i->Process(LmBackground::kHybrid);
      bkgVec.push_back(bkg_i);

      TString signame = mgrVec.at(ic)->GetName();
      //signame.Append(" "+mgrVec.at(ic)->GetAll3DProjRanges());
      LmSignal* sig_i_Std = new LmSignal(*(mgrVec.at(ic)), *(bkgVec.at(ic)), signame.Data()); //Form("Projection_%d", ic)
      sig_i_Std->SetDoSubtraction(kTRUE);
      sig_i_Std->SetDoSignifRaw(kDoSignifRaw);
      sig_i_Std->SetDoNormBinwidth(kDoNormBinwidth);
      sig_i_Std->SetDoNormNevents(kDoNormNevents);
      sig_i_Std->Process(LmSignal::kStd);
      sigVec.push_back(sig_i_Std);
    }
    std::cout << "Read in config file" << std::endl;

    Double_t plotMeeMin  = 0., plotMeeMax  = 0.7;
    Double_t plotPteeMin = 0., plotPteeMax = 8.0;

    LmHandler* han_compare = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
    // attach signals to compare handler. they may already be processed or not.
    for (unsigned int i=0; i<sigVec.size(); i++) {
      han_compare->AttachSignal(*(sigVec.at(i)), sigVec.at(i)->GetName());
    }
    han_compare->SetPlotRangeRatio(0.04, 0.1);
    han_compare->SetDoRatio(kDoRatio, 0.4, kTRUE);
    han_compare->Process(LmHandler::kCompare); // not needed if the attached signals were processed by a previous handler.

    UInt_t histbits=1;
    Bool_t kDoLegend=kTRUE;
    han_compare->SetPlotRangeYMargins(2, 50);
    //    han_compare->SetPlotRangeY(5e1, 1e6);
    for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
      histbits=LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg;//+LmSignal::kUnlikeMix;
      han_compare->PrintCompare(histbits, i, LmBaseSignal::kProjOnMee, Form("+Test"), kDoLegend);
      //histbits=LmSignal::kBkg;//+LmSignal::kLikeMix;
      //han_compare->PrintCompare(histbits, i, LmBaseSignal::kProjOnMee, Form("+%s",GetAllOptions().Data()), kDoLegend);
    }
    han_compare->ResetPlotRangeY();

    // write most important histograms to rootfile:
    // when running with option "all", there is still a bug with the subdirectories...
    const Char_t* filename = "template_conversions_cut5_pt200_0080.root";
    TFile* _fileOut = new TFile(filename, "RECREATE");
    //han_compare->SetRootfile(_fileOut);
    han_compare->Write3DHist(LmSignal::kUnlike+LmSignal::kBkg); //in 3D only Unlike and Bkg exist.
    _fileOut->Close();

    for (int ic=0; ic<2; ic++) {
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




//_______________________________________________________________________________________________
int PhiVstudy() {
  LmHelper::Info("========== doPhiVstudy ==========");

  for (int i = 0; i < n_ptee_bin; i++) {
    Double_t bins3DProjRangeY[] = {ptee_bin[i], ptee_bin[i + 1]}; // ptee
    std::cout << "pTee value: " << ptee_bin[i] << "    " << ptee_bin[i + 1]
              << std::endl;
    //
    std::vector<LmManager *> mgrVec; // works when using pointers (they survive
                                     // after the for-loop). otherwise fancy
                                     // errors.
    std::vector<LmBackground *> bkgVec;
    std::vector<LmSignal *> sigVec;
    std::vector<LmManager *> mgrVec_inputs;

    {
      TString projOpt =
          "xz"; // option="ab" means: a vertical, b horizontal (ROOT-convention)
      // TString projOpt = "yx"; // option="ab" means: a vertical, b horizontal
      // (ROOT-convention)
      // 'xz' means mee on y, 'yz' means ptee on y

      // kDoPhiV = LmManager::kTemplUnsub;
      kDoPhiV = LmManager::kTemplSub;
      // kDoPhiV = LmManager::kNoCut;

      TFile *_fTempl5 = 0x0;
      // TH3D *hSig3=0x0, *hCon3=0x0, *hULS3=0x0, *hLS3=0x0;
      TH3D *hSig = 0x0, *hCon = 0x0, *hNorm = 0x0;
      if (kDoPhiV >= LmManager::kTemplUnsub) { // if templates are needed
        LmHelper::Info("Reading in templates");
        _fTempl5 = LmHelper::SafelyOpenRootfile("./input/templates/template_conversions_cut5_pt200_0080.root");
        hSig = (TH3D *)LmHelper::GetHistFromTemplateFile(_fTempl5, 0, "hUnlike");
        hSig->SetName("hSig");
        hCon = (TH3D *)LmHelper::GetHistFromTemplateFile(_fTempl5, 1, "hUnlike");
        hCon->SetName("hCon");
        hNorm = (TH3D *)hSig->Clone("hNorm");
        hNorm->Add(hCon);
      }

      std::vector<UInt_t> phiVtype = {LmManager::kNoCut, LmManager::kNoCut,
                                      LmManager::kNoCut, LmManager::kTemplSub,
                                      LmManager::kFlatCorrSub};

      // Add all configs to LmFileManager for efficient file handling
      for (int ic = 0; ic < n_config_phiV; ic++) {
        LmFileManager::Instance()->AddConfig(cconfig_phiV[ic]);
      }

      Double_t *phiv_bin_local = 0x0;
      Int_t phiv_rebinfactor = 1; // 1 or 4
      phiv_bin_1[0] *= phiv_rebinfactor;
      phiv_bin[0] *= phiv_rebinfactor;

      // fill vector of input managers
      for (int ic = 0; ic < n_config_phiV; ic++) {
        LmManager *mgr = new LmManager(const_cast<char *>(
            cconfig_phiV[ic]
                .Data())); // (only one rootfile, instead of low+high)
        // set further configuration for the manager
        if (cconfig_phiV[ic].Contains("data_4D") ||
            cconfig_phiV[ic].Contains("MC_4D")) {
          mgr->SetInputhistAndDim("M_Pt_PhivPair_OpeningAngle", 4);
          phiv_bin_local = &phiv_bin_1[0];
          if (cconfig_phiV[ic].Contains("bothTasks"))  phiv_bin_local = &phiv_bin[0]; // some 4D MC still have old phiV binning.
        } else {
          mgr->SetInputhistAndDim(const_cast<char *>(inputhist.Data()),
                                  inputdim);
          phiv_bin_local = &phiv_bin[0];
        }
        mgr->SetProjOption(projOpt.Data());
        mgr->SetEnableEffiCorr(kFALSE);
        mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
        mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
        mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
        mgr->SetTemplateNormRegionMin(n_cutPhiVbelow, cutPhiVbelow); // only needed for some template types.
        mgr->SetTemplateNormRegionMax(n_cutPhiVabove, cutPhiVabove); // only needed for some template types.
        // use individual phiV cut settings:
        if ((int)phiVtype.size() > ic)  kDoPhiV = phiVtype.at(ic);
        if (kDoPhiV == LmManager::kTemplSub) mgr->SetExclusionZTemplates(hSig, 0x0, LmManager::kTemplSub, hSig, hNorm); // special case implemented for phiV-study, check // LmManager::CorrectForExclusionCutIn2D().

        mgr->SetEnableExclusionCutZ(kDoPhiV); // to be able to change or
                                              // deactivate the cut without
                                              // changing the code above.

        Double_t thetaEEmin = 0.00;

        mgr->SetProjRange(thetaEEmin, TMath::Pi(), 3); // axis 3 = dimension 4 = opening angle.
        mgr->SetThetaEEmin(thetaEEmin);
        if (projOpt.EqualTo("xz")) // 'xz' means mee on y, phiv on x
          mgr->SetRebinning2D(n_phiv_bin, phiv_bin_local, mee_bin0010.size() - 1, mee_bin0010.data());
        if (projOpt.EqualTo("yz")) // 'yz' means ptee on y, phiv on x
          mgr->SetRebinning2D(n_phiv_bin, phiv_bin_local, n_ptee_bin, ptee_bin);
        if (projOpt.EqualTo("yx")) // 'yx' means ptee on y, mee on x (default analysis)
          mgr->SetRebinning2D(mee_bin0010.size() - 1, mee_bin0010.data(), n_ptee_bin, ptee_bin);
        // read in histograms from data files
        mgr->Process(LmManager::kReadInputOnly);
        mgrVec_inputs.push_back(mgr);
      }

      // define 3D-projection binning
      // at least one of these two arrays should have only a single integrated
      // bin, otherwise we get many managers...
      // since there is only one handler for all signals, all 3D-subranges - if
      // any - will be plotted together.
      Double_t bins3DProjRangeX[] = {-1, -1}; // mee
      // Double_t bins3DProjRangeX[] = {0, 1}; // mee
      unsigned int n_bins3DProjRangeX = sizeof(bins3DProjRangeX) / sizeof(*bins3DProjRangeX) - 1;
      unsigned int n_bins3DProjRangeY = sizeof(bins3DProjRangeY) / sizeof(*bins3DProjRangeY) - 1;
      if (n_bins3DProjRangeX > 1)
        LmHelper::Error("computation of phiV-corrected spectra with templates "
                        "for multiple mee slices at the same time is messed "
                        "up!");
      if (n_bins3DProjRangeY > 1)
        LmHelper::Error("computation of phiV-corrected spectra with templates "
                        "for multiple ptee slices at the same time is messed "
                        "up!");

      // fill vector of managers with selected 3D subranges
      for (unsigned int iproj_x = 0; iproj_x < n_bins3DProjRangeX; iproj_x++) {
        for (unsigned int iproj_y = 0; iproj_y < n_bins3DProjRangeY; iproj_y++) {
          for (unsigned int imgr = 0; imgr < mgrVec_inputs.size(); imgr++) {
            // make a copy of the manager including its input histograms
            LmManager *mgr_i = new LmManager(*(mgrVec_inputs.at(imgr)));
            if (n_bins3DProjRangeY > 1 || bins3DProjRangeY[0] != 0 || bins3DProjRangeY[1] == 1)
              mgr_i->SetName(Form(
                  // "%s (%.3f-%.3f GeV)", mgr_i->GetName(), bins3DProjRangeY[iproj_y],
                  "%s", mgr_i->GetName())); // cannot use "/c" when
                                                   // saving it to rootfile.
            // select different subranges in input histograms
            mgr_i->Set3DProjRangeX(bins3DProjRangeX[iproj_x], bins3DProjRangeX[iproj_x + 1]);
            mgr_i->Set3DProjRangeY(bins3DProjRangeY[iproj_y], bins3DProjRangeY[iproj_y + 1]);
            // add new manager to vector
            mgrVec.push_back(mgr_i);
          }
          // add manager for integrated y range, if there is more than one bin
          // in y. (nicer to have a separate loop)
          if (n_bins3DProjRangeY > 1 && iproj_y == n_bins3DProjRangeY - 1) {
            for (unsigned int imgr = 0; imgr < mgrVec_inputs.size(); imgr++) {
              LmManager *mgr_i = new LmManager(*(mgrVec_inputs.at(imgr)));
              mgr_i->SetName(
                  // Form("%s (%.3f-%.3f GeV)", mgr_i->GetName(), bins3DProjRangeY[0], bins3DProjRangeY[iproj_y + 1])); // cannot use "/c" when saving it to rootfile.
                  Form("%s", mgr_i->GetName())); // cannot use "/c" when saving it to rootfile.
              mgr_i->Set3DProjRangeX(bins3DProjRangeX[0], bins3DProjRangeX[iproj_x + 1]);
              mgr_i->Set3DProjRangeY(bins3DProjRangeY[0], bins3DProjRangeY[iproj_y + 1]);
              mgrVec.push_back(mgr_i);
            }
          }
        }
      }

      // for each manager: create background and signal class from it, configure
      // and process them, store them in vectors
      for (unsigned int iproj = 0; iproj < mgrVec.size(); iproj++) {
        std::cout << " iproj = " << iproj << " name = " << mgrVec.at(iproj)->GetName() << std::endl;
        // process the managers: make the projections, rebinning, corrections...
        mgrVec.at(iproj)->Process(LmManager::kDontReadInput); // dont read in rootfiles again
        // mgrVec.at(iproj)->Print2DUnlike(Form("c2DUnlike_%d.pdf",iproj));

        LmBackground *bkg_i = new LmBackground(*(mgrVec.at(iproj)));
        bkg_i->Process(LmBackground::kHybrid);
        bkgVec.push_back(bkg_i);

        TString signame = mgrVec.at(iproj)->GetName();
        if (mgrVec.at(iproj)->GetExclCutType() == LmManager::kTemplSub) {
          // try to add an uncut subtracted signal to help in the phiV
          // correction of the current signal.
          if (mgrVec.at(0)->GetExclCutType() == LmManager::kNoCut) mgrVec.at(iproj)->AddVisualSig(sigVec.at(0)->GetSubSig2D(), "hDataOrig", "data, no #phi_{V} corr.");
        }

        LmSignal *sig_i_Std =
            new LmSignal(*(mgrVec.at(iproj)), *(bkgVec.at(iproj)),
                         signame.Data()); // Form("Projection_%d", iproj)
        sig_i_Std->SetDoSubtraction(kTRUE);
        sig_i_Std->SetDoSignifRaw(kDoSignifRaw);

        sig_i_Std->SetDoNormBinwidth(kDoNormBinwidth);
        sig_i_Std->SetDoNormNevents(kDoNormNevents);

        sig_i_Std->Process(LmSignal::kStd);
        // if a signal has produced additional histograms, e.g. to visualize its
        // phiV-correction, then extract them for plotting.
        Int_t skipFirstVisual = 1;
        for (unsigned int ivis = skipFirstVisual;
             ivis < sig_i_Std->GetNVisualSig(); ivis++) {
          sigVec.push_back(sig_i_Std->GetVisualSigI(ivis));
        }
        sigVec.push_back(sig_i_Std);
      }

      // close rootfile(s) from input manager(s) (to free memory if many files
      // have been opened...)
      for (unsigned int imgr = 0; imgr < mgrVec_inputs.size(); imgr++) {
        mgrVec_inputs.at(imgr)->Process(LmManager::kCleanUp);
      }

      Double_t plotMeeMin = 0., plotMeeMax = 0.5;
      Double_t plotPteeMin = 0., plotPteeMax = 8.0;
      Double_t plotPhiVMin = 0., plotPhiVMax = 3.14; // phiv
      Bool_t kDoLegend = kTRUE;
        Bool_t kDoLogY;

      // std::vector<Double_t> binsPhiV;

      LmHandler *han_compare = new LmHandler(LmHandler::kCompare);
      // attach signals to compare handler. they may already be processed or
      // not.
      for (unsigned int i = 0; i < sigVec.size(); i++) {
        han_compare->AttachSignal(*(sigVec.at(i)), sigVec.at(i)->GetName());
      }
      if (projOpt.EqualTo("xz")) { // 'xz' means mee on y, phiv on x
        han_compare->SetBinsY_forprojOnX(binsMee_forPhiV);
        han_compare->SetBinsX_forprojOnY(binsPhiV);
        han_compare->SetPlotRangeMee(plotPhiVMin, plotPhiVMax);
        han_compare->SetPlotRangePtee(plotMeeMin, plotMeeMax);
        kDoLogY = kFALSE;
      }
      if (projOpt.EqualTo("yz")) { // 'yz' means ptee on y, phiv on x
        han_compare->SetBinsY_forprojOnX(
            binsPtee_forMee); // binsPtee_forPhiV doesnt exist.
        han_compare->SetBinsX_forprojOnY(binsPhiV);
        han_compare->SetPlotRangeMee(plotPhiVMin, plotPhiVMax);
        han_compare->SetPlotRangePtee(plotPteeMin, plotPteeMax);
        kDoLogY = kFALSE;
      }
      if (projOpt.EqualTo(
              "yx")) { // 'yx' means ptee on y, mee on x (default analysis)
        han_compare->SetBinsY_forprojOnX(binsPtee_forMee);
        han_compare->SetBinsX_forprojOnY(binsMee_forPtee);
        han_compare->SetPlotRangeMee(plotMeeMin, plotMeeMax);
        han_compare->SetPlotRangePtee(plotPteeMin, plotPteeMax);
        kDoLogY = kTRUE;
      }

      han_compare->SetPlotRangeRatio(0.1, 2);
      han_compare->SetDoRatio(kDoRatio, 0.3, kFALSE);
      han_compare->SetFileType("png");
      han_compare->Process(LmHandler::kCompare); // not needed if the attached
                                                 // signals were processed by a
                                                 // previous handler.

      UInt_t histbits = 1;
      TString s3Drange = "";
      if (n_bins3DProjRangeY == 1 && (bins3DProjRangeY[0] != 0 || bins3DProjRangeY[1] == 1))
        s3Drange = Form("_ptee%.3fto%.3f", bins3DProjRangeY[0], bins3DProjRangeY[1]);
      if (kDoLogY) {
        han_compare->SetPlotRangeYMargins(2, 50);
      } else {
        han_compare->SetPlotRangeYMargins(0, 1.1);
      }

      for (int i = 0; i <= han_compare->GetMaxBinProj(LmBaseSignal::kProjOnX); ++i) {
        if (projOpt.EqualTo("xz")) { // 'xz' means mee on y, phiv on x han_compare->SetPlotRangeY(-0.005, 0.02);
          Double_t yscale = 20. / TMath::Pi(); // to be used when x=phiV and not normalized per radian.
          if (han_compare->GetLmSignalI(0)->GetDoNormBinwidth()) yscale = 1;
          // if (i == 0 || i == han_compare->GetMaxBinProj(LmBaseSignal::kProjOnX)) han_compare->SetPlotRangeY(-0.001 / yscale, 0.03 / yscale);
          // else if (i <= 2) han_compare->SetPlotRangeY(-0.001 / yscale, 0.005 / yscale);
          // else             han_compare->SetPlotRangeY(-0.001 / yscale, 0.005 / yscale);
        }
        if (projOpt.EqualTo("yx")) { // 'yx' means ptee on y, mee on x (default analysis)
          // han_compare->SetPlotRangeY(1e-6, 1e3); // 1e5?
        }

        han_compare->SetPlotRangeY(0, 0.000021); // 1e5?
        // han_compare->SetPlotRangeY(1, -1);
        // han_compare->SetRequestedSignals("056"); // data

        histbits = LmSignal::kSubSig; //+LmSignal::kUnlike+LmSignal::kBkg;
        han_compare->SetRequestedSignals("01234"); // data + MC sum
        han_compare->PrintCompare(histbits, i, LmBaseSignal::kProjOnX, Form("+%s", s3Drange.Data()), kDoLegend, kDoLogY);
        // han_compare->SetPlotRangeY(0., 0.00001); // 1e5?
        // han_compare->SetRequestedSignals("04"); // data + MC sum
        // han_compare->PrintCompare(histbits, i, LmBaseSignal::kProjOnX, Form("+%s", s3Drange.Data()), kDoLegend, kDoLogY);
      }
      han_compare->ResetPlotRangeY();

      if (projOpt.EqualTo("xz")) { // 'xz' means mee on y, phiv on x
        //|__________|   Mee   |__________|
        han_compare->SetPlotRangeY(1e-4, 1e2);
        for (int i = 0; i <= han_compare->GetMaxBinProj(LmBaseSignal::kProjOnY);
             ++i) {

        }
        han_compare->ResetPlotRangeY();
      }

      // write most important histograms to rootfile:
      TString filename = Form("spectra1D-phiVstud.root");
      // if (n_bins3DProjRangeY == 0 && (bins3DProjRangeY[0] != 0 || bins3DProjRangeY[1] == 1))
        filename.ReplaceAll(".root", Form("_ptee%.3fto%.3f.root", bins3DProjRangeY[0], bins3DProjRangeY[1]));

      TFile *_fileOut = new TFile(filename.Data(), "RECREATE");
      han_compare->Write1DHistSingle(LmSignal::kSubSig + LmSignal::kUnlike + LmSignal::kBkg, LmSignal::kProjOnX); // phiV
      han_compare->Write1DHistSingle(LmSignal::kSubSig + LmSignal::kUnlike + LmSignal::kBkg, LmSignal::kProjOnY); // mee
      _fileOut->Close();

      std::cout << "PhiVstudy done :-)" << std::endl;
    }
    LmFileManager::Instance()->Clear();
    mgrVec.clear();
    bkgVec.clear();
    sigVec.clear();
    mgrVec_inputs.clear();
  }
  return 0;
} // PhiVstudy


int QA(){
  std::cout << "Processing QA()" << std::endl;
  LmQA qa(const_cast<char*>(cconfig_pt400[0].Data()));
  qa.SetColorPalette(57);
  qa.PrintCentrality("QAplots/Event_centrality.png");
  qa.PrintCentrality("QAplots/Event_centrality.pdf");
  // qa.PrintEPTPC("QAplots/Event_epTPC.png");
  // qa.PrintEPV0AC("QAplots/epV0AC.png");
  // qa.PrintEPV0ACvsEPTPC("QAplots/epV0AC_epTPC.png");

  // qa.PrintPtPos("QAplots/PtPos.png");
  // qa.PrintPtNeg("QAplots/PtNeg.png");
  // qa.PrintPtAll("QAplots/Tracking_PtAll.png");
  qa.PrintPtCompare("QAplots/Tracking_PtCompare.png");

  // qa.PrintEtaPos("QAplots/EtaPos.png");
  // qa.PrintEtaNeg("QAplots/EtaNeg.png");
  // qa.PrintEtaAll("QAplots/EtaAll.png");
  // qa.PrintEtaCompare("QAplots/Tracking_EtaCompare.png");

  // qa.PrintPhiPos("QAplots/PhiPos.png");
  // qa.PrintPhiNeg("QAplots/PhiNeg.png");
  // qa.PrintPhiAll("QAplots/PhiAll.png");
  // qa.PrintPhiCompare("QAplots/Tracking_PhiCompare.png");

  // qa.PrintEtaPhiPos("QAplots/Tracking_EtaPhiPos.png");
  // qa.PrintEtaPhiNeg("QAplots/Tracking_EtaPhiNeg.png");
  // qa.PrintEtaPhiAll("QAplots/Tracking_EtaPhiAll.png");
  // qa.PrintEtaPhiAll("QAplots/Tracking_EtaPhiAll.png");

  // qa.PrintITSnClsPos("QAplots/ITSnClsPos.png");
  // qa.PrintITSnClsNeg("QAplots/ITSnClsNeg.png");
  // qa.PrintITSnClsAll("QAplots/ITSnClsAll.png");
  // qa.PrintITSnClsCompare("QAplots/ITSnClsCompare.png");

  // qa.PrintTPCnClsPos("QAplots/TPCnClsPos.png");
  // qa.PrintTPCnClsNeg("QAplots/TPCnClsNeg.png");
  // qa.PrintTPCnClsAll("QAplots/TPCnClsAll.png");
  qa.PrintTPCnClsCompare("QAplots/TPCnClsCompare.pdf");

  // qa.PrintITSChi2Pos("QAplots/ITSChi2Pos.png");
  // qa.PrintITSChi2Neg("QAplots/ITSChi2Neg.png");
  // qa.PrintITSChi2All("QAplots/ITSChi2All.png");
  qa.PrintITSChi2Compare("QAplots/ITSChi2Compare.pdf");

  // qa.PrintTPCChi2Pos("QAplots/TPCChi2Pos.png");
  // qa.PrintTPCChi2Neg("QAplots/TPCChi2Neg.png");
  // qa.PrintTPCChi2All("QAplots/TPCChi2All.png");
  qa.PrintTPCChi2Compare("QAplots/TPCChi2Compare.pdf");

  // qa.PrintTPCrowsOverFindablePos("QAplots/TPCCrossedRowsOverFindablePos.png");
  // qa.PrintTPCrowsOverFindableNeg("QAplots/TPCCrossedRowsOverFindableNeg.png");
  // qa.PrintTPCrowsOverFindableAll("QAplots/TPCCrossedRowsOverFindableAll.png");
  qa.PrintTPCrowsOverFindableCompare("QAplots/Tracking_TPCCrossedRowsOverFindableCompare.pdf");

  // qa.PrintTPCCrossedRowsPos("QAplots/TPCCrossedRowsPos.png");
  // qa.PrintTPCCrossedRowsNeg("QAplots/TPCCrossedRowsNeg.png");
  // qa.PrintTPCCrossedRowsAll("QAplots/TPCCrossedRowsAll.png");
  qa.PrintTPCCrossedRowsCompare("QAplots/Tracking_TPCCrossedRowsCompare.pdf");

  // qa.PrintZVertexPos("QAplots/ZVertexPos.png");
  // qa.PrintZVertexNeg("QAplots/ZVertexNeg.png");
  // qa.PrintZVertexAll("QAplots/ZVertexAll.png");
  // qa.PrintZVertexCompare("QAplots/Tracking_ZVertexCompare.pdf");

  // qa.PrintXYVertexPos("QAplots/XYVertexPos.png");
  // qa.PrintXYVertexNeg("QAplots/XYVertexNeg.png");
  // qa.PrintXYVertexAll("QAplots/XYVertexAll.png");
  // qa.PrintXYVertexCompare("QAplots/Tracking_XYVertexCompare.pdf");

  // qa.PrintPvsPInnerWallTPC("QAplots/PrintPvsPInnerWallTPC.png");

  // ############# QA ####################
  // qa.PrintITSSigmaElevsP("QAplots/ITSSigmaElevsP.pdf");
  // qa.PrintITSSigmaPionvsP("QAplots/ITSSigmaPionvsP.png");
  // qa.PrintITSSigmaKaonvsP("QAplots/ITSSigmaKaonvsP.png");

  // qa.PrintTPCSigmaElevsP("QAplots/TPCSigmaElevsP.pdf");
  // qa.PrintTPCSigmaPionvsP("QAplots/TPCSigmaPionvsP.png");
  // qa.PrintTPCSigmaKaonvsP("QAplots/TPCSigmaKaonvsP.png");

  // qa.PrintTOFSigmaElevsP("QAplots/TOFSigmaElevsP.pdf");

  // qa.PrintTPCSigmaElevsEta("QAplots/TPCSigmaElevsEta.png");
  // qa.PrintPIDTPCdEdxvsP("QAplots/PID_TPCdEdxvsP.png");
  // qa.PrintPID("QAplots");

  // qa.PrintPhiEtaProjection("QAplots/Phi_ASide.png", "phi",  0.0, 0.8);
  // qa.PrintPhiEtaProjection("QAplots/Phi_CSide.png", "phi", -0.8, -0.00001);
  //
  // qa.PrintPhiPtProjection("QAplots/Phi_Pt0_1.png", "phi",  0.0, 1.0);
  // qa.PrintPhiPtProjection("QAplots/Phi_Pt1_2.png", "phi",  1.0, 2.0);
  // qa.PrintPhiPtProjection("QAplots/Phi_Pt2_3.png", "phi",  2.0, 3.0);

  return 0;
}

Double_t TwoGaussiansConnected(Double_t *x, Double_t *par)
{
   Float_t xx =x[0];
   double f = 0;
   if (xx < 0){
     f = par[0] * TMath::Exp(-0.5 * ((xx-par[1]) / par[2]) * ((xx-par[1]) / par[2]));
   }
   else if (xx >= 0){
     f = par[0] * TMath::Exp(-0.5 * ((xx-par[1]) / par[3]) * ((xx-par[1]) / par[3]));
   }
   return f;
}
double DoVirtualPhotonFit(TH1D& h1, TH1D& reso, TH1D& photon, TH1D& charmafterscaling,
                          std::vector<double>& normRegionHigh, unsigned int standardNormRegionHigh,
                          std::vector<double>& fitRegionLow,   unsigned int standardFitRegionLow,
                          std::vector<double>& fitRegionHigh,  unsigned int standardFitRegionHigh,
                          double& r_error){
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

void PlotSignalBeforeFit(TH1D& h1, TH1D& reso, TH1D& pion, TH1D& eta, TH1D& LFrest, TH1D& HF, TH1D& photon, unsigned int cut_i, unsigned int pt_i){
  TCanvas c1("c1", "", 800, 800);

  TH1D h_sum = *(dynamic_cast<TH1D*>(reso.Clone("sum")));
  h_sum.Add(&HF);
  //
  h1.SetMarkerColor(kBlue);
  h1.SetMarkerStyle(20);
  h1.SetMarkerSize(1.5);
  h1.Draw("p");
  //
  reso.SetMarkerColor(kOrange+2);
  reso.SetLineWidth(4);
  reso.SetLineColor(kOrange+2);
  reso.Draw("h same");

  pion.SetMarkerColor(kRed);
  pion.SetLineWidth(1);
  pion.SetLineColor(kRed);
  pion.Draw("h same");

  eta.SetMarkerColor(kBlue);
  eta.SetLineWidth(1);
  eta.SetLineColor(kBlue);
  eta.Draw("h same");

  LFrest.SetMarkerColor(kGreen+2);
  LFrest.SetLineWidth(1);
  LFrest.SetLineColor(kGreen+2);
  LFrest.Draw("h same");
  //
  HF.SetMarkerColor(kMagenta);
  HF.SetLineWidth(4);
  HF.SetLineColor(kMagenta);
  HF.Draw("h same");

  h_sum.SetLineColor(kBlack);
  h_sum.SetLineWidth(4);
  h_sum.Draw("h same");

  photon.SetMarkerColor(kGreen+2);
  photon.SetLineColor(kGreen+2);
  photon.SetLineWidth(4);
  photon.Draw("h same");

  h1.SetAxisRange(0., 0.7, "X");
  h1.SetAxisRange(1e-4, 10, "Y");
  h1.GetYaxis()->SetTitle("yield");
  //
  TLegend leg1(0.6, 0.7, 0.88, 0.88);
  leg1.AddEntry(&h1, "data", "lpe");
  leg1.AddEntry(&reso,   "light flavour before fitting", "lpe");
  leg1.AddEntry(&h_sum,       "cocktail sum before fitting", "lpe");
  leg1.AddEntry(&photon, "virtual photon before fitting", "lpe");
  leg1.AddEntry(&HF,     "heavy flavour (not refitted)", "lpe");
  leg1.Draw("same");

  h1.DrawCopy(" same");
  c1.SetLogy();
  c1.SaveAs(Form("photon_fit/001_plot_signal/signal_cut%d_mass%d.pdf", cut_i, pt_i));
  return;
}


struct r_Sys{
  TH1D r;
  std::string caption;
};

void DrawRFactors(std::vector<r_Sys>& v_r_Sys, std::string filename){
  TCanvas c1("c1", "", 800,800);
  c1.SetLeftMargin(0.17);
  c1.SetRightMargin(0.05);
  TLine line0(binsPtee_forMee[0], 0., binsPtee_forMee[binsPtee_forMee.size()-1], 0.);
  line0.SetLineWidth(2);
  v_r_Sys[0].r.SetAxisRange(-0.2, 0.7, "Y");
  v_r_Sys[0].r.DrawCopy("p");
  TLegend leg_r_sys_fit_region(0.19, 0.6, 0.45, 0.88);
  // std::cout << "Number of different r-factors plotted: " << v_r_Sys.size() << std::endl;;
  for (unsigned int i = 0; i < v_r_Sys.size(); ++i){
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
void PrintChiSquare(std::vector<r_Sys>& vec){

  TH1D h1_mean = *(dynamic_cast<TH1D*>(vec[0].r.Clone("mean")));

  for (int bin_i = 1; bin_i < vec[0].r.GetNbinsX()+1; ++bin_i){
    double sum = 0;
    for (unsigned int i = 0; i < vec.size(); ++i){
      sum = sum + vec[i].r.GetBinContent(bin_i);
    }
    double mean = sum / (double)vec.size();
    std::cout << "mean bin " << bin_i << ": " << mean << std::endl;
    h1_mean.SetBinContent(bin_i, mean);
  }

  for (unsigned int i = 0; i < vec.size(); ++i){
    Double_t chi2ndf = vec[i].r.Chi2Test(&h1_mean, "UU NORM CHI2/NDF");
    // Double_t chi2ndf = vec[i].r.Chi2Test(&h1_mean, "NORM UU CHI2/NDF");
    std::cout << "cut " << i << " with chi2/ndf = " << chi2ndf << std::endl;
  }
  // Chi2 += TMath::Power(h1->GetBinContent(i)-h2->GetBinContent(i),2) / (TMath::Power(h1->GetBinError(i),2) + TMath::Power(h2->GetBinError(i),2));

  // TCanvas c3("c3", "c3", 800, 800);
  // c3.cd();
  // h1_mean.Draw("hist");
  // c3.SaveAs("photon_fit/test.pdf");


  // for (int bin_i = 1; bin_i < vec[0].r.GetNbinsX()+1; ++bin_i){
  //   double chi2perBin = 0;
  //   for (unsigned int i = 0; i < vec.size(); ++i){
  //     sum = sum + vec[i].r.GetBinContent(bin_i);
  //   }
  //   double mean = sum / (double)vec.size();
  //   std::cout << "mean bin " << bin_i << ": " << mean << std::endl;
  //   mean_per_bin.push_back(mean);
  // }

}
double GetRMSofBin(std::vector<r_Sys>& vec, int bin){
  // calculates RMS as sqrt(1/N * sum((x_i - mean)^2))
  // TH1D h1_rms("h1_rms", "", 110, -0.1, 1.);
  // for(unsigned int i = 0; i < vec.size(); ++i){
  //   h1_rms.Fill(vec[i].r.GetBinContent(bin+1));
  // }
  // TCanvas c3("c3", "", 800, 800);
  // h1_rms.Draw("hist");
  // c3.SaveAs(Form("photon_fit/test_bin%d.pdf", bin));
  // double rms_with_h1 = h1_rms.GetRMS(1);

  // calculate mean
  double sum = 0;
  for (unsigned int i = 0; i < vec.size(); ++i){
    sum = sum + vec[i].r.GetBinContent(bin+1);
  }
  double mean = sum / (double)vec.size();

  double rms_sum = 0;
  for (unsigned int i = 0; i < vec.size(); ++i){
    rms_sum = rms_sum + (vec[i].r.GetBinContent(bin+1) - mean) * (vec[i].r.GetBinContent(bin+1) - mean);
  }
  double rms = TMath::Sqrt(rms_sum / (double)vec.size());

  return rms;
}


int Photon(){
  TH1::SetDefaultSumw2(true);

  Bool_t DoTOFreq = kFALSE;

  binsPtee_forMee.clear();
  // binsPtee_forMee.push_back(0.);
  // binsPtee_forMee.push_back(1.);
  // binsPtee_forMee.push_back(2.);
  // binsPtee_forMee.push_back(4.);
  // // binsPtee_forMee.push_back(5.);
  // binsPtee_forMee.push_back(8.);

  binsPtee_forMee.push_back(1.);
  binsPtee_forMee.push_back(1.5);
  binsPtee_forMee.push_back(2.);
  binsPtee_forMee.push_back(3.);
  // binsPtee_forMee.push_back(4.);
  binsPtee_forMee.push_back(5.);
  binsPtee_forMee.push_back(8.);

  LmRebinner rebinner;
	rebinner.SetRebinning2D(mee_bin.size()-1, mee_bin.data(), n_ptee_bin, ptee_bin);

  // ###########################################################################
  // Reading photon file
  // std::string photon_file = "photon_fit/input/LFcocktail_pt400_eta08_wRatio_newReso.root";
  // std::string photon_file = "photon_fit/input/cocktail_LF_v2.root";
  std::string photon_file;
  // if      (kDo200MeV && kCentrality == kCent::kCent0080) photon_file = "photon_fit/input/pt200/cocktail_LF_v2.root";
  if      (kDo200MeV && kCentrality == kCent::kCent0080) photon_file = "input/cocktail/pt200/0080/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_0080.root";
  else if (kDo200MeV && kCentrality == kCent::kCent0020) photon_file = "input/cocktail/pt200/0020/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_0020.root";
  else if (kDo200MeV && kCentrality == kCent::kCent2040) photon_file = "input/cocktail/pt200/2040/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_2040.root";
  else if (kDo200MeV && kCentrality == kCent::kCent4080) photon_file = "input/cocktail/pt200/4080/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_4080.root";
  else           photon_file = "photon_fit/input/cocktail_LF_v2.root";
  TFile* file2 = TFile::Open(photon_file.c_str(), "READ");
  TDirectoryFile* dir2 = dynamic_cast<TDirectoryFile*>(file2->Get("LMeeCocktailMC"));
  TList* list2 = dynamic_cast<TList*>(dir2->Get("LMeeCocktailMC_0.80"));

  TH1F hnEvents = *(dynamic_cast<TH1F*>(list2->FindObject("NEvents")));
  double nEvents = hnEvents.GetBinContent(1);
  std::cout << "Number of events in cocktail calculation: " << nEvents << std::endl;
  TH2D h2_photon   = *(reinterpret_cast<TH2D*>(list2->FindObject("pteevsmee_Virtual_Photon")));
  // h2_photon.Scale(1. / nEvents);
  rebinner.Rebin2DHistogram(h2_photon);

  std::vector<TH1D> v_photon;
  for(unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
    double value_low  = -1;
    double value_high = -1;
    if (i == binsPtee_forMee.size()-1){ // integrated pT bin
      value_low  = binsPtee_forMee[0];
      value_high = binsPtee_forMee[binsPtee_forMee.size()-1];
    }
    else {
      value_low  = binsPtee_forMee[i];
      value_high = binsPtee_forMee[i+1];
    }

    int bin_low  = h2_photon.GetYaxis()->FindBin(value_low);
    int bin_high = h2_photon.GetYaxis()->FindBin(value_high-0.00001);
    TH1D h1 = *(h2_photon.ProjectionX(Form("photon_bin_%d_%d", bin_low, bin_high), bin_low, bin_high, "e"));

    // TH1D h1_rebin = *((TH1D*)(h1.Rebin(n_mee_bin, Form("photon_rebinned_bin_%d_%d", bin_low, bin_high),mee_bin)));
    // std::cout << h1_rebin.GetNbinsX() << std::endl;
    // h1_rebin.Scale(1. / nEvents);
    // v_photon.emplace_back(h1_rebin);

    h1.SetTitle("VPhoton");

    h1.Scale(1. / nEvents, "width");
    v_photon.emplace_back(h1);
  }


  // ###########################################################################
  // Reading cocktail file
  std::string cocktail_file_LF;
  // if      (kDo200MeV && kCentrality == kCent::kCent0080) cocktail_file_LF = "photon_fit/input/pt200/cocktail.root";
  if      (kDo200MeV && kCentrality == kCent::kCent0080) cocktail_file_LF = "photon_fit/input/pt200_fullMC/0080/cocktail.root";
  // if      (kDo200MeV && kCentrality == kCent::kCent0080) cocktail_file_LF = "photon_fit/input/pt200_fullMC/0080_scaled_charm/cocktail.root";
  else if (kDo200MeV && kCentrality == kCent::kCent0020) cocktail_file_LF = "photon_fit/input/pt200/0020/cocktail.root";
  else if (kDo200MeV && kCentrality == kCent::kCent2040) cocktail_file_LF = "photon_fit/input/pt200/2040/cocktail.root";
  else if (kDo200MeV && kCentrality == kCent::kCent4080) cocktail_file_LF = "photon_fit/input/pt200/4080/cocktail.root";
  else           cocktail_file_LF = "photon_fit/input/cocktail_LF.root";
  TFile* file3 = TFile::Open(cocktail_file_LF.c_str(), "READ");
  TH2D h2_sum      = *(dynamic_cast<TH2D*>(file3->Get("Sum")));
  TH2D h2_pion     = *(dynamic_cast<TH2D*>(file3->Get("Pion")));
  TH2D h2_eta      = *(dynamic_cast<TH2D*>(file3->Get("Eta")));
  TH2D h2_etaprime = *(dynamic_cast<TH2D*>(file3->Get("EtaPrime")));
  TH2D h2_rho      = *(dynamic_cast<TH2D*>(file3->Get("Rho")));
  TH2D h2_omega    = *(dynamic_cast<TH2D*>(file3->Get("Omega")));
  TH2D h2_phi      = *(dynamic_cast<TH2D*>(file3->Get("Phi")));

  std::string cocktail_file_HF;
  if      (kDo200MeV && kCentrality == kCent::kCent0080) cocktail_file_HF = "photon_fit/input/pt200_fullMC/0080/cocktail.root";
  // if      (kDo200MeV && kCentrality == kCent::kCent0080) cocktail_file_HF = "photon_fit/input/pt200_fullMC/0080_scaled_charm/cocktail.root";
  else if (kDo200MeV && kCentrality == kCent::kCent0020) cocktail_file_HF = "photon_fit/input/pt200/0020/cocktail.root";
  else if (kDo200MeV && kCentrality == kCent::kCent2040) cocktail_file_HF = "photon_fit/input/pt200/2040/cocktail.root";
  else if (kDo200MeV && kCentrality == kCent::kCent4080) cocktail_file_HF = "photon_fit/input/pt200/4080/cocktail.root";
  else           cocktail_file_HF = "photon_fit/input/cocktail_HF.root";
  file3 = TFile::Open(cocktail_file_HF.c_str(), "READ");
  TH2D h2_charm    = *(dynamic_cast<TH2D*>(file3->Get("Charm")));
  TH2D h2_beauty   = *(dynamic_cast<TH2D*>(file3->Get("Beauty")));

  // adding everything except pion and eta
  TH2D h2_LFrest = *(dynamic_cast<TH2D*>(h2_etaprime.Clone("LFrest")));
  h2_LFrest.Add(&h2_rho);
  h2_LFrest.Add(&h2_omega);
  h2_LFrest.Add(&h2_phi);

  TH2D h2_reso = *(dynamic_cast<TH2D*>(h2_pion.Clone("reso")));
  h2_reso.Add(&h2_eta);
  h2_reso.Add(&h2_LFrest);


  TH2D h2_HF = *(dynamic_cast<TH2D*>(h2_charm.Clone("HF")));
  h2_HF.Add(&h2_beauty);


  rebinner.Rebin2DHistogram(h2_reso);
  rebinner.Rebin2DHistogram(h2_pion);
  rebinner.Rebin2DHistogram(h2_eta);
  rebinner.Rebin2DHistogram(h2_LFrest);

  rebinner.Rebin2DHistogram(h2_HF);

  std::vector<TH1D> v_reso;
  std::vector<TH1D> v_pion;
  std::vector<TH1D> v_eta;
  std::vector<TH1D> v_LFrest;
  std::vector<TH1D> v_HF;
  for(unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
    double value_low  = -1;
    double value_high = -1;
    if (i == binsPtee_forMee.size()-1){ // integrated pT bin
      value_low  = binsPtee_forMee[0];
      value_high = binsPtee_forMee[binsPtee_forMee.size()-1];
    }
    else {
      value_low  = binsPtee_forMee[i];
      value_high = binsPtee_forMee[i+1];
    }

    // extracting LF
    int bin_low  = h2_reso.GetYaxis()->FindBin(value_low);
    int bin_high = h2_reso.GetYaxis()->FindBin(value_high-0.00001);
    TH1D h1        =  *(h2_reso. ProjectionX(Form("reso_bin_%d_%d",   bin_low, bin_high), bin_low, bin_high, "e"));
    TH1D h1_pion   =  *(h2_pion. ProjectionX(Form("pion_bin_%d_%d",   bin_low, bin_high), bin_low, bin_high, "e"));
    TH1D h1_eta    =  *(h2_eta.  ProjectionX(Form("eta_bin_%d_%d",    bin_low, bin_high), bin_low, bin_high, "e"));
    TH1D h1_LFrest = *(h2_LFrest.ProjectionX(Form("LFrest_bin_%d_%d", bin_low, bin_high), bin_low, bin_high, "e"));
    h1.       Scale(1., "width");
    h1_pion.  Scale(1., "width");
    h1_eta.   Scale(1., "width");
    h1_LFrest.Scale(1., "width");
    h1.SetTitle("LF");
    v_reso.emplace_back(h1);
    v_pion.emplace_back(h1_pion);
    v_eta.emplace_back(h1_eta);
    v_LFrest.emplace_back(h1_LFrest);

    // extracting HF
    bin_low  = h2_HF.GetYaxis()->FindBin(value_low);
    bin_high = h2_HF.GetYaxis()->FindBin(value_high-0.00001);
    TH1D h1_central      = *(h2_HF.     ProjectionX(Form("HF_bin_%d_%d",      bin_low, bin_high), bin_low, bin_high, "e"));
    h1_central.Scale(1., "width");
    h1_central.SetTitle("HF");
    v_HF.emplace_back(h1_central);
  }




  TH1D h_RGamma            ("RGamma", ";p_{T} [GeV/c];R_{#gamma} = #frac{1}{1-r}", binsPtee_forMee.size()-1, binsPtee_forMee.data());
  TH1D h_RGammaSysErr("RGammaSysErr", ";p_{T} [GeV/c];R_{#gamma} = #frac{1}{1-r}", binsPtee_forMee.size()-1, binsPtee_forMee.data());
  TH1D h_r            ("r", ";p_{T} [GeV/c];r = #frac{#gamma*_{dir}}{#gamma*_{dir} + #gamma*_{decay}}", binsPtee_forMee.size()-1, binsPtee_forMee.data());
  TH1D h_rSysErr("rSysErr", ";p_{T} [GeV/c];r = #frac{#gamma*_{dir}}{#gamma*_{dir} + #gamma*_{decay}}", binsPtee_forMee.size()-1, binsPtee_forMee.data());


  TCanvas c1("c1", "c1", 800, 800);
  c1.cd();
  c1.SetLogy();
  c1.SetLeftMargin(0.18);


  // CONFIG
  unsigned int standardCut = 0; // for TOFif
  if (DoTOFreq) standardCut = 0;
  else if (kDo200MeV && kCentrality == kCent::kCent0020) standardCut = 0;
  else if (kDo200MeV && kCentrality == kCent::kCent2040) standardCut = 0;
  else if (kDo200MeV && kCentrality == kCent::kCent4080) standardCut = 0;

  unsigned int number_sys_variation_cocktail = 100;
  double sys_error_pion = 0.01; // 3%BR, 4%Para = sqrt(0.03*0.03 + 0.04*0.04)
  double sys_error_eta_low = 0.161;// used conservative upper systematics // 5.8%BR, 0.05%para_upper 0.15%para_lower
  double sys_error_eta_high = 0.05;// used conservative upper systematics // 5.8%BR, 0.05%para_upper 0.15%para_lower

  unsigned int number_sys_variation_charm = 100;
  double sys_error_charm = 0.18;

  std::vector<double> normRegionLow  = {0.};
  // std::vector<double> normRegionHigh = {0.04, 0.06};
  std::vector<double> normRegionHigh = {0.04};
  unsigned int standardNormRegionHigh = 0;

  std::vector<double> fitRegionLow  = {0.14};
  std::vector<double> fitRegionHigh = {0.38};
  unsigned int standardFitRegionLow  = 0;
  unsigned int standardFitRegionHigh = 0;
  // std::vector<double> fitRegionLow  = {0.1, 0.14};
  // std::vector<double> fitRegionHigh = { 0.3, 0.38, 0.46};
  // unsigned int standardFitRegionLow  = 1;
  // unsigned int standardFitRegionHigh = 1;


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
  scale_gaus_charm  .Draw();
  c1.SetLogy(kFALSE);
  c1.SaveAs(Form("photon_fit/003_charm_gaus.pdf"));

  // Reading in 2D data for all cutsettings
  std::vector<std::string> v_cutsettings = {"cut 00", "cut 01", "cut 02", "cut 03", "cut 04",
                                            "cut 05", "cut 06", "cut 07", "cut 08", "cut 09",
                                            "cut 10", "cut 11", "cut 12", "cut 13", "cut 14",
                                            "cut 15", "cut 16", "cut 17", "cut 18", "cut 19"};

  if (DoTOFreq) v_cutsettings = {"cut 00", "cut 01", "cut 02", "cut 03", "cut 04",
                                            "cut 05", "cut 06"};
  else if (kDo200MeV && kCentrality == kCent::kCent0020) v_cutsettings = {"cut 04"};
  else if (kDo200MeV && kCentrality == kCent::kCent2040) v_cutsettings = {"cut 05"};
  else if (kDo200MeV && kCentrality == kCent::kCent4080) v_cutsettings = {"cut 06"};

  std::vector<TH2D> v_data2D;

  std::vector<r_Sys> v_r_Sys_fit_region;
  std::vector<r_Sys> v_r_Sys_norm_region;
  std::vector<r_Sys> v_r_Sys_cocktail;
  std::vector<r_Sys> v_r_Sys_HF;



  // for (unsigned int cut_i = 0; cut_i < v_cutsettings.size(); ++cut_i){
  for (unsigned int cut_i = 0; cut_i < 1; ++cut_i){

    // ###########################################################################
    // Reading signal file
    std::string signal_file;
    // if      (kDo200MeV && kCentrality == kCent::kCent0080) signal_file = "photon_fit/input/pt200/signal_all.root";
    if      (kDo200MeV && kCentrality == kCent::kCent0080) signal_file = "photon_fit/input/pt200_fullMC/0080/signal_all.root";
    else if (kDo200MeV && kCentrality == kCent::kCent0020) signal_file = "photon_fit/input/pt200/0020/PairEff/signal_all.root";
    else if (kDo200MeV && kCentrality == kCent::kCent2040) signal_file = "photon_fit/input/pt200/2040/PairEff/signal_all.root";
    else if (kDo200MeV && kCentrality == kCent::kCent4080) signal_file = "photon_fit/input/pt200/4080/PairEff/signal_all.root";
    else if (DoTOFreq) signal_file = "photon_fit/input/signal_all_TOFreq.root";
    else           signal_file = "photon_fit/input/signal_all.root";
    TFile* file1 = TFile::Open(signal_file.c_str(), "READ");
    if (!file1) { LmHelper::Error(Form("Signal file %s not found", signal_file.c_str())); return 1;}
    TDirectoryFile* dir1 = dynamic_cast<TDirectoryFile*>(file1->Get(v_cutsettings[cut_i].c_str()));
    if (!dir1) { LmHelper::Error(Form("Directory %s not found", v_cutsettings[cut_i].c_str())); return 1;}
    TH2D h2_signal      = *(dynamic_cast<TH2D*>(dir1->Get("hSubSig")));
    file1->Close();
    v_data2D.push_back(h2_signal);

    for (unsigned int i = 0; i < fitRegionLow.size();++i){
      for (unsigned int j  = 0; j < fitRegionHigh.size(); ++j){
        v_r_Sys_fit_region.push_back({h_r, Form("Fit: %2.2f - %2.2f MeV/c^{2}, cut %d", fitRegionLow[i], fitRegionHigh[j], cut_i)});
      }
    }
    if (cut_i == standardCut){
      for (unsigned int i = 0; i < normRegionHigh.size();++i){
        v_r_Sys_norm_region.push_back({h_r, Form("Norm: %2.2f - %2.2f MeV/c^{2}, cut %d", 0., normRegionHigh[i], cut_i)});
      }

      for (unsigned int i = 0; i < number_sys_variation_cocktail;++i){
        v_r_Sys_cocktail.push_back({h_r, Form("cut %d", cut_i)});
      }
      for (unsigned int i = 0; i < number_sys_variation_charm;++i){
        v_r_Sys_HF.push_back({h_r, Form("cut %d", cut_i)});
      }
    }

  }

  for (unsigned int pt_i = 0; pt_i < binsPtee_forMee.size()-1; ++pt_i){

    TH1D h_RGammasPerPtSysErr("hgamma", "", 100., 0.9, 2.);
    h_RGammasPerPtSysErr.SetTitle(";R_{#gamma} = #frac{1}{1-r}");
    TH1D h_rPerPtSysErr("r_perPt", "", 100., -0.1, 1.);
    h_rPerPtSysErr.SetTitle(";r = #frac{#gamma*_{dir}}{#gamma*_{dir} + #gamma*_{decay}}");
    TH1D h_rPerPtSysErr_FittingRegion("r_fitting", "", 110., -0.1, 1.);
    h_rPerPtSysErr_FittingRegion.SetTitle(";r = #frac{#gamma*_{dir}}{#gamma*_{dir} + #gamma*_{decay}}");
    TH1D h_rPerPtSysErr_NormalizationRegion("r_normalization", "", 110., -0.1, 1.);
    h_rPerPtSysErr_NormalizationRegion.SetTitle(";r = #frac{#gamma*_{dir}}{#gamma*_{dir} + #gamma*_{decay}}");
    TH1D h_rPerPtSysErr_CocktailVariation("cocktailVariation", "", 110., -0.1, 1.);
    h_rPerPtSysErr_CocktailVariation.SetTitle(";r = #frac{#gamma*_{dir}}{#gamma*_{dir} + #gamma*_{decay}}");
    TH1D h_rPerPtSysErr_CharmVariation("charmVariation", "", 110., -0.1, 1.);
    h_rPerPtSysErr_CharmVariation.SetTitle(";r = #frac{#gamma*_{dir}}{#gamma*_{dir} + #gamma*_{decay}}");

    double rForCentralValue = -1;
    double rErrorForCentralValue = -1;

    std::cout << "\npt interval = " << binsPtee_forMee[pt_i] << "-" << binsPtee_forMee[pt_i+1] << " GeV/c" << std::endl;
    for (unsigned int cut_i = 0; cut_i < v_data2D.size(); ++cut_i){



      double value_low  = binsPtee_forMee[pt_i];
      double value_high = binsPtee_forMee[pt_i+1];
      int bin_low  = v_data2D[cut_i].GetYaxis()->FindBin(value_low);
      int bin_high = v_data2D[cut_i].GetYaxis()->FindBin(value_high-0.00001);
      TH1D h1 = *(v_data2D[cut_i].ProjectionX(Form("bin_%d_%d", bin_low, bin_high), bin_low, bin_high, "e"));
      if      (kDo200MeV && kCentrality == kCent::kCent0080) h1.Scale(1./86242016, "width");
      else if (kDo200MeV && kCentrality == kCent::kCent0020) h1.Scale(1./21768200, "width");
      else if (kDo200MeV && kCentrality == kCent::kCent2040) h1.Scale(1./21772778, "width");
      else if (kDo200MeV && kCentrality == kCent::kCent4080) h1.Scale(1./43548840, "width");
      else if (DoTOFreq) h1.Scale(1./81030384, "width");
      else           h1.Scale(1./84361792, "width");


      // // Drawing of unscaled histograms
      PlotSignalBeforeFit(h1, v_reso[pt_i], v_pion[pt_i], v_eta[pt_i], v_LFrest[pt_i], v_HF[pt_i], v_photon[pt_i], cut_i, pt_i);

      if(cut_i == standardCut){
        // #########################################################################
        // #########################################################################
        // Variation of pion and eta fraction in cocktail  #########################
        //
        for (unsigned int sys_var_j = 0; sys_var_j < number_sys_variation_cocktail; ++sys_var_j){

          // Get scaling factor according to systematic uncertainty
          double gaus_random_pion;
          double gaus_random_eta;
          if (sys_var_j == 0) {
            gaus_random_pion = 0.;
            gaus_random_eta  = 0.;
          }
          else {
            gaus_random_pion = scale_gaus_pion.GetRandom();
            gaus_random_eta = scale_gaus_eta.GetRandom();
          }
          double scaling_factor_pion = 1. + gaus_random_pion;
          double scaling_factor_eta  = 1. + gaus_random_eta;

          TH1D pionafterscaling    = *(dynamic_cast<TH1D*>(v_pion[pt_i].Clone(Form("%d_%d", pt_i, sys_var_j))));
          TH1D etaafterscaling     = *(dynamic_cast<TH1D*>(v_eta[pt_i].Clone(Form("%d_%d", pt_i, sys_var_j))));

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

        for (unsigned int sys_var_j = 0; sys_var_j < number_sys_variation_charm; ++sys_var_j){

          // Get scaling factor according to systematic uncertainty
          double gaus_random_charm;
          if (sys_var_j == 0) {
            gaus_random_charm = 0.;
          }
          else {
            gaus_random_charm = scale_gaus_charm.GetRandom();
          }
          double scaling_factor_charm = 1. + gaus_random_charm;
          TH1D charmafterscaling    = *(dynamic_cast<TH1D*>(v_HF[pt_i].Clone(Form("charm_%d_%d", pt_i, sys_var_j))));
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
        for (unsigned int normalization_region_i_low = 0; normalization_region_i_low < normRegionHigh.size(); ++normalization_region_i_low){
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


      for (unsigned int fitting_region_i_low = 0; fitting_region_i_low < fitRegionLow.size(); ++fitting_region_i_low){
        for (unsigned int fitting_region_i_high = 0; fitting_region_i_high < fitRegionHigh.size(); ++fitting_region_i_high){
          LmFitter fitter;
          fitter.SetDatahist(&h1);
          fitter.AttachFitTemplateA(&v_reso[pt_i]);
          fitter.AttachFitTemplateB(&v_photon[pt_i]);
          fitter.AttachFitTemplateC(&v_HF[pt_i]);
          fitter.SetTemplateNames("resonances", "Heavy flavour", "Virtual Photon");

          fitter.PrepareFitVirtPhot_Normalization(0., normRegionHigh[standardNormRegionHigh], kTRUE);
          fitter.Process(LmFitter::kThreeTempl_OneNorm_PlusBaseline);
          if (fitting_region_i_low == standardFitRegionLow && fitting_region_i_high == standardFitRegionHigh && cut_i == standardCut) {
            fitter.PrintBestFit(Form("photon_fit/004_norm/norm_bin%d.pdf", pt_i));
            TCanvas c2("c2", "c2", 800, 800);
            c2.cd();
            c2.SetLogy();
            fitter.GetBestTemplateA()->GetYaxis()->SetTitle("#frac{1}{N_{ev}} #frac{dN}{N_{ev}dm_{ee}}");
            fitter.GetBestTemplateA()->GetYaxis()->SetTitleOffset(1.55);

            fitter.GetBestTemplateA()->SetAxisRange(0., 0.7, "X");
            fitter.GetBestTemplateA()->SetAxisRange(1e-4, 10, "Y");
            fitter.GetBestTemplateA()->Draw("hist");
            fitter.GetBestTemplateB()->Draw("hist same");
            fitter.GetDatahist()->Draw("p same");

            TLegend leg(0.5, 0.65, 0.85, 0.85);
            leg.AddEntry(fitter.GetBestTemplateA(), "LF Cocktail", "lpe");
            leg.AddEntry(fitter.GetBestTemplateB(), "Direct Photons", "lpe");
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

          h_rPerPtSysErr_FittingRegion.Fill(r);

          //
          if (fitting_region_i_low == standardFitRegionLow && fitting_region_i_high == standardFitRegionHigh && cut_i == standardCut) {

            double chi2 = fitter.GetBestFitFcn()->GetChisquare();
            double ndf  = fitter.GetBestFitFcn()->GetNDF();
            std::cout << "Chi2 = " << chi2 << std::endl;
            std::cout << "NdF = " << ndf << std::endl;
            rForCentralValue = r;
            rErrorForCentralValue = r_error;

            fitter.PrintBestFit(Form("photon_fit/003_best_fit/best_fit_bin%d.pdf", pt_i));
            TCanvas c2("c2", "c2", 800, 800);
            c2.cd();
            c2.SetLogy();

            TH1D cocktailPreFit  = *(dynamic_cast<TH1D*>(v_reso[pt_i].Clone(Form("cocktail_preFit_bin%d", pt_i))));
            TH1D cocktailPostFit = *(dynamic_cast<TH1D*>(fitter.GetBestTemplateA()->Clone(Form("cocktail_bin%d", pt_i))));
            TH1D photonPostFit   = *(dynamic_cast<TH1D*>(fitter.GetBestTemplateB()->Clone(Form("photon_bin%d",   pt_i))));
            TH1D charmPostFit    = *(dynamic_cast<TH1D*>(fitter.GetBestTemplateC()->Clone(Form("charm_bin%d",    pt_i))));
            TH1D data            = *(dynamic_cast<TH1D*>(fitter.GetDatahist()     ->Clone(Form("data_bin%d",    pt_i))));

            cocktailPostFit.Scale(1.-r);
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

            cocktailPreFit.SetMarkerColor(kOrange+2);
            cocktailPreFit.SetLineWidth(3);
            cocktailPreFit.SetLineStyle(2);
            cocktailPreFit.SetLineColor(kOrange+2);

            data.SetMarkerColor(kAzure-3);
            data.SetLineColor  (kAzure-3);
            data.SetAxisRange(1e-4, 2, "Y");
            data.GetYaxis()->SetTitleOffset(1.55);
            // data.GetYaxis()->SetTitle("#frac{dN^{2}}{N_{ev}dm_{ee}dp_{T,ee}}");
            data.GetYaxis()->SetTitle("#frac{1}{#it{N}_{ev}} #frac{d#it{N}}{d#it{m}_{ee}}");
            // data.GetYaxis()->SetTitle("#frac{1}{#textrm{N_{ev}}} #frac{d#textrm{N}}{N_{ev}d#textrm{m_{ee}}}");
            data.SetAxisRange(0., 0.7, "X");
            data.Draw("p");
            cocktailPostFit.Draw("hist same");
            cocktailPreFit. Draw("hist same");
            photonPostFit.  Draw("hist same");
            charmPostFit.   Draw("hist same");
            sumPostFit.     Draw("hist same");
            sumPreFit.      Draw("hist same");
            data.Draw("p same");

            double pt_min = binsPtee_forMee[pt_i];
            double pt_max = binsPtee_forMee[pt_i+1];

            TLegend leg1(0.6, 0.6, 0.9, 0.85);
            leg1.AddEntry(&data,  "data", "lpe");
            leg1.AddEntry(&sumPostFit,      "Sum after fit, with #gamma", "lpe");
            leg1.AddEntry(&cocktailPostFit, "LF after fit", "lpe");
            leg1.AddEntry(&photonPostFit,   "Direct #gamma after fit", "lpe");
            leg1.AddEntry(&charmPostFit,    "HF Cocktail, fixed", "lpe");
            leg1.AddEntry(&sumPreFit,       "Sum before fit, w/o #gamma", "lpe");
            leg1.AddEntry(&cocktailPreFit,  "LF before fit", "lpe");
            // leg1.AddEntry((TObject*)0, Form("%.2f < #it{p}_{T,ee} < %.2f GeV/#it{c}", pt_min, pt_max), "");
            leg1.AddEntry((TObject*)0, Form("#chi^{2} / ndf = %.2f / %.2f", chi2, ndf), "");
            leg1.AddEntry((TObject*)0, Form("r = %.2f", rForCentralValue), "");
            leg1.SetBorderSize(0);
            leg1.Draw("same");
            data.DrawCopy("axis same");


            TLatex latex;
            latex.SetTextSize(gStyle->GetTitleSize()*0.7);
            latex.SetTextFont(gStyle->GetTitleFont());
            latex.SetTextAlign(12);  //align at top
            latex.DrawLatexNDC(.23,.8,"ALICE work in progress");
            latex.DrawLatexNDC(.23,.76,"Pb-Pb, #sqrt{s_{NN}} = 5.02 TeV");
            if      (kDo200MeV && kCentrality == kCent::kCent0080) latex.DrawLatexNDC(.23,.72,"00-80%, p_{T}>200 MeV/c, |#eta|<0.8");
            else if (kDo200MeV && kCentrality == kCent::kCent0020) latex.DrawLatexNDC(.23,.72,"00-20%, p_{T}>200 MeV/c, |#eta|<0.8");
            else if (kDo200MeV && kCentrality == kCent::kCent2040) latex.DrawLatexNDC(.23,.72,"20-40%, p_{T}>200 MeV/c, |#eta|<0.8");
            else if (kDo200MeV && kCentrality == kCent::kCent4080) latex.DrawLatexNDC(.23,.72,"40-80%, p_{T}>200 MeV/c, |#eta|<0.8");
            else                                                   latex.DrawLatexNDC(.23,.72,"0-80%, p_{T}>400 MeV/c, |#eta|<0.8");
            latex.DrawLatexNDC(.23,.68,Form("%.2f < #it{p}_{T,ee} < %.2f GeV/#it{c}", pt_min, pt_max));
            // latex.DrawLatexNDC(.23,.72,"ALICE work in progress");

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
      } // end of loop lower edge of fitting region

    }

    // Calculating of r and RGamma distribution per pT Bin including their uncertainties
    TCanvas c2("c2", "", 800, 800);
    c2.SetRightMargin(0.05);

    h_rPerPtSysErr_CocktailVariation.  Scale(1. / h_rPerPtSysErr_CocktailVariation.Integral());
    h_rPerPtSysErr_CharmVariation.     Scale(1. / h_rPerPtSysErr_CharmVariation.Integral());
    h_rPerPtSysErr_FittingRegion.      Scale(1. / h_rPerPtSysErr_FittingRegion.Integral());
    h_rPerPtSysErr_NormalizationRegion.Scale(1. / h_rPerPtSysErr_NormalizationRegion.Integral());

    h_rPerPtSysErr_CocktailVariation.  SetLineWidth(2);
    h_rPerPtSysErr_CharmVariation.     SetLineWidth(2);
    h_rPerPtSysErr_FittingRegion.      SetLineWidth(2);
    h_rPerPtSysErr_NormalizationRegion.SetLineWidth(2);

    h_rPerPtSysErr_CocktailVariation.  SetLineColor(kBlack);
    h_rPerPtSysErr_CharmVariation.     SetLineColor(kGreen+2);
    h_rPerPtSysErr_FittingRegion.      SetLineColor(kRed);
    h_rPerPtSysErr_NormalizationRegion.SetLineColor(kBlue);

    h_rPerPtSysErr_CocktailVariation.SetAxisRange(0, 1, "Y");

    h_rPerPtSysErr_CocktailVariation.  Draw("hist");
    h_rPerPtSysErr_CharmVariation.     Draw("hist same");
    h_rPerPtSysErr_FittingRegion.      Draw("hist same");
    h_rPerPtSysErr_NormalizationRegion.Draw("hist same");

    TLegend leg_r_dist(0.5, 0.6, 0.90, 0.8);
    leg_r_dist.SetBorderSize(0);
    leg_r_dist.AddEntry(&h_rPerPtSysErr_CocktailVariation,   "from LF variation",      "l");
    leg_r_dist.AddEntry(&h_rPerPtSysErr_CharmVariation,      "from charm variation",         "l");
    leg_r_dist.AddEntry(&h_rPerPtSysErr_NormalizationRegion, "from normalization variation", "l");
    leg_r_dist.AddEntry(&h_rPerPtSysErr_FittingRegion,       "from fitting variation",       "l");
    leg_r_dist.Draw("same");
    c2.SaveAs(Form("photon_fit/002_plot_r_for_sys_unc/r_for_sys_unc_mass%d.pdf", pt_i));



    c1.cd();
    double rms_fittingRegion = GetRMSofBin(v_r_Sys_fit_region, pt_i);
    double rms_normRegion    = GetRMSofBin(v_r_Sys_norm_region, pt_i);
    double rms_cocktail      = GetRMSofBin(v_r_Sys_cocktail, pt_i);
    double rms_HF            = GetRMSofBin(v_r_Sys_HF, pt_i);
    double rms_sum = TMath::Sqrt(rms_fittingRegion * rms_fittingRegion +
                                 rms_normRegion * rms_normRegion +
                                 rms_cocktail * rms_cocktail +
                                 rms_HF * rms_HF);

    std::cout << "r:                          " << rForCentralValue << std::endl;
    std::cout << "Rel. Unc. norm:     " << 100 * rms_normRegion / rForCentralValue    << " %" << std::endl;
    std::cout << "Rel. Unc. cuts:     " << 100 * rms_fittingRegion / rForCentralValue << " %" << std::endl;
    std::cout << "Rel. Unc. cocktail: " << 100 * rms_cocktail / rForCentralValue      << " %" << std::endl;
    std::cout << "Rel. Unc. HF:       " << 100 * rms_HF / rForCentralValue            << " %" << std::endl;
    std::cout << "Rel. Unc. Sum:      " << 100 * rms_sum / rForCentralValue           << " %" << std::endl;

    double RGammaForCentralValue = 1. / (1. - rForCentralValue) ; // R_gamma
    double RGamma_errorStat = rErrorForCentralValue / ((1-rForCentralValue) * (1-rForCentralValue)); // delta_RGamma = r_error / (1-RGamma)^2
    double RGamma_errorSyst = rms_sum / ((1-rForCentralValue) * (1-rForCentralValue)); // delta_RGamma = r_error / (1-RGamma)^2

    // Setting Content for RGamma as function of pT
    h_RGamma.SetBinContent(h_RGamma.FindBin(binsPtee_forMee[pt_i]), RGammaForCentralValue);
    h_RGamma.SetBinError  (h_RGamma.FindBin(binsPtee_forMee[pt_i]), RGamma_errorStat);
    h_r.SetBinContent(h_r.FindBin(binsPtee_forMee[pt_i]), rForCentralValue);
    h_r.SetBinError  (h_r.FindBin(binsPtee_forMee[pt_i]), rErrorForCentralValue);

    h_RGammaSysErr.SetBinContent(h_RGamma.FindBin(binsPtee_forMee[pt_i]), RGammaForCentralValue);
    h_RGammaSysErr.SetBinError  (h_RGamma.FindBin(binsPtee_forMee[pt_i]), RGamma_errorSyst);
    h_rSysErr.SetBinContent(h_r.FindBin(binsPtee_forMee[pt_i]), rForCentralValue);
    h_rSysErr.SetBinError  (h_r.FindBin(binsPtee_forMee[pt_i]), rms_sum);
  }
  PrintChiSquare(v_r_Sys_fit_region);

  //
  TLine line0(binsPtee_forMee[0], 0., binsPtee_forMee[binsPtee_forMee.size()-1], 0.);
  line0.SetLineWidth(2);

  DrawRFactors(v_r_Sys_fit_region, "photon_fit/005_r_factors/001_r-factors_fitRegion.pdf");
  DrawRFactors(v_r_Sys_norm_region, "photon_fit/005_r_factors/002_r-factors_normRegion.pdf");
  DrawRFactors(v_r_Sys_cocktail, "photon_fit/005_r_factors/003_r-factors_cocktail.pdf");
  DrawRFactors(v_r_Sys_HF, "photon_fit/005_r_factors/004_r-factors_charm.pdf");

  // #########################################################################
  // #########################################################################
  // Plotting of r and RGamma Plot ###########################################
  c1.cd();
  h_RGamma.SetAxisRange(0.8, 2.0, "Y");
  h_RGamma.SetAxisRange(0., binsPtee_forMee[binsPtee_forMee.size()-1]-1e10, "X");
  h_RGamma.SetMarkerSize(2);
  h_RGamma.SetMarkerStyle(20);
  h_RGamma.SetMarkerColor(kRed-3);
  h_RGamma.SetLineColor  (kRed-3);
  h_RGamma.DrawCopy("p");

  h_RGammaSysErr.SetMarkerSize(2);
  h_RGammaSysErr.SetMarkerStyle(20);
  h_RGammaSysErr.SetMarkerColor(kRed-3);
  h_RGammaSysErr.SetLineColor  (kRed-3);
  h_RGammaSysErr.SetFillStyle(0);
  h_RGammaSysErr.DrawCopy("p E2 same");

  TLine line1(binsPtee_forMee[0], 1., binsPtee_forMee[binsPtee_forMee.size()-1], 1.);
  line1.SetLineWidth(2);
  line1.Draw("same");

  TLegend leg(0.2, 0.7, 0.5, 0.85);
  leg.AddEntry(&h_RGamma, "data", "pl");

  TLatex latex;
  latex.SetTextSize(gStyle->GetTitleSize()*0.7);
  latex.SetTextFont(gStyle->GetTitleFont());
  latex.SetTextAlign(12);  //align at top
  latex.DrawLatexNDC(.23,.8,"ALICE work in progress");
  latex.DrawLatexNDC(.23,.76,"Pb-Pb, #sqrt{s_{NN}} = 5.02 TeV");
  if      (kDo200MeV && kCentrality == kCent::kCent0080) latex.DrawLatexNDC(.23,.72,"00-80%, p_{T}>200 MeV/c, |#eta|<0.8");
  else if (kDo200MeV && kCentrality == kCent::kCent0020) latex.DrawLatexNDC(.23,.72,"00-20%, p_{T}>200 MeV/c, |#eta|<0.8");
  else if (kDo200MeV && kCentrality == kCent::kCent2040) latex.DrawLatexNDC(.23,.72,"20-40%, p_{T}>200 MeV/c, |#eta|<0.8");
  else if (kDo200MeV && kCentrality == kCent::kCent4080) latex.DrawLatexNDC(.23,.72,"40-80%, p_{T}>200 MeV/c, |#eta|<0.8");
  else                                                   latex.DrawLatexNDC(.23,.72,"0-80%, p_{T}>400 MeV/c, |#eta|<0.8");
  // latex.DrawLatexNDC(.23,.72,"ALICE work in progress");

  c1.SaveAs("photon_fit/001_RGamma.pdf");

  TF1 f_r_fit("r-fit", "[0]*x+[1]", 0, 10);

  h_r.GetYaxis()->SetTitleOffset(2.1);
  h_r.SetAxisRange(-0.1, 0.5, "Y");
  h_r.SetAxisRange(0., binsPtee_forMee[binsPtee_forMee.size()-1]-1e10, "X");
  h_r.SetMarkerSize(2);
  h_r.SetMarkerStyle(20);
  h_r.SetMarkerColor(kRed-3);
  h_r.SetLineColor  (kRed-3);
  h_r.DrawCopy("p");
  h_r.Fit(&f_r_fit, "0Q");
  std::cout << "\n fit result: " << f_r_fit.GetParameter(0) << "(+-" << f_r_fit.GetParError(0) << ") * x + " << f_r_fit.GetParameter(1) << "(+-" << f_r_fit.GetParError(1) << ")" << std::endl;

  h_rSysErr.SetMarkerSize(2);
  h_rSysErr.SetMarkerStyle(20);
  h_rSysErr.SetMarkerColor(kRed-3);
  h_rSysErr.SetLineColor  (kRed-3);
  h_rSysErr.SetFillStyle(0);
  h_rSysErr.DrawCopy("p E2 same");

  line0.Draw("same");

  TLegend leg_r(0.16, 0.6, 0.45, 0.7);
  leg_r.AddEntry(&h_r, "data", "pl");
  leg_r.AddEntry(&h_rSysErr, "Systematic Uncertainty", "E2");

  latex.DrawLatexNDC(.23,.8,"ALICE work in progress");
  latex.DrawLatexNDC(.23,.76,"Pb-Pb, #sqrt{s_{NN}} = 5.02 TeV");
  if      (kDo200MeV && kCentrality == kCent::kCent0080) latex.DrawLatexNDC(.23,.72,"00-80%, p_{T}>200 MeV/c, |#eta|<0.8");
  else if (kDo200MeV && kCentrality == kCent::kCent0020) latex.DrawLatexNDC(.23,.72,"00-20%, p_{T}>200 MeV/c, |#eta|<0.8");
  else if (kDo200MeV && kCentrality == kCent::kCent2040) latex.DrawLatexNDC(.23,.72,"20-40%, p_{T}>200 MeV/c, |#eta|<0.8");
  else if (kDo200MeV && kCentrality == kCent::kCent4080) latex.DrawLatexNDC(.23,.72,"40-80%, p_{T}>200 MeV/c, |#eta|<0.8");
  else                                                   latex.DrawLatexNDC(.23,.72,"0-80%, p_{T}>400 MeV/c, |#eta|<0.8");

  c1.SaveAs("photon_fit/002_r.pdf");

  TFile* fileOut = TFile::Open("photon_fit/r_output.root", "RECREATE");
  fileOut->cd();
  h_r.Write("r_stat");
  h_rSysErr.Write("r_sys");
  fileOut->Close();
  delete fileOut;

  return 0;
}

double GetChi2TH2(TH2& h1, TH2& h2, double x_min, double x_max, double y_min, double y_max){
  double chi2 = 0;
  int bin_x_min = h1.GetXaxis()->FindBin(x_min);
  int bin_x_max = h1.GetXaxis()->FindBin(x_max-0.001);
  int bin_y_min = h1.GetYaxis()->FindBin(y_min);
  int bin_y_max = h1.GetYaxis()->FindBin(y_max-0.001);

  for (int x_i = bin_x_min; x_i < bin_x_max + 1; ++x_i){
    for (int y_i = bin_y_min; y_i < bin_y_max + 1; ++y_i){
      // std::cout << h1.GetXaxis()->GetBinCenter(x_i) << " " << h1.GetYaxis()->GetBinCenter(y_i) << std::endl;
      // std::cout << h1.GetXaxis()->GetBinCenter(x_i) << std::endl;
      double h1_content = h1.GetBinContent(x_i, y_i);
      double h2_content = h2.GetBinContent(x_i, y_i);
      // double h1_error = h1.GetBinError(x_i, y_i);
      // double h2_error = h2.GetBinError(x_i, y_i);
      if (h1_content == 0 || h2_content == 0) continue;
      chi2 += ((h1_content - h2_content) * (h1_content - h2_content)) / h2_content;
      // chi2 += ((h1_content - h2_content) * (h1_content - h2_content)) / ((h1_error*h1_error)+(h2_error*h2_error));
      // std::cout << "h1 " << h1_content << "    h2 " << h2_content << "   " << ((h1_content - h2_content) * (h1_content - h2_content)) / ((h1_error*h1_error)+(h2_error*h2_error)) << std::endl;
      // std::cout << "h1 " << h1_content << "    h2 " << h2_content << "   " << h1_error << " " << h2_error << "       " <<((h1_content - h2_content) * (h1_content - h2_content)) / ((h1_error*h1_error)+(h2_error*h2_error))<< std::endl;
    }
  }
  return chi2;
}



TH2D *hc,*hb,*hRes;
Double_t HFfunction(Double_t *x, Double_t *par)
{
  Int_t xbin = hc->GetXaxis()->FindBin(x[0]);
  Int_t ybin = hc->GetYaxis()->FindBin(x[1]);

  Double_t val = par[0]*hc->GetBinContent(xbin,ybin) + par[1]*hb->GetBinContent(xbin,ybin) + hRes->GetBinContent(xbin,ybin);
  return val;
}
Double_t x1(0.6);

TPaveText GetTextBox(Double_t x1, Double_t y1, Double_t x2, Double_t y2)
{
  TPaveText T(x1, y1, x2, y2, "brNDC");
  T.SetBorderSize(0);
  T.SetTextSize(0.03);
  T.SetFillColor(0);
  T.SetFillStyle(0);
  T.SetLineColor(kWhite);
  T.SetTextAlign(12);

  return T;
}
int HF_Fit(){

  double meeMin = 1.1;
  double meeMax = 2.7;
  double pteeMin = 0.;
  double pteeMax = 8.;


  binsPtee_forMee.clear();
  binsPtee_forMee.push_back(0.);
  binsPtee_forMee.push_back(1.);
  // binsPtee_forMee.push_back(1.5);
  binsPtee_forMee.push_back(2.);
  binsPtee_forMee.push_back(3.);
  // binsPtee_forMee.push_back(4.);
  binsPtee_forMee.push_back(5.);
  binsPtee_forMee.push_back(8.);

  LmRebinner rebinner;
  rebinner.SetRebinning2D(mee_bin.size()-1, mee_bin.data(), ptee_bin_LookingAtPtee_1100_2900.size()-1, ptee_bin_LookingAtPtee_1100_2900.data());

  std::vector<std::string> v_cutsettings = {"cut 00", "cut 01", "cut 02", "cut 03", "cut 04",
                                            "cut 05", "cut 06", "cut 07", "cut 08", "cut 09",
                                            "cut 10", "cut 11", "cut 12", "cut 13", "cut 14",
                                            "cut 15", "cut 16", "cut 17", "cut 18", "cut 19"};

  unsigned int cut_i = 0;

  std::string centrality = "";


  std::string cocktail_filename = "";
  std::string data_filename = "";

  double nEvents;
  if (kCentrality == kCent0080){
    data_filename =     "HF_Fit/input/pt200/0080/fullMC/signal_combine.root";
    cocktail_filename = "HF_Fit/input/pt200/0080/fullMC/cocktail.root";
    // data_filename =     "HF_Fit/input/pt200/0080/fine/signal_all.root";
    // cocktail_filename = "HF_Fit/input/pt200/0080/fine/cocktail.root";
    centrality = "0080";
    nEvents = 87089808;
    cut_i = 0;
  }
  else if (kCentrality == kCent0020){
    data_filename =     "HF_Fit/input/pt200/0020/PairEff/signal_all.root";
    cocktail_filename = "HF_Fit/input/pt200/0020/cocktail.root";
    centrality = "0020";
    nEvents = 21768200;
    cut_i = 4;
  }
  else if (kCentrality == kCent2040){
    data_filename =     "HF_Fit/input/pt200/2040/PairEff/signal_all.root";
    cocktail_filename = "HF_Fit/input/pt200/2040/cocktail.root";
    centrality = "2040";
    nEvents = 21772778;
    cut_i = 5;
  }
  else if (kCentrality == kCent4080){
    data_filename =     "HF_Fit/input/pt200/4080/PairEff/signal_all.root";
    cocktail_filename = "HF_Fit/input/pt200/4080/cocktail.root";
    centrality = "4080";
    nEvents = 43548840;
    cut_i = 6;
  }
  std::cout << "Centrality: " << centrality << std::endl;
  // std::string data_filename = "HF_Fit/input/pt200/0080/coarse/signal_all.root";
  TFile* file_data = TFile::Open(data_filename.c_str());
  if (!file_data) { LmHelper::Error(Form("Signal file %s not found", data_filename.c_str())); return 1;}
  TDirectoryFile* dir1 = dynamic_cast<TDirectoryFile*>(file_data->Get(v_cutsettings[cut_i].c_str()));
  if (!dir1) { LmHelper::Error(Form("Directory %s not found", v_cutsettings[cut_i].c_str())); return 1;}
  TH2D h2_signal      = *(dynamic_cast<TH2D*>(dir1->Get("hSubSig")));


  // std::string cocktail_filename = "HF_Fit/input/pt200/0080/fine/cocktail.root";
  // std::string cocktail_filename = "HF_Fit/input/pt200/0080/coarse/cocktail.root";
  TFile* file3 = TFile::Open(cocktail_filename.c_str(), "READ");
  TH2D h2_jpsi        = *(dynamic_cast<TH2D*>(file3->Get("Jpsi")));
  TH2D h2_pion     = *(dynamic_cast<TH2D*>(file3->Get("Pion")));
  TH2D h2_eta      = *(dynamic_cast<TH2D*>(file3->Get("Eta")));
  TH2D h2_etaprime = *(dynamic_cast<TH2D*>(file3->Get("EtaPrime")));
  TH2D h2_rho      = *(dynamic_cast<TH2D*>(file3->Get("Rho")));
  TH2D h2_omega    = *(dynamic_cast<TH2D*>(file3->Get("Omega")));
  TH2D h2_phi      = *(dynamic_cast<TH2D*>(file3->Get("Phi")));
  TH2D h2_charm    = *(dynamic_cast<TH2D*>(file3->Get("Charm")));
  TH2D h2_beauty   = *(dynamic_cast<TH2D*>(file3->Get("Beauty")));

  TH2D h2_reso = *(dynamic_cast<TH2D*>(h2_jpsi.Clone("cocktail")));
  h2_reso.Add(&h2_pion);
  h2_reso.Add(&h2_eta);
  h2_reso.Add(&h2_etaprime);
  h2_reso.Add(&h2_rho);
  h2_reso.Add(&h2_omega);
  h2_reso.Add(&h2_phi);
  // h2_reso.Scale(2.);

  std::cout << "Signal: " << h2_signal.GetNbinsX() << " " << h2_signal.GetNbinsY() << std::endl;
  std::cout << "Charm:  " << h2_charm.GetNbinsX() << " " << h2_charm.GetNbinsY() << std::endl;

  // rebinner.Rebin2DHistogram(h2_signal);
  // rebinner.Rebin2DHistogram(h2_charm);
  // rebinner.Rebin2DHistogram(h2_beauty);
  // rebinner.Rebin2DHistogram(h2_jpsi);
  // rebinner.Rebin2DHistogram(h2_reso);


  TCanvas c1("c1", "", 800, 800);
  c1.cd();
  c1.SetLogy();

  // h2_signal.Scale(1. / 86242016, "width");
  // h2_charm.Scale(1., "width");
  // h2_beauty.Scale(1., "width");
  // h2_jpsi.Scale(1., "width");
  // h2_reso.Scale(1., "width");
  double small_delta = 0.00001;
  for(unsigned int pt_i = 0; pt_i < binsPtee_forMee.size()-1; ++pt_i){
    int bin_min_data = h2_signal.GetYaxis()->FindBin(binsPtee_forMee[pt_i]);
    int bin_max_data = h2_signal.GetYaxis()->FindBin(binsPtee_forMee[pt_i + 1] - small_delta);
    TH1D h1_data     = *(h2_signal.ProjectionX(Form("proj_data_%d", pt_i), bin_min_data, bin_max_data, "e"));
    h1_data.Scale(1. / nEvents, "width");

    int bin_min_charm = h2_charm.GetYaxis()->FindBin(binsPtee_forMee[pt_i]);
    int bin_max_charm = h2_charm.GetYaxis()->FindBin(binsPtee_forMee[pt_i + 1] - small_delta);
    TH1D h1_charm     = *(h2_charm.ProjectionX(Form("proj_charm_%d", pt_i), bin_min_charm, bin_max_charm, "e"));
    h1_charm.Scale(1., "width");

    int bin_min_beauty = h2_beauty.GetYaxis()->FindBin(binsPtee_forMee[pt_i]);
    int bin_max_beauty = h2_beauty.GetYaxis()->FindBin(binsPtee_forMee[pt_i + 1] - small_delta);
    TH1D h1_beauty     = *(h2_beauty.ProjectionX(Form("proj_beauty_%d", pt_i), bin_min_beauty, bin_max_beauty, "e"));
    h1_beauty.Scale(1., "width");

    int bin_min_jpsi   = h2_jpsi.GetYaxis()->FindBin(binsPtee_forMee[pt_i]);
    int bin_max_jpsi   = h2_jpsi.GetYaxis()->FindBin(binsPtee_forMee[pt_i + 1] - small_delta);
    TH1D h1_jpsi     = *(h2_jpsi.ProjectionX(Form("proj_beauty_%d", pt_i), bin_min_jpsi, bin_max_jpsi, "e"));
    h1_jpsi.Scale(1., "width");

    int bin_min_reso   = h2_reso.GetYaxis()->FindBin(binsPtee_forMee[pt_i]);
    int bin_max_reso   = h2_reso.GetYaxis()->FindBin(binsPtee_forMee[pt_i + 1] - small_delta);
    TH1D h1_reso     = *(h2_reso.ProjectionX(Form("proj_beauty_%d", pt_i), bin_min_reso, bin_max_reso, "e"));
    h1_reso.Scale(1., "width");

    h1_data.SetMarkerColor(kBlue);
    h1_data.SetLineColor(kBlue);
    h1_data.SetMarkerStyle(20);

    h1_charm.SetLineWidth(2);
    h1_charm.SetLineColor(kMagenta);

    h1_beauty.SetLineWidth(2);
    h1_beauty.SetLineColor(kOrange+2);

    h1_jpsi.SetLineWidth(2);
    h1_jpsi.SetLineColor(kBlue+2);
    h1_reso.SetLineWidth(2);
    h1_reso.SetLineColor(kBlue+2);

    TH1D h1_sum = *(dynamic_cast<TH1D*>(h1_charm.Clone(Form("proj_sum_%d", pt_i))));
    h1_sum.Add(&h1_beauty);
    h1_sum.Add(&h1_reso);
    h1_sum.SetLineWidth(2);
    h1_sum.SetLineColor(kBlack);

    h1_data.Draw("p");
    h1_charm.Draw ("hist c same");
    h1_beauty.Draw("hist c same");
    h1_jpsi.Draw("hist c same");
    h1_reso.Draw("hist c same");
    h1_sum.Draw("hist c same");

    c1.SaveAs(Form("HF_Fit/output/%s/001_spectra/spectrum_%d.pdf", centrality.c_str(), pt_i));
  }


  TH2D h2_cocktail = *(dynamic_cast<TH2D*>(h2_charm. Clone("cocktail")));
       h2_cocktail.Add(&h2_beauty);
       h2_cocktail.Add( &h2_charm);
       h2_cocktail.Add(  &h2_jpsi);
  h2_cocktail.SetAxisRange(1e-5, 1e-1, "Z");
  h2_cocktail.Draw("colz");
  c1.SetLogy(kFALSE);
  c1.SetRightMargin(0.15);
  c1.SetLogz();
  c1.SaveAs("HF_Fit/cocktail.pdf");

  h2_signal.SetAxisRange(1e-5, 1e-1, "Z");
  h2_signal.Draw("colz");
  c1.SaveAs("HF_Fit/data.pdf");

  // fitting
  hRes = &h2_reso;
  // pythia
  TF2 fFunction("func", HFfunction, meeMin, meeMax, pteeMin, pteeMax, 2);
  fFunction.SetParName(0, "s_cc");
  fFunction.SetParName(1, "s_bb");
  fFunction.SetParameter(0, 1.);
  fFunction.SetParameter(1, 1.);
  // fFunction.SetParLimits(0, 0., 2.00000001);
  // fFunction.SetParLimits(1, 0.99999999, 1.00000001);

  hc = &h2_charm;
  hb = &h2_beauty;
  h2_signal.Scale(1. / nEvents);
  h2_signal.Fit(&fFunction,"0MEIR");
  Double_t par0_pythia = fFunction.GetParameter(0);
  Double_t par1_pythia = fFunction.GetParameter(1);
  Double_t parErr0_pythia = fFunction.GetParError(0);
  Double_t parErr1_pythia = fFunction.GetParError(1);
  Double_t chi2_pythia = fFunction.GetChisquare();
  Double_t ndf_pythia = fFunction.GetNDF();
  gMinuit->SetErrorDef(1);
  TGraph *gr1_pythia = static_cast<TGraph*>(gMinuit->Contour(200,0,1));
  gr1_pythia->SetFillColor(38);
  gr1_pythia->SetLineWidth(2);
  gMinuit->SetErrorDef(4);
  TGraph *gr2_pythia = static_cast<TGraph*>(gMinuit->Contour(200,0,1));
  gr2_pythia->SetFillColor(42);
  gr2_pythia->SetLineWidth(2);
  TGraph *grPoint_pythia = new TGraph(1);
  grPoint_pythia->SetPoint(0,par0_pythia,par1_pythia);
  grPoint_pythia->SetMarkerStyle(20);
  grPoint_pythia->SetMarkerColor(kBlack);

  TH2D htmp(h2_charm);
  htmp.SetName("htmp");
  htmp.Scale(par0_pythia);
  htmp.Add(&h2_beauty,par1_pythia);
  TH2D DataOverFit_pythia(h2_signal);
  DataOverFit_pythia.SetName("DataOverFit_pythia");
  DataOverFit_pythia.Divide(&htmp);


  // drawing
    TCanvas c("c","",800,800);
    gPad->SetTopMargin(0.02);
    gPad->SetLeftMargin(0.12);
    gPad->SetRightMargin(0.02);
    // ptee
    TH1D *hcPtee_pythia = static_cast<TH1D*> (h2_charm.ProjectionY("cPtee_pythia",hc->GetXaxis()->FindBin(meeMin),hc->GetXaxis()->FindBin(meeMax-1.e-9)));
    hcPtee_pythia->SetLineWidth(2);
    hcPtee_pythia->SetLineColor(kMagenta);
    hcPtee_pythia->SetMarkerColor(kMagenta);
    hcPtee_pythia->Scale(1.,"width");

    TH1D *hbPtee_pythia = static_cast<TH1D*> (h2_beauty.ProjectionY("bPtee_pythia",hb->GetXaxis()->FindBin(meeMin),hb->GetXaxis()->FindBin(meeMax-1.e-9)));
    hbPtee_pythia->SetLineWidth(2);
    hbPtee_pythia->SetLineColor(kOrange+2);
    hbPtee_pythia->SetMarkerColor(kOrange+2);
    hbPtee_pythia->Scale(1.,"width");

    TH1D *hHFPtee_pythia = static_cast<TH1D*> (hcPtee_pythia->Clone("hHFPtee_pythia"));
    hHFPtee_pythia->Add(hbPtee_pythia);
    hHFPtee_pythia->SetLineColor(kBlack);
    hHFPtee_pythia->SetMarkerColor(kBlack);

    TH1D *hcPtee_scaled_pythia = static_cast<TH1D*> (hcPtee_pythia->Clone("hcPtee_scaled_pythia"));
    hcPtee_scaled_pythia->Scale(par0_pythia);
    hcPtee_pythia ->SetLineStyle(kDashed);

    TH1D *hbPtee_scaled_pythia = static_cast<TH1D*> (hbPtee_pythia->Clone("hbPtee_scaled_pythia"));
    hbPtee_scaled_pythia->Scale(par1_pythia);
    hbPtee_pythia ->SetLineStyle(kDashed);

    TH1D *hHFPtee_scaled_pythia = static_cast<TH1D*> (hcPtee_scaled_pythia->Clone("hHFPtee_scaled_pythia"));
    hHFPtee_scaled_pythia->Add(hbPtee_scaled_pythia);
    hHFPtee_scaled_pythia->SetLineColor(kBlack);
    hHFPtee_scaled_pythia->SetMarkerColor(kBlack);
    hHFPtee_pythia->SetLineStyle(kDashed);

    TH1D *hHFPtee_pythia_comp = static_cast<TH1D*> (hHFPtee_pythia->Clone("hHFPtee_pythia_comp"));
    hHFPtee_pythia_comp->SetLineColor(kOrange+2);
    TH1D *hHFPtee_scaled_pythia_comp = static_cast<TH1D*> (hHFPtee_scaled_pythia->Clone("hHFPtee_scaled_pythia_comp"));
    hHFPtee_scaled_pythia_comp->SetLineColor(kOrange+2);


    TH1D *signalPtee = static_cast<TH1D*> (h2_signal.ProjectionY("signalPtee",h2_signal.GetXaxis()->FindBin(meeMin),h2_signal.GetXaxis()->FindBin(meeMax-1.e-9)));
    signalPtee->GetXaxis()->SetTitle("Ptee");
    signalPtee->SetTitle("");
    signalPtee->SetLineColor(kBlack);
    signalPtee->SetMarkerColor(kBlack);
    signalPtee->Scale(1.,"width");
    signalPtee->SetMarkerStyle(20);
    signalPtee->SetMarkerSize(1.5);
  //  signalPtee->GetYaxis()->SetRangeUser(8.001e-7,8.999e-4);
    signalPtee->GetXaxis()->SetTitleOffset(1.);
    signalPtee->GetYaxis()->SetRangeUser(5.001e-5,1.999e-3);


    TPaveText T_mee = GetTextBox(x1, 0.90, 0.95, 0.95);
    T_mee.AddText(Form("%2.1f < m_{ee} < %2.1f GeV/c^{2}", meeMin,meeMax));


    TH1D *hResPtee = static_cast<TH1D*> (h2_reso.ProjectionY("hResPtee",h2_reso.GetXaxis()->FindBin(meeMin-1.e-10),h2_reso.GetXaxis()->FindBin(meeMax-1.e-10)));
    hResPtee->Scale(1.,"width");
    hResPtee->SetLineWidth(2);
    hResPtee->SetLineColor(kRed);
    TH1D *hSumPtee_pythia = static_cast<TH1D*> (hHFPtee_pythia->Clone("hSumPtee_pythia"));
    TH1D *hSumPtee_scaled_pythia = static_cast<TH1D*> (hHFPtee_scaled_pythia->Clone("hSumPtee_scaled_pythia"));
    // TH1D *hSumPtee_powheg = static_cast<TH1D*> (hHFPtee_powheg->Clone("hSumPtee_powheg"));
    // TH1D *hSumPtee_scaled_powheg = static_cast<TH1D*> (hHFPtee_scaled_powheg->Clone("hSumPtee_scaled_powheg"));
    hSumPtee_pythia       ->Add(hResPtee);
    hSumPtee_scaled_pythia->Add(hResPtee);
    // hSumPtee_powheg       ->Add(hResPtee);
    // hSumPtee_scaled_powheg->Add(hResPtee);

    TLegend leg(x1,0.67,0.95,0.9);
    leg.SetFillColor(0);
    leg.SetFillStyle(0);
    leg.SetBorderSize(0);
    leg.SetTextSize(0.03);
    leg.AddEntry(signalPtee,"data","pl");
    leg.AddEntry(hResPtee,"resonances","l");
    leg.AddEntry(hSumPtee_scaled_pythia,"cocktail sum scaled","l");
    leg.AddEntry(hcPtee_scaled_pythia,"c#bar{c} scaled","l");
    leg.AddEntry(hbPtee_scaled_pythia,"b#bar{b} scaled","l");
    leg.AddEntry(hSumPtee_pythia,"cocktail sum","l");
    leg.AddEntry(hcPtee_pythia,"c#bar{c}","l");
    leg.AddEntry(hbPtee_pythia,"b#bar{b}","l");



    TLegend leg2(x1,0.67,0.95,0.8);
    leg2.SetFillColor(0);
    leg2.SetFillStyle(0);
    leg2.SetBorderSize(0);
    leg2.SetTextSize(0.03);
    leg2.AddEntry(hHFPtee_pythia_comp,"pythia","pl");
    // leg2.AddEntry(hHFPtee_powheg_comp,"powheg","l");
    leg2.AddEntry(hHFPtee_scaled_pythia_comp,"pythia scaled","l");
    // leg2.AddEntry(hHFPtee_scaled_powheg_comp,"powheg scaled","l");

    TH2D *hDrawPtee = new TH2D("hDrawPtee","", 1, 0., 8., 1, 1.001e-5, 2e-2);
    hDrawPtee->GetXaxis()->SetTitle("p_{T,ee} (GeV/c)");
    hDrawPtee->GetYaxis()->SetTitle("dN/dp_{T,ee} (GeV/c)^{-1}");
    hDrawPtee->GetYaxis()->SetTitleOffset(1.5);

    std::string cs = "PbPb";
    std::string syst = "";
    gPad->SetLogy();
    hDrawPtee->Draw();
    hcPtee_pythia->         Draw("hist c same");
    hbPtee_pythia->         Draw("hist c same");
    hcPtee_scaled_pythia->  Draw("hist c same");
    hbPtee_scaled_pythia->  Draw("hist c same");
    hResPtee->              Draw("hist c same");
    hSumPtee_pythia->       Draw("hist c same");
    hSumPtee_scaled_pythia->Draw("hist c same");
    signalPtee->Draw("same");
    leg.Draw("same");
    T_mee.Draw("same");
    c.SaveAs(Form("./HF_Fit/output/%s/002_ptee_spectra/pythia_Ptee_%s.pdf", centrality.c_str(), cs.c_str()));

    hDrawPtee->Draw();
    hHFPtee_pythia_comp->Draw("same");
    // hHFPtee_powheg_comp->Draw("same");
    hHFPtee_scaled_pythia_comp->Draw("same");
    // hHFPtee_scaled_powheg_comp->Draw("same");
    leg2.Draw("same");
    T_mee.Draw("same");
    c.SaveAs(Form("./HF_Fit/output/%s/002_ptee_spectra/modelComparison_ptee_%s.pdf", centrality.c_str(), cs.c_str()));


    TH1D *hcMee_pythia,*hbMee_pythia,*hHFMee_pythia,*signalMee;
    TH1D *hcMee_scaled_pythia,*hbMee_scaled_pythia,*hHFMee_scaled_pythia;
    TH1D *hHFMee_pythia_comp,*hHFMee_scaled_pythia_comp;

    std::vector<double> vPtee = binsPtee_forMee;

    TH2D *hDrawMee = new TH2D("hDrawMee","", 1, 0., 4., 1, 1e-5, 2e1);
    hDrawMee->GetXaxis()->SetTitle("m_{ee} (GeV/c^{2})");
    hDrawMee->GetYaxis()->SetTitle("dN/dm_{ee} (GeV/c^{2})^{-1}");
    hDrawMee->GetYaxis()->SetTitleOffset(1.4);
    for(UInt_t i = 0; i < vPtee.size()-1; ++i){
      hcMee_pythia  = static_cast<TH1D*> (h2_charm.ProjectionX("cMee_pythia",h2_charm.GetYaxis()->FindBin(vPtee.at(i)),h2_charm.GetYaxis()->FindBin(vPtee.at(i+1)-1.e-10)));
      hcMee_pythia->SetLineWidth(2);
      hcMee_pythia->SetLineColor(kMagenta);
      hcMee_pythia->SetMarkerColor(kMagenta);
      hcMee_pythia ->Scale(1.,"width");

      hbMee_pythia  = static_cast<TH1D*> (h2_beauty.ProjectionX("bMee_pythia",h2_beauty.GetYaxis()->FindBin(vPtee.at(i)),h2_beauty.GetYaxis()->FindBin(vPtee.at(i+1)-1.e-10)));
      hbMee_pythia->SetLineWidth(2);
      hbMee_pythia->SetLineColor(kOrange+2);
      hbMee_pythia->SetMarkerColor(kOrange+2);
      hbMee_pythia ->Scale(1.,"width");

      hHFMee_pythia = static_cast<TH1D*> (hcMee_pythia->Clone("hHFMee_pythia"));
      hHFMee_pythia->Add(hbMee_pythia);
      hHFMee_pythia->SetLineColor(kBlack);
      hHFMee_pythia->SetMarkerColor(kBlack);

      hcMee_scaled_pythia = static_cast<TH1D*> (hcMee_pythia->Clone("hcMee_scaled_pythia"));
      hcMee_scaled_pythia->Scale(par0_pythia);
      hcMee_scaled_pythia->SetLineStyle(kSolid);
      hcMee_pythia->SetLineStyle(kDashed);

      hbMee_scaled_pythia = static_cast<TH1D*> (hbMee_pythia->Clone("hbMee_scaled_pythia"));
      hbMee_scaled_pythia->Scale(par1_pythia);
      hbMee_scaled_pythia->SetLineStyle(kSolid);
      hbMee_pythia->SetLineStyle(kDashed);

      hHFMee_scaled_pythia = static_cast<TH1D*> (hcMee_scaled_pythia->Clone("hHFMee_scaled_pythia"));
      hHFMee_scaled_pythia->Add(hbMee_scaled_pythia);
      hHFMee_scaled_pythia->SetLineColor(kBlack);
      hHFMee_scaled_pythia->SetMarkerColor(kBlack);
      hHFMee_scaled_pythia->SetLineStyle(kSolid);
      hHFMee_pythia->SetLineStyle(kDashed);

      hHFMee_pythia_comp = static_cast<TH1D*> (hHFMee_pythia->Clone("hHFMee_pythia_comp"));
      hHFMee_pythia_comp->SetLineColor(kOrange+2);
      hHFMee_scaled_pythia_comp = static_cast<TH1D*> (hHFMee_scaled_pythia->Clone("hHFMee_scaled_pythia_comp"));
      hHFMee_scaled_pythia_comp->SetLineColor(kOrange+2);

      signalMee  = static_cast<TH1D*> (h2_signal.ProjectionX("signalMee",h2_signal.GetYaxis()->FindBin(vPtee.at(i)),h2_signal.GetYaxis()->FindBin(vPtee.at(i+1)-1.e-10)));
      signalMee->GetXaxis()->SetTitle("Mee");
      signalMee->SetTitle("");
      signalMee->SetLineColor(kBlack);
      signalMee->SetMarkerColor(kBlack);
      signalMee->Scale(1.,"width");
      signalMee->SetMarkerStyle(20);
      signalMee->SetMarkerSize(1.5);
  //    signalMee ->GetYaxis()->SetRangeUser(8.001e-7,8.999e-4);
      signalMee->GetXaxis()->SetTitleOffset(1);
      // signalMee->GetYaxis()->SetRangeUser(1e-5, 1e-1);

      TPaveText T_ptee = GetTextBox(x1, 0.90, 0.95, 0.95);
      T_ptee.AddText(Form("%2.1f < p_{T}^{ee} < %2.1f GeV/c", vPtee.at(i),vPtee.at(i+1)));

      TH1D *hResMee = static_cast<TH1D*> (h2_reso.ProjectionX("hResMee",h2_reso.GetYaxis()->FindBin(vPtee.at(i)),h2_reso.GetYaxis()->FindBin(vPtee.at(i+1)-1.e-10)));
      hResMee->Scale(1.,"width");
      hResMee->SetLineWidth(2);
      hResMee->SetLineColor(kRed);
      TH1D *hSumMee_pythia = static_cast<TH1D*> (hHFMee_pythia->Clone("hSumMee_pythia"));
      TH1D *hSumMee_scaled_pythia = static_cast<TH1D*> (hHFMee_scaled_pythia->Clone("hSumMee_scaled_pythia"));
      hSumMee_pythia       ->Add(hResMee);
      hSumMee_scaled_pythia->Add(hResMee);

      gPad->SetLogy();
      hDrawMee->Draw();
      hcMee_pythia->Draw       ("hist c same");
      hbMee_pythia->Draw       ("hist c same");
      hcMee_scaled_pythia->Draw("hist c same");
      hbMee_scaled_pythia->Draw("hist c same");
      hResMee->Draw            ("hist c same");
      hSumMee_pythia->Draw     ("hist c same");
      hSumMee_scaled_pythia->Draw("hist c same");
      signalMee->Draw("same");
      leg.Draw("same");
      T_ptee.Draw("same");
      c.SaveAs(Form("./HF_Fit/output/%s/005_mass_spectra/pythia_mee_%s%d.pdf", centrality.c_str(), cs.c_str(), i));


      hDrawMee->Draw();
      hHFMee_pythia_comp->Draw("same");
      hHFMee_scaled_pythia_comp->Draw("same");
      leg2.Draw("same");
      T_ptee.Draw("same");
      c.SaveAs(Form("./HF_Fit/output/%s/005_mass_spectra/modelComparison_mee_%s%d.pdf", centrality.c_str(), cs.c_str(), i));

    }





    Double_t x(0.),y(0.);
    for(Int_t i = 0; i < gr1_pythia->GetN(); ++i){

      gr1_pythia->GetPoint(i,x,y);
      gr1_pythia->SetPoint(i,x,y);
      gr2_pythia->GetPoint(i,x,y);
      gr2_pythia->SetPoint(i,x,y);
      // gr1_powheg->GetPoint(i,x,y);
      // gr1_powheg->SetPoint(i,x,y);
      // gr2_powheg->GetPoint(i,x,y);
      // gr2_powheg->SetPoint(i,x,y);

    }
    grPoint_pythia->GetPoint(0,x,y);
    grPoint_pythia->SetPoint(0,x,y);
    // grPoint_powheg->GetPoint(0,x,y);
    // grPoint_powheg->SetPoint(0,x,y);
    // Double_t ndf = fFunction.GetNDF();

    hc = static_cast<TH2D*> (h2_charm .Clone("charmPythia"));
    hb = static_cast<TH2D*> (h2_beauty.Clone("beautyPythia"));
    int bins_x = 250;
    int bins_y = 250;
    TH2D *hTest_pythia = new TH2D("hTest_pythia","",bins_x,0.0,1.5,bins_y,0.0,1.5);
    for(Int_t ix = 1; ix <= bins_x; ++ix){
      for(Int_t iy = 1; iy <= bins_y; ++iy){
        fFunction.SetParameter(0,hTest_pythia->GetXaxis()->GetBinWidth(ix) * ix);
        fFunction.SetParameter(1,hTest_pythia->GetYaxis()->GetBinWidth(iy) * iy);
        Double_t chi = h2_signal.Chisquare(&fFunction,"R");
        hTest_pythia->SetBinContent(ix,iy,chi/1.);
      }
    }

    hTest_pythia->GetXaxis()->SetTitle("scaling_{c#bar{c}} (mb)");
    hTest_pythia->GetYaxis()->SetTitle("scaling_{b#bar{b}} (mb)");
    hTest_pythia->GetYaxis()->SetTitleOffset(1.2);
    hTest_pythia->GetZaxis()->SetTitle("#chi^{2}");
    hTest_pythia->GetZaxis()->SetRangeUser(chi2_pythia*0.9,chi2_pythia * 1.5);
    // hTest_pythia->GetZaxis()->SetRangeUser(80,130.);

    TPaveText T_pythia = GetTextBox(0.35, 0.72, 0.90, 0.86);

    T_pythia.AddText(Form("scaling_{c#bar{c}} = %5.3f #pm %5.3f (stat.)", par0_pythia,parErr0_pythia));
    T_pythia.AddText(Form("scaling_{b#bar{b}} = %5.3f #pm %5.3f (stat.)", par1_pythia,parErr1_pythia));
    // T_pythia.AddText(Form("#sigma_{c#bar{c}} = %5.3f #pm %5.3f (stat.) #pm %5.3f (sys.) mb", par0_pythia*sigma_ccbar,parErr0_pythia*sigma_ccbar,(par0_pythia-par0_pythia_low)*sigma_ccbar));
    // T_pythia.AddText(Form("#sigma_{b#bar{b}} = %5.3f #pm %5.3f (stat.) #pm %5.3f (sys.) mb", par1_pythia*sigma_bbbar,parErr1_pythia*sigma_bbbar,(par1_pythia-par1_pythia_low)*sigma_bbbar));
    T_pythia.AddText(Form("#chi^{2} = %5.3f  ndf = %3.0f", chi2_pythia,ndf_pythia));
    T_pythia.AddText(Form("#chi^{2}/ndf = % 5.3f", chi2_pythia/ndf_pythia));

    std::cout << Form(">>> Fit Results %s",cs.c_str()) << std::endl;
    std::cout << ">>> Pythia" << std::endl;
    std::cout << ">>> charm: " << par0_pythia << "+-" << parErr0_pythia << "(stat)"  << std::endl;
    std::cout << ">>> beauty: " << par1_pythia << "+-" << parErr1_pythia << "(stat)" << std::endl;


    gPad->SetTopMargin(0.10);
    gPad->SetLeftMargin(0.10);
    gPad->SetRightMargin(0.14);

    gr2_pythia->SetName("gr2_pythia");
    gr1_pythia->SetName("gr1_pythia");
    grPoint_pythia->SetName("grPoint_pythia");

    gPad->SetLogy(0);
    gPad->SetLogz(0);
    hTest_pythia->Draw("colz");
    gr2_pythia->Draw("l");
    gr1_pythia->Draw("l");
    grPoint_pythia->Draw("p");
    T_pythia .Draw("same");
    c.SaveAs(Form("./HF_Fit/output/%s/004_chi2/gr_pythia.pdf", centrality.c_str()));
    c.SaveAs(Form("./HF_Fit/output/%s/004_chi2/gr_pythia.root", centrality.c_str()));

  return 0;
}
