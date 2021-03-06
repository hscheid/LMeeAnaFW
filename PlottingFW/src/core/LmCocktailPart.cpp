// c++ includes
#include <iostream>
using namespace std;
// ROOT includes
#include "TH1.h"
#include "TH2.h"
#include "TColor.h"
// project includes
#include "LmCocktailPart.h"
#include "LmHelper.h"

// initialize static variables
Bool_t      LmCocktailPart::fUseShortLegendNames(kFALSE);

// copy constructor, used by LmCocktail copy constructor
//_______________________________________________________________________________________________
LmCocktailPart::LmCocktailPart(const LmCocktailPart& part) :
LmBaseSignal(),
fName(part.fName),
fType(part.fType),
fSpectrum(0x0),    // copied below.
fSpectrumLow(0x0), //fSpectrumLow(part.fSpectrumLow), // dont trust to copy pointers...
fSpectrumHigh(0x0) //fSpectrumHigh(part.fSpectrumHigh)
{
  /// Copy constructor for LmCocktailPart
  /// the projections are not transferred.

  LmHelper::Debug("LmCocktailPart copy constructor", 5);
  // initialize inherited variables:
  SetNeventsPhysSel(part.GetNeventsPhysSel());
  SetCrossSection(part.GetCrossSection());    
  SetDoNormBinwidth(part.GetDoNormBinwidth());
  SetDoNormNevents(part.GetDoNormNevents());
  SetDoNormNentries(part.GetDoNormNentries());
  SetDoNormCrossSection(part.GetDoNormCrossSection());

  SetDoExtendedTitle(part.GetDoExtendedTitle());
  // copy member variables:
  SetSpectrum2D(part.GetSpectrum2D()); // using copy constructor of TH2D.
  if (part.GetSpectrum2DLow()!=0x0)  SetSpectrum2DLow(part.GetSpectrum2DLow()); // using copy constructor of TH2D.
  if (part.GetSpectrum2DHigh()!=0x0) SetSpectrum2DHigh(part.GetSpectrum2DHigh()); // using copy constructor of TH2D.

  fSpectrum_projMee.clear();
  fSpectrum_projPtee.clear();
  fSpectrumErr_projMee.clear();
  fSpectrumErr_projPtee.clear();

  fMTscalingUnc.clear();
  fBRUnc.clear();
  fAddUnc.clear();
  fMTscalingUnc.push_back(0);
  fMTscalingUnc.push_back(0);
  fBRUnc.push_back(0);
  fBRUnc.push_back(0);
  fAddUnc.push_back(0);
  fAddUnc.push_back(0);
  fParamUnc.push_back(0);
  fParamUnc.push_back(0);
}


//_______________________________________________________________________________________________
LmCocktailPart* LmCocktailPart::Copy(std::string newname, Int_t color)
{
  LmCocktailPart* newPart = new LmCocktailPart(*this);
  if (newname.compare("")!=0) newPart->SetName(newname);
  if (color>-1) newPart->GetSpectrum2D()->SetLineColor(color);
  newPart->ApplyCommonStyle();
  return newPart;
}


//_______________________________________________________________________________________________
LmCocktailPart::LmCocktailPart(std::string name) :
LmBaseSignal(),
fName(name),
fType(0),
fSpectrum(0x0),
fSpectrumLow(0x0),
fSpectrumHigh(0x0)
{
  /// Default constructor for LmCocktailPart
  /// @param name Name of particle or decay (optional)

  LmHelper::Debug("LmCocktailPart constructor", 5);
  // initialize inherited variables:
  SetCrossSection(57.8); //57.8
  SetNeventsPhysSel(1.);
  SetDoNormBinwidth(kTRUE); //TRUE!
  SetDoNormNevents(kFALSE);
  SetDoNormNentries(kFALSE);
  SetDoNormCrossSection(kFALSE);

  SetDoExtendedTitle(kFALSE);

  fMTscalingUnc.push_back(0);
  fMTscalingUnc.push_back(0);
  fBRUnc.push_back(0);
  fBRUnc.push_back(0);
  fAddUnc.push_back(0);
  fAddUnc.push_back(0);
  fParamUnc.push_back(0);
  fParamUnc.push_back(0); 
 
}

////_______________________________________________________________________________________________
//LmCocktailPart::LmCocktailPart(std::string name, Bool_t NormBinwidth, Bool_t NormNevents, Bool_t NormNentries, Bool_t NormCrossSection, Double_t NeventsPhysSel, Double_t CrossSection) :
//LmBaseSignal(),
//fName(name),
//fType(0),
//fSpectrum(0x0),
//fSpectrumLow(0x0),
//fSpectrumHigh(0x0)
//{
//  /// Default constructor for LmCocktailPart
//  /// @param name Name of particle or decay (optional)
//
//  LmHelper::Debug("LmCocktailPart constructor", 5);
//  // initialize inherited variables:
//  SetDoNormBinwidth(NormBinwidth); //TRUE!
//  SetDoNormNevents(NormEvents);
//  SetDoNormNentries(NormNentries);
//  SetDoNormCrossSection(NormCrossSection);
//
//  SetDoExtendedTitle(kFALSE);
//
//  SetNeventsPhysSel(NeventsPhysSel);       
//  SetCrossSection(CrossSection);    
//}


//_______________________________________________________________________________________________
LmCocktailPart::~LmCocktailPart()
{
  LmHelper::Debug("LmCocktailPart destructor", 5);
  if (fSpectrum) delete fSpectrum;
  fSpectrum_projMee.clear();
  fSpectrum_projPtee.clear();
}


//_______________________________________________________________________________________________
void LmCocktailPart::SetType(Int_t type) {
  fType = type;
  if (fName.size()==0 || fName.compare("default")==0) fName = GetTypenameStatic(fType);
}

//_______________________________________________________________________________________________
const char* LmCocktailPart::GetTypenameStatic(Int_t type)
{
 /// Returns default name for given type. Also useful for Error messages.
  switch (type) {
    case kUndef:        return "Undef";
    case kSum:          return "Sum";
    case kLF:           return "LF";
    case kPion:         return "Pion";
    case kEta:          return "Eta";
    case kEtaPrime:     return "EtaPrime";
    case kRho:          return "Rho";
    case kOmega:        return "Omega";
    case kOmegaDalitz:  return "OmegaDalitz";
    case kPhi:          return "Phi";
    case kPhiDalitz:    return "PhiDalitz";
    case kJPsi:         return "JPsi";
    case kJPsiDalitz:   return "JPsiDalitz";
    case kCharm:        return "Charm";
    case kBeauty:       return "Beauty";
    case kVirtGamma:    return "VirtGamma";
    case kHGvac:        return "HGvac";
    case kHGmed:        return "HGmed";
    case kHGdrop:       return "HGdrop";
    case kQGP:          return "QGP";
    case kSystematic:   return "Systematic";
    case kHF:           return "HeavyFlavour";
    case kHadrBrems:    return "HadronicBremsstrahlung";
    case kRappSum:      return "RappSum";
    case kSmashSum:     return "SmashSum";
    default:            return Form("Type%i",type);
  }
}

//_______________________________________________________________________________________________
const char* LmCocktailPart::GetLegendnameStatic(Int_t type)
{
  /// Returns default legend entry name for given type, depending on fUseShortLegendNames.
  if (fUseShortLegendNames) {
    switch (type) {
      case kUndef:        return "undef";
      case kSum:          return "sum";
      case kLF:           return "light flavor";
      case kPion:         return "#pi^{0}";
      case kEta:          return "#eta";
      case kEtaPrime:     return "#eta'";
      case kRho:          return "#rho";
      case kOmega:        return "#omega";
      case kOmegaDalitz:  return "#omega Dalitz";
      //case kOmegaRes:     return "#omega resonance";
      case kPhi:          return "#phi";
      case kPhiDalitz:    return "#phi Dalitz";
      //case kPhiRes:       return "#phi resonance";
      case kJPsi:         return "J/#psi";
      case kCharm:        return "c#bar{c}";
      case kBeauty:       return "b#bar{b}";
      case kVirtGamma:    return "direct photon";
      case kHGvac:        return "HG + vac. #rho [Rapp]";
      //case kHGmed:        return "HG + in-med. #rho [Rapp]";
      case kHGmed:        return "in-med. hadronic [Rapp]";
      case kHGdrop:       return "HG + drop. #rho [Rapp]";
      case kQGP:          return "QGP radiation [Rapp]";
      case kSystematic:   return "systematic";
      case kHF:           return "heavy flavor";
      case kHadrBrems:    return "hadr. bremsstrahlung";
      case kRappSum:      return "in-med. hadronic + QGP [Rapp]";
      case kSmashSum:     return "hadr. BS [SMASH]";
      default:            return Form("Type%i",type);
    }
  }
  else { // default
    switch (type) {
      case kUndef:        return "undef";
      case kSum:          return "sum";
      case kLF:           return "Light flavor (#rho+#omega+#phi+#eta')";
      case kPion:         return "#pi^{0} #rightarrow #gamma e^{+}e^{-}";
      case kEta:          return "#eta #rightarrow #gamma e^{+}e^{-}";
      case kEtaPrime:     return "#eta' #rightarrow #gamma e^{+}e^{-}, #eta' #rightarrow #omega e^{+}e^{-}";
      case kRho:          return "#rho #rightarrow e^{+}e^{-}";
      case kOmega:        return "#omega #rightarrow e^{+}e^{-}, #omega #rightarrow #pi^{0} e^{+}e^{-}";
      case kOmegaDalitz:  return "#omega #rightarrow #pi^{0} e^{+}e^{-}";
      //case kOmegaRes:     return "#omega #rightarrow e^{+}e^{-}";
      case kPhi:          return "#phi #rightarrow e^{+}e^{-}, #phi #rightarrow #eta e^{+}e^{-}, #phi #rightarrow #pi^{0} e^{+}e^{-}";
      case kPhiDalitz:    return "#phi #rightarrow #eta e^{+}e^{-}, #phi #rightarrow #pi^{0} e^{+}e^{-}";
      //case kPhiRes:       return "#phi #rightarrow e^{+}e^{-}";
      case kJPsi:         return "J/#psi #rightarrow e^{+}e^{-}, J/#psi #rightarrow #gamma e^{+}e^{-}";
      case kCharm:        return "c#bar{c} #rightarrow e^{+}e^{-}";
      case kBeauty:       return "b#bar{b} #rightarrow e^{+}e^{-}";
      case kVirtGamma:    return "direct photon";
      case kHGvac:        return "HG + vac. #rho [Rapp]";
      case kHGmed:        return "in-med. hadronic [Rapp]";
      case kHGdrop:       return "HG + drop. #rho [Rapp]";
      case kQGP:          return "QGP radiation [Rapp]";
      case kSystematic:   return "systematic";
      case kHF:           return "heavy flavor";
      case kHadrBrems:    return "hadr. bremsstrahlung";
      case kRappSum:      return "in-med. hadr. [Rapp]";
      case kSmashSum:     return "hadr. BS [SMASH]";
      default:            return Form("Type%i",type);
    }
  }
}


//_______________________________________________________________________________________________
void LmCocktailPart::Process(Int_t type)
{
  /// This function is called during LmCocktail::Process().
  SetType(type);
  LmHelper::Debug(Form("LmCocktailPart Process(type=%i) [name='%s']", type, GetName()), 5);
  // Change the name for the legend (after the debug statement)
  SetName(GetLegendnameStatic(type));

  if (!fSpectrum) { LmHelper::Error(Form("LmCocktailPart::Process(): no spectrum set! Check processing of LmCocktail(Man).")); return; }

  switch (type) {
    case kSum:
      LmHelper::Debug(Form(" kSum: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kGray+3);
      fSpectrum->SetName("cocktailSum");
      if(fSpectrumLow) fSpectrumLow->SetName("cocktailSumLow");
      if(fSpectrumHigh) fSpectrumHigh->SetName("cocktailSumHigh");
      ApplyCommonStyle();
      break;

    case kLF:
      LmHelper::Debug(Form(" kLF: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kGreen+3);
      fSpectrum->SetName("LightFlavorSum");
      ApplyCommonStyle();
      break;

    case kPion:
      LmHelper::Debug(Form(" kPion: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kRed);
      ApplyCommonStyle();
      break;

    case kEta:
      LmHelper::Debug(Form(" kEta: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kBlue);
      ApplyCommonStyle();
      break;

    case kEtaPrime:
      LmHelper::Debug(Form(" kEtaPrime: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kTeal-1);
      ApplyCommonStyle();
      break;

    case kRho:
      LmHelper::Debug(Form(" kRho: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kOrange+3);
      ApplyCommonStyle();
      break;

    case kOmega:
      LmHelper::Debug(Form(" kOmega: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kGreen-1);
      ApplyCommonStyle();
      break;

    case kPhi:
      LmHelper::Debug(Form(" kPhi: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kPink-6);
      ApplyCommonStyle();
      break;

    case kJPsi:
      LmHelper::Debug(Form(" kJPsi: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kAzure+4);
      ApplyCommonStyle();
      break;

    case kCharm:
      LmHelper::Debug(Form(" kCharm: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kMagenta);
      ApplyCommonStyle();
      break;

    case kBeauty:
      LmHelper::Debug(Form(" kBeauty: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kOrange+2);
      ApplyCommonStyle();
      break;

    case kVirtGamma:
      LmHelper::Debug(Form(" kVirtGamma: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kGreen-4); // not tuned
      ApplyCommonStyle();
      break;

    case kHGvac:
      LmHelper::Debug(Form(" kHGvac: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kGreen+2); // not tuned
      ApplyCommonStyle();
      break;
    case kHGmed:
      LmHelper::Debug(Form(" kHGmed: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kOrange+1);// used in LOI, but not good here.
      //fSpectrum->SetLineColor(kGreen+1);
      ApplyCommonStyle();
      break;
    case kHGdrop:
      LmHelper::Debug(Form(" kHGdrop: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kGreen+3); // not tuned
      ApplyCommonStyle();
      break;
    case kQGP:
      LmHelper::Debug(Form(" kQGP: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kRed+1);// used in LOI, but not good here.
      //fSpectrum->SetLineColor(kBlue);
      ApplyCommonStyle();
      break;

    case kHF:
      LmHelper::Debug(Form(" kHF: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kRed);
      fSpectrum->SetName("HeavyFlavorSum");
      ApplyCommonStyle();
      break;

    case kHadrBrems:
      LmHelper::Debug(Form(" kHadrBrems: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kGreen+2);// used in LOI, but not good here.
      //fSpectrum->SetLineColor(kBlue);
      ApplyCommonStyle();
      break;
  
    case kRappSum:
      LmHelper::Debug(Form(" kRappSum: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kRed+1);// used in LOI, but not good here.
      //fSpectrum->SetLineColor(kBlue);
      ApplyCommonStyle();
      break;
    case kRappSumUnc:
      LmHelper::Debug(Form(" kRappSumUnc: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kRed+1);// used in LOI, but not good here.
      fSpectrum->SetLineStyle(3);// used in LOI, but not good here.
      fSpectrum->SetLineWidth(2);
      //fSpectrum->SetLineColor(kBlue);
      //ApplyCommonStyle();
      break;


    case kSmashSum:
      LmHelper::Debug(Form(" kSmashSum: %s", fName.data()), 10);
      fSpectrum->SetLineColor(kOrange+2);// used in LOI, but not good here.
      //fSpectrum->SetLineColor(kBlue);
      ApplyCommonStyle();
      break;



    default:
      break;
  }

}


//_______________________________________________________________________________________________
void LmCocktailPart::ApplyCommonStyle()
{
  fSpectrum->SetMarkerColor(fSpectrum->GetLineColor());
  fSpectrum->SetLineWidth(2);
  fSpectrum->SetLineStyle(1);
}

//_______________________________________________________________________________________________
void LmCocktailPart::InheritStyleFrom2D(TH1* hProj)
{
  /// Inherit styles from 2D spectrum, which may be manually modified.
  hProj->SetLineStyle(fSpectrum->GetLineStyle());
  hProj->SetLineWidth(fSpectrum->GetLineWidth());
  // The color seems to be transferred automatically? Or is it done somewhere else?
}


//_______________________________________________________________________________________________
void LmCocktailPart::MakeSpectra1D(const std::vector<Double_t> bins, Bool_t projOnMee)
{
  LmHelper::Debug(Form(" LmCocktailPart::MakeSpectra1D(projOnMee=%i)", projOnMee), 5);
  if (bins.size()<=1) {
    LmHelper::Info(Form(" LmCocktailPart::MakeSpectra1D(projOnMee=%i): not enough bins, skip doing projections.", projOnMee));
    return;
  }
  CheckAndDeleteOldProjections(projOnMee);
  for (unsigned int i = 0; i < bins.size()-1; ++i){
    if (projOnMee==LmBaseSignal::kProjOnMee)  MakeSpectra1D_Mee(bins.at(i), bins.at(i+1));
    else                                      MakeSpectra1D_Ptee(bins.at(i), bins.at(i+1));
  }
  // the last projection is integrated over all bins
  if (projOnMee==LmBaseSignal::kProjOnMee)    MakeSpectra1D_Mee(bins.at(0), bins.at(bins.size()-1));
  else                                        MakeSpectra1D_Ptee(bins.at(0), bins.at(bins.size()-1));
  if(HasSystematics()){
    for (unsigned int i = 0; i < bins.size()-1; ++i){
      if(projOnMee==LmBaseSignal::kProjOnMee) MakeSpectraErr1D_Mee(bins.at(i), bins.at(i+1));
      else                                    MakeSpectraErr1D_Ptee(bins.at(i), bins.at(i+1));
    }
    // the last projection is integrated over all bins
    if (projOnMee==LmBaseSignal::kProjOnMee)  MakeSpectraErr1D_Mee(bins.at(0), bins.at(bins.size()-1));
    else                                      MakeSpectraErr1D_Ptee(bins.at(0), bins.at(bins.size()-1));
  }
}


//_______________________________________________________________________________________________
void LmCocktailPart::MakeSpectra1D_Mee(Double_t valmin, Double_t valmax)
{
  LmHelper::Debug(Form("  LmCocktailPart::MakeSpectra1D_Mee(): from Ptee = %f to %f GeV/c", valmin, valmax), 10);
  // now with normalization (or not) as requested by fDoNormBinwidth and fDoNormNevents
  
  //TH1D* hProj = (TH1D*) DoProjectionMee(GetSpectrum2D(), valmin, valmax, fDoNormBinwidth, fDoNormNevents);
  TH1D* hProj = (TH1D*) DoProjectionMee(GetSpectrum2D(), valmin, valmax, fNormalisations);
  InheritStyleFrom2D(hProj);
  AttachSpectrum_Mee(*hProj);
}
//_______________________________________________________________________________________________
void LmCocktailPart::MakeSpectra1D_Ptee(Double_t valmin, Double_t valmax)
{
  LmHelper::Debug(Form("  LmCocktailPart::MakeSpectra1D_Ptee(): from Mee = %f to %f GeV/c^2", valmin, valmax), 10);
  // now with normalization (or not) as requested by fDoNormBinwidth and fDoNormNevents
  
  //TH1D* hProj = (TH1D*) DoProjectionPtee(GetSpectrum2D(), valmin, valmax, fDoNormBinwidth, fDoNormNevents);
  TH1D* hProj = (TH1D*) DoProjectionPtee(GetSpectrum2D(), valmin, valmax, fNormalisations);
  InheritStyleFrom2D(hProj); 
  AttachSpectrum_Ptee(*hProj);
}
//_______________________________________________________________________________________________
void LmCocktailPart::MakeSpectraErr1D_Mee(Double_t valmin, Double_t valmax)
{
  LmHelper::Debug(Form("  LmCocktailPart::MakeSpectraErr1D_Mee(): from Ptee = %f to %f GeV/c", valmin, valmax), 10);
  // now with normalization (or not) as requested by fDoNormBinwidth and fDoNormNevents
  //TH1D* hProj     = (TH1D*) DoProjectionMee(GetSpectrum2D(),     valmin, valmax, fDoNormBinwidth, fDoNormNevents);
  //TH1D* hProjLow  = (TH1D*) DoProjectionMee(GetSpectrum2DLow(),  valmin, valmax, fDoNormBinwidth, fDoNormNevents);
  //TH1D* hProjHigh = (TH1D*) DoProjectionMee(GetSpectrum2DHigh(), valmin, valmax, fDoNormBinwidth, fDoNormNevents);
  TH1D* hProj     = (TH1D*) DoProjectionMee(GetSpectrum2D(),     valmin, valmax, fNormalisations);
  TH1D* hProjLow  = (TH1D*) DoProjectionMee(GetSpectrum2DLow(),  valmin, valmax, fNormalisations);
  TH1D* hProjHigh = (TH1D*) DoProjectionMee(GetSpectrum2DHigh(), valmin, valmax, fNormalisations);
  TGraphAsymmErrors *grProj = new TGraphAsymmErrors(hProj->GetNbinsX());
  for(Int_t i = 0; i < grProj->GetN(); ++i){
    grProj->SetPoint(i,hProj->GetBinCenter(i+1),hProj->GetBinContent(i+1));
    grProj->SetPointError(i,TMath::Abs(hProj->GetBinCenter(i+1) - hProj->GetXaxis()->GetBinLowEdge(i+1)),
                            TMath::Abs(hProj->GetBinCenter(i+1) - hProj->GetXaxis()->GetBinUpEdge (i+1)) ,
                            TMath::Abs(hProj->GetBinContent(i+1) - hProjLow ->GetBinContent(i+1)),
                            TMath::Abs(hProj->GetBinContent(i+1) - hProjHigh->GetBinContent(i+1)) );
                            // 0.3*hProj->GetBinContent(i+1),0.3*hProj->GetBinContent(i+1));
  }
  delete hProj; delete hProjLow; delete hProjHigh;
  // grProj->SetFillStyle(0);
  grProj->SetLineWidth(0);
  grProj->SetMarkerColor(kGray);
  grProj->SetLineColor(kGray);
  grProj->SetFillColorAlpha(kGray+1,0.5);
  AttachSpectrumErr_Mee(grProj);
}
//_______________________________________________________________________________________________
void LmCocktailPart::MakeSpectraErr1D_Ptee(Double_t valmin, Double_t valmax)
{
  LmHelper::Debug(Form("  LmCocktailPart::MakeSpectraErr1D_Ptee(): from Mee = %f to %f GeV/c^2", valmin, valmax), 10);
  // now with normalization (or not) as requested by fDoNormBinwidth and fDoNormNevents
  //TH1D* hProj     = (TH1D*) DoProjectionPtee(GetSpectrum2D(),     valmin, valmax, fDoNormBinwidth, fDoNormNevents);
  //TH1D* hProjLow  = (TH1D*) DoProjectionPtee(GetSpectrum2DLow(),  valmin, valmax, fDoNormBinwidth, fDoNormNevents);
  //TH1D* hProjHigh = (TH1D*) DoProjectionPtee(GetSpectrum2DHigh(), valmin, valmax, fDoNormBinwidth, fDoNormNevents);
  TH1D* hProj     = (TH1D*) DoProjectionPtee(GetSpectrum2D(),     valmin, valmax, fNormalisations);
  TH1D* hProjLow  = (TH1D*) DoProjectionPtee(GetSpectrum2DLow(),  valmin, valmax, fNormalisations);
  TH1D* hProjHigh = (TH1D*) DoProjectionPtee(GetSpectrum2DHigh(), valmin, valmax, fNormalisations);
  TGraphAsymmErrors *grProj = new TGraphAsymmErrors(hProj->GetNbinsX());
  for(Int_t i = 0; i < grProj->GetN(); ++i){
    grProj->SetPoint(i,hProj->GetBinCenter(i+1),hProj->GetBinContent(i+1));
    grProj->SetPointError(i,TMath::Abs(hProj->GetBinCenter(i+1) - hProj->GetXaxis()->GetBinLowEdge(i+1)),
                            TMath::Abs(hProj->GetBinCenter(i+1) - hProj->GetXaxis()->GetBinUpEdge (i+1)) ,
                            TMath::Abs(hProj->GetBinContent(i+1) - hProjLow ->GetBinContent(i+1)),
                            TMath::Abs(hProj->GetBinContent(i+1) - hProjHigh->GetBinContent(i+1)) );
                            // 0.3*hProj->GetBinContent(i+1),0.3*hProj->GetBinContent(i+1));
  }
  delete hProj; delete hProjLow; delete hProjHigh;
  // grProj->SetLineWidth(1);
  // grProj->SetMarkerColor(kBlack);
  // grProj->SetLineColor(kBlack);
  // grProj->SetMarkerStyle(20);
  // grProj->SetFillStyle(0);
  grProj->SetLineWidth(0);
  grProj->SetMarkerColor(kGray);
  grProj->SetLineColor(kGray);
  grProj->SetFillColorAlpha(kGray+1,0.5);
  AttachSpectrumErr_Ptee(grProj);
}
//_______________________________________________________________________________________________
Bool_t LmCocktailPart::CheckAndDeleteOldProjections(Bool_t projOnMee){
  if (projOnMee==LmBaseSignal::kProjOnMee) {
    if(GetMaxBin_projMee()>-1) {
      fSpectrum_projMee.clear();
      fSpectrumErr_projMee.clear();
      return kTRUE;
    }
  }
  if (projOnMee==LmBaseSignal::kProjOnPtee) {
    if(GetMaxBin_projPtee()>-1) {
      fSpectrum_projPtee.clear();
      fSpectrumErr_projPtee.clear();
      return kTRUE;
    }
  }
  return kFALSE;
}
