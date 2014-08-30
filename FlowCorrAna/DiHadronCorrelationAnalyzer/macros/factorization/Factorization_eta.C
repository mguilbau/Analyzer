#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/makeMultiPanelCanvas.C"

void Factorization_eta()
{
  const int nfiles = 16;
  TString filename[nfiles];

  filename[0] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent002_pttrg053_ptassallweight_etaass45_eff0_v14.root");
  filename[1] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent05_pttrg053_ptassallweight_etaass45_eff0_v14.root");
  filename[2] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent510_pttrg053_ptassallweight_etaass45_eff0_v14.root");
  filename[3] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent1020_pttrg053_ptassallweight_etaass45_eff0_v14.root");
  filename[4] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent2030_pttrg053_ptassallweight_etaass45_eff0_v14.root");
  filename[5] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent3040_pttrg053_ptassallweight_etaass45_eff0_v14.root");
  filename[6] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent4050_pttrg053_ptassallweight_etaass45_eff0_v14.root");
  filename[7] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent5060_pttrg053_ptassallweight_etaass45_eff0_v14.root");

  filename[8] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent002_pttrg053_ptassallweight_etaass34_eff0_v14.root");
  filename[9] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent05_pttrg053_ptassallweight_etaass34_eff0_v14.root");
  filename[10] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent510_pttrg053_ptassallweight_etaass34_eff0_v14.root");
  filename[11] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent1020_pttrg053_ptassallweight_etaass34_eff0_v14.root");
  filename[12] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent2030_pttrg053_ptassallweight_etaass34_eff0_v14.root");
  filename[13] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent3040_pttrg053_ptassallweight_etaass34_eff0_v14.root");
  filename[14] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent4050_pttrg053_ptassallweight_etaass34_eff0_v14.root");
  filename[15] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent5060_pttrg053_ptassallweight_etaass34_eff0_v14.root");

  const int ntrgbins = 16;
  const int ntrgbins1 = ntrgbins;
  const int ntrgbins2 = ntrgbins/2;
  TGraphErrors* gr[nfiles][6];
  TGraph* gr_band[nfiles][6];
  TGraph* gr1_band[nfiles][6];
  TF1* fit[nfiles][6];
  TF1* fit_aver[nfiles][6];
  TF1* fit1_aver[nfiles][6];
  double slope[6][nfiles];
  double slope_err[6][nfiles];
  double slope1[6][nfiles];
  double slope1_err[6][nfiles];
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
  TH2D* hsignal1[ntrgbins];
  TH2D* hbackground1[ntrgbins];
  TH1D* hsignal_1D[ntrgbins][6];
  TH1D* hbackground_1D[ntrgbins][6]; 

  for(int i=0;i<ntrgbins;i++)
  {
    hsignal[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfp/signalcosn_trg%d",i));
    hbackground[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfp/backgroundcosn_trg%d",i));
    hsignal1[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfm/signalcosn_trg%d",i));
    hbackground1[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfm/backgroundcosn_trg%d",i));
    hsignal[i]->Add(hsignal1[i]);
    hbackground[i]->Add(hbackground1[i]);
    for(int nbin=1;nbin<4;nbin++) hsignal_1D[i][nbin] = (TH1D*)hsignal[i]->ProjectionX(Form("signal_1D_trg%d_%d",i,nbin),nbin,nbin,"i");
    for(int nbin=1;nbin<4;nbin++) hbackground_1D[i][nbin] = (TH1D*)hbackground[i]->ProjectionX(Form("background_1D_trg%d_%d",i,nbin),nbin,nbin,"i");
  }

  for(int nbin=1;nbin<4;nbin++)
  {
    double Vn[ntrgbins1];
    double VnError[ntrgbins1];
    double rn[ntrgbins2];
    double rn_err[ntrgbins2];

    for(int i=0;i<ntrgbins1;i++)
    {
      Vn[i]=hsignal_1D[i][nbin]->GetMean()-hbackground_1D[i][nbin]->GetMean();
      VnError[i]=sqrt(hsignal_1D[i][nbin]->GetMeanError()*hsignal_1D[i][nbin]->GetMeanError()+hbackground_1D[i][nbin]->GetMeanError()*hbackground_1D[i][nbin]->GetMeanError());
if(jj==1) cout<<Vn[i]<<" "<<VnError[i]<<endl;
    } 

    for(int i=0;i<ntrgbins2;i++)
    {
      rn[ntrgbins2-i-1]=Vn[i]/Vn[ntrgbins1-i-1];
      rn_err[ntrgbins2-i-1]=sqrt((VnError[ntrgbins1-i-1]/Vn[ntrgbins1-i-1])**2+(VnError[i]/Vn[i])**2);
    }

    gr[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rn,eta_err,rn_err);
    gr[jj][nbin]->SetMarkerColor(color[nbin]);

//    fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"(1+[0]*(-x-4.5)*(-x-4.5))/(1+[0]*(x-4.5)*(x-4.5))",0,3.0);
//    fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"(1+[0]*(-x-4.5))/(1+[0]*(x-4.5))",0,3.0);
    if(jj<8) fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"exp([0]*(-x-4.5))/exp([0]*(x-4.5))",0.0,2.4);
    else fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"exp([0]*(-x-3.5))/exp([0]*(x-3.5))",0.0,1.4);
    fit[jj][nbin]->SetParameter(0,0.01);
    gr[jj][nbin]->Fit(Form("fit_%d_%d",nbin,jj),"RNO");
    fit[jj][nbin]->SetLineColor(color[nbin]);
    fit[jj][nbin]->SetLineStyle(9);
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

  double cent[8]={0.01,0.025,0.075,0.15,0.25,0.35,0.45,0.55};
  double cent_err[8]={0};
  TGraphErrors* gr_slope[6];
  TGraphErrors* gr1_slope[6];
  for(int nbin=1;nbin<4;nbin++) gr_slope[nbin] = new TGraphErrors(8,cent,slope[nbin],cent_err,slope_err[nbin]);
  for(int nbin=1;nbin<4;nbin++) gr1_slope[nbin] = new TGraphErrors(8,cent,slope1[nbin],cent_err,slope1_err[nbin]);

  TString histtitle[8] = {"0-0.2%","0-5%","5-10%","10-20%","20-30%","30-40%","40-50%","50-60%"};
  TLine* ll = new TLine(0,1.,5.0,1.);
  TCanvas* c = new TCanvas("c","c",900,500);
  makeMultiPanelCanvas(c,4,2,0.01,0.0,0.2,0.2,0.02);
  TH2D* htmp = new TH2D("htmp",";#eta^{a};r_{2}(#eta^{a},#eta^{b})",100,-0.1,2.65,100,0.801,1.06);
  fixedFontHist(htmp,1.8,2.2);
  htmp->GetXaxis()->CenterTitle();
  htmp->GetYaxis()->CenterTitle();
  htmp->GetYaxis()->SetTitleSize(htmp->GetYaxis()->GetTitleSize()*1.2);
  htmp->GetXaxis()->SetTitleSize(htmp->GetXaxis()->GetTitleSize()*1.);
  for(int jj=0;jj<8;jj++)
  {
    c->cd(jj+1);
    htmp->Draw();
    ll->Draw("Lsame");
    gr[jj][1]->SetMarkerStyle(21);
    gr[jj][1]->Draw("Psame");
    fit[jj][1]->Draw("Lsame");
    gr[jj+8][1]->SetMarkerStyle(25);
    fit[jj+8][1]->SetLineStyle(5);
    gr[jj+8][1]->Draw("Psame");
    fit[jj+8][1]->Draw("Lsame");
  }

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

  TCanvas* cc = new TCanvas("cc","cc",900,500);
  makeMultiPanelCanvas(cc,4,2,0.01,0.0,0.2,0.2,0.02);
  TH2D* htmp1 = new TH2D("htmp1",";#eta^{a};r_{3}(#eta^{a},#eta^{b})",100,-0.1,2.65,100,0.801,1.06);
  fixedFontHist(htmp1,1.8,2.2);
  htmp1->GetXaxis()->CenterTitle();
  htmp1->GetYaxis()->CenterTitle();
  htmp1->GetYaxis()->SetTitleSize(htmp1->GetYaxis()->GetTitleSize()*1.2);
  htmp1->GetXaxis()->SetTitleSize(htmp1->GetXaxis()->GetTitleSize()*1.);
  for(int jj=0;jj<8;jj++)
  {
    cc->cd(jj+1);
    htmp1->Draw();
    ll->Draw("Lsame");
    gr[jj][2]->Draw("Psame");
    fit[jj][2]->Draw("Lsame");
    gr[jj+8][2]->SetMarkerStyle(25);
    fit[jj+8][2]->SetLineStyle(5);
    gr[jj+8][2]->Draw("Psame");
    fit[jj+8][2]->Draw("Lsame");
  }

  TLatex* latex3 = new TLatex();
  latex3->SetNDC();
  latex3->SetTextSize(1.5*latex3->GetTextSize());
  cc->cd(1);
  latex3->DrawLatex(0.26,0.05,histtitle[0]);
  latex3->DrawLatex(0.24,0.865,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV");
  cc->cd(2);
  latex3->DrawLatex(0.08,0.05,histtitle[1]);
  latex3->DrawLatex(0.07,0.28,"0.3 < p_{T}^{a} < 3 GeV/c");
  latex3->DrawLatex(0.07,0.18,"p_{T}^{b} > 0 GeV/c");
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
  latex3->DrawLatex(0.26,0.24,histtitle[4]);

  TLegend* legend3 = new TLegend(0.24,0.14,0.51,0.38);
  legend3->SetFillStyle(0);
  legend3->AddEntry(gr[0][1],"4<#eta^{b}<5","P");
  legend3->AddEntry(gr[8][1],"3<#eta^{b}<4","P");
  cc->cd(1);
  legend3->Draw("same");

  TCanvas* ccc = new TCanvas("ccc","ccc",900,500);
  makeMultiPanelCanvas(ccc,4,2,0.01,0.0,0.2,0.2,0.02);
  TH2D* htmp2 = new TH2D("htmp2",";#eta^{a};r_{4}(#eta^{a},#eta^{b})",100,-0.1,2.65,100,0.801,1.06);
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
    gr[jj+8][3]->SetMarkerStyle(25);
    fit[jj+8][3]->SetLineStyle(5);
    gr[jj+8][3]->Draw("Psame");
    fit[jj+8][3]->Draw("Lsame");
  }

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

  TCanvas* cc2 = new TCanvas("cc2","cc2",900,500);
  makeMultiPanelCanvas(cc2,4,2,0.01,0.0,0.2,0.2,0.02);
  TH2D* htmp22 = new TH2D("htmp22",";|#eta^{a}-#eta^{b}|;cos[n(#Psi_{n}(#eta^{a})-#Psi_{n}(#eta^{b}))]",100,0,5,100,0.751,1.06);
  fixedFontHist(htmp22,1.8,2.2);
  htmp22->GetXaxis()->CenterTitle();
  htmp22->GetYaxis()->CenterTitle();
  htmp22->GetYaxis()->SetTitleSize(htmp22->GetYaxis()->GetTitleSize()*1.1);
  htmp22->GetXaxis()->SetTitleSize(htmp22->GetXaxis()->GetTitleSize()*1.);
  for(int jj=0;jj<8;jj++)
  { 
    cc2->cd(jj+1);
    htmp22->Draw();
    ll->Draw("Lsame");
    gr1_band[jj][1]->Draw("Fsame");
    gr1_band[jj][2]->Draw("Fsame");
    fit1_aver[jj][1]->Draw("Lsame");
    fit1_aver[jj][2]->SetLineStyle(5);
    fit1_aver[jj][2]->Draw("Lsame");
  }

  TLatex* latex4 = new TLatex();
  latex4->SetNDC();
  latex4->SetTextSize(1.5*latex4->GetTextSize());
  cc2->cd(1);
  latex4->DrawLatex(0.26,0.05,histtitle[0]);
  latex4->DrawLatex(0.24,0.865,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV");
  cc2->cd(2);
  latex4->DrawLatex(0.08,0.05,histtitle[1]);
  cc2->cd(4);
  latex4->DrawLatex(0.08,0.05,histtitle[3]);
  cc2->cd(3);
  latex4->DrawLatex(0.08,0.05,histtitle[2]);
  cc2->cd(8);
  latex4->DrawLatex(0.08,0.24,histtitle[7]);
  cc2->cd(7);
  latex4->DrawLatex(0.08,0.24,histtitle[6]);
  cc2->cd(6);
  latex4->SetTextSize(0.96*latex4->GetTextSize());
  latex4->DrawLatex(0.08,0.24,histtitle[5]);
  cc2->cd(5);
  latex4->SetTextSize(0.85*latex4->GetTextSize());
  latex4->DrawLatex(0.26,0.24,histtitle[4]);
    
  TLegend* legend4 = new TLegend(0.24,0.18,0.51,0.42);
  legend4->SetFillStyle(0);
  legend4->AddEntry(fit1_aver[0][1],"n=2","L");
  legend4->AddEntry(fit1_aver[0][2],"n=3","L");
  cc2->cd(1);
  legend4->Draw("same");
return;
//  SaveCanvas(c,"HI/FactBreak","epetadeco_HI_r2");
//  SaveCanvas(cc,"HI/FactBreak","epetadeco_HI_r3");
  SaveCanvas(ccc,"HI/FactBreak","epetadeco_HI_r4");
//  SaveCanvas(c1,"HI/FactBreak","epetadeco_HI_C");
//  SaveCanvas(cc2,"HI/FactBreak","epetadeco_HI_cos");
}
