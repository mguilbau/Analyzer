#ifndef EPEtaDecoAnalyzerFWLite_
#define EPEtaDecoAnalyzerFWLite_

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

#define MAXETATRGBINS 12
#define ETATRGBINWIDTH 0.4

class EPEtaDecoAnalyzerFWLite : public DiHadronCorrelationMultiBaseFWLite {
   
 protected:

   // histograms
   TH2D* hSignalCosn[MAXETATRGBINS];
   TH2D* hBackgroundCosn[MAXETATRGBINS];

   // parameters
   int    bkgFactor;

   virtual void Process(); 
   virtual void MakeHists();
   virtual void NormalizeHists();
   virtual void DeleteHists();
   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   virtual TList* GetOutputs();
   
 public:
   EPEtaDecoAnalyzerFWLite(fwlite::ChainEvent&);
   virtual ~EPEtaDecoAnalyzerFWLite();

   void SetBkgFactor(int bkgfactor) {bkgFactor = bkgfactor;}
};
#endif  // EPEtaDecoAnalyzerFWLite_
