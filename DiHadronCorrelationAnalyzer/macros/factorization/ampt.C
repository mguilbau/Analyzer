// fraction of b<6 is 13%

void ampt()
{
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/AMPTGen_Minbias_2760GeV/merged/AMPTGen_Minbias_2760GeV_MBGEN_442p5_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HijingGen_Minbias_2760GeV/merged/HijingGen_Minbias_2760GeV_MBGEN_442p5_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/AMPTReco_Minbias_2760GeV/merged/AMPTReco_Minbias_2760GeV_MBRECO_442p5_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HijingReco_Minbias_2760GeV/merged/HijingReco_Minbias_2760GeV_B6RECO_442p5_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
  TFile* f1 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/AMPTReco_Minbias_2760GeV/merged/AMPTReco_Minbias_2760GeV_B6RECO_442p5_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
//  TFile* f1 = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HijingReco_Minbias_2760GeV/merged/HijingReco_Minbias_2760GeV_B6RECO_442p5_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");

  TNtuple* nt = (TNtuple*)f->Get("higeninfontuple");
  TNtuple* nt1 = (TNtuple*)f1->Get("higeninfontuple");

  TH2D* hNPixelVsHF = new TH2D("hNPixelVsHF",";HF Sum (GeV);Pixel Multiplicity",120,0,6000-1,120,0,120000-1);
  TH2D* hNPixelVsHF1 = new TH2D("hNPixelVsHF1",";HF Sum (GeV);Pixel Multiplicity",120,0,6000-1,120,0,120000-1);

  TH2D* hNpartVsHF = new TH2D("hNpartVsHF",";N_{part};HF Sum (GeV)",500,0,500,120,0,6000);
  TH2D* hNpartVsHF1 = new TH2D("hNpartVsHF1",";N_{part};HF Sum (GeV)",500,0,500,120,0,6000);
  TH2D* hBVsHF = new TH2D("hBVsHF",";B (fm);HF Sum (GeV)",200,0,20,30,0,6000);
  TH2D* hBVsHF1 = new TH2D("hBVsHF1",";B (fm);HF Sum (GeV)",200,0,20,30,0,6000);
  TH1D* hHF = new TH1D("hHF",";HF Sum (GeV)",30,0,6000);
  TH1D* hHF1 = new TH1D("hHF1",";HF Sum (GeV)",30,0,6000);

  TH2D* hNpartVsNPixel = new TH2D("hNpartVsNPixel",";N_{part};Pixel Multiplicity",500,0,500,120,0,120000);
  TH2D* hNpartVsNPixel1 = new TH2D("hNpartVsNPixel1",";N_{part};Pixel Multiplicity",500,0,500,120,0,120000);
  TH2D* hBVsNPixel = new TH2D("hBVsNPixel",";B (fm);Pixel Multiplicity",200,0,20,120,0,120000);
  TH2D* hBVsNPixel1 = new TH2D("hBVsNPixel1",";B (fm);Pixel Multiplicity",200,0,20,120,0,120000);
  TH1D* hNPixel = new TH1D("hNPixel",";Pixel Multiplicity",30,0,120000);
  TH1D* hNPixel1 = new TH1D("hNPixel1",";Pixel Multiplicity",30,0,120000);

  TH1D* hNpart021 = new TH1D("hNpart021",";N_{part};Counts",100,0,600);
  TH1D* hNpart020 = new TH1D("hNpart020",";N_{part};Counts",100,0,600);
  TH1D* hNpart002 = new TH1D("hNpart002",";N_{part};Counts",100,0,600);
  TH1D* hNpart100 = new TH1D("hNpart100",";N_{part};Counts",100,0,600);
  TH1D* hNpart110 = new TH1D("hNpart110",";N_{part};Counts",100,0,600);
  TH1D* hNpart250 = new TH1D("hNpart250",";N_{part};Counts",100,0,600);
  TH1D* hNpart500 = new TH1D("hNpart500",";N_{part};Counts",100,0,600);

  TH1D* hB021 = new TH1D("hB021",";b (fm);Counts",30,0,10);
  TH1D* hB020 = new TH1D("hB020",";b (fm);Counts",30,0,10);
  TH1D* hB002 = new TH1D("hB002",";b (fm);Counts",30,0,10);
  TH1D* hB100 = new TH1D("hB100",";b (fm);Counts",30,0,10);
  TH1D* hB110 = new TH1D("hB110",";b (fm);Counts",30,0,10);
  TH1D* hB250 = new TH1D("hB250",";b (fm);Counts",30,0,10);
  TH1D* hB500 = new TH1D("hB500",";b (fm);Counts",30,0,10);

  nt->Draw("npixel:hft>>hNPixelVsHF","","GOFF");
  nt1->Draw("npixel:hft>>hNPixelVsHF1","","GOFF");
  nt->Draw("hft:npart>>hNpartVsHF","","GOFF");
  nt1->Draw("hft:npart>>hNpartVsHF1","","GOFF");
  nt->Draw("hft:b>>hBVsHF","","GOFF");
  nt1->Draw("hft:b>>hBVsHF1","","GOFF");
  nt->Draw("hft>>hHF","","GOFF");
  nt1->Draw("hft>>hHF1","","GOFF");
  nt->Draw("npixel:npart>>hNpartVsNPixel","","GOFF");
  nt1->Draw("npixel:npart>>hNpartVsNPixel1","","GOFF");
  nt->Draw("npixel:b>>hBVsNPixel","","GOFF");
  nt1->Draw("npixel:b>>hBVsNPixel1","","GOFF");
  nt->Draw("npixel>>hNPixel","","GOFF");
  nt1->Draw("npixel>>hNPixel1","","GOFF");

  nt1->Draw("npart>>hNpart021","hft>4161","GOFF");
  nt1->Draw("npart>>hNpart020","npixel>86484 && hft>4130","GOFF");
  nt1->Draw("npart>>hNpart002","npixel>93185 && hft>4450","GOFF");
  nt1->Draw("npart>>hNpart110","hft>3870 && npixel>81040","GOFF");
  nt1->Draw("npart>>hNpart100","hft>3900","GOFF");
  nt1->Draw("npart>>hNpart250","hft>3660","GOFF");
  nt1->Draw("npart>>hNpart500","hft>3250 && hft<3660","GOFF");

  nt1->Draw("b>>hB021","hft>4161","GOFF");
  nt1->Draw("b>>hB020","npixel>86484 && hft>4130","GOFF");
  nt1->Draw("b>>hB002","npixel>93185 && hft>4450","GOFF");
  nt1->Draw("b>>hB110","hft>3870 && npixel>81040","GOFF");
  nt1->Draw("b>>hB100","hft>3900","GOFF");
  nt1->Draw("b>>hB250","hft>3660","GOFF");
  nt1->Draw("b>>hB500","hft>3250 && hft<3660","GOFF");

cout<<hNpart002->Integral()<<" "<<hNpart020->Integral()<<" "<<hNpart021->Integral()<<" "<<hNpart100->Integral()<<" "<<hNpart110->Integral()<<" "<<hNpart250->Integral()<<" "<<hNpart500->Integral()<<endl;
cout<<hNpart002->GetMean()<<" "<<hNpart020->GetMean()<<" "<<hNpart021->GetMean()<<" "<<hNpart100->GetMean()<<" "<<hNpart110->GetMean()<<" "<<hNpart250->GetMean()<<" "<<hNpart500->GetMean()<<endl;
cout<<hNpart002->GetMeanError()<<" "<<hNpart020->GetMeanError()<<" "<<hNpart021->GetMeanError()<<" "<<hNpart100->GetMeanError()<<" "<<hNpart110->GetMeanError()<<" "<<hNpart250->GetMeanError()<<" "<<hNpart500->GetMeanError()<<endl;
cout<<hNpart002->GetRMS()<<" "<<hNpart020->GetRMS()<<" "<<hNpart021->GetRMS()<<" "<<hNpart100->GetRMS()<<" "<<hNpart110->GetRMS()<<" "<<hNpart250->GetRMS()<<" "<<hNpart500->GetRMS()<<endl;
cout<<endl;
cout<<hB002->GetMean()<<" "<<hB020->GetMean()<<" "<<hB021->GetMean()<<" "<<hB100->GetMean()<<" "<<hB110->GetMean()<<" "<<hB250->GetMean()<<" "<<hB500->GetMean()<<endl;
cout<<hB002->GetRMS()<<" "<<hB020->GetRMS()<<" "<<hB021->GetRMS()<<" "<<hB100->GetRMS()<<" "<<hB110->GetRMS()<<" "<<hB250->GetRMS()<<" "<<hB500->GetRMS()<<endl;

  hNpart002->SetMarkerColor(4);
  hNpart100->SetMarkerColor(3);
  hNpart110->SetMarkerColor(3);
  hNpart110->SetMarkerStyle(25);
  hNpart100->SetMarkerStyle(21);
  hNpart250->SetMarkerColor(6);
  hNpart500->SetMarkerColor(1);
  hNpart021->SetMarkerColor(2);
  hNpart020->SetMarkerColor(2);
  hNpart021->SetMarkerStyle(24);
  hNpart020->SetMarkerStyle(20);

  hB002->SetMarkerColor(4);
  hB100->SetMarkerColor(3);
  hB110->SetMarkerColor(3);
  hB110->SetMarkerStyle(25);
  hB100->SetMarkerStyle(21);
  hB250->SetMarkerColor(6);
  hB500->SetMarkerColor(1);
  hB021->SetMarkerColor(2);
  hB020->SetMarkerColor(2);
  hB021->SetMarkerStyle(24);
  hB020->SetMarkerStyle(20);

  TCanvas* cnpart = new TCanvas("cnpart","",550,500);
  cnpart->SetLogy();
  cnpart->SetLeftMargin(0.16);
  hNpart250->SetAxisRange(250,430,"X");
  hNpart250->SetMaximum(5000);
  hNpart250->GetXaxis()->CenterTitle();
  hNpart250->GetYaxis()->CenterTitle();
  hNpart250->Draw("PE");
  hNpart500->Draw("PESAME");
  hNpart110->Draw("PESAME");
  hNpart100->Draw("PESAME");
  hNpart020->Draw("PESAME");
  hNpart002->Draw("PESAME");
  hNpart021->Draw("PESAME");

  TLegend* legend = new TLegend(0.15,0.52,0.53,0.92);
  legend->SetFillStyle(0);
  legend->SetTextFont(42);
  legend->AddEntry(hNpart500,"2.5-5%, HF","P");
  legend->AddEntry(hNpart250,"0-2.5%, HF","P");
  legend->AddEntry(hNpart100,"0-1.0%, HF","P");
  legend->AddEntry(hNpart110,"0-1.0%, HF+NPixel","P");
  legend->AddEntry(hNpart021,"0-0.2%, HF","P");
  legend->AddEntry(hNpart020,"0-0.2%, HF+NPixel","P");
  legend->AddEntry(hNpart002,"0-0.02%, HF+NPixel","P");
  legend->Draw("same");

  TLatex* latex = new TLatex();
  latex->SetNDC(1);
  latex->SetTextSize(latex->GetTextSize()*1.0);
  latex->DrawLatex(0.65,0.88,"CMS Preliminary");
  latex->DrawLatex(0.455,0.82,"AMPT PbPb  #sqrt{s_{NN}} = 2.76 TeV");
/*
  for(int i=1;i<=hNpart020->GetNbinsX();i++)
  {
    cout<<(int)hNpart020->GetBinCenter(i)<<"            "<<hNpart020->GetBinContent(i)<<endl;
  }
*/
  SaveCanvas(cnpart,"HI/UCC","Npart_b6_ampt");

  TCanvas* cb = new TCanvas("cb","",550,500);
  cb->SetLogy();
  cb->SetLeftMargin(0.16);
  hB250->SetAxisRange(100,430,"X");
  hB250->SetMaximum(5500);
  hB250->GetXaxis()->CenterTitle();
  hB250->GetYaxis()->CenterTitle();
  hB250->Draw("PE");
  hB500->Draw("PESAME");
  hB110->Draw("PESAME");
  hB100->Draw("PESAME");
  hB020->Draw("PESAME");
  hB002->Draw("PESAME");
  hB021->Draw("PESAME");

  TLegend* legend2 = new TLegend(0.6,0.3,0.96,0.78);
  legend2->SetFillStyle(0);
  legend2->SetTextFont(42);
  legend2->AddEntry(hB500,"2.5-5%, HF","P");
  legend2->AddEntry(hB250,"0-2.5%, HF","P");
  legend2->AddEntry(hB100,"0-1.0%, HF","P");
  legend2->AddEntry(hB110,"0-1.0%, HF+NPixel","P");
  legend2->AddEntry(hB021,"0-0.2%, HF","P");
  legend2->AddEntry(hB020,"0-0.2%, HF+NPixel","P");
  legend2->AddEntry(hB002,"0-0.02%, HF+NPixel","P");
  legend2->Draw("same");
  TLatex* latex2 = new TLatex();
  latex2->SetNDC(1);
  latex2->SetTextSize(latex2->GetTextSize()*1.0);
  latex2->DrawLatex(0.65,0.88,"CMS Preliminary");
  latex2->DrawLatex(0.455,0.82,"AMPT PbPb  #sqrt{s_{NN}} = 2.76 TeV");

  SaveCanvas(cb,"HI/UCC","B_b6_ampt");
/*
  cnpart->Print("pics/Npart_b6_ampt.gif");
  cnpart->Print("pics/Npart_b6_ampt.pdf");
  cnpart->Print("pics/Npart_b6_ampt.eps");
  cnpart->Print("pics/Npart_b6_ampt.C");
*/
return;
  TCanvas* ca = new TCanvas("ca","",850,400);
  ca->Divide(2,1);
  ca->cd(1);
  ca->GetPad(1)->SetLogz();
  hBVsHF->Draw("colz");
  ca->cd(2);
  ca->GetPad(2)->SetLogz();
  hBVsHF1->Draw("colz");

  TCanvas* cb = new TCanvas("cb","",850,400);
  cb->Divide(2,1);
  cb->cd(1);
  cb->GetPad(1)->SetLogz();
  hBVsNPixel->Draw("colz");
  cb->cd(2);
  cb->GetPad(2)->SetLogz();
  hBVsNPixel1->Draw("colz");

  TCanvas* c = new TCanvas("c","",850,400);
  c->Divide(2,1);
  c->cd(1);
  c->GetPad(1)->SetLogz();
  hNpartVsHF->GetXaxis()->CenterTitle();
  hNpartVsHF->GetYaxis()->CenterTitle();
  hNpartVsHF->Draw("colz");
  c->cd(2);
  c->GetPad(2)->SetLogz();
  hNpartVsHF1->GetXaxis()->CenterTitle();
  hNpartVsHF1->GetYaxis()->CenterTitle();
  hNpartVsHF1->Draw("colz");

  TCanvas* cbb = new TCanvas("cbb","",920,400);
  cbb->Divide(2,1);
  cbb->cd(1);
  cbb->GetPad(1)->SetRightMargin(0.16);
  cbb->GetPad(1)->SetTopMargin(0.1);
  cbb->GetPad(1)->SetLogz();
  hNpartVsHF->GetYaxis()->SetTitleOffset(1.5*hNpartVsHF->GetYaxis()->GetTitleOffset());
  hNpartVsHF->GetXaxis()->CenterTitle();
  hNpartVsHF->GetYaxis()->CenterTitle();
  hNpartVsHF->SetAxisRange(0,430,"X");
  hNpartVsHF->Draw("colz");
  cbb->cd(2);
  cbb->GetPad(2)->SetRightMargin(0.16);
  cbb->GetPad(2)->SetTopMargin(0.1);
  cbb->GetPad(2)->SetLogz();
  hNpartVsNPixel->GetXaxis()->CenterTitle();
  hNpartVsNPixel->GetYaxis()->CenterTitle();
  hNpartVsNPixel->SetAxisRange(0,430,"X");
  hNpartVsNPixel->Draw("colz");

  cbb->cd(1);  
  TLatex* latex21 = new TLatex();
  latex21->SetNDC(1);
  latex21->SetTextSize(latex21->GetTextSize()*0.9);
  latex21->DrawLatex(0.25,0.84,"CMS Preliminary");
  latex21->DrawLatex(0.25,0.78,"AMPT PbPb  #sqrt{s_{NN}} = 2.76 TeV");

  cbb->cd(2);
  TLatex* latex22 = new TLatex();
  latex22->SetNDC(1);
  latex22->SetTextSize(latex22->GetTextSize()*0.9);
  latex22->DrawLatex(0.25,0.84,"CMS Preliminary");
  latex22->DrawLatex(0.25,0.78,"AMPT PbPb  #sqrt{s_{NN}} = 2.76 TeV");

  SaveCanvas(cbb,"HI/UCC","NpartVsHFNPixel_mb_ampt");

  TCanvas* ccc = new TCanvas("ccc","",570,500);
  ccc->SetLeftMargin(0.2);
  ccc->SetRightMargin(0.16);
  ccc->SetTopMargin(0.1);
  ccc->SetLogz();
  hNPixelVsHF->GetYaxis()->SetTitleOffset(1.15*hNPixelVsHF->GetYaxis()->GetTitleOffset());
  hNPixelVsHF->GetXaxis()->CenterTitle();
  hNPixelVsHF->GetYaxis()->CenterTitle();
  hNPixelVsHF->Draw("colz"); 
  TProfile* hNPixelVsHF_prof = (TProfile*)hNPixelVsHF->ProfileX("hNPixelVsHF_prof",-1,-1,"e");
//  hNPixelVsHF_prof->Draw("");
  TF1* fit = new TF1("fit","[0]*x",0,120000);
  fit->SetParameter(0,0.07);
  hNPixelVsHF_prof->Fit("fit","RNO");
  fit->SetLineColor(kRed);
  fit->Draw("lsame");

  TLatex* latex1 = new TLatex();
  latex1->SetNDC(1);
  latex1->SetTextSize(latex1->GetTextSize()*1.0);
  latex1->DrawLatex(0.24,0.84,"CMS Preliminary");
  latex1->DrawLatex(0.24,0.78,"AMPT PbPb  #sqrt{s_{NN}} = 2.76 TeV");

  SaveCanvas(ccc,"HI/UCC","HFVsNPixel_mb_ampt");

return;
  hHF1->Scale(0.3);

  TCanvas* c1 = new TCanvas("c1","",450,400);
  c1->SetLogy();
  hHF1->SetMarkerColor(kRed);
  hHF->Draw("PE");
  hHF1->Draw("PESAME");

  TCanvas* cc = new TCanvas("cc","",850,400);
  cc->Divide(2,1);
  cc->cd(1);
  cc->GetPad(1)->SetLogz();
  hNpartVsNPixel->Draw("colz");
  cc->cd(2);
  cc->GetPad(2)->SetLogz();
  hNpartVsNPixel1->Draw("colz");

  TCanvas* ccbb = new TCanvas("ccbb","",850,400);
  ccbb->Divide(2,1);
  ccbb->cd(1);
  ccbb->GetPad(1)->SetLogz();
  hNpartVsHF1->Draw("colz");
  ccbb->cd(2);
  ccbb->GetPad(2)->SetLogz();
  hNpartVsNPixel1->Draw("colz");
/*
  ccbb->Print("pics/NpartVsHFNPixel_b6_ampt.gif");
  ccbb->Print("pics/NpartVsHFNPixel_b6_ampt.pdf");
  ccbb->Print("pics/NpartVsHFNPixel_b6_ampt.eps");
  ccbb->Print("pics/NpartVsHFNPixel_b6_ampt.C");
*/
  hNPixel1->Scale(0.3);

  TCanvas* cc1 = new TCanvas("cc1","",450,400);
  cc1->SetLogy();
  hNPixel1->SetMarkerColor(kRed);
  hNPixel->Draw("PE");
  hNPixel1->Draw("PESAME");

}
