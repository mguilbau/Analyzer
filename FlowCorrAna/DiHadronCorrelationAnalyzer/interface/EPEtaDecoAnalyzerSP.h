#ifndef EPEtaDecoAnalyzerSP_
#define EPEtaDecoAnalyzerSP_

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

#define MAXETATRGBINS 16
#define ETATRGBINWIDTH 0.3

class EPEtaDecoAnalyzerSP : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TH2D* hSignalCosn[MAXETATRGBINS];
   TH2D* hBackgroundCosn[MAXETATRGBINS];
   TH2D* hSignalSinn[MAXETATRGBINS];
   TH2D* hBackgroundSinn[MAXETATRGBINS];
   TH2D* hSignalSinnPvsN[5];
   TH2D* hBackgroundSinnPvsN[5];

   // parameters
   int    bkgFactor;

   virtual void beginRun(const edm::Run&, const edm::EventSetup&);
   virtual void endRun(const edm::Run&, const edm::EventSetup&);

   virtual void NormalizeHists();
   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   
 public:
   EPEtaDecoAnalyzerSP(const edm::ParameterSet&);
   ~EPEtaDecoAnalyzerSP();

};
#endif  // EPEtaDecoAnalyzerSP_
