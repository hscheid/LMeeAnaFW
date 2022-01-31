// c++ includes
#include <string>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
// ROOT includes
#include "TError.h"
#include "TString.h"
#include "TSystem.h"
#include "TObjArray.h"

// project includes
#include "PairEfficiency.h"
Bool_t debug = kFALSE; // Does nothing. Is only used to avoid linker errors

std::string outputFilename = "";
std::string inputFilename = "";
std::string histFolderGen = "";
std::string histFolderRec = "";

std::string cutSettings = "";

std::string prefixGen = "";
std::string prefixRec = "";

std::string MCSignal_Pair = "";

std::string MCSignal_ULSLS = "";

std::string MCSignal_Basesignal = "";

std::string cocktailWeightsFileName = "";

std::string cocktailParticlesLF = "";
std::string cocktailParticlesHF = "";

std::string parametrizeEfficiency = "";

std::string mee_bins_string = "";
std::string ptee_bins_string = "";

void GetValue(std::string s, std::string& val);
void GetValue(std::string s, Double_t& val);
void GetValue(std::string s, Int_t& val);
void CreateOutputPath(TString sIn, Bool_t stringIsAFile = kFALSE);

int main(int argc, const char* argv[])
{

  gErrorIgnoreLevel = kBreak;
  std::string cFileName("config.txt");
  if (argc < 2) {
    printf("\n\n No config file specified. Abort!\n");
    return 1;
  } else {
    printf("Using config: %s\n", argv[1]);
    cFileName = argv[1];
  }
  std::string line;
  std::ifstream configfile(cFileName.c_str());
  if (configfile.is_open()) {
    printf("Reading config file\n\n");
    while (getline(configfile, line)) {
      if (line[0] == std::string("#") || line.size() == 0) continue;
      if (line.find("outputFilename") < std::string::npos)
        GetValue(line, outputFilename);
      if (line.find("inputFilename") < std::string::npos)
        GetValue(line, inputFilename);
      if (line.find("histFolderGen") < std::string::npos)
        GetValue(line, histFolderGen);
      if (line.find("histFolderRec") < std::string::npos)
        GetValue(line, histFolderRec);
      if (line.find("cutSettings") < std::string::npos)
        GetValue(line, cutSettings);
      if (line.find("prefixGen") < std::string::npos)
        GetValue(line, prefixGen);
      if (line.find("prefixRec") < std::string::npos)
        GetValue(line, prefixRec);
      if (line.find("MCSignal_Pair") < std::string::npos)
        GetValue(line, MCSignal_Pair);
      if (line.find("MCSignal_ULSLS") < std::string::npos)
        GetValue(line, MCSignal_ULSLS);
      if (line.find("MCSignal_Basesignal") < std::string::npos)
        GetValue(line, MCSignal_Basesignal);
      if (line.find("cocktailWeights") < std::string::npos)
        GetValue(line, cocktailWeightsFileName);
      if (line.find("cocktailParticlesLF") < std::string::npos)
        GetValue(line, cocktailParticlesLF);
      if (line.find("cocktailParticlesHF") < std::string::npos)
        GetValue(line, cocktailParticlesHF);
      if (line.find("mee_bins_string") < std::string::npos)
        GetValue(line, mee_bins_string);
      if (line.find("ptee_bins_string") < std::string::npos)
        GetValue(line, ptee_bins_string);

      if (line.find("parametrizeEfficiency") < std::string::npos)
        GetValue(line, parametrizeEfficiency);
    }
    configfile.close();
  } else {
    std::cout << "Could not read config file. ABORT" << std::endl;
    return 1;
  }

  std::vector<std::string> vec_input_filename;
  auto* arr_in = TString(inputFilename.c_str()).Tokenize(";");
  for (int i = 0; i < arr_in->GetEntriesFast(); i++) {
    std::cout << arr_in->At(i)->GetName() << std::endl;
    vec_input_filename.push_back(arr_in->At(i)->GetName());
  }
  std::vector<std::string> vec_output_filename;
  auto* arr_out = TString(outputFilename.c_str()).Tokenize(";");
  for (int i = 0; i < arr_out->GetEntriesFast(); i++) {
    std::cout << arr_out->At(i)->GetName() << std::endl;
    vec_output_filename.push_back(arr_out->At(i)->GetName());
  }
  delete arr_out;
  delete arr_in;

  if (vec_output_filename.size() != vec_input_filename.size()) std::cout << "number of input and output filenames are not equal - FIX IT!" << std::endl;

  for (unsigned int i = 0; i < vec_output_filename.size(); ++i) {
    printf("Configuration: \n");
    printf("Output filename:    \"%s\"\n", vec_output_filename[i].data());
    printf("Input filename:     \"%s\"\n", vec_input_filename[i].data());
    printf("Gen. Pairs Folder:  \"%s\"\n", histFolderGen.data());
    printf("Rec. Pairs Folder:  \"%s\"\n", histFolderRec.data());
    printf("Cutsettings:        \"%s\"\n", cutSettings.data());
    printf("PrefixGen:          \"%s\"\n", prefixGen.data());
    printf("PrefixRec:          \"%s\"\n", prefixRec.data());
    printf("MCSignal_Pair:      \"%s\"\n", MCSignal_Pair.data());
    printf("MCSignal_ULSLS:     \"%s\"\n", MCSignal_ULSLS.data());
    printf("MCSignal_Basesignal:\"%s\"\n", MCSignal_Basesignal.data());
    printf("cocktailWeights:    \"%s\"\n", cocktailWeightsFileName.data());
    printf("cocktailParticlesLF:  \"%s\"\n", cocktailParticlesLF.data());
    printf("cocktailParticlesHF:  \"%s\"\n", cocktailParticlesHF.data());
    printf("parametrizeEfficiency:  \"%s\"\n", parametrizeEfficiency.data());
    printf("Mee rebinning:          \"%s\"\n", mee_bins_string.data());
    printf("Ptee rebinning:         \"%s\"\n", ptee_bins_string.data());
    printf("\n");
    CreateOutputPath(vec_output_filename[i].data(), kTRUE);

    PairEfficiency paireff;
    paireff.SetOutputFilename(vec_output_filename[i]);
    paireff.SetInputFilename(vec_input_filename[i]);
    paireff.SetHistFolderGen(histFolderGen);
    paireff.SetHistFolderRec(histFolderRec);
    paireff.SetCutSettings(cutSettings);
    paireff.SetPrefixGen(prefixGen);
    paireff.SetPrefixRec(prefixRec);
    paireff.SetMCSignal_Pair(MCSignal_Pair);
    paireff.SetMCSignal_ULSLS(MCSignal_ULSLS);
    paireff.SetMCSignal_Basesignal(MCSignal_Basesignal);
    paireff.SetCocktailFile(cocktailWeightsFileName);
    paireff.SetCocktailParticles(cocktailParticlesLF);
    paireff.SetCocktailParticlesHF(cocktailParticlesHF);

    paireff.ParametrizeEfficiency(parametrizeEfficiency);

    paireff.SetRebinnerBinningMass(mee_bins_string);
    paireff.SetRebinnerBinningPtee(ptee_bins_string);
    paireff.SetRebinner();

    paireff.CalcEfficiency();
  }
  return 0;
}
//______________________________________________________________________________________
void GetValue(std::string s, std::string& val)
{
  size_t first(s.find_first_of("\"")), last(s.find_last_of("\"", s.find("#")));
  if (first == last || first == std::string::npos || last == std::string::npos)
    val = "";
  else
    val = s.substr(first + 1, last - (first + 1));
}
//______________________________________________________________________________________
void GetValue(std::string s, Double_t& val)
{
  size_t first(s.find_first_of("-0123456789")), last(s.find_last_of("0123456789", s.find("#")));
  if (first == std::string::npos || last == std::string::npos) return;
  val = std::atof(s.substr(first, last - first + 1).data());
}
//______________________________________________________________________________________
void GetValue(std::string s, Int_t& val)
{
  size_t first(s.find_first_of("-0123456789")), last(s.find_last_of("0123456789", s.find("#")));
  if (first == std::string::npos || last == std::string::npos) return;
  val = std::atoi(s.substr(first, last - first + 1).data());
}
//______________________________________________________________________________________
void CreateOutputPath(TString sIn, Bool_t stringIsAFile)
{
  TString sPathOut = "";
  if (stringIsAFile)
    sPathOut = sIn(0, sIn.Last('/'));
  else
    sPathOut = sIn;
  std::cout << sPathOut << std::endl;
  if (gSystem->Exec(Form("ls %s > /dev/null", sPathOut.Data())) != 0) // path is available if Exec()==0
  {
    Printf("Creating output directory: %s\n", sPathOut.Data());
    gSystem->Exec(Form("mkdir -p %s", sPathOut.Data())); // recursively create folder/subfolder/... if needed
  }
}
