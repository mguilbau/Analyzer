import FWCore.ParameterSet.Config as cms

import davidlw.HighPtFlow2011.PAHighMultiplicityPileUpFilter_cfi

pAHighMultiplicityPileUpFilter_2Sigma = davidlw.HighPtFlow2011.PAHighMultiplicityPileUpFilter_cfi.pAHighMultiplicityPileUpFilter.clone()

pAHighMultiplicityPileUpFilter_1Sigma = davidlw.HighPtFlow2011.PAHighMultiplicityPileUpFilter_cfi.pAHighMultiplicityPileUpFilter.clone(
    CutParameters0 = cms.vdouble(
      0.814358, 5.986392, 7.108107, -0.528629,
      0.365028, -0.000087, -0.000309, -0.086429,
      0.259900, 197.432073, 703.398397, 2.744931
    )
)

pAHighMultiplicityPileUpFilter_2Sigma_mode1 = davidlw.HighPtFlow2011.PAHighMultiplicityPileUpFilter_cfi.pAHighMultiplicityPileUpFilter.clone(
    mode = cms.int32(1)
)

pAHighMultiplicityPileUpFilter_1Sigma_mode1 = davidlw.HighPtFlow2011.PAHighMultiplicityPileUpFilter_cfi.pAHighMultiplicityPileUpFilter.clone(
    mode = cms.int32(1),
    CutParameters1 = cms.vdouble(
      2.000000, 11.139555, 0.268336, 78.737011, -0.388406,
      8.000000, 0.194166  
    )
)
