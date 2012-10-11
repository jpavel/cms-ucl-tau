// $Id: CycleCreators.py 173 2010-05-12 15:49:33Z krasznaa $

// Local include(s):
#include "../include/Analysis.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "Corrector.h"


ClassImp( Analysis );

Analysis::Analysis()
   : SCycleBase() {

   SetLogName( GetName() );
   DeclareProperty("InTreeName",InTreeName);
   DeclareProperty("MyPtCut",Ptcut);
   DeclareProperty("BestMassForZ",BestMassForZ);
   DeclareProperty("dZvertex", dZvertex);
   DeclareProperty("bTagValue",bTagValue);
   
   DeclareProperty("ElectronTriggerName", doubEle);
   DeclareProperty("ElectronTriggerName2", doubEle2);
   
   DeclareProperty("MuonTriggerName1", doubMu);
   DeclareProperty("MuonTriggerName2", doubMu2);
   DeclareProperty("MuonTriggerName3", doubMu3);
   
   DeclareProperty("checkCategories",checkCategories);
   DeclareProperty("isSimulation",isSimulation);
   DeclareProperty("is2011",is2011);
   DeclareProperty("is2012_52",is2012_52);
   DeclareProperty("is2012_53",is2012_53);
   DeclareProperty("vetoMuonTrigger",vetoMuonTrigger);
   DeclareProperty("vetoElectronTrigger", vetoElectronTrigger);
  
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
    
    h_Z_eta				= Book(TH1D("h_Z_eta","H #eta; #eta",100,-3.0,3.0));
	h_Z_phi				= Book(TH1D("h_Z_phi","H #phi; #phi",64,-3.2,3.2));
	
	h_Z_lep1_eta		= Book(TH1D("h_Z_lep1_eta","H #eta; #eta",100,-3.0,3.0));
	h_Z_lep1_phi		= Book(TH1D("h_Z_lep1_phi","H #phi; #phi",64,-3.2,3.2));	
	
	h_Z_lep2_eta		= Book(TH1D("h_Z_lep2_eta","H #eta; #eta",100,-3.0,3.0));
	h_Z_lep2_phi		= Book(TH1D("h_Z_lep2_phi","H #phi; #phi",64,-3.2,3.2));

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
    
    h_H_eta				= Book(TH1D("h_H_eta","H #eta; #eta",100,-3.0,3.0));
	h_H_phi				= Book(TH1D("h_H_phi","H #phi; #phi",64,-3.2,3.2));
	
	h_H_lep1_eta		= Book(TH1D("h_H_lep1_eta","H #eta; #eta",100,-3.0,3.0));
	h_H_lep1_phi		= Book(TH1D("h_H_lep1_phi","H #phi; #phi",64,-3.2,3.2));	
	
	h_H_lep2_eta		= Book(TH1D("h_H_lep2_eta","H #eta; #eta",100,-3.0,3.0));
	h_H_lep2_phi		= Book(TH1D("h_H_lep2_phi","H #phi; #phi",64,-3.2,3.2));

    
    // lepton histograms
    h_n_goodEl		= Book(TH1D("h_n_goodEl","Number of good electrons; good electrons",10,-0.5,9.5));
    h_n_goodMu		= Book(TH1D("h_n_goodMu","Number of good muons; good muons",10,-0.5,9.5));

    h_el_relIso		= Book(TH1D("h_el_relIso","Relative electron isolation; relIso(el)",100,0.0,1.0));
    h_mu_relIso		= Book(TH1D("h_mu_relIso","Relative muon isolation; relIso(mu)",100,0.0,1.0));
   
    h_n_goodEl_Hcand		= Book(TH1D("h_n_goodEl_Hcand","Number of good electrons; good electrons",10,-0.5,9.5));
    h_n_goodMu_Hcand		= Book(TH1D("h_n_goodMu_Hcand","Number of good muons; good muons",10,-0.5,9.5));
    h_n_goodTau_Hcand		= Book(TH1D("h_n_goodTau_Hcand","Number of good taus; good taus",10,-0.5,9.5));
    
    h_PU_weight				= Book(TH1D("h_PU_weight","PU weights distribution",100,0,5));
    h_nPU_raw				= Book(TH1D("h_nPU_raw","raw PU distribution",50,0,50));
    h_nPU_reweight			= Book(TH1D("h_nPU_reweight","reweighted PU distribution",50,0,50));
    
    h_PF_MET				= Book(TH1D("h_PF_MET","PF MET distribution;PF MET[GeV]",100,0,200));
    h_PF_MET_selected		= Book(TH1D("h_PF_MET_selected","PF MET distribution;PF MET[GeV]",100,0,200));
    
    h_PF_MET_nPU			= Book(TProfile("h_PF_MET_nPU", "PF MET vs number of PU interactions; nPU; PF MET[GeV]",60,0,60));
    h_PF_MET_nPU_selected	= Book(TProfile("h_PF_MET_nPU_selected", "PF MET vs number of PU interactions; nPU; PF MET[GeV]",60,0,60));
    h_nbjets_beforeCut                    = Book(TH1D("h_nbjets_beforeCut", "# of b-jets before b-tag veto",10,0,10));
    h_nbjets_afterCut                    = Book(TH1D("h_nbjets_afterCut", "# of b-jets after b-tag veto",10,0,10));
                      
    h_Tmass					= Book(TH1D("h_Tmass","Transverse mass of leading lepton;Transverse mass[GeV]",100,0,200));
    
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
	 
	 h_PF_MET_nPU=Retrieve<TProfile>("h_PF_MET_nPU");
	 h_PF_MET_nPU_selected=Retrieve<TProfile>("h_PF_MET_nPU_selected");
	 
	 
	  h_H_mass_types.clear();
	 for(uint i = 1; i <= h_event_type->GetNbinsX(); i++)
	 {
		std::stringstream s;
		s << "h_H_mass_type_" << i;
		std::string name = s.str(); 
		std::stringstream ss;
		ss <<  h_event_type->GetXaxis()->GetBinLabel(i) << ";m_{H}[GeV]";
		std::string title = ss.str();
		TH1D* h_temp =  Book(TH1D(TString(name),TString(title),300,0.,300.));
		h_H_mass_types.push_back(h_temp);
	 }
	 
	 
	// Lumi weights
	
	if(is2012_52) LumiWeights_ = new reweight::LumiReWeighting("Summer12_PU.root", "dataPileUpHistogram_True_2012.root","mcPU","pileup");
	else if (is2011) LumiWeights_ = new reweight::LumiReWeighting("Fall11_PU_observed.root", "dataPileUpHistogram_Observed_2011.root","mcPU","pileup");
	else LumiWeights_ = new reweight::LumiReWeighting("Summer12_PU_53X.root", "dataPileUpHistogram_True_2012.root","mcPU","pileup");
	
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

    
    for (map<string, int> ::iterator ihlt = myHLT.begin(); ihlt != myHLT.end(); ihlt++) {
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
	
double Analysis::Tmass(myevent *m, myobject mu) {
				
        vector<myobject> Met = m->RecPFMet;
       
        double tMass_v = sqrt(2*mu.pt*Met.front().et*(1-cos(Met.front().phi-mu.phi)));
        return tMass_v;
}
	
void Analysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
	entries++;
	
    m_logger << DEBUG << " Now executing event " << m->eventNumber << " in a run " << m->runNumber << SLogger::endmsg;
	double PUWeight = 1.0;
	double nPU = 0.0;
	if(!is2011)  nPU = m->PUInfo_true;
	else nPU = m->PUInfo_Bunch0;
	if(isSimulation){	
		PUWeight = LumiWeights_->weight( nPU );
	}
	int eNumber = m->eventNumber;
	
	Hist("h_PU_weight")->Fill(PUWeight);
	if(is2011){ 
		Hist("h_nPU_raw")->Fill(m->PUInfo_Bunch0);
		Hist("h_nPU_reweight")->Fill(m->PUInfo_Bunch0,PUWeight);
	}else{
		Hist("h_nPU_raw")->Fill(m->PUInfo_true);
		Hist("h_nPU_reweight")->Fill(m->PUInfo_true,PUWeight);
	}
        
	bool trigPass = Trg_MC_12(m);
    m_logger << DEBUG << " Trigger decision " << trigPass << SLogger::endmsg;
    if(!trigPass)
    {
		return;
	}
	vector<myobject> Met = m->RecPFMet;
	
	Hist("h_PF_MET")->Fill(Met.front().et,PUWeight);
	h_PF_MET_nPU->Fill(nPU,Met.front().et,PUWeight);
	
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
			if (muGlobal && muTracker && muPt > 10. && fabs(muEta) < 2.4 && pfID)
			{
						goodMuon.push_back(muon[i]);
						Hist("h_mu_relIso")->Fill(relIso,PUWeight);
			}
		
    }
	m_logger << VERBOSE << " There are " << goodMuon.size() << " good muons " << SLogger::endmsg;
	Hist("h_n_goodMu")->Fill(goodMuon.size(),PUWeight);
        
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
		
			if (elPt > 10. && fabs(elEta) < 2.5 && missingHits <= 1 && elID)
			{
				goodElectron.push_back(electron[i]);
				Hist("h_el_relIso")->Fill(relIso,PUWeight);
			}
		
		
    }
	m_logger << VERBOSE << " There are " << goodElectron.size() << " good electrons " << SLogger::endmsg;
	int muCandZ = goodMuon.size();
	int elCandZ = goodElectron.size();
	Hist("h_n_goodEl")->Fill(goodElectron.size(),PUWeight);
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
		if(RelIsoMu(goodMuon[i]) > 0.3) continue;
		for(uint j = i+1; j < goodMuon.size() && !Zmumu; j++)
		{
			m_logger << VERBOSE << "  -->second muon no. "<< j << " has pt "<<  goodMuon[j].pt << " and charge " << goodMuon[j].charge << SLogger::endmsg;
			
			if(RelIsoMu(goodMuon[j]) > 0.3) continue;
			if(goodMuon[i].charge*goodMuon[j].charge >=0.) continue;
			if(deltaR(goodMuon[i].eta,goodMuon[i].phi,goodMuon[j].eta,goodMuon[j].phi)< 0.1) continue;
			
			TLorentzVector cand;
			cand.SetPxPyPzE(goodMuon[i].px+goodMuon[j].px,
								goodMuon[i].py+goodMuon[j].py,
								goodMuon[i].pz+goodMuon[j].pz,
								goodMuon[i].E+goodMuon[j].E);
			double mass = cand.M();
			m_logger << VERBOSE << "  -->Candidate mass is " << mass << SLogger::endmsg;
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
				goodMuon.erase(goodMuon.begin()+j-1);
				Zmumu=true;
			}


 m_logger << VERBOSE << " There are " << goodMuon.size() << " remaining good muons " << SLogger::endmsg;
	
	if(!Zmumu)
	{
		dMass = 999.;
		for(uint i = 0; i < goodElectron.size(); i++)
		{
			m_logger << VERBOSE << " ->good electron no. "<< i << " has pt "<<  goodElectron[i].pt << " and charge " << goodElectron[i].charge << SLogger::endmsg;
			if( goodElectron[i].pt < 20 || Zee) continue;
			if( RelIsoEl(goodElectron[i]) > 0.3) continue;
			for(uint j = i+1; j < goodElectron.size() && !Zee; j++)
			{
				m_logger << VERBOSE << "  -->second electron no. "<< j << " has pt "<<  goodElectron[j].pt << " and charge " << goodElectron[j].charge << SLogger::endmsg;
				if( RelIsoEl(goodElectron[j]) > 0.3) continue;	
				if(goodElectron[i].charge*goodElectron[j].charge >=0.) continue;
				if(deltaR(goodElectron[i].eta,goodElectron[i].phi,goodElectron[j].eta,goodElectron[j].phi)< 0.1) continue;
			
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
					goodElectron.erase(goodElectron.begin()+j-1);
					Zee=true;
                                        
			}
	}
	
	
	double corrZlep1,corrZlep2;
	corrZlep1=corrZlep2=1.0;
	double Z_weight = PUWeight;
	if(isSimulation){
		if(Zmumu)
		{
			if(is2012_53){
				 corrZlep1=Cor_ID_Iso_Mu_Loose_2012_53X(Zcand[0]);
				 corrZlep2=Cor_ID_Iso_Mu_Loose_2012_53X(Zcand[1]);
			 }else if(is2012_52){
				  corrZlep1=Cor_ID_Iso_Mu_Loose_2012(Zcand[0]);
				 corrZlep2=Cor_ID_Iso_Mu_Loose_2012(Zcand[1]);
			 }else{
			 	  corrZlep1=Cor_ID_Iso_Mu_Loose_2011(Zcand[0]);
				 corrZlep2=Cor_ID_Iso_Mu_Loose_2011(Zcand[1]);
			 }
			  Z_weight = corrZlep1* corrZlep2;	
		  }else if(Zee){
				if(is2012_53){
				 corrZlep1=Cor_ID_Iso_Ele_Loose_2012_53X(Zcand[0]);
				 corrZlep2=Cor_ID_Iso_Ele_Loose_2012_53X(Zcand[1]);
			 }else if(is2012_52){
				  corrZlep1=Cor_ID_Iso_Ele_Loose_2012(Zcand[0]);
				 corrZlep2=Cor_ID_Iso_Ele_Loose_2012(Zcand[1]);
			 }else{
			 	  corrZlep1=Cor_ID_Iso_Ele_Loose_2011(Zcand[0]);
				 corrZlep2=Cor_ID_Iso_Ele_Loose_2011(Zcand[1]);
			 }
			 Z_weight = corrZlep1* corrZlep2;	
		  }
	  }
			
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
			
			Hist( "h_Z_eta")->Fill(Zee_.Eta(),Z_weight);
			Hist( "h_Z_phi")->Fill(Zee_.Phi(),Z_weight);
			Hist( "h_Z_lep1_eta")->Fill(ele1.Eta(),Z_weight);
			Hist( "h_Z_lep1_phi")->Fill(ele1.Phi(),Z_weight);
			Hist( "h_Z_lep2_eta")->Fill(ele2.Eta(),Z_weight);
			Hist( "h_Z_lep2_phi")->Fill(ele2.Phi(),Z_weight);
		}
	
	
	
	m_logger << VERBOSE << " There are " << goodElectron.size() << " remaining good electrons " << SLogger::endmsg;
	
	if(Zmumu||Zee)
		m_logger << DEBUG << " There is a Z candidate! " << SLogger::endmsg;
	else{
			return;
	}
	
    	
	// Z overlap removal
	
	for(int i = 0; i < goodMuon.size(); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			if(deltaR(goodMuon[i].eta,goodMuon[i].phi,Zcand[j].eta,Zcand[j].phi)< 0.1) 
			{	goodMuon.erase(goodMuon.begin()+i); i--;removed = true;}
		}
	}
	Hist("h_n_goodMu_Hcand")->Fill(goodMuon.size());
	
	for(int i = 0; i < goodElectron.size(); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			if(deltaR(goodElectron[i].eta,goodElectron[i].phi,Zcand[j].eta,Zcand[j].phi)< 0.1) 
			{	goodElectron.erase(goodElectron.begin()+i); i--; removed = true;}
		}
		
		for(uint j = 0; j < goodMuon.size() && !removed; j++)
		{
			if(deltaR(goodElectron[i].eta,goodElectron[i].phi,goodMuon[j].eta,goodMuon[j].phi)< 0.1 && RelIsoMu(goodMuon[j]) < 0.4) 
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
		
		
		if (tauPt > 20 && fabs(tauEta) < 2.3 && LooseElectron && LooseMuon && DecayMode)
				goodTau.push_back(tau[i]);
		
    }
    
    for(int i = 0; i < goodTau.size(); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			
			if(deltaR(goodTau[i].eta,goodTau[i].phi,Zcand[j].eta,Zcand[j].phi)< 0.1) 
			{	goodTau.erase(goodTau.begin()+i); i--; removed = true;}
			
		}
		
		for(uint j = 0; j < goodMuon.size() && !removed; j++)
		{
			
			if(deltaR(goodTau[i].eta,goodTau[i].phi,goodMuon[j].eta,goodMuon[j].phi)< 0.1 && RelIsoMu(goodMuon[j]) < 0.4) 
			{	goodTau.erase(goodTau.begin()+i); i--; removed = true;}
			
		}
		
		for(uint j = 0; j < goodElectron.size() && !removed; j++)
		{
			
			if(deltaR(goodTau[i].eta,goodTau[i].phi,goodElectron[j].eta,goodElectron[j].phi)< 0.1 && RelIsoEl(goodElectron[j]) < 0.4 ) 
			{	goodTau.erase(goodTau.begin()+i); i--; removed = true;}
			
			
		}
		
		
	}
     int tauCand = 	goodTau.size();
   
	m_logger << DEBUG << " There are " << goodTau.size() << " good taus " << SLogger::endmsg;	
	Hist("h_n_goodTau_Hcand")->Fill(goodTau.size());	
	
		// mutau and emu final states
		bool muTau=false;
		bool muE = false;
        bool signal = false;
        short category = -1;       
        int Hindex[2] = {-1,-1};
        std::vector<myobject> Hcand;
        Hcand.clear();
		for(uint i = 0; i < goodMuon.size() && !signal; i++)
		{
				
			double relIso = RelIsoMu(goodMuon[i]);
			bool iso1_muE = (relIso < 0.3);
			bool iso1_muTau = (relIso < 0.15);
			if(!checkCategories && !iso1_muE) continue;
			m_logger << DEBUG << " Checking for muE with very isolated muon" << SLogger::endmsg;   
			for(uint j=0; j< goodElectron.size() && !signal; j++)
			{
				bool iso2 = (RelIsoEl(goodElectron[j]) < 0.3);
				if(goodMuon[i].charge*goodElectron[j].charge >=0) continue;
				if(deltaR(goodElectron[j].eta,goodElectron[j].phi,goodMuon[i].eta,goodMuon[i].phi)< 0.1) continue;
				if (iso1_muE && iso2){ signal = true; muE=true; muTau = false;}
				else if (!iso1_muE && iso2  && category < 1){ category = 2; muE=true; muTau = false;}
				else if ( iso1_muE && !iso2 && category < 1){ category = 1; muE=true; muTau = false;} 
				else if (!iso1_muE && !iso2 && category < 0){ category = 0; muE=true; muTau = false;}
				else continue;
				Hindex[0]=i;
				Hindex[1]=j;
			}
			 
			m_logger << DEBUG << " Checking for muTau " << SLogger::endmsg;
			if(!checkCategories && !iso1_muTau) continue;
			for(uint j=0; j< goodTau.size() && !signal; j++)
			{
				bool iso2 = (goodTau[j].byMediumCombinedIsolationDeltaBetaCorr > 0.5);
				if(goodMuon[i].charge*goodTau[j].charge >=0) continue;
				if(goodTau[j].discriminationByMuonTight <=0.5) continue;
				if(deltaR(goodTau[j].eta,goodTau[j].phi,goodMuon[i].eta,goodMuon[i].phi)< 0.1) continue;                                    
				if (iso1_muTau && iso2){ signal = true; muE=false; muTau=true;}
				else if (!iso1_muTau && iso2  && category < 1){ category = 2; muE=false; muTau=true;}
				else if ( iso1_muTau && !iso2 && category < 1){ category = 1; muE=false; muTau=true;} 
				else if (!iso1_muTau && !iso2 && category < 0){ category = 0; muE=false; muTau=true;}
				else continue;
				Hindex[0]=i;
				Hindex[1]=j;
			}             
		}
			
		if(muTau) m_logger << INFO << " muTau candidate!" << SLogger::endmsg;   
		else if(muE) m_logger << INFO << " muE candidate!" << SLogger::endmsg;                 
		else m_logger << DEBUG << " Checking no-muon channels" << SLogger::endmsg;
		bool eTau = false;
		if(!signal)
		{
			for(uint i = 0; i < goodElectron.size() && !signal ; i++)
			{

				bool iso1 = (RelIsoEl(goodElectron[i]) < 0.1);
				if (!iso1 && !checkCategories) continue;
				if( goodElectron[i].numLostHitEleInner > 0) continue;
					m_logger << DEBUG << " Checking for eTau " << SLogger::endmsg;	
					for(uint j=0; j< goodTau.size() && !signal; j++)
					{
						bool iso2 = (goodTau[j].byMediumCombinedIsolationDeltaBetaCorr > 0.5);
						if(goodElectron[i].charge*goodTau[j].charge >=0) continue;
						if(goodTau[j].discriminationByElectronMVA <=0.5) continue;
						if(deltaR(goodTau[j].eta,goodTau[j].phi,goodElectron[i].eta,goodElectron[i].phi)< 0.1) continue;
						if (iso1 && iso2){ signal = true; muTau=muE=false; eTau=true;}
						else if (!iso1 && iso2  && category < 1){ category = 2; muTau=muE=false; eTau=true;}
						else if (iso1 && !iso2  && category < 1){ category = 1; muTau=muE=false; eTau=true;} 
						else if (!iso1 && !iso2 && category < 0){ category = 0; muTau=muE=false; eTau=true;}
						else continue;
						Hindex[0]=i;
						Hindex[1]=j;
					}
			}
		}

		if(eTau) m_logger << INFO << " eTau candidate!" << SLogger::endmsg;
		else m_logger << DEBUG << " Checking fully hadronic decay" << SLogger::endmsg;
		
		bool tauTau =false;
		if(!signal)
		{
			for(uint i = 0; i < goodTau.size() && !signal ; i++)
			{
				
					if(goodTau[i].discriminationByElectronMedium <=0.5) continue;
					if(goodTau[i].discriminationByMuonMedium <=0.5) continue;
					bool iso1 = (goodTau[i].byTightCombinedIsolationDeltaBetaCorr > 0.5);
					if(!checkCategories && !iso1) continue;
					for(uint j=i+1; j< goodTau.size() && !signal; j++)
					{
						if(goodTau[i].charge*goodTau[j].charge >=0) continue;
						if(goodTau[j].discriminationByElectronMedium <=0.5) continue;
						if(goodTau[j].discriminationByMuonMedium <=0.5) continue;
						bool iso2 = (goodTau[j].byTightCombinedIsolationDeltaBetaCorr > 0.5);
					
						if(deltaR(goodTau[j].eta,goodTau[j].phi,goodTau[i].eta,goodTau[i].phi)< 0.1) continue;
						if (iso1 && iso2){ signal = true; muTau=muE=eTau = false; tauTau=true;}
						else if (!iso1 && iso2  && category < 1){ category = 1; muTau=muE=eTau = false; tauTau=true;}
						else if (iso1 && !iso2  && category < 1){ category = 2; muTau=muE=eTau = false; tauTau=true;} 
						else if (!iso1 && !iso2 && category < 0){ category = 0; muTau=muE=eTau = false; tauTau=true;}
						else continue;
						Hindex[0]=i;
						Hindex[1]=j;
											
					}
				
			}
		}
		
		if(Hindex[0] < 0 || Hindex[1] < 0 ||(!muTau && !muE && !eTau && !tauTau)){ 
			m_logger << DEBUG << " No Higgs candidate. Going to next event" << SLogger::endmsg; 
			return;
		}
		else m_logger << INFO << "Higgs candidate. Size is " << Hcand.size() << SLogger::endmsg;
		// cross-check
		if(muTau+muE+eTau+tauTau > 1){
			 m_logger << ERROR << "Non-exclusive event type!! Aborting." << SLogger::endmsg;
			 m_logger << ERROR << muTau << muE << eTau << tauTau << " " << eNumber << SLogger::endmsg;			 
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
	// efficiency correction;
	int I = Hindex[0]; int J = Hindex[1];		
	switch(event_type)
	{
		case 2:
		case 6:
		        Hcand.push_back(goodMuon[I]);
				Hcand.push_back(goodElectron[J]);
				goodMuon.erase(goodMuon.begin()+I);
				goodElectron.erase(goodElectron.begin()+J);
				break;
		case 1:
		case 5:
		        Hcand.push_back(goodMuon[I]);
				Hcand.push_back(goodTau[J]);
				goodMuon.erase(goodMuon.begin()+I);
				goodTau.erase(goodTau.begin()+J);
				break;
		case 3:
		case 7:
		        Hcand.push_back(goodElectron[I]);
				Hcand.push_back(goodTau[J]);
				goodElectron.erase(goodElectron.begin()+I);
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
	if(isSimulation){
		
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
     
     // histograms   
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
			
				break;

	
	}
	
			Hist( "h_H_lep1_eta")->Fill(Hcand[0].eta,weight);
			Hist( "h_H_lep1_phi")->Fill(Hcand[0].phi,weight);
			Hist( "h_H_lep2_eta")->Fill(Hcand[1].eta,weight);
			Hist( "h_H_lep2_phi")->Fill(Hcand[1].phi,weight);
		 
		 // overlap cleaning
			
		bool Ad_lepton = false;	
		 for(uint i = 0; i < goodMuon.size(); i++)
				{
					  if(deltaR(goodMuon[i].eta,goodMuon[i].phi,Hcand[0].eta,Hcand[0].phi)> 0.1 &&
					  deltaR(goodMuon[i].eta,goodMuon[i].phi,Hcand[1].eta,Hcand[1].phi)> 0.1 && RelIsoMu(goodMuon[i]) < 0.4) 
						Ad_lepton=true;
					
				}
				
		 for(uint i = 0; i < goodElectron.size(); i++)
				{
						if(deltaR(goodElectron[i].eta,goodElectron[i].phi,Hcand[0].eta,Hcand[0].phi)> 0.1 &&
						deltaR(goodElectron[i].eta,goodElectron[i].phi,Hcand[1].eta,Hcand[1].phi)> 0.1 && RelIsoEl(goodElectron[i]) < 0.4)  
						Ad_lepton=true;
					
				}
				
		for(uint i = 0; i < goodTau.size(); i++)
				{
					if(deltaR(goodTau[i].eta,goodTau[i].phi,Hcand[0].eta,Hcand[0].phi)> 0.1 &&
						deltaR(goodTau[i].eta,goodTau[i].phi,Hcand[1].eta,Hcand[1].phi)> 0.1 && goodTau[i].byMediumCombinedIsolationDeltaBetaCorr > 0.5)  
						Ad_lepton=true;
				}
		
		 if(Ad_lepton) 
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
	Hist("h_nbjets_beforeCut")->Fill(jet.size());
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
		return;
	}
	
	Hist("h_PF_MET_selected")->Fill(Met.front().et,weight);
	h_PF_MET_nPU_selected->Fill(nPU,Met.front().et,weight);
	
	Hist("h_nbjets_afterCut")->Fill(jet.size());
	
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
	if(signal) Hist( "h_event_type" )->Fill(event_type,weight);
 }else  Hist( "h_event_type" )->Fill(event_type,weight); // blinding 
 
  
   return;
   //trigger
    
}

