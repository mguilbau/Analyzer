import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/user/davidlw/HIMinBiasUPC/PR2011_MBUCC_TRKANASKIM_official_v1/71a7d203fff2b3f389673e6fdd587ee0/hiGoodColl_1023_1_S52.root'
#'root://xrootd.unl.edu//store/user/appeltel/HIMinBiasUPC/pixelTrackReco_devel_v0/a236e4501225ae15b3601563d612abb5/pixeltrackreco_6_1_qSR.root'
'file:/mnt/hadoop/cms/store/user/davidlw/HIMinBiasUPC/PR2011_MBPPRereco_TRKANASKIM_v4/2be5f21752c831f670ba8ae18cdae752/pPb_HM_989_1_Wq1.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.chargedepcorr_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltHIMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltHIMB.HLTPaths = ['HLT_HIMinBiasHfOrBSC_*'] # for allphysics
process.hltHIMB.andOr = cms.bool(True)
process.hltHIMB.throw = cms.bool(False)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('chargedepcorr.root')
                                   )

process.ana = cms.Path(process.hltHIMB*process.chargedepcorr_ana_pPb)
process.chargedepcorr_ana_pPb.nmin = cms.int32(185)
process.chargedepcorr_ana_pPb.nmax = cms.int32(260)
