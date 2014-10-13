#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/makeMultiPanelCanvas.C"

void Factorization_eta1()
{
  const int nfiles = 8;
  TString filename[nfiles];

  filename[0] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent002_pttrg033_ptassallweight_etaass45_eff0_v42.root");
  filename[1] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent020_pttrg033_ptassallweight_etaass45_eff0_v42.root");
  filename[2] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent2060_pttrg033_ptassallweight_etaass45_eff0_v42.root");
  filename[3] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent2060_pttrg033_ptassallweight_etaass45_eff0_v42.root");

  filename[4] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent002_pttrg033_ptassallweight_etaass34_eff0_v42.root");
  filename[5] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent020_pttrg033_ptassallweight_etaass34_eff0_v42.root");
  filename[6] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent2060_pttrg033_ptassallweight_etaass34_eff0_v42.root");
  filename[7] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent2060_pttrg033_ptassallweight_etaass34_eff0_v42.root");

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

  double Vn[ntrgbins1];
  double VnError[ntrgbins1];
  double rn[ntrgbins2];
  double rn_err[ntrgbins2];
  double Vn0[ntrgbins1];
  double Vn0Error[ntrgbins1];
  double rn0[ntrgbins2];
  double rn0_err[ntrgbins2];
  double Vn1[ntrgbins1];
  double Vn1Error[ntrgbins1];
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
    hsignal[i] = (TH2D*)hsignal0[i]->Clone(Form("signalcosn_trg%d",i));
    hbackground[i] = (TH2D*)hbackground0[i]->Clone(Form("backgroundcosn_trg%d",i));
    hsignal[i]->Add(hsignal1[i]);
    hbackground[i]->Add(hbackground1[i]);

    for(int nbin=3;nbin<4;nbin++)
    {
      hsignal_1D[i][nbin] = (TH1D*)hsignal[i]->ProjectionX(Form("signal_1D_trg%d_%d",i,nbin),nbin,nbin,"i");
      hsignal0_1D[i][nbin] = (TH1D*)hsignal0[i]->ProjectionX(Form("signal0_1D_trg%d_%d",i,nbin),nbin,nbin,"i");
      hsignal1_1D[i][nbin] = (TH1D*)hsignal1[i]->ProjectionX(Form("signal1_1D_trg%d_%d",i,nbin),nbin,nbin,"i");
      hbackground_1D[i][nbin] = (TH1D*)hbackground[i]->ProjectionX(Form("background_1D_trg%d_%d",i,nbin),nbin,nbin,"i");
      hbackground0_1D[i][nbin] = (TH1D*)hbackground0[i]->ProjectionX(Form("background0_1D_trg%d_%d",i,nbin),nbin,nbin,"i");
      hbackground1_1D[i][nbin] = (TH1D*)hbackground1[i]->ProjectionX(Form("background1_1D_trg%d_%d",i,nbin),nbin,nbin,"i");

      Vn[i]=hsignal_1D[i][nbin]->GetMean()-hbackground_1D[i][nbin]->GetMean();
      VnError[i]=sqrt(hsignal_1D[i][nbin]->GetMeanError()*hsignal_1D[i][nbin]->GetMeanError()+hbackground_1D[i][nbin]->GetMeanError()*hbackground_1D[i][nbin]->GetMeanError());

      Vn0[i]=hsignal0_1D[i][nbin]->GetMean()-hbackground0_1D[i][nbin]->GetMean();
      Vn0Error[i]=sqrt(hsignal0_1D[i][nbin]->GetMeanError()*hsignal0_1D[i][nbin]->GetMeanError()+hbackground0_1D[i][nbin]->GetMeanError()*hbackground0_1D[i][nbin]->GetMeanError());
      Vn1[i]=hsignal1_1D[i][nbin]->GetMean()-hbackground1_1D[i][nbin]->GetMean();
      Vn1Error[i]=sqrt(hsignal1_1D[i][nbin]->GetMeanError()*hsignal1_1D[i][nbin]->GetMeanError()+hbackground1_1D[i][nbin]->GetMeanError()*hbackground1_1D[i][nbin]->GetMeanError());

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

  for(int nbin=3;nbin<4;nbin++)
  {
    for(int i=0;i<ntrgbins2;i++)
    {
      rn[ntrgbins2-i-1]=Vn[i]/Vn[ntrgbins1-i-1];
      rn_err[ntrgbins2-i-1]=sqrt((VnError[ntrgbins1-i-1]/Vn[ntrgbins1-i-1])**2+(VnError[i]/Vn[i])**2);
      rn0[ntrgbins2-i-1]=Vn0[i]/Vn0[ntrgbins1-i-1];
      rn0_err[ntrgbins2-i-1]=sqrt((Vn0Error[ntrgbins1-i-1]/Vn0[ntrgbins1-i-1])**2+(Vn0Error[i]/Vn0[i])**2);
      rn1[ntrgbins2-i-1]=Vn1[i]/Vn1[ntrgbins1-i-1];
      rn1_err[ntrgbins2-i-1]=sqrt((Vn1Error[ntrgbins1-i-1]/Vn1[ntrgbins1-i-1])**2+(Vn1Error[i]/Vn1[i])**2);
      rn_ratio[ntrgbins2-i-1] = rn0[ntrgbins2-i-1]/rn1[ntrgbins2-i-1];
      rn_ratio_err[ntrgbins2-i-1] = sqrt(rn0_err[ntrgbins2-i-1]*rn0_err[ntrgbins2-i-1]+rn1_err[ntrgbins2-i-1]*rn1_err[ntrgbins2-i-1]);
    }

    gr[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rn,eta_err,rn_err);
    gr[jj][nbin]->SetMarkerColor(color[nbin]);
    gr0[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rn0,eta_err,rn0_err);
    gr0[jj][nbin]->SetMarkerColor(color[nbin]);
    gr1[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rn1,eta_err,rn1_err);
    gr1[jj][nbin]->SetMarkerColor(color[nbin]);
    gr_ratio[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rn_ratio,eta_err,rn_ratio_err);
    gr_ratio[jj][nbin]->SetMarkerColor(color[nbin]);

//    fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"(1+[0]*(-x-4.5)*(-x-4.5))/(1+[0]*(x-4.5)*(x-4.5))",0,3.0);
//    fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"(1+[0]*(-x-4.5))/(1+[0]*(x-4.5))",0,3.0);
    if(jj<4) fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"exp([0]*(-2*x))",0.0,2.08);
    else fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"exp([0]*(-2*x))",0.0,1.08);
    fit[jj][nbin]->SetParameter(0,0.01);
    gr[jj][nbin]->Fit(Form("fit_%d_%d",nbin,jj),"RNO");
    fit[jj][nbin]->SetLineColor(color[nbin]);
    fit[jj][nbin]->SetLineStyle(9);
    fit[jj][nbin]->SetLineWidth(1);
    if(jj<4)
    {    
      slope[nbin][jj] = fit[jj][nbin]->GetParameter(0);
      slope_err[nbin][jj] = fit[jj][nbin]->GetParError(0);
    }
    else
    {
      slope1[nbin][jj-4] = fit[jj][nbin]->GetParameter(0);
      slope1_err[nbin][jj-4] = fit[jj][nbin]->GetParError(0);
    }     
  }
}

  ofstream ff("r4_eta.txt");

  double cent[4]={0.01,0.05,0.2,0.45};
  double cent_err[4]={0};
  TGraphErrors* gr_slope[6];
  TGraphErrors* gr1_slope[6];
  for(int nbin=3;nbin<4;nbin++) {
    gr_slope[nbin] = new TGraphErrors(4,cent,slope[nbin],cent_err,slope_err[nbin]);
    gr_slope[nbin]->SetName(Form("gr_slope_%d",nbin));

    cout<<"i="<<nbin+1<<endl;
    ff<<"i="<<nbin+1<<endl;
    for(int j=0;j<4;j++) { cout<<slope[nbin][j]<<" "; ff<<slope[nbin][j]<<", ";}
    cout<<endl;
    ff<<endl;
    for(int j=0;j<4;j++) { cout<<slope_err[nbin][j]<<" "; ff<<slope_err[nbin][j]<<", ";}
    cout<<endl;
    ff<<endl;
  }
  for(int nbin=3;nbin<4;nbin++) {
    gr1_slope[nbin] = new TGraphErrors(4,cent,slope1[nbin],cent_err,slope1_err[nbin]);
    gr1_slope[nbin]->SetName(Form("gr1_slope_%d",nbin));
  }

  ff.close();

  TString histtitle[4] = {"0-0.2%","0-20%","20-60%","30-60%"};
  TLine* ll = new TLine(0,1.,5.0,1.);
/*
  TLatex* latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(1.5*latex2->GetTextSize());
  c->cd(1);
  latex2->DrawLatex(0.26,0.05,histtitle[0]);
  latex2->DrawLatex(0.24,0.865,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV");
  c->cd(2);
  latex2->DrawLatex(0.08,0.05,histtitle[1]);
  latex2->DrawLatex(0.07,0.3,"0.3 < p_{T}^{a} < 3 GeV/c");
  latex2->DrawLatex(0.07,0.18,"p_{T}^{b} > 0 GeV/c");
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
  latex2->DrawLatex(0.26,0.24,histtitle[4]);

  TLegend* legend2 = new TLegend(0.24,0.14,0.51,0.38);
  legend2->SetFillStyle(0);
  legend2->AddEntry(gr[0][1],"4<#eta^{b}<5","P");
  legend2->AddEntry(gr[8][1],"3<#eta^{b}<4","P");
  c->cd(1);
  legend2->Draw("same");
*/
  TCanvas* c = new TCanvas("c","c",700,300);
  makeMultiPanelCanvas(c,3,1,0.01,0.0,0.2,0.2,0.02);
  TH2D* htmp2 = new TH2D("htmp2",";#eta^{a};r_{4}(#eta^{a},#eta^{b})",100,-0.1,2.23,100,0.831,1.06);
  fixedFontHist(htmp2,1.1,1.3);
  htmp2->GetXaxis()->CenterTitle();
  htmp2->GetYaxis()->CenterTitle();
  htmp2->GetYaxis()->SetTitleSize(htmp2->GetYaxis()->GetTitleSize()*1.2);
  htmp2->GetXaxis()->SetTitleSize(htmp2->GetXaxis()->GetTitleSize()*1.);
  for(int jj=0;jj<4;jj++)
  {
    c->cd(jj+1);
    htmp2->Draw();
    ll->Draw("Lsame");
    gr[jj][3]->SetMarkerStyle(21);
    gr[jj][3]->Draw("Psame");
    fit[jj][3]->Draw("Lsame");
    gr[jj+4][3]->SetMarkerStyle(25);
//    fit[jj+4][3]->SetLineStyle(5);
    gr[jj+4][3]->Draw("Psame");
//    fit[jj+4][3]->Draw("Lsame");
  }

  TLatex* latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(1.1*latex2->GetTextSize());
  c->cd(1);
  latex2->DrawLatex(0.26,0.24,histtitle[0]);
  latex2->DrawLatex(0.24,0.865,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV");
  c->cd(2);
  latex2->SetTextSize(1.3*latex2->GetTextSize());
  latex2->DrawLatex(0.08,0.24,histtitle[1]);
  latex2->DrawLatex(0.07,0.43,"0.3 < p_{T}^{a} < 3 GeV/c");
  latex2->DrawLatex(0.07,0.35,"p_{T}^{b} > 0 GeV/c");
  c->cd(3);
  latex2->DrawLatex(0.08,0.24,histtitle[2]);

  TLegend* legend2 = new TLegend(0.24,0.34,0.51,0.5);
  legend2->SetFillStyle(0);
  legend2->AddEntry(gr[0][3],"4<#eta^{b}<5","P");
  legend2->AddEntry(gr[4][3],"3<#eta^{b}<4","P");
  c->cd(1);
  legend2->Draw("same");

  TCanvas* c1 = new TCanvas("c1","c1",500,500);
  TH2D* htmp2 = new TH2D("htmp2",";Centrality;C",100,0,1.0,100,0.0,0.06);
  htmp2->Draw();
  htmp2->GetXaxis()->CenterTitle();
  htmp2->GetYaxis()->CenterTitle();
/*
  gr_slope[1]->SetMarkerColor(1);
  gr_slope[2]->SetMarkerColor(1);
  gr_slope[1]->SetMarkerStyle(21);
  gr_slope[2]->SetMarkerStyle(22);
  gr_slope[1]->Draw("PESAME");
  gr_slope[2]->Draw("PESAME");
*/
  gr_slope[3]->Draw("PESAME");
/*
  gr1_slope[1]->SetMarkerColor(1);
  gr1_slope[2]->SetMarkerColor(1);
  gr1_slope[1]->SetMarkerStyle(25);
  gr1_slope[2]->SetMarkerStyle(26);
  gr1_slope[1]->Draw("PESAME");
  gr1_slope[2]->Draw("PESAME");
*/
  gr1_slope[3]->Draw("PESAME");

  TFile* f_slope_out = new TFile("gr_slope_v4.root","recreate");
  gr_slope[3]->Write();
  gr1_slope[3]->Write();
  f_slope_out->Close();

//  SaveCanvas(c,"HI/FactBreak","epetadeco_HI_r2");
//  SaveCanvas(cc,"HI/FactBreak","epetadeco_HI_r3");
  SaveCanvas(c,"HI/FactBreak","epetadeco_HI_r4");
//  SaveCanvas(c1,"HI/FactBreak","epetadeco_HI_C");
//  SaveCanvas(cc2,"HI/FactBreak","epetadeco_HI_cos");
}
