void eff_test()
{
  using namespace RooFit;

  TFile* f;
//  f = new TFile("/net/hisrv0001/home/davidlw/scratch1/v0validation_V0EffCountAnav1_5M_v6.root");
//  f = new TFile("/net/hisrv0001/home/davidlw/scratch1/v0validation_all_v6.root");
  f = new TFile("/net/hisrv0001/home/davidlw/scratch1/v0validation_V0EffMatchAna_v12.root");

  double ptbins[] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.5,3.0,4.0,5.0,6.0,8.0,10.0};
  int nptbins[18] = {0,2,4,6,8,10,12,14,16,18,20,25,30,40,50,60,80,100};
  double ptbinwidth[17] = {0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.5,0.5,1.0,1.0,1.0,2.0,2.0};

  TH2D* ksmassptgoodsum;
  TH2D* lamassptgoodsum;
  TH1D* ksmassgoodsum[20];
  TH1D* lamassgoodsum[20];

  TH2D* ksmassptallsum;
  TH2D* lamassptallsum;
  TH2D* ksmassptall[7];
  TH2D* lamassptall[7];
  TH1D* ksmassall[7][20];
  TH1D* lamassall[7][20];
  TH2D* hYieldReco_la;
  TH2D* hYieldReco_ks;
  TH2D* hYieldRecoFit_la;
  TH2D* hYieldRecoFit_ks;
  TH2D* hYieldGen_la;
  TH2D* hYieldGen_ks;
  TH2D* hYieldSim_la;
  TH2D* hYieldSim_ks;
  TH2D* hYieldMatch_la;
  TH2D* hYieldMatch_ks;
  TH1D* hYieldRecoPt_la[7];
  TH1D* hYieldRecoPt_ks[7];
  TH1D* hYieldRecoFitPt_la[7];
  TH1D* hYieldRecoFitPt_ks[7];
  TH1D* hYieldGenPt_la[7];
  TH1D* hYieldGenPt_ks[7];
  TH1D* hYieldSimPt_la[7];
  TH1D* hYieldSimPt_ks[7];
  TH1D* hYieldMatchPt_la[7];
  TH1D* hYieldMatchPt_ks[7];


  ksmassptgoodsum = (TH2D*)f->Get("v0Validator/ksMassPtGood");
  lamassptgoodsum = (TH2D*)f->Get("v0Validator/lamMassPtGood");
  ksmassptgoodsum->SetAxisRange(0.45,0.55,"Y");
  lamassptgoodsum->SetAxisRange(1.095,1.14,"Y");

  ksmassptallsum = (TH2D*)f->Get("v0Validator/ksMassPtAll");
  lamassptallsum = (TH2D*)f->Get("v0Validator/lamMassPtAll");
  ksmassptallsum->SetAxisRange(0.45,0.55,"Y");
  lamassptallsum->SetAxisRange(1.095,1.14,"Y");

  hYieldMatch_la = (TH2D*)f->Get("v0Validator/LamEffVsEtaPt_num");
  hYieldMatch_ks = (TH2D*)f->Get("v0Validator/K0sEffVsEtaPt_num");
  hYieldSim_la = (TH2D*)f->Get("v0Validator/LamEffVsEtaPt_denom");
  hYieldSim_ks = (TH2D*)f->Get("v0Validator/K0sEffVsEtaPt_denom");

  TH1D* hYieldGood_la = (TH1D*)f->Get("v0Validator/LamFakeVsPt_denom");
  TH1D* hYieldGood_ks = (TH1D*)f->Get("v0Validator/K0sFakeVsPt_denom");
  TH1D* hYieldMatch1D_la = (TH1D*)f->Get("v0Validator/LamEffVsPt_num");
  TH1D* hYieldMatch1D_ks = (TH1D*)f->Get("v0Validator/K0sEffVsPt_num");

  hYieldGen_la = (TH2D*)f->Get("v0Validator/LamGenVsEtaPt");
  hYieldGen_ks = (TH2D*)f->Get("v0Validator/K0sGenVsEtaPt");
  hYieldReco_la = (TH2D*)hYieldGen_la->Clone("LamRecoVsEtaPt");
  hYieldReco_ks = (TH2D*)hYieldGen_ks->Clone("K0sRecoVsEtaPt");
  hYieldReco_la->Reset();
  hYieldReco_ks->Reset();
  hYieldRecoFit_la = (TH2D*)hYieldGen_la->Clone("LamRecoVsEtaPt");
  hYieldRecoFit_ks = (TH2D*)hYieldGen_ks->Clone("K0sRecoVsEtaPt");
  hYieldRecoFit_la->Reset();
  hYieldRecoFit_ks->Reset();

//  hYieldReco_la->SetMinimum(1);
//  hYieldReco_ks->SetMinimum(1);

  TH2D* hSimToReco_la = (TH2D*)hYieldSim_la->Clone("SimToReco_la");
  hSimToReco_la->Divide(hYieldGen_la);
  TH2D* hSimToReco_ks = (TH2D*)hYieldSim_ks->Clone("SimToReco_ks");
  hSimToReco_ks->Divide(hYieldGen_ks);

  TH1D* hYieldMatch1D_la_ratio = (TH1D*)hYieldMatch1D_la->Clone("Test_la");
  hYieldMatch1D_la_ratio->Divide(hYieldGood_la);
  TH1D* hYieldMatch1D_ks_ratio = (TH1D*)hYieldMatch1D_ks->Clone("Test_ks");
  hYieldMatch1D_ks_ratio->Divide(hYieldGood_ks);

  TCanvas* ccc = new TCanvas("ccc","ccc",800,400);
  ccc->Divide(2,1);
  ccc->cd(1);
  hSimToReco_ks->Draw("lego2");
  ccc->cd(2);
  hSimToReco_la->Draw("lego2");

  TCanvas* cccc = new TCanvas("cccc","cccc",800,400);
  cccc->Divide(2,1);
  cccc->cd(1);
  hYieldMatch1D_ks_ratio->Draw("PE");
  cccc->cd(2);
  hYieldMatch1D_la_ratio->Draw("PE");

  for(int i=0;i<6;i++) 
  {
    ksmassptall[i] = (TH2D*)f->Get(Form("v0Validator/ksMassPtAllEta%d",i+1));
    ksmassptall[i]->SetAxisRange(0.44,0.56,"Y");
  }
  ksmassptall[6] = (TH2D*)f->Get("v0Validator/ksMassPtAll");
  ksmassptall[6]->SetAxisRange(0.45,0.55,"Y");

  for(int i=0;i<6;i++) 
  {
    lamassptall[i] = (TH2D*)f->Get(Form("v0Validator/lamMassPtAllEta%d",i+1));
    lamassptall[i]->SetAxisRange(1.09,1.145,"Y");
  }
  lamassptall[6] = (TH2D*)f->Get("v0Validator/lamMassPtAll");
  lamassptall[6]->SetAxisRange(1.095,1.14,"Y");

  RooRealVar *x_la[7][20],*x_ks[7][20];
  RooDataHist *data_la[7][20],*data_ks[7][20];
  RooPlot *xframe_la[7][20],*xframe_ks[7][20];
  RooRealVar *mean_la[7][20],*mean_ks[7][20];
  RooRealVar *sigma1_la[7][20],*sigma1_ks[7][20];
  RooRealVar *sigma2_la[7][20],*sigma2_ks[7][20];
  RooRealVar *sig1_la[7][20],*sig1_ks[7][20];
  RooRealVar *sig2_la[7][20],*sig2_ks[7][20];
  RooRealVar *a_la[7][20],*a_ks[7][20];
  RooRealVar *b_la[7][20],*b_ks[7][20];
  RooRealVar *cp_la[7][20],*cp_ks[7][20];
  RooRealVar *d_la[7][20],*d_ks[7][20];
  RooGaussian *gaus1_la[7][20],*gaus1_ks[7][20];
  RooGaussian *gaus2_la[7][20],*gaus2_ks[7][20];
  RooPolynomial *poly_la[7][20],*poly_ks[7][20];
  RooRealVar *polysig_la[7][20],*polysig_ks[7][20];
  RooAddPdf *sum_la[7][20],*sum_ks[7][20];

  TLine* l1_la[7][20];
  TLine* l2_la[7][20];
  TLine* l1_ks[7][20];
  TLine* l2_ks[7][20];

  for(int i=0;i<17;i++)
  {
   for(int j=0;j<7;j++)
   {
    int nminpt = ksmassptall[j]->GetXaxis()->FindBin(ptbins[i]+0.0001);
    int nmaxpt = ksmassptall[j]->GetXaxis()->FindBin(ptbins[i+1]-0.0001);
   
//    ksmassall[j][i] = ksmassptall[j]->ProjectionY(Form("ksMassAllEta%d_%d",j+1,i),nminpt,nmaxpt,"e");
//    lamassall[j][i] = lamassptall[j]->ProjectionY(Form("lamMassAllEta%d_%d",j+1,i),nminpt,nmaxpt,"e");

    ksmassall[j][i] = ksmassptall[j]->ProjectionY(Form("ksMassAllEta%d_%d",j+1,i),nptbins[i]+1,nptbins[i+1],"e");
    lamassall[j][i] = lamassptall[j]->ProjectionY(Form("lamMassAllEta%d_%d",j+1,i),nptbins[i]+1,nptbins[i+1],"e");

    x_la[j][i] = new RooRealVar(Form("x_la_eta%d_%d",j+1,i),"mass",1.1,1.14);
    data_la[j][i] = new RooDataHist(Form("data_la_eta%d_%d",j+1,i),"dataset",*x_la[j][i],lamassall[j][i]);
    xframe_la[j][i] = x_la[j][i]->frame(80);
    data_la[j][i]->plotOn(xframe_la[j][i],Name(Form("data_la_eta%d_%d",j+1,i)));
    mean_la[j][i] = new RooRealVar(Form("mean_la_eta%d_%d",j+1,i),"mean",1.115,1.11,1.12);
    sigma1_la[j][i] = new RooRealVar(Form("sigma1_la_eta%d_%d",j+1,i),"sigma1",0.005,0.001,0.008);
    sigma2_la[j][i] = new RooRealVar(Form("sigma2_la_eta%d_%d",j+1,i),"sigma2",0.005,0.001,0.008);
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
//    double totyh  = lamassall[j][i]->Integral(nmin,nmax);
    l1_la[j][i] = new TLine(massmin ,0,massmin ,500);
    l2_la[j][i] = new TLine(massmax ,0,massmax ,500);
    x_la[j][i]->setRange("cut",massmin ,massmax );
    RooAbsReal* ibkg  = poly_la[j][i]->createIntegral(*x_la[j][i],NormSet(*x_la[j][i]),Range("cut"));
    RooAbsReal* isig1  = gaus1_la[j][i]->createIntegral(*x_la[j][i],NormSet(*x_la[j][i]));//,Range("cut"));
    RooAbsReal* isig2  = gaus2_la[j][i]->createIntegral(*x_la[j][i],NormSet(*x_la[j][i]));//,Range("cut"));
    double ibkgf = ibkg->getVal();
    double bkgfe = polysig_la[j][i]->getError();
    double isig1f = isig1->getVal();
    double isig2f = isig2->getVal();
    double bkgy = ibkgf*bkgf;
    double bkgye = ibkgf*bkgfe;
    double sigyh  = totyh - bkgy;
    double sigyhe = sqrt(totyhe*totyhe+bkgye*bkgye); 
    double sigy1  = isig1f *sigf1 ;
    double sigy2  = isig2f *sigf2 ;
    double sigy  = sigy1  + sigy2 ;

    if(i<=1)
    {
      hYieldReco_la->SetBinContent(j+1,i+1,0);
      hYieldReco_la->SetBinError(j+1,i+1,0);
      hYieldRecoFit_la->SetBinContent(j+1,i+1,0);
      hYieldRecoFit_la->SetBinError(j+1,i+1,0);
    }
    else
    {
      hYieldReco_la->SetBinContent(j+1,i+1,sigyh/ptbinwidth[i]);
      hYieldReco_la->SetBinError(j+1,i+1,sigyhe/ptbinwidth[i]);
      hYieldRecoFit_la->SetBinContent(j+1,i+1,1,sigy/ptbinwidth[i]);
      hYieldRecoFit_la->SetBinError(j+1,i+1,sigyhe/ptbinwidth[i]);
    }

    x_ks[j][i] = new RooRealVar(Form("x_ks_eta%d_%d",j+1,i),"mass",0.44,0.56);
    data_ks[j][i] = new RooDataHist(Form("data_ks_eta%d_%d",j+1,i),"dataset",*x_ks[j][i],ksmassall[j][i]);
    xframe_ks[j][i] = x_ks[j][i]->frame(80);
    data_ks[j][i]->plotOn(xframe_ks[j][i],Name(Form("data_ks_eta%d_%d",j+1,i)));
    mean_ks[j][i] = new RooRealVar(Form("mean_ks_eta%d_%d",j+1,i),"mean",0.50,0.49,0.51);
    sigma1_ks[j][i] = new RooRealVar(Form("sigma1_ks_eta%d_%d",j+1,i),"sigma1",0.01,0.001,0.02);
    sigma2_ks[j][i] = new RooRealVar(Form("sigma2_ks_eta%d_%d",j+1,i),"sigma2",0.01,0.001,0.02);
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
//    double totyh  = ksmassall[j][i]->Integral(nmin,nmax);
    l1_ks[j][i] = new TLine(massmin ,0,massmin ,500);
    l2_ks[j][i] = new TLine(massmax ,0,massmax ,500);
    x_ks[j][i]->setRange("cut",massmin ,massmax );
    RooAbsReal* ibkg  = poly_ks[j][i]->createIntegral(*x_ks[j][i],NormSet(*x_ks[j][i]),Range("cut"));
    RooAbsReal* isig1  = gaus1_ks[j][i]->createIntegral(*x_ks[j][i],NormSet(*x_ks[j][i]));//,Range("cut"));
    RooAbsReal* isig2  = gaus2_ks[j][i]->createIntegral(*x_ks[j][i],NormSet(*x_ks[j][i]));//,Range("cut"));
    double ibkgf = ibkg->getVal();
    double bkgfe = polysig_ks[j][i]->getError();
    double isig1f = isig1->getVal();
    double isig2f = isig2->getVal();
    double bkgy = ibkgf*bkgf ;
    double bkgye = ibkgf*bkgfe ;
    double sigyh  = totyh - bkgy;
    double sigyhe = sqrt(totyhe*totyhe+bkgye*bkgye);
    double sigy1  = isig1f *sigf1 ;
    double sigy2  = isig2f *sigf2 ;
    double sigy  = sigy1  + sigy2 ;
    
    if(i==0)
    {
      hYieldReco_ks->SetBinContent(j+1,i+1,0);
      hYieldReco_ks->SetBinError(j+1,i+1,0);
      hYieldRecoFit_ks->SetBinContent(j+1,i+1,0);
      hYieldRecoFit_ks->SetBinError(j+1,i+1,0);
    }
    else
    {
      hYieldReco_ks->SetBinContent(j+1,i+1,sigyh/ptbinwidth[i]);
      hYieldReco_ks->SetBinError(j+1,i+1,sigyhe/ptbinwidth[i]);
      hYieldRecoFit_ks->SetBinContent(j+1,i+1,sigy/ptbinwidth[i]);
      hYieldRecoFit_ks->SetBinError(j+1,i+1,sigyhe/ptbinwidth[i]);
    }
   }
  }

  for(int i=0;i<7;i++)
  {
    hYieldRecoPt_ks[i] = hYieldReco_ks->ProjectionY(Form("ks_%d",i),i+1,i+1,"e");
    hYieldRecoPt_la[i] = hYieldReco_la->ProjectionY(Form("la_%d",i),i+1,i+1,"e");
    hYieldRecoFitPt_ks[i] = hYieldRecoFit_ks->ProjectionY(Form("ksFit_%d",i),i+1,i+1,"e");
    hYieldRecoFitPt_la[i] = hYieldRecoFit_la->ProjectionY(Form("laFit_%d",i),i+1,i+1,"e");
  }

  TH1D* hKsGoodPt = (TH1D*)hYieldRecoPt_ks[6]->Clone("ksGoodPt");
  TH1D* hLamGoodPt = (TH1D*)hYieldRecoPt_la[6]->Clone("lamGoodPt");
  hKsGoodPt->Reset();
  hLamGoodPt->Reset();

  for(int i=0;i<17;i++)
  { 
    ksmassgoodsum[i] = ksmassptgoodsum->ProjectionY(Form("ksMassGood_%d",i),nptbins[i]+1,nptbins[i+1],"e");
    lamassgoodsum[i] = lamassptgoodsum->ProjectionY(Form("lamMassGood_%d",i),nptbins[i]+1,nptbins[i+1],"e");
    hKsGoodPt->SetBinContent(i+1,ksmassgoodsum[i]->Integral()/ptbinwidth[i]);
    hLamGoodPt->SetBinContent(i+1,lamassgoodsum[i]->Integral()/ptbinwidth[i]);
    ksmassgoodsum[i]->SetMarkerColor(4);
    lamassgoodsum[i]->SetMarkerColor(4);
  } 

  // taking two sigmas
  hKsGoodPt->Scale(0.94); 
  hYieldRecoFitPt_ks[6]->Scale(0.9545);
  hLamGoodPt->Scale(0.94);  
  hYieldRecoFitPt_la[6]->Scale(0.9545);

  TCanvas* a = new TCanvas("a","a",800,800);  
  a->Divide(2,2);
  a->cd(1);
  a->GetPad(1)->SetLogy();
  hYieldRecoFitPt_ks[6]->SetMarkerColor(4);
  hYieldRecoPt_ks[6]->SetMarkerColor(2);
  hKsGoodPt->SetTitle("K^{0}_{s} yields;p_{T} (GeV/c);dN^{V^{0}}/dp_{T} (GeV^{-1})");
  hKsGoodPt->GetXaxis()->CenterTitle();
  hKsGoodPt->GetYaxis()->CenterTitle();
  hKsGoodPt->GetYaxis()->SetTitleOffset(1.5*hKsGoodPt->GetYaxis()->GetTitleOffset());
  hKsGoodPt->SetMaximum(hKsGoodPt->GetMaximum()*3);
  hKsGoodPt->Draw("PE");
  hYieldRecoFitPt_ks[6]->Draw("PESAME");
  hYieldRecoPt_ks[6]->Draw("PESAME");
  TLegend* legend = new TLegend(0.3,0.75,0.9,0.9);
  legend->SetFillColor(0);
  legend->SetFillStyle(0);
  legend->AddEntry(hYieldRecoPt_ks[6],"Yield from counting as in the data","P");
  legend->AddEntry(hKsGoodPt,"Yield from matching","P");
  legend->AddEntry(hYieldRecoFitPt_ks[6],"Yield under the fitted Gaussian","P");
  legend->Draw();
  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->DrawLatex(0.2,0.2,"HIJING pPb MC 5.02 TeV");
  a->cd(2);
  a->GetPad(2)->SetLogy();
  hYieldRecoFitPt_la[6]->SetMarkerColor(4);
  hYieldRecoPt_la[6]->SetMarkerColor(2);
  hLamGoodPt->SetTitle("#Lambda yields;p_{T} (GeV/c);dN^{V^{0}}/dp_{T} (GeV^{-1})");
  hLamGoodPt->GetYaxis()->CenterTitle();
  hLamGoodPt->GetXaxis()->CenterTitle();
  hLamGoodPt->GetYaxis()->SetTitleOffset(1.5*hLamGoodPt->GetYaxis()->GetTitleOffset());
  hLamGoodPt->SetMaximum(hLamGoodPt->GetMaximum()*3);
  hLamGoodPt->Draw("PE");
  hYieldRecoFitPt_la[6]->Draw("PESAME");
  hYieldRecoPt_la[6]->Draw("PESAME");
  a->cd(3);
  TH1D* hYieldRecoFitPt_ks6_ratio = hYieldRecoFitPt_ks[6]->Clone("ratiofit_ks");
  TH1D* hYieldRecoPt_ks6_ratio = hYieldRecoPt_ks[6]->Clone("ratio_ks");
  hYieldRecoFitPt_ks6_ratio->Divide(hKsGoodPt);
  hYieldRecoPt_ks6_ratio->Divide(hKsGoodPt);
  hYieldRecoFitPt_ks6_ratio->SetAxisRange(0.8,1.1,"Y");
  hYieldRecoPt_ks6_ratio->SetAxisRange(0.8,1.1,"Y");
  hYieldRecoFitPt_ks6_ratio->SetTitle("K^{0}_{s} ratios;p_{T} (GeV/c);Ratio");
  hYieldRecoFitPt_ks6_ratio->GetYaxis()->CenterTitle();
  hYieldRecoFitPt_ks6_ratio->GetXaxis()->CenterTitle();
  hYieldRecoFitPt_ks6_ratio->Draw("PE");
  hYieldRecoPt_ks6_ratio->Draw("PESAME");
  TLegend* legend1 = new TLegend(0.3,0.75,0.9,0.9);
  legend1->SetFillColor(0);
  legend1->AddEntry(hYieldRecoFitPt_ks6_ratio,"Fitted/Matched","P");
  legend1->AddEntry(hYieldRecoPt_ks6_ratio,"Counted/Matched","P");
  legend1->Draw();
  a->cd(4);
  TH1D* hYieldRecoFitPt_la6_ratio = hYieldRecoFitPt_la[6]->Clone("ratiofit_la");
  TH1D* hYieldRecoPt_la6_ratio = hYieldRecoPt_la[6]->Clone("ratio_la");
  hYieldRecoFitPt_la6_ratio->Divide(hLamGoodPt);
  hYieldRecoPt_la6_ratio->Divide(hLamGoodPt);
  hYieldRecoFitPt_la6_ratio->SetTitle("#Lambda ratios;p_{T} (GeV/c);Ratio");
  hYieldRecoFitPt_la6_ratio->SetAxisRange(0.8,1.1,"Y");
  hYieldRecoPt_la6_ratio->SetAxisRange(0.8,1.1,"Y");
  hYieldRecoFitPt_la6_ratio->GetYaxis()->CenterTitle();
  hYieldRecoFitPt_la6_ratio->GetXaxis()->CenterTitle();
  hYieldRecoFitPt_la6_ratio->Draw("PE");
  hYieldRecoPt_la6_ratio->Draw("PESAME");
  SaveCanvas(a,"HI/V0","YieldAndRatioComp_Hijing");

/*
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
*/
  TCanvas* c2all = new TCanvas("c2all","c2all",1200,700);
  c2all->Divide(5,3);
  for(int i=1;i<15;i++)
  {
    c2all->cd(i+1);
    ksmassall[6][i]->Draw("PE");
    ksmassgoodsum[i]->Draw("PESAME");
    xframe_ks[6][i]->Draw("SAME");
    l1_ks[6][i]->Draw("Lsame");
    l2_ks[6][i]->Draw("Lsame");
  }

  TCanvas* c3all = new TCanvas("c3all","c3all",1200,700);
  c3all->Divide(5,3);
  for(int i=2;i<15;i++)
  {
    c3all->cd(i+1);
    lamassall[6][i]->Draw("PE");
    lamassgoodsum[i]->Draw("PESAME");
    xframe_la[6][i]->Draw("SAME");
    l1_la[6][i]->Draw("Lsame");
    l2_la[6][i]->Draw("Lsame");
  }

/*
  TCanvas* c2 = new TCanvas("c2","c2",1000,800);
  c2->Divide(5,4);
  for(int i=0;i<17;i++) 
  {
    c2->cd(i+1);
    ksmassall[0][i]->Draw("PE");
    xframe_ks[0][i]->Draw("SAME");
    l1_ks[0][i]->Draw("Lsame");
    l2_ks[0][i]->Draw("Lsame");
  }

  TCanvas* c3 = new TCanvas("c3","c3",1000,800);
  c3->Divide(5,4);
  for(int i=0;i<17;i++) 
  {
    c3->cd(i+1);
    lamassall[0][i]->Draw("PE");
    xframe_la[0][i]->Draw("SAME");
    l1_la[0][i]->Draw("Lsame");
    l2_la[0][i]->Draw("Lsame");
  }

  TCanvas* c222222 = new TCanvas("c222222","c222222",1000,800);
  c222222->Divide(5,4);
  for(int i=0;i<17;i++)
  {
    c222222->cd(i+1);
    ksmassall[1][i]->Draw("PE");
    xframe_ks[1][i]->Draw("SAME");
    l1_ks[1][i]->Draw("Lsame");
    l2_ks[1][i]->Draw("Lsame");
  }

  TCanvas* c333333 = new TCanvas("c333333","c333333",1000,800);
  c333333->Divide(5,4);
  for(int i=0;i<17;i++)
  {
    c333333->cd(i+1);
    lamassall[1][i]->Draw("PE");
    xframe_la[1][i]->Draw("SAME");
    l1_la[1][i]->Draw("Lsame");
    l2_la[1][i]->Draw("Lsame");
  }

  TCanvas* c22 = new TCanvas("c22","c22",1000,800);
  c22->Divide(5,4);
  for(int i=0;i<17;i++)
  {
    c22->cd(i+1);
    ksmassall[2][i]->Draw("PE");
    xframe_ks[2][i]->Draw("SAME");
    l1_ks[2][i]->Draw("Lsame");
    l2_ks[2][i]->Draw("Lsame");
  }

  TCanvas* c33 = new TCanvas("c33","c33",1000,800);
  c33->Divide(5,4);
  for(int i=0;i<17;i++)
  {
    c33->cd(i+1);
    lamassall[2][i]->Draw("PE");
    xframe_la[2][i]->Draw("SAME");
    l1_la[2][i]->Draw("Lsame");
    l2_la[2][i]->Draw("Lsame");
  }

  TCanvas* c222 = new TCanvas("c222","c222",1000,800);
  c222->Divide(5,4);
  for(int i=0;i<17;i++)
  {
    c222->cd(i+1);
    ksmassall[3][i]->Draw("PE");
    xframe_ks[3][i]->Draw("SAME");
    l1_ks[3][i]->Draw("Lsame");
    l2_ks[3][i]->Draw("Lsame");
  }

  TCanvas* c333 = new TCanvas("c333","c333",1000,800);
  c333->Divide(5,4);
  for(int i=0;i<17;i++)
  {
    c333->cd(i+1);
    lamassall[3][i]->Draw("PE");
    xframe_la[3][i]->Draw("SAME");
    l1_la[3][i]->Draw("Lsame");
    l2_la[3][i]->Draw("Lsame");
  }

  TCanvas* c2222 = new TCanvas("c2222","c2222",1000,800);
  c2222->Divide(5,4);
  for(int i=0;i<17;i++)
  {
    c2222->cd(i+1);
    ksmassall[4][i]->Draw("PE");
    xframe_ks[4][i]->Draw("SAME");
    l1_ks[4][i]->Draw("Lsame");
    l2_ks[4][i]->Draw("Lsame");
  }

  TCanvas* c3333 = new TCanvas("c3333","c3333",1000,800);
  c3333->Divide(5,4);
  for(int i=0;i<17;i++)
  {
    c3333->cd(i+1);
    lamassall[4][i]->Draw("PE");
    xframe_la[4][i]->Draw("SAME");
    l1_la[4][i]->Draw("Lsame");
    l2_la[4][i]->Draw("Lsame");
  }

  TCanvas* c22222 = new TCanvas("c22222","c22222",1000,800);
  c22222->Divide(5,4);
  for(int i=0;i<17;i++)
  {
    c22222->cd(i+1);
    ksmassall[5][i]->Draw("PE");
    xframe_ks[5][i]->Draw("SAME");
    l1_ks[5][i]->Draw("Lsame");
    l2_ks[5][i]->Draw("Lsame");
  }

  TCanvas* c33333 = new TCanvas("c33333","c33333",1000,800);
  c33333->Divide(5,4);
  for(int i=0;i<17;i++)
  {
    c33333->cd(i+1);
    lamassall[5][i]->Draw("PE");
    xframe_la[5][i]->Draw("SAME");
    l1_la[5][i]->Draw("Lsame");
    l2_la[5][i]->Draw("Lsame");
  }
*/
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
  hYieldReco_la_ratio->SetAxisRange(0.2,10.0,"Y");
  hYieldReco_la_ratio->Draw("lego2");  

  TH2D* hYieldReco_ks_ratio = (TH2D*)hYieldReco_ks->Clone("hYieldReco_ks_ratio");
  hYieldReco_ks_ratio->Divide(hYieldGen_ks);
  TCanvas* c5 = new TCanvas("c5","c5",550,500);
  hYieldReco_ks_ratio->SetAxisRange(0,1.0,"Z");
  hYieldReco_ks_ratio->SetAxisRange(0.2,10.0,"Y");
  hYieldReco_ks_ratio->Draw("lego2");

  TCanvas* c10 = new TCanvas("c10","c10",900,600);
  c10->Divide(3,2);
  TCanvas* c11 = new TCanvas("c11","c11",900,600);
  c11->Divide(3,2);

  TH1D* hEffvsPt_ks[7];
  TH1D* hEffvsPt_la[7];
  for(int i=0;i<7;i++)
  {
    c10->cd(i+1);
    hEffvsPt_ks[i] = hYieldReco_ks_ratio->ProjectionY(Form("effvspt_ks_%d",i+1),i+1,i+1,"e");
    hEffvsPt_ks[i]->Draw("PE");

    c11->cd(i+1);
    hEffvsPt_la[i] = hYieldReco_la_ratio->ProjectionY(Form("effvspt_la_%d",i+1),i+1,i+1,"e");
    hEffvsPt_la[i]->Draw("PE");
  }
return;
  TFile* fout = new TFile("V0Eff_counting_2M.root","recreate");
  hYieldReco_la_ratio->SetDirectory(0);
  hYieldReco_ks_ratio->SetDirectory(0);
  hYieldReco_la_ratio->Write();
  hYieldReco_ks_ratio->Write();
  fout->Close();

//  SaveCanvas(c,"HI/V0","ksmassfake");
//  SaveCanvas(c1,"HI/V0","lammassfake");
//  SaveCanvas(c2,"HI/V0","ksmassgood");
//  SaveCanvas(c3,"HI/V0","lammassgood");
}
