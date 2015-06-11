import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'GR_R_53_LV6::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500)
)

from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
        centralityVariable = cms.string("HFtowers"),
#       nonDefaultGlauberModel = cms.string("Hydjet_2760GeV"),
        centralitySrc = cms.InputTag("hiCentrality")
        )

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIMB.HLTPaths = ['HLT_HIMinBiasHfOrBSC_*'] # for allphysics
process.hltHIMB.andOr = cms.bool(True)
process.hltHIMB.throw = cms.bool(False)

process.hltHIUCC = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIUCC.HLTPaths = ['HLT_HIUCC*_*'] # for allphysics
process.hltHIUCC.andOr = cms.bool(True)
process.hltHIUCC.throw = cms.bool(False)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/user/davidlw/HIMinBiasUPC/PR2011_MBUCC_TRKANASKIM_official_v1/71a7d203fff2b3f389673e6fdd587ee0/hiGoodColl_1023_1_S52.root'
#'root://xrootd.unl.edu//store/user/appeltel/HIMinBiasUPC/pixelTrackReco_devel_v0/a236e4501225ae15b3601563d612abb5/pixeltrackreco_6_1_qSR.root'
'/store/user/davidlw/HIMinBiasUPC/Skim_rereco_pixeltracks_v1/4b65ef5aa7a26abf1f962cd25f7df02d/hiMB_88_1_qbI.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.epetadeco_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('epetadeco.root')
                                   )

process.epetadeco_ana_HI_UCC_nocorr = process.epetadeco_ana_HI_nocorr.clone()

#process.ana_hfp_cent002 = cms.Path(process.hltHIUCC*process.epetadeco_ana_HI_hfp_cent002)
#process.ana_hfm_cent002 = cms.Path(process.hltHIUCC*process.epetadeco_ana_HI_hfm_cent002)
#process.ana_hfp_cent05 = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfp_cent05)
#process.ana_hfm_cent05 = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfm_cent05)
process.ana_hfp_cent510 = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfp_cent510)
process.ana_hfm_cent510 = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfm_cent510)
#process.ana_hfp_cent1020 = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfp_cent1020)
#process.ana_hfm_cent1020 = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfm_cent1020)
#process.ana_hfp_cent2030 = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfp_cent2030)
#process.ana_hfm_cent2030 = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfm_cent2030)
#process.ana_hfp_cent3040 = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfp_cent3040)
#process.ana_hfm_cent3040 = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfm_cent3040)
#process.ana_hfp_cent4050 = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfp_cent4050)
#process.ana_hfm_cent4050 = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfm_cent4050)
#process.ana_hfp_cent5060 = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfp_cent5060)
#process.ana_hfm_cent5060 = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfm_cent5060)
#process.ana_nocorr = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_nocorr)
#process.ana_nocorr_ucc = cms.Path(process.hltHIUCC*process.epetadeco_ana_HI_UCC_nocorr)
