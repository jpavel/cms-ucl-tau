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
  std::vector<Float_t>* o_event_weight = 0;
  std::vector<Float_t>* o_px = 0;
  std::vector<Float_t>* o_py = 0;
  std::vector<Float_t>* o_pz = 0;
  std::vector<Float_t>* o_E = 0;
  std::vector<Int_t>* o_pdg = 0;
  std::vector<Float_t>* o_MET = 0; //(Met_x,Met_y)
  std::vector<Float_t>* o_covMET = 0; // covMatrix(00,01,10,11)
  // new branch
  std::vector<Float_t> *o_svMass = new std::vector<Float_t>;
//   float met, metPhi;
//   float covMet11, covMet12; 
//   float covMet21, covMet22;
//   float l1M, l1Px, l1Py, l1Pz;
//   float l2M, l2Px, l2Py, l2Pz;
//   float mTrue;
//   // branch adresses
  tree->SetBranchAddress("o_pass", &o_pass);
  tree->SetBranchAddress("o_event_weight"          , &o_event_weight       );
  tree->SetBranchAddress("o_px"         , &o_px     );
  tree->SetBranchAddress("o_py"      , &o_py   );
  tree->SetBranchAddress("o_pz"      , &o_pz   );
  tree->SetBranchAddress("o_E"      , &o_E   );
  tree->SetBranchAddress("o_pdg"      , &o_pdg   );
  tree->SetBranchAddress("o_MET"         , &o_MET        );
  tree->SetBranchAddress("o_covMET"        , &o_covMET       );
  // adding branch with results
  TBranch *svBranch = tree->Branch("o_svMass" , &o_svMass);
  int nevent = tree->GetEntries();
  for(int i=0; i<nevent; ++i){
    o_svMass->clear();
    tree->GetEvent(i);
    if(o_pass) std::cout << "event " << i+1 << " : " << o_pass << std::endl;
    if(!o_pass){ svBranch->Fill(); continue;}
    // setup MET input vector
    std::cout << "The MET is " << o_MET->at(0) << " " << o_MET->at(1) << std::endl;
    if(o_MET->size()!=2){ svBranch->Fill(); continue;}
    NSVfitStandalone::Vector measuredMET(o_MET->at(0), o_MET->at(1), 0); 
    // setup the MET significance
     TMatrixD covMET(2,2);
     std::cout << "The cov MET is " << o_covMET->at(0) << " " << o_covMET->at(1) << " : " << o_covMET->at(2) << " : " << o_covMET->at(3) << std::endl;
     if(o_covMET->size()!=4){ svBranch->Fill(); continue;}
       covMET[0][0] = o_covMET->at(0);
       covMET[0][1] = o_covMET->at(1);
       covMET[1][0] = o_covMET->at(2);
       covMET[1][1] = o_covMET->at(3);
//     // setup measure tau lepton vectors 
       if(o_px->size()!=4 || o_py->size()!=4 || o_pz->size()!=4 || o_E->size()!=4) continue;
       std::cout << "the first vector is " << o_px->at(2)<< " : " << o_py->at(2)<< " : " << o_pz->at(2)<< " : " << o_E->at(2) << " : " << o_pdg->at(2) << std::endl;
       std::cout << "the second vector is " << o_px->at(3)<< " : " << o_py->at(3)<< " : " << o_pz->at(3)<< " : " << o_E->at(3) << " : " << o_pdg->at(3) <<std::endl;
       NSVfitStandalone::LorentzVector l1(o_px->at(2), o_py->at(2), o_pz->at(2), o_E->at(2));
       NSVfitStandalone::LorentzVector l2(o_px->at(3), o_py->at(3), o_pz->at(3), o_E->at(3));
       std::vector<NSVfitStandalone::MeasuredTauLepton> measuredTauLeptons;
       measuredTauLeptons.push_back(NSVfitStandalone::MeasuredTauLepton(abs(o_pdg->at(2))==15 ? NSVfitStandalone::kHadDecay : NSVfitStandalone::kLepDecay, l1));
       measuredTauLeptons.push_back(NSVfitStandalone::MeasuredTauLepton(abs(o_pdg->at(3))==15 ? NSVfitStandalone::kHadDecay : NSVfitStandalone::kLepDecay, l2));
//     // construct the class object from the minimal necesarry information
      NSVfitStandaloneAlgorithm algo(measuredTauLeptons, measuredMET, covMET, 1);
      algo.addLogM(false);
      algo.integrateMarkovChain();

      double mass = algo.mass(); 
      double diTauMassErr = algo.massUncert();
//     // apply customized configurations if wanted (examples are given below)
//     algo.maxObjFunctionCalls(5000);
//     //algo.addLogM(false);
//     //algo.metPower(0.5)
//     // run the fit
//     algo.fit();
//     // retrieve the results upon success
//     std::cout << "... m truth : " << mTrue  << std::endl;
    if(algo.isValidSolution()){
      std::cout << "... m svfit : " << mass << "+/-" << diTauMassErr << " " << o_svMass->size() << std::endl;
      o_svMass->push_back(mass);
      o_svMass->push_back(diTauMassErr);
    }
    else{
      std::cout << "... m svfit : ---" << std::endl;
    }
    svBranch->Fill();
  }
  o_svMass->clear();
  tree->Write("", TObject::kOverwrite);
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
