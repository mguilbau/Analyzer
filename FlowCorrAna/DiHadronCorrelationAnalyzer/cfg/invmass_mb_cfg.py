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
'/store/user/davidlw/PAMinBiasUPC/PA2013_FlowCorr_PromptReco_MB_Gplus_v12/67eb24797f3ac7778fd438fc7f3c952c/pPb_HM_423_1_PJn.root'
#'/store/user/davidlw/Hijing_PPb502_MinimumBias/RecoSkim_batch1_v1/84cb8c951385c1f95541c031462cec6b/pPb_MB_308_1_b6a.root'
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

process.ana = cms.Path(process.invmass_ana_mb_seq)
#process.ana = cms.Path(process.invmass_ana)
process.invmass_ana.nmin = cms.int32(0)
process.invmass_ana.nmax = cms.int32(35)
#process.invmass_ana.rhomax = cms.double(1.0)
#process.ana_020 = cms.Path(process.invmass_ana_020_seq)
#process.ana_2040 = cms.Path(process.invmass_ana_2040_seq)
#process.ana_4060 = cms.Path(process.invmass_ana_4060_seq)
#process.ana_60100 = cms.Path(process.invmass_ana_60100_seq)
#process.ana_100120 = cms.Path(process.invmass_ana_100120_seq)
