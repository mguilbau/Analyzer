#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/DiHadronCorrelationMultiAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EPEtaDecoAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EbyEFlowAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/InvMassAnalyzer.h"

//DEFINE_SEAL_MODULE();

DEFINE_FWK_MODULE(DiHadronCorrelationMultiAnalyzer);
DEFINE_FWK_MODULE(EPEtaDecoAnalyzer);
DEFINE_FWK_MODULE(EbyEFlowAnalyzer);
DEFINE_FWK_MODULE(InvMassAnalyzer);
