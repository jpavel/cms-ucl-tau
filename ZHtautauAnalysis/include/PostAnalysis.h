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
#include <TLorentzVector.h>


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
   double PairMass(double px1, double py1, double pz1, double E1,
double px2, double py2, double pz2, double E2);


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
	Int_t in_FR_n;
	std::vector<Bool_t>* in_FRt;
	std::vector<Int_t>* in_FR_type;
	
	Int_t in_type;
	Float_t in_event_weight;
	
	Float_t in_px_H1;
	Float_t in_px_H2;
	
	Float_t in_py_H1;
	Float_t in_py_H2;
	
	Float_t in_pz_H1;
	Float_t in_pz_H2;
	
	Float_t in_E_H1;
	Float_t in_E_H2;


	
	Float_t in_svMass;
	Float_t in_svMass_unc;
	

	Int_t in_run2;
	Int_t in_lumi2;
	Int_t in_event2;
	Bool_t in_pass2;
	
	Int_t in_type2;
	Float_t in_event_weight2;
	
	Bool_t in_FR2;
	Int_t in_FR_n2;
	std::vector<Bool_t>* in_FRt2;
	std::vector<Int_t>* in_FR_type2;
	std::vector<Float_t>* in_FR_svMass;
	std::vector<Float_t>* in_FR_svMass_unc;
	
	std::vector<Float_t>* in_FR_px_H1;
	std::vector<Float_t>* in_FR_px_H2;

	std::vector<Float_t>* in_FR_py_H1;
	std::vector<Float_t>* in_FR_py_H2;

	std::vector<Float_t>* in_FR_pz_H1;
	std::vector<Float_t>* in_FR_pz_H2;

	std::vector<Float_t>* in_FR_E_H1;
	std::vector<Float_t>* in_FR_E_H2;

	
	
	TTree* SVTree;
	TTree* MainTree;
	
	// histograms
	
	TH1* h_svMass;
	TH1* h_FR_svMass;
	TH1* h_FRt_svMass;
	
	TH1* h_visMass;
	TH1* h_FR_visMass;
	TH1* h_FRt_visMass;
	
	TH1D* h_nPU_raw;
    TH1D* h_nPU_raw_old;
                
	
	
	std::vector<TH1*>  h_H_svMass_types;
    std::vector<TH1*>  h_H_visMass_types;
    std::vector<TH1*>  h_H_FR_svMass_types;
    std::vector<TH1*>  h_H_FR_visMass_types;
    std::vector<TH1*>  h_H_FRt_svMass_types;
    std::vector<TH1*>  h_H_FRt_visMass_types;
     

	//bookeeping
	SSummedVar< Int_t > m_allEvents;

   // Macro adding the functions for dictionary generation
   ClassDef( PostAnalysis, 0 );

}; // class PostAnalysis

#endif // PostAnalysis_H

