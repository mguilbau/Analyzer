#include "../interface/EPEtaDecoAnalyzerSP2.h"
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

EPEtaDecoAnalyzerSP2::EPEtaDecoAnalyzerSP2(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig)
{
  bkgFactor = 10;
}

EPEtaDecoAnalyzerSP2::~EPEtaDecoAnalyzerSP2() 
{}

void EPEtaDecoAnalyzerSP2::beginJob()
{
  hDeltaZvtx = theOutputs->make<TH1D>("deltazvtx",";#Delta z_{vtx}",200,-1.0,1.0);

  for(int itrg=0;itrg<MAXETATRGBINS2;itrg++)
  {
    hSignalCosnSame[itrg] = theOutputs->make<TH2D>(Form("signalcosnsame_trg%d",itrg),";cos(n#Delta#phi);n",10000,-0.5,0.5,3,1.5,4.5);
    hBackgroundCosnSame[itrg]= theOutputs->make<TH2D>(Form("backgroundcosnsame_trg%d",itrg),";cos(n#Delta#phi);n",10000,-0.5,0.5,3,1.5,4.5);
    hSignalCosnDiff[itrg] = theOutputs->make<TH2D>(Form("signalcosndiff_trg%d",itrg),";cos(n#Delta#phi);n",10000,-0.5,0.5,3,1.5,4.5);
    hBackgroundCosnDiff[itrg]= theOutputs->make<TH2D>(Form("backgroundcosndiff_trg%d",itrg),";cos(n#Delta#phi);n",10000,-0.5,0.5,3,1.5,4.5);
  }

  DiHadronCorrelationMultiBase::beginJob();
}

void EPEtaDecoAnalyzerSP2::endJob()
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
    FillHistsBackground(eventcorrArray[i],eventcorrArray[i]);

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

void EPEtaDecoAnalyzerSP2::NormalizeHists()
{
}

//--------------- Calculate signal distributions ----------------------
/*
void EPEtaDecoAnalyzerSP2::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
    unsigned int ntrgsize = eventcorr.pVect_trg[0].size();
    unsigned int nasssize = eventcorr.pVect_ass[0].size();
//    double nMultCorr_trg = eventcorr.nMultCorrVect_trg[0];
//    double nMultCorr_ass = eventcorr.nMultCorrVect_ass[0];

    double sumcosn_trg[MAXETATRGBINS2][5]={{0.0}};
    double sumsinn_trg[MAXETATRGBINS2][5]={{0.0}};
    double npairs_trg[MAXETATRGBINS2][5]={{0.0}};
    double sumcosn_ass[5]={0.0};
    double sumsinn_ass[5]={0.0};
    double npairs_ass[5]={0.0};

    for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
    {
      TLorentzVector pvector_trg = (eventcorr.pVect_trg[0])[ntrg];	  
      double effweight_trg = (eventcorr.effVect_trg[0])[ntrg];
      double eta_trg = pvector_trg.Eta()-cutPara.etacms;
      double phi_trg = pvector_trg.Phi();

      int ietabin = (int)((eta_trg+2.4)/ETATRGBINWIDTH2);
      if(cutPara.etaassmin<0 && cutPara.etaassmax<0) ietabin = (int)((2.4-eta_trg)/ETATRGBINWIDTH2);

      for(int nn = 1; nn<4; nn++)
      {
        sumcosn_trg[ietabin][nn] = sumcosn_trg[ietabin][nn] + cos((nn+1)*phi_trg)/effweight_trg;
        sumsinn_trg[ietabin][nn] = sumsinn_trg[ietabin][nn] + sin((nn+1)*phi_trg)/effweight_trg;
        npairs_trg[ietabin][nn] += 1.0/effweight_trg;
      }
   }

   for(unsigned int nass=0;nass<nasssize;nass++)
   {
     TLorentzVector pvector_ass = (eventcorr.pVect_ass[0])[nass];   
     double effweight_ass = (eventcorr.effVect_ass[0])[nass];
     double phi_ass = pvector_ass.Phi();

     for(int nn = 1; nn<4; nn++)
     {
       sumcosn_ass[nn] = sumcosn_ass[nn] + cos((nn+1)*phi_ass)/effweight_ass;
       sumsinn_ass[nn] = sumsinn_ass[nn] + sin((nn+1)*phi_ass)/effweight_ass;
       npairs_ass[nn] += 1.0/effweight_ass;
     }
   }
    
   for(int i=0;i<MAXETATRGBINS2;i++)
     for(int nn = 1; nn<4; nn++) 
      {
        if(npairs_trg[i][nn]==0.0 || npairs_ass[nn]==0.0) continue;
        double Qx = sumcosn_trg[i][nn]*sumcosn_ass[nn]+sumsinn_trg[i][nn]*sumsinn_ass[nn];
        double Qy = -sumcosn_trg[i][nn]*sumsinn_ass[nn]+sumsinn_trg[i][nn]*sumcosn_ass[nn];

        Qx = Qx/npairs_trg[i][nn]/npairs_ass[nn];
        Qy = Qy/npairs_trg[i][nn]/npairs_ass[nn];

        hSignalCosn[i]->Fill(Qx,nn+1);
//        hSignalSinn[i]->Fill(Qy,nn+1);

	double Qx2same = sumcosn_trg[i][nn]*sumcosn_trg[i][nn]+sumsinn_trg[i][nn]*sumsinn_trg[i][nn];
        double Qx2diff = sumcosn_trg[i][nn]*sumcosn_trg[MAXETATRGBINS2-1-i][nn]+sumsinn_trg[i][nn]*sumsinn_trg[MAXETATRGBINS2-1-i][nn];
        Qx2same = (Qx2same-npairs_trg[i][nn])/npairs_trg[i][nn]/(npairs_trg[i][nn]-1);
        Qx2diff = Qx2diff/npairs_trg[i][nn]/npairs_trg[MAXETATRGBINS2-1-i][nn];

        hSignalCosnSame[i]->Fill(Qx2same,nn+1);
        hSignalCosnDiff[i]->Fill(Qx2diff,nn+1);
      }
}
*/
void EPEtaDecoAnalyzerSP2::FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass)
{
    unsigned int ntrgsize = eventcorr_trg.pVect_trg[0].size();
    unsigned int nasssize = eventcorr_ass.pVect_trg[0].size();
//      double nMultCorr_trg = eventcorr_trg.nMultCorrVect_trg[0];
//      double nMultCorr_ass = eventcorr_ass.nMultCorrVect_ass[0];

    double sumcosn_trg[MAXETATRGBINS2][5]={{0.0}};
    double sumsinn_trg[MAXETATRGBINS2][5]={{0.0}};
    double npairs_trg[MAXETATRGBINS2][5]={{0.0}};
    double sumcosn_ass[MAXETATRGBINS2][5]={{0.0}};
    double sumsinn_ass[MAXETATRGBINS2][5]={{0.0}};
    double npairs_ass[MAXETATRGBINS2][5]={{0.0}};

    for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
    {
      TLorentzVector pvector_trg = (eventcorr_trg.pVect_trg[0])[ntrg];
      double effweight_trg = (eventcorr_trg.effVect_trg[0])[ntrg];
      double eta_trg = pvector_trg.Eta()-cutPara.etacms;
      double phi_trg = pvector_trg.Phi();

      int ietabin = (int)((eta_trg+2.4)/ETATRGBINWIDTH2);

      for(int nn = 1; nn<4; nn++)
      {
        sumcosn_trg[ietabin][nn] = sumcosn_trg[ietabin][nn] + cos((nn+1)*phi_trg)/effweight_trg;
        sumsinn_trg[ietabin][nn] = sumsinn_trg[ietabin][nn] + sin((nn+1)*phi_trg)/effweight_trg;
        npairs_trg[ietabin][nn] += 1.0/effweight_trg;
      }
   }

   for(unsigned int nass=0;nass<nasssize;nass++)
   {
      TLorentzVector pvector_ass = (eventcorr_ass.pVect_trg[0])[nass];
      double effweight_ass = (eventcorr_ass.effVect_trg[0])[nass];
      double eta_ass = pvector_ass.Eta()-cutPara.etacms;
      double phi_ass = pvector_ass.Phi();

      int ietabin = (int)((eta_ass+2.4)/ETATRGBINWIDTH2);

      for(int nn = 1; nn<4; nn++)
      {
        sumcosn_ass[ietabin][nn] = sumcosn_ass[ietabin][nn] + cos((nn+1)*phi_ass)/effweight_ass;
        sumsinn_ass[ietabin][nn] = sumsinn_ass[ietabin][nn] + sin((nn+1)*phi_ass)/effweight_ass;
        npairs_ass[ietabin][nn] += 1.0/effweight_ass;
      }
   }

   for(int i=0;i<MAXETATRGBINS2;i++)
     for(int nn = 1; nn<4; nn++)
     {
        if(npairs_trg[i][nn]==0.0 || npairs_ass[i][nn]==0.0) continue;

        double Qx2same = sumcosn_trg[i][nn]*sumcosn_ass[i][nn]+sumsinn_trg[i][nn]*sumsinn_ass[i][nn];
        double Qx2diff = sumcosn_trg[i][nn]*sumcosn_ass[MAXETATRGBINS2-1-i][nn]+sumsinn_trg[i][nn]*sumsinn_ass[MAXETATRGBINS2-1-i][nn];

        if(eventcorr_trg.run==eventcorr_ass.run && eventcorr_trg.event==eventcorr_ass.event) 
        {
          Qx2same = (Qx2same-npairs_trg[i][nn])/npairs_trg[i][nn]/(npairs_ass[i][nn]-1);
          Qx2diff = Qx2diff/npairs_trg[i][nn]/npairs_ass[MAXETATRGBINS2-1-i][nn];
          hSignalCosnSame[i]->Fill(Qx2same,nn+1);
          hSignalCosnDiff[i]->Fill(Qx2diff,nn+1);
        }
        else
        {
          Qx2same = Qx2same/npairs_trg[i][nn]/npairs_ass[i][nn];
          Qx2diff = Qx2diff/npairs_trg[i][nn]/npairs_ass[MAXETATRGBINS2-1-i][nn];
          hBackgroundCosnSame[i]->Fill(Qx2same,nn+1);
          hBackgroundCosnDiff[i]->Fill(Qx2diff,nn+1);
        }
     }
}
