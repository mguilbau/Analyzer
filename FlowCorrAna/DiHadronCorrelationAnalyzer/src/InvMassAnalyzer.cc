#include "../interface/InvMassAnalyzer.h"
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

InvMassAnalyzer::InvMassAnalyzer(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig)
{
  bkgFactor = 5;
}

InvMassAnalyzer::~InvMassAnalyzer() 
{}

void InvMassAnalyzer::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{
  hDeltaZvtx = theOutputs->make<TH1D>("deltazvtx",";#Delta z_{vtx}",200,-1.0,-1.0);

//  hInvMassVsPt_Signal = theOutputs->make<TH2D>("invmassvspt_signal",";p_{T}(GeV);Invariant Mass (GeV)",500,0,50,1500,0,3);
  hInvMassVsPt_Background = theOutputs->make<TH2D>("invmassvspt_background",";p_{T}(GeV);Invariant Mass (GeV)",500,0,50,1500,0,3);

  DiHadronCorrelationMultiBase::beginRun(iRun, iSetup);
}

void InvMassAnalyzer::endRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{
  DiHadronCorrelationMultiBase::endRun(iRun, iSetup);
  
  if(!cutPara.IsCorr) return;

  cout<< "Start sorting the events!" << endl;
  std::sort(eventcorrArray.begin(),eventcorrArray.end());
  cout<< "Finish sorting the events!" << endl;

  cout<< "Start running correlation analysis!" << endl;

  for(unsigned int i=0;i<eventcorrArray.size();i++)
  {
    if( i % 100 == 0 ) cout << "Processing " << i << "th event" << endl;
//    FillHistsSignal(eventcorrArray[i]);

    unsigned int mixstart = i+1;
    unsigned int mixend = i+1+bkgFactor;

    if(mixend>eventcorrArray.size()) mixend=eventcorrArray.size();
    for(unsigned int j=mixstart;j<mixend;j++)
    {
      if(eventcorrArray[i].centbin != eventcorrArray[j].centbin) break;
//      if(eventcorrArray[i].centbin != eventcorrArray[j].centbin) continue;

      double deltazvtx = eventcorrArray[i].zvtx-eventcorrArray[j].zvtx;
      hDeltaZvtx->Fill(deltazvtx);

      FillHistsBackground(eventcorrArray[i],eventcorrArray[j]);
    }
  }
  cout<< "Finish running correlation analysis!" << endl;

  NormalizeHists();
  cout<< "Finish normalizing the histograms!" << endl;
}

void InvMassAnalyzer::NormalizeHists()
{
}

//--------------- Calculate signal distributions ----------------------
void InvMassAnalyzer::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
  unsigned int ntrgsize = eventcorr.pVect_trg[0].size();
  unsigned int nasssize = eventcorr.pVect_ass[0].size();
        
  for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
  {
    TLorentzVector pvector_trg = (eventcorr.pVect_trg[0])[ntrg];
    double chg_trg = (eventcorr.chgVect_trg[0])[ntrg];
      
    for(unsigned int nass=0;nass<nasssize;nass++)
    {
      TLorentzVector pvector_ass = (eventcorr.pVect_ass[0])[nass];
      double chg_ass = (eventcorr.chgVect_ass[0])[nass];

      // check charge sign
      if( (checksign == 0) && (chg_trg != chg_ass)) continue;
      if( (checksign == 1) && (chg_trg == chg_ass)) continue;

      TLorentzVector pvector_total = pvector_ass + pvector_trg;
      double massInv = pvector_total.M();
      hInvMassVsPt_Signal->Fill(pvector_total.Pt(),massInv-pvector_trg.M());
    }
  }
}

void InvMassAnalyzer::FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass)
{
  unsigned int ntrgsize = eventcorr_trg.pVect_trg[0].size();
  unsigned int nasssize = eventcorr_ass.pVect_ass[0].size();
         
  for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
  {
    TLorentzVector pvector_trg = (eventcorr_trg.pVect_trg[0])[ntrg];
    double chg_trg = (eventcorr_trg.chgVect_trg[0])[ntrg];
      
    for(unsigned int nass=0;nass<nasssize;nass++)
    {
      TLorentzVector pvector_ass = (eventcorr_ass.pVect_ass[0])[nass];
      double chg_ass = (eventcorr_ass.chgVect_ass[0])[nass];

      // check charge sign
      if( (checksign == 0) && (chg_trg != chg_ass)) continue;
      if( (checksign == 1) && (chg_trg == chg_ass)) continue;

      TLorentzVector pvector_total = pvector_ass + pvector_trg;
      double massInv = pvector_total.M();
      hInvMassVsPt_Background->Fill(pvector_total.Pt(),massInv-pvector_trg.M());
    }
  }
}
