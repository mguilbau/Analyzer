import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.chargedepcorr_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

chargedepcorr_ana_pPb = chargedepcorr_ana.clone(
  ReCenterDirName = cms.string('chargedepcorr_ana_pPb')
)

chargedepcorr_ana_HI = chargedepcorr_ana.clone(
  TrgTrackCollection = cms.string('hiGeneralAndPixelTracks'),
#  TrgTrackCollection = cms.string('hiGeneralTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
  GenParticleCollection = cms.string('hiGenParticles'),

  IsHITrkQuality = cms.bool(True),
  IsPPTrkQuality = cms.bool(False),

#  etatrgmin = cms.double(-0.8),
#  etatrgmax = cms.double(0.8),

#  EffFileName = cms.string('trkEffNew2012_HI_pixeltracks_tmp.root')
  EffFileName = cms.string(''),
  ReCenterDirName = cms.string('chargedepcorr_ana_HI')
)

chargedepcorr_ana_120150_seq = cms.Sequence(hltHM120150*chargedepcorr_ana_pPb)
chargedepcorr_ana_150185_seq = cms.Sequence(hltHM150185*chargedepcorr_ana_pPb)
chargedepcorr_ana_185220_seq = cms.Sequence(hltHM185220*chargedepcorr_ana_pPb)
chargedepcorr_ana_220260_seq = cms.Sequence(hltHM220*chargedepcorr_ana_pPb)
chargedepcorr_ana_260_seq = cms.Sequence(hltHM220*chargedepcorr_ana_pPb)
