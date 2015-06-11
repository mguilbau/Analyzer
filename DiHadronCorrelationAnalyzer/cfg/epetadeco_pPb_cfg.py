import FWCore.ParameterSet.Config as cms

process = cms.Process("corr")
process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
#'/store/user/davidlw/HIMinBiasUPC/PR2011_MBUCC_TRKANASKIM_official_v1/71a7d203fff2b3f389673e6fdd587ee0/hiGoodColl_1023_1_S52.root'
#'root://xrootd.unl.edu//store/user/appeltel/HIMinBiasUPC/pixelTrackReco_devel_v0/a236e4501225ae15b3601563d612abb5/pixeltrackreco_6_1_qSR.root'
'/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHM_Gplus_Rereco_v15/702fa69daea9da948fe2472b4d29b5b5/pPb_HM_260_1_oTx.root'
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

process.ana = cms.Path(process.epetadeco_ana_150185_seq)
process.epetadeco_ana_pPb_hfp.nmin = cms.int32(150)
process.epetadeco_ana_pPb_hfp.nmax = cms.int32(185)
process.epetadeco_ana_pPb_hfm.nmin = cms.int32(150)
process.epetadeco_ana_pPb_hfm.nmax = cms.int32(185)
