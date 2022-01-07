//Analysis Framework for Dilepton Spectra

// c++ includes
#include <iostream>
#include <vector>
using namespace std;
// ROOT includes
#include "TString.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TStyle.h"
#include "TF2.h"
#include "TError.h"
#include "TSystem.h"
// project includes
#include "theo.h"

#include "../core/LmManager.h"
#include "../core/LmBackground.h"
#include "../core/LmSignal.h"
#include "../core/LmHandler.h"
#include "../core/LmHelper.h"
#include "../core/LmFileManager.h"

void ProcessSingleInputs(std::vector<TString> vConfig, std::vector<TString> vEffiConfig,
                         std::vector<LmManager*> &mgrVec,     std::vector<LmBackground*> &bkgVec,     std::vector<LmSignal*> &sigVec,
                         std::vector<LmManager*> *mgrVec_sys, std::vector<LmBackground*> *bkgVec_sys, std::vector<LmSignal*> *sigVec_sys,
                         std::vector<TH3D*> &vTemlatesUS, std::vector<TH3D*> &vTemlatesLS, std::vector<Double_t> vNormValPhiV);

//void ProcessSingleInputs(std::vector<TString> vConfig, std::vector<TString> vEffiConfig,
//                         std::vector<LmManager*> &mgrVec,     std::vector<LmBackground*> &bkgVec,     std::vector<LmSignal*> &sigVec,
//                         std::vector<LmManager*> *mgrVec_sys=0x0, std::vector<LmBackground*> *bkgVec_sys=0x0, std::vector<LmSignal*> *sigVec_sys=0x0);

//void ProcessSingleInputs(std::vector<TString> vConfig, std::vector<TString> vEffiConfig,
//                         std::vector<LmManager*> &mgrVec, std::vector<LmBackground*> &bkgVec, std::vector<LmSignal*> &sigVec,
//                         std::vector<TH3D*> &vTemlatesUS, std::vector<TH3D*> &vTemlatesLS, std::vector<Double_t> vCutValPhiV, std::vector<Double_t> vNormValPhiV);

int main()
{
  gErrorIgnoreLevel = kWarning;
  
  //___________________________
  Bool_t bPt200 = kTRUE;
  Bool_t bpp = kTRUE;
  Bool_t bPrelCompare = kFALSE;
  Bool_t bWriteOut = kFALSE;
  Bool_t bPythia = kTRUE;
  Bool_t bCocktail = kTRUE;
  Bool_t bCombined = kTRUE;
  Bool_t bSignals = kTRUE;

  UInt_t Ncuts = 23;
  Int_t refCutset = (6 <= Ncuts) ? 5 : Ncuts-1;
    
  TString relUncertaintiesccbar(""),relUncertaintiesbbbar("");
  Double_t arbScalingccbar(1.),arbScalingbbbar(1.);
  if(bpp){
    fTriggerEff = 1./0.852;
    arbScalingccbar = 1.0907;
    arbScalingbbbar = 0.9792;
    relUncertaintiesccbar = "0.21060:0.31841";
    relUncertaintiesbbbar = "0.24241:0.20762";    
  }
  else{
    fTriggerEff = 1./0.976;
    arbScalingccbar = 1.0908;
    arbScalingbbbar = 1.0595;
    relUncertaintiesccbar = "0.21184:0.33266";
    relUncertaintiesbbbar = "0.24349:0.22888";
  }
  Printf("TriggerEfficiency: %f",fTriggerEff);
  LmHelper helper; // initialization of style/colors
   
  std::vector<Double_t> binsPtee_forMee;
  binsPtee_forMee.push_back(0.);
//  binsPtee_forMee.push_back(1.);
//  binsPtee_forMee.push_back(2.);
//  binsPtee_forMee.push_back(3.);
  binsPtee_forMee.push_back(6.);

  std::vector<Double_t> binsMee_forPtee;
  binsMee_forPtee.push_back(0.00);
  binsMee_forPtee.push_back(0.14);
  binsMee_forPtee.push_back(0.75);
  binsMee_forPtee.push_back(1.10);
  binsMee_forPtee.push_back(3.00);
//  binsMee_forPtee.push_back(3.10);

//std::vector<Double_t> binsMee_forPtee;
//  binsMee_forPtee.push_back(0.00);
//  binsMee_forPtee.push_back(0.08);
//  binsMee_forPtee.push_back(0.14);
//  binsMee_forPtee.push_back(0.16);  
//  binsMee_forPtee.push_back(1.10);
//  binsMee_forPtee.push_back(2.70);
//  binsMee_forPtee.push_back(2.80);
//  binsMee_forPtee.push_back(3.20);
    
  Double_t plotMeeMin  = 0., plotMeeMax  = 4.0;
  Double_t plotPteeMin = 0., plotPteeMax = 6.0;
  
  // plotting binning
  std::vector<Double_t> binsMee({0.00,0.02,0.05,0.09,0.14,0.20,0.30,0.40,0.50,
                                 0.60,0.70,0.75,0.80,0.95,1.00,1.05,1.10,1.40,
                                 1.70,2.00,2.40,2.80,3.00,3.05,3.10,3.30,3.50,4.00 });
  std::vector<Double_t> binsPt1({0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.22,0.24,0.26,0.28,0.30,0.32,0.34,0.36,0.38,
                                 0.40,0.42,0.44,0.46,0.48,0.50,0.60,0.70,0.80,0.90,1.00,1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,
                                 2.00,2.10,2.20,2.30,2.40,2.50,2.60,2.70,2.80,2.90,3.00,3.20,3.40,3.60,3.80,4.00,4.50,5.00,6.00});
  std::vector<Double_t> binsPt2({0.00,0.20,0.40,0.60,0.80,1.00,1.20,1.40,1.60,1.80,2.00,2.20,2.40,2.60,2.80,3.00,3.40,3.80,4.20,5.00,6.00});
  std::vector<Double_t> binsPt3({0.00,0.40,0.80,1.20,1.60,2.00,2.40,2.80,3.40,4.00,5.00,6.00});
  std::vector<Double_t> binsPt4({0.00,0.40,0.80,1.20,1.60,2.00,2.50,3.00,3.50,4.00,4.50,5.00,6.00});  
  
  //_________________________________________________________________________________________________________________________________
  
  LmBaseSignal::SetInputLabelZ("#it{#phi}_{V}","rad");
  TString effi_gen = "NGenPairs_pt200";
  TString ptcut = "pt200";
  if(!bPt200){ 
    ptcut = "pt400";
    effi_gen = "NGenPairs_pt400";
  }
  TString coll_system = "pp, #sqrt{#it{s}} = 7 TeV"; 
  TString system = "pp"; 
  if(!bpp){
    coll_system = "pPb, #sqrt{#it{s}} = 5.02 TeV"; 
    system = "pPb"; 
  }
  
  std::vector<TString> cconfig,econfig;
  std::vector<TH3D*> vTempUS,vTempLS;
  std::vector<Double_t> vCutValPhiV,vNormValPhiV;
  TFile *fIn = new TFile(Form("/Users/tbroeker/software/Analysis/Efficiencies/SingleEfficiencies/input/%sEfficiencyPhiVtemplates.root",system.Data()),"READ");    
  TH3D *hTempUS = static_cast<TH3D*>(fIn->Get("Histos_diel_lowmass")->FindObject("cut19")->FindObject("Pair_US")  ->FindObject("InvMass_PairPt_PhivPair") );
  TH3D *hTempLS = static_cast<TH3D*>(fIn->Get("Histos_diel_lowmass")->FindObject("cut19")->FindObject("Pair_LS--")->FindObject("InvMass_PairPt_PhivPair") );
  hTempLS   ->Add(static_cast<TH3D*>(fIn->Get("Histos_diel_lowmass")->FindObject("cut19")->FindObject("Pair_LS++")->FindObject("InvMass_PairPt_PhivPair")) );
  
  for(UInt_t i = 1; i <= Ncuts; ++i){
    if(bCombined){
      cconfig.push_back( coll_system+":"+"./input/combined_"+system+"LowmassRandomRej_"+ptcut+".root:"+tree_name+":"+Form("cut%02d",i) );
      econfig.push_back( "./input/"+system+"ToyMCpairEff_raw_"+ptcut+".root:"+effi_gen+":"+Form("NRecPairsCombined_Eff_cut%02d_%s",i,ptcut.Data()) );
    }
    else{
      tree_name = "Histos_diel_lowmass";
      cconfig.push_back( coll_system+":"+"./input/"+system+"LowmassRandomRej_"+ptcut+".root:"+tree_name+":"+Form("cut%02d",i) );
      econfig.push_back( "./input/"+system+"ToyMCpairEff_raw_"+ptcut+".root:"+effi_gen+":"+Form("NRecPairs_Eff_cut%02d_%s",i,ptcut.Data()) );
    }
    if(bPt200){
      vTempUS.push_back(hTempUS);
      vTempLS.push_back(hTempLS);
      vCutValPhiV .push_back( 0.50*TMath::Pi() ); 
      vNormValPhiV.push_back( 0.50*TMath::Pi() );
    }
    else{
      vTempUS.push_back(0x0);
      vTempLS.push_back(0x0);
      vCutValPhiV .push_back( 0.50*TMath::Pi() ); 
      vNormValPhiV.push_back( 0.50*TMath::Pi() );
    }
  }
  
  std::vector<LmManager*>    mgrVec,mgrVecSys;
  std::vector<LmBackground*> bkgVec,bkgVecSys;
  std::vector<LmSignal*>     sigVec,sigVecSys;

  
  Printf("______ process input  ______");
  ProcessSingleInputs(cconfig,econfig,
                       mgrVec   , bkgVec   , sigVec,
                      &mgrVecSys,&bkgVecSys,&sigVecSys,
                      vTempUS,vTempLS,vNormValPhiV);
  Printf("______ DONE WITH SINGLE INPUT PROCESSING ______");
  
  LmHandler *hanSystematic;
  hanSystematic = new  LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, plotMeeMax,plotPteeMin, plotPteeMax);
  for(UInt_t iCuts = 0; iCuts < Ncuts; ++iCuts)
    hanSystematic->AttachSignal(*(sigVecSys.at(iCuts)), Form("cut%02d",iCuts+1));
  hanSystematic->Process(LmHandler::kSystematic_Average);
  hanSystematic->Process(LmHandler::kCompare);
  
//  TFile fOutttt("~/Desktop/relSystematic.root","RECREATE");
//  fOutttt.cd();
//  TH2D *hhhh = static_cast<TH2D*> (hanSystematic->GetRelSystematics()->Clone("relSystematicUncertainty"));
//  TH1D *hhh = static_cast<TH1D*> (hanSystematic->GetRelSystematics()->ProjectionX("relSystematicUncertainty",1,1));
//  Printf("rel uncert.:");
//  Printf("0.08-0.14: %4.2f%%",100.*hhh->GetBinContent(hhh->GetXaxis()->FindBin(0.10)));
//  Printf("0.16-1.10: %4.2f%%",100.*hhh->GetBinContent(hhh->GetXaxis()->FindBin(0.50)));
//  Printf("1.10-2.70: %4.2f%%",100.*hhh->GetBinContent(hhh->GetXaxis()->FindBin(2.00)));
//  Printf("2.80-3.20: %4.2f%%",100.*hhh->GetBinContent(hhh->GetXaxis()->FindBin(3.00)));
//  hhh->Write();
//  fOutttt.Close();
//  return 0;
  
  LmHandler* hanSignal = new  LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, plotMeeMax,plotPteeMin, plotPteeMax);
  hanSignal->AttachSignal(*(sigVec.at(refCutset)),"ref data");
  hanSignal->GetLmSignalI(0)->SetSymmetricRelSystematics(hanSystematic->GetRelSystematics());
  hanSignal->GetLmSignalI(0)->Process(LmSignal::kSystematic);  
  
  LmHandler *hanAverage = new  LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, plotMeeMax,plotPteeMin, plotPteeMax);
  LmHandler *hanWeightedAverage = new  LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, plotMeeMax,plotPteeMin, plotPteeMax);
  for(UInt_t iCuts = 0; iCuts < Ncuts; ++iCuts){
    hanAverage        ->AttachSignal(*(sigVec.at(iCuts)), Form("cut%02d",iCuts+1));
    hanWeightedAverage->AttachSignal(*(sigVec.at(iCuts)), Form("cut%02d",iCuts+1));
  }
  hanAverage->Process(LmHandler::kAverage);
  hanSignal->AttachSignal(*(hanAverage->GetLmSigAverage()),"average data");
//  hanSignal->GetLmSignalI(1)->SetSymmetricRelSystematics(hanSystematic->GetRelSystematics());
//  hanSignal->GetLmSignalI(1)->Process(LmSignal::kSystematic); 
  
  hanWeightedAverage->Process(LmHandler::kWeightedAverage);
  hanSignal->AttachSignal(*(hanWeightedAverage->GetLmSigAverage()),"weighted average data");
//  hanSignal->GetLmSignalI(2)->SetSymmetricRelSystematics(hanSystematic->GetRelSystematics());
//  hanSignal->GetLmSignalI(2)->Process(LmSignal::kSystematic); 
  hanSignal->SetBinningMee (0,&binsMee);
  hanSignal->SetBinningPtee(0,&binsPt1);
  hanSignal->SetBinningPtee(1,&binsPt2);
  hanSignal->SetBinningPtee(2,&binsPt3);
  hanSignal->SetBinningPtee(3,&binsPt4);
  hanSignal->Process(LmHandler::kCompare);
   
  LmHandler *hanSignals(0x0);
  if(bSignals){
    hanSignals = new  LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, plotMeeMax,plotPteeMin, plotPteeMax);
    for(UInt_t iCuts = 0; iCuts < Ncuts; ++iCuts)
      hanSignals->AttachSignal(*(sigVec.at(iCuts)), Form("cut%02d",iCuts+1));
    hanSignals->SetBinningMee (0,&binsMee);
    hanSignals->SetBinningPtee(0,&binsPt1);
    hanSignals->SetBinningPtee(1,&binsPt2);
    hanSignals->SetBinningPtee(2,&binsPt3);
    hanSignals->SetBinningPtee(3,&binsPt4);
    hanSignals->Process(LmHandler::kCompare);
  }
  // external preliminary results
  if(bPrelCompare){
    if(bpp){
      TFile *fExt = new TFile("./input/pp/preliminary_pp_7TeV.root","READ");
      TH1D *hExt = static_cast<TH1D*> (fExt->Get("histFinal"));
      hExt->SetName("preliminary");
      hExt->SetMarkerColor(kBlack);
      hExt->SetLineColor(kBlack);
      hExt->SetMarkerStyle(21);
      hExt->SetMarkerSize(1);
      hExt->SetFillStyle(0);
      hExt->Scale(1./73.2);
      
      hanSignal->GetLmSignalI(0)->GetSubSig(binsPtee_forMee.size()-1,LmBaseSignal::kProjOnMee)->SetExternalObject(hExt);
      
      //       TH1D *hExtSystematic = static_cast<TH1D*> (hExt->Clone("preliminarySystematic"));
      //       TFile *fExtSyst = new TFile("./input/pp/preliminary_syst_pp_7TeV.root","READ");
      //       TH1D *hExtSyst = static_cast<TH1D*> (fExtSyst->Get("AllSystUncert"));
      //       for(Int_t i = 1; i <= hExtSystematic->GetNbinsX(); ++i)
      //         hExtSystematic->SetBinError(i,hExtSyst->GetBinContent(i)*hExtSystematic->GetBinContent(i));
      //       sigVec.at(refCutset-1)->GetSubSig(binsPtee_forMee.size()-1,LmBaseSignal::kProjOnMee)->SetExternalSystematicObject(hExtSystematic);       
    }
    else{
      TFile *fExt = new TFile("./input/pPb/preliminary.root","READ");
      TH1D *hExtM   = static_cast<TH1D*> (fExt->Get("DataPoints_mee_pt200"));
      TH1D *hExtPt1 = static_cast<TH1D*> (fExt->Get("DataPoints_pt1_pt200"));
      TH1D *hExtPt2 = static_cast<TH1D*> (fExt->Get("DataPoints_pt2_pt200"));
      TH1D *hExtPt3 = static_cast<TH1D*> (fExt->Get("DataPoints_pt3_pt200"));
      TH1D *hExtPt4 = static_cast<TH1D*> (fExt->Get("DataPoints_pt4_pt200"));
      
      hExtM  ->SetName("preliminary");
      hExtPt1->SetName("preliminary");
      hExtPt2->SetName("preliminary");
      hExtPt3->SetName("preliminary");
      hExtPt4->SetName("preliminary");
      hExtM  ->SetMarkerColor(kBlack);
      hExtPt1->SetMarkerColor(kBlack);
      hExtPt2->SetMarkerColor(kBlack);
      hExtPt3->SetMarkerColor(kBlack);
      hExtPt4->SetMarkerColor(kBlack);
      hExtM  ->SetLineColor(kBlack);
      hExtPt1->SetLineColor(kBlack);
      hExtPt2->SetLineColor(kBlack);
      hExtPt3->SetLineColor(kBlack);
      hExtPt4->SetLineColor(kBlack);
      hExtM  ->SetMarkerStyle(21);
      hExtPt1->SetMarkerStyle(21);
      hExtPt2->SetMarkerStyle(21);
      hExtPt3->SetMarkerStyle(21);
      hExtPt4->SetMarkerStyle(21);
      
      hanSignal->GetLmSignalI(hanSignal->GetNSignals()-1)->GetSubSig(binsPtee_forMee.size()-1,LmBaseSignal::kProjOnMee)->SetExternalObject(hExtM);
      hanSignal->GetLmSignalI(hanSignal->GetNSignals()-1)->GetSubSig(0,LmBaseSignal::kProjOnPtee)->SetExternalObject(hExtPt1);
      hanSignal->GetLmSignalI(hanSignal->GetNSignals()-1)->GetSubSig(1,LmBaseSignal::kProjOnPtee)->SetExternalObject(hExtPt2);
      hanSignal->GetLmSignalI(hanSignal->GetNSignals()-1)->GetSubSig(2,LmBaseSignal::kProjOnPtee)->SetExternalObject(hExtPt3);
      hanSignal->GetLmSignalI(hanSignal->GetNSignals()-1)->GetSubSig(3,LmBaseSignal::kProjOnPtee)->SetExternalObject(hExtPt4);
      
      if(hanSignals){
        hanSignals->GetLmSignalI(Ncuts-1)->GetSubSig(binsPtee_forMee.size()-1,LmBaseSignal::kProjOnMee)->SetExternalObject(hExtM);
        hanSignals->GetLmSignalI(Ncuts-1)->GetSubSig(0,LmBaseSignal::kProjOnPtee)->SetExternalObject(hExtPt1);
        hanSignals->GetLmSignalI(Ncuts-1)->GetSubSig(1,LmBaseSignal::kProjOnPtee)->SetExternalObject(hExtPt2);
        hanSignals->GetLmSignalI(Ncuts-1)->GetSubSig(2,LmBaseSignal::kProjOnPtee)->SetExternalObject(hExtPt3);
        hanSignals->GetLmSignalI(Ncuts-1)->GetSubSig(3,LmBaseSignal::kProjOnPtee)->SetExternalObject(hExtPt4);
      }
    }
  }
  
  if(hanSignals){
    hanSignals->SetPlotRangeY(1.0001e-8,0.9999e-0);
    for(UInt_t iProj = 0; iProj < binsPtee_forMee.size()-1; ++iProj)
      hanSignals->PrintCompare(LmSignal::kSubSig,iProj, LmBaseSignal::kProjOnMee,Form("+_signals_%s",system.Data()));
    hanSignals->SetPlotRangeY(1.0001e-6,0.9999e-0);
    hanSignals->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,Form("+_signals_%s",system.Data()));
    hanSignals->SetPlotRangeY(1.0001e-7,0.9999e-2);
    hanSignals->PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee,Form("+_signals_%s",system.Data()));
    hanSignals->SetPlotRangeY(4.0001e-8,4.9999e-3);
    hanSignals->PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee,Form("+_signals_%s",system.Data()));
    hanSignals->SetPlotRangeY(1.0001e-7,0.9999e-3);
    hanSignals->PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee,Form("+_signals_%s",system.Data()));
  }
  hanSignal->SetPlotRangeY(1.0001e-8,0.9999e-0);
  for(UInt_t iProj = 0; iProj < binsPtee_forMee.size()-1; ++iProj)
      hanSignal->PrintCompare(LmSignal::kSubSig,iProj, LmBaseSignal::kProjOnMee,Form("+_signal_%s",system.Data()));
  hanSignal->SetPlotRangeY(1.0001e-6,0.9999e-0);
  hanSignal->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,Form("+_signal_%s",system.Data()));
  hanSignal->SetPlotRangeY(1.0001e-7,0.9999e-2);
  hanSignal->PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee,Form("+_signal_%s",system.Data()));
  hanSignal->SetPlotRangeY(4.0001e-8,4.9999e-3);
  hanSignal->PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee,Form("+_signal_%s",system.Data()));
  hanSignal->SetPlotRangeY(1.0001e-7,0.9999e-3);
  hanSignal->PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee,Form("+_signal_%s",system.Data()));  

  
  if(bCocktail){  
    std::vector<TString> cocktail_files;
    if(bpp){
      cocktail_files.push_back("./input/cocktail/LF-pp_7_"+ptcut+"_ratios_raw_scaled.root");
      cocktail_files.push_back("./input/cocktail/LF-pp_7_"+ptcut+"_ratios-Low_raw_scaled.root");
      cocktail_files.push_back("./input/cocktail/LF-pp_7_"+ptcut+"_ratios-High_raw_scaled.root");
    }
    else{
      cocktail_files.push_back("./input/cocktail/LF-pPb_502_"+ptcut+"_ratios_raw_scaled.root");
      cocktail_files.push_back("./input/cocktail/LF-pPb_502_"+ptcut+"_ratios-Low_raw_scaled.root");
      cocktail_files.push_back("./input/cocktail/LF-pPb_502_"+ptcut+"_ratios-High_raw_scaled.root");
    }
//    cocktail_files.push_back(Form("/Users/tbroeker/software/Analysis/Cocktail/Preparation/output/%s/raw_scaled_LF-102816.root",system.Data()));
//    cocktail_files.push_back(Form("/Users/tbroeker/software/Analysis/Cocktail/Preparation/output/%s/raw_scaled_LF-102816_low.root",system.Data()));
//    cocktail_files.push_back(Form("/Users/tbroeker/software/Analysis/Cocktail/Preparation/output/%s/raw_scaled_LF-102816_high.root",system.Data()));
    
    std::vector<TString> cocktail_histograms;    cocktail_histograms.push_back("Mee_Ptee_Pion_angleSmeared:Mee_Ptee_Eta_angleSmeared:Mee_Ptee_EtaPrime_angleSmeared:Mee_Ptee_Rho_angleSmeared:Mee_Ptee_Omega_angleSmeared:Mee_Ptee_OmegaDalitz_angleSmeared:Mee_Ptee_Phi_angleSmeared:Mee_Ptee_PhiDalitz_angleSmeared:Mee_Ptee_JPsi_angleSmeared");
    
    LmCocktailMan* cocktmanReso = new LmCocktailMan(cocktail_files.at(0),cocktail_histograms.at(0),2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
    cocktmanReso->SetInputfilesAndHistsLow(cocktail_files.at(1),cocktail_histograms.at(0));
    cocktmanReso->SetInputfilesAndHistsHigh(cocktail_files.at(2),cocktail_histograms.at(0));
    cocktmanReso->SetInputlists("Mee_Ptee_angleSmeared");
    cocktmanReso->Process(LmCocktailMan::kLFsum);
        
    LmCocktailMan *cocktmanCharm(0x0),*cocktmanBeauty(0x0);
    if(bPythia){
      cocktmanCharm  = new LmCocktailMan(Form("./input/%s/cocktail/heavy_flavour_pt200.root",system.Data()),"charm_pythiaPerugia2011_pt200" ,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
      cocktmanBeauty = new LmCocktailMan(Form("./input/%s/cocktail/heavy_flavour_pt200.root",system.Data()),"beauty_pythiaPerugia2011_pt200",2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
    }
    else{
      cocktmanCharm  = new LmCocktailMan(Form("./input/%s/cocktail/heavy_flavour_pt200.root",system.Data()),"charm_powheg_pt200" ,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
      cocktmanBeauty = new LmCocktailMan(Form("./input/%s/cocktail/heavy_flavour_pt200.root",system.Data()),"beauty_powheg_pt200",2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);  
    }
    cocktmanCharm ->SetArbitraryScaling(arbScalingccbar);
    cocktmanBeauty->SetArbitraryScaling(arbScalingbbbar);
    cocktmanCharm ->SetRelUncertainties(relUncertaintiesccbar.Data());
    cocktmanBeauty->SetRelUncertainties(relUncertaintiesbbbar.Data());
    cocktmanCharm ->Process(LmCocktailMan::kHeavyFl);
    cocktmanBeauty->Process(LmCocktailMan::kHeavyFl);
    
    LmCocktail cocktail(LmCocktail::kpPb_MB_502);
    cocktail.AttachManager( *cocktmanReso );
    cocktail.AttachManager( *cocktmanCharm );
    cocktail.AttachManager( *cocktmanBeauty );
    
    cocktail.Process();
    LmHandler CocktailHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin, plotPteeMax);
    CocktailHandler.AttachSignal(*(hanSignal     ->GetLmSignalI(0)),"data");
    CocktailHandler.SetBinningMee (0,&binsMee);
    CocktailHandler.SetBinningPtee(0,&binsPt1);
    CocktailHandler.SetBinningPtee(1,&binsPt2);
    CocktailHandler.SetBinningPtee(2,&binsPt3);
    CocktailHandler.SetBinningPtee(3,&binsPt4);
    
    CocktailHandler.SetCocktail(&cocktail); // attach complete cocktail to handler. call cockt00->Process() before!
    CocktailHandler.Process(LmHandler::kCocktail);
    CocktailHandler.SetDrawStyleCocktail("hist");
    CocktailHandler.SetDrawStyleCocktailErr("hist E2");
//    CocktailHandler.SetPlotRangeRatio(0.2, 1.799);
//    CocktailHandler.SetDivideOption("0");
//    CocktailHandler.SetDoRatio(kTRUE);
//    CocktailHandler.SetPlotRangeY(1.0001e-6,0.4999e-0);
    
    CocktailHandler.SetPlotRangeY(1.0001e-8,0.9999e-0);
    for(UInt_t iProj = 0; iProj < binsPtee_forMee.size()-1; ++iProj)
      CocktailHandler.PrintCompare(LmSignal::kSubSig,iProj, LmBaseSignal::kProjOnMee,Form("+_%s",system.Data()));
//    for(UInt_t iProj = 0; iProj < binsMee_forPtee.size()-1; ++iProj)  
//      CocktailHandler.PrintCompare(LmSignal::kSubSig,iProj, LmBaseSignal::kProjOnPtee,Form("+_%s",system.Data()));
      CocktailHandler.SetPlotRangeY(1.0001e-6,0.9999e-0);
      CocktailHandler.PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,Form("+_%s",system.Data()));
      CocktailHandler.SetPlotRangeY(1.0001e-7,0.9999e-2);
      CocktailHandler.PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee,Form("+_%s",system.Data()));
      CocktailHandler.SetPlotRangeY(4.0001e-8,4.9999e-3);
      CocktailHandler.PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee,Form("+_%s",system.Data()));
      CocktailHandler.SetPlotRangeY(1.0001e-7,0.9999e-3);
      CocktailHandler.PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee,Form("+_%s",system.Data()));   
  }
  else{
    LmHandler outHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin, plotPteeMax);
    outHandler.AttachSignal(*(hanSignal     ->GetLmSignalI(0)),"data");
    outHandler.SetBinningMee (0,&binsMee);
    outHandler.SetBinningPtee(0,&binsPt1);
    outHandler.SetBinningPtee(1,&binsPt2);
    outHandler.SetBinningPtee(2,&binsPt3);
    outHandler.SetBinningPtee(3,&binsPt4);
    outHandler.Process(LmHandler::kCompare); 
    
    outHandler.SetPlotRangeY(1.0001e-8,0.9999e-0);
    for(UInt_t iProj = 0; iProj < binsPtee_forMee.size()-1; ++iProj)
      outHandler.PrintCompare(LmSignal::kSubSig,iProj, LmBaseSignal::kProjOnMee,Form("+_%s",system.Data()));
//    for(UInt_t iProj = 0; iProj < binsMee_forPtee.size()-1; ++iProj)  
//      outHandler.PrintCompare(LmSignal::kSubSig,iProj, LmBaseSignal::kProjOnPtee,Form("+_%s",system.Data()));
    outHandler.SetPlotRangeY(1.0001e-6,0.9999e-0);
    outHandler.PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,Form("+_%s",system.Data()));
    outHandler.SetPlotRangeY(1.0001e-7,0.9999e-2);
    outHandler.PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee,Form("+_%s",system.Data()));
    outHandler.SetPlotRangeY(4.0001e-8,4.9999e-3);
    outHandler.PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee,Form("+_%s",system.Data()));
    outHandler.SetPlotRangeY(1.0001e-7,0.9999e-3);
    outHandler.PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee,Form("+_%s",system.Data()));   
  }  
  if(bWriteOut){  
    //    TFile fOut_mee(Form("%s_data_mee.root",system.Data()),"RECREATE");
    //    fOut_mee.cd();
    //    hanSignal->Write1DHistSingle(LmSignal::kSubSig,kTRUE,kFALSE);
    //    fOut_mee.Close();
    //    TFile fOut_ptee(Form("%s_data_ptee.root",system.Data()),"RECREATE");
    TFile fOut_ptee(Form("data.root"),"UPDATE");
    fOut_ptee.cd();
    //    hanSignal->Write1DHistSingle(LmSignal::kSubSig,kFALSE,kFALSE);
    //(unsigned int histBits, const std::vector<Double_t> bins, Bool_t simplehistnames, Bool_t projOnMee, TString signame)
    hanSignal->GetLmSignalI(0)->WriteHist1D(LmSignal::kSubSig,binsPtee_forMee,kTRUE,LmBaseSignal::kProjOnMee,system+"_");
    hanSignal->GetLmSignalI(0)->WriteHist1D(LmSignal::kSubSig,binsMee_forPtee,kTRUE,LmBaseSignal::kProjOnPtee,system+"_");
    fOut_ptee.Close();
  }
  
  std::cout << "main.cpp done :-)" << std::endl;
  return 0;
}

void ProcessSingleInputs(std::vector<TString> vConfig, std::vector<TString> vEffiConfig,
                         std::vector<LmManager*> &mgrVec,     std::vector<LmBackground*> &bkgVec,     std::vector<LmSignal*> &sigVec,
                         std::vector<LmManager*> *mgrVec_sys, std::vector<LmBackground*> *bkgVec_sys, std::vector<LmSignal*> *sigVec_sys,
                         std::vector<TH3D*> &vTemlatesUS, std::vector<TH3D*> &vTemlatesLS, std::vector<Double_t> vNormValPhiV)
{
  if(vConfig.size() != vEffiConfig.size()){ LmHelper::Error("ProcessSingleInputs(): unequal numbers of data and effi configs!"); return; }
  for (UInt_t ic=0; ic<vConfig.size(); ic++){
    LmFileManager::Instance()->AddConfig( vConfig.at(ic) ); // regular
    if(mgrVec_sys&&bkgVec_sys&&sigVec_sys) LmFileManager::Instance()->AddConfig( vConfig.at(ic) ); // systematic
  }
  for(UInt_t ic=0; ic<vConfig.size(); ic++){
    LmHelper::Info(Form("config:  %s %s \n",vConfig.at(ic).Data(),vEffiConfig.at(ic).Data()));
    TObjArray *arr = vEffiConfig.at(ic).Tokenize(":");
    LmManager* mgr = new LmManager(const_cast<char*>(vConfig.at(ic).Data())); // TODO: input style to be optimized
    mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
    mgr->SetTemplateNormRegion(0.,vNormValPhiV.at(ic));
    if(vTemlatesUS.at(ic)) mgr->SetExclusionZTemplates(vTemlatesUS.at(ic),vTemlatesLS.at(ic));
    mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
    mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
    mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
//    mgr->SetEnableExclusionCutZ(LmManager::kFlatCorr);
    mgr->SetEnableExclusionCutZ(LmManager::kTemplUnsub);
    mgr->SetRebinning2D(n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
    mgr->SetEffifileAndHists(arr->At(0)->GetName(),arr->At(1)->GetName(),arr->At(2)->GetName());
    mgr->SetEnableEffiCorr(kDoEffiCorrection); // use this to disable or just comment out the setter above...
    mgr->Process();
    mgr->SetNeventsPhysSel(fTriggerEff*mgr->GetNeventsPhysSel());
    mgr->SetEtaRange(-0.8,0.8);
    mgr->SetPtRange(0.2,-1.);
    //    mgr->SetThetaEEmin(0.05);
    mgrVec.push_back(mgr);
    
    LmBackground* bkg = new LmBackground(*(mgrVec.at(ic)),Form("bg_cut%2d",ic+1));
    bkg->SetRfactorUnityRange(1.);
    bkg->Process(LmBackground::kHybrid);
    bkgVec.push_back(bkg);
    
    LmSignal* sig = new LmSignal(*(mgrVec.at(ic)), *(bkgVec.at(ic)), Form("sig_cut %2d", ic+1));
    sig->SetDoNormBinwidth(kDoNormBinwidth);
    sig->SetDoNormNevents(kDoNormNevents);
    sig->Process(LmSignal::kStd);
    sigVec.push_back(sig);
    
    if(!(mgrVec_sys&&bkgVec_sys&&sigVec_sys)) continue;
    
    LmManager* mgr_sys = new LmManager(const_cast<char*>(vConfig.at(ic).Data())); // TODO: input style to be optimized
    mgr_sys->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
    mgr_sys->SetTemplateNormRegion(0.,vNormValPhiV.at(ic));
    if(vTemlatesUS.at(ic)) mgr_sys->SetExclusionZTemplates(vTemlatesUS.at(ic),vTemlatesLS.at(ic));
    mgr_sys->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
    mgr_sys->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
    mgr_sys->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
//    mgr->SetEnableExclusionCutZ(LmManager::kFlatCorr);
    mgr->SetEnableExclusionCutZ(LmManager::kTemplUnsub);
    mgr_sys->SetRebinning2D(n_mee_bin_systematic, mee_bin_systematic, n_ptee_bin_systematic, ptee_bin_systematic);
    mgr_sys->SetEffifileAndHists(arr->At(0)->GetName(),arr->At(1)->GetName(),arr->At(2)->GetName());
    mgr_sys->SetEnableEffiCorr(kDoEffiCorrection); // use this to disable or just comment out the setter above...
    mgr_sys->Process();
    mgr_sys->SetNeventsPhysSel(fTriggerEff*mgr_sys->GetNeventsPhysSel());
    mgr_sys->SetEtaRange(-0.8,0.8);
    mgr_sys->SetPtRange(0.2,-1.);
    mgrVec_sys->push_back(mgr_sys);
    
    LmBackground* bkg_sys = new LmBackground(*(mgrVec_sys->at(ic)),Form("bg_systematic_cut%2d",ic+1));
    bkg_sys->SetRfactorUnityRange(1.);
    bkg_sys->Process(LmBackground::kHybrid);
    bkgVec_sys->push_back(bkg_sys);
    
    LmSignal* sig_sys = new LmSignal(*(mgrVec_sys->at(ic)), *(bkgVec_sys->at(ic)), Form("sig_systematic_cut %2d", ic+1));
    sig_sys->SetDoNormBinwidth(kDoNormBinwidth);
    sig_sys->SetDoNormNevents(kDoNormNevents);
    sig_sys->Process(LmSignal::kStd);
    sigVec_sys->push_back(sig_sys);
  }
}

//void ProcessSingleInputs(std::vector<TString> vConfig, std::vector<TString> vEffiConfig,
//                         std::vector<LmManager*> &mgrVec, std::vector<LmBackground*> &bkgVec, std::vector<LmSignal*> &sigVec,
//                         std::vector<TH3D*> &vTemlatesUS, std::vector<TH3D*> &vTemlatesLS, std::vector<Double_t> vCutValPhiV, std::vector<Double_t> vNormValPhiV)
//{
//  if(vConfig.size() != vEffiConfig.size()) { LmHelper::Error("ProcessSingleInputs(): unequal numbers of data and effi configs!"); return; }
//  //  for (UInt_t ic=0; ic<vConfig.size(); ic++) {
//  //    LmFileManager::Instance()->AddConfig( vConfig.at(ic) ); // regular
//  //  }
//  for(UInt_t ic=0; ic<vConfig.size(); ic++){
//    if(ic > 0) bCutPhiV=kTRUE;
//    LmHelper::Info(Form("config:  %s %s \n",vConfig.at(ic).Data(),vEffiConfig.at(ic).Data()));
//    TObjArray *arr = vEffiConfig.at(ic).Tokenize(":");
//    LmManager* mgr = new LmManager(const_cast<char*>(vConfig.at(ic).Data())); // TODO: input style to be optimized
//    mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
//    
//    mgr->SetCutValPhiV(vCutValPhiV.at(ic));
//    mgr->SetCutValMee(cutValMee);  
//    mgr->SetTemplateNormRegion(0.,vNormValPhiV.at(ic));
//    if(vTemlatesUS.at(ic)) mgr->SetExclusionZTemplates(vTemlatesUS.at(ic),vTemlatesLS.at(ic));
////    mgr->SetEnablePhiVCut(bCutPhiV);
//    mgr->SetEnableExclusionCutZ(bCutPhiV);
//    
//    mgr->SetRebinning2D(n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
//    mgr->SetEffifileAndHists(arr->At(0)->GetName(),arr->At(1)->GetName(),arr->At(2)->GetName());
//    mgr->SetEnableEffiCorr(kDoEffiCorrection); // use this to disable or just comment out the setter above...
//    mgr->Process();
//    mgr->SetEtaRange(-0.8,0.8);
//    mgr->SetPtRange(0.2,-1.);
//    //    mgr->SetThetaEEmin(0.05);
//    mgrVec.push_back(mgr);
//    
//    LmBackground* bkg = new LmBackground(*(mgrVec.at(ic)),Form("bg_cut%2d",ic+1));
//    bkg->Process(LmBackground::kHybrid);
//    bkgVec.push_back(bkg);
//    
//    LmSignal* sig = new LmSignal(*(mgrVec.at(ic)), *(bkgVec.at(ic)), Form("sig_cut %2d", ic+1));
//    sig->SetDoNormBinwidth(kDoNormBinwidth);
//    sig->SetDoNormNevents(kDoNormNevents);
//    sig->Process(LmSignal::kStd);
//    sigVec.push_back(sig);                         
//  }
//}





