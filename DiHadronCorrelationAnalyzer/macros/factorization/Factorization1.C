#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"

void Factorization1(TString tag = "UCC", int centmin=110, int centmax=1000)
{
   //TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_%s2011_pixeltracks_INCLEFF1v1_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",tag.Data(),centmin,centmax);
   TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_pixeltracks_INCLEFF1v1Eta1Eta2_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax2.root");
//   TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_UCC2011_INCLEFF1v1Eta1Eta2_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin110_centmax1000.root");
   TFile* fdiff = new TFile(filename.Data());

  TString centtag="";
  if(centmin==110) centtag = "0-0.2% centrality";
  if(centmin==210) centtag = "0-0.02% centrality";
  if(centmin==50) centtag = "0-1% centrality";
  if(centmin==51) centtag = "0-1% centrality";
  if(centmin==0 && centmax==1) centtag = "0-2.5% centrality";
  if(centmin==1 && centmax==2) centtag = "2.5-5% centrality";

  TH2D* hsignal[16][16];
  TH2D* hbackground[16][16];
  TH1D* hsignal_1D[16][16];
  TH1D* hbackground_1D[16][16];

  double Vn[16][16];
  double VnError[16][16];
  double ratio_v2[16][16];
  double ratio_v2_err[16][16];

  int nbin=2;
  for(int i=0;i<16;i++)
  {
    for(int j=0;j<16;j++)
    {
      hsignal[i][j] = (TH2D*)fdiff->Get(Form("signalcosn_eta1eta2_eta%d_eta%d",i,j));
      hbackground[i][j] = (TH2D*)fdiff->Get(Form("backgroundcosn_eta1eta2_eta%d_eta%d",i,j));
      hsignal_1D[i][j] = (TH1D*)hsignal[i][j]->ProfileY(Form("signal_1D_trg%d_ass%d",i,j),-1,-1,"e");
      hbackground_1D[i][j] = (TH1D*)hbackground[i][j]->ProfileY(Form("background_1D_trg%d_ass%d",i,j),-1,-1,"e");

      Vn[i][j]=hsignal_1D[i][j]->GetBinContent(nbin)-hbackground_1D[i][j]->GetBinContent(nbin);
      VnError[i][j]=sqrt(hsignal_1D[i][j]->GetBinError(nbin)*hsignal_1D[i][j]->GetBinError(nbin)+hbackground_1D[i][j]->GetBinError(nbin)*hbackground_1D[i][j]->GetBinError(nbin));
    }
//cout<<sqrt(hcorr_1D[i][i]->GetBinContent(2))<<endl;
  }

  for(int i=0;i<16;i++)
  {
    cout<<Vn[i][i]<<endl;    
    for(int j=0;j<16;j++)
    {
      ratio_v2[i][j]=Vn[i][j]/sqrt(Vn[i][i])/sqrt(Vn[j][j]);
      ratio_v2_err[i][j]=ratio_v2[i][j]*sqrt((VnError[i][j]/Vn[i][j])*(VnError[i][j]/Vn[i][j])+(VnError[i][i]/Vn[i][i])*(VnError[i][i]/Vn[i][i])+(VnError[j][j]/Vn[j][j])*(VnError[j][j]/Vn[j][j]));
    }    
  }


cout<<Vn[0][5]*Vn[10][15]/Vn[0][15]/Vn[5][10]<<endl;
  double eta[16] = {-2.25,-1.95,-1.65,-1.35,-1.05,-0.75,-0.45,-0.15,0.15,0.45,0.75,1.05,1.35,1.65,1.95,2.25};
  double eta_err[16] = {0};
  TGraphErrors* gr_ratio[16];
  for(int i=0;i<16;i++)
  {
    gr_ratio[i] = new TGraphErrors(16,eta,ratio_v2[i],eta_err,ratio_v2_err[i]);
    gr_ratio[i]->SetName(Form("vneta_ratio_%d",i));
//    gr_ratio[i]->SetMarkerColor(i);
  }

  TH2D* htmp = new TH2D("tmp",";#eta;ratio",100,-2.4,2.4,100,0.0,1.5);
  TCanvas* c = new TCanvas("c","c",550,500);
  htmp->Draw("");
  gr_ratio[1]->Draw("PESAME");
}
