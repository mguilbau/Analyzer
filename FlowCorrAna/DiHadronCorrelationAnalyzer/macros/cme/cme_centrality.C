void cme_centrality()
{
  const int nfiles = 10;
  TString filename[nfiles];

  filename[0] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent002_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v43.root");
  filename[1] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent05_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v43.root");
  filename[2] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent510_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v43.root");
  filename[3] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent1020_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v43.root");
  filename[4] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent2030_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v43.root");
  filename[5] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent3040_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v43.root");
  filename[6] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v43.root");
  filename[7] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent5060_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v43.root");
  filename[8] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent6070_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v43.root");
  filename[9] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent7080_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v43.root");

  TH2D* hcospp_for[nfiles];
  TH2D* h2pcorrp_pp[nfiles];
  TH2D* h2pcorrm_pp[nfiles];
  TH2D* hnpairs_pp[nfiles];
  TH2D* hcosnn_for[nfiles];
  TH2D* h2pcorrp_nn[nfiles];
  TH2D* h2pcorrm_nn[nfiles];
  TH2D* hnpairs_nn[nfiles];
  TH2D* hcos_for_same_all[nfiles];
  TH2D* h2pcorrp_same_all[nfiles];
  TH2D* h2pcorrm_same_all[nfiles];
  TH2D* hnpairs_same_all[nfiles];
  TH2D* hcospn_for[nfiles];
  TH2D* h2pcorrp_pn[nfiles];
  TH2D* h2pcorrm_pn[nfiles];
  TH2D* hnpairs_pn[nfiles];
  TH2D* hcosnp_for[nfiles];
  TH2D* h2pcorrp_np[nfiles];
  TH2D* h2pcorrm_np[nfiles];
  TH2D* hnpairs_np[nfiles];
  TH2D* hcos_for_diff_all[nfiles];
  TH2D* h2pcorrp_diff_all[nfiles];
  TH2D* h2pcorrm_diff_all[nfiles];
  TH2D* hnpairs_diff_all[nfiles];
  TH1D* hq2[nfiles];

  TH1D* hcos_for_all_same_1D[nfiles];
  TH1D* h2pcorrp_for_all_same_1D[nfiles];
  TH1D* h2pcorrm_for_all_same_1D[nfiles];
  TH1D* hcos_for_all_diff_1D[nfiles];
  TH1D* h2pcorrp_for_all_diff_1D[nfiles];
  TH1D* h2pcorrm_for_all_diff_1D[nfiles];

  TH1D* hcos_for_all_same_1D_rebin[nfiles];
  TH1D* h2pcorrp_for_all_same_1D_rebin[nfiles];
  TH1D* h2pcorrm_for_all_same_1D_rebin[nfiles];
  TH1D* hcos_for_all_diff_1D_rebin[nfiles];
  TH1D* h2pcorrp_for_all_diff_1D_rebin[nfiles];
  TH1D* h2pcorrm_for_all_diff_1D_rebin[nfiles];

  TFile* f[nfiles];

  double cos_same_tot[nfiles][48] = {{0.0}};
  double pcorrp_same_tot[nfiles][48] = {{0.0}};
  double pcorrm_same_tot[nfiles][48] = {{0.0}};
  double cos_same_tot_err[nfiles][48] = {{0.0}};
  double pcorrp_same_tot_err[nfiles][48] = {{0.0}};
  double pcorrm_same_tot_err[nfiles][48] = {{0.0}};
  double npairs_same_tot[nfiles][48] = {{0.0}};

  double cos_diff_tot[nfiles][48] = {{0.0}};
  double pcorrp_diff_tot[nfiles][48] = {{0.0}};
  double pcorrm_diff_tot[nfiles][48] = {{0.0}};
  double cos_diff_tot_err[nfiles][48] = {{0.0}};
  double pcorrp_diff_tot_err[nfiles][48] = {{0.0}};
  double pcorrm_diff_tot_err[nfiles][48] = {{0.0}};
  double npairs_diff_tot[nfiles][48] = {{0.0}};

  double sum_cos_for_same[nfiles]={0};
  double sum_2pcorrp_for_same[nfiles]={0};
  double sum_2pcorrm_for_same[nfiles]={0};
  double sum_cos_for_same_err[nfiles]={0};
  double sum_2pcorrp_for_same_err[nfiles]={0};
  double sum_2pcorrm_for_same_err[nfiles]={0};
  double sum_npairs_same[nfiles]={0};
  double sum_cos_for_diff[nfiles]={0};
  double sum_2pcorrp_for_diff[nfiles]={0};
  double sum_2pcorrm_for_diff[nfiles]={0};
  double sum_cos_for_diff_err[nfiles]={0};
  double sum_2pcorrp_for_diff_err[nfiles]={0};
  double sum_2pcorrm_for_diff_err[nfiles]={0};
  double sum_npairs_diff[nfiles]={0};
  double cent[nfiles]={0.2,2.5,7.5,15,25,35,45,55,65,75};
  double cent_err[nfiles]={0};

  for(int jj=0;jj<nfiles;jj++)
  {
    f[jj] = new TFile(filename[jj].Data());
    hnpairs_pp[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumnpairs_pp");
    hcospp_for[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumcos_pp_for");
    h2pcorrp_pp[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumcos2pcorrp_pp");
    h2pcorrm_pp[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumcos2pcorrm_pp");
    hnpairs_nn[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumnpairs_nn");
    hcosnn_for[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumcos_nn_for");
    h2pcorrp_nn[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumcos2pcorrp_nn");
    h2pcorrm_nn[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumcos2pcorrm_nn");
    hnpairs_pn[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumnpairs_pn");
    hcospn_for[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumcos_pn_for");
    h2pcorrp_pn[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumcos2pcorrp_pn");
    h2pcorrm_pn[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumcos2pcorrm_pn");
    hnpairs_np[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumnpairs_np");
    hcosnp_for[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumcos_np_for");
    h2pcorrp_np[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumcos2pcorrp_np");
    h2pcorrm_np[jj] = (TH2D*)f[jj]->Get("chargedepcorr_ana_HI/sumcos2pcorrm_np");
    hq2[jj] = (TH1D*)f[jj]->Get("chargedepcorr_ana_HI/q2asscos");

    hcos_for_same_all[jj] = (TH2D*)hcospp_for[jj]->Clone(Form("sumcos_for_same_all_%d",jj));
    h2pcorrp_same_all[jj] = (TH2D*)h2pcorrp_pp[jj]->Clone(Form("sumcos2pcorrp_same_all_%d",jj));
    h2pcorrm_same_all[jj] = (TH2D*)h2pcorrm_pp[jj]->Clone(Form("sumcos2pcorrm_same_all_%d",jj));
    hnpairs_same_all[jj] = (TH2D*)hnpairs_pp[jj]->Clone(Form("npairs_same_all_%d",jj));
    hcos_for_same_all[jj]->Add(hcosnn_for[jj]);
    h2pcorrp_same_all[jj]->Add(h2pcorrp_nn[jj]);
    h2pcorrm_same_all[jj]->Add(h2pcorrm_nn[jj]);
    hnpairs_same_all[jj]->Add(hnpairs_nn[jj]);

    hcos_for_diff_all[jj] = (TH2D*)hcospn_for[jj]->Clone(Form("sumcos_for_diff_all_%d",jj));
    h2pcorrp_diff_all[jj] = (TH2D*)h2pcorrp_pn[jj]->Clone(Form("sumcos2pcorrp_diff_all_%d",jj));
    h2pcorrm_diff_all[jj] = (TH2D*)h2pcorrm_pn[jj]->Clone(Form("sumcos2pcorrm_diff_all_%d",jj));
    hnpairs_diff_all[jj] = (TH2D*)hnpairs_pn[jj]->Clone(Form("npairs_diff_all_%d",jj));
    hcos_for_diff_all[jj]->Add(hcosnp_for[jj]);
    h2pcorrp_diff_all[jj]->Add(h2pcorrp_np[jj]);
    h2pcorrm_diff_all[jj]->Add(h2pcorrm_np[jj]);
    hnpairs_diff_all[jj]->Add(hnpairs_np[jj]);

    for(int i=0;i<48;i++)
      for(int j=i;j<48;j++)
      {
//if(i>=16 || j>=16) continue;
        cos_same_tot[jj][j-i] += hcos_for_same_all[jj]->GetBinContent(i+1,j+1);
        pcorrp_same_tot[jj][j-i] += h2pcorrp_same_all[jj]->GetBinContent(i+1,j+1);
        pcorrm_same_tot[jj][j-i] += h2pcorrm_same_all[jj]->GetBinContent(i+1,j+1);
        cos_same_tot_err[jj][j-i] += hcos_for_same_all[jj]->GetBinError(i+1,j+1)*hcos_for_same_all[jj]->GetBinError(i+1,j+1);
        pcorrp_same_tot_err[jj][j-i] += h2pcorrp_same_all[jj]->GetBinError(i+1,j+1)*h2pcorrp_same_all[jj]->GetBinError(i+1,j+1);
        pcorrm_same_tot_err[jj][j-i] += h2pcorrm_same_all[jj]->GetBinError(i+1,j+1)*h2pcorrm_same_all[jj]->GetBinError(i+1,j+1);
        npairs_same_tot[jj][j-i] += hnpairs_same_all[jj]->GetBinContent(i+1,j+1);

        cos_diff_tot[jj][j-i] += hcos_for_diff_all[jj]->GetBinContent(i+1,j+1);
//cout<<cos_diff_tot[jj][j-i]<<endl;
        pcorrp_diff_tot[jj][j-i] += h2pcorrp_diff_all[jj]->GetBinContent(i+1,j+1);
        pcorrm_diff_tot[jj][j-i] += h2pcorrm_diff_all[jj]->GetBinContent(i+1,j+1);
        cos_diff_tot_err[jj][j-i] += hcos_for_diff_all[jj]->GetBinError(i+1,j+1)*hcos_for_diff_all[jj]->GetBinError(i+1,j+1);
        pcorrp_diff_tot_err[jj][j-i] += h2pcorrp_diff_all[jj]->GetBinError(i+1,j+1)*h2pcorrp_diff_all[jj]->GetBinError(i+1,j+1);
        pcorrm_diff_tot_err[jj][j-i] += h2pcorrm_diff_all[jj]->GetBinError(i+1,j+1)*h2pcorrm_diff_all[jj]->GetBinError(i+1,j+1);
        npairs_diff_tot[jj][j-i] += hnpairs_diff_all[jj]->GetBinContent(i+1,j+1);
      }

    hcos_for_all_same_1D[jj] = new TH1D(Form("hcos_for_all_same_1D_%d",jj),"",48,0-0.1/2,4.8-0.1/2);
    h2pcorrp_for_all_same_1D[jj] = new TH1D(Form("h2pcorrp_for_all_same_1D_%d",jj),"",48,0-0.1/2,4.8-0.1/2);
    h2pcorrm_for_all_same_1D[jj] = new TH1D(Form("h2pcorrm_for_all_same_1D_%d",jj),"",48,0-0.1/2,4.8-0.1/2);
    hcos_for_all_diff_1D[jj] = new TH1D(Form("hcos_for_all_diff_1D_%d",jj),"",48,0-0.1/2,4.8-0.1/2);
    h2pcorrp_for_all_diff_1D[jj] = new TH1D(Form("h2pcorrp_for_all_diff_1D_%d",jj),"",48,0-0.1/2,4.8-0.1/2);
    h2pcorrm_for_all_diff_1D[jj] = new TH1D(Form("h2pcorrm_for_all_diff_1D_%d",jj),"",48,0-0.1/2,4.8-0.1/2);

    hcos_for_all_same_1D_rebin[jj] = new TH1D(Form("hcos_for_all_same_1D_rebin_%d",jj),"",23,0.15-0.2/2,4.65-0.2/2);
    h2pcorrp_for_all_same_1D_rebin[jj] = new TH1D(Form("h2pcorrp_for_all_same_1D_rebin_%d",jj),"",23,0.15-0.2/2,4.65-0.2/2);
    h2pcorrm_for_all_same_1D_rebin[jj] = new TH1D(Form("h2pcorrm_for_all_same_1D_rebin_%d",jj),"",23,0.15-0.2/2,4.65-0.2/2);
    hcos_for_all_diff_1D_rebin[jj] = new TH1D(Form("hcos_for_all_diff_1D_rebin_%d",jj),"",23,0.15-0.2/2,4.65-0.2/2);
    h2pcorrp_for_all_diff_1D_rebin[jj] = new TH1D(Form("h2pcorrp_for_all_diff_1D_rebin_%d",jj),"",23,0.15-0.2/2,4.65-0.2/2);
    h2pcorrm_for_all_diff_1D_rebin[jj] = new TH1D(Form("h2pcorrm_for_all_diff_1D_rebin_%d",jj),"",23,0.15-0.2/2,4.65-0.2/2);

    hcos_for_all_diff_1D[jj]->SetMarkerStyle(24);
    h2pcorrp_for_all_diff_1D[jj]->SetMarkerStyle(24);
    h2pcorrm_for_all_diff_1D[jj]->SetMarkerStyle(24);
    hcos_for_all_same_1D_rebin[jj]->SetMarkerStyle(24);
    h2pcorrp_for_all_same_1D_rebin[jj]->SetMarkerStyle(24);
    h2pcorrm_for_all_same_1D_rebin[jj]->SetMarkerStyle(24);

    for(int i=0;i<48;i++)
    {
      hcos_for_all_same_1D[jj]->SetBinContent(i+1,cos_same_tot[jj][i]/npairs_same_tot[jj][i]/sqrt(hq2[jj]->GetMean()));
      h2pcorrp_for_all_same_1D[jj]->SetBinContent(i+1,pcorrp_same_tot[jj][i]/npairs_same_tot[jj][i]);
      h2pcorrm_for_all_same_1D[jj]->SetBinContent(i+1,pcorrm_same_tot[jj][i]/npairs_same_tot[jj][i]);
      if(cos_same_tot_err[jj][i]) hcos_for_all_same_1D[jj]->SetBinError(i+1,sqrt(cos_same_tot_err[jj][i])/npairs_same_tot[jj][i]/sqrt(hq2[jj]->GetMean()));
      if(pcorrp_same_tot_err[jj][i]) h2pcorrp_for_all_same_1D[jj]->SetBinError(i+1,sqrt(pcorrp_same_tot_err[jj][i])/npairs_same_tot[jj][i]);
      if(pcorrm_same_tot_err[jj][i]) h2pcorrm_for_all_same_1D[jj]->SetBinError(i+1,sqrt(pcorrm_same_tot_err[jj][i])/npairs_same_tot[jj][i]);
  
      if(i>0)
      {
        sum_cos_for_same[jj] += cos_same_tot[jj][i]/sqrt(hq2[jj]->GetMean());
        sum_2pcorrp_for_same[jj] += pcorrp_same_tot[jj][i];
        sum_2pcorrm_for_same[jj] += pcorrm_same_tot[jj][i];
        sum_cos_for_same_err[jj] += cos_same_tot_err[jj][i]/hq2[jj]->GetMean();
        sum_2pcorrp_for_same_err[jj] += pcorrp_same_tot_err[jj][i];
        sum_2pcorrm_for_same_err[jj] += pcorrm_same_tot_err[jj][i];
        sum_npairs_same[jj] += npairs_same_tot[jj][i];
      }

      hcos_for_all_diff_1D[jj]->SetBinContent(i+1,cos_diff_tot[jj][i]/npairs_diff_tot[jj][i]/sqrt(hq2[jj]->GetMean()));
      h2pcorrp_for_all_diff_1D[jj]->SetBinContent(i+1,pcorrp_diff_tot[jj][i]/npairs_diff_tot[jj][i]);
      h2pcorrm_for_all_diff_1D[jj]->SetBinContent(i+1,pcorrm_diff_tot[jj][i]/npairs_diff_tot[jj][i]);
      if(cos_diff_tot_err[jj][i]) hcos_for_all_diff_1D[jj]->SetBinError(i+1,sqrt(cos_diff_tot_err[jj][i])/npairs_diff_tot[jj][i]/sqrt(hq2[jj]->GetMean()));
      if(pcorrp_diff_tot_err[jj][i]) h2pcorrp_for_all_diff_1D[jj]->SetBinError(i+1,sqrt(pcorrp_diff_tot_err[jj][i])/npairs_diff_tot[jj][i]);
      if(pcorrm_diff_tot_err[jj][i]) h2pcorrm_for_all_diff_1D[jj]->SetBinError(i+1,sqrt(pcorrm_diff_tot_err[jj][i])/npairs_diff_tot[jj][i]);
      if(i>0)
      {
        sum_cos_for_diff[jj] += cos_diff_tot[jj][i]/sqrt(hq2[jj]->GetMean());
        sum_2pcorrp_for_diff[jj] += pcorrp_diff_tot[jj][i];
        sum_2pcorrm_for_diff[jj] += pcorrm_diff_tot[jj][i];
        sum_cos_for_diff_err[jj] += cos_diff_tot_err[jj][i]/hq2[jj]->GetMean();
        sum_2pcorrp_for_diff_err[jj] += pcorrp_diff_tot_err[jj][i];
        sum_2pcorrm_for_diff_err[jj] += pcorrm_diff_tot_err[jj][i];
        sum_npairs_diff[jj] += npairs_diff_tot[jj][i];
      }
    }
    sum_cos_for_same[jj] = sum_cos_for_same[jj] / sum_npairs_same[jj];
    sum_2pcorrp_for_same[jj] = sum_cos_for_same[jj] / sum_npairs_same[jj];
    sum_2pcorrm_for_same[jj] = sum_2pcorrp_for_same[jj] / sum_npairs_same[jj];
    sum_cos_for_diff[jj] = sum_cos_for_diff[jj] / sum_npairs_diff[jj];
    sum_2pcorrp_for_diff[jj] = sum_2pcorrp_for_diff[jj] / sum_npairs_diff[jj];
    sum_2pcorrm_for_diff[jj] = sum_2pcorrm_for_diff[jj] / sum_npairs_diff[jj];

    sum_cos_for_same_err[jj] = sqrt(sum_cos_for_same_err[jj])/sum_npairs_same[jj];
    sum_2pcorrp_for_same_err[jj] = sqrt(sum_2pcorrp_for_same_err[jj])/sum_npairs_same[jj];
    sum_2pcorrm_for_same_err[jj] = sqrt(sum_2pcorrm_for_same_err[jj])/sum_npairs_same[jj];
    sum_cos_for_diff_err[jj] = sqrt(sum_cos_for_diff_err[jj])/sum_npairs_diff[jj];
    sum_2pcorrp_for_diff_err[jj] = sqrt(sum_2pcorrp_for_diff_err[jj])/sum_npairs_diff[jj];
    sum_2pcorrm_for_diff_err[jj] = sqrt(sum_2pcorrm_for_diff_err[jj])/sum_npairs_diff[jj];

    for(int i=0;i<23;i++)
    {
      hcos_for_all_same_1D_rebin[jj]->SetBinContent(i+1,(cos_same_tot[jj][2*i+1]+cos_same_tot[jj][2*i+2])/(npairs_same_tot[jj][2*i+1]+npairs_same_tot[jj][2*i+2])/sqrt(hq2[jj]->GetMean()));
      h2pcorrp_for_all_same_1D_rebin[jj]->SetBinContent(i+1,(pcorrp_same_tot[jj][2*i+1]+pcorrp_same_tot[jj][2*i+2])/(npairs_same_tot[jj][2*i+1]+npairs_same_tot[jj][2*i+2]));
      h2pcorrm_for_all_same_1D_rebin[jj]->SetBinContent(i+1,(pcorrm_same_tot[jj][2*i+1]+pcorrm_same_tot[jj][2*i+2])/(npairs_same_tot[jj][2*i+1]+npairs_same_tot[jj][2*i+2]));
      hcos_for_all_same_1D_rebin[jj]->SetBinError(i+1,sqrt(cos_same_tot_err[jj][2*i+1]+cos_same_tot_err[jj][2*i+2])/(npairs_same_tot[jj][2*i+1]+npairs_same_tot[jj][2*i+2])/sqrt(hq2[jj]->GetMean()));
      h2pcorrp_for_all_same_1D_rebin[jj]->SetBinError(i+1,sqrt(pcorrp_same_tot_err[jj][2*i+1]+pcorrp_same_tot_err[jj][2*i+2])/(npairs_same_tot[jj][2*i+1]+npairs_same_tot[jj][2*i+2]));
      h2pcorrm_for_all_same_1D_rebin[jj]->SetBinError(i+1,sqrt(pcorrm_same_tot_err[jj][2*i+1]+pcorrm_same_tot_err[jj][2*i+2])/(npairs_same_tot[jj][2*i+1]+npairs_same_tot[jj][2*i+2]));

      hcos_for_all_diff_1D_rebin[jj]->SetBinContent(i+1,(cos_diff_tot[jj][2*i+1]+cos_diff_tot[jj][2*i+2])/(npairs_diff_tot[jj][2*i+1]+npairs_diff_tot[jj][2*i+2])/sqrt(hq2[jj]->GetMean()));
      h2pcorrp_for_all_diff_1D_rebin[jj]->SetBinContent(i+1,(pcorrp_diff_tot[jj][2*i+1]+pcorrp_diff_tot[jj][2*i+2])/(npairs_diff_tot[jj][2*i+1]+npairs_diff_tot[jj][2*i+2]));
      h2pcorrm_for_all_diff_1D_rebin[jj]->SetBinContent(i+1,(pcorrm_diff_tot[jj][2*i+1]+pcorrm_diff_tot[jj][2*i+2])/(npairs_diff_tot[jj][2*i+1]+npairs_diff_tot[jj][2*i+2]));
      hcos_for_all_diff_1D_rebin[jj]->SetBinError(i+1,sqrt(cos_diff_tot_err[jj][2*i+1]+cos_diff_tot_err[jj][2*i+2])/(npairs_diff_tot[jj][2*i+1]+npairs_diff_tot[jj][2*i+2])/sqrt(hq2[jj]->GetMean()));
      h2pcorrp_for_all_diff_1D_rebin[jj]->SetBinError(i+1,sqrt(pcorrp_diff_tot_err[jj][2*i+1]+pcorrp_diff_tot_err[jj][2*i+2])/(npairs_diff_tot[jj][2*i+1]+npairs_diff_tot[jj][2*i+2]));
      h2pcorrm_for_all_diff_1D_rebin[jj]->SetBinError(i+1,sqrt(pcorrm_diff_tot_err[jj][2*i+1]+pcorrm_diff_tot_err[jj][2*i+2])/(npairs_diff_tot[jj][2*i+1]+npairs_diff_tot[jj][2*i+2]));
    }
  }

  double cent_alice[9] = {2.5,7.5,15,25,35,45,55,65,75};
  double cent_alice_err[9] = {0};
  double q3diff_alice[9] = {0.0,-1.0E-6,-1.4E-5,-2.5E-5,-6.4E-5,-2.6E-5,1.08E-4,3.15E-4,9.89E-4};
  double q3diff_alice_err[9] = {+4.0E-6,+6.0E-6,+9.0E-6,+1.4E-5,+2.3E-5,+4.1E-5,+8.0E-5,+1.22E-4,+2.17E-4};
  double q3same_alice[9] = {0.0,-1.0E-5,-4.6E-5,-9.8E-5,-1.47E-4,-2.48E-4,-3.66E-4,-3.7E-4,-3.93E-4};
  double q3same_alice_err[9] = {+4.0E-6,+6.0E-6,+9.0E-6,+1.4E-5,+2.4E-5,+4.1E-5,+8.1E-5,+1.77E-4,+3.77E-4};

  TGraphErrors* gr_same = new TGraphErrors(nfiles,cent,sum_cos_for_same,cent_err,sum_cos_for_same_err);
  TGraphErrors* gr_diff = new TGraphErrors(nfiles,cent,sum_cos_for_diff,cent_err,sum_cos_for_diff_err);
  TGraphErrors* gr_same_alice = new TGraphErrors(9,cent_alice,q3same_alice,cent_alice_err,q3same_alice_err);
  TGraphErrors* gr_diff_alice = new TGraphErrors(9,cent_alice,q3diff_alice,cent_alice_err,q3diff_alice_err);

  TH2D* htmp = new TH2D("tmp","",1000,0.01,4.8,1000,-0.003,0.003);

  TCanvas* c1 = new TCanvas("c1","c1",1200,900);
  c1->Divide(4,3);
  for(int i=0;i<10;i++)
  {
    c1->cd(i+1);
    htmp->Draw();
    hcos_for_all_same_1D_rebin[i]->Draw("PESAME");
    hcos_for_all_diff_1D_rebin[i]->Draw("PESAME");
  }

  TCanvas* c2 = new TCanvas("c2","c2",1200,900);
  c2->Divide(4,3);
  for(int i=0;i<10;i++)
  {
    c2->cd(i+1);
    htmp->Draw();
    h2pcorrp_for_all_same_1D_rebin[i]->Draw("PESAME");
    h2pcorrp_for_all_diff_1D_rebin[i]->Draw("PESAME");
  }

  TCanvas* c3 = new TCanvas("c3","c3",1200,900);
  c3->Divide(4,3);
  for(int i=0;i<10;i++)
  {
    c3->cd(i+1);
    htmp->Draw();
    h2pcorrm_for_all_same_1D_rebin[i]->Draw("PESAME");
    h2pcorrm_for_all_diff_1D_rebin[i]->Draw("PESAME");
  }

  TH2D* htmp1 = new TH2D("tmp1","",1000,0,100,1000,-0.003,0.003);
  TCanvas* c4 = new TCanvas("c4","c4",600,550);
  htmp1->Draw();
  gr_same->SetMarkerColor(2);
  gr_same->Draw("PESAME");
  gr_diff->SetMarkerColor(2);
  gr_diff->SetMarkerStyle(24);
  gr_diff->Draw("PESAME");
  gr_same_alice->SetMarkerStyle(29);
  gr_same_alice->Draw("PESAME");
  gr_diff_alice->SetMarkerStyle(28);
  gr_diff_alice->Draw("PESAME");
}
