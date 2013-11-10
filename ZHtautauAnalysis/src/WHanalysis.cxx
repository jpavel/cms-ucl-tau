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
	
	// ntuple definition
	DeclareVariable(out_pt,"pt");
	
	// histogram booking
        Double_t bins[] = { 20, 30, 40, 50, 60, 70, 80, 100, 130, 300 };

        h_visMass_P1P2P3                                        = Book(TH1D("h_visMass_P1P2P3","H vis mass", 9, bins));
        h_visMass_F1P2P3                                        = Book(TH1D("h_visMass_F1P2P3","H vis mass", 9, bins));
        h_visMass_P1F2P3                                        = Book(TH1D("h_visMass_P1F2P3","H vis mass", 9, bins));
        h_visMass_P1P2F3                                        = Book(TH1D("h_visMass_P1P2F3","H vis mass", 9, bins));
        h_visMass_F1F2F3                                        = Book(TH1D("h_visMass_F1F2F3","H vis mass", 9, bins));
        h_visMass_P1F2F3                                        = Book(TH1D("h_visMass_P1F2F3","H vis mass", 9, bins));
        h_visMass_F1F2P3                                        = Book(TH1D("h_visMass_F1F2P3","H vis mass", 9, bins));
        h_visMass_F1P2F3                                        = Book(TH1D("h_visMass_F1P2F3","H vis mass", 9, bins));

	h_LT_P1P2P3                                             = Book(TH1D("h_LT_P1P2P3","LT",300,0,300));
	h_LT_F1P2P3                                             = Book(TH1D("h_LT_F1P2P3","LT",300,0,300));
	h_LT_P1F2P3                                             = Book(TH1D("h_LT_P1F2P3","LT",300,0,300));
	h_LT_P1P2F3                                             = Book(TH1D("h_LT_P1P2F3","LT",300,0,300));
	h_LT_F1F2F3                                             = Book(TH1D("h_LT_F1F2F3","LT",300,0,300));
	h_LT_P1F2F3                                             = Book(TH1D("h_LT_P1F2F3","LT",300,0,300));
	h_LT_F1F2P3                                             = Book(TH1D("h_LT_F1F2P3","LT",300,0,300));
	h_LT_F1P2F3                                             = Book(TH1D("h_LT_F1P2F3","LT",300,0,300));

        h_visMass_w                                      = Book(TH1D("h_visMass_w","H vis mass w", 9, bins));
	h_LT_w                                           = Book(TH1D("h_LT_w","LT w",300,0,300));

	h_PU_weight					 = Book(TH1D("h_PU_weight","PU weights distribution",100,0,5));
	h_nPU_raw					 = Book(TH1D("h_nPU_raw","raw PU distribution",100,0,100));
	h_nPU_reweight					 = Book(TH1D("h_nPU_reweight","reweighted PU distribution",100,0,100));
        
        h_count                                              = Book(TH1D("h_count","Cut Flow",2,0.0,2.0));	
        h_count_mmt                                          = Book(TH1D("h_count_mmt","Cut Flow",2,0.0,2.0));	
        h_count_eet                                          = Book(TH1D("h_count_eet","Cut Flow",2,0.0,2.0));	
        //h_cut_flow_mmt                                       = Book(TH1D("//h_cut_flow_mmt","Cut Flow",15,-0.5,14.5));	
        //h_cut_flow_eet                                       = Book(TH1D("//h_cut_flow_eet","Cut Flow",16,-0.5,15.5));	

	//h_cut_flow_mmt = Retrieve<TH1D>("//h_cut_flow_mmt");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(1, "Initial Events");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(2, "trigger");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(3, "good vx");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(4, "1muW and 1muH");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(5, "charge");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(6, "muW trigger match");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(7, "muH trigger match");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(8, "0 good tau");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(9, "tau H cand");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(10, "muW-muH inv mass");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(11, "muH-tauH inv mass");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(12, "muon veto");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(13, "ele veto");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(14, "tau veto");
	//h_cut_flow_mmt->GetXaxis()->SetBinLabel(15, "bjet veto");	

	//h_cut_flow_eet = Retrieve<TH1D>("//h_cut_flow_eet");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(1, "Initial Events");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(2, "trigger");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(3, "good vx");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(4, "1elW and 1elH");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(5, "charge");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(6, "elW trigger match");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(7, "elH trigger match");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(8, "DY inv mass");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(9, "0 good tau");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(10, "tau H cand");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(11, "muW-muH inv mass");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(12, "muH-tauH inv mass");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(13, "muon veto");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(14, "ele veto");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(15, "tau veto");
	//h_cut_flow_eet->GetXaxis()->SetBinLabel(16, "bjet veto");	

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

        kNNEval = new MVAEvaluator("2012");
	
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
	
        //h_cut_flow_mmt->Fill(0.0,1);
        //h_cut_flow_eet->Fill(0.0,1);

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

        //h_cut_flow_mmt->Fill(1,1);
        //h_cut_flow_eet->Fill(1,1);
	
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
        
        //h_cut_flow_mmt->Fill(2,1);
        //h_cut_flow_eet->Fill(2,1);
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
	CrossCleanWithMu(&genericElectron,vetoMuon,examineThisEvent,maxDeltaR);
	if(examineThisEvent) std::cout << genericElectron.size() << " generic electrons after the MU-ELE x-Cleaning" << std::endl;
	CrossCleanWithMu(&vetoElectron,vetoMuon,examineThisEvent,maxDeltaR);
	if(examineThisEvent) std::cout << vetoElectron.size() << " veto electrons after the MU-ELE x-Cleaning" << std::endl;
	m_logger << DEBUG << " cross cleaning mu 2 " << SLogger::endmsg;

	//overlap cleaning: selected electrons (with loose id) and taus 
	if(examineThisEvent) std::cout << tau.size() << " preselected taus " << std::endl;
	CrossCleanWithEle(&vetoElectron,tau,examineThisEvent,0.4);
	if(examineThisEvent) std::cout << tau.size() << " preselected taus after the ELE-TAU x-Cleaning" << std::endl;
	m_logger << DEBUG << " cross cleaning tau " << SLogger::endmsg;
	
	std::vector<myobject> electronW_sig;
        electronW_sig.clear();
	std::vector<myobject> electronH_sig;
        electronH_sig.clear();
	std::vector<myobject> electronW_fake;
        electronW_fake.clear();
	std::vector<myobject> electronH_fake;
        electronH_fake.clear();

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
			genericElectron.erase(genericElectron.begin()+i);
			i = i-1;
		} 
	m_logger << DEBUG << " inside good ele for " << SLogger::endmsg;
	}
	if(examineThisEvent){ 
		cout << "after track req" << endl;
		if(examineThisEvent) std::cout  << goodElectron.size() << " good electron " << endl;
		if(examineThisEvent) std::cout << genericElectron.size() << " generic electron " << endl;
	}
	bool isP1 = false;
	bool isF1 = false;

	//select electrons for W: signal and/or fake

	for(uint i=0; i<goodElectron.size(); i++){
		bool relIsoTight_W = false;
		bool relIsoLoose_W = false;
                if( fabs((goodElectron.at(i).eta)) < 1.479 ){
			if( RelIso(goodElectron.at(i)) < 0.15 ) relIsoTight_W = true;
                }else{
			if( RelIso(goodElectron.at(i)) < 0.10 ) relIsoLoose_W = true;
                }
		bool tightEleID = false;
		if( TightEleId(goodElectron.at(i)) ) tightEleID = true;
		

		if(examineThisEvent){ 
			cout << "ele pt: " << goodElectron[i].pt << " eta " << goodElectron[i].eta << " phi " << goodElectron[i].phi <<
				" rel iso is: " << RelIso(goodElectron.at(i),examineThisEvent) << " rel iso tight " << relIsoTight_W << 
				" rel iso loose " << relIsoLoose_W << " tight ID " << tightEleID << endl;}
		if( (goodElectron.at(i)).pt < 20.)  continue;
	
                if( tightEleID && ( relIsoTight_W || relIsoLoose_W ) ){
			electronW_sig.push_back(goodElectron.at(i));
		        goodElectron.erase(goodElectron.begin()+i);
		        i = i-1; isP1 = true;
                }
                else if( !tightEleID || !relIsoTight_W ){ 
			electronW_fake.push_back(goodElectron.at(i));
		        goodElectron.erase(goodElectron.begin()+i);
		        i = i-1; isF1 = true;
                }
                else if( !tightEleID || !relIsoLoose_W ){ 
			electronW_fake.push_back(goodElectron.at(i));
		        goodElectron.erase(goodElectron.begin()+i);
		        i = i-1; isF1 = true;
                }
	m_logger << DEBUG << " inside ele W for" << SLogger::endmsg;
	}

        bool WfakeGoodForH   = false;
        bool WsigGoodForHsig = false;

        
	//if pt signal W > pt fake W --> use fake W to search a fake or signal higgs
	//if pt signal W < pt fake W --> use signal W to search a signal higgs
        if( isP1 && isF1 && goodElectron.size() == 0 ){
		if( electronW_sig[0].pt > electronW_fake[0].pt ) 
			WfakeGoodForH = true;
                else
			WsigGoodForHsig = true;
        }
        
	if(examineThisEvent) cout << " ele W size " << electronW_sig.size() << endl;
	if(examineThisEvent) cout << " ele W size fake " << electronW_fake.size() << endl;
	m_logger << DEBUG << " ele W size " << electronW_sig.size() << SLogger::endmsg;
	m_logger << DEBUG << " ele W size fake " << electronW_fake.size() << SLogger::endmsg;
	m_logger << DEBUG << " goodElectron size " << goodElectron.size() << SLogger::endmsg;


	bool isP2 = false;
	bool isF2 = false;
        bool isP1P2 = false;
        bool isP1F2 = false;
        bool isF1P2 = false;
        bool isF1F2 = false;
        bool attempt1_ = false;
        bool attempt2_ = false;
        bool attempt3_ = false;
        bool attempt4_ = false;

	if( !isP1 && !isF1 )
		return;

        if( WfakeGoodForH ) {
		if( !LooseEleId( electronW_fake[0] ) ){
			electronH_fake.push_back(electronW_fake[0]);
			electronW_fake.erase(electronW_fake.begin());
			isF2 = true;
                        isF1 = false;}
		else{
			if( RelIso( electronW_fake[0] ) < 0.20 ){
				electronH_sig.push_back(electronW_fake[0]);
				electronW_fake.erase(electronW_fake.begin());
				isP2 = true;
                                isF1 = false;}
			else if( RelIso( electronW_fake[0] ) > 0.15 ){
				electronH_fake.push_back(electronW_fake[0]);
				electronW_fake.erase(electronW_fake.begin());
				isF2 = true;
                                isF1 = false;}
		}
	}else if( WsigGoodForHsig ){
		if( RelIso( electronW_sig[0] ) < 0.20 ){
			electronH_sig.push_back(electronW_sig[0]);
			electronW_sig.erase(electronW_sig.begin());
			isP2 = true;
                        isP1 = false;}
		else if( RelIso( electronW_sig[0] ) > 0.15 ){
			electronH_fake.push_back(electronW_sig[0]);
			electronW_sig.erase(electronW_sig.begin());
			isF2 = true;
                        isP1 = false;}
	}

        if( (isP1 && isP2) || (isP1 && isF2) || (isF1 && isP2) || (isF1 && isF2) ) 
        	attempt1_ = true;
	
        m_logger << DEBUG << " isP1/isF1/isP2/isF2 " << isP1 <<"/"<< isF1 << "/" << isP2 << "/" << isF2 << SLogger::endmsg;

        if( isP1P2 || isP1F2 || isF1P2 || isF1F2 )
		attempt1_ = true;

        m_logger << DEBUG << " attempt1 " << attempt1_ << SLogger::endmsg;

	if( !attempt1_ && electronW_sig.size() > 1 ){
		bool found = false;
		if(examineThisEvent) std::cout << " >1 lead. ele for W, looking for sub-lead signal ele among them!" << std::endl;

		for(uint iEl=1; iEl < electronW_sig.size() && !found; iEl++)
		{
			if(examineThisEvent) std::cout << "0) pt: " << electronW_sig[0].pt << std::endl;
			if(examineThisEvent) std::cout << "i) pt: " << electronW_sig[iEl].pt << std::endl;
			if(examineThisEvent) std::cout << "dR: " << deltaR(electronW_sig[iEl],electronW_sig[0]) << std::endl;

			if(electronW_sig[iEl].pt > electronW_sig[0].pt) continue;
			if(deltaR(electronW_sig[iEl],electronW_sig[0]) > 0.5){
				if(examineThisEvent)
					cout << "electron pt: " << electronW_sig[iEl].pt << " eta " << electronW_sig[iEl].eta << " phi " << electronW_sig[iEl].phi <<
						"rel iso is: " << RelIso(electronW_sig[iEl]) << endl;
				if( RelIso( electronW_sig[iEl] ) < 0.20 ){
					electronH_sig.push_back(electronW_sig[iEl]);
					electronW_sig.erase(electronW_sig.begin());
					found = true;
					electronW_sig.erase(electronW_sig.begin()+iEl);
					isP2 = true;
					attempt2_ = true;
				}
				else if( RelIso( electronW_sig[iEl] ) > 0.15 ){
					electronH_fake.push_back(electronW_sig[iEl]);
					electronW_sig.erase(electronW_sig.begin());
					found = true;
					electronW_sig.erase(electronW_sig.begin()+iEl);
					isF2 = true;
					attempt2_ = true;
				}
			}
		}
	}
        
        m_logger << DEBUG << " attempt2 " << attempt2_ << SLogger::endmsg;

	if(examineThisEvent) std::cout << "is P2 after the if electronW_sig.size() > 1 " << isP2 << std::endl;

	if(examineThisEvent) std::cout << electronW_sig.size() << " SIGNAL leading electrons for W " << endl;
	if(examineThisEvent) std::cout << electronW_fake.size() << " FAKE leading electrons for W " << endl;
	if(examineThisEvent) std::cout << electronH_sig.size() << " SIGNAL sub-leading electrons for H " << endl;
	if(examineThisEvent) std::cout << electronH_fake.size() << " FAKE sub-leading electrons for H " << endl;

	// if no W candidate suitable, check the rest
	bool isP2_ptOrder = false; bool isP2_dR = false;                       

	if( !attempt2_ && electronW_fake.size() > 1 ){
		if(examineThisEvent) std::cout << "FIRST ATTEMPT FAILED! Searching for suitable ele H candidate!" << std::endl;
		if(examineThisEvent) std::cout << "good electron size: " <<goodElectron.size()<< std::endl;

		bool found = false;
		bool found2 = false;
		for(uint iEl=1; iEl < electronW_fake.size() && !found; iEl++)
		{
                        isF1 = true;
			if( electronW_fake[iEl].pt > electronW_fake[0].pt ) continue;
			if(examineThisEvent)
				cout << "electron pt: " << electronW_fake[iEl].pt << " eta " << electronW_fake[iEl].eta << 
					" phi " << electronW_fake[iEl].phi <<
					"rel iso is: " << RelIso(electronW_fake[iEl]) << " loose ID " << LooseEleId( electronW_fake[iEl] ) << endl;
			if( !LooseEleId( electronW_fake[iEl] ) ){
				electronH_fake.push_back(electronW_fake[iEl]);
				electronW_fake.erase(electronW_fake.begin()+iEl);
				isF2 = true;
			}else{
				if( RelIso( electronW_fake[iEl] ) < 0.20 ){
					electronH_sig.push_back(electronW_fake[iEl]);
					electronW_fake.erase(electronW_fake.begin()+iEl);
					isP2 = true;
				}
				else if( RelIso( electronW_fake[iEl] ) > 0.15 ){
					electronH_fake.push_back(electronW_fake[iEl]);
					electronW_fake.erase(electronW_fake.begin()+iEl);
					isF2 = true;
				}
			}
		}

                if ( isF2 || isP2 ){
			for(uint i=0; i<goodElectron.size(); i++){
		        	vetoElectron.push_back(goodElectron[i]);
 		                goodElectron.erase(goodElectron.begin()+i);
                                i = i-1;
                        }
                        attempt3_ = true;
                }
	}
        
	m_logger << DEBUG << " attempt3 " << attempt3_ << SLogger::endmsg;
 
        if( !attempt3_ ){
		if( isF1 && electronW_sig.size() == 0 && goodElectron.size() != 0 ){
			for(uint i=0; i<goodElectron.size(); i++){
				bool relIsoTight_H = false;
				bool relIsoLoose_H = false;
				if( fabs((goodElectron.at(i).eta)) < 1.479 ){
					if( RelIso(goodElectron.at(i)) < 0.20 ) relIsoTight_H = true;
				}else{
					if( RelIso(goodElectron.at(i)) < 0.15 ) relIsoLoose_H = true;
				}
				bool looseEleID = false;
				if( LooseEleId(goodElectron.at(i)) ) looseEleID = true;

				if(examineThisEvent){ 
					cout << "ele pt: " << goodElectron[i].pt << " eta " << goodElectron[i].eta << " phi " << goodElectron[i].phi <<
						"rel iso is: " << RelIso(goodElectron.at(i),examineThisEvent) << 
						" tight ID " << TightEleId(goodElectron.at(i)) << endl;
				}
				if( (goodElectron.at(i)).pt < 10. ) continue;

				if( goodElectron[i].pt < electronW_fake[0].pt ) isP2_ptOrder = true;
				if( deltaR(goodElectron[i],electronW_fake[0]) > 0.5 ) isP2_dR = true;

				//if( looseEleID && ( relIsoTight_H || relIsoLoose_H ) ){
				if( isP2_ptOrder && isP2_dR && (looseEleID && ( relIsoTight_H || relIsoLoose_H )) ){
					electronH_sig.push_back(goodElectron.at(i));
					goodElectron.erase(goodElectron.begin()+i);
					i = i-1; isP2 = true; 
					attempt4_ = true;
				}else if( !looseEleID || ( !relIsoTight_H || !relIsoLoose_H ) ){ 
					electronH_fake.push_back(goodElectron.at(i));
					goodElectron.erase(goodElectron.begin()+i);
					i = i-1; isF2 = true;
					attempt4_ = true;
				}
			}
		}
	}
        

	if( attempt1_ || attempt2_ || attempt3_ || attempt4_ ){
		if( isP1 && isP2 ) isP1P2 = true;
		else if( isP1 && isF2 ) isP1F2 = true;
		else if( isF1 && isP2 ) isF1P2 = true;
		else if( isF1 && isF2 ) isF1F2 = true;
	}


	if(examineThisEvent){ 
		std::cout << "P2: " << isP2 << " - F2: " << isF2 << endl;
			std::cout << electronH_sig.size() << " SIGNAL sub-leading electrons " << endl;
			std::cout << electronH_fake.size() << " FAKE sub-leading electrons " << endl;
	}	

	std::vector<myobject> electronLead;
        electronLead.clear();
	std::vector<myobject> electronSubLead;
        electronSubLead.clear();

	if( isP1P2 ){
		if(examineThisEvent) std::cout << "P1P2" << std::endl;
		electronLead.push_back(electronW_sig[0]);
		electronSubLead.push_back(electronH_sig[0]);
	}
	else if( isP1F2 ){
		if(examineThisEvent) std::cout << "P1F2" << std::endl;
		electronLead.push_back(electronW_sig[0]);
		electronSubLead.push_back(electronH_fake[0]);
	}
	else if( isF1P2 ){
		if(examineThisEvent) std::cout << "F1P2" << std::endl;
		electronLead.push_back(electronW_fake[0]);
		electronSubLead.push_back(electronH_sig[0]);
	}
	else if( isF1F2 ){
		if(examineThisEvent) std::cout << "F1F2" << std::endl;
		electronLead.push_back(electronW_fake[0]);
		electronSubLead.push_back(electronH_fake[0]);
	}
        else return;
	//h_cut_flow_eet->Fill(3,1);

        bool isP1P2_SS = false;     
        bool isP1F2_SS = false; //bool isP1F2_OS = false; 
        bool isF1P2_SS = false; //bool isF1P2_OS = false;
        bool isF1F2_SS = false; //bool isF1F2_OS = false;
        bool fake_SS = false;   //bool fake_OS = false;
    
	if( isP1P2 ){
		if( electronLead[0].charge == electronSubLead[0].charge ){
			if(examineThisEvent) std::cout << "Signal candidates has Same charge?" << std::endl;
			isP1P2_SS = true;}
        }else{
		if( electronLead[0].charge == electronSubLead[0].charge ){
			if(isP1F2) isP1P2_SS = true;
			if(isF1P2) isF1P2_SS = true;
			if(isF1F2) isF1F2_SS = true;
			fake_SS = true;
                }
	}
	//if( !isP1P2 && electronLead[0].charge != electronSubLead[0].charge ){
	//	if(isP1F2) isP1F2_OS = true;
	//	if(isF1P2) isF1P2_OS = true;
	//	if(isF1F2) isF1F2_OS = true;
	//	fake_OS = true;
        //}

	if(examineThisEvent) std::cout << "P1P2SS/fakeSS: " << isP1P2_SS << "/" << fake_SS << std::endl;
        if( isP1P2 && !isP1P2_SS ) return;
			if(examineThisEvent) std::cout << "SS YES!" << std::endl;
        if( !isP1P2 && !fake_SS ) return;
			if(examineThisEvent) std::cout << "ma e' qui?!" << std::endl;

	//h_cut_flow_mmt->Fill(4,1);
	//h_cut_flow_eet->Fill(4,1);
	if(examineThisEvent){
		std::cout << " trigger object details for leptons" << std::endl;
		std::cout << " eta lead/sub: " << electronLead[0].TrgObjectEta_loose << "/" << electronSubLead[0].TrgObjectEta_loose << std::endl;
		std::cout << " pt lead/sub: " << electronLead[0].TrgObjectPt_loose << "/" << electronSubLead[0].TrgObjectPt_loose << std::endl;
		std::cout << " phi lead/sub: " << electronLead[0].TrgObjectPhi_loose << "/" << electronSubLead[0].TrgObjectPhi_loose << std::endl;
	}

	if(!electronLead[0].hasTrgObject_loose){
		if(examineThisEvent){
			std::cout << "P1P2/P1F2/F1P2/F1F2: " << isP1P2 <<"/"<< isP1F2 <<"/"<< isF1P2 << "/" << isF1F2 << std::endl;
			std::cout << "pt/eta/phi: " << electronLead[0].TrgObjectPt_loose << "/" << electronLead[0].TrgObjectEta_loose << "/" << electronLead[0].TrgObjectPhi_loose << std::endl;
		}
		return;
	}
	//h_cut_flow_mmt->Fill(5,1);
	//h_cut_flow_eet->Fill(5,1);
	
	if(!electronSubLead[0].hasTrgObject_loose){
		if(examineThisEvent){
			std::cout << "P1P2/P1F2/F1P2/F1F2: " << isP1P2 <<"/"<< isP1F2 <<"/"<< isF1P2 << "/" << isF1F2 << std::endl;
			std::cout << "pt/eta/phi: " << electronSubLead[0].TrgObjectPt_loose << "/" << electronSubLead[0].TrgObjectEta_loose << "/" << electronSubLead[0].TrgObjectPhi_loose << std::endl;
		}
		return;
	}
	if(examineThisEvent) std::cout << "electron lead trigger matching passed!" << std::endl;

	//h_cut_flow_mmt->Fill(6,1);
	//h_cut_flow_eet->Fill(6,1);

        //additional cut for eet to reject dy
        double Z_mass_SS = 90.54;
        //double Z_mass_OS = 91.20;
	if(examineThisEvent) cout << "Pair mass SS: " << fabs(PairMass(electronLead[0],electronSubLead[0])-Z_mass_SS) << endl;
	//if(examineThisEvent) cout << "Pair mass OS: " << fabs(PairMass(electronLead[0],electronSubLead[0])-Z_mass_OS) << endl;

	if( isP1P2_SS && fabs(PairMass(electronLead[0],electronSubLead[0])-Z_mass_SS) < 10. ){
		if(examineThisEvent){
			std::cout << "SIGNAL: No close enough to Z mass!" << std::endl;
		}
		return;
	}
	if( fake_SS && fabs(PairMass(electronLead[0],electronSubLead[0])-Z_mass_SS) < 10. ){
		if(examineThisEvent){
			std::cout << "FAKE SS: No close enough to Z mass!" << std::endl;
		}
		return;
	}
	m_logger << DEBUG << " mass" << SLogger::endmsg;
	//if( fake_OS && fabs(PairMass(electronLead[0],electronSubLead[0])-Z_mass_OS) < 10. ){
	//	if(examineThisEvent){
	//		std::cout << "FAKE OS: No close enough to Z mass!" << std::endl;
	//	}
	//	return;
	//}
	
	//h_cut_flow_eet->Fill(7,1);

	//select good taus 
	std::vector<myobject> goodTau;
	goodTau.clear();

	for (uint i = 0; i < tau.size(); i++) {

		double tauPt = (tau.at(i)).pt;
		double tauEta = (tau.at(i)).eta;
		double tauDZ = (tau.at(i)).dz_Ver_match;
		bool DecayMode = ((tau.at(i)).discriminationByDecayModeFinding > 0.5);
		
		//if(deltaR(electronW_sig[0],tau[i]) < 0.5) continue; if(deltaR(electronH_sig[0],tau[i]) < 0.5) continue;
                
		if(examineThisEvent) std::cout << " tau #" << i << "pt/eta/phi:"
			<< tau[i].pt << "/" << tau[i].eta << "/" << tau[i].phi << " dz: " <<
				tauDZ << " DM " << DecayMode;

		//if (tauPt > 20. && fabs(tauEta) < 2.3 && Loose3Hit && DecayMode && fabs(tauDZ) < 0.2){
		if (tauPt > 20. && fabs(tauEta) < 2.3 && DecayMode && fabs(tauDZ) < 0.2){
			if(examineThisEvent) std::cout << " -> Selected (NO ISO APPLIED)!" << std::endl;
			goodTau.push_back(tau.at(i));
		}
	}

	if(examineThisEvent) std::cout << goodTau.size() << " selected SIGNAL taus" << std::endl;

	if( goodTau.size() == 0 ){
		if(examineThisEvent){
			std::cout << "NO good taus!" << std::endl;
		}
		return;
	}
	//h_cut_flow_mmt->Fill(7,1);
	//h_cut_flow_eet->Fill(8,1);

	std::vector<myobject> tauH_sig;
	tauH_sig.clear();
	std::vector<myobject> tauH_fake;
	tauH_fake.clear();

	for(uint i=0; i<goodTau.size(); i++){
		bool LooseEleMVA3 = ((goodTau.at(i)).discriminationByElectronMVA3Loose > 0.5);
		bool MediumEleMVA3 = ((goodTau.at(i)).discriminationByElectronMVA3Medium > 0.5);
		bool TightEleMVA3 = ((goodTau.at(i)).discriminationByElectronMVA3Tight > 0.5);
		bool TightMuon    = ((goodTau.at(i)).discriminationByMuonTight > 0.5);
		bool LooseMuon    = ((goodTau.at(i)).discriminationByMuonLoose > 0.5);
		bool Loose3Hit = ((goodTau.at(i)).byLooseCombinedIsolationDeltaBetaCorr3Hits > 0.5); // ISOLATION !
		bool charge = goodTau[i].charge*electronSubLead[0].charge < 0; // tau OS sign cut

                double mass1 = fabs(PairMass(electronLead[0],goodTau.at(i)) - Z_mass_SS);
                double mass2 = fabs(PairMass(electronSubLead[0],goodTau.at(i)) - Z_mass_SS);

			if(examineThisEvent) std::cout << "Checking the tau at pt/eta:" << goodTau[i].pt << "/" << goodTau[i].eta << "anti-e,anti-mu" << 
				LooseEleMVA3 << LooseMuon << " charge: " << charge << " isolation: " << Loose3Hit << std::endl;
			if( mass1 < 10. || mass2 < 10.){
				if ( TightEleMVA3 && LooseMuon && charge ){
                                        if( Loose3Hit ) {
						tauH_sig.push_back(goodTau.at(i));
						goodTau.erase(goodTau.begin()+i); 
						i = i-1;
					}else{
						tauH_fake.push_back(goodTau.at(i));
						goodTau.erase(goodTau.begin()+i); 
						i = i-1;
                                        }
				}
			}
			else if( mass1 < 20. || mass2 < 20. ){
				if ( MediumEleMVA3 && LooseMuon && charge ){
                                        if( Loose3Hit ) {
						tauH_sig.push_back(goodTau.at(i));
						goodTau.erase(goodTau.begin()+i); 
						i = i-1;
					}else{
						tauH_fake.push_back(goodTau.at(i));
						goodTau.erase(goodTau.begin()+i); 
						i = i-1;
                                        }
				}
			}
			else{
				if ( LooseEleMVA3 && LooseMuon && charge ){
                                        if( Loose3Hit ) {
						tauH_sig.push_back(goodTau.at(i));
						goodTau.erase(goodTau.begin()+i); 
						i = i-1;
					}else{
						tauH_fake.push_back(goodTau.at(i));
						goodTau.erase(goodTau.begin()+i); 
						i = i-1;
                                        }
				}
			}
	}

	if(examineThisEvent) std::cout << tauH_sig.size() << " SIGNAL taus" << std::endl;
	if(examineThisEvent) std::cout << tauH_fake.size() << " FAKE taus" << std::endl;

	if( tauH_sig.size() == 0 && tauH_fake.size() == 0){
		if(examineThisEvent){
			std::cout << "SIGNAL and FAKE taus fail!" << std::endl;
		}
		return;
	}

        bool isP3 = false; bool isF3 = false;
	if( tauH_sig.size() >= 1 ){
		if(examineThisEvent){
			std::cout << "1 SIGNAL tau - 0 FAKE tau --> isP3" << std::endl;
		}
                isP3 = true; 
	}
	else if( tauH_sig.size() == 0 && tauH_fake.size() >= 1 ){
		if(examineThisEvent){
			std::cout << "0 SIGNAL tau - 1 FAKE tau --> isF3" << std::endl;
		}
                isF3 = true;
	}

	//h_cut_flow_mmt->Fill(8,1);
	//h_cut_flow_eet->Fill(9,1);

	// check the masses of the pair(s)
	if(PairMass(electronLead[0],electronSubLead[0]) < 20.){
		if(examineThisEvent){
			std::cout << " l-l pair failed inv mass cut" << std::endl;
		}
		return;
	}
	//h_cut_flow_mmt->Fill(9,1);
	//h_cut_flow_eet->Fill(10,1);
        
        // It's time to do all the combinations!
	std::vector<myobject> tauH;
	tauH.clear();
        bool isP1P2P3 = false; // P1 P2 P3 --> signal
        bool isP1P2F3 = false; // P1 P2 F3 --> leading and subleading signal, tau fake
        bool isP1F2P3 = false; // P1 F2 P3 --> leading and tau signal, subleading fake
        bool isF1P2P3 = false; // F1 P2 P3 --> leading fake, subleading and tau signal
        bool isP1F2F3 = false; // P1 F2 F3 --> leading signal, subleading and tau fake
	bool isF1P2F3 = false; // F1 P2 F3 --> leading and tau fake, subleading signal
        bool isF1F2P3 = false; // F1 F2 P3 --> leading and subleading fake, tau signal
        bool isF1F2F3 = false; // F1 F2 F3 --> leading, subleading and tau fake

	m_logger << DEBUG << " isP1P2 " << isP1P2 << SLogger::endmsg;
	m_logger << DEBUG << " isP1F2 " << isP1F2 << SLogger::endmsg;
	m_logger << DEBUG << " isF1P2 " << isF1P2 << SLogger::endmsg;
	m_logger << DEBUG << " isF1F2 " << isF1F2 << SLogger::endmsg;
	m_logger << DEBUG << " isF3 " << isF3 << SLogger::endmsg;
	m_logger << DEBUG << " isP3 " << isP3 << SLogger::endmsg;
        
        if( isP1P2 && isP3){
        	isP1P2P3 = true;
                tauH.push_back(tauH_sig[0]);
		if(examineThisEvent) std::cout << " P1 P2 P3 " << std::endl;
        }else if( isP1P2 && isF3){
        	isP1P2F3 = true;
                tauH.push_back(tauH_fake[0]);
		if(examineThisEvent) std::cout << " P1 P2 F3 " << std::endl;
        }else if( isP1F2 && isP3){
        	isP1F2P3 = true;
                tauH.push_back(tauH_sig[0]);
		if(examineThisEvent) std::cout << " P1 F2 P3 " << std::endl;
        }else if( isP1F2 && isF3){
        	isP1F2F3 = true;
                tauH.push_back(tauH_fake[0]);
		if(examineThisEvent) std::cout << " P1 F2 F3 " << std::endl;
        }else if( isF1P2 && isP3){
        	isF1P2P3 = true;
                tauH.push_back(tauH_sig[0]);
		if(examineThisEvent) std::cout << " F1 P2 P3 " << std::endl;
        }else if( isF1P2 && isF3){
        	isF1P2F3 = true;
                tauH.push_back(tauH_fake[0]);
		if(examineThisEvent) std::cout << " F1 P2 F3 " << std::endl;
        }else if( isF1F2 && isP3){
        	isF1F2P3 = true;
                tauH.push_back(tauH_sig[0]);
		if(examineThisEvent) std::cout << " F1 F2 P3 " << std::endl;
        }else if( isF1F2 && isF3){
        	isF1F2F3 = true;
                tauH.push_back(tauH_fake[0]);
		if(examineThisEvent) std::cout << " F1 F2 F3 " << std::endl;
	}
        
	if(PairMass(electronSubLead[0],tauH[0]) < 20.){
		if(examineThisEvent){
			std::cout << " l-tau pair fails inv mass cut" << std::endl;
		}
		return;
	}

	//h_cut_flow_mmt->Fill(10,1);
	//h_cut_flow_eet->Fill(11,1);

	//apply VETOS!

        bool Ad_muon=false;
	if(AdMuon_sig(vetoMuon,electronSubLead[0],tauH[0],electronLead[0],examineThisEvent)){
		Ad_muon=true;
	}
	if(Ad_muon){
		if(examineThisEvent) {
			std::cout << "Muon veto fail!" << std::endl; 
		}
		return;
	}
	if(examineThisEvent) std::cout << " After additional isolated muon veto" << std::endl;

 	//h_cut_flow_mmt->Fill(11,1);
	//h_cut_flow_eet->Fill(12,1);

        for(uint i=0;i<vetoElectron.size();i++){
        	if( deltaR(electronLead[0],vetoElectron[i]) < 0.1 ){
                   vetoElectron.erase(vetoElectron.begin()+i);
                   i = i-1;
		}
        }
        for(uint i=0;i<vetoElectron.size();i++){
        	if( deltaR(electronSubLead[0],vetoElectron[i]) < 0.1 ){
                   vetoElectron.erase(vetoElectron.begin()+i);
                   i = i-1;
		}
	}
        	//for(uint j=0;j<genericElectron.size();j++){
        	//	if( deltaR(vetoElectron[i],genericElectron[j]) < 0.1 ){
		//		vetoElectron.erase(vetoElectron.begin()+i);
	//			i = i-1;}
	//	}
	bool Ad_electron=false;
	if(AdElectron_sig(vetoElectron,electronSubLead[0],tauH[0],electronLead[0],examineThisEvent)){
		Ad_electron=true;
	}
	if(Ad_electron){
		if(examineThisEvent){
			std::cout << "Electron veto fail!" << std::endl; 
		}

		return;
	}
	if(examineThisEvent) std::cout << " After additional isolated electron veto" << std::endl;
 	
        //h_cut_flow_mmt->Fill(12,1);
	//h_cut_flow_eet->Fill(13,1);

	bool Ad_tau=false;
	if(AdTau_sig(tau,electronSubLead[0],tauH[0],electronLead[0],examineThisEvent)){
		Ad_tau=true;
	}
	if(Ad_tau){
		if(examineThisEvent){
			std::cout << "tau veto fail!" << std::endl; 
		}
		return;
	}
	if(examineThisEvent) std::cout << " After additional isolated tau veto" << std::endl;
        
        //h_cut_flow_mmt->Fill(13,1);
	//h_cut_flow_eet->Fill(14,1);

	//b-Tag Veto
	bool bTagVeto = false;

	Int_t count_bJets = 0;
	Int_t count_Jets = 0;

	for (uint i = 0; i < jet.size() && !bTagVeto; i++) {
		double jetPt = jet[i].pt;
		double jetEta = jet[i].eta;
		double jetPhi = jet[i].phi;
		double bTag = jet[i].bDiscriminatiors_CSV;
		double PUjetID = jet[i].puJetIdLoose;
		if(examineThisEvent) std::cout << "jet pt " << jetPt << "jet eta " << jetEta << "btag " << bTag << "PU jet ID" << std::endl;
		if(jetPt > 20. && fabs(jetEta) < 2.4 && PUjetID){
			double dR1_,dR2_,dR3_;
			dR1_=deltaR(jet.at(i),electronLead[0]);
			dR2_=deltaR(jet.at(i),electronSubLead[0]);
			dR3_=deltaR(jet.at(i),tauH[0]);
			if(dR1_ > 0.4 && dR2_ > 0.4 && dR3_ > 0.4)
				count_Jets++;
		}
		if(jetPt > 20. && fabs(jetEta) < 2.4 && bTag > bTagValue && PUjetID){
			count_bJets++;
			if(examineThisEvent) std::cout << "candidate b-jet" << std::endl;
			double dR1,dR2,dR3;
			dR1=deltaR(jet.at(i),electronLead[0]);
			dR2=deltaR(jet.at(i),electronSubLead[0]);
			dR3=deltaR(jet.at(i),tauH[0]);
			if(examineThisEvent) std::cout << " distances are " << dR1 << " " << dR2 << " " << dR3 << std::endl;
			bool overlap = false;
			if(dR1 < 0.4 || dR2 < 0.4 || dR3 < 0.4) overlap = true;
			bTagVeto = !overlap;

		}
	}

	if(bTagVeto){
		if(examineThisEvent){
			std::cout << "Btag veto fail!" << std::endl;
		}	 
		return;
	}
	if(examineThisEvent) std::cout << " After b-tag veto" << std::endl;
	if(examineThisEvent) std::cout << " Count b jets: " << count_bJets << std::endl;
	if(examineThisEvent) std::cout << " Count jets: " << count_Jets << std::endl;

        double maxPt_Lead;
        double maxPt_SubLead;
	
        double LT;

        if( isF1P2P3 || isF1P2F3){
        	myobject ClosestJet_Leading = ClosestInCollection(electronLead[0],m->RecPFJetsAK5,0.4);
                if( ClosestJet_Leading.pt > electronLead[0].pt ) maxPt_Lead = ClosestJet_Leading.pt;
                else maxPt_Lead = electronLead[0].pt;
		if(examineThisEvent) std::cout << " isF1P2P3 or isF1P2F3 ? " << isF1P2P3 << " - " << isF1P2F3 << std::endl;
		if(examineThisEvent) std::cout << " Closest jet pt: " << ClosestJet_Leading.pt << std::endl;
		if(examineThisEvent) std::cout << " Electron Lead pt: " << electronLead[0].pt << std::endl;
		if(examineThisEvent) std::cout << " max pt: " << maxPt_Lead << std::endl;
		if(examineThisEvent) std::cout << " kNN evaluator WJets " << kNNEval->getWJetsLeadingElectron(electronLead[0].pt,maxPt_Lead,count_Jets) << std::endl;
		if(examineThisEvent) std::cout << " kNN evaluator QCD " << kNNEval->getQCDLeadingElectron(electronLead[0].pt,maxPt_Lead,count_Jets) << std::endl;
		LT = electronLead[0].pt + electronSubLead[0].pt + tauH[0].pt;
                if( isF1P2P3 ){
			h_visMass_F1P2P3->Fill(PairMass(electronSubLead[0],tauH[0]));
			h_LT_F1P2P3->Fill(PairMass(electronSubLead[0],tauH[0]));
		}
                if( isF1P2F3 ){
			h_visMass_F1P2F3->Fill(PairMass(electronSubLead[0],tauH[0]));
			h_LT_F1P2F3->Fill(PairMass(electronSubLead[0],tauH[0]));
		}
        }
        if( isP1F2P3 || isP1F2F3 ){
        	myobject ClosestJet_SubLeading = ClosestInCollection(electronSubLead[0],m->RecPFJetsAK5,0.4);
                if( ClosestJet_SubLeading.pt > electronSubLead[0].pt ) maxPt_SubLead = ClosestJet_SubLeading.pt;
                else maxPt_SubLead = electronSubLead[0].pt;
		if(examineThisEvent) std::cout << " isP1F2P3 or isP1F2F3 ? " << isP1F2P3 << " - " << isP1F2F3 << std::endl;
		if(examineThisEvent) std::cout << " Closest jet pt: " << ClosestJet_SubLeading.pt << std::endl;
		if(examineThisEvent) std::cout << " Electron SubLead pt: " << electronSubLead[0].pt << std::endl;
		if(examineThisEvent) std::cout << " max pt: " << maxPt_SubLead << std::endl;
		//if(examineThisEvent) std::cout << " kNN evaluator WJets " << kNNEval->getWJetsSubleadingElectron(electronSubLead[0].pt,maxPt_SubLead,count_Jets) << std::endl;
		//if(examineThisEvent) std::cout << " kNN evaluator QCD " << kNNEval->getQCDSubleadingElectron(electronSubLead[0].pt,maxPt_SubLead,count_Jets) << std::endl;
		LT = electronLead[0].pt + electronSubLead[0].pt + tauH[0].pt;
                if( isP1F2P3 ){
			h_visMass_P1F2P3->Fill(PairMass(electronSubLead[0],tauH[0]));
			h_LT_P1F2P3->Fill(PairMass(electronSubLead[0],tauH[0]));
		}
                if( isP1F2F3 ){
			h_visMass_P1F2F3->Fill(PairMass(electronSubLead[0],tauH[0]));
			h_LT_P1F2F3->Fill(PairMass(electronSubLead[0],tauH[0]));
		}
        }
        if( isF1F2P3 || isF1F2F3){
        	myobject ClosestJet_Leading = ClosestInCollection(electronLead[0],m->RecPFJetsAK5,0.4);
        	myobject ClosestJet_SubLeading = ClosestInCollection(electronSubLead[0],m->RecPFJetsAK5,0.4);
                if( ClosestJet_Leading.pt > electronLead[0].pt ) maxPt_Lead = ClosestJet_Leading.pt;
                else maxPt_Lead = electronLead[0].pt;
                if( ClosestJet_SubLeading.pt > electronSubLead[0].pt ) maxPt_SubLead = ClosestJet_SubLeading.pt;
                else maxPt_SubLead = electronSubLead[0].pt;
		if(examineThisEvent) std::cout << " isF1F2P3 or isF1F2F3 ? " << isF1F2P3 << " - " << isF1F2F3 << std::endl;
		if(examineThisEvent) std::cout << " Closest Lead jet pt: " << ClosestJet_Leading.pt << " Closest SubLead jet pt: " << ClosestJet_SubLeading.pt << std::endl;
		if(examineThisEvent) std::cout << " Electron Lead pt: " << electronLead[0].pt << " Electron SubLead pt: " << electronSubLead[0].pt << std::endl;
		if(examineThisEvent) std::cout << " max lead pt: " << maxPt_Lead << " max sublead pt: " << maxPt_SubLead << std::endl;
		//if(examineThisEvent) std::cout << " kNN evaluator WJets " << kNNEval->getWJetsLeadingElectron(electronLead[0].pt,maxPt_Lead,count_Jets) << std::endl;
		//if(examineThisEvent) std::cout << " kNN evaluator QCD " << kNNEval->getQCDLeadingElectron(electronLead[0].pt,maxPt_Lead,count_Jets) << std::endl;
		//if(examineThisEvent) std::cout << " kNN evaluator WJets " << kNNEval->getWJetsSubleadingElectron(electronSubLead[0].pt,maxPt_SubLead,count_Jets) << std::endl;
		//if(examineThisEvent) std::cout << " kNN evaluator QCD " << kNNEval->getQCDSubleadingElectron(electronSubLead[0].pt,maxPt_SubLead,count_Jets) << std::endl;
		LT = electronLead[0].pt + electronSubLead[0].pt + tauH[0].pt;
                if( isF1F2P3 ){
			h_visMass_F1F2P3->Fill(PairMass(electronSubLead[0],tauH[0]));
			h_LT_F1F2P3->Fill(PairMass(electronSubLead[0],tauH[0]));
		}
                if( isF1F2F3 ){
			h_visMass_F1F2F3->Fill(PairMass(electronSubLead[0],tauH[0]));
			h_LT_F1F2F3->Fill(PairMass(electronSubLead[0],tauH[0]));
		}
	}


    
        //h_cut_flow_mmt->Fill(14,1);
	//h_cut_flow_eet->Fill(15,1);

	//define LT regions

		bool aboveEvent = false;
		bool belowEvent = false;

		if(LT < LTValue_eet){
			//h_finalVisMass_below130->Fill(PairMass(electronH_sig[0],tau_H[0]));
			belowEvent = true;
		}
		if(LT > LTValue_eet){
			//h_finalVisMass_above130->Fill(PairMass(electronH_sig[0],tau_H[0]));
			aboveEvent = true;
	        }


       /////////////////// USEFUL PLOTS !!!!
        //		if(isSimulation && !IgnoreSF){
	//		double eleW_SF = (Cor_ID_Iso_Ele_Loose_2012_53X(electronLead[0])) * (Corr_Trg_Ele_2012_53X(electronLead[0])); 
	//		double eleH_SF = (Cor_ID_Iso_Ele_Tight_2012_53X(electronSubLead[0])) * (Corr_Trg_Ele_2012_53X(electronSubLead[0]));
	//		double final_weight = PUWeight * eleW_SF * eleH_SF;
	//
	//              h_visMass->Fill( PairMass(electronSubLead[0],tauH[0]) ); 
	//              h_visMass_w->Fill( PairMass(electronSubLead[0],tauH[0]), final_weight); 
	//              h_LT->Fill( LT ); 
	//              h_LT_w->Fill( LT, final_weight); 
	//	}
       /////////////////// 

	if(examineThisEvent) {
		if(belowEvent)
			std::cout << " LT =  " << LT << std::endl;
		if(aboveEvent)
			std::cout << " LT =  " << LT << std::endl;
	}

        if(isP1P2P3) 
		eventList_P1P2P3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
        if(isP1P2F3) 
		eventList_P1P2F3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
        if(isP1F2P3)
		eventList_P1F2P3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
        if(isF1P2P3)
		eventList_F1P2P3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
        if(isP1F2F3)
		eventList_P1F2F3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
	if(isF1P2F3)
		eventList_F1P2F3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
        if(isF1F2P3)
		eventList_F1F2P3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
        if(isF1F2F3)
		eventList_F1F2F3 << m->runNumber << ":" << m->lumiNumber << ":" << m->eventNumber << endl ; 
       
}

