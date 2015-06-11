#ifndef EbyEFlowAnalyzer_
#define EbyEFlowAnalyzer_

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

class EbyEFlowAnalyzer : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH1D* hDeltaZvtx;

   TH2D* hQ2XPvsN;
   TH2D* hQ2YPvsN;
   TH1D* hQ2XDiff;
   TH1D* hQ2YDiff;
   TH2D* hQ2XYDiff;
   TH2D* hQ2XY;
/*
   TH2D* hQ2HFPVsHFM;
   TH2D* hQ2HFPVsMid;
   TH2D* hQ2HFMVsMid;
   TNtuple* q2Ntuple;
*/

   virtual void beginJob();
   virtual void endJob();

   virtual void NormalizeHists();
   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   
 public:
   EbyEFlowAnalyzer(const edm::ParameterSet&);
   ~EbyEFlowAnalyzer();

};
#endif  // EbyEFlowAnalyzer_
