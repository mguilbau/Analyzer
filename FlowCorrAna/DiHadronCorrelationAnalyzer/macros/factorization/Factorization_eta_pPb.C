#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/makeMultiPanelCanvas.C"

void Factorization_eta_pPb()
{
  const int nfiles = 8;
  TString filename[nfiles];
  filename[1] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/epetadeco_n150185_pttrg033_ptassallweight_etaass45_eff1_all_v10.root");
  filename[2] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/epetadeco_n185220_pttrg033_ptassallweight_etaass45_eff1_all_v10.root");
  filename[3] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/epetadeco_n220260_pttrg033_ptassallweight_etaass45_eff1_all_v10.root");
  filename[0] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/epetadeco_n120150_pttrg033_ptassallweight_etaass45_eff1_all_v10.root");

  filename[5] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/epetadeco_n150185_pttrg13_ptassallweight_etaass45_eff1_v10.root");
  filename[6] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/epetadeco_n185220_pttrg13_ptassallweight_etaass45_eff1_v10.root");
  filename[7] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/epetadeco_n220260_pttrg13_ptassallweight_etaass45_eff1_v10.root");
  filename[4] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/epetadeco_n120150_pttrg13_ptassallweight_etaass45_eff1_v10.root");
/*
  filename[9] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/epetadeco_n150185_pttrg033_ptassallweight_etaass445_eff1_all_v10.root");
  filename[10] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/epetadeco_n185220_pttrg033_ptassallweight_etaass445_eff1_all_v10.root");
  filename[11] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/epetadeco_n220260_pttrg033_ptassallweight_etaass445_eff1_all_v10.root");
  filename[8] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/epetadeco_n120150_pttrg033_ptassallweight_etaass445_eff1_all_v10.root");
*/
  const int ntrgbins = 16;
  const int ntrgbins1 = ntrgbins;
  const int ntrgbins2 = ntrgbins/2;
  TGraphErrors* gr[nfiles][6];
  TGraphErrors* gr1[nfiles][6];
  TGraphErrors* gr_tot[nfiles][6];
  TGraphErrors* gr_ratio[nfiles][6];
  TGraph* gr_band[nfiles][6];
  TGraph* gr1_band[nfiles][6];
  TF1* fit[nfiles][6];
  TF1* fit_aver[nfiles][6];
  TF1* fit1_aver[nfiles][6];
  double eta[ntrgbins2] = {0.15,0.45,0.75,1.05,1.35,1.65,1.95,2.25};
//  double eta[ntrgbins2] = {0.2,0.6,1.0,1.4,1.8,2.2};
  double eta_err[ntrgbins2] = {0.0};
  Color_t color[6] = {1,kRed, kBlue, kGreen+2,1,1};

  TFile* fdiff[nfiles];
for(int jj=0;jj<nfiles;jj++)
{
  fdiff[jj] = new TFile(filename[jj].Data());

  TH2D* hsignal[ntrgbins];
  TH2D* hbackground[ntrgbins];
  TH2D* hsignal1[ntrgbins];
  TH2D* hbackground1[ntrgbins];
  TH1D* hsignal_1D[ntrgbins];
  TH1D* hbackground_1D[ntrgbins]; 
  TH1D* hsignal1_1D[ntrgbins];
  TH1D* hbackground1_1D[ntrgbins];

  for(int i=0;i<ntrgbins;i++)
  {
    hsignal[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_pPb_hfp/signalcosn_trg%d",i));
    hbackground[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_pPb_hfp/backgroundcosn_trg%d",i));
    hsignal1[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_pPb_hfm/signalcosn_trg%d",i));
    hbackground1[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_pPb_hfm/backgroundcosn_trg%d",i));

    hsignal_1D[i] = (TH1D*)hsignal[i]->ProfileY(Form("signal_1D_trg%d",i),-1,-1,"e");
    hsignal1_1D[i] = (TH1D*)hsignal1[i]->ProfileY(Form("signal1_1D_trg%d",i),-1,-1,"e");
    hbackground_1D[i] = (TH1D*)hbackground[i]->ProfileY(Form("background_1D_trg%d",i),-1,-1,"e");
    hbackground1_1D[i] = (TH1D*)hbackground1[i]->ProfileY(Form("background1_1D_trg%d",i),-1,-1,"e");
  }

  for(int nbin=1;nbin<2;nbin++)
  {
    double Vn[ntrgbins1];
    double VnError[ntrgbins1];
    double rn[ntrgbins2];
    double rn_err[ntrgbins2];
    double Vn1[ntrgbins1];
    double VnError1[ntrgbins1];
    double rn1[ntrgbins2];
    double rn1_err[ntrgbins2];
    double rn_tot[ntrgbins2];
    double rn_tot_err[ntrgbins2];
    double rn_ratio[ntrgbins2];
    double rn_ratio_err[ntrgbins2];

    for(int i=0;i<ntrgbins1;i++)
    {
if(nbin==1 && (jj==3 || jj==7)) cout<<nbin<<" "<<i<<" "<<hsignal1_1D[i]->GetBinContent(nbin)<<" "<<hsignal1_1D[i]->GetBinError(nbin)<<" "<<hbackground1_1D[i]->GetBinContent(nbin)<<" "<<hbackground1_1D[i]->GetBinError(nbin)<<endl;
      Vn[i]=hsignal_1D[i]->GetBinContent(nbin)-hbackground_1D[i]->GetBinContent(nbin);
      VnError[i]=sqrt(hsignal_1D[i]->GetBinError(nbin)*hsignal_1D[i]->GetBinError(nbin)+hbackground_1D[i]->GetBinError(nbin)*hbackground_1D[i]->GetBinError(nbin));
      Vn1[i]=hsignal1_1D[i]->GetBinContent(nbin)-hbackground1_1D[i]->GetBinContent(nbin);
      VnError1[i]=sqrt(hsignal1_1D[i]->GetBinError(nbin)*hsignal1_1D[i]->GetBinError(nbin)+hbackground1_1D[i]->GetBinError(nbin)*hbackground1_1D[i]->GetBinError(nbin));
    } 

    for(int i=0;i<ntrgbins2;i++)
    {
      rn[ntrgbins2-i-1]=Vn[i]/Vn[ntrgbins1-i-1];
      rn_err[ntrgbins2-i-1]=sqrt((VnError[ntrgbins1-i-1]/Vn[ntrgbins1-i-1])**2+(VnError[i]/Vn[i])**2);
      rn1[ntrgbins2-i-1]=Vn1[i]/Vn1[ntrgbins1-i-1];
      rn1_err[ntrgbins2-i-1]=sqrt((VnError1[ntrgbins1-i-1]/Vn1[ntrgbins1-i-1])**2+(VnError1[i]/Vn1[i])**2);

      rn_tot[ntrgbins2-i-1] = rn[ntrgbins2-i-1]*rn1[ntrgbins2-i-1];
      rn_tot_err[ntrgbins2-i-1] = rn_tot[ntrgbins2-i-1]*sqrt(rn_err[ntrgbins2-i-1]/rn[ntrgbins2-i-1]*rn_err[ntrgbins2-i-1]/rn[ntrgbins2-i-1]+rn1_err[ntrgbins2-i-1]/rn1[ntrgbins2-i-1]*rn1_err[ntrgbins2-i-1]/rn1[ntrgbins2-i-1]);

      rn_ratio[ntrgbins2-i-1] = sqrt(rn[ntrgbins2-i-1]/rn1[ntrgbins2-i-1]);
      rn_ratio_err[ntrgbins2-i-1] = rn_ratio[ntrgbins2-i-1]*sqrt(rn_err[ntrgbins2-i-1]/rn[ntrgbins2-i-1]*rn_err[ntrgbins2-i-1]/rn[ntrgbins2-i-1]+rn1_err[ntrgbins2-i-1]/rn1[ntrgbins2-i-1]*rn1_err[ntrgbins2-i-1]/rn1[ntrgbins2-i-1])*0.5;
    }

    gr[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rn,eta_err,rn_err);
    gr[jj][nbin]->SetMarkerColor(color[nbin]);
    gr1[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rn1,eta_err,rn1_err);
    gr1[jj][nbin]->SetMarkerColor(color[nbin]);
    gr_tot[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rn_tot,eta_err,rn_tot_err);
    gr_tot[jj][nbin]->SetMarkerColor(color[nbin]);
//    gr_tot[jj][nbin]->SetMarkerSize(0.9*gr_tot[jj][nbin]->GetMarkerSize());
    gr_ratio[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rn_ratio,eta_err,rn_ratio_err);
    gr_ratio[jj][nbin]->SetMarkerColor(color[nbin]); 
    if(jj<4) fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"exp(2*[0]*(-x-4.5))/exp(2*[0]*(x-4.5))",0.0,2.5);
    else if(jj>=4 && jj<8) fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"exp(2*[0]*(-x-3.5))/exp(2*[0]*(x-3.5))",0.0,1.4);
    else if(jj>=8) fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"exp(2*[0]*(-x-4.7))/exp(2*[0]*(x-4.7))",0.0,2.5);
/*
    if(jj<4) fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"(1-[1]+[1]*exp([0]*(-x-4.5)))/(1-[1]+[1]*exp([0]*(x-4.5)))",0.0,2.5);
    else if(jj>=4 && jj<8) fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"(1-[1]+[1]*exp([0]*(-x-3.5)))/(1-[1]+[1]*exp([0]*(x-3.5)))",0.0,1.4);
    else if(jj>=8) fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"(1-[1]+[1]*exp([0]*(-x-4.7)))/(1-[1]+[1]*exp([0]*(x-4.7)))",0.0,2.5);
*/
    fit[jj][nbin]->SetParameter(0,0.01);
    fit[jj][nbin]->SetParameter(1,0.1);
    fit[jj][nbin]->SetParLimits(1,0,0.2);
    gr_tot[jj][nbin]->Fit(Form("fit_%d_%d",nbin,jj),"RNO");
    fit[jj][nbin]->SetLineColor(color[nbin]);
    fit[jj][nbin]->SetLineStyle(9);
    fit[jj][nbin]->SetLineWidth(1);

//    fit1_aver[jj][nbin] = new TF1(Form("fit1_aver_%d_%d",nbin,jj),"[1]*exp(-[0]*x)+1-[1]",0,5.0);
    fit1_aver[jj][nbin] = new TF1(Form("fit1_aver_%d_%d",nbin,jj),"exp(-[0]*x)",0,5.0);
    fit1_aver[jj][nbin]->SetParameter(0,fit[jj][nbin]->GetParameter(0));
    fit1_aver[jj][nbin]->SetParError(0,fit[jj][nbin]->GetParError(0));
//    fit1_aver[jj][nbin]->SetParameter(1,fit[jj][nbin]->GetParameter(1));
//    fit1_aver[jj][nbin]->SetParError(1,fit[jj][nbin]->GetParError(1));
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

  TString histtitle[4] = {"120 < N_{trk}^{offline} < 150", "150 < N_{trk}^{offline} < 185", "185 < N_{trk}^{offline} < 220", "220 < N_{trk}^{offline} < 260"};

  TLine* ll = new TLine(0,1.,2.65,1.);
  TCanvas* c = new TCanvas("c","c",530,500);
  makeMultiPanelCanvas(c,2,2,0.01,0.0,0.2,0.18,0.02);
  TH2D* htmp = new TH2D("htmp",";#eta^{a};r_{2}(-#eta^{a},-#eta^{b}) #times r_{2}(#eta^{a},#eta^{b})",100,-0.1,2.65,100,0.37,1.12);
  fixedFontHist(htmp,1.8,2.1);
  htmp->GetXaxis()->CenterTitle();
  htmp->GetYaxis()->CenterTitle();
  htmp->GetYaxis()->SetTitleSize(htmp->GetYaxis()->GetTitleSize()*1.2);
  htmp->GetXaxis()->SetTitleSize(htmp->GetXaxis()->GetTitleSize()*1.);
  for(int jj=0;jj<4;jj++)
  {
    c->cd(jj+1);
    htmp->Draw();
    ll->Draw("Lsame");
    gr_tot[jj][1]->Draw("Psame");
    fit[jj][1]->Draw("Lsame");
    gr_tot[jj+4][1]->SetMarkerStyle(24);
    fit[jj+4][1]->SetLineStyle(5);
    gr_tot[jj+4][1]->Draw("Psame");
    fit[jj+4][1]->Draw("Lsame");
/*
    gr_tot[jj+8][1]->SetMarkerStyle(28);
    fit[jj+8][1]->SetLineStyle(9);
    gr_tot[jj+8][1]->Draw("Psame");
    fit[jj+8][1]->Draw("Lsame");
*/
  }
  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(1.43*latex->GetTextSize());
  c->cd(1);
  latex->DrawLatex(0.27,0.05,histtitle[0]);
  latex->DrawLatex(0.55,0.74,"0.3 < p_{T}^{a} < 3 GeV/c");
  latex->DrawLatex(0.55,0.65,"p_{T}^{b} > 0 GeV/c");
  latex->DrawLatex(0.24,0.87,"CMS pPb #sqrt{s_{NN}} = 5.02 TeV");
  c->cd(2);
  latex->DrawLatex(0.09,0.05,histtitle[1]);
  c->cd(4);
  latex->DrawLatex(0.09,0.22,histtitle[3]);
  c->cd(3);
  latex->SetTextSize(0.85*latex->GetTextSize());
  latex->DrawLatex(0.27,0.22,histtitle[2]);

  TLegend* legend = new TLegend(0.22,0.16,0.62,0.36);
  legend->SetFillStyle(0);
//  legend->AddEntry(gr_tot[8][1],"4.4<#eta^{b}<5","P");
  legend->AddEntry(gr_tot[0][1],"4<#eta^{b}<5","P");
//  legend->AddEntry(fit[0][1],"Exponential fit","L");
  legend->AddEntry(gr_tot[4][1],"3<#eta^{b}<4","P");
//  legend->AddEntry(fit[4][1],"Exponential fit","L");

  c->cd(1);  
  legend->Draw();

  TLine* ll = new TLine(0,1.,5.0,1.);
  TCanvas* ca = new TCanvas("ca","ca",560,500);
  makeMultiPanelCanvas(ca,2,2,0.02,0.0,0.27,0.18,0.02);
  TH2D* htmpa = new TH2D("htmpa",";#eta^{a};#frac{v_{2}(#eta^{a})}{v_{2}(-#eta^{a})} =  #sqrt{#frac{r_{2}(#eta^{a},#eta^{b})}{r_{2}(-#eta^{a},-#eta^{b})}}",100,-0.1,2.65,100,0.92,1.03);
  fixedFontHist(htmpa,1.8,2.7);
  htmpa->GetXaxis()->CenterTitle();
  htmpa->GetYaxis()->CenterTitle();
  htmpa->GetYaxis()->SetTitleSize(htmpa->GetYaxis()->GetTitleSize()*1.15);
  htmpa->GetXaxis()->SetTitleSize(htmpa->GetXaxis()->GetTitleSize()*1.);
  for(int jj=0;jj<4;jj++)
  {
    ca->cd(jj+1);
    htmpa->Draw();
    ll->Draw("Lsame");
    gr_ratio[jj][1]->Draw("Psame");
    gr_ratio[jj+4][1]->SetMarkerStyle(24);
    gr_ratio[jj+4][1]->Draw("Psame");
  }
  TLatex* latex1 = new TLatex();
  latex1->SetNDC();
  latex1->SetTextSize(1.4*latex1->GetTextSize());
  ca->cd(1);
  latex1->DrawLatex(0.33,0.05,histtitle[0]);
  latex1->DrawLatex(0.31,0.865,"CMS pPb #sqrt{s_{NN}} = 5.02 TeV");
  ca->cd(2);
  latex1->DrawLatex(0.075,0.05,histtitle[1]);
  latex1->DrawLatex(0.07,0.26,"0.3 < p_{T}^{a} < 3 GeV/c");
  latex1->DrawLatex(0.07,0.16,"p_{T}^{b} > 0 GeV/c");
  ca->cd(4);
  latex1->DrawLatex(0.075,0.22,histtitle[3]);
  ca->cd(3);
  latex1->SetTextSize(0.85*latex1->GetTextSize());
  latex1->DrawLatex(0.33,0.22,histtitle[2]);

  TLegend* legend1 = new TLegend(0.3,0.15,0.57,0.35);
  legend1->SetFillStyle(0);
  legend1->AddEntry(gr_ratio[0][1],"4<#eta^{b}<5","P");
  legend1->AddEntry(gr_ratio[4][1],"3<#eta^{b}<4","P");
  ca->cd(1);
  legend1->Draw();

  TCanvas* c2 = new TCanvas("c2","c2",810,400);
  makeMultiPanelCanvas(c2,4,2,0.016,0.0,0.24,0.2,0.02);
  TH2D* htmp2 = new TH2D("htmp2",";#eta^{a};r_{2}(#eta^{a},#eta^{b})",100,-0.1,2.65,100,0.37,1.12);
  fixedFontHist(htmp2,1.6,1.8);
  htmp2->GetXaxis()->CenterTitle();
  htmp2->GetYaxis()->CenterTitle();
  htmp2->GetYaxis()->SetTitleSize(htmp2->GetYaxis()->GetTitleSize()*1.3);
  htmp2->GetXaxis()->SetTitleSize(htmp2->GetXaxis()->GetTitleSize()*1.);
  TH2D* htmp2a = (TH2D*)htmp2->Clone("tmp2a"); 
  htmp2a->SetTitle(";#eta^{a};r_{2}(-#eta^{a},-#eta^{b})");
  for(int jj=0;jj<4;jj++)
  {
    c2->cd(jj+1);
    htmp2->Draw();
    ll->Draw("Lsame");
    gr[jj][1]->Draw("Psame");
    gr[jj+4][1]->SetMarkerStyle(24);
    gr[jj+4][1]->Draw("Psame");
    c2->cd(jj+5);
    htmp2a->Draw();
    ll->Draw("Lsame");
    gr1[jj][1]->Draw("Psame");
    gr1[jj+4][1]->SetMarkerStyle(24);
    gr1[jj+4][1]->Draw("Psame");
  } 
  TLatex* latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(1.5*latex2->GetTextSize());
  c2->cd(1);
  latex2->DrawLatex(0.30,0.05,histtitle[0]);
  latex2->DrawLatex(0.28,0.865,"CMS pPb #sqrt{s_{NN}} = 5.02 TeV");
  c2->cd(2);
  latex2->DrawLatex(0.08,0.05,histtitle[1]);
  latex2->DrawLatex(0.07,0.3,"0.3 < p_{T}^{a} < 3 GeV/c");
  latex2->DrawLatex(0.07,0.18,"p_{T}^{b} > 0 GeV/c");
  c2->cd(4);
  latex2->DrawLatex(0.08,0.05,histtitle[3]);
  c2->cd(3);
  latex2->DrawLatex(0.08,0.05,histtitle[2]);
  c2->cd(6);
  latex2->SetTextSize(0.96*latex2->GetTextSize());
  latex2->DrawLatex(0.08,0.24,histtitle[1]);
  c2->cd(8);
  latex2->DrawLatex(0.08,0.24,histtitle[3]);
  c2->cd(7);
  latex2->DrawLatex(0.08,0.24,histtitle[2]);
  c2->cd(5);
  latex2->SetTextSize(0.9*latex2->GetTextSize());
  latex2->DrawLatex(0.3,0.24,histtitle[0]);

  TLegend* legend2 = new TLegend(0.3,0.18,0.57,0.42);
  legend2->SetFillStyle(0);
  legend2->AddEntry(gr_ratio[0][1],"4<#eta^{b}<5","P");
  legend2->AddEntry(gr_ratio[4][1],"3<#eta^{b}<4","P");
  c2->cd(1);
  legend2->Draw();

  TCanvas* cc2 = new TCanvas("cc2","cc2",530,500);
  makeMultiPanelCanvas(cc2,2,2,0.01,0.0,0.2,0.18,0.02);
  TH2D* htmp22 = new TH2D("htmp22",";|#eta^{a}-#eta^{b}|;cos[n(#Psi_{n}(#eta^{a})-#Psi_{n}(#eta^{b}))]",100,0,5,100,0.731,1.06);
  fixedFontHist(htmp22,1.8,2.2);
  htmp22->GetXaxis()->CenterTitle();
  htmp22->GetYaxis()->CenterTitle();
  htmp22->GetYaxis()->SetTitleSize(htmp22->GetYaxis()->GetTitleSize()*1.1);
  htmp22->GetXaxis()->SetTitleSize(htmp22->GetXaxis()->GetTitleSize()*1.);
  for(int jj=0;jj<4;jj++)
  { 
    cc2->cd(jj+1);
    htmp22->Draw();
    ll->Draw("Lsame");
    gr1_band[jj][1]->Draw("Fsame");
    fit1_aver[jj][1]->Draw("Lsame");
  } 
  TLatex* latex3 = new TLatex();
  latex3->SetNDC();
  latex3->SetTextSize(1.4*latex3->GetTextSize());
  cc2->cd(1);
  latex3->DrawLatex(0.26,0.05,histtitle[0]);
  latex3->DrawLatex(0.24,0.865,"CMS pPb #sqrt{s_{NN}} = 5.02 TeV");
  cc2->cd(2);
  latex3->DrawLatex(0.075,0.05,histtitle[1]);
  cc2->cd(4);
  latex3->DrawLatex(0.075,0.22,histtitle[3]);
  cc2->cd(3);
  latex3->SetTextSize(0.85*latex3->GetTextSize());
  latex3->DrawLatex(0.24,0.22,histtitle[2]);
return;
  SaveCanvas(c,"HI/FactBreak","epetadeco_pPb_r2tot");
  SaveCanvas(c2,"HI/FactBreak","epetadeco_pPb_r2sep");
  SaveCanvas(ca,"HI/FactBreak","epetadeco_pPb_r2ratio");
  SaveCanvas(cc2,"HI/FactBreak","epetadeco_pPb_cos");
}
