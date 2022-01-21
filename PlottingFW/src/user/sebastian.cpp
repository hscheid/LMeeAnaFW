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
#include "TList.h"
#include "TStyle.h"
#include "TBenchmark.h"
#include "TLegend.h"

#include "TH1.h"
#include "TH2.h"
#include "TPad.h"
#include "TF1.h"
#include "TLine.h"
#include "TPaveText.h"
#include "TVirtualFitter.h"
#include "TGraph.h"
#include "TMinuit.h"
#include "TColor.h"

// project includes
// core
#include "../core/LmManager.h"
#include "../core/LmFileManager.h"
#include "../core/LmBaseSignal.h"
#include "../core/LmSignal.h"
#include "../core/LmHandler.h"
#include "../core/LmHelper.h"
#include "../core/LmQA.h"
#include "../core/LmMultiQA.h"
#include "../core/LmFitter.h"
#include "../core/LmBackground.h"
// user
#include "sebastian.h"

// Start of analysis

// how many configs are we running on?
int n_config = 10;

int main(int argc, char const* argv[])
{
  LmHelper lmHelper; // for styles etc.
  lmHelper.SetDebugLvl(debug);

  LmBaseSignal::SetInputLabelZ("DCA_{ee}", "#sigma", "DCAee");

  std::vector<LmManager*> vecMgr;
  for (int iConfig = 0; iConfig < n_config; ++iConfig) {
    LmManager* mgr = new LmManager(const_cast<char*>(configString[2 + iConfig].Data()));
    // set all kinds of configuration for the manager
    mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
    mgr->SetProjOption(projoption);
    mgr->SetEnableEffiCorr(kFALSE);

    //mgr00->SetEnableRebinning(kFALSE); // use this to disable or just comment out the setter above...
    // configure 3D exclusion cut

    // process the manager
    // if (kDoEffiCorrectionFirst) {
    //   mgr->SetDoEffiCorr();
    // }

    mgr->SetRebinning2D(vMeeBinsQM.size() - 1, vMeeBinsQM.data(), vPteeBinsQM.size() - 1, vPteeBinsQM.data()); // Check which binning to use...
    mgr->SetEtaRange(-0.8, 0.8);
    mgr->SetPtRange(kSetMinPtLabel, kSetMaxPtLabel);
    mgr->Process();
    vecMgr.push_back(mgr);
  }

  // create a background objects
  std::vector<LmBackground*> vecBkg;
  for (auto mgr : vecMgr) {
    /* code */
    LmBackground* bkg = new LmBackground(*(mgr));
    bkg->SetUseRfactor(kDoRfactor);
    bkg->SetRfactorUnityRange(0.5);
    bkg->Process(LmBackground::kHybrid);
    vecBkg.push_back(bkg);
  }
  std::vector<LmSignal*> vecSig;
  // need an index since we need to loop over the mgr and the bkg vectors...
  for (int iS = 0; iS < vecMgr.size(); ++iS) {
    TString signame = Form("Var %d", iS);
    if (iS==0) signame = "Default";
    LmSignal* sig = new LmSignal(*(vecMgr.at(iS)), *(vecBkg.at(iS)), signame.Data());
    //sig->SetDoSubtraction(kFALSE);
    sig->SetDoSignifRaw(kDoSignifRaw);
    sig->SetDoNormBinwidth(kDoNormBinwidth);
    sig->SetDoNormNevents(kDoNormNevents);
    // sig->SetCrossSection(kCrossSection); // for pp
    // sig->SetDoNormCrossSection(kDoNormCrossSection); // plot as cross section, for pp
    // sig->SetTrgEff(kTriggerEfficiency);
    // sig->SetDoNormTrgEff(kDoNormTrgEff);
    // sig->SetDoNormRecEff(kDoNormRecEff);
    // sig->SetVtxRecEff(kVtxRecEff);
    // sig->SetDoNormVtxRecEff(kDoNormVtxRecEff);
    // sig->SetVtxRecEffee(kVtxRecEffee);
    // sig->SetDoNormVtxRecEffee(kDoNormVtxRecEffee);
    sig->Process(LmSignal::kStd);
    vecSig.push_back(sig);
  }

  std::vector<double> binsPtee_forMee = {0., 8};
  std::vector<double> binsMee_forPtee = {0.0, 0.14, 0.7, 1.04, 3.1, 5.};
  double plotMeeMin = 0.0;
  double plotPteeMin = 0.0;
  double plotMeeMax = 5.;
  double plotPteeMax = 8.;

  LmHandler* hanCompare = new LmHandler(binsPtee_forMee, binsMee_forPtee, plotMeeMin, plotMeeMax, plotPteeMin, plotPteeMax);

  for (auto it : vecSig) {
    hanCompare->AttachSignal(*(it));
  }
  hanCompare->Process(LmHandler::kCompare);

  for (int i = 0; i < binsPtee_forMee.size(); i++) {
    /* code */
    hanCompare->PrintCompareSig_Mee(i, kTRUE, Form("../plots/sig_mee_%d.pdf", i));
    hanCompare->PrintCompareSoverB_Mee(i, kTRUE, Form("../plots/soverb_mee_%d.pdf", i));
    hanCompare->PrintCompareSignif_Mee(i, kTRUE, Form("../plots/signif_mee_%d.pdf", i));
  }
  for (int i = 0; i < binsMee_forPtee.size(); i++) {
    hanCompare->PrintCompareSoverB_Ptee(i, kTRUE, Form("../plots/soverb_ptee_%d.pdf", i));
    hanCompare->PrintCompareSignif_Ptee(i, kTRUE, Form("../plots/signif_ptee_%d.pdf", i));
  }

  return 0;
}
