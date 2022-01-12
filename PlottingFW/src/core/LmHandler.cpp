// c++ includes
#include <iostream>
using namespace std;
// ROOT includes
#include "TString.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TObjArray.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TStyle.h" //for gStyle
#include "TObjString.h"
#include "TDirectory.h"
#include "TEnv.h"
// project includes
#include "LmHandler.h"
#include "LmSignal.h"
#include "LmBaseSignal.h"
#include "LmHelper.h"

int debugHandler=0;


//_______________________________________________________________________________________________
LmHandler::LmHandler(Int_t type) : // useful to set type in case calling Process() is not needed.
fSimpleHistnames(kTRUE),
fCocktailProcessed(kFALSE),
fDoConfidenceLevel(kFALSE),
fMarkerSize(1.),
fUseDifferentMarkers(kFALSE),
fLabelsSize(1.),
fDoRatio(kFALSE),
fRatioTitle(""),
fRatioTitleSize(1),
fRatioTitleOffset(1),
fLegendSize(1.),
fLegendLineSizeFactor(1.),
fLegendSizeInYScaling(1.),
fLegendOffsetX(0.),
fLegendOffsetY(0.),
fLabelsOffsetX(0.),
fLabelsOffsetY(0.),
fLegendEntryDrawOption("pe"),
fLegendOnlyFirstCocktail(kFALSE),
fCompareSignalsToAverage(kFALSE),
fOwner(kFALSE),
fName(""),
fType(type),
fTypename(""),
fLmSig(0x0),
fLmSigCombined(0x0),
fLmSigAverage(0x0),
fRelSystematics(0x0),
fLmCocktails(),
fBinsPtee_forprojMee(),
fBinsMee_forprojPtee(),
fMeeBinnings(),
fPteeBinnings(),
fPlotXMeeMin(-1),
fPlotXMeeMax(-1),
fPlotXPteeMin(-1),
fPlotXPteeMax(-1),
fPlotYMin(-1),
fPlotYMax(-1),
fPlotYMarginBelowMin(2.),
fPlotYMarginAboveMax(2.),
fRatioPadSize(0.2),
fPlotRatioMin(-1),
fPlotRatioMax(-1),
fPlotRatioLogy(0),
fLabels(0x0),
fLegend(0x0),
fConfidenceLevel(-1),
fFileOut(0x0),
fDivideOption(""),
fChi2_SignalsToAverage(0x0),
//fBest, // is an array...
fSelectedSig(-1),
fRequestedSignals(""),
fAllowedDiscrepancy(1.),
fFileType("pdf")
{
  /// Default constructor for LmHandler
  /// @param type Type from enum enType (optional)
  /// @see enType

  LmHelper::Debug("LmHandler default constructor", 5-debugHandler);
  SetType(type);

}

//_______________________________________________________________________________________________
LmHandler::LmHandler(std::vector<Double_t> BinsPtee_forprojMee, std::vector<Double_t> BinsMee_forprojPtee, Double_t plotMinMee, Double_t plotMaxMee, Double_t plotMinPtee, Double_t plotMaxPtee) :
fSimpleHistnames(kTRUE),
fCocktailProcessed(kFALSE),
fDoConfidenceLevel(kFALSE),
fMarkerSize(1.),
fUseDifferentMarkers(kFALSE),
fLabelsSize(1.),
fDoRatio(kFALSE),
fRatioTitle(""),
fRatioTitleSize(1),
fRatioTitleOffset(1),
fLegendSize(1.),
fLegendLineSizeFactor(1.),
fLegendSizeInYScaling(1.),
fLegendOffsetX(0.),
fLegendOffsetY(0.),
fLabelsOffsetX(0.),
fLabelsOffsetY(0.),
fLegendEntryDrawOption("pe"),
fLegendOnlyFirstCocktail(kFALSE),
fCompareSignalsToAverage(kFALSE),
fOwner(kFALSE),
fName(""),
fType(0),
fTypename(""),
fLmSig(0x0),
fLmSigCombined(0x0),
fLmSigAverage(0x0),
fRelSystematics(0x0),
fLmCocktails(),
fBinsPtee_forprojMee(BinsPtee_forprojMee),
fBinsMee_forprojPtee(BinsMee_forprojPtee),
fMeeBinnings(), // filled below.
fPteeBinnings(), // filled below.
fPlotXMeeMin(plotMinMee),
fPlotXMeeMax(plotMaxMee-LmHelper::kSmallDelta),
fPlotXPteeMin(plotMinPtee),
fPlotXPteeMax(plotMaxPtee-LmHelper::kSmallDelta),
fPlotYMin(-1),
fPlotYMax(-1),
fPlotYMarginBelowMin(2.),
fPlotYMarginAboveMax(2.),
fRatioPadSize(0.2),
fPlotRatioMin(-1),
fPlotRatioMax(-1),
fPlotRatioLogy(0),
fLabels(0x0),
fLegend(0x0),
fConfidenceLevel(-1),
fFileOut(0x0),
fDivideOption(""),
fChi2_SignalsToAverage(0x0),
//fBest, // is an array...
fSelectedSig(-1),
fRequestedSignals(""),
fAllowedDiscrepancy(1.),
fFileType("pdf")
{
  /// Constructor for LmHandler, specifying projection bins and 1D plotting ranges
  LmHelper::Debug("LmHandler constructor", 5-debugHandler);

  LmHelper::SetEmptyBinnings(fMeeBinnings,  BinsPtee_forprojMee.size()-1);
  LmHelper::SetEmptyBinnings(fPteeBinnings, BinsMee_forprojPtee.size()-1);
  //Printf("fMeeBinnings.size()  = %i", (int)fMeeBinnings.size());
  //Printf("fPteeBinnings.size() = %i", (int)fPteeBinnings.size());
}


//_______________________________________________________________________________________________
LmHandler::~LmHandler()
{
  LmHelper::Debug("LmHandler destructor", 5-debugHandler);

  // free memory:
  if (fLmSigCombined)   delete fLmSigCombined;
  if (fLmSigAverage)    delete fLmSigAverage;
  //if (fLmCocktails.size()>0) fLmCocktails.clear(); // need to delete because a copy was made, but Cocktail has no destructor yet.
  if (fRelSystematics)  delete fRelSystematics;
  if (fLabels)          delete fLabels;
  if (fLegend)          delete fLegend;
  // fFileOut // don't delete.
  if (fChi2_SignalsToAverage) delete[] fChi2_SignalsToAverage;
  if (fOwner) {
    for (UInt_t i=0; i<fLmSig.size(); ++i) delete fLmSig.at(i);
    // maybe fLmSig.clear() would also work?
  }
}


//_______________________________________________________________________________________________
void LmHandler::SetType(Int_t type) {
  fType = type;
  switch (fType) {
    case kNoProcess:  fTypename="";         break;
    case kStd:        fTypename="Std";      break;
    case kCombine:    fTypename="Combine";  break;
    case kCompare:    fTypename="Compare";  break;
    case kAverage:    fTypename="Average";  break;
    case kWeightedAverage: fTypename="WeightedAverage"; break;
    case kSystematic_Average:
    case kSystematic_WeightedAverage:
    case kSystematic_BarlowSubset:
    case kSystematic_Jerome:
    case kSystematic: fTypename="Systematic"; break;
    case kCocktail:   fTypename="Cocktail"; break;
    case kCocktailOnly: fTypename="CocktailOnly"; break;
    case kSubtractCocktail: fTypename="CocktailSub"; break;
    case kExtSig1D:   fTypename="Ext1D";    break;
    case kExtSig2D:   fTypename="Ext2D";    break;
    case kSubtractCocktail2D: fTypename="CocktailSub2D"; break;
    default:          fTypename=Form("Type%i",type); break;
  }
  if (fName.size()==0) SetName(GetTypename());
}


//_______________________________________________________________________________________________
Int_t LmHandler::Process(Int_t type, Bool_t recursive)
{
  /// Entry point to perform any action on the attached LmSignal(s) and LmCocktail.
  /// Refer to the functions called within this main function for further details.
  /// - Main purpose is to produce 1D projections (Mee, Ptee spectra) to create figures. Projection ranges have to be
  /// given via SetBinsPtee_forprojMee() and SetBinsMee_forprojPtee(). Projections are stored inside attached objects.
  /// - Function can also combine, compare or average the attached signals.
  /// - Provides different methods to calculate systematic variations between the attached signals.
  /// (Only case this function is not mandatory [but OK to call]: for printing signals which have all been processed
  ///  by different handlers with identical projection ranges. In that case specify handler type in constructor.)
  ///
  /// NOTE: A handler may be processed with multiple types, e.g. to store combined and average signal at the same time.
  ///       But be aware that some functions incl. PrintCompare() are sensitive to the (current) type due to internal
  ///       use of GetReferenceSignal(). So in case of problems check for a meaningful handler type first.
  /// @param type Handler type from enum enType.
  /// @param recursive Set only if you know what happens, mostly for internal use.

  if (!recursive) SetType(type);
  LmHelper::Debug(Form("LmHandler Process(type=%i:%s, recursive=%i) [name='%s']", type, GetTypename(), recursive, GetName()), 5-debugHandler);
  if (GetNSignals()<1 && !(type==kCocktail||type==kCocktailOnly)) { LmHelper::Error("LmHandler::Process(): no signal available."); return 1; }

  switch (type) {
    case kStd: { // curly brackets needed when defining objects within switch and making recursive calls...
      if (!recursive) {
        fLmSigCombined = GetLmSignalI(0); // ok to do assignment instead of copy, because fLmSig[0] belongs to the class. but only for kStd!
      }
      fLmSigCombined->MakeSpectra1D(fBinsPtee_forprojMee, LmBaseSignal::kProjOnMee, fMeeBinnings);
      fLmSigCombined->MakeSpectra1D(fBinsMee_forprojPtee, LmBaseSignal::kProjOnPtee, fPteeBinnings);
      if (fDoConfidenceLevel) {
        LmHelper::Info(Form(" LmHandler(kStd): calculating confidence levels (CL=%f), may take a moment...", fConfidenceLevel));
        fLmSigCombined->CalcConfidenceLevel(fConfidenceLevel, LmBaseSignal::kProjOnMee);
        fLmSigCombined->CalcConfidenceLevel(fConfidenceLevel, LmBaseSignal::kProjOnPtee);
      }
      LmHelper::Debug("  ...LmHandler::Process(kStd): done.", 10-debugHandler);
      break;
    }

    case kCombine: {
      CombineSignals();
      Process(kStd, kTRUE);
      /// Recursive call of kCompare taken out to save some time. Call it in your main before kCombine if needed.
      /// However be aware that PrintCompare() is sensitive to the handler type due to use of GetReferenceSignal().
      //if (GetNSignals()>1) Process(kCompare, kTRUE); // for Rfactor comparison
      LmHelper::Debug("  ...LmHandler::Process(kCombine): done.", 10-debugHandler);
      break;
    }

    case kCompare: {
      for (Int_t i_sig = 0; i_sig < GetNSignals(); ++i_sig){
        GetLmSignalI(i_sig)->MakeSpectra1D(fBinsPtee_forprojMee, LmBaseSignal::kProjOnMee, fMeeBinnings);
        GetLmSignalI(i_sig)->MakeSpectra1D(fBinsMee_forprojPtee, LmBaseSignal::kProjOnPtee, fPteeBinnings);

        if (fDoConfidenceLevel && !recursive) // save time: not needed if called from combine handler.
        {
          LmHelper::Info(Form(" LmHandler(kCompare): calculating confidence levels (CL=%f), may take a moment...", fConfidenceLevel));
          GetLmSignalI(i_sig)->CalcConfidenceLevel(fConfidenceLevel, LmBaseSignal::kProjOnMee);
          GetLmSignalI(i_sig)->CalcConfidenceLevel(fConfidenceLevel, LmBaseSignal::kProjOnPtee);
        }
      }
      LmHelper::Debug("  ...LmHandler::Process(kCompare): done.", 10-debugHandler);
      break;
    }

    case kAverage: {
      AverageSignals(kFALSE);
      //Process(kStd, kTRUE); // not possible because 'fLmSigCombined' is processed there.
      fLmSigAverage->MakeSpectra1D(fBinsPtee_forprojMee, LmBaseSignal::kProjOnMee, fMeeBinnings);
      fLmSigAverage->MakeSpectra1D(fBinsMee_forprojPtee, LmBaseSignal::kProjOnPtee, fPteeBinnings);
      if (fCompareSignalsToAverage) CompareSignalsToAverage();
      LmHelper::Debug("  ...LmHandler::Process(kAverage): done.", 10-debugHandler);
      break;
    }

    case kWeightedAverage: {
      AverageSignals(kTRUE);
      //Process(kStd, kTRUE); // not possible because 'fLmSigCombined' is processed there.
      fLmSigAverage->MakeSpectra1D(fBinsPtee_forprojMee, LmBaseSignal::kProjOnMee, fMeeBinnings);
      fLmSigAverage->MakeSpectra1D(fBinsMee_forprojPtee, LmBaseSignal::kProjOnPtee, fPteeBinnings);
      if (fCompareSignalsToAverage) CompareSignalsToAverage();
      LmHelper::Debug("  ...LmHandler::Process(kWeightedAverage): done.", 10-debugHandler);
      break;
    }

    case kSystematic: {
      LmHelper::Error("LmHandler::Process(kSystematic): please pick a specific systematic type.");
      return -1;
    }

    case kSystematic_Average: {
      Process(kAverage, kTRUE);
      CalcSystematics();
      LmHelper::Debug("  ...LmHandler::Process(kSystematic): done.", 10-debugHandler);
      break;
    }

    case kSystematic_WeightedAverage: {
      Process(kWeightedAverage, kTRUE);
      CalcSystematics();
      LmHelper::Debug("  ...LmHandler::Process(kSystematic): done.", 10-debugHandler);
      break;
    }

    case kSystematic_BarlowSubset: {
      CalcSystematics();
      LmHelper::Debug("  ...LmHandler::Process(kSystematic): done.", 10-debugHandler);
      break;
    }

    case kSystematic_Jerome: {
      Process(kAverage, kTRUE);
      CalcSystematics();
      LmHelper::Debug("  ...LmHandler::Process(kSystematic): done.", 10-debugHandler);
      break;
    }

    case kCocktailOnly:
    case kCocktail: {
      if (fLmCocktails.size()==0) { LmHelper::Error("LmHandler::Process(kCocktail): no cocktail attached."); return -1; }
      for(UInt_t ic = 0; ic < fLmCocktails.size(); ++ic) {
        fLmCocktails.at(ic)->SetBinsPtee_forprojMee(fBinsPtee_forprojMee);
        fLmCocktails.at(ic)->SetBinsMee_forprojPtee(fBinsMee_forprojPtee);
        fLmCocktails.at(ic)->MakeSpectra1D(); // do projections according to attached binning (projection ranges).
        fCocktailProcessed=kTRUE;
      }
      break;
    }

    case kSubtractCocktail: {
      if (!fCocktailProcessed) Process(kCocktail, kTRUE);
      SubtractCocktailAllBins();
      for (Int_t i_sig = 0; i_sig < GetNSignals(); ++i_sig){
        if (fDoConfidenceLevel) {
          LmHelper::Info(Form(" LmHandler(kStd): calculating confidence levels (CL=%f), may take a moment...", fConfidenceLevel));
          GetLmSignalI(i_sig)->CalcConfidenceLevel(fConfidenceLevel, LmBaseSignal::kProjOnMee, kTRUE);
          GetLmSignalI(i_sig)->CalcConfidenceLevel(fConfidenceLevel, LmBaseSignal::kProjOnPtee, kTRUE);
        }
      }
      break;
    }

    case kSubtractCocktail2D: {
      SubtractCocktail2D();
      break;
    }

    case kExtSig1D: {

      break;
    }

    default:
      break;
  }
  if (recursive) return 0;
  // Put things below which shall be called only for non-recursive Process() calls, otherwise they are executed more than once!

  return 0;
}


//_______________________________________________________________________________________________
void LmHandler::AttachSignal(LmSignal &newsig, std::string newname)
{
  /// Attaches LmSignal to LmHandler. No copy is made.
  /// @param newsig  Signal which should be attached.
  /// @param newname Name which *this* handler uses as legend entry or file subdirectory for this signal (does not modify the attached LmSignal).

  LmHelper::Debug(" AttachSignal()", 5-debugHandler);
  fLmSig.push_back(&newsig);
  if (newname.compare("") == 0) {
    fLmSigNames.push_back(newsig.GetName());
  }
  else fLmSigNames.push_back(newname);
  return;
}

//_______________________________________________________________________________________________
void LmHandler::InitFromRootfile(TString filename)
{
  /// Set up LmHandler with LmSignals from 2D histograms from a rootfile that was previously written by
  /// LmHandler::Write2DHist(LmSignal::kMAXhist-1, kFALSE).
  /// Such rootfile contains a subfolder for each written signal.
  TDirectory* dir = 0x0;
  TFile* infile = LmHelper::SafelyOpenRootfile(filename.Data());
  for (Int_t i=0; i<infile->GetListOfKeys()->GetEntries(); ++i)
  {
    dir = infile->GetDirectory( infile->GetListOfKeys()->At(i)->GetName(), kTRUE );
    LmSignal* newSig = new LmSignal("", LmSignal::kExternal2D);
    newSig->InitFromRootfile(dir);
    AttachSignal(*newSig);
  }
  SetOwner(); // so that this handler can delete its own signals later...
  infile->Close();
  delete infile;
}

//_______________________________________________________________________________________________
void LmHandler::CombineSignals()
{
  /// Needed for LmHandler invoked with kCombine. This internal function adds all attached signals together into 'fLmSigCombined'.
  /// Projection and normalization of spectra happens after combining them, by calling fLmSigCombined->Process(kCombined).

  LmHelper::Debug(" CombineSignals()", 5-debugHandler);

  if (GetNSignals()<2) {
    LmHelper::Warning("LmHandler::CombineSignals(): combination of signals not needed. -> Resetting handler type to 'kStd'.");
    SetType(kStd);
    fLmSigCombined = GetLmSignalI(0); // ok to do assignment instead of copy, because fLmSig[0] belongs to the class. but only for kStd!
    return;
  }
  if (fLmSigCombined) delete fLmSigCombined;
  fLmSigCombined = new LmSignal(*fLmSig.at(0)); // copy constructor of LmSignal

  Double_t Nevents = GetLmSignalI(0)->GetNeventsPhysSel();
  for (int i=1; i<GetNSignals(); i++) {
    Nevents += GetLmSignalI(i)->GetNeventsPhysSel();
    // add the spectra:
    fLmSigCombined->GetUnlike2D()      ->Add( GetLmSignalI(i)->GetUnlike2D() );
    fLmSigCombined->GetBkg2D()         ->Add( GetLmSignalI(i)->GetBkg2D() );
    fLmSigCombined->GetUnlikeNoEffi2D()->Add( GetLmSignalI(i)->GetUnlikeNoEffi2D() );
    fLmSigCombined->GetBkgNoEffi2D()   ->Add( GetLmSignalI(i)->GetBkgNoEffi2D() );
    if (fLmSigCombined->GetSubtractionDone()) {
      fLmSigCombined->GetSubSig2D()      ->Add( GetLmSignalI(i)->GetSubSig2D() );
      fLmSigCombined->GetSigNoEffi2D()   ->Add( GetLmSignalI(i)->GetSigNoEffi2D() );
    }
  }
  if (fLmSigCombined->GetSubtractionDone()) {
    fLmSigCombined->SetDoSubtraction(kFALSE); // doesnt make sense to do it again and would crash without fUnlike.
  } else { // if subtraction wasnt done yet:
    fLmSigCombined->SetDoSubtraction(kTRUE);
  }
  fLmSigCombined->SetNeventsPhysSel(Nevents);
  fLmSigCombined->SetDoAcceCorr(fLmSig.at(0)->GetDoAcceCorr());
  //std::cout << "Acce copy: " << fLmSig.at(0)->GetManager()->GetAcce() << "  " << fLmSigCombined->ModifyManager() << std::endl;
  //fLmSigCombined->ModifyManager()->SetAcce(fLmSig.at(0)->GetManager()->GetAcce());
  //std::cout << "Acce copy done:" << fLmSigCombined->ModifyManager()->GetAcce() << std::endl;


  TObjArray* oaConfig = (fLmSig.at(0)->GetManager()->GetConfig()).Tokenize(":");
  if (oaConfig->GetEntriesFast()>=11) {
    fLmSigCombined->ModifyManager()->SetAccefileAndHists(const_cast<char*>(oaConfig->At(8)->GetName()), const_cast<char*>(oaConfig->At(9)->GetName()), const_cast<char*>(oaConfig->At(10)->GetName()));
  }



  fLmSigCombined->Process(LmSignal::kCombined);
  //fLmSigCombined->PrintSig("c2DSigComb.pdf");
}

//_______________________________________________________________________________________________
void LmHandler::AverageSignals(Bool_t weightAverage)
{
  /// Needed for LmHandler invoked with kAverage. This internal function adds all attached signals together into 'fLmSigAverage' and divides by No of signals.
  /// Average only calculated for SubSig!
  /// @TODO: should not copy anything blindly from fLmSig.at(0)!

  LmHelper::Debug(" AverageSignals()", 5-debugHandler);

  if (GetNSignals()<2) {
    LmHelper::Warning("LmHandler::AverageSignals(): only one signal, average trivial. -> Resetting handler type to 'kStd'.");
    SetType(kStd);
    fLmSigAverage = GetLmSignalI(0); // ok to do assignment instead of copy, because fLmSig[0] belongs to the class. but only for kStd!
    return;
  }
  if (fLmSigAverage) delete fLmSigAverage;
  fLmSigAverage = new LmSignal(*fLmSig.at(0)); // copy constructor of LmSignal
  fLmSigAverage->GetSig2D()->Reset();
  /// @TODO: why not use TH1::Add()?
  Double_t Nevents(0.);
  for (int i=0; i<GetNSignals(); i++) Nevents += GetLmSignalI(i)->GetNeventsPhysSel();
  Nevents = Nevents/GetNSignals();

  Double_t bc(0.),be(0.),weight(0.),sumWeight(0.);
  for(Int_t ix = 0; ix <= fLmSigAverage->GetSig2D()->GetNbinsX()+1; ++ix){
    for(Int_t iy = 0; iy <= fLmSigAverage->GetSig2D()->GetNbinsY()+1; ++iy){
      bc = 0.; be = 0.; weight = 1.; sumWeight = 0.;
      for (int i=0; i<GetNSignals(); i++) {
        /// @TODO: skipping oversubtracted signals will cause a bias towards higher average content!
        /// but removing this check messes up the weighted average...
        if(weightAverage && TMath::Abs(GetLmSignalI(i)->GetSig2D()->GetBinError(ix,iy)) > LmHelper::kSmallDelta)
          weight = 1./TMath::Power((GetLmSignalI(i)->GetSig2D()->GetBinError(ix,iy))/GetLmSignalI(i)->GetNeventsPhysSel(),2);
        else
          weight = 1.;
        bc += weight * (GetLmSignalI(i)->GetSig2D()->GetBinContent(ix,iy))/GetLmSignalI(i)->GetNeventsPhysSel();
        be += weight * (GetLmSignalI(i)->GetSig2D()->GetBinError(ix,iy))  /GetLmSignalI(i)->GetNeventsPhysSel();
        sumWeight += weight;
      }
      if(sumWeight > LmHelper::kSmallDelta){
        bc = bc / sumWeight * Nevents;
        be = be / sumWeight * Nevents;
      }
      fLmSigAverage->GetSig2D()->SetBinContent(ix,iy,bc);
      fLmSigAverage->GetSig2D()->SetBinError(ix,iy,be);
    }
  }
  fLmSigAverage->SetNeventsPhysSel(Nevents);
  if(weightAverage) fLmSigAverage->Process(LmSignal::kWeightedAverage); // doesnt do anything except setting name and type.
  else fLmSigAverage->Process(LmSignal::kAverage);
}


//_______________________________________________________________________________________________
void LmHandler::CalcSystematics()
{

  LmHelper::Debug(" CalcSystematics()", 5-debugHandler);
  std::cout << fType << std::endl;

  if (fRelSystematics) delete fRelSystematics;
  fRelSystematics = new TH2D( *(fLmSig.at(0)->GetSig2D()) );
  fRelSystematics->Reset();
  fRelSystematics->SetName("RelativeSystematics");

  Double_t Nevents(0.);
  for (int i=0; i<GetNSignals(); i++) Nevents += GetLmSignalI(i)->GetNeventsPhysSel();
  Nevents = Nevents/GetNSignals();

  Double_t bc_ref(0.),be_ref(0.),bc_i(0.),be_i(0.);
  Double_t rms(0.),RelErr(0.);

  switch (fType) {

      /// Calculate systematic deviation as RMS of deviations to average signal.
    case kSystematic_Average:
      LmHelper::Debug(" CalcSystematics(Average)", 5-debugHandler);
    case kSystematic_WeightedAverage:
    {
      LmHelper::Debug(" CalcSystematics(WeightedAverage)", 5-debugHandler);
      for(Int_t ix = 1; ix <= fRelSystematics->GetNbinsX()+1; ++ix){
        for(Int_t iy = 1; iy <= fRelSystematics->GetNbinsY()+1; ++iy){
          bc_ref = fLmSigAverage->GetSig2D()->GetBinContent(ix,iy);
          rms = 0.;
          for (int i=0; i<GetNSignals(); i++) {

            bc_i = (GetLmSignalI(i)->GetSig2D()->GetBinContent(ix,iy))/GetLmSignalI(i)->GetNeventsPhysSel() * Nevents;
            rms += TMath::Power(bc_i - bc_ref,2);
            //std::cout << "--> Signal: " << i << "  bc: " << bc_i << "  rms: " << rms << std::endl;
          }
          rms = TMath::Sqrt(rms / GetNSignals());
          if(bc_ref > 0.) RelErr = rms/bc_ref;
          else            RelErr = 0.; // @TODO: this could cause an inconsisteny. Use coarse binning and check that it does not occur.
          std::cout << "mee: " << fRelSystematics->GetXaxis()->GetBinCenter(ix) << "   ptee: " << fRelSystematics->GetYaxis()->GetBinCenter(iy) << "   relError: " << RelErr << std::endl;
          fRelSystematics->SetBinContent(ix,iy,RelErr);
        } // bin y
      } // bin x
      break;
    }
    case kSystematic_Jerome:
    {
      LmHelper::Debug(" CalcSystematics(Box)", 5-debugHandler);
      Double_t min=0, max =0;
      for(Int_t ix = 0; ix <= fRelSystematics->GetNbinsX()+1; ++ix){
        for(Int_t iy = 0; iy <= fRelSystematics->GetNbinsY()+1; ++iy){
          bc_ref = fLmSigAverage->GetSig2D()->GetBinContent(ix,iy);
          min = bc_ref; max = bc_ref;
          for (int i=0; i<GetNSignals(); i++) {
            bc_i = (GetLmSignalI(i)->GetSig2D()->GetBinContent(ix,iy));
            if(bc_i<min) min = bc_i;
            if(bc_i>max) max = bc_i;
          }
          if(bc_ref == 0)         RelErr = 0.;
          else if (min<=max) RelErr = ((max-min)/sqrt(12))/bc_ref;
          else               RelErr = 0.; // @TODO: this could cause an inconsisteny. Use coarse binning and check that it does not occur.
          std::cout << "mee: " << ix << "   ptee: " << iy << "  min: " << min << "   max: " << max << "relError: " << RelErr << std::endl;
          fRelSystematics->SetBinContent(ix,iy,RelErr);
        }
      }
      break;
    }

      /// Calculate systematic deviation based on Barlows criterion.
      /// It cannot be strictly applied to subtracted yields, since a subset is not well-defined (lower efficiency may have higher sub. yield).
      /// We try it anyhow with the subset assumption. Check method & comments in code...
    case kSystematic_BarlowSubset:
    {
      if (!(fSelectedSig>-1)) {
        LmHelper::Error("LmHandler::CalcSystematics(): no reference signal selected. Call SetSelectedSignal() before.");
        return;
      }
      Double_t delta(0.),sigma_delta(0.),n_sigma(0.);
      Int_t n_significant_diff(0);
      for(Int_t ix = 0; ix <= fRelSystematics->GetNbinsX()+1; ++ix){
        for(Int_t iy = 0; iy <= fRelSystematics->GetNbinsY()+1; ++iy){
          bc_ref = GetLmSignalI(fSelectedSig)->GetSig2D()->GetBinContent(ix,iy);
          be_ref = GetLmSignalI(fSelectedSig)->GetSig2D()->GetBinError(ix,iy);

          /// According to Barlow, if dataset_i is a subset of dataset_ref, then the difference 'delta' between the
          /// measurements ( delta = bc_ref - bc_i ) has the error sigma_delta^2 = sigma_i^2 - sigma_ref^2.

          sigma_delta = 0.; n_sigma = 0.; rms = 0.; n_significant_diff = 0;
          for (int i=0; i<GetNSignals(); i++) {
            bc_i = GetLmSignalI(i)->GetSig2D()->GetBinContent(ix,iy);
            be_i = GetLmSignalI(i)->GetSig2D()->GetBinError(ix,iy);
            delta = bc_ref - bc_i;
            if (delta == 0) continue;

            sigma_delta = TMath::Sqrt(TMath::Abs(be_i*be_i - be_ref*be_ref)); // ideally, abs() would not be needed, but to make sure...
            if (sigma_delta>0) n_sigma = delta / sigma_delta;

            //printf(" comp sig %d to %d : bin(%d,%d): delta = %8.1f , sigma_delta = %8.1f, n_sigma = %8.3f \n",i,fSelectedSig,ix,iy,delta,sigma_delta,n_sigma);

            /// Now we have to decide how to treat emerging discrepancies, since there is no fixed recipe for it.
            if (n_sigma > fAllowedDiscrepancy) {
              n_significant_diff++;
              rms += delta*delta;
            }
          }
          //cout<<" fType="<<fType<<" fAllowedDiscrepancy="<<fAllowedDiscrepancy<<" n_significant_diff = "<<n_significant_diff<<endl;
          //rms = rms / GetNSignals();
          //if (n_significant_diff>0) rms = rms / n_significant_diff;
          rms = TMath::Sqrt(rms);
          if(bc_ref > 0.) RelErr = rms/bc_ref;
          else            RelErr = 0.;
          fRelSystematics->SetBinContent(ix,iy,RelErr);
        } // bin y
      } // bin x
      break;
    }

  } // switch

  //PhiV: 5% (maybe too high?)
  //V0AND trigger efficiency: 1%
  //R-factor: 2% (change to 1%?)
  //ITS shared cluster: 6%
  //ITS first: 4%
  //ITS-TPC matching: 5.5% (not applied yet) done
  //fast-cent: 5% (not applied yet) done
  //for(Int_t ix = 0; ix <= fRelSystematics->GetNbinsX()+1; ++ix){
  //  for(Int_t iy = 0; iy <= fRelSystematics->GetNbinsY()+1; ++iy){
  //    if(ix <=1)
  //      fRelSystematics->SetBinContent(ix,iy,sqrt(fRelSystematics->GetBinContent(ix,iy)*fRelSystematics->GetBinContent(ix,iy) + 0.05*0.05 + 0.055*0.055 + 0.04*0.04 + 0.06*0.06 + 0.05*0.05 + 0.02*0.02 + 0.01*0.01));
  //    else
  //      fRelSystematics->SetBinContent(ix,iy,sqrt(fRelSystematics->GetBinContent(ix,iy)*fRelSystematics->GetBinContent(ix,iy) + 0.05*0.05 + 0.055*0.055 + 0.04*0.04 + 0.06*0.06 + 0.02*0.02 + 0.01*0.01));
  //  } // bin y
  //} // bin x

}


//_______________________________________________________________________________________________
void LmHandler::CompareSignalsToAverage()
{
  /// Find the three signals which are closest to the average. The 2D signals are compared.
  /// Decision is based on a Chi2 test between signals. It could mainly depend on first bins (highest stat, low err).
  /// The Kolmogorov-Smirnov test gives probabilities of zero, but the "Maximum Kolmogorov distance" gives at least
  /// similar signal choices as the Chi2 test.
  /// Warning: Chi2/ndf < 1 does not necessarily mean a better correspondence of histograms in the sense we want it.
  /// Please check test macro SharedFiles/patrick/Chi2test.cxx.

  // reserve memory (free old memory if needed):
  if (fChi2_SignalsToAverage) delete[] fChi2_SignalsToAverage;
  fChi2_SignalsToAverage = new Double_t[GetNSignals()];

  Int_t imin=0, isec=0, ithird=0;
  for (int i=0; i<GetNSignals(); i++) {
    Double_t chi2ndf = GetLmSignalI(i)->GetSig2D()->Chi2Test(fLmSigAverage->GetSig2D(), "NORM UU CHI2/NDF");
//    Double_t pvalue  = GetLmSignalI(i)->GetSig2D()->Chi2Test(fLmSigAverage->GetSig2D(), "NORM UU");
//    Double_t pKolmo  = GetLmSignalI(i)->GetSig2D()->KolmogorovTest(fLmSigAverage->GetSig2D(), "N");
//    Double_t kolmoDist = GetLmSignalI(i)->GetSig2D()->KolmogorovTest(fLmSigAverage->GetSig2D(), "M");
//    Printf(" cut %02d:   chi2ndf = %5.3f   pvalue = %7.5f   pKolmo = %5.3f   kolmoDist = %7.5f", i+1, chi2ndf, pvalue, pKolmo, kolmoDist);
    fChi2_SignalsToAverage[i] = chi2ndf;

    // store smallest deviations from average:
    // (maybe replace with clever sorting algorithm...)
    if      (fChi2_SignalsToAverage[i] < fChi2_SignalsToAverage[imin]  ) { ithird = isec; isec = imin; imin = i; }
    else if (fChi2_SignalsToAverage[i] < fChi2_SignalsToAverage[isec]  ) { ithird = isec; isec = i; }
    else if (fChi2_SignalsToAverage[i] < fChi2_SignalsToAverage[ithird]) { ithird = i; }
    else if (isec  ==imin) { isec = i;} // treat special case when the first signal is already the best one.
    else if (ithird==imin || ithird==isec) { ithird = i; } // treat special case when the first two signals are already the best ones.
    //cout << " best 3: " << fChi2_SignalsToAverage[imin] << " < " << fChi2_SignalsToAverage[isec] << " < " << fChi2_SignalsToAverage[ithird] << endl;
  }
  fBest[0]=imin;
  fBest[1]=isec;
  fBest[2]=ithird;
}


//_______________________________________________________________________________________________
void LmHandler::PrintCorrelation(unsigned int histBitX, unsigned int histBitY, unsigned int bin_number, Bool_t projOnMee, const Char_t* filename, Bool_t printLegend, Bool_t separatePlots, TCanvas* can)
{
  /// Draw a 2D bin-by-bin correlation plot between two given histBits for all attached LmSignals.
  /// A coarse binning should be provided to the managers of these signals.
  /// For a correct legend, one has to call PrintCompareSig_Mee/Ptee before, because the histogram style is taken from LmSignal::kSubSig.
  /// @param bin_number Projection bin to correlate.
  /// @param projOnMee Correlate x- or y-projections (set via LmBaseSignal::kProjOnMee or kProjOnPtee).
  /// @param separatePlots Print each correlated bin into a new canvas or all in one, connected with lines (will become busy).
  /// @param can To specify lin/log scales and x-/y-axis ranges, one can give a canvas with drawn histogram (called "haxis") to this function.
  /// @param can Otherwise log-log is assumed and ranges are computed by the internal function ComputeOptimumPlotRangeY().

  int printdebug=0;
  LmHelper::Debug(Form("LmHandler::PrintCorrelation()"), 5-printdebug);
  TString sfilename(filename); // because "const Char_t* filename" somehow gets modified by operations related to LmHistogram... (in case with cocktail)

  if ((Int_t)bin_number > GetReferenceSignal()->GetMaxBinProj(projOnMee)) {
    LmHelper::Error(Form("LmHandler::PrintCorrelation(): projection bin number (%i) out of range (on axis '%i'). [%i=X-axis(Mee),%i=Y-axis(Ptee)]", bin_number, projOnMee, LmBaseSignal::kProjOnMee, LmBaseSignal::kProjOnPtee));
    return;
  }

  std::vector<TH1D*> vProjX = CollectProjections(histBitX, bin_number, projOnMee);
  std::vector<TH1D*> vProjY = CollectProjections(histBitY, bin_number, projOnMee);

  // create canvas and axis histogram if needed
  TH2D* haxis=0x0;
  Bool_t ownCan=kFALSE;
  if (!can) {
    ownCan=kTRUE;
    can = new TCanvas("cCorrel", "cCorrel");
    can->SetLogx();
    can->SetLogy();
    Double_t origYMin=fPlotYMin; // make sure we don't mess up the users individual settings
    Double_t origYMax=fPlotYMax;
    // compute optimum ranges for x and y.
    ComputeOptimumPlotRangeY(histBitX, bin_number, projOnMee);
    Double_t xMin = fPlotXMin;
    Double_t xMax = fPlotXMax;
    ComputeOptimumPlotRangeY(histBitY, bin_number, projOnMee);
    Double_t yMin = fPlotYMin;
    Double_t yMax = fPlotYMax;
    LmHelper::Debug(Form("  using computed ranges: X = %.2e - %.2e,   Y = %.2e - %.2e", xMin, xMax, yMin, yMax), 12-printdebug);
    fPlotYMin=origYMin; // reset global variables to the users individual settings
    fPlotYMax=origYMax;
    haxis = new TH2D("haxis","haxis", 1000,xMin,xMax, 1000,yMin,yMax);
    haxis->SetTitle( Form(";%s;%s",vProjX.at(0)->GetYaxis()->GetTitle(),vProjY.at(0)->GetYaxis()->GetTitle()) );
    haxis->DrawCopy();
  }
  else { // get axis histogram from canvas and set the titles.
    haxis = (TH2D*) can->GetListOfPrimitives()->FindObject("haxis");
    if (!haxis) LmHelper::Error(Form("LmHandler::PrintCorrelation(): histogram not found in provided canvas. Name it \"haxis\" and use Draw()."));
    haxis->SetTitle( Form(";%s;%s",vProjX.at(0)->GetYaxis()->GetTitle(),vProjY.at(0)->GetYaxis()->GetTitle()) );
  }

  haxis->GetXaxis()->SetLabelSize(haxis->GetXaxis()->GetLabelSize());
  // haxis->GetXaxis()->SetLabelSize(haxis->GetXaxis()->GetLabelSize()-4);
  haxis->GetXaxis()->SetTitleOffset(1.0);

  // construct filename of plot
  if (sfilename.IsNull()||sfilename.BeginsWith('+')) {
    TString ssuffix = "";
    if (sfilename.BeginsWith('+')) {
      sfilename.Remove(0,1);
      ssuffix.Append(sfilename);
    }
    sfilename = "/cCorrel";
    sfilename.Prepend(gEnv->GetValue("Canvas.PrintDirectory",".")); // not the best way maybe...
    sfilename.Append(GetReferenceSignal()->GetCharHistBit(histBitX,kTRUE));
    sfilename.Append(GetReferenceSignal()->GetCharHistBit(histBitY,kTRUE));
    LmBaseSignal::inputAxis inputAx = LmBaseSignal::CheckWhichInputAxis( (TH1*) GetReferenceSignal()->GetLmHist(histBitX,bin_number,projOnMee)->GetDatahist() );
    sfilename.Append("_"+LmBaseSignal::GetInputAxisCode(inputAx)); // replaces hardcoded Append("_Mee") or Append("_Ptee").
    sfilename.Append(Form("%s_bin%d.%s",ssuffix.Data(),bin_number,fFileType.Data()));
  }

  // create empty labels array.
  TObjArray* oaLabels = GenerateLabels(kTRUE);

  // print either one or multiple plots
  can->cd();
  if (!separatePlots) {
    TObjArray* oaCorrelGr = LmHelper::MakeCorrelationGraphs(vProjX, vProjY);
    oaCorrelGr->Draw("pl");
    TLegend* leg = GenerateLegend(bin_number, projOnMee, LmSignal::kSubSig/*histBitX*/);
    if (printLegend) leg->DrawClone("same");

    // fill the labels array.
    unsigned int bin_number_2 = GetMaxBinProj(!projOnMee); // here it is ok to use GetMaxBinProj() internally.
    FillLabels(oaLabels, bin_number, projOnMee, bin_number_2);
    // optionally change title of 'latCuts1Dim'.
    TString meerange(""); // do not care about acceptance hole stuff here... (see GenerateLabels())
    if (vProjX.at(0)->GetNbinsX()>1) { // when drawing multiple x-axis bins into one plot, just write an info(rmal) label.
      if (projOnMee==LmBaseSignal::kProjOnPtee) meerange = Form("%d bins in %s",vProjX.at(0)->GetNbinsX(),LmBaseSignal::GetProjLabelYvar().Data());
      else                                      meerange = Form("%d bins in %s",vProjX.at(0)->GetNbinsX(),LmBaseSignal::GetProjLabelXvar().Data());
    }
    TLatex* latCuts1Dim = (TLatex*) oaLabels->FindObject("latCuts1Dim");
    if (latCuts1Dim) latCuts1Dim->SetTitle(meerange.Data());
    oaLabels->DrawClone("same");
    can->Print(sfilename.Data());
    haxis->Draw();
    if (leg) delete leg;
  }
  else {
    for (Int_t bini=1; bini<=vProjX.at(0)->GetNbinsX(); bini++) {

	    std::cout << "Check 1: " << vProjX.at(0)->GetNbinsX() << std::endl;
            std::cout << "Check 2: " << vProjY.at(0)->GetNbinsX() << std::endl;
            std::cout << "Check 3: " << vProjX.size() << std::endl;
            std::cout << "Check 4: " << vProjY.size() << std::endl;
      can->Update(); // reuse the same canvas for each plot.
      TObjArray* oaCorrelGr = LmHelper::MakeCorrelationGraphs(vProjX, vProjY, bini, bini);
      oaCorrelGr->Draw("pl same");
      TLegend* leg = GenerateLegend(bin_number, projOnMee, LmSignal::kSubSig/*histBitX*/);
      if (printLegend) leg->Draw("same");
      // fill the labels array. option kTRUE to update 'latCuts1Dim' for new bin.
      FillLabels(oaLabels, bin_number, projOnMee, bini, kTRUE); // kTRUE is default anyhow.
      if (bini==1) oaLabels->Draw("same"); // needs to be drawn only once, the TLatex will be updated automatically.
      // print canvas
      TString sfilenamei = sfilename;
      sfilenamei.ReplaceAll(Form(".%s", fFileType.Data()),Form("_%d.%s",bini,fFileType.Data()));
      can->Print(sfilenamei.Data());
      oaCorrelGr->Delete(); //Remove all objects from the array AND delete all heap based objects.
      delete oaCorrelGr;
      if (leg) delete leg;
    }
  }

  delete oaLabels;
  if (ownCan) delete haxis;
  if (ownCan) delete can;
  return;
}


//_______________________________________________________________________________________________
void LmHandler::SubtractCocktailAllBins()
{
  /// Subtract the last attached cocktail from all attached signals.
  /// This cocktail is removed afterwards, because it doesnt make sense to plot it anymore.
  /// ('last' is used for easy removal and because ratios are always done to the first cocktail.)
  /// Subtraction is performed on the projections, i.e. LmHistograms, so everything has to be processed before.
  /// Check LmHistogram::Add() for implementation and possible missing peaces like systematics propagation...
  /// That cocktail shall not be printed anymore, so it is deleted from the handler in the end.

  LmHelper::Debug(" SubtractCocktailAllBins()", 5-debugHandler);

  if (GetReferenceSignal()->GetMaxBinProj(LmBaseSignal::kProjOnMee) == 0) {
    LmHelper::Error(Form("LmHandler::SubtractCocktail(): create signal projections first, e.g. via handler->Process(LmHandler::kCompare).")); return;
  }
  if (GetLastCocktail()->GetLmCocktailPart(LmCocktailPart::kSum)->GetMaxBinProj(LmBaseSignal::kProjOnMee) == -1) { // this error should never be reached.
    LmHelper::Error(Form("LmHandler::SubtractCocktail(): create cocktail projections first, e.g. via handler->Process(LmHandler::kCocktail).")); return;
  }

  UInt_t iBit      = LmSignal::kSubSig;
  std::vector<Double_t> biningX = GetLmSignalI(0)->GetManager()->GetBinningX();
  std::vector<Double_t> biningY = GetLmSignalI(0)->GetManager()->GetBinningY();

  Bool_t projOnMee = LmBaseSignal::kProjOnMee;
  for (int bin_number=0; bin_number<=GetReferenceSignal()->GetMaxBinProj(projOnMee); bin_number++) {
    SubtractCocktail(iBit,bin_number,projOnMee,biningX);
  }
  projOnMee = LmBaseSignal::kProjOnPtee;
  for (int bin_number=0; bin_number<=GetReferenceSignal()->GetMaxBinProj(projOnMee); bin_number++) {
    SubtractCocktail(iBit,bin_number,projOnMee,biningY);
  }

  // remove the subtracted cocktail so it isnt printed and/or used for legend.
  fLmCocktails.pop_back();
  if (fLmCocktails.size()==0){
    std::cout << "no Cocktails remaining after subtraction" << std::endl;
    fCocktailProcessed=kFALSE; // to avoid problems if no cocktail remains...
  }
  else std::cout << fLmCocktails.size() << " Cocktails remaining after subtraction" << std::endl;
}

//_______________________________________________________________________________________________
void LmHandler::SubtractCocktail(unsigned int iBit, unsigned int bin_number, Bool_t projOnMee, std::vector<Double_t> binning)
{
  LmHelper::Debug(Form(" SubtractCocktail() %i", bin_number), 5-debugHandler);

  LmHistogram*        lmHistData    = 0x0;
  TH1D*               hCocktailSum  = 0x0;
  TGraphAsymmErrors*  grCocktailErr = 0x0;
  TH2D*               hAcce         = 0x0;
  LmHistogram*        lmAcce        = 0x0;

    // dont change into subtracting any other cocktail, it will mess up.
  hCocktailSum  = GetLastCocktail()->GetLmCocktailPart(LmCocktailPart::kSum)->GetSpectrum(bin_number,projOnMee);
  grCocktailErr = GetLastCocktail()->GetLmCocktailPart(LmCocktailPart::kSum)->GetSpectrumErr(bin_number,projOnMee);
  for (Int_t i_sig = 0; i_sig < GetNSignals(); ++i_sig) {
    lmHistData = GetLmSignalI(i_sig)->GetLmHist(iBit,bin_number,projOnMee);
    /// @TODO: attach grCocktailErr as fExternalSystematicObj or new obj to lmHistData and change its points to the
    /// ones of fSystErr, while keeping its errors. Use grey marker style and maybe marker/drawing type 'E[]',
    /// because it will be drawn on top of remaining cocktail contributions, so it should not have filled boxes.
    lmHistData->Subtract(hCocktailSum, grCocktailErr);
    std::cout << "  LmSignalHist" << std::endl;
    for(int t = 0; t < lmHistData->GetDatahist()->GetNbinsX(); t++)
      std::cout << lmHistData->GetXaxis()->GetXbins()->At(t) << " ";
    std::cout << std::endl;
    if(GetLmSignalI(i_sig)->GetDoAcceCorr()){

      if(projOnMee) GetLmSignalI(i_sig)->GetManager()->SetRebinning2D(binning.size()-1, binning.data(), (GetBinsY_forprojOnX()).size()-1, (GetBinsY_forprojOnX()).data());
      else GetLmSignalI(i_sig)->GetManager()->SetRebinning2D((GetBinsX_forprojOnY()).size()-1, (GetBinsX_forprojOnY()).data(), binning.size()-1, binning.data());
      GetLmSignalI(i_sig)->GetManager()->Process(LmManager::kRebinAcce);
      hAcce = GetLmSignalI(i_sig)->GetManager()->GetAcce();
      if(projOnMee) lmAcce = new LmHistogram(hAcce->ProjectionX(Form("proj_%i",bin_number),bin_number+1, bin_number+1));
      else lmAcce = new LmHistogram(hAcce->ProjectionY(Form("proj_%i",bin_number),bin_number+1, bin_number+1));
      std::cout << bin_number << std::endl;
      for(Int_t bin = 1; bin < lmAcce->GetDatahist()->GetNbinsX(); bin++)
	std::cout << "bin: " << lmAcce->GetDatahist()->GetBinCenter(bin) << "  acce correction: " << lmAcce->GetDatahist()->GetBinContent(bin) << std::endl;
      lmHistData->Divide(lmAcce);
    }
  }
}


//_______________________________________________________________________________________________
void LmHandler::SubtractCocktail2D()
{

  LmHelper::Debug(" SubtractCocktail2D()", 5-debugHandler);

  TH2D*  hData    = 0x0;
  TH2D*  hDataSysHigh = 0x0;
  TH2D*  hDataSysLow  = 0x0;
  TH2D*  hCockSum  = 0x0;
  TH2D*  hCockSysHigh = 0x0;
  TH2D*  hCockSysLow = 0x0;

  // dont change into subtracting any other cocktail, it will mess up.
  hCockSum  = GetLastCocktail()->GetLmCocktailPart(LmCocktailPart::kSum)->GetSpectrum2D();
  hCockSysHigh  = GetLastCocktail()->GetLmCocktailPart(LmCocktailPart::kSum)->GetSpectrum2DHigh();
  hCockSysLow   = GetLastCocktail()->GetLmCocktailPart(LmCocktailPart::kSum)->GetSpectrum2DLow();
  for (Int_t i_sig = 0; i_sig < GetNSignals(); ++i_sig) {
    hData = GetLmSignalI(i_sig)->GetSubSig2D();
    hDataSysHigh = GetLmSignalI(i_sig)->GetSystematicHigh();
    hDataSysLow  = GetLmSignalI(i_sig)->GetSystematicLow();
    /// @TODO: attach grCocktailErr as fExternalSystematicObj or new obj to lmHistData and change its points to the
    /// ones of fSystErr, while keeping its errors. Use grey marker style and maybe marker/drawing type 'E[]',
    /// because it will be drawn on top of remaining cocktail contributions, so it should not have filled boxes.
    LmHelper::Debug(" SubtractCocktail2D()", 5-debugHandler);
    hData->Add(hCockSum, -1.);
    hDataSysHigh->Add(hCockSysHigh,-1.);
    hDataSysLow->Add(hCockSysLow,-1.);

    if(GetLmSignalI(i_sig)->GetDoAcceCorr()){
      GetLmSignalI(i_sig)->Process(LmSignal::kAcceCorrection2D);
    }
  }
  // remove the subtracted cocktail so it isnt printed and/or used for legend.
  fLmCocktails.pop_back();
  if (fLmCocktails.size()==0) fCocktailProcessed=kFALSE; // to avoid problems if no cocktail remains...

}


//_______________________________________________________________________________________________
void LmHandler::PrintAverage(unsigned int histBits, unsigned int bin_number, Bool_t projOnMee, const Char_t* filename, Bool_t printLegend, Bool_t setLogy, TCanvas* can)
{
  PrintCompare(histBits, bin_number, projOnMee, filename, printLegend, setLogy, kFALSE, can, kTRUE);
}


//_______________________________________________________________________________________________
void LmHandler::PrintCompare(unsigned int histBits, unsigned int bin_number, Bool_t projOnMee, const Char_t* filename, Bool_t printLegend, Bool_t setLogy, Bool_t setLogx, TCanvas* can, Bool_t printOnlyAverage)
{
  /// Generic plotting function.
  /// Plots requested histograms into canvas and prints canvas to file. Also plots legend + labels + ratio ... if requested.
  /// Modify the plotting ranges via SetPlotRangeMee()/Ptee(), SetPlotRangeY(), SetPlotRangeYMargins().
  /// If no y-range is given, it finds the optimum plotting range by internally calling ComputeOptimumPlotRangeY().
  ///
  /// NOTE: PrintCompare() works for all handler types and is sensitive to them. In case of a crash, check that
  ///       function GetReferenceSignal() returns the signal that you intend and change handler type if needed.
  ///
  /// In case of multiple cocktails, only for the last cocktail all contributions are drawn and added to the legend.
  /// For the other cocktails only their individual sum is drawn.
  /// The ratio is done w.r.t. the first cocktail's sum, and the sums of the other cocktails are compared to it.
  ///
  /// @param hitBits Bits of histogram types that shall be plotted into the same canvas (e.g. LmSignal::kUnlike+LmSignal::kBkg). the order has no effect.
  /// @param bin_number Projection bin to plot.
  /// @param projOnMee Plot x- or y-projections (set via LmBaseSignal::kProjOnMee or kProjOnPtee).
  /// @param filename If starting with '+', the filename is generated automatically, but the string after '+' is appended.
  /// @param can Option to provide canvas. The (generated) filename is set as the canvas title for external printing.

  Double_t sizefac=0.7;
  int printdebug=0;
  LmHelper::Debug(Form("LmHandler::PrintCompare()"), 5-printdebug);
  TString sfilename(filename); // because "const Char_t* filename" somehow gets modified by operations related to LmHistogram... (in case with cocktail)

  if (fType==kNoProcess) {
    LmHelper::Warning(Form("LmHandler::PrintCompare(): this LmHandler (fType=%i) is not ready for printing. Call Process(..) or specify type in constructor.", fType));
    return;
  }

  std::cout << bin_number << "   " << GetReferenceSignal() << "   "  << GetReferenceSignal()->GetMaxBinProj(projOnMee) << std::endl;
  if ((Int_t)bin_number > GetReferenceSignal()->GetMaxBinProj(projOnMee)) {
    LmHelper::Error(Form("LmHandler::PrintCompare(): projection bin number (%i) out of range (on axis '%i'). [%i=X-axis(Mee),%i=Y-axis(Ptee)]", bin_number, projOnMee, LmBaseSignal::kProjOnMee, LmBaseSignal::kProjOnPtee));
    return;
  }

  if ( (histBits & LmSignal::kRfactor) && GetLmSignalI(0)->GetLmBackground()->GetUseRfactorUnity() ) {
    LmHelper::Warning(Form("LmHandler::PrintCompare(): the 1D Rfactors are not created from the 2D Rfactor which uses a unity range! (never project ratios!)"));
  }

  Bool_t ownCan=kFALSE;
  if (!can) {
    ownCan=kTRUE;
    can = new TCanvas("cCompare", "cCompare");
    can->Clear();
  }
  //can->SetFillStyle(0);
  //can->SetFrameFillStyle(0);
  can->cd()->SetLogy(setLogy);
  can->cd()->SetLogx(setLogx);

  if (fDoRatio) {
    LmHelper::Debug(Form("  create ratio pad"), 10-printdebug);
    Double_t bottommargin = 0.09/fRatioPadSize;
    can->Divide(1,2);
    can->cd(1)->SetPad(0., fRatioPadSize, 1., 1.);  // top pad
    can->cd(1)->SetBottomMargin(0.001);
    //can->cd(1)->SetFillStyle(0);
    //can->cd(1)->SetFrameFillStyle(0);
    can->cd(2)->SetPad(0., 0., 1., fRatioPadSize);  // bottom pad
    can->cd(2)->SetTopMargin(0);
    can->cd(2)->SetBottomMargin(bottommargin); // for x-axis label
//    can->cd(2)->SetBottomMargin(gStyle->GetPadBottomMargin()); // for x-axis label
    can->cd(2)->SetLogx(setLogx);
    //can->cd(2)->SetFillStyle(0);
    //can->cd(2)->SetFrameFillStyle(0);
    // move to upper pad and set log if requested.
    can->cd(1)->SetLogy(setLogy);
    can->cd(1)->SetLogx(setLogx);

  }

  // don't use floats (LmHelper::kSmallDelta will not work)
  Double_t commonXmin=0., commonXmax=0.;
  Double_t commonYmin=0., commonYmax=0.;

  // store the common x-range
  if (projOnMee==LmBaseSignal::kProjOnMee) {
    if (fPlotXMeeMin>-1  && fPlotXMeeMax>0)  { commonXmin=fPlotXMeeMin;  commonXmax=fPlotXMeeMax;  }
  } else { // Ptee
    if (fPlotXPteeMin>-1 && fPlotXPteeMax>0) { commonXmin=fPlotXPteeMin; commonXmax=fPlotXPteeMax; }
  }

  // store the common y-range
  // determine the common y-axis range for all histograms, if it was not manually set to valid values.
  // in that case also apply the margins.
  Bool_t rangeComputed=kFALSE;
  if (fPlotYMin >= fPlotYMax) {
    ComputeOptimumPlotRangeY(histBits, bin_number, projOnMee, printOnlyAverage); // maybe one could just not call this function in case of printOnlyAverage=kTRUE...
    LmHelper::Debug(Form("  using computed range and margins: ymin = %.2e / %.2f,   ymax = %.2e * %.2f", fPlotYMin, fPlotYMarginBelowMin, fPlotYMax, fPlotYMarginAboveMax), 12-printdebug);
    commonYmin = (fPlotYMarginBelowMin!=0) ? fPlotYMin/fPlotYMarginBelowMin : 0;
    commonYmax = fPlotYMax*fPlotYMarginAboveMax;
    rangeComputed=kTRUE; //in the end the range has to be reset, otherwise next time it will take the old range.
  } else {
    commonYmin = fPlotYMin;
    commonYmax = fPlotYMax;
  }
  LmHelper::Debug(Form("  %s plotting range: ymin = %.2e,   ymax = %.2e", (rangeComputed)?"computed":"specified", commonYmin, commonYmax), 12-printdebug);

  unsigned int ihist=0;
  unsigned int reqHist[(int)TMath::Log2(LmSignal::kMAXhist)];
  unsigned int &firstHist=reqHist[0]; // reference, for better readability.
  TH1D* hGray[(int)TMath::Log2(LmSignal::kMAXhist)]; // for additional legend entries if more than one histogram type (bit) will be drawn.

  //
  // Loop over the requested histograms to configure their styles and ranges etc. Drawing is done later.
  //
  for (unsigned int iBit = 1; iBit < LmSignal::kMAXhist; iBit *= 2) {
    if ( !(iBit & histBits) ) continue; // continue if current histogram was not requested.
    reqHist[ihist] = iBit; // store the bits of all requested histograms.

    if (fCompareSignalsToAverage && fBest[0]>-1) {
      GetLmSignalI(fBest[0])->GetLmHist(iBit,bin_number,projOnMee)->SetLineWidth(3);
      GetLmSignalI(fBest[1])->GetLmHist(iBit,bin_number,projOnMee)->SetLineWidth(3);
      GetLmSignalI(fBest[2])->GetLmHist(iBit,bin_number,projOnMee)->SetLineWidth(3);
      GetLmSignalI(fBest[0])->GetLmHist(iBit,bin_number,projOnMee)->SetLineStyle(2);
      GetLmSignalI(fBest[1])->GetLmHist(iBit,bin_number,projOnMee)->SetLineStyle(5);
      GetLmSignalI(fBest[2])->GetLmHist(iBit,bin_number,projOnMee)->SetLineStyle(7);
    }

    Int_t Nsignals = GetNSignals();
    if (printOnlyAverage) Nsignals=1;
    // when plotting only the average, this loop is only used once to draw axes with the correct label sizes etc.
    // @TODO: better create a pointer which stores GetLmSignalI() or GetLmSigAverage(), otherwise - in case of
    //        'printOnlyAverage==kTRUE' - the first signal is modified without need.
    for (Int_t i = 0; i < Nsignals; ++i) {
      //if (!CheckRequestedSigI(i)) continue; // the gray markers become wrong if signal 0 was not requested.
      // reset modifications made on best signals, when drawn later with another handler
      if (i!=fBest[0]&&i!=fBest[1]&&i!=fBest[2]) {
        GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetLineWidth(1);
        GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetLineStyle(1);
      }
      // beautify histograms
      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetLineColor(LmHelper::GetUniformColor(i, GetNSignals()));
      // GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetYaxis()->SetTitle("counts (arb. units)");

      if (fUseDifferentMarkers == kTRUE && Nsignals < 8){
        GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerStyle(LmHelper::GetMarker(i));
      }
      else GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerStyle(20);

      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerColor(LmHelper::GetUniformColor(i, GetNSignals()));
      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerSize(fMarkerSize+0.5); //PRL;
      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetFillStyle(0);
      //GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetFillColor(kAzure+1);
      //GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetFillColorAlpha(LmHelper::GetUniformColor(i, GetNSignals()), 0.4);
      if (ihist>0) { // if more than one histogram type (bit) will be drawn, modify the following ones.
        //GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetLineStyle(ihist+1);
        GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetLineStyle(1);
        GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerStyle(LmHelper::GetCompareMarker(ihist));
        if(iBit == LmSignal::kBkg){
          GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetLineColor(kBlue);
          GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerColor(kBlue);
        }
        if(iBit == LmSignal::kUnlike){
          GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetLineColor(kRed);
          GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerColor(kRed);
        }


        if (fLmSigAverage && iBit == LmSignal::kSubSig) { // average currently only available for SubSig.
          //GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->SetLineStyle(ihist+1);
          GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->SetLineStyle(1);
          GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->SetLineColor(kBlack);
          GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerStyle(LmHelper::GetCompareMarker(ihist));
          GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerColor(kBlack);
        }
        if(iBit == LmSignal::kSubSig){
          GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetLineColor(kBlack);
          GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerColor(kBlack);
        }
      }
      // Set label and title sizes. Update offsets for ratio plot.
      Double_t textSize = gStyle->GetTextSize();//*sizefac; //PRL
      std::cout << "textsize:" << textSize << "  " << gStyle->GetTextSize() << std::endl;

      if (fDoRatio) {
        //textSize /= (1.-fRatioPadSize);
        GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetXaxis()->SetTitleOffset(gStyle->GetTitleOffset("X")); //PRL
        GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetYaxis()->SetTitleOffset(gStyle->GetTitleOffset("Y"));


	//GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetXaxis()->SetTitleOffset(1.2);
        //GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetYaxis()->SetTitleOffset(gStyle->GetTitleOffset("Y")*(1.-fRatioPadSize));
      }

      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist()->SetLabelOffset(gStyle->GetLabelOffset("X"),"X"); //PRL -8 ptee wide
      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist()->SetLabelOffset(gStyle->GetLabelOffset("Y"),"Y"); //PRL -8 ptee wide
      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist()->SetLabelSize(gStyle->GetLabelSize(),"XY"); //PRL -8 ptee wide
      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist()->SetLabelSize(gStyle->GetLabelSize(),"Y"); //PRL -8 ptee wide
      // GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist()->SetLabelSize(gStyle->GetLabelSize()-6,"Y"); //PRL -8 ptee wide
      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist()->SetLabelFont(gStyle->GetLabelFont(),"XY");
      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist()->SetTitleOffset(gStyle->GetTitleOffset("X"),"X");
      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist()->SetTitleOffset(gStyle->GetTitleOffset("Y"),"Y");
      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist()->SetTitleSize(gStyle->GetTitleSize(),"XY");
      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist()->SetTitleFont(gStyle->GetTitleFont(),"XY");
      //GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist()->SetLabelSize(textSize,"XY");
      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist()->GetXaxis()->SetNdivisions(6,6, 0, kTRUE);
      //
      // Set axis ranges
      // need to set identical ranges for all histograms, otherwise the arrows (for confidence levels) will be scaled bad (relative to full range).
      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetAxisRange(commonXmin, commonXmax, "X");
      GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->SetAxisRange(commonYmin, commonYmax, "Y");
      //
      // Draw axes
      if ((iBit==firstHist) && (i==FirstReqSig())) {
        GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->DrawCopy("axis");
      }
      //
      // Draw LmHistogram of each signal. This is done later, after the cocktail was possibly drawn.
      // ...
    } // Nsignals

    // create extra gray-colored histograms for additional legend entries.
    hGray[ihist] = new TH1D( *(GetReferenceSignal()->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist()) );
    hGray[ihist]->SetTitle(GetReferenceSignal()->GetCharHistBit(iBit));
    //hGray[ihist]->SetLineColor(kGray+1);
    //hGray[ihist]->SetMarkerColor(kGray+1);
    ihist++;
  } // hist bit loop
  const unsigned int nHists = ihist;

  //
  // Printing of cocktail.
  //
  if (fCocktailProcessed) {
    // draw cocktail only if one of the signal histograms is plotted (otherwise it will be plotted also into S/B plots etc...)
    if (firstHist & (LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg) ) {
      // loop over all attached cocktails
      //for(UInt_t ic = 0; ic < fLmCocktails.size(); ++ic) {
      //  if(fLmCocktails.at(ic)->HasSystematics())
      //    fLmCocktails.at(ic)->GetSumErr1D(bin_number,projOnMee)->DrawClone(Form("%s same", fLmCocktails.at(ic)->GetDrawStyleErr())); // draw systematics if available.
      //  TObjArray* oaCocktail = fLmCocktails.at(ic)->GetSpectra1D(bin_number, projOnMee);
      //  for(Int_t i = 0; i < oaCocktail->GetEntries(); ++i) ((TH1D*) oaCocktail->At(i))->SetLineWidth(2);
      //  if (ic==fLmCocktails.size()-1) oaCocktail->DrawClone(Form("%s same", fLmCocktails.at(ic)->GetDrawStyle())); // draw all contributions only for the last cocktail.
      //  ((TH1D*) oaCocktail->At(0))->DrawClone(Form("%s same", fLmCocktails.at(ic)->GetDrawStyle())); // draw the sum again, looks nicer.
      //  delete oaCocktail;
      //}
      for(UInt_t ic = 0; ic < fLmCocktails.size(); ++ic) {
        // When drawing multiple cocktails, consider using their different draw options like kOnlySum or kAllButSum.
        // Specify them via cocktail->SetDrawOption(LmCocktail::kOnlySum);
        fLmCocktails.at(ic)->DrawProjection(bin_number,projOnMee);
        // if(fLmCocktails.at(ic)->HasSystematics())  //jerome edit
        //   fLmCocktails.at(ic)->GetSumErr1D(bin_number,projOnMee)->DrawClone(Form("%s same", "E3")); // draw systematics if available.
        // TObjArray* oaCocktail = fLmCocktails.at(ic)->GetSpectra1D(bin_number, projOnMee);
        // for(Int_t i = 0; i < oaCocktail->GetEntries(); ++i) ((TH1D*) oaCocktail->At(i))->SetLineWidth(2);
        // if (ic==fLmCocktails.size()-1) oaCocktail->DrawClone(Form("%s same", "hist c")); // draw all contributions only for the last cocktail.
        // ((TH1D*) oaCocktail->At(0))->DrawClone(Form("%s same", "hist c")); // draw the sum again, looks nicer.
        // delete oaCocktail;
      }
    }
  }

  //
  // Printing of datapoints of all signals which are desired according to the configuration of this handler.
  //
  for (unsigned int iBit = 1; iBit < LmSignal::kMAXhist; iBit *= 2) {
    if (fType==kCocktailOnly) break;
    if ( !(iBit & histBits) ) continue; // continue if current histogram was not requested.
    if (!printOnlyAverage) {
      // Draw LmHistogram of each signal. This contains datapoints, systematics graphs, external objects, arrows...
      for (Int_t i = 0; i < GetNSignals(); ++i)
        if (CheckRequestedSigI(i)) GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->DrawCopy();
        // if (CheckRequestedSigI(i)) GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->DrawCopy("p E same;p E2 same"); Jerome edit
      if (fType==kCombine && fLmSigCombined) {
        GetLmSigCombined()->GetLmHist(iBit,bin_number,projOnMee)->SetLineColor(kBlack);
        GetLmSigCombined()->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerStyle(20);
        GetLmSigCombined()->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerColor(kBlack);
        GetLmSigCombined()->GetLmHist(iBit,bin_number,projOnMee)->SetFillStyle(0);
        GetLmSigCombined()->GetLmHist(iBit,bin_number,projOnMee)->SetAxisRange(commonXmin, commonXmax, "X");
        GetLmSigCombined()->GetLmHist(iBit,bin_number,projOnMee)->SetAxisRange(commonYmin, commonYmax, "Y");
        GetLmSigCombined()->GetLmHist(firstHist,bin_number,projOnMee)->DrawCopy();
        // GetLmSigCombined()->GetLmHist(firstHist,bin_number,projOnMee)->DrawCopy("p E same;p E2 same"); Jerome edit
      }
    }
    // The average may be desired to be drawn in quite a few cases:
    if ((fType==kAverage || fType==kWeightedAverage || fCompareSignalsToAverage || printOnlyAverage)
        && fLmSigAverage && iBit == LmSignal::kSubSig) { // Average currently only available for kSubSig
      GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->SetLineColor(kBlack);
      GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerStyle(20);
      GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerColor(kBlack);
      GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->SetFillStyle(0);
      if (fCompareSignalsToAverage) { // Distinguish the average from all other signals and even from the combined signal if also drawn.
        GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerSize(1.3 +0.5); //PRL
        GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->SetMarkerStyle(21);
      }
      GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->SetAxisRange(commonXmin, commonXmax, "X");
      GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->SetAxisRange(commonYmin, commonYmax, "Y");
      GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->DrawCopy();
      // GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->DrawCopy("p E same;p E2 same"); Jerome edit
    }
  }
  // draw axes again, which may have been over-drawn by cocktail or other lines.
  // @TODO: not yet perfect, because the axis line is too narrow... fix it inside LmHistogram::Draw().
  GetReferenceSignal()->GetLmHist(firstHist,bin_number,projOnMee)->Draw("axis same");

  TObjArray* oaLabels = GenerateLabels();
  if (oaLabels) {
    FillLabels(oaLabels, bin_number, projOnMee);
    oaLabels->DrawClone("same");
    delete oaLabels;
  }
  if (printLegend){
    TLegend* leg = GenerateLegend(bin_number, projOnMee, firstHist, nHists>1?nHists:0, printOnlyAverage);
    if (nHists>1) { // add extra entries for the histogram bits (types) to the legend
      for (unsigned int ihist=0; ihist<nHists; ihist++) { leg->AddEntry(hGray[ihist], "", fLegendEntryDrawOption.Data()); } //hGray[ihist]->GetTitle()
    }
    leg->DrawClone("same");
    delete leg;
  }
  for (unsigned int ihist=0; ihist<nHists; ihist++) {
    delete hGray[ihist];
  }

  if (fDoRatio) {
    can->cd(2)->SetLogy(fPlotRatioLogy); // somehow it crashes when done further above...
    const int Nratios = 10;
    TH1D* hDenominator = 0x0;
    TGraphAsymmErrors* grRatioCocktSys[Nratios];
    TString sYtitle;
    if (fCocktailProcessed) { // produce ratios relative to sum of first attached cocktail. //jerome edit for all cocktails
      LmHelper::Debug(Form("  produce ratios relative to sum of first attached cocktail."), 10-printdebug);
      for(Int_t i1=0; i1<fLmCocktails.size(); i1++){
        hDenominator = fLmCocktails.at(0)->GetSum1D(bin_number, projOnMee);
        sYtitle="Data/Cockt.";
        if(fLmCocktails.at(i1)->HasSystematics()){
          grRatioCocktSys[i1] = new TGraphAsymmErrors(*(fLmCocktails.at(i1)->GetSumErr1D(bin_number,projOnMee)));
          for(Int_t igr = 0; igr < grRatioCocktSys[i1]->GetN(); ++igr){
            Double_t xtmp,ytmp;
            grRatioCocktSys[i1]->SetFillColorAlpha(kGray+1,0.5);
            grRatioCocktSys[i1]->GetPoint(igr,xtmp,ytmp);
            if (ytmp == 0) ytmp = 1e-10; // check if denominator is zero
            grRatioCocktSys[i1]->SetPoint(igr,xtmp,1.);
            if (ytmp == 0) ytmp = 1e-10; // check if denominator is zero
            grRatioCocktSys[i1]->SetPointError(igr,grRatioCocktSys[i1]->GetErrorXlow(igr),grRatioCocktSys[i1]->GetErrorXhigh(igr),
                                               grRatioCocktSys[i1]->GetErrorYlow(igr)/ytmp,grRatioCocktSys[i1]->GetErrorYhigh(igr)/ytmp);
          }
        }
      }

      //for(Int_t i1=0; i1<fLmCocktails.size(); i1++){
      //  hDenominator = fLmCocktails.at(0)->GetSum1D(bin_number, projOnMee);
      //  sYtitle="Data/Theory";
      //  if(fLmCocktails.at(i1)->HasSystematics()){
      //    grRatioCocktSys[i1] = new TGraphAsymmErrors(*(fLmCocktails.at(i1)->GetSumErr1D(bin_number,projOnMee)));
      //    for(Int_t igr = 0; igr < grRatioCocktSys[i1]->GetN(); ++igr){
      //      Double_t xtmp,ytmp;
      //      grRatioCocktSys[i1]->SetFillColorAlpha(kGray+1,0.5);
      //      grRatioCocktSys[i1]->GetPoint(igr,xtmp,ytmp);
      //      if (ytmp == 0) ytmp = 1e-10; // check if denominator is zero
      //      grRatioCocktSys[i1]->SetPoint(igr,xtmp,1.);
      //      if (ytmp == 0) ytmp = 1e-10; // check if denominator is zero
      //      grRatioCocktSys[i1]->SetPointError(igr,grRatioCocktSys[i1]->GetErrorXlow(igr),grRatioCocktSys[i1]->GetErrorXhigh(igr),
      //                                         grRatioCocktSys[i1]->GetErrorYlow(igr)/ytmp,grRatioCocktSys[i1]->GetErrorYhigh(igr)/ytmp);
      //    }
      //  }
      //}
    }
    else if (nHists==2) { // produce ratios between two histogram types (histbits).
      LmHelper::Debug(Form("  produce ratios between two histogram types (histbits)."), 10-printdebug);
      //hDenominator = ...; // must be set inside the for loop below...
      sYtitle=Form("%s/%s", LmSignal::GetCharHistBitStatic(reqHist[0]), LmSignal::GetCharHistBitStatic(reqHist[1]));
    }
    else { // produce ratios relative to first input.
      LmHelper::Debug(Form("  produce ratios relative to first input."), 10-printdebug);
      hDenominator = GetLmSignalI(0)->GetLmHist(firstHist,bin_number,projOnMee)->GetDatahist();
      if (fRatioTitle == "") sYtitle="data/first input";
      else sYtitle = fRatioTitle;
    }
    TH1D* haxis = 0x0;
    for (Int_t i = 0; i < GetNSignals(); ++i) {
      if (printOnlyAverage) break; // ratio not implemented for average and combined signal. Use compare handler to do this...
      if (!CheckRequestedSigI(i)) continue;
      if (nHists==2) { // produce ratios between two histogram types (histbits).
        hDenominator = GetLmSignalI(i)->GetLmHist(reqHist[1],bin_number,projOnMee)->GetDatahist();
      }
      //
      // Perform division.
      // Done inside LmHistogram. Special cases like divide option 0 and incompatible binnings are handled there.
      // -----
      LmHistogram* ratioi = new LmHistogram( *(GetLmSignalI(i)->GetLmHist(firstHist,bin_number,projOnMee)) );
      ratioi->Divide(hDenominator,fDivideOption.Data());
      // -----
      if (i==FirstReqSig()) { // instead of i==0
        ratioi->GetYaxis()->UnZoom();
        ratioi->GetYaxis()->SetTitle(sYtitle.Data());
        ratioi->GetYaxis()->CenterTitle();
        ratioi->GetYaxis()->SetTitleOffset(gStyle->GetTitleOffset("Y")+0.3); //PRL

	//ratioi->GetYaxis()->SetTitleOffset(ratioi->GetYaxis()->GetTitleOffset()*fRatioPadSize/(1.-fRatioPadSize) * fRatioTitleOffset);
        //ratioi->GetDatahist()->SetTitleSize(ratioi->GetDatahist()->GetTitleSize()/fRatioPadSize*(1.-fRatioPadSize) * fRatioTitleSize,"xy");
        //ratioi->GetDatahist()->SetLabelSize(ratioi->GetDatahist()->GetLabelSize()/fRatioPadSize*(1.-fRatioPadSize),"xy");

        ratioi->GetDatahist()->SetTitleFont(gStyle->GetTextFont(),"xy"); //PRL
        ratioi->GetDatahist()->SetTitleSize(gStyle->GetTitleSize(),"x"); //PRL
        //ratioi->GetDatahist()->SetTitleSize(gStyle->GetTitleSize()-14,"y"); //PRL wide
        ratioi->GetDatahist()->SetTitleSize(gStyle->GetTitleSize()-8.,"y"); //PRL height
        ratioi->GetDatahist()->SetTitleOffset(gStyle->GetTitleOffset("y")+0.5,"y"); //PRL height
        ratioi->GetDatahist()->SetTitleOffset(gStyle->GetTitleOffset("x")+2.3,"x"); //PRL height
        ratioi->GetDatahist()->SetLabelFont(gStyle->GetLabelFont(),"xy");
        ratioi->GetDatahist()->SetLabelSize(gStyle->GetLabelSize(),"x");
        //ratioi->GetDatahist()->SetLabelSize(gStyle->GetLabelSize()-8,"y");
        ratioi->GetDatahist()->SetLabelSize(gStyle->GetLabelSize(),"y");

        if (fPlotRatioMax>0) ratioi->SetAxisRange(fPlotRatioMin, fPlotRatioMax, "Y");
        ratioi->GetDatahist()->GetYaxis()->SetNdivisions(4, 5, 0, kTRUE); // 4,5,0 = 504
        ratioi->GetDatahist()->DrawCopy("axis");
        haxis = new TH1D(*(ratioi->GetDatahist()));
        for (Int_t i2 =0; i2<fLmCocktails.size(); i2++){
          if(grRatioCocktSys[i2]) grRatioCocktSys[i2]->DrawClone(Form("same %s",GetDrawStyleCocktailErr()));
        }
        // line at unity
        TLine l1(ratioi->GetXaxis()->GetBinLowEdge(ratioi->GetXaxis()->GetFirst()), 1., ratioi->GetXaxis()->GetBinLowEdge(ratioi->GetXaxis()->GetLast()+1), 1.);
        l1.SetLineWidth(2);
        if (fCocktailProcessed) {
          l1.SetLineColor(fLmCocktails.at(0)->GetSum1D(bin_number, projOnMee)->GetLineColor());
          l1.SetLineStyle(fLmCocktails.at(0)->GetSum1D(bin_number, projOnMee)->GetLineStyle());
          l1.SetLineWidth(fLmCocktails.at(0)->GetSum1D(bin_number, projOnMee)->GetLineWidth());
        }
        l1.DrawClone();

        // Draw ratios of sums of additional cocktails. A bit dirty to do it inside the LmSignal loop, but easiest...
        if (fCocktailProcessed) {
          for(UInt_t ic = 1; ic <fLmCocktails.size() ; ++ic) { //fLmCocktails.size()
	    //if(ic==2) continue;
            LmHelper::Debug(Form("  produce ratios between two cocktails."), 10-printdebug);
            // It would be great to store spectra of LmCocktailPart as LmHistograms, then one could use a copy
            LmHistogram* cocktratioi = new LmHistogram( (TH1D*) fLmCocktails.at(ic)->GetSum1D(bin_number, projOnMee)->Clone("cocktratioi") );
            cocktratioi->Divide(hDenominator,fDivideOption.Data());
            cocktratioi->DrawCopy(Form("%s same", fLmCocktails.at(ic)->GetDrawStyle()));
            delete cocktratioi;
            //TH1D* cocktratioi = (TH1D*) fLmCocktails.at(ic)->GetSum1D(bin_number, projOnMee)->Clone("cocktratioi");
//            TH1D* hDenominator = (TH1D*) fLmCocktails.at(ic)->GetSum1D(bin_number, projOnMee)->Clone("cocktratioi");
//            LmHistogram* ratioi = new LmHistogram( *(GetLmSignalI(i)->GetLmHist(firstHist,bin_number,projOnMee)) );
//            ratioi->Divide(hDenominator,fDivideOption.Data());
//            ratioi->GetDatahist()->DrawCopy("same");


            //for(Int_t i1=0; i1<fLmCocktails.size(); i1++){
            //if(fLmCocktails.at(i1)->HasSystematics()){
            //  grRatioCocktSys[i1] = new TGraphAsymmErrors(*(fLmCocktails.at(i1)->GetSumErr1D(bin_number,projOnMee)));
            //  for(Int_t igr = 0; igr < grRatioCocktSys[i1]->GetN(); ++igr){
            //    Double_t xtmp,ytmp;
            //    grRatioCocktSys[i1]->SetFillColorAlpha(kGray+1,0.5);
            //    grRatioCocktSys[i1]->GetPoint(igr,xtmp,ytmp);
            //    if (ytmp == 0) ytmp = 1e-10; // check if denominator is zero
            //    grRatioCocktSys[i1]->SetPoint(igr,xtmp,1.);
            //    if (ytmp == 0) ytmp = 1e-10; // check if denominator is zero
            //    grRatioCocktSys[i1]->SetPointError(igr,grRatioCocktSys[i1]->GetErrorXlow(igr),grRatioCocktSys[i1]->GetErrorXhigh(igr),
            //                                       grRatioCocktSys[i1]->GetErrorYlow(igr)/ytmp,grRatioCocktSys[i1]->GetErrorYhigh(igr)/ytmp);
            //  }
            //}


            //cocktratioi->Divide(cocktratioi,hDenominator,1,1,"0"); // divide option 0
            //cocktratioi->DrawCopy(Form("%s same", fLmCocktails.at(ic)->GetDrawStyle()));
            TFile* file_ = TFile::Open("ratio_cock.root", "UPDATE");
            //cocktratioi->Write(Form("%s_%i","cocktratioi", bin_number ));
            //ratioi->GetSystError()->Write();
            file_->Close();
            delete file_;
            //delete cocktratioi;
          }
        }
      }
      if(!fCocktailProcessed && nHists==1 && i==FirstReqSig()) { // first ratio histogram in case of no cocktail and no histbit comparison
        ratioi->DrawCopy("onlysys"); // or draw only its systematics?
      }
      else { // draw all other ratio histograms
        if (fType!=kCocktailOnly){
          //ratioi->DrawCopy("p hist same");
          ratioi->DrawCopy();

          TFile* file_ = TFile::Open("ratio_1.root", "UPDATE");
          ratioi->GetDatahist()->Write(Form("%s_%i",ratioi->GetDatahist()->GetName(), i ));
          //ratioi->GetSystError()->Write();
          file_->Close();
          delete file_;

        }
        // if (fType!=kCocktailOnly) ratioi->DrawCopy("p E same;p E2 same"); Jerome edit
      }
      delete ratioi;
    } // NSignals
    haxis->DrawCopy("axis same"); // draw axes again.
    delete haxis;
  } // doRatio

  // construct filename of plot
  if (sfilename.IsNull()||sfilename.BeginsWith('+')) {
    TString ssuffix = "";
    if (sfilename.BeginsWith('+')) {
      sfilename.Remove(0,1);
      ssuffix.Append(sfilename);
    }
    sfilename = "/c";
    sfilename.Prepend(gEnv->GetValue("Canvas.PrintDirectory",".")); // not the best way maybe...
    for (unsigned int iBit = 1; iBit < LmSignal::kMAXhist; iBit *= 2) {
      if ((iBit & histBits) && fType!=kCocktailOnly) sfilename.Append(GetReferenceSignal()->GetCharHistBit(iBit,kTRUE));
    }
    if (fType>kStd && !(fType==kCompare&&GetNSignals()<2)) // avoid to append "Compare" if only one signal is plotted. (but dont use GetNRequestedSig() to keep plots ordered)
      sfilename.Append(GetTypename());
    LmBaseSignal::inputAxis inputAx = LmBaseSignal::CheckWhichInputAxis( (TH1*) GetReferenceSignal()->GetLmHist(firstHist,bin_number,projOnMee)->GetDatahist() );
    sfilename.Append("_"+LmBaseSignal::GetInputAxisCode(inputAx)); // instead of hardcoded Append("_Mee") or Append("_Ptee").
    sfilename.Append(Form("%s_bin%d",ssuffix.Data(),bin_number));
    if (!fRequestedSignals.IsNull()) sfilename.Append(Form("_req%s",fRequestedSignals.Data()));
    sfilename.Append(Form(".%s", fFileType.Data()));
  }

  LmHelper::Debug(Form("  print canvas, called '%s' or '%s'", filename, sfilename.Data()), 12-printdebug); // @TODO: this is a really fancy bug! must be a memory leak somewhere.
  for(Int_t i = 0; i < 3; ++i) can->RedrawAxis();
  if (ownCan) {
    can->Print(sfilename.Data());
    //can->Destructor(); // @TODO: this crashes when doing phiV study with templates...
  } else {
    can->SetTitle(sfilename.Data()); // so that the name can be used for external printing.
  }
  if (rangeComputed) ResetPlotRangeY();
  return;
}



//_______________________________________________________________________________________________
void LmHandler::PrintCompareRatio(unsigned int histBits, unsigned int bin_min, unsigned int bin_max, Bool_t projOnMee, const Char_t* filename, Bool_t printLegend, Bool_t setLogy, TCanvas* can, Bool_t printOnlyAverage)
{
  /// Generic plotting function.
  /// Plots requested histograms into canvas and prints canvas to file. Also plots legend + labels + ratio ... if requested.
  /// Modify the plotting ranges via SetPlotRangeMee()/Ptee(), SetPlotRangeY(), SetPlotRangeYMargins().
  /// If no y-range is given, it finds the optimum plotting range by internally calling ComputeOptimumPlotRangeY().
  ///
  /// NOTE: PrintCompare() works for all handler types and is sensitive to them. In case of a crash, check that
  ///       function GetReferenceSignal() returns the signal that you intend and change handler type if needed.
  ///
  /// In case of multiple cocktails, only for the last cocktail all contributions are drawn and added to the legend.
  /// For the other cocktails only their individual sum is drawn.
  /// The ratio is done w.r.t. the first cocktail's sum, and the sums of the other cocktails are compared to it.
  ///
  /// @param hitBits Bits of histogram types that shall be plotted into the same canvas (e.g. LmSignal::kUnlike+LmSignal::kBkg). the order has no effect.
  /// @param bin_number Projection bin to plot.
  /// @param projOnMee Plot x- or y-projections (set via LmBaseSignal::kProjOnMee or kProjOnPtee).
  /// @param filename If starting with '+', the filename is generated automatically, but the string after '+' is appended.
  /// @param can Option to provide canvas. The (generated) filename is set as the canvas title for external printing.

  // Bool_t ratioAxis = kFALSE; // was not used
  Double_t sizefac=0.7;
  int printdebug=0;
  LmHelper::Debug(Form("LmHandler::PrintCompareAll()"), 5-printdebug);
  TString sfilename(filename); // because "const Char_t* filename" somehow gets modified by operations related to LmHistogram... (in case with cocktail)

  if (fType==kNoProcess) {
    LmHelper::Warning(Form("LmHandler::PrintCompare(): this LmHandler (fType=%i) is not ready for printing. Call Process(..) or specify type in constructor.", fType));
    return;
  }

  Bool_t ownCan=kFALSE;
  if (!can) {
    ownCan=kTRUE;
    can = new TCanvas("cCompareAll", "cCompareAll");
    can->Clear();
  }
  //can->SetFillStyle(0);
  //can->SetFrameFillStyle(0);
  can->cd()->SetLogy(setLogy);

  if (fDoRatio) {
    LmHelper::Debug(Form("  create ratio pad"), 10-printdebug);
    Double_t bottommargin = 0.09/fRatioPadSize;
    can->Divide(1,2);
    can->cd(1)->SetPad(0., fRatioPadSize, 1., 1.);  // top pad
    can->cd(1)->SetBottomMargin(0.001);
    //can->cd(1)->SetFillStyle(0);
    //can->cd(1)->SetFrameFillStyle(0);
    can->cd(2)->SetPad(0., 0., 1., fRatioPadSize);  // bottom pad
    can->cd(2)->SetTopMargin(0);
    can->cd(2)->SetBottomMargin(bottommargin); // for x-axis label
    //can->cd(2)->SetFillStyle(0);
    //can->cd(2)->SetFrameFillStyle(0);
    // move to upper pad and set log if requested.
    can->cd(1)->SetLogy(setLogy);
  }

  // don't use floats (LmHelper::kSmallDelta will not work)
  Double_t commonXmin=0., commonXmax=0.;
  Double_t commonYmin=0., commonYmax=0.;

  // store the common x-range
  if (projOnMee==LmBaseSignal::kProjOnMee) {
    if (fPlotXMeeMin>-1  && fPlotXMeeMax>0)  { commonXmin=fPlotXMeeMin;  commonXmax=fPlotXMeeMax;  }
  } else { // Ptee
    if (fPlotXPteeMin>-1 && fPlotXPteeMax>0) { commonXmin=fPlotXPteeMin; commonXmax=fPlotXPteeMax; }
  }

  // store the common y-range
  // determine the common y-axis range for all histograms, if it was not manually set to valid values.
  // in that case also apply the margins.
  Bool_t rangeComputed=kFALSE;
  if (fPlotYMin >= fPlotYMax) {
    ComputeOptimumPlotRangeY(histBits, bin_min, projOnMee, printOnlyAverage); // maybe one could just not call this function in case of printOnlyAverage=kTRUE...
    LmHelper::Debug(Form("  using computed range and margins: ymin = %.2e / %.2f,   ymax = %.2e * %.2f", fPlotYMin, fPlotYMarginBelowMin, fPlotYMax, fPlotYMarginAboveMax), 12-printdebug);
    commonYmin = (fPlotYMarginBelowMin!=0) ? fPlotYMin/fPlotYMarginBelowMin : 0;
    commonYmax = fPlotYMax*fPlotYMarginAboveMax;
    rangeComputed=kTRUE; //in the end the range has to be reset, otherwise next time it will take the old range.
  } else {
    commonYmin = fPlotYMin;
    commonYmax = fPlotYMax;
  }
  LmHelper::Debug(Form("  %s plotting range: ymin = %.2e,   ymax = %.2e", (rangeComputed)?"computed":"specified", commonYmin, commonYmax), 12-printdebug);

  unsigned int ihist=0;
  unsigned int reqHist[(int)TMath::Log2(LmSignal::kMAXhist)];
  unsigned int &firstHist=reqHist[0]; // reference, for better readability.
  //TH1D* hGray[(int)TMath::Log2(LmSignal::kMAXhist)]; // for additional legend entries if more than one histogram type (bit) will be drawn.

  std::cout << "Number of hists: " << (int)TMath::Log2(LmSignal::kMAXhist) << std::endl;

  for(Int_t bin_i = bin_min; bin_i<=bin_max; bin_i++){
    std::cout << "Start " << bin_i << std::endl;
    std::cout << bin_i << "   " << GetReferenceSignal() << "   "  << GetReferenceSignal()->GetMaxBinProj(projOnMee) << std::endl;
    if ((Int_t)bin_i > GetReferenceSignal()->GetMaxBinProj(projOnMee)) {
      LmHelper::Error(Form("LmHandler::PrintCompare(): projection bin number (%i) out of range (on axis '%i'). [%i=X-axis(Mee),%i=Y-axis(Ptee)]", bin_i, projOnMee, LmBaseSignal::kProjOnMee, LmBaseSignal::kProjOnPtee));
      return;
    }

    if ( (histBits & LmSignal::kRfactor) && GetLmSignalI(0)->GetLmBackground()->GetUseRfactorUnity() ) {
      LmHelper::Warning(Form("LmHandler::PrintCompare(): the 1D Rfactors are not created from the 2D Rfactor which uses a unity range! (never project ratios!)"));
    }

    //
    // Loop over the requested histograms to configure their styles and ranges etc. Drawing is done later.
    //
    for (unsigned int iBit = 1; iBit < LmSignal::kMAXhist; iBit *= 2) {
      if ( !(iBit & histBits) ) continue; // continue if current histogram was not requested.
      reqHist[ihist] = iBit; // store the bits of all requested histograms.

      //if (fCompareSignalsToAverage && fBest[0]>-1) {
      //  GetLmSignalI(fBest[0])->GetLmHist(iBit,bin_i,projOnMee)->SetLineWidth(3);
      //  GetLmSignalI(fBest[1])->GetLmHist(iBit,bin_i,projOnMee)->SetLineWidth(3);
      //  GetLmSignalI(fBest[2])->GetLmHist(iBit,bin_i,projOnMee)->SetLineWidth(3);
      //  GetLmSignalI(fBest[0])->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(2);
      //  GetLmSignalI(fBest[1])->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(5);
      //  GetLmSignalI(fBest[2])->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(7);
      //}

      Int_t Nsignals = GetNSignals();
      if (printOnlyAverage) Nsignals=1;
      // when plotting only the average, this loop is only used once to draw axes with the correct label sizes etc.
      // @TODO: better create a pointer which stores GetLmSignalI() or GetLmSigAverage(), otherwise - in case of
      //        'printOnlyAverage==kTRUE' - the first signal is modified without need.
      for (Int_t i = 0; i < Nsignals; ++i) {
        //if (!CheckRequestedSigI(i)) continue; // the gray markers become wrong if signal 0 was not requested.
        // reset modifications made on best signals, when drawn later with another handler
        if (i!=fBest[0]&&i!=fBest[1]&&i!=fBest[2]) {
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineWidth(1);
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(1);
        }
        // beautify histograms
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineColor(LmHelper::GetUniformColor(i, GetNSignals()));
        // GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->GetYaxis()->SetTitle("counts (arb. units)");

        if (fUseDifferentMarkers == kTRUE && Nsignals < 8){
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(LmHelper::GetMarker(i));
        }
        else GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(20);

        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(LmHelper::GetUniformColor(i, GetNSignals()));
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerSize(fMarkerSize);
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetFillStyle(0);
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(20);
        if (ihist>0) { // if more than one histogram type (bit) will be drawn, modify the following ones.
          //GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(ihist+1);
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(1);
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(20+bin_i);
          //GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(kGreen+2);
//          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(LmHelper::GetCompareMarker(ihist));
          if(iBit == LmSignal::kBkg){
            GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineColor(kBlue);
            GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(kBlue);
          }
          if(iBit == LmSignal::kUnlike){
            GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineColor(kRed);
            GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(kRed);
          }


          if (fLmSigAverage && iBit == LmSignal::kSubSig) { // average currently only available for SubSig.
            //GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(ihist+1);
            GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(1);
            GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetLineColor(kBlack);
            GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(LmHelper::GetCompareMarker(ihist));
            //GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(20);
            GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(kBlack);
          }
          //if(iBit == LmSignal::kSubSig){
          //  GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineColor(kBlack);
          //  GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(kBlack);
          //}
        }
        // Set label and title sizes. Update offsets for ratio plot.
        Double_t textSize = gStyle->GetTextSize();//*sizefac;  //PRL
	std::cout << "textsize:" << textSize << "  " << gStyle->GetTextSize() << std::endl;
        if (fDoRatio) {
          //textSize /= (1.-fRatioPadSize);
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->GetXaxis()->SetTitleOffset(1.2);
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->GetYaxis()->SetTitleOffset(gStyle->GetTitleOffset("Y")*(1.-fRatioPadSize));
        }
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->GetDatahist()->SetTitleSize(textSize,"XY");
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->GetDatahist()->SetLabelSize(textSize,"XY");
        //
        // Set axis ranges
        // need to set identical ranges for all histograms, otherwise the arrows (for confidence levels) will be scaled bad (relative to full range).
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetAxisRange(commonXmin, commonXmax, "X");
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetAxisRange(commonYmin, commonYmax, "Y");
        //
        // Draw axes
        if ((iBit==firstHist) && (i==FirstReqSig()) && bin_i==bin_min) {
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->DrawCopy("axis");
        }
        //
        // Draw LmHistogram of each signal. This is done later, after the cocktail was possibly drawn.
        // ...
      } // Nsignals

      // create extra gray-colored histograms for additional legend entries.
      //hGray[ihist] = new TH1D( *(GetReferenceSignal()->GetLmHist(iBit,bin_i,projOnMee)->GetDatahist()) );
      //hGray[ihist]->SetTitle(GetReferenceSignal()->GetCharHistBit(iBit));
      //hGray[ihist]->SetLineColor(kGray+1);
      //hGray[ihist]->SetMarkerColor(kGray+1);
      ihist++;
    } // hist bit loop
    const unsigned int nHists = ihist;

    //
    // Printing of cocktail.
    //
    if (fCocktailProcessed) {
      // draw cocktail only if one of the signal histograms is plotted (otherwise it will be plotted also into S/B plots etc...)
      if (firstHist & (LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg) ) {
        // loop over all attached cocktails
        //for(UInt_t ic = 0; ic < fLmCocktails.size(); ++ic) {
        //  if(fLmCocktails.at(ic)->HasSystematics())
        //    fLmCocktails.at(ic)->GetSumErr1D(bin_i,projOnMee)->DrawClone(Form("%s same", fLmCocktails.at(ic)->GetDrawStyleErr())); // draw systematics if available.
        //  TObjArray* oaCocktail = fLmCocktails.at(ic)->GetSpectra1D(bin_i, projOnMee);
        //  for(Int_t i = 0; i < oaCocktail->GetEntries(); ++i) ((TH1D*) oaCocktail->At(i))->SetLineWidth(2);
        //  if (ic==fLmCocktails.size()-1) oaCocktail->DrawClone(Form("%s same", fLmCocktails.at(ic)->GetDrawStyle())); // draw all contributions only for the last cocktail.
        //  ((TH1D*) oaCocktail->At(0))->DrawClone(Form("%s same", fLmCocktails.at(ic)->GetDrawStyle())); // draw the sum again, looks nicer.
        //  delete oaCocktail;
        //}
        for(UInt_t ic = 0; ic < fLmCocktails.size(); ++ic) {
          // When drawing multiple cocktails, consider using their different draw options like kOnlySum or kAllButSum.
          // Specify them via cocktail->SetDrawOption(LmCocktail::kOnlySum);
          fLmCocktails.at(ic)->DrawProjection(bin_i,projOnMee);
          // if(fLmCocktails.at(ic)->HasSystematics())  //jerome edit
          //   fLmCocktails.at(ic)->GetSumErr1D(bin_i,projOnMee)->DrawClone(Form("%s same", "E3")); // draw systematics if available.
          // TObjArray* oaCocktail = fLmCocktails.at(ic)->GetSpectra1D(bin_i, projOnMee);
          // for(Int_t i = 0; i < oaCocktail->GetEntries(); ++i) ((TH1D*) oaCocktail->At(i))->SetLineWidth(2);
          // if (ic==fLmCocktails.size()-1) oaCocktail->DrawClone(Form("%s same", "hist c")); // draw all contributions only for the last cocktail.
          // ((TH1D*) oaCocktail->At(0))->DrawClone(Form("%s same", "hist c")); // draw the sum again, looks nicer.
          // delete oaCocktail;
        }
      }
    }
  }
  TH1D* h1_ref = 0x0;
  for (Int_t i = 0; i < GetNSignals(); ++i){
    for(Int_t bin_i = bin_min; bin_i<=bin_max; bin_i++){
      std::cout << "test " << bin_i << std::endl;

      //
      // Printing of datapoints of all signals which are desired according to the configuration of this handler.
      //
      for (unsigned int iBit = 1; iBit < LmSignal::kMAXhist; iBit *= 2) {
        if (fType==kCocktailOnly) break;
        if ( !(iBit & histBits) ) continue; // continue if current histogram was not requested.
        if (bin_i==bin_min) {
          h1_ref = GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->GetDatahist();
          continue;
        }
        if (!printOnlyAverage) {
          // Draw LmHistogram of each signal. This contains datapoints, systematics graphs, external objects, arrows...
          //for (Int_t i = 0; i < GetNSignals(); ++i){
            if (CheckRequestedSigI(i)){
              GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->Divide(h1_ref);
              GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->DrawCopy();
            }
          //}
            // if (CheckRequestedSigI(i)) GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->DrawCopy("p E same;p E2 same"); Jerome edit
          if (fType==kCombine && fLmSigCombined) {
            GetLmSigCombined()->GetLmHist(iBit,bin_i,projOnMee)->SetLineColor(kBlack);
            GetLmSigCombined()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(20);
            GetLmSigCombined()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(kBlack);
            GetLmSigCombined()->GetLmHist(iBit,bin_i,projOnMee)->SetFillStyle(0);
            GetLmSigCombined()->GetLmHist(iBit,bin_i,projOnMee)->SetAxisRange(commonXmin, commonXmax, "X");
            GetLmSigCombined()->GetLmHist(iBit,bin_i,projOnMee)->SetAxisRange(commonYmin, commonYmax, "Y");
            GetLmSigCombined()->GetLmHist(firstHist,bin_i,projOnMee)->Divide(h1_ref);
            GetLmSigCombined()->GetLmHist(firstHist,bin_i,projOnMee)->DrawCopy();
            // GetLmSigCombined()->GetLmHist(firstHist,bin_i,projOnMee)->DrawCopy("p E same;p E2 same"); Jerome edit
          }
        }
        // The average may be desired to be drawn in quite a few cases:
        if ((fType==kAverage || fType==kWeightedAverage || fCompareSignalsToAverage || printOnlyAverage)
            && fLmSigAverage && iBit == LmSignal::kSubSig) { // Average currently only available for kSubSig
          GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetLineColor(kBlack);
          GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(20);
          GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(kBlack);
          GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetFillStyle(0);
          if (fCompareSignalsToAverage) { // Distinguish the average from all other signals and even from the combined signal if also drawn.
            GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerSize(1.3);
            GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(21);
          }
          GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetAxisRange(commonXmin, commonXmax, "X");
          GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetAxisRange(commonYmin, commonYmax, "Y");
          GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->Divide(h1_ref);
          GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->DrawCopy();
          // GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->DrawCopy("p E same;p E2 same"); Jerome edit
        }
      }

      std::cout << "test2 " << bin_i << std::endl;
      // draw axes again, which may have been over-drawn by cocktail or other lines.
      // @TODO: not yet perfect, because the axis line is too narrow... fix it inside LmHistogram::Draw().
      GetReferenceSignal()->GetLmHist(firstHist,bin_i,projOnMee)->Draw("axis same");

      TObjArray* oaLabels = GenerateLabels();
      if (oaLabels) {
        FillLabels(oaLabels, bin_i, projOnMee);
        oaLabels->DrawClone("same");
        delete oaLabels;
      }
      std::cout << "test3 " << bin_i << std::endl;
      //if (printLegend){
      //  TLegend* leg = GenerateLegend(bin_i, projOnMee, firstHist, nHists>1?nHists:0, printOnlyAverage);
      //  //if (nHists>1) { // add extra entries for the histogram bits (types) to the legend
      //  //  for (unsigned int ihist=0; ihist<nHists; ihist++) { leg->AddEntry(hGray[ihist], "", fLegendEntryDrawOption.Data()); } //hGray[ihist]->GetTitle()
      //  //}
      //  leg->DrawClone("same");
      //  delete leg;
      //}
    }
    std::cout << "test4 " << i << std::endl;
    if (fDoRatio) {
      can->cd(2)->SetLogy(fPlotRatioLogy); // somehow it crashes when done further above...
      const int Nratios = 10;
      TH1D* hDenominator = 0x0;
      TGraphAsymmErrors* grRatioCocktSys[Nratios];
      TString sYtitle;
      for(Int_t i1=0; i1<fLmCocktails.size(); i1++){
        if (fCocktailProcessed) { // produce ratios relative to sum of first attached cocktail. //jerome edit for all cocktails
          LmHelper::Debug(Form("  produce ratios relative to sum of first attached cocktail."), 10-printdebug);
          //for(Int_t i1=0; i1<fLmCocktails.size(); i1++){
            for(Int_t bin_i = bin_min; bin_i<=bin_max; bin_i++){
              hDenominator = fLmCocktails.at(0)->GetSum1D(bin_i, projOnMee);
              sYtitle="Data/Cocktail";
              if(fLmCocktails.at(i1)->HasSystematics()){
                grRatioCocktSys[i1] = new TGraphAsymmErrors(*(fLmCocktails.at(i1)->GetSumErr1D(bin_i,projOnMee)));
                for(Int_t igr = 0; igr < grRatioCocktSys[i1]->GetN(); ++igr){
                  Double_t xtmp,ytmp;
                  grRatioCocktSys[i1]->SetFillColorAlpha(kGray+1,0.5);
                  grRatioCocktSys[i1]->GetPoint(igr,xtmp,ytmp);
                  if (ytmp == 0) ytmp = 1e-10; // check if denominator is zero
                  grRatioCocktSys[i1]->SetPoint(igr,xtmp,1.);
                  if (ytmp == 0) ytmp = 1e-10; // check if denominator is zero
                  grRatioCocktSys[i1]->SetPointError(igr,grRatioCocktSys[i1]->GetErrorXlow(igr),grRatioCocktSys[i1]->GetErrorXhigh(igr),
                                                     grRatioCocktSys[i1]->GetErrorYlow(igr)/ytmp,grRatioCocktSys[i1]->GetErrorYhigh(igr)/ytmp);
                }
              }
            }
          //}
        }
        //else if (nHists==2) { // produce ratios between two histogram types (histbits).
        //  LmHelper::Debug(Form("  produce ratios between two histogram types (histbits)."), 10-printdebug);
        //  //hDenominator = ...; // must be set inside the for loop below...
        //  sYtitle=Form("%s/%s", LmSignal::GetCharHistBitStatic(reqHist[0]), LmSignal::GetCharHistBitStatic(reqHist[1]));
        //}
        else { // produce ratios relative to first input.
          LmHelper::Debug(Form("  produce ratios relative to first input."), 10-printdebug);
          hDenominator = GetLmSignalI(i)->GetLmHist(firstHist,bin_min,projOnMee)->GetDatahist();
          if (fRatioTitle == "") sYtitle="data/first input";
          else sYtitle = fRatioTitle;
        }
      }
      TH1D* haxis = 0x0;
      for (Int_t i = 0; i < GetNSignals(); ++i) {
        for(Int_t bin_i = bin_min; bin_i<=bin_max; bin_i++){
          if (printOnlyAverage) break; // ratio not implemented for average and combined signal. Use compare handler to do this...
          if (!CheckRequestedSigI(i)) continue;
          //if (nHists==2) { // produce ratios between two histogram types (histbits).
            //hDenominator = GetLmSignalI(i)->GetLmHist(reqHist[1],bin_i,projOnMee)->GetDatahist();
            hDenominator = GetLmSignalI(0)->GetLmHist(firstHist,bin_i,projOnMee)->GetDatahist();
          // }
          //
          // Perform division.
          // Done inside LmHistogram. Special cases like divide option 0 and incompatible binnings are handled there.
          // -----
          LmHistogram* ratioi = new LmHistogram( *(GetLmSignalI(i)->GetLmHist(firstHist,bin_i,projOnMee)) );
          ratioi->Divide(hDenominator,fDivideOption.Data());
          if(i==0){
            ratioi->GetYaxis()->UnZoom();
            ratioi->GetYaxis()->SetTitle(sYtitle.Data());
            ratioi->GetYaxis()->CenterTitle();
            ratioi->GetYaxis()->SetTitleOffset(ratioi->GetYaxis()->GetTitleOffset()*fRatioPadSize/(1.-fRatioPadSize) * fRatioTitleOffset);
            ratioi->GetDatahist()->SetTitleSize(ratioi->GetDatahist()->GetTitleSize()/fRatioPadSize*(1.-fRatioPadSize) * fRatioTitleSize,"xy");
            ratioi->GetDatahist()->SetLabelSize(ratioi->GetDatahist()->GetLabelSize()/fRatioPadSize*(1.-fRatioPadSize),"xy");
            //if (fPlotRatioMax>0)

            ratioi->GetDatahist()->GetYaxis()->SetNdivisions(4, 5, 0, kTRUE); // 4,5,0 = 504

            std::cout << "min Ratio: " << fPlotRatioMin << "  max Ratio: " << fPlotRatioMax << std::endl;
            ratioi->SetAxisRange(fPlotRatioMin, fPlotRatioMax, "Y");
            ratioi->GetDatahist()->DrawCopy("axis");
            // ratioAxis = kTRUE; // unused variable...
            // ratioAxis == kTRUE; // this is obviously not right
          }
          // -----
          if (i==FirstReqSig()) { // instead of i==0

            //else ratioi->GetDatahist()->DrawCopy("same axis");
            haxis = new TH1D(*(ratioi->GetDatahist()));
            for (Int_t i2 =0; i2<fLmCocktails.size(); i2++){
              if(grRatioCocktSys[i2]) grRatioCocktSys[i2]->DrawClone(Form("same %s",GetDrawStyleCocktailErr()));
            }
            // line at unity
            TLine l1(ratioi->GetXaxis()->GetBinLowEdge(ratioi->GetXaxis()->GetFirst()), 1., ratioi->GetXaxis()->GetBinLowEdge(ratioi->GetXaxis()->GetLast()+1), 1.);
            l1.SetLineWidth(2);
            //if (fCocktailProcessed) {
            //  l1.SetLineColor(fLmCocktails.at(0)->GetSum1D(bin_i, projOnMee)->GetLineColor());
            //  l1.SetLineStyle(fLmCocktails.at(0)->GetSum1D(bin_i, projOnMee)->GetLineStyle());
            //  l1.SetLineWidth(fLmCocktails.at(0)->GetSum1D(bin_i, projOnMee)->GetLineWidth());
            //}
            l1.DrawClone();

            // Draw ratios of sums of additional cocktails. A bit dirty to do it inside the LmSignal loop, but easiest...
            //if (fCocktailProcessed) {
            //  for(UInt_t ic = 1; ic <fLmCocktails.size() ; ++ic) { //fLmCocktails.size()
            //  //if(ic==2) continue;
            //    LmHelper::Debug(Form("  produce ratios between two cocktails."), 10-printdebug);
            //    // It would be great to store spectra of LmCocktailPart as LmHistograms, then one could use a copy
  //        //      LmHistogram* cocktratioi = new LmHistogram( (TH1D*) fLmCocktails.at(ic)->GetSum1D(bin_i, projOnMee)->Clone("cocktratioi") );
  //        //      cocktratioi->Divide(hDenominator,fDivideOption.Data());
  //        //      cocktratioi->DrawCopy(Form("%s same", fLmCocktails.at(ic)->GetDrawStyle()));
  //        //      delete cocktratioi;
            //    TH1D* cocktratioi = (TH1D*) fLmCocktails.at(ic)->GetSum1D(bin_i, projOnMee)->Clone("cocktratioi");
            //    cocktratioi->Divide(cocktratioi,hDenominator,1,1,"0"); // divide option 0
            //    cocktratioi->DrawCopy(Form("%s same", fLmCocktails.at(ic)->GetDrawStyle()));
            //    TFile* file_ = TFile::Open("ratio_cock.root", "UPDATE");
            //    cocktratioi->Write(Form("%s_%i","cocktratioi", bin_i ));
            //    //ratioi->GetSystError()->Write();
            //    file_->Close();
            //    delete file_;
            //    delete cocktratioi;
            //  }
            //}
          }
          //if(!fCocktailProcessed && nHists==1 && i==FirstReqSig()) { // first ratio histogram in case of no cocktail and no histbit comparison
          //  ratioi->DrawCopy("same onlysys"); // or draw only its systematics?
          //}
          //else { // draw all other ratio histograms
            if (fType!=kCocktailOnly){
              //ratioi->DrawCopy("p hist same");
              if(bin_i == bin_min) continue;
              ratioi->DrawCopy("same");
              std::cout << "plotting raios" << std::endl;
              TFile* file_ = TFile::Open("ratio_2.root", "UPDATE");
              ratioi->GetDatahist()->Write(Form("%s_%i",ratioi->GetDatahist()->GetName(), i ));
              //ratioi->GetSystError()->Write();
              file_->Close();
              delete file_;

            }
            // if (fType!=kCocktailOnly) ratioi->DrawCopy("p E same;p E2 same"); Jerome edit
          //}

          delete ratioi;
        }
      } // NSignals
      haxis->DrawCopy("axis same"); // draw axes again.
      delete haxis;
    } // doRatio

    can->cd(1);
    //std::cout << "End " << bin_i << std::endl;

  }





  // construct filename of plot
  if (sfilename.IsNull()||sfilename.BeginsWith('+')) {
    TString ssuffix = "";
    if (sfilename.BeginsWith('+')) {
      sfilename.Remove(0,1);
      ssuffix.Append(sfilename);
    }
    sfilename = "/c";
    sfilename.Prepend(gEnv->GetValue("Canvas.PrintDirectory",".")); // not the best way maybe...
    for (unsigned int iBit = 1; iBit < LmSignal::kMAXhist; iBit *= 2) {
      if ((iBit & histBits) && fType!=kCocktailOnly) sfilename.Append(GetReferenceSignal()->GetCharHistBit(iBit,kTRUE));
    }
    if (fType>kStd && !(fType==kCompare&&GetNSignals()<2)) // avoid to append "Compare" if only one signal is plotted. (but dont use GetNRequestedSig() to keep plots ordered)
      sfilename.Append(GetTypename());
    LmBaseSignal::inputAxis inputAx = LmBaseSignal::CheckWhichInputAxis( (TH1*) GetReferenceSignal()->GetLmHist(firstHist,bin_min,projOnMee)->GetDatahist() );
    sfilename.Append("_"+LmBaseSignal::GetInputAxisCode(inputAx)); // instead of hardcoded Append("_Mee") or Append("_Ptee").
    sfilename.Append(Form("%s_bin%d",ssuffix.Data(),bin_min));
    if (!fRequestedSignals.IsNull()) sfilename.Append(Form("_req%s",fRequestedSignals.Data()));
    sfilename.Append(Form(".%s", fFileType.Data()));
  }




  LmHelper::Debug(Form("  print canvas, called '%s' or '%s'", filename, sfilename.Data()), 12-printdebug); // @TODO: this is a really fancy bug! must be a memory leak somewhere.
  for(Int_t i = 0; i < 3; ++i) can->RedrawAxis();
  if (ownCan) {
    can->Print(sfilename.Data());
    //can->Destructor(); // @TODO: this crashes when doing phiV study with templates...
  } else {
    can->SetTitle(sfilename.Data()); // so that the name can be used for external printing.
  }
  if (rangeComputed) ResetPlotRangeY();
  return;
}





//_______________________________________________________________________________________________
void LmHandler::PrintCompareAll(unsigned int histBits, unsigned int bin_min, unsigned int bin_max, Bool_t projOnMee, const Char_t* filename, Bool_t printLegend, Bool_t setLogy, TCanvas* can, Bool_t printOnlyAverage)
{
  /// Generic plotting function.
  /// Plots requested histograms into canvas and prints canvas to file. Also plots legend + labels + ratio ... if requested.
  /// Modify the plotting ranges via SetPlotRangeMee()/Ptee(), SetPlotRangeY(), SetPlotRangeYMargins().
  /// If no y-range is given, it finds the optimum plotting range by internally calling ComputeOptimumPlotRangeY().
  ///
  /// NOTE: PrintCompare() works for all handler types and is sensitive to them. In case of a crash, check that
  ///       function GetReferenceSignal() returns the signal that you intend and change handler type if needed.
  ///
  /// In case of multiple cocktails, only for the last cocktail all contributions are drawn and added to the legend.
  /// For the other cocktails only their individual sum is drawn.
  /// The ratio is done w.r.t. the first cocktail's sum, and the sums of the other cocktails are compared to it.
  ///
  /// @param hitBits Bits of histogram types that shall be plotted into the same canvas (e.g. LmSignal::kUnlike+LmSignal::kBkg). the order has no effect.
  /// @param bin_number Projection bin to plot.
  /// @param projOnMee Plot x- or y-projections (set via LmBaseSignal::kProjOnMee or kProjOnPtee).
  /// @param filename If starting with '+', the filename is generated automatically, but the string after '+' is appended.
  /// @param can Option to provide canvas. The (generated) filename is set as the canvas title for external printing.

  // Bool_t ratioAxis = kFALSE; // not used anywhere
  Double_t sizefac=0.7;
  int printdebug=0;
  LmHelper::Debug(Form("LmHandler::PrintCompareAll()"), 5-printdebug);
  TString sfilename(filename); // because "const Char_t* filename" somehow gets modified by operations related to LmHistogram... (in case with cocktail)

  if (fType==kNoProcess) {
    LmHelper::Warning(Form("LmHandler::PrintCompare(): this LmHandler (fType=%i) is not ready for printing. Call Process(..) or specify type in constructor.", fType));
    return;
  }

  Bool_t ownCan=kFALSE;
  if (!can) {
    ownCan=kTRUE;
    can = new TCanvas("cCompareAll", "cCompareAll");
    can->Clear();
  }
  //can->SetFillStyle(0);
  //can->SetFrameFillStyle(0);
  can->cd()->SetLogy(setLogy);

  if (fDoRatio) {
    LmHelper::Debug(Form("  create ratio pad"), 10-printdebug);
    Double_t bottommargin = 0.09/fRatioPadSize;
    can->Divide(1,2);
    can->cd(1)->SetPad(0., fRatioPadSize, 1., 1.);  // top pad
    can->cd(1)->SetBottomMargin(0.001);
    //can->cd(1)->SetFillStyle(0);
    //can->cd(1)->SetFrameFillStyle(0);
    can->cd(2)->SetPad(0., 0., 1., fRatioPadSize);  // bottom pad
    can->cd(2)->SetTopMargin(0);
    can->cd(2)->SetBottomMargin(bottommargin); // for x-axis label
    //can->cd(2)->SetFillStyle(0);
    //can->cd(2)->SetFrameFillStyle(0);
    // move to upper pad and set log if requested.
    can->cd(1)->SetLogy(setLogy);
  }

  // don't use floats (LmHelper::kSmallDelta will not work)
  Double_t commonXmin=0., commonXmax=0.;
  Double_t commonYmin=0., commonYmax=0.;

  // store the common x-range
  if (projOnMee==LmBaseSignal::kProjOnMee) {
    if (fPlotXMeeMin>-1  && fPlotXMeeMax>0)  { commonXmin=fPlotXMeeMin;  commonXmax=fPlotXMeeMax;  }
  } else { // Ptee
    if (fPlotXPteeMin>-1 && fPlotXPteeMax>0) { commonXmin=fPlotXPteeMin; commonXmax=fPlotXPteeMax; }
  }

  // store the common y-range
  // determine the common y-axis range for all histograms, if it was not manually set to valid values.
  // in that case also apply the margins.
  Bool_t rangeComputed=kFALSE;
  if (fPlotYMin >= fPlotYMax) {
    ComputeOptimumPlotRangeY(histBits, bin_min, projOnMee, printOnlyAverage); // maybe one could just not call this function in case of printOnlyAverage=kTRUE...
    LmHelper::Debug(Form("  using computed range and margins: ymin = %.2e / %.2f,   ymax = %.2e * %.2f", fPlotYMin, fPlotYMarginBelowMin, fPlotYMax, fPlotYMarginAboveMax), 12-printdebug);
    commonYmin = (fPlotYMarginBelowMin!=0) ? fPlotYMin/fPlotYMarginBelowMin : 0;
    commonYmax = fPlotYMax*fPlotYMarginAboveMax;
    rangeComputed=kTRUE; //in the end the range has to be reset, otherwise next time it will take the old range.
  } else {
    commonYmin = fPlotYMin;
    commonYmax = fPlotYMax;
  }
  LmHelper::Debug(Form("  %s plotting range: ymin = %.2e,   ymax = %.2e", (rangeComputed)?"computed":"specified", commonYmin, commonYmax), 12-printdebug);

  unsigned int ihist=0;
  unsigned int reqHist[(int)TMath::Log2(LmSignal::kMAXhist)];
  unsigned int &firstHist=reqHist[0]; // reference, for better readability.
  //TH1D* hGray[(int)TMath::Log2(LmSignal::kMAXhist)]; // for additional legend entries if more than one histogram type (bit) will be drawn.

  std::cout << "Number of hists: " << (int)TMath::Log2(LmSignal::kMAXhist) << std::endl;

  for(Int_t bin_i = bin_min; bin_i<=bin_max; bin_i++){
    std::cout << "Start " << bin_i << std::endl;
    std::cout << bin_i << "   " << GetReferenceSignal() << "   "  << GetReferenceSignal()->GetMaxBinProj(projOnMee) << std::endl;
    if ((Int_t)bin_i > GetReferenceSignal()->GetMaxBinProj(projOnMee)) {
      LmHelper::Error(Form("LmHandler::PrintCompare(): projection bin number (%i) out of range (on axis '%i'). [%i=X-axis(Mee),%i=Y-axis(Ptee)]", bin_i, projOnMee, LmBaseSignal::kProjOnMee, LmBaseSignal::kProjOnPtee));
      return;
    }

    if ( (histBits & LmSignal::kRfactor) && GetLmSignalI(0)->GetLmBackground()->GetUseRfactorUnity() ) {
      LmHelper::Warning(Form("LmHandler::PrintCompare(): the 1D Rfactors are not created from the 2D Rfactor which uses a unity range! (never project ratios!)"));
    }

    //
    // Loop over the requested histograms to configure their styles and ranges etc. Drawing is done later.
    //
    for (unsigned int iBit = 1; iBit < LmSignal::kMAXhist; iBit *= 2) {
      if ( !(iBit & histBits) ) continue; // continue if current histogram was not requested.
      reqHist[ihist] = iBit; // store the bits of all requested histograms.

      //if (fCompareSignalsToAverage && fBest[0]>-1) {
      //  GetLmSignalI(fBest[0])->GetLmHist(iBit,bin_i,projOnMee)->SetLineWidth(3);
      //  GetLmSignalI(fBest[1])->GetLmHist(iBit,bin_i,projOnMee)->SetLineWidth(3);
      //  GetLmSignalI(fBest[2])->GetLmHist(iBit,bin_i,projOnMee)->SetLineWidth(3);
      //  GetLmSignalI(fBest[0])->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(2);
      //  GetLmSignalI(fBest[1])->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(5);
      //  GetLmSignalI(fBest[2])->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(7);
      //}

      Int_t Nsignals = GetNSignals();
      if (printOnlyAverage) Nsignals=1;
      // when plotting only the average, this loop is only used once to draw axes with the correct label sizes etc.
      // @TODO: better create a pointer which stores GetLmSignalI() or GetLmSigAverage(), otherwise - in case of
      //        'printOnlyAverage==kTRUE' - the first signal is modified without need.
      for (Int_t i = 0; i < Nsignals; ++i) {
        //if (!CheckRequestedSigI(i)) continue; // the gray markers become wrong if signal 0 was not requested.
        // reset modifications made on best signals, when drawn later with another handler
        if (i!=fBest[0]&&i!=fBest[1]&&i!=fBest[2]) {
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineWidth(1);
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(1);
        }
        // beautify histograms
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineColor(LmHelper::GetUniformColor(i, GetNSignals()));
        // GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->GetYaxis()->SetTitle("counts (arb. units)");

        if (fUseDifferentMarkers == kTRUE && Nsignals < 8){
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(LmHelper::GetMarker(i));
        }
        else GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(20);

        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(LmHelper::GetUniformColor(i, GetNSignals()));
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerSize(fMarkerSize);
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetFillStyle(0);
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(20);
        if (ihist>0) { // if more than one histogram type (bit) will be drawn, modify the following ones.
          //GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(ihist+1);
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(1);
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(20+bin_i);
          //GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(kGreen+2);
//          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(LmHelper::GetCompareMarker(ihist));
          if(iBit == LmSignal::kBkg){
            GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineColor(kBlue);
            GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(kBlue);
          }
          if(iBit == LmSignal::kUnlike){
            GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineColor(kRed);
            GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(kRed);
          }


          if (fLmSigAverage && iBit == LmSignal::kSubSig) { // average currently only available for SubSig.
            //GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(ihist+1);
            GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetLineStyle(1);
            GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetLineColor(kBlack);
            GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(LmHelper::GetCompareMarker(ihist));
            //GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(20);
            GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(kBlack);
          }
          //if(iBit == LmSignal::kSubSig){
          //  GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetLineColor(kBlack);
          //  GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(kBlack);
          //}
        }
        // Set label and title sizes. Update offsets for ratio plot.
        Double_t textSize = gStyle->GetTextSize();//*sizefac; //PRL
	std::cout << "textsize:" << textSize << "  " << gStyle->GetTextSize() << std::endl;

        if (fDoRatio) {
          //textSize /= (1.-fRatioPadSize);
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->GetXaxis()->SetTitleOffset(1.2);
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->GetYaxis()->SetTitleOffset(gStyle->GetTitleOffset("Y")*(1.-fRatioPadSize));
        }
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->GetDatahist()->SetTitleSize(textSize,"XY");
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->GetDatahist()->SetLabelSize(textSize,"XY");
        //
        // Set axis ranges
        // need to set identical ranges for all histograms, otherwise the arrows (for confidence levels) will be scaled bad (relative to full range).
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetAxisRange(commonXmin, commonXmax, "X");
        GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->SetAxisRange(commonYmin, commonYmax, "Y");
        //
        // Draw axes
        if ((iBit==firstHist) && (i==FirstReqSig()) && bin_i==bin_min) {
          GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->DrawCopy("axis");
        }
        //
        // Draw LmHistogram of each signal. This is done later, after the cocktail was possibly drawn.
        // ...
      } // Nsignals

      // create extra gray-colored histograms for additional legend entries.
      //hGray[ihist] = new TH1D( *(GetReferenceSignal()->GetLmHist(iBit,bin_i,projOnMee)->GetDatahist()) );
      //hGray[ihist]->SetTitle(GetReferenceSignal()->GetCharHistBit(iBit));
      //hGray[ihist]->SetLineColor(kGray+1);
      //hGray[ihist]->SetMarkerColor(kGray+1);
      ihist++;
    } // hist bit loop
    const unsigned int nHists = ihist;

    //
    // Printing of cocktail.
    //
    if (fCocktailProcessed) {
      // draw cocktail only if one of the signal histograms is plotted (otherwise it will be plotted also into S/B plots etc...)
      if (firstHist & (LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg) ) {
        // loop over all attached cocktails
        //for(UInt_t ic = 0; ic < fLmCocktails.size(); ++ic) {
        //  if(fLmCocktails.at(ic)->HasSystematics())
        //    fLmCocktails.at(ic)->GetSumErr1D(bin_i,projOnMee)->DrawClone(Form("%s same", fLmCocktails.at(ic)->GetDrawStyleErr())); // draw systematics if available.
        //  TObjArray* oaCocktail = fLmCocktails.at(ic)->GetSpectra1D(bin_i, projOnMee);
        //  for(Int_t i = 0; i < oaCocktail->GetEntries(); ++i) ((TH1D*) oaCocktail->At(i))->SetLineWidth(2);
        //  if (ic==fLmCocktails.size()-1) oaCocktail->DrawClone(Form("%s same", fLmCocktails.at(ic)->GetDrawStyle())); // draw all contributions only for the last cocktail.
        //  ((TH1D*) oaCocktail->At(0))->DrawClone(Form("%s same", fLmCocktails.at(ic)->GetDrawStyle())); // draw the sum again, looks nicer.
        //  delete oaCocktail;
        //}
        for(UInt_t ic = 0; ic < fLmCocktails.size(); ++ic) {
          // When drawing multiple cocktails, consider using their different draw options like kOnlySum or kAllButSum.
          // Specify them via cocktail->SetDrawOption(LmCocktail::kOnlySum);
          fLmCocktails.at(ic)->DrawProjection(bin_i,projOnMee);
          // if(fLmCocktails.at(ic)->HasSystematics())  //jerome edit
          //   fLmCocktails.at(ic)->GetSumErr1D(bin_i,projOnMee)->DrawClone(Form("%s same", "E3")); // draw systematics if available.
          // TObjArray* oaCocktail = fLmCocktails.at(ic)->GetSpectra1D(bin_i, projOnMee);
          // for(Int_t i = 0; i < oaCocktail->GetEntries(); ++i) ((TH1D*) oaCocktail->At(i))->SetLineWidth(2);
          // if (ic==fLmCocktails.size()-1) oaCocktail->DrawClone(Form("%s same", "hist c")); // draw all contributions only for the last cocktail.
          // ((TH1D*) oaCocktail->At(0))->DrawClone(Form("%s same", "hist c")); // draw the sum again, looks nicer.
          // delete oaCocktail;
        }
      }
    }

    //
    // Printing of datapoints of all signals which are desired according to the configuration of this handler.
    //
    for (unsigned int iBit = 1; iBit < LmSignal::kMAXhist; iBit *= 2) {
      if (fType==kCocktailOnly) break;
      if ( !(iBit & histBits) ) continue; // continue if current histogram was not requested.
      if (!printOnlyAverage) {
        // Draw LmHistogram of each signal. This contains datapoints, systematics graphs, external objects, arrows...
        for (Int_t i = 0; i < GetNSignals(); ++i)
          if (CheckRequestedSigI(i)) GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->DrawCopy();
          // if (CheckRequestedSigI(i)) GetLmSignalI(i)->GetLmHist(iBit,bin_i,projOnMee)->DrawCopy("p E same;p E2 same"); Jerome edit
        if (fType==kCombine && fLmSigCombined) {
          GetLmSigCombined()->GetLmHist(iBit,bin_i,projOnMee)->SetLineColor(kBlack);
          GetLmSigCombined()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(20);
          GetLmSigCombined()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(kBlack);
          GetLmSigCombined()->GetLmHist(iBit,bin_i,projOnMee)->SetFillStyle(0);
          GetLmSigCombined()->GetLmHist(iBit,bin_i,projOnMee)->SetAxisRange(commonXmin, commonXmax, "X");
          GetLmSigCombined()->GetLmHist(iBit,bin_i,projOnMee)->SetAxisRange(commonYmin, commonYmax, "Y");
          GetLmSigCombined()->GetLmHist(firstHist,bin_i,projOnMee)->DrawCopy();
          // GetLmSigCombined()->GetLmHist(firstHist,bin_i,projOnMee)->DrawCopy("p E same;p E2 same"); Jerome edit
        }
      }
      // The average may be desired to be drawn in quite a few cases:
      if ((fType==kAverage || fType==kWeightedAverage || fCompareSignalsToAverage || printOnlyAverage)
          && fLmSigAverage && iBit == LmSignal::kSubSig) { // Average currently only available for kSubSig
        GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetLineColor(kBlack);
        GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(20);
        GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerColor(kBlack);
        GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetFillStyle(0);
        if (fCompareSignalsToAverage) { // Distinguish the average from all other signals and even from the combined signal if also drawn.
          GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerSize(1.3);
          GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetMarkerStyle(21);
        }
        GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetAxisRange(commonXmin, commonXmax, "X");
        GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->SetAxisRange(commonYmin, commonYmax, "Y");
        GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->DrawCopy();
        // GetLmSigAverage()->GetLmHist(iBit,bin_i,projOnMee)->DrawCopy("p E same;p E2 same"); Jerome edit
      }
    }

    std::cout << "test2 " << bin_i << std::endl;
    // draw axes again, which may have been over-drawn by cocktail or other lines.
    // @TODO: not yet perfect, because the axis line is too narrow... fix it inside LmHistogram::Draw().
    GetReferenceSignal()->GetLmHist(firstHist,bin_i,projOnMee)->Draw("axis same");

    TObjArray* oaLabels = GenerateLabels();
    if (oaLabels) {
      FillLabels(oaLabels, bin_i, projOnMee);
      oaLabels->DrawClone("same");
      delete oaLabels;
    }
    std::cout << "test3 " << bin_i << std::endl;
    if (printLegend){
      TLegend* leg = GenerateLegend(bin_i, projOnMee, firstHist, nHists>1?nHists:0, printOnlyAverage);
      //if (nHists>1) { // add extra entries for the histogram bits (types) to the legend
      //  for (unsigned int ihist=0; ihist<nHists; ihist++) { leg->AddEntry(hGray[ihist], "", fLegendEntryDrawOption.Data()); } //hGray[ihist]->GetTitle()
      //}
      leg->DrawClone("same");
      delete leg;
    }
    if (fDoRatio) {
      can->cd(2)->SetLogy(fPlotRatioLogy); // somehow it crashes when done further above...
      const int Nratios = 10;
      TH1D* hDenominator = 0x0;
      TGraphAsymmErrors* grRatioCocktSys[Nratios];
      TString sYtitle;
      if (fCocktailProcessed) { // produce ratios relative to sum of first attached cocktail. //jerome edit for all cocktails
        LmHelper::Debug(Form("  produce ratios relative to sum of first attached cocktail."), 10-printdebug);
        for(Int_t i1=0; i1<fLmCocktails.size(); i1++){
          hDenominator = fLmCocktails.at(0)->GetSum1D(bin_i, projOnMee);
          sYtitle="Data/Cocktail";
          if(fLmCocktails.at(i1)->HasSystematics()){
            grRatioCocktSys[i1] = new TGraphAsymmErrors(*(fLmCocktails.at(i1)->GetSumErr1D(bin_i,projOnMee)));
            for(Int_t igr = 0; igr < grRatioCocktSys[i1]->GetN(); ++igr){
              Double_t xtmp,ytmp;
              grRatioCocktSys[i1]->SetFillColorAlpha(kGray+1,0.5);
              grRatioCocktSys[i1]->GetPoint(igr,xtmp,ytmp);
              if (ytmp == 0) ytmp = 1e-10; // check if denominator is zero
              grRatioCocktSys[i1]->SetPoint(igr,xtmp,1.);
              if (ytmp == 0) ytmp = 1e-10; // check if denominator is zero
              grRatioCocktSys[i1]->SetPointError(igr,grRatioCocktSys[i1]->GetErrorXlow(igr),grRatioCocktSys[i1]->GetErrorXhigh(igr),
                                                 grRatioCocktSys[i1]->GetErrorYlow(igr)/ytmp,grRatioCocktSys[i1]->GetErrorYhigh(igr)/ytmp);
            }
          }
        }
      }
      //else if (nHists==2) { // produce ratios between two histogram types (histbits).
      //  LmHelper::Debug(Form("  produce ratios between two histogram types (histbits)."), 10-printdebug);
      //  //hDenominator = ...; // must be set inside the for loop below...
      //  sYtitle=Form("%s/%s", LmSignal::GetCharHistBitStatic(reqHist[0]), LmSignal::GetCharHistBitStatic(reqHist[1]));
      //}
      else { // produce ratios relative to first input.
        LmHelper::Debug(Form("  produce ratios relative to first input."), 10-printdebug);
        hDenominator = GetLmSignalI(0)->GetLmHist(firstHist,bin_i,projOnMee)->GetDatahist();
        if (fRatioTitle == "") sYtitle="data/first input";
        else sYtitle = fRatioTitle;
      }
      TH1D* haxis = 0x0;
      for (Int_t i = 0; i < GetNSignals(); ++i) {
        if (printOnlyAverage) break; // ratio not implemented for average and combined signal. Use compare handler to do this...
        if (!CheckRequestedSigI(i)) continue;
        //if (nHists==2) { // produce ratios between two histogram types (histbits).
          //hDenominator = GetLmSignalI(i)->GetLmHist(reqHist[1],bin_i,projOnMee)->GetDatahist();
          hDenominator = GetLmSignalI(0)->GetLmHist(firstHist,bin_i,projOnMee)->GetDatahist();
       // }
        //
        // Perform division.
        // Done inside LmHistogram. Special cases like divide option 0 and incompatible binnings are handled there.
        // -----
        LmHistogram* ratioi = new LmHistogram( *(GetLmSignalI(i)->GetLmHist(firstHist,bin_i,projOnMee)) );
        ratioi->Divide(hDenominator,fDivideOption.Data());
        if(bin_i==0){
          ratioi->GetYaxis()->UnZoom();
          ratioi->GetYaxis()->SetTitle(sYtitle.Data());
          ratioi->GetYaxis()->CenterTitle();
          ratioi->GetYaxis()->SetTitleOffset(ratioi->GetYaxis()->GetTitleOffset()*fRatioPadSize/(1.-fRatioPadSize) * fRatioTitleOffset);
          ratioi->GetDatahist()->SetTitleSize(ratioi->GetDatahist()->GetTitleSize()/fRatioPadSize*(1.-fRatioPadSize) * fRatioTitleSize,"xy");
          ratioi->GetDatahist()->SetLabelSize(ratioi->GetDatahist()->GetLabelSize()/fRatioPadSize*(1.-fRatioPadSize),"xy");
          //if (fPlotRatioMax>0)

          ratioi->GetDatahist()->GetYaxis()->SetNdivisions(4, 5, 0, kTRUE); // 4,5,0 = 504

          std::cout << "min Ratio: " << fPlotRatioMin << "  max Ratio: " << fPlotRatioMax << std::endl;
          ratioi->SetAxisRange(fPlotRatioMin, fPlotRatioMax, "Y");
          ratioi->GetDatahist()->DrawCopy("axis");
          // ratioAxis = kTRUE; //was: ratioAxis == kTRUE; that makes no sense also was not used
        }
        // -----
        if (i==FirstReqSig()) { // instead of i==0

          //else ratioi->GetDatahist()->DrawCopy("same axis");
          haxis = new TH1D(*(ratioi->GetDatahist()));
          for (Int_t i2 =0; i2<fLmCocktails.size(); i2++){
            if(grRatioCocktSys[i2]) grRatioCocktSys[i2]->DrawClone(Form("same %s",GetDrawStyleCocktailErr()));
          }
          // line at unity
          TLine l1(ratioi->GetXaxis()->GetBinLowEdge(ratioi->GetXaxis()->GetFirst()), 1., ratioi->GetXaxis()->GetBinLowEdge(ratioi->GetXaxis()->GetLast()+1), 1.);
          l1.SetLineWidth(2);
          //if (fCocktailProcessed) {
          //  l1.SetLineColor(fLmCocktails.at(0)->GetSum1D(bin_i, projOnMee)->GetLineColor());
          //  l1.SetLineStyle(fLmCocktails.at(0)->GetSum1D(bin_i, projOnMee)->GetLineStyle());
          //  l1.SetLineWidth(fLmCocktails.at(0)->GetSum1D(bin_i, projOnMee)->GetLineWidth());
          //}
          l1.DrawClone();

          // Draw ratios of sums of additional cocktails. A bit dirty to do it inside the LmSignal loop, but easiest...
          //if (fCocktailProcessed) {
          //  for(UInt_t ic = 1; ic <fLmCocktails.size() ; ++ic) { //fLmCocktails.size()
          //  //if(ic==2) continue;
          //    LmHelper::Debug(Form("  produce ratios between two cocktails."), 10-printdebug);
          //    // It would be great to store spectra of LmCocktailPart as LmHistograms, then one could use a copy
  //      //      LmHistogram* cocktratioi = new LmHistogram( (TH1D*) fLmCocktails.at(ic)->GetSum1D(bin_i, projOnMee)->Clone("cocktratioi") );
  //      //      cocktratioi->Divide(hDenominator,fDivideOption.Data());
  //      //      cocktratioi->DrawCopy(Form("%s same", fLmCocktails.at(ic)->GetDrawStyle()));
  //      //      delete cocktratioi;
          //    TH1D* cocktratioi = (TH1D*) fLmCocktails.at(ic)->GetSum1D(bin_i, projOnMee)->Clone("cocktratioi");
          //    cocktratioi->Divide(cocktratioi,hDenominator,1,1,"0"); // divide option 0
          //    cocktratioi->DrawCopy(Form("%s same", fLmCocktails.at(ic)->GetDrawStyle()));
          //    TFile* file_ = TFile::Open("ratio_cock.root", "UPDATE");
          //    cocktratioi->Write(Form("%s_%i","cocktratioi", bin_i ));
          //    //ratioi->GetSystError()->Write();
          //    file_->Close();
          //    delete file_;
          //    delete cocktratioi;
          //  }
          //}
        }
        if(!fCocktailProcessed && nHists==1 && i==FirstReqSig()) { // first ratio histogram in case of no cocktail and no histbit comparison
          ratioi->DrawCopy("same onlysys"); // or draw only its systematics?
        }
        else { // draw all other ratio histograms
          if (fType!=kCocktailOnly){
            //ratioi->DrawCopy("p hist same");
            //if(bin_i == 1)
            ratioi->DrawCopy("same");
            std::cout << "plotting raios" << std::endl;
            TFile* file_ = TFile::Open("ratio_3.root", "UPDATE");
            ratioi->GetDatahist()->Write(Form("%s_%i",ratioi->GetDatahist()->GetName(), i ));
            //ratioi->GetSystError()->Write();
            file_->Close();
            delete file_;

          }
          // if (fType!=kCocktailOnly) ratioi->DrawCopy("p E same;p E2 same"); Jerome edit
        }
        delete ratioi;
      } // NSignals
      haxis->DrawCopy("axis same"); // draw axes again.
      delete haxis;
    } // doRatio

    can->cd(1);
    std::cout << "End " << bin_i << std::endl;

  }





  // construct filename of plot
  if (sfilename.IsNull()||sfilename.BeginsWith('+')) {
    TString ssuffix = "";
    if (sfilename.BeginsWith('+')) {
      sfilename.Remove(0,1);
      ssuffix.Append(sfilename);
    }
    sfilename = "/c";
    sfilename.Prepend(gEnv->GetValue("Canvas.PrintDirectory",".")); // not the best way maybe...
    for (unsigned int iBit = 1; iBit < LmSignal::kMAXhist; iBit *= 2) {
      if ((iBit & histBits) && fType!=kCocktailOnly) sfilename.Append(GetReferenceSignal()->GetCharHistBit(iBit,kTRUE));
    }
    if (fType>kStd && !(fType==kCompare&&GetNSignals()<2)) // avoid to append "Compare" if only one signal is plotted. (but dont use GetNRequestedSig() to keep plots ordered)
      sfilename.Append(GetTypename());
    LmBaseSignal::inputAxis inputAx = LmBaseSignal::CheckWhichInputAxis( (TH1*) GetReferenceSignal()->GetLmHist(firstHist,bin_min,projOnMee)->GetDatahist() );
    sfilename.Append("_"+LmBaseSignal::GetInputAxisCode(inputAx)); // instead of hardcoded Append("_Mee") or Append("_Ptee").
    sfilename.Append(Form("%s_bin%d",ssuffix.Data(),bin_min));
    if (!fRequestedSignals.IsNull()) sfilename.Append(Form("_req%s",fRequestedSignals.Data()));
    sfilename.Append(Form(".%s", fFileType.Data()));
  }




  LmHelper::Debug(Form("  print canvas, called '%s' or '%s'", filename, sfilename.Data()), 12-printdebug); // @TODO: this is a really fancy bug! must be a memory leak somewhere.
  for(Int_t i = 0; i < 3; ++i) can->RedrawAxis();
  if (ownCan) {
    can->Print(sfilename.Data());
    //can->Destructor(); // @TODO: this crashes when doing phiV study with templates...
  } else {
    can->SetTitle(sfilename.Data()); // so that the name can be used for external printing.
  }
  if (rangeComputed) ResetPlotRangeY();
  return;
}



//_______________________________________________________________________________________________
void LmHandler::PrintCompareSig_Mee(unsigned int bin_number, Bool_t printLegend, const Char_t* filename, Double_t marginMin, Double_t marginMax)
{
  Double_t origMarginMin=fPlotYMarginBelowMin; // make sure we don't mess up the users individual settings
  Double_t origMarginMax=fPlotYMarginAboveMax;
  fPlotYMarginBelowMin=marginMin;
  fPlotYMarginAboveMax=marginMax;
  PrintCompare(LmSignal::kSubSig, bin_number, LmBaseSignal::kProjOnMee, filename, printLegend);
  fPlotYMarginBelowMin=origMarginMin;
  fPlotYMarginAboveMax=origMarginMax;
}
//_______________________________________________________________________________________________
void LmHandler::PrintCompareSig_Ptee(unsigned int bin_number, Bool_t printLegend, const Char_t* filename, Double_t marginMin, Double_t marginMax)
{
  Double_t origMarginMin=fPlotYMarginBelowMin; // make sure we don't mess up the users individual settings
  Double_t origMarginMax=fPlotYMarginAboveMax;
  fPlotYMarginBelowMin=marginMin;
  fPlotYMarginAboveMax=marginMax;
  PrintCompare(LmSignal::kSubSig, bin_number, LmBaseSignal::kProjOnPtee, filename, printLegend);
  fPlotYMarginBelowMin=origMarginMin;
  fPlotYMarginAboveMax=origMarginMax;
}


//_______________________________________________________________________________________________
void LmHandler::PrintCompareSoverB_Mee(unsigned int bin_number, Bool_t printLegend, const Char_t* filename, Double_t marginMin, Double_t marginMax)
{
  Double_t origMarginMin=fPlotYMarginBelowMin; // make sure we don't mess up the users individual settings
  Double_t origMarginMax=fPlotYMarginAboveMax;
  fPlotYMarginBelowMin=marginMin;
  fPlotYMarginAboveMax=marginMax;
  PrintCompare(LmSignal::kSoverB, bin_number, LmBaseSignal::kProjOnMee, filename, printLegend);
  fPlotYMarginBelowMin=origMarginMin;
  fPlotYMarginAboveMax=origMarginMax;
}
//_______________________________________________________________________________________________
void LmHandler::PrintCompareSoverB_Ptee(unsigned int bin_number, Bool_t printLegend, const Char_t* filename, Double_t marginMin, Double_t marginMax)
{
  Double_t origMarginMin=fPlotYMarginBelowMin; // make sure we don't mess up the users individual settings
  Double_t origMarginMax=fPlotYMarginAboveMax;
  fPlotYMarginBelowMin=marginMin;
  fPlotYMarginAboveMax=marginMax;
  PrintCompare(LmSignal::kSoverB, bin_number, LmBaseSignal::kProjOnPtee, filename, printLegend);
  fPlotYMarginBelowMin=origMarginMin;
  fPlotYMarginAboveMax=origMarginMax;
}


//_______________________________________________________________________________________________
void LmHandler::PrintCompareSignif_Mee(unsigned int bin_number, Bool_t printLegend, const Char_t* filename, Double_t marginMin, Double_t marginMax)
{
  Double_t origMarginMin=fPlotYMarginBelowMin; // make sure we don't mess up the users individual settings
  Double_t origMarginMax=fPlotYMarginAboveMax;
  fPlotYMarginBelowMin=marginMin;
  fPlotYMarginAboveMax=marginMax;
  PrintCompare(LmSignal::kSignif, bin_number, LmBaseSignal::kProjOnMee, filename, printLegend);
  fPlotYMarginBelowMin=origMarginMin;
  fPlotYMarginAboveMax=origMarginMax;
}
//_______________________________________________________________________________________________
void LmHandler::PrintCompareSignif_Ptee(unsigned int bin_number, Bool_t printLegend, const Char_t* filename, Double_t marginMin, Double_t marginMax)
{
  Double_t origMarginMin=fPlotYMarginBelowMin; // make sure we don't mess up the users individual settings
  Double_t origMarginMax=fPlotYMarginAboveMax;
  fPlotYMarginBelowMin=marginMin;
  fPlotYMarginAboveMax=marginMax;
  PrintCompare(LmSignal::kSignif, bin_number, LmBaseSignal::kProjOnPtee, filename, printLegend);
  fPlotYMarginBelowMin=origMarginMin;
  fPlotYMarginAboveMax=origMarginMax;
}


//_______________________________________________________________________________________________
void LmHandler::PrintCompareSigBkg_Mee(unsigned int bin_number, Bool_t printLegend, const Char_t* filename, Double_t marginMin, Double_t marginMax)
{
  Double_t origMarginMin=fPlotYMarginBelowMin; // make sure we don't mess up the users individual settings
  Double_t origMarginMax=fPlotYMarginAboveMax;
  fPlotYMarginBelowMin=marginMin;
  fPlotYMarginAboveMax=marginMax;
  PrintCompare(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, bin_number, LmBaseSignal::kProjOnMee, filename, printLegend);
  fPlotYMarginBelowMin=origMarginMin;
  fPlotYMarginAboveMax=origMarginMax;
}
//_______________________________________________________________________________________________
void LmHandler::PrintCompareSigBkg_Ptee(unsigned int bin_number, Bool_t printLegend, const Char_t* filename, Double_t marginMin, Double_t marginMax)
{
  Double_t origMarginMin=fPlotYMarginBelowMin; // make sure we don't mess up the users individual settings
  Double_t origMarginMax=fPlotYMarginAboveMax;
  fPlotYMarginBelowMin=marginMin;
  fPlotYMarginAboveMax=marginMax;
  PrintCompare(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, bin_number, LmBaseSignal::kProjOnPtee, filename, printLegend);
  fPlotYMarginBelowMin=origMarginMin;
  fPlotYMarginAboveMax=origMarginMax;
}


//_______________________________________________________________________________________________
void LmHandler::PrintCompareRfactor_Mee(unsigned int bin_number, Bool_t printLegend, const Char_t* filename, Double_t yMin, Double_t yMax)
{
  /// This function temporarily sets the handler type to kCompare, because GetReferenceSignal() inside PrintCompare()
  /// may otherwise return a LmSignal which does not have an Rfactor stored (combined or average signal).
  ///
  /// NOTE: The 1D Rfactors are not created from the 2D Rfactor which may use a unity range! (never project ratios!)
  Int_t origType=fType; // make sure we don't mess up the users individual settings
  fType=kCompare;
  Double_t origMarginMin=fPlotYMarginBelowMin; // make sure we don't mess up the users individual settings
  Double_t origMarginMax=fPlotYMarginAboveMax;
  fPlotYMarginBelowMin=1.;
  fPlotYMarginAboveMax=1.;
  Double_t origYMin=fPlotYMin; // make sure we don't mess up the users individual settings
  Double_t origYMax=fPlotYMax;
  SetPlotRangeY(yMin, yMax);
  PrintCompare(LmSignal::kRfactor, bin_number, LmBaseSignal::kProjOnMee, filename, printLegend, kFALSE);
  // Restore handler to original settings:
  fType=origType;
  fPlotYMarginBelowMin=origMarginMin;
  fPlotYMarginAboveMax=origMarginMax;
  SetPlotRangeY(origYMin, origYMax);
}
//_______________________________________________________________________________________________
void LmHandler::PrintCompareRfactor_Ptee(unsigned int bin_number, Bool_t printLegend, const Char_t* filename, Double_t yMin, Double_t yMax)
{
  /// This function temporarily sets the handler type to kCompare, because GetReferenceSignal() inside PrintCompare()
  /// may otherwise return a LmSignal which does not have an Rfactor stored (combined or average signal).
  ///
  /// NOTE: The 1D Rfactors are not created from the 2D Rfactor which may use a unity range! (never project ratios!)
  Int_t origType=fType; // make sure we don't mess up the users individual settings
  fType=kCompare;
  Double_t origMarginMin=fPlotYMarginBelowMin; // make sure we don't mess up the users individual settings
  Double_t origMarginMax=fPlotYMarginAboveMax;
  fPlotYMarginBelowMin=1.;
  fPlotYMarginAboveMax=1.;
  Double_t origYMin=fPlotYMin; // make sure we don't mess up the users individual settings
  Double_t origYMax=fPlotYMax;
  SetPlotRangeY(yMin, yMax);
  PrintCompare(LmSignal::kRfactor, bin_number, LmBaseSignal::kProjOnPtee, filename, printLegend, kFALSE);
  // Restore handler to original settings:
  fType=origType;
  fPlotYMarginBelowMin=origMarginMin;
  fPlotYMarginAboveMax=origMarginMax;
  SetPlotRangeY(origYMin, origYMax);
}

//_______________________________________________________________________________________________
TObjArray* LmHandler::GenerateLabels(Bool_t forCorrelPlot)
{
  /// Generates the labels on the plots.
  /// Default labels are: figure caption / collision system, energy, centrality / kinematic cuts / 2D-proj. range.
  /// Customize the labels by specifying a TObjArray with TLatex (or other) objects via SetLabels().
  /// Optionally modify them according to their names by adding more rules in FillLabels().
  ///
  /// @return empty TObjArray* which should be given to FillLabels() afterwards.

  LmHelper::Debug(Form(" GenerateLabels()"), 5-debugHandler);

  Double_t eta_min=-0.8, eta_max=0.8;
  Double_t pt_min =0., pt_max =0.;
  Double_t cent_min=-1., cent_max=-1.;
  TString  coll_system="", coll_energy="";
  Double_t thetaEEcut_min=0.;
  if (GetReferenceSignal()->GetManager()) {
   // eta_min  = GetReferenceSignal()->GetManager()->GetEtaRange_min();
   // eta_max  = GetReferenceSignal()->GetManager()->GetEtaRange_max();
    //cout << "Eta-range  = " << eta_min << " to " << eta_max << endl;
    pt_min   = GetReferenceSignal()->GetManager()->GetPtRange_min();
    if(pt_min<0.2)
      pt_min = 0.075;
    pt_max   = GetReferenceSignal()->GetManager()->GetPtRange_max();
    cout << "Pt-range  = " << pt_min << " to " << pt_max << " GeV/c" << endl;
    //cent_min = GetReferenceSignal()->GetManager()->GetCentrality_min();
    //cent_max = GetReferenceSignal()->GetManager()->GetCentrality_max();
    //cent_min = 0;
    //cent_max = 20;
    coll_system = GetReferenceSignal()->GetManager()->GetCollSystem();
    coll_energy = GetReferenceSignal()->GetManager()->GetCollEnergy();
    thetaEEcut_min = GetReferenceSignal()->GetManager()->GetThetaEEmin();
  }
  // Double_t sizefac = 0.7 * fLabelsSize;
  // Double_t xref = 0.575;
  // if (fDoRatio) sizefac = sizefac/(1.-fRatioPadSize);
  // if (thetaEEcut_min > 0.) xref = 0.525;
  Double_t sizefac = 0.7;
  Double_t xref = 0.20; //0.575 //0.20
  Double_t yref = 0.82;
  Double_t yoff = 0.06*sizefac;

  ////PRL mee wide
  //Double_t sizefac = 1.0;
  //Double_t xref = 0.165; //0.575 //0.20
  //Double_t yref = 0.87;
  //Double_t yoff = 0.06*sizefac;

  //PRL ptee wide
  //Double_t sizefac = .80;
  //Double_t xref = 0.165; //0.575 //0.20
  //Double_t yref = 0.87;
  //Double_t yoff = 0.06*sizefac;

  //PRL mee height
//  Double_t sizefac = .70;
//  //Double_t xref = 0.2-0.04; //0.575 //0.20
//  Double_t xref = 0.2+0.03; //0.575 //0.20
//  Double_t yref = 0.87;
//  Double_t yoff = 0.08*sizefac;






  if(fDoRatio){
    sizefac = sizefac/(1.-fRatioPadSize);
    yoff    = yoff/(1.-fRatioPadSize);
  }
  //if(thetaEEcut_min > 0.)  xref = 0.525;
  if(thetaEEcut_min > 0.)  xref = 0.5;
  if(fType==kCocktailOnly) yref += yoff+0.01; // will not draw 'latFigType'.

  TObjArray* obj_array = 0x0;
  if (fLabels) {
    if (fLabels->GetEntriesFast()==0) {
      LmHelper::Debug(Form("  Empty labels array given. Skip generating labels."), 8-debugHandler);
      return 0x0;
    }
    LmHelper::Debug(Form("  Using custom labels."), 8-debugHandler);
    obj_array = (TObjArray*) fLabels->Clone(); // deep copy.
    obj_array->SetOwner(kTRUE); // to be sure.
  }
  else {
    // by default, a new labels array is created each time this function is called.
    LmHelper::Debug(Form("  Creating default labels."), 8-debugHandler);
    if (forCorrelPlot) {
      obj_array = LmHelper::GetLabelsTemplate(LmHelper::kDefaultCorrel);
    }
    else if (fType==kCocktailOnly) { // please provide manager, otherwise some labels stay empty, making the cocktail plot ambiguous.
      obj_array = LmHelper::GetLabelsTemplate(LmHelper::kDefaultOnlyCocktail, sizefac, xref);
    }
//    else if (GetReferenceSignal()->GetManager()) { // default.
//      obj_array = LmHelper::GetLabelsTemplate(LmHelper::kDefault, sizefac, xref + fLabelsOffsetX, 0.82 + fLabelsOffsetY/*historic default, see lmhelper*/);
//    }
//    else { // no labels for which a manager is needed.
//      obj_array = LmHelper::GetLabelsTemplate(LmHelper::kDefaultNoManager, sizefac, xref + fLabelsOffsetX, 0.82 + fLabelsOffsetY/*historic default, see lmhelper*/);
//
    else if (GetReferenceSignal()->GetManager()) { // default.
      obj_array = LmHelper::GetLabelsTemplate(LmHelper::kDefault, sizefac, xref + fLabelsOffsetX, yref + fLabelsOffsetY/*historic default, see lmhelper*/);
    }
    else { // no labels for which a manager is needed.
      obj_array = LmHelper::GetLabelsTemplate(LmHelper::kDefaultNoManager, sizefac, xref + fLabelsOffsetX, yref + fLabelsOffsetY/*historic default, see lmhelper*/);

    }
  }

  return obj_array;
}

//_______________________________________________________________________________________________
TObjArray* LmHandler::FillLabels(TObjArray* obj_array, unsigned int bin_number, Bool_t projOnMee, Int_t bin_number_2, Bool_t updateLabels)
{
  /// Fills the labels of the given TObjArray with the requested values from this handler and returns the array.
  /// Optionally modify the labels according to their names by adding more rules in the sourcecode.
  ///
  /// @param bin_number Projection bin which is plotted
  /// @param projOnMee Plot x- or y-projections (set via LmBaseSignal::kProjOnMee or kProjOnPtee)
  /// @param bin_number_2 Bin of the other dimension in case both projection ranges shall be filled (e.g. for correlation plot).
  /// @param updateLabels Specify if labels which are not empty shall be updated (default=true).
  ///
  /// @return TObjArray* which can be drawn to canvas

  LmHelper::Debug(Form(" FillLabels(bin=%i, proj=%s, bin2=%i)", bin_number, (projOnMee)?"OnX":"OnY", bin_number_2), 5-debugHandler);

  if (!obj_array) { LmHelper::Warning(Form("FillLabels(): no TObjArray specified, skip filling labels.")); return 0x0; }

  Double_t eta_min=0., eta_max=0.;
  Double_t pt_min =0., pt_max =0.;
  Double_t cent_min=-1., cent_max=-1.;
  TString  coll_system="", coll_energy="";
  Double_t thetaEEcut_min=0.;
  if (GetReferenceSignal()->GetManager()) {
    eta_min  = GetReferenceSignal()->GetManager()->GetEtaRange_min();
    eta_max  = GetReferenceSignal()->GetManager()->GetEtaRange_max();
    //cout << "Eta-range  = " << eta_min << " to " << eta_max << endl;
    pt_min   = GetReferenceSignal()->GetManager()->GetPtRange_min();
    pt_max   = GetReferenceSignal()->GetManager()->GetPtRange_max();
    //cout << "Pt-range  = " << pt_min << " to " << pt_max << " GeV/c" << endl;
    //cent_min = GetReferenceSignal()->GetManager()->GetCentrality_min();  //jerome edit //preliminary
    //cent_max = GetReferenceSignal()->GetManager()->GetCentrality_max();
    //cent_min = 0;
    //cent_max = 20;
    coll_system = GetReferenceSignal()->GetManager()->GetCollSystem();
    coll_energy = GetReferenceSignal()->GetManager()->GetCollEnergy();
    thetaEEcut_min = GetReferenceSignal()->GetManager()->GetThetaEEmin();
  }

  if (fType==kCompare && GetNSignals()>1){
    LmHelper::Info("LmHandler::FillLabels(): note: the plotted ranges of #it{p}_{T}^{e}, #it{#eta}_{e} (and centrality) refer to first drawn spectrum!");
  }

  TString sCollsyst("");
  if (cent_min == -1 || cent_max == -1) sCollsyst = Form("%s, %s", coll_system.Data(), coll_energy.Data());
  else sCollsyst = Form("%1.0f#minus %2.0f%% %s %s", cent_min, cent_max, coll_system.Data(), coll_energy.Data());
  // else sCollsyst = Form("%s %s %2.0f-%2.0f%%", coll_system.Data(), coll_energy.Data(), cent_min, cent_max);

  TString ptrange(""), etarange(""), thetaEEcut("");
  if (pt_max > 0.) {
    if (pt_min < 0.150)  ptrange = Form("%.3f < #it{p}_{T,e} < %.0f GeV/#it{c}", 0.075, pt_max);
    else              ptrange = Form("%.3f < #it{p}_{T,e} < %.0f GeV/#it{c}", pt_min, pt_max);
  }
  else             ptrange = Form("#it{p}_{T,e} > %.3f GeV/#it{c}", pt_min);
  //if (TMath::Abs(eta_min+eta_max)<1e-4) etarange = Form(", |#it{#eta}^{e}| < %.2f", eta_max);
  //else                                  etarange = Form(", %.2f < #it{#eta}^{e} < %.2f", eta_min, eta_max);
  //etarange = Form(", |#it{#eta}_{e}| < %.1f", 0.8);
etarange = Form("|#it{#eta}_{e}| < %.1f, ", 0.8);

  if (thetaEEcut_min > 0.) thetaEEcut = Form(", #theta_{ee} > %3.2f#circ", thetaEEcut_min * 180./TMath::Pi());

  // get the projection range (for default dimensions, this is ptee).
  Double_t proj_min=-1, proj_max=-1;
  GetProjRange(bin_number, projOnMee, proj_min, proj_max);
  TString pairptrange("");
  if ( CheckPlottingDefaultDimensions()
      && (proj_min < 1.*pt_min) ) { // modify printout if the lower bound lies within the acceptance hole, because this could be misleading!
    if (projOnMee==LmBaseSignal::kProjOnMee) // in case of Mee: do not print lower bound
      //pairptrange = Form("%s < %.0f %s",LmBaseSignal::GetProjLabelYvar().Data(),proj_max,LmBaseSignal::GetProjLabelYunit().Data());
      pairptrange = Form("%s < %.2g %s",LmBaseSignal::GetProjLabelYvar().Data(),proj_max,LmBaseSignal::GetProjLabelYunit().Data());
    else // in case of Ptee: anyway print lower bound (because we will have multiple bins at low Mee), but attach a notice!
      //pairptrange = Form("%.2f #leq %s #leq %.2f %s (#minus acc.hole)",proj_min,LmBaseSignal::GetProjLabelXvar().Data(),proj_max,LmBaseSignal::GetProjLabelXunit().Data());
      //pairptrange = Form("%.2f < %s < %.2f %s",proj_min,LmBaseSignal::GetProjLabelXvar().Data(),proj_max,LmBaseSignal::GetProjLabelXunit().Data());
      pairptrange = Form("%.2g < %s < %.2g %s",proj_min,LmBaseSignal::GetProjLabelXvar().Data(),proj_max,LmBaseSignal::GetProjLabelXunit().Data());

  }
  else { // print both lower and upper projection limit.
    if (projOnMee==LmBaseSignal::kProjOnMee) pairptrange = Form("%.2g < %s < %.2g %s",proj_min,LmBaseSignal::GetProjLabelYvar().Data(),proj_max,LmBaseSignal::GetProjLabelYunit().Data());
    else                                     pairptrange = Form("%.2g < %s < %.2g %s",proj_min,LmBaseSignal::GetProjLabelXvar().Data(),proj_max,LmBaseSignal::GetProjLabelXunit().Data());
  }

  //  if (projOnMee==LmBaseSignal::kProjOnMee) pairptrange = Form("%.0d%.4g #leq %s #leq %.0f%.4g %s",(int)proj_min/10, proj_min-((int)proj_min-(int)proj_min%10),LmBaseSignal::GetProjLabelYvar().Data(),(int)proj_max/10, proj_max-((int)proj_max-(int)proj_max%10),LmBaseSignal::GetProjLabelYunit().Data());
  //  else                                     pairptrange = Form("%.0d%.4g #leq %s #leq %.0f%.4g %s",(int)proj_min/10, proj_min-((int)proj_min-(int)proj_min%10),LmBaseSignal::GetProjLabelXvar().Data(),(int)proj_max/10, proj_max-((int)proj_max-(int)proj_max%10),LmBaseSignal::GetProjLabelXunit().Data());

  // this is needed for the correlation plot.
  // get the selected range along the x-dimension itself (for default dimensions, this is mee).
  Double_t x_min=-1, x_max=-1;
  TString meerange(""); // do not care about acceptance hole stuff here...
  if (bin_number_2 > -1) {
    GetProjRange(bin_number_2, !projOnMee, x_min, x_max);
    if (projOnMee==LmBaseSignal::kProjOnPtee) meerange = Form("%.2g #leq %s #leq %.2g %s",x_min,LmBaseSignal::GetProjLabelYvar().Data(),x_max,LmBaseSignal::GetProjLabelYunit().Data());
    else                                      meerange = Form("%.2g #leq %s #leq %.2g %s",x_min,LmBaseSignal::GetProjLabelXvar().Data(),x_max,LmBaseSignal::GetProjLabelXunit().Data());
  }

  ///
  /// Modify some of the given objects depending on their name, e.g. if their title is empty.
  ///
  for (int i=0; i<obj_array->GetEntriesFast(); ++i) {
    //obj_array->At(i)->Dump();
    TObject* iLabel = obj_array->At(i);
    if (iLabel->IsA() == TLatex::Class()
        && ( TString(iLabel->GetTitle()).IsNull() || updateLabels) ) {
      LmHelper::Debug(Form("  Found TLatex named '%s'.", iLabel->GetName()), 8-debugHandler);
      //if (TString(iLabel->GetName()).EqualTo("latFigType"))  ((TLatex*) iLabel)->SetTitle(sFigType.Data()); // done in LmHelper::GetLabelsTemplate().
      if (TString(iLabel->GetName()).EqualTo("latCollsyst")) ((TLatex*) iLabel)->SetTitle(sCollsyst.Data());
      if (!(GetReferenceSignal()->GetDoAcceCorr())){
        //if (TString(iLabel->GetName()).EqualTo("latCutsEle"))  ((TLatex*) iLabel)->SetTitle(Form("%s%s%s", ptrange.Data(), etarange.Data(), thetaEEcut.Data()));
        if (TString(iLabel->GetName()).EqualTo("latCutsEle"))  ((TLatex*) iLabel)->SetTitle(Form("%s%s", ptrange.Data(), thetaEEcut.Data()));

      }
      if (TString(iLabel->GetName()).EqualTo("latCuts1Dim")) ((TLatex*) iLabel)->SetTitle(Form("%s%s", etarange.Data(), meerange.Data())); // for correlation plot
      if (TString(iLabel->GetName()).EqualTo("latCuts2Dim")) ((TLatex*) iLabel)->SetTitle(Form("%s%s", etarange.Data(), pairptrange.Data()));
      //if (TString(iLabel->GetName()).EqualTo("latCuts1Dim")) ((TLatex*) iLabel)->SetTitle(meerange.Data()); // for correlation plot
      //if (TString(iLabel->GetName()).EqualTo("latCuts2Dim")) ((TLatex*) iLabel)->SetTitle(pairptrange.Data());

 //     if (TString(iLabel->GetName()).EqualTo("latCuts3Dim")
 //         && GetReferenceSignal()->GetManager())             ((TLatex*) iLabel)->SetTitle(GetReferenceSignal()->GetManager()->GetAll3DProjRanges().Data());
    } // TLatex with empty title
  }
  // or with iterator: TIter nextLabel(obj_array->MakeIterator());  TObject* iLabel=0x0;  while ((iLabel=nextLabel())) { }

  return obj_array;
}

//_______________________________________________________________________________________________
TLegend* LmHandler::GenerateLegend(unsigned int bin_number, Bool_t projOnMee, unsigned int histBit, Int_t nExtraEntries, Bool_t printOnlyAverage)
{
  /// Generates a legend for the histograms on the plot. Names come from given name of AttachSignal() or SetLmSignalName().
  /// Customize the legend by specifying a filled or empty legend (e.g. to change its position) via SetLegend().
  /// Also adds the contributions of a cocktail. If multiple cocktails are attached, it only uses the last one.
  /// @param bin_number Projection bin which is plotted
  /// @param projOnMee Plot x- or y-projections (set via LmBaseSignal::kProjOnMee or kProjOnPtee)
  /// @param histBit Bit of histogram type which is drawn, default 'LmSignal::kSubSig'
  /// @return TLegend* which can be drawn to canvas

  LmHelper::Debug(" GenerateLegend()", 5-debugHandler);
  Int_t number_of_entries = GetNRequestedSig() + nExtraEntries;
  if (printOnlyAverage)     number_of_entries  = 1 + nExtraEntries;
  if (fCocktailProcessed)   number_of_entries += fLmCocktails.back()->GetPartNames().size(); // add space for number of cocktail particles
  if (fType==kCocktailOnly) number_of_entries -= GetNRequestedSig();
  //Double_t sizefac=0.7 * fLegendSize;
  //Double_t ylow=0.77 / fLegendSizeInYScaling + fLegendOffsetY, yup=0.87 + fLegendOffsetY;
  //Double_t xup=0.78;// + fLegendOffsetX;
  //Double_t xlow=0.57;// + fLegendOffsetX;

  //correlation plot
  Double_t sizefac=0.7 * fLegendSize;
  Double_t ylow=0.17 / fLegendSizeInYScaling + fLegendOffsetY, yup=0.27 + fLegendOffsetY;
  Double_t xup=0.78;// + fLegendOffsetX;
  Double_t xlow=0.57;// + fLegendOffsetX;



  //PRL wide
  //Double_t sizefac=1.8 * fLegendSize;
  //Double_t ylow=0.77 / fLegendSizeInYScaling + fLegendOffsetY, yup=0.92 + fLegendOffsetY;
  //Double_t xup=0.77;// + fLegendOffsetX;
  //Double_t xlow=0.57;// + fLegendOffsetX;

  //PRL height
  //Double_t sizefac=0.5 * fLegendSize;
  //Double_t ylow=0.7 / fLegendSizeInYScaling + fLegendOffsetY, yup=0.93 + fLegendOffsetY; //0.93
  //Double_t xup=0.7+0.06;//+0.06;//-0.12;//0.77 + fLegendOffsetX;
  //Double_t xlow=0.17+0.06;//+0.06;//-0.12;// + fLegendOffsetX;

  gStyle->SetErrorX(0);
  gStyle->SetEndErrorSize(0);



  //if (fType==kCompare) xup = 0.55;
  if      (number_of_entries<= 4) ylow=yup-0.035*number_of_entries * fLegendSizeInYScaling;
  //else if (number_of_entries<= 8) ylow=yup-0.025*number_of_entries * fLegendSizeInYScaling;
  //else if (number_of_entries<= 8) ylow=yup-0.035*number_of_entries * fLegendSizeInYScaling; //PRL weight
  else if (number_of_entries<= 8) ylow=yup-0.025*number_of_entries * fLegendSizeInYScaling; //PRL height

  else if (number_of_entries<= 12) ylow=yup-0.025*(number_of_entries) * fLegendSizeInYScaling;
  else {
    ylow=yup-0.020*12; // use largest case
    sizefac=0.4;
    //LmHelper::Warning("LmHandler::GenerateLegend(): Too many Histograms to plot reasonably.");
  }
  if (fDoRatio) {
    ylow = ylow*(1.-fRatioPadSize/2.); // the "/2." is a compromise...
    sizefac = sizefac/(1.-fRatioPadSize);
  }
  Double_t ydiff = yup-ylow; // needed for custom legends.

  TLegend* leg = 0x0;
  if (fLegend) leg = new TLegend(*fLegend);

  // 3 cases:
  if (!leg) {
    // by default, a new legend is created each time this function is called.
    leg = new TLegend(xlow, yup-ydiff, xup, yup);
    leg->SetFillStyle(0);
    //leg->SetTextSize(gStyle->GetTitleSize()*sizefac);
    leg->SetTextSize(gStyle->GetTextSize()/**sizefac*/); //PRL
    leg->SetTextFont(gStyle->GetTextFont()/**sizefac*/); //PRL
    leg->SetMargin(leg->GetMargin() * fLegendLineSizeFactor);
    leg->SetMargin(0.15);//0.15 // or some other value)
  }

  else {
    leg->SetMargin(leg->GetMargin() * fLegendLineSizeFactor);

    // check if a complete legend is already specified.
    if (   (!leg->GetHeader() && leg->GetNRows()>0) // the legend header counts as a row.
        || ( leg->GetHeader() && leg->GetNRows()>1) ) {
      return leg;
    }
    else { // legend exists but has at most a header.
      // use this empty legend to add entries below.
      //cout << "  leg->GetY1() = " << leg->GetY1() << "  leg->GetY2() = " << leg->GetY2() << endl;
      if (TMath::Abs(leg->GetY1() - leg->GetY2()) < LmHelper::kSmallDelta) leg->SetY1(leg->GetY2() - ydiff);
      //leg->SetTextSize(leg->GetTextSize()*sizefac); // better not mess with the user-defined size...
    }
  }
  leg->SetName("legend");

  std::cout << "TitleSize: " << gStyle->GetTitleSize()*sizefac << "   LegendSize: " << gStyle->GetTitleSize()*sizefac << std::endl;
  if (!printOnlyAverage && fType!=kCocktailOnly) {
    for (Int_t i = 0; i < GetNSignals(); ++i) {
      if (!CheckRequestedSigI(i)) continue;
      TString entryname = GetLmSignalName(i);
      if (fCompareSignalsToAverage && fLmSigAverage) entryname = Form("cut %02d (#chi^{2}/NDF = %5.2f)",i+1,fChi2_SignalsToAverage[i]);
      //if (fCompareSignalsToAverage && fLmSigAverage) entryname = Form("cut %02d (Kolmo dist.= %5.4f)",i+1,fChi2_SignalsToAverage[i]);

      leg->AddEntry(GetLmSignalI(i)->GetLmHist(histBit,bin_number,projOnMee)->GetDatahist(), entryname.Data(), fLegendEntryDrawOption.Data()); // for preliminaries
      if(GetLmSignalI(i)->GetLmHist(histBit,bin_number,projOnMee)->GetExternalObject())
        leg->AddEntry(GetLmSignalI(i)->GetLmHist(histBit,bin_number,projOnMee)->GetExternalObject(),
                      GetLmSignalI(i)->GetLmHist(histBit,bin_number,projOnMee)->GetExternalObject()->GetName(),fLegendEntryDrawOption.Data());
    }
  }
  if (fCompareSignalsToAverage && fLmSigAverage && fType!=kCocktailOnly)
	  leg->AddEntry(GetLmSigAverage()->GetLmHist(histBit,bin_number,projOnMee)->GetDatahist(),GetLmSigAverage()->GetName(), fLegendEntryDrawOption.Data());

  // Print Cocktail if needed
  if (fCocktailProcessed){
    // include cocktail only if one of the signal histograms is plotted (otherwise it will be plotted also into S/B plots etc...)
    if (histBit & (LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg) ) {
      for(UInt_t ic = 0; ic < fLmCocktails.size(); ++ic) {
	if(ic==1) continue;
        std::vector<TString> partnames = fLmCocktails.at(ic)->GetPartNames();
        for (unsigned int i = 0; i < partnames.size(); ++i){
	  if(partnames.at(i) == "sum") {
	    //leg->AddEntry(fLmCocktails.back()->GetSpectra1D(bin_number,projOnMee)->At(i), "Rapp Sum", "l"); //LEGEND jerome edit
            //leg->AddEntry(fLmCocktails.back()->GetSumErr1D(bin_number,projOnMee), "Uncertainty", "lF");
            //leg->AddEntry(fLmCocktails.back()->GetSpectra1D(bin_number,projOnMee)->At(i), "Cocktail sum", "lF");
            //leg->AddEntry(fLmCocktails.back()->GetSumErr1D(bin_number,projOnMee), "Cocktail uncertainty", "lF");
            TH1D* dummy = (TH1D*)(fLmCocktails.back()->GetSpectra1D(bin_number,projOnMee)->At(i))->Clone("dummy");
	    dummy->SetFillColor(kGray);
            //leg->AddEntry(dummy, "Cocktail sum", "lF");

	  }
	  else{
	    if(partnames.at(i)=="b#bar{b} #rightarrow e^{+}e^{-}" || partnames.at(i)=="J/#psi #rightarrow e^{+}e^{-}, J/#psi #rightarrow #gamma e^{+}e^{-}") continue;
            //TH1D* dummy = (TH1D*)(fLmCocktails.at(ic)->GetSpectra1D(bin_number,projOnMee)->At(i))->Clone("dummy");
            leg->AddEntry(fLmCocktails.at(ic)->GetSpectra1D(bin_number,projOnMee)->At(i), partnames.at(i), "l");
	  }
          if(i==partnames.size()-1) {
	    TH1D* dummy = (TH1D*)(fLmCocktails.back()->GetSpectra1D(bin_number,projOnMee)->At(i))->Clone("dummy");
	    dummy->SetLineStyle(7);
	    dummy->SetLineColor(kGray+1);
	    //leg->AddEntry(dummy,"sum with #eta from #it{m}_{T} scaling", "l");
          }
	}
        //if(fLegendOnlyFirstCocktail) break;
      }
      leg->AddEntry((TH1D*)0x0, "", "");
      leg->AddEntry((TH1D*)0x0, " 0.6 #leq #it{m}_{ee} #leq 1.1 GeV/#it{c}^{2}", "");
      //leg->AddEntry((TH1D*)0x0, "", "");
      //leg->AddEntry((TH1D*)0x0, "", "");
      //leg->AddEntry((TH1D*)0x0, "#splitline{        #pm5% Global unc.}{               not shown}", "");
    }
  }
	return leg;
}

//_______________________________________________________________________________________________
void LmHandler::ComputeOptimumPlotRangeY(unsigned int histBits, unsigned int bin_number, Bool_t projOnMee, Bool_t printOnlyAverage)
{
  /// This function is automatically called by the generic plotting function 'PrintCompare()' (if the y-range was not explicitly set via SetPlotRangeY()).
  /// Finds the minimum and maximum y-value of data points of all histograms which shall be plotted into the same canvas.
  /// Searches in the requested 1D-projection bin of the selected histogram type(s) in all LmSignals attached to this handler.
  /// Searches within the currently selected x-axis range.
  /// In the end it stores the values via SetPlotRangeY(minimum, maximum);
  /// @param hitBits Bits of histogram types that shall be plotted into the same canvas
  /// @param bin_number Projection bin to optimize.
  /// @param projOnMee Optimize x- or y-projections (set via LmBaseSignal::kProjOnMee or kProjOnPtee).
  /// @TODO: include error bars in calculation...

  LmHelper::Debug(Form("LmHandler::ComputeOptimumPlotRangeY()"), 5-debugHandler);

  // don't use floats (LmHelper::kSmallDelta will not work)
  Double_t searchXmin=-1e15, searchXmax= 1e15, xtmp;
  Double_t commonYmin= 1e15, commonYmax=-1e15, ytmp;

  if (projOnMee==LmBaseSignal::kProjOnMee) {
    if (fPlotXMeeMin>-1  && fPlotXMeeMax>0)  { searchXmin=fPlotXMeeMin;  searchXmax=fPlotXMeeMax;  }
  } else { // Ptee
    if (fPlotXPteeMin>-1 && fPlotXPteeMax>0) { searchXmin=fPlotXPteeMin; searchXmax=fPlotXPteeMax; }
  }

  //
  // loop over the requested histogram types (bits)
  //
  for (unsigned int iBit = 1; iBit < LmSignal::kMAXhist; iBit *= 2) {
    if ( !(iBit & histBits) ) continue; // continue if current histogram was not requested.
    //
    // loop over all attached signals of this handler (if not an average handler)
    //
    Int_t Nsignals = GetNSignals(); // Gives warning not used. C++11 // please contact patrick if it comes back.
    if (printOnlyAverage) Nsignals=1;
    for (Int_t i = 0; i < Nsignals; ++i) {
      //if (!CheckRequestedSigI(i) && !printOnlyAverage) continue; // do not do this here, because we want consistent ranges for all plots, e.g. when flipping slides.
      TH1D* href = 0x0;
      if (printOnlyAverage) {
        href = GetLmSigAverage()->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist();
      }
      else {
        GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetYaxis()->UnZoom(); // reset the plot range, not sure if needed.
        href = GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist();
      }
      //
      // loop over the x-axis range
      //
      for (Int_t i_bin = 1; i_bin <= href->GetNbinsX(); ++i_bin) // what about under/overflow?
      {
        xtmp = href->GetBinCenter(i_bin);
        if (xtmp < searchXmin) continue;
        if (xtmp > searchXmax) break;

        ytmp = href->GetBinContent(i_bin);
        if (ytmp < LmHelper::kSmallDelta) continue; // this is (only) needed for log-plots!
        if (ytmp < commonYmin) commonYmin = ytmp;
        if (ytmp > commonYmax) commonYmax = ytmp;
      }
      href = 0x0; delete href;
    }
  }

  SetPlotRangeY(commonYmin, commonYmax);
}

//_______________________________________________________________________________________________
Bool_t LmHandler::CheckPlottingDefaultDimensions()
{
  return (   LmBaseSignal::GetProjLabelXvar().Contains("#it{m}_{ee}", TString::kIgnoreCase)
          && LmBaseSignal::GetProjLabelYvar().Contains("#it{p}_{T,ee}", TString::kIgnoreCase) );
}

//_______________________________________________________________________________________________
Bool_t LmHandler::CheckRequestedSigI(unsigned int i_sig)
{
  /// Works only for one-digit numbers. Otherwise need to implement tokenization.
  if (fRequestedSignals.IsNull()) return kTRUE;
  if (fRequestedSignals.Contains(Form("%d",i_sig))) return kTRUE;
  // it would be more complicated and less powerful to do it with bits:
  //unsigned int sigBits=...// convert 'fRequestedSignals' to an int which represents all active bits. check stackoverflow...
  //if ((1<<i_sig) & sigBits) return kTRUE;
  return kFALSE;
}

//_______________________________________________________________________________________________
Int_t LmHandler::GetNRequestedSig()
{
  Int_t nReq=0;
  for (Int_t i = 0; i < GetNSignals(); ++i)
    if (CheckRequestedSigI(i)) nReq++;
  return nReq;
}

//_______________________________________________________________________________________________
Int_t LmHandler::FirstReqSig()
{
  for (Int_t i = 0; i < GetNSignals(); ++i)
    if (CheckRequestedSigI(i)) return i;
  return 0;
}

//_______________________________________________________________________________________________
void LmHandler::Write1DHistCocktail(unsigned int histBits, Bool_t projOnMee, TString sigName)
{
  /// Loop over all attached cocktails and write 1D spectra of the particles requested via histBits.
  //WriteInputInfos();
  if (!fCocktailProcessed) return;
  if (projOnMee==LmBaseSignal::kProjOnMee) {
    if (fBinsPtee_forprojMee.size()==0) {LmHelper::Error("LmHandler::Write1DHistCocktail(): no Ptee bins for Mee projections set."); return;}
    for(UInt_t ic = 0; ic < fLmCocktails.size(); ++ic) {
      fLmCocktails.at(ic)->WriteHist1D(histBits, fBinsPtee_forprojMee, kTRUE, projOnMee, sigName);
    }
  }
  else { // Ptee
    if (fBinsMee_forprojPtee.size()==0) {LmHelper::Error("LmHandler::Write1DHistCocktail(): no Mee bins for Ptee projections set."); return;}
    for(UInt_t ic = 0; ic < fLmCocktails.size(); ++ic) {
      fLmCocktails.at(ic)->WriteHist1D(histBits, fBinsMee_forprojPtee, kTRUE, projOnMee, sigName);
    }
  }
}

//_______________________________________________________________________________________________
void LmHandler::Write1DHistCombined(unsigned int histBits, Bool_t projOnMee, TString sigName)
{
  WriteInputInfos();
  if (projOnMee==LmBaseSignal::kProjOnMee) {
    if (fBinsPtee_forprojMee.size()==0) {LmHelper::Error("LmHandler::Write1DHistCombined(): no Ptee bins for Mee projections set."); return;}
    GetLmSigCombined()->WriteHist1D(histBits, fBinsPtee_forprojMee, fSimpleHistnames, projOnMee, sigName);
  }
  else { // Ptee
    if (fBinsMee_forprojPtee.size()==0) {LmHelper::Error("LmHandler::Write1DHistCombined(): no Mee bins for Ptee projections set."); return;}
    GetLmSigCombined()->WriteHist1D(histBits, fBinsMee_forprojPtee, fSimpleHistnames, projOnMee, sigName);
  }
}

//_______________________________________________________________________________________________
void LmHandler::Write1DHistAverage(unsigned int histBits, Bool_t projOnMee, TString sigName)
{
  WriteInputInfos();
  if (projOnMee==LmBaseSignal::kProjOnMee) {
    if (fBinsPtee_forprojMee.size()==0) {LmHelper::Error("LmHandler::Write1DHistAverage(): no Ptee bins for Mee projections set."); return;}
    GetLmSigAverage()->WriteHist1D(histBits, fBinsPtee_forprojMee, fSimpleHistnames, projOnMee, sigName);
  }
  else { // Ptee
    if (fBinsMee_forprojPtee.size()==0) {LmHelper::Error("LmHandler::Write1DHistAverage(): no Mee bins for Ptee projections set."); return;}
    GetLmSigAverage()->WriteHist1D(histBits, fBinsMee_forprojPtee, fSimpleHistnames, projOnMee, sigName);
  }
}

//_______________________________________________________________________________________________
void LmHandler::Write1DHistSingle(unsigned int histBits, Bool_t projOnMee, Bool_t enumerate)
{
  /// Write projections of attached signals into subfolders inside a rootfile.
  /// If no path is given to the handler, it will store the initial active path (which should be an opened file).
  /// Otherwise, subsequent write operations would start writing into the last created subfolder, causing a mess.
  /// Close the file when done writing to it! Since it will not be writable anymore, the handler will get the new
  /// active path (which should be another opened file).
  if (!fFileOut || !fFileOut->IsWritable()) fFileOut = gDirectory->CurrentDirectory();

  if (projOnMee==LmBaseSignal::kProjOnMee && fBinsPtee_forprojMee.size()==0) {
    LmHelper::Error("LmHandler::Write1DHistSingle(): no Ptee bins for Mee projections set."); return;
  }
  if (projOnMee==LmBaseSignal::kProjOnPtee && fBinsMee_forprojPtee.size()==0) {
    LmHelper::Error("LmHandler::Write1DHistSingle(): no Mee bins for Ptee projections set."); return;
  }

  for (int i=0; i<GetNSignals(); ++i) {
    TString signalDir = GetLmSignalName(i);
    if (enumerate) signalDir = Form("cut %02d",i);
    TDirectory* newdir = fFileOut->mkdir(signalDir.Data(), GetLmSignalName(i));
    // Create a sub-directory and return a pointer to the created directory.
    // Returns 0 in case of error. Returns 0 if a directory with the same name already exists.
    if (newdir) {
      newdir->cd();
      WriteInputInfos(i);
    } else { // assume that "0" means that the directory exists.
      LmHelper::Info("LmHandler::Write1DHistSingle(): moving into existing dir. Please ignore the error."); // when saving 1D projections this is OK.
      fFileOut->cd(signalDir.Data());
    }
    if (projOnMee==LmBaseSignal::kProjOnMee)
      GetLmSignalI(i)->WriteHist1D(histBits, fBinsPtee_forprojMee, fSimpleHistnames, projOnMee);
    else { // Ptee
      GetLmSignalI(i)->WriteHist1D(histBits, fBinsMee_forprojPtee, fSimpleHistnames, projOnMee);
    }
  }
}

void LmHandler::Write1DHistCocktail(Bool_t projOnMee, Bool_t enumerate)
{

  if (!fFileOut || !fFileOut->IsWritable()) fFileOut = gDirectory->CurrentDirectory();

  if (projOnMee==LmBaseSignal::kProjOnMee && fBinsPtee_forprojMee.size()==0) {
    LmHelper::Error("LmHandler::Write1DHistCocktail(): no Ptee bins for Mee projections set."); return;
  }
  if (projOnMee==LmBaseSignal::kProjOnPtee && fBinsMee_forprojPtee.size()==0) {
    LmHelper::Error("LmHandler::Write1DHistCocktail(): no Mee bins for Ptee projections set."); return;
  }

  for (int i=0; i<GetNCocktails(); ++i) {
    TString signalDir = "Cocktail1D";
    if (enumerate) signalDir = Form("Cocktail1D %02d",i);
    TDirectory* newdir = fFileOut->mkdir(signalDir.Data(), "Cocktail1D");
    // Create a sub-directory and return a pointer to the created directory.
    // Returns 0 in case of error. Returns 0 if a directory with the same name already exists.
    if (newdir) {
      newdir->cd();
    } else { // assume that "0" means that the directory exists.
      LmHelper::Info("LmHandler::Write1DHistCocktail(): moving into existing dir. Please ignore the error."); // when saving 1D projections this is OK.
      fFileOut->cd(signalDir.Data());
    }
    if (projOnMee==LmBaseSignal::kProjOnMee)
      for(Int_t j = 0; j < fBinsPtee_forprojMee.size()-1; ++j)
        GetLmCocktailI(i)->WriteHist1D(j, projOnMee);
    else { // Ptee
      for(Int_t j = 0; j < fBinsMee_forprojPtee.size()-1; ++j)
        GetLmCocktailI(i)->WriteHist1D(j, projOnMee);
    }
  }

}

//_______________________________________________________________________________________________
void LmHandler::Write2DHist(unsigned int histBits, Bool_t divideByBinWidth, Bool_t enumerate)
{
  /// Write attached 2D signals into subfolders inside a rootfile.
  /// Further description in Write1DHistSingle().
  if (!fFileOut || !fFileOut->IsWritable()) fFileOut = gDirectory->CurrentDirectory();

  for (int i=0; i<GetNSignals(); ++i) {
    TString signalDir = GetLmSignalName(i);
    if (enumerate) signalDir = Form("cut %02d",i);
    TDirectory* newdir = fFileOut->mkdir(signalDir.Data(), GetLmSignalName(i));
    // Create a sub-directory and return a pointer to the created directory.
    // Returns 0 in case of error. Returns 0 if a directory with the same name already exists.
    if (newdir) {
      newdir->cd();
      WriteInputInfos(i);
    } else { // assume that "0" means that the directory exists.
      LmHelper::Warning("LmHandler::Write2DHist(): moving into existing dir. This is probably unintended!"); // for 2D and 3D this should not happen.
      fFileOut->cd(signalDir.Data());
    }
    GetLmSignalI(i)->WriteHist2D(histBits, divideByBinWidth, fSimpleHistnames);
  }
}

void LmHandler::Write2DHistCocktail(Bool_t divideByBinWidth, Bool_t enumerate)
{

  if (!fFileOut || !fFileOut->IsWritable()) fFileOut = gDirectory->CurrentDirectory();

  for (int i=0; i<GetNCocktails(); ++i) {
    TString signalDir = "Cocktail2D";
    if (enumerate) signalDir = Form("Cocktail2D %02d",i);
    TDirectory* newdir = fFileOut->mkdir(signalDir.Data(), "Cocktail1D");
    // Create a sub-directory and return a pointer to the created directory.
    // Returns 0 in case of error. Returns 0 if a directory with the same name already exists.
    if (newdir) {
      newdir->cd();
    } else { // assume that "0" means that the directory exists.
      LmHelper::Info("LmHandler::Write2DHistCocktail(): moving into existing dir. Please ignore the error."); // when saving 1D projections this is OK.
      fFileOut->cd(signalDir.Data());
    }
    GetLmCocktailI(i)->WriteHist2D(divideByBinWidth);
  }

}




//_______________________________________________________________________________________________
void LmHandler::Write3DHist(unsigned int histBits, Bool_t enumerate)
{
  /// Write 3D histograms from managers of attached signals into subfolders inside a rootfile.
  /// Further description in Write1DHistSingle().
  if (!fFileOut || !fFileOut->IsWritable()) fFileOut = gDirectory->CurrentDirectory();

  for (int i=0; i<GetNSignals(); ++i) {
    TString signalDir = GetLmSignalName(i);
    if (enumerate) signalDir = Form("cut %02d",i);
    TDirectory* newdir = fFileOut->mkdir(signalDir.Data(), GetLmSignalName(i));
    // Create a sub-directory and return a pointer to the created directory.
    // Returns 0 in case of error. Returns 0 if a directory with the same name already exists.
    if (newdir) {
      newdir->cd();
      WriteInputInfos(i);
    } else { // assume that "0" means that the directory exists.
      LmHelper::Warning("LmHandler::Write3DHist(): moving into existing dir. This is probably unintended!"); // for 2D and 3D this should not happen.
      fFileOut->cd(signalDir.Data());
    }
    GetLmSignalI(i)->WriteHist3D(histBits);
  }
}

//_______________________________________________________________________________________________
void LmHandler::WriteInputInfos(Int_t i_sig)
{
  // write some info strings to the rootfile.
  LmSignal* tmpSig;
  if (i_sig<0)  tmpSig = GetReferenceSignal();
  else          tmpSig = GetLmSignalI((unsigned int)i_sig);
  if (!tmpSig->GetManager()) {
    LmHelper::Error("LmHandler::WriteInputInfos(): no manager found."); return;
  }
  // system & event related
  TObjString sNevents(Form("Number of events: %.0f", tmpSig->GetNeventsPhysSel()));
  sNevents.Write();
  TObjString sSystem("Collision system: " + tmpSig->GetManager()->GetCollSystem());
  sSystem.Write();
  TObjString sEnergy("Collision energy: " + tmpSig->GetManager()->GetCollEnergy());
  sEnergy.Write();
  Double_t cent_min = tmpSig->GetManager()->GetCentrality_min();
  Double_t cent_max = tmpSig->GetManager()->GetCentrality_max();
  if (cent_min > -1 && cent_max > 0){
    TObjString sCent(Form("Centrality_min = %2.0f   Centrality_max = %2.0f", cent_min, cent_max));
    sCent.Write();
  }

  // track & pair related
  TObjString sPt(Form("Pt_min = %4.2f   Pt_max = %4.2f", tmpSig->GetManager()->GetPtRange_min(), tmpSig->GetManager()->GetPtRange_max()));
  sPt.Write();
  TObjString sEta(Form("Eta_min = %4.2f   Eta_max = %4.2f", tmpSig->GetManager()->GetEtaRange_min(), tmpSig->GetManager()->GetEtaRange_max()));
  sEta.Write();
  if (tmpSig->GetManager()->GetThetaEEmin() > -1) {
    TObjString sOpAngle(Form("Opening angle cut: %3.2f", tmpSig->GetManager()->GetThetaEEmin()));
    sOpAngle.Write();
  }
}

//_______________________________________________________________________________________________
std::vector<TH1D*> LmHandler::CollectProjections(unsigned int histBits, unsigned int bin_number, Bool_t projOnMee)
{
  /// Return vector with all histograms of one type that are typically drawn into one compare plot.
  /// @param histBits Histogram type (bit) that shall be collected. Multiple types not allowed in this function.
  /// @param bin_number Projection bin to collect.
  /// @param projOnMee Collect x- or y-projections (set via LmBaseSignal::kProjOnMee or kProjOnPtee).

  std::vector<TH1D*> vProj;
  //
  // loop over the requested histograms
  //
  Bool_t foundReqHist=kFALSE;
  for (unsigned int iBit = 1; iBit < LmSignal::kMAXhist; iBit *= 2) {
    if (iBit == histBits) {
      foundReqHist=kTRUE;
      for (Int_t i = 0; i < GetNSignals(); ++i) {
        TH1D* histi = new TH1D( *(GetLmSignalI(i)->GetLmHist(iBit,bin_number,projOnMee)->GetDatahist()) );
        histi->SetTitle(GetLmSignalName(i));
        // beautify histograms
        histi->SetLineColor(LmHelper::GetUniformColor(i, GetNSignals()));
        histi->SetMarkerStyle(20);
        histi->SetMarkerColor(LmHelper::GetUniformColor(i, GetNSignals()));
        // attach to vector
        std::cout << "Check 99: " << histi->GetName() << std::endl;
        vProj.push_back(histi);
      }
      break; // quit loop over bits
    } // found requested histogram
  } // hist bit loop

  if (!foundReqHist) {
    LmHelper::Error("LmHandler::CollectProjections(): 'histBits' must exactly match one histogram type (bit). No multiple types allowed.");
  }
  return vProj;

}


//_______________________________________________________________________________________________
void LmHandler::SetDoSystOnUnlikeSign(bool SDSU) {
  /// This reconfigures the attached LmSignals so that they will create projections and systematics from Unlike Sign.
  /// Because their function GetSig2D() is sensitive to their setting of SetSubtractionDone().
  if (SDSU) {
    LmHelper::Info("LmHandler::SetDoSystOnUnlikeSign(): note that this modifies the attached signals, so they will create signal projections and systematics from Unlike Sign.");
    for (Int_t i = 0; i < GetNSignals(); ++i)
      GetLmSignalI(i)->SetSubtractionDone(kFALSE); // by this, the function LmSignal::GetSig2D() returns fUnlike.
  }
  else {
    for (Int_t i = 0; i < GetNSignals(); ++i)
      if (GetLmSignalI(i)->GetSubSig2D()) GetLmSignalI(i)->SetSubtractionDone( kTRUE ); // reset signal to a plausible state.
  }
}


// Please do not use internally! Use GetReferenceSignal()->GetMaxBinProj(projOnMee);
//_______________________________________________________________________________________________
Int_t LmHandler::GetMaxBinProj(Bool_t projOnMee) const {
  Int_t maxBin = GetReferenceSignal()->GetMaxBinProj(projOnMee);
  // maxBin==1 means having 2 projections, which happens if exactly one (integrated) bin is given.
  // Setting it to 0 prevents duplicate printing of this integrated bin in your main.cpp.
  if (maxBin==1) maxBin=0;
  return maxBin;
}

//_______________________________________________________________________________________________
Double_t LmHandler::GetYEdge_forprojOnX(unsigned int bin) const {
  if (fBinsPtee_forprojMee.size() == 0) { LmHelper::Error("LmHandler::GetPteeEdge_forprojMee/GetYEdge_forprojOnX(): No Y-bins for X-projection set! [use: SetBinsY_forprojOnX()]"); }
  if (bin>=fBinsPtee_forprojMee.size()) { LmHelper::Error(Form("LmHandler::GetPteeEdge_forprojMee/GetYEdge_forprojOnX(bin=%u): out of range! Too few bins set!", bin)); }
  return fBinsPtee_forprojMee.at(bin);
}

//_______________________________________________________________________________________________
Double_t LmHandler::GetXEdge_forprojOnY(unsigned int bin) const {
  if (fBinsMee_forprojPtee.size() == 0) { LmHelper::Error("LmHandler::GetMeeEdge_forprojPtee/GetXEdge_forprojOnY(): No X-bins for Y-projection set! [use: SetBinsX_forprojOnY()]"); }
  if (bin>=fBinsMee_forprojPtee.size()) { LmHelper::Error(Form("LmHandler::GetMeeEdge_forprojPtee/GetXEdge_forprojOnY(bin=%u): out of range! Too few bins set!", bin)); }
  return fBinsMee_forprojPtee.at(bin);
}

//_______________________________________________________________________________________________
Double_t LmHandler::GetPteeEdge_forprojMee(unsigned int bin) const {
  return GetYEdge_forprojOnX(bin);
}
//_______________________________________________________________________________________________
Double_t LmHandler::GetMeeEdge_forprojPtee(unsigned int bin) const {
  return GetXEdge_forprojOnY(bin);
}

//_______________________________________________________________________________________________
void LmHandler::GetProjRange(unsigned int bin_number, Bool_t projOnMee, Double_t &proj_min, Double_t &proj_max) const {
/// Fill the projection range of the given projection bin into the return variables 'proj_min' and 'proj_max'.
  if (projOnMee==LmBaseSignal::kProjOnMee){
    if ((Int_t)bin_number >= GetReferenceSignal()->GetMaxBinProj(LmBaseSignal::kProjOnMee)){ // case of integrated projection (last bin)
      proj_min = GetPteeEdge_forprojMee(0);
      proj_max = GetPteeEdge_forprojMee(bin_number);
    }
    else {
      proj_min = GetPteeEdge_forprojMee(bin_number);
      proj_max = GetPteeEdge_forprojMee(bin_number+1);
    }
    LmHelper::Debug(Form("  %s-range = %f to %f %s", LmBaseSignal::GetProjLabelYvar().Data() ,proj_min, proj_max, LmBaseSignal::GetProjLabelYunit().Data()), 10-debugHandler);
  }
  else { // Ptee
    if ((Int_t)bin_number >= GetReferenceSignal()->GetMaxBinProj(LmBaseSignal::kProjOnPtee)){ // case of integrated projection (last bin)
      proj_min = GetMeeEdge_forprojPtee(0);
      proj_max = GetMeeEdge_forprojPtee(bin_number);
    }
    else {
      proj_min = GetMeeEdge_forprojPtee(bin_number);
      proj_max = GetMeeEdge_forprojPtee(bin_number+1);
    }
    LmHelper::Debug(Form("  %s-range = %f to %f %s", LmBaseSignal::GetProjLabelXvar().Data(), proj_min, proj_max, LmBaseSignal::GetProjLabelXunit().Data()), 10-debugHandler);
  }
}

//_______________________________________________________________________________________________
LmSignal* LmHandler::GetLmSigCombined() const {
  if (!fLmSigCombined) { LmHelper::Error(Form("LmHandler::GetLmSigCombined(): fLmSigCombined not available! (name=%s)",GetName())); return 0x0; }
  else return fLmSigCombined;
}

//_______________________________________________________________________________________________
LmSignal* LmHandler::GetLmSigAverage() const {
  if (!fLmSigAverage) { LmHelper::Error(Form("LmHandler::GetLmSigAverage(): fLmSigAverage not available! (name=%s)",GetName())); return 0x0; }
  else return fLmSigAverage;
}

//_______________________________________________________________________________________________
LmSignal* LmHandler::GetLmSignalI(unsigned int i_sig) const {
  if (i_sig>=fLmSig.size()) { LmHelper::Error(Form("LmHandler::GetLmSignalI(i_sig=%u): out of range! (name=%s)",i_sig,GetName())); }
  return fLmSig.at(i_sig);
}

//_______________________________________________________________________________________________
LmSignal* LmHandler::GetReferenceSignal() const {
  /// This internal function returns the most relevant 'reference' signal, depending on the handler type.
  /// For systematics handlers, the average signal is only returned, if SetCompareSignalsToAverage() was called.
  /// Otherwise, and in all other cases, the first signal is returned. This is particularly important due to function
  /// calls, where the manager of that signal is needed (which does't exist for fLmSigAverage and fLmSigCombined).

  // This function must always return a valid LmSignal, because it is meant to be used without checks.
  if      (fLmSigCombined && fType==kCombine) return fLmSigCombined;
  else if (fLmSigAverage  && fType==kAverage) return fLmSigAverage;
  else if (fLmSigAverage  && fCompareSignalsToAverage && (fType==kSystematic_Average || fType==kSystematic_WeightedAverage || fType==kSystematic_Jerome))
    return fLmSigAverage;
  return GetLmSignalI(0);
}
