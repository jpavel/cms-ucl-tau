// $Id: CycleCreators.py 344 2012-12-13 13:10:53Z krasznaa $

// Local include(s):
#include "../include/PostAnalysis.h"

ClassImp( PostAnalysis );

PostAnalysis::PostAnalysis()
   : SCycleBase(), m_allEvents( "allEvents", this ) 
   {

   SetLogName( GetName() );
   DeclareProperty("InTreeName",InTreeName);
	
}

PostAnalysis::~PostAnalysis() {

}

void PostAnalysis::BeginCycle() throw( SError ) {

   return;

}

void PostAnalysis::EndCycle() throw( SError ) {

   std::cout << "Post Analysis finished." << std::endl;
   return;

}

void PostAnalysis::BeginInputData( const SInputData& ) throw( SError ) {
	
	// histogram booking
	
	h_svMass                      		 = Book(TH1D("h_svMass","Invariant mass of tau pair;m_{#tau#tau}[GeV]",300,0.0,300.0));

   return;

}

void PostAnalysis::EndInputData( const SInputData& ) throw( SError ) {

   return;

}

void PostAnalysis::BeginInputFile( const SInputData& ) throw( SError ) {
	//~ ConnectVariable(InTreeName.c_str(),"o_run",in_run);
	//~ ConnectVariable(InTreeName.c_str(),"o_lumi",in_lumi);
	//~ ConnectVariable(InTreeName.c_str(),"o_event",in_event);
	//~ ConnectVariable(InTreeName.c_str(),"o_pass",in_pass);
	ConnectVariable(InTreeName.c_str(),"o_svMass",in_svMass);
	//~ ConnectVariable(InTreeName.c_str(),"o_event_weight",in_event_weight);
	
	
	

   return;

}

void PostAnalysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
	++m_allEvents;
	
    //m_logger << DEBUG << "(" << in_pass << ") Now executing event " << in_event << " in a run " << in_run << SLogger::endmsg;
	//if(in_pass) m_logger << DEBUG << " Now executing event " << in_event << " in a run " << in_run << SLogger::endmsg;
	//if(!in_pass) return;
	m_logger << INFO << m_allEvents << ": Now executing event "<< SLogger::endmsg;
//	" << in_event << " in a run " << in_run << SLogger::endmsg;
	m_logger << INFO << "The mass is " << in_svMass << SLogger::endmsg;
	Hist("h_svMass")->Fill(in_svMass);
		

   return;

}

