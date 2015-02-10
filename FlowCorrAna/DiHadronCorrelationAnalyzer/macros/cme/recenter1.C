void recenter1()
{
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_recenter_cent4050_pttrg033_ptassallweight_etaass445_eff0_vtx2_bin02_v34.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/chargedepcorr_cent05_pttrg033_ptassallweight_etaass445_eff0_bin03_v24.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/chargedepcorr_recenter_n220260_pttrg033_ptassallweight_etaass445_reverse_eff1_v13.root");
//  TFile* f = new TFile("/net/hisrv0001/home/davidlw/OSG_CMSSW/CMSSW_5_3_20/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/chargedepcorr_recenter.root");

  const int ntrg = 1;
  const int MAXETATRGBINSPT = 24;
  TString dirname("chargedepcorr_ana_HI");
//  TString dirname("chargedepcorr_ana_pPb");

  double small = 0.000;
  std::vector<double> multBins;

  for(double mult = 0; mult < 20; mult += 1) multBins.push_back(mult);
  for(double mult = 20; mult < 40; mult += 4) multBins.push_back(mult);
  for(double mult = 40; mult < 100; mult += 10) multBins.push_back(mult);
  for(double mult = 100; mult < 200; mult += 20) multBins.push_back(mult);
  for(double mult = 200; mult < 400; mult += 50) multBins.push_back(mult);

  float etaWidth =  0.2;
  float etaMin   = -2.4-etaWidth;
  float etaMax   =  2.4+etaWidth;
  
  std::vector<double> etaBins;
  for(double eta = etaMin; eta < etaMax + etaWidth/2; eta += etaWidth)
    etaBins.push_back(eta);

  TH2D* hSumNCosTrgPos[ntrg];
  TH2D* hSumNCosTrgNeg[ntrg];
  TH2D* hSumNSinTrgPos[ntrg];
  TH2D* hSumNSinTrgNeg[ntrg];
  TH2D* hSumNCos2TrgPos[ntrg];
  TH2D* hSumNCos2TrgNeg[ntrg];
  TH2D* hSumNSin2TrgPos[ntrg];
  TH2D* hSumNSin2TrgNeg[ntrg];
  TH1D* hSumNCosTrgPos_all[ntrg];
  TH1D* hSumNCosTrgNeg_all[ntrg];
  TH1D* hSumNSinTrgPos_all[ntrg];
  TH1D* hSumNSinTrgNeg_all[ntrg];
  TH1D* hSumNCos2TrgPos_all[ntrg];
  TH1D* hSumNCos2TrgNeg_all[ntrg];
  TH1D* hSumNSin2TrgPos_all[ntrg];
  TH1D* hSumNSin2TrgNeg_all[ntrg];
  TH2D* hSumCosTrgPos[MAXETATRGBINSPT][ntrg];
  TH2D* hSumSinTrgPos[MAXETATRGBINSPT][ntrg];
  TH2D* hSumCosTrgNeg[MAXETATRGBINSPT][ntrg];
  TH2D* hSumSinTrgNeg[MAXETATRGBINSPT][ntrg];
  TH2D* hSumCos2TrgPos[MAXETATRGBINSPT][ntrg];
  TH2D* hSumSin2TrgPos[MAXETATRGBINSPT][ntrg];
  TH2D* hSumCos2TrgNeg[MAXETATRGBINSPT][ntrg];
  TH2D* hSumSin2TrgNeg[MAXETATRGBINSPT][ntrg]; 

  TH1D* hSumAssFor = (TH1D*)f->Get(Form("%s/sumassfor",dirname.Data()));
  TH1D* hSumAssBak = (TH1D*)f->Get(Form("%s/sumassbak",dirname.Data()));
  TH1D* hSumCosAssFor = (TH1D*)f->Get(Form("%s/sumcosassfor",dirname.Data())); 
  TH1D* hSumSinAssFor = (TH1D*)f->Get(Form("%s/sumsinassfor",dirname.Data())); 
  TH1D* hSumCosAssBak = (TH1D*)f->Get(Form("%s/sumcosassbak",dirname.Data())); 
  TH1D* hSumSinAssBak = (TH1D*)f->Get(Form("%s/sumsinassbak",dirname.Data())); 
  TH1D* hSumCos2AssFor = (TH1D*)f->Get(Form("%s/sumcos2assfor",dirname.Data()));
  TH1D* hSumSin2AssFor = (TH1D*)f->Get(Form("%s/sumsin2assfor",dirname.Data()));
  TH1D* hSumCos2AssBak = (TH1D*)f->Get(Form("%s/sumcos2assbak",dirname.Data()));
  TH1D* hSumSin2AssBak = (TH1D*)f->Get(Form("%s/sumsin2assbak",dirname.Data()));

  for(int itrg=0;itrg<ntrg;itrg++)
  {
/*
    hSumNCosTrgPos[itrg] = new TH2D(Form("sumncostrgpos_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
    hSumNCosTrgNeg[itrg] = new TH2D(Form("sumncostrgneg_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
    hSumNSinTrgPos[itrg] = new TH2D(Form("sumnsintrgpos_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
    hSumNSinTrgNeg[itrg] = new TH2D(Form("sumnsintrgneg_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
    hSumNCos2TrgPos[itrg] = new TH2D(Form("sumncos2trgpos_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
    hSumNCos2TrgNeg[itrg] = new TH2D(Form("sumncos2trgneg_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
    hSumNSin2TrgPos[itrg] = new TH2D(Form("sumnsin2trgpos_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
    hSumNSin2TrgNeg[itrg] = new TH2D(Form("sumnsin2trgneg_pt%d",itrg),";#eta;n",MAXETATRGBINSPT+2,-2.4-4.8/MAXETATRGBINSPT,2.4+4.8/MAXETATRGBINSPT,100,0,100);
*/
    hSumNCosTrgPos[itrg] = new TH2D(Form("sumncostrgpos"),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNCosTrgNeg[itrg] = new TH2D(Form("sumncostrgneg"),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNSinTrgPos[itrg] = new TH2D(Form("sumnsintrgpos"),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNSinTrgNeg[itrg] = new TH2D(Form("sumnsintrgneg"),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNCos2TrgPos[itrg] = new TH2D(Form("sumncos2trgpos"),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNCos2TrgNeg[itrg] = new TH2D(Form("sumncos2trgneg"),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNSin2TrgPos[itrg] = new TH2D(Form("sumnsin2trgpos"),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);
    hSumNSin2TrgNeg[itrg] = new TH2D(Form("sumnsin2trgneg"),";#eta;n",etaBins.size()-1, &etaBins[0],multBins.size()-1, &multBins[0]);

    hSumNCosTrgPos_all[itrg] = new TH1D(Form("sumncostrgpos_all"),";#eta;n",etaBins.size()-1, &etaBins[0]);
    hSumNCosTrgNeg_all[itrg] = new TH1D(Form("sumncostrgneg_all"),";#eta;n",etaBins.size()-1, &etaBins[0]);
    hSumNSinTrgPos_all[itrg] = new TH1D(Form("sumnsintrgpos_all"),";#eta;n",etaBins.size()-1, &etaBins[0]);
    hSumNSinTrgNeg_all[itrg] = new TH1D(Form("sumnsintrgneg_all"),";#eta;n",etaBins.size()-1, &etaBins[0]);
    hSumNCos2TrgPos_all[itrg] = new TH1D(Form("sumncos2trgpos_all"),";#eta;n",etaBins.size()-1, &etaBins[0]);
    hSumNCos2TrgNeg_all[itrg] = new TH1D(Form("sumncos2trgneg_all"),";#eta;n",etaBins.size()-1, &etaBins[0]);
    hSumNSin2TrgPos_all[itrg] = new TH1D(Form("sumnsin2trgpos_all"),";#eta;n",etaBins.size()-1, &etaBins[0]);
    hSumNSin2TrgNeg_all[itrg] = new TH1D(Form("sumnsin2trgneg_all"),";#eta;n",etaBins.size()-1, &etaBins[0]);

    for(int ll=0;ll<MAXETATRGBINSPT;ll++)
    {
      hSumCosTrgPos[ll][itrg] = (TH2D*)f->Get(Form("%s/sumcostrgpos_eta%d",dirname.Data(),ll));  
      hSumSinTrgPos[ll][itrg] = (TH2D*)f->Get(Form("%s/sumsintrgpos_eta%d",dirname.Data(),ll));
      hSumCosTrgNeg[ll][itrg] = (TH2D*)f->Get(Form("%s/sumcostrgneg_eta%d",dirname.Data(),ll));
      hSumSinTrgNeg[ll][itrg] = (TH2D*)f->Get(Form("%s/sumsintrgneg_eta%d",dirname.Data(),ll));
      hSumCos2TrgPos[ll][itrg] = (TH2D*)f->Get(Form("%s/sumcos2trgpos_eta%d",dirname.Data(),ll));  
      hSumSin2TrgPos[ll][itrg] = (TH2D*)f->Get(Form("%s/sumsin2trgpos_eta%d",dirname.Data(),ll));
      hSumCos2TrgNeg[ll][itrg] = (TH2D*)f->Get(Form("%s/sumcos2trgneg_eta%d",dirname.Data(),ll));
      hSumSin2TrgNeg[ll][itrg] = (TH2D*)f->Get(Form("%s/sumsin2trgneg_eta%d",dirname.Data(),ll));

      TH1D* hSumCosTrgPos_all_prof = (TH1D*)hSumCosTrgPos[ll][itrg]->ProjectionX("cospos_all",-1,-1,"e");
      TH1D* hSumSinTrgPos_all_prof = (TH1D*)hSumSinTrgPos[ll][itrg]->ProjectionX("sinpos_all",-1,-1,"e");
      TH1D* hSumCosTrgNeg_all_prof = (TH1D*)hSumCosTrgNeg[ll][itrg]->ProjectionX("cosneg_all",-1,-1,"e");
      TH1D* hSumSinTrgNeg_all_prof = (TH1D*)hSumSinTrgNeg[ll][itrg]->ProjectionX("sinneg_all",-1,-1,"e");
      TH1D* hSumCos2TrgPos_all_prof = (TH1D*)hSumCos2TrgPos[ll][itrg]->ProjectionX("cos2pos_all",-1,-1,"e");
      TH1D* hSumSin2TrgPos_all_prof = (TH1D*)hSumSin2TrgPos[ll][itrg]->ProjectionX("sin2pos_all",-1,-1,"e");
      TH1D* hSumCos2TrgNeg_all_prof = (TH1D*)hSumCos2TrgNeg[ll][itrg]->ProjectionX("cos2neg_all",-1,-1,"e");
      TH1D* hSumSin2TrgNeg_all_prof = (TH1D*)hSumSin2TrgNeg[ll][itrg]->ProjectionX("sin2neg_all",-1,-1,"e");

      hSumNCosTrgPos_all[itrg]->SetBinContent(ll+2,hSumCosTrgPos_all_prof->GetMean());
      hSumNCosTrgPos_all[itrg]->SetBinError(ll+2,hSumCosTrgPos_all_prof->GetMeanError());
      hSumNSinTrgPos_all[itrg]->SetBinContent(ll+2,hSumSinTrgPos_all_prof->GetMean());
      hSumNSinTrgPos_all[itrg]->SetBinError(ll+2,hSumSinTrgPos_all_prof->GetMeanError());
      hSumNCosTrgNeg_all[itrg]->SetBinContent(ll+2,hSumCosTrgNeg_all_prof->GetMean());
      hSumNCosTrgNeg_all[itrg]->SetBinError(ll+2,hSumCosTrgNeg_all_prof->GetMeanError());
      hSumNSinTrgNeg_all[itrg]->SetBinContent(ll+2,hSumSinTrgNeg_all_prof->GetMean());
      hSumNSinTrgNeg_all[itrg]->SetBinError(ll+2,hSumSinTrgNeg_all_prof->GetMeanError());
      hSumNCos2TrgPos_all[itrg]->SetBinContent(ll+2,hSumCos2TrgPos_all_prof->GetMean());
      hSumNCos2TrgPos_all[itrg]->SetBinError(ll+2,hSumCos2TrgPos_all_prof->GetMeanError());
      hSumNSin2TrgPos_all[itrg]->SetBinContent(ll+2,hSumSin2TrgPos_all_prof->GetMean());
      hSumNSin2TrgPos_all[itrg]->SetBinError(ll+2,hSumSin2TrgPos_all_prof->GetMeanError());
      hSumNCos2TrgNeg_all[itrg]->SetBinContent(ll+2,hSumCos2TrgNeg_all_prof->GetMean());
      hSumNCos2TrgNeg_all[itrg]->SetBinError(ll+2,hSumCos2TrgNeg_all_prof->GetMeanError());
      hSumNSin2TrgNeg_all[itrg]->SetBinContent(ll+2,hSumSin2TrgNeg_all_prof->GetMean());
      hSumNSin2TrgNeg_all[itrg]->SetBinError(ll+2,hSumSin2TrgNeg_all_prof->GetMeanError());

      for(int jj=1;jj<multBins.size();jj++)
      {
        int binmin = hSumCosTrgPos[ll][itrg]->GetYaxis()->FindBin(multBins[jj-1]+0.0001);
        int binmax = hSumCosTrgPos[ll][itrg]->GetYaxis()->FindBin(multBins[jj]+0.0001);

        TH1D* hSumCosTrgPos_prof = (TH1D*)hSumCosTrgPos[ll][itrg]->ProjectionX("cospos",binmin,binmax-1,"e");
        TH1D* hSumSinTrgPos_prof = (TH1D*)hSumSinTrgPos[ll][itrg]->ProjectionX("sinpos",binmin,binmax-1,"e");
        TH1D* hSumCosTrgNeg_prof = (TH1D*)hSumCosTrgNeg[ll][itrg]->ProjectionX("cosneg",binmin,binmax-1,"e");
        TH1D* hSumSinTrgNeg_prof = (TH1D*)hSumSinTrgNeg[ll][itrg]->ProjectionX("sinneg",binmin,binmax-1,"e");
        TH1D* hSumCos2TrgPos_prof = (TH1D*)hSumCos2TrgPos[ll][itrg]->ProjectionX("cos2pos",binmin,binmax-1,"e");
        TH1D* hSumSin2TrgPos_prof = (TH1D*)hSumSin2TrgPos[ll][itrg]->ProjectionX("sin2pos",binmin,binmax-1,"e");
        TH1D* hSumCos2TrgNeg_prof = (TH1D*)hSumCos2TrgNeg[ll][itrg]->ProjectionX("cos2neg",binmin,binmax-1,"e");
        TH1D* hSumSin2TrgNeg_prof = (TH1D*)hSumSin2TrgNeg[ll][itrg]->ProjectionX("sin2neg",binmin,binmax-1,"e");
     
if(ll==8) cout<<binmin<<" "<<binmax<<" "<<hSumCosTrgPos_prof->GetMean()<<" "<<hSumCosTrgPos_prof->GetMeanError()<<endl;

        hSumNCosTrgPos[itrg]->SetBinContent(ll+2,jj,hSumCosTrgPos_prof->GetMean());
        hSumNCosTrgPos[itrg]->SetBinError(ll+2,jj,hSumCosTrgPos_prof->GetMeanError());
        hSumNSinTrgPos[itrg]->SetBinContent(ll+2,jj,hSumSinTrgPos_prof->GetMean());
        hSumNSinTrgPos[itrg]->SetBinError(ll+2,jj,hSumSinTrgPos_prof->GetMeanError()); 
        hSumNCosTrgNeg[itrg]->SetBinContent(ll+2,jj,hSumCosTrgNeg_prof->GetMean());
        hSumNCosTrgNeg[itrg]->SetBinError(ll+2,jj,hSumCosTrgNeg_prof->GetMeanError()); 
        hSumNSinTrgNeg[itrg]->SetBinContent(ll+2,jj,hSumSinTrgNeg_prof->GetMean());
        hSumNSinTrgNeg[itrg]->SetBinError(ll+2,jj,hSumSinTrgNeg_prof->GetMeanError());
        hSumNCos2TrgPos[itrg]->SetBinContent(ll+2,jj,hSumCos2TrgPos_prof->GetMean());
        hSumNCos2TrgPos[itrg]->SetBinError(ll+2,jj,hSumCos2TrgPos_prof->GetMeanError()); 
        hSumNSin2TrgPos[itrg]->SetBinContent(ll+2,jj,hSumSin2TrgPos_prof->GetMean());
        hSumNSin2TrgPos[itrg]->SetBinError(ll+2,jj,hSumSin2TrgPos_prof->GetMeanError());
        hSumNCos2TrgNeg[itrg]->SetBinContent(ll+2,jj,hSumCos2TrgNeg_prof->GetMean());
        hSumNCos2TrgNeg[itrg]->SetBinError(ll+2,jj,hSumCos2TrgNeg_prof->GetMeanError());
        hSumNSin2TrgNeg[itrg]->SetBinContent(ll+2,jj,hSumSin2TrgNeg_prof->GetMean());
        hSumNSin2TrgNeg[itrg]->SetBinError(ll+2,jj,hSumSin2TrgNeg_prof->GetMeanError());
      }
    }
    for(int jj=1;jj<multBins.size();jj++)
    {
      hSumNCosTrgPos[itrg]->SetBinContent(1,jj,hSumCosAssFor->GetMean()/hSumAssFor->GetMean());
      hSumNCosTrgPos[itrg]->SetBinError(1,jj,hSumCosAssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNCosTrgPos[itrg]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumCosAssBak->GetMean()/hSumAssBak->GetMean());
      hSumNCosTrgPos[itrg]->SetBinError(MAXETATRGBINSPT+2,jj,hSumCosAssBak->GetMeanError()/hSumAssBak->GetMean());
      hSumNSinTrgPos[itrg]->SetBinContent(1,jj,hSumSinAssFor->GetMean()/hSumAssFor->GetMean());
      hSumNSinTrgPos[itrg]->SetBinError(1,jj,hSumSinAssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNSinTrgPos[itrg]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumSinAssBak->GetMean()/hSumAssBak->GetMean());
      hSumNSinTrgPos[itrg]->SetBinError(MAXETATRGBINSPT+2,jj,hSumSinAssBak->GetMeanError()/hSumAssBak->GetMean());
      hSumNCosTrgNeg[itrg]->SetBinContent(1,jj,hSumCosAssFor->GetMean()/hSumAssFor->GetMean());
      hSumNCosTrgNeg[itrg]->SetBinError(1,jj,hSumCosAssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNCosTrgNeg[itrg]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumCosAssBak->GetMean()/hSumAssBak->GetMean());
      hSumNCosTrgNeg[itrg]->SetBinError(MAXETATRGBINSPT+2,jj,hSumCosAssBak->GetMeanError()/hSumAssBak->GetMean());
      hSumNSinTrgNeg[itrg]->SetBinContent(1,jj,hSumSinAssFor->GetMean()/hSumAssFor->GetMean());
      hSumNSinTrgNeg[itrg]->SetBinError(1,jj,hSumSinAssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNSinTrgNeg[itrg]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumSinAssBak->GetMean()/hSumAssBak->GetMean());
      hSumNSinTrgNeg[itrg]->SetBinError(MAXETATRGBINSPT+2,jj,hSumSinAssBak->GetMeanError()/hSumAssBak->GetMean());
      hSumNCos2TrgPos[itrg]->SetBinContent(1,jj,hSumCos2AssFor->GetMean()/hSumAssFor->GetMean());
      hSumNCos2TrgPos[itrg]->SetBinError(1,jj,hSumCos2AssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNCos2TrgPos[itrg]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumCos2AssBak->GetMean()/hSumAssBak->GetMean());
      hSumNCos2TrgPos[itrg]->SetBinError(MAXETATRGBINSPT+2,jj,hSumCos2AssBak->GetMeanError()/hSumAssBak->GetMean());
      hSumNSin2TrgPos[itrg]->SetBinContent(1,jj,hSumSin2AssFor->GetMean()/hSumAssFor->GetMean());
      hSumNSin2TrgPos[itrg]->SetBinError(1,jj,hSumSin2AssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNSin2TrgPos[itrg]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumSin2AssBak->GetMean()/hSumAssBak->GetMean());
      hSumNSin2TrgPos[itrg]->SetBinError(MAXETATRGBINSPT+2,jj,hSumSin2AssBak->GetMeanError()/hSumAssBak->GetMean());
      hSumNCos2TrgNeg[itrg]->SetBinContent(1,jj,hSumCos2AssFor->GetMean()/hSumAssFor->GetMean());
      hSumNCos2TrgNeg[itrg]->SetBinError(1,jj,hSumCos2AssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNCos2TrgNeg[itrg]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumCos2AssBak->GetMean()/hSumAssBak->GetMean());
      hSumNCos2TrgNeg[itrg]->SetBinError(MAXETATRGBINSPT+2,jj,hSumCos2AssBak->GetMeanError()/hSumAssBak->GetMean());
      hSumNSin2TrgNeg[itrg]->SetBinContent(1,jj,hSumSin2AssFor->GetMean()/hSumAssFor->GetMean());
      hSumNSin2TrgNeg[itrg]->SetBinError(1,jj,hSumSin2AssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNSin2TrgNeg[itrg]->SetBinContent(MAXETATRGBINSPT+2,jj,hSumSin2AssBak->GetMean()/hSumAssBak->GetMean());
      hSumNSin2TrgNeg[itrg]->SetBinError(MAXETATRGBINSPT+2,jj,hSumSin2AssBak->GetMeanError()/hSumAssBak->GetMean());
    }
      hSumNCosTrgPos_all[itrg]->SetBinContent(1,hSumCosAssFor->GetMean()/hSumAssFor->GetMean());
      hSumNCosTrgPos_all[itrg]->SetBinError(1,hSumCosAssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNCosTrgPos_all[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumCosAssBak->GetMean()/hSumAssBak->GetMean());
      hSumNCosTrgPos_all[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumCosAssBak->GetMeanError()/hSumAssBak->GetMean());
      hSumNSinTrgPos_all[itrg]->SetBinContent(1,hSumSinAssFor->GetMean()/hSumAssFor->GetMean());
      hSumNSinTrgPos_all[itrg]->SetBinError(1,hSumSinAssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNSinTrgPos_all[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumSinAssBak->GetMean()/hSumAssBak->GetMean());
      hSumNSinTrgPos_all[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumSinAssBak->GetMeanError()/hSumAssBak->GetMean());
      hSumNCosTrgNeg_all[itrg]->SetBinContent(1,hSumCosAssFor->GetMean()/hSumAssFor->GetMean());
      hSumNCosTrgNeg_all[itrg]->SetBinError(1,hSumCosAssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNCosTrgNeg_all[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumCosAssBak->GetMean()/hSumAssBak->GetMean());
      hSumNCosTrgNeg_all[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumCosAssBak->GetMeanError()/hSumAssBak->GetMean());
      hSumNSinTrgNeg_all[itrg]->SetBinContent(1,hSumSinAssFor->GetMean()/hSumAssFor->GetMean());
      hSumNSinTrgNeg_all[itrg]->SetBinError(1,hSumSinAssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNSinTrgNeg_all[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumSinAssBak->GetMean()/hSumAssBak->GetMean());
      hSumNSinTrgNeg_all[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumSinAssBak->GetMeanError()/hSumAssBak->GetMean());
      hSumNCos2TrgPos_all[itrg]->SetBinContent(1,hSumCos2AssFor->GetMean()/hSumAssFor->GetMean());
      hSumNCos2TrgPos_all[itrg]->SetBinError(1,hSumCos2AssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNCos2TrgPos_all[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumCos2AssBak->GetMean()/hSumAssBak->GetMean());
      hSumNCos2TrgPos_all[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumCos2AssBak->GetMeanError()/hSumAssBak->GetMean());
      hSumNSin2TrgPos_all[itrg]->SetBinContent(1,hSumSin2AssFor->GetMean()/hSumAssFor->GetMean());
      hSumNSin2TrgPos_all[itrg]->SetBinError(1,hSumSin2AssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNSin2TrgPos_all[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumSin2AssBak->GetMean()/hSumAssBak->GetMean());
      hSumNSin2TrgPos_all[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumSin2AssBak->GetMeanError()/hSumAssBak->GetMean());
      hSumNCos2TrgNeg_all[itrg]->SetBinContent(1,hSumCos2AssFor->GetMean()/hSumAssFor->GetMean());
      hSumNCos2TrgNeg_all[itrg]->SetBinError(1,hSumCos2AssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNCos2TrgNeg_all[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumCos2AssBak->GetMean()/hSumAssBak->GetMean());
      hSumNCos2TrgNeg_all[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumCos2AssBak->GetMeanError()/hSumAssBak->GetMean());
      hSumNSin2TrgNeg_all[itrg]->SetBinContent(1,hSumSin2AssFor->GetMean()/hSumAssFor->GetMean());
      hSumNSin2TrgNeg_all[itrg]->SetBinError(1,hSumSin2AssFor->GetMeanError()/hSumAssFor->GetMean());
      hSumNSin2TrgNeg_all[itrg]->SetBinContent(MAXETATRGBINSPT+2,hSumSin2AssBak->GetMean()/hSumAssBak->GetMean());
      hSumNSin2TrgNeg_all[itrg]->SetBinError(MAXETATRGBINSPT+2,hSumSin2AssBak->GetMeanError()/hSumAssBak->GetMean());
  }

  TCanvas* cc = new TCanvas("cc","cc",1100,500);
  cc->Divide(2,1);
  cc->cd(1);
  hSumNCosTrgPos_all[0]->Draw("PE");
  cc->cd(2);
  hSumNSinTrgPos_all[0]->Draw("PE");

  TCanvas* cc1 = new TCanvas("cc1","cc1",1100,500);
  cc1->Divide(2,1);
  cc1->cd(1);
  hSumNCosTrgNeg_all[0]->Draw("PE");
  cc1->cd(2);
  hSumNSinTrgNeg_all[0]->Draw("PE");

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
return;
//  TFile* fout = new TFile("recenter_pPb_n220260_pttrg033_etaass445_eff0_bin03_new.root","recreate");
  TFile* fout = new TFile("recenter_cent4050_pttrg033_etaass445_eff0_vtx2_bin02_new.root","recreate");
//  TFile* fout = new TFile("recenter_mc_cent080_pttrg033_etaass445_eff0_bin03.root","recreate");
  for(int itrg=0;itrg<ntrg;itrg++)
  {
    hSumNCosTrgPos[itrg]->Write();
    hSumNCosTrgNeg[itrg]->Write();
    hSumNSinTrgPos[itrg]->Write();
    hSumNSinTrgNeg[itrg]->Write();
    hSumNCos2TrgPos[itrg]->Write();
    hSumNCos2TrgNeg[itrg]->Write();
    hSumNSin2TrgPos[itrg]->Write();
    hSumNSin2TrgNeg[itrg]->Write();
    hSumNCosTrgPos_all[itrg]->Write();
    hSumNCosTrgNeg_all[itrg]->Write();
    hSumNSinTrgPos_all[itrg]->Write();
    hSumNSinTrgNeg_all[itrg]->Write();
    hSumNCos2TrgPos_all[itrg]->Write();
    hSumNCos2TrgNeg_all[itrg]->Write();
    hSumNSin2TrgPos_all[itrg]->Write();
    hSumNSin2TrgNeg_all[itrg]->Write();
  }
  fout->Close();

  TFile* fout1 = new TFile("dNdetadphi_cent4050_pttrg033_etaass445_eff0_vtx2_bin02_new.root","recreate");
  dNdetadphi_pos_new->Write();
  dNdetadphi_neg_new->Write();
  fout1->Close();
}
