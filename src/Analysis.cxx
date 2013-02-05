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
	h_event_type_medium 			         = Book(TH1D("h_event_type_medium","Event Type passing iso < 0.25",8,0.5,8.5));
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

        for(uint i = 1; i <= (uint)h_event_type->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_medium_type_" << i;
                std::string name = s.str();
                std::stringstream ss;
                ss <<  "Iso < 0.25 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
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
                ss <<  "Iso < 0.25 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";#eta";
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
                ss <<  "Iso < 0.25 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
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
                ss <<  "Iso < 0.25 for events of type " << h_event_type->GetXaxis()->GetBinLabel(i) << ";P_{T}";
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

	if(printoutEvents) log1.open("events.txt");
	
	//bookkeeping
	lumi.open("lumi.csv");
	current_run=current_lumi=-999;
	
	// sync part
	std::ifstream myfile;
	myfile.open ("ulb_in.txt");
	 if (myfile.is_open())
	 {	
	    
	    while ( myfile.good() )
	    {
	      int i_number;
		  double number;
		  short my_FR_type=-1; 
		  myfile >> i_number;
		  int e_type = i_number/100;
		  int FR_type = i_number%100;
		  if(FR_type==1) my_FR_type=0;
		  else if(FR_type==2) my_FR_type= 3;
		  else if(FR_type==3 && (e_type%4==1)) my_FR_type= 2;
		  else my_FR_type= 1;	
		//  std::cout << i_number << " " << EventTypeConv(e_type) << " " << my_FR_type << std::endl;
		  switch(my_FR_type){
			case 0:
				evt_type.push_back(EventTypeConv(e_type));      
				myfile >> i_number;
				run_number.push_back(i_number);
				myfile >> i_number;
				lumi_number.push_back(i_number);
				myfile >> i_number;
				evt_number.push_back(i_number);
				myfile >> number;
				mass_Z.push_back(number);
				myfile >> number;
				mass_H.push_back(number);
				break;
			case 1:
				evt_type_l.push_back(EventTypeConv(e_type));      
				myfile >> i_number;
				run_number_l.push_back(i_number);
				myfile >> i_number;
				lumi_number_l.push_back(i_number);
				myfile >> i_number;
				evt_number_l.push_back(i_number);
				myfile >> number;
				mass_Z_l.push_back(number);
				myfile >> number;
				mass_H_l.push_back(number);
				break;
			case 2:
				evt_type_m.push_back(EventTypeConv(e_type));      
				myfile >> i_number;
				run_number_m.push_back(i_number);
				myfile >> i_number;
				lumi_number_m.push_back(i_number);
				myfile >> i_number;
				evt_number_m.push_back(i_number);
				myfile >> number;
				mass_Z_m.push_back(number);
				myfile >> number;
				mass_H_m.push_back(number);
				break;
			case 3:
				evt_type_t.push_back(EventTypeConv(e_type));      
				myfile >> i_number;
				run_number_t.push_back(i_number);
				myfile >> i_number;
				lumi_number_t.push_back(i_number);
				myfile >> i_number;
				evt_number_t.push_back(i_number);
				myfile >> number;
				mass_Z_t.push_back(number);
				myfile >> number;
				mass_H_t.push_back(number);
				break;
		  }	
		  
		
	    }
	    myfile.close();
	  }
	//~ evt_number.pop_back();
	//~ run_number.pop_back();
	//~ lumi_number.pop_back();
	//~ evt_type.pop_back();
	//~ mass_Z.pop_back();
	//~ mass_H.pop_back();
	//~ 
	evt_number_l.pop_back();
	run_number_l.pop_back();
	lumi_number_l.pop_back();
	evt_type_l.pop_back();
	mass_Z_l.pop_back();
	mass_H_l.pop_back();
	//~ 
	//~ evt_number_m.pop_back();
	//~ run_number_m.pop_back();
	//~ lumi_number_m.pop_back();
	//~ evt_type_m.pop_back();
	//~ mass_Z_m.pop_back();
	//~ mass_H_m.pop_back();
	//~ 
	//~ evt_number_t.pop_back();
	//~ run_number_t.pop_back();
	//~ lumi_number_t.pop_back();
	//~ evt_type_t.pop_back();
	//~ mass_Z_t.pop_back();
	//~ mass_H_t.pop_back();
	
	  std::cout << evt_number.size() << " " << run_number.size() << " " << lumi_number.size() << " " << evt_type.size() << 
	  " " << mass_Z.size() <<  std::endl;
	  std::cout << evt_number_l.size() << " " << run_number_l.size() << " " << lumi_number_l.size() << " " << evt_type_l.size() << 
	  " " << mass_Z_l.size() <<  std::endl;
	  std::cout << evt_number_m.size() << " " << run_number_m.size() << " " << lumi_number_m.size() << " " << evt_type_m.size() << 
	  " " << mass_Z_m.size() <<  std::endl;	
	  std::cout << evt_number_t.size() << " " << run_number_t.size() << " " << lumi_number_t.size() << " " << evt_type_t.size() << 
	  " " << mass_Z_t.size() <<  std::endl;
	  
	  std::cout << evt_number.at(evt_number.size()-1) << " " << run_number.at(evt_number.size()-1) << " " << lumi_number.at(evt_number.size()-1) << " " << evt_type.at(evt_number.size()-1) << 
	  " " << mass_Z.at(evt_number.size()-1) <<  std::endl;
	  std::cout << evt_number_l.at(evt_number_l.size()-1) << " " << run_number_l.at(evt_number_l.size()-1) << " " << lumi_number_l.at(evt_number_l.size()-1) << " " << evt_type_l.at(evt_number_l.size()-1) << 
	  " " << mass_Z_l.at(evt_number_l.size()-1) <<  std::endl;
	  std::cout << evt_number_m.at(evt_number_m.size()-1) << " " << run_number_m.at(evt_number_m.size()-1) << " " << lumi_number_m.at(evt_number_m.size()-1) << " " << evt_type_m.at(evt_number_m.size()-1) << 
	  " " << mass_Z_m.at(evt_number_m.size()-1) <<  std::endl;	
	  std::cout << evt_number_t.at(evt_number_t.size()-1) << " " << run_number_t.at(evt_number_t.size()-1) << " " << lumi_number_t.at(evt_number_t.size()-1) << " " << evt_type_t.at(evt_number_t.size()-1) << 
	  " " << mass_Z_t.at(evt_number_t.size()-1) <<  std::endl;
	  
	  //~ std::cout << evt_number.at(evt_number.size()-2) << " " << run_number.at(evt_number.size()-2) << " " << lumi_number.at(evt_number.size()-2) << " " << evt_type.at(evt_number.size()-2) << 
	  //~ " " << mass_Z.at(evt_number.size()-2) <<  std::endl;
	  //~ std::cout << evt_number_l.at(evt_number_l.size()-2) << " " << run_number_l.at(evt_number_l.size()-2) << " " << lumi_number_l.at(evt_number_l.size()-2) << " " << evt_type_l.at(evt_number_l.size()-2) << 
	  //~ " " << mass_Z_l.at(evt_number_l.size()-2) <<  std::endl;
	  //~ std::cout << evt_number_m.at(evt_number_m.size()-2) << " " << run_number_m.at(evt_number_m.size()-2) << " " << lumi_number_m.at(evt_number_m.size()-2) << " " << evt_type_m.at(evt_number_m.size()-2) << 
	  //~ " " << mass_Z_m.at(evt_number_m.size()-2) <<  std::endl;	
	  //~ std::cout << evt_number_t.at(evt_number_t.size()-2) << " " << run_number_t.at(evt_number_t.size()-2) << " " << lumi_number_t.at(evt_number_t.size()-2) << " " << evt_type_t.at(evt_number_t.size()-2) << 
	  //~ " " << mass_Z_t.at(evt_number_t.size()-2) <<  std::endl;
	
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

	std::cout << "Iso < 0.25 summary: " << std::endl;
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

	if(printoutEvents) log1.close();
	
	
	
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

bool Analysis::EleMVANonTrigId(float pt, float eta, double value){
	bool passingId=false;

	if(pt>5. && pt<10. && fabs(eta)<0.8 && value>0.47)
		passingId=true;
	if(pt>5. && pt<10. && fabs(eta)>=0.8 && fabs(eta)<1.479 && value>0.004)
		passingId=true;
	if(pt>5. && pt<10. && fabs(eta)>=1.479 && value>0.294)
		passingId=true;

	if(pt>10. && fabs(eta)<0.8 && value>0.5)
		passingId=true;
	if(pt>10. && fabs(eta)>=0.8 && fabs(eta)<1.479 && value>0.12)
		passingId=true;
	if(pt>10. && fabs(eta)>=1.479 && value>0.6)
		passingId=true;
	//  if(value>10.)cout<<"pt==== "<<pt<<" "<<"eta=== "<<eta<<" "<<"value=== "<<value<<endl;
	return passingId;
}

bool Analysis::PFMuonID(myobject mu){

	if(mu.isGlobalMuon &&  mu.isPFMuon && mu.normalizedChi2 < 10. && mu.numberOfValidMuonHits > 0 && mu.numMatchStation > 1 && mu.dB < 0.2
			&& mu.dZ_in < 0.5 && mu.intrkLayerpixel > 0 && mu.trkLayerMeasure > 5) return true;
	else
		return false;

}

double Analysis::RelIsoMu(myobject mu){

	double MuIsoTrk = mu.pfIsoCharged;
	double MuIsoEcal = mu.pfIsoGamma;
	double MuIsoHcal = mu.pfIsoNeutral;
	double MuIsoPU = mu.pfIsoPU;
	double relIso = (MuIsoTrk) / mu.pt;
	if (MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU > 0)
		relIso = (MuIsoTrk + MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU) / (mu.pt);

	return relIso;
}

double Analysis::RelIsoEl(myobject el){
	double ElIsoTrk = el.pfIsoCharged;
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

        vector<myobject> Met = m->RecPFMet;
        bool met = Met.front().pt < 20.0;

        double tMass_v = sqrt(2*mu.pt*Met.front().et*(1-cos(Met.front().phi-mu.phi)));
        bool tMass = tMass_v < 30.0;

        if(met && tMass)
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
				deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand[j+1].eta,Hcand[j+1].phi)> maxDeltaR && isGoodMu(genericMuon[i]) && RelIsoMu(genericMuon[i]) < 0.4) 
			Ad_lepton=true;
	   }
	   if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
    }
    if(verbose) std::cout << "There are " << genericElectron.size() << " additional electrons." << std::endl;
	for(uint i = 0; i < genericElectron.size(); i++)
	{   
		for(uint j =0; j < Hcand.size(); j+=2){
			if(deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand[j].eta,Hcand[j].phi)> maxDeltaR &&
				deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand[j+1].eta,Hcand[j+1].phi)> maxDeltaR && isGoodEl(genericElectron[i])  && RelIsoEl(genericElectron[i]) < 0.4)  
			Ad_lepton=true;
	   }
	   if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;
	}
	return Ad_lepton;
}

bool Analysis::AdLepton(std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, myobject Hcand1, myobject Hcand2){
	bool Ad_lepton=false;
	for(uint i = 0; i < genericMuon.size(); i++)
	{   
			if(deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand1.eta,Hcand1.phi)> maxDeltaR &&
				deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand2.eta,Hcand2.phi)> maxDeltaR && isGoodMu(genericMuon[i]) < 0.4) 
			Ad_lepton=true;
	   
    }
	for(uint i = 0; i < genericElectron.size(); i++)
	{   
			if(deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand1.eta,Hcand1.phi)> maxDeltaR &&
				deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand2.eta,Hcand2.phi)> maxDeltaR && isGoodEl(genericElectron[i]) < 0.4)  
			Ad_lepton=true;
	   
	}
	return Ad_lepton;
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

bool Analysis::isGoodEl(myobject el){
	        
	        double elPt = el.pt;
                double elEta = el.eta;
                int missingHits = el.numLostHitEleInner;
                bool elID = EleMVANonTrigId(elPt,elEta,el.Id_mvaNonTrg);
                double relIso = RelIsoEl(el);

                if (elPt > 10. && fabs(elEta) < 2.5  && elID && missingHits <=1)
                {
                        return true;
                }else return false;
}

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

void Analysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
	entries++;
		
	 // sync part
	bool found_event = false;
	bool isLoose = false;
	bool isMedium = false;
	bool isTight = false;
	// end sync

	// bookkepping part
		++m_allEvents;
	if(m->runNumber!=current_run || m->lumiNumber!=current_lumi){
		lumi << m->runNumber << " " << m->lumiNumber << std::endl;
		current_run=m->runNumber;
		current_lumi=m->lumiNumber;
	}

	m_logger << DEBUG << " Now executing event " << m->eventNumber << " in a run " << m->runNumber << SLogger::endmsg;

		Hist("h_nPU_Info")->Fill(m->PUInfo);
		Hist("h_nPU_InfoTrue")->Fill(m->PUInfo_true);
		Hist("h_nPU_Bunch0")->Fill(m->PUInfo_Bunch0);

        if(switchToFakeRate && UseSumPtCut){
        Cut_tau_base_Pt  = 0;
        Cut_tautau_sumPt = 0;
        Cut_leptau_sumPt = 0;
        Cut_leplep_sumPt = 0;
	}
        else if(!switchToFakeRate && UseSumPtCut){
        Cut_tau_base_Pt  = 20;
        Cut_tautau_sumPt = 60;
        Cut_leptau_sumPt = 45;
        Cut_leplep_sumPt = 30;
	}
	if(!switchToFakeRate){	
		if(Cut_tau_base_Pt< 1e-3 && Cut_tau_base_Pt >= 0) Cut_tau_base_Pt=20;
		if(Cut_tautau_Pt_1< 1e-3 && Cut_tautau_Pt_1 >= 0) Cut_tautau_Pt_1=20;
		if(Cut_tautau_Pt_2< 1e-3 && Cut_tautau_Pt_2 >= 0) Cut_tautau_Pt_2=20;
	    }

	double PUWeight = 1.0;
	double nPU = 0.0;
	if(useTruePileUp || !is2011)  nPU = m->PUInfo_true;
	else nPU = m->PUInfo_Bunch0;
	if(isSimulation){	
		PUWeight = LumiWeights_->weight( nPU );
		if(IgnorePUW) PUWeight = 1.0;
	}
	int eNumber = m->eventNumber;
	
	// sync
	uint pos = std::find(evt_number.begin(), evt_number.end(), eNumber) - evt_number.begin();
	if( pos < evt_number.size()  )
	{
		found_event = true;
	}
	uint pos_l=0,pos_t=0;
	if(found_event)
	{
		uint pos_l = std::find(evt_number_l.begin(), evt_number_l.end(), eNumber) - evt_number_l.begin();
		if( pos_l < evt_number_l.size() )
		{
			isLoose = true;
		}
		
		uint pos_m = std::find(evt_number_m.begin(), evt_number_m.end(), eNumber) - evt_number_m.begin();
		if( pos_m < evt_number_m.size() )
		{
				isMedium = true;
		}
		
		uint pos_t = std::find(evt_number_t.begin(), evt_number_t.end(), eNumber) - evt_number_t.begin();
		if( pos_t < evt_number_t.size() )
		{
			isTight = true;
		}
	}
	
	
	// end sync
	
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

	bool trigPass,examineThisEvent;
	if( examineEvent==eNumber) examineThisEvent=true;
	else examineThisEvent=false;
	trigPass = Trg_MC_12(m,examineThisEvent);
	if(examineThisEvent) std::cout << "Examining event " << examineEvent << std::endl;
	m_logger << DEBUG <<" Trigger decision " << trigPass << SLogger::endmsg;
	if(!trigPass)
	{
	  if(found_event) m_logger << ERROR << "ENTRY " << m_allEvents <<", event " << eNumber << ":  WRONG TRIGGER" << SLogger::endmsg; // sync
		return;
	}
	if(found_event) m_logger << ERROR << "ENTRY " << m_allEvents << ": Found event " << eNumber << " type " << evt_type[pos] << " loose/medium/tight: " << isLoose << "/" << isMedium << "/" << isTight << SLogger::endmsg; // sync
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
	std::vector<int> DenomToGoodMuon_assoc_index; // indices of good muons
	DenomToGoodMuon_assoc_index.clear();
	std::vector<int> GoodToDenomMuon_assoc_index; // indices of denom muons
	GoodToDenomMuon_assoc_index.clear();


	std::vector<myobject> muon = m->PreSelectedMuons;
	m_logger << DEBUG << " There are " << muon.size() << " preselected muons " << SLogger::endmsg;

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
				GoodToDenomMuon_assoc_index.push_back(denomMuon.size());
				DenomToGoodMuon_assoc_index.push_back(goodMuon.size());
				goodMuon.push_back(muon[i]);
				Hist("h_mu_relIso")->Fill(relIso,PUWeight);
			}
                                
				denomMuon.push_back(muon[i]);
		}
        }

	Hist("h_n_goodMu")->Fill(goodMuon.size(),PUWeight);

	std::vector<myobject> goodElectron;
	goodElectron.clear();
        std::vector<myobject> denomElectron;
        denomElectron.clear();
        std::vector<int> DenomToGoodElectron_assoc_index; // indices of good electrons
        DenomToGoodElectron_assoc_index.clear();
        std::vector<int> GoodToDenomElectron_assoc_index; // indices of denom electrons
        GoodToDenomElectron_assoc_index.clear();

	std::vector<myobject> electron = m->PreSelectedElectrons;
	//m_logger << DEBUG << " There are " << electron.size() << " preselected electrons " << SLogger::endmsg;

	for (uint i = 0; i < electron.size(); i++) {

		double elPt = electron[i].pt;
		double elEta = electron[i].eta;
		int missingHits = electron[i].numLostHitEleInner;
		bool elID = EleMVANonTrigId(elPt,elEta,electron[i].Id_mvaNonTrg);
		double relIso = RelIsoEl(electron[i]);

		if (elPt > 10. && fabs(elEta) < 2.5)
		{
			if(missingHits <=1 && elID){
				GoodToDenomElectron_assoc_index.push_back(denomElectron.size());
				DenomToGoodElectron_assoc_index.push_back(goodElectron.size());
				goodElectron.push_back(electron[i]);
				Hist("h_el_relIso")->Fill(relIso,PUWeight);
			}else{
				DenomToGoodElectron_assoc_index.push_back(-1);
			}
				denomElectron.push_back(electron[i]);
                }
	}

	//m_logger << DEBUG << " There are " << goodElectron.size() << " good electrons " << " and " << GoodToDenomElectron_assoc_index.size() << " goodToDenom eles " << SLogger::endmsg;
	//m_logger << DEBUG << " There are " << denomElectron.size() << " denom electrons " << " and " << DenomToGoodElectron_assoc_index.size() << "denomToGood eles " << SLogger::endmsg;
	int muCandZ = goodMuon.size();
	int elCandZ = goodElectron.size();
	Hist("h_n_goodEl")->Fill(goodElectron.size(),PUWeight);
	// Z compatibility
	std::vector<myobject> Zcand;
	Zcand.clear();
	bool Zmumu = false;
	bool Zee = false;
	bool Zmucand, Zelcand;
	Zmucand=Zelcand=false;
	double dMass=999.0;
	int Zindex[2] = {-1,-1};
	for(uint i = 0; i < goodMuon.size(); i++)
	{
		m_logger << VERBOSE << "  ->good muon no. "<< i << " has pt "<<  goodMuon[i].pt << " and charge " << goodMuon[i].charge << SLogger::endmsg;
		if(Zmumu) continue;
		if(RelIsoMu(goodMuon[i]) > 0.3) continue;
		for(uint j = i+1; j < goodMuon.size() && !Zmumu; j++)
		{
			m_logger << VERBOSE << "  -->second muon no. "<< j << " has pt "<<  goodMuon[j].pt << " and charge " << goodMuon[j].charge << SLogger::endmsg;

			if(RelIsoMu(goodMuon[j]) > 0.3) continue;
			if(goodMuon[i].charge*goodMuon[j].charge >=0.) continue;
			if(deltaR(goodMuon[i].eta,goodMuon[i].phi,goodMuon[j].eta,goodMuon[j].phi)< maxDeltaR) continue;

			TLorentzVector cand;
			cand.SetPxPyPzE(goodMuon[i].px+goodMuon[j].px,
					goodMuon[i].py+goodMuon[j].py,
					goodMuon[i].pz+goodMuon[j].pz,
					goodMuon[i].E+goodMuon[j].E);
			double mass = cand.M();
			m_logger << VERBOSE << "  -->Candidate mass is " << mass << SLogger::endmsg;
			if(mass > 80. && mass < 100.){
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
			int denom_i = GoodToDenomMuon_assoc_index[i];
			int denom_j = GoodToDenomMuon_assoc_index[j];
		if(goodMuon[i].pt > 20.){
			Zcand.push_back(goodMuon[i]);
			Zcand.push_back(goodMuon[j]);
			goodMuon.erase(goodMuon.begin()+i);
			goodMuon.erase(goodMuon.begin()+j-1);
			denomMuon.erase(denomMuon.begin()+denom_i);
			denomMuon.erase(denomMuon.begin()+denom_j-1);

			Zmumu=true;
		}
	}


	m_logger << VERBOSE << " There are " << goodMuon.size() << " remaining good muons " << SLogger::endmsg;

	if(!Zmumu)
	{
		dMass = 999.;
		for(uint i = 0; i < goodElectron.size(); i++)
		{
			m_logger << VERBOSE << " ->good electron no. "<< i << " has pt "<<  goodElectron[i].pt << " and charge " << goodElectron[i].charge << SLogger::endmsg;
			//if( goodElectron[i].pt < 20 || 
			if(Zee) continue;
			if(RelIsoEl(goodElectron[i]) > 0.3) continue;
			for(uint j = i+1; j < goodElectron.size() && !Zee; j++)
			{
				m_logger << VERBOSE << "  -->second electron no. "<< j << " has pt "<<  goodElectron[j].pt << " and charge " << goodElectron[j].charge << SLogger::endmsg;
				if(RelIsoEl(goodElectron[j]) > 0.3) continue;	
				if(goodElectron[i].charge*goodElectron[j].charge >=0.) continue;
				if(deltaR(goodElectron[i].eta,goodElectron[i].phi,goodElectron[j].eta,goodElectron[j].phi)< maxDeltaR) continue;

				TLorentzVector cand;
				cand.SetPxPyPzE(goodElectron[i].px+goodElectron[j].px,
						goodElectron[i].py+goodElectron[j].py,
						goodElectron[i].pz+goodElectron[j].pz,
						goodElectron[i].E+goodElectron[j].E);
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
				int denom_i = GoodToDenomElectron_assoc_index[i];
				int denom_j = GoodToDenomElectron_assoc_index[j];

			if(goodElectron[i].pt > 20.){			
				Zcand.push_back(goodElectron[i]);
				Zcand.push_back(goodElectron[j]);	
				goodElectron.erase(goodElectron.begin()+i);
				goodElectron.erase(goodElectron.begin()+j-1);
				denomElectron.erase(denomElectron.begin()+denom_i);
				denomElectron.erase(denomElectron.begin()+denom_j-1);
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
			return;
	}
	
	h_cut_flow->Fill(3,1);
	h_cut_flow_weight->Fill(3,Z_weight);
	
	Hist("h_Nvertex_AfterZ")->Fill(nGoodVx);
	Hist("h_Nvertex_AfterZ_W")->Fill(nGoodVx,Z_weight);

	// Z overlap removal

	for(uint i = 0; i < goodMuon.size(); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			if(deltaR(goodMuon[i].eta,goodMuon[i].phi,Zcand[j].eta,Zcand[j].phi)< maxDeltaR) 
			{	goodMuon.erase(goodMuon.begin()+i); i--;removed = true;}
		}
	}
	for(uint i = 0; i < denomMuon.size(); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			if(deltaR(denomMuon[i].eta,denomMuon[i].phi,Zcand[j].eta,Zcand[j].phi)< maxDeltaR) 
			{	denomMuon.erase(denomMuon.begin()+i); i--;removed = true;}
		}
	}
	Hist("h_n_goodMu_Hcand")->Fill(goodMuon.size());

	for(uint i = 0; i < goodElectron.size(); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			if(deltaR(goodElectron[i].eta,goodElectron[i].phi,Zcand[j].eta,Zcand[j].phi)< maxDeltaR) 
			{	goodElectron.erase(goodElectron.begin()+i); i--; removed = true;}
		}

		for(uint j = 0; j < goodMuon.size() && !removed; j++)
		{
			if(deltaR(goodElectron[i].eta,goodElectron[i].phi,goodMuon[j].eta,goodMuon[j].phi)< maxDeltaR && RelIsoMu(goodMuon[j]) < 0.4) 
			{	goodElectron.erase(goodElectron.begin()+i); i--; removed = true;}
		}
	}

	for(uint i = 0; i < denomElectron.size(); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			if(deltaR(denomElectron[i].eta,denomElectron[i].phi,Zcand[j].eta,Zcand[j].phi)< maxDeltaR) 
			{	denomElectron.erase(denomElectron.begin()+i); i--; removed = true;}
		}

		for(uint j = 0; j < denomMuon.size() && !removed; j++)
		{
			if(deltaR(denomElectron[i].eta,denomElectron[i].phi,denomMuon[j].eta,denomMuon[j].phi)< maxDeltaR) 
			{	denomElectron.erase(denomElectron.begin()+i); i--; removed = true;}
		}
	}

	//m_logger << DEBUG << " There are " << goodMuon.size() << " and " << goodElectron.size() << " remaining after Z overlap removal " << SLogger::endmsg;
	Hist("h_n_goodEl_Hcand")->Fill(goodElectron.size());	
 
        //generic vector definitions for MUONS and ELECTRONS
	std::vector<myobject> genericMuon;
        genericMuon.clear();
	std::vector<myobject> genericElectron;
        genericElectron.clear();
      
        if(!switchToFakeRate){
        genericMuon = goodMuon;
        genericElectron = goodElectron;}
        else{
        genericMuon = denomMuon;
        genericElectron = denomElectron;}
        

	

	// checking the rest of the event
	// list of good taus 
	std::vector<myobject> goodTau;
	goodTau.clear();
	int muCand = genericMuon.size();
	int elCand = genericElectron.size();

	std::vector<myobject> tau = m->PreSelectedHPSTaus;

	//m_logger << DEBUG << " There are " << tau.size() << " preselected taus " << SLogger::endmsg;

	for (uint i = 0; i < tau.size(); i++) {

		double tauPt = tau[i].pt;
		double tauEta = tau[i].eta;
		bool LooseElectron = (tau[i].discriminationByElectronLoose > 0.5);
		bool LooseMuon = (tau[i].discriminationByMuonLoose > 0.5);
		bool CombinedIsolation = (tau[i].byMediumCombinedIsolationDeltaBetaCorr > 0.5);
		bool DecayMode = (tau[i].discriminationByDecayModeFinding > 0.5);


		if (tauPt > Cut_tau_base_Pt && fabs(tauEta) < 2.3 && LooseElectron && LooseMuon && DecayMode){
			goodTau.push_back(tau[i]);}
	}

        //check the overlap
	if(removeTauOverlap){
	for(uint i = 0; i < goodTau.size(); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			if(deltaR(goodTau[i].eta,goodTau[i].phi,Zcand[j].eta,Zcand[j].phi)< maxDeltaR) 
		               {goodTau.erase(goodTau.begin()+i); i--; removed = true;}
		}
		
		for(uint j = 0; j < genericMuon.size() && !removed; j++)
		{    
			if(deltaR(goodTau[i].eta,goodTau[i].phi,genericMuon[j].eta,genericMuon[j].phi)< maxDeltaR 	 ) 
				{goodTau.erase(goodTau.begin()+i); i--; removed = true;}
		        
        }

		for(uint j = 0; j < genericElectron.size() && !removed; j++)
		{
                        
			if(deltaR(goodTau[i].eta,goodTau[i].phi,genericElectron[j].eta,genericElectron[j].phi)< maxDeltaR ) 
				{goodTau.erase(goodTau.begin()+i); i--; removed = true;}
		        
        }
	}
	}

	int tauCand = 	goodTau.size();
	if(examineThisEvent) std::cout << " There are " << tauCand << " tau candidates " << std::endl;
		
	Hist("h_n_goodTau_Hcand")->Fill(goodTau.size());	

	// mutau and emu final states
	bool muTau=false;
	bool muE = false;
	bool signal = false;
	short category = -1;       
	int Hindex[2] = {-1,-1};
	std::vector<myobject> Hcand;
	Hcand.clear();
	
	if(examineThisEvent) std::cout << " There are " << genericMuon.size() << " mu candidates " << std::endl;
	
	for(uint i = 0; i < genericMuon.size() && !signal; i++)
	{

		if(examineThisEvent) std::cout << " Looping over muon no.  " << i << std::endl;
	
		double relIso = RelIsoMu(genericMuon[i]);
		bool iso1_muE = (relIso < 0.3);
		bool iso1_muTau = (relIso < 0.15);
                
		if(!switchToFakeRate){		
			if(!checkCategories && !iso1_muE) continue;}
			if(examineThisEvent) std::cout << " Checking electrons " << std::endl;
	
		for(uint j=0; j < genericElectron.size() && !signal; j++)
		{
                        //the following switch could be also omitted
                        //since in the case of switchToFakeRate && UseSumPtCut
                        //Cut_leplep_sumPt is 0
            if(examineThisEvent) std::cout << " electron no " << j << std::endl;
	            
			if(!switchToFakeRate){
				if(UseSumPtCut && genericMuon[i].pt+genericElectron[j].pt < Cut_leplep_sumPt) continue;}
			bool iso2 = (RelIsoEl(genericElectron[j]) < 0.3);
			if(switchToFakeRate){
				if(genericMuon[i].charge*genericElectron[j].charge < 0) continue; 
			}
			else{ 
				if(genericMuon[i].charge*genericElectron[j].charge >= 0) continue;
			} 
			if(deltaR(genericElectron[j].eta,genericElectron[j].phi,genericMuon[i].eta,genericMuon[i].phi)< maxDeltaR) continue;

			if (switchToFakeRate){ signal = true; muE=true; muTau = false;}
			else if (!switchToFakeRate && iso1_muE && iso2){ signal = true; muE=true; muTau = false;}
			else if (!switchToFakeRate && !iso1_muE && iso2  && category < 1){ category = 2; muE=true; muTau = false;}
			else if (!switchToFakeRate && iso1_muE && !iso2 && category < 1){ category = 1; muE=true; muTau = false;} 
			else if (!switchToFakeRate && !iso1_muE && !iso2 && category < 0){ category = 0; muE=true; muTau = false;}
			else continue;
			Hindex[0]=i;
			Hindex[1]=j;
			if(signal && AdLepton(genericMuon,genericElectron,genericMuon[i],genericElectron[j])){ signal=false; muE=false;}

		}
		
		
		m_logger << DEBUG << " Checking for muTau " << SLogger::endmsg;
		if(examineThisEvent) std::cout << " Checking mutau " << std::endl;
		if(examineThisEvent) std::cout << " Mu candidate i= " << i << " " << genericMuon[i].pt << std::endl;
			
		if(!switchToFakeRate){		
			if(!checkCategories && !iso1_muTau) continue;}
		for(uint j=0; j< goodTau.size() && !signal; j++)
		{
                        //the following switch could be also omitted
                        //since in the case of switchToFakeRate && UseSumPtCut
                        //Cut_leptau_sumPt is 0
			if(examineThisEvent) std::cout << " Tau candidate j= " << j << " " << goodTau[j].pt << std::endl;
			
			if(!switchToFakeRate){
				if(UseSumPtCut && genericMuon[i].pt+goodTau[j].pt < Cut_leptau_sumPt) continue;}			
			bool iso2 = Cut_tautau_MVA_iso ? goodTau[j].byMediumIsolationMVA > 0.5 : goodTau[j].byMediumCombinedIsolationDeltaBetaCorr > 0.5;
			if(switchToFakeRate){	
				if(genericMuon[i].charge*goodTau[j].charge < 0) continue;
			}
			else{
				if(genericMuon[i].charge*goodTau[j].charge >= 0) continue;
			}
			if(goodTau[j].discriminationByMuonTight <=0.5) continue;
			if(deltaR(goodTau[j].eta,goodTau[j].phi,genericMuon[i].eta,genericMuon[i].phi)< maxDeltaR) continue;                                    
			if(examineThisEvent) std::cout << " j passed pre-selection " << std::endl;
			if (switchToFakeRate){ signal = true; muE=false; muTau=true;}
			else if (!switchToFakeRate && iso1_muTau && iso2){ signal = true; muE=false; muTau=true;}
			else if (!switchToFakeRate && !iso1_muTau && iso2  && category < 1){ category = 2; muE=false; muTau=true;}
			else if (!switchToFakeRate && iso1_muTau && !iso2 && category < 1){ category = 1; muE=false; muTau=true;} 
			else if (!switchToFakeRate && !iso1_muTau && !iso2 && category < 0){ category = 0; muE=false; muTau=true;}
			else continue;
			Hindex[0]=i;
			Hindex[1]=j;
			if(signal && AdLepton(genericMuon,genericElectron,genericMuon[i],goodTau[j])){ 
				if(examineThisEvent) std::cout << " Aborting due to additional lepton" << std::endl;
				signal=false; muTau=false;}
		}             
	}

	//if(signal && AdLepton(genericMuon,genericElectron,Hcand)) signal=false;
	if(muTau) m_logger << INFO << " muTau candidate!" << SLogger::endmsg;   
	else if(muE) m_logger << INFO << " muE candidate!" << SLogger::endmsg;                 
	else m_logger << DEBUG << " Checking no-muon channels" << SLogger::endmsg;
	bool eTau = false;
	if(!signal)
	{
		if(examineThisEvent) std::cout << " There are " << genericElectron.size() << " ele candidates " << std::endl;
	
		for(uint i = 0; i < genericElectron.size() && !signal ; i++)
		{
			bool iso1 = (RelIsoEl(genericElectron[i]) < 0.1);
                        if(!switchToFakeRate){		
			if (!iso1 && !checkCategories) continue;}
                        if(switchToFakeRate){		
			if(genericElectron[i].numLostHitEleInner > 1) continue;}
                        else{
			if(genericElectron[i].numLostHitEleInner > 0) continue;}
			m_logger << DEBUG << " Checking for eTau " << SLogger::endmsg;	
			for(uint j=0; j< goodTau.size() && !signal; j++)
			{
				//the following switch could be also omitted
				//since in the case of switchToFakeRate && UseSumPtCut
				//Cut_leptau_sumPt is 0
                             if(!switchToFakeRate){
				if(UseSumPtCut && genericElectron[i].pt+goodTau[j].pt < Cut_leptau_sumPt) continue;}
				bool iso2 = Cut_tautau_MVA_iso ? goodTau[j].byMediumIsolationMVA > 0.5 : goodTau[j].byMediumCombinedIsolationDeltaBetaCorr > 0.5;
				if(switchToFakeRate){	
				if(genericElectron[i].charge*goodTau[j].charge < 0) continue;
				}
                                else{
				if(genericElectron[i].charge*goodTau[j].charge >= 0) continue;
                                }
                                if(goodTau[j].discriminationByElectronMVA <=0.5) continue;
				if(deltaR(goodTau[j].eta,goodTau[j].phi,genericElectron[i].eta,genericElectron[i].phi)< maxDeltaR) continue;
				
                if (switchToFakeRate){ signal = true; muTau=muE=false; eTau=true;}
				else if (!switchToFakeRate && iso1 && iso2){ signal = true; muTau=muE=false; eTau=true;}
				else if (!switchToFakeRate && !iso1 && iso2  && category < 1){ category = 2; muTau=muE=false; eTau=true;}
				else if (!switchToFakeRate && iso1 && !iso2  && category < 1){ category = 1; muTau=muE=false; eTau=true;} 
				else if (!switchToFakeRate && !iso1 && !iso2 && category < 0){ category = 0; muTau=muE=false; eTau=true;}
				else continue;
				Hindex[0]=i;
				Hindex[1]=j;
				if(signal && AdLepton(genericMuon,genericElectron,genericElectron[i],goodTau[j])){ signal=false; eTau=false;}
			}
		}
	}

	if(eTau) m_logger << INFO << " eTau candidate!" << SLogger::endmsg;
	else m_logger << DEBUG << " Checking fully hadronic decay" << SLogger::endmsg;
	
	if(examineThisEvent && signal && eTau){ std::cout << "Found etau candidate" << std::endl; signal = false; eTau=false;}
	bool tauTau =false;
	if(!signal)
	{
		if(examineThisEvent) std::cout << " Checking tautau " << std::endl;
		for(uint i = 0; i < goodTau.size() && !signal ; i++)
		{
			if(examineThisEvent) std::cout << " Tau candidate i= " << i << " " << goodTau[i].pt << std::endl;
			if(switchToFakeRate){
                          if(goodTau[i].pt < Cut_tautau_Pt_1) continue;
			}
			else{
                        if(goodTau[i].pt < Cut_tautau_Pt_1 && !UseSumPtCut) continue;
			}
			if(goodTau[i].discriminationByElectronMedium <=0.5) continue;
			if(goodTau[i].discriminationByMuonMedium <=0.5) continue;
			bool iso1 = Cut_tautau_MVA_iso ? goodTau[i].byTightIsolationMVA > 0.5 : goodTau[i].byTightCombinedIsolationDeltaBetaCorr > 0.5; 
                        if(!switchToFakeRate){		
			if(!checkCategories && !iso1) continue;}
			if(examineThisEvent) std::cout << "   Passed pre-selection" << std::endl;
			for(uint j=i+1; j< goodTau.size() && !signal; j++)
			{
				if(examineThisEvent) std::cout << " Tau candidate j= " << j << " " << goodTau[j].pt << std::endl;
				if(examineThisEvent){
					TLorentzVector tau1;
					TLorentzVector tau2;
					TLorentzVector H_; 
					tau1.SetPxPyPzE(goodTau[i].px,goodTau[i].py,goodTau[i].pz,goodTau[i].E);        
					tau2.SetPxPyPzE(goodTau[j].px,goodTau[j].py,goodTau[j].pz,goodTau[j].E);        
					H_=tau1+tau2;
					std::cout << " H candidate mass is " << H_.M() << std::endl;
				}
				
				
				if(switchToFakeRate){
                     if(goodTau[j].pt < Cut_tautau_Pt_2) continue;
				}
				else{
					if(goodTau[j].pt < Cut_tautau_Pt_2 && !UseSumPtCut) continue;
					if(UseSumPtCut && goodTau[i].pt+goodTau[j].pt < Cut_tautau_sumPt) continue;
				}
				if(examineThisEvent) std::cout << "  j passed pt cut" << j << " " << Cut_tautau_Pt_2 << std::endl;
				
                if(switchToFakeRate){
					if(goodTau[i].charge*goodTau[j].charge  < 0) continue;
                }
                else{
					if(goodTau[i].charge*goodTau[j].charge >= 0) continue;
                }
				if(goodTau[j].discriminationByElectronMedium <=0.5) continue;
				if(goodTau[j].discriminationByMuonMedium <=0.5) continue;
				if(examineThisEvent) std::cout << "   j Passed pre-selection" << std::endl;
			
				bool iso2 = Cut_tautau_MVA_iso ? goodTau[j].byTightIsolationMVA > 0.5 : goodTau[j].byTightCombinedIsolationDeltaBetaCorr > 0.5; 
				if(deltaR(goodTau[j].eta,goodTau[j].phi,goodTau[i].eta,goodTau[i].phi)< maxDeltaR) continue;
				if(examineThisEvent) std::cout << "   Passed selection" << std::endl;
			
                                if (switchToFakeRate){ signal = true; muTau=muE=eTau = false; tauTau=true;
				}
				else if (!switchToFakeRate && iso1 && iso2){ signal = true; muTau=muE=eTau=false; tauTau=true;
				}
				else if (!switchToFakeRate && !iso1 && iso2  && category < 1){ category = 1; muTau=muE=eTau = false; tauTau=true;
				}
				else if (!switchToFakeRate && iso1 && !iso2  && category < 1){ category = 2; muTau=muE=eTau = false; tauTau=true;
				}
				else if (!switchToFakeRate && !iso1 && !iso2 && category < 0){ category = 0; muTau=muE=eTau = false; tauTau=true;
				}
				else continue;
				Hindex[0]=i;
				Hindex[1]=j;
	m_logger << DEBUG << " hindex[0] " << i << SLogger::endmsg;
	m_logger << DEBUG << " hindex[1] " << j << SLogger::endmsg;

			}
		}
	}

	if(Hindex[0] < 0 || Hindex[1] < 0 ||(!muTau && !muE && !eTau && !tauTau)){ 
		m_logger << DEBUG << " No Higgs candidate. Going to next event" << SLogger::endmsg; 
				// sync begin
		if( found_event){
				 m_logger << ERROR << " MISSED H cand of type " << evt_type[pos] << " and mass " << mass_H[pos] << SLogger::endmsg;
				 m_logger << ERROR << " Remaining mu, tau, el " << goodMuon.size() << " " << goodTau.size() << " " << goodElectron.size()
				 << " out of " << muCand << " " << tauCand << " " << elCand << " out of "
				 << muCandZ <<  " " << elCandZ << SLogger::endmsg;
				 //~ if(evt_type[pos]==7)
				 //~ {
					 //~ TLorentzVector eH_eTau,tauH_eTau,H_eTau;
                                                //~ eH_eTau.SetPxPyPzE(goodElectron[0].px,goodElectron[0].py,goodElectron[0].pz,goodElectron[0].E);
                                                //~ tauH_eTau.SetPxPyPzE(goodTau[0].px,goodTau[0].py,goodTau[0].pz,goodTau[0].E);
                                                //~ H_eTau = eH_eTau+tauH_eTau;
					//~ m_logger << WARNING << " My mass " << H_eTau.M() << SLogger::endmsg;
					//~ m_logger << WARNING << "Z is made from " << Zindex[0] << " and " << Zindex[1] << SLogger::endmsg;
					//~ for(uint i = 0; i < electron.size() && !eTau ; i++)
                        //~ {
						//~ 
                            //~ double relIso = RelIsoEl(electron[i]);
                            //~ m_logger << WARNING << " good el. no " << i << " relIso " << relIso << " hits " << electron[i].numLostHitEleInner << 
                            //~ " charge " << electron[i].charge << SLogger::endmsg;
                            //~ if (relIso > 0.25){m_logger << WARNING << " rej iso"  << SLogger::endmsg; continue;}
                            //~ if(relIso < 0.10 && electron[i].numLostHitEleInner < 1)
                            //~ {
                                //~ m_logger << WARNING << " Checking for eTau " << SLogger::endmsg;	
                                //~ for(uint j=0; j< goodTau.size() && !muTau; j++)
                                //~ {
                                     //~ m_logger << WARNING << " good tau no. " << j << " MVA " << goodTau[j].discriminationByElectronMVA << " hits " << 
                            //~ " charge " << goodTau[i].charge << " delta R " <<
                            //~ deltaR(goodTau[j].eta,goodTau[j].phi,electron[i].eta,electron[i].phi) << SLogger::endmsg;
                            //~ TLorentzVector eH,tauH,H_m;
                                                //~ eH.SetPxPyPzE(electron[i].px,electron[i].py,electron[i].pz,electron[i].E);
                                                //~ tauH.SetPxPyPzE(goodTau[j].px,goodTau[j].py,goodTau[j].pz,goodTau[j].E);
                                                //~ H_m = eH+tauH;
								//~ m_logger << WARNING << " My mass " << H_m.M() << SLogger::endmsg;
                                    //~ if(electron[i].charge*goodTau[j].charge >=0) continue;
                                    //~ if(goodTau[j].discriminationByElectronMVA <=0.5) continue;
                                    //~ if(deltaR(goodTau[j].eta,goodTau[j].phi,electron[i].eta,electron[i].phi)< 0.3) continue;
									//~ eTau=true;
								//~ }
							//~ }
						//~ }
				 //~ 
				 //~ 
				 //~ }
				 
			 }
		// sync end

		return;
	}else{
		if(found_event) m_logger << ERROR << " FOUND H cand of type " << evt_type[pos] << " and mass " << mass_H[pos] << SLogger::endmsg;
	}
	
	Hist("h_Nvertex_AfterZH")->Fill(nGoodVx);
	Hist("h_Nvertex_AfterZH_W")->Fill(nGoodVx,Z_weight);


	//else m_logger << INFO << "Higgs candidate. Size is " << Hcand.size() << SLogger::endmsg;
	// cross-check
	h_cut_flow->Fill(4,1);
	h_cut_flow_weight->Fill(4,Z_weight);
	
	if(muTau+muE+eTau+tauTau > 1){
		m_logger << ERROR << "Non-exclusive event type!! Aborting." << SLogger::endmsg;
		m_logger << ERROR << muTau << muE << eTau << tauTau << " " << eNumber << SLogger::endmsg;			 
		return;
	}

	h_cut_flow->Fill(5,1);
	h_cut_flow_weight->Fill(5,Z_weight);

	m_logger << DEBUG << " muTau " << muTau << SLogger::endmsg;
	m_logger << DEBUG << " muE " << muE << SLogger::endmsg;
	m_logger << DEBUG << " eTau " << eTau << SLogger::endmsg;
	m_logger << DEBUG << " tauTau " << tauTau << SLogger::endmsg;

	short event_type = 0;

	if(Zmumu)
	{
	m_logger << DEBUG << " event type inside Zmm " << event_type << SLogger::endmsg;
		if(muTau) event_type = 1;
		if(muE) event_type = 2;
		if(eTau) event_type = 3;
		if(tauTau) event_type = 4;
	}else if(Zee){
		if(muTau) event_type = 5;
		if(muE) event_type = 6;
		if(eTau) event_type = 7;
		if(tauTau) event_type = 8;
	}
	
	if(event_type!=evt_type[pos] && found_event) m_logger << WARNING << " WRONG type! His is " << evt_type[pos] << " and mine is " << event_type << SLogger::endmsg; 
	// efficiency correction;

	int I = Hindex[0]; int J = Hindex[1];		
	switch(event_type)
	{
		case 2:
		case 6:
			Hcand.push_back(genericMuon[I]);
			Hcand.push_back(genericElectron[J]);
			genericMuon.erase(genericMuon.begin()+I);
			genericElectron.erase(genericElectron.begin()+J);
			break;
		case 1:
		case 5:
			Hcand.push_back(genericMuon[I]);
			Hcand.push_back(goodTau[J]);
			genericMuon.erase(genericMuon.begin()+I);
			goodTau.erase(goodTau.begin()+J);
			break;
		case 3:
		case 7:
			Hcand.push_back(genericElectron[I]);
			Hcand.push_back(goodTau[J]);
			genericElectron.erase(genericElectron.begin()+I);
			goodTau.erase(goodTau.begin()+J);
			break;
		case 4:
		case 8:
			Hcand.push_back(goodTau[I]);
			Hcand.push_back(goodTau[J]);
			goodTau.erase(goodTau.begin()+I);
			goodTau.erase(goodTau.begin()+J-1);
			break;
	}


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

	bool Ad_lepton = false;

        if(switchToFakeRate){
	//~ for(uint i = 0; i < genericMuon.size(); i++)
	//~ {   for(uint j =0; j < Hcand.size(); j+=2){
		//~ if(deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand[j].eta,Hcand[j].phi)> maxDeltaR &&
				//~ deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand[j+1].eta,Hcand[j+1].phi)> maxDeltaR && isGoodMu(genericMuon[i]) < 0.4) 
			//~ Ad_lepton=true;
	   //~ }
        //~ }
	//~ for(uint i = 0; i < genericElectron.size(); i++)
	//~ {   for(uint j =0; j < Hcand.size(); j+=2){
		//~ if(deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand[j].eta,Hcand[j].phi)> maxDeltaR &&
				//~ deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand[j+1].eta,Hcand[j+1].phi)> maxDeltaR && isGoodEl(genericElectron[i]) < 0.4)  
			//~ Ad_lepton=true;
	   //~ }
        //~ }
        
        
        if(examineThisEvent) Ad_lepton=AdLepton(genericMuon,genericElectron,Hcand,1);
        else Ad_lepton=AdLepton(genericMuon,genericElectron,Hcand,0);
        
        }

        else{
	for(uint i = 0; i < genericMuon.size(); i++)
	{
		if(deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand[0].eta,Hcand[0].phi)> maxDeltaR &&deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand[1].eta,Hcand[1].phi)> maxDeltaR && RelIsoMu(genericMuon[i]) < 0.4) 
			Ad_lepton=true;
	}

	for(uint i = 0; i < genericElectron.size(); i++)
	{
		if(deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand[0].eta,Hcand[0].phi)> maxDeltaR &&deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand[1].eta,Hcand[1].phi)> maxDeltaR && RelIsoEl(genericElectron[i]) < 0.4)  
			Ad_lepton=true;
	}
	if(!IgnoreAdditionalTaus){
		for(uint i = 0; i < goodTau.size(); i++)
		{
			if(deltaR(goodTau[i].eta,goodTau[i].phi,Hcand[0].eta,Hcand[0].phi)> maxDeltaR &&
					deltaR(goodTau[i].eta,goodTau[i].phi,Hcand[1].eta,Hcand[1].phi)> maxDeltaR && goodTau[i].byMediumCombinedIsolationDeltaBetaCorr > 0.5)  
				Ad_lepton=true;
		}
	    }
        }//close else
	if(Ad_lepton) 
	{			
		m_logger << INFO << "Additional good lepton(s) present. Aborting. " << SLogger::endmsg;
			if( found_event){ 
				 m_logger << ERROR << " Premature abortion! H cand of type " << evt_type[pos] << " and mine is " << event_type << SLogger::endmsg;
				  m_logger << ERROR << " Remaining mu, tau, el " << goodMuon.size() << " " << goodTau.size() << " " << goodElectron.size()
				 << " out of " << muCand << " " << tauCand << " " << elCand << " out of "
				 << muCandZ <<  " " << elCandZ << SLogger::endmsg;
				
				TLorentzVector H_1,H_2,H_sum;
                                                H_1.SetPxPyPzE(Hcand[0].px,Hcand[0].py,Hcand[0].pz,Hcand[0].E);
                                                H_2.SetPxPyPzE(Hcand[1].px,Hcand[1].py,Hcand[1].pz,Hcand[1].E);
                                                H_sum = H_1 + H_2;
				
				m_logger << WARNING << " My mass " << H_sum.M() << " and his " << mass_H[pos] << SLogger::endmsg;
					
				bool LooseElectron = (goodTau[0].discriminationByElectronLoose > 0.5);
				bool LooseMuon = (goodTau[0].discriminationByMuonLoose > 0.5);
				bool CombinedIsolation = (goodTau[0].byMediumCombinedIsolationDeltaBetaCorr > 0.5);
				
				bool DecayMode = (goodTau[0].discriminationByDecayModeFinding > 0.5);
				
				bool HLooseElectron = (Hcand[1].discriminationByElectronLoose > 0.5);
				bool HLooseMuon = (Hcand[1].discriminationByMuonLoose > 0.5);
				bool HCombinedIsolation = (Hcand[1].byMediumCombinedIsolationDeltaBetaCorr > 0.5);
				
				bool HDecayMode = (Hcand[1].discriminationByDecayModeFinding > 0.5);
				TLorentzVector Zvector;
		        TLorentzVector Hvector;
			
				std::cout << " -------------------------------------------------------------------------------- " << std::endl;
		std::cout << " lumi number " << m->lumiNumber << " event number: " << m->eventNumber << std::endl;;
		switch(event_type){
		case 1: 
			std::cout << "Mu1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoMu(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "Mu2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoMu(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << " Z mass Abdollah " << mass_Z[pos] <<std::endl;                                    	
			std::cout << "Mu3(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " iso " << RelIsoMu(Hcand[0]) << " charge " << Hcand[0].charge << std::endl;
			std::cout << "Tau1(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " AgainstMuonTight " << Hcand[1].discriminationByMuonTight << " AgainstElectronLoose " << Hcand[1].discriminationByElectronLoose
			<< " CombinedMediumIsolation " << Hcand[1].byMediumCombinedIsolationDeltaBetaCorr << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << std::endl;
            break;
        case 2:
            std::cout << "Mu1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoMu(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "Mu2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoMu(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << " Z mass Abdollah " << mass_Z[pos] << std::endl;                                    	
			std::cout << "Mu3(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " iso " << RelIsoMu(Hcand[0]) << " charge " << Hcand[0].charge << std::endl;
			std::cout << "El1(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " iso " << RelIsoEl(Hcand[1]) << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << " H mass Abdollah " << mass_H[pos] << std::endl;
            break;
		case 3: 
			std::cout << "Mu1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoMu(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "Mu2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoMu(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << " Z mass Abdollah " << mass_Z[pos] << std::endl;                                    	
			std::cout << "El1(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " iso " << RelIsoEl(Hcand[0]) << " charge " << Hcand[0].charge << " missing hits in ID " << Hcand[0].numLostHitEleInner << std::endl;
			std::cout << "Tau1(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " AgainstMuonTight " << Hcand[1].discriminationByMuonLoose << " AgainstElectronMVA " << Hcand[1].discriminationByElectronMVA
			<< " CombinedMediumIsolation " << Hcand[1].byMediumCombinedIsolationDeltaBetaCorr << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << " H mass Abdollah " << mass_H[pos] << std::endl;
            break;
        case 4: 
			std::cout << "Mu1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoMu(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "Mu2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoMu(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << " Z mass Abdollah " << mass_Z[pos] << std::endl;                                    	
			std::cout << "Tau1(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " AgainstMuonMedium " << Hcand[0].discriminationByMuonMedium << " AgainstElectronMedium " << Hcand[0].discriminationByElectronMedium
			<< " TightCombinedIsolation " << Hcand[0].byTightCombinedIsolationDeltaBetaCorr << " charge " << Hcand[0].charge << std::endl;
			std::cout << "Tau2(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " AgainstMuonMedium " << Hcand[1].discriminationByMuonMedium << " AgainstElectronMedium " << Hcand[1].discriminationByElectronMedium
			<< " TightCombinedIsolation " << Hcand[1].byTightCombinedIsolationDeltaBetaCorr << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << " H mass Abdollah " << mass_H[pos] << std::endl;
            break;
        case 5: 
			std::cout << "El1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoEl(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "El2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoEl(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << " Z mass Abdollah " << mass_Z[pos] << std::endl;                                    	
			std::cout << "Mu1(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " iso " << RelIsoMu(Hcand[0]) << " charge " << Hcand[0].charge << std::endl;
			std::cout << "Tau1(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " AgainstMuonTight " << Hcand[1].discriminationByMuonTight << " AgainstElectronLoose " << Hcand[1].discriminationByElectronLoose
			<< " CombinedMediumIsolation " << Hcand[1].byMediumCombinedIsolationDeltaBetaCorr << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << " H mass Abdollah " << mass_H[pos] << std::endl;
            break;
        case 6:
            std::cout << "El1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoEl(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "El2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoEl(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << " Z mass Abdollah " << mass_Z[pos] << std::endl;                                    	
			std::cout << "Mu1(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " iso " << RelIsoMu(Hcand[0]) << " charge " << Hcand[0].charge << std::endl;
			std::cout << "El3(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " iso " << RelIsoEl(Hcand[1]) << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << " H mass Abdollah " << mass_H[pos] << std::endl;
            break;
		case 7: 
			std::cout << "El1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoEl(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "El2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoEl(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << " Z mass Abdollah " << mass_Z[pos] << std::endl;                                    	
		    std::cout << "El3(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " iso " << RelIsoEl(Hcand[0]) << " charge " << Hcand[0].charge << " missing hits in ID " << Hcand[0].numLostHitEleInner << std::endl;
		    std::cout << "Tau1(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " AgainstMuonTight " << Hcand[1].discriminationByMuonLoose << " AgainstElectronMVA " << Hcand[1].discriminationByElectronMVA
			<< " CombinedMediumIsolation " << Hcand[1].byMediumCombinedIsolationDeltaBetaCorr << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << " H mass Abdollah " << mass_H[pos] << std::endl;
            break;
        case 8: 
			std::cout << "El1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoEl(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "El2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoEl(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << " Z mass Abdollah " << mass_Z[pos] << std::endl;                                    	
			std::cout << "Tau1(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " AgainstMuonMedium " << Hcand[0].discriminationByMuonMedium << " AgainstElectronMedium " << Hcand[0].discriminationByElectronMedium
			<< " TightCombinedIsolation " << Hcand[0].byTightCombinedIsolationDeltaBetaCorr << " charge " << Hcand[0].charge << std::endl;
			std::cout << "Tau2(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " AgainstMuonMedium " << Hcand[1].discriminationByMuonMedium << " AgainstElectronMedium " << Hcand[1].discriminationByElectronMedium
			<< " TightCombinedIsolation " << Hcand[1].byTightCombinedIsolationDeltaBetaCorr << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << " H mass Abdollah " << mass_H[pos] << std::endl;
            break;
        }
				
				for(uint iTau=0; iTau < goodTau.size(); iTau++){
				 std::cout << "-->Additional tau pt " << goodTau[iTau].pt << " eta " << goodTau[iTau].eta << " phi " << goodTau[iTau].phi <<
				  " AgainstElectronLoose " << goodTau[iTau].discriminationByElectronLoose  << " AgainstMuonLoose " << goodTau[iTau].discriminationByMuonLoose << " MediumCombinedIsolation " << goodTau[iTau].byMediumCombinedIsolationDeltaBetaCorr << 
				  " DecayModeFinding " << goodTau[iTau].discriminationByDecayModeFinding << std::endl;
				 }
			 }

		return;
	}
	
	h_cut_flow->Fill(7,1);
	h_cut_flow_weight->Fill(7,weight);

        if(!switchToFakeRate){	
	if(signal) {h_cut_flow_signal->Fill(2,1);
        }
	else if (category==0) {h_cut_flow_cat0->Fill(2,1);
        }
	else if (category==1) {h_cut_flow_cat1->Fill(2,1);
        }
	else if (category==2) {h_cut_flow_cat2->Fill(2,1);
        }
  	if(signal){ h_cut_flow_signal_weight->Fill(2,weight);
        }
	else if (category==0) {h_cut_flow_cat0_weight->Fill(2,weight);
        }
	else if (category==1) {h_cut_flow_cat1_weight->Fill(2,weight);
        }
	else if (category==2) {h_cut_flow_cat2_weight->Fill(2,weight);
        }
	}
	// Same vertex check

        if(!switchToFakeRate){
	bool dZ_expo = (fabs(Zcand[0].z_expo - Zcand[1].z_expo) < dZvertex && fabs(Zcand[0].z_expo - Hcand[0].z_expo) < dZvertex && fabs(Zcand[0].z_expo - Hcand[1].z_expo) < dZvertex);		
	if(!dZ_expo)
	{
		if( found_event) m_logger << ERROR << " Wrong vertex! H cand of type " << evt_type[pos] << SLogger::endmsg; // sync 
		m_logger << INFO << "Not from the same vertex. Aborting." << SLogger::endmsg;
		return;
	}
	}
        else{
        bool dZ_expo = (fabs(Zcand[0].z_expo - Zcand[1].z_expo) < dZvertex);
        bool dZ_expo2 = false;
        for(uint i = 0; i < Hcand.size() && dZ_expo; i+=2)
        {
                if((fabs(Zcand[0].z_expo - Hcand[i].z_expo) > dZvertex)||(fabs(Zcand[0].z_expo - Hcand[i+1].z_expo) > dZvertex))
                {
                        Hcand.erase(Hcand.begin()+i);
                        Hcand.erase(Hcand.begin()+i);
                        i-=2;
                        if(Hcand.size()==0) i= Hcand.size();
                }else dZ_expo2=true;
        }
        dZ_expo=dZ_expo && dZ_expo2;
	if(!dZ_expo)
	{
		m_logger << INFO << "Not from the same vertex. Aborting." << SLogger::endmsg;
		return;
	}
        }

        if(!switchToFakeRate){
	h_cut_flow->Fill(8,1);
	h_cut_flow_weight->Fill(8,weight);
	
	if(signal) {h_cut_flow_signal->Fill(3,1);
        }
	else if (category==0) {h_cut_flow_cat0->Fill(3,1);
        }
	else if (category==1) {h_cut_flow_cat1->Fill(3,1);
        }
	else if (category==2) {h_cut_flow_cat2->Fill(3,1);
        }
	
	if(signal) {h_cut_flow_signal_weight->Fill(3,weight);
        }
	else if (category==0) {h_cut_flow_cat0_weight->Fill(3,weight);
        }
	else if (category==1) {h_cut_flow_cat1_weight->Fill(3,weight);
        }
	else if (category==2) {h_cut_flow_cat2_weight->Fill(3,weight);
        }
        }

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
		if(jetPt > 20. && fabs(jetEta) < 2.4 && bTag > bTagValue){
			count_bJets++;
			double dR1,dR2,dR3,dR4;
			dR1=deltaR(jetEta,jetPhi,Zcand[0].eta,Zcand[0].phi);
			dR2=deltaR(jetEta,jetPhi,Zcand[1].eta,Zcand[1].phi);
			dR3=deltaR(jetEta,jetPhi,Hcand[0].eta,Hcand[0].phi);
			dR4=deltaR(jetEta,jetPhi,Hcand[1].eta,Hcand[1].phi);
			
			if(!AllowTauBOverlap){
				if(dR1>0.4 && dR2>0.4 && dR3>0.4 && dR4>0.4 ){
					bTagVeto = true;	
					count_bJetsVetoed++;
				}		
				else count_bJets_afterVeto++;
			}else{
				if(eTau || muTau){
					if(dR1>0.4 && dR2>0.4 && dR3>0.4 ){ bTagVeto=true; count_bJetsVetoed++;}
				}else if (tauTau){
					if(dR1>0.4 && dR2>0.4 ){ bTagVeto=true; count_bJetsVetoed++;}
				}else if (muE){
					if(dR1>0.4 && dR2>0.4 && dR3>0.4 && dR4){ bTagVeto=true; count_bJetsVetoed++;}
				}
			}
		}
	}
        if(!switchToFakeRate){
	Hist("h_nbjets")->Fill(count_bJets,weight);
	if(signal) Hist("h_nbjets_signal")->Fill(count_bJets,weight);
	 
	Hist("h_nbjetsVetoed")->Fill(count_bJetsVetoed,weight);
	Hist("h_nbjets_afterVeto")->Fill(count_bJets_afterVeto,weight);
	if(signal)Hist("h_nbjets_afterVeto_signal")->Fill(count_bJets_afterVeto,weight);
	}

	if(bTagVeto)
	{
		 if( found_event) m_logger << ERROR << " Wrong b-tag! H cand of type " << evt_type[pos] << SLogger::endmsg; // sync 
		m_logger << INFO << "B-jet present. Aborting." << SLogger::endmsg;
		return;
	}

	h_cut_flow->Fill(9,1);
	h_cut_flow_weight->Fill(9,weight);

        if(!switchToFakeRate){
	if(signal) h_cut_flow_signal->Fill(4,1);
	else if (category==0) h_cut_flow_cat0->Fill(4,1);
	else if (category==1) h_cut_flow_cat1->Fill(4,1);
	else if (category==2) h_cut_flow_cat2->Fill(4,1);

	if(signal) h_cut_flow_signal_weight->Fill(4,weight);
	else if (category==0) h_cut_flow_cat0_weight->Fill(4,weight);
	else if (category==1) h_cut_flow_cat1_weight->Fill(4,weight);
	else if (category==2) h_cut_flow_cat2_weight->Fill(4,weight);
        }

	Hist("h_PF_MET_selected")->Fill(Met.front().et,weight);
	h_PF_MET_nPU_selected->Fill(nGoodVx,Met.front().et,weight);

        if(switchToFakeRate){
            for(uint i =0; i < Hcand.size() && !tauTau; i+=2)
            {
                if(!WZ_Rej(m,Hcand[i])){
                    Hcand.erase(Hcand.begin()+i);
                    Hcand.erase(Hcand.begin()+i);
                    i-=2;
                    continue;
                }
            }
			TLorentzVector Hcand1,Hcand2,H_boson;

            for(uint i =0; i < Hcand.size(); i+=2)
            {
                Hist( "h_event_type" )->Fill(event_type,weight);
                Hist("h_denom")->Fill(Hcand[i].pt,weight);
                h_denom_types[event_type-1]->Fill(Hcand[i].pt,weight);
                h_denom_types_eta[event_type-1]->Fill(Hcand[i].eta,weight);
                if(Hcand[i].eta<1.2 && Hcand[i].eta>-1.2){
                h_denom_types_centralEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
                }
                if(Hcand[i].eta<-1.2 && Hcand[i].eta>1.2){
                h_denom_types_externalEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
                }
                bool isMedium=false;
                bool isTight=false;
                if(eTau){
                    if(RelIsoEl(Hcand[i]) < 0.30 && isGoodEl(Hcand[i])){ Hist("h_event_type_medium")->Fill(event_type,weight); h_medium_types[event_type-1]->Fill(Hcand[i].pt,weight); h_medium_types_eta[event_type-1]->Fill(Hcand[i].eta,weight); isMedium=true;
			    if(Hcand[i].eta<1.2 && Hcand[i].eta>-1.2){
				    h_medium_types_centralEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
			    if(Hcand[i].eta<-1.2 && Hcand[i].eta>1.2){
				    h_medium_types_externalEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
                        }
                    if(RelIsoEl(Hcand[i]) < 0.10 && isGoodEl(Hcand[i])){ Hist("h_event_type_tight")->Fill(event_type,weight); h_tight_types[event_type-1]->Fill(Hcand[i].pt,weight); h_tight_types_eta[event_type-1]->Fill(Hcand[i].eta,weight); isTight=true; 
			    if(Hcand[i].eta<1.2 && Hcand[i].eta>-1.2){
				    h_tight_types_centralEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
			    if(Hcand[i].eta<-1.2 && Hcand[i].eta>1.2){
				    h_tight_types_externalEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
		    }
                }
                if(muTau){
                    if(RelIsoMu(Hcand[i]) < 0.30 && isGoodMu(Hcand[i])){ Hist("h_event_type_medium")->Fill(event_type,weight); h_medium_types[event_type-1]->Fill(Hcand[i].pt,weight); h_medium_types_eta[event_type-1]->Fill(Hcand[i].eta,weight); isMedium=true; 
			    if(Hcand[i].eta<1.2 && Hcand[i].eta>-1.2){
				    h_medium_types_centralEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
			    if(Hcand[i].eta<-1.2 && Hcand[i].eta>1.2){
				    h_medium_types_externalEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
                    }
                    if(RelIsoMu(Hcand[i]) < 0.15 && isGoodMu(Hcand[i])){ Hist("h_event_type_tight")->Fill(event_type,weight); h_tight_types[event_type-1]->Fill(Hcand[i].pt,weight); h_tight_types_eta[event_type-1]->Fill(Hcand[i].eta,weight); isTight=true;
			    if(Hcand[i].eta<1.2 && Hcand[i].eta>-1.2){
				    h_tight_types_centralEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
			    if(Hcand[i].eta<-1.2 && Hcand[i].eta>1.2){
				    h_tight_types_externalEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
                   }
                }
                if(muE){
                    if(RelIsoEl(Hcand[i]) < 0.30  && isGoodEl(Hcand[i])){ Hist("h_event_type_medium")->Fill(event_type,weight); h_medium_types[event_type-1]->Fill(Hcand[i].pt,weight); h_medium_types_eta[event_type-1]->Fill(Hcand[i].eta,weight); isMedium=true; 
			    if(Hcand[i].eta<1.2 && Hcand[i].eta>-1.2){
				    h_medium_types_centralEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
			    if(Hcand[i].eta<-1.2 && Hcand[i].eta>1.2){
				    h_medium_types_externalEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
                    }
                    if(RelIsoEl(Hcand[i]) < 0.10 && isGoodEl(Hcand[i])){ Hist("h_event_type_tight")->Fill(event_type,weight); h_tight_types[event_type-1]->Fill(Hcand[i].pt,weight); h_tight_types_eta[event_type-1]->Fill(Hcand[i].eta,weight); isTight=true;
			    if(Hcand[i].eta<1.2 && Hcand[i].eta>-1.2){
				    h_tight_types_centralEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
			    if(Hcand[i].eta<-1.2 && Hcand[i].eta>1.2){
				    h_tight_types_externalEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
		    }
                    if(RelIsoMu(Hcand[i+1]) < 0.30 && isGoodMu(Hcand[i+1])){ Hist("h_event_type_medium")->Fill(event_type,weight); h_medium_types[event_type-1]->Fill(Hcand[i+1].pt,weight); h_medium_types_eta[event_type-1]->Fill(Hcand[i+1].eta,weight); isMedium=true;
			    if(Hcand[i+1].eta<1.2 && Hcand[i+1].eta>-1.2){
				    h_medium_types_centralEtaRegion[event_type-1]->Fill(Hcand[i+1].pt,weight);
			    }
			    if(Hcand[i+1].eta<-1.2 && Hcand[i+1].eta>1.2){
				    h_medium_types_externalEtaRegion[event_type-1]->Fill(Hcand[i+1].pt,weight);
			    }
		    }
                    if(RelIsoMu(Hcand[i+1]) < 0.15 && isGoodMu(Hcand[i+1])){ Hist("h_event_type_tight")->Fill(event_type,weight); h_tight_types[event_type-1]->Fill(Hcand[i+1].pt,weight); h_tight_types_eta[event_type-1]->Fill(Hcand[i+1].eta,weight); isTight=true;
			    if(Hcand[i+1].eta<1.2 && Hcand[i+1].eta>-1.2){
				    h_tight_types_centralEtaRegion[event_type-1]->Fill(Hcand[i+1].pt,weight);
			    }
			    if(Hcand[i+1].eta<-1.2 && Hcand[i+1].eta>1.2){
				    h_tight_types_externalEtaRegion[event_type-1]->Fill(Hcand[i+1].pt,weight);
			    }
		    }
                    h_denom_types[event_type-1]->Fill(Hcand[i+1].pt,weight);
                    h_denom_types_eta[event_type-1]->Fill(Hcand[i+1].eta,weight);
		    if(Hcand[i+1].eta<1.2 && Hcand[i+1].eta>-1.2){
			    h_denom_types_centralEtaRegion[event_type-1]->Fill(Hcand[i+1].pt,weight);
		    }
		    if(Hcand[i+1].eta<-1.2 && Hcand[i+1].eta>1.2){
			    h_denom_types_externalEtaRegion[event_type-1]->Fill(Hcand[i+1].pt,weight);
		    }
                }
                if(tauTau){
                    h_denom_types[event_type-1]->Fill(Hcand[i+1].pt,weight);
                    h_denom_types_eta[event_type-1]->Fill(Hcand[i+1].eta,weight);
		    if(Hcand[i+1].eta<1.2 && Hcand[i+1].eta>-1.2){
			    h_denom_types_centralEtaRegion[event_type-1]->Fill(Hcand[i+1].pt,weight);
		    }
		    if(Hcand[i+1].eta<-1.2 && Hcand[i+1].eta>1.2){
			    h_denom_types_externalEtaRegion[event_type-1]->Fill(Hcand[i+1].pt,weight);
		    }
                    if(Hcand[i].byMediumCombinedIsolationDeltaBetaCorr >= 0.5){ Hist("h_event_type_medium")->Fill(event_type,weight); h_medium_types[event_type-1]->Fill(Hcand[i].pt,weight); h_medium_types_eta[event_type-1]->Fill(Hcand[i].eta,weight); isMedium=true; 
			    if(Hcand[i].eta<1.2 && Hcand[i].eta>-1.2){
				    h_medium_types_centralEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
			    if(Hcand[i].eta<-1.2 && Hcand[i].eta>1.2){
				    h_medium_types_externalEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
                    }
                    if(Hcand[i].byTightCombinedIsolationDeltaBetaCorr >= 0.5){ Hist("h_event_type_tight")->Fill(event_type,weight); h_tight_types[event_type-1]->Fill(Hcand[i].pt,weight); h_tight_types_eta[event_type-1]->Fill(Hcand[i].eta,weight); isTight=true;
			    if(Hcand[i].eta<1.2 && Hcand[i].eta>-1.2){
				    h_tight_types_centralEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
			    if(Hcand[i].eta<-1.2 && Hcand[i].eta>1.2){
				    h_tight_types_externalEtaRegion[event_type-1]->Fill(Hcand[i].pt,weight);
			    }
                    }
                    if(Hcand[i+1].byMediumCombinedIsolationDeltaBetaCorr >= 0.5){ Hist("h_event_type_medium")->Fill(event_type,weight); h_medium_types[event_type-1]->Fill(Hcand[i+1].pt,weight); h_medium_types_eta[event_type-1]->Fill(Hcand[i+1].eta,weight); isMedium=true;
			    if(Hcand[i+1].eta<1.2 && Hcand[i+1].eta>-1.2){
				    h_medium_types_centralEtaRegion[event_type-1]->Fill(Hcand[i+1].pt,weight);
			    }
			    if(Hcand[i+1].eta<-1.2 && Hcand[i+1].eta>1.2){
				    h_medium_types_externalEtaRegion[event_type-1]->Fill(Hcand[i+1].pt,weight);
			    }
                    }
                    if(Hcand[i+1].byTightCombinedIsolationDeltaBetaCorr >= 0.5){ Hist("h_event_type_tight")->Fill(event_type,weight); h_tight_types[event_type-1]->Fill(Hcand[i+1].pt,weight); h_tight_types_eta[event_type-1]->Fill(Hcand[i+1].eta,weight); isTight=true; 
			    if(Hcand[i+1].eta<1.2 && Hcand[i+1].eta>-1.2){
				    h_tight_types_centralEtaRegion[event_type-1]->Fill(Hcand[i+1].pt,weight);
			    }
			    if(Hcand[i+1].eta<-1.2 && Hcand[i+1].eta>1.2){
				    h_tight_types_externalEtaRegion[event_type-1]->Fill(Hcand[i+1].pt,weight);
			    }
		    }
                }
                Hcand1.SetPxPyPzE(Hcand[i].px,Hcand[i].py,Hcand[i].pz,Hcand[i].E);
                Hcand2.SetPxPyPzE(Hcand[i+1].px,Hcand[i+1].py,Hcand[i+1].pz,Hcand[i+1].E);
                H_boson = Hcand1+Hcand2;
                double Hmass = H_boson.M();
                if(printoutEvents)
				{
					TString fileName = GetInputTree(InTreeName.c_str())->GetDirectory()->GetFile()->GetName();
					log1 << setiosflags(ios::fixed) << std::setprecision(1) << event_type << " " << m->runNumber << " " << m->lumiNumber << " " << m->eventNumber << " " << Zmass << " " << Hmass 
					<< " " << Hcand[i].pt << " " << Hcand[i+1].pt << " " << isMedium << " " << isTight << " " << std::endl;
				}
                
            }

            if(RelIsoEl(Hcand[0]) < 0.25) Hist("h_medium")->Fill(Hcand[0].pt,weight);
            if(RelIsoEl(Hcand[0]) < 0.10) Hist("h_tight")->Fill(Hcand[0].pt,weight);

            //TLorentzVector Hcand1,Hcand2,H_boson;

            for(uint i =0;i < Hcand.size(); i+=2){
                Hcand1.SetPxPyPzE(Hcand[i].px,Hcand[i].py,Hcand[i].pz,Hcand[i].E);
                Hcand2.SetPxPyPzE(Hcand[i+1].px,Hcand[i+1].py,Hcand[i+1].pz,Hcand[i+1].E);
                H_boson = Hcand1+Hcand2;
                h_H_mass_types[event_type-1]->Fill(H_boson.M(),weight);
            }

        }//close switch to fake

        else{
        double tMass = -100;
        if(!tauTau)
        {
            if(!muE) tMass = Tmass(m,Hcand[0]);
            else{
                if(Hcand[0].pt > Hcand[1].pt) tMass = Tmass(m,Hcand[0]);
                    else tMass = Tmass(m,Hcand[1]);
                }

                Hist("h_Tmass")->Fill(tMass,weight); 
            }


            if(isSimulation)
            { 
                if(signal){
                    Hist( "h_event_type" )->Fill(event_type,weight);
                    Hist( "h_event_type_raw" )->Fill(event_type);
		 
		 }
		
	}else  Hist( "h_event_type" )->Fill(event_type,weight); // blinding 

		if( found_event && event_type!=evt_type[pos]) {
	  m_logger << ERROR << " Wrong event type. His is " << evt_type[pos] << " and mine is " << event_type << SLogger::endmsg;
  }

	
	//histograms for selected candidates
	double Hmass=-100;
	switch(event_type)
	{
		case 2:
		case 6:
			muH_muE_tightMuIso.SetPxPyPzE(Hcand[0].px,Hcand[0].py,Hcand[0].pz,Hcand[0].E);
			eH_muE_tightMuIso.SetPxPyPzE(Hcand[1].px,Hcand[1].py,Hcand[1].pz,Hcand[1].E);
			H_muE_tightMuIso = muH_muE_tightMuIso+eH_muE_tightMuIso;
			Hist( "h_muH_muE_tightMuIso_pt" )->Fill(muH_muE_tightMuIso.Pt(),weight);
			Hist( "h_eH_muE_tightMuIso_pt" )->Fill(eH_muE_tightMuIso.Pt(),weight);
			Hist( "h_H_muE_tightMuIso_pt" )->Fill(H_muE_tightMuIso.Pt(),weight);
			Hist( "h_H_muE_tightMuIso_mass" )->Fill(H_muE_tightMuIso.M(),weight);
			Hist( "h_H_pt" )->Fill(H_muE_tightMuIso.Pt(),weight);
			Hist( "h_H_mass" )->Fill(H_muE_tightMuIso.M(),weight);
			Hist( "h_H_eta")->Fill(H_muE_tightMuIso.Eta(),weight);
			Hist( "h_H_phi")->Fill(H_muE_tightMuIso.Phi(),weight);
			h_H_mass_types[event_type-1]->Fill(H_muE_tightMuIso.M(),weight);
			Hmass=H_muE_tightMuIso.M();
			
			if(signal)
			{
				Hist("h_signal_pt1")->Fill(Hcand[1].pt,weight);
				Hist("h_signal_pt2")->Fill(Hcand[0].pt,weight);	
				h_signal_pt1_types[event_type-1]->Fill(Hcand[1].pt,weight);
				h_signal_pt2_types[event_type-1]->Fill(Hcand[0].pt,weight);
				h_signal_SumPt_types[event_type-1]->Fill(Hcand[0].pt+Hcand[1].pt,weight);
				h_H_mass_signal_types[event_type-1]->Fill(H_muE_tightMuIso.M(),weight);		
			}else if(category==1){
				Hist("h_category1_pt")->Fill(Hcand[1].pt,weight);
				h_category1_pt_types[event_type-1]->Fill(Hcand[1].pt,weight);
				h_H_mass_cat1_types[event_type-1]->Fill(H_muE_tightMuIso.M(),weight);		
			}else if(category==2){
				Hist("h_category2_pt")->Fill(Hcand[0].pt,weight);
				h_category2_pt_types[event_type-1]->Fill(Hcand[0].pt,weight);
				h_H_mass_cat2_types[event_type-1]->Fill(H_muE_tightMuIso.M(),weight);		
			}else if(category==0){
				h_category0_pt->Fill(Hcand[1].pt,Hcand[0].pt,weight);
				h_category0_pt_types[event_type-1]->Fill(Hcand[1].pt,Hcand[0].pt,weight);
				h_H_mass_cat0_types[event_type-1]->Fill(H_muE_tightMuIso.M(),weight);		
			}
			
			
			
			break;
		case 1:
		case 5:
			muH_muTau.SetPxPyPzE(Hcand[0].px,Hcand[0].py,Hcand[0].pz,Hcand[0].E);
			tauH_muTau.SetPxPyPzE(Hcand[1].px,Hcand[1].py,Hcand[1].pz,Hcand[1].E);
			H_muTau = muH_muTau+tauH_muTau;
			Hist( "h_muH_muTau_pt" )->Fill(muH_muTau.Pt(),weight);
			Hist( "h_tauH_muTau_pt" )->Fill(tauH_muTau.Pt(),weight);
			Hist( "h_H_muTau_pt" )->Fill(H_muTau.Pt(),weight);
			Hist( "h_H_muTau_mass" )->Fill(H_muTau.M(),weight);
			Hist( "h_H_pt" )->Fill(H_muTau.Pt(),weight);
			Hist( "h_H_mass" )->Fill(H_muTau.M(),weight);
			Hist( "h_H_eta")->Fill(H_muTau.Eta(),weight);
			Hist( "h_H_phi")->Fill(H_muTau.Phi(),weight);
			h_H_mass_types[event_type-1]->Fill(H_muTau.M(),weight);
			
			Hmass=H_muTau.M();
			
			if(signal)
			{
				Hist("h_signal_pt1")->Fill(Hcand[1].pt,weight);
				Hist("h_signal_pt2")->Fill(Hcand[0].pt,weight);	
				h_signal_pt1_types[event_type-1]->Fill(Hcand[1].pt,weight);
				h_signal_pt2_types[event_type-1]->Fill(Hcand[0].pt,weight);
				h_signal_SumPt_types[event_type-1]->Fill(Hcand[0].pt+Hcand[1].pt,weight);
				h_H_mass_signal_types[event_type-1]->Fill(H_muTau.M(),weight);					
			}else if(category==1){
				Hist("h_category1_pt")->Fill(Hcand[1].pt,weight);
				h_category1_pt_types[event_type-1]->Fill(Hcand[1].pt,weight);
				h_H_mass_cat1_types[event_type-1]->Fill(H_muTau.M(),weight);
			}else if(category==2){
				Hist("h_category2_pt")->Fill(Hcand[0].pt,weight);
				h_category2_pt_types[event_type-1]->Fill(Hcand[0].pt,weight);
				h_H_mass_cat2_types[event_type-1]->Fill(H_muTau.M(),weight);
			}else if(category==0){
				h_category0_pt->Fill(Hcand[1].pt,Hcand[0].pt,weight);
				h_category0_pt_types[event_type-1]->Fill(Hcand[1].pt,Hcand[0].pt,weight);
				h_H_mass_cat0_types[event_type-1]->Fill(H_muTau.M(),weight);
			}
			
			break;
		case 3:
		case 7:
			eH_eTau.SetPxPyPzE(Hcand[0].px,Hcand[0].py,Hcand[0].pz,Hcand[0].E);
			tauH_eTau.SetPxPyPzE(Hcand[1].px,Hcand[1].py,Hcand[1].pz,Hcand[1].E);
			H_eTau = eH_eTau+tauH_eTau;
			Hist( "h_eH_eTau_pt" )->Fill(eH_eTau.Pt(),weight);
			Hist( "h_tauH_eTau_pt" )->Fill(tauH_eTau.Pt(),weight);
			Hist( "h_H_eTau_pt" )->Fill(H_eTau.Pt(),weight);
			Hist( "h_H_eTau_mass" )->Fill(H_eTau.M(),weight);
			Hist( "h_H_pt" )->Fill(H_eTau.Pt(),weight);
			Hist( "h_H_mass" )->Fill(H_eTau.M(),weight);
			Hist( "h_H_eta")->Fill(H_eTau.Eta(),weight);
			Hist( "h_H_phi")->Fill(H_eTau.Phi(),weight);
			h_H_mass_types[event_type-1]->Fill(H_eTau.M(),weight);
			
			Hmass=H_eTau.M();
			
			if(signal)
			{
				Hist("h_signal_pt1")->Fill(Hcand[1].pt,weight);
				Hist("h_signal_pt2")->Fill(Hcand[0].pt,weight);	
				h_signal_pt1_types[event_type-1]->Fill(Hcand[1].pt,weight);
				h_signal_pt2_types[event_type-1]->Fill(Hcand[0].pt,weight);
				h_signal_SumPt_types[event_type-1]->Fill(Hcand[0].pt+Hcand[1].pt,weight);
				h_H_mass_signal_types[event_type-1]->Fill(H_eTau.M(),weight);				
			}else if(category==1){
				Hist("h_category1_pt")->Fill(Hcand[1].pt,weight);
				h_category1_pt_types[event_type-1]->Fill(Hcand[1].pt,weight);
				h_H_mass_cat1_types[event_type-1]->Fill(H_eTau.M(),weight);
			}else if(category==2){
				Hist("h_category2_pt")->Fill(Hcand[0].pt,weight);
				h_category2_pt_types[event_type-1]->Fill(Hcand[0].pt,weight);
				h_H_mass_cat2_types[event_type-1]->Fill(H_eTau.M(),weight);
			}else if(category==0){
				h_category0_pt->Fill(Hcand[1].pt,Hcand[0].pt,weight);
				h_category0_pt_types[event_type-1]->Fill(Hcand[1].pt,Hcand[0].pt,weight);
				h_H_mass_cat0_types[event_type-1]->Fill(H_eTau.M(),weight);
			}	

			break;	
		case 4:
		case 8:

			tau1H_tauTau.SetPxPyPzE(Hcand[0].px,Hcand[0].py,Hcand[0].pz,Hcand[0].E);
			tau2H_tauTau.SetPxPyPzE(Hcand[1].px,Hcand[1].py,Hcand[1].pz,Hcand[1].E);
			H_tauTau = tau1H_tauTau+tau2H_tauTau;
			Hist( "h_tau1H_tauTau_pt" )->Fill(tau1H_tauTau.Pt(),weight);
			Hist( "h_tau2H_tauTau_pt" )->Fill(tau2H_tauTau.Pt(),weight);
			Hist( "h_H_tauTau_pt" )->Fill(H_tauTau.Pt(),weight);
			Hist( "h_H_tauTau_mass" )->Fill(H_tauTau.M(),weight);
			Hist( "h_H_pt" )->Fill(H_tauTau.Pt(),weight);
			Hist( "h_H_mass" )->Fill(H_tauTau.M(),weight);

			Hist( "h_H_eta")->Fill(H_tauTau.Eta(),weight);
			Hist( "h_H_phi")->Fill(H_tauTau.Phi(),weight);
			h_H_mass_types[event_type-1]->Fill(H_tauTau.M(),weight);
			
			Hmass=H_tauTau.M();
			
			if(signal)
			{
				Hist("h_signal_pt1")->Fill(Hcand[0].pt,weight);
				Hist("h_signal_pt2")->Fill(Hcand[1].pt,weight);	
				h_signal_pt1_types[event_type-1]->Fill(Hcand[0].pt,weight);
				h_signal_pt2_types[event_type-1]->Fill(Hcand[1].pt,weight);
				h_signal_SumPt_types[event_type-1]->Fill(Hcand[0].pt+Hcand[1].pt,weight);
				h_H_mass_signal_types[event_type-1]->Fill(H_tauTau.M(),weight);				
			}else if(category==1){
				Hist("h_category1_pt")->Fill(Hcand[0].pt,weight);
				h_category1_pt_types[event_type-1]->Fill(Hcand[0].pt,weight);
				h_H_mass_cat1_types[event_type-1]->Fill(H_tauTau.M(),weight);
			}else if(category==2){
				Hist("h_category2_pt")->Fill(Hcand[1].pt,weight);
				h_category2_pt_types[event_type-1]->Fill(Hcand[1].pt,weight);
				h_H_mass_cat2_types[event_type-1]->Fill(H_tauTau.M(),weight);
			}else if(category==0){
				h_category0_pt->Fill(Hcand[0].pt,Hcand[1].pt,weight);
				h_category0_pt_types[event_type-1]->Fill(Hcand[0].pt,Hcand[1].pt,weight);
				h_H_mass_cat0_types[event_type-1]->Fill(H_tauTau.M(),weight);
			}	

			break;


	}

	Hist( "h_H_lep1_eta")->Fill(Hcand[0].eta,weight);
	Hist( "h_H_lep1_phi")->Fill(Hcand[0].phi,weight);
	Hist( "h_H_lep2_eta")->Fill(Hcand[1].eta,weight);
	Hist( "h_H_lep2_phi")->Fill(Hcand[1].phi,weight);
	Hist( "h_total_weight")->Fill(weight);

        //histogram to estimate the final yield corrected with the FR

        double cat0_weight_medium, cat1_weight_medium, cat2_weight_medium;
        double cat0_weight_tight, cat1_weight_tight, cat2_weight_tight;
        double FR_mu_medium = FR_MMed, FR_mu_tight = FR_MTig;
        double FR_ele_medium = FR_EMed, FR_ele_tight = FR_ETig;
        double FR_tau_medium, FR_tau_tight;
        double FR_tau1_medium, FR_tau1_tight;
        double FR_tau2_medium, FR_tau2_tight;

        switch(event_type){
        //MMMT
        case 1:
        FR_tau_medium = fakeTau_medium(Hcand[1].pt);
        FR_tau_tight = fakeTau_tight(Hcand[1].pt);
        m_logger << DEBUG << " event_type: " << event_type << " Hcand[1].pt " << Hcand[1].pt << " func med " << fakeTau_medium(Hcand[1].pt) << " func tight " << fakeTau_tight(Hcand[1].pt) << SLogger::endmsg;
        m_logger << DEBUG << " event_type: " << event_type << " Hcand[1].pt " << Hcand[1].pt << " func med " << p0_medium*(TMath::Exp(p1_medium*Hcand[1].pt))+p2_medium << " func tight " << p0_tight*(TMath::Exp(p1_tight*Hcand[1].pt))+p2_tight  << SLogger::endmsg;
        if(category==0){
        cat0_weight_medium = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_tau_medium*FR_mu_medium)/(1-FR_tau_medium*FR_mu_medium);
        cat0_weight_tight = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_tau_tight*FR_mu_tight)/(1-FR_tau_tight*FR_mu_tight);
        h_cat0_FR_medium->Fill(1,weight*cat0_weight_medium);
        h_cat0_FR_tight->Fill(1,weight*cat0_weight_tight);
        }
        else if(category==1){
        cat1_weight_medium = (h_category1_pt_types[event_type-1]->GetEntries())*FR_tau_medium/(1-FR_tau_medium);
        cat1_weight_tight = (h_category1_pt_types[event_type-1]->GetEntries())*FR_tau_tight/(1-FR_tau_tight);
        h_cat1_FR_medium->Fill(1,weight*cat1_weight_medium);
        h_cat1_FR_tight->Fill(1,weight*cat1_weight_tight);
        }
        else if(category==2){
        cat2_weight_medium = (h_category2_pt_types[event_type-1]->GetEntries())*FR_mu_medium/(1-FR_mu_medium);
        cat2_weight_tight = (h_category2_pt_types[event_type-1]->GetEntries())*FR_mu_tight/(1-FR_mu_tight);
        h_cat2_FR_medium->Fill(1,weight*cat2_weight_medium);
        h_cat2_FR_tight->Fill(1,weight*cat2_weight_tight);
        }
        break;
        //MMEM
        case 2:
        if(category==0){
        cat0_weight_medium = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_ele_medium*FR_mu_medium)/(1-FR_ele_medium*FR_mu_medium);
        cat0_weight_tight = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_ele_tight*FR_mu_tight)/(1-FR_ele_tight*FR_mu_tight);
        h_cat0_FR_medium->Fill(2,weight*cat0_weight_medium);
        h_cat0_FR_tight->Fill(2,weight*cat0_weight_tight);
        }
        else if(category==1){
        cat1_weight_medium = (h_category1_pt_types[event_type-1]->GetEntries())*FR_ele_medium/(1-FR_ele_medium);
        cat1_weight_tight = (h_category1_pt_types[event_type-1]->GetEntries())*FR_ele_tight/(1-FR_ele_tight);
        h_cat1_FR_medium->Fill(2,weight*cat1_weight_medium);
        h_cat1_FR_tight->Fill(2,weight*cat1_weight_tight);
        }
        else if(category==2){
        cat2_weight_medium = (h_category2_pt_types[event_type-1]->GetEntries())*FR_mu_medium/(1-FR_mu_medium);
        cat2_weight_tight = (h_category2_pt_types[event_type-1]->GetEntries())*FR_mu_tight/(1-FR_mu_tight);
        h_cat2_FR_medium->Fill(2,weight*cat2_weight_medium);
        h_cat2_FR_tight->Fill(2,weight*cat2_weight_tight);
	}
        break;
        //MMET
        case 3:
        FR_tau_medium = fakeTau_medium(Hcand[1].pt);
        FR_tau_tight = fakeTau_tight(Hcand[1].pt);
        m_logger << DEBUG << " event_type: " << event_type << " Hcand[1].pt " << Hcand[1].pt << " func med " << fakeTau_medium(Hcand[1].pt) << " func tight " << fakeTau_tight(Hcand[1].pt) << SLogger::endmsg;
        m_logger << DEBUG << " event_type: " << event_type << " Hcand[1].pt " << Hcand[1].pt << " func med " << p0_medium*(TMath::Exp(p1_medium*Hcand[1].pt))+p2_medium << " func tight " << p0_tight*(TMath::Exp(p1_tight*Hcand[1].pt))+p2_tight  << SLogger::endmsg;
        if(category==0){
        cat0_weight_medium = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_ele_medium*FR_tau_medium)/(1-FR_ele_medium*FR_tau_medium);
        cat0_weight_tight = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_ele_tight*FR_tau_tight)/(1-FR_ele_tight*FR_tau_tight);
        h_cat0_FR_medium->Fill(3,weight*cat0_weight_medium);
        h_cat0_FR_tight->Fill(3,weight*cat0_weight_tight);
        }
        else if(category==1){
        cat1_weight_medium = (h_category1_pt_types[event_type-1]->GetEntries())*FR_tau_medium/(1-FR_tau_medium);
        cat1_weight_tight = (h_category1_pt_types[event_type-1]->GetEntries())*FR_tau_tight/(1-FR_tau_tight);
        h_cat1_FR_medium->Fill(3,weight*cat1_weight_medium);
        h_cat1_FR_tight->Fill(3,weight*cat1_weight_tight);
        }
        else if(category==2){
        cat2_weight_medium = (h_category2_pt_types[event_type-1]->GetEntries())*FR_ele_medium/(1-FR_ele_medium);
        cat2_weight_tight = (h_category2_pt_types[event_type-1]->GetEntries())*FR_ele_tight/(1-FR_ele_tight);
        h_cat2_FR_medium->Fill(3,weight*cat2_weight_medium);
        h_cat2_FR_tight->Fill(3,weight*cat2_weight_tight);
        }
        break;
        //MMTT
        case 4:
        FR_tau1_medium = fakeTau_medium(Hcand[0].pt);
        FR_tau1_tight = fakeTau_tight(Hcand[0].pt);
        FR_tau2_medium = fakeTau_medium(Hcand[1].pt);
        FR_tau2_tight = fakeTau_tight(Hcand[1].pt);
        m_logger << DEBUG << " event_type: " << event_type << " Hcand[0].pt " << Hcand[0].pt << " func med " << fakeTau_medium(Hcand[0].pt) << " func tight " << fakeTau_tight(Hcand[0].pt) << SLogger::endmsg;
        m_logger << DEBUG << " event_type: " << event_type << " Hcand[1].pt " << Hcand[1].pt << " func med " << fakeTau_medium(Hcand[1].pt) << " func tight " << fakeTau_tight(Hcand[1].pt) << SLogger::endmsg;
        m_logger << DEBUG << " event_type: " << event_type << " Hcand[0].pt " << Hcand[0].pt << " func med " << p0_medium*(TMath::Exp(p1_medium*Hcand[0].pt))+p2_medium << " func tight " << p0_tight*(TMath::Exp(p1_tight*Hcand[0].pt))+p2_tight  << SLogger::endmsg;
        m_logger << DEBUG << " event_type: " << event_type << " Hcand[1].pt " << Hcand[1].pt << " func med " << p0_medium*(TMath::Exp(p1_medium*Hcand[1].pt))+p2_medium << " func tight " << p0_tight*(TMath::Exp(p1_tight*Hcand[1].pt))+p2_tight  << SLogger::endmsg;
        if(category==0){
        cat0_weight_medium = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_tau1_medium*FR_tau2_medium)/(1-FR_tau1_medium*FR_tau2_medium);
        cat0_weight_tight = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_tau1_tight*FR_tau2_tight)/(1-FR_tau1_tight*FR_tau2_tight);
        h_cat0_FR_medium->Fill(4,weight*cat0_weight_medium);
        h_cat0_FR_tight->Fill(4,weight*cat0_weight_tight);
        }
        else if(category==1){
        cat1_weight_medium = (h_category1_pt_types[event_type-1]->GetEntries())*(FR_tau1_medium)/(1-FR_tau1_medium);
        cat1_weight_tight = (h_category1_pt_types[event_type-1]->GetEntries())*(FR_tau1_tight)/(1-FR_tau1_tight);
        h_cat1_FR_medium->Fill(4,weight*cat1_weight_medium);
        h_cat1_FR_tight->Fill(4,weight*cat1_weight_tight);
	}
        else if(category==2){
        cat2_weight_medium = (h_category2_pt_types[event_type-1]->GetEntries())*(FR_tau2_medium)/(1-FR_tau2_medium);
        cat2_weight_tight = (h_category2_pt_types[event_type-1]->GetEntries())*(FR_tau2_tight)/(1-FR_tau2_tight);
        h_cat2_FR_medium->Fill(4,weight*cat2_weight_medium);
        h_cat2_FR_tight->Fill(4,weight*cat2_weight_tight);
        }
        break;
        //EEMT
        case 5:
        FR_tau_medium = fakeTau_medium(Hcand[1].pt);
        FR_tau_tight = fakeTau_tight(Hcand[1].pt);
        m_logger << DEBUG << " event_type: " << event_type << " Hcand[1].pt " << Hcand[1].pt << " func med " << fakeTau_medium(Hcand[1].pt) << " func tight " << fakeTau_tight(Hcand[1].pt) << SLogger::endmsg;
        m_logger << DEBUG << " event_type: " << event_type << " Hcand[1].pt " << Hcand[1].pt << " func med " << p0_medium*(TMath::Exp(p1_medium*Hcand[1].pt))+p2_medium << " func tight " << p0_tight*(TMath::Exp(p1_tight*Hcand[1].pt))+p2_tight  << SLogger::endmsg;
        if(category==0){
        cat0_weight_medium = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_tau_medium*FR_mu_medium)/(1-FR_tau_medium*FR_mu_medium);
        cat0_weight_tight = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_tau_tight*FR_mu_tight)/(1-FR_tau_tight*FR_mu_tight);
        h_cat0_FR_medium->Fill(5,weight*cat0_weight_medium);
        h_cat0_FR_tight->Fill(5,weight*cat0_weight_tight);
	}
        else if(category==1){
        cat1_weight_medium = (h_category1_pt_types[event_type-1]->GetEntries())*FR_tau_medium/(1-FR_tau_medium);
        cat1_weight_tight = (h_category1_pt_types[event_type-1]->GetEntries())*FR_tau_tight/(1-FR_tau_tight);
        h_cat1_FR_medium->Fill(5,weight*cat1_weight_medium);
        h_cat1_FR_tight->Fill(5,weight*cat1_weight_tight);
        }
        else if(category==2){
        cat2_weight_medium = (h_category2_pt_types[event_type-1]->GetEntries())*FR_mu_medium/(1-FR_mu_medium);
        cat2_weight_tight = (h_category2_pt_types[event_type-1]->GetEntries())*FR_mu_tight/(1-FR_mu_tight);
	h_cat2_FR_medium->Fill(5,weight*cat2_weight_medium);
	h_cat2_FR_tight->Fill(5,weight*cat2_weight_tight);
	}
        break;
        //EEEM
        case 6:
        if(category==0){
        cat0_weight_medium = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_ele_medium*FR_mu_medium)/(1-FR_ele_medium*FR_mu_medium);
        cat0_weight_tight = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_ele_tight*FR_mu_tight)/(1-FR_ele_tight*FR_mu_tight);
	h_cat0_FR_medium->Fill(6,weight*cat0_weight_medium);
	h_cat0_FR_tight->Fill(6,weight*cat0_weight_tight);
        }
        else if(category==1){
        cat1_weight_medium = (h_category1_pt_types[event_type-1]->GetEntries())*FR_ele_medium/(1-FR_ele_medium);
        cat1_weight_tight = (h_category1_pt_types[event_type-1]->GetEntries())*FR_ele_tight/(1-FR_ele_tight);
	h_cat1_FR_medium->Fill(6,weight*cat1_weight_medium);
	h_cat1_FR_tight->Fill(6,weight*cat1_weight_tight);
	}
        else if(category==2){
        cat2_weight_medium = (h_category2_pt_types[event_type-1]->GetEntries())*FR_mu_medium/(1-FR_mu_medium);
        cat2_weight_tight = (h_category2_pt_types[event_type-1]->GetEntries())*FR_mu_tight/(1-FR_mu_tight);
	h_cat2_FR_medium->Fill(6,weight*cat2_weight_medium);
	h_cat2_FR_tight->Fill(6,weight*cat2_weight_tight);
	}
        break;
        //EEET
        case 7:
        FR_tau_medium = fakeTau_medium(Hcand[1].pt);
        FR_tau_tight = fakeTau_tight(Hcand[1].pt);
        if(category==0){
	cat0_weight_medium = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_ele_medium*FR_tau_medium)/(1-FR_ele_medium*FR_tau_medium);	
	cat0_weight_tight = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_ele_tight*FR_tau_tight)/(1-FR_ele_tight*FR_tau_tight);	
	h_cat0_FR_medium->Fill(7,weight*cat0_weight_medium);
	h_cat0_FR_tight->Fill(7,weight*cat0_weight_tight);
        }
	else if(category==1){
        cat1_weight_medium = (h_category1_pt_types[event_type-1]->GetEntries())*FR_tau_medium/(1-FR_tau_medium);
        cat1_weight_tight = (h_category1_pt_types[event_type-1]->GetEntries())*FR_tau_tight/(1-FR_tau_tight);
	h_cat1_FR_medium->Fill(7,weight*cat1_weight_medium);
	h_cat1_FR_tight->Fill(7,weight*cat1_weight_tight);
        }
	else if(category==2){
        cat2_weight_medium = (h_category2_pt_types[event_type-1]->GetEntries())*FR_ele_medium/(1-FR_ele_medium);
        cat2_weight_tight = (h_category2_pt_types[event_type-1]->GetEntries())*FR_ele_tight/(1-FR_ele_tight);
	h_cat2_FR_medium->Fill(7,weight*cat2_weight_medium);
	h_cat2_FR_medium->Fill(7,weight*cat2_weight_tight);
	}	        
	break;
        //EETT
        case 8:
        FR_tau1_medium = fakeTau_medium(Hcand[0].pt);
        FR_tau1_tight = fakeTau_tight(Hcand[0].pt);
        FR_tau2_medium = fakeTau_medium(Hcand[1].pt);
        FR_tau2_tight = fakeTau_tight(Hcand[1].pt);
        m_logger << DEBUG << " event_type: " << event_type << " Hcand[0].pt " << Hcand[0].pt << " func med " << fakeTau_medium(Hcand[0].pt) << " func tight " << fakeTau_tight(Hcand[0].pt) << SLogger::endmsg;
        m_logger << DEBUG << " event_type: " << event_type << " Hcand[1].pt " << Hcand[1].pt << " func med " << fakeTau_medium(Hcand[1].pt) << " func tight " << fakeTau_tight(Hcand[1].pt) << SLogger::endmsg;
        m_logger << DEBUG << " event_type: " << event_type << " Hcand[0].pt " << Hcand[0].pt << " func med " << p0_medium*(TMath::Exp(p1_medium*Hcand[0].pt))+p2_medium << " func tight " << p0_tight*(TMath::Exp(p1_tight*Hcand[0].pt))+p2_tight  << SLogger::endmsg;
        m_logger << DEBUG << " event_type: " << event_type << " Hcand[1].pt " << Hcand[1].pt << " func med " << p0_medium*(TMath::Exp(p1_medium*Hcand[1].pt))+p2_medium << " func tight " << p0_tight*(TMath::Exp(p1_tight*Hcand[1].pt))+p2_tight  << SLogger::endmsg;

        if(category==0){
        cat0_weight_medium = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_tau1_medium*FR_tau2_medium)/(1-FR_tau1_medium*FR_tau2_medium);
        cat0_weight_tight = (h_category0_pt_types[event_type-1]->GetEntries())*(FR_tau1_tight*FR_tau2_tight)/(1-FR_tau1_tight*FR_tau2_tight);
	h_cat0_FR_medium->Fill(8,weight*cat0_weight_medium);
	h_cat0_FR_tight->Fill(8,weight*cat0_weight_tight);
        }
	else if(category==1){
        cat1_weight_medium = (h_category1_pt_types[event_type-1]->GetEntries())*(FR_tau1_medium)/(1-FR_tau1_medium);
        cat1_weight_tight = (h_category1_pt_types[event_type-1]->GetEntries())*(FR_tau1_tight)/(1-FR_tau1_tight);
	h_cat1_FR_medium->Fill(8,weight*cat1_weight_medium);
	h_cat1_FR_tight->Fill(8,weight*cat1_weight_tight);

        }
	else if(category==2){
        cat2_weight_medium = (h_category2_pt_types[event_type-1]->GetEntries())*(FR_tau2_medium)/(1-FR_tau2_medium);
        cat2_weight_tight = (h_category2_pt_types[event_type-1]->GetEntries())*(FR_tau2_tight)/(1-FR_tau2_tight);
	h_cat2_FR_medium->Fill(8,weight*cat2_weight_medium);
	h_cat2_FR_tight->Fill(8,weight*cat2_weight_tight);
        }
	break;

        }	
	
	h_cut_flow->Fill(10,1);
	h_cut_flow_weight->Fill(10,weight);

        // DeltaR check
        Hist("h_deltaR")->Fill(deltaR(Hcand[0].eta,Hcand[0].phi,Hcand[1].eta,Hcand[1].phi));
        Hist("h_deltaR")->Fill(deltaR(Zcand[0].eta,Zcand[0].phi,Zcand[1].eta,Zcand[1].phi));
        Hist("h_deltaR")->Fill(deltaR(Zcand[0].eta,Zcand[0].phi,Hcand[1].eta,Hcand[1].phi));
        Hist("h_deltaR")->Fill(deltaR(Zcand[0].eta,Zcand[0].phi,Hcand[0].eta,Hcand[0].phi));
        Hist("h_deltaR")->Fill(deltaR(Zcand[1].eta,Zcand[1].eta,Hcand[1].eta,Hcand[1].phi));
        Hist("h_deltaR")->Fill(deltaR(Zcand[1].eta,Zcand[1].phi,Hcand[0].eta,Hcand[0].phi));

        //max DeltaR
        std::vector<double> deltaRlist;
        deltaRlist.clear();
        deltaRlist.push_back(deltaR(Hcand[0].eta,Hcand[0].phi,Hcand[1].eta,Hcand[1].phi));
        deltaRlist.push_back(deltaR(Zcand[0].eta,Zcand[0].phi,Zcand[1].eta,Zcand[1].phi));
        deltaRlist.push_back(deltaR(Zcand[0].eta,Zcand[0].phi,Hcand[1].eta,Hcand[1].phi));
        deltaRlist.push_back(deltaR(Zcand[0].eta,Zcand[0].phi,Hcand[0].eta,Hcand[0].phi));
        deltaRlist.push_back(deltaR(Zcand[1].eta,Zcand[1].phi,Hcand[1].eta,Hcand[1].phi));
        deltaRlist.push_back(deltaR(Zcand[1].eta,Zcand[1].phi,Hcand[0].eta,Hcand[0].phi));

        double maxDR = deltaRlist[0];
        double minDR = deltaRlist[0];

	for(int i = 0; i<(int)deltaRlist.size(); i++)
	{
		if(deltaRlist[i] > maxDR)
			maxDR = deltaRlist[i];
		if(minDR > deltaRlist[i])
			minDR = deltaRlist[i];
	}
        Hist("h_deltaR_max")->Fill(maxDR);
        Hist("h_deltaR_min")->Fill(minDR);
        
    	if( found_event && event_type!=evt_type[pos]) {
	  m_logger << ERROR << " Wrong event type. His is " << evt_type[pos] << " and mine is " << event_type << SLogger::endmsg;
  }
    
    
    if (!found_event && signal){
	 	  m_logger << ERROR << " My plus of type " << event_type << SLogger::endmsg;
		TLorentzVector Zvector;
		TLorentzVector Hvector;
		std::cout << " -------------------------------------------------------------------------------- " << std::endl;
		std::cout << " lumi number " << m->lumiNumber << " event number: " << m->eventNumber << " entry " << entries << std::endl;;
		switch(event_type){
		case 1: 
			std::cout << "Mu1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoMu(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "Mu2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoMu(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << std::endl;                                    	
			std::cout << "Mu3(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " iso " << RelIsoMu(Hcand[0]) << " charge " << Hcand[0].charge << std::endl;
			std::cout << "Tau1(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " AgainstMuonTight " << Hcand[1].discriminationByMuonTight << " AgainstElectronLoose " << Hcand[1].discriminationByElectronLoose
			<< " CombinedMediumIsolation " << Hcand[1].byMediumCombinedIsolationDeltaBetaCorr << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << std::endl;
            break;
        case 2:
            std::cout << "Mu1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoMu(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "Mu2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoMu(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << std::endl;                                    	
			std::cout << "Mu3(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " iso " << RelIsoMu(Hcand[0]) << " charge " << Hcand[0].charge << std::endl;
			std::cout << "El1(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " iso " << RelIsoEl(Hcand[1]) << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << std::endl;
            break;
		case 3: 
			std::cout << "Mu1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoMu(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "Mu2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoMu(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << std::endl;                                    	
			std::cout << "El1(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " iso " << RelIsoEl(Hcand[0]) << " charge " << Hcand[0].charge << " missing hits in ID " << Hcand[0].numLostHitEleInner << std::endl;
			std::cout << "Tau1(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " AgainstMuonLoose " << Hcand[1].discriminationByMuonLoose << " AgainstElectronMVA " << Hcand[1].discriminationByElectronMVA
			<< " CombinedMediumIsolation " << Hcand[1].byMediumCombinedIsolationDeltaBetaCorr << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << std::endl;
            break;
        case 4: 
			std::cout << "Mu1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoMu(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "Mu2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoMu(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << std::endl;                                    	
			std::cout << "Tau1(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " AgainstMuonMedium " << Hcand[0].discriminationByMuonMedium << " AgainstElectronMedium " << Hcand[0].discriminationByElectronMedium
			<< " TightCombinedIsolation " << Hcand[0].byTightCombinedIsolationDeltaBetaCorr << " charge " << Hcand[0].charge << std::endl;
			std::cout << "Tau2(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " AgainstMuonMedium " << Hcand[1].discriminationByMuonMedium << " AgainstElectronMedium " << Hcand[1].discriminationByElectronMedium
			<< " TightCombinedIsolation " << Hcand[1].byTightCombinedIsolationDeltaBetaCorr << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << std::endl;
            break;
        case 5: 
			std::cout << "El1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoEl(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "El2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoEl(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << std::endl;                                    	
			std::cout << "Mu1(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " iso " << RelIsoMu(Hcand[0]) << " charge " << Hcand[0].charge << std::endl;
			std::cout << "Tau1(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " AgainstMuonTight " << Hcand[1].discriminationByMuonTight << " AgainstElectronLoose " << Hcand[1].discriminationByElectronLoose
			<< " CombinedMediumIsolation " << Hcand[1].byMediumCombinedIsolationDeltaBetaCorr << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << std::endl;
            break;
        case 6:
            std::cout << "El1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoEl(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "El2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoEl(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << std::endl;                                    	
			std::cout << "Mu1(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " iso " << RelIsoMu(Hcand[0]) << " charge " << Hcand[0].charge << std::endl;
			std::cout << "El3(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " iso " << RelIsoEl(Hcand[1]) << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << std::endl;
            break;
		case 7: 
			std::cout << "El1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoEl(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "El2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoEl(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << std::endl;                                    	
		    std::cout << "El3(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " iso " << RelIsoEl(Hcand[0]) << " charge " << Hcand[0].charge << " missing hits in ID " << Hcand[0].numLostHitEleInner << std::endl;
		    std::cout << "Tau1(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " AgainstMuonLoose " << Hcand[1].discriminationByMuonLoose << " AgainstElectronMVA " << Hcand[1].discriminationByElectronMVA
			<< " CombinedMediumIsolation " << Hcand[1].byMediumCombinedIsolationDeltaBetaCorr << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << std::endl;
            break;
        case 8: 
			std::cout << "El1(Z): pt: " << Zcand[0].pt << " eta: " << Zcand[0].eta << " phi: " << Zcand[0].phi << " iso " << RelIsoEl(Zcand[0]) << " charge " << Zcand[0].charge << std::endl;
			std::cout << "El2(Z): pt: " << Zcand[1].pt << " eta: " << Zcand[1].eta << " phi: " << Zcand[1].phi << " iso " << RelIsoEl(Zcand[1]) << " charge " << Zcand[1].charge << std::endl;
			Zvector.SetPxPyPzE(Zcand[1].px+Zcand[0].px,Zcand[0].py+Zcand[1].py,Zcand[0].pz+Zcand[1].pz,Zcand[0].E+Zcand[1].E);
            std::cout << " Z mass " << Zvector.M() << std::endl;                                    	
			std::cout << "Tau1(H): pt: " << Hcand[0].pt << " eta: " << Hcand[0].eta << " phi: " << Hcand[0].phi << " AgainstMuonMedium " << Hcand[0].discriminationByMuonMedium << " AgainstElectronMedium " << Hcand[0].discriminationByElectronMedium
			<< " TightCombinedIsolation " << Hcand[0].byTightCombinedIsolationDeltaBetaCorr << " charge " << Hcand[0].charge << std::endl;
			std::cout << "Tau2(H): pt: " << Hcand[1].pt << " eta: " << Hcand[1].eta << " phi: " << Hcand[1].phi << " AgainstMuonMedium " << Hcand[1].discriminationByMuonMedium << " AgainstElectronMedium " << Hcand[1].discriminationByElectronMedium
			<< " TightCombinedIsolation " << Hcand[1].byTightCombinedIsolationDeltaBetaCorr << " charge " << Hcand[1].charge << std::endl;
			Hvector.SetPxPyPzE(Hcand[1].px+Hcand[0].px,Hcand[0].py+Hcand[1].py,Hcand[0].pz+Hcand[1].pz,Hcand[0].E+Hcand[1].E);
            std::cout << " H mass " << Hvector.M() << std::endl;
            break;
    	}	
		std::cout << "---> Detailed accounts: " << std::endl;
		std::cout << " ---------------- MUONS ---------------------- " << std::endl;
		 for (uint i = 0; i < muon.size(); i++) {

		double muPt = muon[i].pt;
		double muEta = muon[i].eta;
		bool muGlobal = muon[i].isGlobalMuon;
		bool muTracker = muon[i].isTrackerMuon;
		double relIso = RelIsoMu(muon[i]);
		
		bool pfID = PFMuonID(muon[i]);	
		std::cout << " --> no. " << i << " pt "  << muPt << " eta " << muEta << " phi " << muon[i].phi 
		<< " ID: " << pfID << " iso " << relIso << std::endl; 
		
		if (muGlobal && muTracker && muPt > 10 && fabs(muEta) < 2.4 && relIso < 0.4 && pfID)
		{
					goodMuon.push_back(muon[i]);
					std::cout << "  ----> GOOD MUON <---- " << std::endl;
					Hist("h_mu_relIso")->Fill(relIso);
		}
		
    }
    std::cout << " ---------------- ELECTRONS ---------------------- " << std::endl;
		
		for (uint i = 0; i < electron.size(); i++) {

		double elPt = electron[i].pt;
		double elEta = electron[i].eta;
		int missingHits = electron[i].numLostHitEleInner;
		bool elID = EleMVANonTrigId(elPt,elEta,electron[i].Id_mvaNonTrg);
		double relIso = RelIsoEl(electron[i]);
		std::cout << " --> no. " << i << " pt "  << elPt << " eta " << elEta << " phi " << electron[i].phi 
		<< " ID: " << elID << " mHits " << missingHits << " iso " << relIso << std::endl; 
		
		if (elPt > 10 && fabs(elEta) < 2.5 && missingHits <= 1 && relIso < 0.4 && elID)
		{
			goodElectron.push_back(electron[i]);
			std::cout << "  ----> GOOD ELECTRON <---- " << std::endl;
			Hist("h_el_relIso")->Fill(relIso);
		}
    }
		
	std::cout << " ---------------- TAUS ---------------------- " << std::endl;
	
	for (uint i = 0; i < tau.size(); i++) {
   
		double tauPt = tau[i].pt;
		double tauEta = tau[i].eta;
		bool LooseElectron = (tau[i].discriminationByElectronLoose > 0.5);
		bool LooseMuon = (tau[i].discriminationByMuonLoose > 0.5);
		bool CombinedIsolation = (tau[i].byMediumCombinedIsolationDeltaBetaCorr > 0.5);
		bool DecayMode = (tau[i].discriminationByDecayModeFinding > 0.5);
		
		if (tauPt > 20 && fabs(tauEta) < 2.3 && LooseElectron && LooseMuon && CombinedIsolation && DecayMode){
			goodTau.push_back(tau[i]);
			std::cout << " --> no. " << i << " pt "  << tauPt << " eta " << tauEta << " phi " << tau[i].phi << std::endl; 
		}
		
    }
	
	
		
}

      
	if(signal && printoutEvents)
	{
		 TString fileName = GetInputTree(InTreeName.c_str())->GetDirectory()->GetFile()->GetName();
		 log1 << setiosflags(ios::fixed) << std::setprecision(1) << event_type << " " << m->runNumber << " " << m->lumiNumber << " " << m->eventNumber << " " << Zmass << " " << Hmass << std::endl;
	}
	
        }//close else (analysis case)
	
	return;


}

