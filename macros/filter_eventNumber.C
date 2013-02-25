#include "TChain.h"
#include "TFile.h"
#include "myevent.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>



#include "selection.h"

#ifdef __CINT__
#pragma link C++ class myevent+;
#pragma link C++ class myobject+;
#endif

/*
 * A script to filter out events based on their run and event number. 
 * The first parameter of the script is text file with the list of input files, 
 * second is text file containing 2 columns separated by space.
 * First column is the run number and the second is event number.
 * Last parameter is amount of events in input files to process.
 */

int filter_eventNumber(std::string inputFiles, std::string eventFile, long n_evt = -1)
{
	long TotalEvents=n_evt;
	
    
    bool debug = false;
    

	
	TChain *chain = new TChain("t");
	
    std::ifstream myfile;
	myfile.open(inputFiles.c_str());
	if (myfile.is_open())
	{	
	     std::string current = "";
		 
	    while ( myfile.good() )
	    {
		  std::string inputFile;
		  myfile >> inputFile;
		  if(debug) std::cout << inputFile << std::endl;
		  if(inputFile.compare(current)==0) continue;
		  if(debug) std::cout << "Another unique file!" << std::endl;		  
		  if(inputFile.length() > 0) chain->Add(TString(inputFile));
		  current = inputFile;
		}
		myfile.close();
   	}
	
	// reading events;
	
	std::vector<long> run_number;
	std::vector<long> event_number;
	
	myfile.open(eventFile.c_str());
	if (myfile.is_open())
	{
		while( myfile.good())
		{
			long myNumber;
			myfile >> myNumber;
			if(debug) std::cout << " run number is " << myNumber << std::endl;
			run_number.push_back(myNumber);
			
			myfile >> myNumber;
			if(debug) std::cout << " event number is " << myNumber << std::endl;
			event_number.push_back(myNumber);
		}
		myfile.close();
	}
	
	event_number.pop_back();
	run_number.pop_back();
	
	if(debug) std::cout << "Sizes are " << event_number.size() << " " << run_number.size() << std::endl;
	if(debug){
		for(uint i = 0; i < event_number.size(); i++)
		{
			std::cout << run_number[i] << " " << event_number[i] << std::endl;
		}
	}
	
	
	

	
	//////////////////////// end of modular part ////////////////////////////////////////
	/////////////////////////COMMON part //////////////////////////////////////////
	myevent* in = new myevent();
	chain->SetBranchAddress("myevent",&in);
	
	long MaxEvents = chain->GetEntries();
	if(TotalEvents > MaxEvents || TotalEvents < 0) TotalEvents=MaxEvents;
	
	std::cout << "There are " << MaxEvents << " entries." << std::endl;
	
	
	//bookkeeping
	ofstream lumi;
	long current_run=-1;
	long current_lumi=-1;
    long m_allEvents=0;
	lumi.open("lumi.csv");
	
	//output definition
	
	 TFile *newFile = new TFile("output.root","recreate");
	TChain *newchain = (TChain*)chain->CloneTree(0);
	 TTree *tree = newchain->GetTree();
	
	
	for(uint i =0; i < TotalEvents; i++)
	{
		chain->GetEntry(i);
		m_allEvents++;
		
		if(debug) std::cout << "Processing entry " << i << " event: " << in->eventNumber << std::endl;
		if(i%1000==0)std::cout << "Analyzing entry no. " << i << std::endl;
		
		// storing lumis
		if(in->runNumber!=current_run || in->lumiNumber!=current_lumi){
			lumi << in->runNumber << " " << in->lumiNumber << std::endl;
			current_run=in->runNumber;
			current_lumi=in->lumiNumber;
		}
		
		if(PassFilter(in, debug, run_number, event_number)
		   ) tree->Fill();
	}
	
	newFile->cd();
	newFile->Write();
	newFile->Close();
	
	 ofstream log1;       
     log1.open("total.txt");
     log1 << m_allEvents << std::endl;
     log1.close();
     
	return 0;
}
