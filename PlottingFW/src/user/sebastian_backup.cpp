//Analysis Framework for Dilepton Spectra

// c++ includes
#include <iostream>
#include <vector>
using namespace std;
// ROOT includes
#include "TString.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TBenchmark.h"
// project includes
#include "sebastian.h"
#include "LmManager.h"
#include "LmBackground.h"
#include "LmBaseSignal.h"
#include "LmSignal.h"
#include "LmHandler.h"
#include "LmHelper.h"
#include "LmCocktailMan.h"
#include "LmCocktail.h"
#include "LmFitter.h"

int main()
{
  LmHelper lmHelper;
 
  
  //Projection of 2D to 1D take a closer look
  std::vector<Double_t> binsMee_forDCA; //x-Axis --> dca
//  binsMee_forDCA.push_back(0.0);
  binsMee_forDCA.push_back(0.05);
  binsMee_forDCA.push_back(0.15);
  binsMee_forDCA.push_back(1.20);
  binsMee_forDCA.push_back(2.80);
  binsMee_forDCA.push_back(3.20);
//  for (int i = 0; i <= n_mee_bin; ++i) {
//    binsMee_forDCA.push_back(mee_bin[i]); //put Mee binning from sebastian.h 
//  }
  std::vector<Double_t> binsDCA_forMee; //x-Axis --> dca
  for (int i = 0; i <= n_dca_bin; ++i) {
    binsDCA_forMee.push_back(dca_bin[i]); //put Mee binning from sebastian.h 
  }
  
  Double_t plotDCAMin  = 0.  , plotDCAMax  = 10.;
  Double_t plotPteeMin = 0.  , plotPteeMax = 5.0;
  Double_t plotMeeMin  = 0.05, plotMeeMax  = 3.2;
 
  
  //New LmManager to set labels etc right in external signal
  LmManager *manExt = new LmManager(const_cast<char*>(cconfig[0].Data()));
    manExt->SetEtaRange(-0.8,0.8);
    manExt->SetPtRange(0.2,5.);
  //new LmSignal for external input, this can be handed to a compare handler
  LmSignal *sigD_MC    = new LmSignal("MC D Mesons",LmSignal::kExternal1D);
  LmSignal *sigB_MC    = new LmSignal("MC B Mesons",LmSignal::kExternal1D);
  LmSignal *sigPi0_MC  = new LmSignal("MC Pi0 Mesons",LmSignal::kExternal1D);
  LmSignal *sigJPsi_MC = new LmSignal("MC JPsi Mesons",LmSignal::kExternal1D);
  sigD_MC   ->SetManager(manExt,kFALSE);
  sigB_MC   ->SetManager(manExt,kFALSE);
  sigPi0_MC ->SetManager(manExt,kFALSE);
  sigJPsi_MC->SetManager(manExt,kFALSE);
  //Binning for invariant mass in this bin is set in sebastian.h
  //Open file with external input
  TFile *f_extFile0 = TFile::Open("./input/MC_out.root");        //all D Mesons
  //TFile *f_extFile0 = TFile::Open("./input/Charm_corr.root");   //only correlated D Mesons
    TH1D* h_inD_MC[5];
    TH1D* h_inPi0_MC[5];
    TH1D* h_inB_MC[5];
    TH1D* h_inJPsi_MC[5];
    for (int i = 0; i < 4; ++i) {
      //this one is a little dirty -> mee_bin[] is not really in the external file but should have same binning
      h_inD_MC[i]    = (TH1D*) f_extFile0 -> Get(Form("D_PairDCA_invM_%3.2f_%3.2f",mee_bin[i],mee_bin[i+1]));  
      h_inB_MC[i]    = (TH1D*) f_extFile0 -> Get(Form("B_PairDCA_invM_%3.2f_%3.2f",mee_bin[i],mee_bin[i+1]));  
      h_inPi0_MC[i]  = (TH1D*) f_extFile0 -> Get(Form("Pi0_PairDCA_invM_%3.2f_%3.2f",mee_bin[i],mee_bin[i+1]));  
      h_inJPsi_MC[i] = (TH1D*) f_extFile0 -> Get(Form("JPsi_PairDCA_invM_%3.2f_%3.2f",mee_bin[i],mee_bin[i+1]));  
      h_inD_MC[i]   ->SetTitle(Form("D: %3.2f #leq m_{ee} #leq  %3.2f",mee_bin[i],mee_bin[i+1]));  
      h_inB_MC[i]   ->SetTitle(Form("B: %3.2f #leq m_{ee} #leq %3.2f",mee_bin[i],mee_bin[i+1]));  
      h_inPi0_MC[i] ->SetTitle(Form("#pi^{0}: %3.2f #leq m_{ee} #leq  %3.2f",mee_bin[i],mee_bin[i+1]));  
      h_inJPsi_MC[i]->SetTitle(Form("J/#Psi: %3.2f #leq m_{ee} #leq %3.2f",mee_bin[i],mee_bin[i+1]));  
      h_inD_MC[i]   ->SetLineWidth(2);
      h_inB_MC[i]   ->SetLineWidth(2);
      h_inPi0_MC[i] ->SetLineWidth(2);
      h_inJPsi_MC[i]->SetLineWidth(2);
      h_inD_MC[i]   ->SetLineColor(kMagenta);
      h_inB_MC[i]   ->SetLineColor(kGreen+2);
      h_inPi0_MC[i] ->SetLineColor(kRed);
      h_inJPsi_MC[i]->SetLineColor(kYellow+1);
      //Additonal to normalize external input on number of entries 
      if (kDoNormNentries && h_inD_MC[i]->Integral()>1.)    h_inD_MC[i]   ->Scale(1/h_inD_MC[i]->Integral());
      if (kDoNormNentries && h_inB_MC[i]->Integral()>1.)    h_inB_MC[i]   ->Scale(1/h_inB_MC[i]->Integral());
      if (kDoNormNentries && h_inPi0_MC[i]->Integral()>1.)  h_inPi0_MC[i] ->Scale(1/h_inPi0_MC[i]->Integral());
      if (kDoNormNentries && h_inJPsi_MC[i]->Integral()>1.) h_inJPsi_MC[i]->Scale(1/h_inJPsi_MC[i]->Integral());
      
      sigD_MC    -> AddProjection(h_inD_MC[i],    LmSignal::kSubSig ,LmBaseSignal::kProjOnMee);
      sigB_MC    -> AddProjection(h_inB_MC[i],    LmSignal::kSubSig ,LmBaseSignal::kProjOnMee);
      sigPi0_MC  -> AddProjection(h_inPi0_MC[i],  LmSignal::kSubSig ,LmBaseSignal::kProjOnMee);
      sigJPsi_MC -> AddProjection(h_inJPsi_MC[i], LmSignal::kSubSig ,LmBaseSignal::kProjOnMee);
    }


//Nochmal neu und ordentlich schreiben!

  
  // create manager from config string
  LmManager* mgr00 = new LmManager(const_cast<char*>(cconfig[0].Data()));
  // (only one rootfile used, cannot compare to combined Pb-Pb output!)
  
  
  //set further configuration for the manager
  mgr00->SetInputhistAndDim("pInvMass_DCAsigma_pPt", 3);
  mgr00->SetProjOption("xy"); //this one hurts a little | its x vs y ... for DCA so its Minv vs DCA, so the DCAee is on the x axis, integrated for Ptee
  // set static variables stored in LmBaseSignal, which will be used as starting point for the axis titles of all spectra histograms.
//  LmBaseSignal::SetInputLabelX("#it{M}_{ee}","GeV/#it{c}^{2}"); //Mee is default
  LmBaseSignal::SetInputLabelY("#it{DCA}_{ee}","#sigma");
  LmBaseSignal::SetInputLabelZ("#it{p}_{T,ee}","GeV/#it{c}");
  LmBaseSignal::SetInputLabelContent("", "a.u."); // if empty -> compute automatically from x and y

  mgr00->SetRebinning2D(n_dca_bin, dca_bin,n_mee_bin, mee_bin);
  //mgr00->SetEnableRebinning(kFALSE); // use this to disable or just comment out the setter above...
  //
  // ...
  
  // read in histograms from data files
//  mgr00->ReadAllHistogramsFromFiles();
  //
  // 1) instead of mgr00->ReadAllHistogramsFromFiles(), please use:
  //
  // 2) remove all lines 'mgr00->CopyHistogramsFrom(...)'
  //
  // 3) instead of mgr00->Process(kFALSE), use:
  // mgr00->Process(LmManager::kDontReadInput); // dont read in rootfiles again
  //
  
  // make a copy of the manager including its input histograms
  mgr00->Process(LmManager::kReadInputOnly);


  // select different subranges in input histograms
//  mgr00->Set3DProjRangeX(0., 3.7);
  
  // process the managers: make the projections, rebinning, corrections...
  mgr00 ->Process(LmManager::kDontReadInput); // kFALSE: dont read in rootfiles again
  
  LmBackground *bkgIn = new LmBackground (*mgr00);
  bkgIn -> Process(LmBackground::kGeom);
  LmSignal *sigIn = new LmSignal(*mgr00, *bkgIn, "Data");
  sigIn -> SetDoSubtraction(kTRUE);
  sigIn -> SetDoSignifRaw(kDoSignifRaw);
  sigIn -> SetDoNormBinwidth(kDoNormBinwidth);
  sigIn -> SetDoNormNevents(kDoNormNevents);
  sigIn -> SetDoNormNentries(kTRUE);
  sigIn -> Process(LmSignal::kStd);
 

  
 //////////////////////////////////////////////////////////////
 
  LmHandler *hanCompare = new LmHandler(LmHandler::kCompare);
  hanCompare->AttachSignal(*sigIn);
  hanCompare->SetBinsY_forprojOnX(binsMee_forDCA);
  hanCompare->SetBinsX_forprojOnY(binsDCA_forMee);
  hanCompare->Process(LmHandler::kCompare);
  hanCompare->AttachSignal(*sigD_MC);
  hanCompare->AttachSignal(*sigB_MC);
  hanCompare->AttachSignal(*sigPi0_MC);
  hanCompare->AttachSignal(*sigJPsi_MC);
  hanCompare->SetPlotRangeMee (0., 10.);
  hanCompare->SetPlotRangePtee(plotDCAMin, 10.);

  //hanCompare->SetPlotRangeYMargins(2,20);
  for(unsigned int i = 0; i < binsMee_forDCA.size()-1; ++i){
//    cout << "max plot range: " << hanCompare->GetPlotRangeXMax() << endl;
    hanCompare->PrintCompare(LmSignal::kSubSig,i,LmBaseSignal::kProjOnMee, "+_norm_lin_410", kTRUE, kFALSE);
  }
 ////////////////////////////////////////////////////////////
 //              FITS! FITS! FITS!                         //
 ////////////////////////////////////////////////////////////
  TH1D* hData = 0x0;
  
  // +------------------------------------------------------------------+
  // | Pythia 8                                                         |
  // +------------------------------------------------------------------+
  // | g g -> c cbar                                  121 |   4.311e+01 |
  // | q qbar -> c cbar                               122 |   2.293e-01 |
  // | g g -> b bbar                                  123 |   2.282e+00 |
  // | q qbar -> b bbar                               124 |   1.657e-02 | 
  // +------------------------------------------------------------------+
  // | PDG Branchingratios                                              |
  // +------------------------------------------------------------------+
  // |D+/- -->  e+/- X                                    |       16.07 |  
  // |D0   -->  e+/- X                                    |        6.49 |
  // |B+/- -->  e+/- X                                    |       10.80 |
  // |B0   -->  e+/- X                                    |       10.10 |
  // +------------------------------------------------------------------+
  
  
  // This is not actually right copared to documentation but works
  Double_t Ratio_DB =1/(((4.311e+01+2.293e-01)/((16.07*2+6.49)/3))/((2.282e+00+1.657e-02)/((10.80*2+10.10)/3))); 
  cout << "Ratio_DB: " << Ratio_DB << endl;


  for (int i = 2; i < 4; ++i){
    // datapoints
    hData = (TH1D*) sigIn->GetSubSig(i,LmBaseSignal::kProjOnMee)->GetDatahist();
    hData->SetTitle("data");
    hData->SetAxisRange(1e-5,40, "Y");

    //////// CHARM FIT. //////////

    LmFitter* fitter = new LmFitter();
    fitter->SetDatahist( hData ); 
    fitter->AttachFitTemplateA( h_inD_MC[i] );
    fitter->AttachFitTemplateB( h_inB_MC[i] );
    fitter->AttachFitTemplateC( h_inJPsi_MC[i] );
    fitter->SetFixPar(0,Ratio_DB);

    fitter->SetFitOpt("I"); // options to suppress drawing ("N0") are added internally.

    fitter->SetXmin(0);
    fitter->SetXmax(10);
    fitter->Process(LmFitter::kThreeTempl_OneNorm_PlusBaseline, Form("Fit_%d.pdf",i));

    fitter->PrintFitStatus();
 
    delete hData;
    delete fitter;
  }
  
  
  std::cout << "main.cpp done :-)" << std::endl;
  return 0;
}


