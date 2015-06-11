#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/makeMultiPanelCanvas.C"

void Factorization_eta_compare()
{
  const int nfiles = 8;
  TString filename[nfiles];

  filename[0] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco2_cent002_pttrg13_ptassallweight_etaass445_bin08_eff1_v45.root");
  filename[1] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco2_cent05_pttrg13_ptassallweight_etaass445_bin08_eff1_v45.root");
  filename[2] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco2_cent510_pttrg13_ptassallweight_etaass445_bin08_eff1_v45.root");
  filename[3] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco2_cent1020_pttrg13_ptassallweight_etaass445_bin08_eff1_v45.root");
  filename[4] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco2_cent2030_pttrg13_ptassallweight_etaass445_bin08_eff1_v45.root");
  filename[5] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco2_cent3040_pttrg13_ptassallweight_etaass445_bin08_eff1_v45.root");
  filename[6] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco2_cent4050_pttrg13_ptassallweight_etaass445_bin08_eff1_v45.root");
  filename[7] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco2_cent5060_pttrg033_ptassallweight_etaass445_bin08_eff1_v45.root");

  const int ntrgbins = 6;
  const int ntrgbins1 = ntrgbins;
  const int ntrgbins2 = ntrgbins/2;
  TGraphErrors* grcomp[nfiles][6];
  TF1* fit[nfiles][6];
  TF1* fit_aver[nfiles][6];
  TF1* fit1_aver[nfiles][6];
  double slope[6][nfiles];
  double slope_err[6][nfiles];
  double slope1[6][nfiles];
  double slope1_err[6][nfiles];
//  double eta[ntrgbins2] = {0.12,0.36,0.6,0.84,1.08,1.32,1.56,1.8,2.04,2.28};
//  double eta[ntrgbins2] = {0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3};  
//  double eta[ntrgbins2] = {0.15,0.45,0.75,1.05,1.35,1.65,1.95,2.25};
  double eta[ntrgbins2] = {0.4,1.2,2.0};
//  double eta[ntrgbins2] = {0.2,0.6,1.0,1.4,1.8,2.2};
  double eta_err[ntrgbins2] = {0.0};
  Color_t color[6] = {1,kBlue, kBlue, kBlue,1,1};

  TFile* fdiff[nfiles];
for(int jj=0;jj<nfiles;jj++)
{
  fdiff[jj] = new TFile(filename[jj].Data());

  TH2D* hsignalsame[ntrgbins];
  TH2D* hbackgroundsame[ntrgbins];
  TH2D* hsignaldiff[ntrgbins];
  TH2D* hbackgrounddiff[ntrgbins];
  TH1D* hsignalsame_1D[ntrgbins][6];
  TH1D* hbackgroundsame_1D[ntrgbins][6];
  TH1D* hsignaldiff_1D[ntrgbins][6];
  TH1D* hbackgrounddiff_1D[ntrgbins][6];

  double Vnsame[ntrgbins1][6];
  double VnsameError[ntrgbins1][6];
  double Vndiff[ntrgbins1][6];
  double VndiffError[ntrgbins1][6];
  double rncomp[ntrgbins2];
  double rncomp_err[ntrgbins2];

  for(int i=0;i<ntrgbins;i++)
  {
    hsignalsame[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfp/signalcosnsame_trg%d",i));
    hbackgroundsame[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfp/backgroundcosnsame_trg%d",i));
    hsignaldiff[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfp/signalcosndiff_trg%d",i));
    hbackgrounddiff[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfp/backgroundcosndiff_trg%d",i));

    for(int nbin=1;nbin<4;nbin++)
    {
      hsignalsame_1D[i][nbin] = (TH1D*)hsignalsame[i]->ProjectionX(Form("signalsame_1D_trg%d_%d",i,nbin),nbin,nbin,"e");
      hbackgroundsame_1D[i][nbin] = (TH1D*)hbackgroundsame[i]->ProjectionX(Form("backgroundsame_1D_trg%d_%d",i,nbin),nbin,nbin,"e");
      hsignaldiff_1D[i][nbin] = (TH1D*)hsignaldiff[i]->ProjectionX(Form("signaldiff_1D_trg%d_%d",i,nbin),nbin,nbin,"e");
      hbackgrounddiff_1D[i][nbin] = (TH1D*)hbackgrounddiff[i]->ProjectionX(Form("backgrounddiff_1D_trg%d_%d",i,nbin),nbin,nbin,"e");

      Vndiff[i][nbin]=hsignaldiff_1D[i][nbin]->GetMean()-hbackgrounddiff_1D[i][nbin]->GetMean();
      VndiffError[i][nbin]=sqrt(hsignaldiff_1D[i][nbin]->GetMeanError()*hsignaldiff_1D[i][nbin]->GetMeanError()+hbackgrounddiff_1D[i][nbin]->GetMeanError()*hbackgrounddiff_1D[i][nbin]->GetMeanError());
      Vnsame[i][nbin]=hsignalsame_1D[i][nbin]->GetMean()-hbackgroundsame_1D[i][nbin]->GetMean();
      VnsameError[i][nbin]=sqrt(hsignalsame_1D[i][nbin]->GetMeanError()*hsignalsame_1D[i][nbin]->GetMeanError()+hbackgroundsame_1D[i][nbin]->GetMeanError()*hbackgroundsame_1D[i][nbin]->GetMeanError());

if(jj==4 && nbin==1) cout<<"nbin="<<nbin<<" i="<<i<<" "<<Vndiff[i][nbin]<<" "<<Vnsame[i][nbin]<<endl;

      delete hsignalsame_1D[i][nbin];
      delete hbackgroundsame_1D[i][nbin];
      delete hsignaldiff_1D[i][nbin];
      delete hbackgrounddiff_1D[i][nbin];
    }
    delete hsignalsame[i];
    delete hbackgroundsame[i];
    delete hsignaldiff[i];
    delete hbackgrounddiff[i];
  }

  for(int nbin=1;nbin<4;nbin++)
  {
    for(int i=0;i<ntrgbins2;i++)
    {
      rncomp[ntrgbins2-i-1]=Vndiff[i][nbin]/sqrt(Vnsame[ntrgbins1-i-1][nbin]*Vnsame[i][nbin]);
      rncomp_err[ntrgbins2-i-1]=sqrt(0.25*(VnsameError[ntrgbins1-i-1][nbin]/Vnsame[ntrgbins1-i-1][nbin])**2+0.25*(VnsameError[i][nbin]/Vnsame[i][nbin])**2+(VndiffError[i][nbin]/Vndiff[i][nbin])**2)*rncomp[ntrgbins2-i-1];
            
if(jj==4 && nbin==1) cout<<"nbin="<<nbin<<" i="<<i<<" "<<rncomp[ntrgbins2-i-1]<<endl;
    }

    grcomp[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rncomp,eta_err,rncomp_err);
    grcomp[jj][nbin]->SetMarkerColor(color[nbin]);

    fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"exp([0]*(-x-4.6))/exp([0]*(x-4.6))",0.0,2.5);
    fit[jj][nbin]->SetParameter(0,0.01);
    grcomp[jj][nbin]->Fit(Form("fit_%d_%d",nbin,jj),"RNO");
    fit[jj][nbin]->SetLineColor(color[nbin]);
    fit[jj][nbin]->SetLineStyle(9);
    fit[jj][nbin]->SetLineWidth(1);
    slope[nbin][jj] = fit[jj][nbin]->GetParameter(0);
    slope_err[nbin][jj] = fit[jj][nbin]->GetParError(0);
  }
}
/*
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
*/
  TString histtitle[8] = {"0-0.2%","0-5%","5-10%","10-20%","20-30%","30-40%","40-50%","50-60%"};
  TLine* ll = new TLine(0,1.,5.0,1.);
  TCanvas* c = new TCanvas("c","c",920,500);
  makeMultiPanelCanvas(c,4,2,0.01,0.0,0.25,0.2,0.02);
  TH2D* htmp = new TH2D("htmp",";#eta^{a};r_{2}(#eta^{a},#eta^{b})",100,-0.1,2.5,100,0.031-0.02,1.06-0.02);
  fixedFontHist(htmp,1.8,2.8);
  htmp->GetXaxis()->CenterTitle();
  htmp->GetYaxis()->CenterTitle();
  htmp->GetYaxis()->SetTitleSize(htmp->GetYaxis()->GetTitleSize()*1.2);
  htmp->GetXaxis()->SetTitleSize(htmp->GetXaxis()->GetTitleSize()*1.);
  for(int jj=0;jj<8;jj++)
  {
    c->cd(jj+1);
    htmp->Draw();
    ll->Draw("Lsame");
//    fit[jj][1]->Draw("Lsame");
    grcomp[jj][1]->SetMarkerStyle(25);
    grcomp[jj][1]->Draw("Psame");
  }
return;
  TLatex* latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(1.5*latex2->GetTextSize());
  c->cd(1);
  latex2->DrawLatex(0.31,0.05,histtitle[0]);
  latex2->DrawLatex(0.29,0.865,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV");
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
  latex2->DrawLatex(0.31,0.24,histtitle[4]);
/*
  TLegend* legend2 = new TLegend(0.31,0.14,0.65,0.38);
  legend2->SetFillStyle(0);
  legend2->AddEntry(gr[0][1],"4.4<#eta^{b}<5","P");
  legend2->AddEntry(gr[16][1],"4<#eta^{b}<5","P");
  legend2->AddEntry(gr[8][1],"3<#eta^{b}<4","P");
  c->cd(1);
  legend2->Draw("same");
*/
  TCanvas* cc = new TCanvas("cc","cc",920,500);
  makeMultiPanelCanvas(cc,4,2,0.01,0.0,0.25,0.2,0.02);
  TH2D* htmp1 = new TH2D("htmp1",";#eta^{a};r_{3}(#eta^{a},#eta^{b})",100,-0.1,2.5,100,0.031-0.02,1.06-0.02);
  fixedFontHist(htmp1,1.8,2.8);
  htmp1->GetXaxis()->CenterTitle();
  htmp1->GetYaxis()->CenterTitle();
  htmp1->GetYaxis()->SetTitleSize(htmp1->GetYaxis()->GetTitleSize()*1.2);
  htmp1->GetXaxis()->SetTitleSize(htmp1->GetXaxis()->GetTitleSize()*1.);
  for(int jj=0;jj<1;jj++)
  {
    cc->cd(jj+1);
    htmp1->Draw();
    ll->Draw("Lsame");
    fit[jj][2]->Draw("Lsame");
    grcomp[jj][2]->SetMarkerStyle(25);
//    fit[jj+8][2]->SetLineStyle(5);
    grcomp[jj][2]->Draw("Psame");
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
  latex3->DrawLatex(0.31,0.24,histtitle[4]);
/*
  TLegend* legend3 = new TLegend(0.31,0.14,0.65,0.38);
  legend3->SetFillStyle(0);
  legend3->AddEntry(gr[0][1],"4.4<#eta^{b}<5","P");
  legend3->AddEntry(gr[16][1],"4<#eta^{b}<5","P");
  legend3->AddEntry(gr[8][1],"3<#eta^{b}<4","P");
  cc->cd(1);
  legend3->Draw("same");
*/
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
return;
  SaveCanvas(c,"HI/FactBreak","epetadeco_HI_alletab_r2");
  SaveCanvas(cc,"HI/FactBreak","epetadeco_HI_alletab_r3");
//  SaveCanvas(ccaa,"HI/FactBreak","epetadeco_HI_r2ratio");
//  SaveCanvas(c1,"HI/FactBreak","epetadeco_HI_C");
//  SaveCanvas(cc2,"HI/FactBreak","epetadeco_HI_cos");
}
