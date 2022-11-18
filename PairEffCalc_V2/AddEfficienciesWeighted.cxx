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

// string fCocktailFileName = "../input/cocktail/Cocktail_withSys_21_01_2021_finebins_powheg_30_50_Daiki_jpsi_2018.root";
string fCocktailFileName = "../input/cocktail/Cocktail_withSys_21_01_2021_bigbins_powheg_00_10_Daiki_jpsi_2018.root";
// string fCocktailFileName = "../input/cocktail/Cocktail_withSys_27_09_2021_pythia_smallbins_00_10_nophimtscaling.root";

// Need to adjust binning to analysis bins
std::vector<double> vec_mass_bins{0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00, 1.10, 1.20, 1.40, 1.60, 1.80, 2.00, 2.20, 2.40, 2.60, 2.80, 3.00, 3.06, 3.10, 3.30, 3.50, 4.00};

// Need to adjust binning to analysis bins
std::vector<double> vec_ptee_bins{0., 1., 2., 3., 4., 5., 6., 7., 8.};

TH2D fWeightsHF;
TH2D fWeightsCharm;
TH2D fWeightsBeauty;
TH2D fWeightsSum;
TH2D fWeightsReso;

void ReadCocktailFile();
double GetWeight(bool isReso, double mass, double ptee);
double GetWeight(int type, double mass, double ptee);
double GetYield(double mass, double ptee, const TH2D& cocktailPart);
void Rebin2DHistogram(TH2D& hIn, Int_t n_bins_mee, Double_t* bins_mee, Int_t n_bins_ptee, Double_t* bins_ptee);

enum FileMode { kRecreate = 0, kUpdate };

void AddEfficienciesWeighted(TString settingname = "aodTrackCuts01", FileMode filemode = kRecreate)
{

  Bool_t WriteOutput = kTRUE;
  Bool_t DoWeighting = kTRUE;
  Bool_t DoCombineHF = kTRUE;

  Bool_t DoRebinning = kFALSE;

  // LHC18qr
  // TString filename_in[]    = {"./pair_effv2_LMEE_LEGO1062_LHC20g8a1234_2.root","./pair_effv2_LMEE_LEGO1061_LHC20g8b1234_2_fromD.root","./pair_effv2_LMEE_LEGO1061_LHC20g8b1234_2_fromB.root"};
  // TString filename_out     = "./pair_effv2_CockWeighted_PbPb2018_v7_cut2_200.root";
  TString baseDir = {"./output/pass1/"};
  TString filename_in[] = {"LHC18f3.root", "LHC19h9_charm.root", "LHC19h9_beauty.root"};
  TString filename_out = "./pair_effv2_CockWeighted.root";

  // std::vector<TString> settingname;
  // for (int i = 1; i <= 10; ++i) {
  //   settingname.push_back(Form("aodTrackCuts%02d", i));
  // }

  TString gens[] = {"Ngen", "Ngen_ULS", "Ngen_ULS"};
  TString recs[] = {"Nrec", "Nrec_ULS", "Nrec_ULS"};
  TString typnames[] = {"sameMother", "eleFinalStateFromD", "eleFinalStateFromB"};

  Int_t components = 3;
  cout << "Number of components: " << components << endl;

  ReadCocktailFile();

  TFile* file = 0x0;

  TFile* file_out = nullptr;
  if(filemode == kRecreate) file_out = TFile::Open(filename_out, "RECREATE");
  else if(filemode == kUpdate) file_out = TFile::Open(filename_out, "UPDATE");
  if (file_out->IsOpen()) cout << "File opened successfully" << endl;
  TDirectoryFile* fDir = nullptr;
  TString str1, str2;

  // for (auto it : settingname) {
    TH2D* h2_PairEffs[3];
    TH2D* h2_gen[3];
    TH2D* h2_reco[3];
    for (Int_t i1 = 0; i1 < components; i1++) {
      file = TFile::Open(baseDir + filename_in[i1], "READ");
      if (file->IsOpen()) cout << "File opened successfully" << endl;
      str1 = (gens[i1] + "_" + typnames[i1]).Data();
      // str2 = (recs[i1] + "_" + it + "_" + typnames[i1]).Data();
      str2 = (recs[i1] + "_" + settingname + "_" + typnames[i1]).Data();

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
    fDir = new TDirectoryFile(settingname, settingname);
    // fDir = new TDirectoryFile(it, it);
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

    cout
      << "Starting" << endl;

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

      h2_PairEffs[0]->Write("NrecoPairsRecResonances");
      if (DoCombineHF)
        h2_PairEffs[1]->Write("NrecoPairsRecHF");
      else {
        h2_PairEffs[1]->Write("NrecoPairsRecCharm");
        h2_PairEffs[2]->Write("NrecoPairsRecBeauty");
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
            // cout << "  Checking " << genPairs->GetBinContent(bin_x, bin_y) << endl;

            if (genPairs->GetBinContent(bin_x, bin_y)) {
              genPairs->SetBinContent(bin_x, bin_y, 1.);

              //          cout << "binx: " << genPairs->GetNbinsX() << "  biny: " << genPairs->GetNbinsY() << endl;
              // cout << "x: " << genPairs->GetXaxis()->GetBinCenter(bin_x) << "  y: " << genPairs->GetYaxis()->GetBinCenter(bin_y) << endl;

              eff_reso = h2_PairEffs[0]->GetBinContent(bin_x, bin_y);
              eff_reso_err = h2_PairEffs[0]->GetBinError(bin_x, bin_y);
              eff_hf = h2_PairEffs[1]->GetBinContent(bin_x, bin_y);
              eff_hf_err = h2_PairEffs[1]->GetBinError(bin_x, bin_y);

              double weight_reso = GetWeight(true, genPairs->GetXaxis()->GetBinCenter(bin_x), genPairs->GetYaxis()->GetBinCenter(bin_y));
              double weight_hf = GetWeight(false, genPairs->GetXaxis()->GetBinCenter(bin_x), genPairs->GetYaxis()->GetBinCenter(bin_y));

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

              // Check the efficiencies
              if (eff_reso == 0) { // if the resonance efficiency is 0, we only use the HF efficiency
                weight_reso = 0.;
                weight_hf = 1;
              }
              if (eff_hf == 0) { // if the hf efficiency is 0, we only use the resonance efficiency
                weight_reso = 1;
                weight_hf = 0.;
              }
              if (eff_reso == 0 && eff_hf == 0) { // if both efficiencies are 0, we put both weights to 0
                weight_reso = 0;
                weight_hf = 0;
              }
              if (eff_reso > 0.6) { // if efficiency is larger than 0.6 it is probably a stat fluctuation... this should be checked!
                weight_reso = 0;
                weight_hf = 1;
              }

              // cout << "weight reso: " << weight_reso << "  weight_hf: " << weight_hf << endl;

              double eff_pair = weight_reso * eff_reso + weight_hf * eff_hf;
              double eff_pair_err = TMath::Sqrt(weight_reso * eff_reso_err * weight_reso * eff_reso_err + weight_hf * eff_hf_err * weight_hf * eff_hf_err);

              if (genPairs->GetXaxis()->GetBinCenter(bin_x) > 2.6) {
                // cout << "  weight reso: " << weight_reso << "  weight_hf: " << weight_hf << endl;
                // cout << "  reso: " << eff_reso << " hf: " << eff_hf << endl;
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

              // std::cout << "weight_reso = " << weight_reso << "   weight_charm = " << weight_ccbar << "   weight_beauty = " << weight_bbbar << std::endl;
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

              double eff_pair = weight_reso * eff_reso + weight_ccbar * eff_ccbar + weight_bbbar * eff_bbbar;
              double eff_pair_err = TMath::Sqrt(weight_reso * eff_reso_err * weight_reso * eff_reso_err + weight_ccbar * eff_ccbar_err * weight_ccbar * eff_ccbar_err + weight_bbbar * eff_bbbar_err * weight_bbbar * eff_bbbar_err);

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

      genPairs = (TH2D*)h2_gen[0]->Clone("NgenPairsRec");
      recoPairs = (TH2D*)h2_reco[0]->Clone("NrecoPairsRec");

      genPairs->Write();
      recoPairs->Write();

      // eff_weighted->Delete();
      // genPairs->Delete();
      // recoPairs->Delete();
      // clone_LF->Delete();
      // clone_HF1->Delete();
      // clone_HF2->Delete();
      // clone_HF->Delete();
      // clone_LF->Delete();
      // clone1->Delete();
      // clone2->Delete();
      // clone3->Delete();
      // h2_PairEffs[0]->Delete();
      // h2_PairEffs[1]->Delete();
      // h2_PairEffs[2]->Delete();
    }
  // }
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

  // cout << cocktail_sum << "   " << cocktail_charm << "   " << cocktail_beauty << "   " << cocktail_reso << endl;

  fWeightsSum = *((TH2D*)cocktail_reso->Clone("weights_sum"));
  fWeightsSum.Add(&fWeightsBeauty);
  fWeightsSum.Add(&fWeightsCharm);

  fWeightsSum.SetName("cocktail_sum");
  fWeightsReso.SetName("cocktail_reso");
  fWeightsCharm.SetName("cocktail_charm");
  fWeightsBeauty.SetName("cocktail_beauty");

  delete file_in;
}

double GetWeight(bool isReso, double mass, double ptee)
{
  // std::cout << "wrong weight" << std::endl;
  double weight = 0;
  double weight_sum = GetYield(mass, ptee, fWeightsSum);
  // cout << "wut " << weight_sum << endl;
  if (weight_sum <= 0) {
    if (isReso)
      return 0;
    else
      return 1.;
  }
  if (isReso) {
    weight = GetYield(mass, ptee, fWeightsReso);
    // cout << "reso " << weight << endl;
  } else {
    weight = GetYield(mass, ptee, fWeightsHF);
    // cout << "hf " << weight << endl;
  }
  double result = weight / weight_sum;
  // std::cout << result << std::endl;
  if (weight < 3e-9 && isReso) {
    return 0;
  }
  if (weight < 3e-9 && !isReso) {
    return 0;
  }
  return weight / weight_sum;
}

double GetWeight(int type, double mass, double ptee)
{
  double weight = 0;
  double weight_sum = GetYield(mass, ptee, fWeightsSum);
  // cout << "wut " << weight_sum << endl;
  if (weight_sum <= 0) {
    return 0;
  }
  if (type == 0) {
    weight = GetYield(mass, ptee, fWeightsReso);
    // cout << "reso " << weight << endl;
  } else if (type == 1) {
    weight = GetYield(mass, ptee, fWeightsCharm);
    // cout << "hf " << weight << endl;
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

  return weight / weight_sum;
}

double GetYield(double mass, double ptee, const TH2D& cocktailPart)
{
  double yield = 0;
  int bin_mass = cocktailPart.GetXaxis()->FindBin(mass);
  int bin_ptee = cocktailPart.GetYaxis()->FindBin(ptee);
  yield = cocktailPart.GetBinContent(bin_mass, bin_ptee);
  // yield        = cocktailPart.GetBinContent(mass, ptee);
  // cout << "yield: " << yield << endl;
  return yield;
}

//_______________________________________________________________________________________________
void Rebin2DHistogram(TH2D& hIn, Int_t n_bins_mee, Double_t* bins_mee, Int_t n_bins_ptee, Double_t* bins_ptee)
{
  /// This function seems a bit dirty, messing around with pointers and references...
  /// Also its computing time is quite noticable, might be reducable...
  // const Char_t* name = hIn.GetName(); // this is not save due to the operation 'hIn = *hOut' below!
  TString sname(hIn.GetName()); // Otherwise potential memory leak
  TH2D* hOut = new TH2D("hOut", hIn.GetTitle(), n_bins_mee, bins_mee, n_bins_ptee, bins_ptee);

  hOut->GetXaxis()->SetTitle(hIn.GetXaxis()->GetTitle());
  hOut->GetYaxis()->SetTitle(hIn.GetYaxis()->GetTitle());
  hOut->GetZaxis()->SetTitle(hIn.GetZaxis()->GetTitle());
  Double_t bin_content_temp = 0;
  Double_t bin_center_mee = -1;
  Double_t bin_center_ptee = -1;

  for (Int_t i_mee = 1; i_mee < hIn.GetNbinsX() + 1; ++i_mee) { // Overflow?
    for (Int_t j_ptee = 1; j_ptee < hIn.GetNbinsY() + 1; ++j_ptee) {
      bin_content_temp = hIn.GetBinContent(i_mee, j_ptee);
      bin_center_mee = hIn.GetXaxis()->GetBinCenter(i_mee);
      // printf(Form(" Bin center mee of bin %i = %f", i_mee, bin_center_mee));
      bin_center_ptee = hIn.GetYaxis()->GetBinCenter(j_ptee);
      hOut->Fill(bin_center_mee, bin_center_ptee, bin_content_temp);
      // hOut->SetBinContent(bin_center_mee, bin_center_ptee, bin_content_temp);
      // hOut->SetBinError(bin_center_mee, bin_center_ptee, TMath::Sqrt(hOut->GetBinContent(bin_center_mee, bin_center_ptee)));
    }
  }
  // Setting the bin error manually to avoid conflicts between root5 and root6
  for (Int_t i_mee = 1; i_mee < hOut->GetNbinsX() + 1; ++i_mee) { // Overflow?
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
