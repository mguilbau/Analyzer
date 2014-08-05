#include "../interface/EbyEFlowAnalyzerFWLite.h"
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

EbyEFlowAnalyzerFWLite::EbyEFlowAnalyzerFWLite(fwlite::ChainEvent& Event) :
  DiHadronCorrelationMultiBaseFWLite(Event)
{}

EbyEFlowAnalyzerFWLite::~EbyEFlowAnalyzerFWLite() 
{}

void EbyEFlowAnalyzerFWLite::Process()
{
  DiHadronCorrelationMultiBaseFWLite::Process();

  if(!cutPara.IsCorr) return;

  cout<< "Start sorting the events!" << endl;
  std::sort(eventcorrArray.begin(),eventcorrArray.end());
  cout<< "Finish sorting the events!" << endl;

  cout<< "Start running ebye vn analysis!" << endl;
  for(unsigned int i=0;i<eventcorrArray.size();i++)
  {
    if( i % 100 == 0 ) cout << "Processing " << i << "th event" << endl;
    FillHistsSignal(eventcorrArray[i]);
  }
  cout<< "Finish running ebye vn analysis!" << endl;
}

void EbyEFlowAnalyzerFWLite::MakeHists()
{
  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    hSignalCosSin2_trg[itrg] = new TH2D(Form("signalcossin2_trg%d",itrg),";cos(2#phi);sin(2#phi)",2000,-1.0,1.0,2000,-1.0,1.0);
    hSignalCosSin3_trg[itrg] = new TH2D(Form("signalcossin3_trg%d",itrg),";cos(3#phi);sin(3#phi)",2000,-1.0,1.0,2000,-1.0,1.0);
    hSignalCosSin4_trg[itrg] = new TH2D(Form("signalcossin4_trg%d",itrg),";cos(4#phi);sin(4#phi)",2000,-1.0,1.0,2000,-1.0,1.0);
    hSignalCosSin5_trg[itrg] = new TH2D(Form("signalcossin5_trg%d",itrg),";cos(5#phi);sin(5#phi)",2000,-1.0,1.0,2000,-1.0,1.0);

    hSignalCosSin2_ass[itrg] = new TH2D(Form("signalcossin2_ass%d",itrg),";cos(2#phi);sin(2#phi)",2000,-1.0,1.0,2000,-1.0,1.0);
    hSignalCosSin3_ass[itrg] = new TH2D(Form("signalcossin3_ass%d",itrg),";cos(3#phi);sin(3#phi)",2000,-1.0,1.0,2000,-1.0,1.0);
    hSignalCosSin4_ass[itrg] = new TH2D(Form("signalcossin4_ass%d",itrg),";cos(4#phi);sin(4#phi)",2000,-1.0,1.0,2000,-1.0,1.0);
    hSignalCosSin5_ass[itrg] = new TH2D(Form("signalcossin5_ass%d",itrg),";cos(5#phi);sin(5#phi)",2000,-1.0,1.0,2000,-1.0,1.0);

    hSignalCosnPM[itrg] = new TH2D(Form("signalcosnpm_trg%d",itrg),";cos(n#phi)+-cos(n#phi)-;n",2000,-1.0,1.0,5,0.5,5.5);
    hSignalSinnPM[itrg] = new TH2D(Form("signalsinnpm_trg%d",itrg),";sin(n#phi)+-sin(n#phi)-;n",2000,-1.0,1.0,5,0.5,5.5);
    
    hSignalRhon_trg[itrg] = new TH2D(Form("signalrhon_trg%d",itrg),";#rho;n",5000,-1.0,1.0,5,0.5,5.5);
    hSignalEPAnglen_trg[itrg] = new TH2D(Form("signalepanglen_trg%d",itrg),";#Psi_n;n",100,-PI,PI,5,0.5,5.5);
    hSignalRhon_ass[itrg] = new TH2D(Form("signalrhon_ass%d",itrg),";#rho;n",5000,-1.0,1.0,5,0.5,5.5);
    hSignalEPAnglen_ass[itrg] = new TH2D(Form("signalepanglen_ass%d",itrg),";#Psi_n;n",100,-PI,PI,5,0.5,5.5);
    hSignalRhon_all[itrg] = new TH2D(Form("signalrhon_all%d",itrg),";#rho;n",2000,0.0,2.0,5,0.5,5.5);
    hSignalEPAnglen_all[itrg] = new TH2D(Form("signalepanglen_all%d",itrg),";#Psi_n;n",100,-PI,PI,5,0.5,5.5);
  }

  DiHadronCorrelationMultiBaseFWLite::MakeHists();
}

void EbyEFlowAnalyzerFWLite::DeleteHists()
{
  DiHadronCorrelationMultiBaseFWLite::DeleteHists();	

  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    delete hSignalCosSin2_trg[itrg];
    delete hSignalCosSin3_trg[itrg];
    delete hSignalCosSin4_trg[itrg];
    delete hSignalCosSin5_trg[itrg];
    delete hSignalCosSin2_ass[itrg];
    delete hSignalCosSin3_ass[itrg];
    delete hSignalCosSin4_ass[itrg];
    delete hSignalCosSin5_ass[itrg];
    delete hSignalCosnPM[itrg];
    delete hSignalSinnPM[itrg];
    delete hSignalRhon_trg[itrg];
    delete hSignalEPAnglen_trg[itrg];
    delete hSignalRhon_ass[itrg];
    delete hSignalEPAnglen_ass[itrg];
    delete hSignalRhon_all[itrg];
    delete hSignalEPAnglen_all[itrg];

    delete hMult_trg[itrg];
    delete hMultCorr_trg[itrg];
    delete hpT_Signal_trg[itrg];
    delete hpTCorr_Signal_trg[itrg];
    delete hdNdetadphi_trg[itrg];
    delete hdNdetadphiCorr_trg[itrg];
    delete hMult_ass[itrg];
    delete hMultCorr_ass[itrg];
    delete hpT_Signal_ass[itrg];
    delete hpTCorr_Signal_ass[itrg];
    delete hdNdetadphi_ass[itrg];
    delete hdNdetadphiCorr_ass[itrg];
  }
}

//--------------- Calculate signal distributions ----------------------
void EbyEFlowAnalyzerFWLite::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  {
    unsigned int ntrgsize = eventcorr.pVect_trg[itrg].size();
    unsigned int nasssize = eventcorr.pVect_ass[itrg].size();
    double nMultCorr_trg = eventcorr.nMultCorrVect_trg[itrg];
    double nMultCorr_ass = eventcorr.nMultCorrVect_ass[itrg];

    double sumcosn_trg[5]={0};
    double sumsinn_trg[5]={0};
    double sumrhon_trg[5]={0};
    double epanglen_trg[5]={0};
    double sumcosn_ass[5]={0};
    double sumsinn_ass[5]={0};
    double sumrhon_ass[5]={0};
    double epanglen_ass[5]={0};
    double sumcosn_all[5]={0};
    double sumsinn_all[5]={0};
    double sumrhon_all[5]={0};
    double epanglen_all[5]={0};

    // subevent 1
    for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
    {
      TLorentzVector pvector_trg = (eventcorr.pVect_trg[itrg])[ntrg];	  
      double effweight_trg = (eventcorr.effVect_trg[itrg])[ntrg];
/*
      double chg_trg = (eventcorr.chgVect_trg[itrg])[ntrg];
      double eta_trg = pvector_trg.Eta();
      double pt_trg = pvector_trg.Pt();
*/
      double phi_trg = pvector_trg.Phi();

      for(int nn = 0; nn<5; nn++)
      {
        sumcosn_trg[nn] = sumcosn_trg[nn] + cos((nn+1)*phi_trg)/effweight_trg;
        sumsinn_trg[nn] = sumsinn_trg[nn] + sin((nn+1)*phi_trg)/effweight_trg;
        sumcosn_all[nn] = sumcosn_all[nn] + cos((nn+1)*phi_trg)/effweight_trg;
        sumsinn_all[nn] = sumsinn_all[nn] + sin((nn+1)*phi_trg)/effweight_trg;
      }
    }

    // subevent 2
    for(unsigned int nass=0;nass<nasssize;nass++)
    {
      TLorentzVector pvector_ass = (eventcorr.pVect_ass[itrg])[nass];
      double effweight_ass = (eventcorr.effVect_ass[itrg])[nass];
/*
      double chg_ass = (eventcorr.chgVect_ass[itrg])[nass];
      double eta_ass = pvector_ass.Eta();
      double pt_ass = pvector_ass.Pt();
*/
      double phi_ass = pvector_ass.Phi();

      for(int nn = 0; nn<5; nn++)
      {
        sumcosn_ass[nn] = sumcosn_ass[nn] + cos((nn+1)*phi_ass)/effweight_ass;
        sumsinn_ass[nn] = sumsinn_ass[nn] + sin((nn+1)*phi_ass)/effweight_ass;
        sumcosn_all[nn] = sumcosn_all[nn] + cos((nn+1)*phi_ass)/effweight_ass;
        sumsinn_all[nn] = sumsinn_all[nn] + sin((nn+1)*phi_ass)/effweight_ass;
      }
    }

    for(int nn = 0; nn<5; nn++) 
    {
      sumcosn_trg[nn]=sumcosn_trg[nn]/nMultCorr_trg;
      sumsinn_trg[nn]=sumsinn_trg[nn]/nMultCorr_trg;
      sumrhon_trg[nn]=sqrt(sumcosn_trg[nn]*sumcosn_trg[nn]+sumsinn_trg[nn]*sumsinn_trg[nn]);
      epanglen_trg[nn]=atan2(sumsinn_trg[nn],sumcosn_trg[nn])/(nn+1);

      sumcosn_ass[nn]=sumcosn_ass[nn]/nMultCorr_ass;
      sumsinn_ass[nn]=sumsinn_ass[nn]/nMultCorr_ass;
      sumrhon_ass[nn]=sqrt(sumcosn_ass[nn]*sumcosn_ass[nn]+sumsinn_ass[nn]*sumsinn_ass[nn]);
      epanglen_ass[nn]=atan2(sumsinn_ass[nn],sumcosn_ass[nn])/(nn+1);

      sumcosn_all[nn]=sumcosn_all[nn]/(nMultCorr_ass+nMultCorr_trg);
      sumsinn_all[nn]=sumsinn_all[nn]/(nMultCorr_ass+nMultCorr_trg);
      sumrhon_all[nn]=sqrt(sumcosn_all[nn]*sumcosn_all[nn]+sumsinn_all[nn]*sumsinn_all[nn]);
      epanglen_all[nn]=atan2(sumsinn_all[nn],sumcosn_all[nn])/(nn+1);

      hSignalCosnPM[itrg]->Fill(sumcosn_trg[nn]-sumcosn_ass[nn],nn+1);
      hSignalSinnPM[itrg]->Fill(sumsinn_trg[nn]-sumsinn_ass[nn],nn+1);
      hSignalRhon_trg[itrg]->Fill(sumrhon_trg[nn],nn+1);
      hSignalEPAnglen_trg[itrg]->Fill(epanglen_trg[nn],nn+1);
      hSignalRhon_ass[itrg]->Fill(sumrhon_ass[nn],nn+1);
      hSignalEPAnglen_ass[itrg]->Fill(epanglen_ass[nn],nn+1);
      hSignalRhon_all[itrg]->Fill(sumrhon_all[nn],nn+1);
      hSignalEPAnglen_all[itrg]->Fill(epanglen_all[nn],nn+1);
    }

    hSignalCosSin2_trg[itrg]->Fill(sumcosn_trg[1],sumsinn_trg[1]);
    hSignalCosSin3_trg[itrg]->Fill(sumcosn_trg[2],sumsinn_trg[2]);
    hSignalCosSin4_trg[itrg]->Fill(sumcosn_trg[3],sumsinn_trg[3]);
    hSignalCosSin5_trg[itrg]->Fill(sumcosn_trg[4],sumsinn_trg[4]);

    hSignalCosSin2_ass[itrg]->Fill(sumcosn_ass[1],sumsinn_ass[1]);
    hSignalCosSin3_ass[itrg]->Fill(sumcosn_ass[2],sumsinn_ass[2]);
    hSignalCosSin4_ass[itrg]->Fill(sumcosn_ass[3],sumsinn_ass[3]);
    hSignalCosSin5_ass[itrg]->Fill(sumcosn_ass[4],sumsinn_ass[4]);
  } 
}

TList* EbyEFlowAnalyzerFWLite::GetOutputs()
{
  TList* outputlist;

  if(cutPara.IsCorr)
  { 
    outputlist = new TList();
    outputlist->Add(hMultRawAll);
    outputlist->Add(hMultCorrAll);
    for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
    {
      outputlist->Add(hSignalCosSin2_trg[itrg]);
      outputlist->Add(hSignalCosSin3_trg[itrg]);
      outputlist->Add(hSignalCosSin4_trg[itrg]);
      outputlist->Add(hSignalCosSin5_trg[itrg]);
      outputlist->Add(hSignalCosSin2_ass[itrg]);
      outputlist->Add(hSignalCosSin3_ass[itrg]);
      outputlist->Add(hSignalCosSin4_ass[itrg]);
      outputlist->Add(hSignalCosSin5_ass[itrg]);
      outputlist->Add(hSignalCosnPM[itrg]);
      outputlist->Add(hSignalSinnPM[itrg]);
      outputlist->Add(hSignalRhon_trg[itrg]);
      outputlist->Add(hSignalEPAnglen_trg[itrg]);
      outputlist->Add(hSignalRhon_ass[itrg]);
      outputlist->Add(hSignalEPAnglen_ass[itrg]);
      outputlist->Add(hSignalRhon_all[itrg]);
      outputlist->Add(hSignalEPAnglen_all[itrg]);

      outputlist->Add(hMult_trg[itrg]);
      outputlist->Add(hMultCorr_trg[itrg]);
      outputlist->Add(hpT_Signal_trg[itrg]);
      outputlist->Add(hpTCorr_Signal_trg[itrg]);
      outputlist->Add(hpT_Background_trg[itrg]);
      outputlist->Add(hpTCorr_Background_trg[itrg]);
      outputlist->Add(hdNdetadphi_trg[itrg]);
      outputlist->Add(hdNdetadphiCorr_trg[itrg]);   
      outputlist->Add(hMult_ass[itrg]);
      outputlist->Add(hMultCorr_ass[itrg]);
      outputlist->Add(hpT_Signal_ass[itrg]);
      outputlist->Add(hpTCorr_Signal_ass[itrg]);
      outputlist->Add(hpT_Background_ass[itrg]);
      outputlist->Add(hpTCorr_Background_ass[itrg]);
      outputlist->Add(hdNdetadphi_ass[itrg]);
      outputlist->Add(hdNdetadphiCorr_ass[itrg]);
    }
  }
  else outputlist = (TList*)DiHadronCorrelationMultiBaseFWLite::GetOutputs();

  return outputlist;
}
