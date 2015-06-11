void dNdetadphi()
{
//  TFile* f = new TFile("/export/d00/scratch/davidlw/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent4050_pttrg033_ptassallweight_etaass445_eff0_bin03_v30.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_20/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/chargedepcorr_recenter.root");

  TH2D* dNdetadphi_pos = (TH2D*)f->Get("chargedepcorr_ana_HI/dndetadphipos");
  TH2D* dNdetadphi_neg = (TH2D*)f->Get("chargedepcorr_ana_HI/dndetadphineg");

  TH1D* dNdphi_pos[24];
  TH1D* dNdphi_neg[24];

  for(int i=0;i<24;i++)
  {
    dNdphi_pos[i] = (TH1D*)dNdetadphi_pos->ProjectionY(Form("dNdphi_pos_%d",i+1),i+1,i+1,"e");
    dNdphi_neg[i] = (TH1D*)dNdetadphi_neg->ProjectionY(Form("dNdphi_neg_%d",i+1),i+1,i+1,"e");
  }

  TCanvas* c = new TCanvas("c","c",1100,900);
  c->Divide(6,4);

  TCanvas* c1 = new TCanvas("c1","c1",1100,900);
  c1->Divide(6,4);

  for(int i=0;i<24;i++)
  {
    c->cd(i+1);
    dNdphi_pos[i]->Rebin(8);
    dNdphi_pos[i]->Scale(1.0/dNdphi_pos[i]->Integral()*dNdphi_pos[i]->GetNbinsX());
    dNdphi_pos[i]->SetMinimum(0);
    dNdphi_pos[i]->SetMaximum(1.2);
    dNdphi_pos[i]->Draw();
    c1->cd(i+1);
    dNdphi_neg[i]->Rebin(8);
    dNdphi_neg[i]->Scale(1.0/dNdphi_neg[i]->Integral()*dNdphi_neg[i]->GetNbinsX());
    dNdphi_neg[i]->SetMinimum(0);
    dNdphi_neg[i]->SetMaximum(1.2);
    dNdphi_neg[i]->Draw();
  }
//  TH1D* 
}
