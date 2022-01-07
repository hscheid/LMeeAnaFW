// c++ includes
#include <iostream>
using namespace std;
// ROOT includes
#include "TH1.h"
#include "TH2.h"
#include "TAxis.h"
#include "TMath.h"
#include "TString.h"
// project includes
#include "LmBaseSignal.h"
#include "LmHelper.h"

// initialize static variables
TString     LmBaseSignal::fsInputCodeX("Mee");
TString     LmBaseSignal::fsInputCodeY("Ptee");
TString     LmBaseSignal::fsInputCodeZ("");
TString     LmBaseSignal::fsInputTexX("#it{m}_{ee}");
TString     LmBaseSignal::fsInputTexXunit("GeV/#it{c}^{2}");
TString     LmBaseSignal::fsInputTexY("#it{p}_{T,ee}");
TString     LmBaseSignal::fsInputTexYunit("GeV/#it{c}");
TString     LmBaseSignal::fsInputTexZ(""); // please leave empty for sanity checks
TString     LmBaseSignal::fsInputTexZunit("");
TString     LmBaseSignal::fsInputTexContent(""); // will be computed automatically
TString     LmBaseSignal::fsInputTexContentunit("a.u.");
LmBaseSignal::inputAxis   LmBaseSignal::fWhatIsX=kInputX;
LmBaseSignal::inputAxis   LmBaseSignal::fWhatIsY=kInputY;
LmBaseSignal::inputAxis   LmBaseSignal::fWhatIsZ=kInputZ;
TString     LmBaseSignal::fsLabelSig("#it{S}");
TString     LmBaseSignal::fsLabelBkg("#it{B}");

//_______________________________________________________________________________________________
TH1D* LmBaseSignal::DoProjectionMee(const TH2D* hIn, Double_t lowpT, Double_t highpT,/* Bool_t normBinw, Bool_t normNev, Bool_t normNent,*/ UInt_t normalisation, Bool_t debugTitles, std::vector<Double_t> *binning)
/// Even though the class contains the members fDoNormBinwidth and fDoNormNevents, do not remove these parameters from the function call!
/// They are needed to produce raw spectra with partial or no normalization to calculate the significance.
{
  //  cout << " DoProjectionMee()" << endl;
  const TAxis* yaxis=hIn->GetYaxis();
  Int_t firstbin  = yaxis->FindFixBin(lowpT); // FindFixBin: Identical to TAxis::FindBin except that if x is an underflow/overflow no attempt is made to extend the axis.
  Int_t lastbin   = yaxis->FindFixBin(highpT-LmHelper::kSmallDelta); // subtract a small delta because the upper bin edge already belongs to the next bin!
  if (lastbin>yaxis->GetNbins()) lastbin=yaxis->GetNbins(); // if 'lastbin' is overflow, 'GetBinUpEdge(lastbin)' calculates an arbitrary edge which may coincide with the requested edge.
  if (firstbin<1) firstbin=1; // less likely for underflow but to be save...
  if ( TMath::Abs(yaxis->GetBinLowEdge(firstbin)-lowpT) > LmHelper::kSmallDelta )
    LmHelper::Warning( Form("LmBaseSignal::DoProjectionMee(): lower edge (%f) doesn't match a bin edge (%f) of histogram '%s'. Fix it!", lowpT, yaxis->GetBinLowEdge(firstbin), hIn->GetName()) );
  if ( TMath::Abs(yaxis->GetBinUpEdge(lastbin)-highpT) > LmHelper::kSmallDelta )
    LmHelper::Warning( Form("LmBaseSignal::DoProjectionMee(): upper edge (%f) doesn't match a bin edge (%f) of histogram '%s'. Fix it!", highpT, yaxis->GetBinUpEdge(lastbin), hIn->GetName()) );

  TString newname(Form("%s_Mee_ptee%.2fto%.2f",hIn->GetName(),lowpT,highpT));
  // should give a unique name to each projection!
  // warning: when comparing projections from differet signals, this name will not be unique anymore! therefore we use the copy constructor:
  //  TH1D* hOut = new TH1D(*((TH1D*)hIn->ProjectionX(newname.Data(), hIn->GetYaxis()->FindBin(lowpT), hIn->GetYaxis()->FindBin(highpT)-1, "e"))); // withOut the -1, it is 1 bin too much. checked 10.2013 // but only correct if search value is a bin edge!
  //  TH1D* hOut = new TH1D(*((TH1D*)hIn->ProjectionX(newname.Data(), hIn->GetYaxis()->FindBin(lowpT), hIn->GetYaxis()->FindBin(highpT-LmHelper::kSmallDelta), "e"))); // subtract a small delta because the upper bin edge already belongs to the next bin!
  TH1D* hOut(0x0);
  if(binning){
   TH1D *htmp = new TH1D(*((TH1D*)hIn->ProjectionX("htmp", firstbin, lastbin, "e")));
   Double_t *binArr = &(*binning)[0];
   hOut = static_cast<TH1D*> (htmp->Rebin(binning->size()-1,newname.Data(),binArr));
   delete htmp;
  }
  else
    hOut = new TH1D(*((TH1D*)hIn->ProjectionX(newname.Data(), firstbin, lastbin, "e"))); // in use since 23.06.2016
  // these versions do NOT work withOut the SetName() below them!
  //TH1D* hOut = (TH1D*)hIn->ProjectionX(newname, hIn->GetYaxis()->FindBin(lowpT), hIn->GetYaxis()->FindBin(highpT)-1);
  //TH1D* hOut = (TH1D*)hIn->ProjectionX("_px", hIn->GetYaxis()->FindBin(lowpT), hIn->GetYaxis()->FindBin(highpT)-1);
  //hOut->SetName("blubb"); // if the projection doesnt have a unique name, then at least this stupid statement is needed to avoid overwriting!
  TString sTitle(hIn->GetZaxis()->GetTitle());
  sTitle.ReplaceAll(Form("d%s",GetProjLabelYvar().Data()),"");
  //sTitle.ReplaceAll("d#it{p}_{T,ee}",""); // old hardcoded
  // hOut->GetXaxis()->SetTitleOffset(1.2);
  hOut->SetYTitle(sTitle.Data());
  hOut->SetTitle(sTitle.Data());

  
  TH1D* hist = hOut;
  if (debugTitles) { // activate it in LmSignal::MakeSpectra1D_Mee()
    LmHelper::Debug(" LmBaseSignal::DoProjectionMee( debugTitles )", 3);
    LmHelper::Debug(Form("1|-> title: %s,   x: %s,   y: %s,   z: %s", hist->GetTitle(), hist->GetXaxis()->GetTitle(), hist->GetYaxis()->GetTitle(), hist->GetZaxis()->GetTitle()), 3);
  }
  if (normalisation & kNormBinWidth)    { NormalizeBinwidth(*hOut); /*std::cout << "+++++++++BinWidth " << kNormBinWidth << " - fNormalisation: " << normalisation << std::endl;*/ }
  hist = hOut;
  if (debugTitles) LmHelper::Debug(Form("2|-> title: %s,   x: %s,   y: %s,   z: %s", hist->GetTitle(), hist->GetXaxis()->GetTitle(), hist->GetYaxis()->GetTitle(), hist->GetZaxis()->GetTitle()), 3);
  if (normalisation & kNormNevents)     { NormalizeNevents(*hOut);      /*std::cout << "+++++++++Nevents " << kNormBinWidth << " - fNormalisation: " << normalisation << std::endl;*/}
  if (normalisation & kNormNentries)    { NormalizeNentries(*hOut);     /*std::cout << "+++++++++Nentries " << kNormBinWidth << " - fNormalisation: " << normalisation << std::endl;*/}
  if (normalisation & kNormRecEff)      { NormalizeRecEff(*hOut);       /*std::cout << "+++++++++RecEff " << kNormBinWidth << " - fNormalisation: " << normalisation << std::endl;*/}
  if (normalisation & kNormVtxRecEffee) { NormalizeVtxRecEffee(*hOut);  /*std::cout << "+++++++++VtxRecEffee " << kNormBinWidth << " - fNormalisation: " << normalisation << std::endl;*/}
  if (normalisation & kNormTrgEff)      { NormalizeTrgEff(*hOut);       /*std::cout << "+++++++++TrgEff " << kNormBinWidth << " - fNormalisation: " << normalisation << std::endl;*/}
  if (normalisation & kNormVtxRecEff)   { NormalizeVtxRecEff(*hOut);    /*std::cout << "+++++++++VtxRecEff " << kNormBinWidth << " - fNormalisation: " << normalisation << std::endl;*/}
  if (normalisation & kNormCrossSection){ NormalizeCrossSection(*hOut); /*std::cout << "+++++++++CrossSection " << kNormBinWidth << " - fNormalisation: " << normalisation << std::endl;*/}
  hist = hOut;
  if (debugTitles) LmHelper::Debug(Form("3|-> title: %s,   x: %s,   y: %s,   z: %s", hist->GetTitle(), hist->GetXaxis()->GetTitle(), hist->GetYaxis()->GetTitle(), hist->GetZaxis()->GetTitle()), 3);
  return hOut;
}


//_______________________________________________________________________________________________
TH1D* LmBaseSignal::DoProjectionPtee(const TH2D* hIn, Double_t lowMee, Double_t highMee, /*Bool_t normBinw, Bool_t normNev, Bool_t normNent,*/ UInt_t normalisation, Bool_t debugTitles, std::vector<Double_t> *binning)
/// Even though the class contains the members fDoNormBinwidth and fDoNormNevents, do not remove these parameters from the function call!
/// They are needed to produce raw spectra with partial or no normalization to calculate the significance.
{
  //  cout << " DoProjectionPtee()" << endl;
  const TAxis* xaxis=hIn->GetXaxis();
  Int_t firstbin  = xaxis->FindFixBin(lowMee); // FindFixBin: Identical to TAxis::FindBin except that if x is an underflow/overflow no attempt is made to extend the axis.
  Int_t lastbin   = xaxis->FindFixBin(highMee-LmHelper::kSmallDelta); // subtract a small delta because the upper bin edge already belongs to the next bin!
  if (lastbin>xaxis->GetNbins()) lastbin=xaxis->GetNbins(); // if 'lastbin' is overflow, 'GetBinUpEdge(lastbin)' calculates an arbitrary edge which may coincide with the requested edge.
  if (firstbin<1) firstbin=1; // less likely for underflow but to be save...
  if ( TMath::Abs(xaxis->GetBinLowEdge(firstbin)-lowMee) > LmHelper::kSmallDelta )
    LmHelper::Warning( Form("LmBaseSignal::DoProjectionPtee(): lower edge (%f) doesn't match a bin edge (%f) of histogram '%s'. Fix it!", lowMee, xaxis->GetBinLowEdge(firstbin), hIn->GetName()) );
  if ( TMath::Abs(xaxis->GetBinUpEdge(lastbin)-highMee) > LmHelper::kSmallDelta )
    LmHelper::Warning( Form("LmBaseSignal::DoProjectionPtee(): upper edge (%f) doesn't match a bin edge (%f) of histogram '%s'. Fix it!", highMee, xaxis->GetBinUpEdge(lastbin), hIn->GetName()) );

  TString newname(Form("%s_Ptee_mee%.2fto%.2f",hIn->GetName(),lowMee,highMee));
  //TH1D* hOut = new TH1D(*((TH1D*)hIn->ProjectionY(newname.Data(), hIn->GetXaxis()->FindBin(lowMee), hIn->GetXaxis()->FindBin(highMee-LmHelper::kSmallDelta), "e")));
  TH1D* hOut(0x0);
  if(binning){
   TH1D *htmp = new TH1D(*((TH1D*)hIn->ProjectionY("htmp", firstbin, lastbin, "e")));
   Double_t *binArr = &(*binning)[0];
   hOut = static_cast<TH1D*> (htmp->Rebin(binning->size()-1,newname.Data(),binArr));
   delete htmp;
  }
  else
    hOut = new TH1D(*((TH1D*)hIn->ProjectionY(newname.Data(), firstbin, lastbin, "e"))); // in use since 23.06.2016
  TString sTitle(hIn->GetZaxis()->GetTitle());
  sTitle.ReplaceAll(Form("d%s",GetProjLabelXvar().Data()),"");
  //sTitle.ReplaceAll("d#it{m}_{ee}","");
  hOut->SetYTitle(sTitle.Data());
  hOut->SetTitle(sTitle.Data());
  hOut->GetXaxis()->SetTitleOffset(1.25);

  TH1D* hist = hOut;
  if (debugTitles) { // activate it in LmSignal::MakeSpectra1D_Ptee()
    LmHelper::Debug(" LmBaseSignal::DoProjectionPtee( debugTitles )", 3);
    LmHelper::Debug(Form("1|-> title: %s,   x: %s,   y: %s,   z: %s", hist->GetTitle(), hist->GetXaxis()->GetTitle(), hist->GetYaxis()->GetTitle(), hist->GetZaxis()->GetTitle()), 3);
  }
  if (normalisation & kNormBinWidth)     NormalizeBinwidth(*hOut);
  hist = hOut;
  if (debugTitles) LmHelper::Debug(Form("2|-> title: %s,   x: %s,   y: %s,   z: %s", hist->GetTitle(), hist->GetXaxis()->GetTitle(), hist->GetYaxis()->GetTitle(), hist->GetZaxis()->GetTitle()), 3);
  if (normalisation & kNormNevents)      NormalizeNevents(*hOut);
  if (normalisation & kNormNentries)     NormalizeNentries(*hOut);
  if (normalisation & kNormRecEff)       NormalizeRecEff(*hOut);
  if (normalisation & kNormVtxRecEffee)  NormalizeVtxRecEffee(*hOut);
  if (normalisation & kNormTrgEff)       NormalizeTrgEff(*hOut);
  if (normalisation & kNormVtxRecEff)    NormalizeVtxRecEff(*hOut);
  if (normalisation & kNormCrossSection) NormalizeCrossSection(*hOut);
  hist = hOut;
  if (debugTitles) LmHelper::Debug(Form("3|-> title: %s,   x: %s,   y: %s,   z: %s", hist->GetTitle(), hist->GetXaxis()->GetTitle(), hist->GetYaxis()->GetTitle(), hist->GetZaxis()->GetTitle()), 3);
  return hOut;
}


//_______________________________________________________________________________________________
void LmBaseSignal::NormalizeBinwidth(TH1D& hIn)
{
//  cout << " NormalizeBinwidth()" << endl;
  hIn.Scale(1., "width"); //If option contains "width" the bin contents and errors are divided by the bin width.
  //
  TString sTitle(hIn.GetYaxis()->GetTitle());
  sTitle.ReplaceAll(" (a.u.)","");
  //if      (sTitle.Contains(GetProjLabelXvar())) { sTitle.Append( (TString)" ("+GetProjLabelXunit()+")^{-1}" ); } // old check based on y-axis label
  //else if (sTitle.Contains(GetProjLabelYvar())) { sTitle.Append( (TString)" ("+GetProjLabelYunit()+")^{-1}" ); }
  if      (CheckWhichProjection(&hIn)==kProjOnX) { sTitle.Append( (TString)" ("+GetProjLabelXunit()+")^{-1}" ); }
  else if (CheckWhichProjection(&hIn)==kProjOnY) { sTitle.Append( (TString)" ("+GetProjLabelYunit()+")^{-1}" ); }
  else {
    LmHelper::Warning(Form("LmBaseSignal::NormalizeBinwidth(): y-axis title ('%s') could not be automatically updated according to normalization. [Probably forgot to use SetInputLabelX/Y/Z() or SetInputLabelContent()]", hIn.GetYaxis()->GetTitle()));
    LmHelper::Warning(Form(" |-> hIn.GetName() = %s, hIn.GetTitle() = %s,\n              GetProjLabelXvar = %s, GetProjLabelYvar = %s, sTitle = %s", hIn.GetName(), hIn.GetTitle(), GetProjLabelXvar().Data(), GetProjLabelYvar().Data(), sTitle.Data()));
  }
  hIn.SetYTitle(sTitle.Data());
  hIn.SetTitle(sTitle.Data());
  return;
}


//_______________________________________________________________________________________________
void LmBaseSignal::NormalizeNevents(TH1D& hIn)
{
    cout << " NormalizeNevents()" << endl;
  Double_t nevents = GetNeventsPhysSel();

  std::cout << "&&&&&&&&&&& " << nevents << std::endl; 
  if (nevents > 1) hIn.Scale(1./nevents);
  else             { LmHelper::Warning(Form("LmBaseSignal::NormalizeNevents(): normalization not possible (nevents = %f). nothing done.",nevents)); return; }
  //
  const char* texNevents="1/#it{N}_{ev} ";
  // const char* texNevents="1/#it{N}_{ev}^{phys.sel.} ";
  TString sTitle(hIn.GetYaxis()->GetTitle());
  sTitle.Prepend(texNevents);
  hIn.SetYTitle(sTitle.Data());
  hIn.SetTitle(sTitle.Data());
  return;
}

//_______________________________________________________________________________________________
void LmBaseSignal::NormalizeNentries(TH1D& hIn)
{
    cout << " NormalizeNentries()" << endl;
  Double_t nentries = hIn.Integral();
  if (nentries > 1) hIn.Scale(1./nentries);
  else             { LmHelper::Warning(Form("LmBaseSignal::NormalizeNentries(): normalization not possible (nentries = %f). nothing done.",nentries)); return; }
  //
  const char* texNentries="1/#it{N}_{entries} ";
  TString sTitle(hIn.GetYaxis()->GetTitle());
  sTitle.Prepend(texNentries);
  hIn.SetYTitle(sTitle.Data());
  hIn.SetTitle(sTitle.Data());
  return;
}

//_______________________________________________________________________________________________
void LmBaseSignal::NormalizeCrossSection(TH1D& hIn)
{
    cout << " NormalizeCrossSection()" << endl;
  if (fCrossSection > 0) hIn.Scale(fCrossSection);
  else             { LmHelper::Warning(Form("LmBaseSignal::NormalizeCrossSection(): normalization not possible (Cross Section = %f). nothing done.",fCrossSection)); return; }
  //
  const char* texCrossSection="#sigma_{pp}"; //TODO change unit
  TString sTitle(hIn.GetYaxis()->GetTitle());
  sTitle.Prepend(texCrossSection);
  if(sTitle.Contains("GeV/#it{c}^{2}"))
    sTitle.ReplaceAll("GeV/#it{c}^{2}","mb / GeV/#it{c}^{2}");
  else sTitle.ReplaceAll("GeV/#it{c}","mb / GeV/#it{c}");
  sTitle.ReplaceAll("^{-1}","");

  if(fNormalisations & kNormVtxRecEff){
    sTitle.ReplaceAll("#sigma_{pp}","");
    sTitle.ReplaceAll("1/#it{N}_{ev}^{V0AND}","1/#it{L}_{int} ");

    if(fNormalisations & ( kNormNevents + kNormTrgEff + kNormRecEff + kNormVtxRecEff + kNormVtxRecEffee )){
      sTitle.ReplaceAll("1/#epsilon_{ee}^{trig.}","");
      sTitle.ReplaceAll("1/#epsilon_{ee}^{rec.}","");
      sTitle.ReplaceAll("1/#epsilon_{ee}^{vtx.}","");
      sTitle.ReplaceAll("1/#it{N}_{ev}^{V0AND}","");
      sTitle.ReplaceAll("1/#it{L}_{int}","");
      sTitle.ReplaceAll("N","#sigma");

      if(fDoAcceCorr)
        sTitle.ReplaceAll(" (","d#it{y} (");
    }

  }
  
  hIn.SetYTitle(sTitle.Data());
  hIn.SetTitle(sTitle.Data());
  return;
}

//_______________________________________________________________________________________________
void LmBaseSignal::NormalizeTrgEff(TH1D& hIn)
{
    cout << " NormalizeTrgEff()" << endl;
  if (fTrgEff > 0) hIn.Scale(1/fTrgEff);
  else             { LmHelper::Warning(Form("LmBaseSignal::NormalizeTrgEff(): normalization not possible (Trigger Efficiency = %f). nothing done.",fTrgEff)); return; }
  //
  if(fDoExtendedTitle){
    const char* texTrgEff="1/#epsilon_{ee}^{trig.}"; 
    TString sTitle(hIn.GetYaxis()->GetTitle());
    sTitle.Prepend(texTrgEff);
    hIn.SetYTitle(sTitle.Data());
    hIn.SetTitle(sTitle.Data());
  }
  return;
}

//_______________________________________________________________________________________________
void LmBaseSignal::NormalizeRecEff(TH1D& hIn)
{
    cout << " NormalizeRecEff()" << endl;
  //if (fTrgEff > 0) hIn.Scale(1/fTrgEff);
  //else             { LmHelper::Warning(Form("LmBaseSignal::NormalizeTrgEff(): normalization not possible (Trigger Efficiency = %f). nothing done.",fTrgEff)); return; }
  //
  if(fDoExtendedTitle){
    const char* texRecEff="1/#epsilon_{ee}^{rec.}"; 
    TString sTitle(hIn.GetYaxis()->GetTitle());
    sTitle.Prepend(texRecEff);
    hIn.SetYTitle(sTitle.Data());
    hIn.SetTitle(sTitle.Data());
  }
  return;
}

//_______________________________________________________________________________________________
void LmBaseSignal::NormalizeVtxRecEff(TH1D& hIn)
{
    cout << " NormalizeVtxRecEff()" << endl;
  if (fVtxRecEff > 0) hIn.Scale(1/fVtxRecEff);
  else             { LmHelper::Warning(Form("LmBaseSignal::NormalizeVtxRecEff(): normalization not possible (Event Vertex Reconstruction Efficiency = %f). nothing done.",fVtxRecEff)); return; }
  //
  TString sTitle(hIn.GetYaxis()->GetTitle());
  if(fDoExtendedTitle){
    const char* texVtxRecEff="1/#epsilon_{evt.}^{vtx.}"; 
    sTitle.Prepend(texVtxRecEff);
  }
  else
    sTitle.ReplaceAll( "1/#it{N}_{ev}", "1/#it{N}_{ev}^{V0AND}");
    //sTitle.ReplaceAll( "1/#it{N}_{ev}^{phys.sel.}", "1/#it{N}_{ev}^{V0AND}");
  hIn.SetYTitle(sTitle.Data());
  hIn.SetTitle(sTitle.Data());
  return;
}

//_______________________________________________________________________________________________
void LmBaseSignal::NormalizeVtxRecEffee(TH1D& hIn)
{
    cout << " NormalizeVtxRecEff()" << endl;
  if (fVtxRecEff_ee > 0) hIn.Scale(1/fVtxRecEff_ee);
  else             { LmHelper::Warning(Form("LmBaseSignal::NormalizeVtxRecEffee(): normalization not possible (Event Vertex Reconstruction Efficiency with dielectron pair= %f). nothing done.",fVtxRecEff)); return; }
  //
  if(fDoExtendedTitle){
    const char* texVtxRecEff="1/#epsilon_{ee}^{vtx.}"; 
    TString sTitle(hIn.GetYaxis()->GetTitle());
    sTitle.Prepend(texVtxRecEff);
    hIn.SetYTitle(sTitle.Data());
    hIn.SetTitle(sTitle.Data());
  }
  return;
}

//_______________________________________________________________________________________________
void LmBaseSignal::SetInputLabelX(const char* var, const char* unit, const char* text)
{
  fsInputTexX=var;
  fsInputTexXunit=unit;
  if (TString(text).IsNull()) {
    LmHelper::Warning(Form("LmBaseSignal::SetInputLabelX(): give plain text for variable '%s' as third argument (e.g. 'Mee','PhiV','DCAee'). Needed for canvas names.",var));
    text="Undef";
  }
  fsInputCodeX=text;
}

//_______________________________________________________________________________________________
void LmBaseSignal::SetInputLabelY(const char* var, const char* unit, const char* text)
{
  fsInputTexY=var;
  fsInputTexYunit=unit;
  if (TString(text).IsNull()) {
    LmHelper::Warning(Form("LmBaseSignal::SetInputLabelY(): give plain text for variable '%s' as third argument (e.g. 'Mee','PhiV','DCAee'). Needed for canvas names.",var));
    text="Undef";
  }
  fsInputCodeY=text;
}

//_______________________________________________________________________________________________
void LmBaseSignal::SetInputLabelZ(const char* var, const char* unit, const char* text)
{
  fsInputTexZ=var;
  fsInputTexZunit=unit;
  if (TString(text).IsNull()) {
    LmHelper::Warning(Form("LmBaseSignal::SetInputLabelZ(): give plain text for variable '%s' as third argument (e.g. 'Mee','PhiV','DCAee'). Needed for canvas names.",var));
    text="Undef";
  }
  fsInputCodeZ=text;
}

//_______________________________________________________________________________________________
void LmBaseSignal::SetInputLabelContent(const char* var, const char* unit)
{
  fsInputTexContent=var; fsInputTexContentunit=unit;
//  LmHelper::Debug(" LmBaseSignal::SetInputLabelContent()", 3);
//  LmHelper::Debug(Form(" |-> fsInputTexContent ,    ~unit: %s , %s", fsInputTexContent.Data(), fsInputTexContentunit.Data()), 3);

  if (fsInputTexContent.Length()>0) return; // already ok? otherwise compute it:
  if (fsInputTexZ.IsNull()) fsInputTexContent = Form("unsubtr. raw d#it{N}/d%sd%s",    fsInputTexX.Data(), fsInputTexY.Data());
  else                      fsInputTexContent = Form("unsubtr. raw d#it{N}/d%sd%sd%s", fsInputTexX.Data(), fsInputTexY.Data(), fsInputTexZ.Data());
//  LmHelper::Debug(Form(" |-> recomputed fsInputTexContent: %s", fsInputTexContent.Data()), 3);
}

//_______________________________________________________________________________________________
TString LmBaseSignal::GetInputLabelContent()
{
  if (fsInputTexContent.IsNull()) SetInputLabelContent("", "a.u."); // automatically compute content label.
  return (TString) fsInputTexContent+" ("+fsInputTexContentunit+")";
}

//_______________________________________________________________________________________________
TString LmBaseSignal::GetProjLabelContent()
{
  /// Returns content (yield) label of 2D histograms.
  /// Removes from it the differential of the third dimension of the 3D input histograms if needed (e.g. "#it{#phi}_{V}" or "#it{dca}_{ee}".

//  LmHelper::Debug(" LmBaseSignal::GetProjLabelContent()", 3);
//  LmHelper::Debug(Form(" |-> fsInputTexContent ,    ~unit: %s , %s", fsInputTexContent.Data(), fsInputTexContentunit.Data()), 3);
  TString scontent(GetInputLabelContent());
//  LmHelper::Debug(Form(" |-> input   scontent: %s", scontent.Data()), 3);

  if (!GetProjLabelZvar().IsNull()) { // important, otherwise would remove all "d"s from the label.
    scontent.ReplaceAll(Form("d%s",GetProjLabelZvar().Data()),"");
    //scontent.ReplaceAll((TString)"d"+GetProjLabelZvar(),""); // avoid Form() statement when it contains a function call with TStrings.
  }
//  LmHelper::Debug(Form(" |-> reduced scontent: %s", scontent.Data()), 3);
  return scontent;
}

//_______________________________________________________________________________________________
TString LmBaseSignal::GetProjLabel(inputAxis iaxis) {
  TString label(""); TString axis("");
  switch (iaxis) {
    case kInputX: label = GetInputLabelX(); axis = "X"; break;
    case kInputY: label = GetInputLabelY(); axis = "Y"; break;
    case kInputZ: label = GetInputLabelZ(); axis = "Z"; break;
    case kInpUndef: label=""; axis="undefined"; break;
  }
  if (label.IsNull()) {
    LmHelper::Warning(Form("LmBaseSignal::GetProjLabel(): empty %s-axis label! Please set via LmBaseSignal::SetInputLabel%s(const char* var, const char* unit) in your <user>.cpp", axis.Data(), axis.Data()));
    label = "undefined";
  }
  return label;
}

//_______________________________________________________________________________________________
TString LmBaseSignal::GetProjLabelvar(inputAxis iaxis) {
  TString label(""); TString axis("");
  switch (iaxis) {
    case kInputX: label = GetInputLabelXvar(); axis = "X"; break;
    case kInputY: label = GetInputLabelYvar(); axis = "Y"; break;
    case kInputZ: label = GetInputLabelZvar(); axis = "Z"; break;
    case kInpUndef: label=""; axis="undefined"; break;
  }
  if (label.IsNull()) {
    LmHelper::Warning(Form("LmBaseSignal::GetProjLabelvar(): empty %s-axis label! Please set via LmBaseSignal::SetInputLabel%s(const char* var, const char* unit) in your <user>.cpp", axis.Data(), axis.Data()));
    label = "undefined";
  }
  return label;
}

//_______________________________________________________________________________________________
TString LmBaseSignal::GetProjLabelunit(inputAxis iaxis) {
  switch (iaxis) {
    case kInputX: return GetInputLabelXunit(); break;
    case kInputY: return GetInputLabelYunit(); break;
    case kInputZ: return GetInputLabelZunit(); break;
    case kInpUndef: return "undefined";
  }
  return "undefined";
}

//_______________________________________________________________________________________________
void LmBaseSignal::CorrelateAxesOfInputAndProjections(const char* option)
{
  /// Determines on which axes the 3D-to-2D projection takes place and stores values to retrieve the correct labels for later usage in LmHandler.
  /// Don't call this function if you are using 2D-input!
  /// option="ab" means: a vertical, b horizontal (ROOT-convention)
  TString sopt(option);
  if      (sopt.Contains("yx",TString::kIgnoreCase)) { fWhatIsX=kInputX; fWhatIsY=kInputY; fWhatIsZ=kInputZ; }
  else if (sopt.Contains("xy",TString::kIgnoreCase)) { fWhatIsX=kInputY; fWhatIsY=kInputX; fWhatIsZ=kInputZ; }
  else if (sopt.Contains("zx",TString::kIgnoreCase)) { fWhatIsX=kInputX; fWhatIsY=kInputZ; fWhatIsZ=kInputY; }
  else if (sopt.Contains("xz",TString::kIgnoreCase)) { fWhatIsX=kInputZ; fWhatIsY=kInputX; fWhatIsZ=kInputY; }
  else if (sopt.Contains("zy",TString::kIgnoreCase)) { fWhatIsX=kInputY; fWhatIsY=kInputZ; fWhatIsZ=kInputX; }
  else if (sopt.Contains("yz",TString::kIgnoreCase)) { fWhatIsX=kInputZ; fWhatIsY=kInputY; fWhatIsZ=kInputX; }
  else LmHelper::Error(Form("LmBaseSignal::CorrelateAxesOfInputAndProjections: projection option '%s' is invalid!", option));
}

//_______________________________________________________________________________________________
LmBaseSignal::projAxis LmBaseSignal::CheckWhichProjection(TH1* hist)
{
  /// Returns if 'hist' is a x- or y-projection of the 2D-signal. Check is based on its x-axis label.
  TString xtitle(hist->GetXaxis()->GetTitle());
  if      (xtitle.Contains(GetProjLabelXvar())) return kProjOnX;
  else if (xtitle.Contains(GetProjLabelYvar())) return kProjOnY;
  else    LmHelper::Error(Form("LmBaseSignal::CheckWhichProjection(): unexpected x-axis label of histogram '%s'.", hist->GetName()));
  return kUndef;
}

//_______________________________________________________________________________________________
LmBaseSignal::inputAxis LmBaseSignal::CheckWhichInputAxis(TH1* hist)
{
  /// Returns if 'hist' is a x-, y- or z-projection of the 3D-input. Check is based on its x-axis label.
  LmBaseSignal::inputAxis result = CheckWhichInputAxis( hist->GetXaxis() );
  if (result==kInpUndef) LmHelper::Error(Form("LmBaseSignal::CheckWhichInputAxis(): unexpected x-axis label of histogram '%s'.", hist->GetName()));
  return result;
}

//_______________________________________________________________________________________________
LmBaseSignal::inputAxis LmBaseSignal::CheckWhichInputAxis(TAxis* axis)
{
  /// Returns if 'axis' is the x-, y- or z-axis of the 3D-input. Check is based on its label/title.
  TString xtitle(axis->GetTitle());
  if      (xtitle.Contains(GetInputLabelXvar())) return kInputX;
  else if (xtitle.Contains(GetInputLabelYvar())) return kInputY;
  else if (xtitle.Contains(GetInputLabelZvar())) return kInputZ;
  else    LmHelper::Error(Form("LmBaseSignal::CheckWhichInputAxis(): unexpected axis label '%s'.", xtitle.Data()));
  return kInpUndef;
}

//_______________________________________________________________________________________________
TAxis* LmBaseSignal::GetInputXaxis(TH2* hist)
{
  if      (CheckWhichInputAxis(hist->GetXaxis()) == kInputX) return hist->GetXaxis();
  else if (CheckWhichInputAxis(hist->GetYaxis()) == kInputX) return hist->GetYaxis();
  else    LmHelper::Error(Form("LmBaseSignal::GetInputXaxis(): no axis of histogram '%s' corresponds to the input-x-axis.", hist->GetName()));
  return 0x0;
}
//_______________________________________________________________________________________________
TAxis* LmBaseSignal::GetInputYaxis(TH2* hist)
{
  if      (CheckWhichInputAxis(hist->GetXaxis()) == kInputY) return hist->GetXaxis();
  else if (CheckWhichInputAxis(hist->GetYaxis()) == kInputY) return hist->GetYaxis();
  else    LmHelper::Error(Form("LmBaseSignal::GetInputYaxis(): no axis of histogram '%s' corresponds to the input-y-axis.", hist->GetName()));
  return 0x0;
}
//_______________________________________________________________________________________________
TAxis* LmBaseSignal::GetInputZaxis(TH2* hist)
{
  if      (CheckWhichInputAxis(hist->GetXaxis()) == kInputZ) return hist->GetXaxis();
  else if (CheckWhichInputAxis(hist->GetYaxis()) == kInputZ) return hist->GetYaxis();
  else    LmHelper::Error(Form("LmBaseSignal::GetInputZaxis(): no axis of histogram '%s' corresponds to the input-z-axis.", hist->GetName()));
  return 0x0;
}


//_______________________________________________________________________________________________
TString LmBaseSignal::GetInputAxisCode(inputAxis iaxis)
{
  switch (iaxis) {
    case kInputX: return (TString) fsInputCodeX;
    case kInputY: return (TString) fsInputCodeY;
    case kInputZ: return (TString) fsInputCodeZ;
    case kInpUndef: return "undefined";
  }
  return "undefined";
}
