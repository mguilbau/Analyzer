void nmult_pPb()
{
  TFile* f[10];
  f[0] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/mult_mb_all.root");
  f[1] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/mult_hm100_all.root");
  f[2] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/mult_hm130_all.root");
  f[3] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/mult_hm160_all.root");
  f[4] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/mult_hm190_all.root");

  TH1D* hmult[10];
  hmult[0] = (TH1D*)f[0]->Get("corr_ana_pPb/multrawall");
  hmult[1] = (TH1D*)f[1]->Get("corr_ana_pPb/multrawall");
  hmult[2] = (TH1D*)f[2]->Get("corr_ana_pPb/multrawall");
  hmult[3] = (TH1D*)f[3]->Get("corr_ana_pPb/multrawall");
  hmult[4] = (TH1D*)f[4]->Get("corr_ana_pPb/multrawall");

  hmult[0]->Scale(1.0/hmult[0]->Integral());
  hmult[1]->Scale(1.0/hmult[1]->Integral());
  hmult[2]->Scale(1.0/hmult[2]->Integral());
  hmult[3]->Scale(1.0/hmult[3]->Integral());
  hmult[4]->Scale(1.0/hmult[4]->Integral());
  hmult[2]->Scale(1.0/hmult[2]->GetBinContent(180)*hmult[0]->GetBinContent(180));
  hmult[4]->Scale(1.0/hmult[4]->GetBinContent(250)*hmult[2]->GetBinContent(250));

  hmult[0]->SetMarkerStyle(20);
  hmult[1]->SetMarkerStyle(20);
  hmult[2]->SetMarkerStyle(20);
  hmult[3]->SetMarkerStyle(20);
  hmult[4]->SetMarkerStyle(20);
  hmult[0]->SetMarkerColor(1);
  hmult[1]->SetMarkerColor(kGreen+10);
  hmult[2]->SetMarkerColor(4);
  hmult[3]->SetMarkerColor(6);
  hmult[4]->SetMarkerColor(2);

  TH1D* htmp = (TH1D*)hmult[0]->Clone("htmp");
  htmp->Reset();

  TCanvas* c = new TCanvas("c","",550,500);
  c->SetLogy();
  htmp->SetAxisRange(0,450,"X");
  htmp->SetAxisRange(0.000000000001,0.1,"Y");
  htmp->Draw();
  hmult[0]->SetAxisRange(0,180,"X");
  hmult[0]->Draw("PESAME");
  hmult[2]->SetAxisRange(180,250,"X");
  hmult[2]->Draw("PESAME");
  hmult[4]->SetAxisRange(250,500,"X");
  hmult[4]->Draw("PESAME");
}
