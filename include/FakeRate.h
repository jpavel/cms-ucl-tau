// Dear emacs, this is -*- c++ -*-
// $Id: CycleCreators.py 173 2010-05-12 15:49:33Z krasznaa $
#ifndef FakeRate_H
#define FakeRate_H

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

// my classes
#include "myevent.h"
#include "TLorentzVector.h"
#include "LumiReweightingStandAlone.h"
/**
 *   @short Put short description of class here
 *
 *          Put a longer description over here...
 *
 *  @author Put your name here
 * @version $Revision: 173 $
 */
class FakeRate : public SCycleBase {

public:
   /// Default constructor
   FakeRate();
   /// Default destructor
   ~FakeRate();

   /// Function called at the beginning of the cycle
   virtual void BeginCycle() throw( SError );
   /// Function called at the end of the cycle
   virtual void EndCycle() throw( SError );

   /// Function called at the beginning of a new input data
   virtual void BeginInputData( const SInputData& ) throw( SError );
   /// Function called after finishing to process an input data
   virtual void EndInputData  ( const SInputData& ) throw( SError );

   /// Function called after opening each new input file
   virtual void BeginInputFile( const SInputData& ) throw( SError );

   /// Function called for every event
   virtual void ExecuteEvent( const SInputData&, Double_t ) throw( SError );
   
   double deltaR(double eta1, double phi1, double eta2, double phi2);
   bool EleMVANonTrigId(float pt, float eta, double value);
   bool PFMuonID(myobject mu);
   double RelIsoMu(myobject mu);
   double RelIsoEl(myobject el);
   bool Trg_MC_12(myevent* m);
   bool WZ_Rej(myevent *m, myobject mu);
   
   bool isGoodMu(myobject mu);
   bool isGoodEl(myobject el);


private:
   //
   // Put all your private variables here
   //

	// input variables
	
	myevent *m;
	
	// histograms
	
	std::vector<int> index_number;
	std::vector<int> evt_number;
	std::vector<int> run_number;
	std::vector<int> lumi_number;
	std::vector<int> evt_type;
	
        TH1* h_el_n;
        TH1* h_el_cut;
        TH1* h_event_type;
        TH1* h_event_type_medium;
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
        TH1* h_eH_eTau_pt;
        TH1* h_tauH_eTau_pt;
        TH1* h_H_eTau_pt;
        TH1* h_H_eTau_mass;
        TH1* h_muH_muTau_pt;
        TH1* h_tauH_muTau_pt;
        TH1* h_H_muTau_pt;
        TH1* h_H_muTau_mass;
        TH1* h_muH_eMu_tightMuIso_pt;
        TH1* h_eH_eMu_tightMuIso_pt;
        TH1* h_H_eMu_tightMuIso_pt;
        TH1* h_H_eMu_tightMuIso_mass;
        TH1* h_muH_eMu_looseMuIso_pt;
        TH1* h_eH_eMu_looseMuIso_pt;
        TH1* h_H_eMu_looseMuIso_pt;
        TH1* h_H_eMu_looseMuIso_mass;
        TH1* h_tau1H_tauTau_pt;
        TH1* h_tau2H_tauTau_pt;
        TH1* h_H_tauTau_pt;
        TH1* h_H_tauTau_mass;
        TH1* h_H_pt;
        TH1* h_H_mass;
        
        TH1* h_n_goodEl;
        TH1* h_n_goodMu;
        
        TH1* h_el_relIso;
        TH1* h_mu_relIso;
        
        TH1* h_n_goodEl_Hcand;
        TH1* h_n_goodMu_Hcand;
        TH1* h_n_goodTau_Hcand;
        
        TH1* h_medium;
        TH1* h_tight;
        TH1*  h_denom;
        
        std::vector<TH1*>  h_denom_types;
		std::vector<TH1*>  h_medium_types;
		std::vector<TH1*>  h_tight_types;
		
		std::vector<TH1*>  h_H_mass_types;
	
          reweight::LumiReWeighting* LumiWeights_;

// properties
	std::string InTreeName;
	double Ptcut;
	double BestMassForZ;
	double dZvertex;
	double bTagValue;
	double maxEvent;
	bool   syncTest;
	
	std::string doubEle;
	std::string doubEle2;
	
    std::string doubMu;
    std::string doubMu2;
    std::string doubMu3;
    
    bool vetoMuonTrigger;
    bool vetoElectronTrigger;
    
      bool isSimulation;
    bool is2011;
    bool is2012_52;
    bool is2012_53;
    bool useTruePileUp;
    double maxDeltaR;
	

// output variables


   // Macro adding the functions for dictionary generation
   ClassDef( FakeRate, 0 );

}; // class FakeRate

#endif // FakeRate_H

