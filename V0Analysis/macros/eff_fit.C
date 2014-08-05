void eff_fit()
{
  TFile* f = new TFile("V0Eff_counting_10M.root");

  TH2D* ks2D = (TH2D*)f->Get("EffCountEtaPt_ks");
  TH2D* la2D = (TH2D*)f->Get("EffCountEtaPt_la");
/*
  TH2D* ks2Dnew = (TH2D*)ks2D->Clone("ks2Dnew");
  TH2D* la2Dnew = (TH2D*)la2D->Clone("la2Dnew");
  ks2Dnew->Reset();
  la2Dnew->Reset();

cout<<ks2D->GetNbinsY()<<endl;
cout<<ks2Dnew->GetNbinsY()<<endl;

  TH2D* ks2Dfine = new TH2D("ks2Dfine",";#eta;p_{T} (GeV/c)",6,-2.4,2.4,1000,0.,10.0);
  TH2D* ks2Dfiner = new TH2D("Eff2D_ks",";#eta;p_{T} (GeV/c)",60,-2.4,2.4,1000,0.,10.0);
  TH2D* la2Dfine = new TH2D("la2Dfine",";#eta;p_{T} (GeV/c)",6,-2.4,2.4,1000,0.,10.0);
  TH2D* la2Dfiner = new TH2D("Eff2D_la",";#eta;p_{T} (GeV/c)",60,-2.4,2.4,1000,0.,10.0);

  TCanvas* c10 = new TCanvas("c10","c10",900,600);
  c10->Divide(3,2);
  TCanvas* c11 = new TCanvas("c11","c11",900,600);
  c11->Divide(3,2);

  TH1D* hEffvsPt_ks[6];
  TH1D* hEffvsPt_la[6];
  TF1*  fitfunc_ks[6];
  TF1*  fitfunc_la[6];
  TF1*  fitfunc1_ks[6];
  TF1*  fitfunc1_la[6];
  TF1*  fitfunc2_ks[6];
  TF1*  fitfunc2_la[6];
  TF1*  fitfunc3_ks[6];
  TF1*  fitfunc3_la[6];
  for(int i=0;i<6;i++)
  {
    c10->cd(i+1);
    hEffvsPt_ks[i] = ks2D->ProjectionY(Form("effvspt_ks_%d",i+1),i+1,i+1,"e");
//    hEffvsPt_ks[i]->Smooth(10);
    hEffvsPt_ks[i]->Draw("PE");
    for(int j=1;j<=ks2D->GetNbinsY();j++)
    {
cout<<j<<" "<<hEffvsPt_ks[i]->GetBinContent(j)<<endl;
      ks2Dnew->SetBinContent(i+1,j,hEffvsPt_ks[i]->GetBinContent(j));
      ks2Dnew->SetBinError(i+1,j,hEffvsPt_ks[i]->GetBinError(j));
    }

    c11->cd(i+1);
    hEffvsPt_la[i] = la2D->ProjectionY(Form("effvspt_la_%d",i+1),i+1,i+1,"e");
//    hEffvsPt_la[i]->Smooth(10);
    hEffvsPt_la[i]->Draw("PE");
    for(int j=1;j<=la2D->GetNbinsY();j++)
    {
      la2Dnew->SetBinContent(i+1,j,hEffvsPt_la[i]->GetBinContent(j));
      la2Dnew->SetBinError(i+1,j,hEffvsPt_la[i]->GetBinError(j));
    }
  }
  
  for(i=1;i<=ks2Dfine->GetNbinsX();i++)
    for(j=1;j<=ks2Dfine->GetNbinsY();j++)
    {
      double cfine = ks2Dfine->GetYaxis()->GetBinCenter(j);
      int binnew = ks2Dnew->GetYaxis()->FindBin(cfine);
      double hnew = ks2Dnew->GetBinContent(i,binnew);
      double hnewd = ks2Dnew->GetBinContent(i,binnew-1);
      double hnewu = ks2Dnew->GetBinContent(i,binnew+1);
      double wnew = ks2Dnew->GetYaxis()->GetBinWidth(binnew);
      double wnewd = ks2Dnew->GetYaxis()->GetBinWidth(binnew-1);
      double wnewu = ks2Dnew->GetYaxis()->GetBinWidth(binnew+1);
      double cnew = ks2Dnew->GetYaxis()->GetBinCenter(binnew);
      double cnewd = ks2Dnew->GetYaxis()->GetBinCenter(binnew-1);
      double cnewu = ks2Dnew->GetYaxis()->GetBinCenter(binnew+1);
     
      double hfine;
      if(cfine < cnew) hfine = hnew-2*(hnew-hnewd)/(wnew+wnewd)*(cnew-cfine);
      if(cfine > cnew) hfine = hnew+2*(hnewu-hnew)/(wnew+wnewu)*(cfine-cnew);
      ks2Dfine->SetBinContent(i,j,hfine);
    }

  for(i=1;i<=la2Dfine->GetNbinsX();i++)
    for(j=1;j<=la2Dfine->GetNbinsY();j++)
    {
      double cfine = la2Dfine->GetYaxis()->GetBinCenter(j);
      int binnew = la2Dnew->GetYaxis()->FindBin(cfine);
      double hnew = la2Dnew->GetBinContent(i,binnew);
      double hnewd = la2Dnew->GetBinContent(i,binnew-1);
      double hnewu = la2Dnew->GetBinContent(i,binnew+1);
      double wnew = la2Dnew->GetYaxis()->GetBinWidth(binnew);
      double wnewd = la2Dnew->GetYaxis()->GetBinWidth(binnew-1);
      double wnewu = la2Dnew->GetYaxis()->GetBinWidth(binnew+1);
      double cnew = la2Dnew->GetYaxis()->GetBinCenter(binnew);
      double cnewd = la2Dnew->GetYaxis()->GetBinCenter(binnew-1);
      double cnewu = la2Dnew->GetYaxis()->GetBinCenter(binnew+1);

      double hfine;
      if(cfine < cnew) hfine = hnew-2*(hnew-hnewd)/(wnew+wnewd)*(cnew-cfine);
      if(cfine > cnew) hfine = hnew+2*(hnewu-hnew)/(wnew+wnewu)*(cfine-cnew);
      la2Dfine->SetBinContent(i,j,hfine);
    }

  for(i=1;i<=ks2Dfiner->GetNbinsX();i++)
    for(j=1;j<=ks2Dfiner->GetNbinsY();j++)
    {
      double cfiner = ks2Dfiner->GetXaxis()->GetBinCenter(i);
      int binnew = ks2Dfine->GetXaxis()->FindBin(cfiner);
      double hnew = ks2Dfine->GetBinContent(binnew,j);
      double hnewd = ks2Dfine->GetBinContent(binnew-1,j);
      double hnewu = ks2Dfine->GetBinContent(binnew+1,j);
      double wnew = ks2Dfine->GetXaxis()->GetBinWidth(binnew);
      double wnewd = ks2Dfine->GetXaxis()->GetBinWidth(binnew-1);
      double wnewu = ks2Dfine->GetXaxis()->GetBinWidth(binnew+1);
      double cnew = ks2Dfine->GetXaxis()->GetBinCenter(binnew);
      double cnewd = ks2Dfine->GetXaxis()->GetBinCenter(binnew-1);
      double cnewu = ks2Dfine->GetXaxis()->GetBinCenter(binnew+1);
     
      double hfine;
      if(cfiner < cnew && cfiner > -2.0 ) hfine = hnew-2*(hnew-hnewd)/(wnew+wnewd)*(cnew-cfiner);
      if(cfiner < cnew && cfiner < -2.0 ) hfine = hnew;
      if(cfiner > cnew && cfiner < 2.0 ) hfine = hnew+2*(hnewu-hnew)/(wnew+wnewu)*(cfiner-cnew);
      if(cfiner > cnew && cfiner > 2.0 ) hfine = hnew;
      ks2Dfiner->SetBinContent(i,j,hfine);
    }

  for(i=1;i<=la2Dfiner->GetNbinsX();i++)
    for(j=1;j<=la2Dfiner->GetNbinsY();j++)
    {
      double cfiner = la2Dfiner->GetXaxis()->GetBinCenter(i);
      int binnew = la2Dfine->GetXaxis()->FindBin(cfiner);
      double hnew = la2Dfine->GetBinContent(binnew,j);
      double hnewd = la2Dfine->GetBinContent(binnew-1,j);
      double hnewu = la2Dfine->GetBinContent(binnew+1,j);
      double wnew = la2Dfine->GetXaxis()->GetBinWidth(binnew);
      double wnewd = la2Dfine->GetXaxis()->GetBinWidth(binnew-1);
      double wnewu = la2Dfine->GetXaxis()->GetBinWidth(binnew+1);
      double cnew = la2Dfine->GetXaxis()->GetBinCenter(binnew);
      double cnewd = la2Dfine->GetXaxis()->GetBinCenter(binnew-1);
      double cnewu = la2Dfine->GetXaxis()->GetBinCenter(binnew+1);

      double hfine;
      if(cfiner < cnew && cfiner > -2.0 ) hfine = hnew-2*(hnew-hnewd)/(wnew+wnewd)*(cnew-cfiner);
      if(cfiner < cnew && cfiner < -2.0 ) hfine = hnew;
      if(cfiner > cnew && cfiner < 2.0 ) hfine = hnew+2*(hnewu-hnew)/(wnew+wnewu)*(cfiner-cnew);
      if(cfiner > cnew && cfiner > 2.0 ) hfine = hnew;
      la2Dfiner->SetBinContent(i,j,hfine);
    }

  TCanvas* cc = new TCanvas("cc","cc",550,500);
//  ks2Dnew->SetAxisRange(0,5.8,"Y");
  ks2Dnew->Draw("lego2");  

  TCanvas* cc3 = new TCanvas("cc3","cc3",550,500);
  la2Dfiner->SetAxisRange(0,5.8,"Y");
  la2Dfiner->Draw("SURF1");
*/

  TCanvas* cc4 = new TCanvas("cc4","cc4",550,500);
  ks2D->Draw("lego2");

  TCanvas* cc5 = new TCanvas("cc5","cc5",550,500);
  la2D->Draw("lego2");

  TFile* fout = new TFile("Efficiency2D_V0_10M.root","recreate");
  ks2D->Write("ks2Dnew");
  la2D->Write("la2Dnew");
  fout->Close();
}
