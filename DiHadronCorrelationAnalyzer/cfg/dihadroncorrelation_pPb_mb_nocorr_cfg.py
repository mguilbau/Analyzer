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
#'file:/mnt/hadoop/cms/store/user/davidlw/JetHT/PP2012_FlowCorr_Jet400_v1/8db2b1c671424ba59874aa53380c8144/pPb_HM_53_1_t5X.root'
#'file:/mnt/hadoop/cms/store/user/davidlw/Hijing_PPb502_MinimumBias/RecoSkim_batch4_v1/84cb8c951385c1f95541c031462cec6b/pPb_MB_22_1_zGV.root'
'file:/mnt/hadoop/cms/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHM_Gplus_v15/702fa69daea9da948fe2472b4d29b5b5/pPb_HM_493_1_3KA.root'
#'file:/mnt/hadoop/cms/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHM_Gplus_Rereco_D0_v1/3d1d10b29b335c650ac2f0572abbbd93/pPb_HM_392_1_MwM.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.dihadroncorrelation_cff")
process.load("FlowCorrAna.V0Analysis.v0selector_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('dihadroncorrelation.root')
                                   )

#process.ana = cms.Path(process.hltHM190On*process.corr_ana_pPb)
#process.ana = cms.Path(process.selectV0CandidatesNewlambda*process.corr_ana_pPb)
process.ana = cms.Path(process.corr_ana_pPb)
process.corr_ana_pPb.IsCorr = cms.bool(False)
process.corr_ana_pPb.IsDebug = cms.bool(True)
process.corr_ana_pPb.pttrgmin = cms.vdouble(0.0)
process.corr_ana_pPb.pttrgmax = cms.vdouble(10000.0)
process.corr_ana_pPb.ptassmin = cms.vdouble(0.0)
process.corr_ana_pPb.ptassmax = cms.vdouble(10000.0)
#process.corr_ana_pPb.TriggerID = cms.string('LambdaP')
#process.corr_ana_pPb.AssociateID = cms.string('LambdaM')
#process.corr_ana_pPb.V0CandidateCollection = cms.string('selectV0CandidatesNewlambda')
