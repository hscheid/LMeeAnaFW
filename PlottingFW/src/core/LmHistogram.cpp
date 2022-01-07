// c++ includes
#include <vector>
using namespace std;
// ROOT includes
#include "TCanvas.h"
#include "TH1.h"
#include "TArrow.h"
#include "TPad.h" //for gPad
#include "TMath.h"
#include "TObjArray.h"
// project includes
#include "LmHistogram.h"
#include "LmHelper.h"

TString LmHistogram::fDrawOptionsDefault = "p E1 same;p E2 same;p E[] same"; // E[] or E5? did not check what looks nice.


//_______________________________________________________________________________________________
LmHistogram::LmHistogram():
fIsRatio(kFALSE),
fDatahist(0x0),
fSystErr(0x0),
fSystErrCorrel(0x0),
fArrow(),
fArrowBinWidth(),
fExternalObj(0x0),
fExternalSystematicObj(0x0),
fDrawOptions("")
{
  /// @brief Default Constructor
  //LmHelper::Debug("LmHistogram default constructor", 5);
}

//_______________________________________________________________________________________________
LmHistogram::LmHistogram(TH1D* datapoints) :
fIsRatio(kFALSE),
fDatahist(datapoints), // Original histogram is not copied. Avoids to delete many pointers in LmSignal::MakeSpectra1D_Mee/Ptee().
fSystErr(0x0),
fSystErrCorrel(0x0),
fArrow(),
fArrowBinWidth(),
fExternalObj(0x0),
fExternalSystematicObj(0x0),
fDrawOptions("")
{
  /// @brief Constructor from TH1D
  //LmHelper::Debug("LmHistogram constructor from TH1D", 5);
  fDatahist->SetStats(kFALSE);
}

//_______________________________________________________________________________________________
LmHistogram::LmHistogram(const LmHistogram &obj) :
fIsRatio(obj.fIsRatio),
fDatahist(0x0), // the following would just transfer the pointer - not what we want!: fDatahist(obj.fDatahist),
fSystErr(0x0),
fSystErrCorrel(0x0),
fArrow(obj.fArrow),
fArrowBinWidth(obj.fArrowBinWidth),
fExternalObj(obj.fExternalObj), // it would be better to do copies...
fExternalSystematicObj(obj.fExternalSystematicObj), // it would be better to do copies...
fDrawOptions(obj.fDrawOptions)
{
  /// @brief Copy Constructor
  LmHelper::Debug("LmHistogram copy constructor", 5);
  if (obj.fDatahist)      SetDatapoints(obj.fDatahist);
  if (obj.fSystErr)       SetSystError(obj.fSystErr);
  if (obj.fSystErrCorrel) SetSystErrorCorrel(obj.fSystErrCorrel);
}

//_______________________________________________________________________________________________
LmHistogram::~LmHistogram(){
  if (fDatahist)              delete fDatahist;
  if (fSystErr)               delete fSystErr;
  if (fSystErrCorrel)         delete fSystErrCorrel;
  if (fExternalObj)           delete fExternalObj;
  if (fExternalSystematicObj) delete fExternalSystematicObj;
  fArrow.clear();
  fArrowBinWidth.clear();
}


//_______________________________________________________________________________________________
LmHistogram::enBinning LmHistogram::CheckCompatibleBinning(const TH1D* h1, const TH1D* h2)
{
  /// Checks if h2 can be rebinned into the binning of h1. So each bin edge of h1 must be available in h2.
  /// Return values can be LmHistogram::kIdentical, ::kCompatible, ::kIncompatible.
  int localdebug=0;
  Double_t epsilon=1.E-6;
  LmHelper::Debug(Form("LmHistogram::CheckCompatibleBinning()"), 5-localdebug);
  Double_t bins1[1001]; // gives subtle/varying errors when using Double_t*
  Double_t bins2[1001];
  Int_t nbins1 = h1->GetNbinsX();
  Int_t nbins2 = h2->GetNbinsX();
  h1->GetXaxis()->GetLowEdge(bins1);
  h2->GetXaxis()->GetLowEdge(bins2);
  bins1[nbins1] = h1->GetXaxis()->GetBinUpEdge(nbins1); // need to fill last bin edge manually.
  bins2[nbins2] = h2->GetXaxis()->GetBinUpEdge(nbins2); // need to fill last bin edge manually.
  // for each bin edge of h1 we search for a match in h2.
  Bool_t foundmatch=kFALSE, compatible=kTRUE;
  Int_t  j_match_h2=-1; // stores the matching j of the previous bin, so that the nested loop can start there instead of from 0).
  for (int i=0; i<=nbins1; ++i) { // i<=nbins1 includes up edge of last bin.
    //cout << "bins1[i] = " << bins1[i] << endl;
    foundmatch = kFALSE;
    for (int j=j_match_h2+1; j<=nbins2; ++j) { // j<=nbins2 includes up edge of last bin.
      if (TMath::Abs(bins1[i]-bins2[j]) < epsilon) {
        foundmatch = kTRUE;
        j_match_h2 = j;
        break;
      }
    }
    if (!foundmatch) {
      LmHelper::Error(Form("LmHistogram::CheckCompatibleBinning(): no match in '%s' found for bin edge %.2f of '%s' (bin %i).",h2->GetName(),bins1[i],h1->GetName(),i));
      compatible=kFALSE;
    }
  }
  if (compatible && nbins1==nbins2) return kIdentical;
  else if (compatible) return kCompatible;
  else LmHelper::Error(Form("LmHistogram: binning of histograms '%s' and '%s' is incompatible!",h1->GetName(),h2->GetName()));
  return kIncompatible;
}

//_______________________________________________________________________________________________
Bool_t LmHistogram::MakeIdenticalBinning(const TH1D* h1, TH1D &h2)
{
  /// Rebin h2 so that its binning matches with h1. Make sure bin edges are compatible, because TH1::Rebin() does not care.
  int localdebug=0;
  LmHelper::Debug(Form("LmHistogram::MakeIdenticalBinning()"), 5-localdebug);
  enBinning bincomp = CheckCompatibleBinning(h1, &h2); // sometimes this does not work if it was called before, don't know why!
  if (bincomp==kIdentical) return kTRUE;
  if (bincomp==kIncompatible) return kFALSE;

  Double_t bins1[1001]; // gives subtle/varying errors when using Double_t*
  Int_t nbins = h1->GetNbinsX();
  LmHelper::Debug(Form("  nbins = %i", nbins), 11-localdebug);
  h1->GetXaxis()->GetLowEdge(bins1);
  *(bins1 + nbins) = h1->GetXaxis()->GetBinLowEdge(nbins+1); // add lower edge of overflow bin to the array (done like in TAxis::GetLowEdge).
  // denormalize
  Double_t binwidth=0.;
  for (int i=1; i<=h2.GetNbinsX(); ++i) {
    binwidth = h2.GetBinWidth(i);
    h2.SetBinContent(i, h2.GetBinContent(i)*binwidth);
    h2.SetBinError  (i, h2.GetBinError(i)*binwidth);
  }
  // apply (variable) binning
  // If newname is blank (default), the current histogram is modified and a pointer to it is returned.
  //h2.Rebin(nbins, "", bins1); // this does not modify the object in the calling function, so it's useless.
  h2 = *( (TH1D*) h2.Rebin(nbins, "", bins1) );
  //cout << " h2.GetNbinsX() = " << h2.GetNbinsX() << endl;
  // normalize again
  h2.Scale(1., "width");
  LmHelper::Debug(Form("LmHistogram::MakeIdenticalBinning(): rebinning of '%s' completed.", const_cast<char*>(h2.GetName())), 10-localdebug);
  return kTRUE;
}


//_______________________________________________________________________________________________
Bool_t LmHistogram::Divide(/*const*/ LmHistogram* obj, TString option)
{
  return Divide( obj->GetDatahist(), option );
}

//_______________________________________________________________________________________________
Bool_t LmHistogram::Divide(const TH1D* obj, TString option)
{
  /// Divide all of the components of this LmHistogram by a TH1. Attempts are made to create compatible binnings.
  /// If option = "0": set errors of denominator to zero. Other divide options are passed to TH1::Divide(), but this
  /// seems to be limited to the "b" option to compute binomial errors. For more advanced error propagation, see
  /// TGraphAsymmErrors::Divide(). To use this, we would have to make 'fDatahist' a TGraphAsymmErrors when *this*
  /// LmHistogram is a ratio.
  /// Note: for Graphs the options may not be implemented yet, see LmHistogram::DivideGraph().
  int localdebug=0;
  LmHelper::Debug(Form("LmHistogram::Divide()"), 5-localdebug);
  Bool_t ok=kFALSE;
  enBinning bincomp=kUnchecked;

  TH1D* hdenom = new TH1D(*obj); // [...] does not copy the list of associated functions. Use TObject::Clone to make a full copy of an histogram.
  if(option.EqualTo("0")){
    for (Int_t iBin = 0; iBin <= hdenom->GetNbinsX(); ++iBin) hdenom->SetBinError(iBin,0.);
  }

  // __________ Rebin denominator if needed __________
  bincomp = CheckCompatibleBinning(fDatahist,  hdenom);
  if(bincomp==kIncompatible) {
    LmHelper::Error(Form("LmHistogram::Divide(): denominator '%s' cannot be rebinned to match binning of datahist '%s'.",hdenom->GetName(),fDatahist->GetName()));
    ok = kFALSE;
  }
  if(bincomp==kCompatible) ok = MakeIdenticalBinning(fDatahist, *hdenom);
  if(bincomp==kIdentical)  ok = kTRUE;
  if (!ok) {
    LmHelper::Error(Form("LmHistogram::Divide(): an error occured. Skip division."));
    return kFALSE;
  }

  // __________ Divide datapoints __________
  LmHelper::Debug(Form(" divide datapoints"), 11-localdebug);
  if(option.EqualTo("0")){
    ok = fDatahist->Divide(fDatahist,hdenom,1.,1.);
  }
  else {
    ok = fDatahist->Divide(fDatahist,hdenom,1.,1.,option);
  }
  if (!ok) { LmHelper::Error(Form("LmHistogram: division of data histogram failed!")); return kFALSE; }

  // __________ Divide systematics graphs __________
  // They must have the same binning as fDatahist.
  LmHelper::Debug(Form(" divide systematics"), 11-localdebug);
  if (fSystErr)       DivideGraph(fSystErr, hdenom, option);
  if (fSystErrCorrel) DivideGraph(fSystErrCorrel, hdenom, option);

  // __________ Divide external objects __________
  if (fExternalObj) {
    if (fExternalObj->InheritsFrom(TH1::Class())) {
      TH1D* hdenomExt = new TH1D(*obj);
      bincomp = CheckCompatibleBinning((TH1D*)fExternalObj,  hdenomExt);
      if(bincomp==kIncompatible) {
        ok = kFALSE;
        LmHelper::Error(Form("LmHistogram::Divide(): denominator '%s' cannot be rebinned to match binning of external object '%s'.",hdenomExt->GetName(),fExternalObj->GetName()));
        //LmHelper::Error(Form("LmHistogram::Divide(): Deleting external object so that it is not drawn wrong."));
        //delete fExternalObj;
      }
      if(bincomp==kCompatible) ok = MakeIdenticalBinning((TH1D*)fExternalObj, *hdenomExt);
      if(bincomp==kIdentical)  ok = kTRUE;
      if (ok) {
        if(option.EqualTo("0")){ // perform external object division, depending on divide option.
          TH1D hdenomExt_tmp(*hdenomExt);
          for (Int_t iBin = 0; iBin <= hdenomExt_tmp.GetNbinsX(); ++iBin) hdenomExt_tmp.SetBinError(iBin,0.);
          ((TH1*)fExternalObj)->Divide((TH1*)fExternalObj,&hdenomExt_tmp,1.,1.);
        }
        else {
          ((TH1*)fExternalObj)->Divide((TH1*)fExternalObj,hdenomExt,1.,1.,option);
        }
      }
      delete hdenomExt;
    }
    if (fExternalSystematicObj) LmHelper::Warning(Form("LmHistogram::Divide(): division of external systematic object '%s' not implemented. Will be drawn wrong in ratio.",fExternalSystematicObj->GetName()));
  }

  // __________ Divide arrows __________
  LmHelper::Debug(Form(" divide arrows"), 11-localdebug);
  for (unsigned int i = 0; i < fArrow.size(); ++i) {
    if (localdebug>0) cout << " " << i << " " << flush;
    Double_t arrowY = fArrow.at(i)->GetY1();
    Double_t histY  = hdenom->GetBinContent( hdenom->FindBin(fArrow.at(i)->GetX1()) );
    fArrow.at(i)->SetY1(arrowY/histY);
    fArrow.at(i)->SetY2(arrowY/histY - 1.); // should be roughly ok for a ratio plot. final length to be determined when drawing...
  }

  SetIsRatio();
  delete hdenom;
  LmHelper::Debug(Form("LmHistogram::Divide(): done %s.", (ok?"OK":"NOT ok")), 10-localdebug);
  return ok;
}


//_______________________________________________________________________________________________
void LmHistogram::DivideGraph(TGraphAsymmErrors* gr, const TH1D* hDenominator, TString option)
{
  /// Manual division of a TGraphAsymmErrors by a TH1.
  /// @TODO: implement some divide options! Have a look at TGraphAsymmErrors::Divide().
  if (gr->GetN() != hDenominator->GetNbinsX()) { // this does not check bin edges!
    LmHelper::Error(Form("LmHistogram::DivideGraph(): systematics graph '%s' has incompatible binning!", gr->GetTitle()));
    return;
  }
  if (option.IsNull()) { } // nothing to do.
  else if (option.EqualTo("0")) { } // denominator errors are already set to zero inside LmHistogram::Divide().
  else if (option.Contains("b")) {
    LmHelper::Warning(Form("LmHistogram::DivideGraph(): binomial division not implemented for systematic error graphs. Will be inconsistent to statistical uncertainties."));
  }
  else LmHelper::Warning(Form("LmHistogram::DivideGraph(): divide option '%s' not implemented for systematic error graphs!",option.Data()));

  Double_t x, y, eylow, eyhigh;
  Double_t bc_denom/*, be_denom*/;
  for(Int_t iPoint = 0; iPoint < gr->GetN(); ++iPoint){
    gr->GetPoint(iPoint,x,y);
    eylow    = gr->GetErrorYlow(iPoint);
    eyhigh   = gr->GetErrorYhigh(iPoint);
    bc_denom = hDenominator->GetBinContent(iPoint+1);
    //be_denom = hDenominator->GetBinError(iPoint+1); // @TODO: take error of denominator into account.
    y      = (bc_denom > 0.) ? y      / bc_denom : 0.;
    eylow  = (bc_denom > 0.) ? eylow  / bc_denom : 0.;
    eyhigh = (bc_denom > 0.) ? eyhigh / bc_denom : 0.;
    gr->SetPoint(iPoint,x,y);
    gr->SetPointError(iPoint,gr->GetErrorXlow(iPoint),gr->GetErrorXhigh(iPoint),eylow,eyhigh);
  }
}


//_______________________________________________________________________________________________
Bool_t LmHistogram::Subtract(const TH1D* obj, const TGraphAsymmErrors* err, Double_t weight, TString option)
{
  /// Calls LmHistogram::Add() with opposite weight, see doc there.
  return Add(obj, err, -weight, option);
}

//_______________________________________________________________________________________________
Bool_t LmHistogram::Add(const TH1D* obj, const TGraphAsymmErrors* err, Double_t weight, TString option)
{
  /// Add/Subtract all of the components of this LmHistogram by a TH1. Attempts are made to create compatible binnings.
  /// If option = "0": set errors of summand/subtrahend to zero.
  /// Note: for Graphs the functionality may not be implemented yet, see LmHistogram::AddGraph().
  ///
  /// @TODO: decide how to apply the uncertainty from 'err' to the result and implement it.

  int localdebug=0;
  LmHelper::Debug(Form("LmHistogram::Add/Subtract()"), 5-localdebug);
  Bool_t ok=kFALSE;
  enBinning bincomp=kUnchecked;
  
  TH1D* hsummand = new TH1D(*obj); // [...] does not copy the list of associated functions. Use TObject::Clone to make a full copy of an histogram.
  if(option.EqualTo("0")){
    for (Int_t iBin = 0; iBin <= hsummand->GetNbinsX(); ++iBin) hsummand->SetBinError(iBin,0.);
  }
  if (err!=0x0) LmHelper::Warning(Form("LmHistogram::Add(): uncertainty of summand/subtrahend '%s' will not be propagated to datahist '%s'. please implement!",hsummand->GetName(),fDatahist->GetName()));
  /// ^^^^^^^^^^ see LmHandler::SubtractCocktail() for an alternative suggestion in case of cocktail subtraction. ^^^^^^^^^^
  
  // __________ Rebin summand/subtrahend if needed __________
  bincomp = CheckCompatibleBinning(fDatahist,  hsummand);
  if(bincomp==kIncompatible) {
    LmHelper::Error(Form("LmHistogram::Add(): summand/subtrahend '%s' cannot be rebinned to match binning of datahist '%s'.",hsummand->GetName(),fDatahist->GetName()));
    ok = kFALSE;
  }
  if(bincomp==kCompatible) ok = MakeIdenticalBinning(fDatahist, *hsummand);
  if(bincomp==kIdentical)  ok = kTRUE;
  if (!ok) {
    LmHelper::Error(Form("LmHistogram::Add(): an error occured. Skip calculation."));
    return kFALSE;
  }
  
  // __________ Add/Subtract datapoints __________
  LmHelper::Debug(Form(" Add/Subtract datapoints"), 11-localdebug);
  ok = fDatahist->Add(hsummand, weight);
  if (!ok) { LmHelper::Error(Form("LmHistogram: addition to/subtraction from data histogram failed!")); return kFALSE; }
  
  // __________ Add/Subtract systematics graphs __________
  // They must have the same binning as fDatahist.
  LmHelper::Debug(Form(" Add/Subtract systematics"), 11-localdebug);
  if (fSystErr)       AddGraph(fSystErr, hsummand, weight, option);
  if (fSystErrCorrel) AddGraph(fSystErrCorrel, hsummand, weight, option);
  
  // __________ Add/Subtract external objects __________
  // @TODO [...]
  
  // __________ Add/Subtract arrows __________
  // @TODO [...]
  
  delete hsummand;
  LmHelper::Debug(Form("LmHistogram::Add(): done %s.", (ok?"OK":"NOT ok")), 10-localdebug);
  return ok;
}

//_______________________________________________________________________________________________
void LmHistogram::AddGraph(TGraphAsymmErrors* gr, const TH1D* hSummand, Double_t weight, TString option)
{
  std::cout << "LmHistogram::AddGraph(): systematics graph: weight:" << weight << "  option: " << option << std::endl;
  /// Manual addition/subtraction of a TGraphAsymmErrors and a TH1.
  if (gr->GetN() != hSummand->GetNbinsX()) { // this does not check bin edges!
    LmHelper::Error(Form("LmHistogram::AddGraph(): systematics graph '%s' has incompatible binning!", gr->GetTitle()));
    return;
  }
  if (option.IsNull()) { } // nothing to do.
  else if (option.EqualTo("0")) { } // summand errors are already set to zero inside LmHistogram::Add().
  else LmHelper::Warning(Form("LmHistogram::AddGraph(): add/subtract option '%s' not implemented for systematic error graphs!",option.Data()));
  
  Double_t x, y, eylow, eyhigh, exlow, exhigh;
  Double_t bc_summand/*, be_summand*/;
  for(Int_t iPoint = 0; iPoint < gr->GetN(); ++iPoint){
    gr->GetPoint(iPoint,x,y);
    eylow = gr->GetErrorYlow(iPoint);
    exlow = gr->GetErrorXlow(iPoint);
    eyhigh = gr->GetErrorYhigh(iPoint);
    exhigh = gr->GetErrorXhigh(iPoint);

    bc_summand = hSummand->GetBinContent(iPoint+1);
    //be_summand = hSummand->GetBinError(iPoint+1); // @TODO: take error of summand into account.
    std::cout << "x: " << x << "  y:" << y << "  bc_summand: " << bc_summand << std::endl;
    y      = y      + bc_summand * weight;
    eylow = sqrt(eylow*eylow + (bc_summand*0.11)*(bc_summand*0.11));
    eyhigh = sqrt(eyhigh*eyhigh + (bc_summand*0.11)*(bc_summand*0.11));

    gr->SetPoint(iPoint,x,y);
    gr->SetPointError(iPoint,exlow, exhigh, eylow, eyhigh);
    // the errors are deltas relative to the point, so we dont need to add/subtract the new bin content to them.
  }
}

//_______________________________________________________________________________________________
void LmHistogram::DrawCopy(const char* options)
{
  Draw(options);
}

//_______________________________________________________________________________________________
void LmHistogram::DrawClone(const char* options)
{
  Draw(options);
}

//_______________________________________________________________________________________________
void LmHistogram::Draw(const char* options)
{
  LmHelper::Debug(Form("LmHistogram::Draw('%s')", options), 5);

  TObjArray* oaDefault = TString(fDrawOptionsDefault).Tokenize(";");
  if (oaDefault->GetEntriesFast() < 3) {
    LmHelper::Error("LmHistogram::Draw(): Please use SetDrawOptionsStatic(const char* options) with 3 arguments (eg: \"p E1 same;p E2 same;p E[] same\") for the drawing style");
  }
  TString dataOpt   = oaDefault->At(0)->GetName();
  TString sysOpt    = oaDefault->At(1)->GetName();
  TString syscorOpt = oaDefault->At(2)->GetName(); // E[] or E5? did not check what looks nice.
  TString extOpt(dataOpt);
  TString extsysOpt(sysOpt);

  TObjArray* oaOpt = TString(options).Tokenize(";");
  if (oaOpt->GetEntries()>0) dataOpt   = oaOpt->At(0)->GetName();
  if (oaOpt->GetEntries()>1) sysOpt    = oaOpt->At(1)->GetName();
  if (oaOpt->GetEntries()>2) syscorOpt = oaOpt->At(2)->GetName();
  if (oaOpt->GetEntries()>3) extOpt    = oaOpt->At(3)->GetName();
  if (oaOpt->GetEntries()>4) extsysOpt = oaOpt->At(4)->GetName();

  TObjArray* oaCustomOpt = TString(fDrawOptions).Tokenize(";");
  if (oaCustomOpt->GetEntries()>0 && !TString(oaCustomOpt->At(0)->GetName()).EqualTo("-")) dataOpt   = oaCustomOpt->At(0)->GetName();
  if (oaCustomOpt->GetEntries()>1 && !TString(oaCustomOpt->At(1)->GetName()).EqualTo("-")) sysOpt    = oaCustomOpt->At(1)->GetName();
  if (oaCustomOpt->GetEntries()>2 && !TString(oaCustomOpt->At(2)->GetName()).EqualTo("-")) syscorOpt = oaCustomOpt->At(2)->GetName();
  if (oaCustomOpt->GetEntries()>3) extOpt    = oaCustomOpt->At(3)->GetName();
  if (oaCustomOpt->GetEntries()>4) extsysOpt = oaCustomOpt->At(4)->GetName();

  // Special case when only the axis shall be (re)drawn
  if (dataOpt.EqualTo("axis",TString::kIgnoreCase) ||
      dataOpt.EqualTo("axis same",TString::kIgnoreCase)) {
    //fDatahist->SetBarWidth(2);
    fDatahist->DrawCopy(dataOpt.Data());
    return;
  }

  // Special case when only systematics shall be (re)drawn (maybe in case of first histogram in ratio plot?)
  Bool_t bOnlySys = (dataOpt.Contains("onlysys",TString::kIgnoreCase));
  if (bOnlySys) {
    sysOpt.Remove(TString::kLeading, 'p');
    syscorOpt.Remove(TString::kLeading, 'p');
  }

  if (!bOnlySys) DrawArrows();

  if (fDatahist && !bOnlySys) fDatahist->DrawCopy(dataOpt.Data());
  if (fSystErr)               fSystErr->DrawClone(sysOpt.Data());
  if (fSystErrCorrel)         fSystErrCorrel->DrawClone(syscorOpt.Data());

  if (fExternalObj)           fExternalObj->DrawClone(extOpt.Data());
  if (fExternalSystematicObj) fExternalSystematicObj->DrawClone(extsysOpt.Data());

  
}

//_______________________________________________________________________________________________
void LmHistogram::DrawArrows()
{
  LmHelper::Debug(Form("LmHistogram::DrawArrows() [total=%i]", (int)fArrow.size()), 10);

  for (unsigned int i = 0; i < fArrow.size(); ++i)
  {
    //cout << " " << i << " " << flush;
    Double_t xMin = fDatahist->GetBinLowEdge( fDatahist->GetXaxis()->GetFirst() );
    Double_t xMax = fDatahist->GetBinLowEdge( fDatahist->GetXaxis()->GetLast()+1 );
    //    printf("GetFirst = %i , xMin = %f \n", fDatahist->GetXaxis()->GetFirst(), xMin);
    //    printf("GetLast  = %i , xMax = %f \n", fDatahist->GetXaxis()->GetLast(), xMax);

    // compute and draw arrow only if it is within the current x-range!
    if (fArrow.at(i)->GetX1() > xMax || fArrow.at(i)->GetX1() < xMin ) continue;

    // calculate arrow width, which is measured in percent of the pad height. (according to TArrow html)
    // we want it to be as wide as the empty histogram bin.
    // (actually, for vertical arrows their size is relative to the pad width - becomes clear in ratio pad.)
//    Double_t binwidth_inPercentOfHistRange = fArrowBinWidth.at(i) / (xMax-xMin);
    Double_t binwidth_inPercentOfHistRange = 0.015 / (xMax-xMin);
    //    printf(" binwidth_inPercentOfHistRange = %f \n", binwidth_inPercentOfHistRange);
    Double_t binwidth_inPercentOfPadWidth = binwidth_inPercentOfHistRange * (1. - gPad->GetLeftMargin() - gPad->GetRightMargin());
    //    printf(" binwidth_inPercentOfPadWidth  = %f \n", binwidth_inPercentOfPadWidth);
    // set the new size:
    fArrow.at(i)->SetArrowSize(binwidth_inPercentOfPadWidth);

    // calculate arrow length. we want it to be a fixed fraction of the y-range.
    Double_t fraction = 0.2;
    if (fIsRatio) fraction = 0.30;
    //    Double_t yMax = gPad->GetUymax(); // doesnt work
    //    Double_t yMin = gPad->GetUymin();
    Double_t yMax = fDatahist->GetMaximum(); // the real plot range is always a bit larger (especially due to errorbars)...
    Double_t yMin = fDatahist->GetMinimum(); //
    Double_t y1   = fArrow.at(i)->GetY1();
    Double_t y2   = fArrow.at(i)->GetY2();
    //    printf("yMax = %f \n", yMax);
    //    printf("yMin = %f \n", yMin);
    //    printf("y1   = %f \n", y1);

    if (gPad->GetLogy()) {
      yMax = TMath::Log10(yMax);
      yMin = fDatahist->GetMinimum(0.); // recompute: minimum, but larger than 0!
      yMin = TMath::Log10(yMin);
      y1   = TMath::Log10(y1);
      //      printf("log yMax = %f \n", yMax);
      //      printf("log yMin = %f \n", yMin);
      //      printf("log y1   = %f \n", y1);
    }
    // calculate y2
    y2 = y1 - fraction*(yMax-yMin);
    fDatahist->SetBinContent(fDatahist->FindBin(fArrow.at(i)->GetX1()),0.00000001 );
    if(fSystErr)
      fSystErr->SetPoint(fDatahist->FindBin(fArrow.at(i)->GetX1())-1,fArrow.at(i)->GetX1(),0.00000001);

    //if(fIsRatio) std::cout << "IsRatio" << std::endl;
    //printf("y2   = %f \n", y2);

    if (gPad->GetLogy()) {
      y2   = TMath::Power(10, y2);
      //      printf("un-log-ed y2   = %f \n", y2);
    }
    fArrow.at(i)->SetY2(y2);

    // draw arrow
    fArrow.at(i)->DrawClone(); // "same" not needed. will overwrite arrow options!
  }
  //cout << " " << endl;
}


//_______________________________________________________________________________________________
void LmHistogram::SetAxisRange(Double_t xmin, Double_t xmax, const char* axis){
  std::cout << "yyyip " << xmin << "  " << xmax << std::endl;
  fDatahist->SetAxisRange(xmin, xmax, axis);
}

//_______________________________________________________________________________________________
void LmHistogram::SetLineColor(Int_t color){
  fDatahist->SetLineColor(color);
  if (fSystErr)       fSystErr      ->SetLineColor(color);
  if (fSystErrCorrel) fSystErrCorrel->SetLineColor(color);
  for (unsigned int i = 0; i < fArrow.size(); ++i){
    fArrow.at(i)->SetLineColor(color);
  }
}

//_______________________________________________________________________________________________
void LmHistogram::SetLineWidth(Int_t lwidth){
  fDatahist->SetLineWidth(lwidth);
  if (fSystErr)       fSystErr      ->SetLineWidth(lwidth);
  if (fSystErrCorrel) fSystErrCorrel->SetLineWidth(lwidth);
  for (unsigned int i = 0; i < fArrow.size(); ++i){
    fArrow.at(i)->SetLineWidth(lwidth);
  }
}

//_______________________________________________________________________________________________
void LmHistogram::SetLineStyle(Int_t lstyle){
  fDatahist->SetLineStyle(lstyle);
  if (fSystErr)       fSystErr      ->SetLineStyle(lstyle);
  if (fSystErrCorrel) fSystErrCorrel->SetLineStyle(lstyle);
  for (unsigned int i = 0; i < fArrow.size(); ++i){
    fArrow.at(i)->SetLineStyle(lstyle);
  }
}

//_______________________________________________________________________________________________
void LmHistogram::SetMarkerStyle(Int_t marker){
  fDatahist->SetMarkerStyle(marker);
  if (fSystErr)       fSystErr      ->SetMarkerStyle(marker);
  if (fSystErrCorrel) fSystErrCorrel->SetMarkerStyle(marker);

}

//_______________________________________________________________________________________________
void LmHistogram::SetMarkerColor(Int_t color){
  fDatahist->SetMarkerColor(color);
  if (fSystErr)       fSystErr      ->SetMarkerColor(color);
  if (fSystErrCorrel) fSystErrCorrel->SetMarkerColor(color);
}

//_______________________________________________________________________________________________
void LmHistogram::SetMarkerSize(Double_t size){
  fDatahist->SetMarkerSize(size);
  if (fSystErr)       fSystErr      ->SetMarkerSize(size);
  if (fSystErrCorrel) fSystErrCorrel->SetMarkerSize(size);
}

//_______________________________________________________________________________________________
void LmHistogram::SetFillStyle(Int_t fstyle){
  fDatahist->SetFillStyle(fstyle);
  if (fSystErr)       fSystErr      ->SetFillStyle(fstyle);
  if (fSystErrCorrel) fSystErrCorrel->SetFillStyle(fstyle);
}

//_______________________________________________________________________________________________
void LmHistogram::SetFillColorAlpha(Int_t color, Int_t alpha){
  fDatahist->SetFillColorAlpha(color, alpha);
  if (fSystErr)       fSystErr      ->SetFillColorAlpha(color, alpha);
  if (fSystErrCorrel) fSystErrCorrel->SetFillColorAlpha(color, alpha);
}

//_______________________________________________________________________________________________
void LmHistogram::SetFillColor(Int_t color){
  fDatahist->SetFillColor(color);
  if (fSystErr)       fSystErr      ->SetFillColor(color);
  if (fSystErrCorrel) fSystErrCorrel->SetFillColor(color);
}
