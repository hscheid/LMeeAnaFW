#ifndef LMREBINNER_H
#define LMREBINNER_H

// c++ includes
#include <vector>
// ROOT includes
// project includes
// forward declarations
class TH2D;

class LmRebinner {
public:
  LmRebinner();
  LmRebinner(const LmRebinner& reb);

  // function declarations
  void          Rebin2DHistogram(TH2D& hIn); ///< mee: X-axis, ptee: Y-axis
  void          Rebin2DHistogramSimpleError(TH2D& hIn); ///< mee: X-axis, ptee: Y-axis
  // setters
  void          SetRebinning2D(Int_t n_bins_mee, const Double_t* bins_mee, Int_t n_bins_ptee, const Double_t* bins_ptee); ///< mee: X-axis, ptee: Y-axis
  void          SetRebinningX(Int_t n_bins, const Double_t* bins, Int_t n_rebin=1);
  void          SetRebinningY(Int_t n_bins, const Double_t* bins, Int_t n_rebin=1);
  void          SetEnableRebinning(bool SEVB=kTRUE) { fEnableRebinning = SEVB; }
  // getters
  Bool_t        GetEnableRebinning() const { return fEnableRebinning; }
  std::vector<Double_t> GetBinningX() { return fBinsRebin_Mee;} // mee: X-axis
  std::vector<Double_t> GetBinningY() { return fBinsRebin_Ptee;} // ptee: Y-axis
 

protected:
  // functions

  // switches
  Bool_t        fEnableRebinning;

  // variables
  std::vector<Double_t> fBinsRebin_Mee; // mee: X-axis
  std::vector<Double_t> fBinsRebin_Ptee; // ptee: Y-axis
};

#endif
