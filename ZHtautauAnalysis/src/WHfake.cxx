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
	
	// histogram booking
        Double_t bins[] = { 20, 30, 40, 50, 60, 70, 80, 100, 130, 300 };

	h_visMass_P1P2P3                                        = Book(TH1D("h_visMass_P1P2P3","H vis mass", 9, bins));
	h_LT_w                                           	= Book(TH1D("h_LT_w","LT w",300,0,300));

	if(is2011) LumiWeights_ = new reweight::LumiReWeighting("Fall11_PU.root", "dataPileUpHistogram_True_2011.root","mcPU","pileup");
	else LumiWeights_ = new reweight::LumiReWeighting("Summer12_PU_53X.root", "dataPileUpHistogramABCD_True_2012.root","mcPU","pileup");

	
	//bookkeeping
	lumi.open("lumi.csv");
	current_run=current_lumi=-999;
	eventList_wjets.open("eventList_wjets.list");
   
	syncOutTree = new TTree("UCL_tree","UCL_tree");
	syncOutTree->Branch("o_selected", &o_selected, "o_selected/i");
	syncOutTree->Branch("o_run", &o_run,"o_run/i");
	syncOutTree->Branch("o_event", &o_event,"o_event/L");
	syncOutTree->Branch("o_lumi", &o_lumi),"o_lumi/i";
	syncOutTree->Branch( "o_weight", &o_weight,"o_weight/D");
	syncOutTree->Branch( "o_id_iso_leadE", &o_id_iso_leadE,"o_id_iso_leadE/D");
	syncOutTree->Branch( "o_id_iso_subLeadE", &o_id_iso_subLeadE,"o_id_iso_subLeadE/D");
	syncOutTree->Branch( "o_pt_leadE", &o_pt_leadE,"o_pt_leadE/D");
	syncOutTree->Branch( "o_pt_subLeadE", &o_pt_subLeadE,"o_pt_subLeadE/D");
	syncOutTree->Branch( "o_pt_tH", &o_pt_tH,"o_pt_tH/D");
	syncOutTree->Branch( "o_pt_jet_leadE", &o_pt_jet_leadE,"o_pt_jet_leadE/D");
	syncOutTree->Branch( "o_pt_jet_subLeadE", &o_pt_jet_subLeadE,"o_pt_jet_subLeadE/D");
	syncOutTree->Branch( "o_njets", &o_njets,"o_njets/i");
	syncOutTree->Branch( "o_maxPt_leadE", &o_maxPt_leadE,"o_maxPt_leadE/D");
	syncOutTree->Branch( "o_maxPt_subLeadE", &o_maxPt_subLeadE,"o_maxPt_subLeadE/D");
	syncOutTree->Branch( "o_mass", &o_mass,"o_mass/D");
	syncOutTree->Branch( "o_LT", &o_LT,"o_LT/D");


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
	eventList_wjets.close();

	syncOut = new TFile("output_tree.root","RECREATE");
	syncOutTree->Write();
	syncOut->Close();


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

std::vector<myobject> WHfake::SelectGoodMuVector(std::vector<myobject> _muon, bool verb, double muPt_ = 5., double muEta_ = 2.4){
//std::vector<myobject> WHfake::SelectGoodMuVector(std::vector<myobject> _muon, std::vector<myobject> _jets, bool verb, double muPt_ = 5., double muEta_ = 2.4){

	std::vector<myobject> outMu_;
	outMu_.clear();
	for (uint i = 0; i < _muon.size(); i++) {
		double muPt = _muon[i].pt;
		double muEta = _muon[i].eta;
		bool muGlobal = _muon[i].isGlobalMuon;
		bool muTracker = _muon[i].isTrackerMuon;
		bool pfID = PFMuonID(_muon[i]);
		bool pixelHits = (_muon[i].intrkLayerpixel >=1);

		/*double max = 0.4;
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
		 */
		bool dZ = fabs(_muon[i].dz_PV) < 0.2;
		if ((muGlobal || muTracker) && muPt > muPt_ && fabs(muEta) < muEta_ && pixelHits && dZ ){
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

myobject WHfake::ClosestInCollection(myobject o1, std::vector<myobject> collection, double max=0.5)
{
        int index = -1;
        double minDist = 999.;
        for(uint i = 0; i< collection.size(); i++)
        {
                double dR = deltaR(o1,collection[i]);
                if(collection[i].pt < 12.) continue;
                if(dR< max && dR < minDist)
                {
                        index=i;
                        minDist=dR;
                }
        }
        if(index>=0) return collection[index];
        else return o1;
}

void WHfake::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {

        o_selected = 0;           
        o_run = 0;           
        o_lumi = 0;          
        o_event = 0;
        o_weight = 0;
        o_id_iso_leadE = 0;
        o_id_iso_subLeadE = 0;
        o_pt_leadE = 0;
        o_pt_subLeadE = 0;
        o_pt_tH = 0;
        o_pt_jet_leadE = 0;
        o_pt_jet_subLeadE = 0;
        o_njets = 0;
        o_maxPt_leadE = 0;
        o_maxPt_subLeadE = 0;
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
	std::vector<myobject> vetoMuon = SelectGoodMuVector(muon,examineThisEvent);
	//std::vector<myobject> vetoMuon = SelectGoodMuVector(muon,jet,examineThisEvent);
	if(examineThisEvent) std::cout << vetoMuon.size() << " selected muons --> good for VETO!" << std::endl;
	//m_logger << DEBUG << " veto muon " << SLogger::endmsg;

	if(examineThisEvent) std::cout << electron.size() << " preselected electrons " << std::endl;
	std::vector<myobject> genericElectron = SelectGoodElVector(electron,examineThisEvent);
	if(examineThisEvent) std::cout << genericElectron.size() << " generic electrons (NO ID APPLIED)" << std::endl;
	m_logger << DEBUG << " generic electron " << SLogger::endmsg;
	
	if(examineThisEvent) std::cout << genericElectron.size() << " generic electrons (NO ID APPLIED) --> good for SIGNAL or FAKE candidates!" << std::endl;

	//overlap cleaning: selected muons and selected electrons (with loose id) 
	//CrossCleanWithMu(&genericElectron,vetoMuon,examineThisEvent,maxDeltaR);
	//if(examineThisEvent) std::cout << genericElectron.size() << " generic electrons after the MU-ELE x-Cleaning" << std::endl;

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
			//genericElectron.erase(genericElectron.begin()+i);
			//i = i-1;
		} 
	m_logger << DEBUG << " inside good ele for " << SLogger::endmsg;
	}
	if(examineThisEvent){ 
		if(examineThisEvent) std::cout  << goodElectron.size() << " good electron " << endl;
		if(examineThisEvent) std::cout << genericElectron.size() << " generic electron " << endl;
	}

	if( goodElectron.size() < 2 )
		return;

        goodTau.clear();

        for (uint i = 0; i < tau.size(); i++) {

                double tauPt = (tau.at(i)).pt;
                double tauEta = (tau.at(i)).eta;
                double tauDZ = (tau.at(i)).dz_Ver_match;
                bool DecayMode = ((tau.at(i)).discriminationByDecayModeFinding > 0.5);
                
                if (tauPt > 20. && fabs(tauEta) < 2.3 && DecayMode && fabs(tauDZ) < 0.2){
                        if(examineThisEvent) std::cout << " -> Selected (NO ISO APPLIED)!" << std::endl;
                        goodTau.push_back(tau.at(i));
                }
       }

	tag.clear();
	probe.clear();

	for(uint i = 0; i < goodElectron.size(); ++i)
	{
                bool isTag = false;
                bool isProbe = false;
		bool etaR = fabs((goodElectron.at(i).eta)) < 1.479;
		bool relIsoLoose_W = RelIso(goodElectron.at(i)) < 0.15;
		bool relIsoTight_W = RelIso(goodElectron.at(i)) < 0.10;
                bool isoLoose_W = etaR && relIsoLoose_W;
                bool isoTight_W = !etaR && relIsoTight_W;
		bool pt10 = goodElectron[i].pt > 10.;
		bool pt20 = goodElectron[i].pt > 20.;
		bool tightEleID = TightEleId(goodElectron.at(i));

		if(examineThisEvent) cout << "ele " << i << " pt/tightEle/eta/iso: " << goodElectron[i].pt<<"/"<<tightEleID<<"/"<<fabs((goodElectron.at(i).eta))<<"/"<<RelIso(goodElectron.at(i))<<  endl;
		//cout << "ele " << i << " pt/tightEle/eta/iso: " << goodElectron[i].pt<<"/"<<tightEleID<<"/"<<fabs((goodElectron.at(i).eta))<<"/"<<RelIso(goodElectron.at(i))<<  endl;
		if( pt20 && tightEleID && (isoLoose_W || isoTight_W) ) isTag = true;
		//if( pt20 && tightEleID && (isoLoose_W || isoTight_W) ) isTag = true;
		if( pt10 ) isProbe = true;
 
		if( isTag ) {
			if(examineThisEvent) cout << "good as tag!" << endl;
			tag.push_back( goodElectron[i] );}               
                if( isProbe ){
			if(examineThisEvent) cout << "good as probe!" << endl;
			probe.push_back( goodElectron[i] );}               
	}
               
        if( (tag.size() + probe.size()) < 2 )
		return;

        //cout << "good electron size: " << goodElectron.size() << endl;
        if(examineThisEvent) cout << "good electron size: " << goodElectron.size() << endl;
        if(examineThisEvent) cout << "tag size: " << tag.size() << endl;
        if(examineThisEvent) cout << "probe size: " << probe.size() << endl;

	pair.clear();
	for(uint i=0; i<tag.size(); i++){
		if(examineThisEvent) cout << "tag trigger object " << tag[i].hasTrgObject_loose << endl;
		if(examineThisEvent) cout << "tag pt " << tag[i].pt << endl;
                if( !tag[i].hasTrgObject_loose ) continue;
		for(uint j=0; j<probe.size(); j++){
			std::pair<myobject,myobject> tmpPair;

			if(examineThisEvent) cout << "probe trigger object " << probe[j].hasTrgObject_loose << endl;
			if(examineThisEvent) cout << "probe pt " << probe[j].pt << endl;
			if(examineThisEvent) cout << "charge " << tag[i].charge*probe[j].charge << endl;
			if(examineThisEvent) cout << "mass " << PairMass(tag[i],probe[j]) << endl;

			if(deltaR(tag[i], probe[j]) < 0.5) continue;
			if( !probe[j].hasTrgObject_loose ) continue;
			if(tag[i].charge*probe[j].charge < 0) continue;
			if(probe[j].pt > tag[i].pt) continue;
			//if(deltaR(probe[j],tag[i]) < 0.5) continue;
                        //if(PairMass(tag[i],probe[j]) < 20. ) continue;
			//cout << "GOOD!" << endl;
			tmpPair=std::make_pair(tag[i],probe[j]);
			pair.push_back(tmpPair);
		}
	}
        if(examineThisEvent) cout << "pair size: " << pair.size() << endl;
        //cout << "probe size: " << probe.size() << endl;
	// Count the number of good muons
        if(pair.size()==0)
		return;
 

	//cout << "number of veto muons: " << vetoMuon.size() << endl;
	for(uint ipair=0; ipair < pair.size(); ipair++){
		bool haveMuon = false;
		for(uint l = 0; l < vetoMuon.size(); ++l){
			bool pt10_m = vetoMuon[l].pt > 10.;
			bool iso = RelIso(vetoMuon[l]) < 0.15;
			bool dR1 = deltaR(vetoMuon[l],pair[ipair].first) < 0.4;
			bool dR2 = deltaR(vetoMuon[l],pair[ipair].second) < 0.4;

			//cout << "pt/dr1/dr2 " <<  vetoMuon[l].pt<<"/"<<dR1<<"/"<<dR2 << endl;
			if(!pt10_m) continue;
			if(!iso) continue;
			if(!dR1 && !dR2){
				haveMuon = true;
                                break;
			}
		}
                if( haveMuon ){
			pair.erase(pair.begin()+ipair);
                        ipair = ipair - 1;}
                else
			if(examineThisEvent) cout << "No additional muons! --> Check Additional electrons" << endl;
      
	}

        if( pair.size()==0 )
		return;

	for(uint ipair=0; ipair < pair.size(); ipair++){
		bool haveElectron = false;
		for(uint i = 0; i < goodElectron.size(); i++){ 
                        if(examineThisEvent) cout << "goodElectronPt/tagPt/probePt: " << goodElectron[i].pt<<"/"<<(pair[ipair].first).pt<<"/"<<(pair[ipair].second).pt << endl;
			bool dR1 = deltaR(goodElectron[i],pair[ipair].first)<0.4;
			bool dR2 = deltaR(goodElectron[i],pair[ipair].second)<0.4;
                        if(examineThisEvent) cout << "dR1/dR2: " << dR1<<"/"<<dR2 << endl;
			bool pt10 = goodElectron[i].pt > 10.;

			if( !pt10 ) continue;
			if( !dR1 && !dR2 ){
				haveElectron = true;
				break;
			}
		}

                if(haveElectron){
			pair.erase(pair.begin()+ipair);
                        ipair = ipair - 1;}
                else
			if(examineThisEvent) cout << "No additional electrons! --> Check Additional taus" << endl;
	}
		//cout << "after the check! check the taus " << endl;
		// Count the number of good taus
        if( pair.size()==0 )
		return;

	for(uint ipair=0; ipair < pair.size(); ipair++){
		bool haveTau = false;
		for(uint l = 0; l < goodTau.size(); ++l){
			bool dR1_ = deltaR(goodTau[l],pair[ipair].first)<0.4;
			bool dR2_ = deltaR(goodTau[l],pair[ipair].second)<0.4;
			if( !dR1_ && !dR2_ ){
				haveTau = true;
				break;
			}
		}
                if(haveTau){
			pair.erase(pair.begin()+ipair);
                        ipair = ipair - 1;}
                else
			if(examineThisEvent) cout << "No additional taus! --> Check b-jet" << endl;
	}
        
	if( pair.size()==0 )
		return;
		// Jet counting
        nJets.clear();
        for(uint ipair=0; ipair < pair.size(); ipair++){
                int count_Jets = 0;
                bool bTagVeto = false;
                for (uint i = 0; i < jet.size() && !bTagVeto; i++) {
                        double jetPt = jet[i].pt;
                        double jetEta = jet[i].eta;
                        double jetPhi = jet[i].phi;
                        double bTag = jet[i].bDiscriminatiors_CSV;
                        double PUjetID = jet[i].puJetIdLoose;
                        double dR1,dR2;
                        dR1=deltaR(jet.at(i),pair[ipair].first);
                        dR2=deltaR(jet.at(i),pair[ipair].second);
                        if(examineThisEvent) std::cout << "jet pt " << jetPt << "jet eta " << jetEta << "btag " << bTag << "PU jet ID" << std::endl;

                        if(jetPt > 20. && fabs(jetEta) < 2.4 && PUjetID){
                                if(dR1 > 0.4 && dR2 > 0.4) count_Jets++;
                                if(bTag > bTagValue){
                                        if(examineThisEvent) std::cout << "candidate b-jet" << std::endl;
                                        if(examineThisEvent) std::cout << " distances are " << dR1 << " " << dR2 << std::endl;
                                        bool overlap = false;
                                        if(dR1 < 0.4 || dR2 < 0.4){
                                                overlap = true;
                                        }
                                        bTagVeto = !overlap;
                                }
                        }
                }
                nJets.push_back(count_Jets);

                if(examineThisEvent) std::cout << " nJets.size() " << nJets.size() << " - value " << nJets[ipair] <<  std::endl;
                if(bTagVeto){
                        if(examineThisEvent) std::cout << " b-jet found! " << std::endl;
                        pair.erase(pair.begin()+ipair);
                        nJets.erase(nJets.begin()+ipair);
                        ipair=ipair-1;
                }
        }

	if( pair.size()==0 )
		return;

	closestJet_subLead.clear();

	for(uint ipair=0; ipair < pair.size(); ipair++){
		if(examineThisEvent) cout << "Iso of tag " << RelIso(pair[ipair].first) << endl;
		if(examineThisEvent) cout << "Tmass with tag " << Tmass(m,pair[ipair].first) << endl;
		if(examineThisEvent) cout << "Tmass with probe " << Tmass(m,pair[ipair].second) << endl;

		if(Tmass(m,pair[ipair].first) < 30.) continue;

		if(60 > PairMass(pair[ipair].first,pair[ipair].second) || PairMass(pair[ipair].first,pair[ipair].second) > 120){ 
	
			bool etaR = fabs(((pair[ipair].second).eta)) < 1.479;
			bool relIsoLoose_subLead = RelIso(pair[ipair].second) < 0.20;
			bool relIsoTight_subLead = RelIso(pair[ipair].second) < 0.15;
			bool isoLoose_subLead = etaR && relIsoLoose_subLead;
			bool isoTight_subLead = !etaR && relIsoTight_subLead;
			bool looseEleID = LooseEleId( pair[ipair].second);

			if(examineThisEvent) cout << "GOOD! selection finished! Now let's fill the tree... " << endl;

			o_pt_subLeadE = (pair[ipair].second).pt;
			if( looseEleID && (isoLoose_subLead || isoTight_subLead))
				o_id_iso_subLeadE = 1;
			else
				o_id_iso_subLeadE = 0;

			closestJet_subLead.push_back(ClosestInCollection(pair[ipair].second,m->RecPFJetsAK5,0.5));

			o_njets = nJets[ipair];
			if(closestJet_subLead.size()==1){
				o_pt_jet_subLeadE = closestJet_subLead[0].pt;
				if(closestJet_subLead[0].pt > (pair[ipair].second).pt)
					o_maxPt_subLeadE = closestJet_subLead[0].pt;
				else
					o_maxPt_subLeadE = (pair[ipair].second).pt;
				closestJet_subLead.clear();
			}
			else{
				o_pt_jet_subLeadE = -1;
				o_maxPt_subLeadE = (pair[ipair].second).pt;
			}
			eventList_wjets << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ;
			syncOutTree->Fill();
		}
	}//loop of the pairs
} 


