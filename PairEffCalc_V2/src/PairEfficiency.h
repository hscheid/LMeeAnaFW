# ifndef PAIREFFICIENCY_H
# define PAIREFFICIENCY_H

#include <iostream>
#include <string>
#include <vector>

#include "TH2D.h"

#include "TFile.h"
#include "../../PlottingFW/src/core/LmRebinner.h"

class PairEfficiency{
public:
PairEfficiency() : fRebinner(){
  const std::vector<double> vec_mass_bins{
    0.00, 0.02, 0.04, 0.08, 0.14,
    0.18, 0.22, 0.30, 0.38, 0.54, 0.7, 0.86, 1.1,
    1.70, 2.30, 2.50, 2.70, 2.90, 3.00, 3.10, 3.30, 3.50
  };

  // std::vector<double> vec_ptee_bins{
  //   0.0, 0.2, 0.4, 0.6, 0.8, 1., 2., 3., 4., 6., 8.
  //
  // };
  std::vector<double> vec_ptee_bins{
  0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0,
    2.2, 2.4, 2.6, 2.8, 3.0, 3.4, 3.8, 4.2, 4.6, 5.0, 6., 10.
  };
  fRebinner.SetRebinning2D(vec_mass_bins.size()-1, vec_mass_bins.data(), vec_ptee_bins.size()-1, vec_ptee_bins.data());
  std::cout << "Setting rebinning bins" << std::endl;

};

void CalcEfficiency();

virtual ~PairEfficiency(){
  delete fWeightsFile;
};

void SetOutputFilename(std::string outputFilename) {fOutputFilename = outputFilename;}
void SetInputFilename(std::string inputFilename)   {fInputFilename = inputFilename;}
void SetHistFolderGen(std::string histFolderGen)   {fHistFolderGen = histFolderGen;}
void SetHistFolderRec(std::string histFolderRec)   {fHistFolderRec = histFolderRec;}
void SetPrefixGen(std::string prefixGen)           {fPrefixGen = prefixGen;}
void SetPrefixRec(std::string prefixRec)           {fPrefixRec = prefixRec;}
void SetCutSettings   (const std::string& cutSettings);
void SetMCSignal_Pair (const std::string& MCSignal_Pair);
void SetMCSignal_ULSLS(const std::string& MCSignal_ULSLS);
void SetMCSignal_Basesignal(std::string MCSignal_Baseline) {fMCSignalBaselineString = MCSignal_Baseline;};
void SetCocktailFile(std::string cocktailName)     {fCocktailFileName = cocktailName;}
void SetCocktailParticles(const std::string& cocktailParticles);
void SetCocktailParticlesHF(const std::string& cocktailParticlesHF);
void SetRebinnerBinningMass(const std::string& binning);
void SetRebinnerBinningPtee(const std::string& binning);
void SetRebinner(){fRebinner.SetRebinning2D(fMass_bins.size()-1, fMass_bins.data(), fPtee_bins.size()-1, fPtee_bins.data());}
void ParametrizeEfficiency(std::string effi)     {fParametrizeEfficiency = effi;}
std::vector<TH2D> CalcEfficiency(const std::vector<TH2D>& Rec, const std::vector<TH2D>& Gen);
std::vector<TH2D> CalcEfficiencyToBaseline(const std::vector<TH2D>& effiToBeFitted, const std::vector<TH2D>& effiBaseline);

private:
  void ReadCocktailFile();
  void FillVector(std::string MCSignals, std::vector<std::string>& vec);
  void FillBinning(std::string string, std::vector<double>& vec);
  void FillParametrizeVector(std::string str, std::vector<unsigned int>& vec);
  double GetWeight(bool isReso, double mass, double ptee);
  double GetYield(double mass, double ptee, const TH2D& cocktailPart);

  std::string fOutputFilename = "";
  std::string fInputFilename = "";
  TString fHistFolderGen = "";
  TString fHistFolderRec = "";

  std::string fCutSettings_string = "";
  std::vector<std::string> fCutSettings;

  std::string fPrefixGen = "";
  std::string fPrefixRec = "";


  std::string fMCSignalPairString = "";
  std::string fMCSignalULSLSString = "";
  std::string fMCSignalBaselineString = "";
  std::vector<std::string> fMCSignalPair;
  std::vector<std::string> fMCSignalULSLS;

  std::vector<TH2D> fGenHisto;
  std::vector<TH2D> fRecHisto;
  std::vector<TH2D> fGenHisto_ULS;
  std::vector<TH2D> fRecHisto_ULS;
  std::vector<TH2D> fGenHisto_ULS_Baseline;
  std::vector<TH2D> fRecHisto_ULS_Baseline;
  std::vector<TH2D> fVecEffi;

  std::string fCocktailFileName = "";
  std::string fCocktailParticles_string;
  std::string fCocktailParticlesHF_string;
  std::vector<std::string> fCocktailParticles;
  std::vector<std::string> fCocktailParticlesHF;
  TFile*      fWeightsFile = 0x0;
  TH2D        fWeightsReso;
  TH2D        fWeightsCharm;
  TH2D        fWeightsBeauty;
  TH2D        fWeightsSum;

  std::string fParametrizeEfficiency = "";
  std::vector<unsigned int> fVecParametrizeEffis;

  LmRebinner fRebinner;
  std::vector<double> fMass_bins;
  std::vector<double> fPtee_bins;
};

# endif
