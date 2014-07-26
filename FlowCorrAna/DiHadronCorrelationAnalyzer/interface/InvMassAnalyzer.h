#ifndef InvMassAnalyzer_
#define InvMassAnalyzer_

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

class InvMassAnalyzer : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
//   TH2D* hInvMassVsPt_Signal;
   TH2D* hInvMassVsPt_Background;
   TH1D* hDeltaZvtx;

   // parameters
   int    bkgFactor;

   virtual void beginRun(const edm::Run&, const edm::EventSetup&);
   virtual void endRun(const edm::Run&, const edm::EventSetup&);

   virtual void NormalizeHists();
   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   
 public:
   InvMassAnalyzer(const edm::ParameterSet&);
   ~InvMassAnalyzer();

};
#endif  // InvMassAnalyzer_
