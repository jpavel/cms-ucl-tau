// $Id: CycleCreators.py 173 2010-05-12 15:49:33Z krasznaa $

// Local include(s):
#include "../include/Analysis.h"
#include <iostream>

ClassImp( Analysis );

Analysis::Analysis()
   : SCycleBase() {

   SetLogName( GetName() );
   DeclareProperty("InTreeName",InTreeName);
   DeclareProperty("MyPtCut",Ptcut);
}

Analysis::~Analysis() {

}

void Analysis::BeginCycle() throw( SError ) {

   return;

}

void Analysis::EndCycle() throw( SError ) {

   return;

}

void Analysis::BeginInputData( const SInputData& ) throw( SError ) {
	
	h_el_n=Book(TH1D("el_n","el_n",50,0,50));
    h_el_cut=Book(TH1D("el_cit","el_cut",50,0,50));
    cutflow=Book(TH1D("cutflow","cutflow",1,0,1));

   DeclareVariable(out_pt,"el_pt");

   return;

}

void Analysis::EndInputData( const SInputData& ) throw( SError ) {

   return;

}

void Analysis::BeginInputFile( const SInputData& ) throw( SError ) {
	//ConnectVariable(InTreeName.c_str(),"el_n",el_n);
	ConnectVariable(InTreeName.c_str(),"myevent",m);

   return;

}

void Analysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {

	m_logger << DEBUG << " Now executing event " << m->eventNumber << " in a run " << m->runNumber << SLogger::endmsg;

 //~ h_el_n->Fill(el_n);
 //~ cutflow->Fill("before",el_n);
  //~ 
 //~ for(int i=0;i<el_n; i++)
   //~ if(el_pt->at(i)>Ptcut)
     //~ out_pt.push_back(el_pt->at(i));
//~ 
 //~ h_el_cut->Fill(out_pt.size());
 //~ cutflow->Fill("after",out_pt.size());
   return;

}

