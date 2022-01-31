#include "PairEfficiency.h"
#include <string>
#include <vector>
#include <iostream>

#include "TString.h"
#include "TObjArray.h"
#include "TFile.h"
#include "TList.h"
#include "TMath.h"
#include "TStyle.h"
#include "TF2.h"

#include "../../PlottingFW/src/core/LmHelper.h"

void PairEfficiency::SetCutSettings(const std::string& settings)
{
  fCutSettings_string = settings;
  std::cout << "Cutsetting in vector: ";
  FillVector(fCutSettings_string, fCutSettings);
}

void PairEfficiency::SetMCSignal_Pair(const std::string& settings)
{
  fMCSignalPairString = settings;
  std::cout << "MCSignal in vector: ";
  FillVector(fMCSignalPairString, fMCSignalPair);
}

void PairEfficiency::SetMCSignal_ULSLS(const std::string& settings)
{
  fMCSignalULSLSString = settings;
  std::cout << "MCSignalULS in vector: ";
  FillVector(fMCSignalULSLSString, fMCSignalULSLS);
}

void PairEfficiency::SetCocktailParticles(const std::string& settings)
{
  fCocktailParticles_string = settings;
  std::cout << "CocktailParticles in vector: ";
  FillVector(fCocktailParticles_string, fCocktailParticles);
}

void PairEfficiency::SetCocktailParticlesHF(const std::string& settings)
{
  fCocktailParticlesHF_string = settings;
  std::cout << "CocktailParticlesHF in vector: ";
  FillVector(fCocktailParticlesHF_string, fCocktailParticlesHF);
}

void PairEfficiency::SetRebinnerBinningMass(const std::string& binning)
{
  std::cout << "Setting Mass binning for rebinning: ";
  FillBinning(binning, fMass_bins);
}

void PairEfficiency::SetRebinnerBinningPtee(const std::string& binning)
{
  std::cout << "Setting PTee binning for rebinning: ";
  FillBinning(binning, fPtee_bins);
}

void PairEfficiency::FillVector(std::string string, std::vector<std::string>& vec)
{
  TString tstring = string;
  auto* arr = tstring.Tokenize(";");
  for (int i = 0; i < arr->GetEntriesFast(); i++) {
    std::cout << arr->At(i)->GetName() << ", ";
    vec.push_back(arr->At(i)->GetName());
  }
  std::cout << std::endl;
  delete arr;
}

void PairEfficiency::FillBinning(std::string string, std::vector<double>& vec)
{
  TString tstring = string;
  auto* arr = tstring.Tokenize(",");
  for (int i = 0; i < arr->GetEntriesFast(); i++) {
    TString number_string = (arr->At(i)->GetName());
    //std::cout << number_string.Atof() << ", ";
    vec.push_back(number_string.Atof());
    std::cout << vec[i] << ", ";
  }
  std::cout << std::endl;
  delete arr;
}

void PairEfficiency::FillParametrizeVector(std::string string, std::vector<unsigned int>& vec)
{
  TString tstring = string;
  auto* arr = tstring.Tokenize(";");
  for (int i = 0; i < arr->GetEntriesFast(); i++) {
    unsigned int tmp = std::stoul(arr->At(i)->GetName());
    std::cout << tmp << ", ";
    vec.push_back(tmp);
  }
  std::cout << std::endl;
  delete arr;
}

double PairEfficiency::GetWeight(bool isReso, double mass, double ptee)
{
  double weight = 0;
  double weight_sum = GetYield(mass, ptee, fWeightsSum);
  if (weight_sum <= 0) return 0;
  if (isReso) {
    weight = GetYield(mass, ptee, fWeightsReso);
  } else {
    weight = GetYield(mass, ptee, fWeightsCharm);
  }
  double result = weight / weight_sum;
  // std::cout << result << std::endl;
  if (weight < 3e-7 && isReso) {
    return 0;
  }
  if (weight < 3e-7 && !isReso) {
    return 0;
  }
  if (weight_sum < 3e-7) return 0;

  if ((result > 1 || result < 0) && isReso) LmHelper::Error(Form("in bin mass = %f, ptee = %f the weight in reso  is result = %f, weight = %f, weight_sum = %f", mass, ptee, result, weight, weight_sum));
  if ((result > 1 || result < 0) && !isReso) LmHelper::Error(Form("in bin mass = %f, ptee = %f the weight in charm is result = %f, weight = %f, weight_sum = %f", mass, ptee, result, weight, weight_sum));
  if (result > 1) return 1;
  return result;
}
double PairEfficiency::GetYield(double mass, double ptee, const TH2D& cocktailPart)
{
  double yield = 0;
  int bin_mass = cocktailPart.GetXaxis()->FindBin(mass);
  int bin_ptee = cocktailPart.GetYaxis()->FindBin(ptee);
  yield = cocktailPart.GetBinContent(bin_mass, bin_ptee);
  return yield;
}

void PairEfficiency::ReadCocktailFile()
{
  TFile* file_in = LmHelper::SafelyOpenRootfile(fCocktailFileName.c_str());
  //TFile* file_in = TFile::Open(fCocktailFileName.c_str(), "READ");
  // fWeightsSum   = *(dynamic_cast<TH2D*>(file_in->Get("Sum")));
  //fWeightsCharm = *(dynamic_cast<TH2D*>(file_in->Get("Charm")));
  //fWeightsBeauty= *(dynamic_cast<TH2D*>(file_in->Get("Beauty")));
  fWeightsCharm = *(dynamic_cast<TH2D*>(file_in->Get(fCocktailParticlesHF[0].c_str())));
  fWeightsBeauty = *(dynamic_cast<TH2D*>(file_in->Get(fCocktailParticlesHF[1].c_str())));

  fRebinner.Rebin2DHistogram(fWeightsCharm);
  fRebinner.Rebin2DHistogram(fWeightsBeauty);

  // for now use only HF instead separation of charm and beauty
  fWeightsCharm.Add(&fWeightsBeauty);

  // fRebinner.Rebin2DHistogram(fWeightsReso);
  //TH2D Pion  = *(dynamic_cast<TH2D*>(file_in->Get("Pion")));
  //TH2D Eta   = *(dynamic_cast<TH2D*>(file_in->Get("Eta")));
  //TH2D EtaP  = *(dynamic_cast<TH2D*>(file_in->Get("EtaPrime")));
  //TH2D Rho   = *(dynamic_cast<TH2D*>(file_in->Get("Rho")));
  //TH2D Omega = *(dynamic_cast<TH2D*>(file_in->Get("Omega")));
  //TH2D Phi   = *(dynamic_cast<TH2D*>(file_in->Get("Phi")));
  //TH2D JPsi  = *(dynamic_cast<TH2D*>(file_in->Get("Jpsi")));
  TH2D Pion = *(dynamic_cast<TH2D*>(file_in->Get(fCocktailParticles[0].c_str())));
  TH2D Eta = *(dynamic_cast<TH2D*>(file_in->Get(fCocktailParticles[1].c_str())));
  TH2D EtaP = *(dynamic_cast<TH2D*>(file_in->Get(fCocktailParticles[2].c_str())));
  TH2D Rho = *(dynamic_cast<TH2D*>(file_in->Get(fCocktailParticles[3].c_str())));
  TH2D Omega = *(dynamic_cast<TH2D*>(file_in->Get(fCocktailParticles[4].c_str())));
  TH2D Phi = *(dynamic_cast<TH2D*>(file_in->Get(fCocktailParticles[5].c_str())));
  TH2D JPsi = *(dynamic_cast<TH2D*>(file_in->Get(fCocktailParticles[6].c_str())));

  fRebinner.Rebin2DHistogram(Pion);
  fRebinner.Rebin2DHistogram(Eta);
  fRebinner.Rebin2DHistogram(EtaP);
  fRebinner.Rebin2DHistogram(Rho);
  fRebinner.Rebin2DHistogram(Omega);
  fRebinner.Rebin2DHistogram(Phi);
  fRebinner.Rebin2DHistogram(JPsi);

  fWeightsReso = Pion;
  fWeightsReso.Add(&Eta);
  fWeightsReso.Add(&EtaP);
  fWeightsReso.Add(&Rho);
  fWeightsReso.Add(&Omega);
  fWeightsReso.Add(&Phi);
  fWeightsReso.Add(&JPsi);

  fWeightsSum = fWeightsReso;
  // fWeightsSum.Add(&fWeightsBeauty);
  fWeightsSum.Add(&fWeightsCharm);

  fWeightsSum.GetZaxis()->SetRangeUser(1e-6, 10);
  fWeightsReso.GetZaxis()->SetRangeUser(1e-6, 10);
  fWeightsCharm.GetZaxis()->SetRangeUser(1e-6, 10);

  fWeightsSum.SetName("cocktail_sum");
  fWeightsReso.SetName("cocktail_reso");
  fWeightsCharm.SetName("cocktail_charm");

  delete file_in;
}

void PairEfficiency::CalcEfficiency()
{
  ReadCocktailFile();

  bool smooth = false;
  bool scale = false;  // scale to binwidth
  bool rebin2D = true; // rebin in 2D
  bool fitToBaseline = false;
  bool plotStuff = true;
  bool doWeightedSum = true;
  bool WriteOnlySum = false;

  TFile fOut(fOutputFilename.c_str(), "RECREATE");

  gStyle->SetPalette(kRainBow);
  TCanvas c1("c1", "c1", 1200, 1200);
  c1.SetRightMargin(0.15);
  c1.SetLogz();
  c1.cd();

  // Read generated histograms from input file for every pair MC signal
  TFile fIn(fInputFilename.c_str(), "READ");

  // #######################################################################################################
  // Getting list from file
  // TList *list_gen = LmHelper::GetList(&fIn, fHistFolderGen.c_str());
  //TList *list_gen_2 = dynamic_cast<TList*>(fIn.Get("efficiency"));
  //TList *list_gen_1 = dynamic_cast<TList*>(list_gen_2->FindObject("Pairs"));
  //TList *list_gen   = dynamic_cast<TList*>(list_gen_1->FindObject("Generated")); //TODO: fix this!
  TList* list_gen = LmHelper::GetList(&fIn, fHistFolderGen);
  for (unsigned int iMCSignal = 0; iMCSignal < fMCSignalPair.size(); ++iMCSignal) {
    std::string histoGenName = fPrefixGen + fMCSignalPair[iMCSignal];

    // Read histogram
    TH2D hGenInput = *(dynamic_cast<TH2D*>(list_gen->FindObject(histoGenName.c_str()))); // Read histograms from file

    if (rebin2D) fRebinner.Rebin2DHistogram(hGenInput);
    if (scale) hGenInput.Scale(1., "width");

    // Put in vector for later storing
    fGenHisto.push_back(std::move(hGenInput));

    if (plotStuff) {
      hGenInput.SetContour(255);
      hGenInput.SetAxisRange(1e-3, 1e6, "Z");
      hGenInput.DrawCopy("colz");
      c1.SaveAs(Form("plots/GenHist_Pair_%s.png", fMCSignalPair[iMCSignal].c_str()));
      TH1D proj1D = *(hGenInput.ProjectionX());
      proj1D.Draw();
      c1.SetLogy();
      c1.SaveAs(Form("plots/GenHist_Pair_Proj_%s.png", fMCSignalPair[iMCSignal].c_str()));
      c1.SetLogy(false);
    }
  }

  // #######################################################################################################
  // Add ULS-LS histograms for generated pairs of every MCULS signal
  for (unsigned int iMCSignal = 0; iMCSignal < fMCSignalULSLS.size(); ++iMCSignal) {

    // Reading of ULS, LS++ and LS-- histograms
    std::string histoGenName_ULS = fPrefixGen + "ULS_" + fMCSignalULSLS[iMCSignal];
    TH2D hGenInputULS = *(dynamic_cast<TH2D*>(list_gen->FindObject(histoGenName_ULS.c_str()))); // Read histograms from file

    if (rebin2D) fRebinner.Rebin2DHistogram(hGenInputULS);
    if (scale) hGenInputULS.Scale(1., "width");

    hGenInputULS.SetName(Form("Ngen_ULS_%s", fMCSignalULSLS[iMCSignal].c_str()));

    // Put in vector for later storing
    fGenHisto_ULS.push_back(hGenInputULS);

    // Create plot
    if (plotStuff) {
      hGenInputULS.SetContour(255);
      hGenInputULS.DrawCopy("colz");
      c1.SaveAs(Form("plots/GenHist_ULS_%s.png", fMCSignalULSLS[iMCSignal].c_str()));
    }
  }

  // #######################################################################################################
  if (fMCSignalBaselineString.size() > 0) {
    // Add Baseline
    // Reading of ULS, LS++ and LS-- histograms
    std::string histoGenName_Baseline = fPrefixGen + "ULS_" + fMCSignalBaselineString;
    TH2D hGenInputULSBaseline = *((TH2D*)list_gen->FindObject(histoGenName_Baseline.c_str())); // Read histograms from file
    hGenInputULSBaseline.SetName(Form("Ngen_ULS_%s", fMCSignalBaselineString.c_str()));
    if (rebin2D) fRebinner.Rebin2DHistogram(hGenInputULSBaseline);
    if (scale) hGenInputULSBaseline.Scale(1., "width");
    fGenHisto_ULS_Baseline.push_back(hGenInputULSBaseline);

    // Create plot
    if (plotStuff) {
      hGenInputULSBaseline.SetContour(255);
      hGenInputULSBaseline.DrawCopy("colz");
      c1.SaveAs(Form("plots/GenBaselineHist_ULS_%s.png", fMCSignalBaselineString.c_str()));
    }
  }

  delete list_gen;
  //delete list_gen_1;
  //delete list_gen_2;

  // #######################################################################################################
  // Reading reconstructed histograms
  std::vector<std::vector<TH2D>> vec_rec_per_MCSignal;

  for (unsigned int iTrackCuts = 0; iTrackCuts < fCutSettings.size(); ++iTrackCuts) {
    std::vector<TH2D> vec_temp; // used to save the reconstructed MC signals per cutsetting to add them later

    std::string histFolderRecPerCut = fHistFolderRec.Data() + fCutSettings[iTrackCuts];
    // TList *list_rec = LmHelper::GetList(&fIn, histFolderRecPerCut.c_str());

    //TList *list_rec_2 = dynamic_cast<TList*>(fIn.Get("efficiency"));
    //TList *list_rec_1   = dynamic_cast<TList*>(list_rec_2->FindObject("Pairs"));
    TList* list_rec_1 = LmHelper::GetList(&fIn, fHistFolderRec);
    TList* list_rec = dynamic_cast<TList*>(list_rec_1->FindObject(fCutSettings[iTrackCuts].c_str()));

    for (unsigned int iMCSignal = 0; iMCSignal < fMCSignalPair.size(); ++iMCSignal) {
      std::string histoRecName = fPrefixRec + fMCSignalPair[iMCSignal];
      std::cout << histoRecName << std::endl;
      TH2D hRecInput = *(dynamic_cast<TH2D*>(list_rec->FindObject(histoRecName.c_str()))); // Read histograms from file
      hRecInput.SetName(Form("Nrec_%s_%s", fCutSettings[iTrackCuts].c_str(), fMCSignalPair[iMCSignal].c_str()));

      if (rebin2D) fRebinner.Rebin2DHistogram(hRecInput);
      if (scale) hRecInput.Scale(1., "width");

      fRecHisto.push_back(hRecInput);
      vec_temp.push_back(hRecInput);

      if (plotStuff) {
        hRecInput.SetAxisRange(1e-3, 1e6, "Z");
        hRecInput.SetContour(255);
        hRecInput.DrawCopy("colz");
        c1.SaveAs(Form("plots/RecHist_Pair_%s_%s.png", fCutSettings[iTrackCuts].c_str(), fMCSignalPair[iMCSignal].c_str()));
      }
    }

    // #######################################################################################################
    for (unsigned int iMCSignal = 0; iMCSignal < fMCSignalULSLS.size(); ++iMCSignal) {
      // Reading of ULS, LS++ and LS-- histograms
      std::string histoRecName_ULS = fPrefixRec + "ULS_" + fMCSignalULSLS[iMCSignal];
      TH2D hRecInputULS = *(dynamic_cast<TH2D*>(list_rec->FindObject(histoRecName_ULS.c_str()))); // Read histograms from file

      // also save ULS histo
      hRecInputULS.SetName(Form("Nrec_ULS_%s_%s", fCutSettings[iTrackCuts].c_str(), fMCSignalULSLS[iMCSignal].c_str()));

      if (rebin2D) fRebinner.Rebin2DHistogram(hRecInputULS);
      if (scale) hRecInputULS.Scale(1., "width");

      // Put in vector for later storing
      fRecHisto_ULS.push_back(hRecInputULS);

      // Create plot
      if (plotStuff) {
        hRecInputULS.SetContour(255);
        hRecInputULS.DrawCopy("colz");
        c1.SaveAs(Form("plots/RecHist_ULS_%s_%s.png", fCutSettings[iTrackCuts].c_str(), fMCSignalULSLS[iMCSignal].c_str()));
      }
      vec_temp.push_back(hRecInputULS);
    }
    vec_rec_per_MCSignal.push_back(vec_temp);

    // #######################################################################################################
    if (fMCSignalBaselineString.size() > 0) {
      // Reading of ULS, LS++ and LS-- histograms
      std::string histoRecName_ULS = fPrefixRec + "ULS_" + fMCSignalBaselineString;

      TH2D hRecInputULSBaseline = *(dynamic_cast<TH2D*>(list_rec->FindObject(histoRecName_ULS.c_str()))); // Read histograms from file
      hRecInputULSBaseline.SetName(Form("Nrec_ULS_%s_%s", fCutSettings[iTrackCuts].c_str(), fMCSignalBaselineString.c_str()));

      if (rebin2D) fRebinner.Rebin2DHistogram(hRecInputULSBaseline);
      if (scale) hRecInputULSBaseline.Scale(1., "width");

      // Put in vector for later storing
      fRecHisto_ULS_Baseline.push_back(hRecInputULSBaseline);

      // Create plot
      if (plotStuff) {
        hRecInputULSBaseline.SetContour(255);
        hRecInputULSBaseline.DrawCopy("colz");
        c1.SaveAs(Form("plots/RecHist_ULS_%s_%s.png", fCutSettings[iTrackCuts].c_str(), fMCSignalBaselineString.c_str()));
      }
    }
    delete list_rec;
    delete list_rec_1;
    //delete list_rec_2;
  }

  // #######################################################################################################
  // WRITING OF ALL HISTOGRAMS
  fOut.cd();
  if (!WriteOnlySum) {
    for (unsigned int i = 0; i < fGenHisto.size(); ++i) {
      fGenHisto[i].Write();
      if (smooth) {
        TH2D fGenHistoSmoothed = fGenHisto[i];
        fGenHistoSmoothed.SetName(Form("%s_smoothed", fGenHisto[i].GetName()));
        fGenHistoSmoothed.Smooth();
        fGenHistoSmoothed.Write();
      }
    }
    for (unsigned int i = 0; i < fGenHisto_ULS.size(); ++i) {
      fGenHisto_ULS[i].Write();
      if (smooth) {
        TH2D fGenHistoSmoothed = fGenHisto_ULS[i];
        fGenHistoSmoothed.SetName(Form("%s_smoothed", fGenHisto_ULS[i].GetName()));
        fGenHistoSmoothed.Smooth();
        fGenHistoSmoothed.Write();
      }
    }
    for (unsigned int i = 0; i < fRecHisto.size(); ++i) {
      fRecHisto[i].Write();
      if (smooth) {
        TH2D fRecHistoSmoothed = fRecHisto[i];
        fRecHistoSmoothed.SetName(Form("%s_smoothed", fRecHisto[i].GetName()));
        fRecHistoSmoothed.Smooth();
        fRecHistoSmoothed.Write();
      }
    }
    for (unsigned int i = 0; i < fRecHisto_ULS.size(); ++i) {
      fRecHisto_ULS[i].Write();
      if (smooth) {
        TH2D fRecHistoSmoothed = fRecHisto_ULS[i];
        fRecHistoSmoothed.SetName(Form("%s_smoothed", fRecHisto_ULS[i].GetName()));
        fRecHistoSmoothed.Smooth();
        fRecHistoSmoothed.Write();
      }
    }
  }

  for (unsigned int i = 0; i < fGenHisto_ULS_Baseline.size(); ++i) {
    fGenHisto_ULS_Baseline[i].Write();
    if (smooth) {
      TH2D fGenHistoSmoothed = fGenHisto_ULS_Baseline[i];
      fGenHistoSmoothed.SetName(Form("%s_smoothed", fGenHisto_ULS_Baseline[i].GetName()));
      fGenHistoSmoothed.Smooth();
      fGenHistoSmoothed.Write();
    }
  }
  for (unsigned int i = 0; i < fRecHisto_ULS_Baseline.size(); ++i) {
    fRecHisto_ULS_Baseline[i].Write();
    if (smooth) {
      TH2D fRecHistoSmoothed = fRecHisto_ULS_Baseline[i];
      fRecHistoSmoothed.SetName(Form("%s_smoothed", fRecHisto_ULS_Baseline[i].GetName()));
      fRecHistoSmoothed.Smooth();
      fRecHistoSmoothed.Write();
    }
  }

  std::vector<TH2D> vec_eff_summed;
  if (doWeightedSum) {
    c1.SetLogz(false);
    std::cout << "Number of cutsettings: " << vec_rec_per_MCSignal.size() << std::endl;
    if (vec_rec_per_MCSignal[0].size() > 2)
      std::cout << "USE ONLY ONE MCSIGNAL AND ONE MCSIGNALULSLS, for example samemother and charm" << std::endl;
    else {
      for (unsigned int iTrackCuts = 0; iTrackCuts < fCutSettings.size(); ++iTrackCuts) {
        TH2D ResoRec = vec_rec_per_MCSignal[iTrackCuts][0];
        TH2D ResoGen = fGenHisto[0];

        TH2D ResoEff = ResoRec;
        ResoEff.SetAxisRange(0., 0.3, "Z");
        ResoEff.Divide(&ResoGen);
        ResoEff.SetName(Form("eff_%s", ResoEff.GetName()));
        ResoEff.Draw("colz");
        c1.SaveAs(Form("%s.png", ResoEff.GetName()));
        if (!WriteOnlySum) ResoEff.Write();

        TH2D CharmRec = vec_rec_per_MCSignal[iTrackCuts][1];
        TH2D CharmGen = fGenHisto_ULS[0];

        TH2D CharmEff = CharmRec;
        CharmEff.SetAxisRange(0., 0.3, "Z");
        CharmEff.Divide(&CharmGen);
        CharmEff.SetName(Form("eff_%s", CharmEff.GetName()));
        CharmEff.Draw("colz");
        c1.SaveAs(Form("%s.png", CharmEff.GetName()));
        if (!WriteOnlySum) CharmEff.Write();

        TH2D SumEff = ResoRec;
        SumEff.Reset();
        SumEff.SetName(Form("eff_sum_%s", fCutSettings[iTrackCuts].c_str()));
        SumEff.SetAxisRange(0., 0.05, "Z");

        for (int bin_x = 1; bin_x < SumEff.GetNbinsX() + 1; ++bin_x) {
          for (int bin_y = 1; bin_y < SumEff.GetNbinsY() + 1; ++bin_y) {
            double reso_eff = ResoEff.GetBinContent(bin_x, bin_y);
            double reso_eff_error = ResoEff.GetBinError(bin_x, bin_y);
            double charm_eff = CharmEff.GetBinContent(bin_x, bin_y);
            double charm_eff_error = CharmEff.GetBinError(bin_x, bin_y);

            double mass = SumEff.GetXaxis()->GetBinCenter(bin_x);
            double ptee = SumEff.GetYaxis()->GetBinCenter(bin_y);

            double weight_reso = GetWeight(true, mass, ptee);
            double weight_charm = GetWeight(false, mass, ptee);

            // std::cout << "weight_reso = " << weight_reso << "   weight_charm = " << weight_charm << std::endl;
            if (weight_reso <= 0) {
              weight_charm = 1.;
              weight_reso = 0.;
            } else if (weight_charm <= 0) {
              weight_reso = 1.;
              weight_charm = 0.;
            } else if (reso_eff == 0) {
              weight_charm = 1;
              weight_reso = 0.;
            } else if (charm_eff == 0) {
              weight_reso = 1;
              weight_charm = 0.;
            } else if (reso_eff == 0 && charm_eff == 0) {
              weight_reso = 0;
              weight_charm = 0;
            } else if (std::isnan(weight_reso) || std::isnan(weight_charm)) {
              weight_reso = 0;
              weight_charm = 0;
            }

            if (weight_reso + weight_charm > 1.0001 || weight_reso + weight_charm < 0.9999) {
              LmHelper::Error(Form("Weights in m=%f GeV/c2 and pT=%f GeV/c do not add up to 1: weight_reso + weight_charm = %f + %f = %f", mass, ptee, weight_reso, weight_charm, weight_reso + weight_charm));
            }

            double pair_eff = weight_reso * reso_eff + weight_charm * charm_eff;
            double pair_eff_error = TMath::Sqrt(weight_reso * reso_eff_error * weight_reso * reso_eff_error + weight_charm * charm_eff_error * weight_charm * charm_eff_error);

            if ((pair_eff < reso_eff && pair_eff < charm_eff) || (pair_eff > reso_eff && pair_eff > charm_eff)) LmHelper::Error(std::string("U Suck"));

            SumEff.SetBinContent(bin_x, bin_y, pair_eff);
            SumEff.SetBinError(bin_x, bin_y, pair_eff_error);
          }
        }

        SumEff.Draw("colz");
        c1.SaveAs(Form("%s.png", SumEff.GetName()));

        SumEff.Write();

        if (smooth) {
          TH2D SumEffSmoothed = SumEff;
          SumEffSmoothed.SetName(Form("%s_smoothed", SumEffSmoothed.GetName()));
          SumEffSmoothed.Smooth();
          SumEffSmoothed.Write();
        }

        vec_eff_summed.push_back(SumEff);

        // TH2D GenSum;
        // GenSum = fGenHisto[0];
        // GenSum.Reset();
        // GenSum.SetName(Form("gen_sum_%s", fCutSettings[iTrackCuts].c_str()));
        // for (unsigned int bin_x = 0; bin_x < GenSum.GetNbinsX()+2; ++bin_x){
        //   for (unsigned int bin_y = 0; bin_y < GenSum.GetNbinsY()+2; ++bin_y){
        //     if (SumEff.GetBinContent(bin_x, bin_y) > 1e-5){
        //       GenSum.SetBinContent(bin_x, bin_y, 1);
        //       GenSum.SetBinError  (bin_x, bin_y, 0);
        //     }
        //   }
        // }
        // GenSum.Write();
      }
    }
  }

  if (plotStuff) {
    fVecEffi.clear();
    std::cout << "Creating efficiency plots for MC signal" << std::endl;
    for (unsigned int i = 0; i < fRecHisto.size(); ++i) {
      for (unsigned int j = 0; j < fGenHisto.size(); ++j) {
        TH2D effffi = fRecHisto[i];
        effffi.Divide(&(fGenHisto[j]));
        effffi.SetStats(false);
        effffi.SetAxisRange(0., 0.3, "Z");
        effffi.SetStats(false);
        effffi.SetContour(255);
        effffi.DrawCopy("colz");
        fVecEffi.push_back(effffi);
        c1.SetLogz(false);
        // c1.SaveAs(Form("plots/eff_Pair_%s.png", effffi.GetName()));
      }
    }
    std::cout << "Creating efficiency plots for MC signal ULS" << std::endl;
    for (unsigned int i = 0; i < fRecHisto_ULS.size(); ++i) {
      for (unsigned int j = 0; j < fGenHisto_ULS.size(); ++j) {
        TH2D effi = fRecHisto_ULS[i];
        effi.Divide(&(fGenHisto_ULS[j]));
        effi.SetStats(false);
        effi.SetAxisRange(0., 0.3, "Z");
        effi.SetStats(false);
        effi.SetContour(255);
        effi.DrawCopy("colz");
        fVecEffi.push_back(effi);

        c1.SetLogz(false);
        // c1.SaveAs(Form("plots/eff_ULS_%s.png", effi.GetName()));
      }
    }
  }

  if (fitToBaseline) {
    std::vector<TH2D> vec_eff_MCSignal = CalcEfficiency(fRecHisto, fGenHisto);
    std::vector<TH2D> vec_eff_MCSignal_ULSLS = CalcEfficiency(fRecHisto_ULS, fGenHisto_ULS);
    std::vector<TH2D> vec_eff_MCSignal_Baseline = CalcEfficiency(fRecHisto_ULS_Baseline, fGenHisto_ULS_Baseline);
    std::cout << "vec_eff_MCSignal.size(): " << vec_eff_MCSignal.size() << "   vec_eff_MCSignal_ULSLS.size():" << vec_eff_MCSignal_ULSLS.size() << "    vec_eff_MCSignal_Baseline.size():" << vec_eff_MCSignal_Baseline.size() << std::endl;
    for (const TH2D& h2 : vec_eff_MCSignal) {
      h2.Write();
    }
    for (const TH2D& h2 : vec_eff_MCSignal_ULSLS) {
      h2.Write();
    }
    for (const TH2D& h2 : vec_eff_MCSignal_Baseline) {
      h2.Write();
    }

    std::vector<TH2D> vec_eff_MCSignal_FitToBaseline = CalcEfficiencyToBaseline(vec_eff_MCSignal, vec_eff_MCSignal_Baseline);
    std::vector<TH2D> vec_eff_MCSignal_ULS_FitToBaseline = CalcEfficiencyToBaseline(vec_eff_MCSignal_ULSLS, vec_eff_MCSignal_Baseline);
    std::vector<TH2D> vec_eff_summed_FitToBaseline = CalcEfficiencyToBaseline(vec_eff_summed, vec_eff_MCSignal_Baseline);
    // std::cout << "vec_eff_MCSignal_ULS_FitToBaseline.size(): " << vec_eff_MCSignal_ULS_FitToBaseline.size() << "   vec_eff_MCSignal_FitToBaseline.size():" << vec_eff_MCSignal_FitToBaseline.size() << std::endl;

    for (const TH2D& h2 : vec_eff_MCSignal_FitToBaseline) {
      h2.Write();
    }
    for (const TH2D& h2 : vec_eff_MCSignal_ULS_FitToBaseline) {
      h2.Write();
    }
    for (const TH2D& h2 : vec_eff_summed_FitToBaseline) {
      h2.Write();
    }
  }

  TH2D Gen1 = fRecHisto[0];
  Gen1.Clear();
  Gen1.SetName("Baseline_1");
  for (int x = 0; x <= Gen1.GetNbinsX(); ++x) {
    for (int y = 0; y <= Gen1.GetNbinsY(); ++y) {
      Gen1.SetBinContent(x, y, 1);
      Gen1.SetBinError(x, y, 0);
    }
  }
  Gen1.Write();

  fOut.Close();

  return;
}

std::vector<TH2D> PairEfficiency::CalcEfficiencyToBaseline(const std::vector<TH2D>& effiToBeFitted, const std::vector<TH2D>& effiBaseline)
{
  std::vector<TH2D> vec_eff;

  // TF2 f2("f2", "[0]*x*x + [1]*x + [2] + [3]*y*y + [4]*y  + [5]", 0., 3.5, 0., 6.);
  TF2 f2("f2", "[0]*x*x*x + [1]*x*x + [2]*x + [3] + [4]*y*y*y + [5]*y*y  + [6]*y + [7]", 0., 4, 0., 6.);

  f2.SetParameters(0, 0, 1, 0, 0, 1);

  f2.SetParLimits(0, -1, 1);
  f2.SetParLimits(1, -1, 1);
  f2.SetParLimits(2, -1, 1);
  f2.SetParLimits(3, 0.5, 2);

  f2.SetParLimits(4, -1, 1);
  f2.SetParLimits(5, -1, 1);
  f2.SetParLimits(6, -1, 1);
  f2.SetParLimits(7, 0.5, 2);

  for (unsigned int i = 0; i < effiToBeFitted.size(); ++i) {
    TH2D effi_in = effiToBeFitted[i];
    TH2D effi_baseline = effiBaseline[i];

    TH2D ratioEffiInToEffiBaseline = effi_in;
    ratioEffiInToEffiBaseline.Divide(&effi_baseline);

    for (int bin_i = 0; bin_i < ratioEffiInToEffiBaseline.GetNbinsX() + 1; bin_i++) {
      if (ratioEffiInToEffiBaseline.GetBinContent(bin_i) < 1e-1) {
        // std::cout << "SOMETHING HAPPENED: " << ratioEffiInToEffiBaseline.GetBinContent(bin_i) << std::endl;
        ratioEffiInToEffiBaseline.SetBinContent(bin_i, 0);
        ratioEffiInToEffiBaseline.SetBinError(bin_i, 0);
      }
    }

    ratioEffiInToEffiBaseline.Fit(&f2);

    TH2D effi_out = effiBaseline[i];
    effi_out.Multiply(&f2);
    effi_out.SetName(Form("baseline_%s", effiToBeFitted[i].GetName()));

    vec_eff.push_back(effi_out);

    f2.SetName(Form("f2_%s", effiToBeFitted[i].GetName()));
    f2.Write();
  }
  return vec_eff;
}

std::vector<TH2D> PairEfficiency::CalcEfficiency(const std::vector<TH2D>& Rec, const std::vector<TH2D>& Gen)
{
  std::vector<TH2D> vec_eff;
  for (unsigned int i = 0; i < Rec.size(); ++i) {
    TH2D rec = Rec[i];
    TH2D gen = Gen[0];
    TH2D eff = rec;
    eff.SetName(Form("eff_%s", rec.GetName()));
    eff.Divide(&gen);
    vec_eff.push_back(eff);
  }

  return vec_eff;
}
