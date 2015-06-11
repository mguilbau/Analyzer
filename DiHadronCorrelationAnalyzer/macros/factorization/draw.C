void draw()
{
  TFile* f_mb = new TFile("output_pixelclustershape_mbgoodcoll.root");
  TFile* f_ucc = new TFile("output_pixelclustershape_ucc.root");

  TNtuple* nt_mb = (TNtuple*)f_mb->Get("ana/ntuple");
  TNtuple* nt_ucc = (TNtuple*)f_ucc->Get("ana/ntuple");

  TH2D* hCompVsNcluster_mb = new TH2D("hCompVsNcluster_mb",";Pixel Cluster Multiplicity;Compatibility",100,0,110000,100,0,6);
  TH2D* hCompVsNcluster_ucc = new TH2D("hCompVsNcluster_ucc",";Pixel Cluster Multiplicity;Compatibility",100,0,110000,100,0,6);
  TH2D* hCompVsHF_mb = new TH2D("hCompVsHF_mb",";HF Energy Sum (GeV);Compatibility",100,0,7000,100,0,6);
  TH2D* hCompVsHF_ucc = new TH2D("hCompVsHF_ucc",";HF Energy Sum (GeV);Compatibility",100,0,7000,100,0,6);
  TH2D* hZDCVsNcluster_mb = new TH2D("hZDCVsNcluster_mb",";Pixel Cluster Multiplicity;ZDC Energy Sum (a.u.)",100,0,110000,100,0,400);
  TH2D* hZDCVsNcluster_ucc = new TH2D("hZDCVsNcluster_ucc",";Pixel Cluster Multiplicity;ZDC Energy Sum (a.u.)",100,0,110000,100,0,400);
  TH2D* hZDCVsHF_mb = new TH2D("hZDCVsHF_mb",";HF Energy Sum (GeV);ZDC Energy Sum (a.u.)",100,0,7000,100,0,400);
  TH2D* hZDCVsHF_ucc = new TH2D("hZDCVsHF_ucc",";HF Energy Sum (GeV);ZDC Energy Sum (a.u.)",100,0,7000,100,0,400);


  nt_mb->Draw("Compatibility:Npxl>>hCompVsNcluster_mb","Compatibility>0 && NClusters>0 && (7.0*HFt+ZDC)<36000","GOFF");
  nt_ucc->Draw("Compatibility:Npxl>>hCompVsNcluster_ucc","Compatibility>0 && NClusters>0 && (7.0*HFt+ZDC)<36000","GOFF");
  nt_mb->Draw("Compatibility:HFt>>hCompVsHF_mb","Compatibility>0 && NClusters>0 && (7.0*HFt+ZDC)<36000","GOFF");
  nt_ucc->Draw("Compatibility:HFt>>hCompVsHF_ucc","Compatibility>0 && NClusters>0 && (7.0*HFt+ZDC)<36000","GOFF");
/*
  nt_mb->Draw("Compatibility:Npxl>>hCompVsNcluster_mb","Compatibility>0 && NClusters>0 && ZDC>0","GOFF");
  nt_ucc->Draw("Compatibility:Npxl>>hCompVsNcluster_ucc","Compatibility>0 && NClusters>0 && ZDC>0","GOFF");
  nt_mb->Draw("Compatibility:HFt>>hCompVsHF_mb","Compatibility>0 && NClusters>0 && ZDC>0","GOFF");
  nt_ucc->Draw("Compatibility:HFt>>hCompVsHF_ucc","Compatibility>0 && NClusters>0 && ZDC>0","GOFF");
*/
  nt_mb->Draw("(ZDC/100):Npxl>>hZDCVsNcluster_mb","Compatibility>0 && NClusters>0","GOFF");
  nt_ucc->Draw("(ZDC/100):Npxl>>hZDCVsNcluster_ucc","Compatibility>0 && NClusters>0","GOFF");
//  nt_mb->Draw("ZDC:HFt>>hZDCVsHF_mb","Compatibility>0 && NClusters>0 && ZDC>0 && (0.38*NClusters+ZDC)<36000","GOFF");
//  nt_ucc->Draw("ZDC:HFt>>hZDCVsHF_ucc","Compatibility>0 && NClusters>0 && ZDC>0 && (0.38*NClusters+ZDC)<36000","GOFF");
  nt_mb->Draw("(ZDC/100):HFt>>hZDCVsHF_mb","Compatibility>0 && NClusters>0","GOFF");
  nt_ucc->Draw("(ZDC/100):HFt>>hZDCVsHF_ucc","Compatibility>0 && NClusters>0","GOFF");

  TF1* func = new TF1("func","0.01*(-7.0*x+36000)",0,110000);
  TF1* func1 = new TF1("func1","1.15*x*0.01",0,110000);

  TCanvas* c = new TCanvas("c","",600,500);
  c->SetLogz();
  hCompVsHF_mb->GetXaxis()->CenterTitle();
  hCompVsHF_mb->GetYaxis()->CenterTitle();
  hCompVsHF_mb->GetYaxis()->SetTitleOffset(hCompVsHF_mb->GetYaxis()->GetTitleOffset()*1.2);
  hCompVsHF_mb->GetXaxis()->SetLabelSize(hCompVsHF_mb->GetXaxis()->GetLabelSize()*0.8);
  hCompVsHF_mb->GetYaxis()->SetLabelSize(hCompVsHF_mb->GetYaxis()->GetLabelSize()*0.8);
  hCompVsHF_mb->Draw("colz");
  SaveCanvas(c,"HI/UCC","CompVsHF_mb_purej");

  TCanvas* ca = new TCanvas("ca","",600,500);
  ca->SetLogz();
  hCompVsHF_ucc->GetXaxis()->CenterTitle();
  hCompVsHF_ucc->GetYaxis()->CenterTitle();
  hCompVsHF_ucc->GetYaxis()->SetTitleOffset(hCompVsHF_ucc->GetYaxis()->GetTitleOffset()*1.2);
  hCompVsHF_ucc->GetXaxis()->SetLabelSize(hCompVsHF_ucc->GetXaxis()->GetLabelSize()*0.8);
  hCompVsHF_ucc->GetYaxis()->SetLabelSize(hCompVsHF_ucc->GetYaxis()->GetLabelSize()*0.8);
  hCompVsHF_ucc->Draw("colz");
  SaveCanvas(ca,"HI/UCC","CompVsHF_ucc_purej");

  TCanvas* c1 = new TCanvas("c1","",600,500);
  c1->SetLogz();
  hZDCVsNcluster_mb->Draw("colz");
/*
  c1->Print("pics/ZDCVsNcluster_mb.gif");
  c1->Print("pics/ZDCVsNcluster_mb.eps");
  c1->Print("pics/ZDCVsNcluster_mb.pdf");
  c1->Print("pics/ZDCVsNcluster_mb.C");
*/
  TCanvas* ca1 = new TCanvas("ca1","",600,500);
  ca1->SetLogz();
  hZDCVsNcluster_ucc->Draw("colz");
/*
  ca1->Print("pics/ZDCVsNcluster_ucc.gif");
  ca1->Print("pics/ZDCVsNcluster_ucc.eps");
  ca1->Print("pics/ZDCVsNcluster_ucc.pdf");
  ca1->Print("pics/ZDCVsNcluster_ucc.C");
*/
  TCanvas* c2 = new TCanvas("c2","",550,500);
  c2->SetLogz();
  hZDCVsHF_mb->GetXaxis()->CenterTitle();
  hZDCVsHF_mb->GetYaxis()->CenterTitle();
  hZDCVsHF_mb->GetYaxis()->SetTitleOffset(hZDCVsHF_mb->GetYaxis()->GetTitleOffset()*1.2);
  hZDCVsHF_mb->GetXaxis()->SetLabelSize(hZDCVsHF_mb->GetXaxis()->GetLabelSize()*0.8);
  hZDCVsHF_mb->GetYaxis()->SetLabelSize(hZDCVsHF_mb->GetYaxis()->GetLabelSize()*0.8);
  hZDCVsHF_mb->Draw("colz");
  func->Draw("Lsame");
  TLatex* latex = new TLatex();
  latex->SetNDC(1);
  latex->SetTextSize(latex->GetTextSize()*1.0);
  latex->DrawLatex(0.65,0.88,"CMS Preliminary");
  latex->DrawLatex(0.57,0.82,"PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  SaveCanvas(c2,"HI/UCC","ZDCVsHF_mb");

  TCanvas* ca2 = new TCanvas("ca2","",550,500);
  ca2->SetLogz();
  hZDCVsHF_ucc->GetXaxis()->CenterTitle();
  hZDCVsHF_ucc->GetYaxis()->CenterTitle();
  hZDCVsHF_ucc->GetYaxis()->SetTitleOffset(hZDCVsHF_ucc->GetYaxis()->GetTitleOffset()*1.2);
  hZDCVsHF_ucc->GetXaxis()->SetLabelSize(hZDCVsHF_ucc->GetXaxis()->GetLabelSize()*0.8);
  hZDCVsHF_ucc->GetYaxis()->SetLabelSize(hZDCVsHF_ucc->GetYaxis()->GetLabelSize()*0.8);
  hZDCVsHF_ucc->Draw("colz");
//  func1->Draw("Lsame");
  func->Draw("Lsame");
  TLatex* latex2 = new TLatex();
  latex2->SetNDC(1);
  latex2->SetTextSize(latex2->GetTextSize()*1.0);
  latex2->DrawLatex(0.65,0.88,"CMS Preliminary");
  latex2->DrawLatex(0.57,0.82,"PbPb  #sqrt{s_{NN}} = 2.76 TeV");

  SaveCanvas(ca2,"HI/UCC","ZDCVsHF_ucc");

return;
  TCanvas* cc = new TCanvas("cc","",700,500);
  hCompVsNcluster_ucc->GetXaxis()->CenterTitle();
  hCompVsNcluster_ucc->GetYaxis()->CenterTitle();
  hCompVsNcluster_ucc->GetYaxis()->SetTitleOffset(hCompVsNcluster_ucc->GetYaxis()->GetTitleOffset()*1.2);
  hCompVsNcluster_ucc->GetXaxis()->SetLabelSize(hCompVsNcluster_ucc->GetXaxis()->GetLabelSize()*0.8);
  hCompVsNcluster_ucc->GetYaxis()->SetLabelSize(hCompVsNcluster_ucc->GetYaxis()->GetLabelSize()*0.8);
  cc->SetLogz();
  hCompVsNcluster_ucc->Draw("colz");
  SaveCanvas(cc,"HI/UCC","CompVsNcluster_ucc");

  TCanvas* cc1 = new TCanvas("cc1","",700,500);
  cc1->SetLogz();
  hZDCVsNcluster_ucc->Draw("colz");
/*
  cc1->Print("pics/ZDCVsNcluster_ucc.gif");
  cc1->Print("pics/ZDCVsNcluster_ucc.eps");
  cc1->Print("pics/ZDCVsNcluster_ucc.pdf");
  cc1->Print("pics/ZDCVsNcluster_ucc.C");
*/
}
