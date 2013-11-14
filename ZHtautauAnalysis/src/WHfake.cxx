// $Id: CycleCreators.py 344 2012-12-13 13:10:53Z krasznaa $

// Local include(s):
#include "../include/WHfake.h"

ClassImp( WHfake );

WHfake::WHfake()
   : SCycleBase(), m_allEvents( "allEvents", this )
    {

   SetLogName( GetName() );
        DeclareProperty("InTreeName",InTreeName);
        DeclareProperty("maxDeltaR",maxDeltaR);
	DeclareProperty("ElectronTriggerName", doubEle);
	DeclareProperty("ElectronTriggerName2", doubEle2);
	
	DeclareProperty("MuonTriggerName1", doubMu);
	DeclareProperty("MuonTriggerName2", doubMu2);
	DeclareProperty("MuonTriggerName3", doubMu3);
	
	DeclareProperty("isSimulation",isSimulation);
	DeclareProperty("is2011",is2011);
	
	DeclareProperty("is2012_53",is2012_53);
	
	DeclareProperty("vetoMuonTrigger",vetoMuonTrigger);
	DeclareProperty("vetoElectronTrigger", vetoElectronTrigger);
	
	DeclareProperty("IgnoreSF",IgnoreSF);
	DeclareProperty("IgnorePUW",IgnorePUW);

	DeclareProperty("examineEvent",examineEvent);
	DeclareProperty("UseLongEvent",UseLongEvent);
	DeclareProperty("OverM",OverM);
	DeclareProperty("BelowM",BelowM);
        DeclareProperty("bTagValue",bTagValue);
	DeclareProperty("LTValue_mmt",LTValue_mmt);
        DeclareProperty("LTValue_eet",LTValue_eet);
        
	DeclareProperty("syncFileName",syncFileName);
	DeclareProperty("doSync",doSync);
}

WHfake::~WHfake() {

}

void WHfake::BeginCycle() throw( SError ) {

   return;

}

void WHfake::EndCycle() throw( SError ) {
	std::cout << "(0) Job exit code is 0" << std::endl;
   return;

}

void WHfake::BeginInputData( const SInputData& ) throw( SError ) {
	
	// ntuple definition
	DeclareVariable(o_selected,"selected");
	DeclareVariable(o_run,"run");
	DeclareVariable(o_lumi,"lumi");
	DeclareVariable(o_event,"event");
        DeclareVariable(o_weight,"weight");
	DeclareVariable(o_id_iso_eleW,"id_iso_eleW");
	DeclareVariable(o_id_iso_eleH,"id_iso_eleH");
        DeclareVariable(o_pt_eW,"pt_eW");
        DeclareVariable(o_pt_eH,"pt_eH");
        DeclareVariable(o_pt_tH,"pt_tH");
        DeclareVariable(o_pt_jet_eW,"pt_jet_eW");
        DeclareVariable(o_pt_jet_eH,"pt_jet_eH");
        DeclareVariable(o_njets,"njets");
        DeclareVariable(o_maxPt_eW,"maxPt_eW");
        DeclareVariable(o_maxPt_eH,"maxPt_eH");
        DeclareVariable(o_mass,"mass");
        DeclareVariable(o_LT,"LT");

	// histogram booking
        Double_t bins[] = { 20, 30, 40, 50, 60, 70, 80, 100, 130, 300 };

	h_visMass_P1P2P3                                        = Book(TH1D("h_visMass_P1P2P3","H vis mass", 9, bins));
	h_LT_w                                           	= Book(TH1D("h_LT_w","LT w",300,0,300));

	if(is2011) LumiWeights_ = new reweight::LumiReWeighting("Fall11_PU.root", "dataPileUpHistogram_True_2011.root","mcPU","pileup");
	else LumiWeights_ = new reweight::LumiReWeighting("Summer12_PU_53X.root", "dataPileUpHistogramABCD_True_2012.root","mcPU","pileup");

	
	//bookkeeping
	lumi.open("lumi.csv");
	current_run=current_lumi=-999;
	//eventList_wjets.open("eventList_wjets.list");
    
	//sync

	//std::ifstream myfile;
	if(doSync){
		sync_eventList.open (syncFileName.c_str());	
		if (sync_eventList.is_open()){
			while ( sync_eventList.good() ){
				long num;
				sync_eventList >> num;
				std::cout << num << std::endl;
				//if(num!=1) continue; //HACK!
				runs.push_back(num);
				sync_eventList >> num;
				lumis.push_back(num);
				sync_eventList >> num;
				events.push_back(num);
			}
			sync_eventList.close();
		}
	}
	std::cout << runs.size() << " " << lumis.size() << " " << events.size() << std::endl;
	for(uint iVal = 0; iVal < runs.size(); iVal++)
	{
		std::cout << runs[iVal] << " " << lumis[iVal] << " " << events[iVal] << std::endl;
	}
	return;
}

void WHfake::EndInputData( const SInputData& ) throw( SError ) {
	
	
	// Lumi weights
	
	// bookkeeping
	lumi.close();
	ofstream log2;       
        log2.open("total.txt");
        log2 << *m_allEvents << std::endl;
        log2.close();
	eventList_P1P2P3.close();

   return;

}

void WHfake::BeginInputFile( const SInputData& ) throw( SError ) {
	ConnectVariable(InTreeName.c_str(),"myevent",m);

   return;

}

// helper functions

bool WHfake::Trg_MC_12(myevent* m, bool found) {
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

std::vector<myobject> WHfake::SelectGoodVxVector(std::vector<myobject> _vertex, double _positionRho = 2., int _ndof = 4, double _dZ = 24.){
	
	std::vector<myobject> outVx_;
	outVx_.clear();	
	for (uint i = 0; i < _vertex.size(); i++) {
			if (_vertex[i].isValid && _vertex[i].position_Rho < _positionRho && _vertex[i].ndof > _ndof && fabs(_vertex[i].z) < _dZ)
			outVx_.push_back(_vertex[i]);
	}
	return outVx_;
}

bool WHfake::PFMuonID(myobject mu){

	if(mu.isGlobalMuon &&  mu.isPFMuon && mu.normalizedChi2 < 10. && mu.numberOfValidMuonHits > 0 && mu.numMatchStation > 1 && mu.dB < 0.2
			&& mu.dZ_in < 0.5 && mu.intrkLayerpixel > 0 && mu.trkLayerMeasure > 5) return true;
	else
		return false;

}

double WHfake::RelIso(myobject mu,bool verb=false){
	if(verb) std::cout << " lep pt/eta=" << mu.pt << "/" << mu.eta << std::endl;
	double MuIsoTrk = mu.pfIsoAll;
	double MuIsoEcal = mu.pfIsoGamma;
	double MuIsoHcal = mu.pfIsoNeutral;
	double MuIsoPU = mu.pfIsoPU;
	double relIso = (MuIsoTrk) / mu.pt;
	if(verb) std::cout << " charged iso:" << MuIsoTrk
					   << " neutral iso:" << MuIsoHcal
					   << " gamma iso:" << MuIsoEcal
					   << " PU iso: " << MuIsoPU;
	if (MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU > 0)
		relIso = (MuIsoTrk + MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU) / (mu.pt);
	if(verb) std::cout << " relIso = " << relIso << std::endl;
	return relIso;
}

double WHfake::deltaR(double eta1, double phi1, double eta2, double phi2){
        double dR, dPhi, dEta;
        dR=dPhi=dEta=0.0;
        dPhi = phi1-phi2;
        if (dPhi < -TMath::Pi()) dPhi += TMath::TwoPi();
        if (dPhi > +TMath::Pi()) dPhi -= TMath::TwoPi();
        dEta = eta1-eta2;
        dR = sqrt(dPhi*dPhi+dEta*dEta);

        return dR;
}

double WHfake::deltaR(myobject o1, myobject o2){
        return deltaR(o1.eta,o1.phi,o2.eta,o2.phi);
}

double WHfake::Tmass(myevent *m, myobject mu) {

	vector<myobject> Met = m->RecPFMet;

	double tMass_v = sqrt(2*mu.pt*Met.front().et*(1-cos(Met.front().phi-mu.phi)));
	return tMass_v;
}

double WHfake::PairMass(myobject Hcand1, myobject Hcand2){
	TLorentzVector H_1,H_2,H_sum;
	H_1.SetPxPyPzE(Hcand1.px,Hcand1.py,Hcand1.pz,Hcand1.E);
	H_2.SetPxPyPzE(Hcand2.px,Hcand2.py,Hcand2.pz,Hcand2.E);
	H_sum = H_1 + H_2;
	
        return H_sum.M();
}

double WHfake::PairPt(myobject Hcand1, myobject Hcand2){
	TLorentzVector H_1,H_2,H_sum;
	H_1.SetPxPyPzE(Hcand1.px,Hcand1.py,Hcand1.pz,Hcand1.E);
	H_2.SetPxPyPzE(Hcand2.px,Hcand2.py,Hcand2.pz,Hcand2.E);
	H_sum = H_1 + H_2;
	
        return H_sum.Pt();
}

bool WHfake::isLooseMu(myobject mu){

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




std::vector<myobject> WHfake::SelectGoodMuVector(std::vector<myobject> _muon, std::vector<myobject> _jets, bool verb, double muPt_ = 5., double muEta_ = 2.4){

	std::vector<myobject> outMu_;
	outMu_.clear();
	for (uint i = 0; i < _muon.size(); i++) {
		double muPt = _muon[i].pt;
		double muEta = _muon[i].eta;
		bool muGlobal = _muon[i].isGlobalMuon;
		bool muTracker = _muon[i].isTrackerMuon;
		bool pfID = PFMuonID(_muon[i]);
		bool pixelHits = (_muon[i].intrkLayerpixel >=1);

		double max = 0.4;
		double minDist = 1.0;
		int index = -1;
		for(uint j = 0; j< _jets.size(); j++)
		{
			if(_jets[j].pt < 12.) continue;
			double dR = deltaR(_muon[i],_jets[j]);
			if(dR< max && dR < minDist)
			{
				index=j;
				minDist=dR;
			}
		}
		bool bTag=true;
		if(index>-1){ bTag = _jets[index].bDiscriminatiors_CSV < 0.8;}

		bool dZ = fabs(_muon[i].dz_PV) < 0.2;
		if ((muGlobal || muTracker) && muPt > muPt_ && fabs(muEta) < muEta_ && pixelHits && bTag && dZ ){
			outMu_.push_back(_muon[i]);
		}
	}
	return outMu_;
}


std::vector<myobject> WHfake::SelectGoodElVector(std::vector<myobject> _electron, bool verb, double elPt_ =10., double elEta_ = 2.5){

	std::vector<myobject> outEl_;
	outEl_.clear();
	for (uint i = 0; i < _electron.size(); i++) {
	
			double elPt = _electron[i].pt;
			double elEta = _electron[i].eta_SC;

			bool dZ = fabs(_electron[i].dz_PV) < 0.2;

                        if(verb) cout << "ele n* " << i+1 << " pt " << elPt << " eta " << fabs(elEta) << " mva " << _electron[i].Id_mvaNonTrg << " dZ " << dZ << endl; 
			if ( elPt > elPt_ && fabs(elEta) < elEta_ && dZ )
			{
				outEl_.push_back(_electron[i]);
			}else{
				if(verb){ 
                        cout << "ele n* " << i+1 << " failed: pt " << elPt << " eta " << fabs(elEta) << " mva " << _electron[i].Id_mvaNonTrg << " dZ " << dZ << endl; 
				}
			}
	}
	return outEl_;
}

void WHfake::CrossCleanWithMu(std::vector<myobject>* _input, std::vector<myobject> _muon, bool verb, double _maxDeltaR, double _muIso = 0.3, bool _looseMuId = true){
	
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

void WHfake::CrossCleanWithEle(std::vector<myobject>* _ele, std::vector<myobject> _input, bool verb, double _maxDeltaR){
	
	for(int i = 0; i < int(_input.size()); i++)
		{
			bool removed = false;
		
			for(uint j = 0; j < _ele->size() && !removed; j++)
			{
				if(deltaR(_input.at(i),_ele->at(j))< _maxDeltaR && RelIso(_ele->at(j)) < 0.3) 
				{      if(verb) cout << "I'm erasing tau with pt " << (_input.at(i)).pt << endl;	
                                       _input.erase(_input.begin()+i); i--; removed = true;}
			}
		}
}

bool WHfake::TightEleId(float pt, float eta, double value){
	bool passingId=false;


	if(pt>20. && fabs(eta)<0.8 && value>0.925)
		passingId=true;
	if(pt>20. && fabs(eta)>0.8 && fabs(eta)<1.479 && value>0.975)
		passingId=true;
	if(pt>20. && fabs(eta)>1.479 && value>0.985)
		passingId=true;
	// if(value>10.)cout<<"pt==== "<<pt<<" "<<"eta=== "<<eta<<" "<<"value=== "<<value<<endl;
	return passingId;
}

bool WHfake::TightEleId(myobject o){
	return TightEleId(o.pt, o.eta_SC,o.Id_mvaNonTrg);
}

bool WHfake::LooseEleId(float pt, float eta, double value){
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
	// if(value>10.)cout<<"pt==== "<<pt<<" "<<"eta=== "<<eta<<" "<<"value=== "<<value<<endl;
	return passingId;
}

bool WHfake::LooseEleId(myobject o){
	//if( o.numLostHitEleInner > 0) return false;
	return LooseEleId(o.pt, o.eta_SC,o.Id_mvaNonTrg);
}

void WHfake::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {

        o_selected = 0;           
        o_run = 0;           
        o_lumi = 0;          
        o_event = 0;
        o_weight = 0;
        o_id_iso_eleW = 0;
        o_id_iso_eleH = 0;
        o_pt_eW = 0;
        o_pt_eH = 0;
        o_pt_tH = 0;
        o_pt_jet_eW = 0;
        o_pt_jet_eH = 0;
        o_njets = 0;
        o_maxPt_eW = 0;
        o_maxPt_eH = 0;
        o_mass = 0;
        o_LT = 0;
        
        o_run = m->runNumber;           
        o_lumi = m->lumiNumber;          
        o_event = m->eventNumber;

	// bookkepping part
	++m_allEvents;
	if(m->runNumber!=current_run || m->lumiNumber!=current_lumi){
		lumi << m->runNumber << " " << m->lumiNumber << std::endl;
		current_run=m->runNumber;
		current_lumi=m->lumiNumber;
	}
	
	m_logger << DEBUG << " Now executing event " << m->eventNumber << " in a run " << m->runNumber << SLogger::endmsg;
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
	
	//syncing
	
	if(doSync){
		uint pos_helper=0;
        pos_helper = std::find(events.begin(), events.end(), m->eventNumber) - events.begin();
		if(pos_helper < events.size()) examineThisEvent=true;
	}
	
	if(examineThisEvent) std::cout << "Examining! Event number " << eNumber << " ENTRY: " << m_allEvents << std::endl;


	// PU weightting
	double PUWeight = 1.0;
	double nPU = 0.0;
	nPU = m->PUInfo_true;
	if(isSimulation){	
		PUWeight = LumiWeights_->weight( nPU );
		if(IgnorePUW) PUWeight = 1.0;
	}
	
	bool trigPass;
	trigPass = Trg_MC_12(m,examineThisEvent);
	m_logger << DEBUG <<" Trigger decision " << trigPass << SLogger::endmsg;
	if(!trigPass)
	{
		if(examineThisEvent){
			 std::cout << "Trigger fail! " << examineEvent << std::endl;
		 }
		return;
	}

	//vertex selection
	std::vector<myobject> vertex = m->Vertex;
	std::vector<myobject> goodVertex = SelectGoodVxVector(vertex);
	short nGoodVx=goodVertex.size();
	
	// at least one good vertex
	if(nGoodVx < 1){
		if(examineThisEvent){ std::cout << "Good vertex fail!" << std::endl;
		}
		 return;
	 
	 }
	if(examineThisEvent){ 
	   std::cout << goodVertex.size() << " good vertex " << std::endl;
	   std::cout << " position rho " << (goodVertex[0]).position_Rho << std::endl;
	   std::cout << " ndof " << (goodVertex[0]).ndof << std::endl;
	   std::cout << " Z " << (goodVertex[0]).z << std::endl;
        }
        
	m_logger << DEBUG << " vertex cut pass " << SLogger::endmsg;
	
	std::vector<myobject> electron = m->PreSelectedElectrons;
	std::vector<myobject> muon = m->PreSelectedMuons;
	std::vector<myobject> tau = m->PreSelectedHPSTaus;
	std::vector<myobject> jet = m->RecPFJetsAK5;

	if(examineThisEvent) std::cout << muon.size() << " preselected muons " << std::endl;
	std::vector<myobject> vetoMuon = SelectGoodMuVector(muon,jet,examineThisEvent);
	if(examineThisEvent) std::cout << vetoMuon.size() << " selected muons --> good for VETO!" << std::endl;
	m_logger << DEBUG << " veto muon " << SLogger::endmsg;

	if(examineThisEvent) std::cout << electron.size() << " preselected electrons " << std::endl;
	std::vector<myobject> genericElectron = SelectGoodElVector(electron,examineThisEvent);
	if(examineThisEvent) std::cout << genericElectron.size() << " generic electrons (NO ID APPLIED)" << std::endl;
	m_logger << DEBUG << " generic electron " << SLogger::endmsg;
	
	if(examineThisEvent) std::cout << genericElectron.size() << " generic electrons (NO ID APPLIED) --> good for SIGNAL or FAKE candidates!" << std::endl;

	//overlap cleaning: selected muons and selected electrons (with loose id) 
	CrossCleanWithMu(&genericElectron,vetoMuon,examineThisEvent,maxDeltaR);
	if(examineThisEvent) std::cout << genericElectron.size() << " generic electrons after the MU-ELE x-Cleaning" << std::endl;

	//overlap cleaning: selected electrons (with loose id) and taus 
	if(examineThisEvent) std::cout << tau.size() << " preselected taus " << std::endl;
	CrossCleanWithEle(&genericElectron,tau,examineThisEvent,0.4);
	if(examineThisEvent) std::cout << tau.size() << " preselected taus after the ELE-TAU x-Cleaning" << std::endl;
	m_logger << DEBUG << " cross cleaning tau " << SLogger::endmsg;
	

	std::vector<myobject> goodElectron;
        goodElectron.clear();
	for(uint i=0; i<genericElectron.size(); i++){

		int eleHit = genericElectron[i].numHitEleInner;
		int index = -1;
		double max = 0.4;
		double minDist = 1.0;
		for(uint j = 0; j< jet.size(); j++)
		{
			if(jet[j].pt < 12.) continue;
			double dR = deltaR(genericElectron[i],jet[j]);
			if(dR< max && dR < minDist)
			{
				index=j;
				minDist=dR;
			}
		}
		bool bTag=true;
		if(index>-1){ bTag = jet[index].bDiscriminatiors_CSV < 0.8;}

		bool isGsfCtfScPixCC = (genericElectron.at(i)).isGsfCtfScPixChargeConsistent;
		bool isGsfScPixCC = (genericElectron.at(i)).isGsfScPixChargeConsistent; 
		bool isGsfCtfCC = (genericElectron.at(i)).isGsfCtfChargeConsistent;
		bool conversionVeto = (genericElectron.at(i)).passConversionVeto;

		if( eleHit == 0 && bTag && isGsfCtfScPixCC && isGsfScPixCC && isGsfCtfCC && conversionVeto ){
			if(examineThisEvent){
				std::cout << "pt " << (genericElectron.at(i)).pt << " ctfSc - ScPix - CtfCC - cv " << isGsfCtfScPixCC << " - " << isGsfScPixCC << " - " << isGsfCtfCC << " - " << conversionVeto << endl;
			}
			goodElectron.push_back(genericElectron.at(i));
			genericElectron.erase(genericElectron.begin()+i);
			i = i-1;
		} 
	m_logger << DEBUG << " inside good ele for " << SLogger::endmsg;
	}
	if(examineThisEvent){ 
		if(examineThisEvent) std::cout  << goodElectron.size() << " good electron " << endl;
		if(examineThisEvent) std::cout << genericElectron.size() << " generic electron " << endl;
	}

	if( goodElectron.size() < 2 )
		return;

        std::vector<myobject> goodTau;
        goodTau.clear();

        for (uint i = 0; i < tau.size(); i++) {

                double tauPt = (tau.at(i)).pt;
                double tauEta = (tau.at(i)).eta;
                double tauDZ = (tau.at(i)).dz_Ver_match;
                bool DecayMode = ((tau.at(i)).discriminationByDecayModeFinding > 0.5);
                
                if (tauPt > 20. && fabs(tauEta) < 2.3 && DecayMode && fabs(tauDZ) < 0.2){
                        if(examineThisEvent) std::cout << " -> Selected (NO ISO APPLIED)!" << std::endl;
                        goodTau.push_back(tau.at(i));
                        tau.erase(tau.begin()+i);
                        i=i-1;
                }
       }


	std::vector<myobject> tag;
	tag.clear();
	std::vector<myobject> probe;
	probe.clear();

	for(uint i = 0; i < goodElectron.size(); ++i)
	{
		bool etaR = fabs((goodElectron.at(i).eta)) < 1.479;
		bool relIsoLoose_W = RelIso(goodElectron.at(i)) < 0.15;
		bool relIsoTight_W = RelIso(goodElectron.at(i)) < 0.10;
		bool pt20 = goodElectron[i].pt > 20.;
		bool tightEleID = TightEleId(goodElectron.at(i));

		if(!pt20) continue;
		if(!tightEleID) continue;
		if(!(etaR&&relIsoLoose_W) || !(!etaR&&relIsoTight_W)) continue;
                
                o_id_iso_eleW = 1;

		// Got a tag, depending on isolation this defines either W+Jets or QCD regino
		for(uint j = 0; j < goodElectron.size() && i!=j; ++j)
		{
			bool pt10 = goodElectron[i].pt > 10.;

			if(!pt10) continue;
			if(goodElectron[i].charge*goodElectron[j].charge < 0) continue;
			if(goodElectron[j].pt > goodElectron[i].pt) continue;
			if(TMath::Max(goodElectron[i].pt, goodElectron[j].pt) < 20.) continue;
			if(deltaR(goodElectron[i], goodElectron[j]) < 0.5) continue;

			// Veto construction
			tag.push_back(goodElectron[i]); //tag
			probe.push_back(goodElectron[j]); //probe

			// Count the number of good muons
			unsigned int nGoodMuons = 0;
			for(unsigned int l = 0; l < vetoMuon.size(); ++l){
				bool pt10_m = vetoMuon[l].pt > 10.;
                                bool dR1 = deltaR(vetoMuon[l],tag[0])<0.4;
                                bool dR2 = deltaR(vetoMuon[l],probe[0])<0.4;
				if(!pt10_m)
					if(!dR1 && !dR2)
						++nGoodMuons;
			}
			if(nGoodMuons > 0) continue;

			// 3rd electron rejection
			bool haveElectron = false;
			for(unsigned int l = 0; l < goodElectron.size(); ++l) if(l != i && l != j){
				bool etaR = fabs((goodElectron.at(i).eta)) < 1.479;
				bool relIsoLoose_W = RelIso(goodElectron.at(i)) < 0.15;
				bool relIsoTight_W = RelIso(goodElectron.at(i)) < 0.10;
				bool pt20 = goodElectron[i].pt > 20.;
				bool tightEleID = TightEleId(goodElectron.at(i));
                                bool dR1 = deltaR(goodElectron[l],tag[0])<0.4;
                                bool dR2 = deltaR(goodElectron[l],probe[0])<0.4;
				if( pt10 ) //&& tightEleID && ( (etaR&&relIsoLoose_W) || (!etaR&&relIsoTight_W) ) )
					if(!dR1 && !dR2)
						haveElectron = true;
			}
			if(haveElectron) continue;

			// Count the number of good taus
			unsigned int nGoodTaus = 0;
			for(unsigned int l = 0; l < goodTau.size(); ++l){
                                bool dR1 = deltaR(goodTau[l],tag[0])<0.4;
                                bool dR2 = deltaR(goodTau[l],probe[0])<0.4;
				if(!dR1 && !dR2)
					++nGoodTaus;
			}
			if(nGoodTaus > 0) continue;

			// Jet counting
			unsigned int nJets20 = 0;
			bool haveTagJet = false;
			bool haveBJet = false;
			for(unsigned int l = 0; l < jet.size(); ++l)
			{
				double jetPt = jet[l].pt;
				double jetEta = jet[l].eta;
				double bTag = jet[l].bDiscriminatiors_CSV;
				double PUjetID = jet[l].puJetIdLoose;
				if(jetPt < 20) continue;
				if(jetEta > 2.4) continue;
				if(!PUjetID) continue;
				if(deltaR(jet[l], tag[0])<0.4) continue;
				if(deltaR(jet[l], probe[0])<0.4) continue;
				haveTagJet = true;
				if(jetEta > 2.3) continue;
				if(bTag < bTagValue) continue;
				haveBJet = true;
				++nJets20;
			}

			if(haveBJet) continue;
			if(!haveTagJet) continue;

			if(Tmass(m,tag[0]) > 30. && (60 > PairMass(tag[0], probe[0])  || PairMass(tag[0], probe[0]) > 120) )
				if(examineThisEvent) cout << "ciao" << endl;

		}//first good electron
	}//second good electron
} 


