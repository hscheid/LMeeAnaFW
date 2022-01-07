// c++ includes
// ROOT includes
// project includes
#include "LmFitFunctions.h"

//_______________________________________________________________________________________________
LmFitFunctions::LmFitFunctions() :
fFitTemplateA(0x0),
fFitTemplateB(0x0),
fFitTemplateC(0x0),
fDoSomething(kFALSE)
{
  /// Default constructor
}

//_______________________________________________________________________________________________
Double_t LmFitFunctions::FcnOneTemplate(Double_t *x, Double_t *par)
{
  Double_t binA = fFitTemplateA->GetXaxis()->FindBin(x[0]);
  return fFitTemplateA->GetBinContent(binA)*par[0];
}

//_______________________________________________________________________________________________
Double_t LmFitFunctions::FcnTwoTemplates(Double_t *x, Double_t *par)
{
  // get bins independently to allow differently binned template histograms.
  Double_t binA = fFitTemplateA->GetXaxis()->FindBin(x[0]);
  Double_t binB = fFitTemplateB->GetXaxis()->FindBin(x[0]);
  
  Double_t val  = par[0]*fFitTemplateA->GetBinContent(binA);
  val          += par[1]*fFitTemplateB->GetBinContent(binB);
  return val;
}
//
//_______________________________________________________________________________________________
Double_t LmFitFunctions::FcnThreeTemplates(Double_t *x, Double_t *par)
{
  // get bins independently to allow differently binned template histograms.
  Double_t binA = fFitTemplateA->GetXaxis()->FindBin(x[0]);
  Double_t binB = fFitTemplateB->GetXaxis()->FindBin(x[0]);
  Double_t binC = fFitTemplateC->GetXaxis()->FindBin(x[0]);
  
  Double_t val  = par[0]*fFitTemplateA->GetBinContent(binA);
  val          += par[1]*fFitTemplateB->GetBinContent(binB);
  val          += par[2]*fFitTemplateC->GetBinContent(binC);
  return val;
}

//_______________________________________________________________________________________________
Double_t LmFitFunctions::FcnTwoTempl_OneNorm(Double_t *x, Double_t *par)
{
  /// See documentation for usage in FcnThreeTempl_OneNorm_PlusBaseline().
  // get bins independently to allow differently binned template histograms.
  Double_t binA = fFitTemplateA->GetXaxis()->FindBin(x[0]);
  Double_t binB = fFitTemplateB->GetXaxis()->FindBin(x[0]);
  
  Double_t val  = (1.-par[0])*par[1]*fFitTemplateA->GetBinContent(binA);
  val          +=  par[0]    *par[1]*fFitTemplateB->GetBinContent(binB);
  return val;
}

//_______________________________________________________________________________________________
Double_t LmFitFunctions::FcnThreeTempl_OneNorm_PlusBaseline(Double_t *x, Double_t *par)
{
  /// Function to fit, for example, low-mass resonances (as TemplateA) + virtual photons (as TemplateB) with
  /// a single normalization factor to extract the photon fraction r, while taking into account a constant
  /// contribution from the open-heavy-flavour decays (as TemplateC, should fix par[2]=1.).
  /// For initial normalization to the data, fix par[0] to 0.5 and determine par[1], by fitting at very low mass.
  /// Afterwards, fix par[1] to 2.*par[1] or to 2. if the spectra were already scaled by par[1] (may happen internally for drawing).
  /// Then par[0] will be the virtual photon fraction, determined in a given fit range.
  
  // get bins independently to allow differently binned template histograms.
  Double_t binA = fFitTemplateA->GetXaxis()->FindBin(x[0]);
  Double_t binB = fFitTemplateB->GetXaxis()->FindBin(x[0]);
  Double_t binC = fFitTemplateC->GetXaxis()->FindBin(x[0]);
  
  Double_t val  = (1.-par[0])*par[1]*fFitTemplateA->GetBinContent(binA);
  val          +=  par[0]    *par[1]*fFitTemplateB->GetBinContent(binB);
  val          +=  par[2]           *fFitTemplateC->GetBinContent(binC);
  return val;
}
