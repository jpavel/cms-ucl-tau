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
	
	SVTree = new TTree();
	MainTree = new TTree();
	
   return;

}

void PostAnalysis::EndInputData( const SInputData& ) throw( SError ) {

   return;

}

void PostAnalysis::BeginInputFile( const SInputData& ) throw( SError ) {
	
	SVTree = Retrieve<TTree>("svTree");
	MainTree = Retrieve<TTree>(InTreeName.c_str());
	std::cout << SVTree->GetEntries() << std::endl;

	ConnectVariable(InTreeName.c_str(),"o_run",in_run);
	ConnectVariable(InTreeName.c_str(),"o_lumi",in_lumi);
	ConnectVariable(InTreeName.c_str(),"o_event",in_event);
	ConnectVariable(InTreeName.c_str(),"o_pass",in_pass);
	ConnectVariable(InTreeName.c_str(),"o_FR",in_FR);
	
	
	SVTree->SetBranchAddress( "o_run",    &in_run2 );
	SVTree->SetBranchAddress( "o_lumi",    &in_lumi2 );
	SVTree->SetBranchAddress( "o_event",    &in_event2 );
	SVTree->SetBranchAddress( "o_pass",    &in_pass2 );
	SVTree->SetBranchAddress( "o_FR",    &in_FR2 );
	
	
	
	//ConnectVariable(InTreeName.c_str(),"o_svMass",in_svMass);
	//~ ConnectVariable(InTreeName.c_str(),"o_event_weight",in_event_weight);
	
	
	

   return;

}

void PostAnalysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
	
    //m_logger << DEBUG << "(" << in_pass << ") Now executing event " << in_event << " in a run " << in_run << SLogger::endmsg;
	if(in_pass || in_FR){
		 SVTree->GetEntry(m_allEvents);
		 
		 m_logger << INFO << " Now executing event " << in_event << "/" << in_event2 << " in a run " << in_run << "/" << in_run2 << " :" 
		 << in_pass2 << "/" << in_FR2 << SLogger::endmsg;
		 
		 ++m_allEvents;
	}
	
	//if(!in_pass) return;
	//m_logger << INFO << m_allEvents << ": Now executing event "<< SLogger::endmsg;
//	" << in_event << " in a run " << in_run << SLogger::endmsg;
	//m_logger << INFO << "The mass is " << in_svMass << SLogger::endmsg;
	//if(in_pass)  
	//Hist("h_svMass")->Fill(in_svMass);
		

   return;

}

