#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/DiHadronCorrelationMultiBase.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EventShape.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TList.h>
#include <TIterator.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TString.h>
#include <TObjString.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <iostream>

#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"

DiHadronCorrelationMultiBase::DiHadronCorrelationMultiBase(const edm::ParameterSet& iConfig) :
  cent(0),
  hEffWeight(0),
  hTrgWeight(0),
  nMult(0),
  nMultP(0),
  nMultM(0),
  nMultAll_trg(0),
  nMultAll_ass(0),
  nMultCorr(0),
  nMultAllCorr_trg(0),
  nMultAllCorr_ass(0),
  nVertices(0),
  maxofflinetracks(0),
  nCentBins(200),
  hft(0),
  npixel(0),
  zdc(0),
  xVtx(-99999.),
  yVtx(-99999.),
  zVtx(-99999.),	
  xVtxError(99999.),
  yVtxError(99999.),
  zVtxError(99999.)
{
  TH1::SetDefaultSumw2();

  cutPara.trgtrackCollection = iConfig.getParameter<string>("TrgTrackCollection");
  cutPara.genParticleCollection = iConfig.getParameter<string>("GenParticleCollection");
  cutPara.vertexCollection = iConfig.getParameter<string>("VertexCollection");
  cutPara.v0CandidateCollection = iConfig.getParameter<string>("V0CandidateCollection");

  trgID = GetParticleID(iConfig.getParameter<string>("TriggerID"));
  assID = GetParticleID(iConfig.getParameter<string>("AssociateID"));

  NEtaBins = iConfig.getParameter<int>("NEtaBins");
  NPhiBins = iConfig.getParameter<int>("NPhiBins");
  checksign = iConfig.getParameter<int>("checksign");

  cutPara.nmin = iConfig.getParameter<int>("nmin");
  cutPara.nmax = iConfig.getParameter<int>("nmax");
  cutPara.centmin = iConfig.getParameter<int>("centmin");
  cutPara.centmax = iConfig.getParameter<int>("centmax");
  cutPara.xvtxcenter = iConfig.getParameter<double>("xvtxcenter");
  cutPara.yvtxcenter = iConfig.getParameter<double>("yvtxcenter");
  cutPara.zvtxcenter = iConfig.getParameter<double>("zvtxcenter");
  cutPara.rhomin = iConfig.getParameter<double>("rhomin");
  cutPara.rhomax = iConfig.getParameter<double>("rhomax");
  cutPara.zvtxmin = iConfig.getParameter<double>("zvtxmin");
  cutPara.zvtxmax = iConfig.getParameter<double>("zvtxmax");  
  cutPara.zvtxbin = iConfig.getParameter<double>("zvtxbin");
  cutPara.etatrgmin = iConfig.getParameter<double>("etatrgmin");
  cutPara.etatrgmax = iConfig.getParameter<double>("etatrgmax");
  cutPara.etaassmin = iConfig.getParameter<double>("etaassmin");
  cutPara.etaassmax = iConfig.getParameter<double>("etaassmax");
  cutPara.etamultmin = iConfig.getParameter<double>("etamultmin");
  cutPara.etamultmax = iConfig.getParameter<double>("etamultmax");
  cutPara.chargeasymmin = iConfig.getParameter<double>("chargeasymmin");
  cutPara.chargeasymmax = iConfig.getParameter<double>("chargeasymmax");
  cutPara.pttrgmin = iConfig.getParameter< std::vector<double> >("pttrgmin");
  cutPara.pttrgmax = iConfig.getParameter< std::vector<double> >("pttrgmax");
  cutPara.ptassmin = iConfig.getParameter< std::vector<double> >("ptassmin");
  cutPara.ptassmax = iConfig.getParameter< std::vector<double> >("ptassmax");
  cutPara.ptmultmin = iConfig.getParameter<double>("ptmultmin");
  cutPara.ptmultmax = iConfig.getParameter<double>("ptmultmax");
  cutPara.runmin = iConfig.getParameter<int>("runmin");
  cutPara.runmax = iConfig.getParameter<int>("runmax");
  cutPara.etacms = iConfig.getParameter<double>("etacms");
  cutPara.nvtxmax = iConfig.getParameter<int>("nvtxmax");

  cutPara.mass_trg = iConfig.getParameter<double>("mass_trg");
  cutPara.mass_ass = iConfig.getParameter<double>("mass_ass");
  cutPara.genpdgId_trg = iConfig.getParameter<int>("genpdgId_trg");
  cutPara.genpdgId_ass = iConfig.getParameter<int>("genpdgId_ass");
  cutPara.isstable_trg = iConfig.getParameter<bool>("isstable_trg");
  cutPara.isstable_ass = iConfig.getParameter<bool>("isstable_ass");
  cutPara.ischarge_trg = iConfig.getParameter<bool>("ischarge_trg");
  cutPara.ischarge_ass = iConfig.getParameter<bool>("ischarge_ass");

  cutPara.IsGenMult = iConfig.getParameter<bool>("IsGenMult");
  cutPara.IsVtxSel = iConfig.getParameter<bool>("IsVtxSel");
  cutPara.IsCorr = iConfig.getParameter<bool>("IsCorr");
  cutPara.IsHI = iConfig.getParameter<bool>("IsHI");
  cutPara.IsFullMatrix = iConfig.getParameter<bool>("IsFullMatrix");
  cutPara.IsPtWeightTrg = iConfig.getParameter<bool>("IsPtWeightTrg");
  cutPara.IsPtWeightAss = iConfig.getParameter<bool>("IsPtWeightAss");   
  cutPara.IsTrgEtaCutAbs = iConfig.getParameter<bool>("IsTrgEtaCutAbs");
  cutPara.IsAssEtaCutAbs = iConfig.getParameter<bool>("IsAssEtaCutAbs");
  cutPara.IsPPTrkQuality = iConfig.getParameter<bool>("IsPPTrkQuality");
  cutPara.IsHITrkQuality = iConfig.getParameter<bool>("IsHITrkQuality");
  cutPara.IsDebug = iConfig.getParameter<bool>("IsDebug");
  cutPara.IsInvMass = iConfig.getParameter<bool>("IsInvMass");
  cutPara.IsEventEngineer = iConfig.getParameter<bool>("IsEventEngineer");
  cutPara.IsCheckV0Dau = iConfig.getParameter<bool>("IsCheckV0Dau");

  TString eff_filename(iConfig.getParameter<string>("EffFileName")); 
  hEffWeight = 0;
  if(!eff_filename.IsNull()) 
  {
    edm::FileInPath fip(Form("FlowCorrAna/DiHadronCorrelationAnalyzer/data/%s",eff_filename.Data()));
    TFile f(fip.fullPath().c_str(),"READ");
    hEffWeight = (TH2D*)f.Get("rTotalEff3D");
    f.Close();
  }

  TString etaphi_filename(iConfig.getParameter<string>("EtaPhiFileName"));
  hEtaPhiWeightPos = 0;
  hEtaPhiWeightNeg = 0;
  if(!etaphi_filename.IsNull())
  {
    edm::FileInPath fip2(Form("FlowCorrAna/DiHadronCorrelationAnalyzer/data/%s",etaphi_filename.Data()));
    TFile f2(fip2.fullPath().c_str(),"READ");
    hEtaPhiWeightPos = (TH2D*)f2.Get("dNdetadphi_weight_pos");
    hEtaPhiWeightNeg = (TH2D*)f2.Get("dNdetadphi_weight_neg");
    if(hEtaPhiWeightPos && hEtaPhiWeightNeg) cout<<"Eta-Phi corrections loaded!"<<endl;
    f2.Close();
  }
}

//DiHadronCorrelationMultiBase::~DiHadronCorrelationMultiBase()
//{}

//
// member functions
//

void DiHadronCorrelationMultiBase::beginJob()
{
  // pt bins
  std::vector<double> ptBins;
/*
  ptBins.push_back(0.0);
  ptBins.push_back(0.3);
  ptBins.push_back(0.5);
  ptBins.push_back(0.7);
  ptBins.push_back(1.0);
  ptBins.push_back(1.3);
  ptBins.push_back(1.6);
  ptBins.push_back(2.0);
  ptBins.push_back(2.5);
  ptBins.push_back(3.0);
  ptBins.push_back(3.5);
  ptBins.push_back(4.0);
  ptBins.push_back(5.0);
  ptBins.push_back(6.0);
  ptBins.push_back(7.0);
  ptBins.push_back(8.0);
*/
  const double small = 1e-3;
  double pt;

  for(pt =   0  ; pt <   1.2-small; pt +=  0.05) ptBins.push_back(pt); // 24 bins
  for(pt =   1.2; pt <   2.4-small; pt +=  0.1 ) ptBins.push_back(pt); // 12 bins
  for(pt =   2.4; pt <   7.2-small; pt +=  0.4 ) ptBins.push_back(pt); // 12 bins
  for(pt =   7.2; pt <  14.4-small; pt +=  1.2 ) ptBins.push_back(pt); // 6 bins
  for(pt =  14.4; pt <  28.8-small; pt +=  2.4 ) ptBins.push_back(pt); // 6 bins 
  for(pt =  28.8; pt <  48.0-small; pt +=  3.2 ) ptBins.push_back(pt); // 6 bins
  for(pt =  48.0; pt <  86.4-small; pt +=  6.4 ) ptBins.push_back(pt); // 6 bins
  for(pt =  86.4; pt < 189.6-small; pt +=  8.6 ) ptBins.push_back(pt); // 6 bins
  ptBins.push_back(189.6);

  static float etaMin   = -3.0;
  static float etaMax   =  3.0;
  static float etaWidth =  0.2;
  std::vector<double> etaBins;

  for(double eta = etaMin; eta < etaMax + etaWidth/2; eta += etaWidth)
    etaBins.push_back(eta);

  hMultRawAll = theOutputs->make<TH1D>("multrawall",";n",10000,0,10000);
  hMultCorrAll = theOutputs->make<TH1D>("multcorrall",";n",10000,0,10000);
  hMultChargeAsym = theOutputs->make<TH1D>("multchargeasym",";#frac{N_{+}-N_{-}}{N_{+}+N_{-}}",200,-1,1);
  hZVtx = theOutputs->make<TH1D>("zvtx",";z_{vtx} (cm)",160,-20,20);
  hXYVtx = theOutputs->make<TH2D>("xyvtx",";x_{vtx} (cm);y_{vtx} (cm)",100,-0.5,0.5,100,-0.5,0.5);
  hCentrality = theOutputs->make<TH1D>("centrality",";centbin",nCentBins+1,-1,nCentBins);
  
//  if(trgID == kLambda || trgID == kKshort || assID == kLambda || assID == kKshort) 
//  {
    hThetaV0Plus = theOutputs->make<TH2D>("thetav0plus",";x_{F};cos#theta",200,0,0.2,100,-1,1);
    hThetaV0Minus = theOutputs->make<TH2D>("thetav0minus",";x_{F};cos#theta",200,0,0.2,100,-1,1);
    hV0InvMassVsP = theOutputs->make<TH2D>("v0invmassvsp",";p (GeV);Invariant Mass (GeV)",1000,0,1000,130,1.7,3.);
    hV0InvEtaVsP = theOutputs->make<TH2D>("v0etavsp",";p (GeV);#pseudorapidity",1000,0,1000,48,-2.4,2.4);
    hV0InvMassVsPt = theOutputs->make<TH2D>("v0invmassvspt",";p_{T}(GeV);Invariant Mass (GeV)",100,0,100,130,1.7,3.);
    hV0InvEtaVsPt = theOutputs->make<TH2D>("v0etavspt",";p_{T}(GeV);#pseudorapidity",100,0,100,48,-2.4,2.4);
//  }

  if(cutPara.IsDebug)
  {
    hPtAll_trg = theOutputs->make<TH1D>("ptall_trg",";p_{T}(GeV/c)",ptBins.size()-1, &ptBins[0]);
    hPTotAll_trg = theOutputs->make<TH1D>("ptotall_trg",";p_{T}(GeV/c)",10000,0,1000);
    hNVtx = theOutputs->make<TH1D>("nvtx",";nVertices",51,-0.5,50.5);
//  hNVtxVsNMult = theOutputs->make<TH2D>("nvtxvsnmult",";nMult;nVertices",500,0,500,50,0,50);
    hdNdetadptAll_trg = theOutputs->make<TH2D>("dNdetadptall_trg",";#eta;pT(GeV)",etaBins.size()-1, &etaBins[0],ptBins.size()-1, &ptBins[0]);
    hdNdetadphiAll_trg = theOutputs->make<TH2D>("dNdetadphiall_trg",";#eta;#phi",120,-6.0,6.0,36,-PI,PI);
    hPtAll_ass = theOutputs->make<TH1D>("ptall_ass",";p_{T}(GeV/c)",5000,0,50);
    hPTotAll_ass = theOutputs->make<TH1D>("ptotall_ass",";p_{T}(GeV/c)",10000,0,1000);
    hdNdetadptAll_ass = theOutputs->make<TH2D>("dNdetadptall_ass",";#eta;pT(GeV)",120,-6.0,6.0,1000,0,10.0);
    hdNdetadphiAll_ass = theOutputs->make<TH2D>("dNdetadphiall_ass",";#eta;#phi",120,-6.0,6.0,36,-PI,PI);
    hPtCorrAll_trg = theOutputs->make<TH1D>("ptcorrall_trg",";p_{T}(GeV/c)",ptBins.size()-1, &ptBins[0]);
    hdNdetadptCorrAll_trg = theOutputs->make<TH2D>("dNdetadptcorrall_trg",";#eta;pT(GeV)",120,-6.0,6.0,1000,0,10.0);
    hdNdetadphiCorrAll_trg = theOutputs->make<TH2D>("dNdetadphicorrall_trg",";#eta;#phi",120,-6.0,6.0,36,-PI,PI);
    hPtCorrAll_ass = theOutputs->make<TH1D>("ptcorrall_ass",";p_{T}(GeV/c)",1000,0,100);
    hdNdetadptCorrAll_ass = theOutputs->make<TH2D>("dNdetadptcorrall_ass",";#eta;pT(GeV)",120,-6.0,6.0,1000,0,10.0);
    hdNdetadphiCorrAll_ass = theOutputs->make<TH2D>("dNdetadphicorrall_ass",";#eta;#phi",120,-6.0,6.0,36,-PI,PI);
    hHFTowerSum = theOutputs->make<TH1D>("hftowersum",";HF Sum E_{T}",600,0,6000);
    hHFvsNpixel = theOutputs->make<TH2D>("hfvsnpixel",";HF Sum E_{T}; Npixel;",600,0,6000,800,0,80000);
    hHFvsZDC = theOutputs->make<TH2D>("hfvszdc",";HF Sum E_{T}; ZDC Sum E_{T};",600,0,6000,800,0,80000);
//    hNpart = theOutputs->make<TH1D>("Npart",";N_{part}",500,0,500);
  }
  if(cutPara.IsInvMass) hInvMassVsPt_Signal = theOutputs->make<TH2D>("invmassvspt_signal",";p_{T}(GeV);Invariant Mass (GeV)",500,0,50,1500,0,3);
  if(cutPara.IsEventEngineer) hEventEngineer = theOutputs->make<TH2D>("eventengineer",";centrality;q_{2}",200,0,200,1000,0,1.0);

/*
  hV0InvMassVsPt = theOutputs->make<TH2D>("v0invmassvspt",";p_{T}(GeV);Invariant Mass (GeV)",200,0,20,1500,0,1.5);
  hV0InvMassVsPt_masspipicut = theOutputs->make<TH2D>("v0invmassvspt_masspipicut",";p_{T}(GeV);Invariant Mass (GeV)",200,0,20,1500,0,1.5);
  hV0AP = theOutputs->make<TH2D>("v0ap",";#alpha;#q_{T}",1000,-1,1,1000,0,0.5);
  hV0AP_masspipicut = theOutputs->make<TH2D>("v0ap_masspipicut",";#alpha;#q_{T}",1000,-1,1,1000,0,0.5);
  hV0MassPiPi = theOutputs->make<TH1D>("v0masspipi",";mass_pipi (GeV/c)",100,0.4,0.6);
  hV0MassEE = theOutputs->make<TH1D>("v0massee",";mass_ee (GeV/c)",100,0.0,0.2);
*/
  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    hMult_trg[itrg] = theOutputs->make<TH1D>(Form("mult_trg_%d",itrg),";n^{trg}",2000,0,2000);
    hMultCorr_trg[itrg] = theOutputs->make<TH1D>(Form("multcorr_trg_%d",itrg),";n^{trg}",2000,0,2000);
    hpT_Signal_trg[itrg] = theOutputs->make<TH1D>(Form("pt_signal_trg_%d",itrg),";pT(GeV)",1000,0,100.);
    hpTCorr_Signal_trg[itrg] = theOutputs->make<TH1D>(Form("ptcorr_signal_trg_%d",itrg),";pT(GeV)",1000,0,100.);
    if(cutPara.IsDebug)
    {
      hdNdetadphi_trg[itrg] = theOutputs->make<TH2D>(Form("dNdetadphi_trg_%d",itrg),";#eta;#phi",60,-6.0,6.0,NPhiBins,-PI,PI);
      hdNdetadphiCorr_trg[itrg] = theOutputs->make<TH2D>(Form("dNdetadphicorr_trg_%d",itrg),";#eta;#phi",60,-6.0,6.0,NPhiBins,-PI,PI);
    }
  }

  for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
  {
    hMult_ass[jass] = theOutputs->make<TH1D>(Form("mult_ass_%d",jass),";n^{ass}",2000,0,2000);
    hMultCorr_ass[jass] = theOutputs->make<TH1D>(Form("multcorr_ass_%d",jass),";n^{ass}",2000,0,2000);
    hpT_Signal_ass[jass] = theOutputs->make<TH1D>(Form("pt_signal_ass_%d",jass),";pT(GeV)",1000,0,100.);
    hpTCorr_Signal_ass[jass] = theOutputs->make<TH1D>(Form("ptcorr_signal_ass_%d",jass),";pT(GeV)",1000,0,100.);
    if(cutPara.IsDebug)
    {
      hdNdetadphi_ass[jass] = theOutputs->make<TH2D>(Form("dNdetadphi_ass_%d",jass),";#eta;#phi",60,-6.0,6.0,NPhiBins,-PI,PI);
      hdNdetadphiCorr_ass[jass] = theOutputs->make<TH2D>(Form("dNdetadphicorr_ass_%d",jass),";#eta;#phi",60,-6.0,6.0,NPhiBins,-PI,PI);
    }
  }
}

// ------------ method called to for each event  -----------
void DiHadronCorrelationMultiBase::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  nMult=0;
  nMultP=0;
  nMultM=0;
  nMultCorr=0;
  nMultAll_trg=0;
  nMultAllCorr_trg=0;
  nMultAll_ass=0;
  nMultAllCorr_ass=0;

  eventcorr = new DiHadronCorrelationEvent();

  // Select vertex
//  double zvtxbincentertmp=0;
  if(cutPara.IsVtxSel)
  {
    GetVertices(iEvent,iSetup);
    hZVtx->Fill(zVtx);
    hXYVtx->Fill(xVtx,yVtx);
    if(cutPara.IsDebug) hNVtx->Fill(nVertices);

    if(nVertices>cutPara.nvtxmax) return;

    double zVtxtmp = zVtx-cutPara.zvtxcenter;
    double yVtxtmp = yVtx-cutPara.yvtxcenter;
    double xVtxtmp = xVtx-cutPara.xvtxcenter;
    double rhotmp = sqrt(xVtxtmp*xVtxtmp+yVtxtmp*yVtxtmp);
//    zvtxbincentertmp = (int)((zVtxtmp-cutPara.zvtxmin)/cutPara.zvtxbin)*cutPara.zvtxbin+cutPara.zvtxmin+cutPara.zvtxbin/2;
    if( zVtxtmp<cutPara.zvtxmin || zVtxtmp>cutPara.zvtxmax || rhotmp<cutPara.rhomin || rhotmp>cutPara.rhomax ) return;
  }

  hiCentrality=-1;
  if(cutPara.centmin!=-1 && cutPara.centmax!=-1)
  {
    hiCentrality = GetCentralityBin(iEvent,iSetup);
    if(hiCentrality<cutPara.centmin || hiCentrality>=cutPara.centmax) return;
    if(cutPara.IsDebug)
    {
      hHFTowerSum->Fill(hft);
      hHFvsNpixel->Fill(hft,npixel);
      hHFvsZDC->Fill(hft,zdc);
    }
  }
  hCentrality->Fill(hiCentrality);

  // Select multiplicity
  GetMult(iEvent,iSetup);
  if((nMult<cutPara.nmin || nMult>=cutPara.nmax) && (cutPara.nmin!=-1 || cutPara.nmax!=-1)) return;
  hMultRawAll->Fill(nMult);
//  hNVtxVsNMult->Fill(nMult,nVertices);
  hMultCorrAll->Fill(nMultCorr,1.0/GetTrgWeight(nMult));

  double asym = (double)(nMultP-nMultM)/(nMultP+nMultM);
  if( asym<cutPara.chargeasymmin || asym>cutPara.chargeasymmax ) return;
  hMultChargeAsym->Fill(asym);

  if(cutPara.IsEventEngineer) hEventEngineer->Fill(hiCentrality,GetEventEngineer(iEvent,iSetup,2));

  switch (trgID)
  {
     case kGenParticle:
       LoopParticles(iEvent,iSetup,1,cutPara.genpdgId_trg,cutPara.isstable_trg,cutPara.ischarge_trg);
       break;
     case kTrack:
       LoopTracks(iEvent,iSetup,1,-999);
       break;
     case kTrackP:
       LoopTracks(iEvent,iSetup,1,1);
       break;
     case kTrackM:
       LoopTracks(iEvent,iSetup,1,-1);
       break;
     case kCaloTower:
       LoopCaloTower(iEvent,iSetup,1);
       break;
     case kKshort:
       cutPara.mass_trg=0.498;
       LoopV0Candidates(iEvent,iSetup, 1, "Kshort",-1);
       break;
     case kLambda:
       cutPara.mass_trg=1.116;
       LoopV0Candidates(iEvent,iSetup, 1, "Lambda",-1);
       break;
     case kLambdaP:
       cutPara.mass_trg=1.116;
       LoopV0Candidates(iEvent,iSetup, 1, "Lambda",3122);
       break;
     case kLambdaM:
       cutPara.mass_trg=1.116;
       LoopV0Candidates(iEvent,iSetup, 1, "Lambda",-3122);
       break;
     case kD0:
       cutPara.mass_trg=1.86484;
       LoopV0Candidates(iEvent,iSetup, 1 , "D0",-1);
     default:
       break;
  }

  switch (assID)
  {
     case kGenParticle:
       LoopParticles(iEvent,iSetup,0,cutPara.genpdgId_ass,cutPara.isstable_ass,cutPara.ischarge_ass);
       break;     
     case kTrack:
       LoopTracks(iEvent,iSetup,0,-999);
       break;
     case kTrackP:
       LoopTracks(iEvent,iSetup,0,1);
       break;
     case kTrackM:
       LoopTracks(iEvent,iSetup,0,-1);
       break;
     case kCaloTower:
       LoopCaloTower(iEvent,iSetup,0);
       break;
     case kKshort:
       cutPara.mass_ass=0.498;
       LoopV0Candidates(iEvent,iSetup,0, "Kshort",-1);
       break;
     case kLambda:
       cutPara.mass_ass=1.116;
       LoopV0Candidates(iEvent,iSetup,0, "Lambda",-1);
       break;
     case kLambdaP:
       cutPara.mass_ass=1.116;
       LoopV0Candidates(iEvent,iSetup, 0, "Lambda",3122);
       break;
     case kLambdaM:
       cutPara.mass_ass=1.116;
       LoopV0Candidates(iEvent,iSetup, 0, "Lambda",-3122);
       break;
     case kD0:
       cutPara.mass_ass=1.86484;
       LoopV0Candidates(iEvent,iSetup,0, "D0",-1);
       break;
     default:
       break;
  }

  eventcorr->run = iEvent.id().run();
//  eventcorr->lumi = iEvent.luminosityBlock();
  eventcorr->event = iEvent.id().event();
//  eventcorr->nmult=nMult;
//  eventcorr->centbin=hiCentrality;
  eventcorr->zvtx=zVtx;

  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  {
    nMult_trg[itrg]=eventcorr->pVect_trg[itrg].size();
    nMultCorr_trg[itrg]=0;
    for(unsigned int ntrg=0;ntrg<nMult_trg[itrg];ntrg++) nMultCorr_trg[itrg] = nMultCorr_trg[itrg] + 1.0/(eventcorr->effVect_trg[itrg])[ntrg];
    hMult_trg[itrg]->Fill(nMult_trg[itrg]);
    hMultCorr_trg[itrg]->Fill(nMultCorr_trg[itrg]);
    (eventcorr->nMultCorrVect_trg).push_back(nMultCorr_trg[itrg]);
  }
    
  for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
  {
    nMult_ass[jass]=eventcorr->pVect_ass[jass].size();
    nMultCorr_ass[jass]=0;
    for(unsigned int nass=0;nass<nMult_ass[jass];nass++) nMultCorr_ass[jass] = nMultCorr_ass[jass] + 1.0/(eventcorr->effVect_ass[jass])[nass];
    hMult_ass[jass]->Fill(nMult_ass[jass]);
    hMultCorr_ass[jass]->Fill(nMultCorr_ass[jass]);
    (eventcorr->nMultCorrVect_ass).push_back(nMultCorr_ass[jass]);
  }
  eventcorrArray.push_back(*eventcorr);

  delete eventcorr;
}

void DiHadronCorrelationMultiBase::endJob()
{
  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  { 
    ptMean_trg[itrg]=hpTCorr_Signal_trg[itrg]->GetMean();
    ptMean2_trg[itrg]=hpTCorr_Signal_trg[itrg]->GetMean()*hpTCorr_Signal_trg[itrg]->GetMean()+hpTCorr_Signal_trg[itrg]->GetRMS()*hpTCorr_Signal_trg[itrg]->GetRMS();
  } 
  for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
  {
    ptMean_ass[jass]=hpTCorr_Signal_ass[jass]->GetMean();
    ptMean2_ass[jass]=hpTCorr_Signal_ass[jass]->GetMean()*hpTCorr_Signal_ass[jass]->GetMean()+hpTCorr_Signal_ass[jass]->GetRMS()*hpTCorr_Signal_ass[jass]->GetRMS();
  }

  NormalizeHists();
}

// ---------------------------------------------------------------
void DiHadronCorrelationMultiBase::GetMult(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   if(!cutPara.IsGenMult) 
   {
     //----- loop over tracks -----
     edm::Handle< reco::TrackCollection > tracks;
     iEvent.getByLabel(cutPara.trgtrackCollection.Data(), tracks);
     if( !tracks->size() ) { cout<<"Invalid or empty track collection!"<<endl; return; }

     for(unsigned it=0; it<tracks->size(); ++it){

       const reco::Track & trk = (*tracks)[it];

       if(trk.pt()<0.0001) continue;

       // select tracks based on proximity to best vertex 
       math::XYZPoint bestvtx(xVtx,yVtx,zVtx);

       double dzvtx = trk.dz(bestvtx);
       double dxyvtx = trk.dxy(bestvtx);      
       double dzerror = sqrt(trk.dzError()*trk.dzError()+zVtxError*zVtxError);
       double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+xVtxError*yVtxError);
       double charge = trk.charge();

/*
       int nhits = trk.numberOfValidHits();
       double chi2n = trk.normalizedChi2();
       int nlayers = trk.hitPattern().trackerLayersWithMeasurement();
*/
       // standard quality cuts

       if(cutPara.IsPPTrkQuality)
       {
         if(!trk.quality(reco::TrackBase::highPurity)) continue;
         if(fabs(trk.ptError())/trk.pt()>0.1) continue;
         if(fabs(dzvtx/dzerror) > 3.0) continue;
         if(fabs(dxyvtx/dxyerror) > 3.0) continue;
       }

       if(cutPara.IsHITrkQuality && !trk.quality(reco::TrackBase::highPurity)) continue;

       double eta = trk.eta();
       double phi = trk.phi();
       double pt  = trk.pt();

       double effweight = GetEffWeight(eta,phi,pt,0.5*(cutPara.zvtxmax+cutPara.zvtxmin),hiCentrality,charge);

       if(eta>=cutPara.etamultmin && eta<=cutPara.etamultmax && pt>=cutPara.ptmultmin && pt<=cutPara.ptmultmax) 
       { 
         nMult++; 
         nMultCorr=nMultCorr+1.0/effweight;
         if(charge>0) nMultP++;
         if(charge<0) nMultM++;         
       }
     }
   }
   else
   {
     //----- loop over particles -----
     edm::Handle<reco::GenParticleCollection> genTracks;
     iEvent.getByLabel(cutPara.genParticleCollection.Data(), genTracks);
     if( !genTracks->size() ) { cout<<"Invalid or empty genParticle collection!"<<endl; return; }
     
     for(unsigned ip=0; ip<genTracks->size(); ++ip){
       const reco::GenParticle & p = (*genTracks)[ip];
       if(p.status() != 1) continue;
       if(p.charge() == 0) continue;

       double eta = p.eta();
       double pt  = p.pt();

       if(eta>=cutPara.etamultmin && eta<=cutPara.etamultmax && pt>=cutPara.ptmultmin && pt<=cutPara.ptmultmax) 
       {
         nMult++;
         nMultCorr++;
         if(p.charge()>0) nMultP++;
         if(p.charge()<0) nMultM++;
       }
     }
   }
}

// ------------- Loop over all the particles ---------------------
void DiHadronCorrelationMultiBase::LoopParticles(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, int pdgid, bool isstable, bool ischarge)
{
   //----- loop over particles -----
   edm::Handle<reco::GenParticleCollection> genTracks;
   iEvent.getByLabel(cutPara.genParticleCollection.Data(), genTracks);
   if( !genTracks->size() ) { cout<<"Invalid or empty genParticle collection!"<<endl; return; }

   for(unsigned ip=0; ip<genTracks->size(); ++ip){
     const reco::GenParticle & p = (*genTracks)[ip];

     if(p.status() != 1 && isstable) continue;
     if(p.charge() == 0 && ischarge) continue;
     if(fabs(p.pdgId()) != pdgid && pdgid!=-999999) continue;

     double eta = p.eta();
     double phi = p.phi();
     double pt  = p.pt();
     double charge = p.charge();
     double mass = p.mass();

     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(pt,eta,phi,mass,charge,effweight);
     else AssignAssPtBins(pt,eta,phi,mass,charge,effweight);
   }
}

// ------------- Loop over all the tracks ---------------------
void DiHadronCorrelationMultiBase::LoopTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, int icharge)
{	
   //----- loop over tracks -----
   edm::Handle< reco::TrackCollection > tracks;
   iEvent.getByLabel(cutPara.trgtrackCollection.Data(), tracks);
   if( !tracks->size() ) { cout<<"Invalid or empty track collection!"<<endl; return; }

   for(unsigned it=0; it<tracks->size(); ++it){     
 
     const reco::Track & trk = (*tracks)[it];

     double pt  = trk.pt();
     if(pt<0.0001) continue;
     double eta = trk.eta();
     double phi = trk.phi();

     // tracks' proximity to best vertex
     math::XYZPoint bestvtx(xVtx,yVtx,zVtx);
     double dzvtx = trk.dz(bestvtx);
     double dxyvtx = trk.dxy(bestvtx);
     double dzerror = sqrt(trk.dzError()*trk.dzError()+zVtxError*zVtxError);
     double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+xVtxError*yVtxError);
/*
     double pterror = trk.ptError();
     double vx = trk.vx();
     double vy = trk.vy();
     double vz = trk.vz();
     int nhits = trk.numberOfValidHits();
     int algo = trk.algo();
     double chi2 = trk.chi2();
*/
//     double chi2n = trk.normalizedChi2();
//     int nlayers = trk.hitPattern().trackerLayersWithMeasurement();
     double charge = trk.charge();

     if(cutPara.IsPPTrkQuality)
     {

       if(!trk.quality(reco::TrackBase::highPurity)) continue;
       if(fabs(trk.ptError())/trk.pt() > 0.1) continue;
       if(fabs(dzvtx/dzerror) > 3.0) continue;
       if(fabs(dxyvtx/dxyerror) > 3.0) continue;
/*
       if(!trk.quality(reco::TrackBase::highPurity)) continue;
       if(fabs(trk.ptError())/trk.pt() > 0.05) continue;
       if(fabs(dzvtx/dzerror) > 100.0) continue;
       if(fabs(dxyvtx/dxyerror) > 100.0) continue;
       if(trk.numberOfValidHits()<11) continue;
       if(chi2n/nlayers>0.25) continue;
*/
     }

     if(cutPara.IsHITrkQuality && !trk.quality(reco::TrackBase::highPurity)) continue;

     if(cutPara.IsCheckV0Dau)
     {
       edm::Handle<reco::VertexCompositeCandidateCollection > v0candidates;
       if(cutPara.v0CandidateCollection.Contains("kshort")) iEvent.getByLabel(cutPara.v0CandidateCollection.Data(), "Kshort", v0candidates);
       if(cutPara.v0CandidateCollection.Contains("lambda")) iEvent.getByLabel(cutPara.v0CandidateCollection.Data(), "Lambda", v0candidates);

       if(!v0candidates->size()) return;
       for(unsigned it=0; it<v0candidates->size(); ++it)
       {
         const VertexCompositeCandidate& v0candidate = (*v0candidates)[it];

         const reco::Candidate * dau1 = v0candidate.daughter(0);
         const reco::Candidate * dau2 = v0candidate.daughter(1);       

         double eta_dau1 = dau1->eta();
         double phi_dau1 = dau1->phi();
         double pt_dau1 = dau1->pt();

         double eta_dau2 = dau2->eta();
         double phi_dau2 = dau2->phi();
         double pt_dau2 = dau2->pt();

         if(fabs(eta-eta_dau1)<0.03 && fabs(phi-phi_dau1)<0.03 && fabs(pt-pt_dau1)<0.01) { cout<<"found a Kshort dau1 match!"<<endl; continue; }
         if(fabs(eta-eta_dau2)<0.03 && fabs(phi-phi_dau2)<0.03 && fabs(pt-pt_dau2)<0.01) { cout<<"found a Kshort dau2 match!"<<endl; continue; }
       }
     }

     double effweight = GetEffWeight(eta,phi,pt,0.5*(cutPara.zvtxmax+cutPara.zvtxmin),hiCentrality,charge);
     double trgweight = GetTrgWeight(nMult);

     if(charge!=icharge && icharge!=-999) continue;
     if(istrg) AssignTrgPtBins(pt,eta,phi,cutPara.mass_trg,charge,effweight*trgweight);
     else AssignAssPtBins(pt,eta,phi,cutPara.mass_ass,charge,effweight*trgweight);
   }
}

void DiHadronCorrelationMultiBase::LoopCaloTower(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg)
{
   edm::Handle<CaloTowerCollection> calotowers;
   iEvent.getByLabel(std::string("towerMaker"), calotowers);
   if(!calotowers->size()) { cout<<"Invalid or empty calotower collection!"<<endl; return; }

   for(unsigned it=0; it<calotowers->size(); ++it){

     //const reco::Candidate & calotower = (*calotowers)[it];
     const CaloTower & calotower = (*calotowers)[it];

     double et  = calotower.et();
     if(et<0.01) continue;        
     double eta = calotower.eta();
     double phi = calotower.phi();
   //  et  = calotower.energy();
     double charge = 0;
     
//     if(calotower.energy()<3 && fabs(eta)>3) continue;

     double effweight = 1.0;

     if(istrg) AssignTrgPtBins(et,eta,phi,0,charge,effweight);
     else AssignAssPtBins(et,eta,phi,0,charge,effweight);
   }
}

void DiHadronCorrelationMultiBase::LoopV0Candidates(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg, TString candtype, int pdgID)
{
   edm::Handle<reco::VertexCompositeCandidateCollection > v0candidates;
   iEvent.getByLabel(cutPara.v0CandidateCollection.Data(),candtype.Data(), v0candidates);
   if(!v0candidates->size()) return;

   for(unsigned it=0; it<v0candidates->size(); ++it){

     const VertexCompositeCandidate& v0candidate = (*v0candidates)[it];

     double eta = v0candidate.eta();
     double phi = v0candidate.phi();
     double pt  = v0candidate.pt();
     double p = v0candidate.p();
     double pz = v0candidate.pz();
     double mass = v0candidate.mass();
     double charge = v0candidate.charge();
     int pdgid = v0candidate.pdgId();

     hV0InvMassVsPt->Fill(pt,mass);
     hV0InvEtaVsPt->Fill(pt,eta);
     hV0InvMassVsP->Fill(p,mass);
     hV0InvEtaVsP->Fill(p,eta);

     if(pdgID!=-1 && pdgid!=pdgID) continue;
 
     if(istrg && fabs(mass-cutPara.mass_trg)>0.02) continue;
     if(!istrg && fabs(mass-cutPara.mass_ass)>0.02) continue;

     const reco::Candidate * d1 = v0candidate.daughter(0);
     const reco::Candidate * d2 = v0candidate.daughter(1);
     
     TLorentzVector dau1vec(d1->px(),d1->py(),d1->pz(), d1->energy());
     TLorentzVector dau2vec(d2->px(),d2->py(),d2->pz(), d2->energy());

     TVector3 boost(-v0candidate.px()/v0candidate.energy(),-v0candidate.py()/v0candidate.energy(),-v0candidate.pz()/v0candidate.energy());
     dau1vec.Boost(boost);
     dau2vec.Boost(boost);

     TVector3 beam(0,0,1);
     TVector3 npol(boost.Cross(beam));
   
     if(d1->charge()>0) hThetaV0Plus->Fill(pz/4000.,cos(dau1vec.Angle(npol)));
     if(d1->charge()<0) hThetaV0Minus->Fill(pz/4000.,cos(dau1vec.Angle(npol)));

     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(pt,eta,phi,mass,charge,effweight);
     else AssignAssPtBins(pt,eta,phi,mass,charge,effweight);
   }
}

// ------------- Fill Vertex distribution ---------------------
void DiHadronCorrelationMultiBase::GetVertices(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    nVertices=0;
    maxofflinetracks=0;
    xVtx = -99999.9;
    yVtx = -99999.9;
    zVtx = -99999.9;
    xVtxError = -99999.9;
    yVtxError = -99999.9;
    zVtxError = -99999.9;

    edm::Handle< reco::VertexCollection > vertices;
    iEvent.getByLabel(cutPara.vertexCollection.Data(), vertices);
    if(!vertices->size()) { cout<<"Invalid or empty vertex collection!"<<endl; return; }

    for(unsigned int iv=0; iv<vertices->size(); ++iv)
    {
      const reco::Vertex & vtx = (*vertices)[iv];
      if(!vtx.isFake() && vtx.tracksSize()>=2) 
      { 
        nVertices++;
        if(vtx.tracksSize()>=maxofflinetracks)
        {
          xVtx = vtx.x();
          yVtx = vtx.y();
          zVtx = vtx.z();
          xVtxError = vtx.xError();
          yVtxError = vtx.yError();
          zVtxError = vtx.zError();

          maxofflinetracks = vtx.tracksSize();
        }
      }
    }
}

void DiHadronCorrelationMultiBase::AssignTrgPtBins(double pt, double eta, double phi, double mass, double charge, double effweight)
{
   if(cutPara.IsPtWeightTrg) effweight = effweight / pt;
   if(cutPara.IsDebug)
   {
     hdNdetadphiAll_trg->Fill(eta,phi);
     hdNdetadptAll_trg->Fill(eta,pt);
     hdNdetadphiCorrAll_trg->Fill(eta,phi,1.0/effweight);
     hdNdetadptCorrAll_trg->Fill(eta,pt,1.0/effweight);
     hPtAll_trg->Fill(pt,1.0/hPtAll_trg->GetBinWidth(hPtAll_trg->FindBin(pt)));
     hPtCorrAll_trg->Fill(pt,1./effweight/hPtAll_trg->GetBinWidth(hPtAll_trg->FindBin(pt)));
     double ptot = pt/sqrt(1-tanh(eta)*tanh(eta));
     hPTotAll_trg->Fill(ptot,1.0/hPTotAll_trg->GetBinWidth(hPTotAll_trg->FindBin(ptot)));
   }

   TLorentzVector pvector;
   pvector.SetPtEtaPhiM(pt,eta,phi,mass);
//   if(pt>0.4 && fabs(eta)<2.4) (eventcorr->pVect_all).push_back(pvector);
   for(int pttrgbin=0;pttrgbin<(int)(cutPara.pttrgmin.size());pttrgbin++)
   {
     if(GetPttrgBin(pt,eta,pttrgbin))
     {
       hpT_Signal_trg[pttrgbin]->Fill(pt);
       hpTCorr_Signal_trg[pttrgbin]->Fill(pt,1.0/effweight);
       if(cutPara.IsDebug)
       {
         hdNdetadphi_trg[pttrgbin]->Fill(eta,phi);
         hdNdetadphiCorr_trg[pttrgbin]->Fill(eta,phi,1.0/effweight);
       }
       nMultAll_trg++; nMultAllCorr_trg = nMultAllCorr_trg + 1.0/effweight;
       (eventcorr->pVect_trg[pttrgbin]).push_back(pvector);
       (eventcorr->chgVect_trg[pttrgbin]).push_back(charge);
       (eventcorr->effVect_trg[pttrgbin]).push_back(effweight);
    }
   }
}

void DiHadronCorrelationMultiBase::AssignAssPtBins(double pt, double eta, double phi, double mass, double charge, double effweight)
{
   if(cutPara.IsPtWeightAss) effweight = effweight / pt;

   if(cutPara.IsDebug)
   {
     hdNdetadphiAll_ass->Fill(eta,phi);
     hdNdetadptAll_ass->Fill(eta,pt);
     hdNdetadphiCorrAll_ass->Fill(eta,phi,1.0/effweight);
     hdNdetadptCorrAll_ass->Fill(eta,pt,1.0/effweight);
     hPtAll_ass->Fill(pt);
     hPtCorrAll_ass->Fill(pt,1.0/effweight);
     double ptot = pt/sqrt(1-tanh(eta)*tanh(eta));
     hPTotAll_ass->Fill(ptot,1.0/hPTotAll_ass->GetBinWidth(hPTotAll_ass->FindBin(ptot)));
   }

   TLorentzVector pvector;
   pvector.SetPtEtaPhiM(pt,eta,phi,mass);
   for(int ptassbin=0;ptassbin<(int)(cutPara.ptassmin.size());ptassbin++)
   {
     if(GetPtassBin(pt,eta,ptassbin))
     {
       hpT_Signal_ass[ptassbin]->Fill(pt);
       hpTCorr_Signal_ass[ptassbin]->Fill(pt,1.0/effweight);
       if(cutPara.IsDebug)
       {
         hdNdetadphi_ass[ptassbin]->Fill(eta,phi);
         hdNdetadphiCorr_ass[ptassbin]->Fill(eta,phi,1.0/effweight);
       }
       nMultAll_ass++; nMultAllCorr_ass = nMultAllCorr_ass + 1.0/effweight;
       (eventcorr->pVect_ass[ptassbin]).push_back(pvector); 
       (eventcorr->chgVect_ass[ptassbin]).push_back(charge);
       (eventcorr->effVect_ass[ptassbin]).push_back(effweight);
     }
   }
}

double DiHadronCorrelationMultiBase::GetEventEngineer(const edm::Event& iEvent, const edm::EventSetup& iSetup, int nn)
{
   edm::Handle<CaloTowerCollection> calotowers;
   iEvent.getByLabel(std::string("towerMaker"), calotowers);
   if(!calotowers->size()) { cout<<"Invalid or empty calotower collection!"<<endl; return -1; }

   double q2x=0;
   double q2y=0;
   double wsum=0;
   for(unsigned it=0; it<calotowers->size(); ++it){

     const CaloTower & calotower = (*calotowers)[it];

     double eta = calotower.eta();
     double phi = calotower.phi();
     double et  = calotower.et();

     if(calotower.energy()<3) continue;
     if(fabs(eta)<3) continue;

     q2x = q2x + et*cos(nn*phi);
     q2y = q2y + et*sin(nn*phi);
     wsum = wsum + et;
   }
   q2x = q2x / wsum;
   q2y = q2y / wsum;

   double q2 = sqrt(q2x*q2x+q2y*q2y);
   return q2;
}

int DiHadronCorrelationMultiBase::GetCentralityBin(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  if(!cent) cent = new CentralityProvider(iSetup);
  cent->newEvent(iEvent,iSetup);

//  double hf = cent->raw()->EtHFhitSum();
  hft = cent->raw()->EtHFtowerSum();
  npixel = cent->raw()->multiplicityPixel();
  zdc = cent->raw()->zdcSum();
//  double eb = cent->raw()->EtEBSum();
//  double eep = cent->raw()->EtEESumPlus();
//  double eem = cent->raw()->EtEESumMinus();
/*
    if(cutPara.IsDebug)
    {
      hHFTowerSum->Fill(hft);
      hHFvsNpixel->Fill(hft,npixel);
      hHFvsZDC->Fill(hft,zdc);
    }
*/
  int bin = cent->getBin();

// UCC centrality bins
  if(hft>3260 && npixel>51400 && cutPara.centmin==1000 && cutPara.centmax == 10000) bin=1000;
  if(hft>3400 && hft<3600 && npixel>51000 && npixel<57000 && cutPara.centmin==2000 && cutPara.centmax == 10000) bin=2000;
  if(hft>3400 && hft<3600 && npixel>51000 && npixel<57000 && zdc<2000 && cutPara.centmin==3000 && cutPara.centmax == 10000) bin=3000;
  if(hft>3129.3 && cutPara.centmin==500 && cutPara.centmax == 10000) bin=500;
  if(hft>3094.3 && npixel>48787 && cutPara.centmin==510 && cutPara.centmax == 10000) bin=510;
  if((7.0*hft+zdc)<36000 && cutPara.centmin==5000 && cutPara.centmax == 10000) bin=5000;
//  if((7.0*hft+zdc)<36000 && hft>3260 && npixel>51400 && cutPara.centmin==1100 && cutPara.centmax == 10000) bin=1100; // hft>3420 && npixel>31300 && 45*hft+zdc<188372
//  if((20.*hft+zdc)<114000 && hft>3400 && npixel>31000 && cutPara.centmin==1100 && cutPara.centmax == 10000) bin=1100;
  if((20.*hft+zdc)<114000 && hft>3420 && npixel>31500 && cutPara.centmin==1100 && cutPara.centmax == 10000) bin=1100;
  if((7.0*hft+zdc)<36000 && 1.15*hft>zdc && hft>3260 && npixel>51400 && cutPara.centmin==1200 && cutPara.centmax == 10000) bin=1200;
  if((7.0*hft+zdc)<36000 && hft>3393 && npixel>53450 && cutPara.centmin==2100 && cutPara.centmax == 10000) bin=2100;
  if((7.0*hft+zdc)<36000 && 1.15*hft>zdc && hft>3393 && npixel>53450 && cutPara.centmin==2200 && cutPara.centmax == 10000) bin=2200;
// pPb centrality bins
/*
  if(!cutPara.centralityCollection.Contains("pACentrality")) return bin;
  if(hft<10.) bin=0;  
  if(hft>10. && hft<20.) bin=1;
  if(hft>20. && hft<30.) bin=2;
  if(hft>30. && hft<40.) bin=3;
  if(hft>40. && hft<60.) bin=4;
  if(hft>60. && hft<80.) bin=5;
  if(hft>80. && hft<100.) bin=6;
  if(hft>100. && hft<120.) bin=7;
  if(hft>120. && hft<140.) bin=8;
  if(hft>140. && hft<155.) bin=9;
  if(hft>155. && hft<170.) bin=10;
  if(hft>170. && hft<190.) bin=11;
  if(hft>190. && hft<210.) bin=12;
  if(hft>210. && hft<250.) bin=13;
  if(hft>250.) bin=14;
*/
  return bin;
}

double DiHadronCorrelationMultiBase::GetDeltaEta(double eta_trg, double eta_ass)
{
        double deltaEta=eta_ass-eta_trg;
        return deltaEta;
}

double DiHadronCorrelationMultiBase::GetDeltaPhi(double phi_trg, double phi_ass)
{     
        double deltaPhi=phi_ass-phi_trg;
        if(deltaPhi>PI)
          deltaPhi=deltaPhi-2*PI;
        if(deltaPhi<-PI/2)
          deltaPhi=deltaPhi+2*PI;
        return deltaPhi;
}

bool DiHadronCorrelationMultiBase::GetPttrgBin(double pt, double eta, int itrg)
{
    if(pt>=cutPara.pttrgmin[itrg] && pt<=cutPara.pttrgmax[itrg] && eta>=cutPara.etatrgmin && eta<=cutPara.etatrgmax && !cutPara.IsTrgEtaCutAbs) 
      return kTRUE; 
    else if(pt>=cutPara.pttrgmin[itrg] && pt<=cutPara.pttrgmax[itrg] && fabs(eta)>=cutPara.etatrgmin && fabs(eta)<=cutPara.etatrgmax && cutPara.IsTrgEtaCutAbs)
      return kTRUE;
    else 
      return kFALSE;
}

bool DiHadronCorrelationMultiBase::GetPtassBin(double pt, double eta, int jass)
{
    if(pt>=cutPara.ptassmin[jass] && pt<=cutPara.ptassmax[jass] && eta>=cutPara.etaassmin && eta<=cutPara.etaassmax && !cutPara.IsAssEtaCutAbs) 
      return kTRUE;
    else if(pt>=cutPara.ptassmin[jass] && pt<=cutPara.ptassmax[jass] && fabs(eta)>=cutPara.etaassmin && fabs(eta)<=cutPara.etaassmax && cutPara.IsAssEtaCutAbs)
      return kTRUE;
    else 
      return kFALSE;
}

double DiHadronCorrelationMultiBase::GetTrgWeight(double nmult)
{
  double trgweight=1.0;
  if(hTrgWeight) trgweight = hTrgWeight->GetBinContent(hTrgWeight->FindBin(nmult));
  return trgweight;
}

double DiHadronCorrelationMultiBase::GetEffWeight(double eta, double phi, double pt, double zvtx, int centbin, double charge)
{
//  if(pt>2.0) pt=2.0;
  double effweight = 1.0;
  if(hEffWeight) 
  {
    if(!cutPara.IsHI) effweight = hEffWeight->GetBinContent(hEffWeight->FindBin(eta,pt));
    else effweight = hEffWeight->GetBinContent(hEffWeight->FindBin(eta,pt,centbin));
    if(effweight<0.005) effweight=1.0;
  }
  if(hEtaPhiWeightPos && charge>0) effweight *= hEtaPhiWeightPos->GetBinContent(hEtaPhiWeightPos->FindBin(eta,phi));
  if(hEtaPhiWeightNeg && charge<0) effweight *= hEtaPhiWeightNeg->GetBinContent(hEtaPhiWeightNeg->FindBin(eta,phi));

  return effweight;
}

DiHadronCorrelationMultiBase::ParticleType DiHadronCorrelationMultiBase::GetParticleID(TString particleid)
{
  ParticleType type;
  if(particleid == "GenParticle")
    type=kGenParticle;
  else if(particleid == "Track")
    type=kTrack;
  else if(particleid == "TrackP")
    type=kTrackP;
  else if(particleid == "TrackM")
    type=kTrackM;
  else if(particleid == "Jet")
    type=kJet;
  else if(particleid == "Muon")
    type=kMuon;
  else if(particleid == "Photon")
    type=kPhoton;
  else if(particleid == "EcalSC")
    type=kEcalSC;
  else if(particleid == "EcalBC")
    type=kEcalBC;
  else if(particleid == "PFHadron")
    type=kPFHadron;
  else if(particleid == "PFPhoton")
    type=kPFPhoton;  
  else if(particleid == "PFHadronPhoton")
    type=kPFHadronPhoton;
  else if(particleid == "PFPhotonTrack")
    type=kPFPhotonTrack;
  else if(particleid == "PFElectron")
    type=kPFElectron;
  else if(particleid == "PFMuon")
    type=kPFMuon;
  else if(particleid == "PFNeutral")
    type=kPFNeutral;
  else if(particleid == "PFHadronHF")
    type=kPFHadronHF;
  else if(particleid == "PFEgammaHF")
    type=kPFEgammaHF;
  else if(particleid == "PionZero")
    type=kPionZero;
  else if(particleid == "PionZeroBkgUp")
    type=kPionZeroBkgUp;
  else if(particleid == "PionZeroBkgDown")
    type=kPionZeroBkgDown;
  else if(particleid == "CaloTower")
    type=kCaloTower;
  else if(particleid == "EcalRecHit")
    type=kEcalRecHit;
  else if(particleid == "HcalRecHit")
    type=kHcalRecHit;
  else if(particleid == "Kshort")
    type=kKshort;
  else if(particleid == "Lambda")
    type=kLambda;
  else if(particleid == "LambdaP")
    type=kLambdaP;
  else if(particleid == "LambdaM")
    type=kLambdaM;
  else if(particleid == "D0")
    type=kD0;
  return type;
}
