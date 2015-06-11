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
        nonDefaultGlauberModel = cms.string("Hydjet_Drum"),
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
#'/store/user/davidlw/HIMinBiasUPC/Skim_rereco_pixeltracks_v1/4b65ef5aa7a26abf1f962cd25f7df02d/hiMB_88_1_qbI.root'
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_v1/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_9_1_lpo.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.chargedepcorr_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('chargedepcorr_recenter_gen.root')
                                   )

process.ana = cms.Path(process.chargedepcorr_ana_HI)
process.chargedepcorr_ana_HI.centmin = cms.int32(60)
process.chargedepcorr_ana_HI.centmax = cms.int32(80)
process.chargedepcorr_ana_HI.IsReCenter = cms.bool(True)
process.chargedepcorr_ana_HI.TrgTrackCollection = cms.string('hiGeneralTracks')
process.chargedepcorr_ana_HI.TriggerID = cms.string('GenParticle')
process.chargedepcorr_ana_HI.AssociateID = cms.string('GenParticle')
process.chargedepcorr_ana_HI.rhomin = cms.double(0.0)
process.chargedepcorr_ana_HI.rhomax = cms.double(2.0)
