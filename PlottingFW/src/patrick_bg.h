// input data files. make sure to edit the other strings accordingly!
TString name[] = {
  "./input/LMEEoutput-272PrelSemi-2low.root",   // (0)+(9)+(10) 0 = QM2014 output
  "./input/LMEEoutput-272PrelSemi-3hig.root",   //     inputhist("InvMass_PairPt_PhivPair")
  "./input/LMEEoutput-272PrelSemi-1full.root", 
  "./input/LMEEoutput-311-2low.root",  // (1) Prefilter SPDfirst 1 (m<20, theta<50)
  "./input/LMEEoutput-311-3hig.root",  //     inputhist("InvMass_PairPt_PhivPair")
  "./input/LMEEoutput-311-1full.root", 
  "./input/LMEEoutput-316-2low.root",  // (2) Prefilter SPDorSDD 1 (m<20, theta<50)
  "./input/LMEEoutput-316-3hig.root",  //     changed inputhist("pInvMass_PairPt_PhivPair")! changed to variable binning!
  "./input/LMEEoutput-316-1full.root", 
  "./input/LMEEoutput-319-2low.root",  // (3) Prefilter SPDfirst 2 (m<30, theta<60)
  "./input/LMEEoutput-319-3hig.root",  
  "./input/LMEEoutput-319-1full.root", 
  "./input/LMEEoutput-347-2low.root",  // (4) like Preliminary, but with TPC eta correction.
  "./input/LMEEoutput-347-3hig.root",  
  "./input/LMEEoutput-347-1full.root", 
  "./input/LMEEoutput-480-2low.root",  // (5)+(6) Prefilter SPDfirst 3 (m<50, theta<80) + SPDorSDD 2 (m<10, theta<30)
  "./input/LMEEoutput-480-3hig.root",  
  "./input/LMEEoutput-480-1full.root", 
  "./input/LMEEoutput-483-2low.root",  // (7)+(8) SPDfirst+V0 () + SPDorSDD+V0 ()
  "./input/LMEEoutput-483-3hig.root",  
  "./input/LMEEoutput-483-1full.root", 
  "./input/LMEEoutput-279-2low.root",  // (11)+(12) SPDorSDD  ( name[21] )
  "./input/LMEEoutput-279-3hig.root",  //     inputhist("InvMass_PairPt_PhivPair")
  "./input/LMEEoutput-279-1full.root", 
  "./input/LMEEoutput-268PrelCent-2low.root", // (13) QM2014 output
  "./input/LMEEoutput-268PrelCent-3hig.root", //      inputhist("InvMass_PairPt_PhivPair")
  "./input/LMEEoutput-268PrelCent-1full.root",
  "./input/LMEEoutput-484-2low.root", // (14) 10-50% Centrality, standard setting like QM2014
  "./input/LMEEoutput-484-3hig.root",
  "./input/LMEEoutput-484-1full.root",
  "./input/LMEEoutput-488-2low.root", // (15)+(16) 10-50% Prefilter (m<40, theta<80) + (phiv>2.36, m<40)
  "./input/LMEEoutput-488-3hig.root",
  "./input/LMEEoutput-488-1full.root",
  "./input/LMEEoutput-489-2low.root", // (17)+(18) 10-50% Prefilter (m<60, theta<100) + (phiv>1.57, m<60)
  "./input/LMEEoutput-489-3hig.root",
  "./input/LMEEoutput-489-1full.root",
  "./input/LMEEoutput-490-2low.root", // (19)+(20) Random daughter check: 10-50% Prefilter (m<40, theta<80) + standard setting
  "./input/LMEEoutput-490-3hig.root",
  "./input/LMEEoutput-490-1full.root",
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
TString coll_system = "Pb-Pb, #sqrt{#it{s}_{NN}} = 2.76 TeV";  /// @TODO: with new Root version, use #minus.
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
  ""
};
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
  (coll_system + ":" + name[27] + ":" + tree_name[0] + ":" + cut_setting[14]  + ":" + caption[14] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), // 0 no Prefilter - Like Sign PhiV not yet flipped!
  (coll_system + ":" + name[28] + ":" + tree_name[0] + ":" + cut_setting[14]  + ":" + caption[14] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ), 
//  (coll_system + ":" + name[12] + ":" + tree_name[0] + ":" + cut_setting[4]  + ":" + caption[4]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_old[0] ), // Prel.+dE/dx-corr. (copy from above)
//  (coll_system + ":" + name[13] + ":" + tree_name[0] + ":" + cut_setting[4]  + ":" + caption[4]  +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec_old[0] ), //                   (copy from above)

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
  "empty" // needed to avoid anger with ',' at the end of the last active line
};
Int_t n_config = sizeof(cconfig)/sizeof(*cconfig) -1; // '-1' to neglect the "empty" entry.
//
// desired binning for output. will also be used for efficiency correction.
// binning has to be compatible with input. [PR/CK: see function GetVector() of Config_user_LMEEPbPb.C]
////Double_t mee_bin[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10,   0.14, 0.18, 0.22, 0.26, 0.30, 0.34, // for QM14 up to 0.5GeV
////  0.42, 0.50, 0.58, 0.66,   0.82, 0.98,   1.50, 2.10, 2.70, 3.30, 4.00, 5.00 };
Double_t mee_bin[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 
  0.14, 0.18,   0.26, 0.34,   0.50,   0.70,   1.10, 1.50, 
  2.10, 2.70, 3.30, 4.00, 5.00 };
//Double_t mee_bin[] = { // phiV
//  0.00
//, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38, 0.40, 0.42, 0.44, 0.46, 0.48, 
//  0.50, 0.52, 0.54, 0.56, 0.58, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.72, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98, 
//  1.00, 1.02, 1.04, 1.06, 1.08, 1.10, 1.12, 1.14, 1.16, 1.18, 1.20, 1.22, 1.24, 1.26, 1.28, 1.30, 1.32, 1.34, 1.36, 1.38, 1.40, 1.42, 1.44, 1.46, 1.48, 1.50, 1.52, 1.54, 1.56, 1.58, 1.60, 
//  1.70, 1.80, 1.90, 2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 3.00, 3.10, 3.1415 
//};
//Double_t ptee_bin[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 
//  2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0 };
Double_t ptee_bin[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.4, 2.0, 3.0, 4.0, 5.0 };
Int_t n_mee_bin = sizeof(mee_bin)/sizeof(*mee_bin) -1;
Int_t n_ptee_bin = sizeof(ptee_bin)/sizeof(*ptee_bin) -1;
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
Bool_t    kDoEffiCorrection = kTRUE;
Bool_t    kDoConfLevel      = kFALSE;
Double_t  confLevel         = 0.84;
Bool_t    kDoRatio          = kTRUE;
Int_t     debug             = 15;

//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/013-LEGO279-semi-syst3+4-SPDorSDD/LMEEoutput-1full.root LMEEoutput-279-1full.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/013-LEGO279-semi-syst3+4-SPDorSDD/LMEEoutput-2low.root LMEEoutput-279-2low.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/013-LEGO279-semi-syst3+4-SPDorSDD/LMEEoutput-3hig.root LMEEoutput-279-3hig.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/015-LEGO311-V0forEtaCorr+Prefilter/LMEEoutput-1full.root LMEEoutput-311-1full.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/015-LEGO311-V0forEtaCorr+Prefilter/LMEEoutput-2low.root LMEEoutput-311-2low.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/015-LEGO311-V0forEtaCorr+Prefilter/LMEEoutput-3hig.root LMEEoutput-311-3hig.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/016-LEGO316-EtaCorr2+PrefSPDorSDD/LMEEoutput-1full.root LMEEoutput-316-1full.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/016-LEGO316-EtaCorr2+PrefSPDorSDD/LMEEoutput-2low.root LMEEoutput-316-2low.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/016-LEGO316-EtaCorr2+PrefSPDorSDD/LMEEoutput-3hig.root LMEEoutput-316-3hig.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/017-LEGO319-EtaCorr3+PrefSPDfirst2/LMEEoutput-1full.root LMEEoutput-319-1full.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/017-LEGO319-EtaCorr3+PrefSPDfirst2/LMEEoutput-2low.root LMEEoutput-319-2low.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/017-LEGO319-EtaCorr3+PrefSPDfirst2/LMEEoutput-3hig.root LMEEoutput-319-3hig.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/018-LEGO347-semi-usingEtaCorr/LMEEoutput-1full.root LMEEoutput-347-1full.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/018-LEGO347-semi-usingEtaCorr/LMEEoutput-2low.root LMEEoutput-347-2low.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/018-LEGO347-semi-usingEtaCorr/LMEEoutput-3hig.root LMEEoutput-347-3hig.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/021-LEGO480-PrefSPDfirst3+PrefSPDorSDD2/LMEEoutput-1full.root LMEEoutput-480-1full.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/021-LEGO480-PrefSPDfirst3+PrefSPDorSDD2/LMEEoutput-2low.root LMEEoutput-480-2low.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/021-LEGO480-PrefSPDfirst3+PrefSPDorSDD2/LMEEoutput-3hig.root LMEEoutput-480-3hig.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/023-LEGO483-V0noTOF+SPDfirstV0+SPDorSDDV0/LMEEoutput-1full.root LMEEoutput-483-1full.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/023-LEGO483-V0noTOF+SPDfirstV0+SPDorSDDV0/LMEEoutput-2low.root LMEEoutput-483-2low.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/023-LEGO483-V0noTOF+SPDfirstV0+SPDorSDDV0/LMEEoutput-3hig.root LMEEoutput-483-3hig.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/024-LEGO484-EtaCorr4+std_10to50cent/LMEEoutput-1full.root LMEEoutput-484-1full.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/024-LEGO484-EtaCorr4+std_10to50cent/LMEEoutput-2low.root LMEEoutput-484-2low.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/024-LEGO484-EtaCorr4+std_10to50cent/LMEEoutput-3hig.root LMEEoutput-484-3hig.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/028-LEGO488-Pref_theta+Pref_phiv/LMEEoutput-1full.root LMEEoutput-488-1full.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/028-LEGO488-Pref_theta+Pref_phiv/LMEEoutput-2low.root LMEEoutput-488-2low.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/028-LEGO488-Pref_theta+Pref_phiv/LMEEoutput-3hig.root LMEEoutput-488-3hig.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/029-LEGO489-Pref_theta+Pref_phiv-wider/LMEEoutput-1full.root LMEEoutput-489-1full.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/029-LEGO489-Pref_theta+Pref_phiv-wider/LMEEoutput-2low.root LMEEoutput-489-2low.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/029-LEGO489-Pref_theta+Pref_phiv-wider/LMEEoutput-3hig.root LMEEoutput-489-3hig.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/030-LEGO490-randomDau_check/LMEEoutput-1full.root LMEEoutput-490-1full.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/030-LEGO490-randomDau_check/LMEEoutput-2low.root LMEEoutput-490-2low.root
//ln -s /Users/Patrick/Desktop/Analyse/008_PbPb_DieleFW/030-LEGO490-randomDau_check/LMEEoutput-3hig.root LMEEoutput-490-3hig.root
//
//ln -s ../../PairEffCalc/pairEff_raw-17h-std.root pairEff_raw-17h-std.root
//ln -s ../../PairEffCalc/pairEff_raw-17g-std.root pairEff_raw-17g-std.root
//