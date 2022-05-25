#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TMath.h"
#include "TSpline.h"
#include "TString.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TLine.h"
#include "TStyle.h"
#include "TObject.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TIterator.h"
#include "TChain.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"
#include "TSystem.h"
#include "TPaveStats.h"
#include "TArray.h"
#include "TArrayD.h"
#include <vector>
#include <string>
#include <climits>
#include <iostream>
#include "../PlottingFW/src/core/LmRebinner.h"

//string fCocktailFileName = "../input/cocktail/Cocktail_withSys_21_01_2021_finebins_powheg_30_50_Daiki_jpsi_2018.root";
string fCocktailFileName = "../input/cocktail/Cocktail_withSys_21_01_2021_bigbins_powheg_00_10_Daiki_jpsi_2018.root";
//string fCocktailFileName = "../input/cocktail/Cocktail_withSys_27_09_2021_pythia_smallbins_00_10_nophimtscaling.root";

//LmRebinner fRebinner;

//std::vector<double> vec_mass_bins{
//	0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
//        0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,
//        0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,
//        0.30,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,
//        0.40,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,
//        0.50,0.51,0.52,0.53,0.54,0.55,0.56,0.57,0.58,0.59,
//        0.60,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,
//        0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,
//        0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,
//        0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99,
//        1.00,1.01,1.02,1.03,1.04,1.05,1.06,1.07,1.08,1.09,
//        1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,
//        2.20,2.40,2.60,2.80,3.00,3.01,3.02,3.03,3.04,3.05,
//        3.06,3.07,3.08,3.09,3.10,3.30,3.50,4.00
//};

// std::vector<double> vec_mass_bins{
//   0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.08, 0.10,
//   0.12, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50,
//   0.55, 0.60, 0.65, 0.70, 0.75, 0.80, 0.85, 0.90, 0.95,
//   1.00, 1.05, 1.10, 1.20, 1.40, 1.60, 1.80, 2.00, 2.20,
//   2.40, 2.60, 2.80, 3.00, 3.06, 3.10, 3.30, 3.50, 4.00};

// Need to adjust binning to analysis bins
std::vector<double> vec_mass_bins{0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00, 1.10, 1.20, 1.40, 1.60, 1.80, 2.00, 2.20, 2.40, 2.60, 2.80, 3.00, 3.06, 3.10, 3.30, 3.50, 4.00};

//std::vector<double> vec_ptee_bins{
//	 0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
//         0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,
//         0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,
//         0.30,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,
//         0.40,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,
//         0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,
//         1.00,1.05,1.10,1.15,1.20,1.25,1.30,1.35,1.40,1.45,
//         1.50,1.55,1.60,1.65,1.70,1.75,1.80,1.85,1.90,1.95,
//         2.00,2.05,2.10,2.15,2.20,2.25,2.30,2.35,2.40,2.45,
//         2.50,2.60,2.70,2.80,2.90,3.00,3.10,3.20,3.30,3.40,
//         3.50,3.60,3.70,3.80,3.90,4.00,4.10,4.20,4.30,4.40,
//         4.50,5.00,5.50,6.00,6.50,7.00,8.00,10.00
//};

// Need to adjust binning to analysis bins
std::vector<double> vec_ptee_bins{0., 1., 2., 3., 4., 5., 6., 7., 8.};

TH2D fWeightsHF;
TH2D fWeightsCharm;
TH2D fWeightsBeauty;
TH2D fWeightsSum;
TH2D fWeightsReso;

void EfficiencyFillerLvL1(TH2D* h2_eff);
void EfficiencyFillerLvL2(TH2D* h2_eff);
void ReadCocktailFile();
double GetWeight(bool isReso, double mass, double ptee);
double GetWeight(int type, double mass, double ptee);
double GetYield(double mass, double ptee, const TH2D& cocktailPart);
void Rebin2DHistogram(TH2D& hIn, Int_t n_bins_mee, Double_t* bins_mee, Int_t n_bins_ptee, Double_t* bins_ptee);

void AddEfficienciesWeighted()
{

  Bool_t WriteOutput = kTRUE;
  Bool_t DoWeighting = kTRUE;
  Bool_t DoCombineHF = kTRUE;
  Bool_t DoFiller = kFALSE;
  Bool_t DoHF = kFALSE;
  Bool_t DoReso = kFALSE;
  Bool_t DoSmooth = kFALSE;
  Bool_t DoRebinning = kFALSE;
  Bool_t DoRandomRejection = kFALSE;

  //LHC18qr
  //TString filename_in[]    = {"./pair_effv2_LMEE_LEGO1062_LHC20g8a1234_2.root","./pair_effv2_LMEE_LEGO1061_LHC20g8b1234_2_fromD.root","./pair_effv2_LMEE_LEGO1061_LHC20g8b1234_2_fromB.root"};
  //TString filename_out     = "./pair_effv2_CockWeighted_PbPb2018_v7_cut2_200.root";
  TString baseDir = {"./output/pass1/"};
  TString filename_in[] = {"LHC18f3.root", "LHC19h9_charm.root", "LHC19h9_beauty.root"};
  TString filename_out = "./pair_effv2_CockWeighted.root";
  // TString settingname = "aodTrackCuts01";
  std::vector<TString> settingname;
  for (int i = 1; i <= 10; ++i) {
    settingname.push_back(Form("aodTrackCuts%02d", i));
  }

  TString gens[] = {"Ngen", "Ngen_ULS", "Ngen_ULS"};
  TString recs[] = {"Nrec", "Nrec_ULS", "Nrec_ULS"};
  TString typnames[] = {"sameMother", "eleFinalStateFromD", "eleFinalStateFromB"};

  Int_t components = 3;
  cout << "Number of components: " << components << endl;
  TH2D* h2_PairEffs[3];
  TH2D* h2_gen[3];
  TH2D* h2_reco[3];

  ReadCocktailFile();

  TFile* file = 0x0;

  TFile* file_out = TFile::Open(filename_out, "RECREATE");
  if (file_out->IsOpen()) cout << "File opened successfully" << endl;
  TDirectoryFile* fDir = nullptr;
  TString str1, str2;

  for (auto it : settingname) {
    for (Int_t i1 = 0; i1 < components; i1++) {
      file = TFile::Open(baseDir + filename_in[i1], "READ");
      if (file->IsOpen()) cout << "File opened successfully" << endl;
      str1 = (gens[i1] + "_" + typnames[i1]).Data();
      str2 = (recs[i1] + "_" + it + "_" + typnames[i1]).Data();
      // str2 = (recs[i1] + "_" + settingname.at(0) + "_" + typnames[i1]).Data();

      h2_gen[i1] = (TH2D*)file->Get(str1);
      h2_reco[i1] = (TH2D*)file->Get(str2);

      cout << "gen histo: " << str1 << endl;
      cout << "rec histo: " << str2 << endl;

      if (DoRebinning) {
        Int_t Nbins_mass = vec_mass_bins.size() - 1;
        Double_t* mass_binning = vec_mass_bins.data();
        Int_t Nbins_ptee = vec_ptee_bins.size() - 1;
        Double_t* ptee_binning = vec_ptee_bins.data();

        Rebin2DHistogram(*h2_gen[i1], Nbins_mass, mass_binning, Nbins_ptee, ptee_binning);
        Rebin2DHistogram(*h2_reco[i1], Nbins_mass, mass_binning, Nbins_ptee, ptee_binning);

        cout << Nbins_mass << "  " << Nbins_ptee << endl;
      }
      cout << h2_gen[i1] << "  " << h2_reco[i1] << endl;
    }

    file_out->cd();
    // TDirectoryFile* fDir = new TDirectoryFile(settingname.at(0), settingname.at(0));
    fDir = new TDirectoryFile(it, it);
    fDir->cd();

    TH2D* clone_LF = (TH2D*)h2_reco[0]->Clone("eff_LF");
    clone_LF->GetZaxis()->SetRangeUser(0, 0.5);
    clone_LF->Divide(h2_gen[0]);
    clone_LF->Write();

    TH2D* clone_HF1 = (TH2D*)h2_reco[1]->Clone("eff_ccbar");
    clone_HF1->GetZaxis()->SetRangeUser(0, 0.5);
    clone_HF1->Divide(h2_gen[1]);
    clone_HF1->Write();

    TH2D* clone_HF2 = (TH2D*)h2_reco[2]->Clone("eff_bbbar");
    clone_HF2->GetZaxis()->SetRangeUser(0, 0.5);
    clone_HF2->Divide(h2_gen[2]);
    clone_HF2->Write();

    TH2D* clone_HF = (TH2D*)h2_reco[1]->Clone("eff_HF");
    clone_HF->Add(h2_reco[2]);
    TH2D* clone_HFgen = (TH2D*)h2_gen[1]->Clone("gen_HF");
    clone_HFgen->Add(h2_gen[2]);

    clone_HF->GetZaxis()->SetRangeUser(0, 0.5);
    clone_HF->Divide(clone_HFgen);
    clone_HF->Write();

    clone_LF->Divide(clone_HF); // Check difference of LF and HF efficiency
    clone_LF->GetZaxis()->SetRangeUser(0.5, 2.0);
    clone_LF->Write("eff_ratio");

    // Add without cocktail weights
    TH2D* clone1 = (TH2D*)h2_reco[0]->Clone("NrecoPairsRecAdded");
    TH2D* clone2 = (TH2D*)h2_gen[0]->Clone("NgenPairsRecAdded");
    for (Int_t i1 = 1; i1 < components; i1++) {
      clone1->Add(h2_reco[i1]);
      clone2->Add(h2_gen[i1]);
    }
    clone1->Write("NrecoPairsRecAdded");
    clone2->Write("NgenPairsRecAdded");
    TH2D* clone3 = (TH2D*)clone1->Clone("eff_PairsAdded");
    clone3->Divide(clone2);
    clone3->Write("eff_PairsAdded");

    cout << "Starting" << endl;

    TH2D* genPairs = 0;
    TH2D* recoPairs = 0;
    if (DoWeighting) {
      cout << "Making HF efficiency, write to array" << endl;
      for (Int_t i1 = 0; i1 < components; i1++) {
        if (DoCombineHF && (i1 == 1)) { // make sure not combined twice (ie when going to beauty) revisit...
          h2_reco[i1]->Add(h2_reco[i1 + 1]);
          h2_gen[i1]->Add(h2_gen[i1 + 1]);
          components--;
        }
        h2_PairEffs[i1] = h2_reco[i1];
        h2_PairEffs[i1]->Divide(h2_gen[i1]);
      }
      if (DoSmooth) {
        h2_PairEffs[0]->Smooth(5, "k3a");
        h2_PairEffs[0]->Write("NrecoPairsRecResonancesSmooth");
      }

      h2_PairEffs[0]->Write("NrecoPairsRecResonances");
      if (DoCombineHF)
        h2_PairEffs[1]->Write("NrecoPairsRecHF");
      else {
        h2_PairEffs[1]->Write("NrecoPairsRecCharm");
        h2_PairEffs[2]->Write("NrecoPairsRecBeauty");
      }

      if (DoFiller) {
        for (int i = 0; i < 100; i++) {

          EfficiencyFillerLvL1(h2_PairEffs[0]);
          EfficiencyFillerLvL1(h2_PairEffs[1]);
          if (i % 10 == 0) {
            h2_PairEffs[0]->Write(Form("ResoFillerLvL1_%d", i));
            h2_PairEffs[1]->Write(Form("CharmFillerLvL1_%d", i));
          }
        }
        for (int i = 0; i < 100; i++) {

          EfficiencyFillerLvL2(h2_PairEffs[0]);
          EfficiencyFillerLvL2(h2_PairEffs[1]);
          if (i % 10 == 0) {
            h2_PairEffs[0]->Write(Form("ResoFillerLvL2_%d", i));
            h2_PairEffs[1]->Write(Form("CharmFillerLvL2_%d", i));
          }
        }

        //h2_PairEffs[0]->Smooth(1, "k3a");
        //h2_PairEffs[1]->Smooth(1, "k3a");

        //h2_PairEffs[0]->Write("ResoSmooth");
        //h2_PairEffs[1]->Write("CharmSmooth");
      }

      if (DoCombineHF) {
        cout << "Combining HF" << endl;
        genPairs = (TH2D*)h2_gen[0]->Clone("NgenPairsRec");
        for (Int_t i1 = 1; i1 < components; i1++) {
          genPairs->Add(h2_gen[i1]);
        }
        recoPairs = (TH2D*)genPairs->Clone("NrecoPairsRec");
        recoPairs->Reset();
        double eff_reso = 0, eff_hf = 0, eff_reso_err = 0, eff_hf_err = 0;

        cout << "  Starting " << genPairs->GetNbinsX() << "  " << genPairs->GetNbinsY() << endl;

        for (int bin_x = 1; bin_x < genPairs->GetNbinsX() + 1; ++bin_x) {
          for (int bin_y = 1; bin_y < genPairs->GetNbinsY() + 1; ++bin_y) {
            cout << "  Checking " << genPairs->GetBinContent(bin_x, bin_y) << endl;

            if (genPairs->GetBinContent(bin_x, bin_y)) {
              genPairs->SetBinContent(bin_x, bin_y, 1.);

              //          cout << "binx: " << genPairs->GetNbinsX() << "  biny: " << genPairs->GetNbinsY() << endl;
              cout << "x: " << genPairs->GetXaxis()->GetBinCenter(bin_x) << "  y: " << genPairs->GetYaxis()->GetBinCenter(bin_y) << endl;

              eff_reso = h2_PairEffs[0]->GetBinContent(bin_x, bin_y);
              eff_reso_err = h2_PairEffs[0]->GetBinError(bin_x, bin_y);
              eff_hf = h2_PairEffs[1]->GetBinContent(bin_x, bin_y);
              eff_hf_err = h2_PairEffs[1]->GetBinError(bin_x, bin_y);
              //eff_charm       = h2_PairEffs[1]->GetBinContent(bin_x,bin_y);
              //eff_charm_err   = h2_PairEffs[1]->GetBinError(bin_x,bin_y);
              //eff_beauty      = h2_PairEffs[1]->GetBinContent(bin_x,bin_y);
              //eff_beauty_err  = h2_PairEffs[1]->GetBinError(bin_x,bin_y);

              double weight_reso = GetWeight(true, genPairs->GetXaxis()->GetBinCenter(bin_x), genPairs->GetYaxis()->GetBinCenter(bin_y));
              double weight_hf = GetWeight(false, genPairs->GetXaxis()->GetBinCenter(bin_x), genPairs->GetYaxis()->GetBinCenter(bin_y));

              // can probably be removed
              if (DoHF) {
                weight_hf = 1;
                weight_reso = 0;
              }
              if (DoReso) {
                weight_hf = 0;
                weight_reso = 1;
              }
              //
              // std::cout << "weight_reso = " << weight_reso << "   weight_charm = " << weight_charm << std::endl;
              if (weight_reso <= 0) {
                weight_hf = 1.;
                weight_reso = 0.;
              } else if (weight_hf <= 0) {
                weight_reso = 1.;
                weight_hf = 0.;
              } else if (std::isnan(weight_reso) || std::isnan(weight_hf)) {
                weight_reso = 0;
                weight_hf = 0;
              }

              if (eff_reso == 0) {
                weight_hf = 1;
                weight_reso = 0.;
              }
              if (eff_hf == 0) {
                weight_reso = 1;
                weight_hf = 0.;
              }
              if (eff_reso == 0 && eff_hf == 0) {
                weight_reso = 0;
                weight_hf = 0;
              }

              if (eff_reso > 0.6) { // if efficiency is larger than 0.6 it is probably a stat fluctuation... this should be checked!
                weight_reso = 0;
                weight_hf = 1;
              }
              //if (genPairs->GetXaxis()->GetBinCenter(bin_x) > 2.){weight_hf = 1; weight_reso = 0.;}

              //if (weight_reso + weight_hf > 1.0001 || weight_reso + weight_hf < 0.9999) {
              //  LmHelper::Error(Form("Weights in m=%f GeV/c2 and pT=%f GeV/c do not add up to 1: weight_reso + weight_charm = %f + %f = %f", bin_x, bin_y, weight_reso, weight_hf, weight_reso + weight_hf));
              //}

              cout << "weight reso: " << weight_reso << "  weight_hf: " << weight_hf << endl;

              double eff_pair = weight_reso * eff_reso + weight_hf * eff_hf;
              double eff_pair_err = TMath::Sqrt(weight_reso * eff_reso_err * weight_reso * eff_reso_err + weight_hf * eff_hf_err * weight_hf * eff_hf_err);

              //if ((eff_pair < eff_reso && eff_pair < eff_hf) || (eff_pair > eff_reso && eff_pair > eff_hf) ) LmHelper::Error(std::string("U Suck"));
              //cout << "reso: " << eff_reso << " charm: " << eff_hf << " combined: "<< eff_pair << "  " << endl;

              if (genPairs->GetXaxis()->GetBinCenter(bin_x) > 2.6) {
                cout << "  weight reso: " << weight_reso << "  weight_hf: " << weight_hf << endl;
                cout << "  reso: " << eff_reso << " hf: " << eff_hf << endl;
              }

              if (weight_reso + weight_hf > 1) {

                cout << "  weight reso: " << weight_reso << "  weight_hf: " << weight_hf << endl;
              }

              recoPairs->SetBinContent(bin_x, bin_y, eff_pair);
              recoPairs->SetBinError(bin_x, bin_y, eff_pair_err);
            }
          }
        }

      } else {

        genPairs = (TH2D*)h2_gen[0]->Clone("NgenPairsRec");
        for (Int_t i1 = 1; i1 < components; i1++)
          genPairs->Add(h2_gen[i1]);

        recoPairs = (TH2D*)genPairs->Clone("NrecoPairsRec");
        recoPairs->Reset();
        double eff_reso = 0, eff_ccbar = 0, eff_bbbar = 0, eff_reso_err = 0, eff_ccbar_err = 0, eff_bbbar_err = 0;

        for (int bin_x = 1; bin_x < genPairs->GetNbinsX() + 1; ++bin_x) {
          for (int bin_y = 1; bin_y < genPairs->GetNbinsY() + 1; ++bin_y) {
            if (genPairs->GetBinContent(bin_x, bin_y)) {
              genPairs->SetBinContent(bin_x, bin_y, 1.);

              //          cout << "binx: " << genPairs->GetNbinsX() << "  biny: " << genPairs->GetNbinsY() << endl;
              cout << "x: " << genPairs->GetXaxis()->GetBinCenter(bin_x) << "  y: " << genPairs->GetYaxis()->GetBinCenter(bin_y) << endl;

              eff_reso = h2_PairEffs[0]->GetBinContent(bin_x, bin_y);
              eff_reso_err = h2_PairEffs[0]->GetBinError(bin_x, bin_y);
              eff_ccbar = h2_PairEffs[1]->GetBinContent(bin_x, bin_y);
              eff_ccbar_err = h2_PairEffs[1]->GetBinError(bin_x, bin_y);
              eff_bbbar = h2_PairEffs[2]->GetBinContent(bin_x, bin_y);
              eff_bbbar_err = h2_PairEffs[2]->GetBinError(bin_x, bin_y);
              double eff_hf = eff_ccbar + eff_bbbar;

              double weight_reso = GetWeight(0, genPairs->GetXaxis()->GetBinCenter(bin_x), genPairs->GetYaxis()->GetBinCenter(bin_y));
              double weight_ccbar = GetWeight(1, genPairs->GetXaxis()->GetBinCenter(bin_x), genPairs->GetYaxis()->GetBinCenter(bin_y));
              double weight_bbbar = GetWeight(2, genPairs->GetXaxis()->GetBinCenter(bin_x), genPairs->GetYaxis()->GetBinCenter(bin_y));
              double weight_hf = weight_ccbar + weight_bbbar;

              //std::cout << "weight_reso = " << weight_reso << "   weight_charm = " << weight_ccbar << "   weight_beauty = " << weight_bbbar << std::endl;
              if (weight_reso <= 0 && weight_hf > 0) {
                weight_ccbar /= weight_hf;
                weight_bbbar /= weight_hf;
                weight_reso = 0.;
              } else if (weight_hf <= 0) {
                weight_reso = 1.;
                weight_ccbar = 0.;
                weight_bbbar = 0.;
              } else if (std::isnan(weight_reso) || std::isnan(weight_hf)) {
                weight_reso = 0;
                weight_ccbar = 0.;
                weight_bbbar = 0.;
              }
              if (eff_reso == 0) {
                if (weight_hf < 0.001) {
                  weight_ccbar = 0.5;
                  weight_bbbar = 0.5;
                  weight_reso = 0;
                } else {
                  weight_ccbar /= weight_hf;
                  weight_bbbar /= weight_hf;
                  weight_reso = 0.;
                }
              }
              if (eff_hf == 0) {
                weight_reso = 1;
                weight_ccbar = 0.;
                weight_bbbar = 0.;
              }
              if (eff_reso == 0 && eff_hf == 0) {
                weight_reso = 0;
                weight_ccbar = 0.;
                weight_bbbar = 0.;
              }

              if (eff_reso > 0.6 && weight_hf > 0.05 && weight_reso < 0.9) {
                weight_reso = 0;
                weight_ccbar /= weight_hf;
                weight_bbbar /= weight_hf;
              } else if (eff_reso > 0.6) {
                weight_reso = 0;
                weight_ccbar = 0;
                weight_bbbar = 0;
              } else if (genPairs->GetXaxis()->GetBinCenter(bin_x) > 2. && weight_hf > 0.05) {
                weight_ccbar /= weight_hf;
                weight_bbbar /= weight_hf;
                weight_reso = 0.;
              }

              //if (weight_reso + weight_hf > 1.0001 || weight_reso + weight_hf < 0.9999) {
              //  LmHelper::Error(Form("Weights in m=%f GeV/c2 and pT=%f GeV/c do not add up to 1: weight_reso + weight_charm = %f + %f = %f", bin_x, bin_y, weight_reso, weight_hf, weight_reso + weight_hf));
              //}

              //            cout << "  weight reso: " << weight_reso << "  weight_charm: " << weight_ccbar << "  weight_beauty: " << weight_bbbar << endl;

              double eff_pair = weight_reso * eff_reso + weight_ccbar * eff_ccbar + weight_bbbar * eff_bbbar;
              double eff_pair_err = TMath::Sqrt(weight_reso * eff_reso_err * weight_reso * eff_reso_err + weight_ccbar * eff_ccbar_err * weight_ccbar * eff_ccbar_err + weight_bbbar * eff_bbbar_err * weight_bbbar * eff_bbbar_err);

              //if ((eff_pair < eff_reso && eff_pair < eff_hf) || (eff_pair > eff_reso && eff_pair > eff_hf) ) LmHelper::Error(std::string("U Suck"));
              if (genPairs->GetXaxis()->GetBinCenter(bin_x) > 2.6) {
                cout << "  weight reso: " << weight_reso << "  weight_charm: " << weight_ccbar << "  weight_beauty: " << weight_bbbar << endl;
                cout << "  reso: " << eff_reso << " charm: " << eff_ccbar << " beauty: " << eff_bbbar << " combined: " << eff_pair << "  " << endl;
              }

              if (weight_reso + weight_ccbar + weight_bbbar > 1) {

                cout << "  weight reso: " << weight_reso << "  weight_charm: " << weight_ccbar << "  weight_beauty: " << weight_bbbar << endl;
              }
              recoPairs->SetBinContent(bin_x, bin_y, eff_pair);
              recoPairs->SetBinError(bin_x, bin_y, eff_pair_err);
            }
          }
        }
      }
      TH2D* eff_weighted = (TH2D*)recoPairs->Clone("eff_weighted");
      eff_weighted->Divide(genPairs);
      eff_weighted->GetZaxis()->SetRangeUser(0, 0.5);
      eff_weighted->Write("eff_weighted");

      if (DoRandomRejection) {
        TString filename = "../input/RandomRejection/LMEE_RandomRejection_PbPb.root";
        TString list1 = "jjung_RandomRejection_out";
        TString list2 = "pT200_PF0wPID0wInvMass40wOp50v4_TrCuts0_PIDCuts136wTOFwITS_SCMAPcut2_noV0";

        TFile* file = TFile::Open(filename, "READ");
        if (file->IsOpen()) cout << "File opened successfully: " << file << endl;
        cout << file->Get(list1) << endl;
        cout << file->Get(list1)->FindObject(list2) << endl;
        cout << file->Get(list1)->FindObject(list2)->FindObject("RandRej_RejPair") << endl;
        cout << file->Get(list1)->FindObject(list2)->FindObject("RandRej_RejPair")->FindObject("InvMass_PairPt") << endl;

        TH2D* rejected = (TH2D*)file->Get(list1)->FindObject(list2)->FindObject("RandRej_RejPair")->FindObject("InvMass_PairPt");
        TH2D* paired = (TH2D*)file->Get(list1)->FindObject(list2)->FindObject("RandRej_Pair")->FindObject("InvMass_PairPt");

        Int_t Nbins_mass = vec_mass_bins.size() - 1;
        Double_t* mass_binning = vec_mass_bins.data();
        Int_t Nbins_ptee = vec_ptee_bins.size() - 1;
        Double_t* ptee_binning = vec_ptee_bins.data();

        Rebin2DHistogram(*rejected, Nbins_mass, mass_binning, Nbins_ptee, ptee_binning);
        Rebin2DHistogram(*paired, Nbins_mass, mass_binning, Nbins_ptee, ptee_binning);

        rejected->Divide(paired);
        TH2F* unity = (TH2F*)paired->Clone("unity");
        for (int binx = 1; binx <= unity->GetNbinsX(); binx++) {
          for (int biny = 1; biny <= unity->GetNbinsY(); biny++) {
            if (unity->GetBinContent(binx, biny) > 0.) {
              unity->SetBinContent(binx, biny, 1. - rejected->GetBinContent(binx, biny));
            }
            if (unity->GetBinContent(binx, biny) > 1.)
              unity->SetBinContent(binx, biny, 1.);
          }
        }

        file_out->cd();
        unity->Write("PF_eff");
        eff_weighted->Multiply(unity);
        eff_weighted->Write("eff_weighted_PF");

        recoPairs->Multiply(unity);
      }
    } else {

      genPairs = (TH2D*)h2_gen[0]->Clone("NgenPairsRec");
      if (!DoReso) genPairs->Reset();
      if (DoHF) genPairs->Add(h2_gen[1]);
      if (DoHF) genPairs->Add(h2_gen[2]);

      recoPairs = (TH2D*)h2_reco[0]->Clone("NrecoPairsRec");
      if (DoReso) recoPairs->Reset();
      if (DoHF) recoPairs->Add(h2_reco[1]);
      if (DoHF) recoPairs->Add(h2_reco[2]);
    }

    genPairs->Write();
    recoPairs->Write();
  }
}
void EfficiencyFillerLvL1(TH2D* h2_eff)
{

  for (int bin_x = 1; bin_x < h2_eff->GetNbinsX() + 1; ++bin_x) {
    for (int bin_y = 1; bin_y < h2_eff->GetNbinsY() + 1; ++bin_y) {
      if (!h2_eff->GetBinContent(bin_x, bin_y)) {
        Int_t counter = 0;
        Double_t bin_content = 0;
        if (h2_eff->GetBinContent(bin_x + 1, bin_y)) ++counter;
        if (h2_eff->GetBinContent(bin_x, bin_y + 1)) ++counter;
        if (h2_eff->GetBinContent(bin_x - 1, bin_y)) ++counter;
        if (h2_eff->GetBinContent(bin_x, bin_y - 1)) ++counter;
        if (counter >= 3) {
          bin_content += h2_eff->GetBinContent(bin_x + 1, bin_y);
          bin_content += h2_eff->GetBinContent(bin_x, bin_y + 1);
          bin_content += h2_eff->GetBinContent(bin_x - 1, bin_y);
          bin_content += h2_eff->GetBinContent(bin_x, bin_y - 1);

          h2_eff->SetBinContent(bin_x, bin_y, bin_content / counter);
        }
      } else
        continue;
    }
  }
}

void EfficiencyFillerLvL2(TH2D* h2_eff)
{

  for (int bin_x = 1; bin_x < h2_eff->GetNbinsX() + 1; ++bin_x) {
    for (int bin_y = 1; bin_y < h2_eff->GetNbinsY() + 1; ++bin_y) {
      if (!h2_eff->GetBinContent(bin_x, bin_y)) {
        Int_t counter = 0;
        Double_t bin_content = 0;
        if (h2_eff->GetBinContent(bin_x - 1, bin_y) && h2_eff->GetBinContent(bin_x + 1, bin_y)) counter = +2;
        if (h2_eff->GetBinContent(bin_x, bin_y - 1) && h2_eff->GetBinContent(bin_x, bin_y + 1)) counter = +2;
        if (counter > 0) {

          counter = 0;
          if (h2_eff->GetBinContent(bin_x + 1, bin_y)) ++counter;
          if (h2_eff->GetBinContent(bin_x, bin_y + 1)) ++counter;
          if (h2_eff->GetBinContent(bin_x - 1, bin_y)) ++counter;
          if (h2_eff->GetBinContent(bin_x, bin_y - 1)) ++counter;
          bin_content += h2_eff->GetBinContent(bin_x + 1, bin_y);
          bin_content += h2_eff->GetBinContent(bin_x, bin_y + 1);
          bin_content += h2_eff->GetBinContent(bin_x - 1, bin_y);
          bin_content += h2_eff->GetBinContent(bin_x, bin_y - 1);

          h2_eff->SetBinContent(bin_x, bin_y, bin_content / counter);
        }
      } else
        continue;
    }
  }
}

void ReadCocktailFile()
{
  TFile* file_in = TFile::Open(fCocktailFileName.c_str(), "READ");

  if (file_in->IsOpen()) cout << "File opened successfully" << endl;

  TH2D* cocktail_sum = (TH2D*)file_in->Get("Cocktail2D");
  TH2D* cocktail_charm = (TH2D*)file_in->Get("ccbar2D");
  TH2D* cocktail_beauty = (TH2D*)file_in->Get("bbbar2D");

  fWeightsCharm = *((TH2D*)cocktail_charm->Clone("weights_charm"));
  fWeightsBeauty = *((TH2D*)cocktail_beauty->Clone("weights_beauty"));
  fWeightsHF = *((TH2D*)cocktail_charm->Clone("weights_hf"));
  fWeightsHF.Add(&fWeightsBeauty);

  TH2D* cocktail_reso = (TH2D*)file_in->Get("pi02D");
  cocktail_reso->Add((TH2D*)file_in->Get("eta2D"));
  cocktail_reso->Add((TH2D*)file_in->Get("etaprim2D"));
  cocktail_reso->Add((TH2D*)file_in->Get("rho2D"));
  cocktail_reso->Add((TH2D*)file_in->Get("omega2D"));
  cocktail_reso->Add((TH2D*)file_in->Get("phi2D"));
  cocktail_reso->Add((TH2D*)file_in->Get("jpsi2D"));
  fWeightsReso = *((TH2D*)cocktail_reso->Clone("weights_reso"));

  cout << cocktail_sum << "   " << cocktail_charm << "   " << cocktail_beauty << "   " << cocktail_reso << endl;

  // fWeightsSum   = *(dynamic_cast<TH2D*>(file_in->Get("Sum")));
  // fWeightsCharm = *(dynamic_cast<TH2D*>(file_in->Get("Charm")));
  //fWeightsBeauty= *(dynamic_cast<TH2D*>(file_in->Get("Beauty")));

  //fRebinner.Rebin2DHistogram(fWeightsCharm);
  //fRebinner.Rebin2DHistogram(fWeightsBeauty);

  // for now use only HF instead separation of charm and beauty
  //fWeightsCharm.Add(&fWeightsBeauty);

  // fRebinner.Rebin2DHistogram(fWeightsReso);
  //TH2D Pion  = *(dynamic_cast<TH2D*>(file_in->Get("Pion")));
  //TH2D Eta   = *(dynamic_cast<TH2D*>(file_in->Get("Eta")));
  //TH2D EtaP  = *(dynamic_cast<TH2D*>(file_in->Get("EtaPrime")));
  //TH2D Rho   = *(dynamic_cast<TH2D*>(file_in->Get("Rho")));
  //TH2D Omega = *(dynamic_cast<TH2D*>(file_in->Get("Omega")));
  //TH2D Phi   = *(dynamic_cast<TH2D*>(file_in->Get("Phi")));
  //TH2D JPsi  = *(dynamic_cast<TH2D*>(file_in->Get("Jpsi")));
  //fRebinner.Rebin2DHistogram(Pion);
  //fRebinner.Rebin2DHistogram(Eta);
  //fRebinner.Rebin2DHistogram(EtaP);
  //fRebinner.Rebin2DHistogram(Rho);
  //fRebinner.Rebin2DHistogram(Omega);
  //fRebinner.Rebin2DHistogram(Phi);
  //fRebinner.Rebin2DHistogram(JPsi);

  //fWeightsReso = Pion;
  //fWeightsReso.Add(&Eta);
  //fWeightsReso.Add(&EtaP);
  //fWeightsReso.Add(&Rho);
  //fWeightsReso.Add(&Omega);
  //fWeightsReso.Add(&Phi);
  //fWeightsReso.Add(&JPsi);

  fWeightsSum = *((TH2D*)cocktail_reso->Clone("weights_sum"));
  fWeightsSum.Add(&fWeightsBeauty);
  fWeightsSum.Add(&fWeightsCharm);

  //fWeightsSum.GetZaxis()->SetRangeUser(1e-6, 10);
  //fWeightsReso.GetZaxis()->SetRangeUser(1e-6, 10);
  //fWeightsCharm.GetZaxis()->SetRangeUser(1e-6, 10);

  fWeightsSum.SetName("cocktail_sum");
  fWeightsReso.SetName("cocktail_reso");
  fWeightsCharm.SetName("cocktail_charm");
  fWeightsBeauty.SetName("cocktail_beauty");

  delete file_in;
}

//double GetWeight(bool isReso, double mass, double ptee){
//  double weight_reso     = 0;
//  double weight_hf       = 0;
//  double weight_sum = GetYield(mass, ptee, fWeightsSum);
//  //cout << "wut " << weight_sum << endl;
//  if (weight_sum <= 0 || weight_sum < 3e-9) return 0.5;
//  weight_reso = GetYield(mass, ptee, fWeightsReso);
//  weight_hf   = GetYield(mass, ptee, fWeightsCharm);
//  double result_reso = weight_reso / weight_sum;
//  double result_hf = weight_hf / weight_sum;
//  if(result_reso <0.01){
//    result_reso = 0;
//    result_hf = 1;
//  }
//  if(result_hf <0.01){
//    result_reso = 0;
//    result_hf = 1;
//  }
//
//  if (isReso){
//    return result_reso;
//  }
//  else{
//    return result_hf;
//  }
//}

double GetWeight(bool isReso, double mass, double ptee)
{
  //std::cout << "wrong weight" << std::endl;
  double weight = 0;
  double weight_sum = GetYield(mass, ptee, fWeightsSum);
  //cout << "wut " << weight_sum << endl;
  if (weight_sum <= 0) {
    if (isReso)
      return 0;
    else
      return 1.;
  }
  if (isReso) {
    weight = GetYield(mass, ptee, fWeightsReso);
    //cout << "reso " << weight << endl;
  } else {
    weight = GetYield(mass, ptee, fWeightsHF);
    //cout << "hf " << weight << endl;
  }
  double result = weight / weight_sum;
  // std::cout << result << std::endl;
  if (weight < 3e-9 && isReso) {
    return 0;
  }
  if (weight < 3e-9 && !isReso) {
    return 0;
  }
  //if (weight_sum < 3e-9) return 0;

  //if ((result > 1 || result < 0) && isReso)  LmHelper::Error(Form("in bin mass = %f, ptee = %f the weight in reso  is result = %f, weight = %f, weight_sum = %f", mass, ptee, result, weight, weight_sum));
  //if ((result > 1 || result < 0) && !isReso) LmHelper::Error(Form("in bin mass = %f, ptee = %f the weight in charm is result = %f, weight = %f, weight_sum = %f", mass, ptee, result, weight, weight_sum));
  return weight / weight_sum;
}

double GetWeight(int type, double mass, double ptee)
{
  double weight = 0;
  double weight_sum = GetYield(mass, ptee, fWeightsSum);
  //cout << "wut " << weight_sum << endl;
  if (weight_sum <= 0) {
    return 0;
  }
  if (type == 0) {
    weight = GetYield(mass, ptee, fWeightsReso);
    //cout << "reso " << weight << endl;
  } else if (type == 1) {
    weight = GetYield(mass, ptee, fWeightsCharm);
    //cout << "hf " << weight << endl;
  } else if (type == 2) {
    weight = GetYield(mass, ptee, fWeightsBeauty);
  }

  double result = weight / weight_sum;
  // std::cout << result << std::endl;
  if (weight < 3e-9) {
    return 0;
  }
  if (weight < 3e-9) {
    return 0;
  }
  //if (weight_sum < 3e-9) return 0;

  //if ((result > 1 || result < 0) && isReso)  LmHelper::Error(Form("in bin mass = %f, ptee = %f the weight in reso  is result = %f, weight = %f, weight_sum = %f", mass, ptee, result, weight, weight_sum));
  //if ((result > 1 || result < 0) && !isReso) LmHelper::Error(Form("in bin mass = %f, ptee = %f the weight in charm is result = %f, weight = %f, weight_sum = %f", mass, ptee, result, weight, weight_sum));
  return weight / weight_sum;
}

double GetYield(double mass, double ptee, const TH2D& cocktailPart)
{
  double yield = 0;
  int bin_mass = cocktailPart.GetXaxis()->FindBin(mass);
  int bin_ptee = cocktailPart.GetYaxis()->FindBin(ptee);
  yield = cocktailPart.GetBinContent(bin_mass, bin_ptee);
  //yield        = cocktailPart.GetBinContent(mass, ptee);
  //cout << "yield: " << yield << endl;
  return yield;
}

//_______________________________________________________________________________________________
void Rebin2DHistogram(TH2D& hIn, Int_t n_bins_mee, Double_t* bins_mee, Int_t n_bins_ptee, Double_t* bins_ptee)
{
  /// This function seems a bit dirty, messing around with pointers and references...
  /// Also its computing time is quite noticable, might be reducable...
  //const Char_t* name = hIn.GetName(); // this is not save due to the operation 'hIn = *hOut' below!
  TString sname(hIn.GetName()); // Otherwise potential memory leak
  TH2D* hOut = new TH2D("hOut", hIn.GetTitle(), n_bins_mee, bins_mee, n_bins_ptee, bins_ptee);

  hOut->GetXaxis()->SetTitle(hIn.GetXaxis()->GetTitle());
  hOut->GetYaxis()->SetTitle(hIn.GetYaxis()->GetTitle());
  hOut->GetZaxis()->SetTitle(hIn.GetZaxis()->GetTitle());
  Double_t bin_content_temp = 0;
  Double_t bin_center_mee = -1;
  Double_t bin_center_ptee = -1;

  for (Int_t i_mee = 1; i_mee < hIn.GetNbinsX() + 1; ++i_mee) { //Overflow?
    for (Int_t j_ptee = 1; j_ptee < hIn.GetNbinsY() + 1; ++j_ptee) {
      bin_content_temp = hIn.GetBinContent(i_mee, j_ptee);
      bin_center_mee = hIn.GetXaxis()->GetBinCenter(i_mee);
      //printf(Form(" Bin center mee of bin %i = %f", i_mee, bin_center_mee));
      bin_center_ptee = hIn.GetYaxis()->GetBinCenter(j_ptee);
      hOut->Fill(bin_center_mee, bin_center_ptee, bin_content_temp);
      // hOut->SetBinContent(bin_center_mee, bin_center_ptee, bin_content_temp);
      // hOut->SetBinError(bin_center_mee, bin_center_ptee, TMath::Sqrt(hOut->GetBinContent(bin_center_mee, bin_center_ptee)));
    }
  }
  // Setting the bin error manually to avoid conflicts between root5 and root6
  for (Int_t i_mee = 1; i_mee < hOut->GetNbinsX() + 1; ++i_mee) { //Overflow?
    for (Int_t j_ptee = 1; j_ptee < hOut->GetNbinsY() + 1; ++j_ptee) {
      Double_t bin_content = hOut->GetBinContent(i_mee, j_ptee);
      hOut->SetBinError(i_mee, j_ptee, TMath::Sqrt(bin_content));
    }
  }
  hIn = *hOut;
  hIn.SetName(sname.Data());

  delete hOut;
  return;
}
