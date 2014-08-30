import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'GR_R_53_LV6::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
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
#'/store/user/davidlw/HIMinBiasUPC/Skim_rereco_pixeltracks_v1/4b65ef5aa7a26abf1f962cd25f7df02d/hiMB_69_1_5b2.root'
'/store/user/davidlw/HIMinBiasUPC/Skim_rereco_generaltracks_MB_v1/9c1b4b9b6b9ff3e493a474ba7d01bc76/hiMB_1331_1_jU2.root'
#'/store/user/davidlw/rereco_53X.root'
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

process.ana_hfp = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfp)
process.ana_hfm = cms.Path(process.hltHIMB*process.epetadeco_ana_HI_hfm)
process.epetadeco_ana_HI_hfp.centmin = cms.int32(0)
process.epetadeco_ana_HI_hfp.centmax = cms.int32(2)
#process.epetadeco_ana_HI_hfp.IsCorr = cms.bool(False)
process.epetadeco_ana_HI_hfm.centmin = cms.int32(0)
process.epetadeco_ana_HI_hfm.centmax = cms.int32(2)
#process.epetadeco_ana_HI_hfm.IsCorr = cms.bool(False)
