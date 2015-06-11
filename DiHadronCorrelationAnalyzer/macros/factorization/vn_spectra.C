#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"

void vn_spectra(TString tag = "UCC", int centmin=110, int centmax=1000)
{
/*
  TFile* fdiff = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_UCC2011_pixeltracks_INCLEFF1PtFullv2_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin110_centmax1000.root");
  TFile* fdiff1 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_UCC2011_pixeltracks_INCLEFF1PtFullv2_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin110_centmax1000.root");
*/
/*
  TFile* fdiff = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_UCC2011_PromptReco_INCLEFF1PtFullv2_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin110_centmax1000.root");
//  TFile* fdiff = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_UCC2011_pixeltracks_INCLEFF1PtFullv5_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin110_centmax1000.root");
  TFile* fdiff1 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_UCC2011_pixeltracks_INCLEFF1PtFullv2_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin110_centmax1000.root");
*/
/*
  TFile* fdiff = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_UCC2011_PromptReco_INCLEFF1PtFullv2ZVTX2_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin110_centmax1000.root");
  TFile* fdiff1 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_UCC2011_pixeltracks_INCLEFF1PtFullv2ZVTX2_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin110_centmax1000.root");
*/
//  TFile* fdiff = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_PromptReco_INCLEFF1PtFullv2_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax1.root");

   TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_%s2011_PromptReco_INCLEFF1PtFullv2_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",tag.Data(),centmin,centmax);
   TString filename1 = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_%s2011_pixeltracks_INCLEFF1PtFullv2_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",tag.Data(),centmin,centmax);
   TFile* fdiff = new TFile(filename.Data());
   TFile* fdiff1 = new TFile(filename1.Data());
/*
   TFile* fdiff = new TFile(Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_%s2011_pixeltracks_INCLEFF1PtFullv3_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",tag.Data(),centmin,centmax));
   TFile* fdiff1 = new TFile(Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_%s2011_pixeltracks_INCLEFF1PtFullv3_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",tag.Data(),centmin,centmax));
*/
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
  hsignal_ref = (TH2D*)fdiff->Get("signalcosn_trg0_ass0");
  hbackground_ref = (TH2D*)fdiff->Get("backgroundcosn_trg0_ass0");
  hsignal_ref_1D = (TH1D*)hsignal_ref->ProfileY("signal_1D_trg0_ass0_ref",1,-1,"e");
  hbackground_ref_1D = (TH1D*)hbackground_ref->ProfileY("background_1D_trg0_ass0_ref",1,-1,"e");
  hcorr_ref_1D = new TH1D("Vn_1D_trg0_ass0_ref",";n;V_{n#Delta}",15,0.5,15.5);
  for(int n=1;n<=hcorr_ref_1D->GetNbinsX();n++)
  {
    double Vn=hsignal_ref_1D->GetBinContent(n)-hbackground_ref_1D->GetBinContent(n);
    double VnError=sqrt(hsignal_ref_1D->GetBinError(n)*hsignal_ref_1D->GetBinError(n)+hbackground_ref_1D->GetBinError(n)*hbackground_ref_1D->GetBinError(n));
    hcorr_ref_1D->SetBinContent(n,Vn);
    hcorr_ref_1D->SetBinError(n,VnError);
    Vn0[n] = Vn;
    vn0[n] = sqrt(fabs(Vn));
    vn0err[n] = fabs(VnError/Vn)*vn0[n];
  }

  hsignal1_ref = (TH2D*)fdiff1->Get("signalcosn_trg0_ass0");
  hbackground1_ref = (TH2D*)fdiff1->Get("backgroundcosn_trg0_ass0");
  hsignal1_ref_1D = (TH1D*)hsignal1_ref->ProfileY("signal1_1D_trg0_ass0_ref",1,-1,"e");
  hbackground1_ref_1D = (TH1D*)hbackground1_ref->ProfileY("background1_1D_trg0_ass0_ref",1,-1,"e");
  hcorr1_ref_1D = new TH1D("Vn1_1D_trg0_ass0_ref",";n;V_{n#Delta}",15,0.5,15.5);
  for(int n=1;n<=hcorr1_ref_1D->GetNbinsX();n++)
  {
    double Vn=hsignal1_ref_1D->GetBinContent(n)-hbackground1_ref_1D->GetBinContent(n);
    double VnError=sqrt(hsignal1_ref_1D->GetBinError(n)*hsignal1_ref_1D->GetBinError(n)+hbackground1_ref_1D->GetBinError(n)*hbackground1_ref_1D->GetBinError(n));
    hcorr1_ref_1D->SetBinContent(n,Vn);
    hcorr1_ref_1D->SetBinError(n,VnError);
    vn01[n] = sqrt(fabs(Vn));
    vn01err[n] = fabs(VnError/Vn)*vn01[n];
  }
  
  TFile* fpt = new TFile(Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_%s2011_pixeltracks_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",tag.Data(),centmin,centmax));
  TH1D* hptcorr = (TH1D*)fpt->Get("ptcorrall_trg");

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
    hpt[i] = (TH1D*)fdiff1->Get(Form("ptcorr_trg_%d",i+1));
    if(i>2)
    {
      hsignal[i] = (TH2D*)fdiff->Get(Form("signalcosn_trg%d_ass0",i+1));
      hbackground[i] = (TH2D*)fdiff->Get(Form("backgroundcosn_trg%d_ass0",i+1));
    }
    else
    {
      hsignal[i] = (TH2D*)fdiff1->Get(Form("signalcosn_trg%d_ass0",i+1));
      hbackground[i] = (TH2D*)fdiff1->Get(Form("backgroundcosn_trg%d_ass0",i+1));
    }
    hsignal_1D[i] = (TH1D*)hsignal[i]->ProfileY(Form("signal_1D_trg%d_ass0",i+1),1,-1,"e");
    hbackground_1D[i] = (TH1D*)hbackground[i]->ProfileY(Form("background_1D_trg%d_ass0",i+1),1,-1,"e");
    hcorr_1D[i] = new TH1D(Form("Vn_1D_trg%d_ass0",i+1),";n;V_{n#Delta}",15,0.5,15.5);

    for(int n=1;n<=hcorr_1D[i]->GetNbinsX();n++)
    {
      if(n>=6 && hpt[i]->GetMean()>5.0) continue;
      if(n==5 && hpt[i]->GetMean()>8.0) continue;
      if(n==4 && hpt[i]->GetMean()>10.0) continue;

      double Vn=hsignal_1D[i]->GetBinContent(n)-hbackground_1D[i]->GetBinContent(n);
      double VnError=sqrt(hsignal_1D[i]->GetBinError(n)*hsignal_1D[i]->GetBinError(n)+hbackground_1D[i]->GetBinError(n)*hbackground_1D[i]->GetBinError(n));

      VnArray[n][i] = Vn;
      hcorr_1D[i]->SetBinContent(n,Vn);
      hcorr_1D[i]->SetBinError(n,VnError);
      
      double vn=Vn/vn0[n];
      if(i<=2) vn=Vn/vn01[n];
      double vnerr=vn*sqrt((VnError/Vn)*(VnError/Vn)+vn0err[n]*vn0err[n]);
      if(i<=2) vnerr=vn*sqrt((VnError/Vn)*(VnError/Vn)+vn01err[n]*vn01err[n]);
      gr[n-1]->SetPoint(i,hpt[i]->GetMean(),vn);
      gr[n-1]->SetPointError(i,0,vnerr);

/*
      double integral = hpt[i]->Integral();
      if(i==0) integral = hpt[1]->Integral();
      if(hpt[i]->GetMean()>3.0) continue;
      merit[n-1] =  merit[n-1] + integral/1000.*vn;
      merit_err[n-1] =  merit_err[n-1] + integral/1000.*vnerr;
      total[n-1] =  total[n-1] + integral/1000.;
      gr_merit[n-1]->SetPoint(i,hpt[i]->GetMean(),merit[n-1]/sqrt(total[n-1]));
if(n==2) cout<<"n="<<n<<" i="<<i<<" "<<merit[n-1]/sqrt(total[n-1])<<endl;
*/
      double integral = hptcorr->GetBinContent(hptcorr->FindBin(hpt[i]->GetMean()))*hptcorr->GetBinWidth(hptcorr->FindBin(hpt[i]->GetMean()));
      if(hpt[i]->GetMean()>3.0) continue;
      merit[n-1] =  merit[n-1] + integral/1000.*vn;
      merit_err[n-1] =  merit_err[n-1] + integral/1000.*vnerr;
      total[n-1] =  total[n-1] + integral/1000.;
      gr_merit[n-1]->SetPoint(i,hpt[i]->GetMean(),merit[n-1]/sqrt(total[n-1]));
if(n==2) cout<<"n="<<n<<" i="<<i<<" "<<merit[n-1]/sqrt(total[n-1])<<endl;
    }
  }

  TH1D* h1corr_2D = (TH1D*)Get2DCFv3(filename.Data(),0,0);
  TH1D* h1corr = (TH1D*)Get1DCFdPhiv3(filename.Data(),0,0,1.9,4.0);
  TH1D* h2corr = (TH1D*)Get1DCFdPhiv3(filename.Data(),11,0,1.9,4.0);
  TCanvas* ccorr = new TCanvas("ccorr","ccorr",900,400);
  ccorr->Divide(2,1);
  ccorr->cd(2);
  ccorr->GetPad(2)->SetLeftMargin(0.23);
  ccorr->GetPad(2)->SetBottomMargin(0.13);
  ccorr->GetPad(2)->SetRightMargin(0.02);
  ccorr->GetPad(2)->SetTopMargin(0.03);
  h1corr->SetAxisRange(50.9,52.,"Y");
  h1corr->GetYaxis()->SetTitleOffset(1.2);
  h1corr->GetXaxis()->SetLabelSize(h1corr->GetXaxis()->GetLabelSize()*0.98);
  h1corr->GetYaxis()->SetLabelSize(h1corr->GetXaxis()->GetLabelSize()*0.98);
  h1corr->GetXaxis()->SetTitleSize(h1corr->GetXaxis()->GetTitleSize()*0.98);
  h1corr->GetYaxis()->SetTitleSize(h1corr->GetXaxis()->GetTitleSize()*0.98);
  h1corr->GetYaxis()->SetTitleOffset(h1corr->GetYaxis()->GetTitleOffset()*1.4);
  h1corr->GetXaxis()->CenterTitle();
  h1corr->GetYaxis()->CenterTitle();
  h1corr->Draw("PE");
  ccorr->cd(1);
  ccorr->GetPad(1)->SetLeftMargin(0.23);
  ccorr->GetPad(1)->SetBottomMargin(0.05);
  ccorr->GetPad(1)->SetRightMargin(0.03);
  ccorr->GetPad(1)->SetTopMargin(0.01);
  ccorr->GetPad(1)->SetTheta(60.839);
  ccorr->GetPad(1)->SetPhi(38.0172);
  h1corr_2D->SetAxisRange(-4.2,4.2,"X");
  h1corr_2D->SetAxisRange(h1corr_2D->GetMinimum()*0.997,h1corr_2D->GetMaximum()*1.00,"Z");
  h1corr_2D->GetXaxis()->SetLabelSize(h1corr_2D->GetXaxis()->GetLabelSize()*1.3);
  h1corr_2D->GetYaxis()->SetLabelSize(h1corr_2D->GetYaxis()->GetLabelSize()*1.3);
  h1corr_2D->GetZaxis()->SetLabelSize(h1corr_2D->GetZaxis()->GetLabelSize()*1.2);
  h1corr_2D->GetXaxis()->SetTitleSize(h1corr_2D->GetXaxis()->GetTitleSize()*1.3);
  h1corr_2D->GetYaxis()->SetTitleSize(h1corr_2D->GetYaxis()->GetTitleSize()*1.3);
  h1corr_2D->GetZaxis()->SetTitleSize(h1corr_2D->GetZaxis()->GetTitleSize()*1.15);
  h1corr_2D->GetXaxis()->SetTitleOffset(h1corr_2D->GetXaxis()->GetTitleOffset()*1.1);
  h1corr_2D->GetYaxis()->SetTitleOffset(h1corr_2D->GetYaxis()->GetTitleOffset()*1.1);
  h1corr_2D->GetZaxis()->SetTitleOffset(h1corr_2D->GetZaxis()->GetTitleOffset()*1.13);

  for(int i=0;i<h1corr->GetNbinsX();i++)
  {
    cout<<Form("%.4f  %.4f  %.4f",h1corr->GetBinCenter(i+1),h1corr->GetBinContent(i+1),h1corr->GetBinError(i+1))<<endl;
  }
/*
  h2corr->SetAxisRange(50.8,52.4,"Y");
  h2corr->GetYaxis()->SetTitleOffset(1.2);
  h2corr->GetXaxis()->SetLabelSize(h2corr->GetXaxis()->GetLabelSize()*0.98);
  h2corr->GetYaxis()->SetLabelSize(h2corr->GetXaxis()->GetLabelSize()*0.98);
  h2corr->GetXaxis()->SetTitleSize(h2corr->GetXaxis()->GetTitleSize()*0.98);
  h2corr->GetYaxis()->SetTitleSize(h2corr->GetXaxis()->GetTitleSize()*0.98);
  h2corr->GetYaxis()->SetTitleOffset(h2corr->GetYaxis()->GetTitleOffset()*1.4);
  h2corr->GetXaxis()->CenterTitle();
  h2corr->GetYaxis()->CenterTitle();
  h2corr->Draw("PE");  
*/
  h1corr_2D->Draw("surf1");

  TF1* fitfunc1 = FitVnFunc(h1corr);
  TF1* fitfunc2 = FitVnFunc(h2corr);
  fitfunc1->SetLineWidth(1);
  fitfunc1->SetLineStyle(1);
  fitfunc2->SetLineStyle(1);
  fitfunc1->SetParameters(fitfunc1->GetParameter(0),Vn0[1],Vn0[2],Vn0[3],Vn0[4],Vn0[5],Vn0[6],Vn0[7],Vn0[8],Vn0[9],Vn0[10]);
  fitfunc2->SetParameters(fitfunc2->GetParameter(0),VnArray[1][10],VnArray[2][10],VnArray[3][10],VnArray[4][10],VnArray[5][10],VnArray[6][10],VnArray[7][10],VnArray[8][10],VnArray[9][10],VnArray[10][10]);
  ccorr->cd(2);
  fitfunc1->Draw("Lsame");

//  ccorr->cd(1);
//  fitfunc2->Draw("Lsame");
  TF1* fitfuns1[6];
  TF1* fitfuns2[6];
  for(int i=0;i<6;i++)
  {
    fitfuns1[i] = (TF1*)fitfunc1->Clone(Form("fitfuncs1_%d",i));
    fitfuns2[i] = (TF1*)fitfunc2->Clone(Form("fitfuncs2_%d",i));
    fitfuns1[i]->SetLineColor(i+1);
    fitfuns2[i]->SetLineColor(i+1);
    fitfuns1[i]->SetLineWidth(1);
    fitfuns2[i]->SetLineWidth(1);
    fitfuns1[i]->SetLineStyle(1);
    fitfuns2[i]->SetLineStyle(1);
  }
  fitfuns1[0]->SetLineColor(1);
  fitfuns1[1]->SetLineColor(2);
  fitfuns1[2]->SetLineColor(9);
  fitfuns1[3]->SetLineColor(4);
  fitfuns1[4]->SetLineColor(kGreen+2);
  fitfuns1[5]->SetLineColor(6);
  fitfuns2[0]->SetLineColor(1);
  fitfuns2[1]->SetLineColor(2);
  fitfuns2[2]->SetLineColor(9);
  fitfuns2[3]->SetLineColor(4);
  fitfuns2[4]->SetLineColor(kGreen+2);
  fitfuns2[5]->SetLineColor(6);
  fitfuns1[0]->SetLineStyle(2);
  fitfuns1[1]->SetLineStyle(3);
  fitfuns1[2]->SetLineStyle(4);
  fitfuns1[3]->SetLineStyle(5);
  fitfuns1[4]->SetLineStyle(6);
  fitfuns1[5]->SetLineStyle(7);
  fitfuns1[0]->SetLineWidth(2);
  fitfuns1[1]->SetLineWidth(2);
  fitfuns1[2]->SetLineWidth(2);
  fitfuns1[3]->SetLineWidth(2);
  fitfuns1[4]->SetLineWidth(2);
  fitfuns1[5]->SetLineWidth(2);

  fitfuns1[0]->SetParameters(fitfuns1[0]->GetParameter(0),fitfuns1[0]->GetParameter(1),0,0,0,0,0,0,0,0,0);
  fitfuns1[1]->SetParameters(fitfuns1[1]->GetParameter(0),0,fitfuns1[1]->GetParameter(2),0,0,0,0,0,0,0,0);
  fitfuns1[2]->SetParameters(fitfuns1[2]->GetParameter(0),0,0,fitfuns1[2]->GetParameter(3),0,0,0,0,0,0,0);
  fitfuns1[3]->SetParameters(fitfuns1[3]->GetParameter(0),0,0,0,fitfuns1[3]->GetParameter(4),0,0,0,0,0,0);
  fitfuns1[4]->SetParameters(fitfuns1[4]->GetParameter(0),0,0,0,0,fitfuns1[4]->GetParameter(5),0,0,0,0,0);
  fitfuns1[5]->SetParameters(fitfuns1[5]->GetParameter(0),0,0,0,0,0,fitfuns1[5]->GetParameter(6),0,0,0,0);
  fitfuns2[0]->SetParameters(fitfuns2[0]->GetParameter(0),fitfuns2[0]->GetParameter(1),0,0,0,0,0,0,0,0,0);
  fitfuns2[1]->SetParameters(fitfuns2[1]->GetParameter(0),0,fitfuns2[1]->GetParameter(2),0,0,0,0,0,0,0,0);
  fitfuns2[2]->SetParameters(fitfuns2[2]->GetParameter(0),0,0,fitfuns2[2]->GetParameter(3),0,0,0,0,0,0,0);
  fitfuns2[3]->SetParameters(fitfuns2[3]->GetParameter(0),0,0,0,fitfuns2[3]->GetParameter(4),0,0,0,0,0,0);
  fitfuns2[4]->SetParameters(fitfuns2[4]->GetParameter(0),0,0,0,0,fitfuns2[4]->GetParameter(5),0,0,0,0,0);
  fitfuns2[5]->SetParameters(fitfuns2[5]->GetParameter(0),0,0,0,0,0,fitfuns2[5]->GetParameter(6),0,0,0,0);
  
  ccorr->cd(2);
  fitfuns1[0]->Draw("Lsame");
  fitfuns1[1]->Draw("Lsame");
  fitfuns1[2]->Draw("Lsame");
  fitfuns1[3]->Draw("Lsame");
  fitfuns1[4]->Draw("Lsame");
  fitfuns1[5]->Draw("Lsame");
/*
  ccorr->cd(1);
  fitfuns2[0]->Draw("Lsame");
  fitfuns2[1]->Draw("Lsame");
  fitfuns2[2]->Draw("Lsame");
  fitfuns2[3]->Draw("Lsame");
  fitfuns2[4]->Draw("Lsame");
  fitfuns2[5]->Draw("Lsame");
*/
  TLegend* legend_corr = new TLegend(0.46,0.53,0.9,0.92);
  legend_corr->SetFillStyle(0);
  legend_corr->SetTextFont(42);
  legend_corr->AddEntry(fitfunc1,"Sum","L");
  legend_corr->AddEntry(fitfuns1[0],"V_{1#Delta}","L");
  legend_corr->AddEntry(fitfuns1[1],"V_{2#Delta}","L");
  legend_corr->AddEntry(fitfuns1[2],"V_{3#Delta}","L");
  legend_corr->AddEntry(fitfuns1[3],"V_{4#Delta}","L");
  legend_corr->AddEntry(fitfuns1[4],"V_{5#Delta}","L");  
  legend_corr->AddEntry(fitfuns1[5],"V_{6#Delta}","L");
//  ccorr->cd(1);
//  legend_corr->Draw("same");
  ccorr->cd(2);
  legend_corr->Draw("same");

/*
  ccorr->cd(1);
  TLatex* latex_corr = new TLatex();
  latex_corr->SetNDC(1);
  latex_corr->SetTextSize(latex_corr->GetTextSize()*0.8);
  latex_corr->DrawLatex(0.47,0.88,"CMS PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  latex_corr->DrawLatex(0.63,0.82,centtag.Data());
  latex_corr->DrawLatex(0.76,0.76,"|#Delta#eta| > 2");
*/
  ccorr->cd(1);
  TLatex* latex1_corr = new TLatex();
  latex1_corr->SetNDC(1);
  latex1_corr->SetTextSize(latex1_corr->GetTextSize()*0.95);
  latex1_corr->DrawLatex(0.03,0.94,"CMS PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  latex1_corr->DrawLatex(0.03,0.87,"L_{int} = 120 #mub^{-1}");
  latex1_corr->DrawLatex(0.03,0.8,centtag.Data());

//  latex1_corr->DrawLatex(0.7,0.94,"CMS Preliminary");

  TLatex* latex_trg1 = new TLatex();
  latex_trg1->SetNDC(1);
  latex_trg1->SetTextSize(latex_trg1->GetTextSize()*0.9);
  latex_trg1->DrawLatex(0.02,0.105,"1 < p_{T}^{trig} < 3 GeV/c");
  latex_trg1->DrawLatex(0.02,0.04,"1 < p_{T}^{assoc} < 3 GeV/c");

  ccorr->cd(2);
  latex1_corr->SetTextSize(latex1_corr->GetTextSize()*1.4);
  latex1_corr->DrawLatex(0.76,0.88,"|#Delta#eta| > 2");

  latex1_corr->SetTextSize(latex1_corr->GetTextSize()*0.8);
//  latex1_corr->DrawLatex(0.6,0.2,"CMS Preliminary");
  latex1_corr->SetTextSize(latex1_corr->GetTextSize()/0.8);

/*
  ccorr->cd(2);
  TLatex* latex_trg2 = new TLatex();
  latex_trg2->SetNDC(1);
  latex_trg2->SetTextSize(latex_trg2->GetTextSize()*0.8);
  latex_trg2->DrawLatex(0.59,0.635,"4 < p_{T}^{trig} < 5 GeV/c");
  latex_trg2->DrawLatex(0.59,0.57,"1 < p_{T}^{assoc} < 3 GeV/c");
*/
  SaveCanvas(ccorr,"HI/UCC",Form("corr1Dfit_%s_centmin%d_centmax%d",tag.Data(),centmin,centmax));
/*
  TCanvas* ccc = new TCanvas("ccc","ccc",900,400);
  ccc->Divide(2,1);
  ccc->cd(1);
  ccc->GetPad(1)->SetLeftMargin(0.3);
  hsignal_ref_1D->GetYaxis()->SetTitleOffset(2.0);
  hsignal_ref_1D->GetYaxis()->CenterTitle();
  hsignal_ref_1D->SetAxisRange(1.5,10.5,"X");
  hsignal_ref_1D->SetAxisRange(-0.00025,0.0019,"Y");
  hsignal_ref_1D->SetYTitle("<cos(n#Delta#phi)>");
  hsignal_ref_1D->Draw("PE");
  hbackground_ref_1D->SetMarkerStyle(24);
  hbackground_ref_1D->Draw("PESAME");
  TLegend* legend = new TLegend(0.5,0.75,0.9,0.9);
  legend->SetFillStyle(0);
  legend->SetTextFont(42);
  legend->AddEntry(hsignal_ref_1D,"Signal","P");
  legend->AddEntry(hbackground_ref_1D,"Background","P");
  legend->Draw("same");
  ccc->cd(2);
  ccc->GetPad(2)->SetLeftMargin(0.3);
  hcorr_ref_1D->GetYaxis()->SetTitleOffset(2.0);
  hcorr_ref_1D->GetYaxis()->CenterTitle();
  hcorr_ref_1D->SetAxisRange(1.5,10.5,"X");
  hcorr_ref_1D->Draw("PE");

  SaveCanvas(ccc,"HI/UCC",Form("sigbak_%s_centmin%d_centmax%d",tag.Data(),centmin,centmax));
*/
  for(int n=1;n<=hcorr_ref_1D->GetNbinsX();n++)
  {  
    vn0[n] = merit[n-1]/total[n-1];
    vn0err[n] = merit_err[n-1]/total[n-1];
  }    

  TFile* ffake = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/efficiency/fake_hiGoodTightMerged_ucc_new.root");
  TH1D* hfake = (TH1D*)ffake->Get("hFake");

//  TFile* ffake1 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/efficiency/fake_hiGoodTight_ucc_new.root");
//  TH1D* hfake1 = (TH1D*)ffake1->Get("hFake");

  TFile* ffake1 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/efficiency/fake_hiGoodTightMerged_ucc_new.root");
  TH1D* hfake1 = (TH1D*)ffake1->Get("hFake");

  for(int n=1;n<=hcorr_ref_1D->GetNbinsX();n++)
  {
cout<<Form("v_%d:",n)<<endl;
cout<<Form("p_{T}    v_%d    stat. err.    syst. up.    syst. down.",n)<<endl;
    for(i=0;i<13;i++) 
    {
      double x,y,xerr,yerr;
      gr[n-1]->GetPoint(i,x,y);
      xerr=gr[n-1]->GetErrorX(i);
      yerr=gr[n-1]->GetErrorY(i);

      if(n>=6 && i>10) continue;

      double fake = 0;
      if(x>1.0) fake = hfake1->GetBinContent(hfake1->FindBin(x));
      if(x<1.0) fake = hfake->GetBinContent(hfake->FindBin(x));
      double vn_corr = (y-fake*factor[n-1]*vn0[n])/(1-fake);
      gr_corr[n-1]->SetPoint(i,x,vn_corr);
      gr_corr[n-1]->SetPointError(i,0,yerr);
      double vn_corr_up = (y-fake*(factor[n-1]-factor_err[n-1])*vn0[n])/(1-fake)+y*0.02;
      double vn_corr_down = (y-fake*(factor[n-1]+factor_err[n-1])*vn0[n])/(1-fake)-y*0.02;
cout<<Form("%.4f  %.4f  %.4f  %.4f  %.4f",x,vn_corr,yerr,vn_corr_up-vn_corr,vn_corr-vn_corr_down)<<endl;

// temporarily add additional systematics due to EP comparison
/*
      if(n==2 && i==8)
      {
        vn_corr_up = (y-fake*(factor[n-1]-factor_err[n-1])*vn0[n])/(1-fake)+y*0.08;
        vn_corr_down = (y-fake*(factor[n-1]+factor_err[n-1])*vn0[n])/(1-fake)-y*0.08;
      }
      if(n==2 && i==9)
      {
        vn_corr_up = (y-fake*(factor[n-1]-factor_err[n-1])*vn0[n])/(1-fake)+y*0.10;
        vn_corr_down = (y-fake*(factor[n-1]+factor_err[n-1])*vn0[n])/(1-fake)-y*0.10;
      }
      if(n==2 && i==10)
      {
        vn_corr_up = (y-fake*(factor[n-1]-factor_err[n-1])*vn0[n])/(1-fake)+y*0.17;
        vn_corr_down = (y-fake*(factor[n-1]+factor_err[n-1])*vn0[n])/(1-fake)-y*0.17;
      }
      if(n==2 && i>10)
      {
        vn_corr_up = (y-fake*(factor[n-1]-factor_err[n-1])*vn0[n])/(1-fake)+y*0.17;
        vn_corr_down = (y-fake*(factor[n-1]+factor_err[n-1])*vn0[n])/(1-fake)-y*0.17;
      }

      if(n==3 && i>=8)
      {
        vn_corr_up = (y-fake*(factor[n-1]-factor_err[n-1])*vn0[n])/(1-fake)+y*0.04;
        vn_corr_down = (y-fake*(factor[n-1]+factor_err[n-1])*vn0[n])/(1-fake)-y*0.04;
      }
      if(n==5)
      {
        vn_corr_up = (y-fake*(factor[n-1]-factor_err[n-1])*vn0[n])/(1-fake)+y*0.04;
        vn_corr_down = (y-fake*(factor[n-1]+factor_err[n-1])*vn0[n])/(1-fake)-y*0.04;
      }
      if(n>5)
      {
        vn_corr_up = (y-fake*(factor[n-1]-factor_err[n-1])*vn0[n])/(1-fake)+y*0.08;
        vn_corr_down = (y-fake*(factor[n-1]+factor_err[n-1])*vn0[n])/(1-fake)-y*0.08;
      }
*/
      if(n>=6)
      {
        gr_syst[n-1]->SetPoint(i,x,vn_corr_up);
        gr_syst[n-1]->SetPoint(21-i,x,vn_corr_down);
      }
      else 
      {
        gr_syst[n-1]->SetPoint(i,x,vn_corr_up);
        gr_syst[n-1]->SetPoint(25-i,x,vn_corr_down);
      }

      gr_ratio[n-1]->SetPoint(i,x,vn_corr/y);
      gr_ratio[n-1]->SetPointError(i,0,0);

//      double integral = hpt[i]->Integral();
//      if(i==0) integral = hpt[1]->Integral();
      double integral = hptcorr->GetBinContent(hptcorr->FindBin(hpt[i]->GetMean()))*hptcorr->GetBinWidth(hptcorr->FindBin(hpt[i]->GetMean()));
      merit_corr[n-1] =  merit_corr[n-1] + integral/1000.*vn_corr;
      merit_corr_up[n-1] =  merit_corr_up[n-1] + integral/1000.*vn_corr_up;
      merit_corr_down[n-1] =  merit_corr_down[n-1] + integral/1000.*vn_corr_down;
      merit_corr_err[n-1] =  merit_corr_err[n-1] + integral/1000.*yerr;
      total_corr[n-1] =  total_corr[n-1] + integral/1000.;
    }
  }

  for(int n=2;n<=15;n++)
  {
    vn0_corr[n] = merit_corr[n-1]/total_corr[n-1];
cout<<n<<" "<<vn0_corr[n]<<endl;
    vn0_corr_up[n] = merit_corr_up[n-1]/total_corr[n-1];
    vn0_corr_down[n] = merit_corr_down[n-1]/total_corr[n-1];
    vn0_corr_sys[n-2] = vn0_corr_up[n];
    vn0_corr_sys[29-n] = vn0_corr_down[n];
    if(n>=5)
    {
      vn0_corr_sys[n-2] = vn0_corr[n]+0.0004;
      vn0_corr_sys[29-n] = vn0_corr[n]-0.0004;
    }
    vn0err_corr[n] = merit_corr_err[n-1]/total_corr[n-1];
    vn0_ratio[n] = vn0_corr[n]/vn0[n];
    vn0err_ratio[n] = 0;
  }

  double vn_hydro_ideal[4] = {0.21,0.1875,0.1,0.0375};
  double vn_hydro_004[4] = {0.195,0.167,0.08,0.025};
  double vn_hydro_008[4] = {0.18,0.15,0.0625,0.0167};
  double vn_hydro_012[4] = {0.167,0.14,0.05,0.0084};
  double vn_hydro_016[4] = {0.15,0.128,0.04,0.001};
  double etas[4] = {2,3,4,5};

  for(int i=3;i>=0;i--)
  {
    vn_hydro_ideal[i] = vn_hydro_ideal[i]/vn_hydro_ideal[0]*vn0[2];
    vn_hydro_004[i] = vn_hydro_004[i]/vn_hydro_004[0]*vn0[2];
    vn_hydro_008[i] = vn_hydro_008[i]/vn_hydro_008[0]*vn0[2];
    vn_hydro_012[i] = vn_hydro_012[i]/vn_hydro_012[0]*vn0[2];
    vn_hydro_016[i] = vn_hydro_016[i]/vn_hydro_016[0]*vn0[2];
  }

  TGraph* gr_ideal = new TGraph(4,etas,vn_hydro_ideal);
  TGraph* gr_004 = new TGraph(4,etas,vn_hydro_004);
  TGraph* gr_008 = new TGraph(4,etas,vn_hydro_008);
  TGraph* gr_012 = new TGraph(4,etas,vn_hydro_012);
  TGraph* gr_016 = new TGraph(4,etas,vn_hydro_016);
  gr_004->SetLineColor(kRed);
  gr_008->SetLineColor(kBlue);
  gr_012->SetLineColor(kGreen);
  gr_016->SetLineColor(6);
  gr_ideal->SetLineStyle(9);
  gr_ideal->SetLineWidth(2);
  gr_004->SetLineWidth(2);
  gr_008->SetLineWidth(2);
  gr_012->SetLineWidth(2);
  gr_016->SetLineWidth(2);

  double narray[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
  double narray2[28] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,15,14,13,12,11,10,9,8,7,6,5,4,3,2};

  double narrayerr[15] = {0};
  TGraphErrors* gr_vn0 = new TGraphErrors(15,narray,vn0,narrayerr,vn0err);
  gr_vn0->SetName("vnn");
  TCanvas* c1 = new TCanvas("c1","",580,500);
  c1->SetLeftMargin(0.16);
  TH2D* htmp1 = new TH2D("htmp1",";n;v_{n}",100,0.5,7.9+5,100,0.00003-0.01,0.04);
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
  gr_vn0->Draw("PESAME");

  gr_ideal->Draw("LSAME");
  gr_004->Draw("LSAME");
  gr_008->Draw("LSAME");
  gr_012->Draw("LSAME");
  gr_016->Draw("LSAME");

  TLine* line1 = new TLine(0.5,0.0,7.9+5,0.0);
  line1->SetLineStyle(9);
  line1->Draw("lsame");

  TLatex* latex1 = new TLatex();
  latex1->SetNDC(1);
  latex1->SetTextSize(latex1->GetTextSize()*1.0);
  latex1->DrawLatex(0.65,0.87,"CMS Preliminary");
  latex1->DrawLatex(0.65,0.80,"PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  latex1->DrawLatex(0.65,0.74,centtag.Data());
  latex1->DrawLatex(0.25,0.34,"0.3<p_{T}<3 GeV/c");

  TLegend* legend = new TLegend(0.2,0.45,0.45,0.7);
  legend->SetFillStyle(0);
  legend->SetTextFont(42);
  legend->AddEntry(gr_ideal,"Ideal Hydro","L");
  legend->AddEntry(gr_004,"#eta/s=0.04","L");
  legend->AddEntry(gr_008,"#eta/s=0.08","L");
  legend->AddEntry(gr_012,"#eta/s=0.12","L");
  legend->AddEntry(gr_016,"#eta/s=0.16","L");
//  legend->Draw("same");

  SaveCanvas(c1,"HI/UCC",Form("vnn_%s_centmin%d_centmax%d",tag.Data(),centmin,centmax));

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

