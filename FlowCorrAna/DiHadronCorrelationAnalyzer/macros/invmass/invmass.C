#define PI 3.141593

void invmass()
{
  using namespace RooFit;

//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HijingReco_Minbias_5TeV/merged/invmassk0spi_hijing_diff.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/invmassk0spi_all_hm220260_diff.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/invmassk0spi_all_mb2040_diff.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_16_correlations/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/invmass.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HijingReco_Minbias_5TeV/merged/invmassk0spi_10M_diff.root");

  TH2D* hsignal = f->Get("invmass_ana/invmassvspt_signal");
  TH2D* hback = f->Get("invmass_ana/invmassvspt_background");
  TH1D* hmult = f->Get("invmass_ana/multrawall");
  int nevents = hmult->Integral();

  TFile* feff = new TFile("efficiency.root");
  TGraphErrors* heff = (TGraphErrors*)feff->Get("eff");

  double ptbins[]={1.0,1.2,1.6,2.0,2.4,3.0,3.6,4.2,5.0,8.0};
  double ptmean[]={1.1,1.4,1.8,2.2,2.7,3.3,3.9,4.6,6.5};
  double ptmean_err[9]={0};
  double yield[9];
  double yield_err[9];

  TH1D* hsignal_1D[10];
  TH1D* hback_1D[10];
  TH1D* hsignal_sub_1D[10];

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
 
  TF1* fit[30];
  TF1* fit_gaus[30];
  TF1* fit_pol[30];

  for(int i=0;i<9;i++)
  {
    int ibinmin = hsignal->GetXaxis()->FindBin(ptbins[i]);
    int ibinmax = hsignal->GetXaxis()->FindBin(ptbins[i+1]-0.00001);
    double width = ptbins[i+1]-ptbins[i];

    hsignal_1D[i] = hsignal->ProjectionY(Form("hsignal_%d",ibinmin),ibinmin,ibinmax,"e");
    hback_1D[i] = hback->ProjectionY(Form("hback_%d",ibinmin),ibinmin,ibinmax,"e");
    hback_1D[i]->Scale(0.2*1.);
    hsignal_1D[i]->Rebin(5);
    hback_1D[i]->Rebin(5);
    hsignal_1D[i]->SetMarkerColor(2);
    hsignal_1D[i]->SetMarkerStyle(20);
    hback_1D[i]->SetMarkerStyle(20);

    hsignal_sub_1D[i] = (TH1D*)hsignal_1D[i]->Clone(Form("hsignal_sub_%d",i));
    hsignal_sub_1D[i]->Add(hback_1D[i],-1.0);

//    fit_gaus[i] = new TF1(Form("fit_gaus_%d",i),"[0]/sqrt(2*TMath::Pi())/[2]*TMath::Exp(-0.5*(x-[1])*(x-[1])/[2]/[2])+[3]*TMath::Exp(-0.5*(x-[1])*(x-[1])/[4]/[4])",0.6-0.37,1.2-0.65);  
//    fit_gaus[i] = new TF1(Form("fit_gaus_%d",i),"[0]*TMath::BreitWigner(x,[1],[2])+[3]*[4]",0.6-0.37,1.2-0.65);
    fit_gaus[i] = new TF1(Form("fit_gaus_%d",i),"[0]*TMath::Voigt(x-[1],[2],[4])+[3]",0.6-0.37,1.2-0.65);
    fit_pol[i] = new TF1(Form("fit_pol_%d",i),"[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x",0.6-0.37,1.2-0.65);
   fit[i] = new TF1(Form("fit_%d",i),Form("fit_gaus_%d+fit_pol_%d",i,i),0.24,0.6);
   fit[i]->SetParameters(20000,0.39,0.02,0.0,0.007,10000,-10000,0,0,0,0);
   fit[i]->FixParameter(3,0);
   fit[i]->FixParameter(10,0);
   fit[i]->FixParameter(9,0);
//   fit[i]->FixParameter(8,0);
   fit[i]->SetParLimits(0,0,10000000);
// gaussian
//    fit[i]->SetParLimits(1,0.39,0.394);
//    fit[i]->SetParLimits(2,0.014,0.027);
// breit-weigner
//    fit[i]->SetParLimits(1,0.387,0.396);
//    fit[i]->SetParLimits(2,0.007,0.04);
// voigt 
    fit[i]->SetParLimits(1,0.390,0.4);
    fit[i]->SetParLimits(2,0.003,0.01);
    fit[i]->SetParLimits(4,0.03,0.07);

//    hsignal_sub_1D[i]->Fit(Form("fit_%d",i),"RNO");
    hsignal_1D[i]->Fit(Form("fit_%d",i),"RNO");
    hsignal_1D[i]->Fit(Form("fit_%d",i),"RNO");
    hsignal_1D[i]->Fit(Form("fit_%d",i),"RNO");
    hsignal_1D[i]->Fit(Form("fit_%d",i),"RNO");
    hsignal_1D[i]->Fit(Form("fit_%d",i),"RNO");
    hsignal_1D[i]->Fit(Form("fit_%d",i),"RNO");
 
    fit_gaus[i]->SetParameters(fit[i]->GetParameters());

    double eff=0;
    double xx=0;
    heff->GetPoint(i,xx,eff);

    yield[i]=fit[i]->GetParameter(0)/width/nevents/ptmean[i]/2/PI/4.8/eff;
    yield_err[i]=fit[i]->GetParError(0)/width/nevents/ptmean[i]/2/PI/4.8/eff;
   
/*
    x[i] = new RooRealVar(Form("x_%d",i),"mass",0.395-0.15,0.395+0.2);
    data[i] = new RooDataHist(Form("data_%d",i),"dataset",*x[i],hsignal_sub_1D[i]);
    xframe[i] = x[i]->frame(80);
    data[i]->plotOn(xframe[i],Name(Form("data_%d",i)));
    mean[i] = new RooRealVar(Form("mean_%d",i),"mean",0.395,0.395-0.15,0.395+0.15);
    sigma1[i] = new RooRealVar(Form("sigma1_%d",i),"sigma1",0.040,0.010,0.070);
    sig1[i] = new RooRealVar(Form("sig1_%d",i),"signal1",10000,0,100000);
    a[i] = new RooRealVar(Form("a_%d",i),"a",-1,-10000,10000);
    b[i] = new RooRealVar(Form("b_%d",i),"b",0,-10000,10000);
    cp[i] = new RooRealVar(Form("cp_%d",i),"cp",0,-10000,10000);
    d[i] = new RooRealVar(Form("d_%d",i),"d",0,-10000,10000);
    gaus1[i] = new RooGaussian(Form("gaus1_%d",i),"gaus1",*x[i],*mean[i],*sigma1[i]);
//    gaus1[i] = new RooBreitWigner(Form("gaus1_%d",i),"gaus1",*x[i],*mean[i],*sigma1[i]);
    poly[i] = new RooPolynomial(Form("poly_%d",i),"poly",*x[i],RooArgList(*a[i],*b[i],*cp[i],*d[i]));
    polysig[i] = new RooRealVar(Form("polysig_%d",i),"polysig",10,0,1000000);
    sum[i] = new RooAddPdf(Form("sum_%d",i),Form("sum_%d",i),RooArgList(*gaus1[i],*poly[i]),RooArgList(*sig1[i],*polysig[i]));

    x[i]->setRange("cut",0.6-0.37,1.2-0.65);
    sum[i]->fitTo(*data[i],Range("cut"));
    sum[i]->fitTo(*data[i],Range("cut"));
    sum[i]->fitTo(*data[i],Range("cut"));
    sum[i]->plotOn(xframe[i],Name(Form("sum_%d",i)));
    sum[i]->plotOn(xframe[i],Components(*poly[i]),LineStyle(kDashed));
    sum[i]->plotOn(xframe[i],Components(*gaus1[i]),LineStyle(kSolid));
*/
  }
  
  TGraphErrors* gr = new TGraphErrors(9,ptmean,yield,ptmean_err,yield_err);    

  TCanvas* c = new TCanvas("c","c",900,900);
  c->Divide(3,3);
  for(int i=0;i<9;i++)
  {
    c->cd(i+1);
    hsignal_1D[i]->SetAxisRange(0.24,0.85,"X");
    hsignal_1D[i]->Draw("PE");
    fit[i]->Draw("Lsame");
//    xframe[i]->Draw("same");
//    hback_1D[i]->Draw("PESAME");
    fit_gaus[i]->SetLineColor(4);
    fit_gaus[i]->Draw("Lsame");    
  }

  TCanvas* c1 = new TCanvas("c1","c1",900,900);
  c1->Divide(3,3);
  for(int i=0;i<9;i++)
  {
    c1->cd(i+1);
    hsignal_sub_1D[i]->SetAxisRange(0.24,0.85,"X");
    hsignal_sub_1D[i]->Draw("PE");
    fit[i]->Draw("Lsame");
    fit_gaus[i]->SetLineColor(4);
    fit_gaus[i]->Draw("Lsame");
//    xframe[i]->Draw("same");
  }

  TCanvas* c2 = new TCanvas("c2","c2",500,500);
  c2->SetLogy();
  TH2D* htmp = new TH2D("htmp",";p_{T} (GeV/c);Yield",100,0,10,100,0.000000001,10);
  htmp->Draw();
  gr->SetMarkerColor(2);
  gr->Draw("PESAME");
  TF1* fitfunc = new TF1("fitfunc","[1]*TMath::Exp(-x/[0])",0.8,4);
  fitfunc->SetParameters(1,0.6);
  gr->Fit("fitfunc","RNO");
  fitfunc->Draw("LSAME");

  TFile* fout = new TFile("output_hm220260.root","recreate");
  gr->Write("yield");
  fout->Close();
}
