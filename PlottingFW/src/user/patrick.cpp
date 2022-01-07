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
#include "TLegend.h"
#include "TLegendEntry.h"
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
#include "../core/LmQA.h"
#include "../core/LmMultiQA.h"
#include "patrick_common.h"
#include "patrick.h"

void      InitOptions();
void      RunSelectedAna(TString sArg);
int       QA();
int       Analysis();
int       ExtractPhiVtemplates();
int       PhiVstudy();
int       Misc();
int       MakePtEtaElectron();
int       DrawResolution();
int       DrawCentrality();

TString   sReq="";
Double_t  diffGaScale=1.;
//_______________________________________________________________________________________________
int main(int argc, char* argv[])
{
  InitCommon();
  InitBinning(); // also in patrick_common.
  
  //
  // OVERWRITE DEFAULT CONFIGS
  //
  kDoEffiCorr = kFALSE;
  debug       = 3;
  
  TString sArg="", sAnaArg="";
  for (int iarg=1; iarg<argc; ++iarg) {
    Printf("argv[%i] = '%s'", iarg, argv[iarg]);
    sArg = argv[iarg];
    
    // arguments to choose the analysis type (they are buffered and executed after configuration):
    if (sArg.Contains("QA"        ,TString::kIgnoreCase))     { sAnaArg.Append(sArg+" "); continue; }
    if (sArg.Contains("ana"       ,TString::kIgnoreCase))     { sAnaArg.Append(sArg+" "); continue; }
    if (sArg.Contains("extr"      ,TString::kIgnoreCase))     { sAnaArg.Append(sArg+" "); continue; }
    if (sArg.Contains("stud"      ,TString::kIgnoreCase))     { sAnaArg.Append(sArg+" "); continue; } // for phiv-study, don't use "phiv"
    if (sArg.Contains("misc"      ,TString::kIgnoreCase))     { sAnaArg.Append(sArg+" "); continue; }
    // arguments to run a specific function. must be given last if they need any configuration.
    if (sArg.Contains("PtEtaEle"  ,TString::kIgnoreCase))     { return MakePtEtaElectron(); }
    if (sArg.Contains("Reso"      ,TString::kIgnoreCase))     { return DrawResolution(); } // uses kDoSemi.
    if (sArg.Contains("Trig"      ,TString::kIgnoreCase))     { return DrawCentrality(); }
    // dataset
    if (sArg.Contains("semi"      ,TString::kIgnoreCase)) {  kDoSemi         = 1; continue; }
    if (sArg.Contains("cent"      ,TString::kIgnoreCase)) {  kDoSemi         = 0; continue; }
    // kinematics
    if (sArg.Contains("pt400"     ,TString::kIgnoreCase)) {  kDoPt400        = 1; continue; }
    if (sArg.Contains("pt200"     ,TString::kIgnoreCase)) {  kDoPt400        = 0; continue; }
    if (sArg.Contains("binsPteePhiV",TString::kIgnoreCase)){ FillBinVec(binsPtee_forPhiV, sArg.Remove(0,sArg.First('=')+1) ); continue; } // use for phiv only with 2 entries.
    // phiv
    if (sArg.Contains("phiVoff"   ,TString::kIgnoreCase)) {  kDoPhiV         = LmManager::kNoCut; continue; }
    if (sArg.Contains("phiVflat"  ,TString::kIgnoreCase)) {  kDoPhiV         = LmManager::kFlatCorrSub; continue; }
    if (sArg.Contains("phiVsub"   ,TString::kIgnoreCase)) {  kDoPhiV         = LmManager::kTemplSub; continue; }
    if (sArg.Contains("phiVconv"  ,TString::kIgnoreCase)) {  kDoPhiV         = LmManager::kTemplConv; continue; }
    if (sArg.Contains("diffGaScal",TString::kIgnoreCase)) {  diffGaScale     = sArg.Remove(0,sArg.First('=')+1).Atof(); continue; }
    // prefilters
    if (sArg.Contains("nopref"    ,TString::kIgnoreCase)) {  kDoPref         = 0; continue; }
    if (sArg.Contains("pref0"     ,TString::kIgnoreCase)) {  kDoPref         = 0; continue; }
    if (sArg.Contains("pref1"     ,TString::kIgnoreCase)) {  kDoPref         = 1; continue; }
    if (sArg.Contains("pref2"     ,TString::kIgnoreCase)) {  kDoPref         = 2; continue; }
    // arguments for plotting
    if (sArg.Contains("req"       ,TString::kIgnoreCase)) {  sReq = sArg.Remove(0,3); continue; } // opens additional spectra, if it contains 'comp'.
    //("012"); // data + MC prompt+gamma
    //("056"); // data
    //("0456"); // data + MC sum (normalized by default)
    //("123"); // all MC
    if (sArg.Contains("plotMeeMin",TString::kIgnoreCase)) { plotMeeMin = sArg.Remove(0,sArg.First('=')+1).Atof(); continue; }
    if (sArg.Contains("plotMeeMax",TString::kIgnoreCase)) { plotMeeMax = sArg.Remove(0,sArg.First('=')+1).Atof(); continue; }
    if (sArg.Contains("plotPteeMin",TString::kIgnoreCase)){ plotPteeMin = sArg.Remove(0,sArg.First('=')+1).Atof(); continue; }
    if (sArg.Contains("plotPteeMax",TString::kIgnoreCase)){ plotPteeMax = sArg.Remove(0,sArg.First('=')+1).Atof(); continue; }
    
    LmHelper::Error(Form("main.cpp: main argument '%s' could not be resolved!", sArg.Data()));
  }
  
  RunSelectedAna(sAnaArg);
  sArg = argv[argc-1]; // last argument
  if (sArg.Contains("all",TString::kIgnoreCase)){
    kDoSemi=(kDoSemi==1)?0:1;
    RunSelectedAna(sAnaArg);
    kDoPt400=(kDoPt400==1)?0:1;
    RunSelectedAna(sAnaArg);
    kDoSemi=(kDoSemi==1)?0:1;
    RunSelectedAna(sAnaArg);
  }
  Int_t nErr = LmHelper::ErrorSummary();
  return nErr;
}

//_______________________________________________________________________________________________
void InitOptions()
{
  if (kDoSemi==1)     sOptCent    = "semi";       else sOptCent   = "cent";
  if (kDoPt400==1)    sOptPt      = "pt400";      else sOptPt     = "pt200";
  if (kDoPref==1)     sOptPref    = "Pref";       else sOptPref   = "NoPref";
  if (kDoPref==2)     sOptPref    = "PrefPhiV";
  sOptPhiV = Form("phiV%s",LmManager::GetExclCutTypeNameStatic(kDoPhiV));
}

//_______________________________________________________________________________________________
void RunSelectedAna(TString sArg)
{
  InitOptions();
  
  if (sArg.Contains("QA"        ,TString::kIgnoreCase))     { FillConfig("QA"  );  QA();                   }
  if (sArg.Contains("ana"       ,TString::kIgnoreCase))     { FillConfig("ana" );  Analysis();             }
  if (sArg.Contains("extr"      ,TString::kIgnoreCase))     { FillConfig("extr");  ExtractPhiVtemplates(); }
  if (sArg.Contains("stud"      ,TString::kIgnoreCase))     { FillConfig("stud");  PhiVstudy();            }
  if (sArg.Contains("misc"      ,TString::kIgnoreCase))     { FillConfig("misc");  Misc();                 }
}


//_______________________________________________________________________________________________
void SetArrayProperties(TObjArray* arrIn)
{
  int nhists = arrIn->GetEntries();
  for (int i=0; i<nhists; i++) {
    TH1* hist = dynamic_cast<TH1*> (arrIn->At(i));
    Int_t color = LmHelper::GetUniformColor(i,nhists);
    hist->SetLineColor(color);
    hist->SetLineWidth(1);
    color = (i==0)?kBlue-9:(i==1)?kRed-9:color;
    hist->SetFillColor(color);
    //hist->SetFillColorAlpha(color, 0.5); // doesnt work.
  }
}


//_______________________________________________________________________________________________
void UpdateXaxis(TH1* hist)
{
  TString sTrkHist[] = {
    "Pt"                        , "#it{p}_{T} (GeV/#it{c})",
    "Eta"                       , "#it{#eta}",
    "Phi"                       , "#it{#varphi}",
    "ITSnCls"                   , "#it{N}_{cls}^{ITS}",
    "dXY"                       , "",
    "dZ"                        , "",
    "TPCnCls"                   , "#it{N}_{cls}^{TPC}",
    "TPCcrossedRows"            , "#it{N}_{cross.rows}^{TPC}",
    "TPCcrossedRowsOverFindable", "#it{N}_{cross.rows}^{TPC}/#it{N}_{find.cls}^{TPC}",
    "TPCchi2"                   , "#it{#chi}^{2}/#it{N}_{cls}^{TPC}",
    ""
  };
  Int_t nTrkHist = sizeof(sTrkHist)/sizeof(*sTrkHist)-1;
  
  for (Int_t ihist=0; ihist<nTrkHist; ihist+=2) {
    if (!TString(hist->GetTitle()).Contains( sTrkHist[ihist] )) continue;
    // set x axis title
    if (!sTrkHist[ihist+1].IsNull()) hist->GetXaxis()->SetTitle(sTrkHist[ihist+1]);
  }
}

//_______________________________________________________________________________________________
void ImproveHistAny(TH1* hist, Int_t npads=3)
{
  UpdateXaxis(hist);
  // beautify
  hist->SetLineWidth(2);
  if (npads>1) {
    hist->SetTitleOffset(gStyle->GetTitleOffset("X")/1.2,"X"); // /1.2
    hist->SetTitleOffset(gStyle->GetTitleOffset("Y")/1.2,"Y"); // /1.2
    hist->SetNdivisions(505,"Y");
    hist->GetXaxis()->CenterTitle();
  }
}



//_______________________________________________________________________________________________
int QA()
{
  // TODO: check for the correct input...
  TString scut16(cconfig[0]);
  TString scut01(cconfig[0]);
  scut01.ReplaceAll("cut16_SPDorSDD14_PID16","cut01_SPD1_PID1");
  scut01.ReplaceAll("cut16","cut01");
  TString scut18(cconfig[0]);
  scut18.ReplaceAll("cut16_SPDorSDD14_PID16","cut18_SPDorSDD15_PID1");
  scut18.ReplaceAll("cut16","cut18");

  LmQA qaData01(const_cast<char*>(scut01.Data()));
  LmQA qaData18(const_cast<char*>(scut18.Data()));
  //LmQA qaData16(const_cast<char*>(scut16.Data()));
  
  
  TString sTrkHist[] = {
    "Pt"                        ,
    "Eta"                       ,
    "Phi"                       ,
    "ITSnCls"                   ,
    "TPCnCls"                   ,
    "TPCchi2"                   ,
    "TPCcrossedRows"            ,
    "TPCcrossedRowsOverFindable",
    "dXY"                       ,
//    "dZ"                        ,
    ""
  };
  Int_t nTrkHist = sizeof(sTrkHist)/sizeof(*sTrkHist)-1;

  // Fill histogram arrays for data and MC. Normalize and style histograms.
  TObjArray* oaTrkHistData = new TObjArray();
  oaTrkHistData->SetOwner();
  for (Int_t ihist=0; ihist<nTrkHist; ihist++) {
    TH1* hist = qaData01.GetTrackHist(sTrkHist[ihist], LmQA::kAll);
    ImproveHistAny(hist);
    hist->Scale(1./hist->Integral());
    hist->GetYaxis()->SetTitle("entries (norm.)");
    hist->SetLineColor(kBlue+1);
    oaTrkHistData->Add(hist);
  }
//  TObjArray* oaTrkHistData2 = new TObjArray();
//  oaTrkHistData2->SetOwner();
//  for (Int_t ihist=0; ihist<nTrkHist; ihist++) {
//    TH1* hist = qaData18.GetTrackHist(sTrkHist[ihist], LmQA::kAll);
//    ImproveHistAny(hist);
//    hist->Scale(1./hist->Integral());
//    hist->GetYaxis()->SetTitle("entries (norm.)");
//    hist->SetLineColor(kBlue+1);
//    oaTrkHistData2->Add(hist);
//  }
  TObjArray* oaTrkHistMC = 0x0;
  LmQA qaMC(const_cast<char*>(cconfig[1].Data()));
  oaTrkHistMC = new TObjArray();
  oaTrkHistMC->SetOwner();
  for (Int_t ihist=0; ihist<nTrkHist; ihist++) {
    TH1* hist = qaMC.GetTrackHist(sTrkHist[ihist], LmQA::kAll);
    ImproveHistAny(hist);
    hist->Scale(1./hist->Integral());
    hist->GetYaxis()->SetTitle("entries (norm.)");
    hist->SetLineColor(kRed+1);
    oaTrkHistMC->Add(hist);
  }
  
  
  TH1*      haxis = 0x0;
  TH1*      hMC   = 0x0;
  TLegend*  leg   = 0x0;
  Int_t     projOffset=0;
  
  // Set up canvas for summary plot
  Double_t sizeFac   = 1.;
  // with the default margins of 0.14 and 0.06, each large pad has has a relative size of 0.8x0.8 and each small one 0.4x0.4.
  // here we need 3 small pads next to each other plus the margins:
  Int_t nHor = 3;
  Int_t nVer = 1;
  Double_t canRelWidth  = (nHor*0.4+0.14+0.06)*sizeFac;
  Double_t canRelHeight = (nVer*0.4+0.10+0.10)*sizeFac;
  Double_t titleSize    = gStyle->GetTitleSize()/canRelHeight*1.2;
  Double_t labelSize    = gStyle->GetLabelSize()/canRelHeight*1.2;

  Printf("______ create QA plot: Kinematics ______");
  projOffset=0;
  TCanvas* cDataMC_Kine = new TCanvas("cDataMC_Kine", "cDataMC_Kine", canRelWidth*gStyle->GetCanvasDefW(), canRelHeight*gStyle->GetCanvasDefH());
  // bottom- and topmargins shall have the same absolute size as in a large figure, so scale them by the relative height of this canvas.
  LmHelper::CreateManyPads(cDataMC_Kine,nHor,nVer, 0.1/canRelHeight,0.1/canRelHeight, 0.14/canRelWidth,0.06/canRelWidth);
  for (int ihist=0; ihist<nHor*nVer; ihist++) {
    if (ihist+projOffset >= oaTrkHistData->GetEntries()) continue;
    cDataMC_Kine->cd(ihist+1);
    TH1F* hist = dynamic_cast<TH1F*>(oaTrkHistData->At(ihist+projOffset));
    hMC = dynamic_cast<TH1F*>(oaTrkHistMC->At(ihist+projOffset));
    hist->GetYaxis()->SetRangeUser(0, TMath::Max(hist->GetMaximum(),hMC->GetMaximum())*1.05);
    
    hist->SetTitleSize(titleSize,"XY");
    hist->SetLabelSize(labelSize,"XY");
    if (TString(hist->GetTitle()).Contains("Pt")) {
      hist->GetXaxis()->SetRangeUser(0.,3.8);
      hist->SetNdivisions(505,"X");
    }
    if (TString(hist->GetTitle()).Contains("Eta")) {
      hist->GetXaxis()->SetRangeUser(-0.9, 0.9);
      hist->SetNdivisions(505,"X");
    }
    if (TString(hist->GetTitle()).Contains("Phi"))      hist->GetXaxis()->SetRangeUser(0.06, TMath::TwoPi()); // to not draw the label "0".
    
    if (haxis)  hist->DrawCopy("hist same");
    else        hist->DrawCopy("hist");
    hMC->DrawCopy("hist same");
    
    if (ihist==0) {
      TPad* padIn = new TPad("inlay","inlay",0.5,0.4,0.97,0.82);
      padIn->SetLeftMargin(0.18);
      padIn->cd()->SetLogy();
      hist->GetXaxis()->SetRangeUser(0, 3.5);
      hist->GetYaxis()->SetRangeUser(0.0005, TMath::Max(hist->GetMaximum(),hMC->GetMaximum())*1.5);
      hist->SetTitleSize(0,"XY");
      hist->SetLabelSize(labelSize*1.5,"XY");
      hist->DrawCopy("hist");
      hMC->DrawCopy("hist same");
      cDataMC_Kine->cd(ihist+1);
      padIn->Draw();
    }
    
    if (ihist==1) { // 1 = middle pad
      leg = new TLegend(0.40,0.25,0.85,0.44);
      leg->SetTextSize(labelSize);
      leg->ConvertNDCtoPad();
      leg->SetFillStyle(0);
      leg->AddEntry(hist, "data");
      leg->AddEntry(hMC, "MC");
      leg->Draw();
    }
    cDataMC_Kine->cd(ihist+1)->RedrawAxis();
    if (haxis) delete haxis; haxis=0x0;
  }
  cDataMC_Kine->Print( Form("%s/cDataMC-Kine-%s-%s.pdf","./QAplots",sOptCent.Data(),sOptPt.Data()) );


  Printf("______ create QA plot: Mixed ______");
  projOffset=3;
  TCanvas* cDataMC_Mix = new TCanvas("cDataMC_Mix", "cDataMC_Mix", canRelWidth*gStyle->GetCanvasDefW(), canRelHeight*gStyle->GetCanvasDefH());
  // bottom- and topmargins shall have the same absolute size as in a large figure, so scale them by the relative height of this canvas.
  LmHelper::CreateManyPads(cDataMC_Mix,nHor,nVer, 0.1/canRelHeight,0.1/canRelHeight, 0.14/canRelWidth,0.06/canRelWidth);
  for (int ihist=0; ihist<nHor*nVer; ihist++) {
    if (ihist+projOffset >= oaTrkHistData->GetEntries()) continue;
    cDataMC_Mix->cd(ihist+1);
    TH1F* hist = dynamic_cast<TH1F*>(oaTrkHistData->At(ihist+projOffset));
    hMC = dynamic_cast<TH1F*>(oaTrkHistMC->At(ihist+projOffset));
    hist->GetYaxis()->SetRangeUser(0, TMath::Max(hist->GetMaximum(),hMC->GetMaximum())*1.05);
    
    hist->SetTitleSize(titleSize,"XY");
    hist->SetLabelSize(labelSize,"XY");
    
    if (TString(hist->GetTitle()).Contains("XY")) {
      hist->SetNdivisions(505,"X");
      hist->GetXaxis()->SetRangeUser(-0.17,0.17);
    }
    if (TString(hist->GetTitle()).Contains("TPCchi2"))  hist->GetXaxis()->SetRangeUser(0.7, 4.4);
    if (TString(hist->GetTitle()).Contains("ITSnCls")) {
      hist->SetNdivisions(8,"X");
      hist->GetXaxis()->SetRangeUser(1, 6);
    }
    if (TString(hist->GetTitle()).Contains("TPCnCls")) {
      haxis = new TH1F("haxis","haxis",180,-0.5,179.5);
      haxis->GetXaxis()->SetRangeUser(55, 168);
      haxis->GetYaxis()->SetRangeUser(0, hist->GetMaximum()/* *1.05*/);
      haxis->GetXaxis()->SetTitle(hist->GetXaxis()->GetTitle());
      haxis->GetYaxis()->SetTitle(hist->GetYaxis()->GetTitle());
      haxis->SetTitleOffset(gStyle->GetTitleOffset("X")/1.2,"X"); // /1.2
      haxis->SetTitleOffset(gStyle->GetTitleOffset("Y")/1.2,"Y"); // /1.2
      haxis->SetTitleSize(titleSize,"XY");
      haxis->SetLabelSize(labelSize,"XY");
      haxis->SetNdivisions(508,"X");
      haxis->SetNdivisions(505,"Y");
      haxis->GetXaxis()->CenterTitle();
      haxis->DrawCopy("axis");
    }    
    if (haxis)  hist->DrawCopy("hist same");
    else        hist->DrawCopy("hist");
    hMC->DrawCopy("hist same");
    
    if (ihist==0) { // 0 = left pad
      leg = new TLegend(0.35,0.55,0.85,0.74);
      leg->SetTextSize(labelSize);
      leg->ConvertNDCtoPad();
      leg->SetFillStyle(0);
      leg->AddEntry(hist, "data");
      leg->AddEntry(hMC, "MC");
      leg->Draw();
    }
    cDataMC_Mix->cd(ihist+1)->RedrawAxis();
    if (haxis) delete haxis; haxis=0x0;
  }
  cDataMC_Mix->Print( Form("%s/cDataMC-Mix-%s-%s.pdf","./QAplots",sOptCent.Data(),sOptPt.Data()) );
  
  
  Printf("______ create QA plot: TPC ______");
  projOffset=6;
  TCanvas* cDataMC_TPC = new TCanvas("cDataMC_TPC", "cDataMC_TPC", canRelWidth*gStyle->GetCanvasDefW(), canRelHeight*gStyle->GetCanvasDefH());
  // bottom- and topmargins shall have the same absolute size as in a large figure, so scale them by the relative height of this canvas.
  LmHelper::CreateManyPads(cDataMC_TPC,nHor,nVer, 0.1/canRelHeight,0.1/canRelHeight, 0.14/canRelWidth,0.06/canRelWidth);
  for (int ihist=0; ihist<nHor*nVer; ihist++) {
    if (ihist+projOffset >= oaTrkHistData->GetEntries()) continue;
    cDataMC_TPC->cd(ihist+1);
    TH1F* hist = dynamic_cast<TH1F*>(oaTrkHistData->At(ihist+projOffset));
    hMC = dynamic_cast<TH1F*>(oaTrkHistMC->At(ihist+projOffset));
    hist->GetYaxis()->SetRangeUser(0, TMath::Max(hist->GetMaximum(),hMC->GetMaximum())*1.05);
    
    hist->SetTitleSize(titleSize,"XY");
    hist->SetLabelSize(labelSize,"XY");

    if (TString(hist->GetTitle()).Contains("XY")) {
      hist->SetNdivisions(505,"X");
      hist->GetXaxis()->SetRangeUser(-0.17,0.17);
    }
    if (TString(hist->GetTitle()).Contains("TPCchi2"))          hist->GetXaxis()->SetRangeUser(0.7, 4.4);
    if (TString(hist->GetTitle()).Contains("RowsOverFindable")) hist->GetXaxis()->SetRangeUser(0.64, 1.16);
    else if (TString(hist->GetTitle()).Contains("Rows")) {
      haxis = new TH1F("haxis","haxis",180,-0.5,179.5);
      haxis->GetXaxis()->SetRangeUser(95, 164);
      haxis->GetYaxis()->SetRangeUser(0, hist->GetMaximum()/* *1.05*/);
      haxis->GetXaxis()->SetTitle(hist->GetXaxis()->GetTitle());
      haxis->GetYaxis()->SetTitle(hist->GetYaxis()->GetTitle());
      haxis->SetTitleOffset(gStyle->GetTitleOffset("X")/1.2,"X"); // /1.2
      haxis->SetTitleOffset(gStyle->GetTitleOffset("Y")/1.2,"Y"); // /1.2
      haxis->SetTitleSize(titleSize,"XY");
      haxis->SetLabelSize(labelSize,"XY");
      haxis->SetNdivisions(505,"X");
      haxis->SetNdivisions(505,"Y");
      haxis->GetXaxis()->CenterTitle();
      haxis->DrawCopy("axis");
    }
    
    if (haxis)  hist->DrawCopy("hist same");
    else        hist->DrawCopy("hist");
    hMC->DrawCopy("hist same");

    if (ihist==0) { // 0 = left pad
      leg = new TLegend(0.35,0.55,0.85,0.74);
      leg->SetTextSize(labelSize);
      leg->ConvertNDCtoPad();
      leg->SetFillStyle(0);
      leg->AddEntry(hist, "data");
      leg->AddEntry(hMC, "MC");
      leg->Draw();
    }
    cDataMC_TPC->cd(ihist+1)->RedrawAxis();
    if (haxis) delete haxis; haxis=0x0;
  }
  cDataMC_TPC->Print( Form("%s/cDataMC-TPC-%s-%s.pdf","./QAplots",sOptCent.Data(),sOptPt.Data()) );
  


  //  return 0;
  
  
  TObjArray* oaTrkRecovery[3];
  TH1F *h18, *h01;
  // Phi
  h18   = (TH1F*) qaData18.GetTrackHist("Phi", LmQA::kAll);
  h01   = (TH1F*) qaData01.GetTrackHist("Phi", LmQA::kAll);
  h01->Scale(1./h18->Integral(), "width"); // normalize to same statistics as h18
  h18->Scale(1./h18->Integral(), "width");
  h18->GetYaxis()->SetTitle("entries (norm.)");
  oaTrkRecovery[0] = new TObjArray();
  oaTrkRecovery[0]->SetOwner();
  oaTrkRecovery[0]->Add(h18);
  oaTrkRecovery[0]->Add(h01);
  // ITSnCls
  h18   = (TH1F*) qaData18.GetTrackHist("ITSnCls", LmQA::kAll);
  h01   = (TH1F*) qaData01.GetTrackHist("ITSnCls", LmQA::kAll);
  h01->Scale(1./h18->Integral()*h18->GetBinContent(7)/h01->GetBinContent(7)); // normalize also for different statistics in last bin...
  h18->Scale(1./h18->Integral());
  cout << "stat gain: (h18-h01)/h01 = " << (h18->Integral() - h01->Integral()) / h01->Integral() << endl;
  h18->GetYaxis()->SetTitle("entries (norm.)");
  oaTrkRecovery[1] = new TObjArray();
  oaTrkRecovery[1]->SetOwner();
  oaTrkRecovery[1]->Add(h18);
  oaTrkRecovery[1]->Add(h01);
  //TH1F* hDiff = (TH1F*) h18->Clone("ITSnClsDiff"); hDiff->Add( h01, -1 ); oaTrkRecovery[0]->Add(hDiff);
  // DCA
  h18   = (TH1F*) qaData18.GetTrackHist("dXY", LmQA::kAll);
  h01   = (TH1F*) qaData01.GetTrackHist("dXY", LmQA::kAll);
  h01->Scale(1./h18->Integral()); // normalize to same statistics as h18
  h18->Scale(1./h18->Integral());
  h18->GetYaxis()->SetTitle("entries (norm.)");
  oaTrkRecovery[2] = new TObjArray();
  oaTrkRecovery[2]->SetOwner();
  oaTrkRecovery[2]->Add(h18);
  oaTrkRecovery[2]->Add(h01);
  
  
  Printf("______ create QA plot: Track Recovery ______");
  TCanvas* cTrkRecov = new TCanvas("cTrkRecov", "cTrkRecov", canRelWidth*gStyle->GetCanvasDefW(), canRelHeight*gStyle->GetCanvasDefH());
  // bottom- and topmargins shall have the same absolute size as in a large figure, so scale them by the relative height of this canvas.
  LmHelper::CreateManyPads(cTrkRecov,nHor,nVer, 0.1/canRelHeight,0.1/canRelHeight, 0.14/canRelWidth,0.06/canRelWidth);
  for (int ihist=0; ihist<nHor*nVer; ihist++) {
    if (!oaTrkRecovery[ihist]) continue;
    cTrkRecov->cd(ihist+1);
    TH1F* hist     = dynamic_cast<TH1F*>(oaTrkRecovery[ihist]->At(0));
    TH1F* histMain = dynamic_cast<TH1F*>(oaTrkRecovery[ihist]->At(1));
    
    ImproveHistAny(hist);
    //SetArrayProperties(oaTrkRecovery[ihist]);
    histMain->SetLineColor(LmHelper::GetUniformColor(0,2));
    histMain->SetFillColor(kBlue-9);
    histMain->SetLineWidth(1);
    hist->SetLineColor(LmHelper::GetUniformColor(3,2));
    hist->SetFillColor(kGreen-9);
//    hist->SetLineColor(LmHelper::GetUniformColor(6,2));
//    hist->SetFillColor(kCyan-9);
//    hist->SetLineColor(LmHelper::GetUniformColor(4,2));
//    hist->SetFillColor(kMagenta-9);
    hist->SetLineWidth(1);
    
    hist->SetTitleSize(titleSize,"XY");
    hist->SetLabelSize(labelSize,"XY");
    hist->GetYaxis()->SetRangeUser(0, hist->GetMaximum()*1.05);
    if (TString(hist->GetTitle()).Contains("ITSnCls")) {
      hist->SetNdivisions(107,"X"); // no sub-ticks for integer number and up to 7 main ticks (6 needed).
      hist->GetXaxis()->SetRangeUser(1, 6);
      hist->GetYaxis()->SetRangeUser(0, hist->GetMaximum()*1.2); // space for the legend
    }
    //if (TString(hist->GetTitle()).Contains("Phi"))      hist->GetXaxis()->SetRangeUser(0.06, TMath::TwoPi()); // to not draw the label "0", if this plot is not in the left panel.
    if (TString(hist->GetTitle()).Contains("XY")) {
      hist->SetNdivisions(505,"X");
      hist->GetXaxis()->SetRangeUser(-0.17,0.17);
      //      hist->GetXaxis()->SetRangeUser(-0.25,0.25);
      //      hist->GetXaxis()->SetRangeUser(-0.98,0.98);
      //      cTrkRecov->cd(ihist+1)->SetLogy();
    }
    oaTrkRecovery[ihist]->DrawClone("hist same"); // errors not computed.
    
    if (TString(hist->GetTitle()).Contains("ITSnCls")) {
      leg = new TLegend(0.28,0.62,0.85,0.80);
      leg->SetTextSize(labelSize);
      leg->ConvertNDCtoPad();
      leg->SetFillStyle(0);
      //      leg->AddEntry(histMain, "SPD first");
      //      leg->AddEntry(hist, "+ SDD first");
      leg->AddEntry(histMain, "main track sel.");
      leg->AddEntry(hist, "+ recovery");
      leg->Draw();
    }
    
    cTrkRecov->cd(ihist+1)->RedrawAxis();
  }
  cTrkRecov->Print( Form("%s/cTrkRecov-%s-%s.pdf","./QAplots",sOptCent.Data(),sOptPt.Data()) );
  
  return 0;
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
  for (int ic=0; ic<n_config; ic++) {
    LmFileManager::Instance()->AddConfig( cconfig[ic] );
  }
  
  {
    for (int ic=0; ic<n_config; ic++) 
    {
      // create manager from config string
      LmManager* mgr = new LmManager(const_cast<char*>(cconfig[ic].Data()));// (only one rootfile, instead of low+high)
      if (cconfig[ic].Contains("data_4D") || cconfig[ic].Contains("MC_4D"))
        mgr->SetInputhistAndDim("M_Pt_PhivPair_OpeningAngle", 4);
      else
        mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
      mgr->SetEnableEffiCorr(kFALSE);
      mgr->SetRebinning2D(n_mee_bin, mee_bin, n_ptee_bin, ptee_bin); // the binning used for spectra3D-5-... seems different from any arrays I have...
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
    
    // better use main arguments to overwrite the default...
    if (plotMeeMax>=4.) plotMeeMax  = 0.7;
    
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
      han_compare->PrintCompare(histbits, i, LmBaseSignal::kProjOnMee, Form("+%s",GetAllOptions().Data()), kDoLegend);
    }
    han_compare->ResetPlotRangeY();
    
    // write most important histograms to rootfile:
    // when running with option "all", there is still a bug with the subdirectories...
    const Char_t* filename = Form("spectra3D-5-%s-%s-%s-MCall+prompt+conv+oneGa+diffGa+hadrCont.root",sOptCent.Data(),sOptPt.Data(),sOptPref.Data());
    TFile* _fileOut = new TFile(filename, "RECREATE");
    //han_compare->SetRootfile(_fileOut);
    han_compare->Write3DHist(LmSignal::kUnlike+LmSignal::kBkg); //in 3D only Unlike and Bkg exist.
    _fileOut->Close();
    
    for (int ic=0; ic<n_config; ic++) {
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
int PhiVstudy()
{
  LmHelper::Info("========== doPhiVstudy ==========");
  //
  std::vector<LmManager*>     mgrVec; // works when using pointers (they survive after the for-loop). otherwise fancy errors.
  std::vector<LmBackground*>  bkgVec;
  std::vector<LmSignal*>      sigVec;
  std::vector<LmManager*>     mgrVec_inputs;
  {
    projoption = "xz"; // option="ab" means: a vertical, b horizontal (ROOT-convention)
    // 'xz' means mee on y, 'yz' means ptee on y
    writeFile=kTRUE;
    
    //kDoPhiV = LmManager::kTemplUnsub;
    //kDoPhiV = LmManager::kTemplSub;
    //kDoPhiV = LmManager::kNoCut;
    
    TFile *_fTempl3 = 0x0, *_fTempl4 = 0x0, *_fTempl5 = 0x0, *_fTempl5_noPref = 0x0;
    TH3D *hSig3=0x0, *hCon3=0x0, *hULS3=0x0, *hLS3=0x0;
    TH3D *hSigNoPF=0x0, *hSig=0x0, *hCon=0x0, *hULS=0x0, *hLS=0x0, *hDiffGa=0x0, *hDiffGa_LS=0x0, *hNorm=0x0;
    if (kDoPhiV>=LmManager::kTemplUnsub) { // if templates are needed
      //_fTempl3 = LmHelper::SafelyOpenRootfile(Form("./input/PbPb/templates/spectra3D-3-%s-%s-MCall+prompt+conv+noConv.root",sOptCent.Data(),sOptPt.Data()));
      //hSig3 = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl3, 1, "hUnlike");  hSig3->SetName("hSig"); // file 3 prompt
      //hCon3 = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl3, 2, "hUnlike");  hCon3->SetName("hCon"); // file 3 conversions
      //hULS3 = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl3, 3, "hUnlike");  hULS3->SetName("hULS"); // file 3 ULS+LS (key 0=all, 3=noConv) w/ paircuts
      //hLS3  = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl3, 3, "hBkg");     hLS3->SetName("hLS");   // file 3 ULS+LS (key 0=all, 3=noConv) w/ paircuts
      //hULS=hULS3;  hLS=hLS3;
      //_fTempl4 = LmHelper::SafelyOpenRootfile(Form("./input/PbPb/templates/spectra3D-4-%s-%s-noPC-MCall+prompt+conv+diffGamma.root",sOptCent.Data(),sOptPt.Data()));
      //hSig = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl4, 1, "hUnlike");  hSig->SetName("hSig");  // file 4 prompt
      //hCon = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl4, 2, "hUnlike");  hCon->SetName("hCon");  // file 4 conversions
      //hDiffGa    = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl4, 3, "hUnlike");  hDiffGa->SetName("hDiffGamma");       // file 4 diff gamma ULS
      //hDiffGa_LS = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl4, 3, "hBkg");     hDiffGa_LS->SetName("hDiffGamma_LS"); // file 4 diff gamma LS
      //hDiffGa->Add(hDiffGa_LS, -1); // diff gamma subtracted
      //cout << " opening template file: " << Form("./input/PbPb/templates/spectra3D-5-%s-%s-NoPref-MCall+prompt+conv+oneGa+diffGa+hadrCont.root",sOptCent.Data(),sOptPt.Data()) << endl;
      _fTempl5_noPref = LmHelper::SafelyOpenRootfile(Form("./input/PbPb/templates/spectra3D-5-%s-%s-NoPref-MCall+prompt+conv+oneGa+diffGa+hadrCont.root",sOptCent.Data(),sOptPt.Data()));
      hSigNoPF = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5_noPref, 1, "hUnlike");  hSigNoPF->SetName("hSigNoPF");  // file 5 prompt, no prefilter
      _fTempl5 = LmHelper::SafelyOpenRootfile(Form("./input/PbPb/templates/spectra3D-5-%s-%s-%s-MCall+prompt+conv+oneGa+diffGa+hadrCont.root",sOptCent.Data(),sOptPt.Data(),sOptPref.Data()));
      hSig       = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5, 1, "hUnlike");  hSig->SetName((kDoPref>0?"hSigPF":"hSig"));  // file 5 prompt
      hCon       = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5, 2, "hUnlike");  hCon->SetName("hCon");                // file 5 conversions
      hDiffGa    = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5, 4, "hUnlike");  hDiffGa->SetName("hDiffGamma");       // file 5 diff gamma ULS
      hDiffGa_LS = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5, 4, "hBkg");     hDiffGa_LS->SetName("hDiffGamma_LS"); // file 5 diff gamma LS
      hDiffGa->Add(hDiffGa_LS, -1); // diff gamma subtracted
      hNorm = (TH3D*) hSig->Clone("hNorm");
      hNorm->Add(hDiffGa, diffGaScale);
      //hNorm->Add(hCon, diffGaScale); // additional scaling of true conversions preferred by the first mass bin for diffGaScale~0.5-0.7.
      hNorm->Add(hCon);
    }
    
    // Construct path for plots.
    TString sPrintPath = "./plots/_PhiVstudy/";
    sPrintPath.Append(sOptCent+"-"+sOptPt+"/");
    sPrintPath.Append(sOptPhiV+"-"+sOptPref);
    if (diffGaScale!=1) sPrintPath.Append(Form("-DiffGa%.2f", diffGaScale));
    sPrintPath.Append("/");
    // Create the output directory and configure it in gEnv.
    // (unfortunately that path will not be used automatically, see workaround in LmHandler::PrintCompare().)
    gSystem->Exec( Form("mkdir -p %s", sPrintPath.Data()) );
    gEnv->SetValue("Canvas.PrintDirectory",sPrintPath.Data());
    cout << "output path   =   " << gEnv->GetValue("Canvas.PrintDirectory",".") << endl;
    cout << endl;
    
    
    // Add all configs to LmFileManager for efficient file handling
    for (int ic=0; ic<n_config; ic++) {
      LmFileManager::Instance()->AddConfig( cconfig[ic] );
    }
    
    Double_t phiv_bin_1[] = { 1 }; // if only one number is given, it will be used for Rebin(n).
    Double_t* phiv_bin_local=0x0;
    Int_t phiv_rebinfactor=1; // 1 or 4
    phiv_bin_1[0]*=phiv_rebinfactor;
    phiv_bin[0]*=phiv_rebinfactor;
    
    // fill vector of input managers
    for (int ic=0; ic<n_config; ic++) 
    {
      LmManager* mgr = new LmManager(const_cast<char*>(cconfig[ic].Data()));// (only one rootfile, instead of low+high)
      // set further configuration for the manager
      if (cconfig[ic].Contains("data_4D") || cconfig[ic].Contains("MC_4D")) {
        mgr->SetInputhistAndDim("M_Pt_PhivPair_OpeningAngle", 4);
        phiv_bin_local = &phiv_bin_1[0];
        if (cconfig[ic].Contains("bothTasks")) phiv_bin_local = &phiv_bin[0]; // some 4D MC still have old phiV binning.
      } else {
        mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
        phiv_bin_local = &phiv_bin[0];
      }
      mgr->SetProjOption(projoption);
      mgr->SetEnableEffiCorr(kDoEffiCorr);
      mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
      mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
      mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
      mgr->SetTemplateNormRegionMin(n_cutPhiVbelow, cutPhiVbelow); // only needed for some template types.
      mgr->SetTemplateNormRegionMax(n_cutPhiVabove, cutPhiVabove); // only needed for some template types.
      // use individual phiV cut settings:
      if ((int)phiVtype.size()>ic) kDoPhiV = phiVtype.at(ic);
      if (kDoPhiV==LmManager::kTemplSub)   mgr->SetExclusionZTemplates(hSigNoPF, 0x0, LmManager::kTemplSub  , hSig, hNorm); // special case implemented for phiV-study, check LmManager::CorrectForExclusionCutIn2D().
      if (kDoPhiV==LmManager::kTemplConv)  mgr->SetExclusionZTemplates(hCon    , 0x0, LmManager::kTemplConv , hSig, hNorm);
      if (kDoPhiV==LmManager::kTemplUnsub) {
        if (hULS && hLS)                   mgr->SetExclusionZTemplates(hULS    , hLS     , LmManager::kTemplUnsub, hSig, hNorm);
        else                               mgr->SetExclusionZTemplates(hSigNoPF, hSigNoPF, LmManager::kTemplUnsub, hSig, hNorm); // workaround since ULS and LS are not available w/o paircuts.
      }
      mgr->SetEnableExclusionCutZ(kDoPhiV); // to be able to change or deactivate the cut without changing the code above.
      
      mgr->SetProjRange(thetaEEmin, TMath::Pi(), 3); // axis 3 = dimension 4 = opening angle.
      mgr->SetThetaEEmin(thetaEEmin);
      if (projoption.EqualTo("xz")) // 'xz' means mee on y, phiv on x
        mgr->SetRebinning2D(n_phiv_bin, phiv_bin_local, n_mee_bin, mee_bin);
      if (projoption.EqualTo("yz")) // 'yz' means ptee on y, phiv on x
        mgr->SetRebinning2D(n_phiv_bin, phiv_bin_local, n_ptee_bin_phiv, ptee_bin_phiv);
      if (projoption.EqualTo("yx")) // 'yx' means ptee on y, mee on x (default analysis)
        mgr->SetRebinning2D(n_mee_bin, mee_bin, n_ptee_bin_phiv, ptee_bin_phiv);
      // read in histograms from data files
      mgr->Process(LmManager::kReadInputOnly);
      mgrVec_inputs.push_back(mgr);
    }
    
    // define 3D-projection binning
    // at least one of these two arrays should have only a single integrated bin, otherwise we get many managers...
    // since there is only one handler for all signals, all 3D-subranges - if any - will be plotted together.
    Double_t bins3DProjRangeX[] = { -1, -1 }; // mee
    //Double_t bins3DProjRangeX[] = { 0.00, /*0.02, 0.04, 0.06,*/ /*0.10,*/ 3.3 }; // mee
//    Double_t bins3DProjRangeY[] = { 0., 1., 2., 4., 6. }; // ptee // with more than one bin the templates seem to get messed up.
//    Double_t bins3DProjRangeY[] = { 0., 1. }; // ptee
//    Double_t bins3DProjRangeY[] = { 1., 2. }; // ptee
//    Double_t bins3DProjRangeY[] = { 2., 4. }; // ptee
//    Double_t bins3DProjRangeY[] = { 4., 6. }; // ptee
//    Double_t bins3DProjRangeY[] = { 0., 6. }; // ptee
    if (binsPtee_forPhiV.size()<2) {
      binsPtee_forPhiV.clear();
      binsPtee_forPhiV.push_back(0.);
      binsPtee_forPhiV.push_back(6.);
    }
    unsigned int n_bins3DProjRangeX = sizeof(bins3DProjRangeX)/sizeof(*bins3DProjRangeX) -1;
    unsigned int n_bins3DProjRangeY = binsPtee_forPhiV.size() -1;
    Double_t* bins3DProjRangeY = binsPtee_forPhiV.data();
    if (n_bins3DProjRangeX>1) LmHelper::Error("computation of phiV-corrected spectra with templates for multiple mee slices at the same time is messed up!");
    if (n_bins3DProjRangeY>1) LmHelper::Error("computation of phiV-corrected spectra with templates for multiple ptee slices at the same time is messed up!");

    // fill vector of managers with selected 3D subranges
    for (unsigned int iproj_x=0; iproj_x<n_bins3DProjRangeX; iproj_x++)
    {
      for (unsigned int iproj_y=0; iproj_y<n_bins3DProjRangeY; iproj_y++)
      {
        for (unsigned int imgr=0; imgr<mgrVec_inputs.size(); imgr++) {
          // make a copy of the manager including its input histograms
          LmManager* mgr_i = new LmManager(*(mgrVec_inputs.at(imgr)));
          if (n_bins3DProjRangeY>1 || bins3DProjRangeY[0]!=0 || bins3DProjRangeY[1]==1)
            mgr_i->SetName(Form("%s (%.0f-%.0f GeV)",mgr_i->GetName(), bins3DProjRangeY[iproj_y], bins3DProjRangeY[iproj_y+1])); // cannot use "/c" when saving it to rootfile.
          // select different subranges in input histograms
          mgr_i->Set3DProjRangeX(bins3DProjRangeX[iproj_x], bins3DProjRangeX[iproj_x+1]);
          mgr_i->Set3DProjRangeY(bins3DProjRangeY[iproj_y], bins3DProjRangeY[iproj_y+1]);
          // add new manager to vector
          mgrVec.push_back(mgr_i);
        }
        // add manager for integrated y range, if there is more than one bin in y. (nicer to have a separate loop)
        if (n_bins3DProjRangeY>1 && iproj_y==n_bins3DProjRangeY-1) {
          for (unsigned int imgr=0; imgr<mgrVec_inputs.size(); imgr++) {
            LmManager* mgr_i = new LmManager(*(mgrVec_inputs.at(imgr)));
            mgr_i->SetName(Form("%s (%.0f-%.0f GeV)",mgr_i->GetName(), bins3DProjRangeY[0], bins3DProjRangeY[iproj_y+1])); // cannot use "/c" when saving it to rootfile.
            mgr_i->Set3DProjRangeX(bins3DProjRangeX[0], bins3DProjRangeX[iproj_x+1]);
            mgr_i->Set3DProjRangeY(bins3DProjRangeY[0], bins3DProjRangeY[iproj_y+1]);
            mgrVec.push_back(mgr_i);
          }
        }
      }
    }
    
    // for each manager: create background and signal class from it, configure and process them, store them in vectors
    for (unsigned int iproj=0; iproj<mgrVec.size(); iproj++)
    {
      cout << " iproj = " << iproj << " name = " << mgrVec.at(iproj)->GetName() << endl;
      // process the managers: make the projections, rebinning, corrections...
      mgrVec.at(iproj)->Process(LmManager::kDontReadInput); // dont read in rootfiles again
      //mgrVec.at(iproj)->Print2DUnlike(Form("c2DUnlike_%d.pdf",iproj));
      
      LmBackground* bkg_i = new LmBackground(*(mgrVec.at(iproj)));
      bkg_i->Process(LmBackground::kHybrid);
      bkgVec.push_back(bkg_i);
      
      TString signame = mgrVec.at(iproj)->GetName();
//      signame.Append(" "+mgrVec.at(iproj)->GetAll3DProjRanges());
      if (mgrVec.at(iproj)->GetExclCutType()==LmManager::kTemplUnsub) signame.Append(" matched");
      if (mgrVec.at(iproj)->GetExclCutType()==LmManager::kTemplConv)  signame.Append(" - conv");
      if (mgrVec.at(iproj)->GetExclCutType()==LmManager::kTemplSub) {
        // try to add an uncut subtracted signal to help in the phiV correction of the current signal.
        if (mgrVec.at(0)->GetExclCutType()==LmManager::kNoCut)
          mgrVec.at(iproj)->AddVisualSig(sigVec.at(0)->GetSubSig2D(),"hDataOrig","data, no #it{#phi}_{V} corr.");
      }
      
      LmSignal* sig_i_Std = new LmSignal(*(mgrVec.at(iproj)), *(bkgVec.at(iproj)), signame.Data()); //Form("Projection_%d", iproj)
      sig_i_Std->SetDoSubtraction(kTRUE);
      sig_i_Std->SetDoSignifRaw(kDoSignifRaw);
//      sig_i_Std->SetDoNormBinwidth( (projoption.EqualTo("xz")||projoption.EqualTo("yz"))?kFALSE:kDoNormBinwidth );
      sig_i_Std->SetDoNormBinwidth( kDoNormBinwidth );
      sig_i_Std->SetDoNormNevents(kDoNormNevents);
//      sig_i_Std->SetDoNormBinwidth(kFALSE);
//      sig_i_Std->SetDoNormNevents(kFALSE);
      sig_i_Std->Process(LmSignal::kStd);
      // if a signal has produced additional histograms, e.g. to visualize its phiV-correction, then extract them for plotting.
      Int_t skipFirstVisual=1;
      for (unsigned int ivis=skipFirstVisual; ivis<sig_i_Std->GetNVisualSig(); ivis++) {
        sigVec.push_back(sig_i_Std->GetVisualSigI(ivis));
      }
      if (sReq.Contains("sys") && mgrVec.at(iproj)->GetExclCutType()==LmManager::kTemplSub) {
        // add systematics to the signal. Needs to be added into pat_sys later...
        sig_i_Std->SetRelSystematicsLow(  CreateRelSysPhiV(1.5) );
        sig_i_Std->SetRelSystematicsHigh( CreateRelSysPhiV(0.5) );
        sig_i_Std->Process(LmSignal::kSystematic);
      }
      sigVec.push_back(sig_i_Std);
    }
    
    // close rootfile(s) from input manager(s) (to free memory if many files have been opened...)
    for (unsigned int imgr=0; imgr<mgrVec_inputs.size(); imgr++) {
      mgrVec_inputs.at(imgr)->Process(LmManager::kCleanUp);
    }
    
    // better use main arguments to overwrite the default...
    //plotMeeMax  = 0.5;
    //plotPteeMax = 4.0; // 4.0 seems to be the current limit in the template outputs.
    //plotPhiVMax = 3.14;
    Bool_t kDoLegend=kTRUE;
    Bool_t kDoLogY;
    
    LmHandler* han_compare = new LmHandler(LmHandler::kCompare);
    han_compare->SetLegend(GetLegendTemplate(kDefault)); // is modified in plotting section below.
    han_compare->SetLabels(GetLabelsTemplate(kDefault));
    han_compare->SetRequestedSignals(sReq);
    if (sReq.BeginsWith("5meesys")) { // customize for thesis plot to get blue markers for corrected data.
      han_compare->SetRequestedSignals("");
      han_compare->AttachSignal(*(sigVec.at(5)), "#it{#phi}_{V}-corrected data");
      writeFile=kFALSE; // the rootfile must contain all signals for other plots.
    }
    else { // default
      // attach signals to compare handler. they may already be processed or not.
      for (unsigned int i=0; i<sigVec.size(); i++) {
        han_compare->AttachSignal(*(sigVec.at(i)), sigVec.at(i)->GetName());
      }
    }
    if (projoption.EqualTo("xz")) { // 'xz' means mee on y, phiv on x
      han_compare->SetBinsY_forprojOnX(binsMee_forPhiV);
      han_compare->SetBinsX_forprojOnY(binsPhiV);
      han_compare->SetPlotRangeMee(plotPhiVMin, plotPhiVMax);
      han_compare->SetPlotRangePtee(plotMeeMin, plotMeeMax);
      kDoLogY=kFALSE;
    }
    if (projoption.EqualTo("yz")) { // 'yz' means ptee on y, phiv on x
      han_compare->SetBinsY_forprojOnX(binsPtee_forMee);//binsPtee_forPhiV doesnt exist. now it does, keeping this anyhow...
      han_compare->SetBinsX_forprojOnY(binsPhiV);
      han_compare->SetPlotRangeMee(plotPhiVMin, plotPhiVMax);
      han_compare->SetPlotRangePtee(plotPteeMin, plotPteeMax);
      kDoLogY=kFALSE;
    }
    if (projoption.EqualTo("yx")) { // 'yx' means ptee on y, mee on x (default analysis)
      han_compare->SetBinsY_forprojOnX(binsPtee_forMee);
      han_compare->SetBinsX_forprojOnY(binsMee_forPtee);
      han_compare->SetPlotRangeMee(plotMeeMin, plotMeeMax);
      han_compare->SetPlotRangePtee(plotPteeMin, plotPteeMax);
      kDoLogY=kTRUE;
    }
//    han_compare->SetPlotRangeRatio(1e-2, 1e0);
//    han_compare->SetDoRatio(kDoRatio, 0.4, kTRUE);
    han_compare->SetPlotRangeRatio(0.1, 50);
    han_compare->SetDoRatio(kDoRatio, 0.3, kTRUE);
    han_compare->Process(LmHandler::kCompare); // not needed if the attached signals were processed by a previous handler.
    
    // open additional spectra without prefilter:
    TString filenameIn = Form("spectra1D-phiVstud-2-%s-%s-%s-data+uncorr+templ+flat+MC.root",sOptCent.Data(),sOptPt.Data(),sOptPref.Data());
    filenameIn.Prepend(Form("%s/", gEnv->GetValue("Canvas.PrintDirectory",".")));
    filenameIn.ReplaceAll(sOptPref.Data(), "NoPref");
    TFile* _fileIn = 0x0;
    TH1D *hData1D=0x0, *hPrompt1D=0x0, *hCon1D=0x0, *hDiffCon1D=0x0;
    
    UInt_t histbits=1;
    TString s3Drange="";
    if (n_bins3DProjRangeY==1 && (bins3DProjRangeY[0]!=0 || bins3DProjRangeY[1]==1)) s3Drange=Form("_ptee%.0fto%.0f",bins3DProjRangeY[0],bins3DProjRangeY[1]);
    if (kDoLogY) { han_compare->SetPlotRangeYMargins(2, 50); }
    else         { han_compare->SetPlotRangeYMargins(0, 1.1); }
    
    for (int i = 0; i <= han_compare->GetMaxBinProj(LmBaseSignal::kProjOnX); ++i){
      if (projoption.EqualTo("xz")) {     // 'xz' means mee on y, phiv on x
        if (sReq.Contains("mee")) break; // dont plot phiv if only mee plot is requested. this is a bit messy.
        
        Double_t yscale = 20./TMath::Pi(); // to be used when x=phiV and not normalized per radian.
        if (han_compare->GetLmSignalI(0)->GetDoNormBinwidth()) yscale = 1;
        if (i==0 || i==han_compare->GetMaxBinProj(LmBaseSignal::kProjOnX)) han_compare->SetPlotRangeY(-0.001/yscale,  0.05/yscale);
        else if (i<=2)                                                    han_compare->SetPlotRangeY(-0.001/yscale,  0.012/yscale);
        else                                                              han_compare->SetPlotRangeY(-0.001/yscale,  0.005/yscale);
        // to see all contributions:
        //han_compare->SetPlotRangeY(0.001/yscale,  10*0.03/yscale); kDoLogY=kTRUE;
      }
      if (projoption.EqualTo("yx")) { // 'yx' means ptee on y, mee on x (default analysis)
        han_compare->SetPlotRangeY(1e-6, 1e3); //1e5?
      }

      // open additional spectra without prefilter:
      TString sMassBin = Form("hSubSig-ptee%.2fto%.2f", binsMee_forPhiV[i], binsMee_forPhiV[i+1]);
      if (kDoPref>0 && sReq.Contains("comp") && i<(int)binsMee_forPhiV.size()-1) {
        _fileIn = LmHelper::SafelyOpenRootfile(filenameIn.Data());
        //_fileIn->ls();
        hData1D   = (TH1D*) LmHelper::GetHistFromTemplateFile(_fileIn, 0, sMassBin, kFALSE);  hData1D   ->SetName("data, no prefilter");
        SetStyles1D(hData1D, LmHelper::GetUniformColor(0), 24);
        hPrompt1D = (TH1D*) LmHelper::GetHistFromTemplateFile(_fileIn, 1, sMassBin, kFALSE);  hPrompt1D ->SetName("MC prompt, no pref.");
        SetStyles1D(hPrompt1D, LmHelper::GetUniformColor(1), 24);
        hCon1D    = (TH1D*) LmHelper::GetHistFromTemplateFile(_fileIn, 2, sMassBin, kFALSE);  hCon1D    ->SetName("MC conv., no pref.");
        SetStyles1D(hCon1D, LmHelper::GetUniformColor(2), 24);
        hDiffCon1D= (TH1D*) LmHelper::GetHistFromTemplateFile(_fileIn, 3, sMassBin, kFALSE);  hDiffCon1D->SetName("MC diff. conv., no pref.");
        SetStyles1D(hDiffCon1D, LmHelper::GetUniformColor(3), 24);
      }
      
      TCanvas cCompare("cCompare", "cCompare");
      han_compare->SetLabels(GetLabelsTemplate(kKineMiddleLeft));
      histbits=LmSignal::kSubSig;//+LmSignal::kUnlike+LmSignal::kBkg;
      han_compare->PrintCompare(histbits, i, LmBaseSignal::kProjOnX, Form("+%s%s",GetAllOptions().Data(), s3Drange.Data()), kDoLegend, kDoLogY, &cCompare);
      if (hData1D   && sReq.Contains("0")) hData1D   ->DrawCopy("p E1 same");
      if (hPrompt1D && sReq.Contains("1")) hPrompt1D ->DrawCopy("p E1 same");
      if (hCon1D    && sReq.Contains("2")) hCon1D    ->DrawCopy("p E1 same");
      if (hDiffCon1D&& sReq.Contains("3")) hDiffCon1D->DrawCopy("p E1 same");
      hData1D = 0x0; hPrompt1D = 0x0; hCon1D = 0x0; hDiffCon1D = 0x0; // should delete properly. memory leak...
      // modify legend:
      if (diffGaScale!=1) {
        TLegend* legend = (TLegend*) cCompare.GetListOfPrimitives()->FindObject("legend");
        TLegendEntry* entry = (TLegendEntry*) legend->GetListOfPrimitives()->At(1);
        if (TString(entry->GetLabel()).Contains("MC sum norm")) entry->SetLabel(Form("MC sum norm. (diff. conv. #times %.1f)", diffGaScale));
      }
      cCompare.Print(cCompare.GetTitle());
      //histbits=LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg;//LmSignal::kUnlike+LmSignal::kUnlikeMix;
      //han_compare->PrintCompare(histbits, i, LmBaseSignal::kProjOnX, Form("+%s%s",GetAllOptions().Data(), s3Drange.Data()), kDoLegend, kDoLogY);
    }
    han_compare->ResetPlotRangeY();
    
    if (projoption.EqualTo("xz")) { // 'xz' means mee on y, phiv on x
      //|__________|   Mee   |__________|
      han_compare->SetPlotRangeY(1e-4, 1e2);
      //han_compare->SetPlotRangeY(1e-5, 1e1); // for ptee 4-6 GeV
      //han_compare->SetPlotRangeY(1e-4, 5);
      //han_compare->SetPlotRangeY(1e-4, 1e5);
      //han_compare->SetPlotRangeY(1e-6, 1e5);
      
      // open additional spectra:
      if (kDoPref>0 && sReq.Contains("comp")) {
        _fileIn = LmHelper::SafelyOpenRootfile(filenameIn.Data());
        //_fileIn->ls();
        hData1D   = (TH1D*) LmHelper::GetHistFromTemplateFile(_fileIn, 0, "hSubSig-mee0.00to3.14", kFALSE);  hData1D  ->SetName("data, no prefilter");
        SetStyles1D(hData1D, LmHelper::GetUniformColor(0), 24);
        hPrompt1D = (TH1D*) LmHelper::GetHistFromTemplateFile(_fileIn, 1, "hSubSig-mee0.00to3.14", kFALSE);  hPrompt1D->SetName("MC prompt, no pref.");
        SetStyles1D(hPrompt1D, LmHelper::GetUniformColor(1), 24);
        hCon1D    = (TH1D*) LmHelper::GetHistFromTemplateFile(_fileIn, 2, "hSubSig-mee0.00to3.14", kFALSE);  hCon1D   ->SetName("MC conv., no pref.");
        SetStyles1D(hCon1D, LmHelper::GetUniformColor(2), 24);
        hDiffCon1D= (TH1D*) LmHelper::GetHistFromTemplateFile(_fileIn, 3, "hSubSig-mee0.00to3.14", kFALSE);  hDiffCon1D->SetName("MC diff. conv., no pref.");
        SetStyles1D(hDiffCon1D, LmHelper::GetUniformColor(3), 24);
      }
      
      for (int i = 0; i <= han_compare->GetMaxBinProj(LmBaseSignal::kProjOnY); ++i){
        TCanvas cCompare("cCompare", "cCompare");
        han_compare->SetLabels(GetLabelsTemplate(kDefault));
        han_compare->PrintCompare(LmSignal::kSubSig, i, LmBaseSignal::kProjOnY, Form("+_phiVstud%s%s",GetAllOptions().Data(), s3Drange.Data()), kDoLegend, kTRUE, &cCompare);
        // this is only ok for one integrated bin:
        if (hData1D   && sReq.Contains("0")) hData1D   ->DrawCopy("p E1 same");
        if (hPrompt1D && sReq.Contains("1")) hPrompt1D ->DrawCopy("p E1 same");
        if (hCon1D    && sReq.Contains("2")) hCon1D    ->DrawCopy("p E1 same");
        if (hDiffCon1D&& sReq.Contains("3")) hDiffCon1D->DrawCopy("p E1 same");
        cCompare.Print(cCompare.GetTitle());
//        han_compare->PrintCompare(LmSignal::kUnlike+LmSignal::kBkg, i, LmBaseSignal::kProjOnY, Form("+_phiVstud%s%s",GetAllOptions().Data(), s3Drange.Data()), kDoLegend);
//        han_compare->PrintCompare(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, i, LmBaseSignal::kProjOnY, Form("+_phiVstud%s%s",GetAllOptions().Data(), s3Drange.Data()), kDoLegend);
      }
      han_compare->ResetPlotRangeY();
    }
    
    
//    running with debug = 6.; ./patrick.exe stud cent pt400 plotMeeMax=0.26 pref2 phiVsub req0456
//    scaling MC templates by 1./1.07 to match data yield in bin at mee=[0.000,0.020].
//    using unfiltered prompt template, scaled by 0.91 to account for random rejection.
//      scaling MC templates by 1./1.33 to match data yield in bin at mee=[0.020,0.040].
//      using unfiltered prompt template, scaled by 0.90 to account for random rejection.
//        scaling MC templates by 1./1.73 to match data yield in bin at mee=[0.040,0.060].
//        using unfiltered prompt template, scaled by 0.90 to account for random rejection.
//          scaling MC templates by 1./2.08 to match data yield in bin at mee=[0.060,0.080].
//          using unfiltered prompt template, scaled by 0.90 to account for random rejection.
//            scaling MC templates by 1./2.69 to match data yield in bin at mee=[0.080,0.100].
//            using unfiltered prompt template, scaled by 0.92 to account for random rejection.
//              scaling MC templates by 1./2.47 to match data yield in bin at mee=[0.100,0.140].
//              using unfiltered prompt template, scaled by 0.91 to account for random rejection.
                
    
////    TH1D* hProj = (TH1D*) han_compare->GetLmSignalI(3)->GetSubSig( han_compare->GetMaxBinProj(LmBaseSignal::kProjOnX), LmBaseSignal::kProjOnX )->GetDatahist();
////    Double_t ytotal = hProj->Integral( 1,20);
//    TH1D* hProj = (TH1D*) han_compare->GetLmSignalI(3)->GetSubSig( 0, LmBaseSignal::kProjOnX )->GetDatahist();
//    //Double_t ytotal = 0.610296; // cent pt400
//    Double_t ytotal = 0.419585; // semi pt400
//    cout << "total yield: " << ytotal << endl;
//    cout << "12-20      : " << hProj->Integral(12,20) << "   % : " << 100. * hProj->Integral(12,20) / ytotal << endl;
//    cout << "13-20      : " << hProj->Integral(13,20) << "   % : " << 100. * hProj->Integral(13,20) / ytotal << endl;
//    cout << "14-20      : " << hProj->Integral(14,20) << "   % : " << 100. * hProj->Integral(14,20) / ytotal << endl;
//    cout << "15-20      : " << hProj->Integral(15,20) << "   % : " << 100. * hProj->Integral(15,20) / ytotal << endl;
//    cout << "16-20      : " << hProj->Integral(16,20) << "   % : " << 100. * hProj->Integral(16,20) / ytotal << endl;
//    cout << "17-20      : " << hProj->Integral(17,20) << "   % : " << 100. * hProj->Integral(17,20) / ytotal << endl;
//    cout << "18-20      : " << hProj->Integral(18,20) << "   % : " << 100. * hProj->Integral(18,20) / ytotal << endl;
//    TCanvas* cProj = new TCanvas("cProj","cProj");
//    hProj->DrawCopy();
//    cProj->Print("cProj.pdf");
    
    //    cent pt400
    //    total yield: 0.610296                 //    0-30 MeV
    //    12-20      : 0.60738    % : 99.5222   //    12-20      : 0.60044    % : 98.3851
    //    13-20      : 0.60582    % : 99.2665   //    13-20      : 0.598894   % : 98.1317
    //    14-20      : 0.603753   % : 98.9279   //    14-20      : 0.596854   % : 97.7975
    //    15-20      : 0.598948   % : 98.1406   //    15-20      : 0.592104   % : 97.0192
    //    16-20      : 0.590038   % : 96.6806   //    16-20      : 0.583276   % : 95.5726 -> less than 5% of all photon conversions remaining.
    //    17-20      : 0.57171    % : 93.6775   //    17-20      : 0.56503    % : 92.583
    //    18-20      : 0.532549   % : 87.2608   //    18-20      : 0.526239   % : 86.2269
    //    semi pt400
    //    total yield: 0.419585                 //    0-30 MeV
    //    12-20      : 0.417463   % : 99.4942   //    12-20      : 0.411589   % : 98.0942
    //    13-20      : 0.416413   % : 99.244    //    13-20      : 0.41056    % : 97.849
    //    14-20      : 0.41475    % : 98.8478   //    14-20      : 0.408921   % : 97.4585
    //    15-20      : 0.411535   % : 98.0815   //    15-20      : 0.405749   % : 96.7025
    //    16-20      : 0.405341   % : 96.6053   //    16-20      : 0.399596   % : 95.2361 -> less than 5% of all photon conversions remaining.
    //    17-20      : 0.392627   % : 93.5752   //    17-20      : 0.387005   % : 92.2351
    //    18-20      : 0.365842   % : 87.1914   //    18-20      : 0.360433   % : 85.9022
    
    // write most important histograms to rootfile:
    TString filename = Form("spectra1D-phiVstud-2-%s-%s-%s-data+uncorr+templ+flat+MC.root",sOptCent.Data(),sOptPt.Data(),sOptPref.Data());
    if (diffGaScale!=1) filename.ReplaceAll(".root", Form("-DiffGa%.2f.root",diffGaScale));
    if (n_bins3DProjRangeY==1 && (bins3DProjRangeY[0]!=0 || bins3DProjRangeY[1]==1))
      filename.ReplaceAll(".root", Form("-ptee%.0fto%.0f.root",bins3DProjRangeY[0],bins3DProjRangeY[1]));
    
    if (writeFile) {
      TFile* _fileOut = new TFile(Form("%s/%s",gEnv->GetValue("Canvas.PrintDirectory","."),filename.Data()), "RECREATE");
      han_compare->Write1DHistSingle(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, LmSignal::kProjOnX); // phiV
      han_compare->Write1DHistSingle(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, LmSignal::kProjOnY); // mee
      _fileOut->Close();
    }
    
    std::cout << "PhiVstudy done :-)" << std::endl;
  }
  LmFileManager::Instance()->Clear();
  mgrVec.clear();
  bkgVec.clear();
  sigVec.clear();
  mgrVec_inputs.clear();
  return 0;
} // PhiVstudy


//_______________________________________________________________________________________________
int Analysis()
{
  TBenchmark* bench = new TBenchmark();
  
  std::vector<LmManager*>     mgrVec; // works when using pointers (they survive after the for-loop). otherwise fancy errors.
  std::vector<LmBackground*>  bkgVec;
  std::vector<LmSignal*>      sigVec;
  
  bench->Start("input_processing");
  TFile *_fTempl3 = 0x0, *_fTempl4 = 0x0, *_fTempl5 = 0x0, *_fTempl5_noPref = 0x0;
  TH3D *hSig3=0x0, *hCon3=0x0, *hULS3=0x0, *hLS3=0x0;
  TH3D *hSigNoPF=0x0, *hSig=0x0, *hCon=0x0, *hULS=0x0, *hLS=0x0, *hDiffGa=0x0, *hDiffGa_LS=0x0, *hNorm=0x0;
  if (kDoPhiV>=LmManager::kTemplUnsub) { // if templates are needed
    //_fTempl3 = LmHelper::SafelyOpenRootfile(Form("./input/PbPb/templates/spectra3D-3-%s-%s-MCall+prompt+conv+noConv.root",sOptCent.Data(),sOptPt.Data()));
    //hSig3 = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl3, 1, "hUnlike");  hSig3->SetName("hSig"); // file 3 prompt
    //hCon3 = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl3, 2, "hUnlike");  hCon3->SetName("hCon"); // file 3 conversions
    //hULS3 = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl3, 3, "hUnlike");  hULS3->SetName("hULS"); // file 3 ULS+LS (key 0=all, 3=noConv) w/ paircuts
    //hLS3  = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl3, 3, "hBkg");     hLS3->SetName("hLS");   // file 3 ULS+LS (key 0=all, 3=noConv) w/ paircuts
    _fTempl5_noPref = LmHelper::SafelyOpenRootfile(Form("./input/PbPb/templates/spectra3D-5-%s-%s-NoPref-MCall+prompt+conv+oneGa+diffGa+hadrCont.root",sOptCent.Data(),sOptPt.Data()));
    hSigNoPF = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5_noPref, 1, "hUnlike");  hSigNoPF->SetName("hSigNoPF");  // file 5 prompt, no prefilter
    _fTempl5 = LmHelper::SafelyOpenRootfile(Form("./input/PbPb/templates/spectra3D-5-%s-%s-%s-MCall+prompt+conv+oneGa+diffGa+hadrCont.root",sOptCent.Data(),sOptPt.Data(),sOptPref.Data()));
    hSig       = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5, 1, "hUnlike");  hSig->SetName((kDoPref>0?"hSigPF":"hSig"));  // file 5 prompt
    hCon       = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5, 2, "hUnlike");  hCon->SetName("hCon");                // file 5 conversions
    hDiffGa    = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5, 4, "hUnlike");  hDiffGa->SetName("hDiffGamma");       // file 5 diff gamma ULS
    hDiffGa_LS = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5, 4, "hBkg");     hDiffGa_LS->SetName("hDiffGamma_LS"); // file 5 diff gamma LS
    hDiffGa->Add(hDiffGa_LS, -1); // diff gamma subtracted
    hNorm = (TH3D*) hSig->Clone("hNorm");
    hNorm->Add(hDiffGa);
    hNorm->Add(hCon);
  }
  
  
  // Add all configs to LmFileManager for efficient file handling
  for (int ic=0; ic<n_config; ic++) {
    LmFileManager::Instance()->AddConfig( cconfig[ic] );
  }
  for (int ic=0; ic<n_config; ic++) 
  {
    LmManager* mgr = new LmManager(const_cast<char*>(cconfig[ic].Data())); // TODO: input style to be optimized
    // set all kinds of configuration for the manager
    if (cconfig[ic].Contains("-268") || cconfig[ic].Contains("-272") || cconfig[ic].Contains("-279") || cconfig[ic].Contains("-311"))
      //mgr->SetInputhistAndDim(const_cast<char*>((inputhist.Strip(TString::kLeading, 'p')).Data()), inputdim);
      mgr->SetInputhistAndDim("InvMass_PairPt_PhivPair", 3);
    else if (cconfig[ic].Contains("data_4D") || cconfig[ic].Contains("MC_4D"))
      mgr->SetInputhistAndDim("M_Pt_PhivPair_OpeningAngle", 4);
    else
      mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
    mgr->SetProjOption(projoption);
    mgr->SetEnableEffiCorr(kDoEffiCorr);
//    if (ic<=1) {
//      mgr->SetEnableExclusionCutZ(0);
//    }
//    else if (ic<=3) {
//      //mgr->SetCutValPhiV(3./4.*TMath::Pi());
//      //mgr->SetCutValMee(0.1);
//      mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
//      mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
//      mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
//      mgr->SetExclusionZTemplates(hSig3);
//    }
//    else if (ic<=5) {
//      mgr->Set3DExclusionZbelow(3, cutPhiVbelow3);
//      mgr->Set3DExclusionZabove(3, cutPhiVabove3);
//      mgr->Set3DExclusionEdgesX(3, cutEdgesMee3);
//      mgr->SetExclusionZTemplates(hSig3);
//    }
//    else
    {
      mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
      mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
      mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
      mgr->SetTemplateNormRegionMin(n_cutPhiVbelow, cutPhiVbelow); // only needed for some template types.
      mgr->SetTemplateNormRegionMax(n_cutPhiVabove, cutPhiVabove); // only needed for some template types.
      // use individual phiV cut settings:
      if ((int)phiVtype.size()>ic) kDoPhiV = phiVtype.at(ic);
      if (kDoPhiV==LmManager::kTemplSub)   mgr->SetExclusionZTemplates(hSigNoPF, 0x0, LmManager::kTemplSub  , hSig, hNorm); // special case implemented for phiV-study, check LmManager::CorrectForExclusionCutIn2D().
      if (kDoPhiV==LmManager::kTemplConv)  mgr->SetExclusionZTemplates(hCon    , 0x0, LmManager::kTemplConv , hSig, hNorm);
      if (kDoPhiV==LmManager::kTemplUnsub) {
        if (hULS && hLS)                   mgr->SetExclusionZTemplates(hULS    , hLS     , LmManager::kTemplUnsub, hSig, hNorm);
        else                               mgr->SetExclusionZTemplates(hSigNoPF, hSigNoPF, LmManager::kTemplUnsub, hSig, hNorm); // workaround since ULS and LS are not available w/o paircuts.
      }
      mgr->SetEnableExclusionCutZ(kDoPhiV); // to be able to change or deactivate the cut without changing the code above.
    }
    


    mgr->Set3DProjRangeY(binsPtee_forMee.at(0), binsPtee_forMee.back()); // "back" gives last element.
    mgr->SetProjRange(thetaEEmin, TMath::Pi(), 3); // axis 3 = dimension 4 = opening angle.
    mgr->SetThetaEEmin(thetaEEmin);
    mgr->SetRebinning2D(n_mee_bin, mee_bin, n_ptee_bin_phiv, ptee_bin_phiv);
    //mgr->SetEnableRebinning(kFALSE); // use this to disable or just comment out the setter above...
    mgr->Process();
    
    mgrVec.push_back(mgr);
    //mgr->SetPlotRangeZ(0.,0.4);
    //mgr->Print2DEffi();
    //mgr->Print2DUnlike();
    
    
    LmBackground* bkg_Hybrid = new LmBackground(*(mgrVec.at(ic)));
//    bkg_Hybrid->SetUseRfactor(kFALSE); // using Rfactor somehow messes up the phiV correction in LS.
    bkg_Hybrid->Process(LmBackground::kHybrid);
    bkgVec.push_back(bkg_Hybrid);
    
    LmSignal* sig0_Std = new LmSignal(*(mgrVec.at(ic)), *(bkgVec.at(ic))); // will take manager name (from caption[]), if no name is given.
    //sig00_Std->SetDoSubtraction(kFALSE);
    sig0_Std->SetDoSignifRaw(kDoSignifRaw);
    sig0_Std->SetDoNormBinwidth(kDoNormBinwidth);
    sig0_Std->SetDoNormNevents(kDoNormNevents);
    sig0_Std->Process(LmSignal::kStd);
    sigVec.push_back(sig0_Std);
    
  } // end config loop
  cout << "__________ DONE WITH SINGLE INPUT PROCESSING __________" << endl;
  bench->Show("input_processing");
  
  
  
  //gSystem->Exec("echo sleep; sleep 10;");
  
  
  
  // better use main arguments to overwrite the default...
  plotMeeMax  = 0.5;//1.5;//3.3;
  //plotPteeMax = 4.0;
  
  
  // handler array needed for later...
  std::vector<LmHandler*>     hanVec;
  
  bench->Start("handler_processing");
  
  Bool_t doCombine=kTRUE;
  UInt_t han_max = (doCombine)?(sigVec.size()/2):(sigVec.size());
  // handlers to combine ++ and -- field
  for (unsigned int ihan=0; ihan<han_max; ihan++) 
  {
    LmHandler* han_i = new LmHandler();
    if (doCombine) {
      han_i->AttachSignal( *(sigVec[ihan*2  ]) );
      han_i->AttachSignal( *(sigVec[ihan*2+1]) );
    } else {
      han_i->AttachSignal( *(sigVec[ihan]) );
    }
    han_i->SetBinsPtee_forprojMee(binsPtee_forMee);
    han_i->SetBinsMee_forprojPtee(binsMee_forPtee);
    han_i->SetPlotRangeMee(plotMeeMin, plotMeeMax);
    han_i->SetPlotRangePtee(plotPteeMin, plotPteeMax);
    han_i->SetConfidenceLevel(confLevel);
//    if (ihan==1) han_i->SetConfidenceLevel(0.84); // ____________________ <--- HARDCODE !!! ____________________
    han_i->SetDoConfidenceLevel(kDoConfLevel);
    if (doCombine) {
      han_i->Process(LmHandler::kCompare);
      han_i->Process(LmHandler::kCombine);
    } else {
      han_i->Process(LmHandler::kStd);
    }
    han_i->SetPlotRangeY(0.8, 1.1);
//    for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
//      han_i->PrintCompareSigBkg_Mee(i, Form("han%d_SigBkg_Mee_bin%d.pdf", ihan, i));
//      han_i->PrintCompareRfactor_Mee(i, kTRUE, Form("han%d_Rfactor_Mee_bin%d.pdf", ihan, i));
//    }
//    han_i->PrintCompareRfactor_Mee(binsPtee_forMee.size()-1, kTRUE, Form("han%d_Rfactor_Mee_bin%d.pdf", ihan, (int)binsPtee_forMee.size()-1));
    hanVec.push_back(han_i);
  }
  
  bench->Show("handler_processing");
  
  
  LmCocktail* cockt00 = 0x0;
  if (kDoCocktail) {
    // cocktail managers (organize input)
    // for resonances
    LmCocktailMan* cocktmanReso = new LmCocktailMan();
    cocktmanReso->SetInputfiles(const_cast<char*>(cocktail_files[which_cockt_files].Data()));
    cocktmanReso->SetInputhistAndDim(const_cast<char*>(cocktail_histograms[which_cockt_hists].Data()), 2); // 2D
    cocktmanReso->SetUndoBinwidthNormalizationMee();
    cocktmanReso->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
    cocktmanReso->Process(LmCocktailMan::kResonances);
    // for heavy flavours
    LmCocktailMan* cocktmanHF = new LmCocktailMan();
    cocktmanHF->SetInputfiles(const_cast<char*>(heavyfl_files[which_heavyfl_files].Data()));
    cocktmanHF->SetInputhistAndDim(const_cast<char*>(heavyfl_histograms[which_heavyfl_hists].Data()), 2); // 2D
    cocktmanHF->SetHistForNeventsHF(const_cast<char*>(heavyfl_hist_Nevents[which_heavyfl_hists].Data()));
    cocktmanHF->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
    cocktmanHF->Process(LmCocktailMan::kHeavyFl);
    // for virtual photons
    // (not available yet)
    
    // cocktail (handles the cocktail spectra)
    Int_t collsystem = -1;
    if (which_cockt_files==0) collsystem = LmCocktail::kPbPb_0010_276;
    if (which_cockt_files==1) collsystem = LmCocktail::kPbPb_2050_276;
    if (which_cockt_files==2) collsystem = LmCocktail::kPbPb_1050_276;
    cockt00 = new LmCocktail(collsystem);
    cockt00->AttachManager( *cocktmanReso );
    cockt00->AttachManager( *cocktmanHF );
    //  cockt00->SetCrosssection_Event(); // cross sections and ncolls should instead be specified in LmCocktail constructor.
    //  cockt00->SetCrosssection_pp();
    //  cockt00->SetNcollCharm();
    cockt00->Process(); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...
    
    // only needed if cocktail shall be projected and plotted stand-alone:
    cockt00->SetBinsPtee_forprojMee(binsPtee_forMee);
    cockt00->SetBinsMee_forprojPtee(binsMee_forPtee);
    cockt00->MakeSpectra1D(); // do projections according to attached binning.
    for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
      //cockt00->PrintCocktail_Mee(i, Form("hCocktailMee_bin%d.pdf", i));
    }
  }
  
  
  LmHandler* han_compare = new LmHandler(LmHandler::kCompare);
  // attach signals to compare handler. they may already be processed or not.
  for (unsigned int i=0; i<hanVec.size(); i++) {
    han_compare->AttachSignal(*(hanVec.at(i)->GetLmSigCombined()), hanVec.at(i)->GetLmSigCombined()->GetName());
  }
  han_compare->SetBinsPtee_forprojMee(binsPtee_forMee);
  han_compare->SetBinsMee_forprojPtee(binsMee_forPtee);
  han_compare->SetPlotRangeMee(plotMeeMin, plotMeeMax);
  han_compare->SetPlotRangePtee(plotPteeMin, plotPteeMax);
  han_compare->SetPlotRangeRatio(0.01, 1.99);
  han_compare->SetDoRatio(kDoRatio, 0.3);
  han_compare->SetConfidenceLevel(confLevel);
  han_compare->SetDoConfidenceLevel(kDoConfLevel);
//  han_compare->Process(LmHandler::kCompare); // not needed if the attached signals were processed by a previous handler.
  
  if (kDoCocktail) {
    han_compare->SetDivideOption("0");
    han_compare->SetCocktail(cockt00); // attach complete cocktail to handler. call cockt00->Process() before!
    //han_compare->SetDrawStyleCocktail("hist c"); // default is "hist"
    han_compare->Process(LmHandler::kCocktail); // create projections of cocktail spectra in the projection binning of the handler. they are stored in each LmCocktailPart.
  }
  else {
    han_compare->SetDivideOption("b");
  }
  LmHelper::Info(Form("main.cpp: handler '%s' uses divide option '%s'", han_compare->GetName(), han_compare->GetDivideOption()));
  
  Bool_t kDoLegend=kTRUE;
  
  
  Printf("|__________|   Plot Mee   |__________|");
  //han_compare->SetPlotRangeY(1e-4, 5);
//  han_compare->SetPlotRangeY(1e-4, 1e5);
  han_compare->SetPlotRangeY(1e-6, 1e5);
  for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
    han_compare->PrintCompare(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, i, LmBaseSignal::kProjOnMee, Form("+%s",GetAllOptions().Data()));
    han_compare->PrintCompareSig_Mee(i, kDoLegend, Form("+%s",GetAllOptions().Data()));
    if (!kDoCocktail) {
//      han_compare->PrintCompareSoverB_Mee(i, kDoLegend, Form("+%s",GetAllOptions().Data()));
//      han_compare->PrintCompareSignif_Mee(i, kDoLegend, Form("+%s",GetAllOptions().Data()));
////      han_compare->PrintCompareSigBkg_Mee(i, kDoLegend, Form("+%s",GetAllOptions().Data()));
    }
  }
  han_compare->ResetPlotRangeY();
  
  
  Printf("|__________|   Plot Ptee   |__________|");
  if (kDoEffiCorr) han_compare->SetPlotRangeY(5e-5, 1e+1); // with effi corr
  else             han_compare->SetPlotRangeY(5e-6, 1e+0);
  for (unsigned int i = 0; i < binsMee_forPtee.size(); ++i){
//    han_compare->PrintCompareSig_Ptee(i, kDoLegend, Form("+%s",GetAllOptions().Data()));
//    if (!kDoCocktail) {
//      han_compare->PrintCompareSoverB_Ptee(i, kDoLegend, Form("+%s",GetAllOptions().Data()));
//      han_compare->PrintCompareSignif_Ptee(i, kDoLegend, Form("+%s",GetAllOptions().Data()));
//      han_compare->PrintCompareSigBkg_Ptee(i, kDoLegend, Form("+%s",GetAllOptions().Data()));
//    }
  }
  han_compare->ResetPlotRangeY();
  
  
  Printf("|__________|   Plot correlations   |__________|");
  Bool_t separatePlots=kTRUE;
  TCanvas c1; c1.SetLogx(); c1.SetLogy();
  TH2D* haxis = new TH2D("haxis","haxis", 1000,3e-5,3e-2, 1000,1e-1,1e2);
  haxis->Draw(); // DrawCopy() causes a segfault with newer root (seen by Carsten).
  han_compare->SetPlotRangeY(1e-7, 1e-0);
  Int_t projOnAxis=LmBaseSignal::kProjOnX;
  for (int i = 0; i <= han_compare->GetMaxBinProj(projOnAxis); ++i){
//    han_compare->PrintCompare(LmSignal::kSubSig, i, projOnAxis, Form("+%s",GetAllOptions().Data())); // printing the same projections of SubSig is needed for correct legend colors in correlation plot.
//    han_compare->PrintCorrelation(LmSignal::kSoverB, LmSignal::kSignif, i, projOnAxis, Form("+%s",GetAllOptions().Data()), kDoLegend, separatePlots, &c1);
  }
  
  
  Bool_t doFitting=kFALSE;
  if (doFitting)
  {
    
    cout << "__________ __________ FITTING __________ __________" << endl;
    cout << "^^^^^^^^^^ ^^^^^^^^^^ ^^^^^^^ ^^^^^^^^^^ ^^^^^^^^^^" << endl;
    
    const UInt_t n_bins = binsPtee_forMee.size();
    
    for (unsigned int i_bin = 0; i_bin < n_bins; ++i_bin)
    {
      
      // datapoints
      TH1D* hData = han_compare->GetLmSignalI(0)->GetSubSig( i_bin, LmBaseSignal::kProjOnMee )->GetDatahist();
      hData->SetTitle("data, unfiltered");
      hData->SetAxisRange(plotMeeMin, plotMeeMax-LmHelper::kSmallDelta, "X");
      // charm
      TH1D* hCharm00  = cockt00->GetComponent1D( LmCocktailPart::kCharm, i_bin, LmBaseSignal::kProjOnMee );
      hCharm00->SetTitle("QM '14");
      //    TH1D* hCharm01  = cockt01->GetComponent1D( LmCocktailPart::kCharm, i_bin, LmBaseSignal::kProjOnMee );
      //    hCharm01->SetTitle("Perugia2011");
      //    TH1D* hCharm02  = cockt02->GetComponent1D( LmCocktailPart::kCharm, i_bin, LmBaseSignal::kProjOnMee );
      //    hCharm02->SetTitle("PowhegPerugia2011");
      // cocktail sum w/o charm
      TH1D* hCocktSum = cockt00->GetSum1D( i_bin, LmBaseSignal::kProjOnMee );
      TH1D* hCockt_wo_charm = (TH1D*) hCocktSum->Clone("hCockt_wo_charm");
      hCockt_wo_charm->SetTitle("QM '14");
      hCockt_wo_charm->Add(hCharm00, -1.);
      // photons
      TH1D* hGamma    = cockt00->GetComponent1D( LmCocktailPart::kOmega, i_bin, LmBaseSignal::kProjOnMee );
      hGamma->SetTitle("omega_as_gamma");
      
      
      //////// CHARM FIT. //////////
      
      //    LmFitter* fitter = new LmFitter();
      //    fitter->SetDatahist( hData );
      //    fitter->AttachFitTemplateA( hCockt_wo_charm );
      //    fitter->AttachFitTemplateB( hCharm00 );
      //    
      //    // Configure the fit with default options. May be done or modified manually if desired...
      //    fitter->PrepareFitCharm(1.2, 2.5);
      //    fitter->Process(); // Type may be left empty if 'PrepareFit...()' was called before. // LmFitter::kTwoTempl
      //    fitter->PrintFitStatus();
      //    fitter->PrintBestFit(    Form("cLmFitter-pPb-charm-Mee_bin%d-best.pdf", i_bin));
      //    fitter->PrintCompareFits(Form("cLmFitter-pPb-charm-Mee_bin%d-compare.pdf", i_bin));
      
      //////// VIRTUAL PHOTON FIT. NORMALIZATION DOESNT WORK WITH PREFILTERED SPECTRA! //////////
      
      LmFitter* fitter = new LmFitter();
      hData->SetAxisRange(0., 0.5-LmHelper::kSmallDelta, "X");
      fitter->SetDatahist( hData );
      fitter->AttachFitTemplateA( hCockt_wo_charm );
      fitter->AttachFitTemplateB( hGamma );
      fitter->AttachFitTemplateC( hCharm00 );
      
      // normalization at very low mass. determine par[1] by fixing par[0] to half.
      //fitter->PrepareFitVirtPhot_Normalization(0.06, 0.15); // norm. range for PREfiltered spectra! // should include min 2 bins
      fitter->PrepareFitVirtPhot_Normalization(0., 0.06); // norm. range for UNfiltered spectra! // should include min 2 bins
      fitter->Process(); // Type may be left empty if 'PrepareFit...()' was called before. // LmFitter::kThreeTempl_OneNorm_PlusBaseline
      fitter->PrintFitStatus();
      fitter->PrintBestFit(    Form("cLmFitter-PbPb-Mee_bin%d-best-1norm.pdf", i_bin));
      
      // extract virt. photon fraction. determine par[0] by fixing par[1].
      fitter->PrepareFitVirtPhot_Extraction(0.15, 0.5);
      fitter->Process(); // Type may be left empty if 'PrepareFit...()' was called before. // LmFitter::kThreeTempl_OneNorm_PlusBaseline
      fitter->PrintFitStatus();
      fitter->PrintBestFit(    Form("cLmFitter-PbPb-Mee_bin%d-best-2extract.pdf", i_bin));
      //fitter->PrintCompareFits(Form("cLmFitter-PbPb-Mee_bin%d-compare-2extract.pdf", i_bin));
    }
    
  } // doFitting 
  
  //
  // write most important histograms to rootfiles:
  //
  // add bits of histograms you want to store: LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg+LmSignal::kSoverB+LmSignal::kSignif
  // to store all of them, you can also use LmSignal::kMAXhist-1
  //
//  const Char_t* filename = "spectra1D_Mee.root";
//  TFile* _fileOut = new TFile(filename, "RECREATE");
//  //  han_compare->SetRootfile(_fileOut);
//  han_compare->SetSimpleHistnames(kTRUE); // use option kTRUE for short histogram names in rootfile or kFALSE for long, more informative histogram names.
//  // for combine handler:
//  // hanCombine->Write1DHistCombined(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg+LmSignal::kSoverB+LmSignal::kSignif, LmSignal::kProjOnMee);
//  // hanCombine->Write1DHistSingle(LmSignal::kRfactor, LmSignal::kProjOnMee);
//  // for compare handler:
//  han_compare->Write1DHistSingle(LmSignal::kSubSig+LmSignal::kSoverB+LmSignal::kSignif, LmSignal::kProjOnMee);
//  //han_compare->Write1DHistSingle(LmSignal::kRfactor, LmSignal::kProjOnMee); // kRfactor only if it is not made of combined signals!
//  _fileOut->Close();
  
  
  std::cout << "main.cpp done :-)" << std::endl;
  LmFileManager::Instance()->Clear();
  mgrVec.clear();
  bkgVec.clear();
  sigVec.clear();
  return 0;
}


//_______________________________________________________________________________________________
int Misc()
{
  TString hnames  = "ITSnClsS:ITSchi2:NclsSFracITS";
  TFile*  _file2  = LmHelper::SafelyOpenRootfile("./input/PbPb/data_4D/LMEEoutput-ESD255-2low.root");
  TFile*  _fileIn = LmHelper::SafelyOpenRootfile("./input/PbPb/MC/bothTasks-ITShists-cent/LMEEoutput-1full.root");
  
  int i=0;
  TList*  llists[20];
  llists[i] = LmHelper::GetList(_file2,  "reichelt_LMEEPbPb2011_out/cut16_SPDorSDD14_PID16_pt400/Track_ev1+");  llists[i]->SetName("e+/- PID in data");  i++;
  //  llists[i] = LmHelper::GetList(_file2,  "reichelt_LMEEPbPb2011_out/cut16_SPDorSDD14_PID16_pt400/Track_ev1-");  llists[i]->SetName("e- in data");  i++;
  llists[i] = LmHelper::GetList(_fileIn, "reichelt_LMEEPbPb2011_out/MC_cut16_SPDorSDD14_PID16_pt400/Track_ev1+");  llists[i]->SetName("e+/- PID in MC");  i++;
  //  llists[i] = LmHelper::GetList(_fileIn, "reichelt_LMEEPbPb2011_out/MC_cut16_SPDorSDD14_PID16_pt400/Track_ev1-");  llists[i]->SetName("e- in MC");  i++;
  llists[i] = LmHelper::GetList(_fileIn, "reichelt_supportHistos");  llists[i]->SetName("true e+/-, mother direct");  i++;
  llists[i] = LmHelper::GetList(_fileIn, "reichelt_LMEEPbPb2011_out/MC_cut16_SPDorSDD14_PID16_pt400/Track_Legs_MCpair_sameMother");  llists[i]->SetName("same Mother");  i++;
  llists[i] = LmHelper::GetList(_fileIn, "reichelt_LMEEPbPb2011_out/MC_cut16_SPDorSDD14_PID16_pt400/Track_Legs_MCpair_diffMother");  llists[i]->SetName("diff Mother");  i++;
  llists[i] = LmHelper::GetList(_fileIn, "reichelt_LMEEPbPb2011_out/MC_cut16_SPDorSDD14_PID16_pt400/Track_Legs_MCpair_sameGamma");   llists[i]->SetName("same Gamma");  i++;
  const Int_t nlists = i;
  
  TList*  lhists[nlists];
  for (Int_t li=0; li<nlists; li++) {
    lhists[li] = LmHelper::SelectHistosList(llists[li], hnames.Data());
  }  
  
  const Int_t nhists = lhists[0]->GetEntries();
  TH1 *hists[nlists][nhists];
  
  Int_t nrebin=1;
  TCanvas c0[nhists];
  TLegend* leg0=0x0;
  for (Int_t hi=0; hi<nhists; hi++) {
    c0[hi].cd();
    if (hi==0 || hi==2) nrebin=3;
    else                nrebin=1;
    
    for (Int_t li=0; li<nlists; li++) {
      hists[li][hi] = (TH1*) lhists[li]->At(hi);
      hists[li][hi]->SetLineColor( LmHelper::GetUniformColor(li, nlists) );
      hists[li][hi]->SetLineWidth( 2 );
      if (li==2) hists[li][hi]->SetLineWidth( 4 );
      hists[li][hi]->SetTitle( TString(lhists[li]->GetName()).ReplaceAll("_out","").Data() );
      hists[li][hi]->RebinX(nrebin);
      
      if (li==0) {
        hists[li][hi]->SetAxisRange(1e3, 1e8, "Y"); // for log
        //hists[li][hi]->SetAxisRange(0, 2.5e7, "Y"); // for lin
        hists[li][hi]->DrawCopy();
        //hists[li][hi]->DrawNormalized();
      }
      else {
        hists[li][hi]->DrawCopy("same");
        //hists[li][hi]->DrawNormalized("same");
      }
    }
    
    leg0 = c0[hi].BuildLegend();
    leg0->SetFillStyle(0);
    c0[hi].SetLogy();
    c0[hi].Print(Form("c0_%s-log-unnorm.pdf", hists[0][hi]->GetName()));
    //    c0[hi].SetLogy(0);
    //    c0[hi].Print(Form("c0_%s-lin-unnorm.pdf", hists[0][hi]->GetName()));
  }
  
  std::cout << "Misc done :-)" << std::endl;
  return 0;
}

//_______________________________________________________________________________________________
int MakePtEtaElectron()
{
  LmHelper lmHelper; // sets global styles etc.
  TFile* _fCharm = LmHelper::SafelyOpenRootfile("./input/PbPb/cocktail/charm-04-PbPb-kPythiaPerugia11_pp2760GeV-rndmPhi.root");
  TH2D* hPtEtaElectron = (TH2D*) LmHelper::GetList(_fCharm, "lowee")->FindObject("hPtEtaElectron");
  
  Double_t p_bin[] = { 0., 0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.5, 3., 4., 6., 10.};
  Int_t n_p_bin = sizeof(p_bin)/sizeof(*p_bin) -1;
  
  LmRebinner* rebinner = new LmRebinner();
  rebinner->SetRebinningX(n_p_bin, p_bin);
  rebinner->Rebin2DHistogram(*hPtEtaElectron);
  
  for (int i=0; i < hPtEtaElectron->GetNbinsX()*hPtEtaElectron->GetNbinsY(); ++i) {
    hPtEtaElectron->SetBinError(i, TMath::Sqrt(hPtEtaElectron->GetBinContent(i)));
  }
  
  LmHelper::PrintHistogram(hPtEtaElectron, "cPtEtaElectron.pdf", "colz");
  
  //
  // Slices: (from Resolution/MakeResolutionArray.cxx)
  //
  TObjArray *histArr = new TObjArray();
  histArr->SetName("PtEtaElectronArr");
  histArr->SetOwner(kTRUE);
  histArr->Add(hPtEtaElectron);
  
  cout << "fill array: " << histArr->GetName() << flush;
  Int_t nbinsx = hPtEtaElectron->GetXaxis()->GetNbins();
  for (Int_t bini=1; bini<=nbinsx; bini++)
  {
    TString newname = Form("bin%d", bini);
    TH1D* hSlice = new TH1D(*((TH1D*)hPtEtaElectron->ProjectionY(newname.Data(), bini, bini, "e")));
    hSlice->SetMarkerStyle(20);
    histArr->Add(hSlice);
  }
  cout << "   ... done. Number of entries: " << histArr->GetLast() << endl;
  
  TFile* fOut = new TFile("hPtEtaElectron.root", "RECREATE");
  histArr->Write(histArr->GetName(),TObject::kSingleKey);
  fOut->Close();
  
  std::cout << "MakePtEtaElectron done :-)" << std::endl;
  return 0;
}


//_______________________________________________________________________________________________
int DrawResolution()
{
  InitOptions();
  LmHelper lmHelper; // sets global styles etc.
  TFile* _fReso=0x0;
  if (kDoSemi) _fReso = LmHelper::SafelyOpenRootfile("../Resolution/output/resolution_PbPb2011_1050_deltaXvsP.root");
  else         _fReso = LmHelper::SafelyOpenRootfile("../Resolution/output/resolution_PbPb2011_0010_deltaXvsP.root");
  TH2D* hPRes       = (TH2D*) ((TObjArray*)_fReso->Get("RelPResArr"))->At(0);
  TH2D* hThetaRes   = (TH2D*) ((TObjArray*)_fReso->Get("ThetaResArr"))->At(0);
  TH2D* hPhiEleRes  = (TH2D*) ((TObjArray*)_fReso->Get("PhiEleResArr"))->At(0);
  //TH2D* hPhiPosRes  = (TH2D*) ((TObjArray*)_fReso->Get("PhiPosResArr"))->At(0);
  // note for the axis labels that the histograms are not flipped at this point!
  hPRes     ->SetTitle(";#it{p}^{gen} (GeV/#it{c});#it{p}^{meas} / #it{p}^{gen}");
  hThetaRes ->SetTitle(";#it{p}^{gen} (GeV/#it{c});#it{#theta}^{meas} - #it{#theta}^{gen} (rad)");
  hPhiEleRes->SetTitle(";#it{p}^{gen} (GeV/#it{c});#it{#varphi}^{meas} - #it{#varphi}^{gen} (rad)");
  
  const int nPads=3;
  TH2D* histArr[nPads];
  histArr[0] = hPRes;
  histArr[1] = hThetaRes;
  histArr[2] = hPhiEleRes;
//  histArr[3] = hPhiPosRes;
  
  // Set up canvas for summary plot
  Double_t sizeFac   = 1.;
  // with the default margins of 0.14 and 0.06, each large pad has has a relative size of 0.8x0.8 and each small one 0.4x0.4.
  // here we need 3 small pads next to each other plus the margins:
  Double_t canRelWidth   = (nPads*0.4+0.14+0.06);
  Double_t canRelHeight  = (1.*0.4+0.10+0.10);
  Double_t relWidthZaxis = 0.03; // for the color palette
  TCanvas* cResolution = new TCanvas("cResolution", "cResolution", canRelWidth*gStyle->GetCanvasDefW()*sizeFac, canRelHeight*gStyle->GetCanvasDefW()*sizeFac);
  // bottom- and topmargins shall have the same absolute size as in a large figure, so scale them by the relative height of this canvas.
  LmHelper::CreateManyPads(cResolution,nPads,1, 0.1/canRelHeight,0.1/canRelHeight, (0.14-relWidthZaxis)/canRelWidth,(0.06+relWidthZaxis)/canRelWidth);
  Double_t titleSize = gStyle->GetTitleSize()/canRelHeight*1.2;
  Double_t labelSize = gStyle->GetLabelSize()/canRelHeight*1.2;
  Double_t zmin = 1;
  for (int iproj=0; iproj<nPads; iproj++) {
    if (histArr[iproj]==0x0) continue;
    TH2D* hist = histArr[iproj];
    hist->Scale(0.005, "width");
    LmHelper::FlipAxes2DHistogram( *hist );
    //cResolution->cd(iproj+1)->SetLogy();
    cResolution->cd(iproj+1)->SetLogz();
    hist->SetTitleOffset(gStyle->GetTitleOffset("X")/1.2,"X");
    hist->SetTitleOffset(gStyle->GetTitleOffset("Y")/1.4,"Y"); // modified because of additional color axis.
    hist->SetTitleSize(titleSize,"XYZ");
    hist->SetLabelSize(labelSize,"XYZ");
    hist->SetLabelOffset(hist->GetLabelOffset("Y")*2.,"Y");
    hist->SetNdivisions(505,"XY");
    hist->GetXaxis()->CenterTitle();
    hist->GetYaxis()->SetRangeUser(0.,5.); // p_gen range
    // z axis range:
    if (iproj==0) zmin = hist->GetMinimum(1); // get the minimum value larger than 1.
    hist->SetMinimum(zmin);
    if (TString(hist->GetXaxis()->GetTitle()).Contains("#it{p}")) hist->GetXaxis()->SetRangeUser(   0., 1.99);
    if (TString(hist->GetXaxis()->GetTitle()).Contains("theta"))  hist->GetXaxis()->SetRangeUser(-0.39, 0.39);
    if (TString(hist->GetXaxis()->GetTitle()).Contains("phi"))    hist->GetXaxis()->SetRangeUser(-0.39, 0.39);
    if (iproj<nPads-1) hist->DrawCopy("col"); // without z it doesnt draw the color palette.
    else               hist->DrawCopy("colz");
    if (iproj<nPads-1) LmHelper::BuildTLatex(0.8, 0.73, "e^{#minus}, e^{#plus}", "lLabel", 1./canRelHeight*1.2)->DrawClone("same");
    else               LmHelper::BuildTLatex(0.1, 0.73, "e^{#minus}"           , "lLabel", 1./canRelHeight*1.2)->DrawClone("same");
    //cResolution->cd(iproj+1)->RedrawAxis();
  }
  cResolution->Print( Form("%s/cResolution-%s.pdf","./plots",sOptCent.Data()) );
  
  std::cout << "DrawResolution done :-)" << std::endl;
  return 0;
}

//_______________________________________________________________________________________________
int DrawCentrality()
{
  InitOptions();
  LmHelper lmHelper; // sets global styles etc.
  
  TH1F *haxis = new TH1F("haxis",";centrality_{V0M} (%);number of events", 100, 0, 100);
  
  // histograms extracted from $lmee/PlottingFW/input/PbPb/data_4D/cut16-cent-AOD-2pref/LMEEoutput-1full.root
  // and 'semi' file.
  
  TH1F *central = new TH1F("central","", 10, 0, 10);
  central->SetLineWidth(2);
  central->SetLineColor(LmHelper::GetUniformColor(0,2));
  central->SetBinContent(1,1921494);
  central->SetBinContent(2,1938263);
  central->SetBinContent(3,1978677);
  central->SetBinContent(4,1980298);
  central->SetBinContent(5,1976763);
  central->SetBinContent(6,1930616);
  central->SetBinContent(7,1944729);
  central->SetBinContent(8,1927617);
  central->SetBinContent(9,1878925);
  central->SetBinContent(10,1645614);
  central->SetEntries(1.9123e+07);
  
  TH1F *semicent = new TH1F("semicent","", 100, 0, 100);
  semicent->GetXaxis()->SetRangeUser(10,50);
  semicent->SetLineWidth(2);
  semicent->SetLineColor(LmHelper::GetUniformColor(1,2));
  semicent->SetBinContent(11,428833);
  semicent->SetBinContent(12,430105);
  semicent->SetBinContent(13,430268);
  semicent->SetBinContent(14,432018);
  semicent->SetBinContent(15,436675);
  semicent->SetBinContent(16,427960);
  semicent->SetBinContent(17,431477);
  semicent->SetBinContent(18,433048);
  semicent->SetBinContent(19,427082);
  semicent->SetBinContent(20,431604);
  semicent->SetBinContent(21,431795);
  semicent->SetBinContent(22,430950);
  semicent->SetBinContent(23,430154);
  semicent->SetBinContent(24,437976);
  semicent->SetBinContent(25,429399);
  semicent->SetBinContent(26,430513);
  semicent->SetBinContent(27,435721);
  semicent->SetBinContent(28,437467);
  semicent->SetBinContent(29,426332);
  semicent->SetBinContent(30,426685);
  semicent->SetBinContent(31,434845);
  semicent->SetBinContent(32,427837);
  semicent->SetBinContent(33,430014);
  semicent->SetBinContent(34,426833);
  semicent->SetBinContent(35,434191);
  semicent->SetBinContent(36,425501);
  semicent->SetBinContent(37,431630);
  semicent->SetBinContent(38,432312);
  semicent->SetBinContent(39,434358);
  semicent->SetBinContent(40,432505);
  semicent->SetBinContent(41,426233);
  semicent->SetBinContent(42,434774);
  semicent->SetBinContent(43,431509);
  semicent->SetBinContent(44,432657);
  semicent->SetBinContent(45,429112);
  semicent->SetBinContent(46,434981);
  semicent->SetBinContent(47,433384);
  semicent->SetBinContent(48,434402);
  semicent->SetBinContent(49,428865);
  semicent->SetBinContent(50,429936);
  semicent->SetEntries(1.725194e+07);
  
  TCanvas* cCentrality = new TCanvas("cCentrality", "cCentrality");
  
  haxis->SetMaximum(central->GetMaximum()*1.05);
  haxis->Draw("axis");
  central->Draw("same");
  semicent->Draw("same");
  
  cCentrality->Print( Form("%s/cCentrality.pdf","./plots") );
  
  std::cout << "DrawCentrality done :-)" << std::endl;
  return 0;
  
}

