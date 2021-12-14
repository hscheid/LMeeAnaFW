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
#include "theo_pp.h"

#include "LmManager.h"
#include "LmBackground.h"
#include "LmSignal.h"
#include "LmHandler.h"
#include "LmHelper.h"
#include "LmFileManager.h"

void PlotHandler(LmHandler *han, TString name, Bool_t bSoverB=kFALSE, Bool_t bSignif=kFALSE);
LmSignal* GetSignal(std::vector<LmSignal*> &sigVec,std::vector<LmSignal*> &sigVec_sys, Int_t iSig=-1);

void ProcessSingleInputs(std::vector<TString> vConfig, std::vector<TString> vEffiConfig, TString name,
                         std::vector<LmManager*> &mgrVec,std::vector<LmBackground*> &bkgVec,std::vector<LmSignal*> &sigVec,
                         std::vector<LmManager*> *mgrVec_sys, std::vector<LmBackground*> *bkgVec_sys, std::vector<LmSignal*> *sigVec_sys,
                         LmBackground::enType type, std::vector<Double_t> vCutPhiVabove);
                         
Bool_t cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}
Int_t Plot();

void MultiplyByBinwidth(TH1D *h);
Bool_t kpt400 = kFALSE;

Int_t main(int argc, char * argv[])
{
 if(cmdOptionExists(argv, argv+argc, "-pt400")) kpt400 = kTRUE;
 
 return Plot();
}

Int_t Plot()
{
  //UInt_t Ncuts = 23; //normal case
  UInt_t Ncuts = 28;
  Bool_t bDsigmaDy(kFALSE);
  Bool_t kGenBin(kFALSE);
  TString xtra("_pt200");
  if(kpt400) xtra = "_pt400";
  TString system("pp");
  gErrorIgnoreLevel = kWarning;
  
  TString tmp = "";
  if(kGenBin) tmp = "_GenBin";
  
  std::vector<TString> cconfigLHC10,econfigLHC10;
  std::vector<TString> cconfigLHC10b,econfigLHC10b;
  std::vector<TString> cconfigLHC10c,econfigLHC10c;
  std::vector<TString> cconfigLHC10d,econfigLHC10d;
  std::vector<TString> cconfigLHC10e,econfigLHC10e;
  std::vector<TString> cconfigLHC10f,econfigLHC10f;
  std::vector<Double_t> vCutPhiVabove;
  
  for(UInt_t i = 1; i <= Ncuts; ++i){

    if((i==11) || (i==18) || (i==16) || (i==20) || (i==21) || (i==22)) continue;
    
    if(kpt400){
      cconfigLHC10.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10_pt400.root:NoList:"+Form("cut%02d",i) );
      econfigLHC10.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10_pt400.root:NGenPairs_pt400:NRecPairsCombined_Eff_cut%02d_pt400",i) );
      cconfigLHC10b.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10b_pt400.root:NoList:"+Form("cut%02d",i) );
      econfigLHC10b.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10b_pt400.root:NGenPairs_pt400:NRecPairsCombined_Eff_cut%02d_pt400",i) );
      cconfigLHC10c.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10c_pt400.root:NoList:"+Form("cut%02d",i) );
      econfigLHC10c.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10c_pt400.root:NGenPairs_pt400:NRecPairsCombined_Eff_cut%02d_pt400",i) );
      cconfigLHC10d.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10d_pt400.root:NoList:"+Form("cut%02d",i) );
      econfigLHC10d.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10d_pt400.root:NGenPairs_pt400:NRecPairsCombined_Eff_cut%02d_pt400",i) );
      cconfigLHC10e.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10e_pt400.root:NoList:"+Form("cut%02d",i) );
      econfigLHC10e.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10e_pt400.root:NGenPairs_pt400:NRecPairsCombined_Eff_cut%02d_pt400",i) );
      cconfigLHC10f.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10f_pt400.root:NoList:"+Form("cut%02d",i) );
      econfigLHC10f.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10f_pt400.root:NGenPairs_pt400:NRecPairsCombined_Eff_cut%02d_pt400",i) );
      vCutPhiVabove.push_back( 1./2.*TMath::Pi() );
    }
    else{
      //cconfigLHC10 .push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10_pt200.root:NoList:"+Form("cut%02d",i) );
      cconfigLHC10 .push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10_940_944_Runlist2_pt200.root:NoList:"+Form("cut%02d",i) );
      econfigLHC10 .push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_628_LHC10_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //econfigLHC10 .push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10_607_611_Runlist2.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //econfigLHC10 .push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //cconfigLHC10b.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10b_pt200.root:NoList:"+Form("cut%02d",i) );
      cconfigLHC10b.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10b_940_944_Runlist2_pt200.root:NoList:"+Form("cut%02d",i) );
      econfigLHC10b.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_628_LHC10b_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //econfigLHC10b.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10b_607_611_Runlist2.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //econfigLHC10b.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10b_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //cconfigLHC10c.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10c_pt200.root:NoList:"+Form("cut%02d",i) );
      cconfigLHC10c.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10c_940_944_Runlist2_pt200.root:NoList:"+Form("cut%02d",i) );
      econfigLHC10c.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_628_LHC10c_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //econfigLHC10c.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10c_607_611_Runlist2.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //econfigLHC10c.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10c_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //cconfigLHC10d.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10d_pt200.root:NoList:"+Form("cut%02d",i) );
      cconfigLHC10d.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10d_940_944_Runlist2_pt200.root:NoList:"+Form("cut%02d",i) );
      econfigLHC10d.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_628_LHC10d_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //econfigLHC10d.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10d_607_611_Runlist2.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //econfigLHC10d.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10d_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //cconfigLHC10e.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10e_pt200.root:NoList:"+Form("cut%02d",i) );
      cconfigLHC10e.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10e_940_944_Runlist2_pt200.root:NoList:"+Form("cut%02d",i) );
      econfigLHC10e.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_628_LHC10e_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //econfigLHC10e.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10e_607_611_Runlist2.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //econfigLHC10e.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10e_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //cconfigLHC10f.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10f_pt200.root:NoList:"+Form("cut%02d",i) );
      cconfigLHC10f.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10f_940_944_Runlist2_pt200.root:NoList:"+Form("cut%02d",i) );
      econfigLHC10f.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_628_LHC10f_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //econfigLHC10f.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10f_607_611_Runlist2.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      //econfigLHC10f.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10f_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut%02d_pt200",i) );
      vCutPhiVabove.push_back( 2. );
    }
  }

  Ncuts = Ncuts - 6;
  
  std::vector<TString> cconfigPhiVsys,econfigPhiVsys;
  std::vector<Double_t> vCutPhiVaboveSys;
  //cconfigPhiVsys.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10_pt200.root:NoList:cut06" );
  cconfigPhiVsys.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10_940_944_Runlist2_pt200.root:NoList:cut06" );
  econfigPhiVsys.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_628_LHC10_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut06_pt200") );
  //econfigPhiVsys.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10_607_611_Runlist2.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut06_pt200") );
  //econfigPhiVsys.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut06_pt200") );
  vCutPhiVaboveSys.push_back( 2. );
  cconfigPhiVsys.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10_940_944_Runlist2_pt200.root:NoList:cut06" );
  //cconfigPhiVsys.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10_pt200.root:NoList:cut06" );
  econfigPhiVsys.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_628_LHC10_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut06_pt200") );
  //econfigPhiVsys.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10_607_611_Runlist2.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut06_pt200") );
  //econfigPhiVsys.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut06_pt200") );
  vCutPhiVaboveSys.push_back( 0.8 *TMath::Pi() );
  //cconfigPhiVsys.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10_pt200.root:NoList:cut06" );
  cconfigPhiVsys.push_back( coll_system+":../../LEGOtrainOutputs/combined_LMEE_LHC10_940_944_Runlist2_pt200.root:NoList:cut06" );
  econfigPhiVsys.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_628_LHC10_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut06_pt200") );
  //econfigPhiVsys.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10_607_611_Runlist2.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut06_pt200") );
  //econfigPhiVsys.push_back( Form("../../Efficiencies/PairEfficiencies/output/ToyMCpairEfficiency_LHC10_pt200.root:NGenPairs_pt200:NRecPairsCombined_Eff_cut06_pt200") );
  vCutPhiVaboveSys.push_back( 0.5 *TMath::Pi() );
  
  
  binsPtee_forMee.push_back(0.);
  binsPtee_forMee.push_back(1.);
  binsPtee_forMee.push_back(2.);
  binsPtee_forMee.push_back(3.);
  binsPtee_forMee.push_back(5.);
  binsPtee_forMee.push_back(8.);
  
  binsMee_forPtee.push_back(0.00);
  binsMee_forPtee.push_back(0.14);
  binsMee_forPtee.push_back(0.70);
  binsMee_forPtee.push_back(1.10);
  binsMee_forPtee.push_back(2.70);
  binsMee_forPtee.push_back(3.30);
  
  
  
  //___________________________
  LmHelper helper; // initialization of style/colors
  
  
  //_________________________________________________________________________________________________________________________________  
  LmBaseSignal::SetInputLabelZ("#it{#phi}_{V}","rad");
  std::vector<Double_t> binsMee1({0.00/*,0.02,0.05*/,0.04,0.09,0.14,0.19,0.24,0.29,0.34,0.39,0.44,0.50,
//  std::vector<Double_t> binsMee1({0.00,0.02,0.05,0.09,0.14,0.20,0.30,0.40,0.50,
                                 0.60,0.70,0.75,0.80,0.95,1.00,1.05,1.10,1.40,
                                 1.70,2.00,2.40,2.70,3.00,3.10,3.30,3.50,4.00 });
                                 
//  std::vector<Double_t> binsMee1({0.00,0.02,0.05,0.09,0.14,0.20,0.30,0.40,0.50,
//                                 0.60,0.70,0.75,0.80,0.95,1.00,1.05,1.10,1.40,
//                                 1.70,2.00,2.40,2.80,3.00,3.05,3.10,3.30,3.50,4.00 });
//  std::vector<Double_t> binsMee2({0.00,0.02,0.05,0.09,0.14,0.20,0.30,0.40,0.50,
//                                  0.60,0.70,0.75,0.80,0.95,1.00,1.05,1.10,1.40,
//                                  1.70,2.00,2.40,2.80,3.00,3.05,3.10,3.30,3.50,4.00 });
//  std::vector<Double_t> binsMee3({0.00,0.02,0.05,0.09,0.14,0.20,0.30,0.40,0.50,
//                                  0.60,0.70,0.75,0.80,0.95,1.00,1.05,1.10,1.40,
//                                  1.70,2.00,2.40,2.80,3.00,3.05,3.10,3.30,3.50,4.00 });
//  std::vector<Double_t> binsMee4({0.00,0.02,0.05,0.09,0.14,0.20,0.30,0.40,0.50,
//                                  0.60,0.70,0.75,0.80,0.95,1.00,1.05,1.10,1.40,
//                                  1.70,2.00,2.40,2.80,3.00,3.05,3.10,3.30,3.50,4.00 });
//  std::vector<Double_t> binsMee5({0.00,0.02,0.05,0.09,0.20,0.40,0.75,0.90,1.05,1.40,
//                                  1.80,2.60,3.00,3.05,3.10,3.30,4.00 });

  
  std::vector<Double_t> binsMee2(binsMee1),binsMee3(binsMee1),binsMee4(binsMee1),binsMee5(binsMee1);
                             
  std::vector<Double_t> binsPt1({0.00,0.10,0.20,0.30,0.40,0.50,0.60,0.70,0.80,0.90,1.00,1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,
                                 2.10,2.20,2.30,2.40,2.50,2.60,2.70,2.80,2.90,3.00,3.20,3.40,3.60,3.80,4.00,4.50,5.00,6.00,8.00,10.0});
//  std::vector<Double_t> binsPt2({0.00,0.30,0.60,1.00,1.40,1.80,2.20,2.60,3.00/*,3.60*/,4.50,6.00,8.00,10.0});
//  std::vector<Double_t> binsPt3({0.00,0.40,0.80,1.20,1.60,2.00,2.40,2.80,4.20,6.00,8.00,10.0});

  std::vector<Double_t> binsPt2({0.00,0.30,0.60,1.00,1.40,1.80,2.20,2.60,3.00,4.00,5.50,8.00,10.0});
  //std::vector<Double_t> binsPt2({0.00,0.40,0.80,1.20,1.60,2.00,2.40,2.80,4.00,5.50,8.00,10.0});
  std::vector<Double_t> binsPt3({0.00,0.40,0.80,1.20,1.60,2.00,2.40,2.80,4.00,5.50,8.00,10.0});
  std::vector<Double_t> binsPt4({0.00,0.40,0.80,1.20,1.60,2.00,2.40,2.80,4.20,6.00,8.00,10.0});                            
  std::vector<Double_t> binsPt5({0.00,1.00,2.00,3.00,4.00,5.00,8.00,10.0});                               
 
//  TString relUncertaintiesccbar = "0.07934:-0.07825";
//  TString relUncertaintiesbbbar = "0.22547:-0.22887";
  
  TString HFnormType = "_Normtotal";
  TString relUncertaintiesccbar = "0.08963:-0.08866";
  TString relUncertaintiesbbbar = "0.16724:-0.16724";
  if(bDsigmaDy){
    relUncertaintiesccbar = "0.12300:-0.12300";
    relUncertaintiesbbbar = "0.31100:-0.31100";
    HFnormType = "_Normmid";
  }
  
  std::vector<TString> cocktail_histograms;
//  cocktail_histograms.push_back("MeePteePion:MeePteeEta:MeePteeEtaPrime:MeePteeRho:MeePteeOmega:MeePteePhi");
  cocktail_histograms.push_back("MeePteePion:MeePteeEta:MeePteeEtaPrime:MeePteeRho:MeePteePhi");
  
  std::vector<TString> cocktail_files;
   cocktail_files.push_back("/Users/Raphaelle/Desktop/pplmeepaper/Cocktail/Try/output/LFcocktail_Raphaelle_200MeV_v5.root");
   cocktail_files.push_back("../../Cocktail/PostprocessUpdate/output/LFgen-kpp_7_ratios-Low.root");
   cocktail_files.push_back("../../Cocktail/PostprocessUpdate/output/LFgen-kpp_7_ratios-High.root");
//   cocktail_files.push_back("../../Cocktail/Postprocess/output/LFgen-kpp_7_pi0ratios-Std.root");
//   cocktail_files.push_back("../../Cocktail/Postprocess/output/LFgen-kpp_7_pi0ratios-Low.root");
//   cocktail_files.push_back("../../Cocktail/Postprocess/output/LFgen-kpp_7_pi0ratios-High.root");
   


  LmCocktailMan* cocktmanReso = new LmCocktailMan(cocktail_files.at(0),cocktail_histograms.at(0),2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
  cocktmanReso->SetInputfilesAndHistsLow(cocktail_files.at(1),cocktail_histograms.at(0));
  cocktmanReso->SetInputfilesAndHistsHigh(cocktail_files.at(2),cocktail_histograms.at(0));
  if(kpt400) cocktmanReso->SetInputlists("cocktailPt400rec");
  else       cocktmanReso->SetInputlists("cocktailPt200rec");
cocktmanReso->SetArbitraryScaling(sigmaINEL);
//  cocktmanReso->SetInputlists("cocktailPt200");
//  cocktmanReso->Process(LmCocktailMan::kLFsum);
  cocktmanReso->Process(LmCocktailMan::kResonances);
  
  std::vector<TString> omega_files;   
  omega_files.push_back("/Users/Raphaelle/Desktop/pplmeepaper/Cocktail/Try/output/LFcocktail_Raphaelle_200MeV_v5.root");
  omega_files.push_back("../../Cocktail/PostprocessUpdate/output/LFgen-kpp_7_ratios-Low.root");
  omega_files.push_back("../../Cocktail/PostprocessUpdate/output/LFgen-kpp_7_ratios-High.root");
  
  LmCocktailMan* cocktmanOmega = new LmCocktailMan(omega_files.at(0),"MeePteeOmega",2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
  cocktmanOmega->SetInputfilesAndHistsLow(omega_files.at(1),"MeePteeOmega");
  cocktmanOmega->SetInputfilesAndHistsHigh(omega_files.at(2),"MeePteeOmega");
  if(kpt400) cocktmanOmega->SetInputlists("cocktailPt400rec");
  else       cocktmanOmega->SetInputlists("cocktailPt200rec");
cocktmanOmega->SetArbitraryScaling(sigmaINEL);
//cocktmanOmega->SetArbitraryScaling(50.);
  cocktmanOmega->Process(LmCocktailMan::kResonances);
  
//  LmCocktailMan *cocktmanJpsi = new LmCocktailMan(cocktail_files.at(0),"MeePteeJPsi",2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
//  cocktmanJpsi->SetInputfilesAndHistsLow(cocktail_files.at(1),"MeePteeJPsi");
//  cocktmanJpsi->SetInputfilesAndHistsHigh(cocktail_files.at(2),"MeePteeJPsi");
//  if(kpt400) cocktmanJpsi->SetInputlists("cocktailPt400rec");
//  else       cocktmanJpsi->SetInputlists("cocktailPt200rec");
//  cocktmanJpsi->Process(LmCocktailMan::kJpsi);
  
  LmCocktailMan *cocktmanJpsi = new LmCocktailMan("../../Cocktail/PostprocessUpdate/output/LFgen-kpp_7_ratios-Std.root","MeePteeJPsi",2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
  cocktmanJpsi->SetInputfilesAndHistsLow("../../Cocktail/PostprocessUpdate/output/LFgen-kpp_7_ratios-Low.root","MeePteeJPsi");
  cocktmanJpsi->SetInputfilesAndHistsHigh("../../Cocktail/PostprocessUpdate/output/LFgen-kpp_7_ratios-High.root","MeePteeJPsi");
  if(kpt400) cocktmanJpsi->SetInputlists("cocktailPt400rec");
  else       cocktmanJpsi->SetInputlists("cocktailPt200rec");
cocktmanJpsi->SetArbitraryScaling(sigmaMB); 
  cocktmanJpsi->Process(LmCocktailMan::kJpsi);  


  LmCocktailMan *cocktmanCharm(0x0),*cocktmanBeauty(0x0);
  if(kpt400){
    cocktmanCharm  = new LmCocktailMan("../../Cocktail/Results_charm_pp7TeV.root" ,"hMeePtee_ULS_LS_eta08_pt4_Pythia"+HFnormType,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
    cocktmanBeauty = new LmCocktailMan("../../Cocktail/Results_beauty_pp7TeV.root","hMeePtee_ULS_LS_eta08_pt4_Pythia"+HFnormType,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
  }
  else{
    cocktmanCharm  = new LmCocktailMan("../../Cocktail/Results_charm_pp7TeV.root" ,"hMeePtee_ULS_LS_eta08_pt2_Pythia"+HFnormType,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
    cocktmanBeauty = new LmCocktailMan("../../Cocktail/Results_beauty_pp7TeV.root","hMeePtee_ULS_LS_eta08_pt2_Pythia"+HFnormType,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
  }
//    cocktmanCharm  = new LmCocktailMan("../../Cocktail/Preparation/output/"+system+"HeavyFlavour.root","charmPythiaPerugia2011"+xtra ,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
//    cocktmanBeauty = new LmCocktailMan("../../Cocktail/Preparation/output/"+system+"HeavyFlavour.root","beautyPythiaPerugia2011"+xtra,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
//cocktmanCharm ->SetArbitraryScaling(sigmaINEL);
//cocktmanBeauty->SetArbitraryScaling(sigmaINEL);
  cocktmanCharm ->SetRelUncertainties(relUncertaintiesccbar.Data());
  cocktmanBeauty->SetRelUncertainties(relUncertaintiesbbbar.Data());
  cocktmanCharm ->Process(LmCocktailMan::kHeavyFl);
  cocktmanBeauty->Process(LmCocktailMan::kHeavyFl);

  LmCocktailMan *cocktmanCharmPowheg(0x0),*cocktmanBeautyPowheg(0x0);
  if(kpt400){
    cocktmanCharmPowheg  = new LmCocktailMan("../../Cocktail/Results_charm_pp7TeV.root" ,"hMeePtee_ULS_LS_eta08_pt4_Powheg"+HFnormType,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
    cocktmanBeautyPowheg = new LmCocktailMan("../../Cocktail/Results_beauty_pp7TeV.root","hMeePtee_ULS_LS_eta08_pt4_Powheg"+HFnormType,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
  }
  else{
    cocktmanCharmPowheg  = new LmCocktailMan("../../Cocktail/Results_charm_pp7TeV.root" ,"hMeePtee_ULS_LS_eta08_pt2_Powheg"+HFnormType,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
    cocktmanBeautyPowheg = new LmCocktailMan("../../Cocktail/Results_beauty_pp7TeV.root","hMeePtee_ULS_LS_eta08_pt2_Powheg"+HFnormType,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
  }
//  cocktmanCharmPowheg  = new LmCocktailMan("../../Cocktail/Preparation/output/"+system+"HeavyFlavour.root","charmPowheg"+xtra ,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
//  cocktmanBeautyPowheg = new LmCocktailMan("../../Cocktail/Preparation/output/"+system+"HeavyFlavour.root","beautyPowheg"+xtra,2,n_mee_bin_c, mee_bin_c, n_ptee_bin_c, ptee_bin_c);
//cocktmanCharmPowheg ->SetArbitraryScaling(sigmaINEL);
//cocktmanBeautyPowheg->SetArbitraryScaling(sigmaINEL);
  cocktmanCharmPowheg ->SetRelUncertainties(relUncertaintiesccbar.Data());
  cocktmanBeautyPowheg->SetRelUncertainties(relUncertaintiesbbbar.Data());
  cocktmanCharmPowheg ->Process(LmCocktailMan::kHeavyFl);
  cocktmanBeautyPowheg->Process(LmCocktailMan::kHeavyFl);

  LmCocktail cocktail(LmCocktail::kpPb_MB_502);
  cocktail.AttachManager( *cocktmanReso );
  cocktail.AttachManager( *cocktmanOmega );
  cocktail.AttachManager( *cocktmanJpsi );
  cocktail.AttachManager( *cocktmanCharm );
  cocktail.AttachManager( *cocktmanBeauty );
  cocktail.Process();  
      
  LmCocktail cocktailPowheg(LmCocktail::kpPb_MB_502);
  cocktailPowheg.AttachManager( *cocktmanReso );
  cocktailPowheg.AttachManager( *cocktmanOmega );
  cocktailPowheg.AttachManager( *cocktmanJpsi );
  cocktailPowheg.AttachManager( *cocktmanCharmPowheg );
  cocktailPowheg.AttachManager( *cocktmanBeautyPowheg );
  cocktailPowheg.Process();
  
  std::vector<LmManager*>    mgrVecLHC10,mgrVecSysLHC10;
  std::vector<LmBackground*> bkgVecLHC10,bkgVecSysLHC10;
  std::vector<LmSignal*>     sigVecLHC10,sigVecSysLHC10;
  
  std::vector<LmManager*>    mgrVecLHC10b,mgrVecSysLHC10b;
  std::vector<LmBackground*> bkgVecLHC10b,bkgVecSysLHC10b;
  std::vector<LmSignal*>     sigVecLHC10b,sigVecSysLHC10b;
  
  std::vector<LmManager*>    mgrVecLHC10c,mgrVecSysLHC10c;
  std::vector<LmBackground*> bkgVecLHC10c,bkgVecSysLHC10c;
  std::vector<LmSignal*>     sigVecLHC10c,sigVecSysLHC10c;
  
  std::vector<LmManager*>    mgrVecLHC10d,mgrVecSysLHC10d;
  std::vector<LmBackground*> bkgVecLHC10d,bkgVecSysLHC10d;
  std::vector<LmSignal*>     sigVecLHC10d,sigVecSysLHC10d;
  
  std::vector<LmManager*>    mgrVecLHC10e,mgrVecSysLHC10e;
  std::vector<LmBackground*> bkgVecLHC10e,bkgVecSysLHC10e;
  std::vector<LmSignal*>     sigVecLHC10e,sigVecSysLHC10e;
  
  std::vector<LmManager*>    mgrVecLHC10f,mgrVecSysLHC10f;
  std::vector<LmBackground*> bkgVecLHC10f,bkgVecSysLHC10f;
  std::vector<LmSignal*>     sigVecLHC10f,sigVecSysLHC10f;
  
  std::vector<LmManager*>    mgrVecPhiVsys;
  std::vector<LmBackground*> bkgVecPhiVsys;
  std::vector<LmSignal*>     sigVecPhiVsys;
  
  Printf("______ process input  ______");
  ProcessSingleInputs(cconfigLHC10 ,econfigLHC10 ,"LHC10" , mgrVecLHC10 , bkgVecLHC10 , sigVecLHC10 , &mgrVecSysLHC10 , &bkgVecSysLHC10 , &sigVecSysLHC10 , LmBackground::kHybrid, vCutPhiVabove);
  ProcessSingleInputs(cconfigLHC10b,econfigLHC10b,"LHC10b", mgrVecLHC10b, bkgVecLHC10b, sigVecLHC10b, &mgrVecSysLHC10b, &bkgVecSysLHC10b, &sigVecSysLHC10b, LmBackground::kHybrid, vCutPhiVabove);
  ProcessSingleInputs(cconfigLHC10c,econfigLHC10c,"LHC10c", mgrVecLHC10c, bkgVecLHC10c, sigVecLHC10c, &mgrVecSysLHC10c, &bkgVecSysLHC10c, &sigVecSysLHC10c, LmBackground::kHybrid, vCutPhiVabove);
  ProcessSingleInputs(cconfigLHC10d,econfigLHC10d,"LHC10d", mgrVecLHC10d, bkgVecLHC10d, sigVecLHC10d, &mgrVecSysLHC10d, &bkgVecSysLHC10d, &sigVecSysLHC10d, LmBackground::kHybrid, vCutPhiVabove);
  ProcessSingleInputs(cconfigLHC10e,econfigLHC10e,"LHC10e", mgrVecLHC10e, bkgVecLHC10e, sigVecLHC10e, &mgrVecSysLHC10e, &bkgVecSysLHC10e, &sigVecSysLHC10e, LmBackground::kHybrid, vCutPhiVabove);
  ProcessSingleInputs(cconfigLHC10f,econfigLHC10f,"LHC10f", mgrVecLHC10f, bkgVecLHC10f, sigVecLHC10f, &mgrVecSysLHC10f, &bkgVecSysLHC10f, &sigVecSysLHC10f, LmBackground::kHybrid, vCutPhiVabove);
  
  ProcessSingleInputs(cconfigPhiVsys ,econfigPhiVsys ,"PhiVsys" , mgrVecPhiVsys , bkgVecPhiVsys , sigVecPhiVsys , 0x0 , 0x0 , 0x0 , LmBackground::kHybrid, vCutPhiVaboveSys);
  
  Printf("______ DONE WITH SINGLE INPUT PROCESSING ______");

  TH2D signalPhiVstd (*(sigVecPhiVsys.at(0)->GetSig2D()));
  TH2D signalPhiVsoft(*(sigVecPhiVsys.at(1)->GetSig2D()));
  TH2D signalPhiVhard(*(sigVecPhiVsys.at(2)->GetSig2D()));
  TH2D RelSysPhiVHigh(signalPhiVstd); RelSysPhiVHigh.SetName("RelSysPhiVHigh"); RelSysPhiVHigh.Reset();
  TH2D RelSysPhiVLow (signalPhiVstd); RelSysPhiVLow .SetName("RelSysPhiVLow" ); RelSysPhiVLow .Reset();
  Double_t IntPhiVstd  = signalPhiVstd .Integral(signalPhiVstd .GetXaxis()->FindBin(0.),signalPhiVstd .GetXaxis()->FindBin(0.9999),
                                                 signalPhiVstd .GetYaxis()->FindBin(0.),signalPhiVstd .GetYaxis()->FindBin(7.9999));
  Double_t IntPhiVlow  = signalPhiVhard.Integral(signalPhiVhard.GetXaxis()->FindBin(0.),signalPhiVhard.GetXaxis()->FindBin(0.9999),
                                                 signalPhiVhard.GetYaxis()->FindBin(0.),signalPhiVhard.GetYaxis()->FindBin(7.9999));
  Double_t IntPhiVhigh = signalPhiVsoft.Integral(signalPhiVsoft.GetXaxis()->FindBin(0.),signalPhiVsoft.GetXaxis()->FindBin(0.9999),
                                                 signalPhiVsoft.GetYaxis()->FindBin(0.),signalPhiVsoft.GetYaxis()->FindBin(7.9999));
  Double_t RelPhiVerrLow  = (IntPhiVstd  - IntPhiVlow)/IntPhiVstd;
  Double_t RelPhiVerrHigh = (IntPhiVhigh - IntPhiVstd)/IntPhiVstd;
  for(Int_t ix = 1; ix <= signalPhiVstd.GetNbinsX(); ++ix){
    if(signalPhiVstd.GetXaxis()->GetBinLowEdge(ix) > cutEdgesMee[0]-0.0001) break; 
    for(Int_t iy = 1; iy <= signalPhiVstd.GetNbinsY(); ++iy){
      RelSysPhiVLow .SetBinContent(ix,iy,RelPhiVerrLow);
      RelSysPhiVHigh.SetBinContent(ix,iy,RelPhiVerrHigh);
    }
  }
  

  std::vector<LmSignal*> vCombined,vCombinedSys;
  for(UInt_t i = 0; i < Ncuts; ++i){
    LmHandler *hanCombine = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
    hanCombine->AttachSignal(*(sigVecLHC10b.at(i)),Form("LHC10b_cut%02d",i+1));
    hanCombine->AttachSignal(*(sigVecLHC10c.at(i)),Form("LHC10c_cut%02d",i+1));
    hanCombine->AttachSignal(*(sigVecLHC10d.at(i)),Form("LHC10d_cut%02d",i+1));
    hanCombine->AttachSignal(*(sigVecLHC10e.at(i)),Form("LHC10e_cut%02d",i+1));
    hanCombine->AttachSignal(*(sigVecLHC10f.at(i)),Form("LHC10f_cut%02d",i+1));
    hanCombine->Process(LmHandler::kCombine);
    vCombined.push_back(hanCombine->GetLmSigCombined());
    
    LmHandler *hanCombineSys = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
    hanCombineSys->AttachSignal(*(sigVecSysLHC10b.at(i)),Form("LHC10bSys_cut%02d",i+1));
    hanCombineSys->AttachSignal(*(sigVecSysLHC10c.at(i)),Form("LHC10cSys_cut%02d",i+1));
    hanCombineSys->AttachSignal(*(sigVecSysLHC10d.at(i)),Form("LHC10dSys_cut%02d",i+1));
    hanCombineSys->AttachSignal(*(sigVecSysLHC10e.at(i)),Form("LHC10eSys_cut%02d",i+1));
    hanCombineSys->AttachSignal(*(sigVecSysLHC10f.at(i)),Form("LHC10fSys_cut%02d",i+1));
    hanCombineSys->Process(LmHandler::kCombine);
    vCombinedSys.push_back(hanCombineSys->GetLmSigCombined());
  }


  LmSignal *sigRef = GetSignal(vCombined,vCombinedSys,5);//normal case 5
  //LmSignal *sigRef = GetSignal(vCombined,vCombinedSys,27); 27 is not 27 anymore..need to look how many cuts were removed
  sigRef->SetRelSystematicsLow (&RelSysPhiVLow);
  sigRef->SetRelSystematicsHigh(&RelSysPhiVHigh);
  sigRef->Process(LmSignal::kSystematic);


//  LmSignal *sig    = GetSignal(vCombined,vCombinedSys,-1);
//  sig->SetRelSystematicsLow (&RelSysPhiVLow);
//  sig->SetRelSystematicsHigh(&RelSysPhiVHigh);
//  sig->Process(LmSignal::kSystematic);
{  
  TFile fOut(Form("./%sData%s.root",system.Data(),xtra.Data()),"RECREATE");
  fOut.cd();
  TH2D signal    (*(sigRef->GetSig2D()));
  TH2D signalLow (*(sigRef->GetSystematicLow()));
  TH2D signalHigh(*(sigRef->GetSystematicHigh()));
  signal    .SetName("signal");
  signalLow .SetName("systematicLow");
  signalHigh.SetName("systematicHigh");
  for(Int_t ix = 0; ix <= signal.GetNbinsX(); ++ix){
    for(Int_t iy = 0; iy <= signal.GetNbinsY(); ++iy){
      signalLow .SetBinError(ix,iy,signal.GetBinError(ix,iy));
      signalHigh.SetBinError(ix,iy,signal.GetBinError(ix,iy));
    }
  }
  Double_t nEv = sigRef->GetNeventsPhysSel();
  signal    .Scale(1./nEv);
  signalLow .Scale(1./nEv);
  signalHigh.Scale(1./nEv);
  
  signal    .Write();
  signalLow .Write();
  signalHigh.Write();
  fOut.Close();
}  
//  LmSignal *sigPreCombinedRef = GetSignal(sigVecLHC10,sigVecSysLHC10,5);
//  LmSignal *sigPreCombined    = GetSignal(sigVecLHC10,sigVecSysLHC10,-1);
  
  LmHandler *han = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
//  han->AttachSignal(*(sig), "average");
  han->AttachSignal(*(sigRef), "cut06");
//  han->AttachSignal(*(sigPreCombined), "average (combined processed)");
//  han->AttachSignal(*(sigPreCombinedRef), "cut06 (combined processed)");
  
  han->SetBinningMee(0,&binsMee1);
  han->SetBinningMee(1,&binsMee2);
  han->SetBinningMee(2,&binsMee3);
  han->SetBinningMee(3,&binsMee4);
  han->SetBinningMee(4,&binsMee5);
  han->SetBinningPtee(0,&binsPt1);
  han->SetBinningPtee(1,&binsPt2);
  han->SetBinningPtee(2,&binsPt3);
  han->SetBinningPtee(3,&binsPt4);
  han->SetBinningPtee(4,&binsPt5);
  
  han->SetDoRatio();
  han->SetDivideOption("0");
  han->SetPlotRangeRatio(0.2,1.8);
 
  han->Process(LmHandler::kCompare);
 // PlotHandler(han,system+"_SigComp"+xtra);
  


  LmHandler *hanCocktailComp = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin, plotPteeMax);
//  hanCocktailComp->AttachSignal(*(sig), "average");
  hanCocktailComp->AttachSignal(*(sigRef), "data");
  hanCocktailComp->SetBinningMee (0,&binsMee1);
  hanCocktailComp->SetBinningMee (1,&binsMee2);
  hanCocktailComp->SetBinningMee (2,&binsMee3);
  hanCocktailComp->SetBinningMee (3,&binsMee4);
  hanCocktailComp->SetBinningMee (4,&binsMee5);
  hanCocktailComp->SetBinningPtee(0,&binsPt1);
  hanCocktailComp->SetBinningPtee(1,&binsPt2);
  hanCocktailComp->SetBinningPtee(2,&binsPt3);
  hanCocktailComp->SetBinningPtee(3,&binsPt4);
  hanCocktailComp->SetBinningPtee(4,&binsPt5);
  
  hanCocktailComp->SetCocktail(&cocktail); // attach complete cocktail to handler. call cockt00->Process() before!
  hanCocktailComp->Process(LmHandler::kCocktail);
  hanCocktailComp->SetDrawStyleCocktail("hist c");
  hanCocktailComp->SetDrawStyleCocktailErr(" E2");
  
  hanCocktailComp->SetDoRatio();
  hanCocktailComp->SetDivideOption("0");
  hanCocktailComp->SetPlotRangeRatio(0.4,2.2001);
  
  PlotHandler(hanCocktailComp,system+"_pythia"+HFnormType+xtra);
  delete hanCocktailComp;
  
  hanCocktailComp = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin, plotPteeMax);
//  hanCocktailComp->AttachSignal(*(sig), "average");
  hanCocktailComp->AttachSignal(*(sigRef), "data");
  hanCocktailComp->SetBinningMee (0,&binsMee1);
  hanCocktailComp->SetBinningMee (1,&binsMee2);
  hanCocktailComp->SetBinningMee (2,&binsMee3);
  hanCocktailComp->SetBinningMee (3,&binsMee4);
  hanCocktailComp->SetBinningMee (4,&binsMee5);
  hanCocktailComp->SetBinningPtee(0,&binsPt1);
  hanCocktailComp->SetBinningPtee(1,&binsPt2);
  hanCocktailComp->SetBinningPtee(2,&binsPt3);
  hanCocktailComp->SetBinningPtee(3,&binsPt4);
  hanCocktailComp->SetBinningPtee(4,&binsPt5);
  
  hanCocktailComp->SetCocktail(&cocktailPowheg); // attach complete cocktail to handler. call cockt00->Process() before!
  hanCocktailComp->Process(LmHandler::kCocktail);
  hanCocktailComp->SetDrawStyleCocktail("hist c");
  hanCocktailComp->SetDrawStyleCocktailErr(" E2");
  
  hanCocktailComp->SetDoRatio();
  hanCocktailComp->SetDivideOption("0");
  hanCocktailComp->SetPlotRangeRatio(0.4,2.2001);
  
  PlotHandler(hanCocktailComp,system+"_powheg"+HFnormType+xtra);
  delete hanCocktailComp;

  
  


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

void ProcessSingleInputs(std::vector<TString> vConfig, std::vector<TString> vEffiConfig, TString name,
                         std::vector<LmManager*> &mgrVec,std::vector<LmBackground*> &bkgVec,std::vector<LmSignal*> &sigVec,
                         std::vector<LmManager*> *mgrVec_sys, std::vector<LmBackground*> *bkgVec_sys, std::vector<LmSignal*> *sigVec_sys,
                         LmBackground::enType type, std::vector<Double_t> vCutPhiVabove)
{  
  if(vConfig.size() != vEffiConfig.size()){ LmHelper::Error("ProcessSingleInputs(): unequal numbers of data and effi configs!"); return; }
  for (UInt_t ic=0; ic<vConfig.size(); ic++){
    LmFileManager::Instance()->AddConfig( vConfig.at(ic) ); // regular
    if(mgrVec_sys&&bkgVec_sys&&sigVec_sys) LmFileManager::Instance()->AddConfig( vConfig.at(ic) ); // systematic
  }
  for(UInt_t ic=0; ic<vConfig.size(); ic++){
    Double_t N_MB_cor(0);
    {
      TObjArray *arrData = vConfig.at(ic).Tokenize(":");
     // TString fName(const_cast<char*>(arrData->At(1));
      TFile fIn(arrData->At(1)->GetName(),"READ");
      TH1D hEvStat(*(static_cast<TH1D*> (fIn.Get("hEventStat"))));
      Double_t N_MB = hEvStat.GetBinContent(2) - (hEvStat.GetBinContent(6) - hEvStat.GetBinContent(7));
      TString listName(arrData->At(2)->GetName());
      TH1D hZvtx;
      if(listName == "NoList")
        hZvtx = TH1D(*(static_cast<TH1D*> (fIn.Get("cut06")->FindObject("Event")->FindObject("ZVertex"))));
      else
        hZvtx = TH1D(*(static_cast<TH1D*> (fIn.Get(arrData->At(2)->GetName())->FindObject(arrData->At(3)->GetName())->FindObject("Event")->FindObject("ZVertex"))));
  
      TF1 fGaus("fGaus","gaus(0)",-10000.,10000.);
      fGaus.SetNpx(10000);
      fGaus.SetParameter(0,1.);
      fGaus.SetParameter(1,hZvtx.GetMean());
      fGaus.SetParameter(2,hZvtx.GetRMS());

      hZvtx.Fit(&fGaus,"QIM0","",-9.,9.);
      Double_t Nvtx10  = fGaus.Integral(-10.,10.);
      Double_t NvtxInf = fGaus.Integral(-50.,50.);
      N_MB_cor = N_MB * Nvtx10 / NvtxInf;
    }
    if(N_MB_cor < 1){ Printf("Nev < 1"); continue; }
    LmHelper::Info(Form("config:  %s %s \n",vConfig.at(ic).Data(),vEffiConfig.at(ic).Data()));
    TObjArray *arr = vEffiConfig.at(ic).Tokenize(":");
    LmManager* mgr = new LmManager(const_cast<char*>(vConfig.at(ic).Data())); // TODO: input style to be optimized
    mgr->SetInputhistAndDim(const_cast<char*>("InvMass_PairPt_PhivPair"), inputdim);
    if(vCutPhiVabove.at(ic) > 0.){
      cutPhiVabove[0] = vCutPhiVabove.at(ic);
      mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
      mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
      mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
      mgr->SetEnableExclusionCutZ(LmManager::kFlatCorr);
    }
    else{
      mgr->SetEnableExclusionCutZ(LmManager::kNoCut); 
    }
    mgr->SetRebinning2D(n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
    if(vEffiConfig.at(ic).Length() > 0){
      mgr->SetEffifileAndHists(arr->At(0)->GetName(),arr->At(1)->GetName(),arr->At(2)->GetName());
      mgr->SetEnableEffiCorr(kTRUE);
    }
    else 
      mgr->SetEnableEffiCorr(kFALSE);
    mgr->Process();
    mgr->SetNeventsPhysSel(N_MB_cor/sigmaMB);
    mgr->SetEtaRange(-0.8,0.8);
    if(kpt400) mgr->SetPtRange(0.4,-1.);
    else       mgr->SetPtRange(0.2,-1.);
    mgrVec.push_back(mgr);
    
    LmBackground* bkg = new LmBackground(*(mgrVec.at(ic)),Form("bg_%s_cut%2d",name.Data(),ic+1));
    bkg->SetRfactorUnityRange(1.);
    bkg->Process(type);
    bkgVec.push_back(bkg);
    
    LmSignal* sig = new LmSignal(*(mgrVec.at(ic)), *(bkgVec.at(ic)), Form("sig_%s_cut %2d",name.Data(),ic+1));
    sig->SetDoNormBinwidth(kDoNormBinwidth);
    sig->SetDoNormNevents(kDoNormNevents);
    sig->Process(LmSignal::kStd);
    sigVec.push_back(sig);
    
    if(!(mgrVec_sys&&bkgVec_sys&&sigVec_sys)) continue;
    
    LmManager* mgr_sys = new LmManager(const_cast<char*>(vConfig.at(ic).Data())); // TODO: input style to be optimized
    mgr_sys->SetInputhistAndDim(const_cast<char*>("InvMass_PairPt_PhivPair"), inputdim);
    if(vCutPhiVabove.at(ic) > 0.){
      cutPhiVabove[0] = vCutPhiVabove.at(ic);
      mgr_sys->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
      mgr_sys->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
      mgr_sys->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
      mgr_sys->SetEnableExclusionCutZ(LmManager::kFlatCorr);
    }
    else{
      mgr_sys->SetEnableExclusionCutZ(LmManager::kNoCut); 
    }
    mgr_sys->SetRebinning2D(n_mee_bin_systematic, mee_bin_systematic, n_ptee_bin_systematic, ptee_bin_systematic);
    if(vEffiConfig.at(ic).Length() > 0){
      mgr_sys->SetEffifileAndHists(arr->At(0)->GetName(),arr->At(1)->GetName(),arr->At(2)->GetName());
      mgr_sys->SetEnableEffiCorr(kTRUE);
    }
    else 
      mgr_sys->SetEnableEffiCorr(kFALSE);
    mgr_sys->Process();
    mgr_sys->SetNeventsPhysSel(N_MB_cor/sigmaMB);
    mgr_sys->SetEtaRange(-0.8,0.8);
    if(kpt400) mgr_sys->SetPtRange(0.4,-1.);
    else       mgr_sys->SetPtRange(0.2,-1.);
    mgrVec_sys->push_back(mgr_sys);
    
    LmBackground* bkg_sys = new LmBackground(*(mgrVec_sys->at(ic)),Form("bg_systematic_%s_cut%2d",name.Data(),ic+1));
    bkg_sys->SetRfactorUnityRange(1.);
    bkg_sys->Process(type);
    bkgVec_sys->push_back(bkg_sys);
    
    LmSignal* sig_sys = new LmSignal(*(mgrVec_sys->at(ic)), *(bkgVec_sys->at(ic)), Form("sig_systematic_%s_cut %2d",name.Data(),ic+1));
    sig_sys->SetDoNormBinwidth(kDoNormBinwidth);
    sig_sys->SetDoNormNevents(kDoNormNevents);
    sig_sys->Process(LmSignal::kStd);
    sigVec_sys->push_back(sig_sys);
  }

}

LmSignal* GetSignal(std::vector<LmSignal*> &sigVec,std::vector<LmSignal*> &sigVec_sys, Int_t iSig)
{
  LmHandler *hanSystematic = new  LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, plotMeeMax,plotPteeMin, plotPteeMax);
  for(UInt_t iCuts = 0; iCuts < sigVec_sys.size(); ++iCuts)
    hanSystematic->AttachSignal(*(sigVec_sys.at(iCuts)), Form("cut%02d",iCuts+1));
  hanSystematic->SetSelectedSignal(iSig);
  hanSystematic->Process(LmHandler::kSystematic_Average);

  LmHandler* han = new  LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, plotMeeMax,plotPteeMin, plotPteeMax);
  if(iSig < 0){ 
    LmHandler* hanSignals = new  LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, plotMeeMax,plotPteeMin, plotPteeMax);
    for(UInt_t iCuts = 0; iCuts < sigVec.size(); ++iCuts)
      hanSignals->AttachSignal(*(sigVec.at(iCuts)), Form("cut%02d",iCuts+1));
    hanSignals->Process(LmHandler::kAverage);
    han->AttachSignal(*(hanSignals->GetLmSigAverage()),"data");
  }
  else
    han->AttachSignal(*(sigVec.at(iSig)),"data");
  han->GetLmSignalI(0)->SetSymmetricRelSystematics(hanSystematic->GetRelSystematics());
//  han->GetLmSignalI(0)->SetRelSystematicsLow (hanSystematic->GetRelSystematics());
//  han->GetLmSignalI(0)->SetRelSystematicsHigh(hanSystematic->GetRelSystematics());
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
//  han->SetPlotRangeY(2.0001e-7,0.8999e+0);
//  han->SetPlotRangeY(sigmaINEL*2.0001e-7,sigmaINEL*0.2999e-0);
//  han->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnMee,Form("+_%s",name.Data()));
//  han->SetPlotRangeY(sigmaINEL*1.0001e-8,sigmaINEL*0.8999e-1);
//  han->PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnMee,Form("+_%s",name.Data()));
//  han->SetPlotRangeY(sigmaINEL*4.0001e-8,sigmaINEL*0.8999e-2);
//  han->PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnMee,Form("+_%s",name.Data()));
//  han->SetPlotRangeY(sigmaINEL*1.0001e-8,sigmaINEL*0.1999e-2);
// han->PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnMee,Form("+_%s",name.Data()));
//  han->SetPlotRangeY(sigmaINEL*4.0001e-8,sigmaINEL*0.2499e-3);
//  han->PrintCompare(LmSignal::kSubSig,4, LmBaseSignal::kProjOnMee,Form("+_%s",name.Data()));
  han->SetPlotRangeY(sigmaINEL*1.0001e-7,sigmaINEL*0.3999e-0);
  han->PrintCompare(LmSignal::kSubSig,5, LmBaseSignal::kProjOnMee,Form("+_%s",name.Data()));
  
//  if(kpPb) han->SetPlotRangeY(6.0001e-7,2.8999e+1);
//  else     han->SetPlotRangeY(3.0001e-7,0.4999e+1); 
//  han->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
//  if(kpPb) han->SetPlotRangeY(2.0001e-7,4.8999e-1);
//  else     han->SetPlotRangeY(4.0001e-8,0.6999e-1);
//  han->PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
//  if(kpPb) han->SetPlotRangeY(1.0001e-7,0.1999e-1);
//  else     han->SetPlotRangeY(2.0001e-8,0.4999e-2);
//  han->PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
//  if(kpPb) han->SetPlotRangeY(2.0001e-7,0.7999e-2);
//  else     han->SetPlotRangeY(3.0001e-8,0.0999e-2);
//  han->PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
//  if(kpPb) han->SetPlotRangeY(3.0001e-7,0.1999e-3);
//  else     han->SetPlotRangeY(6.0001e-8,0.0999e-4);
//  han->PrintCompare(LmSignal::kSubSig,4, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));  

  han->SetPlotRangeY(sigmaINEL*3.0001e-7,sigmaINEL*2.8999e+1);
  han->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
  han->SetPlotRangeY(sigmaINEL*4.0001e-8,sigmaINEL*4.8999e-1);
  han->PrintCompare(LmSignal::kSubSig,1, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
  han->SetPlotRangeY(sigmaINEL*2.0001e-8,sigmaINEL*0.4999e-1);
  han->PrintCompare(LmSignal::kSubSig,2, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
  han->SetPlotRangeY(sigmaINEL*3.0001e-8,sigmaINEL*0.1999e-1);
  han->PrintCompare(LmSignal::kSubSig,3, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data()));
  han->SetPlotRangeY(sigmaINEL*6.0001e-8,sigmaINEL*0.1999e-3);
  han->PrintCompare(LmSignal::kSubSig,4, LmBaseSignal::kProjOnPtee,Form("+_%s",name.Data())); 
}


