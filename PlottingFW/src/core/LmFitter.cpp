// c++ includes
#include <iostream>
using namespace std;
// ROOT includes
#include "TH1.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TFitResult.h"
#include "TVirtualFitter.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"
// project includes
#include "LmFitter.h"
#include "LmHelper.h"

//_______________________________________________________________________________________________
LmFitter::LmFitter() :
fType(kUndef),
fFcnClass(0x0),
fFcnFit(0x0),
fDatahist(0x0),
fXmin(-1),
fXmax(-1),
fNpar(-1),
//fbFixPar(0),
//fFixParVal(0),
fsFitOpt("I"),
fUseOnlyTemplatePairs(kFALSE),
fIBestFit(0) // must be 0 because of some getters.
{
  /// Default constructor
  fFcnClass = new LmFitFunctions(); // create the user function class.

  fFitTemplateA.clear();
  fFitTemplateB.clear();
  fFitTemplateC.clear();

  ClearVectors(kTRUE);
  CleanupParams();
}

//_______________________________________________________________________________________________
void LmFitter::PrepareFitCharm(Double_t xmin, Double_t xmax)
{
  CleanupParams();
  fType=kTwoTempl;
  SetTemplateNames("Reso", "Charm");
  SetFitOpt("I");
  SetXmin(xmin);
  SetXmax(xmax);
  SetFixPar(0, 1.); // Fix resonance yield.
  SetParNames("normResonances", "normCharm");
}


//_______________________________________________________________________________________________
void LmFitter::PrepareFitVirtPhot_Normalization(Double_t xnormmin, Double_t xnormmax, Bool_t NormToData)
{
  CleanupParams();
  fType=kThreeTempl_OneNorm_PlusBaseline;
  SetTemplateNames("Reso", "Gamma", "Charm");
  SetFitOpt("IQ");

  /// First step, two options:
  /// NormToData: Scale virtual photon and resonance template to data at very low mass.
  /// else:       Scale virtual photon template to have same integral as resonances at very low mass.
  /// Assume we have only one resonance template, but maybe multiple photon templates.
  if (NormToData){
    TH1D* hReso = fFitTemplateA.at(0);
    Double_t yieldReso  = hReso->Integral(hReso->FindBin(xnormmin), hReso->FindBin(xnormmax-LmHelper::kSmallDelta));

    Double_t yieldData = fDatahist->Integral(fDatahist->FindBin(xnormmin), fDatahist->FindBin(xnormmax-LmHelper::kSmallDelta));
    hReso->Scale(yieldData/yieldReso);

    for (unsigned int iB=0; iB<fFitTemplateB.size(); ++iB) {
      TH1D* hGamma = fFitTemplateB.at(iB);
      Double_t yieldGamma = hGamma->Integral(hGamma->FindBin(xnormmin), hGamma->FindBin(xnormmax-LmHelper::kSmallDelta));
      hGamma->Scale(yieldData/yieldGamma);
    }
  }
  else {
    TH1D* hReso = fFitTemplateA.at(0);
    Double_t yieldReso  = hReso->Integral(hReso->FindBin(xnormmin), hReso->FindBin(xnormmax-LmHelper::kSmallDelta));

    for (unsigned int iB=0; iB<fFitTemplateB.size(); ++iB) {
      TH1D* hGamma = fFitTemplateB.at(iB);
      Double_t yieldGamma = hGamma->Integral(hGamma->FindBin(xnormmin), hGamma->FindBin(xnormmax-LmHelper::kSmallDelta));
      hGamma->Scale(yieldReso/yieldGamma);
    }
  }  

  /// Second step:
  /// Prepare for normalization to data at very low mass. Fit range should include min. 2 bins!
  /// Always use first charm template, or deactivate it (see below), the bias should be really small.
  /// Determine par[1] by fixing par[0] to onehalf.
  SetXmin(xnormmin);
  SetXmax(xnormmax);
  //SetFixPar(2, 0.); // deactivate charm
  SetFixPar(2, 1.); // fix charm
  SetParNames("#gamma-frac", "norm reso+#gamma", "norm c#bar{c}");
}


//_______________________________________________________________________________________________
void LmFitter::PrepareFitVirtPhot_Extraction(Double_t xmin, Double_t xmax)

{
  CleanupParams();
  fType=kThreeTempl_OneNorm_PlusBaseline;
  SetTemplateNames("Reso", "Gamma", "Charm"); // not really needed again...
  SetFitOpt("IQ");

  /// Third step:
  /// Prepare for the final fit.
  SetXmin(xmin);
  SetXmax(xmax);
//  Double_t normAB = 1.;
//  SetFixPar(1, normAB); // need the fit parameter result from the first iteration, which is not accessible here because the 'counter' is not running at this time.
  SetFixPar(2, 1.); //fix charm 
  SetParNames("#gamma-frac", "norm reso+#gamma", "norm c#bar{c}");
}


//_______________________________________________________________________________________________
Int_t LmFitter::Process(Int_t type)
{
  if (type==kUndef) {
    if (fType==kUndef) LmHelper::Error("LmFitter::Process(): calling this without 'type' is not allowed without calling 'PrepareFit...()' before.");
  }
  else {
    if (fType==kUndef) fType=type;
    if (fType!=type) LmHelper::Error("LmFitter::Process(): the given 'type' is different from 'PrepareFit...()'. Ignoring new type.");
  }

  // some needed cleanup if Process() is called multiple times:
  if (fFcnFit!=0x0) delete fFcnFit;
  for (unsigned int i=0; i<fvFitFcns.size(); ++i) {
    delete fvFitFcns.at(i);
    delete fvConfidenceGrs.at(i);
  }
  ClearVectors(kFALSE); // kFALSE -> don't clear fvNormAB, which is needed later.

  if (!fDatahist) return -5;

  if (fFitTemplateA.size()<1) return -4;

  if ((type==kTwoTempl) && (fFitTemplateB.size()<1)) return -3;

  const UInt_t nTemplA = fFitTemplateA.size();
  const UInt_t nTemplB = fFitTemplateB.size();
  const UInt_t nTemplC = fFitTemplateC.size();

  UInt_t nfitstmp;

  Double_t fcnXmin = fXmin;
  Double_t fcnXmax = fXmax;
  Int_t npx = 500;
  // to draw function over the full range if desired:
  fcnXmin = 0.;
  fcnXmax = 5.;
  npx = 2000;

  switch (fType) {

    case kOneTempl:
      fNpar=1;
      nfitstmp=nTemplA;
      fFcnFit = new TF1("fFcnFit",fFcnClass,&LmFitFunctions::FcnOneTemplate,fcnXmin,fcnXmax,fNpar,"LmFitFunctions","FcnOneTemplate"); // create TF1 class.
      //When constructing the TF1 class, the name of the function class and of the member function are required only if running in CINT and they are not need in compiled C++ mode.
      fFcnFit->SetParNames(fParNames[0].Data());
      break;

    case kTwoTempl:
      fNpar=2;
      nfitstmp=nTemplA*nTemplB;
      fFcnFit = new TF1("fFcnFit",fFcnClass,&LmFitFunctions::FcnTwoTemplates,fcnXmin,fcnXmax,fNpar,"LmFitFunctions","FcnTwoTemplates"); // create TF1 class.
      fFcnFit->SetParNames(fParNames[0].Data(),fParNames[1].Data());
      break;

    case kThreeTempl:
      fNpar=3;
      nfitstmp=nTemplA*nTemplB*nTemplC;
      fFcnFit = new TF1("fFcnFit",fFcnClass,&LmFitFunctions::FcnThreeTemplates,fcnXmin,fcnXmax,fNpar,"LmFitFunctions","FcnThreeTemplates"); // create TF1 class.
      fFcnFit->SetParNames(fParNames[0].Data(),fParNames[1].Data(),fParNames[2].Data());
      break;

    case kThreeTempl_OneNorm_PlusBaseline:
      fNpar=3;
      nfitstmp=nTemplA*nTemplB*nTemplC;
      fFcnFit = new TF1("fFcnFit",fFcnClass,&LmFitFunctions::FcnThreeTempl_OneNorm_PlusBaseline,fcnXmin,fcnXmax,fNpar,"LmFitFunctions","FcnThreeTempl_OneNorm_PlusBaseline"); // create TF1 class.
      fFcnFit->SetParNames(fParNames[0].Data(),fParNames[1].Data(),fParNames[2].Data());
      break;

    case kTwoTempl_OneNorm:
//      nfitstmp=nTemplA*nTemplB;
//      break;

    default:
      cout << "fType # " << fType << " not supported!" << endl;
      return -2;
      break;
  }


  fFcnFit->SetNpx(npx);
  fFcnFit->SetLineColor(kRed);
  fFcnFit->SetLineWidth(3);

  // initialize the parameters
  for (int i=0; i<fNpar; ++i)
  {
    //if(i==0){
    //  fFcnFit->SetParameter(i, 0.5); // start value
    //  fFcnFit->SetParLimits(i, 0., 1.); // logical limits
    //}
    //else 
      fFcnFit->SetParameter(i, 1.); // start value
      fFcnFit->SetParLimits(i, 0.00001, 1.); // logical limits

    // fix parameters on demand
    if (fbFixPar[i]==kTRUE) fFcnFit->FixParameter(i, fFixParVal[i]);
  }


  // cout << " will perform nFits = " << nfitstmp << endl;

  UInt_t counter=0;

  for (unsigned int iA=0; iA<fFitTemplateA.size(); ++iA)
  {
    for (unsigned int iB=0; iB<TMath::Max(fFitTemplateB.size(),(size_t)1); ++iB) // loop at least until 1 to always enter the loop.
    {
      for (unsigned int iC=0; iC<TMath::Max(fFitTemplateC.size(),(size_t)1); ++iC) // loop at least until 1 to always enter the loop.
      {
        if (fUseOnlyTemplatePairs && (iA != iB || iA != iC || iB != iC)) continue;

        DoOneFit(counter, iA, iB, iC);

        counter++;
      }
    }
  }


  return 0;
}


//_______________________________________________________________________________________________
void LmFitter::DoOneFit(UInt_t counter, UInt_t iA, UInt_t iB, UInt_t iC)
{
  // set the pointers to the active histograms
  fFcnClass->SetTemplateA(fFitTemplateA.at(iA));
  if (iB < fFitTemplateB.size()) fFcnClass->SetTemplateB(fFitTemplateB.at(iB)); // check needed because template may be empty.
  if (iC < fFitTemplateC.size()) fFcnClass->SetTemplateC(fFitTemplateC.at(iC)); // check needed because template may be empty.

  if ((fType==kThreeTempl_OneNorm_PlusBaseline) || fType==kTwoTempl_OneNorm) {
    if (fvNormAB.size()>counter) { // fix the normAB parameter if the normalization fit was already done.
      Double_t normAB = fvNormAB.at(counter);
      fFcnFit->FixParameter(1, normAB);
    }
  }

  TFitResultPtr fitResultPtr; // serves as pointer, use "->", which is overloaded. // needs fit option "S" for everything except fit status.

  // Perform the fit
  fitResultPtr = fDatahist->Fit(fFcnFit, (TString)fsFitOpt+"0", "", fXmin, fXmax); // use fXmin, fXmax to fit only in the function range! (safer than using option "R")
  fitResultPtr = fDatahist->Fit(fFcnFit, (TString)fsFitOpt+"0", "", fXmin, fXmax); // use fXmin, fXmax to fit only in the function range! (safer than using option "R")
  fitResultPtr = fDatahist->Fit(fFcnFit, (TString)fsFitOpt+"0", "", fXmin, fXmax); // use fXmin, fXmax to fit only in the function range! (safer than using option "R")

  // Construct confidence level graph
  const Int_t nBinsInFit = LmHelper::GetNBinsInRange(fFitTemplateA.at(iA), fXmin, fXmax);
  Double_t binCenters[nBinsInFit];
  //Double_t binValues[nBinsInFit] = {0.};
  LmHelper::GetBinCentersInRange(fFitTemplateA.at(iA), fXmin, fXmax, binCenters);

  TGraphErrors* grconfint = new TGraphErrors(nBinsInFit, binCenters, binCenters); // y-values will be overwritten anyhow...
  grconfint->SetTitle("1#sigma conf. interval");
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grconfint, 0.68);
  grconfint->SetLineColor(kRed);
  grconfint->SetFillColor(kRed);
  grconfint->SetFillStyle(LmHelper::GetCompareFillStyle(0));

  // Store fit function and confidence level graph
  //fvFitFcns.push_back( new TF1(*fFcnFit) ); // not correctly working
  fvFitFcns.push_back( (TF1*) fFcnFit->Clone(Form("fitfcn%i",counter)) );
  fvConfidenceGrs.push_back( (TGraphErrors*) grconfint->Clone(Form("confgr%i",counter)) );
  fvWhichA.push_back(iA);
  fvWhichB.push_back(iB);
  fvWhichC.push_back(iC);

  // Store some fit results
  if (fFcnFit->GetNDF()==0) {
    cout << "WARNING: fFcnFit->GetNDF() = " << fFcnFit->GetNDF() << endl;
    cout << "   fFcnFit->GetChisquare() = " << fFcnFit->GetChisquare() << endl;
  }
  fvChi2NDF.push_back(fFcnFit->GetChisquare() / fFcnFit->GetNDF());
  //cout << "fvChi2NDF["<<counter<<"] = " << fvChi2NDF.at(counter) << endl;
  fvFitStatus.push_back(fitResultPtr); // converting the TFitResultPtr to an integer
  if (fvNormAB.size()<=counter) fvNormAB.push_back(fFcnFit->GetParameter(1)); // store this parameter for second fit of virtual photon extraction.

  if (counter==0 || fvChi2NDF.at(counter) < fvChi2NDF.at(fIBestFit)) {
    fIBestFit = counter;
  }
}

//_______________________________________________________________________________________________
void LmFitter::ClearVectors(Bool_t clearNormAB)
{
  fvFitFcns.clear();
  fvConfidenceGrs.clear();
  fvWhichA.clear();
  fvWhichB.clear();
  fvWhichC.clear();
  fvChi2NDF.clear();
  fvFitStatus.clear();
  if (clearNormAB) fvNormAB.clear();
}


//_______________________________________________________________________________________________
void LmFitter::CleanupParams()
{
  for (int i=0; i<9; ++i) {
    fParNames[i]=Form("p%i",i);
    fbFixPar[i]=kFALSE;
  }
}


//_______________________________________________________________________________________________
void LmFitter::PrintBestFit(TString filename)
{
  PrintFitI(fIBestFit, filename);
}


//_______________________________________________________________________________________________
void LmFitter::PrintFitI(UInt_t counter, TString filename)
{
  if (filename.IsNull()) filename.Form("cFit%i.pdf", counter);

  gStyle->SetOptStat(0);
  TCanvas *cFit = new TCanvas("cFit","cFit", 810,0, 580*1.2,600*1.2);
  cFit->cd()->SetLogy();
  //GetDatahist()->GetYaxis()->SetRangeUser(0, GetDatahist()->GetMaximum()*1.5);
  // GetDatahist()->GetYaxis()->UnZoom();
  GetDatahist()->SetMarkerStyle(20);
  GetDatahist()->SetMarkerColor(kBlue+1); //GetDatahist()->GetLineColor()
  GetDatahist()->SetLineColor(kBlue+1);
  GetDatahist()->Draw("axis");

  TLatex* lat = new TLatex(0.2,0.67,"result");
  lat->SetNDC();
  lat->SetTextFont(gStyle->GetTitleFont());
  lat->SetTextSize(gStyle->GetTitleSize()*0.9);

  lat->SetTitle(Form("%s=%.3f, %s=%.3f, %s=%.3f", fParNames[0].Data(), GetNormA_I(counter), fParNames[1].Data(), GetNormB_I(counter), fParNames[2].Data(), GetNormC_I(counter)));
  // overwrite the label for special types
  if ((fType==kThreeTempl_OneNorm_PlusBaseline) || fType==kTwoTempl_OneNorm) {
    lat->SetTitle(Form("%s=%.3f, %s=%.3f, %s=%.3f", fParNames[1].Data(), GetNormAB_I(counter), fParNames[2].Data(), GetNormC_I(counter), fParNames[0].Data(), GetNormB_I(counter)));
  }

  TF1* drawFcn = (TF1*) GetFitFcn_I(counter)->Clone("drawFcn");
  drawFcn->SetName(Form("fit, #chi^{2}/ndf = %.2f", GetChi2NDF_I(counter)));
  drawFcn->SetRange(fXmin, fXmax); // to draw only the range which was used for the fit.
  drawFcn->DrawClone("lsame");

  GetConfidenceGr_I(counter)->DrawClone("3 same");
  // LmHelper::Warning("The confidence level graph is only correct if the fit did not run into a limit.");

  // create histograms just for drawing and scale them:
  TH1D* drawTemplA = 0x0;
  TH1D* drawTemplB = 0x0;
  TH1D* drawTemplC = 0x0;

  drawTemplA = (TH1D*) GetTemplateA_I(counter)->Clone("drawTemplA");
  drawTemplA->SetTitle(Form("%s: %s", fTemplNameA.Data(), drawTemplA->GetTitle()));
  drawTemplA->Scale(GetNormA_I(counter)*GetNormAB_I(counter));
  drawTemplA->DrawCopy("hist same");

  TH1D* hSum = (TH1D*) drawTemplA->Clone("hSum");
  hSum->SetTitle("sum");
  hSum->SetLineColor(kBlack);
  hSum->SetLineWidth(2);
  hSum->SetLineStyle(7);

  if (fType!=kOneTempl) {
    drawTemplB = (TH1D*) GetTemplateB_I(counter)->Clone("drawTemplB");
    drawTemplB->SetTitle(Form("%s: %s", fTemplNameB.Data(), drawTemplB->GetTitle()));
    drawTemplB->Scale(GetNormB_I(counter)*GetNormAB_I(counter));
    drawTemplB->DrawCopy("hist same");
    hSum->Add(drawTemplB);
  }
  if (fType==kThreeTempl || fType==kThreeTempl_OneNorm_PlusBaseline) {
    drawTemplC = (TH1D*) GetTemplateC_I(counter)->Clone("drawTemplC");
    drawTemplC->SetTitle(Form("%s: %s", fTemplNameC.Data(), drawTemplC->GetTitle()));
    drawTemplC->Scale(GetNormC_I(counter));
    drawTemplC->DrawCopy("hist same");
    hSum->Add(drawTemplC);
  }

  hSum->DrawCopy("hist same");

  TLegend* leg = cFit->BuildLegend(0.2, 0.7, 0.9, 0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetNColumns(2);
  leg->Draw();
  GetDatahist()->Draw("p E1 same");
  lat->Draw();

  cFit->Print(filename.Data());
  delete cFit;
}


//_______________________________________________________________________________________________
void LmFitter::PrintCompareFits(TString filename)
{

//  if (fFitTemplateA.size()<2 && fFitTemplateB.size()<2 && fFitTemplateC.size()<2) {
//    PrintBestFit(filename);
//    return;
//  }

  gStyle->SetOptStat(0);
  TCanvas *cFit = new TCanvas("cFit","cFit", 810,0, 580*1.2,600*1.2);
  cFit->cd()->SetLogy();
  //GetDatahist()->GetYaxis()->SetRangeUser(0, GetDatahist()->GetMaximum()*1.5);
  // GetDatahist()->GetYaxis()->UnZoom();
  GetDatahist()->SetMarkerStyle(20);
  GetDatahist()->SetMarkerColor(kBlue+1); //GetDatahist()->GetLineColor()
  GetDatahist()->SetLineColor(kBlue+1);
  GetDatahist()->Draw("axis");

  TLatex* lat = new TLatex(0.2,0.67,"result");
  lat->SetNDC();
  lat->SetTextFont(gStyle->GetTitleFont());
  lat->SetTextSize(gStyle->GetTitleSize()*0.9);

  lat->SetTitle(Form("Best: %s=%.3f, %s=%.3f, %s=%.3f", fParNames[0].Data(), GetNormA_I(fIBestFit), fParNames[1].Data(), GetNormB_I(fIBestFit), fParNames[2].Data(), GetNormC_I(fIBestFit)));
  // overwrite the label for special types
  if ((fType==kThreeTempl_OneNorm_PlusBaseline) || fType==kTwoTempl_OneNorm) {
    lat->SetTitle(Form("Best: %s=%.3f, %s=%.3f, %s=%.3f", fParNames[1].Data(), GetNormAB_I(fIBestFit), fParNames[2].Data(), GetNormC_I(fIBestFit), fParNames[0].Data(), GetNormB_I(fIBestFit)));
  }

  UInt_t nFits = fvFitFcns.size();
  for (UInt_t counter=0; counter<nFits; ++counter)
  {
    GetFitFcn_I(counter)->SetLineColor(LmHelper::GetUniformColor(counter, nFits));
    GetFitFcn_I(counter)->SetName(Form("fit %i, #chi^{2}/ndf = %.2f", counter, GetChi2NDF_I(counter)));
    GetFitFcn_I(counter)->SetRange(GetDatahist()->GetXaxis()->GetXmin(), GetDatahist()->GetXaxis()->GetXmax()); // to draw over the full plot range.
    GetFitFcn_I(counter)->DrawClone("lsame");

    GetConfidenceGr_I(counter)->SetLineColor(LmHelper::GetUniformColor(counter, nFits));
    GetConfidenceGr_I(counter)->SetFillColor(LmHelper::GetUniformColor(counter, nFits));
    GetConfidenceGr_I(counter)->SetFillStyle(LmHelper::GetCompareFillStyle(counter));
    GetConfidenceGr_I(counter)->DrawClone("3 same");
  }
  // LmHelper::Warning("The confidence level graph is only correct if the fit did not run into a limit.");

  TLegend* leg = cFit->BuildLegend(0.2, 0.7, 0.9, 0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetNColumns(2);
  leg->Draw();
  GetDatahist()->Draw("p E1 same");
  lat->Draw();

  cFit->Print(filename.Data());
  delete cFit;
}


//_______________________________________________________________________________________________
Double_t LmFitter::GetNormA_I(UInt_t counter) const
{
  switch (fType) {
    case kOneTempl:
    case kTwoTempl:
    case kThreeTempl:
      return GetFitFcn_I(counter)->GetParameter(0);
      break;
    case kThreeTempl_OneNorm_PlusBaseline:
    case kTwoTempl_OneNorm:
      return (1. - GetFitFcn_I(counter)->GetParameter(0));
      break;
    default:
      LmHelper::Error(Form("LmFitter::GetNormA_I(): undefined for fType = %i.", fType));
      break;
  }
  return -1;
}

//_______________________________________________________________________________________________
Double_t LmFitter::GetNormB_I(UInt_t counter) const
{
  switch (fType) {
    case kOneTempl:
    case kTwoTempl:
    case kThreeTempl:
      return GetFitFcn_I(counter)->GetParameter(1);
      break;
    case kThreeTempl_OneNorm_PlusBaseline:
    case kTwoTempl_OneNorm:
      return GetFitFcn_I(counter)->GetParameter(0);
      break;
    default:
      LmHelper::Error(Form("LmFitter::GetNormB_I(): undefined for fType = %i.", fType));
      break;
  }
  return -1;
}

//_______________________________________________________________________________________________
Double_t LmFitter::GetNormC_I(UInt_t counter) const
{
  return GetFitFcn_I(counter)->GetParameter(2); // will it crash with less par? no.
}

//_______________________________________________________________________________________________
Double_t LmFitter::GetNormAB_I(UInt_t counter) const
{
  switch (fType) {
    case kOneTempl:
    case kTwoTempl:
    case kThreeTempl:
      //LmHelper::Warning(Form("LmFitter::GetNormAB_I(): don't use this for fType = %i.", fType));
      return 1.0; // must return 1.0 because of generalized drawing for all types.
      break;
    case kThreeTempl_OneNorm_PlusBaseline:
    case kTwoTempl_OneNorm:
      return GetFitFcn_I(counter)->GetParameter(1);
      break;
    default:
      LmHelper::Error(Form("LmFitter::GetNormAB_I(): undefined for fType = %i.", fType));
      break;
  }
  return -1;
}


//_______________________________________________________________________________________________
void LmFitter::PrintFitStatus(UInt_t counter)
{
  if (counter==9999) counter=fIBestFit;
  cout << "==================================================" << endl;
  if (counter==fIBestFit) {
    cout << " Best Fit result: Chi2/NDF = " << GetBestChi2NDF() << " (status=" << GetFitStatus_I(counter) << ", [0=OK])" << endl;
  } else {
    cout << " Fit result # "<<counter<<": Chi2/NDF = " << GetBestChi2NDF() << " (status=" << GetFitStatus_I(counter) << ", [0=OK])" << endl;
  }
  cout << " fitter->GetNormA_I(): " << GetNormA_I(counter) << endl;
  cout << " fitter->GetNormB_I(): " << GetNormB_I(counter) << endl;
  cout << " fitter->GetNormC_I(): " << GetNormC_I(counter) << endl;
  cout << " fitter->GetNormAB_I():" << GetNormAB_I(counter) << endl;
  cout << "==================================================" << endl;
}
