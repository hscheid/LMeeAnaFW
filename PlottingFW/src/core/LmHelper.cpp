// c++ includes
#include <iostream>
using namespace std;
// ROOT includes
#include "TROOT.h"
#include "TDirectory.h"
#include "TStyle.h"
#include "TColor.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TF1.h"
#include "TGraphBentErrors.h"
//#include "TIter.h"//doesn't exist.
// project includes
#include "LmHelper.h"
#include "TGaxis.h"

Int_t LmHelper::debug{1000}; // initialise static member variable

std::vector<std::string> LmHelper::v_error;
Int_t LmHelper::FI;

Double_t LmHelper::kSmallDelta=1e-15;
// useful to avoid bin edge effects when using SetRange() or FindBin().
// 1e-15 is the smallest that still works for 'h->SetAxisRange(min, max-LmHelper::kSmallDelta, "X");' or 'h->GetXaxis()->FindBin(val-LmHelper::kSmallDelta);'

//_______________________________________________________________________________________________
LmHelper::LmHelper(){
/// @brief Constructor of the LmHelper.
/// @details Contains basic style operations

  // gROOT->SetStyle("Plain");
  LmHelper::Info("Style settings in LmHelper used!");
  gStyle->SetOptStat(0);// statistics yes, less, no (1, 11, 0)
  gStyle->SetOptTitle(0); // do not draw histogram title even if not empty
  //gStyle->SetOptFit(0111);  // ver�ndet Gr��e der Statistikbox, evtl noch mehr

  /// @TODO: could use font with absolute size everywhere... dont know the command, ask Philipp
  //text font 43 has absolute size. (then use size 18 or so)


  // Canvas
  Float_t cstretch = 1.2;  //1.2

  //IRC wide
  //SetCanvasWidth(7./4* 580*cstretch); // 580x600 ok to get vertical pdf when importing to ppt.
  //SetCanvasHeight(600*cstretch);

  //IRC height
  SetCanvasWidth( 580*cstretch); // 580x600 ok to get vertical pdf when importing to ppt.
  SetCanvasHeight(600*cstretch);


  // Pad
  gStyle->SetPadLeftMargin(0.14);   // 0.1 = root default
  gStyle->SetPadRightMargin(0.06);
  gStyle->SetPadTopMargin(0.1);     // room for title. and the canvas is higher than wide.
  gStyle->SetPadBottomMargin(0.10);
  gStyle->SetCanvasColor(0);
  gStyle->SetPadColor(0);           // kRed useful for debugging setup of multiple pads.
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);


  //PRL height
//  gStyle->SetPadLeftMargin(0.13); //0.11  // 0.1 = root default
//  gStyle->SetPadRightMargin(0.03);  //0.11
//  gStyle->SetPadTopMargin(0.04);    //0.01 // room for title. and the canvas is higher than wide.
//  gStyle->SetPadBottomMargin(0.07); //0.13
//  gStyle->SetCanvasColor(0);
//  gStyle->SetPadColor(0);           // kRed useful for debugging setup of multiple pads.
//  gStyle->SetCanvasBorderMode(0);
//  gStyle->SetPadBorderMode(0);
//  gStyle->SetPadTickX(1);
//  gStyle->SetPadTickY(1);



  //gStyle->SetPadGridX(1);
  //gStyle->SetPadGridY(1);

  // Axis
//  gStyle->SetLabelOffset(0.01,"y");    // 0.005 = root default
//  gStyle->SetTitleOffset(1.9,"y");
//  // doesnt work for x axis?
//  gStyle->SetLabelOffset(0.01,"x");
//  gStyle->SetTitleOffset(1.3,"x");

  gStyle->SetLabelOffset(0.005,"y");    // 0.005 = root default
  //gStyle->SetTitleOffset(0.65,"y"); // mee wide
  //gStyle->SetTitleOffset(0.6,"y"); // ptee wide

  //gStyle->SetTitleOffset(1.9,"y"); // ptee height wide
  gStyle->SetTitleOffset(1.6,"y"); // ptee height wide


  gStyle->SetLabelOffset(0.005,"x");
  //gStyle->SetTitleOffset(3.1,"x"); // mee wide
  //gStyle->SetTitleOffset(3.,"x"); //ptee wide
  // gStyle->SetTitleOffset(3.5,"x"); //ptee height
  gStyle->SetTitleOffset(1.1,"x");// 1.2 //ptee height

  //TGaxis::SetMaxDigits(1);

  Int_t textFont  = 43;
  Int_t titleFont = 43;
  Int_t labelFont = 43;

  Float_t legendTextSize = 24; //was 20  38
  Float_t labelSize      = 24; //36 44
  Float_t titleSize      = 24;  //32  40

  gStyle->SetTextFont(textFont);
  gStyle->SetLabelFont(textFont);
  gStyle->SetLegendFont(textFont);
  gStyle->SetTitleFont(textFont);

  gStyle->SetTextSize(legendTextSize);
  gStyle->SetLabelSize(labelSize);
  //gStyle->SetLegendTextSize(legendTextSize);
  gStyle->SetTitleSize(titleSize);


  gStyle->SetErrorX(0);
  gStyle->SetEndErrorSize(0);



  //gStyle->SetTitleSize(0.09,"xy");         // 0.04  = root default

  // Legend
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(0);
  //gStyle->SetLegendFont(Style_t font = 62);

  //gStyle->SetFillStyle(0);
  gStyle->SetFrameLineWidth(2);

  gROOT->ForceStyle();

  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  LmHelper::FI = TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  // @TODO: This call seems to produce a memory leak, either in the function CreateGradientColorTable
  // or due to storage in an integer (the mechanism is not clear). A one-time call of this is ok.

  Int_t MyPalette[NCont];
  for (int i=0;i<NCont;i++) MyPalette[i] = LmHelper::FI+i;
  gStyle->SetPalette(NCont, MyPalette);
  gStyle->SetNumberContours(NCont);
  //MyPalette is equivalent to the predefined palette 55 and increasing the contours:
  //  gStyle->SetPalette(55);
  //  gStyle->SetNumberContours(NCont);
}


//_______________________________________________________________________________________________
void LmHelper::TH2_Beautify(TH2D* hist, TCanvas* canv){
/// @brief Sets right Margin to 0.14 and disables the statsbox
/// @param hist Histogram which needs to be beautified
/// @param canv Canvas in which the histogram should be printed
  canv->SetRightMargin(0.14);
  hist->SetStats(kFALSE);
  return;
}

//_______________________________________________________________________________________________
void LmHelper::Info(const std::string str){
  /// Prints info message in green to console.
  std::cout << "\33[0;32m" << "Info: " << str << "\33[0m" << std::endl;
}

//_______________________________________________________________________________________________
void LmHelper::Warning(const std::string str){
  /// Prints warning message in yellow to console, nice for debugging.
  std::cerr << "\33[1;33m" << "WARNING: " << str << "\33[0m" << std::endl;
}

//_______________________________________________________________________________________________
void LmHelper::Error(const std::string str){
/// Prints error message in red to console, nice for debugging. Adds it to a vector which is printed via ErrorSummary
  std::string str_error = std::string("\33[1;31m") + std::string("ERROR: ") + str + std::string("\33[0m");
  // std::cerr << "\33[0;31m" << "ERROR: " << str << "\33[0m" << std::endl;
  std::cerr << str_error << std::endl;
  LmHelper::v_error.push_back(str_error);
}

//_______________________________________________________________________________________________
Int_t LmHelper::ErrorSummary(){
/// Prints error messages which where aggregated since now
  if (v_error.size() == 0) {
    return 0;
  }
  else{
    std::cerr << "\33[1;31m     ERROR SUMMARY\33[0m" << std::endl;
    for (unsigned int i = 0; i < LmHelper::v_error.size(); ++i){
      std::cerr << "(" << i+1 << ")  "<< LmHelper::v_error.at(i) << std::endl;
    }
  }
  return (Int_t)v_error.size();
}


//_______________________________________________________________________________________________
void LmHelper::Debug(const std::string str, Int_t debug_lvl){
  if (debug >= debug_lvl) std::cout << str << std::endl;
}


//_______________________________________________________________________________________________
Int_t LmHelper::GetUniformColor(Int_t ith_object, Int_t n_objects){
/// @brief Gives different colors according to the number of objects.
/// @details If you use less than 9 objects then the preferred ALICE colors are chosen.
/// @details If you use more, then the colors will be evenly distributed over the full RGB range.
/// @param ith_object I-th object you want to colorize
/// @param n_objects Number of objects you want to colorize
/// @return Integer with number of color
  if (n_objects < 9){
    //const Int_t colors[] = {kRed+1, kBlue+1, kGreen+3, kMagenta+1, kOrange-1,kCyan+2,kYellow+2};
    //const Int_t colors[] = {kBlack, kRed+1, kBlue+1, kGreen+3, kMagenta+1, kOrange-1,kCyan+2,kYellow+2};
    const Int_t colors[] = {kBlue+1, kRed+1, kBlack, kGreen+3, kMagenta+1, kOrange-1,kCyan+2,kYellow+2};
    return colors[ith_object];
  }

  const Int_t NCont = 255;
  Int_t MyPalette[NCont];
  for (int i=0;i<NCont;i++) MyPalette[i] = LmHelper::FI+i;
  Int_t currColor = 1.*ith_object/(n_objects+1)*NCont;
  // could be written without filling the array, but this way it is clear what happens.
  return MyPalette[currColor];
}


//_______________________________________________________________________________________________
Int_t LmHelper::GetCompareMarker(Int_t ith_object){
  /// @brief Gives markers which are well visible if they are plotted on top of each other.
  // const Int_t markers[] = {20, 20, 24, 27, 30, 28, 26, 32}; // von Carsten - 3 mal Kreis macht nicht viel Sinn?
  const Int_t markers[] = {20, 25, 5, 27, 30, 28, 26, 32};
  Int_t n_markers = sizeof(markers)/sizeof(*markers);
  if (ith_object<n_markers){
    return markers[ith_object];
  }
  return 3;
}

//_______________________________________________________________________________________________
Int_t LmHelper::GetMarker(Int_t ith_object){
  /// @brief Gives markers which are well visible if they are plotted on top of each other.
  const Int_t markers[] = {20, 21, 34, 33, 29, 22, 23, 24};
  // const Int_t markers[] = {20, 33, 34, 33, 29, 22, 23, 24};
  Int_t n_markers = sizeof(markers)/sizeof(*markers);
  if (ith_object<n_markers){
    return markers[ith_object];
  }
  return 3;
}


//_______________________________________________________________________________________________
Int_t LmHelper::GetCompareFillStyle(Int_t ith_object){
  /// @brief Gives fill styles which should be well visible (needs tuning) if they are plotted on top of each other.
  const Int_t styles[] = {/*3003,*/ 3004, 3005, 3006, 3007, 3011, 3012, 3016};
  Int_t n_styles = sizeof(styles)/sizeof(*styles);
  if (ith_object<n_styles){
    return styles[ith_object];
  }
  else {
    return styles[n_styles-1]+(ith_object-(n_styles-1)); // last style number + 1, 2, 3...
  }
}


//_______________________________________________________________________________________________
double LmHelper::CalcUpperLimit(Double_t CL, Double_t n_measured, Double_t background, Double_t background_error, Double_t sensitivity, Double_t sensitivity_error, Bool_t nondeterministic, Bool_t playground)
/// @brief Calculates the upper limit R of a measurement for a given confidence level
/// @param CL                Desired confidence level (typically 0.90, 0.95, 0.99)
/// @param n_measured        Measured signal (in dilepton analysis: bin content in ULS histogram)
/// @param background        Measured background (in dilepton analysis: bin content in LS*R histogram)
/// @param background_error  Absolute error of the measured background. Statistical error would be sqrt(Background)
/// @param sensitivity       Total sensitivity of measurement. If unclear, use sensitivity=1 and calulate count- or event-based quantities without efficiency etc.
/// @param sensitivity_error Absolute uncertainty on the sensitivity. If sensitivity=1, then just use relative uncertainty here.
/// @param nondeterministic  When set to kTRUE, a random Seed is used and R_test is picked from some random distribution between R_up and R_low instead of always being their mean value.
/// @param playground        Use to develop code without changing the standard behaviour. Currently used to test the Feldman & Cousins "ensemble of experiments". (check sourcecode!)
/// @details An upper and lower startvalue (R_up and R_low) for the to-be-determined limit R is arbitrarily set. R represents the real signal after background subtraction.
/// A background value is drawn from gaus(mean=background, sigma=background_error). This background value + the initial R is put inside a poisson distribution and a value representing a possible measurement is drawn.
/// The sensitivity value, also gauss-smeared by its own error if requested, is multiplied to R _before_ adding it to the background value (tested to be consistent with Barlows calculator!).
/// If this value is smaller than the initial input n_measured, then numerator is incremented. This procedure is done 'denominator' times.
/// The value 1-numerator/denominator after the for loop is the CL for the given R.
/// This procedure is done for a test R between the upper and lower startvalue of R, and these R_test's are successively adjusted until the CL is close enough to the desired value.
/// based on:
/// [1] R. Barlow, Systematic Errors: facts and fictions, http://arxiv.org/abs/hep-ex/0207026v1
/// [2] R. Barlow, A Calculator for Confidence Intervals, http://arxiv.org/abs/hep-ex/0203002
/// further literature:
/// [3] G. J. Feldman, R. D. Cousins, A Unified Approach to the Classical Statistical Analysis of Small Signals, http://arxiv.org/abs/physics/9711021
{
  LmHelper::Debug("LmHelper::CalcUpperLimit()", 5);

  TRandom3 gen(1);
  if (nondeterministic) gen.SetSeed(0);
  if (playground)       n_measured = gen.Poisson(n_measured); // for testing Feldman & Cousins "ensemble of experiments".

  if (n_measured < 0) {
    LmHelper::Warning("LmHelper::CalcUpperLimit(): Measured input must not be negative. Skip calculation.");
    return -1;
  }
  if (sensitivity != 1.) {
    LmHelper::Info("LmHelper::CalcUpperLimit(): Sensitivity unequal to unity. Treatment should be correct, but make sure you understand what you do.");
  }
  if (sensitivity_error != 0) {
    LmHelper::Info("LmHelper::CalcUpperLimit(): Sensitivity error non-zero. Using 'Cousins and Highland' approach.");
  }
  // @TODO: check functionality for zero measurement
  // @TODO: check for zero measurement and zero background.

  restart: // for goto in case of infinite loop. (@TODO: is it a problem that variables are declared below, but that they already exist?!)

  // Starting points for the upper limit of a measurement.
  // They need to be chosen such that the expected value is in between them, no matter if n_measured and/or background is zero.
  double R_up  = 0;
  double R_low = 0;
  // it seems that the correct value is found fastest, if the forefactors add up to about +1... (+4, -2)
  R_up  = n_measured - background + 4. * TMath::Sqrt(TMath::Abs(n_measured) + TMath::Abs(background));
  R_low = n_measured - background - 2. * TMath::Sqrt(TMath::Abs(n_measured) + TMath::Abs(background));
  if (n_measured==0 && background==0) R_up = 10; // set nonzero in case both inputs are zero
  LmHelper::Debug(Form(" Starting Point: R_up = %f, \t R_low = %f", R_up, R_low), 10);//10

  int       numerator   = 1;
  int       denominator = 20000;
  double    R_test      = 0;
  double    current_CL  = 0;
  int       n_poisson   = 0;

  // R_test is used to calculate the current_CL. Is it set as the arithmetic mean of the current R_up and R_low.
  // R_up   should be always higher than the R belonging to the desired CL.
  // R_low  should be always lower than the R belonging to the desired CL.
  // But it can happen that R_up (R_low) can jump below (above) the actual R (belonging to a desired CL). If this happens
  // the function is stuck in the while loop. It will finish if by chance the poisson sampling happens in that way, that
  // the resulting CL is within the threshold in the while condition. The infinite loop can be avoided by choosing looser
  // CL values inside the while condition or using larger denominators from the beginning which lead to less fluctuations.
  int inf_counter = 0;

  double deviation = 0.02; // 0.01
  while ( 1 )
  {
    // iteratively improve precision:
    // could be further tuned, but would need graphical support. already now ~50% improvement compared to static case using 0.001 @ 100k.
    if ( TMath::Abs(current_CL-CL) < deviation*CL ) {
      if (deviation<=0.002) break;  // <=0.001
      deviation   = deviation/10.;
      denominator = denominator*5.;
      LmHelper::Debug(Form(" improved precision: denominator = %i", denominator), 11);//11
      inf_counter = 0; // restart counting at next precision level.
    }

    if (inf_counter > 20) {
      LmHelper::Debug(Form("LmHelper::CalcUpperLimit(): Infinite loop stopped at %i (n_measured=%.2f). restart calculation...", inf_counter, n_measured), 1);//11
      goto restart; // to avoid a bias, 'restart' should be at a point where 'n_measured' is already determined, so not at the very beginning.
    }
    ++inf_counter;

    numerator = 0;
    R_test    = (R_up+R_low)/2;
    if (nondeterministic || playground) {
      // draw R_test from a random distribution around the median in order not to be deterministic. e.g. for the "ensemble of experiments" check.
      R_test  = R_low + (R_up-R_low) * ( 0.25+(gen.Rndm()+gen.Rndm())/4 ); // produces a pyramid-shaped random distribution from 0.25 to 0.75 of the range between R_up and R_low.
    }
    LmHelper::Debug(Form(" Check: R_test = %f", R_test), 11);

    if (!playground) // standard procedure
    {
      for (int i = 0; i < denominator; ++i)
      {
        double background_drawn = background;
        if  (background_error>0)  background_drawn = gen.Gaus(background, background_error);

        // for testing:
        // For small backgrounds, it may be better to use a Poisson distribution (as done by Feldman & Cousins [3]).
        // Using background_drawn = gen.Poisson(background) reproduces almost exactly their example:
        // 1000 'nondeterministic' calls of LmHelper::CalcUpperLimit(0.9, 2., 3.5, 0, 1, 0) give a mean of 2.6983 (instead of 2.67 from Table IV).
        //background_drawn = gen.Poisson(background);
        //background_drawn = n_measured; // another possible test, but does not reproduce...

        // The computation n_poisson = gen.Poisson(R_test + background_drawn)
        // is correct with background and background_error (no sensitivity!).
        // Used: LmHelper::CalcUpperLimit(0.90, 3, 0.5, 0.2, 1, 0.)

        double sensitivity_drawn = sensitivity;
        if  (sensitivity_error>0)  sensitivity_drawn = gen.Gaus(sensitivity, sensitivity_error);

        // The computation n_poisson = gen.Poisson(R_test * sensitivity_drawn + background_drawn)
        // is consistent with the Cousins and Highland result for sensitivity 1 with error.
        // Also consistent when adding a background with error. Used: LmHelper::CalcUpperLimit(0.90, 3, 2, 1, 1., 0.1)
        // Also works with sensitivity != unity. Used: LmHelper::CalcUpperLimit(0.90, 3, 2, 1, 20., 4.)
        n_poisson = gen.Poisson(R_test * sensitivity_drawn + background_drawn);

        if ( n_poisson <= n_measured ) { // need '<=', otherwise inconsistent with Barlows tool!
          numerator++;
        }
      }
    } // end standard procedure
    else // playground // for testing Feldman & Cousins "ensemble of experiments".
    {
      for (int i = 0; i < denominator; ++i) {
        // for comments see standard loop.
        double background_drawn = gen.Poisson(background);
        double sensitivity_drawn = sensitivity;
        n_poisson = gen.Poisson(R_test * sensitivity_drawn + background_drawn);
        if ( n_poisson <= n_measured ) numerator++;
      }
    } // end playground

    current_CL = 1. - (static_cast<double>(numerator) / static_cast<double>(denominator));
    if      (current_CL > CL) R_up  = R_test;
    else if (current_CL < CL) R_low = R_test;
    LmHelper::Debug(Form(" -> Current CL = %f     modified border values: R_up = %f, \t R_low = %f", current_CL, R_low, R_up), 11);//11

  } // end while loop

  LmHelper::Debug(Form(" Final R = %f, \t final CL = %f", R_test, current_CL), 10);//10
  return R_test;
}

//_______________________________________________________________________________________________
void LmHelper::PrintHistogram(TH1 *h, const std::string filename)
{
  TCanvas c("c","");
  c.SetTopMargin(0.02);
  c.SetRightMargin(0.02);
  c.SetLeftMargin(0.12);
  c.SetGridy();

  h->DrawCopy();
  for(Int_t i = 0; i < h->GetListOfFunctions()->GetEntries(); ++i){
     (dynamic_cast<TF1*> (h->GetListOfFunctions()->At(i)))->DrawCopy("same");
  }
  c.SaveAs(filename.data());

}

//_______________________________________________________________________________________________
void LmHelper::PrintHistogram(TH2 *h, const std::string filename, const std::string drawOption)
{
  TCanvas c("c","");
  c.SetRightMargin(0.12);
  h->DrawCopy(drawOption.data());
  c.SaveAs(filename.data());
}

//_______________________________________________________________________________________________
TLatex* LmHelper::BuildTLatex(Double_t x, Double_t y, TString title, TString name, Double_t textSizeFactor)
{
  TLatex* lat = new TLatex(x,y,title);
  if (!name.IsNull()) lat->SetName(name);
  //lat->SetTextFont(gStyle->GetTitleFont());
  //lat->SetTextSize(gStyle->GetTitleSize()*textSizeFactor);
  lat->SetTextFont(gStyle->GetTextFont()); //PRL
  lat->SetTextSize(gStyle->GetTextSize()/**textSizeFactor*/);

  lat->SetNDC();
  return lat;
}

//_______________________________________________________________________________________________
TObjArray* LmHelper::GetLabelsTemplate(Int_t type, Double_t sizefac, Double_t xref, const Double_t yref, Double_t yoff)
{
  /// Collection of all arrangements and sizes of labels used for plots in this framework.
  /// Used by LmHandler::GenerateLabels() and by pat_sys.h for custom labels.

  TObjArray* oaLabels = new TObjArray();
  oaLabels->SetOwner();

  yoff = yoff * sizefac; // scale automatically so that text separation stays identical when adjusting sizefac.
  TString sFigType = "";
  Double_t yi = yref;

  //
  // yref is const on purpose! use yi in switch statement to change y-starting-position.
  //
  switch (type) {
    case kNone:
      return oaLabels; // this leads to no labels being drawn.
    case kDefault:
      yi = yref;
      sFigType = "ALICE";
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi+0.01,sFigType.Data(),"latFigType" ,sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCollsyst",sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCutsEle" ,sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts2Dim",sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts3Dim",sizefac) );  yi-=yoff;
      break;
    case kPerformance:
      yi = yref;
      sFigType = "ALICE Performance";
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi+0.01,sFigType.Data(),"latFigType" ,sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCollsyst",sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCutsEle" ,sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts2Dim",sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts3Dim",sizefac) );  yi-=yoff;
      break;
    case kPreliminary:
      yi = yref;
      sFigType = "ALICE Preliminary";
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi+0.01,sFigType.Data(),"latFigType" ,sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCollsyst",sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCutsEle" ,sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts2Dim",sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts3Dim",sizefac) );  yi-=yoff;
      break;

    case kPaper:
      yi = yref;
      sFigType = "ALICE";
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi+0.01,sFigType.Data(),"latFigType" ,sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCollsyst",sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCutsEle" ,sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts2Dim",sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts3Dim",sizefac) );  yi-=yoff;
      break;

    case kDefaultNoManager:
      yi = yref;
      sFigType = "ALICE Work in Progress";
      //sFigType = "ALICE Preliminary";
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi+0.01,sFigType.Data(),"latFigType" ,sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts2Dim",sizefac) );  yi-=yoff;
      break;

    case kDefaultOnlyCocktail:
      yi = yref;
      // without any label like "Work in Progress"
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCollsyst",sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCutsEle" ,sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts2Dim",sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts3Dim",sizefac) );  yi-=yoff;
      break;

    case kDefaultCorrel:
      sizefac = 0.7; // hardcoded to avoid problems with fDoRatio in LmHandler::GenerateLabels().
      xref = 0.18;
      yi   = 0.20;
      yoff = 0.05; // the default was independent of sizefac.
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts1Dim",sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts2Dim",sizefac) );  yi-=yoff;
      break;

    case kPatrick1:
      yi = yref;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCollsyst",sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCutsEle" ,sizefac) );  yi-=yoff;
    case kPatrickKine1:
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts2Dim",sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts3Dim",sizefac) );  yi-=yoff;
      break;

    case kPatrickBottomUp1:
    case kPatrickBottomUp2:
      // use negative yoff for these
      yi = yref;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts2Dim",sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCuts1Dim",sizefac) );  yi-=yoff;
      if (type==kPatrickBottomUp1) break;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCutsEle" ,sizefac) );  yi-=yoff;
      oaLabels->Add( LmHelper::BuildTLatex(xref,yi,"","latCollsyst",sizefac) );  yi-=yoff;
      break;

    case kDontUse:
    default:
      break;
  }
  return oaLabels;
}


//_______________________________________________________________________________________________
void LmHelper::SetCanvasWidth(const Double_t width) {
  gStyle->SetCanvasDefW(width);
}
//_______________________________________________________________________________________________
void LmHelper::SetCanvasHeight(const Double_t height) {
  gStyle->SetCanvasDefH(height);
}


//_______________________________________________________________________________________________
void LmHelper::CreatePads(TCanvas* can, Int_t nx, Int_t ny, Double_t bottommargin, Double_t topmargin, Double_t verticalratio)
{
  /// Add pads without any inaccessible space around and between them to an empty canvas.
  /// For more than 2x2 pads, the centered pads will have a larger area for plotting than the outer ones.
  /// But only for identical pad sizes, their axis labels, titles, offsets, ticks, etc. have the same size.
  /// Inspired by TPad::Divide().
  ///
  /// NOTE: Please set margins of outer pads manually if more room is needed for axis labels etc..
  /// Exmple: can->cd(1)->SetTopMargin(ny*gStyle->GetPadTopMargin());
  ///
  /// NOTE: In case of trouble with text sizes, try to draw labels into the canvas instead of its pads.
  ///
  /// @param bottommargin  Configure space for x-axis labels and title.
  /// @param topmargin     Configure empty space above the pads.
  /// @param verticalratio Configure canvas fraction used for upper pad(s) (only for ny==2, e.g. for ratio plots).
  can->Clear();
  if (nx <= 0) nx = 1;
  if (ny <= 0) ny = 1;

  Int_t ix,iy;
  Double_t x1,y1,x2,y2;
  Double_t dx = 1./Double_t(nx);
  Double_t dy = 1./Double_t(ny);
  if (ny==2) dy = verticalratio;
  TPad*    pad = 0x0;
  TString  padname = "";
  Int_t    n = 0;

  for (iy=0;iy<ny;iy++) {
    y2 = 1 - iy*dy;
    y1 = y2 - dy;
    if (y1 < 0) y1 = 0;
    if (y1 > y2) continue;
    for (ix=0;ix<nx;ix++) {
      x1 = ix*dx;
      x2 = x1 +dx;
      if (x1 > x2) continue;
      can->cd();
      n++;
      padname = Form("pad%d",n);
      pad = new TPad(padname.Data(),padname.Data(),x1,y1,x2,y2);
      pad->SetNumber(n); // so it can be called via "can->cd(n);"
      // vertical margins
      if (iy==0)    pad->SetTopMargin(topmargin);
      if (iy>0)     pad->SetTopMargin(0);
      if (iy<ny-1)  pad->SetBottomMargin(0.001); // finite margin between pads for thicker x-axis.
      if (iy==ny-1) pad->SetBottomMargin(bottommargin);
      // horizontal margins
      if (ix==0) {} // keep the value from gStyle.
      if (ix>0)     pad->SetLeftMargin(0);
      if (ix<nx-1)  pad->SetRightMargin(0.001); // margin between pads for thicker y-axis.

      pad->Draw();
    }
  }
}

//_______________________________________________________________________________________________
void LmHelper::CreateManyPads(TCanvas* can, Int_t nx, Int_t ny, Double_t bottommargin, Double_t topmargin, Double_t leftmargin, Double_t rightmargin)
{
  /// Add pads without any inaccessible space around and between them to an empty canvas.
  /// Overcome the issue in CreatePads() for more than 2 horizontal pads by partially overlapping pads of identical size.
  /// NOTE: Not yet done for vertical case. (but 2 rows are ok when bottommargin=topmargin).
  can->Clear();
  if (nx <= 0) nx = 1;
  if (ny <= 0) ny = 1;

  Int_t ix,iy;
  Double_t x1,y1,x2,y2;
  Double_t dx = (1.-(leftmargin+rightmargin)) / Double_t(nx);
  Double_t dy = 1./Double_t(ny);
  Double_t width  = dx+leftmargin; // largest needed width, assuming leftmargin>=rightmargin.
  Double_t height = dy; // height not yet tuned for topmargin!=bottommargin.
  TPad*    pad = 0x0;
  TString  padname = "";
  Int_t    n = nx*ny; // we have to count backwards here.

  for (iy=ny-1;iy>=0;iy--) { // draw bottom row first (for correct numbering). overlapping in y not yet implemented.
    y2 = 1 - iy*dy;
    y1 = y2 - dy;
    if (y1 < 0) y1 = 0;
    if (y1 > y2) continue;
    for (ix=nx-1;ix>=0;ix--) { // draw rightmost pad first, so that they will overlap from right to left.
      x1 = ix*dx;
      x2 = x1 +width; // each pad must have the same width for correct label sizes.
      if (ix==nx-1) { // the rightmost pad must be shifted by the right margin.
        if (nx>1) x1+=rightmargin; // skip special case of one pad in horizontal direction.
        x2+=rightmargin;
      }
      if (x1 > x2) continue;
      if (x2>1.) x2=1.;
      can->cd();
      padname = Form("pad%d",n);
      pad = new TPad(padname.Data(),padname.Data(),x1,y1,x2,y2);
      pad->SetNumber(n); // so it can be called via "can->cd(n);"
      n--;
      //pad->SetFillColor(n+2);
      // vertical margins
      if (iy==0)    pad->SetTopMargin(topmargin/height);
      if (iy>0)     pad->SetTopMargin(0);
      if (iy<ny-1)  pad->SetBottomMargin(0.001); // finite margin between pads for thicker x-axis.
      if (iy==ny-1) pad->SetBottomMargin(bottommargin/height);
      // horizontal margins
      if (ix<nx-1) {
        pad->SetLeftMargin(leftmargin/width); // each pad gets a left margin, but it is hidden by the pad to the left.
        pad->SetRightMargin(0.001); // margin between pads for thicker y-axis.
      }
      if (ix==nx-1) {
        // to preserve identical widths, the rightmost pad needs a smaller left margin because it also has a right margin.
        if (nx>1) pad->SetLeftMargin((leftmargin-rightmargin)/width);
        else      pad->SetLeftMargin(leftmargin/width); // special case of one pad in horizontal direction. avoids inaccessible space.
        pad->SetRightMargin(rightmargin/width);
      }
      pad->Draw();
    }
  }
}


//_______________________________________________________________________________________________
void LmHelper::IntegralAndError(TH2 *h, Double_t &integral, Double_t &error, Double_t Xmin, Double_t Xmax, Double_t Ymin, Double_t Ymax)
{
  if(!h){
    LmHelper::Error("no input histogram given");
    return;
  }
  Int_t ibinXmin = h->GetXaxis()->FindBin(Xmin);
  Int_t ibinXmax = h->GetXaxis()->FindBin(Xmax - LmHelper::kSmallDelta);
  Int_t ibinYmin = h->GetYaxis()->FindBin(Ymin);
  Int_t ibinYmax = h->GetYaxis()->FindBin(Ymax - LmHelper::kSmallDelta);
  Double_t tmp_int(0.),tmp_err(0.);
  for(Int_t ix = ibinXmin; ix <= ibinXmax; ++ix){
    for(Int_t iy = ibinYmin; iy <= ibinYmax; ++iy){
      tmp_int += h->GetBinContent(ix,iy);
      tmp_err += TMath::Power(h->GetBinError(ix,iy),2);
    }
  }
  tmp_err = TMath::Sqrt(tmp_err);
  integral = tmp_int;
  error = tmp_err;
}


//_______________________________________________________________________________________________
Int_t LmHelper::GetNBinsInRange(TH1 *h, Double_t Xmin, Double_t Xmax)
{
  return h->FindBin(Xmax-LmHelper::kSmallDelta) - h->FindBin(Xmin) + 1;
}

//_______________________________________________________________________________________________
void LmHelper::GetBinCentersInRange(TH1 *h, Double_t Xmin, Double_t Xmax, Double_t* binCenters)
{
  /// Useful for constructing a confidence level graph
  Int_t nBins    = GetNBinsInRange(h, Xmin, Xmax);
  Int_t firstBin = h->FindBin(Xmin);
  for (Int_t i=0; i<nBins; ++i) {
    binCenters[i] = h->GetBinCenter(firstBin+i);
  }
}

////_______________________________________________________________________________________________
//void LmHelper::GetBinEdgesInRange(TH1 *h, Double_t Xmin, Double_t Xmax, Double_t* binEdges)
//{
//  /// Useful for constructing another histogram
//  // need to return one more (nBins+1) bin edges
//}

//_______________________________________________________________________________________________
Int_t LmHelper::GetIndex(std::vector<Double_t> v, Int_t type)
{
  /// @TODO: What does this do, Theo? ;-p
  Int_t index;
  switch (type) {
    Double_t tmp,min,max,delta;
    case kMin:
      tmp = 1.e9;
      for(UInt_t i = 0; i < v.size(); ++i){
        if(v.at(i) < tmp){
          tmp = v.at(i);
          index = i;
        }
      }
      break;

    case kMax:
      tmp = -1.e9;
      for(UInt_t i = 0; i < v.size(); ++i){
        if(v.at(i) > tmp){
          tmp = v.at(i);
          index = i;
        }
      }
      break;

    case kMedian:
      max = -1.e9;
      min =  1.e9;
      for(UInt_t i = 0; i < v.size(); ++i){
        if(v.at(i) > max) max = v.at(i);
        if(v.at(i) < min) min = v.at(i);
      }
      delta = 1.e9;
      for(UInt_t i = 0; i < v.size(); ++i){
        Double_t tmp = TMath::Abs(0.5*(max-min) - v.at(i));
        if(tmp < delta) index = i;
      }
      break;

    default:
      index = 0;
      break;
  }
  return index;
}

//_______________________________________________________________________________________________
TH2D* LmHelper::CalcRelativeDifference(TH2D *h1, TH2D *h2, const Char_t *name)
{
  /// Calculate relative difference with respect to h1

  TH2D *hOut = static_cast<TH2D*> (h1->Clone(name));
  hOut->Reset();
  Double_t bc1(0.),bc2(0.);
  for(Int_t ix = 0; ix < hOut->GetNbinsX(); ++ix){
    for(Int_t iy = 0; iy < hOut->GetNbinsY(); ++iy){
      bc1 = h1->GetBinContent(ix,iy);
      bc2 = h2->GetBinContent(ix,iy);
      if(bc1 > kSmallDelta) hOut->SetBinContent(ix,iy,TMath::Abs(bc1-bc2)/bc1);
      else hOut->SetBinContent(ix,iy,0.);
    }
  }
  return hOut;
}

//_______________________________________________________________________________________________
TObjArray* LmHelper::MakeCorrelationGraphs(std::vector<TH1D*> vh1, std::vector<TH1D*> vh2, UInt_t firstbin, UInt_t lastbin, Bool_t correlateErr)
{
  /// Create array of TGraphBentErrors to view correlation between 2 vectors of histograms.
  /// One can specify that only a subrange or just one of all histogram bins are correlated.
  /// The option 'correlateErr' allows to create diagonal error bars instead of separate x- and y-errors.
  /// For plotting it is useful to draw a 2D histogram with desired axis ranges first.
  /// Example:
  ///   std::vector<TH1D*> vProj1 = han_compare->CollectProjections(LmSignal::kSoverB, i, LmBaseSignal::kProjOnMee);
  ///   std::vector<TH1D*> vProj2 = han_compare->CollectProjections(LmSignal::kSignif, i, LmBaseSignal::kProjOnMee);
  ///   TObjArray* oaCorrelGr = LmHelper::MakeCorrelationGraphs(vProj1, vProj2);
  ///   TH2D* haxis = new TH2D("haxis","haxis", 1000,1e-5,1e0, 1000,1e-2,1e5);
  ///   haxis->SetTitle( Form(";%s;%s",vProj1.at(0)->GetYaxis()->GetTitle(),vProj2.at(0)->GetYaxis()->GetTitle()) );
  ///   haxis->DrawCopy();
  ///   oaCorrelGr->DrawClone("pl same");

  TObjArray* objArr = new TObjArray(static_cast<Int_t> (vh1.size()));

  UInt_t size1 = vh1.size();
  UInt_t size2 = vh2.size();
  if (size1 > size2) { // make warning ...
    size1=size2;
  }

  UInt_t nbinsX = vh1.at(0)->GetNbinsX();
  if (firstbin<=lastbin) { nbinsX=lastbin-firstbin+1; }  // use only a subset of all histogram bins.
  else                   { firstbin=1; lastbin=nbinsX; } // use all bins except under-&overflow if no (valid) range is given.

  for (UInt_t histi=0; histi<size1; histi++) {
    TH1D* h1 = (TH1D*) vh1.at(histi);
    TH1D* h2 = (TH1D*) vh2.at(histi);

    TGraphBentErrors* grE = new TGraphBentErrors(nbinsX);
    TGraph* grP = new TGraph(nbinsX);
    // this should be the correct way, but then legend entries also contain x and y axis titles.
    //gr->SetTitle( Form("%s;%s;%s",h1->GetTitle(),h1->GetYaxis()->GetTitle(),h2->GetYaxis()->GetTitle()) );
    grE->SetTitle(h1->GetTitle());
    grE->GetHistogram()->GetXaxis()->SetTitle(h1->GetYaxis()->GetTitle()); // doesnt seem to work
    grE->GetHistogram()->GetYaxis()->SetTitle(h2->GetYaxis()->GetTitle()); // doesnt seem to work
    // store axis titles also in the name:
    grE->SetName( Form("%s;%s;%s",h1->GetTitle(),h1->GetYaxis()->GetTitle(),h2->GetYaxis()->GetTitle()) );

    grE->SetLineColor(h1->GetLineColor());
    grE->SetMarkerColor(h1->GetMarkerColor());
    grE->SetMarkerStyle(0);
    grP->SetMarkerColor(h1->GetMarkerColor());
    grP->SetMarkerStyle(h1->GetMarkerStyle());

    Double_t ex=0, ey=0;
    for (Int_t pointi=0; pointi<(Int_t)nbinsX; pointi++) {
      Int_t bini=pointi+firstbin;
      grE->SetPoint(pointi, h1->GetBinContent(bini), h2->GetBinContent(bini));
      grP->SetPoint(pointi, h1->GetBinContent(bini), h2->GetBinContent(bini));
      ex = h1->GetBinError(bini);
      ey = h2->GetBinError(bini);
      if (correlateErr) {
        // Need only two of the four error bars to make diagonal errors. Lets choose y-low and y-high.
        //gr->SetPointError(pointi, 0, 0, ey, ey, 0, 0, -ex, +ex);
        // Plot all four error bars to get symmetric line ending ticks. Relevant when not using SetMarkerStyle(0).
        grE->SetPointError(pointi, ex, ex, ey, ey, -ey, +ey, -ex, +ex);
      } else {
        grE->SetPointError(pointi, ex, ex, ey, ey);
      }
    } // histogram bins loop

    objArr->Add(grE);
    objArr->Add(grP);

  } // vector hist loop

  return objArr;
}


//_______________________________________________________________________________________________
TH2D* LmHelper::CombineHistograms(TH2D *h1, TH2D *h2, std::string name, Double_t MeeMin, Double_t MeeMax, Double_t PteeMin, Double_t PteeMax)
{
  if(!h1 || !h2) return 0x0;

  TH2D *hOut = static_cast<TH2D*> (h1->Clone(name.data()));
  hOut->Reset();
  for(Int_t ix = 0; ix <= h1->GetNbinsX(); ++ix){
    for(Int_t iy = 0; iy <= h1->GetNbinsY(); ++iy){
      Double_t bc(0.),be(0.);
      if(h1->GetXaxis()->GetBinLowEdge(ix) >  MeeMin - kSmallDelta && h1->GetXaxis()->GetBinUpEdge(ix) <  MeeMax + kSmallDelta &&
         h1->GetYaxis()->GetBinLowEdge(iy) > PteeMin - kSmallDelta && h1->GetYaxis()->GetBinUpEdge(iy) < PteeMax + kSmallDelta){
        bc = h1->GetBinContent(ix,iy);
        be = h1->GetBinError(ix,iy);
      }
      else{
        bc = h2->GetBinContent(ix,iy);
        be = h2->GetBinError(ix,iy);
      }
      hOut->SetBinContent(ix,iy,bc);
      hOut->SetBinError(ix,iy,be);
    }
  }
  return hOut;
}


//_______________________________________________________________________________________________
TH2D* LmHelper::MakeHist2Dfrom1D(std::vector<TH1D*> vhProjX, std::string name, Int_t nBinsY, const Double_t* binsY)
{
  /// Function to create 2D histogram from vector of 1D histograms, which are slices in the second dimension.
  /// Used to create a 2D signal (mee vs ptee) after doing the phiV-correction in slices of ptee. (see pat_sys.h)
  if ((Int_t)vhProjX.size() != nBinsY) {
    LmHelper::Error(Form("LmHelper::MakeHist2Dfrom1D(): number of given projections different from given y bins."));
    return 0x0;
  }
  Int_t           nBinsX = vhProjX.at(0)->GetNbinsX();
  const Double_t* binsX  = vhProjX.at(0)->GetXaxis()->GetXbins()->GetArray();
  //cout << " LmHelper: nBinsX = " << nBinsX << "   binsX = " << binsX[0] << " to " << binsX[nBinsX] << endl;

  TH2D *hOut = new TH2D(name.data(), name.data(), nBinsX, binsX, nBinsY, binsY);

  for (Int_t iy=1; iy<=nBinsY; ++iy) { // loop over projections
    for (Int_t ix=1; ix<=nBinsX; ++ix) {
      hOut->SetBinContent(ix, iy, vhProjX[iy-1]->GetBinContent(ix));
      hOut->SetBinError(  ix, iy, vhProjX[iy-1]->GetBinError(ix));
    }
  }
  return hOut;
}


//_______________________________________________________________________________________________
void LmHelper::FlipAxes2DHistogram(TH2D& hIn){
  /// Flips a 2D histogram along the diagonal axis y=x. Works also for variable-sized bins.
  /// @TODO: This function seems a bit dirty, messing around with pointers and references...
  TString sname(hIn.GetName());  // Otherwise potential memory leak

  //  TCanvas c_hIn("c_hIn","c_hIn");
  //  c_hIn.SetRightMargin(0.2);
  //  hIn.DrawCopy("colz");
  //  c_hIn.Print(Form("c_hIn_%s.pdf",sname.Data()));

  Int_t     nBinsX = hIn.GetNbinsY();
  Double_t  binsX[nBinsX+1];
  Int_t     nBinsY = hIn.GetNbinsX();
  Double_t  binsY[nBinsY+1];
  // fill all bin low edges
  hIn.GetYaxis()->GetLowEdge(binsX);
  hIn.GetXaxis()->GetLowEdge(binsY);
  // fill last bin up edge
  binsX[nBinsX] = hIn.GetYaxis()->GetBinLowEdge(nBinsX + 1);
  binsY[nBinsY] = hIn.GetXaxis()->GetBinLowEdge(nBinsY + 1);

  TH2D* hOut = new TH2D("hOut", hIn.GetTitle(), nBinsX, binsX, nBinsY, binsY);

  hOut->GetXaxis()->SetTitle(hIn.GetYaxis()->GetTitle()); // flip axis titles
  hOut->GetYaxis()->SetTitle(hIn.GetXaxis()->GetTitle()); // flip axis titles
  hOut->GetZaxis()->SetTitle(hIn.GetZaxis()->GetTitle());
  for (int i = 1; i < hOut->GetNbinsX()+1; ++i){
    for (int j = 1; j < hOut->GetNbinsY()+1; ++j){
      hOut->SetBinContent(i, j, hIn.GetBinContent(j, i));
      hOut->SetBinError(i, j, hIn.GetBinError(j, i));
    }
  }

  hIn = *hOut;
  hIn.SetName(sname.Data());
  delete hOut;

  // TCanvas c_hFlipped("c_hFlipped","c_hFlipped");
  // c_hFlipped.SetRightMargin(0.2);
  // hIn.DrawCopy("colz");
  // c_hFlipped.Print(Form("c_hFlipped_%s.pdf",sname.Data()));

  return;
}


//_______________________________________________________________________________________________
TFile* LmHelper::SafelyOpenRootfile(const std::string filename)
{
  /// Opens a rootfile without affecting the active path, which otherwise would point into the file, often causing trouble.
  //save current path before opening rootfile.
  TString sPath = gDirectory->GetPath();

  TFile* ffile = 0x0;
  // check if file is already open.
  if ( gROOT->GetListOfFiles()->FindObject(filename.data()) ) {
    ffile = gROOT->GetFile(filename.data()); // avoid to open same file twice
  }
  if (ffile && ffile->IsOpen()) return ffile;

  ffile = TFile::Open(filename.data()); // gives root error and returns 0x0 on fail.
  //ffile = new TFile(filename.data()); // gives root error on fail.
  //ffile->OpenFile(filename.data());   // gives no error on fail.
  if (!ffile) LmHelper::Error(Form("LmHelper::SafelyOpenRootfile(): file '%s' not found.", filename.data()));

  // change to previous path again, so that it will be possible to close the file later without crash.
  // otherwise heap based objects will be created in memory that will be freed when the file is closed.
  gDirectory->Cd(sPath.Data());

  // alternatively one can do hist->SetDirectory(0); // according to Dario (Analysis Tutorial 26.06.2015)
  // but this seems not to work if the class object (which owns the hist) was created in the file path.

  return ffile;
}


//_______________________________________________________________________________________________
TList* LmHelper::GetList(TFile* fileIn, TString listname)
{
  /// Note: List has to be deleted later only in the first case... Use LmHelper::DeleteList(list).
  if (!fileIn || !fileIn->IsOpen()) { LmHelper::Error("LmHelper::GetList(): file not open."); return 0x0; }
  TList* llist=0x0;

  if (listname.Length()==0 || listname.EqualTo(".")) {
    //if (debug>2) cout << " creating list from list of keys in file " << endl;
    llist = new TList();
    llist->SetName("ListCreatedFromFileBaseDirectory");
    TIter nextKey(fileIn->GetListOfKeys());
    TObject* key=0x0;
    while ((key=nextKey())) llist->Add(fileIn->Get( key->GetName() ));
  }
  else {
    listname.Remove(TString::kLeading, '.'); // Catch case when list was specified as "./list".
    TObjArray* oaListPath = listname.Tokenize("/");
    //if (debug>2) cout << " getting list: " << oaListPath->At(0)->GetName() << endl;
    TObject* object = 0x0;
    object = (TObject*) fileIn->Get(oaListPath->At(0)->GetName());

    if (object->IsA() == TDirectoryFile::Class()){ // This is used in Oton-style Cocktail
      TDirectoryFile* dir = (TDirectoryFile*) object;
      if (dir) dir->SetName(oaListPath->At(0)->GetName());
      else { LmHelper::Error(Form("LmHelper::GetList(): TDirectoryFile '%s' not found in file '%s'.", oaListPath->At(0)->GetName(), fileIn->GetName())); return 0x0; }
      for (Int_t i=1; i<oaListPath->GetEntries(); i++) {
        TList* templist = (TList*) dir->Get(oaListPath->At(i)->GetName());
        if (templist) {
          llist = templist;
          llist->SetName(oaListPath->At(i)->GetName());
        }
        else LmHelper::Warning(Form("LmHelper::GetList(): specified sublist '%s' not found in file '%s'.", oaListPath->At(i)->GetName(), fileIn->GetName()));
      }

    }
    else if (object->IsA() == TList::Class()){
      llist = (TList*) object;
      if (llist) llist->SetName(oaListPath->At(0)->GetName()); // Otherwise the listname would in most cases be "TList".
      else { LmHelper::Error(Form("LmHelper::GetList(): list '%s' not found in file '%s'.", oaListPath->At(0)->GetName(), fileIn->GetName())); return 0x0; }
      // loop to find sublists if specified.
      for (Int_t i=1; i<oaListPath->GetEntries(); i++) {
        //if (debug>2) cout << "  getting list: " << oaListPath->At(i)->GetName() << endl;
        TList* templist = (TList*) llist->FindObject(oaListPath->At(i)->GetName());
        if (templist) {
          llist = templist;
          llist->SetName(oaListPath->At(i)->GetName());
        }
        else LmHelper::Warning(Form("LmHelper::GetList(): specified sublist '%s' not found in file '%s'.", oaListPath->At(i)->GetName(), fileIn->GetName()));
      }
    }
    else {
      LmHelper::Error("sublist is neither TList nor TDirectoryFile");
      return 0x0;
    }
  }
  //if (debug>2) { cout << " list contains: " << endl; llist->Print(); }
  return llist;
}

//_______________________________________________________________________________________________
TList* LmHelper::SelectHistosList(TList* histlist, TString histnames, Bool_t bExact, TString delimiter)
{
  /// Function to select desired histograms from a list and return them in a new list.
  /// All histogram names/patterns to seach for are given via 'histnames', delimited by the character 'delimiter'.
  /// A leading or trailing '*' in patterns inside 'histnames' is treated as wildcard and overwrites the 'bExact' behaviour.
  /// This could be solved more elegantly, but would need changes in other macros, from using bExact=kFALSE to including '*'s...
  /// Note: List has to be deleted later. Use LmHelper::DeleteList(list).
  TList* lHist = new TList();
  lHist->SetName( Form("%s_out",histlist->GetName()) );
  //lHist->SetOwner(); // probably only ok if we copy the histograms.
  TObjArray* oaNames = histnames.Tokenize(delimiter.Data());
  //if (oaNames->GetEntries()==0) oaNames->Add(new TObjString("")); // with this, "" could be used instead of "all".
  for(Int_t i=0; i<histlist->GetEntries(); i++) {
    if (! histlist->At(i)->InheritsFrom(TH1::Class()) ) continue;
    //if (debug>3) cout << " histlist->At(i)->GetName() = " << histlist->At(i)->GetName() << endl;
    for (Int_t namei=0; namei<oaNames->GetEntries(); namei++) {
      //if (debug>3) cout << " oaNames->At(namei)->GetName() = " << oaNames->At(namei)->GetName() << endl;
      TString sNamei = oaNames->At(namei)->GetName();
      Bool_t thisExact=bExact; // the decision is made for each pattern individually.
      if (sNamei.BeginsWith("*")) { sNamei.Remove(TString::kLeading,  '*'); thisExact=kFALSE; }
      if (sNamei.EndsWith("*"))   { sNamei.Remove(TString::kTrailing, '*'); thisExact=kFALSE; }
      //if (debug>3) cout << " sNamei.Data() = " << sNamei.Data() << endl;
      if (   ( sNamei.EqualTo("all") ) // there must be a bug in root: if this check is done last, then the outcome is wrong for i>3 if bExact=kTRUE.
          || ( thisExact  && TString(histlist->At(i)->GetName()).EqualTo (sNamei) )
          || ( !thisExact && TString(histlist->At(i)->GetName()).Contains(sNamei) )
          ) {
        //if (debug>3) cout << " adding histogram: " << histlist->At(i)->GetName() << " , based on requested: " << oaNames->At(namei)->GetName() << endl;
        lHist->Add(histlist->At(i));
        break; // Go on with next histogram. Otherwise the same histogram may be added more than once (e.g. due to Eta:EtaPrime when bExact=kFALSE).
      }
    }
  }
  if (lHist->GetEntries()<1) LmHelper::Warning(Form("LmHelper::SelectHistosList(): no histograms in list '%s' match requested names '%s'.", histlist->GetName(), histnames.Data()));
  return lHist;
}

//_______________________________________________________________________________________________
void LmHelper::DeleteList(TList* list)
{
  /// Collect recipes how to delete/clear the lists which were created or just fetched by other LmHelper functions.
  if (!list) return;
  TString listname = list->GetName();
  if (   listname.EqualTo("ListCreatedFromFileBaseDirectory")
      || listname.EndsWith("_out") )
  { // If the list was created at runtime, we need to take care of its deletion.
    delete list; // @TODO: cross-check if this is the correct call.
    list = 0x0;
    return;
  }
  list = 0x0; // If the list belongs to a file, it should be enough to reset the pointer. The list itself is handled by the file.
}

//_______________________________________________________________________________________________
TH1* LmHelper::GetHistFromTemplateFile(TFile* fileIn, Int_t ikey, TString histname, Bool_t normNevents)
{
  /// Retrieve histogram from a file that was written via LmHandler::Write1DHist/Write2DHist/Write3DHist().
  /// NOTE: This works for any file which has TDirectories stored in its base path (set normNevents=kFALSE).
  ///
  /// @param ikey Get histogram from the i-th directory in the file, i.e. from LmSignal #i (starts at 0).
  /// @param normNevents Normalize the histogram to one event. Corrections in LmManager assume normalized hists.
  TH1* hOut=0x0;
  TList*      keys = fileIn->GetListOfKeys();
  TDirectory* dir  = fileIn->GetDirectory(keys->At(ikey)->GetName());
  // @TODO: Not clear to me, why marker style, color, etc is lost here. In the TBrowser it is visible...
  //dir->Get(histname.Data())->Dump();
  hOut    = (TH1*) dir->Get(histname.Data());
  if (normNevents) {
    Double_t nevents = GetNeventsFromTemplateDir(dir);
    //cout << " nevents = " << nevents << endl;
    hOut->Scale(1./nevents);
  }
  return hOut;
}

//_______________________________________________________________________________________________
Double_t LmHelper::GetNeventsFromTemplateDir(TDirectory* dir)
{
  /// Taken from LmSignal::InitFromRootfile().
  TList* keys = dir->GetListOfKeys();
  TString sValue;
  //Double_t valmin, valmax;
  for (Int_t i=0; i<keys->GetEntries(); ++i)
  {
    TString keyname = keys->At(i)->GetName();
    //
    // Put checks with more complex names before the simpler ones!
    // Otherwise the 'Contains()' logic will give wrong results.
    //
    if (keyname.Contains("Number of events: ", TString::kIgnoreCase)) {
      sValue = keyname(keyname.First(':')+2,100);
      return atof(sValue.Data());
    }
  }
  return 0;
}


//_______________________________________________________________________________________________
void LmHelper::SetEmptyBinnings(std::vector<std::vector<Double_t>*> &vBinnings, UInt_t nvectors)
{
  //Printf("SetEmptyBinnings()");
  vBinnings.resize(nvectors);
  for (UInt_t i=0; i<vBinnings.size(); i++) {
    vBinnings.at(i)=0x0;
  }
}
