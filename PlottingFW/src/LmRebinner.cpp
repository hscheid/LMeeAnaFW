// c++ includes

// ROOT includes
#include "TH2.h"
#include "TMath.h"
// project includes
#include "LmRebinner.h"
#include "LmHelper.h"


//_______________________________________________________________________________________________
LmRebinner::LmRebinner() :
fEnableRebinning(kFALSE)
{
  /// Default constructor for LmRebinner
}

//_______________________________________________________________________________________________
LmRebinner::LmRebinner(const LmRebinner& reb) :
fEnableRebinning(reb.fEnableRebinning)
{
  /// Copy constructor for LmRebinner

  if (fEnableRebinning) {
    SetRebinning2D(reb.fBinsRebin_Mee.size()-1, reb.fBinsRebin_Mee.data(), reb.fBinsRebin_Ptee.size()-1, reb.fBinsRebin_Ptee.data());
  }
}

//_______________________________________________________________________________________________
void LmRebinner::SetRebinning2D(Int_t n_bins_mee, const Double_t* bins_mee, Int_t n_bins_ptee, const Double_t* bins_ptee)
{
  SetRebinningX(n_bins_mee, bins_mee, 1);
  SetRebinningY(n_bins_ptee, bins_ptee, 1);
  SetEnableRebinning();
}

//_______________________________________________________________________________________________
void LmRebinner::SetRebinningX(Int_t n_bins, const Double_t* bins, Int_t n_rebin)
{
  fBinsRebin_Mee.clear(); // to be able to overwrite
  for (int i=0; i<n_bins+1; i+=n_rebin) { fBinsRebin_Mee.push_back(bins[i]); }
  SetEnableRebinning();
}

//_______________________________________________________________________________________________
void LmRebinner::SetRebinningY(Int_t n_bins, const Double_t* bins, Int_t n_rebin)
{
  fBinsRebin_Ptee.clear(); // to be able to overwrite
  for (int i=0; i<n_bins+1; i+=n_rebin) { fBinsRebin_Ptee.push_back(bins[i]); }
  SetEnableRebinning();
}


//_______________________________________________________________________________________________
void LmRebinner::Rebin2DHistogramSimpleError(TH2D& hIn){
  /// Used only in the PairEffCalc_V2
  /// Simple error calculation
  TH2D* hOut = new TH2D("hOut", hIn.GetTitle(), fBinsRebin_Mee.size()-1, fBinsRebin_Mee.data(), fBinsRebin_Ptee.size()-1, fBinsRebin_Ptee.data());

  hOut->GetXaxis()->SetTitle(hIn.GetXaxis()->GetTitle());
  hOut->GetYaxis()->SetTitle(hIn.GetYaxis()->GetTitle());
  hOut->GetZaxis()->SetTitle(hIn.GetZaxis()->GetTitle());
  Double_t bin_content_hIn    =  0;
  Double_t bin_center_mee     = -1;
  Double_t bin_center_ptee    = -1;

  for (Int_t i_mee = 1; i_mee <= hIn.GetNbinsX(); ++i_mee){
    for (Int_t j_ptee = 1; j_ptee <= hIn.GetNbinsY(); ++j_ptee){
      bin_content_hIn = hIn.GetBinContent(i_mee, j_ptee);

      bin_center_mee  = hIn.GetXaxis()->GetBinCenter(i_mee);
      bin_center_ptee = hIn.GetYaxis()->GetBinCenter(j_ptee);

      // set hOut content
      hOut->Fill(bin_center_mee, bin_center_ptee, bin_content_hIn);
    }
  }


  // Setting the bin error manually to avoid conflicts between root5 and root6
  // Old version, based on the assumption of raw unsubtracted yield.
  for (Int_t i_mee = 1; i_mee <= hOut->GetNbinsX(); ++i_mee){ //Overflow?
   for (Int_t j_ptee = 1; j_ptee <= hOut->GetNbinsY(); ++j_ptee){
     Double_t bin_content = hOut->GetBinContent(i_mee, j_ptee);
     hOut->SetBinError(i_mee, j_ptee, TMath::Sqrt(bin_content));
   }
  }
  hOut->Sumw2(); // also done by SetBinError();

  TString sname(hIn.GetName());
  hIn = *hOut;

  hIn.SetName(sname.Data());

  delete hOut;
  return;
}

//_______________________________________________________________________________________________
void LmRebinner::Rebin2DHistogram(TH2D& hIn)
{
  /// Rebin a 2D histogram based on two bin vectors with variable binning.
  /// If one of the binning vectors in this class is not sufficiently filled (<2 entries), there are 2 options:
  /// (1) if the vector has size 1 and the stored number is an integer and an exact divisor of the original number
  ///     of bins, this number is taken as rebin factor.
  /// (2) if (1) is not fulfilled, the original binning of the respective axis is kept.
  ///

  LmHelper::Debug("  LmRebinner::Rebin2DHistogram()", 10);

  TString sname(hIn.GetName());  // Otherwise potential memory leak

  if (fBinsRebin_Mee.size()<2) {
    Int_t n_bins_temp = hIn.GetNbinsX();
    Double_t bins_temp[n_bins_temp+1];
    //    cout << " sizeof(bins_temp)/sizeof(*bins_temp) = " << sizeof(bins_temp)/sizeof(*bins_temp) << endl;
    //    cout << " hIn.GetXaxis()->GetBinLowEdge(n_bins_temp)   = " << hIn.GetXaxis()->GetBinLowEdge(n_bins_temp) << endl;
    //    cout << " hIn.GetXaxis()->GetBinLowEdge(n_bins_temp+1) = " << hIn.GetXaxis()->GetBinLowEdge(n_bins_temp+1) << endl;
    hIn.GetXaxis()->GetLowEdge(bins_temp); // Fills the binning of the original histogram into the array. // problems to fill the last bin! - why!?!
    //    cout << " bins_temp[1] = " << bins_temp[1] << " bins_temp[99] = " << bins_temp[99] << " bins_temp[100] = " << bins_temp[100] << endl;
    bins_temp[n_bins_temp] = hIn.GetXaxis()->GetBinLowEdge(n_bins_temp+1); // fill last bin edge manually...
    //    cout << " bins_temp[1] = " << bins_temp[1] << " bins_temp[99] = " << bins_temp[99] << " bins_temp[100] = " << bins_temp[100] << endl;
    Int_t n_rebin=1;
    if (   fBinsRebin_Mee.size()==1 && fBinsRebin_Mee[0]!=0.
        && fBinsRebin_Mee[0]==Int_t(fBinsRebin_Mee[0])
        && n_bins_temp%Int_t(fBinsRebin_Mee[0])==0 ) {
      n_rebin = fBinsRebin_Mee[0];
      LmHelper::Info(Form("LmRebinner: rebin X axis by factor %i.", n_rebin));
    }
    else LmHelper::Error(Form("LmRebinner: rebinning X axis with factor %f failed", fBinsRebin_Mee[0]));
    SetRebinningX(n_bins_temp, bins_temp, n_rebin);
  }
  if (fBinsRebin_Ptee.size()<2) {
    Int_t n_bins_temp = hIn.GetNbinsY();
    Double_t bins_temp[n_bins_temp+1];
    hIn.GetYaxis()->GetLowEdge(bins_temp); // Fills the binning of the original histogram into the array. // problems to fill the last bin! - why!?!
    bins_temp[n_bins_temp] = hIn.GetYaxis()->GetBinLowEdge(n_bins_temp+1); // fill last bin edge manually...
    Int_t n_rebin=1;
    if (   fBinsRebin_Ptee.size()==1 && fBinsRebin_Ptee[0]!=0.
        && fBinsRebin_Ptee[0]==Int_t(fBinsRebin_Ptee[0])
        && n_bins_temp%Int_t(fBinsRebin_Ptee[0])==0 ) {
      n_rebin = fBinsRebin_Ptee[0];
      LmHelper::Info(Form("LmRebinner: rebin Y axis by factor %i.", n_rebin));
    }
    else LmHelper::Error(Form("LmRebinner: rebinning Y axis with factor %f failed", fBinsRebin_Ptee[0]));
    SetRebinningY(n_bins_temp, bins_temp, n_rebin);
  }

  TH2D hOut("hOut", hIn.GetTitle(), fBinsRebin_Mee.size()-1, fBinsRebin_Mee.data(), fBinsRebin_Ptee.size()-1, fBinsRebin_Ptee.data());
  hOut.Sumw2();

  hOut.GetXaxis()->SetTitle(hIn.GetXaxis()->GetTitle());
  hOut.GetYaxis()->SetTitle(hIn.GetYaxis()->GetTitle());
  hOut.GetZaxis()->SetTitle(hIn.GetZaxis()->GetTitle());
  Double_t bin_content_hIn     =  0;
  Double_t bin_error_hIn       =  0;
  Double_t bin_center_mee_hIn  = -1;
  Double_t bin_center_ptee_hIn = -1;

  Double_t bin_content_hOut    = -1;
  Double_t bin_error_hOut_2    = -1;
  Int_t    bin_mee_hOut        = -1;
  Int_t    bin_ptee_hOut       = -1;

  // The error in this loop is quadratically added. This means that after this loop you have to sqrt the error bin-by-bin
  // to get the real uncertainty
  for (Int_t i_mee = 0; i_mee <= hIn.GetNbinsX()+1; ++i_mee){
    for (Int_t j_ptee = 0; j_ptee <= hIn.GetNbinsY()+1; ++j_ptee){
      bin_content_hIn = hIn.GetBinContent(i_mee, j_ptee); // input bin content
      bin_error_hIn   = hIn.GetBinError(i_mee, j_ptee);   // input bin error

      bin_center_mee_hIn  = hIn.GetXaxis()->GetBinCenter(i_mee);
      bin_center_ptee_hIn = hIn.GetYaxis()->GetBinCenter(j_ptee);

      bin_mee_hOut    = hOut.GetXaxis()->FindBin(bin_center_mee_hIn);
      bin_ptee_hOut   = hOut.GetYaxis()->FindBin(bin_center_ptee_hIn);

      bin_content_hOut = hOut.GetBinContent(bin_mee_hOut, bin_ptee_hOut);
      bin_error_hOut_2 = hOut.GetBinError(bin_mee_hOut, bin_ptee_hOut);

      // set hOut content
      hOut.SetBinContent(bin_mee_hOut, bin_ptee_hOut, bin_content_hOut + bin_content_hIn);
      hOut.SetBinError(bin_mee_hOut, bin_ptee_hOut, bin_error_hOut_2 + bin_error_hIn * bin_error_hIn);
    }
  }

  // sqrt of errors bin-by-bin
  for (Int_t i_mee = 0; i_mee <= hOut.GetNbinsX()+1; ++i_mee){
    for (Int_t j_ptee = 0; j_ptee <= hOut.GetNbinsY()+1; ++j_ptee){
      hOut.SetBinError(i_mee, j_ptee, TMath::Sqrt(hOut.GetBinError(i_mee, j_ptee)));
    }
  }

  hIn = hOut;
  hIn.SetName(sname.Data());

  return;
}
