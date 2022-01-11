//
bool kDoRfactor = true;
bool kDoSignifRaw = true;
bool kDoNormBinwidth = true;
bool kDoNormNevents = true;

Double_t kSetMinPtLabel = 0.2;
Double_t kSetMaxPtLabel = -1;

TString coll_system = "p--Pb #sqrt{#it{s}} = 5.02 TeV";
TString projoption = "yx"; // option="ab" means: a vertical, b horizontal (ROOT-convention) or just a vs b



Int_t     debug                  = 1000;

// input files dataset
TString fileName[] = {
  "../input/data/AnalysisResults_c1.root",
  "../input/data/AnalysisResults_c2.root",
};
TString tree_name[] = {"Histos_diel_lowmass"};
TString cut_setting[] = {
  // always adapt to input data files!
  "aodTrackCuts01" // 001
};
TString inputhist = "pInvMass_pPt_DCAsigma";
Int_t inputdim = 3;

const TString configString[] = {
  (coll_system + ":" + fileName[0] + ":" + tree_name[0] + ":" + cut_setting[0] + ":" + "data")};
// (coll_system + ":" + fileName[0] + ":" + tree_name[0] + ":" + cut_setting[0] + ":" + "data" + ":" + effi_name[76] + ":" + effi_gen[3] + ":" + effi_rec[15])};

//Mee bins
std::vector<double> vMeeBinsDef = {0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38, 0.40, 0.42, 0.44, 0.46, 0.48, 0.50, 0.52, 0.54, 0.56, 0.58, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.72, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98, 1.00, 1.02, 1.04, 1.06, 1.08, 1.10, 1.20, 1.30, 1.40, 1.50, 1.60, 1.70, 1.80, 1.90, 2.00, 2.10, 2.20, 2.30, 2.40, 2.50, 2.60, 2.70, 2.80, 2.90, 3.00, 3.02, 3.04, 3.06, 3.08, 3.10, 3.12, 3.30, 3.50, 4.00, 5.00};
//DCAee bins
std::vector<double> vDcaBinsDef = {0.0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8, 3.2, 3.6, 4.0, 4.4, 4.8, 5.2, 5.6, 6.0, 6.4, 6.8, 7.2, 7.6, 8.0, 8.4, 8.8, 9.2, 9.6, 10.0, 10.4, 10.8, 11.2, 11.6, 12.0, 12.4, 12.8, 13.2, 13.6, 14.0, 14.4, 14.8, 15.2, 15.6, 16.0, 16.4, 16.8, 17.2, 17.6, 18.0, 18.4, 18.8, 19.2, 19.6, 20.0};
// ptee bins
std::vector<double> vPteeBinsDef = {0.000, 0.050, 0.100, 0.150, 0.200, 0.250, 0.300, 0.350, 0.400, 0.450, 0.500, 0.550, 0.600, 0.650, 0.700, 0.750, 0.800, 0.850, 0.900, 0.950, 1.000, 1.100, 1.200, 1.300, 1.400, 1.500, 1.600, 1.700, 1.800, 1.900, 2.000, 2.100, 2.200, 2.300, 2.400, 2.500, 2.600, 2.700, 2.800, 2.900, 3.000, 3.100, 3.200, 3.300, 3.400, 3.500, 3.600, 3.700, 3.800, 3.900, 4.000, 4.100, 4.200, 4.300, 4.400, 4.500, 5.000, 5.500, 6.000, 6.500, 7.000, 8.000};
