#ifndef LMHANDLER_H
#define LMHANDLER_H

// c++ includes
#include <vector>
#include <iostream>
#include <string>
// ROOT includes
#include "TH2.h"
#include "TObjArray.h"
#include "TDirectory.h"
#include "TCanvas.h"
// project includes
#include "LmSignal.h"
#include "LmCocktail.h"
#include "LmHelper.h"

// DOXYGEN Documentation in .cpp files
/// @brief Class responsible for organizing signals (from one or multiple outputs): combine/compare/average them, plot spectra, plot cocktail, write to rootfile.

class LmHandler {
public:
  LmHandler(Int_t type=kNoProcess);
  LmHandler(std::vector<Double_t> BinsPtee_forprojMee, std::vector<Double_t> BinsMee_forprojPtee, Double_t plotMinMee, Double_t plotMaxMee, Double_t plotMinPtee, Double_t plotMaxPtee);
  ~LmHandler();

  // function declarations
  Int_t         Process(Int_t type, Bool_t recursive=kFALSE);
  void          AttachSignal(LmSignal &newsig, std::string newname = "");
  void          SetCocktail(const LmCocktail* cockt) { fLmCocktails.clear(); AttachCocktail(cockt); } // clear may crash because of missing LmCocktail destructor.
  void          AttachCocktail(const LmCocktail* cockt) { fLmCocktails.push_back( new LmCocktail(*cockt) ); fCocktailProcessed=kFALSE; } // using copy constructor of LmCocktail.
  void          InitFromRootfile(TString filename);

  // main plotting function
  void          PrintCompare(unsigned int histBits, unsigned int bin_number, Bool_t projOnMee, const Char_t* filename = "", Bool_t printLegend=kTRUE, Bool_t setLogy=kTRUE, Bool_t setLogx=kFALSE, TCanvas* can=0x0, Bool_t printOnlyAverage=kFALSE);
  void          PrintCompareAll(unsigned int histBits, unsigned int bin_min, unsigned int bin_max, Bool_t projOnMee, const Char_t* filename = "", Bool_t printLegend=kTRUE, Bool_t setLogy=kTRUE, TCanvas* can=0x0, Bool_t printOnlyAverage=kFALSE);
  void          PrintCompareRatio(unsigned int histBits, unsigned int bin_min, unsigned int bin_max, Bool_t projOnMee, const Char_t* filename = "", Bool_t printLegend=kTRUE, Bool_t setLogy=kTRUE, TCanvas* can=0x0, Bool_t printOnlyAverage=kFALSE);
  void          PrintCorrelation(unsigned int histBitX, unsigned int histBitY, unsigned int bin_number, Bool_t projOnMee, const Char_t* filename = "", Bool_t printLegend=kTRUE, Bool_t separatePlots=kTRUE, TCanvas* can=0x0);
  // alias functions
  void          PrintAverage(unsigned int histBits, unsigned int bin_number, Bool_t projOnMee, const Char_t* filename = "", Bool_t printLegend=kFALSE, Bool_t setLogy=kTRUE, TCanvas* can=0x0);
  void          PrintCompareSig_Mee(    unsigned int bin_number = 0, Bool_t printLegend = kTRUE, const Char_t* filename = "", Double_t marginMin=2., Double_t marginMax=2.);
  void          PrintCompareSig_Ptee(   unsigned int bin_number = 0, Bool_t printLegend = kTRUE, const Char_t* filename = "", Double_t marginMin=2., Double_t marginMax=30.);
  void          PrintCompareSoverB_Mee( unsigned int bin_number = 0, Bool_t printLegend = kTRUE, const Char_t* filename = "", Double_t marginMin=2., Double_t marginMax=2.);
  void          PrintCompareSoverB_Ptee(unsigned int bin_number = 0, Bool_t printLegend = kTRUE, const Char_t* filename = "", Double_t marginMin=2., Double_t marginMax=30.);
  void          PrintCompareSignif_Mee( unsigned int bin_number = 0, Bool_t printLegend = kTRUE, const Char_t* filename = "", Double_t marginMin=2., Double_t marginMax=2.);
  void          PrintCompareSignif_Ptee(unsigned int bin_number = 0, Bool_t printLegend = kTRUE, const Char_t* filename = "", Double_t marginMin=2., Double_t marginMax=30.);
  void          PrintCompareSigBkg_Mee( unsigned int bin_number = 0, Bool_t printLegend = kTRUE, const Char_t* filename = "", Double_t marginMin=2., Double_t marginMax=100.);
  void          PrintCompareSigBkg_Ptee(unsigned int bin_number = 0, Bool_t printLegend = kTRUE, const Char_t* filename = "", Double_t marginMin=2., Double_t marginMax=100.);
  void          PrintCompareRfactor_Mee( unsigned int bin_number = 0, Bool_t printLegend = kTRUE, const Char_t* filename = "", Double_t yMin=0.8, Double_t yMax=1.2);
  void          PrintCompareRfactor_Ptee(unsigned int bin_number = 0, Bool_t printLegend = kTRUE, const Char_t* filename = "", Double_t yMin=0.8, Double_t yMax=1.2);
  // output
  void          Write1DHistCocktail(unsigned int histBits, Bool_t projOnMee, TString sigName="");
  void          Write1DHistCombined(unsigned int histBits, Bool_t projOnMee, TString sigName="");
  void          Write1DHistAverage(unsigned int histBits, Bool_t projOnMee, TString sigName="");
  void          Write1DHistSingle(unsigned int histBits, Bool_t projOnMee, Bool_t enumerate = kFALSE);
  void          Write1DHistCocktail(Bool_t projOnMee, Bool_t enumerate = kFALSE);
  void          Write2DHist(unsigned int histBits, Bool_t divideByBinWidth = kFALSE, Bool_t enumerate = kFALSE);
  void          Write2DHistCocktail(Bool_t divideByBinWidth = kFALSE, Bool_t enumerate = kFALSE);
  void          Write3DHist(unsigned int histBits, Bool_t enumerate = kFALSE);
  void          WriteInputInfos(Int_t i_sig = -1); // could be private

  // setters
  void          SetName(const std::string name)                     { fName = name; }
  void          SetType(Int_t type);
  void          SetBinsY_forprojOnX(std::vector<Double_t> bins)     { fBinsPtee_forprojMee=bins; LmHelper::SetEmptyBinnings(fMeeBinnings,  bins.size()-1); } ///< Sets Y-axis bins for projecting the 2D input onto the X-axis in different slices of Y.
  void          SetBinsX_forprojOnY(std::vector<Double_t> bins)     { fBinsMee_forprojPtee=bins; LmHelper::SetEmptyBinnings(fPteeBinnings, bins.size()-1); } ///< Sets X-axis bins for projecting the 2D input onto the Y-axis in different slices of X.
  void          SetBinsPtee_forprojMee(std::vector<Double_t> bins)  { SetBinsY_forprojOnX(bins); } ///< Sets Ptee bins for plotting/projection of Mass spectra in different Ptee regions.
  void          SetBinsMee_forprojPtee(std::vector<Double_t> bins)  { SetBinsX_forprojOnY(bins); } ///< Sets Mee bins for plotting/projection of Pair-Pt spectra in different Mee regions.
  void          SetBinningVectorMee(std::vector<std::vector<Double_t>*> MeeBins) { fMeeBinnings=MeeBins; }
  void          SetBinningVectorPee(std::vector<std::vector<Double_t>*> pteeBins) { fPteeBinnings=pteeBins; }
  void          SetBinningMee(Int_t ibin, std::vector<Double_t> *MeeBins) { fMeeBinnings.at(ibin)=MeeBins; }
  void          SetBinningPtee(Int_t ibin, std::vector<Double_t> *pteeBins) { fPteeBinnings.at(ibin)=pteeBins; }
  void          SetPlotRangeMee(Double_t min, Double_t max)         { fPlotXMeeMin=min; fPlotXMeeMax=max-LmHelper::kSmallDelta; } // small offset to avoid bin edge for plotting.
  void          SetPlotRangePtee(Double_t min, Double_t max)        { fPlotXPteeMin=min; fPlotXPteeMax=max-LmHelper::kSmallDelta; }
  void          SetPlotRangeY(Double_t min, Double_t max)           { fPlotYMin=min; fPlotYMax=max; }
  void          SetPlotRangeX(Double_t min, Double_t max)           { fPlotXMin=min; fPlotXMax=max; }
  void          SetPlotRangeYMargins(Double_t min, Double_t max)    { fPlotYMarginBelowMin=min; fPlotYMarginAboveMax=max; } ///< Set margins used to avoid plotting through the legend/labels. Does not work with the predefined plotting functions, there please pass them directly.
  void          ResetPlotRangeY()                                   { fPlotYMin=-1; fPlotYMax=-1; }
  void          ResetPlotRangeX()                                   { fPlotXMin=-1; fPlotXMax=-1; }
  void          SetPlotRangeRatio(Double_t min, Double_t max)       { fPlotRatioMin=min; fPlotRatioMax=max; SetDoRatio(kTRUE); }
  void          SetRatioTitle(const TString caption)                { fRatioTitle = caption;}
  void          SetRatioTitleSize(const double size)                { fRatioTitleSize = size;}
  void          SetRatioTitleOffset(const double offset)            { fRatioTitleOffset = offset;}
  void          SetDoRatio(bool SDR=1, Double_t ps=0.3, bool log=0) { fDoRatio = SDR; fRatioPadSize=ps; fPlotRatioLogy=log; } ///< Activate plotting of ratio, set relative size of ratio pad, set logy.
  void          SetLabels(TObjArray* labels)                        { fLabels = labels; } ///< Specify a TObjArray with TLatex (or other) objects to modify or suppress automatic generation of labels (see sourcecode).
  void          SetLabelsSize(const double size)                    { fLabelsSize = size;}
  void          SetLegend(TLegend* leg)                             { fLegend = leg; } ///< Specify a filled legend to avoid its automatic generation or an empty legend to define only its position and style.
  void          SetLegendSize(const double size)                    { fLegendSize = size;}
  void          SetLegendSizeInYScaling(const double size)          { fLegendSizeInYScaling = size;}
  void          SetLegendOffsetX(const double offset)               { fLegendOffsetX = offset;}
  void          SetLegendOffsetY(const double offset)               { fLegendOffsetY = offset;}
  void          SetLegendLineSize(const double size)              { fLegendLineSizeFactor = size;}
  void          SetLabelsOffsetX(const double offset)               { fLabelsOffsetX = offset;}
  void          SetLabelsOffsetY(const double offset)               { fLabelsOffsetY = offset;}
  void          SetLegendEntryDrawOption(TString option)            { fLegendEntryDrawOption = option;}
  void          SetLegendOnlyFirstCocktail(Bool_t option)          { fLegendOnlyFirstCocktail = option;}
  void          SetSimpleHistnames(bool SSH=kTRUE)                  { fSimpleHistnames = SSH; }
  void          SetMarkerSize(const double size)                    { fMarkerSize = size;}
  void          SetUseDifferentMarkers(const bool marker)           { fUseDifferentMarkers = marker;}
  void          SetDoConfidenceLevel(bool SDCL=kTRUE)               { fDoConfidenceLevel = SDCL; }
  void          SetConfidenceLevel(Double_t CL)                     { fConfidenceLevel = CL; SetDoConfidenceLevel(); }
  void          SetRootfile(TDirectory* file)                       { fFileOut = file; }
  void          SetLmSignalName(unsigned int i, std::string newname)      { if (fLmSigNames.size()>i)  fLmSigNames.at(i) = newname; } ///< Set name which *this* handler uses as legend entry or file subdirectory for signal i (does not modify the attached LmSignal). Also set by AttachSignal().
  void          SetDrawStyleCocktail(const std::string st, UInt_t i=0)    { if (fLmCocktails.size()>i) fLmCocktails.at(i)->SetDrawStyle(st); }
  void          SetDrawStyleCocktailErr(const std::string st, UInt_t i=0) { if (fLmCocktails.size()>i) fLmCocktails.at(i)->SetDrawStyleErr(st); }
  void          SetDivideOption(const TString st)                   { fDivideOption = st; }
  void          SetCompareSignalsToAverage(Bool_t b = kTRUE)        { fCompareSignalsToAverage = b; fBest[0]=fBest[1]=fBest[2]=-1; } ///< Activates comparison between input signals and average.
  void          SetSelectedSignal(Int_t isig)                       { fSelectedSig = isig; } ///< Specify a signal for certain tasks. E.g. as reference for the Barlow approach to calculate systematic differences.
  void          SetDoSystOnUnlikeSign(bool SDSU=kTRUE);
  void          SetRequestedSignals(const TString st)               { fRequestedSignals = st; } ///< Specify which signals shall be drawn. Useful to get same colors in different plots. E.g. use "023" to skip the second(i=1) of four signals. The order has no effect (yet).
  void          SetAllowedDiscrepancy(Double_t val)                 { fAllowedDiscrepancy = val; }
  void          SetOwner(Bool_t b = kTRUE)                          { fOwner = b; }
  void          SetFileType(const TString type)                     { fFileType = type; }

  // getters
  const char*   GetName()            const { return fName.c_str(); }
  const char*   GetTypename()        const { return fTypename.c_str(); }
  Int_t         GetNSignals()        const { return fLmSig.size(); }
  TH2D*         GetSigComb2D()       const { return GetLmSigCombined()->GetSig2D(); }
  TH2D*         GetBkgComb2D()       const { return GetLmSigCombined()->GetBkg2D(); }
  Double_t      GetPlotRangeYMin()   const { return fPlotYMin; }
  Double_t      GetPlotRangeYMax()   const { return fPlotYMax; }
  Double_t      GetPlotRangeXMin()   const { return fPlotXMin; }
  Double_t      GetPlotRangeXMax()   const { return fPlotXMax; }
  TH2D*         GetRelSystematics()  const { return fRelSystematics; }
  Double_t*     GetChi2_SignalsToAverage() const { return fChi2_SignalsToAverage; }
  Int_t         GetMaxBinProj(Bool_t projOnMee) const; ///< Do not use internally! Useful for plotting-loops in main.cpp. Prevents duplicate printing of an integrated bin.
  Double_t      GetYEdge_forprojOnX(unsigned int bin) const;
  Double_t      GetXEdge_forprojOnY(unsigned int bin) const;
  Double_t      GetPteeEdge_forprojMee(unsigned int bin) const;
  Double_t      GetMeeEdge_forprojPtee(unsigned int bin) const;
  void          GetProjRange(unsigned int bin_number, Bool_t projOnMee, Double_t &proj_min, Double_t &proj_max) const;
  LmSignal*     GetLmSigCombined() const;
  LmSignal*     GetLmSigAverage() const;
  LmSignal*     GetLmSignalI(unsigned int i_sig) const;
  const char*   GetLmSignalName(unsigned int i)  const { return fLmSigNames.at(i).c_str(); }
  LmCocktail*   GetCocktail(UInt_t i=0) const { if (fLmCocktails.size()>i) return fLmCocktails.at(i); else return 0x0; }
  void          GetIndexBestSignals(Int_t* best) { if (fCompareSignalsToAverage) {best[0]=fBest[0]; best[1]=fBest[1]; best[2]=fBest[2];} else {best[0]=best[1]=best[2]=-1;} }
  std::vector<TH1D*> CollectProjections(unsigned int histBits, unsigned int bin_number, Bool_t projOnMee);
  TObjArray*    FillLabels(TObjArray* obj_array, unsigned int bin_number, Bool_t projOnMee, Int_t bin_number_2=-1, Bool_t updateLabels=kTRUE);
  TObjArray*    GetLabels(Bool_t forCorrelPlot=kFALSE) { return GenerateLabels(forCorrelPlot); }
  TLegend*      GetLegend(unsigned int histBit=LmSignal::kSubSig, Bool_t printOnlyAverage=kFALSE) { return GenerateLegend(0,LmBaseSignal::kProjOnMee,histBit,printOnlyAverage); }
  TLegend*      GetLegendPtr()             { return fLegend; } ///< To instead modify the legend after PrintCompare(..., &can), use can.GetListOfPrimitives()->FindObject("legend");
  const char*   GetDivideOption()    const { return fDivideOption.Data(); }
  LmCocktail*   GetLmCocktailI(int cock_i) const { return fLmCocktails.at(cock_i); }
  Int_t         GetNCocktails()      const { return fLmCocktails.size() ; }
  std::vector<Double_t>   GetBinsY_forprojOnX()     {return fBinsPtee_forprojMee; } ///< returns Y-axis bins for projecting the 2D input onto the X-axis in different slices of Y.
  std::vector<Double_t>   GetBinsX_forprojOnY()     {return fBinsMee_forprojPtee; } ///< returns X-axis bins for projecting the 2D input onto the Y-axis in different slices of X.


  enum enType {
    kNoProcess=0,     ///< No specific Type.
    kStd,             ///< Standardhandler, uses one Signal and corresponding background.
    kCombine,         ///< Add n spectra together. Spectra are given to LmHandler via Attachsignal().
    kCompare,         ///< Compare n spectra. Spectra are given to LmHandler via Attachsignal().
    kAverage,         ///< Average attached spectra. Spectra are given to LmHandler via Attachsignal().
    kWeightedAverage, ///< Weighted average of attached spectra. Spectra are given to LmHandler via Attachsignal().
    kSystematic,      ///< Cannot use this type.
    kSystematic_Average,         ///< Calculate systematic deviation as RMS of deviations between given signals and their average.
    kSystematic_WeightedAverage, ///< Calculate systematic deviation as RMS of deviations between given signals and their weighted average.
    kSystematic_BarlowSubset,    ///< This method assumes that 'fSelectedSig' is the total sample and all others are subsets.
    kSystematic_Jerome,          ///< TBA
    kCocktail,        ///< Process the attached cocktail, so that it contains the same projections as the data spectra.
    kCocktailOnly,    ///< Like 'kCocktail', but it will only draw the cocktail. An LmSignal is still needed for the axis and label contents.
    kSubtractCocktail,///< Subtract last attached cocktail from data. Performed on LmHistograms (1D) after projections are done.
    kExtSig1D,        ///< Uses 1D histograms from an external source to create an LmSignal object for plotting etc.
    kExtSig2D,         ///< Not yet implemented.
    kSubtractCocktail2D ///< Subtract last attached cocktail from data. Performed in 2D before projections are done.
    /// please update LmHandler::SetType() when new types are added!
  };

private:
  // functions related to handler types, accessible via Process().
  void          CombineSignals();
  void          AverageSignals(Bool_t weightAverage);
  void          CalcSystematics();
  void          CompareSignalsToAverage();
  void          SubtractCocktailAllBins();
  void          SubtractCocktail(unsigned int iBit, unsigned int bin_number, Bool_t projOnMee, std::vector<Double_t> binning);
  void          SubtractCocktail2D();

  // support functions
  TObjArray*    GenerateLabels(Bool_t forCorrelPlot=kFALSE);
  TLegend*      GenerateLegend(unsigned int bin_number, Bool_t projOnMee, unsigned int histBit=LmSignal::kSubSig, Int_t nExtraEntries=0, Bool_t printOnlyAverage=kFALSE);
  void          ComputeOptimumPlotRangeY(unsigned int histBits, unsigned int bin_number, Bool_t projOnMee, Bool_t printOnlyAverage=kFALSE);
  Bool_t        CheckPlottingDefaultDimensions();
  Bool_t        CheckRequestedSigI(unsigned int i_sig);
  Int_t         GetNRequestedSig();
  Int_t         FirstReqSig();
  LmSignal*     GetReferenceSignal() const; ///< Private getter without error messages. Public versions including Error messages are provided above!
  LmCocktail*   GetLastCocktail()    const { return GetCocktail(fLmCocktails.size()-1); }
  const char*   GetDrawStyleCocktail(UInt_t i=0)    const { if (fLmCocktails.size()>i) return fLmCocktails.at(i)->GetDrawStyle(); else return "hist"; }
  const char*   GetDrawStyleCocktailErr(UInt_t i=0) const { if (fLmCocktails.size()>i) return fLmCocktails.at(i)->GetDrawStyleErr(); else return "E2"; }

  // switches
  Bool_t        fSimpleHistnames;
  Bool_t        fCocktailProcessed;
  Bool_t        fDoConfidenceLevel;
  Double_t      fMarkerSize;
  Bool_t        fUseDifferentMarkers;
  Double_t      fLabelsSize;
  Bool_t        fDoRatio;
  TString       fRatioTitle;
  Double_t      fRatioTitleSize;
  Double_t      fRatioTitleOffset;
  Double_t      fLegendSize;
  Double_t      fLegendLineSizeFactor;
  Double_t      fLegendSizeInYScaling;
  Double_t      fLegendOffsetX;
  Double_t      fLegendOffsetY;
  Double_t      fLabelsOffsetX;
  Double_t      fLabelsOffsetY;
  TString       fLegendEntryDrawOption;
  Bool_t        fLegendOnlyFirstCocktail;
  Bool_t        fCompareSignalsToAverage;
  Bool_t        fOwner;
  // variables
  // make sure to initialize all pointer variables in the constructor(s)!
  // otherwise something like 'if(fLmSigCombined){}' will crash and it is difficult to find the reason!
  std::string   fName;
  Int_t         fType;
  std::string   fTypename;
  std::vector<LmSignal*> fLmSig;
  std::vector<std::string> fLmSigNames;
  LmSignal*     fLmSigCombined;
  LmSignal*     fLmSigAverage;
  TH2D*         fRelSystematics;
  std::vector<LmCocktail*> fLmCocktails;
  std::vector<Double_t> fBinsPtee_forprojMee;
  std::vector<Double_t> fBinsMee_forprojPtee;
  std::vector<std::vector<Double_t>*> fMeeBinnings;
  std::vector<std::vector<Double_t>*> fPteeBinnings;
  Double_t      fPlotXMeeMin;
  Double_t      fPlotXMeeMax;
  Double_t      fPlotXPteeMin;
  Double_t      fPlotXPteeMax;
  Double_t      fPlotYMin;
  Double_t      fPlotYMax;
  Double_t      fPlotXMin;
  Double_t      fPlotXMax;
  Double_t      fPlotYMarginBelowMin;
  Double_t      fPlotYMarginAboveMax;
  Double_t      fRatioPadSize;
  Double_t      fPlotRatioMin;
  Double_t      fPlotRatioMax;
  Bool_t        fPlotRatioLogy;
  TObjArray*    fLabels;
  TLegend*      fLegend;
  Double_t      fConfidenceLevel;
  TDirectory*   fFileOut;
  TString       fDivideOption;
  Double_t*     fChi2_SignalsToAverage;
  Int_t         fBest[3];
  Int_t         fSelectedSig;
  TString       fRequestedSignals;
  Double_t      fAllowedDiscrepancy;
  TString       fFileType;
};

#endif
