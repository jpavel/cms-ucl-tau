// Dear emacs, this is -*- c++ -*-
// $Id: CycleCreators.py 344 2012-12-13 13:10:53Z krasznaa $
#ifndef WHanalysis_H
#define WHanalysis_H

// SFrame include(s):
// SFrame include(s):
#include "core/include/SCycleBase.h"
#include "plug-ins/include/SSummedVar.h"
#include "core/include/SError.h"
#include "core/include/SCycleBaseNTuple.h"
#include "plug-ins/include/SInputVariables.h"

// c++ includes
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

// my classes
#include "myevent.h"
#include "TLorentzVector.h"
#include "TProfile.h"
#include "TH2.h"

// PU weight

#include "LumiReweightingStandAlone.h"

/**
 *   @short Put short description of class here
 *
 *          Put a longer description over here...
 *
 *  @author Put your name here
 * @version $Revision: 344 $
 */
class WHanalysis : public SCycleBase {

public:
   /// Default constructor
   WHanalysis();
   /// Default destructor
   ~WHanalysis();

   /// Function called at the beginning of the cycle
   virtual void BeginCycle() throw( SError );
   /// Function called at the end of the cycle
   virtual void EndCycle() throw( SError );

   /// Function called at the beginning of a new input data
   virtual void BeginInputData( const SInputData& ) throw( SError );
   /// Function called after finishing to process an input data
   virtual void EndInputData  ( const SInputData& ) throw( SError );

   /// Function called after opening each new input file
   virtual void BeginInputFile( const SInputData& ) throw( SError );

   /// Function called for every event
   virtual void ExecuteEvent( const SInputData&, Double_t ) throw( SError );
   
   bool Trg_MC_12(myevent* m, bool found);
   std::vector<myobject> SelectGoodVxVector(std::vector<myobject> _vertex, double _normChi2, int _ndof, double _dZ);
   
   double deltaR(double eta1, double phi1, double eta2, double phi2);
   double deltaR(myobject o1, myobject o2);
   myobject ClosestInCollection(myobject o1, std::vector<myobject> collection, double max);
   double DistanceToClosestInCollection(myobject o1, std::vector<myobject> collection);
   double PairMass(myobject Hcand1, myobject Hcand2);	
   double PairPt(myobject Hcand1, myobject Hcand2);	
   double RelIso(myobject mu);
   double Tmass(myevent *m, myobject mu);
   bool PFMuonID(myobject mu);
     bool CheckOverlapLooseElectron(myobject tau, std::vector<myobject> elCollection, double maxR, double isoVal, bool verb);
   bool CheckOverlapLooseMuon(myobject tau, std::vector<myobject> muCollection, double maxR, double isoVal);
   std::vector<myobject> SelectGoodMuVector(std::vector<myobject> _muon, bool verb, double muPt_, double muEta_);
   std::vector<myobject> SelectGoodElVector(std::vector<myobject> _electron, bool verb, double elPt_, double elEta_ );
   void CrossCleanWithMu(std::vector<myobject>* _input, std::vector<myobject> _muon, bool verb, double _maxDeltaR, double _muIso, bool _looseMuId);
   bool isGoodMu(myobject mu);
   bool isLooseMu(myobject mu);
   bool isGoodEl(myobject el);


private:
   //
   // Put all your private variables here
   //

	// input variables
	
	myevent *m;
	
	// histograms
	
	TH1* h_PU_weight;
	TH1* h_nPU_raw;
	TH1* h_nPU_reweight;
	
	//helpers
	reweight::LumiReWeighting* LumiWeights_;

	// properties
	std::string InTreeName;
	double maxDeltaR;
	
	std::string doubEle;
	std::string doubEle2;
	
    std::string doubMu;
    std::string doubMu2;
    std::string doubMu3;
    
   
   
    bool isSimulation;
    bool is2011;
   
    bool is2012_53;
   
    bool vetoMuonTrigger;
    bool vetoElectronTrigger;
    
    bool IgnoreSF;
    bool IgnorePUW;
    
    double examineEvent;
    
    
    bool UseLongEvent;
    double OverM;
    double BelowM;
    
	
	 // bookkeeping variables
    
    ofstream lumi;
	long current_run;
	long current_lumi;
	SSummedVar< Int_t > m_allEvents;
	
	// output variables in ntuple
	
	Float_t out_pt;

   // Macro adding the functions for dictionary generation
   ClassDef( WHanalysis, 0 );

}; // class WHanalysis

#endif // WHanalysis_H

