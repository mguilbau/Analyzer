import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.epptdeco_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

epptdeco_ana_HI = epptdeco_ana.clone(
  TrgTrackCollection = cms.string('hiGeneralAndPixelTracks'),
#  TrgTrackCollection = cms.string('hiGeneralTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('hiGenParticles'),

  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

  EffFileName = cms.string('')
)

epptdeco_ana_pPb = epptdeco_ana.clone(
)

epptdeco_ana_120150_seq = cms.Sequence(hltHM120150*epptdeco_ana_pPb)
epptdeco_ana_150185_seq = cms.Sequence(hltHM150185*epptdeco_ana_pPb)
epptdeco_ana_185220_seq = cms.Sequence(hltHM185220*epptdeco_ana_pPb)
epptdeco_ana_220260_seq = cms.Sequence(hltHM220*epptdeco_ana_pPb)
epptdeco_ana_260_seq = cms.Sequence(hltHM220*epptdeco_ana_pPb)
