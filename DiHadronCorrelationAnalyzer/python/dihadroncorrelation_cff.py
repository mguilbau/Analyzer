import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

corr_ana_HI = corr_ana.clone(
#  TrgTrackCollection = cms.string('hiLowPtPixelTracks'),
  TrgTrackCollection = cms.string('hiGeneralAndPixelTracks'),
#  TrgTrackCollection = cms.string('hiGeneralTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('hiGenParticles'),

  rhomin = cms.double(0.0),
  rhomax = cms.double(0.02),
  xvtxcenter = cms.double(0.077),
  yvtxcenter = cms.double(0.037),
  zvtxcenter = cms.double(-0.54),

  pttrgmin = cms.vdouble(0.3, 0.5, 0.75, 1.0, 1.5, 2.0, 2.5),
  pttrgmax = cms.vdouble(0.5, 0.75, 1.0, 1.5, 2.0, 2.5, 3.0),
  ptassmin = cms.vdouble(0.3, 0.5, 0.75, 1.0, 1.5, 2.0, 2.5),
  ptassmax = cms.vdouble(0.5, 0.75, 1.0, 1.5, 2.0, 2.5, 3.0),

  IsHarmonics = cms.bool(True),
  IsHarmonicsEta1Eta2 = cms.bool(True),
  IsFullMatrix = cms.bool(False),
  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

  EffFileName = cms.string('')
)

corr_ana_HI_hf = corr_ana_HI.clone(
  pttrgmin = cms.vdouble(0.0),
  pttrgmax = cms.vdouble(10000.0),
  ptassmin = cms.vdouble(0.0),
  ptassmax = cms.vdouble(10000.0),

  etatrgmin = cms.double(-5.0),
  etatrgmax = cms.double(-4.0),
  etaassmin = cms.double(4.0),
  etaassmax = cms.double(5.0),

  IsPtWeightTrg = cms.bool(True),
  IsPtWeightAss = cms.bool(True),

  TriggerID = cms.string('CaloTower'),
  AssociateID = cms.string('CaloTower'),
)

corr_ana_HI_highPt = corr_ana_HI.clone(
  IsHarmonics = cms.bool(False),
  pttrgmin = cms.vdouble(12.0),
  pttrgmax = cms.vdouble(10000.0),
  ptassmin = cms.vdouble(0.5,1.0,2.0,3.0,4.0,6.0,8.0),
  ptassmax = cms.vdouble(1.0,2.0,3.0,4.0,6.0,8.0,12.0)
)

corr_ana_pPb = corr_ana.clone(
  rhomax = cms.double(0.5),

  IsFullMatrix = cms.bool(False),

  pttrgmin = cms.vdouble(1.0, 2.0, 4.0, 6.0),
  pttrgmax = cms.vdouble(2.0, 4.0, 6.0, 12.0),
  ptassmin = cms.vdouble(1.0, 2.0, 4.0, 6.0),
  ptassmax = cms.vdouble(2.0, 4.0, 6.0, 12.0),

#  EffFileName = cms.string('')
)

corr_ana_pPb_TrkCalo = corr_ana.clone(
  rhomax = cms.double(0.5),

  IsFullMatrix = cms.bool(False),

  pttrgmin = cms.vdouble(12.0),
  pttrgmax = cms.vdouble(100.0),
  ptassmin = cms.vdouble(0.0),
  ptassmax = cms.vdouble(100.0),

  AssociateID = cms.string('CaloTower'),

  etatrgmin = cms.double(-2.4),
  etatrgmax = cms.double(0.0),
  etaassmin = cms.double(3.0),
  etaassmax = cms.double(5.0),

  EffFileName = cms.string('')
)
