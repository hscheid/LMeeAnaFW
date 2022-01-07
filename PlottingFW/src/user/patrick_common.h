#ifndef PATRICK_COMMON_H
#define PATRICK_COMMON_H
//_______________________________________________________________________________________________
// global variables
TString coll_system = "Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV";
TString inputhist   = "pInvMass_PairPt_PhivPair"; //"M_Pt_PhivPair_OpeningAngle";
Int_t   inputdim    = 3; // 3 or 4 doesnt matter...
TString projoption  = "yx"; // option="ab" means: a vertical, b horizontal (ROOT-convention)
// projection binning
std::vector<Double_t> binsPtee_forMee, binsPtee_forMee_sys, binsPtee_forPhiV;
std::vector<Double_t> binsMee_forPtee, binsMee_forPtee_sys, binsMee_forPhiV;
std::vector<Double_t> binsPhiV;
// plotting
Double_t plotMeeMin,  plotMeeMax,  plotMeeMax_sys;
Double_t plotPteeMin, plotPteeMax, plotPteeMax_sys;
Double_t plotPhiVMin, plotPhiVMax;
// switches and corresponding strings
Int_t   kDo4D, kUse16_4D, kDoCocktail, kUseLFsum, kUseHfeRaa, kUseRapp;
Int_t   kDoAOD , kDoSemi , kDoPt400, kDoOpAngle , kDoPhiV , kDoPref , kDoEffGen;
TString sOptAOD, sOptCent, sOptPt  , sOptOpAngle, sOptPhiV, sOptPref, sOptEff  ;
Bool_t  kDoEffiCorr;
Bool_t  kDoNormNevents, kDoNormBinwidth;
Bool_t  kDoSignifRaw;
Bool_t  kDoConfLevel;
Int_t   kDoSystematics;
Int_t   kWideMeeBins;
Bool_t  kDoRatio;
Bool_t  kDoLegend, kDoLogY;
Bool_t  plotCombineH, plotAverage, plotWeightAv;
Bool_t  writeFile;
TString sSelectedCut, sSelCutMaxStat;
Int_t   iSelectedCut, iSelCutMaxStat;
unsigned int histBitsPrint;
// files
TString filename2D_sys, filename2D_ana;
TString extpath_sys,    extpath_ana;
const   Int_t kLow=0,   kHig=1;
Bool_t  kReprocess;
Double_t  ratioPadSize;
Double_t  confLevel;
Int_t     debug;

//_______________________________________________________________________________________________
// binning
// Desired binning for output. Will also be used for efficiency correction.
// Binning has to be compatible with input. [PR/CK: see function GetVector() of Config_user_LMEEPbPb.C or LMEECutLib.C]
Double_t mee_bin[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10,  0.14,
  0.18, 0.26, 0.34,   // comment this line for a wide bin to check enhancement.
  0.50, 0.70, 1.10, 1.50, 2.10, 2.90, 3.10, 3.30, 4.00/*, 5.00*/ };
Double_t mee_bin_4D[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10,  0.14,
  0.18, 0.26, 0.34,   // comment this line for a wide bin to check enhancement.
  0.50, 0.70, 1.10, 1.50, 2.10, 2.90, /*3.00,*/ 3.05, 3.10, 3.15, 3.30, 4.00 };
Double_t ptee_bin[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.4, 2.0, 3.0, 4.0, 5.0, 6.0 };
Double_t ptee_bin_4D[] = { 0.0, 1.0, 2.0, 4.0, 6.0 }; // less bins for more stable phiV-correction.
Double_t ptee_bin_phiv[] = { 0.0, 1.0, 2.0, 4.0, 6.0 }; // less bins for more stable phiV-correction.
Double_t ptee_bin_sys_phiv[] = { 0.0, 6.0 };
//
Double_t phiv_bin[] = { 5 // if only one number is given, it will be used for Rebin(n).
  //  0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38, 0.40, 0.42, 0.44, 0.46, 0.48, 
  //  0.50, 0.52, 0.54, 0.56, 0.58, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.72, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98, 
  //  1.00, 1.02, 1.04, 1.06, 1.08, 1.10, 1.12, 1.14, 1.16, 1.18, 1.20, 1.22, 1.24, 1.26, 1.28, 1.30, 1.32, 1.34, 1.36, 1.38, 1.40, 1.42, 1.44, 1.46, 1.48, 1.50, 1.52, 1.54, 1.56, 1.58, 1.60, 
  //  0.00, 0.10, 0.20, 0.30, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00, 1.10, 1.20, 1.30, 1.40, 1.50, 1.60, 
  //  1.70, 1.80, 1.90, 2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 3.00, 3.10, 3.1415 
};
Int_t n_mee_bin     = sizeof(mee_bin)/sizeof(*mee_bin) -1;
Int_t n_mee_bin_4D  = sizeof(mee_bin_4D)/sizeof(*mee_bin_4D) -1;
Int_t n_ptee_bin    = sizeof(ptee_bin)/sizeof(*ptee_bin) -1;
Int_t n_ptee_bin_4D = sizeof(ptee_bin_4D)/sizeof(*ptee_bin_4D) -1;
Int_t n_phiv_bin    = sizeof(phiv_bin)/sizeof(*phiv_bin) -1;
Int_t n_ptee_bin_phiv     = sizeof(ptee_bin_phiv)/sizeof(*ptee_bin_phiv) -1;
Int_t n_ptee_bin_sys_phiv = sizeof(ptee_bin_sys_phiv)/sizeof(*ptee_bin_sys_phiv) -1;
//
// systematic
// Bin edges must match with the projection bins of the final data handler!
Double_t mee_bin_systematic[] = { 0.0, 0.14, 1.1, 2.9, 3.3, 4.0 };
Double_t ptee_bin_systematic[] = { 0.0, 6.0 }; // used for rebinning of signal, to apply effi before integrating over ptee!
Int_t n_mee_bin_systematic = sizeof(mee_bin_systematic)/sizeof(*mee_bin_systematic) -1;
Int_t n_ptee_bin_systematic = sizeof(ptee_bin_systematic)/sizeof(*ptee_bin_systematic) -1;
//
// PhiV-cut that shall be applied
// to disable, it's most efficient to call mgr.SetEnableExclusionCutZ(kFALSE);
Double_t cutPhiVbelow[] = { 0 };
Double_t cutPhiVabove[] = { 1./2.*TMath::Pi() };
Double_t cutEdgesMee[]  = { 0.14 };
//// used by pat_sys until 26.04.18:
//Double_t cutPhiVbelow[] = { 0, 0 };
//Double_t cutPhiVabove[] = { 1./4.*TMath::Pi(), 1./2.*TMath::Pi() };
//Double_t cutEdgesMee[]  = { 0.04,              0.10 };
Int_t    n_cutPhiVbelow = sizeof(cutPhiVbelow)/sizeof(*cutPhiVbelow);
Int_t    n_cutPhiVabove = sizeof(cutPhiVabove)/sizeof(*cutPhiVabove);
Int_t    n_cutEdgesMee  = sizeof(cutEdgesMee)/sizeof(*cutEdgesMee);

//_______________________________________________________________________________________________
// function declarations
void          InitCommon();
void          InitBinning();
void          FillBinVec(std::vector<Double_t> &bins, TString sArg);
TString       GetAllOptions(Bool_t onlyData=kFALSE);
TString       GetHfeOpt();
TString       GetRappOpt();
void          SetPref(Int_t pref);
TObjArray*    GetLabelsTemplate(Int_t type=1, Double_t sizefac=-1);
TLegend*      GetLegendTemplate(Int_t type=1, Double_t sizefac=-1, TString header="");
void          SetStyles1D(TH1* hist, Int_t col=-1, Int_t mark=-1, Int_t fill=-1);
TH2D*         CreateRelSysPhiV(Double_t diffGaSys);
// one-liners:
Bool_t        ReqRfac() { return (histBitsPrint & LmSignal::kRfactor); }
//_______________________________________________________________________________________________

enum enLabelType {
  kNothing=0,
  kTopLeft1,
  kDefault=kTopLeft1,
  kTopLeftNoRatio,
  kDefNoRatio=kTopLeftNoRatio,
  kRfactor,
  kTopRight1,
  kTopRightNoRatio,
  kKineMiddleLeft,
  kTopPanelBottomLeft,
  kTopPanelBottomRight,
  kBottomPanelBottomLeft,
  kBottomPanelBottomRight,
  kDontUse
};

//_______________________________________________________________________________________________
void InitCommon()
{
  //gErrorIgnoreLevel = kWarning;
  LmHelper lmHelper;
  LmHelper::SetCanvasWidth(696); // 580x600 ok to get vertical pdf when importing to ppt.
  LmHelper::SetCanvasHeight(720);
  
  // defaults for main args
  // dataset
  kDoAOD          = 1;
  kDo4D           = 0; // Do not use. For 4D AOD use "16_4D" and for 4D ESD use "ESD".
  kUse16_4D       = 1; // 1 = final default.
  kDoSemi         = 0;
  kDoPt400        = 1;
  kDoOpAngle      = 0; // 0 = final default
  // cocktail
  kDoCocktail     = 0;
  kUseLFsum       = 0;
  kUseHfeRaa      = 0;
  kUseRapp        = 0;
  // phiv & pref
  kDoPhiV         = LmManager::kNoCut;//kTemplSub;//kFlatCorrSub;//kTemplConv;
  kDoPref         = 0;
  // effi & normalizations
  kDoEffGen       = 0;
  kDoEffiCorr     = 1;
  kDoNormNevents  = 1;
  kDoNormBinwidth = 1;
  kDoSignifRaw    = 1;
  // systematics
  kDoSystematics  = 1;
  // plotting
  kWideMeeBins    = 0;
  kDoRatio        = 0;
  kDoLegend       = 1;
  kDoLogY         = 1;
  kDoConfLevel    = 0;
  plotCombineH    = 1;
  kReprocess      = 0;
  writeFile       = 0;
  histBitsPrint   = 0;
  
  // manual settings
  plotAverage  = kFALSE;
  plotWeightAv = kFALSE;
  sSelectedCut  = "cut16"; // which cut shall replace the average datapoints.
  sSelCutMaxStat= "cut18"; // cut 18 has the highest efficiency, but the datapoints may not lie near the average...
  confLevel     = 0.84;
  ratioPadSize  = 0.3;
  debug         = 0;
  
  // plotting
  // select other ranges via main arguments.
  plotMeeMin  = 0.; plotMeeMax  = 4.0;
  plotPteeMin = 0.; plotPteeMax = 6.0;
  plotPhiVMin = 0.; plotPhiVMax = 3.14; // 3.14 will include last bin.
  LmBaseSignal::SetInputLabelZ("#it{#phi}_{V}","rad","PhiV");
  LmBaseSignal::SetLabelSig("#it{N}_{S}");
  LmBaseSignal::SetLabelBkg("#it{N}_{B}");
  plotMeeMax_sys  = mee_bin_systematic[n_mee_bin_systematic];
  plotPteeMax_sys = ptee_bin_systematic[n_ptee_bin_systematic];
}

//_______________________________________________________________________________________________
void InitBinning()
{
  // binning
  for (int ib=0; ib<=n_mee_bin_systematic; ++ib)  binsMee_forPtee_sys.push_back(mee_bin_systematic[ib]);
  for (int ib=0; ib<=n_ptee_bin_systematic; ++ib) binsPtee_forMee_sys.push_back(ptee_bin_systematic[ib]);
  binsPtee_forMee.push_back(0.);
  binsPtee_forMee.push_back(1.);
  binsPtee_forMee.push_back(2.);
  binsPtee_forMee.push_back(4.);
  binsPtee_forMee.push_back(6.);
  binsMee_forPtee.push_back(0.); // TODO: get/check closest existing values from array mee_bin[]
  binsMee_forPtee.push_back(0.14);
  binsMee_forPtee.push_back(1.1);
  binsMee_forPtee.push_back(2.9);
  binsMee_forPtee.push_back(3.3);
  //binsMee_forPtee.push_back(4.0); // test
  
  // phiv-related:
  binsPhiV.push_back(0.);
  binsPhiV.push_back(TMath::Pi());
  binsMee_forPhiV.push_back(0.);
  binsMee_forPhiV.push_back(0.02);
  binsMee_forPhiV.push_back(0.04);
  binsMee_forPhiV.push_back(0.06);
  binsMee_forPhiV.push_back(0.08);
  binsMee_forPhiV.push_back(0.10);
  binsMee_forPhiV.push_back(0.14);
  binsMee_forPhiV.push_back(0.18);
  //  binsMee_forPhiV.push_back(0.26);
  //  binsMee_forPhiV.push_back(0.50);
  //  binsMee_forPhiV.push_back(1.5);
  //  binsMee_forPhiV.push_back(3.3);
  // binsPtee_forPhiV is filled by main arguments in patrick.cpp.
}

//_______________________________________________________________________________________________
void FillBinVec(std::vector<Double_t> &bins, TString sArg) {
  /// Fill main argument into binning vector. E.g. ./patrick.exe stud binsPteePhiV=1,2
  TObjArray* oaEdges = sArg.Tokenize(",");
  for (int i=0; i<oaEdges->GetEntries(); ++i) {
    bins.push_back( TString(oaEdges->At(i)->GetName()).Atof() ); continue;
  }
}

//_______________________________________________________________________________________________
TString GetAllOptions(Bool_t onlyData) {
  TString sAllOpt = "";
  if (!sOptAOD    .IsNull())  sAllOpt.Append("_"+sOptAOD    );
  if (!sOptCent   .IsNull())  sAllOpt.Append("_"+sOptCent   );   
  if (!sOptPt     .IsNull())  sAllOpt.Append("_"+sOptPt     );
  if (!sOptOpAngle.IsNull())  sAllOpt.Append("_"+sOptOpAngle);
  if (!sOptPhiV   .IsNull())  sAllOpt.Append("_"+sOptPhiV   );
  if (!sOptPref   .IsNull())  sAllOpt.Append("_"+sOptPref   );
  if (!sOptEff    .IsNull())  sAllOpt.Append("_"+sOptEff    );
  //Form("_%s_%s_%s_%s_%s_%s_%s",sOptAOD.Data(),sOptCent.Data(),sOptPt.Data(),sOptOpAngle.Data(),sOptPhiV.Data(),sOptPref.Data(),sOptEff.Data());
  if (kUseHfeRaa && !onlyData) sAllOpt.Append("_"+GetHfeOpt());
  if (kUseRapp   && !onlyData) sAllOpt.Append("_"+GetRappOpt());
  return sAllOpt;
}

//_______________________________________________________________________________________________
TString GetHfeOpt() {
  switch (kUseHfeRaa) {
    case 1: return "HfeRaa";
    case 2: return "RndmPhiCC";
    case 3: return "SmearCC1s";
    case 4: return "SmearCC2s";
    case 5: return "SampleCCeta";
    case 7: return "CompareRaa";
    case 9: return "AllCC";
  }
  return "";
}

//_______________________________________________________________________________________________
TString GetRappOpt() {
  switch (kUseRapp) {
    case 1: return "Rapp1";
    case 2: return "Rapp2";
    case 3: return "Rapp3";
  }
  return "";
}

//_______________________________________________________________________________________________
void SetPref(Int_t pref) {
  if (pref==0) { kDoPref=0;     sOptPref    = "NoPref";   }
  if (pref==1) { kDoPref=1;     sOptPref    = "Pref";     }
  if (pref==2) { kDoPref=2;     sOptPref    = "PrefPhiV"; }
  if (pref==4) { kDoPref=4;     sOptPref    = "AllPref";  }
}

//_______________________________________________________________________________________________
TObjArray* GetLabelsTemplate(Int_t type, Double_t sizefac)
{
  TObjArray* oaLabels = 0x0;
  
  Double_t xref = 0.575;
  Double_t yi;
  Double_t yoff;
  
  switch (type) {
    case kNothing:
      oaLabels = LmHelper::GetLabelsTemplate(LmHelper::kNone); // this leads to no labels being drawn.
      break;
    case kDefault:
      if (sizefac<0) sizefac=0.7;
      if (kDoRatio) sizefac /= (1.-ratioPadSize);
      oaLabels = LmHelper::GetLabelsTemplate(LmHelper::kPatrick1, sizefac, xref);
      break;
    case kRfactor: // Rfactor plot, never has a ratio.
    case kDefNoRatio:
      if (sizefac<0) sizefac=0.7;
      oaLabels = LmHelper::GetLabelsTemplate(LmHelper::kPatrick1, sizefac, xref);
      break;
      
    case kKineMiddleLeft:
      if (sizefac<0) sizefac = 0.9;
      xref =  0.21;
      yi   =  0.65;
      oaLabels = LmHelper::GetLabelsTemplate(LmHelper::kPatrickKine1, sizefac, xref, yi);
      break;

    case kTopPanelBottomLeft:
      if (sizefac<0) sizefac = 0.8;
      xref =  0.18;
      yi   =  0.55;
      yoff = -0.06; // shift upwards
      oaLabels = LmHelper::GetLabelsTemplate(LmHelper::kPatrickBottomUp1, sizefac, xref, yi, yoff);
      break;
    case kTopPanelBottomRight:
      if (sizefac<0) sizefac = 0.8;
      xref =  0.58;
      yi   =  0.55;
      yoff = -0.06; // shift upwards
      oaLabels = LmHelper::GetLabelsTemplate(LmHelper::kPatrickBottomUp1, sizefac, xref, yi, yoff);
      break;
    case kBottomPanelBottomLeft:
      if (sizefac<0) sizefac = 0.8;
      xref =  0.18;
      yi   =  0.15;
      yoff = -0.06; // shift upwards
      oaLabels = LmHelper::GetLabelsTemplate(LmHelper::kPatrickBottomUp1, sizefac, xref, yi, yoff);
      break;
    case kBottomPanelBottomRight:
      if (sizefac<0) sizefac = 0.8;
      xref =  0.58;
      yi   =  0.15;
      yoff = -0.06; // shift upwards
      oaLabels = LmHelper::GetLabelsTemplate(LmHelper::kPatrickBottomUp1, sizefac, xref, yi, yoff);
      break;
      
    default:
      break;
  }
  return oaLabels;
}

//_______________________________________________________________________________________________
TLegend* GetLegendTemplate(Int_t type, Double_t sizefac, TString header)
{
  Double_t xlow, xup, ylow, yup;
  switch (type) {
    case kNothing:
      return 0x0; // this leads to a default legend.
    case kTopLeft1:
    case kTopLeftNoRatio:
      if (sizefac<0) {
        sizefac = 0.9;
        if (kDoRatio && type!=kTopLeftNoRatio) sizefac /= (1.-ratioPadSize);
      }
      xlow=0.20; xup=0.55; yup=0.84; ylow=yup;
      break;
    case kTopRight1:
    case kTopRightNoRatio:
      if (sizefac<0) {
        sizefac = 0.9;
        if (kDoRatio && type!=kTopRightNoRatio) sizefac /= (1.-ratioPadSize);
      }
      xlow=0.567; // this matches with label position k...BottomRight
      xup=0.9; yup=0.84; ylow=yup;
      break;
    case kRfactor: // Rfactor plot, never has a ratio.
      if (sizefac<0) sizefac = 0.9;
      xlow=0.20; xup=0.55; ylow=0.74; yup=0.84;
      break;
      
    default: // from framework, space-efficient but not nice.
      if (sizefac<0) {
        sizefac = 0.7;
        if (kDoRatio) sizefac /= (1.-ratioPadSize);
      }
      xlow=0.17; xup=0.55; yup=0.87; ylow=yup;
      break;
  }
  
  TLegend* leg = new TLegend(xlow, ylow, xup, yup);
  if (!header.IsNull()) leg->SetHeader(header.Data()); // option "C" allows to center the header
  leg->SetFillStyle(0);
  leg->SetTextSize(gStyle->GetTitleSize()*sizefac);
  return leg;
}

//_______________________________________________________________________________________________
void SetStyles1D(TH1* hist, Int_t col, Int_t mark, Int_t fill)
{
  hist->SetMarkerStyle(20);
  hist->SetLineWidth(1);
  if (col >=0) hist->SetMarkerColor(col);
  if (col >=0) hist->SetLineColor(col);
  if (mark>=0) hist->SetMarkerStyle(mark);
  if (fill>=0) hist->SetFillStyle(fill);
}

//_______________________________________________________________________________________________
TH2D* CreateRelSysPhiV(Double_t diffGaSys)
{
  TString phivdir    = Form("/Users/Patrick/Desktop/Analyse/LMeeAnaFW/PlottingFW/plots/_PhiVstudy/%s-%s/phiVTemplSub-PrefPhiV",sOptCent.Data(),sOptPt.Data());
  TString appendSys  = Form("-DiffGa%.2f",diffGaSys);
  TString filename   = Form("spectra1D-phiVstud-2-%s-%s-%s-data+uncorr+templ+flat+MC",sOptCent.Data(),sOptPt.Data(),sOptPref.Data());
  
  TFile* fileNom  = LmHelper::SafelyOpenRootfile( (phivdir           +"/"+filename           +".root").Data() );
  TFile* fileSys  = LmHelper::SafelyOpenRootfile( (phivdir+appendSys +"/"+filename+appendSys +".root").Data() );
  
  if (!fileNom || !fileSys) {
    LmHelper::Warning("CreateRelSysPhiV: input files not available, not adding phiV systematics.");
    return 0x0;
  }
  
  TH1D* hTemplFitNom  = (TH1D*) LmHelper::GetHistFromTemplateFile(fileNom , 5, "hSubSig-mee0.00to3.14", kFALSE);  hTemplFitNom ->SetName("phivFitNom");
  TH1D* hTemplFitSys  = (TH1D*) LmHelper::GetHistFromTemplateFile(fileSys , 5, "hSubSig-mee0.00to3.14", kFALSE);  hTemplFitSys ->SetName("phivFitSys");
  
  TH2D* hRelSys = 0x0;
  if (projoption.EqualTo("xz")) { // 'xz' means mee on y, phiv on x (phiv study)
    Int_t     n_phiv_bin_local = hTemplFitNom->GetNbinsX();
    Double_t  phiv_bin_local[n_phiv_bin_local+1];
    hTemplFitNom->GetXaxis()->GetLowEdge(phiv_bin_local); // fill all bin low edges
    phiv_bin_local[n_phiv_bin_local] = hTemplFitNom->GetXaxis()->GetBinLowEdge(n_phiv_bin_local+1); // fill last bin up edge
    hRelSys = new TH2D(Form("hRelSys%.2f",diffGaSys), "hRelSys", n_phiv_bin_local, phiv_bin_local, n_mee_bin, mee_bin);
  }
  if (projoption.EqualTo("yx")) { // 'yx' means ptee on y, mee on x (default analysis)
    hRelSys = new TH2D(Form("hRelSys%.2f",diffGaSys), "hRelSys", n_mee_bin, mee_bin, n_ptee_bin_sys_phiv, ptee_bin_sys_phiv);
  }
  
  Int_t    hTemplbinMee(0);
  Double_t relSys(0.);
  for (int ix=1; ix<=hRelSys->GetNbinsX(); ++ix) {
    for (int iy=1; iy<=hRelSys->GetNbinsY(); ++iy) {
      if      (projoption.EqualTo("xz")) hTemplbinMee = hTemplFitNom->GetXaxis()->FindBin(hRelSys->GetYaxis()->GetBinCenter(iy)); // for mee in phivstudy-projection.
      else if (projoption.EqualTo("yx")) hTemplbinMee = hTemplFitNom->GetXaxis()->FindBin(hRelSys->GetXaxis()->GetBinCenter(ix)); // default ana.
      relSys      = ( hTemplFitSys->GetBinContent(hTemplbinMee) - hTemplFitNom->GetBinContent(hTemplbinMee) ) / hTemplFitNom->GetBinContent(hTemplbinMee);
      //printf(" relSys (%i, %i) = %.6f \n", ix, iy, relSys);
      hRelSys->SetBinContent(ix,iy,relSys);
      hRelSys->SetBinError(ix,iy,0);
    }
  }
  
  return hRelSys;
}

#endif
