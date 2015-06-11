import FWCore.ParameterSet.Config as cms

from FlowCorrAna.DiHadronCorrelationAnalyzer.multiplicityanalyzer_cfi import *
from FlowCorrAna.DiHadronCorrelationAnalyzer.hltFilter_cff import *

mult_ana_HI = mult_ana.clone(
  TrgTrackCollection = cms.string('hiSelectedTracks'),
  VertexCollection = cms.string('hiSelectedVertex'),
)
