import FWCore.ParameterSet.Config as cms

pAHighMultiplicityPileUpFilter  = cms.EDFilter('PAHighMultiplicityPileUpFilter',
    vtxSrc = cms.InputTag("offlinePrimaryVertices"),
    mode = cms.int32(0),
    CutParameters0 = cms.vdouble(
       0.924730, 7.484908, 8.849780, -0.587169,
       0.478601, -0.000106, -0.000385, -0.094790,
       0.250266, 198.662432, 728.424750, 2.958134  
    ),
    CutParameters1 = cms.vdouble(
       2.000000, 2.847512, 0.508131, 0.000025, -0.178067,
       8.000000, 0.257011
    )
)
