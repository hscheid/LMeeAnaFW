//Analysis Framework for Dilepton Spectra

// c++ includes
#include <iostream>
#include <vector>
using namespace std;
// ROOT includes
#include "TString.h"
#include "TMath.h"
#include "TF2.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TBenchmark.h"
#include "TSystem.h"
// project includes
#include "patrick_bg.h"
#include "../core/LmManager.h"
#include "../core/LmBackground.h"
#include "../core/LmBaseSignal.h"
#include "../core/LmSignal.h"
#include "../core/LmHandler.h"
#include "../core/LmHelper.h"
#include "../core/LmCocktailMan.h"
#include "../core/LmCocktail.h"
#include "../core/LmFitter.h"

int main()
{
  LmHelper lmHelper;
  TBenchmark* bench = new TBenchmark();
  
  
//  cout << LmHelper::CalcUpperLimit(0.9, 2, 3.5, 1.8708, 1, 0) << endl;
//  return 0;
  
//  bench->Start("CL_calculation");
//  TH1F* hSens = new TH1F("hSens","hSens", 400, -10, 30);
//  
//  int n=500;
//  double bkg = 15;
//  double upperLimit = -1;
//  for (int i=0; i<n; ++i) {
//    upperLimit = LmHelper::CalcUpperLimit(0.9, bkg, bkg, 0, 1, 0, kTRUE, kTRUE);
//    cout << i << "\t ul = " << upperLimit << "\t" << flush;
//    hSens->Fill( upperLimit );
//  }
//  cout << endl << Form("       mean = %.4f", hSens->GetMean()) << endl;
//  
//  TCanvas* c1 = new TCanvas("c1","c1");
//  gStyle->SetOptStat(1);
//  hSens->SetStats(1);
//  hSens->DrawCopy();
//  c1->Print(Form("c2-b%.1f_bPois-%i.pdf", bkg, n));
//  c1->Print(Form("c2-b%.1f_bPois-%i.C", bkg, n));
//  
//  bench->Show("CL_calculation");
//  return 0;
  
  
  // define vectors to store the different class objects
  std::vector<LmManager*>     mgrVec; // works when using pointers (they survive after the for-loop). otherwise fancy errors.
  std::vector<LmBackground*>  bkgVec;
  std::vector<LmSignal*>      sigVec;
  std::vector<LmBackground*>  bkgVec1;
  std::vector<LmSignal*>      sigVec1;
  std::vector<LmBackground*>  bkgVec2;
  std::vector<LmSignal*>      sigVec2;
  std::vector<LmBackground*>  bkgVec3;
  std::vector<LmSignal*>      sigVec3;
  std::vector<LmBackground*>  bkgVec4;
  std::vector<LmSignal*>      sigVec4;
  std::vector<LmBackground*>  bkgVec5;
  std::vector<LmSignal*>      sigVec5;
  
  // set static variables stored in LmBaseSignal, which will be used as starting point for the axis titles of all spectra histograms.
//  LmBaseSignal::SetInputLabelX("#it{dca}", "#sigma"); // unit without ( )
//  LmBaseSignal::SetInputLabelY("#it{p}_{T,ee}","GeV/#it{c}");
  LmBaseSignal::SetInputLabelZ("#it{#phi}_{V}","rad");
//  LmBaseSignal::SetInputLabelContent("", "a.u."); // if empty -> compute automatically from x and y // is now done internally.
  
  
  std::vector<Double_t> binsPtee_forMee;
  binsPtee_forMee.push_back(0.);
  binsPtee_forMee.push_back(1.);
  binsPtee_forMee.push_back(2.);
  binsPtee_forMee.push_back(3.);
  binsPtee_forMee.push_back(4.);
  std::vector<Double_t> binsMee_forPtee;
  binsMee_forPtee.push_back(0.);
  //  binsMee_forPtee.push_back(0.02);
  //  binsMee_forPtee.push_back(0.04);
  //  binsMee_forPtee.push_back(0.06);
  //  binsMee_forPtee.push_back(0.08);
  //  binsMee_forPtee.push_back(0.10);
  binsMee_forPtee.push_back(0.14);
  //  binsMee_forPtee.push_back(0.18);
  //  binsMee_forPtee.push_back(0.26); // TODO: get closest existing value from array mee_bin[]
  binsMee_forPtee.push_back(0.7);
  binsMee_forPtee.push_back(1.1);
  binsMee_forPtee.push_back(2.7);
  
  
  /*
  
  
  // create manager from config string
  LmManager* mgr00 = new LmManager(const_cast<char*>(cconfig[0].Data()));
  // (only one rootfile used, cannot compare to combined Pb-Pb output!)
  
  // set further configuration for the manager
  mgr00->SetInputhistAndDim(inputhist, inputdim);
//  mgr00->SetProjOption(projoption); // option="ab" means: a vertical, b horizontal (ROOT-convention)
  mgr00->SetProjOption("yz"); // option="ab" means: a vertical, b horizontal (ROOT-convention)
  
  mgr00->SetRebinning2D(n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
  //mgr00->SetEnableRebinning(kFALSE); // use this to disable or just comment out the setter above...
  // ...
//  TObjArray* oaConfig = cconfig[0].Tokenize(":");
//  // config entry 5 (i.e. #4) is convenient to be a nice signal caption (see .h and below).
//  // config entries #5-7 are for efficiency:
//  if (kDoEffiCorrection) {
//    mgr00->SetEffifileAndHists(const_cast<char*>(oaConfig->At(5)->GetName()), const_cast<char*>(oaConfig->At(6)->GetName()), const_cast<char*>(oaConfig->At(7)->GetName()));
//  }
  
  // read in histograms from data files
  mgr00->Process(LmManager::kReadInputOnly);
  
  // define 3D-projection binning
  Double_t bins3DProjRangeX[] = { 0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.10, 0.20 }; // mee
  Double_t bins3DProjRangeY[] = { 0., 1., 2., 3., 4. }; // ptee
  unsigned int n_bins3DProjRangeX = sizeof(bins3DProjRangeX)/sizeof(*bins3DProjRangeX) -1;
  unsigned int n_bins3DProjRangeY = sizeof(bins3DProjRangeY)/sizeof(*bins3DProjRangeY) -1;
  
  
  // fill vector of managers
  for (unsigned int iproj=0; iproj<n_bins3DProjRangeX; iproj++)
  {
    // make a copy of the manager including its input histograms
    LmManager* mgr_i = new LmManager(*mgr00);
    // select different subranges in input histograms
    mgr_i->Set3DProjRangeX(bins3DProjRangeX[iproj], bins3DProjRangeX[iproj+1]);
    //mgr_i->Set3DProjRangeY(bins3DProjRangeY[iproj], bins3DProjRangeY[iproj+1]);
    
    // add new manager to vector
    mgrVec.push_back(mgr_i);
  }
  
  
  // for each manager: create background and signal class from it, configure and process them, store them in vectors
  for (unsigned int iproj=0; iproj<mgrVec.size(); iproj++)
  {
    // process the managers: make the projections, rebinning, corrections...
    mgrVec.at(iproj)->Process(LmManager::kDontReadInput); // dont read in rootfiles again
    //mgrVec.at(iproj)->Print2DUnlike(Form("c2DUnlike_%d.pdf",iproj));
    
    LmBackground* bkg_i_Geom = new LmBackground(*(mgrVec.at(iproj)));
    //bkg_i_Geom->SetUseRfactor(kFALSE);
    bkg_i_Geom->Process(LmBackground::kGeom);
    bkgVec.push_back(bkg_i_Geom);
    
    TString signame = mgrVec.at(iproj)->GetAll3DProjRanges();
    LmSignal* sig_i_Std = new LmSignal(*(mgrVec.at(iproj)), *(bkgVec.at(iproj)), signame.Data()); //Form("Projection_%d", iproj)
    sig_i_Std->SetDoSubtraction(kFALSE);
    sig_i_Std->SetDoSignifRaw(kDoSignifRaw);
    sig_i_Std->SetDoNormBinwidth(kDoNormBinwidth);
    sig_i_Std->SetDoNormNevents(kDoNormNevents);
    sig_i_Std->Process(LmSignal::kStd);
    sigVec.push_back(sig_i_Std);
  }
  
  
  Double_t plotMeeMin  = 0., plotMeeMax  = 3.2;
  Double_t plotPteeMin = 0., plotPteeMax = 4.0;
  
  
  LmHandler* hanCompare = new LmHandler(LmHandler::kCompare);
  // attach signals to compare handler. they may already be processed or not.
  for (unsigned int i=0; i<sigVec.size(); i++) {
    hanCompare->AttachSignal(*(sigVec.at(i)), sigVec.at(i)->GetName());
  }
  hanCompare->SetBinsPtee_forprojMee(binsPtee_forMee);
  hanCompare->SetBinsMee_forprojPtee(binsMee_forPtee);
  hanCompare->SetPlotRangeMee(plotMeeMin, plotMeeMax);
  hanCompare->SetPlotRangePtee(plotPteeMin, plotPteeMax);
  hanCompare->Process(LmHandler::kCompare); // not needed if the attached signals were processed by a previous handler.
  
  Bool_t printLegend=kTRUE;
  hanCompare->SetPlotRangeY(1e-5, 2e+0);
  for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
    hanCompare->PrintCompareSig_Mee(i, printLegend, Form("hCompareMee_bin%d-unsubtr.pdf", i));
  }
  hanCompare->ResetPlotRangeY();
  hanCompare->SetPlotRangeY(5e-5, 1e+1);
  for (unsigned int i = 0; i < binsMee_forPtee.size(); ++i){
    hanCompare->PrintCompareSig_Ptee(i, printLegend, Form("hComparePtee_bin%d.pdf", i));
  }
  hanCompare->ResetPlotRangeY();
  
  
  std::cout << "main.cpp done :-)" << std::endl;
  return 0;
}

// */  
  
// /*


  //_______________________________________________________________________________________________________________
  // BG fit values
  TF2* fResidual = new TF2("pol2D","[0] + [1] * x + [2] * y + [3] * TMath::Power(x,2) + [4] * y * TMath::Power(x,2) + [5] * x * y",0.5,5.,0.,6.);
  fResidual->SetParLimits(0,1.,3.);
  fResidual->SetParLimits(1,0.,100.);
  fResidual->SetParLimits(2,0.,100.);
  fResidual->SetParLimits(3,0.,100.);
  fResidual->SetParLimits(4,0.,100.);
  fResidual->SetParLimits(5,0.,100.);
  Double_t NormMin(0.3);
  Double_t NormMax(0.7);
  //_______________________________________________________________________________________________________________
  
  
//  TFile* _file0 = 0x0;
//  TFile* _file1 = 0x0;
  
  for (int ic=0; ic<n_config; ic++) 
  {
    LmManager* mgr00 = new LmManager(const_cast<char*>(cconfig[ic].Data())); // TODO: input style to be optimized
    // set all kinds of configuration for the manager
    if (cconfig[ic].Contains("-268") || cconfig[ic].Contains("-272") || cconfig[ic].Contains("-279") || cconfig[ic].Contains("-311")) 
    {     inputhist="InvMass_PairPt_PhivPair"; }
    else  inputhist="pInvMass_PairPt_PhivPair";
    mgr00->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
    TObjArray* oaConfig = cconfig[ic].Tokenize(":");
    // config entry 5 (i.e. #4) is convenient to be a nice signal caption (see .h and below).
    // config entries #5-7 are for efficiency:
    if (kDoEffiCorrection) {
      mgr00->SetEffifileAndHists(const_cast<char*>(oaConfig->At(5)->GetName()), const_cast<char*>(oaConfig->At(6)->GetName()), const_cast<char*>(oaConfig->At(7)->GetName()));
    }
    mgr00->SetCutValPhiV(cutValPhiV);  // only relevant for 3D input
    mgr00->SetCutValMee(cutValMee);    // only relevant for 3D input
    //mgr00->SetEnablePhiVCut(kFALSE); // to disable, it is best to change the values in the config.h...
    mgr00->SetRebinning2D(n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
    //mgr00->SetEnableRebinning(kFALSE); // use this to disable or just comment out the setter above...
    
//    if (ic%2==0) mgr00->SetExternalInputfile(_file0);
//    if (ic%2==1) mgr00->SetExternalInputfile(_file1);
    
    mgr00->Process();
    
//    if (_file0==0x0 && ic==0) _file0 = mgr00->GetInputfilePointer();
//    if (_file1==0x0 && ic==1) _file1 = mgr00->GetInputfilePointer();
    
    
//    cout << "_file0 = " << _file0 << endl;
    mgrVec.push_back(mgr00);
    //mgr00->SetPlotRangeZ(0.,0.4);
    //mgr00->Print2DEffi();
    //mgr00->Print2DUnlike();
    
    LmBackground* bkg_Geom = new LmBackground(*(mgrVec.at(ic)));
    bkg_Geom->Process(LmBackground::kGeom);
    bkgVec.push_back(bkg_Geom);
    
    LmBackground* bkg_Arith = new LmBackground(*(mgrVec.at(ic)));
    bkg_Arith->Process(LmBackground::kArith);
    bkgVec1.push_back(bkg_Arith);
    
    LmBackground* bkg_GeomFit = new LmBackground(*(mgrVec.at(ic)));
    //bkg_GeomFit->SetMakeFitQA(kTRUE);
    bkg_GeomFit->SetNormalizationRegion(NormMin,NormMax);
    bkg_GeomFit->AddResidualFunction( fResidual );
    bkg_GeomFit->Process(LmBackground::kGeomFit);
    bkgVec2.push_back(bkg_GeomFit);
    
    LmBackground* bkg_ArithFit = new LmBackground(*(mgrVec.at(ic)));
    bkg_ArithFit->SetMakeFitQA(kTRUE);
    bkg_ArithFit->SetNormalizationRegion(NormMin,NormMax);
    bkg_ArithFit->AddResidualFunction( fResidual );
    bkg_ArithFit->Process(LmBackground::kArithFit);
    bkgVec3.push_back(bkg_ArithFit);
    
    LmBackground* bkg_Hybrid = new LmBackground(*(mgrVec.at(ic)));
    bkg_Hybrid->Process(LmBackground::kHybrid);
    bkgVec4.push_back(bkg_Hybrid);
    
    LmBackground* bkg_HybridFit = new LmBackground(*(mgrVec.at(ic)));
    bkg_HybridFit->Process(LmBackground::kHybridFit);
    bkgVec5.push_back(bkg_HybridFit);
    
    LmSignal* sig0_Std = new LmSignal(*(mgrVec.at(ic)), *(bkgVec.at(ic)), Form("Cut %d", ic));
    // update signal name according to config
    if (oaConfig->GetEntriesFast()>=5) sig0_Std->SetName(oaConfig->At(4)->GetName());
    //sig00_Std->SetDoSubtraction(kFALSE);
    sig0_Std->SetDoSignifRaw(kDoSignifRaw);
    sig0_Std->SetDoNormBinwidth(kDoNormBinwidth);
    sig0_Std->SetDoNormNevents(kDoNormNevents);
    sig0_Std->Process(LmSignal::kStd);
    sigVec.push_back(sig0_Std);
    
//    LmSignal* sig1_Std = new LmSignal(*(mgrVec.at(ic)), *(bkgVec1.at(ic)), Form("Cut %d Arith", ic));
//    sig1_Std->SetDoSignifRaw(kDoSignifRaw);
//    sig1_Std->SetDoNormBinwidth(kDoNormBinwidth);
//    sig1_Std->SetDoNormNevents(kDoNormNevents);
//    sig1_Std->Process(LmSignal::kStd);
//    sigVec1.push_back(sig1_Std);
//    
//    LmSignal* sig2_Std = new LmSignal(*(mgrVec.at(ic)), *(bkgVec2.at(ic)), Form("Cut %d GeomFit", ic));
//    sig2_Std->SetDoSignifRaw(kDoSignifRaw);
//    sig2_Std->SetDoNormBinwidth(kDoNormBinwidth);
//    sig2_Std->SetDoNormNevents(kDoNormNevents);
//    sig2_Std->Process(LmSignal::kStd);
//    sigVec2.push_back(sig2_Std);
//    
//    LmSignal* sig3_Std = new LmSignal(*(mgrVec.at(ic)), *(bkgVec3.at(ic)), Form("Cut %d ArithFit", ic));
//    sig3_Std->SetDoSignifRaw(kDoSignifRaw);
//    sig3_Std->SetDoNormBinwidth(kDoNormBinwidth);
//    sig3_Std->SetDoNormNevents(kDoNormNevents);
//    sig3_Std->Process(LmSignal::kStd);
//    sigVec3.push_back(sig3_Std);
//    
//    LmSignal* sig4_Std = new LmSignal(*(mgrVec.at(ic)), *(bkgVec4.at(ic)), Form("Cut %d Hybrid", ic));
//    sig4_Std->SetDoSignifRaw(kDoSignifRaw);
//    sig4_Std->SetDoNormBinwidth(kDoNormBinwidth);
//    sig4_Std->SetDoNormNevents(kDoNormNevents);
//    sig4_Std->Process(LmSignal::kStd);
//    sigVec4.push_back(sig4_Std);
//    
//    LmSignal* sig5_Std = new LmSignal(*(mgrVec.at(ic)), *(bkgVec5.at(ic)), Form("Cut %d HybridFit", ic));
//    sig5_Std->SetDoSignifRaw(kDoSignifRaw);
//    sig5_Std->SetDoNormBinwidth(kDoNormBinwidth);
//    sig5_Std->SetDoNormNevents(kDoNormNevents);
//    sig5_Std->Process(LmSignal::kStd);
//    sigVec5.push_back(sig5_Std);
    
  } // end config loop
  cout << "__________ DONE WITH SINGLE INPUT PROCESSING __________" << endl;
  
  
  
  //gSystem->Exec("echo sleep; sleep 10;");
  
  
  
  Double_t plotMeeMin  = 0., plotMeeMax  = 1.5;
  Double_t plotPteeMin = 0., plotPteeMax = 4.0;
  
  
  // handler array needed for later...
  std::vector<LmHandler*>     hanVec;
  std::vector<LmHandler*>     hanVec1;
  std::vector<LmHandler*>     hanVec2;
  std::vector<LmHandler*>     hanVec3;
  std::vector<LmHandler*>     hanVec4;
  std::vector<LmHandler*>     hanVec5;
  
  bench->Start("handler_processing");
  
  // handlers to combine ++ and -- field
  for (unsigned int ihan=0; ihan<sigVec.size()/2; ihan++) 
  {
    LmHandler* han0_Comb = new LmHandler();
    han0_Comb->AttachSignal( *(sigVec[ihan*2  ]) );
    han0_Comb->AttachSignal( *(sigVec[ihan*2+1]) );
    han0_Comb->SetBinsPtee_forprojMee(binsPtee_forMee);
    han0_Comb->SetBinsMee_forprojPtee(binsMee_forPtee);
    han0_Comb->SetPlotRangeMee(plotMeeMin, plotMeeMax);
    han0_Comb->SetPlotRangePtee(plotPteeMin, plotPteeMax);
    han0_Comb->SetConfidenceLevel(confLevel);
//    if (ihan==1) han0->SetConfidenceLevel(0.84); // ____________________ <--- HARDCODE !!! ____________________
    han0_Comb->SetDoConfidenceLevel(kDoConfLevel);
    han0_Comb->Process(LmHandler::kCombine);
//    han0->SetPlotRangeY(0.8, 1.1);
//    for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
//      han0->PrintCompareSigBkg_Mee(i, Form("han%d_SigBkg_Mee_bin%d.pdf", ihan, i));
//      han0->PrintCompareRfactor_Mee(i, kTRUE, Form("han%d_Rfactor_Mee_bin%d.pdf", ihan, i));
//    }
    hanVec.push_back(han0_Comb);
    
//    LmHandler* han1_Comb = new LmHandler();
//    han1_Comb->AttachSignal( *(sigVec1[ihan*2  ]) );
//    han1_Comb->AttachSignal( *(sigVec1[ihan*2+1]) );
//    han1_Comb->SetBinsPtee_forprojMee(binsPtee_forMee);
//    han1_Comb->SetBinsMee_forprojPtee(binsMee_forPtee);
//    han1_Comb->SetPlotRangeMee(plotMeeMin, plotMeeMax);
//    han1_Comb->SetPlotRangePtee(plotPteeMin, plotPteeMax);
//    han1_Comb->Process(LmHandler::kCombine);
//    hanVec1.push_back(han1_Comb);
//    
//    LmHandler* han2_Comb = new LmHandler();
//    han2_Comb->AttachSignal( *(sigVec2[ihan*2  ]) );
//    han2_Comb->AttachSignal( *(sigVec2[ihan*2+1]) );
//    han2_Comb->SetBinsPtee_forprojMee(binsPtee_forMee);
//    han2_Comb->SetBinsMee_forprojPtee(binsMee_forPtee);
//    han2_Comb->SetPlotRangeMee(plotMeeMin, plotMeeMax);
//    han2_Comb->SetPlotRangePtee(plotPteeMin, plotPteeMax);
//    han2_Comb->Process(LmHandler::kCombine);
//    hanVec2.push_back(han2_Comb);
//    
//    LmHandler* han3_Comb = new LmHandler();
//    han3_Comb->AttachSignal( *(sigVec3[ihan*2  ]) );
//    han3_Comb->AttachSignal( *(sigVec3[ihan*2+1]) );
//    han3_Comb->SetBinsPtee_forprojMee(binsPtee_forMee);
//    han3_Comb->SetBinsMee_forprojPtee(binsMee_forPtee);
//    han3_Comb->SetPlotRangeMee(plotMeeMin, plotMeeMax);
//    han3_Comb->SetPlotRangePtee(plotPteeMin, plotPteeMax);
//    han3_Comb->Process(LmHandler::kCombine);
//    hanVec3.push_back(han3_Comb);
//    
//    LmHandler* han4_Comb = new LmHandler();
//    han4_Comb->AttachSignal( *(sigVec4[ihan*2  ]) );
//    han4_Comb->AttachSignal( *(sigVec4[ihan*2+1]) );
//    han4_Comb->SetBinsPtee_forprojMee(binsPtee_forMee);
//    han4_Comb->SetBinsMee_forprojPtee(binsMee_forPtee);
//    han4_Comb->SetPlotRangeMee(plotMeeMin, plotMeeMax);
//    han4_Comb->SetPlotRangePtee(plotPteeMin, plotPteeMax);
//    han4_Comb->Process(LmHandler::kCombine);
//    hanVec4.push_back(han4_Comb);
//    
//    LmHandler* han5_Comb = new LmHandler();
//    han5_Comb->AttachSignal( *(sigVec5[ihan*2  ]) );
//    han5_Comb->AttachSignal( *(sigVec5[ihan*2+1]) );
//    han5_Comb->SetBinsPtee_forprojMee(binsPtee_forMee);
//    han5_Comb->SetBinsMee_forprojPtee(binsMee_forPtee);
//    han5_Comb->SetPlotRangeMee(plotMeeMin, plotMeeMax);
//    han5_Comb->SetPlotRangePtee(plotPteeMin, plotPteeMax);
//    han5_Comb->Process(LmHandler::kCombine);
//    hanVec5.push_back(han5_Comb);
    
  }
  
  bench->Show("handler_processing");
  
//  for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
//    hanVec.at(0)->PrintCompareSig_Mee(i);
//  }
  
  //return 0;
  
//  LmHandler* hanCompBkgs = new LmHandler(LmHandler::kCompare);
//  // attach signals to compare handler. they may already be processed or not.
//  for (unsigned int i=0; i<hanVec.size(); i++) {
//    hanCompBkgs->AttachSignal(*(hanVec.at(i)->GetLmSigCombined()), "Geom");
//    hanCompBkgs->AttachSignal(*(hanVec1.at(i)->GetLmSigCombined()), "Arith");
//    hanCompBkgs->AttachSignal(*(hanVec2.at(i)->GetLmSigCombined()), "GeomFit");
//    hanCompBkgs->AttachSignal(*(hanVec3.at(i)->GetLmSigCombined()), "ArithFit");
//    hanCompBkgs->AttachSignal(*(hanVec4.at(i)->GetLmSigCombined()), "Hybrid");
//    hanCompBkgs->AttachSignal(*(hanVec5.at(i)->GetLmSigCombined()), "HybridFit");
//  }
//  hanCompBkgs->SetBinsPtee_forprojMee(binsPtee_forMee);
//  hanCompBkgs->SetBinsMee_forprojPtee(binsMee_forPtee);
//  hanCompBkgs->SetPlotRangeMee(plotMeeMin, plotMeeMax);
//  hanCompBkgs->SetPlotRangePtee(plotPteeMin, plotPteeMax);
//  hanCompBkgs->SetPlotRangeRatio(0.01, 1.99);
//  hanCompBkgs->SetDoRatio(kDoRatio, 0.3);
//  //hanCompBkgs->Process(LmHandler::kCompare); // not needed if the attached signals were processed by a previous handler.
//  
//  for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
//    hanCompBkgs->PrintCompareSig_Mee(i);
//  }
////  for (unsigned int i = 0; i < binsMee_forPtee.size(); ++i){
////    hanCompBkgs->PrintCompareSig_Ptee(i);
////  }
//  
//  return 0;
  
  
  
  // cocktail managers (organize input)
  // for resonances
  LmCocktailMan* cocktmanReso = new LmCocktailMan();
  cocktmanReso->SetInputfiles(const_cast<char*>(cocktail_files[which_cockt_files].Data()));
  cocktmanReso->SetInputhistAndDim(const_cast<char*>(cocktail_histograms[which_cockt_hists].Data()), 2); // 2D
  cocktmanReso->SetUndoBinwidthNormalizationMee();
  cocktmanReso->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanReso->Process(LmCocktailMan::kResonances);
  // for heavy flavours
  LmCocktailMan* cocktmanHF = new LmCocktailMan();
  cocktmanHF->SetInputfiles(const_cast<char*>(heavyfl_files[which_heavyfl_files].Data()));
  cocktmanHF->SetInputhistAndDim(const_cast<char*>(heavyfl_histograms[which_heavyfl_hists].Data()), 2); // 2D
  cocktmanHF->SetHistForNeventsHF(const_cast<char*>(heavyfl_hist_Nevents[which_heavyfl_hists].Data()));
  cocktmanHF->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanHF->Process(LmCocktailMan::kHeavyFl);
  // for virtual photons
  // (not available yet)
  
  // cocktail (handles the cocktail spectra)
  Int_t collsystem = -1;
  if (which_cockt_files==0) collsystem = LmCocktail::kPbPb_0010_276;
  if (which_cockt_files==1) collsystem = LmCocktail::kPbPb_2050_276;
  if (which_cockt_files==2) collsystem = LmCocktail::kPbPb_1050_276;
  LmCocktail* cockt00 = new LmCocktail(collsystem);
  cockt00->AttachManager( *cocktmanReso );
  cockt00->AttachManager( *cocktmanHF );
  //  cockt00->SetCrosssection_Event(); // cross sections and ncolls should instead be specified in LmCocktail constructor.
  //  cockt00->SetCrosssection_pp();
  //  cockt00->SetNcollCharm();
  cockt00->Process(); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...
  
  // only needed if cocktail shall be projected and plotted stand-alone:
  cockt00->SetBinsPtee_forprojMee(binsPtee_forMee);
  cockt00->SetBinsMee_forprojPtee(binsMee_forPtee);
  cockt00->MakeSpectra1D(); // do projections according to attached binning.
  for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
    cockt00->PrintCocktail_Mee(i, Form("hCocktailMee_bin%d.pdf", i));
  }
  
  
  LmHandler* hanCompare = new LmHandler(LmHandler::kCompare);
  // attach signals to compare handler. they may already be processed or not.
  for (unsigned int i=0; i<hanVec.size(); i++) {
    hanCompare->AttachSignal(*(hanVec.at(i)->GetLmSigCombined()), hanVec.at(i)->GetLmSigCombined()->GetName());
  }
  hanCompare->SetBinsPtee_forprojMee(binsPtee_forMee);
  hanCompare->SetBinsMee_forprojPtee(binsMee_forPtee);
  hanCompare->SetPlotRangeMee(plotMeeMin, plotMeeMax);
  hanCompare->SetPlotRangePtee(plotPteeMin, plotPteeMax);
//  hanCompare->SetPlotRangeRatio(0.01, 1.99);
//  hanCompare->SetDoRatio(kDoRatio, 0.3);
  hanCompare->SetConfidenceLevel(confLevel);
  hanCompare->SetDoConfidenceLevel(kDoConfLevel);
//  hanCompare->Process(LmHandler::kCompare); // not needed if the attached signals were processed by a previous handler.
  
  hanCompare->SetCocktail(cockt00); // attach complete cocktail to handler. call cockt00->Process() before!
  //hanCompare->SetDrawStyleCocktail("hist c"); // default is "hist"
  hanCompare->Process(LmHandler::kCocktail); // create projections of cocktail spectra in the projection binning of the handler. they are stored in each LmCocktailPart.
  
  Bool_t printLegend=kTRUE;
  
  
  for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
    //hanCompare->SetPlotRangeYcompareMee(i);
    
    //hanCompare->PrintCompare(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, i, LmBaseSignal::kProjOnMee); // works
    hanCompare->PrintCompareSig_Mee(i, printLegend);
//    hanCompare->PrintCompareSoverB_Mee(i, printLegend);
//    hanCompare->PrintCompareSignif_Mee(i, printLegend);
//    hanCompare->PrintCompareSigBkg_Mee(i, printLegend);
    
    //hanCompare->SetPlotRangeY(0.8, 1.2);
    //hanCompare->PrintCompareRfactor_Mee(i, printLegend, Form("hRfactor_Mee_bin%d.pdf", i));
    // R-factor fails, needs to be caught!
    //    hanCompare->PrintCompare(LmSignal::kRfactor, i, LmBaseSignal::kProjOnMee, Form("hCompareSig_Mee_bin%d.pdf", i), printLegend);
  }
  hanCompare->ResetPlotRangeY();
  
//  if (kDoEffiCorrection) hanCompare->SetPlotRangeY(5e-5, 1e+1); // with effi corr
//  else                   hanCompare->SetPlotRangeY(5e-6, 1e+0);
  for (unsigned int i = 0; i < binsMee_forPtee.size(); ++i){
    hanCompare->PrintCompareSig_Ptee(i, printLegend);
//    hanCompare->PrintCompareSoverB_Ptee(i, printLegend);
//    hanCompare->PrintCompareSignif_Ptee(i, printLegend);
//    hanCompare->PrintCompareSigBkg_Ptee(i, printLegend);
  }
  hanCompare->ResetPlotRangeY();
  
  
  
  cout << "__________ __________ FITTING __________ __________" << endl;
  cout << "^^^^^^^^^^ ^^^^^^^^^^ ^^^^^^^ ^^^^^^^^^^ ^^^^^^^^^^" << endl;
  
  const UInt_t n_bins = binsPtee_forMee.size();
  
  for (unsigned int i_bin = 0; i_bin < n_bins; ++i_bin)
  {
    
    // datapoints
    TH1D* hData = hanCompare->GetLmSignalI(0)->GetSubSig( i_bin, LmBaseSignal::kProjOnMee )->GetDatahist();
    hData->SetTitle("data, unfiltered");
    hData->SetAxisRange(plotMeeMin, plotMeeMax-LmHelper::kSmallDelta, "X");
    // charm
    TH1D* hCharm00  = cockt00->GetComponent1D( LmCocktailPart::kCharm, i_bin, LmBaseSignal::kProjOnMee );
    hCharm00->SetTitle("QM '14");
//    TH1D* hCharm01  = cockt01->GetComponent1D( LmCocktailPart::kCharm, i_bin, LmBaseSignal::kProjOnMee );
//    hCharm01->SetTitle("Perugia2011");
//    TH1D* hCharm02  = cockt02->GetComponent1D( LmCocktailPart::kCharm, i_bin, LmBaseSignal::kProjOnMee );
//    hCharm02->SetTitle("PowhegPerugia2011");
    // cocktail sum w/o charm
    TH1D* hCocktSum = cockt00->GetSum1D( i_bin, LmBaseSignal::kProjOnMee );
    TH1D* hCockt_wo_charm = (TH1D*) hCocktSum->Clone("hCockt_wo_charm");
    hCockt_wo_charm->SetTitle("QM '14");
    hCockt_wo_charm->Add(hCharm00, -1.);
    // photons
    TH1D* hGamma    = cockt00->GetComponent1D( LmCocktailPart::kOmega, i_bin, LmBaseSignal::kProjOnMee );
    hGamma->SetTitle("omega_as_gamma");
    
    
    //////// CHARM FIT. //////////
    
    //    LmFitter* fitter = new LmFitter();
    //    fitter->SetDatahist( hData );
    //    fitter->AttachFitTemplateA( hCockt_wo_charm );
    //    fitter->AttachFitTemplateB( hCharm00 );
    //    
    //    // Configure the fit with default options. May be done or modified manually if desired...
    //    fitter->PrepareFitCharm(1.2, 2.5);
    //    fitter->Process(); // Type may be left empty if 'PrepareFit...()' was called before. // LmFitter::kTwoTempl
    //    fitter->PrintFitStatus();
    //    fitter->PrintBestFit(    Form("cLmFitter-pPb-charm-Mee_bin%d-best.pdf", i_bin));
    //    fitter->PrintCompareFits(Form("cLmFitter-pPb-charm-Mee_bin%d-compare.pdf", i_bin));
    
    //////// VIRTUAL PHOTON FIT. NORMALIZATION DOESNT WORK WITH PREFILTERED SPECTRA! //////////
    
    LmFitter* fitter = new LmFitter();
    hData->SetAxisRange(0., 0.5-LmHelper::kSmallDelta, "X");
    fitter->SetDatahist( hData );
    fitter->AttachFitTemplateA( hCockt_wo_charm );
    fitter->AttachFitTemplateB( hGamma );
    fitter->AttachFitTemplateC( hCharm00 );
    
    // normalization at very low mass. determine par[1] by fixing par[0] to half.
    //fitter->PrepareFitVirtPhot_Normalization(0.06, 0.15); // norm. range for PREfiltered spectra! // should include min 2 bins
    fitter->PrepareFitVirtPhot_Normalization(0., 0.06); // norm. range for UNfiltered spectra! // should include min 2 bins
    fitter->Process(); // Type may be left empty if 'PrepareFit...()' was called before. // LmFitter::kThreeTempl_OneNorm_PlusBaseline
    fitter->PrintFitStatus();
    fitter->PrintBestFit(    Form("cLmFitter-PbPb-Mee_bin%d-best-1norm.pdf", i_bin));
    
    // extract virt. photon fraction. determine par[0] by fixing par[1].
    fitter->PrepareFitVirtPhot_Extraction(0.15, 0.5);
    fitter->Process(); // Type may be left empty if 'PrepareFit...()' was called before. // LmFitter::kThreeTempl_OneNorm_PlusBaseline
    fitter->PrintFitStatus();
    fitter->PrintBestFit(    Form("cLmFitter-PbPb-Mee_bin%d-best-2extract.pdf", i_bin));
    //fitter->PrintCompareFits(Form("cLmFitter-PbPb-Mee_bin%d-compare-2extract.pdf", i_bin));
  }
  
  
  //
  // write most important histograms to rootfiles:
  //
  // add bits of histograms you want to store: LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg+LmSignal::kSoverB+LmSignal::kSignif
  // to store all of them, you can also use LmSignal::kMAXhist-1
  //
//  const Char_t* filename = "spectra1D_Mee.root";
//  TFile* _fileOut = new TFile(filename, "RECREATE");
//  //  hanCompare->SetRootfile(_fileOut);
//  hanCompare->SetSimpleHistnames(kTRUE); // use option kTRUE for short histogram names in rootfile or kFALSE for long, more informative histogram names.
//  // for combine handler:
//  // hanCombine->Write1DHistCombined(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg+LmSignal::kSoverB+LmSignal::kSignif, LmSignal::kProjOnMee);
//  // hanCombine->Write1DHistSingle(LmSignal::kRfactor, LmSignal::kProjOnMee);
//  // for compare handler:
//  hanCompare->Write1DHistSingle(LmSignal::kSubSig+LmSignal::kSoverB+LmSignal::kSignif, LmSignal::kProjOnMee);
//  //hanCompare->Write1DHistSingle(LmSignal::kRfactor, LmSignal::kProjOnMee); // kRfactor only if it is not made of combined signals!
//  _fileOut->Close();
  
  
  std::cout << "main.cpp done :-)" << std::endl;
  return 0;
}

// */
