#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"

void vn_spectra_fit(TString tag = "UCC", int centmin=110, int centmax=1000)
{
   TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_%s2011_INCLHighQ2004_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",tag.Data(),centmin,centmax);
   TString filename1 = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_%s2011_INCLHighQ2004_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",tag.Data(),centmin,centmax);
   TFile* fdiff = new TFile(filename.Data());
   TFile* fdiff1 = new TFile(filename1.Data());

  TString centtag;
  if(centmin==110) centtag = "0-0.2% centrality";
  if(centmin==210) centtag = "0-0.02% centrality";
  if(centmin==50) centtag = "0-1% centrality";
  if(centmin==51) centtag = "0-1% centrality";
  if(centmin==0 && centmax==1) centtag = "0-2.5% centrality";
  if(centmin==1 && centmax==2) centtag = "2.5-5.0% centrality";

  TH1D* hpt_ref;
  TH2D* hsignal_ref;
  TH2D* hbackground_ref;
  TH1D* hsignal_ref_1D;
  TH1D* hbackground_ref_1D;
  TH1D* hcorr_ref_1D;

  TH1D* hpt1_ref;
  TH2D* hsignal1_ref;
  TH2D* hbackground1_ref;
  TH1D* hsignal1_ref_1D;
  TH1D* hbackground1_ref_1D;
  TH1D* hcorr1_ref_1D;

  TH1D* hpt[20];
  TH2D* hsignal[20];
  TH2D* hbackground[20];
  TH1D* hsignal_1D[20];
  TH1D* hbackground_1D[20];
  TH1D* hcorr_1D[20];

  TF1* fitfunc_vn_ref;
  TF1* fitfunc_vn[20];

  TGraphErrors* gr[20];
  TGraphErrors* gr_corr[20];
  TGraphErrors* gr_syst[20];
  TGraphErrors* gr_ratio[20];
  TGraphErrors* gr_merit[20];
  for(int i=0;i<20;i++)
  {
    if(i>=5)
    {
      gr[i] = new TGraphErrors(11);
      gr_corr[i] = new TGraphErrors(11);
      gr_ratio[i] = new TGraphErrors(11);
      gr_merit[i] = new TGraphErrors(11);
      gr_syst[i] = new TGraphErrors(22);
    }
    else
    {
      gr[i] = new TGraphErrors(13);
      gr_corr[i] = new TGraphErrors(13);
      gr_ratio[i] = new TGraphErrors(13);
      gr_merit[i] = new TGraphErrors(13);
      gr_syst[i] = new TGraphErrors(26);
    }
    gr_syst[i]->SetFillColor(TColor::GetColor("#ffff00"));
//    gr_syst[i]->SetFillColor(TColor::GetColor("#FFEE00"));
    gr[i]->SetName(Form("vnpt_%d",i));
    gr_corr[i]->SetName(Form("vnpt_corr_%d",i));
    gr_ratio[i]->SetName(Form("vnpt_ratio_%d",i));
  }

  double factor[20]={1.,1.3,1.0,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8};
  double factor_err[20]={0.,0.1,0.4,0.6,0.6,0.6,0.6,0.6,0.6,0.6,0.6,0.6,0.6,0.6,0.6,0.6,0.6,0.6,0.6,0.6};
  double VnArray[20][20],Vn0[20],vn0[20],vn0err[20],vn01[20],vn01err[20],vn0_corr[20],vn0_corr_up[20],vn0_corr_down[20],vn0_corr_sys[28],vn0err_corr[20],vn0_ratio[20],vn0err_ratio[20];
  hcorr_ref_1D = (TH1D*)Get1DCFdPhiv3(filename.Data(),0,0,2,6);
  fitfunc_vn_ref = FitVnFunc(hcorr_ref_1D);

  for(int n=1;n<=5;n++)
  {
    double Vn=fitfunc_vn_ref->GetParameter(n);
    double VnError=fitfunc_vn_ref->GetParError(n);
    Vn0[n] = Vn;
    vn0[n] = sqrt(fabs(Vn));
    vn0err[n] = fabs(VnError/Vn)*vn0[n];
  }
/*
  TFile* fpt = new TFile(Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_%s2011_pixeltracks_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",tag.Data(),centmin,centmax));
  TH1D* hptcorr = (TH1D*)fpt->Get("ptcorrall_trg");
*/
  double merit[20]={0};
  double merit_err[20]={0};
  double total[20]={0};
  double merit_corr[20]={0};
  double merit_corr_up[20]={0};
  double merit_corr_down[20]={0};
  double merit_corr_err[20]={0};
  double total_corr[20]={0};
  for(int i=13;i>=0;i--)
  {
    hpt[i] = (TH1D*)fdiff->Get(Form("ptcorr_signal_trg_%d",i+1));
    hcorr_1D[i] = (TH1D*)Get1DCFdPhiv3(filename.Data(),i+1,0,2,6);
    fitfunc_vn[i] = FitVnFunc(hcorr_1D[i]);

    for(int n=1;n<=5;n++)
    {
      double Vn=fitfunc_vn[i]->GetParameter(n);
      double VnError=fitfunc_vn[i]->GetParError(n);

      VnArray[n][i] = Vn;
      double vn=Vn/vn0[n];
      double vnerr=vn*sqrt((VnError/Vn)*(VnError/Vn)+vn0err[n]*vn0err[n]);
      gr[n-1]->SetPoint(i,hpt[i]->GetMean(),vn);
      gr[n-1]->SetPointError(i,0,vnerr);
    }
  }

  TCanvas* c1 = new TCanvas("c1","",580,500);
  c1->SetLeftMargin(0.16);
  TH2D* htmp1 = new TH2D("htmp1",";n;v_{n}",100,0.5,7.9+5,100,0.00003-0.01,0.08);
  htmp1->GetXaxis()->CenterTitle();
  htmp1->GetYaxis()->CenterTitle();
  htmp1->GetXaxis()->SetLabelSize(0.8*htmp1->GetXaxis()->GetLabelSize());
  htmp1->GetYaxis()->SetLabelSize(0.8*htmp1->GetYaxis()->GetLabelSize());
  htmp1->GetYaxis()->SetTitleOffset(0.96*htmp1->GetYaxis()->GetTitleOffset());
  htmp1->GetXaxis()->SetTitleOffset(1.02*htmp1->GetXaxis()->GetTitleOffset());
  htmp1->GetYaxis()->SetTitleSize(1.1*htmp1->GetYaxis()->GetTitleSize());
  htmp1->GetXaxis()->SetTitleSize(0.9*htmp1->GetXaxis()->GetTitleSize());
//  c1->SetLogy();
  htmp1->Draw("");
  gr[1]->Draw("PESAME");
  gr[2]->SetMarkerColor(2);
  gr[3]->SetMarkerColor(kGreen+2);
  gr[4]->SetMarkerColor(4);
  gr[2]->Draw("PESAME");
  gr[3]->Draw("PESAME");
  gr[4]->Draw("PESAME");


return;
  TGraphErrors* gr_corr_vn0 = new TGraphErrors(15,narray,vn0_corr,narrayerr,vn0err_corr);
  gr_corr_vn0->SetName("vnn_corr");
  TGraph* gr_corr_vn0_sys = new TGraph(28,narray2,vn0_corr_sys);
  gr_corr_vn0_sys->SetName("vnn_corr_sys");

  TCanvas* c1_corr = new TCanvas("c1_corr","",580,500);
  c1_corr->SetLeftMargin(0.16);
  htmp1->Draw("");
  gr_corr_vn0_sys->SetFillColor(17);
  gr_corr_vn0_sys->Draw("Fsame");
  gr_corr_vn0->Draw("PESAME");

  gr_ideal->Draw("LSAME");
  gr_004->Draw("LSAME");
  gr_008->Draw("LSAME");
  gr_012->Draw("LSAME");
  gr_016->Draw("LSAME");

  line1->Draw("lsame");
  latex1->Draw("same");
//  legend->Draw("same");

  SaveCanvas(c1_corr,"HI/UCC",Form("vnn_%s_centmin%d_centmax%d_corr",tag.Data(),centmin,centmax));

  TGraphErrors* gr_ratio_vn0 = new TGraphErrors(15,narray,vn0_ratio,narrayerr,vn0err_ratio);
  gr_ratio_vn0->SetName("vnn_ratio");
  TCanvas* c1_ratio = new TCanvas("c1_ratio","",580,500);
  c1_ratio->SetLeftMargin(0.16);
  TH2D* htmp1_ratio = new TH2D("htmp1_ratio",";n;v_{n}",100,0.5,7.9+5,100,0.5,1.5);
  htmp1_ratio->GetXaxis()->CenterTitle();
  htmp1_ratio->GetYaxis()->CenterTitle();
  htmp1_ratio->GetXaxis()->SetLabelSize(0.8*htmp1_ratio->GetXaxis()->GetLabelSize());
  htmp1_ratio->GetYaxis()->SetLabelSize(0.8*htmp1_ratio->GetYaxis()->GetLabelSize());
  htmp1_ratio->GetYaxis()->SetTitleOffset(0.96*htmp1_ratio->GetYaxis()->GetTitleOffset());
  htmp1_ratio->GetXaxis()->SetTitleOffset(1.02*htmp1_ratio->GetXaxis()->GetTitleOffset());
  htmp1_ratio->GetYaxis()->SetTitleSize(1.1*htmp1_ratio->GetYaxis()->GetTitleSize());
  htmp1_ratio->GetXaxis()->SetTitleSize(0.9*htmp1_ratio->GetXaxis()->GetTitleSize());
//  c1->SetLogy();
  htmp1_ratio->Draw("");
  gr_ratio_vn0->Draw("PESAME");
  latex1->Draw("same");
  TLine* line1_ratio = new TLine(0.5,1.0,7.9+5,1.0);
  line1_ratio->SetLineStyle(9);
  line1_ratio->Draw("lsame");

  SaveCanvas(c1_ratio,"HI/UCC",Form("vnn_%s_centmin%d_centmax%d_ratio",tag.Data(),centmin,centmax));

  TCanvas* c2 = new TCanvas("c2","",580,500);
  c2->SetLeftMargin(0.18);
  TH2D* htmp = new TH2D("htmp",";p_{T}(GeV/c);v_{n}{2part, |#Delta#eta| > 2}",100,-0.001,7.3,100,-0.005,0.099);  
  htmp->GetXaxis()->CenterTitle();
  htmp->GetYaxis()->CenterTitle();
  htmp->GetXaxis()->SetLabelSize(htmp->GetXaxis()->GetLabelSize());
  htmp->GetYaxis()->SetLabelSize(htmp->GetYaxis()->GetLabelSize());
  htmp->GetYaxis()->SetTitleOffset(0.8*htmp->GetYaxis()->GetTitleOffset());
  htmp->GetXaxis()->SetTitleOffset(0.7*htmp->GetXaxis()->GetTitleOffset());
  htmp->GetYaxis()->SetTitleSize(1.5*htmp->GetYaxis()->GetTitleSize());
  htmp->GetXaxis()->SetTitleSize(1.4*htmp->GetXaxis()->GetTitleSize());
  htmp->Draw();
  TLine* line = new TLine(0.001,0,7.3,0.0);
  line->SetLineStyle(9);
  line->Draw("lsame");
//  gr[0]->SetMarkerColor(6);
  gr[1]->SetMarkerColor(1);
  gr[2]->SetMarkerColor(2);
  gr[3]->SetMarkerColor(kGreen+2);
  gr[4]->SetMarkerColor(4);
  gr[5]->SetMarkerColor(6);
  gr[1]->SetMarkerStyle(20);
  gr[2]->SetMarkerStyle(22);
  gr[3]->SetMarkerStyle(21);
  gr[4]->SetMarkerStyle(29);
  gr[5]->SetMarkerStyle(3);
  gr[2]->SetMarkerSize(1.1*gr[2]->GetMarkerSize());
  gr[3]->SetMarkerSize(0.8*gr[3]->GetMarkerSize());
  gr[4]->SetMarkerSize(1.3*gr[4]->GetMarkerSize());
  gr[5]->SetMarkerSize(1.3*gr[5]->GetMarkerSize());
  gr[1]->Draw("PESAME");
  gr[2]->Draw("PESAME");
  gr[3]->Draw("PESAME");
  gr[4]->Draw("PESAME");
  gr[5]->Draw("PESAME");

  TLegend* legend = new TLegend(0.18,0.6,0.47,0.9);
  legend->SetFillStyle(0);
  legend->SetTextFont(42);
  legend->AddEntry(gr[1],"n = 2","P");
  legend->AddEntry(gr[2],"n = 3","P");
  legend->AddEntry(gr[3],"n = 4","P");
  legend->AddEntry(gr[4],"n = 5","P");
  legend->AddEntry(gr[5],"n = 6","P");
  legend->Draw("same");

  TLatex* latex = new TLatex();
  latex->SetNDC(1);
  latex->SetTextSize(latex->GetTextSize()*1.0);
  latex->DrawLatex(0.66,0.86,"CMS Preliminary");
  latex->DrawLatex(0.64,0.80,"PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  latex->DrawLatex(0.66,0.74,centtag.Data());

  SaveCanvas(c2,"HI/UCC",Form("vn_pt_%s_centmin%d_centmax%d",tag.Data(),centmin,centmax));

  TCanvas* c2_corr = new TCanvas("c2corr","",600,500);
  c2_corr->SetBottomMargin(0.12);
  c2_corr->SetLeftMargin(0.15);
  htmp->Draw();
  line->Draw("lsame");
  gr_corr[1]->SetMarkerColor(1);
  gr_corr[2]->SetMarkerColor(2);
  gr_corr[3]->SetMarkerColor(kGreen+2);
  gr_corr[4]->SetMarkerColor(4);
  gr_corr[5]->SetMarkerColor(6);
  gr_corr[1]->SetMarkerStyle(20);
  gr_corr[2]->SetMarkerStyle(22);
  gr_corr[3]->SetMarkerStyle(21);
  gr_corr[4]->SetMarkerStyle(29);
  gr_corr[5]->SetMarkerStyle(3);
  gr_corr[2]->SetMarkerSize(1.3*gr_corr[2]->GetMarkerSize());
  gr_corr[3]->SetMarkerSize(1.0*gr_corr[3]->GetMarkerSize());
  gr_corr[4]->SetMarkerSize(1.8*gr_corr[4]->GetMarkerSize());
  gr_corr[5]->SetMarkerSize(1.6*gr_corr[5]->GetMarkerSize());

  gr_syst[1]->Draw("FSAME");
  gr_syst[2]->Draw("FSAME");
  gr_syst[3]->Draw("FSAME");
  gr_syst[4]->Draw("FSAME");
  gr_syst[5]->Draw("FSAME");

  gr_corr[1]->Draw("PESAME");
  gr_corr[2]->Draw("PESAME");
  gr_corr[3]->Draw("PESAME");
  gr_corr[4]->Draw("PESAME");
  gr_corr[5]->Draw("PESAME");
  legend->Draw("same");

  TLatex* latex_corr = new TLatex();
  latex_corr->SetNDC(1);
  latex_corr->SetTextSize(latex_corr->GetTextSize()*0.8);
//  latex_corr->DrawLatex(0.63,0.88,"CMS Preliminary");
  latex_corr->DrawLatex(0.54,0.875,"CMS PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  latex_corr->DrawLatex(0.72,0.815,"L_{int} = 120 #mub^{-1}");
  latex_corr->DrawLatex(0.68,0.735,centtag.Data());
  latex_corr->DrawLatex(0.68,0.675,"1 < p_{T}^{ref} < 3 GeV/c");

//  latex_corr->DrawLatex(0.64,0.175,"CMS Preliminary");

  SaveCanvas(c2_corr,"HI/UCC",Form("vn_pt_%s_centmin%d_centmax%d_corr",tag.Data(),centmin,centmax));

  TCanvas* c2_ratio = new TCanvas("c2_ratio","",580,500);
  c2_ratio->SetLeftMargin(0.16);
  TH2D* htmp_ratio = new TH2D("htmp_ratio",";p_{T}(GeV/c);v^{corr}_{n}/v^{raw}_{n}",100,0.001,7.3,100,0.5,1.5);
  htmp_ratio->GetXaxis()->CenterTitle();
  htmp_ratio->GetYaxis()->CenterTitle();
  htmp_ratio->GetXaxis()->SetLabelSize(0.8*htmp_ratio->GetXaxis()->GetLabelSize());
  htmp_ratio->GetYaxis()->SetLabelSize(0.8*htmp_ratio->GetYaxis()->GetLabelSize());
  htmp_ratio->GetYaxis()->SetTitleOffset(0.98*htmp_ratio->GetYaxis()->GetTitleOffset());
  htmp_ratio->GetXaxis()->SetTitleOffset(1.02*htmp_ratio->GetXaxis()->GetTitleOffset());
  htmp_ratio->GetYaxis()->SetTitleSize(1.1*htmp_ratio->GetYaxis()->GetTitleSize());
  htmp_ratio->GetXaxis()->SetTitleSize(0.9*htmp_ratio->GetXaxis()->GetTitleSize());
  htmp_ratio->Draw();
  TLine* line_ratio = new TLine(0.001,1.0,7.3,1.0);
  line_ratio->SetLineStyle(9);
  line_ratio->Draw("lsame");
  gr_ratio[1]->SetMarkerColor(1);
  gr_ratio[2]->SetMarkerColor(2);
  gr_ratio[3]->SetMarkerColor(3);
  gr_ratio[4]->SetMarkerColor(4);
  gr_ratio[5]->SetMarkerColor(6);
  gr_ratio[1]->SetMarkerStyle(20);
  gr_ratio[2]->SetMarkerStyle(22);
  gr_ratio[3]->SetMarkerStyle(21);
  gr_ratio[4]->SetMarkerStyle(29);
  gr_ratio[5]->SetMarkerStyle(3);
  gr_ratio[2]->SetMarkerSize(1.1*gr_ratio[2]->GetMarkerSize());
  gr_ratio[3]->SetMarkerSize(0.8*gr_ratio[3]->GetMarkerSize());
  gr_ratio[4]->SetMarkerSize(1.3*gr_ratio[4]->GetMarkerSize());
  gr_ratio[5]->SetMarkerSize(1.3*gr_ratio[5]->GetMarkerSize());
  gr_ratio[1]->Draw("PESAME");
  gr_ratio[2]->Draw("PESAME");
  gr_ratio[3]->Draw("PESAME");
  gr_ratio[4]->Draw("PESAME");
  gr_ratio[5]->Draw("PESAME");
  legend->Draw("same");

  TLatex* latex_ratio = new TLatex();
  latex_ratio->SetNDC(1);
  latex_ratio->SetTextSize(latex_ratio->GetTextSize()*1.0);
  latex_ratio->DrawLatex(0.65,0.87,"CMS Preliminary");
  latex_ratio->DrawLatex(0.65,0.80,"PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  latex_ratio->DrawLatex(0.65,0.74,centtag.Data());

  SaveCanvas(c2_ratio,"HI/UCC",Form("vn_pt_%s_centmin%d_centmax%d_ratio",tag.Data(),centmin,centmax));

//  gr[0]->Draw("PESAME");
/*
  c2->Print("/net/hisrv0001/home/davidlw/scratch1/UCCPileUp/pics/vnpt_data_UCC020.gif");
  c2->Print("/net/hisrv0001/home/davidlw/scratch1/UCCPileUp/pics/vnpt_data_UCC020.pdf");
  c2->Print("/net/hisrv0001/home/davidlw/scratch1/UCCPileUp/pics/vnpt_data_UCC020.eps");
  c2->Print("/net/hisrv0001/home/davidlw/scratch1/UCCPileUp/pics/vnpt_data_UCC020.C");
*/
/*
  TCanvas* c0 = new TCanvas("c0","",500,500);
  hsignal_1D[3]->Draw("PE");
  hbackground_1D[3]->SetMarkerStyle(24);
  hbackground_1D[3]->Draw("PESAME");

  TCanvas* c = new TCanvas("c","",500,500);
  hcorr_1D[3]->SetAxisRange(-0.001,0.006,"Y");
  hcorr_1D[3]->SetMarkerColor(1);
  hcorr_1D[3]->Draw("PE");
*/

  TFile* fout = new TFile(Form("gr_%s_centmin%d_centmax%d_new.root",tag.Data(),centmin,centmax),"recreate");
  gr_vn0->SetName("vnn");
  gr_vn0->Write();
  gr_corr_vn0->SetName("vnn_corr");
  gr_corr_vn0->Write();
  gr_corr_vn0_sys->SetName("vnn_corr_sys");
  gr_corr_vn0_sys->Write();
  gr_ratio_vn0->SetName("vnn_ratio");
  gr_ratio_vn0->Write();
  for(int i=0;i<6;i++) 
  {
    gr[i]->SetName(Form("v%dpt",i+1));
    gr[i]->Write();
    gr_corr[i]->SetName(Form("v%dpt_corr",i+1));
    gr_corr[i]->Write();
    gr_ratio[i]->SetName(Form("v%dpt_ratio",i+1));
    gr_ratio[i]->Write();
    gr_syst[i]->SetName(Form("v%dpt_syst",i+1));
    gr_syst[i]->Write();
  }
}

