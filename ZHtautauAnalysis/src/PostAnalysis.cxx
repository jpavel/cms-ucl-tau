// $Id: CycleCreators.py 344 2012-12-13 13:10:53Z krasznaa $

// Local include(s):
#include "../include/PostAnalysis.h"
#include <iomanip>

ClassImp( PostAnalysis );

PostAnalysis::PostAnalysis()
   : SCycleBase(), m_allEvents( "allEvents", this ) 
   {

   SetLogName( GetName() );
   DeclareProperty("InTreeName",InTreeName);
   DeclareProperty("UseAbdollahTree",UseAbdollahTree);
   DeclareProperty("syncFileName",syncFileName);
	
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
	
	h_visMass                      		 = Book(TH1D("h_visMass","Invariant mass of tau pair;m_{#tau#tau}[GeV]",300,0.0,300.0));
	h_FR_visMass                      	 = Book(TH1D("h_FR_visMass","Invariant mass of tau pair;m_{#tau#tau}[GeV]",300,0.0,300.0));
	h_FRt_visMass                      	 = Book(TH1D("h_FRt_visMass","Invariant mass of tau pair;m_{#tau#tau}[GeV]",300,0.0,300.0));
	
	h_svCorrelation						 = Book(TH2D("h_svCorrelation","Mass correlation;ULB mass [GeV];UCL mass [GeV]",300,0.,300.,300,0.,300.));
    h_svDifference						 = Book(TH1D("h_svDifference","Mass difference;#Delta M[GeV]",100,-50.,50.));
    h_svDifferenceSig					 = Book(TH1D("h_svDifferenceSig","Mass difference;#Delta M/#sigma M",120,-3.0,3.0));
    h_svDifferenceRel					 = Book(TH1D("h_svDifferenceRel","Mass relative difference;#Delta M/M",160,-2.0,2.0));
	h_svDifferenceAssym					 = Book(TH1D("h_svDifferenceAssym","Mass assymetry; 2#DeltaM/(M_{UCL}+M_{ULB})",160,-2.0,2.0));
    
	h_svDifference_MET					 = Book(TH2D("h_svDifference_MET","Mass difference;#Delta MET; #Delta M[GeV]",100,-0.003,0.003,100,-20,20));
	h_svDifference_METphi				 = Book(TH2D("h_svDifference_METphi","Mass difference;#Delta METphi; #Delta M[GeV]",100,-1.0,0.1,100,-20,20));
	
	h_pxDiff						 = Book(TH1D("h_pxDiff","P_{x} difference;rel. #Delta P_{x}",200,-0.1,0.1));
	h_pyDiff						 = Book(TH1D("h_pyDiff","P_{y} difference;rel. #Delta P_{y}",200,-0.1,0.1));
	h_pzDiff						 = Book(TH1D("h_pzDiff","P_{z} difference;rel. #Delta P_{z}",200,-0.1,0.1));
	h_MDiff						 = Book(TH1D("h_MDiff","M difference;rel. #Delta M",200,-0.1,0.1));
	
	h_pxDiff2						 = Book(TH1D("h_pxDiff2","P_{x} difference;rel. #Delta P_{x}",200,-0.1,0.1));
	h_pyDiff2						 = Book(TH1D("h_pyDiff2","P_{y} difference;rel. #Delta P_{y}",200,-0.1,0.1));
	h_pzDiff2						 = Book(TH1D("h_pzDiff2","P_{z} difference;rel. #Delta P_{z}",200,-0.1,0.1));
	h_MDiff2						 = Book(TH1D("h_MDiff2","M difference;rel. #Delta M",200,-0.1,0.1));
	
	h_METDiff						 = Book(TH1D("h_METDiff","MET difference;rel. #Delta MET",200,-0.003,0.003));
	h_METPhiDiff						 = Book(TH1D("h_METPhiDiff","METPhi difference;rel. #Delta METPhi",200,-1.0,0.1));
	h_covMET11Diff						 = Book(TH1D("h_covMET11Diff","covMET11 difference;rel. #Delta covMET11",200,-0.1,0.1));
	h_covMET12Diff						 = Book(TH1D("h_covMET12Diff","covMET12 difference;rel. #Delta covMET12",200,-0.1,0.1));
	h_covMET21Diff						 = Book(TH1D("h_covMET21Diff","covMET21 difference;rel. #Delta covMET21",200,-0.1,0.1));
	h_covMET22Diff						 = Book(TH1D("h_covMET22Diff","covMET22 difference;rel. #Delta covMET22",200,-0.1,0.1));
	
	h_elMass						= Book(TH1D("h_elMass","Difference between input electron and PDG mass;#Delta M [GeV]",100,-0.1,0.1));
	h_muMass						= Book(TH1D("h_muMass","Difference between input muon and PDG mass;#Delta M [GeV]",100,-0.1,0.1));
	
	// old histograms
	
	h_nPU_raw					 = 		  Book(TH1D("h_nPU_raw","raw PU distribution",50,0,50),"AnalysisHistos");
	
	//h_svCorrelation =
	
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
	
	in_FR_M_H1 = new std::vector<Float_t>;
	in_FR_M_H2 = new std::vector<Float_t>;
	
	
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
	
	
	if(UseAbdollahTree){
		syncFile = TFile::Open(syncFileName.c_str());
		if(!syncFile) {
			std::cerr << "Error: file " << syncFileName << " could not be opened." << std::endl; 
			return;
		}else std::cout << "File " << syncFileName << " succesfully opened!" << std::endl;
		syncTree = (TTree*)syncFile->Get("Mass_tree");
		
		std::cout << " sync tree has " << syncTree->GetEntries() << " entries" << std::endl;
		
		syncTree->SetBranchAddress( "Run_",    &sync_run );
		syncTree->SetBranchAddress( "Event_",    &sync_event );
		syncTree->SetBranchAddress( "Lumi_",    &sync_lumi );
		
		syncTree->SetBranchAddress( "Chanel_", &sync_Channel );
		syncTree->SetBranchAddress( "HMass_Markov", &sync_HMass_Markov );
		syncTree->SetBranchAddress( "l3Px_", &sync_l3Px );
		syncTree->SetBranchAddress( "l3Py_", &sync_l3Py );
		syncTree->SetBranchAddress( "l3Pz_", &sync_l3Pz );
		syncTree->SetBranchAddress( "l3M_", &sync_l3M );
		syncTree->SetBranchAddress( "l4Px_", &sync_l4Px );
		syncTree->SetBranchAddress( "l4Py_", &sync_l4Py );
		syncTree->SetBranchAddress( "l4Pz_", &sync_l4Pz );
		syncTree->SetBranchAddress( "l4M_", &sync_l4M );
		
		syncTree->SetBranchAddress( "SVmass", &sync_SVmass );
		syncTree->SetBranchAddress( "met_", &sync_met );
		syncTree->SetBranchAddress( "metPhi_", &sync_metPhi );
		syncTree->SetBranchAddress( "covMet11_", &sync_covMet11 );
		syncTree->SetBranchAddress( "covMet12_", &sync_covMet12 );
		syncTree->SetBranchAddress( "covMet21_", &sync_covMet21 );
		syncTree->SetBranchAddress( "covMet22_", &sync_covMet22 );
		
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
	
	ConnectVariable(InTreeName.c_str(),"o_M_H1", in_M_H1);
	ConnectVariable(InTreeName.c_str(),"o_M_H2", in_M_H2);
	
	ConnectVariable(InTreeName.c_str(),"o_MET_x",  in_MET_x);
	ConnectVariable(InTreeName.c_str(),"o_MET_y",  in_MET_y);
	ConnectVariable(InTreeName.c_str(),"o_covMET_00",  in_covMET_00);
	ConnectVariable(InTreeName.c_str(),"o_covMET_01",  in_covMET_01);
	ConnectVariable(InTreeName.c_str(),"o_covMET_10",  in_covMET_10);
	ConnectVariable(InTreeName.c_str(),"o_covMET_11",  in_covMET_11);



	ConnectVariable(InTreeName.c_str(),"o_FR_type",   in_FR_type );
	
	ConnectVariable(InTreeName.c_str(),"o_FR_px_H1", in_FR_px_H1);
	ConnectVariable(InTreeName.c_str(),"o_FR_px_H2", in_FR_px_H2);
	
	ConnectVariable(InTreeName.c_str(),"o_FR_py_H1", in_FR_py_H1);
	ConnectVariable(InTreeName.c_str(),"o_FR_py_H2", in_FR_py_H2);
	
	ConnectVariable(InTreeName.c_str(),"o_FR_pz_H1", in_FR_pz_H1);
	ConnectVariable(InTreeName.c_str(),"o_FR_pz_H2", in_FR_pz_H2);
	
	ConnectVariable(InTreeName.c_str(),"o_FR_M_H1", in_FR_M_H1);
	ConnectVariable(InTreeName.c_str(),"o_FR_M_H2", in_FR_M_H2);

	
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

double PostAnalysis::PairMassM(double px1, double py1, double pz1, double M1,
double px2, double py2, double pz2, double M2){
	TLorentzVector H_1,H_2,H_sum;
    H_1.SetXYZM(px1,py1,pz1,M1);
    H_2.SetXYZM(px2,py2,pz2,M2);
    H_sum = H_1 + H_2;
	return H_sum.M();
}

void PostAnalysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
	
    //m_logger << DEBUG << "(" << in_pass << ") Now executing event " << in_event << " in a run " << in_run << SLogger::endmsg;
	if(in_pass || in_FR){
		 SVTree->GetEntry(m_allEvents);
		 double visMass = PairMassM(in_px_H1,in_py_H1,in_pz_H1,in_M_H1,in_px_H2,in_py_H2,in_pz_H2,in_M_H2);
		if(in_pass){
			 h_H_visMass_types[in_type-1]->Fill(visMass,in_event_weight);
			 Hist("h_visMass")->Fill(visMass,in_event_weight);
		 }
		if(in_FR){
			for(int iFR=0; iFR< in_FR_n; iFR++)
			{
				if(in_FR_type->at(iFR) == 0) continue;
				double in_FR_visMass=PairMassM(in_FR_px_H1->at(iFR),in_FR_py_H1->at(iFR),
											  in_FR_pz_H1->at(iFR),in_FR_M_H1->at(iFR),
											  in_FR_px_H2->at(iFR),in_FR_py_H2->at(iFR),
											  in_FR_pz_H2->at(iFR),in_FR_M_H2->at(iFR));
				h_H_FR_visMass_types[in_FR_type->at(iFR)-1]->Fill(in_FR_visMass,in_event_weight);
				Hist("h_FR_visMass")->Fill(in_FR_visMass,in_event_weight);
					
				if(in_FRt->at(iFR)){
					h_H_FRt_visMass_types[in_FR_type->at(iFR)-1]->Fill(in_FR_visMass,in_event_weight);
					Hist("h_FRt_visMass")->Fill(in_FR_visMass,in_event_weight);
				}
			}
		}
		
		 if( in_pass2 || in_FR2){
			m_logger << DEBUG << " Now executing event " << in_event << "/" << in_event2 << " in a run " << in_run << "/" << in_run2 << " :" 
			<< in_pass << "/" << in_pass2 << "/" << in_FR2 << "/" << in_FR << " : " << in_event_weight << "/" << in_event_weight2 
			<< " MASS:" << in_svMass << SLogger::endmsg;
		
			
			if(in_pass2){
				 h_H_svMass_types[in_type2-1]->Fill(in_svMass,in_event_weight2);
				 Hist("h_svMass")->Fill(in_svMass,in_event_weight2);
				 if(in_type2==7){
					 std::cout << in_run2 << " " << in_event2 << " " << in_svMass << " " 
					 << in_px_H1 << " " << in_py_H1 << " " << in_pz_H1 << " " << in_M_H1 
					 << " " << in_px_H2 << " " << in_py_H2 << " " << in_pz_H2 << " " << in_M_H2 
					 << " " << in_MET_x << " " << in_MET_y << " " 
					 << in_covMET_00 << " " << in_covMET_01 << " " << in_covMET_10 << " " << in_covMET_11
					 << std::endl;
				 }
				 if(UseAbdollahTree){
				 bool foundEv = false;
					 for(uint iEv=0; iEv < syncTree->GetEntries() && !foundEv; iEv++)
					 {
						syncTree->GetEntry(iEv);
						if(sync_run==in_run && sync_event==in_event){ 
						 foundEv=true;
						}
					 }
				if(foundEv){
					double Svdiff=sync_SVmass-in_svMass;
					if(fabs(Svdiff/in_svMass_unc)>0.5){ 
						std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(10) <<Svdiff/in_svMass_unc << ":" << in_run2 << " " << in_event2 << " " << in_svMass << " " 
				 << in_px_H1 << " " << in_py_H1 << " " << in_pz_H1 << " " << in_M_H1 
				 << " " << in_px_H2 << " " << in_py_H2 << " " << in_pz_H2 << " " << in_M_H2 
				 << " " << in_MET_x << " " << in_MET_y << " " 
				 << in_covMET_00 << " " << in_covMET_01 << " " << in_covMET_10 << " " << in_covMET_11
				 << std::endl;
						std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(10) <<
							"Abdollah   "  << in_type2 << " " << sync_SVmass << " " 
						 << sync_l3Px << " " << sync_l3Py << " " << sync_l3Pz << " " << sync_l3M 
						 << " " << sync_l4Px << " " << sync_l4Py << " " << sync_l4Pz << " " << sync_l4M
						 << " " << sync_met << " " << sync_metPhi << " " 
						 << sync_covMet11 << " " << sync_covMet21 << " " << sync_covMet12 << " " << sync_covMet22
						 << std::endl;
					 }
						double pxDiff,pyDiff,pzDiff,MDiff;
						double pxDiff2,pyDiff2,pzDiff2,MDiff2;
					if(in_type2!=2){
						pxDiff = ((double)sync_l3Px - (double)in_px_H1)/(double)in_px_H1;
						pyDiff = ((double)sync_l3Py - (double)in_py_H1)/(double)in_py_H1;
						pzDiff = ((double)sync_l3Pz - (double)in_pz_H1)/(double)in_pz_H1;
						MDiff = ((double)sync_l3M - (double)in_M_H1)/(double)in_M_H1;
						
						pxDiff2 = ((double)sync_l4Px - (double)in_px_H2)/(double)in_px_H2;
						pyDiff2 = ((double)sync_l4Py - (double)in_py_H2)/(double)in_py_H2;
						pzDiff2 = ((double)sync_l4Pz - (double)in_pz_H2)/(double)in_pz_H2;
						MDiff2 = ((double)sync_l4M - (double)in_M_H2)/(double)in_M_H2;
					}else{
						pxDiff = ((double)sync_l4Px - (double)in_px_H1)/(double)in_px_H1;
						pyDiff = ((double)sync_l4Py - (double)in_py_H1)/(double)in_py_H1;
						pzDiff = ((double)sync_l4Pz - (double)in_pz_H1)/(double)in_pz_H1;
						MDiff = ((double)sync_l4M - (double)in_M_H1)/(double)in_M_H1;
						
						pxDiff2 = ((double)sync_l3Px - (double)in_px_H2)/(double)in_px_H2;
						pyDiff2 = ((double)sync_l3Py - (double)in_py_H2)/(double)in_py_H2;
						pzDiff2 = ((double)sync_l3Pz - (double)in_pz_H2)/(double)in_pz_H2;
						MDiff2 = ((double)sync_l3M - (double)in_M_H2)/(double)in_M_H2;
					}
					double met=sqrt((double)in_MET_x*(double)in_MET_x+(double)in_MET_y*(double)in_MET_y);
					double metPhi = acos((double)in_MET_x/met);
					if(in_MET_y < 0) metPhi=-metPhi; 	
					double metDiffABS = (double)sync_met - met;
					double metDiff=		metDiffABS/(double)met;
					double metPhiDiffABS = (double)sync_metPhi - metPhi;
					double metPhiDiff = metPhiDiffABS/(double)metPhi;					
					double cov11Diff = ((double)sync_covMet11 - (double)in_covMET_00)/(double)in_covMET_00;
					double cov12Diff = ((double)sync_covMet12 - (double)in_covMET_01)/(double)in_covMET_01;
					double cov21Diff = ((double)sync_covMet21 - (double)in_covMET_10)/(double)in_covMET_10;
					double cov22Diff = ((double)sync_covMet22 - (double)in_covMET_11)/(double)in_covMET_11;
					
					if(fabs(Svdiff/in_svMass_unc)>0.5) std::cout << pxDiff << " " << pyDiff << " " << pzDiff << " " << MDiff
					<< " " << pxDiff2 << " " << pyDiff2 << " " << pzDiff2 << " " << MDiff2
					<< " " << metDiff << " " << metPhiDiff << " " << metPhiDiffABS << " "
					<< cov11Diff << " " << cov21Diff << " " << cov12Diff << " " << cov22Diff << std::endl;
					            
				    Hist("h_pxDiff")->Fill(pxDiff);
					Hist("h_pyDiff")->Fill(pyDiff);
					Hist("h_pzDiff")->Fill(pzDiff);
					Hist("h_MDiff")->Fill(MDiff);
					
					Hist("h_pxDiff2")->Fill(pxDiff2);
					Hist("h_pyDiff2")->Fill(pyDiff2);
					Hist("h_pzDiff2")->Fill(pzDiff2);
					Hist("h_MDiff2")->Fill(MDiff2);
					
					Hist("h_METDiff")->Fill(metDiff);
					Hist("h_METPhiDiff")->Fill(metPhiDiff);
					Hist("h_covMET11Diff")->Fill(cov11Diff);
					Hist("h_covMET12Diff")->Fill(cov21Diff);
					Hist("h_covMET21Diff")->Fill(cov12Diff);
					Hist("h_covMET22Diff")->Fill(cov22Diff);
					
					if(in_type2==2 || in_type2==3 || in_type2==6 || in_type2==7){ 
						double ElMassDifference = double(in_M_H1) - 0.511e-3;
						Hist("h_elMass")->Fill(ElMassDifference);
					}
					
					if(in_type2==1 || in_type2==5){ 
						double MuMassDifference = double(in_M_H1) - 105.66e-3;
						Hist("h_muMass")->Fill(MuMassDifference);
					}
					
					if(in_type2==2 || in_type2==6){ 
						double MuMassDifference = double(in_M_H2) - 105.66e-3;
						Hist("h_muMass")->Fill(MuMassDifference);
					}
					
					Hist("h_svCorrelation")->Fill(sync_SVmass,in_svMass);
					Hist("h_svDifference")->Fill(Svdiff);
					std::cout << in_svMass_unc << std::endl;
					Hist("h_svDifferenceSig")->Fill(Svdiff/in_svMass_unc);
					Hist("h_svDifferenceRel")->Fill(Svdiff/in_svMass);
					Hist("h_svDifferenceAssym")->Fill(2*Svdiff/(sync_SVmass+in_svMass));
					
					Hist("h_svDifference_MET")->Fill(metDiffABS,Svdiff);
					Hist("h_svDifference_METphi")->Fill(metPhiDiffABS,Svdiff);
					
				}
				}
				 
			}
			if(in_FR2){
				for(int iFR=0; iFR< in_FR_n2; iFR++)
				{
					if(in_FR_type2->at(iFR) == 0) continue;
					h_H_FR_svMass_types[in_FR_type2->at(iFR)-1]->Fill(in_FR_svMass->at(iFR),in_event_weight2);
					Hist("h_FR_svMass")->Fill(in_FR_svMass->at(iFR),in_event_weight2);
					if(in_FRt2->at(iFR)){
						 h_H_FRt_svMass_types[in_FR_type2->at(iFR)-1]->Fill(in_FR_svMass->at(iFR),in_event_weight2);
						 Hist("h_FRt_svMass")->Fill(in_FR_svMass->at(iFR),in_event_weight2);
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

