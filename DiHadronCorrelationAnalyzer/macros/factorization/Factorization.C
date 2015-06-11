#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"

void Factorization(TString tag = "UCC", int centmin=110, int centmax=1000)
{
  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epptdeco_cent4050_pt033_factorization_eff0_v2.root");
//  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_pixeltracks_INCLEFF1v1_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin16_centmax20.root");
//  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_pixeltracks_INLCEFF1v1_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax2.root");
  TFile* fdiff = new TFile(filename.Data());

  TString centtag="";
  if(centmin==110) centtag = "0-0.2% centrality";
  if(centmin==210) centtag = "0-0.02% centrality";
  if(centmin==50) centtag = "0-1% centrality";
  if(centmin==51) centtag = "0-1% centrality";
  if(centmin==0 && centmax==1) centtag = "0-2.5% centrality";
  if(centmin==1 && centmax==2) centtag = "2.5-5% centrality";

  TH1D* hpt[20];
  TH2D* hsignal[20][20];
  TH2D* hbackground[20][20];
  TH1D* hsignal_1D[20][20];
  TH1D* hbackground_1D[20][20];
  TH1D* hcorr_1D[20][20];
  TH1D* hcorr_dphi[20][20];
  TF1*  fitfunc_vn[20][20];

  double V1[20][20];
  double V1Error[20][20];
  double Vn[20][20];
  double VnError[20][20];
  double ratio_v2[20][20];
  double ratio_v2_err[20][20];
  double pt[20];
  double pt_error[20];

  for(int i=6;i>=0;i--)
  {
    hpt[i] = (TH1D*)fdiff->Get(Form("epptdeco_ana_HI/ptcorr_signal_trg_%d",i));
//    hpt[i] = (TH1D*)fdiff->Get(Form("pt_signal_trg_%d",i));
    pt[i] = hpt[i]->GetMean();
    pt_error[i] = 0.0;
cout<< pt[i] <<endl;   
    for(int j=i;j>=0;j--)
    {

      hsignal[i][j] = (TH2D*)fdiff->Get(Form("epptdeco_ana_HI/signalcosn_trg%d_ass%d",i,j));
      hbackground[i][j] = (TH2D*)fdiff->Get(Form("epptdeco_ana_HI/backgroundcosn_trg%d_ass%d",i,j));
      hsignal_1D[i][j] = (TH1D*)hsignal[i][j]->ProfileY(Form("epptdeco_ana_HI/signal_1D_trg%d_ass%d",i,j),1,-1,"e");
      hbackground_1D[i][j] = (TH1D*)hbackground[i][j]->ProfileY(Form("epptdeco_ana_HI/background_1D_trg%d_ass%d",i,j),1,-1,"e");

/*
      hsignal[i][j] = (TH2D*)fdiff->Get(Form("signalcosn_trg%d_ass%d",i,j));
      hbackground[i][j] = (TH2D*)fdiff->Get(Form("backgroundcosn_trg%d_ass%d",i,j));
      hsignal_1D[i][j] = (TH1D*)hsignal[i][j]->ProfileY(Form("signal_1D_trg%d_ass%d",i,j),1,-1,"e");
      hbackground_1D[i][j] = (TH1D*)hbackground[i][j]->ProfileY(Form("background_1D_trg%d_ass%d",i,j),1,-1,"e");
*/
//if(i==6) cout<<j<<" "<<hsignal_1D[i][j]->GetBinContent(1)<<" "<<hbackground_1D[i][j]->GetBinContent(1)<<endl;
 /*
      Vn[i][j]=hsignal_1D[i][j]->GetBinContent(2)-hbackground_1D[i][j]->GetBinContent(2);
      VnError[i][j]=sqrt(hsignal_1D[i][j]->GetBinError(2)*hsignal_1D[i][j]->GetBinError(2)+hbackground_1D[i][j]->GetBinError(2)*hsignal_1D[i][j]->GetBinError(2));
*/

      Vn[i][j]=hsignal_1D[i][j]->GetBinContent(1)-hbackground_1D[i][j]->GetBinContent(1);
      VnError[i][j]=sqrt(hsignal_1D[i][j]->GetBinError(1)*hsignal_1D[i][j]->GetBinError(1)+hbackground_1D[i][j]->GetBinError(1)*hsignal_1D[i][j]->GetBinError(1));

    }
  }

  for(int i=6;i>=0;i--)
  {
    for(int j=i;j>=0;j--)
    {
      ratio_v2[i][j]=Vn[i][j]/sqrt(Vn[i][i])/sqrt(Vn[j][j]);  
      ratio_v2_err[i][j]=ratio_v2[i][j]*sqrt(VnError[i][j]*VnError[i][j]/Vn[i][j]/Vn[i][j]+0.25*VnError[i][i]*VnError[i][i]/Vn[i][i]/Vn[i][i]+0.25*VnError[j][j]*VnError[j][j]/Vn[j][j]/Vn[j][j]);
if(i==6) cout<<j<<" "<<ratio_v2[i][j]<<" "<<ratio_v2_err[i][j]<<endl;
    }    
  }

  TGraphErrors* gr_ratio[20];
  for(int i=0;i<7;i++)
  {
    gr_ratio[i] = new TGraphErrors(7,pt,ratio_v2[i],pt_error,ratio_v2_err[i]);
//    gr_ratio[i]->SetName(Form("vnpt_ratio_%d",i));
    gr_ratio[i]->SetMarkerColor(i);
  }

  TH2D* htmp = new TH2D("tmp",";p_{T};ratio",100,0,4,100,0.5,1.5);
  TCanvas* c = new TCanvas("c","c",550,500);
  htmp->Draw("");
  gr_ratio[2]->Draw("PESAME");
  gr_ratio[3]->Draw("PESAME");
  gr_ratio[4]->Draw("PESAME");
  gr_ratio[5]->Draw("PESAME");
  gr_ratio[6]->Draw("PESAME");

  TFile* fout = new TFile("r2_cent4050_eff0_v2.root","recreate");
  gr_ratio[6]->Write("rn");
  fout->Close();
}

void compare()
{
  TFile* f_eff0[10];
  f_eff0[6] = new TFile("r3_cent4050_eff0_v2.root");
  f_eff0[5] = new TFile("r3_cent3040_eff0_v2.root");
  f_eff0[4] = new TFile("r3_cent2030_eff0_v2.root");
  f_eff0[3] = new TFile("r3_cent1020_eff0_v2.root");
  f_eff0[2] = new TFile("r3_cent510_eff0_v2.root");
  f_eff0[1] = new TFile("r3_cent05_eff0_v2.root");
  f_eff0[0] = new TFile("r3_cent002_eff0_v2.root");

  TFile* f_eff1[10];
  f_eff1[6] = new TFile("r3_cent4050_eff1_v2.root");
  f_eff1[5] = new TFile("r3_cent3040_eff1_v2.root");
  f_eff1[4] = new TFile("r3_cent2030_eff1_v2.root");
  f_eff1[3] = new TFile("r3_cent1020_eff1_v2.root");
  f_eff1[2] = new TFile("r3_cent510_eff1_v2.root");
  f_eff1[1] = new TFile("r3_cent05_eff1_v2.root");
  f_eff1[0] = new TFile("r3_cent002_eff1_v2.root");

  TGraphErrors* gr_eff0[10];
  TGraphErrors* gr_eff1[10];
  for(int i=0;i<7;i++)
  {
    gr_eff0[i] = (TGraphErrors)f_eff0[i]->Get("rn"); 
    gr_eff1[i] = (TGraphErrors)f_eff1[i]->Get("rn");
  }
  
  TH2D* htmp = new TH2D("htmp","",1000,0,3.0,1000,0.75,1.05); 

  TCanvas* c = new TCanvas("c","",800,400);
  c->Divide(4,2);
  for(int i=0;i<7;i++)
  {
    c->cd(i+1);
    htmp->Draw();
    gr_eff0[i]->SetMarkerColor(1);
    gr_eff1[i]->SetMarkerColor(2);
    gr_eff0[i]->SetMarkerStyle(20);
    gr_eff1[i]->SetMarkerStyle(20);
    gr_eff0[i]->Draw("PESAME");
    gr_eff1[i]->Draw("PESAME");
  }
 
}
