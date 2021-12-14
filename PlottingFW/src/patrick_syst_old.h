// input data files. make sure to edit the other strings accordingly!
TString name[] = {
  "./input/LMEEoutput-merged-2low.root",
  "./input/LMEEoutput-merged-3hig.root",
  ""
};
// corresponding input efficiency files
TString effi_name[] = {
  //"./input/charm-eff05-17h.root",     // old. 272, 347
  //"./input/charm-eff07-17g.root",     // old. central
  "../PairEffCalc/output/pairEff_raw-17h-std.root", // 272, 347 (20-50%)
  "../PairEffCalc/output/pairEff_raw-17g-std.root", // central
  "../PairEffCalc/output/pairEff_raw-1050-std+RandRej_0to3-1000-50.root", // std, std+randomrej (10-50%)
  ""
};
// name of 2D generated and reconstructed histogram
//TString effi_gen[] = {"meePairPt_Eta076_raw"};
//TString effi_rec[] = {"meePairPt_PID2_e", "meePairPt_PID2_e"}; // old. same for Semi and Cent Prel outputs.
TString effi_gen[]     = {"hNGenPairs_pt400"};
TString effi_rec_old[] = {"Npair_hEff_Nreco_Ele_ITSTPCTOFif_trkSPDfirst_1_pt400"}; // mid-old std
TString effi_rec[]     = {"Npair_hEff_ITSTPCTOFif_trkSPDfirst_1_pt400", // std
  "Npair_hEff_ITSTPCTOFif_trkSPDfirst_1_rej_ITSTPCTOFif_trkSPDfirst_1_PrefAllm40t80_pt400",  "Npair_hEff_ITSTPCTOFif_trkSPDfirst_1_rej_ITSTPCTOFif_trkSPDfirst_1_PrefAllp236m40_pt400",  //(15)+(16) 488
  "Npair_hEff_ITSTPCTOFif_trkSPDfirst_1_rej_ITSTPCTOFif_trkSPDfirst_1_PrefAllm60t100_pt400", "Npair_hEff_ITSTPCTOFif_trkSPDfirst_1_rej_ITSTPCTOFif_trkSPDfirst_1_PrefAllp157m60_pt400",  //(17)+(18) 489
  ""
};
TString effi_rec_syst[] = {"Npair_hEff_ITSTPCTOFif_trkSPDfirst_1_pt400", // syst
  ""
};
//
// further details of input data
TString tree_name[] = {"reichelt_LMEEPbPb2011_out", "reichelt_LMEEPbPb2011_out_nr2", "reichelt_LMEEPbPb2011_out_nr3" }; // extend when comparing PR with CK!
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
  ""
};
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
Int_t   which_cockt_files = 2; // 0=Central, 1=Semi_2050, 2=Semi_1050, see cocktail_files[] above!
Int_t   which_cockt_hists = 0;
Int_t   which_heavyfl_files = 0;
Int_t   which_heavyfl_hists = 0;
TString coll_system = "Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV";  /// @TODO: with new Root version, use #minus.
TString inputhist   = "pInvMass_PairPt_PhivPair";
Int_t   inputdim    = 3;
TString projoption  = "yx"; // option="ab" means: a vertical, b horizontal (ROOT-convention)
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
  ""
};
// config string for manager
TString cconfig[] = { // this determines which settings will really be analysed! check to select the correct cut_setting!
  //10-50%
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[15]  + ":" + caption[15] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[1] ), // 1 mee+theta Prefilter study
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[15]  + ":" + caption[15] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[1] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[16]  + ":" + caption[16] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[2] ), // 2 phiv+mee
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[16]  + ":" + caption[16] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[2] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[17]  + ":" + caption[17] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[3] ), // 3 mee+theta wider
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[17]  + ":" + caption[17] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[3] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[18]  + ":" + caption[18] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[4] ), // 4 phiv+mee wider
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[18]  + ":" + caption[18] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[4] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[19]  + ":" + caption[19] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[1] ), // rndm like 1
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[19]  + ":" + caption[19] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[1] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[20]  + ":" + caption[20] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // rndm like 0
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[20]  + ":" + caption[20] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//new dE/dx corrections
// pt > 200 MeV
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[21]  + ":" + caption[21] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // effi not yet for 200 MeV!
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[21]  + ":" + caption[21] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[22]  + ":" + caption[22] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // effi not yet for 200 MeV!
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[22]  + ":" + caption[22] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
// pt > 400 MeV
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[23]  + ":" + caption[23] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[23]  + ":" + caption[23] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[24]  + ":" + caption[24] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[24]  + ":" + caption[24] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
// pt > 200 MeV
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[25]  + ":" + caption[25] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // effi not yet for 200 MeV!
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[25]  + ":" + caption[25] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[26]  + ":" + caption[26] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // effi not yet for 200 MeV!
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[26]  + ":" + caption[26] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[27]  + ":" + caption[27] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // effi not yet for 200 MeV!
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[27]  + ":" + caption[27] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[28]  + ":" + caption[28] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // effi not yet for 200 MeV!
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[28]  + ":" + caption[28] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[29]  + ":" + caption[29] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // prefilter // effi not yet for 200 MeV!
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[29]  + ":" + caption[29] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[30]  + ":" + caption[30] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // prefilter // effi not yet for 200 MeV!
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[30]  + ":" + caption[30] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[31]  + ":" + caption[31] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // prefilter // effi not yet for 200 MeV!
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[31]  + ":" + caption[31] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
// pt > 400 MeV
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + caption[32] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + caption[32] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[33]  + ":" + caption[33] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[33]  + ":" + caption[33] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[34]  + ":" + caption[34] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[34]  + ":" + caption[34] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[35]  + ":" + caption[35] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[35]  + ":" + caption[35] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[36]  + ":" + caption[36] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // prefilter
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[36]  + ":" + caption[36] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[37]  + ":" + caption[37] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // prefilter
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[37]  + ":" + caption[37] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[38]  + ":" + caption[38] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // prefilter
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[38]  + ":" + caption[38] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 

  "empty" // needed to avoid anger with ',' at the end of the last active line
};
Int_t n_config = sizeof(cconfig)/sizeof(*cconfig) -1; // '-1' to neglect the "empty" entry.
//
// desired binning for output. will also be used for efficiency correction.
// binning has to be compatible with input. [PR/CK: see function GetVector() of Config_user_LMEEPbPb.C]
////Double_t mee_bin[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10,   0.14, 0.18, 0.22, 0.26, 0.30, 0.34, // for QM14 up to 0.5GeV
////  0.42, 0.50, 0.58, 0.66,   0.82, 0.98,   1.50, 2.10, 2.70, 3.30, 4.00, 5.00 };
//Double_t mee_bin[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 
//  0.14, 0.18,   0.26, 0.34,   0.50,   0.70,   1.10, 1.50, 
//  2.10, 2.70, 3.30, 4.00, 5.00 };
Double_t mee_bin[] = { 0.0, 0.14, 1.1, 3.0, 3.2/*, 4.0*/ }; // last bin is oversubtracted except for high pt

//Double_t ptee_bin[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 
//  2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0 };
Double_t ptee_bin[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.4, 2.0, 3.0, 4.0, 5.0 };
Double_t phiv_bin[] = { 5
//  0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38, 0.40, 0.42, 0.44, 0.46, 0.48, 
//  0.50, 0.52, 0.54, 0.56, 0.58, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.72, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98, 
//  1.00, 1.02, 1.04, 1.06, 1.08, 1.10, 1.12, 1.14, 1.16, 1.18, 1.20, 1.22, 1.24, 1.26, 1.28, 1.30, 1.32, 1.34, 1.36, 1.38, 1.40, 1.42, 1.44, 1.46, 1.48, 1.50, 1.52, 1.54, 1.56, 1.58, 1.60, 
//  0.00, 0.10, 0.20, 0.30, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00, 1.10, 1.20, 1.30, 1.40, 1.50, 1.60, 
//  1.70, 1.80, 1.90, 2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 3.00, 3.10, 3.1415 
};
Int_t n_mee_bin = sizeof(mee_bin)/sizeof(*mee_bin) -1;
Int_t n_ptee_bin = sizeof(ptee_bin)/sizeof(*ptee_bin) -1;
Int_t n_phiv_bin = sizeof(phiv_bin)/sizeof(*phiv_bin) -1;
//
// systematic  
Double_t mee_bin_systematic[] = { 0.0, 0.14, 1.1, 3.0, 3.2/*, 4.0*/ }; // last bin is oversubtracted except for high pt
Double_t ptee_bin_systematic[] = { 0.0,1.0,2.0,3.0,6.0 }; 
Int_t n_mee_bin_systematic = sizeof(mee_bin_systematic)/sizeof(*mee_bin_systematic) -1;
Int_t n_ptee_bin_systematic = sizeof(ptee_bin_systematic)/sizeof(*ptee_bin_systematic) -1;
//
// desired binning for cocktail.
// may be much finer than for data, but the bin edges should overlap to avoid inconsistencies when doing projections!
//Double_t mee_bin_cocktail[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38, 0.40, 0.42, 0.44, 0.46, 0.48, 
//  0.50, 0.52, 0.54, 0.56, 0.58, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.72, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98, 
//  1.00, 1.02, 1.04, 1.06, 1.08, 1.10, 1.12, 1.14, 1.16, 1.18, 1.20, 
//  1.30, 1.40, 1.50, 1.60, 1.70, 1.80, 1.90, 2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 3.00, 3.10, 3.20, 3.30, 3.40, 3.50, 3.60, 3.70, 3.80, 3.90, 
//  4.00, 4.10, 4.20, 4.30, 4.40, 4.50, 4.60, 4.70, 4.80, 4.90, 5.00 };
Double_t mee_bin_cocktail[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38, 0.40, 0.42, 0.44, 0.46, 0.48, 
  0.50, 0.52, 0.54, 0.56, 0.58, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.72, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98, 
  1.00, 1.02, 1.04, 1.06, 1.08, 1.10, 1.12, 1.14, 1.16, 1.18, 1.20, 1.22, 1.24, 1.26, 1.28, 1.30, 1.32, 1.34, 1.36, 1.38, 1.40, 1.42, 1.44, 1.46, 1.48, 1.50, 1.52, 1.54, 1.56, 1.58, 1.60, 
  1.70, 1.80, 1.90, 2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 3.00, 3.10, 3.20, 3.30, 3.40, 3.50, 3.60, 3.70, 3.80, 3.90, 
  4.00, 4.10, 4.20, 4.30, 4.40, 4.50, 4.60, 4.70, 4.80, 4.90, 5.00 };
Double_t ptee_bin_cocktail[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 
  2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0 };
Int_t n_mee_bin_cocktail = sizeof(mee_bin_cocktail)/sizeof(*mee_bin_cocktail) -1;
Int_t n_ptee_bin_cocktail = sizeof(ptee_bin_cocktail)/sizeof(*ptee_bin_cocktail) -1;
//
// PhiV-cut that shall be applied
// to disable, set phiv=pi or mee=0 or call mgr.SetEnablePhiVCut(kFALSE);
Double_t cutValPhiV = 3./4.*TMath::Pi();
Double_t cutValMee = 0.10;

Bool_t    kDoSignifRaw      = kTRUE;
Bool_t    kDoNormNevents    = kTRUE;
Bool_t    kDoNormBinwidth   = kTRUE;
Bool_t    kDoEffiCorrection = kFALSE;
Bool_t    kDoConfLevel      = kFALSE;
Double_t  confLevel         = 0.84;
Bool_t    kDoRatio          = kFALSE;
Bool_t    kDoCocktail       = kFALSE;
Int_t     debug             = 2;

//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/044-LEGO496-pt400-Pair_theta+Pref/LMEEoutput-1full.root LMEEoutput-496-1full.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/044-LEGO496-pt400-Pair_theta+Pref/LMEEoutput-2low.root LMEEoutput-496-2low.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/044-LEGO496-pt400-Pair_theta+Pref/LMEEoutput-3hig.root LMEEoutput-496-3hig.root
//
//ln -s ../../../../PairEffCalc/output/pairEff_raw-17h-std.root pairEff_raw-17h-std.root
//ln -s ../../../../PairEffCalc/output/pairEff_raw-17g-std.root pairEff_raw-17g-std.root
//
//ln -s /Users/Patrick/Desktop/Analyse/009_PbPb_Effi/015-LEGO007-MultiDiel-same+diff-mother/LMEEoutput-1full.root LMEEoutput-MC007-1full.root
//ln -s /Users/Patrick/Desktop/Analyse/009_PbPb_Effi/015-LEGO007-MultiDiel-same+diff-mother/LMEEoutput-2low.root LMEEoutput-MC007-2low.root
//ln -s /Users/Patrick/Desktop/Analyse/009_PbPb_Effi/015-LEGO007-MultiDiel-same+diff-mother/LMEEoutput-3hig.root LMEEoutput-MC007-3hig.root
//