void cme1()
{
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_norecenter_eff0_bin03_v18.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_eff0_bin03_v20.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_20/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/chargedepcorr.root");  
  TH2D* hsame = (TH2D*)f->Get("chargedepcorr_ana_HI/signalcos_same_for_trg0_ass0");
  TH2D* hdiff = (TH2D*)f->Get("chargedepcorr_ana_HI/signalcos_diff_for_trg0_ass0");
  TH1D* hq2 = (TH1D*)f->Get("chargedepcorr_ana_HI/q2asscos");

  TH1D* hsame_prof_for = (TH1D*)hsame->ProfileY("hsame_prof_for",-1,-1,"e");
  TH1D* hdiff_prof_for = (TH1D*)hdiff->ProfileY("hdiff_prof_for",-1,-1,"e");

  hsame_prof_for->Scale(1.0/sqrt(hq2->GetMean())); 
  hdiff_prof_for->Scale(1.0/sqrt(hq2->GetMean()));

  TH2D* htmp = new TH2D("tmp","",1000,0.15,4.8,1000,-0.01,0.01);

  TCanvas* c = new TCanvas("c","c",550,500);
  htmp->Draw();
  hsame_prof_for->SetMarkerStyle(20);
  hdiff_prof_for->SetMarkerStyle(25);
  hsame_prof_for->Draw("PESAME");
  hdiff_prof_for->Draw("PESAME");

  TH1D* h = hsame_prof_for->Clone("h");
  h->Add(hdiff_prof_for,-1);

  TCanvas* c1 = new TCanvas("c1","c1",550,500);
  htmp->Draw();
  h->Draw("PESAME");
}
