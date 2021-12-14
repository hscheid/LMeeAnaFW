#include <iostream>
#include <vector>
#include <map>

#include "TDirectoryFile.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"

std::map<TString,Double_t> relErrBR;

std::vector<TH2D>* GetHistograms(TString cocktailfile);
std::vector<TH2D>* CombineErr(std::vector<TH2D> *vStd, std::vector<TH2D> *vErr, Bool_t bHigh);
std::vector<TH2D>* ContractVector(std::vector<TH2D> *v);
void WriteFileAndList(TString fileName, std::vector<TH2D> *v);
//void PlotCocktail(std::vector<TH2D> *v, std::vector<TH2D> *vLow, std::vector<TH2D> *vHigh, std::vector<TH2D> *vBRlow, std::vector<TH2D> *vBRhigh, TString fileName, TString listName, Bool_t simpleJpsi=kFALSE);
//void SetHistoProp(TH1D *h, Int_t color, Int_t lStyle);

//_______________________________________________________________________________________________
Bool_t bMtScaling=kTRUE;
Bool_t bpPb=kTRUE;
Double_t cpp=0.852;
//void ProcessRawCocktail(TString fCocktail= "LFcocktail_low_75MeV_v2.root")
void ProcessRawCocktail(TString fCocktail= "LFcocktail_Jerome_75MeV_low_0404_v1.root")
{
  gStyle->SetOptStat(0);
  TH2::AddDirectory(kFALSE);
  
  relErrBR.insert( std::pair<TString,Double_t>("MeePteePion2eeGamma"    ,2.98126064735945474e-02) );
  relErrBR.insert( std::pair<TString,Double_t>("MeePteeEta2eeGamma"     ,5.79710144927536239e-02) );
  relErrBR.insert( std::pair<TString,Double_t>("MeePteeEtaPrime2eeGamma",6.38297872340425620e-02) );
  relErrBR.insert( std::pair<TString,Double_t>("MeePteeEtaPrime2eeOmega",2.00000000000000011e-01) );
  relErrBR.insert( std::pair<TString,Double_t>("MeePteeRho2ee"          ,1.05932203389830504e-02) );
  relErrBR.insert( std::pair<TString,Double_t>("MeePteeOmega2ee"        ,1.92307692307692318e-02) );
  relErrBR.insert( std::pair<TString,Double_t>("MeePteeOmega2eePion"    ,7.79220779220779342e-02) );
  relErrBR.insert( std::pair<TString,Double_t>("MeePteePhi2ee"          ,1.01557210561949891e-02) );
  relErrBR.insert( std::pair<TString,Double_t>("MeePteePhi2eePion"      ,2.50000000000000000e-01) );
  relErrBR.insert( std::pair<TString,Double_t>("MeePteePhi2eeEta"       ,3.70370370370370350e-02) );
  
  std::vector<TH2D> *vStd = GetHistograms(fCocktail);
  if(!vStd) return;
  for(UInt_t i =0 ; i < vStd->size(); ++i) std::cout << vStd->at(i).GetName() << std::endl;
  
  std::vector<TH2D> *vStdOut = ContractVector(vStd);
  
  WriteFileAndList(fCocktail,vStdOut);
  
}
//_______________________________________________________________________________________________
std::vector<TH2D>* ContractVector(std::vector<TH2D> *v)
{
  std::vector<TH2D> *vNew = new std::vector<TH2D> ();

  Bool_t bPionFirst(kTRUE);
  Bool_t bEtaFirst(kTRUE);
  Bool_t bEtaPrimeFirst(kTRUE);
  Bool_t bRhoFirst(kTRUE);
  Bool_t bOmegaFirst(kTRUE);
  Bool_t bPhiFirst(kTRUE);
  for(UInt_t i = 0; i < v->size(); ++i){
    TString name(v->at(i).GetName());
    printf("Process %s\n",name.Data());
    if(name.Contains("Pi0")){
      if(bPionFirst){
	printf("First pi0\n");
        vNew->push_back(TH2D(v->at(i)));
        vNew->at(vNew->size()-1).SetName("MeePteePion");
      }
      else {
	printf("Add pi0\n");
	vNew->at(vNew->size()-1).Add(&(v->at(i)));
      }
      bPionFirst = kFALSE;  
    }
    if(name.Contains("Eta") && (!name.Contains("EtaP"))){
      if(bEtaFirst){
	printf("First eta\n");
        vNew->push_back(TH2D(v->at(i)));
        vNew->at(vNew->size()-1).SetName("MeePteeEta");
      }
      else {
	printf("Add Eta\n");
	vNew->at(vNew->size()-1).Add(&(v->at(i)));
      }
      bEtaFirst = kFALSE;  
    }
    //   if(name.Contains("EtaP") && name != "MeePteeEtaPrime2eeOmega"){
    if(name.Contains("EtaP")){
      if(bEtaPrimeFirst){
	printf("First EtaP \n");
        vNew->push_back(TH2D(v->at(i)));
        vNew->at(vNew->size()-1).SetName("MeePteeEtaPrime");
      }
      else {
	printf("Add Etap\n");
	vNew->at(vNew->size()-1).Add(&(v->at(i)));
      }
      bEtaPrimeFirst = kFALSE;  
    }
    if(name.Contains("Rho")){
      if(bRhoFirst){ 
	printf("First Rho\n");
	vNew->push_back(TH2D(v->at(i)));
        vNew->at(vNew->size()-1).SetName("MeePteeRho");
      }
      else {
	printf("Add rho\n");
	vNew->at(vNew->size()-1).Add(&(v->at(i)));
      }
      bRhoFirst = kFALSE;  
    }
    if(name.Contains("Omega")){
      if(bOmegaFirst){
	printf("First Omega\n");
        vNew->push_back(TH2D(v->at(i)));
        vNew->at(vNew->size()-1).SetName("MeePteeOmega");
      }
      else {
	printf("Add Omega\n");
	vNew->at(vNew->size()-1).Add(&(v->at(i)));
      }
      bOmegaFirst = kFALSE;  
    }
    //    if(name.Contains("MeePteePhi") && name != "MeePteePhi2eePion"){
    if(name.Contains("Phi")){
      if(bPhiFirst){
	printf("First phi\n");
        vNew->push_back(TH2D(v->at(i)));
        vNew->at(vNew->size()-1).SetName("MeePteePhi");
      }
      else {
	printf("Add phi\n");
	vNew->at(vNew->size()-1).Add(&(v->at(i)));
      }
      bPhiFirst = kFALSE;  
    }
  }
  return vNew;
}
//_______________________________________________________________________________________________
std::vector<TH2D>* CombineErr(std::vector<TH2D> *vStd, std::vector<TH2D> *vErr, Bool_t bHigh)
{
  if(!vStd) return 0x0;
  std::vector<TH2D> *v = new std::vector<TH2D> ();
  TH2D hSum(vStd->at(0));
  hSum.Reset();
  hSum.SetName("MeePteeSum");
  for(UInt_t i=0 ; i < vStd->size(); ++i){
    v->push_back(TH2D(vStd->at(i)));
    hSum.Add(&(vStd->at(i)));
  }
  if(!vErr || (vErr->size() != vStd->size())){
    for(Int_t ix = 0; ix <= hSum.GetNbinsX()+1; ++ix){
      for(Int_t iy = 0; iy <= hSum.GetNbinsY()+1; ++iy){
        Double_t sumBC = hSum.GetBinContent(ix,iy);
        Double_t sumErr(0.);
        for(UInt_t i=0 ; i < vStd->size(); ++i){
          Double_t BRErr = vStd->at(i).GetBinContent(ix,iy) * relErrBR.at(vStd->at(i).GetName());
          sumErr += TMath::Power(BRErr,2);
        }
        sumErr = TMath::Sqrt(sumErr);
        for(UInt_t i=0 ; i < v->size(); ++i){
          Double_t partBC = v->at(i).GetBinContent(ix,iy);
          if(sumBC > 0.){
            if(bHigh) partBC = partBC + (partBC / sumBC) * sumErr;
            else      partBC = partBC - (partBC / sumBC) * sumErr;
          }
          v->at(i).SetBinContent(ix,iy,partBC);
        }
      }
    }
    return v;
  }
  else{
    for(Int_t ix = 0; ix <= hSum.GetNbinsX()+1; ++ix){
      for(Int_t iy = 0; iy <= hSum.GetNbinsY()+1; ++iy){
        Double_t sumBC = hSum.GetBinContent(ix,iy);
        Double_t sumErr(0.);
        for(UInt_t i=0 ; i < vStd->size(); ++i){
          Double_t BRErr = vStd->at(i).GetBinContent(ix,iy) * relErrBR.at(vStd->at(i).GetName());
          Double_t ParamErr = vStd->at(i).GetBinContent(ix,iy) - vErr->at(i).GetBinContent(ix,iy);
          sumErr += TMath::Power(BRErr,2) + TMath::Power(ParamErr,2);
        }
        sumErr = TMath::Sqrt(sumErr);
        for(UInt_t i=0 ; i < v->size(); ++i){
          Double_t partBC = v->at(i).GetBinContent(ix,iy);
          if(sumBC > 0.){
            if(bHigh) partBC = partBC + (partBC / sumBC) * sumErr;
            else      partBC = partBC - (partBC / sumBC) * sumErr;
          }
          v->at(i).SetBinContent(ix,iy,partBC);
        }
      }
    }
    return v;
  }

}
//_______________________________________________________________________________________________
std::vector<TH2D>* GetHistograms(TString cocktailfile)
{
  TFile *f = new TFile(Form("./input/%s",cocktailfile.Data()),"READ");
  if(!(f->IsOpen())) return 0x0;
  printf("Found file\n");
  TDirectoryFile *ll = static_cast<TDirectoryFile*> (f->Get("LMeeCocktailMC"));
  if(!ll) return 0x0;
  printf("Found first list\n");
  TList *l = static_cast<TList*> (ll->Get("LMeeCocktailMC_0.80"));
  if(!l) return 0x0;
  printf("Found second list\n");
  TH1D *hStats = static_cast<TH1D*> (l->FindObject("NEvents"));
  if(!hStats) return 0x0;
  printf("Found histo stats\n");
  Double_t nev = hStats->GetBinContent(1);
  
  std::vector<TH2D> *v = new std::vector<TH2D> ();
  v->push_back(TH2D(*(static_cast<TH2D*> (l->FindObject("pteevsmee_Pi0")))));
  v->push_back(TH2D(*(static_cast<TH2D*> (l->FindObject("pteevsmee_Eta")))));
  v->push_back(TH2D(*(static_cast<TH2D*> (l->FindObject("pteevsmee_EtaP_dalitz_photon")))));
  v->push_back(TH2D(*(static_cast<TH2D*> (l->FindObject("pteevsmee_EtaP_dalitz_omega")))));
  v->push_back(TH2D(*(static_cast<TH2D*> (l->FindObject("pteevsmee_Rho")))));
  v->push_back(TH2D(*(static_cast<TH2D*> (l->FindObject("pteevsmee_Omega_2body")))));
  v->push_back(TH2D(*(static_cast<TH2D*> (l->FindObject("pteevsmee_Omega_dalitz")))));
  v->push_back(TH2D(*(static_cast<TH2D*> (l->FindObject("pteevsmee_Phi_2body")))));
  v->push_back(TH2D(*(static_cast<TH2D*> (l->FindObject("pteevsmee_Phi_dalitz_pi0")))));
  v->push_back(TH2D(*(static_cast<TH2D*> (l->FindObject("pteevsmee_Phi_dalitz_eta")))));
  

  for(UInt_t i = 0; i < v->size(); ++i)
    v->at(i).Scale(1./nev);
  
  f->Close();
  delete f;

  return v;
}
//_______________________________________________________________________________________________
void WriteFileAndList(TString fileName,std::vector<TH2D> *v)
{
  if(!v) return;
  TFile fOut(Form("./output/%s",fileName.Data()),"UPDATE");
  fOut.cd();
  TList *l = new TList();
  l->SetName("cocktailPt75rec");
  for(UInt_t i = 0; i < v->size(); ++i)
    l->Add(&(v->at(i)));
  fOut.cd();
  l->Write(l->GetName(),TObject::kSingleKey);
  fOut.Close();
  delete l;
  
  fileName.ReplaceAll(".root","1D.root");
  TFile fOut1D(Form("./output/1D/%s",fileName.Data()),"UPDATE");
  fOut1D.cd();
  l = new TList();
  l->SetName("cocktailPt75rec");
  for(UInt_t i = 0; i < v->size(); ++i){
    TString hname(v->at(i).GetName());
    hname.ReplaceAll("MeePtee","Mee");
    TH1D *h = static_cast<TH1D*> (v->at(i).ProjectionX(hname,1,v->at(i).GetNbinsY()));
    l->Add(h);
  }
  for(UInt_t i = 0; i < v->size(); ++i){
    TString hname(v->at(i).GetName());
    hname.ReplaceAll("MeePtee","Ptee");
    TH1D *h = static_cast<TH1D*> (v->at(i).ProjectionY(hname,1,v->at(i).GetNbinsX()));
    l->Add(h);
  }
  fOut1D.cd();
  l->Write(l->GetName(),TObject::kSingleKey);
  fOut1D.Close();
  delete l;
}
