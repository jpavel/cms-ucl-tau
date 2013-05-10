// Dear emacs, this is -*- c++ -*-
// $Id: CycleCreators.py 173 2010-05-12 15:49:33Z krasznaa $
#ifndef Analysis_H
#define Analysis_H

// SFrame include(s):
#include "core/include/SCycleBase.h"
#include "plug-ins/include/SSummedVar.h"
#include "core/include/SError.h"
#include "core/include/SCycleBaseNTuple.h"
#include "plug-ins/include/SInputVariables.h"

// c++ includes
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

// my classes
#include "myevent.h"
#include "TLorentzVector.h"
#include "TProfile.h"
#include "TH2.h"

// PU weight

#include "LumiReweightingStandAlone.h"
//#include "Corrector2.h"


/**
 *   @short Put short description of class here
 *
 *          Put a longer description over here...
 *
 *  @author Put your name here
 * @version $Revision: 173 $
 */
class Analysis : public SCycleBase {

public:
   /// Default constructor
   Analysis();
   /// Default destructor
   ~Analysis();

   /// Function called at the beginning of the cycle
   virtual void BeginCycle() throw( SError );
   /// Function called at the end of the cycle
   virtual void EndCycle() throw( SError );
   int EventTypeConv(int e_type_in);	
   /// Function called at the beginning of a new input data
   virtual void BeginInputData( const SInputData& ) throw( SError );
   /// Function called after finishing to process an input data
   virtual void EndInputData  ( const SInputData& ) throw( SError );

   /// Function called after opening each new input file
   virtual void BeginInputFile( const SInputData& ) throw( SError );

   /// Function called for every event
   virtual void ExecuteEvent( const SInputData&, Double_t ) throw( SError );
   
   double deltaR(double eta1, double phi1, double eta2, double phi2);
   double deltaR(myobject o1, myobject o2);
   myobject ClosestInCollection(myobject o1, std::vector<myobject> collection, double max);
   bool AdLepton(std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, std::vector<myobject> Hcand, bool verbose);
   bool AdLepton_mt(myevent *m, uint index, std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, std::vector<myobject> goodTau, myobject Hcand1, myobject Hcand2, bool verbose=false);
   bool AdLepton_et(myevent *m, uint index, std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, std::vector<myobject> goodTau, myobject Hcand1, myobject Hcand2, bool verbose=false);
   bool AdLepton_tt(std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, std::vector<myobject> goodTau, myobject Hcand1, myobject Hcand2, bool verbose=false);
   double PairMass(myobject Hcand1, myobject Hcand2);	
   bool DZ_expo(myobject Zcand1, myobject Zcand2, myobject Hcand1, myobject Hcand2, bool verbose=false);
	
   bool TightEleId(float pt, float eta, double value);
   bool TightEleId(myobject o);
   bool LooseEleId(float pt, float eta, double value);
   bool LooseEleId(myobject o);   bool PFMuonID(myobject mu);
   double RelIsoMu(myobject mu);
   double RelIsoEl(myobject el);
   bool Trg_MC_12(myevent* m,bool found);
   double Tmass(myevent *m, myobject mu);
   bool WZ_Rej(myevent *m, myobject mu);
   bool isGoodMu(myobject mu);
   bool isLooseMu(myobject mu);
   bool isGoodEl(myobject el);
   double fakeTau_tight(double pt);
   double fakeTau_medium(double pt);
   
   
private:
   //
   // Put all your private variables here
   //

	// input variables
	
	myevent *m;
	
	std::vector <int> evt_number;
	std::vector <int> run_number;
	std::vector <int> lumi_number;
	std::vector <int> evt_type;
	std::vector <double>  mass_Z;
	std::vector <double>  mass_H;
	
	std::vector <int> evt_number_l;
	std::vector <int> run_number_l;
	std::vector <int> lumi_number_l;
	std::vector <int> evt_type_l;
	std::vector <double>  mass_Z_l;
	std::vector <double>  mass_H_l;
	
	std::vector <int> evt_number_m;
	std::vector <int> run_number_m;
	std::vector <int> lumi_number_m;
	std::vector <int> evt_type_m;
	std::vector <double>  mass_Z_m;
	std::vector <double>  mass_H_m;
	
	
	std::vector <int> evt_number_t;
	std::vector <int> run_number_t;
	std::vector <int> lumi_number_t;
	std::vector <int> evt_type_t;
	std::vector <double>  mass_Z_t;
	std::vector <double>  mass_H_t;
	
	
	int compared;
	int entries;

	// cut-flow
    TH1* h_tau_denominator;
    TH1* h_tau_num_medium;
    TH1* h_tau_num_tight;
    TH1* h_ele_denominator;
    TH1* h_ele_num_medium;
    TH1* h_ele_num_tight;
    TH1* h_muon_denominator;
    TH1* h_muon_num_medium;
    TH1* h_muon_num_tight;

    TH1* h_deltaR;
    TH1* h_deltaR_max;
    TH1* h_deltaR_min;

    TH1* h_cut_flow_weight;
    TH1* h_cut_flow;
    
    TH1* h_cut_flow_signal;
    TH1* h_cut_flow_cat0;
    TH1* h_cut_flow_cat1;
    TH1* h_cut_flow_cat2;

    TH1* h_cut_flow_signal_weight;
    TH1* h_cut_flow_cat0_weight;
    TH1* h_cut_flow_cat1_weight;
    TH1* h_cut_flow_cat2_weight;
   
    TH1* h_cat0_FR_medium;
    TH1* h_cat1_FR_medium;
    TH1* h_cat2_FR_medium;
    TH1* h_cat0_FR_tight;
    TH1* h_cat1_FR_tight;
    TH1* h_cat2_FR_tight;

	// histograms
        TH1* h_el_n;
        TH1* h_el_cut;
        TH1* h_event_type;
        TH1* h_event_type_raw;
        TH1* h_event_type_medium;
        TH1* h_event_type_loose;
        TH1* h_event_type_tight;
        TH1* h_mu1Z_pt;
        TH1* h_mu2Z_pt;
        TH1* h_Zmass_mumu;
        TH1* h_Zpt_mumu;
        TH1* h_ele1Z_pt;
        TH1* h_ele2Z_pt;
        TH1* h_Zmass_ee;
        TH1* h_Zpt_ee;
        TH1* h_Zmass;
        TH1* h_Zpt;
        TH1* h_Z_eta;
        TH1* h_Z_phi;
        
        TH1* h_Z_lep1_eta;
        TH1* h_Z_lep1_phi;
        
        TH1* h_Z_lep2_eta;
        TH1* h_Z_lep2_phi;
        
        TH1* h_eH_eTau_pt;
        TH1* h_tauH_eTau_pt;
        TH1* h_H_eTau_pt;
        TH1* h_H_eTau_mass;
        TH1* h_muH_muTau_pt;
        TH1* h_tauH_muTau_pt;
        TH1* h_H_muTau_pt;
        TH1* h_H_muTau_mass;
        TH1* h_muH_muE_tightMuIso_pt;
        TH1* h_eH_muE_tightMuIso_pt;
        TH1* h_H_muE_tightMuIso_pt;
        TH1* h_H_muE_tightMuIso_mass;
        TH1* h_muH_muE_looseMuIso_pt;
        TH1* h_eH_muE_looseMuIso_pt;
        TH1* h_H_muE_looseMuIso_pt;
        TH1* h_H_muE_looseMuIso_mass;
        TH1* h_tau1H_tauTau_pt;
        TH1* h_tau2H_tauTau_pt;
        TH1* h_H_tauTau_pt;
        TH1* h_H_tauTau_mass;
        TH1* h_H_pt;
        TH1* h_H_mass;
        
        TH1* h_H_eta;
        TH1* h_H_phi;
        
        TH1* h_H_lep1_eta;
        TH1* h_H_lep1_phi;
        
        TH1* h_H_lep2_eta;
        TH1* h_H_lep2_phi;
        
        
        TH1* h_n_goodEl;
        TH1* h_n_goodMu;
        
        TH1* h_el_relIso;
        TH1* h_mu_relIso;
        
        TH1* h_n_goodEl_Hcand;
        TH1* h_n_goodMu_Hcand;
        TH1* h_n_goodTau_Hcand;
        
        TH1* h_PU_weight;
        TH1* h_total_weight;
        TH1* h_nPU_raw;
        TH1* h_nPU_reweight;
        
        TH1* h_PF_MET;
        TProfile* h_PF_MET_nPU;
        
        TH1* h_PF_MET_selected;
        TProfile* h_PF_MET_nPU_selected;

        TH1* h_nbjets;
        TH1* h_nbjets_signal;
        TH1* h_nbjets_afterVeto;
        TH1* h_nbjets_afterVeto_signal;   
        TH1* h_nbjetsVetoed;
        TH1* h_Tmass;
     
        TH1* h_nPU_Info;
        TH1* h_nPU_InfoTrue;
        TH1* h_nPU_Bunch0;
        TH1* h_nPU_Info_W;
        TH1* h_nPU_InfoTrue_W;
        TH1* h_nPU_Bunch0_W;
        
        TH1* h_signal_pt1;
        TH1* h_signal_pt2;
        
        TH2* h_category0_pt;
        TH1* h_category1_pt;
        TH1* h_category2_pt;
        
	TH1* h_medium;
	TH1* h_tight;
	TH1*  h_denom;

	std::vector<TH1*>  h_denom_types;
	std::vector<TH1*>  h_loose_types;
	std::vector<TH1*>  h_medium_types;
	std::vector<TH1*>  h_tight_types;
	std::vector<TH1*>  h_denom_types_eta;
	std::vector<TH1*>  h_loose_types_eta;
	std::vector<TH1*>  h_medium_types_eta;
	std::vector<TH1*>  h_tight_types_eta;
	std::vector<TH1*>  h_denom_types_centralEtaRegion;
	std::vector<TH1*>  h_loose_types_centralEtaRegion;
	std::vector<TH1*>  h_medium_types_centralEtaRegion;
	std::vector<TH1*>  h_tight_types_centralEtaRegion;
	std::vector<TH1*>  h_denom_types_externalEtaRegion;
	std::vector<TH1*>  h_loose_types_externalEtaRegion;
	std::vector<TH1*>  h_medium_types_externalEtaRegion;
	std::vector<TH1*>  h_tight_types_externalEtaRegion;
	
	std::vector<TH1*>  h_denom_jet_types;
	std::vector<TH1*>  h_loose_jet_types;
	std::vector<TH1*>  h_medium_jet_types;
	std::vector<TH1*>  h_tight_jet_types;
	std::vector<TH1*>  h_denom_jet_types_eta;
	std::vector<TH1*>  h_loose_jet_types_eta;
	std::vector<TH1*>  h_medium_jet_types_eta;
	std::vector<TH1*>  h_tight_jet_types_eta;
	std::vector<TH1*>  h_denom_jet_types_centralEtaRegion;
	std::vector<TH1*>  h_loose_jet_types_centralEtaRegion;
	std::vector<TH1*>  h_medium_jet_types_centralEtaRegion;
	std::vector<TH1*>  h_tight_jet_types_centralEtaRegion;
	std::vector<TH1*>  h_denom_jet_types_externalEtaRegion;
	std::vector<TH1*>  h_loose_jet_types_externalEtaRegion;
	std::vector<TH1*>  h_medium_jet_types_externalEtaRegion;
	std::vector<TH1*>  h_tight_jet_types_externalEtaRegion;
	
	
	std::vector<TH1*>  h_denom_jetRef_types;
	std::vector<TH1*>  h_loose_jetRef_types;
	std::vector<TH1*>  h_medium_jetRef_types;
	std::vector<TH1*>  h_tight_jetRef_types;
	std::vector<TH1*>  h_denom_jetRef_types_eta;
	std::vector<TH1*>  h_loose_jetRef_types_eta;
	std::vector<TH1*>  h_medium_jetRef_types_eta;
	std::vector<TH1*>  h_tight_jetRef_types_eta;
	std::vector<TH1*>  h_denom_jetRef_types_centralEtaRegion;
	std::vector<TH1*>  h_loose_jetRef_types_centralEtaRegion;
	std::vector<TH1*>  h_medium_jetRef_types_centralEtaRegion;
	std::vector<TH1*>  h_tight_jetRef_types_centralEtaRegion;
	std::vector<TH1*>  h_denom_jetRef_types_externalEtaRegion;
	std::vector<TH1*>  h_loose_jetRef_types_externalEtaRegion;
	std::vector<TH1*>  h_medium_jetRef_types_externalEtaRegion;
	std::vector<TH1*>  h_tight_jetRef_types_externalEtaRegion;

	std::vector<TH1*>  h_H_mass_types;
	std::vector<TH1*>  h_H_mass_signal_types;
        std::vector<TH1*>  h_H_mass_cat0_types;
        std::vector<TH1*>  h_H_mass_cat1_types;
        std::vector<TH1*>  h_H_mass_cat2_types;
        
        
        std::vector<TH1*> h_signal_pt1_types;
        std::vector<TH1*> h_signal_pt2_types;
        std::vector<TH1*> h_signal_SumPt_types;
        
        std::vector<TH2*> h_category0_pt_types;
        std::vector<TH1*> h_category1_pt_types;
        std::vector<TH1*> h_category2_pt_types;
        
        
        TH1* h_Nvertex_NoCut;
        TH1* h_Nvertex_NoCut_W;
        TH1* h_Nvertex_AfterZ;
        TH1* h_Nvertex_AfterZ_W;
        TH1* h_Nvertex_AfterZH;
        TH1* h_Nvertex_AfterZH_W;
        
        reweight::LumiReWeighting* LumiWeights_;
        ofstream log1;
        ofstream log_events;
        ofstream log_files;
        
	
        

// properties
	std::string InTreeName;
	double Ptcut;
	double maxDeltaR;
	double maxDeltaR_H;
	double BestMassForZ;
	double dZvertex;
	double bTagValue;
	double maxEvent;
	double p0_tight;
	double p1_tight;
	double p2_tight;
	double p0_medium;
	double p1_medium;
	double p2_medium;
	double FR_MMed;
	double FR_MTig;
	double FR_EMed;
	double FR_ETig;
	
	std::string doubEle;
	std::string doubEle2;
	
    std::string doubMu;
    std::string doubMu2;
    std::string doubMu3;
    
    bool switchToFakeRate;
    bool  checkCategories;
    bool isSimulation;
    bool is2011;
    bool is2012_52;
    bool is2012_53;
    bool useTruePileUp;
    bool vetoMuonTrigger;
    bool vetoElectronTrigger;
    
    double Cut_tau_base_Pt;
    double Cut_tautau_Pt_1;
    double Cut_tautau_Pt_2;
    bool   Cut_tautau_MVA_iso; 	
    
    bool   AllowTauBOverlap;
    
    bool UseSumPtCut;
    double Cut_tautau_sumPt;
    double Cut_leptau_sumPt;
    double Cut_leplep_sumPt;
    
    bool IgnoreAdditionalTaus;
    bool IgnoreSF;
    bool IgnorePUW;
	
    bool printoutEvents;
    double examineEvent;
    bool removeTauOverlap;
    
    
    // bookkeeping variables
    
    ofstream lumi;
	long current_run;
	long current_lumi;
	SSummedVar< Int_t > m_allEvents;


// output variables
std::vector<float> out_pt;

   // Macro adding the functions for dictionary generation
   ClassDef( Analysis, 0 );

}; // class Analysis

#endif // Analysis_H

