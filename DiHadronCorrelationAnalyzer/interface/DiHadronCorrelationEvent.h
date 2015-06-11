#ifndef DiHadronCorrelationEvent_
#define DiHadronCorrelationEvent_

#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>

using namespace std;

#define MAXPTTRGBINS 20 
#define MAXPTASSBINS 20

#define MAXETATRGBINSPT 48
#define ETATRGBINWIDTHPT 0.1

class DiHadronCorrelationEvent {                                                                                  

 public:                                                                                           
   //  vectors for tracks, hits etc
//   vector<TLorentzVector>  pVect_all;
   vector<TLorentzVector>  pVect_trg[MAXPTTRGBINS];
   vector<float>    nMultCorrVect_trg;
   vector<float>    chgVect_trg[MAXPTTRGBINS];
   vector<float>    effVect_trg[MAXPTTRGBINS];
//   double            multcorrVect_trg[MAXPTTRGBINS];
   vector<TLorentzVector>  pVect_ass[MAXPTASSBINS];
   vector<float>    nMultCorrVect_ass;
   vector<float>    chgVect_ass[MAXPTASSBINS];
   vector<float>    effVect_ass[MAXPTASSBINS];
//   double            multcorrVect_ass[MAXPTASSBINS];
   int               run;
//   int               lumi;
   int               event;
//   int               nmult;
//   int               centbin;
   float            zvtx;
//   float            epangle;

   bool operator<(const DiHadronCorrelationEvent & b) const{
     if (zvtx != b.zvtx) return zvtx < b.zvtx;
//     else if (centbin != b.centbin) return centbin < b.centbin;
//     else if (nmult != b.nmult) return nmult < b.nmult;
     else return false;
   }

   DiHadronCorrelationEvent(){}
   ~DiHadronCorrelationEvent(){}
};

#endif  // DiHadronCorrelationEvent_
