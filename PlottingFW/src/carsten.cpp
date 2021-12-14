#include <iostream>

#include "LmQA.h"
#include "TLegend.h"
#include "carsten.h"
#include "TSystem.h"

void Init();
void Analyse();
int QA();


int main(int argc, char* argv[]){
  gErrorIgnoreLevel = kWarning;
  gStyle->SetNumberContours(255);
  if (argc == 2){
    if (std::string(argv[1]) == "QA"){
      QA();
    }
    if (std::string(argv[1]) == "Analysis"){
      Init();
      Analyse();    }
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

  // plotting
  LmBaseSignal::SetInputLabelZ("#it{#phi}_{V}","rad", "PhiV");

  // Set binning exactly in this way that the binning is always as coarse as needed! This
  // is needed to decrease fluctuations in the geometric and hybrid backgrounds
  if (kLookAtMass == kTRUE){
    mee_bins  = mee_bin_LookingAtMee;
    if (kLookIntegrated == kTRUE){
      ptee_bins.push_back(ptee_bin_LookingAtMee.front());
      ptee_bins.push_back(ptee_bin_LookingAtMee.back());

      binsPtee_forMee.push_back(ptee_bins.front());
      binsPtee_forMee.push_back(ptee_bins.back());
      binsMee_forPtee.push_back( mee_bins.front());
      binsMee_forPtee.push_back( mee_bins.back());
    }
    else if (kLookIntegrated == kFALSE){
      ptee_bins = ptee_bin_LookingAtMee;
      binsMee_forPtee.push_back(mee_bins.front());
      binsMee_forPtee.push_back(mee_bins.back());
      for (unsigned int i = 0; i < ptee_bins.size(); ++i){
        binsPtee_forMee.push_back(ptee_bins[i]);
      }
    }
  }
  else if (kLookAtMass == kFALSE){
    ptee_bins = ptee_bin_LookingAtPtee;
    if (kLookIntegrated == kTRUE){
      mee_bins.push_back(mee_bin_LookingAtPtee.front());
      mee_bins.push_back(mee_bin_LookingAtPtee.back());

      binsPtee_forMee.push_back(ptee_bins.front());
      binsPtee_forMee.push_back(ptee_bins.back());
      binsMee_forPtee.push_back( mee_bins.front());
      binsMee_forPtee.push_back( mee_bins.back());
    }
    else if (kLookIntegrated == kFALSE){
      mee_bins = mee_bin_LookingAtPtee;
      binsPtee_forMee.push_back(ptee_bins.front());
      binsPtee_forMee.push_back(ptee_bins.back());
      for (unsigned int i = 0; i < mee_bins.size(); ++i){
        binsMee_forPtee.push_back(mee_bins[i]);
      }
    }
  }

  for (unsigned int i = 0; i < mee_bins.size(); ++i) {
    std::cout << "mee bins: " << mee_bins[i] << std::endl;
  }
  for (unsigned int i = 0; i < ptee_bins.size(); ++i) {
    std::cout << "ptee bins: " << ptee_bins[i] << std::endl;
  }
  for (unsigned int i = 0; i < binsMee_forPtee.size(); ++i) {
    std::cout << "Mee projection bins: " << binsMee_forPtee[i] << std::endl;
  }
  for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i) {
    std::cout << "Pt projection bins: " << binsPtee_forMee[i] << std::endl;
  }

  for (int ib=0; ib<=n_mee_bin_systematic; ++ib)  binsMee_forPtee_sys.push_back(mee_bin_systematic[ib]);
  for (int ib=0; ib<=n_ptee_bin_systematic; ++ib) binsPtee_forMee_sys.push_back(ptee_bin_systematic[ib]);
}

void Analyse(){

  // automatic settings
  TString sOptCent = centrality;
  TString sOptPt;
  if (kDoPt400==kTRUE)  sOptPt  ="pt400";
  else sOptPt  = "pt200";


  filename2D_sys = Form("spectra2D_sys_%s_%s.root",sOptCent.Data(),sOptPt.Data());
  filename2D_ana = Form("spectra2D_ana_%s_%s.root",sOptCent.Data(),sOptPt.Data());
  extpath_sys    = TString("./input/data_2Dsignals/"+filename2D_sys);
  extpath_ana    = TString("./input/data_2Dsignals/"+filename2D_ana);


  std::cout << " ______ CONFIGURATION ______ " << std::endl;
  std::cout << " centrality   =   " << sOptCent.Data() << std::endl;
  std::cout << " pt-cut       =   " << sOptPt.Data() << std::endl;
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
  // LmManager* mgr_low = new LmManager(Form("Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV:./input/data_LMEEoutput/LMEEoutput_903905.root:caklein_LMEEPbPb_out2:kPbPb2015_Pt400_tightTOFreq_semi:TOFreq:./input/paireff/pairefficiency_semi_pt400_16x.root:NGenPairs_pt400_8000:NRecPairs_hEff_Ele_TOFreq_pt400_8000"));
  // mgr_low->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
  // LmSignal* refSig = ProcessOneInput(mgr_low);



  std::cout << "Postprocess input handlers" << std::endl;
  // postprocess analysis binning
  han_analysis->Process(LmHandler::kCompare); // make projections of all spectra
  han_analysis->SetPlotRangeRatio(0.7, 2.1);
  han_analysis->SetDoRatio(kDoRatio, 0.3, kFALSE);

  han_systematic->Process(LmHandler::kCompare); // make projections of all spectra
  han_systematic->SetCompareSignalsToAverage();


  // LmSignal* sig5_SysWeightedAv = han_analysis->GetLmSignalI(5); // When only using TOFreq
  LmSignal* sig5_SysWeightedAv = han_analysis->GetLmSignalI(0); // When only using TOFif

  if (kDoSystematics) {
    // sys weighted average
    han_systematic->Process(LmHandler::kSystematic_Average);
    // han_systematic->Process(LmHandler::kSystematic_WeightedAverage);

    sig5_SysWeightedAv->SetSymmetricRelSystematics(han_systematic->GetRelSystematics());
    sig5_SysWeightedAv->Process(LmSignal::kSystematic);


    TCanvas c1("c1", "c1", 1200, 1200);
    TH2D* sys_unc = dynamic_cast<TH2D*>(han_systematic->GetRelSystematics()->Clone("clone"));
    std::cout << "Systematic: " << sys_unc->GetBinContent(1,1) << std::endl;
    std::cout << "Systematic: " << sys_unc->GetBinContent(2,1) << std::endl;
    std::cout << "Systematic: " << sys_unc->GetBinContent(3,1) << std::endl;
    std::cout << "Systematic: " << sys_unc->GetBinContent(4,1) << std::endl;
    std::cout << "Systematic: " << sys_unc->GetBinContent(5,1) << std::endl;
    c1.SetRightMargin(0.2);
    sys_unc->DrawCopy("colz text");
    c1.SaveAs("SysUnc.png");
  }


    // Print without Cocktail
  // han_analysis->SetPlotRangeY(1e-4, 2e2);
  han_analysis->SetPlotRangeY(5e-3, 1e1);
  // han_analysis->SetPlotRangeY(1e-4, 10);
  han_systematic->SetPlotRangeY(1e-4, 10);
  // han_analysis->SetPlotRangeY(3e-1, 10);

  for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj){
    han_analysis->PrintCompareSig_Mee(iProj, printLegend, Form("+_ana_%s_%s",sOptCent.Data(),sOptPt.Data()), 2, 20);
    // han_systematic->PrintCompareSig_Mee(iProj, printLegend, Form("+_sys_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 2, 20);
    // han_analysis->PrintCompareSigBkg_Mee(iProj, printLegend, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 2, 20);
    // han_analysis->PrintCompareSoverB_Mee(iProj, printLegend, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 2, 20);
    // han_analysis->PrintCompare(LmSignal::kSignif, iProj, LmBaseSignal::kProjOnMee, Form("signif_bin_%d.pdf", iProj), kTRUE, kFALSE); // to plot signif linear
    // han_analysis->PrintCompareSignif_Mee(iProj, printLegend, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 2, 20);
    // han_analysis->PrintCompareRfactor_Mee(iProj, printLegend, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 0.85, 1.2);

    // han_analysis->PrintCompare(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, iProj, LmBaseSignal::kProjOnMee, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), true, true);
    // han_analysis->PrintCompare(LmSignal::kUnlike+LmSignal::kBkg, iProj, LmBaseSignal::kProjOnMee, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), true, true);
    // han_analysis->PrintCorrelation(LmSignal::kSignif, LmSignal::kSoverB, iProj, LmBaseSignal::kProjOnMee, Form("xbin%d_ybin%d"), optional Bool_t printLegend, optional Bool_t separatePlots, optional TCanvas *can)
  }
  for(UInt_t iProj = 0; iProj < binsMee_forPtee.size(); ++iProj){
    // han_analysis->PrintCompareSig_Ptee(iProj, printLegend, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 2, 20);
  }


  // Write File with histograms:
  TFile* file_out = TFile::Open("test.root", "RECREATE");
  han_analysis->Write2DHist(LmSignal::kSubSig);
  file_out->Close();
  delete file_out;


  // compare results
  LmHandler* han_signal = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  if (kLookAtMass == kFALSE){
    han_signal->SetBinningPtee(0,&ptee_bin_LookingAtPtee_0_140);
    han_signal->SetBinningPtee(1,&ptee_bin_LookingAtPtee_140_740);
    han_signal->SetBinningPtee(2,&ptee_bin_LookingAtPtee_740_1100);
    han_signal->SetBinningPtee(3,&ptee_bin_LookingAtPtee_1100_2900);
    han_signal->SetBinningPtee(4,&ptee_bin_LookingAtPtee_2900_3300);
    han_signal->SetBinningPtee(5,&ptee_bin_LookingAtPtee_3300_5000);

  }
  // std::vector<Double_t> binsPt4({0.00,0.40,0.80,1.20,1.60,2.00,3.00,4.00,5.00/*,6.50,7.00,8.00,10.0*/});

  han_signal->SetName("han_signal");
  han_signal->SetPlotRangeRatio(0.1, 2.0);
  han_signal->SetDoRatio(kDoRatio, 0.3);
  han_signal->AttachSignal(*sig5_SysWeightedAv, "data");
  han_signal->Process(LmHandler::kCompare);

  // Add Cocktail
  LmCocktail* cockt00 = 0x0;
  if (kDoCocktail) {
    cockt00 = ProcessCocktail();

    // Add cocktail to old handler
    han_signal->SetCocktail(cockt00); // attach complete cocktail to handler. call cockt00->Process() before!
    han_signal->SetDivideOption("0");
    han_signal->SetDrawStyleCocktail("hist c"); // default is "hist"
    if (kDoCocktailOnly)
    han_signal->Process(LmHandler::kCocktailOnly); // create projections of cocktail spectra in the projection binning of the handler. they are stored in each LmCocktailPart.
    else
    han_signal->Process(LmHandler::kCocktail);

  }


  // Print with included Cocktail
  han_signal->SetPlotRangeY(5e-5, 10);
  if (kLookAtMass == kTRUE){
    for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj){
      // cockt00->PrintCocktail_Mee(iProj, Form("cocktail_bin%d.pdf", iProj));
      // han_signal->PrintCompareSig_Mee(iProj, printLegend, Form("+_ana_cocktail_%s_%s",sOptCent.Data(),sOptPt.Data()), 2, 20);
      // han_signal->PrintCompare(LmSignal::kSubSig, iProj, printLegend, "+_ana_cocktail", kTRUE, kTRUE, kFALSE, kTRUE);
      // han_signal->PrintCompare(LmSignal::kSubSig, iProj, printLegend, "+_ana_cocktail", kTRUE, kTRUE, kFALSE);
    }
  }

  // Pair pT histograms
  han_signal->ResetPlotRangeY();
  if (kLookAtMass == kFALSE){
    for(UInt_t iProj = 0; iProj < binsMee_forPtee.size(); ++iProj){
       han_signal->PrintCompareSig_Ptee(iProj, printLegend, Form("+_ana_cocktail_%s_%s",sOptCent.Data(),sOptPt.Data()));
    }
  }

  ///////////////////////////////
    // // RFACTOR PT WISE
    // TCanvas c1;
    // // std::vector<TH1D*> vProjX = han_analysis->CollectProjections(LmSignal::kRfactor, 5, LmBaseSignal::kProjOnMee);
    // // std::vector<TH1D*> vProjX = han_analysis->CollectProjections(LmSignal::kRfactor, 5, LmBaseSignal::kProjOnPtee);
    // std::vector<TH1D*> vProjX;
    // vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(0, LmSignal::kProjOnMee)->GetDatahist());
    // vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(1, LmSignal::kProjOnMee)->GetDatahist());
    // vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(2, LmSignal::kProjOnMee)->GetDatahist());
    // // vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(3, LmSignal::kProjOnMee)->GetDatahist());
    // // vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(4, LmSignal::kProjOnMee)->GetDatahist());
    // // vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(5, LmSignal::kProjOnMee)->GetDatahist());
    // TH1D* h_axis = new TH1D("r factor", "r factor", 1, 0, 3);
    // h_axis->SetAxisRange(0.85, 1.1, "Y");
    // h_axis->SetTitle("R-Factor;m_{ee} [GeV/c^{2}];R-Factor");
    // h_axis->Draw();
    //
    // for (unsigned int i = 0; i < vProjX.size(); ++i){
    //   vProjX.at(i)->SetMarkerStyle(20);
    //   vProjX.at(i)->SetMarkerColor(LmHelper::GetUniformColor(i, vProjX.size()));
    //   vProjX.at(i)->SetLineColor(LmHelper::GetUniformColor(i, vProjX.size()));
    //   vProjX.at(i)->Draw("same p");
    // }
    //
    // TLegend leg(0.5,0.15,0.9,0.4);
    // leg.AddEntry(vProjX.at(0), "0 < p_{T,ee} < 1 GeV/c", "lpe");
    // leg.AddEntry(vProjX.at(1), "1 < p_{T,ee} < 2 GeV/c", "lpe");
    // leg.AddEntry(vProjX.at(2), "2 < p_{T,ee} < 4 GeV/c", "lpe");
    // // leg.AddEntry(vProjX.at(2), "2 < p_{Tee} < 3 GeV/c", "lpe");
    // // leg.AddEntry(vProjX.at(3), "3 < p_{Tee} < 4 GeV/c", "lpe");
    // // leg.AddEntry(vProjX.at(4), "4 < p_{Tee} < 5 GeV/c", "lpe");
    // // leg.AddEntry(vProjX.at(3), "0 < p_{Tee} < 4 GeV/c", "lpe");
    // leg.DrawClone("same");
    //
    //
    // std::cout << vProjX.size() << std::endl;
    // // vProjX.at(3)->Draw("same");
    // c1.SaveAs("r-factor.pdf");
  ///////////////////////////////////////////////



}

int QA(){
  std::cout << "Processing QA()" << std::endl;
  LmQA qa(const_cast<char*>(cconfig[0].Data()));
  qa.SetColorPalette(57);
  qa.PrintCentrality("QAplots/Event_centrality.png");
  qa.PrintEPTPC("QAplots/Event_epTPC.png");
  // qa.PrintEPV0AC("QAplots/epV0AC.png");
  // qa.PrintEPV0ACvsEPTPC("QAplots/epV0AC_epTPC.png");

  // qa.PrintPtPos("QAplots/PtPos.png");
  // qa.PrintPtNeg("QAplots/PtNeg.png");
  // qa.PrintPtAll("QAplots/Tracking_PtAll.png");
  qa.PrintPtCompare("QAplots/Tracking_PtCompare.png");

  // qa.PrintEtaPos("QAplots/EtaPos.png");
  // qa.PrintEtaNeg("QAplots/EtaNeg.png");
  // qa.PrintEtaAll("QAplots/EtaAll.png");
  qa.PrintEtaCompare("QAplots/Tracking_EtaCompare.png");

  // qa.PrintPhiPos("QAplots/PhiPos.png");
  // qa.PrintPhiNeg("QAplots/PhiNeg.png");
  // qa.PrintPhiAll("QAplots/PhiAll.png");
  qa.PrintPhiCompare("QAplots/Tracking_PhiCompare.png");

  // qa.PrintEtaPhiPos("QAplots/Tracking_EtaPhiPos.png");
  // qa.PrintEtaPhiNeg("QAplots/Tracking_EtaPhiNeg.png");
  // qa.PrintEtaPhiAll("QAplots/Tracking_EtaPhiAll.png");
  // qa.PrintEtaPhiAll("QAplots/Tracking_EtaPhiAll.png");

  // qa.PrintITSnClsPos("QAplots/ITSnClsPos.png");
  // qa.PrintITSnClsNeg("QAplots/ITSnClsNeg.png");
  // qa.PrintITSnClsAll("QAplots/ITSnClsAll.png");
  qa.PrintITSnClsCompare("QAplots/ITSnClsCompare.png");

  // qa.PrintTPCnClsPos("QAplots/TPCnClsPos.png");
  // qa.PrintTPCnClsNeg("QAplots/TPCnClsNeg.png");
  // qa.PrintTPCnClsAll("QAplots/TPCnClsAll.png");
  qa.PrintTPCnClsCompare("QAplots/TPCnClsCompare.png");

  // qa.PrintITSChi2Pos("QAplots/ITSChi2Pos.png");
  // qa.PrintITSChi2Neg("QAplots/ITSChi2Neg.png");
  // qa.PrintITSChi2All("QAplots/ITSChi2All.png");
  qa.PrintITSChi2Compare("QAplots/ITSChi2Compare.png");

  // qa.PrintTPCChi2Pos("QAplots/TPCChi2Pos.png");
  // qa.PrintTPCChi2Neg("QAplots/TPCChi2Neg.png");
  // qa.PrintTPCChi2All("QAplots/TPCChi2All.png");
  qa.PrintTPCChi2Compare("QAplots/TPCChi2Compare.png");

  // qa.PrintTPCrowsOverFindablePos("QAplots/TPCCrossedRowsOverFindablePos.png");
  // qa.PrintTPCrowsOverFindableNeg("QAplots/TPCCrossedRowsOverFindableNeg.png");
  // qa.PrintTPCrowsOverFindableAll("QAplots/TPCCrossedRowsOverFindableAll.png");
  qa.PrintTPCrowsOverFindableCompare("QAplots/Tracking_TPCCrossedRowsOverFindableCompare.png");

  // qa.PrintTPCCrossedRowsPos("QAplots/TPCCrossedRowsPos.png");
  // qa.PrintTPCCrossedRowsNeg("QAplots/TPCCrossedRowsNeg.png");
  // qa.PrintTPCCrossedRowsAll("QAplots/TPCCrossedRowsAll.png");
  qa.PrintTPCCrossedRowsCompare("QAplots/Tracking_TPCCrossedRowsCompare.png");

  // qa.PrintZVertexPos("QAplots/ZVertexPos.png");
  // qa.PrintZVertexNeg("QAplots/ZVertexNeg.png");
  // qa.PrintZVertexAll("QAplots/ZVertexAll.png");
  qa.PrintZVertexCompare("QAplots/Tracking_ZVertexCompare.png");

  // qa.PrintXYVertexPos("QAplots/XYVertexPos.png");
  // qa.PrintXYVertexNeg("QAplots/XYVertexNeg.png");
  // qa.PrintXYVertexAll("QAplots/XYVertexAll.png");
  qa.PrintXYVertexCompare("QAplots/Tracking_XYVertexCompare.png");

  // qa.PrintPvsPInnerWallTPC("QAplots/PrintPvsPInnerWallTPC.png");

  // ############# QA ####################
  // qa.PrintITSSigmaElevsP("QAplots/ITSSigmaElevsP.png");
  // qa.PrintITSSigmaPionvsP("QAplots/ITSSigmaPionvsP.png");
  // qa.PrintITSSigmaKaonvsP("QAplots/ITSSigmaKaonvsP.png");

  qa.PrintTPCSigmaElevsP("QAplots/TPCSigmaElevsP.png");
  // qa.PrintTPCSigmaPionvsP("QAplots/TPCSigmaPionvsP.png");
  // qa.PrintTPCSigmaKaonvsP("QAplots/TPCSigmaKaonvsP.png");

  // qa.PrintTOFSigmaElevsP("QAplots/TOFSigmaElevsP.png");

  qa.PrintTPCSigmaElevsEta("QAplots/TPCSigmaElevsEta.png");
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

LmCocktail* ProcessCocktail()
{
  Printf("______ process cocktail ______");
  // cocktail (handles the cocktail spectra)
  Int_t collsystem = -1;
  if (centrality == "0080") collsystem = LmCocktail::kPbPb_0080_5020;
  else if (centrality == "0010") collsystem = LmCocktail::kPbPb_0010_5020;
  else if (centrality == "1050") collsystem = LmCocktail::kPbPb_1050_5020;
  else if (centrality == "5080") collsystem = LmCocktail::kPbPb_5080_5020;
  LmCocktail* cockt00 = new LmCocktail(collsystem);

  // cocktail managers (organize input)
  // for resonances
  LmCocktailMan* cocktmanReso = new LmCocktailMan();
  cocktmanReso->SetInputfiles(const_cast<char*>(cocktail_files[which_cockt_files].Data()));
  cocktmanReso->SetInputlists(const_cast<char*>(cocktail_list[which_cockt_list].Data()));
  cocktmanReso->SetInputhistAndDim(const_cast<char*>(cocktail_histograms[which_cockt_hists].Data()), 2); // 2D
  cocktmanReso->SetInputfilesAndHistsLow(const_cast<char*>(cocktail_files[which_cockt_files_low].Data()), const_cast<char*>(cocktail_histograms[which_cockt_hists].Data())); // 2D
  cocktmanReso->SetInputfilesAndHistsHigh(const_cast<char*>(cocktail_files[which_cockt_files_high].Data()), const_cast<char*>(cocktail_histograms[which_cockt_hists].Data())); // 2D
  cocktmanReso->SetHistForNevents("NEvents");
  cocktmanReso->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanReso->Process(LmCocktailMan::kResonances);
  // cocktmanReso->Process(LmCocktailMan::kLFsum);


  std::cout << "--- JPsi ---" << std::endl;
  // for heavy flavours
  LmCocktailMan* cocktmanJPsi = new LmCocktailMan();
  cocktmanJPsi->SetInputfiles(const_cast<char*>(JPsi_files[which_JPsi_files].Data()));
  cocktmanJPsi->SetInputlists(const_cast<char*>(JPsi_list.Data()));
  cocktmanJPsi->SetInputhistAndDim(const_cast<char*>(JPsi_histograms[which_JPsi_hists].Data()), 2); // 2D
  // cocktmanJPsi->SetRelUncertainties("+0.3:-0.4:+0.5:-0.3");
  std::cout << cockt00->GetNcoll() << std::endl;
  cocktmanJPsi->SetArbitraryScaling( cockt00->GetNcoll() * 0.4 /** 62.8/64.5 */);
  cocktmanJPsi->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanJPsi->Process(LmCocktailMan::kJpsi);

  std::cout << "--- HEAVY FLAVOUR COCKTAIL ---" << std::endl;
  // for heavy flavours
  LmCocktailMan* cocktmanHF = new LmCocktailMan();
  cocktmanHF->SetInputfiles(const_cast<char*>(heavyfl_files[which_heavyfl_files].Data()));
  cocktmanHF->SetInputlists(const_cast<char*>(heavyfl_list.Data()));
  cocktmanHF->SetInputhistAndDim(const_cast<char*>(heavyfl_histograms[which_heavyfl_hists].Data()), 2); // 2D
  cocktmanHF->SetRelUncertainties("+0.3:-0.4:+0.5:-0.3");
  cocktmanHF->SetArbitraryScaling(2); // when using nquarks histogram instead of nevents, by which the yield gets downscaled about 2 times stronger.
  cocktmanHF->SetHistForNeventsHF(const_cast<char*>(heavyfl_hist_Nevents[which_heavyfl_hists].Data()));
  cocktmanHF->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanHF->Process(LmCocktailMan::kHeavyFl);
  // for virtual photons
  // (not available yet)

  cockt00->AttachManager( *cocktmanReso );
  cockt00->AttachManager( *cocktmanHF );
  cockt00->AttachManager( *cocktmanJPsi );
  //  cockt00->SetCrosssection_Event(); // cross sections and ncolls should instead be specified in LmCocktail constructor.
  //  cockt00->SetCrosssection_pp();
  //  cockt00->SetNcollCharm();
  cockt00->Process(); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...

  // only needed if cocktail shall be projected and plotted stand-alone:
  cockt00->SetBinsPtee_forprojMee(binsPtee_forMee);
  cockt00->SetBinsMee_forprojPtee(binsMee_forPtee);
  cockt00->MakeSpectra1D(); // do projections according to attached binning.
  // for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
  //   cockt00->PrintCocktail_Mee(i, Form("hCocktailMee_bin%d.pdf", i));
  // }
  return cockt00;
}


//_______________________________________________________________________________________________
void ProcessInputfiles(LmHandler* han_sys, LmHandler* han_ana)
{
  Printf("______ process input files ______");
  TBenchmark* bench = new TBenchmark();

  // Add all configs to LmFileManager for efficient file handling
  for (int ic=0; ic<n_config; ic++) {
    LmFileManager::Instance()->AddConfig( cconfig[ic] ); // regular
    LmFileManager::Instance()->AddConfig( cconfig[ic] ); // systematics
  }

  std::vector<LmManager*>    mgrVec, mgrVec_systematic;
  std::vector<LmBackground*> bkgVec, bkgVec_systematic;
  std::vector<LmSignal*>     sigVec, sigVec_systematic;
  std::vector<LmHandler*>    hanVec, hanVec_systematic;

  bench->Start("input_processing");
  ProcessSingleInputs(cconfig, "",
                      mgrVec,           bkgVec,           sigVec,
                      mgrVec_systematic,bkgVec_systematic,sigVec_systematic);
  Printf("______ DONE WITH SINGLE INPUT PROCESSING ______");
  bench->Show("input_processing");

  // Attach signals to the handlers which will be used in main function.
  for(Int_t iCuts = 0; iCuts < n_config; ++iCuts) {
    han_sys->AttachSignal(*sigVec_systematic.at(iCuts));
    han_ana->AttachSignal(*sigVec.at(iCuts));
  }

  // write most important histograms to rootfiles:
  // add bits of histograms you want to save: LmSignal::kSubSig+LmSignal::kSoverB+LmSignal::kSignif (to save all, use LmSignal::kMAXhist-1)
  // TFile* _fileOut2D_sys = new TFile(extpath_sys.Data(), "RECREATE");
  // han_sys->Write2DHist(LmSignal::kMAXhist-1, kFALSE, kTRUE);
  // _fileOut2D_sys->Close();
  // TFile* _fileOut2D_ana = new TFile(extpath_ana.Data(), "RECREATE");
  // han_ana->Write2DHist(LmSignal::kMAXhist-1, kFALSE, kTRUE);
  // _fileOut2D_ana->Close();

}

//____________________________________________________________________________________________
LmSignal* ProcessOneInput(LmManager* mgr)
{
  Printf("______ process one input ______");

  mgr->SetProjOption(projoption);
  mgr->SetEnableEffiCorr(kDoEffiCorrection);
  mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
  mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
  mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
  mgr->SetEnableExclusionCutZ(kDoExclusionCutZ);
  mgr->SetRebinning2D(mee_bins.size()-1, mee_bins.data(), ptee_bins.size()-1, ptee_bins.data());
  // mgr->SetRebinning2D(n_mee_bin_4D, mee_bin_4D, n_ptee_bin, ptee_bin);
  mgr->Process();

  LmBackground* bkg = new LmBackground(*mgr, "bkg");
  bkg->SetUseRfactor(kUseRFactor);
  bkg->Process(kBackground);

  LmSignal* sig = new LmSignal(*mgr, *bkg); // will take manager name (from caption[]), if no name is given.
  sig->Process(LmSignal::kStd);

  return sig;
}

void ProcessSingleInputs(TString config[], TString effiName,
                         std::vector<LmManager*> &mgrVec,     std::vector<LmBackground*> &bkgVec,     std::vector<LmSignal*> &sigVec,
                         std::vector<LmManager*> &mgrVec_sys, std::vector<LmBackground*> &bkgVec_sys, std::vector<LmSignal*> &sigVec_sys)
{
  Printf("______ process single inputs ______");
  if (effiName.IsNull()) {} // to avoid compiler warning

  for (int ic=0; ic<n_config; ic++) {
    Printf("config # %d:  %s", ic, config[ic].Data());

    LmManager* mgr = new LmManager(const_cast<char*>(config[ic].Data()));
    mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);

    mgr->SetProjOption(projoption);
    mgr->SetEnableEffiCorr(kDoEffiCorrection);
    mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
    mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
    mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
    mgr->SetEnableExclusionCutZ(kDoExclusionCutZ);
    mgr->SetRebinning2D(mee_bins.size()-1, mee_bins.data(), ptee_bins.size()-1, ptee_bins.data());
    mgr->Process();
    mgrVec.push_back(mgr);

    LmBackground* bkg = new LmBackground(*(mgrVec.at(ic)),Form("bg_cut_%02d",ic+1));
    bkg->SetUseRfactor(kUseRFactor);
    bkg->Process(kBackground);
    bkgVec.push_back(bkg);

    LmSignal* sig = new LmSignal(*(mgrVec.at(ic)), *(bkgVec.at(ic))/*, Form("sig_cut_%02d",ic+1)*/); // will take manager name (from caption[]), if no name is given.
    sig->SetDoSignifRaw(kDoSignifRaw);
    sig->SetDoNormBinwidth(kDoNormBinwidth);
    sig->SetDoNormNevents(kDoNormNevents);
    sig->Process(LmSignal::kStd);
    sigVec.push_back(sig);

    LmManager* mgr_sys = new LmManager(const_cast<char*>(config[ic].Data()));
    mgr_sys->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);

    mgr_sys->SetProjOption(projoption);
    mgr_sys->SetEnableEffiCorr(kDoEffiCorrection);
    mgr_sys->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
    mgr_sys->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
    mgr_sys->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
    mgr_sys->SetEnableExclusionCutZ(kDoExclusionCutZ);
    mgr_sys->SetRebinning2D(n_mee_bin_systematic, mee_bin_systematic, n_ptee_bin_systematic, ptee_bin_systematic);
    mgr_sys->Process();
    mgrVec_sys.push_back(mgr_sys);

    LmBackground* bkg_sys = new LmBackground(*(mgrVec_sys.at(ic)),Form("bg_sys_cut_%02d",ic+1));
    bkg_sys->SetUseRfactor(kUseRFactor);
    bkg_sys->Process(kBackground);
    bkgVec_sys.push_back(bkg_sys);

    // LmSignal* sig_sys = new LmSignal(*(mgrVec_sys.at(ic)), *(bkgVec_sys.at(ic)), Form("sig_sys_cut_%02d",ic+1));
    LmSignal* sig_sys = new LmSignal(*(mgrVec_sys.at(ic)), *(bkgVec_sys.at(ic)));
    sig_sys->SetDoSignifRaw(kDoSignifRaw);
    sig_sys->SetDoNormBinwidth(kDoNormBinwidth);
    sig_sys->SetDoNormNevents(kDoNormNevents);
    sig_sys->Process(LmSignal::kStd);
    sigVec_sys.push_back(sig_sys);
  }
}
