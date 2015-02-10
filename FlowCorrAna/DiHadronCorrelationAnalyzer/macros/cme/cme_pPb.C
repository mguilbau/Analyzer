void cme(TString filename, TH1D* h[10])
{
  TH1D* h[10];
/*
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/chargedepcorr_n185220_pttrg033_ptassallweight_etaass445_reverse_eff1_v9.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_20/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/chargedepcorr.root");
  TH2D* hsame = (TH2D*)f->Get("chargedepcorr_ana_pPb/signalcos_same_trg0_ass0");
  TH2D* hdiff = (TH2D*)f->Get("chargedepcorr_ana_pPb/signalcos_diff_trg0_ass0");
  TH1D* hq2 = (TH1D*)f->Get("chargedepcorr_ana_pPb/q2asscos");
*/
/*
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_n185260_pttrg033_ptassallweight_eff1_v8.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_20/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/chargedepcorr.root");
  TH2D* hsame = (TH2D*)f->Get("chargedepcorr_ana/signalcos_same_trg0_ass0");
  TH2D* hdiff = (TH2D*)f->Get("chargedepcorr_ana/signalcos_diff_trg0_ass0");
  TH1D* hq2 = (TH1D*)f->Get("chargedepcorr_ana/q2asscos");
*/

//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/chargedepcorr_mc_cent080_pttrg033_ptassallweight_etaass445_norecenter_eff0_v16.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/chargedepcorr_mc_cent080_pttrg033_ptassallweight_etaass445_eff0_v17.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_onlyrecenter_noHF_eff0_bin03_v16.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_20/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/chargedepcorr.root");

  TFile* f = new TFile(filename.Data());

  TH2D* hsame_bak = (TH2D*)f->Get("chargedepcorr_ana_pPb/signalcos_same_bak_trg0_ass0");
  TH2D* hdiff_bak = (TH2D*)f->Get("chargedepcorr_ana_pPb/signalcos_diff_bak_trg0_ass0");
  TH2D* hsame_for = (TH2D*)f->Get("chargedepcorr_ana_pPb/signalcos_same_for_trg0_ass0");
  TH2D* hdiff_for = (TH2D*)f->Get("chargedepcorr_ana_pPb/signalcos_diff_for_trg0_ass0");

  TH2D* hsame_2pcorrp = (TH2D*)f->Get("chargedepcorr_ana_pPb/signalcos2pcorrp_same_trg0_ass0");
  TH2D* hsame_2pcorrm = (TH2D*)f->Get("chargedepcorr_ana_pPb/signalcos2pcorrm_same_trg0_ass0");
  TH2D* hdiff_2pcorrp = (TH2D*)f->Get("chargedepcorr_ana_pPb/signalcos2pcorrp_diff_trg0_ass0");
  TH2D* hdiff_2pcorrm = (TH2D*)f->Get("chargedepcorr_ana_pPb/signalcos2pcorrm_diff_trg0_ass0");

  TH2D* hsame = (TH2D*)hsame_bak->Clone("hsame");
  hsame->Add(hsame_for);
  TH2D* hdiff = (TH2D*)hdiff_bak->Clone("hsame");
  hdiff->Add(hdiff_for);

  TH1D* hq2 = (TH1D*)f->Get("chargedepcorr_ana_pPb/q2asscos");
//  TH1D* hnpos = (TH1D*)f->Get("chargedepcorr_ana_HI/sumntrgpos_pt0");
//  TH1D* hnneg = (TH1D*)f->Get("chargedepcorr_ana_HI/sumntrgneg_pt0");
/*
  hsame_bak->Rebin2D(1,2);
  hdiff_bak->Rebin2D(1,2);
  hsame_for->Rebin2D(1,2);
  hdiff_for->Rebin2D(1,2);
  hsame->Rebin2D(1,2);
  hdiff->Rebin2D(1,2);
*/
//  hnsame->Rebin(2);
//  hndiff->Rebin(2);
/*
  TH1D* hcospos[24];
  TH1D* hsinpos[24];
  TH1D* hcosneg[24];
  TH1D* hsinneg[24];
  for(int i=0;i<24;i++)
  {
    hcospos[i] = f->Get(Form("chargedepcorr_ana_HI/sumcostrgpos_cen_eta%d_pt0",i));
    hsinpos[i] = f->Get(Form("chargedepcorr_ana_HI/sumsintrgpos_cen_eta%d_pt0",i));
    hcosneg[i] = f->Get(Form("chargedepcorr_ana_HI/sumcostrgneg_cen_eta%d_pt0",i));
    hsinneg[i] = f->Get(Form("chargedepcorr_ana_HI/sumsintrgneg_cen_eta%d_pt0",i));
  }
*/

  TH1D* hsame_2pcorrp_prof = (TH1D*)hsame_2pcorrp->ProfileY("hsame_2pcorrp_prof",-1,-1,"e");
  TH1D* hsame_2pcorrm_prof = (TH1D*)hsame_2pcorrm->ProfileY("hsame_2pcorrm_prof",-1,-1,"e");
  TH1D* hdiff_2pcorrp_prof = (TH1D*)hdiff_2pcorrp->ProfileY("hdiff_2pcorrp_prof",-1,-1,"e");
  TH1D* hdiff_2pcorrm_prof = (TH1D*)hdiff_2pcorrm->ProfileY("hdiff_2pcorrm_prof",-1,-1,"e");

  TH1D* hsame_proj_for = (TH1D*)hsame_for->ProjectionY("hsame_proj_for",-1,-1,"e");
  TH1D* hdiff_proj_for = (TH1D*)hdiff_for->ProjectionY("hdiff_proj_for",-1,-1,"e");
  hsame_proj_for->Reset();
  hdiff_proj_for->Reset();

  TH1D* hsame_proj_bak = (TH1D*)hsame_bak->ProjectionY("hsame_proj_bak",-1,-1,"e");
  TH1D* hdiff_proj_bak = (TH1D*)hdiff_bak->ProjectionY("hdiff_proj_bak",-1,-1,"e");
  hsame_proj_bak->Reset();
  hdiff_proj_bak->Reset();
 
  TH1D* hsame_proj = (TH1D*)hsame->ProjectionY("hsame_proj",-1,-1,"e");
  TH1D* hdiff_proj = (TH1D*)hdiff->ProjectionY("hdiff_proj",-1,-1,"e");
  hsame_proj->Reset();
  hdiff_proj->Reset();

  for(int i=1;i<=hsame_proj_for->GetNbinsX();i++)
  {
    TH1D* hsame_proj_for_tmp = (TH1D*)hsame_for->ProjectionX("hsame_proj_for_tmp",i,i,"e");
    TH1D* hdiff_proj_for_tmp = (TH1D*)hdiff_for->ProjectionX("hdiff_proj_for_tmp",i,i,"e");

    double value = hsame_proj_for_tmp->GetMean()/sqrt(hq2->GetMean());
    double value_err = hsame_proj_for_tmp->GetMeanError()/sqrt(hq2->GetMean());
    hsame_proj_for->SetBinContent(i,value);
    hsame_proj_for->SetBinError(i,value_err);

    value = hdiff_proj_for_tmp->GetMean()/sqrt(hq2->GetMean());
    value_err = hdiff_proj_for_tmp->GetMeanError()/sqrt(hq2->GetMean());
    hdiff_proj_for->SetBinContent(i,value);
    hdiff_proj_for->SetBinError(i,value_err);

    TH1D* hsame_proj_bak_tmp = (TH1D*)hsame_bak->ProjectionX("hsame_proj_bak_tmp",i,i,"e");
    TH1D* hdiff_proj_bak_tmp = (TH1D*)hdiff_bak->ProjectionX("hdiff_proj_bak_tmp",i,i,"e");

    value = hsame_proj_bak_tmp->GetMean()/sqrt(hq2->GetMean());
    value_err = hsame_proj_bak_tmp->GetMeanError()/sqrt(hq2->GetMean());
    hsame_proj_bak->SetBinContent(i,value);
    hsame_proj_bak->SetBinError(i,value_err);

    value = hdiff_proj_bak_tmp->GetMean()/sqrt(hq2->GetMean());
    value_err = hdiff_proj_bak_tmp->GetMeanError()/sqrt(hq2->GetMean());
    hdiff_proj_bak->SetBinContent(i,value);
    hdiff_proj_bak->SetBinError(i,value_err);

    TH1D* hsame_proj_tmp = (TH1D*)hsame->ProjectionX("hsame_proj_tmp",i,i,"e");
    TH1D* hdiff_proj_tmp = (TH1D*)hdiff->ProjectionX("hdiff_proj_tmp",i,i,"e");

    value = hsame_proj_tmp->GetMean()/sqrt(hq2->GetMean());
    value_err = hsame_proj_tmp->GetMeanError()/sqrt(hq2->GetMean());
    hsame_proj->SetBinContent(i,value);
    hsame_proj->SetBinError(i,value_err);

    value = hdiff_proj_tmp->GetMean()/sqrt(hq2->GetMean());
    value_err = hdiff_proj_tmp->GetMeanError()/sqrt(hq2->GetMean());
    hdiff_proj->SetBinContent(i,value);
    hdiff_proj->SetBinError(i,value_err);
  }
 
  delete hsame_bak;
  delete hdiff_bak;
  delete hsame_for;
  delete hdiff_for;
  delete hsame;
  delete hdiff;

  h[0] = hsame_proj_for;
  h[1] = hsame_proj_bak;
  h[2] = hsame_proj;
  h[3] = hdiff_proj_for;
  h[4] = hdiff_proj_bak;
  h[5] = hdiff_proj;
  h[6] = hsame_2pcorrp_prof;
  h[7] = hsame_2pcorrm_prof;
  h[8] = hdiff_2pcorrp_prof;
  h[9] = hdiff_2pcorrm_prof; 

//  return h;
/*
 if(index==10) return hsame_proj_for;
 if(index==11) return hsame_proj_bak;
 if(index==12) return hsame_proj;
 if(index==00) return hdiff_proj_for;
 if(index==01) return hdiff_proj_bak;
 if(index==02) return hdiff_proj;
*/
/*
  TH2D* htmp = new TH2D("tmp","",1000,0.0,4.8,1000,-0.005,0.005);

  TCanvas* c = new TCanvas("c","c",1100,500);
  c->Divide(2,1);
  c->cd(1);
  htmp->Draw();
  hsame_proj_for->SetMarkerStyle(24);
  hsame_proj_for->Draw("PESAME");
  hdiff_proj_for->Draw("PESAME");
  c->cd(2);
  htmp->Draw();
  hsame_proj_bak->SetMarkerStyle(24);
  hsame_proj_bak->Draw("PESAME");
  hdiff_proj_bak->Draw("PESAME");

  TCanvas* c1 = new TCanvas("c1","c1",550,500);
  htmp->Draw();
  hsame_proj->SetMarkerStyle(24);
  hsame_proj->Draw("PESAME");
  hdiff_proj->Draw("PESAME");
*/
}

void compare()
{

  TString filename("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/chargedepcorr_n220260_pttrg033_ptassallweight_etaass445_reverse_eff1_v13.root");
//  TString filename("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_20/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/chargedepcorr.root");  
//  TString filename("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_eff0_bin03_v21.root");
  TH1D* h[10];
  cme(filename,h);
cout<<"load file 1"<<endl;

  TString filename1("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/chargedepcorr_n220260_pttrg033_ptassallweight_etaass445_reverse_norecenter_eff1_v13.root");
//  TString filename1("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_norecenter_eff0_bin03_v18.root");
//  TString filename1("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_20/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/chargedepcorr_norecenter.root");
  TH1D* h1[10];
  cme(filename1,h1);
cout<<"load file 2"<<endl;
/*
  TString filename2("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_eff0_bin03_v16.root");
  TH1D* h2[6];
  cme(filename2,h2);
cout<<"load file 3"<<endl;

  TString filename3("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_norecenter_eff0_bin03_v16.root");
  TH1D* h3[6];
  cme(filename3,h3);
cout<<"load file 4"<<endl;

  TString filename4("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_norecenterHF_eff0_bin03_v16.root");
  TH1D* h4[6];
  cme(filename4,h4);
cout<<"load file 5"<<endl;
*/
  TH2D* htmp = new TH2D("tmp","",1000,0.15,4.8,1000,-0.03,0.03);

  TCanvas* c = new TCanvas("c","c",550,500);
  htmp->Draw();
  h[0]->SetMarkerStyle(20);
  h1[0]->SetMarkerStyle(25);
  h[0]->Draw("PESAME");
  h1[0]->Draw("PESAME");

  TCanvas* c1 = new TCanvas("c1","c1",550,500);
  htmp->Draw();
  h[3]->SetMarkerStyle(20);
  h1[3]->SetMarkerStyle(25);
/*
  h2[0]->SetMarkerStyle(24);
  h3[0]->SetMarkerStyle(25);
  h4[0]->SetMarkerStyle(28);
*/
  h[3]->Draw("PESAME");
  h1[3]->Draw("PESAME");

  TCanvas* c2 = new TCanvas("c2","c2",800,800);
  c2->Divide(2,2);
  c2->cd(1);
  htmp->Draw();
  h[6]->SetMarkerStyle(20);
  h1[6]->SetMarkerStyle(25);
  h[6]->Draw("PESAME");
  h1[6]->Draw("PESAME");
  c2->cd(2);
  htmp->Draw();
  h[7]->SetMarkerStyle(20);
  h1[7]->SetMarkerStyle(25);
  h[7]->Draw("PESAME");
  h1[7]->Draw("PESAME");
  c2->cd(3);
  htmp->Draw();
  h[8]->SetMarkerStyle(20);
  h1[8]->SetMarkerStyle(25);
  h[8]->Draw("PESAME");
  h1[8]->Draw("PESAME");
  c2->cd(4);
  htmp->Draw();
  h[9]->SetMarkerStyle(20);
  h1[9]->SetMarkerStyle(25);
  h[9]->Draw("PESAME");
  h1[9]->Draw("PESAME");
/*
  TLegend* legend = new TLegend(0.2,0.6,0.6,0.9);
  legend->AddEntry(h[0],"Only recenter, no HF");
  legend->AddEntry(h1[0],"recenter, twist, no HF");
  legend->AddEntry(h2[0],"full correction");
  legend->AddEntry(h3[0],"no correction");
  legend->AddEntry(h4[0],"no recenter HF");
  legend->Draw();
*/
}
