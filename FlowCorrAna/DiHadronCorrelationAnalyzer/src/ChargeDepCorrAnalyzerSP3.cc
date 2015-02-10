#include "../interface/ChargeDepCorrAnalyzerSP3.h"
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

ChargeDepCorrAnalyzerSP3::ChargeDepCorrAnalyzerSP3(const edm::ParameterSet& iConfig) :
  DiHadronCorrelationMultiBase(iConfig)
{
/*
  for(double mult = 0; mult < 4; mult += 1) multBins.push_back(mult);
  for(double mult = 4; mult < 10; mult += 2) multBins.push_back(mult);
  for(double mult = 10; mult < 30; mult += 4) multBins.push_back(mult);
  for(double mult = 30; mult < 80; mult += 10) multBins.push_back(mult);
  for(double mult = 80; mult < 120; mult += 20) multBins.push_back(mult);
  for(double mult = 120; mult < 200; mult += 40) multBins.push_back(mult);
  multBins.push_back(200.);
*/
/*
  for(double mult = 0; mult < 10; mult += 1) multBins.push_back(mult);
  for(double mult = 10; mult < 50; mult += 4) multBins.push_back(mult);
  for(double mult = 50; mult < 130; mult += 16) multBins.push_back(mult);
  for(double mult = 130; mult < 200; mult += 70) multBins.push_back(mult);
  for(double mult = 200; mult < 400; mult += 200) multBins.push_back(mult);
*/
  multBins.push_back(0);
  multBins.push_back(1000);

  cutPara.etagap = iConfig.getParameter<double>("etagap");
  cutPara.IsReCenter = iConfig.getParameter<bool>("IsReCenter");
/*
  dndetadphi_filename = new TString(iConfig.getParameter<string>("dNdetadphiFileName"));
  if(dndetadphi_filename->Length()) 
  {
    edm::FileInPath fip2(Form("FlowCorrAna/DiHadronCorrelationAnalyzer/data/%s",dndetadphi_filename->Data()));
    fdndetadphi = new TFile(fip2.fullPath().c_str(),"READ");
  }
  else fdndetadphi = 0;
*/
  frecenter=0;
  if(cutPara.IsReCenter) return;
  recenter_filename = new TString(iConfig.getParameter<string>("ReCenterFileName"));
  recenter_dirname = new TString(iConfig.getParameter<string>("ReCenterDirName"));
  if(!recenter_filename->Length()) return;
  edm::FileInPath fip(Form("FlowCorrAna/DiHadronCorrelationAnalyzer/data/%s",recenter_filename->Data()));
  frecenter = new TFile(fip.fullPath().c_str(),"READ");
}

ChargeDepCorrAnalyzerSP3::~ChargeDepCorrAnalyzerSP3() 
{}

void ChargeDepCorrAnalyzerSP3::beginJob()
{
  DiHadronCorrelationMultiBase::beginJob();

//  double scale_factor = 500.0;
/*
  double etaMin   = 0.0-ETATRGBINWIDTHPT/2;
  double etaMax   = 4.8-ETATRGBINWIDTHPT/2;
  std::vector<double> etaBins;
  for(double eta = etaMin; eta < etaMax + ETATRGBINWIDTHPT/2; eta += ETATRGBINWIDTHPT)
    etaBins.push_back(eta);
*/
  hdNdEtadPhiPos = theOutputs->make<TH2D>("dndetadphipos",";#eta;#phi",MAXETATRGBINSPT,-2.4,2.4,128,-PI,PI);
  hdNdEtadPhiNeg = theOutputs->make<TH2D>("dndetadphineg",";#eta;#phi",MAXETATRGBINSPT,-2.4,2.4,128,-PI,PI);
/*
  if(fdndetadphi)
  {
    hdNdEtadPhiPosWeight = (TH2D*)fdndetadphi->Get("dNdetadphi_weight_pos");
    hdNdEtadPhiNegWeight = (TH2D*)fdndetadphi->Get("dNdetadphi_weight_neg");
  }
  else 
  {
    hdNdEtadPhiPosWeight = 0;
    hdNdEtadPhiNegWeight = 0; 
  }
*/
  if(!cutPara.IsReCenter)
  {
    hSignalCos_same_for = theOutputs->make<TH2D>("signalcos_same_for",";cos(#phi_{a}+#phi_{b}-2#phi_{c});#Delta#eta",20000,-20,20,MAXETATRGBINSPT,0-2.4/MAXETATRGBINSPT,4.8-2.4/MAXETATRGBINSPT);
    hSignalCos_diff_for = theOutputs->make<TH2D>("signalcos_diff_for",";cos(#phi_{a}+#phi_{b}-2#phi_{c});#Delta#eta",20000,-20,20,MAXETATRGBINSPT,0-2.4/MAXETATRGBINSPT,4.8-2.4/MAXETATRGBINSPT);
    hSignalCos_same_bak = theOutputs->make<TH2D>("signalcos_same_bak",";cos(#phi_{a}+#phi_{b}-2#phi_{c});#Delta#eta",20000,-20,20,MAXETATRGBINSPT,0-2.4/MAXETATRGBINSPT,4.8-2.4/MAXETATRGBINSPT);
    hSignalCos_diff_bak = theOutputs->make<TH2D>("signalcos_diff_bak",";cos(#phi_{a}+#phi_{b}-2#phi_{c});#Delta#eta",20000,-20,20,MAXETATRGBINSPT,0-2.4/MAXETATRGBINSPT,4.8-2.4/MAXETATRGBINSPT);
    hSignalCos2PcorrP_same = theOutputs->make<TH2D>("signalcos2pcorrp_same",";cos(#phi_{a}+#phi_{b});#Delta#eta",20000,-1,1,MAXETATRGBINSPT,0-2.4/MAXETATRGBINSPT,4.8-2.4/MAXETATRGBINSPT);
    hSignalCos2PcorrM_same = theOutputs->make<TH2D>("signalcos2pcorrm_same",";cos(#phi_{a}-#phi_{b});#Delta#eta",20000,-1,1,MAXETATRGBINSPT,0-2.4/MAXETATRGBINSPT,4.8-2.4/MAXETATRGBINSPT);
    hSignalCos2PcorrP_diff = theOutputs->make<TH2D>("signalcos2pcorrp_diff",";cos(#phi_{a}+#phi_{b});#Delta#eta",20000,-1,1,MAXETATRGBINSPT,0-2.4/MAXETATRGBINSPT,4.8-2.4/MAXETATRGBINSPT);
    hSignalCos2PcorrM_diff = theOutputs->make<TH2D>("signalcos2pcorrm_diff",";cos(#phi_{a}-#phi_{b});#Delta#eta",20000,-1,1,MAXETATRGBINSPT,0-2.4/MAXETATRGBINSPT,4.8-2.4/MAXETATRGBINSPT);
    hSignalNpairs_same = theOutputs->make<TH2D>("signalnpairs_same",";Npairs;#Delta#eta",1000,0,200000,MAXETATRGBINSPT,0-2.4/MAXETATRGBINSPT,4.8-2.4/MAXETATRGBINSPT);
    hSignalNpairs_diff = theOutputs->make<TH2D>("signalnpairs_diff",";Npairs;#Delta#eta",1000,0,200000,MAXETATRGBINSPT,0-2.4/MAXETATRGBINSPT,4.8-2.4/MAXETATRGBINSPT);
    hQ2AssCos = theOutputs->make<TH1D>("q2asscos",";Q_{2}^{2}",20000,-10000.0,10000.0);
  }
  else
  {
    for(int kk=0;kk<MAXZVTXBINS;kk++)
    {
      for(int ll=0;ll<MAXETATRGBINSPT;ll++)
      {
        hSumCosTrgPos[kk][ll] = theOutputs->make<TH2D>(Form("sumcostrgpos_vtx%d_eta%d",kk,ll),";Q_{2};n",400,-1.0,1.0,multBins.size()-1, &multBins[0]);
        hSumSinTrgPos[kk][ll] = theOutputs->make<TH2D>(Form("sumsintrgpos_vtx%d_eta%d",kk,ll),";Q_{2};n",400,-1.0,1.0,multBins.size()-1, &multBins[0]);
        hSumCosTrgNeg[kk][ll] = theOutputs->make<TH2D>(Form("sumcostrgneg_vtx%d_eta%d",kk,ll),";Q_{2};n",400,-1.0,1.0,multBins.size()-1, &multBins[0]);
        hSumSinTrgNeg[kk][ll] = theOutputs->make<TH2D>(Form("sumsintrgneg_vtx%d_eta%d",kk,ll),";Q_{2};n",400,-1.0,1.0,multBins.size()-1, &multBins[0]);
        hSumCos2TrgPos[kk][ll] = theOutputs->make<TH2D>(Form("sumcos2trgpos_vtx%d_eta%d",kk,ll),";Q_{2};n",400,-1.0,1.0,multBins.size()-1, &multBins[0]);
        hSumSin2TrgPos[kk][ll] = theOutputs->make<TH2D>(Form("sumsin2trgpos_vtx%d_eta%d",kk,ll),";Q_{2};n",400,-1.0,1.0,multBins.size()-1, &multBins[0]);
        hSumCos2TrgNeg[kk][ll] = theOutputs->make<TH2D>(Form("sumcos2trgneg_vtx%d_eta%d",kk,ll),";Q_{2};n",400,-1.0,1.0,multBins.size()-1, &multBins[0]);
        hSumSin2TrgNeg[kk][ll] = theOutputs->make<TH2D>(Form("sumsin2trgneg_vtx%d_eta%d",kk,ll),";Q_{2};n",400,-1.0,1.0,multBins.size()-1, &multBins[0]);
      }

      hSumAssFor[kk] = theOutputs->make<TH1D>(Form("sumassfor_vtx%d",kk),";Q_{2}",10000,0.0,10000.0);
      hSumAssBak[kk] = theOutputs->make<TH1D>(Form("sumassbak_vtx%d",kk),";Q_{2}",10000,0.0,10000.0);
      hSumCosAssFor[kk] = theOutputs->make<TH1D>(Form("sumcosassfor_vtx%d",kk),";Q_{2}",10000,-500.0,500.0);
      hSumSinAssFor[kk] = theOutputs->make<TH1D>(Form("sumsinassfor_vtx%d",kk),";Q_{2}",10000,-500.0,500.0);
      hSumCosAssBak[kk] = theOutputs->make<TH1D>(Form("sumcosassbak_vtx%d",kk),";Q_{2}",10000,-500.0,500.0);
      hSumSinAssBak[kk] = theOutputs->make<TH1D>(Form("sumsinassbak_vtx%d",kk),";Q_{2}",10000,-500.0,500.0);
      hSumCos2AssFor[kk] = theOutputs->make<TH1D>(Form("sumcos2assfor_vtx%d",kk),";Q_{2}",10000,-500.0,500.0);
      hSumSin2AssFor[kk] = theOutputs->make<TH1D>(Form("sumsin2assfor_vtx%d",kk),";Q_{2}",10000,-500.0,500.0);
      hSumCos2AssBak[kk] = theOutputs->make<TH1D>(Form("sumcos2assbak_vtx%d",kk),";Q_{2}",10000,-500.0,500.0);
      hSumSin2AssBak[kk] = theOutputs->make<TH1D>(Form("sumsin2assbak_vtx%d",kk),";Q_{2}",10000,-500.0,500.0);
    }
  }

  for(int kk=0;kk<MAXZVTXBINS;kk++)
  {
    if(frecenter)
    {
/*
      hSumNCosTrgPos[kk] = (TH2D*)frecenter->Get(Form("sumncostrgpos_vtx%d",kk));
      hSumNCosTrgNeg[kk] = (TH2D*)frecenter->Get(Form("sumncostrgneg_vtx%d",kk));
      hSumNSinTrgPos[kk] = (TH2D*)frecenter->Get(Form("sumnsintrgpos_vtx%d",kk));
      hSumNSinTrgNeg[kk] = (TH2D*)frecenter->Get(Form("sumnsintrgneg_vtx%d",kk));
      hSumNCos2TrgPos[kk] = (TH2D*)frecenter->Get(Form("sumncos2trgpos_vtx%d",kk));
      hSumNCos2TrgNeg[kk] = (TH2D*)frecenter->Get(Form("sumncos2trgneg_vtx%d",kk));
      hSumNSin2TrgPos[kk] = (TH2D*)frecenter->Get(Form("sumnsin2trgpos_vtx%d",kk));
      hSumNSin2TrgNeg[kk] = (TH2D*)frecenter->Get(Form("sumnsin2trgneg_vtx%d",kk));
*/
      hSumNCosTrgPos[kk] = (TH2D*)frecenter->Get(Form("sumncostrgpos_vtx%d_all",kk));
      hSumNCosTrgNeg[kk] = (TH2D*)frecenter->Get(Form("sumncostrgneg_vtx%d_all",kk));
      hSumNSinTrgPos[kk] = (TH2D*)frecenter->Get(Form("sumnsintrgpos_vtx%d_all",kk));
      hSumNSinTrgNeg[kk] = (TH2D*)frecenter->Get(Form("sumnsintrgneg_vtx%d_all",kk));
      hSumNCos2TrgPos[kk] = (TH2D*)frecenter->Get(Form("sumncos2trgpos_vtx%d_all",kk));
      hSumNCos2TrgNeg[kk] = (TH2D*)frecenter->Get(Form("sumncos2trgneg_vtx%d_all",kk));
      hSumNSin2TrgPos[kk] = (TH2D*)frecenter->Get(Form("sumnsin2trgpos_vtx%d_all",kk));
      hSumNSin2TrgNeg[kk] = (TH2D*)frecenter->Get(Form("sumnsin2trgneg_vtx%d_all",kk));
      if(!hSumNCosTrgPos[kk] || !hSumNCosTrgNeg[kk] || !hSumNSinTrgPos[kk] || !hSumNSinTrgNeg[kk] || !hSumNCos2TrgPos[kk] || !hSumNCos2TrgNeg[kk] || !hSumNSin2TrgPos[kk] || !hSumNSin2TrgNeg[kk]) cout<<"correction histograms missing!"<<endl;
    }
    else
    {
      hSumNCosTrgPos[kk] = 0; 
      hSumNCosTrgNeg[kk] = 0;
      hSumNSinTrgPos[kk] = 0;
      hSumNSinTrgNeg[kk] = 0;
      hSumNCos2TrgPos[kk] = 0;
      hSumNCos2TrgNeg[kk] = 0;
      hSumNSin2TrgPos[kk] = 0;
      hSumNSin2TrgNeg[kk] = 0;
      cout<<"No acceptance correction applied!"<<endl;
    }
  }
}

void ChargeDepCorrAnalyzerSP3::endJob()
{
  DiHadronCorrelationMultiBase::endJob();
  
  unsigned int neventsArr = eventcorrArray.size();
  unsigned int nevents = hMultRawAll->GetEntries();

  cout<< "Start running CME analysis!" << endl;
  cout<< "There are "<<neventsArr<<" and "<<nevents<<" events selected!"<<endl;

  if(cutPara.IsReCenter) 
  {
    for(unsigned int i=0;i<neventsArr;i++)
    {
      if( i % 1000 == 0 ) cout << "Recenter: processing " << i << "th event" << endl;
      int zvtxbin = (int)((eventcorrArray[i].zvtx+15.)/30.0*MAXZVTXBINS);
      FillHistsQVectorTrk(eventcorrArray[i],zvtxbin);
      FillHistsQVectorHF(eventcorrArray[i],zvtxbin);
      Recenter(zvtxbin);
    }
  }
  else
  {
    for(unsigned int i=0;i<neventsArr;i++)
    {
      int zvtxbin = (int)((eventcorrArray[i].zvtx+15.)/30.0*MAXZVTXBINS);

      FillHistsQVectorHF(eventcorrArray[i],zvtxbin);
      if(npairs_ass_for && npairs_ass_bak) hQ2AssCos->Fill(sumcosn_ass_for*sumcosn_ass_bak+sumsinn_ass_for*sumsinn_ass_bak);

      FillHistsQVectorTrk(eventcorrArray[i],zvtxbin);       
      FillHistsCorrelators();
    }
  }

  cout<< "Finish running CME analysis!" << endl;
}

void ChargeDepCorrAnalyzerSP3::Recenter(int zvtxbin)
{
  if(npairs_ass_for)
  {
    hSumAssFor[zvtxbin]->Fill(npairs_ass_for);
    hSumCosAssFor[zvtxbin]->Fill(sumcosn_ass_for);
    hSumSinAssFor[zvtxbin]->Fill(sumsinn_ass_for);
    hSumCos2AssFor[zvtxbin]->Fill(sumcos2n_ass_for);
    hSumSin2AssFor[zvtxbin]->Fill(sumsin2n_ass_for);
  }
  if(npairs_ass_bak)
  {
    hSumAssBak[zvtxbin]->Fill(npairs_ass_bak);
    hSumCosAssBak[zvtxbin]->Fill(sumcosn_ass_bak);
    hSumSinAssBak[zvtxbin]->Fill(sumsinn_ass_bak);
    hSumCos2AssBak[zvtxbin]->Fill(sumcos2n_ass_bak);
    hSumSin2AssBak[zvtxbin]->Fill(sumsin2n_ass_bak);
  }

  for(int i=0;i<MAXETATRGBINSPT;i++)
  {
    if(npairs_trg_pos[i]!=0)
    {
      hSumCosTrgPos[zvtxbin][i]->Fill(sumcosn_trg_pos[i]/npairs_trg_pos[i],npairs_trg_pos[i]);
      hSumCos2TrgPos[zvtxbin][i]->Fill(sumcos2n_trg_pos[i]/npairs_trg_pos[i],npairs_trg_pos[i]);
      hSumSinTrgPos[zvtxbin][i]->Fill(sumsinn_trg_pos[i]/npairs_trg_pos[i],npairs_trg_pos[i]);
      hSumSin2TrgPos[zvtxbin][i]->Fill(sumsin2n_trg_pos[i]/npairs_trg_pos[i],npairs_trg_pos[i]);
    }
    if(npairs_trg_neg[i]!=0)
    {
      hSumCosTrgNeg[zvtxbin][i]->Fill(sumcosn_trg_neg[i]/npairs_trg_neg[i],npairs_trg_neg[i]);
      hSumCos2TrgNeg[zvtxbin][i]->Fill(sumcos2n_trg_neg[i]/npairs_trg_neg[i],npairs_trg_neg[i]);
      hSumSinTrgNeg[zvtxbin][i]->Fill(sumsinn_trg_neg[i]/npairs_trg_neg[i],npairs_trg_neg[i]);
      hSumSin2TrgNeg[zvtxbin][i]->Fill(sumsin2n_trg_neg[i]/npairs_trg_neg[i],npairs_trg_neg[i]);
    }
  }
}

void ChargeDepCorrAnalyzerSP3::FillHistsQVectorHF(const DiHadronCorrelationEvent& eventcorr, int zvtxbin)
{
  sumcosn_ass_for=0.0;
  sumsinn_ass_for=0.0;
  sumcos2n_ass_for=0.0;
  sumsin2n_ass_for=0.0;
  npairs_ass_for=0.0;
  sumcosn_ass_bak=0.0;
  sumsinn_ass_bak=0.0;
  sumcos2n_ass_bak=0.0;
  sumsin2n_ass_bak=0.0;
  npairs_ass_bak=0.0;

  unsigned int nasssize = eventcorr.pVect_ass[0].size();
  for(unsigned int nass=0;nass<nasssize;nass++)
  {
    TLorentzVector pvector_ass = (eventcorr.pVect_ass[0])[nass];
    double effweight_ass = (eventcorr.effVect_ass[0])[nass];
    double eta_ass = pvector_ass.Eta()-cutPara.etacms;
    double phi_ass = pvector_ass.Phi();

    if(eta_ass>0)
    {
      sumcosn_ass_for = sumcosn_ass_for + cos(2*phi_ass)/effweight_ass;
      sumsinn_ass_for = sumsinn_ass_for + sin(2*phi_ass)/effweight_ass;
      sumcos2n_ass_for = sumcos2n_ass_for + cos(4*phi_ass)/effweight_ass/effweight_ass;
      sumsin2n_ass_for = sumsin2n_ass_for + sin(4*phi_ass)/effweight_ass/effweight_ass;
      npairs_ass_for += 1.0/effweight_ass;
    }
    if(eta_ass<0)
    {
      sumcosn_ass_bak = sumcosn_ass_bak + cos(2*phi_ass)/effweight_ass;
      sumsinn_ass_bak = sumsinn_ass_bak + sin(2*phi_ass)/effweight_ass;
      sumcos2n_ass_bak = sumcos2n_ass_bak + cos(4*phi_ass)/effweight_ass/effweight_ass;
      sumsin2n_ass_bak = sumsin2n_ass_bak + sin(4*phi_ass)/effweight_ass/effweight_ass;
      npairs_ass_bak += 1.0/effweight_ass;
    }
  } 

  //Applying corrections
  if(npairs_ass_for)
  {
//    sumcosn_ass_for /= npairs_ass_for;
//    sumsinn_ass_for /= npairs_ass_for;
    if(hSumNCosTrgPos[zvtxbin] && hSumNSinTrgPos[zvtxbin] && hSumNSin2TrgPos[zvtxbin] && hSumNCos2TrgPos[zvtxbin]) 
    {
      sumcosn_ass_for -= npairs_ass_for * hSumNCosTrgPos[zvtxbin]->GetBinContent(1,2);
      sumsinn_ass_for -= npairs_ass_for * hSumNSinTrgPos[zvtxbin]->GetBinContent(1,2);

      double lambda_p = - hSumNSin2TrgPos[zvtxbin]->GetBinContent(1,2)/(1+hSumNCos2TrgPos[zvtxbin]->GetBinContent(1,2));
      double lambda_n = hSumNSin2TrgPos[zvtxbin]->GetBinContent(1,2)/(1-hSumNCos2TrgPos[zvtxbin]->GetBinContent(1,2));
      sumcosn_ass_for = (sumcosn_ass_for-lambda_n*sumsinn_ass_for)/(1-lambda_p*lambda_n);
      sumsinn_ass_for = (sumsinn_ass_for-lambda_p*sumcosn_ass_for)/(1-lambda_p*lambda_n);

      sumcosn_ass_for /= 1+hSumNCos2TrgPos[zvtxbin]->GetBinContent(1,2);
      sumsinn_ass_for /= 1-hSumNCos2TrgPos[zvtxbin]->GetBinContent(1,2);
    }
  }

  if(npairs_ass_bak) 
  {
//    sumcosn_ass_bak /= npairs_ass_bak;
//    sumsinn_ass_bak /= npairs_ass_bak;
    if(hSumNCosTrgPos[zvtxbin] && hSumNSinTrgPos[zvtxbin] && hSumNSin2TrgPos[zvtxbin] && hSumNCos2TrgPos[zvtxbin]) 
    {
      sumcosn_ass_bak -= npairs_ass_bak * hSumNCosTrgPos[zvtxbin]->GetBinContent(MAXETATRGBINSPT+2,2);
      sumsinn_ass_bak -= npairs_ass_bak * hSumNSinTrgPos[zvtxbin]->GetBinContent(MAXETATRGBINSPT+2,2);

      double lambda_p = - hSumNSin2TrgPos[zvtxbin]->GetBinContent(MAXETATRGBINSPT+2,2)/(1+hSumNCos2TrgPos[zvtxbin]->GetBinContent(MAXETATRGBINSPT+2,2));
      double lambda_n = hSumNSin2TrgPos[zvtxbin]->GetBinContent(MAXETATRGBINSPT+2,2)/(1-hSumNCos2TrgPos[zvtxbin]->GetBinContent(MAXETATRGBINSPT+2,2));
      sumcosn_ass_bak = (sumcosn_ass_bak-lambda_n*sumsinn_ass_bak)/(1-lambda_p*lambda_n);
      sumsinn_ass_bak = (sumsinn_ass_bak-lambda_p*sumcosn_ass_bak)/(1-lambda_p*lambda_n);

      sumcosn_ass_bak /= 1+hSumNCos2TrgPos[zvtxbin]->GetBinContent(MAXETATRGBINSPT+2,2);
      sumsinn_ass_bak /= 1-hSumNCos2TrgPos[zvtxbin]->GetBinContent(MAXETATRGBINSPT+2,2);
    }
  }
}

void ChargeDepCorrAnalyzerSP3::FillHistsQVectorTrk(const DiHadronCorrelationEvent& eventcorr, int zvtxbin)
{
  for(int i=0;i<MAXETATRGBINSPT;i++)
  {
    sumcosn_trg_pos[i]=0.0;
    sumsinn_trg_pos[i]=0.0;
    sumcos2n_trg_pos[i]=0.0;
    sumsin2n_trg_pos[i]=0.0;
    npairs_trg_pos[i]=0.0;
    sumcosn_trg_neg[i]=0.0;
    sumsinn_trg_neg[i]=0.0;
    sumcos2n_trg_neg[i]=0.0;
    sumsin2n_trg_neg[i]=0.0;
    npairs_trg_neg[i]=0.0;
  }

  unsigned int ntrgsize = eventcorr.pVect_trg[0].size();
  for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
  {
    TLorentzVector pvector_trg = (eventcorr.pVect_trg[0])[ntrg];
    double effweight_trg = (eventcorr.effVect_trg[0])[ntrg];
    double charge_trg = (eventcorr.chgVect_trg[0])[ntrg];
    double eta_trg = pvector_trg.Eta()-cutPara.etacms;
    double phi_trg = pvector_trg.Phi();

    int ietabin = (int)((eta_trg+2.4)/ETATRGBINWIDTHPT);

    if(charge_trg>0)
    {
      hdNdEtadPhiPos->Fill(eta_trg,phi_trg,1.0/effweight_trg);
      sumcosn_trg_pos[ietabin] += cos(phi_trg)/effweight_trg;
      sumsinn_trg_pos[ietabin] += sin(phi_trg)/effweight_trg;
      sumcos2n_trg_pos[ietabin] += cos(2*phi_trg)/effweight_trg/effweight_trg;
      sumsin2n_trg_pos[ietabin] += sin(2*phi_trg)/effweight_trg/effweight_trg;
      npairs_trg_pos[ietabin] += 1.0/effweight_trg;
    }
    if(charge_trg<0)
    {
      hdNdEtadPhiNeg->Fill(eta_trg,phi_trg,1.0/effweight_trg);
      sumcosn_trg_neg[ietabin] += cos(phi_trg)/effweight_trg;
      sumsinn_trg_neg[ietabin] += sin(phi_trg)/effweight_trg;
      sumcos2n_trg_neg[ietabin] += cos(2*phi_trg)/effweight_trg/effweight_trg;
      sumsin2n_trg_neg[ietabin] += sin(2*phi_trg)/effweight_trg/effweight_trg;
      npairs_trg_neg[ietabin] += 1.0/effweight_trg;
    }
  }

  // Applying corrections
  for(int i=0;i<MAXETATRGBINSPT;i++)
  {
    if(npairs_trg_pos[i]!=0 && hSumNCosTrgPos[zvtxbin] && hSumNSinTrgPos[zvtxbin] && hSumNSin2TrgPos[zvtxbin] && hSumNCos2TrgPos[zvtxbin])
    {
      // recenter
      sumcosn_trg_pos[i] -= npairs_trg_pos[i]*hSumNCosTrgPos[zvtxbin]->GetBinContent(i+2,hSumNCosTrgPos[zvtxbin]->GetYaxis()->FindBin(npairs_trg_pos[i]+0.001));
      sumsinn_trg_pos[i] -= npairs_trg_pos[i]*hSumNSinTrgPos[zvtxbin]->GetBinContent(i+2,hSumNSinTrgPos[zvtxbin]->GetYaxis()->FindBin(npairs_trg_pos[i]+0.001));
      sumcos2n_trg_pos[i] -= npairs_trg_pos[i]*hSumNCos2TrgPos[zvtxbin]->GetBinContent(i+2,hSumNCos2TrgPos[zvtxbin]->GetYaxis()->FindBin(npairs_trg_pos[i]+0.001));
      sumsin2n_trg_pos[i] -= npairs_trg_pos[i]*hSumNSin2TrgPos[zvtxbin]->GetBinContent(i+2,hSumNSin2TrgPos[zvtxbin]->GetYaxis()->FindBin(npairs_trg_pos[i]+0.001));

      // twist
      double lambda_p = - hSumNSin2TrgPos[zvtxbin]->GetBinContent(i+2,hSumNSin2TrgPos[zvtxbin]->GetYaxis()->FindBin(npairs_trg_pos[i]+0.001))/(1+hSumNCos2TrgPos[zvtxbin]->GetBinContent(i+2,hSumNCos2TrgPos[zvtxbin]->GetYaxis()->FindBin(npairs_trg_pos[i]+0.001)));  
      double lambda_n = hSumNSin2TrgPos[zvtxbin]->GetBinContent(i+2,hSumNSin2TrgPos[zvtxbin]->GetYaxis()->FindBin(npairs_trg_pos[i]+0.001))/(1-hSumNCos2TrgPos[zvtxbin]->GetBinContent(i+2,hSumNCos2TrgPos[zvtxbin]->GetYaxis()->FindBin(npairs_trg_pos[i]+0.001)));

      sumcosn_trg_pos[i] = (sumcosn_trg_pos[i]-lambda_n*sumsinn_trg_pos[i])/(1-lambda_p*lambda_n);
      sumsinn_trg_pos[i] = (sumsinn_trg_pos[i]-lambda_p*sumcosn_trg_pos[i])/(1-lambda_p*lambda_n);

      // rescale
      sumcosn_trg_pos[i] /= 1+hSumNCos2TrgPos[zvtxbin]->GetBinContent(i+2,hSumNCos2TrgPos[zvtxbin]->GetYaxis()->FindBin(npairs_trg_pos[i]+0.001));
      sumsinn_trg_pos[i] /= 1-hSumNCos2TrgPos[zvtxbin]->GetBinContent(i+2,hSumNCos2TrgPos[zvtxbin]->GetYaxis()->FindBin(npairs_trg_pos[i]+0.001));
    }

    if(npairs_trg_neg[i]!=0 && hSumNCosTrgNeg[zvtxbin] && hSumNSinTrgNeg[zvtxbin] && hSumNSin2TrgNeg[zvtxbin] && hSumNCos2TrgNeg[zvtxbin]) 
    {
      sumcosn_trg_neg[i] -= npairs_trg_neg[i]*hSumNCosTrgNeg[zvtxbin]->GetBinContent(i+2,hSumNCosTrgNeg[zvtxbin]->GetYaxis()->FindBin(npairs_trg_neg[i]+0.001));
      sumsinn_trg_neg[i] -= npairs_trg_neg[i]*hSumNSinTrgNeg[zvtxbin]->GetBinContent(i+2,hSumNSinTrgNeg[zvtxbin]->GetYaxis()->FindBin(npairs_trg_neg[i]+0.001));
      sumcos2n_trg_neg[i] -= npairs_trg_neg[i]*hSumNCos2TrgNeg[zvtxbin]->GetBinContent(i+2,hSumNCos2TrgNeg[zvtxbin]->GetYaxis()->FindBin(npairs_trg_neg[i]+0.001));
      sumsin2n_trg_neg[i] -= npairs_trg_neg[i]*hSumNSin2TrgNeg[zvtxbin]->GetBinContent(i+2,hSumNSin2TrgNeg[zvtxbin]->GetYaxis()->FindBin(npairs_trg_neg[i]+0.001));

      double lambda_p = - hSumNSin2TrgNeg[zvtxbin]->GetBinContent(i+2,hSumNSin2TrgNeg[zvtxbin]->GetYaxis()->FindBin(npairs_trg_neg[i]+0.001))/(1+hSumNCos2TrgNeg[zvtxbin]->GetBinContent(i+2,hSumNCos2TrgNeg[zvtxbin]->GetYaxis()->FindBin(npairs_trg_neg[i]+0.001)));
      double lambda_n = hSumNSin2TrgNeg[zvtxbin]->GetBinContent(i+2,hSumNSin2TrgNeg[zvtxbin]->GetYaxis()->FindBin(npairs_trg_neg[i]+0.001))/(1-hSumNCos2TrgNeg[zvtxbin]->GetBinContent(i+2,hSumNCos2TrgNeg[zvtxbin]->GetYaxis()->FindBin(npairs_trg_neg[i]+0.001)));
      sumcosn_trg_neg[i] = (sumcosn_trg_neg[i]-lambda_n*sumsinn_trg_neg[i])/(1-lambda_p*lambda_n);
      sumsinn_trg_neg[i] = (sumsinn_trg_neg[i]-lambda_p*sumcosn_trg_neg[i])/(1-lambda_p*lambda_n);

      sumcosn_trg_neg[i] /= 1+hSumNCos2TrgNeg[zvtxbin]->GetBinContent(i+2,hSumNCos2TrgNeg[zvtxbin]->GetYaxis()->FindBin(npairs_trg_neg[i]+0.001));
      sumsinn_trg_neg[i] /= 1-hSumNCos2TrgNeg[zvtxbin]->GetBinContent(i+2,hSumNCos2TrgNeg[zvtxbin]->GetYaxis()->FindBin(npairs_trg_neg[i]+0.001));
    }
  }
}

void ChargeDepCorrAnalyzerSP3::FillHistsCorrelators()
{
  double Qabx_pp[MAXETATRGBINSPT] = {0};
  double Qaby_pp[MAXETATRGBINSPT] = {0};
  double Qabxx_pp[MAXETATRGBINSPT] = {0};
  double nabpairs_pp[MAXETATRGBINSPT] = {0};
  double Qabx_nn[MAXETATRGBINSPT] = {0};
  double Qaby_nn[MAXETATRGBINSPT] = {0};
  double Qabxx_nn[MAXETATRGBINSPT] = {0};
  double nabpairs_nn[MAXETATRGBINSPT] = {0};
  double Qabx_np[MAXETATRGBINSPT] = {0};
  double Qaby_np[MAXETATRGBINSPT] = {0};
  double Qabxx_np[MAXETATRGBINSPT] = {0};
  double nabpairs_np[MAXETATRGBINSPT] = {0};
  double Qabx_pn[MAXETATRGBINSPT] = {0};
  double Qaby_pn[MAXETATRGBINSPT] = {0};
  double Qabxx_pn[MAXETATRGBINSPT] = {0};
  double nabpairs_pn[MAXETATRGBINSPT] = {0};

  for(int i=0;i<MAXETATRGBINSPT;i++)
    for(int j=i;j<MAXETATRGBINSPT;j++)
    {
      Qabx_pp[j-i] += (sumcosn_trg_pos[i]*sumcosn_trg_pos[j]-sumsinn_trg_pos[i]*sumsinn_trg_pos[j]);
      Qaby_pp[j-i] += (sumcosn_trg_pos[i]*sumsinn_trg_pos[j]+sumsinn_trg_pos[i]*sumcosn_trg_pos[j]);
      Qabxx_pp[j-i] += (sumcosn_trg_pos[i]*sumcosn_trg_pos[j]+sumsinn_trg_pos[i]*sumsinn_trg_pos[j]);
      nabpairs_pp[j-i] += npairs_trg_pos[i]*npairs_trg_pos[j];
      if(j==i)
      {
        Qabx_pp[j-i] -= sumcos2n_trg_pos[i];
        Qaby_pp[j-i] -= sumsin2n_trg_pos[i];
        Qabxx_pp[j-i] -= npairs_trg_pos[i];
        nabpairs_pp[j-i] -= npairs_trg_pos[i];
      }

      Qabx_nn[j-i] += (sumcosn_trg_neg[i]*sumcosn_trg_neg[j]-sumsinn_trg_neg[i]*sumsinn_trg_neg[j]);
      Qaby_nn[j-i] += (sumcosn_trg_neg[i]*sumsinn_trg_neg[j]+sumsinn_trg_neg[i]*sumcosn_trg_neg[j]);
      Qabxx_nn[j-i] += (sumcosn_trg_neg[i]*sumcosn_trg_neg[j]+sumsinn_trg_neg[i]*sumsinn_trg_neg[j]);
      nabpairs_nn[j-i] += npairs_trg_neg[i]*npairs_trg_neg[j];
      if(j==i)
      {
        Qabx_nn[j-i] -= sumcos2n_trg_neg[i];
        Qaby_nn[j-i] -= sumsin2n_trg_neg[i];
        Qabxx_nn[j-i] -= npairs_trg_neg[i];
        nabpairs_nn[j-i] -= npairs_trg_neg[i];
      }

      Qabx_pn[j-i] += (sumcosn_trg_pos[i]*sumcosn_trg_neg[j]-sumsinn_trg_pos[i]*sumsinn_trg_neg[j]);
      Qaby_pn[j-i] += (sumcosn_trg_pos[i]*sumsinn_trg_neg[j]+sumsinn_trg_pos[i]*sumcosn_trg_neg[j]);
      Qabxx_pn[j-i] += (sumcosn_trg_pos[i]*sumcosn_trg_neg[j]+sumsinn_trg_pos[i]*sumsinn_trg_neg[j]);
      nabpairs_pn[j-i] += npairs_trg_pos[i]*npairs_trg_neg[j];

      Qabx_np[j-i] += (sumcosn_trg_neg[i]*sumcosn_trg_pos[j]-sumsinn_trg_neg[i]*sumsinn_trg_pos[j]);
      Qaby_np[j-i] += (sumcosn_trg_neg[i]*sumsinn_trg_pos[j]+sumsinn_trg_neg[i]*sumcosn_trg_pos[j]);
      Qabxx_np[j-i] += (sumcosn_trg_neg[i]*sumcosn_trg_pos[j]+sumsinn_trg_neg[i]*sumsinn_trg_pos[j]);
      nabpairs_np[j-i] += npairs_trg_neg[i]*npairs_trg_pos[j];
    }

  for(int i=0;i<MAXETATRGBINSPT;i++)
  {
    double etabin = 4.8/MAXETATRGBINSPT*i;
 
    double Qabc_same_for = (Qabx_pp[i]+Qabx_nn[i])/(nabpairs_pp[i]+nabpairs_nn[i])*sumcosn_ass_for+(Qaby_pp[i]+Qaby_nn[i])/(nabpairs_pp[i]+nabpairs_nn[i])*sumsinn_ass_for;
    double Qabc_same_bak = (Qabx_pp[i]+Qabx_nn[i])/(nabpairs_pp[i]+nabpairs_nn[i])*sumcosn_ass_bak+(Qaby_pp[i]+Qaby_nn[i])/(nabpairs_pp[i]+nabpairs_nn[i])*sumsinn_ass_bak;          hSignalCos_same_for->Fill(Qabc_same_for,etabin);
    hSignalCos_same_bak->Fill(Qabc_same_bak,etabin);
    hSignalCos2PcorrP_same->Fill((Qabx_pp[i]+Qabx_nn[i])/(nabpairs_pp[i]+nabpairs_nn[i]),etabin);
    hSignalCos2PcorrM_same->Fill((Qabxx_pp[i]+Qabxx_nn[i])/(nabpairs_pp[i]+nabpairs_nn[i]),etabin);
    hSignalNpairs_same->Fill(nabpairs_pp[i]+nabpairs_nn[i],etabin);

    double Qabc_diff_for = (Qabx_pn[i]+Qabx_np[i])/(nabpairs_pn[i]+nabpairs_np[i])*sumcosn_ass_for+(Qaby_pn[i]+Qaby_np[i])/(nabpairs_pn[i]+nabpairs_np[i])*sumsinn_ass_for;
    double Qabc_diff_bak = (Qabx_pn[i]+Qabx_np[i])/(nabpairs_pn[i]+nabpairs_np[i])*sumcosn_ass_bak+(Qaby_pn[i]+Qaby_np[i])/(nabpairs_pn[i]+nabpairs_np[i])*sumsinn_ass_bak;
    hSignalCos_diff_for->Fill(Qabc_diff_for,etabin);
    hSignalCos_diff_bak->Fill(Qabc_diff_bak,etabin);
    hSignalCos2PcorrP_diff->Fill((Qabx_pn[i]+Qabx_np[i])/(nabpairs_pn[i]+nabpairs_np[i]),etabin);
    hSignalCos2PcorrM_diff->Fill((Qabxx_pn[i]+Qabxx_np[i])/(nabpairs_pn[i]+nabpairs_np[i]),etabin);
    hSignalNpairs_diff->Fill(nabpairs_pn[i]+nabpairs_np[i],etabin);
  }
}
