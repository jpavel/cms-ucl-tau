// Dear emacs, this is -*- c++ -*-
// $Id: CycleCreators.py 344 2012-12-13 13:10:53Z krasznaa $
#ifndef PostAnalysis_H
#define PostAnalysis_H

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

#include <TTree.h>

/**
 *   @short Put short description of class here
 *
 *          Put a longer description over here...
 *
 *  @author Put your name here
 * @version $Revision: 344 $
 */
class PostAnalysis : public SCycleBase {

public:
   /// Default constructor
   PostAnalysis();
   /// Default destructor
   ~PostAnalysis();

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

private:
   //
   // Put all your private variables here
   //
   
   // properties
   
   std::string InTreeName;
	
   
   // input variables
   
	Int_t in_run;
	Int_t in_lumi;
	Int_t in_event;
	Bool_t in_pass;
	Bool_t in_FR;
	
	Float_t in_svMass;
	Float_t in_event_weight;


	Int_t in_run2;
	Int_t in_lumi2;
	Int_t in_event2;
	Bool_t in_pass2;
	Bool_t in_FR2;
	
	
	
	TTree* SVTree;
	TTree* MainTree;
	
	// histograms
	
	TH1* h_svMass;

	//bookeeping
	SSummedVar< Int_t > m_allEvents;

   // Macro adding the functions for dictionary generation
   ClassDef( PostAnalysis, 0 );

}; // class PostAnalysis

#endif // PostAnalysis_H

