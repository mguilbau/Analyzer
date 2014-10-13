import FWCore.ParameterSet.Config as cms

process = cms.Process("V0Val")
process.load("FWCore.MessageService.MessageLogger_cfi")

### standard includes
process.load('Configuration.StandardSequences.Generator_cff')
process.load('GeneratorInterface.HiGenCommon.VtxSmearedRealisticPPbBoost8TeVCollision_cff')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load("Configuration.StandardSequences.Digi_cff")
process.load("Configuration.StandardSequences.DigiToRaw_cff")
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("SimGeneral.MixingModule.mixNoPU_cfi")
process.load("SimGeneral.TrackingAnalysis.trackingParticles_cfi")

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'STARTHI53_V17::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
'/store/user/davidlw/Hijing_PPb502_MinimumBias/RecoSkim_batch1_v1/84cb8c951385c1f95541c031462cec6b/pPb_MB_100_1_tG6.root'
#'root://xrootd1.cmsaf.mit.edu//store/user/vzhukova/HIJING_MB/HIJING_MB_RECO_v3/13a591fee6315e7fb1e99e6ba8e52eaa/reco_hijing_2582_1_tV4.root'
#'root://xrootd1.cmsaf.mit.edu//store/user/vzhukova/HIJING_MB/HIJING_MB_RECO_v3/13a591fee6315e7fb1e99e6ba8e52eaa/reco_hijing_1000_1_Bov.root'
#'/store/user/vzhukova/HYDGET_PERIPH_batch7/HYDGET_PERIPH_RECO_batch7/b7d33bba7673cdb1ee6f4983c0800c79/HYDGET_PERIPH_RECO_10_1_7bq.root'
#'root://xrootd1.cmsaf.mit.edu//store/user/vzhukova/HIJING_GEN-SIM_YUE-SHI_Minbias_2_v1/HIJING_RECO_YUE-SHI_Minbias__2_v1/b7d33bba7673cdb1ee6f4983c0800c79/hijing_reco_fix_4_2_RU0.root'
#'root://xrootd1.cmsaf.mit.edu//store/himc/HiWinter13/Hijing_PPb502_MinimumBias/GEN-SIM-RECO/pa_STARTHI53_V25-v1/30000/64B44ED9-EF77-E211-825A-00266CF97FF4.root'
                )
                            )

### validation-specific includes
process.load("SimTracker.TrackAssociation.TrackAssociatorByHits_cfi")
process.load("SimTracker.TrackAssociation.TrackAssociatorByChi2_cfi")
process.load("RiceHIG.V0Analysis.v0selector_cff")
process.load("RiceHIG.V0Analysis.v0validator_cff")

process.generalV0CandidatesNew = process.generalV0Candidates.clone (
    tkNhitsCut = cms.int32(0),
    tkChi2Cut = cms.double(7.0),
    dauTransImpactSigCut = cms.double(0.0),
    dauLongImpactSigCut = cms.double(0.0),
    xiVtxSignificance3DCut = cms.double(0.0),
    xiVtxSignificance2DCut = cms.double(0.0),
    vtxSignificance2DCut = cms.double(0.0),
    vtxSignificance3DCut = cms.double(4.0)
)   

process.v0Validator.kShortCollection = cms.InputTag('selectV0CandidatesNewkshort:Kshort')
process.v0Validator.lambdaCollection = cms.InputTag('selectV0CandidatesNewlambda:Lambda')
process.v0Validator.isMatchByHitsOrChi2 = cms.bool(True)
process.v0Validator.isMergedTruth = cms.bool(False)

process.selectV0CandidatesNewlambda.v0CollName = cms.string("generalV0CandidatesNew")
process.selectV0CandidatesNewkshort.v0CollName = cms.string("generalV0CandidatesNew")
process.selectV0CandidatesNewlambda.dxySigCut1 = cms.double(0.0)
process.selectV0CandidatesNewlambda.dxySigCut2 = cms.double(0.0)
process.selectV0CandidatesNewlambda.dzSigCut1 = cms.double(0.0)
process.selectV0CandidatesNewlambda.dzSigCut2 = cms.double(0.0)
process.selectV0CandidatesNewkshort.dxySigCut1 = cms.double(0.0)
process.selectV0CandidatesNewkshort.dxySigCut2 = cms.double(0.0)
process.selectV0CandidatesNewkshort.dzSigCut1 = cms.double(0.0)
process.selectV0CandidatesNewkshort.dzSigCut2 = cms.double(0.0)

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('v0validation.root')
                                   )
process.TrackAssociatorByHits.Cut_RecoToSim = cms.double(0.5)
process.TrackAssociatorByChi2ESProducer.chi2cut = cms.double(25.0)

process.v0validation = cms.Sequence(process.selectV0CandidatesNewlambda*process.selectV0CandidatesNewkshort*process.v0Validator)

process.p = cms.Path(process.v0validation)

process.schedule = cms.Schedule(process.p)
