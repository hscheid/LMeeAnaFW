#ifndef LMBASEMANAGER_H
#define LMBASEMANAGER_H

// c++ includes
// ROOT includes
// project includes
// forward declarations
class TH2D;

class LmBaseManager {
public:
  LmBaseManager();
  LmBaseManager(const LmBaseManager& man);
  
  // function declarations
  void          PrintTH2(TH2D* hIn, const Char_t* filename);
  // setters
  void          SetName(const std::string name) { fName = name; }
  void          SetInputfiles(const char* files); // not yet used by normal manager... only by cocktail manager.
  void          SetInputlists(const char* lists); ///< List in rootfile that contains histograms. Can be given as "list/sublist", when using LmHelper::GetList().
  void          SetInputhistAndDim(const char* histnames, UInt_t dim);
  void          SetPlotRangeZ(Double_t min, Double_t max) { fPlotZMin=min; fPlotZMax=max; }
  void          ResetPlotRangeZ() { fPlotZMin=-1.; fPlotZMax=-1.; }
  // getters
  const char*   GetName()       const { return fName.c_str(); }
  UInt_t        GetNdimInput()  const { return fNdimInput; }
  
protected:
  // functions
  virtual void  InitProjectionRanges() {};
  
  // variables
  std::string           fName;
  TString               fsInputfiles;
  TString               fsInputlists;
  TString               fsInputhists;
  UInt_t                fNdimInput;
  Double_t              fPlotZMin;
  Double_t              fPlotZMax;
};

#endif
