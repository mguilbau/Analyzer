//
// Package:    V0Validator
// Class:      V0Validator
// 
/**\class V0Validator V0Validator.cc Validation/RecoVertex/src/V0Validator.cc

 Description: Creates validation histograms for RecoVertex/V0Producer

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Brian Drell
//         Created:  Wed Feb 18 17:21:04 MST 2009
// $Id: V0Validator.cc,v 1.7 2010/03/18 13:30:11 drell Exp $
//
//


#include "FlowCorrAna/V0Analysis/interface/V0Validator.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

typedef std::vector<TrackingVertex> TrackingVertexCollection;
typedef edm::Ref<TrackingVertexCollection> TrackingVertexRef;
typedef edm::RefVector<edm::HepMCProduct, HepMC::GenVertex > GenVertexRefVector;
typedef edm::RefVector<edm::HepMCProduct, HepMC::GenParticle > GenParticleRefVector;

const double piMass = 0.13957018;
const double piMassSquared = piMass*piMass;
const double protonMass = 0.93827203;
const double protonMassSquared = protonMass*protonMass;

V0Validator::V0Validator(const edm::ParameterSet& iConfig) : 
  trackCollectionTag(iConfig.getParameter<edm::InputTag>("trackCollection")),
  vertexCollectionTag(iConfig.getParameter<edm::InputTag>("vertexCollection")),
  genParticleCollectionTag(iConfig.getParameter<edm::InputTag>("genParticleCollection")),
  k0sCollectionTag(iConfig.getParameter<edm::InputTag>("kShortCollection")),
  lamCollectionTag(iConfig.getParameter<edm::InputTag>("lambdaCollection")),
  isMatchByHitsOrChi2_(iConfig.getParameter<bool>("isMatchByHitsOrChi2")),
  isMergedTruth_(iConfig.getParameter<bool>("isMergedTruth"))
{
    genLam = genK0s = realLamFoundEff = realK0sFoundEff = lamCandFound = 
    k0sCandFound = noTPforK0sCand = noTPforLamCand = realK0sFound = realLamFound = 0;
}


V0Validator::~V0Validator() {

}

void V0Validator::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup) {
  //std::cout << "Running V0Validator" << std::endl;
  //theDQMstore = edm::Service<DQMStore>().operator->();
  //std::cout << "In beginJob() at line 1" << std::endl;
  //edm::Service<TFileService> fs;

  TH1::SetDefaultSumw2();

  const double small = 1e-3;
  double pt;
  for(pt =   0  ; pt <   2.0-small; pt +=  0.2 ) ptBins.push_back(pt); 
  for(pt =   2.0; pt <   3.2-small; pt +=  0.6 ) ptBins.push_back(pt); 
  for(pt =   3.2; pt <   4.2-small; pt +=  1.0 ) ptBins.push_back(pt);
  for(pt =   4.2; pt <   6.0-small; pt +=  1.8 ) ptBins.push_back(pt);
  for(pt =   6.0; pt <   9.0-small; pt +=  3.0 ) ptBins.push_back(pt);  
  ptBins.push_back(9.0);
  ptBins.push_back(15.0);

  double etaMin   = -3.0;
  double etaMax   =  3.0;
  double etaWidth =  0.5;
  for(double eta = etaMin; eta < etaMax + etaWidth/2; eta += etaWidth)
    etaBins.push_back(eta);

  ksGenVsEtaPt = theDQMstore->make<TH2D>("K0sGenVsEtaPt",
                           "Generated K^{0}_{S} vs #eta and p_{T}", etaBins.size()-1, &etaBins[0], ptBins.size()-1, &ptBins[0]);
  lamGenVsEtaPt = theDQMstore->make<TH2D>("LamGenVsEtaPt",
                           "Generated #Lambda^{0} vs #eta and p_{T}", etaBins.size()-1, &etaBins[0], ptBins.size()-1, &ptBins[0]);

  ksEffVsR_num = theDQMstore->make<TH1D>("K0sEffVsR_num", 
			  "K^{0}_{S} Efficiency vs #rho", 40, 0., 40.);
  ksEffVsEta_num = theDQMstore->make<TH1D>("K0sEffVsEta_num",
			    "K^{0}_{S} Efficiency vs #eta", 40, -2.5, 2.5);
  ksEffVsPt_num = theDQMstore->make<TH1D>("K0sEffVsPt_num",
			   "K^{0}_{S} Efficiency vs p_{T}", 70, 0., 20.);
  ksEffVsPtR_num = theDQMstore->make<TH2D>("K0sEffVsPtR_num",
                           "K^{0}_{S} Efficiency vs R and p_{T}", 40, 0., 40., 100, 0, 10.);
  ksEffVsEtaR_num = theDQMstore->make<TH2D>("K0sEffVsEtaR_num",
                           "K^{0}_{S} Efficiency vs R and #eta", 40, 0., 40., 40, -2.5, 2.5);
  ksEffVsEtaPt_num = theDQMstore->make<TH2D>("K0sEffVsEtaPt_num",
                           "K^{0}_{S} Efficiency vs #eta and p_{T}", etaBins.size()-1, &etaBins[0], ptBins.size()-1, &ptBins[0]);

  ksTkEffVsR_num = theDQMstore->make<TH1D>("K0sTkEffVsR_num", 
			  "K^{0}_{S} Tracking Efficiency vs #rho", 40, 0., 40.);
  ksTkEffVsEta_num = theDQMstore->make<TH1D>("K0sTkEffVsEta_num",
			    "K^{0}_{S} Tracking Efficiency vs #eta", 40, -2.5, 2.5);
  ksTkEffVsPt_num = theDQMstore->make<TH1D>("K0sTkEffVsPt_num",
			   "K^{0}_{S} Tracking Efficiency vs p_{T}", 70, 0., 20.);
  ksTkEffVsEtaPt_num = theDQMstore->make<TH2D>("K0sTkEffVsEtaPt_num",
                           "K^{0}_{S} Tracking Efficiency vs #eta and p_{T}", etaBins.size()-1, &etaBins[0], ptBins.size()-1, &ptBins[0]);

  ksEffVsR_denom = theDQMstore->make<TH1D>("K0sEffVsR_denom", 
			  "K^{0}_{S} Efficiency vs #rho", 40, 0., 40.);
  ksEffVsEta_denom = theDQMstore->make<TH1D>("K0sEffVsEta_denom",
			    "K^{0}_{S} Efficiency vs #eta", 40, -2.5, 2.5);
  ksEffVsPt_denom = theDQMstore->make<TH1D>("K0sEffVsPt_denom",
			   "K^{0}_{S} Efficiency vs p_{T}", 70, 0., 20.);
  ksEffVsPtR_denom = theDQMstore->make<TH2D>("K0sEffVsPtR_denom",
                           "K^{0}_{S} Efficiency vs R and p_{T}", 40, 0., 40., 100, 0, 10.);
  ksEffVsEtaR_denom = theDQMstore->make<TH2D>("K0sEffVsEtaR_denom",
                           "K^{0}_{S} Efficiency vs R and #eta", 40, 0., 40., 40, -2.5, 2.5);
  ksEffVsEtaPt_denom = theDQMstore->make<TH2D>("K0sEffVsEtaPt_denom",
                           "K^{0}_{S} Efficiency vs #eta and p_{T}", etaBins.size()-1, &etaBins[0], ptBins.size()-1, &ptBins[0]);

  lamEffVsR_num = theDQMstore->make<TH1D>("LamEffVsR_num",
			   "#Lambda^{0} Efficiency vs #rho", 40, 0., 40.);
  lamEffVsEta_num = theDQMstore->make<TH1D>("LamEffVsEta_num",
			     "#Lambda^{0} Efficiency vs #eta", 40, -2.5, 2.5);
  lamEffVsPt_num = theDQMstore->make<TH1D>("LamEffVsPt_num",
			    "#Lambda^{0} Efficiency vs p_{T}", 70, 0., 20.);
  lamEffVsPtR_num = theDQMstore->make<TH2D>("LamEffVsPtR_num",
                           "#Lambda^{0} Efficiency vs R and p_{T}", 40, 0., 40., 100, 0, 10.);
  lamEffVsEtaR_num = theDQMstore->make<TH2D>("LamEffVsEtaR_num",
                           "#Lambda^{0} Efficiency vs R and #eta", 40, 0., 40., 40, -2.5, 2.5);
  lamEffVsEtaPt_num = theDQMstore->make<TH2D>("LamEffVsEtaPt_num",
                           "#Lambda^{0} Efficiency vs #eta and p_{T}", etaBins.size()-1, &etaBins[0], ptBins.size()-1, &ptBins[0]);

  lamTkEffVsR_num = theDQMstore->make<TH1D>("LamTkEffVsR_num",
			   "#Lambda^{0} TrackingEfficiency vs #rho", 40, 0., 40.);
  lamTkEffVsEta_num = theDQMstore->make<TH1D>("LamTkEffVsEta_num",
			     "#Lambda^{0} Tracking Efficiency vs #eta", 40, -2.5, 2.5);
  lamTkEffVsPt_num = theDQMstore->make<TH1D>("LamTkEffVsPt_num",
			    "#Lambda^{0} Tracking Efficiency vs p_{T}", 70, 0., 20.);
  lamTkEffVsEtaPt_num = theDQMstore->make<TH2D>("LamTkEffVsEtaPt_num",
                           "#Lambda^{0} Efficiency vs #eta and p_{T}", etaBins.size()-1, &etaBins[0], ptBins.size()-1, &ptBins[0]);

  lamEffVsR_denom = theDQMstore->make<TH1D>("LamEffVsR_denom",
			   "#Lambda^{0} Efficiency vs #rho", 40, 0., 40.);
  lamEffVsEta_denom = theDQMstore->make<TH1D>("LamEffVsEta_denom",
			     "#Lambda^{0} Efficiency vs #eta", 40, -2.5, 2.5);
  lamEffVsPt_denom = theDQMstore->make<TH1D>("LamEffVsPt_denom",
			    "#Lambda^{0} Efficiency vs p_{T}", 70, 0., 20.);
  lamEffVsPtR_denom = theDQMstore->make<TH2D>("LamEffVsPtR_denom",
                           "#Lambda^{0} Efficiency vs R and p_{T}", 40, 0., 40., 100, 0, 10.);
  lamEffVsEtaR_denom = theDQMstore->make<TH2D>("LamEffVsEtaR_denom",
                           "#Lambda^{0} Efficiency vs R and #eta", 40, 0., 40., 40, -2.5, 2.5);
  lamEffVsEtaPt_denom = theDQMstore->make<TH2D>("LamEffVsEtaPt_denom",
                           "#Lambda^{0} Efficiency vs #eta and p_{T}", etaBins.size()-1, &etaBins[0], ptBins.size()-1, &ptBins[0]);
  lamEffVsPt_denom_test = theDQMstore->make<TH1D>("LamEffVsPt_denom_test",
                            "#Lambda^{0} Efficiency vs p_{T}", 70, 0., 20.);
  lamEffVsEtaPt_denom_test = theDQMstore->make<TH2D>("LamEffVsEtaPt_denom_test",
                           "#Lambda^{0} Efficiency vs #eta and p_{T}", etaBins.size()-1, &etaBins[0], ptBins.size()-1, &ptBins[0]);

  ksFakeVsR_num = theDQMstore->make<TH1D>("K0sFakeVsR_num",
			   "K^{0}_{S} Fake Rate vs #rho", 40, 0., 40.);
  ksFakeVsEta_num = theDQMstore->make<TH1D>("K0sFakeVsEta_num",
			     "K^{0}_{S} Fake Rate vs #eta", 40, -2.5, 2.5);
  ksFakeVsPt_num = theDQMstore->make<TH1D>("K0sFakeVsPt_num",
			    "K^{0}_{S} Fake Rate vs p_{T}", 70, 0., 20.);
  ksSecVsR_num = theDQMstore->make<TH1D>("K0sSecVsR_num",
                           "K^{0}_{S} Secondary Rate vs #rho", 40, 0., 40.);
  ksSecVsEta_num = theDQMstore->make<TH1D>("K0sSecVsEta_num",
                             "K^{0}_{S} Secondary Rate vs #eta", 40, -2.5, 2.5);
  ksSecVsPt_num = theDQMstore->make<TH1D>("K0sSecVsPt_num",
                            "K^{0}_{S} Secondary Rate vs p_{T}", 70, 0., 20.);
  ksTkFakeVsR_num = theDQMstore->make<TH1D>("K0sTkFakeVsR_num",
			   "K^{0}_{S} Tracking Fake Rate vs #rho", 40, 0., 40.);
  ksTkFakeVsEta_num = theDQMstore->make<TH1D>("K0sTkFakeVsEta_num",
			     "K^{0}_{S} Tracking Fake Rate vs #eta", 40, -2.5, 2.5);
  ksTkFakeVsPt_num = theDQMstore->make<TH1D>("K0sTkFakeVsPt_num",
			    "K^{0}_{S} Tracking Fake Rate vs p_{T}", 70, 0., 20.);

  ksFakeVsR_denom = theDQMstore->make<TH1D>("K0sFakeVsR_denom",
			   "K^{0}_{S} Fake Rate vs #rho", 40, 0., 40.);
  ksFakeVsEta_denom = theDQMstore->make<TH1D>("K0sFakeVsEta_denom",
			     "K^{0}_{S} Fake Rate vs #eta", 40, -2.5, 2.5);
  ksFakeVsPt_denom = theDQMstore->make<TH1D>("K0sFakeVsPt_denom",
			    "K^{0}_{S} Fake Rate vs p_{T}", 70, 0., 20.);

  lamFakeVsR_num = theDQMstore->make<TH1D>("LamFakeVsR_num",
			    "#Lambda^{0} Fake Rate vs #rho", 40, 0., 40.);
  lamFakeVsEta_num = theDQMstore->make<TH1D>("LamFakeVsEta_num",
			      "#Lambda^{0} Fake Rate vs #eta", 40, -2.5, 2.5);
  lamFakeVsPt_num = theDQMstore->make<TH1D>("LamFakeVsPt_num",
			     "#Lambda^{0} Fake Rate vs p_{T}", 70, 0., 20.);
  lamCascadeVsR_num = theDQMstore->make<TH1D>("LamCascadeVsR_num",
                            "#Lambda^{0} cascade Rate vs #rho", 40, 0., 40.);
  lamCascadeVsEta_num = theDQMstore->make<TH1D>("LamCascadeVsEta_num", 
                              "#Lambda^{0} cascade Rate vs #eta", 40, -2.5, 2.5);
  lamCascadeVsPt_num = theDQMstore->make<TH1D>("LamCascadeVsPt_num",
                             "#Lambda^{0} cascade Rate vs p_{T}", 70, 0., 20.);
  lamSecVsR_num = theDQMstore->make<TH1D>("LamSecVsR_num",
                            "#Lambda^{0} Secondary Rate vs #rho", 40, 0., 40.);
  lamSecVsEta_num = theDQMstore->make<TH1D>("LamSecVsEta_num",
                              "#Lambda^{0} Secondary Rate vs #eta", 40, -2.5, 2.5);
  lamSecVsPt_num = theDQMstore->make<TH1D>("LamSecVsPt_num",
                             "#Lambda^{0} Secondary Rate vs p_{T}", 70, 0., 20.);
  lamTkFakeVsR_num = theDQMstore->make<TH1D>("LamTkFakeVsR_num",
			    "#Lambda^{0} Tracking Fake Rate vs #rho", 40, 0., 40.);
  lamTkFakeVsEta_num = theDQMstore->make<TH1D>("LamTkFakeVsEta_num",
			      "#Lambda^{0} Tracking Fake Rate vs #eta", 40, -2.5, 2.5);
  lamTkFakeVsPt_num = theDQMstore->make<TH1D>("LamTkFakeVsPt_num",
			     "#Lambda^{0} Tracking Fake Rate vs p_{T}", 70, 0., 20.);

  lamFakeVsR_denom = theDQMstore->make<TH1D>("LamFakeVsR_denom",
			    "#Lambda^{0} Fake Rate vs #rho", 40, 0., 40.);
  lamFakeVsEta_denom = theDQMstore->make<TH1D>("LamFakeVsEta_denom",
			      "#Lambda^{0} Fake Rate vs #eta", 40, -2.5, 2.5);
  lamFakeVsPt_denom = theDQMstore->make<TH1D>("LamFakeVsPt_denom",
			     "#Lambda^{0} Fake Rate vs p_{T}", 70, 0., 20.);

  nKs = theDQMstore->make<TH1D>("nK0s",
		     "Number of K^{0}_{S} found per event", 60, 0., 60.);
  nLam = theDQMstore->make<TH1D>("nLam",
		      "Number of #Lambda^{0} found per event", 60, 0., 60.);

  ksXResolution = theDQMstore->make<TH1D>("ksXResolution",
			       "Resolution of V0 decay vertex X coordinate", 50, 0., 50.);
  ksYResolution = theDQMstore->make<TH1D>("ksYResolution",
			       "Resolution of V0 decay vertex Y coordinate", 50, 0., 50.);
  ksZResolution = theDQMstore->make<TH1D>("ksZResolution",
			       "Resolution of V0 decay vertex Z coordinate", 50, 0., 50.);
  lamXResolution = theDQMstore->make<TH1D>("lamXResolution",
				"Resolution of V0 decay vertex X coordinate", 50, 0., 50.);
  lamYResolution = theDQMstore->make<TH1D>("lamYResolution",
				"Resolution of V0 decay vertex Y coordinate", 50, 0., 50.);
  lamZResolution = theDQMstore->make<TH1D>("lamZResolution",
				"Resolution of V0 decay vertex Z coordinate", 50, 0., 50.);
  ksAbsoluteDistResolution = theDQMstore->make<TH1D>("ksRResolution",
					  "Resolution of absolute distance from primary vertex to V0 vertex",
					  100, 0., 50.);
  lamAbsoluteDistResolution = theDQMstore->make<TH1D>("lamRResolution",
					   "Resolution of absolute distance from primary vertex to V0 vertex",
					   100, 0., 50.);

  ksCandStatus = theDQMstore->make<TH1D>("ksCandStatus",
			  "Fake type by cand status",
			  30, 0., 30.);
  lamCandStatus = theDQMstore->make<TH1D>("lamCandStatus",
			  "Fake type by cand status",
			  30, 0., 30.);

  double minKsMass = 0.49767 - 0.2;
  double maxKsMass = 0.49767 + 0.2;
  double minLamMass = 1.1156 - 0.2;
  double maxLamMass = 1.1156 + 0.2;
  int ksMassNbins = 800;
  double ksMassXmin = minKsMass;
  double ksMassXmax = maxKsMass;
  int lamMassNbins = 800;
  double lamMassXmin = minLamMass;
  double lamMassXmax = maxLamMass;

  fakeKsMass = theDQMstore->make<TH1D>("ksMassFake",
			     "Mass of fake K0S",
			     ksMassNbins, minKsMass, maxKsMass);
  goodKsMass = theDQMstore->make<TH1D>("ksMassGood",
			     "Mass of good reco K0S",
			     ksMassNbins, minKsMass, maxKsMass);
  fakeLamMass = theDQMstore->make<TH1D>("lamMassFake",
			      "Mass of fake Lambda",
			      lamMassNbins, minLamMass, maxLamMass);
  goodLamMass = theDQMstore->make<TH1D>("lamMassGood",
			      "Mass of good Lambda",
			      lamMassNbins, minLamMass, maxLamMass);
  fakeKsMassPt = theDQMstore->make<TH2D>("ksMassPtFake",
                             "Mass vs p_{T} of fake K0S",
                             120, 0, 12.0, ksMassNbins, minKsMass, maxKsMass);
  goodKsMassPt = theDQMstore->make<TH2D>("ksMassPtGood",
                             "Mass vs p_{T} of good K0S",
                             120, 0, 12.0, ksMassNbins, minKsMass, maxKsMass);
  fakeLamMassPt = theDQMstore->make<TH2D>("lamMassPtFake",
                              "Mass vs p_{T} of fake Lambda",
                              120, 0, 12.0, lamMassNbins, minLamMass, maxLamMass);
  goodLamMassPt = theDQMstore->make<TH2D>("lamMassPtGood",
                              "Mass vs p_{T} of good Lambda",
                              120, 0, 12.0, lamMassNbins, minLamMass, maxLamMass);

  ksEtaPtAll = theDQMstore->make<TH2D>("ksEtaPtAll",
                                  "#eta vs p_{T} of all K0S",
                                  128, -3.2, 3.2, 12, 0, 6.0);
  lamEtaPtAll = theDQMstore->make<TH2D>("lamEtaPtAll",
                                  "#eta vs p_{T} of all #Lambda^{0}",
                                  128, -3.2, 3.2, 12, 0, 6.0);
  ksMassAll = theDQMstore->make<TH1D>("ksMassAll",
				  "Invariant mass of all K0S",
				  ksMassNbins, ksMassXmin, ksMassXmax);
  lamMassAll = theDQMstore->make<TH1D>("lamMassAll",
				   "Invariant mass of all #Lambda^{0}",
				   lamMassNbins, lamMassXmin, lamMassXmax);
  ksMassPtAll = theDQMstore->make<TH2D>("ksMassPtAll",
                                  "Invariant mass vs p_{T} of all K0S", 
                                  120, 0, 12.0, ksMassNbins, ksMassXmin, ksMassXmax);
  lamMassPtAll = theDQMstore->make<TH2D>("lamMassPtAll",
                                   "Invariant mass vs p_{T} of all #Lambda^{0}",
                                   120, 0, 12.0, lamMassNbins, lamMassXmin, lamMassXmax);
  for(int i=0;i<12;i++)
  {
    ksMassPtAllEta[i] = theDQMstore->make<TH2D>(Form("ksMassPtAllEta%d",i+1),
                                  "Invariant mass vs p_{T} of all K0S",
                                  120, 0, 12.0, ksMassNbins, ksMassXmin, ksMassXmax);
    lamMassPtAllEta[i] = theDQMstore->make<TH2D>(Form("lamMassPtAllEta%d",i+1),
                                   "Invariant mass vs p_{T} of all #Lambda^{0}",
                                   120, 0, 12.0, lamMassNbins, lamMassXmin, lamMassXmax);
  }

  ksFakeDauRadDist = theDQMstore->make<TH1D>("radDistFakeKs",
				   "Production radius of daughter particle of Ks fake",
				   100, 0., 15.);
  lamFakeDauRadDist = theDQMstore->make<TH1D>("radDistFakeLam",
				    "Production radius of daughter particle of Lam fake",
				    100, 0., 15.);

  ksResolutionPt = theDQMstore->make<TH2D>("ksResolutionPt",
                                    "K0s pT resolution",
                                    120, 0, 12.0, 100, -0.5, 0.5); 
  lamResolutionPt = theDQMstore->make<TH2D>("lamResolutionPt",
                                    "Lambda pT resolution",
                                    120, 0, 12.0, 100, -0.5, 0.5); 
}

void V0Validator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  using std::cout;
  using std::endl;
  using namespace edm;
  using namespace std;
  using namespace reco;

  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByLabel("offlinePrimaryVertices",vertices);
  double bestvz=-999.9;// bestvx=-999.9, bestvy=-999.9;
//  double bestvzError=-999.9, bestvxError=-999.9, bestvyError=-999.9;
  const reco::Vertex & vtx = (*vertices)[0];
  bestvz = vtx.z(); //bestvx = vtx.x(); bestvy = vtx.y();
//  bestvzError = vtx.zError(); bestvxError = vtx.xError(); bestvyError = vtx.yError();

  if(bestvz < -15.0 || bestvz>15.0) return;

  // Get event setup info, B-field and tracker geometry
//  ESHandle<MagneticField> bFieldHandle;
//  iSetup.get<IdealMagneticFieldRecord>().get(bFieldHandle);
//  ESHandle<GlobalTrackingGeometry> globTkGeomHandle;
//  iSetup.get<GlobalTrackingGeometryRecord>().get(globTkGeomHandle);

  // Make matching collections
  //reco::RecoToSimCollection recSimColl;
  //reco::SimToRecoCollection simRecColl;
  /* 
  Handle<reco::RecoToSimCollection > recotosimH;
  iEvent.getByLabel("trackingParticleRecoTrackAsssociation", recotosimH);
  reco::RecoToSimCollection recotosimCollectionH = *( recotosimH.product() ); 
  
  Handle<reco::SimToRecoCollection> simtorecoH;
  iEvent.getByLabel("trackingParticleRecoTrackAsssociation", simtorecoH);
  reco::SimToRecoCollection simtorecoCollectionH = *( simtorecoH.product() );
*/

  //////////////////////////////////
  // Fill generated V0 candidates //
  //////////////////////////////////

  edm::Handle<reco::GenParticleCollection> genParticleCollection;
  iEvent.getByLabel(genParticleCollectionTag, genParticleCollection);

  for(unsigned it=0; it<genParticleCollection->size(); ++it) {

    const reco::GenParticle & genCand = (*genParticleCollection)[it];
    int id = genCand.pdgId();

    double eta = genCand.rapidity()+0.47;
    double pt  = genCand.pt();

    if(fabs(id)==310) ksGenVsEtaPt->Fill(eta,pt);

    double mid=0;
    if(fabs(id)==3122){
      if(genCand.numberOfMothers()==1){
        const reco::Candidate * mom = genCand.mother();
        mid = mom->pdgId();
        if(mom->numberOfMothers()==1){
          const reco::Candidate * mom1 = mom->mother();
          mid = mom1->pdgId();
        }
      }
      if(fabs(mid)==3322 || fabs(mid)==3312 || fabs(mid)==3324 || fabs(mid)==3314 || fabs(mid)==3334) {continue;}
      lamGenVsEtaPt->Fill(eta,pt);
    }
  }

  //get the V0s;   
  edm::Handle<reco::VertexCompositeCandidateCollection> k0sCollection;
  edm::Handle<reco::VertexCompositeCandidateCollection> lambdaCollection;
  iEvent.getByLabel(k0sCollectionTag, k0sCollection);
  iEvent.getByLabel(lamCollectionTag, lambdaCollection);
  double mass = 0.;
  if ( k0sCollection.isValid() && k0sCollection->size() > 0 ) {
    for( reco::VertexCompositeCandidateCollection::const_iterator iK0s = k0sCollection->begin();
         iK0s != k0sCollection->end();
         iK0s++) {
      // Fill values to be histogrammed
      K0sCandpT = (sqrt( iK0s->momentum().perp2() ));
      K0sCandEta = iK0s->rapidity()+0.47;
//      K0sCandEta = iK0s->momentum().eta();
      mass = iK0s->mass();

      ksEtaPtAll->Fill( K0sCandEta, K0sCandpT );
      if(K0sCandEta>-3.0 && K0sCandEta<3.0) ksMassAll->Fill( mass );
      if(K0sCandEta>-3.0 && K0sCandEta<3.0) ksMassPtAll->Fill( K0sCandpT, mass );
      for(int i=0;i<12;i++)
        if(K0sCandEta>etaBins[i] && K0sCandEta<etaBins[i+1]) ksMassPtAllEta[i]->Fill( K0sCandpT, mass ); 
    }
  }
  if ( lambdaCollection.isValid() && lambdaCollection->size() > 0 ) {
    vector<reco::TrackRef> theDaughterTracks;
    for( reco::VertexCompositeCandidateCollection::const_iterator iLam = lambdaCollection->begin();
         iLam != lambdaCollection->end();
         iLam++) {
      // Fill values to be histogrammed
      LamCandpT = (sqrt( iLam->momentum().perp2() ));
      LamCandEta = iLam->rapidity()+0.47;
//      LamCandEta = iLam->momentum().eta();
      mass = iLam->mass();

      lamEtaPtAll->Fill( LamCandEta, LamCandpT );
      if(LamCandEta>-3. && LamCandEta<3.) lamMassAll->Fill( mass );
      if(LamCandEta>-3. && LamCandEta<3.) lamMassPtAll->Fill( LamCandpT, mass );
      for(int i=0;i<12;i++)
        if(LamCandEta>etaBins[i] && LamCandEta<etaBins[i+1]) lamMassPtAllEta[i]->Fill( LamCandEta, mass );
    }
  }

  if(!isMergedTruth_) return;

  edm::Handle<TrackingParticleCollection>  TPCollectionEff ;
  iEvent.getByLabel("mergedtruth", "MergedTrackTruth", TPCollectionEff);
  const TrackingParticleCollection tPCeff = *( TPCollectionEff.product() );

  edm::ESHandle<TrackAssociatorBase> associatorByHits;
  iSetup.get<TrackAssociatorRecord>().get("TrackAssociatorByHits", associatorByHits);

  edm::ESHandle<TrackAssociatorBase> associatorByChi2;
  iSetup.get<TrackAssociatorRecord>().get("TrackAssociatorByChi2", associatorByChi2);

  // Get tracks
  Handle< View<reco::Track> > trackCollectionH;
  iEvent.getByLabel(trackCollectionTag, trackCollectionH);

  Handle<SimTrackContainer> simTrackCollection;
  iEvent.getByLabel("g4SimHits", simTrackCollection);
  const SimTrackContainer simTC = *(simTrackCollection.product());

  Handle<SimVertexContainer> simVertexCollection;
  iEvent.getByLabel("g4SimHits", simVertexCollection);
  const SimVertexContainer simVC = *(simVertexCollection.product());

  //Get tracking particles
  //  -->tracks
  edm::Handle<TrackingParticleCollection>  TPCollectionH ;
  iEvent.getByLabel("mergedtruth", "MergedTrackTruth", TPCollectionH);
  const View<reco::Track>  tC = *( trackCollectionH.product() );

  // Select the primary vertex, create a new reco::Vertex to hold it
  edm::Handle< std::vector<reco::Vertex> > primaryVtxCollectionH;
  iEvent.getByLabel(vertexCollectionTag, primaryVtxCollectionH);
  const reco::VertexCollection primaryVertexCollection   = *(primaryVtxCollectionH.product());

  reco::Vertex* thePrimary = 0;
  std::vector<reco::Vertex>::const_iterator iVtxPH = primaryVtxCollectionH->begin();
  for(std::vector<reco::Vertex>::const_iterator iVtx = primaryVtxCollectionH->begin();
      iVtx < primaryVtxCollectionH->end();
      iVtx++) {
    if(primaryVtxCollectionH->size() > 1) {
      if(iVtx->tracksSize() > iVtxPH->tracksSize()) {
	iVtxPH = iVtx;
      }
    }
    else iVtxPH = iVtx;
  }
  thePrimary = new reco::Vertex(*iVtxPH);

  //cout << "Done with collections, associating reco and sim..." << endl;
 
  reco::RecoToSimCollection recotosimCollectionH;
  reco::SimToRecoCollection simtorecoCollectionH;

  if(isMatchByHitsOrChi2_) {
    recotosimCollectionH = associatorByHits->associateRecoToSim(trackCollectionH,TPCollectionH,&iEvent,&iSetup );
    simtorecoCollectionH = associatorByHits->associateSimToReco(trackCollectionH,TPCollectionH,&iEvent,&iSetup );
  }
  else {
    recotosimCollectionH = associatorByChi2->associateRecoToSim(trackCollectionH,TPCollectionH,&iEvent,&iSetup );
    simtorecoCollectionH = associatorByChi2->associateSimToReco(trackCollectionH,TPCollectionH,&iEvent,&iSetup );
  }
//  reco::VertexRecoToSimCollection vr2s = associatorByTracks->associateRecoToSim(primaryVtxCollectionH, TVCollectionH, iEvent, r2s);
//  reco::VertexSimToRecoCollection vs2r = associatorByTracks->associateSimToReco(primaryVtxCollectionH, TVCollectionH, iEvent, s2r);

  //make vector of pair of trackingParticles to hold good V0 candidates
  std::vector< pair<TrackingParticleRef, TrackingParticleRef> > trueK0s;
  std::vector< pair<TrackingParticleRef, TrackingParticleRef> > trueLams;
  std::vector<double> trueKsMasses;
  std::vector<double> trueLamMasses;
  std::vector<double> trueKsPt;
  std::vector<double> trueLamPt;

  //////////////////////////////
  // Do fake rate calculation //
  //////////////////////////////

  // cout << "Starting K0s fake rate calculation" << endl;
  // Kshorts
  double numK0sFound = 0.;
  std::vector<double> radDist;
  // cout << "K0s collection size: " << k0sCollection->size() << endl;
  if ( k0sCollection.isValid() && k0sCollection->size() > 0 ) {
    vector<reco::TrackRef> theDaughterTracks;
    for( reco::VertexCompositeCandidateCollection::const_iterator iK0s = k0sCollection->begin();
	 iK0s != k0sCollection->end();
	 iK0s++) {
      // Fill values to be histogrammed
      K0sCandpT = (sqrt( iK0s->momentum().perp2() ));
      K0sCandEta = iK0s->rapidity();
      K0sCandR = (sqrt( iK0s->vertex().perp2() ));
      K0sCandStatus = 0;
      mass = iK0s->mass();

      theDaughterTracks.push_back( (*(dynamic_cast<const reco::RecoChargedCandidate *> (iK0s->daughter(0)) )).track() );
      theDaughterTracks.push_back( (*(dynamic_cast<const reco::RecoChargedCandidate *> (iK0s->daughter(1)) )).track() );

      for (int itrack = 0; itrack < 2; itrack++) {
	K0sPiCandStatus[itrack] = 0;
      }

      std::vector< std::pair<TrackingParticleRef, double> > tp;
      TrackingParticleRef tpref;
      TrackingParticleRef firstDauTP;
      TrackingVertexRef k0sVtx;

      // Loop through K0s candidate daugher tracks
      for(View<reco::Track>::size_type i=0; i<theDaughterTracks.size(); ++i){
	// Found track from theDaughterTracks
	RefToBase<reco::Track> track( theDaughterTracks.at(i) );
        
	if(recotosimCollectionH.find(track) != recotosimCollectionH.end()) {
	  tp = recotosimCollectionH[track];
	  if (tp.size() != 0) {
	    K0sPiCandStatus[i] = 1;
	    tpref = tp.begin()->first;

	    if( simtorecoCollectionH.find(tpref) == simtorecoCollectionH.end() ) {
	      K0sPiCandStatus[i] = 3;
	    }
	    TrackingVertexRef parentVertex = tpref->parentVertex();
	    if(parentVertex.isNonnull()) radDist.push_back(parentVertex->position().R());
	     
	    if( parentVertex.isNonnull() ) {
	      if( k0sVtx.isNonnull() ) {
		if( k0sVtx->position() == parentVertex->position() ) {
		  if( parentVertex->nDaughterTracks() == 2 ) {
            	    if( parentVertex->nSourceTracks() == 0 ) {
                      // No source tracks found for K0s vertex; shouldn't happen, but does for evtGen events
                      K0sCandStatus = 6;
                      if( fabs(firstDauTP->pdgId()) == 211 && fabs(tpref->pdgId()) == 211 ) {
                        K0sCandStatus = 1;
                        realK0sFound++;
                        numK0sFound += 1.;
                        std::pair<TrackingParticleRef, TrackingParticleRef> pair(firstDauTP, tpref);
                        // Pushing back a good V0
                        trueK0s.push_back(pair);
                        trueKsMasses.push_back(mass);
                        trueKsPt.push_back(K0sCandpT);
                      } 
                      else {
                        K0sCandStatus = 2;
                        if((fabs(firstDauTP->pdgId()) == 2212 && fabs(tpref->pdgId()) == 211) || (fabs(firstDauTP->pdgId()) == 211 && fabs(tpref->pdgId()) == 2212)) {
                          K0sCandStatus = 7;
                        }
                      }
                    }
//		    if( fabs(firstDauTP->pdgId()) == 211 && fabs(tpref->pdgId()) == 211 ) {
		    for( TrackingVertex::tp_iterator iTP = parentVertex->sourceTracks_begin();
			 iTP != parentVertex->sourceTracks_end(); iTP++) {
		      if( fabs((*iTP)->pdgId()) == 310 ) {
                        if( (*iTP)->status() == -99 ) K0sCandStatus=20;
                        else {
			  K0sCandStatus = 1;
	  		  realK0sFound++;
			  numK0sFound += 1.;
			  std::pair<TrackingParticleRef, TrackingParticleRef> pair(firstDauTP, tpref);
			  // Pushing back a good V0
			  trueK0s.push_back(pair);
			  trueKsMasses.push_back(mass);
                          trueKsPt.push_back(K0sCandpT);
                        }
		      }
		      else {
			K0sCandStatus = 2;
			if( fabs((*iTP)->pdgId()) == 3122 ) {
//                        if((fabs(firstDauTP->pdgId()) == 2212 && fabs(tpref->pdgId()) == 211) || (fabs(firstDauTP->pdgId()) == 211 && fabs(tpref->pdgId()) == 2212)) {
			  K0sCandStatus = 7;
			}
		      }
                    }
		  }
		  else {
		    // Found a bad match because the mother has too many daughters
		    K0sCandStatus = 3;
		  }
		}
		else {
		  // Found a bad match because the parent vertices from the two tracks are different
		  K0sCandStatus = 4;
		}
	      }
	      else {
		// if k0sVtx is null, fill it with parentVertex to compare to the parentVertex from the second track
		k0sVtx = parentVertex;
		firstDauTP = tpref;
	      }
	    }//parent vertex is null
	  }//tp size zero
	}
	else {
	  K0sPiCandStatus[i] = 2;
	  noTPforK0sCand++;
	  K0sCandStatus = 5;
	  theDaughterTracks.clear();
	}
      }
      theDaughterTracks.clear();
      // fill the fake rate histograms
      if( K0sCandStatus > 1 && K0sCandStatus!=20 ) {
	ksFakeVsR_num->Fill(K0sCandR);
	ksFakeVsEta_num->Fill(K0sCandEta);
	ksFakeVsPt_num->Fill(K0sCandpT);
	ksCandStatus->Fill((float) K0sCandStatus);
	fakeKsMass->Fill(mass);
        fakeKsMassPt->Fill(K0sCandpT,mass);
	for( unsigned int ndx = 0; ndx < radDist.size(); ndx++ ) {
	  ksFakeDauRadDist->Fill(radDist[ndx]);
	}
      }
      if( K0sCandStatus == 5 ) {
	ksTkFakeVsR_num->Fill(K0sCandR);
	ksTkFakeVsEta_num->Fill(K0sCandEta);
	ksTkFakeVsPt_num->Fill(K0sCandpT);
      }
      if( K0sCandStatus == 20 ) {
        ksSecVsR_num->Fill(K0sCandR);
        ksSecVsEta_num->Fill(K0sCandEta);
        ksSecVsPt_num->Fill(K0sCandpT);
      }
      ksFakeVsR_denom->Fill(K0sCandR);
      ksFakeVsEta_denom->Fill(K0sCandEta);
      ksFakeVsPt_denom->Fill(K0sCandpT);
    }
  }
  //cout << "Outside loop, why would it fail here?" << endl;
  //double numK0sFound = (double) realK0sFound;
  //cout << "numK0sFound: " << numK0sFound << endl;
  nKs->Fill( (float) numK0sFound );
  numK0sFound = 0.;

  // cout << "Starting Lambda fake rate calculation" << endl;
  double numLamFound = 0.;
  mass = 0.;
  radDist.clear();

  // Lambdas
  if ( lambdaCollection.isValid() && lambdaCollection->size() > 0 ) {
    vector<reco::TrackRef> theDaughterTracks;
    for( reco::VertexCompositeCandidateCollection::const_iterator iLam = lambdaCollection->begin();
	 iLam != lambdaCollection->end();
	 iLam++) {
      // Fill values to be histogrammed
      LamCandpT = (sqrt( iLam->momentum().perp2() ));
      LamCandEta = iLam->rapidity();
      LamCandR = (sqrt( iLam->vertex().perp2() ));
      LamCandStatus = 0;
      mass = iLam->mass();

      theDaughterTracks.push_back( (*(dynamic_cast<const reco::RecoChargedCandidate *> (iLam->daughter(0)) )).track() );
      theDaughterTracks.push_back( (*(dynamic_cast<const reco::RecoChargedCandidate *> (iLam->daughter(1)) )).track() );
      
      for (int itrack = 0; itrack < 2; itrack++) {
	LamPiCandStatus[itrack] = 0;
      }
      std::vector< std::pair<TrackingParticleRef, double> > tp;
      TrackingParticleRef tpref;
      TrackingParticleRef firstDauTP;
      TrackingVertexRef LamVtx;
      // Loop through Lambda candidate daughter tracks
      for(View<reco::Track>::size_type i=0; i<theDaughterTracks.size(); ++i){
	// Found track from theDaughterTracks
	//cout << "Looping over lam daughters" << endl;
	RefToBase<reco::Track> track( theDaughterTracks.at(i) );
	
	if(recotosimCollectionH.find(track) != recotosimCollectionH.end()) {
	  tp = recotosimCollectionH[track];
	  if (tp.size() != 0) {
	    LamPiCandStatus[i] = 1;
	    tpref = tp.begin()->first;

	    if( simtorecoCollectionH.find(tpref) == simtorecoCollectionH.end() ) {
	      LamPiCandStatus[i] = 3;
	    }
	    TrackingVertexRef parentVertex = tpref->parentVertex();
	    if( parentVertex.isNonnull() ) radDist.push_back(parentVertex->position().R());

	    if( parentVertex.isNonnull() ) {
	      if( LamVtx.isNonnull() ) {
		if( LamVtx->position() == parentVertex->position() ) {
		  if( parentVertex->nDaughterTracks() == 2 ) {
                    if( parentVertex->nSourceTracks() == 0 ) {
                      // No source tracks found for Lam vertex; shouldn't happen, but does for evtGen events
                      LamCandStatus = 6;
                      if((fabs(firstDauTP->pdgId()) == 2212 && fabs(tpref->pdgId()) == 211) || (fabs(firstDauTP->pdgId()) == 211 && fabs(tpref->pdgId()) == 2212) ) {
                        LamCandStatus = 1;
                        realLamFound++;
                        numLamFound += 1.;
                        std::pair<TrackingParticleRef, TrackingParticleRef> pair(firstDauTP, tpref);
                        // Pushing back a good V0
                        trueLams.push_back(pair);
                        trueLamMasses.push_back(mass);
                        trueLamPt.push_back(LamCandpT);
                      }
                    }
//		    if((fabs(firstDauTP->pdgId()) == 2212 && fabs(tpref->pdgId()) == 211) || (fabs(firstDauTP->pdgId()) == 211 && fabs(tpref->pdgId()) == 2212) ) {
		    for( TrackingVertex::tp_iterator iTP = parentVertex->sourceTracks_begin();
			 iTP != parentVertex->sourceTracks_end(); ++iTP) {
		      if( fabs((*iTP)->pdgId()) == 3122 ) {
                        for( TrackingVertex::tp_iterator genmother = (*iTP)->parentVertex()->sourceTracks_begin();
                                              genmother != (*iTP)->parentVertex()->sourceTracks_end(); genmother++) {
                          double mid = (*genmother)->pdgId();
                          if(fabs(mid)==3322 || fabs(mid)==3312 || fabs(mid)==3324 || fabs(mid)==3314 || fabs(mid)==3334) {LamCandStatus=10; break;}
                          for( TrackingVertex::tp_iterator genmother1 = (*genmother)->parentVertex()->sourceTracks_begin();
                                               genmother1 != (*genmother)->parentVertex()->sourceTracks_end(); genmother1++) {
                            mid = (*genmother1)->pdgId();
                            if(fabs(mid)==3322 || fabs(mid)==3312 || fabs(mid)==3324 || fabs(mid)==3314 || fabs(mid)==3334) {LamCandStatus=10; break;}
                          }
                        } 

                        if(LamCandStatus != 10 && (*iTP)->status() == -99) LamCandStatus=20; 
                        if(LamCandStatus != 10 && LamCandStatus != 20 ) 
                        {
	  	          LamCandStatus = 1;
		          realLamFound++;
			  numLamFound += 1.;
		  	  std::pair<TrackingParticleRef, TrackingParticleRef> pair(firstDauTP, tpref);
		 	  // Pushing back a good V0
			  trueLams.push_back(pair);
			  trueLamMasses.push_back(mass);
                          trueLamPt.push_back(LamCandpT);
                        }
		      }
		      else {
			LamCandStatus = 2;
			if( fabs((*iTP)->pdgId() ) == 310 ) {
//                        if( fabs(firstDauTP->pdgId()) == 211 && fabs(tpref->pdgId()) == 211 ) {
			  LamCandStatus = 7;
			}
	              }
                    }
		  }
		  else {
		    // Found a bad match because the mother has too many daughters
		    LamCandStatus = 3;
		  }
		}
		else {
		  // Found a bad match because the parent vertices from the two tracks are different
		  LamCandStatus = 4;
		}
	      }
	      else {
		// if lamVtx is null, fill it with parentVertex to compare to the parentVertex from the second track
		LamVtx = parentVertex;
		firstDauTP = tpref;
	      }
	    }//parent vertex is null
	  }//tp size zero
	}
	else {
	  LamPiCandStatus[i] = 2;
	  noTPforLamCand++;
	  LamCandStatus = 5;
	  theDaughterTracks.clear();
	}
      }
      theDaughterTracks.clear();
      // fill the fake rate histograms
      if( LamCandStatus > 1 && LamCandStatus!=10) {
	lamFakeVsR_num->Fill(LamCandR);
	lamFakeVsEta_num->Fill(LamCandEta);
	lamFakeVsPt_num->Fill(LamCandpT);
	lamCandStatus->Fill((float) LamCandStatus);
	fakeLamMass->Fill(mass);
        fakeLamMassPt->Fill(LamCandpT,mass);
	for( unsigned int ndx = 0; ndx < radDist.size(); ndx++ ) {
	  lamFakeDauRadDist->Fill(radDist[ndx]);
	}
      }
      if( LamCandStatus == 10 ) {
        lamCascadeVsR_num->Fill(LamCandR);
        lamCascadeVsEta_num->Fill(LamCandEta);
        lamCascadeVsPt_num->Fill(LamCandpT);
      }
      if( LamCandStatus == 20 ) {
        lamSecVsR_num->Fill(LamCandR);
        lamSecVsEta_num->Fill(LamCandEta);
        lamSecVsPt_num->Fill(LamCandpT);
      }
      if( LamCandStatus == 5 ) {
	lamTkFakeVsR_num->Fill(LamCandR);
	lamTkFakeVsEta_num->Fill(LamCandEta);
	lamTkFakeVsPt_num->Fill(LamCandpT);
      }
      lamFakeVsR_denom->Fill(LamCandR);
      lamFakeVsEta_denom->Fill(LamCandEta);
      lamFakeVsPt_denom->Fill(LamCandpT);
    }
  }
  nLam->Fill( (double) numLamFound );
  numLamFound = 0.;

// test

  for(TrackingParticleCollection::size_type i = 0; i < tPCeff.size(); i++) {
    TrackingParticleRef tpr1(TPCollectionEff, i);
    TrackingParticle* itp1 = const_cast<TrackingParticle*>(tpr1.get());
    if(fabs(itp1->pdgId()) == 3122)
    {
//      int status = itp1->status();
      bool isSecLam=0;
      for( TrackingVertex::tp_iterator genmother = itp1->parentVertex()->sourceTracks_begin();
                         genmother != itp1->parentVertex()->sourceTracks_end(); genmother++) {
        double mid = (*genmother)->pdgId();
        if(fabs(mid)==3322 || fabs(mid)==3312 || fabs(mid)==3324 || fabs(mid)==3314 || fabs(mid)==3334) {isSecLam=1; break;}
        for( TrackingVertex::tp_iterator genmother1 = (*genmother)->parentVertex()->sourceTracks_begin();
                         genmother1 != (*genmother)->parentVertex()->sourceTracks_end(); genmother1++) {
          mid = (*genmother1)->pdgId();
          if(fabs(mid)==3322 || fabs(mid)==3312 || fabs(mid)==3324 || fabs(mid)==3314 || fabs(mid)==3334) {isSecLam=1; break;}
        }   
      }
      if(isSecLam) continue;
      if(itp1->status() == -99) continue;
 
      if(!itp1->decayVertices().size()) continue;

      double LamGenpTtmp = sqrt(itp1->momentum().perp2());
      double LamGenEtatmp = itp1->rapidity();
      lamEffVsEtaPt_denom_test->Fill(LamGenEtatmp,LamGenpTtmp);
      lamEffVsPt_denom_test->Fill(LamGenpTtmp);
    }
  }

  ///////////////////////////////
  // Do efficiency calculation //
  ///////////////////////////////

  // cout << "Starting Lambda efficiency" << endl;
  // Lambdas

  for(TrackingParticleCollection::size_type i = 0; i < tPCeff.size(); i++) {
    TrackingParticleRef tpr1(TPCollectionEff, i);
    TrackingParticle* itp1 = const_cast<TrackingParticle*>(tpr1.get());
    if( (itp1->pdgId() == 211 || itp1->pdgId() == 2212)
//	&& itp1->parentVertex().isNonnull()
//	&& fabs(itp1->momentum().eta()) < 2.4
//	&& sqrt( itp1->momentum().perp2() ) > 0.0) {
    ) {
//      int nhits1 = itp1->trackPSimHit().size();
      bool isLambda = false;
      if( itp1->pdgId() == 2212 ) isLambda = true;
      if( itp1->parentVertex()->nDaughterTracks() == 2 ) {

	TrackingVertexRef piCand1Vertex = itp1->parentVertex();
	for(TrackingVertex::tp_iterator iTP1 = piCand1Vertex->sourceTracks_begin();
	    iTP1 != piCand1Vertex->sourceTracks_end(); iTP1++) {
	  if( fabs((*iTP1)->pdgId()) == 3122 ) {
	    for(TrackingParticleCollection::size_type j=0;
		j < tPCeff.size();
		j++)
          {
	      TrackingParticleRef tpr2(TPCollectionEff, j);
	      TrackingParticle* itp2 = const_cast<TrackingParticle*>(tpr2.get());
	      int particle2pdgId;
	      if (isLambda) particle2pdgId = -211;
	      else particle2pdgId = -2212;
	      if( itp2->pdgId() == particle2pdgId
   	//	  && itp2->parentVertex().isNonnull()
	//	  && fabs(itp2->momentum().eta()) < 2.4
	//	  && sqrt(itp2->momentum().perp2()) > 0.0) {
              ) {
		if(itp2->parentVertex() == itp1->parentVertex()) {
//                  int nhits2 = itp2->trackPSimHit().size();

		  // Found a good pair of Lambda daughters
		  TrackingVertexRef piCand2Vertex = itp2->parentVertex();
		  for (TrackingVertex::tp_iterator iTP2 = piCand2Vertex->sourceTracks_begin();
		       iTP2 != piCand2Vertex->sourceTracks_end(); 
		       ++iTP2) {
		    LamGenEta = LamGenpT = LamGenR = 0.;
		    LamGenStatus = 0;
		    for(int ifill = 0;
			ifill < 2;
			ifill++) {
		      // do nothing?
		    }
		    if( fabs((*iTP2)->pdgId()) == 3122 && (*iTP2)->status()!=-99 ) {
		      // found generated Lambda
		      LamGenpT = sqrt((*iTP2)->momentum().perp2());
		      LamGenEta = (*iTP2)->rapidity();
		      LamGenR = sqrt(itp2->vertex().perp2());
		      genLam++;
		      if(trueLams.size() > 0) {
			int loop_1 = 0;
			for(std::vector< pair<TrackingParticleRef, TrackingParticleRef> >::const_iterator iEffCheck = trueLams.begin();
			    iEffCheck != trueLams.end();
			    iEffCheck++) {
			  if( itp1->parentVertex() == iEffCheck->first->parentVertex()
			      && itp2->parentVertex() == iEffCheck->second->parentVertex() ) {
			    realLamFoundEff++;
			    //V0Producer found the generated Lambda
			    LamGenStatus = 1;
			    //cout << "Maybe it's here.." << endl;
			    goodLamMass->Fill(trueLamMasses[loop_1]);
                            goodLamMassPt->Fill(trueLamPt[loop_1],trueLamMasses[loop_1]);
                            lamResolutionPt->Fill(trueLamPt[loop_1],LamGenpT-trueLamPt[loop_1]);
			    break;
			  }
			  else {
			    //V0Producer didn't find the generated Lambda
			    LamGenStatus = 2;
			  }
			  loop_1++;
			}
		      }
		      else {
			//No V0 cand found, so V0Producer didn't find the generated Lambda
			LamGenStatus = 2;
		      }
		      std::vector< std::pair<RefToBase<reco::Track>, double> > rt1;
		      std::vector< std::pair<RefToBase<reco::Track>, double> > rt2;
		      
		      //if( simRecColl.find(tpr1) != simRecColl.end() ) {
		      if( simtorecoCollectionH.find(tpr1) != simtorecoCollectionH.end() ) {
			rt1 = (std::vector<std::pair<RefToBase<reco::Track>, double> >) simtorecoCollectionH[tpr1];
			if(rt1.size() != 0) {
			  LamPiEff[0] = 1; //Found the first daughter track
			  edm::RefToBase<reco::Track> t1 = rt1.begin()->first;
			}
		      }
		      else {
			LamPiEff[0] = 2;//First daughter not found
		      }
		      if( (simtorecoCollectionH.find(tpr2) != simtorecoCollectionH.end()) ) {
			//rt2 = (std::vector<std::pair<RefToBase<reco::Track>, double> >) simRecColl[tpr2];
			rt2 = (std::vector<std::pair<RefToBase<reco::Track>, double> >) simtorecoCollectionH[tpr2];
			if(rt2.size() != 0) {
			  LamPiEff[1] = 1;//Found the second daughter track
			  edm::RefToBase<reco::Track> t2 = rt2.begin()->first;
			}
		      }
		      else {
			LamPiEff[1] = 2;//Second daughter not found
		      }
		      
		      if( LamGenStatus == 1
			  && (LamPiEff[0] == 2 || LamPiEff[1] == 2) ) {
			// Good Lambda found, but recoTrack->trackingParticle->recoTrack didn't work
			LamGenStatus = 4;
			realLamFoundEff--;
		      }
		      if( LamGenStatus == 2
			  && (LamPiEff[0] == 2 || LamPiEff[1] == 2) ) {
			// Lambda not found because we didn't find a daughter track
			LamGenStatus = 3;
		      }
		      //cout << "LamGenStatus: " << LamGenStatus << ", LamPiEff[i]: " << LamPiEff[0] << ", " << LamPiEff[1] << endl;
		      // Fill histograms
		      if(LamGenR > 0. && fabs(LamGenEta) > 0. && LamGenpT > 0.) {
			if(LamGenStatus == 1) {
			  lamEffVsR_num->Fill(LamGenR);
                          lamEffVsEtaR_num->Fill(LamGenR,LamGenEta);
                          lamEffVsPtR_num->Fill(LamGenR,LamGenpT);
			}
			if((double) LamGenStatus < 2.5) {
			  lamTkEffVsR_num->Fill(LamGenR);
			}
			lamEffVsR_denom->Fill(LamGenR);
                        lamEffVsEtaR_denom->Fill(LamGenR,LamGenEta);
                        lamEffVsPtR_denom->Fill(LamGenR,LamGenpT);
		      }
		      if(fabs(LamGenEta) > 0. && LamGenpT > 0.) {
			if(LamGenStatus == 1) {
			  lamEffVsEta_num->Fill(LamGenEta);
                          lamEffVsPt_num->Fill(LamGenpT);
                          lamEffVsEtaPt_num->Fill(LamGenEta,LamGenpT);
			}
			if((double) LamGenStatus < 2.5) {
			  lamTkEffVsEta_num->Fill(LamGenEta);
                          lamTkEffVsPt_num->Fill(LamGenpT);
                          lamTkEffVsEtaPt_num->Fill(LamGenEta,LamGenpT);
			}
                     //cout<<nhits1<<" " <<nhits2<<endl;

			lamEffVsEta_denom->Fill(LamGenEta);
                        lamEffVsPt_denom->Fill(LamGenpT);
                        lamEffVsEtaPt_denom->Fill(LamGenEta,LamGenpT);
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }

  //Kshorts
  // cout << "Starting Kshort efficiency" << endl;
  for (TrackingParticleCollection::size_type i=0; i<tPCeff.size(); i++){
    TrackingParticleRef tpr1(TPCollectionEff, i);
    TrackingParticle* itp1=const_cast<TrackingParticle*>(tpr1.get());
    // only count the efficiency for pions with |eta|<2.4 and pT>0.2 GeV. First search for a suitable pi+
    if ( itp1->pdgId() == 211 
//	 && itp1->parentVertex().isNonnull() 
//	 && fabs(itp1->momentum().eta()) < 2.4 
//	 && sqrt(itp1->momentum().perp2()) > 0.0) {
    ){
      if ( itp1->parentVertex()->nDaughterTracks() == 2 ) {
	TrackingVertexRef piCand1Vertex = itp1->parentVertex();	       
	//check trackingParticle pion for a Ks mother
	for (TrackingVertex::tp_iterator iTP1 = piCand1Vertex->sourceTracks_begin();
	     iTP1 != piCand1Vertex->sourceTracks_end(); ++iTP1) {
	  //iTP1 is a TrackingParticle
	  if ( (*iTP1)->pdgId()==310 ) {
	    //with a Ks mother found for the pi+, loop through trackingParticles again to find a pi-
	    for (TrackingParticleCollection::size_type j=0; j<tPCeff.size(); j++){
	      TrackingParticleRef tpr2(TPCollectionEff, j);
	      TrackingParticle* itp2=const_cast<TrackingParticle*>(tpr2.get());
	      if ( itp2->pdgId() == -211
//                   && itp2->parentVertex().isNonnull()  
//		   && fabs(itp2->momentum().eta()) < 2.4 
//		   && sqrt(itp2->momentum().perp2()) > 0.0) {
              ) {
		//check the pi+ and pi- have the same vertex
		if ( itp2->parentVertex() == itp1->parentVertex() ) {
		  TrackingVertexRef piCand2Vertex = itp2->parentVertex();	       
		  for (TrackingVertex::tp_iterator iTP2 = piCand2Vertex->sourceTracks_begin();
		       iTP2 != piCand2Vertex->sourceTracks_end(); ++iTP2) {
		    //iTP2 is a TrackingParticle
		    K0sGenEta = K0sGenpT = K0sGenR = 0.;
		    K0sGenStatus = 0;
		    if( (*iTP2)->pdgId() == 310 && (*iTP2)->status() != -99 ) {
		      K0sGenpT = sqrt( (*iTP2)->momentum().perp2() );
		      K0sGenEta = (*iTP2)->rapidity();
		      K0sGenR = sqrt(itp2->vertex().perp2());
		      genK0s++;
		      int loop_2 = 0;
		      if( trueK0s.size() > 0 ) {
			for( std::vector< pair<TrackingParticleRef, TrackingParticleRef> >::const_iterator iEffCheck = trueK0s.begin();
			     iEffCheck != trueK0s.end();
			     iEffCheck++) {
			  //if the parent vertices for the tracks are the same, then the generated Ks was found
			  if (itp1->parentVertex()==iEffCheck->first->parentVertex() &&
			      itp2->parentVertex()==iEffCheck->second->parentVertex() ) { 
         //                     (itp2->parentVertex()==iEffCheck->first->parentVertex() &&
         //                     itp1->parentVertex()==iEffCheck->second->parentVertex()) )  {
			    realK0sFoundEff++;
			    K0sGenStatus = 1;
			    goodKsMass->Fill(trueKsMasses[loop_2]);
                            goodKsMassPt->Fill(trueKsPt[loop_2],trueKsMasses[loop_2]);
                            ksResolutionPt->Fill(trueKsPt[loop_2],K0sGenpT-trueKsPt[loop_2]);
			    break;
			  }
			  else {
			    K0sGenStatus = 2;
			  }
                          loop_2++;
			}
		      }
		      else {
			K0sGenStatus = 2;
		      }
		      // Check if the generated Ks tracks were found or not
		      // by searching the recoTracks list for a match to the trackingParticles

		      std::vector<std::pair<RefToBase<reco::Track>, double> > rt1;
		      std::vector<std::pair<RefToBase<reco::Track>, double> > rt2;
		      
		      //if( simRecColl.find(tpr1) != simRecColl.end() ) {
		      if( simtorecoCollectionH.find(tpr1) != simtorecoCollectionH.end() ) {
			rt1 = (std::vector< std::pair<RefToBase<reco::Track>, double> >) simtorecoCollectionH[tpr1];
			if(rt1.size() != 0) {
			  //First pion found
			  K0sPiEff[0] = 1;
			  edm::RefToBase<reco::Track> t1 = rt1.begin()->first;
			}
		      }
		      else {
			//First pion not found
			K0sPiEff[0] = 2;
		      }
		      
		      //if( simRecColl.find(tpr2) != simRecColl.end() ) {
		      if( simtorecoCollectionH.find(tpr2) != simtorecoCollectionH.end() ) {
			rt2 = (std::vector< std::pair<RefToBase<reco::Track>, double> >) simtorecoCollectionH[tpr2];
//simRecColl[tpr2];
			if(rt2.size() != 0) {
			  //Second pion found
			  K0sPiEff[1] = 1;
			  edm::RefToBase<reco::Track> t2 = rt2.begin()->first;
			}
		      }
		      else {
			K0sPiEff[1] = 2;
		      }
		      //cout << "Status: " << K0sGenStatus << ", K0sPiEff[i]: " << K0sPiEff[0] << ", " << K0sPiEff[1] << endl;
		      if(K0sGenStatus == 1
			 && (K0sPiEff[0] == 2 || K0sPiEff[1] == 2)) {
			K0sGenStatus = 4;
			realK0sFoundEff--;
		      }
		      if(K0sGenStatus == 2
			 && (K0sPiEff[0] == 2 || K0sPiEff[1] == 2)) {
			K0sGenStatus = 3;
		      }
		      if(K0sPiEff[0] == 1 && K0sPiEff[1] == 1) {
			k0sTracksFound++;
		      }
		      //Fill Histograms
		      if(K0sGenR > 0. && fabs(K0sGenEta) > 0. && K0sGenpT > 0.) {
			if(K0sGenStatus == 1) {
			  ksEffVsR_num->Fill(K0sGenR);
                          ksEffVsEtaR_num->Fill(K0sGenR,K0sGenEta);
                          ksEffVsPtR_num->Fill(K0sGenR,K0sGenpT);
			}
			if((double) K0sGenStatus < 2.5) {			  
			  ksTkEffVsR_num->Fill(K0sGenR);
			}
			ksEffVsR_denom->Fill(K0sGenR);
                        ksEffVsEtaR_denom->Fill(K0sGenR,K0sGenEta);
                        ksEffVsPtR_denom->Fill(K0sGenR,K0sGenpT);
		      }

		      if(fabs(K0sGenEta) > 0. && K0sGenpT > 0.) {
			if(K0sGenStatus == 1) {
			  ksEffVsEta_num->Fill(K0sGenEta);
                          ksEffVsPt_num->Fill(K0sGenpT);
                          ksEffVsEtaPt_num->Fill(K0sGenEta,K0sGenpT);
			}
			if((double) K0sGenStatus < 2.5) {
			  ksTkEffVsEta_num->Fill(K0sGenEta);
                          ksTkEffVsPt_num->Fill(K0sGenpT);
                          ksTkEffVsEtaPt_num->Fill(K0sGenEta,K0sGenpT);
			}
			ksEffVsEta_denom->Fill(K0sGenEta);
                        ksEffVsPt_denom->Fill(K0sGenpT);
                        ksEffVsEtaPt_denom->Fill(K0sGenEta,K0sGenpT);
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
  delete thePrimary;
}

void V0Validator::endRun(const edm::Run& iRun, const edm::EventSetup& iSetup) {}

//void V0Validator::endJob() {}

//define this as a plug-in
//DEFINE_FWK_MODULE(V0Validator);

