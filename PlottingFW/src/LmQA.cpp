// c++ includes

// ROOT includes
#include "TObjArray.h"
#include "TFile.h"
#include "TCollection.h"
#include "TLine.h"
#include "TLegend.h"
#include "TSystem.h"
// project includes
#include "LmQA.h"
#include "LmHelper.h"

//_______________________________________________________________________________________________
LmQA::LmQA() : fInputfile(0x0),
               fCutfolder(0x0),
               fsConfiglong(""),
               fName(""),
               feta_range_min(-1),
               feta_range_max(-1),
               fpt_range_min(-1),
               fpt_range_max(-1),
               fcentrality_min(-1),
               fcentrality_max(-1),
               fcoll_system(""),
               fcoll_energy(""),
               fColorPalette(-1),
               fDoRatio(kTRUE),
               fDoNormNEvents(kFALSE),
               fDoNormNEntries(kFALSE),
               fRatioPadSize(0.3),
               fRebin(-1),
               fNEvents(-1)
{
  // default constructor
  // Need to set fsConfig and load histograms
}
//_______________________________________________________________________________________________
LmQA::LmQA(TString cconfig) : fInputfile(0x0),
                            fCutfolder(0x0),
                            fsConfiglong(cconfig),
                            fName(""),
                            feta_range_min(-1),
                            feta_range_max(-1),
                            fpt_range_min(-1),
                            fpt_range_max(-1),
                            fcentrality_min(-1),
                            fcentrality_max(-1),
                            fcoll_system(""),
                            fcoll_energy(""),
                            fColorPalette(-1),
                            fDoRatio(kTRUE),
                            fDoNormNEvents(kFALSE),
                            fDoNormNEntries(kFALSE),
                            fRatioPadSize(0.3),
                            fRebin(-1),
                            fNEvents(-1)
{
  if (fsConfiglong.IsNull()) return;
  LoadHistograms();

  TObjArray* oaConfig = fsConfiglong.Tokenize(":");
  // set name if given in cconfig.
  if (oaConfig->GetEntriesFast()>=5) SetName(oaConfig->At(4)->GetName());
}

//_______________________________________________________________________________________________
LmQA::~LmQA(){
  delete fInputfile;
  delete fCutfolder;
};

//_______________________________________________________________________________________________
int LmQA::LoadHistograms(){
  TObjArray* oaConfig = fsConfiglong.Tokenize(";:");

  fcoll_system = oaConfig->At(0)->GetName();
  TObjArray* oaColl_system = fcoll_system.Tokenize(",");
  if (oaColl_system->GetEntriesFast()>1) {
    fcoll_system = oaColl_system->At(0)->GetName();
    fcoll_energy = oaColl_system->At(1)->GetName();
    fcoll_energy.Remove(TString::kLeading, ' ');
  }
  LmHelper::Debug(Form(" coll_system = %s, coll_energy = %s", fcoll_system.Data(), fcoll_energy.Data()), 2);

  // updated to handle also rootfiles which were opened by previous manager
  if (fInputfile==0x0) {
  //if (!(fInputfile->IsOpen())) {
    LmHelper::Debug(Form(" opening rootfile: %s", oaConfig->At(1)->GetName()), 2);
    fInputfile = new TFile(oaConfig->At(1)->GetName());
  }
  else {
    LmHelper::Debug(Form(" using already opened rootfile: %s", oaConfig->At(1)->GetName()), 2);
  }

  TList* lCutset = 0x0;
  if (strcmp(oaConfig->At(2)->GetName(), "NoList") != 0){
    LmHelper::Debug(Form(" getting list: %s", oaConfig->At(2)->GetName()), 2);
    fInputfile->GetObject(oaConfig->At(2)->GetName(), lCutset);
    if (!lCutset) LmHelper::Error(Form("LmManager: cannot find list '%s' in rootfile '%s'!", oaConfig->At(2)->GetName(), oaConfig->At(1)->GetName()));
    LmHelper::Debug(Form("  getting cutset, with list: %s", oaConfig->At(3)->GetName()), 2);
    fCutfolder = (TCollection*) lCutset->FindObject(oaConfig->At(3)->GetName());
  }
  else {
    LmHelper::Debug(Form("  getting cutset, no list: %s", oaConfig->At(3)->GetName()), 2);
    fCutfolder = (TCollection*) fInputfile->Get(oaConfig->At(3)->GetName());
    // _file0->GetObject(oaConfig->At(3)->GetName(), fCutfolder);
  }
  if (!fCutfolder) LmHelper::Error(Form("LmManager: cannot find cut folder '%s' in rootfile '%s'!", oaConfig->At(3)->GetName(), oaConfig->At(1)->GetName()));

  fNEvents = GetHistogram<TH1D>("Event", "nEvents")->GetEntries(); 
  LmHelper::Info(Form("   N_Events = %i", fNEvents));
  CalcEtaRange();
  LmHelper::Info(Form("   Eta_min = %4.2f           Eta_max = %4.2f", GetEtaRange_min(), GetEtaRange_max()));
  CalcPtRange();
  LmHelper::Info(Form("   Pt_min  = %4.2f GeV/c      Pt_max  = %4.2f GeV/c", GetPtRange_min(), GetPtRange_max()));
  CalcCentrality();
  LmHelper::Info(Form("   Centrality_min = %2.0f%%      Centrality_max = %2.0f%%", GetCentrality_min(), GetCentrality_max()));


  return 0;
}


//_______________________________________________________________________________________________
double LmQA::GetNumberOfEvents(){
  LmHelper::Debug("GetNumberOfEvents()", 2);
  TH1D* h1 = GetHistogram<TH1D>("Event", "nEvents");
  return h1->GetBinContent(1); //After PhysicsSelection
}

//_______________________________________________________________________________________________
void LmQA::PrintCentrality(TString filename){
  LmHelper::Debug("PrintCentrality()", 2);

  TH1D* h1 = GetHistogram<TH1D>("Event", "centrality");
  TCanvas* c1 = new TCanvas("Centrality", "Centrality", 1200, 800);
  c1->cd();
  h1->Draw();
  c1->Print(filename);
  delete c1;

  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintEPTPC(TString filename){
  LmHelper::Debug("PrintEPTPC()", 2);

  TH1D* h1 = GetHistogram<TH1D>("Event", "nEvTPC_eventplaneents");
  h1->SetAxisRange(0, h1->GetMaximum()*1.3, "Y");
  TCanvas* c1 = new TCanvas("nEvTPC_eventplaneents", "nEvTPC_eventplaneents", 1200, 800);
  c1->cd();
  h1->Draw();
  c1->Print(filename);
  delete c1;

  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintEPV0AC(TString filename){
  LmHelper::Debug("PrintEPV0AC()", 2);

  TH1D* h1 = GetHistogram<TH1D>("Event", "nEvTPC_eventplaneents");
  TCanvas* c1 = new TCanvas("nEvTPC_eventplaneents", "nEvTPC_eventplaneents", 1200, 800);
  c1->cd();
  h1->Draw();
  c1->Print(filename);
  delete c1;

  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintEPV0ACvsEPTPC(TString filename){
  LmHelper::Debug("PrintEPV0ACvsEPTPC()", 1);

  TH2D* h1 = GetHistogram<TH2D>("Event", "epV0AC_epTPC");
  h1->Rebin2D(5,5);
  TCanvas* c1 = new TCanvas("epV0AC_epTPC", "epV0AC_epTPC");
  c1->cd();
  c1->SetLogz();
  LmHelper::TH2_Beautify(h1, c1);
  h1->Draw("colz");
  c1->Print(filename);
  delete c1;

  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintPvsPInnerWallTPC(TString filename){
  LmHelper::Debug("PrintPvsPInnerWallTPC()", 1);

  TH2D* h1 = GetHistogram<TH2D>("Track_ev1+", "P_PIn");
  h1->Add(GetHistogram<TH2D>("Track_ev1-", "P_PIn"));
  h1->SetTitle("pos+neg");

  Double_t upperedge_x(h1->GetXaxis()->GetBinLowEdge(h1->GetNbinsX()+1));
  Double_t upperedge_y(h1->GetYaxis()->GetBinLowEdge(h1->GetNbinsY()+1));
  TLine* line = new TLine(0., 0., upperedge_x, upperedge_y);

  TCanvas* c1 = new TCanvas("PvsPInnerWallTPC", "PvsPInnerWallTPC", 1200, 800);
  c1->cd();
  c1->SetLogz();
  LmHelper::TH2_Beautify(h1, c1);
  h1->Draw("colz");
  line->Draw("same");
  c1->Print(filename);
  delete c1;
  delete line;
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintPIDTPCdEdxvsP(TString filename){
  LmHelper::Debug("PrintPIDTPCdEdxvsP()", 1);

  TH2D* h1 = GetHistogram<TH2D>("Track_ev1+", "TPC_dEdx_P");
  if (h1 == 0x0) {LmHelper::Error("Printing of histogram TPCdEdxvsP not possible"); return;}
  h1->Add(GetHistogram<TH2D>("Track_ev1-", "TPC_dEdx_P"));
  h1->SetTitle("pos+neg tracks/dEdx");
  TCanvas* c1 = new TCanvas("TPCdEdxvsP", "TPCdEdxvsP", 1200, 800);
  c1->cd();
  c1->SetLogz();
  LmHelper::TH2_Beautify(h1, c1);
  h1->Draw("colz");
  c1->Print(filename);
  delete c1;

  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSSigmaElevsP(TString filename){
  LmHelper::Debug("PrintITSSigmaElevsP()", 1);
  PrintPIDSigma(filename, "ITS", "Elec");
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSSigmaPionvsP(TString filename){
  LmHelper::Debug("PrintITSSigmaPionvsP()", 1);
  PrintPIDSigma(filename, "ITS", "Pion");
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSSigmaKaonvsP(TString filename){
  LmHelper::Debug("PrintITSSigmaKaonvsP()", 1);
    PrintPIDSigma(filename, "ITS", "Kaon");
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCSigmaElevsP(TString filename){
  LmHelper::Debug("PrintTPCSigmaElevsP()", 1);
    PrintPIDSigma(filename, "TPC", "Elec");
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCSigmaPionvsP(TString filename){
  LmHelper::Debug("PrintTPCSigmaPionvsP()", 1);
    PrintPIDSigma(filename, "TPC", "Pion");
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCSigmaKaonvsP(TString filename){
  LmHelper::Debug("PrintTPCSigmaKaonvsP()", 1);
    PrintPIDSigma(filename, "TPC", "Kaon");
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTOFSigmaElevsP(TString filename){
  LmHelper::Debug("PrintTOFSigmaElevsP()", 1);
    PrintPIDSigma(filename, "TOF", "Elec");
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTOFSigmaPionvsP(TString filename){
  LmHelper::Debug("PrintTOFSigmaPionvsP()", 1);
    PrintPIDSigma(filename, "TOF", "Pion");
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTOFSigmaKaonvsP(TString filename){
  LmHelper::Debug("PrintTOFSigmaKaonvsP()", 1);
    PrintPIDSigma(filename, "TOF", "Kaon");
  return;
}

//______________________________________________________________________________________________
void LmQA::PrintPhiEtaProjection(TString filename, TString proj_axis, double minvalue, double maxvalue){
  TCanvas c1("c1", "c1", 1200, 800);
  c1.cd();
  double bottommargin(0.3);
  c1.Divide(1,2);
  c1.cd(1);
  c1.cd(1)->SetPad(0., fRatioPadSize, 1., 1.);  // top pad
  c1.cd(1)->SetBottomMargin(0.001);
  c1.cd(1)->SetTicks();
  c1.cd(2)->SetPad(0., 0., 1., fRatioPadSize);  // bottom pad
  c1.cd(2)->SetTopMargin(0);
  c1.cd(2)->SetBottomMargin(bottommargin); // for x-axis label
  c1.cd(2)->SetTicks();
  c1.cd(1);

  TH2D* hEta_Phi_p = GetHistogram<TH2D>("Track_ev1+", "Eta_Phi");
  std::cout << hEta_Phi_p << std::endl;
  hEta_Phi_p->SetName("EtaPhi_p");

  TH2D* hEta_Phi_n = GetHistogram<TH2D>("Track_ev1-", "Eta_Phi");
  std::cout << hEta_Phi_n << std::endl;
  hEta_Phi_n->SetName("EtaPhi_n");

  TH1D* proj_p;
  TH1D* proj_n;

  std::cout << hEta_Phi_p->GetXaxis()->FindBin(minvalue) << " " << hEta_Phi_p->GetXaxis()->FindBin(maxvalue) << std::endl;
  std::cout << hEta_Phi_n->GetXaxis()->FindBin(minvalue) << " " << hEta_Phi_n->GetXaxis()->FindBin(maxvalue) << std::endl;

  if (proj_axis == "eta"){
    proj_p = hEta_Phi_p->ProjectionX("p_px", hEta_Phi_p->GetYaxis()->FindBin(minvalue), hEta_Phi_p->GetYaxis()->FindBin(maxvalue), "e");
    proj_n = hEta_Phi_n->ProjectionX("n_px", hEta_Phi_n->GetYaxis()->FindBin(minvalue), hEta_Phi_n->GetYaxis()->FindBin(maxvalue), "e");
    proj_p->Draw("h ");
    proj_n->Draw("h same");
  }
  else if (proj_axis == "phi"){
    proj_p = hEta_Phi_p->ProjectionY("p_py", hEta_Phi_p->GetXaxis()->FindBin(minvalue), hEta_Phi_p->GetXaxis()->FindBin(maxvalue), "e");
    proj_n = hEta_Phi_n->ProjectionY("n_py", hEta_Phi_n->GetXaxis()->FindBin(minvalue), hEta_Phi_n->GetXaxis()->FindBin(maxvalue), "e");
    proj_p->Draw("h ");
    proj_n->Draw("h same");
  }
  else {
    std::cout << "Use correct description of axis to project to" << std::endl;
    return;
  }
  proj_p->SetTitle("");
  proj_n->SetTitle("");
  proj_p->SetLineColor(kBlack);
  proj_n->SetLineColor(kOrange+1);

  TH1D ratio(*proj_n);
  ratio.Divide(proj_p);

  ratio.SetStats(kFALSE);
  ratio.SetAxisRange(0.5, 3.0, "Y");
  ratio.SetTitle("");
  ratio.GetYaxis()->SetTitle("#frac{#electrons}{#positrons}");
  ratio.GetYaxis()->SetTitleOffset(0.5);
  ratio.GetXaxis()->SetTitleOffset(1.3);
  ratio.SetTitleSize(ratio.GetTitleSize()/fRatioPadSize*(1.-fRatioPadSize), "xy");
  ratio.SetLabelSize(ratio.GetLabelSize()/fRatioPadSize*(1.-fRatioPadSize), "xy");

  ratio.SetMarkerStyle(20);
  // ratio.GetYaxis()->SetTicks("+-");
  ratio.GetYaxis()->SetNdivisions(4, 5, 0, kTRUE);
  // ratio.DrawCopy("axis");
  ratio.SetAxisRange(ratio.GetMinimum() * 0.5, ratio.GetMaximum() * 3.0, "Y");
  TLine l1(ratio.GetXaxis()->GetBinLowEdge(ratio.GetXaxis()->GetFirst()), 1., ratio.GetXaxis()->GetBinLowEdge(ratio.GetXaxis()->GetLast()+1), 1.);
  c1.cd(2);
  ratio.DrawCopy("hist");
  l1.DrawClone("same");

  TLegend leg1(0.44, 0.02, 0.56, 0.09);
  leg1.AddEntry(proj_n, "Negative tracks", "l");
  leg1.AddEntry(proj_p, "Positive tracks", "l");
  leg1.DrawClone("same");

  c1.SaveAs(filename);

  return;
}

//______________________________________________________________________________________________
void LmQA::PrintPhiPtProjection(TString filename, TString proj_axis, double minvalue, double maxvalue){
  TCanvas c1("c1", "c1", 1200, 800);
  c1.cd();
  double bottommargin(0.3);
  c1.Divide(1,2);
  c1.cd(1);
  c1.cd(1)->SetPad(0., fRatioPadSize, 1., 1.);  // top pad
  c1.cd(1)->SetBottomMargin(0.001);
  c1.cd(1)->SetTicks();
  c1.cd(2)->SetPad(0., 0., 1., fRatioPadSize);  // bottom pad
  c1.cd(2)->SetTopMargin(0);
  c1.cd(2)->SetBottomMargin(bottommargin); // for x-axis label
  c1.cd(2)->SetTicks();
  c1.cd(1);
  TH2D* hEta_Phi_p = GetHistogram<TH2D>("Track_ev1+", "Phi_Pt");
  std::cout << hEta_Phi_p << std::endl;
  hEta_Phi_p->SetName("PhiPt_p");

  TH2D* hEta_Phi_n = GetHistogram<TH2D>("Track_ev1-", "Phi_Pt");
  std::cout << hEta_Phi_n << std::endl;
  hEta_Phi_n->SetName("PhiPt_n");

  TH1D* proj_p;
  TH1D* proj_n;

  std::cout << hEta_Phi_p->GetXaxis()->FindBin(minvalue) << " " << hEta_Phi_p->GetXaxis()->FindBin(maxvalue) << std::endl;
  std::cout << hEta_Phi_n->GetXaxis()->FindBin(minvalue) << " " << hEta_Phi_n->GetXaxis()->FindBin(maxvalue) << std::endl;

  if (proj_axis == "pt"){
    proj_p = hEta_Phi_p->ProjectionX("p_px", hEta_Phi_p->GetYaxis()->FindBin(minvalue), hEta_Phi_p->GetYaxis()->FindBin(maxvalue), "e");
    proj_n = hEta_Phi_n->ProjectionX("n_px", hEta_Phi_n->GetYaxis()->FindBin(minvalue), hEta_Phi_n->GetYaxis()->FindBin(maxvalue), "e");
    proj_p->Draw("h ");
    proj_n->Draw("h same");
  }
  else if (proj_axis == "phi"){
    proj_p = hEta_Phi_p->ProjectionY("p_py", hEta_Phi_p->GetXaxis()->FindBin(minvalue), hEta_Phi_p->GetXaxis()->FindBin(maxvalue), "e");
    proj_n = hEta_Phi_n->ProjectionY("n_py", hEta_Phi_n->GetXaxis()->FindBin(minvalue), hEta_Phi_n->GetXaxis()->FindBin(maxvalue), "e");
    proj_p->Draw("h ");
    proj_n->Draw("h same");
  }
  else {
    std::cout << "Use correct description of axis to project to" << std::endl;
    return;
  }
  proj_p->SetTitle("");
  proj_n->SetTitle("");
  proj_p->SetLineColor(kBlack);
  proj_n->SetLineColor(kOrange+1);

  TH1D ratio(*proj_n);
  ratio.Divide(proj_p);

  ratio.SetStats(kFALSE);
  ratio.SetAxisRange(0.5, 3.0, "Y");
  ratio.SetTitle("");
  ratio.GetYaxis()->SetTitle("#frac{#electrons}{#positrons}");
  ratio.GetYaxis()->SetTitleOffset(0.5);
  ratio.GetXaxis()->SetTitleOffset(1.3);
  ratio.SetTitleSize(ratio.GetTitleSize()/fRatioPadSize*(1.-fRatioPadSize), "xy");
  ratio.SetLabelSize(ratio.GetLabelSize()/fRatioPadSize*(1.-fRatioPadSize), "xy");

  ratio.SetMarkerStyle(20);
  // ratio.GetYaxis()->SetTicks("+-");
  ratio.GetYaxis()->SetNdivisions(4, 5, 0, kTRUE);
  // ratio.DrawCopy("axis");
  ratio.SetAxisRange(ratio.GetMinimum() * 0.5, ratio.GetMaximum() *3.0, "Y");
  TLine l1(ratio.GetXaxis()->GetBinLowEdge(ratio.GetXaxis()->GetFirst()), 1., ratio.GetXaxis()->GetBinLowEdge(ratio.GetXaxis()->GetLast()+1), 1.);
  c1.cd(2);
  ratio.DrawCopy("hist");
  l1.DrawClone("same");

  TLegend leg1(0.44, 0.02, 0.56, 0.09);
  leg1.AddEntry(proj_n, "Negative tracks", "l");
  leg1.AddEntry(proj_p, "Positive tracks", "l");
  leg1.DrawClone("same");

  c1.SaveAs(filename);

  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintPIDSigma(TString filename, TString detector, TString particle){
  LmHelper::Debug("--PrintPIDSigma()", 1);

  TString particleChopped(particle.Chop());
  TString histName(TString::Format("%snSigma%s_P", detector.Data(), particleChopped.Data()));
  TH2D* h1 = GetHistogram<TH2D>("Track_ev1+", histName);
  if (h1 == 0x0) {LmHelper::Error(Form("Printing of histogram %s not possible", histName.Data())); return;}
  h1->Add(GetHistogram<TH2D>("Track_ev1-", histName));
  h1->SetTitle("pos+neg");

  Double_t upperedge_x(h1->GetXaxis()->GetBinLowEdge(h1->GetNbinsX()+1));
  TLine* line = new TLine(0., 0., upperedge_x, 0);

  TString canvName(TString::Format("Print%sSigma%svsP", detector.Data(), particle.Data()));
  TCanvas* c1 = new TCanvas(canvName, canvName, 1200, 800);
  c1->cd();
  c1->SetLogz();
  LmHelper::TH2_Beautify(h1, c1);
  h1->SetAxisRange(0.0, 5.0, "X");
  h1->Draw("colz");
  line->Draw("same");
  c1->Print(filename);
  delete c1;
  delete line;
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCSigmaElevsEta(TString filename){
  LmHelper::Debug("PrintTPCSigmaElevsEta()", 1);
  TH2D* h1 = GetHistogram<TH2D>("Track_ev1+", "TPCnSigmaEle_Eta");
  if (h1 == 0x0) {LmHelper::Error("Printing of histogram TPCnSigmaEle_Eta not possible"); return;}
  h1->Add(GetHistogram<TH2D>("Track_ev1-", "TPCnSigmaEle_Eta"));
  h1->SetTitle("pos+neg");

  TCanvas* c1 = new TCanvas("PrintTPCSigmaElevsEta", "PrintTPCSigmaElevsEta", 1200, 800);
  c1->cd();
  // c1->SetLogz();
  LmHelper::TH2_Beautify(h1, c1);
  h1->Draw("colz");
  c1->Print(filename);
  delete c1;
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintPtAll(TString filename){
  LmHelper::Debug("PrintPtTracks()", 2);
  PrintTrackingPrivate(filename, "Pt", kAll);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintPtCompare(TString filename){
  LmHelper::Debug("PrintPtTracks()", 2);
  PrintTrackingPrivate(filename, "Pt", kCompare);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintPtNeg(TString filename){
  LmHelper::Debug("PrintPtNegTracks()", 2);
  PrintTrackingPrivate(filename, "Pt", kNeg);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintPtPos(TString filename){
  LmHelper::Debug("PrintPtPosTracks()", 2);
  PrintTrackingPrivate(filename, "Pt", kPos);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintEtaAll(TString filename){
  LmHelper::Debug("PrintEtaAll()", 1);
  PrintTrackingPrivate(filename, "Eta", kAll);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintEtaCompare(TString filename){
  LmHelper::Debug("PrintEtaAll()", 1);
  PrintTrackingPrivate(filename, "Eta", kCompare);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintEtaNeg(TString filename){
  LmHelper::Debug("PrintEtaNeg()", 1);
  PrintTrackingPrivate(filename, "Eta", kNeg);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintEtaPos(TString filename){
  LmHelper::Debug("PrintEtaPos()", 1);
  PrintTrackingPrivate(filename, "Eta", kPos);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintPhiAll(TString filename){
  LmHelper::Debug("PrintPhiAll()", 1);
  PrintTrackingPrivate(filename, "Phi", kAll);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintPhiCompare(TString filename){
  LmHelper::Debug("PrintPhiAll()", 1);
  PrintTrackingPrivate(filename, "Phi", kCompare);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintPhiNeg(TString filename){
  LmHelper::Debug("PrintPhiNeg()", 1);
  PrintTrackingPrivate(filename, "Phi", kNeg);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintPhiPos(TString filename){
  LmHelper::Debug("PrintPhiPos()", 1);
  PrintTrackingPrivate(filename, "Phi", kPos);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCrowsOverFindableAll(TString filename){
  LmHelper::Debug("PrintTPCrowsoverfinableAll()", 2);
  //PrintTrackingPrivate(filename, "CrossedRowsOverFindable", kAll);
  PrintTrackingPrivate(filename, "TPCcrossedRowsOverFindable", kAll);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCrowsOverFindableCompare(TString filename){
  LmHelper::Debug("PrintTPCrowsoverfinableAll()", 2);
  PrintTrackingPrivate(filename, "TPCcrossedRowsOverFindable", kCompare);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCrowsOverFindableNeg(TString filename){
  LmHelper::Debug("PrintTPCrowsoverfinableNeg()", 2);
  PrintTrackingPrivate(filename, "TPCcrossedRowsOverFindable", kNeg);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCrowsOverFindablePos(TString filename){
  LmHelper::Debug("PrintTPCrowsoverfinablePos()", 2);
  PrintTrackingPrivate(filename, "TPCcrossedRowsOverFindable", kPos);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCCrossedRowsAll(TString filename){
  LmHelper::Debug("PrintTPCCrossedRowsAll()", 2);
//  PrintTrackingPrivate(filename, "CrossedRows", kAll);
  PrintTrackingPrivate(filename, "TPCcrossedRows", kAll);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCCrossedRowsCompare(TString filename){
  LmHelper::Debug("PrintTPCCrossedRowsAll()", 2);
  PrintTrackingPrivate(filename, "TPCcrossedRows", kCompare);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCCrossedRowsNeg(TString filename){
  LmHelper::Debug("PrintTPCCrossedRowsNeg()", 2);
  PrintTrackingPrivate(filename, "TPCcrossedRows", kNeg);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCCrossedRowsPos(TString filename){
  LmHelper::Debug("PrintTPCCrossedRowsPos()", 2);
  PrintTrackingPrivate(filename, "TPCcrossedRows", kPos);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCnClsAll(TString filename){
  LmHelper::Debug("PrintTPCnClsAll()", 2);
//  PrintTrackingPrivate(filename, "NClusterTPC", kAll);
  PrintTrackingPrivate(filename, "TPCnCls", kAll);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCnClsCompare(TString filename){
  LmHelper::Debug("PrintTPCnClsAll()", 2);
  PrintTrackingPrivate(filename, "TPCnCls", kCompare);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCnClsNeg(TString filename){
  LmHelper::Debug("PrintTPCnClsNeg()", 2);
  PrintTrackingPrivate(filename, "TPCnCls", kNeg);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCnClsPos(TString filename){
  LmHelper::Debug("PrintTPCnClsPos()", 2);
  PrintTrackingPrivate(filename, "TPCnCls", kPos);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSnClsAll(TString filename){
  LmHelper::Debug("PrintITSnClsAll()", 2);
//  PrintTrackingPrivate(filename, "NClusterITS", kAll);
  PrintTrackingPrivate(filename, "ITSnCls", kAll);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSnClsCompare(TString filename){
  LmHelper::Debug("PrintITSnClsAll()", 2);
  PrintTrackingPrivate(filename, "ITSnCls", kCompare);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSnClsNeg(TString filename){
  LmHelper::Debug("PrintITSnClsNeg()", 2);
  PrintTrackingPrivate(filename, "ITSnCls", kNeg);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSnClsPos(TString filename){
  LmHelper::Debug("PrintITSnClsPos()", 2);
  PrintTrackingPrivate(filename, "ITSnCls", kPos);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSnClsSAll(TString filename){
  LmHelper::Debug("PrintITSnClsSAll()", 2);
  PrintTrackingPrivate(filename, "ITSnClsS", kAll);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSnClsSCompare(TString filename){
  LmHelper::Debug("PrintITSnClsSAll()", 2);
  PrintTrackingPrivate(filename, "ITSnClsS", kCompare);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSnClsSNeg(TString filename){
  LmHelper::Debug("PrintITSnClsSNeg()", 2);
  PrintTrackingPrivate(filename, "ITSnClsS", kNeg);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSnClsSPos(TString filename){
  LmHelper::Debug("PrintITSnClsSPos()", 2);
  PrintTrackingPrivate(filename, "ITSnClsS", kPos);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCChi2All(TString filename){
  LmHelper::Debug("PrintTPCChi2All()", 2);
//  PrintTrackingPrivate(filename, "TPCchi2perCls", kAll);
  PrintTrackingPrivate(filename, "TPCchi2", kAll);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCChi2Compare(TString filename){
  LmHelper::Debug("PrintTPCChi2All()", 2);
  PrintTrackingPrivate(filename, "TPCchi2", kCompare);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCChi2Neg(TString filename){
  LmHelper::Debug("PrintTPCChi2Neg()", 2);
  PrintTrackingPrivate(filename, "TPCchi2", kNeg);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintTPCChi2Pos(TString filename){
  LmHelper::Debug("PrintTPCChi2Pos()", 2);
  PrintTrackingPrivate(filename, "TPCchi2", kPos);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSChi2All(TString filename){
  LmHelper::Debug("PrintITSChi2All()", 2);
//  PrintTrackingPrivate(filename, "ITSchi2perCls", kAll);
  PrintTrackingPrivate(filename, "ITSchi2", kAll);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSChi2Compare(TString filename){
  LmHelper::Debug("PrintITSChi2All()", 2);
  PrintTrackingPrivate(filename, "ITSchi2", kCompare);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSChi2Neg(TString filename){
  LmHelper::Debug("PrintITSChi2Neg()", 2);
  PrintTrackingPrivate(filename, "ITSchi2", kNeg);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintITSChi2Pos(TString filename){
  LmHelper::Debug("PrintITSChi2Pos()", 2);
  PrintTrackingPrivate(filename, "ITSchi2", kPos);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintZVertexAll(TString filename){
  LmHelper::Debug("PrintZVertexAll()", 2);
  PrintTrackingPrivate(filename, "ImpParZ", kAll);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintZVertexCompare(TString filename){
  LmHelper::Debug("PrintZVertexAll()", 2);
  PrintTrackingPrivate(filename, "ImpParZ", kCompare);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintZVertexNeg(TString filename){
  LmHelper::Debug("PrintZVertexNeg()", 2);
  PrintTrackingPrivate(filename, "ImpParZ", kNeg);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintZVertexPos(TString filename){
  LmHelper::Debug("PrintZVertexPos()", 2);
  PrintTrackingPrivate(filename, "ImpParZ", kPos);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintXYVertexAll(TString filename){
  LmHelper::Debug("PrintXYVertexAll()", 2);
  PrintTrackingPrivate(filename, "ImpParXY", kAll);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintXYVertexCompare(TString filename){
  LmHelper::Debug("PrintXYVertexAll()", 2);
  PrintTrackingPrivate(filename, "ImpParXY", kCompare);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintXYVertexNeg(TString filename){
  LmHelper::Debug("PrintXYVertexNeg()", 2);
  PrintTrackingPrivate(filename, "ImpParXY", kNeg);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintXYVertexPos(TString filename){
  LmHelper::Debug("PrintXYVertexPos()", 2);
  PrintTrackingPrivate(filename, "ImpParXY", kPos);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintEventVtxZ(TString filename){
  LmHelper::Debug("PrintEventVtxZ()", 2);
  PrintTrackingPrivate(filename, "ZVertex", kEvent);
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintPID(TString folder){
  gSystem->Exec( Form("mkdir -p ./%s",folder.Data()) ); // recursively create folder/subfolder/... if needed
  PrintITSSigmaElevsP(Form("%s/PID_ITSSigmaElevsP.pdf", folder.Data()));
  PrintITSSigmaPionvsP(Form("%s/PID_ITSSigmaPionvsP.pdf", folder.Data()));
  PrintITSSigmaKaonvsP(Form("%s/PID_ITSSigmaKaonvsP.pdf", folder.Data()));
  PrintTPCSigmaElevsP(Form("%s/PID_TPCSigmaElevsP.pdf", folder.Data()));
  PrintTPCSigmaPionvsP(Form("%s/PID_TPCSigmaPionvsP.pdf", folder.Data()));
  PrintTPCSigmaKaonvsP(Form("%s/PID_TPCSigmaKaonvsP.pdf", folder.Data()));
  PrintTPCSigmaElevsEta(Form("%s/PID_TPCSigmaElevsEta.pdf", folder.Data()));
  PrintTOFSigmaElevsP(Form("%s/PID_TOFSigmaElevsP.pdf", folder.Data()));
  // PrintTOFSigmaPionvsP(Form("%s/PID_TOFSigmaPionvsP.pdf", folder.Data()));
  // PrintTOFSigmaKaonvsP(Form("%s/PID_TOFSigmaKaonvsP.pdf", folder.Data()));
  return;
}

//_______________________________________________________________________________________________
void LmQA::PrintQuality(TString folder){
  gSystem->Exec( Form("mkdir -p ./%s",folder.Data()) ); // recursively create folder/subfolder/... if needed
  PrintPtAll(Form("%s/Pt.pdf", folder.Data()));
  PrintEtaAll(Form("%s/Eta.pdf", folder.Data()));
  PrintPhiAll(Form("%s/Phi.pdf", folder.Data()));
  PrintTPCrowsOverFindableAll(Form("%s/TPCrowsOverFindable.pdf", folder.Data()));
  PrintTPCCrossedRowsAll(Form("%s/TPCCrossedRows.pdf", folder.Data()));
  PrintTPCnClsAll(Form("%s/TPCnCls.pdf", folder.Data()));
  PrintITSnClsAll(Form("%s/ITSnCls.pdf", folder.Data()));
  PrintTPCChi2All(Form("%s/TPCChi2.pdf", folder.Data()));
  PrintITSChi2All(Form("%s/ITSChi2.pdf", folder.Data()));
  PrintXYVertexAll(Form("%s/dcaXY.pdf", folder.Data()));
  PrintZVertexAll(Form("%s/dcaZ.pdf", folder.Data()));
  return;
}

void LmQA::PrintEtaPhiAll(TString filename){
  TCanvas* c1 = new TCanvas("Eta_Phi_all", "Eta_Phi_all");
  TH2D* h_pos = static_cast<TH2D*>(GetHistogram<TH2D>("Track_ev1+", "Eta_phi"));
  TH2D* h_neg = static_cast<TH2D*>(GetHistogram<TH2D>("Track_ev1-", "Eta_phi"));
  h_pos->Add(h_neg);
  h_pos->SetTitle("EtaPhi pos+neg");
  h_pos->Draw("colz");
  c1->Print(filename);
}
void LmQA::PrintEtaPhiPos(TString filename){
  TCanvas* c1 = new TCanvas("Eta_Phi+", "Eta_Phi+");
  TH2D* h2 = static_cast<TH2D*>(GetHistogram<TH2D>("Track_ev1+", "Eta_phi"));
  h2->SetTitle("EtaPhi pos");
  h2->Draw("colz");
  c1->Print(filename);
}
void LmQA::PrintEtaPhiNeg(TString filename){
  TCanvas* c1 = new TCanvas("Eta_Phi-", "Eta_Phi-");
  TH2D* h2 = static_cast<TH2D*>(GetHistogram<TH2D>("Track_ev1+", "Eta_phi"));
  h2->SetTitle("EtaPhi neg");
  h2->Draw("colz");
  c1->Print(filename);
}


//_______________________________________________________________________________________________
TH1* LmQA::GetEventHist(TString observable){
  LmHelper::Debug("--LmQA::GetEventHist()", 2);
  TH1* h1 = 0x0;
  
  h1 = GetHistogram<TH1D>("Event", observable);
  h1->SetTitle(Form("%s event", observable.Data()));
  if(fRebin > 1)
    h1->Rebin(fRebin);
  if(fDoNormNEntries == 1)
    h1->Scale(1./h1->GetEntries());
  else if(fDoNormNEvents == 1)
    h1->Scale(1./fNEvents); 
  
  return h1;
}

 

//_______________________________________________________________________________________________
TH1* LmQA::GetTrackHist(TString observable, int type/*, TH1* hComp*/){
  LmHelper::Debug("--LmQA::GetTrackHist()", 2);
  TH1* h1 = 0x0;
  //TH1* h2 = 0x0;
  // @TODO: implement return of h2 in case of kCompare
  switch (type){
    case kAll:
    {
      h1 = static_cast<TH1*>((GetHistogram<TH1>("Track_ev1-", observable))->Clone(Form("SumOf%s", observable.Data())));
      h1->Add(GetHistogram<TH1>("Track_ev1+", observable));
      h1->SetTitle(Form("%s pos+neg", observable.Data()));
      if(fRebin > 1)
        h1->Rebin(fRebin);
      if(fDoNormNEntries == 1)
        h1->Scale(1./h1->GetEntries());
      else if(fDoNormNEvents == 1)
        h1->Scale(1./fNEvents); 
      
      break;
    }
    case kNeg:
    {
      h1 = GetHistogram<TH1>("Track_ev1-", observable);
      h1->SetTitle(Form("%s neg", observable.Data()));
      if(fRebin > 1)
        h1->Rebin(fRebin);
      if(fDoNormNEntries == 1)
        h1->Scale(1./h1->GetEntries());
      else if(fDoNormNEvents == 1)
        h1->Scale(1./fNEvents); 
      break;
    }
    case kPos:
    {
      h1 = GetHistogram<TH1>("Track_ev1+", observable);
      h1->SetTitle(Form("%s pos", observable.Data()));
      if(fRebin > 1)
        h1->Rebin(fRebin);
      if(fDoNormNEntries == 1)
        h1->Scale(1./h1->GetEntries());
      else if(fDoNormNEvents == 1)
        h1->Scale(1./fNEvents); 

      break;
    }
//    case kCompare:
//    {
//      h1 = GetHistogram<TH1>("Track_ev1-", observable);
//      h1->SetTitle(Form("Comparison of %s", observable.Data()));
//      h2 = GetHistogram<TH1>("Track_ev1+", observable);
//      break;
//    }
  }
  
//  if (h2!=0x0) hComp = h2; // TODO: not sure if this is ok, compare to other code...
  return h1;
}
      
//_______________________________________________________________________________________________
void LmQA::PrintTrackingPrivate(TString filename, TString observable, int type){
  LmHelper::Debug("--LmQA::PrintTrackingPrivate()", 2);
  TH1D* h1 = 0x0;
  TCanvas* c1 = new TCanvas(observable, observable, 1200, 800);
  c1->cd();

  switch (type){
    case kEvent:
    {
      h1 = (TH1D*) GetEventHist(observable);
      break;
    }
    case kAll:
    case kNeg:
    case kPos:
    {
      h1 = (TH1D*) GetTrackHist(observable, type); // which c++ cast?
      break;
    }
    case kCompare:
    {
      
      //Preparation of canvases
      if (fDoRatio) {
        double bottommargin(0.3);
        c1->Divide(1,2);
        c1->cd(1);
        c1->cd(1)->SetPad(0., fRatioPadSize, 1., 1.);  // top pad
        c1->cd(1)->SetBottomMargin(0.001);
        c1->cd(1)->SetTicks();
        c1->cd(2)->SetPad(0., 0., 1., fRatioPadSize);  // bottom pad
        c1->cd(2)->SetTopMargin(0);
        c1->cd(2)->SetBottomMargin(bottommargin); // for x-axis label
        c1->cd(2)->SetTicks();
      }

      // Upper histogram
      h1 = GetHistogram<TH1D>("Track_ev1-", observable);
      if(fRebin > 1)
        h1->Rebin(fRebin);
      if(fDoNormNEntries == 1)
        h1->Scale(1./h1->GetEntries());
      else if(fDoNormNEvents == 1)
        h1->Scale(1./fNEvents); 


      TH1D* h2 = GetHistogram<TH1D>("Track_ev1+", observable);
      h1->SetTitle(Form("Comparison of %s", observable.Data()));

      h1->SetMarkerColor(kOrange+1);
      h1->SetLineColor(kOrange+1);
      h1->SetLineWidth(2);

      h2->SetMarkerColor(kBlack);
      h2->SetLineColor(kBlack);
      h2->SetLineWidth(2);


      TLegend leg1(0.44, 0.02, 0.56, 0.09);
      leg1.AddEntry(h1, "Negative tracks", "l");
      leg1.AddEntry(h2, "Positive tracks", "l");

      SetAxisRanges(h1, observable, c1);
      SetAxisRanges(h2, observable, c1);
      c1->cd(1);
      h1->DrawCopy("hist e");
      h2->DrawCopy("hist e same");
      leg1.DrawClone("same");


      // Ratio plots
      if (fDoRatio) {
        TH1D ratio(*h1);
        ratio.Divide(h2);

        ratio.SetStats(kFALSE);
        ratio.SetAxisRange(0.5, 5., "Y");
        ratio.SetTitle("");
        ratio.GetYaxis()->SetTitle("#frac{#electrons}{#positrons}");
        ratio.GetYaxis()->SetTitleOffset(0.5);
        ratio.GetXaxis()->SetTitleOffset(1.3);
        ratio.SetTitleSize(ratio.GetTitleSize()/fRatioPadSize*(1.-fRatioPadSize), "xy");
        ratio.SetLabelSize(ratio.GetLabelSize()/fRatioPadSize*(1.-fRatioPadSize), "xy");

        ratio.SetMarkerStyle(20);
        // ratio.GetYaxis()->SetTicks("+-");
        ratio.GetYaxis()->SetNdivisions(4, 5, 0, kTRUE);
        // ratio.DrawCopy("axis");
        SetAxisRanges(&ratio, observable, c1);
        ratio.SetAxisRange(ratio.GetMinimum() * 0.9, ratio.GetMaximum() * 1.1, "Y");
        TLine l1(ratio.GetXaxis()->GetBinLowEdge(ratio.GetXaxis()->GetFirst()), 1., ratio.GetXaxis()->GetBinLowEdge(ratio.GetXaxis()->GetLast()+1), 1.);
        c1->cd(2);
        ratio.DrawCopy("hist");
        l1.DrawClone("same");
      }

      c1->Print(filename);
      delete c1;
      return;
      break;
    }
  }


  SetAxisRanges(h1, observable, c1);
  h1->Draw("");
  c1->Print(filename);
  delete c1;

  return;
}

//_______________________________________________________________________________________________
void LmQA::SetAxisRanges(TH1D* h1, TString observable, TCanvas* c1){
  if (observable == "Pt") {h1->SetAxisRange(0, fpt_range_max, "X"); c1->cd(1)->SetLogy(); }
  //if (observable == "Pt") {h1->SetAxisRange(0, 1.5, "X"); c1->cd(1)->SetLogy(); }

  else if (observable == "Eta") {h1->SetAxisRange(feta_range_min - 0.2, feta_range_max + 0.2, "X"); h1->SetAxisRange(0, h1->GetMaximum()*1.1, "Y");}
  else if (observable == "Phi") {h1->SetAxisRange(0, 2*3.15, "X");  h1->SetAxisRange(0, h1->GetMaximum()*1.1, "Y"); }
//else if (observable == "TPCcrossedRowsOverFindable") h1->SetAxisRange(0, 1.2, "X");
//else if (observable == "TPCcrossedRows") h1->SetAxisRange(0, 170, "X");
//else if (observable == "TPCnCls") h1->SetAxisRange(0, 170, "X");
  else if (observable == "TPCcrossedRowsOverFindable") {h1->SetAxisRange(0.5, 1.2, "X"); }//c1->cd(1)->SetLogy();}
  else if (observable == "TPCcrossedRows") {h1->SetAxisRange(50, 170, "X"); }//c1->cd(1)->SetLogy();}
  else if (observable == "TPCnCls") h1->SetAxisRange(50, 170, "X");
  else if (observable == "ITSnCls") h1->SetAxisRange(0, 7, "X");
  else if (observable == "dZ") {h1->SetAxisRange(-3.5, 3.5, "X"); c1->cd(1)->SetLogy();}
  else if (observable == "dXY") {h1->SetAxisRange(-1.5, 1.5, "X"); c1->cd(1)->SetLogy();}
  return;
}

//_______________________________________________________________________________________________
void LmQA::CalcEtaRange(){
  Int_t eta_bin = -1;
  TCollection* histFolderTemp = 0x0;
  histFolderTemp = (TCollection*) fCutfolder->FindObject("Track_ev1-");
  if (histFolderTemp->FindObject("Eta") != 0)  {
    TH1D* hEtaRange = (TH1D*) histFolderTemp->FindObject("Eta");
    eta_bin = hEtaRange->FindFirstBinAbove(0); //first bin with entries
    feta_range_min = hEtaRange->GetBinLowEdge(eta_bin);
    eta_bin = hEtaRange->FindLastBinAbove(0); //last bin with entries
    feta_range_max = hEtaRange->GetBinLowEdge(eta_bin+1);
  }
  else if (histFolderTemp->FindObject("Eta_Phi") != 0) {
    TH2D* hEta_Phi = (TH2D*) histFolderTemp->FindObject("Eta_Phi");
    TH1D* hEtaRange = (TH1D*) hEta_Phi->ProjectionX();
    eta_bin = hEtaRange->FindFirstBinAbove(0); //first bin with entries
    feta_range_min = hEtaRange->GetBinLowEdge(eta_bin);
    eta_bin = hEtaRange->FindLastBinAbove(0); //last bin with entries
    feta_range_max = hEtaRange->GetBinLowEdge(eta_bin+1);
  }
}

//_______________________________________________________________________________________________
void LmQA::CalcPtRange(){
  Int_t pt_bin = -1;
  TCollection* histFolderTemp;
  histFolderTemp = (TCollection*) fCutfolder->FindObject("Track_ev1+");
  if (histFolderTemp->FindObject("Pt") != 0){
    TH1D* hPtRange = (TH1D*) histFolderTemp->FindObject("Pt");
    pt_bin = hPtRange->FindFirstBinAbove(0); //first bin with entries
    fpt_range_min = hPtRange->GetBinLowEdge(pt_bin);
    pt_bin = hPtRange->FindLastBinAbove(0); //last bin with entries
    fpt_range_max = hPtRange->GetBinLowEdge(pt_bin+1);
  }
}

//_______________________________________________________________________________________________
void LmQA::CalcCentrality(){
  Int_t centrality_range_bin = -1;
  TCollection* histFolderTemp;
  histFolderTemp = (TCollection*) fCutfolder->FindObject("Event");
  // check if there is a centrality histogram. pPb + pp dont have one
  if (histFolderTemp->FindObject("centrality") == 0){
    fcentrality_min = -1;
    fcentrality_max = -1;
  }
  else {
    TH1D* hCentralityRange = (TH1D*) histFolderTemp->FindObject("centrality");
    centrality_range_bin = hCentralityRange->FindFirstBinAbove(0); //First bin with entries
    fcentrality_min = hCentralityRange->GetBinLowEdge(centrality_range_bin);
    centrality_range_bin = hCentralityRange->FindLastBinAbove(0); //last bin with entries
    fcentrality_max = hCentralityRange->GetBinLowEdge(centrality_range_bin+1);
  }
}

