void recenter()
{
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_eff0_bin03_v20.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_20/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/chargedepcorr_recenter.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/chargedepcorr_recenter_mc_cent080_pttrg033_ptassallweight_etaass445_eff0_v16.root");

  const int ntrg = 1;
  const int MAXETATRGBINSPT = 16;
  TString dirname("chargedepcorr_ana_HI");

  TH1D* hSumNTrgPos[ntrg];
  TH1D* hSumNTrgNeg[ntrg];
  TH1D* hSumNCosTrgPos[ntrg];
  TH1D* hSumNCosTrgNeg[ntrg];
  TH1D* hSumNSinTrgPos[ntrg];
  TH1D* hSumNSinTrgNeg[ntrg];
  TH1D* hSumNCos2TrgPos[ntrg];
  TH1D* hSumNCos2TrgNeg[ntrg];
  TH1D* hSumNSin2TrgPos[ntrg];
  TH1D* hSumNSin2TrgNeg[ntrg];
  TH1D* hSumTrgPos[MAXETATRGBINSPT][ntrg];
  TH1D* hSumTrgNeg[MAXETATRGBINSPT][ntrg];
  TH1D* hSumCosTrgPos[MAXETATRGBINSPT][ntrg];
  TH1D* hSumSinTrgPos[MAXETATRGBINSPT][ntrg];
  TH1D* hSumCosTrgNeg[MAXETATRGBINSPT][ntrg];
  TH1D* hSumSinTrgNeg[MAXETATRGBINSPT][ntrg];
  TH1D* hSumCos2TrgPos[MAXETATRGBINSPT][ntrg];
  TH1D* hSumSin2TrgPos[MAXETATRGBINSPT][ntrg];
  TH1D* hSumCos2TrgNeg[MAXETATRGBINSPT][ntrg];
  TH1D* hSumSin2TrgNeg[MAXETATRGBINSPT][ntrg]; 

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
    hSumNTrgPos[itrg] = new TH1D(Form("sumntrgpos_pt%d",itrg),";#eta",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT);
    hSumNTrgNeg[itrg] = new TH1D(Form("sumntrgneg_pt%d",itrg),";#eta",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT);
    hSumNCosTrgPos[itrg] = new TH1D(Form("sumncostrgpos_pt%d",itrg),";#eta",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT);
    hSumNCosTrgNeg[itrg] = new TH1D(Form("sumncostrgneg_pt%d",itrg),";#eta",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT);
    hSumNSinTrgPos[itrg] = new TH1D(Form("sumnsintrgpos_pt%d",itrg),";#eta",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT);
    hSumNSinTrgNeg[itrg] = new TH1D(Form("sumnsintrgneg_pt%d",itrg),";#eta",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT);
    hSumNCos2TrgPos[itrg] = new TH1D(Form("sumncos2trgpos_pt%d",itrg),";#eta",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT);
    hSumNCos2TrgNeg[itrg] = new TH1D(Form("sumncos2trgneg_pt%d",itrg),";#eta",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT);
    hSumNSin2TrgPos[itrg] = new TH1D(Form("sumnsin2trgpos_pt%d",itrg),";#eta",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT);
    hSumNSin2TrgNeg[itrg] = new TH1D(Form("sumnsin2trgneg_pt%d",itrg),";#eta",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT);

    for(int ll=0;ll<MAXETATRGBINSPT;ll++)
    {
      hSumTrgPos[ll][itrg] = (TH1D*)f->Get(Form("%s/sumtrgpos_eta%d_pt%d",dirname.Data(),ll,itrg));
      hSumTrgNeg[ll][itrg] = (TH1D*)f->Get(Form("%s/sumtrgneg_eta%d_pt%d",dirname.Data(),ll,itrg));
      hSumCosTrgPos[ll][itrg] = (TH1D*)f->Get(Form("%s/sumcostrgpos_eta%d_pt%d",dirname.Data(),ll,itrg));  
      hSumSinTrgPos[ll][itrg] = (TH1D*)f->Get(Form("%s/sumsintrgpos_eta%d_pt%d",dirname.Data(),ll,itrg));
      hSumCosTrgNeg[ll][itrg] = (TH1D*)f->Get(Form("%s/sumcostrgneg_eta%d_pt%d",dirname.Data(),ll,itrg));
      hSumSinTrgNeg[ll][itrg] = (TH1D*)f->Get(Form("%s/sumsintrgneg_eta%d_pt%d",dirname.Data(),ll,itrg));
      hSumCos2TrgPos[ll][itrg] = (TH1D*)f->Get(Form("%s/sumcos2trgpos_eta%d_pt%d",dirname.Data(),ll,itrg));  
      hSumSin2TrgPos[ll][itrg] = (TH1D*)f->Get(Form("%s/sumsin2trgpos_eta%d_pt%d",dirname.Data(),ll,itrg));
      hSumCos2TrgNeg[ll][itrg] = (TH1D*)f->Get(Form("%s/sumcos2trgneg_eta%d_pt%d",dirname.Data(),ll,itrg));
      hSumSin2TrgNeg[ll][itrg] = (TH1D*)f->Get(Form("%s/sumsin2trgneg_eta%d_pt%d",dirname.Data(),ll,itrg));

      hSumNTrgPos[itrg]->SetBinContent(ll+2,hSumTrgPos[ll][itrg]->GetMean());
      hSumNTrgPos[itrg]->SetBinError(ll+2,hSumTrgPos[ll][itrg]->GetMeanError());
      hSumNTrgNeg[itrg]->SetBinContent(ll+2,hSumTrgNeg[ll][itrg]->GetMean());
      hSumNTrgNeg[itrg]->SetBinError(ll+2,hSumTrgNeg[ll][itrg]->GetMeanError());
      hSumNCosTrgPos[itrg]->SetBinContent(ll+2,hSumCosTrgPos[ll][itrg]->GetMean());
      hSumNCosTrgPos[itrg]->SetBinError(ll+2,hSumCosTrgPos[ll][itrg]->GetMeanError());
      hSumNSinTrgPos[itrg]->SetBinContent(ll+2,hSumSinTrgPos[ll][itrg]->GetMean());
      hSumNSinTrgPos[itrg]->SetBinError(ll+2,hSumSinTrgPos[ll][itrg]->GetMeanError());
      hSumNCosTrgNeg[itrg]->SetBinContent(ll+2,hSumCosTrgNeg[ll][itrg]->GetMean());
      hSumNCosTrgNeg[itrg]->SetBinError(ll+2,hSumCosTrgNeg[ll][itrg]->GetMeanError());
      hSumNSinTrgNeg[itrg]->SetBinContent(ll+2,hSumSinTrgNeg[ll][itrg]->GetMean());
      hSumNSinTrgNeg[itrg]->SetBinError(ll+2,hSumSinTrgNeg[ll][itrg]->GetMeanError());
      hSumNCos2TrgPos[itrg]->SetBinContent(ll+2,hSumCos2TrgPos[ll][itrg]->GetMean());
      hSumNCos2TrgPos[itrg]->SetBinError(ll+2,hSumCos2TrgPos[ll][itrg]->GetMeanError());
      hSumNSin2TrgPos[itrg]->SetBinContent(ll+2,hSumSin2TrgPos[ll][itrg]->GetMean());
      hSumNSin2TrgPos[itrg]->SetBinError(ll+2,hSumSin2TrgPos[ll][itrg]->GetMeanError());
      hSumNCos2TrgNeg[itrg]->SetBinContent(ll+2,hSumCos2TrgNeg[ll][itrg]->GetMean());
      hSumNCos2TrgNeg[itrg]->SetBinError(ll+2,hSumCos2TrgNeg[ll][itrg]->GetMeanError());
      hSumNSin2TrgNeg[itrg]->SetBinContent(ll+2,hSumSin2TrgNeg[ll][itrg]->GetMean());
      hSumNSin2TrgNeg[itrg]->SetBinError(ll+2,hSumSin2TrgNeg[ll][itrg]->GetMeanError());      
    }
    hSumNTrgPos[itrg]->SetBinContent(1,hSumAssFor->GetMean());
    hSumNTrgPos[itrg]->SetBinError(1,hSumAssFor->GetMeanError());
    hSumNTrgNeg[itrg]->SetBinContent(1,hSumAssFor->GetMean());
    hSumNTrgNeg[itrg]->SetBinError(1,hSumAssFor->GetMeanError());
    hSumNTrgPos[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumAssBak->GetMean());
    hSumNTrgPos[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumAssBak->GetMeanError());
    hSumNTrgNeg[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumAssBak->GetMean());
    hSumNTrgNeg[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumAssBak->GetMeanError());
    hSumNCosTrgPos[itrg]->SetBinContent(1,hSumCosAssFor->GetMean());
    hSumNCosTrgPos[itrg]->SetBinError(1,hSumCosAssFor->GetMeanError());
    hSumNCosTrgPos[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumCosAssBak->GetMean());
    hSumNCosTrgPos[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumCosAssBak->GetMeanError());
    hSumNSinTrgPos[itrg]->SetBinContent(1,hSumSinAssFor->GetMean());
    hSumNSinTrgPos[itrg]->SetBinError(1,hSumSinAssFor->GetMeanError());
    hSumNSinTrgPos[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumSinAssBak->GetMean());
    hSumNSinTrgPos[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumSinAssBak->GetMeanError());
    hSumNCosTrgNeg[itrg]->SetBinContent(1,hSumCosAssFor->GetMean());
    hSumNCosTrgNeg[itrg]->SetBinError(1,hSumCosAssFor->GetMeanError());
    hSumNCosTrgNeg[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumCosAssBak->GetMean());
    hSumNCosTrgNeg[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumCosAssBak->GetMeanError());
    hSumNSinTrgNeg[itrg]->SetBinContent(1,hSumSinAssFor->GetMean());
    hSumNSinTrgNeg[itrg]->SetBinError(1,hSumSinAssFor->GetMeanError());
    hSumNSinTrgNeg[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumSinAssBak->GetMean());
    hSumNSinTrgNeg[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumSinAssBak->GetMeanError());
    hSumNCos2TrgPos[itrg]->SetBinContent(1,hSumCos2AssFor->GetMean());
    hSumNCos2TrgPos[itrg]->SetBinError(1,hSumCos2AssFor->GetMeanError());
    hSumNCos2TrgPos[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumCos2AssBak->GetMean());
    hSumNCos2TrgPos[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumCos2AssBak->GetMeanError());
    hSumNSin2TrgPos[itrg]->SetBinContent(1,hSumSin2AssFor->GetMean());
    hSumNSin2TrgPos[itrg]->SetBinError(1,hSumSin2AssFor->GetMeanError());
    hSumNSin2TrgPos[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumSin2AssBak->GetMean());
    hSumNSin2TrgPos[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumSin2AssBak->GetMeanError());
    hSumNCos2TrgNeg[itrg]->SetBinContent(1,hSumCos2AssFor->GetMean());
    hSumNCos2TrgNeg[itrg]->SetBinError(1,hSumCos2AssFor->GetMeanError());
    hSumNCos2TrgNeg[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumCos2AssBak->GetMean());
    hSumNCos2TrgNeg[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumCos2AssBak->GetMeanError());
    hSumNSin2TrgNeg[itrg]->SetBinContent(1,hSumSin2AssFor->GetMean());
    hSumNSin2TrgNeg[itrg]->SetBinError(1,hSumSin2AssFor->GetMeanError());
    hSumNSin2TrgNeg[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumSin2AssBak->GetMean());
    hSumNSin2TrgNeg[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumSin2AssBak->GetMeanError());
  }
return;
  TFile* fout = new TFile("recenter_cent4050_pttrg033_etaass445_eff0_bin03.root","recreate");
//  TFile* fout = new TFile("recenter_mc_cent080_pttrg033_etaass445_eff0_bin03.root","recreate");
  for(int itrg=0;itrg<ntrg;itrg++)
  {
    hSumNTrgPos[itrg]->Write();
    hSumNTrgNeg[itrg]->Write();
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
