// $Id: CycleCreators.py 344 2012-12-13 13:10:53Z krasznaa $

// Local include(s):
#include "../include/WHanalysis.h"
#include "Corrector_new.h"



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
	DeclareProperty("LTValue_mmt",LTValue_mmt);
	DeclareProperty("LTValue_eet",LTValue_eet);

	DeclareProperty("syncFileName",syncFileName);
	DeclareProperty("doSync",doSync);
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


	// histogram booking
	//Double_t bins[] = { 20, 30, 40, 50, 60, 70, 80, 100, 130, 300 };

	//h_visMass_P1P2P3                                        = Book(TH1D("h_visMass_P1P2P3","H vis mass", 9, bins));

	if(is2011) LumiWeights_ = new reweight::LumiReWeighting("Fall11_PU.root", "dataPileUpHistogram_True_2011.root","mcPU","pileup");
	else LumiWeights_ = new reweight::LumiReWeighting("Summer12_PU_53X.root", "dataPileUpHistogramABCD_True_2012.root","mcPU","pileup");


	//bookkeeping
	lumi.open("lumi.csv");
	current_run=current_lumi=-999;
	eventList_P1P2P3.open("eventList_P1P2P3.list");
	eventList_P1P2F3.open("eventList_P1P2F3.list");
	eventList_P1F2P3.open("eventList_P1F2P3.list");
	eventList_F1P2P3.open("eventList_F1P2P3.list");
	eventList_P1F2F3.open("eventList_P1F2F3.list");
	eventList_F1P2F3.open("eventList_F1P2F3.list");
	eventList_F1F2P3.open("eventList_F1F2P3.list");
	eventList_F1F2F3.open("eventList_F1F2F3.list");

	syncOutTree = new TTree("UCL_tree","UCL_tree");
	//syncOutTree->Branch("o_selected", &o_selected);
	syncOutTree->Branch("o_run", &o_run,"o_run/i");
	syncOutTree->Branch("o_event", &o_event,"o_event/L");
	syncOutTree->Branch("o_lumi", &o_lumi),"o_lumi/i";
	syncOutTree->Branch( "o_weight", &o_weight,"o_weight/D");
	syncOutTree->Branch( "o_id_iso_leadE", &o_id_iso_leadE,"o_id_iso_leadE/D");
	syncOutTree->Branch( "o_id_iso_subLeadE", &o_id_iso_subLeadE,"o_id_iso_subLeadE/D");
	syncOutTree->Branch( "o_isF3", &o_isF3,"o_isF3/i");
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

void WHanalysis::EndInputData( const SInputData& ) throw( SError ) {


	// Lumi weights

	// bookkeeping
	lumi.close();
	ofstream log2;       
	log2.open("total.txt");
	log2 << *m_allEvents << std::endl;
	log2.close();
	eventList_P1P2P3.close();
	eventList_P1P2F3.close();
	eventList_P1F2P3.close();
	eventList_F1P2P3.close();
	eventList_P1F2F3.close();
	eventList_F1P2F3.close();
	eventList_F1F2P3.close();
	eventList_F1F2F3.close();

	syncOut = new TFile("output_tree.root","RECREATE");
	syncOutTree->Write();
	syncOut->Close();

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

std::vector<myobject> WHanalysis::SelectGoodVxVector(std::vector<myobject> _vertex, double _positionRho = 2., int _ndof = 4, double _dZ = 24.){

	std::vector<myobject> outVx_;
	outVx_.clear();	
	for (uint i = 0; i < _vertex.size(); i++) {
		if (_vertex[i].isValid && _vertex[i].position_Rho < _positionRho && _vertex[i].ndof > _ndof && fabs(_vertex[i].z) < _dZ)
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

double WHanalysis::RelIso(myobject mu,bool verb=false){
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

myobject WHanalysis::ClosestInCollection(myobject o1, std::vector<myobject> collection, double max=0.5)
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

std::vector<myobject> WHanalysis::SelectGoodMuVector(std::vector<myobject> _muon, std::vector<myobject> _jets, bool verb, double muPt_ = 5., double muEta_ = 2.4){

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
		//if(verb) std::cout << " pre-muon " << i << " pt eta etaSC: " << muPt << " " 
		//	<< muEta << " pixelHits " << _muon[i].intrkLayerpixel << " btag " << bTag << " dz " << fabs(_muon[i].dz_PV) << std::endl;

		if ((muGlobal || muTracker) && muPt > muPt_ && fabs(muEta) < muEta_ && pixelHits && bTag && dZ ){
			//if(verb) std::cout << " pre-muon " << i << " pt eta etaSC: " << muPt << " " 
			//	<< muEta << std::endl;
			outMu_.push_back(_muon[i]);
		}else{
			//if(verb) std::cout << " pre-_muon no. " << i << " has been rejected because of global|tracker pt eta:" <<
			//	muGlobal << muTracker << " " << muPt << " " << muEta << std::endl; 
		}
	}
	return outMu_;
}


std::vector<myobject> WHanalysis::SelectGoodElVector(std::vector<myobject> _electron, bool verb, double elPt_ =10., double elEta_ = 2.5){

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

void WHanalysis::CrossCleanWithEle(std::vector<myobject>* _ele, std::vector<myobject> _input, bool verb, double _maxDeltaR){

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

bool WHanalysis::TightEleId(float pt, float eta, double value){
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

bool WHanalysis::TightEleId(myobject o){
	return TightEleId(o.pt, o.eta_SC,o.Id_mvaNonTrg);
}

bool WHanalysis::LooseEleId(float pt, float eta, double value){
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

bool WHanalysis::LooseEleId(myobject o){
	//if( o.numLostHitEleInner > 0) return false;
	return LooseEleId(o.pt, o.eta_SC,o.Id_mvaNonTrg);
}

bool WHanalysis::AdMuon_sig(std::vector<myobject> genericMuon, myobject Hcand1, myobject Hcand2, myobject Wcand, bool verbose){

	bool Ad_muon=false;
	if(verbose) std::cout << "Checking additional sig muons!" << std::endl;
	if(verbose) std::cout << "There are " << genericMuon.size() << " additional muons." << std::endl;
	for(uint i = 0; i < genericMuon.size(); i++)
	{
		double dR1= deltaR(genericMuon[i].eta,genericMuon[i].phi,Wcand.eta,Wcand.phi); 
		double dR2= deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand1.eta,Hcand1.phi); 
		double dR3= deltaR(genericMuon[i].eta,genericMuon[i].phi,Hcand2.eta,Hcand2.phi); 

		if(verbose) std::cout << " Mu cand no. " << i << std::endl;
		if(verbose) std::cout << " Isolation is " << RelIso(genericMuon[i]) << std::endl;
		if(verbose) std::cout << " ID is " << PFMuonID(genericMuon[i]) << std::endl;
		if(verbose) std::cout << " dZ is " << fabs((genericMuon[i]).dz_PV) << std::endl;
		if(verbose) std::cout << " Distance to 1st H candidate is " << dR1 << std::endl;
		if(verbose) std::cout << " Distance to 2nd H candidate is " << dR2 << std::endl;
		if(verbose) std::cout << " Distance to W candidate is " << dR3 << std::endl;
		if(RelIso(genericMuon[i]) < 0.15 && PFMuonID(genericMuon[i]) && fabs((genericMuon[i]).dz_PV) < 0.2 && (dR1 > 0.4 && dR2 > 0.4 && dR3 > 0.4))
			Ad_muon=true;
	}
	return Ad_muon;
}

bool WHanalysis::AdElectron_sig(std::vector<myobject> genericElectron, myobject Hcand1, myobject Hcand2, myobject Wcand, bool verbose){

	bool Ad_electron=false;
	if(verbose) std::cout << "Checking additional sig electrons!" << std::endl;
	if(verbose) std::cout << "There are " << genericElectron.size() << " additional electrons." << std::endl;
	for(uint i = 0; i < genericElectron.size(); i++)
	{
		if(deltaR(genericElectron[i],Hcand1)==0) continue;
		if(deltaR(genericElectron[i],Wcand)==0) continue;

		double dR1= deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand1.eta,Hcand1.phi); 
		double dR2= deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand2.eta,Hcand2.phi); 
		double dR3= deltaR(genericElectron[i].eta,genericElectron[i].phi,Wcand.eta,Wcand.phi); 

		if(verbose) std::cout << " Ele cand no. " << i << std::endl;
		if(verbose) std::cout << " Isolation is " << RelIso(genericElectron[i]) << std::endl;
		if(verbose) std::cout << " Distance to 1st H candidate is " << dR1 << std::endl;
		if(verbose) std::cout << " Distance to 2nd H candidate is " << dR2 << std::endl;
		if(verbose) std::cout << " Distance to W candidate is " << dR3 << std::endl;
		if(RelIso(genericElectron[i]) < 0.30 && (dR1 > 0.4 && dR2 > 0.4 && dR3 > 0.4))
			Ad_electron=true;
	}
	return Ad_electron;
}

bool WHanalysis::AdTau_sig(std::vector<myobject> genericTau, myobject Hcand1, myobject Hcand2, myobject Wcand, bool verbose){

	bool Ad_tau=false;
	if(verbose) std::cout << "Checking additional sig taus!" << std::endl;
	if(verbose) std::cout << "There are " << genericTau.size() << " additional taus." << std::endl;
	for(uint i = 0; i < genericTau.size(); i++)
	{
		double dR1= deltaR(genericTau[i].eta,genericTau[i].phi,Wcand.eta,Wcand.phi); 
		double dR2= deltaR(genericTau[i].eta,genericTau[i].phi,Hcand1.eta,Hcand1.phi); 
		double dR3= deltaR(genericTau[i].eta,genericTau[i].phi,Hcand2.eta,Hcand2.phi); 
		bool tauPt = (genericTau[i]).pt > 20.;
		bool tauEta = fabs((genericTau[i]).eta) < 2.5;
		bool tauDZ = (genericTau[i]).dz_Ver_match < 0.2;
		bool Loose3Hit = ((genericTau[i]).byLooseCombinedIsolationDeltaBetaCorr3Hits > 0.5);

		bool pass = tauPt && tauEta && fabs(tauDZ) && Loose3Hit;

		if(!pass) continue;
		if(deltaR(genericTau[i],Hcand2)==0) continue;

		if(verbose) std::cout << " Tau cand no. " << i << "pt/eta/phi:" << genericTau[i].pt << "/"
			<< genericTau[i].eta << "/" << genericTau[i].phi << std::endl;
		if(verbose) std::cout << " Distance to 1st H candidate is " << dR1 << std::endl;
		if(verbose) std::cout << " Distance to 2nd H candidate is " << dR2 << std::endl;
		if(verbose) std::cout << " Distance to W candidate is " << dR3 << std::endl;

		if(dR1 > 0.4 && dR2 > 0.4 && dR3 > 0.4 && pass)
			Ad_tau=true;
	}
	return Ad_tau;
}


void WHanalysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
      
        //if(m->eventNumber!=1971379)
	//	return;

	// bookkepping part
	++m_allEvents;
	if(m->runNumber!=current_run || m->lumiNumber!=current_lumi){
		lumi << m->runNumber << " " << m->lumiNumber << std::endl;
		current_run=m->runNumber;
		current_lumi=m->lumiNumber;
	}

	m_logger << DEBUG << " Now executing event " << m->eventNumber << " in a run " << m->runNumber << SLogger::endmsg;

        o_run = m->runNumber;
        o_lumi = m->lumiNumber;
        o_event = m->eventNumber;

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

	std::vector<myobject> vetoElectron;
	vetoElectron.clear();
	for(uint i=0; i < genericElectron.size(); i++){
		if( LooseEleId( genericElectron[i] ) ){
			vetoElectron.push_back(genericElectron[i]);
		}     
	}

	if(examineThisEvent) std::cout << genericElectron.size() << " generic electrons (NO ID APPLIED) --> good for SIGNAL or FAKE candidates!" << std::endl;
	if(examineThisEvent) std::cout << vetoElectron.size() << " veto electrons (LOOSE ID APPLIED) --> good for VETO! " << std::endl;
	m_logger << DEBUG << " veto electron " << SLogger::endmsg;

	//overlap cleaning: selected muons and selected electrons (with loose id) 
	//CrossCleanWithMu(&genericElectron,vetoMuon,examineThisEvent,maxDeltaR);
	//if(examineThisEvent) std::cout << genericElectron.size() << " generic electrons after the MU-ELE x-Cleaning" << std::endl;
	//CrossCleanWithMu(&vetoElectron,vetoMuon,examineThisEvent,maxDeltaR);
	//if(examineThisEvent) std::cout << vetoElectron.size() << " veto electrons after the MU-ELE x-Cleaning" << std::endl;
	//m_logger << DEBUG << " cross cleaning mu 2 " << SLogger::endmsg;

	//overlap cleaning: selected electrons (with loose id) and taus 
	if(examineThisEvent) std::cout << tau.size() << " preselected taus " << std::endl;
	CrossCleanWithEle(&vetoElectron,tau,examineThisEvent,0.4);
	if(examineThisEvent) std::cout << tau.size() << " preselected taus after the ELE-TAU x-Cleaning" << std::endl;
	m_logger << DEBUG << " cross cleaning tau " << SLogger::endmsg;


	//select good electron 
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
		cout << "after track req" << endl;
		if(examineThisEvent) std::cout  << goodElectron.size() << " good electron " << endl;
		if(examineThisEvent) std::cout << genericElectron.size() << " generic electron " << endl;
	}


	//select electrons for W: signal and/or fake

	if( goodElectron.size() < 2 )
		return;
	m_logger << DEBUG << " i*************** GOODODOODOOD " << SLogger::endmsg;

	electronW_sig.clear();
	electronH_sig.clear();
	electronW_fake.clear();
	electronH_fake.clear();

	for(uint i=0; i<goodElectron.size(); i++){
		bool etaR = fabs((goodElectron.at(i).eta)) < 1.479;
		bool relIsoLoose_W = RelIso(goodElectron.at(i)) < 0.15;
		bool relIsoTight_W = RelIso(goodElectron.at(i)) < 0.10;
		bool isoTight_W = !etaR && relIsoTight_W;
		bool isoLoose_W = etaR && relIsoLoose_W;
		bool relIsoLoose_H = RelIso(goodElectron.at(i)) < 0.20;
		bool relIsoTight_H = RelIso(goodElectron.at(i)) < 0.15;
		bool isoTight_H = !etaR && relIsoTight_H;
		bool isoLoose_H = etaR && relIsoLoose_H;
		bool pt20 = goodElectron[i].pt > 20.;
		bool pt10 = goodElectron[i].pt > 10.;
		bool looseEleID = LooseEleId(goodElectron.at(i));
		bool tightEleID = TightEleId(goodElectron.at(i));

		if(examineThisEvent){ 
			cout << "ele pt: " << goodElectron[i].pt << " eta " << goodElectron[i].eta << " phi " << goodElectron[i].phi <<
				" rel iso is: " << RelIso(goodElectron.at(i),examineThisEvent) <<
				" loose ID " << looseEleID << " tight ID " << tightEleID << endl;}
		if(examineThisEvent) 
			cout << "isoTight_H/isoLoose_H " << isoTight_H << " - " << isoLoose_H << endl;
		if(examineThisEvent) 
			cout << "isoTight_W/isoLoose_W " << isoTight_W << " - " << isoLoose_W << endl;

		if(examineThisEvent) cout << "eta: " << fabs((goodElectron.at(i).eta)) << endl;
		if(examineThisEvent) cout << "iso loose W (0.15): " << relIsoLoose_W << endl;
		if(examineThisEvent) cout << "iso tight W (0.10): " << relIsoTight_W << endl;
		if(examineThisEvent) cout << "eta and iso tight W: " << isoTight_W << endl;
		if(examineThisEvent) cout << "eta and iso loose W: " << isoLoose_W << endl;
		if(examineThisEvent) cout << "iso loose H (0.20): " << relIsoLoose_H << endl;
		if(examineThisEvent) cout << "iso tight H (0.15): " << relIsoTight_H << endl;
		if(examineThisEvent) cout << "eta and iso tight H: " << isoTight_H << endl;
		if(examineThisEvent) cout << "eta and iso loose H: " << isoLoose_H << endl;
		if(examineThisEvent) cout << "pt20: " << pt20 << endl;
		if(examineThisEvent) cout << "pt10: " << pt10 << endl;
		if(examineThisEvent) cout << "loose ele ID: " << looseEleID << endl;
		if(examineThisEvent) cout << "loose tight ID: " << tightEleID << endl;

		bool isWsig = false; bool isHsig = false; bool isWfake = false; bool isHfake = false;

		if( pt20 && tightEleID && (isoTight_W || isoLoose_W)) isWsig = true;

		if( pt10 && looseEleID && (isoTight_H || isoLoose_H)) isHsig = true;

		if( pt20 ){
			if( !tightEleID ) isWfake = true;
			else{
				if( etaR ){
					if( !relIsoLoose_W ) isWfake = true;}
				else{
					if( !relIsoTight_W ) isWfake = true;}

			}
		}
		if( pt10 ){
			if( !looseEleID ) isHfake = true;
			else{
				if( etaR ){
					if( !relIsoLoose_H ) isHfake = true;}
				else{
					if( !relIsoTight_H ) isHfake = true;}

			}
		}

		if( isWsig ) electronW_sig.push_back(goodElectron.at(i));
		if( isHsig ) electronH_sig.push_back(goodElectron.at(i));
		if( isWfake ) electronW_fake.push_back(goodElectron.at(i));
		if( isHfake ) electronH_fake.push_back(goodElectron.at(i));

	}

	int total1 = electronW_sig.size()+electronH_sig.size()+electronW_fake.size()+electronH_fake.size();
	if(total1 < 2)
		return;

	if(examineThisEvent) cout << " goodElectron size " << goodElectron.size() << endl;
	if(examineThisEvent) cout << " electronW_sig size " << electronW_sig.size()  << endl;
	if(examineThisEvent) cout << " electronH_sig size " << electronH_sig.size()  << endl;
	if(examineThisEvent) cout << " electronW_fake size " << electronW_fake.size()  << endl;
	if(examineThisEvent) cout << " electronH_fake size " << electronH_fake.size()  << endl;

	double Z_mass_SS = 90.54;

	//check p1p2
	p1p2.clear();
	for(uint i=0; i<electronW_sig.size(); i++){
		if( !electronW_sig[i].hasTrgObject_loose ) continue;
		for(uint j=0; j<electronH_sig.size(); j++){
			std::pair<myobject,myobject> tmpPair;

			if(examineThisEvent) cout << "w sig " << electronW_sig[i].pt << " h sig " << electronH_sig[j].pt << endl;
			if(examineThisEvent) cout << "dR " << deltaR(electronW_sig[i],electronH_sig[j]) << endl;
			if(examineThisEvent) cout << "charge " << electronW_sig[i].charge*electronH_sig[j].charge << endl;
			if(examineThisEvent) cout << electronW_sig[i].TrgObjectPt_loose << "/" << electronH_sig[j].TrgObjectPt_loose << std::endl;
			if(examineThisEvent) cout << "Pair mass : " << fabs(PairMass(electronW_sig[i],electronH_sig[j])-Z_mass_SS) << endl;

			if(deltaR(electronW_sig[i],electronH_sig[j])==0) continue;
			if( electronW_sig[i].pt < electronH_sig[j].pt ) continue;
			if( electronW_sig[i].charge*electronH_sig[j].charge < 0 ) continue;
			if( !electronH_sig[j].hasTrgObject_loose ) continue;
			if( fabs(PairMass(electronW_sig[i],electronH_sig[j])-Z_mass_SS) < 10 ) continue;
			if( PairMass(electronW_sig[i],electronH_sig[j]) < 20. ) continue;
			if(examineThisEvent) cout << "GOOD!*" << endl;
			tmpPair=std::make_pair(electronW_sig[i],electronH_sig[j]);
			p1p2.push_back(tmpPair);                   
		}
	}

	//check p1f2
	p1f2.clear();
	for(uint i=0; i<electronW_sig.size(); i++){
		if( !electronW_sig[i].hasTrgObject_loose ) continue;
		for(uint j=0; j<electronH_fake.size(); j++){
			std::pair<myobject,myobject> tmpPair;

			if(examineThisEvent) cout << "w sig " << electronW_sig[i].pt << " h fake " << electronH_fake[j].pt << endl;
			if(examineThisEvent) cout << "dR " << deltaR(electronW_sig[i],electronH_fake[j]) << endl;
			if(examineThisEvent) cout << "charge " << electronW_sig[i].charge*electronH_fake[j].charge << endl;
			if(examineThisEvent) cout << electronW_sig[i].TrgObjectPt_loose << "/" << electronH_fake[j].TrgObjectPt_loose << std::endl;
			if(examineThisEvent) cout << "Pair mass : " << fabs(PairMass(electronW_sig[i],electronH_fake[j])-Z_mass_SS) << endl;

			if(deltaR(electronW_sig[i],electronH_fake[j])==0) continue;
			if( electronW_sig[i].pt < electronH_fake[j].pt ) continue;
			if( electronW_sig[i].charge*electronH_fake[j].charge < 0 ) continue;
			if( !electronH_fake[j].hasTrgObject_loose ) continue;
			if( fabs(PairMass(electronW_sig[i],electronH_fake[j])-Z_mass_SS) < 10 ) continue;
			if( PairMass(electronW_sig[i],electronH_fake[j]) < 20. ) continue;
			if(examineThisEvent) cout << "GOOD!*" << endl;
			tmpPair=std::make_pair(electronW_sig[i],electronH_fake[j]);
			p1f2.push_back(tmpPair);                   
		}
	}

	//check f1p2
	f1p2.clear();
	for(uint i=0; i<electronW_fake.size(); i++){
		if( !electronW_fake[i].hasTrgObject_loose ) continue;
		for(uint j=0; j<electronH_sig.size(); j++){
			std::pair<myobject,myobject> tmpPair;

			if(examineThisEvent) cout << "w fake " << electronW_fake[i].pt << " h sig " << electronH_sig[j].pt << endl;
			if(examineThisEvent) cout << "dR " << deltaR(electronW_fake[i],electronH_sig[j]) << endl;
			if(examineThisEvent) cout << "charge " << electronW_fake[i].charge*electronH_sig[j].charge << endl;
			if(examineThisEvent) cout << electronW_fake[i].TrgObjectPt_loose << "/" << electronH_sig[j].TrgObjectPt_loose << std::endl;
			if(examineThisEvent) cout << "Pair mass : " << fabs(PairMass(electronW_fake[i],electronH_sig[j])-Z_mass_SS) << endl;

			if(deltaR(electronW_fake[i],electronH_sig[j])==0) continue;
			if( electronW_fake[i].pt < electronH_sig[j].pt ) continue;
			if( electronW_fake[i].charge*electronH_sig[j].charge < 0 ) continue;
			if( !electronH_sig[j].hasTrgObject_loose ) continue;
			if( fabs(PairMass(electronW_fake[i],electronH_sig[j])-Z_mass_SS) < 10 ) continue;
			if( PairMass(electronW_fake[i],electronH_sig[j]) < 20. ) continue;
			if(examineThisEvent) cout << "GOOD!*" << endl;
			tmpPair=std::make_pair(electronW_fake[i],electronH_sig[j]);
			f1p2.push_back(tmpPair);                   
		}
	}

	//check f1f2
	f1f2.clear();
	for(uint i=0; i<electronW_fake.size(); i++){
		if( !electronW_fake[i].hasTrgObject_loose ) continue;
		for(uint j=0; j<electronH_fake.size(); j++){
			std::pair<myobject,myobject> tmpPair;

			if(examineThisEvent) cout << "w fake " << electronW_fake[i].pt << " h fake " << electronH_fake[j].pt << endl;
			if(examineThisEvent) cout << "dR " << deltaR(electronW_fake[i],electronH_fake[j]) << endl;
			if(examineThisEvent) cout << "charge " << electronW_fake[i].charge*electronH_fake[j].charge << endl;
			if(examineThisEvent) cout << electronW_fake[i].TrgObjectPt_loose << "/" << electronH_fake[j].TrgObjectPt_loose << std::endl;
			if(examineThisEvent) cout << "Pair mass : " << fabs(PairMass(electronW_fake[i],electronH_fake[j])-Z_mass_SS) << endl;

			if(deltaR(electronW_fake[i],electronH_fake[j])==0) continue;
			if( electronW_fake[i].pt < electronH_fake[j].pt ) continue;
			if( electronW_fake[i].charge*electronH_fake[j].charge < 0 ) continue;
			if( !electronH_fake[j].hasTrgObject_loose ) continue;
			if( fabs(PairMass(electronW_fake[i],electronH_fake[j])-Z_mass_SS) < 10 ) continue;
			if( PairMass(electronW_fake[i],electronH_fake[j]) < 20. ) continue;
			if(examineThisEvent) cout << "GOOD!*" << endl;
			tmpPair=std::make_pair(electronW_fake[i],electronH_fake[j]);
			f1f2.push_back(tmpPair);                   
		}
	}

	if(examineThisEvent) cout << " p1p2 " << p1p2.size()  << endl;
	if(examineThisEvent) cout << " p1f2 " << p1f2.size()  << endl;
	if(examineThisEvent) cout << " f1p2 " << f1p2.size()  << endl;
	if(examineThisEvent) cout << " f1f2 " << f1f2.size()  << endl;

	allPair.clear();
	pair_cat.clear();

	for(uint i=0;i<p1p2.size();i++){
		allPair.push_back(p1p2[i]);
		pair_cat.push_back("p1p2");
	}
	for(uint i=0;i<f1p2.size();i++){
		allPair.push_back(f1p2[i]);
		pair_cat.push_back("f1p2");
	}
	for(uint i=0;i<p1f2.size();i++){
		allPair.push_back(p1f2[i]);
		pair_cat.push_back("p1f2");
	}
	for(uint i=0;i<f1f2.size();i++){
		allPair.push_back(f1f2[i]);
		pair_cat.push_back("f1f2");
	}
	if(examineThisEvent) cout << " all pair: size --> " << allPair.size()  << endl;
	if(examineThisEvent) cout << " pair_cat: size --> " << pair_cat.size()  << endl;

	//select good taus 
	std::vector<myobject> goodTau;
	goodTau.clear();
	for (uint i = 0; i < tau.size(); i++) {

		double tauPt = (tau.at(i)).pt;
		double tauEta = (tau.at(i)).eta;
		double tauDZ = (tau.at(i)).dz_Ver_match;
		bool DecayMode = ((tau.at(i)).discriminationByDecayModeFinding > 0.5);

		if (tauPt > 20. && fabs(tauEta) < 2.3 && DecayMode && fabs(tauDZ) < 0.2){
			if(examineThisEvent) std::cout << " -> Tau Selected (NO ISO APPLIED)!" << std::endl;
			goodTau.push_back(tau.at(i));
			//tau.erase(tau.begin()+i);
			//i=i-1;
		}
	}
	if(examineThisEvent) std::cout << goodTau.size() << " selected SIGNAL taus" << std::endl;

	if( goodTau.size() == 0 ){
		if(examineThisEvent){
			std::cout << "NO good taus!" << std::endl;
		}
		return;
	}

	triplets.clear();
	triplets_cat.clear();
	cat = "";

	for(uint ipair=0; ipair < allPair.size(); ipair++){ 
		std::vector<myobject> tmptriplet;
		for(uint i=0; i<goodTau.size(); i++){
			tmptriplet.clear();
			cat = "";
			bool LooseEleMVA3 = ((goodTau.at(i)).discriminationByElectronMVA3Loose > 0.5);
			bool MediumEleMVA3 = ((goodTau.at(i)).discriminationByElectronMVA3Medium > 0.5);
			bool TightEleMVA3 = ((goodTau.at(i)).discriminationByElectronMVA3Tight > 0.5);
			bool TightMuon    = ((goodTau.at(i)).discriminationByMuonTight > 0.5);
			bool LooseMuon    = ((goodTau.at(i)).discriminationByMuonLoose > 0.5);
			bool Loose3Hit = ((goodTau.at(i)).byLooseCombinedIsolationDeltaBetaCorr3Hits > 0.5); // ISOLATION !

			bool charge = goodTau[i].charge*(allPair[ipair].second).charge < 0; // tau OS sign cut

			double mass1 = fabs(PairMass((allPair[ipair].first),goodTau.at(i)) - Z_mass_SS);
			double mass2 = fabs(PairMass((allPair[ipair].second),goodTau.at(i)) - Z_mass_SS);

			if(examineThisEvent) std::cout << "******** tau n " << i << " ********" << endl; 
			if(examineThisEvent) std::cout << "pt " << goodTau[i].pt << endl; 
			if(examineThisEvent) std::cout << "TightEleMVA3 " << TightEleMVA3 << endl; 
			if(examineThisEvent) std::cout << "MediumEleMVA3 " << MediumEleMVA3<< endl; 
			if(examineThisEvent) std::cout << "LooseEleMVA3 "<< LooseEleMVA3 << endl; 
			if(examineThisEvent) std::cout << "Loose3Hit " << Loose3Hit << endl;
			if(examineThisEvent) std::cout << "mass1 " << mass1 << endl;
			if(examineThisEvent) std::cout << "mass2 " << mass2 << endl;
			if(examineThisEvent) std::cout << "charge " << charge << endl;
			if(examineThisEvent) std::cout << "dR1 " << deltaR(allPair[ipair].first,goodTau[i]) << endl;
			if(examineThisEvent) std::cout << "dR2 " << deltaR(allPair[ipair].second,goodTau[i]) << endl;
			if(examineThisEvent) std::cout << "pair mass " << PairMass(allPair[ipair].second,goodTau[i]) << endl;
 
			if(deltaR(allPair[ipair].first,goodTau[i]) < 0.5) continue;
			if(deltaR(allPair[ipair].second,goodTau[i]) < 0.5) continue;
			if(PairMass(allPair[ipair].second,goodTau[i]) < 20.) continue;

			if(examineThisEvent) std::cout << "TAU survived! pt: " << goodTau[i].pt << endl; 

			if( mass1 < 10. || mass2 < 10.){
				if ( TightEleMVA3 && LooseMuon && charge ){
					if( Loose3Hit ) {
						if(examineThisEvent) std::cout << "1^ case signal: tau n " << i << endl; 
						tmptriplet.push_back(allPair[ipair].first);
						tmptriplet.push_back(allPair[ipair].second);
						tmptriplet.push_back(goodTau[i]);
						triplets.push_back(tmptriplet);
						cat = pair_cat[ipair]+"p3";
						if(examineThisEvent) std::cout << "cat???? " << cat << endl; 
						triplets_cat.push_back(cat);
						tmptriplet.clear();
						cat = "";
					}else{
						if(examineThisEvent) std::cout << "1^ case fake: tau n " << i << endl; 
						tmptriplet.push_back(allPair[ipair].first);
						tmptriplet.push_back(allPair[ipair].second);
						tmptriplet.push_back(goodTau[i]);
						triplets.push_back(tmptriplet);
						cat = pair_cat[ipair]+"f3";
						if(examineThisEvent) std::cout << "cat???? " << cat << endl; 
						triplets_cat.push_back(cat);
						tmptriplet.clear();
						cat = "";
					}
				}
			}
			else if( mass1 < 20. || mass2 < 20. ){
				if ( MediumEleMVA3 && LooseMuon && charge ){
					if( Loose3Hit ) {
						if(examineThisEvent) std::cout << "2^ case signal: tau n " << i << endl; 
						tmptriplet.push_back(allPair[ipair].first);
						tmptriplet.push_back(allPair[ipair].second);
						tmptriplet.push_back(goodTau[i]);
						triplets.push_back(tmptriplet);
						cat = pair_cat[ipair]+"p3";
						if(examineThisEvent) std::cout << "cat???? " << cat << endl; 
						triplets_cat.push_back(cat);
						tmptriplet.clear();
						cat = "";
					}else{
						if(examineThisEvent) std::cout << "2^ case fake: tau n " << i << endl; 
						tmptriplet.push_back(allPair[ipair].first);
						tmptriplet.push_back(allPair[ipair].second);
						tmptriplet.push_back(goodTau[i]);
						triplets.push_back(tmptriplet);
						cat = pair_cat[ipair]+"f3";
						if(examineThisEvent) std::cout << "cat???? " << cat << endl; 
						triplets_cat.push_back(cat);
						tmptriplet.clear();
						cat = "";
					}
				}
			}
			else{
				if ( LooseEleMVA3 && LooseMuon && charge ){
					if( Loose3Hit ) {
						if(examineThisEvent) std::cout << "3^ case signal: tau n " << i << endl; 
						tmptriplet.push_back(allPair[ipair].first);
						tmptriplet.push_back(allPair[ipair].second);
						tmptriplet.push_back(goodTau[i]);
						triplets.push_back(tmptriplet);
						cat = pair_cat[ipair]+"p3";
						if(examineThisEvent) std::cout << "cat???? " << cat << endl; 
						triplets_cat.push_back(cat);
						tmptriplet.clear();
						cat = "";
					}else{
						if(examineThisEvent) std::cout << "3^ case fake: tau n " << i << endl; 
						tmptriplet.push_back(allPair[ipair].first);
						tmptriplet.push_back(allPair[ipair].second);
						tmptriplet.push_back(goodTau[i]);
						triplets.push_back(tmptriplet);
						cat = pair_cat[ipair]+"f3";
						if(examineThisEvent) std::cout << "cat???? " << cat << endl; 
						triplets_cat.push_back(cat);
						tmptriplet.clear();
						cat = "";
					}
				}
			}
		}
	}
	if(examineThisEvent) std::cout << "how many triplets? " << triplets.size() << std::endl;

	if( triplets.size() == 0){
		if(examineThisEvent){
			std::cout << "No triplet found! BYE BYE!" << std::endl;
		}
		return;
	}


	//apply VETOS!
	for(uint itrip=0; itrip < triplets.size(); itrip++){ 
		if(AdMuon_sig(vetoMuon,triplets[itrip].at(1),triplets[itrip].at(0),triplets[itrip].at(2),examineThisEvent)){
			triplets.erase(triplets.begin()+itrip);
			triplets_cat.erase(triplets_cat.begin()+itrip);
			itrip=itrip-1;
		}
	}
	if( triplets.size() == 0) return;
	if(examineThisEvent) std::cout << "failed muon veto" << std::endl;
	if(examineThisEvent) std::cout << "how many triplets? " << triplets.size() << std::endl;

	for(uint itrip=0; itrip < triplets.size(); itrip++){ 
		if(AdElectron_sig(vetoElectron,triplets[itrip].at(1),triplets[itrip].at(0),triplets[itrip].at(2),examineThisEvent)){
			triplets.erase(triplets.begin()+itrip);
			triplets_cat.erase(triplets_cat.begin()+itrip);
			itrip=itrip-1;
		}
	}
	if( triplets.size() == 0) return;
	if(examineThisEvent) std::cout << "failed electron veto" << std::endl;
	if(examineThisEvent) std::cout << "how many triplets? " << triplets.size() << std::endl;

	for(uint itrip=0; itrip < triplets.size(); itrip++){ 
		if(AdTau_sig(tau,triplets[itrip].at(1),triplets[itrip].at(0),triplets[itrip].at(2),examineThisEvent)){
			triplets.erase(triplets.begin()+itrip);
			triplets_cat.erase(triplets_cat.begin()+itrip);
			itrip=itrip-1;
		}
	}
	if( triplets.size() == 0) return;
	if(examineThisEvent) std::cout << "failed tau veto" << std::endl;
	if(examineThisEvent) std::cout << "how many triplets? " << triplets.size() << std::endl;
	if(examineThisEvent) std::cout << "how many categories? " << triplets_cat.size() << "..maybe one! " << triplets_cat[0] << std::endl;


	//b-Tag Veto
	nJets.clear();
	for(uint itrip=0; itrip < triplets.size(); itrip++){ 
		int count_Jets = 0;
		bool bTagVeto = false;
		for (uint i = 0; i < jet.size() && !bTagVeto; i++) {
			double jetPt = jet[i].pt;
			double jetEta = jet[i].eta;
			double jetPhi = jet[i].phi;
			double bTag = jet[i].bDiscriminatiors_CSV;
			double PUjetID = jet[i].puJetIdLoose;
			double dR1,dR2,dR3;
			dR1=deltaR(jet.at(i),triplets[itrip].at(0));
			dR2=deltaR(jet.at(i),triplets[itrip].at(1));
			dR3=deltaR(jet.at(i),triplets[itrip].at(2));
			if(examineThisEvent) std::cout << "jet pt " << jetPt << "jet eta " << jetEta << "btag " << bTag << "PU jet ID" << std::endl;

			if(jetPt > 20. && fabs(jetEta) < 2.4 && PUjetID){
				if(dR1 > 0.4 && dR2 > 0.4 && dR3 > 0.4) count_Jets++;
				if(bTag > bTagValue){
					if(examineThisEvent) std::cout << "candidate b-jet" << std::endl;
					if(examineThisEvent) std::cout << " distances are " << dR1 << " " << dR2 << " " << dR3 << std::endl;
					bool overlap = false;
					if(dR1 < 0.4 || dR2 < 0.4 || dR3 < 0.4){
						overlap = true;
					}
					bTagVeto = !overlap;
				}
			}
		}
                nJets.push_back(count_Jets);
		if(examineThisEvent) std::cout << " nJets.size() " << nJets.size() << " - value " << nJets[itrip] <<  std::endl;
		if(bTagVeto){
			if(examineThisEvent) std::cout << " b-jet found! " << std::endl;
			triplets.erase(triplets.begin()+itrip);
			triplets_cat.erase(triplets_cat.begin()+itrip);
			nJets.erase(nJets.begin()+itrip);
			itrip=itrip-1;
		}
	}

	if( triplets.size() == 0 ) return;
	if(examineThisEvent) std::cout << " After b-tag veto" << std::endl;
	if(examineThisEvent) std::cout << "how many triplets? " << triplets.size() << std::endl;
	if(examineThisEvent) std::cout << "how many categories? " << triplets_cat.size() << std::endl;

        electronLead.clear();
	electronSubLead.clear();
	tauH.clear();
	bool isP1P2P3=false; 
	bool isF1P2P3=false; 
	bool isP1F2P3=false;
	bool isP1P2F3=false; 
	bool isP1F2F3=false; 
	bool isF1F2P3=false; 
	bool isF1P2F3=false; 
	bool isF1F2F3=false; 

	int SigPos = -1;

	for(uint itrip=0; itrip < triplets.size(); itrip++){ 
		if(examineThisEvent) std::cout << triplets_cat[itrip]  << std::endl;
		if(triplets_cat[itrip]=="p1p2p3"){
			SigPos = itrip;
			break;
		}
	}

	if(SigPos != -1){
		electronLead.push_back(triplets[SigPos].at(0));
		electronSubLead.push_back(triplets[SigPos].at(1));
		tauH.push_back(triplets[SigPos].at(2));
		triplets.clear();
		triplets_cat.clear();
                isP1P2P3 = true;
	}else{
                if(triplets.size()>1) std::cout << " DIO CANE PIu DI UNO " << m->eventNumber << std::endl;
		for(uint itrip=0; itrip < triplets.size(); itrip++){ 
			electronLead.push_back(triplets[itrip].at(0));
			electronSubLead.push_back(triplets[itrip].at(1));
			tauH.push_back(triplets[itrip].at(2));
		}
	}

	if(examineThisEvent) std::cout << triplets_cat.size()  << std::endl;
	if(examineThisEvent) std::cout << "eleLeadSIZE/eleSubLeadSIZE/tauSIZE: " << electronLead.size()<<"/"<<electronSubLead.size()<<"/"<<tauH.size()<< std::endl;

	for(uint itrip=0; itrip < electronLead.size(); itrip++){  
		if(triplets_cat[itrip] == "p1f2f3" ) isP1F2F3 = true;
		if(triplets_cat[itrip] == "f1p2f3" ) isF1P2F3 = true;
		if(triplets_cat[itrip] == "f1f2p3" ) isF1F2P3 = true;
		if(triplets_cat[itrip] == "f1f2f3" ) isF1F2F3 = true;
		if(triplets_cat[itrip] == "f1p2p3" ) isF1P2P3 = true;
		if(triplets_cat[itrip] == "p1f2p3" ) isP1F2P3 = true;
		if(triplets_cat[itrip] == "p1p2f3" ) isP1P2F3 = true;
		if(examineThisEvent) std::cout << "category: " << triplets_cat[itrip] << std::endl;


		double maxPt_Lead;
		double maxPt_SubLead;

		double LT;
		double eleW_SF;
		double eleH_SF;
		double final_weight;
		closestJet_Lead.clear();
		closestJet_SubLead.clear();

		if(isSimulation && !IgnoreSF && !IgnorePUW){
			eleW_SF = (Cor_ID_Iso_Ele_Loose_2012_53X(electronLead[itrip])) * (Corr_Trg_Ele_2012_53X(electronLead[itrip])); 
			eleH_SF = (Cor_ID_Iso_Ele_Tight_2012_53X(electronSubLead[itrip])) * (Corr_Trg_Ele_2012_53X(electronSubLead[itrip]));
			final_weight = PUWeight * eleW_SF * eleH_SF;
		}else
			final_weight = PUWeight;

		LT = electronLead[itrip].pt + electronSubLead[itrip].pt + tauH[itrip].pt;
		o_pt_leadE = electronLead[itrip].pt; 
		o_pt_subLeadE = electronSubLead[itrip].pt;
		o_pt_tH = tauH[itrip].pt;
		o_mass = PairMass(electronSubLead[itrip],tauH[itrip]); 
		o_LT = LT;
		o_weight = final_weight;
		//o_selected = 1;

		if( isP1P2P3 || isP1P2F3 ){
			if(examineThisEvent) std::cout << " isP1P2P3 or isP1P2F3 ? " << isP1P2P3 << " - " << isP1P2F3 << std::endl;
			if(examineThisEvent) std::cout << " Electron Lead pt: " << electronLead[itrip].pt << std::endl;
			if(examineThisEvent) std::cout << " Electron SubLead pt: " << electronSubLead[itrip].pt << std::endl;

			if(isP1P2P3){
				o_isF3 = 0;
				eventList_P1P2P3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ;
				if(examineThisEvent) std::cout << " SIGNAL FOUND !!! --> event selected as SIGNAL " << std::endl;
			}
			else{
				eventList_P1P2F3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
				o_isF3 = 1;
			}
			o_id_iso_leadE = 1; o_id_iso_subLeadE = 1;
			o_pt_jet_leadE = -1; o_pt_jet_subLeadE = -1;
			o_njets = nJets[itrip];
			o_maxPt_leadE = electronLead[itrip].pt;
			o_maxPt_subLeadE = electronSubLead[itrip].pt;
			syncOutTree->Fill(); 
		}

		if( isF1P2P3 || isF1P2F3){
			if(examineThisEvent) std::cout << " isF1P2P3 or isF1P2F3 ? " << isF1P2P3 << " - " << isF1P2F3 << std::endl;
			if(examineThisEvent) std::cout << " Electron Lead pt: " << electronLead[itrip].pt << std::endl;

			if( isF1P2P3 ){
				if(examineThisEvent) std::cout << " F1P2P3 FOUND !!! " << std::endl;
				closestJet_Lead.push_back(ClosestInCollection(electronLead[itrip],m->RecPFJetsAK5,0.5));
				o_isF3 = 0;
				o_id_iso_leadE = 0; o_id_iso_subLeadE = 1;
				o_pt_jet_subLeadE = -1;
				o_njets = nJets[itrip];
				o_maxPt_subLeadE = electronSubLead[itrip].pt;
				if(closestJet_Lead.size()==1){
					o_pt_jet_leadE = closestJet_Lead[0].pt;
					if(closestJet_Lead[0].pt > electronLead[itrip].pt) 
						o_maxPt_leadE = closestJet_Lead[0].pt;
					else
						o_maxPt_leadE = electronLead[itrip].pt;
					closestJet_Lead.clear();
				}
				else{
					o_pt_jet_leadE = -1;
					o_maxPt_leadE = electronLead[itrip].pt;
				}
				eventList_F1P2P3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
                                syncOutTree->Fill(); 
			}
			if( isF1P2F3 ){
				if(examineThisEvent) std::cout << " F1P2F3 FOUND !!! " << std::endl;
				closestJet_Lead.push_back(ClosestInCollection(electronLead[itrip],m->RecPFJetsAK5,0.5));
				o_isF3 = 1;
				o_id_iso_leadE = 0; o_id_iso_subLeadE = 1;
				o_pt_jet_subLeadE = -1;
				o_njets = nJets[itrip];
				o_maxPt_subLeadE = electronSubLead[itrip].pt;
				if(closestJet_Lead.size()==1){
					o_pt_jet_leadE = closestJet_Lead[0].pt;
					if(closestJet_Lead[0].pt > electronLead[itrip].pt) 
						o_maxPt_leadE = closestJet_Lead[0].pt;
					else
						o_maxPt_leadE = electronLead[itrip].pt;
					closestJet_Lead.clear();
				}
				else{
					o_pt_jet_leadE = -1;
					o_maxPt_leadE = electronLead[itrip].pt;
				}
				eventList_F1P2F3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
                                syncOutTree->Fill(); 
			}
		}
		if( isP1F2P3 || isP1F2F3 ){
			if(examineThisEvent) std::cout << " isF1P2P3 or isF1P2F3 ? " << isF1P2P3 << " - " << isF1P2F3 << std::endl;
			if(examineThisEvent) std::cout << " Electron Lead pt: " << electronLead[itrip].pt << std::endl;

			if( isP1F2P3 ){
				if(examineThisEvent) std::cout << " P1F2P3 FOUND !!! " << std::endl;
				closestJet_SubLead.push_back(ClosestInCollection(electronSubLead[itrip],m->RecPFJetsAK5,0.5));
				o_isF3 = 0;
				o_id_iso_leadE = 1; o_id_iso_subLeadE = 0;
				o_pt_jet_leadE = -1;
				o_njets = nJets[itrip];
				o_maxPt_leadE = electronLead[itrip].pt;
				if(closestJet_SubLead.size()==1){
					o_pt_jet_subLeadE = closestJet_SubLead[0].pt;
					if(closestJet_SubLead[0].pt > electronSubLead[itrip].pt) 
						o_maxPt_subLeadE = closestJet_SubLead[0].pt;
					else
						o_maxPt_subLeadE = electronSubLead[itrip].pt;
					closestJet_SubLead.clear();
				}
				else{
					o_pt_jet_subLeadE = -1;
					o_maxPt_subLeadE = electronSubLead[itrip].pt;
				}
				eventList_P1F2P3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
                                syncOutTree->Fill(); 
			}
			if( isP1F2F3 ){
				if(examineThisEvent) std::cout << " P1F2F3 FOUND !!! " << std::endl;
				closestJet_SubLead.push_back(ClosestInCollection(electronSubLead[itrip],m->RecPFJetsAK5,0.5));
				o_isF3 = 1;
				o_id_iso_leadE = 1; o_id_iso_subLeadE = 0;
				o_pt_jet_leadE = -1;
				o_njets = nJets[itrip];
				o_maxPt_leadE = electronLead[itrip].pt;
				if(closestJet_SubLead.size()==1){
					o_pt_jet_subLeadE = closestJet_SubLead[0].pt;
					if(closestJet_SubLead[0].pt > electronSubLead[itrip].pt) 
						o_maxPt_subLeadE = closestJet_SubLead[0].pt;
					else
						o_maxPt_subLeadE = electronSubLead[itrip].pt;
					closestJet_SubLead.clear();
				}
				else{
					o_pt_jet_subLeadE = -1;
					o_maxPt_subLeadE = electronSubLead[itrip].pt;
				}
				eventList_P1F2F3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
                                syncOutTree->Fill(); 
			}
		}
		if( isF1F2P3 || isF1F2F3){
			if(examineThisEvent) std::cout << " isF1F2P3 or isF1F2F3 ? " << isF1F2P3 << " - " << isF1F2F3 << std::endl;
			if(examineThisEvent) std::cout << " Electron Lead pt: " << electronLead[itrip].pt << " Electron SubLead pt: " << electronSubLead[itrip].pt << std::endl;

			if( isF1F2P3 ){
				if(examineThisEvent) std::cout << " F1F2P3 FOUND !!! " << std::endl;
				closestJet_Lead.push_back(ClosestInCollection(electronLead[itrip],m->RecPFJetsAK5,0.5));
				closestJet_SubLead.push_back(ClosestInCollection(electronSubLead[itrip],m->RecPFJetsAK5,0.5));
				o_isF3 = 0;
				o_id_iso_leadE = 0; o_id_iso_subLeadE = 0;
				o_njets = nJets[itrip];
				if(closestJet_Lead.size()==1){
					o_pt_jet_leadE = closestJet_Lead[0].pt;
					if(closestJet_Lead[0].pt > electronLead[itrip].pt) 
						o_maxPt_leadE = closestJet_Lead[0].pt;
					else
						o_maxPt_leadE = electronLead[itrip].pt;
					closestJet_Lead.clear();
				}
				else{
					o_pt_jet_leadE = -1;
					o_maxPt_leadE = electronLead[itrip].pt;
				}
				if(closestJet_SubLead.size()==1){
					o_pt_jet_subLeadE = closestJet_SubLead[0].pt;
					if(closestJet_SubLead[0].pt > electronSubLead[itrip].pt) 
						o_maxPt_subLeadE = closestJet_SubLead[0].pt;
					else
						o_maxPt_subLeadE = electronSubLead[itrip].pt;
					closestJet_SubLead.clear();
				}
				else{
					o_pt_jet_subLeadE = -1;
					o_maxPt_subLeadE = electronSubLead[itrip].pt;
				}
				eventList_F1F2P3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
                                syncOutTree->Fill(); 
			}
			if( isF1F2F3 ){
				if(examineThisEvent) std::cout << " F1F2F3 FOUND !!! " << std::endl;
				closestJet_Lead.push_back(ClosestInCollection(electronLead[itrip],m->RecPFJetsAK5,0.5));
				closestJet_SubLead.push_back(ClosestInCollection(electronSubLead[itrip],m->RecPFJetsAK5,0.5));
				o_isF3 = 1;
				o_id_iso_leadE = 0; o_id_iso_subLeadE = 0;
				o_njets = nJets[itrip];
				if(closestJet_Lead.size()==1){
					o_pt_jet_leadE = closestJet_Lead[0].pt;
					if(closestJet_Lead[0].pt > electronLead[itrip].pt) 
						o_maxPt_leadE = closestJet_Lead[0].pt;
					else
						o_maxPt_leadE = electronLead[itrip].pt;
					closestJet_Lead.clear();
				}
				else{
					o_pt_jet_leadE = -1;
					o_maxPt_leadE = electronLead[itrip].pt;
				}
				if(closestJet_SubLead.size()==1){
					o_pt_jet_subLeadE = closestJet_SubLead[0].pt;
					if(closestJet_SubLead[0].pt > electronSubLead[itrip].pt) 
						o_maxPt_subLeadE = closestJet_SubLead[0].pt;
					else
						o_maxPt_subLeadE = electronSubLead[itrip].pt;
					closestJet_SubLead.clear();
				}
				else{
					o_pt_jet_subLeadE = -1;
					o_maxPt_subLeadE = electronSubLead[itrip].pt;
				}
				eventList_F1F2F3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
                                syncOutTree->Fill(); 
			}
		}
	}
}
