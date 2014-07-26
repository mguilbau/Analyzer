void eff_matching()
{
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/v0validation_V0EffMatchAna_v12.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/v0validation_V0EffMatchAna_v14.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/v0validation_V0EffMatchAna_v14.root");

  TH2D* ksetar_num = (TH2D*)f->Get("v0Validator/K0sEffVsEtaR_num");
  TH2D* ksetar_denom = (TH2D*)f->Get("v0Validator/K0sEffVsEtaR_denom");
  TH2D* ksptr_num = (TH2D*)f->Get("v0Validator/K0sEffVsPtR_num");
  TH2D* ksptr_denom = (TH2D*)f->Get("v0Validator/K0sEffVsPtR_denom");
  TH2D* laetar_num = (TH2D*)f->Get("v0Validator/LamEffVsEtaR_num");
  TH2D* laetar_denom = (TH2D*)f->Get("v0Validator/LamEffVsEtaR_denom");
  TH2D* laptr_num = (TH2D*)f->Get("v0Validator/LamEffVsPtR_num");
  TH2D* laptr_denom = (TH2D*)f->Get("v0Validator/LamEffVsPtR_denom");
/*
  ksetar_num->Rebin2D(1,5);
  ksetar_denom->Rebin2D(1,5);
  ksptr_num->Rebin2D(1,5);
  ksptr_denom->Rebin2D(1,5);
  laetar_num->Rebin2D(1,5);
  laetar_denom->Rebin2D(1,5);
  laptr_num->Rebin2D(1,5);
  laptr_denom->Rebin2D(1,5);
*/
//  ksetar_num->Divide(ksetar_denom);
//  laetar_num->Divide(laetar_denom);
//  ksptr_num->Divide(ksptr_denom);
//  laptr_num->Divide(laptr_denom);
      
  int ptbinmin=ksptr_num->GetYaxis()->FindBin(1.0);
  int ptbinmax=ksptr_num->GetYaxis()->FindBin(1.5);
  TH1D* ksetar_num_ratio = ksptr_num->ProjectionX("ksetar",ptbinmin,ptbinmax,"e");
  ksetar_num_ratio->Divide(ksptr_denom->ProjectionX("ks",ptbinmin,ptbinmax,"e"));
  TH1D* laetar_num_ratio = laptr_num->ProjectionX("laetar",ptbinmin,ptbinmax,"e");
  laetar_num_ratio->Divide(laptr_denom->ProjectionX("la",ptbinmin,ptbinmax,"e"));

  TH1D* lasecetapt_num = (TH1D*)f->Get("v0Validator/LamCascadeVsPt_num");
  TH1D* lasecetapt_denom = (TH1D*)f->Get("v0Validator/LamFakeVsPt_denom");
  TH2D* ksetapt_num = (TH2D*)f->Get("v0Validator/K0sEffVsEtaPt_num");
  TH2D* ksetapt_denom = (TH2D*)f->Get("v0Validator/K0sEffVsEtaPt_denom");
  TH2D* laetapt_num = (TH2D*)f->Get("v0Validator/LamEffVsEtaPt_num");
  TH2D* laetapt_denom = (TH2D*)f->Get("v0Validator/LamEffVsEtaPt_denom");
  TH2D* ksetapt_num_ratio = (TH2D*)ksetapt_num->Clone("EffCountEtaPt_ks");
  TH2D* laetapt_num_ratio = (TH2D*)laetapt_num->Clone("EffCountEtaPt_la");
  ksetapt_num_ratio->Divide(ksetapt_denom);
  laetapt_num_ratio->Divide(laetapt_denom);
  TH2D* lasecetapt_num_ratio = (TH2D*)lasecetapt_num->Clone("SecCountEtaPt_la");
  lasecetapt_num_ratio->Divide(lasecetapt_denom); 

  TH1D* hEffvsPt_ks[7];
  TH1D* hEffvsPt_la[7];
  for(int i=0;i<6;i++)
  {
    hEffvsPt_ks[i] = ksetapt_num_ratio->ProjectionY(Form("EffCountPt_ks_%d",i+1),i+1,i+1,"e");
    hEffvsPt_la[i] = laetapt_num_ratio->ProjectionY(Form("EffCountPt_la_%d",i+1),i+1,i+1,"e");
  }

  hEffvsPt_ks[6] = ksetapt_num->ProjectionY(Form("EffCountPt_ks_%d",7),1,6,"e");
  hEffvsPt_la[6] = laetapt_num->ProjectionY(Form("EffCountPt_la_%d",7),1,6,"e");
  hEffvsPt_ks[6]->Divide(ksetapt_denom->ProjectionY("denom_ks",1,6,"e"));
  hEffvsPt_la[6]->Divide(laetapt_denom->ProjectionY("denom_la",1,6,"e"));

  TH1D* hYieldRecoEta_ks_ratio = ksetapt_num->ProjectionX("EffCountEta_ks",-1,-1,"e");
  TH1D* hYieldRecoEta_la_ratio = laetapt_num->ProjectionX("EffCountEta_la",-1,-1,"e");
  hYieldRecoEta_ks_ratio->Divide(ksetapt_denom->ProjectionX("eta_ks",-1,-1,"e"));
  hYieldRecoEta_la_ratio->Divide(laetapt_denom->ProjectionX("eta_la",-1,-1,"e"));

  TCanvas* c = new TCanvas("c","",550,500);
  lasecetapt_num_ratio->SetAxisRange(0,6.0,"X");
  lasecetapt_num_ratio->SetTitle(";p_{T} (GeV/c);Fraction of #Lambda from weak decay");
  lasecetapt_num_ratio->GetXaxis()->CenterTitle();
  lasecetapt_num_ratio->GetYaxis()->CenterTitle();
  lasecetapt_num_ratio->GetYaxis()->SetTitleOffset(lasecetapt_num_ratio->GetYaxis()->GetTitleOffset()*1.5);
  lasecetapt_num_ratio->Draw("PE");

  TCanvas* c1 = new TCanvas("c1","c1",800,800);
  c1->Divide(2,2);
  c1->cd(1);
  ksetar_num->Draw("lego2");
  c1->cd(2);
  laetar_num->Draw("lego2");
  c1->cd(3);
  ksptr_num->Draw("lego2");
  c1->cd(4);
  laptr_num->Draw("lego2");

  TCanvas* c2 = new TCanvas("c2","c2",800,400);
  c2->Divide(2,1);
  c2->cd(1);
  ksetar_num_ratio->SetTitle(";Decay Length (cm);Efficiency of K^{0}_{short}");
  ksetar_num_ratio->GetXaxis()->CenterTitle();
  ksetar_num_ratio->GetYaxis()->CenterTitle();
  ksetar_num_ratio->Draw("");
  c2->cd(2);
  laetar_num_ratio->SetTitle(";Decay Length (cm);Efficiency of #Lambda");
  laetar_num_ratio->GetXaxis()->CenterTitle();
  laetar_num_ratio->GetYaxis()->CenterTitle();
  laetar_num_ratio->Draw("");

//  SaveCanvas(c2,"HI/V0","EfficiencyVsR");
//  SaveCanvas(c,"HI/V0","lasecpt");

  TFile* fout = new TFile("V0Eff_matching.root","recreate");
  ksetar_num_ratio->Write();
  laetar_num_ratio->Write();
  ksetapt_num_ratio->Write();
  laetapt_num_ratio->Write();
  for(int i=0;i<7;i++)
  {
    hEffvsPt_ks[i]->Write();
    hEffvsPt_la[i]->Write();
  }
  lasecetapt_num_ratio->Write();
  hYieldRecoEta_ks_ratio->Write();
  hYieldRecoEta_la_ratio->Write();
  fout->Close();
}
