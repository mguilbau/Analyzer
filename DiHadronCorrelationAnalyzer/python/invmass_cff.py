import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.invmass_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

invmass_ana_020 = invmass_ana.clone(
  nmin = cms.int32(0),
  nmax = cms.int32(20)
)

invmass_ana_2040 = invmass_ana.clone(
  nmin = cms.int32(20),
  nmax = cms.int32(40)
)

invmass_ana_4060 = invmass_ana.clone(
  nmin = cms.int32(40),
  nmax = cms.int32(60)
)

invmass_ana_60100 = invmass_ana.clone(
  nmin = cms.int32(60),
  nmax = cms.int32(100)
)

invmass_ana_100120 = invmass_ana.clone(
  nmin = cms.int32(100),
  nmax = cms.int32(120)
)

invmass_ana_120150 = invmass_ana.clone(
  nmin = cms.int32(120),
  nmax = cms.int32(150)
)

invmass_ana_150185 = invmass_ana.clone(
  nmin = cms.int32(150),
  nmax = cms.int32(185)
)

invmass_ana_185220 = invmass_ana.clone(
  nmin = cms.int32(185),
  nmax = cms.int32(220)
)

invmass_ana_220260 = invmass_ana.clone(
  nmin = cms.int32(220),
  nmax = cms.int32(260)
)

invmass_ana_260 = invmass_ana.clone(
  nmin = cms.int32(260),
  nmax = cms.int32(10000)
)

invmass_ana_mb_seq = cms.Sequence(hltMB*invmass_ana)
invmass_ana_120150_seq = cms.Sequence(hltHM120150*invmass_ana)
invmass_ana_150185_seq = cms.Sequence(hltHM150185*invmass_ana)
invmass_ana_185220_seq = cms.Sequence(hltHM185220*invmass_ana)
invmass_ana_220260_seq = cms.Sequence(hltHM220*invmass_ana)
invmass_ana_260_seq = cms.Sequence(hltHM220*invmass_ana)
