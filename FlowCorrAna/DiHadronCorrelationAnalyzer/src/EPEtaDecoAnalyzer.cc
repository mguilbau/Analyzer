#include "../interface/EPEtaDecoAnalyzer.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TMath.h>
#include <TRandom.h>
#include <TTree.h>
#include <TFile.h>
#include <TList.h>
#include <TIterator.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TString.h>
#include <TVector3.h>
#include <vector> 
#include <iostream>
#include "Math/Vector3D.h"

using namespace std;

EPEtaDecoAnalyzer::EPEtaDecoAnalyzer(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig)
{
  bkgFactor = 10;
}

EPEtaDecoAnalyzer::~EPEtaDecoAnalyzer() 
{}

void EPEtaDecoAnalyzer::beginJob()
{
  hDeltaZvtx = theOutputs->make<TH1D>("deltazvtx",";#Delta z_{vtx}",200,-1.0,1.0);

  for(int itrg=0;itrg<MAXETATRGBINS;itrg++)
  {
//    hSignalCosn[itrg] = theOutputs->make<TH2D>(Form("signalcosn_trg%d",itrg),";cos(n#Delta#phi);n",30000,-0.3,0.3,3,1.5,4.5);
//    hBackgroundCosn[itrg]= theOutputs->make<TH2D>(Form("backgroundcosn_trg%d",itrg),";cos(n#Delta#phi);n",30000,-0.3,0.3,3,1.5,4.5);


    hSignalCosn[itrg] = theOutputs->make<TH2D>(Form("signalcosn_trg%d",itrg),";cos(n#Delta#phi);n",10000,-0.5,0.5,3,1.5,4.5);
    hBackgroundCosn[itrg]= theOutputs->make<TH2D>(Form("backgroundcosn_trg%d",itrg),";cos(n#Delta#phi);n",10000,-0.5,0.5,3,1.5,4.5);
    hSignalSinn[itrg] = theOutputs->make<TH2D>(Form("signalsinn_trg%d",itrg),";sin(n#Delta#phi);n",10000,-0.5,0.5,3,1.5,4.5);
    hBackgroundSinn[itrg]= theOutputs->make<TH2D>(Form("backgroundsinn_trg%d",itrg),";sin(n#Delta#phi);n",10000,-0.5,0.5,3,1.5,4.5);
  }
/*
  for(int i=1;i<4;i++)
  {
    hSignalSinnPvsN[i] = theOutputs->make<TH2D>(Form("signalsin%dpvsn",i+1),Form(";sin(%d#Delta#phi)_{P};sin(%d#Delta#phi)_{N}",i+1,i+1),500,-0.3,0.3,500,-0.3,0.3);
    hBackgroundSinnPvsN[i] = theOutputs->make<TH2D>(Form("backgroundsin%dpvsn",i+1),Form(";sin(%d#Delta#phi)_{P};sin(%d#Delta#phi)_{N}",i+1,i+1),500,-0.3,0.3,500,-0.3,0.3);
  }
*/
  DiHadronCorrelationMultiBase::beginJob();
}

void EPEtaDecoAnalyzer::endJob()
{
  DiHadronCorrelationMultiBase::endJob();
  
  if(!cutPara.IsCorr) return;

  cout<< "Start sorting the events!" << endl;
  std::sort(eventcorrArray.begin(),eventcorrArray.end());
  cout<< "Finish sorting the events!" << endl;

  cout<< "Start running correlation analysis!" << endl;

//  for(unsigned int i=0;i<eventcorrArray.size();i++) cout<< "zvtx=" << eventcorrArray[i].zvtx <<" nmult="<<eventcorrArray[i].nmult<<" cent="<<eventcorrArray[i].centbin<<endl;

  for(unsigned int i=0;i<eventcorrArray.size();i++)
  {
    if( i % 100 == 0 ) cout << "Processing " << i << "th event" << endl;
    FillHistsSignal(eventcorrArray[i]);

    unsigned int mixstart = i+1;
    unsigned int mixend = i+1+bkgFactor;

    if(mixend>eventcorrArray.size()) mixend=eventcorrArray.size();
    for(unsigned int j=mixstart;j<mixend;j++)
    {
//      if(eventcorrArray[i].centbin != eventcorrArray[j].centbin) break;
//      if(eventcorrArray[i].centbin != eventcorrArray[j].centbin) continue;

      double deltazvtx = eventcorrArray[i].zvtx-eventcorrArray[j].zvtx;
      hDeltaZvtx->Fill(deltazvtx);

//      if(fabs(deltazvtx)>0.06) continue;

      FillHistsBackground(eventcorrArray[i],eventcorrArray[j]);
    }
  }
  cout<< "Finish running correlation analysis!" << endl;

  NormalizeHists();
  cout<< "Finish normalizing the histograms!" << endl;
}

void EPEtaDecoAnalyzer::NormalizeHists()
{
}

//--------------- Calculate signal distributions ----------------------
void EPEtaDecoAnalyzer::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
    unsigned int ntrgsize = eventcorr.pVect_trg[0].size();
    unsigned int nasssize = eventcorr.pVect_ass[0].size();
//    double nMultCorr_trg = eventcorr.nMultCorrVect_trg[0];
//    double nMultCorr_ass = eventcorr.nMultCorrVect_ass[0];

    double sumcosn[MAXETATRGBINS][5]={{0.0}};
    double sumsinn[MAXETATRGBINS][5]={{0.0}};
    double npairs[MAXETATRGBINS][5]={{0.0}};

    for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
    {
      TLorentzVector pvector_trg = (eventcorr.pVect_trg[0])[ntrg];	  
      double effweight_trg = (eventcorr.effVect_trg[0])[ntrg];
//      double chg_trg = (eventcorr.chgVect_trg[0])[ntrg];
      double eta_trg = pvector_trg.Eta()-cutPara.etacms;
//      double phi_trg = pvector_trg.Phi();
//      double pt_trg = pvector_trg.Pt();

      for(unsigned int nass=0;nass<nasssize;nass++)
      {
        TLorentzVector pvector_ass = (eventcorr.pVect_ass[0])[nass];   
        double effweight_ass = (eventcorr.effVect_ass[0])[nass];
//        double chg_ass = (eventcorr.chgVect_ass[0])[nass];
//        double eta_ass = pvector_ass.Eta()-cutPara.etacms;
//        double phi_ass = pvector_ass.Phi();
//        double pt_ass = pvector_ass.Pt();

        // check charge sign
//        if( (checksign == 0) && (chg_trg != chg_ass)) continue;
//        if( (checksign == 1) && (chg_trg == chg_ass)) continue;

        double deltaPhi= pvector_trg.DeltaPhi(pvector_ass);
//        double deltaPhi=GetDeltaPhi(phi_trg,phi_ass);
//        double deltaEta=GetDeltaEta(eta_trg,eta_ass);

//        if(deltaEta==0.0 && deltaPhi==0.0 && pt_trg==pt_ass) continue; // two particles are identical

        // total weight
        double effweight = effweight_trg * effweight_ass;

        int ietabin = (int)((eta_trg+2.4)/ETATRGBINWIDTH);
        if(cutPara.etaassmin<0 && cutPara.etaassmax<0) ietabin = (int)((2.4-eta_trg)/ETATRGBINWIDTH);

        for(int nn = 1; nn<4; nn++)
        {
          sumcosn[ietabin][nn] = sumcosn[ietabin][nn] + cos((nn+1)*deltaPhi)/effweight;
          sumsinn[ietabin][nn] = sumsinn[ietabin][nn] + sin((nn+1)*deltaPhi)/effweight;
          npairs[ietabin][nn] += 1.0/effweight;
        }
//        delete pvector_ass;
      }
//      delete pvector_trg;
    }
    for(int i=0;i<MAXETATRGBINS;i++)
      for(int nn = 1; nn<4; nn++) 
      {
        if(npairs[i][nn]==0.0) continue;
        sumcosn[i][nn]=sumcosn[i][nn]/npairs[i][nn];
        sumsinn[i][nn]=sumsinn[i][nn]/npairs[i][nn];
        hSignalCosn[i]->Fill(sumcosn[i][nn],nn+1);
        hSignalSinn[i]->Fill(sumsinn[i][nn],nn+1);
      }
/*
//    for(int i=0;i<MAXETATRGBINS/2;i++)
      for(int nn = 1; nn<4; nn++)
      {
        if(sumcosn[0][nn]!=0 && sumsinn[MAXETATRGBINS-1][nn]!=0) hSignalSinnPvsN[nn]->Fill(sumsinn[0][nn],sumsinn[MAXETATRGBINS-1][nn]);
      }
*/
}

void EPEtaDecoAnalyzer::FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass)
{
      unsigned int ntrgsize = eventcorr_trg.pVect_trg[0].size();
      unsigned int nasssize = eventcorr_ass.pVect_ass[0].size();
//      double nMultCorr_trg = eventcorr_trg.nMultCorrVect_trg[0];
//      double nMultCorr_ass = eventcorr_ass.nMultCorrVect_ass[0];

      double sumcosn[MAXETATRGBINS][5]={{0.0}};
      double sumsinn[MAXETATRGBINS][5]={{0.0}};
      double npairs[MAXETATRGBINS][5]={{0.0}};

      for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
      {
        TLorentzVector pvector_trg = (eventcorr_trg.pVect_trg[0])[ntrg];	  
        double effweight_trg = (eventcorr_trg.effVect_trg[0])[ntrg];
//        double chg_trg = (eventcorr_trg.chgVect_trg[0])[ntrg];
        double eta_trg = pvector_trg.Eta()-cutPara.etacms;
//        double phi_trg = pvector_trg.Phi();
//        double pt_trg = pvector_trg.Pt();

        for(unsigned int nass=0;nass<nasssize;nass++)
        {
          TLorentzVector pvector_ass = (eventcorr_ass.pVect_ass[0])[nass];   
          double effweight_ass = (eventcorr_ass.effVect_ass[0])[nass];
//          double chg_ass = (eventcorr_ass.chgVect_ass[0])[nass];
//          double eta_ass = pvector_ass.Eta()-cutPara.etacms;
//          double phi_ass = pvector_ass.Phi();
//          double pt_ass = pvector_ass.Pt();

          // check charge sign
//          if( (checksign == 0) && (chg_trg != chg_ass)) continue;
//          if( (checksign == 1) && (chg_trg == chg_ass)) continue;

          double deltaPhi= pvector_trg.DeltaPhi(pvector_ass);
//          double deltaPhi=GetDeltaPhi(phi_trg,phi_ass);
//          double deltaEta=GetDeltaEta(eta_trg,eta_ass);

          // total weight
          double effweight = effweight_trg * effweight_ass;

          int ietabin = (int)((eta_trg+2.4)/ETATRGBINWIDTH);
          if(cutPara.etaassmin<0 && cutPara.etaassmax<0) ietabin = (int)((2.4-eta_trg)/ETATRGBINWIDTH);

          for(int nn = 1; nn<4; nn++)
          {
            sumcosn[ietabin][nn] = sumcosn[ietabin][nn] + cos((nn+1)*deltaPhi)/effweight;
            sumsinn[ietabin][nn] = sumsinn[ietabin][nn] + sin((nn+1)*deltaPhi)/effweight;
            npairs[ietabin][nn] += 1.0/effweight;
          }
//          delete pvector_ass;
      }
//      delete pvector_trg;
   }
   for(int i=0;i<MAXETATRGBINS;i++)
     for(int nn = 1; nn<4; nn++)
     {
       if(!npairs[i][nn]) continue;
       sumcosn[i][nn]=sumcosn[i][nn]/npairs[i][nn];
       sumsinn[i][nn]=sumsinn[i][nn]/npairs[i][nn];
       hBackgroundCosn[i]->Fill(sumcosn[i][nn],nn+1);
       hBackgroundSinn[i]->Fill(sumsinn[i][nn],nn+1);
     }
/*
//   for(int i=0;i<MAXETATRGBINS/2;i++)
     for(int nn = 1; nn<4; nn++)
     {
       if(sumcosn[0][nn]!=0 && sumsinn[MAXETATRGBINS-1][nn]!=0) hBackgroundSinnPvsN[nn]->Fill(sumsinn[0][nn],sumsinn[MAXETATRGBINS-1][nn]);
     }
*/
}
