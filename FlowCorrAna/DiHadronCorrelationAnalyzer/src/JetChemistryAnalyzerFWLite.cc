#include "../interface/JetChemistryAnalyzerFWLite.h"
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

JetChemistryAnalyzerFWLite::JetChemistryAnalyzerFWLite(fwlite::ChainEvent& Event) :
  DiHadronCorrelationMultiBaseFWLite(Event)
{}

JetChemistryAnalyzerFWLite::~JetChemistryAnalyzerFWLite() 
{}

void JetChemistryAnalyzerFWLite::Process()
{
  DiHadronCorrelationMultiBaseFWLite::Process();

//  cout<< "Start sorting the events!" << endl;
//  std::sort(eventcorrArray.begin(),eventcorrArray.end());
//  cout<< "Finish sorting the events!" << endl;

  cout<< "Start running jet chemistry analysis!" << endl;
  for(unsigned int i=0;i<eventcorrArray.size();i++)
  {
    if( i % 100 == 0 ) cout << "Processing " << i << "th event" << endl;
    FillHistsSignal(eventcorrArray[i]);
  }
  cout<< "Finish running jet chemistry analysis!" << endl;

//  NormalizeHists();
//  cout<< "Finish normalizing the histograms!" << endl;  

}

void JetChemistryAnalyzerFWLite::MakeHists()
{
  hJetPt = new TH1D("jetpt",";p_{T}",1000,0,1000);
  for(int i=0;i<(int)(cutPara.pttrgmin.size());i++)
  {
      h2D[i] = new TH2D(Form("corr_%d",i),";#Delta#eta;#Delta#phi",100,-5,5,100,-PI,PI);
      hFragPt[i] = new TH1D(Form("fragPt_%d",i),";p_{T}",
                                     1000,0,100);
      hFragPt[i]->Sumw2();
      hJetPt_trg[i] = new TH1D(Form("jetpt_%d",i),";p_{T}",
                                     1000,0,1000);
      hJetPt_trg[i]->Sumw2();
  }

  DiHadronCorrelationMultiBaseFWLite::MakeHists();
}

void JetChemistryAnalyzerFWLite::NormalizeHists()
{}

void JetChemistryAnalyzerFWLite::DeleteHists()
{
  DiHadronCorrelationMultiBaseFWLite::DeleteHists();	

  delete hJetPt;
  for(int i=0;i<(int)(cutPara.pttrgmin.size());i++)
  {
      delete h2D[i];
      delete hFragPt[i];
      delete hJetPt_trg[i];
  }
}

//--------------- Calculate signal distributions ----------------------
void JetChemistryAnalyzerFWLite::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
   for(unsigned int i=0;i<cutPara.pttrgmin.size();i++)
   {
     unsigned int ntrgsize = eventcorr.pVect_trg[i].size();
     unsigned int nasssize = eventcorr.pVect_ass[0].size();

     for(unsigned int n=0;n<ntrgsize;n++)
     {
       TLorentzVector pvector_trg = (eventcorr.pVect_trg[i])[n];	  
//       double effweight_trg = (eventcorr.effVect_trg[i])[n];
//       double chg_trg = (eventcorr.chgVect_trg[i])[n];
       double eta_trg = pvector_trg.Eta();
       double phi_trg = pvector_trg.Phi();
       double pt_trg = pvector_trg.Pt();
       hJetPt->Fill(pt_trg);
       hJetPt_trg[i]->Fill(pt_trg);
       for(unsigned int m=0;m<nasssize;m++)
       {
         TLorentzVector pvector_ass = (eventcorr.pVect_ass[0])[m];
//         double effweight_ass = (eventcorr.effVect_ass[0])[m];
//         double chg_ass = (eventcorr.chgVect_ass[0])[m];
         double eta_ass = pvector_ass.Eta();
         double phi_ass = pvector_ass.Phi();
         double pt_ass = pvector_ass.Pt();    

         double deltaPhi=GetDeltaPhi(phi_trg,phi_ass);
         double deltaEta=GetDeltaEta(eta_trg,eta_ass);
         double r = sqrt(deltaPhi*deltaPhi+deltaEta*deltaEta);
         h2D[i]->Fill(deltaEta,deltaPhi);
         if(r<0.3) hFragPt[i]->Fill(pt_ass);
       }
     }
   }
}

TList* JetChemistryAnalyzerFWLite::GetOutputs()
{
  TList* outputlist = (TList*)DiHadronCorrelationMultiBaseFWLite::GetOutputs();

  for(int i=0;i<(int)(cutPara.pttrgmin.size());i++)
  {
        outputlist->Add(h2D[i]);
        outputlist->Add(hFragPt[i]);
        outputlist->Add(hJetPt_trg[i]);
        outputlist->Add(hJetPt);
  }

  return outputlist;
}
