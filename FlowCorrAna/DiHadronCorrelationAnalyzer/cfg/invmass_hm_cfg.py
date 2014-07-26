import FWCore.ParameterSet.Config as cms

process = cms.Process("invmass")
process.load("FWCore.MessageService.MessageLogger_cfi")

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
'/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHM_Gplus_Rereco_v12/9d480a1aca4172fd4f159e4efe1592ae/pPb_HM_283_1_vbF.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.invmass_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('invmass.root')
                                   )

#process.ana_120150 = cms.Path(process.invmass_ana_120150_seq)
#process.ana_150185 = cms.Path(process.invmass_ana_150185_seq)
process.ana_185220 = cms.Path(process.invmass_ana_185220_seq)
#process.ana_220260 = cms.Path(process.invmass_ana_220260_seq)
#process.ana_260 = cms.Path(process.invmass_ana_260_seq)
process.invmass_ana.nmin = cms.int32(185)
process.invmass_ana.nmax = cms.int32(220)
