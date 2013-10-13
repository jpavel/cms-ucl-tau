// $Id: CycleCreators.py 344 2012-12-13 13:10:53Z krasznaa $

// Local include(s):
#include "../include/WHanalysis.h"



ClassImp( WHanalysis );

WHanalysis::WHanalysis()
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
        DeclareProperty("LTValue",LTValue);
}

WHanalysis::~WHanalysis() {

}

void WHanalysis::BeginCycle() throw( SError ) {

   return;

}

void WHanalysis::EndCycle() throw( SError ) {
	std::cout << "(0) Job exit code is 0" << std::endl;
   return;

}

void WHanalysis::BeginInputData( const SInputData& ) throw( SError ) {
	
	// ntuple definition
	DeclareVariable(out_pt,"pt");
	
	// histogram booking
	
	h_PU_weight					 = Book(TH1D("h_PU_weight","PU weights distribution",100,0,5));
	h_nPU_raw					 = Book(TH1D("h_nPU_raw","raw PU distribution",100,0,100));
	h_nPU_reweight					 = Book(TH1D("h_nPU_reweight","reweighted PU distribution",100,0,100));
	
	
	if(is2011) LumiWeights_ = new reweight::LumiReWeighting("Fall11_PU.root", "dataPileUpHistogram_True_2011.root","mcPU","pileup");
	else LumiWeights_ = new reweight::LumiReWeighting("Summer12_PU_53X.root", "dataPileUpHistogramABCD_True_2012.root","mcPU","pileup");

	
	//bookkeeping
	lumi.open("lumi.csv");
	current_run=current_lumi=-999;
	

   return;

}

void WHanalysis::EndInputData( const SInputData& ) throw( SError ) {
	
	
	// Lumi weights

	
	// bookkeeping
	lumi.close();
	ofstream log2;       
     log2.open("total.txt");
     log2 << *m_allEvents << std::endl;
     log2.close();

   return;

}

void WHanalysis::BeginInputFile( const SInputData& ) throw( SError ) {
	ConnectVariable(InTreeName.c_str(),"myevent",m);

   return;

}

// helper functions

bool WHanalysis::Trg_MC_12(myevent* m, bool found) {
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

std::vector<myobject> WHanalysis::SelectGoodVxVector(std::vector<myobject> _vertex, double _normChi2 = 0., int _ndof = 4, double _dZ = 24.){
	
	std::vector<myobject> outVx_;
	outVx_.clear();	
	for (uint i = 0; i < _vertex.size(); i++) {
			if (_vertex[i].isValid && _vertex[i].normalizedChi2 > _normChi2 && _vertex[i].ndof > _ndof && fabs(_vertex[i].z) < _dZ)
			outVx_.push_back(_vertex[i]);
	}
	return outVx_;
}

bool WHanalysis::PFMuonID(myobject mu){

	if(mu.isGlobalMuon &&  mu.isPFMuon && mu.normalizedChi2 < 10. && mu.numberOfValidMuonHits > 0 && mu.numMatchStation > 1 && mu.dB < 0.2
			&& mu.dZ_in < 0.5 && mu.intrkLayerpixel > 0 && mu.trkLayerMeasure > 5) return true;
	else
		return false;

}

double WHanalysis::deltaR(double eta1, double phi1, double eta2, double phi2){
	double dR, dPhi, dEta;
	dR=dPhi=dEta=0.0;
	dPhi = phi1-phi2;
	if (dPhi < -TMath::Pi()) dPhi += TMath::TwoPi();
	if (dPhi > +TMath::Pi()) dPhi -= TMath::TwoPi();
	dEta = eta1-eta2;
	dR = sqrt(dPhi*dPhi+dEta*dEta);

	return dR;
}

double WHanalysis::deltaR(myobject o1, myobject o2){
	return deltaR(o1.eta,o1.phi,o2.eta,o2.phi);
}

double WHanalysis::RelIso(myobject mu){

	double MuIsoTrk = mu.pfIsoAll;
	double MuIsoEcal = mu.pfIsoGamma;
	double MuIsoHcal = mu.pfIsoNeutral;
	double MuIsoPU = mu.pfIsoPU;
	double relIso = (MuIsoTrk) / mu.pt;
	if (MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU > 0)
		relIso = (MuIsoTrk + MuIsoEcal + MuIsoHcal - 0.5 * MuIsoPU) / (mu.pt);

	return relIso;
}

myobject WHanalysis::ClosestInCollection(myobject o1, std::vector<myobject> collection, double max=0.5)
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

double WHanalysis::DistanceToClosestInCollection(myobject o1, std::vector<myobject> collection)
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

double WHanalysis::Tmass(myevent *m, myobject mu) {

	vector<myobject> Met = m->RecPFMet;

	double tMass_v = sqrt(2*mu.pt*Met.front().et*(1-cos(Met.front().phi-mu.phi)));
	return tMass_v;
}

double WHanalysis::PairMass(myobject Hcand1, myobject Hcand2){
	TLorentzVector H_1,H_2,H_sum;
    H_1.SetPxPyPzE(Hcand1.px,Hcand1.py,Hcand1.pz,Hcand1.E);
    H_2.SetPxPyPzE(Hcand2.px,Hcand2.py,Hcand2.pz,Hcand2.E);
    H_sum = H_1 + H_2;
	return H_sum.M();
}

double WHanalysis::PairPt(myobject Hcand1, myobject Hcand2){
	TLorentzVector H_1,H_2,H_sum;
    H_1.SetPxPyPzE(Hcand1.px,Hcand1.py,Hcand1.pz,Hcand1.E);
    H_2.SetPxPyPzE(Hcand2.px,Hcand2.py,Hcand2.pz,Hcand2.E);
    H_sum = H_1 + H_2;
	return H_sum.Pt();
}

std::vector<myobject> WHanalysis::SelectGoodMuVector(std::vector<myobject> _muon, bool verb, double muPt_ = 10., double muEta_ = 2.4){

	std::vector<myobject> outMu_;
	outMu_.clear();
	for (uint i = 0; i < _muon.size(); i++) {
	
			
			double muPt = _muon[i].pt;
			double muEta = _muon[i].eta;
			bool muGlobal = _muon[i].isGlobalMuon;
			bool muTracker = _muon[i].isTrackerMuon;
                        bool pfID = PFMuonID(_muon[i]);

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

std::vector<myobject> WHanalysis::SelectGoodElVector(std::vector<myobject> _electron, bool verb, double elPt_ =10., double elEta_ = 2.4){

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

void WHanalysis::CrossCleanWithMu(std::vector<myobject>* _input, std::vector<myobject> _muon, bool verb, double _maxDeltaR, double _muIso = 0.3, bool _looseMuId = true){
	
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

bool WHanalysis::CheckOverlapLooseElectron(myobject tau, std::vector<myobject> elCollection, double maxR, double isoVal, bool verb){
	
		if(verb) std::cout << "Looking for extra electron!" << std::endl;
		bool overlap = false;
		for(uint j = 0; j < elCollection.size() && !overlap; j++)
		{
			if(verb) std::cout << "Checking ele no. " << j << "/" << elCollection.size() << " pt iso ID: " << elCollection[j].pt << " " << RelIso(elCollection[j])
			 << " " << elCollection[j].numLostHitEleInner << ": dR = " << deltaR(tau, elCollection[j]) << std::endl;
			if(deltaR(tau,elCollection[j])< maxR && RelIso(elCollection[j]) < isoVal && isGoodEl(elCollection[j]) && elCollection[j].numLostHitEleInner <2 ) 
			overlap = true;
		}
	if(verb) std::cout << "extra loose electron returns " << overlap << std::endl; 
	return overlap;	
}

bool WHanalysis::CheckOverlapLooseMuon(myobject tau, std::vector<myobject> muCollection, double maxR, double isoVal){
	
		bool overlap = false;
		for(uint j = 0; j < muCollection.size() && !overlap; j++)
		{
			if(deltaR(tau,muCollection[j])< maxR && RelIso(muCollection[j]) < isoVal &&  isLooseMu(muCollection[j])) 
			overlap = true;
		}
	return overlap;	
}

bool WHanalysis::isGoodMu(myobject mu){

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

bool WHanalysis::isLooseMu(myobject mu){

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

bool WHanalysis::isGoodEl(myobject el){
	        
	        double elPt = el.pt;
                double elEta = el.eta_SC;
                int missingHits = el.numLostHitEleInner;
 //               bool elID = TightEleId(elPt,elEta,el.Id_mvaNonTrg);
                double relIso = RelIso(el);

                if (elPt > 10. && fabs(elEta) < 2.5  && missingHits <=1)
                {
                        return true;
                }else return false;
}

bool WHanalysis::LooseEleId(float pt, float eta, double value){
	bool passingId=false;


	if(pt>10. && fabs(eta)<0.8 && value>0.5)
		passingId=true;
	if(pt>10. && fabs(eta)>=0.8 && fabs(eta)<1.479 && value>0.12)
		passingId=true;
	if(pt>10. && fabs(eta)>=1.479 && value>0.6)
		passingId=true;
	// if(value>10.)cout<<"pt==== "<<pt<<" "<<"eta=== "<<eta<<" "<<"value=== "<<value<<endl;
	return passingId;
}

bool WHanalysis::LooseEleId(myobject o){
	return LooseEleId(o.pt, o.eta_SC,o.Id_mvaNonTrg);
}


bool WHanalysis::AdLepton_sig(std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, myobject Hcand1, myobject Hcand2, myobject Wcand, bool verbose){
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
		if(deltaR(genericMuon[i].eta,genericMuon[i].phi,Wcand.eta,Wcand.phi) < 0.001) continue; // identical object
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
		if(deltaR(genericElectron[i].eta,genericElectron[i].phi,Wcand.eta,Wcand.phi) < 0.001) continue; // identical object

		if(LooseEleId(genericElectron[i]) && genericElectron[i].numLostHitEleInner < 2 && RelIso(genericElectron[i]) < 0.3)
			Ad_lepton=true;
		if(Ad_lepton && verbose) std::cout << "AD LEPTON FAIL!" << std::endl;

	}

	if(verbose) std::cout << "Returning " << Ad_lepton << std::endl;
	return Ad_lepton;
}


void WHanalysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
	
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
	
	if(examineThisEvent) std::cout << "Examining! Event number " << eNumber << " ENTRY: " << m_allEvents << std::endl;


// PU weightting
	double PUWeight = 1.0;
	double nPU = 0.0;
	nPU = m->PUInfo_true;
	if(isSimulation){	
		PUWeight = LumiWeights_->weight( nPU );
		if(IgnorePUW) PUWeight = 1.0;
	}
	
	Hist("h_PU_weight")->Fill(PUWeight);
	Hist("h_nPU_raw")->Fill(m->PUInfo_true);
	Hist("h_nPU_reweight")->Fill(m->PUInfo_true,PUWeight);
	

	bool trigPass;
	trigPass = Trg_MC_12(m,examineThisEvent);
	m_logger << DEBUG <<" Trigger decision " << trigPass << SLogger::endmsg;
	if(!trigPass)
	{
		if(examineThisEvent) std::cout << "Trigger fail! " << examineEvent << std::endl;
		return;
	}
	
	//vertex selection
	std::vector<myobject> vertex = m->Vertex;
	std::vector<myobject> goodVertex = SelectGoodVxVector(vertex);
	short nGoodVx=goodVertex.size();
	
	// at least one good vertex
	if(nGoodVx < 1) return;
	
	// looseMuons
	std::vector<myobject> muon = m->PreSelectedMuons;
	if(examineThisEvent) std::cout << " There are " << muon.size() << " preselected muons " << std::endl;
	m_logger << DEBUG << " There are " << muon.size() << " preselected muons " << SLogger::endmsg;
	std::vector<myobject> genericMuon = SelectGoodMuVector(muon,examineThisEvent);
	if(examineThisEvent) std::cout << " There are " << genericMuon.size() << " selected muons " << std::endl;

	// looseElectrons
	std::vector<myobject> electron = m->PreSelectedElectrons;
	if(examineThisEvent) std::cout << " There are " << electron.size() << " preselected electrons " << std::endl;
	std::vector<myobject> genericElectron = SelectGoodElVector(electron,examineThisEvent);
	
	//overlap cleaning
	CrossCleanWithMu(&genericElectron,genericMuon,examineThisEvent,maxDeltaR);
	if(examineThisEvent) std::cout << " There are " << genericElectron.size() << " selected electrons" << std::endl;

        std::vector<myobject> muonForW;
        std::vector<myobject> muonForH;
 
         for(uint i=0; i<genericMuon.size(); i++){

            bool pfID = PFMuonID(genericMuon.at(i));

            if((genericMuon.at(i)).pt > 20. && pfID){
	       muonForW.push_back(genericMuon.at(i));
               genericMuon.erase(genericMuon.begin()+i);
               i = i-1;
	    } 
         }
         
        for(uint i=0; i<genericMuon.size(); i++){

            bool pfID = PFMuonID(genericMuon.at(i));

            if(pfID){
	       muonForH.push_back(genericMuon.at(i));
               genericMuon.erase(genericMuon.begin()+i);
               i = i-1;
	    } 
         }

	
if(examineThisEvent) std::cout << " There are " << muonForW.size() << " muon for W and " << muonForH.size() << " muon for H " << endl;
        cout << eNumber << endl;

        if( !(muonForH.size() == 1 && muonForW.size() == 1) )
        return;
	
	// list of good taus 
	std::vector<myobject> goodTau;
	goodTau.clear();
	//int muCand=denomMuon.size();
	//int elCand=denomElectron.size();
	std::vector<myobject> tau = m->PreSelectedHPSTaus;
	
	for (uint i = 0; i < tau.size(); i++) {

		double tauPt = tau[i].pt;
		double tauEta = tau[i].eta;
		bool Loose3Hit = (tau[i].byLooseCombinedIsolationDeltaBetaCorr3Hits > 0.5);
		bool DecayMode = (tau[i].discriminationByDecayModeFinding > 0.5);
		
		if (tauPt > 20. && fabs(tauEta) < 2.3 && Loose3Hit && DecayMode){
			goodTau.push_back(tau[i]);
		}
	}
	
        if(examineThisEvent) std::cout << " There are " << goodTau.size() << " selected taus" << std::endl;
        
        if( !(goodTau.size() == 1) )
        return;
        

        // mumutau final state selection

        //leading muon (for W)
	for(uint i=0; i<muonForW.size(); i++){
                if(examineThisEvent) cout << "rel iso is: " << RelIso(muonForW.at(i)) << endl;
		if( fabs(muonForW.at(i).eta) < 1.479 ){
			if( RelIso(muonForW.at(i)) > 0.15 ){
				muonForW.erase(muonForW.begin()+i);
				i = i-1;
			}  
		}
		else if( fabs(muonForW.at(i).eta) > 1.479 ){
			if( RelIso(muonForW.at(i)) > 0.10 ){
				muonForW.erase(muonForW.begin()+i);
				i = i-1;
			}  
		}
	}        

	if(examineThisEvent) std::cout << " There are " << muonForW.size() << " selected muons possibly good for W candidate after RelIso requirement" << std::endl;

        //sub-leading muon (for H)
	for(uint i=0; i<muonForH.size(); i++){
                if(examineThisEvent) cout << "rel iso is: " << RelIso(muonForH.at(i)) << endl;
		if( fabs(muonForH.at(i).eta) < 1.479 ){
			if( RelIso(muonForH.at(i)) > 0.20 ){
				muonForH.erase(muonForH.begin()+i);
				i = i-1;
			}  
		}
		else if( fabs(muonForH.at(i).eta) > 1.479 ){
			if( RelIso(muonForH.at(i)) > 0.15 ){
				muonForH.erase(muonForH.begin()+i);
				i = i-1;
			}  
		}
	}        
	if(examineThisEvent) std::cout << " There are " << muonForH.size() << " selected muons possibly good for H candidate after RelIso requirement" << std::endl;
        
        if( !(muonForH.size() == 1 && muonForW.size() == 1) )
        return;
	

        std::vector<myobject> tauForH;
 
        for(uint i=0; i<goodTau.size(); i++){
		bool LooseEleMVA3 = (tau[i].discriminationByElectronMVA3Loose > 0.5);
		bool TightMuon    = (tau[i].discriminationByMuonTight > 0.5);
		if ( LooseEleMVA3 && TightMuon){
			tauForH.push_back(goodTau.at(i));
                }
        }
        
        if(examineThisEvent) std::cout << " There are " << tauForH.size() << " selected tau possibly good for H candidate" << std::endl;
        if(examineThisEvent) std::cout << " light lepton charges " << std::endl;
        if( !(tauForH.size() == 1) )
        return;
        
        if( (muonForW.at(0)).charge + (muonForH.at(0)).charge == 0 ) return;

        std::vector<myobject> Hcand;
        Hcand.clear();
        Hcand.push_back(muonForH.at(0));
        Hcand.push_back(tauForH.at(0));
        if(examineThisEvent) std::cout << " higgs candidate size " << Hcand.size() << std::endl;

        //b-Tag Veto

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
			double dR1,dR2,dR3;
			dR1=deltaR(jetEta,jetPhi,(muonForW.at(0)).eta,(muonForW.at(0)).phi);
			dR2=deltaR(jetEta,jetPhi,(Hcand.at(0)).eta,(Hcand.at(0)).phi);
			dR3=deltaR(jetEta,jetPhi,(Hcand.at(1)).eta,(Hcand.at(1)).phi);
			if(examineThisEvent) std::cout << " distances are " << dR1 << " " << dR2 << " " << dR3 << std::endl;
			bool overlap = false;
			if(dR1 < 0.4 || dR2 < 0.4 || dR3 < 0.4) overlap = true;
			bTagVeto = !overlap;

		}
	}

	if(examineThisEvent) std::cout << " Before b-tag veto" << std::endl;

	if(bTagVeto)
		return;
	if(examineThisEvent) std::cout << " After b-tag veto" << std::endl;
	if(examineThisEvent) std::cout << " Before additional isolated lepton veto" << std::endl;

        bool Ad_lepton=false;

	if(AdLepton_sig(genericMuon,genericElectron,Hcand.at(0),Hcand.at(1),muonForW.at(0),examineThisEvent)){
		if(examineThisEvent) std::cout << " > j failed overlap check." << std::endl;	
		Ad_lepton=true;
         	}
        if(Ad_lepton) 
           return;
	if(examineThisEvent) std::cout << " After additional isolated lepton veto" << std::endl;


        //define LT regions

        double LT;
        bool aboveEvent = false;
        bool belowEvent = false;
        
        std::vector<myobject> muonForW_below130;
        muonForW_below130.clear();
        std::vector<myobject> Hcand_below130;
        Hcand_below130.clear();
        std::vector<myobject> muonForW_above130;
        muonForW_above130.clear();
        std::vector<myobject> Hcand_above130;
        Hcand_above130.clear();

        LT = (muonForW.at(0)).pt + (Hcand.at(0)).pt + (Hcand.at(1)).pt;
        if(LT < LTValue){
           muonForW_below130.push_back(muonForW.at(0));
           Hcand_below130.push_back(Hcand.at(0));
           Hcand_below130.push_back(Hcand.at(1));
           belowEvent = true;
        }
        if(LT > LTValue){
           muonForW_above130.push_back(muonForW.at(0));
           Hcand_above130.push_back(Hcand.at(0));
           Hcand_above130.push_back(Hcand.at(1));
           aboveEvent = true;
        }

	if(examineThisEvent) {
           if(belowEvent)
           std::cout << " LT < 130 GeV ! scalar pt sum: " << LT << std::endl;
           else if(aboveEvent)
           std::cout << " LT > 130 GeV ! scalar pt sum: " << LT << std::endl;
        }
        

}

