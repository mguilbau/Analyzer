import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cfi import *

corr_ana_HI = corr_ana.clone(
#  TrgTrackCollection = cms.string('hiLowPtPixelTracks'),
  TrgTrackCollection = cms.string('hiGeneralTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('hiGenParticles'),

  rhomin = cms.double(0.0),
  rhomax = cms.double(0.02),
  xvtxcenter = cms.double(0.077),
  yvtxcenter = cms.double(0.037),
  zvtxcenter = cms.double(-0.54),

  IsHarmonics = cms.bool(True),
  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),
)
