// c++ includes
#include <iostream>
using namespace std;
// ROOT includes
#include "TString.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TPaveText.h"
#include "TVirtualFitter.h"
#include "TSystem.h"
// project includes
#include "LmBackground.h"
#include "LmManager.h"
#include "LmBaseSignal.h"
#include "LmHelper.h"

extern Int_t debug;

//_______________________________________________________________________________________________
LmBackground::LmBackground(LmManager &mgr, std::string name) :
fName(name),
fType(0),
fTypename(""),
fLmMgr(&mgr),
fBkg(0x0),
fLike(0x0),
fLikeMix(0x0),
fRfactor(0x0),
fHasMixedEvent(kTRUE), //TRUE!
fUseRfactor(kTRUE), //TRUE!
fUseRfactorUnity(kFALSE),
fRfactorUnityRadius(100.),
fRfactorUnityMee(100.),
fRfactorUnityPtee(100.),
fNormMin(0.),
fNormMax(-1.),
fFitMeeMin(0.),
fFitMeeMax(-1.),
fFitPteeMin(0.),
fFitPteeMax(-1.),
fResidualFunction(),
fFitQA(kFALSE),
fFitQAPlotYmin(0.),
fFitQAPlotYmax(2.999),
fBkgLow(0x0),
fBkgHigh(0x0)
{
  LmHelper::Debug("LmBackground constructor", 5);
}


//_______________________________________________________________________________________________
void LmBackground::Process(Int_t type, Bool_t recursive) 
{
  LmHelper::Debug(Form("LmBackground Process(type=%d, recursive=%d)", type, recursive), 5);
  
  if (!fLmMgr->HasMixedEvent()) {
    LmHelper::Warning(Form("LmBackground::Process(): manager has no mixed event histograms. Just using like sign background."));
    fHasMixedEvent=kFALSE;
    fUseRfactor=kFALSE;
  }
  
  switch (type) {
    case kGeom:
      if (!recursive) { fTypename="Geom"; fType=type; }
      fLike    = CalcLSBackgroundGeom(fLmMgr->GetLikePP(), fLmMgr->GetLikeMM(), Form("hLike%s",GetTypename()));
      if (!fHasMixedEvent) return;
      fLikeMix = CalcLSBackgroundGeom(fLmMgr->GetLikePPMix(), fLmMgr->GetLikeMMMix(), Form("hLikeMix%s",GetTypename()));
      fRfactor = CalcRfactorByDiv2D(fLmMgr->GetUnlikeMix(), fLikeMix, Form("hRfactor%s",GetTypename()));
      break;
      
    case kArith:
      if (!recursive) { fTypename="Arith"; fType=type; }
      fLike    = CalcLSBackgroundArith(fLmMgr->GetLikePP(), fLmMgr->GetLikeMM(), Form("hLike%s",GetTypename()));
      if (!fHasMixedEvent) return;
      fLikeMix = CalcLSBackgroundArith(fLmMgr->GetLikePPMix(), fLmMgr->GetLikeMMMix(), Form("hLikeMix%s",GetTypename()));
      fRfactor = CalcRfactorByDiv2D(fLmMgr->GetUnlikeMix(), fLikeMix, Form("hRfactor%s",GetTypename()));
      break;
     
    case kHybrid:
      if (!recursive) { fTypename="Hybrid"; fType=type; } // name without 'k'
      fLike    = CalcLSBackgroundHybrid(fLmMgr->GetLikePP(), fLmMgr->GetLikeMM(), Form("hLike%s",GetTypename()));
      if (!fHasMixedEvent) return;
      fLikeMix = CalcLSBackgroundHybrid(fLmMgr->GetLikePPMix(), fLmMgr->GetLikeMMMix(), Form("hLikeMix%s",GetTypename()));
      fRfactor = CalcRfactorByDiv2D(fLmMgr->GetUnlikeMix(), fLikeMix, Form("hRfactor%s",GetTypename()));
      break;
    
    case kReal:
      if (!recursive) { fTypename="Hybrid"; fType=type; } // name without 'k'
      fLike    = CalcLSBackgroundReal(fLmMgr->GetLikePP(), fLmMgr->GetLikeMM(), Form("hLike%s",GetTypename()));
      if (!fHasMixedEvent) return;
      fLikeMix = CalcLSBackgroundReal(fLmMgr->GetLikePPMix(), fLmMgr->GetLikeMMMix(), Form("hLikeMix%s",GetTypename()));
      fRfactor = CalcRfactorByDiv2D(fLmMgr->GetUnlikeMix(), fLikeMix, Form("hRfactor%s",GetTypename()));
      break;
 
    case kLog:
      if (!recursive) { fTypename="Hybrid"; fType=type; } // name without 'k'
      fLike    = CalcLSBackgroundLog(fLmMgr->GetLikePP(), fLmMgr->GetLikeMM(), Form("hLike%s",GetTypename()));
      if (!fHasMixedEvent) return;
      fLikeMix = CalcLSBackgroundLog(fLmMgr->GetLikePPMix(), fLmMgr->GetLikeMMMix(), Form("hLikeMix%s",GetTypename()));
      fRfactor = CalcRfactorByDiv2D(fLmMgr->GetUnlikeMix(), fLikeMix, Form("hRfactor%s",GetTypename()));
      break;

    case kLSpp:
      if (!recursive) { fTypename="Positive"; fType=type; } // name without 'k'
      fLike    = CalcLSBackgroundPositive(fLmMgr->GetLikePP(), fLmMgr->GetLikePPMix(), Form("hLike%s",GetTypename()));
      if (!fHasMixedEvent) return;
      fLikeMix = CalcLSBackgroundPositive(fLmMgr->GetLikePPMix(), fLmMgr->GetLikeMMMix(), Form("hLikeMix%s",GetTypename()));
      fRfactor = CalcRfactorByDiv2D(fLmMgr->GetUnlikeMix(), fLikeMix, Form("hRfactor%s",GetTypename()));
      break;

    case kLSmm:
      if (!recursive) { fTypename="Negative"; fType=type; } // name without 'k'
      fLike    = CalcLSBackgroundNegative(fLmMgr->GetLikeMM(), fLmMgr->GetLikeMMMix(), Form("hLike%s",GetTypename()));
      if (!fHasMixedEvent) return;
      fLikeMix = CalcLSBackgroundNegative(fLmMgr->GetLikePPMix(), fLmMgr->GetLikeMMMix(), Form("hLikeMix%s",GetTypename()));
      fRfactor = CalcRfactorByDiv2D(fLmMgr->GetUnlikeMix(), fLikeMix, Form("hRfactor%s",GetTypename()));
      break;
  
    case kULSmixed:
      if (!recursive) { fTypename="UnlikeMixed"; fType=type; } // name without 'k'
      fLike    = CalcULSBackgroundMixed(fLmMgr->GetUnlikeMix(), fLmMgr->GetLikePP(), Form("h%s",GetTypename()));
      if (!fHasMixedEvent) return;
      fLikeMix = CalcULSBackgroundMixed(fLmMgr->GetLikePPMix(), fLmMgr->GetLikeMMMix(), Form("hLikeMix%s",GetTypename()));
      fRfactor = CalcRfactorByDiv2D(fLmMgr->GetUnlikeMix(), fLikeMix, Form("hRfactor%s",GetTypename()));
      break;

    case kGeomFit:
      if (!recursive) { fTypename="GeomFit"; fType=type; } // name without 'k'
      Process(kGeom, kTRUE); // fill fLike, fLikeMix, fRfactor
      // update fLike:
      fLike = FitNormalizationAndResiduals( fLike, fLmMgr->GetUnlikeMix(), Form("hLikeFit%s",GetTypename()));
      SetRfactorToUnityRectangle(fRfactor,fFitMeeMin,100.);
      break;
			
    case kArithFit:
      if (!recursive) { fTypename="ArithFit"; fType=type; } // name without 'k'
      Process(kArith, kTRUE); // fill fLike, fLikeMix, fRfactor
      // update fLike:
      fLike = FitNormalizationAndResiduals( fLike, fLmMgr->GetUnlikeMix(), Form("hLikeFit%s",GetTypename()));
      SetRfactorToUnityRectangle(fRfactor,fFitMeeMin,100.);
      break;
    
    case kHybridFit:
      if (!recursive) { fTypename="HybridFit"; fType=type; } // name without 'k'
      Process(kHybrid, kTRUE); // fill fLike, fLikeMix, fRfactor
      // update fLike:
      fLike = FitNormalizationAndResiduals( fLike, fLmMgr->GetUnlikeMix(), Form("hLikeFit%s",GetTypename()));
      SetRfactorToUnityRectangle(fRfactor,fFitMeeMin,100.);
      break;
      
    default:
      break;
  }
  if (recursive) return;
  // Put things below which shall be called only for non-recursive Process() calls, otherwise they are executed more than once!
  
  if (fUseRfactorUnity) {
    if (fRfactorUnityRadius<100) SetRfactorToUnity(fRfactor);
    if (fRfactorUnityMee<100 || fRfactorUnityPtee<100) SetRfactorToUnityRectangle(fRfactor,fRfactorUnityMee,fRfactorUnityPtee);
  }
  
  if (fUseRfactor) {
    // computation of R-factor already in switch block, so that it can be constructed in different ways.
    fBkg     = CorrectByRfactor(fLike, fRfactor, Form("%s_corr_%s",fLike->GetName(),fRfactor->GetName()));
    if(type == kGeomFit || type == kArithFit || type == kHybridFit){
      fBkgLow  = CorrectByRfactor(fBkgLow,  fRfactor, Form("%s_corr_%s",fBkgLow ->GetName(),fRfactor->GetName()));
      fBkgHigh = CorrectByRfactor(fBkgHigh, fRfactor, Form("%s_corr_%s",fBkgHigh->GetName(),fRfactor->GetName()));
    }
  }
  
}


//_______________________________________________________________________________________________
TH2D* LmBackground::FitNormalizationAndResiduals(const TH2D* hLS, const TH2D* hUSmix, const Char_t* newname)
{
/// Fit normalization for mixed event histograms. Fit Residuals of normalized US_mix to LS. 
/// Return background combined from LS up to fFitMeeMin and US_mix * residuals in mass range above fFitMeeMin
/// TF2 fResidualFunction has to be set by user.
/// @param hLS LikeSign same event histogram
/// @param hUSmix UnlikeSign mixed event histogram
/// @param newname name of returned background histogram

//  if(!fResidualFunction){ 
//    LmHelper::Error("No function set to fit residuals!");
//    return const_cast<TH2D*> (hLS); 
//  }
  if(fNormMax < fNormMin){
    LmHelper::Error("Invalid Normalization range!");
    return const_cast<TH2D*> (hLS); 
  }
  if(fFitMeeMax < fFitMeeMin){
    LmHelper::Error("Invalid fitting range!");
    return const_cast<TH2D*> (hLS); 
  }
  
  TH2D *hOut = new TH2D(*hLS);
  hOut->SetName(newname);
  fBkgLow = new TH2D(*hOut);
  fBkgLow->SetName(Form("%sLow",newname));
  fBkgHigh = new TH2D(*hOut);
  fBkgHigh->SetName(Form("%sHigh",newname));
  
  Double_t NormFactor(1.);
  TH1D hNormRatio( *(static_cast<TH1D*> (hLS->ProjectionX("",1,hLS->GetNbinsX(),""))) );
  hNormRatio.SetName("hRatio");
  hNormRatio.Divide( static_cast<TH1D*> (hUSmix->ProjectionX("",1,hLS->GetNbinsX(),"")) );
  TF1 fConst("const","[0]",0.,10.);
  hNormRatio.Fit(&fConst,"QE0","",fNormMin,fNormMax);
  NormFactor = hNormRatio.GetFunction("const")->GetParameter(0);
  TH2D hResidual(*hLS);
  hResidual.SetName("hResidual");
  hResidual.Divide(hUSmix);
  hResidual.Scale(1./NormFactor);
  TVirtualFitter *fitter(0x0);
  std::vector<TH2D> vFitError;
  for(UInt_t i = 0; i < fResidualFunction.size(); ++i){
    hResidual.Fit(fResidualFunction.at(i),"Q0RIEM","");
    fitter = TVirtualFitter::GetFitter();
    vFitError.push_back(TH2D(hResidual));
    vFitError.at(i).Reset();
    fitter->GetConfidenceIntervals(&(vFitError.at(i)),0.68);
  }
  
  
  std::vector<Double_t> vResCorrection    (static_cast<Int_t> (vFitError.size()),0.);
  std::vector<Double_t> vResCorrectionLow (static_cast<Int_t> (vFitError.size()),0.);
  std::vector<Double_t> vResCorrectionHigh(static_cast<Int_t> (vFitError.size()),0.);
  for(Int_t i1 = 0; i1 <= hOut->GetNbinsX(); ++i1){
    for(Int_t i2 = 0; i2 <= hOut->GetNbinsY(); ++i2){
      if(hOut->GetXaxis()->GetBinLowEdge(i1) < fFitMeeMin || hOut->GetYaxis()->GetBinLowEdge(i2) < fFitPteeMin ||
         hOut->GetXaxis()->GetBinUpEdge(i1)  > fFitMeeMax || hOut->GetYaxis()->GetBinUpEdge(i2)  > fFitPteeMax) 
        continue;
      else{
        Double_t val_mee  = hResidual.GetXaxis()->GetBinCenter(i1);
        Double_t val_ptee = hResidual.GetYaxis()->GetBinCenter(i2);
        for(UInt_t iFunc = 0; iFunc < vFitError.size(); ++iFunc){
          Int_t bin_mee  = vFitError.at(iFunc).GetXaxis()->FindBin(val_mee);
          Int_t bin_ptee = vFitError.at(iFunc).GetYaxis()->FindBin(val_ptee);
          vResCorrection    .at(iFunc) = vFitError.at(iFunc).GetBinContent(bin_mee,bin_ptee);
          vResCorrectionLow .at(iFunc) = vResCorrection.at(iFunc) - vFitError.at(iFunc).GetBinError(bin_mee,bin_ptee);
          vResCorrectionHigh.at(iFunc) = vResCorrection.at(iFunc) + vFitError.at(iFunc).GetBinError(bin_mee,bin_ptee);
        }
        Double_t ResidualCorrection     = vResCorrection    .at(LmHelper::GetIndex(vResCorrection,    LmHelper::kMedian));
        Double_t ResidualCorrectionLow  = vResCorrectionLow .at(LmHelper::GetIndex(vResCorrectionLow, LmHelper::kMin));
        Double_t ResidualCorrectionHigh = vResCorrectionHigh.at(LmHelper::GetIndex(vResCorrectionHigh,LmHelper::kMax));

        hOut    ->SetBinContent( i1,i2,hUSmix->GetBinContent(i1,i2)*ResidualCorrection    * NormFactor);
        hOut    ->SetBinError  ( i1,i2,hUSmix->GetBinError  (i1,i2)*ResidualCorrection    * NormFactor);
        fBkgLow ->SetBinContent( i1,i2,hUSmix->GetBinContent(i1,i2)*ResidualCorrectionLow * NormFactor);
        fBkgLow ->SetBinError  ( i1,i2,hUSmix->GetBinError  (i1,i2)*ResidualCorrectionLow * NormFactor);
        fBkgHigh->SetBinContent( i1,i2,hUSmix->GetBinContent(i1,i2)*ResidualCorrectionHigh* NormFactor);
        fBkgHigh->SetBinError  ( i1,i2,hUSmix->GetBinError  (i1,i2)*ResidualCorrectionHigh* NormFactor);
      }
    }
  }
  
  LmHelper::Debug(Form("Normalization factor: %10.9f",NormFactor),3);
  
  if(fFitQA){
    gSystem->Exec("if [ ! -d \"./FitQA/Mee/\" ]; then mkdir -p ./FitQA/Mee; fi");
    gSystem->Exec("if [ ! -d \"./FitQA/Ptee/\" ]; then mkdir -p ./FitQA/Ptee; fi");

//    std::cout << "Chi2/NDF:  " << fResidualFunction.GetChisquare()/fResidualFunction.GetNDF() << std::endl;
    hNormRatio.SetMarkerStyle(20);
    hNormRatio.SetMarkerSize(0.8);
    hNormRatio.SetMarkerColor(1);
    hNormRatio.GetFunction("const")->SetLineColor(kRed);
    hNormRatio.GetFunction("const")->SetLineWidth(2);
    LmHelper::PrintHistogram(&hNormRatio,Form("./FitQA/NormFit_%s_%s.pdf",GetName(),newname));
    LmHelper::PrintHistogram(hOut,Form("./FitQA/BG2D_%s_%s.pdf",GetName(),newname),"colz");
    for(UInt_t iFunc = 0; iFunc < fResidualFunction.size(); iFunc++){
      for(Int_t ix = 0; ix <= vFitError.at(iFunc).GetNbinsX()+1; ++ix){
        for(Int_t iy = 0; iy <= vFitError.at(iFunc).GetNbinsY()+1; ++iy){
          if(vFitError.at(iFunc).GetXaxis()->GetBinLowEdge(ix) < fFitMeeMin || vFitError.at(iFunc).GetYaxis()->GetBinLowEdge(iy) < fFitPteeMin ||
             vFitError.at(iFunc).GetXaxis()->GetBinUpEdge(ix)  > fFitMeeMax || vFitError.at(iFunc).GetYaxis()->GetBinUpEdge(iy)  > fFitPteeMax){
            vFitError.at(iFunc).SetBinContent(ix,iy,0.);
            vFitError.at(iFunc).SetBinError(ix,iy,0.);
          }
        }
      }
    }
    std::vector<Double_t> vecQA_BinsPtee_forprojMee;
    if(fQA_BinsPtee_forprojMee.size() == 0){
      Double_t pteeRange = fFitPteeMax - fFitPteeMin;
      for(UInt_t i = 0 ; i <= 5; ++i)
        fQA_BinsPtee_forprojMee.push_back(fFitPteeMin + i * pteeRange/5.);
    }
    else{
      for(UInt_t i = 0; i < fQA_BinsPtee_forprojMee.size(); ++i){
        if(fQA_BinsPtee_forprojMee.at(i) > fFitPteeMin - LmHelper::kSmallDelta)
          vecQA_BinsPtee_forprojMee.push_back(fQA_BinsPtee_forprojMee.at(i));
      }
    }
    PrintFitQA( hResidual, vFitError,vecQA_BinsPtee_forprojMee , LmBaseSignal::kProjOnMee);
    std::vector<Double_t> vecQA_BinsMee_forprojPtee;
    if(fQA_BinsMee_forprojPtee.size() < 1){
      Double_t MeeRange = fFitMeeMax - fFitMeeMin;
      for(UInt_t i = 0 ; i <= 5; ++i)
        fQA_BinsMee_forprojPtee.push_back(fFitMeeMin + i * MeeRange/5.);
    }
    else{
      for(UInt_t i = 0; i < fQA_BinsMee_forprojPtee.size(); ++i){
        if(fQA_BinsMee_forprojPtee.at(i) > fFitMeeMin - LmHelper::kSmallDelta)
          vecQA_BinsMee_forprojPtee.push_back(fQA_BinsMee_forprojPtee.at(i));
      }
      if(vecQA_BinsMee_forprojPtee.at(vecQA_BinsMee_forprojPtee.size()-1) < fFitMeeMax - LmHelper::kSmallDelta)
        vecQA_BinsMee_forprojPtee.push_back(fFitMeeMax);
    }
    PrintFitQA( hResidual, vFitError, vecQA_BinsMee_forprojPtee, LmBaseSignal::kProjOnPtee);
  }
  
  return hOut;
}

//_______________________________________________________________________________________________
void LmBackground::PrintFitQA(TH2D &hRes, std::vector<TH2D> &vFit, std::vector<Double_t> bins,  Bool_t projOnMee)
{
  
  TCanvas c("c","",800,800);
  
  gPad->SetTicks();
  gPad->SetTopMargin(0.02);
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.12);

  TH1D* hResProj(0x0);
  // only c++11:
  //std::vector<TH1D*> vFitProj(static_cast<Int_t> (vFit.size()),0x0),vFitLowProj(static_cast<Int_t> (vFit.size()),0x0),vFitHighProj(static_cast<Int_t> (vFit.size()),0x0);
  // old c++:
  std::vector<TH1D*> vFitProj, vFitLowProj, vFitHighProj;
  vFitProj.resize(vFit.size()); // resize vectors to have space for histograms
  vFitLowProj.resize(vFit.size());
  vFitHighProj.resize(vFit.size());
  
  for(UInt_t i = 0; i < bins.size()-1; ++i){
    TPaveText text(0.70,0.88,0.95,0.93,"brNDC");
    text.SetBorderSize(0);
    text.SetTextSize(0.02);
    text.SetFillColor(0);
    text.SetLineColor(kWhite);
    text.SetFillStyle(0);
    text.SetTextAlign(12);
    for(UInt_t iFunc = 0; iFunc < vFit.size(); ++iFunc){
      if(projOnMee){
        vFitProj.at(iFunc) = static_cast<TH1D*> (vFit.at(iFunc).ProjectionX(Form("hFit%2d_proj",iFunc),vFit.at(iFunc).GetYaxis()->FindBin(bins[i]),vFit.at(iFunc).GetYaxis()->FindBin(bins[i+1]-LmHelper::kSmallDelta)));
        vFitProj.at(iFunc)->Scale(1/((Double_t) (vFit.at(iFunc).GetYaxis()->FindBin(bins[i+1]-LmHelper::kSmallDelta) - vFit.at(iFunc).GetYaxis()->FindBin(bins[i]) +1) ));
        if(iFunc == 0){
          hResProj = static_cast<TH1D*> (hRes.ProjectionX(Form("hRes%2d_proj",iFunc),hRes.GetYaxis()->FindBin(bins[i]),hRes.GetYaxis()->FindBin(bins[i+1]-LmHelper::kSmallDelta)));
          hResProj->Scale(1/((Double_t) (hRes.GetYaxis()->FindBin(bins[i+1]-LmHelper::kSmallDelta) - hRes.GetYaxis()->FindBin(bins[i]) +1) ));
          hResProj->GetXaxis()->SetTitle("#it{m}_{ee} (GeV/c^{2})");
          hResProj->GetYaxis()->SetTitle("LS/US_{mix}");
          text.AddText(Form("%3.2f < p^{ee}_{T} < %3.2f (GeV/c)",bins[i],bins[i+1]));
        }
      }
      else{
        vFitProj.at(iFunc) = static_cast<TH1D*> (vFit.at(iFunc).ProjectionY(Form("hFit%2d_proj",iFunc),vFit.at(iFunc).GetXaxis()->FindBin(bins[i]),vFit.at(iFunc).GetXaxis()->FindBin(bins[i+1]-LmHelper::kSmallDelta)));
        vFitProj.at(iFunc)->Scale(1/((Double_t) (vFit.at(iFunc).GetXaxis()->FindBin(bins[i+1]-LmHelper::kSmallDelta) - vFit.at(iFunc).GetXaxis()->FindBin(bins[i]) +1) ));
        if(iFunc == 0){ 
          hResProj = static_cast<TH1D*> (hRes.ProjectionY(Form("hRes%2d_proj",iFunc),hRes.GetXaxis()->FindBin(bins[i]),hRes.GetXaxis()->FindBin(bins[i+1]-LmHelper::kSmallDelta)));
          hResProj->Scale(1/((Double_t) (hRes.GetXaxis()->FindBin(bins[i+1]-LmHelper::kSmallDelta) - hRes.GetXaxis()->FindBin(bins[i]) +1) ));
          hResProj->GetXaxis()->SetTitle("#it{p}^{ee}_{T} (GeV/c)");
          hResProj->GetYaxis()->SetTitle("LS/US_{mix}");
          text.AddText(Form("%3.2f < m_{ee} < %3.2f (GeV/c^{2})",bins[i],bins[i+1]));
        }
      }
      if(!(vFitProj.at(iFunc) || hResProj)){ 
        LmHelper::Error(Form("Projection of fitQA histograms failed (bin=%d)",i));
        return;
      }
      vFitLowProj .at(iFunc) = static_cast<TH1D*> (vFitProj.at(iFunc)->Clone(Form("hFit%2d_low_proj",iFunc)));
      vFitHighProj.at(iFunc) = static_cast<TH1D*> (vFitProj.at(iFunc)->Clone(Form("hFit%2d_high_proj",iFunc)));
      for(Int_t ix = 1; ix < vFitProj.at(iFunc)->GetNbinsX(); ++ix){
        vFitLowProj.at(iFunc)->SetBinContent(ix,vFitProj.at(iFunc)->GetBinContent(ix) - vFitProj.at(iFunc)->GetBinError(ix));
        vFitLowProj.at(iFunc)->SetBinError(ix,0.);
        vFitHighProj.at(iFunc) ->SetBinContent(ix,vFitProj.at(iFunc)->GetBinContent(ix) + vFitProj.at(iFunc)->GetBinError(ix));
        vFitHighProj.at(iFunc) ->SetBinError(ix,0.);
        vFitProj.at(iFunc)->SetBinError(ix,0.);
      }  
      
      Int_t color = LmHelper::GetUniformColor(iFunc,vFit.size());
      vFitProj.at(iFunc)->SetMarkerColor(color);
      vFitProj.at(iFunc)->SetLineColor(color);
      vFitProj.at(iFunc)->SetMarkerStyle(20);
      vFitProj.at(iFunc)->SetLineWidth(1);
      vFitProj.at(iFunc)->SetMarkerSize(0.7);
      vFitProj.at(iFunc)->SetLineStyle(1);
      
      vFitLowProj.at(iFunc)->SetMarkerColor(color);
      vFitLowProj.at(iFunc)->SetLineColor(color);
      vFitLowProj.at(iFunc)->SetMarkerStyle(20);
      vFitLowProj.at(iFunc)->SetLineWidth(1);
      vFitLowProj.at(iFunc)->SetMarkerSize(0.7);
      vFitLowProj.at(iFunc)->SetLineStyle(kDashed);
      
      vFitHighProj.at(iFunc)->SetMarkerColor(color);
      vFitHighProj.at(iFunc)->SetLineColor(color);
      vFitHighProj.at(iFunc)->SetMarkerStyle(20);
      vFitHighProj.at(iFunc)->SetLineWidth(1);
      vFitHighProj.at(iFunc)->SetMarkerSize(0.7);
      vFitHighProj.at(iFunc)->SetLineStyle(kDashed);
      
      if(iFunc == 0){  
        hResProj->SetMarkerColor(color);
        hResProj->SetLineColor(color);
        hResProj->SetMarkerStyle(20);
        hResProj->SetMarkerSize(0.7);  
        hResProj->GetYaxis()->SetRangeUser(fFitQAPlotYmin,fFitQAPlotYmax);  
        hResProj->Draw();
      }
      
      vFitLowProj .at(iFunc)->Draw("hist ][ same");
      vFitHighProj.at(iFunc)->Draw("hist ][ same");
      vFitProj    .at(iFunc)->Draw("hist ][ same");
    } 
    text.Draw("same");
    if(projOnMee)   c.SaveAs(Form("./FitQA/Mee/FitQA_%s_MeeBin%d.pdf",GetName(),i));
    else            c.SaveAs(Form("./FitQA/Ptee/FitQA_%s_PteeBin%d.pdf",GetName(),i));
  }
  
  
  TPaveText text(0.70,0.88,0.95,0.93,"brNDC");
  text.SetBorderSize(0);
  text.SetTextSize(0.02);
  text.SetFillColor(0);
  text.SetLineColor(kWhite);
  text.SetFillStyle(0);
  text.SetTextAlign(12);
  for(UInt_t iFunc = 0; iFunc < vFit.size(); ++iFunc){
    if(projOnMee){
      vFitProj.at(iFunc) = static_cast<TH1D*> (vFit.at(iFunc).ProjectionX(Form("hFit%2d_proj_all",iFunc),hRes.GetYaxis()->FindBin(fFitPteeMin),vFit.at(iFunc).GetYaxis()->FindBin(fFitPteeMax-LmHelper::kSmallDelta)));
      vFitProj.at(iFunc)->Scale(1/((Double_t) (vFit.at(iFunc).GetYaxis()->FindBin(fFitPteeMax-LmHelper::kSmallDelta) - vFit.at(iFunc).GetYaxis()->FindBin(fFitPteeMin) +1)));
      if(iFunc == 0){
        hResProj = static_cast<TH1D*> (hRes.ProjectionX("hRes%2d_proj_all",hRes.GetYaxis()->FindBin(fFitPteeMin),hRes.GetYaxis()->FindBin(fFitPteeMax-LmHelper::kSmallDelta)));
        hResProj->Scale(1/((Double_t) (hRes.GetYaxis()->FindBin(fFitPteeMax-LmHelper::kSmallDelta) - hRes.GetYaxis()->FindBin(fFitPteeMin) +1)));
        hResProj->GetXaxis()->SetTitle("#it{m}_{ee} (GeV/c^{2})");
        hResProj->GetYaxis()->SetTitle("LS/US_{mix}");
        text.AddText(Form("%3.2f < p^{ee}_{T} < %3.2f (GeV/c)",fFitPteeMin,fFitPteeMax));
      }
    }
    else{
      vFitProj.at(iFunc) = static_cast<TH1D*> (vFit.at(iFunc).ProjectionY(Form("hFit%2d_proj_all",iFunc),vFit.at(iFunc).GetXaxis()->FindBin(fFitMeeMin),vFit.at(iFunc).GetXaxis()->FindBin(fFitMeeMax-LmHelper::kSmallDelta)));
      vFitProj.at(iFunc)->Scale(1/((Double_t) (vFit.at(iFunc).GetXaxis()->FindBin(fFitMeeMax-LmHelper::kSmallDelta) - vFit.at(iFunc).GetXaxis()->FindBin(fFitMeeMin) +1)));
      if(iFunc == 0){
        hResProj = static_cast<TH1D*> (hRes.ProjectionY("hRes%2d_proj_all",hRes.GetXaxis()->FindBin(fFitMeeMin),hRes.GetXaxis()->FindBin(fFitMeeMax-LmHelper::kSmallDelta)));
        hResProj->Scale(1/((Double_t) (hRes.GetXaxis()->FindBin(fFitMeeMax-LmHelper::kSmallDelta) - hRes.GetXaxis()->FindBin(fFitMeeMin) +1)));
        hResProj->GetXaxis()->SetTitle("#it{p}^{ee}_{T} (GeV/c)");
        hResProj->GetYaxis()->SetTitle("LS/US_{mix}");
        text.AddText(Form("%3.2f < m_{ee} < %3.2f (GeV/c^{2})",fFitMeeMin,fFitMeeMax));
      }
    }
    for(Int_t ix = 1; ix < vFitProj.at(iFunc)->GetNbinsX(); ++ix){
      vFitLowProj .at(iFunc)->SetBinContent(ix,vFitProj.at(iFunc)->GetBinContent(ix) - vFitProj.at(iFunc)->GetBinError(ix));
      vFitLowProj .at(iFunc)->SetBinError(ix,0.);
      vFitHighProj.at(iFunc)->SetBinContent(ix,vFitProj.at(iFunc)->GetBinContent(ix) + vFitProj.at(iFunc)->GetBinError(ix));
      vFitHighProj.at(iFunc)->SetBinError(ix,0.);
      vFitProj.at(iFunc)->SetBinError(ix,0.);
    }  
    Int_t color = LmHelper::GetUniformColor(iFunc,vFit.size());
    
    vFitProj.at(iFunc)->SetMarkerColor(color);
    vFitProj.at(iFunc)->SetLineColor(color);
    vFitProj.at(iFunc)->SetMarkerStyle(20);
    vFitProj.at(iFunc)->SetLineWidth(1);
    vFitProj.at(iFunc)->SetMarkerSize(0.7);
    vFitProj.at(iFunc)->SetLineStyle(1);
    
    vFitLowProj.at(iFunc)->SetMarkerColor(color);
    vFitLowProj.at(iFunc)->SetLineColor(color);
    vFitLowProj.at(iFunc)->SetMarkerStyle(20);
    vFitLowProj.at(iFunc)->SetLineWidth(1);
    vFitLowProj.at(iFunc)->SetMarkerSize(0.7);
    vFitLowProj.at(iFunc)->SetLineStyle(kDashed);
    
    vFitHighProj.at(iFunc)->SetMarkerColor(color);
    vFitHighProj.at(iFunc)->SetLineColor(color);
    vFitHighProj.at(iFunc)->SetMarkerStyle(20);
    vFitHighProj.at(iFunc)->SetLineWidth(1);
    vFitHighProj.at(iFunc)->SetMarkerSize(0.7);
    vFitHighProj.at(iFunc)->SetLineStyle(kDashed);
    
    if(iFunc == 0){  
      hResProj->SetMarkerColor(color);
      hResProj->SetLineColor(color);
      hResProj->SetMarkerStyle(20);
      hResProj->SetMarkerSize(0.7);  
      hResProj->GetYaxis()->SetRangeUser(fFitQAPlotYmin,fFitQAPlotYmax);  
      hResProj->Draw();
    }
    vFitLowProj .at(iFunc)->Draw("hist ][ same");
    vFitHighProj.at(iFunc)->Draw("hist ][ same");  
    vFitProj.at(iFunc)    ->Draw("hist ][ same");
  }
  text.Draw("same");
  if(projOnMee)   c.SaveAs(Form("./FitQA/Mee/FitQA_%s_Mee.pdf",GetName()));
  else            c.SaveAs(Form("./FitQA/Ptee/FitQA_%s_Ptee.pdf",GetName()));
  
}

//_______________________________________________________________________________________________
void LmBackground::SetRfactorToUnity(TH2D *hRfactor)
{
  /// in the pairPt-InvMass histogram, set Rfactor = 1 above radius r of quarter cirlce
  LmHelper::Debug(" SetRfactorToUnity()", 5);
  for (Int_t ix = 1; ix <= hRfactor->GetNbinsX(); ix++) {
    for (Int_t iy = 1; iy <= hRfactor->GetNbinsY(); iy++) {
      Double_t pos1 = hRfactor->GetXaxis()->GetBinLowEdge(ix);
      Double_t pos2 = hRfactor->GetYaxis()->GetBinLowEdge(iy);
      Double_t r = TMath::Sqrt(pos1 * pos1 + pos2 * pos2);
      if (r < fRfactorUnityRadius) continue;
      else {
        hRfactor->SetBinContent(ix,iy,1.);
        hRfactor->SetBinError(ix,iy,0.);
      }
    }
  }
}

//_______________________________________________________________________________________________
void LmBackground::SetRfactorToUnityRectangle(TH2D *hRfactor, Double_t meeCut, Double_t pteeCut)
{
  /// in the pairPt-InvMass histogram, set Rfactor = 1 above meeCut and pteeCut respectively
  LmHelper::Debug(" SetRfactorToUnityRectangle()", 5);
  for(Int_t ix = 1; ix <= hRfactor->GetNbinsX(); ix++) {
    for(Int_t iy = 1; iy <= hRfactor->GetNbinsY(); iy++) {
      Double_t pos1 = hRfactor->GetXaxis()->GetBinLowEdge(ix);
      Double_t pos2 = hRfactor->GetYaxis()->GetBinLowEdge(iy);
      if(pos1 < meeCut && pos2 < pteeCut) 
        continue;
      else {
        hRfactor->SetBinContent(ix,iy,1.);
        hRfactor->SetBinError(ix,iy,0.);
      }
    }
  }
}

//_______________________________________________________________________________________________
TH2D* LmBackground::CalcULSBackgroundMixed(const TH2D* hULSmixed, const TH2D* hULSmixed1, const Char_t* newname)
{
  /// Use geometric calculation only if both bins have non-zero entries
  LmHelper::Debug(" CalcLSBackgroundPositive()", 5);
  TH2D* hLS = (TH2D*) (hULSmixed->Clone(newname));
  //TH2D* hLS = dynamic_cast<TH2D*>(hPP->Clone(newname));
 
  Double_t counter = 0; 
  Int_t globalbin=0;
  for (Int_t bx=1;bx <= hLS->GetNbinsX(); bx++) {
    for (Int_t by=1;by <= hLS->GetNbinsY(); by++) {
      Double_t mMass = hLS->GetXaxis()->GetBinCenter(bx);
      Double_t mPt   = hLS->GetYaxis()->GetBinCenter(by);
      if(0.5*(TMath::Sqrt(mMass*mMass + mPt*mPt) - 2*0.0005109989) < 0.075) continue;
      
      globalbin=hLS->GetBin(bx,by);
      Double_t scaling = (hULSmixed1->Integral()/hULSmixed->Integral());
      Double_t val1 = hULSmixed->GetBinContent(globalbin);// * scaling;// / hULSmixed1->GetBinContent(globalbin);

      //if(hLS->GetXaxis()->GetBinCenter(bx) <= 0.6 && hLS->GetYaxis()->GetBinCenter(by) <= 0.4)
      //   std::cout << "-->>x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << "   binc: " << val1 << " " << val2 << "  A: " << (1-val1/val2)/2 << std::endl;
      //else
      //  std::cout << "x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << "   binc: " << val1 << " " << val2 << "  A: " << (1-val1/val2)/2 << std::endl;

      Double_t thisVal = val1;
      Double_t thisErr = 0.;
      
      //WARNING: this is only valid when histogram is NOT normalized per 1GeV!
      Double_t err1(0.),err2(0.);
      if(val1 > 0) err1 = TMath::Sqrt(val1);
      thisErr =  err1;
      if(thisVal > 0) {
        hLS->SetBinContent(globalbin,thisVal);
        hLS->SetBinError(globalbin,thisErr);
      }
      else {
        hLS->SetBinContent(globalbin,0);
        hLS->SetBinError(globalbin,0);
      }
      
    }
  }
  return hLS;
}


//_______________________________________________________________________________________________
TH2D* LmBackground::CalcLSBackgroundPositive(const TH2D* hPP, const TH2D* hPPmixed, const Char_t* newname)
{
  /// Use geometric calculation only if both bins have non-zero entries
  LmHelper::Debug(" CalcLSBackgroundPositive()", 5);
  TH2D* hLS = (TH2D*) (hPP->Clone(newname));
  //TH2D* hLS = dynamic_cast<TH2D*>(hPP->Clone(newname));
 
  Double_t counter = 0; 
  Int_t globalbin=0;
  for (Int_t bx=1;bx <= hLS->GetNbinsX(); bx++) {
    for (Int_t by=1;by <= hLS->GetNbinsY(); by++) {
      Double_t mMass = hLS->GetXaxis()->GetBinCenter(bx);
      Double_t mPt   = hLS->GetYaxis()->GetBinCenter(by);
      if(0.5*(TMath::Sqrt(mMass*mMass + mPt*mPt) - 2*0.0005109989) < 0.075) continue;
      
      globalbin=hLS->GetBin(bx,by);
      Double_t val1 = hPP->GetBinContent(globalbin); /// ( hPPmixed->GetBinContent(globalbin) *  hPP->Integral()/hPPmixed->Integral() );

      //if(hLS->GetXaxis()->GetBinCenter(bx) <= 0.6 && hLS->GetYaxis()->GetBinCenter(by) <= 0.4)
      //   std::cout << "-->>x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << "   binc: " << val1 << " " << val2 << "  A: " << (1-val1/val2)/2 << std::endl;
      //else
      //  std::cout << "x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << "   binc: " << val1 << " " << val2 << "  A: " << (1-val1/val2)/2 << std::endl;

      Double_t thisVal = val1;
      Double_t thisErr = 0.;
      
      //WARNING: this is only valid when histogram is NOT normalized per 1GeV!
      Double_t err1(0.),err2(0.);
      if(val1 > 0) err1 = TMath::Sqrt(val1);
      thisErr =  err1;
      if(thisVal > 0) {
        hLS->SetBinContent(globalbin,thisVal);
        hLS->SetBinError(globalbin,thisErr);
      }
      else {
        hLS->SetBinContent(globalbin,0);
        hLS->SetBinError(globalbin,0);
      }
      
    }
  }
  return hLS;
}

//_______________________________________________________________________________________________
TH2D* LmBackground::CalcLSBackgroundNegative(const TH2D* hMM, const TH2D* hMMmixed, const Char_t* newname)
{
  /// Use geometric calculation only if both bins have non-zero entries
  LmHelper::Debug(" CalcLSBackgroundPositive()", 5);
  TH2D* hLS = (TH2D*) (hMM->Clone(newname));
  //TH2D* hLS = dynamic_cast<TH2D*>(hPP->Clone(newname));
 
  Double_t counter = 0; 
  Int_t globalbin=0;
  for (Int_t bx=1;bx <= hLS->GetNbinsX(); bx++) {
    for (Int_t by=1;by <= hLS->GetNbinsY(); by++) {
      Double_t mMass = hLS->GetXaxis()->GetBinCenter(bx);
      Double_t mPt   = hLS->GetYaxis()->GetBinCenter(by);
      if(0.5*(TMath::Sqrt(mMass*mMass + mPt*mPt) - 2*0.0005109989) < 0.075) continue;
      
      globalbin=hLS->GetBin(bx,by);
      Double_t val1 = hMM->GetBinContent(globalbin);// / ( hMMmixed->GetBinContent(globalbin) *  hMM->Integral()/hMMmixed->Integral() );

      //if(hLS->GetXaxis()->GetBinCenter(bx) <= 0.6 && hLS->GetYaxis()->GetBinCenter(by) <= 0.4)
      //   std::cout << "-->>x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << "   binc: " << val1 << " " << val2 << "  A: " << (1-val1/val2)/2 << std::endl;
      //else
      //  std::cout << "x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << "   binc: " << val1 << " " << val2 << "  A: " << (1-val1/val2)/2 << std::endl;

      Double_t thisVal = val1;
      Double_t thisErr = 0.;
      
      //WARNING: this is only valid when histogram is NOT normalized per 1GeV!
      Double_t err1(0.),err2(0.);
      if(val1 > 0) err1 = TMath::Sqrt(val1);
      thisErr =  err1;
      if(thisVal > 0) {
        hLS->SetBinContent(globalbin,thisVal);
        hLS->SetBinError(globalbin,thisErr);
      }
      else {
        hLS->SetBinContent(globalbin,0);
        hLS->SetBinError(globalbin,0);
      }
      
    }
  }
  return hLS;
}


//_______________________________________________________________________________________________
TH2D* LmBackground::CalcLSBackgroundReal(const TH2D* hPP, const TH2D* hMM, const Char_t* newname)
{
  /// Use ULS background estimation calculation only if both bins have non-zero entries
  LmHelper::Debug(" CalcLSBackgroundReal()", 5);
  TH2D* hLS = (TH2D*) (hPP->Clone(newname));
  //TH2D* hLS = dynamic_cast<TH2D*>(hPP->Clone(newname));
 
  Double_t counter = 0; 
  Int_t globalbin=0;
  for (Int_t bx=1;bx <= hLS->GetNbinsX(); bx++) {
    for (Int_t by=1;by <= hLS->GetNbinsY(); by++) {
      Double_t mMass = hLS->GetXaxis()->GetBinCenter(bx);
      Double_t mPt   = hLS->GetYaxis()->GetBinCenter(by);
      if(0.5*(TMath::Sqrt(mMass*mMass + mPt*mPt) - 2*0.0005109989) < 0.075) continue;
      
      globalbin=hLS->GetBin(bx,by);
      Double_t N_PP = hPP->GetBinContent(globalbin);
      Double_t N_MM = hMM->GetBinContent(globalbin);
      Double_t N_PP_err = hPP->GetBinError(globalbin);
      Double_t N_MM_err = hMM->GetBinError(globalbin);

      Double_t N = -1;
      Double_t A = 99;
      Double_t A_eff = 99;
      if(N_MM > N_PP){
        N = 0.5*(1+sqrt(1+8*N_MM));
        A_eff = 1-N_PP/N_MM;
        A = (1-2*N)/(-2) + sqrt( ((1-2*N)/(2))*((1-2*N)/(2)) + A_eff*(1-N) );
      }
      else if(N_PP > N_MM){
        N = 0.5*(1+sqrt(1+8*N_PP));
        A_eff = 1-N_MM/N_PP;
        A = (1-2*N)/(-2) + sqrt( ((1-2*N)/(2))*((1-2*N)/(2)) + A_eff*(1-N) );
      }
      else{
        A=0;
        A_eff=0;
        N = 0.5*(1+sqrt(1+8*N_PP)); 
      } 

      Double_t N_P = 0.5*(1+sqrt(1+8*N_PP));
      Double_t N_M = 0.5*(1+sqrt(1+8*N_MM));
      Double_t N_P_err = 2/sqrt(1+8)*N_PP_err;
      Double_t N_M_err = 2/sqrt(1+8)*N_MM_err; 

      //if(hLS->GetXaxis()->GetBinCenter(bx) <= 0.6 && hLS->GetYaxis()->GetBinCenter(by) <= 0.4)
      //   std::cout << "-->>x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << "   binc: " << N_PP << " " << N_MM << "  A: " << A << "  A_eff: " << A_eff << "  N: " << N << std::endl;
      //else
      //   std::cout << "x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << "   binc: " << N_PP << " " << N_MM << "  A: " << A << "  A_eff: " << A_eff << "  N: " << N << std::endl;

      Double_t thisVal = N*N - N;
      Double_t thisErr = 0.;
      thisVal = 2. * thisVal*(1-A);

      Double_t test = -1;
      Double_t test_err = -1;
      if(N_P>=N_M){
        test = N_P*N_M-N_M;
        test_err = sqrt( (N_M*N_P_err)*(N_M*N_P_err) + (((N_P)-1)*N_M_err)*(((N_P)-1)*N_M_err) );
      }
      else{
        test = N_P*N_M-N_P;

      }
      //std::cout << "test: " << thisVal << " " << test << std::endl;
      thisVal = test;
      //WARNING: this is only valid when histogram is NOT normalized per 1GeV!
      Double_t err1(0.),err2(0.);
      if(N_PP > 0) err1 = TMath::Sqrt(N_PP);
      if(N_MM > 0) err2 = TMath::Sqrt(N_MM);
      //Patrick: (quadratic addition of squares of errors - Gauß'sche Fehlerfortpflanzung)
      //thisErr =  sqrt((val2/sqrt(val1*val2))*err1*(val2/sqrt(val1*val2))*err1 + (val1/sqrt(val1*val2))*err2*(val1/sqrt(val1*val2))*err2);
      // can be written shorter, because err=sqrt(val):
      thisErr =  TMath::Sqrt(err2 * err2 + err1 * err1);
      thisErr = test_err;
      if(thisVal > 0) 
        hLS->SetBinContent(globalbin,thisVal);
      else { 
        hLS->SetBinContent(globalbin,(N_MM+N_PP));
        if(hLS->GetXaxis()->GetBinCenter(bx)<=0.6 && hLS->GetYaxis()->GetBinCenter(by)<=0.4) counter++;
        //std::cout << "global bin: " << globalbin << std::endl;
        //std::cout << "x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << std::endl;
      }
      
      hLS->SetBinError(globalbin,thisErr);
    }
  }
  std::cout << counter << " procent arithmetric  " << newname << std::endl;
  return hLS;
}

//_______________________________________________________________________________________________
TH2D* LmBackground::CalcLSBackgroundLog(const TH2D* hPP, const TH2D* hMM, const Char_t* newname)
{
  /// Use logarithmic calculation only if both bins have non-zero entries
  LmHelper::Debug(" CalcLSBackgroundLog()", 5);
  TH2D* hLS = (TH2D*) (hPP->Clone(newname));
  //TH2D* hLS = dynamic_cast<TH2D*>(hPP->Clone(newname));
 
  Double_t counter = 0; 
  Int_t globalbin=0;
  for (Int_t bx=1;bx <= hLS->GetNbinsX(); bx++) {
    for (Int_t by=1;by <= hLS->GetNbinsY(); by++) {
      Double_t mMass = hLS->GetXaxis()->GetBinCenter(bx);
      Double_t mPt   = hLS->GetYaxis()->GetBinCenter(by);
      if(0.5*(TMath::Sqrt(mMass*mMass + mPt*mPt) - 2*0.0005109989) < 0.075) continue;
      
      globalbin=hLS->GetBin(bx,by);
      //LS = PP+MM = (PP-MM)/ln(PP/MM);
      Double_t val1 = hPP->GetBinContent(globalbin);
      Double_t val2 = hMM->GetBinContent(globalbin);

      //if(hLS->GetXaxis()->GetBinCenter(bx) <= 0.6 && hLS->GetYaxis()->GetBinCenter(by) <= 0.4)
      //   std::cout << "-->>x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << "   binc: " << val1 << " " << val2 << "  A: " << (1-val1/val2)/2 << std::endl;
      //else
      //  std::cout << "x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << "   binc: " << val1 << " " << val2 << "  A: " << (1-val1/val2)/2 << std::endl;

      Double_t thisVal = val1 - val2;
      Double_t thisErr = 0.;
      thisVal = 2. * thisVal/TMath::Log(val1/val2);
      
      //WARNING: this is only valid when histogram is NOT normalized per 1GeV!
      Double_t err1(0.),err2(0.);
      if(val1 > 0) err1 = TMath::Sqrt(val1);
      if(val2 > 0) err2 = TMath::Sqrt(val2);
      //Patrick: (quadratic addition of squares of errors - Gauß'sche Fehlerfortpflanzung)
      //thisErr =  sqrt((val2/sqrt(val1*val2))*err1*(val2/sqrt(val1*val2))*err1 + (val1/sqrt(val1*val2))*err2*(val1/sqrt(val1*val2))*err2);
      // can be written shorter, because err=sqrt(val):
      thisErr =  TMath::Sqrt(err2 * err2 + err1 * err1);
      if(thisVal > 0) 
        hLS->SetBinContent(globalbin,thisVal);
      else { 
        hLS->SetBinContent(globalbin,(val1+val2));
        if(hLS->GetXaxis()->GetBinCenter(bx)<=0.6 && hLS->GetYaxis()->GetBinCenter(by)<=0.4) counter++;
        //std::cout << "global bin: " << globalbin << std::endl;
        //std::cout << "x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << std::endl;
      }
      
      hLS->SetBinError(globalbin,thisErr);
    }
  }
  std::cout << counter << " procent arithmetric  " << newname << std::endl;
  return hLS;
}




//_______________________________________________________________________________________________
TH2D* LmBackground::CalcLSBackgroundHybrid(const TH2D* hPP, const TH2D* hMM, const Char_t* newname)
{
  /// Use geometric calculation only if both bins have non-zero entries
  LmHelper::Debug(" CalcLSBackgroundHybrid()", 5);
  TH2D* hLS = (TH2D*) (hPP->Clone(newname));
  //TH2D* hLS = dynamic_cast<TH2D*>(hPP->Clone(newname));
 
  Double_t counter = 0; 
  Int_t globalbin=0;
  for (Int_t bx=1;bx <= hLS->GetNbinsX(); bx++) {
    for (Int_t by=1;by <= hLS->GetNbinsY(); by++) {
      Double_t mMass = hLS->GetXaxis()->GetBinCenter(bx);
      Double_t mPt   = hLS->GetYaxis()->GetBinCenter(by);
      if(0.5*(TMath::Sqrt(mMass*mMass + mPt*mPt) - 2*0.0005109989) < 0.075) continue;
      
      globalbin=hLS->GetBin(bx,by);
      //LS = PP+MM = 2*sqrt(PP*MM);
      Double_t val1 = hPP->GetBinContent(globalbin);
      Double_t val2 = hMM->GetBinContent(globalbin);

      //if(hLS->GetXaxis()->GetBinCenter(bx) <= 0.6 && hLS->GetYaxis()->GetBinCenter(by) <= 0.4)
      //   std::cout << "-->>x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << "   binc: " << val1 << " " << val2 << "  A: " << (1-val1/val2)/2 << std::endl;
      //else
      //  std::cout << "x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << "   binc: " << val1 << " " << val2 << "  A: " << (1-val1/val2)/2 << std::endl;

      Double_t thisVal = val1 * val2;
      Double_t thisErr = 0.;
      thisVal = 2. * TMath::Sqrt(thisVal);
      
      //WARNING: this is only valid when histogram is NOT normalized per 1GeV!
      Double_t err1(0.),err2(0.);
      if(val1 > 0) err1 = TMath::Sqrt(val1);
      if(val2 > 0) err2 = TMath::Sqrt(val2);
      //Patrick: (quadratic addition of squares of errors - Gauß'sche Fehlerfortpflanzung)
      //thisErr =  sqrt((val2/sqrt(val1*val2))*err1*(val2/sqrt(val1*val2))*err1 + (val1/sqrt(val1*val2))*err2*(val1/sqrt(val1*val2))*err2);
      // can be written shorter, because err=sqrt(val):
      thisErr =  TMath::Sqrt(err2 * err2 + err1 * err1);
      if(thisVal > 0) 
        hLS->SetBinContent(globalbin,thisVal);
      else { 
        hLS->SetBinContent(globalbin,(val1+val2));
        if(hLS->GetXaxis()->GetBinCenter(bx)<=0.6 && hLS->GetYaxis()->GetBinCenter(by)<=0.4) counter++;
        //std::cout << "global bin: " << globalbin << std::endl;
        //std::cout << "x: " << hLS->GetXaxis()->GetBinCenter(bx) << "  y: " <<  hLS->GetYaxis()->GetBinCenter(by) << std::endl;
      }
      
      hLS->SetBinError(globalbin,thisErr);
    }
  }
  std::cout << counter << " procent arithmetric  " << newname << std::endl;
  return hLS;
}

//_______________________________________________________________________________________________
TH2D* LmBackground::CalcLSBackgroundGeom(const TH2D* hPP, const TH2D* hMM, const Char_t* newname) 
{
  LmHelper::Debug(" CalcLSBackgroundGeom()", 5);
  TH2D* hLS = (TH2D*) (hPP->Clone(newname));
  //TH2D* hLS = dynamic_cast<TH2D*>(hPP->Clone(newname));
  
  for (Int_t bx=0;bx <= hLS->GetNbinsX()+1; bx++) {
    for (Int_t by=0;by <= hLS->GetNbinsY()+1; by++) {
      Int_t globalbin=hLS->GetBin(bx,by);
      //LS = 2*sqrt(PP*MM);
      Double_t val1 = hPP->GetBinContent(globalbin);
      Double_t val2 = hMM->GetBinContent(globalbin);
      Double_t thisVal = val1 * val2;
      thisVal = 2. * TMath::Sqrt(thisVal);
      //WARNING: this is only valid when histogram is NOT normalized per 1GeV!
      Double_t err1(0.),err2(0.);
      if(val1 > 0) err1 = TMath::Sqrt(val1);
      if(val2 > 0) err2 = TMath::Sqrt(val2);
      //Patrick: (addition of squares of errors - Gauß'sche Fehlerfortpflanzung)
      //thisErr =  sqrt((val2/sqrt(val1*val2))*err1*(val2/sqrt(val1*val2))*err1 + (val1/sqrt(val1*val2))*err2*(val1/sqrt(val1*val2))*err2);
      // can be written shorter, because err=sqrt(val):
      Double_t thisErr = TMath::Sqrt(err2 * err2 + err1 * err1);
      
      hLS->SetBinContent(globalbin,thisVal);
      hLS->SetBinError(globalbin,thisErr);
    }
  }
  return hLS;
}

//_______________________________________________________________________________________________
TH2D* LmBackground::CalcLSBackgroundArith(const TH2D* hPP, const TH2D* hMM, const Char_t* newname)
{
  LmHelper::Debug(" CalcLSBackgroundArith()", 5);
  TH2D* hLS = (TH2D*) (hPP->Clone(newname));
  //TH2D* hLS = dynamic_cast<TH2D*>(hPP->Clone(newname));
  
  for (Int_t bx=0;bx <= hLS->GetNbinsX()+1; bx++) {
    for (Int_t by=0;by <= hLS->GetNbinsY()+1; by++) {
      Int_t globalbin=hLS->GetBin(bx,by);
      //LS = PP+MM;
      Double_t val1 = hPP->GetBinContent(globalbin);
      Double_t val2 = hMM->GetBinContent(globalbin);
      Double_t thisVal = val1 + val2;
		  //WARNING: this is only valid when histogram is NOT normalized per 1GeV!
			Double_t err1 = TMath::Sqrt(val1);
			Double_t err2 = TMath::Sqrt(val2);
			Double_t thisErr = TMath::Sqrt(err2 * err2 + err1 * err1);
			
      hLS->SetBinContent(globalbin,thisVal);
      hLS->SetBinError(globalbin,thisErr);
    }
  }
  return hLS;
}

// MAKE SURE to change 1D and 2D functions consistently! (or write it smarter...)
//_______________________________________________________________________________________________
TH2D* LmBackground::CalcRfactorByDiv2D(const TH2D* hNum, const TH2D* hDenom, const Char_t* newname) 
{
  LmHelper::Debug(" CalcRfactorByDiv2D()", 5);
  TH2D* hRfactorByDiv = (TH2D*) (hNum->Clone(newname));
  hRfactorByDiv->Divide(hDenom);
	hRfactorByDiv->SetZTitle("N^{mix}_{+-} / (2 #sqrt{ N^{mix}_{++} N^{mix}_{--} }) ");
	hRfactorByDiv->SetTitle("N^{mix}_{+-} / (2 #sqrt{ N^{mix}_{++} N^{mix}_{--} }) ");
  return hRfactorByDiv;
}
//_______________________________________________________________________________________________
TH1D* LmBackground::CalcRfactorByDiv1D(const TH1D* hNum, const TH1D* hDenom, const Char_t* newname) 
{
  /// This function is used inside LmSignal::MakeSpectra1D_Mee()/Ptee().
  /// NOTE: The 1D Rfactors are not created from the 2D Rfactor which may use a unity range! (never project ratios!)
  ///       This would need to be done directly inside this function by using copies of the 2D mixed-event histograms,
  ///       setting their content to zero where the 2D Rfactor shall be unity, then projecting the needed y-slices,
  ///       dividing them, and setting the rest of the Rfactor to 1. (still wrong for x-bins where part of the y-slice is affected)
  LmHelper::Debug("  CalcRfactorByDiv1D()", 6); //(two spaces to match with all LmSignal debugs for 1D projections.)
  TH1D* hRfactorByDiv = (TH1D*) (hNum->Clone(newname));
  hRfactorByDiv->Divide(hDenom);
	hRfactorByDiv->SetYTitle("N^{mix}_{+-} / (2 #sqrt{ N^{mix}_{++} N^{mix}_{--} }) ");
	hRfactorByDiv->SetTitle("N^{mix}_{+-} / (2 #sqrt{ N^{mix}_{++} N^{mix}_{--} }) ");
  return hRfactorByDiv;
}


//_______________________________________________________________________________________________
TH2D* LmBackground::CorrectByRfactor(const TH2D* hLS, const TH2D* hRfac, const Char_t* newname) 
{
  LmHelper::Debug(" CorrectByRfactor()", 5);
  TH2D* hCorrected = (TH2D*) (hLS->Clone(newname));
  hCorrected->Multiply(hRfac);
  return hCorrected;
}

//_______________________________________________________________________________________________
void LmBackground::PrintBkg2D(const Char_t* filename) 
{
  TCanvas* bkg = new TCanvas("bkg", "bkg");
  bkg->cd();
  LmHelper::TH2_Beautify(GetBkg2D(), bkg);
  GetBkg2D()->DrawCopy("colz");
  bkg->Print(filename);
  delete bkg;
}

//_______________________________________________________________________________________________
void LmBackground::PrintRfactor2D(const Char_t* filename) 
{
  TCanvas* rfactor = new TCanvas("rfactor", "rfactor");
  rfactor->cd();
  LmHelper::TH2_Beautify(GetRfactor2D(), rfactor);
  GetRfactor2D()->DrawCopy("colz");
  rfactor->Print(filename);
  delete rfactor;
}
