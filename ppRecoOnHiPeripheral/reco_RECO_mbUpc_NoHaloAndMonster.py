# Auto generated configuration file
# using:
# Revision: 1.341.2.2
# Source: /local/reps/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v
# with command line options: reco -s RECO --eventcontent RECO --conditions FrontierConditions_GlobalTag,GR_P_V27A::All --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('ppRECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 200 

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

# Input source
process.source = cms.Source("PoolSource",
                            secondaryFileNames = cms.untracked.vstring(),
                            fileNames = cms.untracked.vstring('/store/user/davidlw/rereco_53X.root')
                                                   )

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool( False ))

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.2 $'),
    annotation = cms.untracked.string('reco nevts:1'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

process.RECOoutput = cms.OutputModule("PoolOutputModule",
    eventAutoFlushCompressedSize = cms.untracked.int32(15728640),
    outputCommands = process.RECOEventContent.outputCommands,
    fileName = cms.untracked.string('/export/d00/scratch/davidlw/reco_ppRECO_mbUpc_53X.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('reconstruction_step')
    )
)
# Additional output definition
process.RECOoutput.outputCommands.extend(cms.untracked.vstring('drop *_*muons_*_RECO'))
process.RECOoutput.outputCommands.extend(cms.untracked.vstring('drop *_*Muons_*_RECO'))
process.RECOoutput.outputCommands.extend(cms.untracked.vstring('drop *_muIsoDepositTk_*_RECO'))
process.RECOoutput.outputCommands.extend(cms.untracked.vstring('drop *_muIsoDepositCalByAssociatorTowers_*_RECO'))
process.RECOoutput.outputCommands.extend(cms.untracked.vstring('drop *_*Jets_*_RECO'))
process.RECOoutput.outputCommands.extend(cms.untracked.vstring('drop *_offlineBeamSpot_*_RECO'))
process.RECOoutput.outputCommands.extend(cms.untracked.vstring('drop *_*Cluster*_*_RECO'))
process.RECOoutput.outputCommands.extend(cms.untracked.vstring('drop *_photon*_*_RECO'))
process.RECOoutput.outputCommands.extend(cms.untracked.vstring('drop *_Castor*_*_RECO'))
process.RECOoutput.outputCommands.extend(cms.untracked.vstring('drop *_ak7CastorJetID_*_RECO'))

process.RECOoutput.outputCommands.extend(cms.untracked.vstring('keep *_siPixelRecHits_*_ppRECO'))
process.RECOoutput.outputCommands.extend(cms.untracked.vstring('keep *_siPixelClusters_*_RECO'))
process.RECOoutput.outputCommands.extend(cms.untracked.vstring('keep *_hiCentrality_*_RECO'))
process.RECOoutput.outputCommands.extend(cms.untracked.vstring('keep *_hiEvtPlane_*_RECO'))

# Other statements
process.GlobalTag.globaltag = 'GR_R_53_LV6::All'
process.GlobalTag.toGet.extend([
  cms.PSet(record = cms.string("HeavyIonRcd"),
    tag = cms.string("CentralityTable_HFtowers200_Glauber2010A_v5315x01_offline"),
    connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
    label = cms.untracked.string("HFtowers")
  )
])

# ___________________________________________________________________________________________
# #### set the centrality selection filter
process.load("RecoHI.HiCentralityAlgos.CentralityFilter_cfi")

process.HeavyIonGlobalParameters = cms.PSet(centralityVariable = cms.string("HFtowers"),
                                            centralitySrc = cms.InputTag("hiCentrality")
                                            )
process.centralityFilter.selectedBins = [
                                                                 96,97,98,99,100,
                                         101,102,103,104,105,106,107,108,109,110,
                                         111,112,113,114,115,116,117,118,119,120,
                                         121,122,123,124,125,126,127,128,129,130,
                                         131,132,133,134,135,136,137,138,139,140,
                                         141,142,143,144,145,146,147,148,149,150,
                                         151,152,153,154,155,156,157,158,159,160,
                                         161,162,163,164,165,166,167,168,169,170,
                                         171,172,173,174,175,176,177,178,179,180,
                                         181,182,183,184,185,186,187,188,189,190,
                                         191,192,193,194,195,196,197,198,199,200
                                        ];

# #### HLT filters:
process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltMinBiasUPC = process.hltHighLevel.clone()
process.hltMinBiasUPC.HLTPaths = ["HLT_HIMinBiasHfOrBSC_v*",
                                  "HLT_HIUPCNeuEG2Pixel_SingleTrack_v*",
                                  "HLT_HIUPCNeuEG5Pixel_SingleTrack_v*",
                                  "HLT_HIUPCNeuMuPixel_SingleTrack_v*",
                                  "HLT_HIMinBiasZDC_Calo_PlusOrMinus_v*",
                                  "HLT_HIMinBiasZDC_PlusOrMinusPixel_SingleTrack_v*",
                                  "HLT_HIZeroBias_v*"
                                  ]

# #### reject monster and beam halo
# Reject BSC beam halo L1 technical bits
process.load("L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff")
process.load("HLTrigger.HLTfilters.hltLevel1GTSeed_cfi")
process.noBSChalo = process.hltLevel1GTSeed.clone(
    L1TechTriggerSeeding = cms.bool(True),
    L1SeedsLogicalExpression = cms.string('NOT (36 OR 37 OR 38 OR 39)')
)
# Cluster-shape filter re-run offline
process.load("RecoLocalTracker.SiPixelRecHits.SiPixelRecHits_cfi")
process.load("HLTrigger.special.hltPixelClusterShapeFilter_cfi")
process.hltPixelClusterShapeFilter.inputTag = "siPixelRecHits"

process.collisionEventSelection_HaloAndMonster = cms.Sequence(process.noBSChalo *
                                       process.siPixelRecHits *
                                       process.hltPixelClusterShapeFilter)

process.GoodEventFilterSequence = cms.Sequence(process.hltMinBiasUPC*process.collisionEventSelection_HaloAndMonster*process.centralityFilter)

# ___________________________________________________________________________________________
process.reconstruction_step = cms.Path(process.reconstruction_fromRECO)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)

# Schedule definition
process.schedule = cms.Schedule(process.reconstruction_step, process.endjob_step,process.RECOoutput_step)

# filter all path with the good event filter sequence
for path in process.paths:
        getattr(process,path)._seq = process.GoodEventFilterSequence * getattr(process,path)._seq
