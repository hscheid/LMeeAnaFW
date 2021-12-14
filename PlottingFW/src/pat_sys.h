// input data files. make sure to edit the other strings accordingly!
TString name[] = {
  //set this order such that it complies with kDoAOD*8+kDo4D*4+kDoSemi*2+(low/hig)
  "", "", "", "", // ESD 3D, not needed
  "./input/PbPb/data_4D_merged/LMEEoutput-cent-ESD-cut16-2low.root", // ESD 4D (with+without ITScuts, pt200+pt400). Bad TPC dEdx correction.
  "./input/PbPb/data_4D_merged/LMEEoutput-cent-ESD-cut16-1hig.root",
  "./input/PbPb/data_4D_merged/LMEEoutput-semi-ESD-cut16-2low.root",
  "./input/PbPb/data_4D_merged/LMEEoutput-semi-ESD-cut16-1hig.root",
  "./input/PbPb/data_merged/LMEEoutput-cent-2low.root", // AOD 3D (cut01-20, with opening angle cut)
  "./input/PbPb/data_merged/LMEEoutput-cent-3hig.root",
  "./input/PbPb/data_merged/LMEEoutput-semi-2low.root",
  "./input/PbPb/data_merged/LMEEoutput-semi-3hig.root",
  "./input/PbPb/data_4D/cut16-cent-AOD-2pref/LMEEoutput-2low.root", // AOD 4D (w/o + w/ 2 prefilters (m<40, t<80 / phiV>2.36, m<40), pt200+pt400)
  "./input/PbPb/data_4D/cut16-cent-AOD-2pref/LMEEoutput-3hig.root",
  "./input/PbPb/data_4D/cut16-semi-AOD-2pref/LMEEoutput-2low.root",
  "./input/PbPb/data_4D/cut16-semi-AOD-2pref/LMEEoutput-3hig.root",
  "" // 16+ maybe for MC...
};
//
// further details of input data
TString tree_name[] = {"reichelt_LMEEPbPb2011_out"}; // extend when comparing PR with CK!
Int_t iSet;
const Int_t NcutsMAX = 20;
TString cut_setting[/*iSet*/][NcutsMAX] = { // always adapt to input data files!
  //set this order such that it complies with kDoAOD*2+kDo4D*1
  { "","","","","","","","","","","","","","","","","","","","" }, // ESD 3D, not needed
  { "","","","","","","","","","","","","","","","cut16_SPDorSDD14_PID16","","","","" }, // ESD 4D
  { "cut01_SPD1_PID1","cut02_SPD2_PID2","cut03_SPD3_PID3","cut04_SPD4_PID4","cut05_SPD5_PID1","cut06_SPD6_PID6",
    "cut07_SPD7_PID7","cut08_SPD8_PID8","cut09_SPD9_PID9","cut10_SPD1_PID10","cut11_SPD11_PID11","cut12_SPD11_PID12",
    "cut13_SPD6_PID13","cut14_SPDorSDD14_PID14","cut15_SPDorSDD15_PID13","cut16_SPDorSDD14_PID16",
    "cut17_SPDorSDD17_PID16","cut18_SPDorSDD15_PID1","cut19_SPDorSDD17_PID6","cut20_SPDorSDD17_PID10" }, // AOD 3D
  { "","","","","","","","","","","","","","","","cut16_SPDorSDD14_PID16","","","","" } // AOD 4D
};
Int_t Ncuts; // filled by GetNcuts(). //=sizeof(cut_setting)/sizeof(*cut_setting);
// config string for manager
TString cconfig[NcutsMAX * 8]; // filled in ProcessInputfiles().
Int_t n_config; // calculated in ProcessInputfiles().

// text for legend and maybe signal name
TString caption[] = { // do not use a colon(:)!
  "cut01_SPD1_PID1","cut02_SPD2_PID2","cut03_SPD3_PID3","cut04_SPD4_PID4","cut05_SPD5_PID1","cut06_SPD6_PID6",
  "cut07_SPD7_PID7","cut08_SPD8_PID8","cut09_SPD9_PID9","cut10_SPD1_PID10","cut11_SPD11_PID11","cut12_SPD11_PID12",
  "cut13_SPD6_PID13","cut14_SPDorSDD14_PID14","cut15_SPDorSDD15_PID13","cut16_SPDorSDD14_PID16",
  "cut17_SPDorSDD17_PID16","cut18_SPDorSDD15_PID1","cut19_SPDorSDD17_PID6","cut20_SPDorSDD17_PID10"
};

// corresponding input efficiency files
TString effi_name[] = {
  // set this order such that it complies with kDoEffGen*4+kDoSemi*2+kDoPt400.
  "../PairEffCalc/output/measurable/pairEff_raw-0010-pt200.root",
  "../PairEffCalc/output/measurable/pairEff_raw-0010-pt400.root",
  "../PairEffCalc/output/measurable/pairEff_raw-1050-pt200.root",
  "../PairEffCalc/output/measurable/pairEff_raw-1050-pt400.root",
  "../PairEffCalc/output/generated/pairEff_raw-0010-pt200.root",
  "../PairEffCalc/output/generated/pairEff_raw-0010-pt400.root",
  "../PairEffCalc/output/generated/pairEff_raw-1050-pt200.root",
  "../PairEffCalc/output/generated/pairEff_raw-1050-pt400.root",
//  "../PairEffCalc/output/measurable+ITScuts/pairEff_raw-0010-pt200.root",
//  "../PairEffCalc/output/measurable+ITScuts/pairEff_raw-0010-pt400.root",
//  "../PairEffCalc/output/measurable+ITScuts/pairEff_raw-1050-pt200.root",
//  "../PairEffCalc/output/measurable+ITScuts/pairEff_raw-1050-pt400.root",
  ""
};
// name of 2D generated and reconstructed histogram
TString effi_gen[] = {
  // set this order such that it complies with kDoEffGen*4+kDoOpAngle*2+kDoPt400.
  "NGenPairs_pt200_3500",
  "NGenPairs_pt400_3500",
  "NGenPairs_pt200_3500_opAngle50",
  "NGenPairs_pt400_3500_opAngle50",
  "hNGenPairs_pt200",           // EffGen was created with an older version of our pair generator, where histograms were called differently.
  "hNGenPairs_pt400",
  "hNGenPairs_pt200_opAngle50",
  "hNGenPairs_pt400_opAngle50"
};
TString effi_rec; //effi_rec[Ncuts * 4]; // filled in ProcessInputfiles().

// cocktail files
TString cocktail_files[] = {
  // set this order such that it complies with kDoSemi*2+kDoPt400.
//  "./input/PbPb/cocktail/cocktail_PbPb_0010.root",
//  "./input/PbPb/cocktail/cocktail_PbPb_1020.root:./input/PbPb/cocktail/cocktail_PbPb_2030.root:./input/PbPb/cocktail/cocktail_PbPb_3040.root:./input/PbPb/cocktail/cocktail_PbPb_4050.root",
//  "./input/PbPb/cocktail/cocktail-00-kPbPb_276_0010_pt200.root", // before code migration, default decay table
//  "./input/PbPb/cocktail/cocktail-00-kPbPb_276_0010_pt400.root", // 
//  "./input/PbPb/cocktail/cocktail-01-kPbPb_276_0010_pt200.root", // (01) = after code migration to AliPhysics, decay table from Theo.
//  "./input/PbPb/cocktail/cocktail-01-kPbPb_276_0010_pt400.root",
//  "./input/PbPb/cocktail/cocktail-01-kPbPb_276_1020_pt200.root:./input/PbPb/cocktail/cocktail-01-kPbPb_276_2030_pt200.root:./input/PbPb/cocktail/cocktail-01-kPbPb_276_3040_pt200.root:./input/PbPb/cocktail/cocktail-01-kPbPb_276_4050_pt200.root",
//  "./input/PbPb/cocktail/cocktail-01-kPbPb_276_1020_pt400.root:./input/PbPb/cocktail/cocktail-01-kPbPb_276_2030_pt400.root:./input/PbPb/cocktail/cocktail-01-kPbPb_276_3040_pt400.root:./input/PbPb/cocktail/cocktail-01-kPbPb_276_4050_pt400.root",
//  "./input/PbPb/cocktail/cocktail-02-kPbPb_276_0010_pt200.root", // (02) = (01) + using private fit on charged pions (range 0.1-7 GeV/c).
//  "./input/PbPb/cocktail/cocktail-02-kPbPb_276_0010_pt400.root",
//  "./input/PbPb/cocktail/cocktail-02-kPbPb_276_1050_pt200.root",
//  "./input/PbPb/cocktail/cocktail-02-kPbPb_276_1050_pt400.root",
  "./input/PbPb/cocktail/cocktail-03-kPbPb_276_0010_pt200.root", // (03) = (02) + using new official decaytable + seed fix.
  "./input/PbPb/cocktail/cocktail-03-kPbPb_276_0010_pt400.root",
  "./input/PbPb/cocktail/cocktail-03-kPbPb_276_1050_pt200.root",
  "./input/PbPb/cocktail/cocktail-03-kPbPb_276_1050_pt400.root",
  ""
};
TString jpsi_files[] = {
  // set this order such that it complies with kDoSemi*2+kDoPt400.
  "./input/PbPb/cocktail/jpsi-01-pt200.root", // (01): pp param "simple", no R_AA scaling. with smearing for 00-10% centrality
  "./input/PbPb/cocktail/jpsi-01-pt400.root",
  "./input/PbPb/cocktail/jpsi-01-pt200.root",
  "./input/PbPb/cocktail/jpsi-01-pt400.root",
  ""
};
TString rapp_files[] = {
  // set this order such that it complies with [[[kDoSemi*2+]]]kDoPt400.
  "./input/PbPb/cocktail/rapp_Nch1600_pt200.txt",
  "./input/PbPb/cocktail/rapp_Nch1600_pt400.txt",
//  "./input/PbPb/cocktail/",
//  "./input/PbPb/cocktail/",
  ""
};

TString cocktail_list[] = {
  // set this order such that it complies with kDoOpAngle*1.
  "Mee_Ptee_angleSmeared",
  "Mee_Ptee_angleSmeared_opAngle0.05",
  ""
};
// cocktail histograms
TString cocktail_histograms[] = {
  // set this order such that it complies with kUseRapp?1:0.
//  "pteevsmeePion:pteevsmeeEta:pteevsmeeEtaPrime:pteevsmeeRho:pteevsmeeOmega:pteevsmeeOmegaDalitz:pteevsmeePhi:pteevsmeePhiDalitz", //:pteevsmeeJPsi
//  "pteevsmeePion:pteevsmeeEta:pteevsmeeEtaPrime:pteevsmeeOmega:pteevsmeeOmegaDalitz", // for tests
  "Mee_Ptee_Pion*:Mee_Ptee_Eta*:Mee_Ptee_EtaPrime*:Mee_Ptee_Rho*:Mee_Ptee_Omega*:Mee_Ptee_OmegaDalitz*:Mee_Ptee_Phi*:Mee_Ptee_PhiDalitz*",
  "Mee_Ptee_Pion*:Mee_Ptee_Eta*:Mee_Ptee_EtaPrime*:Mee_Ptee_Omega*:Mee_Ptee_OmegaDalitz*:Mee_Ptee_Phi*:Mee_Ptee_PhiDalitz*", // without rho
//  "Mee_Ptee_Pion:Mee_Ptee_Eta:Mee_Ptee_Omega", // for tests
  ""
};
// heavy flavour files
TString heavyfl_files[] = {
  // set this order such that it complies with kUseHfeRaa*2+kDoSemi.
//  "./input/PbPb/cocktail/charm_PbPb_201403_BsE.root", // old
//  "./input/PbPb/cocktail/charm-01-PbPb-kPythiaPerugia11_pp2760GeV.root",  // with smearing for 00-10% centrality
//  "./input/PbPb/cocktail/beauty-01-PbPb-kPythiaPerugia11_pp2760GeV.root", // with smearing for 00-10% centrality
//  "./input/PbPb/cocktail/charm-01-PbPb-kPythiaPerugia11_pp2760GeV.root:./input/PbPb/cocktail/beauty-01-PbPb-kPythiaPerugia11_pp2760GeV.root", // both. "01" has no high-pt cut!
  "./input/PbPb/cocktail/charm-02-PbPb-kPythiaPerugia11_pp2760GeV.root:./input/PbPb/cocktail/beauty-02-PbPb-kPythiaPerugia11_pp2760GeV.root", // re-ana with 20k(gen=40k) per job.
  "./input/PbPb/cocktail/charm-02-PbPb-kPythiaPerugia11_pp2760GeV.root:./input/PbPb/cocktail/beauty-02-PbPb-kPythiaPerugia11_pp2760GeV.root", // just a copy (should do re-ana using smearing for 10-50%).
  "./input/PbPb/cocktail/charm-03-PbPb-kPythiaPerugia11_pp2760GeV-RAA0010.root:./input/PbPb/cocktail/beauty-03-PbPb-kPythiaPerugia11_pp2760GeV-RAA0010.root", // re-ana with HFE RAA from 0-10% (fit with pol1).
  "./input/PbPb/cocktail/charm-03-PbPb-kPythiaPerugia11_pp2760GeV-RAA1040.root:./input/PbPb/cocktail/beauty-03-PbPb-kPythiaPerugia11_pp2760GeV-RAA1040.root", // re-ana with HFE RAA from 10-20% & 20-40%.
  "./input/PbPb/cocktail/charm-04-PbPb-kPythiaPerugia11_pp2760GeV-rndmPhi.root:./input/PbPb/cocktail/beauty-02-PbPb-kPythiaPerugia11_pp2760GeV.root", // charm with random phi (azimuth) of ele.
  "./input/PbPb/cocktail/charm-04-PbPb-kPythiaPerugia11_pp2760GeV-rndmPhi.root:./input/PbPb/cocktail/beauty-02-PbPb-kPythiaPerugia11_pp2760GeV.root", // just a copy.
  "./input/PbPb/cocktail/charm-05-PbPb-kPythiaPerugia11_pp2760GeV-smear-eta1-phi1.root:./input/PbPb/cocktail/beauty-02-PbPb-kPythiaPerugia11_pp2760GeV.root", // charm with eta & phi of ele smeared by gaus(0,1).
  "./input/PbPb/cocktail/charm-05-PbPb-kPythiaPerugia11_pp2760GeV-smear-eta1-phi1.root:./input/PbPb/cocktail/beauty-02-PbPb-kPythiaPerugia11_pp2760GeV.root", // just a copy.
  "./input/PbPb/cocktail/charm-06-PbPb-kPythiaPerugia11_pp2760GeV-smear-eta2-phi2.root:./input/PbPb/cocktail/beauty-02-PbPb-kPythiaPerugia11_pp2760GeV.root", // charm with eta & phi of ele smeared by gaus(0,2).
  "./input/PbPb/cocktail/charm-06-PbPb-kPythiaPerugia11_pp2760GeV-smear-eta2-phi2.root:./input/PbPb/cocktail/beauty-02-PbPb-kPythiaPerugia11_pp2760GeV.root", // just a copy.
  "./input/PbPb/cocktail/charm-07-PbPb-kPythiaPerugia11_pp2760GeV-sampling-eta.root:./input/PbPb/cocktail/beauty-02-PbPb-kPythiaPerugia11_pp2760GeV.root", // charm with eta ele sampled from eta-pt-distribution.
  "./input/PbPb/cocktail/charm-07-PbPb-kPythiaPerugia11_pp2760GeV-sampling-eta.root:./input/PbPb/cocktail/beauty-02-PbPb-kPythiaPerugia11_pp2760GeV.root", // just a copy.
  "", "", //kUseHfeRaa=6 empty
  "./input/PbPb/cocktail/charm-02-PbPb-kPythiaPerugia11_pp2760GeV.root:./input/PbPb/cocktail/beauty-02-PbPb-kPythiaPerugia11_pp2760GeV.root", //kUseHfeRaa=7. just a copy.
  "./input/PbPb/cocktail/charm-02-PbPb-kPythiaPerugia11_pp2760GeV.root:./input/PbPb/cocktail/beauty-02-PbPb-kPythiaPerugia11_pp2760GeV.root", //kUseHfeRaa=7. just a copy.
  "", "", //kUseHfeRaa=8 empty
  "./input/PbPb/cocktail/charm-02-PbPb-kPythiaPerugia11_pp2760GeV.root:./input/PbPb/cocktail/beauty-02-PbPb-kPythiaPerugia11_pp2760GeV.root", //kUseHfeRaa=9, charm is removed later.
  "./input/PbPb/cocktail/charm-02-PbPb-kPythiaPerugia11_pp2760GeV.root:./input/PbPb/cocktail/beauty-02-PbPb-kPythiaPerugia11_pp2760GeV.root", //kUseHfeRaa=9, charm is removed later.
  ""
};
TString heavyfl_list = "lowee:lowee";
// heavy flavour histograms
TString heavyfl_histograms[] = {
  // set this order such that it complies with kDoOpAngle*2+kDoPt400.
//  "hpt_mass4",
//  "hMeePtee_ULS_eta08_pt400_opAngle50_smeared",//"-hMeePtee_LS_eta08_pt400_opAngle50_smeared",
//  "hMeePtee_ULS_eta08_pt400_opAngle50_smeared:hMeePtee_ULS_eta08_pt400_opAngle50",
  "hMeePtee_ULS_eta08_pt200-hMeePtee_LS_eta08_pt200:hMeePtee_ULS_eta08_pt200-hMeePtee_LS_eta08_pt200",
  "hMeePtee_ULS_eta08_pt400-hMeePtee_LS_eta08_pt400:hMeePtee_ULS_eta08_pt400-hMeePtee_LS_eta08_pt400",
//  "hMeePtee_ULS_eta08_pt200_opAngle50_smeared-hMeePtee_LS_eta08_pt200_opAngle50_smeared:hMeePtee_ULS_eta08_pt200_opAngle50-hMeePtee_LS_eta08_pt200_opAngle50", // for "charm-01"
//  "hMeePtee_ULS_eta08_pt400_opAngle50_smeared-hMeePtee_LS_eta08_pt400_opAngle50_smeared:hMeePtee_ULS_eta08_pt400_opAngle50-hMeePtee_LS_eta08_pt400_opAngle50", // for "charm-01"
  "hMeePtee_ULS_eta08_pt200_opAngle50-hMeePtee_LS_eta08_pt200_opAngle50:hMeePtee_ULS_eta08_pt200_opAngle50-hMeePtee_LS_eta08_pt200_opAngle50", // for "charm-02"
  "hMeePtee_ULS_eta08_pt400_opAngle50-hMeePtee_LS_eta08_pt400_opAngle50:hMeePtee_ULS_eta08_pt400_opAngle50-hMeePtee_LS_eta08_pt400_opAngle50", // for "charm-02"
  ""
};
// heavy flavour histograms for nevents
TString heavyfl_hist_Nevents[] = {
  "hee_c",
  "hRapCharmQuarkMethod1",//"hNEvents",
  "hRapCharmQuarkMethod1:hRapBeautyQuarkMethod1",
  ""
};
//Int_t which_cockt_hists = 0;
//Int_t which_heavyfl_files = 0;
Int_t   which_heavyfl_Nevents = 2;
//
// desired binning for output. will also be used for efficiency correction.
// see patrick_common.h
//
// desired binning for cocktail.
// may be much finer than for data, but the bin edges should overlap to avoid inconsistencies when doing projections!
Double_t mee_bin_cocktail[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, //0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38, 0.40, 0.42, 0.44, 0.46, 0.48, 
  //0.50, 0.52, 0.54, 0.56, 0.58, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.72, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98, 
  //1.00, 1.02, 1.04, 1.06, 1.08, 1.10, 1.12, 1.14, 1.16, 1.18, 1.20, 1.22, 1.24, 1.26, 1.28, 1.30, 1.32, 1.34, 1.36, 1.38, 1.40, 1.42, 1.44, 1.46, 1.48, 1.50, 1.52, 1.54, 1.56, 1.58, 1.60, 
  0.14, 0.18, 0.22, 0.26, 0.30, 0.34, 0.38, 0.42, 0.46, 0.50, 0.54, 0.58, 0.62, 0.66, 0.70, 0.74, /*0.76,*/ 0.78, /*0.80,*/ 0.82, 0.86, 0.90, 0.94, 0.98, 
  /*1.00,*/ 1.02, /*1.04,*/ 1.06, 1.10, 1.20, 1.30, 1.40, 1.50, 1.60, 
  1.70, 1.80, 1.90, 2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 2.95, 3.00, 3.05, 3.10, 3.15, 3.20, 3.30, 3.40, 3.50, 3.60, 3.70, 3.80, 3.90, 
  4.00/*, 4.10, 4.20, 4.30, 4.40, 4.50, 4.60, 4.70, 4.80, 4.90, 5.00*/ };

// cocktail compatible to albertos points:
//Double_t mee_bin_cocktail[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 
//  0.14, 0.15, 0.18, 0.20, 0.22, 0.26, 0.30, 0.34, 0.38, 0.42, 0.46, 0.50, 0.54, 0.58, 0.62, 0.66, 0.70, 0.74, /*0.76,*/ 0.78, /*0.80,*/ 0.82, 0.86, 0.90, 0.94, 0.98, 
//  1.00, 1.02, /*1.04,*/ 1.06, 1.10, 1.20, 1.30, 1.40, 1.50, 1.60, 
//  1.70, 1.80, 1.90, 2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 2.95, 3.00, 3.05, 3.10, 3.15, 3.20, 3.30, 3.40, 3.50, 3.60, 3.70, 3.80, 3.90, 
//  4.00, 4.50, 5.00 };

Double_t ptee_bin_cocktail[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 
  2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 5.2, 5.4, 5.6, 5.8, 6.0 };
Int_t n_mee_bin_cocktail = sizeof(mee_bin_cocktail)/sizeof(*mee_bin_cocktail) -1;
Int_t n_ptee_bin_cocktail = sizeof(ptee_bin_cocktail)/sizeof(*ptee_bin_cocktail) -1;
//
// Opening angle cut that shall be applied if kDoOpAngle=kTRUE.
const Double_t thetaEEmin = 0.05; // dont change this value in pat_sys, because many things exist only for 50 mrad.

//_______________________________________________________________________________________________
// function declarations
LmCocktail*   ProcessCocktail();
const char*   GetNameCharm(Int_t hfeRaa=0);
const char*   GetNameBeauty(Int_t hfeRaa=0);
const char*   GetNameSum(Int_t hfeRaa=0);
Int_t         GetColorCharm(Int_t hfeRaa=0);
LmCocktail*   CreateCocktailHeavyFlavour(Int_t hfeRaa=0);
LmCocktailMan* CreateManagerHeavyFlavour(Int_t hfeRaa=0);
  

Int_t         GetNcuts();
Int_t         FindIndexOfCut(TString sCut);
// general
LmSignal*     CreateFinalSignal(TString newName="", Int_t getAverageSig=0);
void          CreateCorrelationPlot(LmHandler* han_compare);
// cut16 4D
void          ProcessCut16_4D_AOD(LmHandler* han16_4D, Bool_t doPlots=kFALSE);
LmSignal*     ProcessOneInput(LmManager* mgr);
// 20 cut settings
void          ProcessSystematics(LmHandler* han_systematic, LmHandler* han_analysis);
void          ProcessInputfiles(LmHandler* han_sys, LmHandler* han_ana);
void          ProcessSingleInputs(TString config[], TString effiName, 
                                  std::vector<LmManager*> &mgrVec,     std::vector<LmBackground*> &bkgVec,     std::vector<LmSignal*> &sigVec,
                                  std::vector<LmManager*> &mgrVec_sys, std::vector<LmBackground*> &bkgVec_sys, std::vector<LmSignal*> &sigVec_sys);
void          ProcessCombineHandlers(std::vector<LmSignal*> &sigVec, std::vector<LmHandler*> &hanVec, Bool_t doPlots,
                                     std::vector<Double_t> binsPtee_forMee, std::vector<Double_t> binsMee_forPtee,
                                     Double_t plotMeeMin, Double_t plotMeeMax, Double_t plotPteeMin, Double_t plotPteeMax);
//_______________________________________________________________________________________________

Int_t collsystem = -1;
LmCocktail* cocktRapp = 0x0;
LmCocktail* cocktSum = 0x0;

//_______________________________________________________________________________________________
LmCocktail* ProcessCocktail()
{
  Printf("______ process cocktail ______");
  // cocktail (handles the cocktail spectra)
  if (kDoSemi) collsystem = LmCocktail::kPbPb_1050_276;
  else         collsystem = LmCocktail::kPbPb_0010_276;
  LmCocktail* cockt = new LmCocktail(collsystem);
  
  // cocktail managers (organize input)
  // Rapp
  LmCocktailMan* cocktmanRapp = 0x0;
  if (kUseRapp>0) {
    Printf(" * Rapp");
    cocktmanRapp = new LmCocktailMan();
    cocktmanRapp->SetInputfiles(const_cast<char*>(rapp_files[/*kDoSemi*2+*/kDoPt400].Data()));
    cocktmanRapp->SetInputlists("%lg %*lg %*lg %lg:%lg %*lg %*lg %*lg %*lg %lg");
    cocktmanRapp->SetInputhistAndDim("HGmed:QGP", 1); // 1D // "HGvac:HGmed:HGdrop:QGP"
    //  cocktmanRapp->SetInputlists("%lg %*lg %*lg %*lg %*lg %lg");
    //  cocktmanRapp->SetInputhistAndDim("QGP", 1); // 1D
    //  cocktmanRapp->SetRelUncertainties("+0.1:-0.1");
    cocktmanRapp->SetArbitraryScaling(1.6*(0.8/0.84)); // Rapps result is dN/(dMdy) / (dNch/dy) and for |y_e|<0.84, while my results are dN/dM for |eta_e|~|y_e|<0.8. For correction I assume flat y-dependence.
    //if (kDoSemi) cocktmanRapp->SetArbitraryScaling( 1600 * cocktmanRapp->GetArbitraryScaling() );
    /*else*/         cocktmanRapp->SetArbitraryScaling( 1600 * cocktmanRapp->GetArbitraryScaling() );
    cocktmanRapp->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
    cocktmanRapp->Process(LmCocktailMan::kRapp);
  }
  // for resonances
  Printf(" * light flavour");
  LmCocktailMan* cocktmanReso = 0x0;
  cocktmanReso = new LmCocktailMan();
  cocktmanReso->SetInputfiles(const_cast<char*>(cocktail_files[kDoSemi*2+kDoPt400].Data()));
  cocktmanReso->SetInputlists(const_cast<char*>(cocktail_list[kDoOpAngle*1/*-kUse16_4D*/].Data()));
  cocktmanReso->SetInputhistAndDim(const_cast<char*>(cocktail_histograms[kUseRapp?1:0].Data()), 2); // 2D
  TString filesSys(cocktail_files[kDoSemi*2+kDoPt400].Data());
  filesSys.ReplaceAll(".root","-Low.root");
  cocktmanReso->SetInputfilesAndHistsLow(const_cast<char*>(filesSys.Data()), const_cast<char*>(cocktail_histograms[kUseRapp?1:0].Data()));
  filesSys.ReplaceAll("-Low.root","-High.root");
  cocktmanReso->SetInputfilesAndHistsHigh(const_cast<char*>(filesSys.Data()), const_cast<char*>(cocktail_histograms[kUseRapp?1:0].Data()));
  //cocktmanReso->SetArbitraryScaling(1./(24*2000)); // for cocktail-00
  //cocktmanReso->SetUndoBinwidthNormalizationMee();
  cocktmanReso->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanReso->Process( kUseLFsum?LmCocktailMan::kLFsum:LmCocktailMan::kResonances );//kResonances or kLFsum
  // for heavy flavours
  LmCocktailMan* cocktmanHF = 0x0;
  cocktmanHF = CreateManagerHeavyFlavour(kUseHfeRaa);
  // for J/psi
  Printf(" * J/psi");
  LmCocktailMan* cocktmanJpsi = new LmCocktailMan();
  cocktmanJpsi->SetInputfiles(const_cast<char*>(jpsi_files[kDoSemi*2+kDoPt400].Data()));
  cocktmanJpsi->SetInputlists(const_cast<char*>(cocktail_list[kDoOpAngle*1/*-kUse16_4D*/].Data()));
  cocktmanJpsi->SetInputhistAndDim("Mee_Ptee_Jpsi_std*", 2); // 2D
  if (kDoSemi) cocktmanJpsi->SetRelUncertainties(Form("%f", TMath::Sqrt(0.132*0.132+0.125*0.125))); // correl+uncorrel syst, Julian Thesis p. 73.
  else         cocktmanJpsi->SetRelUncertainties(Form("%f", TMath::Sqrt(0.132*0.132+0.128*0.128))); // correl+uncorrel syst, Julian Thesis p. 73.
  //  cocktmanJpsi->SetInputfilesAndHistsLow(const_cast<char*>(jpsi_files[kDoSemi*2+kDoPt400].Data()), "Mee_Ptee_Jpsi_low*");
  //  cocktmanJpsi->SetInputfilesAndHistsHigh(const_cast<char*>(jpsi_files[kDoSemi*2+kDoPt400].Data()), "Mee_Ptee_Jpsi_high*");
  // scale Jpsi from pp @ 7 TeV to Pb-Pb @ 2.76 TeV
  cocktmanJpsi->SetArbitraryScaling( cockt->GetNcoll() * 62.8/64.5 );
  // scale Jpsi with measured R_AA:
  if (kDoSemi) cocktmanJpsi->SetArbitraryScaling( 0.74 * cocktmanJpsi->GetArbitraryScaling() ); // 10-40%, read off from Julians figure 4.26 
  else         cocktmanJpsi->SetArbitraryScaling( 0.65 * cocktmanJpsi->GetArbitraryScaling() ); //  0-10%, read off from Julians figure 4.26
  cocktmanJpsi->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  cocktmanJpsi->Process(LmCocktailMan::kJpsi);
  // for virtual photons
  // (not available yet)
  
  // attach managers to cocktail and process it
  Printf(" * Combine all");
  if (cocktmanReso) cockt->AttachManager( *cocktmanReso );
  if (cocktmanHF  ) cockt->AttachManager( *cocktmanHF );
  if (cocktmanJpsi) cockt->AttachManager( *cocktmanJpsi );

// @TODO: von Carsten, was passt fuer mich?
  cockt->SetBRRelUncertainty        (LmCocktailPart::kPion, -0.0298, 0.0298);                                                            
  cockt->SetMTscalingRelUncertainty (LmCocktailPart::kEta, -0.2, +0.2);                                                                
  //cockt->SetAdditionalRelUncertainty(LmCocktailPart::kEta, -0.1, +0.1);                                                                  
  cockt->SetBRRelUncertainty        (LmCocktailPart::kEta, 0.058, 0.058);                                                                
  cockt->SetMTscalingRelUncertainty (LmCocktailPart::kEtaPrime, -0.2, +0.2);                                                             
  cockt->SetBRRelUncertainty        (LmCocktailPart::kEtaPrime, 0.0638, 0.0638);                                                         
  cockt->SetMTscalingRelUncertainty (LmCocktailPart::kRho, -0.2, +0.2);                                                                  
  cockt->SetBRRelUncertainty        (LmCocktailPart::kRho, 0.011, 0.011);                                                                
  cockt->SetMTscalingRelUncertainty (LmCocktailPart::kOmega, -0.2, +0.2);                                                                
  cockt->SetBRRelUncertainty        (LmCocktailPart::kOmega, 0.0192, 0.0192);                                                            
  cockt->SetMTscalingRelUncertainty (LmCocktailPart::kPhi, -0.3, +0.3);                                                                  
  cockt->SetBRRelUncertainty        (LmCocktailPart::kPhi, 0.0102, 0.0102);                                                              
//  cockt->PrintUncertainties();                                                                                                           
  
  if (kUseRapp==1) {
    cockt->SetName("sum");
    cockt->AttachManager( *cocktmanRapp );
  }
  cockt->Process(LmCocktail::kStd); // fill vector of LmCocktailPart according to attached cocktailmanagers. set their names, types, colors, etc...
  if (kUseHfeRaa!=9) cockt->GetLmCocktailPart(LmCocktailPart::kCharm)->SetName(GetNameCharm(kUseHfeRaa));
  cockt->GetLmCocktailPart(LmCocktailPart::kBeauty)->SetName(GetNameBeauty(kUseHfeRaa));

  if (kUseRapp==2 || kUseRapp==3) {
    cocktRapp = new LmCocktail(collsystem, "Rapp sum");
    cocktRapp->AttachManager( *cocktmanRapp );
    cocktRapp->Process(LmCocktail::kFromManagers); // kFromManagers is the same as kStd
    // one could try to add the Rapp function to the listoffunctions and draw it as dashed line to visualize extrapolation...
    //if (fFitPtr) fH2D->GetListOfFunctions()->Add( (TF1*)fFitPtr->Clone("") );
    // Combine both cocktails:
    cocktSum = new LmCocktail(collsystem, "cocktail + model");
    cocktSum->SetDrawStyle("hist c");
    cocktSum->AttachPart( *(cockt    ->GetLmCocktailPart(LmCocktailPart::kSum)  ->Copy("hadronic cocktail", kRed)) );
    cockt    ->GetLmCocktailPart(LmCocktailPart::kSum)->GetSpectrum2D()->SetLineColor(kRed); // to get a red line in the ratio.
    cocktSum->AttachPart( *(cocktRapp->GetLmCocktailPart(LmCocktailPart::kHGmed)->Copy()) );
    cocktSum->AttachPart( *(cocktRapp->GetLmCocktailPart(LmCocktailPart::kQGP)  ->Copy()) );
    cocktSum->Process(LmCocktail::kFromParticles);
  }
  if (kUseRapp==2) return cocktSum;
  if (kUseRapp==3) cockt->SetDrawOption(LmCocktail::kOnlySum);
  
  return cockt;
}

//_______________________________________________________________________________________________
const char* GetNameCharm(Int_t hfeRaa) {
  if (hfeRaa==0) return Form("c#bar{c}");
  if (hfeRaa==1) return Form("c#bar{c} w/ HFE #it{R}_{AA}");
  if (hfeRaa==2) return Form("c#bar{c} w/ random #it{#varphi}_{e}");
  if (hfeRaa==3) return Form("c#bar{c} w/ smeared #it{#varphi}_{e} & #it{#eta}_{e}");
//  if (hfeRaa==3) return Form("c#bar{c} w/ smear #it{#varphi}_{e} & #it{#eta}_{e} gaus(0,1)");
  if (hfeRaa==4) return Form("c#bar{c} w/ smear #it{#varphi}_{e} & #it{#eta}_{e} gaus(0,2)");
  if (hfeRaa==5) return Form("c#bar{c} w/ sampling #it{#eta}_{e}");
  return "c#bar{c}";
}

//_______________________________________________________________________________________________
const char* GetNameBeauty(Int_t hfeRaa) {
  if (hfeRaa==0) return Form("b#bar{b}");
  if (hfeRaa==1) return Form("b#bar{b} w/ HFE #it{R}_{AA}");
  // Option for long name is now gone: Form("%s w/ HFE it{R}_{AA}", cockt->GetLmCocktailPart(LmCocktailPart::kBeauty)->GetName()));
  return "b#bar{b}";
}

//_______________________________________________________________________________________________
const char* GetNameSum(Int_t hfeRaa) {
  if (hfeRaa==0) return Form("sum");
  if (hfeRaa==1) return Form("sum w/ HFE #it{R}_{AA}");
  return "sum";
}

//_______________________________________________________________________________________________
Int_t GetColorCharm(Int_t hfeRaa) {
  // @TODO: set good colors.
  switch (hfeRaa) {
    case 0: return kMagenta;
    case 1: return kMagenta;
    case 2: return kPink+2;
    case 3: return kViolet+1;
    case 4: break; // not tuned
    case 5: return kPink-2;
    default: return kMagenta;
  }
  return hfeRaa;
}

//_______________________________________________________________________________________________
LmCocktail* CreateCocktailHeavyFlavour(Int_t hfeRaa) {
  if (kDoSemi) collsystem = LmCocktail::kPbPb_1050_276;
  else         collsystem = LmCocktail::kPbPb_0010_276;
  LmCocktail* cocktHF = new LmCocktail(collsystem, GetNameCharm(hfeRaa));
  LmCocktailMan* cocktmanHF = CreateManagerHeavyFlavour(hfeRaa);
  cocktHF->AttachManager( *cocktmanHF );
  cocktHF->Process(LmCocktail::kFromManagers); // kFromManagers is the same as kStd
  cocktHF->SetDrawStyle("hist c");
  if (kUseHfeRaa==9) {
    // make charm and sum look identical
    cocktHF->GetLmCocktailPart(LmCocktailPart::kCharm)->GetSpectrum2D()->SetLineColor(GetColorCharm(hfeRaa));
    cocktHF->GetLmCocktailPart(LmCocktailPart::kSum)  ->GetSpectrum2D()->SetLineColor(GetColorCharm(hfeRaa));
  }
  if (kUseHfeRaa==7) {
//    cocktHF->SetDrawOption(LmCocktail::kAllButSum);
    cocktHF->GetLmCocktailPart(LmCocktailPart::kCharm) ->SetName(GetNameCharm(hfeRaa));
    cocktHF->GetLmCocktailPart(LmCocktailPart::kBeauty)->SetName(GetNameBeauty(hfeRaa));
    cocktHF->GetLmCocktailPart(LmCocktailPart::kSum)   ->SetName(GetNameSum(hfeRaa));
    if (hfeRaa==0) {
      // modify the default HF for comparison:
      cocktHF->GetLmCocktailPart(LmCocktailPart::kCharm) ->GetSpectrum2D()->SetLineStyle(7);
      cocktHF->GetLmCocktailPart(LmCocktailPart::kBeauty)->GetSpectrum2D()->SetLineStyle(7);
      cocktHF->GetLmCocktailPart(LmCocktailPart::kSum)   ->GetSpectrum2D()->SetLineStyle(7);
    }
  }
  return cocktHF;
}

//_______________________________________________________________________________________________
LmCocktailMan* CreateManagerHeavyFlavour(Int_t hfeRaa) {
  Printf(" * heavy flavour");
  LmCocktailMan* cocktmanHF = new LmCocktailMan();
  cocktmanHF->SetInputfiles(const_cast<char*>(heavyfl_files[hfeRaa*2+kDoSemi].Data()));
  cocktmanHF->SetInputlists(const_cast<char*>(heavyfl_list.Data()));
  cocktmanHF->SetInputhistAndDim(const_cast<char*>(heavyfl_histograms[(kDoOpAngle/*-kUse16_4D*/)*2+kDoPt400].Data()), 2); // 2D
  cocktmanHF->SetHistForNevents( const_cast<char*>(heavyfl_hist_Nevents[which_heavyfl_Nevents].Data()));
  cocktmanHF->SetRelUncertainties("+0.60:-0.33:+0.35:-0.40"); // total cross-section uncertainties from papers (see LmCocktail constructor).
  cocktmanHF->SetArbitraryScaling(2); // when using nquarks histogram instead of nevents, by which the yield gets downscaled about 2 times stronger.
  cocktmanHF->SetRebinning2D(n_mee_bin_cocktail, mee_bin_cocktail, n_ptee_bin_cocktail, ptee_bin_cocktail);
  if (kUseHfeRaa==7 || kUseHfeRaa==9) cocktmanHF->SetRelUncertainties("0:0"); // no unc. because they would cover other charm versions in the comparison plot.
  cocktmanHF->Process(LmCocktailMan::kHeavyFl);
  if (kUseHfeRaa==9) {
    if (hfeRaa==9) cocktmanHF->RemoveEntry(0); // remove charm from the cocktail which will be subtracted.
    else           cocktmanHF->RemoveEntry(1); // remove beauty from all other HF cocktails to get only charm.
  }
  return cocktmanHF;
}

//_______________________________________________________________________________________________
void FillLegendCharm(TLegend* leg, LmHandler* han) {
  // assumption: use first signal and first projection bin along mee.
  Int_t i=0;
  Int_t proj=LmBaseSignal::kProjOnMee;
  Int_t bin =han->GetMaxBinProj(proj);
  TH1D* datahist = han->GetLmSignalI(i)->GetLmHist(LmSignal::kSubSig,bin,proj)->GetDatahist();
  datahist->SetLineColor(LmHelper::GetUniformColor(i, 8)); // needed beause handler only does it during printing.
  datahist->SetMarkerStyle(20);
  datahist->SetMarkerColor(LmHelper::GetUniformColor(i, 8));
  datahist->SetFillStyle(0);
  leg->AddEntry(datahist, Form("%s #minus cocktail #plus c#bar{c}",han->GetLmSignalName(0)), "lpe");
  Int_t ic=0;
  LmCocktail* cockt = han->GetCocktail(ic);
  while (cockt!=0x0) {
    cockt->GetSum1D(bin,proj)->SetLineWidth(2);
    cockt->GetSum1D(bin,proj)->Smooth();
    cockt->GetComponent1D(LmCocktailPart::kCharm,bin,proj)->Smooth(); // to be consistent with the sum, if both are drawn.
    leg->AddEntry(cockt->GetSum1D(bin,proj), cockt->GetName(), "l");
    ic++;
    cockt = han->GetCocktail(ic);
  }
  if (TMath::Abs(leg->GetY1() - leg->GetY2()) < LmHelper::kSmallDelta) {
    Double_t ydiff = leg->GetNRows()*0.045;
    leg->SetY1(leg->GetY2() - ydiff);
  }
}

//_______________________________________________________________________________________________
Int_t GetNcuts() {
  /// Count only non-empty cutset entries.
  Ncuts=0;
  for(Int_t iCuts = 0; iCuts < NcutsMAX; ++iCuts) {
    if (!cut_setting[iSet][iCuts].IsNull()) Ncuts++;
  }
  return Ncuts;
}

//_______________________________________________________________________________________________
Int_t FindIndexOfCut(TString sCut) {
  /// Find index relative to only non-empty cutset entries.
  Int_t index=0;
  for(Int_t iCuts = 0; iCuts < NcutsMAX; ++iCuts) {
    if (cut_setting[iSet][iCuts].IsNull()) continue;
    if (cut_setting[iSet][iCuts].Contains(sCut.Data())) return index;
    else index++;
  }
  LmHelper::Error(Form("FindIndexOfCut(): cut '%s' not found! Using cut #0.", sCut.Data()));
  return 0;
}


//_______________________________________________________________________________________________
void ProcessCut16_4D_AOD(LmHandler* han16_4D, Bool_t doPlots)
{
  Printf("______ process cut 16 4D AOD ______");
  effi_rec = Form("NRecPairs%s_hEff_Ele_%s_%s_3500_%s",(kDoPref?"Combined":""),"cut16_SPDorSDD14_PID16",sOptPt.Data(),sOptOpAngle.Data());
  effi_rec.Remove(TString::kTrailing, '_');
  // need to set eff_gen manually because of issue described below:
  TString eff_gen = Form("NGenPairs_%s_3500_%s",sOptPt.Data(),sOptOpAngle.Data());
  eff_gen.Remove(TString::kTrailing, '_');
  // efficiencies without opening angle cut now only exist in the output measurable+PrefPhiV. (the combination PrefTheta + noOpAngCut no longer exists)
  TString effi_file = Form("../PairEffCalc/output/measurable%s/pairEff_raw-%s-%s.root", ((kDoPref==2||kDoPref==0)?"+PrefPhiV":""), (kDoSemi?"1050":"0010"), sOptPt.Data());
  TString sConf_part2 = Form("reichelt_LMEEPbPb2011_out:cut16_SPDorSDD14_PID16%s_%s:cut16 AOD:%s:%s:%s", (kDoPref>0?Form("_%s",sOptPref.Data()):""), sOptPt.Data(), effi_file.Data(), eff_gen.Data(), effi_rec.Data());
  //  cout << " effi_rec     =   " << effi_rec.Data() << endl;
  //  cout << " effi_file    =   " << effi_file.Data() << endl << endl;
  // The numbers in name[] are hardcoded to read AOD 4D, don't change it.
  LmManager* mgr_low = new LmManager(Form("Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV:%s:%s", name[8+4+kDoSemi*2+kLow].Data(), sConf_part2.Data()));
  mgr_low->SetInputhistAndDim("M_Pt_PhivPair_OpeningAngle", 4);
  LmSignal* sig16_4D_low = ProcessOneInput(mgr_low);
  LmManager* mgr_hig = new LmManager(Form("Pb#minusPb, #sqrt{#it{s}_{NN}} = 2.76 TeV:%s:%s", name[8+4+kDoSemi*2+kHig].Data(), sConf_part2.Data()));
  mgr_hig->SetInputhistAndDim("M_Pt_PhivPair_OpeningAngle", 4);
  LmSignal* sig16_4D_hig = ProcessOneInput(mgr_hig);
  
  han16_4D->AttachSignal( *sig16_4D_low );
  han16_4D->AttachSignal( *sig16_4D_hig );
  han16_4D->Process(LmHandler::kCombine);
  
  if (kDoSystematics==0 && kDoCocktail==0 && kWideMeeBins==0 && kDoPref<3) doPlots=kTRUE;
  if (doPlots) {
    TString fieldName[3] = {"#minus#minus", "#plus#plus", "magnetic field polarities"}; // run numbers: low=--, hig=++
    for (int isig=0; isig<han16_4D->GetNSignals(); ++isig) {
      han16_4D->SetLmSignalName(isig, fieldName[isig].Data());
    }
    // Set custom legend and labels
    han16_4D->SetLegend(GetLegendTemplate(kRfactor, -1, fieldName[2]));
    han16_4D->SetLabels(GetLabelsTemplate(kRfactor));

    han16_4D->Process(LmHandler::kCompare); // for plots comparing B-fields, e.g. Rfactor
    if (ReqRfac()) gSystem->Exec(Form("mkdir -p %s/_plots-fields/", gEnv->GetValue("Canvas.PrintDirectory",".")));
    for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
      //han16_4D->PrintCompareSoverB_Mee( i, kTRUE, Form("+%s",GetAllOptions().Data()));
      //han16_4D->PrintCompareSignif_Mee( i, kTRUE, Form("+%s",GetAllOptions().Data()));
      //han16_4D->PrintCompareSigBkg_Mee( i, kTRUE, Form("+%s",GetAllOptions().Data()));
      if (ReqRfac()) han16_4D->PrintCompareRfactor_Mee(i, kTRUE, Form("+%s",GetAllOptions().Data()), 0.9, 1.1); // .pdf into current dir...
      if (ReqRfac()) han16_4D->PrintCompareRfactor_Mee(i, kTRUE, Form("%s/_plots-fields/cRfactor_cut%02d_Mee_bin%d.C"  , gEnv->GetValue("Canvas.PrintDirectory","."), 16, i), 0.9, 1.1);
    }
    
    // reset handler type
    han16_4D->SetType(LmHandler::kCombine);
  } // doPlots
  
}

//_______________________________________________________________________________________________
LmSignal* ProcessOneInput(LmManager* mgr)
{
  Printf("______ process one input ______");
  //TFile *_fTempl4 = 0x0;
  TFile *_fTempl5 = 0x0, *_fTempl5_noPref = 0x0;
  TH3D *hSigNoPF=0x0, *hSig=0x0, *hCon=0x0, *hULS=0x0, *hLS=0x0, *hDiffGa=0x0, *hDiffGa_LS=0x0, *hNorm=0x0;
  if (kDoPhiV>=LmManager::kTemplUnsub) { // if templates are needed
    //_fTempl4 = LmHelper::SafelyOpenRootfile(Form("./input/PbPb/templates/spectra3D-4-%s-%s-noPC-MCall+prompt+conv+diffGamma.root",sOptCent.Data(),sOptPt.Data()));
    //hSig = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl4, 1, "hUnlike");  hSig->SetName("hSig");  // file 4 prompt
    //hCon = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl4, 2, "hUnlike");  hCon->SetName("hCon");  // file 4 conversions
    //hDiffGa    = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl4, 3, "hUnlike");  hDiffGa->SetName("hDiffGamma");       // file 4 diff gamma ULS
    //hDiffGa_LS = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl4, 3, "hBkg");     hDiffGa_LS->SetName("hDiffGamma_LS"); // file 4 diff gamma LS
    //hDiffGa->Add(hDiffGa_LS, -1); // diff gamma subtracted
    _fTempl5_noPref = LmHelper::SafelyOpenRootfile(Form("./input/PbPb/templates/spectra3D-5-%s-%s-NoPref-MCall+prompt+conv+oneGa+diffGa+hadrCont.root",sOptCent.Data(),sOptPt.Data()));
    hSigNoPF = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5_noPref, 1, "hUnlike");  hSigNoPF->SetName("hSigNoPF");  // file 5 prompt, no prefilter
    _fTempl5 = LmHelper::SafelyOpenRootfile(Form("./input/PbPb/templates/spectra3D-5-%s-%s-%s-MCall+prompt+conv+oneGa+diffGa+hadrCont.root",sOptCent.Data(),sOptPt.Data(),sOptPref.Data()));
    hSig       = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5, 1, "hUnlike");  hSig->SetName((kDoPref>0?"hSigPF":"hSig"));  // file 5 prompt
    hCon       = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5, 2, "hUnlike");  hCon->SetName("hCon");                // file 5 conversions
    hDiffGa    = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5, 4, "hUnlike");  hDiffGa->SetName("hDiffGamma");       // file 5 diff gamma ULS
    hDiffGa_LS = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl5, 4, "hBkg");     hDiffGa_LS->SetName("hDiffGamma_LS"); // file 5 diff gamma LS
    hDiffGa->Add(hDiffGa_LS, -1); // diff gamma subtracted
    hNorm = (TH3D*) hSig->Clone("hNorm");
    hNorm->Add(hDiffGa);
    hNorm->Add(hCon);
  }
  
  if (kDoOpAngle && mgr->GetNdimInput()>=4) {
    mgr->SetProjRange(thetaEEmin, TMath::Pi(), 3); // axis 3 = dimension 4 = opening angle.
    mgr->SetThetaEEmin(thetaEEmin);
  }
  mgr->SetProjOption(projoption);
  mgr->SetEnableEffiCorr(kDoEffiCorr);
  mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
  mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
  mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
  mgr->SetTemplateNormRegionMin(n_cutPhiVbelow, cutPhiVbelow); // only needed for some template types.
  mgr->SetTemplateNormRegionMax(n_cutPhiVabove, cutPhiVabove); // only needed for some template types.
  if (kDoPhiV==LmManager::kTemplSub)   mgr->SetExclusionZTemplates(hSigNoPF, 0x0, LmManager::kTemplSub  , hSig, hNorm);
  if (kDoPhiV==LmManager::kTemplConv)  mgr->SetExclusionZTemplates(hCon    , 0x0, LmManager::kTemplConv , hSig, hNorm);
  if (kDoPhiV==LmManager::kTemplUnsub) mgr->SetExclusionZTemplates(hULS    , hLS, LmManager::kTemplUnsub, hSig, hNorm);
  mgr->SetEnableExclusionCutZ(kDoPhiV); // to be able to change or deactivate the cut without changing the code above.
  if (kWideMeeBins==0) mgr->SetRebinning2D(n_mee_bin_4D, mee_bin_4D, n_ptee_bin_4D, ptee_bin_4D);
  if (kWideMeeBins==1) mgr->SetRebinning2D(n_mee_bin_systematic, mee_bin_systematic, n_ptee_bin_4D, ptee_bin_4D); // do not use integrated ptee bin!
  mgr->Process();
  
  LmBackground* bkg = new LmBackground(*mgr, "bkg");
  bkg->SetRfactorUnityRectangle(1.5, 100.); // set Rfactor to 1 above mee=1.5GeV
  bkg->Process(LmBackground::kHybrid);
  //bkg->PrintRfactor2D(); // only the 2D plot will show the Rfactor with applied unity region.
  
  // Need to give phiV-corrected subtracted raw spectra to the manager before LmSignal::Process() is called.
  // Only then the LmManager::SignalPostCorrection(hSub) modifies the subtracted yield before SoverB and Signif are
  // computed from it. The difficulty is that the phiV template fit happens in 1D (projection binning of handler),
  // while the signal is processed in 2D (2D rebinning in (base)manager). Therefore use same binning (ptee_bin_4D)!
  TFile* _fPhiVcorr[8];
  std::vector<TH1D*> vhPhiVcorr;
  if (kDoPhiV==LmManager::kTemplSub) {
    TString fileDir = Form("./plots/_PhiVstudy/%s-%s/phiVTemplSub-%s",sOptCent.Data(),sOptPt.Data(),sOptPref.Data());
    for (int i=0; i<n_ptee_bin_4D; ++i) {
      _fPhiVcorr[i] = LmHelper::SafelyOpenRootfile(Form("%s/spectra1D-phiVstud-2-%s-%s-%s-data+uncorr+templ+flat+MC-ptee%.0fto%.0f.root",
                                                        fileDir.Data(),sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),ptee_bin_4D[i],ptee_bin_4D[i+1]));
      vhPhiVcorr.push_back( (TH1D*) LmHelper::GetHistFromTemplateFile(_fPhiVcorr[i], 5, "hSubSig-mee0.00to3.14", kFALSE) );
      vhPhiVcorr.at(i)->SetName(Form("hSubSig-ptee%.0fto%.0f",ptee_bin_4D[i],ptee_bin_4D[i+1]));
    }
    TH2D* hSubSig_phiVcorr = LmHelper::MakeHist2Dfrom1D(vhPhiVcorr, "hSubSig_phiVcorr", n_ptee_bin_4D, ptee_bin_4D);
    mgr->AddCorrectedSig(hSubSig_phiVcorr);
    delete hSubSig_phiVcorr;
  }
  
  LmSignal* sig = new LmSignal(*mgr, *bkg); // will take manager name (from caption[]), if no name is given.
  sig->SetDoSignifRaw(kDoSignifRaw);
  sig->SetDoNormBinwidth(kDoNormBinwidth);
  sig->SetDoNormNevents(kDoNormNevents);
  //sig->SetRebinningY(n_ptee_bin_systematic, ptee_bin_systematic); // only for testing
  sig->Process(LmSignal::kStd);
  
  return sig;
}    


//_______________________________________________________________________________________________
void ProcessSystematics(LmHandler* han_systematic, LmHandler* han_analysis)
{
  Printf("______ process systematics ______");
  // A bit of tweaking is needed because systematics are not available for all configurations.
  // - e.g. only with opening angle cut, for which we cannot apply the template phiv-correction.
  // - and not for phiv-prefilter, so in that case we take the regular one.
  //  filename2D_sys = Form("spectra2D_sys%s.root",GetAllOptions().Data());
  //  filename2D_ana = Form("spectra2D_ana%s.root",GetAllOptions().Data());
  filename2D_sys = Form("spectra2D_sys_AOD_%s_%s_opAngle50_phiVoff_%s_%s.root",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data());
  filename2D_ana = Form("spectra2D_ana_AOD_%s_%s_opAngle50_phiVoff_%s_%s.root",sOptCent.Data(),sOptPt.Data(),sOptPref.Data(),sOptEff.Data());
  filename2D_sys.ReplaceAll("_PrefPhiV","_Pref");
  filename2D_ana.ReplaceAll("_PrefPhiV","_Pref");
  extpath_sys    = TString("./input/PbPb/data_2Dsignals/"+filename2D_sys);
  extpath_ana    = TString("./input/PbPb/data_2Dsignals/"+filename2D_ana);
  
  if (!extpath_sys.Contains(sOptPhiV)) LmHelper::Warning(Form("main.h: phiV cut of systematics will be different from '%s'.", sOptPhiV.Data()));
  if (!extpath_sys.Contains(sOptPref)) LmHelper::Warning(Form("main.h: prefilter cut of systematics will be different from '%s'.", sOptPref.Data()));
  if (!kDoOpAngle && extpath_sys.Contains("opAngle")) LmHelper::Warning("main.h: opening angle cut of systematics will be different from 'none'.");
  cout << " systematics path  =  " << extpath_sys.Data() << endl;
  
  // check if pre-processed files exist
  if (   (gSystem->Exec( Form("ls %s > /dev/null",extpath_sys.Data()) )==0) // file is available if Exec()==0
      && (gSystem->Exec( Form("ls %s > /dev/null",extpath_ana.Data()) )==0)
      && kReprocess==kFALSE )
  {
    cout << " * InitFromRootfile()" << endl;
    han_systematic->InitFromRootfile(extpath_sys.Data());
    han_analysis->InitFromRootfile(extpath_ana.Data());
    // InitFromRootfile() assumes some defaults, which we may want to change:
    for (int isig=0; isig<han_analysis->GetNSignals(); ++isig) {
      han_systematic->GetLmSignalI(isig)->SetDoSignifRaw(kDoSignifRaw);
      han_analysis  ->GetLmSignalI(isig)->SetDoSignifRaw(kDoSignifRaw);
      han_systematic->GetLmSignalI(isig)->SetDoNormNevents(kDoNormNevents);
      han_analysis  ->GetLmSignalI(isig)->SetDoNormNevents(kDoNormNevents);
      han_systematic->GetLmSignalI(isig)->SetDoNormBinwidth(kDoNormBinwidth);
      han_analysis  ->GetLmSignalI(isig)->SetDoNormBinwidth(kDoNormBinwidth);
    }
  }
  else { // pre-processed files not available
    cout << " * ProcessInputfiles()" << endl;
    ProcessInputfiles(han_systematic, han_analysis);
  }
  
  cout << " * Postprocess input handlers" << endl;
  // postprocess systematic binning
  han_systematic->Process(LmHandler::kCompare); // make projections of all spectra
  han_systematic->SetSelectedSignal(iSelCutMaxStat); // only needed for Barlow syst
  // postprocess analysis binning
  han_analysis->Process(LmHandler::kCompare); // make projections of all spectra
  
  // plot results of the kCompare processing
  han_systematic->SetPlotRangeRatio(0.01, 2.99);
  han_systematic->SetDoRatio(kDoRatio, ratioPadSize);
  han_analysis->SetPlotRangeRatio(0.01, 2.99);
  han_analysis->SetDoRatio(kDoRatio, ratioPadSize);
  //  han_analysis->SetPlotRangeY(1e-3, 1e5);
  //  for(UInt_t iProj = 0; iProj < binsPtee_forMee.size(); ++iProj){
  ////    han_systematic->PrintCompareSig_Mee(iProj, kDoLegend, Form("+_sys%s",GetAllOptions().Data()));
  //    han_analysis  ->PrintCompareSig_Mee   (iProj, kDoLegend, Form("+_ana%s",GetAllOptions().Data()));
  //    han_analysis  ->PrintCompareSigBkg_Mee(iProj, kDoLegend, Form("+_ana%s",GetAllOptions().Data()));
  //  }
  //  han_analysis->ResetPlotRangeY();
}

//_______________________________________________________________________________________________
void ProcessInputfiles(LmHandler* han_sys, LmHandler* han_ana)
{
  Printf("______ process input files ______");
  TBenchmark* bench = new TBenchmark();
  n_config=0;//=Ncuts*2;
  // Set up the config strings
  for(Int_t iCuts = 0; iCuts < NcutsMAX; ++iCuts) { // Need to use 'NcutsMAX' to loop over all possible cutsets, because the efficiency files contain all of them.
    if (cut_setting[iSet][iCuts].IsNull()) continue; // Skip cutsets which are empty in data.
    if (!kDoPref) { // needed due to different naming schemes.
      if (kDoEffGen) effi_rec = Form("Npair_hEff_%s_NoPref_%s_%s",cut_setting[iSet][iCuts].Data(),sOptPt.Data(),sOptOpAngle.Data());
      else           effi_rec = Form("NRecPairs_hEff_Ele_%s_%s_3500_%s",cut_setting[iSet][iCuts].Data(),sOptPt.Data(),sOptOpAngle.Data());
      effi_rec.Remove(TString::kTrailing, '_');
      cconfig[iCuts*2+0] = coll_system+":"+name[kDoAOD*8+kDo4D*4+kDoSemi*2+0]+":"+tree_name[0]+":"+cut_setting[iSet][iCuts]+"_"+sOptPt+":"+caption[iCuts]+":"+effi_name[kDoEffGen*4+kDoSemi*2+kDoPt400]+":"+effi_gen[kDoEffGen*4+kDoOpAngle*2+kDoPt400]+":"+effi_rec;
      cconfig[iCuts*2+1] = coll_system+":"+name[kDoAOD*8+kDo4D*4+kDoSemi*2+1]+":"+tree_name[0]+":"+cut_setting[iSet][iCuts]+"_"+sOptPt+":"+caption[iCuts]+":"+effi_name[kDoEffGen*4+kDoSemi*2+kDoPt400]+":"+effi_gen[kDoEffGen*4+kDoOpAngle*2+kDoPt400]+":"+effi_rec;
    }
    else if (kDoPref) {
      if (kDoEffGen) effi_rec = Form("Npair_hEff_%s_Pref_%s_%s",cut_setting[iSet][iCuts].Data(),sOptPt.Data(),sOptOpAngle.Data());
      else           effi_rec = Form("NRecPairsCombined_hEff_Ele_%s_%s_3500_%s",cut_setting[iSet][iCuts].Data(),sOptPt.Data(),sOptOpAngle.Data());
      effi_rec.Remove(TString::kTrailing, '_');
      cconfig[iCuts*2+0] = coll_system+":"+name[kDoAOD*8+kDo4D*4+kDoSemi*2+0]+":"+tree_name[0]+":"+cut_setting[iSet][iCuts]+"_Pref_"+sOptPt+":"+caption[iCuts]+":"+effi_name[kDoEffGen*4+kDoSemi*2+kDoPt400]+":"+effi_gen[kDoEffGen*4+kDoOpAngle*2+kDoPt400]+":"+effi_rec;
      cconfig[iCuts*2+1] = coll_system+":"+name[kDoAOD*8+kDo4D*4+kDoSemi*2+1]+":"+tree_name[0]+":"+cut_setting[iSet][iCuts]+"_Pref_"+sOptPt+":"+caption[iCuts]+":"+effi_name[kDoEffGen*4+kDoSemi*2+kDoPt400]+":"+effi_gen[kDoEffGen*4+kDoOpAngle*2+kDoPt400]+":"+effi_rec;
    }
    n_config+=2; //low+hig
  }
  
  // Add all configs to LmFileManager for efficient file handling
  for (int ic=0; ic<n_config; ic++) {
    LmFileManager::Instance()->AddConfig( cconfig[ic] ); // regular
    LmFileManager::Instance()->AddConfig( cconfig[ic] ); // systematics
  }
  
  /// Functionality quasi identical to Theos, so it is quite portable.
  /// But I need to fill temporary vectors '..._fields' for the 2 fields and combine them before attaching to the final handlers.
  std::vector<LmManager*>    mgrVec, mgrVec_systematic;
  std::vector<LmBackground*> bkgVec, bkgVec_systematic;
  std::vector<LmSignal*>     sigVec, sigVec_systematic;
  std::vector<LmSignal*>     sigVec_fields, sigVec_fields_systematic;
  std::vector<LmHandler*>    hanVec, hanVec_systematic;
  
  bench->Start("input_processing");
  ProcessSingleInputs(cconfig, "",
                      mgrVec,           bkgVec,           sigVec_fields,
                      mgrVec_systematic,bkgVec_systematic,sigVec_fields_systematic);
  Printf("______ DONE WITH SINGLE INPUT PROCESSING ______");
  bench->Show("input_processing");
  
  // combine -- and ++ field
  bench->Start("handler_processing");
  ProcessCombineHandlers(sigVec_fields, hanVec, plotCombineH,
                         binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
  ProcessCombineHandlers(sigVec_fields_systematic, hanVec_systematic, kFALSE,
                         binsPtee_forMee_sys,binsMee_forPtee_sys,plotMeeMin,plotMeeMax_sys,plotPteeMin,plotPteeMax_sys);
  Printf("______ DONE WITH COMBINE HANDLER PROCESSING ______");
  bench->Show("handler_processing");
  
  // Fill the signal vectors with combined signals. After this, the code is identical to Theos again.
  for(Int_t iCuts = 0; iCuts < Ncuts; ++iCuts) {
    sigVec           .push_back( hanVec           .at(iCuts)->GetLmSigCombined() );
    sigVec_systematic.push_back( hanVec_systematic.at(iCuts)->GetLmSigCombined() );
  }
  
  // Attach signals to the handlers which will be used in main function.
  for(Int_t iCuts = 0; iCuts < Ncuts; ++iCuts) {
    han_ana->AttachSignal(*sigVec.at(iCuts));
    han_sys->AttachSignal(*sigVec_systematic.at(iCuts));
  }
  
  // Write 2D histograms to rootfiles for quick future access.
  // First create the output directory:
  TString outdir = extpath_ana(0,extpath_ana.Last('/'));
  gSystem->Exec( Form("mkdir -p %s", outdir.Data()) );
  outdir = extpath_sys(0,extpath_sys.Last('/'));
  gSystem->Exec( Form("mkdir -p %s", outdir.Data()) );
  // add bits of histograms you want to save: LmSignal::kSubSig+LmSignal::kSoverB+LmSignal::kSignif (to save all, use LmSignal::kMAXhist-1)
  TFile* _fileOut2D_ana = new TFile(extpath_ana.Data(), "RECREATE");
  han_ana->Write2DHist(LmSignal::kMAXhist-1, kFALSE, kTRUE);
  _fileOut2D_ana->Close();
  TFile* _fileOut2D_sys = new TFile(extpath_sys.Data(), "RECREATE");
  han_sys->Write2DHist(LmSignal::kMAXhist-1, kFALSE, kTRUE);
  _fileOut2D_sys->Close();
  
  LmFileManager::Instance()->Clear();
}

//_______________________________________________________________________________________________
void ProcessSingleInputs(TString config[], TString effiName, 
                         std::vector<LmManager*> &mgrVec,     std::vector<LmBackground*> &bkgVec,     std::vector<LmSignal*> &sigVec,
                         std::vector<LmManager*> &mgrVec_sys, std::vector<LmBackground*> &bkgVec_sys, std::vector<LmSignal*> &sigVec_sys)
{
  Printf("______ process single inputs ______");
  if (effiName.IsNull()) {} // to avoid compiler warning
  
  TFile* _fTempl3 = 0x0;
  TH3D *hSig3=0x0, *hCon3=0x0, *hULS3=0x0, *hLS3=0x0;
  if (kDoPhiV>=LmManager::kTemplUnsub) { // if templates are needed
    _fTempl3 = LmHelper::SafelyOpenRootfile(Form("./input/PbPb/templates/spectra3D-3-%s-%s-MCall+prompt+conv+noConv.root",sOptCent.Data(),sOptPt.Data()));
    hSig3 = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl3, 1, "hUnlike");  hSig3->SetName("hSig"); // file 3 prompt
    hCon3 = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl3, 2, "hUnlike");  hCon3->SetName("hCon"); // file 3 conversions
    hULS3 = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl3, 3, "hUnlike");  hULS3->SetName("hULS"); // file 3 ULS+LS (key 0=all, 3=noConv) w/ paircuts
    hLS3  = (TH3D*) LmHelper::GetHistFromTemplateFile(_fTempl3, 3, "hBkg");     hLS3->SetName("hLS");   // file 3 ULS+LS (key 0=all, 3=noConv) w/ paircuts
  }
  
  for (int ic=0; ic<n_config; ic++) {
    Printf("config # %d:  %s", ic, config[ic].Data());
    
    LmManager* mgr = new LmManager(const_cast<char*>(config[ic].Data()));
    mgr->SetInputhistAndDim(const_cast<char*>(inputhist.Data()), inputdim);
    mgr->SetProjOption(projoption);
    mgr->SetEnableEffiCorr(kDoEffiCorr);
    mgr->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
    mgr->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
    mgr->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
    mgr->SetTemplateNormRegionMin(n_cutPhiVbelow, cutPhiVbelow); // only needed for some template types.
    mgr->SetTemplateNormRegionMax(n_cutPhiVabove, cutPhiVabove); // only needed for some template types.
    if (kDoPhiV==LmManager::kTemplSub)   mgr->SetExclusionZTemplates(hSig3,  0x0, LmManager::kTemplSub);
    if (kDoPhiV==LmManager::kTemplConv)  mgr->SetExclusionZTemplates(hCon3,  0x0, LmManager::kTemplConv);
    if (kDoPhiV==LmManager::kTemplUnsub) mgr->SetExclusionZTemplates(hULS3, hLS3, LmManager::kTemplUnsub);
    mgr->SetEnableExclusionCutZ(kDoPhiV); // to be able to change or deactivate the cut without changing the code above.
    if (kWideMeeBins==0) mgr->SetRebinning2D(n_mee_bin, mee_bin, n_ptee_bin, ptee_bin);
    if (kWideMeeBins==1) mgr->SetRebinning2D(n_mee_bin_systematic, mee_bin_systematic, n_ptee_bin, ptee_bin); // do not use integrated ptee bin!
    mgr->Process();
    mgrVec.push_back(mgr);
    
    LmBackground* bkg = new LmBackground(*(mgrVec.at(ic)),Form("bg_cut_%02d",ic+1));
    bkg->SetRfactorUnityRectangle(1.5, 100.); // set Rfactor to 1 above mee=1.5GeV (next time this runs)
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
    mgr_sys->SetEnableEffiCorr(kDoEffiCorr);
    mgr_sys->Set3DExclusionZbelow(n_cutPhiVbelow, cutPhiVbelow);
    mgr_sys->Set3DExclusionZabove(n_cutPhiVabove, cutPhiVabove);
    mgr_sys->Set3DExclusionEdgesX(n_cutEdgesMee, cutEdgesMee);
    mgr_sys->SetTemplateNormRegionMin(n_cutPhiVbelow, cutPhiVbelow); // only needed for some template types.
    mgr_sys->SetTemplateNormRegionMax(n_cutPhiVabove, cutPhiVabove); // only needed for some template types.
    if (kDoPhiV==LmManager::kTemplSub)   mgr_sys->SetExclusionZTemplates(hSig3,  0x0, LmManager::kTemplSub);
    if (kDoPhiV==LmManager::kTemplConv)  mgr_sys->SetExclusionZTemplates(hCon3,  0x0, LmManager::kTemplConv);
    if (kDoPhiV==LmManager::kTemplUnsub) mgr_sys->SetExclusionZTemplates(hULS3, hLS3, LmManager::kTemplUnsub);
    mgr_sys->SetEnableExclusionCutZ(kDoPhiV); // to be able to change or deactivate the cut without changing the code above.
    mgr_sys->SetRebinning2D(n_mee_bin_systematic, mee_bin_systematic, n_ptee_bin_4D, ptee_bin_4D); // two-step rebinning to apply effi before integrating over ptee.
    mgr_sys->Process();
    mgrVec_sys.push_back(mgr_sys);
    
    LmBackground* bkg_sys = new LmBackground(*(mgrVec_sys.at(ic)),Form("bg_sys_cut_%02d",ic+1));
    bkg->SetRfactorUnityRectangle(1.5, 100.); // set Rfactor to 1 above mee=1.5GeV (next time this runs)
    bkg_sys->Process(LmBackground::kHybrid);
    bkgVec_sys.push_back(bkg_sys);
    
    LmSignal* sig_sys = new LmSignal(*(mgrVec_sys.at(ic)), *(bkgVec_sys.at(ic)), Form("sig_sys_cut_%02d",ic+1));
    sig_sys->SetDoSignifRaw(kDoSignifRaw);
    sig_sys->SetDoNormBinwidth(kDoNormBinwidth);
    sig_sys->SetDoNormNevents(kDoNormNevents);
    sig_sys->SetRebinningY(n_ptee_bin_systematic, ptee_bin_systematic); // will integrate over ptee after effi correction.
    sig_sys->Process(LmSignal::kStd);
    sigVec_sys.push_back(sig_sys);
  }
}

//_______________________________________________________________________________________________
void ProcessCombineHandlers(std::vector<LmSignal*> &sigVec, std::vector<LmHandler*> &hanVec, Bool_t doPlots,
                            std::vector<Double_t> binsPtee_forMee, std::vector<Double_t> binsMee_forPtee,
                            Double_t plotMeeMin, Double_t plotMeeMax, Double_t plotPteeMin, Double_t plotPteeMax)
{
  Printf("______ process combine handlers ______");
  TString fieldName[3] = {"#minus#minus", "#plus#plus", "magnetic field polarities"}; // run numbers: low=--, hig=++
  for (unsigned int ihan=0; ihan<sigVec.size()/2; ihan++) 
  {
    cout << " " << ihan << flush;
    LmHandler* hanComb = new LmHandler(binsPtee_forMee,binsMee_forPtee,plotMeeMin,plotMeeMax,plotPteeMin,plotPteeMax);
    hanComb->SetName(sigVec[ihan*2]->GetName()); // because I overwrite the signal names with -- and ++
    sigVec[ihan*2  ]->SetName(fieldName[0].Data());
    sigVec[ihan*2+1]->SetName(fieldName[1].Data());
    hanComb->AttachSignal( *(sigVec[ihan*2  ]) );
    hanComb->AttachSignal( *(sigVec[ihan*2+1]) );
    if (doPlots) hanComb->Process(LmHandler::kCompare);
    hanComb->Process(LmHandler::kCombine);
    hanComb->GetLmSigCombined()->SetName(caption[ihan].Data()); //(Form("cut %02d",ihan+1));//sig_combined_%02d
    hanVec.push_back(hanComb);
    
    if (!doPlots) continue;
    // Set custom legend and labels
    hanComb->SetLegend(GetLegendTemplate(kRfactor, -1, fieldName[2]));
    hanComb->SetLabels(GetLabelsTemplate(kRfactor));
    
    if (ReqRfac()) gSystem->Exec(Form("mkdir -p %s/_plots-fields/", gEnv->GetValue("Canvas.PrintDirectory",".")));
    for (unsigned int i = 0; i < binsPtee_forMee.size(); ++i){
      //hanComb->PrintCompareSoverB_Mee( i, kTRUE, Form("%s/_plots-fields/cSoverB_cut%02d_Mee_bin%d.pdf",  gEnv->GetValue("Canvas.PrintDirectory","."), ihan+1, i));
      //hanComb->PrintCompareSignif_Mee( i, kTRUE, Form("%s/_plots-fields/cSignif_cut%02d_Mee_bin%d.pdf",  gEnv->GetValue("Canvas.PrintDirectory","."), ihan+1, i));
      //hanComb->PrintCompareSigBkg_Mee( i, kTRUE, Form("%s/_plots-fields/cSigBkg_cut%02d_Mee_bin%d.pdf",  gEnv->GetValue("Canvas.PrintDirectory","."), ihan+1, i));
      if (ReqRfac()) hanComb->PrintCompareRfactor_Mee(i, kTRUE, Form("%s/_plots-fields/cRfactor_cut%02d_Mee_bin%d.pdf", gEnv->GetValue("Canvas.PrintDirectory","."), ihan+1, i), 0.9, 1.1);
      if (ReqRfac()) hanComb->PrintCompareRfactor_Mee(i, kTRUE, Form("%s/_plots-fields/cRfactor_cut%02d_Mee_bin%d.C"  , gEnv->GetValue("Canvas.PrintDirectory","."), ihan+1, i), 0.9, 1.1);
    }
  }
  printf("\n");
}

