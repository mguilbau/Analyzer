#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/makeMultiPanelCanvas.C"

void Factorization_eta_v2v3_paper()
{
  const int nfiles = 24;
  TString filename[nfiles];

  filename[0] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent002_pttrg033_ptassallweight_etaass445_eff1_v42.root");
  filename[1] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent05_pttrg033_ptassallweight_etaass445_eff1_v42.root");
  filename[2] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent510_pttrg033_ptassallweight_etaass445_eff1_v42.root");
  filename[3] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent1020_pttrg033_ptassallweight_etaass445_eff1_v42.root");
  filename[4] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent2030_pttrg033_ptassallweight_etaass445_eff1_v42.root");
  filename[5] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent3040_pttrg033_ptassallweight_etaass445_eff1_v42.root");
  filename[6] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent4050_pttrg033_ptassallweight_etaass445_eff1_v42.root");
  filename[7] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent5060_pttrg033_ptassallweight_etaass445_eff1_v42.root");
/*
  filename[0] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent002_pttrg053_ptassallweight_etaass445_eff0_general_v45.root");
  filename[1] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent05_pttrg053_ptassallweight_etaass445_eff0_general_v45.root");
  filename[2] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent510_pttrg053_ptassallweight_etaass445_eff0_general_v45.root");
  filename[3] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent1020_pttrg053_ptassallweight_etaass445_eff0_general_v45.root");
  filename[4] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent2030_pttrg053_ptassallweight_etaass445_eff0_general_v45.root");
  filename[5] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent3040_pttrg053_ptassallweight_etaass445_eff0_general_v45.root");
  filename[6] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent4050_pttrg053_ptassallweight_etaass445_eff0_general_v45.root");
  filename[7] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent5060_pttrg053_ptassallweight_etaass445_eff0_general_v45.root");
*/
  filename[8] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent002_pttrg033_ptassallweight_etaass34_eff1_v42.root");
  filename[9] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent05_pttrg033_ptassallweight_etaass34_eff1_v42.root");
  filename[10] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent510_pttrg033_ptassallweight_etaass34_eff1_v42.root");
  filename[11] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent1020_pttrg033_ptassallweight_etaass34_eff1_v42.root");
  filename[12] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent2030_pttrg033_ptassallweight_etaass34_eff1_v42.root");
  filename[13] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent3040_pttrg033_ptassallweight_etaass34_eff1_v42.root");
  filename[14] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent4050_pttrg033_ptassallweight_etaass34_eff1_v42.root");
  filename[15] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent5060_pttrg033_ptassallweight_etaass34_eff1_v42.root");

  filename[16] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent002_pttrg033_ptassallweight_etaass45_eff1_v42.root");
  filename[17] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent05_pttrg033_ptassallweight_etaass45_eff1_v42.root");
  filename[18] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent510_pttrg033_ptassallweight_etaass45_eff1_v42.root");
  filename[19] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent1020_pttrg033_ptassallweight_etaass45_eff1_v42.root");
  filename[20] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent2030_pttrg033_ptassallweight_etaass45_eff1_v42.root");
  filename[21] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent3040_pttrg033_ptassallweight_etaass45_eff1_v42.root");
  filename[22] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent4050_pttrg033_ptassallweight_etaass45_eff1_v42.root");
  filename[23] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent5060_pttrg033_ptassallweight_etaass45_eff1_v42.root");

  const int ntrgbins = 16;
  const int ntrgbins1 = ntrgbins;
  const int ntrgbins2 = ntrgbins/2;
  TGraphErrors* gr[nfiles][6];
  TGraphErrors* gr0[nfiles][6];
  TGraphErrors* gr1[nfiles][6];
  TGraphErrors* gr_ratio[nfiles][6];
  TGraph* gr_band[nfiles][6];
  TGraph* gr1_band[nfiles][6];
  TF1* fit[nfiles][6];
  TF1* fit_aver[nfiles][6];
  TF1* fit1_aver[nfiles][6];
  double slope[6][nfiles];
  double slope_err[6][nfiles];
  double slope1[6][nfiles];
  double slope1_err[6][nfiles];
//  double eta[ntrgbins2] = {0.12,0.36,0.6,0.84,1.08,1.32,1.56,1.8,2.04,2.28};
//  double eta[ntrgbins2] = {0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3};  
  double eta[ntrgbins2] = {0.15,0.45,0.75,1.05,1.35,1.65,1.95,2.25};
//  double eta[ntrgbins2] = {0.2,0.6,1.0,1.4,1.8,2.2};
  double eta_err[ntrgbins2] = {0.0};
  Color_t color[6] = {1,kBlue, kBlue, kBlue,1,1};

  TFile* fdiff[nfiles];
for(int jj=0;jj<nfiles;jj++)
{
  fdiff[jj] = new TFile(filename[jj].Data());

  TH2D* hsignal[ntrgbins];
  TH2D* hbackground[ntrgbins];
  TH2D* hsignal0[ntrgbins];
  TH2D* hbackground0[ntrgbins];
  TH2D* hsignal1[ntrgbins];
  TH2D* hbackground1[ntrgbins];
  TH1D* hsignal_1D[ntrgbins][6];
  TH1D* hbackground_1D[ntrgbins][6]; 
  TH1D* hsignal0_1D[ntrgbins][6];
  TH1D* hbackground0_1D[ntrgbins][6];
  TH1D* hsignal1_1D[ntrgbins][6];
  TH1D* hbackground1_1D[ntrgbins][6];

  double Vn[ntrgbins1][6];
  double VnError[ntrgbins1][6];
  double rn[ntrgbins2];
  double rn_err[ntrgbins2];
  double Vn0[ntrgbins1][6];
  double Vn0Error[ntrgbins1][6];
  double rn0[ntrgbins2];
  double rn0_err[ntrgbins2];
  double Vn1[ntrgbins1][6];
  double Vn1Error[ntrgbins1][6];
  double rn1[ntrgbins2];
  double rn1_err[ntrgbins2];
  double rn_ratio[ntrgbins2];
  double rn_ratio_err[ntrgbins2];

  for(int i=0;i<ntrgbins;i++)
  {
    hsignal0[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfp/signalcosn_trg%d",i));
    hbackground0[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfp/backgroundcosn_trg%d",i));
    hsignal1[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfm/signalcosn_trg%d",i));
    hbackground1[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfm/backgroundcosn_trg%d",i));
/*
    if(jj==6 || jj==7)
    {
      hsignal0[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_pPb_hfp/signalcosn_trg%d",i));
      hbackground0[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_pPb_hfp/backgroundcosn_trg%d",i));
      hsignal1[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_pPb_hfm/signalcosn_trg%d",i));
      hbackground1[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_pPb_hfm/backgroundcosn_trg%d",i));
    }
*/
    hsignal[i] = (TH2D*)hsignal0[i]->Clone(Form("signalcosn_trg%d",i));
    hbackground[i] = (TH2D*)hbackground0[i]->Clone(Form("backgroundcosn_trg%d",i));
    hsignal[i]->Add(hsignal1[i]);
    hbackground[i]->Add(hbackground1[i]);

    for(int nbin=1;nbin<4;nbin++)
    {
      hsignal_1D[i][nbin] = (TH1D*)hsignal[i]->ProjectionX(Form("signal_1D_trg%d_%d",i,nbin),nbin,nbin,"e");
      hsignal0_1D[i][nbin] = (TH1D*)hsignal0[i]->ProjectionX(Form("signal0_1D_trg%d_%d",i,nbin),nbin,nbin,"e");
      hsignal1_1D[i][nbin] = (TH1D*)hsignal1[i]->ProjectionX(Form("signal1_1D_trg%d_%d",i,nbin),nbin,nbin,"e");
      hbackground_1D[i][nbin] = (TH1D*)hbackground[i]->ProjectionX(Form("background_1D_trg%d_%d",i,nbin),nbin,nbin,"e");
      hbackground0_1D[i][nbin] = (TH1D*)hbackground0[i]->ProjectionX(Form("background0_1D_trg%d_%d",i,nbin),nbin,nbin,"e");
      hbackground1_1D[i][nbin] = (TH1D*)hbackground1[i]->ProjectionX(Form("background1_1D_trg%d_%d",i,nbin),nbin,nbin,"e");

      Vn[i][nbin]=hsignal_1D[i][nbin]->GetMean()-hbackground_1D[i][nbin]->GetMean();
      VnError[i][nbin]=sqrt(hsignal_1D[i][nbin]->GetMeanError()*hsignal_1D[i][nbin]->GetMeanError()+hbackground_1D[i][nbin]->GetMeanError()*hbackground_1D[i][nbin]->GetMeanError());
      Vn0[i][nbin]=hsignal0_1D[i][nbin]->GetMean()-hbackground0_1D[i][nbin]->GetMean();
      Vn0Error[i][nbin]=sqrt(hsignal0_1D[i][nbin]->GetMeanError()*hsignal0_1D[i][nbin]->GetMeanError()+hbackground0_1D[i][nbin]->GetMeanError()*hbackground0_1D[i][nbin]->GetMeanError());
      Vn1[i][nbin]=hsignal1_1D[i][nbin]->GetMean()-hbackground1_1D[i][nbin]->GetMean();
      Vn1Error[i][nbin]=sqrt(hsignal1_1D[i][nbin]->GetMeanError()*hsignal1_1D[i][nbin]->GetMeanError()+hbackground1_1D[i][nbin]->GetMeanError()*hbackground1_1D[i][nbin]->GetMeanError());

if(jj==7 && nbin==1) cout<<"pos nbin="<<nbin<<" i="<<i<<" "<<hsignal0_1D[i][nbin]->GetMean()<<" "<<hbackground0_1D[i][nbin]->GetMean()<<" "<<Vn0[i][nbin]<<endl;
if(jj==7 && nbin==1) cout<<"neg nbin="<<nbin<<" i="<<i<<" "<<hsignal1_1D[i][nbin]->GetMean()<<" "<<hbackground1_1D[i][nbin]->GetMean()<<" "<<Vn1[i][nbin]<<endl;

      delete hsignal_1D[i][nbin];
      delete hsignal0_1D[i][nbin];
      delete hsignal1_1D[i][nbin];
      delete hbackground_1D[i][nbin];
      delete hbackground0_1D[i][nbin];
      delete hbackground1_1D[i][nbin];
    }
    delete hsignal0[i];
    delete hsignal1[i];
    delete hsignal[i];
    delete hbackground0[i];
    delete hbackground1[i];
    delete hbackground[i];
  }

  for(int nbin=1;nbin<4;nbin++)
  {
    for(int i=0;i<ntrgbins2;i++)
    {
      rn[ntrgbins2-i-1]=Vn[i][nbin]/Vn[ntrgbins1-i-1][nbin];
      rn_err[ntrgbins2-i-1]=sqrt((VnError[ntrgbins1-i-1][nbin]/Vn[ntrgbins1-i-1][nbin])**2+(VnError[i][nbin]/Vn[i][nbin])**2);
      rn0[ntrgbins2-i-1]=Vn0[i][nbin]/Vn0[ntrgbins1-i-1][nbin];
      rn0_err[ntrgbins2-i-1]=sqrt((Vn0Error[ntrgbins1-i-1][nbin]/Vn0[ntrgbins1-i-1][nbin])**2+(Vn0Error[i][nbin]/Vn0[i][nbin])**2);
      rn1[ntrgbins2-i-1]=Vn1[i][nbin]/Vn1[ntrgbins1-i-1][nbin];
      rn1_err[ntrgbins2-i-1]=sqrt((Vn1Error[ntrgbins1-i-1][nbin]/Vn1[ntrgbins1-i-1][nbin])**2+(Vn1Error[i][nbin]/Vn1[i][nbin])**2);
      rn_ratio[ntrgbins2-i-1] = rn0[ntrgbins2-i-1]/rn1[ntrgbins2-i-1];
      rn_ratio_err[ntrgbins2-i-1] = sqrt(rn0_err[ntrgbins2-i-1]*rn0_err[ntrgbins2-i-1]+rn1_err[ntrgbins2-i-1]*rn1_err[ntrgbins2-i-1]);

if(jj==7 && nbin==1) cout<<"pos nbin="<<nbin<<" i="<<i<<" "<<Vn0[i][nbin]<<" "<<Vn0[ntrgbins1-i-1][nbin]<<" "<<rn0[ntrgbins2-i-1]<<endl;
if(jj==7 && nbin==1) cout<<"neg nbin="<<nbin<<" i="<<i<<" "<<Vn1[i][nbin]<<" "<<Vn1[ntrgbins1-i-1][nbin]<<" "<<rn1[ntrgbins2-i-1]<<endl;

    }

    gr[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rn,eta_err,rn_err);
    gr[jj][nbin]->SetMarkerColor(color[nbin]);
    gr0[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rn0,eta_err,rn0_err);
    gr0[jj][nbin]->SetMarkerColor(color[nbin]);
    gr1[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rn1,eta_err,rn1_err);
    gr1[jj][nbin]->SetMarkerColor(color[nbin]);
    gr_ratio[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rn_ratio,eta_err,rn_ratio_err);
    gr_ratio[jj][nbin]->SetMarkerColor(color[nbin]);
/*
    gr[jj][nbin]->SetMarkerSize(gr[jj][1]->GetMarkerSize()*0.8);
    gr0[jj][nbin]->SetMarkerSize(gr0[jj][1]->GetMarkerSize()*0.8);
    gr1[jj][nbin]->SetMarkerSize(gr1[jj][1]->GetMarkerSize()*0.8);
    gr_ratio[jj][nbin]->SetMarkerSize(gr_ratio[jj][1]->GetMarkerSize()*0.8);
*/
//    fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"(1+[0]*(-x-4.5)*(-x-4.5))/(1+[0]*(x-4.5)*(x-4.5))",0,3.0);
//    fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"(1+[0]*(-x-4.5))/(1+[0]*(x-4.5))",0,3.0);
    if(jj<8) fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"exp([0]*(-x-4.6))/exp([0]*(x-4.6))",0.0,2.4);
    else fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"exp([0]*(-x-3.5))/exp([0]*(x-3.5))",0.0,1.1);
    fit[jj][nbin]->SetParameter(0,0.01);
    gr[jj][nbin]->Fit(Form("fit_%d_%d",nbin,jj),"RNO");
    fit[jj][nbin]->SetLineColor(color[nbin]);
    fit[jj][nbin]->SetLineStyle(7);
    fit[jj][nbin]->SetLineWidth(1);
    if(jj<8)
    {    
      slope[nbin][jj] = fit[jj][nbin]->GetParameter(0);
      slope_err[nbin][jj] = fit[jj][nbin]->GetParError(0);
    }
    else
    {
      slope1[nbin][jj-8] = fit[jj][nbin]->GetParameter(0);
      slope1_err[nbin][jj-8] = fit[jj][nbin]->GetParError(0);
    }     

//    fit1_aver[jj][nbin] = new TF1(Form("fit1_aver_%d_%d",nbin,jj),"(1+[0]*(-x-4.5))/(1-4.5*[0])",0,4.5);
    fit1_aver[jj][nbin] = new TF1(Form("fit1_aver_%d_%d",nbin,jj),"exp(-[0]*x)",0,5);
    fit1_aver[jj][nbin]->SetParameter(0,fit[jj][nbin]->GetParameter(0));
    fit1_aver[jj][nbin]->SetParError(0,fit[jj][nbin]->GetParError(0));    
    fit1_aver[jj][nbin]->SetLineStyle(1);
    fit1_aver[jj][nbin]->SetLineColor(color[nbin]);
    gr1_band[jj][nbin] = new TGraph(53);
    for(int mm=0;mm<26;mm++) 
    {
      gr1_band[jj][nbin]->SetPoint(mm,0.2*mm,exp(-0.2*mm*(fit1_aver[jj][nbin]->GetParameter(0)+fit1_aver[jj][nbin]->GetParError(0))));
      gr1_band[jj][nbin]->SetPoint(51-mm,0.2*mm,exp(-0.2*mm*(fit1_aver[jj][nbin]->GetParameter(0)-fit1_aver[jj][nbin]->GetParError(0))));
    }
    gr1_band[jj][nbin]->SetPoint(52,0,1);
    gr1_band[jj][nbin]->SetFillColor(color[nbin]-10);
  }
}

  ofstream ff("r2r3_eta.txt");

  double cent[8]={0.01,0.025,0.075,0.15,0.25,0.35,0.45,0.55};
  double cent_err[8]={0};
  TGraphErrors* gr_slope[6];
  TGraphErrors* gr1_slope[6];
  for(int nbin=1;nbin<4;nbin++) {
    gr_slope[nbin] = new TGraphErrors(8,cent,slope[nbin],cent_err,slope_err[nbin]);
    gr_slope[nbin]->SetName(Form("gr_slope_%d",nbin));
    cout<<"i="<<nbin+1<<endl;
    ff<<"i="<<nbin+1<<endl;
    for(int j=0;j<8;j++) { cout<<slope[nbin][j]<<" "; ff<<slope[nbin][j]<<", ";}
    cout<<endl;
    ff<<endl;
    for(int j=0;j<8;j++) { cout<<slope_err[nbin][j]<<" "; ff<<slope_err[nbin][j]<<", ";}
    cout<<endl;
    ff<<endl;
  }
  for(int nbin=1;nbin<4;nbin++) {
    gr1_slope[nbin] = new TGraphErrors(8,cent,slope1[nbin],cent_err,slope1_err[nbin]);
    gr1_slope[nbin]->SetName(Form("gr1_slope_%d",nbin));
  }

  ff.close();

  TString histtitle[8] = {"0-0.2% centrality","0-5%","5-10%","10-20%","20-30%","30-40%","40-50%","50-60%"};
  TLine* ll = new TLine(-0.12,1.,2.49,1.);
  TCanvas* c = new TCanvas("c","c",920,500);
  makeMultiPanelCanvas(c,4,2,0.01,0.0,0.25,0.2,0.02);
  TH2D* htmp = new TH2D("htmp",";#eta^{a};r_{2}(#eta^{a},#eta^{b})",100,-0.12,2.49,100,0.831-0.02,1.06-0.02);
  fixedFontHist(htmp,1.8,2.8);
  htmp->GetXaxis()->CenterTitle();
  htmp->GetYaxis()->CenterTitle();
  htmp->GetYaxis()->SetTitleSize(htmp->GetYaxis()->GetTitleSize()*1.2);
  htmp->GetXaxis()->SetTitleSize(htmp->GetXaxis()->GetTitleSize()*1.);
  htmp->GetXaxis()->SetLabelSize(htmp->GetXaxis()->GetLabelSize()*0.95);
  htmp->GetXaxis()->SetNdivisions(510);

  for(int jj=0;jj<8;jj++)
  {
    c->cd(jj+1);
    htmp->Draw();
    ll->Draw("Lsame");
    gr[jj][1]->SetMarkerStyle(21);
    gr[jj][1]->Draw("Psame");
    fit[jj][1]->Draw("Lsame");
    cout<<fit[jj][1]->GetChisquare()/fit[jj][1]->GetNDF()<<endl;

    gr[jj+8][1]->SetMarkerStyle(25);
//    fit[jj+8][1]->SetLineStyle(5);
    gr[jj+8][1]->Draw("Psame");
//    fit[jj+8][1]->Draw("Lsame");
/*
    gr[jj+16][1]->SetMarkerStyle(28);
    gr[jj+16][1]->SetMarkerColor(1);
    gr[jj+16][1]->Draw("Psame");
*/
  }

  TLatex* latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(1.5*latex2->GetTextSize());
  c->cd(1);
  latex2->DrawLatex(0.31,0.05,histtitle[0]);
  latex2->DrawLatex(0.29,0.865,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV");
  c->cd(2);
  latex2->DrawLatex(0.08,0.05,histtitle[1]);
  latex2->SetTextSize(0.98*latex2->GetTextSize());
  latex2->DrawLatex(0.1,0.285,"0.3 < p_{T}^{a} < 3.0 GeV/c");
  latex2->DrawLatex(0.1,0.18,"p_{T}^{b} > 0 GeV/c");
  latex2->SetTextSize(latex2->GetTextSize()/0.98);
  c->cd(4);
  latex2->DrawLatex(0.08,0.05,histtitle[3]);
  c->cd(3);
  latex2->DrawLatex(0.08,0.05,histtitle[2]);
  c->cd(8);
  latex2->DrawLatex(0.08,0.24,histtitle[7]);
  c->cd(7);
  latex2->DrawLatex(0.08,0.24,histtitle[6]);
  c->cd(6);
  latex2->SetTextSize(0.96*latex2->GetTextSize());
  latex2->DrawLatex(0.08,0.24,histtitle[5]);
  c->cd(5);
  latex2->SetTextSize(0.85*latex2->GetTextSize());
  latex2->DrawLatex(0.31,0.24,histtitle[4]);

  TLegend* legend2 = new TLegend(0.26,0.16,0.78,0.46);
  legend2->SetFillStyle(0);
  legend2->AddEntry(gr[0][1],"4.4 < #eta^{b} < 5.0","P");
  legend2->AddEntry(gr[8][1],"3.0 < #eta^{b} < 4.0","P");
  legend2->AddEntry(fit[0][1],"Exponential fits","L");
  c->cd(1);
  legend2->Draw("same");

  TCanvas* ccaa = new TCanvas("ccaa","ccaa",900,500);
  makeMultiPanelCanvas(ccaa,4,2,0.01,0.0,0.2,0.2,0.02);
  for(int jj=0;jj<8;jj++)
  {
    ccaa->cd(jj+1);
    htmp->Draw();
    ll->Draw("Lsame");
    gr0[jj][1]->SetMarkerStyle(21);
    gr0[jj][1]->Draw("Psame");
    gr1[jj][1]->SetMarkerStyle(25);
    gr1[jj][1]->Draw("Psame");
  }

  TCanvas* ccbb = new TCanvas("ccbb","ccbb",900,500);
  makeMultiPanelCanvas(ccbb,4,2,0.01,0.0,0.2,0.2,0.02);
  TH2D* htmpaa = new TH2D("htmpaa",";#eta^{a};r_{2}(#eta^{a},#eta^{b})",100,-0.1,2.5,100,0.97,1.03);
  for(int jj=0;jj<8;jj++)
  {
    ccbb->cd(jj+1);
    htmpaa->Draw();
    ll->Draw("Lsame");
    gr_ratio[jj][1]->SetMarkerStyle(21);
    gr_ratio[jj][1]->Draw("Psame");
  }

  TCanvas* cc = new TCanvas("cc","cc",920,500);
  makeMultiPanelCanvas(cc,4,2,0.01,0.0,0.25,0.2,0.02);
  TH2D* htmp1 = new TH2D("htmp1",";#eta^{a};r_{3}(#eta^{a},#eta^{b})",100,-0.12,2.49,100,0.831-0.02,1.06-0.02);
  fixedFontHist(htmp1,1.8,2.8);
  htmp1->GetXaxis()->CenterTitle();
  htmp1->GetYaxis()->CenterTitle();
  htmp1->GetYaxis()->SetTitleSize(htmp1->GetYaxis()->GetTitleSize()*1.2);
  htmp1->GetXaxis()->SetTitleSize(htmp1->GetXaxis()->GetTitleSize()*1.);
  htmp1->GetXaxis()->SetLabelSize(htmp1->GetXaxis()->GetLabelSize()*0.95);
  htmp1->GetXaxis()->SetNdivisions(510);

  for(int jj=0;jj<8;jj++)
  {
    cc->cd(jj+1);
    htmp1->Draw();
    ll->Draw("Lsame");
    gr[jj][2]->SetMarkerStyle(21);
    gr[jj][2]->Draw("Psame");
    fit[jj][2]->Draw("Lsame");
    cout<<fit[jj][2]->GetChisquare()/fit[jj][2]->GetNDF()<<endl;

    gr[jj+8][2]->SetMarkerStyle(25);
//    fit[jj+8][2]->SetLineStyle(5);
    gr[jj+8][2]->Draw("Psame");
//    fit[jj+8][2]->Draw("Lsame");
/*
    gr[jj+16][2]->SetMarkerStyle(28);
    gr[jj+16][2]->SetMarkerColor(1);
    gr[jj+16][2]->Draw("Psame");
    fit[jj+16][2]->Draw("Lsame");
*/
  }

  TLatex* latex3 = new TLatex();
  latex3->SetNDC();
  latex3->SetTextSize(1.5*latex3->GetTextSize());
  cc->cd(1);
  latex3->DrawLatex(0.31,0.05,histtitle[0]);
  latex3->DrawLatex(0.29,0.865,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV");
  cc->cd(2);
  latex3->DrawLatex(0.08,0.05,histtitle[1]);
  latex3->SetTextSize(0.98*latex3->GetTextSize());
  latex3->DrawLatex(0.1,0.285,"0.3 < p_{T}^{a} < 3.0 GeV/c");
  latex3->DrawLatex(0.1,0.18,"p_{T}^{b} > 0 GeV/c");
  latex3->SetTextSize(latex3->GetTextSize()/0.98);
  cc->cd(4);
  latex3->DrawLatex(0.08,0.05,histtitle[3]);
  cc->cd(3);
  latex3->DrawLatex(0.08,0.05,histtitle[2]);
  cc->cd(8);
  latex3->DrawLatex(0.08,0.24,histtitle[7]);
  cc->cd(7);
  latex3->DrawLatex(0.08,0.24,histtitle[6]);
  cc->cd(6);
  latex3->SetTextSize(0.96*latex3->GetTextSize());
  latex3->DrawLatex(0.08,0.24,histtitle[5]);
  cc->cd(5);
  latex3->SetTextSize(0.85*latex3->GetTextSize());
  latex3->DrawLatex(0.31,0.24,histtitle[4]);

  TLegend* legend3 = new TLegend(0.26,0.16,0.78,0.46);
  legend3->SetFillStyle(0);
  legend3->AddEntry(gr[0][1],"4.4 < #eta^{b} < 5.0","P");
//  legend3->AddEntry(gr[16][1],"4<#eta^{b}<5","P");
  legend3->AddEntry(gr[8][1],"3.0 < #eta^{b} < 4.0","P");
  legend3->AddEntry(fit[0][1],"Exponential fits","L");
  cc->cd(1);
  legend3->Draw("same");
/*
  TCanvas* ccc = new TCanvas("ccc","ccc",900,500);
  makeMultiPanelCanvas(ccc,4,2,0.01,0.0,0.2,0.2,0.02);
  TH2D* htmp2 = new TH2D("htmp2",";#eta^{a};r_{4}(#eta^{a},#eta^{b})",100,-0.1,2.23,100,0.801,1.06);
  fixedFontHist(htmp2,1.8,2.2);
  htmp2->GetXaxis()->CenterTitle();
  htmp2->GetYaxis()->CenterTitle();
  htmp2->GetYaxis()->SetTitleSize(htmp2->GetYaxis()->GetTitleSize()*1.2);
  htmp2->GetXaxis()->SetTitleSize(htmp2->GetXaxis()->GetTitleSize()*1.);
  for(int jj=0;jj<8;jj++)
  {
    ccc->cd(jj+1);
    htmp2->Draw();
    ll->Draw("Lsame");
    gr[jj][3]->Draw("Psame");
    fit[jj][3]->Draw("Lsame");

    gr[jj+8][3]->Set_arkerStyle(25);
    fit[jj+8][3]->SetLineStyle(5);
    gr[jj+8][3]->Draw("Psame");
    fit[jj+8][3]->Draw("Lsame");
  }
*/
  SaveCanvas(c,"HI/FactBreak","epetadeco_HI_r2");
  SaveCanvas(cc,"HI/FactBreak","epetadeco_HI_r3");
return;
  TCanvas* c1 = new TCanvas("c1","c1",500,500);
  TH2D* htmp2 = new TH2D("htmp2",";Centrality;C",100,0,1.0,100,0.0,0.06);
  htmp2->Draw();
  htmp2->GetXaxis()->CenterTitle();
  htmp2->GetYaxis()->CenterTitle();
  gr_slope[1]->SetMarkerColor(1);
  gr_slope[2]->SetMarkerColor(1);
  gr_slope[1]->SetMarkerStyle(21);
  gr_slope[2]->SetMarkerStyle(22);
  gr_slope[1]->Draw("PESAME");
  gr_slope[2]->Draw("PESAME");
  gr1_slope[1]->SetMarkerColor(1);
  gr1_slope[2]->SetMarkerColor(1);
  gr1_slope[1]->SetMarkerStyle(25);
  gr1_slope[2]->SetMarkerStyle(26);
  gr1_slope[1]->Draw("PESAME");
  gr1_slope[2]->Draw("PESAME");

  TFile* f_slope_out = new TFile("gr_slope_v2v3.root","recreate");
  gr_slope[1]->Write();
  gr_slope[2]->Write();
  gr1_slope[1]->Write();
  gr1_slope[2]->Write();
  f_slope_out->Close();

  double c2th_05[4] = {1,0.961347696746,0.880663601763,0.754486161464};
  double c2th_05_err[4] = {0,0.000356333410703,0.000338330912667,0.000274987058522};
  double c2th_510[4] = {1,0.972713667246,0.915076778092,0.833525975859};
  double c2th_510_err[4] = {0,0.000405999641418,0.000387338629763,0.000306789774481};
  double c2th_2025[4] = {1,0.984223594381,0.952359517332,0.902163004038};
  double c2th_2025_err[4] = {0,0.00034410202865,0.000327502849547,0.000264412975357};

  double c3th_05[4] = {1,0.969266017011,0.906673110779,0.811457263278};
  double c3th_05_err[4] = {0,0.000169783126377,0.000162733412441,0.000127976935994};
  double c3th_510[4] = {1,0.967235903665,0.902375220756,0.794138304113};
  double c3th_510_err[4] = {0,0.000140808705408,0.000136143144565,0.000110350606241};
  double c3th_2025[4] = {1,0.969550353187,0.904351369862,0.80580447205};
  double c3th_2025_err[4] = {0,9.57789409787e-05,9.14453396096e-05,7.07914090744e-05};

  double etath[4] = {0,0.5,1,2};
  double etath_err[4] = {0};

  TGraphErrors* gr_c2th_05 = new TGraphErrors(4,etath,c2th_05,etath_err,c2th_05_err);
  TGraphErrors* gr_c2th_510 = new TGraphErrors(4,etath,c2th_510,etath_err,c2th_510_err);
  TGraphErrors* gr_c2th_2025 = new TGraphErrors(4,etath,c2th_2025,etath_err,c2th_2025_err);
  TGraphErrors* gr_c3th_05 = new TGraphErrors(4,etath,c3th_05,etath_err,c3th_05_err);
  TGraphErrors* gr_c3th_510 = new TGraphErrors(4,etath,c3th_510,etath_err,c3th_510_err);
  TGraphErrors* gr_c3th_2025 = new TGraphErrors(4,etath,c3th_2025,etath_err,c3th_2025_err);
  gr_c2th_05->SetMarkerStyle(31);
  gr_c2th_510->SetMarkerStyle(31);
  gr_c2th_2025->SetMarkerStyle(31);
  gr_c3th_05->SetMarkerStyle(31);
  gr_c3th_510->SetMarkerStyle(31);
  gr_c3th_2025->SetMarkerStyle(31);

  TCanvas* cth = new TCanvas("cth","",900,330);
  makeMultiPanelCanvas(cth,3,1,0.01,0.0,0.2,0.17,0.02);
  TH2D* htmp8 = new TH2D("htmp8",";#eta^{a};r_{2}(#eta^{a},#eta^{b})",100,-0.1,2.5,100,0.67,1.06);
  fixedFontHist(htmp8,0.9,1.3);
  htmp8->GetXaxis()->CenterTitle();
  htmp8->GetYaxis()->CenterTitle();
  htmp8->GetYaxis()->SetTitleSize(htmp8->GetYaxis()->GetTitleSize()*1.4);
  htmp8->GetXaxis()->SetTitleSize(htmp8->GetXaxis()->GetTitleSize()*1.2);
  cth->cd(1);
  htmp8->Draw();
  ll->Draw("Lsame");
  gr[1][1]->SetMarkerStyle(20);
  gr[1][1]->Draw("Psame");
  gr_c2th_05->Draw("LPsame");
  cth->cd(2);
  htmp8->Draw();
  ll->Draw("Lsame");
  gr[2][1]->SetMarkerStyle(20);
  gr[2][1]->Draw("Psame");
  gr_c2th_510->Draw("LPsame");
  cth->cd(3);
  htmp8->Draw();
  ll->Draw("Lsame");
  gr[4][1]->SetMarkerStyle(20);
  gr[4][1]->Draw("Psame");
  gr_c2th_2025->Draw("LPsame");

  TLegend* legend_cth = new TLegend(0.25,0.24,0.75,0.4);
  legend_cth->SetFillStyle(0);
  legend_cth->AddEntry(gr[1][1],"Data","P");
  legend_cth->AddEntry(gr_c2th_05,"3D hydro. model","PL");
  cth->cd(1);
  legend_cth->Draw("same");

  TLatex* latex8 = new TLatex();
  latex8->SetNDC();
  latex8->SetTextSize(latex3->GetTextSize());
  cth->cd(1);
  latex8->DrawLatex(0.8,0.25,histtitle[1]);
  latex8->DrawLatex(0.285,0.88,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV");
  cth->cd(2);
  latex8->DrawLatex(0.68,0.25,histtitle[2]);
  latex8->DrawLatex(0.07,0.45,"4.4 < #eta^{b} < 5");
  latex8->DrawLatex(0.07,0.35,"0.3 < p_{T}^{a} < 3 GeV/c");
  latex8->DrawLatex(0.07,0.25,"p_{T}^{b} > 0 GeV/c");
  cth->cd(3);
  latex8->DrawLatex(0.68,0.25,histtitle[4]);

  TCanvas* cth3 = new TCanvas("cth3","",900,330);
  makeMultiPanelCanvas(cth3,3,1,0.01,0.0,0.2,0.17,0.02);
  TH2D* htmp9 = new TH2D("htmp9",";#eta^{a};r_{3}(#eta^{a},#eta^{b})",100,-0.12,2.49,100,0.7,1.06);
  fixedFontHist(htmp9,0.9,1.3);
  htmp9->GetXaxis()->CenterTitle();
  htmp9->GetYaxis()->CenterTitle();
  htmp9->GetYaxis()->SetTitleSize(htmp9->GetYaxis()->GetTitleSize()*1.4);
  htmp9->GetXaxis()->SetTitleSize(htmp9->GetXaxis()->GetTitleSize()*1.2);
  cth3->cd(1);
  htmp9->Draw();
  ll->Draw("Lsame");
  gr[1][2]->SetMarkerStyle(20);
  gr[1][2]->Draw("Psame");
  gr_c3th_05->Draw("LPsame");
  cth3->cd(2);
  htmp9->Draw();
  ll->Draw("Lsame");
  gr[2][2]->SetMarkerStyle(20);
  gr[2][2]->Draw("Psame");
  gr_c3th_510->Draw("LPsame");
  cth3->cd(3);
  htmp9->Draw();
  ll->Draw("Lsame");
  gr[4][2]->SetMarkerStyle(20);
  gr[4][2]->Draw("Psame");
  gr_c3th_2025->Draw("LPsame");
  cth3->cd(1);
  legend_cth->Draw("same");

  cth3->cd(1);
  latex8->DrawLatex(0.8,0.25,histtitle[1]);
  latex8->DrawLatex(0.285,0.88,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV");
  cth3->cd(2);
  latex8->DrawLatex(0.68,0.25,histtitle[2]);
  latex8->DrawLatex(0.07,0.45,"4.4 < #eta^{b} < 5");
  latex8->DrawLatex(0.07,0.35,"0.3 < p_{T}^{a} < 3 GeV/c");
  latex8->DrawLatex(0.07,0.25,"p_{T}^{b} > 0 GeV/c");
  cth3->cd(3);
  latex8->DrawLatex(0.68,0.25,histtitle[4]);
/*
  SaveCanvas(cth,"HI/FactBreak","epetadeco_HI_theory_r2");
  SaveCanvas(cth3,"HI/FactBreak","epetadeco_HI_theory_r3");
*/
  SaveCanvas(c,"HI/FactBreak","epetadeco_HI_r2");
  SaveCanvas(cc,"HI/FactBreak","epetadeco_HI_r3");
//  SaveCanvas(ccaa,"HI/FactBreak","epetadeco_HI_r2ratio");
//  SaveCanvas(c1,"HI/FactBreak","epetadeco_HI_C");
//  SaveCanvas(cc2,"HI/FactBreak","epetadeco_HI_cos");
}
