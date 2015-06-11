//void cme_new(TString filename, TH1D* h[10])
void cme_new1()
{
//  TFile* f = new TFile(filename.Data());
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_20/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/chargedepcorr.root");
  TFile* f = new TFile("/export/d00/scratch/davidlw/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent3040_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v44.root");
//  TFile* f_norecenter = new TFile("/export/d00/scratch/davidlw/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent05_pttrg033_ptassallweight_etaass445_eff0_bin01_norecenter_v42.root");
//  TFile* f_norecenter = new TFile("/export/d00/scratch/davidlw/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v43.root");

  TH2D* hcospp_for;
  TH2D* h2pcorrp_pp;
  TH2D* h2pcorrm_pp;
  TH2D* hnpairs_pp;
  TH2D* hcosnn_for;
  TH2D* h2pcorrp_nn;
  TH2D* h2pcorrm_nn;
  TH2D* hnpairs_nn;
  TH2D* hcos_for_all;
  TH2D* h2pcorrp_all;
  TH2D* h2pcorrm_all;
  TH2D* hnpairs_all;

  TH2D* hcospp_for_norecenter;
  TH2D* h2pcorrp_pp_norecenter;
  TH2D* h2pcorrm_pp_norecenter;
  TH2D* hnpairs_pp_norecenter;
  TH2D* hcosnn_for_norecenter;
  TH2D* h2pcorrp_nn_norecenter;
  TH2D* h2pcorrm_nn_norecenter;
  TH2D* hnpairs_nn_norecenter;
  TH2D* hcos_for_all_norecenter;
  TH2D* h2pcorrp_all_norecenter;
  TH2D* h2pcorrm_all_norecenter;
  TH2D* hnpairs_all_norecenter;

  hnpairs_pp = (TH2D*)f->Get("chargedepcorr_ana_HI/sumnpairs_pp");
  hcospp_for = (TH2D*)f->Get("chargedepcorr_ana_HI/sumcos_pp_for");
  h2pcorrp_pp = (TH2D*)f->Get("chargedepcorr_ana_HI/sumcos2pcorrp_pp");
  h2pcorrm_pp = (TH2D*)f->Get("chargedepcorr_ana_HI/sumcos2pcorrm_pp");
  hnpairs_nn = (TH2D*)f->Get("chargedepcorr_ana_HI/sumnpairs_nn");
  hcosnn_for = (TH2D*)f->Get("chargedepcorr_ana_HI/sumcos_nn_for");
  h2pcorrp_nn = (TH2D*)f->Get("chargedepcorr_ana_HI/sumcos2pcorrp_nn");
  h2pcorrm_nn = (TH2D*)f->Get("chargedepcorr_ana_HI/sumcos2pcorrm_nn");
  TH1D* hq2 = (TH1D*)f->Get("chargedepcorr_ana_HI/q2asscos");
  TH1D* hnpairs_hf = (TH1D*)f->Get("chargedepcorr_ana_HI/sumnpairs_hf");

  hnpairs_pp_norecenter = (TH2D*)f->Get("chargedepcorr_ana_HI/sumnpairs_pn");
  hcospp_for_norecenter = (TH2D*)f->Get("chargedepcorr_ana_HI/sumcos_pn_for");
  h2pcorrp_pp_norecenter = (TH2D*)f->Get("chargedepcorr_ana_HI/sumcos2pcorrp_pn");
  h2pcorrm_pp_norecenter = (TH2D*)f->Get("chargedepcorr_ana_HI/sumcos2pcorrm_pn");
  hnpairs_nn_norecenter = (TH2D*)f->Get("chargedepcorr_ana_HI/sumnpairs_np");
  hcosnn_for_norecenter = (TH2D*)f->Get("chargedepcorr_ana_HI/sumcos_np_for");
  h2pcorrp_nn_norecenter = (TH2D*)f->Get("chargedepcorr_ana_HI/sumcos2pcorrp_np");
  h2pcorrm_nn_norecenter = (TH2D*)f->Get("chargedepcorr_ana_HI/sumcos2pcorrm_np");
  TH1D* hq2_norecenter = (TH1D*)f->Get("chargedepcorr_ana_HI/q2asscos");
  TH1D* hnpairs_hf_norecenter = (TH1D*)f->Get("chargedepcorr_ana_HI/sumnpairs_hf");

  hcos_for_all = (TH2D*)hcospp_for->Clone("sumcos_for_all");
  h2pcorrp_all = (TH2D*)h2pcorrp_pp->Clone("sumcos2pcorrp_all");
  h2pcorrm_all = (TH2D*)h2pcorrm_pp->Clone("sumcos2pcorrm_all");
  hnpairs_all = (TH2D*)hnpairs_pp->Clone("npairs_all");
  hcos_for_all->Add(hcosnn_for);
  h2pcorrp_all->Add(h2pcorrp_nn);
  h2pcorrm_all->Add(h2pcorrm_nn);
  hnpairs_all->Add(hnpairs_nn);  

  hcos_for_all_norecenter = (TH2D*)hcospp_for_norecenter->Clone("sumcos_for_all_norecenter");
  h2pcorrp_all_norecenter = (TH2D*)h2pcorrp_pp_norecenter->Clone("sumcos2pcorrp_all_norecenter");
  h2pcorrm_all_norecenter = (TH2D*)h2pcorrm_pp_norecenter->Clone("sumcos2pcorrm_all_norecenter");
  hnpairs_all_norecenter = (TH2D*)hnpairs_pp_norecenter->Clone("npairs_all_norecenter");
  hcos_for_all_norecenter->Add(hcosnn_for_norecenter);
  h2pcorrp_all_norecenter->Add(h2pcorrp_nn_norecenter);
  h2pcorrm_all_norecenter->Add(h2pcorrm_nn_norecenter);
  hnpairs_all_norecenter->Add(hnpairs_nn_norecenter);

  TCanvas* c = new TCanvas("c","c",900,900);
  c->Divide(2,2);
  c->cd(1);
  hcos_for_all->Draw("lego2");
  c->cd(2);
  h2pcorrp_all->Draw("lego2");
  c->cd(3);
  h2pcorrm_all->Draw("lego2");
  c->cd(4);
  hnpairs_all->Draw("lego2");

  TCanvas* cc = new TCanvas("cc","cc",900,900);
  cc->Divide(2,2);
  cc->cd(1);
  hcos_for_all_norecenter->Draw("lego2");
  cc->cd(2);
  h2pcorrp_all_norecenter->Draw("lego2");
  cc->cd(3);
  h2pcorrm_all_norecenter->Draw("lego2");
  cc->cd(4);
  hnpairs_all_norecenter->Draw("lego2");

  double cos_tot[48] = {0.0};
  double pcorrp_tot[48] = {0.0};
  double pcorrm_tot[48] = {0.0};
  double cos_tot_err[48] = {0.0};
  double pcorrp_tot_err[48] = {0.0};
  double pcorrm_tot_err[48] = {0.0};
  double npairs_tot[48] = {0.0};

  double cos_tot_norecenter[48] = {0.0};
  double pcorrp_tot_norecenter[48] = {0.0};
  double pcorrm_tot_norecenter[48] = {0.0};
  double cos_tot_norecenter_err[48] = {0.0};
  double pcorrp_tot_norecenter_err[48] = {0.0};
  double pcorrm_tot_norecenter_err[48] = {0.0};
  double npairs_tot_norecenter[48] = {0.0};

  for(int i=0;i<48;i++)
    for(int j=i;j<48;j++)
    {
//if(i==0 || i==1 || i==22 || i==23 || j==0 || j==1 || j==22 || i==23) continue;
      cos_tot[j-i] += hcos_for_all->GetBinContent(i+1,j+1);
      pcorrp_tot[j-i] += h2pcorrp_all->GetBinContent(i+1,j+1);
      pcorrm_tot[j-i] += h2pcorrm_all->GetBinContent(i+1,j+1);
      cos_tot_err[j-i] += hcos_for_all->GetBinError(i+1,j+1)*hcos_for_all->GetBinError(i+1,j+1);
      pcorrp_tot_err[j-i] += h2pcorrp_all->GetBinError(i+1,j+1)*h2pcorrp_all->GetBinError(i+1,j+1);
      pcorrm_tot_err[j-i] += h2pcorrm_all->GetBinError(i+1,j+1)*h2pcorrm_all->GetBinError(i+1,j+1);
      npairs_tot[j-i] += hnpairs_all->GetBinContent(i+1,j+1);

      cos_tot_norecenter[j-i] += hcos_for_all_norecenter->GetBinContent(i+1,j+1);
      pcorrp_tot_norecenter[j-i] += h2pcorrp_all_norecenter->GetBinContent(i+1,j+1);
      pcorrm_tot_norecenter[j-i] += h2pcorrm_all_norecenter->GetBinContent(i+1,j+1);
      cos_tot_norecenter_err[j-i] += hcos_for_all_norecenter->GetBinError(i+1,j+1)*hcos_for_all_norecenter->GetBinError(i+1,j+1);
      pcorrp_tot_norecenter_err[j-i] += h2pcorrp_all_norecenter->GetBinError(i+1,j+1)*h2pcorrp_all_norecenter->GetBinError(i+1,j+1);
      pcorrm_tot_norecenter_err[j-i] += h2pcorrm_all_norecenter->GetBinError(i+1,j+1)*h2pcorrm_all_norecenter->GetBinError(i+1,j+1);
      npairs_tot_norecenter[j-i] += hnpairs_all_norecenter->GetBinContent(i+1,j+1);
    }

  TH1D* hcos_for_all_1D = new TH1D("hcos_for_all_1D","",48,0-0.1/2,4.8-0.1/2);
  TH1D* h2pcorrp_for_all_1D = new TH1D("h2pcorrp_for_all_1D","",48,0-0.1/2,4.8-0.1/2);
  TH1D* h2pcorrm_for_all_1D = new TH1D("h2pcorrm_for_all_1D","",48,0-0.1/2,4.8-0.1/2);
  TH1D* hcos_for_all_norecenter_1D = new TH1D("hcos_for_all_norecenter_1D","",48,0-0.1/2,4.8-0.1/2);
  TH1D* h2pcorrp_for_all_norecenter_1D = new TH1D("h2pcorrp_for_all_norecenter_1D","",48,0-0.1/2,4.8-0.1/2);
  TH1D* h2pcorrm_for_all_norecenter_1D = new TH1D("h2pcorrm_for_all_norecenter_1D","",48,0-0.1/2,4.8-0.1/2);

  TH1D* hcos_for_all_1D_rebin = new TH1D("hcos_for_all_1D_rebin","",23,0.15-0.2/2,4.65-0.2/2);
  TH1D* h2pcorrp_for_all_1D_rebin = new TH1D("h2pcorrp_for_all_1D_rebin","",23,0.15-0.2/2,4.65-0.2/2);
  TH1D* h2pcorrm_for_all_1D_rebin = new TH1D("h2pcorrm_for_all_1D_rebin","",23,0.15-0.2/2,4.65-0.2/2);
  TH1D* hcos_for_all_norecenter_1D_rebin = new TH1D("hcos_for_all_norecenter_1D_rebin","",23,0.15-0.2/2,4.65-0.2/2);
  TH1D* h2pcorrp_for_all_norecenter_1D_rebin = new TH1D("h2pcorrp_for_all_norecenter_1D_rebin","",23,0.15-0.2/2,4.65-0.2/2);
  TH1D* h2pcorrm_for_all_norecenter_1D_rebin = new TH1D("h2pcorrm_for_all_norecenter_1D_rebin","",23,0.15-0.2/2,4.65-0.2/2);

  hcos_for_all_norecenter_1D->SetMarkerStyle(24);
  h2pcorrp_for_all_norecenter_1D->SetMarkerStyle(24);
  h2pcorrm_for_all_norecenter_1D->SetMarkerStyle(24);
  hcos_for_all_norecenter_1D_rebin->SetMarkerStyle(24);
  h2pcorrp_for_all_norecenter_1D_rebin->SetMarkerStyle(24);
  h2pcorrm_for_all_norecenter_1D_rebin->SetMarkerStyle(24);

  for(int i=0;i<48;i++)
  {
    hcos_for_all_1D->SetBinContent(i+1,cos_tot[i]/npairs_tot[i]/sqrt(hq2->GetMean()));
    h2pcorrp_for_all_1D->SetBinContent(i+1,pcorrp_tot[i]/npairs_tot[i]);
    h2pcorrm_for_all_1D->SetBinContent(i+1,pcorrm_tot[i]/npairs_tot[i]);
    if(cos_tot_err[i]) hcos_for_all_1D->SetBinError(i+1,sqrt(cos_tot_err[i])/npairs_tot[i]/sqrt(hq2->GetMean()));
    if(pcorrp_tot_err[i]) h2pcorrp_for_all_1D->SetBinError(i+1,sqrt(pcorrp_tot_err[i])/npairs_tot[i]);
    if(pcorrm_tot_err[i]) h2pcorrm_for_all_1D->SetBinError(i+1,sqrt(pcorrm_tot_err[i])/npairs_tot[i]);

    hcos_for_all_norecenter_1D->SetBinContent(i+1,cos_tot_norecenter[i]/npairs_tot_norecenter[i]/sqrt(hq2_norecenter->GetMean()));
    h2pcorrp_for_all_norecenter_1D->SetBinContent(i+1,pcorrp_tot_norecenter[i]/npairs_tot_norecenter[i]);
    h2pcorrm_for_all_norecenter_1D->SetBinContent(i+1,pcorrm_tot_norecenter[i]/npairs_tot_norecenter[i]);
    if(cos_tot_norecenter_err[i]) hcos_for_all_norecenter_1D->SetBinError(i+1,sqrt(cos_tot_norecenter_err[i])/npairs_tot_norecenter[i]/sqrt(hq2_norecenter->GetMean()));
    if(pcorrp_tot_norecenter_err[i]) h2pcorrp_for_all_norecenter_1D->SetBinError(i+1,sqrt(pcorrp_tot_norecenter_err[i])/npairs_tot_norecenter[i]);
    if(pcorrm_tot_norecenter_err[i]) h2pcorrm_for_all_norecenter_1D->SetBinError(i+1,sqrt(pcorrm_tot_norecenter_err[i])/npairs_tot_norecenter[i]);
  }

  for(int i=0;i<23;i++)
  {
    hcos_for_all_1D_rebin->SetBinContent(i+1,(cos_tot[2*i+1]+cos_tot[2*i+2])/(npairs_tot[2*i+1]+npairs_tot[2*i+2])/sqrt(hq2->GetMean()));
    h2pcorrp_for_all_1D_rebin->SetBinContent(i+1,(pcorrp_tot[2*i+1]+pcorrp_tot[2*i+2])/(npairs_tot[2*i+1]+npairs_tot[2*i+2]));
    h2pcorrm_for_all_1D_rebin->SetBinContent(i+1,(pcorrm_tot[2*i+1]+pcorrm_tot[2*i+2])/(npairs_tot[2*i+1]+npairs_tot[2*i+2]));
    hcos_for_all_1D_rebin->SetBinError(i+1,sqrt(cos_tot_err[2*i+1]+cos_tot_err[2*i+2])/(npairs_tot[2*i+1]+npairs_tot[2*i+2])/sqrt(hq2->GetMean()));
    h2pcorrp_for_all_1D_rebin->SetBinError(i+1,sqrt(pcorrp_tot_err[2*i+1]+pcorrp_tot_err[2*i+2])/(npairs_tot[2*i+1]+npairs_tot[2*i+2]));
    h2pcorrm_for_all_1D_rebin->SetBinError(i+1,sqrt(pcorrm_tot_err[2*i+1]+pcorrm_tot_err[2*i+2])/(npairs_tot[2*i+1]+npairs_tot[2*i+2]));

    hcos_for_all_norecenter_1D_rebin->SetBinContent(i+1,(cos_tot_norecenter[2*i+1]+cos_tot_norecenter[2*i+2])/(npairs_tot_norecenter[2*i+1]+npairs_tot_norecenter[2*i+2])/sqrt(hq2_norecenter->GetMean()));
    h2pcorrp_for_all_norecenter_1D_rebin->SetBinContent(i+1,(pcorrp_tot_norecenter[2*i+1]+pcorrp_tot_norecenter[2*i+2])/(npairs_tot_norecenter[2*i+1]+npairs_tot_norecenter[2*i+2]));
    h2pcorrm_for_all_norecenter_1D_rebin->SetBinContent(i+1,(pcorrm_tot_norecenter[2*i+1]+pcorrm_tot_norecenter[2*i+2])/(npairs_tot_norecenter[2*i+1]+npairs_tot_norecenter[2*i+2]));
    hcos_for_all_norecenter_1D_rebin->SetBinError(i+1,sqrt(cos_tot_norecenter_err[2*i+1]+cos_tot_norecenter_err[2*i+2])/(npairs_tot_norecenter[2*i+1]+npairs_tot_norecenter[2*i+2])/sqrt(hq2_norecenter->GetMean()));
    h2pcorrp_for_all_norecenter_1D_rebin->SetBinError(i+1,sqrt(pcorrp_tot_norecenter_err[2*i+1]+pcorrp_tot_norecenter_err[2*i+2])/(npairs_tot_norecenter[2*i+1]+npairs_tot_norecenter[2*i+2]));
    h2pcorrm_for_all_norecenter_1D_rebin->SetBinError(i+1,sqrt(pcorrm_tot_norecenter_err[2*i+1]+pcorrm_tot_norecenter_err[2*i+2])/(npairs_tot_norecenter[2*i+1]+npairs_tot_norecenter[2*i+2]));
  }

  TH2D* htmp = new TH2D("tmp","",1000,0.01,4.8,1000,-0.003,0.003);

  TCanvas* c1 = new TCanvas("c1","c1",900,300);
  c1->Divide(3,1);
  c1->cd(1);
  htmp->Draw();
  hcos_for_all_1D->Draw("PESAME");
  hcos_for_all_norecenter_1D->Draw("PESAME");
  c1->cd(2);
  htmp->Draw();
  h2pcorrp_for_all_1D->Draw("PESAME");
  h2pcorrp_for_all_norecenter_1D->Draw("PESAME");
  c1->cd(3);
  htmp->Draw();
  h2pcorrm_for_all_1D->Draw("PESAME");
  h2pcorrm_for_all_norecenter_1D->Draw("PESAME");

  TCanvas* c2 = new TCanvas("c2","c2",900,300);
  c2->Divide(3,1);
  c2->cd(1);
  htmp->Draw();
  hcos_for_all_1D_rebin->Draw("PESAME");
  hcos_for_all_norecenter_1D_rebin->Draw("PESAME");
  c2->cd(2);
  htmp->Draw();
  h2pcorrp_for_all_1D_rebin->Draw("PESAME");
  h2pcorrp_for_all_norecenter_1D_rebin->Draw("PESAME");
  c2->cd(3);
  htmp->Draw();
  h2pcorrm_for_all_1D_rebin->Draw("PESAME");
  h2pcorrm_for_all_norecenter_1D_rebin->Draw("PESAME");
}
