// Dear emacs, this is -*- c++ -*-
// $Id: CycleCreators.py 173 2010-05-12 15:49:33Z krasznaa $
#ifndef Filter_H
#define Filter_H

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

// my includes
#include "myevent.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"

/**
 *   @short Put short description of class here
 *
 *          Put a longer description over here...
 *
 *  @author Put your name here
 * @version $Revision: 173 $
 */
class Filter : public SCycleBase {

public:
   /// Default constructor
   Filter();
   /// Default destructor
   ~Filter();

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
   
   bool Trg_MC_12(myevent* m);
   double deltaR(double eta1, double phi1, double eta2, double phi2);
   double deltaR(myobject o1, myobject o2);

private:
   //
   // Put all your private variables here
   //
   
   // variables
	
	myevent *m;
	myevent out;
	TFile* outFile;
	TTree* outTree;
	
	
	// properties
	
	std::string InTreeName;
	
	std::string doubEle;
	std::string doubEle2;
	
    std::string doubMu;
    std::string doubMu2;
    std::string doubMu3;
    
    bool is2011;
    bool is2012_52;
    bool is2012_53;
    bool useTruePileUp;
    bool vetoMuonTrigger;
    bool vetoElectronTrigger;
    
    
    double N_ALL;
    double N_ELMU;
    
    double cut_mu_pt;
    double cut_mu_eta;    
    double cut_el_pt;
    double cut_el_eta;
    double cut_tau_pt;
    double cut_tau_eta;
    
    double cut_dR;

   // Macro adding the functions for dictionary generation
   ClassDef( Filter, 0 );

}; // class Filter

#endif // Filter_H

