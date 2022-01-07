///@mainpage Analysis Framework for Dilepton Spectra
///@section ALICE ALICE
///http://aliceinfo.cern.ch/
///http://stackoverflow.com/questions/51667/best-tips-for-documenting-code-using-doxygen?rq=1
///@section DEVELOPER
///Developed by Patrick Reichelt, Carsten Klein and Theo Bröker

// c++ includes
#include <iostream>
#include <vector>
using namespace std;
// ROOT includes
#include "TString.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TStyle.h"
// project includes
#include "config.h"
#include "../core/LmManager.h"
#include "../core/LmBackground.h"
#include "../core/LmSignal.h"
#include "../core/LmHandler.h"
#include "../core/LmHelper.h"

/*
// Patricks Input
// TString name[] = {
//   "./input/LMEEoutput-347-2low.root", 
//   "./input/LMEEoutput-347-3hig.root", 
//   "./input/LMEEoutput-347-1full.root" };
//  TString tree_name[] = { "reichelt_LMEEPbPb2011_out" }; // extend when comparing PR with CK!
//  TString cut_setting[] = { "ITSTPCTOFif_trkSPDfirst_1_kSemi" }; // always adapt to input data files!
//  TString coll_system = "Pb#minusPb";
// TString inputhist("pInvMass_PairPt_PhivPair");
// Int_t   inputdim = 3;
// Bool_t  kDoNormNevents  = kTRUE;
// Bool_t  kDoNormBinwidth = kTRUE;
// // desired binning for output. will also be used for efficiency correction.
// // binning has to be compatible with input. [PR/CK: see function GetVector() of Config_user_LMEEPbPb.C]
// Double_t mee_bin[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 
// 0.14, 0.18, 0.22, 0.26, 0.30, 0.34, 
// 0.42, 0.50, 0.58, 0.66, 0.82, 0.98, 
// 1.50, 2.10, 2.70, 3.30, 4.00, 5.00 };
// Double_t ptee_bin[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.4, 2.0, 3.0, 4.0, 5.0 };

// ____________________________________________________________________________________________
// Theos Input
// TString name[] = {
//    "./input/pt200_lowmass.root" };
// TString tree_name[] = { "NoList" };
// TString cut_setting[] = { "cut1" };
// TString coll_system = "pPb"; // used for plotting labels
// TString inputhist("InvMass_pPt");
// Int_t   inputdim = 2;
// Bool_t  kDoNormBinwidth = kTRUE;
// Bool_t  kDoNormNevents  = kTRUE;
//  // desired binning for output. will also be used for efficiency correction.
//  // binning has to be compatible with input. [PR/CK: see function GetVector() of Config_user_LMEEPbPb.C]
//  Double_t mee_bin[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 
//  0.14, 0.18, 0.22, 0.26, 0.30, 0.34, 
//  0.42, 0.50, 0.58, 0.66, 0.82, 0.98, 
//  1.50, 2.10, 2.70, 3.30, 4.00, 5.00 };
//  Double_t ptee_bin[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.4, 2.0, 3.0, 4.0, 5.0 };

// ____________________________________________________________________________________________
// Carstens Input
TString name[] = {
   "./input/LMEEoutput-440-2low.root", 
   "./input/LMEEoutput-440-3hig.root", 
   "./input/LMEEoutput-440-1full.root",  // QM 2014 setting, 200 MeV single leg pt cut
   "./input/LMEEoutput-347-1full.root" }; // QM 2014 setting
TString tree_name[] = { "caklein_LMEEPbPb_out", "reichelt_LMEEPbPb2011_out" };
TString cut_setting[] = { "ITSTPCTOFif_trkSPDfirst_1_kSemi" };
TString coll_system = "Pb#minusPb";
TString inputhist("pInvMass_PairPt_PhivPair");
Int_t   inputdim = 3;
Bool_t  kDoNormBinwidth = kTRUE;
Bool_t  kDoNormNevents  = kTRUE;

// desired binning for output. will also be used for efficiency correction.
// binning has to be compatible with input. [PR/CK: see function GetVector() of Config_user_LMEEPbPb.C]
Double_t mee_bin[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 
0.14, 0.18, 0.22, 0.26, 0.30, 0.34, 
0.42, 0.50, 0.58, 0.66, 0.82, 0.98, 
1.50, 2.10, 2.70, 3.30, 4.00, 5.00 };
Double_t ptee_bin[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.4, 2.0, 3.0, 4.0, 5.0 };




 // corresponding input efficiency files
 TString effi_name[] = {
 "./input/charm-eff05-17h.root", 
 "./input/charm-eff05-17h.root", 
 "./input/charm-eff05-17h.root" };
 // name of 2D generated and reconstructed histogram
 TString effi_gen[] = {"meePairPt_Eta076_raw", "meePairPt_Eta076_raw", "meePairPt_Eta076_raw"};
 TString effi_rec[] = {"meePairPt_PID2_e", "meePairPt_PID2_e", "meePairPt_PID2_e"};
 Bool_t kDoEffiCorrection = kTRUE;


 //
 // further details of input data
 // config string for manager
 TString cconfig[] = { // this determines which settings will really be analysed!
 // (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[0]) 
 // , (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[0])
  (coll_system + ":" + name[2] + ":" + tree_name[0] + ":" + cut_setting[0])
  ,(coll_system + ":" + name[3] + ":" + tree_name[1] + ":" + cut_setting[0])
 };
 Int_t n_config = sizeof(cconfig)/sizeof(*cconfig);
 
 //
 Int_t n_mee_bin = sizeof(mee_bin)/sizeof(*mee_bin) -1;
 Int_t n_ptee_bin = sizeof(ptee_bin)/sizeof(*ptee_bin) -1;
 //
 // PhiV-cut that shall be applied
 // to disable, set phiv=pi or mee=0 or call mgr.SetEnablePhiVCut(kFALSE);
 Double_t cutValPhiV = 3./4.*TMath::Pi();
 Double_t cutValMee = 0.10;
*/

/*__________ Info-Exchange / To-Do-Next Section __________
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 > Setter kDoNormEvents, kDoNormBinWidth and kDoEffiCorrection in config.h implemented. UPDATE it!
 > 
 > NEEDS CHECK IF BINS ARE SETTED in Handler
 */

int main()
{
  //Style____________________________________________________________________________________________________________________________

  // gROOT->Macro("./input/init_style.C");   // Causes some problems with root6 which are not understood
  //gROOT->SetStyle("Plain");
  
  gStyle->SetOptStat(0);// statistics yes, less, no (1, 11, 0)
  gStyle->SetOptTitle(0); // do not draw histogram title even if not empty
  //gStyle->SetOptFit(0111);  // ver�ndet Gr��e der Statistikbox, evtl noch mehr
   
  // Canvas
  Float_t cstretch = 1.2;
  gStyle->SetCanvasDefW(580*cstretch); // 580x600 ok to get vertical pdf when importing to ppt.
  gStyle->SetCanvasDefH(600*cstretch);
  
  // Pad
  gStyle->SetPadLeftMargin(0.14);   // 0.1 = root default
  gStyle->SetPadRightMargin(0.06);  
  gStyle->SetPadTopMargin(0.1);     // room for title. and the canvas is higher than wide.
  gStyle->SetPadBottomMargin(0.1);  
  gStyle->SetCanvasColor(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0); 
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  //gStyle->SetPadGridX(1);
  //gStyle->SetPadGridY(1);
  
  // Axis
  gStyle->SetLabelOffset(0.01,"y");    // 0.005 = root default
  gStyle->SetTitleOffset(1.9,"y");
  // doesnt work for x axis?
  gStyle->SetLabelOffset(0.01,"x");
  gStyle->SetTitleOffset(1.3,"x");
  
  //gStyle->SetTitleSize(0.09,"xy");         // 0.04  = root default
  
  // Legend
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(0);
  //gStyle->SetLegendFont(Style_t font = 62);
  
  //gStyle->SetFillStyle(0);
  gStyle->SetFrameLineWidth(2);
  
  gStyle->SetPalette(1);
  gROOT->ForceStyle();
  
//_________________________________________________________________________________________________________________________________

  LmHelper lmHelper;

  std::vector<LmManager*>     mgrVec; // works when using pointers (they survive after the for-loop). otherwise fancy errors.
  std::vector<LmBackground*>  bkgVec;
  std::vector<LmSignal*>      sigVec;
  LmHandler*                  hanComb = new LmHandler();
  
  for (int ic=0; ic<n_config; ic++) 
  {
    LmManager* mgr00 = new LmManager(const_cast<char*>(cconfig[ic].Data())); // TODO: input style to be optimized
    mgr00->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
    
    mgr00->SetCutValPhiV(cutValPhiV);  // only relevant for 3D input
    mgr00->SetCutValMee(cutValMee);    // only relevant for 3D input
    //mgr00->SetEnablePhiVCut(kFALSE); // to disable, it is best to change the values in the config.h...
    
    mgr00->SetRebinning2D(n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
    //mgr00->SetEnableRebinning(kFALSE); // use this to disable or just comment out the setter above...
    
    mgr00->SetEffifileAndHists(const_cast<char*>(effi_name[ic].Data()), const_cast<char*>(effi_gen[ic].Data()), const_cast<char*>(effi_rec[ic].Data()));
    mgr00->SetEnableEffiCorr(kDoEffiCorrection); // use this to disable or just comment out the setter above...
    
    mgr00->Process();
    
    //mgr00->Print2DUnlike(Form("c2DUnlike_cut%d.pdf",ic));
    //mgr00->Print2DUnlikeMix(Form("c2DUnlikeMix_cut%d.pdf",ic));
    // mgr00->Print2DEffi(Form("cEffi_cut%d.pdf",ic));
    
    mgrVec.push_back(mgr00);
    
    LmBackground* bkg00_Geom = new LmBackground(*(mgrVec.at(ic)));
    // bkg00_Geom->SetUseRfactor(kFALSE);
    bkg00_Geom->Process(LmBackground::kGeom);
    //bkg00_Geom->PrintBkg2D();
    //bkg00_Geom->PrintRfactor2D(Form("c2DRfactor_cut%d.pdf",ic));
    
    bkgVec.push_back(bkg00_Geom);
    
    LmSignal* sig00_Std = new LmSignal(*(mgrVec.at(ic)), *(bkgVec.at(ic)), Form("Cut %d", ic));
    //sig00_Std->SetDoSubtraction(kFALSE);
    sig00_Std->SetDoNormBinwidth(kDoNormBinwidth);
    sig00_Std->SetDoNormNevents(kDoNormNevents);
    
    sig00_Std->Process(LmSignal::kStd);
    //sig00_Std->PrintSig(Form("c2DSig_cut%d.pdf",ic));
    //sig00_Std->PrintSoverB();
    //sig00_Std->PrintSignif();
    
    sigVec.push_back(sig00_Std);
    
    // attach all signals to a handler for later combination or comparison
    hanComb->AttachSignal(*(sigVec[ic])); // could use AttachSignal(..., "newname") in case the previous signal name is not meaningful enough...
    
  } // end config loop
  cout << "__________ DONE WITH SINGLE INPUT PROCESSING __________" << endl;
  
  // combined handler:
  std::vector<Double_t> binsPtee_forMee;
  binsPtee_forMee.push_back(0.);
  binsPtee_forMee.push_back(1.);
  binsPtee_forMee.push_back(2.);
  binsPtee_forMee.push_back(3.);
  binsPtee_forMee.push_back(4.);
//  binsPtee_forMee.push_back(4.);
  std::vector<Double_t> binsMee_forPtee;
  binsMee_forPtee.push_back(0.); // pi0 region no good idea with effi from charm.
  // binsMee_forPtee.push_back(0.3);
  binsMee_forPtee.push_back(0.98);
  binsMee_forPtee.push_back(1.5);
  
  Double_t plotMeeMin  = 0., plotMeeMax  = 1.5;
  Double_t plotPteeMin = 0., plotPteeMax = 4.0;
  
  hanComb->SetBinsPtee_forprojMee(binsPtee_forMee);
  hanComb->SetBinsMee_forprojPtee(binsMee_forPtee);
  hanComb->SetPlotRangeMee(plotMeeMin, plotMeeMax);
  hanComb->SetPlotRangePtee(plotPteeMin, plotPteeMax);
  
  hanComb->Process(LmHandler::kCombine);

 // cout << "projections Mee: " << endl;
 // for (unsigned int i_proj = 0; i_proj < binsPtee_forMee.size()-1; ++i_proj){
 //   hanComb->PrintSig_Mee(i_proj, Form("cSig_MeeComb_%d.pdf",i_proj));
 //   hanComb->PrintSigBkg_Mee(i_proj, Form("cSigBkg_MeeComb_%d.pdf",i_proj));
 //   hanComb->PrintSoverB_Mee(i_proj, Form("cSoverB_MeeComb_%d.pdf",i_proj));
 //   hanComb->PrintSignif_Mee(i_proj, Form("cSignif_MeeComb_%d.pdf",i_proj));
 // }
 // hanComb->PrintSig_Mee(binsPtee_forMee.size()-1, Form("cSig_MeeComb_int.pdf"));
//  hanComb->PrintSigBkg_Mee(binsPtee_forMee.size()-1, Form("cSigBkg_MeeComb_int.pdf"));
//  hanComb->PrintSoverB_Mee(binsPtee_forMee.size()-1, Form("cSoverB_MeeComb_int.pdf"));
//  hanComb->PrintSignif_Mee(binsPtee_forMee.size()-1, Form("cSignif_MeeComb_int.pdf"));
 // cout << "projections Ptee: " << endl;
 // for (unsigned int i_proj = 0; i_proj < binsMee_forPtee.size()-1; ++i_proj){
 //   hanComb->PrintSig_Ptee(i_proj, Form("cSig_PteeComb_%d.pdf",i_proj));
 //   hanComb->PrintSigBkg_Ptee(i_proj, Form("cSigBkg_PteeComb_%d.pdf",i_proj));
 //   hanComb->PrintSoverB_Ptee(i_proj, Form("cSoverB_PteeComb_%d.pdf",i_proj));
 //   hanComb->PrintSignif_Ptee(i_proj, Form("cSignif_PteeComb_%d.pdf",i_proj));
 // }
 // hanComb->PrintSig_Ptee(binsMee_forPtee.size()-1, Form("cSig_PteeComb_int.pdf"));
//  hanComb->PrintSigBkg_Ptee(binsMee_forPtee.size()-1, Form("cSigBkg_PteeComb_int.pdf"));
//  hanComb->PrintSoverB_Ptee(binsMee_forPtee.size()-1, Form("cSoverB_PteeComb_int.pdf"));
//  hanComb->PrintSignif_Ptee(binsMee_forPtee.size()-1, Form("cSignif_PteeComb_int.pdf"));
  
  //
  // write most important histograms to rootfiles:
  //
  // add bits of histograms you want to store: LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg+LmSignal::kSoverB+LmSignal::kSignif
  // to store all of them, you can also use LmSignal::kMAXhist-1
  //
  // const Char_t* filename = "spectra1D_Mee.root";
  // TFile* _fileOut = new TFile(filename, "RECREATE");
  // hanComb->SetSimpleHistnames(kTRUE); // use option kTRUE for short histogram names in rootfile or kFALSE for long, more informative histogram names.
  // for combine handler:
  // hanComb->Write1DHistCombined(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg+LmSignal::kSoverB+LmSignal::kSignif, LmSignal::kProjOnMee);
  // for compare handler:
  //hanComb->Write1DHistSingle(LmSignal::kSubSig+LmSignal::kSoverB+LmSignal::kSignif, LmSignal::kProjOnMee);
  // for any handler:
  //hanComb->Write1DHistSingle(LmSignal::kRfactor, LmSignal::kProjOnMee);
  // _fileOut->Close();
  
  // easy single handlers, temporarily:
  cout << "    HANDLER 00 ##############################################" << endl;
  LmHandler* han00_Std = new LmHandler(*(sigVec.at(0)));
  han00_Std->SetBinsPtee_forprojMee(binsPtee_forMee);
  han00_Std->SetBinsMee_forprojPtee(binsMee_forPtee);
  han00_Std->SetPlotRangeMee(plotMeeMin, plotMeeMax);
  han00_Std->SetPlotRangePtee(plotPteeMin, plotPteeMax);
  han00_Std->Process(LmHandler::kStd);
  for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
    han00_Std->PrintSig_Mee(i, Form("han00_Std_Mee_bin%d.pdf", i));
  }
  // han00_Std->PrintSigBkg_Mee(1, Form("han00_cSigBkg_MeeComb.pdf"));
  cout << "     Process succeeded ++++++++++++++++++++++++++++++" << endl;
  
  cout << "    HANDLER 01 ##############################################" << endl;
  LmHandler* han01_Std = new LmHandler(*(sigVec.at(1)));
  han01_Std->SetBinsPtee_forprojMee(binsPtee_forMee);
  han01_Std->SetBinsMee_forprojPtee(binsMee_forPtee);
  han01_Std->SetPlotRangeMee(plotMeeMin, plotMeeMax);
  han01_Std->SetPlotRangePtee(plotPteeMin, plotPteeMax);
  han01_Std->Process(LmHandler::kStd);
  for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
    han01_Std->PrintSig_Mee(i, Form("han01_Std_Mee_bin%d.pdf", i));
  }
  // han01_Std->PrintSigBkg_Mee(1, Form("han01_cSigBkg_MeeComb.pdf"));

  cout << "     COMPAREHANDLER ############!!!!!!!!!!!!!'############" << endl;
  LmHandler* hanCompare = new LmHandler();
  hanCompare->SetBinsPtee_forprojMee(binsPtee_forMee);    // NEEDS CHECK IF BINS ARE SETTED
  hanCompare->SetBinsMee_forprojPtee(binsMee_forPtee);
  hanCompare->SetPlotRangeMee(plotMeeMin, plotMeeMax);
  hanCompare->SetPlotRangePtee(plotPteeMin, plotPteeMax);

  hanCompare->AttachSignal(*(han00_Std->GetLmSigCombined()), "pT > 200 MeV/c");
  hanCompare->AttachSignal(*(han01_Std->GetLmSigCombined()), "pT > 400 MeV/c");
  hanCompare->SetType(LmHandler::kCompare);

  for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
    hanCompare->PrintCompareSig_Mee(i, kTRUE, Form("hCompareMee_bin%d.pdf", i));
  }
  
  for (unsigned int i = 0; i < binsMee_forPtee.size(); ++i){
    hanCompare->PrintCompareSig_Ptee(i, kTRUE, Form("hComparePtee_bin%d.pdf", i));
  }

  cout << "      print done************" << endl;


  // std::cout << LmHelper::GetUniformColor(0, 4) << " " << LmHelper::GetUniformColor(1, 4) << " " << LmHelper::GetUniformColor(2, 4) << " " << LmHelper::GetUniformColor(3,4) << " " << LmHelper::GetUniformColor(4,4) << std::endl;
  std::cout << "main.cpp done :-)" << std::endl;
  return 0;
}
