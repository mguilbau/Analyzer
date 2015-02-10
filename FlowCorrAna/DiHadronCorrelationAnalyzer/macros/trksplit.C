void trksplit()
{
  TFile* f = new TFile("../cfg/dihadroncorrelation_wsplit_real_cent010_mc.root");
  TFile* f1 = new TFile("../cfg/dihadroncorrelation_wosplit_cent010_mc.root");
 
  TH1D* hpt = (TH1D*)f->Get("corr_ana_HI/ptall_trg");
  TH1D* hpt1 = (TH1D*)f1->Get("corr_ana_HI/ptall_trg");
  hpt->SetMarkerStyle(20);
  hpt1->SetMarkerStyle(20);
  hpt->SetMarkerColor(4);
  hpt->Rebin(4);
  hpt1->Rebin(4);

  TCanvas* c = new TCanvas("c","c",500,450);
  hpt->SetAxisRange(0,5.0,"X");
  hpt->Draw("PE");
  hpt1->Draw("PESAME");

  TH1D* hratio = (TH1D*)hpt->Clone("hratio");
  hratio->Divide(hpt1);

  TCanvas* c1 = new TCanvas("c1","c1",500,450);
  hratio->Draw("PE");
}
