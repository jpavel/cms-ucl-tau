// $Id: CycleCreators.py 173 2010-05-12 15:49:33Z krasznaa $

// Local include(s):
#include "../include/Analysis.h"
#include <iostream>
#include <fstream>
#include <string>

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
	
    h_el_n              = Book(TH1D("el_n","el_n",50,0,50));
    h_el_cut            = Book(TH1D("el_cit","el_cut",50,0,50));
    h_event_type        = Book(TH1D("h_event_type","Event Type",8,0.5,8.5));

    //Z->mumu    
    h_mu1Z_pt           = Book(TH1D("h_mu1Z_pt","muon1_Pt",300,0,300));
    h_mu2Z_pt           = Book(TH1D("h_mu2Z_pt","muon2_Pt",300,0,300));
    h_Zmass_mumu        = Book(TH1D("h_Zmass_mumu","Zmumu_mass",60,60,120));
    h_Zpt_mumu          = Book(TH1D("h_Zpt_mumu","Zmumu_pt",300,0,300));
    //Z->ee    
    h_ele1Z_pt          = Book(TH1D("h_ele1Z_pt","ele1_Pt",300,0,300));
    h_ele2Z_pt          = Book(TH1D("h_ele2Z_pt","ele2_Pt",300,0,300));
    h_Zmass_ee          = Book(TH1D("h_Zmass_ee","Zee_mass",60,60,120));
    h_Zpt_ee            = Book(TH1D("h_Zpt_ee","Zee_pt",300,0,300));
    //Z
    h_Zmass             = Book(TH1D("h_Zmass","Z_mass",60,60,120));
    h_Zpt               = Book(TH1D("h_Zpt","Z_pt",300,0,300));

    //H->eTau
    h_eH_eTau_pt        = Book(TH1D("h_eH_eTau_pt","H->e tau, ele pt",100,0,300));
    h_tauH_eTau_pt      = Book(TH1D("h_tauH_eTau_pt","H->e tau, tau pt",100,0,300));
    h_H_eTau_pt         = Book(TH1D("h_H_eTau_pt","H->e tau, H pt",100,0,300));
    h_H_eTau_mass       = Book(TH1D("h_H_eTau_mass","H->e tau, H visible mass",100,0,300));
    //H->muTau
    h_muH_muTau_pt      = Book(TH1D("h_muH_muTau_pt","H->mu tau, mu pt",100,0,300));
    h_tauH_muTau_pt     = Book(TH1D("h_tauH_muTau_pt","H->mu tau, tau pt",100,0,300));
    h_H_muTau_pt        = Book(TH1D("h_H_muTau_pt","H->mu tau, H pt",100,0,300));
    h_H_muTau_mass      = Book(TH1D("h_H_muTau_mass","H->mu tau, H visible mass",100,0,300));
    //H->muE relIso(mu)<0.15
    h_muH_muE_tightMuIso_pt        = Book(TH1D("h_muH_muE_tightMuIso_pt","H->mu e, mu pt",100,0,300));
    h_eH_muE_tightMuIso_pt         = Book(TH1D("h_eH_muE_tightMuIso_pt","H->mu e, e pt",100,0,300));
    h_H_muE_tightMuIso_pt          = Book(TH1D("h_H_muE_tightMuIso_pt","H->mu e, H pt",100,0,300));
    h_H_muE_tightMuIso_mass        = Book(TH1D("h_H_muE_tightMuIso_mass","H->mu e, H visible mass",100,0,300));
    //H->muE relIso(mu)<0.25
    h_muH_muE_looseMuIso_pt        = Book(TH1D("h_muH_muE_looseMuIso_pt","H->mu e, mu pt",100,0,300));
    h_eH_muE_looseMuIso_pt         = Book(TH1D("h_eH_muE_looseMuIso_pt","H->mu e, e pt",100,0,300));
    h_H_muE_looseMuIso_pt          = Book(TH1D("h_H_muE_looseMuIso_pt","H->mu e, H pt",100,0,300));
    h_H_muE_looseMuIso_mass        = Book(TH1D("h_H_muE_looseMuIso_mass","H->mu e, H visible mass",100,0,300));
    //H->tauTau
    h_tau1H_tauTau_pt   = Book(TH1D("h_tau1H_tauTau_pt","H->tau tau, tau1 pt",100,0,300));
    h_tau2H_tauTau_pt   = Book(TH1D("h_tau2H_tauTau_pt","H->tau tau, tau2 pt",100,0,300));
    h_H_tauTau_pt       = Book(TH1D("h_H_tauTau_pt","H->tau tau, H pt",100,0,300));
    h_H_tauTau_mass    = Book(TH1D("h_H_tauTau_mass","H->tau tau, H visible mass",100,0,300));
    //Higgs
    h_H_pt           = Book(TH1D("h_H_pt","H pt (all final states)",100,0,300));
    h_H_mass         = Book(TH1D("h_H_mass","H mass (all final states)",100,0,300));
    
    // lepton histograms
    h_n_goodEl		= Book(TH1D("h_n_goodEl","Number of good electrons; good electrons",10,-0.5,9.5));
    h_n_goodMu		= Book(TH1D("h_n_goodMu","Number of good muons; good muons",10,-0.5,9.5));

    h_el_relIso		= Book(TH1D("h_el_relIso","Relative electron isolation; relIso(el)",100,0.0,1.0));
    h_mu_relIso		= Book(TH1D("h_mu_relIso","Relative muon isolation; relIso(mu)",100,0.0,1.0));
   
    h_n_goodEl_Hcand		= Book(TH1D("h_n_goodEl_Hcand","Number of good electrons; good electrons",10,-0.5,9.5));
    h_n_goodMu_Hcand		= Book(TH1D("h_n_goodMu_Hcand","Number of good muons; good muons",10,-0.5,9.5));
    h_n_goodTau_Hcand		= Book(TH1D("h_n_goodTau_Hcand","Number of good taus; good taus",10,-0.5,9.5));
    
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
	 
	 
	 
	 // input text file
	 
    //~ evt_index.clear();
	//~ mass_vector.clear();
	
	index_number.clear();
	evt_number.clear();
	run_number.clear();
	lumi_number.clear();
	evt_type.clear();
	mass_Z.clear();
	mass_H.clear();
	
	 
	 std::ifstream myfile;
	 std::string line;
     myfile.open ("zh_sync.txt");
	 if (myfile.is_open())
	 {	
	    
	    while ( myfile.good() )
	    {
	      std::vector<int> tmp_index;
	      std::vector<double> tmp_mass;
	      tmp_index.clear();
	      int i_number;
		  double number;
		
	      myfile >> i_number;
		  index_number.push_back(i_number);
		  myfile >> i_number;
		  evt_type.push_back(i_number);      
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
		
	    }
	    myfile.close();
	  }
	 index_number.pop_back();
	evt_number.pop_back();
	run_number.pop_back();
	lumi_number.pop_back();
	evt_type.pop_back();
	mass_Z.pop_back();
	mass_H.pop_back();
	  std::cout << index_number.size() << " " << evt_number.size() << " " << run_number.size() << " " << lumi_number.size() << " " << evt_type.size() << 
	  " " << mass_Z.size() << " " << mass_H.size() << std::endl;
	  for (uint i =0; i < index_number.size(); i++)
	  {
		 std::cout << index_number[i] << " " << evt_type[i] << " " << run_number[i] << " " << lumi_number[i] << " " << evt_number[i] << 
	  " " << mass_Z[i] << " " << mass_H[i] << std::endl;		
	  }
	  
	  compared=0;
	  entries=0;
	
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

bool Analysis::Trg_MC_12(myevent* m) {
    map<string, int> myHLT = m->HLT;
    bool Trigger = false;
    bool TriggerEle = false;
    bool TriggerMu = false;

    string doubEle = "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v15";
    string doubMu = "HLT_Mu17_Mu8_v16";
    string doubMu2 = "HLT_Mu17_TkMu8_v9";

    for (map<string, int> ::iterator ihlt = myHLT.begin(); ihlt != myHLT.end(); ihlt++) {
         if (ihlt->first == doubEle)
             TriggerEle = ihlt->second;
         if (ihlt->first == doubMu || ihlt->first == doubMu2)
             TriggerMu = ihlt->second;
		}
        Trigger = TriggerEle || TriggerMu;
    return Trigger;    
	}
	
void Analysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
	entries++;
	bool found_event = false;
    m_logger << DEBUG << " Now executing event " << m->eventNumber << " in a run " << m->runNumber << SLogger::endmsg;
	
	int eNumber = m->eventNumber;
	
	uint pos = std::find(evt_number.begin(), evt_number.end(), eNumber) - evt_number.begin();
	if( pos < evt_number.size())
	{
		found_event = true;
		compared++;		
	}
	
	bool trigPass = Trg_MC_12(m);
    m_logger << DEBUG << " Trigger decision " << trigPass << SLogger::endmsg;
    if(!trigPass)
    {
		if(found_event) m_logger << ERROR << " WRONG TRIGGER" << SLogger::endmsg;
	//	return;
	}
	
    std::vector<myobject> goodMuon;
    goodMuon.clear();

    std::vector<myobject> muon = m->PreSelectedMuons;
    m_logger << VERBOSE << " There are " << muon.size() << " preselected muons " << SLogger::endmsg;

     for (uint i = 0; i < muon.size(); i++) {

		double muPt = muon[i].pt;
		double muEta = muon[i].eta;
		bool muGlobal = muon[i].isGlobalMuon;
		bool muTracker = muon[i].isTrackerMuon;
		double relIso = RelIsoMu(muon[i]);
		
		bool pfID = PFMuonID(muon[i]);	

		if (muGlobal && muTracker && muPt > 10. && fabs(muEta) < 2.4 && relIso < 0.4 && pfID)
		{
					goodMuon.push_back(muon[i]);
					Hist("h_mu_relIso")->Fill(relIso);
		}
    }
	m_logger << VERBOSE << " There are " << goodMuon.size() << " good muons " << SLogger::endmsg;
	Hist("h_n_goodMu")->Fill(goodMuon.size());
        
        std::vector<myobject> goodElectron;
        goodElectron.clear();
        std::vector<myobject> electron = m->PreSelectedElectrons;
        m_logger << VERBOSE << " There are " << electron.size() << " preselected electrons " << SLogger::endmsg;

     for (uint i = 0; i < electron.size(); i++) {

		double elPt = electron[i].pt;
		double elEta = electron[i].eta;
		int missingHits = electron[i].numLostHitEleInner;
		bool elID = EleMVANonTrigId(elPt,elEta,electron[i].Id_mvaNonTrg);
		double relIso = RelIsoEl(electron[i]);
		
		if (elPt > 10. && fabs(elEta) < 2.5 && missingHits <= 1 && relIso < 0.4 && elID)
		{
			goodElectron.push_back(electron[i]);
			Hist("h_el_relIso")->Fill(relIso);
		}
    }
	m_logger << VERBOSE << " There are " << goodElectron.size() << " good electrons " << SLogger::endmsg;
	int muCandZ = goodMuon.size();
	int elCandZ = goodElectron.size();
	Hist("h_n_goodEl")->Fill(goodElectron.size());
	// Z compatibility
	std::vector<myobject> Zcand;
	Zcand.clear();
	bool Zmumu = false;
	bool Zee = false;
	double dMass=999.0;
        int Zindex[2] = {-1,-1};
	for(uint i = 0; i < goodMuon.size(); i++)
	{
		m_logger << VERBOSE << "  ->good muon no. "<< i << " has pt "<<  goodMuon[i].pt << " and charge " << goodMuon[i].charge << SLogger::endmsg;
		if(goodMuon[i].pt < 20. || Zmumu) continue;
		if(RelIsoMu(goodMuon[i]) > 0.25) continue;
		for(uint j = i+1; j < goodMuon.size() && !Zmumu; j++)
		{
			m_logger << VERBOSE << "  -->second muon no. "<< j << " has pt "<<  goodMuon[j].pt << " and charge " << goodMuon[j].charge << SLogger::endmsg;
			
			if(RelIsoMu(goodMuon[j]) > 0.25) continue;
			if(goodMuon[i].charge*goodMuon[j].charge >=0.) continue;
			if(deltaR(goodMuon[i].eta,goodMuon[i].phi,goodMuon[j].eta,goodMuon[j].phi)< 0.3) continue;
			
			TLorentzVector cand;
			cand.SetPxPyPzE(goodMuon[i].px+goodMuon[j].px,
								goodMuon[i].py+goodMuon[j].py,
								goodMuon[i].pz+goodMuon[j].pz,
								goodMuon[i].E+goodMuon[j].E);
			double mass = cand.M();
			m_logger << VERBOSE << "  -->Candidate mass is " << mass << SLogger::endmsg;
                        if(mass > 71.2 && mass < 111.2){
                            Zmumu=true;
                            double dM = 999.;
                            if(BestMassForZ > 0.0){
                                Zmumu=false;
                                dM=fabs(mass-BestMassForZ);
                                //std::cout<<"mass: "<<mass<<"dM: "<<dM<<std::endl;        
                                if(dM < dMass){
						Zindex[0]=i;
						Zindex[1]=j;
                                                dMass=dM;
                                //std::cout<<"mass: "<<mass<<"dMass: "<<dM<<std::endl;        
                                        }
                        }else{
                            Zindex[0]=i;
                            Zindex[1]=j;
                                }
                        }
                 }
        }
			if(Zindex[0] > -1 && Zindex[1] > -1){
                                TLorentzVector muon1;
                                TLorentzVector muon2;
                                TLorentzVector Zmumu_;
				int i = Zindex[0];
				int j = Zindex[1];
				Zcand.push_back(goodMuon[i]);
				Zcand.push_back(goodMuon[j]);
                                muon1.SetPxPyPzE(goodMuon[i].px,goodMuon[i].py,goodMuon[i].pz,goodMuon[i].E);        
                                muon2.SetPxPyPzE(goodMuon[j].px,goodMuon[j].py,goodMuon[j].pz,goodMuon[j].E);        
                                Zmumu_=muon1+muon2;        
				goodMuon.erase(goodMuon.begin()+i);
				goodMuon.erase(goodMuon.begin()+j-1);
				Zmumu=true;
                                        Hist( "h_mu1Z_pt" )->Fill(muon1.Pt());
                                        Hist( "h_mu2Z_pt" )->Fill(muon2.Pt());
                                        Hist( "h_Zmass_mumu" )->Fill(Zmumu_.M());
                                        Hist( "h_Zpt_mumu" )->Fill(Zmumu_.Pt());
                                        Hist( "h_Zmass" )->Fill(Zmumu_.M());
                                        Hist( "h_Zpt" )->Fill(Zmumu_.Pt());
			}


 m_logger << VERBOSE << " There are " << goodMuon.size() << " remaining good muons " << SLogger::endmsg;
	
	if(!Zmumu)
	{
		dMass = 999.;
		for(uint i = 0; i < goodElectron.size(); i++)
		{
			m_logger << VERBOSE << " ->good electron no. "<< i << " has pt "<<  goodElectron[i].pt << " and charge " << goodElectron[i].charge << SLogger::endmsg;
			if( goodElectron[i].pt < 20 || Zee) continue;
			if( RelIsoEl(goodElectron[i]) > 0.25) continue;
			for(uint j = i+1; j < goodElectron.size() && !Zee; j++)
			{
				m_logger << VERBOSE << "  -->second electron no. "<< j << " has pt "<<  goodElectron[j].pt << " and charge " << goodElectron[j].charge << SLogger::endmsg;
				if( RelIsoEl(goodElectron[j]) > 0.25) continue;	
				if(goodElectron[i].charge*goodElectron[j].charge >=0.) continue;
				if(deltaR(goodElectron[i].eta,goodElectron[i].phi,goodElectron[j].eta,goodElectron[j].phi)< 0.3) continue;
			
				TLorentzVector cand;
				cand.SetPxPyPzE(goodElectron[i].px+goodElectron[j].px,
									goodElectron[i].py+goodElectron[j].py,
									goodElectron[i].pz+goodElectron[j].pz,
									goodElectron[i].E+goodElectron[j].E);
				double mass = cand.M();
				m_logger << VERBOSE << "  -->Candidate mass is " << mass << SLogger::endmsg;
				if(mass > 71.2 && mass < 111.2){ 
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
                                    TLorentzVector ele1;
                                    TLorentzVector ele2;
                                    TLorentzVector Zee_;
					int i = Zindex[0];
					int j = Zindex[1];
                                        ele1.SetPxPyPzE(goodElectron[i].px,goodElectron[i].py,goodElectron[i].pz,goodElectron[i].E);        
                                        ele2.SetPxPyPzE(goodElectron[j].px,goodElectron[j].py,goodElectron[j].pz,goodElectron[j].E);        
                                        Zee_=ele1+ele2;        
					Zcand.push_back(goodElectron[i]);
					Zcand.push_back(goodElectron[j]);	
					goodElectron.erase(goodElectron.begin()+i);
					goodElectron.erase(goodElectron.begin()+j-1);
					Zee=true;
                                        Hist( "h_ele1Z_pt" )->Fill(ele1.Pt());
                                        Hist( "h_ele2Z_pt" )->Fill(ele2.Pt());
                                        Hist( "h_Zmass_ee" )->Fill(Zee_.M());
                                        Hist( "h_Zpt_ee" )->Fill(Zee_.Pt());
                                        Hist( "h_Zmass" )->Fill(Zee_.M());
                                        Hist( "h_Zpt" )->Fill(Zee_.Pt());
			}
	}
	
	m_logger << VERBOSE << " There are " << goodElectron.size() << " remaining good electrons " << SLogger::endmsg;
	
	if(Zmumu||Zee)
		m_logger << DEBUG << " There is a Z candidate! " << SLogger::endmsg;
	else{
		if(found_event) std::cout << "WRONG!" <<std::endl;
			return;
	
	}
	
    	
	// Z overlap removal
	
	for(int i = 0; i < goodMuon.size(); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			if(deltaR(goodMuon[i].eta,goodMuon[i].phi,Zcand[j].eta,Zcand[j].phi)< 0.3) 
			{	goodMuon.erase(goodMuon.begin()+i); i--;removed = true;}
		}
	}
	Hist("h_n_goodMu_Hcand")->Fill(goodMuon.size());
	
	for(int i = 0; i < goodElectron.size(); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			if(deltaR(goodElectron[i].eta,goodElectron[i].phi,Zcand[j].eta,Zcand[j].phi)< 0.3) 
			{	goodElectron.erase(goodElectron.begin()+i); i--; removed = true;}
		}
		
		for(uint j = 0; j < goodMuon.size() && !removed; j++)
		{
			if(deltaR(goodElectron[i].eta,goodElectron[i].phi,goodMuon[j].eta,goodMuon[j].phi)< 0.3) 
			{	goodElectron.erase(goodElectron.begin()+i); i--; removed = true;}
		}
		
	}
	m_logger << DEBUG << " There are " << goodMuon.size() << " and " << goodElectron.size() << " remaining after Z overlap removal " << SLogger::endmsg;
	Hist("h_n_goodEl_Hcand")->Fill(goodElectron.size());	
	    // checking the rest of the event
		// list of good taus 
		std::vector<myobject> goodTau;
		goodTau.clear();
    	int muCand = goodMuon.size();
	int elCand = goodElectron.size();

    
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
    
    for(int i = 0; i < goodTau.size(); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			
			if(deltaR(goodTau[i].eta,goodTau[i].phi,Zcand[j].eta,Zcand[j].phi)< 0.3) 
			{	goodTau.erase(goodTau.begin()+i); i--; removed = true;}
			
		}
		
		for(uint j = 0; j < goodMuon.size() && !removed; j++)
		{
			
			if(deltaR(goodTau[i].eta,goodTau[i].phi,goodMuon[j].eta,goodMuon[j].phi)< 0.3) 
			{	goodTau.erase(goodTau.begin()+i); i--; removed = true;}
			
		}
		
		for(uint j = 0; j < goodElectron.size() && !removed; j++)
		{
			
			if(deltaR(goodTau[i].eta,goodTau[i].phi,goodElectron[j].eta,goodElectron[j].phi)< 0.3) 
			{	goodTau.erase(goodTau.begin()+i); i--; removed = true;}
			
			
		}
		
		
	}
     int tauCand = 	goodTau.size();
   
	m_logger << DEBUG << " There are " << goodTau.size() << " good taus " << SLogger::endmsg;	
	Hist("h_n_goodTau_Hcand")->Fill(goodTau.size());	
	
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
                            if(relIso > 0.25) continue;    
                            if(relIso < 0.15)
                            {
                                m_logger << DEBUG << " Checking for muE with very isolated muon" << SLogger::endmsg;   
                                for(uint j=0; j< goodElectron.size() && !muE; j++)
                                {
                                    double relIsoEl = RelIsoEl(goodElectron[j]);
                                    if(relIsoEl > 0.25) continue;
                                    if(goodMuon[i].charge*goodElectron[j].charge >=0) continue;
                                    if(deltaR(goodElectron[j].eta,goodElectron[j].phi,goodMuon[i].eta,goodMuon[i].phi)< 0.3) continue;
                                    muE=true;
                                    Hcand.push_back(goodMuon[i]);
                                    Hcand.push_back(goodElectron[j]);
                                    goodMuon.erase(goodMuon.begin()+i);
                                    goodElectron.erase(goodElectron.begin()+j);
                                    TLorentzVector muH_muE_tightMuIso,eH_muE_tightMuIso,H_muE_tightMuIso;
                                    muH_muE_tightMuIso.SetPxPyPzE(goodMuon[i].px,goodMuon[i].py,goodMuon[i].pz,goodMuon[i].E);
                                    eH_muE_tightMuIso.SetPxPyPzE(goodElectron[j].px,goodElectron[j].py,goodElectron[j].pz,goodElectron[j].E);
                                    H_muE_tightMuIso = muH_muE_tightMuIso+eH_muE_tightMuIso;
                                    Hist( "h_muH_muE_tightMuIso_pt" )->Fill(muH_muE_tightMuIso.Pt());
                                    Hist( "h_eH_muE_tightMuIso_pt" )->Fill(eH_muE_tightMuIso.Pt());
                                    Hist( "h_H_muE_tightMuIso_pt" )->Fill(H_muE_tightMuIso.Pt());
                                    Hist( "h_H_muE_tightMuIso_mass" )->Fill(H_muE_tightMuIso.M());
                                    Hist( "h_H_pt" )->Fill(H_muE_tightMuIso.Pt());
                                    Hist( "h_H_mass" )->Fill(H_muE_tightMuIso.M());

                                }

                                m_logger << DEBUG << " Checking for muTau " << SLogger::endmsg;
                                for(uint j=0; j< goodTau.size() && !muTau && !muE; j++)
                                {
                                    if(goodMuon[i].charge*goodTau[j].charge >=0) continue;
                                    if(goodTau[j].discriminationByMuonTight <=0.5) continue;
                                    if(deltaR(goodTau[j].eta,goodTau[j].phi,goodMuon[i].eta,goodMuon[i].phi)< 0.3) continue;
                                    muTau=true;
                                    Hcand.push_back(goodMuon[i]);
                                    Hcand.push_back(goodTau[j]);

                                    TLorentzVector muH_muTau,tauH_muTau,H_muTau;
                                    muH_muTau.SetPxPyPzE(goodMuon[i].px,goodMuon[i].py,goodMuon[i].pz,goodMuon[i].E);
                                    tauH_muTau.SetPxPyPzE(goodTau[j].px,goodTau[j].py,goodTau[j].pz,goodTau[j].E);
                                    H_muTau = muH_muTau+tauH_muTau;
                                    Hist( "h_muH_muTau_pt" )->Fill(muH_muTau.Pt());
                                    Hist( "h_tauH_muTau_pt" )->Fill(tauH_muTau.Pt());
                                    Hist( "h_H_muTau_pt" )->Fill(H_muTau.Pt());
                                    Hist( "h_H_muTau_mass" )->Fill(H_muTau.M());
                                    Hist( "h_H_pt" )->Fill(H_muTau.Pt());
                                    Hist( "h_H_mass" )->Fill(H_muTau.M());

                                    goodMuon.erase(goodMuon.begin()+i);
                                    goodTau.erase(goodTau.begin()+j);

                                }
                            }else {//muE candidate
                                m_logger << DEBUG << " Checking for muE " << SLogger::endmsg;   
                                for(uint j=0; j< goodElectron.size() && !muE; j++)
                                {
                                    double relIsoEl = RelIsoEl(goodElectron[j]);
                                    if(relIsoEl > 0.25) continue;
                                    
                                    if(goodMuon[i].charge*goodElectron[j].charge >=0) continue;
                                    if(deltaR(goodElectron[j].eta,goodElectron[j].phi,goodMuon[i].eta,goodMuon[i].phi)< 0.3) continue;
                                    muE=true;
                                    Hcand.push_back(goodMuon[i]);
                                    Hcand.push_back(goodElectron[j]);

                                    TLorentzVector muH_muE_looseMuIso,eH_muE_looseMuIso,H_muE_looseMuIso;
                                    muH_muE_looseMuIso.SetPxPyPzE(goodMuon[i].px,goodMuon[i].py,goodMuon[i].pz,goodMuon[i].E);
                                    eH_muE_looseMuIso.SetPxPyPzE(goodElectron[j].px,goodElectron[j].py,goodElectron[j].pz,goodElectron[j].E);
                                    H_muE_looseMuIso = muH_muE_looseMuIso+eH_muE_looseMuIso;
                                    Hist( "h_muH_muE_looseMuIso_pt" )->Fill(muH_muE_looseMuIso.Pt());
                                    Hist( "h_eH_muE_looseMuIso_pt" )->Fill(eH_muE_looseMuIso.Pt());
                                    Hist( "h_H_muE_looseMuIso_pt" )->Fill(H_muE_looseMuIso.Pt());
                                    Hist( "h_H_muE_looseMuIso_mass" )->Fill(H_muE_looseMuIso.M());
                                    Hist( "h_H_pt" )->Fill(H_muE_looseMuIso.Pt());
                                    Hist( "h_H_mass" )->Fill(H_muE_looseMuIso.M());

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

                            double relIso = RelIsoEl(goodElectron[i]);
                            if (relIso > 0.25) continue;
                            if(relIso < 0.10 && goodElectron[i].numLostHitEleInner < 1)
                            {
                                m_logger << DEBUG << " Checking for eTau " << SLogger::endmsg;	
                                for(uint j=0; j< goodTau.size() && !eTau; j++)
                                {
                                    if(goodElectron[i].charge*goodTau[j].charge >=0) continue;
                                    if(goodTau[j].discriminationByElectronMVA <=0.5) continue;
                                    if(deltaR(goodTau[j].eta,goodTau[j].phi,goodElectron[i].eta,goodElectron[i].phi)< 0.3) continue;
						eTau=true;
						Hcand.push_back(goodElectron[i]);
						Hcand.push_back(goodTau[j]);

                                                TLorentzVector eH_eTau,tauH_eTau,H_eTau;
                                                eH_eTau.SetPxPyPzE(goodElectron[i].px,goodElectron[i].py,goodElectron[i].pz,goodElectron[i].E);
                                                tauH_eTau.SetPxPyPzE(goodTau[j].px,goodTau[j].py,goodTau[j].pz,goodTau[j].E);
                                                H_eTau = eH_eTau+tauH_eTau;
                                                Hist( "h_eH_eTau_pt" )->Fill(eH_eTau.Pt());
                                                Hist( "h_tauH_eTau_pt" )->Fill(tauH_eTau.Pt());
                                                Hist( "h_H_eTau_pt" )->Fill(H_eTau.Pt());
                                                Hist( "h_H_eTau_mass" )->Fill(H_eTau.M());
                                                Hist( "h_H_pt" )->Fill(H_eTau.Pt());
                                                Hist( "h_H_mass" )->Fill(H_eTau.M());
						
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
						if(deltaR(goodTau[j].eta,goodTau[j].phi,goodTau[i].eta,goodTau[i].phi)< 0.3) continue;
						tauTau=true;
						Hcand.push_back(goodTau[i]);
						Hcand.push_back(goodTau[j]);

                                                TLorentzVector tau1H_tauTau,tau2H_tauTau,H_tauTau;
                                                tau1H_tauTau.SetPxPyPzE(goodTau[i].px,goodTau[i].py,goodTau[i].pz,goodTau[i].E);
                                                tau2H_tauTau.SetPxPyPzE(goodTau[j].px,goodTau[j].py,goodTau[j].pz,goodTau[j].E);
                                                H_tauTau = tau1H_tauTau+tau2H_tauTau;
                                                Hist( "h_tau1H_tauTau_pt" )->Fill(tau1H_tauTau.Pt());
                                                Hist( "h_tau2H_tauTau_pt" )->Fill(tau2H_tauTau.Pt());
                                                Hist( "h_H_tauTau_pt" )->Fill(H_tauTau.Pt());
                                                Hist( "h_H_tauTau_mass" )->Fill(H_tauTau.M());
                                                Hist( "h_H_pt" )->Fill(H_tauTau.Pt());
                                                Hist( "h_H_mass" )->Fill(H_tauTau.M());
						
                                                goodTau.erase(goodTau.begin()+i);
                                                goodTau.erase(goodTau.begin()+j-1);
					}
				
			}
		}
		
		if(Hcand.size()==0 || (!muTau && !muE && !eTau && !tauTau)){ m_logger << DEBUG << " No Higgs candidate. Going to next event" << SLogger::endmsg; 
			if( found_event){
				 m_logger << ERROR << " MISSED H cand of type " << evt_type[pos] << " and mass " << mass_H[pos] << SLogger::endmsg;
				 m_logger << ERROR << " Remaining mu, tau, el " << goodMuon.size() << " " << goodTau.size() << " " << goodElectron.size()
				 << " out of " << muCand << " " << tauCand << " " << elCand << " out of "
				 << muCandZ <<  " " << elCandZ << SLogger::endmsg;
				 if(evt_type[pos]==7)
				 {
					 TLorentzVector eH_eTau,tauH_eTau,H_eTau;
                                                eH_eTau.SetPxPyPzE(goodElectron[0].px,goodElectron[0].py,goodElectron[0].pz,goodElectron[0].E);
                                                tauH_eTau.SetPxPyPzE(goodTau[0].px,goodTau[0].py,goodTau[0].pz,goodTau[0].E);
                                                H_eTau = eH_eTau+tauH_eTau;
					m_logger << WARNING << " My mass " << H_eTau.M() << SLogger::endmsg;
					m_logger << WARNING << "Z is made from " << Zindex[0] << " and " << Zindex[1] << SLogger::endmsg;
					for(uint i = 0; i < electron.size() && !eTau ; i++)
                        {
						
                            double relIso = RelIsoEl(electron[i]);
                            m_logger << WARNING << " good el. no " << i << " relIso " << relIso << " hits " << electron[i].numLostHitEleInner << 
                            " charge " << electron[i].charge << SLogger::endmsg;
                            if (relIso > 0.25){m_logger << WARNING << " rej iso"  << SLogger::endmsg; continue;}
                            if(relIso < 0.10 && electron[i].numLostHitEleInner < 1)
                            {
                                m_logger << WARNING << " Checking for eTau " << SLogger::endmsg;	
                                for(uint j=0; j< goodTau.size() && !muTau; j++)
                                {
                                     m_logger << WARNING << " good tau no. " << j << " MVA " << goodTau[j].discriminationByElectronMVA << " hits " << 
                            " charge " << goodTau[i].charge << " delta R " <<
                            deltaR(goodTau[j].eta,goodTau[j].phi,electron[i].eta,electron[i].phi) << SLogger::endmsg;
                            TLorentzVector eH,tauH,H_m;
                                                eH.SetPxPyPzE(electron[i].px,electron[i].py,electron[i].pz,electron[i].E);
                                                tauH.SetPxPyPzE(goodTau[j].px,goodTau[j].py,goodTau[j].pz,goodTau[j].E);
                                                H_m = eH+tauH;
								m_logger << WARNING << " My mass " << H_m.M() << SLogger::endmsg;
                                    if(electron[i].charge*goodTau[j].charge >=0) continue;
                                    if(goodTau[j].discriminationByElectronMVA <=0.5) continue;
                                    if(deltaR(goodTau[j].eta,goodTau[j].phi,electron[i].eta,electron[i].phi)< 0.3) continue;
									eTau=true;
								}
							}
						}
				 
				 
				 }
				 
			 }
		return;
		}
		else m_logger << INFO << "Higgs candidate. Size is " << Hcand.size() << SLogger::endmsg;
		// cross-check
		if(muTau+muE+eTau+tauTau > 1){
			 m_logger << ERROR << "Non-exclusive event type!! Aborting." << SLogger::endmsg;
			 if( found_event) m_logger << ERROR << " H cand of type " << evt_type[pos] << SLogger::endmsg;
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
		 
		 // overlap cleaning
			
		bool Ad_lepton = false;	
		 for(uint i = 0; i < goodMuon.size(); i++)
				{
					  if(deltaR(goodMuon[i].eta,goodMuon[i].phi,Hcand[0].eta,Hcand[0].phi)> 0.3 &&
					  deltaR(goodMuon[i].eta,goodMuon[i].phi,Hcand[1].eta,Hcand[1].phi)> 0.3) 
						Ad_lepton=true;
					
				}
				
		 for(uint i = 0; i < goodElectron.size(); i++)
				{
						if(deltaR(goodElectron[i].eta,goodElectron[i].phi,Hcand[0].eta,Hcand[0].phi)> 0.3 &&
						deltaR(goodElectron[i].eta,goodElectron[i].phi,Hcand[1].eta,Hcand[1].phi)> 0.3)  
						Ad_lepton=true;
					
				}
				
		for(uint i = 0; i < goodTau.size(); i++)
				{
					if(deltaR(goodTau[i].eta,goodTau[i].phi,Hcand[0].eta,Hcand[0].phi)> 0.3 &&
						deltaR(goodTau[i].eta,goodTau[i].phi,Hcand[1].eta,Hcand[1].phi)> 0.3)  
						Ad_lepton=true;
				}
		
		
		 
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
				
				
				 std::cout << "-->Additional tau pt " << goodTau[0].pt << " eta " << goodTau[0].eta << " phi " << goodTau[0].phi <<
				  " AgainstElectronLoose " << LooseElectron  << " AgainstMuonLoose " << LooseMuon << " MediumCombinedIsolation " << CombinedIsolation << 
				  " DecayModeFinding " << DecayMode << std::endl;
				 
			 }
			return;
		 }
		 
	// Same vertex check
	
	bool dZ_expo = (fabs(Zcand[0].z_expo - Zcand[1].z_expo) < dZvertex && fabs(Zcand[0].z_expo - Hcand[0].z_expo) < dZvertex && fabs(Zcand[0].z_expo - Hcand[1].z_expo) < dZvertex);		
	if(!dZ_expo)
	{
		m_logger << INFO << "Not from the same vertex. Aborting." << SLogger::endmsg;
		if( found_event) m_logger << ERROR << " Wrong vertex! H cand of type " << evt_type[pos] << SLogger::endmsg;
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
		if(jetPt > 20. && fabs(jetEta) < 2.4 && bTag > bTagValue){
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
		 if( found_event) m_logger << ERROR << " Wrong b-tag! H cand of type " << evt_type[pos] << SLogger::endmsg;
		return;
	}
	

//        short 
    event_type = 0;

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
 
  if( found_event && event_type!=evt_type[pos]) {
	  m_logger << ERROR << " Wrong event type. His is " << evt_type[pos] << " and mine is " << event_type << SLogger::endmsg;
  }
 if (event_type > 0 && !found_event){
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
 
   return;
   //trigger
    
}

