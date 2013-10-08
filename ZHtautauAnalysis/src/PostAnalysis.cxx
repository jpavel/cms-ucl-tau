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
	h_FR_svMass                      	 = Book(TH1D("h_FR_svMass","Invariant mass of tau pair;m_{#tau#tau}[GeV]",300,0.0,300.0));
	h_FRt_svMass                      	 = Book(TH1D("h_FRt_svMass","Invariant mass of tau pair;m_{#tau#tau}[GeV]",300,0.0,300.0));
	
	
	// old histograms
	
	h_nPU_raw					 = 		  Book(TH1D("h_nPU_raw","raw PU distribution",50,0,50),"AnalysisHistos");
	
	SVTree = new TTree();
	MainTree = new TTree();
	
	in_FRt2 = new std::vector<Bool_t>;
	in_FRt = new std::vector<Bool_t>;
	
	in_FR_svMass = new std::vector<Float_t>;
	in_FR_svMass_unc = new std::vector<Float_t>;
	in_FR_type = new std::vector<Int_t>;
	in_FR_type2 = new std::vector<Int_t>;
	
	
	in_FR_px_H1 = new std::vector<Float_t>;
	in_FR_px_H2 = new std::vector<Float_t>;
	
	in_FR_py_H1 = new std::vector<Float_t>;
	in_FR_py_H2 = new std::vector<Float_t>;
	
	in_FR_pz_H1 = new std::vector<Float_t>;
	in_FR_pz_H2 = new std::vector<Float_t>;
	
	in_FR_E_H1 = new std::vector<Float_t>;
	in_FR_E_H2 = new std::vector<Float_t>;
	
	
	h_H_svMass_types.clear();
	
	TString type_name[8]={"Z(#mu#mu)H(#mu#tau)" ,"Z(#mu#mu)H(#mu e)" ,"Z(#mu#mu)H(e#tau)" ,"Z(#mu#mu)H(#tau#tau)" ,
							"Z(ee)H(#mu#tau)","Z(ee)H(#mu e)","Z(ee)H(e#tau)","Z(ee)H(#tau#tau)"};
	for(uint i = 1; i <= 8; i++)
	{
		std::stringstream s;
		s << "h_H_svMass_type_" << i;
		std::string name = s.str(); 
		std::stringstream ss;
		ss <<  type_name[i] << ";m_{H}[GeV]";
		std::string title = ss.str();
		
		TH1D* h_temp 						=  Book(TH1D(TString(name),TString(title),300,0.,300.));
		h_H_svMass_types.push_back(h_temp);	
	}
	
	h_H_visMass_types.clear();
	
	for(uint i = 1; i <= 8; i++)
	{
		std::stringstream s;
		s << "h_H_visMass_type_" << i;
		std::string name = s.str(); 
		std::stringstream ss;
		ss <<  type_name[i-1] << ";m_{H}[GeV]";
		std::string title = ss.str();
		
		TH1D* h_temp 						=  Book(TH1D(TString(name),TString(title),300,0.,300.));
		h_H_visMass_types.push_back(h_temp);	
	}
	
	h_H_FR_svMass_types.clear();
	
	for(uint i = 1; i <= 8; i++)
	{
		std::stringstream s;
		s << "h_H_FR_svMass_type_" << i;
		std::string name = s.str(); 
		std::stringstream ss;
		ss <<  type_name[i] << ";m_{H}[GeV]";
		std::string title = ss.str();
		
		TH1D* h_temp 						=  Book(TH1D(TString(name),TString(title),300,0.,300.));
		h_H_FR_svMass_types.push_back(h_temp);	
	}
	
	h_H_FR_visMass_types.clear();
	
	for(uint i = 1; i <= 8; i++)
	{
		std::stringstream s;
		s << "h_H_FR_visMass_type_" << i;
		std::string name = s.str(); 
		std::stringstream ss;
		ss <<  type_name[i-1] << ";m_{H}[GeV]";
		std::string title = ss.str();
		
		TH1D* h_temp 						=  Book(TH1D(TString(name),TString(title),300,0.,300.));
		h_H_FR_visMass_types.push_back(h_temp);	
	}
	
	h_H_FRt_svMass_types.clear();
	
	for(uint i = 1; i <= 8; i++)
	{
		std::stringstream s;
		s << "h_H_FRt_svMass_type_" << i;
		std::string name = s.str(); 
		std::stringstream ss;
		ss <<  type_name[i] << ";m_{H}[GeV]";
		std::string title = ss.str();
		
		TH1D* h_temp 						=  Book(TH1D(TString(name),TString(title),300,0.,300.));
		h_H_FRt_svMass_types.push_back(h_temp);	
	}
	
	h_H_FRt_visMass_types.clear();
	
	for(uint i = 1; i <= 8; i++)
	{
		std::stringstream s;
		s << "h_H_FRt_visMass_type_" << i;
		std::string name = s.str(); 
		std::stringstream ss;
		ss <<  type_name[i-1] << ";m_{H}[GeV]";
		std::string title = ss.str();
		
		TH1D* h_temp 						=  Book(TH1D(TString(name),TString(title),300,0.,300.));
		h_H_FRt_visMass_types.push_back(h_temp);	
	}
	
   return;

}

void PostAnalysis::EndInputData( const SInputData& ) throw( SError ) {
	
   return;

}

void PostAnalysis::BeginInputFile( const SInputData& ) throw( SError ) {
	
	SVTree = Retrieve<TTree>("svTree");
	MainTree = Retrieve<TTree>(InTreeName.c_str());
	std::cout << SVTree->GetEntries() << std::endl;
	
	h_nPU_raw_old = Retrieve<TH1D>("h_nPU_raw");
	std::cout << h_nPU_raw_old->Integral() << std::endl;
	for (int iBin =0; iBin <= (h_nPU_raw_old->GetNbinsX() +1); iBin++)
	{
		h_nPU_raw->SetBinContent(iBin,h_nPU_raw_old->GetBinContent(iBin));
		h_nPU_raw->SetBinError(iBin,h_nPU_raw_old->GetBinError(iBin));
		
	}
	
	//h_nPU_raw = (TH1D*)h_nPU_raw_old->Clone();
	std::cout << h_nPU_raw->Integral() << std::endl;
	
	ConnectVariable(InTreeName.c_str(),"o_run",in_run);
	ConnectVariable(InTreeName.c_str(),"o_lumi",in_lumi);
	ConnectVariable(InTreeName.c_str(),"o_event",in_event);
	ConnectVariable(InTreeName.c_str(),"o_pass",in_pass);
	ConnectVariable(InTreeName.c_str(),"o_FR_n", in_FR_n);
	ConnectVariable(InTreeName.c_str(),"o_FR",in_FR);
	ConnectVariable(InTreeName.c_str(),"o_FRt",    in_FRt );
	ConnectVariable(InTreeName.c_str(),"o_event_weight",    in_event_weight );
	ConnectVariable(InTreeName.c_str(),"o_type",    in_type );
	
	ConnectVariable(InTreeName.c_str(),"o_px_H1", in_px_H1);
	ConnectVariable(InTreeName.c_str(),"o_px_H2", in_px_H2);
	
	ConnectVariable(InTreeName.c_str(),"o_py_H1", in_py_H1);
	ConnectVariable(InTreeName.c_str(),"o_py_H2", in_py_H2);
	
	ConnectVariable(InTreeName.c_str(),"o_pz_H1", in_pz_H1);
	ConnectVariable(InTreeName.c_str(),"o_pz_H2", in_pz_H2);
	
	ConnectVariable(InTreeName.c_str(),"o_E_H1", in_E_H1);
	ConnectVariable(InTreeName.c_str(),"o_E_H2", in_E_H2);


	ConnectVariable(InTreeName.c_str(),"o_FR_type",   in_FR_type );
	
	ConnectVariable(InTreeName.c_str(),"o_FR_px_H1", in_FR_px_H1);
	ConnectVariable(InTreeName.c_str(),"o_FR_px_H2", in_FR_px_H2);
	
	ConnectVariable(InTreeName.c_str(),"o_FR_py_H1", in_FR_py_H1);
	ConnectVariable(InTreeName.c_str(),"o_FR_py_H2", in_FR_py_H2);
	
	ConnectVariable(InTreeName.c_str(),"o_FR_pz_H1", in_FR_pz_H1);
	ConnectVariable(InTreeName.c_str(),"o_FR_pz_H2", in_FR_pz_H2);
	
	ConnectVariable(InTreeName.c_str(),"o_FR_E_H1", in_FR_E_H1);
	ConnectVariable(InTreeName.c_str(),"o_FR_E_H2", in_FR_E_H2);

	
	SVTree->SetBranchAddress( "o_svMass",    &in_svMass );
	SVTree->SetBranchAddress( "o_svMass_unc",    &in_svMass_unc );
	
	SVTree->SetBranchAddress( "o_run",    &in_run2 );
	SVTree->SetBranchAddress( "o_lumi",    &in_lumi2 );
	SVTree->SetBranchAddress( "o_event",    &in_event2 );
	SVTree->SetBranchAddress( "o_pass",    &in_pass2 );
	SVTree->SetBranchAddress( "o_FR_n", &in_FR_n2 );
	SVTree->SetBranchAddress( "o_FR",    &in_FR2 );
	SVTree->SetBranchAddress( "o_FRt",    &in_FRt2 );
	SVTree->SetBranchAddress( "o_event_weight",    &in_event_weight2 );
	SVTree->SetBranchAddress( "o_type",    &in_type2 );
	SVTree->SetBranchAddress( "o_FR_type",    &in_FR_type2 );
	SVTree->SetBranchAddress( "o_FR_svMass",    &in_FR_svMass );
	SVTree->SetBranchAddress( "o_FR_svMass_unc",    &in_FR_svMass_unc ); 
	
	//ConnectVariable(InTreeName.c_str(),"o_svMass",in_svMass);
	//~ ConnectVariable(InTreeName.c_str(),"o_event_weight",in_event_weight);
	
	
	

   return;

}

double PostAnalysis::PairMass(double px1, double py1, double pz1, double E1,
double px2, double py2, double pz2, double E2){
	TLorentzVector H_1,H_2,H_sum;
    H_1.SetPxPyPzE(px1,py1,pz1,E1);
    H_2.SetPxPyPzE(px2,py2,pz2,E2);
    H_sum = H_1 + H_2;
	return H_sum.M();
}

void PostAnalysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
	
    //m_logger << DEBUG << "(" << in_pass << ") Now executing event " << in_event << " in a run " << in_run << SLogger::endmsg;
	if(in_pass || in_FR){
		 SVTree->GetEntry(m_allEvents);
		 double visMass = PairMass(in_px_H1,in_py_H1,in_pz_H1,in_E_H1,in_px_H2,in_py_H2,in_pz_H2,in_E_H2);
		if(in_pass) h_H_visMass_types[in_type-1]->Fill(visMass,in_event_weight);
		if(in_FR){
			for(int iFR=0; iFR< in_FR_n; iFR++)
			{
				if(in_FR_type->at(iFR) == 0) continue;
				double in_FR_visMass=PairMass(in_FR_px_H1->at(iFR),in_FR_py_H1->at(iFR),
											  in_FR_pz_H1->at(iFR),in_FR_E_H1->at(iFR),
											  in_FR_px_H2->at(iFR),in_FR_py_H2->at(iFR),
											  in_FR_pz_H2->at(iFR),in_FR_E_H2->at(iFR));
				h_H_FR_visMass_types[in_FR_type->at(iFR)-1]->Fill(in_FR_visMass,in_event_weight2);
				if(in_FRt->at(iFR)) h_H_FRt_visMass_types[in_FR_type->at(iFR)-1]->Fill(in_FR_visMass,in_event_weight2);
			}
		}
		
		 if( in_pass2 || in_FR2){
			m_logger << DEBUG << " Now executing event " << in_event << "/" << in_event2 << " in a run " << in_run << "/" << in_run2 << " :" 
			<< in_pass << "/" << in_pass2 << "/" << in_FR2 << "/" << in_FR << " : " << in_event_weight << "/" << in_event_weight2 
			<< " MASS:" << in_svMass << SLogger::endmsg;
		
			
			if(in_pass2){
				 h_H_svMass_types[in_type2-1]->Fill(in_svMass,in_event_weight2);
				 Hist("h_svMass")->Fill(in_svMass);
			}
			if(in_FR2){
				for(int iFR=0; iFR< in_FR_n2; iFR++)
				{
					if(in_FR_type2->at(iFR) == 0) continue;
					h_H_FR_svMass_types[in_FR_type2->at(iFR)-1]->Fill(in_FR_svMass->at(iFR),in_event_weight2);
					Hist("h_FR_svMass")->Fill(in_FR_svMass->at(iFR));
					if(in_FRt2->at(iFR)){
						 h_H_FRt_svMass_types[in_FR_type2->at(iFR)-1]->Fill(in_FR_svMass->at(iFR),in_event_weight2);
						 Hist("h_FRt_svMass")->Fill(in_FR_svMass->at(iFR));
					 }
				}
			}
			
				
			 
		 }
		 
		 ++m_allEvents;
	}
	
	//if(!in_pass) return;
	//m_logger << INFO << m_allEvents << ": Now executing event "<< SLogger::endmsg;
//	" << in_event << " in a run " << in_run << SLogger::endmsg;
	//m_logger << INFO << "The mass is " << in_svMass << SLogger::endmsg;
	//if(in_pass)  
	//
		

   return;

}

