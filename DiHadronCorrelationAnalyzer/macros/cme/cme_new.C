//void cme_new(TString filename, TH1D* h[10])
void cme_new()
{
//  TFile* f = new TFile(filename.Data());
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_20/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/chargedepcorr.root");
  TFile* f = new TFile("/export/d00/scratch/davidlw/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_eff0_zvtx1_bin01_v43.root");

  TH1D* hmult = (TH1D*)f->Get("chargedepcorr_ana_HI/multrawall");
  int nevents = hmult->GetEntries();
  
  TH2D* hcospp_for[40][40];
  TH2D* h2pcorrp_pp[40][40];
  TH2D* h2pcorrm_pp[40][40];
  TH2D* hnpairs_pp[40][40];
  TH2D* hcospp_for_all;
  TH2D* h2pcorrp_pp_all;
  TH2D* h2pcorrm_pp_all;
  TH2D* hnpairs_pp_all;

  TH2D* hcosnn_for[40][40];
  TH2D* h2pcorrp_nn[40][40];
  TH2D* h2pcorrm_nn[40][40];
  TH2D* hnpairs_nn[40][40];
  TH2D* hcosnn_for_all;
  TH2D* h2pcorrp_nn_all;
  TH2D* h2pcorrm_nn_all;
  TH2D* hnpairs_nn_all;

  TH2D* hcos_for_all;
  TH2D* h2pcorrp_all;
  TH2D* h2pcorrm_all;
  TH2D* hnpairs_all;

  for(int i=0;i<35;i++)
    for(int j=0;j<35;j++)
    {
      hnpairs_pp[i][j] = (TH2D*)f->Get(Form("chargedepcorr_ana_HI/sumnpairs_pp_n%d_n%d",i,j));
      hcospp_for[i][j] = (TH2D*)f->Get(Form("chargedepcorr_ana_HI/sumcos_pp_for_n%d_n%d",i,j));
      h2pcorrp_pp[i][j] = (TH2D*)f->Get(Form("chargedepcorr_ana_HI/sumcos2pcorrp_pp_n%d_n%d",i,j));
      h2pcorrm_pp[i][j] = (TH2D*)f->Get(Form("chargedepcorr_ana_HI/sumcos2pcorrm_pp_n%d_n%d",i,j));

      hnpairs_nn[i][j] = (TH2D*)f->Get(Form("chargedepcorr_ana_HI/sumnpairs_nn_n%d_n%d",i,j));
      hcosnn_for[i][j] = (TH2D*)f->Get(Form("chargedepcorr_ana_HI/sumcos_nn_for_n%d_n%d",i,j));
      h2pcorrp_nn[i][j] = (TH2D*)f->Get(Form("chargedepcorr_ana_HI/sumcos2pcorrp_nn_n%d_n%d",i,j));
      h2pcorrm_nn[i][j] = (TH2D*)f->Get(Form("chargedepcorr_ana_HI/sumcos2pcorrm_nn_n%d_n%d",i,j));
/*
      hnpairs_pp[i][j]->Scale(1.0/nevents);
      hcospp_for[i][j]->Scale(1.0/nevents);
      h2pcorrp_pp[i][j]->Scale(1.0/nevents);
      h2pcorrm_pp[i][j]->Scale(1.0/nevents);
      hnpairs_nn[i][j]->Scale(1.0/nevents);
      hcosnn_for[i][j]->Scale(1.0/nevents);
      h2pcorrp_nn[i][j]->Scale(1.0/nevents);
      h2pcorrm_nn[i][j]->Scale(1.0/nevents);
*/
      if(i==0 && j==0)
      {
        hcospp_for_all = (TH2D*)hcospp_for[i][j]->Clone("sumcos_pp_for_all");
        h2pcorrp_pp_all = (TH2D*)h2pcorrp_pp[i][j]->Clone("sumcos2pcorrp_pp_all");
        h2pcorrm_pp_all = (TH2D*)h2pcorrm_pp[i][j]->Clone("sumcos2pcorrm_pp_all");
        hnpairs_pp_all = (TH2D*)hnpairs_pp[i][j]->Clone("npairs_pp_all");
        hcosnn_for_all = (TH2D*)hcosnn_for[i][j]->Clone("sumcos_nn_for_all");
        h2pcorrp_nn_all = (TH2D*)h2pcorrp_nn[i][j]->Clone("sumcos2pcorrp_nn_all");
        h2pcorrm_nn_all = (TH2D*)h2pcorrm_nn[i][j]->Clone("sumcos2pcorrm_nn_all");
        hnpairs_nn_all = (TH2D*)hnpairs_nn[i][j]->Clone("npairs_nn_all");
      }
      else
      {
        hcospp_for_all->Add(hcospp_for[i][j]);
        h2pcorrp_pp_all->Add(h2pcorrp_pp[i][j]);
        h2pcorrm_pp_all->Add(h2pcorrm_pp[i][j]);
        hnpairs_pp_all->Add(hnpairs_pp[i][j]);
        hcosnn_for_all->Add(hcosnn_for[i][j]);
        h2pcorrp_nn_all->Add(h2pcorrp_nn[i][j]);
        h2pcorrm_nn_all->Add(h2pcorrm_nn[i][j]);
        hnpairs_nn_all->Add(hnpairs_nn[i][j]);
      }
    }

  TH1D* hq2 = (TH1D*)f->Get("chargedepcorr_ana_HI/q2asscos");

  hcos_for_all = (TH2D*)hcospp_for_all->Clone("sumcos_for_all");
  h2pcorrp_all = (TH2D*)h2pcorrp_pp_all->Clone("sumcos2pcorrp_pp_all");
  h2pcorrm_all = (TH2D*)h2pcorrm_pp_all->Clone("sumcos2pcorrm_pp_all");
  hnpairs_all = (TH2D*)hnpairs_pp_all->Clone("npairs_all");
  hcos_for_all->Add(hcosnn_for_all);
  h2pcorrp_all->Add(h2pcorrp_nn_all);
  h2pcorrm_all->Add(h2pcorrm_nn_all);
  hnpairs_all->Add(hnpairs_nn_all);  

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
/*
  hcos_for_all->Multiply(hnpairs_all);
  h2pcorrp_all->Multiply(hnpairs_all);
  h2pcorrm_all->Multiply(hnpairs_all);
*/
  double cos_tot[48] = {0.0};
  double pcorrp_tot[48] = {0.0};
  double pcorrm_tot[48] = {0.0};
  double cos_tot_err[48] = {0.0};
  double pcorrp_tot_err[48] = {0.0};
  double pcorrm_tot_err[48] = {0.0};
  double npairs_tot[48] = {0.0};
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
    }

  TH1D* hcos_for_all_1D = new TH1D("hcos_for_all_1D","",48,0-0.1/2,4.8-0.1/2);
  TH1D* h2pcorrp_for_all_1D = new TH1D("h2pcorrp_for_all_1D","",48,0-0.1/2,4.8-0.1/2);
  TH1D* h2pcorrm_for_all_1D = new TH1D("h2pcorrm_for_all_1D","",48,0-0.1/2,4.8-0.1/2);
  for(int i=0;i<48;i++)
  {
    hcos_for_all_1D->SetBinContent(i+1,cos_tot[i]/npairs_tot[i]/sqrt(hq2->GetMean()));
    h2pcorrp_for_all_1D->SetBinContent(i+1,pcorrp_tot[i]/npairs_tot[i]);
    h2pcorrm_for_all_1D->SetBinContent(i+1,pcorrm_tot[i]/npairs_tot[i]);
    if(cos_tot_err[i]) hcos_for_all_1D->SetBinError(i+1,sqrt(cos_tot_err[i])/npairs_tot[i]/sqrt(hq2->GetMean()));
    if(pcorrp_tot_err[i]) h2pcorrp_for_all_1D->SetBinError(i+1,sqrt(pcorrp_tot_err[i])/npairs_tot[i]);
    if(pcorrm_tot_err[i]) h2pcorrm_for_all_1D->SetBinError(i+1,sqrt(pcorrm_tot_err[i])/npairs_tot[i]);
  }

  TH2D* htmp = new TH2D("tmp","",1000,0.15,4.8,1000,-0.002,0.002);

  TCanvas* c1 = new TCanvas("c1","c1",900,300);
  c1->Divide(3,1);
  c1->cd(1);
  htmp->Draw();
  hcos_for_all_1D->Draw("PESAME");
  c1->cd(2);
  htmp->Draw();
  h2pcorrp_for_all_1D->Draw("PESAME");
  c1->cd(3);
  htmp->Draw();
  h2pcorrm_for_all_1D->Draw("PESAME");
}
