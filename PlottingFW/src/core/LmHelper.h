#ifndef LMHELPER_H
#define LMHELPER_H

// c++ includes
#include <string>
#include <vector>
#include <iostream>
// ROOT includes
#include "TH1.h"
#include "TH2.h"
#include "TObjArray.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TList.h"
#include "TLatex.h"
// project includes

/// Helper class with few static member functions
class LmHelper{
public:
  LmHelper();
  static void   SetDebugLvl(Int_t debug_) {debug = debug_;};

  // functions for printout / debugging
  static void   Info(const std::string str);
  static void   Warning(const std::string str);
  static void   Error(const std::string str);
  static Int_t  ErrorSummary();
  static void   Debug(const std::string str, Int_t debug_lvl);

  // functions for plotting
  static void   TH2_Beautify(TH2D* hist, TCanvas* canv);
  static Int_t  GetUniformColor(Int_t ith_object, Int_t n_objects=8); // n<9 gives ALICE preferred colors.
  static Int_t  GetCompareMarker(Int_t ith_object);
  static Int_t  GetMarker(Int_t ith_object);
  static Int_t  GetCompareFillStyle(Int_t ith_object);
  static void   PrintHistogram(TH1 *h, const std::string filename);
  static void   PrintHistogram(TH2 *h, const std::string filename, const std::string drawOption = "");
  static TObjArray* GetLabelsTemplate(Int_t type, Double_t sizefac=1., Double_t xref=0.575, const Double_t yref=0.82, Double_t yoff=0.06); ///< Dont change historic defaults.
  static TLatex*    BuildTLatex(Double_t x, Double_t y, TString title, TString name="", Double_t textSizeFactor=1.);
  static void   SetCanvasWidth(const Double_t width);
  static void   SetCanvasHeight(const Double_t height);
  static void   CreatePads(TCanvas* can, Int_t nx, Int_t ny, Double_t bottommargin=0.1, Double_t topmargin=0.1, Double_t verticalratio=0.5);
  static void   CreateManyPads(TCanvas* can, Int_t nx, Int_t ny, Double_t bottommargin=0.1, Double_t topmargin=0.1, Double_t leftmargin=0.14, Double_t rightmargin=0.06);

  // functions for histograms
  static void   IntegralAndError(TH2 *h, Double_t &integral, Double_t &error, Double_t Xmin=0., Double_t Xmax=10., Double_t Ymin=0., Double_t Ymax=10.);
  static Int_t  GetNBinsInRange(TH1 *h, Double_t Xmin, Double_t Xmax);
  static void   GetBinCentersInRange(TH1 *h, Double_t Xmin, Double_t Xmax, Double_t* binCenters);
  static TH2D*  CalcRelativeDifference(TH2D *h1, TH2D *h2, const Char_t *name);
  static TObjArray*  MakeCorrelationGraphs(std::vector<TH1D*> vh1, std::vector<TH1D*> vh2, UInt_t firstbin=999, UInt_t lastbin=0, Bool_t correlateErr=kFALSE);
  static TH2D*  CombineHistograms(TH2D *h1, TH2D *h2, std::string name, Double_t MeeMin, Double_t MeeMax, Double_t PteeMin, Double_t PteeMax);
  static TH2D*  MakeHist2Dfrom1D(std::vector<TH1D*> vhProjX, std::string name, Int_t nBinsY, const Double_t* binsY);
  static void   FlipAxes2DHistogram(TH2D& hIn);

  // functions for files and lists in general
  static TFile* SafelyOpenRootfile(const std::string filename);
  static TList* GetList(TFile* fileIn, TString listname);
  static TList* SelectHistosList(TList* histlist, TString histnames, Bool_t bExact=kTRUE, TString delimiter=":");
  static void   DeleteList(TList* list);

  // functions for files written by LmHandler::Write...()
  static TH1*   GetHistFromTemplateFile(TFile* fileIn, Int_t ikey, TString histname, Bool_t normNevents=kTRUE);
  static Double_t GetNeventsFromTemplateDir(TDirectory* dir);

  // functions to replace c++11 behaviour
  static void   SetEmptyBinnings(std::vector<std::vector<Double_t>*> &vBinnings, UInt_t nvectors);

  // other functions
  static double CalcUpperLimit(Double_t CL, Double_t n_measured, Double_t background, Double_t background_error,
                               Double_t sensitivity=1., Double_t sensitivity_error=0., Bool_t nondeterministic=kFALSE, Bool_t playground=kFALSE);
  static Int_t  GetIndex(std::vector<Double_t> v, Int_t type);

  // variables
  static Double_t kSmallDelta;

  enum enLabelsType {
    kNone=0,
    kDefault,
    kDefaultNoManager,
    kDefaultOnlyCocktail,
    kDefaultCorrel,
    kPatrick1,
    kPatrickKine1,
    kPatrickBottomUp1,
    kPatrickBottomUp2,
    kPerformance,
    kPreliminary,
    kPaper,
    kDontUse
  };

  enum IndexType {
    kMin=0,
    kMedian,
    kMax
  };

private:
  static std::vector<std::string> v_error;
  static Int_t FI;
  static Int_t debug;
};
#endif
