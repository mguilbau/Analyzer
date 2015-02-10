#ifndef ChargeDepCorrAnalyzerSP2_
#define ChargeDepCorrAnalyzerSP2_

#ifndef DiHadronCorrelationMultiBase_
#include "DiHadronCorrelationMultiBase.h"
#endif 

#include <vector>
#include <string>

#ifndef MAXZVTXBINS_
#define MAXZVTXBINS 30
#endif

class TH1F;
class TH2F;
class TH3F;
class TTree;
class TList;

class ChargeDepCorrAnalyzerSP2 : public DiHadronCorrelationMultiBase {
   
 protected:

   // histograms
   TH2F* hdNdEtadPhiPos;
   TH2F* hdNdEtadPhiNeg;

   TH2F* hSumNpairs_pp;
   TH2F* hSumNpairs_nn;
   TH2F* hSumNpairs_pn;
   TH2F* hSumNpairs_np;
   TH1F* hSumNpairs_hf;
   TH1F* hSignalCos_pp_for[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH1F* hSignalCos_pn_for[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH1F* hSignalCos_pp_bak[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH1F* hSignalCos_pn_bak[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH1F* hSignalCos2PcorrP_pp[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH1F* hSignalCos2PcorrP_pn[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH1F* hSignalCos2PcorrM_pp[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH1F* hSignalCos2PcorrM_pn[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH2F* hSumCos_pp_for;
   TH2F* hSumCos_pn_for;
   TH2F* hSumCos_pp_bak;
   TH2F* hSumCos_pn_bak;
   TH2F* hSumCos2PcorrP_pp;
   TH2F* hSumCos2PcorrP_pn;
   TH2F* hSumCos2PcorrM_pp;
   TH2F* hSumCos2PcorrM_pn;

   TH1F* hSignalCos_nn_for[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH1F* hSignalCos_np_for[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH1F* hSignalCos_nn_bak[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH1F* hSignalCos_np_bak[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH1F* hSignalCos2PcorrP_nn[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH1F* hSignalCos2PcorrP_np[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH1F* hSignalCos2PcorrM_nn[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH1F* hSignalCos2PcorrM_np[MAXETATRGBINSPT][MAXETATRGBINSPT];
   TH2F* hSumCos_nn_for;
   TH2F* hSumCos_np_for;
   TH2F* hSumCos_nn_bak;
   TH2F* hSumCos_np_bak;
   TH2F* hSumCos2PcorrP_nn;
   TH2F* hSumCos2PcorrP_np;
   TH2F* hSumCos2PcorrM_nn;
   TH2F* hSumCos2PcorrM_np;

//   TH2F* hSignalNpairs_same;
//   TH2F* hSignalNpairs_diff;
   TH2F* hSumNCosTrgPos[MAXZVTXBINS];
   TH2F* hSumNCosTrgNeg[MAXZVTXBINS];
   TH2F* hSumNSinTrgPos[MAXZVTXBINS];
   TH2F* hSumNSinTrgNeg[MAXZVTXBINS];
   TH2F* hSumNCos2TrgPos[MAXZVTXBINS];
   TH2F* hSumNCos2TrgNeg[MAXZVTXBINS];
   TH2F* hSumNSin2TrgPos[MAXZVTXBINS];
   TH2F* hSumNSin2TrgNeg[MAXZVTXBINS];
   TH2F* hSumCosTrgPos[MAXZVTXBINS][MAXETATRGBINSPT];
   TH2F* hSumSinTrgPos[MAXZVTXBINS][MAXETATRGBINSPT];
   TH2F* hSumCosTrgNeg[MAXZVTXBINS][MAXETATRGBINSPT];
   TH2F* hSumSinTrgNeg[MAXZVTXBINS][MAXETATRGBINSPT];
   TH2F* hSumCos2TrgPos[MAXZVTXBINS][MAXETATRGBINSPT];
   TH2F* hSumSin2TrgPos[MAXZVTXBINS][MAXETATRGBINSPT];
   TH2F* hSumCos2TrgNeg[MAXZVTXBINS][MAXETATRGBINSPT];
   TH2F* hSumSin2TrgNeg[MAXZVTXBINS][MAXETATRGBINSPT];
   TH1F* hQ2AssCos;
   TH1F* hSumAssFor[MAXZVTXBINS];
   TH1F* hSumAssBak[MAXZVTXBINS];
   TH1F* hSumCosAssFor[MAXZVTXBINS];
   TH1F* hSumSinAssFor[MAXZVTXBINS];
   TH1F* hSumCosAssBak[MAXZVTXBINS];
   TH1F* hSumSinAssBak[MAXZVTXBINS];
   TH1F* hSumCos2AssFor[MAXZVTXBINS];
   TH1F* hSumSin2AssFor[MAXZVTXBINS];
   TH1F* hSumCos2AssBak[MAXZVTXBINS];
   TH1F* hSumSin2AssBak[MAXZVTXBINS];

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

   double npairs_pp_total[MAXETATRGBINSPT][MAXETATRGBINSPT];
   double nevt_pp_total[MAXETATRGBINSPT][MAXETATRGBINSPT];
   double npairs_nn_total[MAXETATRGBINSPT][MAXETATRGBINSPT];
   double nevt_nn_total[MAXETATRGBINSPT][MAXETATRGBINSPT];
   double npairs_pn_total[MAXETATRGBINSPT][MAXETATRGBINSPT];
   double nevt_pn_total[MAXETATRGBINSPT][MAXETATRGBINSPT];
   double npairs_np_total[MAXETATRGBINSPT][MAXETATRGBINSPT];
   double nevt_np_total[MAXETATRGBINSPT][MAXETATRGBINSPT];

/*
   std::vector<double> sumcosn_trg_pos_vect;
   std::vector<double> sumsinn_trg_pos_vect;
   std::vector<double> sumcos2n_trg_pos_vect;
   std::vector<double> sumsin2n_trg_pos_vect;
   std::vector<double> npairs_trg_pos_vect;
   std::vector<double> sumcosn_trg_neg_vect;
   std::vector<double> sumsinn_trg_neg_vect;
   std::vector<double> sumcos2n_trg_neg_vect;
   std::vector<double> sumsin2n_trg_neg_vect;
   std::vector<double> npairs_trg_neg_vect;
*/
/*
   std::vector< std::vector<double> > sumcosn_trg_pos_vect;
   std::vector< std::vector<double> > sumsinn_trg_pos_vect;
   std::vector< std::vector<double> > sumcos2n_trg_pos_vect;
   std::vector< std::vector<double> > sumsin2n_trg_pos_vect;
   std::vector< std::vector<double> > npairs_trg_pos_vect;
   std::vector< std::vector<double> > sumcosn_trg_neg_vect;
   std::vector< std::vector<double> > sumsinn_trg_neg_vect;
   std::vector< std::vector<double> > sumcos2n_trg_neg_vect;
   std::vector< std::vector<double> > sumsin2n_trg_neg_vect;
   std::vector< std::vector<double> > npairs_trg_neg_vect;
*/
   std::vector<double> multBins;

   TString* recenter_filename;
   TString* recenter_dirname;
   TFile* frecenter;

   // parameters
   virtual void beginJob();
   virtual void endJob();

   virtual void FillHistsQVectorTrk(const DiHadronCorrelationEvent& eventcorr, int zvtxbin);
   virtual void FillHistsQVectorHF(const DiHadronCorrelationEvent& eventcorr, int zvtxbin);
   virtual void FillHistsCorrelators(int ietabin, int jetabin);
   virtual void Recenter(int zvtxbin);
   virtual int  GetNMultBin(int nmult);

 public:
   ChargeDepCorrAnalyzerSP2(const edm::ParameterSet&);
   ~ChargeDepCorrAnalyzerSP2();

};
#endif  // ChargeDepCorrAnalyzerSP2_
