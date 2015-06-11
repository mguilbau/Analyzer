void jetcorr()
{
  TH1D* h_fwd = (TH1D*)Get1DCFdPhiv3("~/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/dihadroncorrelation_mb_fwd_eff0_v2.root","corr_ana_pPb",2,1,-10,10);
  TH1D* h_back = (TH1D*)Get1DCFdPhiv3("~/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/dihadroncorrelation_mb_back_eff0_v2.root","corr_ana_pPb",2,1,-10,10);

  TH1D* h_fwd_zyam = GetJetCorrFunc1D_ZYAM_pp(h_fwd);
  TH1D* h_back_zyam = GetJetCorrFunc1D_ZYAM_pp(h_back);

  h_fwd_zyam->SetMarkerColor(2);
  h_fwd_zyam->SetMarkerStyle(20);
  h_back_zyam->SetMarkerStyle(20);

  TCanvas* c = new TCanvas("c","c",550,500);
  h_back_zyam->Draw("PE");
  h_fwd_zyam->Draw("PESAME");
}
