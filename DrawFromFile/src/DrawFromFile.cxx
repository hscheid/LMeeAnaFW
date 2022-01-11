#include <vector>
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TCanvas.h"
#include "TString.h"
#include "TObjString.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TObjArray.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TPaveText.h"
#include "TMath.h"

#include <iostream>

#include "../../PlottingFW/src/core/LmHelper.h"
#include "../../PlottingFW/src/core/LmRebinner.h"

Bool_t debug = kFALSE;
// feel free to add debug statements

//_______________________________________________________________________________________________
int         main(int argc, char* argv[]);
int         DrawFromFile(Int_t conf=100);
TList*      GetList(TFile* infile, TString listname=""); // could now be taken from LmHelper.
TObjArray*  SelectHistos(TList* histlist, TString patSelect="", TString patReject="");
Bool_t      SetupLimits(int ix, int iy, int iz, std::vector<Double_t> vx, std::vector<Double_t> vy, std::vector<Double_t> vz, Double_t* limits);
TObjArray*  MakeProjection(TObjArray* arrIn, Double_t *limits, TString opt, TString filetitle="");
void        DivideHists(TObjArray* arrIn, TH1* hDenom);
TCanvas*    DrawHists(TObjArray* arrIn, TString opt, TString label);
void        MakeSummaryPlotSingleEff(TObjArray** oaProjForMultiPadPlot, TString outdir, TObjArray** oaLabelsForMultiPadPlot = 0x0);
void        MakeSummaryPlotPairEff  (TObjArray** oaProjForMultiPadPlot, TString outdir, TObjArray** oaLabelsForMultiPadPlot = 0x0);
void        SetArrayProperties(TObjArray* arrIn, TString opt="1");
void        SetHistProperties(TH1D &h, Int_t ith, Int_t NHists);
void        SetError(TH1D &h);

//_______________________________________________________________________________________________

Int_t iconf; // global makes it easier to handle different wishes...
const Int_t confMaxPat= 49;
const Int_t confMaxCar= 99;
const Int_t nmax=20;
TString filename[nmax];
TString filetitle[nmax];
TString listname[nmax]={"","","","","","","","","",""};
TString collsyst="";
TString stype;
TString patSelGen, patSelRec, patReject="", patRemove="";
Int_t   nfiles; // do not initialize.
Double_t kSmallDelta=1e-15;

// pair eff
std::vector<Double_t> vProjBins_mee;
std::vector<Double_t> vProjBins_ptee;
std::vector<Double_t> vEmpty;
// single eff
std::vector<Double_t> vProjBins_p;
std::vector<Double_t> vProjBins_eta;
std::vector<Double_t> vProjBins_phi;


//_______________________________________________________________________________________________
int main(int argc, char* argv[])
{
  if (argc<2) return DrawFromFile();

  TString sArg="";
  int errCode=0;
  for (int iarg=1; iarg<argc; ++iarg) {
    Printf("argv[%i] = '%s'", iarg, argv[iarg]);
    sArg = argv[iarg];

    // crashes...
//    if (sArg.Contains("-")) {
//      int first = sArg.Copy().Remove(sArg.First('-'),sArg.Length()).Atoi();
//      int last  = sArg.Copy().Remove(0,sArg.First('-')+1).Atoi();
//      Printf(" using conf from %i to %i", first, last);
//      for (int i=first; i<=last; i++) {
//        errCode = DrawFromFile(i);
//        if (errCode>0) return errCode;
//      }
//    }

    errCode = DrawFromFile(sArg.Atoi());
    if (errCode>0) return errCode;
  }

  return errCode;
}

//_______________________________________________________________________________________________
void Init()
{
  LmHelper lmHelper;

  if      (iconf<=confMaxPat) { // Patrick
    LmHelper::SetCanvasWidth(696); // 580x600 ok to get vertical pdf when importing to ppt.
    LmHelper::SetCanvasHeight(720);
    //can = new TCanvas("can","",800,825); // old defaults

    // projection bins mee
    vProjBins_mee.push_back(0.0);
    vProjBins_mee.push_back(0.14);
    vProjBins_mee.push_back(1.1);
    vProjBins_mee.push_back(2.9);
    vProjBins_mee.push_back(3.3);
    vProjBins_mee.push_back(4.0);
    vProjBins_mee.push_back(5.0);
    // projection bins ptee
//    vProjBins_ptee.push_back(0.0);
//    vProjBins_ptee.push_back(1.0);
//    vProjBins_ptee.push_back(2.0);
//    vProjBins_ptee.push_back(6.0);
    Double_t smallPtRange =  0.1;
//    vProjBins_ptee.push_back(0.0);
//    vProjBins_ptee.push_back(0.0 + smallPtRange - kSmallDelta);
    vProjBins_ptee.push_back(1.0 - smallPtRange);
    vProjBins_ptee.push_back(1.0 + smallPtRange - kSmallDelta);
    vProjBins_ptee.push_back(2.0 - smallPtRange);
    vProjBins_ptee.push_back(2.0 + smallPtRange - kSmallDelta);
    vProjBins_ptee.push_back(4.0 - smallPtRange);
    vProjBins_ptee.push_back(4.0 + smallPtRange - kSmallDelta);
    vProjBins_ptee.push_back(6.0 - smallPtRange);
    vProjBins_ptee.push_back(6.0 + smallPtRange - kSmallDelta);
  }

  else if (iconf<=confMaxCar) { // Carsten
    LmHelper::SetCanvasWidth(1600);
    LmHelper::SetCanvasHeight(1600);

    // projection bins mee
    vProjBins_mee.push_back(0.0);
    vProjBins_mee.push_back(0.1);
    vProjBins_mee.push_back(0.2);
    vProjBins_mee.push_back(0.3);
    vProjBins_mee.push_back(0.4);
    vProjBins_mee.push_back(0.5);
    vProjBins_mee.push_back(0.6);
    vProjBins_mee.push_back(0.8);
    vProjBins_mee.push_back(1.0);
    vProjBins_mee.push_back(1.5);
    vProjBins_mee.push_back(2.7);
    vProjBins_mee.push_back(3.3);
    // projection bins ptee
    vProjBins_ptee.push_back(0.0);
    vProjBins_ptee.push_back(1.0);
    vProjBins_ptee.push_back(2.0);
    vProjBins_ptee.push_back(3.0);
    vProjBins_ptee.push_back(4.0);
    vProjBins_ptee.push_back(8.0);
  }
  else {
    // Style: Plotting framework defaults
    // Binning: just a simple example
    // projection bins mee
    vProjBins_mee.push_back(0.0);
    vProjBins_mee.push_back(1.1);
    vProjBins_mee.push_back(3.3);
    // projection bins ptee
    vProjBins_ptee.push_back(0.0);
    vProjBins_ptee.push_back(8.0);
  }

  // projection bins empty
  vEmpty.push_back(0);

  // track p
  if (iconf==4 || iconf==6)  vProjBins_p.push_back(0.2);
  vProjBins_p.push_back(0.0);
  vProjBins_p.push_back(0.2);
  vProjBins_p.push_back(0.4);
  vProjBins_p.push_back(1.0);
  // vProjBins_p.push_back(4);
  vProjBins_p.push_back(8.0);

  // track eta
  vProjBins_eta.push_back(-0.8);
  // vProjBins_eta.push_back( 0.);
  vProjBins_eta.push_back( 0.8);

  // track phi
  vProjBins_phi.push_back(0.0);
  // vProjBins_phi.push_back(6.28);
  vProjBins_phi.push_back(TMath::TwoPi());

  TString inputOptSingle   = "measurable";
  TString inputOptPairOp50 = "measurable"; // only for outputs with opening angle cut!

  switch (iconf) {
      //
      // Patrick  0 - 49 (<=confMaxPat)
      // Carsten 50 - 99 (<=confMaxCar)
      // Jerome 100 - 150
      //

      //
      // single efficiency - all (for syst)
      // these work for inputOptSingle = "generated", "measurable" and "measurable+ITScuts"
      //
      /*
       root -b -q 'DrawFromFile.cxx (4)'
       root -b -q 'DrawFromFile.cxx (5)'
       root -b -q 'DrawFromFile.cxx (6)'
       root -b -q 'DrawFromFile.cxx (7)'
       */
    case 4:
      filename[0]="../SingleEff/output/"+inputOptSingle+"/singleEff_raw-cent-pt200.root";
      listname[0]="Sum";
      filetitle[0]="LHC14a1a";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV, 0-10%";
      stype     ="SingleEff-cent-pt200-"+inputOptSingle+"-syst";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;
    case 5:
      filename[0]="../SingleEff/output/"+inputOptSingle+"/singleEff_raw-cent-pt400.root";
      listname[0]="Sum";
      filetitle[0]="LHC14a1a";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV, 0-10%";
      stype     ="SingleEff-cent-pt400-"+inputOptSingle+"-syst";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;
    case 6:
      filename[0]="../SingleEff/output/"+inputOptSingle+"/singleEff_raw-semi-pt200.root";
      listname[0]="Sum";
      filetitle[0]="LHC14a1b";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV, 10-50%";
      stype     ="SingleEff-semi-pt200-"+inputOptSingle+"-syst";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;
    case 7:
      filename[0]="../SingleEff/output/"+inputOptSingle+"/singleEff_raw-semi-pt400.root";
      listname[0]="Sum";
      filetitle[0]="LHC14a1b";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV, 10-50%";
      stype     ="SingleEff-semi-pt400-"+inputOptSingle+"-syst";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

//    case 7:
//      filename[0]="./SingleEff/singleEff_raw-MC002-onlysum.root";
//      filetitle[0]="LHC12a17h_fix";
//      stype     ="SingleEff-MC002";
//      patSelGen ="hGen_sum";
//      patSelRec ="Sum_"; patReject="";
//      patRemove ="Sum_";
//      break;
    case 8:
      filename[0]="../SingleEff/singleEff_raw-MC006-onlysum.root";
      filetitle[0]="LHC14a1b";
      stype     ="SingleEff-MC006";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;
    case 9:
      filename[0]="../SingleEff/singleEff_raw-MC002-onlysum.root";
      filename[1]="../SingleEff/singleEff_raw-MC006-onlysum.root";
      filetitle[0]="LHC12a17h_fix";
      filetitle[1]="LHC14a1b";
      stype     ="SingleEff-MC002+006";
      patSelGen ="hGen_sum";
      //patSelRec ="Sum_ITSTPCTOFif"; patReject="";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

      //
      // single efficiency - cut 16
      // these work for inputOptSingle = "generated", "measurable" and "measurable+ITScuts"
      //
    case 14:
      filename[0]="../SingleEff/output/"+inputOptSingle+"/singleEff_raw-cent-pt200.root";
      listname[0]="Sum";
      filetitle[0]="LHC14a1a";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV, 0-10%";
      stype     ="SingleEff-cent-pt200-"+inputOptSingle+"-cut16";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_cut16"; patReject="";
      patRemove ="Sum_";
      break;
    case 15:
      filename[0]="../SingleEff/output/"+inputOptSingle+"/singleEff_raw-cent-pt400.root";
      listname[0]="Sum";
      filetitle[0]="LHC14a1a";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV, 0-10%";
      stype     ="SingleEff-cent-pt400-"+inputOptSingle+"-cut16";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_cut16"; patReject="";
      patRemove ="Sum_";
      break;
    case 16:
      filename[0]="../SingleEff/output/"+inputOptSingle+"/singleEff_raw-semi-pt200.root";
      listname[0]="Sum";
      filetitle[0]="LHC14a1b";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV, 10-50%";
      stype     ="SingleEff-semi-pt200-"+inputOptSingle+"-cut16";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_cut16"; patReject="";
      patRemove ="Sum_";
      break;
    case 17:
      filename[0]="../SingleEff/output/"+inputOptSingle+"/singleEff_raw-semi-pt400.root";
      listname[0]="Sum";
      filetitle[0]="LHC14a1b";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV, 10-50%";
      stype     ="SingleEff-semi-pt400-"+inputOptSingle+"-cut16";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_cut16"; patReject="";
      patRemove ="Sum_";
      break;

      //
      // random rejection single track - cut 16
      //
    case 44:
      filename[0]="../RandomRejection/output/randrejEff_raw-cut16-cent-PrefPhiV_pt200.root";
      filetitle[0]="LHC11h";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV, 0-10%";
      stype     ="RandRej-cent-pt200-PrefPhiV-cut16";
      patSelGen ="all_";
      patSelRec ="rej_"; patReject="";
      patRemove ="rej_";
      break;
    case 45:
      filename[0]="../RandomRejection/output/randrejEff_raw-cut16-cent-PrefPhiV_pt400.root";
      filetitle[0]="LHC11h";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV, 0-10%";
      stype     ="RandRej-cent-pt400-PrefPhiV-cut16";
      patSelGen ="all_";
      patSelRec ="rej_"; patReject="";
      patRemove ="rej_";
      break;
    case 46:
      filename[0]="../RandomRejection/output/randrejEff_raw-cut16-semi-PrefPhiV_pt200.root";
      filetitle[0]="LHC11h";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV, 10-50%";
      stype     ="RandRej-semi-pt200-PrefPhiV-cut16";
      patSelGen ="all_";
      patSelRec ="rej_"; patReject="";
      patRemove ="rej_";
      break;
    case 47:
      filename[0]="../RandomRejection/output/randrejEff_raw-cut16-semi-PrefPhiV_pt400.root";
      filetitle[0]="LHC11h";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV, 10-50%";
      stype     ="RandRej-semi-pt400-PrefPhiV-cut16";
      patSelGen ="all_";
      patSelRec ="rej_"; patReject="";
      patRemove ="rej_";
      break;

      //
      // pair efficiency
      //
      // old effi
    case 20:
      //filename[0]="../PairEffCalc/output/pairEff_raw-17h-std.root";
      filename[0]="../PairEffCalc/output/pairEff_raw-1050-std+RandRej_0to3.root";
      filename[1]="../PairEffCalc/output/pairEff_raw-1050-MC006.root";
      filetitle[0]="LHC12a17h_fix";
      filetitle[1]="LHC14a1b";
      collsyst  ="Pb#minusPb, 2.76 TeV, 10-50%, 0.4 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-semi-comp";
      patSelGen ="hNGen";
//      patSelRec ="Npair";
      patSelRec ="ITSTPCTOFif_trkSPDfirst_1";
      patReject ="_Pref";
      patRemove ="Npair_hEff_";
      break;

      //
      // systematics with and without prefilter
      // all with opening angle cut!
      // these work for inputOptPairOp50 = "measurable" and "measurable+ITScuts"
      // "generated" EffGen was created with an older version of our pair generator, where histograms were called differently.
      //
    case 21:
      filename[0]="../PairEffCalc/output/"+inputOptPairOp50+"/pairEff_raw-0010-pt200.root";
      filetitle[0]="LHC14a1a";
      collsyst  ="Pb#minusPb, 2.76 TeV, 0-10%, 0.2 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-cent-pt200-opAngle50-"+inputOptPairOp50+"-pref";
      patSelGen ="NGenPairs_pt200_3500_opAngle50";
      patSelRec ="PairsCombined_";
      patReject ="NGen";
      patRemove ="NRecPairsCombined_hEff_Ele_";
      break;
    case 22:
      filename[0]="../PairEffCalc/output/"+inputOptPairOp50+"/pairEff_raw-0010-pt200.root";
      filetitle[0]="LHC14a1a";
      collsyst  ="Pb#minusPb, 2.76 TeV, 0-10%, 0.2 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-cent-pt200-opAngle50-"+inputOptPairOp50+"-nopref";
      patSelGen ="NGenPairs_pt200_3500_opAngle50";
      patSelRec ="Pairs_";
      patReject ="NGen";
      patRemove ="NRecPairs_hEff_Ele_";
      break;
    case 23:
      filename[0]="../PairEffCalc/output/"+inputOptPairOp50+"/pairEff_raw-0010-pt400.root";
      filetitle[0]="LHC14a1a";
      collsyst  ="Pb#minusPb, 2.76 TeV, 0-10%, 0.4 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-cent-pt400-opAngle50-"+inputOptPairOp50+"-pref";
      patSelGen ="NGenPairs_pt400_3500_opAngle50";
      patSelRec ="PairsCombined_";
      patReject ="NGen";
      patRemove ="NRecPairsCombined_hEff_Ele_";
      break;
    case 24:
      filename[0]="../PairEffCalc/output/"+inputOptPairOp50+"/pairEff_raw-0010-pt400.root";
      filetitle[0]="LHC14a1a";
      collsyst  ="Pb#minusPb, 2.76 TeV, 0-10%, 0.4 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-cent-pt400-opAngle50-"+inputOptPairOp50+"-nopref";
      patSelGen ="NGenPairs_pt400_3500_opAngle50";
      patSelRec ="Pairs_";
      patReject ="NGen";
      patRemove ="NRecPairs_hEff_Ele_";
      break;

    case 25:
      filename[0]="../PairEffCalc/output/"+inputOptPairOp50+"/pairEff_raw-1050-pt200.root";
      filetitle[0]="LHC14a1b";
      collsyst  ="Pb#minusPb, 2.76 TeV, 10-50%, 0.2 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-semi-pt200-opAngle50-"+inputOptPairOp50+"-pref";
      patSelGen ="NGenPairs_pt200_3500_opAngle50";
      patSelRec ="PairsCombined_";
      patReject ="NGen";
      patRemove ="NRecPairsCombined_hEff_Ele_";
      break;
    case 26:
      filename[0]="../PairEffCalc/output/"+inputOptPairOp50+"/pairEff_raw-1050-pt200.root";
      filetitle[0]="LHC14a1b";
      collsyst  ="Pb#minusPb, 2.76 TeV, 10-50%, 0.2 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-semi-pt200-opAngle50-"+inputOptPairOp50+"-nopref";
      patSelGen ="NGenPairs_pt200_3500_opAngle50";
      patSelRec ="Pairs_";
      patReject ="NGen";
      patRemove ="NRecPairs_hEff_Ele_";
      break;
    case 27:
      filename[0]="../PairEffCalc/output/"+inputOptPairOp50+"/pairEff_raw-1050-pt400.root";
      filetitle[0]="LHC14a1b";
      collsyst  ="Pb#minusPb, 2.76 TeV, 10-50%, 0.4 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-semi-pt400-opAngle50-"+inputOptPairOp50+"-pref";
      patSelGen ="NGenPairs_pt400_3500_opAngle50";
      patSelRec ="PairsCombined_";
      patReject ="NGen";
      patRemove ="NRecPairsCombined_hEff_Ele_";
      break;
    case 28:
      filename[0]="../PairEffCalc/output/"+inputOptPairOp50+"/pairEff_raw-1050-pt400.root";
      filetitle[0]="LHC14a1b";
      collsyst  ="Pb#minusPb, 2.76 TeV, 10-50%, 0.4 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-semi-pt400-opAngle50-"+inputOptPairOp50+"-nopref";
      patSelGen ="NGenPairs_pt400_3500_opAngle50";
      patSelRec ="Pairs_";
      patReject ="NGen";
      patRemove ="NRecPairs_hEff_Ele_";
      break;

      // Pair efficiencies from pairing within effi task (as cross-check)
      // Due to a hardcoded pt-cut they are only available for pt>200 MeV
    case 30:
      filename[0]="../PlottingFW/input/PbPb/MC_4D/bothTasks-ITShists-cent/LMEEoutput-1full.root";
      listname[0]="reichelt_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances";
      filetitle[0]="LHC14a1a";
      collsyst  ="Pb#minusPb, 2.76 TeV, 0-10%, 0.2 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-cent-pt200-measurable-fullMC-LF-nopref";
      patSelGen ="NgenPairs";
      patSelRec ="NrecoPairs";
      patReject ="-";
      patRemove ="NrecoPairsRec";
      break;
    case 31:
      filename[0]="../PlottingFW/input/PbPb/MC_4D/bothTasks-ITShists-cent/LMEEoutput-1full.root";
      listname[0]="reichelt_ElectronEfficiency/pairEfficiency/reconstructedBinning/heavyflavor";
      filetitle[0]="LHC14a1a";
      collsyst  ="Pb#minusPb, 2.76 TeV, 0-10%, 0.2 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-cent-pt200-measurable-fullMC-HF-nopref";
      patSelGen ="NgenPairs";
      patSelRec ="NrecoPairs";
      patReject ="-";
      patRemove ="NrecoPairsRec";
      break;
      // pair effi not filled in "moreSignals" files for some reason:
      //filename[0]="./PlottingFW/input/PbPb/MC_4D/bothTasks-moreSignals-cent/LMEEoutput-1full.root";
      //...

      //
      // pair efficiency
      // cut16_4D with phiV prefilter
      //
    case 32:
      filename[0]="../PairEffCalc/output/measurable+PrefPhiV/pairEff_raw-0010-pt200.root";
      filetitle[0]="LHC14a1a";
      //collsyst  ="Pb#minusPb, 2.76 TeV, 0-10%, 0.2 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-cent-pt200-PrefPhiV-cut16";
      patSelGen ="NGenPairs_pt200_3500";
      patSelRec ="PairsCombined_";
      patReject ="_opAngle50";
      patRemove ="NRecPairsCombined_hEff_Ele_";
      break;
    case 33:
      filename[0]="../PairEffCalc/output/measurable+PrefPhiV/pairEff_raw-0010-pt400.root";
      filetitle[0]="LHC14a1a";
      //collsyst  ="Pb#minusPb, 2.76 TeV, 0-10%, 0.4 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-cent-pt400-PrefPhiV-cut16";
      patSelGen ="NGenPairs_pt400_3500";
      patSelRec ="PairsCombined_";
      patReject ="_opAngle50";
      patRemove ="NRecPairsCombined_hEff_Ele_";
      break;
    case 34:
      filename[0]="../PairEffCalc/output/measurable+PrefPhiV/pairEff_raw-1050-pt200.root";
      filetitle[0]="LHC14a1b";
      //collsyst  ="Pb#minusPb, 2.76 TeV, 10-50%, 0.2 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-semi-pt200-PrefPhiV-cut16";
      patSelGen ="NGenPairs_pt200_3500";
      patSelRec ="PairsCombined_";
      patReject ="_opAngle50";
      patRemove ="NRecPairsCombined_hEff_Ele_";
      break;
    case 35:
      filename[0]="../PairEffCalc/output/measurable+PrefPhiV/pairEff_raw-1050-pt400.root";
      filetitle[0]="LHC14a1b";
      //collsyst  ="Pb#minusPb, 2.76 TeV, 10-50%, 0.4 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-semi-pt400-PrefPhiV-cut16";
      patSelGen ="NGenPairs_pt400_3500";
      patSelRec ="PairsCombined_";
      patReject ="_opAngle50";
      patRemove ="NRecPairsCombined_hEff_Ele_";
      break;

      // cut16_4D survival probability
    case 36:
      filename[0]="../PairEffCalc/output/measurable+PrefPhiV/pairEff_raw-0010-pt200.root";
      filetitle[0]="LHC14a1a";
      //collsyst  ="Pb#minusPb, 2.76 TeV, 0-10%, 0.2 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-cent-pt200-PrefPhiV-cut16-SurvProb";
      patSelGen ="NGenPairs_pt200_3500";
      patSelRec ="PairsPrefilter_";
      patReject ="_opAngle50";
      patRemove ="NRecPairsPrefilter_hEff_Ele_";
      patRemove+="cut01_SPD1_PID1_"; // because of wrong naming of survival probability histograms in GenCompletePhaseSpace.cpp.
      break;
    case 37:
      filename[0]="../PairEffCalc/output/measurable+PrefPhiV/pairEff_raw-0010-pt400.root";
      filetitle[0]="LHC14a1a";
      //collsyst  ="Pb#minusPb, 2.76 TeV, 0-10%, 0.4 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-cent-pt400-PrefPhiV-cut16-SurvProb";
      patSelGen ="NGenPairs_pt400_3500";
      patSelRec ="PairsPrefilter_";
      patReject ="_opAngle50";
      patRemove ="NRecPairsPrefilter_hEff_Ele_";
      patRemove+="cut01_SPD1_PID1_"; // because of wrong naming of survival probability histograms in GenCompletePhaseSpace.cpp.
      break;
    case 38:
      filename[0]="../PairEffCalc/output/measurable+PrefPhiV/pairEff_raw-1050-pt200.root";
      filetitle[0]="LHC14a1b";
      //collsyst  ="Pb#minusPb, 2.76 TeV, 10-50%, 0.2 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-semi-pt200-PrefPhiV-cut16-SurvProb";
      patSelGen ="NGenPairs_pt200_3500";
      patSelRec ="PairsPrefilter_";
      patReject ="_opAngle50";
      patRemove ="NRecPairsPrefilter_hEff_Ele_";
      patRemove+="cut01_SPD1_PID1_"; // because of wrong naming of survival probability histograms in GenCompletePhaseSpace.cpp.
      break;
    case 39:
      filename[0]="../PairEffCalc/output/measurable+PrefPhiV/pairEff_raw-1050-pt400.root";
      filetitle[0]="LHC14a1b";
      //collsyst  ="Pb#minusPb, 2.76 TeV, 10-50%, 0.4 < #it{p}_{T} < 3.5 GeV/#it{c}";
      stype     ="PairEff-semi-pt400-PrefPhiV-cut16-SurvProb";
      patSelGen ="NGenPairs_pt400_3500";
      patSelRec ="PairsPrefilter_";
      patReject ="_opAngle50";
      patRemove ="NRecPairsPrefilter_hEff_Ele_";
      patRemove+="cut01_SPD1_PID1_"; // because of wrong naming of survival probability histograms in GenCompletePhaseSpace.cpp.
      break;
    // case 44-47 used for random rejection of tracks.


      //
      // Carsten
      //       root -b -q 'DrawFromFile.cxx (52)'
      //
    case 50:
      filename[0]="../SingleEff/output/singleEff_raw-semi-pt400_train104.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1b";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 10-50%";
      stype     ="SingleEff-semi-pt400";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 51:
      filename[0]="../SingleEff/output/singleEff_raw-semi-pt400_train16x.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1b";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 10-50%";
      stype     ="SingleEff-semi-pt400";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;
    case 52:
      filename[0]="../SingleEff/output/singleEff_raw-pt400_c00_c19.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%";
      stype     ="SingleEff-pt400";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;
    case 53:
      filename[0]="../SingleEff/output/singleEff_raw-pt400_v2_reconstructed.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%";
      stype     ="SingleEff-pt400_reconstructed_noESDcuts";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;
    case 54:
      filename[0]="../SingleEff/output/singleEff_raw-pt400_v2_generated.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%";
      stype     ="SingleEff-pt400_generated";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;
    case 55:
      filename[0]="../SingleEff/output/singleEff_raw-pt400_v3_reconstructed.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%";
      stype     ="SingleEff-pt400_reconstructed_TOFif_TOFreq";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 56:
      filename[0]="../SingleEff/output/singleEff_raw-pt400_v4_TOFMismatch_reconstructed.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%";
      stype     ="SingleEff-pt400_reconstructed";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 57:
      filename[0]="../SingleEff/output/singleEff_raw-pt400_MCClosure.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%";
      stype     ="SingleEff-pt400_MCClosure_reconstructed";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 58:
      filename[0]="../SingleEff/output/singleEff_raw-pt400_v5_wITSSMAP.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%";
      stype     ="SingleEff-pt400_reconstructed";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 59:
      filename[0]="../SingleEff/output/singleEff_raw-pt400_MCClosure.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%";
      stype     ="SingleEff-pt400_reconstructed-old-efficiency";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 60:
      filename[0]="../SingleEff_V2/output/eff_raw_eleFinalState.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%";
      stype     ="SingleEff-pt400_reconstructed-new-efficiency-finalState";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 61:
      filename[0]="../SingleEff_V2/output/eff_raw_eleFinalStateFromD.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%, e from D";
      stype     ="SingleEff-pt400_reconstructed-new-efficiency-finalStateFromD";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

      case 62:
      filename[0]="../SingleEff_V2/output/eff_raw_LEGO419_15012018_eleFinalState.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%";
      stype     ="SingleEff-pt400_reconstructed-new-efficiency-finalState";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

      case 63:
      filename[0]="../SingleEff_V2/output/eff_raw_LEGO419_15012018_eleFinalStateFromD.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%, e from D";
      stype     ="SingleEff-pt400_reconstructed-new-efficiency-finalStateFromD";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

      case 64:
      filename[0]="../SingleEff_V2/output/eff_raw_LEGO421_17012018_eleFinalState.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%";
      stype     ="SingleEff-pt400_reconstructed-new-efficiency-finalState";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

      case 65:
      filename[0]="../SingleEff_V2/output/eff_raw_LEGO421_17012018_eleFinalStateFromD.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%, e from D";
      stype     ="SingleEff-pt400_reconstructed-new-efficiency-finalStateFromD";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

      case 66:
      filename[0]="../SingleEff_V2/output/eff_raw_LEGO421_17012018_eleFinalStateFromPion.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%, e from #pi^{0}";
      stype     ="SingleEff-pt400_reconstructed-new-efficiency-finalStateFromPion";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

      case 67:
      filename[0]="../SingleEff_V2/output/eff_raw_LEGO421_17012018_eleFinalState_0SITSCl.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%";
      stype     ="SingleEff-pt400_reconstructed-new-efficiency-finalState_0SITSCl";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

      case 68:
      filename[0]="../SingleEff_V2/output/eff_raw_LEGO421_17012018_eleFinalStateFromD_0SITSCl.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%, e from D";
      stype     ="SingleEff-pt400_reconstructed-new-efficiency-finalStateFromD_0SITSCl";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

      case 69:
      filename[0]="../SingleEff_V2/output/eff_raw_LEGO421_17012018_eleFinalStateFromPion_0SITSCl.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%, e from #pi^{0}";
      stype     ="SingleEff-pt400_reconstructed-new-efficiency-finalStateFromPion_0SITSCl";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

      case 70:
      filename[0]="../SingleEff_V2/output/eff_raw_LEGO421_17012018_eleFinalState_ITSMAP.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%";
      stype     ="SingleEff-pt400_reconstructed-new-efficiency-finalState_ITSMAP";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

      case 71:
      filename[0]="../SingleEff_V2/output/eff_raw_LEGO421_17012018_eleFinalStateFromD_ITSMAP.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%, e from D";
      stype     ="SingleEff-pt400_reconstructed-new-efficiency-finalStateFromD_ITSMAP";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

      case 72:
      filename[0]="../SingleEff_V2/output/eff_raw_LEGO421_17012018_eleFinalStateFromPion_ITSMAP.root";
      listname[0]="Sum";
      filetitle[0]="LHC16g1";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 00-80%, e from #pi^{0}";
      stype     ="SingleEff-pt400_reconstructed-new-efficiency-finalStateFromPion_ITSMAP";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;



    case 75:
      filename[0]="../PairEffCalc/output/pairefficiency_semi_pt400.root";
      filetitle[0]="LHC16g1b";
      // collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 10-50%, 0.4<#it{p}_{T}<8.0 GeV/#it{c}";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 10-50%";
      stype     ="PairEff-semi-pt400";
      patSelGen ="NGenPairs_pt400_8000";
      patSelRec ="Pairs_";
      patReject ="NGen";
      patRemove ="NRecPairs_hEff_Ele_";
      break;

    case 76:
      filename[0]="../PairEffCalc/output/pairefficiency_pt400_v2.root";
      filetitle[0]="LHC16g1";
      // collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 10-50%, 0.4<#it{p}_{T}<8.0 GeV/#it{c}";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 0-80%";
      stype     ="PairEff-pt400";
      patSelGen ="NGenPairs_pt400_8000";

    case 77:
      filename[0]="../PairEffCalc/output/pairefficiency_pt400_v5_wITSSMAP.root";
      filetitle[0]="LHC16g1";
      // collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 10-50%, 0.4<#it{p}_{T}<8.0 GeV/#it{c}";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 0-80%";
      stype     ="PairEff-pt400";
      patSelGen ="NGenPairs_pt400_8000";
      patSelRec ="Pairs_";
      patReject ="NGen";
      patRemove ="NRecPairs_hEff_Ele_";
      break;

    case 78:
      filename[0]="../PairEffCalc/output/pairefficiency_pt400_v5_wITSSMAP.root";
      filetitle[0]="LHC16g1";
      // collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 10-50%, 0.4<#it{p}_{T}<8.0 GeV/#it{c}";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 0-80%";
      stype     ="PairEff-pt400";
      patSelGen ="NGenPairs_pt400_8000";
      patSelRec ="NRecPairs_hEff_Ele_cut3";
      patReject ="NGen";
      patRemove ="NRecPairs_hEff_Ele_";
      break;
    case 79:
      filename[0]="../PairEffCalc/output/pairefficiency_pt400_27012018_c20.root";
      filetitle[0]="LHC16g1";
      // collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 10-50%, 0.4<#it{p}_{T}<8.0 GeV/#it{c}";
      collsyst  ="Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV, 0-80%";
      stype     ="PairEff-pt400";
      patSelGen ="NGenPairs_pt400_8000";
      patSelRec ="NRecPairs_hEff_cut5";
      patReject ="NGen";
      patRemove ="NRecPairs_hEff_";
      break;

      //
      // Jerome
      //       root -b -q 'DrawFromFile.cxx (100)'
      //
    case 100:
      filename[0]="./SingleEff/output/singleEff_raw-pt75_LHC17d1.root";
      listname[0]="Sum";
      filetitle[0]="LHC17d1";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_LHC17d1";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_";
      patReject="";
      patRemove ="Sum_";
      break;

    case 101:
      filename[0]="./SingleEff/output/singleEff_raw-pt75_LHC17h3.root";
      listname[0]="Sum";
      filetitle[0]="LHC17d1";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_LHC17h3";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_";
      patReject="";
      patRemove ="Sum_";
      break;

    case 102:
      filename[0]="./SingleEff/output/singleEff_raw-pt75_LHC17d1_low.root";
      listname[0]="Sum";
      filetitle[0]="LHC17d1";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_LHC17d1_low";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_";
      patReject="";
      patRemove ="Sum_";
      break;

    case 103:
      filename[0]="./SingleEff/output/singleEff_raw-pt75_LHC17d20a1_nom.root";
      listname[0]="Sum";
      filetitle[0]="LHC17d20a1";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, nom Field";
      stype     ="SingleEff-pt75_LHC17d20a1_nom";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_";
      patReject="";
      patRemove ="Sum_";
      break;

    case 104:
      filename[0]="./SingleEff/output/singleEff_raw-pt75_LHC17d1_LEGO443.root";
      listname[0]="Sum";
      filetitle[0]="LHC17d1_LEGO443";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_LHC17d1_LEGO443";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_";
      patReject="";
      patRemove ="Sum_";
      break;

    case 105:
      filename[0]="./SingleEff/output/singleEff_raw-pt75_LHC17h3_LEGO444.root";
      listname[0]="Sum";
      filetitle[0]="LHC17h3";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_LHC17h3_LEGO444";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_";
      patReject="";
      patRemove ="Sum_";
      break;

    case 106:
      filename[0]="../SingleEff/output/singleEff_raw-pt75_test17_noV0.root";
      listname[0]="Sum";
      filetitle[0]="LHC17h3";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_LHC17h3_LEGO444";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_";
      patReject="";
      patRemove ="Sum_";
      break;

    case 107:
      filename[0]="../SingleEff/output/singleEff_raw-pt75_16n17_HfFineMC_noV0.root";
      listname[0]="Sum";
      filetitle[0]="16n17_HF";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_HF";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_";
      patReject="";
      patRemove ="Sum_";
      break;

    case 108:
      filename[0]="../SingleEff/output/singleEff_raw-pt75_16n17_ResoFineMC_noV0.root";
      listname[0]="Sum";
      filetitle[0]="16n17_LF";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LF";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_";
      patReject="";
      patRemove ="Sum_";
      break;

    case 109:
      filename[0]="../SingleEff_V2/output/testv2_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 110:
      filename[0]="../SingleEff_V2/output/testv2_fromD_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_D";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 111:
      filename[0]="../SingleEff_V2/output/testv2_fromPi_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_Pi";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 112:
      filename[0]="../SingleEff_V2/output/AnaResults_16n17_eleFinal_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_eleFinal";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 113:
      filename[0]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromPion_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_eleFinalFromPion";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 114:
      filename[0]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromEta_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_eleFinalFromEta";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 115:
      filename[0]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromEtaPrime_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_eleFinalFromEtaPrime";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 116:
      filename[0]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromOmega_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_eleFinalFromOmega";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 117:
      filename[0]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromRho_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_eleFinalFromRho";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 118:
      filename[0]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromPhi_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_eleFinalFromPhi";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 119:
      filename[0]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromJPsi_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_eleFinalFromJPsi";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 120:
      filename[0]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromSameMotherMeson_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_eleFinalFromSameMotherMeson";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 121:
      filename[0]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromD_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_eleFinalFromD";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 122:
      filename[0]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromB_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_eleFinalFromB";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="";
      patRemove ="Sum_";
      break;

    case 123:
      filename[0]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromPion_raw.root";
      listname[0]="Sum";
      filetitle[0]="Pion";
      filename[1]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromEta_raw.root";
      listname[1]="Sum";
      filetitle[1]="Eta";
      filename[2]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromOmega_raw.root";
      listname[2]="Sum";
      filetitle[2]="Omega";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_eleFinalFromEtaComp";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="SCcut";
      patRemove ="Sum_";
      break;

    case 124:
      filename[0]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromSameMotherMeson_raw.root";
      listname[0]="Sum";
      filetitle[0]="LF";
      filename[1]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromD_raw.root";
      listname[1]="Sum";
      filetitle[1]="Charm";
      filename[2]="../SingleEff_V2/output/AnaResults_16n17_eleFinalFromB_raw.root";
      listname[2]="Sum";
      filetitle[2]="Beauty";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_eleFinalComp";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="SCcut";
      patRemove ="Sum_";
      break;

    case 125:
      filename[0]="../SingleEff_V2/output/AnaResults_16n17_eleFinal_raw.root";
      listname[0]="Sum";
      filetitle[0]="LHC16n17";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="SingleEff-pt75_16n17_LFv2_eleFinal-test";
      patSelGen ="hGen_sum";
      patSelRec ="Sum_"; patReject="ITS_noV0";
      patRemove ="Sum_";
      break;



    case 130:
      filename[0]="./PairEffCalc/output/ppToyMCpairEff_raw_pt75_LHC17d1.root";
      filetitle[0]="LHC17d1";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="PairEff-pt75_LHC17d1";
      patSelGen ="NGenPairs_pt75";
      patSelRec ="Pairs_";
      patReject ="NGen";
      patRemove ="NRecPairs_hEff_Ele_";
      break;

    case 131:
      filename[0]="./PairEffCalc/output/ppToyMCpairEff_raw_pt75_LHC17h3.root";
      filetitle[0]="LHC17h3";
      collsyst  ="pp, #sqrt{#it{s}} = 13 TeV, low Field";
      stype     ="PairEff-pt75_LHC17h3";
      patSelGen ="NGenPairs_pt75";
      patSelRec ="Pairs_";
      patReject ="NGen";
      patRemove ="NRecPairs_hEff_Ele_";
      break;



    default:
      break;

  }
}


//_______________________________________________________________________________________________
int DrawFromFile(Int_t conf)
{
  iconf=conf;
  Init();
  TString outdir = Form("./plots/%s", stype.Data());
  if (outdir.Contains("-SurvProb")) outdir.ReplaceAll("-SurvProb",""); // plot into same dir as pair effi.
  gSystem->Exec( Form("mkdir -p %s", outdir.Data()) );

  TFile* infile[nmax];
  nfiles=0;
  for (int i=0; i<nmax; i++) {
    if (filename[i].Length()>0) {
      infile[i] = new TFile(filename[i], "READ");
      if (!infile[i]) {
        std::cerr << "\33[0;31m ERROR: file '" << filename[i].Data() << "' not found, skip it. \33[0m" << std::endl;
        continue;
      }
      if (debug) { infile[i]->ls(); std::cout << " " << std::endl; }
      nfiles++;
    }
    else {
      break;
    }
  }

  TList* histlist[nmax];
  TObjArray* oaSelectedRec[nmax];
  TObjArray* oaSelectedGen[nmax];

  for (int i=0; i<nfiles; i++) {
    std::cout << " file i = " << i << std::endl;
    histlist[i] = GetList(infile[i], listname[i]);
    if (debug) { histlist[i]->Print(); std::cout << " " << std::endl; }

    oaSelectedRec[i] = SelectHistos(histlist[i], patSelRec, patReject);
    std::cout << "\33[1;32m selected reco histograms : \33[1;33m (make sure no generated histogram is selected!) \33[0m" << std::endl;
    oaSelectedRec[i]->Print(); std::cout << " " << std::endl;
    // ((TH1*)oaSelectedRec[i]->At(0))->DrawCopy("colz");

    oaSelectedGen[i] = SelectHistos(histlist[i], patSelGen);
    std::cout << "\33[1;32m selected gen histogram : (should be just one) \33[0m" << std::endl;
    oaSelectedGen[i]->Print(); std::cout << " " << std::endl;

    if (oaSelectedRec[i]->GetEntries()==0 || oaSelectedGen[i]->GetEntries()==0) {
      std::cerr << "\33[1;31m ERROR: requested histograms not found in file '" << filename[i].Data() << "'. skip all further files. \33[0m" << std::endl;
      nfiles--;
      break; // if this break isn't called, the logic will fail if more files are given.
    }
    if (oaSelectedGen[i]->GetEntries()>1) {
      std::cout << "\33[1;33m WARNING: more than one generated histogram selected! using the first one for all divisions. \33[0m" << std::endl << std::endl;
    }

    // Rebin:
    if (stype.Contains("PairEff") || stype.Contains("SurvProb")) {
      int nrebinx=5;
      for (int j=0; j<oaSelectedRec[i]->GetEntries(); j++) {
        ((TH2D*) oaSelectedRec[i]->At(j))->RebinX(nrebinx);
      }
      for (int j=0; j<oaSelectedGen[i]->GetEntries(); j++) {
        ((TH2D*) oaSelectedGen[i]->At(j))->RebinX(nrebinx);
      }
    }

    // for (int j = 0; j < oaSelectedRec[i]->GetEntries(); ++j){
    //   TCanvas c1("c1","PairEfficiency",1200,800);
    //   TH1F* h1 = (TH1F*)oaSelectedRec[i]->At(j);
    //   h1->SetTitle(";m_{ee} [GeV/c^{2}];p_{T,ee} [GeV/c];Efficiency");
    //   h1->SetAxisRange(0,0.2,"Z");
    //   h1->SetStats(kFALSE);
    //   h1->SetContour(255);
    //   h1->Divide((TH1F*)oaSelectedGen[i]->At(0));
    //   h1->Draw("COLZ");
    //   c1.SaveAs(Form("pair_efficiency%d.png", j));
    // }
  }

  TObjArray* oaProjForMultiPadPlot[3];
  oaProjForMultiPadPlot[0]=0x0;
  oaProjForMultiPadPlot[1]=0x0;
  oaProjForMultiPadPlot[2]=0x0;
  TObjArray* oaLabelsForMultiPadPlot[3];
  oaLabelsForMultiPadPlot[0]=0x0;
  oaLabelsForMultiPadPlot[1]=0x0;
  oaLabelsForMultiPadPlot[2]=0x0;

  std::vector<Double_t> vx, vy, vz;

  if (stype.Contains("PairEff") || stype.Contains("SurvProb")) {
    vx = vProjBins_mee;
    vy = vProjBins_ptee;
    vz = vEmpty;
  }
  if (stype.Contains("SingleEff") || stype.Contains("RandRej")) {
    vx = vProjBins_p;
    vy = vProjBins_eta;
    vz = vProjBins_phi;
  }

  Double_t limits[6] = {0, -1, 0, -1, 0, -1};
  TString sproj="x";

  for (int iproj=0; iproj<3; iproj++)
  {
    if (iproj==0) sproj="x";
    if (iproj==1) sproj="y";
    if (iproj==2) sproj="z";

    int nbins_b=0;
    int nbins_c=0;
    if (sproj.EqualTo("x")) { if (vx.size()<2) break; nbins_b=vy.size(); nbins_c=vz.size(); }
    if (sproj.EqualTo("y")) { if (vy.size()<2) break; nbins_b=vx.size(); nbins_c=vz.size(); }
    if (sproj.EqualTo("z")) { if (vz.size()<2) break; nbins_b=vx.size(); nbins_c=vy.size(); }

    oaProjForMultiPadPlot[iproj] = new TObjArray();
    oaProjForMultiPadPlot[iproj]->SetOwner();
    oaLabelsForMultiPadPlot[iproj] = new TObjArray();
    oaLabelsForMultiPadPlot[iproj]->SetOwner();

    for (int bin_b=0; bin_b<nbins_b; bin_b++)
    {
      for (int bin_c=0; bin_c<nbins_c; bin_c++)
      {
        if (debug) std::cout << "sproj = " << sproj.Data() << "   bin_b = " << bin_b << "   bin_c = " << bin_c << std::endl;

        Bool_t skip=kFALSE;
        if (sproj.EqualTo("x")) skip = !SetupLimits(0   , bin_b, bin_c, vx, vy, vz, limits);
        if (sproj.EqualTo("y")) skip = !SetupLimits(bin_b, 0   , bin_c, vx, vy, vz, limits);
        if (sproj.EqualTo("z")) skip = !SetupLimits(bin_b, bin_c, 0   , vx, vy, vz, limits);
        if (skip) continue;

        TString label;
        if (stype.Contains("PairEff") || stype.Contains("SurvProb")) {
          if (sproj.EqualTo("x")) label = Form("%3.1f < #it{p}_{T,ee} < %3.1f GeV/#it{c}",limits[2],limits[3]);
          if (sproj.EqualTo("y")) label = Form("%3.2f < #it{m}_{ee} < %3.2f GeV/#it{c}^{2}",limits[0],limits[1]);
        }
        if (stype.Contains("SingleEff") || stype.Contains("RandRej")) {
          if (sproj.EqualTo("x")) label = Form("%3.2f < #it{#eta} < %3.2f,  %3.2f < #it{#varphi} < %3.2f"            ,limits[2],limits[3],limits[4],limits[5]);
          if (sproj.EqualTo("y")) label = Form("%3.2f < #it{p}_{T} < %3.2f GeV/#it{c},  %3.2f < #it{#varphi} < %3.2f",limits[0],limits[1],limits[4],limits[5]);
          if (sproj.EqualTo("z")) label = Form("%3.2f < #it{p}_{T} < %3.2f GeV/#it{c},  %3.2f < #it{#eta} < %3.2f"   ,limits[0],limits[1],limits[2],limits[3]);
        }
        if (!collsyst.IsNull()) label.Prepend(Form("%s,  ",collsyst.Data()));

        TObjArray* oaSelectedRec_proj[nmax];
        TObjArray* oaSelectedGen_proj[nmax];
        for (int i=0; i<nfiles; i++) {

          if (debug) std::cout << " make projections for file i = " << i << std::endl;
          oaSelectedRec_proj[i] = MakeProjection(oaSelectedRec[i], limits, Form("%s %s",sproj.Data(),stype.Data()), filetitle[i] );
          oaSelectedGen_proj[i] = MakeProjection(oaSelectedGen[i], limits, Form("%s %s",sproj.Data(),stype.Data()), filetitle[i] );
          DivideHists(oaSelectedRec_proj[i], (TH1*)oaSelectedGen_proj[i]->At(0));
          SetArrayProperties(oaSelectedRec_proj[i], Form("%i",i+1) ); // different line styles

          // add all arrays to the first array
          //
          if (i>0) oaSelectedRec_proj[0]->AddAll( oaSelectedRec_proj[i] );
        }

        // buffer the integrated projection of each dimension, because they shall be drawn into a summary plot.
        //std::cout << " bin_b = " << bin_b << " nbins_b = " << nbins_b << " bin_c = " << bin_c << " nbins_c = " << nbins_c << std::endl;
        if ((stype.Contains("SingleEff") || stype.Contains("RandRej")) &&
            (bin_b==nbins_b-1 || nbins_b==2) && (bin_c==nbins_c-1 || nbins_c==2)) { // last bin. bit complicated due to the 'skip' logic above.
          oaProjForMultiPadPlot[iproj]->AddAll( (TCollection*) oaSelectedRec_proj[0]->Clone() );
        }
        if ((stype.Contains("PairEff") || stype.Contains("SurvProb")) &&
            (bin_b%2==0)) { // every other bin. they start with 0.
          oaProjForMultiPadPlot[iproj]->AddAll( (TCollection*) oaSelectedRec_proj[0]->Clone() ); // AddAll does not copy, so we need Clone().
          oaLabelsForMultiPadPlot[iproj]->Add( new TObjString(label) );
        }

        TCanvas* can = DrawHists(oaSelectedRec_proj[0], Form("%s %s",sproj.Data(),stype.Data()), label);
        if      (iconf<=confMaxPat) can->Print( Form("%s/c%s_p%s_bin%i_%i.pdf",outdir.Data(),stype.Data(),sproj.Data(),bin_b,bin_c) ); // Patrick
        else if (iconf<=confMaxCar) can->Print( Form("%s/c%s_p%s_bin%i_%i.png",outdir.Data(),stype.Data(),sproj.Data(),bin_b,bin_c) ); // Carsten
        else                        can->Print( Form("%s/c%s_p%s_bin%i_%i.pdf",outdir.Data(),stype.Data(),sproj.Data(),bin_b,bin_c) ); // new user -> old defaults

        TCanvas* can2 = DrawHists(oaSelectedRec_proj[0], Form("%s %s Ratio",sproj.Data(),stype.Data()), label+" Ratio");
        if      (iconf<=confMaxPat) can2->Print( Form("%s/c%s_p%s_bin%i_%i_ratio.pdf",outdir.Data(),stype.Data(),sproj.Data(),bin_b,bin_c) ); // Patrick
        else if (iconf<=confMaxCar) can2->Print( Form("%s/c%s_p%s_bin%i_%i_ratio.png",outdir.Data(),stype.Data(),sproj.Data(),bin_b,bin_c) ); // Carsten
        else                        can2->Print( Form("%s/c%s_p%s_bin%i_%i_ratio.pdf",outdir.Data(),stype.Data(),sproj.Data(),bin_b,bin_c) ); // new user -> old defaults
        //
      } // bin_c
    } // bin_b
  } // iproj

  if (stype.Contains("SingleEff") || stype.Contains("RandRej")) MakeSummaryPlotSingleEff(oaProjForMultiPadPlot, outdir, oaLabelsForMultiPadPlot);
  if (stype.Contains("PairEff") || stype.Contains("SurvProb"))  MakeSummaryPlotPairEff(oaProjForMultiPadPlot, outdir, oaLabelsForMultiPadPlot);

  return 0;
}


//_______________________________________________________________________________________________
void MakeSummaryPlotPairEff(TObjArray** oaProjForMultiPadPlot, TString outdir, TObjArray** oaLabelsForMultiPadPlot)
{
  // Set up canvas for summary plot
  // 0.65 is the width of regular plots in the document, 0.49 for a figure with two separate plots (not 2 pads).
  Double_t sizeFac   = 1.*0.49/0.65;
  // with the default margins of 0.14 and 0.06, each large pad has has a relative size of 0.8x0.8 and each small one 0.4x0.4.
  // here we need 2 small pads next to each other plus the margins:
  Double_t canRelWidth  = (2.*0.4+0.14+0.06)*sizeFac;
  Double_t canRelHeight = (2.*0.4+0.10+0.10)*sizeFac;
  TCanvas* cSummary = new TCanvas("cSummary", "cSummary", canRelWidth*gStyle->GetCanvasDefW(), canRelHeight*gStyle->GetCanvasDefH());
  // bottom- and topmargins shall have the same absolute size as in a large figure, so scale them by the relative height of this canvas.
  //LmHelper::CreateManyPads(cSummary,1,1, 0.1/canRelHeight,0.1/canRelHeight, 0.14/canRelWidth,0.06/canRelWidth);
  LmHelper::CreateManyPads(cSummary,1,1, 0.1/canRelHeight,0.06/canRelHeight, 0.12/canRelWidth,0.04/canRelWidth);
  Double_t titleSize = gStyle->GetTitleSize()/canRelHeight;
  Double_t labelSize = gStyle->GetLabelSize()/canRelHeight;
  for (int iproj=0; iproj<1; iproj++) {
    if (oaProjForMultiPadPlot[iproj]==0x0 || oaProjForMultiPadPlot[iproj]->GetEntries()==0) continue;
    cSummary->cd(iproj+1);
    SetArrayProperties(oaProjForMultiPadPlot[iproj]); // mainly to give different line colors.
    TH1D* hist = dynamic_cast<TH1D*>(oaProjForMultiPadPlot[iproj]->At(0));
    hist->SetTitleOffset(gStyle->GetTitleOffset("X")    ,"X"); // /1.2
    hist->SetTitleOffset(gStyle->GetTitleOffset("Y")/1.1,"Y"); // /1.2
    hist->SetTitleSize(titleSize,"XY");
    hist->SetLabelSize(labelSize,"XY");
//    hist->SetLabelOffset(hist->GetLabelOffset("Y")*2.,"Y");
//    hist->SetNdivisions(505,"Y");
    if (stype.Contains("PairEff"))   { hist->SetAxisRange(0  , 0.25, "y"); }
    if (stype.Contains("SurvProb"))  { hist->SetAxisRange(0.5, 1.1, "y"); }
    if (TString(hist->GetXaxis()->GetTitle()).Contains("#it{m}_{ee}")) {
      hist->GetXaxis()->SetRangeUser(0.,4.0);
    }
    if (oaLabelsForMultiPadPlot) {
      //oaLabelsForMultiPadPlot[iproj]->Print();
      for (int ihist=0; ihist<oaProjForMultiPadPlot[iproj]->GetEntries(); ihist++) {
        ((TH1D*) oaProjForMultiPadPlot[iproj]->At(ihist))->SetName( oaLabelsForMultiPadPlot[iproj]->At(ihist)->GetName() );
      }
    }

    oaProjForMultiPadPlot[iproj]->DrawClone("hist same");

    if (oaLabelsForMultiPadPlot) {
      TLegend* leg = 0x0;
      if      (stype.Contains("SurvProb"))  { leg = cSummary->cd(1)->BuildLegend(0.20,0.20,0.85,0.39); } // need 'else' because stype for SurvProb also contains PairEff.
      else if (stype.Contains("PairEff"))   { leg = cSummary->cd(1)->BuildLegend(0.20,0.68,0.85,0.87); }
      leg->SetTextSize(labelSize);
      leg->ConvertNDCtoPad();
      leg->SetFillStyle(0);
      //leg->GetListOfPrimitives()->Print();
    }
    cSummary->cd(iproj+1)->RedrawAxis();
  }
  cSummary->Print( Form("%s/cSummary%s.pdf",outdir.Data(),stype.Data()) ); // Patrick
}


//_______________________________________________________________________________________________
void MakeSummaryPlotSingleEff(TObjArray** oaProjForMultiPadPlot, TString outdir, TObjArray** oaLabelsForMultiPadPlot)
{
  // Set up canvas for summary plot
  Double_t sizeFac   = 1.;
  // with the default margins of 0.14 and 0.06, each large pad has has a relative size of 0.8x0.8 and each small one 0.4x0.4.
  // here we need 3 small pads next to each other plus the margins:
  Double_t canRelWidth  = (3.*0.4+0.14+0.06)*sizeFac;
  Double_t canRelHeight = (1.*0.4+0.10+0.10)*sizeFac;
  TCanvas* cSummary = new TCanvas("cSummary", "cSummary", canRelWidth*gStyle->GetCanvasDefW(), canRelHeight*gStyle->GetCanvasDefH());
  // bottom- and topmargins shall have the same absolute size as in a large figure, so scale them by the relative height of this canvas.
  LmHelper::CreateManyPads(cSummary,3,1, 0.1/canRelHeight,0.1/canRelHeight, 0.14/canRelWidth,0.06/canRelWidth);
  Double_t titleSize = gStyle->GetTitleSize()/canRelHeight*1.2;
  Double_t labelSize = gStyle->GetLabelSize()/canRelHeight*1.2;
  for (int iproj=0; iproj<3; iproj++) {
    if (oaProjForMultiPadPlot[iproj]==0x0 || oaProjForMultiPadPlot[iproj]->GetEntries()==0) continue;
    cSummary->cd(iproj+1);
    TH1D* hist = dynamic_cast<TH1D*>(oaProjForMultiPadPlot[iproj]->At(0));
    hist->SetTitleOffset(gStyle->GetTitleOffset("X")/1.2,"X");
    hist->SetTitleOffset(gStyle->GetTitleOffset("Y")/1.2,"Y");
    hist->SetTitleSize(titleSize,"XY");
    hist->SetLabelSize(labelSize,"XY");
    hist->SetLabelOffset(hist->GetLabelOffset("Y")*2.,"Y");
    hist->SetNdivisions(505,"Y");
    hist->GetXaxis()->CenterTitle();
    if (stype.Contains("SingleEff")) { hist->SetAxisRange(0, 0.8, "y"); }
    if (stype.Contains("RandRej-cent")) { hist->SetAxisRange(0, 0.2, "y"); }
    if (stype.Contains("RandRej-semi")) { hist->SetAxisRange(0, 0.1, "y"); }
    if (TString(hist->GetXaxis()->GetTitle()).Contains("#it{p}_{T}")) {
      hist->GetXaxis()->SetRangeUser(0.,1.6);
      hist->SetNdivisions(505,"X");
    }
    if (TString(hist->GetXaxis()->GetTitle()).Contains("#eta")) {
      hist->GetXaxis()->SetRangeUser(-0.9, 0.9);
      hist->SetNdivisions(505,"X");
    }
    //if (TString(hist->GetXaxis()->GetTitle()).Contains("#phi")) hist->GetXaxis()->SetRangeUser(0., TMath::TwoPi());
    oaProjForMultiPadPlot[iproj]->DrawClone("hist same");
    cSummary->cd(iproj+1)->RedrawAxis();
  }
  cSummary->Print( Form("%s/cSummary%s.pdf",outdir.Data(),stype.Data()) ); // Patrick
}


//_______________________________________________________________________________________________
Bool_t SetupLimits(int ix, int iy, int iz, std::vector<Double_t> vx, std::vector<Double_t> vy, std::vector<Double_t> vz, Double_t* limits)
{
  if (ix<(int)vx.size()-1) {
    limits[0] = vx[ix];
    limits[1] = vx[ix+1];
  } else { // integrated
    if (vx.size()==2) return kFALSE; // would be identical to bin 0
    limits[0] = vx[0];
    limits[1] = vx[ix];
  }
  if (iy<(int)vy.size()-1) {
    limits[2] = vy[iy];
    limits[3] = vy[iy+1];
  } else { // integrated
    if (vy.size()==2) return kFALSE; // would be identical to bin 0
    limits[2] = vy[0];
    limits[3] = vy[iy];
  }
  if (iz<(int)vz.size()-1) {
    limits[4] = vz[iz];
    limits[5] = vz[iz+1];
  } else { // integrated
    if (vz.size()==2) return kFALSE; // would be identical to bin 0
    limits[4] = vz[0];
    limits[5] = vz[iz];
  }
  return kTRUE;
}


//_______________________________________________________________________________________________
TCanvas* DrawHists(TObjArray* arrIn, TString opt, TString label)
{
  TLegend leg(0.15,0.65,0.55,0.90);
  leg.SetFillStyle(0);
  leg.SetFillColor(kWhite);
  leg.SetBorderSize(0);
  TLegend leg2(leg.GetX2(),leg.GetY1(),leg.GetX2()+(leg.GetX2()-leg.GetX1()),leg.GetY2());
  leg2.SetFillStyle(0);
  leg2.SetFillColor(kWhite);
  leg2.SetBorderSize(0);

  TPaveText text(0.13,0.9,0.55,0.95,"brNDC");
  text.SetBorderSize(0);
  text.SetTextSize(0.025);
  text.SetFillColor(0);
  text.SetLineColor(kWhite);
  text.SetFillStyle(0);
  text.SetTextAlign(12);
  text.AddText( label.Data() );

  TCanvas* can = new TCanvas("can",""); // Dimensions are set via LmHelper in Init();
  // Styles are defined in LmHelper. If you need others, create setters in LmHelper like SetCanvasWidth().
  //  gPad->SetTicks();
  //  gPad->SetTopMargin(0.02);
  //  gPad->SetRightMargin(0.02);
  //  gPad->SetLeftMargin(0.12);

  int nhists = arrIn->GetEntries();
  //if (nhists>10) leg.SetNColumns(2); // the ordering is shitty...

  for (int i=0; i<nhists; i++) {
    TH1D* hist = dynamic_cast<TH1D*>(arrIn->At(i));
    SetHistProperties(*hist, i, nhists); // its already done by SetArrayProperties()
    if (opt.Contains("PairEff"))   { hist->SetAxisRange(0.0, 0.4, "y"); }
    if (opt.Contains("SurvProb"))  { hist->SetAxisRange(0.0, 1.1, "y"); }
    if (opt.Contains("SingleEff")) { hist->SetAxisRange(0.0, 1.0, "y"); hist->SetAxisRange(0, 1.4, "x"); } //jerome edit
    if (opt.Contains("RandRej"))   { hist->SetAxisRange(0.0, 0.3, "y"); }
    if (opt.Contains("Ratio"))     { hist->SetAxisRange(0.7, 1.3, "y"); }

//    if (i==0) hist->SetDrawOption("hist");
//    else hist->SetDrawOption("hist same");

    TString histname=hist->GetName();
    if (patRemove.Length()>0) histname.ReplaceAll(patRemove,"");
    histname.ReplaceAll("_px","");
    histname.ReplaceAll("_py","");
    histname.ReplaceAll("_pz","");
    //leg.AddEntry(hist,histname.Data(),"l");
    if(i < nhists/2)  leg .AddEntry(hist,histname.Data(),"l"); //Form("cut %2d",i+1)
    else              leg2.AddEntry(hist,histname.Data(),"l");

    if (opt.Contains("Ratio")) {
      if(i>0)
        hist->Divide(dynamic_cast<TH1D*>(arrIn->At(0)));
      histname.ReplaceAll("_px","Ratio");
      histname.ReplaceAll("_py","Ratio");
      histname.ReplaceAll("_pz","Ratio");
    }
  }

  if (opt.Contains("Ratio")) {
        dynamic_cast<TH1D*>(arrIn->At(0))->Divide(dynamic_cast<TH1D*>(arrIn->At(0)));
    }

  if      (iconf<=confMaxPat) arrIn->DrawClone("hist same"); // Patrick
  else if (iconf<=confMaxCar) arrIn->DrawClone("hist e same"); // Carsten
  else                        arrIn->DrawClone("hist same"); // new user -> old defaults
  leg.DrawClone("same");
  leg2.DrawClone("same");
  text.DrawClone("same");
  can->RedrawAxis();
  return can;
}


//_______________________________________________________________________________________________
void DivideHists(TObjArray* arrIn, TH1* hDenom)
{
  int nhists = arrIn->GetEntries();
  for (int i=0; i<nhists; i++) {
    ((TH1*)arrIn->At(i))->Divide( hDenom );
  }
}


//_______________________________________________________________________________________________
TObjArray* MakeProjection(TObjArray* arrIn, Double_t *limits, TString opt, TString filetitle)
{
  std::cout << "MakeProjection() opt = " << opt.Data() << std::endl;

  Double_t kSmallDelta = 1e-15;
  TObjArray* arrOut = 0x0;

  TObjArray* oaopt = opt.Tokenize("; ");
  TString opt0=oaopt->At(0)->GetName();

  TString xtit="", ytit="", ztit="", ctit="";
  if (opt.Contains("PairEff"))   { xtit="#it{m}_{ee} (GeV/#it{c}^{2})";  ytit="#it{p}_{T,ee} (GeV/#it{c})";  ztit="";  ctit="#it{#epsilon}_{ pair}"; }
  if (opt.Contains("SurvProb"))  { xtit="#it{m}_{ee} (GeV/#it{c}^{2})";  ytit="#it{p}_{T,ee} (GeV/#it{c})";  ztit="";  ctit="#it{P}_{ surv}^{ pair}"; }
  if (opt.Contains("SingleEff")) { xtit="#it{p}_{T} (GeV/#it{c})";  ytit="#it{#eta}";  ztit="#it{#varphi}";  ctit="#it{#epsilon}_{ track}"; }
  if (opt.Contains("RandRej"))   { xtit="#it{p}_{T} (GeV/#it{c})";  ytit="#it{#eta}";  ztit="#it{#varphi}";  ctit="#it{P}_{rand}"; }
  Bool_t noCustomTitles = TString(xtit+ytit+ztit+ctit).IsNull();

  int dim=((TH1*)arrIn->At(0))->GetDimension();

  if (dim==1) {
    arrOut = new TObjArray(*arrIn); // shallow copy
    return arrOut;
  }

  arrOut = new TObjArray();
  arrOut->SetOwner();
  Double_t minx = 0, maxx = -1;
  Double_t miny = 0, maxy = -1;
  Double_t minz = 0, maxz = -1;
  if (dim>1) minx = limits[0], maxx = limits[1], miny = limits[2], maxy = limits[3];
  if (dim>2) minz = limits[4], maxz = limits[5];

  int nhists = arrIn->GetEntries();
  for (int i=0; i<nhists; i++) {
    TH1*  hIn  = (TH1*) arrIn->At(i);
    TH1D* hOut = 0x0;
    // should give a unique name to each projection!
    //TString newname(Form("%s_p%s_%.2fto%.2f",hIn->GetName(),opt.Data(),min,max));

    //
    // simple cases: project into 1D histogram
    //
    if (opt0.EqualTo("x")) {
      TString newname(Form("%s_px",hIn->GetName()));
      if (nfiles>1) newname.Append(Form(" (%s)",filetitle.Data()));
      if (dim==2) hOut = ((TH2*)hIn)->ProjectionX(newname.Data(), hIn->GetYaxis()->FindBin(miny), hIn->GetYaxis()->FindBin(maxy-kSmallDelta), "e"); // subtract a small delta because the upper bin edge already belongs to the next bin!
      if (dim==3) hOut = ((TH3*)hIn)->ProjectionX(newname.Data(), hIn->GetYaxis()->FindBin(miny), hIn->GetYaxis()->FindBin(maxy-kSmallDelta), hIn->GetZaxis()->FindBin(minz), hIn->GetZaxis()->FindBin(maxz-kSmallDelta), "e");
      if (TString(hIn->GetXaxis()->GetTitle()).Length()!=0 && noCustomTitles) {
        hOut->SetXTitle(hIn->GetXaxis()->GetTitle());
        hOut->SetYTitle(hIn->GetTitle());
      } else {
        hOut->SetXTitle(xtit);
        hOut->SetYTitle(ctit);
      }
    }
    else if (opt0.EqualTo("y")) {
      TString newname(Form("%s_py",hIn->GetName()));
      if (nfiles>1) newname.Append(Form(" (%s)",filetitle.Data()));
      if (dim==2) hOut = ((TH2*)hIn)->ProjectionY(newname.Data(), hIn->GetXaxis()->FindBin(minx), hIn->GetXaxis()->FindBin(maxx-kSmallDelta), "e");
      if (dim==3) hOut = ((TH3*)hIn)->ProjectionY(newname.Data(), hIn->GetXaxis()->FindBin(minx), hIn->GetXaxis()->FindBin(maxx-kSmallDelta), hIn->GetZaxis()->FindBin(minz), hIn->GetZaxis()->FindBin(maxz-kSmallDelta), "e");
      if (TString(hIn->GetXaxis()->GetTitle()).Length()!=0 && noCustomTitles) {
        hOut->SetXTitle(hIn->GetYaxis()->GetTitle());
        hOut->SetYTitle(hIn->GetTitle());
      } else {
        hOut->SetXTitle(ytit);
        hOut->SetYTitle(ctit);
      }
    }
    else if (opt0.EqualTo("z")) {
      TString newname(Form("%s_pz",hIn->GetName()));
      if (nfiles>1) newname.Append(Form(" (%s)",filetitle.Data()));
      //if (dim==2) hOut = ((TH2*)hIn)->ProjectionZ(newname.Data(), hIn->GetXaxis()->FindBin(min1), hIn->GetXaxis()->FindBin(max1-kSmallDelta), "e");
      if (dim==3) hOut = ((TH3*)hIn)->ProjectionZ(newname.Data(), hIn->GetXaxis()->FindBin(minx), hIn->GetXaxis()->FindBin(maxx-kSmallDelta), hIn->GetYaxis()->FindBin(miny), hIn->GetYaxis()->FindBin(maxy-kSmallDelta), "e");
      if (TString(hIn->GetXaxis()->GetTitle()).Length()!=0 && noCustomTitles) {
        hOut->SetXTitle(hIn->GetZaxis()->GetTitle());
        hOut->SetYTitle(hIn->GetTitle());
      } else {
        hOut->SetXTitle(ztit);
        hOut->SetYTitle(ctit);
      }
    }
    else {
      //
      // projections of 3D to 2D
      //
      if (dim==3) {
        hIn->SetAxisRange(minx, maxx-kSmallDelta, "x");
        hIn->SetAxisRange(miny, maxy-kSmallDelta, "y");
        hIn->SetAxisRange(minz, maxz-kSmallDelta, "z");
        arrOut->Add( (dynamic_cast<TH3D*>(hIn))->Project3D(opt0.Data()) );
      }
      else {
        std::cout << "ERROR: MakeProjection() unforeseen option!" << std::endl;
      }
    }

    // special stuff for patrick...
    if (opt.Contains("RandRej")) {
      if (opt0.EqualTo("x")) {
        Double_t pt_bins[] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0,
          2.2, 2.4, 2.6, 2.8, 3.0, 3.5, 3.8, 4.0};
        Int_t n_pt_bins = sizeof(pt_bins)/sizeof(*pt_bins) -1;
        hOut = (TH1D*) hOut->Rebin(n_pt_bins, hOut->GetName(), pt_bins);
        if (opt.Contains("pt400")) {
          Int_t bini=0;
          while (hOut->GetBinLowEdge(bini+1)<=0.4) {
            hOut->SetBinContent(bini,0);
            hOut->SetBinError(bini,0);
            bini++;
          }
        }
      }
      if (opt0.EqualTo("z")) {
        Int_t n_bins_temp = hOut->GetNbinsX();
        Double_t bins_temp[n_bins_temp+1];
        hOut->GetXaxis()->GetLowEdge(bins_temp); // Fills the binning of the original histogram into the array.
        bins_temp[n_bins_temp] = hOut->GetXaxis()->GetBinLowEdge(n_bins_temp+1); // fill last bin edge manually...
        bins_temp[0] = 0.001; // manipulate first bin to get rid of the label "0" for a multi-pad plot.
        hOut = (TH1D*) hOut->Rebin(n_bins_temp, hOut->GetName(), bins_temp);
      }
    }

    if (hOut) arrOut->Add(hOut);
  }

  return arrOut;
}


//_______________________________________________________________________________________________
TObjArray* SelectHistos(TList* histlist, TString patSelect, TString patReject)
{
  TObjArray* oaHist = new TObjArray();
  oaHist->SetOwner(); // not sure if ok.
  for(Int_t i=0; i<histlist->GetEntries(); i++) {
    if (patReject.Length()==0) { // every string contains the null string, so we need to treat this case separately.
      if (TString(histlist->At(i)->GetName()).Contains(patSelect.Data()))
        oaHist->Add(histlist->At(i));
      }
    else {
      TString teststr(histlist->At(i)->GetName());
      if (    teststr.Contains(patSelect.Data())
          && !teststr.Contains(patReject.Data()) ) // this check does not work without the teststr substitution! :-(
      {
        //std::cout <<  "   patSelect.Data(): " << patSelect.Data() << "   patReject.Data(): " << patReject.Data() << "   name: " << TString(histlist->At(i)->GetName()).Data() << std::endl;
        oaHist->Add(histlist->At(i));
      }
    }
  }
  return oaHist;
}


//_______________________________________________________________________________________________
TList* GetList(TFile* fileIn, TString listname)
{
  TList* list=0x0;
  if (listname.Length()==0) {
    if (debug) std::cout << " creating list from listof keys in file " << std::endl;
    list = new TList();
    TIter nextKey(fileIn->GetListOfKeys());
    TObject* key=0x0;
    while ((key=nextKey())) list->Add(fileIn->Get( key->GetName() ));
  }
  else {
    TObjArray* oaListPath = listname.Tokenize("/");
    if (debug) std::cout << " getting list : " << oaListPath->At(0)->GetName() << std::endl;
    list = (TList*) fileIn->Get(oaListPath->At(0)->GetName());
    for (Int_t i=1; i<oaListPath->GetEntries(); i++) {
      if (debug) std::cout << "  getting list : " << oaListPath->At(i)->GetName() << std::endl;
      TList* templist = (TList*) list->FindObject(oaListPath->At(i)->GetName());
      if (templist) list = templist;
      else std::cout << "\33[1;31m ERROR: list " << oaListPath->At(i)->GetName() << " not found in list " << list->GetName() << "\33[0m" << std::endl;
    }
  }
  if (debug) { std::cout << " list contains : " << std::endl; list->Print(); }
  return list;
}


//_______________________________________________________________________________________________
void SetArrayProperties(TObjArray* arrIn, TString opt)
{
  int nhists = arrIn->GetEntries();
  for (int i=0; i<nhists; i++) {
    TH1D* hist = dynamic_cast<TH1D*> (arrIn->At(i));
    SetHistProperties(*hist, i, nhists);
    hist->SetLineStyle( atoi(opt.Data()) );
  }
}


//_______________________________________________________________________________________________
void SetHistProperties(TH1D &h, Int_t ith, Int_t NHists){
  h.SetTitle("");
  h.SetTitleOffset(gStyle->GetTitleOffset("X"),"X");
  h.SetTitleOffset(gStyle->GetTitleOffset("Y"),"Y");
  h.SetStats(0);
  h.SetMarkerStyle(20);
  h.SetMarkerSize(0.8);
  Int_t color = LmHelper::GetUniformColor(ith,NHists);
  h.SetMarkerColor(color);
  h.SetLineColor(color);
  if      (iconf<=confMaxPat) { // Patrick
    h.SetLineWidth(2);
    h.SetMarkerStyle(0);
  }
  else if (iconf<=confMaxCar) h.SetLineWidth(4); // Carsten
  else                        h.SetLineWidth(4); // new user -> entscheidet euch selbst...
}

//_______________________________________________________________________________________________
void SetError(TH1D &h){
  for(Int_t i = 1; i <= h.GetNbinsX(); ++i){
    h.SetBinError(i,TMath::Sqrt(h.GetBinContent(i)));
  }
}
