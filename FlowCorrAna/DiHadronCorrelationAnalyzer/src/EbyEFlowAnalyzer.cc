#include "../interface/EbyEFlowAnalyzer.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TMath.h>
#include <TRandom.h>
#include <TTree.h>
#include <TNtuple.h>
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

EbyEFlowAnalyzer::EbyEFlowAnalyzer(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig)
{
}

EbyEFlowAnalyzer::~EbyEFlowAnalyzer() 
{}

void EbyEFlowAnalyzer::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{
  hDeltaZvtx = theOutputs->make<TH1D>("deltazvtx",";#Delta z_{vtx}",200,-1.0,1.0);

  hQ2XY = theOutputs->make<TH2D>("q2xy",";q_{2,x};q_{2,y}",2000,-1.0,1.0,2000,-1.0,1.0);
  hQ2XPvsN = theOutputs->make<TH2D>("q2xpvsn",";q_{2,x}^{+};q_{2,x}^{-}",2000,-1.0,1.0,2000,-1.0,1.0);
  hQ2YPvsN = theOutputs->make<TH2D>("q2ypvsn",";q_{2,y}^{+};q_{2,y}^{-}",2000,-1.0,1.0,2000,-1.0,1.0);
  hQ2XDiff = theOutputs->make<TH1D>("q2xdiff",";q_{2,x}^{+}-q_{2,x}^{-}",2000,-1.0,1.0);
  hQ2YDiff = theOutputs->make<TH1D>("q2ydiff",";q_{2,y}^{+}-q_{2,y}^{-}",2000,-1.0,1.0);
  hQ2XYDiff = theOutputs->make<TH2D>("q2xydiff",";q_{2,x}^{+}-q_{2,x}^{-};q_{2,y}^{+}-q_{2,y}^{-}",2000,-1.0,1.0,2000,-1.0,1.0);
/*
  hQ2HFPVsHFM = theOutputs->make<TH2D>("q2hfpvshfm",";q_{2}^{HF+};q_{2}^{HF-}",1000,0.,0.5,1000,0.,0.5);
  hQ2HFPVsMid = theOutputs->make<TH2D>("q2hfpvsmid",";q_{2}^{HF+};q_{2}^{Mid}",1000,0.,0.5,1000,0.,0.5);
  hQ2HFMVsMid = theOutputs->make<TH2D>("q2hfmvsmid",";q_{2}^{HF-};q_{2}^{Mid}",1000,0.,0.5,1000,0.,0.5);
  
  q2Ntuple = theOutputs->make<TNtuple>("q2ntuple","","run:lumi:evtnum:cent:q2hf:q2hfp:q2hfm:q2mid:hf");
*/
  DiHadronCorrelationMultiBase::beginRun(iRun, iSetup);
}

void EbyEFlowAnalyzer::endRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{
  DiHadronCorrelationMultiBase::endRun(iRun, iSetup);
  
  if(!cutPara.IsCorr) return;

  cout<< "Start running correlation analysis!" << endl;

  for(unsigned int i=0;i<eventcorrArray.size();i++)
  {
    if( i % 100 == 0 ) cout << "Processing " << i << "th event" << endl;
    FillHistsSignal(eventcorrArray[i]);
  }
  cout<< "Finish running correlation analysis!" << endl;

  NormalizeHists();
  cout<< "Finish normalizing the histograms!" << endl;
}

void EbyEFlowAnalyzer::NormalizeHists()
{
}

//--------------- Calculate signal distributions ----------------------
void EbyEFlowAnalyzer::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
  unsigned int ntrgsize = eventcorr.pVect_trg[0].size();
/*
  double q2x_hf=0; double q2y_hf=0; double wsum_hf=0;
  double q2x_hfp=0; double q2y_hfp=0; double wsum_hfp=0;
  double q2x_hfm=0; double q2y_hfm=0; double wsum_hfm=0;
  double q2x_mid=0; double q2y_mid=0; double wsum_mid=0;
*/
  double q2x_p=0; double q2y_p=0; double wsum_p=0;
  double q2x_n=0; double q2y_n=0; double wsum_n=0;
  double q2x=0; double q2y=0; double wsum=0;

  for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
  {
    TLorentzVector pvector_trg = (eventcorr.pVect_trg[0])[ntrg];	  
    double effweight_trg = (eventcorr.effVect_trg[0])[ntrg];
    double chg_trg = (eventcorr.chgVect_trg[0])[ntrg];
    double eta_trg = pvector_trg.Eta();
    double phi_trg = pvector_trg.Phi();
//    double pt_trg = pvector_trg.Pt();

    if(fabs(eta_trg)<2.4)
    {
      if(chg_trg>0)
      {
        q2x_p = q2x_p + (1.0/effweight_trg)*cos(2*phi_trg);
        q2y_p = q2y_p + (1.0/effweight_trg)*sin(2*phi_trg);
        wsum_p = wsum_p + 1.0/effweight_trg;
      }
      if(chg_trg<0) 
      { 
        q2x_n = q2x_n + (1.0/effweight_trg)*cos(2*phi_trg);
        q2y_n = q2y_n + (1.0/effweight_trg)*sin(2*phi_trg);
        wsum_n = wsum_n + 1.0/effweight_trg;
      }
      q2x=q2x_p+q2x_n;
      q2y=q2y_p+q2y_n;
      wsum = wsum_p + wsum_n;
    }
/*
    if(fabs(eta_trg)>3)
    {
      q2x_hf = q2x_hf + (1.0/effweight_trg)*cos(2*phi_trg);
      q2y_hf = q2y_hf + (1.0/effweight_trg)*sin(2*phi_trg);
      wsum_hf = wsum_hf + 1.0/effweight_trg;
    }
    if(eta_trg<5 && eta_trg>3)
    {
      q2x_hfp = q2x_hfp + (1.0/effweight_trg)*cos(2*phi_trg);
      q2y_hfp = q2y_hfp + (1.0/effweight_trg)*sin(2*phi_trg);
      wsum_hfp = wsum_hfp + 1.0/effweight_trg;
    }
    if(eta_trg<-3 && eta_trg>-5)
    {
      q2x_hfm = q2x_hfm + (1.0/effweight_trg)*cos(2*phi_trg);
      q2y_hfm = q2y_hfm + (1.0/effweight_trg)*sin(2*phi_trg);
      wsum_hfm = wsum_hfm + 1.0/effweight_trg;
    }
    if(eta_trg<1 && eta_trg>-1)
    {
      q2x_mid = q2x_mid + (1.0/effweight_trg)*cos(2*phi_trg);
      q2y_mid = q2y_mid + (1.0/effweight_trg)*sin(2*phi_trg);
      wsum_mid = wsum_mid + 1.0/effweight_trg;
    }
*/
  }
/*
  q2x_hf = q2x_hf / wsum_hf;
  q2y_hf = q2y_hf / wsum_hf;
  q2x_hfp = q2x_hfp / wsum_hfp;
  q2y_hfp = q2y_hfp / wsum_hfp;
  q2x_hfm = q2x_hfm / wsum_hfm;
  q2y_hfm = q2y_hfm / wsum_hfm;
  q2x_mid = q2x_mid / wsum_mid;
  q2y_mid = q2y_mid / wsum_mid;
*/
  q2x_p = q2x_p / wsum_p;
  q2y_p = q2y_p / wsum_p;
  q2x_n = q2x_n / wsum_n;
  q2y_n = q2y_n / wsum_n;
  q2x = q2x / wsum;
  q2y = q2y / wsum;
  hQ2XPvsN->Fill(q2x_p,q2x_n);
  hQ2YPvsN->Fill(q2y_p,q2y_n);
  hQ2XDiff->Fill((q2x_p-q2x_n)/2.);
  hQ2YDiff->Fill((q2y_p-q2y_n)/2.);
  hQ2XYDiff->Fill((q2x_p-q2x_n)/2.,(q2y_p-q2y_n)/2.);
  hQ2XY->Fill(q2x,q2y);
/*
  double q2_hf = sqrt(q2x_hf*q2x_hf+q2y_hf*q2y_hf);
  double q2_hfp = sqrt(q2x_hfp*q2x_hfp+q2y_hfp*q2y_hfp);
  double q2_hfm = sqrt(q2x_hfm*q2x_hfm+q2y_hfm*q2y_hfm);
  double q2_mid = sqrt(q2x_mid*q2x_mid+q2y_mid*q2y_mid);

  q2Ntuple->Fill(eventcorr.run,eventcorr.lumi,eventcorr.event,eventcorr.centbin,q2_hf,q2_hfp,q2_hfm,q2_mid,wsum_hf);

  hQ2HFPVsHFM->Fill(q2_hfp,q2_hfm);
  hQ2HFPVsMid->Fill(q2_hfp,q2_mid);
  hQ2HFMVsMid->Fill(q2_hfm,q2_mid);
*/
}
