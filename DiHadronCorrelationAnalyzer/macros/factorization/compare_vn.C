#include "/net/hisrv0001/home/davidlw/useful_macros/makeMultiPanelCanvas.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/GetGraphFromFile.C"

void compare_vn()
{
  TFile* f = new TFile("gr_UCC_centmin110_centmax1000.root");
  TFile* f1 = new TFile("gr_UCC_centmin110_centmax1000_zvtx2.root");

  TGraph* gr = (TGraph*)f->Get("vnn");
  TGraph* gr1 = (TGraph*)f1->Get("vnn");

  TH2D* htmp1 = new TH2D("htmp1",";n;v_{n}",100,0,10.99,100,-0.005,0.05);

  TCanvas* c = new TCanvas("c","c",600,500);
//  c->SetLogy();
  htmp1->Draw();
  gr->Draw("pesame");
  gr1->SetMarkerColor(kRed);
  gr1->Draw("pesame");
/*
  c->Print("/net/hisrv0001/home/davidlw/scratch1/UCCPileUp/pics/compare_vnn_zdccut.gif");
  c->Print("/net/hisrv0001/home/davidlw/scratch1/UCCPileUp/pics/compare_vnn_zdccut.pdf");
  c->Print("/net/hisrv0001/home/davidlw/scratch1/UCCPileUp/pics/compare_vnn_zdccut.eps");
  c->Print("/net/hisrv0001/home/davidlw/scratch1/UCCPileUp/pics/compare_vnn_zdccut.C");
*/
}

void compare_vn4()
{
  TFile* f = new TFile("gr_UCC_centmin110_centmax1000.root");

  TGraph* gr_v2 = (TGraph*)f->Get("v2pt_corr");
  TGraph* gr_v3 = (TGraph*)f->Get("v3pt_corr");
  TGraph* gr_v4 = (TGraph*)f->Get("v4pt_corr");
  TGraph* gr_v5 = (TGraph*)f->Get("v5pt_corr");
  TGraph* gr_v6 = (TGraph*)f->Get("v6pt_corr");
  TGraph* gr_v2_sys = (TGraph*)f->Get("v2pt_syst");
  TGraph* gr_v3_sys = (TGraph*)f->Get("v3pt_syst");
  TGraph* gr_v4_sys = (TGraph*)f->Get("v4pt_syst");
  TGraph* gr_v5_sys = (TGraph*)f->Get("v5pt_syst");
  TGraph* gr_v6_sys = (TGraph*)f->Get("v6pt_syst");
  gr_v2->SetMarkerColor(1);
  gr_v3->SetMarkerColor(1);
  gr_v4->SetMarkerColor(1);
  gr_v5->SetMarkerColor(1);
  gr_v6->SetMarkerColor(1);
  gr_v2->SetMarkerStyle(20);
  gr_v3->SetMarkerStyle(20);
  gr_v4->SetMarkerStyle(20);
  gr_v5->SetMarkerStyle(20);
  gr_v6->SetMarkerStyle(20);
  gr_v2_sys->SetFillColor(TColor::GetColor("#ffff00"));
  gr_v3_sys->SetFillColor(TColor::GetColor("#ffff00"));
  gr_v4_sys->SetFillColor(TColor::GetColor("#ffff00"));
  gr_v5_sys->SetFillColor(TColor::GetColor("#ffff00"));
  gr_v6_sys->SetFillColor(TColor::GetColor("#ffff00"));

  TGraph* gr_vnn = (TGraph*)f->Get("vnn_corr");
  gr_vnn->SetMarkerColor(1);
  TGraph* gr_vnn_sys = (TGraph*)f->Get("vnn_corr_sys");
  gr_vnn_sys->SetFillColor(TColor::GetColor("#ffff00"));

  TGraphAsymmErrors* gr_v2_glb_008_uli = (TGraphAsymmErrors*)GetGraphWithErrorsFromFile("ChHdv2_pt_Glb.dat",4,20,1.3);
  TGraphAsymmErrors* gr_v3_glb_008_uli = (TGraphAsymmErrors*)GetGraphWithErrorsFromFile("ChHdv3_pt_Glb.dat",4,20,1.3);
  TGraphAsymmErrors* gr_v4_glb_008_uli = (TGraphAsymmErrors*)GetGraphWithErrorsFromFile("ChHdv4_pt_Glb.dat",4,20,1.3);
  TGraphAsymmErrors* gr_v5_glb_008_uli = (TGraphAsymmErrors*)GetGraphWithErrorsFromFile("ChHdv5_pt_Glb.dat",4,20,1.3);
  TGraphAsymmErrors* gr_v6_glb_008_uli = (TGraphAsymmErrors*)GetGraphWithErrorsFromFile("ChHdv6_pt_Glb.dat",4,20,1.3);
  gr_v2_glb_008_uli->SetFillColor(kCyan);
  gr_v3_glb_008_uli->SetFillColor(kCyan);
  gr_v4_glb_008_uli->SetFillColor(kCyan);
  gr_v5_glb_008_uli->SetFillColor(kCyan);
  gr_v6_glb_008_uli->SetFillColor(kCyan);

  TGraphAsymmErrors* gr_v2_kln_020_uli = (TGraphAsymmErrors*)GetGraphWithErrorsFromFile("ChHdv2_pt_KLN.dat",8,20,1.3);
  TGraphAsymmErrors* gr_v3_kln_020_uli = (TGraphAsymmErrors*)GetGraphWithErrorsFromFile("ChHdv3_pt_KLN.dat",8,20,1.3);
  TGraphAsymmErrors* gr_v4_kln_020_uli = (TGraphAsymmErrors*)GetGraphWithErrorsFromFile("ChHdv4_pt_KLN.dat",8,20,1.3);
  TGraphAsymmErrors* gr_v5_kln_020_uli = (TGraphAsymmErrors*)GetGraphWithErrorsFromFile("ChHdv5_pt_KLN.dat",8,20,1.3);
  TGraphAsymmErrors* gr_v6_kln_020_uli = (TGraphAsymmErrors*)GetGraphWithErrorsFromFile("ChHdv6_pt_KLN.dat",8,20,1.3);
  gr_v2_kln_020_uli->SetFillColor(kGreen); 
  gr_v3_kln_020_uli->SetFillColor(kGreen);
  gr_v4_kln_020_uli->SetFillColor(kGreen);
  gr_v5_kln_020_uli->SetFillColor(kGreen);
  gr_v6_kln_020_uli->SetFillColor(kGreen); 

  TGraphAsymmErrors* gr_vnn_glb_008_uli = (TGraphAsymmErrors*)GetGraphWithErrorsFromFile("ChHdvn_int_Glb.dat",4,20,1.3);
  TGraphAsymmErrors* gr_vnn_kln_020_uli = (TGraphAsymmErrors*)GetGraphWithErrorsFromFile("ChHdvn_int_KLN.dat",8,20,1.3);
  gr_vnn_glb_008_uli->SetFillColor(kCyan);
  gr_vnn_kln_020_uli->SetFillColor(kGreen);

  TH2D* htmp1 = new TH2D("htmp1",";p_{T} (GeV/c);v_{n}{2part,|#Delta#eta|>2}",100,0.1,2.95,100,-0.005,0.13);
  htmp1->GetYaxis()->SetTitleOffset(htmp1->GetYaxis()->GetTitleOffset()*0.93);
  htmp1->GetYaxis()->SetTitleSize(htmp1->GetYaxis()->GetTitleSize()*1.4);
  htmp1->GetXaxis()->CenterTitle();
  htmp1->GetYaxis()->CenterTitle();
  TH2D* htmp2 = (TH2D*)htmp1->Clone("htmp2");
  TH2D* htmp3 = (TH2D*)htmp1->Clone("htmp3");
  TH2D* htmp4 = (TH2D*)htmp1->Clone("htmp4");
  htmp4->GetYaxis()->SetLabelSize(htmp4->GetYaxis()->GetLabelSize()*0.8);
  htmp4->GetYaxis()->SetTitleOffset(htmp4->GetYaxis()->GetTitleOffset()*1.2);
  htmp4->GetYaxis()->SetTitleSize(htmp4->GetYaxis()->GetTitleSize()*0.8);
  TH2D* htmp5 = (TH2D*)htmp1->Clone("htmp5");
  htmp5->GetXaxis()->SetLabelSize(htmp5->GetXaxis()->GetLabelSize()*1.1);
  htmp5->GetXaxis()->SetTitleSize(htmp5->GetXaxis()->GetTitleSize()*1.2);
  htmp5->GetXaxis()->SetTitleOffset(htmp5->GetXaxis()->GetTitleOffset()*0.85);
  htmp5->GetXaxis()->SetLabelOffset(htmp5->GetXaxis()->GetLabelOffset()*0.1);


  TLine* line1 = new TLine(0.0,0.0,2.95,0.0);
  line1->SetLineStyle(9);

  TCanvas* c = new TCanvas("c","c",830,600);
  makeMultiPanelCanvas(c,3,2,0.01,0.0,0.18,0.2,0.04);
  c->cd(1);
  htmp1->Draw();
  gr_v2_sys->Draw("fsame");
  gr_v2_glb_008_uli->Draw("3");
  gr_v2_glb_008_uli->Draw("cx");
  gr_v2_kln_020_uli->Draw("3");
  gr_v2_kln_020_uli->Draw("cx");  
  gr_v2->Draw("pesame");
  line1->Draw("lsame");
  TLatex* latex1 = new TLatex();
  latex1->SetTextSize(1.2*latex1->GetTextSize());
  latex1->SetNDC();
  latex1->DrawLatex(0.24,0.8,"n=2");
  c->cd(2);
  htmp2->Draw();
  gr_v3_sys->Draw("fsame");
  gr_v3_glb_008_uli->Draw("3");
  gr_v3_glb_008_uli->Draw("cx");
  gr_v3_kln_020_uli->Draw("3");
  gr_v3_kln_020_uli->Draw("cx");
  gr_v3->Draw("pesame");
  line1->Draw("lsame");
  TLatex* latex2 = new TLatex();
  latex2->SetTextSize(1.2*latex2->GetTextSize());
  latex2->SetNDC();
  latex2->DrawLatex(0.07,0.8,"n=3");
  c->cd(3);
  htmp3->Draw();
  gr_v4_sys->Draw("fsame");
  gr_v4_glb_008_uli->Draw("3");
  gr_v4_glb_008_uli->Draw("cx");
  gr_v4_kln_020_uli->Draw("3");
  gr_v4_kln_020_uli->Draw("cx");
  gr_v4->Draw("pesame");
  line1->Draw("lsame");
  TLatex* latex3 = new TLatex();
  latex3->SetTextSize(1.2*latex3->GetTextSize());
  latex3->SetNDC();
  latex3->DrawLatex(0.07,0.8,"n=4");
  c->cd(4);
  htmp4->Draw();
  gr_v5_sys->Draw("fsame");
  gr_v5_glb_008_uli->Draw("3");
  gr_v5_glb_008_uli->Draw("cx");
  gr_v5_kln_020_uli->Draw("3");
  gr_v5_kln_020_uli->Draw("cx");
  gr_v5->Draw("pesame");
  line1->Draw("lsame");
  TLatex* latex4 = new TLatex();
  latex4->SetTextSize(1.2*latex4->GetTextSize());
  latex4->SetNDC();
  latex4->DrawLatex(0.24,0.85,"n=5");
  c->cd(5);
  htmp5->Draw();
  gr_v6_sys->Draw("fsame");
  gr_v6_glb_008_uli->Draw("3");
  gr_v6_glb_008_uli->Draw("cx");
  gr_v6_kln_020_uli->Draw("3");
  gr_v6_kln_020_uli->Draw("cx");
  gr_v6->Draw("pesame");
  line1->Draw("lsame");
  TLatex* latex5 = new TLatex();
  latex5->SetTextSize(1.2*latex5->GetTextSize());
  latex5->SetNDC();
  latex5->DrawLatex(0.07,0.85,"n=6");

  TLegend* legend = new TLegend(0.23,0.4,0.78,0.63);
  legend->SetTextFont(42);
  legend->SetFillStyle(0);
  legend->SetHeader("VISH2+1 Hydro");
  legend->AddEntry(gr_v2_glb_008_uli,"Glauber, #eta/s=0.08","L");
  legend->AddEntry(gr_v2_kln_020_uli,"MC-KLN, #eta/s=0.2","L");
  c->cd(1);
  legend->Draw("same");
  TLatex* latex11 = new TLatex();
  latex11->SetNDC(1);
  latex11->SetTextSize(latex11->GetTextSize()*0.8);
  latex11->DrawLatex(0.5,0.86,"CMS Preliminary");
  latex11->DrawLatex(0.5,0.77,"PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  latex11->DrawLatex(0.5,0.7,"0-0.2% centrality");

  SaveCanvas(c,"HI/UCC","compare_vnpt_hydro_uli");

  TH2D* htmp20 = new TH2D("htmp20",";n;v_{n}{2part,|#Delta#eta|>2}",100,1.5,7.79,100,-0.005,0.038);
  htmp20->GetYaxis()->SetTitleOffset(htmp20->GetYaxis()->GetTitleOffset()*1.2);
  htmp20->GetXaxis()->SetTitleOffset(htmp20->GetXaxis()->GetTitleOffset()*0.7);
  htmp20->GetYaxis()->SetLabelSize(htmp20->GetYaxis()->GetLabelSize()*0.8);
  htmp20->GetXaxis()->SetLabelSize(htmp20->GetXaxis()->GetLabelSize()*0.8);
  htmp20->GetXaxis()->CenterTitle();
  htmp20->GetYaxis()->CenterTitle();
  TLine* line2 = new TLine(1.5,0.0,7.49,0.0);
  line2->SetLineStyle(9);
  line2->Draw("lsame");

  TCanvas* c1 = new TCanvas("c1","c1",500,500);
  c1->SetLeftMargin(0.18);
  c1->SetBottomMargin(0.13);
  c1->SetRightMargin(0.02);
  htmp20->Draw("");
  line2->Draw("Lsame");
  drawSystBox(gr_vnn,gr_vnn_sys); 
//  drawSystBoxTheory(gr_vnn_glb_008_uli,gr_vnn_glb_008_uli->GetFillColor(),4);
//  drawSystBoxTheory(gr_vnn_kln_020_uli,gr_vnn_kln_020_uli->GetFillColor(),8);
  gr_vnn->SetMarkerStyle(20);
//  gr_vnn_sys->Draw("FSAME");
/*
  gr_vnn_glb_008_uli->Draw("3");
  gr_vnn_glb_008_uli->Draw("cx");
  gr_vnn_kln_020_uli->Draw("3");
  gr_vnn_kln_020_uli->Draw("cx");
*/
  gr_vnn->Draw("PESAME");

  TLegend* legend1 = new TLegend(0.25,0.23,0.58,0.38);
  legend1->SetTextFont(42);
  legend1->SetFillStyle(0);
//  legend1->AddEntry(gr_vnn,"","P");
  legend1->Draw("same");
  TLatex* latex2 = new TLatex();
  latex2->SetNDC(1);
  latex2->SetTextSize(latex2->GetTextSize()*1.0);
  latex2->DrawLatex(0.55,0.87,"CMS Preliminary");
  latex2->DrawLatex(0.55,0.80,"PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  latex2->DrawLatex(0.55,0.75,"0-0.2% centrality");
  latex2->DrawLatex(0.2,0.24,"0.3 < p_{T} < 3 GeV/c");

  TLegend* legend1 = new TLegend(0.53,0.55,0.93,0.68);
  legend1->SetTextFont(42);
  legend1->SetFillStyle(0);
  legend1->SetHeader("VISH2+1 Hydro");
  legend1->AddEntry(gr_vnn_glb_008_uli,"Glauber, #eta/s=0.08","L");
  legend1->AddEntry(gr_vnn_kln_020_uli,"MC-KLN, #eta/s=0.2","L");
  c1->cd(1);
//  legend1->Draw("same");

//  SaveCanvas(c1,"HI/UCC","compare_vnn_hydro_uli");
  SaveCanvas(c1,"HI/UCC","compare_vnn_notheory");
}


void compare_vn3()
{
  TF1* f[5];
  double a[5]={0.349796,0.3043,0.19742,0.0988182,0.042765};
  double b[5]={-0.762338,-0.676579,-0.696441,-0.47842,-0.26643};
  double c[5]={1.22181,0.599942,0.903908,0.648075,0.360201};
  for(int i=0;i<5;i++)
  {
    f[i] = new TF1(Form("hydro_v%d",i+2),"[0]+[1]*x+[2]*x*x",0,0.4);
    f[i]->SetParameters(a[i],b[i],c[i]);
    f[i]->SetLineColor(i+1);
  }
  f[4]->SetLineColor(6);

  TH2D* htmp = new TH2D("htmp",";#eta/s;v_{n}{2}/#epsilon_{n}{2}",100,0,0.2,100,0,0.4);
  htmp->GetXaxis()->CenterTitle();
  htmp->GetYaxis()->CenterTitle();

  TCanvas* cc = new TCanvas("cc","cc",550,500);
  htmp->Draw("");
  f[0]->Draw("Lsame");
  f[1]->Draw("Lsame");
  f[2]->Draw("Lsame");
  f[3]->Draw("Lsame");
  f[4]->Draw("Lsame");
  SaveCanvas(cc,"HI/UCC","vnepsilonn_vs_etas_hydro");

  TFile* ff = new TFile("gr_UCC_centmin110_centmax1000.root");
  TGraph* gr_v2 = (TGraph*)ff->Get("v2pt_corr");
  TGraph* gr_v3 = (TGraph*)ff->Get("v3pt_corr");
  TGraph* gr_v4 = (TGraph*)ff->Get("v4pt_corr");
  TGraph* gr_v5 = (TGraph*)ff->Get("v5pt_corr");
  TGraph* gr_v6 = (TGraph*)ff->Get("v6pt_corr");
  TGraph* gr_vnn = (TGraph*)ff->Get("vnn_corr");
  TGraph* gr_vnn_sys = (TGraph*)ff->Get("vnn_corr_sys");
  gr_vnn_sys->SetFillColor(TColor::GetColor("#ffff00"));

  double n[5] = {2,3,4,5,6};
  double vn_ideal[5];
  double vn_004[5];
  double vn_008[5];
  double vn_012[5];  
  double vn_016[5];
  double vn_020[5];
  double vn_024[5];
  double ecc[5]={0.0940024,0.0981397,0.105829,0.11521,0.126895};
  double factor = 1.0;

  for(int i=0;i<5;i++)
  {
    vn_ideal[i] = f[i]->Eval(0)*ecc[i]*factor;
    vn_004[i] = f[i]->Eval(0.04)*ecc[i]*factor;
    vn_008[i] = f[i]->Eval(0.08)*ecc[i]*factor;
    vn_012[i] = f[i]->Eval(0.12)*ecc[i]*factor;
    vn_016[i] = f[i]->Eval(0.16)*ecc[i]*factor;
    vn_020[i] = f[i]->Eval(0.2)*ecc[i]*factor;
    vn_024[i] = f[i]->Eval(0.24)*ecc[i]*factor;
  }

  TGraph* gr_vn_ideal = new TGraph(5,n,vn_ideal);
  TGraph* gr_vn_004 = new TGraph(5,n,vn_004);
  TGraph* gr_vn_008 = new TGraph(5,n,vn_008);
  TGraph* gr_vn_012 = new TGraph(5,n,vn_012);
  TGraph* gr_vn_016 = new TGraph(5,n,vn_016);
  TGraph* gr_vn_020 = new TGraph(5,n,vn_020);
  TGraph* gr_vn_024 = new TGraph(5,n,vn_024);
  gr_vn_ideal->SetLineColor(1);
  gr_vn_004->SetLineColor(2);
  gr_vn_008->SetLineColor(4);
  gr_vn_012->SetLineColor(4);
  gr_vn_016->SetLineColor(7);
  gr_vn_020->SetLineColor(8);
  gr_vn_024->SetLineColor(8);

  TH2D* htmp20 = new TH2D("htmp20",";n;v_{n}{2part,|#Delta#eta|>2}",100,1.5,7.79,100,-0.005,0.038);
  htmp20->GetYaxis()->SetLabelSize(htmp20->GetYaxis()->GetLabelSize()*0.8);
  htmp20->GetXaxis()->SetLabelSize(htmp20->GetXaxis()->GetLabelSize()*0.8);
  htmp20->GetYaxis()->SetTitleOffset(htmp20->GetYaxis()->GetTitleOffset()*1.2);
  htmp20->GetXaxis()->SetTitleOffset(htmp20->GetXaxis()->GetTitleOffset()*0.7);
  htmp20->GetXaxis()->CenterTitle();
  htmp20->GetYaxis()->CenterTitle();
  TLine* line2 = new TLine(1.5,0.0,7.79,0.0);
  line2->SetLineStyle(9);

  TLegend* legend = new TLegend(0.57,0.56,0.95,0.71);
  legend->SetFillStyle(0);
  legend->SetTextFont(42);
  legend->SetLineWidth(3);
  legend->AddEntry(gr_vn_ideal,"Glauber, #eta/s=0","L");
//  legend->AddEntry(gr_vn_004,"#eta/s=0.04","L");
  legend->AddEntry(gr_vn_008,"Glauber, #eta/s=0.08","L");
//  legend->AddEntry(gr_vn_012,"#eta/s=0.12","L");
//  legend->AddEntry(gr_vn_016,"#eta/s=0.16","L");
  legend->AddEntry(gr_vn_020,"Glauber, #eta/s=0.20","L");

  TCanvas* c1 = new TCanvas("c1","c1",500,500);
  c1->SetLeftMargin(0.18);
  c1->SetBottomMargin(0.13);
  c1->SetRightMargin(0.02);
  htmp20->Draw("");
//  gr_vnn_sys->Draw("Fsame");
  drawSystBox(gr_vnn,gr_vnn_sys); 
  gr_vnn->SetMarkerStyle(20);
  gr_vnn->Draw("PESAME");
  drawLineTheory(gr_vn_ideal,1);
//  drawLineTheory(gr_vn_004,2);
  drawLineTheory(gr_vn_008,4);
//  drawLineTheory(gr_vn_012,4);
//  drawLineTheory(gr_vn_016,7);
  drawLineTheory(gr_vn_020,8);
//  gr_vn_024->Draw("Lsame");

  legend->Draw("same");
  line2->Draw("lsame");

  TLatex* latex1 = new TLatex();
  latex1->SetNDC(1);
  latex1->SetTextSize(latex1->GetTextSize()*1.0);
  latex1->DrawLatex(0.55,0.87,"CMS Preliminary");
  latex1->DrawLatex(0.55,0.80,"PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  latex1->DrawLatex(0.55,0.75,"0-0.2% centrality");
  latex1->DrawLatex(0.2,0.24,"0.3 < p_{T} < 3 GeV/c");

  SaveCanvas(c1,"HI/UCC","compare_vnn_hydro_luzum");
}

void compare_vn2()
{
  TFile* f = new TFile("gr_UCC_centmin110_centmax1000.root");
  TFile* f2 = new TFile("gr_UCC_centmin110_centmax1000_lowptass.root");
  TFile* f1 = new TFile("gr_UCC_centmin110_centmax1000_zvtx2.root");
  TFile* f3 = new TFile("gr_UCC_centmin110_centmax1000_highptass.root");

  TGraphErrors* gr_v2 = (TGraphErrors*)f->Get("v2pt_corr");
  TGraphErrors* gr_v3 = (TGraphErrors*)f->Get("v3pt_corr");
  TGraphErrors* gr_v4 = (TGraphErrors*)f->Get("v4pt_corr");
  TGraphErrors* gr_v5 = (TGraphErrors*)f->Get("v5pt_corr");
  TGraphErrors* gr_v6 = (TGraphErrors*)f->Get("v6pt_corr");

  TGraphErrors* gr1_v2 = (TGraphErrors*)f1->Get("v2pt_corr");
  TGraphErrors* gr1_v3 = (TGraphErrors*)f1->Get("v3pt_corr");
  TGraphErrors* gr1_v4 = (TGraphErrors*)f1->Get("v4pt_corr");
  TGraphErrors* gr1_v5 = (TGraphErrors*)f1->Get("v5pt_corr");
  TGraphErrors* gr1_v6 = (TGraphErrors*)f1->Get("v6pt_corr");

  TGraphErrors* gr2_v2 = (TGraphErrors*)f2->Get("v2pt_corr");
  TGraphErrors* gr2_v3 = (TGraphErrors*)f2->Get("v3pt_corr");
  TGraphErrors* gr2_v4 = (TGraphErrors*)f2->Get("v4pt_corr");
  TGraphErrors* gr2_v5 = (TGraphErrors*)f2->Get("v5pt_corr");
  TGraphErrors* gr2_v6 = (TGraphErrors*)f2->Get("v6pt_corr");

  TGraphErrors* gr3_v2 = (TGraphErrors*)f3->Get("v2pt_corr");
  TGraphErrors* gr3_v3 = (TGraphErrors*)f3->Get("v3pt_corr");
  TGraphErrors* gr3_v4 = (TGraphErrors*)f3->Get("v4pt_corr");
  TGraphErrors* gr3_v5 = (TGraphErrors*)f3->Get("v5pt_corr");
  TGraphErrors* gr3_v6 = (TGraphErrors*)f3->Get("v6pt_corr");

  cout<<"v_2:"<<endl;
  cout<<"p_{T}    v_2    stat. err."<<endl;
  for(int i=0;i<gr2_v2->GetN();i++) 
  {
    double x,y,yerr;
    gr2_v2->GetPoint(i,x,y);
    yerr = gr2_v2->GetErrorY(i);
    cout<<Form("%.4f  %.4f  %.4f",x,y,yerr)<<endl;
  }

  cout<<"v_3:"<<endl;
  cout<<"p_{T}    v_3    stat. err."<<endl;
  for(int i=0;i<gr2_v3->GetN();i++)
  {
    double x,y,yerr;
    gr2_v3->GetPoint(i,x,y);
    yerr = gr2_v3->GetErrorY(i);
    cout<<Form("%.4f  %.4f  %.4f",x,y,yerr)<<endl;
  }

  cout<<"v_4:"<<endl;
  cout<<"p_{T}    v_4    stat. err."<<endl;
  for(int i=0;i<gr2_v4->GetN();i++)
  {
    double x,y,yerr;
    gr2_v4->GetPoint(i,x,y);
    yerr = gr2_v4->GetErrorY(i);
    cout<<Form("%.4f  %.4f  %.4f",x,y,yerr)<<endl;
  }

  cout<<"v_5:"<<endl;
  cout<<"p_{T}    v_5    stat. err."<<endl;
  for(int i=0;i<gr2_v5->GetN();i++)
  {
    double x,y,yerr;
    gr2_v5->GetPoint(i,x,y);
    yerr = gr2_v5->GetErrorY(i);
    cout<<Form("%.4f  %.4f  %.4f",x,y,yerr)<<endl;
  }

  cout<<"v_6:"<<endl;
  cout<<"p_{T}    v_6    stat. err."<<endl;
  for(int i=0;i<gr2_v6->GetN();i++)
  {
    double x,y,yerr;
    gr2_v6->GetPoint(i,x,y);
    yerr = gr2_v6->GetErrorY(i);
    cout<<Form("%.4f  %.4f  %.4f",x,y,yerr)<<endl;
  }

  gr_v2->SetMarkerColor(2);
  gr_v3->SetMarkerColor(2);
  gr_v4->SetMarkerColor(2);
  gr_v5->SetMarkerColor(2);
  gr_v6->SetMarkerColor(2);

  gr_v2->SetMarkerStyle(20);
  gr_v3->SetMarkerStyle(20);
  gr_v4->SetMarkerStyle(20);
  gr_v5->SetMarkerStyle(20);
  gr_v6->SetMarkerStyle(20);

  gr1_v2->SetMarkerStyle(24);
  gr1_v3->SetMarkerStyle(24);
  gr1_v4->SetMarkerStyle(24);
  gr1_v5->SetMarkerStyle(24);
  gr1_v6->SetMarkerStyle(24);

  gr2_v2->SetMarkerStyle(25);
  gr2_v3->SetMarkerStyle(25);
  gr2_v4->SetMarkerStyle(25);
  gr2_v5->SetMarkerStyle(25);
  gr2_v6->SetMarkerStyle(25);

  gr3_v2->SetMarkerStyle(26);
  gr3_v3->SetMarkerStyle(26);
  gr3_v4->SetMarkerStyle(26);
  gr3_v5->SetMarkerStyle(26);
  gr3_v6->SetMarkerStyle(26);

  TGraph* gr_vnn = (TGraph*)f->Get("vnn_corr");
  TGraph* gr1_vnn = (TGraph*)f1->Get("vnn_corr");
  TGraph* gr2_vnn = (TGraph*)f2->Get("vnn_corr");
  TGraph* gr3_vnn = (TGraph*)f3->Get("vnn_corr");

  gr1_vnn->SetMarkerStyle(24);
  gr2_vnn->SetMarkerStyle(25);
  gr3_vnn->SetMarkerStyle(26);
  gr_vnn->SetMarkerColor(2);

  TGraph* gr_vnn_sys = (TGraph*)f->Get("vnn_corr_sys");
  TGraph* gr1_vnn_sys = (TGraph*)f1->Get("vnn_corr_sys");
  TGraph* gr2_vnn_sys = (TGraph*)f2->Get("vnn_corr_sys");
  TGraph* gr3_vnn_sys = (TGraph*)f3->Get("vnn_corr_sys");

  TFile* fEP_v2 = new TFile("EPSpectra_gt10dz40chi_13_V2.root");
  TFile* fEP_v3 = new TFile("EPSpectra_gt10dz40chi_10_V3.root");
  TFile* fEP_v4 = new TFile("EPSpectra_gt10dz40chi_08_V4.root");
  TFile* fEP_v5 = new TFile("EPSpectra_gt10dz40chi_08_V5.root");
  TFile* fEP_v6 = new TFile("EPSpectra_gt10dz40chi_08_V6.root");
 
  TGraphErrors* gr_v2ep = fEP_v2->Get("-1.0_00.0_00.0_01.0_etHFp_etHFm_13/v2_2_0_5-1.0_00.0_00.0_01.0_etHFp_Corrected");
  TGraphErrors* gr_v3ep = fEP_v3->Get("-1.0_00.0_00.0_01.0_etHFp3_etHFm3_10/v3_3_0_5-1.0_00.0_00.0_01.0_etHFp3_Corrected");
  TGraphErrors* gr_v4ep = fEP_v4->Get("-1.0_00.0_00.0_01.0_etHFp4_etHFm4_08/v4_4_0_5-1.0_00.0_00.0_01.0_etHFp4_Corrected");
  TGraphErrors* gr_v5ep = fEP_v5->Get("-1.0_00.0_00.0_01.0_etHFp5_etHFm5_08/v5_5_0_5-1.0_00.0_00.0_01.0_etHFp5_Corrected");
  TGraphErrors* gr_v6ep = fEP_v6->Get("-1.0_00.0_00.0_01.0_etHFp6_etHFm6_08/v6_6_0_5-1.0_00.0_00.0_01.0_etHFp6_Corrected");

  gr_v2ep->SetMarkerStyle(25);
  gr_v3ep->SetMarkerStyle(25);
  gr_v4ep->SetMarkerStyle(25);
  gr_v5ep->SetMarkerStyle(25);
  gr_v6ep->SetMarkerStyle(25);

  TH2D* htmp1 = new TH2D("htmp1",";p_{T} (GeV/c);v_{n}{2part, |#Delta#eta| > 2}",100,0.1,7.9,100,-0.005,0.09);
  htmp1->GetYaxis()->SetTitleOffset(htmp1->GetYaxis()->GetTitleOffset()*0.65);
  htmp1->GetYaxis()->SetTitleSize(htmp1->GetYaxis()->GetTitleSize()*2.4);
  htmp1->GetYaxis()->SetLabelOffset(htmp1->GetYaxis()->GetLabelOffset()*1.0);
  htmp1->GetYaxis()->SetLabelSize(htmp1->GetYaxis()->GetLabelSize()*1.7);
  htmp1->GetXaxis()->SetTitleOffset(htmp1->GetXaxis()->GetTitleOffset()*0.7);
  htmp1->GetXaxis()->SetTitleSize(htmp1->GetXaxis()->GetTitleSize()*2.0);
  htmp1->GetXaxis()->SetLabelOffset(htmp1->GetXaxis()->GetLabelOffset()*1.0);
  htmp1->GetXaxis()->SetLabelSize(htmp1->GetXaxis()->GetLabelSize()*1.5);
  htmp1->GetXaxis()->CenterTitle();
  htmp1->GetYaxis()->CenterTitle();
  TH2D* htmp2 = (TH2D*)htmp1->Clone("htmp2");
  TH2D* htmp3 = (TH2D*)htmp1->Clone("htmp3");
  TH2D* htmp4 = (TH2D*)htmp1->Clone("htmp4");
  htmp4->GetYaxis()->SetLabelSize(htmp4->GetYaxis()->GetLabelSize()*0.84);
  htmp4->GetYaxis()->SetTitleOffset(htmp4->GetYaxis()->GetTitleOffset()*1.2);
  htmp4->GetYaxis()->SetTitleSize(htmp4->GetYaxis()->GetTitleSize()*0.83);
  TH2D* htmp5 = (TH2D*)htmp1->Clone("htmp5");
  htmp5->GetXaxis()->SetTitleOffset(htmp5->GetXaxis()->GetTitleOffset()*0.96);
  htmp5->GetXaxis()->SetTitleSize(htmp5->GetXaxis()->GetTitleSize()*1.07);
  htmp5->GetXaxis()->SetLabelSize(htmp5->GetXaxis()->GetLabelSize()*1.04);

  TLine* line1 = new TLine(0.0,0.0,7.9,0.0);
  line1->SetLineStyle(9);

  TCanvas* c = new TCanvas("c","c",950,600);
  makeMultiPanelCanvas(c,3,2,0.01,0.0,0.18,0.2,0.04);
  c->cd(1);
  htmp1->Draw();
  gr_v2->Draw("pesame");
//  gr1_v2->Draw("pesame");
  gr2_v2->Draw("pesame");
//  gr3_v2->Draw("pesame");
//  gr_v2ep->SetMarkerColor(kRed);
//  gr_v2ep->Draw("pesame");
  line1->Draw("lsame");
  TLatex* latex1 = new TLatex();
  latex1->SetTextSize(1.8*latex1->GetTextSize());
  latex1->SetNDC();
  latex1->DrawLatex(0.24,0.8,"n = 2");
  c->cd(2);
  htmp2->Draw();
  gr_v3->Draw("pesame");
//  gr1_v3->Draw("pesame");
  gr2_v3->Draw("pesame");
//  gr3_v3->Draw("pesame");
//  gr_v3ep->SetMarkerColor(kRed);
//  gr_v3ep->Draw("pesame");
  line1->Draw("lsame");
  TLatex* latex2 = new TLatex();
  latex2->SetTextSize(1.8*latex2->GetTextSize());
  latex2->SetNDC();
  latex2->DrawLatex(0.07,0.8,"n = 3");
  c->cd(3);
  htmp3->Draw();
  gr_v4->Draw("pesame");
//  gr1_v4->Draw("pesame");
  gr2_v4->Draw("pesame");
//  gr3_v4->Draw("pesame");
//  gr_v4ep->SetMarkerColor(kRed);
//  gr_v4ep->Draw("pesame");
  line1->Draw("lsame");
  TLatex* latex3 = new TLatex();
  latex3->SetTextSize(1.8*latex3->GetTextSize());
  latex3->SetNDC();
  latex3->DrawLatex(0.07,0.8,"n = 4");
  c->cd(4);
  htmp4->Draw();
  gr_v5->Draw("pesame");
//  gr1_v5->Draw("pesame");
  gr2_v5->Draw("pesame");
//  gr3_v5->Draw("pesame");
//  gr_v5ep->SetMarkerColor(kRed);
//  gr_v5ep->Draw("pesame");
  line1->Draw("lsame");
  TLatex* latex4 = new TLatex();
  latex4->SetTextSize(1.6*latex4->GetTextSize());
  latex4->SetNDC();
  latex4->DrawLatex(0.24,0.85,"n = 5");
  c->cd(5);
  htmp5->Draw();
  gr_v6->Draw("pesame");
//  gr1_v6->Draw("pesame");
  gr2_v6->Draw("pesame");
//  gr3_v6->Draw("pesame");
//  gr_v6ep->SetMarkerColor(kRed);
//  gr_v6ep->Draw("pesame");
  line1->Draw("lsame");
  TLatex* latex5 = new TLatex();
  latex5->SetTextSize(1.8*latex5->GetTextSize());
  latex5->SetNDC();
  latex5->DrawLatex(0.07,0.85,"n = 6");

  TLegend* legend = new TLegend(0.03,0.23,0.76,0.43);
  legend->SetTextFont(42);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.07);
  legend->AddEntry(gr_v2,"1 < p_{T}^{ref} < 3 GeV/c","P");
  legend->AddEntry(gr2_v2,"0.5 < p_{T}^{ref} < 1.0 GeV/c","P");
//  legend->AddEntry(gr_v2,"Correlation method","P");
//  legend->AddEntry(gr_v2ep,"EP method","P");
//  legend->AddEntry(gr_v2,"z_{vtx} bin 1cm","P");
//  legend->AddEntry(gr2_v2,"z_{vtx} bin 0.2cm","P");
//  legend->AddEntry(gr_v2,"Default","P");
//  legend->AddEntry(gr2_v2,"Tighter ZDC cut","P");
  c->cd(6);
  legend->Draw("same");
  TLatex* latex11 = new TLatex();
  latex11->SetNDC(1);
  latex11->SetTextSize(1.3*latex11->GetTextSize());
  latex11->DrawLatex(0.1,0.78,"CMS PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  latex11->DrawLatex(0.5,0.7,"L_{int} = 120 #mub^{-1}");
  latex11->DrawLatex(0.36,0.62,"0-0.2% centrality");

  c->cd(1);  
//  latex1->DrawLatex(0.24,0.64,"CMS Preliminary");

  SaveCanvas(c,"HI/UCC","compare_vnpt_lowptass");

  double vn_ep[5] = {0.0185,0.0190,0.00949,0.00356,0.00278};
  double n_ep[5] = {2,3,4,5,6};

  TH2D* htmp20 = new TH2D("htmp20",";n;v_{n}{2part,|#Delta#eta|>2}",100,1.5,7.79,100,-0.005,0.03);
  htmp20->GetYaxis()->SetLabelSize(htmp20->GetYaxis()->GetLabelSize()*0.8);
  htmp20->GetXaxis()->SetLabelSize(htmp20->GetXaxis()->GetLabelSize()*0.8);
  htmp20->GetXaxis()->CenterTitle();
  htmp20->GetYaxis()->CenterTitle();
  TLine* line2 = new TLine(1.5,0.0,7.79,0.0);
  line2->SetLineStyle(9);
  line2->Draw("lsame");

  TCanvas* c1 = new TCanvas("c1","c1",580,500);
  c1->SetLeftMargin(0.18);
  htmp20->Draw("");
  gr_vnn->SetMarkerStyle(20);
  gr_vnn->Draw("PESAME");
//  gr1_vnn->Draw("PESAME");
  gr2_vnn->Draw("PESAME");
//  gr3_vnn->Draw("PESAME");

  TGraph* gr_vnn_ep = new TGraph(5,n_ep,vn_ep);
  gr_vnn_ep->SetMarkerStyle(25);
//  gr_vnn_ep->Draw("PESAME");

  TLegend* legend1 = new TLegend(0.2,0.2,0.78,0.38);
  legend1->SetTextFont(42);
  legend1->SetFillStyle(0);
//  legend1->AddEntry(gr_vnn,"Correlation method","P");
//  legend1->AddEntry(gr2_vnn,"EP method","P");
  legend1->AddEntry(gr_vnn,"1<p_{T}^{assoc}<3 GeV/c","P");
  legend1->AddEntry(gr2_vnn,"0.5<p_{T}^{assoc}<1 GeV/c","P");
  legend1->Draw("same");
  TLatex* latex2 = new TLatex();
  latex2->SetNDC(1);
  latex2->SetTextSize(latex2->GetTextSize()*1.0);
//  latex2->DrawLatex(0.6,0.87,"CMS Preliminary");
  latex2->DrawLatex(0.6,0.80,"PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  latex2->DrawLatex(0.6,0.75,"0-0.2% centrality");

  SaveCanvas(c1,"HI/UCC","compare_vnn_lowptass");
}

void compare_vn1()
{
  TFile* f = new TFile("gr_UCC_centmin110_centmax1000.root");
  TFile* f1 = new TFile("gr_UCC_centmin210_centmax1000.root");
  TFile* f2 = new TFile("gr_MB_centmin50_centmax1000.root");
  TFile* f3 = new TFile("gr_MB_centmin51_centmax1000.root");
  TFile* f4 = new TFile("gr_MB_centmin0_centmax1.root");
  TFile* f5 = new TFile("gr_MB_centmin1_centmax2.root");

  TGraphErrors* gr = (TGraphErrors*)f->Get("vnn_corr");
  TGraphErrors* gr1 = (TGraphErrors*)f1->Get("vnn_corr");
  TGraphErrors* gr2 = (TGraphErrors*)f2->Get("vnn_corr");
  TGraphErrors* gr3 = (TGraphErrors*)f3->Get("vnn_corr");
  TGraphErrors* gr4 = (TGraphErrors*)f4->Get("vnn_corr");
  TGraphErrors* gr5 = (TGraphErrors*)f5->Get("vnn_corr");

  TGraph* gr_sys = (TGraph*)f->Get("vnn_corr_sys");
  TGraph* gr1_sys = (TGraph*)f1->Get("vnn_corr_sys");
  TGraph* gr2_sys = (TGraph*)f2->Get("vnn_corr_sys");
  TGraph* gr3_sys = (TGraph*)f3->Get("vnn_corr_sys");
  TGraph* gr4_sys = (TGraph*)f4->Get("vnn_corr_sys");
  TGraph* gr5_sys = (TGraph*)f5->Get("vnn_corr_sys");

  cout<<"2.5-5% centrality:"<<endl;
  cout<<"n    v_n    stat. err.    syst. err."<<endl;
  for(int i=0;i<gr5->GetN();i++)
  {
    double x,y,yerr;
    gr5->GetPoint(i+2,x,y);
    yerr = gr5->GetErrorY(i+2);
    double xsyst,ysyst;
    gr5_sys->GetPoint(i,xsyst,ysyst);
    cout<<Form("%.0f  %.4f  %.4f  %.4f",x,y,yerr,ysyst-y)<<endl;
    if(x>=7) break;
  }

  cout<<"0-2.5% centrality:"<<endl;
  cout<<"n    v_n    stat. err.    syst. err."<<endl;
  for(int i=0;i<gr4->GetN();i++)
  {
    double x,y,yerr;
    gr4->GetPoint(i+2,x,y);
    yerr = gr4->GetErrorY(i+2);
    double xsyst,ysyst;
    gr4_sys->GetPoint(i,xsyst,ysyst);
    cout<<Form("%.0f  %.4f  %.4f  %.4f",x,y,yerr,ysyst-y)<<endl;
    if(x>=7) break;
  }

  cout<<"0-1% centrality:"<<endl;
  cout<<"n    v_n    stat. err.    syst. err."<<endl;
  for(int i=0;i<gr3->GetN();i++)
  {
    double x,y,yerr;
    gr3->GetPoint(i+2,x,y);
    yerr = gr3->GetErrorY(i+2);
    double xsyst,ysyst;
    gr3_sys->GetPoint(i,xsyst,ysyst);
    cout<<Form("%.0f  %.4f  %.4f  %.4f",x,y,yerr,ysyst-y)<<endl;
    if(x>=7) break;
  }

  cout<<"0-0.2% centrality:"<<endl;
  cout<<"n    v_n    stat. err.    syst. err."<<endl;
  for(int i=0;i<gr->GetN();i++)
  {
    double x,y,yerr;
    gr->GetPoint(i+2,x,y);
    yerr = gr->GetErrorY(i+2);
    double xsyst,ysyst;
    gr_sys->GetPoint(i,xsyst,ysyst);
    cout<<Form("%.0f  %.4f  %.4f  %.4f",x,y,yerr,ysyst-y)<<endl;
    if(x>=7) break;
  }

  cout<<"0-0.02% centrality:"<<endl;
  cout<<"n    v_n    stat. err.    syst. err."<<endl;
  for(int i=0;i<gr1->GetN();i++)
  {
    double x,y,yerr;
    gr1->GetPoint(i+2,x,y);
    yerr = gr1->GetErrorY(i+2);
    double xsyst,ysyst;
    gr1_sys->GetPoint(i,xsyst,ysyst);
    cout<<Form("%.0f  %.4f  %.4f  %.4f",x,y,yerr,ysyst-y)<<endl;
    if(x>=7) break;
  }

  gr_sys->SetFillColor(TColor::GetColor("#ffff00"));
  gr1_sys->SetFillColor(TColor::GetColor("#ffff00"));
  gr2_sys->SetFillColor(TColor::GetColor("#ffff00"));
  gr3_sys->SetFillColor(TColor::GetColor("#ffff00"));
  gr4_sys->SetFillColor(TColor::GetColor("#ffff00"));
  gr5_sys->SetFillColor(TColor::GetColor("#ffff00"));

/*
  TGraph* gr = (TGraph*)f->Get("vnn");
  TGraph* gr1 = (TGraph*)f1->Get("vnn");
  TGraph* gr2 = (TGraph*)f2->Get("vnn");
  TGraph* gr3 = (TGraph*)f3->Get("vnn");
  TGraph* gr4 = (TGraph*)f4->Get("vnn");
  TGraph* gr5 = (TGraph*)f5->Get("vnn");
*/

  gr1->SetMarkerColor(kRed);
  gr2->SetMarkerColor(kBlue);
  gr3->SetMarkerColor(kGreen+2);
  gr4->SetMarkerColor(9);
  gr5->SetMarkerColor(6);

  gr->SetMarkerStyle(20);
  gr1->SetMarkerStyle(21);
  gr2->SetMarkerStyle(33);
  gr3->SetMarkerStyle(34);
  gr4->SetMarkerStyle(29);
  gr5->SetMarkerStyle(31);

  gr->SetMarkerSize(gr->GetMarkerSize()*1.5);
  gr1->SetMarkerSize(gr1->GetMarkerSize()*1.5);
  gr2->SetMarkerSize(gr2->GetMarkerSize()*1.5);
  gr3->SetMarkerSize(gr3->GetMarkerSize()*1.5);
  gr4->SetMarkerSize(gr4->GetMarkerSize()*1.5);
  gr5->SetMarkerSize(gr5->GetMarkerSize()*1.5);

  TH2D* htmp1 = new TH2D("htmp1",";n;v_{n}{2part, |#Delta#eta| > 2}",100,1.49,7.52,100,-0.005,0.04);
  htmp1->SetTickLength(0);
  htmp1->SetNdivisions(510);
  htmp1->GetXaxis()->CenterTitle();
  htmp1->GetYaxis()->CenterTitle();
  htmp1->GetXaxis()->SetLabelSize(htmp1->GetXaxis()->GetLabelSize());
  htmp1->GetYaxis()->SetLabelSize(htmp1->GetYaxis()->GetLabelSize());
  htmp1->GetYaxis()->SetTitleOffset(0.5*htmp1->GetYaxis()->GetTitleOffset());
  htmp1->GetXaxis()->SetTitleOffset(0.5*htmp1->GetXaxis()->GetTitleOffset());
  htmp1->GetYaxis()->SetTitleSize(1.5*htmp1->GetYaxis()->GetTitleSize());
  htmp1->GetXaxis()->SetTitleSize(1.8*htmp1->GetXaxis()->GetTitleSize());

  TCanvas* c = new TCanvas("c","c",1000,500);
  c->SetLeftMargin(0.1);
  c->SetBottomMargin(0.12);
//  c->SetLogy();
  
  htmp1->Draw();

/*
  gr_sys->Draw("Fsame");
  gr1_sys->Draw("Fsame");  
  gr2_sys->Draw("Fsame");
  gr3_sys->Draw("Fsame");
  gr4_sys->Draw("Fsame");
  gr5_sys->Draw("Fsame");
*/
  drawSystBox(gr,gr_sys,TColor::GetColor("#ffff00"),0.08,-0.21);
  drawSystBox(gr1,gr1_sys,TColor::GetColor("#ffff00"),0.08,-0.42);
//  drawSystBox(gr2,gr2_sys,TColor::GetColor("#ffff00"),0.1,-0.04);
  drawSystBox(gr3,gr3_sys,TColor::GetColor("#ffff00"),0.08,+0.0);
  drawSystBox(gr4,gr4_sys,TColor::GetColor("#ffff00"),0.08,+0.21);
  drawSystBox(gr5,gr5_sys,TColor::GetColor("#ffff00"),0.08,+0.42);

  shiftTGraph(gr,-0.21);
  shiftTGraph(gr1,-0.42);
//  shiftTGraph(gr2,-0.04);
  shiftTGraph(gr3,0.0);
  shiftTGraph(gr4,0.21);
  shiftTGraph(gr5,0.42);

  gr3->Draw("pesame");
//  gr2->Draw("pesame");
  gr1->Draw("pesame");
  gr4->Draw("pesame");
  gr5->Draw("pesame");
  gr->Draw("pesame");

  TLine* lline = new TLine(1.5,0.0,7.52,0.0);
  lline->SetLineStyle(9);
  lline->Draw("Lsame");

  TLine* vline1 = new TLine(1.5,-0.005,1.5,0.04);
  TLine* vline2 = new TLine(2.5,-0.005,2.5,0.04);
  TLine* vline3 = new TLine(3.5,-0.005,3.5,0.04);
  TLine* vline4 = new TLine(4.5,-0.005,4.5,0.04);
  TLine* vline5 = new TLine(5.5,-0.005,5.5,0.008);
  TLine* vline6 = new TLine(6.5,-0.005,6.5,0.008);
  TLine* vline7 = new TLine(7.5,-0.005,7.5,0.008);
  vline1->SetLineStyle(3);
  vline2->SetLineStyle(3);
  vline3->SetLineStyle(3);
  vline4->SetLineStyle(3);
  vline5->SetLineStyle(3);
  vline6->SetLineStyle(3);
  vline7->SetLineStyle(3);
//  vline1->Draw("Lsame");
  vline2->Draw("Lsame");
  vline3->Draw("Lsame");
  vline4->Draw("Lsame");
  vline5->Draw("Lsame");
  vline6->Draw("Lsame");
//  vline7->Draw("Lsame");

  TLine* tline2 = new TLine(2.,0.04,2.,0.04-0.001);
  TLine* tline3 = new TLine(3.,0.04,3.,0.04-0.001);
  TLine* tline4 = new TLine(4.,0.04,4.,0.04-0.001);
 TLine* tline5 = new TLine(5.,0.04,5.,0.04-0.001);
  TLine* tline6 = new TLine(6.,0.04,6.,0.04-0.001);
  TLine* tline7 = new TLine(7.,0.04,7.,0.04-0.001);
  tline2->Draw("Lsame");
  tline3->Draw("Lsame");
  tline4->Draw("Lsame");
  tline5->Draw("Lsame");
  tline6->Draw("Lsame");
  tline7->Draw("Lsame");

  TLine* ttline2 = new TLine(2.,-0.005,2.,-0.004);
  TLine* ttline3 = new TLine(3.,-0.005,3.,-0.004);
  TLine* ttline4 = new TLine(4.,-0.005,4.,-0.004);
  TLine* ttline5 = new TLine(5.,-0.005,5.,-0.004);
  TLine* ttline6 = new TLine(6.,-0.005,6.,-0.004);
  TLine* ttline7 = new TLine(7.,-0.005,7.,-0.004);
  ttline2->Draw("Lsame");
  ttline3->Draw("Lsame");
  ttline4->Draw("Lsame");
  ttline5->Draw("Lsame");
  ttline6->Draw("Lsame");
  ttline7->Draw("Lsame");

//  TArrow* arrow = new TArrow(2.35,0.005,1.65,0.005,0.02,"|>");
//  arrow->Draw("");
//  TLatex* llatex = new TLatex();
//  llatex->DrawLatex(1.75,0.0065,"central");

/*
  vline_left[2]->Draw("Lsame");
  vline_right[2]->Draw("Lsame");
  vline_left[3]->Draw("Lsame");
  vline_right[3]->Draw("Lsame");
  vline_left[4]->Draw("Lsame");
  vline_right[4]->Draw("Lsame");
  vline_left[5]->Draw("Lsame");
  vline_right[5]->Draw("Lsame");
  vline_left[6]->Draw("Lsame");
  vline_right[6]->Draw("Lsame");
  vline_left[7]->Draw("Lsame");
  vline_right[7]->Draw("Lsame");
*/

  TLatex* latex1 = new TLatex();
  latex1->SetNDC(1);
  latex1->SetTextSize(latex1->GetTextSize()*1.0);
  latex1->DrawLatex(0.63,0.88,"CMS PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  latex1->DrawLatex(0.77,0.81,"L_{int} = 120 #mub^{-1}");
  latex1->DrawLatex(0.71,0.74,"0.3 < p_{T} < 3.0 GeV/c");

//  latex1->DrawLatex(0.13,0.24,"CMS Preliminary");

  TLegend* legend = new TLegend(0.565,0.37,0.88,0.7);
  legend->SetFillStyle(0);
  legend->SetTextFont(42);
  legend->AddEntry(gr5,"2.5-5.0%, HF","P");
  legend->AddEntry(gr4,"0-2.5%, HF","P");
//  legend->AddEntry(gr2,"0-1%, HF","P");
  legend->AddEntry(gr3,"0-1%, HF+NPixel","P");
  legend->AddEntry(gr,"0-0.2%, HF+NPixel","P");
  legend->AddEntry(gr1,"0-0.02%, HF+NPixel","P");
  legend->Draw("same");

  SaveCanvas(c,"HI/UCC","compare_vnn_centrality");
/*
  double npart[4] = {381.3,395.8,404.0,406.2};
  double nparterr[4] = {0};
  double v2[4],v3[4],v4[4],v5[4];
  double v2err[4],v3err[4],v4err[4],v5err[4];

  for(int i=0;i<4;i++)
  {
    double v2,v2err;
    f3->GetPoint() 
  }
*/
}

void drawSystBox(TGraph* gr, TGraph* gr_syst, int fillcolor=TColor::GetColor("#ffff00"), double xwidth=0.2, double xshift=0)
{
  TBox* box;
  for(int n=0;n<6;n++)
  {
    double x,y;
    gr->GetPoint(n+2,x,y);
    double xerr,yerr;
    gr_syst->GetPoint(n,xerr,yerr);

cout<<y<<" "<<yerr<<endl;
cout<<x<<" "<<xerr<<endl;

    box = new TBox(x+xshift-xwidth,y-fabs(y-yerr),x+xshift+xwidth,y+fabs(y-yerr));
    box->SetFillColor(fillcolor);
    box->SetLineWidth(0);
    box->Draw("Fsame");
  }
}

void drawLineTheory(TGraph* gr, int linecolor=1, double xwidth=0.2, double xshift=0)
{
  TLine* line;
  for(int n=0;n<gr->GetN();n++)
  {
    double x,y;
    gr->GetPoint(n,x,y);

    line = new TLine(x+xshift-xwidth,y,x+xshift+xwidth,y);
    line->SetLineWidth(3);
    line->SetLineColor(linecolor);
    line->Draw("Lsame");
  }
}

void drawSystBoxTheory(TGraphAsymmErrors* gr, int fillcolor=TColor::GetColor("#ffff00"), int linecolor=1, double xwidth=0.2, double xshift=0)
{
  TBox* box;
  TLine* line;
  for(int n=0;n<gr->GetN();n++)
  {
    double x,y;
    gr->GetPoint(n,x,y);
cout<<x<<" "<<y<<endl;
    double yerrhigh,yerrlow;
    yerrhigh = gr->GetErrorYhigh(n);
    yerrlow = gr->GetErrorYlow(n);

    box = new TBox(x+xshift-xwidth,y-yerrlow,x+xshift+xwidth,y+yerrhigh);
    box->SetFillColor(fillcolor);
    box->SetLineWidth(0);
    box->Draw("Fsame");

    line = new TLine(x+xshift-xwidth,y,x+xshift+xwidth,y);
    line->SetLineWidth(3);
    line->SetLineColor(linecolor);
    line->Draw("Lsame");
  }
}

void shiftTGraph(TGraph* gr, double xshift=0)
{
  for(int n=0;n<gr->GetN();n++)
  {
    double x,y;
    gr->GetPoint(n,x,y);
    gr->SetPoint(n,x+xshift,y);
  }
}
