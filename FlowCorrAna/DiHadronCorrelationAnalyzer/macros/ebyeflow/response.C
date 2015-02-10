#include "TFile.h"
#include "TH1.h"
#include "TF1.h"
#include "TH2.h"
#include "TCanvas.h"

#define PI 3.141593

using namespace std;

void response()
{

  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/ebyeflow_cent4050_pttrg13_eff0_v1.root");
  TH1D* hvxdiff = (TH1D*)f->Get("ebyeflow_ana_HI/q2xdiff");
  TH1D* hvydiff = (TH1D*)f->Get("ebyeflow_ana_HI/q2ydiff");
  TH2D* hvxy = (TH2D*)f->Get("ebyeflow_ana_HI/q2xy");
/*
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/ebyeflow_n220260_pttrg033_rereco_eff1_v1.root");
  TH1D* hvxdiff = (TH1D*)f->Get("ebyeflow_ana_pPb/q2xdiff");
  TH1D* hvydiff = (TH1D*)f->Get("ebyeflow_ana_pPb/q2ydiff");
  TH2D* hvxy = (TH2D*)f->Get("ebyeflow_ana_pPb/q2xy");
*/
  double vxmean=hvxy->GetMean(1);
  double vymean=hvxy->GetMean(2);

  hvxdiff->Rebin(10);
  hvydiff->Rebin(10);
  hvxy->Rebin2D(10,10);

  TF1* fitx = new TF1("fitx","[0]*ROOT::Math::tdistribution_pdf(x/[2],[1])",-0.3,0.3);
  TF1* fity = new TF1("fity","[0]*ROOT::Math::tdistribution_pdf(x/[2],[1])",-0.3,0.3);
//  TF1* fitx = new TF1("fitx","[0]*TMath::Exp(-0.5*x*x/[1]/[1])",-0.6,0.6);
//  TF1* fity = new TF1("fity","[0]*TMath::Exp(-0.5*x*x/[1]/[1])",-0.6,0.6);
  fitx->SetParameters(30000,3,0.1);
  fity->SetParameters(30000,3,0.1);

  TCanvas* c = new TCanvas("c","c",800,400);
  c->Divide(2,1);
  c->cd(1);
  c->GetPad(1)->SetLogy();
  hvxdiff->SetAxisRange(-0.3,0.3,"X");
  hvxdiff->Draw("PE");
  hvxdiff->Fit("fitx","RNO");
  fitx->SetLineColor(kRed);
  fitx->Draw("LSAME");
  c->cd(2);
  c->GetPad(2)->SetLogy();
  hvydiff->SetAxisRange(-0.3,0.3,"X");
  hvydiff->Draw("PE");
  hvydiff->Fit("fity","RNO");
  fity->SetLineColor(kRed);
  fity->Draw("LSAME");

  TH2D* hresponse = new TH2D("response",";v_{2}^{obs};v_{2}^{true}",200,0,1.0,200,0,1.0);
  TH1D* hmeasure = new TH1D("measure",";v_{2}^{obs}",200,0,1.0);
  TH1D* htrue = new TH1D("true",";v_{2}^{true}",200,0,1.0);

  for(int isample=0;isample<100000;isample++)
  {
    double v2xobs=0;
    double v2yobs=0;
    hvxy->GetRandom2(v2xobs,v2yobs);
    v2xobs=v2xobs-vxmean;
    v2yobs=v2yobs-vymean;
    double v2obs = sqrt(v2xobs*v2xobs+v2yobs*v2yobs);
    hmeasure->Fill(v2obs);
    htrue->Fill(v2obs/1.8);
  }

  TCanvas* c2 = new TCanvas("c2","c2",500,500);
  hmeasure->Scale(1.0/hmeasure->Integral("width"));
  hmeasure->Draw("PE");

  TF1* fit1 = new TF1("fit1","x/[0]/[0]*exp(-0.5*(x*x+[1]*[1])/[0]/[0])*TMath::BesselI0(x*[1]/[0]/[0])",0,1);
  fit1->SetParameters(0.1,0.05);
  hmeasure->Fit("fit1","RNO");
  fit1->Draw("Lsame");
/*
  TF1* fit2 = new TF1("fit2","x/[0]/[0]*exp(-0.5*(x*x+[1]*[1])/[0]/[0])*TMath::BesselI0(x*[1]/[0]/[0])",0,1);
  fit2->SetParameters(0.04,0.03);
  fit2->Draw("Lsame");
*/
  TF1* fit2 = new TF1("fit2","2*[0]*x*(1-x*x)**([0]-1)",0,1.0);
  fit2->SetParameter(0,125);

  for(int jsample=0;jsample<200;jsample++)
  {
cout<<"jsample="<<jsample<<endl;
    double v2 =jsample*hmeasure->GetBinWidth(jsample+1)+hmeasure->GetBinWidth(jsample+1)/2;
    double weight = fit2->Eval(v2);
if(jsample==0) cout<<weight<<endl;
    double v2obs=0;
    for(int jbin=0;jbin<100;jbin++)
    {
      double phi = 2*PI/100*jbin;
      double v2x = v2*cos(phi);
      double v2y = v2*sin(phi);
      for(int isample=0;isample<50000;isample++)
      {
        double v2xobs = v2x + fitx->GetRandom();
        double v2yobs = v2y + fitx->GetRandom();
//cout<<"v2x="<<v2x<<" v2xobs="<<v2xobs<<"v2x="<<v2y<<" v2yobs="<<v2yobs<<endl;
        v2obs = sqrt(v2xobs*v2xobs+v2yobs*v2yobs);
        hresponse->Fill(v2obs,v2,weight);
      }
    }
  }

  TCanvas* c1 = new TCanvas("c1","c1",500,500);
  hresponse->Draw("colz");

  TFile* fout = new TFile("ebyeflow_hist_v1.root","recreate");
  hresponse->Write();
  hmeasure->Write();
  fout->Close(); 
}
