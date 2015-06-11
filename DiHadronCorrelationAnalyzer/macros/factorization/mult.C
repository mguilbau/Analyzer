void mult()
{
  //TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_UCC2011_pixeltracks_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin500_centmax1000.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_UCC2011_pixeltracks_INCLMULTUCC010_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");

  TNtuple* h = (TNtuple*)f->Get("higeninfontuple");
 
  TH1D* hMultAll = new TH1D("hMultAll",";nMult",300,0,6000); 
  TH1D* hMult = new TH1D("hMult",";nMult",300,0,6000);
  TH1D* hMult010 = new TH1D("hMult010",";nMult",300,0,6000);
  TH1D* hMult001 = new TH1D("hMult001",";nMult",300,0,6000);

  higeninfontuple->Draw("nmult>>hMultAll","","GOFF");
  higeninfontuple->Draw("nmult>>hMult","(7.0*hft+zdc)<36000","GOFF");
  higeninfontuple->Draw("nmult>>hMult010","(7.0*hft+zdc)<36000 && npixel>51400 && hft>3260","GOFF");
  higeninfontuple->Draw("nmult>>hMult001","(7.0*hft+zdc)<36000 && npixel>53450 && hft>3393","GOFF");

  hMult->SetMarkerColor(kRed);
  hMult010->SetMarkerColor(kBlue);
  hMult001->SetMarkerColor(kGreen);

  TCanvas* c = new TCanvas("c","c",550,500);
  c->SetLogy();
  hMultAll->Draw("PE");
  hMult->Draw("PESAME");
  hMult010->Draw("PESAME");
  hMult001->Draw("PESAME");
}
