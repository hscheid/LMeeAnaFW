// c++ includes

// ROOT includes
#include "TObjArray.h"
#include "TFile.h"
#include "TCollection.h"
#include "TLine.h"
#include "TLegend.h"
// project includes
#include "LmMultiQA.h"
#include "LmHelper.h"

//_______________________________________________________________________________________________
LmMultiQA::LmMultiQA(LmQA &data, LmQA &mc) :
fData(&data),
fMC(&mc)
{
  // @TODO: there seems to be an issue in the constructor of LmQA, which is implicitly called by the
  // LmMultiQA constructor: warning: deprecated conversion from string constant to ‘char*’
  feta_range_min  = fData->GetEtaRange_min();
  feta_range_max  = fData->GetEtaRange_max();
  fpt_range_min   = fData->GetPtRange_min();
  fpt_range_max   = fData->GetPtRange_max();
  fcentrality_min = fData->GetCentrality_min();
  fcentrality_max = fData->GetCentrality_max();
}

//_______________________________________________________________________________________________
LmMultiQA::~LmMultiQA(){
}


//_______________________________________________________________________________________________
void LmMultiQA::PrintTrackingPrivate(TString filename, TString observable, int type){
  LmHelper::Debug("--LmMultiQA::PrintTrackingPrivate()", 2);
  Int_t rebinFac = 10;
  TH1D* hData = 0x0;
  TH1D* hMC   = 0x0;
  
  switch (type){
    case kEvent: {
      hData = static_cast<TH1D*>((fData->GetHistogram<TH1D>("Event", observable))->Clone(Form("Event%s_data", observable.Data())));
      hMC   = static_cast<TH1D*>((fMC  ->GetHistogram<TH1D>("Event", observable))->Clone(Form("Event%s_MC"  , observable.Data())));
      break;
    }
    
    case kCompare:
    case kAll: {
      hData = static_cast<TH1D*>((fData->GetHistogram<TH1D>("Track_ev1-", observable))->Clone(Form("SumOf%s_data", observable.Data())));
      hData->Add(fData->GetHistogram<TH1D>("Track_ev1+", observable));
      hMC = static_cast<TH1D*>((fMC->GetHistogram<TH1D>("Track_ev1-", observable))->Clone(Form("SumOf%s_MC", observable.Data())));
      hMC->Add(fMC->GetHistogram<TH1D>("Track_ev1+", observable));
      break;
    }
    case kNeg: {
      hData = static_cast<TH1D*>((fData->GetHistogram<TH1D>("Track_ev1-", observable))->Clone(Form("Neg%s_data", observable.Data())));
      hMC   = static_cast<TH1D*>((fMC->GetHistogram<TH1D>("Track_ev1-", observable))->Clone(Form("Neg%s_MC", observable.Data())));
      break;
    }
    case kPos: {
      hData = static_cast<TH1D*>((fData->GetHistogram<TH1D>("Track_ev1+", observable))->Clone(Form("Pos%s_data", observable.Data())));
      hMC   = static_cast<TH1D*>((fMC->GetHistogram<TH1D>("Track_ev1+", observable))->Clone(Form("Pos%s_MC", observable.Data())));
      break;
    }
  }
  
  if(fRebin > 1){
    hData->Rebin(fRebin);
    hMC->Rebin(fRebin); 
  }
 
  hData->SetLineColor(kBlue);
  hData->SetLineWidth(2);
  hMC->SetLineColor(kRed);
  hMC->SetLineWidth(2);
  hData->SetTitle(Form("%s", observable.Data()));
  hMC->SetTitle(Form("%s", observable.Data()));
  
  TString sNorm="";
  if (fDoNormNEntries == 1) {
    sNorm=" norm. to 1";
    hData->Scale(1./hData->Integral());
    hMC->Scale(1./hMC->Integral());
  }
  else if (fDoNormNEvents == 1) {
    sNorm=" per event";
    hData->Scale(1./fData->GetNumberOfEvents());
    hMC->Scale(1./fMC->GetNumberOfEvents());
  }
  
  //Preparation of canvases
  TCanvas* c1 = new TCanvas(observable, observable);
  if (fDoRatio) {
    double bottommargin(0.3);
    c1->Divide(1,2);
    c1->cd(1)->SetPad(0., fRatioPadSize, 1., 1.);  // top pad
    c1->cd(1)->SetBottomMargin(0.001);
    c1->cd(1)->SetTicks();
    c1->cd(2)->SetPad(0., 0., 1., fRatioPadSize);  // bottom pad
    c1->cd(2)->SetTopMargin(0);
    c1->cd(2)->SetBottomMargin(bottommargin); // for x-axis label
    c1->cd(2)->SetTicks();
  }
  
  TLegend leg1(0.35, 0.60, 0.75, 0.80);
  leg1.SetFillStyle(0);
  leg1.SetTextAlign(22); // 20=hcenter, 2=vcenter
  if (TString(fData->GetName()).IsNull()) leg1.AddEntry(hData, Form("data%s",sNorm.Data()), "l");
  else                                    leg1.AddEntry(hData, Form("%s%s",fData->GetName(),sNorm.Data()), "l");
  if (TString(fMC->GetName()).IsNull())   leg1.AddEntry(hMC,   Form("MC%s",sNorm.Data()), "l");
  else                                    leg1.AddEntry(hMC,   Form("%s%s",fMC->GetName(),sNorm.Data()), "l");
  
  hData->SetStats(kFALSE);
  hMC->SetStats(kFALSE);
  SetAxisRanges(hData, observable, c1);
  SetAxisRanges(hMC, observable, c1);
  c1->cd(1);
  hMC->GetYaxis()->SetTitleOffset(1.5);
  hData->GetYaxis()->SetTitleOffset(1.5);
  hData->DrawCopy("");
  hMC->DrawCopy("same");
  
  leg1.DrawClone("same");
  
  //temporary tweak to plot difference of 2 track selections (also turn off normalization above!):
//  TH1D* hDiff = new TH1D(*hMC);
//  hDiff->Add(hData,-1.);
//  hDiff->SetLineColor(kGreen+2);
//  hDiff->DrawCopy("same");
//  hData->DrawCopy("same");
//  Printf("integrals: 1: %.2f, 2: %.2f, 3: %.2f, 2/1: %.2f", hData->GetEntries(), hMC->GetEntries(), hDiff->GetEntries(), hMC->GetEntries()/hData->GetEntries());
  
  // Ratio plots
  if (fDoRatio) {
    TH1D ratio(*hData);
    ratio.Divide(hMC);
    
    ratio.SetStats(kFALSE);
    ratio.SetAxisRange(0.5, 1000.5, "Y");
    ratio.SetTitle("");
    //ratio.GetYaxis()->SetTitle("#frac{data}{MC}");
    ratio.GetYaxis()->SetTitle("Ratio");
    ratio.GetYaxis()->SetTitleOffset(0.5);
    ratio.GetXaxis()->SetTitleOffset(1.3);
    ratio.SetTitleSize(ratio.GetTitleSize()/fRatioPadSize*(1.-fRatioPadSize), "xy");
    ratio.SetLabelSize(ratio.GetLabelSize()/fRatioPadSize*(1.-fRatioPadSize), "xy");
    
    ratio.GetYaxis()->SetNdivisions(4, 5, 0, kTRUE);
    SetAxisRanges(&ratio, observable, c1);
    TLine l1(ratio.GetXaxis()->GetBinLowEdge(ratio.GetXaxis()->GetFirst()), 1., ratio.GetXaxis()->GetBinLowEdge(ratio.GetXaxis()->GetLast()+1), 1.);
    c1->cd(2)->SetLogy();
    c1->cd(2);
    ratio.DrawCopy("hist");
    l1.DrawClone("same");
  }
  
  c1->Print(filename);
  delete c1;
  delete hData;
  delete hMC;
}

