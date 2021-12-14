
#include <iostream>

#include "TFile.h"
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TF1.h"
#include "TF2.h"
#include "TStyle.h"
#include "TPad.h"
#include "TLine.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TVirtualFitter.h"
#include "TGraph.h"
#include "TMinuit.h"
#include "TColor.h"
#include "TString.h"

Double_t meeMin(1.0),meeMax(2.8),pteeMin(0.),pteeMax(8.);
TH2D *hc,*hb,*hRes;


//Double_t sigma_ccbar(7.480);//7TeV  
//Double_t sigma_bbbar(0.288);//7TeV

Bool_t do200MeV = kFALSE;


Double_t sigma_ccbar(12.16); // 13 TeV 
Double_t sigma_bbbar(0.500); // 13 TeV

//Double_t sigma_ccbar(0.977);
//Double_t sigma_bbbar(0.058);

Double_t x1(0.65);

////////////////////////////////////////////
//swithc this to new input i got from theo//
////////////////////////////////////////////

TString sData = "./input/Data_TheoStyle_75MeV.root";

TString sLFcocktail_Std     = "./output/LFcocktail_Jerome_75MeV_low_0404_v1.root";
TString sLFcocktail_Low  = "./output/LFcocktail_Jerome_75MeV_low_0404_v1.root";
TString sLFcocktail_High = "./output/LFcocktail_Jerome_75MeV_low_0404_v1.root";

//TString ResName     = "./output/LFcocktail_low_75MeV_v2.root";
//TString ResNameLow  = "./output/LFcocktail_low_75MeV_v2.root";
//TString ResNameHigh = "./output/LFcocktail_low_75MeV_v2.root";

TString sLFcocktail   = "cocktailPt75rec";
TString sHFcocktail_LS   = "hMeePtee_LS_eta08_pt075";
TString sHFcocktail_ULS   = "hMeePtee_ULS_eta08_pt075";
TString sJPsicocktail = "cocktailPt075rec";


Double_t ccbarErrLow  = 0.07825; // to be updated but not used in the fit
Double_t ccbarErrHigh = 0.07934;
Double_t bbbarErrLow  = 0.35724;
Double_t bbbarErrHigh = 0.33461;

void SetHistoProp(TH1D *h, Int_t color,Int_t mStyle,Int_t lStyle);
Double_t HFfunction(Double_t *x, Double_t *par);
void SutractHisto(TH2D &h1, TH2D &h2);
void Rebin2D(TH2D &h,TH2D &hRefBinning);
TH2D *RebinBis(TH2D &h);
TPaveText GetTextBox(Double_t x1, Double_t y1, Double_t x2, Double_t y2);
void Add5proc(TH2D &hup, TH2D &h);

void fitNewDec(  TString syst = "",TString cs = "pp")
{
  TFile *fOut(0x0);

  std::vector<Double_t> vPtee;
  vPtee.push_back(0.0);
  //vPtee.push_back(1.0);
  //vPtee.push_back(2.0);
  //vPtee.push_back(3.0);
  vPtee.push_back(8.0);

  const Int_t nRGBs = 5;
  const Int_t nCont = 255;
  Double_t stops[nRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[nRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[nRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[nRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(nRGBs, stops, red, green, blue, nCont);
  gStyle->SetNumberContours(nCont);

  gStyle->SetOptStat(0);
  TVirtualFitter::SetDefaultFitter("Minuit");

  if(do200MeV){

    sLFcocktail_Std  = "./output/LFcocktail_low_200MeV_v2.root";
    sLFcocktail_Low  = "./output/LFcocktail_low_200MeV_v2.root";
    sLFcocktail_High = "./output/LFcocktail_low_200MeV_v2.root";

    sData = "./input/Data_TheoStyle_200MeV.root";

    sLFcocktail   = "cocktailPt200rec";
    sHFcocktail_LS   = "hMeePtee_LS_eta08_pt200";
    sHFcocktail_ULS   = "hMeePtee_ULS_eta08_pt200";
    sJPsicocktail = "cocktailPt200rec";

  }

  //
  // Take the data
  //
  
 
  //TFile fData("/Users/Raphaelle/Desktop/pplmeepaper/AnalysisPF/LMeeAnaFW/PlottingFW/CorrectedSpectra/603_607/ppData_pt400.root","READ");
  // Up to now output:
  //TFile fData("./input/11_12_2017/ppData_pt400.root","READ");

  // New pt 200 output:
  // toymc
  //TFile fData("/Users/Raphaelle/Desktop/pplmeepaper/AnalysisPF/MacrosCombinedFullMCToyMC/ppData_pt200_545_combined_cut5.root","READ");
  // fullmc
  //TFile fData("/Users/Raphaelle/Desktop/pplmeepaper/Cocktail/Try/14_02_2018/Data/FullMC/Cut5/ppData_pt200.root","READ");


  // New pt 400 output:
  // toymc
  //TFile fData("/Users/Raphaelle/Desktop/pplmeepaper/Cocktail/Try/05_03_2018/Datapt400/ToyMC/Cut5/ppData_pt400.root","READ");
  // fullmc
  //TFile fData("/Users/Raphaelle/Desktop/pplmeepaper/Cocktail/Try/05_03_2018/Datapt400/FullMC/Cut5/ppData_pt400.root","READ");
  TFile fData(sData,"READ");
  //TFile fData("./input/Data_TheoStyle_200MeV.root","READ");
  

  //
  // Take the LF cocktail
  //
  
  TFile fRes    (sLFcocktail_Std,"READ");
  TFile fResLow (sLFcocktail_Low,"READ");
  TFile fResHigh(sLFcocktail_High,"READ");

  //
  // Take the HFs files
  //

  // has to be 2 files for charm/ beauty
  // check if different files for pythia/powheg
  // TFile fHFcharm  ("~/analysis/Analysis/src/theo/input/pp/new/HFfitInput/ppHeavyFlavour.root","READ");
  // TFile fHFbeauty  ("~/analysis/Analysis/src/theo/input/pp/new/HFfitInput/ppHeavyFlavour.root","READ");
  TFile fHFcharm  ("./input/HFcocktail_charm_new.root","READ");
  TFile fHFbeauty ("./input/HFcocktail_BEAUTY.root","READ");

  std::cout << &fHFcharm << "   " << &fHFbeauty << std::endl;

  //TFile fHFcharm  ("./input/intermediate/Results_charm_pp7TeV_diffnorm.root","READ");
  //TFile fHFbeauty  ("./input/intermediate/Results_beauty_pp7TeV_diffnorm.root","READ");


  TFile fJPsi_Std  ("./input/JPsi-kpp-Std_low.root","READ");
  TFile fJPsi_Low  ("./input/JPsi-kpp-Low_low.root","READ");
  TFile fJPsi_High ("./input/JPsi-kpp-High_low.root","READ");


  if(!(fData.IsOpen()&&fRes.IsOpen()&&fResLow.IsOpen()&&fResHigh.IsOpen()&&fHFcharm.IsOpen()&&fHFbeauty.IsOpen())){
    Printf("files not open");
    return;
  }


  //
  // Sys data
  //

  TH2D ssignal    (*(static_cast<TH2D*> (fData.Get("signal"))));
  TH2D ssignalLow (*(static_cast<TH2D*> (fData.Get("systematicLow"))));
  ssignalLow.SetName("signalLow");
  Add5proc(ssignalLow, ssignal);
  TH2D ssignalHigh(*(static_cast<TH2D*> (fData.Get("systematicHigh"))));
  ssignalHigh.SetName("signalHigh");
  Add5proc(ssignalHigh, ssignal);

  //
  // Scale LF to cross-sections
  //

  //Double_t resscale[7] = {73.2,73.2,73.2,73.2,73.2,73.2,62.2};
  //Double_t resscale[7] = {78.1,78.1,78.1,78.1,78.1,78.1,62.2};
  Double_t resscale[7] = {1.,1.,1.,1.,1.,1.,1.}; 

 
  TList *l(0x0);
  //l = static_cast<TList*> (fRes.Get("cocktailPt200rec"));
  l = static_cast<TList*> (fRes.Get(sLFcocktail));
  TH2D rresonances(*(static_cast<TH2D*> (l->At(0))));
  rresonances.SetName("resonances");
  rresonances.Scale(resscale[0]);
  for(Int_t i = 1; i < l->GetEntries(); ++i) {
    printf("%d and scale factor %f and name %s\n",i,resscale[i],l->At(i)->GetName());
    rresonances.Add(static_cast<TH2D*> (l->At(i)),resscale[i]);
  }

 
  //l = static_cast<TList*> (fResLow.Get("cocktailPt200rec"));
  l = static_cast<TList*> (fResLow.Get(sLFcocktail));
  TH2D rresonances_low(*(static_cast<TH2D*> (l->At(0))));
  rresonances_low.SetName("resonances_low");
  rresonances_low.Scale(resscale[0]);
  for(Int_t i = 1; i < l->GetEntries(); ++i) {
    rresonances_low.Add(static_cast<TH2D*> (l->At(i)),resscale[i]);
  }

  //l = static_cast<TList*> (fResHigh.Get("cocktailPt200rec"));
  l = static_cast<TList*> (fResHigh.Get(sLFcocktail));
  TH2D rresonances_high(*(static_cast<TH2D*> (l->At(0))));
  rresonances_high.SetName("resonances_high");
  rresonances_high.Scale(resscale[0]);
  for(Int_t i = 1; i < l->GetEntries(); ++i) {
    rresonances_high.Add(static_cast<TH2D*> (l->At(i)),resscale[i]);
  }


  //Jpsi
  //l = static_cast<TList*> (fJPsi_Std.Get("cocktailPt200rec"));
  l = static_cast<TList*> (fJPsi_Std.Get(sJPsicocktail));
  TH2D jjpsi(*(static_cast<TH2D*> (l->FindObject("MeePteeJPsi"))));
  jjpsi.SetName("jjpsi");
  jjpsi.Scale(12.16/7.48);
  //jjpsi.Scale(57.8);
  

 
  //l = static_cast<TList*> (fJPsi_Low.Get("cocktailPt200rec"));
  l = static_cast<TList*> (fJPsi_Low.Get(sJPsicocktail));
  TH2D jjpsi_low(*(static_cast<TH2D*> (l->FindObject("MeePteeJPsi"))));
  jjpsi_low.SetName("jpsi_low");
  jjpsi_low.Scale(12.16/7.48);
  //jjpsi_low.Scale(57.8);
  

  //l = static_cast<TList*> (fJPsi_High.Get("cocktailPt200rec"));
  l = static_cast<TList*> (fJPsi_High.Get(sJPsicocktail));
  TH2D jjpsi_high(*(static_cast<TH2D*> (l->FindObject("MeePteeJPsi"))));
  jjpsi_high.SetName("jjpsi_high");
  jjpsi_high.Scale(12.16/7.48);
  //jjpsi_high.Scale(57.8);
  

  

  //
  // Take the two 2 distributions for HF
  //
  
  //TH2D ccharm_pythia  (*(static_cast<TH2D*> (fHFcharm.Get("hMeePtee_ULS_LS_eta08_pt4_Pythia_Normmid"))));
  //TH2D ccharm_pythia  (*(static_cast<TH2D*> (fHFcharm.Get("lowee")->FindObject("hMeePtee_ULS_LS_eta08_pt075"))));
  TH2D ccharm_ULS_pythia  (*(static_cast<TH2D*> (fHFcharm.Get("lowee")->FindObject(sHFcocktail_ULS))));
  TH2D ccharm_LS_pythia  (*(static_cast<TH2D*> (fHFcharm.Get("lowee")->FindObject(sHFcocktail_LS))));
  //TH2D ccharm_ULS_pythia  (*(static_cast<TH2D*> (fHFcharm.Get("lowee")->FindObject("hMeePtee_ULS_eta08_pt200"))));
  //TH2D ccharm_LS_pythia  (*(static_cast<TH2D*> (fHFcharm.Get("lowee")->FindObject("hMeePtee_LS_eta08_pt200"))));
  TH2D ccharm_rap     (*(static_cast<TH2D*> (fHFcharm.Get("lowee")->FindObject("hRapCharmQuarkMethod1"))));
  //TH2D ccharm_pythia  (*(static_cast<TH2D*> (fHFcharm.Get("hMeePtee_ULS_LS_eta08_pt2_Pythia_Normtotal"))));
  //TH2D ccharm_pythia  (*(static_cast<TH2D*> (fHFcharm.Get("hMeePtee_ULS_LS_eta08_pt2_Pythia_Normmid"))));
  
  
 
//  //TH2D ccharm_powheg  (*(static_cast<TH2D*> (fHFcharm.Get(Form("hMeePtee_ULS_LS_eta08_pt4_Powheg%s_Normmid",syst.Data())))));
//  TH2D ccharm_powheg  (*(static_cast<TH2D*> (fHFcharm.Get(Form("hMeePtee_ULS_LS_eta08_pt4_Powheg%s_Normtotal",syst.Data())))));
//  //TH2D ccharm_powheg  (*(static_cast<TH2D*> (fHFcharm.Get(Form("hMeePtee_ULS_LS_eta08_pt2_Powheg%s_Normtotal",syst.Data())))));
//  //TH2D ccharm_powheg  (*(static_cast<TH2D*> (fHFcharm.Get(Form("hMeePtee_ULS_LS_eta08_pt2_Powheg%s_Normmid",syst.Data())))));
//  ccharm_powheg.SetName("charm_powheg");

  //TH2D bbeauty_pythia (*(static_cast<TH2D*> (fHFbeauty.Get("hMeePtee_ULS_LS_eta08_pt4_Pythia_Normmid"))));
  //TH2D bbeauty_pythia (*(static_cast<TH2D*> (fHFbeauty.Get("lowee")->FindObject("hMeePtee_ULS_LS_eta08_pt075"))));
  TH2D bbeauty_ULS_pythia (*(static_cast<TH2D*> (fHFbeauty.Get("lowee")->FindObject(sHFcocktail_ULS))));
  TH2D bbeauty_LS_pythia (*(static_cast<TH2D*> (fHFbeauty.Get("lowee")->FindObject(sHFcocktail_LS))));
  //TH2D bbeauty_ULS_pythia (*(static_cast<TH2D*> (fHFbeauty.Get("lowee")->FindObject("hMeePtee_ULS_eta08_pt200"))));
  //TH2D bbeauty_LS_pythia (*(static_cast<TH2D*> (fHFbeauty.Get("lowee")->FindObject("hMeePtee_LS_eta08_pt200"))));
  TH2D bbeauty_rap    (*(static_cast<TH2D*> (fHFbeauty.Get("lowee")->FindObject("hRapBeautyQuarkMethod1"))));
  //TH2D bbeauty_pythia (*(static_cast<TH2D*> (fHFbeauty.Get("hMeePtee_ULS_LS_eta08_pt2_Pythia_Normtotal"))));
  //TH2D bbeauty_pythia (*(static_cast<TH2D*> (fHFbeauty.Get("hMeePtee_ULS_LS_eta08_pt2_Pythia_Normmid"))));
  // TH2D beauty_pythia (*(static_cast<TH2D*> (fHFbeauty.Get("hMeePtee_ULS_LS_eta08_pt4_Pythia_Normmid"))));
  
  
//  //TH2D bbeauty_powheg (*(static_cast<TH2D*> (fHFbeauty.Get(Form("hMeePtee_ULS_LS_eta08_pt4_Powheg%s_Normmid",syst.Data())))));
//  TH2D bbeauty_powheg (*(static_cast<TH2D*> (fHFbeauty.Get(Form("hMeePtee_ULS_LS_eta08_pt4_Powheg%s_Normtotal",syst.Data())))));
//  //TH2D bbeauty_powheg (*(static_cast<TH2D*> (fHFbeauty.Get(Form("hMeePtee_ULS_LS_eta08_pt2_Powheg%s_Normtotal",syst.Data())))));
//  //TH2D bbeauty_powheg (*(static_cast<TH2D*> (fHFbeauty.Get(Form("hMeePtee_ULS_LS_eta08_pt2_Powheg%s_Normmid",syst.Data())))));
//  // TH2D beauty_powheg (*(static_cast<TH2D*> (fHFbeauty.Get(Form("hMeePtee_ULS_LS_eta08_pt4_Powheg%s_Normmid",syst.Data())))));
//  bbeauty_powheg.SetName("beauty_powheg");


  TH2D ccharm_pythia = ccharm_ULS_pythia;
  TH2D bbeauty_pythia= bbeauty_ULS_pythia;

  ccharm_pythia.Add(&ccharm_LS_pythia,-1.); 
  bbeauty_pythia.Add(&bbeauty_LS_pythia,-1.);

  std::cout << &ccharm_pythia << "   " << &ccharm_rap << std::endl;
  ccharm_pythia.SetName("charm_pythiaPerugia2011");

  std::cout << &bbeauty_pythia << "   " << &bbeauty_rap << std::endl;
  bbeauty_pythia.SetName("beauty_pythiaPerugia2011");

  Bool_t IsNormMidRap = kTRUE;
  Double_t Nccbar, luminosity_cc;
  Double_t Nbbbar, luminosity_bb;
  Double_t xsec_dy_cc = 1.33  , xsec_cc = 12.16; 
  Double_t xsec_dy_bb = 0.0681, xsec_bb = 0.500;
  if(IsNormMidRap){
    Nccbar        = ccharm_rap.Integral(ccharm_rap.FindBin(-0.5),ccharm_rap.FindBin(0.5)-1)/2.;
    luminosity_cc = Nccbar/xsec_dy_cc;

    Nbbbar        = bbeauty_rap.Integral(bbeauty_rap.FindBin(-0.5),bbeauty_rap.FindBin(0.5)-1)/2.;
    luminosity_bb = Nbbbar/xsec_dy_bb;    
  }
  else{
    Nccbar        = ccharm_rap.Integral(-1,-1)/2.;
    luminosity_cc = Nccbar/xsec_cc;

    Nbbbar        = bbeauty_rap.Integral(-1,-1)/2.;
    luminosity_bb = Nbbbar/xsec_bb;
  }
  ccharm_pythia .Scale(1./(luminosity_cc*57.8)); 
  ccharm_pythia .Scale(0.096*0.096); 
  bbeauty_pythia.Scale(1./(luminosity_bb*57.8));  
 
  std::cout << "test4" << std::endl; 

  int meeMinBin = ccharm_pythia.GetXaxis()->FindBin(meeMin);
  int meeMaxBin = ccharm_pythia.GetXaxis()->FindBin(meeMax);
  int pteeMinBin = ccharm_pythia.GetYaxis()->FindBin(pteeMin);
  int pteeMaxBin = ccharm_pythia.GetYaxis()->FindBin(pteeMax);
  Double_t integal_charm_powheg_err=0.,integal_beauty_powheg_err=0.;
  //Double_t integal_charm_powheg = ccharm_powheg.IntegralAndError(meeMinBin,meeMaxBin,pteeMinBin,pteeMaxBin,integal_charm_powheg_err);
  //Double_t integal_beauty_powheg = bbeauty_powheg.IntegralAndError(meeMinBin,meeMaxBin,pteeMinBin,pteeMaxBin,integal_beauty_powheg_err);


  //
  // Rebin all the LF, HF to the data binning
  //

  TH2D signal(*RebinBis(ssignal));
  TH2D signalLow(*RebinBis(ssignalLow));
  TH2D signalHigh(*RebinBis(ssignalHigh));
  
  TH2D resonances(*RebinBis(rresonances));
  TH2D resonances_low(*RebinBis(rresonances_low));
  TH2D resonances_high(*RebinBis(rresonances_high));
  TH2D charm_pythia(*RebinBis(ccharm_pythia));
  TH2D beauty_pythia(*RebinBis(bbeauty_pythia));


  TH2D jpsi(*RebinBis(jjpsi));
  TH2D jpsi_low(*RebinBis(jjpsi_low));
  TH2D jpsi_high(*RebinBis(jjpsi_high));

  resonances.Add(&jpsi);
  resonances_low.Add(&jpsi_low);
  resonances_high.Add(&jpsi_high);


//  TH2D charm_powheg(*RebinBis(ccharm_powheg));
//  TH2D beauty_powheg(*RebinBis(bbeauty_powheg));
  
  /*
  Rebin2D(signal,signal);
  Rebin2D(signalLow,signal);
  Rebin2D(signalHigh,signal);
  
  Rebin2D(resonances,signal);
  Rebin2D(resonances_low,signal);
  Rebin2D(resonances_high,signal);
  Rebin2D(charm_pythia,signal);
  Rebin2D(beauty_pythia,signal);
  Rebin2D(charm_powheg,signal);
  Rebin2D(beauty_powheg,signal);
  */

  //
  // Check fraction of LF in the fit range for  paper
  //
  
  Int_t meelf1 = resonances.GetXaxis()->FindBin(meeMin);
  Int_t meelf2 = resonances.GetXaxis()->FindBin(meeMax);
  Double_t meelowedgelf = resonances.GetXaxis()->GetBinLowEdge(meelf1);
  Double_t meeupedgelf = resonances.GetXaxis()->GetBinUpEdge(meelf2-1);
  printf("MASS Low Edge LF %f and Up edge %f\n",meelowedgelf,meeupedgelf);
  Int_t pteelf1 = resonances.GetYaxis()->FindBin(pteeMin);
  Int_t pteelf2 = resonances.GetYaxis()->FindBin(pteeMax);
  Double_t pteelowedgelf = resonances.GetYaxis()->GetBinLowEdge(pteelf1);
  Double_t pteeupedgelf = resonances.GetYaxis()->GetBinUpEdge(pteelf2);
  printf("PTEE Low Edge LF %f and Up edge %f\n",pteelowedgelf,pteeupedgelf);
  Double_t integrallf = resonances.Integral(meelf1,meelf2-1,pteelf1,pteelf2);
  //
  Int_t mees1 = signal.GetXaxis()->FindBin(meeMin);
  Int_t mees2 = signal.GetXaxis()->FindBin(meeMax);
  Double_t meelowedges = signal.GetXaxis()->GetBinLowEdge(mees1);
  Double_t meeupedges = signal.GetXaxis()->GetBinUpEdge(mees2-1);
  printf("MASS Low Edge LF %f and Up edge %f\n",meelowedges,meeupedges);
  Int_t ptees1 = signal.GetYaxis()->FindBin(pteeMin);
  Int_t ptees2 = signal.GetYaxis()->FindBin(pteeMax);
  Double_t pteelowedges = signal.GetYaxis()->GetBinLowEdge(ptees1);
  Double_t pteeupedges = signal.GetYaxis()->GetBinUpEdge(ptees2);
  printf("PTEE Low Edge LF %f and Up edge %f\n",pteelowedges,pteeupedges);
  Double_t integrals = signal.Integral(mees1,mees2-1,ptees1,ptees2);
  Double_t ratioin = integrallf/integrals;
  printf("Integral LF %f, signal %f and ratio %f\n",integrallf,integrals,ratioin);



  //
  // fitting function
  //
  hRes = &resonances;
  // pythia
  TF2 fFunction("func",HFfunction,meeMin,meeMax,pteeMin,pteeMax,2);
  fFunction.SetParName(0,"s_cc");
  fFunction.SetParName(1,"s_bb");
  fFunction.SetParameter(0,1.);
  fFunction.SetParameter(1,1.);

  // Fit the data with PYTHIA
  hc = &charm_pythia;
  hb = &beauty_pythia;
  signal.Fit(&fFunction,"0MEIR");
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

  // Fit the data high/low with PYTHIA
  fFunction.SetParameter(0,1.);
  signalHigh.Fit(&fFunction,"0MEIRQ");
  Double_t par0_pythia_high = fFunction.GetParameter(0);
  Double_t par1_pythia_high = fFunction.GetParameter(1);
  fFunction.SetParameter(0,1.);
  signalLow.Fit(&fFunction,"0MEIRQ");
  Double_t par0_pythia_low = fFunction.GetParameter(0);
  Double_t par1_pythia_low = fFunction.GetParameter(1);

//  // Fit the data with powheg
//  hc = &charm_powheg;
//  hb = &beauty_powheg;
//  fFunction.SetParameter(0,1.);
//  fFunction.SetParameter(1,1.);
//  signal.Fit(&fFunction,"0MEIR");
//  Double_t par0_powheg = fFunction.GetParameter(0);
//  Double_t par1_powheg = fFunction.GetParameter(1);
//  Double_t parErr0_powheg = fFunction.GetParError(0);
//  Double_t parErr1_powheg = fFunction.GetParError(1);
//  Double_t chi2_powheg = fFunction.GetChisquare();
//  Double_t ndf_powheg = fFunction.GetNDF();
//  gMinuit->SetErrorDef(1);
//  TGraph *gr1_powheg = static_cast<TGraph*>(gMinuit->Contour(200,0,1));
//  gr1_powheg->SetFillColor(38);
//  gr1_powheg->SetLineWidth(2);
//  gMinuit->SetErrorDef(4);
//  TGraph *gr2_powheg = static_cast<TGraph*>(gMinuit->Contour(200,0,1));
//  gr2_powheg->SetFillColor(42);
//  gr2_powheg->SetLineWidth(2);
//  TGraph *grPoint_powheg = new TGraph(1);
//  grPoint_powheg->SetPoint(0,par0_powheg,par1_powheg);
//  grPoint_powheg->SetMarkerStyle(20);
//  grPoint_powheg->SetMarkerColor(kBlack);
//
//  // Fit the data sys high/low with powheg
//  fFunction.SetParameter(0,1.);
//  signalHigh.Fit(&fFunction,"0MEIRQ");
//  Double_t par0_powheg_high = fFunction.GetParameter(0);
//  Double_t par1_powheg_high = fFunction.GetParameter(1);
//  fFunction.SetParameter(0,1.);
//  signalLow.Fit(&fFunction,"0MEIRQ");
//  Double_t par0_powheg_low = fFunction.GetParameter(0);
//  Double_t par1_powheg_low = fFunction.GetParameter(1);

  //
  // end of fitting part
  //

  TH2D htmp(charm_pythia);
  htmp.SetName("htmp");
  htmp.Scale(par0_pythia);
  htmp.Add(&beauty_pythia,par1_pythia);
  TH2D DataOverFit_pythia(signal);
  DataOverFit_pythia.SetName("DataOverFit_pythia");
  DataOverFit_pythia.Divide(&htmp);

//  htmp = TH2D(charm_powheg);
//  htmp.SetName("htmp");
//  htmp.Scale(par0_powheg);
//  htmp.Add(&beauty_powheg,par1_powheg);
//  TH2D DataOverFit_powheg(signal);
//  DataOverFit_powheg.SetName("DataOverFit_powheg");
//  DataOverFit_powheg.Divide(&htmp);

  

  // drawing
  TCanvas *c = new TCanvas("c","",800,800);
  gPad->SetTopMargin(0.02);
  gPad->SetLeftMargin(0.12);
  gPad->SetRightMargin(0.02);
  
  // ptee in the fit range pythia
  TH1D *hcPtee_pythia = static_cast<TH1D*> (charm_pythia.ProjectionY("cPtee_pythia",hc->GetXaxis()->FindBin(meeMin),hc->GetXaxis()->FindBin(meeMax-1.e-9)));
  hcPtee_pythia->SetLineWidth(2);
  hcPtee_pythia->SetLineColor(kMagenta);
  hcPtee_pythia->SetMarkerColor(kMagenta);
  hcPtee_pythia->Scale(1.,"width");
  hcPtee_pythia->SetDirectory(0);

  TH1D *hbPtee_pythia = static_cast<TH1D*> (beauty_pythia.ProjectionY("bPtee_pythia",hb->GetXaxis()->FindBin(meeMin),hb->GetXaxis()->FindBin(meeMax-1.e-9)));
  hbPtee_pythia->SetLineWidth(2);
  hbPtee_pythia->SetLineColor(kOrange+2);
  hbPtee_pythia->SetMarkerColor(kOrange+2);
  hbPtee_pythia->Scale(1.,"width");
  hbPtee_pythia->SetDirectory(0);

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

//  // ptee in the fit range powheg
//  TH1D *hcPtee_powheg = static_cast<TH1D*> (charm_powheg.ProjectionY("cPtee_powheg",hc->GetXaxis()->FindBin(meeMin),hc->GetXaxis()->FindBin(meeMax-1.e-9)));
//  hcPtee_powheg->SetLineWidth(2);
//  hcPtee_powheg->SetLineColor(kMagenta);
//  hcPtee_powheg->SetMarkerColor(kMagenta);
//  hcPtee_powheg->Scale(1.,"width");
//
//  TH1D *hbPtee_powheg = static_cast<TH1D*> (beauty_powheg.ProjectionY("bPtee_powheg",hb->GetXaxis()->FindBin(meeMin),hb->GetXaxis()->FindBin(meeMax-1.e-9)));
//  hbPtee_powheg->SetLineWidth(2);
//  hbPtee_powheg->SetLineColor(kOrange+2);
//  hbPtee_powheg->SetMarkerColor(kOrange+2);
//  hbPtee_powheg->Scale(1.,"width");
//
//  TH1D *hHFPtee_powheg = static_cast<TH1D*> (hcPtee_powheg->Clone("hHFPtee_powheg"));
//  hHFPtee_powheg->Add(hbPtee_powheg);
//  hHFPtee_powheg->SetLineColor(kBlack);
//  hHFPtee_powheg->SetMarkerColor(kBlack);
//
//  TH1D *hcPtee_scaled_powheg = static_cast<TH1D*> (hcPtee_powheg->Clone("hcPtee_scaled_powheg"));
//  hcPtee_scaled_powheg->Scale(par0_powheg);
//  hcPtee_powheg ->SetLineStyle(kDashed);
//
//  TH1D *hbPtee_scaled_powheg = static_cast<TH1D*> (hbPtee_powheg->Clone("hbPtee_scaled_powheg"));
//  hbPtee_scaled_powheg->Scale(par1_powheg);
//  hbPtee_powheg ->SetLineStyle(kDashed);
//
//  TH1D *hHFPtee_scaled_powheg = static_cast<TH1D*> (hcPtee_scaled_powheg->Clone("hHFPtee_scaled_powheg"));
//  hHFPtee_scaled_powheg->Add(hbPtee_scaled_powheg);
//  hHFPtee_scaled_powheg->SetLineColor(kBlack);
//  hHFPtee_scaled_powheg->SetMarkerColor(kBlack);
//  hHFPtee_powheg->SetLineStyle(kDashed);
//
//  TH1D *hHFPtee_pythia_comp = static_cast<TH1D*> (hHFPtee_pythia->Clone("hHFPtee_pythia_comp"));
//  hHFPtee_pythia_comp->SetLineColor(kOrange+2);
//  TH1D *hHFPtee_powheg_comp = static_cast<TH1D*> (hHFPtee_powheg->Clone("hHFPtee_powheg_comp"));
//  hHFPtee_powheg_comp->SetLineColor(kBlack);
//  TH1D *hHFPtee_scaled_pythia_comp = static_cast<TH1D*> (hHFPtee_scaled_pythia->Clone("hHFPtee_scaled_pythia_comp"));
//  hHFPtee_scaled_pythia_comp->SetLineColor(kOrange+2);
//  TH1D *hHFPtee_scaled_powheg_comp = static_cast<TH1D*> (hHFPtee_scaled_powheg->Clone("hHFPtee_scaled_powheg_comp"));
//  hHFPtee_scaled_powheg_comp->SetLineColor(kBlack);

  TH1D *signalPtee = static_cast<TH1D*> (signal.ProjectionY("signalPtee",signal.GetXaxis()->FindBin(meeMin),signal.GetXaxis()->FindBin(meeMax-1.e-9)));
  signalPtee->GetXaxis()->SetTitle("Ptee");
  signalPtee->SetTitle("");
  signalPtee->SetLineColor(kBlack);
  signalPtee->SetMarkerColor(kBlack);
  signalPtee->Scale(1.,"width");
  signalPtee->SetMarkerStyle(20);
  signalPtee->SetMarkerSize(0.8);
//  signalPtee->GetYaxis()->SetRangeUser(8.001e-7,8.999e-4);
  signalPtee->GetXaxis()->SetTitleOffset(1.);
  signalPtee->GetYaxis()->SetRangeUser(5.001e-7,1.999e-4);

  TPaveText T_mee = GetTextBox(x1, 0.80, 0.95, 0.86);
  T_mee.AddText(Form("%2.1f < m_{ee} < %2.1f GeV/c^{2}", meeMin,meeMax));

  TH1D *hResPtee = static_cast<TH1D*> (resonances.ProjectionY("hResPtee",resonances.GetXaxis()->FindBin(meeMin-1.e-10),resonances.GetXaxis()->FindBin(meeMax-1.e-10)));
  hResPtee->Scale(1.,"width");
  hResPtee->SetLineWidth(2);
  hResPtee->SetLineColor(kRed);
  TH1D *hSumPtee_pythia = static_cast<TH1D*> (hHFPtee_pythia->Clone("hSumPtee_pythia"));
  TH1D *hSumPtee_scaled_pythia = static_cast<TH1D*> (hHFPtee_scaled_pythia->Clone("hSumPtee_scaled_pythia"));
//  TH1D *hSumPtee_powheg = static_cast<TH1D*> (hHFPtee_powheg->Clone("hSumPtee_powheg"));
//  TH1D *hSumPtee_scaled_powheg = static_cast<TH1D*> (hHFPtee_scaled_powheg->Clone("hSumPtee_scaled_powheg"));
  hSumPtee_pythia       ->Add(hResPtee);
  hSumPtee_scaled_pythia->Add(hResPtee);
//  hSumPtee_powheg       ->Add(hResPtee);
//  hSumPtee_scaled_powheg->Add(hResPtee);
  
  
  TLegend leg(x1,0.77,0.95,0.9);
  leg.SetFillColor(0);
  leg.SetFillStyle(0);
  leg.SetBorderSize(0);
  leg.SetTextSize(0.015);
  leg.AddEntry(signalPtee,"data","pl");
  leg.AddEntry(hResPtee,"resonances","l");
  leg.AddEntry(hSumPtee_scaled_pythia,"cocktail sum scaled","l");
  leg.AddEntry(hcPtee_scaled_pythia,"c#bar{c} scaled","l");
  leg.AddEntry(hbPtee_scaled_pythia,"b#bar{b} scaled","l");
  leg.AddEntry(hSumPtee_pythia,"cocktail sum","l");
  leg.AddEntry(hcPtee_pythia,"c#bar{c}","l");
  leg.AddEntry(hbPtee_pythia,"b#bar{b}","l");



  TLegend leg2(x1,0.77,0.95,0.9);
  leg2.SetFillColor(0);
  leg2.SetFillStyle(0);
  leg2.SetBorderSize(0);
  leg2.SetTextSize(0.015);
  //leg2.AddEntry(hHFPtee_pythia_comp,"pythia","pl");
//  leg2.AddEntry(hHFPtee_powheg_comp,"powheg","l");
  //leg2.AddEntry(hHFPtee_scaled_pythia_comp,"pythia scaled","l");
//  leg2.AddEntry(hHFPtee_scaled_powheg_comp,"powheg scaled","l");


//  gPad->SetLogy();
//  signalPtee->Draw();
//  hcPtee_pythia->Draw("same");
//  hbPtee_pythia->Draw("same");
//  hHFPtee_pythia->Draw("same");
//  hcPtee_scaled_pythia->Draw("same");
//  hbPtee_scaled_pythia->Draw("same");
//  hHFPtee_scaled_pythia->Draw("same");
//  T_mee.Draw("same");
//  leg.Draw("same");
//  c.SaveAs(Form("./output/%s/pythia_ptee.pdf",cs.Data()));
//
//  gPad->SetLogy();
//  signalPtee->Draw();
//  hcPtee_powheg->Draw("same");
//  hbPtee_powheg->Draw("same");
//  hHFPtee_powheg->Draw("same");
//  hcPtee_scaled_powheg->Draw("same");
//  hbPtee_scaled_powheg->Draw("same");
//  hHFPtee_scaled_powheg->Draw("same");
//  T_mee.Draw("same");
//  leg.Draw("same");
//  c.SaveAs(Form("./output/%s/powheg_ptee.pdf",cs.Data()));

    TH2D *hDrawPtee = new TH2D("hDrawPtee","",1,0.,8.,1,1.001e-7,8.999e-2);
    hDrawPtee->GetXaxis()->SetTitle("p_{T,ee} (GeV/c)");
    hDrawPtee->GetYaxis()->SetTitle("dN/dp_{T,ee} (GeV/c)^{-1}");


    gPad->SetLogy();
    gPad->SetTicks();
    hDrawPtee->Draw();
    hcPtee_pythia->Draw("L,same");
    hbPtee_pythia->Draw("L,same");
    hcPtee_scaled_pythia->Draw("L,same");
    hbPtee_scaled_pythia->Draw("L,same");
    hResPtee->Draw("same");
    hSumPtee_pythia->Draw("same");
    hSumPtee_scaled_pythia->Draw("same");
    signalPtee->Draw("same");
    leg.Draw("same");
    T_mee.Draw("same");
    c->SaveAs("./output/pythia_Ptee.pdf");
    c->SaveAs("./output/pythia_Ptee.root");
     

    //TFile *fa = TFile::Open(Form("./output/%s/pythia_Ptee_%s.root",cs.Data(),syst.Data()));
    //c->Write();
    //fa->Close();
    
//    gPad->SetLogy();
//    gPad->SetTicks();
//    hDrawPtee->Draw();
//    hcPtee_powheg->Draw("L,same");
//    hbPtee_powheg->Draw("L,same");
//    hcPtee_scaled_powheg->Draw("L,same");
//    hbPtee_scaled_powheg->Draw("L,same");
//    hResPtee->Draw("same");
//    hSumPtee_powheg->Draw("same");
//    hSumPtee_scaled_powheg->Draw("same");
//    signalPtee->Draw("same");
//    leg.Draw("same");
//    T_mee.Draw("same");
//    c->SaveAs(Form("./output/%s/powheg_Ptee_%s.pdf",cs.Data(),syst.Data()));
//    c->SaveAs(Form("./output/%s/powheg_Ptee_%s.root",cs.Data(),syst.Data()));

    //TFile *fb = TFile::Open(Form("./output/%s/powheg_Ptee_%s.root",cs.Data(),syst.Data()));
    //c->Write();
    //fb->Close();
    
    // too much stuff
    /*
      hDrawPtee->Draw();
      hHFPtee_pythia_comp->Draw("same");
      hHFPtee_powheg_comp->Draw("same");
      hHFPtee_scaled_pythia_comp->Draw("same");
      hHFPtee_scaled_powheg_comp->Draw("same");
      leg2.Draw("same");
      T_mee.Draw("same");
      c.SaveAs(Form("./output/%s/modelComparison_ptee_%s.pdf",cs.Data(),syst.Data()));
    */

    
  TH1D *hcMee_pythia,*hbMee_pythia,*hHFMee_pythia,*hcMee_powheg,*hbMee_powheg,*hHFMee_powheg,*signalMee;
  TH1D *hcMee_scaled_pythia,*hbMee_scaled_pythia,*hHFMee_scaled_pythia,*hcMee_scaled_powheg,*hbMee_scaled_powheg,*hHFMee_scaled_powheg;
  TH1D *hHFMee_pythia_comp,*hHFMee_powheg_comp,*hHFMee_scaled_pythia_comp,*hHFMee_scaled_powheg_comp;

  TH2D *hDrawMee = new TH2D("hDrawMee","",1,0.,3.3,1,1.001e-8,8.999e-2);
  hDrawMee->GetXaxis()->SetTitle("m_{ee} (GeV/c^{2})");
  hDrawMee->GetYaxis()->SetTitle("dN/dm_{ee} (GeV/c^{2})^{-1}");

  // Would do the plot bin by bin but maybe too much at the end but only one bin
  
  for(UInt_t i = 0; i < vPtee.size()-1; ++i){
    hcMee_pythia  = static_cast<TH1D*> (charm_pythia.ProjectionX("cMee_pythia",charm_pythia.GetYaxis()->FindBin(vPtee.at(i)),charm_pythia.GetYaxis()->FindBin(vPtee.at(i+1)-1.e-10)));
    hcMee_pythia->SetLineWidth(2);
    hcMee_pythia->SetLineColor(kMagenta);
    hcMee_pythia->SetMarkerColor(kMagenta);
    hcMee_pythia ->Scale(1.,"width");

    hbMee_pythia  = static_cast<TH1D*> (beauty_pythia.ProjectionX("bMee_pythia",beauty_pythia.GetYaxis()->FindBin(vPtee.at(i)),beauty_pythia.GetYaxis()->FindBin(vPtee.at(i+1)-1.e-10)));
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

//    hcMee_powheg  = static_cast<TH1D*> (charm_powheg.ProjectionX("cMee_powheg",charm_powheg.GetYaxis()->FindBin(vPtee.at(i)),charm_powheg.GetYaxis()->FindBin(vPtee.at(i+1)-1.e-10)));
//    hcMee_powheg->SetLineWidth(2);
//    hcMee_powheg->SetLineColor(kMagenta);
//    hcMee_powheg->SetMarkerColor(kMagenta);
//    hcMee_powheg ->Scale(1.,"width");
//
//    hbMee_powheg  = static_cast<TH1D*> (beauty_powheg.ProjectionX("bMee_powheg",beauty_powheg.GetYaxis()->FindBin(vPtee.at(i)),beauty_powheg.GetYaxis()->FindBin(vPtee.at(i+1)-1.e-10)));
//    hbMee_powheg->SetLineWidth(2);
//    hbMee_powheg->SetLineColor(kOrange+2);
//    hbMee_powheg->SetMarkerColor(kOrange+2);
//    hbMee_powheg ->Scale(1.,"width");
//
//    hHFMee_powheg = static_cast<TH1D*> (hcMee_powheg->Clone("hHFMee_powheg"));
//    hHFMee_powheg->Add(hbMee_powheg);
//    hHFMee_powheg->SetLineColor(kBlack);
//    hHFMee_powheg->SetMarkerColor(kBlack);
//
//    hcMee_scaled_powheg = static_cast<TH1D*> (hcMee_powheg->Clone("hcMee_scaled_powheg"));
//    hcMee_scaled_powheg->Scale(par0_powheg);
//    hcMee_scaled_powheg->SetLineStyle(kSolid);
//    hcMee_powheg->SetLineStyle(kDashed);
//
//    hbMee_scaled_powheg = static_cast<TH1D*> (hbMee_powheg->Clone("hbMee_scaled_powheg"));
//    hbMee_scaled_powheg->Scale(par1_powheg);
//    hbMee_scaled_powheg->SetLineStyle(kSolid);
//    hbMee_powheg->SetLineStyle(kDashed);
//
//    hHFMee_scaled_powheg = static_cast<TH1D*> (hcMee_scaled_powheg->Clone("hHFMee_scaled_powheg"));
//    hHFMee_scaled_powheg->Add(hbMee_scaled_powheg);
//    hHFMee_scaled_powheg->SetLineColor(kBlack);
//    hHFMee_scaled_powheg->SetMarkerColor(kBlack);
//    hHFMee_scaled_powheg->SetLineStyle(kSolid);
//    hHFMee_powheg->SetLineStyle(kDashed);
//
//    hHFMee_pythia_comp = static_cast<TH1D*> (hHFMee_pythia->Clone("hHFMee_pythia_comp"));
//    hHFMee_pythia_comp->SetLineColor(kOrange+2);
//    hHFMee_powheg_comp = static_cast<TH1D*> (hHFMee_powheg->Clone("hHFMee_powheg_comp"));
//    hHFMee_powheg_comp->SetLineColor(kBlack);
//    hHFMee_scaled_pythia_comp = static_cast<TH1D*> (hHFMee_scaled_pythia->Clone("hHFMee_scaled_pythia_comp"));
//    hHFMee_scaled_pythia_comp->SetLineColor(kOrange+2);
//    hHFMee_scaled_powheg_comp = static_cast<TH1D*> (hHFMee_scaled_powheg->Clone("hHFMee_scaled_powheg_comp"));
//    hHFMee_scaled_powheg_comp->SetLineColor(kBlack);

    signalMee  = static_cast<TH1D*> (signal.ProjectionX("signalMee",signal.GetYaxis()->FindBin(vPtee.at(i)),signal.GetYaxis()->FindBin(vPtee.at(i+1)-1.e-10)));
    signalMee->GetXaxis()->SetTitle("Mee");
    signalMee->SetTitle("");
    signalMee->SetLineColor(kBlack);
    signalMee->SetMarkerColor(kBlack);
    signalMee->Scale(1.,"width");
    signalMee->SetMarkerStyle(20);
    signalMee->SetMarkerSize(0.8);
//    signalMee ->GetYaxis()->SetRangeUser(8.001e-7,8.999e-4);
    signalMee->GetXaxis()->SetTitleOffset(1.);
    signalMee->GetYaxis()->SetRangeUser(8.001e-8,3.999e-4);

    TPaveText T_ptee = GetTextBox(x1, 0.80, 0.95, 0.86);
    T_ptee.AddText(Form("%2.1f < p_{T}^{ee} < %2.1f GeV/c", vPtee.at(i),vPtee.at(i+1)));

    TH1D *hResMee = static_cast<TH1D*> (resonances.ProjectionX("hResMee",resonances.GetYaxis()->FindBin(vPtee.at(i)),resonances.GetYaxis()->FindBin(vPtee.at(i+1)-1.e-10)));
    hResMee->Scale(1.,"width");
    hResMee->SetLineWidth(2);
    hResMee->SetLineColor(kRed);
    TH1D *hSumMee_pythia = static_cast<TH1D*> (hHFMee_pythia->Clone("hSumMee_pythia"));
    TH1D *hSumMee_scaled_pythia = static_cast<TH1D*> (hHFMee_scaled_pythia->Clone("hSumMee_scaled_pythia"));
//    TH1D *hSumMee_powheg = static_cast<TH1D*> (hHFMee_powheg->Clone("hSumMee_powheg"));
//    TH1D *hSumMee_scaled_powheg = static_cast<TH1D*> (hHFMee_scaled_powheg->Clone("hSumMee_scaled_powheg"));
    hSumMee_pythia       ->Add(hResMee);
    hSumMee_scaled_pythia->Add(hResMee);
//    hSumMee_powheg       ->Add(hResMee);
//    hSumMee_scaled_powheg->Add(hResMee);

    gPad->SetLogy();
    hDrawMee->Draw();
    hcMee_pythia->Draw("same");
    hbMee_pythia->Draw("same");
    hcMee_scaled_pythia->Draw("same");
    hbMee_scaled_pythia->Draw("same");
    hResMee->Draw("same");
    hSumMee_pythia->Draw("same");
    hSumMee_scaled_pythia->Draw("same");
    signalMee->Draw("same");
    leg.Draw("same");
    T_ptee.Draw("same");
    c->SaveAs(Form("./output/pythia_mee_%d.pdf",i));
    c->SaveAs(Form("./output/pythia_mee_%d.root",i));

    //TFile *fc = TFile::Open(Form("./output/%s/pythia_mee_%s%d.pdf",cs.Data(),syst.Data(),i));
    //c->Write();
    //fc->Close();

//    gPad->SetLogy();
//    hDrawMee->Draw();
//    hcMee_powheg->Draw("same");
//    hbMee_powheg->Draw("same");
//    hcMee_scaled_powheg->Draw("same");
//    hbMee_scaled_powheg->Draw("same");
//    hResMee->Draw("same");
//    hSumMee_powheg->Draw("same");
//    hSumMee_scaled_powheg->Draw("same");
//    signalMee->Draw("same");
//    leg.Draw("same");
//    T_ptee.Draw("same");
//    c->SaveAs(Form("./output/%s/powheg_mee_%s%d.pdf",cs.Data(),syst.Data(),i));
//    c->SaveAs(Form("./output/%s/powheg_mee_%s%d.root",cs.Data(),syst.Data(),i));

    //TFile *fd = TFile::Open(Form("./output/%s/powheg_mee_%s%d.pdf",cs.Data(),syst.Data(),i));
    //c->Write();
    //fd->Close();

    // Too much stuff kill the info
    /*
    hDrawMee->Draw();
    hHFMee_pythia_comp->Draw("same");
    hHFMee_powheg_comp->Draw("same");
    hHFMee_scaled_pythia_comp->Draw("same");
    hHFMee_scaled_powheg_comp->Draw("same");
    leg2.Draw("same");
    T_ptee.Draw("same");
    c.SaveAs(Form("./output/%s/modelComparison_mee_%s%d.pdf",cs.Data(),syst.Data(),i));
    */

  }


  Double_t x(0.),y(0.);
  for(Int_t i = 0; i < gr1_pythia->GetN(); ++i){

    gr1_pythia->GetPoint(i,x,y);
    gr1_pythia->SetPoint(i,x,y);
//    gr1_powheg->GetPoint(i,x,y);
//    gr1_powheg->SetPoint(i,x,y);
    gr2_pythia->GetPoint(i,x,y);
    gr2_pythia->SetPoint(i,x,y);
//    gr2_powheg->GetPoint(i,x,y);
//    gr2_powheg->SetPoint(i,x,y);

  }
  grPoint_pythia->GetPoint(0,x,y);
  grPoint_pythia->SetPoint(0,x,y);
//  grPoint_powheg->GetPoint(0,x,y);
//  grPoint_powheg->SetPoint(0,x,y);
  Double_t ndf = fFunction.GetNDF();

  hc = static_cast<TH2D*> (charm_pythia .Clone("charmPythia"));
  hb = static_cast<TH2D*> (beauty_pythia.Clone("beautyPythia"));
  TH2D *hTest_pythia = new TH2D("hTest_pythia","",500,0.0,3.0,500,0.0,3.0);
  for(Int_t ix = 1; ix <= 500; ++ix){
    for(Int_t iy = 1; iy <= 500; ++iy){
      fFunction.SetParameter(0,hTest_pythia->GetXaxis()->GetBinWidth(ix) * ix);
      fFunction.SetParameter(1,hTest_pythia->GetYaxis()->GetBinWidth(iy) * iy);
      Double_t chi = signal.Chisquare(&fFunction,"R");
      hTest_pythia->SetBinContent(ix,iy,chi/1.);
    }
  }

//  hc = static_cast<TH2D*> (charm_powheg .Clone("charmPowheg"));
//  hb = static_cast<TH2D*> (beauty_powheg.Clone("beautyPowheg"));
//  TH2D *hTest_powheg = new TH2D("hTest_powheg","",500,0.0,3.0,500,0.0,3.0);
//  for(Int_t ix = 1; ix <= 500; ++ix){
//    for(Int_t iy = 1; iy <= 500; ++iy){
//      fFunction.SetParameter(0,hTest_powheg->GetXaxis()->GetBinWidth(ix) * ix);
//      fFunction.SetParameter(1,hTest_powheg->GetYaxis()->GetBinWidth(iy) * iy);
//      Double_t chi = signal.Chisquare(&fFunction,"R");
//      hTest_powheg->SetBinContent(ix,iy,chi/1.);
//    }
//  }

  hTest_pythia->GetXaxis()->SetTitle("scaling_{c#bar{c}} (mb)");
  hTest_pythia->GetYaxis()->SetTitle("scaling_{b#bar{b}} (mb)");
  hTest_pythia->GetYaxis()->SetTitleOffset(1.2);
  hTest_pythia->GetZaxis()->SetTitle("#chi^{2}");
  // hTest_pythia->GetXaxis()->SetRangeUser(0.,55.);
  // hTest_pythia->GetYaxis()->SetRangeUser(1.,4.5);
  // hTest_pythia->GetZaxis()->SetRangeUser(0.8,2.5);

//  hTest_powheg->GetXaxis()->SetTitle("scaling_{c#bar{c}} (mb)");
//  hTest_powheg->GetYaxis()->SetTitle("scaling_{b#bar{b}} (mb)");
//  hTest_powheg->GetYaxis()->SetTitleOffset(1.2);
//  hTest_powheg->GetZaxis()->SetTitle("#chi^{2}");
  // hTest_powheg->GetXaxis()->SetRangeUser(0.,55.);
  // hTest_powheg->GetYaxis()->SetRangeUser(1.,4.5);
  // hTest_powheg->GetZaxis()->SetRangeUser(0.8,2.5);

  hTest_pythia->GetZaxis()->SetRangeUser(0.,350.);
//  hTest_powheg->GetZaxis()->SetRangeUser(0.,350.);

  printf("PYTHIA\n");
  printf("scaling_{c#bar{c}} = %5.3f #pm %5.3f (stat.) #pm %5.3f (sys.)\n", par0_pythia,parErr0_pythia,(par0_pythia-par0_pythia_low));
  printf("scaling_{b#bar{b}} = %5.3f #pm %5.3f (stat.) #pm %5.3f (sys.)\n", par1_pythia,parErr1_pythia,(par1_pythia-par1_pythia_low));
  printf("#sigma_{c#bar{c}} = %5.3f #pm %5.3f (stat.) - %5.3f + %5.3f (sys.) mb\n", par0_pythia*sigma_ccbar,parErr0_pythia*sigma_ccbar,(par0_pythia-par0_pythia_low)*sigma_ccbar,(par0_pythia_high-par0_pythia)*sigma_ccbar);
  printf("#sigma_{b#bar{b}} = %5.3f #pm %5.3f (stat.) - %5.3f + %5.3f (sys.) mb\n", par1_pythia*sigma_bbbar,parErr1_pythia*sigma_bbbar,(par1_pythia-par1_pythia_low)*sigma_bbbar,(par1_pythia_high-par1_pythia)*sigma_bbbar);
  printf("#chi^{2}/ndf = % 5.3f\n", chi2_pythia/ndf_pythia);

//  printf("POWHEG\n");
//
//  printf("scaling_{c#bar{c}} = %5.3f #pm %5.3f (stat.) #pm %5.3f (sys.)\n", par0_powheg,parErr0_powheg,(par0_powheg-par0_powheg_low));
//  printf("scaling_{b#bar{b}} = %5.3f #pm %5.3f (stat.) #pm %5.3f (sys.)\n", par1_powheg,parErr1_powheg,(par1_powheg-par1_powheg_low));
//  printf("#sigma_{c#bar{c}} = %5.3f #pm %5.3f (stat.) - %5.3f + %5.3f  (sys.) mb\n", par0_powheg*sigma_ccbar,parErr0_powheg*sigma_ccbar,(par0_powheg-par0_powheg_low)*sigma_ccbar,(par0_powheg_high-par0_powheg)*sigma_ccbar);
//  printf("#sigma_{b#bar{b}} = %5.3f #pm %5.3f (stat.) - %5.3f + %5.3f (sys.) mb\n", par1_powheg*sigma_bbbar,parErr1_powheg*sigma_bbbar,(par1_powheg-par1_powheg_low)*sigma_bbbar,(par1_powheg_high-par1_powheg)*sigma_bbbar);
//  printf("#chi^{2}/ndf = % 5.3f\n", chi2_powheg/ndf_powheg);


  TPaveText T_pythia = GetTextBox(0.45, 0.72, 0.90, 0.86);

  T_pythia.AddText(Form("scaling_{c#bar{c}} = %5.3f #pm %5.3f (stat.) #pm %5.3f (sys.)", par0_pythia,parErr0_pythia,(par0_pythia-par0_pythia_low)));
  T_pythia.AddText(Form("scaling_{b#bar{b}} = %5.3f #pm %5.3f (stat.) #pm %5.3f (sys.)", par1_pythia,parErr1_pythia,(par1_pythia-par1_pythia_low)));
  T_pythia.AddText(Form("#sigma_{c#bar{c}} = %5.3f #pm %5.3f (stat.) #pm %5.3f (sys.) mb", par0_pythia*sigma_ccbar,parErr0_pythia*sigma_ccbar,(par0_pythia-par0_pythia_low)*sigma_ccbar));
  T_pythia.AddText(Form("#sigma_{b#bar{b}} = %5.3f #pm %5.3f (stat.) #pm %5.3f (sys.) mb", par1_pythia*sigma_bbbar,parErr1_pythia*sigma_bbbar,(par1_pythia-par1_pythia_low)*sigma_bbbar));
  T_pythia.AddText(Form("#chi^{2} = %5.3f  ndf = %3.0f", chi2_pythia,ndf_pythia));
  T_pythia.AddText(Form("#chi^{2}/ndf = % 5.3f", chi2_pythia/ndf_pythia));

//  TPaveText T_powheg = GetTextBox(0.45, 0.72, 0.90, 0.86);
//  T_powheg.AddText(Form("scaling_{c#bar{c}} = %5.3f #pm %5.3f (stat.) #pm %5.3f (sys.)", par0_powheg,parErr0_powheg,(par0_powheg-par0_powheg_low)));
//  T_powheg.AddText(Form("scaling_{b#bar{b}} = %5.3f #pm %5.3f (stat.) #pm %5.3f (sys.)", par1_powheg,parErr1_powheg,(par1_powheg-par1_powheg_low)));
//  T_powheg.AddText(Form("#sigma_{c#bar{c}} = %5.3f #pm %5.3f (stat.) #pm %5.3f (sys.) mb", par0_powheg*sigma_ccbar,parErr0_powheg*sigma_ccbar,(par0_powheg-par0_powheg_low)*sigma_ccbar));
//  T_powheg.AddText(Form("#sigma_{b#bar{b}} = %5.3f #pm %5.3f (stat.) #pm %5.3f (sys.) mb", par1_powheg*sigma_bbbar,parErr1_powheg*sigma_bbbar,(par1_powheg-par1_powheg_low)*sigma_bbbar));
//  T_powheg.AddText(Form("#chi^{2} = %5.3f  ndf = %3.0f", chi2_powheg,ndf_powheg));
//  T_powheg.AddText(Form("#chi^{2}/ndf = % 5.3f", chi2_powheg/ndf_powheg));

  //std::cout << Form(">>> Fit Results %s",syst.Data()) << std::endl;
  //std::cout << ">>> Pythia" << std::endl;
  //std::cout << ">>> charm: " << par0_pythia << "+-" << parErr0_pythia << "(stat) +-" << abs(par0_pythia-par0_pythia_low) << "syst" << std::endl;
  //std::cout << ">>> beauty: " << par1_pythia << "+-" << parErr1_pythia << "(stat) +-" << abs(par1_pythia-par1_pythia_low) << "syst" << std::endl;
  //std::cout << ">>> Powheg" << std::endl;
  //std::cout << ">>> charm: " << par0_powheg << "+-" << parErr0_powheg << "(stat) +-" << abs(par0_powheg-par0_powheg_low) << "syst" << std::endl;
  //std::cout << ">>> beauty: " << par1_powheg << "+-" << parErr1_powheg << "(stat) +-" << abs(par1_powheg-par1_powheg_low) << "syst" << std::endl;
  //std::cout << ">>> Integrals:" << '\n';
  //std::cout << ">>> charm: " << integal_charm_powheg << " +- " << integal_charm_powheg_err << '\n';
  //std::cout << ">>> beauty: " << integal_beauty_powheg << " +- " << integal_beauty_powheg_err << '\n';


  gPad->SetTopMargin(0.10);
  gPad->SetLeftMargin(0.10);
  gPad->SetRightMargin(0.14);

  gr2_pythia->SetName("gr2_pythia");
  gr1_pythia->SetName("gr1_pythia");
  grPoint_pythia->SetName("grPoint_pythia");

//  gr2_powheg->SetName("gr2_powheg");
//  gr1_powheg->SetName("gr1_powheg");
//  grPoint_powheg->SetName("grPoint_powheg");




  gPad->SetLogy(0);
  gPad->SetLogz(0);
  hTest_pythia->Draw("colz");
  gr2_pythia->Draw("l");
  gr1_pythia->Draw("l");
  grPoint_pythia->Draw("p");
  T_pythia .Draw("same");
  c->SaveAs("./output/gr_pythia.png");
  c->SaveAs("./output/gr_pythia.root");

  //gPad->SetLogy(0);
  //gPad->SetLogz(0);
  //hTest_powheg->Draw("colz");
  //gr2_powheg->Draw("l");
  //gr1_powheg->Draw("l");
  //grPoint_powheg->Draw("p");
  //T_powheg .Draw("same");
  //c->SaveAs(Form("./output/%s/gr_powheg.png",cs.Data()));
  //c->SaveAs(Form("./output/%s/gr_powheg.root",cs.Data()));

 TH2D HFscaled_pythia(charm_pythia);
 HFscaled_pythia.SetName("HFscaled_pythia");
 HFscaled_pythia.Scale(par0_pythia);
 HFscaled_pythia.Add(&beauty_pythia,par1_pythia);
 //TH2D HFscaled_powheg(charm_powheg);
 //HFscaled_powheg.SetName("HFscaled_powheg");
 //HFscaled_powheg.Scale(par0_powheg);
 //HFscaled_powheg.Add(&beauty_powheg,par1_powheg);

 TH2D HFscaledLow_pythia(charm_pythia);
 HFscaledLow_pythia.SetName("HFscaledLow_pythia");
 HFscaledLow_pythia.Scale(par0_pythia_low);
 HFscaledLow_pythia.Add(&beauty_pythia,par1_pythia_low);
 //TH2D HFscaledLow_powheg(charm_powheg);
 //HFscaledLow_powheg.SetName("HFscaledLow_powheg");
 //HFscaledLow_powheg.Scale(par0_powheg_low);
 //HFscaledLow_powheg.Add(&beauty_powheg,par1_powheg_low);

 TH2D HFscaledHigh_pythia(charm_pythia);
 HFscaledHigh_pythia.SetName("HFscaledHigh_pythia");
 HFscaledHigh_pythia.Scale(par0_pythia_high);
 HFscaledHigh_pythia.Add(&beauty_pythia,par1_pythia_high);
 //TH2D HFscaledHigh_powheg(charm_powheg);
 //HFscaledHigh_powheg.SetName("HFscaledHigh_powheg");
 //HFscaledHigh_powheg.Scale(par0_powheg_high);
 //HFscaledHigh_powheg.Add(&beauty_powheg,par1_powheg_high);


 TH2D HF_pythia(charm_pythia);
 HF_pythia.SetName("HF_pythia");
 HF_pythia.Add(&beauty_pythia);
 //TH2D HF_powheg(charm_powheg);
 //HF_powheg.SetName("HF_powheg");
 //HF_powheg.Add(&beauty_powheg);

 TH2D HFLow_pythia(charm_pythia);
 HFLow_pythia.SetName("HFLow_pythia");
 HFLow_pythia.Scale(1.-ccbarErrLow);
 HFLow_pythia.Add(&beauty_pythia,1.-bbbarErrLow);
 //TH2D HFLow_powheg(charm_powheg);
 //HFLow_powheg.SetName("HFLow_powheg");
 //HFLow_powheg.Scale(1.-ccbarErrLow);
 //HFLow_powheg.Add(&beauty_powheg,1.-bbbarErrLow);

 TH2D HFHigh_pythia(charm_pythia);
 HFHigh_pythia.SetName("HFHigh_pythia");
 HFHigh_pythia.Scale(1.+ccbarErrHigh);
 HFHigh_pythia.Add(&beauty_pythia,1.+bbbarErrHigh);
 //TH2D HFHigh_powheg(charm_powheg);
 //HFHigh_powheg.SetName("HFHigh_powheg");
 //HFHigh_powheg.Scale(1.+ccbarErrHigh);
 //HFHigh_powheg.Add(&beauty_powheg,1.+bbbarErrHigh);

//
 fOut = new TFile("./output/vpInputNew.root","RECREATE");
 fOut->cd();
 signal.Write();
 signalLow.Write();
 signalHigh.Write();
 resonances.Write();
 resonances_low.Write();
 resonances_high.Write();
 jpsi.Write();
 jpsi_low.Write();
 jpsi_high.Write();

 HF_pythia.Write();
 HFLow_pythia.Write();
 HFHigh_pythia.Write();
 //HF_powheg.Write();
 //HFLow_powheg.Write();
 //HFHigh_powheg.Write();

 HFscaled_pythia.Write();
 HFscaledLow_pythia.Write();
 HFscaledHigh_pythia.Write();
 //HFscaled_powheg.Write();
 //HFscaledLow_powheg.Write();
 //HFscaledHigh_powheg.Write();
 hTest_pythia->Write();
 //hTest_powheg->Write();
 gr1_pythia->Write();
 gr2_pythia->Write();
 grPoint_pythia->Write();
 //gr1_powheg->Write();
 //gr2_powheg->Write();
 //grPoint_powheg->Write();
 fOut->Close();
 delete fOut;




}

Double_t HFfunction(Double_t *x, Double_t *par)
{
  Int_t xbin = hc->GetXaxis()->FindBin(x[0]);
  Int_t ybin = hc->GetYaxis()->FindBin(x[1]);

  Double_t val = par[0]*hc->GetBinContent(xbin,ybin) + par[1]*hb->GetBinContent(xbin,ybin) + hRes->GetBinContent(xbin,ybin);
  return val;
}

void SutractHisto(TH2D &h1, TH2D &h2)
{

  for(Int_t ix = 1; ix <= h1.GetNbinsX(); ++ix){
    for(Int_t iy = 1; iy <= h1.GetNbinsY(); ++iy){
      h1.SetBinContent(ix,iy,h1.GetBinContent(ix,iy)-h2.GetBinContent(ix,iy));
    }
  }

}

void Rebin2D(TH2D &h,TH2D &hRefBinning)
{

  // Different binnings
  //Double_t mee_bin[] = { 0.00,0.04,0.09,0.14,0.19,0.24,0.29,0.34,0.39,0.44,0.50,0.60,0.70,0.75,0.80,0.95,1.00,1.05,1.10,1.40,1.70,2.00,2.40,2.70,3.00,3.10,3.30,3.50,4.00};
  //Double_t mee_bin[] = { 0.00,0.04,0.09,0.14,0.19,0.24,0.29,0.34,0.39,0.44,0.50,0.60,0.70,0.75,0.80,0.95,1.00,1.05,1.10,1.40,1.70,2.00,2.40,2.70,3.00,3.10,3.30,3.50,4.00};
  //Double_t ptee_bin[] = {0.00,0.40,0.80,1.20,1.60,2.00,2.40,2.80,4.00,5.50,8.00,10.0};
  //Int_t n_mee_bin = sizeof(mee_bin)/sizeof(*mee_bin) -1;
  //Int_t n_ptee_bin = sizeof(ptee_bin)/sizeof(*ptee_bin) -1;

   // Binning from the data
   Int_t n_mee_bin = hRefBinning.GetNbinsX();
   Double_t mee_bin[n_mee_bin+1];
   for(Int_t i = 0; i <= n_mee_bin; ++i)
   mee_bin[i] = hRefBinning.GetXaxis()->GetBinUpEdge(i);
   Int_t n_ptee_bin = hRefBinning.GetNbinsY();
   Double_t ptee_bin[n_ptee_bin+1];
   for(Int_t i = 0; i <= n_ptee_bin; ++i)
   ptee_bin[i] = hRefBinning.GetYaxis()->GetBinUpEdge(i);

   TH2D hrb(Form("%s_rb",h.GetName()),"",n_mee_bin,mee_bin,n_ptee_bin,ptee_bin);
   hrb.Sumw2();
   for(Int_t ix = 1; ix <= h.GetNbinsX(); ix++){
     for(Int_t iy = 1; iy <= h.GetNbinsY(); iy++){
       Double_t w(0.);
       w = h.GetBinContent(ix,iy);
       hrb.Fill(h.GetXaxis()->GetBinCenter(ix),
		h.GetYaxis()->GetBinCenter(iy),w);
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

void SetHistoProp(TH1D *h, Int_t color,Int_t mStyle,Int_t lStyle)
{
  h->SetMarkerStyle(mStyle);
  h->SetLineStyle(lStyle);
  h->SetLineColor(color);
  h->SetMarkerColor(color);

}
void Add5proc(TH2D &hup, TH2D &h){


  Int_t n_mee_bin = h.GetNbinsX();
  Int_t n_ptee_bin = h.GetNbinsY();

  Double_t proc = 0.05; // Add 5 % sys
 
  for(Int_t ix = 1; ix <= h.GetNbinsX(); ix++){
    for(Int_t iy = 1; iy <= h.GetNbinsY(); iy++){

      Double_t signal = h.GetBinContent(ix,iy);
      Double_t signalup = hup.GetBinContent(ix,iy);

      Double_t sysup = TMath::Abs(signal-signalup);
      Double_t sysupnew = TMath::Sqrt(sysup*sysup+proc*proc*signal*signal);

      Double_t signalnew = 0.;
      if(signalup>signal) signalnew = signal+sysupnew;
      else signalnew = signal-sysupnew;

      //printf("Old and New %f and %f\n",signalup,signalnew);

      hup.SetBinContent(ix,iy,signalnew);
      
    }
  }
  return;
  
}
TH2D *RebinBis(TH2D &h) {
  
  //Double_t mee_bin[] = { 0.00,0.04,0.09,0.14,0.19,0.24,0.29,0.34,0.39,0.44,0.50,0.60,0.70,0.75,0.80,0.95,1.00,1.05,1.10,1.40,1.70,2.00,2.40,2.70,3.00,3.10,3.30,3.50,4.00};
  //Double_t ptee_bin[] = {0.00,0.40,0.80,1.20,1.60,2.00,2.40,2.80,4.00,5.50,8.00,10.0};

  Double_t mee_bin[] = { 0.00,0.04,0.09,0.14,0.19,0.24,0.29,0.34,0.39,0.44,0.50,0.60,0.70,0.75,0.80,0.90,0.95,1.00,1.04,1.10,1.40,1.70,2.00,2.40,2.80,3.00,3.10,3.30,3.50,4.00};
  Double_t ptee_bin[] = {0.00,0.40,0.80,1.20,2.00,3.00,4.00,6.00,8.00};

  //Double_t mee_bin[] = {0.00,/*0.01,*/0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.20,0.24,0.30,0.40,0.50,0.60,0.70,0.75,0.80,0.85,0.90,0.95,1.00,1.04,1.10,1.20,1.40,1.60,1.80,2.00,2.20,2.40,2.60,2.80,3.00,3.06,3.10,3.30,3.50,4.00};
  //Double_t ptee_bin[] = {0.00,0.20,0.4,0.6,0.8,1.0,1.5,2.0,2.5,3.0,3.5,4.5,6.0,8.0,10.};


  //Double_t mee_bin[] = { 0.00,0.04,0.09,0.14,0.19,0.24,0.29,0.34,0.39,0.44,0.50,0.60,0.70,0.75,0.80,0.95,1.00,1.05,1.10,1.70,2.40,2.70,3.00,3.10,3.30,3.50,4.00};
  //Double_t ptee_bin[] = {0.00,0.40,0.80,1.20,1.60,2.00,2.40,2.80,4.00,5.50,8.00,10.0};
  Int_t n_mee_bin = sizeof(mee_bin)/sizeof(*mee_bin) -1;
  Int_t n_ptee_bin = sizeof(ptee_bin)/sizeof(*ptee_bin) -1;

  
  TH2D* hOut = new TH2D(Form("hOut_%s",h.GetName()), h.GetTitle(), n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
  hOut->Sumw2(); // also done by SetBinError();
  //LmHelper::Debug(Form("   hOut created..."), 12);
  hOut->GetXaxis()->SetTitle(h.GetXaxis()->GetTitle());
  hOut->GetYaxis()->SetTitle(h.GetYaxis()->GetTitle());
  hOut->GetZaxis()->SetTitle(h.GetZaxis()->GetTitle());
  Double_t bin_content_hIn    =  0;
  Double_t bin_error_hIn      =  0;
  Double_t bin_center_mee     = -1;
  Double_t bin_center_ptee    = -1;
  Int_t    hOut_previous_bin  = -1;
  Int_t    hOut_current_bin   = -1;
  Double_t hOut_bin_err2      =  0;
  //LmHelper::Debug(Form("   fill new bins..."), 12);
  for (Int_t i_mee = 1; i_mee <= h.GetNbinsX(); ++i_mee){ //Overflow? -> would probably mess up error calculation.
    for (Int_t j_ptee = 1; j_ptee <= h.GetNbinsY(); ++j_ptee){
      bin_content_hIn = h.GetBinContent(i_mee, j_ptee);
      bin_error_hIn   = h.GetBinError(i_mee, j_ptee);
      bin_center_mee  = h.GetXaxis()->GetBinCenter(i_mee);
      //printf(Form(" Bin center mee of bin %i = %f", i_mee, bin_center_mee));
      bin_center_ptee = h.GetYaxis()->GetBinCenter(j_ptee);

      // set hOut content
      // Fill(): The function returns the corresponding global bin number which has its content incremented by w
      hOut_current_bin = hOut->Fill(bin_center_mee, bin_center_ptee, bin_content_hIn);

      // set hOut error
      if (hOut_current_bin != hOut_previous_bin) { // new bin in hOut
        // set error of previous bin which is now finished.
        if (hOut_previous_bin>-1) hOut->SetBinError(hOut_previous_bin, TMath::Sqrt(hOut_bin_err2)); // compute and set absolute bin error.
        // prepare error for current bin
        hOut_bin_err2 = bin_error_hIn*bin_error_hIn; // compute first squared error.
        hOut_previous_bin = hOut_current_bin;
      }
      else {
        // update error of current bin
        hOut_bin_err2 += bin_error_hIn*bin_error_hIn; // update squared error.
      }
    }
  }
  // set error of the very last bin, because it cannot be reached in the loop via (hOut_current_bin != hOut_previous_bin):
  hOut->SetBinError(hOut_previous_bin, TMath::Sqrt(hOut_bin_err2)); // compute and set absolute bin error.

  return hOut;
}
