# Auto generated configuration file
# using: 
# Revision: 1.168.2.1 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: step2 -s RAW2DIGI,RECO --datatier GEN-SIM-RECO --eventcontent RECODEBUG --conditions auto:mc --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('TEST')

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
process.GlobalTag.globaltag = 'START44_V9E::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500)
)

# message logger
#process.MessageLogger.categories = ['TrkEffAnalyzer']
#process.MessageLogger.debugModules = ['*']
#process.MessageLogger.cerr = cms.untracked.PSet(
#    threshold = cms.untracked.string('DEBUG'),
#    DEBUG = cms.untracked.PSet(
#        limit = cms.untracked.int32(0)
#    ),
#    INFO = cms.untracked.PSet(
#        limit = cms.untracked.int32(0)
#    ),
#    TrkEffAnalyzer = cms.untracked.PSet(
#        limit = cms.untracked.int32(-1)
#    )
#)

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Input source
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
'/store/mc/Fall11/MinBias_TuneZ2_7TeV-pythia6/GEN-SIM-RECODEBUG/NoPileUp_START42_V14B-v1/20000/00370B82-2540-E311-BB9E-00266CF258D8.root'
#'root://xrootd1.cmsaf.mit.edu//store/user/vzhukova/HIJING_MB/HIJING_MB_RECO_v3/13a591fee6315e7fb1e99e6ba8e52eaa/reco_hijing_2582_1_tV4.root',
#'root://xrootd1.cmsaf.mit.edu//store/user/vzhukova/HIJING_MB/HIJING_MB_RECO_v3/13a591fee6315e7fb1e99e6ba8e52eaa/reco_hijing_1000_1_Bov.root'
)
)

# Track efficiency analyzer
process.load("RiceHIG.TrkEffAnalyzer.trkEffAnalyzer_cff")
process.load("RiceHIG.Skim2013.ppExtraReco_cff")
process.trkEffAnalyzer.tracks = cms.untracked.InputTag('selectTracks')
process.trackingParticleRecoTrackAsssociation.label_tr = cms.untracked.InputTag('selectTracks')
process.trkEffAnalyzer.doAssociation = cms.untracked.bool(True) # association done inside analyzer (not from map)
process.trkEffAnalyzer.hasSimInfo = cms.untracked.bool(True) # for MC matching

# retracking
#process.initialStepSeeds.RegionFactoryPSet.RegionPSet.originRadius = 0.2
#process.detachedTripletStepSeeds.RegionFactoryPSet.RegionPSet.ptMin = 0.075
#process.detachedTripletStepSeeds.RegionFactoryPSet.RegionPSet.originRadius = 2.0 
#process.detachedTripletStepSeeds.RegionFactoryPSet.RegionPSet.originHalfLength = 15.0
#process.lowPtTripletStepSeeds.RegionFactoryPSet.RegionPSet.ptMin = 0.075
#process.mixedTripletStepSeedsA.RegionFactoryPSet.RegionPSet.ptMin = 0.1
#process.mixedTripletStepSeedsB.RegionFactoryPSet.RegionPSet.ptMin = 0.2
#process.pixelLessStepSeeds.RegionFactoryPSet.RegionPSet.ptMin = 0.2
#process.source.dropDescendantsOfDroppedBranches=cms.untracked.bool(False)
#process.source.inputCommands=cms.untracked.vstring(
#            'keep *',
#            'drop *_*generalTracks*_*_*',
#            'drop *_*offlinePrimaryVertices*_*_*'
#)

#process.rechits = cms.Sequence(process.siPixelRecHits * process.siStripMatchedRecHits)
#process.ppTrackReco = cms.Sequence(process.rechits * process.iterTracking * process.offlinePrimaryVertices)
#process.extra_reco = cms.Path(process.ppTrackReco)

# Output definition
process.RECODEBUGEventContent.outputCommands.extend(
    ['keep *_trackingParticleRecoTrackAsssociation_*_*'] )
process.output = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.RECODEBUGEventContent.outputCommands,
    fileName = cms.untracked.string('output.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RECO'),
        filterName = cms.untracked.string('')
    )
)

# Additional output definition
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('hists.root')
                                   )

#process.load("GeneratorInterface.HiGenCommon.highMultiplicityGenFilter_cfi")
#process.highMultiplicityGenFilter.nMin = cms.untracked.int32(200)

# Path and EndPath definitions
process.ana_step = cms.Path(
                            process.ppSingleTrackFilterSequence*process.trkEffAnalyzer)
#process.out_step = cms.EndPath(process.output)
