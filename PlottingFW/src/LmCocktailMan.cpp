// c++ includes
#include <iostream>
using namespace std;
// ROOT includes
#include "TString.h"
#include "TObjArray.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TF1.h"
// project includes
#include "LmCocktailMan.h"
#include "LmBaseSignal.h"
#include "LmHelper.h"

int debugCocktailMan=0;

//_______________________________________________________________________________________________
LmCocktailMan::LmCocktailMan() :
fMeeIsOnXaxis(kTRUE),
fUndoBinwidthNormalizationMee(kFALSE),
fDoNormMidRap(kFALSE),
fType(0),
fTypename(""),
fsHistForNevents(""),
fsInputfilesLow(""),
fsInputhistsLow(""),
fsInputfilesHigh(""),
fsInputhistsHigh(""),
fsRelUncertainties(""),
fhMeePteeLow(),
fhMeePteeHigh(),
fArbitraryScaling(1.)
{
  LmHelper::Debug("LmCocktailMan default constructor", 5-debugCocktailMan);
  // initialize inherited variables:
  SetEnableRebinning(kFALSE);
}

//_______________________________________________________________________________________________
LmCocktailMan::LmCocktailMan(TString InFiles,TString InHistNames,Int_t Ndim,Int_t nRebinM,const Double_t *newBinsM,Int_t nRebinPt,const Double_t *newBinsPt,TString NeventsHistNames) :
fMeeIsOnXaxis(kTRUE),
fUndoBinwidthNormalizationMee(kFALSE),
fDoNormMidRap(kFALSE),
fType(0),
fTypename(""),
fsInputfilesLow(""),
fsInputhistsLow(""),
fsInputfilesHigh(""),
fsInputhistsHigh(""),
fsRelUncertainties(""),
fhMeePteeLow(),
fhMeePteeHigh(),
fArbitraryScaling(1.)
{
  LmHelper::Debug("LmCocktailMan constructor", 5-debugCocktailMan);
  SetInputfiles(InFiles.Data());
	  SetInputhistAndDim(InHistNames.Data(), Ndim); // 2D
	  SetHistForNevents(NeventsHistNames.Data());
  SetRebinning2D(nRebinM,newBinsM,nRebinPt,newBinsPt);
}

//_______________________________________________________________________________________________
LmCocktailMan::~LmCocktailMan()
{
  LmHelper::Debug("LmCocktailMan destructor", 5-debugCocktailMan);
}


//_______________________________________________________________________________________________
void LmCocktailMan::SetType(Int_t type) {
  fType = type;
  switch (fType) {
    case kUndef:        fTypename="Undef";      break;
    case kResonances:   fTypename="Resonances"; break;
    case kLFsum:        fTypename="LFsum";      break;
    case kJpsi:         fTypename="Jpsi";       break;
    case kHeavyFl:      fTypename="HeavyFl";    break;
    case kVirtGamma:    fTypename="VirtGamma";  break;
    case kRappMee:      fTypename="Rapp";       break;
    case kRappPtee:     fTypename="RappPtee";   break;
    case kFromFileMee:  fTypename="FileMee";    break;
    case kFromFilePtee: fTypename="FilePtee";   break;		      
    default:            fTypename=Form("Type%i",type); break;
  }
  if (fName.size()==0) SetName(GetTypename());
}


//_______________________________________________________________________________________________
Int_t LmCocktailMan::Process(Int_t type, Bool_t recursive)
{
  if (!recursive) SetType(type);
  LmHelper::Debug(Form("LmCocktailMan Process(type=%i) [name='%s']", type, GetName()), 5-debugCocktailMan);

  if (fNdimInput!=2 && type!=kRappMee && type!=kRappPtee && type!=kFromFileMee && type!=kFromFilePtee) { LmHelper::Error(Form("LmCocktailMan('%s'): invalid input dimension given.", GetName())); return 1; }

    switch (type) {
    case kResonances:
      GetHistogramsFromFiles2D(kAdd);
      GetHistogramsFromFiles2D(kAdd, -1); // Low syst
      GetHistogramsFromFiles2D(kAdd, +1); // High syst
      FindMeeAxisIn2DHist(fhMeePtee.at(0), 1.5); // use Pion for check, but allow for smearing up to 1.5 GeV/c2.
      LmHelper::Debug((fMeeIsOnXaxis)?Form(" Cocktail Mass axis is: X") :Form(" Cocktail Mass axis is: Y"), 10-debugCocktailMan);
      if (!fMeeIsOnXaxis) FlipAxes();
      break;

    case kLFsum:
      Process(kResonances, kTRUE);
      CalcSumAndClearOthers("LFsum");
      break;

    case kJpsi:
      GetHistogramsFromFiles2D(kAdd);
      GetHistogramsFromFiles2D(kAdd, -1); // Low syst
      GetHistogramsFromFiles2D(kAdd, +1); // High syst
      LmHelper::Debug((fMeeIsOnXaxis)?Form(" Cocktail Mass axis is: X") :Form(" Cocktail Mass axis is: Y"), 10-debugCocktailMan);
      break;

    case kHeavyFl:
      GetHistogramsFromFiles2D(kOneByOne);
      GetHistogramsFromFiles2D(kOneByOne, -1); // Low syst
      GetHistogramsFromFiles2D(kOneByOne, +1); // High syst
      //CalcNeventsHF(); // Now done in GetHistogramsFromFiles2D().
      break;

    case kHFsum:
      Process(kHeavyFl, kFALSE);
      CalcSumAndClearOthers("HFsum");
      break;

    case kVirtGamma:
      GetHistogramsFromFiles2D(kAdd);
      GetHistogramsFromFiles2D(kAdd, -1); // Low syst
      GetHistogramsFromFiles2D(kAdd, +1); // High syst
      break;

    case kRappMee:
      if (GetNdimInput()==1) GetHistogramsRapp1D_Mee();
      if (GetNdimInput()==2) GetHistogramsRapp2D();
      break;

    case kRappPtee:
      if (GetNdimInput()==1) GetHistogramsRapp1D_Ptee();
      if (GetNdimInput()==2) GetHistogramsRapp2D();
      break;

    case kFromFileMee:
      if (GetNdimInput()==1) GetHistogramsFromFiles1D(kTRUE);
      break;
    case kFromFilePtee:
      if (GetNdimInput()==1) GetHistogramsFromFiles1D(kFALSE);
      break;


    default:
      break;
  }

  if (fhMeePtee.size()<1) { LmHelper::Error(Form("LmCocktailMan('%s'): Cocktail empty.", GetName())); return 2; }

  if (recursive || type==kHFsum) return 0;
  // Put things below which shall be called only for non-recursive Process() calls, otherwise they are executed more than once!

  for (unsigned int i=0; i<fhMeePtee.size(); i++) {
    // set new titles:
    TString sTitleContent = Form("d#it{N}/d%sd%s (a.u.)", LmBaseSignal::GetProjLabelXvar().Data(), LmBaseSignal::GetProjLabelYvar().Data());
    fhMeePtee.at(i)->SetTitle(Form("%s;%s;%s;%s",fhMeePtee.at(i)->GetName(),LmBaseSignal::GetProjLabelX().Data(),LmBaseSignal::GetProjLabelY().Data(),sTitleContent.Data()));
    if (GetSpectrumILow(i))  fhMeePteeLow.at(i) ->SetTitle(Form("%s;%s;%s;%s",fhMeePtee.at(i)->GetName(),LmBaseSignal::GetProjLabelX().Data(),LmBaseSignal::GetProjLabelY().Data(),sTitleContent.Data()));
    if (GetSpectrumIHigh(i)) fhMeePteeHigh.at(i)->SetTitle(Form("%s;%s;%s;%s",fhMeePtee.at(i)->GetName(),LmBaseSignal::GetProjLabelX().Data(),LmBaseSignal::GetProjLabelY().Data(),sTitleContent.Data()));
  }

//  TH2D* hist = fhMeePtee[0];
//  LmHelper::Debug(" LmCocktailMan::Process()", 3);
//  LmHelper::Debug(Form(" |-> title: %s,   x: %s,   y: %s,   z: %s", hist->GetTitle(), hist->GetXaxis()->GetTitle(), hist->GetYaxis()->GetTitle(), hist->GetZaxis()->GetTitle()), 3);

  if (fUndoBinwidthNormalizationMee) {
    Double_t binwidth = fhMeePtee.at(0)->GetXaxis()->GetBinWidth(1);
    LmHelper::Info(Form("LmCocktailMan('%s'): undo scaling of input cocktail histograms by 1./binwidth_Mee! -> scale by %f     - make sure this is correct!", GetName(), binwidth));
    for (unsigned int i=0; i<fhMeePtee.size(); i++) {
      fhMeePtee.at(i)->Scale(binwidth);
      if (GetSpectrumILow(i))  fhMeePteeLow.at(i) ->Scale(binwidth);
      if (GetSpectrumIHigh(i)) fhMeePteeHigh.at(i)->Scale(binwidth);
    }
  }
  if (fArbitraryScaling!=1.) {
    LmHelper::Warning(Form("LmCocktailMan('%s'): arbitrary scaling of input cocktail histograms! -> scale by %f     - make sure this is correct!", GetName(), fArbitraryScaling));
    for (unsigned int i=0; i<fhMeePtee.size(); i++) {
      fhMeePtee.at(i)->Scale(fArbitraryScaling);
      if (GetSpectrumILow(i))  fhMeePteeLow.at(i) ->Scale(fArbitraryScaling);
      if (GetSpectrumIHigh(i)) fhMeePteeHigh.at(i)->Scale(fArbitraryScaling);
    }
  }

  if (fEnableRebinning) Rebin2DHistogram_all();
  return 0;
}


//_______________________________________________________________________________________________
void LmCocktailMan::RemoveEntry(unsigned int i_spec)
{
  fhMeePtee    .erase(fhMeePtee.begin()+i_spec);
  fhMeePteeLow .erase(fhMeePteeLow.begin()+i_spec);
  fhMeePteeHigh.erase(fhMeePteeHigh.begin()+i_spec);
}


//_______________________________________________________________________________________________
void LmCocktailMan::GetHistogramsFromFiles1D(Bool_t IsMee)
{
  /// This function will just create a flat pair-pt shape, so use its results ONLY for integrated mass spectra!
  /// Rapps input (quote): Pair yield is computed for y=[-1,1] and normalized as dN/(dMdy) / (dNch/dy) in [1/GeV].
  ///
  TObjArray* oaLists = fsInputlists.Tokenize(":"); // each token for a textfile column definition like: "%lg %*lg %lg"
  TObjArray* oaHists = fsInputhists.Tokenize(":"); // histnames like: "HGvac:HGmed:HGdrop:QGP"

  Int_t n_bins_mee    = fBinsRebin_Mee.size()-1;
  Double_t* bins_mee  = fBinsRebin_Mee.data();
  Int_t n_bins_ptee   = fBinsRebin_Ptee.size()-1;
  Double_t* bins_ptee = fBinsRebin_Ptee.data();

  for (Int_t ihist=0; ihist<oaHists->GetEntries(); ihist++) {
    TGraph* fGr1D = (TGraph*) TGraph(fsInputfiles.Data(), oaLists->At(ihist)->GetName()).Clone( oaHists->At(ihist)->GetName() );
    TH2D* fH2D  = new TH2D(fGr1D->GetName(), fGr1D->GetName(), n_bins_mee, bins_mee, n_bins_ptee, bins_ptee);
    fH2D->SetTitle(";m_{ee};p_{t,ee}");

    double x[] = { 0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.7,0.8,0.9,1.0};
    double y[] = { 0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.7,0.8,0.9,1.0};
    TF1 f1("f",[&](double *x, double *){ return fGr1D->Eval(x[0]); },0.0001,1.0,0);
    double integral = f1.Integral(0.15,0.6);
    std::cout << fsInputfiles.Data() << "  brems integral  " << integral  << std::endl;  
    Double_t x_val = 0, z_val = 0;
    for (Int_t m_i = 1; m_i <= fH2D->GetNbinsX(); m_i++) {
      for (Int_t p_i = 1; p_i <= fH2D->GetNbinsY(); p_i++) {
        if(IsMee) x_val = fH2D->GetXaxis()->GetBinCenter(m_i);
	else      x_val = fH2D->GetYaxis()->GetBinCenter(p_i);
        // 1D:
        z_val = fGr1D->Eval(x_val); // linear inter- and extrapolation.
        //std::cout << "Brems: " << x_val << "  " << z_val <<std::endl;	
        if(IsMee) z_val *= fH2D->GetXaxis()->GetBinWidth(m_i); 
	else      z_val *= fH2D->GetYaxis()->GetBinWidth(p_i); 
        fH2D->SetBinContent(m_i, p_i, z_val);
      }
      
    }
    //for (Int_t p_i = 1; p_i <= fH2D->GetNbinsY(); p_i++)
    //  std::cout << "x_val: " << x_val << " rapp_val: " << z_val << "  " << z_val / fH2D->GetYaxis()->GetBinWidth(p_i) << std::endl;
    fhMeePtee.push_back(fH2D);
  }
}



//_______________________________________________________________________________________________
void LmCocktailMan::GetHistogramsRapp1D_Mee()
{
  /// This function will just create a flat pair-pt shape, so use its results ONLY for integrated mass spectra!
  /// Rapps input (quote): Pair yield is computed for y=[-1,1] and normalized as dN/(dMdy) / (dNch/dy) in [1/GeV].
  ///
  TObjArray* oaLists = fsInputlists.Tokenize(":"); // each token for a textfile column definition like: "%lg %*lg %lg"
  TObjArray* oaHists = fsInputhists.Tokenize(":"); // histnames like: "HGvac:HGmed:HGdrop:QGP"

  Int_t n_bins_mee    = fBinsRebin_Mee.size()-1;
  Double_t* bins_mee  = fBinsRebin_Mee.data();
  Int_t n_bins_ptee   = fBinsRebin_Ptee.size()-1;
  Double_t* bins_ptee = fBinsRebin_Ptee.data();

  for (Int_t ihist=0; ihist<oaHists->GetEntries(); ihist++) {
    TGraph* fGr1D = (TGraph*) TGraph(fsInputfiles.Data(), oaLists->At(ihist)->GetName()).Clone( oaHists->At(ihist)->GetName() );
    TH2D* fH2D  = new TH2D(fGr1D->GetName(), fGr1D->GetName(), n_bins_mee, bins_mee, n_bins_ptee, bins_ptee);
    fH2D->SetTitle(";m_{ee};p_{t,ee}");

    
    double x[] = { 0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.7,0.8,0.9,1.0};
    double y[] = { 0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.7,0.8,0.9,1.0};
    TF1 f1("f",[&](double *x, double *){ return fGr1D->Eval(x[0]); },0.000,1.0,0);
    double integral = f1.Integral(0.15,0.6);
    std::cout << fsInputfiles.Data() << "  rapp mee  integral  " << integral * 57.8 * 7 << std::endl;  


    Double_t m_val = 0, z_val = 0;
    //cout << "interpolating to new bins: " << fGr1D->GetName() << "   n_bins_ptee = " << n_bins_ptee << endl;
    for (Int_t m_i = 1; m_i <= fH2D->GetNbinsX(); m_i++) {
      for (Int_t p_i = 1; p_i <= fH2D->GetNbinsY(); p_i++) {
        m_val = fH2D->GetXaxis()->GetBinCenter(m_i);
        // 1D:
        z_val = fGr1D->Eval(m_val); // linear inter- and extrapolation.
        fH2D->SetBinContent(m_i, p_i, z_val/1.6 * fH2D->GetXaxis()->GetBinWidth(m_i));
      }
      //std::cout << "m_val: " << m_val << " rapp_val: " << z_val << "  " << z_val * fH2D->GetXaxis()->GetBinWidth(m_i) << std::endl;
    }
    fhMeePtee.push_back(fH2D);
  }
}


//_______________________________________________________________________________________________
void LmCocktailMan::GetHistogramsRapp1D_Ptee()
{
  /// This function will just create a flat pair-pt shape, so use its results ONLY for integrated mass spectra!
  /// Rapps input (quote): Pair yield is computed for y=[-1,1] and normalized as dN/(dMdy) / (dNch/dy) in [1/GeV].
  ///
  TObjArray* oaLists = fsInputlists.Tokenize(":"); // each token for a textfile column definition like: "%lg %*lg %lg"
  TObjArray* oaHists = fsInputhists.Tokenize(":"); // histnames like: "HGvac:HGmed:HGdrop:QGP"

  Int_t n_bins_mee    = fBinsRebin_Mee.size()-1;
  Double_t* bins_mee  = fBinsRebin_Mee.data();
  Int_t n_bins_ptee   = fBinsRebin_Ptee.size()-1;
  Double_t* bins_ptee = fBinsRebin_Ptee.data();

  for (Int_t ihist=0; ihist<oaHists->GetEntries(); ihist++) {
    TGraph* fGr1D = (TGraph*) TGraph(fsInputfiles.Data(), oaLists->At(ihist)->GetName()).Clone( oaHists->At(ihist)->GetName() );
    TH2D* fH2D  = new TH2D(fGr1D->GetName(), fGr1D->GetName(), n_bins_mee, bins_mee, n_bins_ptee, bins_ptee);
    fH2D->SetTitle(";m_{ee};p_{t,ee}");

    double x[] = { 0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.7,0.8,0.9,1.0};
    double y[] = { 0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.7,0.8,0.9,1.0};
    TF1 f1("f",[&](double *x, double *){ return fGr1D->Eval(x[0])* x[0]; },0.000,1.0,0);
    double integral = f1.Integral(0.,0.5);
    std::cout << fsInputfiles.Data() << "  rapp ptee integral  " << integral * 57.8 * 7 << std::endl;  



    Double_t m_val = 0, z_val = 0;
    //cout << "interpolating to new bins: " << fGr1D->GetName() << "   n_bins_ptee = " << n_bins_ptee << endl;
    for (Int_t m_i = 1; m_i <= fH2D->GetNbinsX(); m_i++) {
      for (Int_t p_i = 1; p_i <= fH2D->GetNbinsY(); p_i++) {
	m_val = fH2D->GetYaxis()->GetBinCenter(p_i);
        z_val = fGr1D->Eval(m_val); // linear inter- and extrapolation.
        z_val *= m_val;
        fH2D->SetBinContent(m_i, p_i, z_val * fH2D->GetYaxis()->GetBinWidth(p_i));
      }
      //std::cout << "m_val: " << m_val << " rapp_val: " << z_val << "  " << z_val * fH2D->GetXaxis()->GetBinWidth(m_i) << std::endl;
    }
    fhMeePtee.push_back(fH2D);
  }
}





//_______________________________________________________________________________________________
void LmCocktailMan::GetHistogramsRapp2D()
{
  /// This function was not tested yet (March 2017), or this comment never updated.
  /// Rapps input (quote):
  ///
  TObjArray* oaLists = fsInputlists.Tokenize(":"); // each token for a textfile column definition like: "%lg %lg %*lg %lg"
  TObjArray* oaHists = fsInputhists.Tokenize(":"); // histnames like: "HGvac:HGmed:HGdrop:QGP"

  Int_t n_bins_mee    = fBinsRebin_Mee.size()-1;
  Double_t* bins_mee  = fBinsRebin_Mee.data();
  Int_t n_bins_ptee   = fBinsRebin_Ptee.size()-1;
  Double_t* bins_ptee = fBinsRebin_Ptee.data();

  for (Int_t ihist=0; ihist<oaHists->GetEntries(); ihist++) {
    TGraph2D* fGr2D = (TGraph2D*) TGraph2D(fsInputfiles.Data(), oaLists->At(ihist)->GetName()).Clone( oaHists->At(ihist)->GetName() );
    TH2D* fH2D  = new TH2D(fGr2D->GetName(), fGr2D->GetName(), n_bins_mee, bins_mee, n_bins_ptee, bins_ptee);
    fH2D->SetTitle(";m_{ee};p_{t,ee}");

    Double_t m_val = 0, p_val = 0, z_val = 0;
    cout << "interpolating to new bins: " << fGr2D->GetName() << "   n_bins_ptee = " << n_bins_ptee << endl;
    for (Int_t m_i = 1; m_i <= fH2D->GetNbinsX(); m_i++) {
      cout << m_i << " of " << fH2D->GetNbinsX() << endl;
      for (Int_t p_i = 1; p_i <= fH2D->GetNbinsY(); p_i++) {
        m_val = fH2D->GetXaxis()->GetBinCenter(m_i);
        p_val = fH2D->GetYaxis()->GetBinCenter(p_i);
        //			cout << "m_val, p_val = " << m_val << " , " << p_val << endl;
        // 2D:
        //if (bExtrap && m_val>1.4) fQGPslope->Interpolate(p_val, m_val); // the input Graphs have switched x and y axis!!!
        //else
        if (m_val>1.5) z_val = 0;
        else {
          z_val = fGr2D->Interpolate(p_val, m_val);	// the input Graphs have switched x and y axis!!!
          // change normalization from "dN/(dM qt dqt dy) [GeV^{-3}]" to "dN/(dM dqt dy) [GeV^{-2}]"
          z_val = z_val * p_val;
        }
        fH2D->SetBinContent(m_i, p_i, z_val * fH2D->GetXaxis()->GetBinWidth(m_i) * fH2D->GetYaxis()->GetBinWidth(p_i) ); // Doublecheck the binwidth normalization!
      }
    }
    fhMeePtee.push_back(fH2D);
  }
}


//_______________________________________________________________________________________________
void LmCocktailMan::GetHistogramsFromFiles2D(Int_t setting, Int_t doSys)
{
  LmHelper::Debug(Form(" GetHistogramsFromFiles2D(setting=%i, doSys=%i)",setting,doSys), 5-debugCocktailMan);

  // Avoid to fill systematics vectors with the default input, because then HasSystematics() would always return true.
  if (doSys!=0 && fsRelUncertainties.IsNull() && !HasValidSysInput()) return;
  LmHelper::Debug(Form(" relUncert = %s, validSysInput = %s",fsRelUncertainties.Data(),HasValidSysInput()?"kTRUE":"kFALSE"), 10-debugCocktailMan);

  // default:
  std::vector<TH2D*> *fhMeePteePtr = &fhMeePtee; // Set local pointer to one of the global vectors.
  TString inputfiles = fsInputfiles;
  TString inputhists = fsInputhists;
  // systematics:
  if (doSys==-1) {
    fhMeePteePtr = &fhMeePteeLow;
    if (HasValidSysInput()) {
      inputfiles   = fsInputfilesLow;
      inputhists   = fsInputhistsLow;
    }
  }
  if (doSys==+1) {
    fhMeePteePtr = &fhMeePteeHigh;
    if (HasValidSysInput()) {
      inputfiles   = fsInputfilesHigh;
      inputhists   = fsInputhistsHigh;
    }
  }

  std::cout << std::endl;
  std::cout << "Cocktail histos: " << inputhists << std::endl;
  fhMeePteePtr->clear();
  LmHelper::Debug(Form("  using file(s): %s",inputfiles.Data()), 5-debugCocktailMan);
  TObjArray* oaFiles =   inputfiles.Tokenize(":");
  TObjArray* oaLists = fsInputlists.Tokenize(":");
  TObjArray* oaHists =   inputhists.Tokenize(":");
  if (oaFiles->GetEntries() > oaLists->GetEntries()) {
    LmHelper::Warning(Form("LmCocktailMan('%s'): more input files than input lists. Using last list for each extra file.", GetName()));
    for (int i=oaLists->GetEntries(); i<oaFiles->GetEntries(); i++) fsInputlists.Append(Form(":%s",oaLists->Last()->GetName()));
    delete oaLists;
    oaLists = fsInputlists.Tokenize(":");
  }

  std::vector<Double_t> relUncert = GetRelUncertainties(doSys, oaHists->GetEntries());

  // Shortcut: if systematics are only given via numbers, reuse the original histograms instead of reading the same file(s) again.
  if (!HasValidSysInput() && doSys!=0) {
    LmHelper::Debug(Form("  perform shortcut"), 6-debugCocktailMan);
    for (UInt_t i=0; i<fhMeePtee.size(); i++) {
      TH2D* hTemp = (TH2D*) fhMeePtee.at(i)->Clone(/*Form("%s_%s_%i",fhMeePtee.at(i)->GetName(),(doSys==-1)?"Low":"High",i)*/);
      hTemp->Scale( 1.+relUncert.at(i) ); // Scale by relative uncertainty.
      fhMeePteePtr->push_back(hTemp);
    }
    return;
  }

  switch (setting) {
    case kAdd:
      // each rootfile shall contain the same histograms (e.g. same cocktail spectra for different centralities).
      // loop over all rootfiles and add the corresponding histograms from each file. store the summed ones in the vector 'fhMeePtee'.
      // each histogram is scaled by 1./(number_of_files), assuming that all files correspond to equal centrality percentiles!
      LmHelper::Debug(Form("  perform kAdd"), 6-debugCocktailMan);
      if (oaFiles->GetEntries()>1)
        LmHelper::Info(Form("LmCocktailMan('%s'): scale cocktail histograms by 1./nfiles: %f", GetName(), 1./oaFiles->GetEntries()));
      for (int filei=0; filei<oaFiles->GetEntries(); filei++)
      {
        TFile* _file = LmHelper::SafelyOpenRootfile(oaFiles->At(filei)->GetName());
        if (!_file) return;
        TList* llist  = LmHelper::GetList(_file, oaLists->At(filei)->GetName());
        TList* lHists = LmHelper::SelectHistosList(llist, inputhists, kTRUE); // kTRUE means exact match of name needed. Can be overruled by using '*' in fsInputhists.
        for (int posi=0; posi<lHists->GetEntries(); posi++)
        {
	  std::cout << "histo: " << lHists->At(posi)->GetName() << "  " << relUncert.at(posi)  << std::endl;
          TH2D* hTemp = (TH2D*) lHists->At(posi)->Clone();
          hTemp->Scale( 1./oaFiles->GetEntries() * (1.+relUncert.at(posi)) ); // Scale by relative uncertainty and number of files.
          if (filei==0) { fhMeePteePtr->push_back(hTemp); }
          else          { fhMeePteePtr->at(posi)->Add(hTemp); }
        }
        // -----
        // Get Nevents here to save time for opening rootfile and list again...
        // Since the number of simulated events may be different for Std, Low and High (failed jobs etc), it is
        // best to normalize the histograms per event, if this was not already done.
        Double_t Nevents = CalcNevents(llist, 0);
        std::cout << "wewewewewwww" << Nevents << std::endl;
        for (int i = 0; i < lHists->GetEntries(); ++i){
          fhMeePteePtr->at(i)->Scale(1./Nevents); // Scale every cocktail source with number of events
        }
        // fhMeePteePtr->back()->Scale(1./Nevents);
        // -----
        LmHelper::DeleteList(lHists);
        LmHelper::DeleteList(llist); // Theo reported that systematics don't work if all histograms are in one file. Small update done in DeleteList().
        _file->Close();
      }
      break;

    case kOneByOne:
      // each rootfile shall contain a certain histogram. (one-to-one relation in 'oaFiles' and 'oaHists')
      // loop over all rootfiles and get the specified histogram. append each of them to the vector 'fhMeePtee'.
      // no scaling is applied at this stage, should be done in LmCocktail class if needed.
      // If 'fsInputhists' contains a '-', e.g. 'hMeePtee_ULS-hMeePtee_LS', then the second histogram will be subtracted.
      LmHelper::Debug(Form("  perform kOneByOne"), 6-debugCocktailMan);
      if (oaFiles->GetEntries() != oaHists->GetEntries()) { LmHelper::Error(Form("LmCocktailMan('%s'): unequal number of input files and histograms.", GetName())); return; }
      for (int posi=0; posi<oaFiles->GetEntries(); posi++)
      {
        TFile* _file  = LmHelper::SafelyOpenRootfile(oaFiles->At(posi)->GetName());
        if (!_file){ return;}
        TList* llist  = LmHelper::GetList(_file, oaLists->At(posi)->GetName());
        TList* lHists = LmHelper::SelectHistosList(llist, oaHists->At(posi)->GetName(), kTRUE, "-"); // kTRUE means exact match of name needed. Use '-' as delimiter.
        TH2D*  hTemp  = (TH2D*) lHists->At(0)->Clone();
	std::cout << "hist: " << hTemp->GetMaximum() << std::endl; 
        if (lHists->GetEntries()>1) hTemp->Add( (TH2D*) lHists->At(1), -1); // Subtract Like Sign histogram if specified.
        hTemp->Scale( 1.+relUncert.at(posi) ); // Scale by relative uncertainty.
	std::cout << "HF unc: " << relUncert.at(posi) << std::endl; 
        if ( TString(_file->GetName()).Contains("charm", TString::kIgnoreCase) ){std::cout << "naming charm" <<std::endl;  hTemp->SetName("charm");}
        if ( TString(_file->GetName()).Contains("beauty", TString::kIgnoreCase) ) hTemp->SetName("beauty");
        fhMeePteePtr->push_back(hTemp);
        // -----
        // Get Nevents here to save time for opening rootfile and list again...
        // Since the number of simulated events may be different for Std, Low and High (failed jobs etc), it is
        // best to normalize the histograms per event, if this was not already done.
        Double_t Nevents = CalcNevents(llist, posi);
        fhMeePteePtr->back()->Scale(1./Nevents);
        // -----
        LmHelper::DeleteList(lHists);
        LmHelper::DeleteList(llist);
        _file->Close();
      }
      break;

    default:
      break;
  } // switch
}


//_______________________________________________________________________________________________
void LmCocktailMan::CalcSumAndClearOthers(const char* histname)
{
  LmHelper::Debug(" CalcSumAndClearOthers()", 5-debugCocktailMan);
  TH2D *hLFsum = (TH2D*) fhMeePtee.at(0)->Clone(histname);
  Int_t i =0;
  for(std::vector<TH2D*>::iterator it = fhMeePtee.begin()+1; it != fhMeePtee.end(); ++it){
     hLFsum->Add(*it);
     std::cout << "CalcSum: "  << i++ << std::endl;
  }
  fhMeePtee.clear(); // remove all contents
  fhMeePtee.push_back(hLFsum);
  if (HasSystematics()) {
    TH2D *hLFsumLow  = (TH2D*) fhMeePteeLow.at(0) ->Clone(Form("%c_Low",histname));
    TH2D *hLFsumHigh = (TH2D*) fhMeePteeHigh.at(0)->Clone(Form("%c_High",histname));
    for (UInt_t i=1; i<fhMeePteeLow.size(); i++) {
      hLFsumLow ->Add(fhMeePteeLow.at(i));
      hLFsumHigh->Add(fhMeePteeHigh.at(i));
    }
    fhMeePteeLow.clear();
    fhMeePteeHigh.clear();
    fhMeePteeLow.push_back(hLFsumLow);
    fhMeePteeHigh.push_back(hLFsumHigh);
  }
}


//_______________________________________________________________________________________________
Double_t LmCocktailMan::CalcNevents(TList* llist, Int_t posi)
{
  /// Please check in sourcecode which histogram types are foreseen and if GetBinContent(1) or GetEntries() is used.
  LmHelper::Debug(" CalcNevents()", 5-debugCocktailMan);
  Double_t Nevents = 1.;
  TObjArray* oaHistsNevents = fsHistForNevents.Tokenize(":");
  if(oaHistsNevents->GetEntries()==0 || TString( oaHistsNevents->At(posi)->GetName() ).EqualTo("NONE", TString::kIgnoreCase)){
    return 1.;
  }
  TList* lHistsNevents = LmHelper::SelectHistosList(llist, oaHistsNevents->At(posi)->GetName(), kTRUE); // kTRUE means exact match of name needed.
  LmHelper::Debug(Form("  get Nevents from hist : %s", lHistsNevents->At(0)->GetName()), 4-debugCocktailMan);
  if (lHistsNevents->At(0)->IsA()==TH2F::Class() || lHistsNevents->At(0)->IsA()==TH2D::Class()) {
    LmHelper::Debug("2D extraction", 4-debugCocktailMan);
    Nevents = ((TH2*) lHistsNevents->At(0))->GetEntries();
  }
  else if (lHistsNevents->At(0)->IsA()==TH1F::Class() || lHistsNevents->At(0)->IsA()==TH1D::Class()) {
    LmHelper::Debug("1D extraction", 4-debugCocktailMan);
    Nevents = ((TH1*) lHistsNevents->At(0))->GetBinContent(1);
    if(fDoNormMidRap == kTRUE){
      Nevents = ((TH1*) lHistsNevents->At(0))->Integral(((TH1*) lHistsNevents->At(0))->FindBin(-0.5),((TH1*) lHistsNevents->At(0))->FindBin(0.5)-1);
    }
    else if (Nevents == 0 || Nevents < 10000) {
      LmHelper::Debug("full", 4-debugCocktailMan); 
      Nevents = ((TH1*) lHistsNevents->At(0))->GetEntries(); 
    }
  }
  LmHelper::Debug(Form("  Nevents = %.2f", Nevents), 4-debugCocktailMan);
  LmHelper::DeleteList(lHistsNevents);
  return Nevents;
}


//_______________________________________________________________________________________________
Bool_t LmCocktailMan::HasValidSysInput()
{
  Int_t nfiles     = (fsInputfiles.Tokenize(":"))->GetEntries();
  Int_t nhists     = (fsInputhists.Tokenize(":"))->GetEntries();
  Int_t nfilesLow  = (fsInputfilesLow.Tokenize(":"))->GetEntries();
  Int_t nhistsLow  = (fsInputhistsLow.Tokenize(":"))->GetEntries();
  Int_t nfilesHigh = (fsInputfilesHigh.Tokenize(":"))->GetEntries();
  Int_t nhistsHigh = (fsInputhistsHigh.Tokenize(":"))->GetEntries();
  LmHelper::Debug(Form(" HasValidSysInput(): nfiles=%d, nfilesLow=%d, nfilesHigh=%d, nhists=%d, nhistsLow=%d, nhistsHigh=%d",nfiles,nfilesLow,nfilesHigh,nhists,nhistsLow,nhistsHigh), 10-debugCocktailMan);
  if (nfilesLow == nfiles && nfilesHigh == nfiles && nhistsLow == nhists && nhistsHigh == nhists) return kTRUE;
  return kFALSE;
}


//_______________________________________________________________________________________________
std::vector<Double_t> LmCocktailMan::GetRelUncertainties(Int_t doSys, Int_t nSpectra)
{
  LmHelper::Debug(" GetRelUncertainties()", 10-debugCocktailMan);
  std::vector<Double_t> relUncert;
  TObjArray* oaRelUncert = fsRelUncertainties.Tokenize(":");

  if (oaRelUncert->GetEntries()>0 && HasValidSysInput())
    LmHelper::Warning(Form("LmCocktailMan('%s'): systematic uncertainties are given via extra files AND via numbers. Will use both!", GetName()));

  // In any case, create one value per input spectrum for easy further handling.
  for (int iSpec=0; iSpec<nSpectra; iSpec++) {
    // case 1: Default input or no given numeric uncertainties.
    if (doSys==0 || oaRelUncert->GetEntries()==0) {
      relUncert.push_back(0.);
      continue;
    }
    // case 2: Same value for all systematics.
    if (oaRelUncert->GetEntries()==1) {
      if (doSys==+1) relUncert.push_back(    atof( oaRelUncert->At(0)->GetName() ));
      if (doSys==-1) relUncert.push_back(-1.*atof( oaRelUncert->At(0)->GetName() ));
      continue;
    }
    // case 3: Upper and lower values given with "+0.2:-0.1[:+0.3:-0.3:...]".
    //         If there are more spectra than value pairs, the last value pair will be used for all further spectra.
    if (oaRelUncert->GetEntries() >= (iSpec+1)*2) {
      if (doSys==+1) relUncert.push_back(atof( oaRelUncert->At(iSpec*2  )->GetName() )); // entry 0, 2, 4, ...
      if (doSys==-1) relUncert.push_back(atof( oaRelUncert->At(iSpec*2+1)->GetName() )); // entry 1, 3, 5, ...
      continue;
    }
    else {
      relUncert.push_back( relUncert.back() ); // Duplicate the last element.
      continue;
    }
  }
  //  for (unsigned int j=0; j<relUncert.size(); j++) {
  //    cout << relUncert.at(j) << ", " << flush;
  //  } cout << endl;
  LmHelper::Debug(" GetRelUncertainties() done", 12-debugCocktailMan);
  return relUncert;
}


//_______________________________________________________________________________________________
void LmCocktailMan::FindMeeAxisIn2DHist(TH2D* hIn, Double_t mass)
{
  Int_t    x_bin = -1;
  Double_t x_max = -100;
  x_bin = hIn->FindLastBinAbove(0., 1); //last bin with entries. axis 1=x, 2=y
  x_max = hIn->GetXaxis()->GetBinLowEdge(x_bin/* +1 */); // without +1 we get the bin which includes the physical mass limit, so the low edge is still below.
  Int_t    y_bin = -1;
  Double_t y_max = -100;
  y_bin = hIn->FindLastBinAbove(0., 2); //last bin with entries. axis 1=x, 2=y
  y_max = hIn->GetYaxis()->GetBinLowEdge(y_bin/* +1 */); // without +1 we get the bin which includes the physical mass limit, so the low edge is still below.

  if (x_max<=mass) {
    if (y_max>mass) { fMeeIsOnXaxis=kTRUE; return; }
    else            LmHelper::Warning(Form("LmCocktailMan('%s'): determination of Mass axis not conclusive! (no statistics at high-pT) [case 1] fMeeIsOnXaxis=%i", GetName(),fMeeIsOnXaxis));
  }
  if (y_max<=mass) {
    if (x_max>mass) { fMeeIsOnXaxis=kFALSE; return; }
    else            LmHelper::Warning(Form("LmCocktailMan('%s'): determination of Mass axis not conclusive! (no statistics at high-pT) [case 2] fMeeIsOnXaxis=%i", GetName(),fMeeIsOnXaxis));
  }
  LmHelper::Error(Form("LmCocktailMan('%s'): determination of Mass axis not conclusive! (entries above mass limit) [case 3] fMeeIsOnXaxis=%i", GetName(),fMeeIsOnXaxis));
}


//_______________________________________________________________________________________________
void LmCocktailMan::FlipAxes()
{
  LmHelper::Debug(" FlipAxes()", 5-debugCocktailMan);
  LmHelper::Info(Form("LmCocktailMan('%s'): flipping X and Y axis of input histograms.     - make sure this is correct!", GetName()));
  for (unsigned int i=0; i<fhMeePtee.size(); i++) {
    LmHelper::FlipAxes2DHistogram(*fhMeePtee.at(i));
  }
  if(HasSystematics()){
    for (unsigned int i=0; i<fhMeePteeLow.size(); i++) {
      LmHelper::FlipAxes2DHistogram(*fhMeePteeLow.at(i));
      LmHelper::FlipAxes2DHistogram(*fhMeePteeHigh.at(i));
    }
  }
}


//_______________________________________________________________________________________________
void LmCocktailMan::Rebin2DHistogram_all()
{
  /// Rebin all 2D histograms according to binning given by LmRebinner::SetRebinning2D()/SetRebinningX()/SetRebinningY().
  /// Uses function LmRebinner::Rebin2DHistogram().
  LmHelper::Debug(" LmCocktailMan::Rebin2DHistogram_all()", 5-debugCocktailMan);

  for (unsigned int i=0; i<fhMeePtee.size(); i++) {
    Rebin2DHistogram(*fhMeePtee.at(i));
  }
  if(HasSystematics()){
    for (unsigned int i=0; i<fhMeePteeLow.size(); i++) {
      Rebin2DHistogram(*fhMeePteeLow.at(i));
      Rebin2DHistogram(*fhMeePteeHigh.at(i));
    }
  }
  LmHelper::Debug(" Rebin2DHistogram_all() done", 7-debugCocktailMan);
  return;
}
