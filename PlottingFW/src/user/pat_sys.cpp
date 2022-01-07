//Analysis Framework for Dilepton Spectra

// c++ includes
#include <iostream>
#include <vector>
using namespace std;
// ROOT includes
#include "TString.h"
#include "TMath.h"
#include "TF2.h"
#include "TObjArray.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TStyle.h"
#include "TBenchmark.h"
#include "TSystem.h"
#include "TEnv.h"
// project includes
#include "../core/LmFileManager.h"
#include "../core/LmManager.h"
#include "../core/LmBackground.h"
#include "../core/LmBaseSignal.h"
#include "../core/LmSignal.h"
#include "../core/LmHandler.h"
#include "../core/LmHelper.h"
#include "../core/LmCocktailMan.h"
#include "../core/LmCocktail.h"
#include "../core/LmFitter.h"
#include "patrick_common.h"
#include "pat_sys.h"

int  Analysis();

//_______________________________________________________________________________________________
int main(int argc, char* argv[])
{
  InitCommon();
  InitBinning(); // also in patrick_common.
  
  TString sArg="";
  for (int iarg=1; iarg<argc; ++iarg) {
    Printf("argv[%i] = '%s'", iarg, argv[iarg]);
    sArg = argv[iarg];
    // dataset
    if (sArg.Contains("AOD"       ,TString::kIgnoreCase)) {  kDoAOD          = 1; kDo4D=0; continue; }
    if (sArg.Contains("ESD"       ,TString::kIgnoreCase)) {  kDoAOD          = 0; kDo4D=1; continue; }
    //if (sArg.Contains("do4D"    ,TString::kIgnoreCase)) {  kDo4D           = 1; continue; }
    if (sArg.Contains("16_4D"     ,TString::kIgnoreCase)) {  kUse16_4D       = 1; continue; }
    if (sArg.Contains("16_old"    ,TString::kIgnoreCase)) {  kUse16_4D       = 0; continue; }
    if (sArg.Contains("semi"      ,TString::kIgnoreCase)) {  kDoSemi         = 1; continue; }
    if (sArg.Contains("cent"      ,TString::kIgnoreCase)) {  kDoSemi         = 0; continue; }
    // kinematics
    if (sArg.Contains("pt400"     ,TString::kIgnoreCase)) {  kDoPt400        = 1; continue; }
    if (sArg.Contains("pt200"     ,TString::kIgnoreCase)) {  kDoPt400        = 0; continue; }
    if (sArg.Contains("Op50"      ,TString::kIgnoreCase)) {  kDoOpAngle      = 1; continue; }
    if (sArg.Contains("noOp"      ,TString::kIgnoreCase)) {  kDoOpAngle      = 0; continue; }
    // cocktail
    if (sArg.Contains("cockt"     ,TString::kIgnoreCase)) {  kDoCocktail     = 1; continue; }
    if (sArg.Contains("coonly"    ,TString::kIgnoreCase)) {  kDoCocktail     = 2; continue; }
    if (sArg.Contains("LFsum"     ,TString::kIgnoreCase)) {  kUseLFsum       = 1; continue; }
    if (sArg.Contains("HfeRaa"    ,TString::kIgnoreCase)) {  kUseHfeRaa      = 1; continue; }
    if (sArg.Contains("RndmPhiCC" ,TString::kIgnoreCase)) {  kUseHfeRaa      = 2; continue; }
    if (sArg.Contains("SmearCC1s" ,TString::kIgnoreCase)) {  kUseHfeRaa      = 3; continue; }
    if (sArg.Contains("SmearCC2s" ,TString::kIgnoreCase)) {  kUseHfeRaa      = 4; continue; }
    if (sArg.Contains("SampleCCeta",TString::kIgnoreCase)){  kUseHfeRaa      = 5; continue; }
    if (sArg.Contains("CompareRaa",TString::kIgnoreCase)) {  kUseHfeRaa      = 7; continue; }
    if (sArg.Contains("AllCC"     ,TString::kIgnoreCase)) {  kUseHfeRaa      = 9; continue; }
    if (sArg.Contains("Rapp1"     ,TString::kIgnoreCase)) {  kUseRapp        = 1; continue; } // adds Rapp to the normal cocktail, all contributions shown.
    if (sArg.Contains("Rapp2"     ,TString::kIgnoreCase)) {  kUseRapp        = 2; continue; } // creates combined cocktail, h.c. sum and Rapp shown.
    if (sArg.Contains("Rapp3"     ,TString::kIgnoreCase)) {  kUseRapp        = 3; continue; } // similar to 2, but with ratio to h.c. sum.
    // phiv
    if (sArg.Contains("phiVoff"   ,TString::kIgnoreCase)) {  kDoPhiV         = LmManager::kNoCut; continue; }
    if (sArg.Contains("phiVflat"  ,TString::kIgnoreCase)) {  kDoPhiV         = LmManager::kFlatCorrSub; continue; }
    if (sArg.Contains("phiVsub"   ,TString::kIgnoreCase)) {  kDoPhiV         = LmManager::kTemplSub; continue; }
    if (sArg.Contains("phiVconv"  ,TString::kIgnoreCase)) {  kDoPhiV         = LmManager::kTemplConv; continue; }
    // prefilters
    if (sArg.Contains("nopref"    ,TString::kIgnoreCase)) {  kDoPref         = 0; continue; }
    if (sArg.Contains("pref0"     ,TString::kIgnoreCase)) {  kDoPref         = 0; continue; }
    if (sArg.Contains("pref1"     ,TString::kIgnoreCase)) {  kDoPref         = 1; continue; }
    if (sArg.Contains("pref2"     ,TString::kIgnoreCase)) {  kDoPref         = 2; continue; }
    if (sArg.Contains("allpref"   ,TString::kIgnoreCase)) {  kDoPref         = 4; continue; }
    // effi & normalizations
    if (sArg.Contains("effgen"    ,TString::kIgnoreCase)) {  kDoEffGen       = 1; continue; }
    if (sArg.Contains("noEff"     ,TString::kIgnoreCase)) {  kDoEffiCorr     = 0; continue; }
    if (sArg.Contains("noNev"     ,TString::kIgnoreCase)) {  kDoNormNevents  = 0; continue; }
    if (sArg.Contains("noBinW"    ,TString::kIgnoreCase)) {  kDoNormBinwidth = 0; continue; }
    if (sArg.Contains("signifNorm",TString::kIgnoreCase)) {  kDoSignifRaw    = 0; continue; }
    // systematics
    if (sArg.Contains("noSys"     ,TString::kIgnoreCase)) {  kDoSystematics  = 0; continue; }
    if (sArg.Contains("sysAv"     ,TString::kIgnoreCase)) {  kDoSystematics  = 1; continue; }
    if (sArg.Contains("sysWAv"    ,TString::kIgnoreCase)) {  kDoSystematics  = 2; continue; }
    if (sArg.Contains("sysBar"    ,TString::kIgnoreCase)) {  kDoSystematics  = 3; continue; }
    // plotting
    if (sArg.Contains("correl"     ,TString::kIgnoreCase)){  kWideMeeBins    = 1; continue; }
    if (sArg.Contains("wideMeeBins",TString::kIgnoreCase)){  kWideMeeBins    = 1; continue; }
    if (sArg.Contains("ratio"     ,TString::kIgnoreCase)) {  kDoRatio        = 1; continue; }
    if (sArg.Contains("noLeg"     ,TString::kIgnoreCase)) {  kDoLegend       = 0; continue; }
    if (sArg.Contains("noLog"     ,TString::kIgnoreCase)) {  kDoLogY         = 0; continue; }
    if (sArg.Contains("doCL"      ,TString::kIgnoreCase)) {  kDoConfLevel    = 1; continue; }
    if (sArg.Contains("repro"     ,TString::kIgnoreCase)) {  kReprocess      = 1; continue; }
    if (sArg.Contains("write1D"   ,TString::kIgnoreCase)) {  writeFile       = kTRUE; continue; }
    if (sArg.Contains("plotMeeMin",TString::kIgnoreCase)) { plotMeeMin = sArg.Remove(0,sArg.First('=')+1).Atof(); continue; }
    if (sArg.Contains("plotMeeMax",TString::kIgnoreCase)) { plotMeeMax = sArg.Remove(0,sArg.First('=')+1).Atof(); continue; }
    if (sArg.Contains("plotPteeMin",TString::kIgnoreCase)){ plotPteeMin = sArg.Remove(0,sArg.First('=')+1).Atof(); continue; }
    if (sArg.Contains("plotPteeMax",TString::kIgnoreCase)){ plotPteeMax = sArg.Remove(0,sArg.First('=')+1).Atof(); continue; }
    // plot selection via histBits
    if (sArg.Contains("printR"    ,TString::kIgnoreCase)) {  histBitsPrint |= LmSignal::kRfactor; continue; }
    
    LmHelper::Error(Form("main.cpp: main argument '%s' could not be resolved!", sArg.Data()));
  }
  
  Analysis();
  sArg = argv[argc-1]; // last argument
  if (sArg.EqualTo("all",TString::kIgnoreCase)){
    kDoSemi=(kDoSemi==1)?0:1;
    Analysis();
    kDoPt400=(kDoPt400==1)?0:1;
    Analysis();
    kDoSemi=(kDoSemi==1)?0:1;
    Analysis();
  }
  Int_t nErr = LmHelper::ErrorSummary();
  return nErr;
}

//_______________________________________________________________________________________________
int Analysis()
{
  // some sanity checks
  if (!kUse16_4D && !kDoOpAngle)      LmHelper::Error("main.cpp: 3D outputs are only available with opening angle cut! (remove '16_old' or set 'Op50')");
  if (!kUse16_4D && !kDoSystematics)  LmHelper::Error("main.cpp: remove at least one of '16_old' or 'noSys' to read in a spectrum!");
  if (!kDoAOD)                        LmHelper::Error("main.cpp: dont use ESD outputs, because TPC dEdx correction is bad!");
  
  // automatic settings
  if (kDoAOD==1)      sOptAOD     = "AOD";        else sOptAOD    = "ESD";
  if (kDoSemi==1)     sOptCent    = "semi";       else sOptCent   = "cent";
  if (kDoPt400==1)    sOptPt      = "pt400";      else sOptPt     = "pt200";
  if (kDoOpAngle==1)  sOptOpAngle = "opAngle50";  else sOptOpAngle= ""; // has to be empty due to names of efficiency histograms.
  switch (kDoPhiV) {
    case LmManager::kNoCut:     sOptPhiV="phiVoff";   break;
    case LmManager::kTemplConv: sOptPhiV="phiVconv";  break;
    case LmManager::kFlatCorrSub: sOptPhiV=Form("phiVflatn%d",n_cutEdgesMee);  break;
    case LmManager::kTemplSub:  sOptPhiV=Form("phiVsubn%d" ,n_cutEdgesMee);  break;
    default: sOptPhiV=Form("phiVtype%dn%d",kDoPhiV,n_cutEdgesMee); break;
  }
  SetPref(kDoPref);
  if (kDoEffGen==1)   sOptEff     = "EffiGen";    else sOptEff    = "EffiMeas";
  if (!kDoEffiCorr) { sOptEff     = "NoEffi";
    if (!kDoNormNevents ) sOptEff.Append("-NoNevents");
    if (!kDoNormBinwidth) sOptEff.Append("-NoBinwidth");
    kDoSystematics=0; // everything else would make no sense!
  } else { // with effi corr
    kDoNormNevents=kTRUE;   kDoNormBinwidth=kTRUE; // everything else would make no sense!
  }
  
  
  iSet           = kDoAOD*2+kDo4D*1;
  Ncuts          = GetNcuts();
  iSelectedCut   = FindIndexOfCut(sSelectedCut);
  iSelCutMaxStat = FindIndexOfCut(sSelCutMaxStat); // may have checked the wrong signal in the past, index 18 instead of 18-1...
  
  
  // Construct path for plots.
  TString sPrintPath = "./plots/";
  if ( kDoSystematics==0) sPrintPath.Append("NoSys-");
  if ( kDoSystematics==1) sPrintPath.Append("WithSysAv-");
  if ( kDoSystematics==2) sPrintPath.Append("WithSysWAv-");
  if ( kDoSystematics==3) sPrintPath.Append("WithSysBarlow-");
  if (!kDoEffiCorr      ) sPrintPath.Append(sOptEff+"-");
  //sPrintPath.Remove(TString::kTrailing, '-');
  sPrintPath.Replace(sPrintPath.Length()-1,1,"/"); // replace the last "-" with "/".
  sPrintPath.Append(sOptCent+"-"+sOptPt+"/");
  if ( kUse16_4D==0     ) sPrintPath.Append("cut16_old-");
  if ( kUse16_4D==1     ) sPrintPath.Append("cut16_4D-");
  sPrintPath.Append(sOptOpAngle+"-"+sOptPhiV+"-"+sOptPref+"/");
  if ( kDoCocktail!=2   ) sPrintPath.Append("Data-");
  if ( kDoCocktail      ) sPrintPath.Append("Cocktail-");
  if ( kUseLFsum  && kDoCocktail ) sPrintPath.Append("LFsum-");
  if ( kUseHfeRaa && kDoCocktail ) sPrintPath.Append(GetHfeOpt()+"-");
  if ( kUseRapp   && kDoCocktail ) sPrintPath.Append(GetRappOpt()+"-");
  if ( kWideMeeBins>0   ) sPrintPath.Append("WideMeeBins-");
  if ( kDoRatio         ) sPrintPath.Append("WithRatio-");
  if (!kDoLegend        ) sPrintPath.Append("NoLegend-");
  sPrintPath.Remove(TString::kTrailing, '-');
  
  // Create the output directory and configure it in gEnv.
  // (unfortunately that path will not be used automatically, see workaround in LmHandler::PrintCompare().)
  gSystem->Exec( Form("mkdir -p %s", sPrintPath.Data()) );
  gEnv->SetValue("Canvas.PrintDirectory",sPrintPath.Data());
  
  
  cout << " ______ CONFIGURATION ______ " << endl;
  cout << " data type    =   " << sOptAOD.Data() << endl;
  cout << " centrality   =   " << sOptCent.Data() << endl;
  cout << " pt-cut       =   " << sOptPt.Data() << endl;
  cout << " opening angle=   " << sOptOpAngle.Data() << endl;
  cout << " prefilter    =   " << sOptPref.Data() << endl;
  cout << " efficiency   =   " << sOptEff.Data() << endl;
  cout << " phiV option  =   " << sOptPhiV.Data() << endl;
  cout << endl;
  //cout << " plotCombineH =   " << (plotCombineH?"YES":"NO") << endl;
  //cout << " plotAverage  =   " << (plotAverage?"YES":"NO") << endl;
  //cout << " plotWeightAv =   " << (plotWeightAv?"YES":"NO") << endl;
  cout << " writeFile    =   " << (writeFile?"YES":"NO") << endl;
  cout << " Ncuts        =   " << Ncuts << endl;
  cout << " SelectedCut  =   " << sSelectedCut.Data() << " (index = " <<iSelectedCut<< ")" << endl;
  cout << endl;
  cout << " plots path   =   " << gEnv->GetValue("Canvas.PrintDirectory",".") << endl;
  cout << endl;
  
  //return 1;
  
  if (kDoPhiV==LmManager::kTemplSub || projoption.EqualTo("yx", TString::kIgnoreCase)) { // x=mee, y=ptee (default)
    LmHelper::Info(Form("main.cpp: resetting phiV cut values to pi in order to use all datapoints in phiV for statistical uncertainty of each mee bin.\n"));
    // turn off the cut window for phiV
    for (int iphiV=0; iphiV<n_cutPhiVabove; ++iphiV) {
      cutPhiVabove[iphiV] = TMath::Pi();
    }
  }
  
  
  std::vector<LmSignal*>  sigVec_final;
  std::vector<TString>    sigNames_final;
  TString   finalSigName  = "";
  
  
  //
  // Decide which signals shall be created and plotted.
  //
  if (kDoPref==4) {
    SetPref(0);
    sigVec_final.push_back( CreateFinalSignal("no prefilter") );
    SetPref(1); // prefilter with mee & theta
    if (kDoOpAngle==0) sOptOpAngle = "opAngle50"; // needed to get the right effi histogram, because the combination PrefTheta + noOpAngCut no longer exists.
    sigVec_final.push_back( CreateFinalSignal("pref. cut #it{m}_{ee} & #it{#theta}_{ee}") );
    if (kDoOpAngle==0) sOptOpAngle = ""; // reset the change above.
    SetPref(2); // prefilter with mee and phiV
    sigVec_final.push_back( CreateFinalSignal("pref. cut #it{m}_{ee} & #it{#phi}_{V}") );
    SetPref(4);
  }
  else {
    sigVec_final.push_back( CreateFinalSignal("data") );
  }
  
  
  LmSignal* sig16_Used = sigVec_final.at(0);
  if (!sig16_Used) LmHelper::Error("main.cpp: signal is missing!");
  
  // compare results
  LmHandler* han_compare = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  han_compare->SetName("han_compare");
  for (int isig=0; isig<(int)sigVec_final.size(); ++isig) {
    han_compare->AttachSignal(*sigVec_final.at(isig));
  }
  
  //han_compare->AttachSignal(*sig16_Used, "-");
//    han_compare->AttachSignal(*sig16_Used, "data");
//  han_compare->AttachSignal(*sig16_Used, (kDoPref>0?"Patrick, pref":"Patrick")); // "data"
//  han_compare->AttachSignal(*sigAv_SysAverage,       "average signal + sys av.");
//  han_compare->AttachSignal(*sigWAv_SysWeightedAv,   "weigh.av. signal + sys w.av.");
//  han_compare->AttachSignal(*sig16_4D_SysAverage,    "cut 16, sys av.");
//  han_compare->AttachSignal(*sig16_4D_SysWeightedAv, "cut 16, sys w.av.");
  // cut 16 comparisons:
  //  han_compare->AttachSignal(*sig16_SysAverage, "sys av");
  //  han_compare->AttachSignal(*sig16_SysWeightedAv, "sys weighted av");
  //  han_compare->AttachSignal(*sig16_SysWeightedAv, "pt<200");
  //  han_compare->AttachSignal(*sig16_SysWeightedAv2 , "pt<400");
  //  han_compare->AttachSignal(*sig16_SysWeightedAv, "without prefilter" );
  //  han_compare->AttachSignal(*sig16_SysWeightedAv2 , "prefilter m<40 #theta<80");
  //  han_compare->AttachSignal(*sig16_Barlow1        );
  //  han_compare->AttachSignal(*sig16_Barlow2        );
  //  han_compare->AttachSignal(*sig16_Barlow3        );
  han_compare->Process(LmHandler::kCompare);
  
  
  // attach external datapoints:
  Bool_t compAlberto=kFALSE;
  TFile* _fExt = LmHelper::SafelyOpenRootfile("./input/datapoints/DielectronResultsPbPb_Alberto/InputFile_EfficiencyCorrectedSignal_Central.root");
  TH1D *hExt[5];
  hExt[0] = new TH1D( *static_cast<TH1D*> (_fExt->Get("fHistoInvMass_Signal_Pref_Central(1)")) );
  hExt[1] = new TH1D( *static_cast<TH1D*> (_fExt->Get("fHistoInvMass_Signal_Pref_Central(2)")) );
  hExt[2] = new TH1D( *static_cast<TH1D*> (_fExt->Get("fHistoInvMass_Signal_Pref_Central(3)")) );
  hExt[3] = 0x0;
  hExt[4] = new TH1D( *static_cast<TH1D*> (_fExt->Get("fHistoInvMass_Signal_Pref_Central(0)")) ); // 0 is integrated
  for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj){
    if (hExt[iProj]) {
      hExt[iProj]->SetName("Alberto, pref");
      hExt[iProj]->SetMarkerColor(kBlack);
      hExt[iProj]->SetLineColor(kBlack);
      hExt[iProj]->SetMarkerStyle(21);
      hExt[iProj]->SetMarkerSize(1);
      hExt[iProj]->SetFillStyle(0);
    }
    if (!compAlberto) break;
    sig16_Used->GetSubSig(iProj,LmBaseSignal::kProjOnMee)->SetExternalObject(hExt[iProj]);
    //sig16_Used->GetSubSig(iProj,LmBaseSignal::kProjOnMee)->SetExternalSystematicObject(hExtSystematic[iProj]);
    sig16_Used->GetSubSig(iProj,LmBaseSignal::kProjOnMee)->SetDrawOptions("-;-;-;p E1 same");
  }
  
  LmCocktail* cockt00 = 0x0;
  if (kDoCocktail>0) {
    if (kDoCocktail!=2) LmCocktailPart::SetUseShortLegendNames();
    else                LmCocktailPart::SetUseShortLegendNames(kFALSE); // old default, may want to use for cocktail-only plot.
    if (kUseHfeRaa==9) {
      han_compare->AttachCocktail( CreateCocktailHeavyFlavour(0) ); // default charm.
      han_compare->AttachCocktail( CreateCocktailHeavyFlavour(2) ); // need to attach the charm cocktails before cockt00, which will be subtracted.
      han_compare->AttachCocktail( CreateCocktailHeavyFlavour(5) );
      han_compare->AttachCocktail( CreateCocktailHeavyFlavour(3) );
    }
    else if (kUseHfeRaa==7) {
      han_compare->AttachCocktail( CreateCocktailHeavyFlavour(0) ); // default HF.
      han_compare->AttachCocktail( CreateCocktailHeavyFlavour(1) ); // RAA HF.
    }
    cockt00 = ProcessCocktail();
    han_compare->SetDivideOption("0");
    if (kUseHfeRaa!=7) han_compare->AttachCocktail(cockt00); // attach complete cocktail to handler. call cockt00->Process() before!
    han_compare->SetDrawStyleCocktail("hist c"); // default is "hist"
    if (kUseRapp==3) han_compare->AttachCocktail( cocktSum ); // if more than 1 cocktail is set/attached, only the last is drawn to the legend.
    if (kUseHfeRaa==9) han_compare->Process(LmHandler::kSubtractCocktail); // last cocktail is subtracted from data. projections are done first if needed.
    else han_compare->Process(LmHandler::kCocktail); // create projections of cocktail spectra in the projection binning of the handler. they are stored in each LmCocktailPart.
    if (kDoCocktail==2) han_compare->SetType(LmHandler::kCocktailOnly);
  }
  else {
    han_compare->SetDivideOption("b"); // "b" ist not completely right to compare subtracted signals, because they are not perfect subsets.
  }
  LmHelper::Info(Form("main.cpp: handler '%s' uses divide option '%s'. Be careful with 'b', it is not really ok and not implemented for syst. errors.", han_compare->GetName(), han_compare->GetDivideOption()));
  
  
  if (kWideMeeBins>0) {
    Printf("|__________|   Plot correlations   |__________|");
    CreateCorrelationPlot(han_compare);
    han_compare->ResetPlotRangeY();
  }
  else {
    // Set handler properties
    if (kUseHfeRaa==7)  han_compare->SetPlotRangeRatio(0.01, 1.25);
    else                han_compare->SetPlotRangeRatio(0.01, 2.99);
    han_compare->SetDoRatio(kDoRatio, ratioPadSize);
    TLegend* leg = GetLegendTemplate(kTopLeft1); // some legends have height 0 until filled by handler.
    if (kUseHfeRaa==9) FillLegendCharm(leg, han_compare); // custom legend for charm comparison.
    han_compare->SetLegend(leg);
    han_compare->SetLabels(GetLabelsTemplate(kDefault));
    Printf("|__________|   Plot Mee   |__________|");
    //if (kDoLogY) han_compare->SetPlotRangeY(1.001e-3, 10000);
    if (kDoLogY && kDoCocktail>0)  han_compare->SetPlotRangeY(1.001e-5, 40);
    //if (kDoCocktail==2)             han_compare->SetPlotRangeY(1.001e-4, 40); // cocktail only, for Carsten
    //else           han_compare->SetPlotRangeY(0.  , 0.1);
    //han_compare->SetPlotRangeY(1e-6, 1e5);
    for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj){
      if (kUseRapp) iProj=binsPtee_forMee.size()-1; // print only integrated projection, because all others are wrong with 1D Rapp input...
      han_compare   ->PrintCompareSig_Mee(    iProj, kDoLegend, Form("+%s",GetAllOptions().Data()));
      if (!kDoSystematics && !kDoCocktail) {
        if (!kDoEffiCorr) han_compare   ->PrintCompareSoverB_Mee( iProj, kDoLegend, Form("+%s",GetAllOptions().Data()));
        han_compare   ->PrintCompareSignif_Mee( iProj, kDoLegend, Form("+%s",GetAllOptions().Data()));
        han_compare   ->PrintCompareSigBkg_Mee( iProj, kDoLegend, Form("+%s",GetAllOptions().Data())); // crashes with Rapp external cocktail.
        //han_compare ->PrintCompare(LmSignal::kUnlike+LmSignal::kBkg, iProj, LmBaseSignal::kProjOnMee, Form("+%s",GetAllOptions().Data()), kDoLegend, kDoLogY);
      }
      // to check systematics using LmSignal::debugSyst=kTRUE;
      //han_compare   ->PrintCompare(LmSignal::kSubSig+LmSignal::kSoverB+LmSignal::kSignif, iProj, LmBaseSignal::kProjOnMee, Form("+%s",GetAllOptions().Data()), kDoLegend, kDoLogY);
    }
    han_compare->ResetPlotRangeY();
    
    Printf("|__________|   Plot Ptee   |__________|");
    if (kDoLogY && kDoCocktail==1)  han_compare->SetPlotRangeY(6.8e-5, 2.8e-1); // to match the old random-charm plots.
    for(UInt_t iProj = 0; iProj < binsMee_forPtee.size(); ++iProj){
      if (kUseRapp) iProj=binsMee_forPtee.size()-1; // print only integrated projection -> as reminder that Rapp is flat in ptee.
      //han_compare   ->PrintCompare(LmSignal::kSubSig,iProj, LmBaseSignal::kProjOnPtee, Form("+%s",GetAllOptions().Data()), kDoLegend, kDoLogY);
      han_compare   ->PrintCompareSig_Ptee(   iProj, kDoLegend, Form("+%s",GetAllOptions().Data()));
      if (!kDoSystematics && !kDoCocktail) {
        if (!kDoEffiCorr) han_compare   ->PrintCompareSoverB_Ptee(iProj, kDoLegend, Form("+%s",GetAllOptions().Data()));
        han_compare   ->PrintCompareSignif_Ptee(iProj, kDoLegend, Form("+%s",GetAllOptions().Data()));
        //han_compare   ->PrintCompareSigBkg_Ptee(iProj, kDoLegend, Form("+%s",GetAllOptions().Data()));
      }
    }
    han_compare->ResetPlotRangeY();
  }
  
  
  if (writeFile) {
    // write most important histograms to rootfiles:
    // add bits of histograms you want to save: LmSignal::kSubSig+LmSignal::kSoverB+LmSignal::kSignif (to save all, use LmSignal::kMAXhist-1)
    TString filename1D = Form("spectra1D%s.root",GetAllOptions(kTRUE).Data());
    TFile* _fileOut1D  = new TFile(filename1D.Data(), "RECREATE");
    han_compare->Write1DHistSingle(LmSignal::kSubSig+LmSignal::kSoverB+LmSignal::kSignif, LmSignal::kProjOnMee);
    han_compare->Write1DHistSingle(LmSignal::kSubSig+LmSignal::kSoverB+LmSignal::kSignif, LmSignal::kProjOnPtee);
    _fileOut1D->Close();

    if (kDoCocktail) {
      TString filename1Dco = Form("spectra1D_cocktail_%s_%s_%s_%s.root",sOptCent.Data(),sOptPt.Data(),sOptOpAngle.Data(),GetHfeOpt().Data());
      TFile* _fileOut1Dco  = new TFile(filename1Dco.Data(), "RECREATE");
      han_compare->Write1DHistCocktail(LmCocktailPart::kMAXpart-1, LmSignal::kProjOnMee);
      han_compare->Write1DHistCocktail(LmCocktailPart::kMAXpart-1, LmSignal::kProjOnPtee);
      _fileOut1Dco->Close();
    }
  }
  
  
  
//  Int_t best3[3]; best3[0]=-1;
////  han_weighted_average->GetIndexBestSignals(best3);
////  cout << "best3 = " << best3[0] << " " << best3[1] << " " << best3[2] << endl;
//  // compare results
//  LmHandler* han_compare = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin, plotMeeMax,plotPteeMin, plotPteeMax);
//  han_compare->SetName("han_compare");
//  if (best3[0]>-1)            han_compare->AttachSignal(*(han_weighted_average->GetLmSignalI(best3[0])));
//  if (best3[0]>-1)            han_compare->AttachSignal(*(han_weighted_average->GetLmSignalI(best3[1])));
//  if (best3[0]>-1)            han_compare->AttachSignal(*(han_weighted_average->GetLmSignalI(best3[2])));
//  if (iSelectedCut>0)          han_compare->AttachSignal(*(han_weighted_average->GetLmSignalI(iSelectedCut)));
//  han_compare->Process(LmHandler::kCompare);
  
  
  std::cout << "main.cpp done :-)" << std::endl;
  return 0;
}


//_______________________________________________________________________________________________
LmSignal* CreateFinalSignal(TString newName, Int_t getAverageSig)
{
  Printf("______ create final signal ______");
  
  // return signal
  LmSignal*   sig_return      = 0x0;
  // 20 cut settings, 3D
  LmHandler*  han_systematic  = 0x0;
  LmHandler*  han_analysis    = 0x0;
  TH2D*       hRelSys         = 0x0;
  // 4D
  LmHandler*  han16_4D        = 0x0;
  TH2D*       hRelSysPhivLow  = 0x0;
  TH2D*       hRelSysPhivHigh = 0x0;
  
  if (kUse16_4D) {
    //
    // Read in 4D output for cut16 (kUse16_4D).
    //
    han16_4D = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
    ProcessCut16_4D_AOD(han16_4D);
    sig_return = new LmSignal(*(han16_4D->GetLmSigCombined()), "sig16_4D");
  }
  else {
    //
    // Read in 3D outputs from 20 cut settings to get average signal or old cut16 signal.
    //
    han_systematic = new LmHandler(binsPtee_forMee_sys,binsMee_forPtee_sys,plotMeeMin,plotMeeMax_sys,plotPteeMin,plotPteeMax_sys);
    han_systematic->SetName("han_systematic");
    han_analysis = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
    han_analysis->SetName("han_analysis");
    ProcessSystematics(han_systematic, han_analysis); // process or read all signals into the handlers.
    if (getAverageSig==1) {
      han_analysis->Process(LmHandler::kAverage);
      sig_return = new LmSignal(*(han_analysis->GetLmSigAverage()), "sigAv");
    }
    else if (getAverageSig==2) {
      han_analysis->Process(LmHandler::kWeightedAverage);
      sig_return = new LmSignal(*(han_analysis->GetLmSigAverage()), "sigWAv");
    }
    else { // get cut16 signal with opening angle cut (16_old)
      sig_return = new LmSignal(*(han_analysis->GetLmSignalI(iSelectedCut)), "sig16_old");
    }
  }
  cout << " * Created selected signal with temporary name " << sig_return->GetName() << endl;
  
  if (kDoSystematics) {
    //
    // Compute systematics from 20 cut settings.
    // Apply systematics to individual signals.
    //
    if (!han_systematic || !han_analysis) {
      han_systematic = new LmHandler(binsPtee_forMee_sys,binsMee_forPtee_sys,plotMeeMin,plotMeeMax_sys,plotPteeMin,plotPteeMax_sys);
      han_systematic->SetName("han_systematic");
      han_analysis = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
      han_analysis->SetName("han_analysis");
      ProcessSystematics(han_systematic, han_analysis);
    }
    
    Int_t hanType = 0;
    if (kDoSystematics==1) hanType = LmHandler::kSystematic_Average;
    if (kDoSystematics==2) hanType = LmHandler::kSystematic_WeightedAverage;
    if (kDoSystematics==3) {
      hanType = LmHandler::kSystematic_BarlowSubset;
      han_systematic->SetAllowedDiscrepancy(1.); // sys barlow 1 sigma
    }
    
    // Optional: find and highlight the 3 signal closest to the average during Process(k[Syst]Average).
    //  han_systematic->SetCompareSignalsToAverage();
    //  han_analysis->SetCompareSignalsToAverage();
    
    // Optional: compute systematics on Unlike Sign (to be used for Barlow, but needs efficiency for ULS).
    //  han_systematic->SetDoSystOnUnlikeSign(kTRUE);
    //  han_analysis  ->SetDoSystOnUnlikeSign(kTRUE);
    
    cout << " * Calculate relative systematics" << endl;
    // get systematics
    han_systematic->Process(hanType);
    hRelSys = (TH2D*) han_systematic->GetRelSystematics()->Clone("hRelSys");
    
    cout << " * Calculate PhiV systematics" << endl;
    hRelSysPhivLow  = CreateRelSysPhiV(1.5);
    hRelSysPhivHigh = CreateRelSysPhiV(0.5);
    
    // apply the systematics to the selected signal ('iSelectedCut' or average signal or sig16_4D):
    cout << " * Apply systematics to selected signal" << endl;
    sig_return->SetSymmetricRelSystematics(hRelSys);
    sig_return->SetRelSystematicsLow(hRelSysPhivLow);
    sig_return->SetRelSystematicsHigh(hRelSysPhivHigh);
    sig_return->Process(LmSignal::kSystematic);
    
    // plot results
    // syst only integrated:
    Int_t lastProj = han_systematic->GetMaxBinProj(LmSignal::kProjOnMee);
    han_systematic->PrintCompareSig_Mee(lastProj, kFALSE, Form("+%s",GetAllOptions().Data()));
    
    for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj){
      //han_systematic->PrintCompareSig_Mee(iProj, kDoLegend, Form("+_sys%s",GetAllOptions().Data()), 2, 20);
      //han_analysis  ->PrintCompareSig_Mee(iProj, kDoLegend, Form("+_ana%s",GetAllOptions().Data()), 2, 20);
    }
  }
  
  if (!newName.IsNull()) sig_return->SetName(newName.Data());
  return sig_return;
}

//_______________________________________________________________________________________________
void CreateCorrelationPlot(LmHandler* han_compare)
{
  Printf("______ create correlation plot ______");
  
  // Set projection axis and bin of other axis
  Int_t projOnAxis=LmBaseSignal::kProjOnX;
  int i = han_compare->GetMaxBinProj(projOnAxis);
  // Set handler properties for support plots
  ratioPadSize = 0.5;
  han_compare->SetPlotRangeRatio(0.8, 1.99);
  han_compare->SetDoRatio(kTRUE, ratioPadSize);
  han_compare->SetLegend(GetLegendTemplate(kTopRight1, 0.9/(1.-ratioPadSize)));
  han_compare->SetLabels(GetLabelsTemplate(kBottomPanelBottomLeft, 0.9/(1.-ratioPadSize)));
  han_compare->SetPlotRangeY(1e-4, 1e4);
  han_compare->PrintCompare(LmSignal::kSignif, i, projOnAxis, Form("+%s_forCorrel",GetAllOptions().Data()));
  han_compare->PrintCompare(LmSignal::kSoverB, i, projOnAxis, Form("+%s_forCorrel",GetAllOptions().Data()));
  han_compare->PrintCompare(LmSignal::kSubSig, i, projOnAxis, Form("+%s_forCorrel",GetAllOptions().Data())); // printing the same projections of SubSig is needed for correct legend colors in correlation plot.
  
  // Set up canvas for correlation plot
  TCanvas cCorrel("cCorrel", "cCorrel");
  LmHelper::CreatePads(&cCorrel,1,2, 2*gStyle->GetPadBottomMargin(), 2*gStyle->GetPadTopMargin());
  TPad* pad1 = (TPad*) cCorrel.GetPad(1);
  TPad* pad2 = (TPad*) cCorrel.GetPad(2);
  pad1->SetLogx(); pad1->SetLogy();
  pad2->SetLogx(); pad2->SetLogy();
  
  std::vector<TH1D*> vProj1 = han_compare->CollectProjections(LmSignal::kSoverB, i, LmBaseSignal::kProjOnMee);
  std::vector<TH1D*> vProj2 = han_compare->CollectProjections(LmSignal::kSignif, i, LmBaseSignal::kProjOnMee);
  TObjArray* oaCorrelGr = 0x0;
  TObjArray* oaLabels = 0x0;
  Double_t titleSize = vProj1.at(0)->GetYaxis()->GetTitleSize();
  Double_t labelSize = vProj1.at(0)->GetYaxis()->GetLabelSize();
  
  // Retrieve legend
  han_compare->PrintCompare(LmSignal::kSubSig, 0, projOnAxis, Form("+%s_forLegend",GetAllOptions().Data())); // printing the same projections of SubSig is needed for correct legend colors in correlation plot.
  TLegend* leg = han_compare->GetLegend();
  
  pad1->cd();
  unsigned int proj_bin_2 = 1; // ptee-projection bin 1 is resonance region.
  TH2D* haxis = new TH2D("haxis","haxis", 1000,4e-4,4e-2, 1000,0.8,1.2e1);
  haxis->SetTitle( Form(";%s;%s",vProj1.at(0)->GetYaxis()->GetTitle(),vProj2.at(0)->GetYaxis()->GetTitle()) );
  haxis->SetTitleOffset(1.,"Y");
  haxis->SetTitleSize(titleSize,"XY");
  haxis->SetLabelSize(labelSize,"XY");
  haxis->DrawCopy();
  oaCorrelGr = LmHelper::MakeCorrelationGraphs(vProj1, vProj2, proj_bin_2+1, proj_bin_2+1, kTRUE); // this function takes histogram bins, so +1.
  oaCorrelGr->DrawClone("p same");
  delete oaCorrelGr;
  
  cCorrel.cd(); // Draw labels & legend into the canvas instead of its pads, to use global coordinates.
  leg->SetTextSize(gStyle->GetTitleSize()*0.9);
  leg->SetY1(0.72);
  leg->DrawClone("same");
  oaLabels = han_compare->FillLabels(GetLabelsTemplate(kTopPanelBottomLeft), i, projOnAxis, proj_bin_2);
  oaLabels->DrawClone("same");
  
  pad2->cd();
  proj_bin_2 = 2;
  TH2D* haxis2 = new TH2D("haxis2","haxis2", 1000,4e-4,4e-2, 1000,0.8,1.2e1);
  haxis2->SetTitle( Form(";%s;%s",vProj1.at(0)->GetYaxis()->GetTitle(),vProj2.at(0)->GetYaxis()->GetTitle()) );
  haxis2->SetTitleOffset(1.,"Y");
  haxis2->SetTitleSize(titleSize,"XY");
  haxis2->SetLabelSize(labelSize,"XY");
  haxis2->DrawCopy();
  oaCorrelGr = LmHelper::MakeCorrelationGraphs(vProj1, vProj2, proj_bin_2+1, proj_bin_2+2, kTRUE); // make correlation for 2 histogram bins.
  oaCorrelGr->DrawClone("p same");
  delete oaCorrelGr;
  
  cCorrel.cd(); // Draw labels & legend into the canvas instead of its pads, to use global coordinates.
  oaLabels = han_compare->FillLabels(GetLabelsTemplate(kBottomPanelBottomLeft), i, projOnAxis, proj_bin_2);
  oaLabels->DrawClone("same");
  oaLabels = han_compare->FillLabels(GetLabelsTemplate(kBottomPanelBottomRight), i, projOnAxis, proj_bin_2+1);
  oaLabels->DrawClone("same");
  
  TLine* lVert = new TLine();
  lVert->SetLineStyle(7);
  lVert->SetLineWidth(2);  
  lVert->DrawLineNDC(0.54, 0.1, 0.54, 0.9);
  
  // construct filename of plot
  TString sfilename = "/cCorrelSoverBSignif_Mee";
  sfilename.Prepend(gEnv->GetValue("Canvas.PrintDirectory",".")); // not the best way maybe...
  sfilename.Append(GetAllOptions());
  sfilename.Append(Form("_bin%d.pdf",i));
  cCorrel.Print(sfilename.Data());
  
  //    // Set handler properties for correlation plots
  //    ratioPadSize = 0.3;
  //    han_compare->SetDoRatio(kFALSE);
  //    han_compare->SetLegend(GetLegendTemplate(kDefNoRatio));
  //    han_compare->SetLabels(GetLabelsTemplate(kBottomPanelBottomLeft, 0.9));
  //    Bool_t separatePlots=kFALSE;
  //    TCanvas cCorrel; cCorrel.SetLogx(); cCorrel.SetLogy();
  //    TH2D* haxis = new TH2D("haxis","haxis", 1000,3e-4,3e-2, 1000,3e-1,3e1);
  //    haxis->Draw(); // DrawCopy() causes a segfault with newer root (seen by Carsten).
  //    han_compare->PrintCompare(LmSignal::kSubSig, i, projOnAxis, Form("+%s_forCorrel",GetAllOptions().Data())); // printing the same projections of SubSig is needed for correct legend colors in correlation plot.
  //    han_compare->PrintCorrelation(LmSignal::kSoverB, LmSignal::kSignif, i, projOnAxis, Form("+%s",GetAllOptions().Data()), kDoLegend, separatePlots, &cCorrel);
}

