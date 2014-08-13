void invmass()
{
  using namespace RooFit;

//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HijingReco_Minbias_5TeV/merged/invmassk0spi_hijing_diff.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/invmassk0spi_all_hm185220_diff.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/invmassk0spi_promptreco_reverse_mb035_diff_new.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_16_correlations/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/invmass.root");
  TH2D* hsignal = f->Get("invmass_ana/invmassvspt_signal");
  TH2D* hback = f->Get("invmass_ana/invmassvspt_background");

  double ptbins[]={0.8,0.9,1.0,1.1,1.2,2.0,4.0,6.0,10.0};
  TH1D* hsignal_1D[10];
  TH1D* hback_1D[10];

  RooRealVar *x[30];
  RooDataHist *data[30];
  RooPlot *xframe[30];
  RooRealVar *mean[30];
  RooRealVar *sigma1[30];
  RooRealVar *sig1[30];
  RooRealVar *a[30];
  RooRealVar *b[30];
  RooRealVar *cp[30];
  RooRealVar *d[30];
  RooGaussian *gaus1[30];
//  RooBreitWigner *gaus1[30];
  RooPolynomial *poly[30];
  RooRealVar *polysig[30];
  RooAddPdf *sum[30];
 
  for(int i=0;i<7;i++)
  {
    int ibinmin = hsignal->GetXaxis()->FindBin(ptbins[i]);
    int ibinmax = hsignal->GetXaxis()->FindBin(ptbins[i+1]-0.00001);

    hsignal_1D[i] = hsignal->ProjectionY(Form("hsignal_%d",ibinmin),ibinmin,ibinmax,"e");
    hback_1D[i] = hback->ProjectionY(Form("hback_%d",ibinmin),ibinmin,ibinmax,"e");
    hback_1D[i]->Scale(0.2*1.);
    hsignal_1D[i]->Rebin(5);
    hback_1D[i]->Rebin(5);
    hsignal_1D[i]->SetMarkerColor(2);
    hsignal_1D[i]->SetMarkerStyle(20);
    hback_1D[i]->SetMarkerStyle(20);

    x[i] = new RooRealVar(Form("x_%d",i),"mass",0.395-0.15,0.395+0.4);
    data[i] = new RooDataHist(Form("data_%d",i),"dataset",*x[i],hsignal_1D[i]);
    xframe[i] = x[i]->frame(80);
    data[i]->plotOn(xframe[i],Name(Form("data_%d",i)));
    mean[i] = new RooRealVar(Form("mean_%d",i),"mean",0.395,0.395-0.05,0.395+0.05);
    sigma1[i] = new RooRealVar(Form("sigma1_%d",i),"sigma1",0.020,0.010,0.050);
    sig1[i] = new RooRealVar(Form("sig1_%d",i),"signal1",10,0,1000000000);
    a[i] = new RooRealVar(Form("a_%d",i),"a",0,-1000000,1000000);
    b[i] = new RooRealVar(Form("b_%d",i),"b",0,-1000000,1000000);
    cp[i] = new RooRealVar(Form("cp_%d",i),"cp",0,-1000000,1000000);
    d[i] = new RooRealVar(Form("d_%d",i),"d",0,-1000000,1000000);
    gaus1[i] = new RooGaussian(Form("gaus1_%d",i),"gaus1",*x[i],*mean[i],*sigma1[i]);
//    gaus1[i] = new RooBreitWigner(Form("gaus1_%d",i),"gaus1",*x[i],*mean[i],*sigma1[i]);
    poly[i] = new RooPolynomial(Form("poly_%d",i),"poly",*x[i],RooArgList(*a[i],*b[i],*cp[i],*d[i]));
    polysig[i] = new RooRealVar(Form("polysig_%d",i),"polysig",10,0,1000000000);
    sum[i] = new RooAddPdf(Form("sum_%d",i),"sum",RooArgList(*gaus1[i],*poly[i]),RooArgList(*sig1[i],*polysig[i]));
    sum[i]->fitTo(*data[i]);
    sum[i]->fitTo(*data[i]);
    sum[i]->fitTo(*data[i]);
    sum[i]->plotOn(xframe[i],Name(Form("sum_%d",i)));
    sum[i]->plotOn(xframe[i],Components(*poly[i]),LineStyle(kDashed));
    sum[i]->plotOn(xframe[i],Components(*gaus1[i]),LineStyle(kSolid));
  }
  
  TCanvas* c = new TCanvas("c","c",900,900);
  c->Divide(3,3);
  for(int i=0;i<7;i++)
  {
    c->cd(i+1);
    hsignal_1D[i]->SetAxisRange(0.6-0.4,1.2-0.4,"X");
    hsignal_1D[i]->Draw("PE");
    xframe[i]->Draw("");
//    hback_1D[i]->Draw("PESAME");
  }
return;
  TCanvas* c1 = new TCanvas("c1","c1",900,900);
  c1->Divide(3,3);
  TH1D* hsignal_sub_1D[10];
  for(int i=0;i<7;i++)
  {
    c1->cd(i+1);
    hsignal_sub_1D[i] = (TH1D*)hsignal_1D[i]->Clone(Form("hsignal_sub_%d",i));
    hsignal_sub_1D[i]->Add(hback_1D[i],-1);
    hsignal_sub_1D[i]->Draw("PE");
  }
}
