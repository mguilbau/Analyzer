#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/GetMultiJetCorrFunc.C"

void cmw_pPb()
{
  TString filename = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/dihadroncorrelation_n185220_chasym1520_pt033_reverse_eff1_v2.root";

  TH2D* h2D_pos = (TH2D*)Get2DCFv3(filename.Data(),"corr_ana_pPb_pos",0,0);
  TH2D* h2D_neg = (TH2D*)Get2DCFv3(filename.Data(),"corr_ana_pPb_neg",0,0);

  TH1D* h1D_pos = (TH1D*)Get1DCFdPhiv3(filename.Data(),"corr_ana_pPb_pos",0,0,2,6);  
  TH1D* h1D_neg = (TH1D*)Get1DCFdPhiv3(filename.Data(),"corr_ana_pPb_neg",0,0,2,6);

  TF1* fitfunc_pos = FitVnFunc(h1D_pos);
  TF1* fitfunc_neg = FitVnFunc(h1D_neg);
  fitfunc_pos->SetLineColor(2);
  fitfunc_neg->SetLineColor(2);

  TCanvas* c = new TCanvas("c","c",800,400); 
  c->Divide(2,1);
  c->cd(1);
  h2D_pos->Draw("surf1");
  c->cd(2);
  h2D_neg->Draw("surf1");

  TCanvas* c1 = new TCanvas("c1","c1",800,400);
  c1->Divide(2,1);
  c1->cd(1); 
  h1D_pos->Draw("PE");
  fitfunc_pos->Draw("LSAME");
  c1->cd(2);
  h1D_neg->Draw("PE");
  fitfunc_neg->Draw("LSAME");
}
