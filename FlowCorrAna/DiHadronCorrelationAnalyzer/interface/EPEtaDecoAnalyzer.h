#ifndef EPEtaDecoAnalyzer_
#define EPEtaDecoAnalyzer_

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

#define MAXETATRGBINS 24
#define ETATRGBINWIDTH 0.2

class EPEtaDecoAnalyzer : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;
   TH2D* hSignalCosn[MAXETATRGBINS];
   TH2D* hBackgroundCosn[MAXETATRGBINS];
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
   EPEtaDecoAnalyzer(const edm::ParameterSet&);
   ~EPEtaDecoAnalyzer();

};
#endif  // EPEtaDecoAnalyzer_
