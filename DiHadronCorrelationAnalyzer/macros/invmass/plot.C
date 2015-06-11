void plot()
{
  TFile* f[10];
  f[0] = new TFile("output_mb035.root");
  f[1] = new TFile("output_mb3560.root");
  f[2] = new TFile("output_mb6090.root");
  f[3] = new TFile("output_mb90120.root");
  f[4] = new TFile("output_hm120150.root");
  f[5] = new TFile("output_hm150185.root");
  f[6] = new TFile("output_hm185220.root");
  f[7] = new TFile("output_hm220260.root");

  TGraphErrors* gr[10];

  for(int i=0;i<8;i++)
  {
    gr[i] = (TGraphErrors*)f[i]->Get("yield");
    gr[i]->SetMarkerColor(i+1);
  }

  TCanvas* c2 = new TCanvas("c2","c2",500,500);
  c2->SetLogy();
  TH2D* htmp = new TH2D("htmp",";p_{T} (GeV/c);Yield",10000,0,10,10000,0.00000001,10);
  htmp->Draw();
//  gr[7]->Draw("PESAME");
  gr[6]->Draw("PESAME");
//  gr[5]->Draw("PESAME");
  gr[4]->Draw("PESAME");
//  gr[3]->Draw("PESAME");
  gr[2]->Draw("PESAME");
//  gr[1]->Draw("PESAME");
  gr[0]->Draw("PESAME");
}
