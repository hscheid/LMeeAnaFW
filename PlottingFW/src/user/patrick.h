// input data files. make sure to edit the other strings accordingly!
TString name[] = {
  "./input/PbPb/data/LMEEoutput-272PrelSemi-2low.root",   // (0)+(9)+(10) 0 = QM2014 output
  "./input/PbPb/data/LMEEoutput-272PrelSemi-3hig.root",   //     inputhist("InvMass_PairPt_PhivPair")
  "./input/PbPb/data/LMEEoutput-272PrelSemi-1full.root", 
  "./input/PbPb/data/LMEEoutput-311-2low.root",  // (1) Prefilter SPDfirst 1 (m<20, theta<50)
  "./input/PbPb/data/LMEEoutput-311-3hig.root",  //     inputhist("InvMass_PairPt_PhivPair")
  "./input/PbPb/data/LMEEoutput-311-1full.root", 
  "./input/PbPb/data/LMEEoutput-316-2low.root",  // (2) Prefilter SPDorSDD 1 (m<20, theta<50)
  "./input/PbPb/data/LMEEoutput-316-3hig.root",  //     changed inputhist("pInvMass_PairPt_PhivPair")! changed to variable binning!
  "./input/PbPb/data/LMEEoutput-316-1full.root", 
  "./input/PbPb/data/LMEEoutput-319-2low.root",  // (3) Prefilter SPDfirst 2 (m<30, theta<60)
  "./input/PbPb/data/LMEEoutput-319-3hig.root",  
  "./input/PbPb/data/LMEEoutput-319-1full.root", 
  "./input/PbPb/data/LMEEoutput-347-2low.root",  // (4) like Preliminary, but with TPC eta correction.
  "./input/PbPb/data/LMEEoutput-347-3hig.root",  
  "./input/PbPb/data/LMEEoutput-347-1full.root", 
  "./input/PbPb/data/LMEEoutput-480-2low.root",  // (5)+(6) Prefilter SPDfirst 3 (m<50, theta<80) + SPDorSDD 2 (m<10, theta<30)
  "./input/PbPb/data/LMEEoutput-480-3hig.root",  
  "./input/PbPb/data/LMEEoutput-480-1full.root", 
  "./input/PbPb/data/LMEEoutput-483-2low.root",  // (7)+(8) SPDfirst+V0 () + SPDorSDD+V0 ()
  "./input/PbPb/data/LMEEoutput-483-3hig.root",  
  "./input/PbPb/data/LMEEoutput-483-1full.root", 
  "./input/PbPb/data/LMEEoutput-279-2low.root",  // (11)+(12) SPDorSDD  ( name[21] )
  "./input/PbPb/data/LMEEoutput-279-3hig.root",  //     inputhist("InvMass_PairPt_PhivPair")
  "./input/PbPb/data/LMEEoutput-279-1full.root", 
  "./input/PbPb/data/LMEEoutput-268PrelCent-2low.root", // (13) QM2014 output
  "./input/PbPb/data/LMEEoutput-268PrelCent-3hig.root", //      inputhist("InvMass_PairPt_PhivPair")
  "./input/PbPb/data/LMEEoutput-268PrelCent-1full.root",
  "./input/PbPb/data/LMEEoutput-484-2low.root", // (14) 10-50% Centrality, standard setting like QM2014
  "./input/PbPb/data/LMEEoutput-484-3hig.root",
  "./input/PbPb/data/LMEEoutput-484-1full.root",
  "./input/PbPb/data/LMEEoutput-488-2low.root", // (15)+(16) 10-50% Prefilter (m<40, theta<80) + (phiv>2.36, m<40)
  "./input/PbPb/data/LMEEoutput-488-3hig.root",
  "./input/PbPb/data/LMEEoutput-488-1full.root",
  "./input/PbPb/data/LMEEoutput-489-2low.root", // (17)+(18) 10-50% Prefilter (m<60, theta<100) + (phiv>1.57, m<60)
  "./input/PbPb/data/LMEEoutput-489-3hig.root",
  "./input/PbPb/data/LMEEoutput-489-1full.root",
  "./input/PbPb/data/LMEEoutput-490-2low.root", // (19)+(20) Random daughter check: 10-50% Prefilter (m<40, theta<80) + standard setting
  "./input/PbPb/data/LMEEoutput-490-3hig.root",
  "./input/PbPb/data/LMEEoutput-490-1full.root",
  "./input/PbPb/data/LMEEoutput-494-2low.root", // (21)-(24) pt>200 MeV + pt>400 MeV + pair cuts, with new dE/dx corrections ITS+TPC
  "./input/PbPb/data/LMEEoutput-494-3hig.root",
  "./input/PbPb/data/LMEEoutput-494-1full.root",
  "./input/PbPb/data/LMEEoutput-495-2low.root", // (25)-(31) pt>200 MeV, pair cuts only theta, + prefilter
  "./input/PbPb/data/LMEEoutput-495-3hig.root",
  "./input/PbPb/data/LMEEoutput-495-1full.root",
  "./input/PbPb/data/LMEEoutput-496-2low.root", // (32)-(38) pt>400 MeV, pair cuts only theta, + prefilter
  "./input/PbPb/data/LMEEoutput-496-3hig.root",
  "./input/PbPb/data/LMEEoutput-496-1full.root",
//  "./input/PbPb/data_syst/cut01-cent/LMEEoutput-2low.root", // (cut01 cent, train 532)
//  "./input/PbPb/data_syst/cut01-cent/LMEEoutput-3hig.root",
//  "./input/PbPb/data_syst/cut01-cent/LMEEoutput-1full.root",
//  "./input/PbPb/data_syst/cut01-semi/LMEEoutput-2low.root", // (cut01 semi, train 531)
//  "./input/PbPb/data_syst/cut01-semi/LMEEoutput-3hig.root",
//  "./input/PbPb/data_syst/cut01-semi/LMEEoutput-1full.root",
  "./input/PbPb/data_syst/cut16-cent/LMEEoutput-2low.root", // (cut16 cent)
  "./input/PbPb/data_syst/cut16-cent/LMEEoutput-3hig.root",
  "./input/PbPb/data_syst/cut16-cent/LMEEoutput-1full.root",
  "./input/PbPb/data_syst/cut16-semi/LMEEoutput-2low.root", // (cut16 semi)
  "./input/PbPb/data_syst/cut16-semi/LMEEoutput-3hig.root",
  "./input/PbPb/data_syst/cut16-semi/LMEEoutput-1full.root",
  "./input/PbPb/data_4D_merged/LMEEoutput-cent-ESD-cut16-2low.root", // (with+without ITScuts, pt200+pt400)
  "./input/PbPb/data_4D_merged/LMEEoutput-cent-ESD-cut16-1hig.root",
  "", // full
  "./input/PbPb/data_4D_merged/LMEEoutput-semi-ESD-cut16-2low.root", // (with+without ITScuts, pt200+pt400)
  "./input/PbPb/data_4D_merged/LMEEoutput-semi-ESD-cut16-1hig.root",
  "", // full
  "./input/PbPb/data_4D/cut16-cent-AOD-2pref/LMEEoutput-2low.root", // (w/o + w/ 2 prefilters (m<40, t<80 / phiV>2.36, m<40), pt200+pt400)
  "./input/PbPb/data_4D/cut16-cent-AOD-2pref/LMEEoutput-3hig.root",
  "./input/PbPb/data_4D/cut16-cent-AOD-2pref/LMEEoutput-1full.root",
  "./input/PbPb/data_4D/cut16-semi-AOD-2pref/LMEEoutput-2low.root", // (w/o + w/ 2 prefilters (m<40, t<80 / phiV>2.36, m<40), pt200+pt400)
  "./input/PbPb/data_4D/cut16-semi-AOD-2pref/LMEEoutput-3hig.root",
  "./input/PbPb/data_4D/cut16-semi-AOD-2pref/LMEEoutput-1full.root",
  ""
};
// corresponding input efficiency files
TString effi_name[] = {
  //"./input/charm-eff05-17h.root",     // old. 272, 347
  //"./input/charm-eff07-17g.root",     // old. central
  "../PairEffCalc/output/old/pairEff_raw-17h-std.root", // 272, 347 (20-50%)
  "../PairEffCalc/output/old/pairEff_raw-17g-std.root", // central
  "../PairEffCalc/output/old/pairEff_raw-1050-std+RandRej_0to3-1000-50.root", // std, std+randomrej (10-50%)
  "../PairEffCalc/output/measurable/pairEff_raw-0010-pt200.root", // [3]
  "../PairEffCalc/output/measurable/pairEff_raw-0010-pt400.root",
  "../PairEffCalc/output/measurable/pairEff_raw-1050-pt200.root",
  "../PairEffCalc/output/measurable/pairEff_raw-1050-pt400.root",
  "../PairEffCalc/output/measurable+ITScuts/pairEff_raw-0010-pt200.root", // [7]
  "../PairEffCalc/output/measurable+ITScuts/pairEff_raw-0010-pt400.root",
  "../PairEffCalc/output/measurable+ITScuts/pairEff_raw-1050-pt200.root",
  "../PairEffCalc/output/measurable+ITScuts/pairEff_raw-1050-pt400.root",
  ""
};
// name of 2D generated and reconstructed histogram
//TString effi_gen[] = {"meePairPt_Eta076_raw"};
//TString effi_rec[] = {"meePairPt_PID2_e", "meePairPt_PID2_e"}; // old. same for Semi and Cent Prel outputs.
TString effi_gen[]     = {"hNGenPairs_pt400",
  "NGenPairs_pt200_3500"          , "NGenPairs_pt400_3500",           // measurable effi. same name with or without ITS cuts.
  "NGenPairs_pt200_3500_opAngle50", "NGenPairs_pt400_3500_opAngle50", // with opening angle cut.
  ""
};
TString effi_rec_old[] = {"Npair_hEff_Nreco_Ele_ITSTPCTOFif_trkSPDfirst_1_pt400"}; // mid-old std
TString effi_rec[]     = {"Npair_hEff_ITSTPCTOFif_trkSPDfirst_1_pt400", // std
  "Npair_hEff_ITSTPCTOFif_trkSPDfirst_1_rej_ITSTPCTOFif_trkSPDfirst_1_PrefAllm40t80_pt400",  "Npair_hEff_ITSTPCTOFif_trkSPDfirst_1_rej_ITSTPCTOFif_trkSPDfirst_1_PrefAllp236m40_pt400",  //(15)+(16) 488
  "Npair_hEff_ITSTPCTOFif_trkSPDfirst_1_rej_ITSTPCTOFif_trkSPDfirst_1_PrefAllm60t100_pt400", "Npair_hEff_ITSTPCTOFif_trkSPDfirst_1_rej_ITSTPCTOFif_trkSPDfirst_1_PrefAllp157m60_pt400",  //(17)+(18) 489
  "NRecPairs_hEff_Ele_cut16_SPDorSDD14_PID16_pt200_3500"                  , "NRecPairs_hEff_Ele_cut16_SPDorSDD14_PID16_pt400_3500", // [5],[6]        // measurable effi.
  "NRecPairs_hEff_Ele_cut16_SPDorSDD14_PID16_pt200_3500_opAngle50"        , "NRecPairs_hEff_Ele_cut16_SPDorSDD14_PID16_pt400_3500_opAngle50",         // with opening angle cut.
  "NRecPairsCombined_hEff_Ele_cut16_SPDorSDD14_PID16_pt200_3500"          , "NRecPairsCombined_hEff_Ele_cut16_SPDorSDD14_PID16_pt400_3500",           // prefilter. no opening angle cut.
  "NRecPairsCombined_hEff_Ele_cut16_SPDorSDD14_PID16_pt200_3500_opAngle50", "NRecPairsCombined_hEff_Ele_cut16_SPDorSDD14_PID16_pt400_3500_opAngle50", // prefilter.
  "NRecPairs_hEff_Ele_cut16_SPDorSDD14_PID16_ITScuts_pt200_3500"                  , "NRecPairs_hEff_Ele_cut16_SPDorSDD14_PID16_ITScuts_pt400_3500",   // [13],[14]    // ITS cuts. measurable effi.
  "NRecPairs_hEff_Ele_cut16_SPDorSDD14_PID16_ITScuts_pt200_3500_opAngle50"        , "NRecPairs_hEff_Ele_cut16_SPDorSDD14_PID16_ITScuts_pt400_3500_opAngle50",         // with opening angle cut.
  "NRecPairsCombined_hEff_Ele_cut16_SPDorSDD14_PID16_ITScuts_pt200_3500"          , "NRecPairsCombined_hEff_Ele_cut16_SPDorSDD14_PID16_ITScuts_pt400_3500",           // prefilter. no opening angle cut.
  "NRecPairsCombined_hEff_Ele_cut16_SPDorSDD14_PID16_ITScuts_pt200_3500_opAngle50", "NRecPairsCombined_hEff_Ele_cut16_SPDorSDD14_PID16_ITScuts_pt400_3500_opAngle50", // prefilter.
  ""
};
TString effi_rec_syst[] = {"Npair_hEff_ITSTPCTOFif_trkSPDfirst_1_pt400", // syst
  ""
};
//
// further details of input data
TString tree_name[] = { "reichelt_LMEEPbPb2011_out", "reichelt_LMEEPbPb2011_out_nr2", "reichelt_LMEEPbPb2011_out_nr3" }; // extend when comparing PR with CK!
TString cut_setting[] = { // always adapt to input data files!
  "ITSTPCTOFif_trkSPDfirst_1_kSemi",   // (0) 272
  "ITSTPCTOFif_trkSPDfirst_1_PrefAll", // (1) 311
  "ITSTPCTOFif_trkSPDorSDD_1_PrefAll", // (2) 316
  "ITSTPCTOFif_trkSPDfirst_1_PrefAll", // (3) 319
  "ITSTPCTOFif_trkSPDfirst_1_kSemi",   // (4) 347
  "ITSTPCTOFif_trkSPDfirst_1_PrefAllm50t80", "ITSTPCTOFif_trkSPDorSDD_1_PrefAllm10t30", // (5)+(6) 480
  "ITSTPCTOFif_trkSPDfirst_7_V0excl", "ITSTPCTOFif_trkSPDorSDD_7_V0excl",               // (7)+(8) 483
  "ITSTPCTOFif_trkSPDfirst5cls_4_kSemi", "ITS2gevTPCTOFif_trkSPDfirst_5_tight_kSemi",   // (9)+(10) 272
  "ITSTPCTOFif_trkSPD5orSDD4cls_4_kSemi", "ITS2gevTPCTOFif_trkSPDorSDD_5_tight_kSemi",  //(11)+(12) 279
  "ITSTPCTOFif_trkSPDfirst_1_kCent", // (13) 268
  "ITSTPCTOFif_trkSPDfirst_1_10to50", // (14) 484
  "ITSTPCTOFif_trkSPDfirst_1_PrefAllm40t80", "ITSTPCTOFif_trkSPDfirst_1_PrefAllp236m40",  //(15)+(16) 488
  "ITSTPCTOFif_trkSPDfirst_1_PrefAllm60t100", "ITSTPCTOFif_trkSPDfirst_1_PrefAllp157m60",  //(17)+(18) 489
  "ITSTPCTOFif_trkSPDfirst_1_PrefAllm40t80_rndmDau", "ITSTPCTOFif_trkSPDfirst_1_rndmDau",  //(19)+(20) 490
  "PID1_SPDfirst1_pt200_PairCutm20t20", "PID1_SPDfirst1_pt200_PairCutp236m100",   // (21)+(22) 494
  "PID1_SPDfirst1_pt400_PairCutm20t20", "PID1_SPDfirst1_pt400_PairCutp236m100",   // (23)+(24) 494
  "PID1_SPDfirst1_pt200", "PID1_SPDfirst1_pt200_PairCutt20",              // (25)+(26) 495
  "PID1_SPDfirst1_pt200_PairCutt50", "PID1_SPDfirst1_pt200_PairCutt100",  // (27)+(28) 495
  "PID1_SPDfirst1_PrefAllm20t20_pt200_PairCutt20",                        // (29) 495
  "PID1_SPDfirst1_PrefAllm40t80_pt200_PairCutt20",                        // (30) 495
  "PID1_SPDfirst1_PrefAllp236m40_pt200_PairCutt20",                       // (31) 495
  "PID1_SPDfirst1_pt400", "PID1_SPDfirst1_pt400_PairCutt20",              // (32)+(33) 496
  "PID1_SPDfirst1_pt400_PairCutt50", "PID1_SPDfirst1_pt400_PairCutt100",  // (34)+(35) 496
  "PID1_SPDfirst1_PrefAllm40t80_pt400_PairCutt20",                        // (36) 496
  "PID1_SPDfirst1_PrefAllm60t100_pt400_PairCutt20",                       // (37) 496
  "PID1_SPDfirst1_PrefAllp236m40_pt400_PairCutt20",                       // (38) 496
//  "cut01_SPD1_PID1_pt200",                                // (39)
//  "cut01_SPD1_PID1_pt400",                                // (40)
//  "cut01_SPD1_PID1_Pref_pt200",                           // (41)
//  "cut01_SPD1_PID1_Pref_pt400",                           // (42)
  "cut16_SPDorSDD14_PID16_pt200",                                // (39)
  "cut16_SPDorSDD14_PID16_pt400",                                // (40)
  "cut16_SPDorSDD14_PID16_Pref_pt200",                           // (41)
  "cut16_SPDorSDD14_PID16_Pref_pt400",                           // (42)
  "cut16_SPDorSDD14_PID16_PrefPhiV_pt200",                       // (43)
  "cut16_SPDorSDD14_PID16_PrefPhiV_pt400",                       // (44)
  "cut16_ITScuts_pt200",      // ESD                             // (45)
  "cut16_ITScuts_pt400",      // ESD                             // (46)
  "cut16_ITScuts_Pref_pt200", // ESD                             // (47)
  "cut16_ITScuts_Pref_pt400", // ESD                             // (48)
  ""
};
TString nameMC[] = {
  "./input/PbPb/MC/LMEEoutput-MC007-1full.root",
  "./input/PbPb/MC/LMEEoutput-MC007-2low.root",
  "./input/PbPb/MC/LMEEoutput-MC007-3hig.root",
  "./input/PbPb/MC/noPC-cent/LMEEoutput-1full.root", // (#3) // cut01, cut16, and pure prefilter. cut16 superseeded by #27 ff. ("MC_4D/moreSignals")
  "./input/PbPb/MC/noPC-cent/LMEEoutput-2low.root",
  "./input/PbPb/MC/noPC-cent/LMEEoutput-3hig.root",
  "./input/PbPb/MC/noPC-semi/LMEEoutput-1full.root",
  "./input/PbPb/MC/noPC-semi/LMEEoutput-2low.root",
  "./input/PbPb/MC/noPC-semi/LMEEoutput-3hig.root",
  "./input/PbPb/MC/cut16-cent/LMEEoutput-1full.root", // (#9)
  "./input/PbPb/MC/cut16-cent/LMEEoutput-2low.root",
  "./input/PbPb/MC/cut16-cent/LMEEoutput-3hig.root",
  "./input/PbPb/MC/cut16-semi/LMEEoutput-1full.root",
  "./input/PbPb/MC/cut16-semi/LMEEoutput-2low.root",
  "./input/PbPb/MC/cut16-semi/LMEEoutput-3hig.root",
  "./input/PbPb/MC/cut16-cent-noConv/LMEEoutput-1full.root", // (#15)
  "./input/PbPb/MC/cut16-cent-noConv/LMEEoutput-2low.root",
  "./input/PbPb/MC/cut16-cent-noConv/LMEEoutput-3hig.root",
  "./input/PbPb/MC/cut16-semi-noConv/LMEEoutput-1full.root",
  "./input/PbPb/MC/cut16-semi-noConv/LMEEoutput-2low.root",
  "./input/PbPb/MC/cut16-semi-noConv/LMEEoutput-3hig.root",
  "./input/PbPb/MC_4D/bothTasks-ITShists-cent/LMEEoutput-1full.root", // (#21)
  "./input/PbPb/MC_4D/bothTasks-ITShists-cent/LMEEoutput-2low.root",
  "./input/PbPb/MC_4D/bothTasks-ITShists-cent/LMEEoutput-3hig.root",
  "./input/PbPb/MC_4D/bothTasks-ITShists-semi/LMEEoutput-1full.root",
  "./input/PbPb/MC_4D/bothTasks-ITShists-semi/LMEEoutput-2low.root",
  "./input/PbPb/MC_4D/bothTasks-ITShists-semi/LMEEoutput-3hig.root",
//  "./input/PbPb/MC_4D/bothTasks-moreSignals-cent/LMEEoutput-1full.root", // (#27) // only 1/3 of the statistics of #3 ff.
//  "./input/PbPb/MC_4D/bothTasks-moreSignals-cent/LMEEoutput-2low.root",
//  "./input/PbPb/MC_4D/bothTasks-moreSignals-cent/LMEEoutput-3hig.root",
//  "./input/PbPb/MC_4D/bothTasks-moreSignals-semi/LMEEoutput-1full.root",
//  "./input/PbPb/MC_4D/bothTasks-moreSignals-semi/LMEEoutput-2low.root",
//  "./input/PbPb/MC_4D/bothTasks-moreSignals-semi/LMEEoutput-3hig.root",
  "./input/PbPb/MC_4D/moreSignals+LS-cent/LMEEoutput-1full.root", // (#27) // w/o + w/ 2 prefilters (m<40, t<80 / phiV>2.36, m<40). ~same stat as #3 ff.
  "./input/PbPb/MC_4D/moreSignals+LS-cent/LMEEoutput-2low.root",
  "./input/PbPb/MC_4D/moreSignals+LS-cent/LMEEoutput-3hig.root",
  "./input/PbPb/MC_4D/moreSignals+LS-semi/LMEEoutput-1full.root",
  "./input/PbPb/MC_4D/moreSignals+LS-semi/LMEEoutput-2low.root",
  "./input/PbPb/MC_4D/moreSignals+LS-semi/LMEEoutput-3hig.root",
  // MC has no Mixing -> no R factor so far!
  ""
};
TString cut_settingMC[] = { // always adapt to input data files!
  "MC_TPCITSif2_FilterBit0_pt50", // (0)
  "MC_PID1_SPDfirst_pt200", // (1)
  "MC_PID1_SPDorSDD_pt200", // (2)
  "MC_PID1_SPDfirst_pt400", // (3)
  "MC_PID1_SPDfirst_pt400/Pair_MCpair_sameMother", // (4)
  "MC_PID1_SPDfirst_pt400/Pair_MCpair_diffMother", // (5)
  "MC_PID1_SPDorSDD_pt400", // (6)
  "MC_TPCITSif2_FilterBit0_pt50_noPairCut", // (7) noPC files
  "MC_cut01_pt200_noPairCut", "MC_cut01_pt400_noPairCut", //  (8)+ (9) noPC files
  "MC_cut16_pt200_noPairCut", "MC_cut16_pt400_noPairCut", // (10)+(11) noPC files
  "MC_cut16_SPDorSDD14_PID16_pt200",          "MC_cut16_SPDorSDD14_PID16_pt400",      // (12)+(13) cut16 files
  "MC_cut16_SPDorSDD14_PID16_Pref_pt200",     "MC_cut16_SPDorSDD14_PID16_Pref_pt400", // (14)+(15) cut16 files
  "MC_cut16_SPDorSDD14_PID16_PrefPhiV_pt200", "MC_cut16_SPDorSDD14_PID16_PrefPhiV_pt400", // (16)+(17)
  "MC_cut16_noConv_pt200",      "MC_cut16_noConv_pt400",      // (18)+(19)
  "MC_cut16_noConv_Pref_pt200", "MC_cut16_noConv_Pref_pt400", // (20)+(21)
  ""
};
TString pairMC[] = { "", "/Pair_MCpair_sameMother", "/Pair_MCpair_diffMother/ULS", "/Pair_MCpair_sameGamma", // 0-3
  "/Pair_MCpair_diffM_oneGamma/ULS", "/Pair_MCpair_diffGamma/ULS", "/Pair_MCpair_HadronCont/ULS", // 4-6
  "/Pair_MCpair_diffM_oneGamma/ULS/Pair_MCpair_diffM_oneGamma_LSpp/Pair_MCpair_diffM_oneGamma_LSmm", // multiple MC signal for ULS and LS++/--
  "/Pair_MCpair_diffGamma/ULS/Pair_MCpair_diffGamma_LSpp/Pair_MCpair_diffGamma_LSmm", // multiple MC signal for ULS and LS++/--
  "/Pair_MCpair_HadronCont/ULS/Pair_MCpair_HadronCont_LSpp/Pair_MCpair_HadronCont_LSmm", // multiple MC signal for ULS and LS++/--
  ""
};
//
// cocktail files
TString cocktail_files[] = { // TODO: implement correct scaling if files have different centrality percentiles!!!
  // if this order here is changed, then check the use of 'which_cockt_files' in <main>.cpp file!!!
  "./input/cocktail_PbPb_0010.root",
  "./input/cocktail_PbPb_2030.root:./input/cocktail_PbPb_3040.root:./input/cocktail_PbPb_4050.root",
  "./input/cocktail_PbPb_1020.root:./input/cocktail_PbPb_2030.root:./input/cocktail_PbPb_3040.root:./input/cocktail_PbPb_4050.root",
};
// cocktail histograms
TString cocktail_histograms[] = {
  "pteevsmeePion:pteevsmeeEta:pteevsmeeEtaPrime:pteevsmeeRho:pteevsmeeOmega:pteevsmeeOmegaDalitz:pteevsmeePhi:pteevsmeePhiDalitz", //:pteevsmeeJPsi
  "pteevsmeePion:pteevsmeeEta:pteevsmeeEtaPrime:pteevsmeeOmega:pteevsmeeOmegaDalitz", // for tests
};
// heavy flavour files
TString heavyfl_files[] = {
  "./input/charm_PbPb_201403_BsE.root"
};
// heavy flavour histograms
TString heavyfl_histograms[] = {
  "hpt_mass4"
};
// heavy flavour histograms for nevents
TString heavyfl_hist_Nevents[] = {
  "hee_c"
};
Int_t   which_cockt_files = 0; // 0=Central, 1=Semi_2050, 2=Semi_1050, see cocktail_files[] above!
Int_t   which_cockt_hists = 0;
Int_t   which_heavyfl_files = 0;
Int_t   which_heavyfl_hists = 0;
// text for legend and maybe signal name
TString caption[] = { // do not use a colon(:)!
  "Tech. Prel. QM14",             // (0) 272
  "SPDfirst 1, m<20, #theta<50",  // (1) 311
  "SPDorSDD 1, m<20, #theta<50",  // (2) 316
  "SPDfirst 2, m<30, #theta<60",  // (3) 319
  "Tech.Prel.+dE/dx-corr.",       // (4) 347
  "SPDfirst 3, m<50, #theta<80",  // (5) 480
  "SPDorSDD 2, m<10, #theta<30",  // (6) 480
  "SPDfirst, V0cut",              // (7) 483
  "SPDorSDD, V0cut",              // (8) 483
  "SPDfirst, 5 ITS clu",          // (9) 272 syst
  "SPDfirst, tighter PID",        // (10) 272 syst
  "SPDorSDD, 5(4) ITS clu",       // (11) 279 syst
  "SPDorSDD, tighter PID",        // (12) 279 syst
  "Tech. Prel. QM14 0-10%",       // (13) 268 central std
  "T.P. cuts, 10-50% (no Pref.)",   // (14) 484 - Like Sign PhiV not yet flipped!
  "T.P., Pref. m<40 #theta<80",     // (15) 488
  "T.P., Pref. #phi_{V}>2.36 m<40", // (16) 488
  "T.P., Pref. m<60 #theta<100",    // (17) 489
  "T.P., Pref. #phi_{V}>1.57 m<60", // (18) 489
  "T.P., Pref. (rndm legs)",   // (19) 490 // compare to 15
  "T.P., no Pref.(rndm legs)", // (20) 490 // compare to 14
  "P.c. m<20 #theta<20, p_{T}>200",       // (21) 494
  "P.c. #phi_{V}>2.36 m<100, p_{T}>200",  // (22) 494
  "P.c. m<20 #theta<20, p_{T}>400",       // (23) 494
  "P.c. #phi_{V}>2.36 m<100, p_{T}>400",  // (24) 494
  "no Paircuts, p_{T}>200",                               // (25) 495
  "P.c. #theta<20, p_{T}>200",                            // (26) 495
  "P.c. #theta<50, p_{T}>200",                            // (27) 495
  "P.c. #theta<100, p_{T}>200",                           // (28) 495
  "Pref. m<20 #theta<20, P.c. #theta<20, p_{T}>200",      // (29) 495
  "Pref. m<40 #theta<80, P.c. #theta<20, p_{T}>200",      // (30) 495
  "Pref. #phi_{V}>2.36 m<40, P.c. #theta<20, p_{T}>200",  // (31) 495
  "no Paircuts, p_{T}>400",                               // (32) 496
  "P.c. #theta<20, p_{T}>400",                            // (33) 496
  "P.c. #theta<50, p_{T}>400",                            // (34) 496
  "P.c. #theta<100, p_{T}>400",                           // (35) 496
  "Pref. m<40 #theta<80, P.c. #theta<20, p_{T}>400",      // (36) 496
  "Pref. m<60 #theta<100, P.c. #theta<20, p_{T}>400",     // (37) 496
  "Pref. #phi_{V}>2.36 m<40, P.c. #theta<20, p_{T}>400",  // (38) 496
//  "cut01 p_{T}>200",                                // (39)
//  "cut01 p_{T}>400",                                // (40)
//  "cut01 Pref., p_{T}>200",                         // (41)
//  "cut01 Pref., p_{T}>400",                         // (42)
  "cut16 p_{T}>200",                                // (39)
  "cut16 p_{T}>400",                                // (40)
  "cut16 Pref., p_{T}>200",                         // (41)
  "cut16 Pref., p_{T}>400",                         // (42)
  "cut16+ITScuts, p_{T}>200",                       // (43)
  "cut16+ITScuts, p_{T}>400",                       // (44)
  "cut16+ITScuts Pref., p_{T}>200",                 // (45)
  "cut16+ITScuts Pref., p_{T}>400",                 // (46)
  ""
};

//_______________________________________________________________________________________________
// config string for manager
std::vector<TString> cconfig; // filled in FillConfig().
std::vector<Int_t>   phiVtype; // filled in FillConfig().
Int_t n_config=0;

//_______________________________________________________________________________________________
void FillConfig(TString sArg)
{
  if (sArg.EqualTo("ana")) { // Analysis
  // low + hig:
    cconfig.push_back(coll_system + ":" + name[  60+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_setting[39+kDoPt400+2*kDoPref]  + ":" + "data, no #it{#phi}_{V} corr." );  // AOD 4D, cut16
    cconfig.push_back(coll_system + ":" + name[  61+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_setting[39+kDoPt400+2*kDoPref]  + ":" + "data, no #it{#phi}_{V} corr." );  // AOD 4D, cut16
    phiVtype.push_back(LmManager::kNoCut);  phiVtype.push_back(LmManager::kNoCut);
    cconfig.push_back(coll_system + ":" + name[  60+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_setting[39+kDoPt400+2*kDoPref]  + ":" + "data + #it{#phi}_{V} templ." );  // AOD 4D, cut16
    cconfig.push_back(coll_system + ":" + name[  61+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_setting[39+kDoPt400+2*kDoPref]  + ":" + "data + #it{#phi}_{V} templ." );  // AOD 4D, cut16
    phiVtype.push_back(LmManager::kTemplSub);  phiVtype.push_back(LmManager::kTemplSub);
  }
  
  if (sArg.EqualTo("stud") ) { // PhiV study
    // --------------------------------------------------
    // The first entry is not added to the handler for drawing, duplicate it if needed.
    cconfig.push_back(coll_system + ":" + name[  62+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_setting[39+kDoPt400+2*kDoPref]  + ":" + "data" );  // AOD 4D, cut16 // "data, no #it{#phi}_{V} corr."
    phiVtype.push_back(LmManager::kNoCut);
    // --------------------------------------------------
    //  cconfig.push_back(coll_system + ":" + nameMC[27+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[0] + ":" + "MC"           ); // MC 4D, cut16
    //  phiVtype.push_back(LmManager::kNoCut);
    cconfig.push_back(coll_system + ":" + nameMC[27+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[1] + ":" + "MC, prompt"   ); // MC 4D, cut16
    phiVtype.push_back(LmManager::kNoCut);
    cconfig.push_back(coll_system + ":" + nameMC[27+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[3] + ":" + "MC, conv."    ); // MC 4D, cut16
    phiVtype.push_back(LmManager::kNoCut);
    //  cconfig.push_back(coll_system + ":" + nameMC[27+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[7] + ":" + "MC, one #gamma - LS(one #gamma)"); // MC 4D, cut16
    //  phiVtype.push_back(LmManager::kNoCut);
    cconfig.push_back(coll_system + ":" + nameMC[27+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[8] + ":" + "MC, diff. conv."); // MC 4D, cut16 ("MC, diff. #gamma - LS(diff. #gamma)")
    phiVtype.push_back(LmManager::kNoCut);
    //  cconfig.push_back(coll_system + ":" + nameMC[27+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[9] + ":" + "MC, hadr. cont. - LS(h.c.)"); // MC 4D, cut16
    //  phiVtype.push_back(LmManager::kNoCut);
    cconfig.push_back(coll_system + ":" + name[  62+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_setting[39+kDoPt400+2*kDoPref]  + ":" + "#it{#phi}_{V} template fit" );  // AOD 4D, cut16
    phiVtype.push_back(LmManager::kTemplSub);
    cconfig.push_back(coll_system + ":" + name[  62+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_setting[39+kDoPt400+2*kDoPref]  + ":" + "#it{#phi}_{V} flat correction" );  // AOD 4D, cut16
    phiVtype.push_back(LmManager::kFlatCorrSubAll);
//    cconfig.push_back(coll_system + ":" + name[  62+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_setting[39+kDoPt400+2*kDoPref]  + ":" + "#it{#phi}_{V} prompt correction" );  // AOD 4D, cut16
//    phiVtype.push_back(LmManager::kTemplSub);

    //  cconfig.push_back(coll_system + ":" + name[  62+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_setting[39+kDoPt400+2*kDoPref]  + ":" + "#it{#phi}_{V} flat corr. unsub." );  // AOD 4D, cut16
    //  phiVtype.push_back(LmManager::kFlatCorrUnsub);
    // data with effi, not complete (PrefPhiv not implemented):
    //cconfig.push_back(coll_system + ":" + name[62+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_setting[39+kDoPt400+2*kDoPref]  + ":" + "data, cut16" +":"+effi_name[3+2*kDoSemi+kDoPt400]+":"+effi_gen[1+2*kDoOpAngle+kDoPt400]+":"+effi_rec[...] );  // AOD 4D, cut16
  }
  
  if (sArg.EqualTo("extr")) { // PhiV template extraction
  }
  
  if (sArg.EqualTo("QA")) { // QA plots
    // not sure if they are the right ones...
//    cconfig.push_back(coll_system + ":" + name[47]  + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + "data"     +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ); // data pt>400, no paircuts
//    cconfig.push_back(coll_system + ":" + nameMC[0] + ":" + tree_name[0] + ":" + cut_settingMC[3] + ":" + "MC"       +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[0] ); // MC, regular pairing,  pt>400, no paircuts
    
    cconfig.push_back(coll_system + ":" + name[50+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_setting[39+kDoPt400+2*kDoPref]  + ":" + caption[39+kDoPt400+2*kDoPref]); // AOD, all runs. cuts 01-20 possible.
    // MC, cut01, regular pairing, no paircuts. only for semi-central!
    //cconfig.push_back(coll_system + ":" + nameMC[0] + ":" + tree_name[0] + ":" + cut_settingMC[1+2*kDoPt400] + ":" + "MC cut01 semi"); if (kDoSemi!=1) LmHelper::Error("main.h: this MC only exists for semi-central!");
    // MC, cut01 and cut16.
    cconfig.push_back(coll_system + ":" + nameMC[3+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_settingMC[8+1*kDoPt400] + ":" + "MC cut01");
    
    //cconfig.push_back(coll_system + ":" + name[62+3*kDoSemi] + ":" + tree_name[0] + ":" + cut_setting[39+kDoPt400+2*kDoPref]  + ":" + "data, cut16 AOD");  // AOD 4D, cut16
    
    phiVtype.resize(cconfig.size()); // to avoid triggering of errors below.
  }
  
  n_config = cconfig.size();
  if (n_config==0) LmHelper::Error("main.h: cconfig is empty, nothing to analyze.");
  if (phiVtype.size()!=cconfig.size()) LmHelper::Error("main.h: cconfig size and phiVtype size are different, may cause issues.");
}

/*
// config string for manager
TString cconfig[] = { // this determines which settings will really be analysed! check to select the correct cut_setting!
//  (coll_system + ":" + name[0]  + ":" + tree_name[0] + ":" + cut_setting[0]  + ":" + caption[0]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_old[0] ), // QM2014 //2low (always specify the pair of files (low+hig) with the same setting)
//  (coll_system + ":" + name[1]  + ":" + tree_name[0] + ":" + cut_setting[0]  + ":" + caption[0]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_old[0] ), //          3hig
//  (coll_system + ":" + name[12] + ":" + tree_name[0] + ":" + cut_setting[4]  + ":" + caption[4]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_old[0] ), // Prel.+dE/dx-corr.
//  (coll_system + ":" + name[13] + ":" + tree_name[0] + ":" + cut_setting[4]  + ":" + caption[4]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_old[0] ), 
//syst SPD
//  (coll_system + ":" + name[0]  + ":" + tree_name[0] + ":" + cut_setting[9]  + ":" + caption[9]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), // SPDfirst
//  (coll_system + ":" + name[1]  + ":" + tree_name[0] + ":" + cut_setting[9]  + ":" + caption[9]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), 
//  (coll_system + ":" + name[0]  + ":" + tree_name[0] + ":" + cut_setting[10] + ":" + caption[10] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), // SPDfirst
//  (coll_system + ":" + name[1]  + ":" + tree_name[0] + ":" + cut_setting[10] + ":" + caption[10] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), 
//  (coll_system + ":" + name[18] + ":" + tree_name[0] + ":" + cut_setting[7]  + ":" + caption[7]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), // SPDfirst V0
//  (coll_system + ":" + name[19] + ":" + tree_name[0] + ":" + cut_setting[7]  + ":" + caption[7]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), 
//syst SDD
//  (coll_system + ":" + name[21] + ":" + tree_name[0] + ":" + cut_setting[11] + ":" + caption[11] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), // SPDorSDD
//  (coll_system + ":" + name[22] + ":" + tree_name[0] + ":" + cut_setting[11] + ":" + caption[11] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), 
//  (coll_system + ":" + name[21] + ":" + tree_name[0] + ":" + cut_setting[12] + ":" + caption[12] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), // SPDorSDD
//  (coll_system + ":" + name[22] + ":" + tree_name[0] + ":" + cut_setting[12] + ":" + caption[12] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), 
//  (coll_system + ":" + name[18] + ":" + tree_name[0] + ":" + cut_setting[8]  + ":" + caption[8]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), // SPDorSDD V0
//  (coll_system + ":" + name[19] + ":" + tree_name[0] + ":" + cut_setting[8]  + ":" + caption[8]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), 
//syst Prefilter
//  (coll_system + ":" + name[3]  + ":" + tree_name[0] + ":" + cut_setting[1]  + ":" + caption[1]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), // SPDfirst Pref
//  (coll_system + ":" + name[4]  + ":" + tree_name[0] + ":" + cut_setting[1]  + ":" + caption[1]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), 
//  (coll_system + ":" + name[9]  + ":" + tree_name[0] + ":" + cut_setting[3]  + ":" + caption[3]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), // SPDfirst Pref
//  (coll_system + ":" + name[10] + ":" + tree_name[0] + ":" + cut_setting[3]  + ":" + caption[3]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), 
//  (coll_system + ":" + name[15] + ":" + tree_name[0] + ":" + cut_setting[5]  + ":" + caption[5]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), // SPDfirst Pref
//  (coll_system + ":" + name[16] + ":" + tree_name[0] + ":" + cut_setting[5]  + ":" + caption[5]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), 
////  (coll_system + ":" + name[6]  + ":" + tree_name[0] + ":" + cut_setting[2]  + ":" + caption[2]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), // SPDorSDD Pref //this output caused plotting troubles!
////  (coll_system + ":" + name[7]  + ":" + tree_name[0] + ":" + cut_setting[2]  + ":" + caption[2]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), //               //this output caused plotting troubles!
//  (coll_system + ":" + name[15] + ":" + tree_name[0] + ":" + cut_setting[6]  + ":" + caption[6]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), // SPDorSDD Pref
//  (coll_system + ":" + name[16] + ":" + tree_name[0] + ":" + cut_setting[6]  + ":" + caption[6]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_syst[0] ), 
//central
//  (coll_system + ":" + name[24] + ":" + tree_name[0] + ":" + cut_setting[13]  + ":" + caption[13] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec_old[0] ), // Prel. central
//  (coll_system + ":" + name[25] + ":" + tree_name[0] + ":" + cut_setting[13]  + ":" + caption[13] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec_old[0] ), 
//10-50%
//  (coll_system + ":" + name[27] + ":" + tree_name[0] + ":" + cut_setting[14]  + ":" + caption[14] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // 0 no Prefilter - Like Sign PhiV not yet flipped!
//  (coll_system + ":" + name[28] + ":" + tree_name[0] + ":" + cut_setting[14]  + ":" + caption[14] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[12] + ":" + tree_name[0] + ":" + cut_setting[4]   + ":" + caption[4]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_old[0] ), // Prel.+dE/dx-corr. (copy from above)
//  (coll_system + ":" + name[13] + ":" + tree_name[0] + ":" + cut_setting[4]   + ":" + caption[4]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_old[0] ), //                   (copy from above)
//  (coll_system + ":" + name[30] + ":" + tree_name[0] + ":" + cut_setting[15]  + ":" + caption[15] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[1] ), // 1 mee+theta Prefilter study
//  (coll_system + ":" + name[31] + ":" + tree_name[0] + ":" + cut_setting[15]  + ":" + caption[15] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[1] ), 
//  (coll_system + ":" + name[30] + ":" + tree_name[0] + ":" + cut_setting[16]  + ":" + caption[16] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[2] ), // 2 phiv+mee
//  (coll_system + ":" + name[31] + ":" + tree_name[0] + ":" + cut_setting[16]  + ":" + caption[16] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[2] ), 
//  (coll_system + ":" + name[33] + ":" + tree_name[1] + ":" + cut_setting[17]  + ":" + caption[17] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[3] ), // 3 mee+theta wider
//  (coll_system + ":" + name[34] + ":" + tree_name[1] + ":" + cut_setting[17]  + ":" + caption[17] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[3] ), 
//  (coll_system + ":" + name[33] + ":" + tree_name[1] + ":" + cut_setting[18]  + ":" + caption[18] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[4] ), // 4 phiv+mee wider
//  (coll_system + ":" + name[34] + ":" + tree_name[1] + ":" + cut_setting[18]  + ":" + caption[18] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[4] ), 
//  (coll_system + ":" + name[36] + ":" + tree_name[2] + ":" + cut_setting[19]  + ":" + caption[19] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[1] ), // rndm like 1
//  (coll_system + ":" + name[37] + ":" + tree_name[2] + ":" + cut_setting[19]  + ":" + caption[19] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[1] ), 
//  (coll_system + ":" + name[36] + ":" + tree_name[2] + ":" + cut_setting[20]  + ":" + caption[20] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // rndm like 0
//  (coll_system + ":" + name[37] + ":" + tree_name[2] + ":" + cut_setting[20]  + ":" + caption[20] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//new dE/dx corrections
//  // pt > 200 MeV
//  (coll_system + ":" + name[39] + ":" + tree_name[0] + ":" + cut_setting[21]  + ":" + caption[21] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // effi not yet for 200 MeV!
//  (coll_system + ":" + name[40] + ":" + tree_name[0] + ":" + cut_setting[21]  + ":" + caption[21] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[39] + ":" + tree_name[0] + ":" + cut_setting[22]  + ":" + caption[22] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // effi not yet for 200 MeV!
//  (coll_system + ":" + name[40] + ":" + tree_name[0] + ":" + cut_setting[22]  + ":" + caption[22] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  // pt > 400 MeV
//  (coll_system + ":" + name[39] + ":" + tree_name[0] + ":" + cut_setting[23]  + ":" + caption[23] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
//  (coll_system + ":" + name[40] + ":" + tree_name[0] + ":" + cut_setting[23]  + ":" + caption[23] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[39] + ":" + tree_name[0] + ":" + cut_setting[24]  + ":" + caption[24] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
//  (coll_system + ":" + name[40] + ":" + tree_name[0] + ":" + cut_setting[24]  + ":" + caption[24] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  // pt > 200 MeV
////  (coll_system + ":" + name[42] + ":" + tree_name[0] + ":" + cut_setting[25]  + ":" + caption[25] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // effi not yet for 200 MeV!
////  (coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[25]  + ":" + caption[25] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[42] + ":" + tree_name[0] + ":" + cut_setting[26]  + ":" + caption[26] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // effi not yet for 200 MeV!
//  (coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[26]  + ":" + caption[26] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
////(coll_system + ":" + name[42] + ":" + tree_name[0] + ":" + cut_setting[27]  + ":" + caption[27] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // effi not yet for 200 MeV!
////(coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[27]  + ":" + caption[27] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
////(coll_system + ":" + name[42] + ":" + tree_name[0] + ":" + cut_setting[28]  + ":" + caption[28] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // effi not yet for 200 MeV!
////(coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[28]  + ":" + caption[28] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[42] + ":" + tree_name[0] + ":" + cut_setting[29]  + ":" + caption[29] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // prefilter // effi not yet for 200 MeV!
//  (coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[29]  + ":" + caption[29] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[42] + ":" + tree_name[0] + ":" + cut_setting[30]  + ":" + caption[30] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // prefilter // effi not yet for 200 MeV!
//  (coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[30]  + ":" + caption[30] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[42] + ":" + tree_name[0] + ":" + cut_setting[31]  + ":" + caption[31] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // prefilter // effi not yet for 200 MeV!
//  (coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[31]  + ":" + caption[31] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
////  // pt > 400 MeV
////  (coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + caption[32] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
////  (coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + caption[32] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[33]  + ":" + caption[33] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
//  (coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[33]  + ":" + caption[33] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
////(coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[34]  + ":" + caption[34] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
////(coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[34]  + ":" + caption[34] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
////(coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[35]  + ":" + caption[35] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
////(coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[35]  + ":" + caption[35] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[36]  + ":" + caption[36] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // prefilter
//  (coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[36]  + ":" + caption[36] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[37]  + ":" + caption[37] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // prefilter
//  (coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[37]  + ":" + caption[37] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[38]  + ":" + caption[38] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // prefilter
//  (coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[38]  + ":" + caption[38] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[47] + ":" + tree_name[0] + ":" + cut_setting[34]  + ":" + caption[34] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // 34 full
//  (coll_system + ":" + name[47] + ":" + tree_name[0] + ":" + cut_setting[38]  + ":" + caption[38] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // 38 full
//MC comparison, PhiV study
//  (coll_system + ":" + name[47]  + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + "data"     +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // data pt>400, no paircuts
//  (coll_system + ":" + nameMC[0] + ":" + tree_name[0] + ":" + cut_settingMC[3] + ":" + "MC"       +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[0] ), // MC, regular pairing,  pt>400, no paircuts
//  (coll_system + ":" + nameMC[0] + ":" + tree_name[0] + ":" + cut_settingMC[4] + ":" + "MC_same"  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[0] ), // MC, same mother,      pt>400, no paircuts
//  (coll_system + ":" + nameMC[0] + ":" + tree_name[0] + ":" + cut_settingMC[5] + ":" + "MC_diff"  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[0] ), // MC, different mother, pt>400, no paircuts
//cut01/cut16 semi
////(coll_system + ":" + name[53] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + caption[40] +":"+effi_name[6]+":"+effi_gen[4]+":"+effi_rec[8] ), // AOD, all runs. pt>400
//  (coll_system + ":" + name[51] + ":" + tree_name[0] + ":" + cut_setting[39]  + ":" + caption[39] +":"+effi_name[5]+":"+effi_gen[3]+":"+effi_rec[7] ), // pt>200
//  (coll_system + ":" + name[52] + ":" + tree_name[0] + ":" + cut_setting[39]  + ":" + caption[39] +":"+effi_name[5]+":"+effi_gen[3]+":"+effi_rec[7] ), 
//  (coll_system + ":" + name[51] + ":" + tree_name[0] + ":" + cut_setting[41]  + ":" + caption[41] +":"+effi_name[5]+":"+effi_gen[3]+":"+effi_rec[11] ), // prefilter
//  (coll_system + ":" + name[52] + ":" + tree_name[0] + ":" + cut_setting[41]  + ":" + caption[41] +":"+effi_name[5]+":"+effi_gen[3]+":"+effi_rec[11] ), 
//  (coll_system + ":" + name[51] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + caption[40] +":"+effi_name[6]+":"+effi_gen[4]+":"+effi_rec[8] ), // pt>400
//  (coll_system + ":" + name[52] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + caption[40] +":"+effi_name[6]+":"+effi_gen[4]+":"+effi_rec[8] ), 
//  (coll_system + ":" + name[51] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "#phi_{V} templ no PC" +":"+effi_name[6]+":"+effi_gen[4]+":"+effi_rec[8] ), // pt>400
//  (coll_system + ":" + name[52] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "#phi_{V} templ no PC" +":"+effi_name[6]+":"+effi_gen[4]+":"+effi_rec[8] ), 
//  (coll_system + ":" + name[51] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "#phi_{V} templ w/ PC" +":"+effi_name[6]+":"+effi_gen[4]+":"+effi_rec[8] ), // pt>400
//  (coll_system + ":" + name[52] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "#phi_{V} templ w/ PC" +":"+effi_name[6]+":"+effi_gen[4]+":"+effi_rec[8] ), 
//  (coll_system + ":" + name[51] + ":" + tree_name[0] + ":" + cut_setting[42]  + ":" + caption[42] +":"+effi_name[6]+":"+effi_gen[4]+":"+effi_rec[12] ), // prefilter
//  (coll_system + ":" + name[52] + ":" + tree_name[0] + ":" + cut_setting[42]  + ":" + caption[42] +":"+effi_name[6]+":"+effi_gen[4]+":"+effi_rec[12] ), 
//cut01/cut16 cent
//  (coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[39]  + ":" + caption[39] +":"+effi_name[3]+":"+effi_gen[3]+":"+effi_rec[7] ), // pt>200
//  (coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[39]  + ":" + caption[39] +":"+effi_name[3]+":"+effi_gen[3]+":"+effi_rec[7] ), 
//  (coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[41]  + ":" + caption[41] +":"+effi_name[3]+":"+effi_gen[3]+":"+effi_rec[11] ), // prefilter
//  (coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[41]  + ":" + caption[41] +":"+effi_name[3]+":"+effi_gen[3]+":"+effi_rec[11] ), 
//  (coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + caption[40] +":"+effi_name[4]+":"+effi_gen[4]+":"+effi_rec[8] ), // pt>400
//  (coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + caption[40] +":"+effi_name[4]+":"+effi_gen[4]+":"+effi_rec[8] ), 
//  (coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "#phi_{V} type5n4" +":"+effi_name[4]+":"+effi_gen[4]+":"+effi_rec[8] ), // pt>400
//  (coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "#phi_{V} type5n4" +":"+effi_name[4]+":"+effi_gen[4]+":"+effi_rec[8] ), 
//  (coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "#phi_{V} type5n3" +":"+effi_name[4]+":"+effi_gen[4]+":"+effi_rec[8] ), // pt>400
//  (coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "#phi_{V} type5n3" +":"+effi_name[4]+":"+effi_gen[4]+":"+effi_rec[8] ), 
//  (coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "#phi_{V} type4n4" +":"+effi_name[4]+":"+effi_gen[4]+":"+effi_rec[8] ), // pt>400
//  (coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "#phi_{V} type4n4" +":"+effi_name[4]+":"+effi_gen[4]+":"+effi_rec[8] ), 
//  (coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "yield #minus #gamma conv." +":"+effi_name[4]+":"+effi_gen[4]+":"+effi_rec[8] ), // pt>400
//  (coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "yield #minus #gamma conv." +":"+effi_name[4]+":"+effi_gen[4]+":"+effi_rec[8] ), 
//  (coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[42]  + ":" + caption[42] +":"+effi_name[4]+":"+effi_gen[4]+":"+effi_rec[12] ), // prefilter
//  (coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[42]  + ":" + caption[42] +":"+effi_name[4]+":"+effi_gen[4]+":"+effi_rec[12] ), 
//PhiV study
// full run list
//  (coll_system + ":" + name[47] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + caption[32] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
//  (coll_system + ":" + name[47] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + "#phi_{V} < 3/4 #pi, flat corr" +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
//  (coll_system + ":" + name[47] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + "#phi_{V} < 1/2 #pi, flat corr" +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
//  (coll_system + ":" + name[47] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + "#phi_{V} < 1/4 to 3/4 #pi, template" +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
// low+high separately
//  (coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + caption[32] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
//  (coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + caption[32] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + "#phi_{V} < 3/4 #pi, flat corr" +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
//  (coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + "#phi_{V} < 3/4 #pi, flat corr" +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + "#phi_{V} < 1/2 #pi, flat corr" +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
//  (coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + "#phi_{V} < 1/2 #pi, flat corr" +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + "#phi_{V} < 1/4 to 3/4 #pi, template" +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
//  (coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + "#phi_{V} < 1/4 to 3/4 #pi, template" +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
// PhiV again
// MC
//  (coll_system + ":" + nameMC[3]  + ":" + tree_name[0] + ":" + cut_settingMC[11]+pairMC[0] + ":" + "MC, no PC"         ), // MC, cent, cut16, pt>400, no paircuts
//  (coll_system + ":" + nameMC[3]  + ":" + tree_name[0] + ":" + cut_settingMC[11]+pairMC[1] + ":" + "MC prompt, no PC"  ), // MC, cent, cut16, pt>400, no paircuts
//  (coll_system + ":" + nameMC[3]  + ":" + tree_name[0] + ":" + cut_settingMC[11]+pairMC[3] + ":" + "MC conv., no PC"   ), // MC, cent, cut16, pt>400, no paircuts
//  (coll_system + ":" + nameMC[6]  + ":" + tree_name[0] + ":" + cut_settingMC[11]+pairMC[0] + ":" + "MC, no PC"         ), // MC, semi, cut16, pt>400, no paircuts
//  (coll_system + ":" + nameMC[6]  + ":" + tree_name[0] + ":" + cut_settingMC[11]+pairMC[1] + ":" + "MC prompt, no PC"  ), // MC, semi, cut16, pt>400, no paircuts
//  (coll_system + ":" + nameMC[6]  + ":" + tree_name[0] + ":" + cut_settingMC[11]+pairMC[3] + ":" + "MC conv., no PC"   ), // MC, semi, cut16, pt>400, no paircuts
// cent
//  (coll_system + ":" + name[50]   + ":" + tree_name[0] + ":" + cut_setting[39]  + ":" + "data, cut16" ), // AOD, cut16, cent, pt>200
//  (coll_system + ":" + nameMC[3]  + ":" + tree_name[0] + ":" + cut_settingMC[10]+pairMC[0] + ":" + "MC, no PC"         ), // MC, cut16, pt>200, no paircuts
//  (coll_system + ":" + nameMC[9]  + ":" + tree_name[0] + ":" + cut_settingMC[12]+pairMC[0] + ":" + "MC, w/ PC"         ), // MC, cut16, pt>200, paircuts
//  (coll_system + ":" + nameMC[9]  + ":" + tree_name[0] + ":" + cut_settingMC[14]+pairMC[0] + ":" + "MC, w/ PC + Pref." ), // MC, cut16, pt>200, paircuts + prefilter
//  (coll_system + ":" + name[50]   + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "data, cut16" ), // AOD, cut16, cent, pt>400
//  (coll_system + ":" + nameMC[3]  + ":" + tree_name[0] + ":" + cut_settingMC[11]+pairMC[3] + ":" + "MC, no PC"         ), // MC, cut16, pt>400, no paircuts
//  (coll_system + ":" + nameMC[9]  + ":" + tree_name[0] + ":" + cut_settingMC[13]+pairMC[3] + ":" + "MC, w/ PC"         ), // MC, cut16, pt>400, paircuts
//  (coll_system + ":" + nameMC[9]  + ":" + tree_name[0] + ":" + cut_settingMC[15]+pairMC[3] + ":" + "MC, w/ PC + Pref." ), // MC, cut16, pt>400, paircuts + prefilter
//  (coll_system + ":" + name[50]   + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "data, cut16" ), // AOD, cut16, cent, pt>400
//  (coll_system + ":" + nameMC[9]  + ":" + tree_name[0] + ":" + cut_settingMC[13]+pairMC[0] + ":" + "MC"                ), // MC, cut16, pt>400, paircuts
//  (coll_system + ":" + nameMC[9]  + ":" + tree_name[0] + ":" + cut_settingMC[13]+pairMC[1] + ":" + "MC prompt"         ), // MC, cut16, pt>400, paircuts
//  (coll_system + ":" + nameMC[9]  + ":" + tree_name[0] + ":" + cut_settingMC[13]+pairMC[3] + ":" + "MC conv."          ), // MC, cut16, pt>400, paircuts
//  (coll_system + ":" + nameMC[15] + ":" + tree_name[0] + ":" + cut_settingMC[19]+pairMC[0] + ":" + "MC noConv"         ), // MC, cut16, pt>400, paircuts, noConv
////  (coll_system + ":" + nameMC[15] + ":" + tree_name[0] + ":" + cut_settingMC[19]+pairMC[1] + ":" + "MC prompt nC"      ), // MC, cut16, pt>400, paircuts, noConv
////  (coll_system + ":" + nameMC[15] + ":" + tree_name[0] + ":" + cut_settingMC[19]+pairMC[2] + ":" + "MC diff.M nC"      ), // MC, cut16, pt>400, paircuts, noConv
//  (coll_system + ":" + nameMC[27]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[0] + ":" + "MC 4D"           ), // MC 4D, cut16
//  (coll_system + ":" + nameMC[27]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[1] + ":" + "MC 4D, prompt"   ), // MC 4D, cut16
//  (coll_system + ":" + nameMC[27]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[3] + ":" + "MC 4D, conv."    ), // MC 4D, cut16
////(coll_system + ":" + nameMC[27]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[4] + ":" + "MC 4D, one gamma"), // MC 4D, cut16
//  (coll_system + ":" + nameMC[27]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[8] + ":" + "MC 4D, diff. #gamma - LS(#gamma)"), // MC 4D, cut16
  //(coll_system + ":" + nameMC[27]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[5] + ":" + "MC 4D, diff. gamma"), // MC 4D, cut16
  //(coll_system + ":" + nameMC[27]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[6] + ":" + "MC 4D, hadr. cont."), // MC 4D, cut16
  ////  (coll_system + ":" + nameMC[27]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[2] + ":" + "MC 4D, diff.M"   ), // MC 4D, cut16
// semi
//  (coll_system + ":" + name[53]   + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "data, cut16" ), // AOD, cut16, semi, pt>400
//  (coll_system + ":" + nameMC[12] + ":" + tree_name[0] + ":" + cut_settingMC[13]+pairMC[0] + ":" + "MC"                ), // MC, cut16, pt>400, paircuts
//  (coll_system + ":" + nameMC[12] + ":" + tree_name[0] + ":" + cut_settingMC[13]+pairMC[1] + ":" + "MC prompt"         ), // MC, cut16, pt>400, paircuts
//  (coll_system + ":" + nameMC[12] + ":" + tree_name[0] + ":" + cut_settingMC[13]+pairMC[3] + ":" + "MC conv."          ), // MC, cut16, pt>400, paircuts
//  (coll_system + ":" + nameMC[18] + ":" + tree_name[0] + ":" + cut_settingMC[19]+pairMC[0] + ":" + "MC noConv"         ), // MC, cut16, pt>400, paircuts, noConv
//  (coll_system + ":" + nameMC[18] + ":" + tree_name[0] + ":" + cut_settingMC[19]+pairMC[1] + ":" + "MC prompt nC"      ), // MC, cut16, pt>400, paircuts, noConv
//  (coll_system + ":" + nameMC[18] + ":" + tree_name[0] + ":" + cut_settingMC[19]+pairMC[2] + ":" + "MC diff.M nC"      ), // MC, cut16, pt>400, paircuts, noConv
  (coll_system + ":" + name[65]    + ":" + tree_name[0] + ":" + cut_setting[39+kDoPt400+2*kDoPref]  + ":" + "-" +":"+effi_name[5+kDoPt400]+":"+effi_gen[2]+":"+effi_rec[6] ),  // AOD 4D, cut16, semi (same effi as before)
  (coll_system + ":" + nameMC[30]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[0] + ":" + "MC"           ), // MC 4D, cut16
  (coll_system + ":" + nameMC[30]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[1] + ":" + "MC, prompt"   ), // MC 4D, cut16
  (coll_system + ":" + nameMC[30]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[3] + ":" + "MC, conv."    ), // MC 4D, cut16
  (coll_system + ":" + nameMC[30]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[7] + ":" + "MC, one #gamma - LS(one #gamma)"), // MC 4D, cut16
  (coll_system + ":" + nameMC[30]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[8] + ":" + "MC, diff. #gamma - LS(diff. #gamma)"), // MC 4D, cut16
  (coll_system + ":" + nameMC[30]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[9] + ":" + "MC, hadr. cont. - LS(h.c.)"), // MC 4D, cut16
  (coll_system + ":" + name[65]    + ":" + tree_name[0] + ":" + cut_setting[39+kDoPt400+2*kDoPref]  + ":" + "data, cut16 AOD" +":"+effi_name[5+kDoPt400]+":"+effi_gen[2]+":"+effi_rec[6] ),  // AOD 4D, cut16, semi (same effi as before)
  //(coll_system + ":" + nameMC[30]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[4] + ":" + "MC, one gamma"), // MC 4D, cut16
  //(coll_system + ":" + nameMC[30]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[5] + ":" + "MC, diff. gamma"), // MC 4D, cut16
  //(coll_system + ":" + nameMC[30]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[6] + ":" + "MC, hadr. cont."), // MC 4D, cut16
  ////  (coll_system + ":" + nameMC[30]  + ":" + tree_name[0] + ":" + cut_settingMC[12+kDoPt400+2*kDoPref]+pairMC[2] + ":" + "MC, diff.M"   ), // MC 4D, cut16
// ESD cut16 cent, 4D (default: no opening angle cut)
//  (coll_system + ":" + name[54]   + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "cut16 ESD" +":"+effi_name[4]+":"+effi_gen[2]+":"+effi_rec[6] ),  // ESD 4D, cut16, cent, pt>400 (same effi as before)
//  (coll_system + ":" + name[55]   + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "cut16 ESD" +":"+effi_name[4]+":"+effi_gen[2]+":"+effi_rec[6] ),  //
//  (coll_system + ":" + name[54]   + ":" + tree_name[0] + ":" + cut_setting[46]  + ":" + caption[44] +":"+effi_name[8]+":"+effi_gen[2]+":"+effi_rec[14] ), // ESD 4D, cut16, cent, pt>400, ITS cuts
//  (coll_system + ":" + name[55]   + ":" + tree_name[0] + ":" + cut_setting[46]  + ":" + caption[44] +":"+effi_name[8]+":"+effi_gen[2]+":"+effi_rec[14] ), //
//  (coll_system + ":" + name[54]   + ":" + tree_name[0] + ":" + cut_setting[48]  + ":" + caption[46] ), // ESD, cut16, cent, pt>400, ITS cuts, Pref
//  (coll_system + ":" + name[55]   + ":" + tree_name[0] + ":" + cut_setting[48]  + ":" + caption[46] ), // ESD, cut16, cent, pt>400, ITS cuts, Pref
// AOD cut16 cent, 4D (default: no opening angle cut)
//  (coll_system + ":" + name[60]   + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "cut16 AOD" +":"+effi_name[4]+":"+effi_gen[2]+":"+effi_rec[6] ),  // AOD 4D, cut16, cent, pt>400 (same effi as before)
//  (coll_system + ":" + name[61]   + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + "cut16 AOD" +":"+effi_name[4]+":"+effi_gen[2]+":"+effi_rec[6] ),  //
  "empty" // needed to avoid anger with ',' at the end of the last active line
};
Int_t n_config = sizeof(cconfig)/sizeof(*cconfig) -1; // '-1' to neglect the "empty" entry.
*/
//
// binning
// see patrick_common.h
//
// desired binning for cocktail.
// may be much finer than for data, but the bin edges should overlap to avoid inconsistencies when doing projections!
//Double_t mee_bin_cocktail[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38, 0.40, 0.42, 0.44, 0.46, 0.48, 
//  0.50, 0.52, 0.54, 0.56, 0.58, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.72, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98, 
//  1.00, 1.02, 1.04, 1.06, 1.08, 1.10, 1.12, 1.14, 1.16, 1.18, 1.20, 
//  1.30, 1.40, 1.50, 1.60, 1.70, 1.80, 1.90, 2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 3.00, 3.10, 3.20, 3.30, 3.40, 3.50, 3.60, 3.70, 3.80, 3.90, 
//  4.00, 4.10, 4.20, 4.30, 4.40, 4.50, 4.60, 4.70, 4.80, 4.90, 5.00 };
Double_t mee_bin_cocktail[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, //0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38, 0.40, 0.42, 0.44, 0.46, 0.48, 
  //0.50, 0.52, 0.54, 0.56, 0.58, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.72, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98, 
  //1.00, 1.02, 1.04, 1.06, 1.08, 1.10, 1.12, 1.14, 1.16, 1.18, 1.20, 1.22, 1.24, 1.26, 1.28, 1.30, 1.32, 1.34, 1.36, 1.38, 1.40, 1.42, 1.44, 1.46, 1.48, 1.50, 1.52, 1.54, 1.56, 1.58, 1.60, 
  0.14, 0.18, 0.22, 0.26, 0.30, 0.34, 0.38, 0.42, 0.46, 0.50, 0.54, 0.58, 0.62, 0.66, 0.70, 0.74, /*0.76,*/ 0.78, /*0.80,*/ 0.82, 0.86, 0.90, 0.94, 0.98, 
  /*1.00,*/ 1.02, /*1.04,*/ 1.06, 1.10, 1.20, 1.30, 1.40, 1.50, 1.60, 
  1.70, 1.80, 1.90, 2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 2.95, 3.00, 3.05, 3.10, 3.15, 3.20, 3.30, 3.40, 3.50, 3.60, 3.70, 3.80, 3.90, 
  4.00/*, 4.10, 4.20, 4.30, 4.40, 4.50, 4.60, 4.70, 4.80, 4.90, 5.00*/ };

Double_t ptee_bin_cocktail[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 
  2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 5.2, 5.4, 5.6, 5.8, 6.0 };
Int_t n_mee_bin_cocktail = sizeof(mee_bin_cocktail)/sizeof(*mee_bin_cocktail) -1;
Int_t n_ptee_bin_cocktail = sizeof(ptee_bin_cocktail)/sizeof(*ptee_bin_cocktail) -1;
//
// Opening angle cut that shall be applied
Double_t thetaEEmin = 0.00;

//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/047-ESD255ff-ITS-chi2+shared/LMEEoutput-ESD263-1hig.root LMEEoutput-ESD263-1hig.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/047-ESD255ff-ITS-chi2+shared/LMEEoutput-ESD263-2low.root LMEEoutput-ESD263-2low.root
//
//ln -s ../../../../PairEffCalc/output/pairEff_raw-17h-std.root pairEff_raw-17h-std.root
//ln -s ../../../../PairEffCalc/output/pairEff_raw-17g-std.root pairEff_raw-17g-std.root
//
//ln -s /Users/Patrick/Desktop/Analyse/009_PbPb_Effi/015-LEGO007-MultiDiel-same+diff-mother/LMEEoutput-1full.root LMEEoutput-MC007-1full.root
//ln -s /Users/Patrick/Desktop/Analyse/009_PbPb_Effi/015-LEGO007-MultiDiel-same+diff-mother/LMEEoutput-2low.root LMEEoutput-MC007-2low.root
//ln -s /Users/Patrick/Desktop/Analyse/009_PbPb_Effi/015-LEGO007-MultiDiel-same+diff-mother/LMEEoutput-3hig.root LMEEoutput-MC007-3hig.root
//