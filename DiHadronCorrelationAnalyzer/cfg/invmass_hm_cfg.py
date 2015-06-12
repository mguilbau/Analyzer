import FWCore.ParameterSet.Config as cms

process = cms.Process("invmass")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000


### conditions
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'GR_R_53_LV6::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

#from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
#overrideCentrality(process)
#process.HeavyIonGlobalParameters = cms.PSet(
#        centralityVariable = cms.string("HFtowers"),
#       nonDefaultGlauberModel = cms.string("Hydjet_2760GeV"),
#        centralitySrc = cms.InputTag("hiCentrality")
#        )

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
#import HLTrigger.HLTfilters.hltHighLevel_cfi
#process.hltHM = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
#process.hltHM.HLTPaths = ['HLT_HIMinBiasHfOrBSC_*'] # for allphysics
#process.hltHM.andOr = cms.bool(True)
#process.hltHM.throw = cms.bool(False)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHM_Gplus_Rereco_v15/702fa69daea9da948fe2472b4d29b5b5/pPb_HM_271_1_tDL.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.invmass_cff")
process.load("FlowCorrAna.V0Analysis.v0selector_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('invmass.root')
                                   )

#process.ana_120150 = cms.Path(process.invmass_ana_120150_seq)
#process.ana_150185 = cms.Path(process.invmass_ana_150185_seq)
process.ana_185220 = cms.Path(process.selectV0CandidatesNewlambda*process.invmass_ana_185220_seq)
#process.ana_220260 = cms.Path(process.invmass_ana_220260_seq)
#process.ana_260 = cms.Path(process.invmass_ana_260_seq)
process.invmass_ana.nmin = cms.int32(185)
process.invmass_ana.nmax = cms.int32(220)
process.invmass_ana.V0CandidateCollection = cms.string('selectV0CandidatesNewlambda')
process.invmass_ana.AssociateID = cms.string('LambdaP')
process.invmass_ana.TriggerID = cms.string('LambdaP')
#process.invmass_ana.mass_ass = cms.double(0.139570)
