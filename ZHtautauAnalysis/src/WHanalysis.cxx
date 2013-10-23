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
        
    DeclareProperty("syncFileName",syncFileName);
    DeclareProperty("doSync",doSync);
    DeclareProperty("checkF3",checkF3);
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
        
        h_cut_flow                                       = Book(TH1D("h_cut_flow","Cut Flow",15,-0.5,14.5));	
	h_cut_flow = Retrieve<TH1D>("h_cut_flow");
	h_cut_flow->GetXaxis()->SetBinLabel(1, "Initial Events");
	h_cut_flow->GetXaxis()->SetBinLabel(2, "trigger");
	h_cut_flow->GetXaxis()->SetBinLabel(3, "good vx");
	h_cut_flow->GetXaxis()->SetBinLabel(4, "1muW and 1muH");
	h_cut_flow->GetXaxis()->SetBinLabel(5, "charge");
	h_cut_flow->GetXaxis()->SetBinLabel(6, "muW trigger match");
	h_cut_flow->GetXaxis()->SetBinLabel(7, "muH trigger match");
	h_cut_flow->GetXaxis()->SetBinLabel(8, "tau H cand");
	h_cut_flow->GetXaxis()->SetBinLabel(9, "muW-muH inv mass");
	h_cut_flow->GetXaxis()->SetBinLabel(10, "muH-tauH inv mass");
	h_cut_flow->GetXaxis()->SetBinLabel(11, "muon veto");
	h_cut_flow->GetXaxis()->SetBinLabel(12, "ele veto");
	h_cut_flow->GetXaxis()->SetBinLabel(13, "tau veto");
	h_cut_flow->GetXaxis()->SetBinLabel(14, "bjet veto");	
	h_cut_flow->GetXaxis()->SetBinLabel(15, "LT");	

	h_dZ_PV_muon                                             = Book(TH1D("h_dZ_PV_muon","muon dz PV",100,0.,1.));
	h_dZ_PV_tau                                              = Book(TH1D("h_dZ_PV_tau","tau dz PV",100,0.,1.));
        
        //mu W plot
	h_muW_beforeVetoes_pt                                    = Book(TH1D("h_muW_beforeVetoes_pt","muonW_Pt",300,0,300));
	h_muW_beforeVetoes_eta	                                 = Book(TH1D("h_muW_beforeVetoes_eta","muonW #eta; #eta",100,-3.0,3.0));
	h_muW_beforeVetoes_phi	                                 = Book(TH1D("h_muW_beforeVetoes_phi","muonW #phi; #phi",64,-3.2,3.2));	
	h_muW_afterVetoes_pt                                     = Book(TH1D("h_muW_afterVetoes_pt","muonW_Pt",300,0,300));
	h_muW_afterVetoes_eta	                                 = Book(TH1D("h_muW_afterVetoes_eta","muonW #eta; #eta",100,-3.0,3.0));
	h_muW_afterVetoes_phi	                                 = Book(TH1D("h_muW_afterVetoes_phi","muonW #phi; #phi",64,-3.2,3.2));	
        //mu H plot
	h_muH_beforeVetoes_pt                                    = Book(TH1D("h_muH_beforeVetoes_pt","muonH_Pt",300,0,300));
	h_muH_beforeVetoes_eta	                                 = Book(TH1D("h_muH_beforeVetoes_eta","muonH #eta; #eta",100,-3.0,3.0));
	h_muH_beforeVetoes_phi	                                 = Book(TH1D("h_muH_beforeVetoes_phi","muonH #phi; #phi",64,-3.2,3.2));	
	h_muH_afterVetoes_pt                                     = Book(TH1D("h_muH_afterVetoes_pt","muonH_Pt",300,0,300));
	h_muH_afterVetoes_eta	                                 = Book(TH1D("h_muH_afterVetoes_eta","muonH #eta; #eta",100,-3.0,3.0));
	h_muH_afterVetoes_phi	                                 = Book(TH1D("h_muH_afterVetoes_phi","muonH #phi; #phi",64,-3.2,3.2));	
        //tau H plot
	h_tauH_beforeVetoes_pt                                   = Book(TH1D("h_tauH_beforeVetoes_pt","tauH_Pt",300,0,300));
	h_tauH_beforeVetoes_eta	                                 = Book(TH1D("h_tauH_beforeVetoes_eta","tauH #eta; #eta",100,-3.0,3.0));
	h_tauH_beforeVetoes_phi	                                 = Book(TH1D("h_tauH_beforeVetoes_phi","tauH #phi; #phi",64,-3.2,3.2));	
	h_tauH_afterVetoes_pt                                    = Book(TH1D("h_tauH_afterVetoes_pt","tauH_Pt",300,0,300));
	h_tauH_afterVetoes_eta	                                 = Book(TH1D("h_tauH_afterVetoes_eta","tauH #eta; #eta",100,-3.0,3.0));
	h_tauH_afterVetoes_phi	                                 = Book(TH1D("h_tauH_afterVetoes_phi","tauH #phi; #phi",64,-3.2,3.2));	
        //final vis mass plot
        h_finalVisMass_below130                                  = Book(TH1D("h_HvisMass_below130LT","H vis mass",300,0,300));
        h_finalVisMass_above130                                  = Book(TH1D("h_HvisMass_above130LT","H vis mass",300,0,300));

	h_fail_reason = Book(TH1D("h_fail_reason","Fail reason",14, 0.5,14.5));
	h_fail_reason = Retrieve<TH1D>("h_fail_reason");
	h_fail_reason->GetXaxis()->SetBinLabel(1, "trigger");
	h_fail_reason->GetXaxis()->SetBinLabel(2, "good vx");
	h_fail_reason->GetXaxis()->SetBinLabel(3, "1muW and 1muH");
	h_fail_reason->GetXaxis()->SetBinLabel(4, "charge");
	h_fail_reason->GetXaxis()->SetBinLabel(5, "muW trigger match");
	h_fail_reason->GetXaxis()->SetBinLabel(6, "muH trigger match");
	h_fail_reason->GetXaxis()->SetBinLabel(7, "tau H cand");
	h_fail_reason->GetXaxis()->SetBinLabel(8, "1tau cand");
	h_fail_reason->GetXaxis()->SetBinLabel(9, "muW-muH inv mass");
	h_fail_reason->GetXaxis()->SetBinLabel(10, "muH-tauH inv mass");
	h_fail_reason->GetXaxis()->SetBinLabel(11, "muon veto");
	h_fail_reason->GetXaxis()->SetBinLabel(12, "ele veto");
	h_fail_reason->GetXaxis()->SetBinLabel(13, "tau veto");
	h_fail_reason->GetXaxis()->SetBinLabel(14, "bjet veto");	


	if(is2011) LumiWeights_ = new reweight::LumiReWeighting("Fall11_PU.root", "dataPileUpHistogram_True_2011.root","mcPU","pileup");
	else LumiWeights_ = new reweight::LumiReWeighting("Summer12_PU_53X.root", "dataPileUpHistogramABCD_True_2012.root","mcPU","pileup");

	
	//bookkeeping
	lumi.open("lumi.csv");
	current_run=current_lumi=-999;
    eventList.open("event.list");
    
    //sync
    
      //std::ifstream myfile;
	if(doSync){
	sync_eventList.open (syncFileName.c_str());	
  if (sync_eventList.is_open()){
	while ( sync_eventList.good() ){
		long num;
		sync_eventList >> num;
		std::cout << num << std::endl;
		if(num!=1) continue; //HACK!
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
        eventList.close();

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
			
            bool dZ = _muon[i].dz_PV < 0.2;
if(verb) std::cout << " pre-muon " << i << " pt eta etaSC: " << muPt << " " 
				<< muEta << " pixelHits " << _muon[i].intrkLayerpixel << " btag " << bTag << " dz " << _muon[i].dz_PV << std::endl;
				
			if ((muGlobal || muTracker) && muPt > muPt_ && fabs(muEta) < muEta_ && pixelHits && bTag && dZ ){
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

std::vector<myobject> WHanalysis::SelectGoodElVector(std::vector<myobject> _electron, bool verb, double elPt_ =5., double elEta_ = 2.5){

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

bool WHanalysis::TightEleId(float pt, float eta, double value){
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

bool WHanalysis::TightEleId(myobject o){
	if( o.numLostHitEleInner > 0) return false;
	return TightEleId(o.pt, o.eta_SC,o.Id_mvaNonTrg);
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
		if(verbose) std::cout << " Distance to 1st H candidate is " << dR1 << std::endl;
		if(verbose) std::cout << " Distance to 2nd H candidate is " << dR2 << std::endl;
		if(verbose) std::cout << " Distance to W candidate is " << dR3 << std::endl;
		if(RelIso(genericMuon[i]) < 0.15 && (dR1 > 0.4 && dR2 > 0.4 && dR3 > 0.4))
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
		double dR1= deltaR(genericElectron[i].eta,genericElectron[i].phi,Wcand.eta,Wcand.phi); 
		double dR2= deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand1.eta,Hcand1.phi); 
		double dR3= deltaR(genericElectron[i].eta,genericElectron[i].phi,Hcand2.eta,Hcand2.phi); 

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
		bool pass = tauPt && tauEta && tauDZ && Loose3Hit;
		if(verbose) std::cout << " Tau cand no. " << i << std::endl;
		if(verbose) std::cout << " Distance to 1st H candidate is " << dR1 << std::endl;
		if(verbose) std::cout << " Distance to 2nd H candidate is " << dR2 << std::endl;
		if(verbose) std::cout << " Distance to W candidate is " << dR3 << std::endl;
		if(dR1 > 0.4 && dR2 > 0.4 && dR3 > 0.4 && pass)
			Ad_tau=true;
	}
	return Ad_tau;
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
	
	Hist("h_PU_weight")->Fill(PUWeight);
	Hist("h_nPU_raw")->Fill(m->PUInfo_true);
	Hist("h_nPU_reweight")->Fill(m->PUInfo_true,PUWeight);
	
        h_cut_flow->Fill(0.0,1);

	bool trigPass;
	trigPass = Trg_MC_12(m,examineThisEvent);
	m_logger << DEBUG <<" Trigger decision " << trigPass << SLogger::endmsg;
	if(!trigPass)
	{
		if(examineThisEvent){
			 std::cout << "Trigger fail! " << examineEvent << std::endl;
			 h_fail_reason->Fill(1);
		 }
		return;
	}

        h_cut_flow->Fill(1,1);
	
	//vertex selection
	std::vector<myobject> vertex = m->Vertex;
	std::vector<myobject> goodVertex = SelectGoodVxVector(vertex);
	short nGoodVx=goodVertex.size();
	
	// at least one good vertex
	if(nGoodVx < 1){
		if(examineThisEvent){ std::cout << "Good vertex fail!" << std::endl;
		h_fail_reason->Fill(2);
		}
		 return;
	 
	 }
        
        h_cut_flow->Fill(2,1);
	
	//select generic muon with pt > 5 GeV and |eta| < 2.4
	std::vector<myobject> muon = m->PreSelectedMuons;
	std::vector<myobject> jet = m->RecPFJetsAK5;
	if(examineThisEvent) std::cout << " There are " << muon.size() << " preselected muons " << std::endl;
	m_logger << DEBUG << " There are " << muon.size() << " preselected muons " << SLogger::endmsg;
	std::vector<myobject> genericMuon = SelectGoodMuVector(muon,jet,examineThisEvent);
	if(examineThisEvent) std::cout << " There are " << genericMuon.size() << " selected muons " << std::endl;

	//select generic electron with pt > 5 GeV and |eta| < 2.5
	std::vector<myobject> electron = m->PreSelectedElectrons;
	if(examineThisEvent) std::cout << " There are " << electron.size() << " preselected electrons " << std::endl;
	std::vector<myobject> genericElectron = SelectGoodElVector(electron,examineThisEvent);
	
	//overlap cleaning
	CrossCleanWithMu(&genericElectron,genericMuon,examineThisEvent,maxDeltaR);
	if(examineThisEvent) std::cout << " There are " << genericElectron.size() << " selected electrons" << std::endl;

	//select good electron 
        std::vector<myobject> goodElectron;
        for(uint i=0; i<genericElectron.size(); i++){

            bool tightID = TightEleId(genericElectron.at(i));

            if(tightID && (genericElectron.at(i)).dz_PV < 0.2){
	       goodElectron.push_back(genericElectron.at(i));
	    } 
        }
	
        //select good muon 
        std::vector<myobject> goodMuon;
        for(uint i=0; i<genericMuon.size(); i++){

            h_dZ_PV_muon->Fill((genericMuon.at(i)).dz_PV);

            bool pfID = PFMuonID(genericMuon.at(i));
            if(examineThisEvent) std::cout << "The muon no. " << i << " has id " << pfID << " and dz " << genericMuon[i].dz_PV << std::endl;

            if(pfID && (genericMuon.at(i)).dz_PV < 0.2){
	       goodMuon.push_back(genericMuon.at(i));
	    } 
        }
         
	if(examineThisEvent) std::cout << " There are " << goodMuon.size() << " good muon before mu_W selection " << endl;

	//select leading muon for W
        std::vector<myobject> muon_W;
        muon_W.clear();

	for(uint i=0; i<goodMuon.size(); i++){
                // pt cut > 20
		if( (goodMuon.at(i)).pt < 20.)  continue;
                //
                if(examineThisEvent) cout << "rel iso is: " << RelIso(goodMuon.at(i)) << endl;
                if( fabs((goodMuon.at(i)).eta) < 1.479 ){
			if( RelIso(goodMuon.at(i)) < 0.15 ){
				muon_W.push_back(goodMuon.at(i));
				goodMuon.erase(goodMuon.begin()+i);
				i = i-1;
			}  
		}
		else{
			if( RelIso(goodMuon.at(i)) < 0.10 ){
				muon_W.push_back(goodMuon.at(i));
				goodMuon.erase(goodMuon.begin()+i);
				i = i-1;
			}  
		}
	}        
        
	if(examineThisEvent) std::cout << " There are " << muon_W.size() << " muon for W " << endl;
	if(examineThisEvent) std::cout << " There are still " << goodMuon.size() << " good muon for mu_H selection " << endl;

        //select sub-leading muon for H
        std::vector<myobject> muon_H;
        muon_H.clear();
  // every W candidate is good H candidate      
    if(muon_W.size() > 1){
		bool found = false;
		for(uint iMu=1; iMu < muon_W.size() && !found; iMu++)
		{
			if(deltaR(muon_W[iMu],muon_W[0]) > 0.5){
				 muon_H.push_back(muon_W[iMu]);
				 found = true;
				 muon_W.erase(muon_W.begin()+iMu);
			 }
					
		}
		
	}
// if no W candidate suitable, check the rest
if(muon_H.size()==0){
	for(uint i=0; i<goodMuon.size(); i++){
                // pt cut > 10
		if( (goodMuon.at(i)).pt < 10. ) continue;
                //
                if(examineThisEvent) cout << "rel iso is: " << RelIso(goodMuon.at(i)) << endl;
		if( fabs((goodMuon.at(i)).eta) < 1.479 ){
			if( RelIso(goodMuon.at(i)) < 0.20 ){
				muon_H.push_back(goodMuon.at(i));
				goodMuon.erase(goodMuon.begin()+i);
				i = i-1;
			}  
		}
		else{
			if( RelIso(goodMuon.at(i)) < 0.15 ){
				muon_H.push_back(goodMuon.at(i));
				goodMuon.erase(goodMuon.begin()+i);
				i = i-1;
			}  
		}
	}
}        
        
	
        if(examineThisEvent) std::cout << " There are " << muon_H.size() << " muon for H " << endl;
	if(examineThisEvent) std::cout << " There are still " << goodMuon.size() << " good muon " << endl;

        if( !(muon_H.size() == 1 && muon_W.size() == 1) ){
			if(examineThisEvent){
				 std::cout << "Too many mu cand fail!" << std::endl;
				 h_fail_reason->Fill(3);
			 }
			return;
		}
        
        h_cut_flow->Fill(3,1);
   
   if( (muon_W.at(0)).charge!=(muon_H.at(0)).charge ){
			if(examineThisEvent){
				 std::cout << "SS charge fail!" << std::endl;
				 h_fail_reason->Fill(4);
			 }
			 return;
	}
        h_cut_flow->Fill(4,1);
	
	if(!muon_W[0].hasTrgObject_loose){
		if(examineThisEvent){
			 std::cout << "Muon from W not matched to trigger!" << std::endl;
			 h_fail_reason->Fill(5);
		 }
		return;
	}
        h_cut_flow->Fill(5,1);
	
	if(!muon_H[0].hasTrgObject_loose){
		if(examineThisEvent){
			 std::cout << "Muon from H not matched to trigger!" << std::endl;
			 h_fail_reason->Fill(6);
		 }
		return;
	}
        h_cut_flow->Fill(6,1);
	
	//select good taus 
	std::vector<myobject> goodTau;
	goodTau.clear();
	std::vector<myobject> tau = m->PreSelectedHPSTaus;
	
	for (uint i = 0; i < tau.size(); i++) {

		double tauPt = (tau.at(i)).pt;
		double tauEta = (tau.at(i)).eta;
		double tauDZ = (tau.at(i)).dz_Ver_match;
		bool Loose3Hit = ((tau.at(i)).byLooseCombinedIsolationDeltaBetaCorr3Hits > 0.5);
		if(checkF3) Loose3Hit=!Loose3Hit;
		bool DecayMode = ((tau.at(i)).discriminationByDecayModeFinding > 0.5);
		// overlap removal
		if(deltaR(muon_W[0],tau[i]) < 0.5) continue;
		if(deltaR(muon_H[0],tau[i]) < 0.5) continue;
		
	
		h_dZ_PV_tau->Fill(tauDZ);
		
                if (tauPt > 20. && fabs(tauEta) < 2.3 && Loose3Hit && DecayMode && tauDZ < 0.2){
			goodTau.push_back(tau.at(i));
		}
	}
	
        if(examineThisEvent) std::cout << " There are " << goodTau.size() << " selected taus" << std::endl;
        
        if( goodTau.size() == 0 ){
			if(examineThisEvent){
				 std::cout << "No good tau cand fail!" << std::endl;
				 h_fail_reason->Fill(7);
			 }
			return;
		}
        
        std::vector<myobject> tau_H;
        tau_H.clear();
 
        for(uint i=0; i<goodTau.size(); i++){
			bool LooseEleMVA3 = ((goodTau.at(i)).discriminationByElectronMVA3Loose > 0.5);
			bool TightMuon    = ((goodTau.at(i)).discriminationByMuonTight > 0.5);
			bool charge = goodTau[i].charge*muon_H[0].charge < 0; // tau OS sign cut
			if(examineThisEvent) std::cout << "Checking the tau at pt/eta:" << goodTau[i].pt << "/" << goodTau[i].eta << "anti-e,anti-mu" << 
			LooseEleMVA3 << TightMuon << " charge: " << charge << std::endl;
			if ( LooseEleMVA3 && TightMuon && charge){
				tau_H.push_back(goodTau.at(i));
	                }
        }
        
        if(examineThisEvent) std::cout << " There are " << tau_H.size() << " selected tau possibly good for H candidate" << std::endl;
        if(examineThisEvent) std::cout << " light lepton charges " << std::endl;
        
        if( !(tau_H.size() == 1) ){
			if(examineThisEvent){
				 std::cout << "Too many signal tau cands fail!" << std::endl;
				h_fail_reason->Fill(8); 
			}
			return;
		}
        
        h_cut_flow->Fill(7,1);
        
        
        //filling histograms
        h_muW_beforeVetoes_pt->Fill((muon_W.at(0)).pt);
        h_muW_beforeVetoes_eta->Fill((muon_W.at(0)).eta);
        h_muW_beforeVetoes_phi->Fill((muon_W.at(0)).phi);
        h_muH_beforeVetoes_pt->Fill((muon_H.at(0)).pt);
        h_muH_beforeVetoes_eta->Fill((muon_H.at(0)).eta);
        h_muH_beforeVetoes_phi->Fill((muon_H.at(0)).phi);
        h_tauH_beforeVetoes_pt->Fill((tau_H.at(0)).pt);
        h_tauH_beforeVetoes_eta->Fill((tau_H.at(0)).eta);
        h_tauH_beforeVetoes_phi->Fill((tau_H.at(0)).phi);


	// check the masses of the pair(s)
	
	if(PairMass(muon_W[0],muon_H[0]) < 20.){
		if(examineThisEvent){
			 std::cout << " mu pair failed inv mass cut" << std::endl;
			 h_fail_reason->Fill(9);
		 }
		return;
	}
        
        h_cut_flow->Fill(8,1);
	
	if(PairMass(muon_H[0],tau_H[0]) < 20.){
		if(examineThisEvent){
			 std::cout << " mutau pair failed inv mass cut" << std::endl;
			 h_fail_reason->Fill(10);
		 }
		return;
	}
        
        h_cut_flow->Fill(9,1);
	
        //check the presence of additional isolated muons
        //if any, reject the event
	if(examineThisEvent) std::cout << " Before additional isolated muon veto" << std::endl;
        bool Ad_muon=false;
	if(AdMuon_sig(goodMuon,muon_H.at(0),tau_H.at(0),muon_W.at(0),examineThisEvent)){
		Ad_muon=true;
         	}
        if(Ad_muon){
			if(examineThisEvent) {
				std::cout << "Muon veto fail!" << std::endl; 
				h_fail_reason->Fill(11);
			}
           return;
	   }
	if(examineThisEvent) std::cout << " After additional isolated muon veto" << std::endl;
        h_cut_flow->Fill(10,1);
        
        //check the presence of additional isolated electrons
        //if any, reject the event
	if(examineThisEvent) std::cout << " Before additional isolated electron veto" << std::endl;
        bool Ad_electron=false;
	if(AdElectron_sig(goodElectron,muon_H.at(0),tau_H.at(0),muon_W.at(0),examineThisEvent)){
		Ad_electron=true;
         	}
        if(Ad_electron){
			if(examineThisEvent){
				 std::cout << "Electron veto fail!" << std::endl; 
				 h_fail_reason->Fill(12);
			 }
	
           return;
	   }
	if(examineThisEvent) std::cout << " After additional isolated electron veto" << std::endl;
        h_cut_flow->Fill(11,1);
        
        //check the presence of additional isolated taus
        //if any, reject the event
	if(examineThisEvent) std::cout << " Before additional isolated tau veto" << std::endl;
        bool Ad_tau=false;
	if(AdTau_sig(tau,muon_H.at(0),tau_H.at(0),muon_W.at(0),examineThisEvent)){
		Ad_tau=true;
         	}
        if(Ad_tau){
			if(examineThisEvent){
				 std::cout << "tau veto fail!" << std::endl; 
				 h_fail_reason->Fill(13);
			}
           return;
	   }
	if(examineThisEvent) std::cout << " After additional isolated tau veto" << std::endl;
        h_cut_flow->Fill(12,1);

        //b-Tag Veto
	bool bTagVeto = false;
	
	Int_t count_bJets = 0;
	Int_t count_bJetsVetoed = 0;
	Int_t count_bJets_afterVeto = 0;

	for (uint i = 0; i < jet.size() && !bTagVeto; i++) {
		double jetPt = jet[i].pt;
		double jetEta = jet[i].eta;
		double jetPhi = jet[i].phi;
		double bTag = jet[i].bDiscriminatiors_CSV;
		double PUjetID = jet[i].puJetIdLoose;
		if(examineThisEvent) std::cout << "jet pt " << jetPt << "jet eta " << jetEta << "btag " << bTag << "PU jet ID" << std::endl;
		if(jetPt > 20. && fabs(jetEta) < 2.4 && bTag > bTagValue && PUjetID){
			count_bJets++;
			if(examineThisEvent) std::cout << "candidate b-jet" << std::endl;
			double dR1,dR2,dR3;
			//dR1=deltaR(jetEta,jetPhi,(muon_W.at(0)).eta,(muon_W.at(0)).phi);
			//dR2=deltaR(jetEta,jetPhi,(muon_H.at(0)).eta,(muon_H.at(0)).phi);
			//dR3=deltaR(jetEta,jetPhi,(tau_H.at(0)).eta,(tau_H.at(0)).phi);
			dR1=deltaR(jet.at(i),muon_W.at(0));
			dR2=deltaR(jet.at(i),muon_H.at(0));
			dR3=deltaR(jet.at(i),tau_H.at(0));
			if(examineThisEvent) std::cout << " distances are " << dR1 << " " << dR2 << " " << dR3 << std::endl;
			bool overlap = false;
			if(dR1 < 0.4 || dR2 < 0.4 || dR3 < 0.4) overlap = true;
			bTagVeto = !overlap;

		}
	}

	if(examineThisEvent) std::cout << " Before b-tag veto" << std::endl;

	if(bTagVeto){
		if(examineThisEvent){
			 std::cout << "Btag veto fail!" << std::endl;
			 h_fail_reason->Fill(14);
		 }	 
		return;
	}
	if(examineThisEvent) std::cout << " After b-tag veto" << std::endl;
        h_cut_flow->Fill(13,1);
        
        //filling histograms
        h_muW_afterVetoes_pt->Fill((muon_W.at(0)).pt);
        h_muW_afterVetoes_eta->Fill((muon_W.at(0)).eta);
        h_muW_afterVetoes_phi->Fill((muon_W.at(0)).phi);
        h_muH_afterVetoes_pt->Fill((muon_H.at(0)).pt);
        h_muH_afterVetoes_eta->Fill((muon_H.at(0)).eta);
        h_muH_afterVetoes_phi->Fill((muon_H.at(0)).phi);
        h_tauH_afterVetoes_pt->Fill((tau_H.at(0)).pt);
        h_tauH_afterVetoes_eta->Fill((tau_H.at(0)).eta);
        h_tauH_afterVetoes_phi->Fill((tau_H.at(0)).phi);



        //define LT regions

        double LT;
        bool aboveEvent = false;
        bool belowEvent = false;
        
        //TLorentzVector muW_b130, muH_b130, tauH_b130;
        //TLorentzVector muW_a130, muH_a130, tauH_a130;
        
        LT = (muon_W.at(0)).pt + (muon_H.at(0)).pt + (tau_H.at(0)).pt;
        if(LT < LTValue){
		//muW_b130.SetPxPyPzE( (muon_W.at(0)).px, (muon_W.at(0)).py, (muon_W.at(0)).pz, (muon_W.at(0)).E );
		//muH_b130.SetPxPyPzE( (muon_H.at(0)).px, (muon_H.at(0)).py, (muon_H.at(0)).pz, (muon_H.at(0)).E );
		//tauH_b130.SetPxPyPzE( (tau_H.at(0)).px, (tau_H.at(0)).py, (tau_H.at(0)).pz, (tau_H.at(0)).E );
                h_finalVisMass_below130->Fill(PairMass(muon_H.at(0),tau_H.at(0)));
                belowEvent = true;
        }
        if(LT > LTValue){
		//muW_a130.SetPxPyPzE( (muon_W.at(0)).px, (muon_W.at(0)).py, (muon_W.at(0)).pz, (muon_W.at(0)).E );
		//muH_a130.SetPxPyPzE( (muon_H.at(0)).px, (muon_H.at(0)).py, (muon_H.at(0)).pz, (muon_H.at(0)).E );
		//tauH_a130.SetPxPyPzE( (tau_H.at(0)).px, (tau_H.at(0)).py, (tau_H.at(0)).pz, (tau_H.at(0)).E );
                h_finalVisMass_above130->Fill(PairMass(muon_H.at(0),tau_H.at(0)));
		aboveEvent = true;
        }



	if(examineThisEvent) {
           if(belowEvent)
           std::cout << " LT < 130 GeV ! scalar pt sum: " << LT << std::endl;
           else if(aboveEvent)
           std::cout << " LT > 130 GeV ! scalar pt sum: " << LT << std::endl;
        }
        h_cut_flow->Fill(14,1);
        
        //cout << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl; 
        //write runNumber:lumiNumber:eventNumber
        eventList << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
 
   


}

