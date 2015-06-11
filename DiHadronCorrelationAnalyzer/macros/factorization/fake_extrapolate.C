void fake_extrapolate()
{
  TFile* fhist = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_UCC2011_pixeltracks_INCLEFF1PtFullv2_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin110_centmax1000.root");
  TH2D* hdNdetadphi = (TH2D*)fhist->Get("dNdetadphicorrall_trg");
  TH1D* hdNdeta = (TH1D*)hdNdetadphi->ProjectionX("dNdeta",-1,-1,"e");
  
  TFile* ffake = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/efficiency/trkEffNew2012_HI_hiGoodTightMerged_new.root");

  TH2D* hfake[5];
  TH1D* hfake1D[5];
  TH2D* heff[5];

  for(int i=0;i<5;i++)
  {
    hfake[i] = (TH2D*)ffake->Get(Form("Fak_%d",i));
    heff[i] = (TH2D*)ffake->Get(Form("Eff_%d",i));
    hfake1D[i] = (TH1D*)hfake[i]->ProjectionY(Form("Fak1D_%d",i),hfake[i]->GetXaxis()->FindBin(-1.9),hfake[i]->GetXaxis()->FindBin(-0.5),"e");
    hfake1D[i]->Scale(1.0/(hfake[i]->GetXaxis()->FindBin(-0.5)-hfake[i]->GetXaxis()->FindBin(-1.9)+1));
    hfake1D[i]->SetMarkerColor(i+1);
  }

  TCanvas* c = new TCanvas("c","",550,500);
  c->SetLogx();
  hfake1D[0]->SetAxisRange(0.3,4,"X");
  hfake1D[0]->Draw("PE");
  hfake1D[1]->Draw("PESAME");
  hfake1D[2]->Draw("PESAME");
  hfake1D[3]->Draw("PESAME");
  hfake1D[4]->Draw("PESAME");

  TFile* fmult[5];
  fmult[0] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_pixeltracks_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin0_centmax2.root");
  fmult[1] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_pixeltracks_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin2_centmax4.root");
  fmult[2] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_pixeltracks_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin4_centmax12.root");
  fmult[3] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_pixeltracks_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin12_centmax20.root");
  fmult[4] = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_MB2011_pixeltracks_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin20_centmax40.root");
  TH1D* hmult[5];
  hmult[0] = (TH1D*)fmult[0]->Get("multrawall");
  hmult[1] = (TH1D*)fmult[1]->Get("multrawall");
  hmult[2] = (TH1D*)fmult[2]->Get("multrawall");
  hmult[3] = (TH1D*)fmult[3]->Get("multrawall");
  hmult[4] = (TH1D*)fmult[4]->Get("multrawall");

  double mult[5];
  double fake[5];
  double eff[5];
  for(int i=0;i<5;i++) 
  {
    mult[i] = hmult[i]->GetMean();
    fake[i] = hfake[i]->GetBinContent(hfake[0]->FindBin(0,0.5));
    eff[i] = heff[i]->GetBinContent(heff[0]->FindBin(0,0.5));
  }
  TGraph* gr_fake = new TGraph(5,mult,fake);
  TGraph* gr_eff = new TGraph(5,mult,eff);
  TCanvas* cc = new TCanvas("cc","",550,500);
  TH2D* htmp = new TH2D("htmp",";Track multiplicity;Fake rate (p_{T}=0.5GeV/c,#eta=0)",100,0,4900,100,0,0.1);
  htmp->GetYaxis()->SetTitleOffset(1.5*htmp->GetYaxis()->GetTitleOffset());
  htmp->GetXaxis()->CenterTitle();
  htmp->GetYaxis()->CenterTitle();
  htmp->Draw();
  gr_fake->Draw("Psame");
  TF1* fit = new TF1("fit","[0]+[1]*x+[2]*x*x",0,4900);
  fit->SetParameters(0,0.1/3000,0);
  gr_fake->Fit("fit","RNO");
  fit->SetLineColor(kRed);
  fit->Draw("Lsame");

  SaveCanvas(cc,"HI/UCC","fakevsmult_extrapolate");

  TCanvas* cc1 = new TCanvas("cc1","",550,500);
  TH2D* htmp1 = new TH2D("htmp1",";Track multiplicity;Efficiency (p_{T}=0.5GeV/c,#eta=0)",100,0,4900,100,0,1.0);
  htmp1->GetYaxis()->SetTitleOffset(1.5*htmp1->GetYaxis()->GetTitleOffset());
  htmp1->GetXaxis()->CenterTitle();
  htmp1->GetYaxis()->CenterTitle();
  htmp1->Draw();
  gr_eff->Draw("Psame");
  TF1* fit1 = new TF1("fit1","[0]+[1]*x+[2]*x*x",0,4900);
  fit1->SetParameters(0,0.1/3000,0);
  gr_eff->Fit("fit1","RNO");
  fit1->SetLineColor(kRed);
  fit1->Draw("Lsame");

  SaveCanvas(cc1,"HI/UCC","effvsmult_extrapolate");

  TH2D* heff_ucc = (TH2D*)heff[0]->Clone("heff_ucc");
  TH2D* hfake_ucc = (TH2D*)hfake[0]->Clone("hfake_ucc");
  heff_ucc->Reset();
  hfake_ucc->Reset();
  for(int mm=1;mm<=hfake[0]->GetNbinsX();mm++)
    for(int nn=1;nn<=hfake[0]->GetNbinsY();nn++)
    {
      double fakeall[5];
      double effall[5];
      for(int i=0;i<5;i++)
      {
        fakeall[i] = hfake[i]->GetBinContent(mm,nn);
        effall[i] = heff[i]->GetBinContent(mm,nn);
      }
      TGraph* grall_fake = new TGraph(5,mult,fakeall);
      TGraph* grall_eff = new TGraph(5,mult,effall);
      TF1* fit_fake = new TF1("fit_fake","[0]+[1]*x+[2]*x*x",0,4900);
      fit_fake->SetParameters(0,0.1/3000,0);
      grall_fake->Fit("fit_fake","RNO");
      TF1* fit_eff = new TF1("fit_eff","[0]+[1]*x+[2]*x*x",0,4900);
      fit_eff->SetParameters(1,-0.3/3000,0);
      grall_eff->Fit("fit_eff","RNO");
      heff_ucc->SetBinContent(mm,nn,grall_eff->Eval(3375));
      hfake_ucc->SetBinContent(mm,nn,grall_fake->Eval(3375));
      delete grall_fake;
      delete grall_eff;
      delete fit_fake;
      delete fit_eff;
    }

  TCanvas* cccc = new TCanvas("cccc","",900,400);
  cccc->Divide(2,1);
  cccc->cd(1);
  cccc->GetPad(1)->SetRightMargin(0.2);
  cccc->GetPad(1)->SetLogz();
  cccc->GetPad(1)->SetLogy();
  heff_ucc->SetAxisRange(-1.9,1.9,"X");
  heff_ucc->SetAxisRange(0.3,5,"Y");
  heff_ucc->SetAxisRange(0.0,1,"Z");
  heff_ucc->SetTitle("");
  heff_ucc->Draw("colz");
  cccc->cd(2);
  cccc->GetPad(2)->SetRightMargin(0.2);
  cccc->GetPad(2)->SetLogz();
  cccc->GetPad(2)->SetLogy();
  hfake_ucc->SetAxisRange(-1.9,1.9,"X");
  hfake_ucc->SetAxisRange(0.3,5,"Y");
  hfake_ucc->SetAxisRange(0.0,1,"Z");
  hfake_ucc->SetTitle("");
  hfake_ucc->Draw("colz");

  SaveCanvas(cccc,"HI/UCC","efffake_ucc020");

  TH1D* hfake1D_ucc = (TH1D*)hfake_ucc->ProjectionY("Fak1D_ucc",hfake_ucc->GetXaxis()->FindBin(-1.9),hfake_ucc->GetXaxis()->FindBin(-0.5),"e");
  hfake1D_ucc->Scale(1.0/(hfake_ucc->GetXaxis()->FindBin(-0.5)-hfake_ucc->GetXaxis()->FindBin(-1.9)+1));
  TCanvas* ccc = new TCanvas("ccc","",550,500);
  hfake1D_ucc->SetMaximum(0.2);
  hfake1D_ucc->GetYaxis()->SetTitleOffset(1.5*hfake1D_ucc->GetYaxis()->GetTitleOffset());
  hfake1D_ucc->GetXaxis()->CenterTitle();
  hfake1D_ucc->GetYaxis()->CenterTitle();
  hfake1D_ucc->SetTitle("0-0.2% centrality");
  hfake1D_ucc->SetYTitle("Fake rate");
  hfake1D_ucc->Draw("PE");

  TLatex* latex1 = new TLatex();
  latex1->SetNDC(1);
  latex1->SetTextSize(latex1->GetTextSize()*1.5);
  latex1->DrawLatex(0.7,0.84,"|#Delta#eta|>2");

  SaveCanvas(ccc,"HI/UCC","fake1D_deta_ucc020");
/*
  TFile* ffake_out = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/efficiency/fake_hiGoodTightMerged_ucc_new.root","recreate");
  hfake_ucc->Write();
  ffake_out->Close();
*/
}
