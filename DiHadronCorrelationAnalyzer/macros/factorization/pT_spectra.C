void pT_spectra()
{
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/epetadeco_cent5060_pttrg033_ptassallweight_etaass445_eff1_v42.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/epetadeco_n120150_pttrg033_ptassallweight_etaass445_eff1_all_v42.root");

  TH1D* hpt = (TH1D*)f->Get("epetadeco_ana_pPb_hfp/pt_signal_ass_0");
  hpt->Scale(1.0/hpt->Integral());
  
  TCanvas* c = new TCanvas("c","c",650,500);
  c->SetLogy();
  c->SetLogx();
  hpt->SetMarkerStyle(20);
  hpt->SetAxisRange(0,30,"X");
  hpt->SetTitle("pPb 120<N_{trk}^{offline}<150;E^{b}_{T} (4.4<|#eta^{b}|<5);");
  hpt->GetXaxis()->CenterTitle();
  hpt->GetYaxis()->CenterTitle();
  hpt->Draw("PE");
/*
  TLegend* legend = new TLegend(0.5,0.75,0.9,0.9);
  legend->SetFillStyle(0);
  legend->SetTextFont(42);
  legend->AddEntry(hpt,"Before correction","P");
  legend->AddEntry(hpt_corr,"After correction","P");
  legend->Draw("same");
*/
  SaveCanvas(c,"HI/FactBreak","ETspectra_120150_pPb");
}
