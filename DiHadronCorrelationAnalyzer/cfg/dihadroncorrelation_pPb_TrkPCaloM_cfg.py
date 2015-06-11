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
'file:/mnt/hadoop/cms/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHMPt12_Gplus_v15/67b343be419cbc696fd1a318fe62657e/pPb_HM_389_1_Fga.root',
'file:/mnt/hadoop/cms/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHMPt12_Gplus_v15/67b343be419cbc696fd1a318fe62657e/pPb_HM_433_1_fZh.root',
'file:/mnt/hadoop/cms/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHMPt12_Gplus_v15/67b343be419cbc696fd1a318fe62657e/pPb_HM_392_1_bHs.root',
'file:/mnt/hadoop/cms/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHMPt12_Gplus_v15/67b343be419cbc696fd1a318fe62657e/pPb_HM_387_1_CA8.root',
'file:/mnt/hadoop/cms/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHMPt12_Gplus_v15/67b343be419cbc696fd1a318fe62657e/pPb_HM_432_2_Liv.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('dihadroncorrelation.root')
                                   )

process.ana = cms.Path(process.corr_ana_pPb_TrkCalo)
process.corr_ana_pPb_TrkCalo.etatrgmin = cms.double(0.0)
process.corr_ana_pPb_TrkCalo.etatrgmax = cms.double(2.4)
process.corr_ana_pPb_TrkCalo.etaassmin = cms.double(-5.0)
process.corr_ana_pPb_TrkCalo.etaassmax = cms.double(-3.0)
