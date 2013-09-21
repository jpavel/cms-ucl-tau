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
   double DistanceToClosestInCollection(myobject o1, std::vector<myobject> collection);
   bool AdLepton(std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, std::vector<myobject> Hcand, bool verbose);
   bool AdLepton_mt(myevent *m, uint index, std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, std::vector<myobject> goodTau, myobject Hcand1, myobject Hcand2, bool verbose=false);
   bool AdLepton_et(myevent *m, uint index, std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, std::vector<myobject> goodTau, myobject Hcand1, myobject Hcand2, bool verbose=false);
   bool AdLepton_tt(std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, std::vector<myobject> goodTau, myobject Hcand1, myobject Hcand2, bool verbose=false);
   bool AdLepton_sig(std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, std::vector<myobject> goodTau, myobject Hcand1, myobject Hcand2, bool verbose=false);
   bool AdLepton_em(myevent *m, uint index_e, uint index_m, std::vector<myobject> genericMuon, std::vector<myobject> genericElectron, myobject Hcand1, myobject Hcand2,bool verbose=false);
   double PairMass(myobject Hcand1, myobject Hcand2);	
   double PairPt(myobject Hcand1, myobject Hcand2);	
   bool CheckOverlapLooseElectron(myobject tau, std::vector<myobject> elCollection, double maxR, double isoVal, bool verb);
   bool CheckOverlapLooseMuon(myobject tau, std::vector<myobject> muCollection, double maxR, double isoVal);
   std::vector<myobject> SelectGoodVxVector(std::vector<myobject> _vertex, double _normChi2, int _ndof, double _dZ);
   std::vector<myobject> SelectGoodMuVector(std::vector<myobject> _muon, bool verb, double muPt_, double muEta_);
   std::vector<myobject> SelectGoodElVector(std::vector<myobject> _electron, bool verb, double elPt_, double elEta_ );
   void CrossCleanWithMu(std::vector<myobject>* _input, std::vector<myobject> _muon, bool verb, double _maxDeltaR, double _muIso, bool _looseMuId);
   bool FindZ(std::vector<myobject>* _lepton, std::vector<myobject>* _Zcand, bool _isMu, bool verb, double _maxDeltaR, double _bestMass,
	double _massLow, double _massHi, double _relIso);




   
   
   bool DZ_expo(myobject Zcand1, myobject Zcand2, myobject Hcand1, myobject Hcand2, bool verbose=false);
  // bool isLargerPt(myobject o1, myobject o2);		
   bool TightEleId(float pt, float eta, double value);
   bool TightEleId(myobject o);
   bool LooseEleId(float pt, float eta, double value);
   bool LooseEleId(myobject o);   bool PFMuonID(myobject mu);
   double RelIso(myobject mu);
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

   

    TH1* h_cut_flow_weight;
    TH1* h_cut_flow;
    
   
   
   
	// histograms
       
   
        TH1* h_event_type;
        TH1* h_event_type_raw;
       
        TH1* h_mu1Z_pt;
        TH1* h_mu2Z_pt;
        TH1* h_Zmass_mumu;
        TH1* h_Zpt_mumu;
        TH1* h_ele1Z_pt;
        TH1* h_ele2Z_pt;
        TH1* h_Zmass_ee;
        TH1* h_Zpt_ee;
        
        TH1* h_Z_eta;
        TH1* h_Z_phi;
        
        TH1* h_Z_lep1_eta;
        TH1* h_Z_lep1_phi;
        
        TH1* h_Z_lep2_eta;
        TH1* h_Z_lep2_phi;
        
     
        
        
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

        
      
     
        TH1* h_nPU_Info;
        TH1* h_nPU_InfoTrue;
        TH1* h_nPU_Bunch0;
        TH1* h_nPU_Info_W;
        TH1* h_nPU_InfoTrue_W;
        TH1* h_nPU_Bunch0_W;
        
        //FR plots
        
        TH1* h_FR_tau_denom;
        TH1* h_FR_tauLT_denom;
        TH1* h_FR_mu_denom;
        TH1* h_FR_el_denom;
        TH1* h_FR_muT_denom;
        TH1* h_FR_elT_denom;
        
        TH1* h_FR_tau_num;
        TH1* h_FR_tauLT_num;
        TH1* h_FR_mu_num;
        TH1* h_FR_el_num;
        TH1* h_FR_muT_num;
        TH1* h_FR_elT_num;
        
        TH1* h_FR_tau_denom_EC;
        TH1* h_FR_tauLT_denom_EC;
        TH1* h_FR_mu_denom_EC;
        TH1* h_FR_el_denom_EC;
        TH1* h_FR_muT_denom_EC;
        TH1* h_FR_elT_denom_EC;
        
        TH1* h_FR_tau_num_EC;
        TH1* h_FR_tauLT_num_EC;
        TH1* h_FR_mu_num_EC;
        TH1* h_FR_el_num_EC;
        TH1* h_FR_muT_num_EC;
        TH1* h_FR_elT_num_EC;
        
     

	

		std::vector<TH1*>  h_H_mass_FR_types;
		std::vector<TH1*>  h_H_mass_signal_types;
        std::vector<TH1*>  h_H_mass_FRt_types;
        std::vector<TH1*>  h_H_mass_cat1_types;
        std::vector<TH1*>  h_H_mass_cat2_types;
        
        
        std::vector<TH1*> h_signal_pt1_types;
        std::vector<TH1*> h_signal_pt2_types;
        std::vector<TH1*> h_signal_SumPt_types;
        
        std::vector<TH2*> h_category0_pt_types;
        std::vector<TH1*> h_category1_pt_types;
        std::vector<TH1*> h_category2_pt_types;
        
        std::vector<TH2*> h_category0_jet_pt_types;
        std::vector<TH1*> h_category1_jet_pt_types;
        std::vector<TH1*> h_category2_jet_pt_types;
        
        std::vector<TH2*> h_category0_jet_BB_pt_types;
        std::vector<TH2*> h_category0_jet_EE_pt_types;
        std::vector<TH2*> h_category0_jet_EB_pt_types;
        std::vector<TH2*> h_category0_jet_BE_pt_types;
        
        std::vector<TH1*> h_category1_jet_EC_pt_types;
        std::vector<TH1*> h_category2_jet_EC_pt_types;
        
        
        std::vector<TH2*> h_category0_jetRef_pt_types;
        std::vector<TH1*> h_category1_jetRef_pt_types;
        std::vector<TH1*> h_category2_jetRef_pt_types;
        
        
        TH1* h_Nvertex_NoCut;
        TH1* h_Nvertex_NoCut_W;
        TH1* h_Nvertex_AfterZ;
        TH1* h_Nvertex_AfterZ_W;
        TH1* h_Nvertex_AfterZH;
        TH1* h_Nvertex_AfterZH_W;
        
        reweight::LumiReWeighting* LumiWeights_;
        ofstream log1;
        ofstream logFR;
        ofstream logS;
        ofstream log_events;
        ofstream log_files;
        
	
        

// properties
	std::string InTreeName;
	double maxDeltaR;
	double BestMassForZ;
	double dZvertex;
	double bTagValue;
	
	
	
	std::string doubEle;
	std::string doubEle2;
	
    std::string doubMu;
    std::string doubMu2;
    std::string doubMu3;
    
   
   
    bool isSimulation;
    bool is2011;
   
    bool is2012_53;
   
    bool vetoMuonTrigger;
    bool vetoElectronTrigger;
    
    double Cut_tau_base_Pt;
    double Cut_tautau_Pt_1;
    double Cut_tautau_Pt_2;
    
    double Cut_leptau_Pt;
    
  
    
   
    
    bool UseSumPtCut;
    double Cut_tautau_sumPt;
    double Cut_mutau_sumPt;
    double Cut_etau_sumPt;
    double Cut_leplep_sumPt;
    
    double Cut_tautau_sumPt_FR;
    double Cut_mutau_sumPt_FR;
    double Cut_etau_sumPt_FR;
    double Cut_leplep_sumPt_FR;
    
    double relIso_MT;
    double relIso_ET;
    double relIso_EM;
   
    bool IgnoreSF;
    bool IgnorePUW;
	
    bool printoutEvents;
    double examineEvent;
    bool removeTauOverlap;
    
    bool UseLongEvent;
    double OverM;
    double BelowM;
    
    bool DoubleE;
    bool DoubleM;
    
     bool ShiftTauES_up;
    bool ShiftTauES_down;
    bool onlyTrigger;
    bool onlyIDIso;
    bool SFShiftUp_Mu;
    bool SFShiftDown_Mu;
    bool SFShiftUp_Ele;
    bool SFShiftDown_Ele;
    double SystUncert_ES;
    
    bool FillPDFInfo;
    bool FillSVmassInfo;
    bool FillZZgenInfo;
    
    double tau_shape_iso_cut;
    double lep_shape_iso_cut;
    
    bool IgnoreLTforFR_TT;
    bool IgnoreLTforFR_LT;
    bool IgnoreLTforFR_LL;
    
            
    
    
    // bookkeeping variables
    
    ofstream lumi;
	long current_run;
	long current_lumi;
	SSummedVar< Int_t > m_allEvents;


// output variables
Int_t o_run;
Int_t o_lumi;
Int_t o_event;
Bool_t o_pass;
Bool_t o_FR;
Bool_t o_FRt;
Float_t o_event_weight;
Float_t o_px_Z1;
Float_t o_px_Z2;
Float_t o_px_H1;
Float_t o_px_H2;

Float_t o_py_Z1;
Float_t o_py_Z2;
Float_t o_py_H1;
Float_t o_py_H2;

Float_t o_pz_Z1;
Float_t o_pz_Z2;
Float_t o_pz_H1;
Float_t o_pz_H2;

Float_t o_E_Z1;
Float_t o_E_Z2;
Float_t o_E_H1;
Float_t o_E_H2;

Float_t o_pdg_Z1;
Float_t o_pdg_Z2;
Float_t o_pdg_H1;
Float_t o_pdg_H2;

Float_t o_MET_x;
Float_t o_MET_y;
Float_t o_covMET_00;
Float_t o_covMET_01;
Float_t o_covMET_10;
Float_t o_covMET_11;


//pdf info
Float_t o_pdf_alphaQCD;
Float_t o_pdf_alphaQED;
Float_t o_pdf_qScale;
Float_t o_pdf_weight;
Float_t o_pdf_scalePDF;
Float_t o_pdf_binningValue0;
Float_t o_pdf_id_1;
Float_t o_pdf_id_2;
Float_t o_pdf_x_1;
Float_t o_pdf_x_2;
Float_t o_pdf_xPDF_1;
Float_t o_pdf_xPDF_2;
Bool_t o_pdf_hasPDF; 
Bool_t o_pdf_hasBinningValues; 
UInt_t o_pdf_signalProcessID; 
Int_t o_pdf_binningValueSize; 

// ZZgen info

Float_t o_gen_pt_Z1;
Float_t o_gen_pt_Z2;
Float_t o_gen_eta_Z1;
Float_t o_gen_eta_Z2;
Float_t o_gen_phi_Z1;
Float_t o_gen_phi_Z2;
Float_t o_gen_mass_Z1;
Float_t o_gen_mass_Z2;





   // Macro adding the functions for dictionary generation
   ClassDef( Analysis, 0 );

}; // class Analysis

#endif // Analysis_H

