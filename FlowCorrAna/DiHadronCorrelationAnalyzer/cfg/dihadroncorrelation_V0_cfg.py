import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'GR_R_53_LV6::All'
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:startup', '')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
        centralityVariable = cms.string("HFtowers"),
#        nonDefaultGlauberModel = cms.string("Hydjet_Drum"),
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
#'file:/export/d00/scratch/davidlw/output_wsplit_real_mc.root'
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_427_1_3mB.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_103_1_Gat.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_195_1_Hxk.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_445_1_LgV.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_297_1_yHa.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_291_1_vfJ.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_241_1_SmS.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_179_1_A9J.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_280_1_cN4.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_295_1_7E7.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_318_1_KMd.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_325_1_vmj.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_346_1_ffM.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_27_1_Quj.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_338_1_aSx.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_180_1_waT.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_387_1_H3G.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_90_1_max.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_1_1_jn5.root',
'/store/user/davidlw/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/RECO_5320_DEBUG_v3/71a485a731d6b2661f997f58ff50f0c0/reco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_112_1_xLi.root'
                )
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('dihadroncorrelation_mc.root')
                                   )

process.ana_step = cms.Path(process.corr_ana_HI)
#process.ana_step = cms.Path(process.corr_ana)
process.corr_ana_HI.IsCorr = cms.bool(False)
process.corr_ana_HI.IsDebug = cms.bool(True)
process.corr_ana_HI.rhomax = cms.double(2.0)
#process.ana_step = cms.Path(process.corr_ana)
process.corr_ana_HI.centmin = cms.int32(0)
process.corr_ana_HI.centmax = cms.int32(200)
#process.corr_ana.V0CandidateCollection = cms.string('generalV0CandidateLowPt')
#process.corr_ana.TriggerID = cms.string('Kshort')
process.corr_ana_HI.TrgTrackCollection = cms.string('hiGeneralTracks')
process.corr_ana_HI.pttrgmin = cms.vdouble(0.0)
process.corr_ana_HI.pttrgmax = cms.vdouble(100.0)
process.corr_ana_HI.ptassmin = cms.vdouble(0.0)
process.corr_ana_HI.ptassmax = cms.vdouble(100.0)
