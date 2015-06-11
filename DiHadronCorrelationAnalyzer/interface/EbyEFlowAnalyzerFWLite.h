#ifndef EbyEFlowAnalyzerFWLite_
#define EbyEFlowAnalyzerFWLite_

#ifndef DiHadronCorrelationMultiBaseFWLite_
#include "DiHadronCorrelationMultiBaseFWLite.h"
#endif 

#include <vector>
#include <string>

class TH1D;
class TH2D;
class TH3D;
class TTree;
class TList;

class EbyEFlowAnalyzerFWLite : public DiHadronCorrelationMultiBaseFWLite {
   
 protected:

   // histograms
   TH2D* hSignalCosSin2_trg[MAXPTTRGBINS];
   TH2D* hSignalCosSin3_trg[MAXPTTRGBINS];
   TH2D* hSignalCosSin4_trg[MAXPTTRGBINS];
   TH2D* hSignalCosSin5_trg[MAXPTTRGBINS];
   TH2D* hSignalCosSin2_ass[MAXPTTRGBINS];
   TH2D* hSignalCosSin3_ass[MAXPTTRGBINS];
   TH2D* hSignalCosSin4_ass[MAXPTTRGBINS];
   TH2D* hSignalCosSin5_ass[MAXPTTRGBINS];
   TH2D* hSignalSinnPM[MAXPTTRGBINS];
   TH2D* hSignalCosnPM[MAXPTTRGBINS]; 
   TH2D* hSignalRhon_trg[MAXPTTRGBINS];
   TH2D* hSignalEPAnglen_trg[MAXPTTRGBINS];
   TH2D* hSignalRhon_ass[MAXPTTRGBINS];
   TH2D* hSignalEPAnglen_ass[MAXPTTRGBINS];
   TH2D* hSignalRhon_all[MAXPTTRGBINS]; 
   TH2D* hSignalEPAnglen_all[MAXPTTRGBINS];

   virtual void Process(); 
   virtual void MakeHists();
//   virtual void NormalizeHists();
   virtual void DeleteHists();
   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual TList* GetOutputs();
   
 public:
   EbyEFlowAnalyzerFWLite(fwlite::ChainEvent&);
   virtual ~EbyEFlowAnalyzerFWLite();
};
#endif  // EbyEFlowAnalyzerFWLite_
