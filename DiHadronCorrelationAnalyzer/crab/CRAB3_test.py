import os
from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'pp_Data_Ridge13TeV_test'
config.General.workArea = 'pp_Data_Ridge13TeV_test'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
#config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = os.path.expandvars('$CMSSW_BASE/src/FlowCorrAna/DiHadronCorrelationAnalyzer/cfg/dihadroncorrelation_pp2015_mb_cfg.py')

config.section_("Data")
config.Data.inputDataset = '/MinBias_TuneMonash13_13TeV-pythia8/davidlw-RecoSkim_batch4_v1-00b3bbd68a41a1bc2b98cf5da8508e09/USER'
#config.Data.inputDataset = '/MinBias_TuneZ2_7TeV-pythia6/davidlw-Skim_v15-1709136df11f28c8f8a8a944d51c46a6/USER'
#config.Data.userInputFiles = list(open('HMMC90.txt'))
config.Data.inputDBS = 'phys03'
#config.Data.primaryDataset = 'MinBias_TuneZ2star_7TeV_pythia6'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
#config.Data.outLFN = '/store/user/zhchen/'
config.Data.publication = False
config.Data.publishDBS = 'phys03'
config.Data.publishDataName = 'pp_Data_Ridge13TeV_test'

config.section_("Site")
config.Site.storageSite = 'T2_CH_CERN'
config.Site.whitelist = ['T2_US_MIT']
