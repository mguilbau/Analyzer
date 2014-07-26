void ptres()
{
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/v0validation_V0EffMatchAna_v12.root");

  TH2D* ksptres = (TH2D*)f->Get("v0Validator/ksResolutionPt");
  TH2D* laptres = (TH2D*)f->Get("v0Validator/lamResolutionPt");
  ksptres->Rebin2D(10,1);
  laptres->Rebin2D(10,1);
  TProfile* ksptres_prof = ksptres->ProfileX("ks",-1,-1,"s");
  TProfile* laptres_prof = laptres->ProfileX("la",-1,-1,"s");

  ksptres->SetTitle("V^{0} p_{T} resolution;p^{RECO V^{0}}_{T}-p^{GEN V^{0}}_{T} (GeV/c);p^{RECO V^{0}}_{T} (GeV/c)");
  laptres->SetTitle("V^{0} p_{T} resolution;p^{RECO V^{0}}_{T}-p^{GEN V^{0}}_{T} (GeV/c);p^{RECO V^{0}}_{T} (GeV/c)");
  ksptres->GetXaxis()->CenterTitle();
  ksptres->GetYaxis()->CenterTitle();
  laptres->GetXaxis()->CenterTitle();
  laptres->GetYaxis()->CenterTitle();

  TCanvas* c = new TCanvas("c","c",800,400);
  c->Divide(2,1);
  c->cd(1);
  ksptres->Draw("colz");
  ksptres_prof->Draw("PESAME");
  c->cd(2);
  laptres->Draw("colz");
  laptres_prof->Draw("PESAME");
}
