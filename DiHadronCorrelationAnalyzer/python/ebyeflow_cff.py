import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.ebyeflow_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

ebyeflow_ana_HI = ebyeflow_ana.clone(
#  TrgTrackCollection = cms.string('hiLowPtPixelTracks'),
  TrgTrackCollection = cms.string('hiGeneralTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('hiGenParticles'),

  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

  pttrgmin = cms.vdouble(1.0),

  EffFileName = cms.string('')
)

ebyeflow_ana_HI_cent002 = ebyeflow_ana_HI.clone(
  centmin = cms.int32(110),
  centmax = cms.int32(1000)
)

ebyeflow_ana_HI_cent05 = ebyeflow_ana_HI.clone(
  centmin = cms.int32(0),
  centmax = cms.int32(10)
)

ebyeflow_ana_HI_cent510 = ebyeflow_ana_HI.clone(
  centmin = cms.int32(10),
  centmax = cms.int32(20)
)

ebyeflow_ana_HI_cent1020 = ebyeflow_ana_HI.clone(
  centmin = cms.int32(20),
  centmax = cms.int32(40)
)

ebyeflow_ana_HI_cent2030 = ebyeflow_ana_HI.clone(
  centmin = cms.int32(40),
  centmax = cms.int32(60)
)

ebyeflow_ana_HI_cent3040 = ebyeflow_ana_HI.clone(
  centmin = cms.int32(60),
  centmax = cms.int32(80)
)

ebyeflow_ana_HI_cent4050 = ebyeflow_ana_HI.clone(
  centmin = cms.int32(80),
  centmax = cms.int32(100)
)

ebyeflow_ana_HI_cent5060 = ebyeflow_ana_HI.clone(
  centmin = cms.int32(100),
  centmax = cms.int32(120)
)

ebyeflow_ana_pPb = ebyeflow_ana.clone()

ebyeflow_ana_120150_seq = cms.Sequence(hltHM120150*ebyeflow_ana_pPb)
ebyeflow_ana_150185_seq = cms.Sequence(hltHM150185*ebyeflow_ana_pPb)
ebyeflow_ana_185220_seq = cms.Sequence(hltHM185220*ebyeflow_ana_pPb)
ebyeflow_ana_220260_seq = cms.Sequence(hltHM220*ebyeflow_ana_pPb)
ebyeflow_ana_260_seq = cms.Sequence(hltHM220*ebyeflow_ana_pPb)
