// c++ includes
#include <iostream>
#include <vector>
using namespace std;
// ROOT includes
#include "TString.h"
#include "TObjArray.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TMath.h"
#include "TLegend.h"
// project includes
#include "LmCocktail.h"
#include "LmCocktailMan.h"
#include "LmCocktailPart.h"
#include "LmHelper.h"


// copy constructor, used by LmHandler to have its own cocktail
//_______________________________________________________________________________________________
LmCocktail::LmCocktail(const LmCocktail& cockt) :
fName(cockt.fName),
fType(cockt.fType),
fPrintUnc(kFALSE),
fCrosssection_pp(cockt.fCrosssection_pp),
fCrosssection_event_cc(cockt.fCrosssection_event_cc),
fCrosssection_event_bb(cockt.fCrosssection_event_bb),
fNcoll(cockt.fNcoll),
//fLFscaling(cockt.fLFscaling),
fBranchingCharmToEle(cockt.fBranchingCharmToEle),
fBranchingBeautyToEle(cockt.fBranchingBeautyToEle),
//fNeventsPhysSel(cockt.fNeventsPhysSel),
fCrossSection(cockt.fCrossSection),
fDoNormBinwidth(cockt.fDoNormBinwidth),
fDoNormNevents(cockt.fDoNormNevents),
fDoNormNentries(cockt.fDoNormNentries),
fDoNormCrossSection(cockt.fCrossSection),
fDoNormMidRap(cockt.fDoNormMidRap),
fDrawStyle(cockt.fDrawStyle),
fDrawStyleErr(cockt.fDrawStyleErr),
fDrawOpt(cockt.fDrawOpt)
{
  /// Copy constructor for LmCocktail
  /// use it only after having called Process(), because the managers are not copied.

  LmHelper::Debug("LmCocktail copy constructor", 5);

  if (fType==LmCocktail::kNoProcess) { LmHelper::Error(Form("LmCocktail(const LmCocktail&): do not use copy constructor before having called Process()!")); }

  // initialize inherited variables:
  // copy member variables:
  fBinsPtee_forprojMee = cockt.fBinsPtee_forprojMee;
  fBinsMee_forprojPtee = cockt.fBinsMee_forprojPtee;
  fLmCocktailMan.clear(); // dont need managers, if Process() was called before.
  fLmCocktailPart.clear();

  for (unsigned int iPart=0; iPart<cockt.fLmCocktailPart.size(); iPart++)
  {
    LmCocktailPart* partTemp = new LmCocktailPart( *(cockt.fLmCocktailPart.at(iPart)) ); // using copy constructor of LmCocktailPart.
    fLmCocktailPart.push_back(partTemp);
  }
}


//_______________________________________________________________________________________________
LmCocktail::LmCocktail(Int_t system, std::string name, Bool_t UseNormMidRap) :
fName(name),
fType(kNoProcess), // dont change this unless the copy constructor was updated.
fPrintUnc(kFALSE),
fCrosssection_pp(1),
fCrosssection_event_cc(1),
fCrosssection_event_bb(1),
fNcoll(1),
//fLFscaling(1),
fBranchingCharmToEle(1.),
fBranchingBeautyToEle(1.),
fDrawStyle("hist"),
fDrawStyleErr("E2"),
fDrawOpt(kAll),
fCrossSection(1),
fDoNormBinwidth(kTRUE),
fDoNormNevents(kFALSE),
fDoNormNentries(kTRUE),
fDoNormCrossSection(kFALSE),
fDoNormMidRap(UseNormMidRap)
{
  /// Default constructor for LmCocktail
  /// @param system Collision system from enum enSystem (optional)
  /// @see enSystem

  LmHelper::Debug("LmCocktail default constructor", 5);

  // The sum is attached in the constructor, so that it will always be the first vector element, no matter which cocktail type is used.
  LmCocktailPart* partSum = new LmCocktailPart(); // name will be replaced by fName later.
  AttachPart( *partSum ); // placeholder for sum as first vector element. Initially it will have the type LmCocktailPart::kUndef.

  const Double_t sigma_tot_cc_2760GeV = 4.8  ; // mb. [https://arxiv.org/pdf/1205.4007v2.pdf] High: +TMath::Sqrt(0.8*0.8+1+0.06*0.06+0.01+0.01+2.6*2.6) = +2.902, Low: -TMath::Sqrt(0.8*0.8+1.3*1.3+0.06*0.06+0.01+0.01+0.4*0.4) = -1.585
  const Double_t sigma_tot_cc_5020GeV = 7.0 ; // interpolated
  //const Double_t sigma_tot_cc_7TeV  = 8.5  ; // mb. [https://arxiv.org/pdf/1205.4007v2.pdf]
  const Double_t sigma_tot_cc_7TeV    = 7.48 ; // mb. [https://arxiv.org/pdf/1702.00766.pdf] σcc_pp,7TeV(ALICE,LHCb) = 7.48±0.14(stat.) ±0.46(syst.)+0.11−0.05(extr.) ±0.33(FF) mb
  const Double_t dsigma_dy_cc_7TeV    = 0.954; // mb. [https://arxiv.org/pdf/1702.00766.pdf] 954±69(stat)±74(syst)±33(lumi)±42(FF)±31(rap.shape)
  const Double_t sigma_tot_cc_13TeV   = 12.16 ; // mb.  +-1.3-1.15 FONLL extrapolation from 7 TeV to 13 TeV 
  const Double_t dsigma_dy_cc_13TeV    = 1.33 ; //mb | y=0 +-0.17 FONLL extrapolation from 7 TeV to 13 TeV IVAN analysis note
  const Double_t dsigma_dy_cc_13TeVpythia = 0.974 ; //mb | y=0 +-0.138 FROM 13 TeV nominal field HF fit pythia
  const Double_t dsigma_dy_cc_13TeVpowheg = 1.417 ; //mb | y=0 +-0.138 FROM 13 TeV nominal field HF fit powheg


  const Double_t sigma_tot_bb_2760GeV = 0.130; // mb. [http://arxiv.org/pdf/1405.4144.pdf] High: +TMath::Sqrt(15.1*15.1+42.1*42.1+3.4*3.4+2.5+2.5+4.4*4.4) = +0.04513, Low: -TMath::Sqrt(15.1*15.1+49.8*49.8+3.1*3.1+2.5+2.5+4.4*4.4) = -0.05236
  const Double_t sigma_tot_bb_5020GeV = 0.220; // interpolated
  const Double_t sigma_tot_bb_7TeV    = 0.281; // mb. [http://arxiv.org/pdf/1208.1902v4.pdf], 0.295 measured by LHCb
  const Double_t sigma_tot_bb_13TeV   = 0.500; // mb. LHCb ~0.6 [https://journals.aps.org/prl/pdf/10.1103/PhysRevLett.118.052002] FONLL 0.500+-0.113
  const Double_t dsigma_dy_bb_13TeV    = 0.0681 ; //mb | y=0 +22.5-23.8 FONLL extrapolation from 7 TeV to 13 TeV IVAN analysis note
  const Double_t dsigma_dy_bb_13TeVpythia = 0.079 ; //mb | y=0 +-0.014 FROM 13 TeV nominal field HF fit pythia
  const Double_t dsigma_dy_bb_13TeVpowheg = 0.048 ; //mb | y=0 +-0.014 FROM 13 TeV nominal field HF fit powheg
 


  Double_t avoidcompilerwarning = sigma_tot_cc_2760GeV + sigma_tot_cc_7TeV + sigma_tot_cc_5020GeV;
  avoidcompilerwarning += sigma_tot_bb_2760GeV + sigma_tot_bb_7TeV + sigma_tot_bb_5020GeV;

  switch (system) {
    case kpp_MB_7:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kpp_MB_7'     - make sure this is correct!"));
      fCrosssection_pp       = 73.2; // +-2.9 mb
      fCrosssection_event_cc = sigma_tot_cc_7TeV;
      fCrosssection_event_bb = sigma_tot_bb_7TeV;
      // SetNcoll(1); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.0828);
      break;
//    case kpp_EMcal_7:
//      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kpp_EMcal_7'     - make sure this is correct!"));
//      break;
    case kpp_MB_13:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kpp_MB_13'     - make sure this is correct!"));
      fCrosssection_pp       = 57.8; // 78.1+-2.9 mb  ATLAS 13TeV
      fCrosssection_event_cc = sigma_tot_cc_13TeV;
      fCrosssection_event_bb = sigma_tot_bb_13TeV;
      if(fDoNormMidRap){
        std::cout << "enter new mid rap cross sections" << std::endl;
        fCrosssection_event_cc = dsigma_dy_cc_13TeV;
        fCrosssection_event_bb = dsigma_dy_bb_13TeV;
      }
      // SetNcoll(1); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.096); //used by Raphaelle
      //SetForcedBranchingCharmToEle(0.103); //used by Raphaelle
      break;
    case kpp_MB_13pythia:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kpp_MB_13'     - make sure this is correct!"));
      fCrosssection_pp       = 57.8; // 78.1+-2.9 mb  ATLAS 13TeV
      fCrosssection_event_cc = sigma_tot_cc_13TeV;
      fCrosssection_event_bb = sigma_tot_bb_13TeV;
      if(fDoNormMidRap){
        std::cout << "enter new mid rap cross sections" << std::endl;
        fCrosssection_event_cc = dsigma_dy_cc_13TeVpythia;
        fCrosssection_event_bb = dsigma_dy_bb_13TeVpythia;
      }
      // SetNcoll(1); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.096); //used by Raphaelle
      //SetForcedBranchingCharmToEle(0.103); //used by Raphaelle
      break;

    case kpp_MB_13powheg:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kpp_MB_13'     - make sure this is correct!"));
      fCrosssection_pp       = 57.8; // 78.1+-2.9 mb  ATLAS 13TeV
      fCrosssection_event_cc = sigma_tot_cc_13TeV;
      fCrosssection_event_bb = sigma_tot_bb_13TeV;
      if(fDoNormMidRap){
        std::cout << "enter new mid rap cross sections" << std::endl;
        fCrosssection_event_cc = dsigma_dy_cc_13TeVpowheg;
        fCrosssection_event_bb = dsigma_dy_bb_13TeVpowheg;
      }
      // SetNcoll(1); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.096); //used by Raphaelle
      //SetForcedBranchingCharmToEle(0.103); //used by Raphaelle
      break;



    case kpPb_MB_502:
//      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kpPb_MB_502'     - make sure this is correct!"));
//      SetCrosssection_Event(1.215*1.12);  // @ 5.02 TeV
//      SetCrosssection_pp(70.);
//      SetNcoll(6.9);
      SetCrosssection_pp(1.);
      SetNcoll(1.);
      break;
    case kPbPb_0010_276_InputIrem:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_0010_276'     - make sure this is correct!"));
      SetCrosssection_event_cc(2.*0.418989*1.12); //2.*0.418989*1.12; // @ 2.76 TeV
      SetCrosssection_pp(62.8); //62.8; // @ 2.76 TeV
      SetNcoll(1500.5); // from Irem
      break;
    case kPbPb_0010_276:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_0010_276'     - make sure this is correct!"));
      fCrosssection_pp       = 62.8; //62.8 @ 2.76 TeV
      fCrosssection_event_cc = sigma_tot_cc_2760GeV;
      fCrosssection_event_bb = sigma_tot_bb_2760GeV;
      SetNcoll(1500.5); // from Irem
      SetForcedBranchingCharmToEle(0.096); // apply scaling, because we have forced decays in ccbar.
      break;
    case kPbPb_1050_276:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_1050_276'     - make sure this is correct!"));
      fCrosssection_pp       = 62.8; //62.8 @ 2.76 TeV
      fCrosssection_event_cc = sigma_tot_cc_2760GeV;
      fCrosssection_event_bb = sigma_tot_bb_2760GeV;
      SetNcoll(492.2); // from Irem
      SetForcedBranchingCharmToEle(0.096); // apply scaling, because we have forced decays in ccbar.
      break;
    case kPbPb_2050_276:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_2050_276'     - make sure this is correct!"));
      fCrosssection_pp       = 62.8; //62.8 @ 2.76 TeV
      fCrosssection_event_cc = sigma_tot_cc_2760GeV;
      fCrosssection_event_bb = sigma_tot_bb_2760GeV;
      SetNcoll(419.18); // from Irem
      SetForcedBranchingCharmToEle(0.096); // apply scaling, because we have forced decays in ccbar.
      break;

    case kPbPb_0080_5020:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_0080_5020'     - make sure this is correct!"));
      fCrosssection_pp       = 70.; // interpolation from 62.8 @ 2.76 TeV and 73.2 @ 7 TeV https://arxiv.org/pdf/1208.4968.pdf
      fCrosssection_event_cc = dsigma_dy_cc_7TeV * 0.81; // *downscaling from pp@7TeV with FONLL
      // CHARM
      // FONLL 7 TeV dsigma/dy:    central=0.573 min=0.166 max=1.25
      // FONLL 5.02 TeV dsigma/dy: central=0.463 min=0.149 max=1.05
      // Scaling 5.02/7:           central=0.81  min=0.89  max=0.84 // Normalization uncertainty from last two values ==> 8%
      // fCrosssection_event_cc = sigma_tot_cc_5020GeV;

      fCrosssection_event_bb = sigma_tot_bb_7TeV * 0.77;
      // BOTTOM
      // FONLL 7    TeV dsigma/dy: central=3.82 min=2.35 max=5.63
      // FONLL 5.02 TeV dsigma/dy: central=2.93 min=1.85 max=4.26
      // Scaling 5.02/7:           central=0.77 min=0.78 max=0.76
      // fCrosssection_event_bb = sigma_tot_bb_5020GeV;
      SetNcoll(488.9); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.096);
      break;
    case kPbPb_0010_5020:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_0010_5020'     - make sure this is correct!"));
      fCrosssection_pp       = 70.; // interpolation from 62.8 @ 2.76 TeV and 73.2 @ 7 TeV https://arxiv.org/pdf/1208.4968.pdf
      fCrosssection_event_cc = dsigma_dy_cc_7TeV * 0.81; // *downscaling from pp@7TeV with FONLL
      // CHARM
      // FONLL 7 TeV dsigma/dy:    central=0.573 min=0.166 max=1.25
      // FONLL 5.02 TeV dsigma/dy: central=0.463 min=0.149 max=1.05
      // Scaling 5.02/7:           central=0.81  min=0.89  max=0.84 // Normalization uncertainty from last two values ==> 8%
      // fCrosssection_event_cc = sigma_tot_cc_5020GeV;

      fCrosssection_event_bb = sigma_tot_bb_7TeV * 0.77;
      // BOTTOM
      // FONLL 7    TeV dsigma/dy: central=3.82 min=2.35 max=5.63
      // FONLL 5.02 TeV dsigma/dy: central=2.93 min=1.85 max=4.26
      // Scaling 5.02/7:           central=0.77 min=0.78 max=0.76
      // fCrosssection_event_bb = sigma_tot_bb_5020GeV;
      SetNcoll(1636); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.096);
      break;
    case kPbPb_1050_5020:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_1050_5020'     - make sure this is correct!"));
      fCrosssection_pp       = 70.; // interpolation from 62.8 @ 2.76 TeV and 73.2 @ 7 TeV https://arxiv.org/pdf/1208.4968.pdf
      fCrosssection_event_cc = dsigma_dy_cc_7TeV * 0.81; // *downscaling from pp@7TeV with FONLL
      // CHARM
      // FONLL 7 TeV dsigma/dy:    central=0.573 min=0.166 max=1.25
      // FONLL 5.02 TeV dsigma/dy: central=0.463 min=0.149 max=1.05
      // Scaling 5.02/7:           central=0.81  min=0.89  max=0.84 // Normalization uncertainty from last two values ==> 8%
      // fCrosssection_event_cc = sigma_tot_cc_5020GeV;

      fCrosssection_event_bb = sigma_tot_bb_7TeV * 0.77;
      // BOTTOM
      // FONLL 7    TeV dsigma/dy: central=3.82 min=2.35 max=5.63
      // FONLL 5.02 TeV dsigma/dy: central=2.93 min=1.85 max=4.26
      // Scaling 5.02/7:           central=0.77 min=0.78 max=0.76
      // fCrosssection_event_bb = sigma_tot_bb_5020GeV;
      SetNcoll(532.25); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.096);
      break;
    case kPbPb_5080_5020:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_5080_5020'     - make sure this is correct!"));
      fCrosssection_pp       = 70.; // interpolation from 62.8 @ 2.76 TeV and 73.2 @ 7 TeV https://arxiv.org/pdf/1208.4968.pdf
      fCrosssection_event_cc = dsigma_dy_cc_7TeV * 0.81; // *downscaling from pp@7TeV with FONLL
      // CHARM
      // FONLL 7 TeV dsigma/dy:    central=0.573 min=0.166 max=1.25
      // FONLL 5.02 TeV dsigma/dy: central=0.463 min=0.149 max=1.05
      // Scaling 5.02/7:           central=0.81  min=0.89  max=0.84 // Normalization uncertainty from last two values ==> 8%
      // fCrosssection_event_cc = sigma_tot_cc_5020GeV;

      fCrosssection_event_bb = sigma_tot_bb_7TeV * 0.77;
      // BOTTOM
      // FONLL 7    TeV dsigma/dy: central=3.82 min=2.35 max=5.63
      // FONLL 5.02 TeV dsigma/dy: central=2.93 min=1.85 max=4.26
      // Scaling 5.02/7:           central=0.77 min=0.78 max=0.76
      // fCrosssection_event_bb = sigma_tot_bb_5020GeV;
      SetNcoll(48.6); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      // SetNcoll(1); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.096);
      // SetForcedBranchingCharmToEle(0.0828);
      break;
    case kPbPb_0020_5020:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_0020_5020'     - make sure this is correct!"));
      fCrosssection_pp       = 70.; // interpolation from 62.8 @ 2.76 TeV and 73.2 @ 7 TeV https://arxiv.org/pdf/1208.4968.pdf
      fCrosssection_event_cc = dsigma_dy_cc_7TeV * 0.81; // *downscaling from pp@7TeV with FONLL
      // CHARM
      // FONLL 7 TeV dsigma/dy:    central=0.573 min=0.166 max=1.25
      // FONLL 5.02 TeV dsigma/dy: central=0.463 min=0.149 max=1.05
      // Scaling 5.02/7:           central=0.81  min=0.89  max=0.84 // Normalization uncertainty from last two values ==> 8%
      // fCrosssection_event_cc = sigma_tot_cc_5020GeV;

      fCrosssection_event_bb = sigma_tot_bb_7TeV * 0.77;
      // BOTTOM
      // FONLL 7    TeV dsigma/dy: central=3.82 min=2.35 max=5.63
      // FONLL 5.02 TeV dsigma/dy: central=2.93 min=1.85 max=4.26
      // Scaling 5.02/7:           central=0.77 min=0.78 max=0.76
      // fCrosssection_event_bb = sigma_tot_bb_5020GeV;
      SetNcoll(1318.5); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      // SetNcoll(1); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.096);
      // SetForcedBranchingCharmToEle(0.0828);
      break;
    case kPbPb_2040_5020:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_2040_5020'     - make sure this is correct!"));
      fCrosssection_pp       = 70.; // interpolation from 62.8 @ 2.76 TeV and 73.2 @ 7 TeV https://arxiv.org/pdf/1208.4968.pdf
      fCrosssection_event_cc = dsigma_dy_cc_7TeV * 0.81; // *downscaling from pp@7TeV with FONLL
      // CHARM
      // FONLL 7 TeV dsigma/dy:    central=0.573 min=0.166 max=1.25
      // FONLL 5.02 TeV dsigma/dy: central=0.463 min=0.149 max=1.05
      // Scaling 5.02/7:           central=0.81  min=0.89  max=0.84 // Normalization uncertainty from last two values ==> 8%
      // fCrosssection_event_cc = sigma_tot_cc_5020GeV;

      fCrosssection_event_bb = sigma_tot_bb_7TeV * 0.77;
      // BOTTOM
      // FONLL 7    TeV dsigma/dy: central=3.82 min=2.35 max=5.63
      // FONLL 5.02 TeV dsigma/dy: central=2.93 min=1.85 max=4.26
      // Scaling 5.02/7:           central=0.77 min=0.78 max=0.76
      // fCrosssection_event_bb = sigma_tot_bb_5020GeV;
      SetNcoll(472.5); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      // SetNcoll(1); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.096);
      // SetForcedBranchingCharmToEle(0.0828);
      break;
    case kPbPb_4080_5020:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_4080_5020'     - make sure this is correct!"));
      fCrosssection_pp       = 70.; // interpolation from 62.8 @ 2.76 TeV and 73.2 @ 7 TeV https://arxiv.org/pdf/1208.4968.pdf
      fCrosssection_event_cc = dsigma_dy_cc_7TeV * 0.81; // *downscaling from pp@7TeV with FONLL
      // CHARM
      // FONLL 7 TeV dsigma/dy:    central=0.573 min=0.166 max=1.25
      // FONLL 5.02 TeV dsigma/dy: central=0.463 min=0.149 max=1.05
      // Scaling 5.02/7:           central=0.81  min=0.89  max=0.84 // Normalization uncertainty from last two values ==> 8%
      // fCrosssection_event_cc = sigma_tot_cc_5020GeV;

      fCrosssection_event_bb = sigma_tot_bb_7TeV * 0.77;
      // BOTTOM
      // FONLL 7    TeV dsigma/dy: central=3.82 min=2.35 max=5.63
      // FONLL 5.02 TeV dsigma/dy: central=2.93 min=1.85 max=4.26
      // Scaling 5.02/7:           central=0.77 min=0.78 max=0.76
      // fCrosssection_event_bb = sigma_tot_bb_5020GeV;
      SetNcoll(82.2); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      // SetNcoll(1); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.096);
      // SetForcedBranchingCharmToEle(0.0828);
      break;
    case kPbPb_1020_5020:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_1020_5020'     - make sure this is correct!"));
      fCrosssection_pp       = 70.; // interpolation from 62.8 @ 2.76 TeV and 73.2 @ 7 TeV https://arxiv.org/pdf/1208.4968.pdf
      fCrosssection_event_cc = dsigma_dy_cc_7TeV * 0.81; // *downscaling from pp@7TeV with FONLL
      // CHARM
      // FONLL 7 TeV dsigma/dy:    central=0.573 min=0.166 max=1.25
      // FONLL 5.02 TeV dsigma/dy: central=0.463 min=0.149 max=1.05
      // Scaling 5.02/7:           central=0.81  min=0.89  max=0.84 // Normalization uncertainty from last two values ==> 8%
      // fCrosssection_event_cc = sigma_tot_cc_5020GeV;

      fCrosssection_event_bb = sigma_tot_bb_7TeV * 0.77;
      // BOTTOM
      // FONLL 7    TeV dsigma/dy: central=3.82 min=2.35 max=5.63
      // FONLL 5.02 TeV dsigma/dy: central=2.93 min=1.85 max=4.26
      // Scaling 5.02/7:           central=0.77 min=0.78 max=0.76
      // fCrosssection_event_bb = sigma_tot_bb_5020GeV;
      SetNcoll(1001); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      // SetNcoll(1); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.096);
      // SetForcedBranchingCharmToEle(0.0828);
      break;
    case kPbPb_4050_5020:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_4050_5020'     - make sure this is correct!"));
      fCrosssection_pp       = 70.; // interpolation from 62.8 @ 2.76 TeV and 73.2 @ 7 TeV https://arxiv.org/pdf/1208.4968.pdf
      fCrosssection_event_cc = dsigma_dy_cc_7TeV * 0.81; // *downscaling from pp@7TeV with FONLL
      // CHARM
      // FONLL 7 TeV dsigma/dy:    central=0.573 min=0.166 max=1.25
      // FONLL 5.02 TeV dsigma/dy: central=0.463 min=0.149 max=1.05
      // Scaling 5.02/7:           central=0.81  min=0.89  max=0.84 // Normalization uncertainty from last two values ==> 8%
      // fCrosssection_event_cc = sigma_tot_cc_5020GeV;

      fCrosssection_event_bb = sigma_tot_bb_7TeV * 0.77;
      // BOTTOM
      // FONLL 7    TeV dsigma/dy: central=3.82 min=2.35 max=5.63
      // FONLL 5.02 TeV dsigma/dy: central=2.93 min=1.85 max=4.26
      // Scaling 5.02/7:           central=0.77 min=0.78 max=0.76
      // fCrosssection_event_bb = sigma_tot_bb_5020GeV;
      SetNcoll(183); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.096);
      // SetForcedBranchingCharmToEle(0.0828);
      break;
    case kPbPb_5060_5020:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_5060_5020'     - make sure this is correct!"));
      fCrosssection_pp       = 70.; // interpolation from 62.8 @ 2.76 TeV and 73.2 @ 7 TeV https://arxiv.org/pdf/1208.4968.pdf
      fCrosssection_event_cc = dsigma_dy_cc_7TeV * 0.81; // *downscaling from pp@7TeV with FONLL
      // CHARM
      // FONLL 7 TeV dsigma/dy:    central=0.573 min=0.166 max=1.25
      // FONLL 5.02 TeV dsigma/dy: central=0.463 min=0.149 max=1.05
      // Scaling 5.02/7:           central=0.81  min=0.89  max=0.84 // Normalization uncertainty from last two values ==> 8%
      // fCrosssection_event_cc = sigma_tot_cc_5020GeV;

      fCrosssection_event_bb = sigma_tot_bb_7TeV * 0.77;
      // BOTTOM
      // FONLL 7    TeV dsigma/dy: central=3.82 min=2.35 max=5.63
      // FONLL 5.02 TeV dsigma/dy: central=2.93 min=1.85 max=4.26
      // Scaling 5.02/7:           central=0.77 min=0.78 max=0.76
      // fCrosssection_event_bb = sigma_tot_bb_5020GeV;
      SetNcoll(89.8); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.096);
      // SetForcedBranchingCharmToEle(0.0828);
      break;
    case kPbPb_6080_5020:
      LmHelper::Info(Form("LmCocktail: creating Cocktail for system:     'kPbPb_6080_5020'     - make sure this is correct!"));
      fCrosssection_pp       = 70.; // interpolation from 62.8 @ 2.76 TeV and 73.2 @ 7 TeV https://arxiv.org/pdf/1208.4968.pdf
      fCrosssection_event_cc = dsigma_dy_cc_7TeV * 0.81; // *downscaling from pp@7TeV with FONLL
      // CHARM
      // FONLL 7 TeV dsigma/dy:    central=0.573 min=0.166 max=1.25
      // FONLL 5.02 TeV dsigma/dy: central=0.463 min=0.149 max=1.05
      // Scaling 5.02/7:           central=0.81  min=0.89  max=0.84 // Normalization uncertainty from last two values ==> 8%
      // fCrosssection_event_cc = sigma_tot_cc_5020GeV;

      fCrosssection_event_bb = sigma_tot_bb_7TeV * 0.77;
      // BOTTOM
      // FONLL 7    TeV dsigma/dy: central=3.82 min=2.35 max=5.63
      // FONLL 5.02 TeV dsigma/dy: central=2.93 min=1.85 max=4.26
      // Scaling 5.02/7:           central=0.77 min=0.78 max=0.76
      // fCrosssection_event_bb = sigma_tot_bb_5020GeV;
      SetNcoll(56); // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentralityCodeSnippets
      SetForcedBranchingCharmToEle(0.096);
      // SetForcedBranchingCharmToEle(0.0828);
      break;
    case kUndef:
      LmHelper::Info(Form("LmCocktail: creating Cocktail without system. You need to set cross sections and Ncolls by hand or implement them!"));
      break;
    default:
      LmHelper::Error(Form("LmCocktail: no cocktail available for system number %i!", system));
      break;
  }

  if (fBranchingCharmToEle !=1.) LmHelper::Info(Form("LmCocktail: assuming forced decays of c-cbar, correcting with given branching ratio."));
  if (fBranchingBeautyToEle!=1.) LmHelper::Info(Form("LmCocktail: assuming forced decays of b-bbar, correcting with given branching ratio."));
}

//_______________________________________________________________________________________________
LmCocktail::~LmCocktail()
{
  LmHelper::Debug("LmCocktail destructor", 5);
}

//_______________________________________________________________________________________________
Int_t LmCocktail::Process(Int_t type)
{
  LmHelper::Debug(Form("LmCocktail Process(type=%d)", type), 5);
  fType=type;
  // The sum is attached in the constructor, so that it will always be the first vector element, no matter which cocktail type is used.
  //LmCocktailPart* partSum = new LmCocktailPart("cocktail sum"); // if we put it inside a switch case, then we need curly brackets!
  //AttachPart( *partSum ); // placeholder for sum as first vector element. Initially it will have the type LmCocktailPart::kUndef.

  fLmCocktailPart.at(0) -> SetName(fName);
  fLmCocktailPart.at(0) -> SetDoNormCrossSection(fDoNormCrossSection);
  fLmCocktailPart.at(0) -> SetCrossSection(fCrossSection);
  fLmCocktailPart.at(0) -> SetDoNormBinwidth(fDoNormBinwidth);
  //fLmCocktailPart.at(0) -> SetDoNormNevents(fDoNormNevents);
  
  switch (type) {
    case kFromManagers: // = kStd:
    {
      if (fLmCocktailMan.size()==0) { LmHelper::Error(Form("LmCocktail::Process(): no cocktail managers available! (name: '%s')", GetName())); return 1; }

      for (unsigned int iMan=0; iMan<fLmCocktailMan.size(); iMan++)
      {
        if (fLmCocktailMan.at(iMan)==0x0) { LmHelper::Error(Form("LmCocktail::Process(): nullpointer attached (LmCocktailMan '%d'). Skip. (name: '%s')", iMan, GetName())); continue; }

        for (Int_t iSpec=0; iSpec<fLmCocktailMan.at(iMan)->GetNEntries(); iSpec++)
        {
          // Create copies of histograms from manager.
          // (Previously we used the pointers directly, but using hTemp->Scale() in cc and bb modifies the managers
          //  contents, so if a manager is used for two cocktails or a cocktail is processed twice, we mess up!)
          TH2D*           hTemp     = new TH2D(*(fLmCocktailMan.at(iMan)->GetSpectrumI(iSpec)));
          TH2D*           hTempLow  = 0x0;
          TH2D*           hTempHigh = 0x0;
          if (fLmCocktailMan.at(iMan)->GetSpectrumILow(iSpec))  hTempLow  = new TH2D(*(fLmCocktailMan.at(iMan)->GetSpectrumILow(iSpec)));
          if (fLmCocktailMan.at(iMan)->GetSpectrumIHigh(iSpec)) hTempHigh = new TH2D(*(fLmCocktailMan.at(iMan)->GetSpectrumIHigh(iSpec)));
          TString         histName = hTemp->GetName();
          LmCocktailPart* partTemp = new LmCocktailPart();
	  std::cout << "DoNormCrossSection: "  << fDoNormCrossSection << "  CrossSection: " << fCrossSection << "  DoNormBinWidth: " << fDoNormBinwidth << std::endl; 
          partTemp -> SetDoNormCrossSection(fDoNormCrossSection);
          partTemp -> SetCrossSection(fCrossSection);
          partTemp -> SetDoNormBinwidth(fDoNormBinwidth);
          //partTemp -> SetDoNormNevents(fDoNormNevents);
          //
          // MAKE SURE to put more extended particle names before the shorter ones in this swith block!
          // (like 'EtaPrime' before 'Eta', 'OmegaDalitz' before 'Omega')
          //
          // The legend entry names are now set during LmCocktailPart::Process().
          //
          if (histName.Contains("LFsum", TString::kIgnoreCase)) {
            hTemp->Scale(fLFscaling);
            partTemp->SetSpectrum2D(hTemp); // using copy constructor of TH2D.
            //partTemp->SetCrossSection(fLFscaling);
            partTemp->Process(LmCocktailPart::kLF);
          }
          else if (histName.Contains("Pion", TString::kIgnoreCase) || histName.Contains("pi0", TString::kIgnoreCase)) {
            hTemp->Scale(fLFscaling);
            partTemp->SetSpectrum2D(hTemp);
            //partTemp->SetCrossSection(fLFscaling);
            partTemp->Process(LmCocktailPart::kPion);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("EtaPrime", TString::kIgnoreCase) || histName.Contains("EtaP", TString::kIgnoreCase)) {
            hTemp->Scale(fLFscaling);
            partTemp->SetSpectrum2D(hTemp);
            //partTemp->SetCrossSection(fLFscaling);
            partTemp->Process(LmCocktailPart::kEtaPrime);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("Eta", TString::kIgnoreCase)) {
            hTemp->Scale(fLFscaling);
            partTemp->SetSpectrum2D(hTemp);
            //partTemp->SetCrossSection(fLFscaling);
            partTemp->Process(LmCocktailPart::kEta);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
	    //cout << "Eta cocktail sys: " << partTemp << "  " << hTempLow << "  " << hTempHigh << std::endl;
          }
          else if (histName.Contains("Rho", TString::kIgnoreCase)) {
            hTemp->Scale(fLFscaling);
            partTemp->SetSpectrum2D(hTemp);
            //partTemp->SetCrossSection(fLFscaling);
            partTemp->Process(LmCocktailPart::kRho);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("OmegaDalitz", TString::kIgnoreCase)) { // "OmegaDalitz" has to be checked before "Omega"
            hTemp->Scale(fLFscaling);
            AddHistToParticle(hTemp, LmCocktailPart::kOmega);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("Omega", TString::kIgnoreCase)) {
            hTemp->Scale(fLFscaling);
            partTemp->SetSpectrum2D(hTemp);
            //partTemp->SetCrossSection(fLFscaling);
            partTemp->Process(LmCocktailPart::kOmega);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("PhiDalitz", TString::kIgnoreCase)) {  // "PhiDalitz" has to be checked before "Phi"
            hTemp->Scale(fLFscaling);
            AddHistToParticle(hTemp, LmCocktailPart::kPhi);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("Phi", TString::kIgnoreCase)) {
            hTemp->Scale(fLFscaling);
            partTemp->SetSpectrum2D(hTemp);
            //partTemp->SetCrossSection(fLFscaling);
            partTemp->Process(LmCocktailPart::kPhi);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("JPsiDalitz", TString::kIgnoreCase)) {
            AddHistToParticle(hTemp, LmCocktailPart::kJPsi);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("JPsi", TString::kIgnoreCase)) {
            partTemp->SetName("J/#psi #rightarrow ee, J/#psi #rightarrow #gammaee");
            partTemp->SetSpectrum2D(hTemp);
            partTemp->Process(LmCocktailPart::kJPsi);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          // Rapp:
          else if (histName.Contains("HGvac", TString::kIgnoreCase)) {
            partTemp->SetSpectrum2D(hTemp);
            partTemp->Process(LmCocktailPart::kHGvac);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("HGmed", TString::kIgnoreCase)) {
            partTemp->SetSpectrum2D(hTemp);
            partTemp->Process(LmCocktailPart::kHGmed);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("HGdrop", TString::kIgnoreCase)) {
            partTemp->SetSpectrum2D(hTemp);
            partTemp->Process(LmCocktailPart::kHGdrop);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("QGP", TString::kIgnoreCase)) {
            partTemp->SetSpectrum2D(hTemp);
            partTemp->Process(LmCocktailPart::kQGP);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("Photon", TString::kIgnoreCase)) {
            partTemp->SetSpectrum2D(hTemp);
            partTemp->Process(LmCocktailPart::kVirtGamma);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("HadrBrems", TString::kIgnoreCase)) {
            partTemp->SetSpectrum2D(hTemp);
            partTemp->Process(LmCocktailPart::kHadrBrems);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("RappSumUnc", TString::kIgnoreCase)) {
            partTemp->SetSpectrum2D(hTemp);
            partTemp->Process(LmCocktailPart::kRappSumUnc);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("RappSum", TString::kIgnoreCase)) {
            partTemp->SetSpectrum2D(hTemp);
            partTemp->Process(LmCocktailPart::kRappSum);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else if (histName.Contains("SmashSum", TString::kIgnoreCase)) {
            partTemp->SetSpectrum2D(hTemp);
            partTemp->Process(LmCocktailPart::kSmashSum);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          // charm:
          else if (histName.Contains("charm", TString::kIgnoreCase) || histName.Contains("ccbar", TString::kIgnoreCase)
                   || histName.Contains("hpt_mass4", TString::kIgnoreCase)/*still needed for patrick*/ ) {
            // calculation based on Irems cocktail plotting macro:
            std::cout << "using cross section: " << fCrosssection_event_cc << "   " << fBranchingCharmToEle << "   " << fCrosssection_pp << "   " << fNcoll << "   " << fDoNormMidRap << std::endl;
            Double_t Nevt_Charm     = 1.; // Must be normalized in LmCocktailMan. //fLmCocktailMan.at(iMan)->GetNeventsHF(iSpec);
            Double_t Ldt0_Charm     = Nevt_Charm/fCrosssection_event_cc;
            Double_t Ldt_Charm      = Ldt0_Charm/fBranchingCharmToEle/fBranchingCharmToEle;
            Double_t Nevt_cc        = Ldt_Charm*fCrosssection_pp;
            Double_t scaling_Charm  = 1./Nevt_cc; // "normalize as per pp collision"
            scaling_Charm *= fNcoll;
            hTemp->Scale(scaling_Charm);
            if(hTempLow){
              hTempLow ->Scale(scaling_Charm);
              partTemp->SetSpectrum2DLow(hTempLow);
            }
            else{
              partTemp->SetSpectrum2DLow(hTemp);
            }
            if(hTempHigh) {
              hTempHigh->Scale(scaling_Charm);
              partTemp->SetSpectrum2DHigh(hTempHigh);
            }
            else{
              partTemp->SetSpectrum2DHigh(hTemp);
            }
            partTemp->SetSpectrum2D(hTemp);
            partTemp->Process(LmCocktailPart::kCharm);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          // beauty:
          else if (histName.Contains("beauty", TString::kIgnoreCase) || histName.Contains("bbbar", TString::kIgnoreCase)) {
            // calculation based on Irems cocktail plotting macro:
            Double_t Nevt_Beauty    = 1.; // Must be normalized in LmCocktailMan. //fLmCocktailMan.at(iMan)->GetNeventsHF(iSpec);
            Double_t Ldt0_Beauty    = Nevt_Beauty/fCrosssection_event_bb;
            Double_t Ldt_Beauty     = Ldt0_Beauty/fBranchingBeautyToEle/fBranchingBeautyToEle;
            Double_t Nevt_bb        = Ldt_Beauty*fCrosssection_pp;
            Double_t scaling_Beauty = 1./Nevt_bb; // "normalize as per pp collision"
            scaling_Beauty *= fNcoll;
            hTemp->Scale(scaling_Beauty);
            if(hTempLow){
              hTempLow ->Scale(scaling_Beauty);
              partTemp->SetSpectrum2DLow(hTempLow);
            }
            else{
              partTemp->SetSpectrum2DLow(hTemp);
            }
            if(hTempHigh) {
              hTempHigh->Scale(scaling_Beauty);
              partTemp->SetSpectrum2DHigh(hTempHigh);
            }
            else{
              partTemp->SetSpectrum2DHigh(hTemp);
            }
            partTemp->SetSpectrum2D(hTemp);
            partTemp->Process(LmCocktailPart::kBeauty);
            ApplySysRelUncertainties(partTemp, hTempLow, hTempHigh);
          }
          else {
            LmHelper::Error(Form("LmCocktail::Process(): unforeseen cocktail histogram named %s!",histName.Data()));
            delete hTemp; if(hTempLow)delete hTempLow; if(hTempHigh)delete hTempHigh;
            continue; /*return 1;*/
          }

          // the following if clause is needed to make sure that branching ratio and mt-scaling
          // for light flavour is kept even when no uncertainty for parametrization is given
          if (partTemp->GetSpectrum2DLow() != 0x0 && partTemp->GetSpectrum2DHigh() != 0x0){
            hTempLow = dynamic_cast<TH2D*>( partTemp->GetSpectrum2DLow()->Clone("low"));
            hTempHigh= dynamic_cast<TH2D*>(partTemp->GetSpectrum2DHigh()->Clone("high"));
          }

          if (partTemp->GetType()!=LmCocktailPart::kUndef) {
            bool addParticle = true;
            for (unsigned int k = 0; k < fLmCocktailPart.size(); ++k){
              if(partTemp->GetType() == fLmCocktailPart.at(k)->GetType()) addParticle = false;
            }
            if (addParticle){
              AttachPart( *partTemp );
            }
          }
          else delete partTemp; // without else, this deletes also the content of std::vector fLmCocktailPart...

          delete hTemp; if(hTempLow)delete hTempLow; if(hTempHigh)delete hTempHigh;
        } // Spectra
      } // Managers



      // Adding up all particles with correct systematic uncertainty. Each uncertainty is quadratically added weighted with their yield per particle.
      // eg: sqrt(x*BR_part1^2 + (1-x)*BR_part2^2) with x=[0;1]. Same for MT and additional uncertainties. Afterwards all uncertainties are quadratically
      // added to construct sum of all errors
      std::vector<TH2D> vec_central;

      LmCocktailPart* sum = fLmCocktailPart.at(0);
      TH2D sum_dummy;// = *(dynamic_cast<TH2D*>(sum->GetSpectrum2D()->Clone("dummy")));

      // add this as a dummy for the sum
      vec_central.push_back(sum_dummy);

      for (unsigned int i = 1; i < fLmCocktailPart.size(); ++i){
        LmCocktailPart* part_i = fLmCocktailPart.at(i);
        TH2D central = *(part_i->GetSpectrum2DCopy());
        TH2D central_low  = *(part_i->GetSpectrum2DLowCopy());
        TH2D central_high = *(part_i->GetSpectrum2DHighCopy());

        if (sum->GetType()==LmCocktailPart::kUndef) { // First particle to add to sum
          sum->SetSpectrum2D(&central);
          sum->SetSpectrum2DLow(&central_low);
          sum->SetSpectrum2DHigh(&central_high);
          sum->Process(LmCocktailPart::kSum); // needed to set the type from kUndef to kSum.
        }
        else { // Add all other particles to the sum
          sum->GetSpectrum2D()->Add(&central);
          sum->GetSpectrum2DLow() ->Add(&central_low);
          sum->GetSpectrum2DHigh()->Add(&central_high);
        }
        vec_central.push_back( central );
      }
      fLmCocktailPart.at(0)->Process(LmCocktailPart::kSum); // not really needed again, as long as just styles are updated.

      fCentral      = (sum->GetSpectrum2DCopy());
      fCentral_low  = (sum->GetSpectrum2DCopy());
      fCentral_high = (sum->GetSpectrum2DCopy());
      fRel_para_low = (sum->GetSpectrum2DCopy());
      fRel_para_high= (sum->GetSpectrum2DCopy());
      fRel_MT_low   = (sum->GetSpectrum2DCopy());
      fRel_MT_high  = (sum->GetSpectrum2DCopy());
      fRel_BR_low   = (sum->GetSpectrum2DCopy());
      fRel_BR_high  = (sum->GetSpectrum2DCopy());
      fRel_Add_low  = (sum->GetSpectrum2DCopy());
      fRel_Add_high = (sum->GetSpectrum2DCopy());

      // Actual calculations for the sum

      for (int mee = 0; mee < fCentral->GetNbinsX(); ++mee){
        for (int ptee = 0; ptee < fCentral->GetNbinsY(); ++ptee){

	  //std::cout << "mee: " << fCentral->GetXaxis()->GetBinCenter(mee) << "  ptee: " << fCentral->GetXaxis()->GetBinCenter(ptee) << endl; 
          double weighted_unc_i_para_low  = 0;
          double weighted_unc_i_para_high = 0;
          double weighted_unc_i_MT_low    = 0;
          double weighted_unc_i_MT_high   = 0;
          double weighted_unc_i_BR_low    = 0;
          double weighted_unc_i_BR_high   = 0;
          double weighted_unc_i_Add_low   = 0;
          double weighted_unc_i_Add_high  = 0;
          double bin_central  = fCentral->GetBinContent(mee, ptee);
          if (bin_central != 0){
            for (unsigned int part_i = 1; part_i < fLmCocktailPart.size(); ++part_i){
              double central_value = fCentral->GetBinContent(mee, ptee);
              double central_value_i = fLmCocktailPart.at(part_i)->GetSpectrum2D() ->GetBinContent(mee, ptee);
              double para_low_i  = 0;
              double para_high_i = 0; 

              if (central_value_i != 0 && fCentral->GetXaxis()->GetBinCenter(mee) < 1.5 && fLmCocktailPart.at(part_i)->GetSpectrum2DLow()  && fLmCocktailPart.at(part_i)->GetSpectrum2DHigh() ){  // fix fuer null-safety
                para_low_i  = TMath::Abs((fLmCocktailPart.at(part_i)->GetSpectrum2DLow() ->GetBinContent(mee, ptee) / central_value_i) - 1.);
                para_high_i = TMath::Abs((fLmCocktailPart.at(part_i)->GetSpectrum2DHigh()->GetBinContent(mee, ptee) / central_value_i) - 1.);

                //if(part_i < 3) std::cout << "uncertainty calc new: " << fLmCocktailPart.at(part_i)->GetName() << " " << para_low_i << "  " << para_high_i  <<  std::endl;
		//para_low_i = sqrt(para_low_i * para_low_i + fLmCocktailPart.at(part_i)->GetParamRelUncertainty()[0]*fLmCocktailPart.at(part_i)->GetParamRelUncertainty()[0] );
		//para_high_i = sqrt(para_high_i * para_high_i + fLmCocktailPart.at(part_i)->GetParamRelUncertainty()[1]*fLmCocktailPart.at(part_i)->GetParamRelUncertainty()[1] );
               //if(part_i < 3) std::cout << "uncertainty calc new: " << fLmCocktailPart.at(part_i)->GetName() << " " << fLmCocktailPart.at(part_i)->GetParamRelUncertainty()[0] << "  " << fLmCocktailPart.at(part_i)->GetParamRelUncertainty()[1]  <<  std::endl;
                 para_low_i = para_low_i - fLmCocktailPart.at(part_i)->GetParamRelUncertainty()[0];
		para_high_i = para_high_i + fLmCocktailPart.at(part_i)->GetParamRelUncertainty()[1] ;
               //if(part_i < 3) std::cout << "uncertainty calc new: " << fLmCocktailPart.at(part_i)->GetName() << " " << para_low_i << "  " << para_high_i  <<  std::endl;


		//para_low_i
              }
	      else{
                 //if(part_i < 3)std::cout << "uncertainty calc old: " << fLmCocktailPart.at(part_i)->GetName() <<  std::endl;

                para_low_i  = fLmCocktailPart.at(part_i)->GetParamRelUncertainty()[0];
                para_high_i = fLmCocktailPart.at(part_i)->GetParamRelUncertainty()[1];
              }

              double mt_low_i    = fLmCocktailPart.at(part_i)->GetMTscalingRelUncertainty()[0];
              double mt_high_i   = fLmCocktailPart.at(part_i)->GetMTscalingRelUncertainty()[1];
              double br_low_i    = fLmCocktailPart.at(part_i)->GetBRRelUncertainty()[0];
              double br_high_i   = fLmCocktailPart.at(part_i)->GetBRRelUncertainty()[1];
              double add_low_i   = fLmCocktailPart.at(part_i)->GetAdditionalRelUncertainty()[0];
              double add_high_i  = fLmCocktailPart.at(part_i)->GetAdditionalRelUncertainty()[1];

              double frac_of_sum = vec_central.at(part_i).GetBinContent(mee, ptee) / central_value;
              frac_of_sum = TMath::Abs(frac_of_sum);
              frac_of_sum *= frac_of_sum;

              if (central_value_i != 0 && fCentral->GetXaxis()->GetBinCenter(mee) < 1.5 && fLmCocktailPart.at(part_i)->GetSpectrum2DLow()  && fLmCocktailPart.at(part_i)->GetSpectrum2DHigh() ){  // fix fuer null-safety
	      //  if(part_i < 3)  std::cout << "Fraction of sum: " << frac_of_sum << std::endl;
	      }
              para_low_i  *= para_low_i;
              para_high_i *= para_high_i;
              mt_low_i    *= mt_low_i;
              mt_high_i   *= mt_high_i;
              br_low_i    *= br_low_i;
              br_high_i   *= br_high_i;
              add_low_i   *= add_low_i;
              add_high_i  *= add_high_i;
              weighted_unc_i_para_low  += para_low_i   * frac_of_sum;
              weighted_unc_i_para_high += para_high_i  * frac_of_sum;
              weighted_unc_i_MT_low    += mt_low_i   * frac_of_sum;
              weighted_unc_i_MT_high   += mt_high_i  * frac_of_sum;
              weighted_unc_i_BR_low    += br_low_i   * frac_of_sum;
              weighted_unc_i_BR_high   += br_high_i  * frac_of_sum;
              weighted_unc_i_Add_low   += add_low_i  * frac_of_sum;
              weighted_unc_i_Add_high  += add_high_i * frac_of_sum;
            }
          }
          //
          weighted_unc_i_para_low  = TMath::Sqrt(weighted_unc_i_para_low);
          weighted_unc_i_para_high = TMath::Sqrt(weighted_unc_i_para_high);
          weighted_unc_i_MT_low    = TMath::Sqrt(weighted_unc_i_MT_low);
          weighted_unc_i_MT_high   = TMath::Sqrt(weighted_unc_i_MT_high);
          weighted_unc_i_BR_low    = TMath::Sqrt(weighted_unc_i_BR_low);
          weighted_unc_i_BR_high   = TMath::Sqrt(weighted_unc_i_BR_high);
          weighted_unc_i_Add_low   = TMath::Sqrt(weighted_unc_i_Add_low);
          weighted_unc_i_Add_high  = TMath::Sqrt(weighted_unc_i_Add_high);

          double bin_para_low  = bin_central * (1 - weighted_unc_i_para_low);
          double bin_para_high = bin_central * (1 + weighted_unc_i_para_high);
          fRel_para_low-> SetBinContent(mee, ptee, bin_para_low);
          fRel_para_high->SetBinContent(mee, ptee, bin_para_high);
          double bin_MT_low  = bin_central * (1 - weighted_unc_i_MT_low);
          double bin_MT_high = bin_central * (1 + weighted_unc_i_MT_high);
          fRel_MT_low-> SetBinContent(mee, ptee, bin_MT_low);
          fRel_MT_high->SetBinContent(mee, ptee, bin_MT_high);
          double bin_BR_low  = bin_central * (1 - weighted_unc_i_BR_low);
          double bin_BR_high = bin_central * (1 + weighted_unc_i_BR_high);
          fRel_BR_low-> SetBinContent(mee, ptee, bin_BR_low);
          fRel_BR_high->SetBinContent(mee, ptee, bin_BR_high);
          double bin_Add_low  = bin_central * (1 - weighted_unc_i_Add_low);
          double bin_Add_high = bin_central * (1 + weighted_unc_i_Add_high);
          fRel_Add_low-> SetBinContent(mee, ptee, bin_Add_low);
          fRel_Add_high->SetBinContent(mee, ptee, bin_Add_high);
        }
      }

      // quadratic sum of all error bands
      for (int mee = 0; mee < fCentral->GetNbinsX(); ++mee){
        for (int ptee = 0; ptee < fCentral->GetNbinsY(); ++ptee){
          double central_value = fCentral->GetBinContent(mee, ptee);
          if (central_value == 0) continue;
          double rel_unc_para_low_value  = TMath::Abs(fRel_para_low->  GetBinContent(mee, ptee) / central_value - 1);
          double rel_unc_para_high_value = TMath::Abs(fRel_para_high-> GetBinContent(mee, ptee) / central_value - 1);
          double rel_unc_MT_low_value    = TMath::Abs(fRel_MT_low->  GetBinContent(mee, ptee) / central_value - 1);
          double rel_unc_MT_high_value   = TMath::Abs(fRel_MT_high-> GetBinContent(mee, ptee) / central_value - 1);
          double rel_unc_BR_low_value    = TMath::Abs(fRel_BR_low->  GetBinContent(mee, ptee) / central_value - 1);
          double rel_unc_BR_high_value   = TMath::Abs(fRel_BR_high-> GetBinContent(mee, ptee) / central_value - 1);
          double rel_unc_Add_low_value   = TMath::Abs(fRel_Add_low-> GetBinContent(mee, ptee) / central_value - 1);
          double rel_unc_Add_high_value  = TMath::Abs(fRel_Add_high->GetBinContent(mee, ptee) / central_value - 1);
          rel_unc_para_low_value  *= rel_unc_para_low_value;
          rel_unc_para_high_value *= rel_unc_para_high_value;
          rel_unc_MT_low_value    *= rel_unc_MT_low_value;
          rel_unc_MT_high_value   *= rel_unc_MT_high_value;
          rel_unc_BR_low_value    *= rel_unc_BR_low_value;
          rel_unc_BR_high_value   *= rel_unc_BR_high_value;
          rel_unc_Add_low_value   *= rel_unc_Add_low_value;
          rel_unc_Add_high_value  *= rel_unc_Add_high_value;
          double factor = 1; // for debugging purposes
          double corr_low = (1 - TMath::Sqrt(rel_unc_para_low_value  / factor + rel_unc_MT_low_value  / factor + rel_unc_BR_low_value  / factor + rel_unc_Add_low_value  / factor) );
          double corr_high= (1 + TMath::Sqrt(rel_unc_para_high_value / factor + rel_unc_MT_high_value / factor + rel_unc_BR_high_value / factor + rel_unc_Add_high_value / factor) );
          double central_low_value  = central_value * corr_low;
          double central_high_value = central_value * corr_high;
          fCentral_low-> SetBinContent(mee, ptee, central_low_value);
          fCentral_high->SetBinContent(mee, ptee, central_high_value);
        }
      }

      //if(kTRUE){
      //  


      //  TCanvas c2("c2", "c2", 800, 800);
      //  c2.cd();
      //  TH1D central_proj_ptee = *(fCentral->ProjectionY());


      //  TH1D rel_para_low_proj_ptee = BuildUncertaintyPlot(*fRel_para_low, central_proj_ptee,   kMagenta, false, -1, -1);
      //  TH1D rel_para_high_proj_ptee = BuildUncertaintyPlot(*fRel_para_high, central_proj_ptee, kMagenta, false, -1, -1);
      //  rel_para_low_proj_ptee.Draw("hist");
      //  rel_para_high_proj_ptee.Draw("hist same");
      //  c2.SaveAs("unc_para_ptee.png");

      //  TH1D rel_MT_low_proj_ptee = BuildUncertaintyPlot(*fRel_MT_low, central_proj_ptee,   kBlue+2, false, -1, -1);
      //  TH1D rel_MT_high_proj_ptee = BuildUncertaintyPlot(*fRel_MT_high, central_proj_ptee, kBlue+2, false, -1, -1);
      //  rel_MT_low_proj_ptee.Draw("hist");
      //  rel_MT_high_proj_ptee.Draw("hist same");
      //  c2.SaveAs("unc_MT_ptee.png");

      //  TH1D rel_BR_low_proj_ptee = BuildUncertaintyPlot(*fRel_BR_low, central_proj_ptee,   kRed, false, -1, -1);
      //  TH1D rel_BR_high_proj_ptee = BuildUncertaintyPlot(*fRel_BR_high, central_proj_ptee, kRed, false, -1, -1);
      //  rel_BR_low_proj_ptee.Draw("hist");
      //  rel_BR_high_proj_ptee.Draw("hist same");
      //  c2.SaveAs("unc_BR_ptee.png");

      //  TH1D rel_Add_low_proj_ptee = BuildUncertaintyPlot(*fRel_Add_low, central_proj_ptee, kGreen+2, false, -1, -1);
      //  TH1D rel_Add_high_proj_ptee = BuildUncertaintyPlot(*fRel_Add_high, central_proj_ptee, kGreen+2, false, -1, -1);
      //  rel_Add_low_proj_ptee.Draw("hist");
      //  rel_Add_high_proj_ptee.Draw("hist same");
      //  c2.SaveAs("unc_Add_ptee.png");

      //  TH1D central_low_proj_ptee = BuildUncertaintyPlot(fCentral_low, central_proj_ptee,   kBlack, false, -1, -1);
      //  TH1D central_high_proj_ptee = BuildUncertaintyPlot(fCentral_high, central_proj_ptee, kBlack, false, -1, -1);
      //  central_low_proj_ptee.Draw("hist");
      //  central_high_proj_ptee.Draw("hist same");
      //  c2.SaveAs("unc_sum_ptee.png");

      //  c4.cd(1);
      //  c4.cd(1)->SetTopMargin(topmargin);
      //  c4.cd(1)->SetRightMargin(rightmargin);
      //  c4.cd(1)-> SetLeftMargin(leftmargin);
      //  rel_para_low_proj_ptee.Draw("hist");
      //  rel_para_high_proj_ptee.Draw("hist same");
      //  c4.cd(2);
      //  c4.cd(2)->SetTopMargin(topmargin);
      //  c4.cd(2)->SetRightMargin(rightmargin);
      //  c4.cd(2)-> SetLeftMargin(leftmargin);
      //  rel_MT_low_proj_ptee.Draw("hist");
      //  rel_MT_high_proj_ptee.Draw("hist same");
      //  c4.cd(3);
      //  c4.cd(3)->SetTopMargin(topmargin);
      //  c4.cd(3)->SetRightMargin(rightmargin);
      //  c4.cd(3)-> SetLeftMargin(leftmargin);
      //  rel_BR_low_proj_ptee.Draw("hist");
      //  rel_BR_high_proj_ptee.Draw("hist same");
      //  c4.cd(4);
      //  c4.cd(4)->SetTopMargin(topmargin);
      //  c4.cd(4)->SetRightMargin(rightmargin);
      //  c4.cd(4)-> SetLeftMargin(leftmargin);
      //  rel_Add_low_proj_ptee.Draw("hist");
      //  rel_Add_high_proj_ptee.Draw("hist same");
      //  c4.cd(5);
      //  c4.cd(5)->SetTopMargin(topmargin);
      //  c4.cd(5)->SetRightMargin(rightmargin);
      //  c4.cd(5)-> SetLeftMargin(leftmargin);
      //  central_low_proj_ptee.Draw("hist");
      //  central_high_proj_ptee.Draw("hist same");

      //  c4.cd(6);
      //  leg.Draw("same");


      //  c4.SaveAs("unc_overall_ptee.png");

      //}


      sum->SetSpectrum2DHigh( fCentral_high);
      sum->SetSpectrum2DLow ( fCentral_low );
      break;
    }
    case kFromParticles:
    {
      if (fLmCocktailPart.size()==0) { LmHelper::Error(Form("LmCocktail::Process(): no cocktail particles available! (name: '%s')", GetName())); return 2; }

      for (unsigned int iPart=1; iPart<fLmCocktailPart.size(); iPart++)
      {
        if (fLmCocktailPart.at(iPart)==0x0) { LmHelper::Error(Form("LmCocktail::Process(): nullpointer attached (LmCocktailPart '%d'). Skip. (name: '%s')", iPart, GetName())); continue; }

        TH2D* hTemp     = fLmCocktailPart.at(iPart)->GetSpectrum2D(); // here it is ok to use pointers, because SetSpectrum2D() does the copying...
        TH2D* hTempLow  = fLmCocktailPart.at(iPart)->GetSpectrum2DLow();
        TH2D* hTempHigh = fLmCocktailPart.at(iPart)->GetSpectrum2DHigh();
        // (it would be much nicer if we had a LmCocktailPart->Add() function and used the copy constuctor or ->Copy() for the sum.)
        if (iPart==1) {
          // Use spectrum 1 to initialize the sum.
          fLmCocktailPart.at(0)->SetSpectrum2D( hTemp ); // using copy constructor of TH2D.
          fLmCocktailPart.at(0)->SetSpectrum2DLow(  (hTempLow)?hTempLow:hTemp ); // Use default if the current particle doesnt have syst.
          fLmCocktailPart.at(0)->SetSpectrum2DHigh( (hTempHigh)?hTempHigh:hTemp );
        }
        else {
          // Add all other attached particles to the sum.
          fLmCocktailPart.at(0)->GetSpectrum2D()->Add( hTemp );
          fLmCocktailPart.at(0)->GetSpectrum2DLow() ->Add( (hTempLow)?hTempLow:hTemp ); // Use default if the current particle doesnt have syst.
          fLmCocktailPart.at(0)->GetSpectrum2DHigh()->Add( (hTempHigh)?hTempHigh:hTemp );
        }
      }
      fLmCocktailPart.at(0)->Process(LmCocktailPart::kSum); // needed to set the type from kUndef to kSum and the styles.
      break;
    }
    default:
    {
      break;
    }
  }
  //  if (recursive) return;
  //  // Put things below which shall be called only for non-recursive Process() calls, otherwise they are executed more than once!

  return 0;
}

//_______________________________________________________________________________________________
TH1D LmCocktail::BuildUncertaintyPlot(TH2D& unc, const TH1D& central_proj, int color, bool doMass, int bin_min, int bin_max){
  TH1D proj = *(unc.ProjectionX("proj_mee",bin_min, bin_max));
  if(!doMass)
    proj = *(unc.ProjectionY("proj_ptee",bin_min, bin_max));

  // Relative uncertainty
  proj.Add(&central_proj, -1.);
  proj.Divide(&central_proj);

  proj.SetAxisRange(-0.4, 0.4, "Y");
  proj.SetAxisRange(0. , 3.99, "X");
  proj.SetLineColor(color);
  proj.SetFillStyle(1001);
  //LmHelper::Error(Form("LmCocktail::BuildUncertaintyPlot(): sorry, 'proj.SetFillColorAlpha(color, 0.7);' geht erst mit root 6..."));
  // proj.SetFillColorAlpha(color, 0.7);
  proj.SetFillColor(color);
  return proj;
}

//_______________________________________________________________________________________________
void LmCocktail::AddHistToParticle(TH2D* hist, Int_t partType)
{
  for (unsigned int iPart=0; iPart<fLmCocktailPart.size(); iPart++)
  {
    if (fLmCocktailPart.at(iPart)->GetType()==partType) {
      fLmCocktailPart.at(iPart)->GetSpectrum2D()->Add(hist);
      //if (partType == LmCocktailPart::kOmega) fLmCocktailPart.at(iPart)->SetName(Form("%s, %s", fLmCocktailPart.at(iPart)->GetName(), LmCocktailPart::GetLegendnameStatic(LmCocktailPart::kOmegaDalitz)));
      //if (partType == LmCocktailPart::kPhi)   fLmCocktailPart.at(iPart)->SetName(Form("%s, %s", fLmCocktailPart.at(iPart)->GetName(), LmCocktailPart::GetLegendnameStatic(LmCocktailPart::kPhiDalitz)));
      return;
    }
  }
  LmHelper::Error(Form("LmCocktail::AddHistToParticle(): particle with type '%s' not available for adding. (hint: put the Dalitz part after the resonance part in your config string.)",LmCocktailPart::GetTypenameStatic(partType)));
}


//_______________________________________________________________________________________________
void LmCocktail::MakeSpectra1D()
{
  /// note: when calling this from within a LmHandler, make sure to have set identical projection ranges.

  if (fType==kNoProcess) { LmHelper::Error(Form("LmCocktail::MakeSpectra1D(): execute Process() before! (name: '%s')", GetName())); return; }
  //cout << "fLmCocktailPart.size()=" << fLmCocktailPart.size() << endl;
  for (unsigned int iPart=0; iPart<fLmCocktailPart.size(); iPart++)
  {
    LmHelper::Debug(Form(" Next Cocktail ingredient [%i/%i]: %s", iPart+1, (int)fLmCocktailPart.size(), fLmCocktailPart.at(iPart)->GetName()), 5);
    fLmCocktailPart.at(iPart)->MakeSpectra1D(fBinsPtee_forprojMee, LmBaseSignal::kProjOnMee);
    fLmCocktailPart.at(iPart)->MakeSpectra1D(fBinsMee_forprojPtee, LmBaseSignal::kProjOnPtee);
  }
}


//_______________________________________________________________________________________________
TObjArray* LmCocktail::GetSpectra1D(unsigned int bin_number, Bool_t projOnMee)
{
  TObjArray* obj_array = new TObjArray();
  //obj_array->SetOwner(kTRUE); // better not do this.
  for (unsigned int iPart=0; iPart<fLmCocktailPart.size(); iPart++)
  {
    obj_array->Add( fLmCocktailPart.at(iPart)->GetSpectrum(bin_number,projOnMee) );
  }
  return obj_array;
}


//_______________________________________________________________________________________________
TH1D* LmCocktail::GetSum1D(unsigned int bin_number, Bool_t projOnMee)
{
  return fLmCocktailPart.at(0)->GetSpectrum(bin_number,projOnMee);
}
//_______________________________________________________________________________________________
TGraphAsymmErrors* LmCocktail::GetSumErr1D(unsigned int bin_number, Bool_t projOnMee)
{
  return fLmCocktailPart.at(0)->GetSpectrumErr(bin_number,projOnMee);
}
//_______________________________________________________________________________________________
TH1D* LmCocktail::GetComponent1D(Int_t partType, unsigned int bin_number, Bool_t projOnMee)
{
  for (unsigned int iPart=0; iPart<fLmCocktailPart.size(); iPart++)
  {
    if (fLmCocktailPart.at(iPart)->GetType() == partType) return fLmCocktailPart.at(iPart)->GetSpectrum(bin_number,projOnMee);
  }
  LmHelper::Error(Form("LmCocktail::GetComponent1D(): component with type '%s' not found.", LmCocktailPart::GetTypenameStatic(partType)));
  return 0x0;
}

//_______________________________________________________________________________________________
//LmCocktailPart* LmCocktail::GetLmCocktailPartCopy(Int_t partType)
//{
//  if (GetLmCocktailPart(partType)!=0x0) return new LmCocktailPart();
//}
//_______________________________________________________________________________________________
LmCocktailPart* LmCocktail::GetLmCocktailPart(Int_t partType, Bool_t suppressErr)
{
  for (unsigned int iPart=0; iPart<fLmCocktailPart.size(); iPart++)
  {
    if (fLmCocktailPart.at(iPart)->GetType() == partType) return fLmCocktailPart.at(iPart);
  }
  if (!suppressErr) LmHelper::Error(Form("LmCocktail::GetLmCocktailPart(): particle with type '%s' not found.", LmCocktailPart::GetTypenameStatic(partType)));
  return 0x0;
}

//_______________________________________________________________________________________________
std::vector<TString> LmCocktail::GetPartNames()
{
  std::vector<TString> sNames;
  for (unsigned int iPart=0; iPart<fLmCocktailPart.size(); iPart++)
  {
    sNames.push_back(fLmCocktailPart.at(iPart)->GetName()); // implicitly using constructor of TString.
  }
  return sNames;
}


//_______________________________________________________________________________________________
Double_t LmCocktail::GetPteeEdge_forprojMee(unsigned int bin) const
{
  if (fBinsPtee_forprojMee.size() == 0) { LmHelper::Error("LmHandler::GetPteeEdge_forprojMee(): No Ptee Bins for Mee Projection set!"); }
  if (bin>=fBinsPtee_forprojMee.size()) { LmHelper::Error(Form("LmHandler::GetPteeEdge_forprojMee(bin=%u): out of range! Too few bins set!", bin)); }
  return fBinsPtee_forprojMee.at(bin);
}
//_______________________________________________________________________________________________
Double_t LmCocktail::GetMeeEdge_forprojPtee(unsigned int bin) const
{
  if (fBinsMee_forprojPtee.size() == 0) { LmHelper::Error("LmHandler::GetMeeEdge_forprojPtee(): No Meee Bins for Ptee Projection set!"); }
  if (bin>=fBinsMee_forprojPtee.size()) { LmHelper::Error(Form("LmHandler::GetMeeEdge_forprojPtee(bin=%u): out of range! Too few bins set!", bin)); }
  return fBinsMee_forprojPtee.at(bin);
}


//_______________________________________________________________________________________________
void LmCocktail::DrawProjection(unsigned int bin_number, Bool_t projOnMee)
{
  /// Draw cocktail spectra for the selected projection bin. Used by LmHandler::PrintCompare().
  /// Line widths and styles are automatically set inside LmCocktailPart via InheritStyleFrom2D().
  /// To change them, set these properties for the 2D spectra of the particles before calling cocktail->Process().
  /// E.g.: cocktail->GetLmCocktailPart(LmCocktailPart::kSum)->GetSpectrum2D()->SetLineStyle(7);
  
  // Collect 1D spectra of current projection.
  TObjArray* oaCocktail = GetSpectra1D(bin_number,projOnMee);
  
  // Draw systematics first, if available (or add more switch cases for this if desired):
  //if (HasSystematics()) GetSumErr1D(bin_number,projOnMee)->DrawClone(Form("%s same", GetDrawStyleErr()));
  
  switch (fDrawOpt) {
    case kAll:
      if(HasSystematics()) GetSumErr1D(bin_number,projOnMee)->DrawClone(Form("%s same", GetDrawStyleErr()));
      oaCocktail->DrawClone(Form("%s same", GetDrawStyle())); // draw all contributions.
      ((TH1D*) oaCocktail->At(0))->DrawClone(Form("%s same", GetDrawStyle())); // draw the sum again, looks nicer.
      break;
    case kOnlySum:
      if(HasSystematics()) GetSumErr1D(bin_number,projOnMee)->DrawClone(Form("%s same", GetDrawStyleErr()));
      ((TH1D*) oaCocktail->At(0))->DrawClone(Form("%s same", GetDrawStyle())); // draw the sum.
      break;
    case kAllButSum:
      oaCocktail->RemoveAt(0); // remove the sum.
      oaCocktail->DrawClone(Form("%s same", GetDrawStyle())); // draw the remaining contributions.
      break;
    default:
      break;
  }
  delete oaCocktail;
}

//_______________________________________________________________________________________________
void LmCocktail::PrintCocktail_Mee(unsigned int bin_number, const Char_t* filename, const Char_t* comment, TH1* hData)
{
  if ((Int_t)bin_number > fLmCocktailPart.at(0)->GetMaxBinProj(LmBaseSignal::kProjOnMee)) {LmHelper::Error("LmCocktail::PrintCocktail_Mee(): bin number out of range"); return;}
  TCanvas can("cocktail_mee", "cocktail_mee");
  can.cd()->SetLogy();

  TH1D hist_temp(*fLmCocktailPart.at(0)->GetSpectrum(bin_number,LmBaseSignal::kProjOnMee));
  hist_temp.SetMinimum(1e-5);
  hist_temp.SetMaximum(10.);
  hist_temp.SetAxisRange(0., 3.499, "X");
  hist_temp.DrawCopy(fDrawStyle.c_str());

  for (unsigned int iPart=1; iPart<fLmCocktailPart.size(); iPart++)
  {
    fLmCocktailPart.at(iPart)->GetSpectrum(bin_number,LmBaseSignal::kProjOnMee)->DrawCopy((fDrawStyle + " same").c_str());
  }
  if (hData) hData->DrawCopy("same");

  TLatex* latComment = new TLatex(0.55,0.82,comment);
  latComment->SetTextFont(gStyle->GetTitleFont());
  latComment->SetTextSize(gStyle->GetTitleSize());
  latComment->SetNDC();
  latComment->Draw();

  Double_t proj_min = -1;
  Double_t proj_max = -1;
  if ((Int_t)bin_number >= (Int_t)fBinsPtee_forprojMee.size()-1){ // case of integrated projection (last bin)
    proj_min = GetPteeEdge_forprojMee(0);
    proj_max = GetPteeEdge_forprojMee(bin_number);
  }
  else {
    proj_min = GetPteeEdge_forprojMee(bin_number);
    proj_max = GetPteeEdge_forprojMee(bin_number+1);
  }
  char pairptrange[256];
  sprintf(pairptrange,"%.2f #leq %s #leq %.2f %s",proj_min,LmBaseSignal::GetProjLabelYvar().Data(),proj_max,LmBaseSignal::GetProjLabelYunit().Data());
  TLatex* latCuts2 = new TLatex(0.45,0.64,Form("%s", pairptrange));
  latCuts2->SetTextFont(gStyle->GetTitleFont());
  latCuts2->SetTextSize(gStyle->GetTitleSize());
  latCuts2->SetNDC();
  latCuts2->Draw();

  can.Print(filename);
  return;
}

//_______________________________________________________________________________________________
void LmCocktail::PrintCocktail_Ptee(unsigned int bin_number, const Char_t* filename, const Char_t* comment, TH1* hData)
{
  if ((Int_t)bin_number > fLmCocktailPart.at(0)->GetMaxBinProj(LmBaseSignal::kProjOnPtee)) {LmHelper::Error("LmCocktail::PrintCocktail_Ptee(): bin number out of range"); return;}
  TCanvas can("cocktail_ptee", "cocktail_ptee");
  can.cd()->SetLogy();

  TH1D hist_temp(*fLmCocktailPart.at(0)->GetSpectrum(bin_number,LmBaseSignal::kProjOnPtee));
  // hist_temp.SetMinimum(1e-5);
  hist_temp.SetAxisRange(0., 4.999, "X");
  hist_temp.DrawCopy(fDrawStyle.c_str());

  for (unsigned int iPart=1; iPart<fLmCocktailPart.size(); iPart++)
  {
    fLmCocktailPart.at(iPart)->GetSpectrum(bin_number,LmBaseSignal::kProjOnPtee)->DrawCopy((fDrawStyle + " same").c_str());
  }
  if (hData) hData->DrawCopy("same");

  TLatex* latComment = new TLatex(0.55,0.82,comment);
  latComment->SetTextFont(gStyle->GetTitleFont());
  latComment->SetTextSize(gStyle->GetTitleSize());
  latComment->SetNDC();
  latComment->Draw();

  Double_t proj_min = -1;
  Double_t proj_max = -1;
  if ((Int_t)bin_number == (Int_t)fBinsMee_forprojPtee.size()-1){ // case of integrated projection (last bin)
    proj_min = GetMeeEdge_forprojPtee(0);
    proj_max = GetMeeEdge_forprojPtee(bin_number);
  }
  else {
    proj_min = GetMeeEdge_forprojPtee(bin_number);
    proj_max = GetMeeEdge_forprojPtee(bin_number+1);
  }
  char pairptrange[256];
  sprintf(pairptrange,"%.2f #leq %s #leq %.2f %s",proj_min,LmBaseSignal::GetProjLabelXvar().Data(),proj_max,LmBaseSignal::GetProjLabelXunit().Data());
  TLatex* latCuts2 = new TLatex(0.55,0.74,Form("%s", pairptrange));
  latCuts2->SetTextFont(gStyle->GetTitleFont());
  latCuts2->SetTextSize(gStyle->GetTitleSize());
  latCuts2->SetNDC();
  latCuts2->Draw();

  can.Print(filename);
  return;
}



void LmCocktail::WriteHist1D(unsigned int bin_number, Bool_t projOnMee)
{

  if(projOnMee) {
    if ((Int_t)bin_number > fLmCocktailPart.at(0)->GetMaxBinProj(LmBaseSignal::kProjOnMee)) {LmHelper::Error("LmCocktail::PrintCocktail_Mee(): bin number out of range"); return;}
 
    for (unsigned int iPart=0; iPart<fLmCocktailPart.size(); iPart++)
    {
      TH1D hist_temp(*fLmCocktailPart.at(iPart)->GetSpectrum(bin_number,LmBaseSignal::kProjOnMee));
      hist_temp.SetAxisRange(0., 3.5, "X");
      hist_temp.Write();
    }
  }

  else {
    if ((Int_t)bin_number > fLmCocktailPart.at(0)->GetMaxBinProj(LmBaseSignal::kProjOnPtee)) {LmHelper::Error("LmCocktail::PrintCocktail_Ptee(): bin number out of range"); return;}
 
    for (unsigned int iPart=0; iPart<fLmCocktailPart.size(); iPart++)
    {
      TH1D hist_temp(*fLmCocktailPart.at(iPart)->GetSpectrum(bin_number,LmBaseSignal::kProjOnPtee));
      hist_temp.SetAxisRange(0., 4.999, "X");
      hist_temp.Write();
    }
  }



  //LmHelper::Debug(Form(" WriteHist1D(projOnMee=%i)", projOnMee), 5-debugSignal);

  //Int_t     maxbin = GetMaxBinProj(projOnMee); // maxbin cannot be unsigned.
  //Double_t  projmin=-1, projmax=-1;
  //TString   projrange;
  //if (!signame.IsNull()) signame.Prepend("-");

  //if (bins.size()==0) {LmHelper::Error("LmCocktail::WriteHist1D(): no bins for projections set."); return;}
  //if ((Int_t)bins.size()!=maxbin+1) {
  //  LmHelper::Error("LmCocktail::WriteHist1D(): wrong number of projection bins. Process handler again."); return;}

  //for (unsigned int ibin = 0; (Int_t)ibin <= maxbin; ++ibin) { // cast to Int_t needed to avoid compiler warning.
  //  if (maxbin==1 && ibin==1) break; // in case of one integrated bin: do not write same projection twice.
  //  if (ibin < bins.size()-1) {
  //    projmin = bins.at(ibin);
  //    projmax = bins.at(ibin+1);
  //  }
  //  else { // for integrated projection (last entry in projection vectors)
  //    projmin = bins.at(0);
  //    projmax = bins.at(bins.size()-1); // last entry in bins vector
  //  }

  //  LmHistogram lmTemp = GetLmHist(iBit,ibin,projOnMee);
  //  if (!lmTemp) continue;
  //  TH1D* hTemp = lmTemp->GetDatahist();

  //  if (projOnMee==LmBaseSignal::kProjOnMee)  projrange=(Form("ptee%.2fto%.2f",projmin,projmax));
  //  else                                      projrange=(Form("mee%.2fto%.2f",projmin,projmax));
  //  
  //  hTemp->GetXaxis()->SetRangeUser(0., -1);
  //  hTemp->Write();

  //  // write systematics if available
  //  TGraphAsymmErrors* grSysTemp = 0x0;
  //  grSysTemp = GetSystematicGraph(iBit,ibin,projOnMee);
  //  if (!grSysTemp) continue;
  //  if (simplehistnames) grSysTemp->SetName(Form("h%s_sys-%s%s",GetCharHistBit(iBit,kTRUE),projrange.Data(),signame.Data()));
  //  grSysTemp->Write();

  //} // end projection bin loop
}
      

void LmCocktail::WriteHist2D(Bool_t divideByBinWidth)
{

  for (unsigned int iPart=0; iPart<fLmCocktailPart.size(); iPart++)
  { 
    TH2D hTemp(*fLmCocktailPart.at(iPart)->GetSpectrum2D());
    //hist_temp.SetAxisRange(0., 3.5, "X");

    if(divideByBinWidth) {
      for(Int_t ix = 1; ix <= hTemp.GetNbinsX(); ++ix){
        for(Int_t iy = 1; iy <= hTemp.GetNbinsY(); ++iy){
          hTemp.SetBinContent(ix,iy,hTemp.GetBinContent(ix,iy) / hTemp.GetXaxis()->GetBinWidth(ix) / hTemp.GetYaxis()->GetBinWidth(iy));
          hTemp.SetBinError(ix,iy,hTemp.GetBinError(ix,iy) / hTemp.GetXaxis()->GetBinWidth(ix) / hTemp.GetYaxis()->GetBinWidth(iy));
        }
      }
    }

    hTemp.Write();
  }
}



//_______________________________________________________________________________________________
void LmCocktail::WriteHist1D(unsigned int histBits, const std::vector<Double_t> bins, Bool_t simplehistnames, Bool_t projOnMee, TString appendix)
{
  /// Write 1D histograms and error graphs of cocktail particles to the currently active path (which should be an
  /// opened rootfile).
  /// @param histBits Collection of particle types (bits) that shall be written. Multiple types allowed by adding bits.
  /// @param simplehistnames Use short particle names defined by LmCocktailPart::GetTypenameStatic(). Should be kTRUE.
  LmHelper::Debug(Form(" LmCocktail::WriteHist1D(projOnMee=%i)", projOnMee), 5);

  Int_t     maxbin = GetLmCocktailPart(LmCocktailPart::kSum)->GetMaxBinProj(projOnMee); // maxbin cannot be unsigned.
  Double_t  projmin=-1, projmax=-1;
  TString   projrange;
  if (!appendix.IsNull()) appendix.Prepend("-");

  if (bins.size()==0) {LmHelper::Error("LmCocktail::WriteHist1D(): no bins for projections set."); return;}
  if ((Int_t)bins.size()!=maxbin+1) {
    LmHelper::Error("LmCocktail::WriteHist1D(): wrong number of projection bins. Process handler again."); return;}

  for (unsigned int ibin = 0; (Int_t)ibin <= maxbin; ++ibin) { // cast to Int_t needed to avoid compiler warning.
    if (maxbin==1 && ibin==1) break; // in case of one integrated bin: do not write same projection twice.
    if (ibin < bins.size()-1) {
      projmin = bins.at(ibin);
      projmax = bins.at(ibin+1);
    }
    else { // for integrated projection (last entry in projection vectors)
      projmin = bins.at(0);
      projmax = bins.at(bins.size()-1); // last entry in bins vector
    }

    for (unsigned int iBit = 1; iBit < LmCocktailPart::kMAXpart; iBit *= 2) {
      if ( !(iBit & histBits) ) continue; // continue if current histogram was not requested.
      LmCocktailPart* lmTemp = GetLmCocktailPart(iBit, kTRUE); // kTRUE: dont show errors for unfound particles.
      if (!lmTemp) continue;
      TH1D* hTemp = lmTemp->GetSpectrum(ibin,projOnMee);

      if (projOnMee==LmBaseSignal::kProjOnMee)  projrange=(Form("ptee%.2fto%.2f",projmin,projmax));
      else                                      projrange=(Form("mee%.2fto%.2f",projmin,projmax));

      if (simplehistnames) hTemp->SetName(Form("h%s-%s%s",lmTemp->GetTypename(),projrange.Data(),appendix.Data()));
      // otherwise it will use the names of the histograms (not recommended until they are named consistently).
      // the projection range is included in both cases.

      hTemp->GetXaxis()->SetRangeUser(0., -1);
      hTemp->Write();

      // write systematics if available
      TGraphAsymmErrors* grSysTemp = 0x0;
      grSysTemp = lmTemp->GetSpectrumErr(ibin,projOnMee);
      if (!grSysTemp) continue;
      if (simplehistnames) grSysTemp->SetName(Form("h%s_sys-%s%s",lmTemp->GetTypename(),projrange.Data(),appendix.Data()));
      grSysTemp->Write();

    } // end histogram loop
  } // end projection bin loop
}

//_______________________________________________________________________________________________
void LmCocktail::WriteHist2D(std::string filename){
  TFile* fileOut = TFile::Open(filename.c_str(), "RECREATE");
  for (unsigned int i = 0; i < fLmCocktailPart.size(); ++i){
    TH2D* part =     fLmCocktailPart[i]->GetSpectrum2DCopy();
    TH2D* part_low  = fLmCocktailPart[i]->GetSpectrum2DLowCopy();
    TH2D* part_high = fLmCocktailPart[i]->GetSpectrum2DHighCopy();
    part->Write(Form("%s", fLmCocktailPart[i]->GetTypename()));
    part_low->Write(Form("%s_low", fLmCocktailPart[i]->GetTypename()));
    part_high->Write(Form("%s_high", fLmCocktailPart[i]->GetTypename()));
    delete part;
  }

  fileOut->Close();
  delete fileOut;
  return;
}

//_______________________________________________________________________________________________
Bool_t LmCocktail::IsLFParticle(LmCocktailPart::enType type){
  switch (type) {
    case LmCocktailPart::kPion:
    case LmCocktailPart::kEta:
    case LmCocktailPart::kEtaPrime:
    case LmCocktailPart::kRho:
    case LmCocktailPart::kOmega:
    case LmCocktailPart::kOmegaDalitz:
    case LmCocktailPart::kPhi:
    case LmCocktailPart::kPhiDalitz:
    return true;
    break;
    default:
    return false;
  }
}

//_______________________________________________________________________________________________
void LmCocktail::SetBRRelUncertainty(LmCocktailPart::enType type, double low, double high){
  /// Loops through vector of uncertainties and replaces values when particle of same type is found
  /// Otherwise it adds another uncertainty for a particle
  // if (IsLFParticle(type) == kFALSE) return;
  for (unsigned int i = 0; i < fSysUnc.size(); ++i){
    if (fSysUnc.at(i).type == type){
      fSysUnc.at(i).BRunc_high = high;
      fSysUnc.at(i).BRunc_low = low;
      return;
    }
  }
  SysUnc temp = {type, low, high, 0., 0., 0., 0.,0.,0.};
  fSysUnc.push_back(temp);
}

//_______________________________________________________________________________________________
void LmCocktail::SetParamRelUncertainty(LmCocktailPart::enType type, double low, double high){
  /// Loops through vector of uncertainties and replaces values when particle of same type is found
  /// Otherwise it adds another uncertainty for a particle
  // if (IsLFParticle(type) == kFALSE) return;
  for (unsigned int i = 0; i < fSysUnc.size(); ++i){
    if (fSysUnc.at(i).type == type){
      fSysUnc.at(i).Param_high = high;
      fSysUnc.at(i).Param_low = low;
      return;
    }
  }
  SysUnc temp = {type, low, high, 0., 0., 0., 0.,0.,0.};
  fSysUnc.push_back(temp);
}

//_______________________________________________________________________________________________
void LmCocktail::SetMTscalingRelUncertainty(LmCocktailPart::enType type, double low, double high){
  /// Loops through vector of uncertainties and replaces values when particle of same type is found
  /// Otherwise it adds another uncertainty for a particle
  // if (IsLFParticle(type) == kFALSE) return;
  for (unsigned int i = 0; i < fSysUnc.size(); ++i){
    if (fSysUnc.at(i).type == type){
      fSysUnc.at(i).MTscaling_high = high;
      fSysUnc.at(i).MTscaling_low  = low;
      return;
    }
  }
  SysUnc temp = {type, 0., 0., low, high, 0., 0., 0.,0.};
  fSysUnc.push_back(temp);
}

//_______________________________________________________________________________________________
void LmCocktail::SetAdditionalRelUncertainty(LmCocktailPart::enType type, double low, double high){
  /// Loops through vector of uncertainties and replaces values when particle of same type is found
  /// Otherwise it adds another uncertainty for a particle
  // if (IsLFParticle(type) == kFALSE) return;
  for (unsigned int i = 0; i < fSysUnc.size(); ++i){
    if (fSysUnc.at(i).type == type){
      fSysUnc.at(i).additional_uncertainty_high = high;
      fSysUnc.at(i).additional_uncertainty_low  = low;
      return;
    }
  }
  SysUnc temp = {type, 0., 0., 0., 0., low, high,0.,0.};
  fSysUnc.push_back(temp);
}



//_______________________________________________________________________________________________
void LmCocktail::PrintUncertainties(Double_t min, Double_t max, Bool_t doMass){
  for (unsigned int i = 0; i < fSysUnc.size(); ++i){
    LmHelper::Info(Form("%s with branching ratio uncertainty = [%0.3f, %0.3f] and parametrisation uncertainty = [%0.1f, %0.1f] and mT-scaling uncertainty = [%0.1f, %0.1f] and additional uncertainty = [%0.1f, %0.1f]", LmCocktailPart::GetTypenameStatic(fSysUnc.at(i).type), fSysUnc.at(i).BRunc_low, fSysUnc.at(i).BRunc_high, fSysUnc.at(i).Param_low, fSysUnc.at(i).Param_high, fSysUnc.at(i).MTscaling_low, fSysUnc.at(i).MTscaling_high, fSysUnc.at(i).additional_uncertainty_low, fSysUnc.at(i).additional_uncertainty_high));
  }
  //fPrintUnc = unc;

  TString str = Form("_mee_%.0ito%.0i", (int)(min*1000),(int)(max*1000));
  if(!doMass)
    str = Form("_ptee_%.0ito%.0i", (int)(min*1000),(int)(max*1000)) ;

  TCanvas c1("c1", "c1", 800, 800);
  c1.cd();

  Int_t bin_min = fCentral->GetXaxis()->FindBin(min);
  Int_t bin_max = fCentral->GetXaxis()->FindBin(max)+1;
  if(!doMass){
    bin_min = fCentral->GetYaxis()->FindBin(min);
    bin_max = fCentral->GetYaxis()->FindBin(max)+1;
  }
  TH1D central_proj = *(fCentral->ProjectionX("central_mee",bin_min,bin_max));
  if(!doMass)
    central_proj = *(fCentral->ProjectionY("central_ptee",bin_min,bin_max));
  TH1D rel_para_low_proj = BuildUncertaintyPlot(*fRel_para_low, central_proj,   kMagenta, doMass, bin_min, bin_max);
  TH1D rel_para_high_proj = BuildUncertaintyPlot(*fRel_para_high, central_proj, kMagenta, doMass, bin_min, bin_max);
  rel_para_low_proj.GetXaxis()->SetRangeUser(0.,1.);
  rel_para_high_proj.GetXaxis()->SetRangeUser(0.,1.);
  rel_para_high_proj.Draw("hist same");
  rel_para_low_proj.Draw("hist");
  rel_para_high_proj.Draw("hist same");
  c1.SaveAs(("unc_para" + str + ".pdf"));
  TH1D rel_MT_low_proj = BuildUncertaintyPlot(*fRel_MT_low, central_proj,   kBlue+2, doMass, bin_min, bin_max);
  TH1D rel_MT_high_proj = BuildUncertaintyPlot(*fRel_MT_high, central_proj, kBlue+2, doMass, bin_min, bin_max);
  rel_MT_low_proj.GetXaxis()->SetRangeUser(0.,1.);
  rel_MT_high_proj.GetXaxis()->SetRangeUser(0.,1.);
  rel_MT_low_proj.Draw("hist");
  rel_MT_high_proj.Draw("hist same");
  c1.SaveAs("unc_MT" + str + ".pdf");

  TH1D rel_BR_low_proj = BuildUncertaintyPlot(*fRel_BR_low, central_proj,   kRed, doMass, bin_min, bin_max);
  TH1D rel_BR_high_proj = BuildUncertaintyPlot(*fRel_BR_high, central_proj, kRed, doMass, bin_min, bin_max);
  rel_BR_low_proj.GetXaxis()->SetRangeUser(0.,1.);
  rel_BR_high_proj.GetXaxis()->SetRangeUser(0.,1.);
  rel_BR_low_proj.Draw("hist");
  rel_BR_high_proj.Draw("hist same");
  c1.SaveAs("unc_BR" + str + ".pdf");

  TH1D rel_Add_low_proj = BuildUncertaintyPlot(*fRel_Add_low, central_proj, kGreen+2, doMass, bin_min, bin_max);
  TH1D rel_Add_high_proj = BuildUncertaintyPlot(*fRel_Add_high, central_proj, kGreen+2, doMass, bin_min, bin_max);
  rel_Add_low_proj.GetXaxis()->SetRangeUser(0.,1.);
  rel_Add_high_proj.GetXaxis()->SetRangeUser(0.,1.);
  rel_Add_low_proj.Draw("hist");
  rel_Add_high_proj.Draw("hist same");
  c1.SaveAs("unc_Add" + str + ".pdf");

  TH1D central_low_proj = BuildUncertaintyPlot(*fCentral_low, central_proj,   kBlack, doMass, bin_min, bin_max);
  TH1D central_high_proj = BuildUncertaintyPlot(*fCentral_high, central_proj, kBlack, doMass, bin_min, bin_max);
  central_low_proj.GetXaxis()->SetRangeUser(0.,1.);
  central_high_proj.GetXaxis()->SetRangeUser(0.,1.);
  central_low_proj.Draw("hist");
  central_high_proj.Draw("hist same");
  c1.SaveAs("unc_sum" + str + ".pdf");

  TCanvas c4("c4", "c4", 1500, 1000);
  c4.Divide(3, 2, 0.01, 0.01);
  // c4.Divide(3, 2);
  double rightmargin = 0.01;
  double leftmargin  = 0.05;
  double topmargin   = 0.01;
  c4.cd(1);
  c4.cd(1)->SetTopMargin(topmargin);
  c4.cd(1)->SetRightMargin(rightmargin);
  c4.cd(1)-> SetLeftMargin(leftmargin);
  rel_para_low_proj.Draw("hist");
  rel_para_high_proj.Draw("hist same");
  c4.cd(2);
  c4.cd(2)->SetTopMargin(topmargin);
  c4.cd(2)->SetRightMargin(rightmargin);
  c4.cd(2)-> SetLeftMargin(leftmargin);
  rel_MT_low_proj.Draw("hist");
  rel_MT_high_proj.Draw("hist same");
  c4.cd(3);
  c4.cd(3)->SetTopMargin(topmargin);
  c4.cd(3)->SetRightMargin(rightmargin);
  c4.cd(3)-> SetLeftMargin(leftmargin);
  rel_BR_low_proj.Draw("hist");
  rel_BR_high_proj.Draw("hist same");
  c4.cd(4);
  c4.cd(4)->SetTopMargin(topmargin);
  c4.cd(4)->SetRightMargin(rightmargin);
  c4.cd(4)-> SetLeftMargin(leftmargin);
  rel_Add_low_proj.Draw("hist");
  rel_Add_high_proj.Draw("hist same");
  c4.cd(5);
  c4.cd(5)->SetTopMargin(topmargin);
  c4.cd(5)->SetRightMargin(rightmargin);
  c4.cd(5)-> SetLeftMargin(leftmargin);
  central_low_proj.Draw("hist");
  central_high_proj.Draw("hist same");

  c4.cd(6);
  TLegend leg(0.0, 0.2, 0.99, 0.9);
  leg.SetTextFont(42);
  leg.AddEntry((TObject*)0, "Systematic uncertainties of cocktail", "");
  leg.AddEntry(&rel_para_low_proj, "Parametrization", "F");
  leg.AddEntry(&rel_MT_low_proj,   "m_{T}-scaling", "F");
  leg.AddEntry(&rel_BR_low_proj,   "Branching ratio", "F");
  leg.AddEntry(&rel_Add_low_proj,  "Additional (eg.: cross section)", "F");
  leg.AddEntry(&central_low_proj,  "Quadratic sum of above", "F");
  leg.Draw("same");


  c4.SaveAs("unc_overall" + str + ".pdf");



  return;
}

//_______________________________________________________________________________________________
void LmCocktail::ApplySysRelUncertainties(LmCocktailPart* part, TH2D* low, TH2D* high){
  /// Applies systematic uncertainties to the high and low part of the cocktail
  double BR_low = 0, BR_high = 0, Param_low = 0, Param_high = 0, MT_low = 0, MT_high = 0, add_low = 0, add_high = 0;
  // double param_low = 0, param_high = 0;
  for (unsigned int i = 0; i < fSysUnc.size(); ++i){
    if (fSysUnc.at(i).type == part->GetType()){
      BR_low = fSysUnc.at(i).BRunc_low;
      BR_high= fSysUnc.at(i).BRunc_high;
      Param_low = fSysUnc.at(i).Param_low;
      Param_high= fSysUnc.at(i).Param_high;
      MT_low = fSysUnc.at(i).MTscaling_low;
      MT_high= fSysUnc.at(i).MTscaling_high;
      add_low = fSysUnc.at(i).additional_uncertainty_low;
      add_high= fSysUnc.at(i).additional_uncertainty_high;
      break;
    }
  }
  // if (BR_low == 0 && BR_high == 0 && MT_low == 0 && MT_high == 0 && add_low == 0 && add_high == 0) return;

  TH2D* central = part->GetSpectrum2D();
  // If no lower and higher systematics are given low and high get created
  if (!low) {
    std::cout << "Something goes wrong!! " << "  " << part->GetName() << std::endl;
    low = new TH2D(*dynamic_cast<TH2D*>(central->Clone(Form("low_%s", part->GetTypename()))));
  }
  if (!high) {
    std::cout << "Something goes wrong!! " << "  " << part->GetName() << std::endl;
    high = new TH2D(*dynamic_cast<TH2D*>(central->Clone(Form("high_%s", part->GetTypename()))));
  }

  // Set the uncertainties per particle
  part->SetSpectrum2DLow(low);
  part->SetSpectrum2DHigh(high);
  part->SetBRRelUncertainty(BR_low, BR_high);
  part->SetMTscalingRelUncertainty(MT_low, MT_high);
  part->SetAdditionalRelUncertainty(add_low, add_high);
  part->SetParamRelUncertainty(Param_low, Param_high); 
  std::cout << part->GetName() << " different uncertainties assigned" << std::endl;

  return;
}
