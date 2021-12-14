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
#include "theo_Misc.h"

#include "LmManager.h"
#include "LmBackground.h"
#include "LmSignal.h"
#include "LmHandler.h"
#include "LmHelper.h"
#include "LmFileManager.h"


void ProcessSingleInputs(TString vConfig, TString vEffiConfig, TString inputhist, Int_t inputdim, TString name,
                         std::vector<LmManager*> &mgrVec,std::vector<LmBackground*> &bkgVec,std::vector<LmSignal*> &sigVec,
                         Int_t n_bins_mee, const Double_t* bins_mee, Int_t n_bins_ptee, const Double_t* bins_ptee, LmBackground::enType type);

void MultiplyByBinwidth(TH1D *h);
int main()
{
  gErrorIgnoreLevel = kWarning;
  
//  TString cconfigRef = "pPb, #sqrt{#it{s}} = 5.02 TeV:./input/pPbLowmassPairByPairCorrectionTest.root:Histos_diel_lowmass:cut01PtEtaPhi";
  
  TString cconfig1   = "pPb, #sqrt{#it{s}} = 5.02 TeV:./input/pPbLowmassPairByPairCorrectionTest.root:Histos_diel_lowmass:cut01PtEtaPhi";
  TString cconfig2   = "pPb, #sqrt{#it{s}} = 5.02 TeV:./input/pPbLowmassPairByPairCorrectionTest.root:Histos_diel_lowmass:cut01PtPhi";
  TString cconfig3   = "pPb, #sqrt{#it{s}} = 5.02 TeV:./input/pPbLowmassPairByPairCorrectionTest.root:Histos_diel_lowmass:cut01PtEta";
  TString cconfig4   = "pPb, #sqrt{#it{s}} = 5.02 TeV:./input/pPbLowmassPairByPairCorrectionTest.root:Histos_diel_lowmass:cut01Pt";
  
  TString econfig1 = "./input/pPbToyMCpairEff_raw_1_pt200.root:NGenPairs_pt200:NRecPairs_Eff_cut01_pt200";
  TString econfig2 = "./input/pPbToyMCpairEff_raw_2_pt200.root:NGenPairs_pt200:NRecPairs_Eff_cut01_pt200";
  TString econfig3 = "./input/pPbToyMCpairEff_raw_LHC14g3b_pt200.root:NGenPairs_pt200:NRecPairs_Eff_cut01_pt200";
  
  //___________________________
  LmHelper helper; // initialization of style/colors
  
  std::vector<Double_t> binsPtee_forMee;
  binsPtee_forMee.push_back(0.);
  binsPtee_forMee.push_back(6.);
  
  std::vector<Double_t> binsMee_forPtee;
  binsMee_forPtee.push_back(0.00);
  binsMee_forPtee.push_back(0.14);
  binsMee_forPtee.push_back(0.75);
  binsMee_forPtee.push_back(1.10);
  binsMee_forPtee.push_back(3.00);
  
  Double_t plotMeeMin  = 0., plotMeeMax  = 4.0;
  Double_t plotPteeMin = 0., plotPteeMax = 6.0;
  
  //_________________________________________________________________________________________________________________________________
  
  LmBaseSignal::SetInputLabelZ("#it{#phi}_{V}","rad");
  std::vector<LmManager*>    mgrVec;
  std::vector<LmBackground*> bkgVec;
  std::vector<LmSignal*>     sigVec;
  
  Double_t mee_bin1[]  = { 
  0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
  0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,
  0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,
  0.30,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,
  0.40,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,
  0.50,0.51,0.52,0.53,0.54,0.55,0.56,0.57,0.58,0.59,
  0.60,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,
  0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,
  0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,
  0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99,
  1.00,1.01,1.02,1.03,1.04,1.05,1.06,1.07,1.08,1.09,
  1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,
  2.20,2.40,2.60,2.80,3.00,3.01,3.02,3.03,3.04,3.05,
  3.06,3.07,3.08,3.09,3.10,3.30,3.50,4.00 };
                          
  Double_t ptee_bin1[] = { 
  0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
  0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,
  0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,
  0.30,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,
  0.40,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,
  0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,
  1.00,1.05,1.10,1.15,1.20,1.25,1.30,1.35,1.40,1.45,
  1.50,1.55,1.60,1.65,1.70,1.75,1.80,1.85,1.90,1.95,
  2.00,2.05,2.10,2.15,2.20,2.25,2.30,2.35,2.40,2.45,
  2.50,2.60,2.70,2.80,2.90,3.00,3.10,3.20,3.30,3.40,
  3.50,3.60,3.70,3.80,3.90,4.00,4.10,4.20,4.30,4.40,
  4.50,5.00,6.00 };
                          
  Int_t n_mee_bin1  = sizeof(mee_bin1)/sizeof(*mee_bin1) -1;
  Int_t n_ptee_bin1 = sizeof(ptee_bin1)/sizeof(*ptee_bin1) -1;
  
//  Double_t mee_bin2[401],ptee_bin2[251];
//  for(Int_t i = 0; i < 401; ++i)
//    mee_bin2[i] = 0. + i * 0.01;
//  for(Int_t i = 0; i < 251; ++i)
//    ptee_bin2[i] = 0. + i * 0.02;
//  Int_t n_mee_bin2 = sizeof(mee_bin2)/sizeof(*mee_bin2) -1;
//  Int_t n_ptee_bin2 = sizeof(ptee_bin2)/sizeof(*ptee_bin2) -1;
  
  std::vector<Double_t> binsMee({0.00,0.02,0.05,0.09,0.14,0.20,0.30,0.40,0.50,
                                 0.60,0.70,0.75,0.80,0.95,1.00,1.05,1.10,1.40,
                                 1.70,2.00,2.40,2.80,3.00,3.05,3.10,3.30,3.50,4.00 });
  std::vector<Double_t> binsPt1({0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.22,0.24,0.26,0.28,0.30,0.32,0.34,0.36,0.38,
                                 0.40,0.42,0.44,0.46,0.48,0.50,0.60,0.70,0.80,0.90,1.00,1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,
                                 2.00,2.10,2.20,2.30,2.40,2.50,2.60,2.70,2.80,2.90,3.00,3.20,3.40,3.60,3.80,4.00,4.50,5.00,6.00});
//  std::vector<Double_t> binsPt2({0.00,0.10,0.20,0.30,0.40,0.50,0.60,0.70,0.80,0.90,1.00,1.20,1.40,1.60,1.80,2.00,2.20,2.40,2.60,2.80,3.00,3.40,3.80,4.20,5.00,6.00});
  std::vector<Double_t> binsPt2({0.00,0.20,0.40,0.60,0.80,1.00,1.20,1.40,1.60,1.80,2.00,2.20,2.40,2.60,2.80,3.00,3.40,3.80,4.20,5.00,6.00});
//  std::vector<Double_t> binsPt3({0.00,0.20,0.40,0.60,0.80,1.00,1.20,1.40,1.60,1.80,2.00,2.20,2.40,2.60,2.80,3.00,3.40,3.80,4.20,5.00,6.00});
  std::vector<Double_t> binsPt3({0.00,0.40,0.80,1.20,1.60,2.00,2.40,2.80,3.40,4.00,5.00,6.00});
  std::vector<Double_t> binsPt4({0.00,0.40,0.80,1.20,1.60,2.00,2.50,3.00,3.50,4.00,4.50,5.00,6.00});                               

  Int_t n_mee_bin2  = binsMee.size() -1;
  Double_t *mee_bin2 = &binsMee[0];
  
//  Double_t ptee_bin2[] = { 
//  0.00,0.25,0.50,0.75,1.00,1.25,1.50,1.75,
//  2.00,2.25,2.50,3.00,3.50,4.00,4.50,5.00,6.00 };
//  Int_t n_ptee_bin2 = sizeof(ptee_bin2)/sizeof(*ptee_bin2) -1;
 
  Double_t arbScalingccbar = 1.0908;
  Double_t arbScalingbbbar = 1.0595;
  TString relUncertaintiesccbar = "0.21184:0.33266";
  TString relUncertaintiesbbbar = "0.24349:0.22888";
  std::vector<TString> cocktail_files;
  cocktail_files.push_back("./input/cocktail/LF-pPb_502_pt200_ratios_raw_scaled.root");
  cocktail_files.push_back("./input/cocktail/LF-pPb_502_pt200_ratios-Low_raw_scaled.root");
  cocktail_files.push_back("./input/cocktail/LF-pPb_502_pt200_ratios-High_raw_scaled.root");
//  cocktail_files.push_back("/Users/tbroeker/software/Analysis/Cocktail/Preparation/output/pPb/raw_scaled_LF-ratios.root");
//  cocktail_files.push_back("/Users/tbroeker/software/Analysis/Cocktail/Preparation/output/pPb/raw_scaled_LF-ratios_low.root");
//  cocktail_files.push_back("/Users/tbroeker/software/Analysis/Cocktail/Preparation/output/pPb/raw_scaled_LF-ratios_high.root");
  std::vector<TString> cocktail_histograms;
  cocktail_histograms.push_back("Mee_Ptee_Pion_angleSmeared:Mee_Ptee_Eta_angleSmeared:Mee_Ptee_EtaPrime_angleSmeared:Mee_Ptee_Rho_angleSmeared:Mee_Ptee_Omega_angleSmeared:Mee_Ptee_OmegaDalitz_angleSmeared:Mee_Ptee_Phi_angleSmeared:Mee_Ptee_PhiDalitz_angleSmeared:Mee_Ptee_JPsi_angleSmeared");
  
  LmCocktailMan* cocktmanReso = new LmCocktailMan(cocktail_files.at(0),cocktail_histograms.at(0),2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
  cocktmanReso->SetInputfilesAndHistsLow(cocktail_files.at(1),cocktail_histograms.at(0));
  cocktmanReso->SetInputfilesAndHistsHigh(cocktail_files.at(2),cocktail_histograms.at(0));
  cocktmanReso->SetInputlists("Mee_Ptee_angleSmeared");
//  cocktmanReso->Process(LmCocktailMan::kLFsum);
  cocktmanReso->Process(LmCocktailMan::kResonances);
  
  LmCocktailMan *cocktmanCharm  = new LmCocktailMan("./input/pPb/cocktail/heavy_flavour_pt200.root","charm_pythiaPerugia2011_pt200" ,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
  LmCocktailMan *cocktmanBeauty = new LmCocktailMan("./input/pPb/cocktail/heavy_flavour_pt200.root","beauty_pythiaPerugia2011_pt200",2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);

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
    
/*
  Printf("______ process input  ______");
  ProcessSingleInputs(cconfigRef,econfig,"InvMass_PairPt_PhivPair",3,"FineBinGeom",  mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kGeom);
  ProcessSingleInputs(cconfigRef,econfig,"InvMass_PairPt_PhivPair",3,"FineBinArith", mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kArith);
  ProcessSingleInputs(cconfigRef,econfig,"InvMass_PairPt_PhivPair",3,"FineBinHybrid",mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
  ProcessSingleInputs(cconfigRef,econfig,"InvMass_PairPt_PhivPair",3,"StdBinGeom",   mgrVec,bkgVec,sigVec,n_mee_bin2,mee_bin2,n_ptee_bin1,ptee_bin1,LmBackground::kGeom);
  ProcessSingleInputs(cconfigRef,econfig,"InvMass_PairPt_PhivPair",3,"StdBinArith",  mgrVec,bkgVec,sigVec,n_mee_bin2,mee_bin2,n_ptee_bin1,ptee_bin1,LmBackground::kArith);
  ProcessSingleInputs(cconfigRef,econfig,"InvMass_PairPt_PhivPair",3,"StdBinHybrid", mgrVec,bkgVec,sigVec,n_mee_bin2,mee_bin2,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
  Printf("______ DONE WITH SINGLE INPUT PROCESSING ______");
  
  LmHandler *han = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  han->SetBinningMee(0,&binsMee);
  han->SetBinningPtee(0,&binsPt1);
  han->SetBinningPtee(1,&binsPt2);
  han->SetBinningPtee(2,&binsPt3);
  han->SetBinningPtee(3,&binsPt4);
  han->AttachSignal(*(sigVec.at(2)),sigVec.at(2)->GetName());
  han->AttachSignal(*(sigVec.at(0)),sigVec.at(0)->GetName());
  han->AttachSignal(*(sigVec.at(1)),sigVec.at(1)->GetName());
  han->AttachSignal(*(sigVec.at(5)),sigVec.at(5)->GetName());
  han->AttachSignal(*(sigVec.at(3)),sigVec.at(3)->GetName());
//  han->AttachSignal(*(sigVec.at(4)),sigVec.at(4)->GetName());
  han->SetDoRatio();
  han->SetPlotRangeRatio(0.5,1.5);
  han->Process(LmHandler::kCompare);
  han->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnMee);
  han->SetPlotRangeY(1.0001e-6,0.9999e-1);
  han->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee);
  han->SetPlotRangeY(1.0001e-7,0.9999e-3);
  han->PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee);
  han->SetPlotRangeY(4.0001e-8,4.9999e-4);
  han->PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee);
  han->SetPlotRangeY(1.0001e-7,0.9999e-4);
  han->PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee);
//  han->SetPlotRangeY(0.8001,1.2999);
//  han->PrintCompare(LmSignal::kRfactor,0, LmBaseSignal::kProjOnMee, "",kTRUE,kFALSE);
//  han->PrintCompare(LmSignal::kRfactor,0, LmBaseSignal::kProjOnPtee,"",kTRUE,kFALSE);
//  han->PrintCompare(LmSignal::kRfactor,1, LmBaseSignal::kProjOnPtee,"",kTRUE,kFALSE);
//  han->PrintCompare(LmSignal::kRfactor,2, LmBaseSignal::kProjOnPtee,"",kTRUE,kFALSE);
//  han->PrintCompare(LmSignal::kRfactor,3, LmBaseSignal::kProjOnPtee,"",kTRUE,kFALSE);

  LmHandler CocktailHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin, plotPteeMax);
  CocktailHandler.SetBinningMee(0,&binsMee);
  CocktailHandler.SetBinningPtee(0,&binsPt1);
  CocktailHandler.SetBinningPtee(1,&binsPt2);
  CocktailHandler.SetBinningPtee(2,&binsPt3);
  CocktailHandler.SetBinningPtee(3,&binsPt4);
  CocktailHandler.AttachSignal(*(sigVec.at(2)),sigVec.at(2)->GetName());
  CocktailHandler.AttachSignal(*(sigVec.at(0)),sigVec.at(0)->GetName());
  CocktailHandler.AttachSignal(*(sigVec.at(1)),sigVec.at(1)->GetName());
  CocktailHandler.AttachSignal(*(sigVec.at(5)),sigVec.at(5)->GetName());
  CocktailHandler.AttachSignal(*(sigVec.at(3)),sigVec.at(3)->GetName());
  
  CocktailHandler.SetCocktail(&cocktail);
  CocktailHandler.SetDrawStyleCocktail("hist");
  CocktailHandler.SetDrawStyleCocktailErr("hist E2");
//  CocktailHandler.SetPlotRangeRatio(0.2, 1.799);
//  CocktailHandler.SetDivideOption("0");
  CocktailHandler.SetDoRatio(kFALSE);
//  CocktailHandler.SetPlotRangeY(1.0001e-6,0.4999e-0);
  CocktailHandler.Process(LmHandler::kCompare);
  CocktailHandler.Process(LmHandler::kCocktail);
  
  CocktailHandler.PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnMee );
  CocktailHandler.PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee);
  CocktailHandler.PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee);
  CocktailHandler.PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee);
  CocktailHandler.PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee);
*/  
  
  mgrVec.clear();
  bkgVec.clear();
  sigVec.clear();
  Printf("______ process input  ______");
//  ProcessSingleInputs(cconfig1,econfig1,"InvMass_PairPt_PhivPair",       3,"ToyCorr",     mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
//  ProcessSingleInputs(cconfig1,"",      "InvMass_PairPt_PhivPair_EffCor",3,"PtEtaPhiCorr",mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
//  ProcessSingleInputs(cconfig2,"",      "InvMass_PairPt_PhivPair_EffCor",3,"PtPhiCorr",   mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
//  ProcessSingleInputs(cconfig3,"",      "InvMass_PairPt_PhivPair_EffCor",3,"PtEtaCorr",   mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
//  ProcessSingleInputs(cconfig4,"",      "InvMass_PairPt_PhivPair_EffCor",3,"PtCorr",      mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
  
  ProcessSingleInputs(cconfig1,econfig1,"InvMass_PairPt_PhivPair",       3,"ToyCorr",     mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kArith);
  ProcessSingleInputs(cconfig1,"",      "InvMass_PairPt_PhivPair_EffCor",3,"PtEtaPhiCorr",mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kArith);
  ProcessSingleInputs(cconfig2,"",      "InvMass_PairPt_PhivPair_EffCor",3,"PtPhiCorr",   mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kArith);
  ProcessSingleInputs(cconfig3,"",      "InvMass_PairPt_PhivPair_EffCor",3,"PtEtaCorr",   mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kArith);
  ProcessSingleInputs(cconfig4,"",      "InvMass_PairPt_PhivPair_EffCor",3,"PtCorr",      mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kArith);
  Printf("______ DONE WITH SINGLE INPUT PROCESSING ______");
  
  LmHandler *han2 = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  han2->SetBinningMee(0,&binsMee);
  han2->SetBinningPtee(0,&binsPt1);
  han2->SetBinningPtee(1,&binsPt2);
  han2->SetBinningPtee(2,&binsPt3);
  han2->SetBinningPtee(3,&binsPt4);
  han2->AttachSignal(*(sigVec.at(0)),sigVec.at(0)->GetName());
  han2->AttachSignal(*(sigVec.at(1)),sigVec.at(1)->GetName());
  han2->AttachSignal(*(sigVec.at(2)),sigVec.at(2)->GetName());
  han2->AttachSignal(*(sigVec.at(3)),sigVec.at(3)->GetName());
  han2->AttachSignal(*(sigVec.at(4)),sigVec.at(4)->GetName());
  han2->SetDoRatio();
  han2->SetPlotRangeRatio(0.5,1.5);
  han2->Process(LmHandler::kCompare);
  han2->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnMee ,"+_OnTheFlyCorrection");
  han2->SetPlotRangeY(1.0001e-6,0.9999e-0);
  han2->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
  han2->SetPlotRangeY(1.0001e-7,0.9999e-2);
  han2->PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
  han2->SetPlotRangeY(4.0001e-8,4.9999e-3);
  han2->PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
  han2->SetPlotRangeY(1.0001e-7,0.9999e-3);
  han2->PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
  
  
  LmHandler CocktailHandler2(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin, plotPteeMax);
  CocktailHandler2.SetBinningMee(0,&binsMee);
  CocktailHandler2.SetBinningPtee(0,&binsPt1);
  CocktailHandler2.SetBinningPtee(1,&binsPt2);
  CocktailHandler2.SetBinningPtee(2,&binsPt3);
  CocktailHandler2.SetBinningPtee(3,&binsPt4);
  CocktailHandler2.AttachSignal(*(sigVec.at(0)),sigVec.at(0)->GetName());
  CocktailHandler2.AttachSignal(*(sigVec.at(1)),sigVec.at(1)->GetName());
  CocktailHandler2.AttachSignal(*(sigVec.at(2)),sigVec.at(2)->GetName());
  CocktailHandler2.AttachSignal(*(sigVec.at(3)),sigVec.at(3)->GetName());
  
  CocktailHandler2.SetCocktail(&cocktail);
  CocktailHandler2.SetDrawStyleCocktail("hist");
  CocktailHandler2.SetDrawStyleCocktailErr("hist E2");
//  CocktailHandler2.SetPlotRangeRatio(0.2, 1.799);
//  CocktailHandler2.SetDivideOption("0");
  CocktailHandler2.SetDoRatio(kFALSE);
//  CocktailHandler2.SetPlotRangeY(1.0001e-6,0.4999e-0);
  CocktailHandler2.Process(LmHandler::kCompare);
  CocktailHandler2.Process(LmHandler::kCocktail);
  
  CocktailHandler2.PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnMee ,"+_OnTheFlyCorrection");
  CocktailHandler2.SetPlotRangeY(1.0001e-6,0.9999e-0);
  CocktailHandler2.PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
  CocktailHandler2.SetPlotRangeY(1.0001e-7,0.9999e-2);
  CocktailHandler2.PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
  CocktailHandler2.SetPlotRangeY(4.0001e-8,4.9999e-3);
  CocktailHandler2.PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
  CocktailHandler2.SetPlotRangeY(1.0001e-7,0.9999e-3);
  CocktailHandler2.PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
  

  mgrVec.clear();
  bkgVec.clear();
  sigVec.clear();
  Printf("______ process input  ______");
  ProcessSingleInputs(cconfig1,econfig1,"InvMass_PairPt_PhivPair",      3,"ToyCor1",       mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
  ProcessSingleInputs(cconfig1,econfig2,"InvMass_PairPt_PhivPair",      3,"ToyCor2",       mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
  ProcessSingleInputs(cconfig1,econfig3,"InvMass_PairPt_PhivPair",      3,"ToyCorLHC14g3b",mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
  Printf("______ DONE WITH SINGLE INPUT PROCESSING ______");
  
  LmHandler *han3 = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  han3->SetBinningMee(0,&binsMee);
  han3->SetBinningPtee(0,&binsPt1);
  han3->SetBinningPtee(1,&binsPt2);
  han3->SetBinningPtee(2,&binsPt3);
  han3->SetBinningPtee(3,&binsPt4);
  han3->AttachSignal(*(sigVec.at(0)),sigVec.at(0)->GetName());
  han3->AttachSignal(*(sigVec.at(1)),sigVec.at(1)->GetName());
  han3->AttachSignal(*(sigVec.at(2)),sigVec.at(2)->GetName());
  han3->SetDoRatio();
  han3->SetPlotRangeRatio(0.5,1.5);
  han3->Process(LmHandler::kCompare);
  han3->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnMee ,"+_EffComp");
  han3->SetPlotRangeY(1.0001e-6,0.9999e-0);
  han3->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,"+_EffComp");
  han3->SetPlotRangeY(1.0001e-7,0.9999e-2);
  han3->PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee,"+_EffComp");
  han3->SetPlotRangeY(4.0001e-8,4.9999e-3);
  han3->PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee,"+_EffComp");
  han3->SetPlotRangeY(1.0001e-7,0.9999e-3);
  han3->PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee,"+_EffComp");
 

  
//  TFile fOut(Form("dataMisc.root"),"RECREATE");
//  fOut.cd();
//  Double_t binsMee[] = {0.00,0.02,0.05,0.09,0.14,0.20,0.30,0.40,0.50,0.60,0.70,0.75,0.80,0.95,1.00,1.05,1.10,1.40,1.70,2.00,2.30,2.60,2.80,3.00,3.05,3.10,3.30,3.50,4.00};
//  Int_t nBinsMee = sizeof(binsMee) / sizeof(binsMee[0]) -1;
//  for(Int_t i = 0; i < han->GetNSignals(); ++i){
//    TH1D *hTmp = static_cast<TH1D*> (sigVec.at(i)->GetSubSig(0,1)->GetDatahist()->Clone(Form("%s_tmp",sigVec.at(i)->GetName())));
//    MultiplyByBinwidth(hTmp);
//    TH1D *hRef = static_cast<TH1D*> (hTmp->Rebin(nBinsMee,Form("%s",sigVec.at(i)->GetName()),binsMee));
//    hRef->Scale(1.,"width");
//    hRef->Write();
//  }
  
//  LmHandler *han2 = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
//  han2->AttachSignal(*(sigVec.at(5)),sigVec.at(5)->GetName());
//  han2->Process(LmHandler::kCompare);
//  han2->PrintCompare(LmSignal::kUnlike+LmSignal::kBkg,0, LmBaseSignal::kProjOnMee);
  
//  TH1D *hReference1_tmp = static_cast<TH1D*> (sigVec.at(0)->GetSubSig(0,1)->GetDatahist());
//  hReference1_tmp->SetName("hReference1_tmp");
//  TH1D *hpostCorr_tmp  = static_cast<TH1D*> (sigVec.at(1)->GetSubSig(0,1)->GetDatahist());
//  hpostCorr_tmp->SetName("hpostCorr_tmp");
//  TH1D *hOnTheFly_tmp  = static_cast<TH1D*> (sigVec.at(2)->GetSubSig(0,1)->GetDatahist());
//  hOnTheFly_tmp->SetName("hOnTheFly_tmp");
//  TH1D *hReference2_tmp  = static_cast<TH1D*> (sigVec.at(3)->GetSubSig(0,1)->GetDatahist());
//  hReference2_tmp->SetName("hReference2_tmp");
//  
//  MultiplyByBinwidth(hReference1_tmp);
//  MultiplyByBinwidth(hpostCorr_tmp);
//  MultiplyByBinwidth(hOnTheFly_tmp);
//  MultiplyByBinwidth(hReference2_tmp);
//  TH1D *hReference1 = static_cast<TH1D*> (hReference1_tmp->Rebin(nBinsMee,"hReference1_NoCorrGeomBkg",binsMee));
//  TH1D *hpostCorr   = static_cast<TH1D*> (hpostCorr_tmp  ->Rebin(nBinsMee,"hPostCorrection",binsMee));
//  TH1D *hOnTheFly   = static_cast<TH1D*> (hOnTheFly_tmp  ->Rebin(nBinsMee,"hOnTheFlyCorrection",binsMee));
//  TH1D *hReference2 = static_cast<TH1D*> (hReference2_tmp->Rebin(nBinsMee,"hReference2_NoCorrGeomBkg",binsMee));
//  hReference1->Scale(1.,"width");
//  hpostCorr  ->Scale(1.,"width");
//  hOnTheFly  ->Scale(1.,"width");
//  hReference2->Scale(1.,"width");
//  hReference1->Write();
//  hReference2->Write();
//  hpostCorr ->Write();
//  hOnTheFly ->Write();

//  sigVec.at(0)->WriteHist1D(LmSignal::kSubSig,binsPtee_forMee,kTRUE,LmBaseSignal::kProjOnMee,"reference"); 
//  sigVec.at(1)->WriteHist1D(LmSignal::kSubSig,binsPtee_forMee,kTRUE,LmBaseSignal::kProjOnMee,"postCorrection");
//  sigVec.at(2)->WriteHist1D(LmSignal::kSubSig,binsPtee_forMee,kTRUE,LmBaseSignal::kProjOnMee,"onTheFlyCorrection");
//  fOut.Close();
  
  std::cout << "main.cpp done :-)" << std::endl;
  return 0;
}

void MultiplyByBinwidth(TH1D *h)
{
  for(Int_t i = 0; i <= h->GetNbinsX()+1; ++i){
    h->SetBinContent(i,h->GetBinContent(i)*h->GetXaxis()->GetBinWidth(i));
    h->SetBinError  (i,h->GetBinError(i)  *h->GetXaxis()->GetBinWidth(i));
  }
}

void ProcessSingleInputs(TString vConfig, TString vEffiConfig, TString inputhist, Int_t inputdim, TString name,
                         std::vector<LmManager*> &mgrVec,std::vector<LmBackground*> &bkgVec,std::vector<LmSignal*> &sigVec,
                         Int_t n_bins_mee, const Double_t* bins_mee, Int_t n_bins_ptee, const Double_t* bins_ptee, LmBackground::enType type)
{

  LmHelper::Info(Form("config:  %s %s \n",vConfig.Data(),vEffiConfig.Data()));
  
  LmManager* mgr = new LmManager(const_cast<char*>(vConfig.Data())); // TODO: input style to be optimized
  mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
  if(inputdim > 2)
    mgr->SetEnableExclusionCutZ(LmManager::kNoCut);
  mgr->SetRebinning2D(n_bins_mee, bins_mee, n_bins_ptee, bins_ptee);
  if(vEffiConfig.Length() > 0){
    TObjArray *arr = vEffiConfig.Tokenize(":");
    mgr->SetEffifileAndHists(arr->At(0)->GetName(),arr->At(1)->GetName(),arr->At(2)->GetName());
    mgr->SetEnableEffiCorr(kTRUE);
  }
  else 
    mgr->SetEnableEffiCorr(kFALSE);
    
  mgr->Process();
  mgr->SetEtaRange(-0.8,0.8);
  mgr->SetPtRange(0.2,-1.);
  mgrVec.push_back(mgr);
  
  LmBackground* bkg = new LmBackground(*(mgrVec.at(mgrVec.size()-1)),Form("bkg_%s",name.Data()));
  bkg->SetRfactorUnityRange(1.);
  bkg->Process(type);
  bkgVec.push_back(bkg);
  
  LmSignal* sig = new LmSignal(*(mgrVec.at(mgrVec.size()-1)), *(bkgVec.at(bkgVec.size()-1)),Form("%s",name.Data()));
  sig->SetDoNormBinwidth(kDoNormBinwidth);
  sig->SetDoNormNevents(kDoNormNevents);
//  sig->SetDoNormNevents(kFALSE);
  sig->Process(LmSignal::kStd);
  sigVec.push_back(sig);
}





