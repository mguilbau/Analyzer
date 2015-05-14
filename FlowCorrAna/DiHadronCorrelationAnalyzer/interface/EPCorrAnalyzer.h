#ifndef EPCorrAnalyzer_
#define EPCorrAnalyzer_

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
class TNtuple;

class EPCorrAnalyzer : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hCorrelator23;
   TH1D* hCorrelator24;
   TH1D* hV2denom6;
   TH1D* hV3denom4;
   TH1D* hV2denom4;
   TH1D* hV4denom2;

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   
 public:
   EPCorrAnalyzer(const edm::ParameterSet&);
   ~EPCorrAnalyzer();

};
#endif  // EPCorrAnalyzer_
