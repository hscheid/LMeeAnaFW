#ifndef LMMULTIQA_H
#define LMMULTIQA_H

#include "TString.h"
#include "TCollection.h"
#include "TH1D.h"
#include "LmHelper.h"
#include "LmQA.h"
// forward declarations
class TCollection;
class TFile;
class TH1D;
class TCanvas;

class LmMultiQA : public LmQA {
public:
//  LmMultiQA();
//  void SetData(LmQA &data) {fData = &data;};
//  void SetMC(LmQA &mc)     {fMC = &mc;};
  LmMultiQA(LmQA &data, LmQA &mc);
  ~LmMultiQA();

private:
  LmQA*         fData;
  LmQA*         fMC;
  
  void PrintTrackingPrivate(TString filename, TString observable, int type);

};

#endif // LMMULTIQA_H