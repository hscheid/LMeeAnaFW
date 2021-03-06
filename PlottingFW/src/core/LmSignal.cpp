// c++ includes
#include <iostream>
using namespace std;
// ROOT includes
#include "TString.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TDirectory.h"
// project includes
#include "LmSignal.h"
#include "LmBackground.h"
#include "LmManager.h"
#include "LmHistogram.h"
#include "LmHelper.h"

int debugSignal=0;
Bool_t debugSyst=kFALSE; // replace mee projections for SoverB and significance with the ones from systematic histograms.


//_______________________________________________________________________________________________
LmSignal::LmSignal(std::string name, Int_t type) :
	LmBaseSignal(), // @TODO: create constructors for LmBaseSignal
	LmRebinner(),
	fName(name.data()),
	fType(type),
	fTypename(Form("type%i",type)), // would stay empty if Process() will not be called.
	fLmMgr(0x0),
	fLmBkg(0x0),
	fUnlike(0x0),
	fBkg(0x0),
	fSubSig(0x0),
	fUnlikeNoEffi(0x0),
	fBkgNoEffi(0x0),
	fSigNoEffi(0x0),
	fSoverB(0x0),
	fSignifSplusB(0x0),
	fSignifSplus2B(0x0),
	fDoSubtraction(kFALSE),
	fSubtractionDone(kFALSE),
	fEffiApplied(kFALSE),
  fAcceApplied(kFALSE),
	fDoSignifRaw(kTRUE), //TRUE! should always be the default.
	fOwnerMgr(kFALSE),
	fSubSig_projMee(), // initialize because of use in GetMaxBinProj().
	fSubSig_projPtee(),
	fSymmetricRelSystematics(0x0),
	fRelSystematicsLow(0x0),
	fRelSystematicsHigh(0x0),
	fSystematicLow(0x0),
	fSystematicHigh(0x0)
	// all the projection vectors are not initialized or copied
{
	/// Default constructor for LmSignal
	/// Do not set a 'type' which needs to be processed! (some sanity checks may not work)

	LmHelper::Debug("LmSignal default constructor", 5-debugSignal);
	// initialize inherited variables:
	SetNeventsPhysSel(0);
	SetDoNormBinwidth(kFALSE);
	SetDoNormNevents (kFALSE);
	SetDoNormNentries(kFALSE);
	SetDoNormCrossSection(kFALSE);
	SetDoNormTrgEff(kFALSE);
	SetDoNormRecEff(kFALSE);
	SetDoNormVtxRecEff(kFALSE);
	SetDoNormVtxRecEffee(kFALSE);

	SetDoExtendedTitle(kTRUE);
}


//_______________________________________________________________________________________________
LmSignal::LmSignal(const LmSignal& sig, std::string name) :
	LmBaseSignal(), // may not be needed but once had some trouble with empty fNeventsPhysSel...
	// @TODO: create constructors for LmBaseSignal
	LmRebinner(sig),
	fName(sig.fName),
	fType(sig.fType),
	fTypename(sig.fTypename),
	fLmMgr(0x0), // copied below if available
	fLmBkg(0x0), // not copied
	fDoSubtraction(sig.fDoSubtraction),
	fSubtractionDone(sig.fSubtractionDone),
	fEffiApplied(sig.fEffiApplied),
  fAcceApplied(sig.fAcceApplied),
	fDoSignifRaw(sig.fDoSignifRaw),
	fOwnerMgr(kFALSE),
	fSubSig_projMee(), // initialize because of use in GetMaxBinProj().
	fSubSig_projPtee(),
	fSymmetricRelSystematics(sig.fSymmetricRelSystematics),
	fRelSystematicsLow(sig.fRelSystematicsLow),
	fRelSystematicsHigh(sig.fRelSystematicsHigh),
	fSystematicLow(sig.fSystematicLow),
	fSystematicHigh(sig.fSystematicHigh)
	// all the projection vectors are not initialized or copied
{
	/// Copy constructor for LmSignal
	/// Only some properties of LmManager will be copied.
	/// The LmBackground object will not be copied.
	/// The projections are not transferred.

	LmHelper::Debug("LmSignal copy constructor", 5-debugSignal);
	if (name.compare("") != 0) fName = name.data(); // set new name if specified.
	// initialize inherited variables:
	SetNeventsPhysSel(sig.GetNeventsPhysSel());
	SetCrossSection(sig.GetCrossSection());
	SetTrgEff(sig.GetTrgEff());
	SetVtxRecEff(sig.GetVtxRecEff());
	SetVtxRecEffee(sig.GetVtxRecEffee());

	SetDoNormBinwidth(sig.GetDoNormBinwidth());
	SetDoNormNevents(sig.GetDoNormNevents());
	SetDoNormNentries(sig.GetDoNormNentries());
	SetDoNormCrossSection(sig.GetDoNormCrossSection());
	SetDoNormTrgEff(sig.GetDoNormTrgEff());
	SetDoNormRecEff(sig.GetDoNormRecEff());
	SetDoNormVtxRecEff(sig.GetDoNormVtxRecEff());
	SetDoNormVtxRecEffee(sig.GetDoNormVtxRecEffee());

	SetDoExtendedTitle(sig.GetDoExtendedTitle());

	// copy member variables:
	if (sig.GetManager()) {
		SetManager(     sig.GetManager(), kFALSE ); // using copy constructor of LmManager. kFALSE: dont copy input histograms.
	}
	SetUnlike2D(      sig.GetUnlike2D() );
	SetBkg2D(         sig.GetBkg2D() );
	SetSubSig2D(      sig.GetSubSig2D() );
	SetUnlikeNoEffi2D(sig.GetUnlikeNoEffi2D() );
	SetBkgNoEffi2D(   sig.GetBkgNoEffi2D() );
	SetSigNoEffi2D(   sig.GetSigNoEffi2D() );
	// No need to copy 2D histograms SoverB and significance. They are not used for calculations or drawing.
	fSoverB = 0x0; //if (sig.fSoverB) fSoverB = new TH2D(*sig.GetSoverB());
	fSignifSplusB = 0x0;
	fSignifSplus2B = 0x0;
}


//_______________________________________________________________________________________________
LmSignal::LmSignal(LmManager &mgr, LmBackground &bkg, std::string name) :
	LmBaseSignal(),
	LmRebinner(),
	fName(mgr.GetName()),
	fType(0),
	fTypename(""),
	fLmMgr(&mgr),
	fLmBkg(&bkg),
	fUnlike(0x0),
	fBkg(0x0),
	fSubSig(0x0),
	fUnlikeNoEffi(0x0),
	fBkgNoEffi(0x0),
	fSigNoEffi(0x0),
	fSoverB(0x0),
	fSignifSplusB(0x0),
	fSignifSplus2B(0x0),
	fDoSubtraction(kTRUE), //TRUE!
	fSubtractionDone(kFALSE),
	fEffiApplied(kFALSE),
  fAcceApplied(kFALSE),
	fDoSignifRaw(kTRUE), //TRUE!
	fOwnerMgr(kFALSE),
	fSubSig_projMee(), // initialize because of use in GetMaxBinProj().
	fSubSig_projPtee(),
	fSymmetricRelSystematics(0x0),
	fRelSystematicsLow(0x0),
	fRelSystematicsHigh(0x0),
	fSystematicLow(0x0),
	fSystematicHigh(0x0)
	// all the projection vectors are not initialized or copied
{
	/// Constructor for LmSignal, specifying LmManager and LmBackground and name
	/// @param mgr  LmManager object (contains 2D/3D pair spectra and efficiency histograms from rootfile)
  /// @param bkg  LmBackground object (contains processed 2D histograms of Like-Sign and R-factor)
  /// @param name Name of signal (optional). Otherwise the name is taken from the manager.

  LmHelper::Debug("LmSignal constructor", 5-debugSignal);
  if (name.length()>0) fName = name;
  // initialize inherited variables:
  SetNeventsPhysSel(0);
  SetDoNormBinwidth(kTRUE); //TRUE!
  SetDoNormNevents(kTRUE); //TRUE!
  SetDoNormNentries(kFALSE); //FALSE! not necessary for typical analysis
  SetDoNormCrossSection(kFALSE);//FALSE! not necessary for typical analysis
  SetDoNormTrgEff(kFALSE);//FALSE! not necessary for typical analysis
  SetDoNormRecEff(kFALSE);//FALSE! not necessary for typical analysis
  SetDoNormVtxRecEff(kFALSE);//FALSE! not necessary for typical analysis
  SetDoNormVtxRecEffee(kFALSE);//FALSE! not necessary for typical analysis

  SetDoExtendedTitle(kFALSE);
}


//_______________________________________________________________________________________________
LmSignal::LmSignal(const LmSignal &s1, const LmSignal &s2, Double_t MeeMin, Double_t MeeMax, Double_t PteeMin, Double_t PteeMax) :
LmBaseSignal(s1),
LmRebinner(s1),
fName(Form("%s_%s",s1.GetName(),s2.GetName())),
fType(s1.fType),
fTypename(Form("%s_%s",s1.GetTypename(),s2.GetTypename())),
fLmMgr(s1.fLmMgr),
fLmBkg(s1.fLmBkg),
fUnlike(0x0),
fBkg(0x0),
fSubSig(0x0),
fUnlikeNoEffi(0x0),
fBkgNoEffi(0x0),
fSigNoEffi(0x0),
fSoverB(0x0),
fSignifSplusB(0x0),
fSignifSplus2B(0x0),
fDoSubtraction(s1.fDoSubtraction),
fSubtractionDone(s1.fSubtractionDone),
fEffiApplied(s1.fEffiApplied),
fDoSignifRaw(s1.fDoSignifRaw),
fOwnerMgr(kFALSE)
{
  SetNeventsPhysSel    (s1.GetNeventsPhysSel());
  SetCrossSection      (s1.GetCrossSection());
  SetTrgEff            (s1.GetTrgEff());
  SetVtxRecEff         (s1.GetVtxRecEff());
  SetVtxRecEffee       (s1.GetVtxRecEffee());

  SetDoNormBinwidth    (s1.GetDoNormBinwidth());
  SetDoNormNevents     (s1.GetDoNormNevents());
  SetDoNormNentries    (s1.GetDoNormNentries());
  SetDoNormCrossSection(s1.GetDoNormCrossSection());
  SetDoNormTrgEff      (s1.GetDoNormTrgEff());
  SetDoNormRecEff      (s1.GetDoNormRecEff());
  SetDoNormVtxRecEff   (s1.GetDoNormVtxRecEff());
  SetDoNormVtxRecEffee (s1.GetDoNormVtxRecEffee());

  SetDoExtendedTitle   (s1.GetDoExtendedTitle());

  fUnlike          = LmHelper::CombineHistograms(s1.fUnlike,       s2.fUnlike,       Form("%s_%s",s1.fUnlike       ->GetName(),s2.fUnlike       ->GetName()), MeeMin, MeeMax, PteeMin, PteeMax);
  fBkg             = LmHelper::CombineHistograms(s1.fBkg,          s2.fBkg,          Form("%s_%s",s1.fBkg          ->GetName(),s2.fBkg          ->GetName()), MeeMin, MeeMax, PteeMin, PteeMax);
  fSubSig          = LmHelper::CombineHistograms(s1.fSubSig,       s2.fSubSig,       Form("%s_%s",s1.fSubSig       ->GetName(),s2.fSubSig       ->GetName()), MeeMin, MeeMax, PteeMin, PteeMax);
  fUnlikeNoEffi    = LmHelper::CombineHistograms(s1.fUnlikeNoEffi, s2.fUnlikeNoEffi, Form("%s_%s",s1.fUnlikeNoEffi ->GetName(),s2.fUnlikeNoEffi ->GetName()), MeeMin, MeeMax, PteeMin, PteeMax);
  fBkgNoEffi       = LmHelper::CombineHistograms(s1.fBkgNoEffi,    s2.fBkgNoEffi,    Form("%s_%s",s1.fBkgNoEffi    ->GetName(),s2.fBkgNoEffi    ->GetName()), MeeMin, MeeMax, PteeMin, PteeMax);
  fSigNoEffi       = LmHelper::CombineHistograms(s1.fSigNoEffi,    s2.fSigNoEffi,    Form("%s_%s",s1.fSigNoEffi    ->GetName(),s2.fSigNoEffi    ->GetName()), MeeMin, MeeMax, PteeMin, PteeMax);
  fSoverB          = LmHelper::CombineHistograms(s1.fSoverB,       s2.fSoverB,       Form("%s+%s",s1.fSoverB       ->GetName(),s2.fSoverB       ->GetName()), MeeMin, MeeMax, PteeMin, PteeMax);
  fSignifSplusB    = LmHelper::CombineHistograms(s1.fSignifSplusB, s2.fSignifSplusB, Form("%s+%s",s1.fSignifSplusB ->GetName(),s2.fSignifSplusB ->GetName()), MeeMin, MeeMax, PteeMin, PteeMax);
  fSignifSplus2B   = LmHelper::CombineHistograms(s1.fSignifSplus2B,s2.fSignifSplus2B,Form("%s+%s",s1.fSignifSplus2B->GetName(),s2.fSignifSplus2B->GetName()), MeeMin, MeeMax, PteeMin, PteeMax);
//  fSymmetricRelSystematics = LmHelper::CombineHistograms(s1.fSymmetricRelSystematics, s2.fSymmetricRelSystematics, Form("%s+%s",s1.fSymmetricRelSystematics->GetName(),s2.fSymmetricRelSystematics->GetName()), MeeMin, MeeMax, PteeMin, PteeMax);
//  fRelSystematicsLow       = LmHelper::CombineHistograms(s1.fRelSystematicsLow,       s2.fRelSystematicsLow,       Form("%s+%s",s1.fRelSystematicsLow      ->GetName(),s2.fRelSystematicsLow      ->GetName()), MeeMin, MeeMax, PteeMin, PteeMax);
//  fRelSystematicsHigh      = LmHelper::CombineHistograms(s1.fRelSystematicsHigh,      s2.fRelSystematicsHigh,      Form("%s+%s",s1.fRelSystematicsHigh     ->GetName(),s2.fRelSystematicsHigh     ->GetName()), MeeMin, MeeMax, PteeMin, PteeMax);
  if(s1.fSystematicLow && s2.fSystematicLow)
    fSystematicLow = LmHelper::CombineHistograms(s1.fSystematicLow,s2.fSystematicLow,Form("%s_%s",s1.fSystematicLow->GetName(),s2.fSystematicLow->GetName()), MeeMin, MeeMax, PteeMin, PteeMax);
  if(s1.fSystematicHigh && s2.fSystematicHigh)
    fSystematicHigh = LmHelper::CombineHistograms(s1.fSystematicHigh,s2.fSystematicHigh,Form("%s_%s",s1.fSystematicHigh->GetName(),s2.fSystematicHigh->GetName()), MeeMin, MeeMax, PteeMin, PteeMax);
}


//_______________________________________________________________________________________________
LmSignal::~LmSignal()
{
  LmHelper::Debug("LmSignal destructor", 5-debugSignal);

  if (fLmMgr && fOwnerMgr) delete fLmMgr   ;
  //if (fLmBkg        ) delete fLmBkg        ; // not a class member.
  if (fUnlike       ) delete fUnlike       ;
  if (fBkg          ) delete fBkg          ;
  if (fSubSig       ) delete fSubSig       ;
  if (fUnlikeNoEffi ) delete fUnlikeNoEffi ;
  if (fBkgNoEffi    ) delete fBkgNoEffi    ;
  if (fSigNoEffi    ) delete fSigNoEffi    ;
  if (fSoverB       ) delete fSoverB       ;
  if (fSignifSplusB ) delete fSignifSplusB ;
  if (fSignifSplus2B) delete fSignifSplus2B;

  CheckAndDeleteOldProjections(LmBaseSignal::kProjOnMee);
  CheckAndDeleteOldProjections(LmBaseSignal::kProjOnPtee);

  if (fSymmetricRelSystematics) delete fSymmetricRelSystematics;
  if (fRelSystematicsLow      ) delete fRelSystematicsLow      ;
  if (fRelSystematicsHigh     ) delete fRelSystematicsHigh     ;
  if (fSystematicLow          ) delete fSystematicLow          ;
  if (fSystematicHigh         ) delete fSystematicHigh         ;
}


//_______________________________________________________________________________________________
void LmSignal::Process(Int_t type, Bool_t recursive)
{
  LmHelper::Debug(Form("LmSignal Process(type=%d, recursive=%d) [name='%s']", type, recursive, GetName()), 5-debugSignal);

  switch (type) {
    case kStd:
      if (!recursive) {
        fTypename="Std"; fType=type;
        // copy objects from LmManager and LmBackground
        SetNeventsPhysSel(fLmMgr->GetNeventsPhysSel());
        SetUnlike2D(      fLmMgr->GetUnlike()); GetUnlike2D()->SetName("hUnlike"); // somehow the name is empty otherwise.
        SetBkg2D(         fLmBkg->GetBkg2D());  GetBkg2D()->SetName("hBkg");
      }

      if (fLmMgr && fLmMgr->IsSubtractedMC()) { // check if this LmSignal was made from a "subtracted" MC signal (i.e. real pairs).
        SetSubSig2D(fUnlike); // make copy
        UpdateTitleSubtracted(fSubSig);
        SetSubtractionDone(kTRUE);
        SetDoSubtraction(kFALSE);
      }

      if (GetDoSubtraction()) {
        fSubSig         = CalcSubtractedSignal(fUnlike, fBkg, Form("hSubSig%s_%s",GetTypename(),fLmBkg->GetName()));
      }
      if (GetSubtractionDone()) { // check needed for manually configured signals (like kCombined)
        fSoverB         = CalcSignalBackgroundRatio2D(fSubSig, fBkg, Form("hSoverB%s",GetTypename()));
      }

      if (!GetEffiApplied()) { // make backup of plain spectra before effi correction (to compute significances and confidence level).
        LmHelper::Debug(Form(" backup 2D spectra before efficiency correction."), 10-debugSignal);
        SetUnlikeNoEffi2D(GetUnlike2D()); GetUnlikeNoEffi2D()->SetName("hUnlikeNoEffi");
        SetBkgNoEffi2D(GetBkg2D());       GetBkgNoEffi2D()->SetName("hBkgNoEffi");
        SetSigNoEffi2D(GetSig2D());       GetSigNoEffi2D()->SetName("hSigNoEffi"); // could be subtracted or unsubtracted!
      }

      if (GetSubtractionDone()) {
        if (!fSigNoEffi || !fBkgNoEffi) { // check that plain spectra are available to compute significance
          LmHelper::Warning("LmSignal::Process(): 2D histograms before effi correction not available! Not computing significance!");
        } else {
          fSignifSplusB   = CalcSignificance2D(fSigNoEffi, fBkgNoEffi, Form("hSignifSplusB%s",GetTypename()));
          fSignifSplus2B  = CalcSignificance2D(fSigNoEffi, fBkgNoEffi, Form("hSignifSplus2B%s",GetTypename()));
        }
      }

      // efficiency correction needs to be done after subtraction, otherwise titles messed up, and probably errors as well!
      // may need to specify for which signal types this is meaningful, make sure the signal has a manager attached!
      //if (fType==kStd || fType==kCombined) ...
      if (fLmMgr && fLmMgr->GetEnableEffiCorr() && !GetEffiApplied()) {
        ApplyEfficiency2D_all(fLmMgr->GetEffi());
      }
      // do additional rebinning in 2D after efficiency correction.
      if (GetEnableRebinning()) { // in LmRebinner class
        Rebin2DHistogram_all();
      }

      break;

    case kCombined:
      if (!recursive) { fTypename="Combined"; fType=type; } // name without 'k'
      Process(kStd, kTRUE);
      break;

    case kAverage:
      if (!recursive) { fTypename="Average"; fName=fTypename; fType=type; } // name without 'k'
      break;

    case kWeightedAverage:
      if (!recursive) { fTypename="WeightedAverage"; fName=fTypename; fType=type; } // name without 'k'
      break;

    case kSystematic:
      if(fSymmetricRelSystematics || fRelSystematicsLow || fRelSystematicsHigh)
        MakeSystematicHistos();
      else
        LmHelper::Error("LmSignal::Process(kSystematic): no histogram with relative systematics set.");
      break;

    case kExternalBG:
      if (!recursive) { fTypename="ExternalBG"; fType=type; } // name without 'k'
      SetNeventsPhysSel(fLmMgr->GetNeventsPhysSel());
      SetUnlike2D(      fLmMgr->GetUnlike()); GetUnlike2D()->SetName("hUnlike"); // somehow the name is empty otherwise.
      if(GetBkg2D())
        GetBkg2D()->SetName("hBkg");
      else{
        LmHelper::Error("LmSignal::Process(kExternalBG): no 2D Bkg set. Cannot process!");
        return;
      }
      Process(kStd, kTRUE);
      break;

    case kExternal1D:
      if (!recursive) { fTypename="External1D"; fType=type; } // name without 'k'
      break;

    case kExternal2D:
      if (!recursive) { fTypename="External2D"; fType=type; } // name without 'k'
      //Process(kStd, kTRUE); // this would only fill the 2D SoverB and significance...
      break;

    case kAcceCorrection2D:
      if (!recursive) { fTypename="AcceCorrection2D"; fType=type; } // name without 'k'
      //TODO remember 2D rebinning of acceptance correction first
      //if (GetAcceCorr2D()   ) Rebin2DHistogram(*GetAcceCorr2D()   );
      if (fLmMgr && fLmMgr->GetEnableAcceCorr() && !GetAcceApplied() && GetEffiApplied()){
	if(fLmMgr->GetAcce())
          ApplyAcceptance2D(fLmMgr->GetAcce());
	else{
	  LmHelper::Error("LmSignal::Process(kAcceCorrection2D): no Acceptance correction histogram. Cannot process!");
          return;
	}
      }

      break;


    default:
      break;
  }
  if (recursive) return;
  // Put things below which shall be called only for non-recursive Process() calls, otherwise they are executed more than once!
}

//_______________________________________________________________________________________________
void LmSignal::MakeSystematicHistos()
{
  /// Creates 2 copies of the (un)subtracted 2D signal for lower and upper systematics and scales them such that
  /// lower systematics = signal * (1 - rel. uncert.) and upper systematics = signal * (1 + rel. uncert.).
  /// For a negative bin, the upper syst. will by construction have the most negative value and vice versa.
  /// This still gives the correct uncertainty when the integral over several bins is positive and these bins all
  /// have the same relative uncertainty [checked by hand 24.06.16, and can be seen as identical error sizes in
  /// neighboring (mass) bins of signal plots that were projected over just one of the coarse systematic (pT) bins].
  ///
  /// NOTE: projections over (pT) bins with varying rel. uncert. (e.g. integrated projections) will get relative
  /// systematic errors that are no longer equal in neighboring (mass) bins. This is due to the weighting of rel.
  /// uncert. with corresponding bin contents and therefore intrinsic to this method.
  LmHelper::Debug(" LmSignal::MakeSystematicHistos()", 5-debugSignal);

  if (debugSyst) {
    TCanvas* cRelSys = new TCanvas("cRelSys", "cRelSys");
    LmHelper::TH2_Beautify(fSymmetricRelSystematics, cRelSys);
    fSymmetricRelSystematics->DrawCopy("colz");
    cRelSys->Print(Form("cRelSys-%s.pdf", GetName()));
    delete cRelSys;
  }

  // systematic histograms could exist from reading external file or from multiple calls of Process(LmSignal::kSystematic).
  if (fSystematicLow)  delete fSystematicLow;
  if (fSystematicHigh) delete fSystematicHigh;
  fSystematicLow = new TH2D(*GetSig2D());
  fSystematicHigh= new TH2D(*GetSig2D());
  fSystematicLow ->SetName(Form("%s_sysLow",GetSig2D()->GetName()));
  fSystematicHigh->SetName(Form("%s_sysHigh",GetSig2D()->GetName()));
  fSystematicLow ->Reset();
  fSystematicHigh->Reset();

  Int_t    relbinx(0),relbiny(0);
  Double_t bcLow(0.),bcHigh(0.);
  Double_t RelSymSys(0.),RelSysLow(0.),RelSysHigh(0.);
  Double_t TotalRelSysLow(0.),TotalRelSysHigh(0.);
  for(Int_t ix = 1; ix <= GetSig2D()->GetNbinsX(); ++ix){
    for(Int_t iy = 1; iy <= GetSig2D()->GetNbinsY(); ++iy){
      // Support systematic histos with different binning:
      if(fSymmetricRelSystematics) {
        relbinx   = fSymmetricRelSystematics->GetXaxis()->FindBin(GetSig2D()->GetXaxis()->GetBinCenter(ix));
        relbiny   = fSymmetricRelSystematics->GetYaxis()->FindBin(GetSig2D()->GetYaxis()->GetBinCenter(iy));
        RelSymSys = fSymmetricRelSystematics->GetBinContent(relbinx, relbiny);
      }
      if(fRelSystematicsLow) {
        relbinx   = fRelSystematicsLow->GetXaxis()->FindBin(GetSig2D()->GetXaxis()->GetBinCenter(ix));
        relbiny   = fRelSystematicsLow->GetYaxis()->FindBin(GetSig2D()->GetYaxis()->GetBinCenter(iy));
        RelSysLow = fRelSystematicsLow      ->GetBinContent(relbinx, relbiny);
      }
      if(fRelSystematicsHigh) {
        relbinx   = fRelSystematicsHigh->GetXaxis()->FindBin(GetSig2D()->GetXaxis()->GetBinCenter(ix));
        relbiny   = fRelSystematicsHigh->GetYaxis()->FindBin(GetSig2D()->GetYaxis()->GetBinCenter(iy));
        RelSysHigh= fRelSystematicsHigh     ->GetBinContent(relbinx, relbiny);
      }
      TotalRelSysLow  = TMath::Sqrt(TMath::Power(RelSymSys,2) + TMath::Power(RelSysLow, 2));
      TotalRelSysHigh = TMath::Sqrt(TMath::Power(RelSymSys,2) + TMath::Power(RelSysHigh,2));
      bcLow  = GetSig2D()->GetBinContent(ix,iy);
      bcHigh = GetSig2D()->GetBinContent(ix,iy);
      bcLow  = bcLow  * (1. - TotalRelSysLow); // in principle also ok for negative bin contents.
      bcHigh = bcHigh * (1. + TotalRelSysHigh);
      if(TotalRelSysLow > 1.) bcLow = 0.; // from Theo // @TODO: this could cause an inconsistency.
      //Printf(" bin(%2i,%2i): mee = %4.2f, ptee = %4.2f :  relbin(%2i,%2i):  RelSymSys = %5.3f,   RelSysLow = %5.3f, RelSysHigh = %5.3f", ix, iy, fSystematicLow->GetXaxis()->GetBinCenter(ix), fSystematicLow->GetYaxis()->GetBinCenter(iy), relbinx, relbiny, RelSymSys, TotalRelSysLow, TotalRelSysHigh);
      fSystematicLow ->SetBinContent(ix,iy,bcLow);
      fSystematicHigh->SetBinContent(ix,iy,bcHigh);
      fSystematicLow ->SetBinError(ix,iy,0.);
      fSystematicHigh->SetBinError(ix,iy,0.);
    }
  }
  if (debugSyst) { fSoverB = fSystematicLow; fSignifSplus2B = fSystematicHigh; }
}


//_______________________________________________________________________________________________
void LmSignal::MakeSpectra1D(const std::vector<Double_t> bins, Bool_t projOnMee, std::vector<std::vector<Double_t>*> vBinnings)
{
	/// This function is called from LmHandler to create projections according to the binning (projection ranges) of the handler.
	/// The projections are stored inside this LmSignal.
	LmHelper::Debug(Form("LmSignal::MakeSpectra1D(projOnMee=%i)", projOnMee), 5-debugSignal);

	if (fType==kExternal1D) {
		LmHelper::Warning(Form("LmSignal::MakeSpectra1D(on axis '%i'): this LmSignal (fType=%i) does not have 2D input. Skip doing projections. [%i=kExternal1D]", projOnMee, fType, kExternal1D));
		return;
	}

	if (bins.size()<=1) {
		LmHelper::Warning(Form("LmSignal::MakeSpectra1D(on axis '%i'): not enough projection bins set (>=2)! Skip doing projections. [%i=X-axis(Mee),%i=Y-axis(Ptee)]", projOnMee, LmBaseSignal::kProjOnMee, LmBaseSignal::kProjOnPtee));
		return;
	}
	if (vBinnings.size()<bins.size()-1) {
		LmHelper::Error(Form("LmSignal::MakeSpectra1D(on axis '%i'): vBinnings size = %i is too small, will crash.", projOnMee, (int)vBinnings.size()));
	}
	CheckAndDeleteOldProjections(projOnMee);
	for (unsigned int i = 0; i < bins.size()-1; ++i){
		if (projOnMee==LmBaseSignal::kProjOnMee)  MakeSpectra1D_Mee(bins.at(i), bins.at(i+1), vBinnings.at(i));
		else                                      MakeSpectra1D_Ptee(bins.at(i), bins.at(i+1), vBinnings.at(i));
	}
	// The last projection is integrated over all bins.
	// This projection must also be done in case only one bin exists, because some checks in the code rely on it!
	if (projOnMee==LmBaseSignal::kProjOnMee)    MakeSpectra1D_Mee(bins.at(0), bins.at(bins.size()-1), vBinnings.at(0));
	else                                        MakeSpectra1D_Ptee(bins.at(0), bins.at(bins.size()-1), vBinnings.at(0));
}

//_______________________________________________________________________________________________
void LmSignal::MakeSpectra1D_Mee(Double_t valmin, Double_t valmax, std::vector<Double_t> *binning)
{
	LmHelper::Debug(" MakeSpectra1D_Mee() ", 6-debugSignal);
	LmHelper::Debug(Form(" Mee-Projection from Ptee = %f to %f GeV/c", valmin, valmax), 10-debugSignal);
  if (fSigNoEffi && fUnlikeNoEffi && fBkgNoEffi) { // 2D histograms before effi correction may not be available (e.g. external 2D signal).
    // for confidence level calculation:
    TH1D* hUnlikeNoEffiUnnorm = (TH1D*) DoProjectionMee(fUnlikeNoEffi, valmin, valmax, kNoNormalisation, kFALSE, binning); // no normalization!
    TH1D* hBkgNoEffiUnnorm    = (TH1D*) DoProjectionMee(fBkgNoEffi, valmin, valmax, kNoNormalisation, kFALSE, binning); // no normalization!
    AttachUnlikeNoEffiUnnorm_Mee(*hUnlikeNoEffiUnnorm);
    AttachBkgNoEffiUnnorm_Mee(*hBkgNoEffiUnnorm);
    // significance:
    if (GetSubtractionDone() && !debugSyst) {
      LmHelper::Debug(Form(" calculating %s significance", GetDoSignifRaw()?"RAW":"normalized"), 11-debugSignal);
      if (GetDoSignifRaw()) { // this is the default significance, which needs un-normalized spectra
        TH1D* hSubNoEffiUnnorm = (TH1D*) DoProjectionMee(fSigNoEffi, valmin, valmax, kNoNormalisation, kFALSE, binning); // no normalization!
        TH1D* hSignif = CalcSignificance1D(hSubNoEffiUnnorm, hBkgNoEffiUnnorm, Form("hSignifSplus2B_Raw"));
        AttachSignif_Mee(*hSignif);
      }
      else { // other alternative for significance, using current normalization
        //TH1D* hSubNoEffi = (TH1D*) DoProjectionMee(fSigNoEffi, valmin, valmax, GetDoNormBinwidth(), GetDoNormNevents(), kFALSE, kFALSE, binning);
        //TH1D* hBkgNoEffi = (TH1D*) DoProjectionMee(fBkgNoEffi, valmin, valmax, GetDoNormBinwidth(), GetDoNormNevents(), kFALSE, kFALSE, binning);
        TH1D* hSubNoEffi = (TH1D*) DoProjectionMee(fSigNoEffi, valmin, valmax, GetDoNormBinwidth() + GetDoNormNevents(), kFALSE, binning);
        TH1D* hBkgNoEffi = (TH1D*) DoProjectionMee(fBkgNoEffi, valmin, valmax, GetDoNormBinwidth() + GetDoNormNevents(), kFALSE, binning);
        TH1D* hSignif = CalcSignificance1D(hSubNoEffi, hBkgNoEffi, Form("hSignifSplus2B_Norm"));
        AttachSignif_Mee(*hSignif);
      }
    }
  }
  // Rfactor + mixed-event ULS + LS:
  if (fType==kStd && fLmMgr->HasMixedEvent()) { // mixed-event histograms not computed for combined signal!
    LmHelper::Debug("  calculating Rfactor", 11-debugSignal);
    TH1D* hUnlikeMix = (TH1D*) DoProjectionMee(fLmMgr->GetUnlikeMix(), valmin, valmax, kNoNormalisation, kFALSE, binning); // no normalization!
    TH1D* hLikeMix   = (TH1D*) DoProjectionMee(fLmBkg->GetLikeMix2D(), valmin, valmax, kNoNormalisation, kFALSE, binning); // no normalization!
    TString newname(Form("hRfactor%s_Mee_ptee%.2fto%.2f",fLmBkg->GetTypename(),valmin,valmax));
    TH1D* hRfactor = fLmBkg->CalcRfactor1D(hUnlikeMix, hLikeMix, newname.Data()); // NOTE: This will not show if an Rfactor unity range was used!
    AttachRfactor_Mee(*hRfactor);
    // repeat with requested normalizations
    delete hUnlikeMix; delete hLikeMix;
    //hUnlikeMix = (TH1D*) DoProjectionMee(fLmMgr->GetUnlikeMix(), valmin, valmax, GetDoNormBinwidth(), GetDoNormNevents(), GetDoNormNentries(), kFALSE, binning);
    //hLikeMix   = (TH1D*) DoProjectionMee(fLmBkg->GetLikeMix2D(), valmin, valmax, GetDoNormBinwidth(), GetDoNormNevents(), GetDoNormNentries(), kFALSE, binning);
    hUnlikeMix = (TH1D*) DoProjectionMee(fLmMgr->GetUnlikeMix(), valmin, valmax, fNormalisations, kFALSE, binning);
    hLikeMix   = (TH1D*) DoProjectionMee(fLmBkg->GetLikeMix2D(), valmin, valmax, fNormalisations, kFALSE, binning);
    AttachUnlikeMix_Mee(*hUnlikeMix);
    AttachLikeMix_Mee(*hLikeMix);
  }
  // now with normalization (or not) as requested by GetDoNormBinwidth() and GetDoNormNevents(), GetDoNormNentries(kFALSE by default)
  LmHelper::Debug("  calculating hSub", 11-debugSignal);
  //TH1D* hSub = (TH1D*) DoProjectionMee(GetSig2D(), valmin, valmax, GetDoNormBinwidth(), GetDoNormNevents(), GetDoNormNentries(), kFALSE, binning); // last kTRUE/kFALSE enables/disables debugging of y axis title.
  TH1D* hSub = (TH1D*) DoProjectionMee(GetSig2D(), valmin, valmax, fNormalisations, kFALSE, binning); // last kTRUE/kFALSE enables/disables debugging of y axis title.
  AttachSubSig_Mee(*hSub);
  TH1D* hUnlike = (TH1D*) DoProjectionMee(GetUnlike2D(), valmin, valmax, fNormalisations, kFALSE, binning);
  AttachUnlike_Mee(*hUnlike);
  TH1D* hBkg = (TH1D*) DoProjectionMee(GetBkg2D(), valmin, valmax, fNormalisations, kFALSE, binning);
  AttachBkg_Mee(*hBkg);
  // signal-to-background ratio (doesnt care about normalization or not)
  if (GetSubtractionDone() && !debugSyst) {
    LmHelper::Debug("  calculating SoverB", 11-debugSignal);
    TH1D* hSoverB = CalcSignalBackgroundRatio1D(hSub, hBkg, Form("hSoverB"));
    AttachSoverB_Mee(*hSoverB);
  }
  if(fSystematicLow && fSystematicHigh){
    TH1D *hSysLow  = DoProjectionMee(fSystematicLow , valmin, valmax, fNormalisations, kFALSE, binning);
    TH1D *hSysHigh = DoProjectionMee(fSystematicHigh, valmin, valmax, fNormalisations, kFALSE, binning);
    if (debugSyst) { AttachSignif_Mee(*hSysLow); AttachSoverB_Mee(*hSysHigh); }
    if (GetSubtractionDone()) AttachSystematicGraph_Mee(hSub,hSysLow,hSysHigh);
    else                      AttachSystematicGraph_Mee(hUnlike,hSysLow,hSysHigh);
  }
}

//_______________________________________________________________________________________________
void LmSignal::MakeSpectra1D_Ptee(Double_t valmin, Double_t valmax, std::vector<Double_t> *binning)
{
  LmHelper::Debug(" MakeSpectra1D_Ptee() ", 6-debugSignal);
  LmHelper::Debug(Form(" Ptee-Projection from Mee = %f to %f GeV/c^2", valmin, valmax), 10-debugSignal);
  if (fSigNoEffi && fUnlikeNoEffi && fBkgNoEffi) { // 2D histograms before effi correction may not be available (e.g. external 2D signal).
    // for confidence level calculation:
    TH1D* hUnlikeNoEffiUnnorm = (TH1D*) DoProjectionPtee(fUnlikeNoEffi, valmin, valmax, kNoNormalisation, kFALSE, binning); // no normalization!
    TH1D* hBkgNoEffiUnnorm    = (TH1D*) DoProjectionPtee(fBkgNoEffi, valmin, valmax, kNoNormalisation, kFALSE, binning); // no normalization!
    AttachUnlikeNoEffiUnnorm_Ptee(*hUnlikeNoEffiUnnorm);
    AttachBkgNoEffiUnnorm_Ptee(*hBkgNoEffiUnnorm);
    // significance:
    if (GetSubtractionDone()) {
      LmHelper::Debug(Form(" calculating %s significance", GetDoSignifRaw()?"RAW":"normalized"), 11-debugSignal);
      if (GetDoSignifRaw()) { // this is the default significance, which needs un-normalized spectra
        TH1D* hSubNoEffiUnnorm = (TH1D*) DoProjectionPtee(fSigNoEffi, valmin, valmax, kNoNormalisation, kFALSE, binning); // no normalization
        TH1D* hSignif = CalcSignificance1D(hSubNoEffiUnnorm, hBkgNoEffiUnnorm, Form("hSignifSplus2B_Raw"));
        AttachSignif_Ptee(*hSignif);
      }
      else { // other alternative for significance, using current normalization
        TH1D* hSubNoEffi = (TH1D*) DoProjectionPtee(fSigNoEffi, valmin, valmax, GetDoNormBinwidth() + GetDoNormNevents(), kFALSE, binning);
        TH1D* hBkgNoEffi = (TH1D*) DoProjectionPtee(fBkgNoEffi, valmin, valmax, GetDoNormBinwidth() + GetDoNormNevents(), kFALSE, binning);
        TH1D* hSignif = CalcSignificance1D(hSubNoEffi, hBkgNoEffi, Form("hSignifSplus2B_Norm"));
        AttachSignif_Ptee(*hSignif);
      }
    }
  }
  // Rfactor + mixed-event ULS + LS:
  if (fType==kStd && fLmMgr->HasMixedEvent()) { // mixed-event histograms not computed for combined signal!
    LmHelper::Debug("  calculating Rfactor", 11-debugSignal);
    TH1D* hUnlikeMix = (TH1D*) DoProjectionPtee(fLmMgr->GetUnlikeMix(), valmin, valmax, kNoNormalisation, kFALSE, binning); // no normalization
    TH1D* hLikeMix   = (TH1D*) DoProjectionPtee(fLmBkg->GetLikeMix2D(), valmin, valmax, kNoNormalisation, kFALSE, binning); // no normalization
    TString newname(Form("hRfactor%s_Ptee_mee%.2fto%.2f",fLmBkg->GetTypename(),valmin,valmax));
    TH1D* hRfactor = fLmBkg->CalcRfactor1D(hUnlikeMix, hLikeMix, newname.Data()); // NOTE: This will not show if an Rfactor unity range was used!
    AttachRfactor_Ptee(*hRfactor);
    // repeat with requested normalizations
    delete hUnlikeMix; delete hLikeMix;
    hUnlikeMix = (TH1D*) DoProjectionPtee(fLmMgr->GetUnlikeMix(), valmin, valmax, fNormalisations, kFALSE, binning);
    hLikeMix   = (TH1D*) DoProjectionPtee(fLmBkg->GetLikeMix2D(), valmin, valmax, fNormalisations, kFALSE, binning);
    AttachUnlikeMix_Ptee(*hUnlikeMix);
    AttachLikeMix_Ptee(*hLikeMix);
  }
  // now with normalization (or not) as requested by GetDoNormBinwidth() and GetDoNormNevents(), GetDoNormNentries(kFALSE by default)
  LmHelper::Debug("  calculating hSub", 11-debugSignal);
  TH1D* hSub = (TH1D*) DoProjectionPtee(GetSig2D(), valmin, valmax, fNormalisations, kFALSE, binning); // last kTRUE/kFALSE enables/disables debugging of y axis title.
  AttachSubSig_Ptee(*hSub);
  TH1D* hUnlike = (TH1D*) DoProjectionPtee(GetUnlike2D(), valmin, valmax, fNormalisations, kFALSE, binning);
  AttachUnlike_Ptee(*hUnlike);
  TH1D* hBkg = (TH1D*) DoProjectionPtee(GetBkg2D(), valmin, valmax, fNormalisations, kFALSE, binning);
  AttachBkg_Ptee(*hBkg);
  // signal-to-background ratio (doesnt care about normalization or not)
  if (GetSubtractionDone()) {
    LmHelper::Debug("  calculating SoverB", 11-debugSignal);
    TH1D* hSoverB = CalcSignalBackgroundRatio1D(hSub, hBkg, Form("hSoverB"));
    AttachSoverB_Ptee(*hSoverB);
  }
  if(fSystematicLow && fSystematicHigh){
    TH1D *hSysLow  = DoProjectionPtee(fSystematicLow , valmin, valmax, fNormalisations, kFALSE, binning);
    TH1D *hSysHigh = DoProjectionPtee(fSystematicHigh, valmin, valmax, fNormalisations, kFALSE, binning);
    if (GetSubtractionDone()) AttachSystematicGraph_Ptee(hSub,hSysLow,hSysHigh);
    else                      AttachSystematicGraph_Ptee(hUnlike,hSysLow,hSysHigh);
  }
}


//_______________________________________________________________________________________________
void LmSignal::AddProjection(const TH1D *newproj, unsigned int histBit, Bool_t projOnMee)
{
  /// Function to set up external 1D signals.
  /// not extensively used yet...
  TH1D* hist = new TH1D(*newproj);

  if (projOnMee==LmBaseSignal::kProjOnMee) {
    switch (histBit) {
      case kSubSig:   AttachSubSig_Mee( *hist ); break;
//      case kUnlike:   return GetUnlike(bin, projOnMee);
//      case kBkg:      return GetBkg(bin, projOnMee);
//      case kRfactor:  return GetRfactor(bin, projOnMee);
//      case kSoverB:   return GetSoverB(bin, projOnMee);
//      case kSignif:   return GetSignif(bin, projOnMee);
      default: LmHelper::Error("LmSignal::AddProjection( mee ): hitBit not valid.");
        break;
    }
  }
  else { // Ptee
    switch (histBit) {
      case kSubSig:   AttachSubSig_Ptee( *hist ); break;
        //      case kUnlike:   return GetUnlike(bin, projOnMee);
        //      case kBkg:      return GetBkg(bin, projOnMee);
        //      case kRfactor:  return GetRfactor(bin, projOnMee);
        //      case kSoverB:   return GetSoverB(bin, projOnMee);
        //      case kSignif:   return GetSignif(bin, projOnMee);
      default: LmHelper::Error("LmSignal::AddProjection( ptee ): hitBit not valid.");
        break;
    }
  }
}

//_______________________________________________________________________________________________
void LmSignal::AttachSystematicGraph_Mee(TH1D *hSubSig, TH1D *hSysLow, TH1D *hSysHigh)
{
  Int_t nPoints = hSubSig->GetNbinsX();
  Double_t x[nPoints],y[nPoints],xLow[nPoints],xHigh[nPoints],yLow[nPoints],yHigh[nPoints];
  for(Int_t i = 0; i < nPoints; ++i){
    x[i]    = hSubSig->GetXaxis()->GetBinCenter(i+1);
    xLow[i] = TMath::Abs(x[i] - hSubSig->GetXaxis()->GetBinLowEdge(i+1));
    xHigh[i]= TMath::Abs(x[i] - hSubSig->GetXaxis()->GetBinUpEdge(i+1));
    y[i]    = hSubSig->GetBinContent(i+1);
    yLow[i] = TMath::Abs(y[i] - hSysLow ->GetBinContent(i+1));
    yHigh[i]= TMath::Abs(y[i] - hSysHigh->GetBinContent(i+1));
  }
  // store the uncertainty graph in LmHistogram, as it has always been foreseen:
  fSubSig_projMee.back()->SetSystError( new TGraphAsymmErrors(nPoints,x,y,xLow,xHigh,yLow,yHigh) );
}

//_______________________________________________________________________________________________
void LmSignal::AttachSystematicGraph_Ptee(TH1D *hSubSig, TH1D *hSysLow, TH1D *hSysHigh)
{
  Int_t nPoints = hSubSig->GetNbinsX();
  Double_t x[nPoints],y[nPoints],xLow[nPoints],xHigh[nPoints],yLow[nPoints],yHigh[nPoints];
  for(Int_t i = 0; i < nPoints; ++i){
    x[i]    = hSubSig->GetXaxis()->GetBinCenter(i+1);
    xLow[i] = TMath::Abs(x[i] - hSubSig->GetXaxis()->GetBinLowEdge(i+1));
    xHigh[i]= TMath::Abs(x[i] - hSubSig->GetXaxis()->GetBinUpEdge(i+1));
    y[i]    = hSubSig->GetBinContent(i+1);
    yLow[i] = TMath::Abs(y[i] - hSysLow ->GetBinContent(i+1));
    yHigh[i]= TMath::Abs(y[i] - hSysHigh->GetBinContent(i+1));
  }
  // store the uncertainty graph in LmHistogram, as it has always been foreseen:
  fSubSig_projPtee.back()->SetSystError( new TGraphAsymmErrors(nPoints,x,y,xLow,xHigh,yLow,yHigh) );
}

//_______________________________________________________________________________________________
void LmSignal::CalcConfidenceLevel(Double_t CL, Bool_t projOnMee, Bool_t cockRef)
{
  /// Calculate Confidence Levels for each oversubtracted bin of each projected spectrum.
  /// Calculation is done with raw spectra (no normalizations, no efficiency).

  LmHelper::Debug(Form(" CalcConfidenceLevel(CL=%.2f, projOnMee=%i)", CL, projOnMee), 5-debugSignal);

  Int_t maxProj = GetMaxBinProj(projOnMee);
  for (Int_t iProj = 0; iProj <= maxProj; ++iProj)
  {
    LmHelper::Debug(Form(" check projection %i of %i\n", iProj, maxProj), 10-debugSignal);

    /// @TODO: check <= or <
    for (Int_t bin = 1; bin <= GetSubSig(iProj,projOnMee)->GetDatahist()->GetNbinsX(); ++bin)
    {
      if (!cockRef && GetSubSig(iProj,projOnMee)->GetDatahist()->GetBinContent(bin) < 0) // if <= 0, it tries to compute empty bins as well (at low pair-pT)...
      {
      // if (GetBkg(iProj,projOnMee)->GetDatahist()->GetBinContent(bin) > 0) // will compute all arrows, except for empty bins at low pair-pT...
      // {
        LmHelper::Debug(Form(" oversubtracted bin: %i, low edge: %f", bin, GetSubSig(iProj,projOnMee)->GetDatahist()->GetBinLowEdge(bin)), 10-debugSignal);
        Double_t ULS_raw = GetUnlikeNoEffiUnnorm(iProj,projOnMee)->GetBinContent(bin);
        Double_t LS_raw  = GetBkgNoEffiUnnorm(iProj,projOnMee)->GetBinContent(bin);
        Double_t LS_error = TMath::Sqrt(LS_raw);
//        cout << "ULS = " << ULS_raw << endl;
//        cout << "LS  = " << LS_raw << endl;
//        cout << "ULS - LS = " << ULS_raw - LS_raw << endl;
//        cout << "LS_error = " << LS_error << endl;
        Double_t upper_limit_raw = 0;
        Double_t sensitivity = 1.; // as long as raw spectra are used, this should be 1.
        Double_t sensitivity_error = 0.; // can put here the estimated uncertainty on the efficiency correction.
        upper_limit_raw = LmHelper::CalcUpperLimit(CL, ULS_raw, LS_raw, LS_error, sensitivity, sensitivity_error); // represents upper limit on subtracted signal!
        //
        // scale the result to the normalized, efficiency corrected spectra, by using the ratio final/raw:
        Double_t finalToRaw_ratio = GetUnlike(iProj,projOnMee)->GetDatahist()->GetBinContent(bin) / ULS_raw;
        Double_t upper_limit = upper_limit_raw * finalToRaw_ratio;
        LmHelper::Debug(Form(" upper_limit scaled to final subtracted signal = %f", upper_limit), 10-debugSignal);

        // these numbers are just for positioning and scaling the arrow:
        Double_t binwidth  = GetUnlikeNoEffiUnnorm(iProj,projOnMee)->GetBinWidth(bin);
        Double_t bincenter = GetUnlikeNoEffiUnnorm(iProj,projOnMee)->GetBinCenter(bin);

        // Subtracted Signal
        if (upper_limit > 0) { // no reason to compute arrow if still oversubtracted.
          TArrow* arrow_SubSig = new TArrow(bincenter, upper_limit, bincenter, GetSubSig(iProj,projOnMee)->GetDatahist()->GetBinContent(bin), 0.05, "|->"); // better arrow width and length(y2) has to be calculated during plotting!
          GetSubSig(iProj,projOnMee)->AttachArrow(arrow_SubSig, binwidth);
        }
        // ULS
        upper_limit = (upper_limit_raw + LS_raw) * finalToRaw_ratio; // now it represents upper limit on ULS!
        LmHelper::Debug(Form(" upper_limit scaled to final ULS = %f", upper_limit), 10-debugSignal);
        TArrow* arrow_ULS = new TArrow(bincenter, upper_limit, bincenter, upper_limit/100, 0.05, "|->"); // better arrow width and length(y2) has to be calculated during plotting!
        GetUnlike(iProj,projOnMee)->AttachArrow(arrow_ULS, binwidth);
      }

      else if(cockRef && GetSubSig(iProj,projOnMee)->GetDatahist()->GetBinContent(bin)-GetSubSig(iProj,projOnMee)->GetDatahist()->GetBinError(bin)< 0)
      {
      // if (GetBkg(iProj,projOnMee)->GetDatahist()->GetBinContent(bin) > 0) // will compute all arrows, except for empty bins at low pair-pT...
      // {
        LmHelper::Debug(Form(" to low bin after cocktail subtraction: %i, low edge: %f", bin, GetSubSig(iProj,projOnMee)->GetDatahist()->GetBinLowEdge(bin)), 10-debugSignal);
        Double_t subSig = GetSubSig(iProj,projOnMee)->GetDatahist()->GetBinContent(bin);
        Double_t subSig_statErr = GetSubSig(iProj,projOnMee)->GetDatahist()->GetBinError(bin);
        Double_t subSig_systErr = GetSubSig(iProj,projOnMee)->GetSystError()->GetErrorYhigh(bin-1);
        std::cout << "arrow calc: " << subSig_systErr << std::endl;
        Double_t upper_limit = subSig + 1.645*sqrt(subSig_statErr*subSig_statErr + subSig_systErr*subSig_systErr);
        LmHelper::Debug(Form(" upper_limit scaled to final subtracted signal = %f", upper_limit), 10-debugSignal);

        // these numbers are just for positioning and scaling the arrow:
        Double_t binwidth  = GetSubSig(iProj,projOnMee)->GetDatahist()->GetBinWidth(bin);
        Double_t bincenter = GetSubSig(iProj,projOnMee)->GetDatahist()->GetBinCenter(bin);

        // Subtracted Signal
        if (upper_limit > 0) { // no reason to compute arrow if still oversubtracted.
          TArrow* arrow_SubSig = new TArrow(bincenter, upper_limit, bincenter, upper_limit - sqrt(subSig_statErr*subSig_statErr + subSig_systErr*subSig_systErr) , 0.05, "|->"); // better arrow width and length(y2) has to be calculated during plotting!
          GetSubSig(iProj,projOnMee)->AttachArrow(arrow_SubSig, binwidth);
          //GetSubSig(iProj,projOnMee)->GetDatahist()->SetBinContent(bin,0.00000001);
          //GetSubSig(iProj,projOnMee)->GetSystError()->SetPoint(bin-1,bincenter, 0.0000001);
          GetSubSig(iProj,projOnMee)->GetDatahist()->SetBinError(bin,0.00000001);
          GetSubSig(iProj,projOnMee)->GetSystError()->SetPointEYhigh(bin-1, 0.000000);
          GetSubSig(iProj,projOnMee)->GetSystError()->SetPointEYlow(bin-1, 0.000000);
          GetSubSig(iProj,projOnMee)->GetSystError()->SetPointEXhigh(bin-1, 0.000000);
          GetSubSig(iProj,projOnMee)->GetSystError()->SetPointEXlow(bin-1, 0.000000);
        }
      }



    } // histogram bins
  } // projections
}


//_______________________________________________________________________________________________
void LmSignal::InitFromRootfile(TString filename, Int_t ikey, TString dirname)
{
  /// Set up LmSignal with 2D histograms from a rootfile that was previously written by LmHandler::Write2DHist(LmSignal::kMAXhist-1, kFALSE).
  /// Such rootfile contains a subfolder for each written signal. One can select a signal either by the index
  /// (specify ikey - starting from 0) or by the name of its subfolder (if ikey <= -1).
  /// If the LmSignal has no name yet, it will be named like the subfolder name (or title in case of using ikey).
  TDirectory* dir = 0x0;
  TFile* infile = LmHelper::SafelyOpenRootfile(filename.Data());
  if (ikey>-1 && ikey<infile->GetListOfKeys()->GetEntries())
    dir = infile->GetDirectory( infile->GetListOfKeys()->At(ikey)->GetName(), kTRUE );
  else
    dir = infile->GetDirectory( dirname.Data(), kTRUE );
  InitFromRootfile(dir);
  infile->Close();
  delete infile;
}

//_______________________________________________________________________________________________
void LmSignal::InitFromRootfile(TDirectory* dir)
{
  /// For description see: LmSignal::InitFromRootfile(TString filename, Int_t ikey, TString dirname).
  if (!dir) { LmHelper::Error("LmSignal::InitFromRootfile(): could not find signal directory. Specify valid key index or valid directory name."); return; }
  Bool_t debug_init=kFALSE;
  TList* keys = dir->GetListOfKeys();
  if (debug_init) keys->Print();

  if (fName.compare("default")==0 || fName.compare("")==0)
    fName = dir->GetTitle(); // the name could be enumerated ("cut %02d"), but the title is always meaningful.

  if (!fLmMgr) {
    fLmMgr = new LmManager((char*)""); fOwnerMgr=kTRUE;
    fLmMgr->SetInputhistAndDim("", 2); // This internally calls LmManager::InitProjectionRanges(), which is needed.
  }

  TString sValue;
  Double_t valmin, valmax;
  for (Int_t i=0; i<keys->GetEntries(); ++i)
  {
    TString keyname = keys->At(i)->GetName();
    //
    // Put checks with more complex names before the simpler ones!
    // Otherwise the 'Contains()' logic will give wrong results.
    //
    // input infos
    if (keyname.Contains("Number of events: ", TString::kIgnoreCase)) {
      sValue = keyname(keyname.First(':')+2,100);
      if (debug_init) cout << "nevents = " << sValue.Data() << endl;
      SetNeventsPhysSel(atof(sValue.Data()));
      fLmMgr->SetNeventsPhysSel(atof(sValue.Data())); // maybe good for consistency.
    }
    else if (keyname.Contains("Collision system: ", TString::kIgnoreCase)) {
      sValue = keyname(keyname.First(':')+2,100);
      if (debug_init) cout << "collision system = " << sValue.Data() << endl;
      fLmMgr->SetCollSystem(sValue);
    }
    else if (keyname.Contains("Collision energy: ", TString::kIgnoreCase)) {
      sValue = keyname(keyname.First(':')+2,100);
      if (debug_init) cout << "collision energy = " << sValue.Data() << endl;
      fLmMgr->SetCollEnergy(sValue);
    }
    else if (   keyname.Contains("Centrality_min = ", TString::kIgnoreCase)
             && keyname.Contains("Centrality_max = ", TString::kIgnoreCase)) {
      sValue = keyname(keyname.First('=')+2,3);
      valmin = atof(sValue.Data());
      sValue = keyname(keyname.Last('=')+2,3);
      valmax = atof(sValue.Data());
      if (debug_init) cout << "centrality = " << valmin << " to " << valmax << endl;
      fLmMgr->SetCentRange(valmin, valmax);
    }
    else if (   keyname.Contains("Pt_min = ", TString::kIgnoreCase)
             && keyname.Contains("Pt_max = ", TString::kIgnoreCase)) {
      sValue = keyname(keyname.First('=')+2,5);
      valmin = atof(sValue.Data());
      sValue = keyname(keyname.Last('=')+2,5);
      valmax = atof(sValue.Data());
      if (debug_init) cout << "Pt = " << valmin << " to " << valmax << endl;
      fLmMgr->SetPtRange(valmin, valmax);
    }
    else if (   keyname.Contains("Eta_min = ", TString::kIgnoreCase)
             && keyname.Contains("Eta_max = ", TString::kIgnoreCase)) {
      sValue = keyname(keyname.First('=')+2,5);
      valmin = atof(sValue.Data());
      sValue = keyname(keyname.Last('=')+2,5);
      valmax = atof(sValue.Data());
      if (debug_init) cout << "Eta = " << valmin << " to " << valmax << endl;
      fLmMgr->SetEtaRange(valmin, valmax);
    }
    else if (keyname.Contains("Opening angle cut: ", TString::kIgnoreCase)) {
      sValue = keyname(keyname.First(':')+2,100);
      if (debug_init) cout << "Opening angle cut = " << sValue.Data() << endl;
      fLmMgr->SetThetaEEmin(atof(sValue.Data()));
    }
    // histograms
    else if (keyname.Contains("SigNoEffi", TString::kIgnoreCase)) {
      fSigNoEffi = (TH2D*) dir->Get(keyname.Data())->Clone("hSigNoEffi");
      if (debug_init) fSigNoEffi->Print();
    }
    else if (keyname.Contains("UnlikeNoEffi", TString::kIgnoreCase)) {
      fUnlikeNoEffi = (TH2D*) dir->Get(keyname.Data())->Clone("hUnlikeNoEffi");
      if (debug_init) fUnlikeNoEffi->Print();
    }
    else if (keyname.Contains("BkgNoEffi", TString::kIgnoreCase)) {
      fBkgNoEffi = (TH2D*) dir->Get(keyname.Data())->Clone("hBkgNoEffi");
      if (debug_init) fBkgNoEffi->Print();
    }
    else if (keyname.Contains("_sysLow", TString::kIgnoreCase)) {
      fSystematicLow = (TH2D*) dir->Get(keyname.Data())->Clone("hSubSig_sysLow");
      if (debug_init) fSystematicLow->Print();
    }
    else if (keyname.Contains("_sysHigh", TString::kIgnoreCase)) {
      fSystematicHigh = (TH2D*) dir->Get(keyname.Data())->Clone("hSubSig_sysHigh");
      if (debug_init) fSystematicHigh->Print();
    }
    else if (keyname.Contains("SubSig", TString::kIgnoreCase)) { // has to be checked after the '_sys' histograms
      fSubSig = (TH2D*) dir->Get(keyname.Data())->Clone("hSubSig");
      SetSubtractionDone(kTRUE);
      SetDoSubtraction(kFALSE);
      if (debug_init) fSubSig->Print();
      if (! TString(fSubSig->GetZaxis()->GetTitle()).Contains("raw")) SetEffiApplied(kTRUE); // no 'else'!
    }
    else if (keyname.Contains("Unlike", TString::kIgnoreCase)) { // has to be checked after the 'NoEffi' histograms
      fUnlike = (TH2D*) dir->Get(keyname.Data())->Clone("hUnlike");
      if (debug_init) fUnlike->Print();
      if (! TString(fUnlike->GetZaxis()->GetTitle()).Contains("raw")) SetEffiApplied(kTRUE); // no 'else'!
    }
    else if (keyname.Contains("Bkg", TString::kIgnoreCase)) {
      fBkg = (TH2D*) dir->Get(keyname.Data())->Clone("hBkg");
      if (debug_init) fBkg->Print();
    }
    // ...
  }
  // By default, the 2D spectra in the rootfile should not contain any normalizations.
  // If this was manipulated during LmHandler::Write2DHist(), please call these setters again as appropriate.
  SetDoNormBinwidth(kTRUE);
  SetDoNormNevents(kTRUE);
}


//_______________________________________________________________________________________________
TH2D* LmSignal::CalcSubtractedSignal(const TH2D* hUnlike, const TH2D* hLike, const Char_t* newname)
{
  LmHelper::Debug("  CalcSubtractedSignal()", 6-debugSignal);
  TH2D* hSub = (TH2D*) hUnlike->Clone(newname);
  hSub->Add(hLike,-1.);
  SetSubtractionDone();
  // Check in LmManager if any further corrections are needed and execute them.
  if (fLmMgr) fLmMgr->SignalPostCorrection(hSub);

  UpdateTitleSubtracted(hSub);
  return hSub;
}

//_______________________________________________________________________________________________
void LmSignal::UpdateTitleSubtracted(TH2D* hSub)
{
  TString sTitle(hSub->GetZaxis()->GetTitle());
  sTitle.ReplaceAll("unsubtr. ","");
  hSub->SetZTitle(sTitle.Data());
  hSub->SetTitle(sTitle.Data());
}


// MAKE SURE to change 1D and 2D functions consistently! (or write it smarter...)
//_______________________________________________________________________________________________
TH2D* LmSignal::CalcSignalBackgroundRatio2D(const TH2D* hSignal, const TH2D* hBackground, const Char_t* newname)
{
  LmHelper::Debug("  CalcSignalBackgroundRatio2D()", 6-debugSignal);
  //  cout << "===CalcSignalBackgroundRatio2D: ERROR PROPAGATION MAY BE WRONG!======" << endl;
  TH2D* hSigBackRatio = (TH2D*) hSignal->Clone(newname);
	hSigBackRatio->Divide(hBackground);
  //
  TString texSoverB = GetLabelSig()+"/"+GetLabelBkg();
  hSigBackRatio->SetZTitle(texSoverB.Data()); // watch out with Z and Y!
  hSigBackRatio->SetTitle(texSoverB.Data());
  return hSigBackRatio;
}
// MAKE SURE to change 1D and 2D functions consistently! (or write it smarter...)
//_______________________________________________________________________________________________
TH1D* LmSignal::CalcSignalBackgroundRatio1D(const TH1D* hSignal, const TH1D* hBackground, const Char_t* newname)
{
  LmHelper::Debug("  CalcSignalBackgroundRatio1D()", 6-debugSignal);
  //  cout << "===CalcSignalBackgroundRatio1D: ERROR PROPAGATION MAY BE WRONG!======" << endl;
  TH1D* hSigBackRatio = (TH1D*) hSignal->Clone(newname);
	hSigBackRatio->Divide(hBackground);
  //
  TString texSoverB = GetLabelSig()+"/"+GetLabelBkg();
  hSigBackRatio->SetYTitle(texSoverB.Data()); // watch out with Z and Y!
  hSigBackRatio->SetTitle(texSoverB.Data());
  return hSigBackRatio;
}


// MAKE SURE to change 1D and 2D functions consistently! (or write it smarter...)
//_______________________________________________________________________________________________
TH2D* LmSignal::CalcSignificance2D(const TH2D* hSignal, const TH2D* hBackground, const Char_t* newname)
{
  LmHelper::Debug("  CalcSignificance2D()", 6-debugSignal);
  //  cout << "===CalcSignificance2D: ERROR PROPAGATION MAY BE WRONG!======" << endl;
  TH2D* hSignifSplusB = (TH2D*) hSignal->Clone(newname);

  TString texSignifSplus2B_plain = GetLabelSig()+"/#sqrt{"+GetLabelSig()+"+2"+GetLabelBkg()+"}";
  TString texSignifSplusB_plain  = GetLabelSig()+"/#sqrt{"+GetLabelSig()+"+"+GetLabelBkg()+"}";
  Double_t bkgFactor = 0;
  if (TString(newname).Contains("2B")) {
    bkgFactor = 2.;
    hSignifSplusB->SetZTitle(texSignifSplus2B_plain.Data()); // watch out with Z and Y!
    hSignifSplusB->SetTitle(texSignifSplus2B_plain.Data());
  }
  else {
    bkgFactor = 1.;
    hSignifSplusB->SetZTitle(texSignifSplusB_plain.Data()); // watch out with Z and Y!
    hSignifSplusB->SetTitle(texSignifSplusB_plain.Data());
  }

  Double_t ySig,yBkg,ySigerr,yBkgerr;
  Double_t ys,yserr;

  // old 1D version:
	//for (int globalbin=1; globalbin < hSignal->GetNbinsX(); globalbin++) {

  for (Int_t bx=0;bx <= hSignal->GetNbinsX()+1; bx++) {
    for (Int_t by=0;by <= hSignal->GetNbinsY()+1; by++) {
      Int_t globalbin=hSignal->GetBin(bx,by);

      ySig = hSignal->GetBinContent(globalbin);
      ySigerr = hSignal->GetBinError(globalbin);
      yBkg = hBackground->GetBinContent(globalbin) * bkgFactor;
      yBkgerr = hBackground->GetBinError(globalbin) * bkgFactor;
      if (ySig == 0) ySigerr=0.;
      else           ySigerr/=ySig;
      if (yBkg == 0) yBkgerr=0.;
      else           yBkgerr/=yBkg;

      if (yBkg != 0) {
        ys = ySig/TMath::Sqrt(ySig+yBkg);
        yserr = TMath::Sqrt(ySigerr*ySigerr+yBkgerr*yBkgerr)*ys;
        // TODO: error from derivation by hand
      }
      else {ys=0; yserr=0.;}
      hSignifSplusB->SetBinContent(globalbin,ys);
      hSignifSplusB->SetBinError(globalbin,yserr);
    }
  }

  TString sTitle(hSignifSplusB->GetZaxis()->GetTitle());
  if (!GetDoSignifRaw() && GetDoNormNevents())  sTitle.Append(" /#sqrt{#it{N}_{ev}}");
  if (!GetDoSignifRaw() && GetDoNormBinwidth()) {
    if      (CheckWhichProjection(hSignifSplusB)==kProjOnX) sTitle.Append(" ("+GetProjLabelXunit()+")^{-1/2}");
    else if (CheckWhichProjection(hSignifSplusB)==kProjOnY) sTitle.Append(" ("+GetProjLabelYunit()+")^{-1/2}");
    else    LmHelper::Error("LmSignal::CalcSignificance(): cannot give correct normalization unit.");
  }
  hSignifSplusB->SetZTitle(sTitle.Data()); // watch out with Z and Y!
  hSignifSplusB->SetTitle(sTitle.Data());

  return hSignifSplusB;
}
// MAKE SURE to change 1D and 2D functions consistently! (or write it smarter...)
//_______________________________________________________________________________________________
TH1D* LmSignal::CalcSignificance1D(const TH1D* hSignal, const TH1D* hBackground, const Char_t* newname)
{
  LmHelper::Debug("  CalcSignificance1D()", 6-debugSignal);
  //  cout << "===CalcSignificance1D: ERROR PROPAGATION MAY BE WRONG!======" << endl;
  TH1D* hSignifSplusB = (TH1D*) hSignal->Clone(newname);

  TString texSignifSplus2B_plain = GetLabelSig()+"/#sqrt{"+GetLabelSig()+"+2"+GetLabelBkg()+"}";
  TString texSignifSplusB_plain  = GetLabelSig()+"/#sqrt{"+GetLabelSig()+"+"+GetLabelBkg()+"}";
  Double_t bkgFactor = 0;
  if (TString(newname).Contains("2B")) {
    bkgFactor = 2.;
    hSignifSplusB->SetYTitle(texSignifSplus2B_plain.Data()); // watch out with Z and Y!
    hSignifSplusB->SetTitle(texSignifSplus2B_plain.Data());
  }
  else {
    bkgFactor = 1.;
    hSignifSplusB->SetYTitle(texSignifSplusB_plain.Data()); // watch out with Z and Y!
    hSignifSplusB->SetTitle(texSignifSplusB_plain.Data());
  }

  Double_t ySig,yBkg,ySigerr,yBkgerr;
  Double_t ys,yserr;

	for (int globalbin=0; globalbin <= hSignal->GetNbinsX(); globalbin++) {
    ySig = hSignal->GetBinContent(globalbin);
    ySigerr = hSignal->GetBinError(globalbin);
    yBkg = hBackground->GetBinContent(globalbin) * bkgFactor;
    yBkgerr = hBackground->GetBinError(globalbin) * bkgFactor;
    if (ySig == 0) ySigerr=0.;
    else           ySigerr/=ySig;
    if (yBkg == 0) yBkgerr=0.;
    else           yBkgerr/=yBkg;

    if (yBkg != 0) {
      ys = ySig/TMath::Sqrt(ySig+yBkg);
      yserr = TMath::Sqrt(ySigerr*ySigerr+yBkgerr*yBkgerr)*ys;
      // TODO: error from derivation by hand
    }
    else {ys=0; yserr=0.;}
    hSignifSplusB->SetBinContent(globalbin,ys);
    hSignifSplusB->SetBinError(globalbin,yserr);
  }

  TString sTitle(hSignifSplusB->GetYaxis()->GetTitle());
  if (!GetDoSignifRaw() && GetDoNormNevents())  sTitle.Append(" /#sqrt{#it{N}_{ev}}");
  if (!GetDoSignifRaw() && GetDoNormBinwidth()) {
    if      (CheckWhichProjection(hSignifSplusB)==kProjOnX) sTitle.Append(" ("+GetProjLabelXunit()+")^{-1/2}");
    else if (CheckWhichProjection(hSignifSplusB)==kProjOnY) sTitle.Append(" ("+GetProjLabelYunit()+")^{-1/2}");
    else    LmHelper::Error("LmSignal::CalcSignificance(): cannot give correct normalization unit.");
  }
  hSignifSplusB->SetYTitle(sTitle.Data()); // watch out with Z and Y!
  hSignifSplusB->SetTitle(sTitle.Data());

  return hSignifSplusB;
}


//_______________________________________________________________________________________________
void LmSignal::ApplyEfficiency2D(TH2D& hIn, const TH2D* hEffi)
{
  LmHelper::Debug(Form(" ApplyEfficiency2D(hIn:'%s')",hIn.GetName()), 5-debugSignal);
  TH2D* hOut = new TH2D(hIn);

  //check binning first:
  //cout << "  x in: " << hOut->GetXaxis()->GetBinLowEdge(10) << "  effi: " << hEffi->GetXaxis()->GetBinLowEdge(10) << endl;
  //cout << "  y in: " << hOut->GetYaxis()->GetBinLowEdge(5) << "  effi: " << hEffi->GetYaxis()->GetBinLowEdge(5) << endl;
  cout << "  x in: " << hOut->GetXaxis()->GetNbins() << "  effi: " << hEffi->GetXaxis()->GetNbins() << endl;
  cout << "  y in: " << hOut->GetYaxis()->GetNbins() << "  effi: " << hEffi->GetYaxis()->GetNbins() << endl;

  if ( TMath::Abs(hEffi->GetXaxis()->GetBinLowEdge(10) - hOut->GetXaxis()->GetBinLowEdge(10)) > 0.00001 ) {
    LmHelper::Error("LmSignal::ApplyEfficiency2D(): inconsistent binning in X! not correcting for efficiency!"); return;
  }
  if ( TMath::Abs(hEffi->GetYaxis()->GetBinLowEdge(5) - hOut->GetYaxis()->GetBinLowEdge(5)) > 0.00001 ) {
    LmHelper::Error("LmSignal::ApplyEfficiency2D(): inconsistent binning in Y! not correcting for efficiency!"); return;
  }


  for(Int_t ix = 1; ix <= hEffi->GetNbinsX(); ++ix){
    for(Int_t iy = 1; iy <= hEffi->GetNbinsY(); ++iy){
      if (ix > hOut->GetNbinsX()) break;
      if (iy > hOut->GetNbinsY()) break;
      Double_t eff(0.),val(0.),valerr(0.);
      eff    = hEffi->GetBinContent(ix,iy);

      val    = hOut->GetBinContent(ix,iy);
      valerr = hOut->GetBinError(ix,iy);
      if(eff > 0.) {
        val/=eff; valerr/=eff;
      }
      hOut->SetBinContent(ix,iy,val);
      hOut->SetBinError(ix,iy,valerr); // may not be meaningful, statistics have to be recomputed!
    }
  }

  //const char* texEffi="#epsilon_{corr} ";
  TString sTitle(hOut->GetZaxis()->GetTitle());
  sTitle.ReplaceAll("raw ","");
  //sTitle.Prepend(texEffi);
  hOut->SetZTitle(sTitle.Data());
  hOut->SetTitle(sTitle.Data());
  hIn = *hOut;
  delete hOut;
  return;
}

//_______________________________________________________________________________________________
void LmSignal::ApplyEfficiency2D_all(const TH2D* hEffi)
{
  /// Note that efficiency correction for unsubtracted spectra may not be really meaningful, because the efficiency
  /// is typically determined based on signal pairs, and the one for background pairs may be different.
  if (GetEffiApplied()) { LmHelper::Warning("LmSignal::ApplyEfficiency2D_all(): Efficiency already applied! Skip it."); return; }
  if (fSubSig) ApplyEfficiency2D(*fSubSig, hEffi);
  if (fUnlike) ApplyEfficiency2D(*fUnlike, hEffi);
  ApplyEfficiency2D(*fBkg, hEffi);
  SetEffiApplied();
  return;
}

//_______________________________________________________________________________________________
void LmSignal::ApplyAcceptance2D(const TH2D* hAcce)
{

  TH2D* hIn  = fSubSig;
  TH2D* hOut = new TH2D(*hIn);
  LmHelper::Debug(Form(" ApplyAcceptance2D(hIn:'%s')",hIn->GetName()), 5-debugSignal);

  //check binning first:
  cout << "  x in: " << hOut->GetXaxis()->GetBinLowEdge(10) << "  " << hIn->GetNbinsX() << "  acce: " << hAcce->GetXaxis()->GetBinLowEdge(10) << "  " << hAcce->GetNbinsX() << endl;
  cout << "  y in: " << hOut->GetYaxis()->GetBinLowEdge(5) << "  " << hIn->GetNbinsY() << "  acce: " << hAcce->GetYaxis()->GetBinLowEdge(5) << "  " << hAcce->GetNbinsY()  << endl;
  if ( TMath::Abs(hAcce->GetXaxis()->GetBinLowEdge(10) - hOut->GetXaxis()->GetBinLowEdge(10)) > 0.00001 ) {
    LmHelper::Error("LmSignal::ApplyAcceptance2D(): inconsistent binning in X! not correcting for acceptance!"); return;
  }
  LmHelper::Debug(Form(" ApplyAcceptance2D(hIn:'%s')",hIn->GetName()), 5-debugSignal);
  if ( TMath::Abs(hAcce->GetYaxis()->GetBinLowEdge(5) - hOut->GetYaxis()->GetBinLowEdge(5)) > 0.00001 ) {
    LmHelper::Error("LmSignal::ApplyAcceptance2D(): inconsistent binning in Y! not correcting for acceptance!"); return;
  }
  LmHelper::Debug(Form(" ApplyAcceptance2D(hIn:'%s')",hIn->GetName()), 5-debugSignal);
  if ( (hIn->GetNbinsX() == hAcce->GetNbinsX()) && (hIn->GetNbinsY() == hAcce->GetNbinsY()) ) {
    LmHelper::Error("LmSignal::ApplyAcceptance2D(): inconsistent binning in Y! not correcting for acceptance!"); return;
  }

  LmHelper::Debug("stand the checks", 5-debugSignal);
  for(Int_t ix = 1; ix <= hAcce->GetNbinsX(); ++ix){
    for(Int_t iy = 1; iy <= hAcce->GetNbinsY(); ++iy){
      if (ix > hOut->GetNbinsX()) break;
      if (iy > hOut->GetNbinsY()) break;
      Double_t acceCorr(0.),val(0.),valerr(0.);
      acceCorr  = hAcce->GetBinContent(ix,iy);

      val    = hOut->GetBinContent(ix,iy);
      valerr = hOut->GetBinError(ix,iy);
      if(acceCorr > 0.) {
        val/=acceCorr; valerr/=acceCorr;
      }
      hOut->SetBinContent(ix,iy,val);
      hOut->SetBinError(ix,iy,valerr); // may not be meaningful, statistics have to be recomputed!
    }
  }

  LmHelper::Debug("almost done", 5-debugSignal);
  //const char* texEffi="#epsilon_{corr} ";
  TString sTitle(hOut->GetZaxis()->GetTitle());
  //sTitle.Prepend(texEffi);
  hOut->SetZTitle(sTitle.Data());
  hOut->SetTitle(sTitle.Data());
  hIn = (TH2D*)hOut->Clone(hOut->GetName());
  delete hOut;

  SetAcceApplied(kTRUE);
  return;
}


//_______________________________________________________________________________________________
void LmSignal::Rebin2DHistogram_all()
{
  /// Rebin all 2D histograms according to binning given by LmRebinner::SetRebinning2D()/SetRebinningX()/SetRebinningY().
  /// Uses function LmRebinner::Rebin2DHistogram().
  LmHelper::Debug(" LmSignal::Rebin2DHistogram_all()", 5);

  //LmHelper::Warning(" LmSignal::Rebin2DHistogram_all(): statistical error may become wrong. Fix it in LmRebinner::Rebin2DHistogram()");
  if (GetUnlike2D()      ) Rebin2DHistogram(*GetUnlike2D()      );
  if (GetBkg2D()         ) Rebin2DHistogram(*GetBkg2D()         );
  if (GetSubSig2D()      ) Rebin2DHistogram(*GetSubSig2D()      );
  if (GetUnlikeNoEffi2D()) Rebin2DHistogram(*GetUnlikeNoEffi2D());
  if (GetBkgNoEffi2D()   ) Rebin2DHistogram(*GetBkgNoEffi2D()   );
  if (GetSigNoEffi2D()   ) Rebin2DHistogram(*GetSigNoEffi2D()   );
//if (GetSoverB()        ) Rebin2DHistogram(*GetSoverB()        ); // dont rebin ratios!
//if (GetSignif()        ) Rebin2DHistogram(*GetSignif()        ); // dont rebin ratios!
  return;
}

//_______________________________________________________________________________________________
Bool_t LmSignal::CheckAndDeleteOldProjections(Bool_t projOnMee)
{
  if (projOnMee==LmBaseSignal::kProjOnMee) {
    if(GetMaxBin_projMee()>-1) {
      fSubSig_projMee.clear();
      fUnlike_projMee.clear();
      fBkg_projMee.clear();
      fRfactor_projMee.clear();
      fSoverB_projMee.clear();
      fSignif_projMee.clear();
      fUnlikeMix_projMee.clear();
      fLikeMix_projMee.clear();
      fUnlikeNoEffiUnnorm_projMee.clear();
      fBkgNoEffiUnnorm_projMee.clear();
      LmHelper::Debug(Form(" LmSignal::CheckAndDeleteOldProjections(): previous Mee projections deleted from LmSignal '%s'.", GetName()), 5-debugSignal);
      return kTRUE;
    }
  }
  if (projOnMee==LmBaseSignal::kProjOnPtee) {
    if(GetMaxBin_projPtee()>-1) {
      fSubSig_projPtee.clear();
      fUnlike_projPtee.clear();
      fBkg_projPtee.clear();
      fRfactor_projPtee.clear();
      fSoverB_projPtee.clear();
      fSignif_projPtee.clear();
      fUnlikeMix_projPtee.clear();
      fLikeMix_projPtee.clear();
      fUnlikeNoEffiUnnorm_projPtee.clear();
      fBkgNoEffiUnnorm_projPtee.clear();
      LmHelper::Debug(Form(" LmSignal::CheckAndDeleteOldProjections(): previous Ptee projections deleted from LmSignal '%s'.", GetName()), 5-debugSignal);
      return kTRUE;
    }
  }
  return kFALSE;
}

//_______________________________________________________________________________________________
void LmSignal::PrintUnlike(const Char_t* filename)
{
  TCanvas* can = new TCanvas("unlike", "unlike");
  can->cd();
  LmHelper::TH2_Beautify(fUnlike, can);
  fUnlike->DrawCopy("colz");
  can->Print(filename);
  delete can;
}

//_______________________________________________________________________________________________
void LmSignal::PrintSig(const Char_t* filename)
{
  TCanvas* can = new TCanvas("sig", "sig");
  can->cd()->SetLogz();
  if (debugSyst) {
    can->cd()->SetLogz(kFALSE);
    GetSig2D()->SetMinimum(0.); // to clearly see oversubtraction
  }
  LmHelper::TH2_Beautify(GetSig2D(), can);
  GetSig2D()->DrawCopy("colz");
  can->Print(filename);
  delete can;
}

//_______________________________________________________________________________________________
void LmSignal::PrintSoverB(const Char_t* filename)
{
  TCanvas* can = new TCanvas("soverb", "soverb");
  can->cd()->SetLogz();
  if (debugSyst) {
    can->cd()->SetLogz(kFALSE);
    GetSoverB()->SetMinimum(0.); // to clearly see oversubtraction
  }
  LmHelper::TH2_Beautify(GetSoverB(), can);
  GetSoverB()->DrawCopy("colz");
  can->Print(filename);
  delete can;
}

//_______________________________________________________________________________________________
void LmSignal::PrintSignif(const Char_t* filename)
{
  TCanvas* can = new TCanvas("signif", "signif");
  can->cd()->SetLogz();
  if (debugSyst) {
    can->cd()->SetLogz(kFALSE);
    GetSignif()->SetMinimum(0.); // to clearly see oversubtraction
  }
  LmHelper::TH2_Beautify(GetSignif(), can);
  GetSignif()->DrawCopy("colz");
  can->Print(filename);
  delete can;
}


//_______________________________________________________________________________________________
void LmSignal::WriteHist1D(unsigned int histBits, const std::vector<Double_t> bins, Bool_t simplehistnames, Bool_t projOnMee, TString signame)
{
  LmHelper::Debug(Form(" WriteHist1D(projOnMee=%i)", projOnMee), 5-debugSignal);

  Int_t     maxbin = GetMaxBinProj(projOnMee); // maxbin cannot be unsigned.
  Double_t  projmin=-1, projmax=-1;
  TString   projrange;
  if (!signame.IsNull()) signame.Prepend("-");

  if (bins.size()==0) {LmHelper::Error("LmSignal::WriteHist1D(): no bins for projections set."); return;}
  if ((Int_t)bins.size()!=maxbin+1) {
    LmHelper::Error("LmSignal::WriteHist1D(): wrong number of projection bins. Process handler again."); return;}

  for (unsigned int ibin = 0; (Int_t)ibin <= maxbin; ++ibin) { // cast to Int_t needed to avoid compiler warning.
    if (maxbin==1 && ibin==1) break; // in case of one integrated bin: do not write same projection twice.
    if (ibin < bins.size()-1) {
      projmin = bins.at(ibin);
      projmax = bins.at(ibin+1);
    }
    else { // for integrated projection (last entry in projection vectors)
      projmin = bins.at(0);
      projmax = bins.at(bins.size()-1); // last entry in bins vector
    }

    for (unsigned int iBit = 1; iBit < kMAXhist; iBit *= 2) {
      if ( !(iBit & histBits) ) continue; // continue if current histogram was not requested.
      LmHistogram* lmTemp = GetLmHist(iBit,ibin,projOnMee);
      if (!lmTemp) continue;
      TH1D* hTemp = lmTemp->GetDatahist();

      if (projOnMee==LmBaseSignal::kProjOnMee)  projrange=(Form("ptee%.2fto%.2f",projmin,projmax));
      else                                      projrange=(Form("mee%.2fto%.2f",projmin,projmax));

      if (simplehistnames) hTemp->SetName(Form("h%s-%s%s",GetCharHistBit(iBit,kTRUE),projrange.Data(),signame.Data()));
      // otherwise it will use the long names which are put together during the signal processing.
      // they include info on: signal fType, background fType, if Rfactor was applied and its fType (&maybe more to come).
      // the projection range is included in both cases.

      hTemp->GetXaxis()->SetRangeUser(0., -1);
      hTemp->Write();

      // write systematics if available
      TGraphAsymmErrors* grSysTemp = 0x0;
      grSysTemp = GetSystematicGraph(iBit,ibin,projOnMee);
      if (!grSysTemp) continue;
      if (simplehistnames) grSysTemp->SetName(Form("h%s_sys-%s%s",GetCharHistBit(iBit,kTRUE),projrange.Data(),signame.Data()));
      grSysTemp->Write();

    } // end histogram loop
  } // end projection bin loop
}

//_______________________________________________________________________________________________
void LmSignal::WriteHist2D(unsigned int histBits, Bool_t divideByBinWidth, Bool_t simplehistnames)
{
  LmHelper::Debug("WriteHist2D()", 5-debugSignal);

  for (unsigned int iBit = 1; iBit < kMAXhist; iBit *= 2) {
    if ( !(iBit & histBits) ) continue; // continue if current histogram was not requested.
    TH2D* hTemp = 0x0;

    if (iBit == kSubSig)        hTemp = GetSig2D();
    if (iBit == kUnlike)        hTemp = GetUnlike2D();
    if (iBit == kBkg)           hTemp = GetBkg2D();
    if (iBit==kRfactor&&fLmBkg) hTemp = this->fLmBkg->GetRfactor2D();
    if (iBit == kSoverB)        hTemp = GetSoverB();
    if (iBit == kSignif)        hTemp = GetSignif();
    if (iBit == kSigNoEffi)     hTemp = fSigNoEffi;
    if (iBit == kUnlikeNoEffi)  hTemp = fUnlikeNoEffi;
    if (iBit == kBkgNoEffi)     hTemp = fBkgNoEffi;
    if (!hTemp) continue;

    if (simplehistnames) hTemp->SetName(Form("h%s",GetCharHistBit(iBit,kTRUE)));
    // otherwise it will use the long names which are put together during the signal processing.
    // they include info on: signal fType, background fType, if Rfactor was applied and its fType (&maybe more to come).

    if(divideByBinWidth) {
      for(Int_t ix = 1; ix <= hTemp->GetNbinsX(); ++ix){
        for(Int_t iy = 1; iy <= hTemp->GetNbinsY(); ++iy){
          hTemp->SetBinContent(ix,iy,hTemp->GetBinContent(ix,iy) / hTemp->GetXaxis()->GetBinWidth(ix) / hTemp->GetYaxis()->GetBinWidth(iy));
          hTemp->SetBinError(ix,iy,hTemp->GetBinError(ix,iy) / hTemp->GetXaxis()->GetBinWidth(ix) / hTemp->GetYaxis()->GetBinWidth(iy));
        }
      }
    }
    hTemp->Write();

    // write systematics if available
    if (iBit == kSubSig && fSystematicLow && fSystematicHigh) {
      if (simplehistnames) {
        fSystematicLow ->SetName(Form("h%s_sysLow",GetCharHistBit(iBit,kTRUE)));
        fSystematicHigh->SetName(Form("h%s_sysHigh",GetCharHistBit(iBit,kTRUE)));
      }
      fSystematicLow->Write();
      fSystematicHigh->Write();
    }

  } // end histogram loop
}

//_______________________________________________________________________________________________
void LmSignal::WriteHist3D(unsigned int histBits)
{
  LmHelper::Debug("WriteHist3D()", 5-debugSignal);

  for (unsigned int iBit = 1; iBit < kMAXhist; iBit *= 2) {
    if ( !(iBit & histBits) ) continue; // continue if current histogram was not requested.
    if (!fLmMgr) { LmHelper::Error("LmSignal::WriteHist3D(): no manager available."); return; }
    TH3D* hTemp = 0x0;

    if (iBit == kUnlike) hTemp = new TH3D(*(fLmMgr->GetHist3D(0)));
    if (iBit == kBkg) {
      LmHelper::Warning("LmSignal::WriteHist3D(): saving arithmetic like sign (geometric is statistically critical).");
      hTemp = new TH3D(*(fLmMgr->GetHist3D(1)));
      hTemp->Add(fLmMgr->GetHist3D(2));
    }
    if (iBit == kUnlikeMix) {
      LmHelper::Warning("LmSignal::WriteHist3D(): saving arithmetic mixed event unlike sign (geometric is statistically critical).");
      hTemp = new TH3D(*(fLmMgr->GetHistMix3D(0)));
      hTemp->Add(fLmMgr->GetHistMix3D(3));
    }
    if (iBit == kLikeMix) {
      LmHelper::Warning("LmSignal::WriteHist3D(): saving arithmetic mixed event like sign (geometric is statistically critical).");
      hTemp = new TH3D(*(fLmMgr->GetHistMix3D(1)));
      hTemp->Add(fLmMgr->GetHistMix3D(2));
    }
    if (!hTemp) {
      LmHelper::Warning(Form("LmSignal::WriteHist3D(): saving of histogram '%s' not implemented (probably it does not exist in 3D).", GetCharHistBit(iBit,kTRUE)));
      continue;
    }

    hTemp->SetName(Form("h%s",GetCharHistBit(iBit,kTRUE))); // always use "simplehistnames"
    hTemp->Write();
    delete hTemp;
  } // end histogram loop
}

//_______________________________________________________________________________________________
LmHistogram* LmSignal::GetLmHist(unsigned int histBit, Int_t bin, Bool_t projOnMee) const
{
  switch (histBit) {
    case kSubSig:   return GetSubSig(bin, projOnMee);
    case kUnlike:   return GetUnlike(bin, projOnMee);
    case kBkg:      return GetBkg(bin, projOnMee);
    case kRfactor:  return GetRfactor(bin, projOnMee);
    case kSoverB:   return GetSoverB(bin, projOnMee);
    case kSignif:   return GetSignif(bin, projOnMee);
    case kUnlikeMix:return GetUnlikeMix(bin, projOnMee);
    case kLikeMix:  return GetLikeMix(bin, projOnMee);
    case kSigNoEffi:    return 0x0;
    case kUnlikeNoEffi: return 0x0; //not an LmHistogram: GetUnlikeNoEffiUnnorm(bin, projOnMee);
    case kBkgNoEffi:    return 0x0; //not an LmHistogram: GetBkgNoEffiUnnorm(bin, projOnMee);
    default: LmHelper::Error("LmSignal::GetLmHist(): 'histBit' must exactly match one histogram type (bit). No multiple types allowed.");
      break;
  }
  return 0x0;
}

//_______________________________________________________________________________________________
TGraphAsymmErrors* LmSignal::GetSystematicGraph(unsigned int histBit, Int_t bin, Bool_t projOnMee) const
{
  if (!HasSystematic()) return 0x0;
  switch (histBit) {
    case kSubSig:   return GetSubSigSystematicGraph(bin, projOnMee);
    case kUnlike:   return 0x0;
    case kBkg:      return 0x0;
    case kRfactor:  return 0x0;
    case kSoverB:   return 0x0;
    case kSignif:   return 0x0;
    case kUnlikeMix:return 0x0;
    case kLikeMix:  return 0x0;
    case kSigNoEffi:    return 0x0;
    case kUnlikeNoEffi: return 0x0;
    case kBkgNoEffi:    return 0x0;
    default: LmHelper::Error("LmSignal::GetSystematicGraph(): 'histBit' must exactly match one histogram type (bit). No multiple types allowed.");
      break;
  }
  return 0x0;
}

//_______________________________________________________________________________________________
LmSignal* LmSignal::GetVisualSigI(UInt_t i) const
{
  if (i>=GetNVisualSig()) return 0x0;
  TH2D* hVisual = fLmMgr->GetVisualSigI(i); // just get the pointer, the setters below do the copying.
  //cout << "LmSignal::GetVisualSigI("<<i<<"): address = " << hVisual << ", title = " << hVisual->GetTitle() << endl;
  LmSignal* newSig = new LmSignal(*this, hVisual->GetName()); // make copy to reuse most information from this signal itself.
  if (!TString(hVisual->GetTitle()).IsNull()) newSig->SetName(hVisual->GetTitle());
  // following are assumptions, which usecases are meaningful:
  if (GetSubtractionDone()) newSig->SetSubSig2D(hVisual);
  else newSig->SetUnlike2D(hVisual);
  return newSig;
}

//_______________________________________________________________________________________________
const char* LmSignal::GetCharHistBit(unsigned int histBit, Bool_t shortname)
{
  return GetCharHistBitStatic(histBit, shortname, GetSubtractionDone(), GetDoSignifRaw());
}

//_______________________________________________________________________________________________
const char* LmSignal::GetCharHistBitStatic(unsigned int histBit, Bool_t shortname, Bool_t subtracted, Bool_t signifraw)
{
  switch (histBit) {

    // Used for performance plots
    case kSubSig:   if (subtracted) return (shortname)?"SubSig":"#it{S} = #it{ULS} - #it{B}"; // else return kUnlike
    case kUnlike:   return (shortname)?"Unlike":"#it{ULS}";
    case kBkg:      return (shortname)?"Bkg"   :"#it{B}";

    // case kSubSig:   if (subtracted) return (shortname)?"SubSig":"subtr. signal"; // else return kUnlike
    // case kUnlike:   return (shortname)?"Unlike":"unlike sign";
    // case kBkg:      return (shortname)?"Bkg"   :"background";
    case kRfactor:  return (shortname)?"Rfac"  :"R factor";
    case kSoverB:   { if (!debugSyst) return (shortname)?"SoverB":"S/B";
                      else            return (shortname)?"SysHigh":"upper syst."; }
    case kSignif:   { if (!debugSyst) { if (signifraw) return (shortname)?"Signif":"significance";
                                        else           return (shortname)?"SignifNorm":"normalized significance"; }
                      else            return (shortname)?"SysLow":"lower syst."; }
    case kUnlikeMix:    return (shortname)?"UnlikeMix"   :"mixed-event unlike sign";
    case kLikeMix:      return (shortname)?"LikeMix"     :"mixed-event like sign";
    case kSigNoEffi:    return (shortname)?"SigNoEffi"   :"signal(subtr.?) w/o effi";
    case kUnlikeNoEffi: return (shortname)?"UnlikeNoEffi":"unlike sign w/o effi";
    case kBkgNoEffi:    return (shortname)?"BkgNoEffi"   :"background w/o effi";
    default: LmHelper::Error("LmSignal::GetCharHistBit(): 'histBit' must exactly match one histogram type (bit). No multiple types allowed.");
      break;
  }
  return "none";
}
