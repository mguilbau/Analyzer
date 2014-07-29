import FWCore.ParameterSet.Config as cms

from RiceHIG.V0Analysis.v0selector_cfi import *
selectV0CandidatesNewkshort = selectV0CandidatesNew.clone()
selectV0CandidatesNewlambda = selectV0CandidatesNew.clone(
  v0IDName = cms.string("Lambda"),
  misIDMassCut   = cms.double(0.020)
)
