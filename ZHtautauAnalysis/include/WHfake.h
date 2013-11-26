// Dear emacs, this is -*- c++ -*-
// $Id: CycleCreators.py 344 2012-12-13 13:10:53Z krasznaa $
#ifndef WHfake_H
#define WHfake_H

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
#include "kNNEvaluator.h"

/**
 *   @short Put short description of class here
 *
 *          Put a longer description over here...
 *
 *  @author Put your name here
 * @version $Revision: 344 $
 */
class WHfake : public SCycleBase {

public:
   /// Default constructor
   WHfake();
   /// Default destructor
   ~WHfake();

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
   double PairMass(myobject Hcand1, myobject Hcand2);	
   double PairPt(myobject Hcand1, myobject Hcand2);	
   double RelIso(myobject mu, bool verb);
   double Tmass(myevent *m, myobject mu);
   bool PFMuonID(myobject mu);
   std::vector<myobject> SelectGoodMuVector(std::vector<myobject> _muon, bool verb, double muPt_, double muEta_);
   //std::vector<myobject> SelectGoodMuVector(std::vector<myobject> _muon, std::vector<myobject> _jets, bool verb, double muPt_, double muEta_);
   std::vector<myobject> SelectGoodElVector(std::vector<myobject> _electron, bool verb, double elPt_, double elEta_);
   bool LooseEleId(float pt, float eta, double value);
   bool LooseEleId(myobject o);
   bool TightEleId(float pt, float eta, double value);
   bool TightEleId(myobject o);
   myobject ClosestInCollection(myobject o1, std::vector<myobject> collection, double max);
   void CrossCleanWithMu(std::vector<myobject>* _input, std::vector<myobject> _muon, bool verb, double _maxDeltaR, double _muIso, bool _looseMuId);
   void CrossCleanWithEle(std::vector<myobject>* _ele, std::vector<myobject> _input, bool verb, double _maxDeltaR);
   bool isGoodMu(myobject mu);
   bool isLooseMu(myobject mu);
   bool isGoodEl(myobject el);

private:
   //
   // Put all your private variables here
   //

	// input variables
	
	myevent *m;

	std::vector<myobject> tag;
	std::vector<myobject> probe;
	std::vector<myobject> goodTau;
        std::vector<std::pair<myobject,myobject> > pair;
        std::vector<int> nJets;
        std::vector<myobject> closestJet_subLead;	
        std::vector<myobject> closestJet_lead;	
	// histograms

	TH1* h_visMass_P1P2P3;
	TH1* h_LT_w;
	
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
    double bTagValue;
    double LTValue_mmt;
    double LTValue_eet;
    
    std::string syncFileName;
    bool doSync;
    
    TFile* syncOut_lead;
    TFile* syncOut_subLead;
    TTree* syncOutTree_lead;
    TTree* syncOutTree_subLead;
	
	 // bookkeeping variables
    
    ofstream lumi;
    ofstream eventList_wjets_lead;
    ofstream eventList_wjets_subLead;
   
    int o_run_lead;
    int o_run_subLead;
    int o_lumi_lead;
    int o_lumi_subLead;
    long o_event_lead;
    long o_event_subLead;
    double o_weight_lead;
    double o_weight_subLead;
    int o_id_iso_lead;
    int o_id_iso_subLead;
    double o_pt_lead;
    double o_pt_subLead;
    double o_pt_jet_lead;
    double o_pt_jet_subLead;
    int o_njets_lead;
    int o_njets_subLead;
    double o_maxPt_lead;
    double o_maxPt_subLead;

    //MVAEvaluator *kNNEval; 
    ifstream sync_eventList;
    std::vector<long> runs,lumis,events;
    
    long current_run;
    long current_lumi;
    SSummedVar< Int_t > m_allEvents;
	
	// output variables in ntuple
	
	Float_t out_pt;

   // Macro adding the functions for dictionary generation
   ClassDef( WHfake, 0 );

}; // class WHfake

#endif // WHfake_H

