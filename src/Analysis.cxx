// $Id: CycleCreators.py 173 2010-05-12 15:49:33Z krasznaa $

// Local include(s):
#include "../include/Analysis.h"

#include "Corrector.h"


ClassImp( Analysis );

Analysis::Analysis()
	: SCycleBase(), m_allEvents( "allEvents", this )
	 {

		SetLogName( GetName() );
		DeclareProperty("InTreeName",InTreeName);
		DeclareProperty("maxDeltaR",maxDeltaR);
		DeclareProperty("maxDeltaR_H",maxDeltaR_H);
		DeclareProperty("MyPtCut",Ptcut);
		DeclareProperty("BestMassForZ",BestMassForZ);
		DeclareProperty("dZvertex", dZvertex);
		DeclareProperty("bTagValue",bTagValue);
		DeclareProperty("p0_tight",p0_tight);
		DeclareProperty("p1_tight",p1_tight);
		DeclareProperty("p2_tight",p2_tight);
		DeclareProperty("p0_medium",p0_medium);
		DeclareProperty("p1_medium",p1_medium);
		DeclareProperty("p2_medium",p2_medium);
		DeclareProperty("FR_MMed",FR_MMed);
		DeclareProperty("FR_MTig",FR_MTig);
		DeclareProperty("FR_EMed",FR_EMed);
		DeclareProperty("FR_ETig",FR_ETig);

		DeclareProperty("ElectronTriggerName", doubEle);
		DeclareProperty("ElectronTriggerName2", doubEle2);

		DeclareProperty("MuonTriggerName1", doubMu);
		DeclareProperty("MuonTriggerName2", doubMu2);
		DeclareProperty("MuonTriggerName3", doubMu3);

		DeclareProperty("switchToFakeRate",switchToFakeRate);
		DeclareProperty("checkCategories",checkCategories);
		DeclareProperty("isSimulation",isSimulation);
		DeclareProperty("is2011",is2011);
		DeclareProperty("is2012_52",is2012_52);
		DeclareProperty("is2012_53",is2012_53);
		DeclareProperty("useTruePileUp",useTruePileUp);
		DeclareProperty("vetoMuonTrigger",vetoMuonTrigger);
		DeclareProperty("vetoElectronTrigger", vetoElectronTrigger);
		
		DeclareProperty("Cut_tau_base_Pt",Cut_tau_base_Pt);
		DeclareProperty("Cut_tautau_Pt_1",Cut_tautau_Pt_1);
		DeclareProperty("Cut_tautau_Pt_2",Cut_tautau_Pt_2);
		DeclareProperty("Cut_tautau_MVA_iso",Cut_tautau_MVA_iso); 	
		DeclareProperty("AllowTauBOverlap",AllowTauBOverlap);
		
		DeclareProperty("Cut_tautau_sumPt",Cut_tautau_sumPt);
		DeclareProperty("Cut_leptau_sumPt",Cut_leptau_sumPt);
		DeclareProperty("Cut_leplep_sumPt",Cut_leplep_sumPt);
		DeclareProperty("UseSumPtCut",UseSumPtCut);
		DeclareProperty("IgnoreAdditionalTaus",IgnoreAdditionalTaus);
		DeclareProperty("IgnoreSF",IgnoreSF);
		DeclareProperty("IgnorePUW",IgnorePUW);
		DeclareProperty("printoutEvents",printoutEvents);
		DeclareProperty("examineEvent",examineEvent);
		DeclareProperty("removeTauOverlap",removeTauOverlap);
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
		default: return -1;	
	}
}

void Analysis::BeginInputData( const SInputData& ) throw( SError ) {

	h_deltaR                       			 = Book(TH1D("h_deltaR","deltaR distributions", 100,0,10));
	h_deltaR_max                    		 = Book(TH1D("h_deltaR_max","maxDeltaR distributions", 100,0,10));
	h_deltaR_min                    		 = Book(TH1D("h_deltaR_min","minDeltaR distributions", 100,0,10));

	h_cut_flow                      		 = Book(TH1D("h_cut_flow","Cut Flow",11,-0.5,10.5));
	h_cut_flow_weight               		 = Book(TH1D("h_cut_flow_weight","Cut Flow Weighted",11,-0.5,10.5));

	h_cut_flow_signal 				 = Book(TH1D("h_cut_flow_signal","Cut Flow signal",4,0.5,4.5));
	h_cut_flow_cat0					 = Book(TH1D("h_cut_flow_cat0","Cut Flow cat0",4,0.5,4.5));
	h_cut_flow_cat1					 = Book(TH1D("h_cut_flow_cat1","Cut Flow cat1",4,0.5,4.5));
	h_cut_flow_cat2					 = Book(TH1D("h_cut_flow_cat2","Cut Flow cat2",4,0.5,4.5));

	h_cut_flow_signal_weight			 = Book(TH1D("h_cut_flow_signal_weight","Cut Flow signal",4,0.5,4.5));
	h_cut_flow_cat0_weight				 = Book(TH1D("h_cut_flow_cat0_weight","Cut Flow signal",4,0.5,4.5));
	h_cut_flow_cat1_weight			 	 = Book(TH1D("h_cut_flow_cat1_weight","Cut Flow signal",4,0.5,4.5));
	h_cut_flow_cat2_weight			 	 = Book(TH1D("h_cut_flow_cat2_weight","Cut Flow signal",4,0.5,4.5));

	h_cat0_FR_medium 				 = Book(TH1D("h_cat0_FR_medium","cat0 with FR medium corrections",8,0.5,8.5));
	h_cat1_FR_medium				 = Book(TH1D("h_cat1_FR_medium","cat1 with FR medium corrections",8,0.5,8.5));
	h_cat2_FR_medium				 = Book(TH1D("h_cat2_FR_medium","cat2 with FR medium corrections",8,0.5,8.5));
	h_cat0_FR_tight 				 = Book(TH1D("h_cat0_FR_tight","cat0 with FR tight corrections",8,0.5,8.5));
	h_cat1_FR_tight 				 = Book(TH1D("h_cat1_FR_tight","cat1 with FR tight corrections",8,0.5,8.5));
	h_cat2_FR_tight 				 = Book(TH1D("h_cat2_FR_tight","cat2 with FR tight corrections",8,0.5,8.5));

	h_el_n              				 = Book(TH1D("el_n","el_n",50,0,50));
	h_el_cut            				 = Book(TH1D("el_cit","el_cut",50,0,50));
	h_event_type        	      		  	 = Book(TH1D("h_event_type","Event Type",8,0.5,8.5));
	h_event_type_raw        			 = Book(TH1D("h_event_type_raw","Event Type (no weights)",8,0.5,8.5));
	h_event_type_loose 			         = Book(TH1D("h_event_type_loose","Event Type passing iso < 0.3",8,0.5,8.5));
	h_event_type_medium 			         = Book(TH1D("h_event_type_medium","Event Type passing medium iso",8,0.5,8.5));
	h_event_type_tight  				 = Book(TH1D("h_event_type_tight","Event Type passing iso < 0.1 ",8,0.5,8.5));
	
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
	h_Zmass     		        		 = Book(TH1D("h_Zmass","Z_mass",60,60,120));
	h_Zpt            		   		 = Book(TH1D("h_Zpt","Z_pt",300,0,300));

	h_Z_eta						 = Book(TH1D("h_Z_eta","H #eta; #eta",100,-3.0,3.0));
	h_Z_phi						 = Book(TH1D("h_Z_phi","H #phi; #phi",64,-3.2,3.2));

	h_Z_lep1_eta					 = Book(TH1D("h_Z_lep1_eta","H #eta; #eta",100,-3.0,3.0));
	h_Z_lep1_phi					 = Book(TH1D("h_Z_lep1_phi","H #phi; #phi",64,-3.2,3.2));	

	h_Z_lep2_eta					 = Book(TH1D("h_Z_lep2_eta","H #eta; #eta",100,-3.0,3.0));
	h_Z_lep2_phi					 = Book(TH1D("h_Z_lep2_phi","H #phi; #phi",64,-3.2,3.2));

	//H->eTau
	h_eH_eTau_pt        				 = Book(TH1D("h_eH_eTau_pt","H->e tau, ele pt",100,0,300));
	h_tauH_eTau_pt      				 = Book(TH1D("h_tauH_eTau_pt","H->e tau, tau pt",100,0,300));
	h_H_eTau_pt         				 = Book(TH1D("h_H_eTau_pt","H->e tau, H pt",100,0,300));
	h_H_eTau_mass       				 = Book(TH1D("h_H_eTau_mass","H->e tau, H visible mass",100,0,300));
	//H->muTau
	h_muH_muTau_pt      				 = Book(TH1D("h_muH_muTau_pt","H->mu tau, mu pt",100,0,300));
	h_tauH_muTau_pt     				 = Book(TH1D("h_tauH_muTau_pt","H->mu tau, tau pt",100,0,300));
	h_H_muTau_pt        				 = Book(TH1D("h_H_muTau_pt","H->mu tau, H pt",100,0,300));
	h_H_muTau_mass      				 = Book(TH1D("h_H_muTau_mass","H->mu tau, H visible mass",100,0,300));
	//H->muE relIso(mu)<0.15
	h_muH_muE_tightMuIso_pt         		 = Book(TH1D("h_muH_muE_tightMuIso_pt","H->mu e, mu pt",100,0,300));
	h_eH_muE_tightMuIso_pt          		 = Book(TH1D("h_eH_muE_tightMuIso_pt","H->mu e, e pt",100,0,300));
	h_H_muE_tightMuIso_pt           		 = Book(TH1D("h_H_muE_tightMuIso_pt","H->mu e, H pt",100,0,300));
	h_H_muE_tightMuIso_mass         		 = Book(TH1D("h_H_muE_tightMuIso_mass","H->mu e, H visible mass",100,0,300));
	//H->muE relIso(mu)<0.25
	h_muH_muE_looseMuIso_pt         		 = Book(TH1D("h_muH_muE_looseMuIso_pt","H->mu e, mu pt",100,0,300));
	h_eH_muE_looseMuIso_pt          		 = Book(TH1D("h_eH_muE_looseMuIso_pt","H->mu e, e pt",100,0,300));
	h_H_muE_looseMuIso_pt           	 	 = Book(TH1D("h_H_muE_looseMuIso_pt","H->mu e, H pt",100,0,300));
	h_H_muE_looseMuIso_mass         		 = Book(TH1D("h_H_muE_looseMuIso_mass","H->mu e, H visible mass",100,0,300));
	//H->tauTau
	h_tau1H_tauTau_pt   				 = Book(TH1D("h_tau1H_tauTau_pt","H->tau tau, tau1 pt",100,0,300));
	h_tau2H_tauTau_pt   				 = Book(TH1D("h_tau2H_tauTau_pt","H->tau tau, tau2 pt",100,0,300));
	h_H_tauTau_pt       				 = Book(TH1D("h_H_tauTau_pt","H->tau tau, H pt",100,0,300));
	h_H_tauTau_mass    				 = Book(TH1D("h_H_tauTau_mass","H->tau tau, H visible mass",100,0,300));
	//Higgs
	h_H_pt           				 = Book(TH1D("h_H_pt","H pt (all final states)",100,0,300));
	h_H_mass         				 = Book(TH1D("h_H_mass","H mass (all final states)",100,0,300));

	h_H_eta						 = Book(TH1D("h_H_eta","H #eta; #eta",100,-3.0,3.0));
	h_H_phi						 = Book(TH1D("h_H_phi","H #phi; #phi",64,-3.2,3.2));
	h_H_lep1_eta					 = Book(TH1D("h_H_lep1_eta","H #eta; #eta",100,-3.0,3.0));
	h_H_lep1_phi					 = Book(TH1D("h_H_lep1_phi","H #phi; #phi",64,-3.2,3.2));	
	h_H_lep2_eta					 = Book(TH1D("h_H_lep2_eta","H #eta; #eta",100,-3.0,3.0));
	h_H_lep2_phi					 = Book(TH1D("h_H_lep2_phi","H #phi; #phi",64,-3.2,3.2));

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
	h_nbjets                        		 = Book(TH1D("h_nbjets", "# of b-jets",10,0,10));
	h_nbjets_afterVeto              		 = Book(TH1D("h_nbjets_afterVeto", "# of b-jets remaining after b-tag Veto",10,0,10));
	h_nbjets_signal                        		 = Book(TH1D("h_nbjets_signal", "# of b-jets",10,0,10));
	h_nbjets_afterVeto_signal              		 = Book(TH1D("h_nbjets_afterVeto_signal", "# of b-jets remaining after b-tag Veto",10,0,10));
	h_nbjetsVetoed                  		 = Book(TH1D("h_nbjetsVetoed", "# of b-jets removed from b-tag Veto",10,0,10));

	h_Tmass						 = Book(TH1D("h_Tmass","Transverse mass of leading lepton;Transverse mass[GeV]",100,0,200));

        h_nPU_Info                      		 = Book(TH1D("h_nPU_Info","PU info distribution",50,0,50));
        h_nPU_InfoTrue                  		 = Book(TH1D("h_nPU_InfoTrue","PU info True distribution",50,0,50));
        h_nPU_Bunch0                    		 = Book(TH1D("h_nPU_Bunch0","PU info Bunch0 distribution",50,0,50));
        h_nPU_Info_W                    		 = Book(TH1D("h_nPU_Info_W","PU info distribution reweighted",50,0,50));
        h_nPU_InfoTrue_W               			 = Book(TH1D("h_nPU_InfoTrue_W","PU info True distribution reweighted",50,0,50));
        h_nPU_Bunch0_W                 			 = Book(TH1D("h_nPU_Bunch0_W","PU info Bunch0 distribution reweighted",50,0,50));

	h_signal_pt1					 = Book(TH1D("h_signal_pt1", " Pt distribution in signal region; P_{T}[GeV]",100,0,100));
	h_signal_pt2					 = Book(TH1D("h_signal_pt2", " Pt distribution in signal region; P_{T}[GeV]",100,0,100));

	h_category0_pt					 = Book(TH2D("h_category0_pt", " Pt distribution in category0 region;P_{T1}[GeV];P_{T2}[GeV]",100,0,100,100,0,100));
	h_category1_pt					 = Book(TH1D("h_category1_pt", " Pt distribution in category1 region; P_{T}[GeV]",100,0,100));
	h_category2_pt					 = Book(TH1D("h_category2_pt", " Pt distribution in category2 region; P_{T}[GeV]",100,0,100));

        h_medium                                	 = Book(TH1D("h_medium","Medium iso",100,0,100));
        h_tight                                 	 = Book(TH1D("h_tight", "Tight iso", 100,0,100));
        h_denom                                          = Book(TH1D("h_denom", "Denominator", 100,0,100));

       h_denom_types.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_denom_type_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_denom_types.push_back(h_temp);
        }
       h_denom_types_eta.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_denom_type_ETA_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";#eta";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,-3,3));
                h_denom_types_eta.push_back(h_temp);
        }
       h_denom_types_centralEtaRegion.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_denom_type_centralEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_denom_types_centralEtaRegion.push_back(h_temp);
        }
       h_denom_types_externalEtaRegion.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_denom_type_externalEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_denom_types_externalEtaRegion.push_back(h_temp);
        }
        //////////////////////////////////
       h_denom_jet_types.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_denom_jet_type_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_denom_jet_types.push_back(h_temp);
        }
       h_denom_jet_types_eta.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_denom_jet_type_ETA_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";#eta";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,-3,3));
                h_denom_jet_types_eta.push_back(h_temp);
        }
       h_denom_jet_types_centralEtaRegion.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_denom_jet_type_centralEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_denom_jet_types_centralEtaRegion.push_back(h_temp);
        }
       h_denom_jet_types_externalEtaRegion.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_denom_jet_type_externalEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_denom_jet_types_externalEtaRegion.push_back(h_temp);
        }
        ///////////////////////////
               h_denom_jetRef_types.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_denom_jetRef_type_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_denom_jetRef_types.push_back(h_temp);
        }
       h_denom_jetRef_types_eta.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_denom_jetRef_type_ETA_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";#eta";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,-3,3));
                h_denom_jetRef_types_eta.push_back(h_temp);
        }
       h_denom_jetRef_types_centralEtaRegion.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_denom_jetRef_type_centralEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_denom_jetRef_types_centralEtaRegion.push_back(h_temp);
        }
       h_denom_jetRef_types_externalEtaRegion.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_denom_jetRef_type_externalEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_denom_jetRef_types_externalEtaRegion.push_back(h_temp);
        }
        
        //loose
        h_loose_types.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_loose_type_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.3 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_loose_types.push_back(h_temp);
        }
        h_loose_types_eta.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_loose_type_ETA_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.3 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";#eta";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,-3,3));
                h_loose_types_eta.push_back(h_temp);
        }
        h_loose_types_centralEtaRegion.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_loose_type_centralEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.3 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_loose_types_centralEtaRegion.push_back(h_temp);
        }
        h_loose_types_externalEtaRegion.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_loose_type_externalEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.3 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_loose_types_externalEtaRegion.push_back(h_temp);
        }
        
         //loose_jet
        h_loose_jet_types.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_loose_jet_type_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.3 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_loose_jet_types.push_back(h_temp);
        }
        h_loose_jet_types_eta.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_loose_jet_type_ETA_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.3 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";#eta";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,-3,3));
                h_loose_jet_types_eta.push_back(h_temp);
        }
        h_loose_jet_types_centralEtaRegion.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_loose_jet_type_centralEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.3 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_loose_jet_types_centralEtaRegion.push_back(h_temp);
        }
        h_loose_jet_types_externalEtaRegion.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_loose_jet_type_externalEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.3 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_loose_jet_types_externalEtaRegion.push_back(h_temp);
        }
        
         //loose_jetRef
        h_loose_jetRef_types.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_loose_jetRef_type_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.3 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_loose_jetRef_types.push_back(h_temp);
        }
        h_loose_jetRef_types_eta.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_loose_jetRef_type_ETA_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.3 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";#eta";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,-3,3));
                h_loose_jetRef_types_eta.push_back(h_temp);
        }
        h_loose_jetRef_types_centralEtaRegion.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_loose_jetRef_type_centralEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.3 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_loose_jetRef_types_centralEtaRegion.push_back(h_temp);
        }
        h_loose_jetRef_types_externalEtaRegion.clear();
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_loose_jetRef_type_externalEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.3 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_loose_jetRef_types_externalEtaRegion.push_back(h_temp);
        }
		// medium
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_medium_type_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Medium iso for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_medium_types.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_medium_type_ETA_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Medium iso for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";#eta";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,-3,3));
                h_medium_types_eta.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_medium_type_centralEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Medium iso for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_medium_types_centralEtaRegion.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_medium_type_externalEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Medium iso for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_medium_types_externalEtaRegion.push_back(h_temp);
        }

        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_tight_type_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.1 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_tight_types.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_tight_type_ETA_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.1 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";#eta";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,-3,3));
                h_tight_types_eta.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_tight_type_centralEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.1 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_tight_types_centralEtaRegion.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_tight_type_externalEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.1 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_tight_types_externalEtaRegion.push_back(h_temp);
        }
        
        //m+t jet
        
         for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_medium_type_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Medium iso for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_medium_jet_types.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_medium_type_ETA_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Medium iso for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";#eta";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,-3,3));
                h_medium_jet_types_eta.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_medium_type_centralEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Medium iso for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_medium_jet_types_centralEtaRegion.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_medium_type_externalEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Medium iso for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_medium_jet_types_externalEtaRegion.push_back(h_temp);
        }

        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_tight_type_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.1 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_tight_jet_types.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_tight_type_ETA_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.1 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";#eta";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,-3,3));
                h_tight_jet_types_eta.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_tight_type_centralEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.1 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_tight_jet_types_centralEtaRegion.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_tight_type_externalEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.1 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_tight_jet_types_externalEtaRegion.push_back(h_temp);
        }
        
        //jetRef
        
         for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_medium_type_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Medium iso for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_medium_jetRef_types.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_medium_type_ETA_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Medium iso for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";#eta";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,-3,3));
                h_medium_jetRef_types_eta.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_medium_type_centralEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Medium iso for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_medium_jetRef_types_centralEtaRegion.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_medium_type_externalEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Medium iso for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_medium_jetRef_types_externalEtaRegion.push_back(h_temp);
        }

        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_tight_type_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.1 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_tight_jetRef_types.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_tight_type_ETA_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.1 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";#eta";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,-3,3));
                h_tight_jetRef_types_eta.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_tight_type_centralEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.1 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_tight_jetRef_types_centralEtaRegion.push_back(h_temp);
        }
        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_tight_type_externalEtaRegion_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.1 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
                std::string title = ss.str();
                TH1D* h_temp =  Book(TH1D(TString(name),TString(title),100,0.,100.));
                h_tight_jetRef_types_externalEtaRegion.push_back(h_temp);
        }

	h_category0_pt=Retrieve<TH2D>("h_category0_pt");

	h_Nvertex_NoCut = Book(TH1D("h_Nvertex_NoCut","Number of vertices - no cut", 50, -0.5,49.5));
	h_Nvertex_NoCut_W = Book(TH1D("h_Nvertex_NoCut_W","Number of vertices - no cut (PU weight)", 50, -0.5,49.5));
	h_Nvertex_AfterZ = Book(TH1D("h_Nvertex_AfterZ","Number of vertices - selected Z", 50, -0.5,49.5));
	h_Nvertex_AfterZ_W = Book(TH1D("h_Nvertex_AfterZ_W","Number of vertices - selected Z (PU weight)", 50, -0.5,49.5));
	h_Nvertex_AfterZH = Book(TH1D("h_Nvertex_AfterZH","Number of vertices - selected Z and H", 50, -0.5,49.5));
	h_Nvertex_AfterZH_W = Book(TH1D("h_Nvertex_AfterZH_W","Number of vertices - selected Z and H (PU weight)", 50, -0.5,49.5));

	DeclareVariable(out_pt,"el_pt");

	h_cut_flow = Retrieve<TH1D>("h_cut_flow");
	h_cut_flow->GetXaxis()->SetBinLabel(1, "Initial Events");
	h_cut_flow->GetXaxis()->SetBinLabel(2, "trigger");
	h_cut_flow->GetXaxis()->SetBinLabel(3, "good vx");
	h_cut_flow->GetXaxis()->SetBinLabel(4, "Z cand");
	h_cut_flow->GetXaxis()->SetBinLabel(5, "Exc. Event type BC");
	h_cut_flow->GetXaxis()->SetBinLabel(6, "Exc. Event type AC");
	h_cut_flow->GetXaxis()->SetBinLabel(7, "H cand");
	h_cut_flow->GetXaxis()->SetBinLabel(8, "Add. Leptons");
	h_cut_flow->GetXaxis()->SetBinLabel(9, "Same Vertex");
	h_cut_flow->GetXaxis()->SetBinLabel(10, "B-Tag Veto");
	h_cut_flow->GetXaxis()->SetBinLabel(11, "Final Events");

        h_cut_flow_weight = Retrieve<TH1D>("h_cut_flow_weight");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(1, "Initial Events");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(2, "trigger");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(3, "good vx");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(4, "Z cand");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(5, "Exc. Event type BC");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(6, "Exc. Event type AC");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(7, "H cand");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(8, "Add. Leptons");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(9, "Same Vertex");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(10, "B-Tag Veto");
	h_cut_flow_weight->GetXaxis()->SetBinLabel(11, "Final Events");


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

        h_event_type_loose = Retrieve<TH1D>("h_event_type_loose");
        h_event_type_loose->GetXaxis()->SetBinLabel(1,"Z(#mu#mu)H(#mu#tau)");
        h_event_type_loose->GetXaxis()->SetBinLabel(2,"Z(#mu#mu)H(#mu e)");
        h_event_type_loose->GetXaxis()->SetBinLabel(3,"Z(#mu#mu)H(e#tau)");
        h_event_type_loose->GetXaxis()->SetBinLabel(4,"Z(#mu#mu)H(#tau#tau)");
        h_event_type_loose->GetXaxis()->SetBinLabel(5,"Z(ee)H(#mu#tau)");
        h_event_type_loose->GetXaxis()->SetBinLabel(6,"Z(ee)H(#mu e)");
        h_event_type_loose->GetXaxis()->SetBinLabel(7,"Z(ee)H(e#tau)");
        h_event_type_loose->GetXaxis()->SetBinLabel(8,"Z(ee)H(#tau#tau)");
        
        h_event_type_medium = Retrieve<TH1D>("h_event_type_medium");
        h_event_type_medium->GetXaxis()->SetBinLabel(1,"Z(#mu#mu)H(#mu#tau)");
        h_event_type_medium->GetXaxis()->SetBinLabel(2,"Z(#mu#mu)H(#mu e)");
        h_event_type_medium->GetXaxis()->SetBinLabel(3,"Z(#mu#mu)H(e#tau)");
        h_event_type_medium->GetXaxis()->SetBinLabel(4,"Z(#mu#mu)H(#tau#tau)");
        h_event_type_medium->GetXaxis()->SetBinLabel(5,"Z(ee)H(#mu#tau)");
        h_event_type_medium->GetXaxis()->SetBinLabel(6,"Z(ee)H(#mu e)");
        h_event_type_medium->GetXaxis()->SetBinLabel(7,"Z(ee)H(e#tau)");
        h_event_type_medium->GetXaxis()->SetBinLabel(8,"Z(ee)H(#tau#tau)");

        h_event_type_tight = Retrieve<TH1D>("h_event_type_tight");
        h_event_type_tight->GetXaxis()->SetBinLabel(1,"Z(#mu#mu)H(#mu#tau)");
        h_event_type_tight->GetXaxis()->SetBinLabel(2,"Z(#mu#mu)H(#mu e)");
        h_event_type_tight->GetXaxis()->SetBinLabel(3,"Z(#mu#mu)H(e#tau)");
        h_event_type_tight->GetXaxis()->SetBinLabel(4,"Z(#mu#mu)H(#tau#tau)");
        h_event_type_tight->GetXaxis()->SetBinLabel(5,"Z(ee)H(#mu#tau)");
        h_event_type_tight->GetXaxis()->SetBinLabel(6,"Z(ee)H(#mu e)");
        h_event_type_tight->GetXaxis()->SetBinLabel(7,"Z(ee)H(e#tau)");
        h_event_type_tight->GetXaxis()->SetBinLabel(8,"Z(ee)H(#tau#tau)");



	h_PF_MET_nPU=Retrieve<TProfile>("h_PF_MET_nPU");
	h_PF_MET_nPU_selected=Retrieve<TProfile>("h_PF_MET_nPU_selected");

	h_cut_flow_signal=Retrieve<TH1D>("h_cut_flow_signal");
	h_cut_flow_cat0=Retrieve<TH1D>("h_cut_flow_cat0");
	h_cut_flow_cat1=Retrieve<TH1D>("h_cut_flow_cat1");
	h_cut_flow_cat2=Retrieve<TH1D>("h_cut_flow_cat2");
	
	h_cut_flow_signal_weight=Retrieve<TH1D>("h_cut_flow_signal_weight");
	h_cut_flow_cat0_weight=Retrieve<TH1D>("h_cut_flow_cat0_weight");
	h_cut_flow_cat1_weight=Retrieve<TH1D>("h_cut_flow_cat1_weight");
	h_cut_flow_cat2_weight=Retrieve<TH1D>("h_cut_flow_cat2_weight");
	
	h_cat0_FR_medium=Retrieve<TH1D>("h_cat0_FR_medium");
	h_cat1_FR_medium=Retrieve<TH1D>("h_cat1_FR_medium");
	h_cat2_FR_medium=Retrieve<TH1D>("h_cat2_FR_medium");
	h_cat0_FR_tight=Retrieve<TH1D>("h_cat0_FR_tight");
	h_cat1_FR_tight=Retrieve<TH1D>("h_cat1_FR_tight");
	h_cat2_FR_tight=Retrieve<TH1D>("h_cat2_FR_tight");

	h_H_mass_types.clear();
	h_H_mass_signal_types.clear();
	h_H_mass_cat0_types.clear();
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
		std::stringstream s,sig_1,sig_2,cat0,cat1,cat2,mass_sig,mass_cat0,mass_cat1,mass_cat2,sumPt;
		s << "h_H_mass_type_" << i;
		mass_sig << "h_H_mass_signal_type_" << i;
		mass_cat0 << "h_H_mass_cat0_type_" << i;
		mass_cat1 << "h_H_mass_cat1_type_" << i;
		mass_cat2 << "h_H_mass_cat2_type_" << i;
		
		sig_1 << "h_signal_pt1_" << i;
		sig_2 << "h_signal_pt2_" << i;
		sumPt << "h_signal_SumPt_" << i;
		cat0 << "h_category0_pt_" << i;
		cat1 << "h_category1_pt_" << i;
		cat2 << "h_category2_pt_" << i;
		
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
		
		std::stringstream ss,tit_sig_1,tit_sig_2,tit_cat0,tit_cat1,tit_cat2,tit_sumPt;
		ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";m_{H}[GeV]";
		
		tit_sig_1 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
		tit_sig_2 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
		tit_sumPt << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
		tit_cat0 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T1}[GeV];P_{T2}[GeV]";
		tit_cat1 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
		tit_cat2 << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}[GeV]";
			
		std::string title = ss.str();
		std::string title_sig_1 = tit_sig_1.str(); 
		std::string title_sig_2 = tit_sig_2.str(); 
		std::string title_SumPt = tit_sig_2.str(); 
		std::string title_cat0 = tit_cat0.str(); 
		std::string title_cat1 = tit_cat1.str(); 
		std::string title_cat2 = tit_cat2.str();
		
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
		
		h_H_mass_types.push_back(h_temp);
		h_H_mass_signal_types.push_back(h_mass_sig_temp);
		h_H_mass_cat0_types.push_back(h_mass_cat0_temp);
		h_H_mass_cat1_types.push_back(h_mass_cat1_temp);
		h_H_mass_cat2_types.push_back(h_mass_cat2_temp);
		
		h_signal_pt1_types.push_back(h_signal_temp_pt1);
		h_signal_pt2_types.push_back(h_signal_temp_pt2);
		h_signal_SumPt_types.push_back(h_signal_temp_SumPt);
        
		h_category0_pt_types.push_back(h_category0_temp_pt);
		h_category1_pt_types.push_back(h_category1_temp_pt);
		h_category2_pt_types.push_back(h_category2_temp_pt);
    
		
	}


	// Lumi weights

	if(is2012_52) LumiWeights_ = new reweight::LumiReWeighting("Summer12_PU.root", "dataPileUpHistogram_True_2012.root","mcPU","pileup");
	else if (useTruePileUp && is2011) LumiWeights_ = new reweight::LumiReWeighting("Fall11_PU.root", "dataPileUpHistogram_True_2011.root","mcPU","pileup");
	else if (!useTruePileUp && is2011) LumiWeights_ = new reweight::LumiReWeighting("Fall11_PU_observed.root", "dataPileUpHistogram_Observed_2011.root","mcPU","pileup");
	else LumiWeights_ = new reweight::LumiReWeighting("Summer12_PU_53X.root", "dataPileUpHistogramABCD_True_2012.root","mcPU","pileup");

	if(printoutEvents){
		 log1.open("events.txt");
		 log_events.open("eventlist.txt");
		 log_files.open("filelist.txt");
	 }
	
	//bookkeeping
	lumi.open("lumi.csv");
	current_run=current_lumi=-999;
	
	
	
	return;

}

void Analysis::EndInputData( const SInputData& ) throw( SError ) {

	std::cout << "Event type summary: " << std::endl;
	std::cout << "Z(mumu)H(mutau)   : " << h_event_type->GetBinContent(1) << std::endl;
	std::cout << "Z(mumu)H(muE)     : " << h_event_type->GetBinContent(2) << std::endl;
	std::cout << "Z(mumu)H(Etau)    : " << h_event_type->GetBinContent(3) << std::endl;
	std::cout << "Z(mumu)H(tautau)  : " << h_event_type->GetBinContent(4) << std::endl;
	std::cout << "Z(EE)H(mutau)     : " << h_event_type->GetBinContent(5) << std::endl;
	std::cout << "Z(EE)H(muE)       : " << h_event_type->GetBinContent(6) << std::endl;
	std::cout << "Z(EE)H(Etau)      : " << h_event_type->GetBinContent(7) << std::endl;
	std::cout << "Z(EE)H(tautau)    : " << h_event_type->GetBinContent(8) << std::endl;

	std::cout << "Iso < 0.3 summary: " << std::endl;
       
        std::cout << "Z(mumu)H(mutau)   : " << h_event_type_loose->GetBinContent(1) << std::endl;
        std::cout << "Z(mumu)H(eMu)     : " << h_event_type_loose->GetBinContent(2) << std::endl;
        std::cout << "Z(mumu)H(Etau)    : " << h_event_type_loose->GetBinContent(3) << std::endl;
        std::cout << "Z(mumu)H(tautau)  : " << h_event_type_loose->GetBinContent(4) << std::endl;
        std::cout << "Z(EE)H(mutau)     : " << h_event_type_loose->GetBinContent(5) << std::endl;
        std::cout << "Z(EE)H(eMu)       : " << h_event_type_loose->GetBinContent(6) << std::endl;
        std::cout << "Z(EE)H(Etau)      : " << h_event_type_loose->GetBinContent(7) << std::endl;
        std::cout << "Z(EE)H(tautau)    : " << h_event_type_loose->GetBinContent(8) << std::endl;
       
    std::cout << "Medium iso summary: " << std::endl;
       
        std::cout << "Z(mumu)H(mutau)   : " << h_event_type_medium->GetBinContent(1) << std::endl;
        std::cout << "Z(mumu)H(eMu)     : " << h_event_type_medium->GetBinContent(2) << std::endl;
        std::cout << "Z(mumu)H(Etau)    : " << h_event_type_medium->GetBinContent(3) << std::endl;
        std::cout << "Z(mumu)H(tautau)  : " << h_event_type_medium->GetBinContent(4) << std::endl;
        std::cout << "Z(EE)H(mutau)     : " << h_event_type_medium->GetBinContent(5) << std::endl;
        std::cout << "Z(EE)H(eMu)       : " << h_event_type_medium->GetBinContent(6) << std::endl;
        std::cout << "Z(EE)H(Etau)      : " << h_event_type_medium->GetBinContent(7) << std::endl;
        std::cout << "Z(EE)H(tautau)    : " << h_event_type_medium->GetBinContent(8) << std::endl;

        std::cout << "Iso < 0.1 summary: " << std::endl;
        std::cout << "Z(mumu)H(mutau)   : " << h_event_type_tight->GetBinContent(1) << std::endl;
        std::cout << "Z(mumu)H(eMu)     : " << h_event_type_tight->GetBinContent(2) << std::endl;
        std::cout << "Z(mumu)H(Etau)    : " << h_event_type_tight->GetBinContent(3) << std::endl;
        std::cout << "Z(mumu)H(tautau)  : " << h_event_type_tight->GetBinContent(4) << std::endl;
        std::cout << "Z(EE)H(mutau)     : " << h_event_type_tight->GetBinContent(5) << std::endl;
        std::cout << "Z(EE)H(eMu)       : " << h_event_type_tight->GetBinContent(6) << std::endl;
        std::cout << "Z(EE)H(Etau)      : " << h_event_type_tight->GetBinContent(7) << std::endl;
        std::cout << "Z(EE)H(tautau)    : " << h_event_type_tight->GetBinContent(8) << std::endl;

        
        h_medium=Retrieve<TH1D>("h_medium");
        h_tight=Retrieve<TH1D>("h_tight");
        h_denom=Retrieve<TH1D>("h_denom");

        std::cout << "Medium      : " << h_medium->Integral() << std::endl;
        std::cout << "Tight    : " << h_tight->Integral() << std::endl;
        std::cout << "Denom    : " << h_denom->Integral() << std::endl;

	if(printoutEvents){ 
		log1.close();
		log_events.close();
		log_files.close();
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

double Analysis::RelIsoMu(myobject mu){

	double MuIsoTrk = mu.pfIsoAll;
	double MuIsoEcal = mu.pfIsoGamma;
	double MuIsoHcal = mu.pfIsoNeutral;
	double MuIsoPU = mu.pfIsoPU;
	double relIso = (MuIsoTrk) / mu.pt;
	if (MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU > 0)
		relIso = (MuIsoTrk + MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU) / (mu.pt);

	return relIso;
}

double Analysis::RelIsoEl(myobject el){
	double ElIsoTrk = el.pfIsoAll;
	double ElIsoEcal = el.pfIsoGamma;
	double ElIsoHcal = el.pfIsoNeutral;
	double ElIsoPU = el.pfIsoPU;


	double relIso = (ElIsoTrk) / el.pt;
	if (ElIsoEcal + ElIsoHcal - 0.5 * ElIsoPU > 0)
		relIso = (ElIsoTrk + ElIsoEcal + ElIsoHcal - 0.5 * ElIsoPU) / (el.pt);
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

	vector<myobject> Met = m->RecPFMet;

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
				deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand[j+1].eta,Hcand[j+1].phi)> maxDeltaR && isLooseMu(genericMuon[i]) && RelIsoMu(genericMuon[i]) < 0.3) 
			Ad_lepton=true;
	   }
	   if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
    }
    if(verbose) std::cout << "There are " << genericElectron.size() << " additional electrons." << std::endl;
	for(uint i = 0; i < genericElectron.size(); i++)
	{   
		for(uint j =0; j < Hcand.size(); j+=2){
			if(deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand[j].eta,Hcand[j].phi)> maxDeltaR &&
				deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand[j+1].eta,Hcand[j+1].phi)> maxDeltaR && LooseEleId(genericElectron[i])  && RelIsoEl(genericElectron[i]) < 0.3)  
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
	for(uint i = 0; i < genericMuon.size(); i++)
	{   
			if(verbose) std::cout << " Mu cand no. " << i << std::endl;
			if(verbose) std::cout << " Distance to 1st is " << deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand1.eta,Hcand1.phi) << std::endl;
			if(verbose) std::cout << " Distance to 2nd is " << deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand2.eta,Hcand2.phi) << std::endl;
			if(verbose) std::cout << " Is good? " << isLooseMu(genericMuon[i]) << std::endl;
			if(verbose) std::cout << " iso is " << RelIsoMu(genericMuon[i]) << std::endl;
			if(verbose) std::cout << " WZ rej is " << WZ_Rej(m,genericMuon[i]) << std::endl;
			
			if (!WZ_Rej(m,genericMuon[i])) continue;
			
			
			if(isLooseMu(genericMuon[i]) && RelIsoMu(genericMuon[i]) < 0.3  && i!=index ) 
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
			if(verbose) std::cout << " Is very good? " << TightEleId(genericElectron[i]) << std::endl;
			if(verbose) std::cout << " Pt is " << genericElectron[i].pt << std::endl;
			if(verbose) std::cout << " num lost hits is " << genericElectron[i].numLostHitEleInner << std::endl;
			if(verbose) std::cout << " iso is " << RelIsoEl(genericElectron[i]) << std::endl;
			if(verbose) std::cout << " WZ rej is " << WZ_Rej(m,genericElectron[i]) << std::endl;
			if (!WZ_Rej(m,genericElectron[i])) continue;
			if( genericElectron[i].numLostHitEleInner > 1) continue;
	
			if(verbose) std::cout << " decision: " << LooseEleId(genericElectron[i]) << " " << 	RelIsoEl(genericElectron[i]) << " " << i << " index " << index << std::endl;
	
			if(LooseEleId(genericElectron[i]) && RelIsoEl(genericElectron[i])<0.3 )  
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
			if(verbose) std::cout << " iso is " << RelIsoMu(genericMuon[i]) << std::endl;
			if(verbose) std::cout << " WZ rej is " << WZ_Rej(m,genericMuon[i]) << std::endl;
			
			if (!WZ_Rej(m,genericMuon[i])) continue;
			
			
			if(isLooseMu(genericMuon[i]) && RelIsoMu(genericMuon[i]) < 0.3  ) 
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
			if(verbose) std::cout << " Is very good? " << TightEleId(genericElectron[i]) << std::endl;
			if(verbose) std::cout << " Pt is " << genericElectron[i].pt << std::endl;
			if(verbose) std::cout << " num lost hits is " << genericElectron[i].numLostHitEleInner << std::endl;
			if(verbose) std::cout << " iso is " << RelIsoEl(genericElectron[i]) << std::endl;
			if(verbose) std::cout << " WZ rej is " << WZ_Rej(m,genericElectron[i]) << std::endl;
			if (!WZ_Rej(m,genericElectron[i])) continue;
			if( genericElectron[i].numLostHitEleInner > 1) continue;
	
			if(verbose) std::cout << " decision: " << LooseEleId(genericElectron[i]) << " " << 	RelIsoEl(genericElectron[i]) << " " << i << " index " << index << std::endl;
	
			if(LooseEleId(genericElectron[i]) && RelIsoEl(genericElectron[i])<0.3 && i!=index )  
				Ad_lepton=true;
			if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
	   
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
			if(verbose) std::cout << " iso is " << RelIsoMu(genericMuon[i]) << std::endl;
			if(verbose) std::cout << " WZ rej is " << WZ_Rej(m,genericMuon[i]) << std::endl;
			
			if (!WZ_Rej(m,genericMuon[i])) continue;
			
			
			if(isLooseMu(genericMuon[i]) && RelIsoMu(genericMuon[i]) < 0.3 && i!=index_m ) 
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
			if(verbose) std::cout << " Is very good? " << TightEleId(genericElectron[i]) << std::endl;
			if(verbose) std::cout << " Pt is " << genericElectron[i].pt << std::endl;
			if(verbose) std::cout << " num lost hits is " << genericElectron[i].numLostHitEleInner << std::endl;
			if(verbose) std::cout << " iso is " << RelIsoEl(genericElectron[i]) << std::endl;
			if(verbose) std::cout << " WZ rej is " << WZ_Rej(m,genericElectron[i]) << std::endl;
			if (!WZ_Rej(m,genericElectron[i])) continue;
			if( genericElectron[i].numLostHitEleInner > 1) continue;
	
			if(verbose) std::cout << " decision: " << LooseEleId(genericElectron[i]) << " " << 	RelIsoEl(genericElectron[i]) << " " << i << " index " << index_e << std::endl;
	
			if(LooseEleId(genericElectron[i]) && RelIsoEl(genericElectron[i])<0.3 && i!=index_e )  
				Ad_lepton=true;
			if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
	   
	}
	
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
			if(verbose) std::cout << " iso is " << RelIsoMu(genericMuon[i]) << std::endl;
			
			if(isLooseMu(genericMuon[i]) && RelIsoMu(genericMuon[i]) < 0.3) 
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
			if(verbose) std::cout << " iso is " << RelIsoEl(genericElectron[i]) << std::endl;
			
			
			if(LooseEleId(genericElectron[i]) && genericElectron[i].numLostHitEleInner == 0 && RelIsoEl(genericElectron[i]) < 0.3)  
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
                double relIso = RelIsoMu(mu);

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
                double relIso = RelIsoMu(mu);

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
                double relIso = RelIsoEl(el);

                if (elPt > 10. && fabs(elEta) < 2.5  && elID && missingHits <=1)
                {
                        return true;
                }else return false;
}

//~ bool Analysis::isLargerPt(myobject o1, myobject o2){
	//~ return (o1.pt > o2.pt);
//~ }

// Fake Rate functions
double Analysis::fakeTau_tight(double pt) {
		if (pt<0) return 1.0;
		else{
			double f = p0_tight*(TMath::Exp(p1_tight*pt))+p2_tight;
      		return f;}
		}

double Analysis::fakeTau_medium(double pt) {
		if (pt<0) return 1.0;
		else{
			double f = p0_medium*(TMath::Exp(p1_medium*pt))+p2_medium;
      		return f;}
		}
		
double Analysis::PairMass(myobject Hcand1, myobject Hcand2){
	TLorentzVector H_1,H_2,H_sum;
    H_1.SetPxPyPzE(Hcand1.px,Hcand1.py,Hcand1.pz,Hcand1.E);
    H_2.SetPxPyPzE(Hcand2.px,Hcand2.py,Hcand2.pz,Hcand2.E);
    H_sum = H_1 + H_2;
	return H_sum.M();
}

void Analysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
	entries++;
	 // sync part
	std::vector<bool> found_event; //{false,false,false};
	std::vector<bool> isLoose;
	std::vector<bool> isMedium;
	std::vector<bool> isTight;
	found_event.clear();
	isLoose.clear();
	isMedium.clear();
	isTight.clear();
	// end sync

	// bookkepping part
		++m_allEvents;
	if(m->runNumber!=current_run || m->lumiNumber!=current_lumi){
		lumi << m->runNumber << " " << m->lumiNumber << std::endl;
		current_run=m->runNumber;
		current_lumi=m->lumiNumber;
	}
	TString fileName = GetInputTree(InTreeName.c_str())->GetDirectory()->GetFile()->GetName();
					
	m_logger << DEBUG << " Now executing event " << m->eventNumber << " in a run " << m->runNumber << SLogger::endmsg;

		Hist("h_nPU_Info")->Fill(m->PUInfo);
		Hist("h_nPU_InfoTrue")->Fill(m->PUInfo_true);
		Hist("h_nPU_Bunch0")->Fill(m->PUInfo_Bunch0);

        Cut_tau_base_Pt  = 0;
        Cut_tautau_sumPt = 0;
        Cut_leptau_sumPt = 0;
        Cut_leplep_sumPt = 0;
	
	

	double PUWeight = 1.0;
	double nPU = 0.0;
	if(useTruePileUp || !is2011)  nPU = m->PUInfo_true;
	else nPU = m->PUInfo_Bunch0;
	if(isSimulation){	
		PUWeight = LumiWeights_->weight( nPU );
		if(IgnorePUW) PUWeight = 1.0;
	}
	int eNumber = m->eventNumber;
	bool examineThisEvent;
	if( examineEvent==eNumber) examineThisEvent=true;
	else examineThisEvent=false;
	
	
	Hist("h_PU_weight")->Fill(PUWeight);
	if(!useTruePileUp && is2011){ 
		Hist("h_nPU_raw")->Fill(m->PUInfo_Bunch0);
		Hist("h_nPU_reweight")->Fill(m->PUInfo_Bunch0,PUWeight);
	}else{ 
		Hist("h_nPU_raw")->Fill(m->PUInfo_true);
		Hist("h_nPU_reweight")->Fill(m->PUInfo_true,PUWeight);
	}

	
        //vertex selection
	std::vector<myobject> vertex = m->Vertex;
	std::vector<myobject> goodVertex;
	goodVertex.clear();
	for (uint i = 0; i < vertex.size(); i++) {
		if (vertex[i].isValid && vertex[i].normalizedChi2 > 0 && vertex[i].ndof > 4 && fabs(vertex[i].z) < 24)
		goodVertex.push_back(vertex[i]);
	}
	short nGoodVx=goodVertex.size();

		Hist("h_nPU_Info_W")->Fill(m->PUInfo,PUWeight);
		Hist("h_nPU_InfoTrue_W")->Fill(m->PUInfo_true,PUWeight);
		Hist("h_nPU_Bunch0_W")->Fill(m->PUInfo_Bunch0,PUWeight);

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
	
		return;
	}
	
	h_cut_flow->Fill(1,1);
	h_cut_flow_weight->Fill(1,PUWeight);
	
	if(nGoodVx < 1) return;
	
	h_cut_flow->Fill(2,1);
	h_cut_flow_weight->Fill(2,PUWeight);
	

	vector<myobject> Met = m->RecPFMet;

	Hist("h_PF_MET")->Fill(Met.front().et,PUWeight);
	h_PF_MET_nPU->Fill(nGoodVx,Met.front().et,PUWeight);

	std::vector<myobject> goodMuon;
	goodMuon.clear();
	std::vector<myobject> denomMuon;
	denomMuon.clear();


	std::vector<myobject> muon = m->PreSelectedMuons;
	if(examineThisEvent) std::cout << " There are " << muon.size() << " preselected muons " << std::endl;

	for (uint i = 0; i < muon.size(); i++) {

		double muPt = muon[i].pt;
		double muEta = muon[i].eta;
		bool muGlobal = muon[i].isGlobalMuon;
		bool muTracker = muon[i].isTrackerMuon;
		double relIso = RelIsoMu(muon[i]);
		bool pfID = PFMuonID(muon[i]);	

		if ((muGlobal || muTracker) && muPt > 10. && fabs(muEta) < 2.4){
		
			if (muGlobal && muTracker && muPt > 10. && fabs(muEta) < 2.4 && pfID)
			{
				goodMuon.push_back(muon[i]);
				Hist("h_mu_relIso")->Fill(relIso,PUWeight);
			}
        		denomMuon.push_back(muon[i]);
		}else{
			if(examineThisEvent) std::cout << " pre-muon no. " << i << " has been rejected because of global|tracker pt eta:" <<
			muGlobal << muTracker << " " << muPt << " " << muEta << std::endl; 
		}
    }

	Hist("h_n_goodMu")->Fill(goodMuon.size(),PUWeight);

	std::vector<myobject> goodElectron;
	goodElectron.clear();
        std::vector<myobject> denomElectron;
        denomElectron.clear();
   
	std::vector<myobject> electron = m->PreSelectedElectrons;
	if(examineThisEvent) std::cout << " There are " << electron.size() << " preselected electrons " << std::endl;
	
	for (uint i = 0; i < electron.size(); i++) {

		double elPt = electron[i].pt;
		double elEta = electron[i].eta_SC;
		int missingHits = electron[i].numLostHitEleInner;
		bool elID =  LooseEleId(elPt,electron[i].eta_SC,electron[i].Id_mvaNonTrg);
		double relIso = RelIsoEl(electron[i]);

		if (elPt > 10. && fabs(elEta) < 2.5 && missingHits < 2)
		{
			if(examineThisEvent) std::cout << " pre-electron " << i << " pt eta etaSC: " << elPt << " " 
			<< elEta << " " << electron[i].eta << std::endl;
			if(elID){
				goodElectron.push_back(electron[i]);
				Hist("h_el_relIso")->Fill(relIso,PUWeight);
			}
				denomElectron.push_back(electron[i]);
        }else{
			if(examineThisEvent) std::cout << "Pre-electron no. " << i << " rejected: " << elPt << " " << elEta << " " << missingHits <<std::endl;
		}
	}
	
	
	// Z compatibility
	std::vector<myobject> Zcand;
	Zcand.clear();
	
	//overlap cleaning
	
	//~ for(int i = 0; i < denomMuon.size(); i++)
	//~ {
		//~ if(examineThisEvent) std::cout << "Looping over muon no. " << i << " out of " << denomMuon.size() << std::endl;
		//~ 
		//~ bool removed = false;
		//~ for(uint j = i+1; j < denomMuon.size() && !removed ; j++)
		//~ {
			//~ if(examineThisEvent) std::cout << "Looping over muon no. " << j << " out of " << denomMuon.size() 
			//~ <<":" << deltaR(denomMuon[i].eta,denomMuon[i].phi,denomMuon[j].eta,denomMuon[j].phi) << std::endl;
		//~ 
			//~ if(deltaR(denomMuon[i].eta,denomMuon[i].phi,denomMuon[j].eta,denomMuon[j].phi)< maxDeltaR) 
			//~ {	denomMuon.erase(denomMuon.begin()+i); i--;removed = true;}
			//~ if(examineThisEvent) std::cout << "Preremoved? " << removed << std::endl;
		//~ }
	//~ }
	//~ 
	
	
	for(int i = 0; i < denomElectron.size(); i++)
	{
		if(examineThisEvent) std::cout << "Looping over electron no. " << i << " out of " << denomElectron.size() << std::endl;
		bool removed = false;
		//~ for(uint j = i+1; j < denomElectron.size() && !removed ; j++)
		//~ {
			//~ if(examineThisEvent) std::cout << "Looping over ele no. " << j << " out of " << Zcand.size() 
			//~ << " " << deltaR(denomElectron[i].eta,denomElectron[i].phi,denomElectron[j].eta,denomElectron[j].phi) << std::endl;
		//~ 
			//~ if(deltaR(denomElectron[i].eta,denomElectron[i].phi,denomElectron[j].eta,denomElectron[j].phi)< maxDeltaR) 
			//~ {	denomElectron.erase(denomElectron.begin()+i); i--; removed = true;}
			//~ if(examineThisEvent) std::cout << "Zremoved? " << removed << std::endl;
		//~ }

		for(uint j = 0; j < denomMuon.size() && !removed; j++)
		{
			if(examineThisEvent) std::cout << "Looping over mu no. " << j << " out of " << denomMuon.size() << " " << 
			deltaR(denomElectron[i].eta,denomElectron[i].phi,denomMuon[j].eta,denomMuon[j].phi) << std::endl;
			if(deltaR(denomElectron[i].eta,denomElectron[i].phi,denomMuon[j].eta,denomMuon[j].phi)< maxDeltaR && RelIsoMu(denomMuon[j]) < 0.3) 
			{	denomElectron.erase(denomElectron.begin()+i); i--; removed = true;}
			if(examineThisEvent) std::cout << "Muremoved? " << removed << std::endl;
		}

	}
	
	
	

	int muCandZ = goodMuon.size();
	int elCandZ = goodElectron.size();
	if(examineThisEvent) std::cout << " There are " << elCandZ << " good electrons and " << denomElectron.size() << " denom electrons" << std::endl;
	
	
	Hist("h_n_goodEl")->Fill(goodElectron.size(),PUWeight);
	
	bool Zmumu = false;
	bool Zee = false;
	bool Zmucand, Zelcand;
	Zmucand=Zelcand=false;
	double dMass=999.0;
	int Zindex[2] = {-1,-1};
	if(examineThisEvent) std::cout << "Finding Z out of " << goodMuon.size() << " muons " << std::endl;
	for(uint i = 0; i < denomMuon.size(); i++)
	{
		m_logger << VERBOSE << "  ->denom muon no. "<< i << " has pt "<<  denomMuon[i].pt << " and charge " << denomMuon[i].charge << SLogger::endmsg;
		if(examineThisEvent) std::cout << "  ->denom muon no. "<< i << " has pt "<<  denomMuon[i].pt << " and charge " << denomMuon[i].charge << std::endl;
		if(Zmumu) continue;
		if(RelIsoMu(denomMuon[i]) > 0.3) continue;
		if(!isLooseMu(denomMuon[i])) continue;
		if(examineThisEvent) std::cout << "  -> Passed pre-selection " << std::endl;
		for(uint j = i+1; j < denomMuon.size() && !Zmumu; j++)
		{
			m_logger << VERBOSE << "  -->second muon no. "<< j << " has pt "<<  denomMuon[j].pt << " and charge " << denomMuon[j].charge << SLogger::endmsg;
			if(examineThisEvent) std::cout << "  -->second muon no. "<< j << " has pt "<<  denomMuon[j].pt << " and charge " << denomMuon[j].charge << std::endl;
			if(RelIsoMu(denomMuon[j]) > 0.3) continue;
			if(!isLooseMu(denomMuon[j])) continue;
			if(denomMuon[i].charge*denomMuon[j].charge >=0.) continue;
			if(deltaR(denomMuon[i].eta,denomMuon[i].phi,denomMuon[j].eta,denomMuon[j].phi)< maxDeltaR) continue;
			if(examineThisEvent) std::cout << " Passed pre-selection " << std::endl;
			
			TLorentzVector cand;
			cand.SetPxPyPzE(denomMuon[i].px+denomMuon[j].px,
					denomMuon[i].py+denomMuon[j].py,
					denomMuon[i].pz+denomMuon[j].pz,
					denomMuon[i].E+denomMuon[j].E);
			double mass = cand.M();
			m_logger << VERBOSE << "  -->Candidate mass is " << mass << SLogger::endmsg;
			if(examineThisEvent) std::cout << " mass " << mass << std::endl;
			
			if(mass > 60. && mass < 120.){
				Zmumu=true;
				double dM = 999.;
				if(BestMassForZ > 0.0){
					Zmumu=false;
					dM=fabs(mass-BestMassForZ);

					if(dM < dMass){
						Zindex[0]=i;
						Zindex[1]=j;
						dMass=dM;
						Zmucand=true;
					}
				}else{
					Zmucand=true;
					Zindex[0]=i;
					Zindex[1]=j;
				}
			}
		}
	}
	
	if(Zindex[0] > -1 && Zindex[1] > -1 && Zmucand){
		        
            int i = Zindex[0];
			int j = Zindex[1];
	
		if(denomMuon[i].pt > 20.){
			Zcand.push_back(denomMuon[i]);
			Zcand.push_back(denomMuon[j]);
			denomMuon.erase(denomMuon.begin()+i);
			denomMuon.erase(denomMuon.begin()+j-1);
	
			Zmumu=true;
		}
	}
	

	m_logger << VERBOSE << " There are " << goodMuon.size() << " remaining good muons " << SLogger::endmsg;

	if(!Zmumu)
	{
		dMass = 999.;
		for(uint i = 0; i < denomElectron.size(); i++)
		{
			m_logger << VERBOSE << " ->denom electron no. "<< i << " has pt "<<  denomElectron[i].pt << " and charge " << denomElectron[i].charge << SLogger::endmsg;
			if(Zee) continue;
			if(RelIsoEl(denomElectron[i]) > 0.3) continue;
			if(!LooseEleId(denomElectron[i])) continue;
			for(uint j = i+1; j < denomElectron.size() && !Zee; j++)
			{
				m_logger << VERBOSE << "  -->second electron no. "<< j << " has pt "<<  denomElectron[j].pt << " and charge " << denomElectron[j].charge << SLogger::endmsg;
				if(RelIsoEl(denomElectron[j]) > 0.3) continue;	
				if(!LooseEleId(denomElectron[j])) continue;
				if(denomElectron[i].charge*denomElectron[j].charge >=0.) continue;
				if(deltaR(denomElectron[i].eta,denomElectron[i].phi,denomElectron[j].eta,denomElectron[j].phi)< maxDeltaR) continue;

				TLorentzVector cand;
				cand.SetPxPyPzE(denomElectron[i].px+denomElectron[j].px,
						denomElectron[i].py+denomElectron[j].py,
						denomElectron[i].pz+denomElectron[j].pz,
						denomElectron[i].E+denomElectron[j].E);
				double mass = cand.M();
				m_logger << VERBOSE << "  -->Candidate mass is " << mass << SLogger::endmsg;
				if(mass > 60. && mass < 120.){ 
					Zee=true;
					double dM = 999.; 
					if(BestMassForZ > 0.0){
						Zee=false;
						dM=fabs(mass-BestMassForZ);
						if(dM < dMass){
							Zindex[0]=i;
							Zindex[1]=j;
							dMass=dM;
							Zelcand=true;
						}
					}else{
						Zelcand=true;
						Zindex[0]=i;
						Zindex[1]=j;
					} 

				}
			}
		}
	
		if(Zindex[0] > -1 && Zindex[1] > -1 && Zelcand){
				int i = Zindex[0];
				int j = Zindex[1];
		
			if(denomElectron[i].pt > 20.){			
				Zcand.push_back(denomElectron[i]);
				Zcand.push_back(denomElectron[j]);	
				denomElectron.erase(denomElectron.begin()+i);
				denomElectron.erase(denomElectron.begin()+j-1);
				Zee=true;
			}
		}
	}

	
	double corrZlep1,corrZlep2;
	corrZlep1=corrZlep2=1.0;
	double Z_weight = PUWeight;
	if(isSimulation && !IgnoreSF){
		if(Zmumu)
		{
			if(is2012_53){
				corrZlep1=Cor_ID_Iso_Mu_Loose_2012_53X(Zcand[0])*Corr_Trg_Mu_2012_53X(Zcand[0]);;
				corrZlep2=Cor_ID_Iso_Mu_Loose_2012_53X(Zcand[1])*Corr_Trg_Mu_2012_53X(Zcand[1]);;
			}else if(is2012_52){
				corrZlep1=Cor_ID_Iso_Mu_Loose_2012(Zcand[0]);
				corrZlep2=Cor_ID_Iso_Mu_Loose_2012(Zcand[1]);
			}else{
				corrZlep1=Cor_ID_Iso_Mu_Loose_2011(Zcand[0])*Corr_Trg_Mu_2011(Zcand[0]);
				corrZlep2=Cor_ID_Iso_Mu_Loose_2011(Zcand[1])*Corr_Trg_Mu_2011(Zcand[1]);
			}
			Z_weight *= corrZlep1* corrZlep2;	
		}else if(Zee){
			if(is2012_53){
				corrZlep1=Cor_ID_Iso_Ele_Loose_2012_53X(Zcand[0])*Corr_Trg_Ele_2012_53X(Zcand[0]);;
				corrZlep2=Cor_ID_Iso_Ele_Loose_2012_53X(Zcand[1])*Corr_Trg_Ele_2012_53X(Zcand[1]);;
			}else if(is2012_52){
				corrZlep1=Cor_ID_Iso_Ele_Loose_2012(Zcand[0]);
				corrZlep2=Cor_ID_Iso_Ele_Loose_2012(Zcand[1]);
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

		Hist( "h_mu1Z_pt" )->Fill(muon1.Pt(),Z_weight);
		Hist( "h_mu2Z_pt" )->Fill(muon2.Pt(),Z_weight);
		Hist( "h_Zmass_mumu" )->Fill(Zmumu_.M(),Z_weight);
		Hist( "h_Zpt_mumu" )->Fill(Zmumu_.Pt(),Z_weight);
		Hist( "h_Zmass" )->Fill(Zmumu_.M(),Z_weight);
		Hist( "h_Zpt" )->Fill(Zmumu_.Pt(),Z_weight);
		Zmass=Zmumu_.M();
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
		Hist( "h_ele1Z_pt" )->Fill(ele1.Pt(),Z_weight);
		Hist( "h_ele2Z_pt" )->Fill(ele2.Pt(),Z_weight);
		Hist( "h_Zmass_ee" )->Fill(Zee_.M(),Z_weight);
		Hist( "h_Zpt_ee" )->Fill(Zee_.Pt(),Z_weight);
		Hist( "h_Zmass" )->Fill(Zee_.M(),Z_weight);
		Hist( "h_Zpt" )->Fill(Zee_.Pt(),Z_weight);	
		Zmass=Zee_.M();
		Hist( "h_Z_eta")->Fill(Zee_.Eta(),Z_weight);
		Hist( "h_Z_phi")->Fill(Zee_.Phi(),Z_weight);
		Hist( "h_Z_lep1_eta")->Fill(ele1.Eta(),Z_weight);
		Hist( "h_Z_lep1_phi")->Fill(ele1.Phi(),Z_weight);
		Hist( "h_Z_lep2_eta")->Fill(ele2.Eta(),Z_weight);
		Hist( "h_Z_lep2_phi")->Fill(ele2.Phi(),Z_weight);
	}

	m_logger << VERBOSE << " There are " << goodElectron.size() << " remaining good electrons " << SLogger::endmsg;

	if(Zmumu||Zee){
		m_logger << DEBUG << " There is a Z candidate! " << SLogger::endmsg;
		if(examineThisEvent) std::cout << " Z mass is " << Zmass << std::endl;
	}
	else{
		if(examineThisEvent) std::cout << "No Z cand!" << std::endl;
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

		

		if (fabs(tauEta) < 2.3 && LooseMuon && DecayMode){
			goodTau.push_back(tau[i]);
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
		if(RelIsoEl(denomElectron[i]) < 0.3 && LooseEleId(denomElectron[i])) isoElectrons++;
	}
 
	for(uint i=0; i< denomMuon.size(); i++)
	{
		if(RelIsoMu(denomMuon[i]) < 0.3 && isLooseMu(denomMuon[i])) isoMuons++;
	}
	
	if(isoElectrons > 2  || isoMuons > 2) return;

	if(examineThisEvent) std::cout << "checking size of electrons and muons...PASSED" << std::endl;
	
	// Z overlap removal
	bool Zoverlap = false;
	
	for(int i = 0; i < denomMuon.size(); i++)
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
	
	for(int i = 0; i < denomElectron.size(); i++)
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

	for(int i = 0; i < goodTau.size(); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{

			if(deltaR(goodTau[i].eta,goodTau[i].phi,Zcand[j].eta,Zcand[j].phi)< maxDeltaR) 
			{	goodTau.erase(goodTau.begin()+i); i--; removed = true;}

		}
		if(examineThisEvent && removed) std::cout << " tau overlap with Z" << std::endl;
	}
	//~ 
	if(examineThisEvent) std::cout << "Checking Z overlap..." << std::endl;
	
//	std::sort(goodTau.begin(),goodTau.end());
	
	//if(Zoverlap) return;

	Hist("h_n_goodEl_Hcand")->Fill(goodElectron.size());	
    if(examineThisEvent) std::cout << " There are " << goodElectron.size() << " good electrons and " << denomElectron.size() << " denom electrons after Zremoval" << std::endl;
	
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
	short category = -1;
	 	bool category0 = false;
		bool category1= false;
		bool category2=false;     
	 
	std::vector<myobject> Hcand;
	std::vector<int> Hcand_type;
	std::vector<myobject> Hcand_cat0;
	std::vector<int> Hcand_type_cat0;
	std::vector<myobject> Hcand_cat1;
	std::vector<int> Hcand_type_cat1;
	std::vector<myobject> Hcand_cat2;
	std::vector<int> Hcand_type_cat2;
	Hcand.clear();
	Hcand_type.clear();
	Hcand_cat0.clear();
	Hcand_type_cat0.clear();
	Hcand_cat1.clear();
	Hcand_type_cat1.clear();
	Hcand_cat2.clear();
	Hcand_type_cat2.clear();
	
	std::vector<uint> usedTauIdx;
	usedTauIdx.clear();
	if(examineThisEvent) std::cout << " There are " << genericMuon.size() << " mu candidates " << std::endl;
	
	bool tauTau =false;

	if(examineThisEvent) std::cout << " Checking tautau " << std::endl;
	for(uint i = 0; i < goodTau.size() ; i++)
	{
		if(examineThisEvent) std::cout << " Tau candidate i= " << i << " " << goodTau[i].pt << std::endl;
		if(goodTau[i].pt < Cut_tautau_Pt_1) continue;
		if(goodTau[i].discriminationByElectronLoose <= 0.5) continue;
				
		//if(goodTau[i].discriminationByElectronMedium <=0.5) continue;
		//if(goodTau[i].discriminationByMuonMedium <=0.5) continue;
		if(examineThisEvent) std::cout << "   Passed pre-selection" << std::endl;
		for(uint j=i+1; j< goodTau.size() && !(category0 && category1 && category2); j++)
		{
			if(examineThisEvent) std::cout << " Tau candidate j= " << j << " " << goodTau[j].pt << " mass: " << 
			PairMass(goodTau[i],goodTau[j]) <<std::endl;
			
			
			if(goodTau[j].pt < Cut_tautau_Pt_2) continue;	
			if(examineThisEvent) std::cout << "  j passed pt cut" << j << " " << Cut_tautau_Pt_2 << std::endl;
			if(goodTau[i].charge*goodTau[j].charge  > 0) continue;
			if(goodTau[j].discriminationByElectronLoose <= 0.5) continue;
		
			//if(goodTau[j].discriminationByElectronMedium <=0.5) continue;
			//if(goodTau[j].discriminationByMuonMedium <=0.5) continue;
			if(examineThisEvent) std::cout << "   j Passed pre-selection" << std::endl;
		
			if(deltaR(goodTau[j].eta,goodTau[j].phi,goodTau[i].eta,goodTau[i].phi)< maxDeltaR) continue;
			if(examineThisEvent) std::cout << "   Passed selection" << std::endl;
			
			bool verb=false;
			if(examineThisEvent) verb=true;
			
			if(AdLepton_tt(genericMuon,genericElectron,goodTau,goodTau[i],goodTau[j],verb)){
				if(examineThisEvent) std::cout << "   > j failed overlap check." << std::endl;				
				continue;
			}
			if(!DZ_expo(Zcand[0],Zcand[1],goodTau[i],goodTau[j], verb)) continue; 			
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
			if(Hcand[index].byLooseCombinedIsolationDeltaBetaCorr3Hits <=0.5 && Hcand[index+1].byLooseCombinedIsolationDeltaBetaCorr3Hits <=0.5 && !category0)
			{
				if(examineThisEvent) std::cout << " in category 0!" << std::endl;
				category0=true;
				Hcand_cat0.push_back(Hcand[index]);
				Hcand_cat0.push_back(Hcand[index+1]);
				if(Zmumu) Hcand_type_cat0.push_back(4);
				else if(Zee) Hcand_type_cat0.push_back(8);
			}
			if(Hcand[index].byLooseCombinedIsolationDeltaBetaCorr3Hits >0.5 && Hcand[index+1].byLooseCombinedIsolationDeltaBetaCorr3Hits <=0.5 && !category1)
			{
				if(examineThisEvent) std::cout << " in category 1!" << std::endl;
				category1=true;
				Hcand_cat1.push_back(Hcand[index]);
				Hcand_cat1.push_back(Hcand[index+1]);
				if(Zmumu) Hcand_type_cat1.push_back(4);
				else if(Zee) Hcand_type_cat1.push_back(8);
			}
			if(Hcand[index].byLooseCombinedIsolationDeltaBetaCorr3Hits <=0.5 && Hcand[index+1].byLooseCombinedIsolationDeltaBetaCorr3Hits >0.5 && !category2)
			{
				if(examineThisEvent) std::cout << " in category 2!" << std::endl;
				category2=true;
				Hcand_cat2.push_back(Hcand[index]);
				Hcand_cat2.push_back(Hcand[index+1]);
				if(Zmumu) Hcand_type_cat2.push_back(4);
				else if(Zee) Hcand_type_cat2.push_back(8);
			}
			
			usedTauIdx.push_back(i);
			usedTauIdx.push_back(j);
			if(Zmumu) Hcand_type.push_back(4);
			else if(Zee) Hcand_type.push_back(8);
			m_logger << DEBUG << " hindex[0] " << i << SLogger::endmsg;
			m_logger << DEBUG << " hindex[1] " << j << SLogger::endmsg;

		}
	}
	
	if(examineThisEvent) std::cout << " After TT, there are " << Hcand_cat0.size() << " cat0 "<< Hcand_cat1.size() << " cat1 "<< Hcand_cat2.size() << " cat2. "<<   std::endl;
	category0 = false;
	category1= false;
	category2=false;     
	
	for(uint i = 0; i < genericMuon.size() ; i++)
	{
	
		if(examineThisEvent) std::cout << " Looping over muon no.  " << i << std::endl;
	
	
		m_logger << DEBUG << " Checking for muTau " << SLogger::endmsg;
		
		if(examineThisEvent) std::cout << " Checking mutau " << std::endl;
		if(examineThisEvent) std::cout << " Mu candidate i= " << i << " " << genericMuon[i].pt << " " << genericMuon[i].charge << std::endl;
		//if(!WZ_Rej(m,genericMuon[i])) continue;
		if(examineThisEvent) std::cout << " Passed pre-selection. Looping over " << goodTau.size() << " taus." << std::endl;	
		for(uint j=0; j< goodTau.size() && !(category0 && category1 && category2); j++)
		{
                       
			//~ if((j==usedTauIdx[0] || j==usedTauIdx[1]) && examineThisEvent) std::cout << "This tau has been used!" << std::endl;
			//~ if(j==usedTauIdx[0] || j==usedTauIdx[1]) continue;
			if(examineThisEvent) std::cout << "   > tau no. " << j << " " << goodTau[j].pt << " " << goodTau[j].charge << std::endl;
			if(examineThisEvent){
				TLorentzVector ele1;
				TLorentzVector tau2;
				TLorentzVector H_; 
				ele1.SetPxPyPzE(genericMuon[i].px,genericMuon[i].py,genericMuon[i].pz,genericMuon[i].E);        
				tau2.SetPxPyPzE(goodTau[j].px,goodTau[j].py,goodTau[j].pz,goodTau[j].E);        
				H_=ele1+tau2;
				std::cout << " H candidate mass is " << H_.M() << std::endl;
			}
			if(goodTau[j].pt < Cut_tautau_Pt_2) continue;	
			
			if(genericMuon[i].charge*goodTau[j].charge > 0) continue;
			if(goodTau[j].discriminationByMuonTight2 <=0.5) continue;
			if(goodTau[j].discriminationByElectronLoose <= 0.5) continue;
		
			if(deltaR(goodTau[j].eta,goodTau[j].phi,genericMuon[i].eta,genericMuon[i].phi)< maxDeltaR) continue;  
			if(examineThisEvent) std::cout << " j distance is " << deltaR(goodTau[j].eta,goodTau[j].phi,genericMuon[i].eta,genericMuon[i].phi) << std::endl;            
			if(examineThisEvent) std::cout << " j passed pre-selection " << std::endl;
			bool verb=false;
			if(examineThisEvent) verb=true;
			if(AdLepton_mt(m,i,genericMuon,genericElectron,goodTau,genericMuon[i],goodTau[j],verb)){ 
				if(examineThisEvent) std::cout << " Aborting due to additional lepton" << std::endl;
				continue;}
			if(!DZ_expo(Zcand[0],Zcand[1],genericMuon[i],goodTau[j], verb)) continue;
			if(examineThisEvent) std::cout << "PASSED!" << std::endl;
			signal = true; 
			muTau=true;
			Hcand.push_back(genericMuon[i]);
			Hcand.push_back(goodTau[j]);
			int index = Hcand.size() -2;
			bool pass1 = (RelIsoMu(Hcand[index])<0.3 && isGoodMu(Hcand[index]));
			bool pass2 = Hcand[index+1].byLooseCombinedIsolationDeltaBetaCorr3Hits >0.5;
			
			if( !pass1 && !pass2 && !category0)
			{
				category0=true;
				Hcand_cat0.push_back(Hcand[index]);
				Hcand_cat0.push_back(Hcand[index+1]);
				if(Zmumu) Hcand_type_cat0.push_back(1);
				else if(Zee) Hcand_type_cat0.push_back(5);
			}
			if(!pass1 && pass2 && !category1)
			{
				category1=true;
				Hcand_cat1.push_back(Hcand[index]);
				Hcand_cat1.push_back(Hcand[index+1]);
				if(Zmumu) Hcand_type_cat1.push_back(1);
				else if(Zee) Hcand_type_cat1.push_back(5);
			}
			if(pass1 && !pass2 && !category2)
			{
				category2=true;
				Hcand_cat2.push_back(Hcand[index]);
				Hcand_cat2.push_back(Hcand[index+1]);
				if(Zmumu) Hcand_type_cat2.push_back(1);
				else if(Zee) Hcand_type_cat2.push_back(5);
			}
			
			if(Zmumu) Hcand_type.push_back(1);
			else if(Zee) Hcand_type.push_back(5);
			
		}             
	}
	

	if(muTau) m_logger << INFO << " muTau candidate!" << SLogger::endmsg;   
	else if(muE) m_logger << INFO << " muE candidate!" << SLogger::endmsg;                 
	else m_logger << DEBUG << " Checking no-muon channels" << SLogger::endmsg;
	bool eTau = false;
	if(examineThisEvent) std::cout << " There are " << genericElectron.size() << " ele candidates " << std::endl;
	category0 = false;
	category1= false;
	category2=false;     
	
	for(uint i = 0; i < genericElectron.size() ; i++)
	{
		if(examineThisEvent) std::cout << " electron no. "<< i << " " << genericElectron[i].pt << " " << genericElectron[i].charge << std::endl;
		
		if(genericElectron[i].numLostHitEleInner > 0) continue;
		if(examineThisEvent) std::cout << " Checking for eTau " << std::endl;
		//if (!WZ_Rej(m,genericElectron[i])) continue;
		if(examineThisEvent) std::cout << " i passed pre-selection. Looping over " << goodTau.size() << " taus." << std::endl;
		for(uint j=0; j< goodTau.size() &&!(category0 && category1 && category2); j++)
		{
			//~ if((j==usedTauIdx[0] || j==usedTauIdx[1]) && examineThisEvent) std::cout << "This tau has been used!" << std::endl;
			//~ if(j==usedTauIdx[0] || j==usedTauIdx[1]) continue;
			if(examineThisEvent) std::cout << "   > tau no. " << j << " " << goodTau[j].pt << " " << goodTau[j].charge << std::endl;
			if(examineThisEvent){
				TLorentzVector ele1;
				TLorentzVector tau2;
				TLorentzVector H_; 
				ele1.SetPxPyPzE(genericElectron[i].px,genericElectron[i].py,genericElectron[i].pz,genericElectron[i].E);        
				tau2.SetPxPyPzE(goodTau[j].px,goodTau[j].py,goodTau[j].pz,goodTau[j].E);        
				H_=ele1+tau2;
				std::cout << " H candidate mass is " << H_.M() << std::endl;
			}
			if(goodTau[j].pt < Cut_tautau_Pt_2) continue;	
			
			if(genericElectron[i].charge*goodTau[j].charge > 0) continue;
			if(goodTau[j].discriminationByElectronMVA3Tight <=0.5) continue;
			if(goodTau[j].discriminationByElectronLoose <= 0.5) std::cout << "WTF!!!!!!!!!!!!!!!" << goodTau[j].eta << std::endl;
		
			if(deltaR(goodTau[j].eta,goodTau[j].phi,genericElectron[i].eta,genericElectron[i].phi)< maxDeltaR) continue;
			if(examineThisEvent) std::cout << " j distance is " << deltaR(goodTau[j].eta,goodTau[j].phi,genericElectron[i].eta,genericElectron[i].phi) << std::endl;            
			if(examineThisEvent) std::cout << "   > j passed pre-selection." << std::endl;
			if(examineThisEvent) std::cout << "   > candidate passed WZ rejection" << std::endl;
			
			bool verb = false;
			if(examineThisEvent) verb = true;
			if(AdLepton_et(m,i,genericMuon,genericElectron,goodTau,genericElectron[i],goodTau[j],verb)){ 
				if(examineThisEvent) std::cout << "   > j failed overlap check." << std::endl;				
				continue;
			}
			if(examineThisEvent) verb=true;
			if(!DZ_expo(Zcand[0],Zcand[1],genericElectron[i],goodTau[j], verb)) continue;
			signal = true; 
			eTau=true;
			if(examineThisEvent) std::cout << "tau MVA3VTight, eta,Loose:" << goodTau[j].discriminationByElectronMVA3VTight << " " << goodTau[j].eta << " " << goodTau[j].discriminationByElectronLoose << std::endl;
			if(examineThisEvent) std::cout << "PASSED!" << std::endl;
			Hcand.push_back(genericElectron[i]);
			Hcand.push_back(goodTau[j]);
			int index = Hcand.size() -2;
			
					
			bool pass1 = (RelIsoEl(Hcand[index])<0.3 && TightEleId(Hcand[index]));
			bool pass2 = Hcand[index+1].byLooseCombinedIsolationDeltaBetaCorr3Hits >0.5;
			
			if(examineThisEvent) std::cout << "checking categories: " << category0 << category1 << category2 << std::endl;
			if(examineThisEvent) std::cout << "The isolation is " << pass1 << pass2 << std::endl;
			
			if( !pass1 && !pass2 && !category0)
			{
				if(examineThisEvent) std::cout << "In category0" << std::endl;
				category0=true;
				Hcand_cat0.push_back(Hcand[index]);
				Hcand_cat0.push_back(Hcand[index+1]);
				if(Zmumu) Hcand_type_cat0.push_back(3);
				else if(Zee) Hcand_type_cat0.push_back(7);
			}
			if(!pass1 && pass2 && !category1)
			{
				if(examineThisEvent) std::cout << "In category1" << std::endl;
				category1=true;
				Hcand_cat1.push_back(Hcand[index]);
				Hcand_cat1.push_back(Hcand[index+1]);
				if(Zmumu) Hcand_type_cat1.push_back(3);
				else if(Zee) Hcand_type_cat1.push_back(7);
			}
			if(pass1 && !pass2 && !category2)
			{
				if(examineThisEvent) std::cout << "in category2" << std::endl;
				category2=true;
				Hcand_cat2.push_back(Hcand[index]);
				Hcand_cat2.push_back(Hcand[index+1]);
				if(Zmumu) Hcand_type_cat2.push_back(3);
				else if(Zee) Hcand_type_cat2.push_back(7);
			}
			
			if(Zmumu) Hcand_type.push_back(3);
			else if(Zee) Hcand_type.push_back(7);
		
		}
	}
	if(examineThisEvent) std::cout << " After ET, there are " << Hcand_cat0.size() << " cat0 "<< Hcand_cat1.size() << " cat1 "<< Hcand_cat2.size() << " cat2. "<<   std::endl;
	
	
	//emu final state
	bool eMu=false;
	category0 = false;
	category1= false;
	category2=false;     
	
	
	for(uint i = 0; i < genericElectron.size() ; i++)
	{
		if(examineThisEvent) std::cout << " electron no. "<< i << " " << genericElectron[i].pt << " " << genericElectron[i].charge << std::endl;
		
		if(genericElectron[i].numLostHitEleInner > 1) continue;
		if(examineThisEvent) std::cout << " Checking for eMu " << std::endl;
		//if (!WZ_Rej(m,genericElectron[i])) continue;
		if(examineThisEvent) std::cout << " i passed pre-selection. Looping over " << genericMuon.size() << " muons." << std::endl;
		for(uint j=0; j< genericMuon.size() && !(category0 && category1 && category2); j++)
		{
			
			if(examineThisEvent) std::cout << "   > muon no. " << j << " " << genericMuon[j].pt << " " << genericMuon[j].charge << std::endl;
			if(examineThisEvent) std::cout << " H candidate mass is " << PairMass(genericElectron[i],genericMuon[j]) << std::endl;
			if(genericElectron[i].charge*genericMuon[j].charge > 0) continue;
			if(deltaR(genericMuon[j],genericElectron[i])< maxDeltaR) continue;
			if(examineThisEvent) std::cout << " j distance is " << deltaR(genericMuon[j],genericElectron[i]) << std::endl;            
			if(examineThisEvent) std::cout << "   > j passed pre-selection." << std::endl;
			
			bool verb = false;
			if(examineThisEvent) verb = true;
			if(AdLepton_em(m,i,j,genericMuon,genericElectron,genericElectron[i],genericMuon[j],verb)){ 
				if(examineThisEvent) std::cout << "   > j failed overlap check." << std::endl;				
				continue;
			}
			
			if(!DZ_expo(Zcand[0],Zcand[1],genericElectron[i],genericMuon[j], verb)) continue;
			signal = true; 
			eMu=true;
			if(examineThisEvent) std::cout << "PASSED!" << std::endl;
			Hcand.push_back(genericElectron[i]);
			Hcand.push_back(genericMuon[j]);
			int index = Hcand.size() -2;
			
			bool pass1 = (RelIsoEl(Hcand[index])<0.3 && LooseEleId(Hcand[index]));
			bool pass2 = (RelIsoMu(Hcand[index+1])<0.3 && isLooseMu(Hcand[index+1]));
		    if(examineThisEvent) std::cout << "checking categories: " << category0 << category1 << category2 << std::endl;
			if(examineThisEvent) std::cout << "The isolation is " << pass1 << pass2 << std::endl;
			
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
			
			if(Zmumu) Hcand_type.push_back(2);
			else if(Zee) Hcand_type.push_back(6);
			
			
			
		}
    
		
	}
	
	if(examineThisEvent) std::cout << " After EM, there are " << Hcand_cat0.size() << " cat0 "<< Hcand_cat1.size() << " cat1 "<< Hcand_cat2.size() << " cat2. "<<   std::endl;
	

	if(eTau) m_logger << INFO << " eTau candidate!" << SLogger::endmsg;
	else m_logger << DEBUG << " Checking fully hadronic decay" << SLogger::endmsg;
	
	if(examineThisEvent && signal && eTau){ std::cout << "Found etau candidate" << std::endl;}
	
	
	if(examineThisEvent) std::cout << " " << muTau << muE << eTau << tauTau << std::endl;
	if(Hcand_type.size()!=Hcand.size()/2) m_logger << FATAL << " Mismatch in size of type vector: " << Hcand_type.size() << " is not 1/2 of " << Hcand.size() << SLogger::endmsg; 
	if((Hcand_cat2.size() + Hcand_cat1.size() + Hcand_cat0.size()) ==0){ 
		m_logger << DEBUG << " No Higgs candidate. Going to next event" << SLogger::endmsg; 
	
		return;
	}
	
	Hist("h_Nvertex_AfterZH")->Fill(nGoodVx);
	Hist("h_Nvertex_AfterZH_W")->Fill(nGoodVx,Z_weight);


	// cross-check
	h_cut_flow->Fill(4,1);
	h_cut_flow_weight->Fill(4,Z_weight);
	
		h_cut_flow->Fill(5,1);
	h_cut_flow_weight->Fill(5,Z_weight);

	m_logger << DEBUG << " muTau " << muTau << SLogger::endmsg;
	m_logger << DEBUG << " muE " << muE << SLogger::endmsg;
	m_logger << DEBUG << " eTau " << eTau << SLogger::endmsg;
	m_logger << DEBUG << " tauTau " << tauTau << SLogger::endmsg;

	if(examineThisEvent) std::cout << " Before type assignment" << std::endl;
	std::vector<int> event_type;
	std::vector<double> Hmass;//[3] = {0.0,0.0,0.0};
	event_type.clear();
	Hmass.clear();
	std::vector<myobject> Hcand_sync;
	Hcand_sync.clear();
	
	if(examineThisEvent) std::cout << " There are " << Hcand_type.size() << " event types and " << Hcand.size() << " H candidates." << Hcand_type[0] << std::endl;
	
	for(uint i=0; i< Hcand_type.size() ;i++)
	{
		if(Hcand_type[i]==8 || Hcand_type[i]==4){
		if(examineThisEvent) std::cout << " Type number " << i << " " << Hcand_type[i] << std::endl;	
		if(examineThisEvent) std::cout << " > Correct type!" << Hcand_type[i] << std::endl;
		event_type.push_back(Hcand_type[i]);
		double mass= PairMass(Hcand[2*i],Hcand[2*i+1]);
		if(examineThisEvent) std::cout << " > Mass is " << mass << std::endl;
		Hmass.push_back(mass);
		Hcand_sync.push_back(Hcand[2*i]);
		Hcand_sync.push_back(Hcand[2*i+1]);
		}
	}
	
	for(uint i=0; i< Hcand_type.size() ;i++)
	{
		if(Hcand_type[i]==5 || Hcand_type[i]==3){
		if(examineThisEvent) std::cout << " Type number " << i << " " << Hcand_type[i] << std::endl;
		if(examineThisEvent) std::cout << " > Correct type!" << Hcand_type[i] << std::endl;
		event_type.push_back(Hcand_type[i]);
		double mass= PairMass(Hcand[2*i],Hcand[2*i+1]);
		if(examineThisEvent) std::cout << " > Mass is " << mass << std::endl;
		Hmass.push_back(mass);
		Hcand_sync.push_back(Hcand[2*i]);
		Hcand_sync.push_back(Hcand[2*i+1]);
		}
	}
	
	for(uint i=0; i< Hcand_type.size() ;i++)
	{
		if(Hcand_type[i]==7 || Hcand_type[i]==1){
		if(examineThisEvent) std::cout << " Type number " << i << " " << Hcand_type[i] << std::endl;
		if(examineThisEvent) std::cout << " > Correct type!" << Hcand_type[i] << std::endl;
		event_type.push_back(Hcand_type[i]);
		double mass= PairMass(Hcand[2*i],Hcand[2*i+1]);
		if(examineThisEvent) std::cout << " > Mass is " << mass << std::endl;
		Hmass.push_back(mass);
	//	if(examineThisEvent) std::cout << " > Mass is " << Hmass[0] << std::endl;
		
		Hcand_sync.push_back(Hcand[2*i]);
		Hcand_sync.push_back(Hcand[2*i+1]);
		}
	}
	
		for(uint i=0; i< Hcand_type.size() ;i++)
	{
		if(Hcand_type[i]==6 || Hcand_type[i]==2){
		if(examineThisEvent) std::cout << " Type number " << i << " " << Hcand_type[i] << std::endl;
		if(examineThisEvent) std::cout << " > Correct type!" << Hcand_type[i] << std::endl;
		event_type.push_back(Hcand_type[i]);
		double mass= PairMass(Hcand[2*i],Hcand[2*i+1]);
		if(examineThisEvent) std::cout << " > Mass is " << mass << std::endl;
		Hmass.push_back(mass);
	//	if(examineThisEvent) std::cout << " > Mass is " << Hmass[0] << std::endl;
		
		Hcand_sync.push_back(Hcand[2*i]);
		Hcand_sync.push_back(Hcand[2*i+1]);
		}
	}
		
		
	
	if(examineThisEvent) std::cout << " After type assignment" << std::endl;
	
	// efficiency correction;

	

	double corrHlep1,corrHlep2;
	corrHlep1=corrHlep2=1.0;
	if(isSimulation && !IgnoreSF){

		if(muTau)
		{
			if(is2012_53){
				corrHlep1=Cor_ID_Iso_Mu_Tight_2012_53X(Hcand[0]);
			}else if(is2012_52){
				corrHlep1=Cor_ID_Iso_Mu_Tight_2012(Hcand[0]);
			}else{
				corrHlep1=Cor_ID_Iso_Mu_Tight_2011(Hcand[0]);
			}
		}else if(eTau){
			if(is2012_53){
				corrHlep1=Cor_ID_Iso_Ele_Tight_2012_53X(Hcand[0]);
			}else if(is2012_52){
				corrHlep1=Cor_ID_Iso_Ele_Tight_2012(Hcand[0]);
			}else{
				corrHlep1=Cor_ID_Iso_Ele_Tight_2011(Hcand[0]);
			}
		}else if(muE){
			if(is2012_53){
				corrHlep1=Cor_ID_Iso_Mu_Loose_2012_53X(Hcand[0]);
				corrHlep2=Cor_ID_Iso_Ele_Loose_2012_53X(Hcand[1]);
			}else if(is2012_52){
				corrHlep1=Cor_ID_Iso_Mu_Loose_2012(Hcand[0]);
				corrHlep2=Cor_ID_Iso_Ele_Loose_2012(Hcand[1]);
			}else{
				corrHlep1=Cor_ID_Iso_Mu_Loose_2011(Hcand[0]);
				corrHlep2=Cor_ID_Iso_Ele_Loose_2011(Hcand[1]);
			}
		}
	}

	double weight = PUWeight*corrZlep1*corrZlep2*corrHlep1*corrHlep2;

	TLorentzVector eH_eTau,tauH_eTau,H_eTau;
	TLorentzVector tau1H_tauTau,tau2H_tauTau,H_tauTau;
	TLorentzVector muH_muTau,tauH_muTau,H_muTau;
	TLorentzVector muH_muE_tightMuIso,eH_muE_tightMuIso,H_muE_tightMuIso;
	
	h_cut_flow->Fill(6,1);
	h_cut_flow_weight->Fill(6,weight);
	
        if(!switchToFakeRate){
	if(signal) {h_cut_flow_signal->Fill(1,1);
        }
	else if (category==0) {h_cut_flow_cat0->Fill(1,1);
        }
	else if (category==1) {h_cut_flow_cat1->Fill(1,1);
        }
	else if (category==2) {h_cut_flow_cat2->Fill(1,1);
	}
	if(signal) {h_cut_flow_signal_weight->Fill(1,weight);
        }
	else if (category==0){ 
		h_cut_flow_cat0_weight->Fill(1,weight);
        }
	else if (category==1) {h_cut_flow_cat1_weight->Fill(1,weight);
        }
	else if (category==2) {h_cut_flow_cat2_weight->Fill(1,weight);
	}
	}
	// histograms   
	
	// overlap cleaning

	if(examineThisEvent) std::cout << " After efficiency" << std::endl;
	
    int Event_type=event_type[0];
		
		
	h_cut_flow->Fill(7,1);
	h_cut_flow_weight->Fill(7,weight);

    
	

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
				if(RelIsoMu(genericMuon[iMu]) > 0.3 || !isLooseMu(genericMuon[iMu])) continue;
				if(deltaR(genericMuon[iMu].eta,genericMuon[iMu].phi,jetEta,jetPhi) < 0.4) overlap = true;
			}
			for(uint iEl =0; iEl< genericElectron.size() && !overlap; iEl++)
			{
				if(RelIsoEl(genericElectron[iEl]) > 0.3 || !LooseEleId(genericElectron[iEl])) continue;
				if(deltaR(genericElectron[iEl].eta,genericElectron[iEl].phi,jetEta,jetPhi) < 0.4) overlap = true;
			}
			
			bTagVeto = !overlap;
		
		}
	}
    
	if(examineThisEvent) std::cout << " Before b-tag veto" << std::endl;
	
	if(bTagVeto)
	{
		 //~ if( found_event.size()>0){ 
			 //~ m_logger << ERROR << " Wrong b-tag! H cand of type " << evt_type[pos[0]] << SLogger::endmsg; // sync 
			 //~ log_events << m->runNumber << " "  << m->eventNumber << std::endl;
			//~ log_files << fileName << std::endl;
		//~ }
		m_logger << INFO << "B-jet present. Aborting." << SLogger::endmsg;
		return;
	}
	
	if(examineThisEvent) std::cout << " After b-tag veto" << std::endl;
	
	// now we have the cands
	
	// sync
	bool fatal = false;
	bool used_fatal=false;
	
	
	
	h_cut_flow->Fill(9,1);
	h_cut_flow_weight->Fill(9,weight);

        

	Hist("h_PF_MET_selected")->Fill(Met.front().et,weight);
	h_PF_MET_nPU_selected->Fill(nGoodVx,Met.front().et,weight);
	    std::vector<bool> PassFail;
	    PassFail.clear();
        	TLorentzVector Hcand1,Hcand2,H_boson;
		if(examineThisEvent) std::cout << " checking isolation " << std::endl;
		
		if(examineThisEvent) std::cout << "Now evaluating candidates!" << std::endl;
		for(uint i =0; i < Hcand.size(); i+=2)
            {
				switch(event_type[i/2])
				{
						//tautau
					case 4:
					case 8:
						PassFail.push_back((Hcand_sync[i].byLooseCombinedIsolationDeltaBetaCorr3Hits >= 0.5 && Hcand_sync[i].pt > 10.));
						PassFail.push_back((Hcand_sync[i+1].byLooseCombinedIsolationDeltaBetaCorr3Hits >= 0.5 && Hcand_sync[i+1].pt > 10.));
						break;
						//mutau
					case 1:	
					case 5:
						PassFail.push_back(RelIsoMu(Hcand_sync[i])<0.3 && isLooseMu(Hcand_sync[i]));
						PassFail.push_back((Hcand_sync[i+1].byLooseCombinedIsolationDeltaBetaCorr3Hits >= 0.5 && Hcand_sync[i+1].pt > 10.));
						break;
						//etau
					case 3:
					case 7:
						PassFail.push_back(RelIsoEl(Hcand_sync[i])<0.3 && LooseEleId(Hcand_sync[i]));
						PassFail.push_back((Hcand_sync[i+1].byLooseCombinedIsolationDeltaBetaCorr3Hits >= 0.5 && Hcand_sync[i+1].pt > 10.));
						break;
				}
			}
	
            for(uint i =0; i < Hcand.size(); i+=2)
            {
                myobject ClosestJet = ClosestInCollection(Hcand_sync[i],jet);
                myobject ClosestJet2 = ClosestInCollection(Hcand_sync[i+1],jet);
                if(examineThisEvent) std::cout << " -checking Hcand no. " << i << " type is " << event_type[i/2] << std::endl;
                Hist( "h_event_type" )->Fill(event_type[i/2],weight);
                Hist("h_denom")->Fill(Hcand_sync[i].pt,weight);
                h_denom_types[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
                h_denom_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i].eta,weight);
                
                h_denom_jet_types[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
                h_denom_jet_types_eta[event_type[i/2]-1]->Fill(ClosestJet.eta,weight);
                
                h_denom_jetRef_types[event_type[i/2]-1]->Fill(Hcand_sync[i].jetPt,weight);
                h_denom_jetRef_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i].jetEta,weight);
                
                if(fabs(Hcand_sync[i].eta)<1.2){
					h_denom_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
					h_denom_jet_types_centralEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
					h_denom_jetRef_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].jetPt,weight);
                }else{
					h_denom_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
					h_denom_jet_types_externalEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
					h_denom_jetRef_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].jetPt,weight);
                }
                int isL=0;
                int isM=0;
                int isT=0;
                if(event_type[i/2]%4==3){
                    if(RelIsoEl(Hcand_sync[i]) < 0.30 && LooseEleId(Hcand_sync[i])){ 
						Hist("h_event_type_loose")->Fill(event_type[i/2],weight); 
						h_loose_types[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight); 
						h_loose_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i].eta,weight);
						
						h_loose_jet_types[event_type[i/2]-1]->Fill(ClosestJet.pt,weight); 
						h_loose_jet_types_eta[event_type[i/2]-1]->Fill(ClosestJet.eta,weight); 
						isL++;
						if(fabs(Hcand_sync[i].eta)<1.2){
							h_loose_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
							h_loose_jet_types_centralEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
					
						}else{
							h_loose_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
							h_loose_jet_types_externalEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
						}
					}
                    if(RelIsoEl(Hcand_sync[i]) < 0.15 && isGoodEl(Hcand_sync[i])){ 
						Hist("h_event_type_tight")->Fill(event_type[i/2],weight); 
						h_tight_types[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight); 
						h_tight_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i].eta,weight);
						
						h_tight_jet_types[event_type[i/2]-1]->Fill(ClosestJet.pt,weight); 
						h_tight_jet_types_eta[event_type[i/2]-1]->Fill(ClosestJet.eta,weight); 
						isT++;
						if(fabs(Hcand_sync[i].eta)<1.2){
							h_tight_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
							h_tight_jet_types_centralEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
					
						}else{
							h_tight_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
							h_tight_jet_types_externalEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
						}
							}
                }
                if(event_type[i/2]%4==1){
					if(examineThisEvent) std::cout << " checking muTau isolation " << std::endl;
	
                    if(RelIsoMu(Hcand_sync[i]) < 0.30 && isLooseMu(Hcand_sync[i])){ 
						Hist("h_event_type_loose")->Fill(event_type[i/2],weight); 
						h_loose_types[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight); 
						h_loose_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i].eta,weight);
						
						h_loose_jet_types[event_type[i/2]-1]->Fill(ClosestJet.pt,weight); 
						h_loose_jet_types_eta[event_type[i/2]-1]->Fill(ClosestJet.eta,weight); 
						isL++;
						if(fabs(Hcand_sync[i].eta)<1.2){
							h_loose_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
							h_loose_jet_types_centralEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
					
						}else{
							h_loose_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
							h_loose_jet_types_externalEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
						}
					}
                    if(RelIsoMu(Hcand_sync[i]) < 0.25 && isGoodMu(Hcand_sync[i])){ 
						Hist("h_event_type_tight")->Fill(event_type[i/2],weight); 
						h_tight_types[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight); 
						h_tight_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i].eta,weight);
						
						h_tight_jet_types[event_type[i/2]-1]->Fill(ClosestJet.pt,weight); 
						h_tight_jet_types_eta[event_type[i/2]-1]->Fill(ClosestJet.eta,weight); 
						isT++;
						if(fabs(Hcand_sync[i].eta)<1.2){
							h_tight_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
							h_tight_jet_types_centralEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
					
						}else{
							h_tight_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
							h_tight_jet_types_externalEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
						}
					 }
                }
                if(examineThisEvent) std::cout << " done lepton iso " << std::endl;
                if(event_type[i/2]%4==0){
                    h_denom_types[event_type[i/2]-1]->Fill(Hcand_sync[i+1].pt,weight);
                    h_denom_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i+1].eta,weight);
                    h_denom_jet_types[event_type[i/2]-1]->Fill(ClosestJet2.pt,weight);
					h_denom_jet_types_eta[event_type[i/2]-1]->Fill(ClosestJet2.eta,weight);
                
					h_denom_jetRef_types[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetPt,weight);
					h_denom_jetRef_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetEta,weight);
               
					if(fabs(Hcand_sync[i+1].eta)<1.2){
						h_denom_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].pt,weight);
						h_denom_jet_types_centralEtaRegion[event_type[i/2]-1]->Fill(ClosestJet2.pt,weight);
						h_denom_jetRef_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetPt,weight);
					}else{
						h_denom_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].pt,weight);
						h_denom_jet_types_externalEtaRegion[event_type[i/2]-1]->Fill(ClosestJet2.pt,weight);
						h_denom_jetRef_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetPt,weight);
					}
					if(examineThisEvent) std::cout << "Checking tau 1 with pt " << Hcand_sync[i].pt << std::endl;
                    if(Hcand_sync[i].byLooseCombinedIsolationDeltaBetaCorr3Hits >= 0.5){ 
						if(examineThisEvent) std::cout << "Has loose iso!" << Hcand_sync[i].pt << std::endl;
						Hist("h_event_type_loose")->Fill(event_type[i/2],weight); 
						h_loose_types[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight); 
						h_loose_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i].eta,weight);
						
						h_loose_jet_types[event_type[i/2]-1]->Fill(ClosestJet.pt,weight); 
						h_loose_jet_types_eta[event_type[i/2]-1]->Fill(ClosestJet.eta,weight);
						h_loose_jetRef_types[event_type[i/2]-1]->Fill(Hcand_sync[i].jetPt,weight); 
						h_loose_jetRef_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i].jetEta,weight); 
						isL++;
						if(fabs(Hcand_sync[i].eta)<1.2){
							h_loose_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
							h_loose_jetRef_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].jetPt,weight);
							h_loose_jet_types_centralEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
					
						}else{
							h_loose_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
							h_loose_jetRef_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].jetPt,weight);
							h_loose_jet_types_externalEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
						}
                    }
                     if(examineThisEvent) std::cout << "Checking tau 2 with pt " << Hcand_sync[i+1].pt << std::endl;
                   
                    if(Hcand_sync[i+1].byLooseCombinedIsolationDeltaBetaCorr3Hits >= 0.5){ 
						if(examineThisEvent) std::cout << "Has loose iso!" << Hcand_sync[i+1].pt << std::endl;
						
						Hist("h_event_type_loose")->Fill(event_type[i/2],weight); 
						h_loose_types[event_type[i/2]-1]->Fill(Hcand_sync[i+1].pt,weight); 
						h_loose_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i+1].eta,weight);
						
						h_loose_jet_types[event_type[i/2]-1]->Fill(ClosestJet2.pt,weight); 
						h_loose_jet_types_eta[event_type[i/2]-1]->Fill(ClosestJet2.eta,weight);
						h_loose_jetRef_types[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetPt,weight); 
						h_loose_jetRef_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetEta,weight); 
						isL++;
						if(fabs(Hcand_sync[i+1].eta)<1.2){
							h_loose_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].pt,weight);
							h_loose_jetRef_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetPt,weight);
							h_loose_jet_types_centralEtaRegion[event_type[i/2]-1]->Fill(ClosestJet2.pt,weight);
					
						}else{
							h_loose_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].pt,weight);
							h_loose_jetRef_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetPt,weight);
							h_loose_jet_types_externalEtaRegion[event_type[i/2]-1]->Fill(ClosestJet2.pt,weight);
						}
                    }
                    // medium
                    
                    if(Hcand_sync[i].byMediumCombinedIsolationDeltaBetaCorr3Hits >= 0.5){ 
						if(examineThisEvent) std::cout << "tau 1 Passed medium iso" << std::endl;
						Hist("h_event_type_medium")->Fill(event_type[i/2],weight); 
						h_medium_types[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight); 
						h_medium_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i].eta,weight);
						
						h_medium_jet_types[event_type[i/2]-1]->Fill(ClosestJet.pt,weight); 
						h_medium_jet_types_eta[event_type[i/2]-1]->Fill(ClosestJet.eta,weight);
						h_medium_jetRef_types[event_type[i/2]-1]->Fill(Hcand_sync[i].jetPt,weight); 
						h_medium_jetRef_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i].jetEta,weight); 
						isM++;
						if(fabs(Hcand_sync[i].eta)<1.2){
							h_medium_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
							h_medium_jetRef_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].jetPt,weight);
							h_medium_jet_types_centralEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
					
						}else{
							h_medium_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
							h_medium_jetRef_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].jetPt,weight);
							h_medium_jet_types_externalEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
						}
                    }
                    if(Hcand_sync[i+1].byMediumCombinedIsolationDeltaBetaCorr3Hits >= 0.5){ 
						if(examineThisEvent) std::cout << "tau 2 Passed medium iso" << std::endl;
						Hist("h_event_type_medium")->Fill(event_type[i/2],weight); 
						h_medium_types[event_type[i/2]-1]->Fill(Hcand_sync[i+1].pt,weight); 
						h_medium_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i+1].eta,weight);
						
						h_medium_jet_types[event_type[i/2]-1]->Fill(ClosestJet2.pt,weight); 
						h_medium_jet_types_eta[event_type[i/2]-1]->Fill(ClosestJet2.eta,weight);
						h_medium_jetRef_types[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetPt,weight); 
						h_medium_jetRef_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetEta,weight); 
						isM++;
						if(fabs(Hcand_sync[i+1].eta)<1.2){
							h_medium_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].pt,weight);
							h_medium_jetRef_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetPt,weight);
							h_medium_jet_types_centralEtaRegion[event_type[i/2]-1]->Fill(ClosestJet2.pt,weight);
					
						}else{
							h_medium_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].pt,weight);
							h_medium_jetRef_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetPt,weight);
							h_medium_jet_types_externalEtaRegion[event_type[i/2]-1]->Fill(ClosestJet2.pt,weight);
						}
                    }
                    //tight
                    
                    if(Hcand_sync[i].byTightCombinedIsolationDeltaBetaCorr3Hits >= 0.5){ 
						Hist("h_event_type_tight")->Fill(event_type[i/2],weight); 
						h_tight_types[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight); 
						h_tight_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i].eta,weight);
						
						h_tight_jet_types[event_type[i/2]-1]->Fill(ClosestJet.pt,weight); 
						h_tight_jet_types_eta[event_type[i/2]-1]->Fill(ClosestJet.eta,weight);
						h_tight_jetRef_types[event_type[i/2]-1]->Fill(Hcand_sync[i].jetPt,weight); 
						h_tight_jetRef_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i].jetEta,weight); 
						isT++;
						if(fabs(Hcand_sync[i].eta)<1.2){
							h_tight_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
							h_tight_jetRef_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].jetPt,weight);
							h_tight_jet_types_centralEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
					
						}else{
							h_tight_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].pt,weight);
							h_tight_jetRef_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i].jetPt,weight);
							h_tight_jet_types_externalEtaRegion[event_type[i/2]-1]->Fill(ClosestJet.pt,weight);
						}
                    }
                    if(Hcand_sync[i+1].byTightCombinedIsolationDeltaBetaCorr3Hits >= 0.5){ 
						Hist("h_event_type_tight")->Fill(event_type[i/2],weight); 
						h_tight_types[event_type[i/2]-1]->Fill(Hcand_sync[i+1].pt,weight); 
						h_tight_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i+1].eta,weight);
						
						h_tight_jet_types[event_type[i/2]-1]->Fill(ClosestJet2.pt,weight); 
						h_tight_jet_types_eta[event_type[i/2]-1]->Fill(ClosestJet2.eta,weight);
						h_tight_jetRef_types[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetPt,weight); 
						h_tight_jetRef_types_eta[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetEta,weight); 
						isT++;
						if(fabs(Hcand_sync[i+1].eta)<1.2){
							h_tight_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].pt,weight);
							h_tight_jetRef_types_centralEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetPt,weight);
							h_tight_jet_types_centralEtaRegion[event_type[i/2]-1]->Fill(ClosestJet2.pt,weight);
					
						}else{
							h_tight_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].pt,weight);
							h_tight_jetRef_types_externalEtaRegion[event_type[i/2]-1]->Fill(Hcand_sync[i+1].jetPt,weight);
							h_tight_jet_types_externalEtaRegion[event_type[i/2]-1]->Fill(ClosestJet2.pt,weight);
						}
                    }
                }// end of tautau
                
                    
                Hcand1.SetPxPyPzE(Hcand[i].px,Hcand[i].py,Hcand[i].pz,Hcand[i].E);
                Hcand2.SetPxPyPzE(Hcand[i+1].px,Hcand[i+1].py,Hcand[i+1].pz,Hcand[i+1].E);
                H_boson = Hcand1+Hcand2;
               // double Hmass = H_boson.M();
                
               
                
            }

            if(RelIsoEl(Hcand[0]) < 0.25) Hist("h_medium")->Fill(Hcand[0].pt,weight);
            if(RelIsoEl(Hcand[0]) < 0.10) Hist("h_tight")->Fill(Hcand[0].pt,weight);

            //TLorentzVector Hcand1,Hcand2,H_boson;

            for(uint i =0;i < Hcand.size(); i+=2){
                Hcand1.SetPxPyPzE(Hcand[i].px,Hcand[i].py,Hcand[i].pz,Hcand[i].E);
                Hcand2.SetPxPyPzE(Hcand[i+1].px,Hcand[i+1].py,Hcand[i+1].pz,Hcand[i+1].E);
                H_boson = Hcand1+Hcand2;
                h_H_mass_types[Event_type-1]->Fill(H_boson.M(),weight);
            }

        
			
			 if(printoutEvents)
				{
					if(examineThisEvent) std::cout << " in printout " << std::endl;
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
						
						log1 << setiosflags(ios::fixed) << std::setprecision(1) << exp_event_type << " " << name << " " << status << " " <<  
						m->runNumber << " " << m->lumiNumber << " " << m->eventNumber << " " << Zmass << " " << mass  << "     " << fileName << std::endl;
						
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
						std::string status="PF";
						
						log1 << setiosflags(ios::fixed) << std::setprecision(1) << exp_event_type << " " << name << " " << status << " " <<  
						m->runNumber << " " << m->lumiNumber << " " << m->eventNumber << " " << Zmass << " " << mass  << "     " << fileName << std::endl;
						
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
						std::string status="FP";
						
						log1 << setiosflags(ios::fixed) << std::setprecision(1) << exp_event_type << " " << name << " " << status << " " <<  
						m->runNumber << " " << m->lumiNumber << " " << m->eventNumber << " " << Zmass << " " << mass  << "     " << fileName << std::endl;
						
					}
					
				}
        
	return;


}

