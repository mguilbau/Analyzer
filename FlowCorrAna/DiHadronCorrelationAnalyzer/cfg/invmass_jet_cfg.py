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
'/store/user/davidlw/PAMinBiasUPC/PA2013_FlowCorr_PromptReco_MB_Gplus_v12/67eb24797f3ac7778fd438fc7f3c952c/pPb_HM_423_1_PJn.root'
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

process.ana_jet = cms.Path(process.invmass_ana_all_seq)
