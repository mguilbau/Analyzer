#ifndef ChargeDepCorrAnalyzerSP3_
#define ChargeDepCorrAnalyzerSP3_

#ifndef DiHadronCorrelationMultiBase_
#include "DiHadronCorrelationMultiBase.h"
#endif 

#include <vector>
#include <string>

#ifndef MAXZVTXBINS_
#define MAXZVTXBINS 30
#endif

class TH1D;
class TH2D;
class TH3D;
class TTree;
class TList;

class ChargeDepCorrAnalyzerSP3 : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH2D* hdNdEtadPhiPos;
   TH2D* hdNdEtadPhiNeg;

   TH2D* hSignalCos_same_for;
   TH2D* hSignalCos_diff_for;
   TH2D* hSignalCos_same_bak;
   TH2D* hSignalCos_diff_bak;
   TH2D* hSignalCos2PcorrP_same;
   TH2D* hSignalCos2PcorrP_diff;
   TH2D* hSignalCos2PcorrM_same;
   TH2D* hSignalCos2PcorrM_diff;
   TH2D* hSignalNpairs_same;
   TH2D* hSignalNpairs_diff;

   TH2D* hSumNCosTrgPos[MAXZVTXBINS];
   TH2D* hSumNCosTrgNeg[MAXZVTXBINS];
   TH2D* hSumNSinTrgPos[MAXZVTXBINS];
   TH2D* hSumNSinTrgNeg[MAXZVTXBINS];
   TH2D* hSumNCos2TrgPos[MAXZVTXBINS];
   TH2D* hSumNCos2TrgNeg[MAXZVTXBINS];
   TH2D* hSumNSin2TrgPos[MAXZVTXBINS];
   TH2D* hSumNSin2TrgNeg[MAXZVTXBINS];
   TH2D* hSumCosTrgPos[MAXZVTXBINS][MAXETATRGBINSPT];
   TH2D* hSumSinTrgPos[MAXZVTXBINS][MAXETATRGBINSPT];
   TH2D* hSumCosTrgNeg[MAXZVTXBINS][MAXETATRGBINSPT];
   TH2D* hSumSinTrgNeg[MAXZVTXBINS][MAXETATRGBINSPT];
   TH2D* hSumCos2TrgPos[MAXZVTXBINS][MAXETATRGBINSPT];
   TH2D* hSumSin2TrgPos[MAXZVTXBINS][MAXETATRGBINSPT];
   TH2D* hSumCos2TrgNeg[MAXZVTXBINS][MAXETATRGBINSPT];
   TH2D* hSumSin2TrgNeg[MAXZVTXBINS][MAXETATRGBINSPT];
   TH1D* hQ2AssCos;
   TH1D* hSumAssFor[MAXZVTXBINS];
   TH1D* hSumAssBak[MAXZVTXBINS];
   TH1D* hSumCosAssFor[MAXZVTXBINS];
   TH1D* hSumSinAssFor[MAXZVTXBINS];
   TH1D* hSumCosAssBak[MAXZVTXBINS];
   TH1D* hSumSinAssBak[MAXZVTXBINS];
   TH1D* hSumCos2AssFor[MAXZVTXBINS];
   TH1D* hSumSin2AssFor[MAXZVTXBINS];
   TH1D* hSumCos2AssBak[MAXZVTXBINS];
   TH1D* hSumSin2AssBak[MAXZVTXBINS];

   double sumcosn_ass_for;
   double sumsinn_ass_for;
   double sumcos2n_ass_for;
   double sumsin2n_ass_for;
   double npairs_ass_for;
   double sumcosn_ass_bak;
   double sumsinn_ass_bak;
   double sumcos2n_ass_bak;
   double sumsin2n_ass_bak;
   double npairs_ass_bak;
   double sumcosn_trg_pos[MAXETATRGBINSPT];
   double sumsinn_trg_pos[MAXETATRGBINSPT];
   double sumcos2n_trg_pos[MAXETATRGBINSPT];
   double sumsin2n_trg_pos[MAXETATRGBINSPT];
   double npairs_trg_pos[MAXETATRGBINSPT];
   double sumcosn_trg_neg[MAXETATRGBINSPT];
   double sumsinn_trg_neg[MAXETATRGBINSPT];
   double sumcos2n_trg_neg[MAXETATRGBINSPT];
   double sumsin2n_trg_neg[MAXETATRGBINSPT];
   double npairs_trg_neg[MAXETATRGBINSPT];

   std::vector<double> multBins;

   TString* recenter_filename;
   TString* recenter_dirname;
   TFile* frecenter;

   // parameters
   virtual void beginJob();
   virtual void endJob();

   virtual void FillHistsQVectorTrk(const DiHadronCorrelationEvent& eventcorr, int zvtxbin);
   virtual void FillHistsQVectorHF(const DiHadronCorrelationEvent& eventcorr, int zvtxbin);
   virtual void FillHistsCorrelators();
   virtual void Recenter(int zvtxbin);

 public:
   ChargeDepCorrAnalyzerSP3(const edm::ParameterSet&);
   ~ChargeDepCorrAnalyzerSP3();

};
#endif  // ChargeDepCorrAnalyzerSP3_
