#include <iostream>

#include "LmQA.h"
#include "TLegend.h"
#include "carsten_phiV.h"
#include "TSystem.h"

void Init();
void Analyse();
int QA();
int PhiVstudy();


int main(int argc, char* argv[]){
  gErrorIgnoreLevel = kWarning;
  gStyle->SetNumberContours(255);
  if (argc == 2){
    if (std::string(argv[1]) == "QA"){
      QA();
    }
    if (std::string(argv[1]) == "Analysis"){
      Init();
      Analyse();    }
    if (std::string(argv[1]) == "phiV"){
      Init();
      PhiVstudy();    }
  }
  else{
    std::cout << "Specify 'QA' or 'Analysis'" << std::endl;
  }

  return 0;
}

void Init()
{
  gErrorIgnoreLevel = kWarning;
  LmHelper lmHelper;
  LmHelper::SetCanvasHeight(1200);
  LmHelper::SetCanvasWidth(1200);

  // defaults
  kDoInclusive   = kTRUE;
  kDoPt400  = 1;
  kDoPref   = 0;
  kDoEffGen = 0;

  // manual settings
  printLegend  = kTRUE;
  plotAverage  = kFALSE;
  plotWeightAv = kFALSE;
  writeFile    = kFALSE;

  // plotting
  plotMeeMin  = 0.; plotMeeMax  = 2.69;   plotMeeMax_sys  = 3.3; //mee_bin_systematic[n_mee_bin_systematic];
  plotPteeMin = 0.; plotPteeMax = 5.000; plotPteeMax_sys = ptee_bin_systematic[n_ptee_bin_systematic];
  LmBaseSignal::SetInputLabelZ("#it{#phi}_{V}","rad", "PhiV");
  LmBaseSignal::SetLabelSig("#it{N}_{S}");
  LmBaseSignal::SetLabelBkg("#it{N}_{B}");
  // binning
  binsMee_forPtee_sys.push_back(0.);
  binsMee_forPtee_sys.push_back(0.14);
  binsMee_forPtee_sys.push_back(5.);

  binsPtee_forMee_sys.push_back(0.);
  binsPtee_forMee_sys.push_back(8.);



  binsPtee_forMee.push_back(0.);
  binsPtee_forMee.push_back(1.);
  binsPtee_forMee.push_back(2.);
  // binsPtee_forMee.push_back(3.);
  // binsPtee_forMee.push_back(4.);
  binsPtee_forMee.push_back(8.);

  binsMee_forPtee.push_back(0.); // TODO: get/check closest existing values from array mee_bin[]
  binsMee_forPtee.push_back(0.06);
  binsMee_forPtee.push_back(0.14);
  binsMee_forPtee.push_back(0.74);
  binsMee_forPtee.push_back(1.1);
  binsMee_forPtee.push_back(2.7);
  binsMee_forPtee.push_back(3.3);
  binsMee_forPtee.push_back(5.0);

  binsMee_forPhiV.push_back(0.);
  //  binsMee_forPhiV.push_back(0.01); // test
  binsMee_forPhiV.push_back(0.02);
  //  binsMee_forPhiV.push_back(0.03); // test
  binsMee_forPhiV.push_back(0.04);
  binsMee_forPhiV.push_back(0.06);
  binsMee_forPhiV.push_back(0.10);
  binsMee_forPhiV.push_back(0.14);
  binsMee_forPhiV.push_back(0.22);
}
//_______________________________________________________________________________________________
int PhiVstudy()
{
  LmHelper::Info("========== doPhiVstudy ==========");
  //
  std::vector<LmManager*>     mgrVec; // works when using pointers (they survive after the for-loop). otherwise fancy errors.
  std::vector<LmBackground*>  bkgVec;
  std::vector<LmSignal*>      sigVec;
  std::vector<LmManager*>     mgrVec_inputs;
  {
    TString projOpt = "xz"; // option="ab" means: a vertical, b horizontal (ROOT-convention)

    // Add all configs to LmFileManager for efficient file handling
    for (int ic=0; ic<n_config; ic++) {
      LmFileManager::Instance()->AddConfig( cconfig[ic] );
    }
    std::vector<Double_t> binsPhiV;
    binsPhiV.push_back(0.);
    binsPhiV.push_back(TMath::Pi());

    Double_t phiv_bin[] = { 5 };
    Double_t phiv_bin_1[] = { 1 };
    Int_t n_phiv_bin = sizeof(phiv_bin)/sizeof(*phiv_bin) -1;

    Double_t* phiv_bin_local=0x0;
    Int_t phiv_rebinfactor=1; // 1 or 4
    phiv_bin_1[0]*=phiv_rebinfactor;
    phiv_bin[0]*=phiv_rebinfactor;

    // fill vector of input managers
    for (int ic=0; ic<n_config; ic++)
    {
      LmManager* mgr = new LmManager(const_cast<char*>(cconfig[ic].Data()));// (only one rootfile, instead of low+high)
      // set further configuration for the manager
      mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
      phiv_bin_local = &phiv_bin[0];

      mgr->SetProjOption(projOpt.Data());
      mgr->SetEnableEffiCorr(kDoEffiCorrection);
      mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
      mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
      mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
      mgr->SetTemplateNormRegionMin(n_cutPhiVbelow, cutPhiVbelow); // only needed for some template types.
      mgr->SetTemplateNormRegionMax(n_cutPhiVabove, cutPhiVabove); // only needed for some template types.
      // use individual phiV cut settings:
      mgr->SetEnableExclusionCutZ(LmManager::kNoCut); // to be able to change or deactivate the cut without changing the code above.

      if (projOpt.EqualTo("xz")) // 'xz' means mee on y, phiv on x
        mgr->SetRebinning2D(n_phiv_bin, phiv_bin_local, n_mee_bin, mee_bin);
      if (projOpt.EqualTo("yz")) // 'yz' means ptee on y, phiv on x
        mgr->SetRebinning2D(n_phiv_bin, phiv_bin_local, n_ptee_bin, ptee_bin);
      if (projOpt.EqualTo("yx")) // 'yx' means ptee on y, mee on x (default analysis)
        mgr->SetRebinning2D(n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
      // read in histograms from data files
      mgr->Process(LmManager::kReadInputOnly);
      mgrVec_inputs.push_back(mgr);
    }

    // define 3D-projection binning
    // at least one of these two arrays should have only a single integrated bin, otherwise we get many managers...
    // since there is only one handler for all signals, all 3D-subranges - if any - will be plotted together.
    Double_t bins3DProjRangeX[] = { -1, -1 }; // mee
    Double_t bins3DProjRangeY[] = { 0., 1., 2., 3., 8. }; // ptee
//    Double_t bins3DProjRangeY[] = { 1., 2. }; // ptee
//    Double_t bins3DProjRangeY[] = { 2., 4. }; // ptee
//    Double_t bins3DProjRangeY[] = { 4., 6. }; // ptee
//    Double_t bins3DProjRangeY[] = { 0., 4. }; // ptee
    unsigned int n_bins3DProjRangeX = sizeof(bins3DProjRangeX)/sizeof(*bins3DProjRangeX) -1;
    unsigned int n_bins3DProjRangeY = sizeof(bins3DProjRangeY)/sizeof(*bins3DProjRangeY) -1;
    if (n_bins3DProjRangeX>1) LmHelper::Error("computation of phiV-corrected spectra with templates for multiple mee slices at the same time is messed up!");
    if (n_bins3DProjRangeY>1) LmHelper::Error("computation of phiV-corrected spectra with templates for multiple ptee slices at the same time is messed up!");

    // fill vector of managers with selected 3D subranges
    for (unsigned int iproj_x=0; iproj_x<n_bins3DProjRangeX; iproj_x++)
    {
      for (unsigned int iproj_y=0; iproj_y<n_bins3DProjRangeY; iproj_y++)
      {
        for (unsigned int imgr=0; imgr<mgrVec_inputs.size(); imgr++) {
          // make a copy of the manager including its input histograms
          LmManager* mgr_i = new LmManager(*(mgrVec_inputs.at(imgr)));
          if (n_bins3DProjRangeY>1 || bins3DProjRangeY[0]!=0 || bins3DProjRangeY[1]==1)
            mgr_i->SetName(Form("%s (%.0f-%.0f GeV)",mgr_i->GetName(), bins3DProjRangeY[iproj_y], bins3DProjRangeY[iproj_y+1])); // cannot use "/c" when saving it to rootfile.
          // select different subranges in input histograms
          mgr_i->Set3DProjRangeX(bins3DProjRangeX[iproj_x], bins3DProjRangeX[iproj_x+1]);
          mgr_i->Set3DProjRangeY(bins3DProjRangeY[iproj_y], bins3DProjRangeY[iproj_y+1]);
          // add new manager to vector
          mgrVec.push_back(mgr_i);
        }
        // add manager for integrated y range, if there is more than one bin in y. (nicer to have a separate loop)
        if (n_bins3DProjRangeY>1 && iproj_y==n_bins3DProjRangeY-1) {
          for (unsigned int imgr=0; imgr<mgrVec_inputs.size(); imgr++) {
            LmManager* mgr_i = new LmManager(*(mgrVec_inputs.at(imgr)));
            mgr_i->SetName(Form("%s (%.0f-%.0f GeV)",mgr_i->GetName(), bins3DProjRangeY[0], bins3DProjRangeY[iproj_y+1])); // cannot use "/c" when saving it to rootfile.
            mgr_i->Set3DProjRangeX(bins3DProjRangeX[0], bins3DProjRangeX[iproj_x+1]);
            mgr_i->Set3DProjRangeY(bins3DProjRangeY[0], bins3DProjRangeY[iproj_y+1]);
            mgrVec.push_back(mgr_i);
          }
        }
      }
    }

    // for each manager: create background and signal class from it, configure and process them, store them in vectors
    for (unsigned int iproj=0; iproj<mgrVec.size(); iproj++)
    {
      std::cout << " iproj = " << iproj << " name = " << mgrVec.at(iproj)->GetName() << std::endl;
      // process the managers: make the projections, rebinning, corrections...
      mgrVec.at(iproj)->Process(LmManager::kDontReadInput); // dont read in rootfiles again
      //mgrVec.at(iproj)->Print2DUnlike(Form("c2DUnlike_%d.pdf",iproj));

      LmBackground* bkg_i = new LmBackground(*(mgrVec.at(iproj)));
      bkg_i->SetUseRfactor(kUseRFactor);
      bkg_i->Process(LmBackground::kArith);
      bkgVec.push_back(bkg_i);

      TString signame = mgrVec.at(iproj)->GetName();
//      signame.Append(" "+mgrVec.at(iproj)->GetAll3DProjRanges());
      if (mgrVec.at(iproj)->GetExclCutType()==LmManager::kTemplUnsub) signame.Append(" matched");
      if (mgrVec.at(iproj)->GetExclCutType()==LmManager::kTemplConv)  signame.Append(" - conv");
      if (mgrVec.at(iproj)->GetExclCutType()==LmManager::kTemplSub) {
        // try to add an uncut subtracted signal to help in the phiV correction of the current signal.
        // if (mgrVec.at(0)->GetExclCutType()==LmManager::kNoCut)
        //   mgrVec.at(iproj)->AddVisualSig(sigVec.at(0)->GetSubSig2D(),"hDataOrig","data, no #phi_{V} corr.");
      }

      LmSignal* sig_i_Std = new LmSignal(*(mgrVec.at(iproj)), *(bkgVec.at(iproj)), signame.Data()); //Form("Projection_%d", iproj)
      sig_i_Std->SetDoSubtraction(kTRUE);
      sig_i_Std->SetDoSignifRaw(kDoSignifRaw);
      sig_i_Std->SetDoNormBinwidth( kDoNormBinwidth );
      sig_i_Std->SetDoNormNevents(kDoNormNevents);
      sig_i_Std->Process(LmSignal::kStd);
      // if a signal has produced additional histograms, e.g. to visualize its phiV-correction, then extract them for plotting.
      sigVec.push_back(sig_i_Std);
    }

    // close rootfile(s) from input manager(s) (to free memory if many files have been opened...)
    for (unsigned int imgr=0; imgr<mgrVec_inputs.size(); imgr++) {
      mgrVec_inputs.at(imgr)->Process(LmManager::kCleanUp);
    }

    Double_t plotPhiVMin = 0., plotPhiVMax = 3.14; // phiv
    Bool_t kDoLegend=kTRUE;
    Bool_t kDoLogY=kFALSE;

    LmHandler* han_compare = new LmHandler(LmHandler::kCompare);
    han_compare->SetFileType("png");
    // attach signals to compare handler. they may already be processed or not.
    for (unsigned int i=0; i<sigVec.size(); i++) {
      han_compare->AttachSignal(*(sigVec.at(i)), sigVec.at(i)->GetName());
    }
    if (projOpt.EqualTo("xz")) { // 'xz' means mee on y, phiv on x
      han_compare->SetBinsY_forprojOnX(binsMee_forPhiV);
      han_compare->SetBinsX_forprojOnY(binsPhiV);
      han_compare->SetPlotRangeMee(plotPhiVMin, plotPhiVMax);
      han_compare->SetPlotRangePtee(plotMeeMin, plotMeeMax);
      kDoLogY=kFALSE;
    }

    han_compare->SetPlotRangeRatio(0.1, 3);
    han_compare->SetDoRatio(kDoRatio, 0.3, kFALSE);
    han_compare->Process(LmHandler::kCompare); // not needed if the attached signals were processed by a previous handler.

    UInt_t histbits=1;
    TString s3Drange="";

    for (int i = 0; i <= han_compare->GetMaxBinProj(LmBaseSignal::kProjOnX); ++i){

      histbits=LmSignal::kSubSig;//+LmSignal::kUnlike+LmSignal::kBkg;
      han_compare->PrintCompare(histbits, i, LmBaseSignal::kProjOnX, Form("+%s%s","TEST", s3Drange.Data()), kDoLegend, kDoLogY);
    }

    han_compare->ResetPlotRangeY();

    if (projOpt.EqualTo("xz")) { // 'xz' means mee on y, phiv on x
      han_compare->SetPlotRangeY(2e-4, 1e1);
      for (int i = 0; i <= han_compare->GetMaxBinProj(LmBaseSignal::kProjOnY); ++i){
        han_compare->PrintCompare(LmSignal::kSubSig, i, LmBaseSignal::kProjOnY, Form("+_phiVstud%s%s","TEST", s3Drange.Data()), kDoLegend);
      }
      han_compare->ResetPlotRangeY();
    }

    // write most important histograms to rootfile:

    std::cout << "PhiVstudy done :-)" << std::endl;
  }
  LmFileManager::Instance()->Clear();
  mgrVec.clear();
  bkgVec.clear();
  sigVec.clear();
  mgrVec_inputs.clear();
  return 0;
} // PhiVstudy


void Analyse(){

  // automatic settings
  if (kDoInclusive==kTRUE)   sOptCent="incl";    else sOptCent="semi";
  if (kDoPt400==1)  sOptPt  ="pt400";   else sOptPt  ="pt200";
  if (kDoPref==1)   sOptPref="Pref";    else sOptPref="NoPref";
  if (kDoEffGen==1) sOptEff ="EffiGen"; else sOptEff ="EffiMeas";
  //Bool_t doBothPref = (kDoNoPref&&kDoPref);


  filename2D_sys = Form("spectra2D_sys_%s_%s_%s_%s.root",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data());
  filename2D_ana = Form("spectra2D_ana_%s_%s_%s_%s.root",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data());
  extpath_sys    = TString("./input/data_2Dsignals/"+filename2D_sys);
  extpath_ana    = TString("./input/data_2Dsignals/"+filename2D_ana);


  std::cout << " ______ CONFIGURATION ______ " << std::endl;
  std::cout << " centrality   =   " << sOptCent.Data() << std::endl;
  std::cout << " pt-cut       =   " << sOptPt.Data() << std::endl;
  std::cout << " prefilter    =   " << sOptPref.Data() << std::endl;
  std::cout << " efficiency   =   " << sOptEff.Data() << std::endl;
  std::cout << " plotAverage  =   " << (plotAverage?"YES":"NO") << std::endl;
  std::cout << " plotWeightAv =   " << (plotWeightAv?"YES":"NO") << std::endl;
  std::cout << " writeFile    =   " << (writeFile?"YES":"NO") << std::endl;
  std::cout << std::endl;


  LmHandler* han_systematic = new LmHandler(binsPtee_forMee_sys,binsMee_forPtee_sys,plotMeeMin,plotMeeMax_sys,plotPteeMin,plotPteeMax_sys);
  han_systematic->SetName("han_systematic");
  LmHandler* han_analysis = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  han_analysis->SetName("han_analysis");


  if (kDoReadFromRootFile){
    // check if pre-processed files exist
    if (   (gSystem->Exec( Form("ls %s > /dev/null",extpath_sys.Data()) )==0) // file is available if Exec()==0
        && (gSystem->Exec( Form("ls %s > /dev/null",extpath_ana.Data()) )==0) )
    {
      std::cout << "InitFromRootfile()" << std::endl;
      han_systematic->InitFromRootfile(extpath_sys.Data());
      han_analysis->InitFromRootfile(extpath_ana.Data());
    }
  }
  else {
    std::cout << "Read input files" << std::endl;
    ProcessInputfiles(han_systematic, han_analysis);
  }
  // LmManager* mgr_low = new LmManager(Form("Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV:./input/data_LMEEoutput/LMEEoutput_903905.root:caklein_LMEEPbPb_out2:kPbPb2015_Pt400_tightTOFreq_semi:TOFreq:./input/paireff/pairefficiency_semi_pt400_16x.root:NGenPairs_pt400_8000:NRecPairs_hEff_Ele_TOFreq_pt400_8000"));
  // mgr_low->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
  // LmSignal* refSig = ProcessOneInput(mgr_low);



  std::cout << "Postprocess input handlers" << std::endl;
  // postprocess analysis binning
  han_analysis->Process(LmHandler::kCompare); // make projections of all spectra
  han_analysis->SetPlotRangeRatio(0.7, 2.5);
  han_analysis->SetDoRatio(kDoRatio, 0.3, kFALSE);
  han_analysis->SetFileType("png");
  // han_analysis->SetCanvasWidth(1200);
  // han_analysis->SetCanvasHeight(1200);

  han_systematic->Process(LmHandler::kCompare); // make projections of all spectra
  han_systematic->SetCompareSignalsToAverage();

  han_systematic->SetBinningMee(0,&mee_bin_systematic_coarse);
  han_systematic->SetBinningPtee(0,&ptee_bin_systematic_coarse);
  han_systematic->Process(LmHandler::kCompare); // make projections of all spectra
  han_systematic->SetFileType("png");



  LmSignal* sig5_SysWeightedAv = han_analysis->GetLmSignalI(0); // When using only TOFif with ITSSMAP

  // LmSignal* sig5_SysWeightedAv = han_analysis->GetLmSignalI(12); // When using TOFreq_tuned and TOFif spectra

  // LmSignal* sig5_SysWeightedAv = han_analysis->GetLmSignalI(5); // When only using TOFreq
  // LmSignal* sig5_SysWeightedAv = han_analysis->GetLmSignalI(15); // When only using TOFif

  if (kDoSystematics) {
    // sys weighted average
    han_systematic->Process(LmHandler::kSystematic_Average);
    // han_systematic->Process(LmHandler::kSystematic_WeightedAverage);

    sig5_SysWeightedAv->SetSymmetricRelSystematics(han_systematic->GetRelSystematics());
    sig5_SysWeightedAv->Process(LmSignal::kSystematic);


    TCanvas c1("c1", "c1", 1200, 1200);
    TH2D* sys_unc = dynamic_cast<TH2D*>(han_systematic->GetRelSystematics()->Clone("clone"));
    std::cout << "Systematic: " << sys_unc->GetBinContent(1,1) << std::endl;
    std::cout << "Systematic: " << sys_unc->GetBinContent(2,1) << std::endl;
    std::cout << "Systematic: " << sys_unc->GetBinContent(3,1) << std::endl;
    std::cout << "Systematic: " << sys_unc->GetBinContent(4,1) << std::endl;
    std::cout << "Systematic: " << sys_unc->GetBinContent(5,1) << std::endl;
    c1.SetRightMargin(0.2);
    sys_unc->DrawCopy("colz text");
    c1.SaveAs("SysUnc.png");
  }


    // Print without Cocktail
  han_analysis->SetPlotRangeY(2e-4, 1e1);
  han_systematic->SetPlotRangeY(1e-3, 10);

  for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj){
    han_analysis->PrintCompareSig_Mee(iProj, printLegend, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 2, 20);
    // han_analysis->PrintCompareSoverB_Mee(iProj, printLegend, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 2, 20);
    // han_analysis->PrintCompareSignif_Mee(iProj, printLegend, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 2, 20);
    // han_analysis->PrintCompareRfactor_Mee(iProj, printLegend, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 0.85, 1.2);

    // han_analysis->PrintCompare(LmSignal::kSubSig+LmSignal::kUnlike+LmSignal::kBkg, iProj, LmBaseSignal::kProjOnMee, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), true, true);
    // han_analysis->PrintCompare(LmSignal::kUnlike+LmSignal::kBkg, iProj, LmBaseSignal::kProjOnMee, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), true, true);
    // han_analysis->PrintCorrelation(LmSignal::kSignif, LmSignal::kSoverB, iProj, LmBaseSignal::kProjOnMee, Form("xbin%d_ybin%d"), optional Bool_t printLegend, optional Bool_t separatePlots, optional TCanvas *can)

    // han_systematic->PrintCompareSig_Mee(iProj, printLegend, Form("+_sys_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 2, 20);
  }
  for(UInt_t iProj = 0; iProj < binsMee_forPtee.size(); ++iProj){
    // han_analysis->PrintCompareSig_Ptee(iProj, printLegend, Form("+_ana_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 2, 20);
  }
  TFile* file = TFile::Open("test.root", "RECREATE");
  han_analysis->SetRootfile(file);
  han_analysis->Write1DHistSingle(LmSignal::kSubSig, LmBaseSignal::kProjOnMee);

  // compare results
  LmHandler* han_signal = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
    // han_signal->SetBinningPtee(0,&ptee_bin_LookingAtPtee_0_140);
    // han_signal->SetBinningPtee(1,&ptee_bin_LookingAtPtee_140_740);
    // han_signal->SetBinningPtee(2,&ptee_bin_LookingAtPtee_740_1100);
    // han_signal->SetBinningPtee(3,&ptee_bin_LookingAtPtee_1100_2900);
    // han_signal->SetBinningPtee(4,&ptee_bin_LookingAtPtee_2900_3300);
    // han_signal->SetBinningPtee(5,&ptee_bin_LookingAtPtee_3300_5000);

  han_signal->SetName("han_signal");
  han_signal->SetPlotRangeRatio(0.1, 2.6);
  han_signal->SetDoRatio(kDoRatio, 0.3);
  han_signal->AttachSignal(*sig5_SysWeightedAv, "data");
  han_signal->Process(LmHandler::kCompare);
  han_signal->SetFileType("png");
  // han_signal->SetCanvasWidth(1200);
  // han_signal->SetCanvasHeight(1200);



  // Add Cocktail
  LmCocktail* cockt00 = 0x0;
  if (kDoCocktail) {
    cockt00 = ProcessCocktail();

    // Add cocktail to old handler
    han_signal->SetCocktail(cockt00); // attach complete cocktail to handler. call cockt00->Process() before!
    han_signal->SetDivideOption("0");
    han_signal->SetDrawStyleCocktail("hist c"); // default is "hist"
    if (kDoCocktailOnly)
    han_signal->Process(LmHandler::kCocktailOnly); // create projections of cocktail spectra in the projection binning of the handler. they are stored in each LmCocktailPart.
    else
    han_signal->Process(LmHandler::kCocktail);

  }


  // Print with included Cocktail
  han_signal->SetPlotRangeY(2e-4, 10); // Normal invariant mass
  han_systematic->SetPlotRangeY(1e-4, 10);
  for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj){
    // cockt00->PrintCocktail_Mee(iProj, Form("cocktail_bin%d.pdf", iProj));
    han_signal->PrintCompareSig_Mee(iProj, printLegend, Form("+_ana_cocktail_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()), 2, 20);
    // han_signal->PrintCompare(LmSignal::kSubSig, iProj, printLegend, "+_ana_cocktail", kTRUE, kTRUE, kFALSE);
    // han_cocktail->PrintCompare(LmSignal::kSubSig, iProj, printLegend, "+_ana_Onlycocktail", kTRUE, kTRUE, kFALSE);
  }

  // Pair pT histograms
  han_signal->ResetPlotRangeY();
  han_signal->SetPlotRangeY(2e-5, 1); // For 0.14-ß.74 and 0.74-1.1
  han_signal->SetPlotRangeY(2e-4, 10); // For 0.14-ß.74 and 0.74-1.1
  // han_signal->SetPlotRangeY(2e-4, 10); // For 0-0.14
  for(UInt_t iProj = 0; iProj < binsMee_forPtee.size(); ++iProj){
     han_signal->PrintCompareSig_Ptee(iProj, printLegend, Form("+_ana_cocktail_%s_%s_%s_%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data()));
  }

  ///////////////////////////////
    // // RFACTOR PT WISE
    // TCanvas c1;
    // // std::vector<TH1D*> vProjX = han_analysis->CollectProjections(LmSignal::kRfactor, 5, LmBaseSignal::kProjOnMee);
    // // std::vector<TH1D*> vProjX = han_analysis->CollectProjections(LmSignal::kRfactor, 5, LmBaseSignal::kProjOnPtee);
    // std::vector<TH1D*> vProjX;
    // vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(0, LmSignal::kProjOnMee)->GetDatahist());
    // vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(1, LmSignal::kProjOnMee)->GetDatahist());
    // vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(2, LmSignal::kProjOnMee)->GetDatahist());
    // // vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(3, LmSignal::kProjOnMee)->GetDatahist());
    // // vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(4, LmSignal::kProjOnMee)->GetDatahist());
    // // vProjX.push_back(han_analysis->GetLmSignalI(0)->GetRfactor(5, LmSignal::kProjOnMee)->GetDatahist());
    // TH1D* h_axis = new TH1D("r factor", "r factor", 1, 0, 3);
    // h_axis->SetAxisRange(0.85, 1.1, "Y");
    // h_axis->SetTitle("R-Factor;m_{ee} [GeV/c^{2}];R-Factor");
    // h_axis->Draw();
    //
    // for (unsigned int i = 0; i < vProjX.size(); ++i){
    //   vProjX.at(i)->SetMarkerStyle(20);
    //   vProjX.at(i)->SetMarkerColor(LmHelper::GetUniformColor(i, vProjX.size()));
    //   vProjX.at(i)->SetLineColor(LmHelper::GetUniformColor(i, vProjX.size()));
    //   vProjX.at(i)->Draw("same p");
    // }
    //
    // TLegend leg(0.5,0.15,0.9,0.4);
    // leg.AddEntry(vProjX.at(0), "0 < p_{T,ee} < 1 GeV/c", "lpe");
    // leg.AddEntry(vProjX.at(1), "1 < p_{T,ee} < 2 GeV/c", "lpe");
    // leg.AddEntry(vProjX.at(2), "2 < p_{T,ee} < 4 GeV/c", "lpe");
    // // leg.AddEntry(vProjX.at(2), "2 < p_{Tee} < 3 GeV/c", "lpe");
    // // leg.AddEntry(vProjX.at(3), "3 < p_{Tee} < 4 GeV/c", "lpe");
    // // leg.AddEntry(vProjX.at(4), "4 < p_{Tee} < 5 GeV/c", "lpe");
    // // leg.AddEntry(vProjX.at(3), "0 < p_{Tee} < 4 GeV/c", "lpe");
    // leg.DrawClone("same");
    //
    //
    // std::cout << vProjX.size() << std::endl;
    // // vProjX.at(3)->Draw("same");
    // c1.SaveAs("r-factor.pdf");
  ///////////////////////////////////////////////



}

int QA(){
  std::cout << "Processing QA()" << std::endl;
  LmQA qa(const_cast<char*>(cconfig[0].Data()));
  qa.SetColorPalette(57);
  qa.PrintCentrality("QAplots/Event_centrality.png");
  qa.PrintEPTPC("QAplots/Event_epTPC.png");
  // qa.PrintEPV0AC("QAplots/epV0AC.png");
  // qa.PrintEPV0ACvsEPTPC("QAplots/epV0AC_epTPC.png");

  // qa.PrintPtPos("QAplots/PtPos.png");
  // qa.PrintPtNeg("QAplots/PtNeg.png");
  // qa.PrintPtAll("QAplots/Tracking_PtAll.png");
  qa.PrintPtCompare("QAplots/Tracking_PtCompare.png");

  // qa.PrintEtaPos("QAplots/EtaPos.png");
  // qa.PrintEtaNeg("QAplots/EtaNeg.png");
  // qa.PrintEtaAll("QAplots/EtaAll.png");
  qa.PrintEtaCompare("QAplots/Tracking_EtaCompare.png");

  // qa.PrintPhiPos("QAplots/PhiPos.png");
  // qa.PrintPhiNeg("QAplots/PhiNeg.png");
  // qa.PrintPhiAll("QAplots/PhiAll.png");
  qa.PrintPhiCompare("QAplots/Tracking_PhiCompare.png");

  // qa.PrintEtaPhiPos("QAplots/Tracking_EtaPhiPos.png");
  // qa.PrintEtaPhiNeg("QAplots/Tracking_EtaPhiNeg.png");
  // qa.PrintEtaPhiAll("QAplots/Tracking_EtaPhiAll.png");
  // qa.PrintEtaPhiAll("QAplots/Tracking_EtaPhiAll.png");

  // qa.PrintITSnClsPos("QAplots/ITSnClsPos.png");
  // qa.PrintITSnClsNeg("QAplots/ITSnClsNeg.png");
  // qa.PrintITSnClsAll("QAplots/ITSnClsAll.png");
  qa.PrintITSnClsCompare("QAplots/ITSnClsCompare.png");

  // qa.PrintTPCnClsPos("QAplots/TPCnClsPos.png");
  // qa.PrintTPCnClsNeg("QAplots/TPCnClsNeg.png");
  // qa.PrintTPCnClsAll("QAplots/TPCnClsAll.png");
  qa.PrintTPCnClsCompare("QAplots/TPCnClsCompare.png");

  // qa.PrintITSChi2Pos("QAplots/ITSChi2Pos.png");
  // qa.PrintITSChi2Neg("QAplots/ITSChi2Neg.png");
  // qa.PrintITSChi2All("QAplots/ITSChi2All.png");
  qa.PrintITSChi2Compare("QAplots/ITSChi2Compare.png");

  // qa.PrintTPCChi2Pos("QAplots/TPCChi2Pos.png");
  // qa.PrintTPCChi2Neg("QAplots/TPCChi2Neg.png");
  // qa.PrintTPCChi2All("QAplots/TPCChi2All.png");
  qa.PrintTPCChi2Compare("QAplots/TPCChi2Compare.png");

  // qa.PrintTPCrowsOverFindablePos("QAplots/TPCCrossedRowsOverFindablePos.png");
  // qa.PrintTPCrowsOverFindableNeg("QAplots/TPCCrossedRowsOverFindableNeg.png");
  // qa.PrintTPCrowsOverFindableAll("QAplots/TPCCrossedRowsOverFindableAll.png");
  qa.PrintTPCrowsOverFindableCompare("QAplots/Tracking_TPCCrossedRowsOverFindableCompare.png");

  // qa.PrintTPCCrossedRowsPos("QAplots/TPCCrossedRowsPos.png");
  // qa.PrintTPCCrossedRowsNeg("QAplots/TPCCrossedRowsNeg.png");
  // qa.PrintTPCCrossedRowsAll("QAplots/TPCCrossedRowsAll.png");
  qa.PrintTPCCrossedRowsCompare("QAplots/Tracking_TPCCrossedRowsCompare.png");

  // qa.PrintZVertexPos("QAplots/ZVertexPos.png");
  // qa.PrintZVertexNeg("QAplots/ZVertexNeg.png");
  // qa.PrintZVertexAll("QAplots/ZVertexAll.png");
  qa.PrintZVertexCompare("QAplots/Tracking_ZVertexCompare.png");

  // qa.PrintXYVertexPos("QAplots/XYVertexPos.png");
  // qa.PrintXYVertexNeg("QAplots/XYVertexNeg.png");
  // qa.PrintXYVertexAll("QAplots/XYVertexAll.png");
  qa.PrintXYVertexCompare("QAplots/Tracking_XYVertexCompare.png");

  // qa.PrintPvsPInnerWallTPC("QAplots/PrintPvsPInnerWallTPC.png");

  // ############# QA ####################
  // qa.PrintITSSigmaElevsP("QAplots/ITSSigmaElevsP.png");
  // qa.PrintITSSigmaPionvsP("QAplots/ITSSigmaPionvsP.png");
  // qa.PrintITSSigmaKaonvsP("QAplots/ITSSigmaKaonvsP.png");

  qa.PrintTPCSigmaElevsP("QAplots/TPCSigmaElevsP.png");
  // qa.PrintTPCSigmaPionvsP("QAplots/TPCSigmaPionvsP.png");
  // qa.PrintTPCSigmaKaonvsP("QAplots/TPCSigmaKaonvsP.png");

  // qa.PrintTOFSigmaElevsP("QAplots/TOFSigmaElevsP.png");

  qa.PrintTPCSigmaElevsEta("QAplots/TPCSigmaElevsEta.png");
  // qa.PrintPIDTPCdEdxvsP("QAplots/PID_TPCdEdxvsP.png");
  // qa.PrintPID("QAplots");

  // qa.PrintPhiEtaProjection("QAplots/Phi_ASide.png", "phi",  0.0, 0.8);
  // qa.PrintPhiEtaProjection("QAplots/Phi_CSide.png", "phi", -0.8, -0.00001);
  //
  // qa.PrintPhiPtProjection("QAplots/Phi_Pt0_1.png", "phi",  0.0, 1.0);
  // qa.PrintPhiPtProjection("QAplots/Phi_Pt1_2.png", "phi",  1.0, 2.0);
  // qa.PrintPhiPtProjection("QAplots/Phi_Pt2_3.png", "phi",  2.0, 3.0);

  return 0;
}
