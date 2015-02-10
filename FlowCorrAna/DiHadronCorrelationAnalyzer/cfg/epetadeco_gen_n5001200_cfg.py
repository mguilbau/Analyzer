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
'/store/user/davidlw/AMPT_hijing_53x_v1/AMPT_hijing_53x_v1/192217a8621b84870589d7611656bfcb/AMPT_PPb_5020GeV_MinimumBias_cfi_py_GEN_698_1_vN8.root'
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

process.ana = cms.Path(process.epetadeco_ana_HI_hfp*process.epetadeco_ana_HI_hfm)
process.epetadeco_ana_HI_hfp.nmin = cms.int32(500)
process.epetadeco_ana_HI_hfp.nmax = cms.int32(1200)
process.epetadeco_ana_HI_hfm.nmin = cms.int32(500)
process.epetadeco_ana_HI_hfm.nmax = cms.int32(1200)
process.epetadeco_ana_HI_hfp.IsVtxSel = cms.bool(False)
process.epetadeco_ana_HI_hfp.IsGenMult = cms.bool(True)
process.epetadeco_ana_HI_hfm.IsVtxSel = cms.bool(False)
process.epetadeco_ana_HI_hfm.IsGenMult = cms.bool(True)
#process.epetadeco_ana_HI_hfp.IsCorr = cms.bool(False)
process.epetadeco_ana_HI_hfp.TriggerID = cms.string('GenParticle')
process.epetadeco_ana_HI_hfp.AssociateID = cms.string('GenParticle')
process.epetadeco_ana_HI_hfm.TriggerID = cms.string('GenParticle')
process.epetadeco_ana_HI_hfm.AssociateID = cms.string('GenParticle')
