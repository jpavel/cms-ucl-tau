#include <TFile.h>
#include <TSystem.h>
#include <TROOT.h>
//#include "DataFormats/FWLite/interface/Event.h"
//#include "DataFormats/FWLite/interface/Handle.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

#include "TTree.h"
#include "TFile.h"

#include "TauAnalysis/CandidateTools/interface/NSVfitStandaloneAlgorithm.h"
#include <vector>

#ifdef __MAKECINT__
#pragma link C++ class std::vector<Float_t>+;
#endif

//#include <vector.h>
/**
   \class nsvfitStandalone nsvfitStandalone.cc "TauAnalysis/CandidateTools/bin/nsvfitStandalone.cc"
   \brief Basic example of the use of the standalone version of NSVfit
#ifdef __MAKECINT__
#pragma link C++ class vector<float>+;
#endif
   This is an example executable to show the use of the standalone version of NSVfit form a flat 
   n-tuple or single event.
*/

void singleEvent()
{
  /* 
     This is a single event for testing in the integration mode.
  */
  // define MET
  Vector MET(11.7491, -51.9172, 0.); 
  // define MET covariance
  TMatrixD covMET(2, 2);
  /*
  covMET[0][0] = 0.;
  covMET[1][0] = 0.;
  covMET[0][1] = 0.;
  covMET[1][1] = 0.;
  */
  covMET[0][0] = 787.352;
  covMET[1][0] = -178.63;
  covMET[0][1] = -178.63;
  covMET[1][1] = 179.545;
  // define lepton four vectors
  NSVfitStandalone::LorentzVector l1( 28.9132, -17.3888, 36.6411, 49.8088); //lepton
  NSVfitStandalone::LorentzVector l2(-24.19  ,  8.77449, 16.9413, 30.8086); //tau
  std::vector<NSVfitStandalone::MeasuredTauLepton> measuredTauLeptons;
  measuredTauLeptons.push_back(NSVfitStandalone::MeasuredTauLepton(NSVfitStandalone::kHadDecay, l2));
  measuredTauLeptons.push_back(NSVfitStandalone::MeasuredTauLepton(NSVfitStandalone::kLepDecay, l1));
  // define algorithm (set the debug level to 3 for testing)
  NSVfitStandaloneAlgorithm algo(measuredTauLeptons, MET, covMET, /*debug=*/0);
  algo.addLogM(false);
  /* 
     the following lines show how to use the different methods on a single event
  */
  // minuit fit method
  //algo.fit();
  // integration by VEGAS (same as function algo.integrate() that has been in use when markov chain integration had not yet been implemented)
  //algo.integrateVEGAS();
  // integration by markov chain MC
  algo.integrateMarkovChain();

  double mass = algo.getMass(); // mass uncertainty not implemented yet
  if(algo.isValidSolution()){
    std::cout << "found mass    = " << mass << std::endl;
  }
  else{
    std::cout << "sorry -- status of NLL is not valid [" << algo.isValidSolution() << "]" << std::endl;
  }
  return;
}

void eventsFromTree(int argc, char* argv[]) 
{
  // parse arguments
  if ( argc < 3 ) {
    std::cout << "Usage : " << argv[0] << " [inputfile.root] [tree_name]" << std::endl;
    return;
  }

  // get intput directory up to one before mass points
  TFile* file = new TFile(argv[1],"update"); 
  // access tree in file
  TTree* tree = (TTree*) file->Get(argv[2]);
  std::cout << "My Tree has "<< tree->GetEntries() << " entries. " << std::endl; 
  // input variables
  Bool_t  o_pass;
  Bool_t o_FR;
  Bool_t o_FRt;
  Float_t o_event_weight;
  Int_t o_type;
  Int_t o_run;
  Int_t o_lumi;
  Int_t o_event;

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
  
  // FR
  
  Int_t o_FR_n;
std::vector<Int_t>* o_FR_type=0;
std::vector<Bool_t>* o_FRt=0;


std::vector<Float_t>* o_FR_px_H1=0;
std::vector<Float_t>* o_FR_px_H2=0;

std::vector<Float_t>* o_FR_py_H1=0;
std::vector<Float_t>* o_FR_py_H2=0;

std::vector<Float_t>* o_FR_pz_H1=0;
std::vector<Float_t>* o_FR_pz_H2=0;

std::vector<Float_t>* o_FR_E_H1=0;
std::vector<Float_t>* o_FR_E_H2=0;

std::vector<Float_t>* o_FR_pdg_H1=0;
std::vector<Float_t>* o_FR_pdg_H2=0;


  Float_t o_MET_x;
  Float_t o_MET_y;
  Float_t o_covMET_00;
  Float_t o_covMET_01;
  Float_t o_covMET_10;
  Float_t o_covMET_11;

  // new branch
  Float_t o_svMass=-100.;
  Float_t o_svMass_unc=-100.;
  

  Bool_t  o_pass2;
  Bool_t o_FR2;
  Float_t o_event_weight2;
  Int_t o_type2;
  Int_t o_run2;
  Int_t o_lumi2;
  Int_t o_event2;
  	
  Int_t o_FR_n2;	
  std::vector<Bool_t>* o_FRt2;
   	
  std::vector<Float_t>* o_FR_svMass;
  std::vector<Float_t>* o_FR_svMass_unc;
  std::vector<Int_t>* o_FR_type2;
  
  o_FRt2 = new std::vector<Bool_t>;
   	
  o_FR_svMass = new std::vector<Float_t>;
  o_FR_svMass_unc = new std::vector<Float_t>;
  o_FR_type2 = new std::vector<Int_t>;
  
  	

//   // branch adresses
  tree->SetBranchAddress("o_pass", &o_pass);
  tree->SetBranchAddress("o_FR", &o_FR);
  tree->SetBranchAddress("o_FRt", &o_FRt);
  tree->SetBranchAddress("o_event_weight"          , &o_event_weight       );
  tree->SetBranchAddress("o_type", &o_type);
  tree->SetBranchAddress("o_run", &o_run);
  tree->SetBranchAddress("o_lumi", &o_lumi);
  tree->SetBranchAddress("o_event", &o_event);
  tree->SetBranchAddress("o_px_Z1"         , &o_px_Z1     );
  tree->SetBranchAddress("o_px_Z2"         , &o_px_Z2     );
  tree->SetBranchAddress("o_px_H1"         , &o_px_H1     );
  tree->SetBranchAddress("o_px_H2"         , &o_px_H2     );
  tree->SetBranchAddress("o_py_Z1"         , &o_py_Z1     );
  tree->SetBranchAddress("o_py_Z2"         , &o_py_Z2     );
  tree->SetBranchAddress("o_py_H1"         , &o_py_H1     );
  tree->SetBranchAddress("o_py_H2"         , &o_py_H2     );
  tree->SetBranchAddress("o_pz_Z1"         , &o_pz_Z1     );
  tree->SetBranchAddress("o_pz_Z2"         , &o_pz_Z2     );
  tree->SetBranchAddress("o_pz_H1"         , &o_pz_H1     );
  tree->SetBranchAddress("o_pz_H2"         , &o_pz_H2     );
  tree->SetBranchAddress("o_E_Z1"         , &o_E_Z1     );
  tree->SetBranchAddress("o_E_Z2"         , &o_E_Z2     );
  tree->SetBranchAddress("o_E_H1"         , &o_E_H1     );
  tree->SetBranchAddress("o_E_H2"         , &o_E_H2     );
  tree->SetBranchAddress("o_pdg_Z1"         , &o_pdg_Z1     );
  tree->SetBranchAddress("o_pdg_Z2"         , &o_pdg_Z2     );
  tree->SetBranchAddress("o_pdg_H1"         , &o_pdg_H1     );
  tree->SetBranchAddress("o_pdg_H2"         , &o_pdg_H2     );
  
  //FR
  
  tree->SetBranchAddress("o_FR_n", &o_FR_n);
  
  tree->SetBranchAddress("o_FR_type", &o_FR_type);
  tree->SetBranchAddress("o_FR_px_H1"         , &o_FR_px_H1     );
  tree->SetBranchAddress("o_FR_px_H2"         , &o_FR_px_H2     );
  tree->SetBranchAddress("o_FR_py_H1"         , &o_FR_py_H1     );
  tree->SetBranchAddress("o_FR_py_H2"         , &o_FR_py_H2     );
  tree->SetBranchAddress("o_FR_pz_H1"         , &o_FR_pz_H1     );
  tree->SetBranchAddress("o_FR_pz_H2"         , &o_FR_pz_H2     );
  tree->SetBranchAddress("o_FR_E_H1"         , &o_FR_E_H1     );
  tree->SetBranchAddress("o_FR_E_H2"         , &o_FR_E_H2     );
  tree->SetBranchAddress("o_FR_pdg_H1"         , &o_FR_pdg_H1     );
  tree->SetBranchAddress("o_FR_pdg_H2"         , &o_FR_pdg_H2     );
  
  
  tree->SetBranchAddress("o_MET_x"         , &o_MET_x        );
  tree->SetBranchAddress("o_MET_y"         , &o_MET_y        );
  tree->SetBranchAddress("o_covMET_00"        , &o_covMET_00       );
  tree->SetBranchAddress("o_covMET_01"        , &o_covMET_01       );
  tree->SetBranchAddress("o_covMET_10"        , &o_covMET_10       );
  tree->SetBranchAddress("o_covMET_11"        , &o_covMET_11       );  
  // adding branch with results
  TTree *svTree = new TTree("svTree","Tree with SVmass");
  svTree->Branch("o_svMass" , &o_svMass, "o_svMass/F");
  svTree->Branch("o_svMass_unc" , &o_svMass_unc, "o_svMass_unc/F");
  svTree->Branch("o_pass", &o_pass2, "o_pass2/O");
  svTree->Branch("o_FR", &o_FR2, "o_FR2/O");
  
  svTree->Branch("o_event_weight", &o_event_weight2, "o_event_weight2/F");
  svTree->Branch("o_type", &o_type2, "o_type2/I");
  svTree->Branch("o_run", &o_run2, "o_run2/I");
  svTree->Branch("o_lumi", &o_lumi2, "o_lumi2/I");
  svTree->Branch("o_event", &o_event2, "o_event2/I");
  
  svTree->Branch("o_FR_n", &o_FR_n2, "o_FR_n2/I");
  svTree->Branch("o_FR_svMass" , &o_FR_svMass);
  svTree->Branch("o_FR_svMass_unc" , &o_FR_svMass_unc);
  svTree->Branch("o_FR_type", &o_FR_type2);
  svTree->Branch("o_FRt", &o_FRt2);
  

  int nevent = tree->GetEntries();
  for(int i=0; i<nevent; ++i){
    tree->GetEvent(i);
    if(o_pass||o_FR) std::cout << "event " << i+1 << " : " << o_pass << std::endl;
    else{ 
      continue;
    }
    // setup MET input vector
    // std::cout << "The MET is " << o_MET_x << " " << o_MET_y << std::endl;
    //    if(o_MET->size()!=2){ svBranch->Fill(); continue;}
    o_event_weight2=o_event_weight;
    o_type2=o_type;
    o_run2=o_run;
    o_lumi2=o_lumi;
    o_event2=o_event;
    NSVfitStandalone::Vector measuredMET(o_MET_x, o_MET_y, 0); 
    // setup the MET significance
     TMatrixD covMET(2,2);
     //     std::cout << "The cov MET is " << o_covMET_00 << " " << o_covMET_01 << " : " << o_covMET_10 << " : " << o_covMET_11 << std::endl;
     //     if(o_covMET->size()!=4){ svBranch->Fill(); continue;}
       covMET[0][0] = o_covMET_00;
       covMET[0][1] = o_covMET_01;
       covMET[1][0] = o_covMET_10;
       covMET[1][1] = o_covMET_11;
//     // setup measure tau lepton vectors 
       // std::cout << "the first vector is " << o_px_H1<< " : " << o_py_H1<< " : " << o_pz_H1<< " : " << o_E_H1 << " : " << o_pdg_H1 << std::endl;
       // std::cout << "the second vector is " << o_px_H2<< " : " << o_py_H2<< " : " << o_pz_H2<< " : " << o_E_H2 << " : " << o_pdg_H2 <<std::endl;
	if(o_pass){
       NSVfitStandalone::LorentzVector l1(o_px_H1, o_py_H1, o_pz_H1, o_E_H1);
       NSVfitStandalone::LorentzVector l2(o_px_H2, o_py_H2, o_pz_H2, o_E_H2);
       std::vector<NSVfitStandalone::MeasuredTauLepton> measuredTauLeptons;
       measuredTauLeptons.push_back(NSVfitStandalone::MeasuredTauLepton(abs(o_pdg_H1)==15 ? NSVfitStandalone::kHadDecay : NSVfitStandalone::kLepDecay, l1));
       measuredTauLeptons.push_back(NSVfitStandalone::MeasuredTauLepton(abs(o_pdg_H2)==15 ? NSVfitStandalone::kHadDecay : NSVfitStandalone::kLepDecay, l2));
//     // construct the class object from the minimal necesarry information
      NSVfitStandaloneAlgorithm algo(measuredTauLeptons, measuredMET, covMET, 1);
      algo.addLogM(false);
      algo.integrateMarkovChain();

      double mass = algo.mass(); 
      double diTauMassErr = algo.massUncert();
    if(algo.isValidSolution()){
      std::cout << "... m svfit : " << mass << "+/-" << diTauMassErr << " " << std::endl;
      o_svMass=mass;
      o_svMass_unc=diTauMassErr;
      o_pass2= o_pass;
      o_FR2=o_FR;
      //o_FRt2=o_FRt;
      
      //svTree->Fill();
    }
    else{
      std::cout << "... m svfit : ---" << std::endl;
      o_svMass=-999.;
      o_svMass_unc=-999.;
      o_pass2= 0;
      o_FR2=0;
      //o_FRt2=0;
      //svTree->Fill();
    }
   }
   if(o_FR){ // protections
	   if(o_FR_type->size()!=o_FR_n) continue;
	   if(o_FR_px_H1->size()!=o_FR_n) continue;
	   if(o_FR_py_H1->size()!=o_FR_n) continue;
	   if(o_FR_pz_H1->size()!=o_FR_n) continue;
	   if(o_FR_E_H1->size()!=o_FR_n) continue;
	   if(o_FR_px_H2->size()!=o_FR_n) continue;
	   if(o_FR_py_H2->size()!=o_FR_n) continue;
	   if(o_FR_pz_H2->size()!=o_FR_n) continue;
	   if(o_FR_E_H2->size()!=o_FR_n) continue;
	   if(o_FR_pdg_H1->size()!=o_FR_n) continue;
	   if(o_FR_pdg_H2->size()!=o_FR_n) continue;
	  
	   o_FR2=0;
	   for(int iFR=0; iFR < o_FR_n; iFR++)
	   {
	       o_FR_n2++;
	       NSVfitStandalone::LorentzVector l1(o_px_H1->at(iFR), o_py_H1->at(iFR), o_pz_H1->at(iFR), o_E_H1->at(iFR));
	       NSVfitStandalone::LorentzVector l2(o_px_H2->at(iFR), o_py_H2->at(iFR), o_pz_H2->at(iFR), o_E_H2->at(iFR));
	       std::vector<NSVfitStandalone::MeasuredTauLepton> measuredTauLeptons;
	       measuredTauLeptons.push_back(NSVfitStandalone::MeasuredTauLepton(abs(o_pdg_H1->at(iFR))==15 ? NSVfitStandalone::kHadDecay : NSVfitStandalone::kLepDecay, l1));
	       measuredTauLeptons.push_back(NSVfitStandalone::MeasuredTauLepton(abs(o_pdg_H2->at(iFR))==15 ? NSVfitStandalone::kHadDecay : NSVfitStandalone::kLepDecay, l2));
	//     // construct the class object from the minimal necesarry information
	      NSVfitStandaloneAlgorithm algo(measuredTauLeptons, measuredMET, covMET, 1);
	      algo.addLogM(false);
	      algo.integrateMarkovChain();
	
	      double mass = algo.mass(); 
	      double diTauMassErr = algo.massUncert();
	    if(algo.isValidSolution()){
	      std::cout << "... m svfit : " << mass << "+/-" << diTauMassErr << " " << std::endl;
	      o_FR_svMass->push_back(mass);
	      o_FR_svMass_unc->pusk_back(diTauMassErr);
	      o_FR2=o_FR;
	      o_FRt2->push_back(o_FRt->at(iFR));
	      o_FR_type2->push_back(o_FR_type);
	      
	      //svTree->Fill();
	    }
	    else{
	      std::cout << "... m svfit : ---" << std::endl;
	      o_FR_svMass->push_back(-999.);
	      o_FR_svMass_unc->push_back(-999.);
	      o_FRt2->push_back(0);
	      o_FR_type2->push_back(0);
	      
	     
	      //svTree->Fill();
	    }
	}
   }
    //    o_svMass=-100.;
    // o_svMass_unc=-100.;
    svTree->Fill();
  }  
  //  o_svMass=-100.;
  //  o_svMass_unc=-100.;
  svTree->Write(); //"", TObject::kOverwrite);
  
 file->Close();
  return;
}

int main(int argc, char* argv[]) 
{
  gSystem->Load( "libFWCoreFWLite" );
  gROOT->ProcessLine("#include <vector>");
  AutoLibraryLoader::enable(); 
  eventsFromTree(argc, argv);
  //  singleEvent();
  return 0;
}
