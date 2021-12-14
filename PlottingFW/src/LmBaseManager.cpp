// c++ includes

// ROOT includes
#include "TH2.h"
#include "TCanvas.h"
#include "TStyle.h"
// project includes
#include "LmBaseManager.h"
#include "LmHelper.h"


//_______________________________________________________________________________________________
LmBaseManager::LmBaseManager() :
fName(""),
fsInputfiles(""),
fsInputlists("."), // Need something for tokenizing. Using "." is correctly treated by LmHelper::GetList().
fsInputhists(""),
fNdimInput(0),
fPlotZMin(-1.),
fPlotZMax(-1.)
{
  /// Default constructor for LmBaseManager
}

//_______________________________________________________________________________________________
LmBaseManager::LmBaseManager(const LmBaseManager& man) :
fName(man.fName),
fsInputfiles(""),
fsInputlists(man.fsInputlists),
fsInputhists(man.fsInputhists),
fNdimInput(man.fNdimInput),
fPlotZMin(man.fPlotZMin),
fPlotZMax(man.fPlotZMax)
{
  /// Copy constructor for LmBaseManager
  /// does not copy all information, since it is not expected to read in the same rootfiles again.
}

//_______________________________________________________________________________________________
void LmBaseManager::PrintTH2(TH2D* hIn, const Char_t* filename)
{
  TCanvas* c1 = new TCanvas("c1", "c1");
  c1->cd();
  LmHelper::TH2_Beautify(hIn, c1);
  //if (fPlotZMax > fPlotZMin) { hIn->SetAxisRange(fPlotZMin, fPlotZMax, "Z"); }
  //else                       { hIn->GetZaxis()->UnZoom(); } // to reset the plot range after calling ResetPlotRangeZ().
  hIn->GetZaxis()->UnZoom(); 
  gStyle->SetOptTitle(1); // for debugging
  hIn->DrawCopy("colz");
  c1->Print(filename);
  gStyle->SetOptTitle(0);
  delete c1;
  return;
}

//_______________________________________________________________________________________________
void LmBaseManager::SetInputfiles(const char* files)
{
  fsInputfiles = files;
}

//_______________________________________________________________________________________________
void LmBaseManager::SetInputlists(const char* lists)
{
  fsInputlists = lists;
  if (fsInputlists.IsNull()) fsInputlists="."; // Need something for tokenizing. Using "." is correctly treated by LmHelper::GetList().
}

//_______________________________________________________________________________________________
void LmBaseManager::SetInputhistAndDim(const char* histnames, UInt_t dim)
{
  fsInputhists = histnames;
  fNdimInput   = dim;
  InitProjectionRanges();
}
