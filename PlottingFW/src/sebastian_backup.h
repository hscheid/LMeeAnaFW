// c++ includes
// ROOT includes
#include "TString.h"
#include "TMath.h"
// project includes

// Global variable
Int_t debug = 3;
Bool_t  kDoSignifRaw      = kTRUE;
Bool_t  kDoEffiCorrection = kFALSE;
Bool_t  kDoNormBinwidth   = kTRUE;
Bool_t  kDoNormNentries   = kTRUE;
Bool_t  kDoNormNevents    = kFALSE;
Bool_t  kDoConfLevel      = kFALSE;
Double_t   confLevel      = 0.95;
// ____________________________________________________________________________________________
// Carstens Input
TString name[] = {
   "./input/merged_02_07_2015.root"};     // pp 2010 data
//   "./input/merged_pPb_13_07_15.root"}; // pPb data not full statistic
TString tree_name[] = { "sscheid_Histos_diel_lowmass" };
//TString cut_setting[] = { "cut1", "cut2", "cut3", "cut4" };
TString cut_setting[] = { "cut1"};
TString coll_system = "pp, #sqrt{#it{s}} = 7 TeV";
//TString coll_system = "pPb, #sqrt{#it{s}} = 5.02 TeV";
TString inputhist("pInvMass_DCAsigma_pPt");
//TString inputhist("pInvMass_DCAabs_pPt");
Int_t   inputdim = 3;

//______________________________________________________________________________________________________________________________________________________________________

 // corresponding input efficiency files
 TString effi_name[] = {
 "./input/pairEff_raw-17h-std_QM2014_400MeV.root"};
  // name of 2D generated and reconstructed histogram
 TString effi_gen[] = {"hNGenPairs_pt400"};
 TString effi_rec[] = {"Npair_hEff_Nreco_Ele_ITSTPCTOFif_trkSPDfirst_1_pt400"};

//______________________________________________________________________________________________________________________________________________________________________

 //
 // further details of input data
 // config string for manager
 TString cconfig[] = { // this determines which settings will really be analysed!
  //  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[0] + ":" + "dca , pT > 200 MeV") // "./input/LMEEoutput-440-1full.root",  // QM 2014 setting, 200 MeV single leg pt cut
  // ,(coll_system + ":" + name[2] + ":" + tree_name[0] + ":" + cut_setting[1] + ":" + "QM 2014, pT > 300 MeV") // "./input/LMEEoutput-481-1full.root"   // QM 2014 setting, 300 MeV single leg pt cut
  (coll_system+":"+name[0]+":"+tree_name[0]+":"+cut_setting[0]+":"+"DCA sigma 1, pT > 400 MeV"+":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[0] ) // "./input/LMEEoutput-347-1full.root",  // QM 2014 setting, 400 MeV single leg pt cut
  // ,(coll_system + ":" + name[2] + ":" + tree_name[0] + ":" + cut_setting[2] + ":" + "QM 2014, pT > 500 MeV") // "./input/LMEEoutput-481-1full.root"   // QM 2014 setting, 500 MeV single leg pt cut
 };
 Int_t n_config = sizeof(cconfig)/sizeof(*cconfig);


//______________________________________________________________________________________________________________________________________________________________________

// desired binning for output. will also be used for efficiency correction.
// binning has to be compatible with input. [PR/CK: see function GetVector() of Config_user_LMEEPbPb.C]

//Double_t mee_bin[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, // for QM14 I think
//  0.14, 0.18, 0.22, 0.26, 0.30, 0.34,
//  0.42, 0.50, 0.58, 0.66, 0.82, 0.98,
//  1.50, 2.10, 2.70, 3.30, 4.00, 5.00 };
//Double_t mee_bin[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10,
//  0.14, 0.18,   0.26, 0.34,   0.50,   0.70,   1.10, 1.50,
//  2.10, 2.70, 3.30, 4.00, 5.00 }; 
//  Double_t mee_bin[] {0.0, 0.4,0.8,1.2,1.6,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.,16.,17.,18.,19.,20.}; //actually dca binning
  Double_t mee_bin[] =  {0.05,0.15,1.2,2.8,3.2};
  Double_t dca_bin[] =  {0.0, 0.4,0.8,1.2,1.6,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.,16.,17.,18.,19.,20.};
  Double_t ptee_bin[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 
  2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0 };
// Double_t ptee_bin[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.4, 2.0, 3.0, 4.0, 5.0 };


//______________________________________________________________________________________________________________________________________________________________________

// desired binning for cocktail.
// may be much finer than for data, but the bin edges should overlap to avoid inconsistencies when doing projections!
Double_t mee_bin_cocktail[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38, 0.40, 0.42, 0.44, 0.46, 0.48, 
  0.50, 0.52, 0.54, 0.56, 0.58, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.72, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98, 
  1.00, 1.02, 1.04, 1.06, 1.08, 1.10, 1.12, 1.14, 1.16, 1.18, 1.20, 
  1.30, 1.40, 1.50, 1.60, 1.70, 1.80, 1.90, 2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 3.00, 3.10, 3.20, 3.30, 3.40, 3.50, 3.60, 3.70, 3.80, 3.90, 
  4.00, 4.10, 4.20, 4.30, 4.40, 4.50, 4.60, 4.70, 4.80, 4.90, 5.00 };
Double_t ptee_bin_cocktail[] = { 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 
  2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0 };
Int_t n_mee_bin_cocktail = sizeof(mee_bin_cocktail)/sizeof(*mee_bin_cocktail) -1;
Int_t n_ptee_bin_cocktail = sizeof(ptee_bin_cocktail)/sizeof(*ptee_bin_cocktail) -1;
//



//______________________________________________________________________________________________________________________________________________________________________

// cocktail files
TString cocktail_files[] = {
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
Int_t   which_heavyfl_files = 0;
Int_t   which_heavyfl_hists = 0;

Int_t   which_cockt_files = 1;
Int_t   which_cockt_hists = 0;

 

//______________________________________________________________________________________________________________________________________________________________________
 //
 Int_t n_dca_bin = sizeof(dca_bin)/sizeof(*dca_bin) -1;
 Int_t n_mee_bin = sizeof(mee_bin)/sizeof(*mee_bin) -1;
 Int_t n_ptee_bin = sizeof(ptee_bin)/sizeof(*ptee_bin) -1;
 //

//______________________________________________________________________________________________________________________________________________________________________
 // PhiV-cut that shall be applied
 // to disable, set phiv=pi or mee=0 or call mgr.SetEnablePhiVCut(kFALSE);
 Double_t cutValPhiV = 3./4.*TMath::Pi();
 Double_t cutValMee = 0.10;
