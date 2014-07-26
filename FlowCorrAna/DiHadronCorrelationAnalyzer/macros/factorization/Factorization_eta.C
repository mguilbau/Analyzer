#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/makeMultiPanelCanvas.C"

void Factorization_eta()
{
  const int nfiles = 4;
  TString filename[nfiles];
//  filename[0] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_UCC2011_INCLEPDECORRv4_nmin-1_nmax-1_etatrg-2.4-2.4_fabsetaass4.0-5.0_centmin110_centmax1000.root");
//  filename[0] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_UCC2011_INCLEPDECORR23v4_nmin-1_nmax-1_etatrg-2.4-2.4_fabsetaass4.0-5.0_centmin110_centmax1000.root");
  filename[0] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent002.root");
  filename[1] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent010.root");
  filename[2] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent1030.root");
  filename[3] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent3050.root");
//  filename[0] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/AMPTGen_Minbias_2760GeV/merged/AMPTGen_Minbias_2760GeV_String_INCLGenEPDECORR033v4_nmin550_nmax10000_etatrg-2.4-2.4_fabsetaass4.0-5.0_centmin-1_centmax-1.root");
//  filename[1] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_INCLEPDECORRv4Tower_nmin-1_nmax-1_etatrg-2.4-2.4_fabsetaass4.0-5.0_centmin12_centmax20.root");
//  filename[1] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_INCLEPDECORRv4_nmin-1_nmax-1_etatrg-2.4-2.4_fabsetaass4.0-5.0_centmin0_centmax4.root");
//  filename[2] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_INCLEPDECORRv4_nmin-1_nmax-1_etatrg-2.4-2.4_fabsetaass4.0-5.0_centmin2_centmax4.root");
//  filename[2] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_INCLEPDECORRv4_nmin-1_nmax-1_etatrg-2.4-2.4_fabsetaass4.0-5.0_centmin4_centmax12.root");
//  filename[3] = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_INCLEPDECORRv4_nmin-1_nmax-1_etatrg-2.4-2.4_fabsetaass4.0-5.0_centmin12_centmax20.root");

  const int ntrgbins = 12;
  const int ntrgbins1 = ntrgbins;
  const int ntrgbins2 = ntrgbins/2;
  TGraphErrors* gr[nfiles][6];
  TGraph* gr_band[nfiles][6];
  TGraph* gr1_band[nfiles][6];
  TF1* fit[nfiles][6];
  TF1* fit_aver[nfiles][6];
  TF1* fit1_aver[nfiles][6];
  double eta[ntrgbins2] = {0.2,0.6,1.0,1.4,1.8,2.2};
  double eta_err[ntrgbins2] = {0.0};
  Color_t color[6] = {1,1,kRed, kBlue, kGreen+2,1};

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

  for(int i=0;i<ntrgbins;i++)
  {
/*
    if(jj==0)
    {
*/
      hsignal[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfp/signalcosn_trg%d",i));
      hbackground[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfp/backgroundcosn_trg%d",i));
/*
      hsignal1[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfm/signalcosn_trg%d",i));
      hbackground1[i] = (TH2D*)fdiff[jj]->Get(Form("epetadeco_ana_HI_hfm/backgroundcosn_trg%d",i));
      hsignal[i]->Add(hsignal1[i]);
      hbackground[i]->Add(hbackground1[i]);
*/
/*
    }
    else{
      hsignal[i] = (TH2D*)fdiff[jj]->Get(Form("signalcosn_trg%d",i));
      hbackground[i] = (TH2D*)fdiff[jj]->Get(Form("backgroundcosn_trg%d",i));
    }
*/
    hsignal_1D[i] = (TH1D*)hsignal[i]->ProfileY(Form("signal_1D_trg%d",i),1,-1,"e");
    hbackground_1D[i] = (TH1D*)hbackground[i]->ProfileY(Form("background_1D_trg%d",i),1,-1,"e");
  }

  for(int nbin=1;nbin<6;nbin++)
  {
    double Vn[ntrgbins1];
    double VnError[ntrgbins1];
    double rn[ntrgbins2];
    double rn_err[ntrgbins2];

    for(int i=0;i<ntrgbins1;i++)
    {
//      Vn[i]=hsignal_1D[i]->GetBinContent(nbin);
//      VnError[i]=hsignal_1D[i]->GetBinError(nbin);
      Vn[i]=hsignal_1D[i]->GetBinContent(nbin)-hbackground_1D[i]->GetBinContent(nbin);
      VnError[i]=sqrt(hsignal_1D[i]->GetBinError(nbin)*hsignal_1D[i]->GetBinError(nbin)+hbackground_1D[i]->GetBinError(nbin)*hbackground_1D[i]->GetBinError(nbin));
if(jj==0) cout<<Vn[i]<<" "<<VnError[i]<<endl;
    } 

    for(int i=0;i<ntrgbins2;i++)
    {
      rn[ntrgbins2-i-1]=Vn[i]/Vn[ntrgbins1-i-1];
      rn_err[ntrgbins2-i-1]=sqrt((VnError[ntrgbins1-i-1]/Vn[ntrgbins1-i-1])**2+(VnError[i]/Vn[i])**2);

//      rn[ntrgbins2-i-1]=1./rn[ntrgbins2-i-1];
    }

    gr[jj][nbin] = new TGraphErrors(ntrgbins2,eta,rn,eta_err,rn_err);
    gr[jj][nbin]->SetMarkerColor(color[nbin]);

//    fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"(1+[0]*(-x-4.5)*(-x-4.5))/(1+[0]*(x-4.5)*(x-4.5))",0,3.0);
    fit[jj][nbin] = new TF1(Form("fit_%d_%d",nbin,jj),"(1+[0]*(-x-4.5))/(1+[0]*(x-4.5))",0,3.0);
    fit[jj][nbin]->SetParameter(0,0.01);
    gr[jj][nbin]->Fit(Form("fit_%d_%d",nbin,jj),"RNO");
    fit[jj][nbin]->SetLineColor(color[nbin]);
    fit[jj][nbin]->SetLineStyle(9);
    fit[jj][nbin]->SetLineWidth(1);

//    fit_aver[jj][nbin] = new TF1(Form("fit_aver_%d_%d",nbin,jj),"1+[0]*(x-4.5)*(x-4.5)",-4.5,4.5);
    fit_aver[jj][nbin] = new TF1(Form("fit_aver_%d_%d",nbin,jj),"1+[0]*(x-4.5)",-4.5,4.5);
    fit_aver[jj][nbin]->SetParameter(0,fit[jj][nbin]->GetParameter(0));
    fit_aver[jj][nbin]->SetParError(0,fit[jj][nbin]->GetParError(0));
    fit_aver[jj][nbin]->SetLineStyle(1);
    fit_aver[jj][nbin]->SetLineColor(color[nbin]);
    gr_band[jj][nbin] = new TGraph(4);
    gr_band[jj][nbin]->SetPoint(0,4.5,1);
    gr_band[jj][nbin]->SetPoint(1,-4.5,1-9*(fit_aver[jj][nbin]->GetParameter(0)+fit_aver[jj][nbin]->GetParError(0)));
    gr_band[jj][nbin]->SetPoint(2,-4.5,1-9*(fit_aver[jj][nbin]->GetParameter(0)-fit_aver[jj][nbin]->GetParError(0)));
    gr_band[jj][nbin]->SetPoint(3,4.5,1);
    gr_band[jj][nbin]->SetFillColor(color[nbin]-10);
    if(nbin==3) gr_band[jj][nbin]->SetFillColor(color[nbin]-12);

    fit1_aver[jj][nbin] = new TF1(Form("fit1_aver_%d_%d",nbin,jj),"(1+[0]*(-x-4.5))/(1-4.5*[0])",0,4.5);
    fit1_aver[jj][nbin]->SetParameter(0,fit[jj][nbin]->GetParameter(0));
    fit1_aver[jj][nbin]->SetParError(0,fit[jj][nbin]->GetParError(0));
    fit1_aver[jj][nbin]->SetLineStyle(1);
    fit1_aver[jj][nbin]->SetLineColor(color[nbin]);
    gr1_band[jj][nbin] = new TGraph(4);
    gr1_band[jj][nbin]->SetPoint(0,0,1);
    gr1_band[jj][nbin]->SetPoint(1,4.5,(1-9*(fit_aver[jj][nbin]->GetParameter(0)+fit_aver[jj][nbin]->GetParError(0)))/(1-4.5*(fit_aver[jj][nbin]->GetParameter(0)+fit_aver[jj][nbin]->GetParError(0))));
    gr1_band[jj][nbin]->SetPoint(2,4.5,(1-9*(fit_aver[jj][nbin]->GetParameter(0)-fit_aver[jj][nbin]->GetParError(0)))/(1-4.5*(fit_aver[jj][nbin]->GetParameter(0)-fit_aver[jj][nbin]->GetParError(0))));
    gr1_band[jj][nbin]->SetPoint(3,0,1);
    gr1_band[jj][nbin]->SetFillColor(color[nbin]-10);
    if(nbin==3) gr_band[jj][nbin]->SetFillColor(color[nbin]-12);
  }
}

  TCanvas* c = new TCanvas("c","c",650,700);
  makeMultiPanelCanvas(c,3,4,0.01,0.0,0.23,0.24,0.02);
  TH2D* htmp = new TH2D("htmp",";#eta^{trig};r'_{n}(#eta^{trig}, #eta^{assoc} #approx 4.5)",100,0,2.58,100,0.751,1.06);
  fixedFontHist(htmp,4.0,4);
  htmp->GetXaxis()->CenterTitle();
  htmp->GetYaxis()->CenterTitle();
  htmp->GetYaxis()->SetTitleSize(htmp->GetYaxis()->GetTitleSize()*1.0);
  htmp->GetXaxis()->SetTitleSize(htmp->GetXaxis()->GetTitleSize()*1.);
  for(int jj=0;jj<4;jj++)
    for(int ii=0;ii<3;ii++)
    {
      c->cd(ii+jj*3+1);
      htmp->Draw();
      gr[jj][ii+2]->Draw("Psame");
      fit[jj][ii+2]->Draw("Lsame");
    }

  TCanvas* c1 = new TCanvas("c1","c1",600,700);
  makeMultiPanelCanvas(c1,3,4,0.01,0.0,0.23,0.24,0.02);
  TH2D* htmp1 = new TH2D("htmp1",";#eta;cos[n(#Psi_{n}(#eta)-#Psi_{n}(#eta #approx 4.5))]",100,-5,5,100,0.651,1.06);
  fixedFontHist(htmp1,4.0,4.5);
  htmp1->GetXaxis()->CenterTitle();
  htmp1->GetYaxis()->CenterTitle();
  htmp1->GetYaxis()->SetTitleSize(htmp1->GetYaxis()->GetTitleSize()*0.8);
  htmp1->GetXaxis()->SetTitleSize(htmp1->GetXaxis()->GetTitleSize()*1.);
  for(int jj=0;jj<4;jj++)
    for(int ii=0;ii<3;ii++)
    {
      c1->cd(ii+jj*3+1);
      htmp1->Draw();
      gr_band[jj][ii+2]->Draw("Fsame"); 
      fit_aver[jj][ii+2]->Draw("Lsame");
    }

  SaveCanvas(c,"HI/UCC","Facbreak_etatrg_pt033_rereco_hfp");
  SaveCanvas(c1,"HI/UCC","Facbreak_eta_pt033_rereco_hfp");

/*
  TCanvas* c1 = new TCanvas("c1","c1",1200,450);
  c1->Divide(3,1);
  TH2D* htmp1 = new TH2D("htmp1",";#eta;cos[n(#Psi_{n}(#eta) - #Psi_{n}(#eta ~ 4.5))]",100,-5,5,100,0.8,1.02);
  c1->cd(1);
  htmp1->Draw();
  fit_aver[0][2]->Draw("Lsame");
  gr_band[0][2]->Draw("Fsame"); 
  c1->cd(2);
  htmp1->Draw();
  fit_aver[0][3]->Draw("Lsame"); 
  gr_band[0][3]->Draw("Fsame");
  c1->cd(3);
  htmp1->Draw();
  fit_aver[0][4]->Draw("Lsame"); 
  gr_band[0][4]->Draw("Fsame");

  TCanvas* c2 = new TCanvas("c2","c2",1200,450);
  c2->Divide(3,1);
  TH2D* htmp2 = new TH2D("htmp2",";#eta;cos[n(#Psi_{n}(#eta) - #Psi_{n}(#eta ~ 0))]",100,0,5,100,0.85,1.02);
  c2->cd(1);
  htmp2->Draw();
  fit1_aver[0][2]->Draw("Lsame");
  gr1_band[0][2]->Draw("Fsame");
  c2->cd(2);
  htmp2->Draw();
  fit1_aver[0][3]->Draw("Lsame");
  gr1_band[0][3]->Draw("Fsame");
  c2->cd(3);
  htmp2->Draw();
  fit1_aver[0][4]->Draw("Lsame");
  gr1_band[0][4]->Draw("Fsame");
*/
}
