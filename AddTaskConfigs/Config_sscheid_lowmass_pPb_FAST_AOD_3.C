void InitHistograms(AliDielectron* die, Int_t cutDefinition);

void SetSignalsMC(AliDielectron* die);
void InitCF(AliDielectron* die, Int_t cutDefinition);

void SetupCuts(AliDielectron* die, Int_t cutDefinition);

AliDielectronVarCuts* SetupTrackCuts(Int_t cutDefinition);
AliESDtrackCuts* SetupPreFilterESDtrackCuts(Int_t cutDefinition);
AliAnalysisCuts* SetupPIDcuts(Int_t cutDefinition);

AliDielectronEventCuts* GetEventCuts();
void SetEtaCorrectionTPCMean(AliDielectron* die, Int_t corrXdim, Int_t corrYdim, Int_t corrZdim, Bool_t runwise);
void SetEtaCorrectionTPCRMS(AliDielectron* die, Int_t corrXdim, Int_t corrYdim, Int_t corrZdim, Bool_t runwise);
void SetEtaCorrectionTOFMean(AliDielectron* die, Int_t corrXdim, Int_t corrYdim, Int_t corrZdim, Bool_t runwise);
void SetEtaCorrectionTOFRMS(AliDielectron* die, Int_t corrXdim, Int_t corrYdim, Int_t corrZdim, Bool_t runwise);

AliDielectron* Config_sscheid_lowmass_pPb_FAST_AOD_3(Int_t cutDefinition = 1, Bool_t isRandomRej = kFALSE);
AliDielectron* Config_sscheid_lowmass(Int_t cutDefinition = 1, Bool_t isRandomRej = kFALSE);

Bool_t GetMixing();

Bool_t isRandomRejTask = kFALSE; //needed for InitHistograms() //dont change!!!
const TString RndmPtExpr = "exp(-x/3.)";
const Double_t RndmPtMin = 0.2;
const Double_t RndmPtMax = 10.0;
const Double_t RndmEtaMax = 0.8;
const Int_t nTestpartPerEle = 500; // number of testparticles used per final analysis electron in an event.

// TString names("nTPCcls;TPCcrossedRows;CrRowsOverFindable;Chi2TPC;nITScls;Chi2ITS;TPCclsCrRows;NoTPC;SharedClusterITS");
TString names("aodTrackCuts21;aodTrackCuts22;aodTrackCuts23;aodTrackCuts24;aodTrackCuts25;aodTrackCuts26;aodTrackCuts27;aodTrackCuts28;aodTrackCuts29;aodTrackCuts30");
//one with, one without prefilter to show effect
Bool_t kRot = 0;
Bool_t kMix = 1;

Bool_t randomizeDau = kFALSE;

TObjArray* arrNames = names.Tokenize(";");
const Int_t nDie = arrNames->GetEntriesFast();
Bool_t MCenabled = kFALSE;

AliDielectron* Config_sscheid_lowmass(Int_t cutDefinition, Bool_t isRandomRej)
{
  //
  // Setup the instance of AliDielectron
  //
  isRandomRejTask = isRandomRej;
  // create the actual framework object
  TString name = Form("%02d", cutDefinition);
  if (cutDefinition < arrNames->GetEntriesFast()) {
    name = arrNames->At(cutDefinition)->GetName();
  }
  AliDielectron* die =
    new AliDielectron(Form("%s", name.Data()),
                      Form("Track cuts: %s", name.Data()));

  if (kRot) {
    AliDielectronTrackRotator* rot = new AliDielectronTrackRotator;
    rot->SetConeAnglePhi(TMath::Pi());
    rot->SetIterations(10);
    die->SetTrackRotator(rot);
  } //kRot

  if (kMix) {
    AliDielectronMixingHandler* mix = new AliDielectronMixingHandler;
    mix->SetMixType(AliDielectronMixingHandler::kAll);
    mix->AddVariable(AliDielectronVarManager::kZvPrim, "-10., -7.5, -5., -2.5 , 0., 2.5, 5., 7.5 , 10.");
    mix->AddVariable(AliDielectronVarManager::kNacc, "0,10000");
    mix->SetDepth(20);
    die->SetMixingHandler(mix);
  } //kMix

  // set track cuts
  SetupCuts(die, cutDefinition);

  //
  // histogram setup
  // only if an AliDielectronHistos object is attached to the
  // dielectron framework histograms will be filled
  //

  InitHistograms(die, cutDefinition);

  die->SetNoPairing(kFALSE);

  return die;
}

AliDielectron* Config_sscheid_lowmass_pPb_FAST_AOD_3(Int_t cutDefinition, Bool_t isRandomRej)
{
  // Essentially a wrapper function for Config_sscheid_lowmass
  // Exec() of macro calls a function that is called like the Makro/file
  return Config_sscheid_lowmass(cutDefinition, isRandomRej);
}

//______________________________________________________________________________________
void SetupCuts(AliDielectron* die, Int_t cutDefinition)
{

  //Setup Event cuts
  die->GetEventFilter().AddCuts(dynamic_cast<AliAnalysisCuts*>(GetEventCuts())); // add event cuts to AliDielectron object not to analysis task - ROOT6
  // die->GetEventFilter().AddCuts( dynamic_cast<const AliAnalysisCuts *>(GetEventCuts())); // add event cuts to AliDielectron object not to analysis task - ROOT6

  // Setup the track cuts
  AliDielectronVarCuts* nSharedClsITS = new AliDielectronVarCuts("nSharedClsITS", "nSharedClsITS");
  nSharedClsITS->AddCut(AliDielectronVarManager::kNclsSITS, 1.0, 6.0, kTRUE);
  //This definition is bogus
  //Checked with patrick and its right but the code is stupid
  AliDielectronVarCuts* phiVcut = new AliDielectronVarCuts("phiVcut", "phiVcut");
  phiVcut->AddCut(AliDielectronVarManager::kPhivPair, 2.0, 3.2, kTRUE);
  phiVcut->AddCut(AliDielectronVarManager::kM, 0., 0.1, kTRUE);
  phiVcut->SetCutType(AliDielectronVarCuts::CutType::kAny);

  AliDielectronV0Cuts* noconv = new AliDielectronV0Cuts("IsGamma", "IsGamma");
  // which V0 finder you want to use
  noconv->SetV0finder(AliDielectronV0Cuts::kAll); // kAll(default), kOffline or kOnTheFly
  // add some pdg codes (they are used then by the KF package and important for gamma conversions)
  noconv->SetPdgCodes(22, 11, 11); // mother, daughter1 and 2
  // add default PID cuts (defined in AliDielectronPID)
  // requirement can be set to at least one(kAny) of the tracks or to both(kBoth)
  //noconv->SetDefaultPID(16, AliDielectronV0Cuts::kAny);
  // add the pair cuts for V0 candidates
  noconv->AddCut(AliDielectronVarManager::kCosPointingAngle, TMath::Cos(0.02), 1.00, kFALSE);
  noconv->AddCut(AliDielectronVarManager::kChi2NDF, 0.0, 10.00, kFALSE);
  noconv->AddCut(AliDielectronVarManager::kLegDist, 0.0, 0.25, kFALSE);
  noconv->AddCut(AliDielectronVarManager::kR, 3.0, 90.00, kFALSE);
  noconv->AddCut(AliDielectronVarManager::kPsiPair, 0.0, 0.05, kFALSE);
  noconv->AddCut(AliDielectronVarManager::kM, 0.0, 0.10, kFALSE);
  noconv->AddCut(AliDielectronVarManager::kArmPt, 0.0, 0.05, kFALSE);
  // selection or rejection of V0 tracks
  noconv->SetExcludeTracks(kTRUE);

  //pairing with TLorentzVector
  die->SetUseKF(kFALSE);

  AliDielectronVarCuts* pairCutsInvM = new AliDielectronVarCuts("pairCutsInvM", "pairCutsInvM");
  AliDielectronVarCuts* pairCutsOpAng = new AliDielectronVarCuts("pairCutsOpAng", "pairCutsOpAng");

  // die->GetTrackFilter().AddCuts(SetupPreFilterESDtrackCuts(cutDefinition));
  // die->GetPairPreFilterLegs().AddCuts(noconv);
  //pairPrefilter
  AliAnalysisCuts* pairPreCuts = 0x0;

  pairCutsInvM->AddCut(AliDielectronVarManager::kM, 0.0, 0.06);
  pairCutsOpAng->AddCut(AliDielectronVarManager::kOpeningAngle, 0.0, 0.050);

  AliDielectronCutGroup* pairCutsCG = new AliDielectronCutGroup("pairCutsCG", "pairCutsCG", AliDielectronCutGroup::kCompAND);
  pairCutsCG->AddCut(pairCutsInvM);
  pairCutsCG->AddCut(pairCutsOpAng);
  pairPreCuts = pairCutsCG;

  /* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv FILTER CUTS vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */
  // AOD track filter (needs to be first cut to speed up)
  AliDielectronTrackCuts* trkFilter = new AliDielectronTrackCuts("TrkFilter", "TrkFilter");
  trkFilter->SetAODFilterBit(AliDielectronTrackCuts::kTPCqual);
  trkFilter->SetRequireITSRefit(kTRUE);
  trkFilter->SetRequireTPCRefit(kTRUE);
  trkFilter->SetClusterRequirementITS(AliDielectronTrackCuts::kSPD, AliDielectronTrackCuts::kFirst);

  //only cut in OpAngle, doesnt matter really and correction not so complicated

  //FinalTrackCuts after prefiltering
  die->GetTrackFilter().AddCuts(trkFilter);
  die->GetTrackFilter().AddCuts(SetupPIDcuts(cutDefinition + 20));
  die->GetTrackFilter().AddCuts(SetupTrackCuts(cutDefinition + 20));

  SetEtaCorrectionTPCRMS(die, AliDielectronVarManager::kP, AliDielectronVarManager::kEta, AliDielectronVarManager::kRefMultTPConly, kFALSE);
  SetEtaCorrectionTPCMean(die, AliDielectronVarManager::kP, AliDielectronVarManager::kEta, AliDielectronVarManager::kRefMultTPConly, kFALSE);

  SetEtaCorrectionTOFRMS(die, AliDielectronVarManager::kP, AliDielectronVarManager::kEta, AliDielectronVarManager::kRefMultTPConly, kFALSE);
  SetEtaCorrectionTOFMean(die, AliDielectronVarManager::kP, AliDielectronVarManager::kEta, AliDielectronVarManager::kRefMultTPConly, kFALSE);

  die->SetPreFilterUnlikeOnly(kTRUE);

  // die->GetPairFilter().AddCuts(phiVcut);
  die->GetTrackFilter().AddCuts(noconv);
  die->GetTrackFilter().AddCuts(nSharedClsITS);

  //  if(cutDefinition == 0) {
  //  }
  //  if(cutDefinition == 1) {
  //  }
}
//______________________________________________________________________________________
//-----------------------------------pid------------------------------------------------

AliAnalysisCuts* SetupPIDcuts(Int_t cutDefinition)
{

  std::cout << ">>>>>>>>>>>> Setup PID cuts! <<<<<<<<<<<<" << '\n';
  //New PID standard cut: full PID setting with recovery of ITS and TOF tracks
  //accepts an electron if it's identified in one of the 3 detector samples

  AliDielectronPID* recover_TPC = new AliDielectronPID("recover_TPC", "recover_TPC");
  AliDielectronPID* recover_TOF = new AliDielectronPID("recover_TOF", "recover_TOF");

  //TPC electrons: includes electrons and exclude all possible other contributions using the TPC
  //possible elemination of contamination using ITS and TOF
  if (cutDefinition == 0) {
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.5, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3, 3., 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3, 3., 0.200, 100., kTRUE);

    //TOF electrons: includes all electrons, exlcludes Pions using the TPC
    //possible elemination of contamination using ITS
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE, AliDielectronPID::kRequire);
    // if the ITS identify a track as an electron include it back in
  }

  if (cutDefinition == 1) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.5, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -2.5, 3.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -2.5, 3.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 2) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.5, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.0, 3.0, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -2.5, 3.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 3) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -2.5, 3.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.0, 3.0, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 4) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.0, 3.0, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -2.5, 3.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -3.0, 3.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 5) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.0, 3.0, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.0, 3.0, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 6) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.5, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.0, 3.0, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -2.5, 3.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -3.0, 3.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 7) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.5, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.0, 3.0, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.0, 3.0, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 8) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.5, 2.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -2.5, 3.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -3.0, 3.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 9) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.5, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.5, 2.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -2.5, 3.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -3.0, 3.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 10) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.5, 2.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.0, 3.0, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 11) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.5, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -2.5, 3.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.0, 3.0, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -3.0, 3.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 12) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.5, 2.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -2.5, 3.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -3.0, 3.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 13) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.0, 3.0, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.5, 2.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -3.0, 3.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 14) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.0, 3.0, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -2.5, 3.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 15) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.5, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.5, 2.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.0, 3.0, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 16) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.5, 2.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -2.5, 3.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -3.0, 3.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 17) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -2.5, 3.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.0, 3.0, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -3.0, 3.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 18) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.5, 2.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.0, 3.0, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 19) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.0, 3.0, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.0, 3.0, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 20) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.5, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.5, 2.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.5, 2.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 21) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -2.5, 3.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -2.5, 3.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 22) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.5, 2.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.5, 2.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -3.0, 3.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 23) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -2.5, 3.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.5, 2.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 24) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.5, 2.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.5, 2.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 25) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -2., 2., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -2.5, 3.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.0, 3.0, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 26) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -2., 2., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.0, 3.0, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.0, 3.0, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 27) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -2., 2., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -2.5, 3.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.5, 2.5, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -3.0, 3.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 28) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -2., 2., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.5, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.5, 2.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.0, 3.0, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  if (cutDefinition == 29) {
    //TPC only sample
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -2., 2., 0., 100., kFALSE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 3.0, 0.00, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kKaon, -3.5, 2.5, 0.200, 100., kTRUE);
    recover_TPC->AddCut(AliDielectronPID::kTPC, AliPID::kProton, -3.0, 3.0, 0.200, 100., kTRUE);
    // TOF sample
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kElectron, -3., 3., 0.0, 100., kFALSE);
    recover_TOF->AddCut(AliDielectronPID::kTPC, AliPID::kPion, -100, 4., 0.0, 100., kTRUE);
    recover_TOF->AddCut(AliDielectronPID::kTOF, AliPID::kElectron, -2.0, 2.0, 0.0, 100., kFALSE, AliDielectronPID::kRequire);
  }

  // AliDielectronCutGroup* recover_cg = new AliDielectronCutGroup("recover_cg","recover_cg",AliDielectronCutGroup::kCompAND);
  AliDielectronCutGroup* recover_cg = new AliDielectronCutGroup("recover_cg", "recover_cg", AliDielectronCutGroup::kCompOR);
  recover_cg->AddCut(recover_TPC);
  recover_cg->AddCut(recover_TOF);

  AliAnalysisCuts* returnCut = NULL;
  returnCut = reinterpret_cast<AliAnalysisCuts*>(recover_cg);
  return returnCut;
}

//______________________________________________________________________________________
//-------------------------------prefilter pid------------------------------------------
//AliDielectronPID *SetPreFilterPIDcuts(Int_t cutDefinition){
//  AliDielectronPID *pid = new AliDielectronPID();
//    pid->AddCut(AliDielectronPID::kTPC,AliPID::kPion,    -100. ,4. ,0.0, 100., kTRUE ,AliDielectronPID::kIfAvailable,AliDielectronVarManager::kPt);
//    pid->AddCut(AliDielectronPID::kTOF,AliPID::kElectron,  -3. ,3. ,0.0, 100., kFALSE,AliDielectronPID::kIfAvailable,AliDielectronVarManager::kPt);
//    pid->AddCut(AliDielectronPID::kITS,AliPID::kElectron,  -3. ,0.5,0.0, 100., kFALSE,AliDielectronPID::kRequire    ,AliDielectronVarManager::kPt);
//    pid->AddCut(AliDielectronPID::kTPC,AliPID::kElectron,  -0.5,4. ,0.0, 100., kFALSE,AliDielectronPID::kIfAvailable,AliDielectronVarManager::kPt);
// return pid;
//}

//______________________________________________________________________________________
//-----------------------------------track cuts-----------------------------------------

//Reimplementation of SetupESDtrackCuts. Uses AliDielectronVarCuts to also be used in AOD analysis
AliDielectronVarCuts* SetupTrackCuts(Int_t cutDefinition)
{

  AliDielectronVarCuts* fTrackCuts = new AliDielectronVarCuts("fTrackCuts", "fTrackCuts");
  //global
  fTrackCuts->AddCut(AliDielectronVarManager::kPt, 0.4, 100.);        //SetPtRange( 0.2 , 100. );
  fTrackCuts->AddCut(AliDielectronVarManager::kEta, -0.8, 0.8);       //SetEtaRange( -0.8 , 0.8 );
  fTrackCuts->AddCut(AliDielectronVarManager::kImpactParXY, -1., 1.); //SetMaxDCAToVertexZ(3.);
  fTrackCuts->AddCut(AliDielectronVarManager::kImpactParZ, -3., 3.);  //SetMaxDCAToVertexXY(1.);

  if (cutDefinition == 0) {
    // fTrackCuts->AddCut(AliDielectronVarManager::kNclsTPC,       100., 160.);  //SetMinNClustersTPC(100);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 100., 160.);    //SetMinNClustersTPC(100);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.5, 1.1); //SetMinRatioCrossedRowsOverFindableClustersTPC(0.5);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 4.);       //SetMaxChi2PerClusterTPC(4);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 3., 10.);         //SetMinNClustersITS(3);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 5.5);      //SetMaxChi2PerClusterITS(5.5);
  }
  if (cutDefinition == 1) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 120.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.6, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 3.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 2.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 4.5);
  }

  if (cutDefinition == 2) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 120.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.6, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 3.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 3.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 6.5);
  }

  if (cutDefinition == 3) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 100.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.7, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 3.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 2.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 6.5);
  }

  if (cutDefinition == 4) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 120.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.5, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 4.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 3.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 4.5);
  }

  if (cutDefinition == 5) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 140.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.7, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 3.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 3.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 6.5);
  }

  if (cutDefinition == 6) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 140.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.7, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 5.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 2.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 5.5);
  }

  if (cutDefinition == 7) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 120.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.6, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 4.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 3.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 5.5);
  }

  if (cutDefinition == 8) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 140.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.6, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 3.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 3.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 4.5);
  }

  if (cutDefinition == 9) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 140.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.7, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 4.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 3.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 5.5);
  }

  if (cutDefinition == 10) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 100.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.5, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 4.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 4.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 4.5);
  }

  if (cutDefinition == 11) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 140.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.6, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 5.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 4.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 5.5);
  }

  if (cutDefinition == 12) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 100.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.7, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 5.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 4.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 5.5);
  }

  if (cutDefinition == 13) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 140.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.6, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 5.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 3.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 6.5);
  }

  if (cutDefinition == 14) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 100.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.7, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 5.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 3.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 6.5);
  }

  if (cutDefinition == 15) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 120.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.5, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 4.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 2.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 5.5);
  }

  if (cutDefinition == 16) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 120.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.6, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 5.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 4.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 4.5);
  }

  if (cutDefinition == 17) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 140.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.6, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 5.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 2.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 6.5);
  }

  if (cutDefinition == 18) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 140.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.7, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 4.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 2.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 6.5);
  }

  if (cutDefinition == 19) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 120.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.6, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 5.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 4.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 6.5);
  }

  if (cutDefinition == 20) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 140.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.6, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 4.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 2.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 5.5);
  }

  if (cutDefinition == 21) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 140.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.7, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 5.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 2.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 6.5);
  }

  if (cutDefinition == 22) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 100.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.5, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 3.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 3.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 6.5);
  }

  if (cutDefinition == 23) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 100.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.7, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 5.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 3.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 4.5);
  }

  if (cutDefinition == 24) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 120.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.6, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 5.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 2.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 4.5);
  }

  if (cutDefinition == 25) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 140.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.7, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 5.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 3.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 5.5);
  }

  if (cutDefinition == 26) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 100.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.7, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 4.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 3.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 6.5);
  }

  if (cutDefinition == 27) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 140.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.5, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 4.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 2.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 6.5);
  }

  if (cutDefinition == 28) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 100.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.7, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 5.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 3.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 4.5);
  }

  if (cutDefinition == 29) {
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCr, 100.0, 160.);
    fTrackCuts->AddCut(AliDielectronVarManager::kNFclsTPCfCross, 0.6, 1.1);
    fTrackCuts->AddCut(AliDielectronVarManager::kTPCchi2Cl, 0.0, 5.0);
    fTrackCuts->AddCut(AliDielectronVarManager::kNclsITS, 2.0, 10.);
    fTrackCuts->AddCut(AliDielectronVarManager::kITSchi2Cl, 0.0, 6.5);
  }

  AliDielectronVarCuts* returnCut = NULL;
  returnCut = fTrackCuts;
  return returnCut;
}

//______________________________________________________________________________________
//-------------------------------prefilter track cuts-----------------------------------
AliESDtrackCuts* SetupPreFilterESDtrackCuts(Int_t cutDefinition)
{

  AliESDtrackCuts* fesdTrackCuts = new AliESDtrackCuts;

  //global
  fesdTrackCuts->SetPtRange(0.08, 100.);
  fesdTrackCuts->SetEtaRange(-1.1, 1.1);
  fesdTrackCuts->SetAcceptKinkDaughters(kFALSE);
  fesdTrackCuts->SetRequireSigmaToVertex(kFALSE);
  fesdTrackCuts->SetDCAToVertex2D(kFALSE);
  fesdTrackCuts->SetMaxDCAToVertexZ(3.);
  fesdTrackCuts->SetMaxDCAToVertexXY(1.);

  //ITS cuts
  fesdTrackCuts->SetRequireITSRefit(kTRUE);
  fesdTrackCuts->SetMinNClustersITS(3);
  fesdTrackCuts->SetClusterRequirementITS(AliESDtrackCuts::kSPD, AliESDtrackCuts::kAny);

  return fesdTrackCuts;
}

void InitHistograms(AliDielectron* die, Int_t cutDefinition)
{

  //Setup histogram classes
  AliDielectronHistos* histos =
    new AliDielectronHistos(die->GetName(),
                            die->GetTitle());

  //Initialise histogram classes
  //histos->SetReservedWords("Track;Pair");
  histos->SetReservedWords("Track;Pair;Track_Legs;Pre;RejPair;RejTrack;Random");
  //histos->SetReservedWords("Track");

  //Event class
  histos->AddClass("Event");

  if (!isRandomRejTask) {
    //Track classes
    //to fill also track info from 2nd event loop until 2
    for (Int_t i = 0; i < 2; ++i) {
      histos->AddClass(Form("Track_%s", AliDielectron::TrackClassName(i)));
    }
    //Pair classes
    for (Int_t i = 0; i < 3; ++i) {
      histos->AddClass(Form("Pair_%s", AliDielectron::PairClassName(i)));
      // Legs of final Pairs. Both charges together. No duplicate entries.
    }
    //ME and track rot
    if (die->GetMixingHandler()) {
      histos->AddClass(Form("Pair_%s", AliDielectron::PairClassName(3)));
      histos->AddClass(Form("Pair_%s", AliDielectron::PairClassName(4)));
      histos->AddClass(Form("Pair_%s", AliDielectron::PairClassName(6)));
      histos->AddClass(Form("Pair_%s", AliDielectron::PairClassName(7)));
    }
    if (die->GetTrackRotator()) {
      histos->AddClass(Form("Pair_%s", AliDielectron::PairClassName(10)));
    }
  }
  if (isRandomRejTask) {
    //
    // _____ histograms for AliAnalysisTaskMultiDielectronPR _____
    //
    //    histos->AddClass("Rand_Pair");
    //    histos->AddClass("Rand_RejPair");
    const char* cRandomPairClassNames[2] = {"Testpart", "RejTestpart"};
    for (Int_t i = 0; i < 2; ++i) {
      histos->AddClass(Form("Random_%s", cRandomPairClassNames[i]));
    }
    histos->UserHistogram("Random", "Pt", "", 200, 0, 10., AliDielectronVarManager::kPt);
    histos->UserHistogram("Random", "Eta", "", 200, -2, 2, AliDielectronVarManager::kEta);
    histos->UserHistogram("Random", "Phi", "", 120, 0., TMath::TwoPi(), AliDielectronVarManager::kPhi);
    histos->UserHistogram("Random", "Px", "", 200, 0, 10., AliDielectronVarManager::kPx);
    histos->UserHistogram("Random", "Py", "", 200, 0, 10., AliDielectronVarManager::kPy);
    histos->UserHistogram("Random", "Pz", "", 200, 0, 10., AliDielectronVarManager::kPz);
    histos->UserHistogram("Random", "Pt_Eta_Phi", "",
                          500, 0., 10., 16, -0.8, 0.8, 30, 0., 2 * TMath::Pi(),
                          AliDielectronVarManager::kPt, AliDielectronVarManager::kEta, AliDielectronVarManager::kPhi);
  }

  //add histograms to event class
  histos->UserHistogram("Event", "nEvents", "Number of processed events after cuts;Number events", 1, 0, 1, AliDielectronVarManager::kNevents);
  histos->UserHistogram("Event", "ZVertex", "ZVertex;ZVertex/cm", 120, -12., 12., AliDielectronVarManager::kZvPrim);

  //add histograms to track class
  histos->UserHistogram("Track", "Pt", "Pt;Pt [GeV];#tracks", 500, 0., 10., AliDielectronVarManager::kPt);
  // histos->UserHistogram("Track","highPt","Pt;Pt [GeV];#tracks",500,0.,100.,AliDielectronVarManager::kPt);
  // histos->UserHistogram("Track","P","P;P [GeV];#tracks",500,0.,10.,AliDielectronVarManager::kP);
  // histos->UserHistogram("Track","PIn","PIn;PIn [GeV];#tracks",500,0.,10.,AliDielectronVarManager::kPIn);
  histos->UserHistogram("Track", "Eta_phi", "Eta vs Phi;Eta;Phi", 90, -0.9, 0.9, 160, 0., 6.4, AliDielectronVarManager::kEta, AliDielectronVarManager::kPhi);
  // histos->UserHistogram("Track","Pt_phi","Pt vs Phi;Pt;Phi [GeV];#tracks",500,0.,5.,320,0.,6.4,AliDielectronVarManager::kPt,AliDielectronVarManager::kPhi);
  // histos->UserHistogram("Track","ImpParXY","ImpParXY; ImpParXY ;#tracks",100,-5.,5.,AliDielectronVarManager::kImpactParXY);
  // histos->UserHistogram("Track","ImpParZ","ImpParZ; ImpParZ ;#tracks",100,-5.,5.,AliDielectronVarManager::kImpactParZ);
  // histos->UserHistogram("Track","ImpactParZsigma","ImpactParZsigma; ImpactParZsigma ;#tracks",100,-5.,5.,AliDielectronVarManager::kImpactParZsigma);

  // histos->UserHistogram("Track","NClusterTPC","NClusterTPC; NClusterTPC ;#tracks",200,-0.5,199.5,AliDielectronVarManager::kNclsTPC);
  // histos->UserHistogram("Track","CrossedRows","CrossedRows; CrossedRows ;#tracks",200,-0.5,199.5,AliDielectronVarManager::kNFclsTPCr);
  // histos->UserHistogram("Track","CrossedRowsOverFindable","CrRowsOverFindable; CrRows/FindableCls ;#tracks",120,0.,1.2,AliDielectronVarManager::kNFclsTPCfCross);
  // histos->UserHistogram("Track","TPCchi2perCls","TPCchi2perCls; TPCchi2perCls ;#tracks",100,0.,10.,AliDielectronVarManager::kTPCchi2Cl);
  //
  // histos->UserHistogram("Track","NClusterITS","NClusterITS; NClusterITS ;#tracks",8,-0.5,7.5,AliDielectronVarManager::kNclsITS);
  // histos->UserHistogram("Track","NSharedClusterITS","NSharedClusterITS; NSharedClusterITS ;#tracks",8,-0.5,7.5,AliDielectronVarManager::kNclsSITS);
  // histos->UserHistogram("Track","ITSchi2perCls","ITSchi2perCls; ITSchi2perCls ;#tracks",100,0.,10.,AliDielectronVarManager::kITSchi2Cl);
  //
  // histos->UserHistogram("Track","ImpactParXYsigmaPt","ImpactParXYsigma vs Pt; Pt; ImpactParXYsigma ;#tracks",100,0.,10.,100,-20.,20.,AliDielectronVarManager::kPt,AliDielectronVarManager::kImpactParXYsigma);
  // histos->UserHistogram("Track","ImpactParXYPt","ImpactParXY vs Pt; Pt; ImpactParXY ;#tracks",100,0.,10.,100,-2.,2.,AliDielectronVarManager::kPt,AliDielectronVarManager::kImpactParXY);
  //

  // histos->UserHistogram("Track","ITSdEdx_P","dEdx;P [GeV];ITS signal (arb units) vs Momentum;Mom;ITSsignal",     200,0.,10.,150,  0.,150. ,AliDielectronVarManager::kPIn,AliDielectronVarManager::kITSsignal);
  histos->UserHistogram("Track", "TPCdEdx_P", "dEdx;P [GeV];TPC signal (arb units) vs Momentum;Mom;TPCsignal", 200, 0., 10., 150, 0., 150., AliDielectronVarManager::kPIn, AliDielectronVarManager::kTPCsignal);
  histos->UserHistogram("Track", "TOFbeta_Mom", "kTOFbeta vs Momentum;Mom;TOFbeta", 200, 0., 10., 120, 0., 1.2, AliDielectronVarManager::kPIn, AliDielectronVarManager::kTOFbeta);

  histos->UserHistogram("Track", "TPCnSigma_MomEle", "TPC number of sigmas Electrons vs Momentum;p;TPCsigmaEle", 600, 0., 6., 400, -20., 20., AliDielectronVarManager::kPIn, AliDielectronVarManager::kTPCnSigmaEle);
  // histos->UserHistogram("Track","ITSnSigma_MomEle","ITS number of sigmas Electrons vs Momentum;p;ITSsigmaEle", 600,0.,6.,400,-20., 20. ,AliDielectronVarManager::kPIn,AliDielectronVarManager::kITSnSigmaEle);
  histos->UserHistogram("Track", "TOFnSigma_MomEle", "TOF number of sigmas Electrons vs Momentum;p;TOFsigmaEle", 600, 0., 6., 400, -20., 20., AliDielectronVarManager::kPIn, AliDielectronVarManager::kTOFnSigmaEle);
  //
  histos->UserHistogram("Track", "TPCnSigma_EtaEle", "TPC number of sigmas Electrons vs Eta;Eta;TPCsigmaEle", 200, -2., 2., 400, -20., 20., AliDielectronVarManager::kEta, AliDielectronVarManager::kTPCnSigmaEle);
  // histos->UserHistogram("Track","ITSnSigma_EtaEle","ITS number of sigmas Electrons vs Eta;Eta;ITSsigmaEle", 200,-2.,2.,400,-20., 20. ,AliDielectronVarManager::kEta,AliDielectronVarManager::kITSnSigmaEle);
  histos->UserHistogram("Track", "TOFnSigma_EtaEle", "TOF number of sigmas Electrons vs Eta;Eta;TOFsigmaEle", 200, -2., 2., 400, -20., 20., AliDielectronVarManager::kEta, AliDielectronVarManager::kTOFnSigmaEle);
  //
  // histos->UserHistogram("Track","TPCnSigma_PhiEle","TPC number of sigmas Electrons vs Phi;Phi;TPCsigmaEle", 200,0.,7.,400,-20., 20. ,AliDielectronVarManager::kPhi,AliDielectronVarManager::kTPCnSigmaEle);
  // histos->UserHistogram("Track","ITSnSigma_PhiEle","ITS number of sigmas Electrons vs Phi;Phi;ITSsigmaEle", 200,0.,7.,400,-20., 20. ,AliDielectronVarManager::kPhi,AliDielectronVarManager::kITSnSigmaEle);
  // histos->UserHistogram("Track","TOFnSigma_PhiEle","TOF number of sigmas Electrons vs Phi;Phi;TOFsigmaEle", 200,0.,7.,400,-20., 20. ,AliDielectronVarManager::kPhi,AliDielectronVarManager::kTOFnSigmaEle);

  //add histograms to pair classes

  //3d histos for pair dca

  TVectorD* MeeBins = AliDielectronHelper::MakeArbitraryBinning("0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.22,0.24,0.26,0.28,0.30,0.32,0.34,0.36,0.38,0.40,0.42,0.44,0.46,0.48,0.50,0.52,0.54,0.56,0.58,0.60,0.62,0.64,0.66,0.68,0.70,0.72,0.74,0.76,0.78,0.80,0.82,0.84,0.86,0.88,0.90,0.92,0.94,0.96,0.98,1.00,1.02,1.04,1.06,1.08,1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,2.10,2.20,2.30,2.40,2.50,2.60,2.70,2.80,2.90,3.00,3.02,3.04,3.06,3.08,3.10,3.12,3.30,3.50,4.00,5.00");
  // TVectorD *MeeBins = AliDielectronHelper::MakeArbitraryBinning("0.00,0.01,0.02,0.03,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.22,0.24,0.26,0.28,0.30,0.32,0.34,0.36,0.38,0.40,0.42,0.44,0.46,0.48,0.50,0.52,0.54,0.56,0.58,0.60,0.62,0.64,0.66,0.68,0.70,0.72,0.74,0.76,0.78,0.80,0.82,0.84,0.86,0.88,0.90,0.92,0.94,0.96,0.98,1.00,1.02,1.04,1.06,1.08,1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,2.10,2.20,2.30,2.40,2.50,2.60,2.70,2.80,2.90,3.00,3.02,3.04,3.06,3.08,3.10,3.12,3.30,3.50,4.00,5.00");
  //DCAee bins
  TVectorD* DCABins = AliDielectronHelper::MakeArbitraryBinning("0.0,0.4,0.8,1.2,1.6,2.0,2.4,2.8,3.2,3.6,4.0,4.4,4.8,5.2,5.6,6.0,6.4,6.8,7.2,7.6,8.0,8.4,8.8,9.2,9.6,10.0,10.4,10.8,11.2,11.6,12.0,12.4,12.8,13.2,13.6,14.0,14.4,14.8,15.2,15.6,16.0,16.4,16.8,17.2,17.6,18.0,18.4,18.8,19.2,19.6,20.0");
  // ptee bins
  // TVectorD *PteeBins = AliDielectronHelper::MakeArbitraryBinning("0.100,0.200,0.300,0.400,0.500,0.600,0.700,0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,4.000,4.100,4.200,4.300,4.400,4.500,5.000,5.500,6.000,6.500,7.000,8.000");
  TVectorD* PteeBins = AliDielectronHelper::MakeArbitraryBinning("0.000,0.050,0.100,0.150,0.200,0.250,0.300,0.350,0.400,0.450,0.500,0.550,0.600,0.650,0.700,0.750,0.800,0.850,0.900,0.950,1.000,1.100,1.200,1.300,1.400,1.500,1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,4.000,4.100,4.200,4.300,4.400,4.500,5.000,5.500,6.000,6.500,7.000,8.000");

  histos->UserHistogram("Pair", "InvMass_pPt_DCAsigma", "", MeeBins, PteeBins, DCABins,
                        AliDielectronVarManager::kM, AliDielectronVarManager::kPt, AliDielectronVarManager::kPairDCAsigXY);
  // histos->UserHistogram("Pair","InvMass_DCAsigma_pPt","",
  //                       250,0.,5, 40,0.,20., 80,0.,8.,
  //                       AliDielectronVarManager::kM, AliDielectronVarManager::kPairDCAsigXY, AliDielectronVarManager::kPt);

  // histos->UserHistogram("Pair","mee_PhiV","",100, 0., 4., 100, 0., 3.15, AliDielectronVarManager::kM,AliDielectronVarManager::kPhivPair);

  // Legs of rejected Pairs. Both charges together. One track can and will make multiple entries.
  histos->AddClass(Form("RejTrack_%s", AliDielectron::PairClassName(1))); // not TrackClassName, see 'AliDielectron::FillHistogramsPair(...)'
  //Create Classes for Rejected Tracks/Pairs:
  histos->AddClass(Form("RejPair_%s", AliDielectron::PairClassName(1)));
  histos->AddClass(Form("Track_Legs_%s", AliDielectron::PairClassName(0))); // not TrackClassName, see 'AliDielectron::FillHistograms(...)'
  histos->AddClass(Form("Track_Legs_%s", AliDielectron::PairClassName(1)));
  histos->AddClass(Form("Track_Legs_%s", AliDielectron::PairClassName(2)));

  histos->UserHistogram("RejPair",
                        "InvMass_pPt", "Inv.Mass_PairPt;m_{ee} (GeV/c^{2});p_{T,pair} (GeV/c)",
                        500, 0., 5., 250, 0., 5.,
                        AliDielectronVarManager::kM, AliDielectronVarManager::kPt);
  histos->UserHistogram("RejPair",
                        "OpAngle_InvMass", "InvMass_openingAngle;Invariant Mass;opening angle",
                        100, 0., 0.2, 100, 0., 0.2,
                        AliDielectronVarManager::kM, AliDielectronVarManager::kOpeningAngle);
  histos->UserHistogram("RejPair",
                        "InvMass_PhivPair", "InvMass_PhivPair;InvMass;PhivPair",
                        50, 0., 0.5, 160, 0., 3.2,
                        AliDielectronVarManager::kM, AliDielectronVarManager::kPhivPair);
  histos->UserHistogram("RejPair",
                        "Y", "Y;counts;Y",
                        60, -1.2, 1.2,
                        AliDielectronVarManager::kY);
  //    histos->UserHistogram("RejTrack","Pt",";Pt [GeV];#tracks",500,0,10.,AliDielectronVarManager::kPt);
  histos->UserHistogram("RejTrack", "Pt_charge", ";Pt [GeV];#tracks", 3, -1.5, 1.5, 500, 0, 10., AliDielectronVarManager::kCharge, AliDielectronVarManager::kPt);
  histos->UserHistogram("RejTrack", "Eta_phi", "Eta vs Phi;Eta;Phi", 90, -0.9, 0.9, 160, 0., 6.4, AliDielectronVarManager::kEta, AliDielectronVarManager::kPhi);
  histos->UserHistogram("RejTrack", "TPCnSigma_MomEle", "TPC number of sigmas Electrons vs Momentum;Mom;TPCsigmaEle", 200, 0., 10., 300, -30., 30., AliDielectronVarManager::kPIn, AliDielectronVarManager::kTPCnSigmaEle);

  //    histos->UserHistogram("Track_Legs","Pt",";Pt [GeV];#tracks",500,0,10.,AliDielectronVarManager::kPt);
  histos->UserHistogram("Track_Legs", "Pt_charge", "", 3, -1.5, 1.5, 500, 0, 10., AliDielectronVarManager::kCharge, AliDielectronVarManager::kPt);
  histos->UserHistogram("Track_Legs", "Eta_phi", "Eta vs Phi;Eta;Phi", 90, -0.9, 0.9, 160, 0., 6.4, AliDielectronVarManager::kEta, AliDielectronVarManager::kPhi);
  histos->UserHistogram("Track_Legs", "TPCnSigma_MomEle", "TPC number of sigmas Electrons vs Momentum;Mom;TPCsigmaEle", 200, 0., 10., 300, -30., 30., AliDielectronVarManager::kPIn, AliDielectronVarManager::kTPCnSigmaEle);

  die->SetHistogramManager(histos);
}

void InitCF(AliDielectron* die, Int_t cutDefinition)
{

  AliDielectronCF* cf = new AliDielectronCF(die->GetName(), die->GetTitle());

  //Add pair variables
  cf->AddVariable(AliDielectronVarManager::kM, 200, 0., 4.);                // Inv. Mass
  cf->AddVariable(AliDielectronVarManager::kPt, 60, 0., 6.);                // Pair pT
  cf->AddVariable(AliDielectronVarManager::kPairDCAsigXY, 50, 0., 20.);     // Pair DCA (sigma) square sum
  cf->AddVariable(AliDielectronVarManager::kPairLinDCAsigXY, 100, 0., 20.); // Pair DCA (sigma) linear sum
  cf->AddVariable(AliDielectronVarManager::kPairType, 11, 0., 11.);         // PairType
  //Add leg variables
  cf->AddVariable(AliDielectronVarManager::kPt, 200, 0., 10., kTRUE);
  //  cf->AddVariable(AliDielectronVarManager::kPdgCode,50, -20.,20.,kTRUE);
  //  cf->AddVariable(AliDielectronVarManager::kPdgCodeMother,50,-600.,600.,kTRUE);
  //  cf->AddVariable(AliDielectronVarManager::kPdgCodeGrandMother,50,-600.,600.,kTRUE);

  cf->SetStepsForMCtruthOnly(kTRUE);
  die->SetCFManagerPair(cf);
}

void SetSignalsMC(AliDielectron* die)
{

  // From Ionut "iarsene_correlations"
  AliDielectronSignalMC* promptJpsi = new AliDielectronSignalMC("promptJpsi", "Prompt J/psi"); // prompt J/psi (not from beauty decays)
  promptJpsi->SetLegPDGs(11, -11);
  promptJpsi->SetMotherPDGs(443, 443);
  promptJpsi->SetGrandMotherPDGs(503, 503, kTRUE, kTRUE); // not from beauty hadrons
  promptJpsi->SetMothersRelation(AliDielectronSignalMC::kSame);
  promptJpsi->SetFillPureMCStep(kTRUE);
  promptJpsi->SetLegSources(AliDielectronSignalMC::kFinalState, AliDielectronSignalMC::kFinalState);
  promptJpsi->SetCheckBothChargesLegs(kTRUE, kTRUE);
  promptJpsi->SetCheckBothChargesMothers(kTRUE, kTRUE);
  promptJpsi->SetCheckBothChargesGrandMothers(kTRUE, kTRUE);
  die->AddSignalMC(promptJpsi);

  AliDielectronSignalMC* beautyJpsi = new AliDielectronSignalMC("beautyJpsi", "beauty hadron -> J/psi"); // J/psi->e+e- from beauty hadron decays
  beautyJpsi->SetLegPDGs(11, -11);
  beautyJpsi->SetMotherPDGs(443, 443);
  beautyJpsi->SetMothersRelation(AliDielectronSignalMC::kSame);
  beautyJpsi->SetGrandMotherPDGs(503, 503);
  beautyJpsi->SetFillPureMCStep(kTRUE);
  beautyJpsi->SetLegSources(AliDielectronSignalMC::kFinalState, AliDielectronSignalMC::kFinalState);
  beautyJpsi->SetCheckBothChargesLegs(kTRUE, kTRUE);
  beautyJpsi->SetCheckBothChargesMothers(kTRUE, kTRUE);
  beautyJpsi->SetCheckBothChargesGrandMothers(kTRUE, kTRUE);
  die->AddSignalMC(beautyJpsi);

  AliDielectronSignalMC* beautyMesonJpsi = new AliDielectronSignalMC("beautyMesonJpsi", "beauty meson -> J/psi"); // J/psi->e+e- from beauty hadron decays
  beautyMesonJpsi->SetLegPDGs(11, -11);
  beautyMesonJpsi->SetMotherPDGs(443, 443);
  beautyMesonJpsi->SetMothersRelation(AliDielectronSignalMC::kSame);
  beautyMesonJpsi->SetGrandMotherPDGs(500, 500);
  beautyMesonJpsi->SetFillPureMCStep(kTRUE);
  beautyMesonJpsi->SetLegSources(AliDielectronSignalMC::kFinalState, AliDielectronSignalMC::kFinalState);
  beautyMesonJpsi->SetCheckBothChargesLegs(kTRUE, kTRUE);
  beautyMesonJpsi->SetCheckBothChargesMothers(kTRUE, kTRUE);
  beautyMesonJpsi->SetCheckBothChargesGrandMothers(kTRUE, kTRUE);
  die->AddSignalMC(beautyMesonJpsi);

  //Used pdg codes (defined in AliDielectronMC::ComparePDG)
  //401: open charm meson
  //404: charged open charmed mesons NO s quark
  //405: neutral open charmed mesons
  //406: charged open charmed mesons with s quark
  //501: open beauty mesons
  //503: all beauty hadrons
  //504: charged open beauty mesons NO s quark
  //505: neutral open beauty mesons
  //506: charged open beauty mesons with s quark
  //all D mesons

  // decay channels
  // (1) D -> e X
  // (1) B -> e X
  // (2) B -> D X -> e X Y
  // (3) B -> e D X -> ee X Y always produces ULS pair

  //useful functionality TODO: IMPLEMENT!
  //      SetCheckBothChargesSisters(kTRUE,kTRUE)
  //      SetCheckBothChargesAunts(kTRUE,kTRUE)
  //      SetAuntPDGs(Int_t pdg1, Int_t pdg2, Bool_t exclude1=kFALSE, Bool_t exclude2=kFALSE)
  // to select nieces the pdg for niece and sister(mother of niece) have to be set
  // include/ exclude via the pdgExclude of niece, not sister
  //      SetNiecesPDGs(Int_t pdg1, Int_t pdg2, Bool_t exclude1=kFALSE, Bool_t exclude2=kFALSE)
  //      SetSisterPDGs(Int_t pdg1, Int_t pdg2)

  //D+- meson (1)(1)
  AliDielectronSignalMC* diEleOpenCharmCharged = new AliDielectronSignalMC("DmesonsCharged", "di-electrons from open charm D+- mesons no B grandmother"); // dielectrons originating from open charm hadrons
  diEleOpenCharmCharged->SetLegPDGs(11, -11);
  diEleOpenCharmCharged->SetMotherPDGs(401, 401);
  diEleOpenCharmCharged->SetLegSources(AliDielectronSignalMC::kFinalState, AliDielectronSignalMC::kFinalState);
  diEleOpenCharmCharged->SetMothersRelation(AliDielectronSignalMC::kDifferent);
  diEleOpenCharmCharged->SetCheckStackForPDG(kTRUE);
  diEleOpenCharmCharged->SetPDGforStack(503);
  diEleOpenCharmCharged->SetCheckBothChargesLegs(kTRUE, kTRUE);
  diEleOpenCharmCharged->SetCheckBothChargesMothers(kTRUE, kTRUE);
  die->AddSignalMC(diEleOpenCharmCharged);
  //D0 meson (1)(1)
  AliDielectronSignalMC* diEleOpenCharmNeutral = new AliDielectronSignalMC("DmesonsNeutral", "di-electrons from open charm D0 mesons no B grandmother"); // dielectrons originating from open charm hadrons
  diEleOpenCharmNeutral->SetLegPDGs(11, -11);
  diEleOpenCharmNeutral->SetMotherPDGs(405, 405);
  diEleOpenCharmNeutral->SetLegSources(AliDielectronSignalMC::kFinalState, AliDielectronSignalMC::kFinalState);
  diEleOpenCharmNeutral->SetMothersRelation(AliDielectronSignalMC::kDifferent);
  diEleOpenCharmNeutral->SetCheckStackForPDG(kTRUE);
  diEleOpenCharmNeutral->SetPDGforStack(503);
  diEleOpenCharmNeutral->SetCheckBothChargesLegs(kTRUE, kTRUE);
  diEleOpenCharmNeutral->SetCheckBothChargesMothers(kTRUE, kTRUE);
  die->AddSignalMC(diEleOpenCharmNeutral);
  //B meson (3)
  AliDielectronSignalMC* diEleOneOpenB = new AliDielectronSignalMC("B2ee", "di-electrons from one B meson"); // dielectrons originating from open charm hadrons
  diEleOneOpenB->SetLegPDGs(11, -11);
  diEleOneOpenB->SetMotherPDGs(401, 501);
  diEleOneOpenB->SetLegSources(AliDielectronSignalMC::kFinalState, AliDielectronSignalMC::kFinalState);
  diEleOneOpenB->SetGrandMotherPDGs(501, 0);
  diEleOneOpenB->SetCheckMotherGrandmotherRelation(kTRUE, kTRUE);
  diEleOneOpenB->SetCheckBothChargesLegs(kTRUE, kTRUE);
  diEleOneOpenB->SetCheckBothChargesMothers(kTRUE, kTRUE);
  diEleOneOpenB->SetCheckBothChargesGrandMothers(kTRUE, kTRUE);
  die->AddSignalMC(diEleOneOpenB);

  //B meson (1)(1)
  AliDielectronSignalMC* diEleOpenB = new AliDielectronSignalMC("BMesons", "di-electrons from B mesons"); // dielectrons originating from open charm hadrons
  diEleOpenB->SetLegPDGs(11, -11);
  diEleOpenB->SetMotherPDGs(501, 501);
  diEleOpenB->SetLegSources(AliDielectronSignalMC::kFinalState, AliDielectronSignalMC::kFinalState);
  diEleOpenB->SetMothersRelation(AliDielectronSignalMC::kDifferent);
  diEleOpenB->SetCheckBothChargesLegs(kTRUE, kTRUE);
  diEleOpenB->SetCheckBothChargesMothers(kTRUE, kTRUE);
  die->AddSignalMC(diEleOpenB);

  //B meson (2)(2)
  AliDielectronSignalMC* diEleOpenBtoD = new AliDielectronSignalMC("B2D2ee", "di-electrons from B->D-> e"); // dielectrons originating from open charm hadrons
  diEleOpenBtoD->SetLegPDGs(11, -11);
  diEleOpenBtoD->SetMotherPDGs(401, 401);
  diEleOpenBtoD->SetLegSources(AliDielectronSignalMC::kFinalState, AliDielectronSignalMC::kFinalState);
  diEleOpenBtoD->SetGrandMotherPDGs(501, 501);
  diEleOpenBtoD->SetGrandMothersRelation(AliDielectronSignalMC::kDifferent);
  diEleOpenBtoD->SetCheckBothChargesLegs(kTRUE, kTRUE);
  diEleOpenBtoD->SetCheckBothChargesMothers(kTRUE, kTRUE);
  diEleOpenBtoD->SetCheckBothChargesGrandMothers(kTRUE, kTRUE);
  die->AddSignalMC(diEleOpenBtoD);

  //B meson (1)(2)
  AliDielectronSignalMC* diEleOpenBandBtoD = new AliDielectronSignalMC("B2eAndB2D2e", "di-electrons from B->e and B->D->e"); // dielectrons originating from open charm hadrons
  diEleOpenBandBtoD->SetLegPDGs(11, 11);
  diEleOpenBandBtoD->SetMotherPDGs(401, 501);
  diEleOpenBandBtoD->SetGrandMotherPDGs(501, 0);
  diEleOpenBandBtoD->SetLegSources(AliDielectronSignalMC::kFinalState, AliDielectronSignalMC::kFinalState);
  diEleOpenBandBtoD->SetCheckBothChargesLegs(kTRUE, kTRUE);
  diEleOpenBandBtoD->SetCheckBothChargesMothers(kTRUE, kTRUE);
  diEleOpenBandBtoD->SetCheckBothChargesGrandMothers(kTRUE, kTRUE);
  //do i need this?
  diEleOpenBandBtoD->SetCheckMotherGrandmotherRelation(kTRUE, kFALSE);
  die->AddSignalMC(diEleOpenBandBtoD);

  AliDielectronSignalMC* PiDalitz = new AliDielectronSignalMC("Pi0", "di-electrons from Pi0 dalitz"); // dielectrons originating from dalitz decays
  PiDalitz->SetLegPDGs(11, -11);
  PiDalitz->SetMotherPDGs(111, 111);
  PiDalitz->SetMothersRelation(AliDielectronSignalMC::kSame);
  PiDalitz->SetLegSources(AliDielectronSignalMC::kFinalState, AliDielectronSignalMC::kFinalState);
  PiDalitz->SetCheckBothChargesLegs(kTRUE, kTRUE);
  PiDalitz->SetCheckBothChargesMothers(kTRUE, kTRUE);
  die->AddSignalMC(PiDalitz);

  AliDielectronSignalMC* Conversion = new AliDielectronSignalMC("conv", "di-electrons from gamma conversions"); // dielectrons originating from dalitz decays
  Conversion->SetLegPDGs(11, -11);
  Conversion->SetMotherPDGs(22, 22);
  Conversion->SetMothersRelation(AliDielectronSignalMC::kSame);
  Conversion->SetLegSources(AliDielectronSignalMC::kSecondary, AliDielectronSignalMC::kSecondary);
  Conversion->SetCheckBothChargesLegs(kTRUE, kTRUE);
  die->AddSignalMC(Conversion);
  //eta eta prime omega phi  ->
}

AliDielectronEventCuts* GetEventCuts()
{

  AliDielectronEventCuts* eventCuts = new AliDielectronEventCuts("eventCuts", "Vertex Track && |vtxZ|<10 && ncontrib>0");
  eventCuts->SetVertexType(AliDielectronEventCuts::kVtxSPD); // AOD
  eventCuts->SetRequireVertex();
  eventCuts->SetVertexZ(-10., 10.);
  eventCuts->SetMinVtxContributors(1);

  return eventCuts;
}

void SetEtaCorrectionTPCMean(AliDielectron* die, Int_t corrXdim, Int_t corrYdim, Int_t corrZdim, Bool_t runwise)
{
  //
  // eta correction for the centroid and width of electron sigmas in the TPC, can be one/two/three-dimensional
  //
  std::cout << "Set eta correction width\n";
  std::string file_name = "~/analysis/pPb/PID/summary_TPC/outputTPC.root";

  TFile* _file = TFile::Open(file_name.c_str());
  std::cout << _file << std::endl;
  if (_file == 0x0) {
    gSystem->Exec("alien_cp alien:///alice/cern.ch/user/h/hscheid/supportFiles/PIDrecalibration/TPC/outputTPC.root file:.");
    std::cout << "Copy TPC correction from Alien" << std::endl;
    _file = TFile::Open("outputTPC.root");
    if (_file == 0x0) {
      printf("Did not find the file for mean\n");
      return;
    } else
      printf("Correction loaded\n");
  } else {
    std::cout << "Correction loaded" << std::endl;
  }
  if (runwise) {
    TObjArray* arr_mean = dynamic_cast<TObjArray*>(_file->Get("mean_correction_arr"));
    die->SetWidthCorrArr(arr_mean, kTRUE, corrXdim, corrYdim, corrZdim);
  } else {
    TH3D* mean = dynamic_cast<TH3D*>(_file->Get("sum_mean_correction"));
    die->SetCentroidCorrFunction(mean, corrXdim, corrYdim, corrZdim);
  }
}
void SetEtaCorrectionTPCRMS(AliDielectron* die, Int_t corrXdim, Int_t corrYdim, Int_t corrZdim, Bool_t runwise)
{
  //
  // eta correction for the centroid and width of electron sigmas in the TPC, can be one/two/three-dimensional
  //
  std::cout << "Set eta correction width\n";
  std::string file_name = "~/analysis/pPb/PID/summary_TPC/outputTPC.root";

  TFile* _file = TFile::Open(file_name.c_str());
  std::cout << _file << std::endl;
  // printf("%s",file_name);
  if (_file == 0x0) {
    gSystem->Exec("alien_cp alien:///alice/cern.ch/user/h/hscheid/supportFiles/PIDrecalibration/TPC/outputTPC.root file:.");
    std::cout << "Copy TPC correction from Alien" << std::endl;
    _file = TFile::Open("outputTPC.root");
    if (_file == 0x0) {
      printf("Did not find the file for sigma\n");
      return;
    } else
      printf("correction loaded\n");
  } else {
    std::cout << "Correction loaded" << std::endl;
  }
  if (runwise) {
    TObjArray* arr_width = dynamic_cast<TObjArray*>(_file->Get("width_correction_arr"));
    die->SetWidthCorrArr(arr_width, kTRUE, corrXdim, corrYdim, corrZdim);
  } else {
    TH3D* width = dynamic_cast<TH3D*>(_file->Get("sum_width_correction"));
    die->SetWidthCorrFunction(width, corrXdim, corrYdim, corrZdim);
  }
}

void SetEtaCorrectionTOFMean(AliDielectron* die, Int_t corrXdim, Int_t corrYdim, Int_t corrZdim, Bool_t runwise)
{
  //
  // eta correction for the centroid and width of electron sigmas in the TPC, can be one/two/three-dimensional
  //
  std::cout << "Set eta correction width\n";
  std::string file_name = "~/analysis/pPb/PID/summary_TOF/outputTOF.root";

  TFile* _file = TFile::Open(file_name.c_str());
  std::cout << _file << std::endl;
  if (_file == 0x0) {
    gSystem->Exec("alien_cp alien:///alice/cern.ch/user/h/hscheid/supportFiles/PIDrecalibration/TOF/outputTOF.root file:.");
    std::cout << "Copy TOF correction from Alien" << std::endl;
    _file = TFile::Open("outputTOF.root");
    if (_file == 0x0) {
      printf("Did not find the file for mean\n");
      return;
    } else
      printf("Correction loaded\n");
  } else {
    std::cout << "Correction loaded" << std::endl;
  }
  if (runwise) {
    TObjArray* arr_mean = dynamic_cast<TObjArray*>(_file->Get("mean_correction_arr"));
    die->SetWidthCorrArr(arr_mean, kTRUE, corrXdim, corrYdim, corrZdim);
  } else {
    TH3D* mean = dynamic_cast<TH3D*>(_file->Get("sum_mean_correction"));
    die->SetCentroidCorrFunction(mean, corrXdim, corrYdim, corrZdim);
  }
}
void SetEtaCorrectionTOFRMS(AliDielectron* die, Int_t corrXdim, Int_t corrYdim, Int_t corrZdim, Bool_t runwise)
{
  //
  // eta correction for the centroid and width of electron sigmas in the TPC, can be one/two/three-dimensional
  //
  std::cout << "Set eta correction width\n";
  std::string file_name = "~/analysis/pPb/PID/summary_TOF/outputTOF.root";

  TFile* _file = TFile::Open(file_name.c_str());
  std::cout << _file << std::endl;
  if (_file == 0x0) {
    gSystem->Exec("alien_cp alien:///alice/cern.ch/user/h/hscheid/supportFiles/PIDrecalibration/TOF/outputTOF.root file:.");
    std::cout << "Copy TOF correction from Alien" << std::endl;
    _file = TFile::Open("outputTOF.root");
    if (_file == 0x0) {
      printf("Did not find the file for sigma\n");
      return;
    } else
      printf("correction loaded\n");
  } else {
    std::cout << "Correction loaded" << std::endl;
  }
  if (runwise) {
    TObjArray* arr_width = dynamic_cast<TObjArray*>(_file->Get("width_correction_arr"));
    die->SetWidthCorrArr(arr_width, kTRUE, corrXdim, corrYdim, corrZdim);
  } else {
    TH3D* width = dynamic_cast<TH3D*>(_file->Get("sum_width_correction"));
    die->SetWidthCorrFunction(width, corrXdim, corrYdim, corrZdim);
  }
}

Bool_t GetMixing() { return kMix; }
