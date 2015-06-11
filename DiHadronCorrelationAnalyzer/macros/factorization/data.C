void data()
{
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_pixeltracks_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin500_centmax1000.root");
  TFile* f1 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_UCC2011_pixeltracks_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
  TNtuple* nt = (TNtuple*)f->Get("higeninfontuple");
  TNtuple* nt1 = (TNtuple*)f1->Get("higeninfontuple");

  TH2D* hNPixelVsHF = new TH2D("hNPixelVsHF",";Pixel Cluster Multiplicity;HF E_{T} Sum (GeV)",3000,0,120000,3000,0,7000);
  TH2D* hNPixelVsHF1 = new TH2D("hNPixelVsHF1",";Pixel Cluster Multiplicity;HF E_{T} Sum (GeV)",3000,0,120000,3000,0,7000);
  TH2D* hNPixelVsHF_nopurej = new TH2D("hNPixelVsHF_nopurej",";Pixel Cluster Multiplicity;HF E_{T} Sum (GeV)",3000,0,120000,3000,0,7000);
  TH2D* hNPixelVsHF1_nopurej = new TH2D("hNPixelVsHF1_nopurej",";Pixe Cluster Multiplicity;HF E_{T} Sum (GeV)",3000,0,120000,3000,0,7000);
  TH1D* hHF_nopurej = new TH1D("hHF_nopurej",";HF E_{T} Sum (GeV);Counts",350,0,7000);
  TH1D* hHF1_nopurej = new TH1D("hHF1_nopurej",";HF E_{T} Sum (GeV);Counts",350,0,7000);
  TH1D* hHF_zoomin = new TH1D("hHF_zoomin",";HF E_{T} Sum (GeV);Counts",500,3000,4000);
  TH1D* hHF = new TH1D("hHF",";HF E_{T} Sum (GeV);Counts",350,0,7000);
  TH1D* hHF1 = new TH1D("hHF1",";HF E_{T} Sum (GeV);Counts",350,0,7000);
  TH1D* hHF025 = new TH1D("hHF025",";HF E_{T} Sum (GeV);Counts",3500,0,7000);
  TH1D* hHF001 = new TH1D("hHF001",";HF E_{T} Sum (GeV);Counts",3500,0,7000);
  TH1D* hHF0001 = new TH1D("hHF0001",";HF E_{T} Sum (GeV);Counts",3500,0,7000);
  TH1D* hNPixel_nopurej = new TH1D("hNPixel_nopurej",";Pixel Cluster Multiplicity;Counts",6000,0,120000);
  TH1D* hNPixel1_nopurej = new TH1D("hNPixel1_nopurej",";Pixel Cluster Multiplicity;Counts",6000,0,120000);
  TH1D* hNPixel = new TH1D("hNPixel",";Pixel Cluster Multiplicity;Counts",6000,0,120000);
  TH1D* hNPixel1 = new TH1D("hNPixel1",";Pixel Cluster Multiplicity;Counts",6000,0,120000);
  TH1D* hNPixel025 = new TH1D("hNPixel025",";Pixel Cluster Multiplicity;Counts",6000,0,120000);
  TH1D* hNPixel001 = new TH1D("hNPixel001",";Pixel Cluster Multiplicity;Counts",6000,0,120000);
  TH1D* hNPixel0001 = new TH1D("hNPixel0001",";Pixel Cluster Multiplicity;Counts",6000,0,120000);
  TH1D* hmult_nopurej = new TH1D("hmult_nopurej",";Track Multiplicity",500,0,5000);
  TH1D* hmult1_nopurej = new TH1D("hmult1_nopurej",";Track Multiplicity",500,0,5000);
  TH1D* hmult = new TH1D("hmult",";Track Multiplicity",500,0,5000);
  TH1D* hmult1 = new TH1D("hmult1",";Track Multiplicity",500,0,5000);

  nt->Draw("hft:npixel>>hNPixelVsHF","(7.0*hft+zdc)<36000 && zdc>0","GOFF");
  nt1->Draw("hft:npixel>>hNPixelVsHF1","(7.0*hft+zdc)<36000 && zdc>0","GOFF");
  nt->Draw("hft:npixel>>hNPixelVsHF_nopurej","","GOFF");
  nt1->Draw("hft:npixel>>hNPixelVsHF1_nopurej","","GOFF");
  nt->Draw("hft>>hHF","(7.0*hft+zdc)<36000 && zdc>0","GOFF");
  nt1->Draw("hft>>hHF1","(7.0*hft+zdc)<36000 && npixel>51400 && hft>3260 && zdc>0","GOFF");
  nt1->Draw("hft>>hHF_zoomin","(7.0*hft+zdc)<36000 && npixel>51400 && hft>3260 && zdc>0","GOFF");
  nt->Draw("hft>>hHF_nopurej","","GOFF");
  nt1->Draw("hft>>hHF1_nopurej","npixel>51400 && hft>3260","GOFF");
  nt->Draw("hft>>hHF025","bin==0","GOFF");
  nt->Draw("hft>>hHF001","(7.0*hft+zdc)<36000 && npixel>51400 && hft>3260 && zdc>0","GOFF");
  nt->Draw("hft>>hHF0001","(7.0*hft+zdc)<36000 && npixel>53450 && hft>3393 && zdc>0","GOFF");
  nt->Draw("npixel>>hNPixel","(7.0*hft+zdc)<36000 && zdc>0","GOFF");
  nt1->Draw("npixel>>hNPixel1","(7.0*hft+zdc)<36000 && npixel>51400 && hft>3260 && zdc>0","GOFF");
  nt->Draw("npixel>>hNPixel_nopurej","","GOFF");
  nt1->Draw("npixel>>hNPixel1_nopurej","npixel>51400 && hft>3260","GOFF");
  nt->Draw("npixel>>hNPixel025","bin==0","GOFF");
  nt->Draw("npixel>>hNPixel001","(7.0*hft+zdc)<36000 && npixel>51400 && hft>3260 && zdc>0","GOFF");
  nt->Draw("npixel>>hNPixel0001","(7.0*hft+zdc)<36000 && npixel>53450 && hft>3393 && zdc>0","GOFF");
  nt->Draw("nmult>>hmult_nopurej","","GOFF");
  nt1->Draw("nmult>>hmult1_nopurej","npixel>51400 && hft>3260","GOFF");
  nt->Draw("nmult>>hmult","(7.0*hft+zdc)<36000 && zdc>0","GOFF");
  nt1->Draw("nmult>>hmult1","(7.0*hft+zdc)<36000 && npixel>51400 && hft>3260 && zdc>0","GOFF");

cout<<hHF001->Integral()/hHF->Integral()<<endl;
cout<<hHF001->Integral()/hHF025->Integral()<<endl;
cout<<hHF0001->Integral()/hHF025->Integral()<<endl;
/*
  hHF025->Scale(1./hHF->Integral());
  hHF->Scale(1./hHF->Integral());
  hHF1->Scale(0.005/hHF1->Integral());
  hNPixel025->Scale(1./hNPixel->Integral());
  hNPixel->Scale(1./hNPixel->Integral());
  hNPixel1->Scale(1./hNPixel1->Integral());
*/
/*
  TCanvas* cb1 = new TCanvas("cb1","",550,500);
  cb1->SetLeftMargin(0.15);
  cb1->SetRightMargin(0.1);
  cb1->SetLogy();
  hHF1_nopurej->GetXaxis()->CenterTitle();
  hHF1_nopurej->GetYaxis()->CenterTitle();
  hHF1_nopurej->GetXaxis()->SetLabelSize(0.8*hHF1_nopurej->GetXaxis()->GetLabelSize());
  hHF1_nopurej->GetYaxis()->SetLabelSize(0.8*hHF1_nopurej->GetYaxis()->GetLabelSize());
  hHF1_nopurej->GetYaxis()->SetTitleOffset(1.1*hHF1_nopurej->GetYaxis()->GetTitleOffset());
  hHF1_nopurej->GetXaxis()->SetTitleOffset(1.02*hHF1_nopurej->GetXaxis()->GetTitleOffset());
  hHF1_nopurej->GetYaxis()->SetTitleSize(1.1*hHF1_nopurej->GetYaxis()->GetTitleSize());
  hHF1_nopurej->GetXaxis()->SetTitleSize(0.9*hHF1_nopurej->GetXaxis()->GetTitleSize());
  hHF1_nopurej->SetMarkerColor(kRed);
  hHF1_nopurej->Rebin(2);
  hHF1_nopurej->Rebin(2);
  hHF1_nopurej->Draw("PE");
  hHF_nopurej->Draw("PESAME");
  hHF1_nopurej->Draw("PESAME");
  TLegend* legend = new TLegend(0.18,0.3,0.5,0.45);
  legend->SetFillStyle(0);
  legend->SetTextFont(42);
  legend->AddEntry(hHF_nopurej,"MB","P");
  legend->AddEntry(hHF1_nopurej,"UCC","P");
  legend->Draw("same");
  SaveCanvas(cb1,"HI/UCC","HFdist_mbucccomp");
*/
  TCanvas* ctmp1 = new TCanvas("ctmp1","",550,500);
  ctmp1->SetLeftMargin(0.15);
  ctmp1->SetRightMargin(0.1);
//  ctmp1->SetLogy();
  hHF_zoomin->GetXaxis()->CenterTitle();
  hHF_zoomin->GetYaxis()->CenterTitle();
  hHF_zoomin->GetXaxis()->SetLabelSize(0.8*hHF_zoomin->GetXaxis()->GetLabelSize());
  hHF_zoomin->GetYaxis()->SetLabelSize(0.8*hHF_zoomin->GetYaxis()->GetLabelSize());
  hHF_zoomin->GetYaxis()->SetTitleOffset(1.1*hHF_zoomin->GetYaxis()->GetTitleOffset());
  hHF_zoomin->GetXaxis()->SetTitleOffset(1.02*hHF_zoomin->GetXaxis()->GetTitleOffset());
  hHF_zoomin->GetYaxis()->SetTitleSize(1.1*hHF_zoomin->GetYaxis()->GetTitleSize());
  hHF_zoomin->GetXaxis()->SetTitleSize(0.9*hHF_zoomin->GetXaxis()->GetTitleSize());
  hHF_zoomin->SetMarkerColor(kRed);
  hHF_zoomin->Rebin(1);
  hHF_zoomin->SetMaximum(hHF_zoomin->GetMaximum()*1.2);
  hHF_zoomin->Draw("PE");
  SaveCanvas(ctmp1,"HI/UCC","HFdist_zoomin");

  TCanvas* ca1 = new TCanvas("ca1","",550,500);
  ca1->SetLeftMargin(0.17);
  ca1->SetRightMargin(0.1);
  ca1->SetLogy();
  hHF1->GetXaxis()->CenterTitle();
  hHF1->GetYaxis()->CenterTitle();
  hHF1->GetXaxis()->SetLabelSize(0.8*hHF1->GetXaxis()->GetLabelSize());
  hHF1->GetYaxis()->SetLabelSize(0.8*hHF1->GetYaxis()->GetLabelSize());
  hHF1->GetYaxis()->SetTitleOffset(1.1*hHF1->GetYaxis()->GetTitleOffset());
  hHF1->GetXaxis()->SetTitleOffset(1.02*hHF1->GetXaxis()->GetTitleOffset());
  hHF1->GetYaxis()->SetTitleSize(1.1*hHF1->GetYaxis()->GetTitleSize());
  hHF1->GetXaxis()->SetTitleSize(0.9*hHF1->GetXaxis()->GetTitleSize());
  hHF1->SetMarkerColor(kRed);
  hHF1_nopurej->SetMarkerColor(1);
  hHF1->Rebin(2);
  hHF1_nopurej->Rebin(2);
  hHF1->SetMaximum(hHF1->GetMaximum()*3);
  hHF1->SetAxisRange(3000,7000,"X");
  hHF1->Draw("PE");
  hHF1_nopurej->Draw("PESAME");
  hHF1->Draw("PESAME");
  TLegend* legend1 = new TLegend(0.43,0.6,0.87,0.75);
  legend1->SetFillStyle(0);
  legend1->SetTextFont(42);
  legend1->AddEntry(hHF1_nopurej,"No pileup rejection","P");
  legend1->AddEntry(hHF1,"Pileup rejection","P");
  legend1->Draw("same");
  TLatex* latex = new TLatex();
  latex->SetNDC(1);
  latex->SetTextSize(latex->GetTextSize()*1.0);
  latex->DrawLatex(0.6,0.88,"CMS Preliminary");
  latex->DrawLatex(0.52,0.82,"PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  SaveCanvas(ca1,"HI/UCC","HFdist_ucc_purejcomp");

  TCanvas* ca2 = new TCanvas("ca2","",550,500);
  ca2->SetLeftMargin(0.17);
  ca2->SetRightMargin(0.1);
  ca2->SetLogy();
  hNPixel1->GetXaxis()->CenterTitle();
  hNPixel1->GetYaxis()->CenterTitle();
  hNPixel1->GetXaxis()->SetLabelSize(0.8*hNPixel1->GetXaxis()->GetLabelSize());
  hNPixel1->GetYaxis()->SetLabelSize(0.8*hNPixel1->GetYaxis()->GetLabelSize());
  hNPixel1->GetYaxis()->SetTitleOffset(1.1*hNPixel1->GetYaxis()->GetTitleOffset());
  hNPixel1->GetXaxis()->SetTitleOffset(1.02*hNPixel1->GetXaxis()->GetTitleOffset());
  hNPixel1->GetYaxis()->SetTitleSize(1.1*hNPixel1->GetYaxis()->GetTitleSize());
  hNPixel1->GetXaxis()->SetTitleSize(0.9*hNPixel1->GetXaxis()->GetTitleSize());
  hNPixel1->SetMarkerColor(kRed);
  hNPixel1->Rebin(10);
  hNPixel1_nopurej->Rebin(10);
  hNPixel1->SetAxisRange(45000,110000,"X");
  hNPixel1->Draw("PE");
  hNPixel1_nopurej->Draw("PESAME");
  hNPixel1->Draw("PESAME");
  TLegend* legend2 = new TLegend(0.43,0.6,0.87,0.75);
  legend2->SetFillStyle(0);
  legend2->SetTextFont(42);
  legend2->AddEntry(hNPixel1_nopurej,"No pileup rejection","P");
  legend2->AddEntry(hNPixel1,"Pileup rejection","P");
  legend2->Draw("same");
  TLatex* latex2 = new TLatex();
  latex2->SetNDC(1);
  latex2->SetTextSize(latex2->GetTextSize()*1.0);
  latex2->DrawLatex(0.6,0.88,"CMS Preliminary");
  latex2->DrawLatex(0.52,0.82,"PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  SaveCanvas(ca2,"HI/UCC","NPixeldist_ucc_purejcomp");

/*
  TCanvas* ca3 = new TCanvas("ca3","",550,500);
  ca3->SetLeftMargin(0.15);
  ca3->SetRightMargin(0.1);
  ca3->SetLogy();
  hmult1->GetXaxis()->CenterTitle();
  hmult1->GetYaxis()->CenterTitle();
  hmult1->GetXaxis()->SetLabelSize(0.8*hmult1->GetXaxis()->GetLabelSize());
  hmult1->GetYaxis()->SetLabelSize(0.8*hmult1->GetYaxis()->GetLabelSize());
  hmult1->GetYaxis()->SetTitleOffset(1.1*hmult1->GetYaxis()->GetTitleOffset());
  hmult1->GetXaxis()->SetTitleOffset(1.02*hmult1->GetXaxis()->GetTitleOffset());
  hmult1->GetYaxis()->SetTitleSize(1.1*hmult1->GetYaxis()->GetTitleSize());
  hmult1->GetXaxis()->SetTitleSize(0.9*hmult1->GetXaxis()->GetTitleSize());
  hmult1->SetMarkerColor(kRed);
//  hmult1->Rebin(3);
//  hmult1_nopurej->Rebin(3);
  hmult1->Draw("PE");
  hmult1_nopurej->Draw("PESAME");
  hmult1->Draw("PESAME");
  TLegend* legend3 = new TLegend(0.18,0.3,0.5,0.45);
  legend3->SetFillStyle(0);
  legend3->SetTextFont(42);
  legend3->AddEntry(hmult1_nopurej,"No PU rejection","P");
  legend3->AddEntry(hmult1,"PU rejection","P");
  legend3->Draw("same");
  SaveCanvas(ca3,"HI/UCC","Multdist_ucc_purejcomp");
*/
/*
  TCanvas* cca1 = new TCanvas("cca1","",450,400);
  cca1->SetLogy();
  hNPixel1->SetMarkerColor(kRed);
  hNPixel1_nopurej->Draw("PE");
  hNPixel1->Draw("PESAME");
*/
/*
  ca1->Print("pics/HFdist_purejcomp.gif");
  ca1->Print("pics/HFdist_purejcomp.pdf");
  ca1->Print("pics/HFdist_purejcomp.eps");
  ca1->Print("pics/HFdist_purejcomp.C");
  cca1->Print("pics/NPixeldist_purejcomp.gif");
  cca1->Print("pics/NPixeldist_purejcomp.pdf");
  cca1->Print("pics/NPixeldist_purejcomp.eps");
  cca1->Print("pics/NPixeldist_purejcomp.C");
*/
/*
  TCanvas* cb1 = new TCanvas("cb1","",450,400);
  cb1->SetLogy();
  hHF1_nopurej->SetMarkerColor(kRed);
  hHF_nopurej->Draw("PE");
  hHF1_nopurej->Draw("PESAME");

  TCanvas* ccb1 = new TCanvas("ccb1","",450,400);
  ccb1->SetLogy();
  hNPixel1_nopurej->SetMarkerColor(kRed);
  hNPixel_nopurej->Draw("PE");
  hNPixel1_nopurej->Draw("PESAME");
*/
/*
  cb1->Print("pics/HFdist_nopurej.gif");
  cb1->Print("pics/HFdist_nopurej.pdf");
  cb1->Print("pics/HFdist_nopurej.eps");
  cb1->Print("pics/HFdist_nopurej.C");
  ccb1->Print("pics/NPixeldist_nopurej.gif");
  ccb1->Print("pics/NPixeldist_nopurej.pdf");
  ccb1->Print("pics/NPixeldist_nopurej.eps");
  ccb1->Print("pics/NPixeldist_nopurej.C");
*/
/*
  TCanvas* c1 = new TCanvas("c1","",450,400);
  c1->SetLogy();
  hHF1->SetMarkerColor(kRed);
  hHF025->SetMarkerColor(kBlue);
  hHF->Draw("PE");
//  hHF025->Draw("PESAME");
  hHF1->Draw("PESAME");

  TCanvas* cc1 = new TCanvas("cc1","",450,400);
  cc1->SetLogy();
  hNPixel1->SetMarkerColor(kRed);
//  hNPixel025->SetMarkerColor(kBlue);
  hNPixel->Draw("PE");
//  hNPixel025->Draw("PESAME");
  hNPixel1->Draw("PESAME");
*/
/*
  c1->Print("pics/HFdist_purej.gif");
  c1->Print("pics/HFdist_purej.pdf");
  c1->Print("pics/HFdist_purej.eps");
  c1->Print("pics/HFdist_purej.C");
  cc1->Print("pics/NPixeldist_purej.gif");
  cc1->Print("pics/NPixeldist_purej.pdf");
  cc1->Print("pics/NPixeldist_purej.eps");
  cc1->Print("pics/NPixeldist_purej.C");
*/
/*
  TCanvas* c = new TCanvas("c","",850,400);
  c->Divide(2,1);
  c->cd(1);
  c->GetPad(1)->SetLogz();
  hNPixelVsHF->Draw("colz");
  TProfile* hNPixelVsHF_prof = (TProfile*)hNPixelVsHF->ProfileX("hNPixelVsHF_prof",-1,-1,"e");
//  hNPixelVsHF_prof->Draw("lesame");
  TF1* fit = new TF1("fit","[0]*x",0,120000);
  fit->SetParameter(0,0.07);
  hNPixelVsHF_prof->Fit("fit","RNO");
  fit->SetLineColor(kRed);
  fit->Draw("lsame");
  c->cd(2);
  c->GetPad(2)->SetLogz();
  hNPixelVsHF1->Draw("colz");
  fit->Draw("lsame");
*/
/*
  c->Print("pics/HFVsPixel_purej.gif");
  c->Print("pics/HFVsPixel_purej.pdf");
  c->Print("pics/HFVsPixel_purej.eps");
  c->Print("pics/HFVsPixel_purej.C");  
*/
  TCanvas* ca = new TCanvas("ca","",550,500);
  ca->SetRightMargin(0.13);
  ca->SetLeftMargin(0.15);
  ca->SetBottomMargin(0.13);
  ca->SetLogz();
  hNPixelVsHF->SetAxisRange(0,5000,"Y");
  hNPixelVsHF->SetAxisRange(0,80000,"X");
  hNPixelVsHF->GetXaxis()->CenterTitle();
  hNPixelVsHF->GetYaxis()->CenterTitle();
  hNPixelVsHF->GetXaxis()->SetLabelSize(hNPixelVsHF->GetXaxis()->GetLabelSize());
  hNPixelVsHF->GetYaxis()->SetLabelSize(hNPixelVsHF->GetYaxis()->GetLabelSize());
  hNPixelVsHF->GetYaxis()->SetTitleOffset(1.2*hNPixelVsHF->GetYaxis()->GetTitleOffset());
  hNPixelVsHF->GetXaxis()->SetTitleOffset(hNPixelVsHF->GetXaxis()->GetTitleOffset());
  hNPixelVsHF->GetYaxis()->SetTitleSize(hNPixelVsHF->GetYaxis()->GetTitleSize());
  hNPixelVsHF->GetXaxis()->SetTitleSize(hNPixelVsHF->GetXaxis()->GetTitleSize());
  hNPixelVsHF->Draw("colz");
  TProfile* hNPixelVsHF_prof = (TProfile*)hNPixelVsHF->ProfileX("hNPixelVsHF_prof",-1,-1,"e");
  TF1* fit = new TF1("fit","[0]*x",0,120000);
  fit->SetParameter(0,0.07);
  hNPixelVsHF_prof->Fit("fit","RNO");
  fit->SetLineColor(kRed);
  fit->Draw("lsame");

  TLine* line = new TLine(0,3260,80000,3260);
  line->SetLineStyle(9);
  line->Draw("lsame");

  TLine* line1 = new TLine(51400,0,51400,5000);
  line1->SetLineStyle(9);
  line1->Draw("lsame");

  TLatex* latex = new TLatex();
  latex->SetNDC(1);
  latex->SetTextSize(latex->GetTextSize()*0.8);
  latex->DrawLatex(0.18,0.87,"CMS PbPb  #sqrt{s_{NN}} = 2.76 TeV");
  latex->DrawLatex(0.67,0.85,"0-0.2%");
  latex->DrawLatex(0.67,0.8,"centrality");

  //latex->DrawLatex(0.327,0.2,"CMS Preliminary");

  SaveCanvas(ca,"HI/UCC","HFVsPixel_mb_purej");
}
