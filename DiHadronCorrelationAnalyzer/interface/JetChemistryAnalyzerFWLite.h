#ifndef JetChemistryAnalyzerFWLite_
#define JetChemistryAnalyzerFWLite_

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

class JetChemistryAnalyzerFWLite : public DiHadronCorrelationMultiBaseFWLite {
   
 protected:

   // histograms
   TH2D* h2D[MAXPTTRGBINS];
   TH1D* hJetPt;
   TH1D* hFragPt[MAXPTTRGBINS];
   TH1D* hJetPt_trg[MAXPTTRGBINS];

   // parameters

   virtual void Process(); 
   virtual void MakeHists();
   virtual void NormalizeHists();
   virtual void DeleteHists();
   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual TList* GetOutputs();
   
 public:
   JetChemistryAnalyzerFWLite(fwlite::ChainEvent&);
   virtual ~JetChemistryAnalyzerFWLite();

};
#endif  // JetChemistryAnalyzerFWLite_
