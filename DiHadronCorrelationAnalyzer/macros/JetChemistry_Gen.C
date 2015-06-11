void JetChemistry_Gen()
{
  TFile* f_ks = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_2760GeV/merged/PythiaReco_Minbias_2760GeV_TuneZ2_Pt120_TESTKs_ffrom0_fto10_vtxmin-15.0_vtxmax15.0_nmin-1_nmax-1_etatrg-1.0-1.0_etaass-2.4-2.4_centmin-1_centmax-1.root");
  TFile* f_la = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_2760GeV/merged/PythiaReco_Minbias_2760GeV_TuneZ2_Pt120_TESTLambda_ffrom0_fto10_vtxmin-15.0_vtxmax15.0_nmin-1_nmax-1_etatrg-1.0-1.0_etaass-2.4-2.4_centmin-1_centmax-1.root");

  TFile* f_ks_mb = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_2760GeV/merged/PythiaReco_Minbias_2760GeV_TuneZ2_MB_TESTKshort_ffrom0_fto10_vtxmin-15.0_vtxmax15.0_nmin-1_nmax-1_etatrg-1.0-1.0_etaass-2.4-2.4_centmin-1_centmax-1.root");
  TFile* f_la_mb = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_2760GeV/merged/PythiaReco_Minbias_2760GeV_TuneZ2_MB_TESTLambda_ffrom0_fto10_vtxmin-15.0_vtxmax15.0_nmin-1_nmax-1_etatrg-1.0-1.0_etaass-2.4-2.4_centmin-1_centmax-1.root");

//  TFile* f_ks = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_2760GeV/unmerged/PythiaReco_Minbias_2760GeV_TuneZ2_Pt120_TESTKs_ffrom0_fto2_vtxmin-15.0_vtxmax15.0_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
//  TFile* f_la = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_2760GeV/unmerged/PythiaReco_Minbias_2760GeV_TuneZ2_Pt120_TESTLambda_ffrom0_fto2_vtxmin-15.0_vtxmax15.0_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");

  TH1D* hFragPt_ks = f_ks->Get("fragPt_0");
  TH1D* hJetPt_ks = f_ks->Get("jetpt_0");
  TH1D* hFragPt_la = f_la->Get("fragPt_0");
  TH1D* hJetPt_la = f_la->Get("jetpt_0");

  TH1D* hPt_ks_mb = f_ks_mb->Get("ptall_ass");
  TH1D* hPt_la_mb = f_la_mb->Get("ptall_ass");
//  hFragPt_ks->Scale(1.0/hJetPt_ks->Integral());
//  hFragPt_la->Scale(1.0/hJetPt_la->Integral());

  hFragPt_ks->Rebin(10);
  hFragPt_la->Rebin(10);

  hPt_ks_mb->Rebin(10);
  hPt_la_mb->Rebin(10);

  TCanvas* c = new TCanvas("c","",550,500);
  c->SetLogy();
  hFragPt_la->SetMarkerColor(2);
  hFragPt_ks->SetAxisRange(0.001,0.1,"Y"); 
  hFragPt_ks->Draw("PE");
  hFragPt_la->Draw("PESAME");

  TCanvas* c1 = new TCanvas("c1","",550,500);
  TH1D* hRatio = (TH1D*)hFragPt_la->Clone("ratio");
  hRatio->Divide(hFragPt_ks);
  hRatio->Scale(0.5);
  hRatio->Draw("PE");

  TCanvas* c2 = new TCanvas("c2","",550,500);
  TH1D* hRatio_mb = (TH1D*)hPt_la_mb->Clone("ratio");
  hRatio_mb->Divide(hPt_ks_mb);
  hRatio_mb->Scale(0.5);
  hRatio_mb->SetAxisRange(0,0.7,"Y");
  hRatio_mb->SetAxisRange(0,30,"X");
  hRatio_mb->Draw("PE");
  hRatio->Draw("PESAME");
}
