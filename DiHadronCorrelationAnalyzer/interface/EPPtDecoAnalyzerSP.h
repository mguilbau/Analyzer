#ifndef EPPtDecoAnalyzerSP_
#define EPPtDecoAnalyzerSP_

#ifndef DiHadronCorrelationMultiBase_
#include "DiHadronCorrelationMultiBase.h"
#endif 

#include <vector>
#include <string>

class TH1D;
class TH2D;
class TH3D;
class TTree;
class TList;

class EPPtDecoAnalyzerSP : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TH2D* hSignalCosn[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hBackgroundCosn[MAXPTTRGBINS][MAXPTASSBINS];

   // parameters
   int    bkgFactor;

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
//   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   
 public:
   EPPtDecoAnalyzerSP(const edm::ParameterSet&);
   ~EPPtDecoAnalyzerSP();

};
#endif  // EPPtDecoAnalyzerSP_
