/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Exectuable: TMVAClassificationApplication                                      *
 *                                                                                *
 * This macro provides a simple example on how to use the trained classifiers     *
 * within an analysis module                                                      *
 **********************************************************************************/

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#endif

using namespace TMVA;

void TMVAClassificationApplication( TString fname = "./tmva_class_example.root" ) 
{   
#ifdef __CINT__
   gROOT->ProcessLine( ".O0" ); // turn off optimization in CINT
#endif

   //---------------------------------------------------------------

   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // --- Cut optimisation
  
   Use["KNN"]             = 1; // k-nearest neighbour method
   //
  
   std::cout << std::endl;
   std::cout << "==> Start TMVAClassificationApplication" << std::endl;

   

   // --------------------------------------------------------------------------------------------------

   // --- Create the Reader object

   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    

   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
   Float_t var1, var2;
   Float_t var3;
   

   
   reader->AddVariable( "pt_eH", &var1 );
   reader->AddVariable( "max(pt_jet_eH,pt_eH)", &var2 );
   reader->AddVariable( "njets",                &var3 );
   
   // Spectator variables declared in the training have to be added to the reader, too
   //~ Float_t spec1,spec2;
   //~ reader->AddSpectator( "spec1 := var1*2",   &spec1 );
   //~ reader->AddSpectator( "spec2 := var1*3",   &spec2 );

   //~ Float_t Category_cat1, Category_cat2, Category_cat3;
   //~ if (Use["Category"]){
      //~ // Add artificial spectators for distinguishing categories
      //~ reader->AddSpectator( "Category_cat1 := var3<=0",             &Category_cat1 );
      //~ reader->AddSpectator( "Category_cat2 := (var3>0)&&(var4<0)",  &Category_cat2 );
      //~ reader->AddSpectator( "Category_cat3 := (var3>0)&&(var4>=0)", &Category_cat3 );
   //~ }

   // --- Book the MVA methods

   TString dir    = "weights/";
   TString prefix = "TMVAClassification";

   // Book method(s)
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
         reader->BookMVA( methodName, weightfile ); 
      }
   }
   
   // Book output histograms
   UInt_t nbin = 100;
   TH1F   *histKNN(0);
   TH1F	  *BG_mass(0);
   
   if (Use["KNN"])           histKNN     = new TH1F( "MVA_KNN",           "MVA_KNN",           nbin,  0, 1 );
   // output histograms
   BG_mass=new TH1F( "h_BG_mass",  "Reducible background shape",           300,  0, 300 );
   


   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //   
   TFile *input(0);
   if (gSystem->AccessPathName( fname )){  // file does not exist in local directory
      gSystem->Exec("wget http://root.cern.ch/files/tmva_class_example.root");
	  fname = "./tmva_class_example.root";
  }else{
	input= TFile::Open( fname );
  }
  if (!input) {
     std::cout << "ERROR: could not open data file " << fname << std::endl;
     exit(1);
  }
   std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;
   
   // --- Event loop

   // Prepare the event tree
   // - here the variable names have to corresponds to your tree
   // - you can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
   std::cout << "--- Select signal sample" << std::endl;
   TTree* theTree = (TTree*)input->Get("FakeTreeData");
   Double_t pt_eH, pt_jet_eH,mass;
   Int_t njets;
   // just for lep2. If you want more, just connect additional branches
   theTree->SetBranchAddress( "pt_eH", &pt_eH );
   theTree->SetBranchAddress( "pt_jet_eH", &pt_jet_eH );
   theTree->SetBranchAddress( "njets", &njets );
   theTree->SetBranchAddress( "mass", &mass );
   
   //~ // Efficiency calculator for cut method
   //~ Int_t    nSelCutsGA = 0;
   //~ Double_t effS       = 0.7;

   std::vector<Float_t> vecVar(4); // vector for EvaluateMVA tests

   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {

      if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

      theTree->GetEntry(ievt);

	 // evaluating for lep2
      var1 = pt_eH;
      var2 = max(pt_eH,pt_jet_eH);
      var3 = njets;

      // --- Return the MVA outputs and fill into histograms

      
	//  std::cout << reader->EvaluateMVA( "KNN method"           ) << std::endl;

      double kNN_out=reader->EvaluateMVA( "KNN method"           );
      histKNN    ->Fill( kNN_out  );
     
      double BG_weight=kNN_out/(1-kNN_out);
	  BG_mass->Fill(mass,BG_weight);

     
   }

   // Get elapsed time
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();

  

  

   // --- Write histograms

   TFile *target  = new TFile( "TMVApp.root","RECREATE" );
   
   histKNN    ->Write();
   BG_mass->Write();
   
   
   target->Close();

   std::cout << "--- Created root file: \"TMVApp.root\" containing the MVA output histograms" << std::endl;
  
   delete reader;
    
   std::cout << "==> TMVAClassificationApplication is done!" << endl << std::endl;
} 
