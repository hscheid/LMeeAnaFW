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

#include "../core/LmManager.h"
#include "../core/LmBackground.h"
#include "../core/LmSignal.h"
#include "../core/LmHandler.h"
#include "../core/LmHelper.h"
#include "../core/LmFileManager.h"

void ProcessSingleInputs(std::vector<TString> vConfig, std::vector<TString> vEffiConfig,
                         std::vector<LmManager*> &mgrVec,     std::vector<LmBackground*> &bkgVec,     std::vector<LmSignal*> &sigVec,
                         std::vector<LmManager*> *mgrVec_sys, std::vector<LmBackground*> *bkgVec_sys, std::vector<LmSignal*> *sigVec_sys,
                         std::vector<TH3D*> &vTemlatesUS, std::vector<TH3D*> &vTemlatesLS, std::vector<Double_t> vCutValPhiV, std::vector<Double_t> vNormValPhiV);

//void ProcessSingleInputs(std::vector<TString> vConfig, std::vector<TString> vEffiConfig,
//                         std::vector<LmManager*> &mgrVec,     std::vector<LmBackground*> &bkgVec,     std::vector<LmSignal*> &sigVec,
//                         std::vector<LmManager*> *mgrVec_sys=0x0, std::vector<LmBackground*> *bkgVec_sys=0x0, std::vector<LmSignal*> *sigVec_sys=0x0);

void ProcessSingleInputs(std::vector<TString> vConfig, std::vector<TString> vEffiConfig,
                         std::vector<LmManager*> &mgrVec, std::vector<LmBackground*> &bkgVec, std::vector<LmSignal*> &sigVec,
                         std::vector<TH3D*> &vTemlatesUS, std::vector<TH3D*> &vTemlatesLS, std::vector<Double_t> vCutValPhiV, std::vector<Double_t> vNormValPhiV);

int main()
{
  gErrorIgnoreLevel = kWarning;
  
  //___________________________
  Int_t Ncuts = 3;
  Int_t refCutSet = (6 <= Ncuts) ? 5 : Ncuts-1;
  
  
  LmHelper helper; // initialization of style/colors
  
  std::vector<Double_t> binsPtee_forMee;
  binsPtee_forMee.push_back(0.);
  binsPtee_forMee.push_back(1.);
  binsPtee_forMee.push_back(2.);
  binsPtee_forMee.push_back(3.);
  binsPtee_forMee.push_back(6.);
  
  std::vector<Double_t> binsMee_forPtee;
  binsMee_forPtee.push_back(0.00);
  binsMee_forPtee.push_back(0.14);
  binsMee_forPtee.push_back(0.70);
  binsMee_forPtee.push_back(1.10);
  binsMee_forPtee.push_back(2.00);
  binsMee_forPtee.push_back(3.05);
  binsMee_forPtee.push_back(3.30);
  
  Double_t plotMeeMin  = 0., plotMeeMax  = 4.0;
  Double_t plotPteeMin = 0., plotPteeMax = 6.0;
  
  //_________________________________________________________________________________________________________________________________
  
  LmBaseSignal::SetInputLabelZ("#it{#phi}_{V}","rad");
  
  TString effi_gen = "NGenPairs_pt200";
  TString coll_system = "pp, #sqrt{#it{s}} = 7 TeV"; 
  TString system = "pp"; 
  
  std::vector<TString> cconfigAllCuts,econfigAllCuts;
  std::vector<TString> cconfigAllCuts_pp,econfigAllCuts_pp;
  std::vector<TString> cconfigAllCuts_mm,econfigAllCuts_mm;
  
  
  //  std::vector<TString> cconfigAllCutsNoSclsITS,econfigAllCutsNoSclsITS,econfigAllCutsNoSclsITSFullMC;
  //    cconfigAllCutsNoSclsITS
  //    econfigAllCutsNoSclsITS
  //    econfigAllCutsNoSclsITSFullMC
  //    econfigAllCutsFullMC
  
  std::vector<TH3D*> vTempUS,vTempLS;
  std::vector<Double_t> vCutValPhiV,vNormValPhiV;
  TFile *fIn = new TFile(Form("./input/09-2016/%s/phiVtemplates/phiVtemplate_allCuts.root",system.Data()),"READ");    
  
  for(Int_t i = 1; i <= Ncuts; ++i){
    cconfigAllCuts    .push_back( coll_system+":"+"./input/09-2016/"+system+"/data/combined_allCuts.root"+":"+tree_name+":"+Form("cut%02d",i) );
    econfigAllCuts    .push_back( "./input/09-2016/"+system+"/efficiencies/ToyPairEff_allEfficiencies.root"+":"+effi_gen+":"+Form("NRecPairsCombined_Eff_cut%02d_pt200",i) );
    cconfigAllCuts_pp .push_back( coll_system+":"+"./input/09-2016/"+system+"/data/combined_pp_allCuts.root"+":"+tree_name+":"+Form("cut%02d",i) );
    econfigAllCuts_pp .push_back( "./input/09-2016/"+system+"/efficiencies/ToyPairEff_pp_allEfficiencies.root"+":"+effi_gen+":"+Form("NRecPairsCombined_Eff_cut%02d_pt200",i) );
    cconfigAllCuts_mm .push_back( coll_system+":"+"./input/09-2016/"+system+"/data/combined_mm_allCuts.root"+":"+tree_name+":"+Form("cut%02d",i) );
    econfigAllCuts_mm .push_back( "./input/09-2016/"+system+"/efficiencies/ToyPairEff_mm_allEfficiencies.root"+":"+effi_gen+":"+Form("NRecPairsCombined_Eff_cut%02d_pt200",i) );
    
    vTempUS.push_back( static_cast<TH3D*>(fIn->Get("Histos_diel_lowmass")->FindObject(Form("cut%02d",i))->FindObject("Pair_US")->FindObject("InvMass_PairPt_PhivPair")) );
    vTempLS.push_back( static_cast<TH3D*>(fIn->Get("Histos_diel_lowmass")->FindObject(Form("cut%02d",i))->FindObject("Pair_LS--")->FindObject("InvMass_PairPt_PhivPair")) );
    vTempLS.at(i-1)->Add(static_cast<TH3D*>(fIn->Get("Histos_diel_lowmass")->FindObject(Form("cut%02d",i))->FindObject("Pair_LS++")->FindObject("InvMass_PairPt_PhivPair")));
    vCutValPhiV .push_back( 0.60*TMath::Pi() ); 
    vNormValPhiV.push_back( 0.60*TMath::Pi() );
  }
  
  
  std::vector<LmManager*>    mgrVecAllCuts,mgrVecAllCuts_pp,mgrVecAllCuts_mm;
  std::vector<LmBackground*> bkgVecAllCuts,bkgVecAllCuts_pp,bkgVecAllCuts_mm;
  std::vector<LmSignal*>     sigVecAllCuts,sigVecAllCuts_pp,sigVecAllCuts_mm;
  
  std::vector<LmManager*>    mgrVecSysAllCuts,mgrVecSysAllCuts_pp,mgrVecSysAllCuts_mm;
  std::vector<LmBackground*> bkgVecSysAllCuts,bkgVecSysAllCuts_pp,bkgVecSysAllCuts_mm;
  std::vector<LmSignal*>     sigVecSysAllCuts,sigVecSysAllCuts_pp,sigVecSysAllCuts_mm;
  
  Printf("______ process input  ______");
  ProcessSingleInputs(cconfigAllCuts,econfigAllCuts,
                      mgrVecAllCuts   , bkgVecAllCuts   , sigVecAllCuts,
                      &mgrVecSysAllCuts,&bkgVecSysAllCuts,&sigVecSysAllCuts,
                      vTempUS,vTempLS,vCutValPhiV,vNormValPhiV);
  ProcessSingleInputs(cconfigAllCuts_pp,econfigAllCuts_pp,
                      mgrVecAllCuts_pp   , bkgVecAllCuts_pp   , sigVecAllCuts_pp,
                      &mgrVecSysAllCuts_pp,&bkgVecSysAllCuts_pp,&sigVecSysAllCuts_pp,
                      vTempUS,vTempLS,vCutValPhiV,vNormValPhiV);
  ProcessSingleInputs(cconfigAllCuts_mm,econfigAllCuts_mm,
                      mgrVecAllCuts_mm   , bkgVecAllCuts_mm   , sigVecAllCuts_mm,
                      &mgrVecSysAllCuts_mm,&bkgVecSysAllCuts_mm,&sigVecSysAllCuts_mm,
                      vTempUS,vTempLS,vCutValPhiV,vNormValPhiV);    
  Printf("______ DONE WITH SINGLE INPUT PROCESSING ______");
  
//  LmHandler* han_systematic;
//  han_systematic = new  LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, plotMeeMax,plotPteeMin, plotPteeMax);
//  for(UInt_t iCuts = 0; iCuts < Ncuts; ++iCuts)
//    han_systematic->AttachSignal(*(sigVec_systematic.at(iCuts)), Form("cut%02d",iCuts+1));
//  han_systematic->Process(LmHandler::kAverage);
//  han_systematic->Process(LmHandler::kCompare);
//  // postprocess analysis binning "
//  // process signals (average, set systematics)
//  LmHandler* hanSignal = new  LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, plotMeeMax,plotPteeMin, plotPteeMax);
//  hanSignal->AttachSignal(*(sigVec.at(refCutset-1)),"data");
//  hanSignal->GetLmSignalI(0)->SetSymmetricRelSystematics(han_systematic->GetRelSystematics());
//  hanSignal->GetLmSignalI(0)->Process(LmSignal::kSystematic);
      
  LmHandler *hanComb = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  hanComb->AttachSignal(*(sigVecAllCuts_pp.at(refCutSet)),"combine1");
  hanComb->AttachSignal(*(sigVecAllCuts_mm.at(refCutSet)),"combine2");
  hanComb->Process(LmHandler::kCombine);
      
  LmHandler *han1 = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  han1->AttachSignal(*(sigVecAllCuts   .at(refCutSet)),"preCombined");
//  han1->AttachSignal(*(sigVecAllCuts_pp.at(refCutSet)),"++");
//  han1->AttachSignal(*(sigVecAllCuts_mm.at(refCutSet)),"--");
  han1->AttachSignal(*(hanComb->GetLmSigCombined()),"hancombined");
  han1->SetDoRatio();
  han1->SetDivideOption("0");
  han1->SetPlotRangeRatio(0.5,1.5);
  han1->Process(LmHandler::kCompare);

//  han1->PrintCompare(LmSignal::kSubSig,binsPtee_forMee.size()-1, LmBaseSignal::kProjOnMee,"");
  for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj)
    han1->PrintCompare(LmSignal::kSubSig,iProj, LmBaseSignal::kProjOnMee,"");
  for(UInt_t iProj = 0; iProj < binsMee_forPtee.size()-1; ++iProj)
    han1->PrintCompare(LmSignal::kSubSig,iProj, LmBaseSignal::kProjOnPtee,"");  
  //    
  //    LmHandler *han2 = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  //    han2->AttachSignal(*(sigVec.at(3)),"std (angle cut)");
  //    han2->AttachSignal(*(sigVec.at(4)),"pfAngle (angle cut)");
  //    han2->AttachSignal(*(sigVec.at(5)),"pfAngleMass (angle cut)");
  //    han2->SetDoRatio();
  //    han2->SetPlotRangeRatio(0.5,1.5);
  //    han2->Process(LmHandler::kCompare); 
  //    
  //    han2->PrintCompare(LmSignal::kSubSig,binsPtee_forMee.size()-1, LmBaseSignal::kProjOnMee,"+_PFcompAngleCut");
  //    han2->PrintCompare(LmSignal::kSignif,binsPtee_forMee.size()-1, LmBaseSignal::kProjOnMee,"+_PFcompAngleCut");
  //    han2->SetPlotRangeY(5.001e-8,2.999e0);
  //    han2->PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,"+_PFcompAngleCut");
  //    han2->SetPlotRangeY(8.001e-1,8.999e2);
  //    han2->PrintCompare(LmSignal::kSignif,0, LmBaseSignal::kProjOnPtee,"+_PFcompAngleCut");
  
  //  han2->PrintCompare(LmSignal::kSignif,0, LmBaseSignal::kProjOnPtee,"+_prefilterAngleCut");
  //  han3->PrintCompare(LmSignal::kSignif,0, LmBaseSignal::kProjOnPtee,"+_AngleCutEff");
  
  /*
   std::vector<TString> cocktail_files;
   cocktail_files.push_back("./input/pPb/cocktail/resonances-new_angleSmeared.root");
   cocktail_files.push_back("./input/pPb/cocktail/resonances-new_angleSmeared_50mrad.root");
   std::vector<TString> cocktail_histograms;
   cocktail_histograms.push_back("Mee_Ptee_Pion:Mee_Ptee_Eta:Mee_Ptee_EtaPrime:Mee_Ptee_Rho:Mee_Ptee_Omega:Mee_Ptee_OmegaDalitz:Mee_Ptee_Phi:Mee_Ptee_PhiDalitz:Mee_Ptee_JPsi");
   cocktail_histograms.push_back("Mee_Ptee_Pion:Mee_Ptee_Eta:Mee_Ptee_EtaPrime:Mee_Ptee_Rho:Mee_Ptee_Omega:Mee_Ptee_OmegaDalitz:Mee_Ptee_Phi:Mee_Ptee_PhiDalitz:Mee_Ptee_JPsi_simple");
   std::vector<TString> heavyfl_files; 
   heavyfl_files.push_back("./input/pPb/cocktail/heavy_flavour_pt200.root:./input/pPb/cocktail/heavy_flavour_pt200.root");
   heavyfl_files.push_back("./input/pPb/cocktail/scaled_heavy_flavour_pt200.root:./input/pPb/cocktail/scaled_heavy_flavour_pt200.root");
   heavyfl_files.push_back("./input/pPb/cocktail/ppScaled_heavy_flavour_pt200.root:./input/pPb/cocktail/ppScaled_heavy_flavour_pt200.root");
   std::vector<TString> heavyfl_histograms;
   heavyfl_histograms.push_back("charm_pythiaPerugia2011_pt200:beauty_pythiaPerugia2011_pt200");
   heavyfl_histograms.push_back("charm_powheg_pt200:beauty_powheg_pt200");
   std::vector<TString> heavyfl_hist_Nevents;
   heavyfl_hist_Nevents.push_back("");
   heavyfl_hist_Nevents.push_back("NONE:NONE");
   
   LmCocktailMan cocktmanHF_powheg  (heavyfl_files.at(0),heavyfl_histograms.at(1),2,n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
   cocktmanHF_powheg.Process(LmCocktailMan::kHeavyFl);
   
   LmCocktailMan* cocktmanReso = new LmCocktailMan(cocktail_files.at(0),cocktail_histograms.at(1),2,n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
   cocktmanReso->Process(LmCocktailMan::kLFsum);
   
   {
   LmCocktail cocktail(LmCocktail::kpPb_MB_502);
   cocktail.AttachManager( *cocktmanReso );
   cocktail.AttachManager( cocktmanHF_powheg );
   cocktail.Process();
   LmHandler CocktailHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, 0.5,plotPteeMin, plotPteeMax);
   CocktailHandler.SetPlotRangeRatio(0.2, 1.799);
   CocktailHandler.SetDoRatio(kTRUE);
   CocktailHandler.SetDivideOption("0");
   CocktailHandler.SetDrawStyleCocktail("hist");
   CocktailHandler.AttachSignal(*(sigVec.at(0)),"cut06");
   CocktailHandler.AttachSignal(*(sigVec.at(13)),"sharedClsITS = 0");
   CocktailHandler.SetCocktail(&cocktail); // attach complete cocktail to handler. call cockt00->Process() before!
   CocktailHandler.Process(LmHandler::kCocktail);
   
   CocktailHandler.SetPlotRangeY(5.001e-5,4.999e0);
   CocktailHandler.PrintCompare(LmSignal::kSubSig,binsPtee_forMee.size()-1, LmBaseSignal::kProjOnMee);
   CocktailHandler.SetPlotRangeY(9.001e-8,4.999e0);
   CocktailHandler.PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee);
   //  for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj)
   //    CocktailHandler.PrintCompare(LmSignal::kSubSig,iProj, LmBaseSignal::kProjOnMee,"+_cocktail");
   }
   
   LmCocktailMan* cocktmanReso50mrad = new LmCocktailMan(cocktail_files.at(1),cocktail_histograms.at(1),2,n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
   cocktmanReso50mrad->Process(LmCocktailMan::kLFsum); 
   {
   LmCocktail cocktail(LmCocktail::kpPb_MB_502);
   cocktail.AttachManager( *cocktmanReso50mrad );
   cocktail.AttachManager( cocktmanHF_powheg );
   cocktail.Process();
   LmHandler CocktailHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, 0.5,plotPteeMin, plotPteeMax);
   CocktailHandler.SetPlotRangeRatio(0.2, 1.799);
   CocktailHandler.SetDoRatio(kTRUE);
   CocktailHandler.SetDivideOption("0");
   CocktailHandler.SetDrawStyleCocktail("hist");
   CocktailHandler.AttachSignal(*(sigVec.at(1)),"cut06(angleCut)");
   CocktailHandler.AttachSignal(*(sigVec.at(4)),"cut06(prefilter)");
   CocktailHandler.AttachSignal(*(sigVec.at(5)),"cut06(prefilter+angleCut)");
   CocktailHandler.SetCocktail(&cocktail); // attach complete cocktail to handler. call cockt00->Process() before!
   CocktailHandler.Process(LmHandler::kCocktail);
   
   CocktailHandler.SetPlotRangeY(5.001e-5,4.999e0);
   CocktailHandler.PrintCompare(LmSignal::kSubSig,binsPtee_forMee.size()-1, LmBaseSignal::kProjOnMee,"+_50mrad");
   CocktailHandler.SetPlotRangeY(9.001e-8,4.999e0);
   CocktailHandler.PrintCompare(LmSignal::kSubSig,0, LmBaseSignal::kProjOnPtee,"+_50mrad");
   //  for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj)
   //    CocktailHandler.PrintCompare(LmSignal::kSubSig,iProj, LmBaseSignal::kProjOnMee,"+_cocktail50mrad");
   }   
   
   
   */
  std::cout << "main.cpp done :-)" << std::endl;
  return 0;
}

void ProcessSingleInputs(std::vector<TString> vConfig, std::vector<TString> vEffiConfig,
                         std::vector<LmManager*> &mgrVec,     std::vector<LmBackground*> &bkgVec,     std::vector<LmSignal*> &sigVec,
                         std::vector<LmManager*> *mgrVec_sys, std::vector<LmBackground*> *bkgVec_sys, std::vector<LmSignal*> *sigVec_sys,
                         std::vector<TH3D*> &vTemlatesUS, std::vector<TH3D*> &vTemlatesLS, std::vector<Double_t> vCutValPhiV, std::vector<Double_t> vNormValPhiV)
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
    mgr->SetCutValPhiV(vCutValPhiV.at(ic));
    mgr->SetCutValMee(cutValMee);  
    mgr->SetTemplateNormRegion(0.,vNormValPhiV.at(ic));
    if(vTemlatesUS.at(ic)) mgr->SetExclusionZTemplates(vTemlatesUS.at(ic),vTemlatesLS.at(ic));
    mgr->SetEnablePhiVCut(bCutPhiV);
    mgr->SetRebinning2D(n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
    mgr->SetEffifileAndHists(arr->At(0)->GetName(),arr->At(1)->GetName(),arr->At(2)->GetName());
    mgr->SetEnableEffiCorr(kDoEffiCorrection); // use this to disable or just comment out the setter above...
    mgr->Process();
    mgr->SetEtaRange(-0.8,0.8);
    mgr->SetPtRange(0.2,-1.);
    //    mgr->SetThetaEEmin(0.05);
    mgrVec.push_back(mgr);
    
    LmBackground* bkg = new LmBackground(*(mgrVec.at(ic)),Form("bg_cut%2d",ic+1));
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
    mgr_sys->SetCutValPhiV(vCutValPhiV.at(ic));
    mgr_sys->SetCutValMee(cutValMee);  
    mgr_sys->SetTemplateNormRegion(0.,vNormValPhiV.at(ic));
    if(vTemlatesUS.at(ic)) mgr_sys->SetExclusionZTemplates(vTemlatesUS.at(ic),vTemlatesLS.at(ic));
    mgr_sys->SetEnablePhiVCut(bCutPhiV);
    mgr_sys->SetRebinning2D(n_mee_bin_systematic, mee_bin_systematic, n_ptee_bin_systematic, ptee_bin_systematic);
    mgr_sys->SetEffifileAndHists(arr->At(0)->GetName(),arr->At(1)->GetName(),arr->At(2)->GetName());
    mgr_sys->SetEnableEffiCorr(kDoEffiCorrection); // use this to disable or just comment out the setter above...
    mgr_sys->Process();
    mgr_sys->SetEtaRange(-0.8,0.8);
    mgr_sys->SetPtRange(0.2,-1.);
    mgrVec_sys->push_back(mgr_sys);
    
    LmBackground* bkg_sys = new LmBackground(*(mgrVec_sys->at(ic)),Form("bg_systematic_cut%2d",ic+1));
    bkg_sys->Process(LmBackground::kHybrid);
    bkgVec_sys->push_back(bkg_sys);
    
    LmSignal* sig_sys = new LmSignal(*(mgrVec_sys->at(ic)), *(bkgVec_sys->at(ic)), Form("sig_systematic_cut %2d", ic+1));
    sig_sys->SetDoNormBinwidth(kDoNormBinwidth);
    sig_sys->SetDoNormNevents(kDoNormNevents);
    sig_sys->Process(LmSignal::kStd);
    sigVec_sys->push_back(sig_sys);
  }
}

void ProcessSingleInputs(std::vector<TString> vConfig, std::vector<TString> vEffiConfig,
                         std::vector<LmManager*> &mgrVec, std::vector<LmBackground*> &bkgVec, std::vector<LmSignal*> &sigVec,
                         std::vector<TH3D*> &vTemlatesUS, std::vector<TH3D*> &vTemlatesLS, std::vector<Double_t> vCutValPhiV, std::vector<Double_t> vNormValPhiV)
{
  if(vConfig.size() != vEffiConfig.size()) { LmHelper::Error("ProcessSingleInputs(): unequal numbers of data and effi configs!"); return; }
  //  for (UInt_t ic=0; ic<vConfig.size(); ic++) {
  //    LmFileManager::Instance()->AddConfig( vConfig.at(ic) ); // regular
  //  }
  for(UInt_t ic=0; ic<vConfig.size(); ic++){
    if(ic > 0) bCutPhiV=kTRUE;
    LmHelper::Info(Form("config:  %s %s \n",vConfig.at(ic).Data(),vEffiConfig.at(ic).Data()));
    TObjArray *arr = vEffiConfig.at(ic).Tokenize(":");
    LmManager* mgr = new LmManager(const_cast<char*>(vConfig.at(ic).Data())); // TODO: input style to be optimized
    mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
    
    mgr->SetCutValPhiV(vCutValPhiV.at(ic));
    mgr->SetCutValMee(cutValMee);  
    mgr->SetTemplateNormRegion(0.,vNormValPhiV.at(ic));
    if(vTemlatesUS.at(ic)) mgr->SetExclusionZTemplates(vTemlatesUS.at(ic),vTemlatesLS.at(ic));
    mgr->SetEnablePhiVCut(bCutPhiV);
    
    mgr->SetRebinning2D(n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
    mgr->SetEffifileAndHists(arr->At(0)->GetName(),arr->At(1)->GetName(),arr->At(2)->GetName());
    mgr->SetEnableEffiCorr(kDoEffiCorrection); // use this to disable or just comment out the setter above...
    mgr->Process();
    mgr->SetEtaRange(-0.8,0.8);
    mgr->SetPtRange(0.2,-1.);
    //    mgr->SetThetaEEmin(0.05);
    mgrVec.push_back(mgr);
    
    LmBackground* bkg = new LmBackground(*(mgrVec.at(ic)),Form("bg_cut%2d",ic+1));
    bkg->Process(LmBackground::kHybrid);
    bkgVec.push_back(bkg);
    
    LmSignal* sig = new LmSignal(*(mgrVec.at(ic)), *(bkgVec.at(ic)), Form("sig_cut %2d", ic+1));
    sig->SetDoNormBinwidth(kDoNormBinwidth);
    sig->SetDoNormNevents(kDoNormNevents);
    sig->Process(LmSignal::kStd);
    sigVec.push_back(sig);                         
  }
}





