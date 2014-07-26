void eff_count()
{
  using namespace RooFit;

  TFile* f;
  f = new TFile("/net/hisrv0001/home/davidlw/scratch1/v0validation_V0EffCountAnav1_all_v6.root");
 
  double ptbins[] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.4,3.8,4.2,4.6,5.0,5.6,6.6,9.0,12.0};

  TH2D* ksmassptallsum;
  TH2D* lamassptallsum;
  TH2D* ksmassptall[6];
  TH2D* lamassptall[6];
  TH1D* ksmassall[6][30];
  TH1D* lamassall[6][30];
  TH2D* hYieldReco_la;
  TH2D* hYieldReco_ks;
  TH2D* hYieldGen_la;
  TH2D* hYieldGen_ks;
  TH2D* hYieldSim_la;
  TH2D* hYieldSim_ks;
  TH2D* hYieldMatch_la;
  TH2D* hYieldMatch_ks;

  ksmassptallsum = (TH2D*)f->Get("v0Validator/ksMassPtAll");
  lamassptallsum = (TH2D*)f->Get("v0Validator/lamMassPtAll");
  ksmassptallsum->SetAxisRange(0.45,0.55,"Y");
  lamassptallsum->SetAxisRange(1.095,1.14,"Y");

  hYieldMatch_la = (TH2D*)f->Get("v0Validator/LamEffVsEtaPt_num");
  hYieldMatch_ks = (TH2D*)f->Get("v0Validator/K0sEffVsEtaPt_num");
  hYieldSim_la = (TH2D*)f->Get("v0Validator/LamEffVsEtaPt_denom");
  hYieldSim_ks = (TH2D*)f->Get("v0Validator/K0sEffVsEtaPt_denom");

  hYieldGen_la = (TH2D*)f->Get("v0Validator/LamGenVsEtaPt");
  hYieldGen_ks = (TH2D*)f->Get("v0Validator/K0sGenVsEtaPt");
  hYieldReco_la = (TH2D*)hYieldGen_la->Clone("LamRecoVsEtaPt");
  hYieldReco_ks = (TH2D*)hYieldGen_ks->Clone("K0sRecoVsEtaPt");
  hYieldReco_la->Reset();
  hYieldReco_ks->Reset();
  hYieldReco_la->SetMinimum(1);
  hYieldReco_ks->SetMinimum(1);

  for(int i=0;i<6;i++) 
  {
    ksmassptall[i] = (TH2D*)f->Get(Form("v0Validator/ksMassPtAllEta%d",i+1));
    ksmassptall[i]->SetAxisRange(0.45,0.55,"Y");
  }

  for(int i=0;i<6;i++) 
  {
    lamassptall[i] = (TH2D*)f->Get(Form("v0Validator/lamMassPtAllEta%d",i+1));
    lamassptall[i]->SetAxisRange(1.095,1.14,"Y");
  }

  RooRealVar *x_la[6][30],*x_ks[6][30];
  RooDataHist *data_la[6][30],*data_ks[6][30];
  RooPlot *xframe_la[6][30],*xframe_ks[6][30];
  RooRealVar *mean_la[6][30],*mean_ks[6][30];
  RooRealVar *sigma1_la[6][30],*sigma1_ks[6][30];
  RooRealVar *sigma2_la[6][30],*sigma2_ks[6][30];
  RooRealVar *sig1_la[6][30],*sig1_ks[6][30];
  RooRealVar *sig2_la[6][30],*sig2_ks[6][30];
  RooRealVar *a_la[6][30],*a_ks[6][30];
  RooRealVar *b_la[6][30],*b_ks[6][30];
  RooRealVar *cp_la[6][30],*cp_ks[6][30];
  RooRealVar *d_la[6][30],*d_ks[6][30];
  RooGaussian *gaus1_la[6][30],*gaus1_ks[6][30];
  RooGaussian *gaus2_la[6][30],*gaus2_ks[6][30];
  RooPolynomial *poly_la[6][30],*poly_ks[6][30];
  RooRealVar *polysig_la[6][30],*polysig_ks[6][30];
  RooAddPdf *sum_la[6][30],*sum_ks[6][30];

  TLine* l1_la[6][30];
  TLine* l2_la[6][30];
  TLine* l1_ks[6][30];
  TLine* l2_ks[6][30];

  for(int i=0;i<24;i++)
  {
   for(int j=0;j<6;j++)
   {
    int nminpt = ksmassptall[j]->GetXaxis()->FindBin(ptbins[i]);
    int nmaxpt = ksmassptall[j]->GetXaxis()->FindBin(ptbins[i+1]);
   
    ksmassall[j][i] = ksmassptall[j]->ProjectionY(Form("ksMassAllEta%d_%d",j+1,i),nminpt,nmaxpt-1,"e");
    lamassall[j][i] = lamassptall[j]->ProjectionY(Form("lamMassAllEta%d_%d",j+1,i),nminpt,nmaxpt-1,"e");

    x_la[j][i] = new RooRealVar(Form("x_la_eta%d_%d",j+1,i),"mass",1.1,1.14);
    data_la[j][i] = new RooDataHist(Form("data_la_eta%d_%d",j+1,i),"dataset",*x_la[j][i],lamassall[j][i]);
    xframe_la[j][i] = x_la[j][i]->frame(80);
    data_la[j][i]->plotOn(xframe_la[j][i],Name(Form("data_la_eta%d_%d",j+1,i)));
    mean_la[j][i] = new RooRealVar(Form("mean_la_eta%d_%d",j+1,i),"mean",1.115,1.11,1.12);
    sigma1_la[j][i] = new RooRealVar(Form("sigma1_la_eta%d_%d",j+1,i),"sigma1",0.005,0.001,0.01);
    sigma2_la[j][i] = new RooRealVar(Form("sigma2_la_eta%d_%d",j+1,i),"sigma2",0.005,0.001,0.01);
    sig1_la[j][i] = new RooRealVar(Form("sig1_la_eta%d_%d",j+1,i),"signal1",10,0,10000000);
    sig2_la[j][i] = new RooRealVar(Form("sig2_la_eta%d_%d",j+1,i),"signal2",10,0,10000000);
    a_la[j][i] = new RooRealVar(Form("a_la_eta%d_%d",j+1,i),"a",0,-100000,100000);
    b_la[j][i] = new RooRealVar(Form("b_la_eta%d_%d",j+1,i),"b",0,-100000,100000);
    cp_la[j][i] = new RooRealVar(Form("cp_la_eta%d_%d",j+1,i),"cp",0,-100000,100000);
    d_la[j][i] = new RooRealVar(Form("d_la_eta%d_%d",j+1,i),"d",0,-100000,100000);
    gaus1_la[j][i] = new RooGaussian(Form("gaus1_la_eta%d_%d",j+1,i),"gaus1",*x_la[j][i],*mean_la[j][i],*sigma1_la[j][i]);
    gaus2_la[j][i] = new RooGaussian(Form("gaus2_la_eta%d_%d",j+1,i),"gaus2",*x_la[j][i],*mean_la[j][i],*sigma2_la[j][i]);
    poly_la[j][i] = new RooPolynomial(Form("poly_la_eta%d_%d",j+1,i),"poly",*x_la[j][i],RooArgList(*a_la[j][i],*b_la[j][i],*cp_la[j][i],*d_la[j][i]));
    polysig_la[j][i] = new RooRealVar(Form("polysig_la_eta%d_%d",j+1,i),"polysig",10,0,10000000);
    sum_la[j][i] = new RooAddPdf(Form("sum_la_eta%d_%d",j+1,i),"sum",RooArgList(*gaus1_la[j][i],*gaus2_la[j][i],*poly_la[j][i]),RooArgList(*sig1_la[j][i],*sig2_la[j][i],*polysig_la[j][i]));
    sum_la[j][i]->fitTo(*data_la[j][i]);
    sum_la[j][i]->fitTo(*data_la[j][i]);
    sum_la[j][i]->fitTo(*data_la[j][i]);
    sum_la[j][i]->plotOn(xframe_la[j][i],Name(Form("sum_la_eta%d_%d",j+1,i)));
    sum_la[j][i]->plotOn(xframe_la[j][i],Components(*poly_la[j][i]),LineStyle(kDashed));

    double meanf  = mean_la[j][i]->getVal();
    double meanfe  = mean_la[j][i]->getError();
    double sigmaf1  = sigma1_la[j][i]->getVal();
    double sigmaf2  = sigma2_la[j][i]->getVal();
    double bkgf  = polysig_la[j][i]->getVal();
    double sigf1  = sig1_la[j][i]->getVal();
    double sigf2  = sig2_la[j][i]->getVal();
    double sigwf1  = sigf1 /(sigf1 +sigf2 );
    double sigwf2  = sigf2 /(sigf1 +sigf2 );
    double sigmaf  = sqrt(sigmaf1 **2*sigwf1  + sigmaf2 **2*sigwf2 );
    double massmin  = meanf  - 2*sigmaf ;
    double massmax  = meanf  + 2*sigmaf ;
    int nmin = lamassall[j][i]->GetXaxis()->FindBin(massmin);
    int nmax = lamassall[j][i]->GetXaxis()->FindBin(massmax);
    double totyhe = 0;
    double totyh  = lamassall[j][i]->IntegralAndError(nmin,nmax,totyhe);
    l1_la[j][i] = new TLine(massmin ,0,massmin ,500);
    l2_la[j][i] = new TLine(massmax ,0,massmax ,500);
    x_la[j][i]->setRange("cut",massmin ,massmax );
    RooAbsReal* ibkg  = poly_la[j][i]->createIntegral(*x_la[j][i],NormSet(*x_la[j][i]),Range("cut"));
    RooAbsReal* isig1  = gaus1_la[j][i]->createIntegral(*x_la[j][i],NormSet(*x_la[j][i]),Range("cut"));
    RooAbsReal* isig2  = gaus2_la[j][i]->createIntegral(*x_la[j][i],NormSet(*x_la[j][i]),Range("cut"));
    double ibkgf = ibkg->getVal();
    double bkgfe = polysig_la[j][i]->getError();
    double isig1f = isig1->getVal();
    double isig2f = isig2->getVal();
    double bkgy = ibkgf*bkgf;
    double bkgye = ibkgf*bkgfe;
    double sigyh  = (totyh - bkgy);
    double sigyhe = sqrt(totyhe*totyhe+bkgye*bkgye); 

    hYieldReco_la->SetBinContent(j+1,i+1,sigyh);
    hYieldReco_la->SetBinError(j+1,i+1,sigyhe);

    x_ks[j][i] = new RooRealVar(Form("x_ks_eta%d_%d",j+1,i),"mass",0.44,0.56);
    data_ks[j][i] = new RooDataHist(Form("data_ks_eta%d_%d",j+1,i),"dataset",*x_ks[j][i],ksmassall[j][i]);
    xframe_ks[j][i] = x_ks[j][i]->frame(80);
    data_ks[j][i]->plotOn(xframe_ks[j][i],Name(Form("data_ks_eta%d_%d",j+1,i)));
    mean_ks[j][i] = new RooRealVar(Form("mean_ks_eta%d_%d",j+1,i),"mean",0.50,0.49,0.51);
    sigma1_ks[j][i] = new RooRealVar(Form("sigma1_ks_eta%d_%d",j+1,i),"sigma1",0.01,0.001,0.04);
    sigma2_ks[j][i] = new RooRealVar(Form("sigma2_ks_eta%d_%d",j+1,i),"sigma2",0.01,0.001,0.04);
    sig1_ks[j][i] = new RooRealVar(Form("sig1_ks_eta%d_%d",j+1,i),"signal1",10,0,10000000);
    sig2_ks[j][i] = new RooRealVar(Form("sig2_ks_eta%d_%d",j+1,i),"signal2",10,0,10000000);
    a_ks[j][i] = new RooRealVar(Form("a_ks_eta%d_%d",j+1,i),"a",0,-100000,100000);
    b_ks[j][i] = new RooRealVar(Form("b_ks_eta%d_%d",j+1,i),"b",0,-100000,100000);
    cp_ks[j][i] = new RooRealVar(Form("cp_ks_eta%d_%d",j+1,i),"cp",0,-100000,100000);
    d_ks[j][i] = new RooRealVar(Form("d_ks_eta%d_%d",j+1,i),"d",0,-100000,100000);
    gaus1_ks[j][i] = new RooGaussian(Form("gaus1_ks_eta%d_%d",j+1,i),"gaus1",*x_ks[j][i],*mean_ks[j][i],*sigma1_ks[j][i]);
    gaus2_ks[j][i] = new RooGaussian(Form("gaus2_ks_eta%d_%d",j+1,i),"gaus2",*x_ks[j][i],*mean_ks[j][i],*sigma2_ks[j][i]);
    poly_ks[j][i] = new RooPolynomial(Form("poly_ks_eta%d_%d",j+1,i),"poly",*x_ks[j][i],RooArgList(*a_ks[j][i],*b_ks[j][i],*cp_ks[j][i],*d_ks[j][i]));
    polysig_ks[j][i] = new RooRealVar(Form("polysig_ks_eta%d_%d",j+1,i),"polysig",10,0,10000000);
    sum_ks[j][i] = new RooAddPdf(Form("sum_ks_eta%d_%d",j+1,i),"sum",RooArgList(*gaus1_ks[j][i],*gaus2_ks[j][i],*poly_ks[j][i]),RooArgList(*sig1_ks[j][i],*sig2_ks[j][i],*polysig_ks[j][i]));
    sum_ks[j][i]->fitTo(*data_ks[j][i]);
    sum_ks[j][i]->fitTo(*data_ks[j][i]);
    sum_ks[j][i]->fitTo(*data_ks[j][i]);
    sum_ks[j][i]->plotOn(xframe_ks[j][i],Name(Form("sum_ks_eta%d_%d",j+1,i)));
    sum_ks[j][i]->plotOn(xframe_ks[j][i],Components(*poly_ks[j][i]),LineStyle(kDashed));

    double meanf  = mean_ks[j][i]->getVal();
    double meanfe  = mean_ks[j][i]->getError();
    double sigmaf1  = sigma1_ks[j][i]->getVal();
    double sigmaf2  = sigma2_ks[j][i]->getVal();
    double bkgf  = polysig_ks[j][i]->getVal();
    double sigf1  = sig1_ks[j][i]->getVal();
    double sigf2  = sig2_ks[j][i]->getVal();
    double sigwf1  = sigf1 /(sigf1 +sigf2 );
    double sigwf2  = sigf2 /(sigf1 +sigf2 );
    double sigmaf  = sqrt(sigmaf1 **2*sigwf1  + sigmaf2 **2*sigwf2 );
    double massmin  = meanf  - 2*sigmaf ;
    double massmax  = meanf  + 2*sigmaf ;
    int nmin = ksmassall[j][i]->GetXaxis()->FindBin(massmin);
    int nmax = ksmassall[j][i]->GetXaxis()->FindBin(massmax);
    double totyhe = 0;
    double totyh  = ksmassall[j][i]->IntegralAndError(nmin,nmax,totyhe);
    l1_ks[j][i] = new TLine(massmin ,0,massmin ,500);
    l2_ks[j][i] = new TLine(massmax ,0,massmax ,500);
    x_ks[j][i]->setRange("cut",massmin ,massmax );
    RooAbsReal* ibkg  = poly_ks[j][i]->createIntegral(*x_ks[j][i],NormSet(*x_ks[j][i]),Range("cut"));
    RooAbsReal* isig1  = gaus1_ks[j][i]->createIntegral(*x_ks[j][i],NormSet(*x_ks[j][i]),Range("cut"));
    RooAbsReal* isig2  = gaus2_ks[j][i]->createIntegral(*x_ks[j][i],NormSet(*x_ks[j][i]),Range("cut"));
    double ibkgf = ibkg->getVal();
    double bkgfe = polysig_ks[j][i]->getError();
    double isig1f = isig1->getVal();
    double isig2f = isig2->getVal();
    double bkgy = ibkgf*bkgf ;
    double bkgye = ibkgf*bkgfe ;
    double sigyh  = (totyh - bkgy);
    double sigyhe = sqrt(totyhe*totyhe+bkgye*bkgye);
    
    hYieldReco_ks->SetBinContent(j+1,i+1,sigyh);
    hYieldReco_ks->SetBinError(j+1,i+1,sigyhe);
   }
  }

  TCanvas* c = new TCanvas("c","c",900,600);
  c->Divide(3,2);
  for(int i=0;i<6;i++)
  {
    c->cd(i+1);
    ksmassptall[i]->Draw("colz");
  }

  TCanvas* c1 = new TCanvas("c1","c1",900,600);
  c1->Divide(3,2);
  for(int i=0;i<6;i++)
  {
    c1->cd(i+1);
    lamassptall[i]->Draw("colz");
  }

  TCanvas* c2 = new TCanvas("c2","c2",1000,800);
  c2->Divide(5,4);
  for(int i=0;i<17;i++) 
  {
    c2->cd(i+1);
    ksmassall[3][i]->Draw("PE");
    xframe_ks[3][i]->Draw("SAME");
  }

  TCanvas* c3 = new TCanvas("c3","c3",1000,800);
  c3->Divide(5,4);
  for(int i=0;i<17;i++) 
  {
    c3->cd(i+1);
    lamassall[3][i]->Draw("PE");
    xframe_la[3][i]->Draw("SAME");
  }

  TCanvas* c6 = new TCanvas("c6","c6",900,450);
  c6->Divide(2,1);
  c6->cd(1);
  c6->GetPad(1)->SetLogz();
  hYieldReco_la->Draw("lego2");
  c6->cd(2);
  c6->GetPad(2)->SetLogz();
  hYieldGen_la->Draw("lego2");

  TCanvas* c7 = new TCanvas("c7","c7",900,450);
  c7->Divide(2,1);
  c7->cd(1);
  c7->GetPad(1)->SetLogz();
  hYieldReco_ks->Draw("lego2");
  c7->cd(2);
  c7->GetPad(2)->SetLogz();
  hYieldGen_ks->Draw("lego2");

  TH2D* hYieldReco_la_ratio = (TH2D*)hYieldReco_la->Clone("hYieldReco_la_ratio");
  hYieldReco_la_ratio->Divide(hYieldGen_la);
  TCanvas* c4 = new TCanvas("c4","c4",550,500);
  hYieldReco_la_ratio->SetAxisRange(0,1.0,"Z");
  hYieldReco_la_ratio->Draw("lego2");  

  TH2D* hYieldReco_ks_ratio = (TH2D*)hYieldReco_ks->Clone("hYieldReco_ks_ratio");
  hYieldReco_ks_ratio->Divide(hYieldGen_ks);
  TCanvas* c5 = new TCanvas("c5","c5",550,500);
  hYieldReco_ks_ratio->SetAxisRange(0,1.0,"Z");
  hYieldReco_ks_ratio->Draw("lego2");

//  SaveCanvas(c,"HI/V0","ksmassfake");
//  SaveCanvas(c1,"HI/V0","lammassfake");
//  SaveCanvas(c2,"HI/V0","ksmassgood");
//  SaveCanvas(c3,"HI/V0","lammassgood");
}
