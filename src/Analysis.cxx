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
   DeclareProperty("BestMassForZ",BestMassForZ);
   DeclareProperty("dZvertex", dZvertex);
   DeclareProperty("bTagValue",bTagValue);
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
    h_event_type=Book(TH1D("h_event_type","Event Type",8,0.5,8.5));



   DeclareVariable(out_pt,"el_pt");


	 h_event_type = Retrieve<TH1D>("h_event_type");
     h_event_type->GetXaxis()->SetBinLabel(1,"Z(#mu#mu)H(#mu#tau)");
     h_event_type->GetXaxis()->SetBinLabel(2,"Z(#mu#mu)H(#mu e)");
     h_event_type->GetXaxis()->SetBinLabel(3,"Z(#mu#mu)H(e#tau)");
     h_event_type->GetXaxis()->SetBinLabel(4,"Z(#mu#mu)H(#tau#tau)");
     h_event_type->GetXaxis()->SetBinLabel(5,"Z(ee)H(#mu#tau)");
	 h_event_type->GetXaxis()->SetBinLabel(6,"Z(ee)H(#mu e)");
	 h_event_type->GetXaxis()->SetBinLabel(7,"Z(ee)H(e#tau)");
	 h_event_type->GetXaxis()->SetBinLabel(8,"Z(ee)H(#tau#tau)");
	 

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
	
	

   return;

}

void Analysis::BeginInputFile( const SInputData& ) throw( SError ) {
	//ConnectVariable(InTreeName.c_str(),"el_n",el_n);
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
	if(pt>5. && pt<10. && fabs(eta)>=1.479 && value>0.295)
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

void Analysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {

	m_logger << DEBUG << " Now executing event " << m->eventNumber << " in a run " << m->runNumber << SLogger::endmsg;

	std::vector<myobject> goodMuon;
    goodMuon.clear();
    std::vector<myobject> goodElectron;
    goodElectron.clear();
    
    std::vector<myobject> muon = m->PreSelectedMuons;
    m_logger << VERBOSE << " There are " << muon.size() << " preselected muons " << SLogger::endmsg;

     for (uint i = 0; i < muon.size(); i++) {

		double muPt = muon[i].pt;
		double muEta = muon[i].eta;
		bool muGlobal = muon[i].isGlobalMuon;
		bool muTracker = muon[i].isTrackerMuon;
		int MunHit = muon[i].numberOfHits;
		double MuIsoTrk = muon[i].pfIsoCharged;
		double MuIsoEcal = muon[i].pfIsoGamma;
		double MuIsoHcal = muon[i].pfIsoNeutral;
		double MuIsoPU = muon[i].pfIsoPU;

		double relIso = (MuIsoTrk) / muon[i].pt;
		if (MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU > 0)
			relIso = (MuIsoTrk + MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU) / (muon[i].pt);

		if (muGlobal && muTracker && muPt > 10 && fabs(muEta) < 2.4 && MunHit > 10 && relIso < 0.25)
			goodMuon.push_back(muon[i]);
    }
	m_logger << VERBOSE << " There are " << goodMuon.size() << " good muons " << SLogger::endmsg;
	
	std::vector<myobject> electron = m->PreSelectedElectrons;
    m_logger << VERBOSE << " There are " << electron.size() << " preselected electrons " << SLogger::endmsg;

     for (uint i = 0; i < electron.size(); i++) {

		double elPt = electron[i].pt;
		double elEta = electron[i].eta;
		int missingHits = electron[i].numLostHitEleInner;
		double ElIsoTrk = electron[i].pfIsoCharged;
		double ElIsoEcal = electron[i].pfIsoGamma;
		double ElIsoHcal = electron[i].pfIsoNeutral;
		double ElIsoPU = electron[i].pfIsoPU;
		bool elID = EleMVANonTrigId(elPt,elEta,electron[i].Id_mvaNonTrg);

		double relIso = (ElIsoTrk) / electron[i].pt;
		if (ElIsoEcal + ElIsoHcal - 0.5 * ElIsoPU > 0)
			relIso = (ElIsoTrk + ElIsoEcal + ElIsoHcal - 0.5 * ElIsoPU) / (electron[i].pt);

		if (elPt > 10 && fabs(elEta) < 2.5 && missingHits < 1 && relIso < 0.25 && elID)
			goodElectron.push_back(electron[i]);
    }
	m_logger << VERBOSE << " There are " << goodElectron.size() << " good electrons " << SLogger::endmsg;
	
	// Z compatibility
	std::vector<myobject> Zcand;
	Zcand.clear();
	bool Zmumu = false;
	bool Zee = false;
	double dMass = 999.;
	int Zindex[2] = {-1,-1};
	for(uint i = 0; i < goodMuon.size(); i++)
	{
		m_logger << VERBOSE << "  ->good muon no. "<< i << " has pt "<<  goodMuon[i].pt << " and charge " << goodMuon[i].charge << SLogger::endmsg;
		if( goodMuon[i].pt < 20 || Zmumu) break;
		for(uint j = i+1; j < goodMuon.size() && !Zmumu; j++)
		{
			m_logger << VERBOSE << "  -->second muon no. "<< j << " has pt "<<  goodMuon[j].pt << " and charge " << goodMuon[j].charge << SLogger::endmsg;
			
			if(goodMuon[i].charge*goodMuon[j].charge >=0) continue;
			if(deltaR(goodMuon[i].eta,goodMuon[i].phi,goodMuon[j].eta,goodMuon[j].phi)< 0.1) continue;
			
			TLorentzVector cand;
			cand.SetPxPyPzE(goodMuon[i].px+goodMuon[j].px,
								goodMuon[i].py+goodMuon[j].py,
								goodMuon[i].pz+goodMuon[j].pz,
								goodMuon[i].E+goodMuon[j].E);
			double mass = cand.M();
			m_logger << VERBOSE << "  -->Candidate mass is " << mass << SLogger::endmsg;
			if(mass > 71 && mass < 111){ 
				Zmumu=true;
				double dM = 999.; 
				if(BestMassForZ > 0.0){
					Zmumu=false;
					dM=fabs(mass-BestMassForZ);
					if(dM < dMass){
						Zindex[0]=i;
						Zindex[1]=j;
						dMass=dM;
					}
				}else{
					Zindex[0]=i;
					Zindex[1]=j;
				}
			}
		}
	}
			if(Zindex[0] > -1 && Zindex[1] > -1){
				int i = Zindex[0];
				int j = Zindex[1];
				Zcand.push_back(goodMuon[i]);
				Zcand.push_back(goodMuon[j]);	
				goodMuon.erase(goodMuon.begin()+i);
				goodMuon.erase(goodMuon.begin()+j);
				Zmumu=true;
			}
 m_logger << VERBOSE << " There are " << goodMuon.size() << " remaining good muons " << SLogger::endmsg;
	
	if(!Zmumu)
	{
		dMass = 999.;
		for(uint i = 0; i < goodElectron.size(); i++)
		{
			m_logger << VERBOSE << " ->good electron no. "<< i << " has pt "<<  goodElectron[i].pt << " and charge " << goodElectron[i].charge << SLogger::endmsg;
			if( goodElectron[i].pt < 20 || Zee) break;
			for(uint j = i+1; j < goodElectron.size() && !Zee; j++)
			{
				m_logger << VERBOSE << "  -->second electron no. "<< j << " has pt "<<  goodElectron[j].pt << " and charge " << goodElectron[j].charge << SLogger::endmsg;
				
				if(goodElectron[i].charge*goodElectron[j].charge >=0) continue;
				if(deltaR(goodElectron[i].eta,goodElectron[i].phi,goodElectron[j].eta,goodElectron[j].phi)< 0.1) continue;
			
				TLorentzVector cand;
				cand.SetPxPyPzE(goodElectron[i].px+goodElectron[j].px,
									goodElectron[i].py+goodElectron[j].py,
									goodElectron[i].pz+goodElectron[j].pz,
									goodElectron[i].E+goodElectron[j].E);
				double mass = cand.M();
				m_logger << VERBOSE << "  -->Candidate mass is " << mass << SLogger::endmsg;
				if(mass > 71 && mass < 111){ 
					Zee=true;
					double dM = 999.; 
					if(BestMassForZ > 0.0){
						Zee=false;
						dM=fabs(mass-BestMassForZ);
						if(dM < dMass){
							Zindex[0]=i;
							Zindex[1]=j;
							dMass=dM;
						}
					}else{
						Zindex[0]=i;
						Zindex[1]=j;
					} 
					
				}
			}
		}
				if(Zindex[0] > -1 && Zindex[1] > -1){
					int i = Zindex[0];
					int j = Zindex[1];
					Zcand.push_back(goodElectron[i]);
					Zcand.push_back(goodElectron[j]);	
					goodElectron.erase(goodElectron.begin()+i);
					goodElectron.erase(goodElectron.begin()+j);
					Zee=true;
			}
	}
	
	m_logger << VERBOSE << " There are " << goodElectron.size() << " remaining good electrons " << SLogger::endmsg;
	
	if(Zmumu||Zee)
		m_logger << DEBUG << " There is a Z candidate! " << SLogger::endmsg;
	else
		return;
		
	// Z overlap removal
	for(uint i = 0; i < goodMuon.size(); i++)
	{
		for(uint j = 0; i < Zcand.size(); i++)
		{
			if(deltaR(goodMuon[i].eta,goodMuon[i].phi,Zcand[j].eta,Zcand[j].phi)< 0.1) 
				goodMuon.erase(goodMuon.begin()+i);
		}
	}
	
	for(uint i = 0; i < goodElectron.size(); i++)
	{
		for(uint j = 0; i < Zcand.size(); i++)
		{
			if(deltaR(goodElectron[i].eta,goodElectron[i].phi,Zcand[j].eta,Zcand[j].phi)< 0.1) 
				goodElectron.erase(goodElectron.begin()+i);
		}
	}
	m_logger << DEBUG << " There are " << goodMuon.size() << " and " << goodElectron.size() << " remaining after Z overlap removal " << SLogger::endmsg;
		
		// checking the rest of the event
		// list of good taus 
		std::vector<myobject> goodTau;
		goodTau.clear();
    
    
    std::vector<myobject> tau = m->PreSelectedHPSTaus;
    
    m_logger << DEBUG << " There are " << tau.size() << " preselected taus " << SLogger::endmsg;
    
    for (uint i = 0; i < tau.size(); i++) {
   
		double tauPt = tau[i].pt;
		double tauEta = tau[i].eta;
		bool LooseElectron = (tau[i].discriminationByElectronLoose > 0.5);
		bool LooseMuon = (tau[i].discriminationByMuonLoose > 0.5);
		bool CombinedIsolation = (tau[i].byMediumCombinedIsolationDeltaBetaCorr > 0.5);
		bool DecayMode = (tau[i].discriminationByDecayModeFinding > 0.5);
		
		if (tauPt > 20 && fabs(tauEta) < 2.3 && LooseElectron && LooseMuon && CombinedIsolation && DecayMode)
			goodTau.push_back(tau[i]);
    }
    
    for(uint i = 0; i < goodTau.size(); i++)
	{
		for(uint j = 0; j < Zcand.size(); j++)
		{
			if(deltaR(goodTau[i].eta,goodTau[i].phi,Zcand[j].eta,Zcand[j].phi)< 0.1) 
				goodTau.erase(goodTau.begin()+i);
		}
	}
    
	m_logger << DEBUG << " There are " << goodTau.size() << " good taus " << SLogger::endmsg;	
	
		// mutau and emu final states
		bool muTau=false;
		bool muE = false;
		std::vector<myobject> Hcand;
	    Hcand.clear();
		for(uint i = 0; i < goodMuon.size() && !muTau && !muE; i++)
		{
			double MuIsoTrk = goodMuon[i].pfIsoCharged;
			double MuIsoEcal = goodMuon[i].pfIsoGamma;
			double MuIsoHcal = goodMuon[i].pfIsoNeutral;
			double MuIsoPU = goodMuon[i].pfIsoPU;

			double relIso = (MuIsoTrk) / goodMuon[i].pt;
			if (MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU > 0)
				relIso = (MuIsoTrk + MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU) / (goodMuon[i].pt);
			
			if(relIso < 0.15)
			{
				m_logger << DEBUG << " Checking for muE with very isolated muon" << SLogger::endmsg;	
				for(uint j=0; j< goodElectron.size() && !muE; j++)
				{
					if(goodMuon[i].charge*goodElectron[j].charge >=0) continue;
					if(deltaR(goodElectron[j].eta,goodElectron[j].phi,goodMuon[i].eta,goodMuon[i].phi)< 0.1) continue;
					muE=true;
					Hcand.push_back(goodMuon[i]);
					Hcand.push_back(goodElectron[j]);
					goodMuon.erase(goodMuon.begin()+i);
				    goodElectron.erase(goodElectron.begin()+j);
				}
				
				m_logger << DEBUG << " Checking for muTau " << SLogger::endmsg;	
				for(uint j=0; j< goodTau.size() && !muTau && !muE; j++)
				{
					if(goodMuon[i].charge*goodTau[j].charge >=0) continue;
					if(goodTau[j].discriminationByMuonTight <=0.5) continue;
					if(deltaR(goodTau[j].eta,goodTau[j].phi,goodMuon[i].eta,goodMuon[i].phi)< 0.1) continue; 
					muTau=true;
					Hcand.push_back(goodMuon[i]);
					Hcand.push_back(goodTau[j]);
					goodMuon.erase(goodMuon.begin()+i);
				    goodTau.erase(goodTau.begin()+j);
				}
			}else {//muE candidate
				m_logger << DEBUG << " Checking for muE " << SLogger::endmsg;	
				for(uint j=0; j< goodElectron.size() && !muE; j++)
				{
					if(goodMuon[i].charge*goodElectron[j].charge >=0) continue;
					if(deltaR(goodElectron[j].eta,goodElectron[j].phi,goodMuon[i].eta,goodMuon[i].phi)< 0.1) continue;
					muE=true;
					Hcand.push_back(goodMuon[i]);
					Hcand.push_back(goodElectron[j]);
					goodMuon.erase(goodMuon.begin()+i);
				    goodElectron.erase(goodElectron.begin()+j);
				}
			}
		}
		
		if(muTau) m_logger << INFO << " muTau candidate!" << SLogger::endmsg;	
		else if(muE) m_logger << INFO << " muE candidate!" << SLogger::endmsg;			
		else m_logger << DEBUG << " Checking no-muon channels" << SLogger::endmsg;
		
		bool eTau = false;
		if(!muTau && !muE)
		{
			for(uint i = 0; i < goodElectron.size() && !eTau ; i++)
			{
				double ElIsoTrk = goodElectron[i].pfIsoCharged;
				double ElIsoEcal = goodElectron[i].pfIsoGamma;
				double ElIsoHcal = goodElectron[i].pfIsoNeutral;
				double ElIsoPU = goodElectron[i].pfIsoPU;
	
				double relIso = (ElIsoTrk) / goodElectron[i].pt;
				if (ElIsoEcal + ElIsoHcal - 0.5 * ElIsoPU > 0)
					relIso = (ElIsoTrk + ElIsoEcal + ElIsoHcal - 0.5 * ElIsoPU) / (goodElectron[i].pt);
				
				if(relIso < 0.10 && goodElectron[i].numLostHitEleInner < 1)
				{
					m_logger << DEBUG << " Checking for eTau " << SLogger::endmsg;	
					for(uint j=0; j< goodTau.size() && !muTau; j++)
					{
						if(goodElectron[i].charge*goodTau[j].charge >=0) continue;
						if(goodTau[j].discriminationByElectronMVA <=0.5) continue;
						if(deltaR(goodTau[j].eta,goodTau[j].phi,goodElectron[i].eta,goodElectron[i].phi)< 0.1) continue;
						eTau=true;
						Hcand.push_back(goodElectron[i]);
						Hcand.push_back(goodTau[j]);
						goodElectron.erase(goodElectron.begin()+i);
					    goodTau.erase(goodTau.begin()+j);
					}
				}
			}
		
		}

		if(eTau) m_logger << INFO << " eTau candidate!" << SLogger::endmsg;
		else m_logger << DEBUG << " Checking fully hadronic decay" << SLogger::endmsg;
		
		bool tauTau =false;
		if(!muTau && !muE && !eTau)
		{
			for(uint i = 0; i < goodTau.size() && !tauTau ; i++)
			{
				
					if(goodTau[i].discriminationByElectronMedium <=0.5) continue;
					if(goodTau[i].discriminationByMuonMedium <=0.5) continue;
					if(goodTau[i].byTightCombinedIsolationDeltaBetaCorr <=0.5) continue;
					
					for(uint j=i+1; j< goodTau.size() && !tauTau; j++)
					{
						if(goodTau[i].charge*goodTau[j].charge >=0) continue;
						if(goodTau[j].discriminationByElectronMedium <=0.5) continue;
						if(goodTau[j].discriminationByMuonMedium <=0.5) continue;
						if(goodTau[j].byTightCombinedIsolationDeltaBetaCorr <=0.5) continue;
						if(deltaR(goodTau[j].eta,goodTau[j].phi,goodTau[i].eta,goodTau[i].phi)< 0.1) continue;
						tauTau=true;
						Hcand.push_back(goodTau[i]);
						Hcand.push_back(goodTau[j]);
						goodTau.erase(goodTau.begin()+i);
					    goodTau.erase(goodTau.begin()+j);
					}
				
			}
		}
		
		if(Hcand.size()==0 || (!muTau && !muE && !eTau && !tauTau)){ m_logger << DEBUG << " No Higgs candidate. Going to next event" << SLogger::endmsg; return;}
		else m_logger << INFO << "Higgs candidate. Size is " << Hcand.size() << SLogger::endmsg;
		// cross-check
		if(muTau+muE+eTau+tauTau > 1){
			 m_logger << ERROR << "Non-exclusive event type!! Aborting." << SLogger::endmsg;
			 return;
		 }
		 
		 if(goodMuon.size()+goodTau.size()+goodElectron.size()>0) 
		 {
			m_logger << INFO << "Additional good lepton(s) present. Aborting. " << SLogger::endmsg;
			return;
		 }
		 
	// Same vertex check
	
	bool dZ_expo = (fabs(Zcand[0].z_expo - Zcand[1].z_expo) < dZvertex && fabs(Zcand[0].z_expo - Hcand[0].z_expo) < dZvertex && fabs(Zcand[0].z_expo - Hcand[1].z_expo) < dZvertex);		
	if(!dZ_expo)
	{
		m_logger << INFO << "Not from the same vertex. Aborting." << SLogger::endmsg;
		return;
	}
	
	// b-tag veto
	bool bTagVeto = false;
	std::vector<myobject> jet = m->RecPFJetsAK5;
	for (uint i = 0; i < jet.size() && !bTagVeto; i++) {
		double jetPt = jet[i].pt;
		double jetEta = jet[i].eta;
		double jetPhi = jet[i].phi;
		double bTag = jet[i].bDiscriminatiors_CSV;
		if(jetPt > 20 && fabs(jetEta) < 2.4 && bTag > bTagValue){
			double dR1,dR2,dR3,dR4;
			dR1=deltaR(jetEta,jetPhi,Zcand[0].eta,Zcand[0].phi);
			dR2=deltaR(jetEta,jetPhi,Zcand[1].eta,Zcand[1].phi);
			dR3=deltaR(jetEta,jetPhi,Hcand[0].eta,Hcand[0].phi);
			dR4=deltaR(jetEta,jetPhi,Hcand[1].eta,Hcand[1].phi);
			if(dR1>0.4 && dR2>0.4 && dR3>0.4 && dR4>0.4 ) bTagVeto = true;			
		}
	}
	if(bTagVeto)
	{
		m_logger << INFO << "B-jet present. Aborting." << SLogger::endmsg;
		return;
	}
	

short event_type = 0;

	if(Zmumu)
	{
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
 
 Hist( "h_event_type" )->Fill(event_type);
 
 
   return;

}

