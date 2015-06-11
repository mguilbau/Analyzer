void recenter_new()
{
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_recenter_cent002_pttrg033_ptassallweight_etaass445_eff1_bin01_v42.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_20/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/chargedepcorr_recenter.root");
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/chargedepcorr_recenter_n260_pttrg033_ptassallweight_etaass445_all_eff1_zvtx1_bin01_v13.root");

  const int MAXETATRGBINSPT = 48;
  const int MAXZVTXBIN = 30;

//  TString dirname("chargedepcorr_ana_HI");
  TString dirname("chargedepcorr_ana_pPb");

  double small = 0.000;
  std::vector<double> multBins;
/*
  for(double mult = 0; mult < 10; mult += 1) multBins.push_back(mult);
  for(double mult = 10; mult < 50; mult += 4) multBins.push_back(mult);
  for(double mult = 50; mult < 130; mult += 16) multBins.push_back(mult);
  for(double mult = 130; mult < 200; mult += 70) multBins.push_back(mult);
  for(double mult = 200; mult < 400; mult += 200) multBins.push_back(mult);
*/
  multBins.push_back(0);
  multBins.push_back(1000);

  float etaWidth =  0.1;
  float etaMin   = -2.4-etaWidth;
  float etaMax   =  2.4+etaWidth;
  
  std::vector<double> etaBins;
  for(double eta = etaMin; eta < etaMax + etaWidth/2; eta += etaWidth)
    etaBins.push_back(eta);

  TH2D* hSumNCosTrgPos[MAXZVTXBIN];
  TH2D* hSumNCosTrgNeg[MAXZVTXBIN];
  TH2D* hSumNSinTrgPos[MAXZVTXBIN];
  TH2D* hSumNSinTrgNeg[MAXZVTXBIN];
  TH2D* hSumNCos2TrgPos[MAXZVTXBIN];
  TH2D* hSumNCos2TrgNeg[MAXZVTXBIN];
  TH2D* hSumNSin2TrgPos[MAXZVTXBIN];
  TH2D* hSumNSin2TrgNeg[MAXZVTXBIN];
  TH1D* hSumNCosTrgPos_all[MAXZVTXBIN];
  TH1D* hSumNCosTrgNeg_all[MAXZVTXBIN];
  TH1D* hSumNSinTrgPos_all[MAXZVTXBIN];
  TH1D* hSumNSinTrgNeg_all[MAXZVTXBIN];
  TH1D* hSumNCos2TrgPos_all[MAXZVTXBIN];
  TH1D* hSumNCos2TrgNeg_all[MAXZVTXBIN];
  TH1D* hSumNSin2TrgPos_all[MAXZVTXBIN];
  TH1D* hSumNSin2TrgNeg_all[MAXZVTXBIN];
  TH2D* hSumCosTrgPos[MAXZVTXBIN][MAXETATRGBINSPT];
  TH2D* hSumSinTrgPos[MAXZVTXBIN][MAXETATRGBINSPT];
  TH2D* hSumCosTrgNeg[MAXZVTXBIN][MAXETATRGBINSPT];
  TH2D* hSumSinTrgNeg[MAXZVTXBIN][MAXETATRGBINSPT];
  TH2D* hSumCos2TrgPos[MAXZVTXBIN][MAXETATRGBINSPT];
  TH2D* hSumSin2TrgPos[MAXZVTXBIN][MAXETATRGBINSPT];
  TH2D* hSumCos2TrgNeg[MAXZVTXBIN][MAXETATRGBINSPT];
  TH2D* hSumSin2TrgNeg[MAXZVTXBIN][MAXETATRGBINSPT]; 
  TH1D* hSumAssFor[MAXZVTXBIN];
  TH1D* hSumAssBak[MAXZVTXBIN];
  TH1D* hSumCosAssFor[MAXZVTXBIN];
  TH1D* hSumSinAssFor[MAXZVTXBIN];
  TH1D* hSumCosAssBak[MAXZVTXBIN];
  TH1D* hSumSinAssBak[MAXZVTXBIN];
  TH1D* hSumCos2AssFor[MAXZVTXBIN];
  TH1D* hSumSin2AssFor[MAXZVTXBIN];
  TH1D* hSumCos2AssBak[MAXZVTXBIN];
  TH1D* hSumSin2AssBak[MAXZVTXBIN];

  for(int mm=0;mm<MAXZVTXBIN;mm++)
  {
    hSumAssFor[mm] = (TH1D*)f->Get(Form("%s/sumassfor_vtx%d",dirname.Data(),mm));
    hSumAssBak[mm] = (TH1D*)f->Get(Form("%s/sumassbak_vtx%d",dirname.Data(),mm));
    hSumCosAssFor[mm] = (TH1D*)f->Get(Form("%s/sumcosassfor_vtx%d",dirname.Data(),mm));
    hSumSinAssFor[mm] = (TH1D*)f->Get(Form("%s/sumsinassfor_vtx%d",dirname.Data(),mm));
    hSumCosAssBak[mm] = (TH1D*)f->Get(Form("%s/sumcosassbak_vtx%d",dirname.Data(),mm));
    hSumSinAssBak[mm] = (TH1D*)f->Get(Form("%s/sumsinassbak_vtx%d",dirname.Data(),mm));
    hSumCos2AssFor[mm] = (TH1D*)f->Get(Form("%s/sumcos2assfor_vtx%d",dirname.Data(),mm));
    hSumSin2AssFor[mm] = (TH1D*)f->Get(Form("%s/sumsin2assfor_vtx%d",dirname.Data(),mm));
    hSumCos2AssBak[mm] = (TH1D*)f->Get(Form("%s/sumcos2assbak_vtx%d",dirname.Data(),mm));
    hSumSin2AssBak[mm] = (TH1D*)f->Get(Form("%s/sumsin2assbak_vtx%d",dirname.Data(),mm));

    hSumNCosTrgPos[mm] = new TH2D(Form("sumncostrgpos_vtx%d",mm),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNCosTrgNeg[mm] = new TH2D(Form("sumncostrgneg_vtx%d",mm),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNSinTrgPos[mm] = new TH2D(Form("sumnsintrgpos_vtx%d",mm),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNSinTrgNeg[mm] = new TH2D(Form("sumnsintrgneg_vtx%d",mm),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNCos2TrgPos[mm] = new TH2D(Form("sumncos2trgpos_vtx%d",mm),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNCos2TrgNeg[mm] = new TH2D(Form("sumncos2trgneg_vtx%d",mm),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNSin2TrgPos[mm] = new TH2D(Form("sumnsin2trgpos_vtx%d",mm),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNSin2TrgNeg[mm] = new TH2D(Form("sumnsin2trgneg_vtx%d",mm),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);

    hSumNCosTrgPos_all[mm] = new TH1D(Form("sumncostrgpos_vtx%d_all",mm),";#eta;n",etaBins.size()-1, &etaBins[0]);
    hSumNCosTrgNeg_all[mm] = new TH1D(Form("sumncostrgneg_vtx%d_all",mm),";#eta;n",etaBins.size()-1, &etaBins[0]);
    hSumNSinTrgPos_all[mm] = new TH1D(Form("sumnsintrgpos_vtx%d_all",mm),";#eta;n",etaBins.size()-1, &etaBins[0]);
    hSumNSinTrgNeg_all[mm] = new TH1D(Form("sumnsintrgneg_vtx%d_all",mm),";#eta;n",etaBins.size()-1, &etaBins[0]);
    hSumNCos2TrgPos_all[mm] = new TH1D(Form("sumncos2trgpos_vtx%d_all",mm),";#eta;n",etaBins.size()-1, &etaBins[0]);
    hSumNCos2TrgNeg_all[mm] = new TH1D(Form("sumncos2trgneg_vtx%d_all",mm),";#eta;n",etaBins.size()-1, &etaBins[0]);
    hSumNSin2TrgPos_all[mm] = new TH1D(Form("sumnsin2trgpos_vtx%d_all",mm),";#eta;n",etaBins.size()-1, &etaBins[0]);
    hSumNSin2TrgNeg_all[mm] = new TH1D(Form("sumnsin2trgneg_vtx%d_all",mm),";#eta;n",etaBins.size()-1, &etaBins[0]);

    for(int ll=0;ll<MAXETATRGBINSPT;ll++)
    {
      hSumCosTrgPos[mm][ll] = (TH2D*)f->Get(Form("%s/sumcostrgpos_vtx%d_eta%d",dirname.Data(),mm,ll));  
      hSumSinTrgPos[mm][ll] = (TH2D*)f->Get(Form("%s/sumsintrgpos_vtx%d_eta%d",dirname.Data(),mm,ll));
      hSumCosTrgNeg[mm][ll]= (TH2D*)f->Get(Form("%s/sumcostrgneg_vtx%d_eta%d",dirname.Data(),mm,ll));
      hSumSinTrgNeg[mm][ll] = (TH2D*)f->Get(Form("%s/sumsintrgneg_vtx%d_eta%d",dirname.Data(),mm,ll));
      hSumCos2TrgPos[mm][ll] = (TH2D*)f->Get(Form("%s/sumcos2trgpos_vtx%d_eta%d",dirname.Data(),mm,ll));  
      hSumSin2TrgPos[mm][ll] = (TH2D*)f->Get(Form("%s/sumsin2trgpos_vtx%d_eta%d",dirname.Data(),mm,ll));
      hSumCos2TrgNeg[mm][ll] = (TH2D*)f->Get(Form("%s/sumcos2trgneg_vtx%d_eta%d",dirname.Data(),mm,ll));
      hSumSin2TrgNeg[mm][ll] = (TH2D*)f->Get(Form("%s/sumsin2trgneg_vtx%d_eta%d",dirname.Data(),mm,ll));

      TH1D* hSumCosTrgPos_all_prof = (TH1D*)hSumCosTrgPos[mm][ll]->ProjectionX("cospos_all",-1,-1,"e");
      TH1D* hSumSinTrgPos_all_prof = (TH1D*)hSumSinTrgPos[mm][ll]->ProjectionX("sinpos_all",-1,-1,"e");
      TH1D* hSumCosTrgNeg_all_prof = (TH1D*)hSumCosTrgNeg[mm][ll]->ProjectionX("cosneg_all",-1,-1,"e");
      TH1D* hSumSinTrgNeg_all_prof = (TH1D*)hSumSinTrgNeg[mm][ll]->ProjectionX("sinneg_all",-1,-1,"e");
      TH1D* hSumCos2TrgPos_all_prof = (TH1D*)hSumCos2TrgPos[mm][ll]->ProjectionX("cos2pos_all",-1,-1,"e");
      TH1D* hSumSin2TrgPos_all_prof = (TH1D*)hSumSin2TrgPos[mm][ll]->ProjectionX("sin2pos_all",-1,-1,"e");
      TH1D* hSumCos2TrgNeg_all_prof = (TH1D*)hSumCos2TrgNeg[mm][ll]->ProjectionX("cos2neg_all",-1,-1,"e");
      TH1D* hSumSin2TrgNeg_all_prof = (TH1D*)hSumSin2TrgNeg[mm][ll]->ProjectionX("sin2neg_all",-1,-1,"e");

      hSumNCosTrgPos_all[mm]->SetBinContent(ll+2,hSumCosTrgPos_all_prof->GetMean());
      hSumNCosTrgPos_all[mm]->SetBinError(ll+2,hSumCosTrgPos_all_prof->GetMeanError());
      hSumNSinTrgPos_all[mm]->SetBinContent(ll+2,hSumSinTrgPos_all_prof->GetMean());
      hSumNSinTrgPos_all[mm]->SetBinError(ll+2,hSumSinTrgPos_all_prof->GetMeanError());
      hSumNCosTrgNeg_all[mm]->SetBinContent(ll+2,hSumCosTrgNeg_all_prof->GetMean());
      hSumNCosTrgNeg_all[mm]->SetBinError(ll+2,hSumCosTrgNeg_all_prof->GetMeanError());
      hSumNSinTrgNeg_all[mm]->SetBinContent(ll+2,hSumSinTrgNeg_all_prof->GetMean());
      hSumNSinTrgNeg_all[mm]->SetBinError(ll+2,hSumSinTrgNeg_all_prof->GetMeanError());
      hSumNCos2TrgPos_all[mm]->SetBinContent(ll+2,hSumCos2TrgPos_all_prof->GetMean());
      hSumNCos2TrgPos_all[mm]->SetBinError(ll+2,hSumCos2TrgPos_all_prof->GetMeanError());
      hSumNSin2TrgPos_all[mm]->SetBinContent(ll+2,hSumSin2TrgPos_all_prof->GetMean());
      hSumNSin2TrgPos_all[mm]->SetBinError(ll+2,hSumSin2TrgPos_all_prof->GetMeanError());
      hSumNCos2TrgNeg_all[mm]->SetBinContent(ll+2,hSumCos2TrgNeg_all_prof->GetMean());
      hSumNCos2TrgNeg_all[mm]->SetBinError(ll+2,hSumCos2TrgNeg_all_prof->GetMeanError());
      hSumNSin2TrgNeg_all[mm]->SetBinContent(ll+2,hSumSin2TrgNeg_all_prof->GetMean());
      hSumNSin2TrgNeg_all[mm]->SetBinError(ll+2,hSumSin2TrgNeg_all_prof->GetMeanError());
    
      for(int jj=1;jj<multBins.size();jj++)
      {
        int binmin = hSumCosTrgPos[mm][ll]->GetYaxis()->FindBin(multBins[jj-1]+0.0001);
        int binmax = hSumCosTrgPos[mm][ll]->GetYaxis()->FindBin(multBins[jj]-0.0001);

        TH1D* hSumCosTrgPos_prof = (TH1D*)hSumCosTrgPos[mm][ll]->ProjectionX("cospos",binmin,binmax,"e");
        TH1D* hSumSinTrgPos_prof = (TH1D*)hSumSinTrgPos[mm][ll]->ProjectionX("sinpos",binmin,binmax,"e");
        TH1D* hSumCosTrgNeg_prof = (TH1D*)hSumCosTrgNeg[mm][ll]->ProjectionX("cosneg",binmin,binmax,"e");
        TH1D* hSumSinTrgNeg_prof = (TH1D*)hSumSinTrgNeg[mm][ll]->ProjectionX("sinneg",binmin,binmax,"e");
        TH1D* hSumCos2TrgPos_prof = (TH1D*)hSumCos2TrgPos[mm][ll]->ProjectionX("cos2pos",binmin,binmax,"e");
        TH1D* hSumSin2TrgPos_prof = (TH1D*)hSumSin2TrgPos[mm][ll]->ProjectionX("sin2pos",binmin,binmax,"e");
        TH1D* hSumCos2TrgNeg_prof = (TH1D*)hSumCos2TrgNeg[mm][ll]->ProjectionX("cos2neg",binmin,binmax,"e");
        TH1D* hSumSin2TrgNeg_prof = (TH1D*)hSumSin2TrgNeg[mm][ll]->ProjectionX("sin2neg",binmin,binmax,"e");
     
if(ll==12) cout<<binmin<<" "<<binmax<<" "<<hSumCosTrgPos_prof->GetMean()<<" "<<hSumCosTrgPos_prof->GetMeanError()<<endl;

        hSumNCosTrgPos[mm]->SetBinContent(ll+2,jj,hSumCosTrgPos_prof->GetMean());
        hSumNCosTrgPos[mm]->SetBinError(ll+2,jj,hSumCosTrgPos_prof->GetMeanError());
        hSumNSinTrgPos[mm]->SetBinContent(ll+2,jj,hSumSinTrgPos_prof->GetMean());
        hSumNSinTrgPos[mm]->SetBinError(ll+2,jj,hSumSinTrgPos_prof->GetMeanError()); 
        hSumNCosTrgNeg[mm]->SetBinContent(ll+2,jj,hSumCosTrgNeg_prof->GetMean());
        hSumNCosTrgNeg[mm]->SetBinError(ll+2,jj,hSumCosTrgNeg_prof->GetMeanError()); 
        hSumNSinTrgNeg[mm]->SetBinContent(ll+2,jj,hSumSinTrgNeg_prof->GetMean());
        hSumNSinTrgNeg[mm]->SetBinError(ll+2,jj,hSumSinTrgNeg_prof->GetMeanError());
        hSumNCos2TrgPos[mm]->SetBinContent(ll+2,jj,hSumCos2TrgPos_prof->GetMean());
        hSumNCos2TrgPos[mm]->SetBinError(ll+2,jj,hSumCos2TrgPos_prof->GetMeanError()); 
        hSumNSin2TrgPos[mm]->SetBinContent(ll+2,jj,hSumSin2TrgPos_prof->GetMean());
        hSumNSin2TrgPos[mm]->SetBinError(ll+2,jj,hSumSin2TrgPos_prof->GetMeanError());
        hSumNCos2TrgNeg[mm]->SetBinContent(ll+2,jj,hSumCos2TrgNeg_prof->GetMean());
        hSumNCos2TrgNeg[mm]->SetBinError(ll+2,jj,hSumCos2TrgNeg_prof->GetMeanError());
        hSumNSin2TrgNeg[mm]->SetBinContent(ll+2,jj,hSumSin2TrgNeg_prof->GetMean());
        hSumNSin2TrgNeg[mm]->SetBinError(ll+2,jj,hSumSin2TrgNeg_prof->GetMeanError());
      }
    }
    for(int jj=1;jj<multBins.size();jj++)
    {
      if(!hSumAssFor[mm]->GetMean()) continue;
      hSumNCosTrgPos[mm]->SetBinContent(1,jj,hSumCosAssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNCosTrgPos[mm]->SetBinError(1,jj,hSumCosAssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNCosTrgPos[mm]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumCosAssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNCosTrgPos[mm]->SetBinError(MAXETATRGBINSPT+2,jj,hSumCosAssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
      hSumNSinTrgPos[mm]->SetBinContent(1,jj,hSumSinAssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNSinTrgPos[mm]->SetBinError(1,jj,hSumSinAssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNSinTrgPos[mm]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumSinAssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNSinTrgPos[mm]->SetBinError(MAXETATRGBINSPT+2,jj,hSumSinAssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
      hSumNCosTrgNeg[mm]->SetBinContent(1,jj,hSumCosAssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNCosTrgNeg[mm]->SetBinError(1,jj,hSumCosAssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNCosTrgNeg[mm]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumCosAssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNCosTrgNeg[mm]->SetBinError(MAXETATRGBINSPT+2,jj,hSumCosAssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
      hSumNSinTrgNeg[mm]->SetBinContent(1,jj,hSumSinAssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNSinTrgNeg[mm]->SetBinError(1,jj,hSumSinAssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNSinTrgNeg[mm]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumSinAssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNSinTrgNeg[mm]->SetBinError(MAXETATRGBINSPT+2,jj,hSumSinAssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
      hSumNCos2TrgPos[mm]->SetBinContent(1,jj,hSumCos2AssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNCos2TrgPos[mm]->SetBinError(1,jj,hSumCos2AssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNCos2TrgPos[mm]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumCos2AssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNCos2TrgPos[mm]->SetBinError(MAXETATRGBINSPT+2,jj,hSumCos2AssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
      hSumNSin2TrgPos[mm]->SetBinContent(1,jj,hSumSin2AssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNSin2TrgPos[mm]->SetBinError(1,jj,hSumSin2AssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNSin2TrgPos[mm]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumSin2AssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNSin2TrgPos[mm]->SetBinError(MAXETATRGBINSPT+2,jj,hSumSin2AssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
      hSumNCos2TrgNeg[mm]->SetBinContent(1,jj,hSumCos2AssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNCos2TrgNeg[mm]->SetBinError(1,jj,hSumCos2AssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNCos2TrgNeg[mm]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumCos2AssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNCos2TrgNeg[mm]->SetBinError(MAXETATRGBINSPT+2,jj,hSumCos2AssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
      hSumNSin2TrgNeg[mm]->SetBinContent(1,jj,hSumSin2AssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNSin2TrgNeg[mm]->SetBinError(1,jj,hSumSin2AssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNSin2TrgNeg[mm]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumSin2AssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNSin2TrgNeg[mm]->SetBinError(MAXETATRGBINSPT+2,jj,hSumSin2AssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
    }
      if(!hSumAssFor[mm]->GetMean()) continue;
      hSumNCosTrgPos_all[mm]->SetBinContent(1,hSumCosAssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNCosTrgPos_all[mm]->SetBinError(1,hSumCosAssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNCosTrgPos_all[mm]->SetBinContent(MAXETATRGBINSPT+2,hSumCosAssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNCosTrgPos_all[mm]->SetBinError(MAXETATRGBINSPT+2,hSumCosAssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
      hSumNSinTrgPos_all[mm]->SetBinContent(1,hSumSinAssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNSinTrgPos_all[mm]->SetBinError(1,hSumSinAssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNSinTrgPos_all[mm]->SetBinContent(MAXETATRGBINSPT+2,hSumSinAssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNSinTrgPos_all[mm]->SetBinError(MAXETATRGBINSPT+2,hSumSinAssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
      hSumNCosTrgNeg_all[mm]->SetBinContent(1,hSumCosAssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNCosTrgNeg_all[mm]->SetBinError(1,hSumCosAssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNCosTrgNeg_all[mm]->SetBinContent(MAXETATRGBINSPT+2,hSumCosAssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNCosTrgNeg_all[mm]->SetBinError(MAXETATRGBINSPT+2,hSumCosAssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
      hSumNSinTrgNeg_all[mm]->SetBinContent(1,hSumSinAssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNSinTrgNeg_all[mm]->SetBinError(1,hSumSinAssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNSinTrgNeg_all[mm]->SetBinContent(MAXETATRGBINSPT+2,hSumSinAssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNSinTrgNeg_all[mm]->SetBinError(MAXETATRGBINSPT+2,hSumSinAssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
      hSumNCos2TrgPos_all[mm]->SetBinContent(1,hSumCos2AssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNCos2TrgPos_all[mm]->SetBinError(1,hSumCos2AssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNCos2TrgPos_all[mm]->SetBinContent(MAXETATRGBINSPT+2,hSumCos2AssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNCos2TrgPos_all[mm]->SetBinError(MAXETATRGBINSPT+2,hSumCos2AssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
      hSumNSin2TrgPos_all[mm]->SetBinContent(1,hSumSin2AssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNSin2TrgPos_all[mm]->SetBinError(1,hSumSin2AssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNSin2TrgPos_all[mm]->SetBinContent(MAXETATRGBINSPT+2,hSumSin2AssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNSin2TrgPos_all[mm]->SetBinError(MAXETATRGBINSPT+2,hSumSin2AssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
      hSumNCos2TrgNeg_all[mm]->SetBinContent(1,hSumCos2AssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNCos2TrgNeg_all[mm]->SetBinError(1,hSumCos2AssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNCos2TrgNeg_all[mm]->SetBinContent(MAXETATRGBINSPT+2,hSumCos2AssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNCos2TrgNeg_all[mm]->SetBinError(MAXETATRGBINSPT+2,hSumCos2AssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
      hSumNSin2TrgNeg_all[mm]->SetBinContent(1,hSumSin2AssFor[mm]->GetMean()/hSumAssFor[mm]->GetMean());
      hSumNSin2TrgNeg_all[mm]->SetBinError(1,hSumSin2AssFor[mm]->GetMeanError()/hSumAssFor[mm]->GetMean());
      hSumNSin2TrgNeg_all[mm]->SetBinContent(MAXETATRGBINSPT+2,hSumSin2AssBak[mm]->GetMean()/hSumAssBak[mm]->GetMean());
      hSumNSin2TrgNeg_all[mm]->SetBinError(MAXETATRGBINSPT+2,hSumSin2AssBak[mm]->GetMeanError()/hSumAssBak[mm]->GetMean());
  }

  TCanvas* cc = new TCanvas("cc","cc",1200,1200);
  cc->Divide(6,5);
  for(int i=0;i<30;i++)
  {
    cc->cd(i+1);
    hSumNCosTrgPos_all[i]->Draw("PE");
  }

  TCanvas* cc1 = new TCanvas("cc1","cc1",1200,1200);
  cc1->Divide(6,5);
  for(int i=0;i<30;i++)
  {
    cc1->cd(i+1);
    hSumNCosTrgNeg_all[i]->Draw("PE");
  }
/*
  TH2D* dNdetadphi_pos = (TH2D*)f->Get("chargedepcorr_ana_HI/dndetadphipos");
  TH2D* dNdetadphi_neg = (TH2D*)f->Get("chargedepcorr_ana_HI/dndetadphineg");

  TH2D* dNdetadphi_pos_new = (TH2D*)dNdetadphi_pos->Clone("dNdetadphi_weight_pos");
  TH2D* dNdetadphi_neg_new = (TH2D*)dNdetadphi_neg->Clone("dNdetadphi_weight_neg");
  dNdetadphi_pos_new->Reset();
  dNdetadphi_neg_new->Reset();
  dNdetadphi_pos_new->Rebin2D(1,8);
  dNdetadphi_neg_new->Rebin2D(1,8);

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
    dNdphi_pos[i]->SetMaximum(1.5);
    dNdphi_pos[i]->Draw();
    c1->cd(i+1);
    dNdphi_neg[i]->Rebin(8);
    dNdphi_neg[i]->Scale(1.0/dNdphi_neg[i]->Integral()*dNdphi_neg[i]->GetNbinsX());
    dNdphi_neg[i]->SetMinimum(0);
    dNdphi_neg[i]->SetMaximum(1.5);
    dNdphi_neg[i]->Draw();

    for(int j=1;j<=dNdphi_pos[i]->GetNbinsX();j++)
    {
      dNdetadphi_pos_new->SetBinContent(i+1,j,dNdphi_pos[i]->GetBinContent(j));
      dNdetadphi_neg_new->SetBinContent(i+1,j,dNdphi_neg[i]->GetBinContent(j));
      dNdetadphi_pos_new->SetBinError(i+1,j,dNdphi_pos[i]->GetBinError(j));
      dNdetadphi_neg_new->SetBinError(i+1,j,dNdphi_neg[i]->GetBinError(j));
    }
  }

  TCanvas* ccc = new TCanvas("ccc","",900,450);
  ccc->Divide(2,1);
  ccc->cd(1);
  dNdetadphi_pos_new->Draw("lego2");
  ccc->cd(2);
  dNdetadphi_neg_new->Draw("lego2");
*/

  TFile* fout = new TFile("recenter_pPb_n260_pttrg033_etaass445_eff1_zvtx1_bin01_new.root","recreate");
//  TFile* fout = new TFile("recenter_cent002_pttrg033_etaass445_eff1_zvtx1_bin01_new.root","recreate");
//  TFile* fout = new TFile("recenter_mc_cent080_pttrg033_etaass445_eff0_bin03.root","recreate");
  for(int mm=0;mm<MAXZVTXBIN;mm++)
  {
    hSumNCosTrgPos[mm]->Write();
    hSumNCosTrgNeg[mm]->Write();
    hSumNSinTrgPos[mm]->Write();
    hSumNSinTrgNeg[mm]->Write();
    hSumNCos2TrgPos[mm]->Write();
    hSumNCos2TrgNeg[mm]->Write();
    hSumNSin2TrgPos[mm]->Write();
    hSumNSin2TrgNeg[mm]->Write();
    hSumNCosTrgPos_all[mm]->Write();
    hSumNCosTrgNeg_all[mm]->Write();
    hSumNSinTrgPos_all[mm]->Write();
    hSumNSinTrgNeg_all[mm]->Write();
    hSumNCos2TrgPos_all[mm]->Write();
    hSumNCos2TrgNeg_all[mm]->Write();
    hSumNSin2TrgPos_all[mm]->Write();
    hSumNSin2TrgNeg_all[mm]->Write();
  }
  fout->Close();
/*
  TFile* fout1 = new TFile("dNdetadphi_cent4050_pttrg033_etaass445_eff0_vtx2_bin02_new.root","recreate");
  dNdetadphi_pos_new->Write();
  dNdetadphi_neg_new->Write();
  fout1->Close();
*/
}
