#ifndef LMFITFUNCTIONS_H
#define LMFITFUNCTIONS_H

// c++ includes
// ROOT includes
#include "TH1.h"
// project includes

class LmFitFunctions {
public:
  LmFitFunctions();
  //~LmFitFunctions();
  
  // functions for construction of TF1 class objects
  Double_t      FcnOneTemplate(Double_t *x, Double_t *par);
  Double_t      FcnTwoTemplates(Double_t *x, Double_t *par);
  Double_t      FcnTwoTempl_OneNorm(Double_t *x, Double_t *par);
  Double_t      FcnThreeTemplates(Double_t *x, Double_t *par);
  Double_t      FcnThreeTempl_OneNorm_PlusBaseline(Double_t *x, Double_t *par);
  // other functions
  Int_t         CalcNBinsInFitRange(Double_t xmin, Double_t xmax);
  
  // setters
  void          SetTemplateA(TH1D* h)         { fFitTemplateA = h; }
  void          SetTemplateB(TH1D* h)         { fFitTemplateB = h; }
  void          SetTemplateC(TH1D* h)         { fFitTemplateC = h; }
  void          SetDoSomething(bool b=kTRUE)  { fDoSomething = b; }
  
  // getters
  TH1D*         GetTemplateA() const    { return fFitTemplateA; }
  TH1D*         GetTemplateB() const    { return fFitTemplateB; }
  TH1D*         GetTemplateC() const    { return fFitTemplateC; }
  Bool_t        GetDoSomething() const  { return fDoSomething; }
  
private:
  // variables
  TH1D*         fFitTemplateA; // just store the pointers. the object itself belongs to the external class.
  TH1D*         fFitTemplateB;
  TH1D*         fFitTemplateC;
  Bool_t        fDoSomething;
  
};

#endif
