
#include <vector>
#include "TMath.h"
#include "TString.h"
#include "TBenchmark.h"
#include "TSystem.h"

#include "LmCocktail.h"
#include "LmHandler.h"
#include "LmFileManager.h"

enum kCent{kCent0080, kCent0010, kCent1020, kCent2040, kCent4050, kCent5060, kCent6080, kCent1050, kCent5080, kCent0020, kCent4080};

Bool_t    kDo200MeV         = kTRUE;
// Int_t     kCentrality       = kCent::kCent0010;
Int_t     kCentrality       = kCent::kCent0020;
// Int_t     kCentrality       = kCent::kCent2040;
// Int_t     kCentrality       = kCent::kCent4080;
// Int_t     kCentrality       = kCent::kCent0080;

Bool_t    kDoSystematics    = kTRUE;
Bool_t    kDoOwnSystematics = kTRUE;

Bool_t    kDoCombineHandler = kTRUE;
Bool_t    kDoCompareHandler = kTRUE;

// UInt_t    kDoPhiV = LmManager::kTemplSub;
UInt_t    kDoPhiV = LmManager::kNoCut;
// UInt_t    kDoPhiV = LmManager::kDoCut;
// UInt_t    kDoPhiV = LmManager::kFlatCorrSub;

Bool_t    kDoSignifRaw      = kFALSE;

Bool_t    kUseRFactor       = kTRUE;

Bool_t    kDoNormNevents    = kTRUE;
Bool_t    kDoNormBinwidth   = kTRUE;

// Bool_t    kDoEffiCorrection = kTRUE;
Bool_t    kDoEffiCorrection = kTRUE;

Bool_t    kDoConfLevel      = kFALSE;
Double_t  confLevel         = 0.84;

Bool_t    kDoRatio          = kTRUE;

Bool_t    kDoCocktail       = kTRUE;
Bool_t    kDoCocktailOnly   = kFALSE;

Bool_t    kDoReadFromRootFile = kFALSE;
Int_t     debug             = 0;

TString name[] = {
   "./input/data_LMEEoutput/LMEEoutput-347-1full.root",  // 1 QM 2014 setting, 400 MeV single leg pt cut. From Patricks LEGO train
   "./input/data_LMEEoutput/LMEEoutput_100Chunks_woPID.root", // LHC15o lowInt no PID
   "./input/data_LMEEoutput/LMEEoutput_LHC15o_lowIR_ITSSA.root", // lowInt ITSSA
   "", "", "", "", "", "", "", "", "", "./input/data_LMEEoutput/LMEEoutput-cut16-semi-1full.root", // LHC11h with opening angle cut
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
   "./input/data_LMEEoutput/LMEEoutput_MC_PHIV_v2.root", // 35: MC AOD to check differences in efficiency calculation
   "./input/data_LMEEoutput/LMEEoutput_MCTruth.root", // 36: MC truth. compatible to 35
   "./input/data_LMEEoutput/LMEEoutput_20cuts_ITSSMap.root", // 37: 20 cut settings, all with ITS S Map cut
   "./input/data_LMEEoutput/LMEEoutput_20cuts_ITSSMAP_lowIR.root", // 38: 20 cut settings, all with ITS S Map cut, only lowIR
   "./input/data_LMEEoutput/LMEEoutput_woSC_wSC_wSM.root", // 39: MC with shared cluster, shared map and without conv rejection
   "./input/data_LMEEoutput/LMEEoutput_MCClosureTest.root", // 40: MCClosure Test
   "./input/data_LMEEoutput/LMEEoutput_MCClosureTest2.root", // 41: MCClosure Test
   "./input/data_LMEEoutput/LMEEoutput_MCClosureTest2_ESD.root", // 42: MCClosure Test ESD
   "./input/data_LMEEoutput/LMEEoutput_AOD_lowInt.root", // 43: MCClosure Test ESD
   "./input/data_LMEEoutput/LMEEoutput_AOD_pass1.root", // 44: MCClosure Test ESD
   "./input/data_LMEEoutput/LMEEoutput_AOD_pass1_pidfix.root", // 45: MCClosure Test ESD
   "./input/data_LMEEoutput/LMEEoutput_ESD_lowInt.root", // 46: MCClosure Test ESD
   "./input/data_LMEEoutput/LMEEoutput_ESD_pass1.root", // 47: MCClosure Test ESD
   "./input/data_LMEEoutput/LMEEoutput_ESD_pass1_pidfix.root", // 48: MCClosure Test ESD
   "./input/data_LMEEoutput/LMEEoutput_AOD.root", // 49: MCClosure Test AOD, all periods merged
   "./input/data_LMEEoutput/LMEEoutput_ESD.root", // 50: MCClosure Test ESD, all periods merged
   "./input/data_LMEEoutput/LMEEoutput_noTrackCuts.root", // 51 sample with no track cuts for QA
   "./input/data_LMEEoutput/LMEEoutput_c20_LEGO1087_27012018.root", // 52 20cuts 27.01.2018
   "./input/data_LMEEoutput/LMEEoutput_c20_LEGO_1108-1110_07032018.root", // 53 20 cuts pt200 07.03.2018
   "./input/data_LMEEoutput/LMEEoutput_c1_10_LEGO_1116_08032018.root", // 54 1-10 cuts pt200 08.03.2018
   "./input/data_LMEEoutput/LMEEoutput_c5_centrality_LEGO_1124_13032018.root", // 55 cut 5 centralities with pt200 and pt400 13.03.2018

   "./input/data_LMEEoutput/centrality/LMEEoutput_c5_LEGO1124_13032018_0080.root", // 56 cut 5 centralities with pt200
   "./input/data_LMEEoutput/centrality/LMEEoutput_c5_LEGO1124_13032018_0010.root", // 57 cut 5 centralities with pt200
   "./input/data_LMEEoutput/centrality/LMEEoutput_c5_LEGO1124_13032018_1050.root", // 58 cut 5 centralities with pt200
   "./input/data_LMEEoutput/centrality/LMEEoutput_c5_LEGO1124_13032018_5080.root", // 59 cut 5 centralities with pt200
   "./input/data_LMEEoutput/centrality/LMEEoutput_c5_LEGO1124_13032018_0020.root", // 60 cut 5 centralities with pt200
   "./input/data_LMEEoutput/centrality/LMEEoutput_c5_LEGO1124_13032018_2040.root", // 61 cut 5 centralities with pt200
   "./input/data_LMEEoutput/centrality/LMEEoutput_c5_LEGO1124_13032018_4080.root", // 62 cut 5 centralities with pt200

   "./input/data_LMEEoutput/LHC18b5a_cut5/LMEEoutput.root", // 63 MC LHC18g5a cut5 pt200

   "./input/data_LMEEoutput/LMEEoutput_c20_LEGO1144_17042018_0080.root", // 64, pt200, cut 1-20, 19.04

   "./input/data_LMEEoutput/LEGO_1147_c20/LMEEoutput_c1-10.root", // 65 cut 5 centralities with pt200
   "./input/data_LMEEoutput/LEGO_1150_c3/LMEEoutput.root", // 66 cut 5 centralities with pt200

   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_0010.root", // 67 cut 5 with woSC and loosePionRej centralities with pt200
   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_1020.root", // 68 cut 5 with woSC and loosePionRej centralities with pt200
   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_2030.root", // 69 cut 5 with woSC and loosePionRej centralities with pt200
   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_3040.root", // 70 cut 5 with woSC and loosePionRej centralities with pt200
   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_4050.root", // 71 cut 5 with woSC and loosePionRej centralities with pt200
   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_5060.root", // 72 cut 5 with woSC and loosePionRej centralities with pt200
   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_6070.root", // 73 cut 5 with woSC and loosePionRej centralities with pt200
   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_7080.root", // 74 cut 5 with woSC and loosePionRej centralities with pt200
   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_8090.root", // 75 cut 5 with woSC and loosePionRej centralities with pt200

   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_0020.root", // 76 cut 5 with woSC and loosePionRej centralities with pt200
   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_2040.root", // 77 cut 5 with woSC and loosePionRej centralities with pt200
   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_4080.root", // 78 cut 5 with woSC and loosePionRej centralities with pt200

   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_0020.root", // 76 cut 5 with woSC and loosePionRej centralities with pt200
   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_2040.root", // 77 cut 5 with woSC and loosePionRej centralities with pt200
   "./input/data_LMEEoutput/LEGO_1160/LMEEoutput_4080.root", // 78 cut 5 with woSC and loosePionRej centralities with pt200

   "./input/data_LMEEoutput/LEGO_1165/LMEEoutput_0020.root", // 79 cut 5 with woSC and loosePionRej centralities with pt200, ITS/TPC/TOF wrongly recalibrated
   "./input/data_LMEEoutput/LEGO_1165/LMEEoutput_2040.root", // 80 cut 5 with woSC and loosePionRej centralities with pt200, ITS/TPC/TOF wrongly recalibrated
   "./input/data_LMEEoutput/LEGO_1165/LMEEoutput_4080.root", // 81 cut 5 with woSC and loosePionRej centralities with pt200, ITS/TPC/TOF wrongly recalibrated

   "./input/data_LMEEoutput/LEGO_1166/LMEEoutput_0020.root", // 82 cut 5 with woSC and loosePionRej centralities with pt200, ITS/TPC/TOF recalibrated
   ""
   };

TString tree_name[] = {
  "caklein_LMEEPbPb_out",
  "reichelt_LMEEPbPb2011_out",
  "caklein_LMEEPbPb_out1",
  "caklein_LMEEPbPb_out2",
  "caklein_LMEEPbPb_out0",
  "caklein_LMEEPbPb_out3",

  "caklein_LMEEPbPb_out4",
  "caklein_LMEEPbPb_out5",
  "caklein_LMEEPbPb_out6",
  "caklein_LMEEPbPb_out7",
  "caklein_LMEEPbPb_out8",
  "caklein_LMEEPbPb_out9",
  "caklein_LMEEPbPb_out10", //12 0010
  "caklein_LMEEPbPb_out11", //13 1020
  "caklein_LMEEPbPb_out12", //14 2030
  "caklein_LMEEPbPb_out13", //15 3040
  "caklein_LMEEPbPb_out14", //16 4050
  "caklein_LMEEPbPb_out15", //17 5060
  "caklein_LMEEPbPb_out16", //18 6070
  "caklein_LMEEPbPb_out17", //19 7080
  "caklein_LMEEPbPb_out18", //20 8090
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
  "kPbPb2015_Pt400_PID_cutoff_pion_kaon_proton", // 09
  "kPbPb2015_Pt400_tightTOFif_semi", //10
  "kPbPb2015_Pt400_looseTOFif_semi", // 11
  "kPbPb2015_Pt400_tightTOFreq_semi", // 12
  "cut0", "cut1", "cut2", "cut3", "cut4", "cut5", "cut6", "cut7", "cut8", "cut9", // 13-22
  "cut10", "cut11", "cut12", "cut13", "cut14", "cut15", "cut16", "cut17", "cut18", "cut19", // 23-32
  "cut20",
  "cut11_Version1", "cut11_0SITSCl_Version1", "cut11_1SITSCl_Version1", "cut11_3SITSCl_Version1", //34-37
  "kPbPb2015_Pt400_looseTOFif_MB", //38
  "kPbPb2015_Pt400_tightTOFreq_MB", // 39
  "kPbPb2015_Pt400_looseTOFif_MB_Track3", //40
  "kPbPb2015_Pt400_tightTOFreq_MB_Track3", // 41
  "kPbPb2015_Pt400_PID_cutoff_pion_kaon_proton_Track3", // 42
  "kPbPb2015_Pt400_looseTOFif_MB_PDGCodeElectron", //43
  "kPbPb2015_Pt400_tightTOFreq_MB_PDGCodeElectron", // 44
  "kPbPb2015_Pt400_PID_cutoff_pion_kaon_proton_PDGCodeElectron", // 45
  "kPbPb2015_Pt400_looseTOFif_MB_noConversion", //46
  "kPbPb2015_Pt400_tightTOFreq_MB_noConversion", // 47
  "kPbPb2015_Pt400_PID_cutoff_pion_kaon_proton_noConversion", // 48
  "kPbPb2015_Pt200_PID_cutoff_pion_kaon_proton", // 49
  "cut5_pt200_looserPionRejection", // 50
  "cut5_pt200_looserPionRejection_woSCcut", // 51
  ""
};
TString cuts[] = {
  "cut0", "cut1", "cut2", "cut3", "cut4", "cut5", "cut6", "cut7", "cut8", "cut9", // 0
  "cut10", "cut11", "cut12", "cut13", "cut14", "cut15", "cut16", "cut17", "cut18", "cut19",
  "cut20"
};
TString cuts400[] = {
  "cut0_pt400", "cut1_pt400", "cut2_pt400", "cut3_pt400", "cut4_pt400", "cut5_pt400", "cut6_pt400", "cut7_pt400", "cut8_pt400", "cut9_pt400", // 0
  "cut10_pt400", "cut11_pt400", "cut12_pt400", "cut13_pt400", "cut14_pt400", "cut15_pt400", "cut16_pt400", "cut17_pt400", "cut18_pt400", "cut19_pt400",
  "cut20_pt400"
};
TString cuts200[] = {
  "cut0_pt200", "cut1_pt200", "cut2_pt200", "cut3_pt200", "cut4_pt200", "cut5_pt200", "cut6_pt200", "cut7_pt200", "cut8_pt200", "cut9_pt200", // 0
  "cut10_pt200", "cut11_pt200", "cut12_pt200", "cut13_pt200", "cut14_pt200", "cut15_pt200", "cut16_pt200", "cut17_pt200", "cut18_pt200", "cut19_pt200",
  "cut20_pt200",
  "cut1_pt200_TOFreq", "cut2_pt200_TOFreq", "cut3_pt200_TOFreq", "cut4_pt200_TOFreq", "cut5_pt200_TOFreq", "cut6_pt200_TOFreq", "cut7_pt200_TOFreq", "cut8_pt200_TOFreq", "cut9_pt200_TOFreq", // 0
  "cut10_pt200_TOFreq", "cut11_pt200_TOFreq", "cut12_pt200_TOFreq", "cut13_pt200_TOFreq", "cut14_pt200_TOFreq", "cut15_pt200_TOFreq", "cut16_pt200_TOFreq", "cut17_pt200_TOFreq", "cut18_pt200_TOFreq", "cut19_pt200_TOFreq",
  "cut20_pt200_TOFreq",
};
TString cuts200_woSCcut[] = {
  "cut0_pt200_woSCcut", "cut1_pt200_woSCcut", "cut2_pt200_woSCcut", "cut3_pt200_woSCcut", "cut4_pt200_woSCcut", "cut5_pt200_woSCcut", "cut6_pt200_woSCcut", "cut7_pt200_woSCcut", "cut8_pt200_woSCcut", "cut9_pt200_woSCcut", // 0
  "cut10_pt200_woSCcut", "cut11_pt200_woSCcut", "cut12_pt200_woSCcut", "cut13_pt200_woSCcut", "cut14_pt200_woSCcut", "cut15_pt200_woSCcut", "cut16_pt200_woSCcut", "cut17_pt200_woSCcut", "cut18_pt200_woSCcut", "cut19_pt200_woSCcut",
  "cut20_pt200_woSCcut"
};
TString coll_system = "Pb#minus Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV";
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
   "./input/paireff/pairefficiency_pt400_v5_wITSSMAP.root", // [9]
   "./input/paireff/Efficiency_MC_Closure.root", // [10]
   "./input/paireff/Efficiency_MC_Closure2.root", // [11]
   "./input/paireff/pairefficiency_pt400_27012018_c20.root", // [12]
   "./input/paireff/pairefficiency_pt200_07032018_c20.root", // [13]
   "./input/paireff/pairefficiency_pt200_c5_0010.root", // [14]

   "./input/paireff/centrality/pairefficiency_pt200_c5_0080.root", // [15]
   "./input/paireff/centrality/pairefficiency_pt200_c5_0010.root", // [16]
   "./input/paireff/centrality/pairefficiency_pt200_c5_1050.root", // [17]
   "./input/paireff/centrality/pairefficiency_pt200_c5_5080.root", // [18]

   "./input/paireff/centrality/pairefficiency_pt200_c5_0020.root", // [19]
   "./input/paireff/centrality/pairefficiency_pt200_c5_2040.root", // [20]
   "./input/paireff/centrality/pairefficiency_pt200_c5_4080.root", // [21]
   "./input/paireff/centrality/pairefficiency_pt200_c5_1020.root", // [22]
   "./input/paireff/centrality/pairefficiency_pt200_c5_4050.root", // [23]
   "./input/paireff/centrality/pairefficiency_pt200_c5_5060.root", // [24]
   "./input/paireff/centrality/pairefficiency_pt200_c5_6080.root", // [25]

   "./input/paireff/pairefficiency_pt400_v3_c1.root", // [26]

   "./input/paireff/centralities_injected_c5/pairefficiency_pt200_c5_0020.root", // [27]
   "./input/paireff/centralities_injected_c5/pairefficiency_pt200_c5_2040.root", // [28]
   "./input/paireff/centralities_injected_c5/pairefficiency_pt200_c5_4080.root", // [29]
   "./input/paireff/centralities_injected_c5/pairefficiency_pt200_c5_0080.root", // [30]

   "./input/paireff/centralities_injected_c5/pair_eff_c5_injected_0020.root",    // [31]
   "./input/paireff/centralities_injected_c5/pair_eff_c5_injected_2040.root",    // [32]
   "./input/paireff/centralities_injected_c5/pair_eff_c5_injected_4080.root",    // [33]
   "./input/paireff/centralities_injected_c5/pair_eff_c5_injected_0080.root",    // [34]

   "./input/paireff/centralities_injected_c5/weighted/pair_eff_c5_injected_0080.root",    // [35] first weighted
   "./input/paireff/centralities_injected_c5/weighted/pair_eff_c5_injected_0020.root",    // [36] first weighted
   "./input/paireff/centralities_injected_c5/weighted/pair_eff_c5_injected_2040.root",    // [37] first weighted
   "./input/paireff/centralities_injected_c5/weighted/pair_eff_c5_injected_4080.root",    // [38] first weighted

   "./input/paireff/centralities_injected_c5/weighted_smoothed/pair_eff_c5_injected_0080.root",    // [39] weighted + smoothed
   "./input/paireff/centralities_injected_c5/weighted_smoothed/pair_eff_c5_injected_0020.root",    // [40] weighted + smoothed
   "./input/paireff/centralities_injected_c5/weighted_smoothed/pair_eff_c5_injected_2040.root",    // [41] weighted + smoothed
   "./input/paireff/centralities_injected_c5/weighted_smoothed/pair_eff_c5_injected_4080.root",    // [42] weighted + smoothed

   "./input/paireff/LHC18b5a_smoothed_weighted/pair_eff_c5_injected_0080.root",    // [43] weighted + smoothed
   "./input/paireff/LHC18b5a_smoothed_weighted/pair_eff_c5_injected_0020.root",    // [44] weighted + smoothed
   "./input/paireff/LHC18b5a_smoothed_weighted/pair_eff_c5_injected_2040.root",    // [45] weighted + smoothed
   "./input/paireff/LHC18b5a_smoothed_weighted/pair_eff_c5_injected_4080.root",    // [46] weighted + smoothed

   "./input/paireff/LHC18b5a_smoothed_weighted/pair_eff_c1-10_injected_0080_woSCcut.root",    // [47] weighted + smoothed + woSCcut
   "./input/paireff/LHC18b5a_smoothed_weighted/pair_eff_c11-20_injected_0080_woSCcut.root",    // [48] weighted + smoothed + woSCcut

   "./input/paireff/LHC18b5a_smoothed_weighted/pair_eff_c5_injected_0080_generated.root",    // [49] weighted + smoothed + generated (not smeared)
   "./input/paireff/LHC18b5a_LEGO456/pair_eff_c1-10_injected_0080.root",    // [50] LEGO456, matches name[65]
   "./input/paireff/LHC18b5a_LEGO456/pair_eff_c11-20_injected_0080.root",    // [51] LEGO456, matches name[65]

   "./input/paireff/LHC18b5a_LEGO_370_ESD/AnalysisResults.root",    // [52] LEGO370ESD, matches name[65]
   "./input/paireff/LHC18b5a_LEGO_370_ESD/pair_eff_c5_injected_0080.root",    // [53] LEGO370ESD, matches name[65]

   "./input/paireff/LHC18b5a_weighting_v2/pair_eff_c5_injected_0080.root",    // [54] new weighting method for cut 5
   "./input/paireff/001_LHC18b5a_Reweighting_3settings/pair_eff_c5_injected_0080_reweighted.root",    // [55] new weighting method for cut 5

   "./input/paireff/centralities_LHC491/pair_eff_cut5_0010.root",    // [56]
   "./input/paireff/centralities_LHC491/pair_eff_cut5_0020.root",    // [57]
   "./input/paireff/centralities_LHC491/pair_eff_cut5_2040.root",    // [58]
   "./input/paireff/centralities_LHC491/pair_eff_cut5_4080.root",    // [59]

   "./input/paireff/centralities_LEGO500/paireff_summed_and_smoothed.root",    // [60]
  ""
};
  // name of 2D generated and reconstructed histogram
TString effi_gen[] = {
   "hNGenPairs_pt400",
   "NGenPairs_pt400_8000",
   "NGenPairs_pt400_3500_opAngle50",
   "NGenPairs_pt400_3500_opAngle50",
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NgenPairsRecResonances", // 4
   "NGenPairs_pt200_8000",
   "Ngen_sameMother", // 6
   "Ngen_cut5_pt200", // 7
   "Ngen_2_", // 8
   "Ngen_regions", // 9
   "GenSum", // 10
   "Ngen_sameMother", // 11
   "Ngen_ULS_eleFinalStateFromD", // 12
   "Ngen_ULS_eleFinalState", // 13
   "SumGen", //14
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
   "NRecPairs_hEff_Ele_cut1_pt400_8000", "NRecPairs_hEff_Ele_cut2_pt400_8000", "NRecPairs_hEff_Ele_cut3_pt400_8000", "NRecPairs_hEff_Ele_cut4_pt400_8000",
   "NRecPairs_hEff_Ele_cut5_pt400_8000", "NRecPairs_hEff_Ele_cut6_pt400_8000", "NRecPairs_hEff_Ele_cut7_pt400_8000", "NRecPairs_hEff_Ele_cut8_pt400_8000",
   "NRecPairs_hEff_Ele_cut9_pt400_8000", "NRecPairs_hEff_Ele_cut10_pt400_8000","NRecPairs_hEff_Ele_cut11_pt400_8000","NRecPairs_hEff_Ele_cut12_pt400_8000",
   "NRecPairs_hEff_Ele_cut13_pt400_8000","NRecPairs_hEff_Ele_cut14_pt400_8000","NRecPairs_hEff_Ele_cut15_pt400_8000","NRecPairs_hEff_Ele_cut16_pt400_8000",
   "NRecPairs_hEff_Ele_cut17_pt400_8000","NRecPairs_hEff_Ele_cut18_pt400_8000","NRecPairs_hEff_Ele_cut19_pt400_8000","NRecPairs_hEff_Ele_cut20_pt400_8000",
   "NRecPairs_hEff_Ele_kPbPb2015_Pt400_looseTOFif_MB_pt400_8000", //31
   "NRecPairs_hEff_Ele_kPbPb2015_Pt400_tightTOFreq_MB_pt400_8000", //32
   "NRecPairs_hEff_Ele_kPbPb2015_Pt400_looseTOFif_MB_exclMismatch_pt400_8000", //33
   "NRecPairs_hEff_Ele_kPbPb2015_Pt400_tightTOFreq_MB_exclMismatch_pt400_8000", //34
    "NRecPairs_hEff_Ele_cut1_pt200_pt400_8000", //35
    "NRecPairs_hEff_Ele_cut2_pt200_pt400_8000", "NRecPairs_hEff_Ele_cut3_pt200_pt400_8000", "NRecPairs_hEff_Ele_cut4_pt200_pt400_8000", "NRecPairs_hEff_Ele_cut5_pt200_pt400_8000",
    "NRecPairs_hEff_Ele_cut6_pt200_pt400_8000", "NRecPairs_hEff_Ele_cut7_pt200_pt400_8000", "NRecPairs_hEff_Ele_cut8_pt200_pt400_8000", "NRecPairs_hEff_Ele_cut9_pt200_pt400_8000",
   "NRecPairs_hEff_Ele_cut10_pt200_pt400_8000", "NRecPairs_hEff_Ele_cut11_pt200_pt400_8000","NRecPairs_hEff_Ele_cut12_pt200_pt400_8000","NRecPairs_hEff_Ele_cut13_pt200_pt400_8000",
   "NRecPairs_hEff_Ele_cut14_pt200_pt400_8000", "NRecPairs_hEff_Ele_cut15_pt200_pt400_8000","NRecPairs_hEff_Ele_cut16_pt200_pt400_8000","NRecPairs_hEff_Ele_cut17_pt200_pt400_8000",
   "NRecPairs_hEff_Ele_cut18_pt200_pt400_8000", "NRecPairs_hEff_Ele_cut19_pt200_pt400_8000",
   "NRecPairs_hEff_Ele_cut20_pt200_pt400_8000", // 54
   "NRecPairs_hEff_Ele_kPbPb2015_Pt400_looseTOFif_pt400_8000", //55
   "NRecPairs_hEff_Ele_kPbPb2015_Pt400_tightTOFreq_pt400_8000", //56
   "NRecPairs_hEff_Ele_NewPID_pt400_8000", //57
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_kPbPb2015_Pt400_looseTOFif", //58
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_kPbPb2015_Pt400_tightTOFreq", //59
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_NewPID", //60
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_kPbPb2015_Pt400_looseTOFif_Track3", //61
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_kPbPb2015_Pt400_tightTOFreq_Track3", //62
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_kPbPb2015_Pt400_PID_cutoff_pion_kaon_proton_Track3", //63
   "NRecPairs_hEff_cut1_pt400_pt400_8000", //64
   "NRecPairs_hEff_cut2_pt400_pt400_8000", "NRecPairs_hEff_cut3_pt400_pt400_8000", "NRecPairs_hEff_cut4_pt400_pt400_8000","NRecPairs_hEff_cut5_pt400_pt400_8000","NRecPairs_hEff_cut6_pt400_pt400_8000",
   "NRecPairs_hEff_cut7_pt400_pt400_8000", // 70
   "NRecPairs_hEff_cut8_pt400_pt400_8000","NRecPairs_hEff_cut9_pt400_pt400_8000","NRecPairs_hEff_cut10_pt400_pt400_8000","NRecPairs_hEff_cut11_pt400_pt400_8000",
   "NRecPairs_hEff_cut12_pt400_pt400_8000","NRecPairs_hEff_cut13_pt400_pt400_8000","NRecPairs_hEff_cut14_pt400_pt400_8000","NRecPairs_hEff_cut15_pt400_pt400_8000",
   "NRecPairs_hEff_cut16_pt400_pt400_8000", "NRecPairs_hEff_cut17_pt400_pt400_8000", // 80
   "NRecPairs_hEff_cut18_pt400_pt400_8000", "NRecPairs_hEff_cut19_pt400_pt400_8000", "NRecPairs_hEff_cut20_pt400_pt400_8000", // 83

   "NRecPairs_hEff_cut1_pt200_pt200_8000", //84
   "NRecPairs_hEff_cut2_pt200_pt200_8000",
   "NRecPairs_hEff_cut3_pt200_pt200_8000",
   "NRecPairs_hEff_cut4_pt200_pt200_8000",
   "NRecPairs_hEff_cut5_pt200_pt200_8000",
   "NRecPairs_hEff_cut6_pt200_pt200_8000",
   "NRecPairs_hEff_cut7_pt200_pt200_8000", // 90
   "NRecPairs_hEff_cut8_pt200_pt200_8000",
   "NRecPairs_hEff_cut9_pt200_pt200_8000",
   "NRecPairs_hEff_cut10_pt200_pt200_8000",
   "NRecPairs_hEff_cut11_pt200_pt200_8000",
   "NRecPairs_hEff_cut12_pt200_pt200_8000",
   "NRecPairs_hEff_cut13_pt200_pt200_8000",
   "NRecPairs_hEff_cut14_pt200_pt200_8000",
   "NRecPairs_hEff_cut15_pt200_pt200_8000",
   "NRecPairs_hEff_cut16_pt200_pt200_8000",
   "NRecPairs_hEff_cut17_pt200_pt200_8000", // 100
   "NRecPairs_hEff_cut18_pt200_pt200_8000",
   "NRecPairs_hEff_cut19_pt200_pt200_8000",
   "NRecPairs_hEff_cut20_pt200_pt200_8000", // 103
   "Nrec_cut5_pt200_sameMother", // 104
   "Nrec_cut5_pt200", // 105
   "Nrec_2_0", // 106
   "Nrec_regions_cut1_pt200_woSCcut", //107
   "Nrec_regions_cut2_pt200_woSCcut",
   "Nrec_regions_cut3_pt200_woSCcut",
   "Nrec_regions_cut4_pt200_woSCcut",
   "Nrec_regions_cut5_pt200_woSCcut",
   "Nrec_regions_cut6_pt200_woSCcut",
   "Nrec_regions_cut7_pt200_woSCcut",
   "Nrec_regions_cut8_pt200_woSCcut",
   "Nrec_regions_cut9_pt200_woSCcut",
   "Nrec_regions_cut10_pt200_woSCcut",
   "Nrec_regions_cut11_pt200_woSCcut", // 117
   "Nrec_regions_cut12_pt200_woSCcut",
   "Nrec_regions_cut13_pt200_woSCcut",
   "Nrec_regions_cut14_pt200_woSCcut",
   "Nrec_regions_cut15_pt200_woSCcut",
   "Nrec_regions_cut16_pt200_woSCcut",
   "Nrec_regions_cut17_pt200_woSCcut",
   "Nrec_regions_cut18_pt200_woSCcut",
   "Nrec_regions_cut19_pt200_woSCcut",
   "Nrec_regions_cut20_pt200_woSCcut", // 126
    "Nrec_regions_cut1_pt200", //127
    "Nrec_regions_cut2_pt200",
    "Nrec_regions_cut3_pt200",
    "Nrec_regions_cut4_pt200",
    "Nrec_regions_cut5_pt200",
    "Nrec_regions_cut6_pt200",
    "Nrec_regions_cut7_pt200",
    "Nrec_regions_cut8_pt200",
    "Nrec_regions_cut9_pt200",
   "Nrec_regions_cut10_pt200",
   "Nrec_regions_cut11_pt200", // 137
   "Nrec_regions_cut12_pt200",
   "Nrec_regions_cut13_pt200",
   "Nrec_regions_cut14_pt200",
   "Nrec_regions_cut15_pt200",
   "Nrec_regions_cut16_pt200",
   "Nrec_regions_cut17_pt200",
   "Nrec_regions_cut18_pt200",
   "Nrec_regions_cut19_pt200",
   "Nrec_regions_cut20_pt200", // 146
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_cut1_pt200", //147
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_cut2_pt200", //
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_cut3_pt200", //
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_cut4_pt200", //150
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_cut5_pt200", //
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_cut6_pt200", //
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_cut7_pt200", //
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_cut8_pt200", //
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_cut9_pt200", //155
   "cklein_ElectronEfficiency_0/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_cut10_pt200", //156
   "RecSum_cut5_pt200", // 157
   "Nrec_cut5_pt200_sameMother", // 158
   "Nrec_ULS_cut5_pt200_eleFinalStateFromD", // 159
   "Nrec_cut5_pt200_woSCcut_sameMother", // 160
   "Nrec_cut5_pt200_looserPionRejection_sameMother", // 161
   "Nrec_ULS_cut5_pt200_eleFinalState", // 162
   "Nrec_ULS_cut5_pt200_looserPionRejection_eleFinalState", // 163
   "Nrec_ULS_cut5_pt200_looserPionRejection_eleFinalState_woSCcut", // 164
   "Nrec_ULS_cut5_pt200_looserPionRejection_eleFinalState", // 165
   "SumRec", //166
   ""
};

// config string for manager
TString cconfig_pt400[] = { // this determines which settings will really be analysed!
  // ( coll_system + ":" + name[0] + ":" + tree_name[1] + ":" + cut_setting[0] + ":" + "LHC11h pass2 - 20-50%" + ":" + effi_name[0] + ":" + effi_gen[0] + ":" + effi_rec[0] ), // "./input/LMEEoutput-347-1full.root",  // QM 2014 setting, 400 MeV single leg pt cut
  // ( coll_system + ":" + name[12] + ":" + tree_name[1] + ":" + cut_setting[7] + ":" + "LHC11h pass2 - 10-50%" + ":" + effi_name[2] + ":" + effi_gen[2] + ":" + effi_rec[5] ), // "./input/LMEEoutput-347-1full.root",  // QM 2014 setting, 400 MeV single leg pt cut
  // (coll_system + ":" + name[2] + ":" + tree_name[0] + ":" + cut_setting[2] + ":" + "LHC15o - ITSSA" + ":" + effi_name[0] + ":" + effi_gen[0] + ":" + effi_rec[0] ), //

  // (coll_system + ":" + name[55] + ":" + tree_name[6] + ":" + cuts400[5]  +  ":" + "cut5 pt400 - 00-10%"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[68] ), //
  // (coll_system + ":" + name[55] + ":" + tree_name[7] + ":" + cuts400[5]  +  ":" + "cut5 pt400 - 10-20%"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[68] ), //
  // (coll_system + ":" + name[55] + ":" + tree_name[8] + ":" + cuts400[5]  +  ":" + "cut5 pt400 - 20-40%"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[68] ), //
  // (coll_system + ":" + name[55] + ":" + tree_name[9] + ":" + cuts400[5]  +  ":" + "cut5 pt400 - 40-50%"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[68] ), //
  // (coll_system + ":" + name[55] + ":" + tree_name[10] + ":" + cuts400[5] +  ":" + "cut5 pt400 - 50-60%"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[68] ), //
  // (coll_system + ":" + name[55] + ":" + tree_name[11] + ":" + cuts400[5] +  ":" + "cut5 pt400 - 60-80%"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[68] ), //


  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[5] +  ":" + "cut5 pt400 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[68] ), //
  // (coll_system + ":" + name[54] + ":" + tree_name[5] + ":" + cuts200[5] +  ":" + "cut5 pt200 - TOFif"  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[88] ), //

  (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[5] +   ":" + "0.4 < #it{p}_{T,e} < 8 GeV/#it{c}"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[68] ), //
  (coll_system + ":" + name[56] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "0.2 < #it{p}_{T,e} < 8 GeV/#it{c}"  + ":" + effi_name[43] + ":" + effi_gen[7] + ":" + effi_rec[105] ), //

  // End of january status
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[1] +  ":" + "cut1 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[64] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[2] +  ":" + "cut2 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[65] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[3] +  ":" + "cut3 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[66] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[4] +  ":" + "cut4 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[67] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[5] +  ":" + "cut5 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[68] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[6] +  ":" + "cut6 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[69] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[7] +  ":" + "cut7 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[70] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[8] +  ":" + "cut8  - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[71] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[9] +  ":" + "cut9  - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[72] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[10] + ":" + "cut10 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[73] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[11] + ":" + "cut11 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[74] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[12] + ":" + "cut12 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[75] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[13] + ":" + "cut13 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[76] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[14] + ":" + "cut14 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[77] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[15] + ":" + "cut15 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[78] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[16] + ":" + "cut16 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[79] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[17] + ":" + "cut17 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[80] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[18] + ":" + "cut18 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[81] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[19] + ":" + "cut19 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[82] ), //
  // (coll_system + ":" + name[52] + ":" + tree_name[5] + ":" + cuts400[20] + ":" + "cut20 - TOFif"  + ":" + effi_name[12] + ":" + effi_gen[1] + ":" + effi_rec[83] ), //
  // //

  // (coll_system + ":" + name[35] + ":" + tree_name[2] + ":" + cut_setting[39] + ":" + "TOFreq - \"standard effi\""  + ":" + effi_name[8] + ":" + effi_gen[1] + ":" + effi_rec[32] ), //
  // (coll_system + ":" + name[35] + ":" + tree_name[2] + ":" + cut_setting[38] + ":" + "TOFif - \"standard effi\""   + ":" + effi_name[8] + ":" + effi_gen[1] + ":" + effi_rec[31] ), //
  // (coll_system + ":" + name[35] + ":" + tree_name[2] + ":" + cut_setting[39] + ":" + "TOFreq - \"Mismatch excluded\""  + ":" + effi_name[8] + ":" + effi_gen[1] + ":" + effi_rec[34] ), //
  // (coll_system + ":" + name[35] + ":" + tree_name[2] + ":" + cut_setting[38] + ":" + "TOFif - \"Mismatch excluded\""   + ":" + effi_name[8] + ":" + effi_gen[1] + ":" + effi_rec[33] ), //
  // (coll_system + ":" + name[36] + ":" + tree_name[2] + ":" + cut_setting[38] + ":" + "MCTruth"   + ":" + effi_name[-1] + ":" + effi_gen[1] + ":" + effi_rec[31] ), //

  // No track cuts applied
  // (coll_system + ":" + name[51] + ":" + tree_name[0] + ":" + cut_setting[8] + ":" + "no cuts applied"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[30] ), //

  // 4 Different Shared ITS Cluster settings
  // (coll_system + ":" + name[34] + ":" + tree_name[2] + ":" + cut_setting[37] + ":" + "max 3 Shared Cluster"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[30] ), //
  // (coll_system + ":" + name[34] + ":" + tree_name[2] + ":" + cut_setting[34] + ":" + "max 2 Shared Cluster"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[30] ), //
  // (coll_system + ":" + name[34] + ":" + tree_name[2] + ":" + cut_setting[36] + ":" + "max 1 Shared Cluster"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[30] ), //
  // (coll_system + ":" + name[34] + ":" + tree_name[2] + ":" + cut_setting[35] + ":" + "max 0 Shared Cluster"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[30] ), //

  // (coll_system + ":" + name[41] + ":" + tree_name[5] + ":" + cut_setting[40] + ":" + "MC TOFif"  + ":" + effi_name[6] + ":" + effi_gen[1] + ":" + effi_rec[30] ), //


  // "Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV:./input/data_LMEEoutput/LMEEoutput-Patrick.root:reichelt_LMEEPbPb2011_out:cut16_SPDorSDD14_PID16_pt400:PbPb @ 2.76 TeV:./input/paireff/pairEff_raw-1050-pt400_Patrick.root:NGenPairs_pt400_3500:NRecPairs_hEff_Ele_cut16_SPDorSDD14_PID16_pt400_3500",
  // TODO ADD NEW ROOT FILES
("")
};

TString cconfig_pt200[] = { // this determines which settings will really be analysed!

  // (coll_system + ":" + name[63] + ":" + tree_name[5] + ":" + "cut5_pt200/Pair_MCpair_sameMother"  +  ":" + "MC, prompt"  + ":" + effi_name[35] + ":" + effi_gen[7] + ":" + effi_rec[105] ), //
  // (coll_system + ":" + name[63] + ":" + tree_name[5] + ":" + "cut5_pt200/Pair_MCpair_sameGamma"   +  ":" + "MC, conv."  + ":" + effi_name[35] + ":" + effi_gen[7] + ":" + effi_rec[105] ), //

  // (coll_system + ":" + name[56] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 00-80%"  + ":" + effi_name[35] + ":" + effi_gen[6] + ":" + effi_rec[104] ), //

  // (coll_system + ":" + name[67] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 00-10%"  + ":" + effi_name[56] + ":" + effi_gen[10] + ":" + effi_rec[157] ), //
  // (coll_system + ":" + name[68] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 00-10%"  + ":" + effi_name[56] + ":" + effi_gen[11] + ":" + effi_rec[158] ), //
  // (coll_system + ":" + name[69] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 10-20%"  + ":" + effi_name[56] + ":" + effi_gen[10] + ":" + effi_rec[157] ), //
  // (coll_system + ":" + name[70] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 20-30%"  + ":" + effi_name[56] + ":" + effi_gen[10] + ":" + effi_rec[157] ), //
  // (coll_system + ":" + name[71] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 30-40%"  + ":" + effi_name[56] + ":" + effi_gen[10] + ":" + effi_rec[157] ), //
  // (coll_system + ":" + name[72] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 40-50%"  + ":" + effi_name[56] + ":" + effi_gen[10] + ":" + effi_rec[157] ), //
  // (coll_system + ":" + name[73] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 50-60%"  + ":" + effi_name[56] + ":" + effi_gen[10] + ":" + effi_rec[157] ), //
  // (coll_system + ":" + name[74] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 60-70%"  + ":" + effi_name[56] + ":" + effi_gen[10] + ":" + effi_rec[157] ), //
  // (coll_system + ":" + name[75] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 70-80%"  + ":" + effi_name[56] + ":" + effi_gen[10] + ":" + effi_rec[157] ), //

  // (coll_system + ":" + name[76] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 effSum- 00-20%"  + ":" + effi_name[57] + ":" + effi_gen[10] + ":" + effi_rec[157] ), //
  // (coll_system + ":" + name[76] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 effSameM- 00-20%"  + ":" + effi_name[57] + ":" + effi_gen[11] + ":" + effi_rec[158] ), //
  // (coll_system + ":" + name[76] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 charm- 00-20%"  + ":" + effi_name[57] + ":" + effi_gen[12] + ":" + effi_rec[159] ), //
  // (coll_system + ":" + name[77] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 20-40%"  + ":" + effi_name[58] + ":" + effi_gen[10] + ":" + effi_rec[157] ), //
  // (coll_system + ":" + name[78] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 40-80%"  + ":" + effi_name[59] + ":" + effi_gen[10] + ":" + effi_rec[157] ), //
  // (coll_system + ":" + name[76] + ":" + tree_name[5] + ":" + cuts200_woSCcut[5]  +  ":" + "cut5_woSCcut effSameM- 00-20%"  + ":" + effi_name[57] + ":" + effi_gen[11] + ":" + effi_rec[160] ), //

  // (coll_system + ":" + name[76] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 ULS- 00-20%"  + ":" + effi_name[57] + ":" + effi_gen[13] + ":" + effi_rec[162] ), //
  // (coll_system + ":" + name[76] + ":" + tree_name[5] + ":" + cut_setting[50]  +  ":" + "cut5 loose pion ULS - 00-20%"  + ":" + effi_name[57] + ":" + effi_gen[13] + ":" + effi_rec[163] ), //
  // (coll_system + ":" + name[76] + ":" + tree_name[5] + ":" + cut_setting[51]  +  ":" + "cut5 loose pion ULS wo SC- 00-20%"  + ":" + effi_name[57] + ":" + effi_gen[13] + ":" + effi_rec[163] ), //
  // (coll_system + ":" + name[76] + ":" + tree_name[5] + ":" + cuts200_woSCcut[5]  +  ":" + "cut5 ULS wo SC- 00-20%"  + ":" + effi_name[57] + ":" + effi_gen[13] + ":" + effi_rec[163] ), //

  (coll_system + ":" + name[82] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 Recalibrated corr 00-20%"  + ":" + effi_name[60] + ":" + effi_gen[14] + ":" + effi_rec[166] ), //
  // (coll_system + ":" + name[79] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 unc corr 00-20%"  + ":" + effi_name[57] + ":" + effi_gen[11] + ":" + effi_rec[158] ), //

    // LHC16g1 based
        // (coll_system + ":" + name[56] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 00-80%"  + ":" + effi_name[15] + ":" + effi_gen[5] + ":" + effi_rec[88] ), //
        // (coll_system + ":" + name[60] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 00-20%"  + ":" + effi_name[27] + ":" + effi_gen[5] + ":" + effi_rec[88] ), //
        // (coll_system + ":" + name[61] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 20-40%"  + ":" + effi_name[28] + ":" + effi_gen[5] + ":" + effi_rec[88] ), //
        // (coll_system + ":" + name[62] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "cut5 pt200 - 40-80%"  + ":" + effi_name[29] + ":" + effi_gen[5] + ":" + effi_rec[88] ), //

        // (coll_system + ":" + name[64] + ":" + tree_name[5] + ":" + cuts200_woSCcut[5] +  ":" + "w/o ITS shared cl. cut"  + ":" + effi_name[47] + ":" + effi_gen[9] + ":" + effi_rec[111] ), //
        // (coll_system + ":" + name[56] + ":" + tree_name[5] + ":" + cuts200[5]         +  ":" + "w/ ITS shared cl. cut"  + ":" + effi_name[43] + ":" + effi_gen[7] + ":" + effi_rec[105] ), //  weighted sum, should be wrong



  // (coll_system + ":" + name[54] + ":" + tree_name[5] + ":" + cuts200[1] +  ":" + "cut1 "  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[84] ), //   ToyMC
  // (coll_system + ":" + name[54] + ":" + tree_name[5] + ":" + cuts200[2] +  ":" + "cut2 "  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[85] ), // ToyMC
  // (coll_system + ":" + name[54] + ":" + tree_name[5] + ":" + cuts200[3] +  ":" + "cut3 "  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[86] ), // ToyMC
  // (coll_system + ":" + name[54] + ":" + tree_name[5] + ":" + cuts200[4] +  ":" + "cut4 "  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[87] ), // ToyMC
  // (coll_system + ":" + name[54] + ":" + tree_name[5] + ":" + cuts200[5] +  ":" + "cut5 "  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[88] ), // ToyMC
  // (coll_system + ":" + name[54] + ":" + tree_name[5] + ":" + cuts200[6] +  ":" + "cut6 "  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[89] ), // ToyMC
  // (coll_system + ":" + name[54] + ":" + tree_name[5] + ":" + cuts200[7] +  ":" + "cut7 "  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[90] ), // ToyMC
  // (coll_system + ":" + name[54] + ":" + tree_name[5] + ":" + cuts200[8] +  ":" + "cut8 "  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[91] ), // ToyMC
  // (coll_system + ":" + name[54] + ":" + tree_name[5] + ":" + cuts200[9] +  ":" + "cut9 "  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[92] ), // ToyMC
  // (coll_system + ":" + name[54] + ":" + tree_name[5] + ":" + cuts200[10] + ":" + "cut10"  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[93] ), // ToyMC
  // (coll_system + ":" + name[53] + ":" + tree_name[5] + ":" + cuts200[11] + ":" + "cut11"  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[94] ), // ToyMC
  // (coll_system + ":" + name[53] + ":" + tree_name[5] + ":" + cuts200[12] + ":" + "cut12"  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[95] ), // ToyMC
  // (coll_system + ":" + name[53] + ":" + tree_name[5] + ":" + cuts200[13] + ":" + "cut13"  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[96] ), // ToyMC
  // (coll_system + ":" + name[53] + ":" + tree_name[5] + ":" + cuts200[14] + ":" + "cut14"  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[97] ), // ToyMC
  // (coll_system + ":" + name[53] + ":" + tree_name[5] + ":" + cuts200[15] + ":" + "cut15"  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[98] ), // ToyMC
  // (coll_system + ":" + name[53] + ":" + tree_name[5] + ":" + cuts200[16] + ":" + "cut16"  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[99] ), // ToyMC
  // (coll_system + ":" + name[53] + ":" + tree_name[5] + ":" + cuts200[17] + ":" + "cut17"  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[100] ), // ToyMC
  // (coll_system + ":" + name[53] + ":" + tree_name[5] + ":" + cuts200[18] + ":" + "cut18"  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[101] ), // ToyMC
  // (coll_system + ":" + name[53] + ":" + tree_name[5] + ":" + cuts200[19] + ":" + "cut19"  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[102] ), // ToyMC
  // (coll_system + ":" + name[53] + ":" + tree_name[5] + ":" + cuts200[20] + ":" + "cut20"  + ":" + effi_name[13] + ":" + effi_gen[5] + ":" + effi_rec[103] ), //  ("") ToyMC

  // (coll_system + ":" + name[66] + ":" + tree_name[5] + ":" + cuts200[5]      +  ":" + "cut5 TOFif"     + ":" + effi_name[55] + ":" + effi_gen[9] + ":" + effi_rec[131] ), //
  // (coll_system + ":" + name[66] + ":" + tree_name[5] + ":" + cuts200[25]     +  ":" + "cut5 TOFreq"    + ":" + effi_name[55] + ":" + effi_gen[9] + ":" + effi_rec[131] ), //
  // (coll_system + ":" + name[66] + ":" + tree_name[5] + ":" + cut_setting[49] +  ":" + "Jerome"         + ":" + effi_name[55] + ":" + effi_gen[9] + ":" + effi_rec[131] ), //
  ("")
};
TString cconfig_phiV[] = { // this determines which settings will really be analysed!
  // (coll_system + ":" + name[64] + ":" + tree_name[5] + ":" + cuts200_woSCcut[5] +  ":" + "woSCcut - cut5 "  + ":" + effi_name[47] + ":" + effi_gen[9] + ":" + effi_rec[111] ), //

  // (coll_system + ":" + name[56] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "data, no #phi_{V} corr."  + ":" + effi_name[35] + ":" + effi_gen[7] + ":" + effi_rec[105] ), //
  // (coll_system + ":" + name[63] + ":" + tree_name[5] + ":" + "cut5_pt200/Pair_MCpair_sameMother"  +  ":" + "MC, prompt"  + ":" + effi_name[35] + ":" + effi_gen[7] + ":" + effi_rec[105] ), //
  // (coll_system + ":" + name[63] + ":" + tree_name[5] + ":" + "cut5_pt200/Pair_MCpair_sameGamma"   +  ":" + "MC, conv."  + ":" + effi_name[35] + ":" + effi_gen[7] + ":" + effi_rec[105] ), //
  // (coll_system + ":" + name[56] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "data, template correction"  + ":" + effi_name[35] + ":" + effi_gen[7] + ":" + effi_rec[105] ), //
  // (coll_system + ":" + name[56] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "data, flat corr"  + ":" + effi_name[35] + ":" + effi_gen[7] + ":" + effi_rec[105] ), //

  (coll_system + ":" + name[76] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "data, no #phi_{V} corr."  + ":" + effi_name[57] + ":" + effi_gen[13] + ":" + effi_rec[162] ), //
  (coll_system + ":" + name[63] + ":" + tree_name[5] + ":" + "cut5_pt200/Pair_MCpair_sameMother"  +  ":" + "MC, prompt"  + ":" + effi_name[35] + ":" + effi_gen[7] + ":" + effi_rec[105] ), //
  (coll_system + ":" + name[63] + ":" + tree_name[5] + ":" + "cut5_pt200/Pair_MCpair_sameGamma"   +  ":" + "MC, conv."  + ":" + effi_name[35] + ":" + effi_gen[7] + ":" + effi_rec[105] ), //
  (coll_system + ":" + name[76] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "data, template corr."  + ":" + effi_name[57] + ":" + effi_gen[13] + ":" + effi_rec[162] ), //
  (coll_system + ":" + name[76] + ":" + tree_name[5] + ":" + cuts200[5]  +  ":" + "data, flat corr."  + ":" + effi_name[57] + ":" + effi_gen[13] + ":" + effi_rec[162] ), //



  ("")
};

Int_t n_config_pt400 = sizeof(cconfig_pt400)/sizeof(*cconfig_pt400) - 1;
Int_t n_config_pt200 = sizeof(cconfig_pt200)/sizeof(*cconfig_pt200) - 1;
Int_t n_config_phiV  = sizeof(cconfig_phiV)/sizeof(*cconfig_phiV) - 1;

  // cocktail files
TString cocktail_files[] = {
  "./input/cocktail/pt400/0080/cocktail-01-kPbPb_276_1020_pt400-24x100x20000.root:./input/cocktail/cocktail-01-kPbPb_276_2030_pt400-24x100x20000.root:./input/cocktail/cocktail-01-kPbPb_276_3040_pt400-24x100x20000.root:./input/cocktail/cocktail-01-kPbPb_276_4050_pt400-24x100x20000.root",
  "./input/cocktail/pt400/0080/cocktail_PbPb502_1050.root",
  "./input/cocktail/pt400/0080/LF_cocktail_v3.root", // First working cocktail Oton Style
  "./input/cocktail/pt400/0080/LF_cocktail_v3_low.root",
  "./input/cocktail/pt400/0080/LF_cocktail_v3_high.root",
  "./input/cocktail/pt400/0080/Cocktail_pt400_0080_smeared.root", // Strange behaviour. Do not use
  "./input/cocktail/pt400/0080/LFcocktail_pt400_eta08_mT_newReso.root", // Cocktail with new Resolution and only mT scaling
  "./input/cocktail/pt400/0080/LFcocktail_pt400_eta08_wRatio_newReso.root", // Cocktail with new Resolution and K/pi ratio as proxy for eta/pi ratio
  "./input/cocktail/pt400/0080/cocktail_LF_v2.root", // [8] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018
  "./input/cocktail/pt400/0080/cocktail_LF_v2_low.root", // [9] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018
  "./input/cocktail/pt400/0080/cocktail_LF_v2_high.root", // [10] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018
  "./input/cocktail/pt200/0080/cocktail_LF_v2.root", // [11] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018
  "./input/cocktail/pt200/0080/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_0080.root", // [12] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018
  "./input/cocktail/pt200/0010/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_0010.root", // [13] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018
  "./input/cocktail/pt200/1050/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_1050.root", // [14] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018
  "./input/cocktail/pt200/5080/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_5080.root", // [15] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018
  "./input/cocktail/pt200/0080/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_0080_maxpt.root", // [16] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018

  "./input/cocktail/pt200/0020/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_0020.root", // [17] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018
  "./input/cocktail/pt200/2040/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_2040.root", // [18] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018
  "./input/cocktail/pt200/4080/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_4080.root", // [19] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018

  "./input/cocktail/pt200/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_1020.root", // [20] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018
  "./input/cocktail/pt200/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_4050.root", // [21] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018
  "./input/cocktail/pt200/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_5060.root", // [22] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018
  "./input/cocktail/pt200/LFcocktail_pt200_eta08_wRatio_newReso_PhotonV2_central_6080.root", // [23] Cocktail with K/pi ratio as proxy for eta/pi ratio. 16.Feb.2018

  "./input/cocktail/pt200/0080/LFcocktail_pt200_eta08_wRatio_newReso_central_0080_newResolution.root", // [24] Cocktail with K/pi ratio as proxy for eta/pi ratio, new resolution map. 03.04.2018
  "./input/cocktail/pt200/0080/LFcocktail_pt200_eta08_wRatio_newReso_central_0080_high.root", // [25] high Cocktail with K/pi ratio as proxy for eta/pi ratio, new resolution map. 03.04.2018
  "./input/cocktail/pt200/0080/LFcocktail_pt200_eta08_wRatio_newReso_central_0080_low.root", //  [26] low Cocktail with K/pi ratio as proxy for eta/pi ratio, new resolution map. 03.04.2018

  "./input/cocktail/pt200/0080/LFcocktail_pt200_eta08_wRatio_newReso_central_0080_4080_resolution.root", //  [27] low Cocktail with K/pi ratio as proxy for eta/pi ratio, new resolution map. 03.04.2018

  "./input/cocktail/pt200/0080/LFcocktail_pt200_eta08_wRatio_central_0080_pp13TeV_resolution.root", //  [28] low Cocktail with K/pi ratio as proxy for eta/pi ratio, new resolution map. 03.04.2018
  "./input/cocktail/pt200/0080/LFcocktail_Carsten_200MeV_0080_wRatio_v1.root", //  [29] low Cocktail with K/pi ratio as proxy for eta/pi ratio, new resolution map. 03.04.2018

  "./input/cocktail/pt200/0080/LFcocktail_pt200_eta08_wRatio_central_0080_upto30GeV_halftheresolution.root", //  [30] low Cocktail with K/pi ratio as proxy for eta/pi ratio, new resolution map. 03.04.2018

  "./input/cocktail/pt200/0010/LFcocktail_pt200-8000_eta08_wRatio_central_0010_01082018.root", //  [31] 01.08.2018 new resolution
  "./input/cocktail/pt200/0020/LFcocktail_pt200-8000_wRatio_central_0020_01082018.root", //  [32] 01.08.2018 new resolution
  ""
};
TString cocktail_list[] = {
  "cocktailPt400rec:cocktailPt400rec:cocktailPt400rec:cocktailPt400rec:cocktailPt400rec",
  "cocktailPt400:cocktailPt400:cocktailPt400:cocktailPt400:cocktailPt400",
  "LMeeCocktailMC/LMeeCocktailMC_pt400",
  "LMeeCocktailMC/LMeeCocktailMC_0.80",
  ""
};
// cocktail histograms
TString cocktail_histograms[] = {
  "Mee_Ptee_Pion_angleSmeared:Mee_Ptee_Eta_angleSmeared:Mee_Ptee_EtaPrime_angleSmeared:Mee_Ptee_Rho_angleSmeared:Mee_Ptee_Omega_angleSmeared:Mee_Ptee_OmegaDalitz_angleSmeared:Mee_Ptee_Phi_angleSmeared:Mee_Ptee_PhiDalitz_angleSmeared",
  "MeePteePion:MeePteeEta:MeePteeEtaPrime:MeePteeRho:MeePteeOmega:MeePtee:MeePteePhi",
  "pteevsmee_Pi0:pteevsmee_Eta:pteevsmee_EtaPrim:pteevsmee_rho0:pteevsmee_omega:pteevsmee_phi",
  "pteevsmee_Pi0:pteevsmee_Eta:pteevsmee_EtaP:pteevsmee_Rho:pteevsmee_Omega:pteevsmee_Phi",
  "pteevsmee_Pi0:pteevsmee_Eta",
  "pteevsmee_Eta",
  "pteevsmee_Pi0:pteevsmee_EtaP:pteevsmee_Rho:pteevsmee_Omega:pteevsmee_Phi",
  ""
};

// J/Psi files
TString JPsi_files[] = {
   "./input/cocktail/pt400/0080/jpsi-PbPb2015_0080-pt400.root", // 0
   "./input/cocktail/pt200/0080/jpsi-PbPb2015_0080-pt200.root", // 1
   "./input/cocktail/pt200/0020/jpsi-PbPb2015_0020-pt200.root", // 2
   "./input/cocktail/pt200/2040/jpsi-PbPb2015_2040-pt200.root", // 3
   "./input/cocktail/pt200/4080/jpsi-PbPb2015_4080-pt200.root", // 4
   ""
};
TString JPsi_list[] = {
  "Mee_Ptee_angleSmeared",
  "Mee_Ptee",
  ""
};

TString JPsi_histograms[] = {
   "Mee_Ptee_Jpsi_std_angleSmeared",//"-hMeePtee_LS_eta08_pt400_opAngle50_smeared",
   "Mee_Ptee_Jpsi_low_angleSmeared",//"-hMeePtee_LS_eta08_pt400_opAngle50_smeared",
   "Mee_Ptee_Jpsi_high_angleSmeared",//"-hMeePtee_LS_eta08_pt400_opAngle50_smeared",
   "Mee_Ptee_Jpsi_std",//"-hMeePtee_LS_eta08_pt400_opAngle50_smeared",
   ""
};

// heavy flavour files
TString heavyfl_files[] = {
   "./input/cocktail/pt400/0080/charm-PbPb-kPythiaPerugia11_pp5020GeV_Run2-240x40000_unsmeared.root", //
   "./input/cocktail/pt400/0080/charm-PbPb-kPythiaPerugia11_pp5020GeV_Run2-240x40000_smeared1050.root:./input/cocktail/pt400/0080/beauty-PbPb-kPythiaPerugia11_pp5020GeV_Run2-960x40000_smeared1050.root",
   "./input/cocktail/pt400/0080/cocktail_charm.root:./input/cocktail/pt400/0080/beauty-PbPb-kPythiaPerugia11_pp5020GeV_Run2-960x40000_smeared1050.root",
   "./input/cocktail/pt400/0080/cocktail_charm.root",
   "./input/cocktail/pt400/0080/beauty-PbPb-kPythiaPerugia11_pp5020GeV_Run2-960x40000_smeared1050.root",
   "./input/cocktail/pt400/0080/cocktail_charm_V2.root", // 5
   "./input/cocktail/pt400/0080/cocktail_beauty_V2.root",
   "./input/cocktail/charm_eps09_v1.root", // 7
   "./input/cocktail/PbPb_coldeffectscharm_1.root", // 8
   ""
};
TString heavyfl_list = "lowee:lowee";
TString heavyfl_charm[]  = {"lowee", "lowee1"};
TString heavyfl_beauty = "lowee";

TString heavyfl_histograms[] = {
   "hMeePtee_ULS_eta08_pt400",//"-hMeePtee_LS_eta08_pt400_opAngle50_smeared",
   "hMeePtee_ULS_eta08_pt400-hMeePtee_LS_eta08_pt400:hMeePtee_ULS_eta08_pt400-hMeePtee_LS_eta08_pt400",
   "hMeePtee_ULS_eta08_pt400-hMeePtee_LS_eta08_pt400",
   "hMeePtee_ULS_eta08_pt200-hMeePtee_LS_eta08_pt200",
   "hMeePtee_ULS_eta08_pt200-hMeePtee_LS_eta08_pt200",
   ""
};

TString heavyfl_hist_Nevents[] = { // always synchronize with 'heavyfl_histograms'.
   "hRapCharmQuarkMethod1",//"hNEvents",
   "hRapCharmQuarkMethod1:hRapBeautyQuarkMethod1",
   "hRapBeautyQuarkMethod1",//"hNEvents",
   ""
};

//__________________________________________________________________________________________________________

// std::vector<Double_t> mee_bin = { // most fine binning
//   0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
//    0.10, 0.14, 0.18, 0.22, 0.26, 0.30, 0.34, 0.38, 0.42, 0.46,
//    0.50, 0.54, 0.58, 0.62, 0.66, 0.70, 0.74, 0.78, 0.82, 0.86,
//    0.90, 0.94, 0.98, 1.02, 1.06,
//    1.10, 1.20, 1.30, 1.40, 1.50, 1.70, 1.90, 2.10, 2.30, 2.50, 2.70, 2.80,
//    2.90, 3.00, 3.05, 3.10, 3.20, 3.30, 3.50, 4.00, 4.50, 5.00
// };
// std::vector<Double_t> mee_bin = { // Shown on 14.03.2018 in DQ meeting
//   0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14,// Realistic binningLHC15o
//   0.18, 0.22, 0.30, 0.38, 0.46, 0.54, 0.62, 0.70, 0.78, 0.86, 0.94, 1.02, 1.1, 1.3,
//   1.70, 2.30, 2.70, 2.90, 3.00, 3.10, 3.20, 3.30, 4.00, 5.00
// };
// std::vector<Double_t> mee_bin = { // Coarse binning for less fluctuations
//   0.00, 0.04, 0.08, 0.14,// Realistic binningLHC15o
//   0.38, 0.7, 1.1,
//   2.70, 3.30, 4.00, 5.00
// };
std::vector<Double_t> mee_bin = { // Preview
  0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14,// Realistic binningLHC15o
  0.18, 0.22, 0.30, 0.38, 0.46, 0.62, 0.7, 0.86, 1.1,
  1.70, 2.30, 2.70, 2.90, 3.00, 3.10, 3.30, 4.00, 5.00
};
std::vector<Double_t> mee_bin0010 = {
  0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14,
  0.22, 0.38, 0.54, 0.70, 1.1,
  1.50, 2.30, 2.70, 2.90, 3.00, 3.10, 3.20, 3.30, 4.00, 5.00
};
std::vector<Double_t> mee_bin1050 = {
  0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14,
  0.22, 0.38, 0.54, 0.70, 0.86, 0.94, 1.1,
  1.70, 2.30, 2.70, 2.90, 3.00, 3.10, 3.20, 3.30, 4.00, 5.00
};
std::vector<Double_t> mee_bin5080 = {
  0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14,
  0.22, 0.38, 0.54, 0.70, 0.86, 0.94, 1.1,
  1.70, 2.30, 2.70, 2.90, 3.00, 3.10, 3.20, 3.30, 4.00, 5.00
};
std::vector<Double_t> mee_bin0020 = {
// std::vector<Double_t> mee_bin = {
  0.00, 0.02, 0.04, 0.06, 0.08, 0.1, 0.14, 0.22,
  0.38, 0.54, 0.70, 1.1,
  1.70, 2.30, 2.70, 2.90, 3.00, 3.10, 3.20, 3.30, 4.00, 5.00
};
// std::vector<Double_t> mee_bin0020 = {
// // std::vector<Double_t> mee_bin = {
//   0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14,
//   0.22, 0.38, 0.54, 0.70, 1.1,
//   1.70, 2.30, 2.70, 2.90, 3.00, 3.10, 3.20, 3.30, 4.00, 5.00
// };
std::vector<Double_t> mee_bin2040 = {
  0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14,
  0.22, 0.38, 0.54, 0.70, 0.86, 0.94, 1.1,
  1.70, 2.30, 2.70, 2.90, 3.00, 3.10, 3.20, 3.30, 4.00, 5.00
};
std::vector<Double_t> mee_bin4080 = {
  0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14,
  0.22, 0.38, 0.54, 0.70, 0.86, 0.94, 1.1,
  1.70, 2.30, 2.70, 2.90, 3.00, 3.10, 3.20, 3.30, 4.00, 5.00
};
std::vector<Double_t> mee_bin_coarse = {
  0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14,
  0.22, 0.38, 0.54, 0.70, 1.1,
  1.70, 2.70, 2.90, 3.00, 3.10, 3.20, 3.30, 4.00, 5.00
};

// std::vector<Double_t> mee_bin = { // Fine binning for ULS-LS plots
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

// for phiV study
// Double_t ptee_bin[] = {
//   0.0, 1.0}; // Binning for first shots on LHC15o
//   // 2.0, 3.0, 4.0, 5.0, 6., 8.};
//
//
Double_t ptee_bin[] = { // binning from APW
  0.0, 0.05, 0.10, 0.15, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
  1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6,
  3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 6., 8.};
// Double_t ptee_bin[] = { // Coarse binning for preview
//   0.0, 0.10, 0.2, 0.4, 0.6, 0.8, 1.0,
//   1.2, 1.6, 2.0, 2.4, 3.0, 3.4,
//   4.0,  4.4, 5.0, 8.};

// Double_t ptee_bin[] = { // binning for HF_Fit
//     0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 8.};
// Double_t ptee_bin[] = { // binning for HF_Fit
//     0.0, 0.5, 1.0, 2.0, 3.0, 4.0, 5.0, 6., 8.};
// Special binning

std::vector<double> mee_bin_0_1GeV{ 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14, 0.22, 0.38, 0.54, 0.7, 0.74, 0.94, 1.02, 1.1, 1.5, 2.0, 2.70, 2.90, 3.0, 3.10, 3.30, 4.00, 5.00};
std::vector<double> mee_bin_1_2GeV{ 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14, 0.18, 0.22, 0.30, 0.38, 0.46, 0.54, 0.62, 0.7, 0.74, 0.78, 0.86, 0.94, 0.98, 1.02, 1.1, 1.5, 2.0, 2.70, 2.90, 3.0, 3.10, 3.30, 4.00, 5.00};
std::vector<double> mee_bin_2_4GeV{ 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14, 0.18, 0.22, 0.30, 0.38, 0.46, 0.54, 0.62, 0.7, 0.74, 0.78, 0.86, 0.94, 0.98, 1.02, 1.1, 1.3, 1.5, 1.70, 2.0, 2.30, 2.70, 2.90, 3.0, 3.10, 3.2, 3.30, 4.00, 5.00};
std::vector<double> mee_bin_4_8GeV{ 0.00, 0.04, 0.08, 0.14, 0.22, 0.38, 0.54, 0.7, 0.74, 0.94, 1.02, 1.1, 1.5, 2.0, 2.70, 2.90, 3.0, 3.10, 3.30, 4.00, 5.00};
std::vector<double> mee_bin_0_8GeV{ 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14, 0.18, 0.22, 0.30, 0.38, 0.46, 0.54, 0.62, 0.7, 0.74, 0.78, 0.86, 0.94, 0.98, 1.02, 1.1, 1.3, 1.5, 1.70, 2.0, 2.30, 2.70, 2.90, 3.0, 3.10, 3.2, 3.30, 4.00, 5.00};

std::vector<double> ptee_bin_LookingAtPtee_0_140{
  0.0, 0.10, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.4, 3.8, 4.2, 4.6, 5.0, 6., 8.};
std::vector<double> ptee_bin_LookingAtPtee_140_380{
  0.0, 0.4, 0.8, 1.2, 2.0, 3.0, 4., 5.0, 8. };
std::vector<double> ptee_bin_LookingAtPtee_380_740{
  0.0, 0.4, 0.8, 1.2, 2.0, 3.0, 4., 5.0, 8. };
std::vector<double> ptee_bin_LookingAtPtee_740_1100{
  0.0, 0.4, 0.8, 1.2, 2.0, 3.0, 4., 5.0, 8. };
std::vector<double> ptee_bin_LookingAtPtee_1100_2900{
  0.0, 0.4, 0.8, 1.2, 2.0, 3.0, 4., 5.0, 8.};
std::vector<double> ptee_bin_LookingAtPtee_2900_3300{
  0.0, 0.4, 0.8, 1.2, 2.0, 3.0, 4., 5.0, 8.};
    // 0.0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.2, 3.6, 3.8, 4.0, 5.0, 6.0, 8. };
std::vector<double> ptee_bin_LookingAtPtee_3300_5000{
    0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 8. };
// std::vector<double> ptee_bin_LookingAtPtee_0_140{
//     0.0, 0.6, 0.8, 0.9, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 6.0, 8. };
// std::vector<double> ptee_bin_LookingAtPtee_140_380{
//   0.0, 0.4, 0.7, 1.2, 2.0, 2.8, 3.6, 5.0, 6.0, 8. };
// std::vector<double> ptee_bin_LookingAtPtee_380_740{
//   0.0, 0.5, 0.9, 1.6, 2.4, 3.2, 4.4, 6.0, 8. };
// std::vector<double> ptee_bin_LookingAtPtee_740_1100{
//     0.0, 0.5, 0.9, 1.6, 2.4, 3.2, 4.4, 6.0, 8. };
// std::vector<double> ptee_bin_LookingAtPtee_1100_2900{
//     0.0, 0.8, 1.6, 2.4, 3.2, 4.0, 4.8, 6, 8. };
// std::vector<double> ptee_bin_LookingAtPtee_2900_3300{
//     0.0, 0.8, 1.6, 2.4, 3.2, 4.0, 5.0, 6.0, 8.  };
//     // 0.0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.2, 3.6, 3.8, 4.0, 5.0, 6.0, 8. };
// std::vector<double> ptee_bin_LookingAtPtee_3300_5000{
//     0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 8. };

Int_t n_mee_bin ;
// Int_t n_ptee_bin;
// Int_t n_mee_bin = sizeof(mee_bin)/sizeof(*mee_bin) -1;
Int_t n_ptee_bin = sizeof(ptee_bin)/sizeof(*ptee_bin) -1;

// desired binning for cocktail.
// may be much finer than for data, but the bin edges should overlap to avoid inconsistencies when doing projections!

// COCKTAIL BINNING ###############################
//
// Double_t mee_bin_cocktail[] = { // binning for HF FIT
//   0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14,// Realistic binningLHC15o
//   0.18, 0.22, 0.30, 0.38, 0.46, 0.62, 0.7, 0.86, 1.1,
//   1.70, 2.30, 2.70, 2.90, 3.00, 3.10, 3.30, 4.00, 5.00
// };
// //
// Double_t ptee_bin_cocktail[] = { // binning for HF FIT
//   0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 8.
// };
// Double_t ptee_bin_cocktail[] = { // binning for HF FIT
//   0.0, 0.5, 1.0, 2.0, 3.0, 4.0, 5.0, 6., 8.
// };

Double_t mee_bin_cocktail[] = {
  0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38, 0.40, 0.42, 0.44, 0.46, 0.48,
  0.50, 0.52, 0.54, 0.56, 0.58, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.72, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98,
  1.00, 1.02, 1.04, 1.06, 1.08, 1.10, 1.12, 1.14, 1.16, 1.18, 1.20,
  1.30, 1.40, 1.50, 1.60, 1.70, 1.80, 1.90, 2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 3.00, 3.10, 3.20, 3.30, 3.40, 3.50, 3.60, 3.70, 3.80, 3.90,
  4.00, 4.10, 4.20, 4.30, 4.40, 4.50, 4.60, 4.70, 4.80, 4.90, 5.00
};

Double_t ptee_bin_cocktail[] = {
  0.0, 0.05, 0.10, 0.15, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, // Binning for first shots on LHC15o
  1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6,
  3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 6.0, 7.9, 8., 9.
};
Int_t n_mee_bin_cocktail = sizeof(mee_bin_cocktail)/sizeof(*mee_bin_cocktail) -1;
Int_t n_ptee_bin_cocktail = sizeof(ptee_bin_cocktail)/sizeof(*ptee_bin_cocktail) -1;

// SYSTEMATIC BINNING #############################################################
// bin edges must match with the projection bins of the final data handler!
Double_t mee_bin_systematic[] = {   0.00, 0.02, 0.04, 0.06, 0.10, 0.14,// Realistic binningLHC15o
  0.22, 0.30, 0.46, 0.66, 0.74, 0.86, 0.98, 1.1, 1.30,
  1.70, 2.30, 2.70, 2.90, 3.10, 3.30, 4.00, 5.00
};

// Double_t ptee_bin_systematic[] = {
//   0.0, 0.5, 1.0, 2.0, 3.0, 4.0, 5.0, 6., 8.
//
// };
Double_t ptee_bin_systematic[] = {
  0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5,
  1.6, 1.7, 1.8, 1.9, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0,
  3.2, 3.4, 3.6, 3.8, 4.0, 4.5, 5.0, 6.0, 8.0
};
// Double_t ptee_bin_systematic[] = {
//   0.0, 0.1, 0.3, 0.5, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5,
//   1.6, 1.7, 1.8, 1.9, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0,
//   3.2, 3.4, 3.6, 3.8, 4.0, 4.5, 5.0, 6.0, 8.0
// };

std::vector<double> mee_bin_systematic_coarse{
  0.00, 0.14,// Realistic binningLHC15o
    5.00
};
// std::vector<double> mee_bin_systematic_coarse{
//   0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14,// Realistic binningLHC15o
//    0.38, 0.7, 1.1,
//   2.30, 2.90, 3.10, 4.00, 5.00
// };
std::vector<double> ptee_bin_systematic_coarse{
    0.0, 8.
};

// Double_t ptee_bin_systematic[] = {  0.0, 8.0};
Int_t n_mee_bin_systematic = sizeof(mee_bin_systematic)/sizeof(*mee_bin_systematic) -1;
Int_t n_ptee_bin_systematic = sizeof(ptee_bin_systematic)/sizeof(*ptee_bin_systematic) -1;

//__________________________________________________________________________________________________________
// PhiV-cut that shall be applied
// to disable, it's most efficient to call mgr.SetEnableExclusionCutZ(kFALSE);
// Double_t cutPhiVbelow[] = { 0,                 0,                 0 };
// Double_t cutPhiVabove[] = { 1./2.*TMath::Pi(), 3./4.*TMath::Pi(), 7./8.*TMath::Pi()};
// Double_t cutEdgesMee[]  = { 0.02,              0.04,              0.14 };

// Double_t cutPhiVbelow[] = { 0,                 0,                     0.};
// Double_t cutPhiVabove[] = { 4./8.*TMath::Pi(), 6/8.*TMath::Pi(),      7/8.*TMath::Pi()};
// Double_t cutEdgesMee[]  = { 0.02,              0.04,                  0.1};

// Double_t cutPhiVbelow[] = { 0,                 0              };
// Double_t cutPhiVabove[] = { 4./8.*TMath::Pi(), 6/8.*TMath::Pi()};
// Double_t cutEdgesMee[]  = { 0.02,              0.04           };

// Double_t cutPhiVbelow[] = { 0,                 0              };
// Double_t cutPhiVabove[] = { 6./8.*TMath::Pi(), 6/8.*TMath::Pi()};
// Double_t cutEdgesMee[]  = { 0.02,              0.06           };
Double_t cutPhiVbelow[] = { 0,                 0              };
Double_t cutPhiVabove[] = { 6./8.*TMath::Pi(), 7/8.*TMath::Pi()};
Double_t cutEdgesMee[]  = { 0.04,              0.08           };
Int_t    n_cutPhiVbelow = sizeof(cutPhiVbelow)/sizeof(*cutPhiVbelow);
Int_t    n_cutPhiVabove = sizeof(cutPhiVabove)/sizeof(*cutPhiVabove);
Int_t    n_cutEdgesMee  = sizeof(cutEdgesMee)/sizeof(*cutEdgesMee);

Double_t phiv_bin_1[] = { 1 };
Double_t phiv_bin[] = { 2 };
Int_t n_phiv_bin = sizeof(phiv_bin)/sizeof(*phiv_bin) -1;

//_______________________________________________________________________________________________
// more global variables
std::vector<Double_t> binsPtee_forMee, binsPtee_forMee_sys;
std::vector<Double_t> binsMee_forPtee, binsMee_forPtee_sys, binsMee_forPhiV;
std::vector<Double_t> binsPhiV;

Double_t plotMeeMin,  plotMeeMax,  plotMeeMax_sys;
Double_t plotPteeMin, plotPteeMax, plotPteeMax_sys;
// switches and corresponding strings
Int_t   kDoPt400, kDoPref , kDoEffGen;
Bool_t kDoInclusive;
TString sOptCent, sOptPt  , sOptPref, sOptEff;
//Bool_t  kDoPref, kDoNoPref;
Bool_t  printLegend;
Bool_t  plotAverage, plotWeightAv;
Bool_t  writeFile;
Int_t   selectedCut, selCutMaxStat;
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

LmCocktail* ProcessCocktail()
{
  Printf("______ process cocktail ______");

  // pt 400; 00-80
  Int_t   which_cockt_files = 8;
  Int_t   which_cockt_list  = 3;
  Int_t   which_cockt_hists = 3;

  Int_t   which_cockt_files_low  = 9;
  Int_t   which_cockt_files_high = 10;

  Int_t   which_JPsi_files = 0;
  Int_t   Which_JPsi_list = 1;
  Int_t   which_JPsi_hists = 3;

  Int_t   which_heavyfl_files = 2;
  Int_t   which_heavyfl_hists = 1;
  Int_t   which_charm_files = 5;
  Int_t   which_charm_hists = 2;
  Int_t   which_beauty_files = 6;
  Int_t   which_beauty_hists = 2;
  Int_t   which_charm_list = 0;

  if (kDo200MeV == kFALSE && kCentrality == kCent::kCent0080){
    which_cockt_files = 8;
    which_cockt_files_low = 9;
    which_cockt_files_high = 10;
    which_JPsi_files = 0;
    which_charm_hists  = 2;
    which_beauty_hists = 2;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent0080){
    // which_cockt_files      = 11; // old cocktail
    // which_cockt_files_low  = 11; // old cocktail
    // which_cockt_files_high = 11; // old cocktail
    // which_cockt_files      = 12;
    // which_cockt_files_low  = 12;
    // which_cockt_files_high = 12;
    // which_cockt_files      = 16; // max pt cut
    // which_cockt_files_low  = 16; // max pt cut
    // which_cockt_files_high = 16; // max pt cut

    // which_cockt_files      = 24; // 18.04.2018 cocktail
    // which_cockt_files_low  = 25; // 18.04.2018 cocktail
    // which_cockt_files_high = 26; // 18.04.2018 cocktail

    which_cockt_files      = 30; // jeromes calculation
    which_cockt_files_low  = 30; // jeromes calculation
    which_cockt_files_high = 30; // jeromes calculation
    which_JPsi_files = 1;
    which_charm_files = 8;
    which_charm_list = 1;
    which_charm_hists  = 3;
    which_beauty_hists = 3;

  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent0010){
    // which_cockt_files      = 13;
    // which_cockt_files_low  = 13;
    // which_cockt_files_high = 13;
    which_cockt_files      = 31;
    which_cockt_files_low  = 31;
    which_cockt_files_high = 31;
    which_JPsi_files = 2;
    which_charm_hists  = 3;
    which_beauty_hists = 3;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent1050){
    which_cockt_files      = 14;
    which_cockt_files_low  = 14;
    which_cockt_files_high = 14;
    which_JPsi_files = 3;
    which_charm_hists  = 3;
    which_beauty_hists = 3;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent5080){
    which_cockt_files      = 15;
    which_cockt_files_low  = 15;
    which_cockt_files_high = 15;
    which_JPsi_files = 4;
    which_charm_hists  = 3;
    which_beauty_hists = 3;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent0020){
    which_cockt_files      = 32;
    which_cockt_files_low  = 32;
    which_cockt_files_high = 32;
    which_JPsi_files   = 2;
    which_charm_hists  = 3;
    which_beauty_hists = 3;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent2040){
    which_cockt_files      = 18;
    which_cockt_files_low  = 18;
    which_cockt_files_high = 18;
    which_JPsi_files   = 3;
    which_charm_hists  = 3;
    which_beauty_hists = 3;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent4080){
    which_cockt_files      = 19;
    which_cockt_files_low  = 19;
    which_cockt_files_high = 19;
    which_JPsi_files = 4;
    which_charm_hists  = 3;
    which_beauty_hists = 3;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent1020){
    which_cockt_files      = 20;
    which_cockt_files_low  = 20;
    which_cockt_files_high = 20;
    which_JPsi_files = 2;
    which_charm_hists  = 3;
    which_beauty_hists = 3;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent4050){
    which_cockt_files      = 21;
    which_cockt_files_low  = 21;
    which_cockt_files_high = 21;
    which_JPsi_files = 3;
    which_charm_hists  = 3;
    which_beauty_hists = 3;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent5060){
    which_cockt_files      = 22;
    which_cockt_files_low  = 22;
    which_cockt_files_high = 22;
    which_JPsi_files = 3;
    which_charm_hists  = 3;
    which_beauty_hists = 3;
  }
  else if (kDo200MeV == kTRUE && kCentrality == kCent::kCent6080){
    which_cockt_files      = 23;
    which_cockt_files_low  = 23;
    which_cockt_files_high = 23;
    which_JPsi_files = 4;
    which_charm_hists  = 3;
    which_beauty_hists = 3;
  }

  // cocktail (handles the cocktail spectra)
  Int_t collsystem = -1;
  if      (kCentrality == kCent0080) collsystem = LmCocktail::kPbPb_0080_5020;
  else if (kCentrality == kCent0010) collsystem = LmCocktail::kPbPb_0010_5020;
  else if (kCentrality == kCent1050) collsystem = LmCocktail::kPbPb_1050_5020;
  else if (kCentrality == kCent5080) collsystem = LmCocktail::kPbPb_5080_5020;
  else if (kCentrality == kCent0020) collsystem = LmCocktail::kPbPb_0020_5020;
  else if (kCentrality == kCent2040) collsystem = LmCocktail::kPbPb_2040_5020;
  else if (kCentrality == kCent4080) collsystem = LmCocktail::kPbPb_4080_5020;
  else if (kCentrality == kCent4080) collsystem = LmCocktail::kPbPb_4080_5020;
  else if (kCentrality == kCent1020) collsystem = LmCocktail::kPbPb_1020_5020;
  else if (kCentrality == kCent4050) collsystem = LmCocktail::kPbPb_4050_5020;
  else if (kCentrality == kCent5060) collsystem = LmCocktail::kPbPb_5060_5020;
  else if (kCentrality == kCent6080) collsystem = LmCocktail::kPbPb_6080_5020;
  LmCocktail* cockt00 = new LmCocktail(collsystem);

  // cocktail managers (organize input)
  // for resonances
  LmCocktailMan* cocktmanReso = new LmCocktailMan();
  cocktmanReso->SetInputfiles(const_cast<char*>(cocktail_files[which_cockt_files].Data()));
  cocktmanReso->SetInputlists(const_cast<char*>(cocktail_list[which_cockt_list].Data()));
  cocktmanReso->SetInputhistAndDim(const_cast<char*>(cocktail_histograms[which_cockt_hists].Data()), 2); // 2D
  cocktmanReso->SetInputfilesAndHistsLow(const_cast<char*>(cocktail_files[which_cockt_files_low].Data()), const_cast<char*>(cocktail_histograms[which_cockt_hists].Data())); // 2D
  cocktmanReso->SetInputfilesAndHistsHigh(const_cast<char*>(cocktail_files[which_cockt_files_high].Data()), const_cast<char*>(cocktail_histograms[which_cockt_hists].Data())); // 2D
  cocktmanReso->SetHistForNevents("NEvents");
  cocktmanReso->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanReso->Process(LmCocktailMan::kResonances);
  // cocktmanReso->Process(LmCocktailMan::kLFsum);

  LmCocktailMan* cocktmanResoWoEta = new LmCocktailMan();
  cocktmanResoWoEta->SetInputfiles(const_cast<char*>(cocktail_files[which_cockt_files].Data()));
  cocktmanResoWoEta->SetInputlists(const_cast<char*>(cocktail_list[which_cockt_list].Data()));
  cocktmanResoWoEta->SetInputhistAndDim(const_cast<char*>(cocktail_histograms[5].Data()), 2); // 2D
  cocktmanResoWoEta->SetHistForNevents("NEvents");
  cocktmanResoWoEta->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanResoWoEta->Process(LmCocktailMan::kResonances);

  LmCocktailMan* cocktmanEta = new LmCocktailMan();
  cocktmanEta->SetInputfiles(const_cast<char*>(cocktail_files[which_cockt_files].Data()));
  cocktmanEta->SetInputlists(const_cast<char*>(cocktail_list[which_cockt_list].Data()));
  cocktmanEta->SetInputhistAndDim(const_cast<char*>(cocktail_histograms[6].Data()), 2); // 2D
  cocktmanEta->SetHistForNevents("NEvents");
  cocktmanEta->SetArbitraryScaling(1);
  cocktmanEta->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanEta->Process(LmCocktailMan::kResonances);

  // for virtual photon
  std::cout << "--- Virtual Photon ---" << std::endl;
  LmCocktailMan* cocktmanVirtPhoton = new LmCocktailMan();
  cocktmanVirtPhoton->SetInputfiles(const_cast<char*>(cocktail_files[which_cockt_files].Data()));
  cocktmanVirtPhoton->SetInputlists(const_cast<char*>(cocktail_list[which_cockt_list].Data()));
  cocktmanVirtPhoton->SetInputhistAndDim(const_cast<char*>("pteevsmee_Virtual_Photon"), 2); // 2D
  cocktmanVirtPhoton->SetArbitraryScaling(1. / 5000);
  cocktmanVirtPhoton->SetHistForNevents("NEvents");
  cocktmanVirtPhoton->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanVirtPhoton->Process(LmCocktailMan::kVirtGamma);


  std::cout << "--- JPsi ---" << std::endl;
  // for heavy flavours
  LmCocktailMan* cocktmanJPsi = new LmCocktailMan();
  cocktmanJPsi->SetInputfiles(const_cast<char*>(JPsi_files[which_JPsi_files].Data()));
  cocktmanJPsi->SetInputlists(const_cast<char*>(JPsi_list[Which_JPsi_list].Data()));
  cocktmanJPsi->SetInputhistAndDim(const_cast<char*>(JPsi_histograms[which_JPsi_hists].Data()), 2); // 2D
  // cocktmanJPsi->SetRelUncertainties("+0.3:-0.4:+0.5:-0.3");
  std::cout << cockt00->GetNcoll() << std::endl;
  cocktmanJPsi->SetArbitraryScaling( 0.05961); // Branching ratio
  // cocktmanJPsi->SetArbitraryScaling( cockt00->GetNcoll() * 0.74 /** 62.8/64.5 */);
  cocktmanJPsi->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanJPsi->Process(LmCocktailMan::kJpsi);

  std::cout << "--- HEAVY FLAVOUR COCKTAIL ---" << std::endl;
  // for heavy flavours
  LmCocktailMan* cocktmanHeavyFl = new LmCocktailMan();
  cocktmanHeavyFl->SetInputfiles(const_cast<char*>(heavyfl_files[which_heavyfl_files].Data()));
  cocktmanHeavyFl->SetInputlists(const_cast<char*>(heavyfl_list.Data()));
  cocktmanHeavyFl->SetInputhistAndDim(const_cast<char*>(heavyfl_histograms[which_heavyfl_hists].Data()), 2); // 2D
  cocktmanHeavyFl->SetArbitraryScaling(2); // when using nquarks histogram instead of nevents, by which the yield gets downscaled about 2 times stronger.
  cocktmanHeavyFl->SetHistForNeventsHF(const_cast<char*>(heavyfl_hist_Nevents[which_heavyfl_hists].Data()));
  cocktmanHeavyFl->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanHeavyFl->Process(LmCocktailMan::kHeavyFl);

  LmCocktailMan* cocktmanCharm = new LmCocktailMan();
  cocktmanCharm->SetInputfiles(const_cast<char*>(heavyfl_files[which_charm_files].Data()));
  cocktmanCharm->SetInputlists(const_cast<char*>(heavyfl_charm[which_charm_list].Data()));
  cocktmanCharm->SetInputhistAndDim(const_cast<char*>(heavyfl_histograms[which_charm_hists].Data()), 2); // 2D
  cocktmanCharm->SetArbitraryScaling(2); // when using nquarks histogram instead of nevents, by which the yield gets downscaled about 2 times stronger.
  cocktmanCharm->SetNormMidRap(true);
  cocktmanCharm->SetHistForNeventsHF(const_cast<char*>(heavyfl_hist_Nevents[0].Data()));
  cocktmanCharm->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanCharm->Process(LmCocktailMan::kHeavyFl);
  //
  LmCocktailMan* cocktmanBeauty = new LmCocktailMan();
  cocktmanBeauty->SetInputfiles(const_cast<char*>(heavyfl_files[which_beauty_files].Data()));
  cocktmanBeauty->SetInputlists(const_cast<char*>(heavyfl_beauty.Data()));
  cocktmanBeauty->SetInputhistAndDim(const_cast<char*>(heavyfl_histograms[which_beauty_hists].Data()), 2); // 2D
  // cocktmanBeauty->SetArbitraryScaling(2 * 1.); // when using nquarks histogram instead of nevents, by which the yield gets downscaled about 2 times stronger.
  // cocktmanBeauty->SetArbitraryScaling(2 * 0.352); // when using nquarks histogram instead of nevents, by which the yield gets downscaled about 2 times stronger.
  cocktmanBeauty->SetArbitraryScaling(2); // when using nquarks histogram instead of nevents, by which the yield gets downscaled about 2 times stronger.
  // cocktmanBeauty->SetNormMidRap(true);
  cocktmanBeauty->SetHistForNeventsHF(const_cast<char*>(heavyfl_hist_Nevents[2].Data()));
  cocktmanBeauty->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanBeauty->Process(LmCocktailMan::kHeavyFl);

  cockt00->AttachManager( *cocktmanReso );
  // cockt00->AttachManager( *cocktmanResoWoEta );
  // cockt00->AttachManager( *cocktmanEta );


  // cockt00->AttachManager( *cocktmanHeavyFl ); // with total cross section scaled
  cockt00->AttachManager( *cocktmanCharm );
  cockt00->AttachManager( *cocktmanBeauty );
  cockt00->AttachManager( *cocktmanJPsi );
  // cockt00->AttachManager( *cocktmanVirtPhoton );


  cockt00->SetBRRelUncertainty        (LmCocktailPart::kPion, -0.0298, 0.0298);

  cockt00->SetMTscalingRelUncertainty (LmCocktailPart::kEta, -0.15, 0.05);
  cockt00->SetBRRelUncertainty        (LmCocktailPart::kEta, -0.058, 0.058);

  cockt00->SetMTscalingRelUncertainty (LmCocktailPart::kEtaPrime, -0.2, +0.2);
  cockt00->SetBRRelUncertainty        (LmCocktailPart::kEtaPrime, -0.0638, 0.0638);

  cockt00->SetMTscalingRelUncertainty (LmCocktailPart::kRho, -0.2, +0.2);
  cockt00->SetBRRelUncertainty        (LmCocktailPart::kRho, -0.011, 0.011);

  cockt00->SetMTscalingRelUncertainty (LmCocktailPart::kOmega, -0.2, +0.2);
  cockt00->SetBRRelUncertainty        (LmCocktailPart::kOmega, -0.0192, 0.0192);

  cockt00->SetMTscalingRelUncertainty (LmCocktailPart::kPhi, -0.3, +0.3);
  cockt00->SetBRRelUncertainty        (LmCocktailPart::kPhi, -0.0102, 0.0102);

  cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kJpsi, -0.3, +0.3);
  cockt00->SetBRRelUncertainty        (LmCocktailPart::kJpsi, -0.0054, 0.0054);
  // cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kCharm, -0.178, 0.178); // Use this when doing total cross section normalization; Measurement with +-7.8%

  cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kCharm, -0.1595, 0.1595); // Use this when doing dsigma/dy normalization; Measurement with +-10.2% syst + 8% scaling + 9.3% Ncoll == 15,95
  cockt00->SetBRRelUncertainty(LmCocktailPart::kCharm, -0.2408, 0.2408); // 24% BR + 2% weil nicht auf paar level normiert

  cockt00->SetAdditionalRelUncertainty(LmCocktailPart::kBeauty, -0.3278, 0.3278); // total cross section unc = 0.304 +- 8% scaling +- 9.3% NColl = 32.78%
  cockt00->SetBRRelUncertainty(LmCocktailPart::kBeauty, -0.07, 0.07);
  cockt00->PrintUncertainties();

  cockt00->Process(); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...

  // only needed if cocktail shall be projected and plotted stand-alone:
  cockt00->SetBinsPtee_forprojMee(binsPtee_forMee);
  cockt00->SetBinsMee_forprojPtee(binsMee_forPtee);
  cockt00->MakeSpectra1D(); // do projections according to attached binning.

  // cockt00->SetDrawStyle
  cockt00->SetDrawStyleErr("E3");
  // cockt00->WriteHist2D();
  return cockt00;
}


//_______________________________________________________________________________________________
void ProcessInputfiles(LmHandler* han_sys, LmHandler* han_ana)
{
  Printf("______ process input files ______");
  TBenchmark* bench = new TBenchmark();

  // Add all configs to LmFileManager for efficient file handling
  if (kDo200MeV == false){
    for (int ic=0; ic<n_config_pt400; ic++) {
      LmFileManager::Instance()->AddConfig( cconfig_pt400[ic] ); // regular
      LmFileManager::Instance()->AddConfig( cconfig_pt400[ic] ); // systematics
    }
  }
  if (kDo200MeV == true){
    for (int ic=0; ic<n_config_pt200; ic++) {
      LmFileManager::Instance()->AddConfig( cconfig_pt200[ic] ); // regular
      LmFileManager::Instance()->AddConfig( cconfig_pt200[ic] ); // systematics
    }
  }

  std::vector<LmManager*>    mgrVec, mgrVec_systematic;
  std::vector<LmBackground*> bkgVec, bkgVec_systematic;
  std::vector<LmSignal*>     sigVec, sigVec_systematic;
  std::vector<LmHandler*>    hanVec, hanVec_systematic;

  bench->Start("input_processing");
  if (kDo200MeV == false){
    ProcessSingleInputs(cconfig_pt400, "",
                      mgrVec,           bkgVec,           sigVec,
                      mgrVec_systematic,bkgVec_systematic,sigVec_systematic);
  }
  if (kDo200MeV == true){
    ProcessSingleInputs(cconfig_pt200, "",
                      mgrVec,           bkgVec,           sigVec,
                      mgrVec_systematic,bkgVec_systematic,sigVec_systematic);
  }
  Printf("______ DONE WITH SINGLE INPUT PROCESSING ______");
  bench->Show("input_processing");

  // Attach signals to the handlers which will be used in main function.
  if (kDo200MeV == false){
    for(Int_t iCuts = 0; iCuts < n_config_pt400; ++iCuts) {
      han_sys->AttachSignal(*sigVec_systematic.at(iCuts));
      han_ana->AttachSignal(*sigVec.at(iCuts));
    }
  }
  if (kDo200MeV == true){
    for(Int_t iCuts = 0; iCuts < n_config_pt200; ++iCuts) {
      han_sys->AttachSignal(*sigVec_systematic.at(iCuts));
      han_ana->AttachSignal(*sigVec.at(iCuts));
    }
  }

  // write most important histograms to rootfiles:
  // add bits of histograms you want to save: LmSignal::kSubSig+LmSignal::kSoverB+LmSignal::kSignif (to save all, use LmSignal::kMAXhist-1)
  // TFile* _fileOut2D_sys = new TFile(extpath_sys.Data(), "RECREATE");
  // han_sys->Write2DHist(LmSignal::kMAXhist-1, kFALSE, kTRUE);
  // _fileOut2D_sys->Close();
  // TFile* _fileOut2D_ana = new TFile(extpath_ana.Data(), "RECREATE");
  // han_ana->Write2DHist(LmSignal::kMAXhist-1, kFALSE, kTRUE);
  // _fileOut2D_ana->Close();

}

//____________________________________________________________________________________________
LmSignal* ProcessOneInput(LmManager* mgr)
{
  Printf("______ process one input ______");

  mgr->SetProjOption(projoption);
  mgr->SetEnableEffiCorr(kDoEffiCorrection);
  mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
  mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
  mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
  mgr->SetEnableExclusionCutZ(kDoPhiV);
  mgr->SetRebinning2D(mee_bin.size()-1, mee_bin.data(), n_ptee_bin, ptee_bin);
  // mgr->SetRebinning2D(n_mee_bin_4D, mee_bin_4D, n_ptee_bin, ptee_bin);
  mgr->Process();

  LmBackground* bkg = new LmBackground(*mgr, "bkg");
  bkg->SetUseRfactor(kUseRFactor);
  bkg->Process(LmBackground::kHybrid);

  LmSignal* sig = new LmSignal(*mgr, *bkg); // will take manager name (from caption[]), if no name is given.
  sig->Process(LmSignal::kStd);

  return sig;
}

void ProcessSingleInputs(TString config[], TString effiName,
                         std::vector<LmManager*> &mgrVec,     std::vector<LmBackground*> &bkgVec,     std::vector<LmSignal*> &sigVec,
                         std::vector<LmManager*> &mgrVec_sys, std::vector<LmBackground*> &bkgVec_sys, std::vector<LmSignal*> &sigVec_sys)
{
  Printf("______ process single inputs ______");
  if (effiName.IsNull()) {} // to avoid compiler warning

  if (kDo200MeV == false){
    for (int ic=0; ic<n_config_pt400; ic++) {
      Printf("config # %d:  %s", ic, config[ic].Data());

      LmManager* mgr = new LmManager(const_cast<char*>(config[ic].Data()));
      mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);

      mgr->SetProjOption(projoption);
      mgr->SetEnableEffiCorr(kDoEffiCorrection);
      mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
      mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
      mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);

      mgr->SetEnableExclusionCutZ(kDoPhiV);
      mgr->SetRebinning2D(mee_bin.size()-1, mee_bin.data(), n_ptee_bin, ptee_bin);
      mgr->Process();
      mgrVec.push_back(mgr);

      LmBackground* bkg = new LmBackground(*(mgrVec.at(ic)),Form("bg_cut_%02d",ic+1));
      bkg->SetUseRfactor(kUseRFactor);
      bkg->Process(LmBackground::kHybrid);
      bkgVec.push_back(bkg);

      LmSignal* sig = new LmSignal(*(mgrVec.at(ic)), *(bkgVec.at(ic))/*, Form("sig_cut_%02d",ic+1)*/); // will take manager name (from caption[]), if no name is given.
      sig->SetDoSignifRaw(kDoSignifRaw);
      sig->SetDoNormBinwidth(kDoNormBinwidth);
      sig->SetDoNormNevents(kDoNormNevents);
      sig->Process(LmSignal::kStd);
      sigVec.push_back(sig);

      LmManager* mgr_sys = new LmManager(const_cast<char*>(config[ic].Data()));
      mgr_sys->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);

      mgr_sys->SetProjOption(projoption);
      mgr_sys->SetEnableEffiCorr(kDoEffiCorrection);
      mgr_sys->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
      mgr_sys->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
      mgr_sys->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
      mgr_sys->SetEnableExclusionCutZ(kDoPhiV);
      mgr_sys->SetRebinning2D(n_mee_bin_systematic, mee_bin_systematic, n_ptee_bin_systematic, ptee_bin_systematic);
      mgr_sys->Process();
      mgrVec_sys.push_back(mgr_sys);

      LmBackground* bkg_sys = new LmBackground(*(mgrVec_sys.at(ic)),Form("bg_sys_cut_%02d",ic+1));
      bkg_sys->SetUseRfactor(kUseRFactor);
      bkg_sys->Process(LmBackground::kHybrid);
      bkgVec_sys.push_back(bkg_sys);

      // LmSignal* sig_sys = new LmSignal(*(mgrVec_sys.at(ic)), *(bkgVec_sys.at(ic)), Form("sig_sys_cut_%02d",ic+1));
      LmSignal* sig_sys = new LmSignal(*(mgrVec_sys.at(ic)), *(bkgVec_sys.at(ic)));
      sig_sys->SetDoSignifRaw(kDoSignifRaw);
      sig_sys->SetDoNormBinwidth(kDoNormBinwidth);
      sig_sys->SetDoNormNevents(kDoNormNevents);
      sig_sys->SetRebinning2D(mee_bin_systematic_coarse.size()-1, mee_bin_systematic_coarse.data(), ptee_bin_systematic_coarse.size()-1, ptee_bin_systematic_coarse.data());
      sig_sys->Process(LmSignal::kStd);
      sigVec_sys.push_back(sig_sys);
    }
  }
  if (kDo200MeV == true){
    TFile *_fTempl5 = 0x0;
    TH3D *hSig=0x0, *hCon=0x0, *hNorm=0x0;
    if (kDoPhiV>=LmManager::kTemplSub) { // if templates are needed
      _fTempl5 = LmHelper::SafelyOpenRootfile("./input/templates/template_conversions_cut5_pt200_0080.root");
      hSig       = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5, 0, "hUnlike");  hSig->SetName((kDoPref>0?"hSigPF":"hSig"));  // file 5 prompt
      hCon       = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5, 1, "hUnlike");  hCon->SetName("hCon");                // file 5 conversions
      hNorm = (TH3D*) hSig->Clone("hNorm");
      hNorm->Add(hCon);
    }
    for (int ic=0; ic<n_config_pt200; ic++) {
      Printf("config # %d:  %s", ic, config[ic].Data());

      LmManager* mgr = new LmManager(const_cast<char*>(config[ic].Data()));
      mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);

      mgr->SetProjOption(projoption);
      mgr->SetEnableEffiCorr(kDoEffiCorrection);
      mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
      mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
      mgr->SetTemplateNormRegionMin(n_cutPhiVbelow, cutPhiVbelow); // only needed for some template types.
      mgr->SetTemplateNormRegionMax(n_cutPhiVabove, cutPhiVabove); // only needed for some template types.
      mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
      if (kDoPhiV == LmManager::kTemplSub) mgr->SetExclusionZTemplates(hSig, 0x0, LmManager::kTemplSub, hSig, hNorm);

      mgr->SetEnableExclusionCutZ(kDoPhiV);
      mgr->SetRebinning2D(mee_bin.size()-1, mee_bin.data(), n_ptee_bin, ptee_bin);

      // Need to give phiV-corrected subtracted raw spectra to the manager before LmSignal::Process() is called.
      // Only then the LmManager::SignalPostCorrection(hSub) modifies the subtracted yield before SoverB and Signif are
      // computed from it. The difficulty is that the phiV template fit happens in 1D (projection binning of handler),
      // while the signal is processed in 2D (2D rebinning in (base)manager). Therefore use same binning (ptee_bin_4D)!
      TFile* _fPhiVcorr[100];
      std::vector<TH1D*> vhPhiVcorr;
      if (kDoPhiV==LmManager::kTemplSub) {
        for (int i=0; i<n_ptee_bin; ++i) {
          // _fPhiVcorr[i] = LmHelper::SafelyOpenRootfile(Form("./input/templates/cut5_pt200_0080_coarse_bins/spectra1D-phiVstud_ptee%.3fto%.3f.root",ptee_bin[i],ptee_bin[i+1]));
          _fPhiVcorr[i] = LmHelper::SafelyOpenRootfile(Form("./input/templates/cut5_pt200_0080/spectra1D-phiVstud_ptee%.3fto%.3f.root",ptee_bin[i],ptee_bin[i+1]));
          vhPhiVcorr.push_back( (TH1D*) LmHelper::GetHistFromTemplateFile(_fPhiVcorr[i], 4, "hSubSig-mee0.00to3.14", kFALSE) );
          vhPhiVcorr.at(i)->SetName(Form("hSubSig-ptee%.3fto%.3f",ptee_bin[i],ptee_bin[i+1]));
        }
        TH2D* hSubSig_phiVcorr = LmHelper::MakeHist2Dfrom1D(vhPhiVcorr, "hSubSig_phiVcorr", n_ptee_bin, ptee_bin);
        mgr->AddCorrectedSig(hSubSig_phiVcorr);

        TCanvas c5("c5", "", 800, 800);
        c5.SetLogz();
        c5.SetRightMargin(0.2);
        c5.SetLeftMargin(0.15);
        hSubSig_phiVcorr->Draw("colz");
        hSubSig_phiVcorr->SetAxisRange(0., 0.1, "X");
        c5.SaveAs("Corr_Map.pdf");
        delete hSubSig_phiVcorr;
      }
      mgr->Process();
      mgrVec.push_back(mgr);

      LmBackground* bkg = new LmBackground(*(mgrVec.at(ic)),Form("bg_cut_%02d",ic+1));
      bkg->SetUseRfactor(kUseRFactor);
      bkg->Process(LmBackground::kHybrid);
      bkgVec.push_back(bkg);

      LmSignal* sig = new LmSignal(*(mgrVec.at(ic)), *(bkgVec.at(ic))/*, Form("sig_cut_%02d",ic+1)*/); // will take manager name (from caption[]), if no name is given.
      sig->SetDoSignifRaw(kDoSignifRaw);
      sig->SetDoNormBinwidth(kDoNormBinwidth);
      sig->SetDoNormNevents(kDoNormNevents);
      sig->Process(LmSignal::kStd);
      sigVec.push_back(sig);

      LmManager* mgr_sys = new LmManager(const_cast<char*>(config[ic].Data()));
      mgr_sys->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);

      mgr_sys->SetProjOption(projoption);
      mgr_sys->SetEnableEffiCorr(kDoEffiCorrection);
      mgr_sys->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
      mgr_sys->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
      mgr_sys->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
      mgr_sys->SetEnableExclusionCutZ(kDoPhiV);
      mgr_sys->SetTemplateNormRegionMin(n_cutPhiVbelow, cutPhiVbelow); // only needed for some template types.
      mgr_sys->SetTemplateNormRegionMax(n_cutPhiVabove, cutPhiVabove); // only needed for some template types.
      if (kDoPhiV == LmManager::kTemplSub) mgr_sys->SetExclusionZTemplates(hSig, 0x0, LmManager::kTemplSub, hSig, hNorm);


      // Need to give phiV-corrected subtracted raw spectra to the manager before LmSignal::Process() is called.
      // Only then the LmManager::SignalPostCorrection(hSub) modifies the subtracted yield before SoverB and Signif are
      // computed from it. The difficulty is that the phiV template fit happens in 1D (projection binning of handler),
      // while the signal is processed in 2D (2D rebinning in (base)manager). Therefore use same binning (ptee_bin_4D)!
      TFile* _fPhiVcorr_sys[100];
      std::vector<TH1D*> vhPhiVcorr_sys;
      if (kDoPhiV==LmManager::kTemplSub) {
        for (int i=0; i<n_ptee_bin; ++i) {
          _fPhiVcorr_sys[i] = LmHelper::SafelyOpenRootfile(Form("./input/templates/cut5_pt200_0080/spectra1D-phiVstud_ptee%.3fto%.3f.root",ptee_bin[i],ptee_bin[i+1]));
          // _fPhiVcorr_sys[i] = LmHelper::SafelyOpenRootfile(Form("./input/templates/cut5_pt200_0080_coarse_bins/spectra1D-phiVstud_ptee%.3fto%.3f.root",ptee_bin[i],ptee_bin[i+1]));
          vhPhiVcorr_sys.push_back( (TH1D*) LmHelper::GetHistFromTemplateFile(_fPhiVcorr_sys[i], 0, "hSubSig-mee0.00to3.14", kFALSE) );
          vhPhiVcorr_sys.at(i)->SetName(Form("hSubSig-ptee%.3fto%.3f",ptee_bin[i],ptee_bin[i+1]));
        }
        TH2D* hSubSig_phiVcorr = LmHelper::MakeHist2Dfrom1D(vhPhiVcorr_sys, "hSubSig_phiVcorr", n_ptee_bin, ptee_bin);
        mgr_sys->AddCorrectedSig(hSubSig_phiVcorr);

        TCanvas c5("c5", "", 800, 800);
        c5.SetLogz();
        c5.SetRightMargin(0.2);
        c5.SetLeftMargin(0.15);
        hSubSig_phiVcorr->SetAxisRange(1e-6, 2e-1, "Z");
        hSubSig_phiVcorr->Draw("colz");
        hSubSig_phiVcorr->SetAxisRange(0., 0.1, "X");
        c5.SaveAs("Corr_Map.pdf");
        delete hSubSig_phiVcorr;
      }

      mgr_sys->SetRebinning2D(n_mee_bin_systematic, mee_bin_systematic, n_ptee_bin_systematic, ptee_bin_systematic);
      mgr_sys->Process();
      mgrVec_sys.push_back(mgr_sys);

      LmBackground* bkg_sys = new LmBackground(*(mgrVec_sys.at(ic)),Form("bg_sys_cut_%02d",ic+1));
      bkg_sys->SetUseRfactor(kUseRFactor);
      bkg_sys->Process(LmBackground::kHybrid);
      bkgVec_sys.push_back(bkg_sys);

      // LmSignal* sig_sys = new LmSignal(*(mgrVec_sys.at(ic)), *(bkgVec_sys.at(ic)), Form("sig_sys_cut_%02d",ic+1));
      LmSignal* sig_sys = new LmSignal(*(mgrVec_sys.at(ic)), *(bkgVec_sys.at(ic)));
      sig_sys->SetDoSignifRaw(kDoSignifRaw);
      sig_sys->SetDoNormBinwidth(kDoNormBinwidth);
      sig_sys->SetDoNormNevents(kDoNormNevents);
      sig_sys->SetRebinning2D(mee_bin_systematic_coarse.size()-1, mee_bin_systematic_coarse.data(), ptee_bin_systematic_coarse.size()-1, ptee_bin_systematic_coarse.data());
      sig_sys->Process(LmSignal::kStd);
      sigVec_sys.push_back(sig_sys);
    }

  }
}

enum LabelsTemplate{kNothing, kDefault, kPerformance};
TObjArray* GetLabelsTemplate(Int_t type=1, Double_t sizefac=-1)
{
  LmHelper::Info("New Labels");
  TObjArray* oaLabels = new TObjArray();
  oaLabels->SetOwner();
  TString sFigType = "";
  Double_t ratioPadSize  = 0.3;

  // const Double_t yref=0.82;
  Double_t xref = 0.575;
  // Double_t yi = yref;
  // Double_t yoff = 0;
  switch (type) {
    case kNothing:
      oaLabels = LmHelper::GetLabelsTemplate(LmHelper::kNone); // this leads to no labels being drawn.
      break;
    case kDefault:
      if (sizefac<0) sizefac=0.7;
      if (kDoRatio) sizefac /= (1.-ratioPadSize);
      oaLabels = LmHelper::GetLabelsTemplate(LmHelper::kDefault, sizefac, xref);
      // yi = yref;
      // sFigType = "ALICE Work in Progress";
      // // sFigType = "ALICE Performance";
      // oaLabels->Add( LmHelper::BuildTLatex(xref,yi+0.01,sFigType.Data(),"latFigType" ,sizefac) );  yi-=yoff;
      // oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCollsyst",sizefac) );  yi-=yoff;
      // oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCutsEle" ,sizefac) );  yi-=yoff;
      // oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts2Dim",sizefac) );  yi-=yoff;
      // oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts3Dim",sizefac) );  yi-=yoff;
      break;
    case kPerformance:
      if (sizefac<0) sizefac=0.7 * 1.2;
      if (kDoRatio) sizefac /= (1.-ratioPadSize);
      xref = 0.55;
      oaLabels = LmHelper::GetLabelsTemplate(LmHelper::kPerformance, sizefac, xref);
      // yi = yref;
      // // sFigType = "ALICE Work in Progress";
      // sFigType = "ALICE Performance";
      // oaLabels->Add( LmHelper::BuildTLatex(xref,yi+0.01,sFigType.Data(),"latFigType" ,sizefac) );  yi-=yoff;
      // oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCollsyst",sizefac) );  yi-=yoff;
      // oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCutsEle" ,sizefac) );  yi-=yoff;
      // oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts2Dim",sizefac) );  yi-=yoff;
      // oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts3Dim",sizefac) );  yi-=yoff;
      break;
  }
  return oaLabels;
}
