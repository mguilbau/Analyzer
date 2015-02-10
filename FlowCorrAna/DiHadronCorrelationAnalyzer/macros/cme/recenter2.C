void recenter2()
{
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_eff0_bin03_v26.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/chargedepcorr_recenter_n220260_pttrg033_ptassallweight_etaass445_reverse_eff1_v13.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_20/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/chargedepcorr_recenter.root");

  const int ntrg = 1;
  const int MAXETATRGBINSPT = 24;
//  TString dirname("chargedepcorr_ana_HI");
  TString dirname("chargedepcorr_ana_pPb");

  double small = 0.000;
  std::vector<double> multBins;

  for(double mult = 0; mult < 20; mult += 1) multBins.push_back(mult);
  for(double mult = 20; mult < 40; mult += 4) multBins.push_back(mult);
  for(double mult = 40; mult < 100; mult += 10) multBins.push_back(mult);
  for(double mult = 100; mult < 200; mult += 20) multBins.push_back(mult);
  for(double mult = 200; mult < 400; mult += 50) multBins.push_back(mult);

  float etaWidth =  0.2;
  float etaMin   = -2.4-etaWidth;
  float etaMax   =  2.4+etaWidth;
  
  std::vector<double> etaBins;
  for(double eta = etaMin; eta < etaMax + etaWidth/2; eta += etaWidth)
    etaBins.push_back(eta);

  TH2D* hSumNCosTrgPos[ntrg];
  TH2D* hSumNCosTrgNeg[ntrg];
  TH2D* hSumNSinTrgPos[ntrg];
  TH2D* hSumNSinTrgNeg[ntrg];
  TH2D* hSumNCos2TrgPos[ntrg];
  TH2D* hSumNCos2TrgNeg[ntrg];
  TH2D* hSumNSin2TrgPos[ntrg];
  TH2D* hSumNSin2TrgNeg[ntrg];
  TH2D* hSumCosTrgPos[MAXETATRGBINSPT][ntrg];
  TH2D* hSumSinTrgPos[MAXETATRGBINSPT][ntrg];
  TH2D* hSumCosTrgNeg[MAXETATRGBINSPT][ntrg];
  TH2D* hSumSinTrgNeg[MAXETATRGBINSPT][ntrg];
  TH2D* hSumCos2TrgPos[MAXETATRGBINSPT][ntrg];
  TH2D* hSumSin2TrgPos[MAXETATRGBINSPT][ntrg];
  TH2D* hSumCos2TrgNeg[MAXETATRGBINSPT][ntrg];
  TH2D* hSumSin2TrgNeg[MAXETATRGBINSPT][ntrg]; 

  TH1D* hSumAssFor = (TH1D*)f->Get(Form("%s/sumassfor",dirname.Data()));
  TH1D* hSumAssBak = (TH1D*)f->Get(Form("%s/sumassbak",dirname.Data()));
  TH1D* hSumCosAssFor = (TH1D*)f->Get(Form("%s/sumcosassfor",dirname.Data())); 
  TH1D* hSumSinAssFor = (TH1D*)f->Get(Form("%s/sumsinassfor",dirname.Data())); 
  TH1D* hSumCosAssBak = (TH1D*)f->Get(Form("%s/sumcosassbak",dirname.Data())); 
  TH1D* hSumSinAssBak = (TH1D*)f->Get(Form("%s/sumsinassbak",dirname.Data())); 
  TH1D* hSumCos2AssFor = (TH1D*)f->Get(Form("%s/sumcos2assfor",dirname.Data()));
  TH1D* hSumSin2AssFor = (TH1D*)f->Get(Form("%s/sumsin2assfor",dirname.Data()));
  TH1D* hSumCos2AssBak = (TH1D*)f->Get(Form("%s/sumcos2assbak",dirname.Data()));
  TH1D* hSumSin2AssBak = (TH1D*)f->Get(Form("%s/sumsin2assbak",dirname.Data()));

  for(int itrg=0;itrg<ntrg;itrg++)
  {
/*
    hSumNCosTrgPos[itrg] = new TH2D(Form("sumncostrgpos_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
    hSumNCosTrgNeg[itrg] = new TH2D(Form("sumncostrgneg_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
    hSumNSinTrgPos[itrg] = new TH2D(Form("sumnsintrgpos_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
    hSumNSinTrgNeg[itrg] = new TH2D(Form("sumnsintrgneg_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
    hSumNCos2TrgPos[itrg] = new TH2D(Form("sumncos2trgpos_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
    hSumNCos2TrgNeg[itrg] = new TH2D(Form("sumncos2trgneg_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
    hSumNSin2TrgPos[itrg] = new TH2D(Form("sumnsin2trgpos_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
    hSumNSin2TrgNeg[itrg] = new TH2D(Form("sumnsin2trgneg_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
*/
    hSumNCosTrgPos[itrg] = new TH2D(Form("sumncostrgpos_pt%d",itrg),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNCosTrgNeg[itrg] = new TH2D(Form("sumncostrgneg_pt%d",itrg),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNSinTrgPos[itrg] = new TH2D(Form("sumnsintrgpos_pt%d",itrg),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNSinTrgNeg[itrg] = new TH2D(Form("sumnsintrgneg_pt%d",itrg),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNCos2TrgPos[itrg] = new TH2D(Form("sumncos2trgpos_pt%d",itrg),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNCos2TrgNeg[itrg] = new TH2D(Form("sumncos2trgneg_pt%d",itrg),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNSin2TrgPos[itrg] = new TH2D(Form("sumnsin2trgpos_pt%d",itrg),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNSin2TrgNeg[itrg] = new TH2D(Form("sumnsin2trgneg_pt%d",itrg),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);

    for(int ll=0;ll<MAXETATRGBINSPT;ll++)
    {
      hSumCosTrgPos[ll][itrg] = (TH2D*)f->Get(Form("%s/sumcostrgpos_eta%d_pt%d",dirname.Data(),ll,itrg));  
      hSumSinTrgPos[ll][itrg] = (TH2D*)f->Get(Form("%s/sumsintrgpos_eta%d_pt%d",dirname.Data(),ll,itrg));
      hSumCosTrgNeg[ll][itrg] = (TH2D*)f->Get(Form("%s/sumcostrgneg_eta%d_pt%d",dirname.Data(),ll,itrg));
      hSumSinTrgNeg[ll][itrg] = (TH2D*)f->Get(Form("%s/sumsintrgneg_eta%d_pt%d",dirname.Data(),ll,itrg));
      hSumCos2TrgPos[ll][itrg] = (TH2D*)f->Get(Form("%s/sumcos2trgpos_eta%d_pt%d",dirname.Data(),ll,itrg));  
      hSumSin2TrgPos[ll][itrg] = (TH2D*)f->Get(Form("%s/sumsin2trgpos_eta%d_pt%d",dirname.Data(),ll,itrg));
      hSumCos2TrgNeg[ll][itrg] = (TH2D*)f->Get(Form("%s/sumcos2trgneg_eta%d_pt%d",dirname.Data(),ll,itrg));
      hSumSin2TrgNeg[ll][itrg] = (TH2D*)f->Get(Form("%s/sumsin2trgneg_eta%d_pt%d",dirname.Data(),ll,itrg));

      for(int jj=1;jj<multBins.size();jj++)
      {
        int binmin = hSumCosTrgPos[ll][itrg]->GetYaxis()->FindBin(multBins[jj-1]+0.0001);
        int binmax = hSumCosTrgPos[ll][itrg]->GetYaxis()->FindBin(multBins[jj]+0.0001);

        TH1D* hSumCosTrgPos_prof = (TH1D*)hSumCosTrgPos[ll][itrg]->ProjectionX("cospos",binmin,binmax-1,"e");
        TH1D* hSumSinTrgPos_prof = (TH1D*)hSumSinTrgPos[ll][itrg]->ProjectionX("sinpos",binmin,binmax-1,"e");
        TH1D* hSumCosTrgNeg_prof = (TH1D*)hSumCosTrgNeg[ll][itrg]->ProjectionX("cosneg",binmin,binmax-1,"e");
        TH1D* hSumSinTrgNeg_prof = (TH1D*)hSumSinTrgNeg[ll][itrg]->ProjectionX("sinneg",binmin,binmax-1,"e");
        TH1D* hSumCos2TrgPos_prof = (TH1D*)hSumCos2TrgPos[ll][itrg]->ProjectionX("cos2pos",binmin,binmax-1,"e");
        TH1D* hSumSin2TrgPos_prof = (TH1D*)hSumSin2TrgPos[ll][itrg]->ProjectionX("sin2pos",binmin,binmax-1,"e");
        TH1D* hSumCos2TrgNeg_prof = (TH1D*)hSumCos2TrgNeg[ll][itrg]->ProjectionX("cos2neg",binmin,binmax-1,"e");
        TH1D* hSumSin2TrgNeg_prof = (TH1D*)hSumSin2TrgNeg[ll][itrg]->ProjectionX("sin2neg",binmin,binmax-1,"e");
     
if(ll==8) cout<<binmin<<" "<<binmax<<" "<<hSumCosTrgPos_prof->GetMean()<<" "<<hSumCosTrgPos_prof->GetMeanError()<<endl;

        hSumNCosTrgPos[itrg]->SetBinContent(ll+2,jj,hSumCosTrgPos_prof->GetMean());
        hSumNCosTrgPos[itrg]->SetBinError(ll+2,jj,hSumCosTrgPos_prof->GetMeanError());
        hSumNSinTrgPos[itrg]->SetBinContent(ll+2,jj,hSumSinTrgPos_prof->GetMean());
        hSumNSinTrgPos[itrg]->SetBinError(ll+2,jj,hSumSinTrgPos_prof->GetMeanError()); 
        hSumNCosTrgNeg[itrg]->SetBinContent(ll+2,jj,hSumCosTrgNeg_prof->GetMean());
        hSumNCosTrgNeg[itrg]->SetBinError(ll+2,jj,hSumCosTrgNeg_prof->GetMeanError()); 
        hSumNSinTrgNeg[itrg]->SetBinContent(ll+2,jj,hSumSinTrgNeg_prof->GetMean());
        hSumNSinTrgNeg[itrg]->SetBinError(ll+2,jj,hSumSinTrgNeg_prof->GetMeanError());
        hSumNCos2TrgPos[itrg]->SetBinContent(ll+2,jj,hSumCos2TrgPos_prof->GetMean());
        hSumNCos2TrgPos[itrg]->SetBinError(ll+2,jj,hSumCos2TrgPos_prof->GetMeanError()); 
        hSumNSin2TrgPos[itrg]->SetBinContent(ll+2,jj,hSumSin2TrgPos_prof->GetMean());
        hSumNSin2TrgPos[itrg]->SetBinError(ll+2,jj,hSumSin2TrgPos_prof->GetMeanError());
        hSumNCos2TrgNeg[itrg]->SetBinContent(ll+2,jj,hSumCos2TrgNeg_prof->GetMean());
        hSumNCos2TrgNeg[itrg]->SetBinError(ll+2,jj,hSumCos2TrgNeg_prof->GetMeanError());
        hSumNSin2TrgNeg[itrg]->SetBinContent(ll+2,jj,hSumSin2TrgNeg_prof->GetMean());
        hSumNSin2TrgNeg[itrg]->SetBinError(ll+2,jj,hSumSin2TrgNeg_prof->GetMeanError());
      }
    }
  }

  TH2D* dNdetadphi_pos = (TH2D*)f->Get("chargedepcorr_ana_HI/dndetadphipos");
  TH2D* dNdetadphi_neg = (TH2D*)f->Get("chargedepcorr_ana_HI/dndetadphineg");

  TH1D* dNdphi_pos[24];
  TH1D* dNdphi_neg[24];

  for(int i=0;i<24;i++)
  {
    dNdphi_pos[i] = (TH1D*)dNdetadphi_pos->ProjectionY(Form("dNdphi_pos_%d",i+1),i+1,i+1,"e");
    dNdphi_neg[i] = (TH1D*)dNdetadphi_neg->ProjectionY(Form("dNdphi_neg_%d",i+1),i+1,i+1,"e");
  }

  TCanvas* c = new TCanvas("c","c",1100,900);
  c->Divide(6,4);

  TCanvas* c1 = new TCanvas("c1","c1",1100,900);
  c1->Divide(6,4);

  for(int i=0;i<24;i++)
  {
    c->cd(i+1);
    dNdphi_pos[i]->Rebin(8);
    dNdphi_pos[i]->Scale(1.0/dNdphi_pos[i]->Integral()*dNdphi_pos[i]->GetNbinsX());
    dNdphi_pos[i]->SetMinimum(0);
    dNdphi_pos[i]->SetMaximum(1.2);
    dNdphi_pos[i]->Draw();
    c1->cd(i+1);
    dNdphi_neg[i]->Rebin(8);
    dNdphi_neg[i]->Scale(1.0/dNdphi_neg[i]->Integral()*dNdphi_neg[i]->GetNbinsX());
    dNdphi_neg[i]->SetMinimum(0);
    dNdphi_neg[i]->SetMaximum(1.2);
    dNdphi_neg[i]->Draw();
  }

  TFile* fout = new TFile("crosscheck_cent4050_pttrg033_etaass445_eff0_bin02.root","recreate");
  for(int itrg=0;itrg<ntrg;itrg++)
  {
    hSumNCosTrgPos[itrg]->Write();
    hSumNCosTrgNeg[itrg]->Write();
    hSumNSinTrgPos[itrg]->Write();
    hSumNSinTrgNeg[itrg]->Write();
    hSumNCos2TrgPos[itrg]->Write();
    hSumNCos2TrgNeg[itrg]->Write();
    hSumNSin2TrgPos[itrg]->Write();
    hSumNSin2TrgNeg[itrg]->Write();
  }
  fout->Close();
}
