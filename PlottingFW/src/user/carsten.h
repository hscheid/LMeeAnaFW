#include <vector>

#include "TMath.h"
#include "TString.h"
#include "TBenchmark.h"
#include "TSystem.h"

#include "LmCocktail.h"
#include "LmBackground.h"
#include "LmHandler.h"
#include "LmFileManager.h"


Double_t plotMeeMin= 0.; Double_t plotMeeMax = 0.139; Double_t  plotMeeMax_sys = 3.3;
Double_t plotPteeMin = 0.; Double_t plotPteeMax = 4.; Double_t plotPteeMax_sys = 4.;

Bool_t    kWriteFile        = kTRUE;
Bool_t    printLegend       = kTRUE;


std::vector<TString> Centrality {"0080", "0010", "1050", "5080"};
TString   centrality        = Centrality[0];
Bool_t    kDoPt400          = kTRUE;

Bool_t    kLookAtMass       = kTRUE; // true: look at mass spectra; false: look at pt spectra
Bool_t    kLookIntegrated   = kFALSE; // takes first and last bin of binning

Bool_t    kDoSystematics    = kFALSE;
UInt_t    kBackground       = LmBackground::kHybrid;
// UInt_t    kBackground       = LmBackground::kGeom;
// UInt_t    kBackground       = LmBackground::kArith;
UInt_t    kDoExclusionCutZ  = LmManager::kFlatCorrSub;
// UInt_t    kDoExclusionCutZ  = LmManager::kFlatCorrUnsub;
// UInt_t    kDoExclusionCutZ  = LmManager::kNoCut;
Bool_t    kDoSignifRaw      = kTRUE;

Bool_t    kUseRFactor       = kFALSE;

Bool_t    kDoNormNevents    = kTRUE;
Bool_t    kDoNormBinwidth   = kTRUE;

Bool_t    kDoEffiCorrection = kTRUE;

Bool_t    kDoConfLevel      = kFALSE;
Double_t  confLevel         = 0.84;

Bool_t    kDoRatio          = kTRUE;

Bool_t    kDoCocktail       = kFALSE;
Bool_t    kDoCocktailOnly   = kFALSE;

Bool_t    kDoReadFromRootFile = kFALSE;
Int_t     debug             = 0;

TString name[] = {
   "./input/data_LMEEoutput/LMEEoutput-347-1full.root",  // 1 QM 2014 setting, 400 MeV single leg pt cut. From Patricks LEGO train
   "./input/data_LMEEoutput/LMEEoutput_100Chunks_woPID.root", // LHC15o lowInt no PID
   "./input/data_LMEEoutput/LMEEoutput_LHC15o_lowIR_ITSSA.root", // lowInt ITSSA
   "", // First hiInt Chunk out of 6. Normal Analysis cuts used
   "", // low Intensity runs. OUTDATED SUPERSEEDED BY LMEEoutput_654_LHC15o_lowIR
   "", // low Intensity runs. PID scheme test on GSI
   "", // OUTDATED SUPERSEEDED BY LMEEoutput_650_LHC15o_HighIR
   "", // ++
   "", // --
   "", // first, second and third chunk of high IR runs
   "", // 10
   "", // first, second and third chunk of high IR runs after TPC splines correction
   "./input/data_LMEEoutput/LMEEoutput-cut16-semi-1full.root", // LHC11h with opening angle cut
   "",
   "./input/data_LMEEoutput/LMEEoutput_MC_357_LHC16g1b.root", // First output from MC
   "",
   "",
   "./input/data_LMEEoutput/LMEEoutput_highIR_1_noTrackCuts.root",
   "./input/data_LMEEoutput/LMEEoutput_highIR_2_noTrackCuts.root",
   "./input/data_LMEEoutput/LMEEoutput_lowIR_noTrackCuts.root",
   "./input/data_LMEEoutput/LMEEoutput_888_lowIR.root", //20
   "./input/data_LMEEoutput/LMEEoutput_886_highIR1.root",
   "./input/data_LMEEoutput/LMEEoutput_887_highIR2.root",
   "./input/data_LMEEoutput/LMEEoutput_88x_all.root",
   "./input/data_LMEEoutput/LMEEoutput_889_lowIR.root",
   "./input/data_LMEEoutput/LMEEoutput_890_highIR1.root",
   "./input/data_LMEEoutput/LMEEoutput_891_highIR2.root",
   "./input/data_LMEEoutput/LMEEoutput_890_all.root",
   "./input/data_LMEEoutput/LMEEoutput_897899_all.root",
   "./input/data_LMEEoutput/LMEEoutput_fine_binning.root", //29
   "./input/data_LMEEoutput/LMEEoutput_903905.root", // working event plane task
   "./input/data_LMEEoutput/LMEEoutput_c00-09.root", // 31 first with 20 cut settings
   "./input/data_LMEEoutput/LMEEoutput_c10-19.root", // 32 first with 20 cut settings
   "./input/data_LMEEoutput/LMEEoutput_v2.root", // 33 first time with all 20 settings and ITSsharedClusterCut
   "./input/data_LMEEoutput/LMEEoutput_4SharedITS.root", // 34: 4 different shared cluster settings to compare S/B and Signif
   "./input/data_LMEEoutput/LMEEoutput_MC_PHIV_v2.root", // 35: MC AOD to check differences in efficiency calculation of TOFreq and TOFif
   "./input/data_LMEEoutput/LMEEoutput_MCTruth.root", // 36: MC truth. compatible to 35 but without kinematic cuts :(
   "./input/data_LMEEoutput/LMEEoutput_MC_AOD_ContaminationCheck.root", // 37: TOFreq and TOFif + TOFif_pdgele and TOFreq_pdgele to check effect of contamination
   ""
   };

TString tree_name[] = {
  "caklein_LMEEPbPb_out",
  "reichelt_LMEEPbPb2011_out",
  "caklein_LMEEPbPb_out1",
  "caklein_LMEEPbPb_out2",
  "caklein_LMEEPbPb_out0",
  ""
};

TString cut_setting[] =
{ "ITSTPCTOFif_trkSPDfirst_1_kSemi",
  "kITSTPCTOFif_trkSPDfirst_kINT7_pt100_woPID",
  "kPbPb2015_Pt400_ITSSA",
  "kPbPb2015_Pt400_TPCele_AsymITS_tightTOFreq",
  "kPbPb2015_Pt400_TPCele_AsymITS_tightTOFif",
  "kPbPb2015_Pt400_mastermind",
  "kPbPb2015_Pt400_mastermind2",
  "cut16_SPDorSDD14_PID16_pt400",
  "kPbPb2015_TOFif_NoTrackQualityCuts_Pt400",
  "kPbPb2015_Pt400_PID_cutoff_pion_kaon_proton",
  "kPbPb2015_Pt400_tightTOFif_semi", //10
  "kPbPb2015_Pt400_looseTOFif_semi", // 11
  "kPbPb2015_Pt400_tightTOFreq_semi", // 12
  "cut0", "cut1", "cut2", "cut3", "cut4", "cut5", "cut6", "cut7", "cut8", "cut9", // 13-22
  "cut10", "cut11", "cut12", "cut13", "cut14", "cut15", "cut16", "cut17", "cut18", "cut19", // 23-32
  "cut20",
  "cut11_Version1", "cut11_0SITSCl_Version1", "cut11_1SITSCl_Version1", "cut11_3SITSCl_Version1", //34-37
  "kPbPb2015_Pt400_looseTOFif_MB", //38
  "kPbPb2015_Pt400_tightTOFreq_MB", // 39
  "kPbPb2015_Pt400_looseTOFif_MB_pdgEle", //40
  "kPbPb2015_Pt400_tightTOFreq_MB_pdgEle", // 41
  ""
};
TString cuts[] = {
  "cut0", "cut1", "cut2", "cut3", "cut4", "cut5", "cut6", "cut7", "cut8", "cut9", // 0
  "cut10", "cut11", "cut12", "cut13", "cut14", "cut15", "cut16", "cut17", "cut18", "cut19",
  "cut20"
};
TString coll_system = "Pb#minusPb, #sqrt{#it{s}_{NN}} = 5.02 TeV";
TString inputhist("pInvMass_PairPt_PhivPair");
Int_t   inputdim = 3;
TString projoption = "yx"; // Mass and Pair pt and NOT PhiV

// corresponding input efficiency files
TString effi_name[] = {
   "./input/paireff/pairEff_raw-17h-std_QM2014_400MeV.root",
   "./input/paireff/pairefficiency_semi_pt400_729_104.root",
   "./input/paireff/pairEff_raw-1050-pt400.root",
   "./input/paireff/pairefficiency_semi_pt400_16x.root",
   "./input/paireff/pairefficiency_c00_19.root",
   "./input/paireff/pairefficiency_v2.root",
   "./input/paireff/pairefficiency_pt400_v3.root",
   "./input/paireff/pairefficiency_pt400_v4.root", // [7]
   "./input/paireff/pairefficiency_pt400_MCClosure.root", // [8]
  ""
};
  // name of 2D generated and reconstructed histogram
TString effi_gen[] = {
   "hNGenPairs_pt400",
   "NGenPairs_pt400_8000",
   "NGenPairs_pt400_3500_opAngle50",
  ""
};
TString effi_rec[] = {
   "Npair_hEff_Nreco_Ele_ITSTPCTOFif_trkSPDfirst_1_pt400",
   "NRecPairs_hEff_Ele_TOFreq_pt400_8000",
   "NRecPairs_hEff_Ele_TOFif_pt400_8000",
   "NRecPairs_hEff_Ele_newPID_pt400_8000",
   "NRecPairs_hEff_Ele_cut16_SPDorSDD14_PID16_pt400_3500",        // measurable effi, no opening angle cut.
   "NRecPairs_hEff_Ele_cut16_SPDorSDD14_PID16_pt400_3500_opAngle50", // meas., with opening angle cut.
   "NRecPairs_hEff_Ele_TOFreq_pt400_8000",
   "NRecPairs_hEff_Ele_looseTOFif_pt400_8000",
   "NRecPairs_hEff_Ele_tightTOFif_pt400_8000",
   "",
   "NRecPairs_hEff_Ele_cut0_pt400_8000", //10
   "NRecPairs_hEff_Ele_cut1_pt400_8000",
   "NRecPairs_hEff_Ele_cut2_pt400_8000",
   "NRecPairs_hEff_Ele_cut3_pt400_8000",
   "NRecPairs_hEff_Ele_cut4_pt400_8000",
   "NRecPairs_hEff_Ele_cut5_pt400_8000",
   "NRecPairs_hEff_Ele_cut6_pt400_8000",
   "NRecPairs_hEff_Ele_cut7_pt400_8000",
   "NRecPairs_hEff_Ele_cut8_pt400_8000",
   "NRecPairs_hEff_Ele_cut9_pt400_8000",
   "NRecPairs_hEff_Ele_cut10_pt400_8000",
   "NRecPairs_hEff_Ele_cut11_pt400_8000",
   "NRecPairs_hEff_Ele_cut12_pt400_8000",
   "NRecPairs_hEff_Ele_cut13_pt400_8000",
   "NRecPairs_hEff_Ele_cut14_pt400_8000",
   "NRecPairs_hEff_Ele_cut15_pt400_8000",
   "NRecPairs_hEff_Ele_cut16_pt400_8000",
   "NRecPairs_hEff_Ele_cut17_pt400_8000",
   "NRecPairs_hEff_Ele_cut18_pt400_8000",
   "NRecPairs_hEff_Ele_cut19_pt400_8000",
   "NRecPairs_hEff_Ele_cut20_pt400_8000",
   "NRecPairs_hEff_Ele_kPbPb2015_Pt400_looseTOFif_MB_pt400_8000", //31
   "NRecPairs_hEff_Ele_kPbPb2015_Pt400_tightTOFreq_MB_pt400_8000", //32
   "NRecPairs_hEff_Ele_kPbPb2015_Pt400_looseTOFif_MB_exclMismatch_pt400_8000", //33
   "NRecPairs_hEff_Ele_kPbPb2015_Pt400_tightTOFreq_MB_exclMismatch_pt400_8000", //34
   ""
};

// config string for manager
TString cconfig[] = { // this determines which settings will really be analysed!
  // ( coll_system + ":" + name[0] + ":" + tree_name[1] + ":" + cut_setting[0] + ":" + "LHC11h pass2 - 20-50%" + ":" + effi_name[0] + ":" + effi_gen[0] + ":" + effi_rec[0] ), // "./input/LMEEoutput-347-1full.root",  // QM 2014 setting, 400 MeV single leg pt cut
  // ( coll_system + ":" + name[12] + ":" + tree_name[1] + ":" + cut_setting[7] + ":" + "LHC11h pass2 - 10-50%" + ":" + effi_name[2] + ":" + effi_gen[2] + ":" + effi_rec[5] ), // "./input/LMEEoutput-347-1full.root",  // QM 2014 setting, 400 MeV single leg pt cut
  // (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[1] + ":" + "LHC15o pass2 - 0-90% - woPID" + ":" + effi_name[0] + ":" + effi_gen[0] + ":" + effi_rec[0] ), //
  // (coll_system + ":" + name[2] + ":" + tree_name[0] + ":" + cut_setting[2] + ":" + "LHC15o - ITSSA" + ":" + effi_name[0] + ":" + effi_gen[0] + ":" + effi_rec[0] ), //
  // (coll_system + ":" + name[28] + ":" + tree_name[3] + ":" + cut_setting[10] + ":" + "data - PID Scheme1"+   ":" + effi_name[3] + ":" + effi_gen[1] + ":" + effi_rec[8] ), //
  // (coll_system + ":" + name[28] + ":" + tree_name[3] + ":" + cut_setting[11] + ":" + "PbPb @ 5.02 TeV"  + ":" + effi_name[3] + ":" + effi_gen[1] + ":" + effi_rec[7] ), //
  // (coll_system + ":" + name[28] + ":" + tree_name[3] + ":" + cut_setting[12] + ":" + "data - PID Scheme2" +      ":" + effi_name[3] + ":" + effi_gen[1] + ":" + effi_rec[6] ), //
  // (coll_system + ":" + name[29] + ":" + tree_name[4] + ":" + cut_setting[11] + ":" + "data"  + ":" + effi_name[3] + ":" + effi_gen[1] + ":" + effi_rec[7] ), //
  // (coll_system + ":" + name[30] + ":" + tree_name[2] + ":" + cut_setting[10] + ":" + "tightTOFif - /wo Pileupcut"  + ":" + effi_name[3] + ":" + effi_gen[1] + ":" + effi_rec[8] ), //
  // (coll_system + ":" + name[30] + ":" + tree_name[3] + ":" + cut_setting[10] + ":" + "tightTOFif"  + ":" + effi_name[3] + ":" + effi_gen[1] + ":" + effi_rec[8] ), //
  // (coll_system + ":" + name[30] + ":" + tree_name[2] + ":" + cut_setting[11] + ":" + "looseTOFif - /wo Pileupcut"  + ":" + effi_name[3] + ":" + effi_gen[1] + ":" + effi_rec[7] ), //
  // (coll_system + ":" + name[30] + ":" + tree_name[3] + ":" + cut_setting[11] + ":" + "looseTOFif"  + ":" + effi_name[3] + ":" + effi_gen[1] + ":" + effi_rec[7] ), //
  // (coll_system + ":" + name[30] + ":" + tree_name[2] + ":" + cut_setting[12] + ":" + "TOFreq - /wo Pileupcut"  + ":" + effi_name[3] + ":" + effi_gen[1] + ":" + effi_rec[1] ), //
  // (coll_system + ":" + name[30] + ":" + tree_name[3] + ":" + cut_setting[12] + ":" + "TOFreq"  + ":" + effi_name[3] + ":" + effi_gen[1] + ":" + effi_rec[1] ), //
  // first 20 Cutsetting without ITS shared Cluster
  // (coll_system + ":" + name[31] + ":" + tree_name[2] + ":" + cuts[0]  + ":" + "cut00 - TOFreq"   + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[10] ), //
  // (coll_system + ":" + name[31] + ":" + tree_name[2] + ":" + cuts[1]  + ":" + "cut01 - TOFreq"   + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[11] ), //
  // (coll_system + ":" + name[31] + ":" + tree_name[2] + ":" + cuts[6]  + ":" + "cut06 - TOFreq"   + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[16] ), //
  // (coll_system + ":" + name[31] + ":" + tree_name[2] + ":" + cuts[7]  + ":" + "cut07 - TOFreq"   + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[17] ), //
  // (coll_system + ":" + name[32] + ":" + tree_name[4] + ":" + cuts[10] + ":" + "cut10 - TOFreq"  + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[20] ), //
  // (coll_system + ":" + name[32] + ":" + tree_name[4] + ":" + cuts[11] + ":" + "cut11 - TOFreq"  + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[21] ), //
  // (coll_system + ":" + name[32] + ":" + tree_name[4] + ":" + cuts[12] + ":" + "cut12 - TOFreq"  + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[22] ), //
  // (coll_system + ":" + name[32] + ":" + tree_name[4] + ":" + cuts[13] + ":" + "cut13 - TOFreq"  + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[23] ), //
  // (coll_system + ":" + name[32] + ":" + tree_name[4] + ":" + cuts[16] + ":" + "cut16 - TOFreq"  + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[26] ), //
  // (coll_system + ":" + name[31] + ":" + tree_name[2] + ":" + cuts[2]  + ":" + "cut02 - TOFif"   + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[12] ), //
  // (coll_system + ":" + name[31] + ":" + tree_name[2] + ":" + cuts[3]  + ":" + "cut03 - TOFif"   + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[13] ), //
  // (coll_system + ":" + name[31] + ":" + tree_name[2] + ":" + cuts[4]  + ":" + "cut04 - TOFif"   + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[14] ), //
  // (coll_system + ":" + name[31] + ":" + tree_name[2] + ":" + cuts[5]  + ":" + "cut05 - TOFif"   + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[15] ), //
  // (coll_system + ":" + name[31] + ":" + tree_name[2] + ":" + cuts[8]  + ":" + "cut08 - TOFif"   + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[18] ), //
  // (coll_system + ":" + name[31] + ":" + tree_name[2] + ":" + cuts[9]  + ":" + "cut09 - TOFif"   + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[19] ), //
  // (coll_system + ":" + name[32] + ":" + tree_name[4] + ":" + cuts[14] + ":" + "cut14 - TOFif"  + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[24] ), //
  // (coll_system + ":" + name[32] + ":" + tree_name[4] + ":" + cuts[15] + ":" + "cut15 - TOFif"  + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[25] ), //
  // (coll_system + ":" + name[32] + ":" + tree_name[4] + ":" + cuts[17] + ":" + "cut17 - TOFif"  + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[27] ), //
  // (coll_system + ":" + name[32] + ":" + tree_name[4] + ":" + cuts[18] + ":" + "cut18 - TOFif"  + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[28] ), //
  // (coll_system + ":" + name[32] + ":" + tree_name[4] + ":" + cuts[19] + ":" + "cut19 - TOFif"  + ":" + effi_name[4] + ":" + effi_gen[1] + ":" + effi_rec[29] ), //

  // first 20 Cutsetting with ITS shared Cluster
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[1] +  ":" + "cut1   - TOFreq"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[11] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[2] +  ":" + "cut2   - TOFreq"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[12] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[3] +  ":" + "cut3   - TOFreq"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[13] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[4] +  ":" + "cut4   - TOFreq"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[14] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[5] +  ":" + "cut5   - TOFreq"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[15] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[6] +  ":" + "cut6   - TOFreq"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[16] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[7] +  ":" + "cut7   - TOFreq"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[17] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[8] +  ":" + "cut8   - TOFreq"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[18] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[9] +  ":" + "cut9   - TOFreq"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[19] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[10] + ":" + "cut10 - TOFreq" + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[20] ), //
  // // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[11] + ":" + "cut11 - TOFif"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[21] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[12] + ":" + "cut12 - TOFif"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[22] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[13] + ":" + "cut13 - TOFif"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[23] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[14] + ":" + "cut14 - TOFif"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[24] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[15] + ":" + "cut15 - TOFif"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[25] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[16] + ":" + "cut16 - TOFif"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[26] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[17] + ":" + "cut17 - TOFif"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[27] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[18] + ":" + "cut18 - TOFif"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[28] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[19] + ":" + "cut19 - TOFif"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[29] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[20] + ":" + "cut20 - TOFif"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[30] ), //

  // New Efficiency calculation with ESD Cuts
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[1] +  ":" + "cut1   - TOFreq"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[11] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[2] +  ":" + "cut2   - TOFreq"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[12] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[3] +  ":" + "cut3   - TOFreq"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[13] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[4] +  ":" + "cut4   - TOFreq"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[14] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[5] +  ":" + "cut5   - TOFreq"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[15] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[6] +  ":" + "cut6   - TOFreq"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[16] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[7] +  ":" + "cut7   - TOFreq"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[17] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[8] +  ":" + "cut8   - TOFreq"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[18] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[9] +  ":" + "cut9   - TOFreq"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[19] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[10] + ":" + "cut10 - TOFreq" + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[20] ), //
  // // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[11] + ":" + "cut11 - TOFif"  + ":" + effi_name[5] + ":" + effi_gen[1] + ":" + effi_rec[21] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[12] + ":" + "cut12 - TOFif"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[22] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[13] + ":" + "cut13 - TOFif"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[23] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[14] + ":" + "cut14 - TOFif"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[24] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[15] + ":" + "cut15 - TOFif"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[25] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[16] + ":" + "cut16 - TOFif"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[26] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[17] + ":" + "cut17 - TOFif"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[27] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[18] + ":" + "cut18 - TOFif"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[28] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[19] + ":" + "cut19 - TOFif"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[29] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[20] + ":" + "cut20 - TOFif"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[30] ), //

  // New Efficiency calculation with ESD Cuts and TOFreq-Mismatch
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[1] +  ":" + "cut1   - TOFreq"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[11] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[2] +  ":" + "cut2   - TOFreq"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[12] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[3] +  ":" + "cut3   - TOFreq"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[13] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[4] +  ":" + "cut4   - TOFreq"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[14] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[5] +  ":" + "cut5   - TOFreq"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[15] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[6] +  ":" + "cut6   - TOFreq"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[16] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[7] +  ":" + "cut7   - TOFreq"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[17] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[8] +  ":" + "cut8   - TOFreq"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[18] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[9] +  ":" + "cut9   - TOFreq"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[19] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[10] + ":" + "cut10 - TOFreq" + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[20] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[11] + ":" + "cut11 - TOFif"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[21] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[12] + ":" + "cut12 - TOFif"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[22] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[13] + ":" + "cut13 - TOFif"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[23] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[14] + ":" + "cut14 - TOFif"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[24] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[15] + ":" + "cut15 - TOFif"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[25] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[16] + ":" + "cut16 - TOFif"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[26] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[17] + ":" + "cut17 - TOFif"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[27] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[18] + ":" + "cut18 - TOFif"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[28] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[19] + ":" + "cut19 - TOFif"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[29] ), //
  // (coll_system + ":" + name[33] + ":" + tree_name[2] + ":" + cuts[20] + ":" + "cut20 - TOFif"  + ":" + effi_name[7] + ":" + effi_gen[1] + ":" + effi_rec[30] ), //

  // TOF efficiency MC closure test
  (coll_system + ":" + name[35] + ":" + tree_name[2] + ":" + cut_setting[39] + ":" + "TOFreq - \"standard effi\""  + ":" + effi_name[8] + ":" + effi_gen[1] + ":" + effi_rec[32] ), //
  (coll_system + ":" + name[35] + ":" + tree_name[2] + ":" + cut_setting[38] + ":" + "TOFif - \"standard effi\""   + ":" + effi_name[8] + ":" + effi_gen[1] + ":" + effi_rec[31] ), //
  // (coll_system + ":" + name[35] + ":" + tree_name[2] + ":" + cut_setting[39] + ":" + "TOFreq - \"Mismatch excluded\""  + ":" + effi_name[8] + ":" + effi_gen[1] + ":" + effi_rec[34] ), //
  // (coll_system + ":" + name[35] + ":" + tree_name[2] + ":" + cut_setting[38] + ":" + "TOFif - \"Mismatch excluded\""   + ":" + effi_name[8] + ":" + effi_gen[1] + ":" + effi_rec[33] ), //
  // (coll_system + ":" + name[36] + ":" + tree_name[2] + ":" + cut_setting[38] + ":" + "MCTruth"   + ":" + effi_name[-1] + ":" + effi_gen[1] + ":" + effi_rec[31] ), //

  // (coll_system + ":" + name[37] + ":" + tree_name[2] + ":" + cut_setting[39] + ":" + "TOFreq"  + ":" + effi_name[8] + ":" + effi_gen[1] + ":" + effi_rec[32] ), //
  // (coll_system + ":" + name[37] + ":" + tree_name[2] + ":" + cut_setting[38] + ":" + "TOFif"   + ":" + effi_name[8] + ":" + effi_gen[1] + ":" + effi_rec[31] ), //
  // (coll_system + ":" + name[37] + ":" + tree_name[2] + ":" + cut_setting[41] + ":" + "TOFreq + pdgEle"  + ":" + effi_name[8] + ":" + effi_gen[1] + ":" + effi_rec[32] ), //
  // (coll_system + ":" + name[37] + ":" + tree_name[2] + ":" + cut_setting[40] + ":" + "TOFif + pdgEle"   + ":" + effi_name[8] + ":" + effi_gen[1] + ":" + effi_rec[31] ), //

  // 4 Different Shared ITS Cluster settings
  // (coll_system + ":" + name[34] + ":" + tree_name[2] + ":" + cut_setting[37] + ":" + "max 3 Shared Cluster"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[30] ), //
  // (coll_system + ":" + name[34] + ":" + tree_name[2] + ":" + cut_setting[34] + ":" + "max 2 Shared Cluster"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[30] ), //
  // (coll_system + ":" + name[34] + ":" + tree_name[2] + ":" + cut_setting[36] + ":" + "max 1 Shared Cluster"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[30] ), //
  // (coll_system + ":" + name[34] + ":" + tree_name[2] + ":" + cut_setting[35] + ":" + "max 0 Shared Cluster"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[30] ), //
  // "Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV:./input/data_LMEEoutput/LMEEoutput-Patrick.root:reichelt_LMEEPbPb2011_out:cut16_SPDorSDD14_PID16_pt400:PbPb @ 2.76 TeV:./input/paireff/pairEff_raw-1050-pt400_Patrick.root:NGenPairs_pt400_3500:NRecPairs_hEff_Ele_cut16_SPDorSDD14_PID16_pt400_3500",
  // TODO ADD NEW ROOT FILES
("")
};
Int_t n_config = sizeof(cconfig)/sizeof(*cconfig) - 1;

  // cocktail files
TString cocktail_files[] = {
  "./input/cocktail/cocktail-01-kPbPb_276_1020_pt400-24x100x20000.root:./input/cocktail/cocktail-01-kPbPb_276_2030_pt400-24x100x20000.root:./input/cocktail/cocktail-01-kPbPb_276_3040_pt400-24x100x20000.root:./input/cocktail/cocktail-01-kPbPb_276_4050_pt400-24x100x20000.root",
  "./input/cocktail/cocktail_PbPb502_1050.root",
  "./input/cocktail/LF_cocktail_v3.root", // First working cocktail Oton Style
  "./input/cocktail/LF_cocktail_v3_low.root", // First working cocktail Oton Style
  "./input/cocktail/LF_cocktail_v3_high.root", // First working cocktail Oton Style
  ""
};
TString cocktail_list[] = {
  "cocktailPt400rec:cocktailPt400rec:cocktailPt400rec:cocktailPt400rec:cocktailPt400rec",
  "cocktailPt400:cocktailPt400:cocktailPt400:cocktailPt400:cocktailPt400",
  "LMeeCocktailMC/LMeeCocktailMC_pt400",
  ""
};
// cocktail histograms
TString cocktail_histograms[] = {
  "Mee_Ptee_Pion_angleSmeared:Mee_Ptee_Eta_angleSmeared:Mee_Ptee_EtaPrime_angleSmeared:Mee_Ptee_Rho_angleSmeared:Mee_Ptee_Omega_angleSmeared:Mee_Ptee_OmegaDalitz_angleSmeared:Mee_Ptee_Phi_angleSmeared:Mee_Ptee_PhiDalitz_angleSmeared",
  "MeePteePion:MeePteeEta:MeePteeEtaPrime:MeePteeRho:MeePteeOmega:MeePtee:MeePteePhi",
  "pteevsmee_Pi0:pteevsmee_Eta:pteevsmee_EtaPrim:pteevsmee_rho0:pteevsmee_omega:pteevsmee_phi",
  ""
};

// J/Psi files
TString JPsi_files[] = {
   "./input/cocktail/jpsi-PbPb2015_0080-pt400.root", //
   "./input/cocktail/jpsi-PbPb2015_0080-pt400_simple.root", //
   ""
};
TString JPsi_list = "Mee_Ptee_angleSmeared";

TString JPsi_histograms[] = {
   "Mee_Ptee_Jpsi_std_angleSmeared",//"-hMeePtee_LS_eta08_pt400_opAngle50_smeared",
   "Mee_Ptee_Jpsi_low_angleSmeared",//"-hMeePtee_LS_eta08_pt400_opAngle50_smeared",
   "Mee_Ptee_Jpsi_high_angleSmeared",//"-hMeePtee_LS_eta08_pt400_opAngle50_smeared",
   ""
};

// heavy flavour files
TString heavyfl_files[] = {
   "./input/cocktail/charm-PbPb-kPythiaPerugia11_pp5020GeV_Run2-240x40000_unsmeared.root", //
   "./input/cocktail/charm-PbPb-kPythiaPerugia11_pp5020GeV_Run2-240x40000_smeared1050.root:./input/cocktail/beauty-PbPb-kPythiaPerugia11_pp5020GeV_Run2-960x40000_smeared1050.root",
   "./input/cocktail/cocktail_charm.root:./input/cocktail/beauty-PbPb-kPythiaPerugia11_pp5020GeV_Run2-960x40000_smeared1050.root",
   ""
};
TString heavyfl_list = "lowee:lowee";

TString heavyfl_histograms[] = {
   "hMeePtee_ULS_eta08_pt400",//"-hMeePtee_LS_eta08_pt400_opAngle50_smeared",
   "hMeePtee_ULS_eta08_pt400-hMeePtee_LS_eta08_pt400:hMeePtee_ULS_eta08_pt400-hMeePtee_LS_eta08_pt400",
   ""
};

TString heavyfl_hist_Nevents[] = { // always synchronize with 'heavyfl_histograms'.
   "hRapCharmQuarkMethod1",//"hNEvents",
   "hRapCharmQuarkMethod1:hRapBeautyQuarkMethod1",
   ""
};

Int_t   which_cockt_files = 2; // New Cocktail couple ;) Event
Int_t   which_cockt_list  = 2;
Int_t   which_cockt_hists = 2;

Int_t   which_cockt_files_low  = 3; // New Cocktail couple ;) Event
Int_t   which_cockt_files_high = 4; // New Cocktail couple ;) Event

Int_t   which_JPsi_files = 1;
Int_t   which_JPsi_hists = 0;

Int_t   which_heavyfl_files = 2;
Int_t   which_heavyfl_hists = 1;

//__________________________________________________________________________________________________________
// Binning for data
std::vector<double> mee_bins;
std::vector<double> ptee_bins;
std::vector<double> mee_bin_LookingAtMee{
  0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14,// Realistic binningLHC15o
  0.22, 0.30, 0.46, 0.66, 0.74, 0.86, 0.98, 1.1, 1.30,
  1.70, 2.30, 2.70, 2.90, 3.10, 3.30, 4.00, 5.00
};
std::vector<double> ptee_bin_LookingAtMee{
  0.0, 0.5, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5,
  1.6, 1.7, 1.8, 1.9, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0,
  3.2, 3.4, 3.6, 3.8, 4.0, 4.5, 5.0, 8.0
};
// std::vector<double> ptee_bin_LookingAtMee{
//   0.0, 8.0
// };

std::vector<double> mee_bin_LookingAtPtee{
  0.00, 0.14, 0.74, 1.1, 2.9, 3.3, 5.0
};
std::vector<double> ptee_bin_LookingAtPtee{
    0.0, 0.05, 0.10, 0.15, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, // Binning for first shots on LHC15o
    1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6,
    3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 8.
};

// Special binning
std::vector<double> ptee_bin_LookingAtPtee_0_140{
    0.0, 0.05, 0.10, 0.15, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, // Binning for first shots on LHC15o
    1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6,
    3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 8.
};
std::vector<double> ptee_bin_LookingAtPtee_140_740{
  0.0, 0.4, 0.7, 0.9,  // Binning for first shots on LHC15o
  1.2, 1.6, 2.0, 2.4, 2.8, 3.2, 3.6,
  4.0, 5.0, 8.
};
std::vector<double> ptee_bin_LookingAtPtee_740_1100{
    0.0, 0.3, 0.5, 0.7, 0.9,  // Binning for first shots on LHC15o
    1.2, 1.6, 2.0, 2.4, 2.8, 3.2, 3.6,
    4.0, 5.0, 8.
};
std::vector<double> ptee_bin_LookingAtPtee_1100_2900{
    0.0, 0.2, 0.4, 0.6, 0.8,
    1.0, 1.2, 1.4, 1.6, 1.8,
    2.0, 2.4, 2.8, 3.2, 3.6,
    4.0, 5.0, 8.
};
std::vector<double> ptee_bin_LookingAtPtee_2900_3300{
    0.0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.2, 3.6, 3.8, 4.0, 5.0, 8.
};
std::vector<double> ptee_bin_LookingAtPtee_3300_5000{
    0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 8.
};


// Double_t mee_bin[] = {
//   0.00, 0.02, 0.04, 0.06, 0.10, 0.14,// Realistic binningLHC15o
//   0.22, 0.30, 0.46, 0.66, 0.74, 0.86, 0.98, 1.1, 1.30,
//   1.70, 2.30, 2.70, 2.90, 3.10, 3.30, 4.00, 5.00
// };
// Double_t mee_bin[] = {
//   0.00, 0.02, 0.04, 0.06, 0.10, 0.14, // Coarse Binning to reduce fluctuations
//   0.22, 0.30, 0.46, 0.74, 1.1, 1.7, 2.90, 3.10, 3.30, 4.00, 5.00
// };

// Double_t mee_bin[] = { // Fine binning for ULS-LS plots
//                        0.00, 0.10, 0.20, 0.30, 0.40,
//                        0.50, 0.60, 0.70, 0.80, 0.90,
//                        1.00, 1.10, 1.20, 1.30, 1.40,
//                        1.50, 1.60, 1.70, 1.80, 1.90,
//                        2.00, 2.10, 2.20, 2.30, 2.40,
//                        2.50, 2.60, 2.70, 2.80, 2.90,
//                        3.00, 3.10, 3.20, 3.30, 3.40,
//                        3.50, 3.60, 3.70, 3.80, 3.90,
//                        4.00, 4.10, 4.20, 4.30, 4.40,
//                        4.50, 4.60, 4.70, 4.80, 4.90,
//                        5.00
// };
// Double_t mee_bin[] = { // R-Factor
//   0.00, 0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45,
//                                               0.50, 0.55, 0.60, 0.65, 0.70, 0.75, 0.80, 0.85, 0.90, 0.95,
//                                               1.00, 1.05, 1.10, 1.15, 1.20, 1.25, 1.30, 1.35, 1.40, 1.45,
//                                               1.50, 1.55, 1.60, 1.65, 1.70, 1.75, 1.80, 1.85, 1.90, 1.95,
//                                               2.00, 2.05, 2.10, 2.15, 2.20, 2.25, 2.30, 2.35, 2.40, 2.45,
//                                               2.50, 2.55, 2.60, 2.65, 2.70, 2.75, 2.80, 2.85, 2.90, 2.95,
//                                               3.00, 3.05, 3.10, 3.15, 3.20, 3.25, 3.30, 3.35, 3.40, 3.45,
//                                               3.50, 3.55, 3.60, 3.65, 3.70, 3.75, 3.80, 3.85, 3.90, 3.95,
//                                               4.00, 4.05, 4.10, 4.15, 4.20, 4.25, 4.30, 4.35, 4.40, 4.45,
//                                               4.50, 4.55, 4.60, 4.65, 4.70, 4.75, 4.80, 4.85, 4.90, 4.95,
//                                               5.00
// };

// Double_t ptee_bin[] = {
//   0.0, 0.05, 0.10, 0.15, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, // Binning for first shots on LHC15o
//   1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6,
//   3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 8.
// };

// desired binning for cocktail.
// may be much finer than for data, but the bin edges should overlap to avoid inconsistencies when doing projections!
// Double_t mee_bin_cocktail[] = {
//   0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38, 0.40, 0.42, 0.44, 0.46, 0.48,
//   0.50, 0.52, 0.54, 0.56, 0.58, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.72, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98,
//   1.00, 1.02, 1.04, 1.06, 1.08, 1.10, 1.12, 1.14, 1.16, 1.18, 1.20,
//   1.30, 1.40, 1.50, 1.60, 1.70, 1.80, 1.90, 2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 3.00, 3.10, 3.20, 3.30, 3.40, 3.50, 3.60, 3.70, 3.80, 3.90,
//   4.00, 4.10, 4.20, 4.30, 4.40, 4.50, 4.60, 4.70, 4.80, 4.90, 5.00
// };
Double_t mee_bin_cocktail[] = {
  0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38, 0.40, 0.42, 0.44, 0.46, 0.48,
  0.50, 0.52, 0.54, 0.56, 0.58, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.72, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98,
  1.00, 1.02, 1.04, 1.06, 1.08, 1.10, 1.12, 1.14, 1.16, 1.18, 1.20,
  1.30, 1.40, 1.50, 1.60, 1.70, 1.80, 1.90, 2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 3.00, 3.10, 3.20, 3.30, 3.40, 3.50, 3.60, 3.70, 3.80, 3.90,
  4.00, 4.10, 4.20, 4.30, 4.40, 4.50, 4.60, 4.70, 4.80, 4.90, 5.00
};
// Double_t mee_bin_cocktail[] = {
//   0.00, 5.00
// };
// Double_t ptee_bin_cocktail[] = {
//   0.0, 2.0, 4.0, 8.
// };
Double_t ptee_bin_cocktail[] = {
  0.0, 0.05, 0.10, 0.15, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, // Binning for first shots on LHC15o
  1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6,
  3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 8.
};
Int_t n_mee_bin_cocktail = sizeof(mee_bin_cocktail)/sizeof(*mee_bin_cocktail) -1;
Int_t n_ptee_bin_cocktail = sizeof(ptee_bin_cocktail)/sizeof(*ptee_bin_cocktail) -1;

// systematic
// bin edges must match with the projection bins of the final data handler!
// Double_t mee_bin_systematic[] = { 0.0, 0.14, 5.0 };
// Double_t mee_bin_systematic[] = { 0.0, 0.14, 1.1, 2.7, 3.3, 5.0 };
Double_t mee_bin_systematic[] = { 0.0, 0.14, 5.0 };
// Double_t mee_bin_systematic[] = {
//   0.00, 0.02, 0.04, 0.06, 0.10, 0.14, // Realistic binningLHC15o
//   0.22, 0.30, 0.46, 0.74, 0.86, 1.1, 1.30,
//   1.70, 2.30, 2.70, 2.90, 3.10, 3.30, 4.00, 5.00
// };
// Double_t ptee_bin_systematic[] = { 0.0, 1., 2., 3., 4., 5.0};
Double_t ptee_bin_systematic[] = { 0.0, 8.0};
Int_t n_mee_bin_systematic = sizeof(mee_bin_systematic)/sizeof(*mee_bin_systematic) -1;
Int_t n_ptee_bin_systematic = sizeof(ptee_bin_systematic)/sizeof(*ptee_bin_systematic) -1;

//__________________________________________________________________________________________________________
// PhiV-cut that shall be applied
// to disable, it's most efficient to call mgr.SetEnableExclusionCutZ(kFALSE);
//Double_t cutValPhiV = 3./4.*TMath::Pi();
//Double_t cutValMee = 0.10;
Double_t cutPhiVbelow[] = { 0,                 0};
Double_t cutPhiVabove[] = { 2./4.*TMath::Pi(), 6./8.*TMath::Pi()};
Double_t cutEdgesMee[]  = { 0.02,              0.10 };
Int_t    n_cutPhiVbelow = sizeof(cutPhiVbelow)/sizeof(*cutPhiVbelow);
Int_t    n_cutPhiVabove = sizeof(cutPhiVabove)/sizeof(*cutPhiVabove);
Int_t    n_cutEdgesMee  = sizeof(cutEdgesMee)/sizeof(*cutEdgesMee);


//_______________________________________________________________________________________________
// more global variables
std::vector<Double_t> binsPtee_forMee, binsPtee_forMee_sys;
std::vector<Double_t> binsMee_forPtee, binsMee_forPtee_sys;

//Bool_t  kDoPref, kDoNoPref;
Bool_t  plotAverage, plotWeightAv;
// files
TString filename2D_sys, filename2D_ana;
TString extpath_sys, extpath_ana;


void ProcessCocktail(LmCocktail* cockt00);
void ProcessInputfiles(LmHandler* han_sys, LmHandler* han_ana);
void ProcessSingleInputs(TString config[], TString effiName,
                         std::vector<LmManager*> &mgrVec,     std::vector<LmBackground*> &bkgVec,     std::vector<LmSignal*> &sigVec,
                         std::vector<LmManager*> &mgrVec_sys, std::vector<LmBackground*> &bkgVec_sys, std::vector<LmSignal*> &sigVec_sys);
void ProcessCombineHandlers(std::vector<LmSignal*> &sigVec, std::vector<LmHandler*> &hanVec, Bool_t doPlots,
                            std::vector<Double_t> binsPtee_forMee, std::vector<Double_t> binsMee_forPtee,
                            Double_t plotMeeMin, Double_t plotMeeMax, Double_t plotPteeMin, Double_t plotPteeMax);
LmCocktail* ProcessCocktail();
