import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.ebyeflow_cfi import *

ebyeflow_ana_HI = ebyeflow_ana.clone(
  TrgTrackCollection = cms.string('hiLowPtPixelTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('hiGenParticles'),
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
