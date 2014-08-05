/** \class PAHighMultiplicityPileUpFilter
 *
 *  
 *  This class is an EDFilter for rejecting pPb events with multiple collisions
 *  (pileup). This is performed by looking at the correlations among the number of
 *  tracks from each vertex and the distance between two vertices.
 *  
 *  Authors: Wei Li - Rice University
 */


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <string>
#include <vector>
#include <algorithm>
#include "TF1.h"
#include "TF2.h"

#include <DataFormats/VertexReco/interface/Vertex.h>
#include <DataFormats/VertexReco/interface/VertexFwd.h>

#include "FWCore/MessageLogger/interface/MessageLogger.h"

class PAHighMultiplicityPileUpFilter : public edm::EDFilter {
    public:
       explicit PAHighMultiplicityPileUpFilter(const edm::ParameterSet&);
       ~PAHighMultiplicityPileUpFilter();
       virtual void endJob() ;

       virtual bool filter(edm::Event&, const edm::EventSetup&);

    private:

       edm::InputTag vtxSrc_;
       std::vector<double> CutParameters0_;
       std::vector<double> CutParameters1_;

       int  mode_; 
       TF1* func1D_;
       TF2* func2D_;
};


PAHighMultiplicityPileUpFilter::PAHighMultiplicityPileUpFilter(const edm::ParameterSet& iConfig) :
vtxSrc_(iConfig.getParameter<edm::InputTag>("vtxSrc")),
CutParameters0_(iConfig.getParameter<std::vector<double> >("CutParameters0")),
CutParameters1_(iConfig.getParameter<std::vector<double> >("CutParameters1")),
mode_(iConfig.getParameter<int>("mode"))
{
  if(mode_==0)
  {
    func2D_ = new TF2("func2D","[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x/[4])*x**[7]+[5])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])",0,50.0,0,500);
    for(int i=0;i<12;i++) func2D_->SetParameter(i,CutParameters0_[i]);
  }
  else{
    func2D_ = new TF2("func2D","[0]*y**([2]*exp(-x**[3]/[1])*x**[4])",0,50.0,0,500);
    for(int i=0;i<5;i++) func2D_->SetParameter(i,CutParameters1_[i]);
    func1D_ = new TF1("func1D","[0]*x**[1]",0,500);
    for(int i=5;i<7;i++) func1D_->SetParameter(i-5,CutParameters1_[i]);
  }  
}

PAHighMultiplicityPileUpFilter::~PAHighMultiplicityPileUpFilter()
{
}

bool
PAHighMultiplicityPileUpFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   bool accepted = true;

   Handle<std::vector<reco::Vertex> > vcol;
   iEvent.getByLabel(vtxSrc_, vcol);

   std::vector<reco::Vertex> vsorted = *vcol;
   // sort the vertcies by number of tracks in descending order
   std::sort( vsorted.begin(), vsorted.end(), 
              []( reco::Vertex a, reco::Vertex b) 
   {
      return  a.tracksSize() > b.tracksSize() ? true : false ;
   });

   // check additional PVs
   for (unsigned int i =1; i<vsorted.size(); i++)
   {
     double dz = fabs( vsorted[i].z() - vsorted[0].z() );
//     double dx = fabs( vsorted[i].x() - vsorted[0].x() );
//     double dy = fabs( vsorted[i].y() - vsorted[0].y() );
//     double dxy  = sqrt ( dx*dx + dy*dy );
     double nTrk = vsorted[i].tracksSize();

     if(nTrk>func2D_->Eval(dz,vsorted[0].tracksSize()) && dz>0.2) accepted = false; 
     if(nTrk>func1D_->Eval(vsorted[0].tracksSize()) && dz<=0.2) accepted = false;

//     if(dxy>0.05) accepted = true;
   }

   return accepted;
}

void
PAHighMultiplicityPileUpFilter::endJob()
{
}

DEFINE_FWK_MODULE(PAHighMultiplicityPileUpFilter);
