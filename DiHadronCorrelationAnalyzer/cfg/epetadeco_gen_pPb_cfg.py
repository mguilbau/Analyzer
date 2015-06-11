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
#'file:/mnt/hadoop/cms/store/user/davidlw/PAHighPt/PA2013_FlowCorr_PromptReco_TrkHM_Gplus_Rereco_v15/702fa69daea9da948fe2472b4d29b5b5/pPb_HM_282_1_izm.root'
'/store/user/davidlw/ReggeGribovPartonMCfix_EposLHC_5TeV_pPb/RecoSkim_batch1_v1/84cb8c951385c1f95541c031462cec6b/pPb_MB_111_4_M4A.root'
                )
#                                secondaryFileNames = cms.untracked.vstring('')
                            )
process.load("FlowCorrAna.DiHadronCorrelationAnalyzer.epetadeco_cff")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('epetadeco_gen.root')
                                   )

process.ana = cms.Path(process.epetadeco_ana_pPb_hfp*process.epetadeco_ana_pPb_hfm)
process.epetadeco_ana_pPb_hfp.nmin = cms.int32(100)
process.epetadeco_ana_pPb_hfp.nmax = cms.int32(1000)
process.epetadeco_ana_pPb_hfm.nmin = cms.int32(100)
process.epetadeco_ana_pPb_hfm.nmax = cms.int32(1000)
process.epetadeco_ana_pPb_hfp.rhomin = cms.double(0.0)
process.epetadeco_ana_pPb_hfp.rhomax = cms.double(2.0)
process.epetadeco_ana_pPb_hfm.rhomin = cms.double(0.0)
process.epetadeco_ana_pPb_hfm.rhomax = cms.double(2.0)
process.epetadeco_ana_pPb_hfp.TriggerID = cms.string('GenParticle')
process.epetadeco_ana_pPb_hfp.AssociateID = cms.string('GenParticle')
process.epetadeco_ana_pPb_hfm.TriggerID = cms.string('GenParticle')
process.epetadeco_ana_pPb_hfm.AssociateID = cms.string('GenParticle')
