import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('UCCTriggerAnalyzer',
   srcPixelClusters = cms.InputTag("siPixelClusters"),
   srcSumET = cms.InputTag("met")
)
