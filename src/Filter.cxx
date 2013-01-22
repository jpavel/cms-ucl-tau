// $Id: CycleCreators.py 173 2010-05-12 15:49:33Z krasznaa $

// Local include(s):
#include "../include/Filter.h"
#include <iostream>

ClassImp( Filter );

Filter::Filter()
   : SCycleBase(), m_allEvents( "allEvents", this ) 
   {

   SetLogName( GetName() );
   DeclareProperty("InTreeName",InTreeName);
   
   DeclareProperty("ElectronTriggerName", doubEle);
		DeclareProperty("ElectronTriggerName2", doubEle2);

		DeclareProperty("MuonTriggerName1", doubMu);
		DeclareProperty("MuonTriggerName2", doubMu2);
		DeclareProperty("MuonTriggerName3", doubMu3);
		
		DeclareProperty("is2011",is2011);
		DeclareProperty("is2012_52",is2012_52);
		DeclareProperty("is2012_53",is2012_53);
		DeclareProperty("useTruePileUp",useTruePileUp);
		DeclareProperty("vetoMuonTrigger",vetoMuonTrigger);
		DeclareProperty("vetoElectronTrigger", vetoElectronTrigger);
		
		DeclareProperty("N_ALL",N_ALL);
		DeclareProperty("N_ELMU",N_ELMU);
		
		DeclareProperty("cut_mu_pt",cut_mu_pt);
		DeclareProperty("cut_mu_eta",cut_mu_eta);    
		DeclareProperty("cut_el_pt",cut_el_pt);
		DeclareProperty("cut_el_eta",cut_el_eta);
		DeclareProperty("cut_tau_pt",cut_tau_pt);
		DeclareProperty("cut_tau_eta",cut_tau_eta);
		DeclareProperty("cut_dR", cut_dR);
		DeclareProperty("lepton_mass_min", lepton_mass_min);
		DeclareProperty("lepton_mass_max", lepton_mass_max);
}

Filter::~Filter() {

}

void Filter::BeginCycle() throw( SError ) {

   return;

}

void Filter::EndCycle() throw( SError ) {

   return;

}

void Filter::BeginInputData( const SInputData& ) throw( SError ) {

	//DeclareVariable(out,"myevent");
	outFile = new TFile("output.root","recreate");
	outTree = new TTree("t","filtered tree");
	outTree->Branch("myevent",&out);
	lumi.open("lumi.csv");
	
	current_run=current_lumi=-999;
   return;

}

void Filter::EndInputData( const SInputData& ) throw( SError ) {
	lumi.close();
	outTree->Write();
	outFile->Close();
	 m_logger << INFO << "Number of all processed events: "
            << *m_allEvents
            << SLogger::endmsg;
     ofstream log1;       
     log1.open("total.txt");
     log1 << *m_allEvents << std::endl;
     log1.close();
     
   return;

}

void Filter::BeginInputFile( const SInputData& ) throw( SError ) {
	ConnectVariable(InTreeName.c_str(),"myevent",m);
   return;

}

double Filter::deltaR(double eta1, double phi1, double eta2, double phi2){
	double dR, dPhi, dEta;
	dR=dPhi=dEta=0.0;
	dPhi = phi1-phi2;
	if (dPhi < -TMath::Pi()) dPhi += TMath::TwoPi();
	if (dPhi > +TMath::Pi()) dPhi -= TMath::TwoPi();
	dEta = eta1-eta2;
	dR = sqrt(dPhi*dPhi+dEta*dEta);

	return dR;
}

double Filter::deltaR(myobject o1, myobject o2)
{
	return deltaR(o1.eta,o1.phi,o2.eta,o2.phi);
}

bool Filter::Trg_MC_12(myevent* m) {
	map<string, int> myHLT = m->HLT;
	bool Trigger = false;
	bool TriggerEle = false;
	bool TriggerMu = false;


	for (map<string, int> ::iterator ihlt = myHLT.begin(); ihlt != myHLT.end() && !TriggerEle && !TriggerMu; ihlt++) {
		//	std::cout << ihlt->first << std::endl; 
		size_t foundEl=(ihlt->first).find(doubEle);
		size_t foundEl2=(ihlt->first).find(doubEle2);
		if(!is2011) foundEl2=foundEl;

		size_t foundMu1=(ihlt->first).find(doubMu);
		size_t foundMu2=(ihlt->first).find(doubMu2);
		size_t foundMu3=(ihlt->first).find(doubMu3);
		if(!is2011) foundMu3=foundMu2;

		if (foundEl!=string::npos || foundEl2!=string::npos)
			TriggerEle = ihlt->second;
		if (foundMu1!=string::npos || foundMu2!=string::npos || foundMu3!=string::npos)
			TriggerMu = ihlt->second;
	}
	Trigger = TriggerEle || TriggerMu;
	if(vetoElectronTrigger && TriggerEle) Trigger = false;
	if(vetoMuonTrigger && TriggerMu) Trigger = false;    
	return Trigger;    
}

void Filter::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
	
	++m_allEvents;
	if(m->runNumber!=current_run || m->lumiNumber!=current_lumi){
		lumi << m->runNumber << " " << m->lumiNumber << std::endl;
		current_run=m->runNumber;
		current_lumi=m->lumiNumber;
	}
	m_logger << DEBUG << " Now executing event " << m->eventNumber << " in a run " << m->runNumber << SLogger::endmsg;
	double event_number=9612;
	bool printout = false;
	if(m->eventNumber==event_number) printout=true;
	if(printout) std::cout << "Here!" << std::endl;
	
	bool trigPass = Trg_MC_12(m);
	m_logger << DEBUG << " Trigger decision " << trigPass << SLogger::endmsg;
	if(!trigPass)
	{
		if(printout) std::cout << "Trigger!" << std::endl;
		return;
	}
	if(printout) std::cout << "Here2!" << std::endl;
	
	
	std::vector<myobject> vertex = m->Vertex;
	bool goodVertex = false;
	for (uint i = 0; i < vertex.size() && !goodVertex; i++) {
		if (vertex[i].isValid && vertex[i].normalizedChi2 > 0 && vertex[i].ndof > 4 && fabs(vertex[i].z) < 24)
		goodVertex=true;
	}
	
	if(!goodVertex){		
		if(printout) std::cout << "vertex!" << std::endl;
		return;
	}
	
	
	std::vector<myobject> muon = m->PreSelectedMuons;
	m_logger << VERBOSE << " There are " << muon.size() << " preselected muons " << SLogger::endmsg;

	std::vector<myobject> goodMuon;
	goodMuon.clear();

	for (uint i = 0; i < muon.size(); i++) {

		double muPt = muon[i].pt;
		double muEta = muon[i].eta;	
		if (muPt > cut_mu_pt && fabs(muEta) < cut_mu_eta)
		{
				goodMuon.push_back(muon[i]);
		}

	}
	
	uint N_MU=goodMuon.size();
	
	std::vector<myobject> electron = m->PreSelectedElectrons;
	m_logger << VERBOSE << " There are " << electron.size() << " preselected electrons " << SLogger::endmsg;
	
	std::vector<myobject> goodElectron;
	goodElectron.clear();

	for (uint i = 0; i < electron.size(); i++) {

		double elPt = electron[i].pt;
		double elEta = electron[i].eta;
		
		if (elPt > cut_el_pt && fabs(elEta) < cut_el_eta )
		{
			goodElectron.push_back(electron[i]);
		}
	}
	
	uint N_EL=goodElectron.size();
	
	std::vector<myobject> tau = m->PreSelectedHPSTaus;

	m_logger << DEBUG << " There are " << tau.size() << " preselected taus " << SLogger::endmsg;

	std::vector<myobject> goodTau;
	goodTau.clear();

	for (uint i = 0; i < tau.size(); i++) {

		double tauPt = tau[i].pt;
		double tauEta = tau[i].eta;
		bool DecayMode = (tau[i].discriminationByDecayModeFinding > 0.5);


		if (tauPt > cut_tau_pt && fabs(tauEta) < cut_tau_eta && DecayMode)
			goodTau.push_back(tau[i]);
	}
	
	uint N_TAU=goodTau.size();
	m_logger << DEBUG << " There are " << N_MU << " muons " << N_EL << " electrons and " << N_TAU << " taus." << SLogger::endmsg;

	if(N_ALL > 0 && (N_MU+N_EL+N_TAU) < N_ALL){		if(printout) std::cout << "N_ALL!" << std::endl; return;}
	if(N_ELMU > 0 && (N_MU+N_EL) < N_ELMU){		if(printout) std::cout << "N_ELMU!" << std::endl; return;}
	
	if(printout) std::cout << "Here3!" << std::endl;
	
	
	bool failDR = false;
	if(cut_dR > 0){
		if(N_MU > 0)
		{
			for(uint iMu=0; iMu < N_MU && !failDR; iMu++)
			{
				for(uint jMu =iMu+1; jMu < N_MU && !failDR; jMu++)
				{
					double dR=deltaR(goodMuon[iMu],goodMuon[jMu]);
					m_logger << VERBOSE << " MuMu: " << iMu << " " << jMu << " :" << dR << SLogger::endmsg;	
					if(dR < cut_dR) failDR=true;
				}
				
				for(uint iEl =0; iEl < N_EL && !failDR; iEl++)
				{
					double dR=deltaR(goodMuon[iMu],goodElectron[iEl]);
					m_logger << VERBOSE << " MuEl: " << iMu << " " << iEl << " :" << dR << SLogger::endmsg;	
					if(dR < cut_dR) failDR=true;
				}
				
				for(uint iTau =0; iTau < N_TAU && !failDR; iTau++)
				{
					double dR=deltaR(goodMuon[iMu],goodTau[iTau]);
					m_logger << VERBOSE << " MuTau: " << iMu << " " << iTau << " :" << dR << SLogger::endmsg;	
					if(dR < cut_dR) failDR=true;
				}
			}
		}else if(N_EL > 0)
		{
			for(uint iEl=0; iEl < N_EL && !failDR; iEl++)
			{
				for(uint jEl =iEl+1; jEl < N_EL && !failDR; jEl++)
				{
					double dR=deltaR(goodElectron[iEl],goodElectron[jEl]);
					m_logger << VERBOSE << " ElEl: " << iEl << " " << jEl << " :" << dR << SLogger::endmsg;	
					if(dR < cut_dR) failDR=true;
				}
				
				for(uint iTau =0; iTau < N_TAU && !failDR; iTau++)
				{
					double dR=deltaR(goodElectron[iEl],goodTau[iTau]);
					m_logger << VERBOSE << " ElTau: " << iEl << " " << iTau << " :" << dR << SLogger::endmsg;	
					if(dR < cut_dR) failDR=true;
				}
			}
		
		}else if(N_TAU > 0)
		{
			for(uint iTau=0; iTau < N_TAU && !failDR; iTau++)
			{
				for(uint jTau =iTau+1; jTau < N_TAU && !failDR; jTau++)
				{
					double dR=deltaR(goodTau[iTau],goodTau[jTau]);
					m_logger << VERBOSE << " TauTau: " << iTau << " " << jTau << " :" << dR << SLogger::endmsg;	
					if(dR < cut_dR) failDR=true;
				}
			}
		}
	}
	
	if(failDR){		if(printout) std::cout << "dR" << std::endl; return;}
	if(printout) std::cout << "Here4!" << std::endl;
	
	
	// dMass cut
	
	bool passMass = false;
	
	for (uint i = 0; i < goodMuon.size() && !passMass; i++) {
		for (uint j = i+1; j < goodMuon.size() && !passMass; j++) {
			TLorentzVector cand;
			cand.SetPxPyPzE(goodMuon[i].px+goodMuon[j].px,
					goodMuon[i].py+goodMuon[j].py,
					goodMuon[i].pz+goodMuon[j].pz,
					goodMuon[i].E+goodMuon[j].E);
			double mass = cand.M();
			if(printout) std::cout << mass << std::endl;
			if(mass > lepton_mass_min && mass < lepton_mass_max ) passMass=true;
			if(passMass) m_logger << DEBUG << " Passed mass cut with value " << mass << SLogger::endmsg;
			else m_logger << VERBOSE << " Failed mass cut with value " << mass << SLogger::endmsg;
		}
	}
	
	for (uint i = 0; i < goodElectron.size() && !passMass; i++) {
		for (uint j = i+1; j < goodElectron.size() && !passMass; j++) {
			TLorentzVector cand;
			cand.SetPxPyPzE(goodElectron[i].px+goodElectron[j].px,
					goodElectron[i].py+goodElectron[j].py,
					goodElectron[i].pz+goodElectron[j].pz,
					goodElectron[i].E+goodElectron[j].E);
			double mass = cand.M();
			if(printout) std::cout << mass << std::endl;
			if(mass > lepton_mass_min && mass < lepton_mass_max ) passMass=true;
			if(passMass) m_logger << DEBUG << " Passed mass cut with value " << mass << SLogger::endmsg;
			else m_logger << VERBOSE << " Failed mass cut with value " << mass << SLogger::endmsg;
		}
	}
	
	if(!passMass){		if(printout) std::cout << "Mass" << std::endl; return;}
	if(printout) std::cout << "Here5!" << std::endl;
	
	m_logger << DEBUG << " Passed!" << SLogger::endmsg;

	out=*m;
	outTree->Fill();
	
	if(printout) std::cout << "Pass!" << std::endl;
	
	
   return;

}
