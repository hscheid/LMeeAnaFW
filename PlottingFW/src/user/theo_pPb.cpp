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
#include "theo_pPb.h"

#include "../core/LmManager.h"
#include "../core/LmBackground.h"
#include "../core/LmSignal.h"
#include "../core/LmHandler.h"
#include "../core/LmHelper.h"
#include "../core/LmFileManager.h"

void PlotHandler(LmHandler *han, TString name, Bool_t bSoverB=kFALSE, Bool_t bSignif=kFALSE);
LmSignal* GetSignal(std::vector<LmSignal*> &sigVec,std::vector<LmSignal*> &sigVec_sys, Int_t iSig, Bool_t bWeightedAve=kFALSE);
void ProcessSingleInputs(std::vector<TString> vConfig, std::vector<TString> vEffiConfig, TString inputhist,
                         std::vector<LmManager*> &mgrVec,std::vector<LmBackground*> &bkgVec,std::vector<LmSignal*> &sigVec,
                         std::vector<LmManager*> *mgrVec_sys, std::vector<LmBackground*> *bkgVec_sys, std::vector<LmSignal*> *sigVec_sys,
                         LmBackground::enType type,
                         Int_t corPhiV, std::vector<TH3D*> &vTemlatesUS, std::vector<TH3D*> &vTemlatesLS, std::vector<Double_t> vNormValPhiV);

void MultiplyByBinwidth(TH1D *h);
int main()
{
  gErrorIgnoreLevel = kWarning;
  
  UInt_t Ncuts = 23;
  Int_t refCutset = (6 <= Ncuts) ? 5 : Ncuts-1;
  
  std::vector<TString> cconfig,combcconfig,econfig1,combeconfig1,econfig2,combeconfig2,econfig3,combeconfig3,cconfigPF;
  std::vector<TH3D*> vTempUS,vTempLS;
  std::vector<Double_t> vCutValPhiV,vNormValPhiV;
  TFile *fIn = new TFile("/Users/tbroeker/software/Analysis/Efficiencies/SingleEfficiencies/input/pPbEfficiencyPhiVtemplates_2.root","READ");    
  TH3D *hTempUS = static_cast<TH3D*>(fIn->Get("Histos_diel_lowmass")->FindObject("cut19")->FindObject("Pair_US")  ->FindObject("InvMass_PairPt_PhivPair") );
  TH3D *hTempLS = static_cast<TH3D*>(fIn->Get("Histos_diel_lowmass")->FindObject("cut19")->FindObject("Pair_LS--")->FindObject("InvMass_PairPt_PhivPair") );
  hTempLS   ->Add(static_cast<TH3D*>(fIn->Get("Histos_diel_lowmass")->FindObject("cut19")->FindObject("Pair_LS++")->FindObject("InvMass_PairPt_PhivPair")) );
  
  for(UInt_t i = 1; i <= Ncuts; ++i){
    cconfig .push_back( coll_system+":"+"./input/pPbLowmassRandomRej_pt200.root:Histos_diel_lowmass:"+Form("cut%02d",i) );
    econfig1.push_back( Form("./input/pPbToyMCpairEff_raw_1_pt200.root:NGenPairs_pt200:NRecPairs_Eff_cut%02d_pt200",i) );
    econfig2.push_back( +Form("./input/pPbToyMCpairEff_raw_2_pt200.root:NGenPairs_pt200:NRecPairs_Eff_cut%02d_pt200",i) );
    econfig3.push_back( +Form("./input/pPbToyMCpairEff_raw_LHC14g3b_pt200.root:NGenPairs_pt200:NRecPairs_Eff_cut%02d_pt200",i) );
    
    combcconfig .push_back( coll_system+":"+"./input/combined_pPbLowmassRandomRej_pt200.root:NoList:"+Form("cut%02d",i) );
    combeconfig1.push_back( Form("./input/pPbToyMCpairEff_raw_1_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
    combeconfig2.push_back( Form("./input/pPbToyMCpairEff_raw_2_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
    combeconfig3.push_back( Form("./input/pPbToyMCpairEff_raw_LHC14g3b_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );

    cconfigPF.push_back( coll_system+":"+"./input/pPbLowmassRandomRej_pt200.root:Histos_diel_lowmass:"+Form("cut%02d_pf",i) );
    
    vTempUS.push_back(hTempUS);
    vTempLS.push_back(hTempLS);
    vCutValPhiV .push_back( 0.50*TMath::Pi() ); 
    vNormValPhiV.push_back( 0.50*TMath::Pi() );
    
  }
  
  binsPtee_forMee.push_back(0.);
  binsPtee_forMee.push_back(6.);
  
  binsMee_forPtee.push_back(0.00);
  binsMee_forPtee.push_back(0.14);
  binsMee_forPtee.push_back(0.75);
  binsMee_forPtee.push_back(1.10);
  binsMee_forPtee.push_back(3.00);
  
  //___________________________
  LmHelper helper; // initialization of style/colors
  
  
  
  //_________________________________________________________________________________________________________________________________  
  LmBaseSignal::SetInputLabelZ("#it{#phi}_{V}","rad");
  
  std::vector<Double_t> binsMee({0.00,0.01,0.02,0.05,0.09,0.14,0.20,0.30,0.40,0.50,
                                 0.60,0.70,0.75,0.80,0.95,1.00,1.05,1.10,1.40,
                                 1.70,2.00,2.40,2.80,3.00,3.05,3.10,3.30,3.50,4.00 });
  std::vector<Double_t> binsPt1({0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.22,0.24,0.26,0.28,0.30,0.32,0.34,0.36,0.38,
                                 0.40,0.42,0.44,0.46,0.48,0.50,0.60,0.70,0.80,0.90,1.00,1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,
                                 2.00,2.10,2.20,2.30,2.40,2.50,2.60,2.70,2.80,2.90,3.00,3.20,3.40,3.60,3.80,4.00,4.50,5.00,6.00});
//  std::vector<Double_t> binsPt1({0.000,0.025,0.050,0.075,0.100,0.125,0.150,0.175,0.200,0.225,0.250,0.275,0.300,0.325,0.350,0.375,0.400,0.425,0.450,0.475,0.500,
//                                 0.60,0.70,0.80,0.90,1.00,1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,2.10,2.20,
//                                 2.30,2.40,2.50,2.60,2.70,2.80,2.90,3.00,3.20,3.40,3.60,3.80,4.00,4.50,5.00,6.00,6.50,7.00,8.00,10.0});
  std::vector<Double_t> binsPt2({0.00,0.20,0.40,0.60,0.80,1.00,1.20,1.40,1.60,1.80,2.00,2.20,2.40,2.60,2.80,3.00,3.40,3.80,4.20,5.00,6.00/*,6.50,7.00,8.00,10.0*/});
  std::vector<Double_t> binsPt3({0.00,0.40,0.80,1.20,1.60,2.00,2.40,2.80,3.40,4.00,5.00,6.00/*,6.50,7.00,8.00,10.0*/});
  std::vector<Double_t> binsPt4({0.00,0.40,0.80,1.20,1.60,2.00,2.50,3.00,3.50,4.00,4.50,5.00,6.00/*,6.50,7.00,8.00,10.0*/});                               

 
  Double_t arbScalingccbar = 1.0908;
  Double_t arbScalingbbbar = 1.0595;
  TString relUncertaintiesccbar = "0.21184:0.33266";
  TString relUncertaintiesbbbar = "0.24349:0.22888";
  std::vector<TString> cocktail_files;
  cocktail_files.push_back("./input/cocktail/LF-pPb_502_pt200_ratios_raw_scaled.root");
  cocktail_files.push_back("./input/cocktail/LF-pPb_502_pt200_ratios-Low_raw_scaled.root");
  cocktail_files.push_back("./input/cocktail/LF-pPb_502_pt200_ratios-High_raw_scaled.root");
  std::vector<TString> cocktail_histograms;
  cocktail_histograms.push_back("Mee_Ptee_Pion_angleSmeared:Mee_Ptee_Eta_angleSmeared:Mee_Ptee_EtaPrime_angleSmeared:Mee_Ptee_Rho_angleSmeared:Mee_Ptee_Omega_angleSmeared:Mee_Ptee_OmegaDalitz_angleSmeared:Mee_Ptee_Phi_angleSmeared:Mee_Ptee_PhiDalitz_angleSmeared:Mee_Ptee_JPsi_angleSmeared");
  
  LmCocktailMan* cocktmanReso = new LmCocktailMan(cocktail_files.at(0),cocktail_histograms.at(0),2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
  cocktmanReso->SetInputfilesAndHistsLow(cocktail_files.at(1),cocktail_histograms.at(0));
  cocktmanReso->SetInputfilesAndHistsHigh(cocktail_files.at(2),cocktail_histograms.at(0));
  cocktmanReso->SetInputlists("Mee_Ptee_angleSmeared");
  cocktmanReso->Process(LmCocktailMan::kLFsum);
  
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
    
  
  std::vector< std::vector<LmManager*> >    mgrVec(9),mgrVecSys(9);
  std::vector< std::vector<LmBackground*> > bkgVec(9),bkgVecSys(9);
  std::vector< std::vector<LmSignal*> >     sigVec(9),sigVecSys(9);
  
  Printf("______ process input  ______");
  ProcessSingleInputs(combcconfig,combeconfig1,"InvMass_PairPt_PhivPair", mgrVec.at(0), bkgVec.at(0), sigVec.at(0),&mgrVecSys.at(0),&bkgVecSys.at(0),&sigVecSys.at(0),LmBackground::kHybrid, 1, vTempUS,vTempLS,vNormValPhiV);
  ProcessSingleInputs(combcconfig,combeconfig2,"InvMass_PairPt_PhivPair", mgrVec.at(1), bkgVec.at(1), sigVec.at(1),&mgrVecSys.at(1),&bkgVecSys.at(1),&sigVecSys.at(1),LmBackground::kHybrid, 1, vTempUS,vTempLS,vNormValPhiV);
  ProcessSingleInputs(combcconfig,combeconfig3,"InvMass_PairPt_PhivPair", mgrVec.at(2), bkgVec.at(2), sigVec.at(2),&mgrVecSys.at(2),&bkgVecSys.at(2),&sigVecSys.at(2),LmBackground::kHybrid, 1, vTempUS,vTempLS,vNormValPhiV);
  ProcessSingleInputs(    cconfig,    econfig1,"InvMass_PairPt_PhivPair", mgrVec.at(3), bkgVec.at(3), sigVec.at(3),&mgrVecSys.at(3),&bkgVecSys.at(3),&sigVecSys.at(3),LmBackground::kHybrid, 1, vTempUS,vTempLS,vNormValPhiV);
  ProcessSingleInputs(combcconfig,combeconfig1,"InvMass_PairPt_PhivPair", mgrVec.at(4), bkgVec.at(4), sigVec.at(4),&mgrVecSys.at(4),&bkgVecSys.at(4),&sigVecSys.at(4),LmBackground::kHybrid, 0, vTempUS,vTempLS,vNormValPhiV);
  ProcessSingleInputs(combcconfig,combeconfig1,"InvMass_PairPt_PhivPair", mgrVec.at(5), bkgVec.at(5), sigVec.at(5),&mgrVecSys.at(5),&bkgVecSys.at(5),&sigVecSys.at(5),LmBackground::kHybrid, 2, vTempUS,vTempLS,vNormValPhiV);
  ProcessSingleInputs(combcconfig,combeconfig1,"InvMass_PairPt_PhivPair", mgrVec.at(6), bkgVec.at(6), sigVec.at(6),&mgrVecSys.at(6),&bkgVecSys.at(6),&sigVecSys.at(6),LmBackground::kGeom,   1, vTempUS,vTempLS,vNormValPhiV);
  ProcessSingleInputs(combcconfig,combeconfig1,"InvMass_PairPt_PhivPair", mgrVec.at(7), bkgVec.at(7), sigVec.at(7),&mgrVecSys.at(7),&bkgVecSys.at(7),&sigVecSys.at(7),LmBackground::kArith,  1, vTempUS,vTempLS,vNormValPhiV);
  ProcessSingleInputs(  cconfigPF,    econfig1,"InvMass_PairPt_PhivPair", mgrVec.at(8), bkgVec.at(8), sigVec.at(8),&mgrVecSys.at(8),&bkgVecSys.at(8),&sigVecSys.at(8),LmBackground::kHybrid, 1, vTempUS,vTempLS,vNormValPhiV);
  Printf("______ DONE WITH SINGLE INPUT PROCESSING ______");

  LmSignal *sig1  = GetSignal(sigVec.at(0),sigVecSys.at(0),refCutset);
  LmSignal *sig2  = GetSignal(sigVec.at(1),sigVecSys.at(1),refCutset);
  LmSignal *sig3  = GetSignal(sigVec.at(2),sigVecSys.at(2),refCutset);
  LmSignal *sig4  = GetSignal(sigVec.at(3),sigVecSys.at(3),refCutset);
  LmSignal *sig5  = GetSignal(sigVec.at(4),sigVecSys.at(4),refCutset);
  LmSignal *sig6  = GetSignal(sigVec.at(5),sigVecSys.at(5),refCutset);
  LmSignal *sig7  = GetSignal(sigVec.at(6),sigVecSys.at(6),refCutset);
  LmSignal *sig8  = GetSignal(sigVec.at(7),sigVecSys.at(7),refCutset);
  LmSignal *sig9  = GetSignal(sigVec.at(8),sigVecSys.at(8),refCutset);
  LmSignal *sig10 = GetSignal(sigVec.at(0),sigVecSys.at(0),refCutset,kFALSE);
  LmSignal *sig11 = GetSignal(sigVec.at(0),sigVecSys.at(0),refCutset,kTRUE);
  LmSignal *sig12 = GetSignal(sigVec.at(0),sigVecSys.at(0),-1,kFALSE);
  LmSignal *sig13 = GetSignal(sigVec.at(0),sigVecSys.at(0),-1,kTRUE);

  LmHandler *han1 = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  han1->SetBinningMee(0,&binsMee);
  han1->SetBinningPtee(0,&binsPt1);
  han1->SetBinningPtee(1,&binsPt2);
  han1->SetBinningPtee(2,&binsPt3);
  han1->SetBinningPtee(3,&binsPt4);
  han1->AttachSignal(*(sig1),"std eff");
  han1->AttachSignal(*(sig2),"all eff");
  han1->AttachSignal(*(sig3),"LHC14g3b");
  han1->Process(LmHandler::kCompare);
  PlotHandler(han1,"eff");

  LmHandler *han2 = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  han2->SetBinningMee(0,&binsMee);
  han2->SetBinningPtee(0,&binsPt1);
  han2->SetBinningPtee(1,&binsPt2);
  han2->SetBinningPtee(2,&binsPt3);
  han2->SetBinningPtee(3,&binsPt4);
  han2->AttachSignal(*(sig1),"combined");
  han2->AttachSignal(*(sig4),"no pf");
  han2->AttachSignal(*(sig9),"pf");
  han2->Process(LmHandler::kCompare);
  PlotHandler(han2,"pf",kTRUE,kTRUE);

  LmHandler *han3 = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  han3->SetBinningMee(0,&binsMee);
  han3->SetBinningPtee(0,&binsPt1);
  han3->SetBinningPtee(1,&binsPt2);
  han3->SetBinningPtee(2,&binsPt3);
  han3->SetBinningPtee(3,&binsPt4);
  han3->AttachSignal(*(sig1),"phiV flat cor");
  han3->AttachSignal(*(sig5),"phiV no cut");
  han3->AttachSignal(*(sig6),"phiV template cor");
  han3->Process(LmHandler::kCompare);
  PlotHandler(han3,"phiVcor");
  
  LmHandler *han4 = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  han4->SetBinningMee(0,&binsMee);
  han4->SetBinningPtee(0,&binsPt1);
  han4->SetBinningPtee(1,&binsPt2);
  han4->SetBinningPtee(2,&binsPt3);
  han4->SetBinningPtee(3,&binsPt4);
  han4->AttachSignal(*(sig1),"hybrid");
  han4->AttachSignal(*(sig7),"geom");
  han4->AttachSignal(*(sig8),"arith");
  han4->Process(LmHandler::kCompare);
  PlotHandler(han4,"bgType");
 
  LmHandler *han5 = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  han5->SetBinningMee(0,&binsMee);
  han5->SetBinningPtee(0,&binsPt1);
  han5->SetBinningPtee(1,&binsPt2);
  han5->SetBinningPtee(2,&binsPt3);
  han5->SetBinningPtee(3,&binsPt4);
  han5->AttachSignal(*(sig10) ,"cut6 (ave sys)");
  han5->AttachSignal(*(sig11),"cut6 (w. ave sys)");
  han5->AttachSignal(*(sig12),"ave (ave sys)");
  han5->AttachSignal(*(sig13),"w. ave (w. ave sys)");
  han5->Process(LmHandler::kCompare);
  PlotHandler(han5,"signalCalculation");

  LmHandler *hanCocktailComp = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin, plotPteeMax);
  hanCocktailComp->AttachSignal(*(sig1),"std data");
  hanCocktailComp->SetBinningMee (0,&binsMee);
  hanCocktailComp->SetBinningPtee(0,&binsPt1);
  hanCocktailComp->SetBinningPtee(1,&binsPt2);
  hanCocktailComp->SetBinningPtee(2,&binsPt3);
  hanCocktailComp->SetBinningPtee(3,&binsPt4);
  
  hanCocktailComp->SetCocktail(&cocktail); // attach complete cocktail to handler. call cockt00->Process() before!
  hanCocktailComp->Process(LmHandler::kCocktail);
  hanCocktailComp->SetDrawStyleCocktail("hist");
  hanCocktailComp->SetDrawStyleCocktailErr("hist E2");
  PlotHandler(hanCocktailComp,"comparison");

/*  
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
//  
//  mgrVec.clear();
//  bkgVec.clear();
//  sigVec.clear();
//  Printf("______ process input  ______");
//  ProcessSingleInputs(cconfig1,econfig1,"InvMass_PairPt_PhivPair",      3,"ToyCorr",     mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
//  ProcessSingleInputs(cconfig1,"",     "InvMass_PairPt_PhivPair_EffCor",3,"PtEtaPhiCorr",mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
//  ProcessSingleInputs(cconfig2,"",     "InvMass_PairPt_PhivPair_EffCor",3,"PtPhiCorr",   mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
//  ProcessSingleInputs(cconfig3,"",     "InvMass_PairPt_PhivPair_EffCor",3,"PtEtaCorr",   mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
//  ProcessSingleInputs(cconfig4,"",     "InvMass_PairPt_PhivPair_EffCor",3,"PtCorr",      mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
//  Printf("______ DONE WITH SINGLE INPUT PROCESSING ______");
//  
//  LmHandler *han2 = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
//  han2->SetBinningMee(0,&binsMee);
//  han2->SetBinningPtee(0,&binsPt1);
//  han2->SetBinningPtee(1,&binsPt2);
//  han2->SetBinningPtee(2,&binsPt3);
//  han2->SetBinningPtee(3,&binsPt4);
//  han2->AttachSignal(*(sigVec.at(0)),sigVec.at(0)->GetName());
//  han2->AttachSignal(*(sigVec.at(1)),sigVec.at(1)->GetName());
//  han2->AttachSignal(*(sigVec.at(2)),sigVec.at(2)->GetName());
//  han2->AttachSignal(*(sigVec.at(3)),sigVec.at(3)->GetName());
//  han2->AttachSignal(*(sigVec.at(4)),sigVec.at(4)->GetName());
//  han2->SetDoRatio();
//  han2->SetPlotRangeRatio(0.5,1.5);
//  han2->Process(LmHandler::kCompare);
//  han2->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnMee ,"+_OnTheFlyCorrection");
//  han2->SetPlotRangeY(1.0001e-6,0.9999e-0);
//  han2->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
//  han2->SetPlotRangeY(1.0001e-7,0.9999e-2);
//  han2->PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
//  han2->SetPlotRangeY(4.0001e-8,4.9999e-3);
//  han2->PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
//  han2->SetPlotRangeY(1.0001e-7,0.9999e-3);
//  han2->PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
//  
//  
//  LmHandler CocktailHandler2(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin, plotPteeMax);
//  CocktailHandler2.SetBinningMee(0,&binsMee);
//  CocktailHandler2.SetBinningPtee(0,&binsPt1);
//  CocktailHandler2.SetBinningPtee(1,&binsPt2);
//  CocktailHandler2.SetBinningPtee(2,&binsPt3);
//  CocktailHandler2.SetBinningPtee(3,&binsPt4);
//  CocktailHandler2.AttachSignal(*(sigVec.at(0)),sigVec.at(0)->GetName());
//  CocktailHandler2.AttachSignal(*(sigVec.at(1)),sigVec.at(1)->GetName());
//  CocktailHandler2.AttachSignal(*(sigVec.at(2)),sigVec.at(2)->GetName());
//  CocktailHandler2.AttachSignal(*(sigVec.at(3)),sigVec.at(3)->GetName());
//  
//  CocktailHandler2.SetCocktail(&cocktail);
//  CocktailHandler2.SetDrawStyleCocktail("hist");
//  CocktailHandler2.SetDrawStyleCocktailErr("hist E2");
////  CocktailHandler2.SetPlotRangeRatio(0.2, 1.799);
////  CocktailHandler2.SetDivideOption("0");
//  CocktailHandler2.SetDoRatio(kFALSE);
////  CocktailHandler2.SetPlotRangeY(1.0001e-6,0.4999e-0);
//  CocktailHandler2.Process(LmHandler::kCompare);
//  CocktailHandler2.Process(LmHandler::kCocktail);
//  
//  CocktailHandler2.PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnMee ,"+_OnTheFlyCorrection");
//  CocktailHandler2.SetPlotRangeY(1.0001e-6,0.9999e-0);
//  CocktailHandler2.PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
//  CocktailHandler2.SetPlotRangeY(1.0001e-7,0.9999e-2);
//  CocktailHandler2.PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
//  CocktailHandler2.SetPlotRangeY(4.0001e-8,4.9999e-3);
//  CocktailHandler2.PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
//  CocktailHandler2.SetPlotRangeY(1.0001e-7,0.9999e-3);
//  CocktailHandler2.PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee,"+_OnTheFlyCorrection");
//  
//
//  mgrVec.clear();
//  bkgVec.clear();
//  sigVec.clear();
//  Printf("______ process input  ______");
//  ProcessSingleInputs(cconfig1,econfig1,"InvMass_PairPt_PhivPair",      3,"ToyCor1",       mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
//  ProcessSingleInputs(cconfig1,econfig2,"InvMass_PairPt_PhivPair",      3,"ToyCor2",       mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
//  ProcessSingleInputs(cconfig1,econfig3,"InvMass_PairPt_PhivPair",      3,"ToyCorLHC14g3b",mgrVec,bkgVec,sigVec,n_mee_bin1,mee_bin1,n_ptee_bin1,ptee_bin1,LmBackground::kHybrid);
//  Printf("______ DONE WITH SINGLE INPUT PROCESSING ______");
//  
//  LmHandler *han3 = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
//  han3->SetBinningMee(0,&binsMee);
//  han3->SetBinningPtee(0,&binsPt1);
//  han3->SetBinningPtee(1,&binsPt2);
//  han3->SetBinningPtee(2,&binsPt3);
//  han3->SetBinningPtee(3,&binsPt4);
//  han3->AttachSignal(*(sigVec.at(0)),sigVec.at(0)->GetName());
//  han3->AttachSignal(*(sigVec.at(1)),sigVec.at(1)->GetName());
//  han3->AttachSignal(*(sigVec.at(2)),sigVec.at(2)->GetName());
//  han3->SetDoRatio();
//  han3->SetPlotRangeRatio(0.5,1.5);
//  han3->Process(LmHandler::kCompare);
//  han3->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnMee ,"+_EffComp");
//  han3->SetPlotRangeY(1.0001e-6,0.9999e-0);
//  han3->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,"+_EffComp");
//  han3->SetPlotRangeY(1.0001e-7,0.9999e-2);
//  han3->PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee,"+_EffComp");
//  han3->SetPlotRangeY(4.0001e-8,4.9999e-3);
//  han3->PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee,"+_EffComp");
//  han3->SetPlotRangeY(1.0001e-7,0.9999e-3);
//  han3->PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee,"+_EffComp");
// 

  
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

void ProcessSingleInputs(std::vector<TString> vConfig, std::vector<TString> vEffiConfig, TString inputhist,
                         std::vector<LmManager*> &mgrVec,std::vector<LmBackground*> &bkgVec,std::vector<LmSignal*> &sigVec,
                         std::vector<LmManager*> *mgrVec_sys, std::vector<LmBackground*> *bkgVec_sys, std::vector<LmSignal*> *sigVec_sys,
                         LmBackground::enType type,
                         Int_t corPhiV, std::vector<TH3D*> &vTemlatesUS, std::vector<TH3D*> &vTemlatesLS, std::vector<Double_t> vNormValPhiV)
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
    if(corPhiV == 0)
      mgr->SetEnableExclusionCutZ(LmManager::kNoCut);    
    else if(corPhiV == 1){
      mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
      mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
      mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
      mgr->SetEnableExclusionCutZ(LmManager::kFlatCorr);
    }
    else if(corPhiV == 2){ 
      mgr->SetTemplateNormRegion(0.,vNormValPhiV.at(ic));
      mgr->SetExclusionZTemplates(vTemlatesUS.at(ic),vTemlatesLS.at(ic));
      mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
      mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
      mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
      mgr->SetEnableExclusionCutZ(LmManager::kTemplUnsub);
    }
    mgr->SetRebinning2D(n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
    if(vEffiConfig.at(ic).Length() > 0){
      mgr->SetEffifileAndHists(arr->At(0)->GetName(),arr->At(1)->GetName(),arr->At(2)->GetName());
      mgr->SetEnableEffiCorr(kTRUE);
    }
    else 
      mgr->SetEnableEffiCorr(kFALSE);
    mgr->Process();
    mgr->SetNeventsPhysSel(fTriggerEff*mgr->GetNeventsPhysSel());
    mgr->SetEtaRange(-0.8,0.8);
    mgr->SetPtRange(0.2,-1.);
    mgrVec.push_back(mgr);
    
    LmBackground* bkg = new LmBackground(*(mgrVec.at(ic)),Form("bg_cut%2d",ic+1));
    bkg->SetRfactorUnityRange(1.);
    bkg->Process(type);
    bkgVec.push_back(bkg);
    
    LmSignal* sig = new LmSignal(*(mgrVec.at(ic)), *(bkgVec.at(ic)), Form("sig_cut %2d", ic+1));
    sig->SetDoNormBinwidth(kDoNormBinwidth);
    sig->SetDoNormNevents(kDoNormNevents);
    sig->Process(LmSignal::kStd);
    sigVec.push_back(sig);
    
    if(!(mgrVec_sys&&bkgVec_sys&&sigVec_sys)) continue;
    
    LmManager* mgr_sys = new LmManager(const_cast<char*>(vConfig.at(ic).Data())); // TODO: input style to be optimized
    mgr_sys->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
    if(corPhiV == 0)
      mgr_sys->SetEnableExclusionCutZ(LmManager::kNoCut);    
    else if(corPhiV == 1){
      mgr_sys->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
      mgr_sys->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
      mgr_sys->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
      mgr_sys->SetEnableExclusionCutZ(LmManager::kFlatCorr);
    }
    else if(corPhiV == 2){ 
      mgr_sys->SetTemplateNormRegion(0.,vNormValPhiV.at(ic));
      mgr_sys->SetExclusionZTemplates(vTemlatesUS.at(ic),vTemlatesLS.at(ic));
      mgr_sys->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
      mgr_sys->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
      mgr_sys->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
      mgr_sys->SetEnableExclusionCutZ(LmManager::kTemplUnsub);
    }
    mgr_sys->SetRebinning2D(n_mee_bin_systematic, mee_bin_systematic, n_ptee_bin_systematic, ptee_bin_systematic);
    if(vEffiConfig.at(ic).Length() > 0){
      mgr_sys->SetEffifileAndHists(arr->At(0)->GetName(),arr->At(1)->GetName(),arr->At(2)->GetName());
      mgr_sys->SetEnableEffiCorr(kTRUE);
    }
    else 
      mgr_sys->SetEnableEffiCorr(kFALSE);
    mgr_sys->Process();
    mgr_sys->SetNeventsPhysSel(fTriggerEff*mgr_sys->GetNeventsPhysSel());
    mgr_sys->SetEtaRange(-0.8,0.8);
    mgr_sys->SetPtRange(0.2,-1.);
    mgrVec_sys->push_back(mgr_sys);
    
    LmBackground* bkg_sys = new LmBackground(*(mgrVec_sys->at(ic)),Form("bg_systematic_cut%2d",ic+1));
    bkg_sys->SetRfactorUnityRange(1.);
    bkg_sys->Process(type);
    bkgVec_sys->push_back(bkg_sys);
    
    LmSignal* sig_sys = new LmSignal(*(mgrVec_sys->at(ic)), *(bkgVec_sys->at(ic)), Form("sig_systematic_cut %2d", ic+1));
    sig_sys->SetDoNormBinwidth(kDoNormBinwidth);
    sig_sys->SetDoNormNevents(kDoNormNevents);
    sig_sys->Process(LmSignal::kStd);
    sigVec_sys->push_back(sig_sys);
  }

}

LmSignal* GetSignal(std::vector<LmSignal*> &sigVec,std::vector<LmSignal*> &sigVec_sys, Int_t iSig, Bool_t bWeightedAve)
{
  LmHandler *hanSystematic = new  LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, plotMeeMax,plotPteeMin, plotPteeMax);
  for(UInt_t iCuts = 0; iCuts < sigVec_sys.size(); ++iCuts)
    hanSystematic->AttachSignal(*(sigVec_sys.at(iCuts)), Form("cut%02d",iCuts+1));
  if(bWeightedAve) hanSystematic->Process(LmHandler::kSystematic_WeightedAverage);
  else             hanSystematic->Process(LmHandler::kSystematic_Average);
//  hanSystematic->Process(LmHandler::kCompare);

  LmHandler* han = new  LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, plotMeeMax,plotPteeMin, plotPteeMax);
  if(iSig < 0){ 
    LmHandler* hanSignals = new  LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, plotMeeMax,plotPteeMin, plotPteeMax);
    for(UInt_t iCuts = 0; iCuts < sigVec.size(); ++iCuts)
      hanSignals->AttachSignal(*(sigVec.at(iCuts)), Form("cut%02d",iCuts+1));
    if(bWeightedAve) hanSignals->Process(LmHandler::kAverage);
    else             hanSignals->Process(LmHandler::kWeightedAverage);
    han->AttachSignal(*(hanSignals->GetLmSigAverage()),"data");
  }
  else
    han->AttachSignal(*(sigVec.at(iSig)),"data");
  han->GetLmSignalI(0)->SetSymmetricRelSystematics(hanSystematic->GetRelSystematics());
  han->GetLmSignalI(0)->Process(LmSignal::kSystematic);  

  return han->GetLmSignalI(0);
}

void PlotHandler(LmHandler *han, TString name, Bool_t bSoverB, Bool_t bSignif)
{
  if(bSoverB){
    for(UInt_t iProj = 0; iProj < binsPtee_forMee.size()-1; ++iProj)
      han->PrintCompare(LmSignal::kSoverB,iProj, LmBaseSignal::kProjOnMee,Form("+_%s",name.Data()));
    han->PrintCompare(LmSignal::kSoverB,0, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
    han->PrintCompare(LmSignal::kSoverB,1, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
    han->PrintCompare(LmSignal::kSoverB,2, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
    han->PrintCompare(LmSignal::kSoverB,3, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data())); 
  }
  if(bSignif){
    for(UInt_t iProj = 0; iProj < binsPtee_forMee.size()-1; ++iProj)
      han->PrintCompare(LmSignal::kSignif,iProj, LmBaseSignal::kProjOnMee,Form("+_%s",name.Data()));
    han->PrintCompare(LmSignal::kSignif,0, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
    han->PrintCompare(LmSignal::kSignif,1, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
    han->PrintCompare(LmSignal::kSignif,2, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
    han->PrintCompare(LmSignal::kSignif,3, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data())); 
  }
  han->SetPlotRangeY(1.0001e-6,0.9999e-0);
  for(UInt_t iProj = 0; iProj < binsPtee_forMee.size()-1; ++iProj)
    han->PrintCompare(LmSignal::kSubSig,iProj, LmBaseSignal::kProjOnMee,Form("+_%s",name.Data()));
  han->SetPlotRangeY(1.0001e-6,0.9999e-0);
  han->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
  han->SetPlotRangeY(1.0001e-7,0.9999e-2);
  han->PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
  han->SetPlotRangeY(4.0001e-8,4.9999e-3);
  han->PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
  han->SetPlotRangeY(1.0001e-7,0.9999e-3);
  han->PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));  
}


