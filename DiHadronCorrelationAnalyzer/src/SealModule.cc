#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/DiHadronCorrelationMultiAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EPEtaDecoAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EPEtaDecoAnalyzerSP.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EPEtaDecoAnalyzerSP2.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EPPtDecoAnalyzerSP.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EbyEFlowAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/InvMassAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/MultiplicityAnalyzer.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/ChargeDepCorrAnalyzerSP.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/ChargeDepCorrAnalyzerSP2.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/ChargeDepCorrAnalyzerSP3.h"

//DEFINE_SEAL_MODULE();

DEFINE_FWK_MODULE(DiHadronCorrelationMultiAnalyzer);
DEFINE_FWK_MODULE(EPEtaDecoAnalyzer);
DEFINE_FWK_MODULE(EPEtaDecoAnalyzerSP);
DEFINE_FWK_MODULE(EPEtaDecoAnalyzerSP2);
DEFINE_FWK_MODULE(EPPtDecoAnalyzerSP);
DEFINE_FWK_MODULE(EbyEFlowAnalyzer);
DEFINE_FWK_MODULE(InvMassAnalyzer);
DEFINE_FWK_MODULE(MultiplicityAnalyzer);
DEFINE_FWK_MODULE(ChargeDepCorrAnalyzerSP);
DEFINE_FWK_MODULE(ChargeDepCorrAnalyzerSP2);
DEFINE_FWK_MODULE(ChargeDepCorrAnalyzerSP3);
