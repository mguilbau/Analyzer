void JetChemistry_Gen_MB()
{
  TFile* f_ks = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_2760GeV/unmerged/PythiaReco_Minbias_2760GeV_TuneZ2_MB_TESTKs_ffrom0_fto2_vtxmin-15.0_vtxmax15.0_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
  TFile* f_la = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_2760GeV/unmerged/PythiaReco_Minbias_2760GeV_TuneZ2_MB_TESTLambda_ffrom0_fto2_vtxmin-15.0_vtxmax15.0_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");

//  TFile* f_ks = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_2760GeV/merged/PythiaReco_Minbias_2760GeV_TuneZ2_Pt120_TESTKs_ffrom0_fto10_vtxmin-15.0_vtxmax15.0_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
//  TFile* f_la = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PythiaReco_Minbias_2760GeV/merged/PythiaReco_Minbias_2760GeV_TuneZ2_Pt120_TESTLambda_ffrom0_fto10_vtxmin-15.0_vtxmax15.0_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");

  TH1D* hJetPt_ks = f_ks->Get("ptall_ass");
  TH1D* hJetPt_la = f_la->Get("ptall_ass");

  hJetPt_ks->Rebin(2);
  hJetPt_la->Rebin(2);

  TCanvas* c1 = new TCanvas("c1","",550,500);
  TH1D* hRatio = (TH1D*)hJetPt_la->Clone("ratio");
  hRatio->Divide(hJetPt_ks);
  hRatio->Scale(0.5);
  hRatio->Draw("PE");
}
