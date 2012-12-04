// $Id: CycleCreators.py 173 2010-05-12 15:49:33Z krasznaa $

// Local include(s):
#include "../include/FakeRate.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "Corrector_FR.h"

ClassImp( FakeRate );

FakeRate::FakeRate()
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
		DeclareProperty("SynchronizationTest",syncTest);
		DeclareProperty("vetoMuonTrigger",vetoMuonTrigger);
		DeclareProperty("vetoElectronTrigger", vetoElectronTrigger);
		DeclareProperty("isSimulation",isSimulation);
		DeclareProperty("is2011",is2011);
		DeclareProperty("is2012_52",is2012_52);
		DeclareProperty("is2012_53",is2012_53);
		DeclareProperty("useTruePileUp",useTruePileUp);
		DeclareProperty("maxDeltaR",maxDeltaR);
		
	}

FakeRate::~FakeRate() {

}

void FakeRate::BeginCycle() throw( SError ) {

	return;

}

void FakeRate::EndCycle() throw( SError ) {

	return;

}

void FakeRate::BeginInputData( const SInputData& ) throw( SError ) {

	h_el_n              = Book(TH1D("el_n","el_n",50,0,50));
	h_el_cut            = Book(TH1D("el_cit","el_cut",50,0,50));
	h_event_type        = Book(TH1D("h_event_type","Event Type",8,0.5,8.5));
	h_event_type_medium = Book(TH1D("h_event_type_medium","Event Type passing iso < 0.25",8,0.5,8.5));
	h_event_type_tight  = Book(TH1D("h_event_type_tight","Event Type passing iso < 0.1 ",8,0.5,8.5));

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
	//H->eMu relIso(mu)<0.15
	h_muH_eMu_tightMuIso_pt        = Book(TH1D("h_muH_eMu_tightMuIso_pt","H->mu e, mu pt",100,0,300));
	h_eH_eMu_tightMuIso_pt         = Book(TH1D("h_eH_eMu_tightMuIso_pt","H->mu e, e pt",100,0,300));
	h_H_eMu_tightMuIso_pt          = Book(TH1D("h_H_eMu_tightMuIso_pt","H->mu e, H pt",100,0,300));
	h_H_eMu_tightMuIso_mass        = Book(TH1D("h_H_eMu_tightMuIso_mass","H->mu e, H visible mass",100,0,300));
	//H->eMu relIso(mu)<0.25
	h_muH_eMu_looseMuIso_pt        = Book(TH1D("h_muH_eMu_looseMuIso_pt","H->mu e, mu pt",100,0,300));
	h_eH_eMu_looseMuIso_pt         = Book(TH1D("h_eH_eMu_looseMuIso_pt","H->mu e, e pt",100,0,300));
	h_H_eMu_looseMuIso_pt          = Book(TH1D("h_H_eMu_looseMuIso_pt","H->mu e, H pt",100,0,300));
	h_H_eMu_looseMuIso_mass        = Book(TH1D("h_H_eMu_looseMuIso_mass","H->mu e, H visible mass",100,0,300));
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

	h_medium				= Book(TH1D("h_medium","Medium iso",100,0,100));
	h_tight					= Book(TH1D("h_tight", "Tight iso", 100,0,100));
	h_denom					= Book(TH1D("h_denom", "Denominator", 100,0,100));




	h_event_type = Retrieve<TH1D>("h_event_type");
	h_event_type->GetXaxis()->SetBinLabel(1,"Z(#mu#mu)H(#mu#tau)");
	h_event_type->GetXaxis()->SetBinLabel(2,"Z(#mu#mu)H(#mu e)");
	h_event_type->GetXaxis()->SetBinLabel(3,"Z(#mu#mu)H(e#tau)");
	h_event_type->GetXaxis()->SetBinLabel(4,"Z(#mu#mu)H(#tau#tau)");
	h_event_type->GetXaxis()->SetBinLabel(5,"Z(ee)H(#mu#tau)");
	h_event_type->GetXaxis()->SetBinLabel(6,"Z(ee)H(#mu e)");
	h_event_type->GetXaxis()->SetBinLabel(7,"Z(ee)H(e#tau)");
	h_event_type->GetXaxis()->SetBinLabel(8,"Z(ee)H(#tau#tau)");

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

	h_denom_types.clear();
	for(uint i = 1; i <= h_event_type->GetNbinsX(); i++)
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

	for(uint i = 1; i <= h_event_type->GetNbinsX(); i++)
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

	for(uint i = 1; i <= h_event_type->GetNbinsX(); i++)
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


	index_number.clear();
	evt_number.clear();
	run_number.clear();
	lumi_number.clear();
	evt_type.clear();


	std::ifstream myfile;
	std::string line;
	if(syncTest){
		myfile.open ("mmet.txt");
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

			}
			myfile.close();
		}

		index_number.pop_back();
		evt_number.pop_back();
		run_number.pop_back();
		lumi_number.pop_back();
		evt_type.pop_back();
		std::cout << index_number.size() << " " << evt_number.size() << " " << run_number.size() << " " << lumi_number.size() << " " << evt_type.size() << std::endl;
		for (uint i =0; i < index_number.size(); i++)
		{
			std::cout << index_number[i] << " " << evt_type[i] << " " << run_number[i] << " " << lumi_number[i] << " " << evt_number[i] << std::endl;		
		}
	}
	
	
	// Lumi weights

	if(is2012_52) LumiWeights_ = new reweight::LumiReWeighting("Summer12_PU.root", "dataPileUpHistogram_True_2012.root","mcPU","pileup");
	else if (useTruePileUp && is2011) LumiWeights_ = new reweight::LumiReWeighting("Fall11_PU.root", "dataPileUpHistogram_True_2011.root","mcPU","pileup");
	else if (!useTruePileUp && is2011) LumiWeights_ = new reweight::LumiReWeighting("Fall11_PU_observed.root", "dataPileUpHistogram_Observed_2011.root","mcPU","pileup");
	else LumiWeights_ = new reweight::LumiReWeighting("Summer12_PU_53X.root", "dataPileUpHistogram_True_2012.root","mcPU","pileup");

	return;
}

void FakeRate::EndInputData( const SInputData& ) throw( SError ) {

	std::cout << "Event type summary: " << std::endl;
	std::cout << "Z(mumu)H(mutau)   : " << h_event_type->GetBinContent(1) << std::endl;
	std::cout << "Z(mumu)H(eMu)     : " << h_event_type->GetBinContent(2) << std::endl;
	std::cout << "Z(mumu)H(Etau)    : " << h_event_type->GetBinContent(3) << std::endl;
	std::cout << "Z(mumu)H(tautau)  : " << h_event_type->GetBinContent(4) << std::endl;
	std::cout << "Z(EE)H(mutau)     : " << h_event_type->GetBinContent(5) << std::endl;
	std::cout << "Z(EE)H(eMu)       : " << h_event_type->GetBinContent(6) << std::endl;
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

	return;

}

void FakeRate::BeginInputFile( const SInputData& ) throw( SError ) {
	ConnectVariable(InTreeName.c_str(),"myevent",m); 
	return;

}

double FakeRate::deltaR(double eta1, double phi1, double eta2, double phi2){
	double dR, dPhi, dEta;
	dR=dPhi=dEta=0.0;
	dPhi = phi1-phi2;
	if (dPhi < -TMath::Pi()) dPhi += TMath::TwoPi();
	if (dPhi > +TMath::Pi()) dPhi -= TMath::TwoPi();
	dEta = eta1-eta2;
	dR = sqrt(dPhi*dPhi+dEta*dEta);

	return dR;
}

bool FakeRate::EleMVANonTrigId(float pt, float eta, double value){
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

bool FakeRate::PFMuonID(myobject mu){

	if(mu.isGlobalMuon &&  mu.isPFMuon && mu.normalizedChi2 < 10. && mu.numberOfValidMuonHits > 0 && mu.numMatchStation > 1 && mu.dB < 0.2
			&& mu.dZ_in < 0.5 && mu.intrkLayerpixel > 0 && mu.trkLayerMeasure > 5) return true;
	else
		return false;

}

double FakeRate::RelIsoMu(myobject mu){
	double MuIsoTrk = mu.pfIsoCharged;
	double MuIsoEcal = mu.pfIsoGamma;
	double MuIsoHcal = mu.pfIsoNeutral;
	double MuIsoPU = mu.pfIsoPU;
	double relIso = (MuIsoTrk) / mu.pt;
	if (MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU > 0)
		relIso = (MuIsoTrk + MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU) / (mu.pt);

	return relIso;
}

double FakeRate::RelIsoEl(myobject el){
	double ElIsoTrk = el.pfIsoCharged;
	double ElIsoEcal = el.pfIsoGamma;
	double ElIsoHcal = el.pfIsoNeutral;
	double ElIsoPU = el.pfIsoPU;


	double relIso = (ElIsoTrk) / el.pt;
	if (ElIsoEcal + ElIsoHcal - 0.5 * ElIsoPU > 0)
		relIso = (ElIsoTrk + ElIsoEcal + ElIsoHcal - 0.5 * ElIsoPU) / (el.pt);
	return relIso;		
}

bool FakeRate::Trg_MC_12(myevent* m) {
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

bool FakeRate::WZ_Rej(myevent *m, myobject mu) {

	vector<myobject> Met = m->RecPFMet;
	bool met = Met.front().pt < 20.0;

	double tMass_v = sqrt(2*mu.pt*Met.front().et*(1-cos(Met.front().phi-mu.phi)));
	bool tMass = tMass_v < 30.0;
	if(syncTest)
		std::cout << "    >> MET is " << Met.front().pt <<  " aMass is " << sqrt(pow(Met.front().et + mu.et, 2) - pow(Met.front().px + mu.px, 2) - pow(Met.front().py + mu.py, 2)) << 
			" and tMass is " << sqrt(2*mu.pt*Met.front().et*(1-cos(Met.front().phi-mu.phi))) << std::endl;

	if(met && tMass)
		return true;
	else
		return false;
}

bool FakeRate::isGoodMu(myobject mu){

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

bool FakeRate::isGoodEl(myobject el){
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


void FakeRate::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
	m_logger << DEBUG << " Now executing event " << m->eventNumber << " in a run " << m->runNumber << SLogger::endmsg;

	int eNumber = m->eventNumber;
	bool foundEvent = false;
	uint pos = std::find(evt_number.begin(), evt_number.end(), eNumber) - evt_number.begin();
	if( pos < evt_number.size() && syncTest)
	{
		foundEvent = true;
	}

	if(foundEvent) std::cout << ">>>>>>>>>>>>>>>>> in event " << eNumber << " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << endl;	
	
	double PUWeight = 1.0;
	double nPU = 0.0;
	if(useTruePileUp || !is2011)  nPU = m->PUInfo_true;
	else nPU = m->PUInfo_Bunch0;
	if(isSimulation){	
		PUWeight = LumiWeights_->weight( nPU );
	}
	
	std::vector<myobject> vertex = m->Vertex;
	std::vector<myobject> goodVertex;
	goodVertex.clear();
	for (uint i = 0; i < vertex.size(); i++) {
		if (vertex[i].isValid && vertex[i].normalizedChi2 > 0 && vertex[i].ndof > 4 && fabs(vertex[i].z) < 24)
			goodVertex.push_back(vertex[i]);
	}
	short nGoodVx=goodVertex.size();


	bool trigPass = Trg_MC_12(m);
	m_logger << DEBUG << " Trigger decision " << trigPass << SLogger::endmsg;
	if(!trigPass)
	{
		return;
	}

	if(nGoodVx < 1) return;
	
	std::vector<myobject> goodMuon;
	goodMuon.clear();
	std::vector<myobject> denomMuon;
	denomMuon.clear();
	std::vector<int> DenomToGoodMuon_assoc_index; // indices of good muons
	DenomToGoodMuon_assoc_index.clear();
	std::vector<int> GoodToDenomMuon_assoc_index; // indices of denom muons
	GoodToDenomMuon_assoc_index.clear();
	

	std::vector<myobject> muon = m->PreSelectedMuons;
	m_logger << VERBOSE << " There are " << muon.size() << " preselected muons " << SLogger::endmsg;

	for (uint i = 0; i < muon.size(); i++) {

		double muPt = muon[i].pt;
		double eMuta = muon[i].eta;
		bool muGlobal = muon[i].isGlobalMuon;
		bool muTracker = muon[i].isTrackerMuon;
		double relIso = RelIsoMu(muon[i]);

		bool pfID = PFMuonID(muon[i]);	

		
		if (muGlobal && muTracker && muPt > 10. && fabs(eMuta) < 2.4)
		{
			
			if (pfID)
			{
				GoodToDenomMuon_assoc_index.push_back(denomMuon.size());
				DenomToGoodMuon_assoc_index.push_back(goodMuon.size());
				goodMuon.push_back(muon[i]);
				Hist("h_mu_relIso")->Fill(relIso,PUWeight);								
			}else{
				DenomToGoodMuon_assoc_index.push_back(-1);
			}
			denomMuon.push_back(muon[i]);
		}
		
	}

	// no isolation to muons applied!
	m_logger << VERBOSE << " There are " << goodMuon.size() << " good muons " << " and " << denomMuon.size() << " denominator muons" << SLogger::endmsg;
	
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
	
	
	if(foundEvent) std::cout <<  " There are " << electron.size() << " preselected electrons " << std::endl;
	m_logger << VERBOSE << " There are " << electron.size() << " preselected electrons " << SLogger::endmsg;

	for (uint i = 0; i < electron.size(); i++) {

		double elPt = electron[i].pt;
		double elEta = electron[i].eta;
		int missingHits = electron[i].numLostHitEleInner;
		bool elID = EleMVANonTrigId(elPt,elEta,electron[i].Id_mvaNonTrg);
		double relIso = RelIsoEl(electron[i]);

		if (elPt > 10. && fabs(elEta) < 2.5 )
		{
			if(elID && missingHits <=1){
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
	// no isolation to eles applied!
	m_logger << VERBOSE << " There are " << goodElectron.size() << " good electrons and " << denomElectron.size() << " denominator electrons" << SLogger::endmsg;
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
		//here you apply the iso to reconstruct the Z!
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
		int denom_i = GoodToDenomMuon_assoc_index[i];
		int denom_j = GoodToDenomMuon_assoc_index[j];		
		Zcand.push_back(goodMuon[i]);
		Zcand.push_back(goodMuon[j]);
		goodMuon.erase(goodMuon.begin()+i);
		goodMuon.erase(goodMuon.begin()+j-1);
		GoodToDenomMuon_assoc_index.erase(GoodToDenomMuon_assoc_index.begin()+i);
		GoodToDenomMuon_assoc_index.erase(GoodToDenomMuon_assoc_index.begin()+j-1);
		DenomToGoodMuon_assoc_index.erase(DenomToGoodMuon_assoc_index.begin()+denom_i);
		DenomToGoodMuon_assoc_index.erase(DenomToGoodMuon_assoc_index.begin()+denom_j-1);
		
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
			//here you apply the iso to reconstruct the Z!
			if( RelIsoEl(goodElectron[i]) > 0.3) continue;
			for(uint j = i+1; j < goodElectron.size() && !Zee; j++)
			{
				m_logger << VERBOSE << "  -->second electron no. "<< j << " has pt "<<  goodElectron[j].pt << " and charge " << goodElectron[j].charge << SLogger::endmsg;
				if( RelIsoEl(goodElectron[j]) > 0.3) continue;	
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
			int denom_i = GoodToDenomElectron_assoc_index[i];
			int denom_j = GoodToDenomElectron_assoc_index[j];		
		
			
			Zcand.push_back(goodElectron[i]);
			Zcand.push_back(goodElectron[j]);	
			goodElectron.erase(goodElectron.begin()+i);
			goodElectron.erase(goodElectron.begin()+j-1);
			GoodToDenomElectron_assoc_index.erase(GoodToDenomElectron_assoc_index.begin()+i);
			GoodToDenomElectron_assoc_index.erase(GoodToDenomElectron_assoc_index.begin()+j-1);
			DenomToGoodElectron_assoc_index.erase(DenomToGoodElectron_assoc_index.begin()+denom_i);
			DenomToGoodElectron_assoc_index.erase(DenomToGoodElectron_assoc_index.begin()+denom_j-1);
		
			
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
				corrZlep1=Cor_FR_ID_Iso_Mu_Loose_2012_53X(Zcand[0]);
				corrZlep2=Cor_FR_ID_Iso_Mu_Loose_2012_53X(Zcand[1]);
			}else if(is2012_52){
				corrZlep1=Cor_FR_ID_Iso_Mu_Loose_2012(Zcand[0]);
				corrZlep2=Cor_FR_ID_Iso_Mu_Loose_2012(Zcand[1]);
			}else{
				corrZlep1=Cor_FR_ID_Iso_Mu_Loose_2011(Zcand[0])*Cor_FR_Trg_Mu_Lead_2011(Zcand[0]);
				corrZlep2=Cor_FR_ID_Iso_Mu_Loose_2011(Zcand[1])*Cor_FR_Trg_Mu_SubLead_2011(Zcand[1]);
			}
			Z_weight *= corrZlep1* corrZlep2;	
		}else if(Zee){
			if(is2012_53){
				corrZlep1=Cor_FR_ID_Iso_Ele_Loose_2012_53X(Zcand[0]);
				corrZlep2=Cor_FR_ID_Iso_Ele_Loose_2012_53X(Zcand[1]);
			}else if(is2012_52){
				corrZlep1=Cor_FR_ID_Iso_Ele_Loose_2012(Zcand[0]);
				corrZlep2=Cor_FR_ID_Iso_Ele_Loose_2012(Zcand[1]);
			}else{
				corrZlep1=Cor_FR_ID_Iso_Ele_Loose_2011(Zcand[0])*Cor_FR_Trg_Ele_Lead_2011(Zcand[0]);
				corrZlep2=Cor_FR_ID_Iso_Ele_Loose_2011(Zcand[1])*Cor_FR_Trg_Ele_SubLead_2011(Zcand[1]);
			}
			Z_weight *= corrZlep1* corrZlep2;	
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

	}

	m_logger << VERBOSE << " There are " << goodElectron.size() << " remaining good electrons " << SLogger::endmsg;
	if(foundEvent) std::cout << eNumber <<": There are " << goodElectron.size() << " remaining good electrons " << std::endl;


	if(Zmumu||Zee)
	{
		if(foundEvent) std::cout << " Z candidate " << std::endl;
		m_logger << DEBUG << " There is a Z candidate! " << SLogger::endmsg;
	}
	else{
		return;
	}


	// Z overlap removal

	for(int i = 0; i < denomMuon.size(); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			if(deltaR(denomMuon[i].eta,denomMuon[i].phi,Zcand[j].eta,Zcand[j].phi)< maxDeltaR) 
			{	
				denomMuon.erase(denomMuon.begin()+i); 
				i--;			
				removed = true;
				// removal of the same muon as above from the "goodMuon" collection and association indices vectors
				if (DenomToGoodMuon_assoc_index[i] > -1){
					 uint goodIndex=DenomToGoodMuon_assoc_index[i];
					 goodMuon.erase(goodMuon.begin()+goodIndex);
					 GoodToDenomMuon_assoc_index.erase(GoodToDenomMuon_assoc_index.begin()+goodIndex);
					 DenomToGoodMuon_assoc_index.erase(DenomToGoodMuon_assoc_index.begin() +i);
				}
			}
		}
	}
	Hist("h_n_goodMu_Hcand")->Fill(muon.size());

	for(int i = 0; i < denomElectron.size(); i++)
	{
		bool removed = false;
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			if(deltaR(denomElectron[i].eta,denomElectron[i].phi,Zcand[j].eta, Zcand[j].phi)< maxDeltaR) 
			{	
				denomElectron.erase(denomElectron.begin()+i); 
				i--; 
				removed = true;
				if (DenomToGoodElectron_assoc_index[i] > -1){
					 uint goodIndex=DenomToGoodElectron_assoc_index[i];
					 goodElectron.erase(goodElectron.begin()+goodIndex);
					 GoodToDenomElectron_assoc_index.erase(GoodToDenomElectron_assoc_index.begin()+goodIndex);
					 DenomToGoodElectron_assoc_index.erase(DenomToGoodElectron_assoc_index.begin() +i);
				}
			}
		}

		for(uint j = 0; j < denomMuon.size() && !removed; j++)
		{
			if(deltaR(denomElectron[i].eta,denomElectron[i].phi,denomMuon[j].eta,denomMuon[j].phi)< maxDeltaR) 
			{	
				denomElectron.erase(denomElectron.begin()+i); 
				i--; 
				removed = true;
				if (DenomToGoodElectron_assoc_index[i] > -1){
					 uint goodIndex=DenomToGoodElectron_assoc_index[i];
					 goodElectron.erase(goodElectron.begin()+goodIndex);
					 GoodToDenomElectron_assoc_index.erase(GoodToDenomElectron_assoc_index.begin()+goodIndex);
					 DenomToGoodElectron_assoc_index.erase(DenomToGoodElectron_assoc_index.begin() +i);
				}
				
			}
			
		}

	}
	m_logger << DEBUG << " There are " << muon.size() << " and " << electron.size() << " remaining after Z overlap removal " << SLogger::endmsg;
	if(foundEvent) std::cout <<" There are " << goodMuon.size() << " and " << electron.size() << " remaining after Z overlap removal " << std::endl;

	Hist("h_n_goodEl_Hcand")->Fill(electron.size());	
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
		bool LooseIsolation = (tau[i].byLooseCombinedIsolationDeltaBetaCorr > 0.5);
		bool DecayMode = (tau[i].discriminationByDecayModeFinding > 0.5);
		bool ElectronMVA = (tau[i].discriminationByElectronMVA > 0.5);
		bool TightMuon = (tau[i].discriminationByMuonTight > 0.5);
		// no isolation, no cut on pt!	
		if(fabs(tauEta) < 2.3 && LooseElectron && LooseMuon && DecayMode){
				goodTau.push_back(tau[i]);
				if(foundEvent) std::cout<< "   Putting tau with pt " << tau[i].pt << " phi " <<tau[i].phi 
					<< " and ID " << LooseElectron << LooseMuon << CombinedIsolation << LooseIsolation << DecayMode << TightMuon << ElectronMVA << std::endl;
			
		}
	}

	for(int i = 0; i < goodTau.size(); i++)
	{
		bool removed = false;
		
		for(uint j = 0; j < Zcand.size() && !removed; j++)
		{
			if(deltaR(goodTau[i].eta,goodTau[i].phi,Zcand[j].eta, Zcand[j].phi)< maxDeltaR) 
			{	
				goodTau.erase(goodTau.begin()+i); 
				i--; 
				removed = true;
	
			}
		}
		

		for(uint j = 0; j < denomMuon.size() && !removed; j++)
		{

			if(deltaR(goodTau[i].eta,goodTau[i].phi,muon[j].eta,muon[j].phi)< maxDeltaR && RelIsoMu(muon[j]) < 0.4) 
			{	
				goodTau.erase(goodTau.begin()+i); 
				i--; 
				removed = true;
			}

		}

		for(uint j = 0; j < denomElectron.size() && !removed; j++)
		{

			if(deltaR(goodTau[i].eta,goodTau[i].phi,electron[j].eta,electron[j].phi)< maxDeltaR && RelIsoEl(electron[j]) < 0.4 ) 
			{	
				goodTau.erase(goodTau.begin()+i); 
				i--; 
				removed = true;
			}


		}

	}
	if(foundEvent) cout <<  " There are " << goodTau.size() << " good taus " << std::endl;
	m_logger << DEBUG << " There are " << goodTau.size() << " good taus " << SLogger::endmsg;	
	Hist("h_n_goodTau_Hcand")->Fill(goodTau.size());	

	// mutau final states
	bool muTau=false;
	bool eMu = false;         
	std::vector<myobject> Hcand;
	std::vector<myobject> Fakecand;
	Fakecand.clear();
	Hcand.clear();
	m_logger << DEBUG << " Starting muon loop: " << muon.size() << " " << eMu << " " << muTau << SLogger::endmsg;
	
	for(uint i = 0; i < denomMuon.size(); i++)
	{
		m_logger << DEBUG << " Checking for eMu " << denomMuon.size() << " " << i << " " << eMu << " " << muTau << SLogger::endmsg;
		for(uint j=0; j< denomElectron.size() &&!muTau; j++)
		{
			if(denomMuon[i].charge*denomElectron[j].charge < 0) continue;
			if(deltaR(denomElectron[j].eta,denomElectron[j].phi,denomMuon[i].eta,denomMuon[i].phi)< maxDeltaR) continue;
			eMu=true;
			Hcand.push_back(denomElectron[j]);
			Hcand.push_back(denomMuon[i]);
			

			denomElectron.erase(denomElectron.begin()+j); 
			j--;
			if(denomElectron.size()==0) j=denomElectron.size();
		}
		if(eMu){
			m_logger << DEBUG << " Found eMu " << muon.size() << " " << i << SLogger::endmsg;
		
			denomMuon.erase(denomMuon.begin()+i);i--;
			if(denomMuon.size()==0) i=denomMuon.size();	
		}

		m_logger << DEBUG << " Checking for muTau " << muon.size() << " " << i << " " << eMu << " " << muTau << SLogger::endmsg;
		for(uint j=0; j< goodTau.size() && !eMu ; j++)
		{
			if(denomMuon[i].charge*goodTau[j].charge < 0) continue;
			if(goodTau[j].discriminationByMuonTight <=0.5) continue;
			if(deltaR(goodTau[j].eta,goodTau[j].phi,denomMuon[i].eta,denomMuon[i].phi)< maxDeltaR) continue;
			muTau=true;
			Hcand.push_back(denomMuon[i]);
			Hcand.push_back(goodTau[j]);

			
			goodTau.erase(goodTau.begin()+j); j--;
			if(goodTau.size()==0) j=goodTau.size();
		}
		if(muTau){
			m_logger << DEBUG << " Found muTau " << denomMuon.size() << " " << i << SLogger::endmsg;
			
			denomMuon.erase(denomMuon.begin()+i);i--;
			
			if(denomMuon.size()==0) i=denomMuon.size();	
		
		}

	}


	bool eTau = false;
	if(!muTau&&!eMu)
	{
		for(uint i = 0; i < denomElectron.size() ; i++)
		{
			if(foundEvent) std::cout << " denomElectron no. " << i << " pt: " << denomElectron[i].pt << " eta " << denomElectron[i].eta << " phi " 
				<< denomElectron[i].phi << " charge " << denomElectron[i].charge << std::endl;
			if( denomElectron[i].numLostHitEleInner > 0) continue;
			m_logger << DEBUG << " Checking for eTau " << SLogger::endmsg;	
			eTau = false;
			for(uint j=0; j< goodTau.size() ; j++)
			{
				if(foundEvent) std::cout << " tau no. " << j << " pt: " << goodTau[j].pt << " eta " << goodTau[j].eta << " phi " 
					<< goodTau[j].phi << " charge " << goodTau[j].charge << std::endl;

				if(denomElectron[i].charge*goodTau[j].charge <0) continue;
				if(goodTau[j].discriminationByElectronMVA <=0.5) continue;
				if(deltaR(goodTau[j].eta,goodTau[j].phi,denomElectron[i].eta,denomElectron[i].phi)< maxDeltaR) continue;
				eTau=true;
				Hcand.push_back(denomElectron[i]);
				Hcand.push_back(goodTau[j]);
				
				goodTau.erase(goodTau.begin()+j); j--;
				if(goodTau.size()==0) j=goodTau.size();
			}
			if(eTau){
				denomElectron.erase(denomElectron.begin()+i); i--;
				if(denomElectron.size()==0) i=denomElectron.size();	
			}
		}

	}
	// no ISO has been applied to all "H leptons"! 
	if(foundEvent)  std::cout << " Total fake candidates " << Hcand.size() << std::endl;


	bool tauTau =false;
	if(!muTau && !eTau && !eMu)
	{
		for(uint i = 0; i < goodTau.size() &&!tauTau ; i++)
		{

			if(goodTau[i].discriminationByElectronMedium <=0.5) continue;
			if(goodTau[i].discriminationByMuonMedium <=0.5) continue;
			//if(goodTau[i].byTightCombinedIsolationDeltaBetaCorr <=0.5) continue;
			if(goodTau[i].pt < 20) continue;

			for(uint j=i+1; j< goodTau.size() &&!tauTau ; j++)
			{
				if(goodTau[i].charge*goodTau[j].charge <0) continue;
				if(goodTau[j].discriminationByElectronMedium <=0.5) continue;
				if(goodTau[j].discriminationByMuonMedium <=0.5) continue;
				//if(goodTau[j].byTightCombinedIsolationDeltaBetaCorr <=0.5) continue;
				if(goodTau[j].pt < 20) continue;
				if(deltaR(goodTau[j].eta,goodTau[j].phi,goodTau[i].eta,goodTau[i].phi)< maxDeltaR) continue;
				tauTau=true;
				Hcand.push_back(goodTau[i]);
				Hcand.push_back(goodTau[j]);

				
				goodTau.erase(goodTau.begin()+i); i--;
				goodTau.erase(goodTau.begin()+j-1); j-=2;

			}
		}
	}
	//tauTau=false;
	if(Hcand.size()==0 || (!muTau && !eTau && !tauTau && !eMu)){ 
		if(foundEvent) std::cout << " Not selected" << std::endl;

		m_logger << DEBUG << " No Higgs candidate. Going to next event" << SLogger::endmsg; 
		return;
	}
	//	else m_logger << INFO << "Higgs candidate. Size is " << Hcand.size() << SLogger::endmsg;
	// cross-check
	if(muTau+eTau+tauTau + eMu> 1){
		m_logger << ERROR << "Non-exclusive event type!! Aborting." << SLogger::endmsg;
		return;
	}

	short event_type = 0;

	if(Zmumu)
	{
		if(muTau) event_type = 1;
		if(eMu) event_type = 2;
		if(eTau) event_type = 3;
		if(tauTau) event_type = 4;
	}else if(Zee){
		if(muTau) event_type = 5;
		if(eMu) event_type = 6;
		if(eTau) event_type = 7;
		if(tauTau) event_type = 8;
	}


	double corrHlep1,corrHlep2;
	corrHlep1=corrHlep2=1.0;
	if(isSimulation){

		if(muTau)
		{
			if(is2012_53){
				corrHlep1=Cor_FR_ID_Iso_Mu_Tight_2012_53X(Hcand[0]);
			}else if(is2012_52){
				corrHlep1=Cor_FR_ID_Iso_Mu_Tight_2012(Hcand[0]);
			}else{
				corrHlep1=Cor_FR_ID_Iso_Mu_Tight_2011(Hcand[0]);
			}
		}else if(eTau){
			if(is2012_53){
				corrHlep1=Cor_FR_ID_Iso_Ele_Tight_2012_53X(Hcand[0]);
			}else if(is2012_52){
				corrHlep1=Cor_FR_ID_Iso_Ele_Tight_2012(Hcand[0]);
			}else{
				corrHlep1=Cor_FR_ID_Iso_Ele_Tight_2011(Hcand[0]);
			}
		}else if(eMu){
			if(is2012_53){
				corrHlep1=Cor_FR_ID_Iso_Mu_Loose_2012_53X(Hcand[0]);
				corrHlep2=Cor_FR_ID_Iso_Ele_Loose_2012_53X(Hcand[1]);
			}else if(is2012_52){
				corrHlep1=Cor_FR_ID_Iso_Mu_Loose_2012(Hcand[0]);
				corrHlep2=Cor_FR_ID_Iso_Ele_Loose_2012(Hcand[1]);
			}else{
				corrHlep1=Cor_FR_ID_Iso_Mu_Loose_2011(Hcand[0]);
				corrHlep2=Cor_FR_ID_Iso_Ele_Loose_2011(Hcand[1]);
			}
		}

	}

	double weight = PUWeight*corrZlep1*corrZlep2*corrHlep1*corrHlep2;
	

	// overlap cleaning
	if(foundEvent) 
		std::cout << "There is " << goodMuon.size() << " " << denomElectron.size() << " " << goodTau.size() << " more leptons." << std::endl;
	bool Ad_lepton = false;	
	for(uint i = 0; i < denomMuon.size(); i++)
	{
		for(uint j =0; j < Hcand.size(); j+=2){
			if(deltaR(denomMuon[i].eta,denomMuon[i].phi,Hcand[j].eta,Hcand[j].phi)> maxDeltaR &&
					deltaR(denomMuon[i].eta,denomMuon[i].phi,Hcand[j+1].eta,Hcand[j+1].phi)> maxDeltaR && isGoodMu(denomMuon[i]) < 0.4) 
				Ad_lepton=true;
		}

	}

	for(uint i = 0; i < denomElectron.size(); i++)
	{
		for(uint j =0; j < Hcand.size(); j+=2){				
			if(deltaR(denomElectron[i].eta,denomElectron[i].phi,Hcand[j].eta,Hcand[j].phi)> maxDeltaR &&
					deltaR(denomElectron[i].eta,denomElectron[i].phi,Hcand[j+1].eta,Hcand[j+1].phi)> maxDeltaR && RelIsoEl(denomElectron[i]) < 0.4 && isGoodEl(denomElectron[i]))  
				Ad_lepton=true;
		}

	}


	//~ for(uint i = 0; i < goodTau.size(); i++)
	//~ {
	//~ if(deltaR(goodTau[i].eta,goodTau[i].phi,Hcand[0].eta,Hcand[0].phi)> 0.3 &&
	//~ deltaR(goodTau[i].eta,goodTau[i].phi,Hcand[1].eta,Hcand[1].phi)> 0.3)  
	//~ Ad_lepton=true;
	//~ }
	//~ 


	if(Ad_lepton) 
	{			
		if(foundEvent) 
			std::cout << "Overlap cleaning" << std::endl;

		m_logger << INFO << "Additional good lepton(s) present. Aborting. " << SLogger::endmsg;
		return;
	}

	// Same vertex check
	if(foundEvent) 
		std::cout << " Z-vertex distances are " << fabs(Zcand[0].z_expo - Zcand[1].z_expo) << " " 
			<< fabs(Zcand[0].z_expo - Hcand[0].z_expo) << " " << fabs(Zcand[0].z_expo - Hcand[1].z_expo) << std::endl;
	bool dZ_expo = (fabs(Zcand[0].z_expo - Zcand[1].z_expo) < dZvertex);		
	bool dZ_expo2 = false;
	for(uint i = 0; i < Hcand.size() && dZ_expo; i+=2)
	{ 
		if(foundEvent) 
			std::cout << " Z-vertex distances in loop are " << fabs(Zcand[0].z_expo - Hcand[i].z_expo) << " " 
				<< fabs(Zcand[0].z_expo - Hcand[i+1].z_expo) << std::endl;
		if((fabs(Zcand[0].z_expo - Hcand[i].z_expo) > dZvertex)||(fabs(Zcand[0].z_expo - Hcand[i+1].z_expo) > dZvertex))
		{
			Hcand.erase(Hcand.begin()+i);
			Hcand.erase(Hcand.begin()+i);
			i-=2;
			if(Hcand.size()==0) i= Hcand.size();
			if(foundEvent) 
				std::cout << " Erasing! Remaing candidates are " << Hcand.size() << std::endl;
		}else dZ_expo2=true; 
	}
	dZ_expo=dZ_expo && dZ_expo2;  
	if(!dZ_expo)
	{
		if(foundEvent) 
			std::cout << " Vertex cut" << std::endl;

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
		if(jetPt > 20. && fabs(jetEta) < 2.4 && bTag > bTagValue){
			double dR1,dR2,dR3,dR4;
			dR1=deltaR(jetEta,jetPhi,Zcand[0].eta,Zcand[0].phi);
			dR2=deltaR(jetEta,jetPhi,Zcand[1].eta,Zcand[1].phi);
			dR3=deltaR(jetEta,jetPhi,Hcand[0].eta,Hcand[0].phi);
			dR4=deltaR(jetEta,jetPhi,Hcand[1].eta,Hcand[1].phi);
			bool dR = 1;
			for(uint i = 0; i < Hcand.size(); i++) dR*= (deltaR(jetEta,jetPhi,Hcand[i].eta,Hcand[i].phi) > 0.4);	
			if(dR1>0.4 && dR2>0.4 && dR3>0.4 && dR4>0.4 && dR) 
				bTagVeto = true;			
		}
	}

	if(bTagVeto)
	{
		if(foundEvent) 
			std::cout << " Btag cut" << std::endl;

		m_logger << INFO << "B-jet present. Aborting." << SLogger::endmsg;
		return;
	}

	if(foundEvent) std::cout << " WZ_rej cut" << std::endl;

	for(uint i =0; i < Hcand.size() && !tauTau; i+=2)
	{
		if(!WZ_Rej(m,Hcand[i])){
			Hcand.erase(Hcand.begin()+i);
			Hcand.erase(Hcand.begin()+i);
			i-=2;
			continue;
		}
	}



	//if(foundEvent) std::cout << " ---> Event " << eNumber << " I have " << Hcand.size()/2 << " candidates " << std::endl;
	//else if(Hcand.size() > 0 && syncTest) std::cout << " ---> Event " << eNumber << " I have " << Hcand.size()/2 << " candidates while Abdollah has NONE " << std::endl;

	for(uint i =0; i < Hcand.size(); i+=2)
	{
		Hist( "h_event_type" )->Fill(event_type,weight);
		//all no iso contributions are going into h_denom	
		Hist("h_denom")->Fill(Hcand[i].pt,weight);
		h_denom_types[event_type-1]->Fill(Hcand[i].pt,weight);
		if(eTau){
			if(RelIsoEl(Hcand[i]) < 0.25 && isGoodEl(Hcand[i])){ Hist("h_event_type_medium")->Fill(event_type,weight); h_medium_types[event_type-1]->Fill(Hcand[i].pt,weight); }
			if(RelIsoEl(Hcand[i]) < 0.10 && isGoodEl(Hcand[i])){ Hist("h_event_type_tight")->Fill(event_type,weight); h_tight_types[event_type-1]->Fill(Hcand[i].pt,weight); }
		}
		if(muTau){
			if(RelIsoMu(Hcand[i]) < 0.25 && isGoodMu(Hcand[i])){ Hist("h_event_type_medium")->Fill(event_type,weight); h_medium_types[event_type-1]->Fill(Hcand[i].pt,weight); }
			if(RelIsoMu(Hcand[i]) < 0.15 && isGoodMu(Hcand[i])){ Hist("h_event_type_tight")->Fill(event_type,weight); h_tight_types[event_type-1]->Fill(Hcand[i].pt,weight); }
		}
		if(eMu){
			if(RelIsoEl(Hcand[i]) < 0.3  && isGoodEl(Hcand[i])){ Hist("h_event_type_medium")->Fill(event_type,weight); h_medium_types[event_type-1]->Fill(Hcand[i].pt,weight); }
			if(RelIsoEl(Hcand[i]) < 0.10 && isGoodEl(Hcand[i])){ Hist("h_event_type_tight")->Fill(event_type,weight); h_tight_types[event_type-1]->Fill(Hcand[i].pt,weight); }
			if(RelIsoMu(Hcand[i+1]) < 0.3 && isGoodMu(Hcand[i+1])){ Hist("h_event_type_medium")->Fill(event_type,weight); h_medium_types[event_type-1]->Fill(Hcand[i+1].pt,weight); }
			if(RelIsoMu(Hcand[i+1]) < 0.15 && isGoodMu(Hcand[i+1])){ Hist("h_event_type_tight")->Fill(event_type,weight); h_tight_types[event_type-1]->Fill(Hcand[i+1].pt,weight); }
			h_denom_types[event_type-1]->Fill(Hcand[i+1].pt,weight);
		}
		if(tauTau){
			h_denom_types[event_type-1]->Fill(Hcand[i+1].pt,weight);
			if(Hcand[i].byMediumCombinedIsolationDeltaBetaCorr >= 0.5){ Hist("h_event_type_medium")->Fill(event_type,weight); h_medium_types[event_type-1]->Fill(Hcand[i].pt,weight); }
			if(Hcand[i].byTightCombinedIsolationDeltaBetaCorr >= 0.5){ Hist("h_event_type_tight")->Fill(event_type,weight); h_tight_types[event_type-1]->Fill(Hcand[i].pt,weight); }
			if(Hcand[i+1].byMediumCombinedIsolationDeltaBetaCorr >= 0.5){ Hist("h_event_type_medium")->Fill(event_type,weight); h_medium_types[event_type-1]->Fill(Hcand[i+1].pt,weight); }
			if(Hcand[i+1].byTightCombinedIsolationDeltaBetaCorr >= 0.5){ Hist("h_event_type_tight")->Fill(event_type,weight); h_tight_types[event_type-1]->Fill(Hcand[i+1].pt,weight); }
		}

		if(syncTest){
			std::cout <<" type: " << event_type << " event " << m->eventNumber << " in a run " << m->runNumber << std::endl;
			if(event_type==3 || event_type==7 || eMu){
				std::cout << " > candidate electron no. " << i/2 << " pt: " << Hcand[i].pt << " eta: " << Hcand[i].eta << " phi: " << 
					Hcand[i].phi << " ch: " << Hcand[i].charge << " iso " << RelIsoEl(Hcand[i]) << std::endl;
			}else if(event_type==1 || event_type==5){
				std::cout << " > candidate muon no. " << i/2 << " pt: " << Hcand[i].pt << " eta: " << Hcand[i].eta << " phi: " << 
					Hcand[i].phi << " ch: " << Hcand[i].charge << " iso " << RelIsoMu(Hcand[i]) << std::endl;
			}
			else if(tauTau)
			{
				std::cout << " > candidate tau no. " << i/2 << " pt: " << Hcand[i].pt << " eta: " << Hcand[i].eta << " phi: " << 
					Hcand[i].phi << " ch: " << Hcand[i].charge << std::endl;
			}
			if(!eMu){
				std::cout << " > candidate tau no. " << i/2 << " pt: " << Hcand[i+1].pt << " eta: " << Hcand[i+1].eta << " phi: " << 
					Hcand[i+1].phi << " ch: " << Hcand[i+1].charge << std::endl;
			}else{
				std::cout << " > candidate muon no. " << i/2 << " pt: " << Hcand[i].pt << " eta: " << Hcand[i+1].eta << " phi: " << 
					Hcand[i].phi << " ch: " << Hcand[i+1].charge << " iso " << RelIsoMu(Hcand[i+1]) << std::endl;
			}
		}


	}
	if(RelIsoEl(Hcand[0]) < 0.25) Hist("h_medium")->Fill(Hcand[0].pt,weight);
	if(RelIsoEl(Hcand[0]) < 0.10) Hist("h_tight")->Fill(Hcand[0].pt,weight);

	TLorentzVector Hcand1,Hcand2,H_boson;

	for(uint i =0;i < Hcand.size(); i+=2){
		Hcand1.SetPxPyPzE(Hcand[i].px,Hcand[i].py,Hcand[i].pz,Hcand[i].E);
		Hcand2.SetPxPyPzE(Hcand[i+1].px,Hcand[i+1].py,Hcand[i+1].pz,Hcand[i+1].E);
		H_boson = Hcand1+Hcand2;
		h_H_mass_types[event_type-1]->Fill(H_boson.M(),weight);
	}



	if(syncTest && Hcand.size() > 0){
		std::cout << " ----------------------------------------------------------------------------------------" << std::endl;
	}


	return;

}

