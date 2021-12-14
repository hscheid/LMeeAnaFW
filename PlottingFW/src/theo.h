#include "TH3.h"
// ____________________________________________________________________________________________
// Theos Input

// TString tree_name = "Histos_diel_lowmass";
 TString tree_name = "NoList";

 TString inputhist = "InvMass_PairPt_PhivPair";

 Int_t   inputdim = 3;
  // desired binning for output. will also be used for efficiency correction.
  // binning has to be compatible with input. [PR/CK: see function GetVector() of Config_user_LMEEPbPb.C]

  Double_t mee_bin[]  = { 
  0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
  0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,
  0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,
  0.30,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,
  0.40,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,
  0.50,0.51,0.52,0.53,0.54,0.55,0.56,0.57,0.58,0.59,
  0.60,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,
  0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,
  0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,
  0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99,
  1.00,1.01,1.02,1.03,1.04,1.05,1.06,1.07,1.08,1.09,
  1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,
  2.20,2.40,2.60,2.80,3.00,3.01,3.02,3.03,3.04,3.05,
  3.06,3.07,3.08,3.09,3.10,3.30,3.50,4.00, };
                          
  Double_t ptee_bin[] = { 
  0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
  0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,
  0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,
  0.30,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,
  0.40,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,
  0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,
  1.00,1.05,1.10,1.15,1.20,1.25,1.30,1.35,1.40,1.45,
  1.50,1.55,1.60,1.65,1.70,1.75,1.80,1.85,1.90,1.95,
  2.00,2.05,2.10,2.15,2.20,2.25,2.30,2.35,2.40,2.45,
  2.50,2.60,2.70,2.80,2.90,3.00,3.10,3.20,3.30,3.40,
  3.50,3.60,3.70,3.80,3.90,4.00,4.10,4.20,4.30,4.40,
  4.50,5.00,6.00 };

  Double_t mee_bin_systematic[]  = { 0.00,0.14,0.75,1.10,3.00,3.10,4.00 };
  Double_t ptee_bin_systematic[] = { 0.0,1.0,2.0,3.0,6.0 };

// for basti
//  Double_t mee_bin[]  = {  0.00,0.02,0.05,0.08,0.14,0.16,0.20,0.30,0.40,0.50,0.60,0.70,0.75,
//                           0.80,0.95,1.00,1.05,1.10,1.40,1.70,2.00,2.30,
//                           2.60,2.70,2.80,3.00,3.05,3.10,3.20,3.50,4.00 };
//  Double_t ptee_bin[] = {
//  0.00,0.25,0.50,0.75,1.00,1.25,1.50,1.75,2.00,2.25,2.50,3.00,3.50,4.00,4.50,5.00,6.00
//  };
  // systematic
//  Double_t mee_bin_systematic[]  = { 0.00,0.08,0.14,0.16,1.10,2.70,2.80,3.20 };
//  Double_t ptee_bin_systematic[] = { 0.0,6.0 };

  
  Int_t n_mee_bin = sizeof(mee_bin)/sizeof(*mee_bin) -1;
  Int_t n_ptee_bin = sizeof(ptee_bin)/sizeof(*ptee_bin) -1;
  // systematic
  Int_t n_mee_bin_systematic = sizeof(mee_bin_systematic)/sizeof(*mee_bin_systematic) -1;
  Int_t n_ptee_bin_systematic = sizeof(ptee_bin_systematic)/sizeof(*ptee_bin_systematic) -1;

  Double_t mee_bin_c[]  = { 
  0.00,0.02,0.05,0.09,0.14,0.20,0.25,0.30,0.35,0.40,0.45,
  0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.90,0.95,1.00,1.05,1.10,
  1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,
  2.20,2.30,2.40,2.60,2.80,3.00,3.05,3.10,3.30,3.50,4.00 
  };
                            
  Double_t ptee_bin_c[] = {
  0.00,0.25,0.50,0.75,
  1.00,1.25,1.50,1.75,
  2.00,2.25,2.50,2.75,
  3.00,3.25,3.50,3.75,
  4.00,4.25,4.50,4.75,
  5.00,5.25,5.50,5.75,
  6.00
  };
  Int_t n_mee_bin_c = sizeof(mee_bin_c)/sizeof(*mee_bin_c) -1;
  Int_t n_ptee_bin_c = sizeof(ptee_bin_c)/sizeof(*ptee_bin_c) -1;

// ____________________________________________________________________________________________

  Bool_t kDoNormNevents    = kTRUE;
  Bool_t kDoNormBinwidth   = kTRUE;
  Bool_t kDoEffiCorrection = kTRUE;
 
  Int_t debug = 00;

  //
  // PhiV-cut that shall be applied
  // to disable, set phiv=pi or mee=0 or call mgr.SetEnablePhiVCut(kFALSE);
  //Double_t cutValPhiV = 3./4.*TMath::Pi();
  Bool_t bCutPhiV = kTRUE;
//  Double_t cutValPhiV = 0.5*TMath::Pi();
//  Double_t cutValMee = 0.06;

  Double_t cutPhiVbelow[] = { 0. };
  Double_t cutPhiVabove[] = { 1./2.*TMath::Pi() };
  Double_t cutEdgesMee[]  = { 0.10 };
  Int_t    n_cutPhiVbelow = sizeof(cutPhiVbelow)/sizeof(*cutPhiVbelow);
  Int_t    n_cutPhiVabove = sizeof(cutPhiVabove)/sizeof(*cutPhiVabove);
  Int_t    n_cutEdgesMee  = sizeof(cutEdgesMee)/sizeof(*cutEdgesMee);

  Double_t fTriggerEff = 1.;
