import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cfi import *

corr_ana_HI = corr_ana.clone(
  TrgTrackCollection = cms.string('hiLowPtPixelTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('hiGenParticles')
)
