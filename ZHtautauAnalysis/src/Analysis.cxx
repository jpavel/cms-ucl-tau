// $Id: CycleCreators.py 173 2010-05-12 15:49:33Z krasznaa $

// Local include(s):
#include "../include/Analysis.h"

#include "Corrector_new.h"

ClassImp( Analysis );

Analysis::Analysis()
	: SCycleBase(), m_allEvents( "allEvents", this )
	 {

		SetLogName( GetName() );
		DeclareProperty("InTreeName",InTreeName);
		DeclareProperty("maxDeltaR",maxDeltaR);
		DeclareProperty("BestMassForZ",BestMassForZ);
		DeclareProperty("dZvertex", dZvertex);
		DeclareProperty("bTagValue",bTagValue);
		
		

		DeclareProperty("ElectronTriggerName", doubEle);
		DeclareProperty("ElectronTriggerName2", doubEle2);

		DeclareProperty("MuonTriggerName1", doubMu);
		DeclareProperty("MuonTriggerName2", doubMu2);
		DeclareProperty("MuonTriggerName3", doubMu3);

		
		
		DeclareProperty("isSimulation",isSimulation);
		DeclareProperty("is2011",is2011);
		DeclareProperty("useObservedPU",useObservedPU);
		
		DeclareProperty("is2012_53",is2012_53);
	
		DeclareProperty("vetoMuonTrigger",vetoMuonTrigger);
		DeclareProperty("vetoElectronTrigger", vetoElectronTrigger);
		
		DeclareProperty("Cut_tau_base_Pt",Cut_tau_base_Pt);
		DeclareProperty("Cut_tautau_Pt_1",Cut_tautau_Pt_1);
		DeclareProperty("Cut_tautau_Pt_2",Cut_tautau_Pt_2);
		DeclareProperty("Cut_leptau_Pt",Cut_leptau_Pt);
		
		
		DeclareProperty("Cut_tautau_sumPt",Cut_tautau_sumPt);
		DeclareProperty("Cut_mutau_sumPt",Cut_mutau_sumPt);
		DeclareProperty("Cut_etau_sumPt",Cut_etau_sumPt);
		DeclareProperty("Cut_leplep_sumPt",Cut_leplep_sumPt);
		DeclareProperty("Cut_tautau_sumPt_FR",Cut_tautau_sumPt_FR);
		DeclareProperty("Cut_mutau_sumPt_FR",Cut_mutau_sumPt_FR);
		DeclareProperty("Cut_etau_sumPt_FR",Cut_etau_sumPt_FR);
		DeclareProperty("Cut_leplep_sumPt_FR",Cut_leplep_sumPt_FR);
		DeclareProperty("UseSumPtCut",UseSumPtCut);
		
		DeclareProperty("relIso_MT",relIso_MT);
		DeclareProperty("relIso_ET",relIso_ET);;
		DeclareProperty("relIso_EM",relIso_EM);
	
	
		DeclareProperty("IgnoreSF",IgnoreSF);
		DeclareProperty("IgnorePUW",IgnorePUW);
		DeclareProperty("printoutEvents",printoutEvents);
		DeclareProperty("examineEvent",examineEvent);
		DeclareProperty("removeTauOverlap",removeTauOverlap);
		
		DeclareProperty("UseLongEvent",UseLongEvent);
		DeclareProperty("OverM",OverM);
		DeclareProperty("BelowM",BelowM);
		
		DeclareProperty("DoubleE",DoubleE);
		DeclareProperty("DoubleM",DoubleM);
		
		//shape
		
		DeclareProperty("tau_shape_iso_cut",tau_shape_iso_cut);
		DeclareProperty("lep_shape_iso_cut",lep_shape_iso_cut);
		
		//syst
		DeclareProperty("ShiftTauES_up",ShiftTauES_up); 
		DeclareProperty("ShiftTauES_down",ShiftTauES_down); 
		DeclareProperty("SystUncert_ES",SystUncert_ES); 
		DeclareProperty("onlyTrigger",onlyTrigger);
		DeclareProperty("onlyIDIso",onlyIDIso);
		DeclareProperty("SFShiftUp_Mu",SFShiftUp_Mu);
		DeclareProperty("SFShiftDown_Mu",SFShiftDown_Mu);
		DeclareProperty("SFShiftUp_Ele",SFShiftUp_Ele);
		DeclareProperty("SFShiftDown_Ele",SFShiftDown_Ele);
		
		//ntuple out
		
		DeclareProperty("doNtuple", doNtuple);
		DeclareProperty("FillPDFInfo",FillPDFInfo);
		DeclareProperty("FillSVmassInfo",FillSVmassInfo);
		DeclareProperty("FillZZgenInfo",FillZZgenInfo);
		DeclareProperty("FillGenMET",FillGenMET);
		
		// for FR calculation
		
		DeclareProperty("IgnoreLTforFR_TT",IgnoreLTforFR_TT);
		DeclareProperty("IgnoreLTforFR_LT",IgnoreLTforFR_LT);
		DeclareProperty("IgnoreLTforFR_LL",IgnoreLTforFR_LL);
		DeclareProperty("reverseFR",reverseFR);
		
		DeclareProperty("syncFileName",syncFileName);
		DeclareProperty("doSync",doSync);
		DeclareProperty("doSyncFR",doSyncFR);
		

	}

Analysis::~Analysis() {

}

void Analysis::BeginCycle() throw( SError ) {

	return;

}

void Analysis::EndCycle() throw( SError ) {

	std::cout << "(0) Job exit code is 0" << std::endl;
	return;

}

int Analysis::EventTypeConv(int e_type_in)
{
	switch(e_type_in)
	{
		case 1: return 4;
		case 2: return 3;
		case 3: return 1;
		case 4: return 2;
		case 5: return 8;
		case 6: return 5;
		case 7: return 7;
		case 8: return 6;
		default: return e_type_in;	
	}
}

int Analysis::EventTypeConvAbdollah(int e_type_in)
{
	switch(e_type_in)
	{
		case 1: return 3;
		case 2: return 4;
		case 3: return 2;
		case 4: return 1;
		case 5: return 6;
		case 6: return 8;
		case 7: return 7;
		case 8: return 5;
		default: return e_type_in;	
	}
}

std::string Analysis::EventTypeName(int e_type_in)
{
	switch(e_type_in)
	{
		case 1: return "MMMT";
		case 2: return "MMME";
		case 3: return "MMET";
		case 4: return "MMTT";
		case 5: return "EEMT";
		case 6: return "EEEM";
		case 7: return "EEET";
		case 8: return "EETT";
		default: return "";	
	}
}

void Analysis::BeginInputData( const SInputData& ) throw( SError ) {
	
	// sync tree
	if(doSync){
		syncFile = TFile::Open(syncFileName.c_str());
		if(!syncFile) {
			std::cerr << "Error: file " << syncFileName << " could not be opened." << std::endl; 
			return;
		}else std::cout << "File " << syncFileName << " succesfully opened!" << std::endl;
		syncTree = (TTree*)syncFile->Get("BG_Tree");
		
		std::cout << " sync tree has " << syncTree->GetEntries() << " entries" << std::endl;
		
		syncTree->SetBranchAddress( "Run_",    &sync_run );
		syncTree->SetBranchAddress( "Event_",    &sync_event );
		syncTree->SetBranchAddress( "Lumi_",    &sync_lumi );
		
		syncTree->SetBranchAddress( "Channel_", &sync_Channel );
        syncTree->SetBranchAddress( "subChannel_", &sync_subChannel );
		syncTree->SetBranchAddress( "HMass_", &sync_HMass );
		syncTree->SetBranchAddress( "l3Pt_", &sync_l3Pt );
		syncTree->SetBranchAddress( "l3Eta_", &sync_l3Eta );
		syncTree->SetBranchAddress( "l3_CloseJetPt_", &sync_l3_CloseJetPt );
		syncTree->SetBranchAddress( "l3_CloseJetEta_", &sync_l3_CloseJetEta );
		syncTree->SetBranchAddress( "l4Pt_", &sync_l4Pt );
		syncTree->SetBranchAddress( "l4Eta_", &sync_l4Eta );
		syncTree->SetBranchAddress( "l4_CloseJetPt_", &sync_l4_CloseJetPt );
		syncTree->SetBranchAddress( "l4_CloseJetEta_", &sync_l4_CloseJetEta );
		
		sync_run_vec.clear();
		sync_lumi_vec.clear();
		sync_event_vec.clear();
		
		syncTreeMap.clear();
		int n_same=0;
		bool smaller = false;
		bool equal = false;
		treemap::iterator it=syncTreeMap.begin();
		for(uint iEv = 0; iEv < syncTree->GetEntries(); iEv++)
		{
			if(equal) n_same++;
			RunLumiEvent prevRLE(sync_run, sync_lumi, sync_event);
			syncTree->GetEvent(iEv);
			RunLumiEvent thisRLE(sync_run, sync_lumi, sync_event);
			if(prevRLE < thisRLE) smaller=true;
			else smaller=false;
			if(prevRLE==thisRLE) equal=true;
			else equal=false;
			if(!equal){
				std::cout << "write " << prevRLE.run <<":" << prevRLE.lumi <<":" << prevRLE.event << " " << n_same << " " << iEv - n_same -1 << std::endl;
				it=syncTreeMap.find(prevRLE);
				treeinfo myinfo = std::make_pair(iEv-n_same-1,n_same);
				if(it==syncTreeMap.end())
				{
					syncTreeMap.insert(std::make_pair(prevRLE,myinfo));
				}else{
					m_logger << ERROR << " WTF ??? !!! " << SLogger::endmsg;
				}
				n_same=0;
			}
			std::cout << iEv << ": " << sync_run << ":" << sync_lumi << ":" << sync_event << " "  << smaller << equal << std::endl;
			sync_run_vec.push_back(sync_run);
			sync_lumi_vec.push_back(sync_lumi);
			sync_event_vec.push_back(sync_event);	
			thisRLE = RunLumiEvent(sync_run, sync_lumi, sync_event);
			
		}	
	}else{ // doSync == false
		syncFile=NULL;
		syncTree=NULL;
	}
	
	// ntuple definition
	//DeclareVariable(out_pt,"el_pt");
	if(doNtuple){
	DeclareVariable(o_run,"o_run");
	DeclareVariable(o_lumi,"o_lumi");
	DeclareVariable(o_event,"o_event");
	DeclareVariable(o_pass, "o_pass");
	DeclareVariable(o_FR, "o_FR");
	DeclareVariable(o_FRt, "o_FRt");
	DeclareVariable(o_event_weight,"o_event_weight");
	DeclareVariable(o_type,"o_type");
	DeclareVariable(o_px_Z1,"o_px_Z1");
	DeclareVariable(o_px_Z2,"o_px_Z2");
	DeclareVariable(o_px_H1,"o_px_H1");
	DeclareVariable(o_px_H2,"o_px_H2");
	DeclareVariable(o_py_Z1,"o_py_Z1");
	DeclareVariable(o_py_Z2,"o_py_Z2");
	DeclareVariable(o_py_H1,"o_py_H1");
	DeclareVariable(o_py_H2,"o_py_H2");
	DeclareVariable(o_pz_Z1,"o_pz_Z1");
	DeclareVariable(o_pz_Z2,"o_pz_Z2");
	DeclareVariable(o_pz_H1,"o_pz_H1");
	DeclareVariable(o_pz_H2,"o_pz_H2");
	DeclareVariable(o_M_Z1,"o_M_Z1");
	DeclareVariable(o_M_Z2,"o_M_Z2");
	DeclareVariable(o_M_H1,"o_M_H1");
	DeclareVariable(o_M_H2,"o_M_H2");
	DeclareVariable(o_pdg_Z1,"o_pdg_Z1");
	DeclareVariable(o_pdg_Z2,"o_pdg_Z2");
	DeclareVariable(o_pdg_H1,"o_pdg_H1");
	DeclareVariable(o_pdg_H2,"o_pdg_H2");
	
	//FR
	DeclareVariable( o_FR_n, "o_FR_n");
	DeclareVariable(o_FR_type,"o_FR_type");
	DeclareVariable(o_FR_px_H1,"o_FR_px_H1");
	DeclareVariable(o_FR_px_H2,"o_FR_px_H2");
	DeclareVariable(o_FR_py_H1,"o_FR_py_H1");
	DeclareVariable(o_FR_py_H2,"o_FR_py_H2");
	DeclareVariable(o_FR_pz_H1,"o_FR_pz_H1");
	DeclareVariable(o_FR_pz_H2,"o_FR_pz_H2");
	DeclareVariable(o_FR_M_H1,"o_FR_M_H1");
	DeclareVariable(o_FR_M_H2,"o_FR_M_H2");
	DeclareVariable(o_FR_pdg_H1,"o_FR_pdg_H1");
	DeclareVariable(o_FR_pdg_H2,"o_FR_pdg_H2");
	
	
	
	
	DeclareVariable(o_MET_x,"o_MET_x");
	DeclareVariable(o_MET_y,"o_MET_y");
	
	DeclareVariable(o_covMET_00,"o_covMET_00");
	DeclareVariable(o_covMET_01,"o_covMET_01"); 
	DeclareVariable(o_covMET_10,"o_covMET_10");
	DeclareVariable(o_covMET_11,"o_covMET_11");
	//pdf info
	DeclareVariable(o_pdf_alphaQCD,"o_alphaQCD");
	DeclareVariable(o_pdf_alphaQED,"o_alphaQED");
	DeclareVariable(o_pdf_qScale,"o_qScale");
	DeclareVariable(o_pdf_weight,"o_weight");
	DeclareVariable(o_pdf_scalePDF,"o_scalePDF");
	DeclareVariable(o_pdf_binningValue0,"o_binningValue0");
	DeclareVariable(o_pdf_id_1,"o_id_1");
	DeclareVariable(o_pdf_id_2,"o_id_2");
	DeclareVariable(o_pdf_x_1,"o_x_1");
	DeclareVariable(o_pdf_x_2,"o_x_2");
	DeclareVariable(o_pdf_xPDF_1,"o_xPDF_1");
	DeclareVariable(o_pdf_xPDF_2,"o_xPDF_2");
	DeclareVariable(o_pdf_hasPDF,"o_hasPDF"); 
	DeclareVariable(o_pdf_hasBinningValues,"o_hasBinningValues"); 
	DeclareVariable(o_pdf_signalProcessID,"o_signalProcessID"); 
	DeclareVariable(o_pdf_binningValueSize,"o_binningValueSize"); 
	
	DeclareVariable(o_gen_pt_Z1,"o_gen_pt_Z1");
	DeclareVariable(o_gen_pt_Z2,"o_gen_pt_Z2");
	DeclareVariable(o_gen_eta_Z1,"o_gen_eta_Z1");
	DeclareVariable(o_gen_eta_Z2,"o_gen_eta_Z2");
	DeclareVariable(o_gen_phi_Z1,"o_gen_phi_Z1");
	DeclareVariable(o_gen_phi_Z2,"o_gen_phi_Z2");
	DeclareVariable(o_gen_mass_Z1,"o_gen_mass_Z1");
	DeclareVariable(o_gen_mass_Z2,"o_gen_mass_Z2");
	
	DeclareVariable(o_gen_MET_x,"o_gen_MET_x");
	DeclareVariable(o_gen_MET_y,"o_gen_MET_y");
	DeclareVariable(o_gen_MET,"o_gen_MET");

}


	

	h_cut_flow                      		 = Book(TH1D("h_cut_flow","Cut Flow",11,-0.5,10.5));
	h_cut_flow_weight               		 = Book(TH1D("h_cut_flow_weight","Cut Flow Weighted",11,-0.5,10.5));

	
	

	
	
	h_event_type        	      		  	 = Book(TH1D("h_event_type","Event Type",8,0.5,8.5));
	h_event_type_raw        			 = Book(TH1D("h_event_type_raw","Event Type (no weights)",8,0.5,8.5));

	
	//Z->mumu    
	h_mu1Z_pt           				 = Book(TH1D("h_mu1Z_pt","muon1_Pt",300,0,300));
	h_mu2Z_pt          		        	 = Book(TH1D("h_mu2Z_pt","muon2_Pt",300,0,300));
	h_Zmass_mumu        			       	 = Book(TH1D("h_Zmass_mumu","Zmumu_mass",60,60,120));
	h_Zpt_mumu          		 		 = Book(TH1D("h_Zpt_mumu","Zmumu_pt",300,0,300));
	//Z->ee    
	h_ele1Z_pt          				 = Book(TH1D("h_ele1Z_pt","ele1_Pt",300,0,300));
	h_ele2Z_pt         		        	 = Book(TH1D("h_ele2Z_pt","ele2_Pt",300,0,300));
	h_Zmass_ee          				 = Book(TH1D("h_Zmass_ee","Zee_mass",60,60,120));
	h_Zpt_ee            				 = Book(TH1D("h_Zpt_ee","Zee_pt",300,0,300));
	//Z
	

	h_Z_eta						 = Book(TH1D("h_Z_eta","H #eta; #eta",100,-3.0,3.0));
	h_Z_phi						 = Book(TH1D("h_Z_phi","H #phi; #phi",64,-3.2,3.2));

	h_Z_lep1_eta					 = Book(TH1D("h_Z_lep1_eta","H #eta; #eta",100,-3.0,3.0));
	h_Z_lep1_phi					 = Book(TH1D("h_Z_lep1_phi","H #phi; #phi",64,-3.2,3.2));	

	h_Z_lep2_eta					 = Book(TH1D("h_Z_lep2_eta","H #eta; #eta",100,-3.0,3.0));
	h_Z_lep2_phi					 = Book(TH1D("h_Z_lep2_phi","H #phi; #phi",64,-3.2,3.2));

	
	// lepton histograms
	h_n_goodEl					 = Book(TH1D("h_n_goodEl","Number of good electrons; good electrons",10,-0.5,9.5));
	h_n_goodMu					 = Book(TH1D("h_n_goodMu","Number of good muons; good muons",10,-0.5,9.5));

	h_el_relIso					 = Book(TH1D("h_el_relIso","Relative electron isolation; relIso(el)",100,0.0,1.0));
	h_mu_relIso					 = Book(TH1D("h_mu_relIso","Relative muon isolation; relIso(mu)",100,0.0,1.0));

	h_n_goodEl_Hcand				 = Book(TH1D("h_n_goodEl_Hcand","Number of good electrons; good electrons",10,-0.5,9.5));
	h_n_goodMu_Hcand			         = Book(TH1D("h_n_goodMu_Hcand","Number of good muons; good muons",10,-0.5,9.5));
	h_n_goodTau_Hcand				 = Book(TH1D("h_n_goodTau_Hcand","Number of good taus; good taus",10,-0.5,9.5));

	h_PU_weight					 = Book(TH1D("h_PU_weight","PU weights distribution",100,0,5));
	h_total_weight					 = Book(TH1D("h_total_weight","Weights distribution",100,0,5));
	h_nPU_raw					 = Book(TH1D("h_nPU_raw","raw PU distribution",50,0,50));
	h_nPU_reweight					 = Book(TH1D("h_nPU_reweight","reweighted PU distribution",50,0,50));

	h_PF_MET					 = Book(TH1D("h_PF_MET","PF MET distribution;PF MET[GeV]",100,0,200));
	h_PF_MET_selected				 = Book(TH1D("h_PF_MET_selected","PF MET distribution;PF MET[GeV]",100,0,200));

	h_PF_MET_nPU					 = Book(TProfile("h_PF_MET_nPU", "PF MET vs number of PU interactions; nPU; PF MET[GeV]",60,0,60));
	h_PF_MET_nPU_selected				 = Book(TProfile("h_PF_MET_nPU_selected", "PF MET vs number of PU interactions; nPU; PF MET[GeV]",60,0,60));
	
	

        h_nPU_Info                      		 = Book(TH1D("h_nPU_Info","PU info distribution",100,0,100));
        h_nPU_InfoTrue                  		 = Book(TH1D("h_nPU_InfoTrue","PU info True distribution",100,0,100));
        h_nPU_Bunch0                    		 = Book(TH1D("h_nPU_Bunch0","PU info Bunch0 distribution",100,0,100));
        h_nPU_Info_W                    		 = Book(TH1D("h_nPU_Info_W","PU info distribution reweighted",100,0,100));
        h_nPU_InfoTrue_W               			 = Book(TH1D("h_nPU_InfoTrue_W","PU info True distribution reweighted",100,0,100));
        h_nPU_Bunch0_W                 			 = Book(TH1D("h_nPU_Bunch0_W","PU info Bunch0 distribution reweighted",100,0,100));
        
        
        // FR plots
        
        h_FR_tau_denom 	= Book(TH1D("h_FR_tau_denom","Tau FR denominator in |#eta| < 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_tauLT_denom 	= Book(TH1D("h_FR_tauLT_denom","Tau LT FR denominator in |#eta| < 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_mu_denom 	= Book(TH1D("h_FR_mu_denom","Mu FR denominator in |#eta| < 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_el_denom 	= Book(TH1D("h_FR_el_denom","El FR denominator in |#eta| < 1.4; jet p_{T}[GeV]",300,0,300));
        
        h_FR_tau_num 	= Book(TH1D("h_FR_tau_num","Tau FR numerator in |#eta| < 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_tauLT_num 	= Book(TH1D("h_FR_tauLT_num","Tau LT FR numerator in |#eta| < 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_mu_num		= Book(TH1D("h_FR_mu_num","Mu FR numerator in |#eta| < 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_el_num		= Book(TH1D("h_FR_el_num","El FR numerator in |#eta| < 1.4; jet p_{T}[GeV]",300,0,300));

		h_FR_tau_denom_EC 	= Book(TH1D("h_FR_tau_denom_EC","Tau FR denominator in |#eta| > 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_tauLT_denom_EC 	= Book(TH1D("h_FR_tauLT_denom_EC","Tau LT FR denominator in |#eta| > 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_mu_denom_EC 	= Book(TH1D("h_FR_mu_denom_EC","Mu FR denominator in |#eta| > 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_el_denom_EC 	= Book(TH1D("h_FR_el_denom_EC","El FR denominator in |#eta| > 1.4; jet p_{T}[GeV]",300,0,300));
        
        h_FR_tau_num_EC 	= Book(TH1D("h_FR_tau_num_EC","Tau FR numerator in |#eta| > 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_tauLT_num_EC 	= Book(TH1D("h_FR_tauLT_num_EC","Tau LT FR numerator in |#eta| > 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_mu_num_EC		= Book(TH1D("h_FR_mu_num_EC","Mu FR numerator in |#eta| > 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_el_num_EC		= Book(TH1D("h_FR_el_num_EC","El FR numerator in |#eta| > 1.4; jet p_{T}[GeV]",300,0,300));
      
		
		h_FR_muT_denom 	= Book(TH1D("h_FR_muT_denom","Tight Mu FR denominator in |#eta| < 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_elT_denom 	= Book(TH1D("h_FR_elT_denom","Tight El FR denominator in |#eta| < 1.4; jet p_{T}[GeV]",300,0,300));
		h_FR_muT_denom_EC 	= Book(TH1D("h_FR_muT_denom_EC","Tight Mu FR denominator in |#eta| > 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_elT_denom_EC 	= Book(TH1D("h_FR_elT_denom_EC","Tight El FR denominator in |#eta| > 1.4; jet p_{T}[GeV]",300,0,300));
        
		h_FR_muT_num 	= Book(TH1D("h_FR_muT_num","Tight Mu FR numerator in |#eta| < 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_elT_num 	= Book(TH1D("h_FR_elT_num","Tight El FR numerator in |#eta| < 1.4; jet p_{T}[GeV]",300,0,300));
		h_FR_muT_num_EC 	= Book(TH1D("h_FR_muT_num_EC","Tight Mu FR numerator in |#eta| > 1.4; jet p_{T}[GeV]",300,0,300));
        h_FR_elT_num_EC 	= Book(TH1D("h_FR_elT_num_EC","Tight El FR numerator in |#eta| > 1.4; jet p_{T}[GeV]",300,0,300));
        
	
	h_Nvertex_NoCut = Book(TH1D("h_Nvertex_NoCut","Number of vertices - no cut", 50, -0.5,49.5));
	h_Nvertex_NoCut_W = Book(TH1D("h_Nvertex_NoCut_W","Number of vertices - no cut (PU weight)", 50, -0.5,49.5));
	h_Nvertex_AfterZ = Book(TH1D("h_Nvertex_AfterZ","Number of vertices - selected Z", 50, -0.5,49.5));
	h_Nvertex_AfterZ_W = Book(TH1D("h_Nvertex_AfterZ_W","Number of vertices - selected Z (PU weight)", 50, -0.5,49.5));
	h_Nvertex_AfterZH = Book(TH1D("h_Nvertex_AfterZH","Number of vertices - selected Z and H", 50, -0.5,49.5));
	h_Nvertex_AfterZH_W = Book(TH1D("h_Nvertex_AfterZH_W","Number of vertices - selected Z and H (PU weight)", 50, -0.5,49.5));

	

	h_cut_flow = Retrieve<TH1D>("h_cut_flow");
	h_cut_flow->GetXaxis()->SetBinLabel(1, "Initial Events");
	h_cut_flow->GetXaxis()->SetBinLabel(2, "trigger");
	h_cut_flow->GetXaxis()->SetBinLabel(3, "good vx");
	h_cut_flow->GetXaxis()->SetBinLabel(4, "Z cand");
	h_cut_flow->GetXaxis()->SetBinLabel(5, "Lepton veto");
	h_cut_flow->GetXaxis()->SetBinLabel(6, "Signal cand");
	h_cut_flow->GetXaxis()->SetBinLabel(7, "B-tag veto");
	h_cut_flow->GetXaxis()->SetBinLabel(8, "N/A");
	h_cut_flow->GetXaxis()->SetBinLabel(9, "N/A");
	h_cut_flow->GetXaxis()->SetBinLabel(10, "N/A");
	h_cut_flow->GetXaxis()->SetBinLabel(11, "N/A");

        h_cut_flow_weight = Retrieve<TH1D>("h_cut_flow_weight");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(1, "Initial Events");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(2, "trigger");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(3, "good vx");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(4, "Z cand");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(5, "Lepton veto");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(6, "Signal cand");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(7, "B-tag veto");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(8, "N/A");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(9, "N/A");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(10, "N/A");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(11, "N/A");


	h_event_type = Retrieve<TH1D>("h_event_type");
	h_event_type->GetXaxis()->SetBinLabel(1,"Z(#mu#mu)H(#mu#tau)");
	h_event_type->GetXaxis()->SetBinLabel(2,"Z(#mu#mu)H(#mu e)");
	h_event_type->GetXaxis()->SetBinLabel(3,"Z(#mu#mu)H(e#tau)");
	h_event_type->GetXaxis()->SetBinLabel(4,"Z(#mu#mu)H(#tau#tau)");
	h_event_type->GetXaxis()->SetBinLabel(5,"Z(ee)H(#mu#tau)");
	h_event_type->GetXaxis()->SetBinLabel(6,"Z(ee)H(#mu e)");
	h_event_type->GetXaxis()->SetBinLabel(7,"Z(ee)H(e#tau)");
	h_event_type->GetXaxis()->SetBinLabel(8,"Z(ee)H(#tau#tau)");
	
        h_event_type_raw = Retrieve<TH1D>("h_event_type_raw");
	h_event_type_raw->GetXaxis()->SetBinLabel(1,"Z(#mu#mu)H(#mu#tau)");
	h_event_type_raw->GetXaxis()->SetBinLabel(2,"Z(#mu#mu)H(#mu e)");
	h_event_type_raw->GetXaxis()->SetBinLabel(3,"Z(#mu#mu)H(e#tau)");
	h_event_type_raw->GetXaxis()->SetBinLabel(4,"Z(#mu#mu)H(#tau#tau)");
	h_event_type_raw->GetXaxis()->SetBinLabel(5,"Z(ee)H(#mu#tau)");
	h_event_type_raw->GetXaxis()->SetBinLabel(6,"Z(ee)H(#mu e)");
	h_event_type_raw->GetXaxis()->SetBinLabel(7,"Z(ee)H(e#tau)");
	h_event_type_raw->GetXaxis()->SetBinLabel(8,"Z(ee)H(#tau#tau)");

      


	h_PF_MET_nPU=Retrieve<TProfile>("h_PF_MET_nPU");
	h_PF_MET_nPU_selected=Retrieve<TProfile>("h_PF_MET_nPU_selected");

	
	
	
	h_H_mass_FR_types.clear();
	h_H_mass_signal_types.clear();
	h_H_mass_FRt_types.clear();
	h_H_mass_cat1_types.clear();
	h_H_mass_cat2_types.clear();
	
	
	h_signal_pt1_types.clear();
	h_signal_pt2_types.clear();
	h_signal_SumPt_types.clear();
        
	h_category0_pt_types.clear();
	h_category1_pt_types.clear();
	h_category2_pt_types.clear();
        
	for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
	{
		std::stringstream s,sig_1,sig_2,cat0,cat1,cat2,mass_sig,mass_cat0,mass_cat1,mass_cat2,sumPt,jet_cat0,jet_cat1,jet_cat2,
		jet_EE_cat0,jet_EB_cat0,jet_BE_cat0,jet_BB_cat0,
		jet_EC_cat1,jet_EC_cat2,jetRef_cat0,jetRef_cat1,jetRef_cat2;
		s << "h_H_mass_FR_type_" << i;
		mass_sig << "h_H_mass_signal_type_" << i;
		mass_cat0 << "h_H_mass_FRt_type_" << i;
		mass_cat1 << "h_H_mass_cat1_type_" << i;
		mass_cat2 << "h_H_mass_cat2_type_" << i;
		
		sig_1 << "h_signal_pt1_" << i;
		sig_2 << "h_signal_pt2_" << i;
		sumPt << "h_signal_SumPt_" << i;
		cat0 << "h_category0_pt_" << i;
		cat1 << "h_category1_pt_" << i;
		cat2 << "h_category2_pt_" << i;
		
		jet_cat0 << "h_jet_category0_jet_pt_" << i;
		jet_cat1 << "h_jet_category1_jet_pt_" << i;
		jet_cat2 << "h_jet_category2_jet_pt_" << i;
		
		jet_EE_cat0 << "h_jet_EE_category0_jet_EE_pt_" << i;
		jet_EB_cat0 << "h_jet_EB_category0_jet_EB_pt_" << i;
		jet_BE_cat0 << "h_jet_BE_category0_jet_BE_pt_" << i;
		jet_BB_cat0 << "h_jet_BB_category0_jet_BB_pt_" << i;
		
		jet_EC_cat1 << "h_jet_EC_category1_jet_EC_pt_" << i;
		jet_EC_cat2 << "h_jet_EC_category2_jet_EC_pt_" << i;
		
		
		jetRef_cat0 << "h_jetRef_category0_jetRef_pt_" << i;
		jetRef_cat1 << "h_jetRef_category1_jetRef_pt_" << i;
		jetRef_cat2 << "h_jetRef_category2_jetRef_pt_" << i;
		
		std::string name = s.str(); 
		std::string name_mass_sig = mass_sig.str(); 
		std::string name_mass_cat0 = mass_cat0.str(); 
		std::string name_mass_cat1 = mass_cat1.str(); 
		std::string name_mass_cat2 = mass_cat2.str(); 
		
		std::string name_sig_1 = sig_1.str(); 
		std::string name_sig_2 = sig_2.str(); 
		std::string name_SumPt = sumPt.str(); 
		std::string name_cat0 = cat0.str(); 
		std::string name_cat1 = cat1.str(); 
		std::string name_cat2 = cat2.str(); 
		std::string name_jet_cat0 = jet_cat0.str(); 
		std::string name_jet_cat1 = jet_cat1.str(); 
		std::string name_jet_cat2 = jet_cat2.str();
		
		std::string name_jet_EE_cat0 = jet_EE_cat0.str(); 
		std::string name_jet_EB_cat0 = jet_EB_cat0.str(); 
		std::string name_jet_BE_cat0 = jet_BE_cat0.str(); 
		std::string name_jet_BB_cat0 = jet_BB_cat0.str(); 
		
		std::string name_jet_EC_cat1 = jet_EC_cat1.str(); 
		std::string name_jet_EC_cat2 = jet_EC_cat2.str(); 
		
		std::string name_jetRef_cat0 = jetRef_cat0.str(); 
		std::string name_jetRef_cat1 = jetRef_cat1.str(); 
		std::string name_jetRef_cat2 = jetRef_cat2.str(); 
		
		std::stringstream ss,tit_sig_1,tit_sig_2,tit_cat0,tit_cat1,tit_cat2,tit_sumPt,tit_jet_cat0,tit_jet_cat1,tit_jet_cat2,
		tit_jet_EE_cat0,tit_jet_EB_cat0,tit_jet_BE_cat0,tit_jet_BB_cat0,
		tit_jet_EC_cat1,tit_jet_EC_cat2,
		tit_jetRef_cat0,tit_jetRef_cat1,tit_jetRef_cat2;
		ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";m_{H}[GeV]";
		
		tit_sig_1 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
		tit_sig_2 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
		tit_sumPt << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
		tit_cat0 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T1}[GeV];P_{T2}[GeV]";
		tit_cat1 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
		tit_cat2 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
		tit_jet_cat0 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T1}[GeV];P_{T2}[GeV]";
		tit_jet_cat1 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
		tit_jet_cat2 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
		tit_jet_EE_cat0 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T1}[GeV];P_{T2}[GeV]";
		tit_jet_EB_cat0 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T1}[GeV];P_{T2}[GeV]";
		tit_jet_BE_cat0 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T1}[GeV];P_{T2}[GeV]";
		tit_jet_BB_cat0 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T1}[GeV];P_{T2}[GeV]";
		tit_jet_EC_cat1 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
		tit_jet_EC_cat2 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
			tit_jetRef_cat0 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T1}[GeV];P_{T2}[GeV]";
		tit_jetRef_cat1 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
		tit_jetRef_cat2 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
	
			
		std::string title = ss.str();
		std::string title_sig_1 = tit_sig_1.str(); 
		std::string title_sig_2 = tit_sig_2.str(); 
		std::string title_SumPt = tit_sig_2.str(); 
		std::string title_cat0 = tit_cat0.str(); 
		std::string title_cat1 = tit_cat1.str(); 
		std::string title_cat2 = tit_cat2.str();
		std::string title_jet_cat0 = tit_jet_cat0.str(); 
		std::string title_jet_cat1 = tit_jet_cat1.str(); 
		std::string title_jet_cat2 = tit_jet_cat2.str();
		std::string title_jet_EE_cat0 = tit_jet_EE_cat0.str();
		std::string title_jet_EB_cat0 = tit_jet_EB_cat0.str();
		std::string title_jet_BE_cat0 = tit_jet_BE_cat0.str();
		std::string title_jet_BB_cat0 = tit_jet_BB_cat0.str();
		 
		std::string title_jet_EC_cat1 = tit_jet_EC_cat1.str(); 
		std::string title_jet_EC_cat2 = tit_jet_EC_cat2.str();
		std::string title_jetRef_cat0 = tit_jetRef_cat0.str(); 
		std::string title_jetRef_cat1 = tit_jetRef_cat1.str(); 
		std::string title_jetRef_cat2 = tit_jetRef_cat2.str();
		
		TH1D* h_temp 					=  Book(TH1D(TString(name),TString(title),300,0.,300.));
		TH1D* h_mass_sig_temp 				=  Book(TH1D(TString(name_mass_sig),TString(title),300,0.,300.));
		TH1D* h_mass_cat0_temp 				=  Book(TH1D(TString(name_mass_cat0),TString(title),300,0.,300.));
		TH1D* h_mass_cat1_temp 				=  Book(TH1D(TString(name_mass_cat1),TString(title),300,0.,300.));
		TH1D* h_mass_cat2_temp 				=  Book(TH1D(TString(name_mass_cat2),TString(title),300,0.,300.));
		
		TH1D* h_signal_temp_pt1				= Book(TH1D(TString(name_sig_1), TString(title_sig_1),100,0,100));
		TH1D* h_signal_temp_pt2				= Book(TH1D(TString(name_sig_2), TString(title_sig_2),100,0,100));
		TH1D* h_signal_temp_SumPt			= Book(TH1D(TString(name_SumPt), TString(title_SumPt),300,0,300));
	    
		TH2D* h_category0_temp_pt			= Book(TH2D(TString(name_cat0), TString(title_cat0),100,0,100,100,0,100));
		TH1D* h_category1_temp_pt			= Book(TH1D(TString(name_cat1), TString(title_cat1),100,0,100));
		TH1D* h_category2_temp_pt			= Book(TH1D(TString(name_cat2), TString(title_cat2),100,0,100));
		
		TH2D* h_category0_temp_jet_pt			= Book(TH2D(TString(name_jet_cat0), TString(title_jet_cat0),300,0,300,300,0,300));
		TH1D* h_category1_temp_jet_pt			= Book(TH1D(TString(name_jet_cat1), TString(title_jet_cat1),300,0,300));
		TH1D* h_category2_temp_jet_pt			= Book(TH1D(TString(name_jet_cat2), TString(title_jet_cat2),300,0,300));
		TH2D* h_category0_temp_jet_EE_pt			= Book(TH2D(TString(name_jet_EE_cat0), TString(title_jet_EE_cat0),300,0,300,300,0,300));
		TH2D* h_category0_temp_jet_BE_pt			= Book(TH2D(TString(name_jet_BE_cat0), TString(title_jet_BE_cat0),300,0,300,300,0,300));
		TH2D* h_category0_temp_jet_EB_pt			= Book(TH2D(TString(name_jet_EB_cat0), TString(title_jet_EB_cat0),300,0,300,300,0,300));
		TH2D* h_category0_temp_jet_BB_pt			= Book(TH2D(TString(name_jet_BB_cat0), TString(title_jet_BB_cat0),300,0,300,300,0,300));
		
		TH1D* h_category1_temp_jet_EC_pt			= Book(TH1D(TString(name_jet_EC_cat1), TString(title_jet_EC_cat1),300,0,300));
		TH1D* h_category2_temp_jet_EC_pt			= Book(TH1D(TString(name_jet_EC_cat2), TString(title_jet_EC_cat2),300,0,300));
		
		
		TH2D* h_category0_temp_jetRef_pt			= Book(TH2D(TString(name_jetRef_cat0), TString(title_jetRef_cat0),100,0,100,100,0,100));
		TH1D* h_category1_temp_jetRef_pt			= Book(TH1D(TString(name_jetRef_cat1), TString(title_jetRef_cat1),100,0,100));
		TH1D* h_category2_temp_jetRef_pt			= Book(TH1D(TString(name_jetRef_cat2), TString(title_jetRef_cat2),100,0,100));
		
		h_H_mass_FR_types.push_back(h_temp);
		h_H_mass_signal_types.push_back(h_mass_sig_temp);
		h_H_mass_FRt_types.push_back(h_mass_cat0_temp);
		h_H_mass_cat1_types.push_back(h_mass_cat1_temp);
		h_H_mass_cat2_types.push_back(h_mass_cat2_temp);
		
		h_signal_pt1_types.push_back(h_signal_temp_pt1);
		h_signal_pt2_types.push_back(h_signal_temp_pt2);
		h_signal_SumPt_types.push_back(h_signal_temp_SumPt);
        
		h_category0_pt_types.push_back(h_category0_temp_pt);
		h_category1_pt_types.push_back(h_category1_temp_pt);
		h_category2_pt_types.push_back(h_category2_temp_pt);
		
		h_category0_jet_pt_types.push_back(h_category0_temp_jet_pt);
		h_category1_jet_pt_types.push_back(h_category1_temp_jet_pt);
		h_category2_jet_pt_types.push_back(h_category2_temp_jet_pt);
		
		h_category0_jet_EE_pt_types.push_back(h_category0_temp_jet_EE_pt);
		h_category0_jet_EB_pt_types.push_back(h_category0_temp_jet_EB_pt);
		h_category0_jet_BE_pt_types.push_back(h_category0_temp_jet_BE_pt);
		h_category0_jet_BB_pt_types.push_back(h_category0_temp_jet_BB_pt);
		
		h_category1_jet_EC_pt_types.push_back(h_category1_temp_jet_EC_pt);
		h_category2_jet_EC_pt_types.push_back(h_category2_temp_jet_EC_pt);
    
		h_category0_jetRef_pt_types.push_back(h_category0_temp_jetRef_pt);
		h_category1_jetRef_pt_types.push_back(h_category1_temp_jetRef_pt);
		h_category2_jetRef_pt_types.push_back(h_category2_temp_jetRef_pt);
    
		
	}
	TString FRchannelName[6] ={"tauB TT","tauEC TT","tauB LT","tauEC LT","el FR","mu FR"};
	TString subChName[5] = {"cat0","cat1","cat2","sig","BGshape" };
	TString syncSummaryName[6] = {"only UCL","type UCL l1","only UCL l2","OK","only ULB","wrong order"};
	TString failReasons[6] = {"trigger","Vx","Z", "iso leptons", "no H", "b tag" };
	h_fail_shape_TT = Book(TH1D("h_fail_shape_TT","Reasons failing shape cuts",15,-0.5,14.5));
	h_fail_shape_TT=Retrieve<TH1D>("h_fail_shape_TT");
	TString failReasonsTT[15] = {"LeadPt","LeadElID","SubPt", "SS", "one pair", "SubEleID", "dR", "dZ","LT","lepVeto","shape","no2nd tau", "wrong pair", "BarrelFail1", "BarrelFail2" };
	
	h_fail_shape_MT = Book(TH1D("h_fail_shape_MT","Reasons failing shape cuts",16,-0.5,15.5));
	h_fail_shape_MT=Retrieve<TH1D>("h_fail_shape_MT");
	TString failReasonsMT[16] = {"SS", "tau pt", "one pair", "tauMuID", "tauEleID", "dR", "dZ","LT","lepVeto","shape","no2nd tau","elOverlap", "muOverlap","tau pt","no cat", "no cat0" };
	
	h_fail_shape_ET = Book(TH1D("h_fail_shape_ET","Reasons failing shape cuts",16,-0.5,15.5));
	h_fail_shape_ET=Retrieve<TH1D>("h_fail_shape_ET");
	TString failReasonsET[16] = {"lost hits", "SS", "tau pt", "one pair", "tauEleID", "dR", "dZ","LT","lepVeto","shape","no2nd tau","elOverlap", "muOverlap","tau pt","no cat", "no cat0" };
	
	h_fail_shape_EM = Book(TH1D("h_fail_shape_EM","Reasons failing shape cuts",8,-0.5,7.5));
	h_fail_shape_EM=Retrieve<TH1D>("h_fail_shape_EM");
	TString failReasonsEM[8] = {"lost hits", "SS", "dR", "dZ","LT","lepVeto","shape","no2nd tau" };
	
	for(uint jBin = 1; jBin <= (uint)h_fail_shape_TT->GetNbinsX(); jBin++)
		{
			h_fail_shape_TT->GetXaxis()->SetBinLabel(jBin,failReasonsTT[jBin-1]);
		}
		
	for(uint jBin = 1; jBin <= (uint)h_fail_shape_MT->GetNbinsX(); jBin++)
		{
			h_fail_shape_MT->GetXaxis()->SetBinLabel(jBin,failReasonsMT[jBin-1]);
		}
	
		for(uint jBin = 1; jBin <= (uint)h_fail_shape_ET->GetNbinsX(); jBin++)
		{
			h_fail_shape_ET->GetXaxis()->SetBinLabel(jBin,failReasonsET[jBin-1]);
		}
		
		for(uint jBin = 1; jBin <= (uint)h_fail_shape_EM->GetNbinsX(); jBin++)
		{
			h_fail_shape_EM->GetXaxis()->SetBinLabel(jBin,failReasonsEM[jBin-1]);
		}
	
	for(uint i = 0; i < 5; i++)
	{
		std::stringstream fail_reason_s_name;
		fail_reason_s_name << "h_fail_reason_reason sch_" << i;
		std::string fail_reason_name = fail_reason_s_name.str();
		
		std::stringstream fail_reason_s_title;
		fail_reason_s_title << subChName[i];
		std::string fail_reason_title = fail_reason_s_title.str();
		
		TH2D* h_fail_reason_temp 					=  Book(TH2D(TString(fail_reason_name),TString(fail_reason_title),6,-0.5,5.5,14,0.5,14.5));
		for(uint iBin = 1; iBin <= (uint)h_fail_reason_temp->GetNbinsY(); iBin++)
		{
			if(iBin <9) h_fail_reason_temp->GetYaxis()->SetBinLabel(iBin,h_event_type->GetXaxis()->GetBinLabel(iBin));
			else h_fail_reason_temp->GetYaxis()->SetBinLabel(iBin,FRchannelName[iBin-9]);
		}
		
		for(uint jBin = 1; jBin <= (uint)h_fail_reason_temp->GetNbinsX(); jBin++)
		{
			h_fail_reason_temp->GetXaxis()->SetBinLabel(jBin,failReasons[jBin-1]);
		}
		
		h_fail_reason.push_back(h_fail_reason_temp);
		
		
		std::stringstream sync_summary_s_name;
		sync_summary_s_name << "h_sync_summary_reason sch_" << i;
		std::string sync_summary_name = sync_summary_s_name.str();
		
		std::stringstream sync_summary_s_title;
		sync_summary_s_title << subChName[i];
		std::string sync_summary_title = sync_summary_s_title.str();
		
		TH2D* h_sync_summary_temp 					=  Book(TH2D(TString(sync_summary_name),TString(sync_summary_title),6,-0.5,5.5,14,0.5,14.5));
		for(uint iBin = 1; iBin <= (uint)h_sync_summary_temp->GetNbinsY(); iBin++)
		{
			if(iBin < 9) h_sync_summary_temp->GetYaxis()->SetBinLabel(iBin,h_event_type->GetXaxis()->GetBinLabel(iBin));
			else h_sync_summary_temp->GetYaxis()->SetBinLabel(iBin,FRchannelName[iBin-9]);
		}
		for(uint jBin = 1; jBin <= (uint)h_sync_summary_temp->GetNbinsX(); jBin++)
		{
			h_sync_summary_temp->GetXaxis()->SetBinLabel(jBin,syncSummaryName[jBin-1]);
		}
		h_sync_summary.push_back(h_sync_summary_temp);
		
	}


	// Lumi weights

	if(is2011) LumiWeights_ = new reweight::LumiReWeighting("Fall11_PU.root", "dataPileUpHistogram_True_2011.root","mcPU","pileup");
	else LumiWeights_ = new reweight::LumiReWeighting("Summer12_PU_53X.root", "dataPileUpHistogramABCD_True_2012.root","mcPU","pileup");

	if(printoutEvents){
		 log1.open("eventsAP.txt");
		 logFR.open("eventsFR.txt");
		 logS.open("events.txt");
		 log_events.open("eventlist.txt");
		 log_files.open("filelist.txt");
	 }
	 
	 
	
	//bookkeeping
	lumi.open("lumi.csv");
	current_run=current_lumi=-999;
	
	if(doSync){
		syncOutTree = new TTree("UCL_tree","UCL_tree");
		syncOutTree->Branch( "Run_",    &sync_o_run , "Run_/i");
		syncOutTree->Branch( "Event_",    &sync_o_event, "Event_/i" );
		syncOutTree->Branch( "Lumi_",    &sync_o_lumi, "Lumi/i" );
		
		syncOutTree->Branch( "Channel_", &sync_o_Channel, "Channel_/S" );
        syncOutTree->Branch( "subChannel_", &sync_o_subChannel, "Channel_/S" );
		syncOutTree->Branch( "HMass_", &sync_o_HMass, "HMass_/F" );
		syncOutTree->Branch( "l3Pt_", &sync_o_l3Pt, "l3Pt_/F" );
		syncOutTree->Branch( "l3Eta_", &sync_o_l3Eta, "l3Eta_/F" );
		syncOutTree->Branch( "l3_CloseJetPt_", &sync_o_l3_CloseJetPt, "l3_CloseJetPt_/F" );
		syncOutTree->Branch( "l3_CloseJetEta_", &sync_o_l3_CloseJetEta, "l3_CloseJetEta_/F" );
		syncOutTree->Branch( "l4Pt_", &sync_o_l4Pt, "l4Pt_/F" );
		syncOutTree->Branch( "l4Eta_", &sync_o_l4Eta, "l4Eta_/F" );
		syncOutTree->Branch( "l4_CloseJetPt_", &sync_o_l4_CloseJetPt, "l4_CloseJetPt_/F" );
		syncOutTree->Branch( "l4_CloseJetEta_", &sync_o_l4_CloseJetEta, "l4_CloseJetEta_/F" );
	}
	
	
	
	return;

}

void Analysis::EndInputData( const SInputData& ) throw( SError ) {

	std::cout << "Event type summary: " << std::endl;
	std::cout << "Z(mumu)H(mutau)   : " << h_event_type->GetBinContent(1) << 
	" (" << h_event_type_raw->GetBinContent(1) << ")"<< std::endl;
	std::cout << "Z(mumu)H(muE)     : " << h_event_type->GetBinContent(2) << 
	" (" << h_event_type_raw->GetBinContent(2) << ")"<< std::endl;
	std::cout << "Z(mumu)H(Etau)    : " << h_event_type->GetBinContent(3) << 
	" (" << h_event_type_raw->GetBinContent(3) << ")"<< std::endl;
	std::cout << "Z(mumu)H(tautau)  : " << h_event_type->GetBinContent(4) << 
	" (" << h_event_type_raw->GetBinContent(4) << ")"<< std::endl;
	std::cout << "Z(EE)H(mutau)     : " << h_event_type->GetBinContent(5) << 
	" (" << h_event_type_raw->GetBinContent(5) << ")"<< std::endl;
	std::cout << "Z(EE)H(muE)       : " << h_event_type->GetBinContent(6) << 
	" (" << h_event_type_raw->GetBinContent(6) << ")"<< std::endl;
	std::cout << "Z(EE)H(Etau)      : " << h_event_type->GetBinContent(7) << 
	" (" << h_event_type_raw->GetBinContent(7) << ")"<< std::endl;
	std::cout << "Z(EE)H(tautau)    : " << h_event_type->GetBinContent(8) << 
	" (" << h_event_type_raw->GetBinContent(8) << ")"<< std::endl;


	if(printoutEvents){ 
		log1.close();
		logFR.close();
		logS.close();
		log_events.close();
		log_files.close();
	}
	
	//sync
	if(doSync)
	{
		syncOut = new TFile("syncTree.root","RECREATE");
		syncOutTree->Write();
		syncOut->Close();
	}
	
	
	
	// bookkeeping
	lumi.close();
	ofstream log2;       
     log2.open("total.txt");
     log2 << *m_allEvents << std::endl;
     log2.close();
	
	
	return;

}

void Analysis::BeginInputFile( const SInputData& ) throw( SError ) {
	ConnectVariable(InTreeName.c_str(),"myevent",m);

	return;

}

double Analysis::deltaR(double eta1, double phi1, double eta2, double phi2){
	double dR, dPhi, dEta;
	dR=dPhi=dEta=0.0;
	dPhi = phi1-phi2;
	if (dPhi < -TMath::Pi()) dPhi += TMath::TwoPi();
	if (dPhi > +TMath::Pi()) dPhi -= TMath::TwoPi();
	dEta = eta1-eta2;
	dR = sqrt(dPhi*dPhi+dEta*dEta);

	return dR;
}

double Analysis::deltaR(myobject o1, myobject o2){
	return deltaR(o1.eta,o1.phi,o2.eta,o2.phi);
}
 
myobject Analysis::ClosestInCollection(myobject o1, std::vector<myobject> collection, double max=0.5)
{
	int index = -1;
	double minDist = 999.;
	for(uint i = 0; i< collection.size(); i++)
	{
		double dR = deltaR(o1,collection[i]);
		if(dR< max && dR < minDist)
		{
			index=i;
			minDist=dR;
		}
	}
	if(index>=0) return collection[index];
	else return o1;
}

double Analysis::DistanceToClosestInCollection(myobject o1, std::vector<myobject> collection)
{
	double minDist = 999.;
	for(uint i = 0; i< collection.size(); i++)
	{
		double dR = deltaR(o1,collection[i]);
		if(dR < minDist)
		{
			minDist=dR;
		}
	}
	return minDist;
}

bool Analysis::TightEleId(float pt, float eta, double value){
	bool passingId=false;

	if( pt<20. && fabs(eta)<0.8 && value>0.925)
		passingId=true;
	if( pt<20. && fabs(eta)>=0.8 && fabs(eta)<1.479 && value>0.915)
		passingId=true;
	if( pt<20. && fabs(eta)>=1.479 && value>0.965)
		passingId=true;

	if(pt>20. && fabs(eta)<0.8 && value>0.905)
		passingId=true;
	if(pt>20. && fabs(eta)>=0.8 && fabs(eta)<1.479 && value>0.955)
		passingId=true;
	if(pt>20. && fabs(eta)>=1.479 && value>0.975)
		passingId=true;
	//  if(value>10.)cout<<"pt==== "<<pt<<" "<<"eta=== "<<eta<<" "<<"value=== "<<value<<endl;
	return passingId;
}

bool Analysis::TightEleId(myobject o){
	if( o.numLostHitEleInner > 0) return false;
	return TightEleId(o.pt, o.eta_SC,o.Id_mvaNonTrg);
}

bool Analysis::LooseEleId(float pt, float eta, double value){
	bool passingId=false;

	
	if(pt>10. && fabs(eta)<0.8 && value>0.5)
		passingId=true;
	if(pt>10. && fabs(eta)>=0.8 && fabs(eta)<1.479 && value>0.12)
		passingId=true;
	if(pt>10. && fabs(eta)>=1.479 && value>0.6)
		passingId=true;
	//  if(value>10.)cout<<"pt==== "<<pt<<" "<<"eta=== "<<eta<<" "<<"value=== "<<value<<endl;
	return passingId;
}

bool Analysis::LooseEleId(myobject o){
	return LooseEleId(o.pt, o.eta_SC,o.Id_mvaNonTrg);
}

bool Analysis::PFMuonID(myobject mu){

	if(mu.isGlobalMuon &&  mu.isPFMuon && mu.normalizedChi2 < 10. && mu.numberOfValidMuonHits > 0 && mu.numMatchStation > 1 && mu.dB < 0.2
			&& mu.dZ_in < 0.5 && mu.intrkLayerpixel > 0 && mu.trkLayerMeasure > 5) return true;
	else
		return false;

}

double Analysis::RelIso(myobject mu){

	double MuIsoTrk = mu.pfIsoAll;
	double MuIsoEcal = mu.pfIsoGamma;
	double MuIsoHcal = mu.pfIsoNeutral;
	double MuIsoPU = mu.pfIsoPU;
	double relIso = (MuIsoTrk) / mu.pt;
	if (MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU > 0)
		relIso = (MuIsoTrk + MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU) / (mu.pt);

	return relIso;
}



bool Analysis::Trg_MC_12(myevent* m, bool found) {
	map<string, int> myHLT = m->HLT;
	bool Trigger = false;
	bool TriggerEle = false;
	bool TriggerMu = false;


	for (map<string, int> ::iterator ihlt = myHLT.begin(); ihlt != myHLT.end() && !TriggerEle && !TriggerMu; ihlt++) {
		if(found) std::cout << ihlt->first << std::endl; 
		size_t foundEl=(ihlt->first).find(doubEle);
		size_t foundEl2=(ihlt->first).find(doubEle2);
		if(!is2011) foundEl2=foundEl;

		size_t foundMu1=(ihlt->first).find(doubMu);
		size_t foundMu2=(ihlt->first).find(doubMu2);
		size_t foundMu3=(ihlt->first).find(doubMu3);
		if(!is2011) foundMu3=foundMu2;

		if (foundEl!=string::npos || foundEl2!=string::npos)
			{ 
				if(found) std::cout << "found trigger! Decision of " << ihlt->first << " is " << ihlt->second << std::endl; // sync
				TriggerEle = ihlt->second;
			}
		if (foundMu1!=string::npos || foundMu2!=string::npos || foundMu3!=string::npos)
			{ 
				if(found) std::cout << "found trigger! Decision of " << ihlt->first << " is " << ihlt->second << std::endl; // sync
				TriggerMu = ihlt->second;
			}
			
	}
	Trigger = TriggerEle || TriggerMu;
	if(vetoElectronTrigger && TriggerEle) Trigger = false;
	if(vetoMuonTrigger && TriggerMu) Trigger = false;    
	return Trigger;    
}

double Analysis::Tmass(myevent *m, myobject mu) {

	vector<myobject> Met = m->RecMVAMet;

	double tMass_v = sqrt(2*mu.pt*Met.front().et*(1-cos(Met.front().phi-mu.phi)));
	return tMass_v;
}


bool Analysis::WZ_Rej(myevent *m, myobject mu) {

        vector<myobject> Met = m->RecMVAMet;
        bool met = Met.front().pt < 20.0;

        double tMass_v = sqrt(2*mu.pt*Met.front().et*(1-cos(Met.front().phi-mu.phi)));
        bool tMass = tMass_v < 30.0;

        if(tMass)
                return true;
        else
                return false;
}

bool Analysis::AdLepton(std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, std::vector<myobject> Hcand, bool verbose){
	bool Ad_lepton=false;
	if(verbose) std::cout << "Checking additional leptons!" << std::endl;
	if(verbose) std::cout << "There are " << genericMuon.size() << " additional muons." << std::endl;
	for(uint i = 0; i < genericMuon.size(); i++)
	{   
		if(verbose) std::cout << " Mu cand no. " << i << std::endl;
		for(uint j =0; j < Hcand.size(); j+=2){
			if(deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand[j].eta,Hcand[j].phi)> maxDeltaR &&
				deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand[j+1].eta,Hcand[j+1].phi)> maxDeltaR && isLooseMu(genericMuon[i]) && RelIso(genericMuon[i]) < 0.3) 
			Ad_lepton=true;
	   }
	   if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
    }
    if(verbose) std::cout << "There are " << genericElectron.size() << " additional electrons." << std::endl;
	for(uint i = 0; i < genericElectron.size(); i++)
	{   
		for(uint j =0; j < Hcand.size(); j+=2){
			if(deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand[j].eta,Hcand[j].phi)> maxDeltaR &&
				deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand[j+1].eta,Hcand[j+1].phi)> maxDeltaR && LooseEleId(genericElectron[i])  && RelIso(genericElectron[i]) < 0.3)  
			Ad_lepton=true;
	   }
	   if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
	}
	return Ad_lepton;
}

bool Analysis::AdLepton_mt(myevent *m, uint index, std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, std::vector<myobject> goodTau, myobject Hcand1, myobject Hcand2,bool verbose){
	bool Ad_lepton=false;
	if(verbose) std::cout << "Checking additional leptons!" << std::endl;
	if(verbose) std::cout << "There are " << genericMuon.size() << " additional muons." << std::endl;
	//~ for(uint i = 0; i < genericMuon.size(); i++)
	//~ {   
			//~ if(verbose) std::cout << " Mu cand no. " << i << std::endl;
			//~ if(verbose) std::cout << " Distance to 1st is " << deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand1.eta,Hcand1.phi) << std::endl;
			//~ if(verbose) std::cout << " Distance to 2nd is " << deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand2.eta,Hcand2.phi) << std::endl;
			//~ if(verbose) std::cout << " Is good? " << isLooseMu(genericMuon[i]) << std::endl;
			//~ if(verbose) std::cout << " iso is " << RelIso(genericMuon[i]) << std::endl;
			//~ if(verbose) std::cout << " WZ rej is " << WZ_Rej(m,genericMuon[i]) << std::endl;
			//~ 
	//~ //		if (!WZ_Rej(m,genericMuon[i])) continue;
			//~ 
			//~ 
			//~ if(isLooseMu(genericMuon[i]) && RelIso(genericMuon[i]) < 0.3  && i!=index ) 
			//~ Ad_lepton=true;
			//~ if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
	   //~ 
    //~ }
	 if(verbose) std::cout << "There are " << genericElectron.size() << " additional electrons." << std::endl;
	
	for(uint i = 0; i < genericElectron.size(); i++)
	{   
			if(verbose) std::cout << " Ele cand no. " << i << std::endl;
			if(verbose) std::cout << " Distance to 1st is " << deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand1.eta,Hcand1.phi) << std::endl;
			if(verbose) std::cout << " Distance to 2nd is " << deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand2.eta,Hcand2.phi) << std::endl;
			if(verbose) std::cout << " Is good? " << LooseEleId(genericElectron[i]) << std::endl;
			if(verbose) std::cout << " Is very good? " << TightEleId(genericElectron[i]) << std::endl;
			if(verbose) std::cout << " Pt is " << genericElectron[i].pt << std::endl;
			if(verbose) std::cout << " num lost hits is " << genericElectron[i].numLostHitEleInner << std::endl;
			if(verbose) std::cout << " iso is " << RelIso(genericElectron[i]) << std::endl;
		//	if(verbose) std::cout << " WZ rej is " << WZ_Rej(m,genericElectron[i]) << std::endl;
			if (!WZ_Rej(m,genericElectron[i])) continue;
			if( genericElectron[i].numLostHitEleInner > 1) continue;
	
			if(verbose) std::cout << " decision: " << LooseEleId(genericElectron[i]) << " " << 	RelIso(genericElectron[i]) << " " << i << " index " << index << std::endl;
	
			if(LooseEleId(genericElectron[i]) && RelIso(genericElectron[i])<0.3 )  
				Ad_lepton=true;
			if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
	   
	}
	
	if(verbose) std::cout << "Returning " << Ad_lepton << std::endl;
	return Ad_lepton;
}

bool Analysis::AdLepton_et(myevent *m, uint index, std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, std::vector<myobject> goodTau, myobject Hcand1, myobject Hcand2,bool verbose){
	bool Ad_lepton=false;
	if(verbose) std::cout << "Checking additional leptons!" << std::endl;
	if(verbose) std::cout << "There are " << genericMuon.size() << " additional muons." << std::endl;
	for(uint i = 0; i < genericMuon.size(); i++)
	{   
			if(verbose) std::cout << " Mu cand no. " << i << std::endl;
			if(verbose) std::cout << " Distance to 1st is " << deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand1.eta,Hcand1.phi) << std::endl;
			if(verbose) std::cout << " Distance to 2nd is " << deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand2.eta,Hcand2.phi) << std::endl;
			if(verbose) std::cout << " Is good? " << isLooseMu(genericMuon[i]) << std::endl;
			if(verbose) std::cout << " iso is " << RelIso(genericMuon[i]) << std::endl;
			if(verbose) std::cout << " WZ rej is " << WZ_Rej(m,genericMuon[i]) << std::endl;
			
		//	if (!WZ_Rej(m,genericMuon[i])) continue;
			
			
			if(isLooseMu(genericMuon[i]) && RelIso(genericMuon[i]) < 0.3  ) 
			Ad_lepton=true;
			if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
	   
    }
	 if(verbose) std::cout << "There are " << genericElectron.size() << " additional electrons." << std::endl;
	//~ 
	for(uint i = 0; i < genericElectron.size(); i++)
	{   
			if(verbose) std::cout << " Ele cand no. " << i << std::endl;
			if(verbose) std::cout << " Distance to 1st is " << deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand1.eta,Hcand1.phi) << std::endl;
			if(verbose) std::cout << " Distance to 2nd is " << deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand2.eta,Hcand2.phi) << std::endl;
			if(verbose) std::cout << " Is good? " << LooseEleId(genericElectron[i]) << std::endl;
			if(verbose) std::cout << " Is very good? " << TightEleId(genericElectron[i]) << std::endl;
			if(verbose) std::cout << " Pt is " << genericElectron[i].pt << std::endl;
			if(verbose) std::cout << " num lost hits is " << genericElectron[i].numLostHitEleInner << std::endl;
			if(verbose) std::cout << " iso is " << RelIso(genericElectron[i]) << std::endl;
			if(verbose) std::cout << " WZ rej is " << WZ_Rej(m,genericElectron[i]) << std::endl;
		//	if (!WZ_Rej(m,genericElectron[i])) continue;
			//~ if( genericElectron[i].numLostHitEleInner > 1) continue;
	//~ 
			//~ if(verbose) std::cout << " decision: " << LooseEleId(genericElectron[i]) << " " << 	RelIso(genericElectron[i]) << " " << i << " index " << index << std::endl;
	//~ 
			//~ if(LooseEleId(genericElectron[i]) && RelIso(genericElectron[i])<0.3 && i!=index )  
				//~ Ad_lepton=true;
			//~ if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
	   //~ 
	}
	
	if(verbose) std::cout << "Returning " << Ad_lepton << std::endl;
	return Ad_lepton;
}

bool Analysis::AdLepton_em(myevent *m, uint index_e, uint index_m, std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, myobject Hcand1, myobject Hcand2,bool verbose){
	bool Ad_lepton=false;
	if(verbose) std::cout << "Checking additional leptons!" << std::endl;
	if(verbose) std::cout << "There are " << genericMuon.size() << " additional muons." << std::endl;
	for(uint i = 0; i < genericMuon.size(); i++)
	{   
			if(verbose) std::cout << " Mu cand no. " << i << std::endl;
			if(verbose) std::cout << " Distance to 1st is " << deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand1.eta,Hcand1.phi) << std::endl;
			if(verbose) std::cout << " Distance to 2nd is " << deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand2.eta,Hcand2.phi) << std::endl;
			if(verbose) std::cout << " Is good? " << isLooseMu(genericMuon[i]) << std::endl;
			if(verbose) std::cout << " iso is " << RelIso(genericMuon[i]) << std::endl;
			if(verbose) std::cout << " WZ rej is " << WZ_Rej(m,genericMuon[i]) << std::endl;
			
		//	if (!WZ_Rej(m,genericMuon[i])) continue;
			
			
			if(isLooseMu(genericMuon[i]) && RelIso(genericMuon[i]) < 0.3 && i!=index_m ) 
			Ad_lepton=true;
			if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
	   
    }
	 //~ if(verbose) std::cout << "There are " << genericElectron.size() << " additional electrons." << std::endl;
	//~ 
	//~ for(uint i = 0; i < genericElectron.size(); i++)
	//~ {   
			//~ if(verbose) std::cout << " Ele cand no. " << i << std::endl;
			//~ if(verbose) std::cout << " Distance to 1st is " << deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand1.eta,Hcand1.phi) << std::endl;
			//~ if(verbose) std::cout << " Distance to 2nd is " << deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand2.eta,Hcand2.phi) << std::endl;
			//~ if(verbose) std::cout << " Is good? " << LooseEleId(genericElectron[i]) << std::endl;
			//~ if(verbose) std::cout << " Is very good? " << TightEleId(genericElectron[i]) << std::endl;
			//~ if(verbose) std::cout << " Pt is " << genericElectron[i].pt << std::endl;
			//~ if(verbose) std::cout << " num lost hits is " << genericElectron[i].numLostHitEleInner << std::endl;
			//~ if(verbose) std::cout << " iso is " << RelIso(genericElectron[i]) << std::endl;
			//~ if(verbose) std::cout << " WZ rej is " << WZ_Rej(m,genericElectron[i]) << std::endl;
		//~ //	if (!WZ_Rej(m,genericElectron[i])) continue;
			//~ if( genericElectron[i].numLostHitEleInner > 1) continue;
	//~ 
			//~ if(verbose) std::cout << " decision: " << LooseEleId(genericElectron[i]) << " " << 	RelIso(genericElectron[i]) << " " << i << " index " << index_e << std::endl;
	//~ 
			//~ if(LooseEleId(genericElectron[i]) && RelIso(genericElectron[i])<0.3 && i!=index_e )  
				//~ Ad_lepton=true;
			//~ if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
	   //~ 
	//~ }
	
	if(verbose) std::cout << "Returning " << Ad_lepton << std::endl;
	return Ad_lepton;
}

bool Analysis::AdLepton_tt(std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, std::vector<myobject> goodTau, myobject Hcand1, myobject Hcand2,bool verbose){
	bool Ad_lepton=false;
	if(verbose) std::cout << "Checking additional leptons!" << std::endl;
	if(verbose) std::cout << "There are " << genericMuon.size() << " additional muons." << std::endl;
	for(uint i = 0; i < genericMuon.size(); i++)
	{   
			if(verbose) std::cout << " Mu cand no. " << i << std::endl;
			if(verbose) std::cout << " Distance to 1st is " << deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand1.eta,Hcand1.phi) << std::endl;
			if(verbose) std::cout << " Distance to 2nd is " << deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand2.eta,Hcand2.phi) << std::endl;
			if(verbose) std::cout << " Is good? " << isLooseMu(genericMuon[i]) << std::endl;
			if(verbose) std::cout << " iso is " << RelIso(genericMuon[i]) << std::endl;
			
			if(isLooseMu(genericMuon[i]) && RelIso(genericMuon[i]) < 0.3) 
			Ad_lepton=true;
			if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
	   
    }
	 if(verbose) std::cout << "There are " << genericElectron.size() << " additional electrons." << std::endl;
	
	for(uint i = 0; i < genericElectron.size(); i++)
	{   
			if(verbose) std::cout << " Ele cand no. " << i << std::endl;
			if(verbose) std::cout << " Distance to 1st is " << deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand1.eta,Hcand1.phi) << std::endl;
			if(verbose) std::cout << " Distance to 2nd is " << deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand2.eta,Hcand2.phi) << std::endl;
			if(verbose) std::cout << " Is good? " << LooseEleId(genericElectron[i]) << std::endl;
			if(verbose) std::cout << " iso is " << RelIso(genericElectron[i]) << std::endl;
			
			
			if(LooseEleId(genericElectron[i]) && genericElectron[i].numLostHitEleInner < 2 && RelIso(genericElectron[i]) < 0.3)  
			Ad_lepton=true;
			if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
	   
	}
	
	if(verbose) std::cout << "Returning " << Ad_lepton << std::endl;
	return Ad_lepton;
}

bool Analysis::AdLepton_sig(std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, std::vector<myobject> goodTau, myobject Hcand1, myobject Hcand2,bool verbose){
	bool Ad_lepton=false;
	if(verbose) std::cout << "Checking additional sig leptons!" << std::endl;
	if(verbose) std::cout << "There are " << genericMuon.size() << " additional muons." << std::endl;
	for(uint i = 0; i < genericMuon.size(); i++)
	{   
			if(verbose) std::cout << " Mu cand no. " << i << std::endl;
			if(verbose) std::cout << " Distance to 1st is " << deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand1.eta,Hcand1.phi) << std::endl;
			if(verbose) std::cout << " Distance to 2nd is " << deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand2.eta,Hcand2.phi) << std::endl;
			if(verbose) std::cout << " Is good? " << isLooseMu(genericMuon[i]) << std::endl;
			if(verbose) std::cout << " iso is " << RelIso(genericMuon[i]) << std::endl;
			if(deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand1.eta,Hcand1.phi) < 0.001) continue; // identical object
			if(deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand2.eta,Hcand2.phi) < 0.001) continue; // identical object
			if(isLooseMu(genericMuon[i]) && RelIso(genericMuon[i]) < 0.3) 
			Ad_lepton=true;
			if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
	   
    }
	 if(verbose) std::cout << "There are " << genericElectron.size() << " additional electrons." << std::endl;
	
	for(uint i = 0; i < genericElectron.size(); i++)
	{   
			if(verbose) std::cout << " Ele cand no. " << i << std::endl;
			if(verbose) std::cout << " Distance to 1st is " << deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand1.eta,Hcand1.phi) << std::endl;
			if(verbose) std::cout << " Distance to 2nd is " << deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand2.eta,Hcand2.phi) << std::endl;
			if(verbose) std::cout << " Is good? " << LooseEleId(genericElectron[i]) << std::endl;
			if(verbose) std::cout << " iso is " << RelIso(genericElectron[i]) << std::endl;
			if(deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand1.eta,Hcand1.phi) < 0.001) continue; // identical object
			if(deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand2.eta,Hcand2.phi) < 0.001) continue; // identical object
			
			if(LooseEleId(genericElectron[i]) && genericElectron[i].numLostHitEleInner < 2 && RelIso(genericElectron[i]) < 0.3)  
			Ad_lepton=true;
			if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
	   
	}
	
	if(verbose) std::cout << "Returning " << Ad_lepton << std::endl;
	return Ad_lepton;
}

bool Analysis::DZ_expo(myobject Zcand1, myobject Zcand2, myobject Hcand1, myobject Hcand2, bool verbose)
{
	if(verbose) std::cout << "  > Distances are: " <<  fabs(Zcand1.z_expo - Zcand2.z_expo) << " " << fabs(Zcand1.z_expo - Hcand1.z_expo) <<
					" " << fabs(Zcand1.z_expo - Hcand2.z_expo) << " " << fabs(Zcand2.z_expo - Hcand1.z_expo) <<
					" " << fabs(Zcand2.z_expo - Hcand2.z_expo) << " " << fabs(Hcand1.z_expo - Hcand2.z_expo) << std::endl;
					
	bool dZ_expo = (fabs(Zcand1.z_expo - Zcand2.z_expo) < dZvertex && fabs(Zcand1.z_expo - Hcand1.z_expo) < dZvertex 
					&& fabs(Zcand1.z_expo - Hcand2.z_expo) < dZvertex );//&& fabs(Zcand2.z_expo - Hcand1.z_expo) < dZvertex );
				//	&& fabs(Zcand2.z_expo - Hcand2.z_expo) < dZvertex);// && fabs(Hcand1.z_expo - Hcand2.z_expo) < dZvertex);
    
    if(!dZ_expo && verbose) std::cout << "FAILED same vertex cut!" << std::endl;
    return dZ_expo;		
	

}

bool Analysis::isGoodMu(myobject mu){

                double muPt = mu.pt;
                double eMuta = mu.eta;
                bool muGlobal = mu.isGlobalMuon;
                bool muTracker = mu.isTrackerMuon;
                double relIso = RelIso(mu);

                bool pfID = PFMuonID(mu);

                if (muGlobal && muTracker && muPt > 10. && fabs(eMuta) < 2.4 && pfID)
                {
                        return true;
                }else return false;
}

bool Analysis::isLooseMu(myobject mu){

                double muPt = mu.pt;
                double eMuta = mu.eta;
                bool muGlobal = mu.isGlobalMuon;
                bool muTracker = mu.isTrackerMuon;
                double relIso = RelIso(mu);

                bool pfID = mu.isPFMuon;

                if (muGlobal && muTracker && muPt > 10. && fabs(eMuta) < 2.4 && pfID)
                {
                        return true;
                }else return false;
}

bool Analysis::isGoodEl(myobject el){
	        
	        double elPt = el.pt;
                double elEta = el.eta_SC;
                int missingHits = el.numLostHitEleInner;
                bool elID = TightEleId(elPt,elEta,el.Id_mvaNonTrg);
                double relIso = RelIso(el);

                if (elPt > 10. && fabs(elEta) < 2.5  && elID && missingHits <=1)
                {
                        return true;
                }else return false;
}

		
double Analysis::PairMass(myobject Hcand1, myobject Hcand2){
	TLorentzVector H_1,H_2,H_sum;
    H_1.SetPxPyPzE(Hcand1.px,Hcand1.py,Hcand1.pz,Hcand1.E);
    H_2.SetPxPyPzE(Hcand2.px,Hcand2.py,Hcand2.pz,Hcand2.E);
    H_sum = H_1 + H_2;
	return H_sum.M();
}

double Analysis::PairPt(myobject Hcand1, myobject Hcand2){
	TLorentzVector H_1,H_2,H_sum;
    H_1.SetPxPyPzE(Hcand1.px,Hcand1.py,Hcand1.pz,Hcand1.E);
    H_2.SetPxPyPzE(Hcand2.px,Hcand2.py,Hcand2.pz,Hcand2.E);
    H_sum = H_1 + H_2;
	return H_sum.Pt();
}

bool Analysis::CheckOverlapLooseElectron(myobject tau, std::vector<myobject> elCollection, double maxR, double isoVal, bool verb){
	
		if(verb) std::cout << "Looking for extra electron!" << std::endl;
		bool overlap = false;
		for(uint j = 0; j < elCollection.size() && !overlap; j++)
		{
			if(verb) std::cout << "Checking ele no. " << j << "/" << elCollection.size() << " pt iso ID: " << elCollection[j].pt << " " << RelIso(elCollection[j]) <<
			" " << LooseEleId(elCollection[j]) << " " << elCollection[j].numLostHitEleInner << ": dR = " << deltaR(tau, elCollection[j]) << std::endl;
			if(deltaR(tau,elCollection[j])< maxR && RelIso(elCollection[j]) < isoVal &&  LooseEleId(elCollection[j]) && elCollection[j].numLostHitEleInner <2 ) 
			overlap = true;
		}
	if(verb) std::cout << "extra loose electron returns " << overlap << std::endl; 
	return overlap;	
}

bool Analysis::CheckOverlapLooseMuon(myobject tau, std::vector<myobject> muCollection, double maxR, double isoVal){
	
		bool overlap = false;
		for(uint j = 0; j < muCollection.size() && !overlap; j++)
		{
			if(deltaR(tau,muCollection[j])< maxR && RelIso(muCollection[j]) < isoVal &&  isLooseMu(muCollection[j])) 
			overlap = true;
		}
	return overlap;	
}

std::vector<myobject> Analysis::SelectGoodVxVector(std::vector<myobject> _vertex, double _normChi2 = 0., int _ndof = 4, double _dZ = 24.){
	
	std::vector<myobject> outVx_;
	outVx_.clear();	
	for (uint i = 0; i < _vertex.size(); i++) {
			if (_vertex[i].isValid && _vertex[i].normalizedChi2 > _normChi2 && _vertex[i].ndof > _ndof && fabs(_vertex[i].z) < _dZ)
			outVx_.push_back(_vertex[i]);
	}
	return outVx_;
}
	
std::vector<myobject> Analysis::SelectGoodMuVector(std::vector<myobject> _muon, bool verb, double muPt_ =10., double muEta_ = 2.4){

	std::vector<myobject> outMu_;
	outMu_.clear();
	for (uint i = 0; i < _muon.size(); i++) {
	
			
			double muPt = _muon[i].pt;
			double muEta = _muon[i].eta;
			bool muGlobal = _muon[i].isGlobalMuon;
			bool muTracker = _muon[i].isTrackerMuon;
			
			if ((muGlobal || muTracker) && muPt > muPt_ && fabs(muEta) < muEta_){
				if(verb) std::cout << " pre-muon " << i << " pt eta etaSC: " << muPt << " " 
				<< muEta << std::endl;
	        	outMu_.push_back(_muon[i]);
			}else{
				if(verb) std::cout << " pre-_muon no. " << i << " has been rejected because of global|tracker pt eta:" <<
				muGlobal << muTracker << " " << muPt << " " << muEta << std::endl; 
			}
	}
	return outMu_;
}

std::vector<myobject> Analysis::SelectGoodElVector(std::vector<myobject> _electron, bool verb, double elPt_ =10., double elEta_ = 2.4){

	std::vector<myobject> outEl_;
	outEl_.clear();
	for (uint i = 0; i < _electron.size(); i++) {
	
			double elPt = _electron[i].pt;
			double elEta = _electron[i].eta_SC;
			
			if (elPt > 10. && fabs(elEta) < 2.5 )
			{
				if(verb) std::cout << " pre-_electron " << i << " pt eta etaSC: " << elPt << " " 
				<< elEta << " " << _electron[i].eta << std::endl;
				outEl_.push_back(_electron[i]);
	        }else{
				if(verb) std::cout << "Pre-_electron no. " << i << " rejected: " << elPt << " " << elEta << std::endl;
			}
		}
	return outEl_;
}

void Analysis::CrossCleanWithMu(std::vector<myobject>* _input, std::vector<myobject> _muon, bool verb, double _maxDeltaR, double _muIso = 0.3, bool _looseMuId = true){
	
	for(int i = 0; i < int(_input->size()); i++)
		{
			if(verb) std::cout << "Looping over input object no. " << i << " out of " << _input->size() << std::endl;
			bool removed = false;
		
			for(uint j = 0; j < _muon.size() && !removed; j++)
			{
				if(verb) std::cout << "Looping over mu no. " << j << " out of " << _muon.size() << " " << 
				deltaR(_input->at(i),_muon[j]) << std::endl;
				if(verb) std::cout << " > Pt is " << _muon[j].pt << " iso is " << RelIso(_muon[j]) << " ID is " << isLooseMu(_muon[j]) << std::endl;
				bool ID = _looseMuId? isLooseMu(_muon[j]) : true;
				if(deltaR(_input->at(i),_muon[j])< _maxDeltaR && RelIso(_muon[j]) < _muIso && ID) 
				{	_input->erase(_input->begin()+i); i--; removed = true;}
				if(verb) std::cout << "input removed ? " << removed << std::endl;
			}
	
		}
}

bool Analysis::FindZ(std::vector<myobject>* _lepton, std::vector<myobject>* _Zcand, bool _isMu, bool verb, double _maxDeltaR, double _bestMass,
double _massLow = 60., double _massHi = 120., double _relIso = 0.3){
	
	bool Zll = false;
	bool Zcand=false;
	double dMass=999.0;
	int Zindex[2] = {-1,-1};
	if(verb && _isMu) std::cout << " Looking for Zmm." << std::endl;
	if(verb && !_isMu) std::cout << " Looking for Zee." << std::endl;
	for(uint i = 0; i < _lepton->size(); i++)
		{
			if(verb) std::cout << "  ->loose lepton no. "<< i << "/" << _lepton->size() 
			<< " has pt "<<  (_lepton->at(i)).pt << " and charge " << (_lepton->at(i)).charge 
			<< " and iso "  << RelIso(_lepton->at(i)) << std::endl;
			if(Zll) continue;
			if(RelIso(_lepton->at(i)) > _relIso) continue;
			if(verb)  std::cout << " Passed iso." << std::endl;
			if(_isMu && !isLooseMu(_lepton->at(i))) continue;
			else if(!_isMu && (!LooseEleId(_lepton->at(i))|| (_lepton->at(i)).numLostHitEleInner>1) ) continue;
			if(verb)  std::cout << " Passed ID" << std::endl;
			if(verb) std::cout << "  -> Passed pre-selection " << std::endl;
			for(uint j = i+1; j < _lepton->size() && !Zll; j++)
			{
				if(verb) std::cout << "  -->second lepton no. "<< j << " has pt "<<  (_lepton->at(j)).pt << " and charge " << (_lepton->at(j)).charge 
				<< " and iso "  << RelIso(_lepton->at(j)) << std::endl;
				if(RelIso(_lepton->at(j)) > _relIso) continue;
				if(verb)  std::cout << " Passed iso." << std::endl;
				if(_isMu && !isLooseMu(_lepton->at(j))) continue;
				else if(!_isMu && (!LooseEleId(_lepton->at(j))|| (_lepton->at(j)).numLostHitEleInner>1) ) continue;
				if(verb)  std::cout << " Passed ID" << std::endl;
				if((_lepton->at(i)).charge*(_lepton->at(j)).charge >=0.) continue;
				if(deltaR(_lepton->at(i),_lepton->at(j))< _maxDeltaR) continue;
				if(verb) std::cout << " Passed pre-selection " << std::endl;
				
				double mass = PairMass(_lepton->at(i),_lepton->at(j));
				if(verb) std::cout << " mass " << mass << std::endl;
				
				if(mass > _massLow && mass < _massHi){
					Zll=true;
					double dM = 999.;
					if(_bestMass > 0.0){
						Zll=false;
						dM=fabs(mass-BestMassForZ);	
						if(dM < dMass){
							Zindex[0]=i;
							Zindex[1]=j;
							dMass=dM;
							Zcand=true;
						}
					}else{
						Zcand=true;
						Zindex[0]=i;
						Zindex[1]=j;
					}
				}
			}
		}
		if(Zindex[0] > -1 && Zindex[1] > -1 && Zcand){
	        int i = Zindex[0];
			int j = Zindex[1];
		if((_lepton->at(i)).pt > 20.){
			_Zcand->push_back(_lepton->at(i));
			_Zcand->push_back(_lepton->at(j));
			_lepton->erase(_lepton->begin()+i);
			_lepton->erase(_lepton->begin()+j-1);
			Zll=true;
		}
	}
	return Zll;	
}

std::vector<myGenobject> FindTrueZZ(std::vector<myGenobject>* _allGen){
	std::vector<myGenobject> outZZ_;
	outZZ_.clear();
	//std::cout << "-----------> NEW SEARCH <-------------------" << std::endl;
	for(uint i = 0; i < _allGen->size(); i++)
		{
			if((_allGen->at(i)).pdgId==23 && (_allGen->at(i)).status==2){
				//~ std::cout << "checking particle no. " << i << " pdg id: " << (_allGen->at(i)).pdgId << 
				//~ " status: " << (_allGen->at(i)).status << " mother pdgID: " << (_allGen->at(i)).mod_pdgId 
				//~ << " Gmod pdgID: " << (_allGen->at(i)).mod_pdgId <<  std::endl;
				outZZ_.push_back(_allGen->at(i));
			}
		}
	if(outZZ_.size()!=2){
		outZZ_.clear();
		TLorentzVector lep1,lep2,lepA,lepB;
		uint lep2_index=0;
		uint lep1_index=0;
		bool Z1=false;
		bool Z2=false;
		myGenobject gen_z1,gen_z2;
		for(uint i = 0; i < _allGen->size(); i++)
		{
			int pdgId=(_allGen->at(i)).pdgId;
			int status = (_allGen->at(i)).status;
			
			//~ std::cout << "checking particle no. " << i << " pdg id: " << (_allGen->at(i)).pdgId << 
				//~ " status: " << (_allGen->at(i)).status << " mother pdgID: " << (_allGen->at(i)).mod_pdgId 
				//~ << " Gmod pdgID: " << (_allGen->at(i)).mod_pdgId <<  std::endl;
			if(status==1 &&(!Z1||!Z2))// decay products after ISR/FSR
			{
				if(abs(pdgId)==11||abs(pdgId)==13||abs(pdgId)==15) //lepton
				{
					//std::cout << i << ":lepton1 candidate" << pdgId  << std::endl;
					// looking for the second
					if(!Z1) lep1.SetPtEtaPhiM((_allGen->at(i)).pt,(_allGen->at(i)).eta,(_allGen->at(i)).phi,(_allGen->at(i)).mass);
					for(uint j = i+1; j < _allGen->size() && !Z1; j++)
					{
						int pdgId2=(_allGen->at(j)).pdgId;
						int status2 = (_allGen->at(j)).status;
						
			
						if(pdgId2==-pdgId&&status2==1)
						{
						//	std::cout << "lep2 cand" << pdgId2 << std::endl;
							lep2.SetPtEtaPhiM((_allGen->at(j)).pt,(_allGen->at(j)).eta,(_allGen->at(j)).phi,(_allGen->at(j)).mass);
							lep2+=lep1;
							//std::cout << "Cand mass is " << lep2.M() << std::endl;
							 
								Z1=true; 
								lep2_index=j;
								lep1_index=i;
								gen_z1.pt=lep2.Pt();
								gen_z1.eta=lep2.Eta();
								gen_z1.phi=lep2.Phi();
								gen_z1.mass=lep2.M();
								outZZ_.push_back(gen_z1);
								
								
					
						}
					
					}
					if(Z1&&!Z2&& (i!=lep1_index&&i!=lep2_index))
					{
						lepA.SetPtEtaPhiM((_allGen->at(i)).pt,(_allGen->at(i)).eta,(_allGen->at(i)).phi,(_allGen->at(i)).mass);
					//	std::cout << i <<":lepA candidate" << pdgId << std::endl;
					}
					
					for(uint j = i+1; j < _allGen->size() && Z1 && !Z2 && (i!=lep1_index && i!=lep2_index) ; j++)
					{
						if(j==lep2_index|| j==lep1_index) continue;
						int pdgId2=(_allGen->at(j)).pdgId;
						int status2 = (_allGen->at(j)).status;
				//		std::cout << j <<":looking for match with " << pdgId2 << " " << status2 << std::endl;
						if(pdgId2==-pdgId&&status2==1)
						{
							
						//	std::cout << "lepB cand" << std::endl;
							lepB.SetPtEtaPhiM((_allGen->at(j)).pt,(_allGen->at(j)).eta,(_allGen->at(j)).phi,(_allGen->at(j)).mass);
							lepB+=lepA;
							//std::cout << "Cand mass is " << lepB.M() << std::endl;
							Z2=true; 
							gen_z2.pt=lepB.Pt();
							gen_z2.eta=lepB.Eta();
							gen_z2.phi=lepB.Phi();
							gen_z2.mass=lepB.M();
							outZZ_.push_back(gen_z2);
					
						}
					
					}
				} 
			}
		}
	}
	
	return outZZ_;
}

void Analysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
	entries++;

	if(doNtuple){
	o_run=0;
	o_lumi=0;
	o_event=0;
	
	//clearing output vectors
	o_pass=false;
	o_FR=false;
	o_FRt.clear();
	o_event_weight=0.;
	o_type=0;
	o_px_Z1=0.;
	o_px_Z2=0.;
	o_px_H1=0.;
	o_px_H2=0.;
	o_py_Z1=0.;
	o_py_Z2=0.;
	o_py_H1=0.;
	o_py_H2=0.;
	o_pz_Z1=0.;
	o_pz_Z2=0.;
	o_pz_H1=0.;
	o_pz_H2=0.;
	o_M_Z1=0.;
	o_M_Z2=0.;
	o_M_H1=0.;
	o_M_H2=0.;
	o_pdg_Z1=0.;
	o_pdg_Z2=0.;
	o_pdg_H1=0.;
	o_pdg_H2=0.;

	
	o_FR_n=0;
	o_FR_type.clear();
	o_FR_px_H1.clear();
	o_FR_px_H2.clear();
	o_FR_py_H1.clear();
	o_FR_py_H2.clear();
	o_FR_pz_H1.clear();
	o_FR_pz_H2.clear();
	o_FR_M_H1.clear();
	o_FR_M_H2.clear();
	o_FR_pdg_H1.clear();
	o_FR_pdg_H2.clear();

	
	o_MET_x=0;
	o_MET_y=0;
	
	o_covMET_00=0;
	o_covMET_01=0;
	o_covMET_10=0;
	o_covMET_11=0;
	//pdf info
	o_pdf_alphaQCD=0;
	o_pdf_alphaQED=0;
	o_pdf_qScale=0;
	o_pdf_weight=0;
	o_pdf_scalePDF=0;
	o_pdf_binningValue0=0;
	o_pdf_id_1=0;
	o_pdf_id_2=0;
	o_pdf_x_1=0;
	o_pdf_x_2=0;
	o_pdf_xPDF_1=0;
	o_pdf_xPDF_2=0;
	o_pdf_hasPDF=0; 
	o_pdf_hasBinningValues=0; 
	o_pdf_signalProcessID=0; 
	o_pdf_binningValueSize=0; 
	
	o_gen_pt_Z1=0;
	o_gen_pt_Z2=0;
	o_gen_eta_Z1=0;
	o_gen_eta_Z2=0;
	o_gen_phi_Z1=0;
	o_gen_phi_Z2=0;
	o_gen_mass_Z1=0;
	o_gen_mass_Z2=0;
	
	o_gen_MET_x=0;
	o_gen_MET_y=0;
	o_gen_MET=0;
}

	// bookkepping part
	++m_allEvents;
	if(m->runNumber!=current_run || m->lumiNumber!=current_lumi){
		lumi << m->runNumber << " " << m->lumiNumber << std::endl;
		current_run=m->runNumber;
		current_lumi=m->lumiNumber;
	}
	TString fileName = GetInputTree(InTreeName.c_str())->GetDirectory()->GetFile()->GetName(); // name of the current file
					
	m_logger << DEBUG << " Now executing event " << m->eventNumber << " in a run " << m->runNumber << SLogger::endmsg;
	//lumi << m->runNumber << " " << m->eventNumber << std::endl;
		Hist("h_nPU_Info")->Fill(m->PUInfo);
		Hist("h_nPU_InfoTrue")->Fill(m->PUInfo_true);
		Hist("h_nPU_Bunch0")->Fill(m->PUInfo_Bunch0);

	// sync check
	
	
	

	
	// for debug printout for a given event
	long eNumber = m->eventNumber;
	bool examineThisEvent;
	long examineNumber;
	if(UseLongEvent){
		long temp = long(OverM)*1000000+long(BelowM);
		examineNumber=temp;
	}else examineNumber=examineEvent;
	if( examineNumber==eNumber) examineThisEvent=true;
	else examineThisEvent=false;
	
	if(examineThisEvent) std::cout << "Examining! Event number " << eNumber << " ENTRY: " << m_allEvents << std::endl;
	
	sync_vec_Channel.clear();
	sync_vec_subChannel.clear();
	sync_vec_HMass.clear();
	sync_vec_l3Pt.clear();
	sync_vec_l3Eta.clear();
	sync_vec_l3_CloseJetPt.clear();
	sync_vec_l3_CloseJetEta.clear();
	sync_vec_l4Pt.clear();
	sync_vec_l4Eta.clear();
	sync_vec_l4_CloseJetPt.clear();
	sync_vec_l4_CloseJetEta.clear();

	if(doSync)
	{
		RunLumiEvent thisRLE(m->runNumber, m->lumiNumber, m->eventNumber);
		//(203912,105,135623662);
		//(203912,107,138473080);
		//
		treemap::iterator it=syncTreeMap.find(thisRLE);
		long index =0;
		int plusEvents = 0;
				
		if(it!=syncTreeMap.end())
		{
			index=(it->second).first;
			plusEvents=(it->second).second;
			std::cout << " event for sync: " << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber <<
			" index is " << index << " and plus events are " << plusEvents << std::endl;
			examineThisEvent=true;
			syncTree->GetEvent(index);
			for(int iEv=0; iEv <= plusEvents; iEv++)
			{
				syncTree->GetEvent(index+iEv);
			
				std::cout << " Obtaining entry#" << index << "/" << iEv << ": " << sync_run << ":" << sync_lumi << ":" << sync_event << 
				"channel/subchannel:" << sync_Channel << " (" << EventTypeName(EventTypeConv(sync_Channel)) << ")/" << sync_subChannel << std::endl;
				std::cout << "  -> Hmass = " << sync_HMass << " l3pt= " << sync_l3Pt << " " << sync_l3Eta << " l4Pt= " << sync_l4Pt << " " << sync_l4Eta << std::endl;
			
				if(sync_Channel > -1) sync_vec_Channel.push_back(sync_Channel);
				else sync_vec_Channel.push_back(sync_Channel+48);
		        sync_vec_subChannel.push_back(sync_subChannel);
				sync_vec_HMass.push_back(sync_HMass);
				sync_vec_l3Pt.push_back(sync_l3Pt);
				sync_vec_l3Eta.push_back(sync_l3Eta);
				sync_vec_l3_CloseJetPt.push_back(sync_l3_CloseJetPt);
				sync_vec_l3_CloseJetEta.push_back(sync_l3_CloseJetEta);
				sync_vec_l4Pt.push_back(sync_l4Pt);
				sync_vec_l4Eta.push_back(sync_l4Eta);
				sync_vec_l4_CloseJetPt.push_back(sync_l4_CloseJetPt);
				sync_vec_l4_CloseJetEta.push_back(sync_l4_CloseJetEta);	
				
				syncTree->GetEvent(index+iEv+1);
				std::cout << " Next entry#" << index << "/" << iEv << ": " << sync_run << ":" << sync_lumi << ":" << sync_event << std::endl;
			}
			
		}
	}
	
	double PUWeight = 1.0;
	double nPU = 0.0;
	nPU = m->PUInfo_true;
	if(useObservedPU) nPU=m->PUInfo_true;
	if(isSimulation){	
		PUWeight = LumiWeights_->weight( nPU );
		if(IgnorePUW) PUWeight = 1.0;
	}
	
	Hist("h_PU_weight")->Fill(PUWeight);
	Hist("h_nPU_raw")->Fill(m->PUInfo_true);
	Hist("h_nPU_reweight")->Fill(m->PUInfo_true,PUWeight);
	Hist("h_nPU_Info_W")->Fill(m->PUInfo,PUWeight);
	Hist("h_nPU_InfoTrue_W")->Fill(m->PUInfo_true,PUWeight);
	Hist("h_nPU_Bunch0_W")->Fill(m->PUInfo_Bunch0,PUWeight);


	
    //vertex selection
	std::vector<myobject> vertex = m->Vertex;
	std::vector<myobject> goodVertex = SelectGoodVxVector(vertex);
	short nGoodVx=goodVertex.size();

	
	h_cut_flow->Fill(0.0,1.0);
	h_cut_flow_weight->Fill(0.0,PUWeight);

	Hist("h_Nvertex_NoCut")->Fill(nGoodVx);
	Hist("h_Nvertex_NoCut_W")->Fill(nGoodVx,PUWeight);

	bool trigPass;
	trigPass = Trg_MC_12(m,examineThisEvent);
	m_logger << DEBUG <<" Trigger decision " << trigPass << SLogger::endmsg;
	if(!trigPass)
	{
		if(examineThisEvent) std::cout << "Trigger fail! " << examineEvent << std::endl;
		for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
		{
			std::cout << " Channel " << sync_vec_Channel[iSync] << " " << EventTypeConv(sync_vec_Channel[iSync]) << " " << EventTypeName(EventTypeConv(sync_vec_Channel[iSync])) 
			<< " subch: " << sync_vec_subChannel[iSync] << std::endl;
			int subCh = sync_vec_subChannel[iSync];
			int Ch = EventTypeConv(sync_vec_Channel[iSync]);
			
			h_fail_reason[subCh]->Fill(0.,double(Ch));
		}
		return;
	}
	
	h_cut_flow->Fill(1,1);
	h_cut_flow_weight->Fill(1,PUWeight);
	
	// at least one good vertex
	if(nGoodVx < 1){
		if(examineThisEvent) std::cout << "vertex fail" << std::endl;
		for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
		{
			std::cout << " Channel " << sync_vec_Channel[iSync] << " " << EventTypeConv(sync_vec_Channel[iSync]) << " " << EventTypeName(EventTypeConv(sync_vec_Channel[iSync])) 
			<< " subch: " << sync_vec_subChannel[iSync] << std::endl;
			int subCh = sync_vec_subChannel[iSync];
			int Ch = EventTypeConv(sync_vec_Channel[iSync]);
			
			h_fail_reason[subCh]->Fill(1.,double(Ch));
		}
		 return;
	 
	 }
	
	h_cut_flow->Fill(2,1);
	h_cut_flow_weight->Fill(2,PUWeight);
	

	vector<myobject> Met = m->RecMVAMet;

	Hist("h_PF_MET")->Fill(Met.front().et,PUWeight);
	h_PF_MET_nPU->Fill(nGoodVx,Met.front().et,PUWeight);

	
	// looseMuons
	std::vector<myobject> muon = m->PreSelectedMuons;
	if(examineThisEvent) std::cout << " There are " << muon.size() << " preselected muons " << std::endl;
	std::vector<myobject> denomMuon = SelectGoodMuVector(muon,examineThisEvent);
	if(examineThisEvent) std::cout << " There are " << denomMuon.size() << " selected muons " << std::endl;
	Hist("h_n_goodMu")->Fill(denomMuon.size(),PUWeight);


	// looseElectrons
	std::vector<myobject> electron = m->PreSelectedElectrons;
	if(examineThisEvent) std::cout << " There are " << electron.size() << " preselected electrons " << std::endl;
	std::vector<myobject> denomElectron = SelectGoodElVector(electron,examineThisEvent);
	Hist("h_n_goodEl")->Fill(denomElectron.size(),PUWeight);
	
	//overlap cleaning
	CrossCleanWithMu(&denomElectron,denomMuon,examineThisEvent,maxDeltaR);
	if(examineThisEvent) std::cout << " There are " << denomElectron.size() << " selected electrons" << std::endl;
	
	
	// Z compatibility
	std::vector<myobject> Zcand;
	Zcand.clear();
	bool Zmumu = false;
	bool Zee = false;
	
	if(!DoubleE){
		Zmumu=FindZ(&denomMuon, &Zcand, true, examineThisEvent, maxDeltaR, BestMassForZ);
	}
	
	if(!Zmumu && !DoubleM)
	{
		Zee=FindZ(&denomElectron, &Zcand, false, examineThisEvent, maxDeltaR, BestMassForZ);	
	}

	
	double corrZlep1,corrZlep2;
	corrZlep1=corrZlep2=1.0;
	double Z_weight = PUWeight;
	
	if(isSimulation && !IgnoreSF){
		if(Zmumu)
		{
			if(is2012_53){ 
				if(SFShiftUp_Mu){
				    if(onlyIDIso && !onlyTrigger){
						corrZlep1=(Cor_ID_Iso_Mu_Loose_2012_53X(Zcand[0])+Unc_ID_Iso_Mu_Loose_2012_53X(Zcand[0]))*(Corr_Trg_Mu_2012_53X(Zcand[0]));
						corrZlep2=(Cor_ID_Iso_Mu_Loose_2012_53X(Zcand[1])+Unc_ID_Iso_Mu_Loose_2012_53X(Zcand[1]))*(Corr_Trg_Mu_2012_53X(Zcand[1]));
                    }else if(!onlyIDIso && onlyTrigger){
						corrZlep1=(Cor_ID_Iso_Mu_Loose_2012_53X(Zcand[0]))*(Corr_Trg_Mu_2012_53X(Zcand[0])+Unc_Trg_Mu_2012_53X(Zcand[0]));
						corrZlep2=(Cor_ID_Iso_Mu_Loose_2012_53X(Zcand[1]))*(Corr_Trg_Mu_2012_53X(Zcand[1])+Unc_Trg_Mu_2012_53X(Zcand[1]));
                    }
				}else if(SFShiftDown_Mu){
					if(onlyIDIso && !onlyTrigger){
						corrZlep1=(Cor_ID_Iso_Mu_Loose_2012_53X(Zcand[0])-Unc_ID_Iso_Mu_Loose_2012_53X(Zcand[0]))*(Corr_Trg_Mu_2012_53X(Zcand[0]));
						corrZlep2=(Cor_ID_Iso_Mu_Loose_2012_53X(Zcand[1])-Unc_ID_Iso_Mu_Loose_2012_53X(Zcand[1]))*(Corr_Trg_Mu_2012_53X(Zcand[1]));
                    }else if(!onlyIDIso && onlyTrigger){
						corrZlep1=(Cor_ID_Iso_Mu_Loose_2012_53X(Zcand[0]))*(Corr_Trg_Mu_2012_53X(Zcand[0])-Unc_Trg_Mu_2012_53X(Zcand[0]));
						corrZlep2=(Cor_ID_Iso_Mu_Loose_2012_53X(Zcand[1]))*(Corr_Trg_Mu_2012_53X(Zcand[1])-Unc_Trg_Mu_2012_53X(Zcand[1]));
                    }
				}else{ 
					corrZlep1=Cor_ID_Iso_Mu_Loose_2012_53X(Zcand[0])*Corr_Trg_Mu_2012_53X(Zcand[0]);
					corrZlep2=Cor_ID_Iso_Mu_Loose_2012_53X(Zcand[1])*Corr_Trg_Mu_2012_53X(Zcand[1]);
				}
			}
			else{
				corrZlep1=Cor_ID_Iso_Mu_Loose_2011(Zcand[0])*Corr_Trg_Mu_2011(Zcand[0]);
				corrZlep2=Cor_ID_Iso_Mu_Loose_2011(Zcand[1])*Corr_Trg_Mu_2011(Zcand[1]);
			}
			Z_weight *= corrZlep1* corrZlep2;	
		}else if(Zee){
			if(is2012_53){ 
				if(SFShiftUp_Ele){
					if(onlyIDIso && !onlyTrigger){
						corrZlep1=(Cor_ID_Iso_Ele_Loose_2012_53X(Zcand[0])+Unc_ID_Iso_Ele_Loose_2012_53X(Zcand[0]))*(Corr_Trg_Ele_2012_53X(Zcand[0]));
						corrZlep2=(Cor_ID_Iso_Ele_Loose_2012_53X(Zcand[1])+Unc_ID_Iso_Ele_Loose_2012_53X(Zcand[1]))*(Corr_Trg_Ele_2012_53X(Zcand[1]));
                    }else if(!onlyIDIso && onlyTrigger){
						corrZlep1=(Cor_ID_Iso_Ele_Loose_2012_53X(Zcand[0]))*(Corr_Trg_Ele_2012_53X(Zcand[0])+Unc_Trg_Ele_2012_53X(Zcand[0]));
						corrZlep2=(Cor_ID_Iso_Ele_Loose_2012_53X(Zcand[1]))*(Corr_Trg_Ele_2012_53X(Zcand[1])+Unc_Trg_Ele_2012_53X(Zcand[1]));
                    }   
                }else if(SFShiftDown_Ele){
					if(onlyIDIso && !onlyTrigger){
						corrZlep1=(Cor_ID_Iso_Ele_Loose_2012_53X(Zcand[0])-Unc_ID_Iso_Ele_Loose_2012_53X(Zcand[0]))*(Corr_Trg_Ele_2012_53X(Zcand[0]));
						corrZlep2=(Cor_ID_Iso_Ele_Loose_2012_53X(Zcand[1])-Unc_ID_Iso_Ele_Loose_2012_53X(Zcand[1]))*(Corr_Trg_Ele_2012_53X(Zcand[1]));
					}else if(!onlyIDIso && onlyTrigger){
						corrZlep1=(Cor_ID_Iso_Ele_Loose_2012_53X(Zcand[0]))*(Corr_Trg_Ele_2012_53X(Zcand[0])-Unc_Trg_Ele_2012_53X(Zcand[0]));
						corrZlep2=(Cor_ID_Iso_Ele_Loose_2012_53X(Zcand[1]))*(Corr_Trg_Ele_2012_53X(Zcand[1])-Unc_Trg_Ele_2012_53X(Zcand[1]));
					}
				}else{
					corrZlep1=Cor_ID_Iso_Ele_Loose_2012_53X(Zcand[0])*Corr_Trg_Ele_2012_53X(Zcand[0]);
					corrZlep2=Cor_ID_Iso_Ele_Loose_2012_53X(Zcand[1])*Corr_Trg_Ele_2012_53X(Zcand[1]);
				} 
			}else{
				corrZlep1=Cor_ID_Iso_Ele_Loose_2011(Zcand[0])*Corr_Trg_Ele_2011(Zcand[0]);
				corrZlep2=Cor_ID_Iso_Ele_Loose_2011(Zcand[1])*Corr_Trg_Ele_2011(Zcand[1]);
			}
			Z_weight *= corrZlep1* corrZlep2;	
		}
	}
	
	double Zmass = -100.;
	if(Zmumu){
		TLorentzVector muon1;
		TLorentzVector muon2;
		TLorentzVector Zmumu_;			
		muon1.SetPxPyPzE(Zcand[0].px,Zcand[0].py,Zcand[0].pz,Zcand[0].E);        
		muon2.SetPxPyPzE(Zcand[1].px,Zcand[1].py,Zcand[1].pz,Zcand[1].E);        
		Zmumu_=muon1+muon2;        
		Zmass=Zmumu_.M();
		Hist( "h_mu1Z_pt" )->Fill(muon1.Pt(),Z_weight);
		Hist( "h_mu2Z_pt" )->Fill(muon2.Pt(),Z_weight);
		Hist( "h_Zmass_mumu" )->Fill(Zmass,Z_weight);
		Hist( "h_Zpt_mumu" )->Fill(Zmumu_.Pt(),Z_weight);	
		Hist( "h_Z_eta")->Fill(Zmumu_.Eta(),Z_weight);
		Hist( "h_Z_phi")->Fill(Zmumu_.Phi(),Z_weight);
		Hist( "h_Z_lep1_eta")->Fill(muon1.Eta(),Z_weight);
		Hist( "h_Z_lep1_phi")->Fill(muon1.Phi(),Z_weight);
		Hist( "h_Z_lep2_eta")->Fill(muon2.Eta(),Z_weight);
		Hist( "h_Z_lep2_phi")->Fill(muon2.Phi(),Z_weight);	 
	}else if( Zee){	

		TLorentzVector ele1;
		TLorentzVector ele2;
		TLorentzVector Zee_; 
		ele1.SetPxPyPzE(Zcand[0].px,Zcand[0].py,Zcand[0].pz,Zcand[0].E);        
		ele2.SetPxPyPzE(Zcand[1].px,Zcand[1].py,Zcand[1].pz,Zcand[1].E);        
		Zee_=ele1+ele2;
		Zmass=Zee_.M();
		Hist( "h_ele1Z_pt" )->Fill(ele1.Pt(),Z_weight);
		Hist( "h_ele2Z_pt" )->Fill(ele2.Pt(),Z_weight);
		Hist( "h_Zmass_ee" )->Fill(Zmass,Z_weight);
		Hist( "h_Zpt_ee" )->Fill(Zee_.Pt(),Z_weight);
		Hist( "h_Z_eta")->Fill(Zee_.Eta(),Z_weight);
		Hist( "h_Z_phi")->Fill(Zee_.Phi(),Z_weight);
		Hist( "h_Z_lep1_eta")->Fill(ele1.Eta(),Z_weight);
		Hist( "h_Z_lep1_phi")->Fill(ele1.Phi(),Z_weight);
		Hist( "h_Z_lep2_eta")->Fill(ele2.Eta(),Z_weight);
		Hist( "h_Z_lep2_phi")->Fill(ele2.Phi(),Z_weight);
	}

	
	if(Zmumu||Zee){
		m_logger << DEBUG << " There is a Z candidate! " << SLogger::endmsg;
		if(examineThisEvent) std::cout << " Z mass is " << Zmass << std::endl;
	}
	else{
		if(examineThisEvent) std::cout << "No Z cand!" << std::endl;
		for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
		{
			std::cout << " Channel " << sync_vec_Channel[iSync] << " " << EventTypeConv(sync_vec_Channel[iSync]) << " " << EventTypeName(EventTypeConv(sync_vec_Channel[iSync])) 
			<< " subch: " << sync_vec_subChannel[iSync] << std::endl;
			int subCh = sync_vec_subChannel[iSync];
			int Ch = EventTypeConv(sync_vec_Channel[iSync]);
			
			h_fail_reason[subCh]->Fill(2.,double(Ch));
		}
			return;
	}
	
	h_cut_flow->Fill(3,1);
	h_cut_flow_weight->Fill(3,Z_weight);
	
	Hist("h_Nvertex_AfterZ")->Fill(nGoodVx);
	Hist("h_Nvertex_AfterZ_W")->Fill(nGoodVx,Z_weight);
	
	
	// list of good taus 
	std::vector<myobject> goodTau;
	goodTau.clear();
	int muCand=denomMuon.size();
	int elCand=denomElectron.size();
	std::vector<myobject> tau = m->PreSelectedHPSTaus;


	for (uint i = 0; i < tau.size(); i++) {

		double tauEta = tau[i].eta;
		bool LooseMuon = (tau[i].discriminationByMuonLoose2 > 0.5);
		bool DecayMode = (tau[i].discriminationByDecayModeFinding > 0.5);
		double tauPt;
		double tauPx;
		double tauPy;
		double tauPz;
		double tauE;
                //shift the pt of the tau by 1 sigma
		if(ShiftTauES_up && !ShiftTauES_down){
                  tauPt = tau[i].pt + SystUncert_ES * tau[i].pt;
				  tauPx = tau[i].px + SystUncert_ES * tau[i].px;
				  tauPy = tau[i].py + SystUncert_ES * tau[i].py;
				  tauPz = tau[i].pz + SystUncert_ES * tau[i].pz;
				  tauE = tau[i].E + SystUncert_ES * tau[i].E; 	
		}else if(ShiftTauES_down && !ShiftTauES_up){
                  tauPt = tau[i].pt - SystUncert_ES * tau[i].pt;
                  tauPx = tau[i].px - SystUncert_ES * tau[i].px;
				  tauPy = tau[i].py - SystUncert_ES * tau[i].py;
				  tauPz = tau[i].pz - SystUncert_ES * tau[i].pz;
				  tauE = tau[i].E - SystUncert_ES * tau[i].E;         
         }else{ 
                  tauPt = tau[i].pt;
                  tauPx = tau[i].px;
                  tauPy = tau[i].py;
                  tauPz = tau[i].pz;
                  tauE = tau[i].E;
               }

		if (fabs(tauEta) < 2.3 && LooseMuon && DecayMode){
			goodTau.push_back(tau[i]);
			goodTau[goodTau.size()-1].pt = tauPt;
			goodTau[goodTau.size()-1].px = tauPx;
			goodTau[goodTau.size()-1].py = tauPy;
			goodTau[goodTau.size()-1].pz = tauPz;
			goodTau[goodTau.size()-1].E = tauE;
			if(examineThisEvent){
					std::cout << ">Possible MT candidates: " << std::endl;
					for(uint iMu=0; iMu < denomMuon.size(); iMu++)
					{
						std::cout<< "Mu " << iMu << " + tau " << i << "(" << tau[i].pt << " GeV)"
						<< " m = " << PairMass(denomMuon[iMu],tau[i]) << std::endl;
					}
					std::cout << ">Possible ET candidates: " << std::endl;
					for(uint iEl=0; iEl < denomElectron.size(); iEl++)
					{
						std::cout<< "El " << iEl << " + tau " << i << "(" << tau[i].pt << " GeV)"
						<< " m = " << PairMass(denomElectron[iEl],tau[i]) << std::endl;
					}
				}
			
			}
			else{
				if(examineThisEvent){
					std::cout << ">Rejected MT candidates: " << std::endl;
					for(uint iMu=0; iMu < denomMuon.size(); iMu++)
					{
						std::cout<< "Mu " << iMu << " + tau " << i << "(" << tau[i].pt << " GeV)"
						<< " m = " << PairMass(denomMuon[iMu],tau[i]) << std::endl;
					}
					std::cout << ">Rejected ET candidates (eta, muL, DM): " << tauEta << " " << LooseMuon << DecayMode << std::endl;
					for(uint iEl=0; iEl < denomElectron.size(); iEl++)
					{
						std::cout<< "El " << iEl << " + tau " << i << "(" << tau[i].pt << " GeV)"
						<< " m = " << PairMass(denomElectron[iEl],tau[i]) << std::endl;
					}
				}
			}
	}
	
	if(examineThisEvent){
		for(uint iTau=0; iTau < goodTau.size(); iTau++)
		{
			for(uint jTau=iTau+1; jTau < goodTau.size(); jTau++)
			{
				if(goodTau[iTau].pt > Cut_tautau_Pt_1 && goodTau[jTau].pt > Cut_tautau_Pt_2)
				  std::cout << " TT cand: [" << iTau << ", " <<jTau <<"], pt=["<< goodTau[iTau].pt << ", " << 
				  goodTau[jTau].pt <<"], mass = " << PairMass(goodTau[iTau],goodTau[jTau]) <<std::endl;	
			}
		}
		 
			
		}
			
	
	if(examineThisEvent) std::cout << "There is " << goodTau.size() << " goodTaus " << std::endl;
	// overlap check tau-leptons
		
	
	
	uint isoElectrons = 0;
	uint isoMuons = 0;
	for(uint i=0; i< denomElectron.size(); i++)
	{
		if(RelIso(denomElectron[i]) < 0.3 && LooseEleId(denomElectron[i]) && denomElectron[i].numLostHitEleInner<2 ) isoElectrons++;
	}
 
	for(uint i=0; i< denomMuon.size(); i++)
	{
		if(RelIso(denomMuon[i]) < 0.3 && isLooseMu(denomMuon[i])) isoMuons++;
	}
	
	if(isoElectrons > 2  || isoMuons > 2){
		if(examineThisEvent) std::cout << " too much iso leptons: " << isoElectrons << " " << isoMuons << std::endl;
		for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
		{
			std::cout << " Channel " << sync_vec_Channel[iSync] << " " << EventTypeConv(sync_vec_Channel[iSync]) << " " << EventTypeName(EventTypeConv(sync_vec_Channel[iSync])) 
			<< " subch: " << sync_vec_subChannel[iSync] << std::endl;
			int subCh = sync_vec_subChannel[iSync];
			int Ch = EventTypeConv(sync_vec_Channel[iSync]);
			
			h_fail_reason[subCh]->Fill(3.,double(Ch));
		}
		 return;
	 }
	
	h_cut_flow->Fill(4,1);
	h_cut_flow_weight->Fill(4,Z_weight);


	if(examineThisEvent) std::cout << "checking size of electrons and muons...PASSED" << std::endl;
	
	// Z overlap removal
	bool Zoverlap = false;
	
	for(int i = 0; i < int(denomMuon.size()); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{

			if(examineThisEvent) std::cout << "muon no. " << i << " (" << denomMuon[i].pt << ") with Z cand no." << j
			<< " (" << Zcand[j].pt << ") and distance is " <<  deltaR(denomMuon[i],Zcand[j]) << std::endl;
			if(deltaR(denomMuon[i].eta,denomMuon[i].phi,Zcand[j].eta,Zcand[j].phi)< maxDeltaR) 
			{	denomMuon.erase(denomMuon.begin()+i); i--; removed = true;}
			if(removed)Zoverlap=true;

		}
		if(examineThisEvent && removed) std::cout << " mu overlap with Z" << isLooseMu(denomMuon[i]) << std::endl;
	}
	
	for(int i = 0; i < int(denomElectron.size()); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			if(examineThisEvent) std::cout << "electron no. " << i << " (" << denomElectron[i].pt << ") with Z cand no." << j
					<< " (" << Zcand[j].pt << ") and distance is " <<  deltaR(denomElectron[i],Zcand[j]) << std::endl;
			if(deltaR(denomElectron[i].eta,denomElectron[i].phi,Zcand[j].eta,Zcand[j].phi)< maxDeltaR) 
			{	denomElectron.erase(denomElectron.begin()+i); i--; removed = true;}
			if(removed)Zoverlap=true;

		}
		if(examineThisEvent && removed) std::cout << " electron overlap with Z" << std::endl;
	}
//~ 
	for(int i = 0; i < int(goodTau.size()); i++)
	{
		bool removed = false;
		if(examineThisEvent) std::cout << "Checking tau no. " << i << " with pt " << goodTau[i].pt << std::endl;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			if(examineThisEvent) std::cout << "tau no. " << i << " (" << goodTau[i].pt << ") with Z cand no." << j
					<< " (" << Zcand[j].pt << ") and distance is " <<  deltaR(goodTau[i],Zcand[j]) << std::endl;
			
			if(deltaR(goodTau[i].eta,goodTau[i].phi,Zcand[j].eta,Zcand[j].phi)< maxDeltaR) 
			{	goodTau.erase(goodTau.begin()+i); i--; removed = true;}

		}
		if(examineThisEvent && removed) std::cout << " tau overlap with Z" << std::endl;
	}
	// removing taus overlapping with loose isolated muons and electrons
	
	
	
	
	
	//~ 
	if(examineThisEvent) std::cout << "Checking Z overlap..." << std::endl;
	


	Hist("h_n_goodEl_Hcand")->Fill(denomElectron.size());	
	Hist("h_n_goodMu_Hcand")->Fill(denomMuon.size());	
	
    if(examineThisEvent) std::cout << " There are " << denomElectron.size() << " denom electrons after Zremoval" << std::endl;
	
        //generic vector definitions for MUONS and ELECTRONS
	std::vector<myobject> genericMuon;
        genericMuon.clear();
	std::vector<myobject> genericElectron;
        genericElectron.clear();
      
        genericMuon = denomMuon;
        genericElectron = denomElectron;
        

	

	// checking the rest of the event
	

	

	int tauCand = 	goodTau.size();
	if(examineThisEvent) std::cout << " There are " << tauCand << " tau candidates " << std::endl;
		
	Hist("h_n_goodTau_Hcand")->Fill(goodTau.size());	

	// mutau and emu final states
	bool muTau=false;
	bool muE = false;
	bool signal = false;
	bool saved_signal = false;
	short category = -1;
	bool category0 = false;
	bool category1= false;
	bool category2=false;     
	 
	std::vector<myobject> Hcand;
	//std::vector<int> Hcand_type;
	std::vector<myobject> Hcand_cat0;
	std::vector<int> Hcand_type_cat0;
	std::vector<myobject> Hcand_cat1;
	std::vector<int> Hcand_type_cat1;
	std::vector<myobject> Hcand_cat2;
	std::vector<int> Hcand_type_cat2;
	std::vector<myobject> Hcand_FR;
	std::vector<int> Hcand_pass;
	std::vector<int> Hcand_type_FR;
	std::vector<int> Hcand_shape_pass;
	
	std::vector<myobject> Hcand_signal;
	std::vector<int> Hcand_type_signal;
	Hcand.clear();
//	Hcand_type.clear();
	Hcand_cat0.clear();
	Hcand_type_cat0.clear();
	Hcand_cat1.clear();
	Hcand_type_cat1.clear();
	Hcand_cat2.clear();
	Hcand_type_cat2.clear();
	Hcand_pass.clear();
	Hcand_FR.clear();
	Hcand_type_FR.clear();
	Hcand_signal.clear();
	Hcand_type_signal.clear();
	
	std::vector<int> usedTauIdx;
	usedTauIdx.clear();
	if(examineThisEvent) std::cout << " There are " << genericMuon.size() << " mu candidates " << std::endl;
	
	bool tauTau =false;
	
	std::vector<int> s_s_i_TT; //sync_shape_index
    s_s_i_TT.clear();
	for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
	{
		if(sync_vec_subChannel[iSync]==1 && (sync_vec_Channel[iSync] ==9 || sync_vec_Channel[iSync] ==10 )) s_s_i_TT.push_back(iSync);
	}
	
	
	std::vector<int> usedElId;
	std::vector<int> usedTauId;
	
	usedElId.clear();
	usedTauId.clear();

	if(examineThisEvent) std::cout << " Checking tautau " << std::endl;
	for(uint i = 0; i < goodTau.size(); i++)
	{
		if(examineThisEvent) std::cout << " Tau candidate i= " << i << " " << goodTau[i].pt << " " <<  goodTau[i].charge << " " <<
		goodTau[i].discriminationByElectronLoose << std::endl;
		// finding the sync match
		int s_match_i = -1;
		for(uint iSync =0; iSync < s_s_i_TT.size() && s_match_i < 0; iSync++)
		{
			std::cout << " Sync FR candidate #" << iSync << " type:" << sync_vec_Channel[s_s_i_TT[iSync]] <<
			" l3 pt/eta/jeta:" << sync_vec_l3Pt[s_s_i_TT[iSync]] << "/" << sync_vec_l3Eta[s_s_i_TT[iSync]] << "/" << sync_vec_l3_CloseJetEta[s_s_i_TT[iSync]] << 
			" l4 pt/eta/jeta:" << sync_vec_l4Pt[s_s_i_TT[iSync]] << "/" << sync_vec_l4Eta[s_s_i_TT[iSync]] << "/" << sync_vec_l4_CloseJetEta[s_s_i_TT[iSync]] << std::endl;
			//if(Zmumu && EventTypeConv(sync_vec_Channel[s_s_i_TT[iSync]])!=4) continue;
			//if(Zee && EventTypeConv(sync_vec_Channel[s_s_i_TT[iSync]])!=8) continue;
			if(fabs(goodTau[i].pt - sync_vec_l3Pt[s_s_i_TT[iSync]]) < 0.1 && fabs(goodTau[i].eta - sync_vec_l3Eta[s_s_i_TT[iSync]]) < 0.1){
				 std::cout << " matched leading tau" << std::endl;
				 s_match_i=iSync;
			 }
		}
		
		if(goodTau[i].pt < Cut_tautau_Pt_1){
			if(s_match_i > -1){
				std::cout << "Failed lead tau cut: " << goodTau[i].pt << std::endl;
				h_fail_shape_TT->Fill(0.0);
			}
			 continue;
		 }
		if(goodTau[i].discriminationByElectronLoose <= 0.5){
			if(s_match_i > -1){
				std::cout << "Failed lead tau ElId cut: " << std::endl;
				h_fail_shape_TT->Fill(1.0);
			}
			 continue;
		 }
				
		//if(goodTau[i].discriminationByElectronMedium <=0.5) continue;
		//if(goodTau[i].discriminationByMuonMedium <=0.5) continue;
		if(examineThisEvent) std::cout << "   Passed pre-selection" << std::endl;
		double dZ1=deltaR(goodTau[i],Zcand[0]);
		double dZ2=deltaR(goodTau[i],Zcand[1]);
		
		bool match2 = false;
		for(uint j=i+1; j< goodTau.size() && !(category0 && category1 && category2 && signal); j++)
		{
			bool isFakeRate=false;
			bool matchedSync = false;
			if(examineThisEvent) std::cout << " Tau candidate j= " << j << " " << goodTau[j].pt << "ch: " << 
			goodTau[j].charge << " mass: " << PairMass(goodTau[i],goodTau[j]) <<std::endl;
			
			int s_match2_i = -1;
			for(uint iSync =0; iSync < s_s_i_TT.size() && s_match2_i < 0 ; iSync++)
			{
				if((int)iSync==s_match_i) continue;
				std::cout << "SUB Sync FR candidate #" << iSync << " type:" << sync_vec_Channel[s_s_i_TT[iSync]] <<
				" l3 pt/eta/jeta:" << sync_vec_l3Pt[s_s_i_TT[iSync]] << "/" << sync_vec_l3Eta[s_s_i_TT[iSync]] << "/" << sync_vec_l3_CloseJetEta[s_s_i_TT[iSync]] << 
				" l4 pt/eta/jeta:" << sync_vec_l4Pt[s_s_i_TT[iSync]] << "/" << sync_vec_l4Eta[s_s_i_TT[iSync]] << "/" << sync_vec_l4_CloseJetEta[s_s_i_TT[iSync]] << std::endl;
				//if(Zmumu && EventTypeConv(sync_vec_Channel[s_s_i_TT[iSync]])!=4) continue;
				//if(Zee && EventTypeConv(sync_vec_Channel[s_s_i_TT[iSync]])!=8) continue;
				if(fabs(goodTau[j].pt - sync_vec_l4Pt[s_s_i_TT[iSync]]) < 0.1 && fabs(goodTau[j].eta - sync_vec_l4Eta[s_s_i_TT[iSync]]) < 0.1){
					 std::cout << " matched sub leading tau (mass " << sync_vec_HMass[s_s_i_TT[iSync]] << ")" << std::endl;
					 s_match2_i=iSync;
					  match2=true;
					 matchedSync = true;
				 }
			}
			
			
			if(s_match_i >-1 && s_match2_i > -1){
				if(fabs(sync_vec_l4Pt[s_s_i_TT[s_match2_i]] - sync_vec_l4Pt[s_s_i_TT[s_match_i]]) > 0.1 || 
				fabs(sync_vec_l4Eta[s_s_i_TT[s_match2_i]] - sync_vec_l4Eta[s_s_i_TT[s_match_i]]) > 0.1){
					
					 std::cout << "matched wrong pair! (orig mass " << sync_vec_HMass[s_s_i_TT[s_match_i]] << ")" << std::endl;
					 h_fail_shape_TT->Fill(12.0);
				 }
			}
			
			if(goodTau[j].pt < Cut_tautau_Pt_2){
				 if(matchedSync)
				 {
					std::cout << "Failed subleading tau cut" << std::endl;
					h_fail_shape_TT->Fill(2.0);
				 }
				 continue;	
			 }
			if(examineThisEvent) std::cout << "  j passed pt cut" << j << " " << Cut_tautau_Pt_2 << std::endl;
			isFakeRate = (goodTau[i].charge*goodTau[j].charge  > 0);
			if(reverseFR) isFakeRate=!(isFakeRate);
			if(matchedSync && !isFakeRate){
				std::cout << "TT Failed sync charge cut" << std::endl;
				h_fail_shape_TT->Fill(3.0);
			}
			if(examineThisEvent && isFakeRate) std::cout << "Fake candidate!" << std::endl;
			bool verb=false;
			if(examineThisEvent) verb=true;
		//	if(!isFakeRate && (dZ1<maxDeltaR || dZ2 < maxDeltaR || deltaR(goodTau[j],Zcand[0]) < maxDeltaR || deltaR(goodTau[j],Zcand[1]) < maxDeltaR)) continue;
			if(!isFakeRate && CheckOverlapLooseElectron(goodTau[i], denomElectron, maxDeltaR, 0.3,verb)) continue;
			if(!isFakeRate && CheckOverlapLooseElectron(goodTau[j], denomElectron, maxDeltaR, 0.3,verb)) continue;
			if(!isFakeRate && CheckOverlapLooseMuon(goodTau[i], denomMuon, maxDeltaR, 0.3)) continue;
			if(!isFakeRate && CheckOverlapLooseMuon(goodTau[j], denomMuon, maxDeltaR, 0.3)) continue;
			
			
			//~ if(isFakeRate && tauTau){
				//~ if(matchedSync) {
					//~ std::cout << "too many pairs for FR" << std::endl;
					//~ h_fail_shape_TT->Fill(4.0);
				//~ }
				 //~ continue; // save only one pair
			 //~ }
			if(goodTau[j].discriminationByElectronLoose <= 0.5){
				if(matchedSync) {
					std::cout << "sub tau faild el ID" << std::endl;
					h_fail_shape_TT->Fill(5.0);
				}
				 continue;
			 }
		
			//if(goodTau[j].discriminationByElectronMedium <=0.5) continue;
			//if(goodTau[j].discriminationByMuonMedium <=0.5) continue;
			if(examineThisEvent) std::cout << "   j Passed pre-selection" << std::endl;
		
			if(deltaR(goodTau[j].eta,goodTau[j].phi,goodTau[i].eta,goodTau[i].phi)< maxDeltaR){
				if(matchedSync){
					std::cout << " shape cand failed delta R" << std::endl;
					h_fail_shape_TT->Fill(6.0);
				}
				 continue;
			 }
			if(examineThisEvent) std::cout << "   Passed selection" << std::endl;
			
			if(!DZ_expo(Zcand[0],Zcand[1],goodTau[i],goodTau[j], verb)){
				if(matchedSync){
					std::cout << " shape cand failed dZ cut" << std::endl;
					h_fail_shape_TT->Fill(7.0);
				}
				 continue; 			
			 }
			if(goodTau[i].pt > goodTau[j].pt){ 
				Hcand.push_back(goodTau[i]);
				Hcand.push_back(goodTau[j]);
			}else{
				Hcand.push_back(goodTau[j]);
				Hcand.push_back(goodTau[i]);
			}
			if(examineThisEvent) std::cout << "checking categories: " << category0 << category1 << category2 << std::endl;
			if(examineThisEvent) std::cout << "The isolation is " << goodTau[i].byLooseCombinedIsolationDeltaBetaCorr3Hits << goodTau[j].byLooseCombinedIsolationDeltaBetaCorr3Hits << std::endl;
			int index = Hcand.size() -2;
			bool pass1 = Hcand[index].byMediumCombinedIsolationDeltaBetaCorr3Hits > 0.5;
			bool pass2 = Hcand[index+1].byMediumCombinedIsolationDeltaBetaCorr3Hits > 0.5;
			bool shapePass1 = Hcand[index].byIsolationMVA2raw > tau_shape_iso_cut;
			bool shapePass2 = Hcand[index+1].byIsolationMVA2raw > tau_shape_iso_cut;			
			double pt1=Hcand[index].pt;
			double pt2=Hcand[index+1].pt;
			double sumPt = pt1+pt2;
			bool signalPtCuts = ( pt1 > Cut_tau_base_Pt && pt2 > Cut_tau_base_Pt);
			bool LTcut = UseSumPtCut && (sumPt > Cut_tautau_sumPt);
			bool LTcut_FR = UseSumPtCut && (sumPt > Cut_tautau_sumPt_FR);
			if(examineThisEvent) std::cout << "shape iso is " << Hcand[index].byIsolationMVA2raw << " " << Hcand[index+1].byIsolationMVA2raw << std::endl;
			if(!LTcut && !LTcut_FR){
				if(matchedSync){
					std::cout << " shape cand failed LT cut" << std::endl;
					h_fail_shape_TT->Fill(8.0);
				}
				 continue;
			 }
			signal = pass1 && pass2 && signalPtCuts && !isFakeRate && LTcut;
			bool Ad_lepton=false;
			if(!signal){
				if(AdLepton_tt(genericMuon,genericElectron,goodTau,goodTau[i],goodTau[j],verb)){
					if(examineThisEvent) std::cout << "   > j failed overlap check." << std::endl;				
					Ad_lepton=true;
				}
			}else{
				if(AdLepton_sig(genericMuon,genericElectron,goodTau,goodTau[i],goodTau[j],verb)){
					if(examineThisEvent) std::cout << "   > j failed overlap check." << std::endl;				
					Ad_lepton=true;
				}
			}
			if(Ad_lepton){
				if(matchedSync){
					std::cout << " shape cand failed lepton veto" << std::endl;
					h_fail_shape_TT->Fill(9.0);
				}
				 continue;
			 }
			if(isFakeRate) tauTau=true;
			if(signal) tauTau=true;
			if(!isFakeRate&&!signal&&LTcut&&signalPtCuts){
				if(!pass1 && !pass2 && !category0)
				{
					if(examineThisEvent) std::cout << " in category 0!" << std::endl;
					category0=true;
					Hcand_cat0.push_back(Hcand[index]);
					Hcand_cat0.push_back(Hcand[index+1]);
					usedTauIdx.push_back(index);
					if(Zmumu) Hcand_type_cat0.push_back(4);
					else if(Zee) Hcand_type_cat0.push_back(8);
				}
				if(pass1 && !pass2 && !category1)
				{
					if(examineThisEvent) std::cout << " in category 1!" << std::endl;
					category1=true;
					Hcand_cat1.push_back(Hcand[index]);
					Hcand_cat1.push_back(Hcand[index+1]);
					usedTauIdx.push_back(index);
					if(Zmumu) Hcand_type_cat1.push_back(4);
					else if(Zee) Hcand_type_cat1.push_back(8);
				}
				if(!pass1 && pass2 && !category2)
				{
					if(examineThisEvent) std::cout << " in category 2!" << std::endl;
					category2=true;
					Hcand_cat2.push_back(Hcand[index]);
					Hcand_cat2.push_back(Hcand[index+1]);
					usedTauIdx.push_back(index);
					if(Zmumu) Hcand_type_cat2.push_back(4);
					else if(Zee) Hcand_type_cat2.push_back(8);
				}
			}else if(isFakeRate){
				if(examineThisEvent){
					myobject ClosestJet = ClosestInCollection(Hcand[index],m->RecPFJetsAK5);
					myobject ClosestJet2 = ClosestInCollection(Hcand[index+1],m->RecPFJetsAK5);
					
					std::cout << "Saving denom fake candidates with pass = " << pass1 << " " << pass2 << 
					" and pts " << Hcand[index].pt << " " << Hcand[index+1].pt << " jet etas" << ClosestJet.eta << " " << ClosestJet2.eta << " M= " <<
					PairMass(Hcand[index],Hcand[index+1]) << std::endl;
				
				bool barrelMatch1 =true;
				bool barrelMatch2 =true;
				
				if(doSync && doSyncFR){
					barrelMatch1 = (fabs(ClosestJet.eta) < 1.4 && sync_vec_Channel[s_s_i_TT[s_match_i]] == 9) || (fabs(ClosestJet.eta) >= 1.4 && sync_vec_Channel[s_s_i_TT[s_match_i]] == 10);
					barrelMatch2 = (fabs(ClosestJet2.eta) < 1.4 && sync_vec_Channel[s_s_i_TT[s_match2_i]] == 9) || (fabs(ClosestJet2.eta) >= 1.4 && sync_vec_Channel[s_s_i_TT[s_match2_i]] == 10);
					if(!barrelMatch1){
						std::cout << "Lead tau failed barrel cut!" << std::endl;
						h_fail_shape_TT->Fill(13.0);
					}else{
						std::cout << "Lead tau passed barrel cut with type " << sync_vec_Channel[s_s_i_TT[s_match_i]] << " and eta " << ClosestJet.eta << "!" << std::endl;
					}
					if(!barrelMatch2){
						std::cout << "Sub tau failed barrel cut!" << std::endl;
						h_fail_shape_TT->Fill(14.0);
					}else{
						std::cout << "Sub tau passed barrel cut with type " << sync_vec_Channel[s_s_i_TT[s_match2_i]] << " and eta " << ClosestJet2.eta << "!" << std::endl;
					
					}
				}
			}
				Hcand_FR.push_back(Hcand[index]);
				Hcand_FR.push_back(Hcand[index+1]);
				
				int result = pass1? 1:0;
				int result2 = pass2? 1:0;
				bool usedEl = false;
				size_t el_helper = std::find(usedElId.begin(), usedElId.end(), i) - usedElId.begin();
				if(el_helper < usedElId.size()) usedEl=true;
				
				if(usedEl) result = -1;
				Hcand_pass.push_back(result);
				if(result > -1) usedElId.push_back(i);
				
				bool usedTau = false;
				size_t tau_helper = std::find(usedTauId.begin(), usedTauId.end(), i) - usedTauId.begin();
				if(tau_helper < usedTauId.size()) usedTau=true;
				
				if(usedTau ) result2=-1;
				Hcand_pass.push_back(result2);
				if(result2 > -1) usedTauId.push_back(j);
				if(shapePass1 && shapePass2 && LTcut && signalPtCuts){
					if(matchedSync){
						std::cout << "TT Shape cand accepted!" << std::endl;
					}
					 Hcand_shape_pass.push_back(1);
				}else{
					 if(matchedSync){
						std::cout << "TT shape cand failed shape cuts" << std::endl;
						h_fail_shape_TT->Fill(10.0);
					 }
					 Hcand_shape_pass.push_back(0);
				 }
				usedTauIdx.push_back(index);
				if(Zmumu) Hcand_type_FR.push_back(4);
				else if(Zee) Hcand_type_FR.push_back(8);
			}else if(signal && !saved_signal){
				if(examineThisEvent){
					std::cout << "Saving signal candidate with pts " << Hcand[index].pt << " " << Hcand[index+1].pt << " " << 
					PairMass(Hcand[index],Hcand[index+1]) << std::endl;
				}
				Hcand_signal.push_back(Hcand[index]);
				Hcand_signal.push_back(Hcand[index+1]);
				if(Zmumu) Hcand_type_signal.push_back(4);
				else if(Zee) Hcand_type_signal.push_back(8);
				saved_signal=true;
			}
			
			
			
			//~ if(Zmumu) Hcand_type.push_back(4);
			//~ else if(Zee) Hcand_type.push_back(8);
			
			m_logger << DEBUG << " hindex[0] " << i << SLogger::endmsg;
			m_logger << DEBUG << " hindex[1] " << j << SLogger::endmsg;

		}
		if(s_match_i > -1 && match2==false)
		{
			std::cout << "TT shape candidate not found" << std::endl;
			h_fail_shape_TT->Fill(11.0);
		}
	}
	
	if(examineThisEvent) std::cout << " After TT, there are " << Hcand_cat0.size() << " cat0 "<< Hcand_cat1.size() << " cat1 "<< Hcand_cat2.size() << " cat2 "<<
	 Hcand_FR.size() << " FR." <<   std::endl;
	category0 = false;
	category1= false;
	category2=false;     
	
	std::vector<int> s_s_i_MT; //sync_shape_index
    s_s_i_MT.clear();
	for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
	{
		if(sync_vec_subChannel[iSync]==0 && ((EventTypeConv(sync_vec_Channel[iSync]))%4) == 1) s_s_i_MT.push_back(iSync); // now checking cat0
	}
	
	usedElId.clear();
	usedTauId.clear();
	
	for(uint i = 0; i < genericMuon.size()  ; i++)
	{
	
		if(examineThisEvent) std::cout << " Looping over muon no.  " << i << std::endl;
		// finding the sync match
		int s_match_i = -1;
		for(uint iSync =0; iSync < s_s_i_MT.size(); iSync++)
		{
			std::cout << " Sync shape candidate #" << iSync << " type:" << EventTypeConv(sync_vec_Channel[s_s_i_MT[iSync]]) <<
			" l3 pt/eta:" << sync_vec_l3Pt[s_s_i_MT[iSync]] << "/" << sync_vec_l3Eta[s_s_i_MT[iSync]] <<
			" l4 pt/eta:" << sync_vec_l4Pt[s_s_i_MT[iSync]] << "/" << sync_vec_l4Eta[s_s_i_MT[iSync]] << std::endl;
			if(Zmumu && EventTypeConv(sync_vec_Channel[s_s_i_MT[iSync]])!=1) continue;
			if(Zee && EventTypeConv(sync_vec_Channel[s_s_i_MT[iSync]])!=5) continue;
			if(fabs(genericMuon[i].pt - sync_vec_l3Pt[s_s_i_MT[iSync]]) < 0.1 && fabs(genericMuon[i].eta - sync_vec_l3Eta[s_s_i_MT[iSync]]) < 0.1){
				 std::cout << " matched leading mu " << std::endl;
				 s_match_i=iSync;
			 }
		}
	
		m_logger << DEBUG << " Checking for muTau " << SLogger::endmsg;
		
		if(examineThisEvent) std::cout << " Checking mutau " << std::endl;
		if(examineThisEvent) std::cout << " Mu candidate i= " << i << " " << genericMuon[i].pt << " " << genericMuon[i].charge << std::endl;
		//if(!WZ_Rej(m,genericMuon[i])) continue;
		if(examineThisEvent) std::cout << " Passed pre-selection. Looping over " << goodTau.size() << " taus." << std::endl;	
		bool match2 = false;
		for(uint j=0; j< goodTau.size() && !(category0 && category1 && category2 && signal) ; j++)
		{
            bool matchedSync = false;
            if(s_match_i >-1){
				if(fabs(goodTau[j].pt - sync_vec_l4Pt[s_s_i_MT[s_match_i]]) < 0.1 && fabs(goodTau[j].eta - sync_vec_l4Eta[s_s_i_MT[s_match_i]]) < 0.1){
					 match2=true;
					 matchedSync=true;
					 std::cout << "matched sub Mtau (mass " << sync_vec_HMass[s_s_i_MT[s_match_i]] << ")" << std::endl;
				 }
			}       
			
			if(examineThisEvent) std::cout << "   > tau no. " << j << " " << goodTau[j].pt << " " << goodTau[j].charge << std::endl;
			if(examineThisEvent) std::cout << " H candidate mass is " << PairMass(goodTau[j],genericMuon[i]) << std::endl;
			bool isFakeRate = (genericMuon[i].charge*goodTau[j].charge  > 0);
			if(reverseFR) isFakeRate=!(isFakeRate);
			if(matchedSync && !isFakeRate){
				std::cout << "MT Failed sync charge cut" << std::endl;
				h_fail_shape_MT->Fill(0.0);
			}
			
			if(examineThisEvent && isFakeRate) std::cout << "Fake candidate!" << std::endl;
			bool verb=false;
			if(examineThisEvent) verb=true;
			
		
			if(!isFakeRate && CheckOverlapLooseElectron(goodTau[j], denomElectron, maxDeltaR, 0.3, verb)){
				if(matchedSync){
					std::cout << "MT failed overlap check loose electron" << std::endl;
					h_fail_shape_MT->Fill(11.0);
				}
				 continue;
			 }
			if(!isFakeRate && CheckOverlapLooseMuon(goodTau[j], denomMuon, maxDeltaR, 0.3)){
				 if(matchedSync){
					std::cout << "MT failed overlap check loose muon" << std::endl;
					h_fail_shape_MT->Fill(12.0);
				}
				 continue;
			 }
			
			if(examineThisEvent) std::cout << "There are " << genericMuon.size() << " muons." << std::endl;
			
			if(!isFakeRate && goodTau[j].pt < Cut_tautau_Pt_2){
				if(matchedSync){
					std::cout << "MT tau failed pt" << std::endl;
					h_fail_shape_MT->Fill(13.0);
				}
				 continue;	
			}
			if(isFakeRate && goodTau[j].pt < Cut_leptau_Pt){
				 if(matchedSync)
				 {
					std::cout << "Failed subleading Mtau cut" << std::endl;
					h_fail_shape_MT->Fill(1.0);
				 }	
				 continue;	
			 }
			if(examineThisEvent) std::cout << "Passed pt cut" << std::endl;
			if(examineThisEvent) std::cout << "Passed WZ rejection" << std::endl;
			//~ if(isFakeRate && muTau){ 
				//~ if(matchedSync)
				 //~ {
					//~ std::cout << "only one pair" << std::endl;
					//~ h_fail_shape_MT->Fill(2.0);
				 //~ }
				//~ continue; // save only one pair
			//~ }
			if(examineThisEvent) std::cout << "Passed uniqueness cut" << std::endl;
	
				
			if(goodTau[j].discriminationByMuonTight2 <=0.5){
				 if(matchedSync)
				 {
					std::cout << "Failed tau mu ID" << std::endl;
					h_fail_shape_MT->Fill(3.0);
				 }
				 continue;
			 }
			if(goodTau[j].discriminationByElectronLoose <= 0.5){
				 if(matchedSync)
				 {
					std::cout << "Failed tau el ID" << std::endl;
					h_fail_shape_MT->Fill(4.0);
				 }
				 continue;
			 }
		
			if(deltaR(goodTau[j].eta,goodTau[j].phi,genericMuon[i].eta,genericMuon[i].phi)< maxDeltaR){
				 if(matchedSync)
				 {
					std::cout << "Failed dR" << std::endl;
					h_fail_shape_MT->Fill(5.0);
				 }
				 continue;  
			 }
			if(examineThisEvent) std::cout << " j distance is " << deltaR(goodTau[j].eta,goodTau[j].phi,genericMuon[i].eta,genericMuon[i].phi) << std::endl;            
			if(examineThisEvent) std::cout << " j passed pre-selection " << std::endl;
			
			if(!DZ_expo(Zcand[0],Zcand[1],genericMuon[i],goodTau[j], verb)){
				 if(matchedSync)
				 {
					std::cout << "Failed dZ" << std::endl;
					h_fail_shape_MT->Fill(6.0);
				 }
				 continue;
			 }
			if(examineThisEvent) std::cout << "PASSED!" << std::endl;
			Hcand.push_back(genericMuon[i]);
			Hcand.push_back(goodTau[j]);
			int index = Hcand.size() -2;
			bool pass2 = (RelIso(Hcand[index])<relIso_MT && isLooseMu(Hcand[index]));
			bool pass1 = Hcand[index+1].byLooseCombinedIsolationDeltaBetaCorr3Hits >0.5;
			bool shapePass2 = RelIso(Hcand[index])< lep_shape_iso_cut;// && isLooseMu(Hcand[index]));
			bool shapePass1 = Hcand[index+1].byIsolationMVA2raw > tau_shape_iso_cut;
			
			double pt1=Hcand[index].pt;
			double pt2=Hcand[index+1].pt;
			double sumPt = pt1+pt2;
			bool tightFR=isGoodMu(Hcand[index]);
			bool signalCuts = ( pt2 > Cut_tau_base_Pt && tightFR);
			bool LTcut = UseSumPtCut && (sumPt > Cut_mutau_sumPt);
			bool LTcut_FR = UseSumPtCut && (sumPt > Cut_mutau_sumPt_FR);
			if(!LTcut && !LTcut_FR){
				 if(matchedSync)
				 {
					std::cout << "Failed LT" << std::endl;
					h_fail_shape_MT->Fill(7.0);
				 }
				 continue;
			 }
			
			signal = pass1 && pass2 && signalCuts && !isFakeRate && LTcut;
			bool Ad_lepton=false;
			if(!signal){
				if(AdLepton_mt(m,i,genericMuon,genericElectron,goodTau,genericMuon[i],goodTau[j],verb)){
					if(examineThisEvent) std::cout << "   > j failed overlap check." << std::endl;				
					Ad_lepton=true;
				}
			}else{
				if(AdLepton_sig(genericMuon,genericElectron,goodTau,genericMuon[i],goodTau[j],verb)){
					if(examineThisEvent) std::cout << "   > j failed overlap check." << std::endl;				
					Ad_lepton=true;
				}
			}
			if(Ad_lepton){
				 if(matchedSync)
				 {
					std::cout << "Failed lep veto" << std::endl;
					h_fail_shape_MT->Fill(8.0);
				 }
				 continue;
			 }
			if(isFakeRate) muTau=true;
			if(signal && !saved_signal ) muTau=true;
			
			if(examineThisEvent) std::cout << "checking categories: " << category0 << category1 << category2 << std::endl;
			if(examineThisEvent) std::cout << "The isolation is " << pass2 << pass1 << shapePass1 << shapePass2 << std::endl;
			
			if(!isFakeRate && !signal && LTcut && pt2>Cut_tau_base_Pt){
				if(matchedSync){
					std::cout << "MT is category candidate!" << std::endl;
					std::cout << pass1 << pass2 << tightFR << category0 << category1 << category2 << std::endl;
				}
				if( !pass1 && (!pass2||!tightFR) && !category0 )
				{
					if(examineThisEvent) std::cout << " in category 0!" << std::endl;
					category0=true;
					Hcand_cat0.push_back(Hcand[index]);
					Hcand_cat0.push_back(Hcand[index+1]);
					if(Zmumu) Hcand_type_cat0.push_back(1);
					else if(Zee) Hcand_type_cat0.push_back(5);
				}else{
					if(matchedSync){
					std::cout << "MT failed cat0" << std::endl;
					h_fail_shape_MT->Fill(15.0);
				}
				}
				if(!pass1 && pass2 && !category1 && tightFR)
				{	
				
					if(examineThisEvent) std::cout << " in category 1!" << std::endl;
					category1=true;
					Hcand_cat1.push_back(Hcand[index]);
					Hcand_cat1.push_back(Hcand[index+1]);
					if(Zmumu) Hcand_type_cat1.push_back(1);
					else if(Zee) Hcand_type_cat1.push_back(5);
				}
				if(pass1 && (!pass2||!tightFR) && !category2 )
				{
					if(examineThisEvent) std::cout << " in category 2!" << std::endl;
					category2=true;
					Hcand_cat2.push_back(Hcand[index]);
					Hcand_cat2.push_back(Hcand[index+1]);
					if(Zmumu) Hcand_type_cat2.push_back(1);
					else if(Zee) Hcand_type_cat2.push_back(5);
				}
			}else if(isFakeRate){
				if(examineThisEvent){
					myobject ClosestJet = ClosestInCollection(Hcand[index+1],m->RecPFJetsAK5);
					std::cout << "Saving denom fake candidates with pass = " << pass1 << " " << pass2 << 
					" and pts " << Hcand[index].pt << " " << Hcand[index+1].pt << " " << ClosestJet.pt << " " << 
					PairMass(Hcand[index],Hcand[index+1]) << std::endl;
				}
				Hcand_FR.push_back(Hcand[index]);
				Hcand_FR.push_back(Hcand[index+1]);
				int result = pass2? 1:0;
				int result2 = pass1? 1:0;
				int tight = tightFR? 1:0;
				if(pass2) result+=tightFR;
				
				bool usedEl = false;
				size_t el_helper = std::find(usedElId.begin(), usedElId.end(), i) - usedElId.begin();
				if(el_helper < usedElId.size()) usedEl=true;
				
				if(!WZ_Rej(m,Hcand[index]) || usedEl) result = -1;
				Hcand_pass.push_back(result);
				if(result > -1) usedElId.push_back(i);
				
				bool usedTau = false;
				size_t tau_helper = std::find(usedTauId.begin(), usedTauId.end(), i) - usedTauId.begin();
				if(tau_helper < usedTauId.size()) usedTau=true;
				
				bool LTptcut=Hcand[index+1].pt > Cut_tautau_Pt_2;
				if(!LTptcut || usedTau ) result2=-1;
		
				Hcand_pass.push_back(result2);
				if(result2 > -1) usedTauId.push_back(j);
				
				if(matchedSync){
					std::cout << "MT:WZ rej: " << WZ_Rej(m,Hcand[index]) << " LTptcut: " << LTptcut << " pt:" 
					<< Hcand[index+1].pt << " LT:" << sumPt << "usedLep" << usedEl << usedTau << std::endl;
				}
				
				if(shapePass1 && shapePass2 && LTptcut && LTcut){
					if(matchedSync){
						std::cout << "MT Shape cand accepted!" << std::endl;
					}
					if(tightFR) Hcand_shape_pass.push_back(2);
					else Hcand_shape_pass.push_back(1);
				}else{
					 if(matchedSync)
					{
						std::cout << "MT Failed shape cut" << std::endl;
						h_fail_shape_MT->Fill(9.0);
					}
					 Hcand_shape_pass.push_back(0);
				 }
				if(Zmumu) Hcand_type_FR.push_back(1);
				else if(Zee) Hcand_type_FR.push_back(5);
			}else if(signal && !saved_signal){
				if(examineThisEvent){
					std::cout << "Saving signal candidate with pts " << Hcand[index].pt << " " << Hcand[index+1].pt << " " << 
					PairMass(Hcand[index],Hcand[index+1]) << std::endl;
				}
				Hcand_signal.push_back(Hcand[index]);
				Hcand_signal.push_back(Hcand[index+1]);
				if(Zmumu) Hcand_type_signal.push_back(1);
				else if(Zee) Hcand_type_signal.push_back(5);
				saved_signal=true;
			}else{
				if(matchedSync){
					std::cout << "MT is not in any category" << std::endl;
					h_fail_shape_MT->Fill(14.0);
				}
			}
			
		
			
		}
		if(s_match_i > -1 && match2==false)
		{
			std::cout << " shape candidate not found" << std::endl;
			h_fail_shape_MT->Fill(10.0);
		}             
	}
	

	
	bool eTau = false;
   if(examineThisEvent) std::cout << " After MT, there are " << Hcand_cat0.size() << " cat0 "<< Hcand_cat1.size() << " cat1 "<< Hcand_cat2.size() << " cat2 "<<
	 Hcand_FR.size() << " FR." <<   std::endl;
		
	if(examineThisEvent) std::cout << " There are " << genericElectron.size() << " ele candidates " << std::endl;
	category0 = false;
	category1= false;
	category2=false;   
	
	std::vector<int> s_s_i_ET; //sync_shape_index
    s_s_i_ET.clear();
	for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
	{
		if(sync_vec_subChannel[iSync]==4 && ((EventTypeConv(sync_vec_Channel[iSync]))%4) == 3) s_s_i_ET.push_back(iSync);
	}  
	
	usedElId.clear();
	usedTauId.clear();
	for(uint i = 0; i < genericElectron.size()  ; i++)
	{
		if(examineThisEvent) std::cout << " electron no. "<< i << " " << genericElectron[i].pt << " " << genericElectron[i].charge << std::endl;
		// finding the sync match
		int s_match_i = -1;
		for(uint iSync =0; iSync < s_s_i_ET.size(); iSync++)
		{
			std::cout << " Sync shape candidate #" << iSync << " type:" << EventTypeConv(sync_vec_Channel[s_s_i_ET[iSync]]) <<
			" l3 pt/eta:" << sync_vec_l3Pt[s_s_i_ET[iSync]] << "/" << sync_vec_l3Eta[s_s_i_ET[iSync]] <<
			" l4 pt/eta:" << sync_vec_l4Pt[s_s_i_ET[iSync]] << "/" << sync_vec_l4Eta[s_s_i_ET[iSync]] << std::endl;
			if(Zmumu && EventTypeConv(sync_vec_Channel[s_s_i_ET[iSync]])!=3) continue;
			if(Zee && EventTypeConv(sync_vec_Channel[s_s_i_ET[iSync]])!=7) continue;
			if(fabs(genericElectron[i].pt - sync_vec_l3Pt[s_s_i_ET[iSync]]) < 0.1 && fabs(genericElectron[i].eta - sync_vec_l3Eta[s_s_i_ET[iSync]]) < 0.1){
				 std::cout << "ET matched leading ele" << std::endl;
				 s_match_i=iSync;
			 }
		}
		
		if(genericElectron[i].numLostHitEleInner > 1){
			 if(s_match_i > -1){
				std::cout << " ET Failed lost hits cut: " << genericElectron[i].numLostHitEleInner << std::endl;
				h_fail_shape_ET->Fill(0.0);
			}
			 continue;
		 }
		if(examineThisEvent) std::cout << " Checking for eTau " << std::endl;
	
		if(examineThisEvent) std::cout << " i passed pre-selection. Looping over " << goodTau.size() << " taus." << std::endl;
		bool match2 = false;
		for(uint j=0; j< goodTau.size() &&!(category0 && category1 && category2 &&signal)  ; j++)
		{
			bool matchedSync = false;
			if(s_match_i >-1){
				if(fabs(goodTau[j].pt - sync_vec_l4Pt[s_s_i_ET[s_match_i]]) < 0.1 && fabs(goodTau[j].eta - sync_vec_l4Eta[s_s_i_ET[s_match_i]]) < 0.1){
					 match2=true;
					 matchedSync=true;
					 std::cout << "matched sub Etau (mass " << sync_vec_HMass[s_s_i_ET[s_match_i]] << ")" << std::endl;
				 }
			}
			if(examineThisEvent) std::cout << "   > tau no. " << j << " " << goodTau[j].pt << " " << goodTau[j].charge << std::endl;
			if(examineThisEvent) std::cout << " H candidate mass is " << PairMass(goodTau[j],genericElectron[i]) << std::endl;
			bool isFakeRate = (genericElectron[i].charge*goodTau[j].charge  > 0);
			if(reverseFR) isFakeRate=!(isFakeRate);
			if(examineThisEvent && isFakeRate) std::cout << "Fake candidate!" << std::endl;
			if(matchedSync && !isFakeRate){
				std::cout << " ET Failed sync charge cut" << std::endl;
				h_fail_shape_ET->Fill(1.0);
			}
			
			bool verb=false;
			if(examineThisEvent) verb=true;
	
			if(!isFakeRate && CheckOverlapLooseElectron(goodTau[j], denomElectron, maxDeltaR, 0.3, verb)){
				if(matchedSync){
					std::cout << "ET failed overlap check loose electron" << std::endl;
					h_fail_shape_ET->Fill(11.0);
				}
				 continue;
			 }
			if(!isFakeRate && CheckOverlapLooseMuon(goodTau[j], denomMuon, maxDeltaR, 0.3)){
				if(matchedSync){
					std::cout << "ET failed overlap check loose muon" << std::endl;
					h_fail_shape_ET->Fill(12.0);
				}
				 continue;
			 }
		
			if(examineThisEvent) std::cout << "There are " << genericElectron.size() << " electrons	." << std::endl;
		
			
			if(!isFakeRate && goodTau[j].pt < Cut_tautau_Pt_2){
				if(matchedSync){
					std::cout << "ET failed overlap check loose electron" << std::endl;
					h_fail_shape_ET->Fill(13.0);
				}
				 continue;	
			 }
			if(isFakeRate && goodTau[j].pt < Cut_leptau_Pt){
				 if(matchedSync)
				 {
					std::cout << "ET Failed subleading Etau cut" << std::endl;
					h_fail_shape_ET->Fill(2.0);
				 }	
				 continue;	
			 }
		//	if(isFakeRate && !WZ_Rej(m,genericElectron[i])) continue;
			if(examineThisEvent) std::cout << "Passed Pt cuts and WZ rej" << std::endl;	
			//~ if(isFakeRate && eTau){
				 //~ if(matchedSync)
				 //~ {
					//~ std::cout << "One pair only" << std::endl;
					//~ h_fail_shape_ET->Fill(3.0);
				 //~ }	
				 //~ continue; // save only one pair	
			 //~ }
			if(examineThisEvent) std::cout << "The event has not been used for application so far" << std::endl;
			
			if(goodTau[j].discriminationByElectronMVA3Tight <=0.5){
				 if(matchedSync)
				 {
					std::cout << "ET failed tau ele ID" << std::endl;
					h_fail_shape_ET->Fill(4.0);
				 }
				 continue;
			 }
			
		
			if(deltaR(goodTau[j].eta,goodTau[j].phi,genericElectron[i].eta,genericElectron[i].phi)< maxDeltaR){
				 if(matchedSync)
				 {
					std::cout << "ET failed dR" << std::endl;
					h_fail_shape_ET->Fill(5.0);
				 }
				 continue;
			 }
			if(examineThisEvent) std::cout << " j distance is " << deltaR(goodTau[j].eta,goodTau[j].phi,genericElectron[i].eta,genericElectron[i].phi) << std::endl;            
			if(examineThisEvent) std::cout << "   > j passed pre-selection." << std::endl;
			if(examineThisEvent) std::cout << "   > candidate passed WZ rejection" << std::endl;
			
			
			if(examineThisEvent) verb=true;
			if(!DZ_expo(Zcand[0],Zcand[1],genericElectron[i],goodTau[j], verb)){
				 if(matchedSync)
				 {
					std::cout << "ET Failed dZ" << std::endl;
					h_fail_shape_ET->Fill(6.0);
				 }
				 continue;
			 }
			double jetDist = DistanceToClosestInCollection(genericElectron[i],m->RecPFJetsAK5);
			myobject ClosestJet = ClosestInCollection(genericElectron[i],m->RecPFJetsAK5);
			if(examineThisEvent) std::cout << "The closest jet distance is " << jetDist << " " << ClosestJet.pt << std::endl;
			if(examineThisEvent) std::cout << "tau MVA3VTight, eta,Loose:" << goodTau[j].discriminationByElectronMVA3VTight << " " << goodTau[j].eta << " " << goodTau[j].discriminationByElectronLoose << std::endl;
			if(examineThisEvent) std::cout << "PASSED!" << std::endl;
			Hcand.push_back(genericElectron[i]);
			Hcand.push_back(goodTau[j]);
			int index = Hcand.size() -2;
			
					
			bool pass2 = (RelIso(Hcand[index])<relIso_ET && LooseEleId(Hcand[index]));
			bool pass1 = Hcand[index+1].byLooseCombinedIsolationDeltaBetaCorr3Hits >0.5;
			bool shapePass2 = RelIso(Hcand[index])< lep_shape_iso_cut;// && LooseEleId(Hcand[index]));
			bool shapePass1 = Hcand[index+1].byIsolationMVA2raw > tau_shape_iso_cut;
			
			
			double pt1=Hcand[index].pt;
			double pt2=Hcand[index+1].pt;
			double sumPt = pt1+pt2;
			bool tightFR=TightEleId(Hcand[index]);
			bool signalCuts = ( pt2 > Cut_tau_base_Pt && tightFR);
			bool LTcut = UseSumPtCut && (sumPt > Cut_etau_sumPt);
			bool LTcut_FR = UseSumPtCut && (sumPt > Cut_etau_sumPt_FR);
			
			if(!LTcut && !LTcut_FR){
				 if(matchedSync)
				 {
					std::cout << "ET Failed LT" << std::endl;
					h_fail_shape_ET->Fill(7.0);
				 }
				 continue;
			 }
			signal = pass1 && pass2 && signalCuts && !isFakeRate && LTcut;
			bool Ad_lepton=false;
			if(!signal){
				if(AdLepton_et(m,i,genericMuon,genericElectron,goodTau,genericElectron[i],goodTau[j],verb)){
					if(examineThisEvent) std::cout << "   > j failed overlap check." << std::endl;				
					Ad_lepton=true;
				}
			}else{
				if(AdLepton_sig(genericMuon,genericElectron,goodTau,genericElectron[i],goodTau[j],verb)){
					if(examineThisEvent) std::cout << "   > j failed overlap check." << std::endl;				
					Ad_lepton=true;
				}
			}
			if(Ad_lepton){
				 if(matchedSync)
				 {
					std::cout << "ET Failed lepton veto" << std::endl;
					h_fail_shape_ET->Fill(8.0);
				 }
				 continue;
			 }
		//	if(isFakeRate) eTau=true;
			if(signal && !saved_signal ) eTau=true;
			
			if(examineThisEvent) std::cout << "checking categories: " << category0 << category1 << category2 << std::endl;
			if(examineThisEvent) std::cout << "The isolation is " << pass1 << pass2 << shapePass1 << shapePass2 << std::endl;
			
			if(!isFakeRate && !signal &&LTcut && pt2>Cut_tau_base_Pt){
				if( !pass1 && (!pass2||!tightFR) && !category0 )
				{
					if(examineThisEvent) std::cout << "In category0" << std::endl;
					category0=true;
					Hcand_cat0.push_back(Hcand[index]);
					Hcand_cat0.push_back(Hcand[index+1]);
					if(Zmumu) Hcand_type_cat0.push_back(3);
					else if(Zee) Hcand_type_cat0.push_back(7);
				}else if(matchedSync){
					std::cout << "ET failed cat0" << std::endl;
					std::cout << pass1 << pass2 << tightFR << category0 << category1 << category2 << std::endl;
					h_fail_shape_ET->Fill(15.0);
				}
				if(!pass1 && pass2 && !category1 && tightFR)
				{
					if(examineThisEvent) std::cout << "In category1" << std::endl;
					category1=true;
					Hcand_cat1.push_back(Hcand[index]);
					Hcand_cat1.push_back(Hcand[index+1]);
					if(Zmumu) Hcand_type_cat1.push_back(3);
					else if(Zee) Hcand_type_cat1.push_back(7);
				}
				if(pass1 && (!pass2||!tightFR) && !category2 )
				{
					if(examineThisEvent) std::cout << "in category2" << std::endl;
					category2=true;
					Hcand_cat2.push_back(Hcand[index]);
					Hcand_cat2.push_back(Hcand[index+1]);
					if(Zmumu) Hcand_type_cat2.push_back(3);
					else if(Zee) Hcand_type_cat2.push_back(7);
				}
			}else if(isFakeRate){
				if(examineThisEvent){
					myobject ClosestJet = ClosestInCollection(Hcand[index+1],m->RecPFJetsAK5);
					std::cout << "Saving denom fake candidates with pass = " << pass1 << " " << pass2 << 
					" and pts " << Hcand[index].pt << " " << Hcand[index+1].pt << " " << ClosestJet.pt << " " << 
					PairMass(Hcand[index],Hcand[index+1]) << std::endl;
				}
				Hcand_FR.push_back(Hcand[index]);
				Hcand_FR.push_back(Hcand[index+1]);
				int result = pass2? 1:0;
				int result2 = pass1? 1:0;
				int tight = tightFR? 1:0;
				if(pass2) result+=tightFR;
				
				bool usedEl = false;
				size_t el_helper = std::find(usedElId.begin(), usedElId.end(), i) - usedElId.begin();
				if(el_helper < usedElId.size()) usedEl=true;
				
				if(!WZ_Rej(m,Hcand[index]) || usedEl) result = -1;
				Hcand_pass.push_back(result);
				if(result > -1) usedElId.push_back(i);
				
				bool usedTau = false;
				size_t tau_helper = std::find(usedTauId.begin(), usedTauId.end(), i) - usedTauId.begin();
				if(tau_helper < usedTauId.size()) usedTau=true;
				
				bool LTptcut=Hcand[index+1].pt > Cut_tautau_Pt_2;
				if(!LTptcut || usedTau ) result2=-1;
				Hcand_pass.push_back(result2);
				if(result2 > -1) usedTauId.push_back(j);
				if(matchedSync){
					std::cout << "ET:WZ rej: " << WZ_Rej(m,Hcand[index]) << " LTptcut: " << LTptcut << " pt:" 
					<< Hcand[index+1].pt << " LT:" << sumPt << "usedLep" << usedEl << usedTau << std::endl;
				}
				if(shapePass1 && shapePass2 && LTptcut && LTcut){
					if(matchedSync){
						std::cout << " ET Shape cand accepted!" << std::endl;
					}
					if(tightFR) Hcand_shape_pass.push_back(2);
					else Hcand_shape_pass.push_back(1);
				}else{
					if(matchedSync)
					{
						std::cout << " ET Shape failed" << std::endl;
						h_fail_shape_ET->Fill(9.0);
					}
					Hcand_shape_pass.push_back(0);	
				 }
				if(Zmumu) Hcand_type_FR.push_back(3);
				else if(Zee) Hcand_type_FR.push_back(7);
			}else if(signal && !saved_signal){
				if(examineThisEvent){
					std::cout << "Saving signal candidate with pts " << Hcand[index].pt << " " << Hcand[index+1].pt << " " << 
					PairMass(Hcand[index],Hcand[index+1]) << std::endl;
				}
				Hcand_signal.push_back(Hcand[index]);
				Hcand_signal.push_back(Hcand[index+1]);
				if(Zmumu) Hcand_type_signal.push_back(3);
				else if(Zee) Hcand_type_signal.push_back(7);
				saved_signal=true;
			}else if(matchedSync){
					std::cout << "ET matched no category" << std::endl;
					h_fail_shape_ET->Fill(14.0);
				}
		
		
		}
		if(s_match_i > -1 && match2==false)
		{
			std::cout << " ET shape candidate not found" << std::endl;
			h_fail_shape_ET->Fill(10.0);
		}       
	}
	if(examineThisEvent) std::cout << " After ET, there are " << Hcand_cat0.size() << " cat0 "<< Hcand_cat1.size() << " cat1 "<< Hcand_cat2.size() << " cat2 "<<
	 Hcand_FR.size() << " FR." <<   std::endl;
	
	
	//emu final state
	bool eMu=false;
	category0 = false;
	category1= false;
	category2=false;     
	
	std::vector<int> s_s_i_EM; //sync_shape_index
    s_s_i_EM.clear();
	for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
	{
		if(sync_vec_subChannel[iSync]==4 && ((EventTypeConv(sync_vec_Channel[iSync]))%4) == 2) s_s_i_EM.push_back(iSync);
	}  
	
	
	for(uint i = 0; i < genericElectron.size() ; i++)
	{
		if(examineThisEvent) std::cout << " electron no. "<< i << "/" << genericElectron.size() << " " << genericElectron[i].pt << " " << genericElectron[i].charge << std::endl;
			// finding the sync match
		int s_match_i = -1;
		for(uint iSync =0; iSync < s_s_i_EM.size(); iSync++)
		{
			std::cout << " Sync shape candidate #" << iSync << " type:" << EventTypeConv(sync_vec_Channel[s_s_i_EM[iSync]]) <<
			" l3 pt/eta:" << sync_vec_l3Pt[s_s_i_EM[iSync]] << "/" << sync_vec_l3Eta[s_s_i_EM[iSync]] <<
			" l4 pt/eta:" << sync_vec_l4Pt[s_s_i_EM[iSync]] << "/" << sync_vec_l4Eta[s_s_i_EM[iSync]] << std::endl;
			if(Zmumu && EventTypeConv(sync_vec_Channel[s_s_i_EM[iSync]])!=2) continue;
			if(Zee && EventTypeConv(sync_vec_Channel[s_s_i_EM[iSync]])!=6) continue;
			if(Zee){
				if(fabs(genericElectron[i].pt - sync_vec_l3Pt[s_s_i_EM[iSync]]) < 0.1 && fabs(genericElectron[i].eta - sync_vec_l3Eta[s_s_i_EM[iSync]]) < 0.1){
					 std::cout << " matched leading ele" << std::endl;
					 s_match_i=iSync;
				 }
			}else{
				if(fabs(genericElectron[i].pt - sync_vec_l4Pt[s_s_i_EM[iSync]]) < 0.1 && fabs(genericElectron[i].eta - sync_vec_l4Eta[s_s_i_EM[iSync]]) < 0.1){
					 std::cout << " matched leading ele" << std::endl;
					 s_match_i=iSync;
				 }
			}
		}
		
		//~ if(genericElectron[i].numLostHitEleInner > 1){
			  //~ if(s_match_i > -1){
				//~ std::cout << "Failed lost hits cut: " << genericElectron[i].numLostHitEleInner << std::endl;
				//~ h_fail_shape_EM->Fill(0.0);
			  //~ }
			 //~ continue;
		 //~ }
		if(examineThisEvent) std::cout << " Checking for eMu " << std::endl;
		
		if(examineThisEvent) std::cout << " i passed pre-selection. Looping over " << genericMuon.size() << " muons." << std::endl;
		bool match2=false;
		for(uint j=0; j< genericMuon.size() && !(category0 && category1 && category2 && signal) ; j++)
		{
			bool matchedSync = false;
			if(s_match_i >-1){
				if(Zee){
					if(fabs(genericMuon[j].pt - sync_vec_l4Pt[s_s_i_EM[s_match_i]]) < 0.1 && fabs(genericMuon[j].eta - sync_vec_l4Eta[s_s_i_EM[s_match_i]]) < 0.1){
						 match2=true;
						 matchedSync=true;
						 std::cout << "matched sub mu (mass " << sync_vec_HMass[s_s_i_EM[s_match_i]] << ")" << std::endl;
					 }
				}else{
					if(fabs(genericMuon[j].pt - sync_vec_l3Pt[s_s_i_EM[s_match_i]]) < 0.1 && fabs(genericMuon[j].eta - sync_vec_l3Eta[s_s_i_EM[s_match_i]]) < 0.1){
						 match2=true;
						 matchedSync=true;
						 std::cout << "matched sub mu (mass " << sync_vec_HMass[s_s_i_EM[s_match_i]] << ")" << std::endl;
					 }
				}
			}
			if(examineThisEvent) std::cout << "   > muon no. " << j << "/" << genericMuon.size() << " " << genericMuon[j].pt << " " << genericMuon[j].charge << std::endl;
			if(examineThisEvent) std::cout << " H candidate mass is " << PairMass(genericElectron[i],genericMuon[j]) << std::endl;
			bool isFakeRate = (genericElectron[i].charge*genericMuon[j].charge > 0);
			if(reverseFR) isFakeRate=!(isFakeRate);
			if(matchedSync && !isFakeRate){
				std::cout << "EM Failed sync charge cut" << std::endl;
				h_fail_shape_EM->Fill(1.0);
			}
			if(examineThisEvent && isFakeRate) std::cout << "Fake candidate!" << std::endl;
			
			if(deltaR(genericMuon[j],genericElectron[i])< maxDeltaR){
				  if(matchedSync)
				 {
					std::cout << "failed dR" << std::endl;
					h_fail_shape_EM->Fill(2.0);
				 }
				 continue;
			 }
			if(examineThisEvent) std::cout << " j distance is " << deltaR(genericMuon[j],genericElectron[i]) << std::endl;            
			if(examineThisEvent) std::cout << "   > j passed pre-selection." << std::endl;
			
			bool verb = false;
			if(examineThisEvent) verb = true;
		
			
			if(!DZ_expo(Zcand[0],Zcand[1],genericElectron[i],genericMuon[j], verb)){
				  if(matchedSync)
				 {
					std::cout << "failed dz" << std::endl;
					h_fail_shape_EM->Fill(3.0);
				 }
				 continue;
			 }
			if(examineThisEvent) std::cout << "PASSED!" << std::endl;
			Hcand.push_back(genericElectron[i]);
			Hcand.push_back(genericMuon[j]);
			int index = Hcand.size() -2;
			
			bool pass1 = (RelIso(Hcand[index])<relIso_EM && LooseEleId(Hcand[index])) && genericElectron[i].numLostHitEleInner < 2;
			bool pass2 = (RelIso(Hcand[index+1])<relIso_EM && isLooseMu(Hcand[index+1]));
			if(examineThisEvent) std::cout << "the values of isolations are" << RelIso(genericElectron[i]) << " " << RelIso(genericMuon[j]) << std::endl;
			if(examineThisEvent) std::cout << "the ID values are" << LooseEleId(genericElectron[i]) << " " << isLooseMu(genericMuon[j]) << std::endl;
			bool shapePass1 = RelIso(Hcand[index])< lep_shape_iso_cut;// && LooseEleId(Hcand[index]));
			bool shapePass2 = RelIso(Hcand[index+1])< lep_shape_iso_cut;// && isLooseMu(Hcand[index+1]));
			
			
		    if(examineThisEvent) std::cout << "checking categories: " << category0 << category1 << category2 << std::endl;
			if(examineThisEvent) std::cout << "The isolation is " << pass1 << pass2 << shapePass1 << shapePass2 << std::endl;
			
			double pt1=Hcand[index].pt;
			double pt2=Hcand[index+1].pt;
			double sumPt = pt1+pt2;
			if(examineThisEvent) std::cout << "Sum Pt is" << std::endl;
			bool LTcut = UseSumPtCut && (sumPt > Cut_leplep_sumPt);
			bool LTcut_FR = UseSumPtCut && (sumPt > Cut_leplep_sumPt_FR);
			if(!LTcut && !LTcut_FR){
				  if(matchedSync)
				 {
					std::cout << "failed LT" << std::endl;
					h_fail_shape_EM->Fill(4.0);
				 }
				 continue;
			 }
			signal = pass1 && pass2 && LTcut && !isFakeRate;
			bool Ad_lepton=false;
			if(signal){
				if(AdLepton_sig(genericMuon,genericElectron,goodTau,genericElectron[i],genericMuon[j],verb)){
					if(examineThisEvent) std::cout << "   > j failed overlap check." << std::endl;				
					Ad_lepton=true;
				}
			}
			if(Ad_lepton){
				  if(matchedSync)
				 {
					std::cout << "failed lepton veto" << std::endl;
					h_fail_shape_EM->Fill(5.0);
				 }
				 continue;
			 }
			if(signal && !saved_signal ) eMu=true;
			
			if(!signal && !isFakeRate &&LTcut){
				if( !pass1 && !pass2 && !category0)
				{
					if(examineThisEvent) std::cout << "In category0" << std::endl;
					category0=true;
					Hcand_cat0.push_back(Hcand[index]);
					Hcand_cat0.push_back(Hcand[index+1]);
					if(Zmumu) Hcand_type_cat0.push_back(2);
					else if(Zee) Hcand_type_cat0.push_back(6);
				}
				if(pass1 && !pass2 && !category1)
				{
					if(examineThisEvent) std::cout << "In category1" << std::endl;
					category1=true;
					Hcand_cat1.push_back(Hcand[index]);
					Hcand_cat1.push_back(Hcand[index+1]);
					if(Zmumu) Hcand_type_cat1.push_back(2);
					else if(Zee) Hcand_type_cat1.push_back(6);
				}
				if(!pass1 && pass2 && !category2)
				{
					if(examineThisEvent) std::cout << "in category2" << std::endl;
					category2=true;
					Hcand_cat2.push_back(Hcand[index]);
					Hcand_cat2.push_back(Hcand[index+1]);
					if(Zmumu) Hcand_type_cat2.push_back(2);
					else if(Zee) Hcand_type_cat2.push_back(6);
				}
			}else if(signal && !saved_signal){
				if(examineThisEvent){
					std::cout << "Saving signal candidate with pts " << Hcand[index].pt << " " << Hcand[index+1].pt << " " << 
					PairMass(Hcand[index],Hcand[index+1]) << std::endl;
				}
				Hcand_signal.push_back(Hcand[index]);
				Hcand_signal.push_back(Hcand[index+1]);
				if(Zmumu) Hcand_type_signal.push_back(2);
				else if(Zee) Hcand_type_signal.push_back(6);
				saved_signal=true;
			}else if(isFakeRate){
				if(examineThisEvent){
					myobject ClosestJet = ClosestInCollection(Hcand[index+1],m->RecPFJetsAK5);
					std::cout << "Saving shape fake candidates with pass = " << shapePass1 << " " << shapePass2 << 
					" and pts " << Hcand[index].pt << " " << Hcand[index+1].pt << " " << ClosestJet.pt << " " << 
					PairMass(Hcand[index],Hcand[index+1]) << std::endl;
				}
				Hcand_FR.push_back(Hcand[index]);
				Hcand_FR.push_back(Hcand[index+1]);
				Hcand_pass.push_back(-1);
				Hcand_pass.push_back(-1);
				if(shapePass1 && shapePass2 && LTcut){
					if(matchedSync){
						std::cout << " EM Shape cand accepted!" << std::endl;
					}
					Hcand_shape_pass.push_back(1);
				}else{
					  if(matchedSync)
					{
						std::cout << " EM failed shape " << LTcut <<  std::endl;
						h_fail_shape_EM->Fill(6.0);
					}
					 Hcand_shape_pass.push_back(0);	
				 }
				if(Zmumu) Hcand_type_FR.push_back(2);
				else if(Zee) Hcand_type_FR.push_back(6);
			}
				
		}
		if(s_match_i > -1 && match2==false)
		{
			std::cout << " shape candidate not found" << std::endl;
			h_fail_shape_EM->Fill(7.0);
		}       
    
		
	}
	
	if(examineThisEvent) std::cout << " After EM, there are " << Hcand_cat0.size() << " cat0 "<< Hcand_cat1.size() << " cat1 "<< Hcand_cat2.size() << " cat2. "<<   std::endl;
	

	
	if(examineThisEvent) std::cout << " " << muTau << muE << eTau << tauTau << std::endl;
	if((Hcand_cat2.size() + Hcand_cat1.size() + Hcand_cat0.size() + Hcand_FR.size() + Hcand_signal.size()) ==0){ 
		m_logger << DEBUG << " No Higgs candidate. Going to next event" << SLogger::endmsg; 
		if(examineThisEvent) std::cout << " No Higgs candidate. Going to next event" << std::endl;
		for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
		{
			std::cout << " Channel " << sync_vec_Channel[iSync] << " " << EventTypeConv(sync_vec_Channel[iSync]) << " " << EventTypeName(EventTypeConv(sync_vec_Channel[iSync])) 
			<< " subch: " << sync_vec_subChannel[iSync] << std::endl;
			int subCh = sync_vec_subChannel[iSync];
			int Ch = EventTypeConv(sync_vec_Channel[iSync]);
			
			h_fail_reason[subCh]->Fill(4.,double(Ch));
		}
		return;
	}
	
	Hist("h_Nvertex_AfterZH")->Fill(nGoodVx);
	Hist("h_Nvertex_AfterZH_W")->Fill(nGoodVx,Z_weight);


	// cross-check
	if(Hcand_signal.size() > 0){
		h_cut_flow->Fill(5,1);
		h_cut_flow_weight->Fill(5,Z_weight);
	}

	m_logger << DEBUG << " muTau " << muTau << SLogger::endmsg;
	m_logger << DEBUG << " muE " << muE << SLogger::endmsg;
	m_logger << DEBUG << " eTau " << eTau << SLogger::endmsg;
	m_logger << DEBUG << " tauTau " << tauTau << SLogger::endmsg;

	if(examineThisEvent) std::cout << " Before type assignment" << std::endl;
	
	
	double corrHlep1,corrHlep2;
	corrHlep1=corrHlep2=1.0;
	if(isSimulation && !IgnoreSF && Hcand_signal.size()>0){
		int event_type = Hcand_type_signal[0];
		if(event_type%4==1) //mutau
		{
			if(is2012_53){
				if(SFShiftUp_Mu && onlyIDIso){
					corrHlep1=Cor_ID_Iso_Mu_Tight_2012_53X(Hcand_signal[0])+Unc_ID_Iso_Mu_Tight_2012_53X(Hcand_signal[0]);
				}else if(SFShiftDown_Mu && onlyIDIso){
					corrHlep1=Cor_ID_Iso_Mu_Tight_2012_53X(Hcand_signal[0])-Unc_ID_Iso_Mu_Tight_2012_53X(Hcand_signal[0]);
				}else{
					corrHlep1=Cor_ID_Iso_Mu_Tight_2012_53X(Hcand_signal[0]);
				}
			}else{
				corrHlep1=Cor_ID_Iso_Mu_Tight_2011(Hcand_signal[0]);
			}
		}else if(event_type%4==3){ //etau
			if(is2012_53){
				if(SFShiftUp_Ele && onlyIDIso){
					corrHlep1=Cor_ID_Iso_Ele_Tight_2012_53X(Hcand_signal[0])+Unc_ID_Iso_Ele_Tight_2012_53X(Hcand_signal[0]);
				}else if(SFShiftDown_Ele && onlyIDIso){
					corrHlep1=Cor_ID_Iso_Ele_Tight_2012_53X(Hcand_signal[0])-Unc_ID_Iso_Ele_Tight_2012_53X(Hcand_signal[0]);
				}else{
					corrHlep1=Cor_ID_Iso_Ele_Tight_2012_53X(Hcand_signal[0]);
				}
			}else{
				corrHlep1=Cor_ID_Iso_Ele_Tight_2011(Hcand_signal[0]);
			}
		}else if(event_type%4==2){ //eMu
			if(is2012_53){
				if(SFShiftUp_Mu && onlyIDIso){
					corrHlep1=Cor_ID_Iso_Mu_Loose_2012_53X(Hcand_signal[1])+Unc_ID_Iso_Mu_Loose_2012_53X(Hcand_signal[1]);
					corrHlep2=Cor_ID_Iso_Ele_Loose_2012_53X(Hcand_signal[0])+Unc_ID_Iso_Ele_Loose_2012_53X(Hcand_signal[0]);
				}else if(SFShiftDown_Mu && onlyIDIso){
					corrHlep1=Cor_ID_Iso_Mu_Loose_2012_53X(Hcand_signal[1])-Unc_ID_Iso_Mu_Loose_2012_53X(Hcand_signal[1]);
					corrHlep2=Cor_ID_Iso_Ele_Loose_2012_53X(Hcand_signal[0])-Unc_ID_Iso_Ele_Loose_2012_53X(Hcand_signal[0]);
				}else{
					
					corrHlep1=Cor_ID_Iso_Mu_Loose_2012_53X(Hcand_signal[1]);
					corrHlep2=Cor_ID_Iso_Ele_Loose_2012_53X(Hcand_signal[0]);
				
				}
			}else{
				corrHlep1=Cor_ID_Iso_Mu_Loose_2011(Hcand_signal[1]);
				corrHlep2=Cor_ID_Iso_Ele_Loose_2011(Hcand_signal[0]);
			}
		}
	}
	double weight = PUWeight*corrZlep1*corrZlep2*corrHlep1*corrHlep2;
	
	if(examineThisEvent){
		std::cout << "****** WEIGHT INFO *****" << std::endl;
		std::cout << " Event number/Lumi/Run = " << m->eventNumber << "/" << m->lumiNumber << "/" << m->runNumber << std::endl;
		std::cout << " The event is of type " << EventTypeName(Hcand_type_signal[0]) << std::endl;
		std::cout << " True PU in event:" << nPU << std::endl;
		std::cout << " PU weight: " << PUWeight << std::endl;
		std::cout << " The Z legs are (pt/eta):" << Zcand[0].pt << "/" << Zcand[0].eta << " and " << Zcand[1].pt << "/" << Zcand[1].eta << std::endl;
		std::cout << " MC/Data correction for Z legs are " << corrZlep1 << " " << corrZlep2 << std::endl;
		std::cout << " The H legs are (pt/eta):" << Hcand[0].pt << "/" << Hcand[0].eta << " and " << Hcand[1].pt << "/" << Hcand[1].eta << std::endl;
		std::cout << " MC/Data correction for H legs are " << corrHlep1 << " " << corrHlep2 << std::endl;
		std::cout << " The total weight is " << weight << std::endl;
		
		
	}

	if(examineThisEvent) std::cout << " After efficiency" << std::endl;
	
  
	// b-tag veto

	bool bTagVeto = false;
	std::vector<myobject> jet = m->RecPFJetsAK5;
	Int_t count_bJets = 0;
	Int_t count_bJetsVetoed = 0;
	Int_t count_bJets_afterVeto = 0;

	for (uint i = 0; i < jet.size() && !bTagVeto; i++) {
		double jetPt = jet[i].pt;
		double jetEta = jet[i].eta;
		double jetPhi = jet[i].phi;
		double bTag = jet[i].bDiscriminatiors_CSV;
		if(examineThisEvent) std::cout << "jet pt " << jetPt << "jet eta " << jetEta << "btag " << bTag << std::endl;
		if(jetPt > 20. && fabs(jetEta) < 2.4 && bTag > bTagValue){
			count_bJets++;
			if(examineThisEvent) std::cout << "candidate b-jet" << std::endl;
			double dR1,dR2,dR3,dR4;
			dR1=deltaR(jetEta,jetPhi,Zcand[0].eta,Zcand[0].phi);
			dR2=deltaR(jetEta,jetPhi,Zcand[1].eta,Zcand[1].phi);
			dR3=deltaR(jetEta,jetPhi,Hcand[0].eta,Hcand[0].phi);
			dR4=deltaR(jetEta,jetPhi,Hcand[1].eta,Hcand[1].phi);
			if(examineThisEvent) std::cout << " distances are " << dR1 << " " << dR2 << " " << dR3 << " " << dR4 << std::endl;
			bool overlap = false;
			if(dR1 < 0.4 || dR2 < 0.4) overlap = true;
			//muon overlap
			for(uint iMu =0; iMu< genericMuon.size() && !overlap; iMu++)
			{
				if(RelIso(genericMuon[iMu]) > 0.3 || !isLooseMu(genericMuon[iMu])) continue;
				if(deltaR(genericMuon[iMu].eta,genericMuon[iMu].phi,jetEta,jetPhi) < 0.4) overlap = true;
			}
			for(uint iEl =0; iEl< genericElectron.size() && !overlap; iEl++)
			{
				if(RelIso(genericElectron[iEl]) > 0.3 || !LooseEleId(genericElectron[iEl])) continue;
				if(deltaR(genericElectron[iEl].eta,genericElectron[iEl].phi,jetEta,jetPhi) < 0.4) overlap = true;
			}
			
			bTagVeto = !overlap;
		
		}
	}
    
	if(examineThisEvent) std::cout << " Before b-tag veto" << std::endl;
	
	if(bTagVeto)
	{
		if(examineThisEvent) std::cout << " B veto fail" << std::endl;
		for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
		{
			std::cout << " Channel " << sync_vec_Channel[iSync] << " " << EventTypeConv(sync_vec_Channel[iSync]) << " " << EventTypeName(EventTypeConv(sync_vec_Channel[iSync])) 
			<< " subch: " << sync_vec_subChannel[iSync] << std::endl;
			int subCh = sync_vec_subChannel[iSync];
			int Ch = EventTypeConv(sync_vec_Channel[iSync]);
			
			h_fail_reason[subCh]->Fill(5.,double(Ch));
		}	
		return;
	}
	
	if(examineThisEvent) std::cout << " After b-tag veto" << std::endl;
	
	// now we have the cands
	
	if(Hcand_signal.size() > 0){
		h_cut_flow->Fill(6,1);
		h_cut_flow_weight->Fill(6,weight);
		Hist("h_total_weight")->Fill(weight);
	}

        

	

	

	// histogramming
	
	// signal saving
	int sync_sig_index=-1;
	for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
	{
		if(sync_vec_subChannel[iSync]==3) sync_sig_index=iSync;
	}
	
	if(Hcand_signal.size() > 0)
		{
			 
			 int event_type = Hcand_type_signal[0];
			 if(sync_sig_index < 0) h_sync_summary[3]->Fill(0.0,double(event_type));
			 else if(EventTypeConv(sync_vec_Channel[sync_sig_index])!=event_type){
				  h_sync_summary[3]->Fill(1.0,double(event_type));
				  h_sync_summary[3]->Fill(2.0,double(EventTypeConv(sync_vec_Channel[sync_sig_index])));
			  }
			 else h_sync_summary[3]->Fill(3.0,double(event_type));
			 
			 Hist( "h_event_type" )->Fill(event_type,weight);
			 Hist( "h_event_type_raw" )->Fill(event_type);
			 
			 Hist("h_PF_MET_selected")->Fill(Met.front().et,weight);
			 h_PF_MET_nPU_selected->Fill(nGoodVx,Met.front().et,weight);
			 //ntuple filling
			if(doNtuple){
			o_run=m->runNumber;
			o_lumi=m->lumiNumber;
			o_event=m->eventNumber;
			
			// a bit od hack...
			
	
			
			o_pass=true;
			o_event_weight=weight;
			o_type=event_type;
			o_px_Z1=Zcand[0].px;o_px_Z2=Zcand[1].px;
			o_px_H1=Hcand_signal[0].px;o_px_H2=Hcand_signal[1].px;
			o_py_Z1=Zcand[0].py;o_py_Z2=Zcand[1].py;
			o_py_H1=Hcand_signal[0].py;o_py_H2=Hcand_signal[1].py;
			o_pz_Z1=Zcand[0].pz;o_pz_Z2=Zcand[1].pz;
			o_pz_H1=Hcand_signal[0].pz;o_pz_H2=Hcand_signal[1].pz;
			o_M_Z1=Zcand[0].mass;o_M_Z2=Zcand[1].mass;
			o_M_H1=Hcand_signal[0].mass;o_M_H2=Hcand_signal[1].mass;
	
			if(o_run==202504 && o_event==650927814)
			{
				std::cout << "U vsech kurev, nasel jsem ho! The type is " << EventTypeName(event_type) << std::endl;
				std::cout << " Z1(X,Y,Z,M)= " << o_px_Z1 << " " << o_py_Z1 << " " << o_pz_Z1 << " " << o_M_Z1 << std::endl;
				std::cout << " Z2(X,Y,Z,M)= " << o_px_Z2 << " " << o_py_Z2 << " " << o_pz_Z2 << " " << o_M_Z2 << std::endl;
				std::cout << " H1(X,Y,Z,M)= " << o_px_H1 << " " << o_py_H1 << " " << o_pz_H1 << " " << o_M_H1 << std::endl;
				std::cout << " H2(X,Y,Z,M)= " << o_px_H2 << " " << o_py_H2 << " " << o_pz_H2 << " " << o_M_H2 << std::endl;
				std::cout << " MVA MET(X,Y)= " << Met.front().et*TMath::Cos(Met.front().phi) << " " << Met.front().et*TMath::Sin(Met.front().phi) << std::endl;
				std::cout << " MVA MET covariance = " << m->MVAMet_sigMatrix_00 << " " << m->MVAMet_sigMatrix_01 << " " << m->MVAMet_sigMatrix_10 << " " << m->MVAMet_sigMatrix_11 << std::endl;
				vector<myobject> PFMet = m->RecPFMet;
				std::cout << " PF MET(X,Y)= " << PFMet.front().et*TMath::Cos(Met.front().phi) << " " << PFMet.front().et*TMath::Sin(Met.front().phi) << std::endl;
				std::cout << " PF MET covariance = " << m->MET_sigMatrix_00 << " " << m->MET_sigMatrix_01 << " " << m->MET_sigMatrix_10 << " " << m->MET_sigMatrix_11 << std::endl;
			}
			
			//~ 
			switch(event_type){
				case 1://MMMT
					o_pdg_Z1=13*Zcand[0].charge;
					o_pdg_Z2=13*Zcand[1].charge;
					o_pdg_H1=13*Hcand_signal[0].charge;
					o_pdg_H2=15*Hcand_signal[1].charge;
					break;
				case 2://MMEM
					o_pdg_Z1=13*Zcand[0].charge;
					o_pdg_Z2=13*Zcand[1].charge;
					o_pdg_H1=11*Hcand_signal[0].charge;
					o_pdg_H2=13*Hcand_signal[1].charge;
					break;
				case 3://MMET
					o_pdg_Z1=13*Zcand[0].charge;
					o_pdg_Z2=13*Zcand[1].charge;
					o_pdg_H1=11*Hcand_signal[0].charge;
					o_pdg_H2=15*Hcand_signal[1].charge;
					break;
				case 4://MMTT
					o_pdg_Z1=13*Zcand[0].charge;
					o_pdg_Z2=13*Zcand[1].charge;
					o_pdg_H1=15*Hcand_signal[0].charge;
					o_pdg_H2=15*Hcand_signal[1].charge;
					break;
				case 5://EEMT
					o_pdg_Z1=11*Zcand[0].charge;
					o_pdg_Z2=11*Zcand[1].charge;
					o_pdg_H1=13*Hcand_signal[0].charge;
					o_pdg_H2=15*Hcand_signal[1].charge;
					break;
				case 6://EEEM
					o_pdg_Z1=11*Zcand[0].charge;
					o_pdg_Z2=11*Zcand[1].charge;
					o_pdg_H1=11*Hcand_signal[0].charge;
					o_pdg_H2=13*Hcand_signal[1].charge;
					break;
				case 7://EEET
					o_pdg_Z1=11*Zcand[0].charge;
					o_pdg_Z2=11*Zcand[1].charge;
					o_pdg_H1=11*Hcand_signal[0].charge;
					o_pdg_H2=15*Hcand_signal[1].charge;
					break;
				case 8://EETT
					o_pdg_Z1=11*Zcand[0].charge;
					o_pdg_Z2=11*Zcand[1].charge;
					o_pdg_H1=15*Hcand_signal[0].charge;
					o_pdg_H2=15*Hcand_signal[1].charge;
					break;
			}
			
			if(FillSVmassInfo){
				double tauEScorrX = 0.;
				double tauEScorrY = 0.;
				
				if(ShiftTauES_up||ShiftTauES_down){
					switch(event_type){
						case 1:
						case 3:
						case 5:
						case 7:
						   tauEScorrX=(double)Hcand_signal[1].px*(-SystUncert_ES/(1.+SystUncert_ES));
						   tauEScorrY=(double)Hcand_signal[1].py*(-SystUncert_ES/(1.+SystUncert_ES));
						   break;
						case 4:
						case 8:
							tauEScorrX=(double)Hcand_signal[1].px*(-SystUncert_ES/(1.+SystUncert_ES));
							tauEScorrX+=(double)Hcand_signal[0].px*(-SystUncert_ES/(1.+SystUncert_ES));
							tauEScorrY=(double)Hcand_signal[1].py*(-SystUncert_ES/(1.+SystUncert_ES));
							tauEScorrY+=(double)Hcand_signal[0].py*(-SystUncert_ES/(1.+SystUncert_ES));
							break;
						default:
							break;
					}
				}
				if(ShiftTauES_down){
					tauEScorrX=-tauEScorrX;
					tauEScorrY=-tauEScorrY;
				}
				
				double metX=Met.front().et*TMath::Cos(Met.front().phi);
				double metY=Met.front().et*TMath::Sin(Met.front().phi);
					 
				o_MET_x=metX+tauEScorrX;
				o_MET_y=metY+tauEScorrY;
				
				
				o_covMET_00=m->MVAMet_sigMatrix_00;
				o_covMET_01=m->MVAMet_sigMatrix_01;
				o_covMET_10=m->MVAMet_sigMatrix_10;
				o_covMET_11=m->MVAMet_sigMatrix_11;
			}
			
			//pdf info
			if(FillPDFInfo){
				o_pdf_alphaQCD=m->alphaQCD;
				o_pdf_alphaQED=m->alphaQED;
				o_pdf_qScale=m->qScale;
				o_pdf_weight=m->weight;
				o_pdf_scalePDF=m->scalePDF;
				o_pdf_binningValue0=m->binningValue0;
				o_pdf_id_1=m->id_First; o_pdf_id_2=m->id_Second; //(first,second) x_First
				o_pdf_x_1=m->x_First; o_pdf_x_2=m->x_Second; //(first,second)
				o_pdf_xPDF_1=m->xPDF_First; o_pdf_xPDF_2=m->xPDF_Second; //(first,second)
				o_pdf_hasPDF=m->hasPDF; 
				o_pdf_hasBinningValues=m->hasBinningValues; 
				o_pdf_signalProcessID=m->signalProcessID; 
				o_pdf_binningValueSize=m->binningValueSize; 
			}
			
			if(FillZZgenInfo)
			{
				//finding Z's
				// looseElectrons
				std::vector<myGenobject> allMC = m->RecGenParticle;
				std::vector<myGenobject> ZZpair = FindTrueZZ(&allMC);
				//~ std::cout << "We found " << ZZpair.size() << "Z's" << std::endl;
				if(ZZpair.size()==2){
					o_gen_pt_Z1=ZZpair[0].pt;o_gen_pt_Z2=ZZpair[1].pt;
					o_gen_eta_Z1=ZZpair[0].eta;o_gen_eta_Z2=ZZpair[1].eta;
					o_gen_phi_Z1=ZZpair[0].phi;o_gen_phi_Z2=ZZpair[1].phi;
					o_gen_mass_Z1=ZZpair[0].mass;o_gen_mass_Z2=ZZpair[1].mass;
				}else{
					o_gen_pt_Z1=-999.;o_gen_pt_Z2=-999.;
					o_gen_eta_Z1=-999.;o_gen_eta_Z2=-999.;
					o_gen_phi_Z1=-999.;o_gen_phi_Z2=-999.;
					o_gen_mass_Z1=-999.;o_gen_mass_Z2=-999.;
				}
			
			}
			
			if(FillGenMET)
			{
				std::vector<myGenobject> truMET=m->RecGenMet;
				//~ for(uint iVec=0; iVec < truMET.size(); iVec++)
				//~ {
					//~ std::cout << "member no. " << iVec << " pt=" << truMET[iVec].pt << 
					//~ " phi=" << truMET[iVec].phi << " et=" << truMET[iVec].et << std::endl;
				//~ }
				double genMET=truMET[0].pt;
				double genPhi=truMET[0].phi;
				double genMETx=genMET*cos(genPhi);
				double genMETy=genMET*sin(genPhi);
				o_gen_MET_x=genMETx;
				o_gen_MET_y=genMETy;
				o_gen_MET=genMET;
			
			}
		 }
		}else{ // no sig candidate
				if(sync_sig_index > -1) // sync event exists
				{
					h_sync_summary[3]->Fill(4.0,double(EventTypeConv(sync_vec_Channel[sync_sig_index])));
				}
		 
		}
    // save mass info in SS events to get background shape
    std::vector<int> sync_BG_index;
    sync_BG_index.clear();
	for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
	{
		if(sync_vec_subChannel[iSync]==4) sync_BG_index.push_back(iSync);
	}
    
    for(uint i=0; i < Hcand_FR.size(); i+=2)
		{
			 if(Hcand_shape_pass[i/2] <1) continue; // did not pass loose ID+iso cuts
			 int event_type = Hcand_type_FR[i/2];
			 bool common = false;
			 double Mass;
			 if(doSync) Mass=PairMass(Hcand_FR[i],Hcand_FR[i+1]);
			 
			 for(uint iSync = 0; iSync < sync_BG_index.size() && !common; iSync++)
			 {
				 if(event_type == EventTypeConv(sync_vec_Channel[sync_BG_index[iSync]])  && 
					(fabs(Mass-sync_vec_HMass[sync_BG_index[iSync]]) < 0.1) ) common = true;//
				if(common){ // remove matched candidates
					sync_BG_index.erase(sync_BG_index.begin()+iSync);
					iSync-=1;
				}
			 }
			 if(common) h_sync_summary[4]->Fill(3.0,double(event_type));
			 else{
				if(doSync)  std::cout << " UCL only event of type: " << EventTypeName(event_type) << " mass = " << Mass << std::endl;
				  h_sync_summary[4]->Fill(0.0,double(event_type)); // UCL only
			  }
			 //ntuple filling
			 if(doNtuple){
			o_run=m->runNumber;
			o_lumi=m->lumiNumber;
			o_event=m->eventNumber;
			
			o_FR=true; 
			o_FRt.push_back(Hcand_shape_pass[i/2] >1); // passed tight ID cuts
			o_event_weight=weight;
			o_FR_n++;
			
		// make to vectors
			o_FR_type.push_back(event_type);
			o_FR_px_H1.push_back(Hcand_FR[i].px);o_FR_px_H2.push_back(Hcand_FR[i+1].px);
			o_FR_py_H1.push_back(Hcand_FR[i].py);o_FR_py_H2.push_back(Hcand_FR[i+1].py);
			o_FR_pz_H1.push_back(Hcand_FR[i].pz);o_FR_pz_H2.push_back(Hcand_FR[i+1].pz);
			o_FR_M_H1.push_back(Hcand_FR[i].mass);o_FR_M_H2.push_back(Hcand_FR[i+1].mass);
		//~ 
		
			//~ o_px.push_back(Zcand[0].px);o_px.push_back(Zcand[1].px);
			//~ o_px.push_back(Hcand[0].px);o_px.push_back(Hcand[1].px);
			//~ 
			//~ o_py.push_back(Zcand[0].py);o_py.push_back(Zcand[1].py);
			//~ o_py.push_back(Hcand[0].py);o_py.push_back(Hcand[1].py);
			//~ 
			//~ o_pz.push_back(Zcand[0].pz);o_pz.push_back(Zcand[1].pz);
			//~ o_pz.push_back(Hcand[0].pz);o_pz.push_back(Hcand[1].pz);
			//~ 
			//~ o_E.push_back(Zcand[0].E);o_E.push_back(Zcand[1].E);
			//~ o_E.push_back(Hcand[0].E);o_E.push_back(Hcand[1].E);
			//~ 
			switch(event_type){
				case 1://MMMT
					o_FR_pdg_H1.push_back(13*Hcand_FR[i].charge);
					o_FR_pdg_H2.push_back(15*Hcand_FR[i+1].charge);
					break;
				case 2://MMEM
					o_FR_pdg_H1.push_back(11*Hcand_FR[i].charge);
					o_FR_pdg_H2.push_back(13*Hcand_FR[i+1].charge);
					break;
				case 3://MMET
					o_FR_pdg_H1.push_back(11*Hcand_FR[i].charge);
					o_FR_pdg_H2.push_back(15*Hcand_FR[i+1].charge);
					break;
				case 4://MMTT
					o_FR_pdg_H1.push_back(15*Hcand_FR[i].charge);
					o_FR_pdg_H2.push_back(15*Hcand_FR[i+1].charge);
					break;
				case 5://EEMT
					o_FR_pdg_H1.push_back(13*Hcand_FR[i].charge);
					o_FR_pdg_H2.push_back(15*Hcand_FR[i+1].charge);
					break;
				case 6://EEEM
					o_FR_pdg_H1.push_back(11*Hcand_FR[i].charge);
					o_FR_pdg_H2.push_back(13*Hcand_FR[i+1].charge);
					break;
				case 7://EEET
					o_FR_pdg_H1.push_back(11*Hcand_FR[i].charge);
					o_FR_pdg_H2.push_back(15*Hcand_FR[i+1].charge);
					break;
				case 8://EETT
					o_FR_pdg_H1.push_back(15*Hcand_FR[i].charge);
					o_FR_pdg_H2.push_back(15*Hcand_FR[i+1].charge);
					break;
			}
			
			if(FillSVmassInfo){
				o_MET_x=Met.front().px;
				o_MET_y=Met.front().py;
				
				
				o_covMET_00=m->MVAMet_sigMatrix_00;
				o_covMET_01=m->MVAMet_sigMatrix_01;
				o_covMET_10=m->MVAMet_sigMatrix_10;
				o_covMET_11=m->MVAMet_sigMatrix_11;
			}
			
			//pdf info
			if(FillPDFInfo){
				o_pdf_alphaQCD=m->alphaQCD;
				o_pdf_alphaQED=m->alphaQED;
				o_pdf_qScale=m->qScale;
				o_pdf_weight=m->weight;
				o_pdf_scalePDF=m->scalePDF;
				o_pdf_binningValue0=m->binningValue0;
				o_pdf_id_1=m->id_First; o_pdf_id_2=m->id_Second; //(first,second) x_First
				o_pdf_x_1=m->x_First; o_pdf_x_2=m->x_Second; //(first,second)
				o_pdf_xPDF_1=m->xPDF_First; o_pdf_xPDF_2=m->xPDF_Second; //(first,second)
				o_pdf_hasPDF=m->hasPDF; 
				o_pdf_hasBinningValues=m->hasBinningValues; 
				o_pdf_signalProcessID=m->signalProcessID; 
				o_pdf_binningValueSize=m->binningValueSize; 
			}
			}
			
			 
		 }
		 // not matched sync objects
		 for(uint iSync = 0; iSync < sync_BG_index.size(); iSync++)
			 {
				std::cout << " ULB only event of type: " << EventTypeName(EventTypeConv(sync_vec_Channel[sync_BG_index[iSync]])) << " mass = " << sync_vec_HMass[sync_BG_index[iSync]] << std::endl;
				h_sync_summary[4]->Fill(4.0,double(EventTypeConv(sync_vec_Channel[sync_BG_index[iSync]])));
			 }
			
	if(printoutEvents)
	{
		if(examineThisEvent) std::cout << " in printout " << std::endl;
		
		for(uint i=0; i < Hcand_signal.size(); i+=2)
		{
			 int event_type = Hcand_type_signal[i/2];
			 double mass=PairMass(Hcand_signal[i],Hcand_signal[i+1]);	
			 logS << setiosflags(ios::fixed) << std::setprecision(1) << 
			 event_type << " " << m->runNumber << " " << m->lumiNumber << " " << m->eventNumber << " " 
			 << Zmass << " " << mass << std::endl;
		}
		
		
		
		
		for(uint i=0; i < Hcand_cat0.size(); i+=2)
		{
			int exp_event_type;
			std::string name;
			double mass=PairMass(Hcand_cat0[i],Hcand_cat0[i+1]);
			switch(Hcand_type_cat0[i/2])
			{
				case 1: exp_event_type=30; name="mmmt"; break;
				case 2: exp_event_type=40; name="mmme"; break;
				case 3: exp_event_type=20; name="mmet"; break;
				case 4: exp_event_type=10; name="mmtt"; break;
				case 5: exp_event_type=60; name="eemt"; break;
				case 6: exp_event_type=80; name="eeem"; break;
				case 7: exp_event_type=70; name="eeet"; break;
				case 8: exp_event_type=50; name="eett"; break;
				default: exp_event_type=0; break;
			}
			std::string status="FF";
			int new_e_type=90+exp_event_type/10;
			log1 << setiosflags(ios::fixed) << std::setprecision(1) << new_e_type << " " << status << " " <<  
			m->runNumber << " " << m->lumiNumber << " " << m->eventNumber << " " << Zmass << " " << mass  << std::endl; //"     " << fileName << std::endl;
			
		}
		for(uint i=0; i < Hcand_cat1.size(); i+=2)
		{
			int exp_event_type;
			std::string name;
			double mass=PairMass(Hcand_cat1[i],Hcand_cat1[i+1]);
			switch(Hcand_type_cat1[i/2])
			{
				case 1: exp_event_type=32; name="mmmt"; break;
				case 2: exp_event_type=42; name="mmme"; break;
				case 3: exp_event_type=22; name="mmet"; break;
				case 4: exp_event_type=12; name="mmtt"; break;
				case 5: exp_event_type=62; name="eemt"; break;
				case 6: exp_event_type=82; name="eeem"; break;
				case 7: exp_event_type=72; name="eeet"; break;
				case 8: exp_event_type=52; name="eett"; break;
				default: exp_event_type=0; break;
			}
			std::string status="FP";
			int new_e_type=90+exp_event_type/10;
			log1 << setiosflags(ios::fixed) << std::setprecision(1) << new_e_type << " " << status << " " <<  
			m->runNumber << " " << m->lumiNumber << " " << m->eventNumber << " " << Zmass << " " << mass  << std::endl; //"     " << fileName << std::endl;
			
		}
		for(uint i=0; i < Hcand_cat2.size(); i+=2)
		{
			int exp_event_type;
			std::string name;
			double mass=PairMass(Hcand_cat2[i],Hcand_cat2[i+1]);
			switch(Hcand_type_cat2[i/2])
			{
				case 1: exp_event_type=31; name="mmmt"; break;
				case 2: exp_event_type=41; name="mmme"; break;
				case 3: exp_event_type=21; name="mmet"; break;
				case 4: exp_event_type=11; name="mmtt"; break;
				case 5: exp_event_type=61; name="eemt"; break;
				case 7: exp_event_type=71; name="eeet"; break;
				case 6: exp_event_type=81; name="eeem"; break;
				case 8: exp_event_type=51; name="eett"; break;
				default: exp_event_type=0; break;
			}
			std::string status="PF";
			int new_e_type=90+exp_event_type/10;
			log1 << setiosflags(ios::fixed) << std::setprecision(1) << new_e_type << " " << status << " " <<  
			m->runNumber << " " << m->lumiNumber << " " << m->eventNumber << " " << Zmass << " " << mass  << std::endl; //"     " << fileName << std::endl;
			
		}
		
		for(uint i=0; i < Hcand_FR.size(); i+=2)
		{
			int exp_event_type;
			std::string name;
			double mass=PairMass(Hcand_FR[i],Hcand_FR[i+1]);
			bool fake1 = false;
			bool fake12 = false;
			switch(Hcand_type_FR[i/2])
			{
				case 1: exp_event_type=93; name="mmmt"; fake1 = true; break;
				case 2: exp_event_type=94; name="mmme"; break;
				case 3: exp_event_type=92; name="mmet"; fake1 = true; break;
				case 4: exp_event_type=91; name="mmtt"; fake12= true; break;
				case 5: exp_event_type=96; name="eemt"; fake1 = true; break;
				case 6: exp_event_type=98; name="eeem"; break;
				case 7: exp_event_type=97; name="eeet"; fake1 = true; break;
				case 8: exp_event_type=95; name="eett"; fake12 = true; break;
				default: exp_event_type=0; break;
			}
			std::string status="DD";
			int new_e_type=exp_event_type;
			logFR << setiosflags(ios::fixed) << std::setprecision(1) << new_e_type << " " << status << " " <<  
			m->runNumber << " " << m->lumiNumber << " " << m->eventNumber << " " << Zmass << " " << mass  << std::endl; //"     " << fileName << std::endl;
			if(Hcand_pass[i] && (fake1 || fake12)){
				 status="P1";
				 myobject ClosestJet = ClosestInCollection(Hcand_FR[i],jet);
				 logFR << setiosflags(ios::fixed) << std::setprecision(1) << new_e_type << " " << status << " " <<  
				 m->runNumber << " " << m->lumiNumber << " " << m->eventNumber << " " << Zmass << " " << mass  << " " <<
				 Hcand_FR[i].pt << " " << ClosestJet.pt << std::endl; //"     " << fileName << std::endl;
			 }
			if(Hcand_pass[i+1] && fake12){
				 status="P2";
				 myobject ClosestJet = ClosestInCollection(Hcand_FR[i+1],jet);
				 logFR << setiosflags(ios::fixed) << std::setprecision(1) << new_e_type << " " << status << " " <<  
				 m->runNumber << " " << m->lumiNumber << " " << m->eventNumber << " " << Zmass << " " << mass  << " " <<
				 Hcand_FR[i+1].pt << " " << ClosestJet.pt << std::endl; //"     " << fileName << std::endl;
			}
			
			
		}
		
	}
			
	if(examineThisEvent) std::cout << " filling signal histo " << std::endl;	
				//histo filling
	if(Hcand_signal.size() > 0)
		{	
			int event_type = Hcand_type_signal[0];
			double mass=PairMass(Hcand_signal[0],Hcand_signal[1]);	
			h_H_mass_signal_types[event_type-1]->Fill(mass,weight);	
		}
	if(examineThisEvent) std::cout << " filling FR histo " << std::endl;
			
	std::vector<int> sync_FRdenom_index;
    sync_FRdenom_index.clear();
	for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
	{
		if(sync_vec_subChannel[iSync]==1 && sync_vec_Channel[iSync]>8) sync_FRdenom_index.push_back(iSync);
	}
	
	std::vector<int> sync_FRnumL_index;
    sync_FRnumL_index.clear();
	for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
	{
		if(sync_vec_subChannel[iSync]==3 && sync_vec_Channel[iSync]>8) sync_FRnumL_index.push_back(iSync);
	}
	
	std::vector<int> sync_FRnumT_index;
    sync_FRnumT_index.clear();
	for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
	{
		if(sync_vec_subChannel[iSync]==2 && sync_vec_Channel[iSync]>8) sync_FRnumT_index.push_back(iSync);
	}
		
	for(uint i=0; i < Hcand_FR.size(); i+=2)
	{
		 myobject ClosestJet = ClosestInCollection(Hcand_FR[i],jet);
		 myobject ClosestJet2 = ClosestInCollection(Hcand_FR[i+1],jet); //tau in LT
		 bool barrel1= fabs(ClosestJet.eta) < 1.4 ? true : false; 
		 bool barrel2= fabs(ClosestJet2.eta) < 1.4 ? true : false; 
		 
		 int exp_event_type=Hcand_type_FR[i/2];
		 double mass=PairMass(Hcand_FR[i],Hcand_FR[i+1]);
		 
		 if(Hcand_shape_pass[i/2] > 0) h_H_mass_FR_types[exp_event_type-1]->Fill(mass,weight);
		 if(Hcand_shape_pass[i/2] > 1) h_H_mass_FRt_types[exp_event_type-1]->Fill(mass,weight);
		 	
		 if(examineThisEvent) std::cout << " filled mass " << std::endl;
		 
		 //
		 int myChannel1 = -1;
		 int myChannel2 = -1;
		 if(doSync && doSyncFR)
		 {
			switch(exp_event_type%4)
			{
				case 0: // TT
				 myChannel1 = barrel1 ? 9 : 10;
				 myChannel2 = barrel2 ? 9 : 10;
				 break;
				case 1: // MT
				  myChannel1 = 14;
				  myChannel2 = barrel2 ? 11: 12;
				  break;
				case 3: // ET
				  myChannel1 = 13;
				  myChannel2 = barrel2 ? 11: 12;
				  break;
				 default:
				  break;
			}
		 }
		 
		 bool common1 = false;
		 bool common2 = false;
		 bool correctOrder = false;
		 if(doSyncFR) std::cout << " size if denom/loose/tight is" << sync_FRdenom_index.size() << "/" <<
		 sync_FRnumL_index.size() << "/" << sync_FRnumT_index.size() << "/" << std::endl;
		 
		 // find sync match for the lepton 1
		 for(int iSync =0; (uint)iSync < sync_FRdenom_index.size() && !common1 && i <2; iSync++)
		 {
			std::cout << "1: object #" << iSync << std::endl;
			if(sync_vec_Channel[sync_FRdenom_index[iSync]] == myChannel1 && 
			(fabs(Hcand_FR[i].pt-sync_vec_l3Pt[sync_FRdenom_index[iSync]]) < 0.1) &&
			(fabs(Hcand_FR[i].eta-sync_vec_l3Eta[sync_FRdenom_index[iSync]]) < 0.1)){
				 common1 = true;
				 correctOrder=true;
			 }
			if(sync_vec_Channel[sync_FRdenom_index[iSync]] == myChannel1 && 
			((fabs(Hcand_FR[i].pt-sync_vec_l4Pt[sync_FRdenom_index[iSync]]) < 0.1) &&
			(fabs(Hcand_FR[i].eta-sync_vec_l4Eta[sync_FRdenom_index[iSync]]) < 0.1))) 
				common1 = true;
			if(common1)
			{
				std::cout << "removing 1:" << sync_FRdenom_index.size() << " " << iSync << std::endl;
				
				sync_FRdenom_index.erase(sync_FRdenom_index.begin()+iSync);
				iSync-=1;
				std::cout << "removed 1:" << sync_FRdenom_index.size() << " " << iSync << std::endl;
			}
		}
		
		// find sync match for the lepton 2
		 for(int iSync =0; (uint)iSync < sync_FRdenom_index.size() && !common2 && i <2; iSync++)
		 {
			std::cout << "2: object #" << iSync << std::endl;
			if(sync_vec_Channel[sync_FRdenom_index[iSync]] == myChannel2 && 
			(fabs(Hcand_FR[i+1].pt-sync_vec_l3Pt[sync_FRdenom_index[iSync]]) < 0.1) &&
			(fabs(Hcand_FR[i+1].eta-sync_vec_l3Eta[sync_FRdenom_index[iSync]]) < 0.1)){
				 correctOrder=false;
				 common2 = true;
			 }
			if(sync_vec_Channel[sync_FRdenom_index[iSync]] == myChannel2 && 
			((fabs(Hcand_FR[i+1].pt-sync_vec_l4Pt[sync_FRdenom_index[iSync]]) < 0.1) &&
			(fabs(Hcand_FR[i+1].eta-sync_vec_l4Eta[sync_FRdenom_index[iSync]]) < 0.1)))
				common2 = true;
			if(common2)
			{
				std::cout << "removing 2:" << sync_FRdenom_index.size() << " " << iSync << std::endl;
				
				sync_FRdenom_index.erase(sync_FRdenom_index.begin()+iSync);
				iSync-=1;
				std::cout << "removed 2:" << sync_FRdenom_index.size() << " " << iSync << std::endl;
			}
		}
		
		
			
		 
		 if(common1) h_sync_summary[1]->Fill(3.0,double(myChannel1));
		 else if (i<2){
				if(doSyncFR && Hcand_pass[i] > -1){  
					std::cout << " UCL only event of type: " << myChannel1 << " mass = " << mass << " pt = " << Hcand_FR[i].pt << " eta= " << Hcand_FR[i].eta << 
					"jeta= " << ClosestJet.eta << std::endl;
					h_sync_summary[1]->Fill(0.0,double(myChannel1)); // UCL only
					Float_t mass = PairMass(Hcand_FR[i],Hcand_FR[i+1]);
					 sync_o_event = m->eventNumber;
					 sync_o_lumi = m->lumiNumber;
					 sync_o_run = m->runNumber;
					
					 sync_o_Channel = myChannel1;
					 sync_o_subChannel = 1;
					 sync_o_HMass = mass;
					 sync_o_l3Pt = Hcand_FR[i].pt;
					 sync_o_l3Eta = Hcand_FR[i].eta;
					 sync_o_l3_CloseJetPt = ClosestJet.pt;
					 sync_o_l3_CloseJetEta = ClosestJet.eta;
					 sync_o_l4Pt = Hcand_FR[i+1].pt;
					 sync_o_l4Eta = Hcand_FR[i+1].eta;
					 sync_o_l4_CloseJetPt = ClosestJet2.pt;
					 sync_o_l4_CloseJetEta = ClosestJet2.eta;
					 
					 syncOutTree->Fill();	
				}
			  }
		 if(common2) h_sync_summary[1]->Fill(3.0,double(myChannel2));
		 else if (i<2 && Hcand_pass[1+1] > -1){
				if(doSyncFR){
					  std::cout << " UCL only event of type: " << myChannel2 << " mass = " << mass << " pt = " << Hcand_FR[i+1].pt << " eta= " << Hcand_FR[i+1].eta << 
					"jeta= " << ClosestJet2.eta << std::endl;
				  h_sync_summary[1]->Fill(0.0,double(myChannel2)); // UCL only
				  Float_t mass = PairMass(Hcand_FR[i],Hcand_FR[i+1]);
					 sync_o_event = m->eventNumber;
					 sync_o_lumi = m->lumiNumber;
					 sync_o_run = m->runNumber;
					
					 sync_o_Channel = myChannel2;
					 sync_o_subChannel = 1;
					 sync_o_HMass = mass;
					 sync_o_l3Pt = Hcand_FR[i].pt;
					 sync_o_l3Eta = Hcand_FR[i].eta;
					 sync_o_l3_CloseJetPt = ClosestJet.pt;
					 sync_o_l3_CloseJetEta = ClosestJet.eta;
					 sync_o_l4Pt = Hcand_FR[i+1].pt;
					 sync_o_l4Eta = Hcand_FR[i+1].eta;
					 sync_o_l4_CloseJetPt = ClosestJet2.pt;
					 sync_o_l4_CloseJetEta = ClosestJet2.eta;
					 
					 syncOutTree->Fill();	
				}
			  }
		 if(!correctOrder && doSyncFR && i < 2)
		 {
			if(!common1) h_sync_summary[1]->Fill(1.0,double(myChannel1));
			else if(!common2) h_sync_summary[1]->Fill(2.0,double(myChannel1));
			else h_sync_summary[1]->Fill(5.0,double(myChannel1));
		 }
			  
		// numerator Loose
		
		common1 = false;
		common2 = false;
		correctOrder = false;
		
		// find sync match for the lepton 1
		 for(int iSync =0; (uint)iSync < sync_FRnumL_index.size() && !common1 && i < 2; iSync++)
		 {
			std::cout << "1: object #" << iSync << std::endl;
			if(sync_vec_Channel[sync_FRnumL_index[iSync]] == myChannel1 && Hcand_pass[i] > 0 && 
			(fabs(Hcand_FR[i].pt-sync_vec_l3Pt[sync_FRnumL_index[iSync]]) < 0.1) &&
			(fabs(Hcand_FR[i].eta-sync_vec_l3Eta[sync_FRnumL_index[iSync]]) < 0.1)){
				 common1 = true;
				 correctOrder=true;
			 }
			if(sync_vec_Channel[sync_FRnumL_index[iSync]] == myChannel1 && Hcand_pass[i] > 0 &&
			((fabs(Hcand_FR[i].pt-sync_vec_l4Pt[sync_FRnumL_index[iSync]]) < 0.1) &&
			(fabs(Hcand_FR[i].eta-sync_vec_l4Eta[sync_FRnumL_index[iSync]]) < 0.1))) 
				common1 = true;
			if(common1)
			{
				std::cout << "removing 1:" << sync_FRnumL_index.size() << " " << iSync << std::endl;
				
				sync_FRnumL_index.erase(sync_FRnumL_index.begin()+iSync);
				iSync-=1;
				std::cout << "removed 1:" << sync_FRnumL_index.size() << " " << iSync << std::endl;
			}
		}


		// find sync match for the lepton 2
		 for(int iSync =0; (uint)iSync < sync_FRnumL_index.size() && !common2 && i < 2 ; iSync++)
		 {
			std::cout << "2: object #" << iSync << std::endl;
			if(sync_vec_Channel[sync_FRnumL_index[iSync]] == myChannel2 && Hcand_pass[i+1] > 0 && 
			(fabs(Hcand_FR[i+1].pt-sync_vec_l3Pt[sync_FRnumL_index[iSync]]) < 0.1) &&
			(fabs(Hcand_FR[i+1].eta-sync_vec_l3Eta[sync_FRnumL_index[iSync]]) < 0.1)){
				 common2 = true;
				 correctOrder=false;
			 }
			if(sync_vec_Channel[sync_FRnumL_index[iSync]] == myChannel2 && Hcand_pass[i+1] > 0 && 
			((fabs(Hcand_FR[i+1].pt-sync_vec_l4Pt[sync_FRnumL_index[iSync]]) < 0.1) &&
			(fabs(Hcand_FR[i+1].eta-sync_vec_l4Eta[sync_FRnumL_index[iSync]]) < 0.1))) 
				common2 = true;
			if(common2)
			{
				std::cout << "removing 2:" << sync_FRnumL_index.size() << " " << iSync << std::endl;
				
				sync_FRnumL_index.erase(sync_FRnumL_index.begin()+iSync);
				iSync-=1;
				std::cout << "removed 2:" << sync_FRnumL_index.size() << " " << iSync << std::endl;
			}
		}
	
		
		 
		 if(common1) h_sync_summary[3]->Fill(3.0,double(myChannel1));
		 else if(Hcand_pass[i]>0 && i < 2){
				if(doSyncFR){  
					std::cout << "Loose FR: UCL only event of type: " << myChannel1 << " mass = " << mass << " pt = " << Hcand_FR[i].pt << " eta= " << Hcand_FR[i].eta << 
				"jeta= " << ClosestJet.eta << std::endl;
				  h_sync_summary[3]->Fill(0.0,double(myChannel1)); // UCL only
				  // fill information about this event
					Float_t mass = PairMass(Hcand_FR[i],Hcand_FR[i+1]);
					 sync_o_event = m->eventNumber;
					 sync_o_lumi = m->lumiNumber;
					 sync_o_run = m->runNumber;
					
					 sync_o_Channel = myChannel1;
					 sync_o_subChannel = 3;
					 sync_o_HMass = mass;
					 sync_o_l3Pt = Hcand_FR[i].pt;
					 sync_o_l3Eta = Hcand_FR[i].eta;
					 sync_o_l3_CloseJetPt = ClosestJet.pt;
					 sync_o_l3_CloseJetEta = ClosestJet.eta;
					 sync_o_l4Pt = Hcand_FR[i+1].pt;
					 sync_o_l4Eta = Hcand_FR[i+1].eta;
					 sync_o_l4_CloseJetPt = ClosestJet2.pt;
					 sync_o_l4_CloseJetEta = ClosestJet2.eta;
					 
					 syncOutTree->Fill();	   
				 }
			  }
		 if(common2) h_sync_summary[3]->Fill(3.0,double(myChannel2));
		 else if(Hcand_pass[i+1]>0 && i < 2){
				if(doSyncFR){
					  std::cout << "Loose FR: UCL only event of type: " << myChannel2 << " mass = " << mass << " pt = " << Hcand_FR[i+1].pt << " eta= " << Hcand_FR[i+1].eta << 
				"jeta= " << ClosestJet2.eta << std::endl;
				 h_sync_summary[3]->Fill(0.0,double(myChannel2)); // UCL only
				 
				 Float_t mass = PairMass(Hcand_FR[i],Hcand_FR[i+1]);
					 sync_o_event = m->eventNumber;
					 sync_o_lumi = m->lumiNumber;
					 sync_o_run = m->runNumber;
					
					 sync_o_Channel = myChannel2;
					 sync_o_subChannel = 3;
					 sync_o_HMass = mass;
					 sync_o_l3Pt = Hcand_FR[i].pt;
					 sync_o_l3Eta = Hcand_FR[i].eta;
					 sync_o_l3_CloseJetPt = ClosestJet.pt;
					 sync_o_l3_CloseJetEta = ClosestJet.eta;
					 sync_o_l4Pt = Hcand_FR[i+1].pt;
					 sync_o_l4Eta = Hcand_FR[i+1].eta;
					 sync_o_l4_CloseJetPt = ClosestJet2.pt;
					 sync_o_l4_CloseJetEta = ClosestJet2.eta;
					 
					 syncOutTree->Fill();	
				 }
			  }
			  
		 if(!correctOrder && doSyncFR && i < 2)
		 {
			if(!common1 && Hcand_pass[i] >0) h_sync_summary[1]->Fill(1.0,double(myChannel1));
			else if(!common2 && Hcand_pass[i+1] >0) h_sync_summary[1]->Fill(2.0,double(myChannel1));
			else if(Hcand_pass[i] >0 && Hcand_pass[i+1] >0) h_sync_summary[1]->Fill(5.0,double(myChannel1));
		 }
			  
		// numerator Tight
		
		common1 = false;
		common2 = false;
		correctOrder = false;
		
		// find sync match for the lepton 1 - tight is only for lepton !
		 for(int iSync =0; (uint)iSync < sync_FRnumT_index.size() && !common1 && i < 2; iSync++)
		 {
			if(myChannel1!= 13 && myChannel1!=14) continue; // just e and mu
			std::cout << "1: object #" << iSync << std::endl;
			if(sync_vec_Channel[sync_FRnumT_index[iSync]] == myChannel1 && Hcand_pass[i] ==2 && 
			(fabs(Hcand_FR[i].pt-sync_vec_l3Pt[sync_FRnumT_index[iSync]]) < 0.1) &&
			(fabs(Hcand_FR[i].eta-sync_vec_l3Eta[sync_FRnumT_index[iSync]]) < 0.1)){
				 common1 = true;
				 correctOrder=true;
			 }
			if(sync_vec_Channel[sync_FRnumT_index[iSync]] == myChannel1 && Hcand_pass[i] ==2 &&
			((fabs(Hcand_FR[i].pt-sync_vec_l4Pt[sync_FRnumT_index[iSync]]) < 0.1) &&
			(fabs(Hcand_FR[i].eta-sync_vec_l4Eta[sync_FRnumT_index[iSync]]) < 0.1))) 
				common1 = true;
			if(common1)
			{
				std::cout << "removing 1:" << sync_FRnumT_index.size() << " " << iSync << std::endl;
				
				sync_FRnumT_index.erase(sync_FRnumT_index.begin()+iSync);
				iSync-=1;
				std::cout << "removed 1:" << sync_FRnumT_index.size() << " " << iSync << std::endl;
			}
		}
		
		 for(int iSync =0; (uint)iSync < sync_FRnumT_index.size() && !common2 && i < 2; iSync++)
		 {
			if(myChannel1!= 13 && myChannel1!=14) continue; // just in case
			std::cout << "2: object #" << iSync << std::endl;
			if(sync_vec_Channel[sync_FRnumT_index[iSync]] == myChannel2 && Hcand_pass[i+1] > 0 && 
			(fabs(Hcand_FR[i+1].pt-sync_vec_l3Pt[sync_FRnumT_index[iSync]]) < 0.1) &&
			(fabs(Hcand_FR[i+1].eta-sync_vec_l3Eta[sync_FRnumT_index[iSync]]) < 0.1)){
				 common2 = true;
				 correctOrder=false;
			 }
			if(sync_vec_Channel[sync_FRnumT_index[iSync]] == myChannel2 && Hcand_pass[i+1] >2 &&
			((fabs(Hcand_FR[i+1].pt-sync_vec_l4Pt[sync_FRnumT_index[iSync]]) < 0.1) &&
			(fabs(Hcand_FR[i+1].eta-sync_vec_l4Eta[sync_FRnumT_index[iSync]]) < 0.1))) 
				common2 = true;
			if(common2)
			{
				std::cout << "removing 2:" << sync_FRnumT_index.size() << " " << iSync << std::endl;
				
				sync_FRnumT_index.erase(sync_FRnumT_index.begin()+iSync);
				iSync-=1;
				std::cout << "removed 2:" << sync_FRnumT_index.size() << " " << iSync << std::endl;
			}
		}


		
		
		 		 
		 if(common1) h_sync_summary[2]->Fill(3.0,double(myChannel1));
		 else if(Hcand_pass[i]==2 && i < 2){
				if(doSyncFR){
					  std::cout << "Tight FR: UCL only event of type: " << myChannel1 << " mass = " << mass << " pt = " << Hcand_FR[i].pt << " eta= " << Hcand_FR[i].eta << 
				"jeta= " << ClosestJet.eta << std::endl;
				  h_sync_summary[2]->Fill(0.0,double(myChannel1)); // UCL only
				  Float_t mass = PairMass(Hcand_FR[i],Hcand_FR[i+1]);
					 sync_o_event = m->eventNumber;
					 sync_o_lumi = m->lumiNumber;
					 sync_o_run = m->runNumber;
					
					 sync_o_Channel = myChannel1;
					 sync_o_subChannel = 2;
					 sync_o_HMass = mass;
					 sync_o_l3Pt = Hcand_FR[i].pt;
					 sync_o_l3Eta = Hcand_FR[i].eta;
					 sync_o_l3_CloseJetPt = ClosestJet.pt;
					 sync_o_l3_CloseJetEta = ClosestJet.eta;
					 sync_o_l4Pt = Hcand_FR[i+1].pt;
					 sync_o_l4Eta = Hcand_FR[i+1].eta;
					 sync_o_l4_CloseJetPt = ClosestJet2.pt;
					 sync_o_l4_CloseJetEta = ClosestJet2.eta;
					 
					 syncOutTree->Fill();	
				 }
			  }
		 if(common2) h_sync_summary[2]->Fill(3.0,double(myChannel2));
		 else if(Hcand_pass[i+1] > 0 && i < 2){
				if(doSyncFR){
					  std::cout << "Tight FR: UCL only event of type: " << myChannel2 << " mass = " << mass << " pt = " << Hcand_FR[i+1].pt << " eta= " << Hcand_FR[i+1].eta << 
				"jeta= " << ClosestJet2.eta << std::endl;
				  h_sync_summary[2]->Fill(0.0,double(myChannel2)); // UCL only
				  Float_t mass = PairMass(Hcand_FR[i],Hcand_FR[i+1]);
					 sync_o_event = m->eventNumber;
					 sync_o_lumi = m->lumiNumber;
					 sync_o_run = m->runNumber;
					
					 sync_o_Channel = myChannel2;
					 sync_o_subChannel = 2;
					 sync_o_HMass = mass;
					 sync_o_l3Pt = Hcand_FR[i].pt;
					 sync_o_l3Eta = Hcand_FR[i].eta;
					 sync_o_l3_CloseJetPt = ClosestJet.pt;
					 sync_o_l3_CloseJetEta = ClosestJet.eta;
					 sync_o_l4Pt = Hcand_FR[i+1].pt;
					 sync_o_l4Eta = Hcand_FR[i+1].eta;
					 sync_o_l4_CloseJetPt = ClosestJet2.pt;
					 sync_o_l4_CloseJetEta = ClosestJet2.eta;
					 
					 syncOutTree->Fill();	
				 }
			  }
		
		 if(!correctOrder && doSyncFR && i < 2)
		 {
			if(!common1 && Hcand_pass[i] == 2) h_sync_summary[1]->Fill(1.0,double(myChannel1));
			else if(!common2 && Hcand_pass[i+1] >0) h_sync_summary[1]->Fill(2.0,double(myChannel1));
			else if(Hcand_pass[i]==2 && Hcand_pass[i+1] >0) h_sync_summary[1]->Fill(5.0,double(myChannel1));
		 }
		 
		 if(i<2){
		 switch(exp_event_type)
			{
				case 4:
				case 8:
					barrel1 ? Hist("h_FR_tau_denom")->Fill(ClosestJet.pt) : Hist("h_FR_tau_denom_EC")->Fill(ClosestJet.pt);
					barrel2 ? Hist("h_FR_tau_denom")->Fill(ClosestJet2.pt) : Hist("h_FR_tau_denom_EC")->Fill(ClosestJet2.pt);
					break;
				case 1:
				case 5:
					if(Hcand_pass[i] > -1){ barrel1 ? Hist("h_FR_mu_denom")->Fill(ClosestJet.pt) : Hist("h_FR_mu_denom_EC")->Fill(ClosestJet.pt);} // fill only those passing WZrejection
					if(Hcand_pass[i+1] > -1){ barrel2 ? Hist("h_FR_tauLT_denom")->Fill(ClosestJet2.pt) : Hist("h_FR_tauLT_denom_EC")->Fill(ClosestJet2.pt); } // PT cut on taus
					break;
				case 3:
				case 7:
					if(Hcand_pass[i] > -1){ barrel1 ? Hist("h_FR_el_denom")->Fill(ClosestJet.pt) : Hist("h_FR_el_denom_EC")->Fill(ClosestJet.pt);} // fill only those passing WZrejection
					if(Hcand_pass[i+1] > -1){ barrel2 ? Hist("h_FR_tauLT_denom")->Fill(ClosestJet2.pt) : Hist("h_FR_tauLT_denom_EC")->Fill(ClosestJet2.pt);} // Pt cut on taus
					break;
				default:
					break;
			}
		if(Hcand_pass[i]>0){
			switch(exp_event_type)
			{
				case 4:
				case 8:
					barrel1 ? Hist("h_FR_tau_num")->Fill(ClosestJet.pt) : Hist("h_FR_tau_num_EC")->Fill(ClosestJet.pt);
					break;
				case 1:
				case 5:
					barrel1 ? Hist("h_FR_mu_num")->Fill(ClosestJet.pt) : Hist("h_FR_mu_num_EC")->Fill(ClosestJet.pt);
					break;
				case 3:
				case 7:
					barrel1 ? Hist("h_FR_el_num")->Fill(ClosestJet.pt) : Hist("h_FR_el_num_EC")->Fill(ClosestJet.pt);
					break;
				default:
					break;
			}
		}
		if(Hcand_pass[i]==2){
			switch(exp_event_type)
			{
				
				case 1:
				case 5:
					barrel1 ? Hist("h_FR_muT_num")->Fill(ClosestJet.pt) : Hist("h_FR_muT_num_EC")->Fill(ClosestJet.pt);
					break;
				case 3:
				case 7:
					barrel1 ? Hist("h_FR_elT_num")->Fill(ClosestJet.pt) : Hist("h_FR_elT_num_EC")->Fill(ClosestJet.pt);
					break;
				default:
					break;
			}
		}
		if(Hcand_pass[i+1]==1){
			switch(exp_event_type)
			{
				case 4:
				case 8:
					barrel2 ? Hist("h_FR_tau_num")->Fill(ClosestJet2.pt) : Hist("h_FR_tau_num_EC")->Fill(ClosestJet2.pt);
					break;
				case 1:
				case 5:
					barrel2 ? Hist("h_FR_tauLT_num")->Fill(ClosestJet2.pt) : Hist("h_FR_tauLT_num_EC")->Fill(ClosestJet2.pt);
					break;
				case 3:
				case 7:
					barrel2 ? Hist("h_FR_tauLT_num")->Fill(ClosestJet2.pt) : Hist("h_FR_tauLT_num_EC")->Fill(ClosestJet2.pt);
					break;
				default:
					break;
			}
		}
		}
		 
	}
	// not matched sync objects
		 for(uint iSync = 0; iSync < sync_FRdenom_index.size(); iSync++)
			 {
				std::cout << " ULB only event of type: " << sync_vec_Channel[sync_FRdenom_index[iSync]] << " mass = " << sync_vec_HMass[sync_FRdenom_index[iSync]] 
				<< " pt = " << sync_vec_l3Pt[sync_FRdenom_index[iSync]] << "eta " << sync_vec_l3Eta[sync_FRdenom_index[iSync]] << " jeta " 
				<< sync_vec_l3_CloseJetEta[sync_FRdenom_index[iSync]] << " 2: pt = " << sync_vec_l4Pt[sync_FRdenom_index[iSync]] << "eta " 
				<< sync_vec_l4Eta[sync_FRdenom_index[iSync]] << " jeta " << sync_vec_l4_CloseJetEta[sync_FRdenom_index[iSync]] << std::endl;
				h_sync_summary[1]->Fill(4.0,sync_vec_Channel[sync_FRdenom_index[iSync]]);
			 }
			 
		 	 for(uint iSync = 0; iSync < sync_FRnumL_index.size(); iSync++)
			 {
				std::cout << " ULB only event of type: " << sync_vec_Channel[sync_FRnumL_index[iSync]] << " mass = " << sync_vec_HMass[sync_FRnumL_index[iSync]] 
				<< " pt = " << sync_vec_l3Pt[sync_FRnumL_index[iSync]] << "eta " << sync_vec_l3Eta[sync_FRnumL_index[iSync]]  << " jeta " 
				<< sync_vec_l3_CloseJetEta[sync_FRnumL_index[iSync]] << " 2: pt = " << sync_vec_l4Pt[sync_FRnumL_index[iSync]] << "eta "
				 << sync_vec_l4Eta[sync_FRnumL_index[iSync]] << " jeta " << sync_vec_l4_CloseJetEta[sync_FRnumL_index[iSync]] << std::endl;
				h_sync_summary[3]->Fill(4.0,sync_vec_Channel[sync_FRnumL_index[iSync]]);
			 }
			 
			 for(uint iSync = 0; iSync < sync_FRnumT_index.size(); iSync++)
			 {
				std::cout << " ULB only event of type: " << sync_vec_Channel[sync_FRnumT_index[iSync]] << " mass = " << sync_vec_HMass[sync_FRnumT_index[iSync]] 
				<< " pt = " << sync_vec_l3Pt[sync_FRnumT_index[iSync]] << "eta " << sync_vec_l3Eta[sync_FRnumT_index[iSync]]  << " jeta " 
				<< sync_vec_l3_CloseJetEta[sync_FRnumT_index[iSync]] << " 2: pt = " << sync_vec_l4Pt[sync_FRnumT_index[iSync]] << "eta "
				 << sync_vec_l4Eta[sync_FRnumT_index[iSync]] << " jeta " << sync_vec_l4_CloseJetEta[sync_FRnumT_index[iSync]] << std::endl;
				h_sync_summary[2]->Fill(4.0,sync_vec_Channel[sync_FRnumT_index[iSync]]);
			 }
			 
			 
	
	std::vector<int> sync_cat0_index;
    sync_cat0_index.clear();
	for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
	{
		if(sync_vec_subChannel[iSync]==0) sync_cat0_index.push_back(iSync);
	}
				
	if(examineThisEvent) std::cout << " filling AP histo cat0 " << std::endl;
	for(uint i=0; i < Hcand_cat0.size(); i+=2)
		{
			int exp_event_type=Hcand_type_cat0[i/2];
			myobject ClosestJet = ClosestInCollection(Hcand_cat0[i],jet);
			myobject ClosestJet2 = ClosestInCollection(Hcand_cat0[i+1],jet);
			
			 bool common = false;
			 for(uint iSync = 0; iSync < sync_cat0_index.size() && !common; iSync++)
			 {
				 if(exp_event_type!=2){
				 if((exp_event_type == EventTypeConv(sync_vec_Channel[sync_cat0_index[iSync]]))  && 
					(fabs(Hcand_cat0[i].pt-sync_vec_l3Pt[sync_cat0_index[iSync]]) < 0.1) &&
					(fabs(Hcand_cat0[i].eta-sync_vec_l3Eta[sync_cat0_index[iSync]]) < 0.1) &&
					(fabs(Hcand_cat0[i+1].pt-sync_vec_l4Pt[sync_cat0_index[iSync]]) < 0.1) &&
					(fabs(Hcand_cat0[i+1].eta-sync_vec_l4Eta[sync_cat0_index[iSync]]) < 0.1)
				   ) common = true;//
				}else{
					 if((exp_event_type == EventTypeConv(sync_vec_Channel[sync_cat0_index[iSync]]))  && 
					(fabs(Hcand_cat0[i].pt-sync_vec_l4Pt[sync_cat0_index[iSync]]) < 0.1) &&
					(fabs(Hcand_cat0[i].eta-sync_vec_l4Eta[sync_cat0_index[iSync]]) < 0.1) &&
					(fabs(Hcand_cat0[i+1].pt-sync_vec_l3Pt[sync_cat0_index[iSync]]) < 0.1) &&
					(fabs(Hcand_cat0[i+1].eta-sync_vec_l3Eta[sync_cat0_index[iSync]]) < 0.1)
				   ) common = true;//
				}
				if(common){ // remove matched candidates
					sync_cat0_index.erase(sync_cat0_index.begin()+iSync);
					iSync-=1;
				}
			 }
			
			 
			  if(common) h_sync_summary[0]->Fill(3.0,double(exp_event_type));
			  else if(doSync){
				   h_sync_summary[0]->Fill(0.0,double(exp_event_type)); // UCL only
				   
			   }
			
			bool B1= fabs(ClosestJet.eta) < 1.4 ? true : false; 
			bool B2= fabs(ClosestJet2.eta) < 1.4 ? true : false; 
			switch(exp_event_type)
			{
				case 1: //MT, ET
				case 3:
				case 5:
				case 7: 
					h_category0_pt_types[exp_event_type-1]->Fill(Hcand_cat0[i+1].pt, Hcand_cat0[i].pt); // Tau goes first
					h_category0_jet_pt_types[exp_event_type-1]->Fill(ClosestJet2.pt, ClosestJet.pt); 
					if(B1&&B2) h_category0_jet_BB_pt_types[exp_event_type-1]->Fill(ClosestJet2.pt, ClosestJet.pt);  
					else if(!B1&&B2) h_category0_jet_BE_pt_types[exp_event_type-1]->Fill(ClosestJet2.pt, ClosestJet.pt); // Tau is in the barrel
					else if(B1&&!B2) h_category0_jet_EB_pt_types[exp_event_type-1]->Fill(ClosestJet2.pt, ClosestJet.pt);
					else if(!B1&&!B2) h_category0_jet_EE_pt_types[exp_event_type-1]->Fill(ClosestJet2.pt, ClosestJet.pt);
					h_category0_jetRef_pt_types[exp_event_type-1]->Fill(Hcand_cat0[i+1].jetPt,Hcand_cat0[i].jetPt); 
					break;
				case 2: 
				case 4: 
				case 6: 
				case 8: 
					h_category0_pt_types[exp_event_type-1]->Fill(Hcand_cat0[i].pt, Hcand_cat0[i+1].pt); // tau/electron goes first
					h_category0_jet_pt_types[exp_event_type-1]->Fill(ClosestJet.pt, ClosestJet2.pt);
					if(B1&&B2) h_category0_jet_BB_pt_types[exp_event_type-1]->Fill(ClosestJet.pt, ClosestJet2.pt);  
					else if(!B1&&B2) h_category0_jet_EB_pt_types[exp_event_type-1]->Fill(ClosestJet.pt, ClosestJet2.pt);
					else if(B1&&!B2) h_category0_jet_BE_pt_types[exp_event_type-1]->Fill(ClosestJet.pt, ClosestJet2.pt);
					else if(!B1&&!B2) h_category0_jet_EE_pt_types[exp_event_type-1]->Fill(ClosestJet.pt, ClosestJet2.pt); 
					h_category0_jetRef_pt_types[exp_event_type-1]->Fill(Hcand_cat0[i].jetPt,Hcand_cat0[i+1].jetPt);
					break;
				default:
					break;
			}
		}
		
		 // not matched sync objects
		 for(uint iSync = 0; iSync < sync_cat0_index.size(); iSync++)
			 {
				h_sync_summary[0]->Fill(4.0,double(EventTypeConv(sync_vec_Channel[sync_cat0_index[iSync]])));
			 }
			 
	if(examineThisEvent) std::cout << " filling AP histo cat1 " << std::endl;
	
	std::vector<int> sync_cat1_index;
    sync_cat1_index.clear();
	for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
	{
		if(sync_vec_subChannel[iSync]==1 && ((EventTypeConv(sync_vec_Channel[iSync]))!=2)) sync_cat1_index.push_back(iSync);
		if(sync_vec_subChannel[iSync]==2 && ((EventTypeConv(sync_vec_Channel[iSync])))==2) sync_cat1_index.push_back(iSync);
		
	}
	
	
	
	// messed with categories: cat1 = tau fails or e fails	
	for(uint i=0; i < Hcand_cat1.size(); i+=2)
	{
		int exp_event_type=Hcand_type_cat1[i/2];
		myobject ClosestJet2 = ClosestInCollection(Hcand_cat1[i+1],jet);
		
		bool common = false;
		 
		 for(uint iSync = 0; iSync < sync_cat1_index.size() && !common; iSync++)
		 {
			if(exp_event_type!=2){
			 if((exp_event_type == EventTypeConv(sync_vec_Channel[sync_cat1_index[iSync]]))  && 
				(fabs(Hcand_cat1[i].pt-sync_vec_l3Pt[sync_cat1_index[iSync]]) < 0.1) &&
				(fabs(Hcand_cat1[i].eta-sync_vec_l3Eta[sync_cat1_index[iSync]]) < 0.1) &&
				(fabs(Hcand_cat1[i+1].pt-sync_vec_l4Pt[sync_cat1_index[iSync]]) < 0.1) &&
				(fabs(Hcand_cat1[i+1].eta-sync_vec_l4Eta[sync_cat1_index[iSync]]) < 0.1)
			   ) common = true;//
		   }else{
			 if((exp_event_type == EventTypeConv(sync_vec_Channel[sync_cat1_index[iSync]]))  && 
				(fabs(Hcand_cat1[i].pt-sync_vec_l4Pt[sync_cat1_index[iSync]]) < 0.1) &&
				(fabs(Hcand_cat1[i].eta-sync_vec_l4Eta[sync_cat1_index[iSync]]) < 0.1) &&
				(fabs(Hcand_cat1[i+1].pt-sync_vec_l3Pt[sync_cat1_index[iSync]]) < 0.1) &&
				(fabs(Hcand_cat1[i+1].eta-sync_vec_l3Eta[sync_cat1_index[iSync]]) < 0.1)
			   ) common = true;//
		   }
			if(common){ // remove matched candidates
				sync_cat1_index.erase(sync_cat1_index.begin()+iSync);
				iSync-=1;
			}
		 }
		if(common) h_sync_summary[1]->Fill(3.0,double(exp_event_type));
		else if(doSync){
			 h_sync_summary[1]->Fill(0.0,double(exp_event_type)); // UCL only
				myobject ClosestJet = ClosestInCollection(Hcand_cat1[i],jet);
				Float_t mass = PairMass(Hcand_cat1[i],Hcand_cat1[i+1]);
					 //~ sync_o_event = m->eventNumber;
					 //~ sync_o_lumi = m->lumiNumber;
					 //~ sync_o_run = m->runNumber;
					//~ 
					 //~ sync_o_Channel = EventTypeConvAbdollah(exp_event_type);
					 //~ sync_o_subChannel = 1;
					 //~ sync_o_HMass = mass;
					 //~ if(exp_event_type!=2){
						 //~ sync_o_l3Pt = Hcand_cat1[i].pt;
						 //~ sync_o_l3Eta = Hcand_cat1[i].eta;
						 //~ sync_o_l3_CloseJetPt = ClosestJet.pt;
						 //~ sync_o_l3_CloseJetEta = ClosestJet.eta;
						 //~ sync_o_l4Pt = Hcand_cat1[i+1].pt;
						 //~ sync_o_l4Eta = Hcand_cat1[i+1].eta;
						 //~ sync_o_l4_CloseJetPt = ClosestJet2.pt;
						 //~ sync_o_l4_CloseJetEta = ClosestJet2.eta;
					 //~ }else{
						 //~ sync_o_l4Pt = Hcand_cat1[i].pt;
						 //~ sync_o_l4Eta = Hcand_cat1[i].eta;
						 //~ sync_o_l4_CloseJetPt = ClosestJet.pt;
						 //~ sync_o_l4_CloseJetEta = ClosestJet.eta;
						 //~ sync_o_l3Pt = Hcand_cat1[i+1].pt;
						 //~ sync_o_l3Eta = Hcand_cat1[i+1].eta;
						 //~ sync_o_l3_CloseJetPt = ClosestJet2.pt;
						 //~ sync_o_l3_CloseJetEta = ClosestJet2.eta; 
					 //~ }
					 //~ syncOutTree->Fill();	   
		 
		 }
		
		bool B2= fabs(ClosestJet2.eta) < 1.4 ? true : false; 
		
			h_category1_pt_types[exp_event_type-1]->Fill(Hcand_cat1[i+1].pt); 
			B2? h_category1_jet_pt_types[exp_event_type-1]->Fill(ClosestJet2.pt) : h_category1_jet_EC_pt_types[exp_event_type-1]->Fill(ClosestJet2.pt);
			h_category1_jetRef_pt_types[exp_event_type-1]->Fill(Hcand_cat1[i+1].jetPt);
								
	}
	
	for(uint iSync = 0; iSync < sync_cat1_index.size(); iSync++)
	 {
		h_sync_summary[1]->Fill(4.0,double(EventTypeConv(sync_vec_Channel[sync_cat1_index[iSync]])));
	 }
	
	if(examineThisEvent) std::cout << " filling AP histo cat2 " << std::endl;
	
	std::vector<int> sync_cat2_index;
    sync_cat2_index.clear();
	for(uint iSync=0; iSync < sync_vec_subChannel.size(); iSync++)
	{
		if(sync_vec_subChannel[iSync]==2 && ((EventTypeConv(sync_vec_Channel[iSync]))!=2)) sync_cat2_index.push_back(iSync);
		if(sync_vec_subChannel[iSync]==1 && ((EventTypeConv(sync_vec_Channel[iSync]))==2)) sync_cat2_index.push_back(iSync);
	}
	
	for(uint i=0; i < Hcand_cat2.size(); i+=2)
	{
		int exp_event_type=Hcand_type_cat2[i/2];
		myobject ClosestJet = ClosestInCollection(Hcand_cat2[i],jet);
		
		bool common = false;
			 
		 for(uint iSync = 0; iSync < sync_cat2_index.size() && !common; iSync++)
		 {
			 if(exp_event_type!=2){
			 if((exp_event_type == EventTypeConv(sync_vec_Channel[sync_cat2_index[iSync]]))  && 
				(fabs(Hcand_cat2[i].pt-sync_vec_l3Pt[sync_cat2_index[iSync]]) < 0.1) &&
				(fabs(Hcand_cat2[i].eta-sync_vec_l3Eta[sync_cat2_index[iSync]]) < 0.1) &&
				(fabs(Hcand_cat2[i+1].pt-sync_vec_l4Pt[sync_cat2_index[iSync]]) < 0.1) &&
				(fabs(Hcand_cat2[i+1].eta-sync_vec_l4Eta[sync_cat2_index[iSync]]) < 0.1)
			   ) common = true;//
		   }else{
			if((exp_event_type == EventTypeConv(sync_vec_Channel[sync_cat2_index[iSync]]))  && 
				(fabs(Hcand_cat2[i].pt-sync_vec_l4Pt[sync_cat2_index[iSync]]) < 0.1) &&
				(fabs(Hcand_cat2[i].eta-sync_vec_l4Eta[sync_cat2_index[iSync]]) < 0.1) &&
				(fabs(Hcand_cat2[i+1].pt-sync_vec_l3Pt[sync_cat2_index[iSync]]) < 0.1) &&
				(fabs(Hcand_cat2[i+1].eta-sync_vec_l3Eta[sync_cat2_index[iSync]]) < 0.1)
			   ) common = true;//
		   }
			if(common){ // remove matched candidates
				sync_cat2_index.erase(sync_cat2_index.begin()+iSync);
				iSync-=1;
			}
		 }
		if(common) h_sync_summary[2]->Fill(3.0,double(exp_event_type));
		else if(doSync){
			 h_sync_summary[2]->Fill(0.0,double(exp_event_type)); // UCL only
			Float_t mass = PairMass(Hcand_cat2[i],Hcand_cat2[i+1]);
			myobject ClosestJet2 = ClosestInCollection(Hcand_cat2[i+1],jet);
		
					 //~ sync_o_event = m->eventNumber;
					 //~ sync_o_lumi = m->lumiNumber;
					 //~ sync_o_run = m->runNumber;
					//~ 
					 //~ sync_o_Channel = EventTypeConvAbdollah(exp_event_type);
					 //~ sync_o_subChannel = 2;
					 //~ sync_o_HMass = mass;
					 //~ if(exp_event_type!=2){
						 //~ sync_o_l3Pt = Hcand_cat2[i].pt;
						 //~ sync_o_l3Eta = Hcand_cat2[i].eta;
						 //~ sync_o_l3_CloseJetPt = ClosestJet.pt;
						 //~ sync_o_l3_CloseJetEta = ClosestJet.eta;
						 //~ sync_o_l4Pt = Hcand_cat2[i+1].pt;
						 //~ sync_o_l4Eta = Hcand_cat2[i+1].eta;
						 //~ sync_o_l4_CloseJetPt = ClosestJet2.pt;
						 //~ sync_o_l4_CloseJetEta = ClosestJet2.eta;
					 //~ }else{
						 //~ sync_o_l4Pt = Hcand_cat2[i].pt;
						 //~ sync_o_l4Eta = Hcand_cat2[i].eta;
						 //~ sync_o_l4_CloseJetPt = ClosestJet.pt;
						 //~ sync_o_l4_CloseJetEta = ClosestJet.eta;
						 //~ sync_o_l3Pt = Hcand_cat2[i+1].pt;
						 //~ sync_o_l3Eta = Hcand_cat2[i+1].eta;
						 //~ sync_o_l3_CloseJetPt = ClosestJet2.pt;
						 //~ sync_o_l3_CloseJetEta = ClosestJet2.eta; 
					 //~ }
					 //~ syncOutTree->Fill();	   
		 }
		
		bool B1= fabs(ClosestJet.eta) < 1.4 ? true : false; 
		
		h_category2_pt_types[exp_event_type-1]->Fill(Hcand_cat2[i].pt); 
		B1? h_category2_jet_pt_types[exp_event_type-1]->Fill(ClosestJet.pt) : h_category2_jet_EC_pt_types[exp_event_type-1]->Fill(ClosestJet.pt);
		h_category2_jetRef_pt_types[exp_event_type-1]->Fill(Hcand_cat2[i].jetPt);
		
	}
	
	for(uint iSync = 0; iSync < sync_cat2_index.size(); iSync++)
	 {
		h_sync_summary[2]->Fill(4.0,double(EventTypeConv(sync_vec_Channel[sync_cat2_index[iSync]])));
	 }
	
	
	
        
	return;


}

