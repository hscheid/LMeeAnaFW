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

int main(int argc, char const* argv[])
{
  LmHelper lmHelper; // for styles etc.
  lmHelper.SetDebugLvl(debug);

  LmBaseSignal::SetInputLabelZ("DCA_{ee}", "#sigma", "DCAee");

  LmManager* mgr = new LmManager(const_cast<char*>(configString[0].Data()));
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

std::cout << "Bins" << '\n';
std::cout << "mee: "<< vMeeBinsDef.data() << '\n';
std::cout << "ptee: "<< vPteeBinsDef.data() << '\n';
  mgr->SetRebinning2D(vMeeBinsDef.size()-1, vMeeBinsDef.data(), vPteeBinsDef.size()-1, vPteeBinsDef.data()); // Check which binning to use...
  mgr->SetEtaRange(-0.8, 0.8);
  mgr->SetPtRange(kSetMinPtLabel, kSetMaxPtLabel);
  mgr->Process();

  // create a background object
  LmBackground* bkg = new LmBackground(*(mgr));
  bkg->SetUseRfactor(kDoRfactor);
  bkg->SetRfactorUnityRange(0.5);
  bkg->Process(LmBackground::kHybrid);

  LmSignal* sig = new LmSignal(*(mgr), *(bkg));
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
  sig->PrintUnlike();

  std::vector<double> binsPtee_forMee = {0.,8};
  std::vector<double> binsMee_forPtee = {0.0,0.14,0.7,1.1,3.1,5.};
  double plotMeeMin = 0.0;
  double plotPteeMin= 0.0;
  double plotMeeMax = 5.;
  double plotPteeMax= 8.;

  LmHandler* hanCompare = new LmHandler(binsPtee_forMee, binsMee_forPtee, plotMeeMin, plotMeeMax, plotPteeMin, plotPteeMax);

  hanCompare->AttachSignal(*(sig));
  hanCompare->Process(LmHandler::kStd);

  for (int i = 0; i < binsPtee_forMee.size(); i++) {
    /* code */
    hanCompare->PrintCompareSoverB_Mee(i,Form("soverb_mee_%d.pdf",i));
    hanCompare->PrintCompareSignif_Mee(i,Form("signif_mee_%d.pdf",i));
  }
  for (int i = 0; i < binsMee_forPtee.size(); i++) {
    hanCompare->PrintCompareSoverB_Ptee(i,Form("soverb_ptee_%d.pdf",i));
    hanCompare->PrintCompareSignif_Ptee(i,Form("signif_ptee_%d.pdf",i));
  }

  return 0;
}
