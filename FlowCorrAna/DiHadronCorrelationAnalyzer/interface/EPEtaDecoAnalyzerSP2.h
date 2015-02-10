#ifndef EPEtaDecoAnalyzerSP2_
#define EPEtaDecoAnalyzerSP2_

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

#define MAXETATRGBINS2 6
#define ETATRGBINWIDTH2 0.8

class EPEtaDecoAnalyzerSP2 : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TH2D* hSignalCosnSame[MAXETATRGBINS2];
   TH2D* hBackgroundCosnSame[MAXETATRGBINS2];
   TH2D* hSignalCosnDiff[MAXETATRGBINS2];
   TH2D* hBackgroundCosnDiff[MAXETATRGBINS2];

   // parameters
   int    bkgFactor;

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
//   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   
 public:
   EPEtaDecoAnalyzerSP2(const edm::ParameterSet&);
   ~EPEtaDecoAnalyzerSP2();

};
#endif  // EPEtaDecoAnalyzerSP2_
