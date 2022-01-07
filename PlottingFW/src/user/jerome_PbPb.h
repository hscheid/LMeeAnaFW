// input data files. make sure to edit the other strings accordingly!

#include "LmBackground.h"

TString name[] = {
  "./input/data_PbPb/LMEE_LEGO1545_LHC18r.root",
  "./input/data_PbPb/LMEE_LEGO1546_LHC18q.root",
  "./input/data_PbPb/LMEE_LEGO1568_LHC18r.root",
  "./input/data_PbPb/LMEE_LEGO1569_LHC18q.root",
  "./input/data_PbPb/LMEE_LEGO1576_LHC18q.root",
  "./input/data_PbPb/LMEE_LEGO1577_LHC18r.root",
  "./input/data_PbPb/LMEE_LEGO1583_LHC18q.root",
  "./input/data_PbPb/LMEE_LEGO1584_LHC18r.root",
  "./input/data_PbPb/LMEE_LEGO1587_LHC18q.root",
  "./input/data_PbPb/LMEE_LEGO1595_LHC18q.root",

  "",
  ""
};
TString nameMC[] = {
  "",
  ""
};
//
// further details of input data
TString tree_name[] = { "Histos_diel_lowmass", "Histos_diel_lowmass_1", "Histos_diel_lowmass_2", "Histos_diel_lowmass_3", "Histos_diel_lowmass_4", "Histos_diel_lowmass_5", "Histos_diel_lowmass_6", "Histos_diel_lowmass_7" , "Histos_diel_lowmass_8", "Histos_diel_lowmass_9"};

TString cut_setting[] = { // always adapt to input data files!
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass40v2_TrCuts0_PIDCuts100wTOFwoITS_SCMAPcut2_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts120wTOFwITS_SCMAPcut2_noV0",
  "pT200_noPF_TrCuts0_PIDCuts121wTOFwoITS_SCMAPcut2_noV0",
  "pT200_noPF_TrCuts0_PIDCuts122wTOFwoITS_SCMAPcut2_noV0",

  "pT200_noPF_TrCuts0_PIDCuts120wTOFwoITS_SCMAPcut2_noV0",
  "pT200_noPF_TrCuts0_PIDCuts124wTOFwoITS_SCMAPcut2_noV0",
  "pT200_noPF_TrCuts0_PIDCuts123wTOFwoITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass40wOp2827.43v2_TrCuts0_PIDCuts123wTOFwoITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass40wOp3036.87v2_TrCuts0_PIDCuts123wTOFwoITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass100wOp3036.87v2_TrCuts0_PIDCuts123wTOFwoITS_SCMAPcut2_noV0",

  "pT200_noPF_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",
  "pT200_noPF_TrCuts0_PIDCuts125wTOFwoITS_SCMAPcut2_noV0",
  "pT200_noPF_TrCuts0_PIDCuts126wTOFwoITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass100wOp2932.15v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass20wOp2827.43v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass10wOp2722.71v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",

  "pT200_noPF_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",
  "pT200_noPF_TrCuts0_PIDCuts127wTOFwITS_SCMAPcut2_noV0",
  "pT200_noPF_TrCuts0_PIDCuts128wTOFwITS_SCMAPcut2_noV0", 
  "pT200_PF0wPID0wInvMass100wOp2827.43v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass100wOp2932.15v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass100wOp3036.87v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",

  "pT200_noPF_TrCuts0_PIDCuts123wTOFwITSwTRD_SCMAPcut2_noV0",
  "pT200_noPF_TrCuts0_PIDCuts127wTOFwITS_SCMAPcut2_noV0",
  "pT200_noPF_TrCuts0_PIDCuts128wTOFwITS_SCMAPcut2_noV0", 
  "pT200_PF0wPID0wInvMass100wOp2513.27v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass100wOp2617.99v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass100wOp2722.71v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",

  "pT200_noPF_TrCuts0_PIDCuts127wTOFwITSwTRD_SCMAPcut2_noV0",
  "pT200_noPF_TrCuts0_PIDCuts129wTOFwITSwTRD_SCMAPcut2_noV0",
  "pT200_noPF_TrCuts0_PIDCuts130wTOFwITSwTRD_SCMAPcut2_noV0", 
  "pT200_PF0wPID0wInvMass100wOp3036.87v2_TrCuts0_PIDCuts127wTOFwITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass100wOp3036.87v2_TrCuts0_PIDCuts129wTOFwITSwTRD_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass100wOp3036.87v2_TrCuts0_PIDCuts130wTOFwITSwTRD_SCMAPcut2_noV0",

  ""
};
TString cut_settingMC[] = { // always adapt to input data files!
  "",
  ""
};


TString pairMC[] = {
"", 
"/Pair_MCpair_sameMother", 
"/Pair_MCpair_diffMother/ULS", 
"/Pair_MCpair_sameGamma"
};


// corresponding input efficiency files
TString effi_name[] = {
  "",
  ""
};
// name of 2D generated and reconstructed histogram
TString effi_gen[] = {
  "NGenPairs_pt75",
  "NGenPairs_pt200",
  "jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances/NgenPairsRecResonances:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/charm/NgenPairsRecCharm:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/beauty/NgenPairsRecBeauty",
  "NgenPairsRec",
  "jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances/NgenPairsRecResonances",
  "NgenPairsRecResonances",
  "NgenPairsRecUnity",
  "NgenPairsRecAdded",
  ""
};
TString effi_rec[] = {
  "NRecPairs_hEff_Ele_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_pt75",
  "NRecPairs_hEff_Ele_pT75_noPF_TrCuts0_PIDCuts140wTOFwoITS_pt75",
  "NRecPairs_hEff_Ele_pT75_noPF_TrCuts0_PIDCuts600wTOFwoITS_pt75",
  "NRecPairs_hEff_Ele_pT75_noPF_TrCuts0_PIDCuts701wTOFwoITS_pt75",
  "NRecPairs_hEff_Ele_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_pt75", 
  "NRecPairs_hEff_Ele_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_pt200",
  "NRecPairs_hEff_Ele_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_pt200",
  "NRecPairs_hEff_Ele_pT200_noPF_TrCuts0_PIDCuts701wTOFwoITS_pt200",
  "NRecPairs_hEff_Ele_pT200_noPF_TrCuts0_PIDCuts701wTOFwoITS_SCcut_pt200",
  "NRecPairs_hEff_Ele_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_pt200",
  "NRecPairs_hEff_Ele_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_pt200",  //10
  "jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/charm/NrecoPairsCharm_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/beauty/NrecoPairsRecBeauty_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/charm/NrecoPairsCharm_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/beauty/NrecoPairsRecBeauty_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/charm/NrecoPairsCharm_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/beauty/NrecoPairsRecBeauty_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_pT75_noPF_TrCuts0_PIDCuts100,wTOFwoITS_SCcut_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/charm/NrecoPairsCharm_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/beauty/NrecoPairsRecBeauty_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "NrecoPairsRec", 
  "jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "NrecoPairsRecResonances",
  "NrecoPairsRecCharm",
  "NrecoPairsRecAdded",
  "NrecoPairsRecEfficiency", //20
  "NrecoPairsRecResonancesSmooth",
  "",
  ""
};

// cocktail files
TString cocktail_files[] = { // TODO: implement correct scaling if files have different centrality percentiles!!!
  // if this order here is changed, then check the use of 'which_cockt_files' in <main>.cpp file!!!
  "",
  ""
};

TString cocktail_list[] = {
  "LMeeCocktailMC/LMeeCocktailMC_0.80",
  ""
};


// cocktail histograms
TString cocktail_histograms[] = {
//  "pteevsmee_Pi0", //:pteevsmeeJPsi
//  "pteevsmee_Pi0:pteevsmee_Eta:pteevsmee_EtaPrim:pteevsmee_rho0:pteevsmee_omega:pteevsmee_phi", //:pteevsmeeJPsi
//  "pteevsmee_orig_Pi0:pteevsmee_orig_Eta:pteevsmee_orig_EtaP:pteevsmee_orig_Rho:pteevsmee_orig_Omega:pteevsmee_orig_Phi:pteevsmee_orig_Virtual_Photon",
  "pteevsmee_Pi0:pteevsmee_Eta:pteevsmee_EtaP:pteevsmee_Rho:pteevsmee_Omega:pteevsmee_Phi",
  "pteevsmee_Pi0:pteevsmee_EtaP:pteevsmee_Rho:pteevsmee_Omega:pteevsmee_Phi",
  "pteevsmee_Eta",





//  "pteevsmee_wEff_Pi0:pteevsmee_wEff_Eta:pteevsmee_wEff_EtaP:pteevsmee_wEff_Rho:pteevsmee_wEff_Omega:pteevsmee_wEff_Phi:pteevsmee_wEff_Virtual_Photon",
  "" 
};

//Short useCocktailVersion = 0;



// heavy flavour files
TString heavyfl_files[] = {
  //"input/cocktail_HF/HFcocktail_charm_newMNR.root:input/cocktail_HF/HFcocktail_BEAUTY.root"
};

//TString heavyfl_list = "lowee:lowee";
TString heavyfl_list = "loweepp_LHC17d1_new:lowee";


// heavy flavour histograms
TString heavyfl_histograms[] = {
  
  "hMeePtee_ULS_eta08_pt075-hMeePtee_LS_eta08_pt075:hMeePtee_ULS_eta08_pt075-hMeePtee_LS_eta08_pt075",
  //"hMeePtee_ULS_eta08_pt075:hMeePtee_ULS_eta08_pt075-hMeePtee_LS_eta08_pt075",

  "hMeePtee_ULS_eta08_pt200-hMeePtee_LS_eta08_pt200:hMeePtee_ULS_eta08_pt200-hMeePtee_LS_eta08_pt200",
  ""
};
// heavy flavour histograms for nevents
TString heavyfl_hist_Nevents[] = {
  "hRapCharmQuarkMethod1:hRapBeautyQuarkMethod1",
  "hNEvents:hNEvents",//"" ,hRapCharmQuarkMethod1
  ""
};

// j/psi files 
TString jpsi_files[] = {
  "input/cocktail_jpsi/JPsi-kpp-Std_low.root",
  "input/cocktail_jpsi/JPsi-kpp-Low_low.root",
  "input/cocktail_jpsi/JPsi-kpp-High_low.root", 
  //"input/cocktail_jpsi/JPsi-kpp-Std_nom.root",
  //"input/cocktail_jpsi/JPsi-kpp-Low_nom.root",
  //"input/cocktail_jpsi/JPsi-kpp-High_nom.root",
  "input/cocktail_jpsi/jpsi-pp2016f-pt75.root",
  "input/cocktail_jpsi/jpsi-pp2016f-pt200.root"
};

//TString jpsi_list = "Mee_Ptee_angleSmeared";  //_angleSmeared
TString jpsi_list[] = {
  "cocktailPt200rec",
  "cocktailPt075rec",
  ""
}; 

// j/psi histograms
TString jpsi_histograms[] = {
  "Mee_Ptee_Jpsi_std_angleSmeared",  //_angleSmeared
  "Mee_Ptee_Jpsi_low_angleSmeared",  //_angleSmeared
  "Mee_Ptee_Jpsi_high_angleSmeared",  //_angleSmeared
  "MeePteeJPsi"
};
// j/psi histograms for nevents
TString jspi_hist_Nevents[] = {
  ""
};






TString coll_system = "Pb--Pb #sqrt{#it{s}} = 5.02 TeV";
TString inputhist   = "InvMass_PairPt_PhivPair";
Int_t   inputdim    = 3;
TString projoption  = "yx"; // option="ab" means: a vertical, b horizontal (ROOT-convention)
// text for legend and maybe signal name
TString caption[] = { // do not use a colon(:)!

  "HR -2.5-3#sigma",
  "HR -2.5-3#sigma + SCM",
  "HR -2.5-3#sigma + PF + SCM",
  "HR -2.5-3#sigma + SC",
  "HR -2.5-3.#sigma + SCM + ITS if",
  "Best Carsten + SCM",
  "HR 3#sigma + SCM",

  "HR -2.5-3#sigma + SCM",
  "HR -2.0-3#sigma + SCM",
  "HR -2.0-3#sigma + SCM + hard Pi",
  "HR123 + SCM + PF27/30 & M40",
  "HR123 + SCM + PF29/30 & M40",
  "HR123 + SCM + PF29/30 & M100",

  "HR123 + full ITS",
  "HR123 + ITS if rej",
  "HR123 + ITS if (TOF)",
  "pT200_PF0wPID0wInvMass100wOp2932.15v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass20wOp2827.43v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass10wOp2722.71v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",


  "HR123 + ITS",
  "pT200_noPF_TrCuts0_PIDCuts127wTOFwITS_SCMAPcut2_noV0",
  "pT200_noPF_TrCuts0_PIDCuts128wTOFwITS_SCMAPcut2_noV0", 
  "pT200_PF0wPID0wInvMass100wOp2827.43v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass100wOp2932.15v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass100wOp3036.87v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",


  "HR123 + ITS +TOF",
  "HR123 + ITS2",
  "HR123 + ITS3", 
  "pT200_PF0wPID0wInvMass100wOp2513.27v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass100wOp2617.99v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",
  "pT200_PF0wPID0wInvMass100wOp2722.71v2_TrCuts0_PIDCuts123wTOFwITS_SCMAPcut2_noV0",

  "pT200_noPF_TrCuts0_PIDCuts127wTOFwITSwTRD_SCMAPcut2_noV0",
  "HR123 + ITS + TRD",
  "pT200_noPF_TrCuts0_PIDCuts130wTOFwITSwTRD_SCMAPcut2_noV0", 
  "pT200_PF0wPID0wInvMass100wOp3036.87v2_TrCuts0_PIDCuts127wTOFwITS_SCMAPcut2_noV0",
  "HR123 + ITS + TRD + PF",
  "pT200_PF0wPID0wInvMass100wOp3036.87v2_TrCuts0_PIDCuts130wTOFwITSwTRD_SCMAPcut2_noV0",


  ""
};
// config string for manager
TString cconfig[] = { // this determines which settings will really be analysed! check to select the correct cut_setting!

  
//  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[0]  + ":" + caption[0] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),
//  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[0]  + ":" + caption[0] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[1]  + ":" + caption[1] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[1]  + ":" + caption[1] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[2]  + ":" + caption[2] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),
//  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[2]  + ":" + caption[2] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[3]  + ":" + caption[3] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[3]  + ":" + caption[3] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[4]  + ":" + caption[4] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[4]  + ":" + caption[4] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[5]  + ":" + caption[5] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[5]  + ":" + caption[5] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[6]  + ":" + caption[6] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[6]  + ":" + caption[6] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  


//  (coll_system + ":" + name[2] + ":" + tree_name[0] + ":" + cut_setting[7]  + ":" + caption[7] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),
//  (coll_system + ":" + name[3] + ":" + tree_name[0] + ":" + cut_setting[7]  + ":" + caption[7] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[2] + ":" + tree_name[0] + ":" + cut_setting[8]  + ":" + caption[8] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[3] + ":" + tree_name[0] + ":" + cut_setting[8]  + ":" + caption[8] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[2] + ":" + tree_name[0] + ":" + cut_setting[9]  + ":" + caption[9] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),
//  (coll_system + ":" + name[3] + ":" + tree_name[0] + ":" + cut_setting[9]  + ":" + caption[9] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[2] + ":" + tree_name[0] + ":" + cut_setting[10]  + ":" + caption[10] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[3] + ":" + tree_name[0] + ":" + cut_setting[10]  + ":" + caption[10] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[2] + ":" + tree_name[0] + ":" + cut_setting[11]  + ":" + caption[11] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[3] + ":" + tree_name[0] + ":" + cut_setting[11]  + ":" + caption[11] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[2] + ":" + tree_name[0] + ":" + cut_setting[12]  + ":" + caption[12] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[3] + ":" + tree_name[0] + ":" + cut_setting[12]  + ":" + caption[12] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  

//  (coll_system + ":" + name[4] + ":" + tree_name[0] + ":" + cut_setting[13]  + ":" + caption[13] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),
//  (coll_system + ":" + name[5] + ":" + tree_name[0] + ":" + cut_setting[13]  + ":" + caption[13] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[4] + ":" + tree_name[0] + ":" + cut_setting[14]  + ":" + caption[14] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[5] + ":" + tree_name[0] + ":" + cut_setting[14]  + ":" + caption[14] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[4] + ":" + tree_name[0] + ":" + cut_setting[15]  + ":" + caption[15] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),
//  (coll_system + ":" + name[5] + ":" + tree_name[0] + ":" + cut_setting[15]  + ":" + caption[15] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[4] + ":" + tree_name[0] + ":" + cut_setting[16]  + ":" + caption[16] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[5] + ":" + tree_name[0] + ":" + cut_setting[16]  + ":" + caption[16] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[4] + ":" + tree_name[0] + ":" + cut_setting[17]  + ":" + caption[17] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[5] + ":" + tree_name[0] + ":" + cut_setting[17]  + ":" + caption[17] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[4] + ":" + tree_name[0] + ":" + cut_setting[18]  + ":" + caption[18] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[5] + ":" + tree_name[0] + ":" + cut_setting[18]  + ":" + caption[19] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  

//  (coll_system + ":" + name[6] + ":" + tree_name[0] + ":" + cut_setting[19]  + ":" + caption[19] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),
//  (coll_system + ":" + name[7] + ":" + tree_name[0] + ":" + cut_setting[19]  + ":" + caption[19] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[6] + ":" + tree_name[0] + ":" + cut_setting[20]  + ":" + caption[20] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[7] + ":" + tree_name[0] + ":" + cut_setting[20]  + ":" + caption[20] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[6] + ":" + tree_name[0] + ":" + cut_setting[21]  + ":" + caption[21] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),
//  (coll_system + ":" + name[7] + ":" + tree_name[0] + ":" + cut_setting[21]  + ":" + caption[21] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[6] + ":" + tree_name[0] + ":" + cut_setting[22]  + ":" + caption[22] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[7] + ":" + tree_name[0] + ":" + cut_setting[22]  + ":" + caption[22] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[6] + ":" + tree_name[0] + ":" + cut_setting[23]  + ":" + caption[23] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[7] + ":" + tree_name[0] + ":" + cut_setting[23]  + ":" + caption[23] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[6] + ":" + tree_name[0] + ":" + cut_setting[24]  + ":" + caption[24] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[7] + ":" + tree_name[0] + ":" + cut_setting[24]  + ":" + caption[24] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  


//  (coll_system + ":" + name[8] + ":" + tree_name[0] + ":" + cut_setting[25]  + ":" + caption[25] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[8] + ":" + tree_name[0] + ":" + cut_setting[26]  + ":" + caption[26] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[8] + ":" + tree_name[0] + ":" + cut_setting[27]  + ":" + caption[27] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[8] + ":" + tree_name[0] + ":" + cut_setting[28]  + ":" + caption[28] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[8] + ":" + tree_name[0] + ":" + cut_setting[29]  + ":" + caption[29] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[8] + ":" + tree_name[0] + ":" + cut_setting[30]  + ":" + caption[30] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  

//  (coll_system + ":" + name[9] + ":" + tree_name[0] + ":" + cut_setting[31]  + ":" + caption[31] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
  (coll_system + ":" + name[9] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + caption[32] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[9] + ":" + tree_name[0] + ":" + cut_setting[33]  + ":" + caption[33] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ), 
//  (coll_system + ":" + name[9] + ":" + tree_name[0] + ":" + cut_setting[34]  + ":" + caption[34] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
  (coll_system + ":" + name[9] + ":" + tree_name[0] + ":" + cut_setting[35]  + ":" + caption[35] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  
//  (coll_system + ":" + name[9] + ":" + tree_name[0] + ":" + cut_setting[36]  + ":" + caption[36] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] +":"+""+":"+""+":"+"" ),  

  "empty" // needed to avoid anger with ',' at the end of the last active line
};

Int_t n_config = sizeof(cconfig)/sizeof(*cconfig) -1; // '-1' to neglect the "empty" entry.



//
// desired binning for output. will also be used for efficiency correction.
// binning has to be compatible with input. [PR/CK: see function GetVector() of Config_user_LMEEPbPb.C]

  Double_t mee_bins[]  = { 
      0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.08,
      0.10,0.12,0.15,//0.16,0.18,
      0.20,0.25,
      0.30,0.35,
      0.40,
      0.50,
      0.60,
      0.70,
      0.80,0.85,
      0.90,0.95,
      1.00,1.05,
      1.10,1.20,1.40,1.60,1.80,2.00,
      2.20,2.40,2.60,2.80,3.00,
      3.06,3.10,3.30,3.50,4.00
  }; //Jerome data


  //////LMR spectra
  //Double_t mee_bins_plotting[]  = {
  //    0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.08,
  //    0.10,0.12,0.15,//0.16,0.18,
  //    0.20,0.25,
  //    0.30,0.35,
  //    0.40,
  //    0.50,
  //    0.60,
  //    0.70,
  //    0.80,0.85,
  //    0.90,0.95,
  //    1.00,1.05,
  //    1.10,1.20,1.40,1.60,1.80,2.00,
  //    2.20,2.40,2.60,2.80,3.00,
  //    3.06,3.10,3.30,3.50,4.00
  //}; //Jerome data
  
 Double_t mee_bins_plotting[]  = {0.00,0.04,.14,0.6,1.1,2.6, 4.0};  
 
 Double_t mee_bins_cocktail[]  = { 
     0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.08,
     0.10,0.12,0.15,//0.18,
     0.20,0.25,
     0.30,0.35,
     0.40,
     0.50,0.59,
     0.60,
     0.70,
     0.80,0.85,
     0.90,0.95,
     1.00,1.05,
     1.10,1.20,1.40,1.60,1.80,2.00,
     2.20,2.40,2.60,2.80,3.00,
     3.06,3.10,3.30,3.50,4.00
 }; //Jerome data


  Double_t mee_bins_plotting_0[]  = { 
 
    0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.22,0.24,0.26,0.28,0.30,0.32,0.34,0.36,0.38,0.40,0.42,0.44,0.46,0.48,0.50,0.52,0.54,0.56,0.58,
    0.60,0.62,0.64,0.66,0.68,
    0.70,0.72,0.74,0.76,0.78,
    0.80,0.82,0.84,0.86,0.88,
    0.90,0.92,0.94,0.96,0.98,
    1.00,1.02,1.04,1.06,1.08,
    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,2.20,2.40,2.60,2.80,3.00,3.10,3.30,3.50,4.00

  }; //Jerome data

  Double_t mee_bins_plotting_1[]  = { 
 
    0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.22,0.24,0.26,0.28,0.30,0.32,0.34,0.36,0.38,0.40,0.42,0.44,0.46,0.48,0.50,0.52,0.54,0.56,0.58,
    0.60,0.62,0.64,0.66,0.68,
    0.70,0.72,0.74,0.76,0.78,
    0.80,0.82,0.84,0.86,0.88,
    0.90,0.92,0.94,0.96,0.98,
    1.00,1.02,1.04,1.06,1.08,
    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,2.20,2.40,2.60,2.80,3.00,3.10,3.30,3.50,4.00

  }; //Jerome data

  Double_t mee_bins_plotting_2[]  = { 
 
    0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,
    0.60,0.65,
    0.70,0.75,
    0.80,0.85,
    0.90,0.95,
    1.00,1.05,
    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,2.20,2.40,2.60,2.80,3.00,3.10,3.30,3.50,4.00

  }; //Jerome data

  Double_t mee_bins_plotting_3[]  = { 
 
    0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,
    0.60,0.65,
    0.70,0.75,
    0.80,0.85,
    0.90,0.95,
    1.00,1.05,
    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,2.20,2.40,2.60,2.80,3.00,3.10,3.30,3.50,4.00

  }; //Jerome data

  Double_t mee_bins_plotting_4[]  = { 
 
    0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.30,0.40,0.50,
    0.60,//0.64,0.68,
    0.70,//0.72,0.74,0.76,0.78,
    0.80,//0.82,0.84,0.86,0.88,
    0.90,//0.92,0.94,0.96,0.98,
    1.00,//1.02,1.04,1.06,
    1.10,1.30,1.50,1.70,1.80,1.90,2.00,2.20,2.40,2.60,2.80,3.00,3.10,3.30,3.50,4.00

  }; //Jerome data

  Double_t mee_bins_plotting_5[]  = { 
 
    0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.22,0.24,0.26,0.28,0.30,0.32,0.34,0.36,0.38,0.40,0.42,0.44,0.46,0.48,0.50,0.52,0.54,0.56,0.58,
    0.60,0.62,0.64,0.66,0.68,
    0.70,0.72,0.74,0.76,0.78,
    0.80,0.82,0.84,0.86,0.88,
    0.90,0.92,0.94,0.96,0.98,
    1.00,1.01,1.02,1.03,1.04,1.05,1.06,1.07,1.08,1.09,
    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,2.20,2.40,2.60,2.80,3.00,3.10,3.30,3.50,4.00

  }; //Jerome data




Double_t ptee_bins[] = {

    0.000,0.050,0.100,0.200,0.300,0.400,0.500,0.600,0.700,
    0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
    1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
    2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
    3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
    4.000,4.500,5.000,6.000,8.000,10.

};

Double_t ptee_bins_plotting[] = {0.00,0.02,0.04,0.06,0.07,0.08,0.09,
                                 0.10,0.12,0.14,0.16,0.18,
                                 0.20,0.22,0.24,0.26,0.28,
                                 0.30,0.32,0.34,0.36,0.38,
                                 0.40,0.42,0.44,0.46,0.48,
                                 0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,
                                 1.00,1.10,1.20,1.30,1.40,
                                 1.50,
                                 2.00,
                                 2.50,3.00,3.50,
                                 4.00,5.00,
                                 6.00,8.00,10.0
};

Double_t ptee_bins_cocktail[] = {

    0.000,0.050,0.100,0.200,0.300,0.400,0.500,0.600,0.700,
    0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
    1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
    2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
    3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
    4.000,4.500,5.000,6.000,8.000,10.

};


Double_t ptee_bins_plotting_0[] = {
    0.000,0.050,0.100,0.200,0.300,0.400,0.500,0.600,0.700,
    0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
    1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
    2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
    3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
    4.000,4.500,5.000,6.000,8.000,10.
};

Double_t ptee_bins_plotting_1[] = {

    0.000,0.100,0.200,0.300,0.400,0.500,0.600,0.700,

    0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
    1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
    2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
    3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
    4.000,4.500,5.000,6.000,8.000,10.

};

Double_t ptee_bins_plotting_2[] = {

    0.000,0.100,0.200,0.400,0.600,
    0.800,1.000,1.200,1.400,
    1.600,1.800,2.000,2.200,
    2.400,2.600,2.800,3.000,
    3.200,3.400,3.600,3.800,
    4.000,4.500,5.000,6.000,8.000,10.

};

Double_t ptee_bins_plotting_3[] = { 0.00,2.0,6.0,10.}; //new Binning 2
Double_t ptee_bins_plotting_4[] = { 0.00,2.0,6.0,10.}; //new Binning 2
Double_t ptee_bins_plotting_5[] = { 0.00,2.0,6.0,10.}; //new Binning 2






Int_t n_mee_bin = sizeof(mee_bins)/sizeof(*mee_bins) -1;
Int_t n_ptee_bin = sizeof(ptee_bins)/sizeof(*ptee_bins) -1;

Int_t n_mee_bin_plotting  = sizeof(mee_bins_plotting)/sizeof(*mee_bins_plotting) -1;
Int_t n_ptee_bin_plotting = sizeof(ptee_bins_plotting)/sizeof(*ptee_bins_plotting) -1;

Int_t n_mee_bin_plotting_0 = sizeof(mee_bins_plotting_0)/sizeof(*mee_bins_plotting_0) -1;
Int_t n_mee_bin_plotting_1 = sizeof(mee_bins_plotting_1)/sizeof(*mee_bins_plotting_1) -1;
Int_t n_mee_bin_plotting_2 = sizeof(mee_bins_plotting_2)/sizeof(*mee_bins_plotting_2) -1;
Int_t n_mee_bin_plotting_3 = sizeof(mee_bins_plotting_3)/sizeof(*mee_bins_plotting_3) -1;
Int_t n_mee_bin_plotting_4 = sizeof(mee_bins_plotting_4)/sizeof(*mee_bins_plotting_4) -1;
Int_t n_mee_bin_plotting_5 = sizeof(mee_bins_plotting_5)/sizeof(*mee_bins_plotting_5) -1;



Int_t n_ptee_bin_plotting_0 = sizeof(ptee_bins_plotting_0)/sizeof(*ptee_bins_plotting_0) -1;
Int_t n_ptee_bin_plotting_1 = sizeof(ptee_bins_plotting_1)/sizeof(*ptee_bins_plotting_1) -1;
Int_t n_ptee_bin_plotting_2 = sizeof(ptee_bins_plotting_2)/sizeof(*ptee_bins_plotting_2) -1;
Int_t n_ptee_bin_plotting_3 = sizeof(ptee_bins_plotting_3)/sizeof(*ptee_bins_plotting_3) -1;
Int_t n_ptee_bin_plotting_4 = sizeof(ptee_bins_plotting_4)/sizeof(*ptee_bins_plotting_4) -1;
Int_t n_ptee_bin_plotting_5 = sizeof(ptee_bins_plotting_5)/sizeof(*ptee_bins_plotting_5) -1;



std::vector<Double_t> mee_bin(mee_bins, mee_bins + sizeof(mee_bins)/sizeof(*mee_bins)); 
std::vector<Double_t> ptee_bin(ptee_bins, ptee_bins + sizeof(ptee_bins)/sizeof(*ptee_bins));

Int_t n_mee_bin_cocktail = sizeof(mee_bins_cocktail)/sizeof(*mee_bins_cocktail) -1;
Int_t n_ptee_bin_cocktail = sizeof(ptee_bins_cocktail)/sizeof(*ptee_bins_cocktail) -1;

std::vector<Double_t> mee_bin_cocktail(mee_bins_cocktail, mee_bins_cocktail + sizeof(mee_bins_cocktail)/sizeof(*mee_bins_cocktail)); 
std::vector<Double_t> ptee_bin_cocktail(ptee_bins_cocktail, ptee_bins_cocktail + sizeof(ptee_bins_cocktail)/sizeof(*ptee_bins_cocktail));



Double_t phiv_bin[] = { 1 }; // if only one number is given, it will be used for Rebin(n).
Int_t n_phiv_bin = sizeof(phiv_bin)/sizeof(*phiv_bin) -1;
//
// systematic
// bin edges must match with the projection bins of the final data handler!
Double_t* mee_bin_sys = mee_bins_plotting;
Double_t* ptee_bin_sys = ptee_bins_plotting;
Int_t n_mee_bin_sys = sizeof(mee_bin_sys)/sizeof(*mee_bin_sys) -1;
Int_t n_ptee_bin_sys = sizeof(ptee_bin_sys)/sizeof(*ptee_bin_sys) -1;
 
std::vector<double> mee_bin_systematic_coarse{
  0.00,0.04,0.14,0.60,1.1,2.80,3.10,4.00// Realistic binning
};
std::vector<double> ptee_bin_systematic_coarse{
  0.0, 10.
};

std::vector<double> unc_bins_mee = {0.00,0.04,0.14,1.1,2.8,3.1,4.0}; 
std::vector<double> unc_bins_ptee = {0., 10.};






Double_t mee_slices[]  = {0.00,0.04,.14,0.6,1.1,2.6, 4.0}; 
Double_t ptee_slices[] = {0.00,1., 2.0,4., 10.};


Int_t n_mee_slices = sizeof(mee_slices)/sizeof(*mee_slices) -1;
Int_t n_ptee_slices = sizeof(ptee_slices)/sizeof(*ptee_slices) -1;



// PhiV-cut that shall be applied
Double_t cutPhiVbelow[] = { 0., 0., 0., 0.};
Double_t cutPhiVabove[] = { 2., 2., 2., 2.};  //3./4.  0.6
Double_t cutEdgesMee[]  = { 0.01, 0.02 ,0.03, 0.1};



Int_t    n_cutPhiVbelow = sizeof(cutPhiVbelow)/sizeof(*cutPhiVbelow);
Int_t    n_cutPhiVabove = sizeof(cutPhiVabove)/sizeof(*cutPhiVabove);
Int_t    n_cutEdgesMee  = sizeof(cutEdgesMee)/sizeof(*cutEdgesMee);


Double_t plotMeeMin  = 0., plotMeeMax = 3.5;    //3.5
Double_t plotPteeMin = 0.0, plotPteeMax = 6.;  //6.0

Int_t     kBkgEstimator          = LmBackground::kHybrid;  //LmBackground::kHybrid, LmBackground::kArith, LmBackground::kGeom
Int_t     kDoPhiVCut             = 2; // 0:noCut  2:DoCut  4:FlatCorrSub  6:kTemplUnsub  7:kTemplSub

Bool_t    kDoSignifRaw           = kTRUE;
Bool_t    kDoNormNevents         = kTRUE;
Bool_t    kDoNormBinwidth        = kTRUE;
Bool_t    kDoRfactor             = kTRUE;
Bool_t    kDoEffiCorrection      = kFALSE;
Bool_t    kDoEffiCorrectionFirst = kFALSE;
Bool_t    kDoConfLevel           = kFALSE;
Double_t  confLevel              = 0.84;
Bool_t    kDoRatio               = kTRUE;
Bool_t    kDoBinominal           = kFALSE;
Double_t  kRatioLow              = 0.2; //0.2 0.6 
Double_t  kRatioHigh             = 3.29;//53.49; //2.29, 3.69
Bool_t    kDoRatioLog            = kFALSE;
Bool_t    kDoCocktail            = kFALSE;
Int_t     debug                  = 1000;
Bool_t    doPhiVtemplates        = kFALSE;  //with MC cut settings, without effcorr otherwise mee_ptee efficiency will be applied on phiV_ptee
Bool_t    doPhiVstudy            = kFALSE;  //without effcorr
Bool_t    DoCorrelationPlots     = kTRUE;
Bool_t    doVirtualPhotonFits    = kFALSE;


Bool_t    DoQA                   = kFALSE;
Bool_t    DoTOFeffPlots          = kFALSE;

//Bool_t    kDoMassSlices          = kTRUE;  //kTRUE: do mass slices  kFALSE: do pair pt slices
Bool_t    kDoIntegrated          = kFALSE;
Bool_t    kDoCombineSpectra      = kFALSE;
Bool_t    kDoMergeMultiple       = kFALSE;
Int_t     kStartMergeAt          = 0;
Int_t     kStopMergeAt           = 99;
Int_t     kMergeNSettings        = 2;
Bool_t    kDoPlotOnlyFirstIn     = kFALSE;
Bool_t    kDoPlotCombineOnly     = kTRUE;

Bool_t    kDoSystematics         = kFALSE;
Bool_t    kDoFixedSystematics    = kFALSE;
Bool_t    kDoNonLogY             = kFALSE;
Bool_t    kDoNonLogX             = kTRUE;

Bool_t    kDoCocktailSubtraction  = kFALSE;
Bool_t    kDoCocktailSubtraction2D= kFALSE;
Bool_t    kDoAcceptanceCorrection = kFALSE;
Bool_t    kDoCocktailOnly         = kFALSE;
Bool_t    kDoVirtGamma            = kFALSE;
Bool_t    kDo200MeVCocktail       = kFALSE;
Bool_t    kDoNormMidRap           = kTRUE;
Bool_t    kDoPublished13TeVpythia = kTRUE;
Bool_t    kDoPublished13TeVpowheg = kFALSE;

Bool_t    kDoLFsum                = kFALSE;
Bool_t    kDoLFonly               = kFALSE;
Bool_t    kDoHFonly               = kFALSE;
Bool_t    kDoJPsi                 = kTRUE;
Bool_t    kDoSUMonly              = kFALSE;
Bool_t    kDoSUMnot               = kFALSE;
Bool_t    kDoScaleEtaSeperate     = kFALSE;
Bool_t    kDoReducedCocktail      = kTRUE;
Bool_t    kDoDrawOnlyFirstCock    = kTRUE;
Bool_t    kDoRapp                 = kFALSE; //reduce cocktail bins to projection
Bool_t    kDoAddRapp              = kFALSE;
Double_t  kRappScaling            = 7./(10.);//5 mee 10 ptee
Bool_t    kDoBrems                = kFALSE; //reduce cocktail bins to projection
Bool_t    kDoAddBrems             = kFALSE;
//Double_t  kBremsScaling           = 10./340000*0.4 * 2;
Double_t  kBremsScaling           = 1/(10. * 57.8);//3bins of cocktail * cross section
Bool_t    kDoMultiTheo            = kFALSE;
//Int_t     kCocktailVersion       = 3; //1: EtaSeperate 2:DONT 3:MultDep


//normalization values
Bool_t    kDoNormCrossSection    = kFALSE;
Bool_t    kDoNormCrossSectionCocktail = kFALSE;
Double_t  kCrossSectionLF        = 0.79; //+-2.9
Double_t  kCrossSection          = 57.8; //+-2.9
Bool_t    kDoNormTrgEff          = kFALSE;
//Double_t  kTriggerEfficiency     = 0.990;//+-0.01
Bool_t    kDoNormRecEff          = kFALSE;
Bool_t    kDoNormVtxRecEff       = kFALSE;
Double_t  kVtxRecEff             = 0.975;//0.977; //0.949
Bool_t    kDoNormVtxRecEffee     = kFALSE;
Double_t  kVtxRecEffee           = 1.0;

Double_t kLFscaling              = 1.;//0.5153; //0.79

//MB - 0-100
Int_t     kLowerCent             = 0;
Int_t     kUpperCent             = 100;
Double_t  kTriggerEfficiency     = 0.921*0.97;//+-0.01
Double_t  kDoResoScaling         = 1.; 
Double_t  kDoHFScaling           = 1.; 


Double_t  kDoKWScaling           = 1.;

Double_t  kSetMinPtLabel         = 0.2;
Double_t  kSetMaxPtLabel         = -1;

Double_t  kPlotLow               = 0.0; 
Double_t  kPlotHigh              = 0.0;
Bool_t    kDoSaveData            = kFALSE; 




struct SuperConfig{

  TString   DataConfig;
  //Double_t  mee_bins[];
  //Double_t  ptee_bins[];
  Int_t     BkgEstimator;//          = LmBackground::kHybrid;  //LmBackground::kHybrid, LmBackground::kArith, LmBackground::kGeom
  
  Int_t     LowerCent;//             = 0;
  Int_t     UpperCent;//             = 100;

  Double_t  CrossSection;//          = 57.8; //+-2.9
  Double_t  TriggerEfficiency;//     = 0.921*0.97;//+-0.01
  Double_t  VtxRecEff;//             = 0.975;//0.977; //0.949
  Double_t  VtxRecEffee;//           = 1.0;
  //Double_t  kDoEtaScaling          = 1.;

  TString   LFCocktail;
  TString   LFCocktailUpper;
  TString   LFCocktailLower;
  Double_t  DoResoScaling;//         = 1.; 
  TString   HFCocktail;
  TString   HFCocktailHistograms;
  Double_t  DoHFScaling;//           = 1.; 

  TString   JPsiCocktail;
  Int_t     CocktailVersion;//       = 3; //1: EtaSeperate 2:DONT 3:MultDep
};




//Example1
SuperConfig NewPreFilter_0_100_1617 = {
  cconfig[81], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 1.02*0.921*0.97*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};






Bool_t    kUseSuperConfig        = kFALSE;
Bool_t    kDoMassSlices          = kFALSE;  //kTRUE: do mass slices  kFALSE: do pair pt slices
Double_t  kDoEtaScaling          = 1.0;

SuperConfig sconfig[] = {NewPreFilter_0_100_1617};

Int_t n_sconfig = sizeof(sconfig)/sizeof(*sconfig);
