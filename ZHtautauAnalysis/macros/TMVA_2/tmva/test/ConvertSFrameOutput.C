#include "TString.h"
#include "TFile.h"
#include "TTree.h"

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

int ConvertSFrameOutput(TString filename)
{
  TFile *f; 
  std::stringstream indexes;  
  
  indexes.str("");
  indexes << filename;
  std::string input_file=indexes.str();
  f= TFile::Open(input_file.c_str());
  if(!f) {
	  std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
	  return 1;
  } else std::cout<< "File " << input_file << " succesfully opened!" << std::endl;
  
  TTree* inputTree = (TTree*)f->Get("redtree");
  
  std::cout << " The SFrame tree has " << inputTree->GetEntries() << " entries." << std::endl;
  
  TString outfileName( "FRin.root" );
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
  TTree* outTreeSig = new TTree("FakeTreeSig","Tree with inputs for fake rate");
  TTree* outTreeBG = new TTree("FakeTreeBG","Tree with inputs for fake rate");
   TTree* outTreeData = new TTree("FakeTreeData","Tree with inputs for fake rate");
  
  
  
  Int_t selected;
  Int_t isF3;
  Int_t run;
  Int_t lumi;
  Int_t event;
  Double_t weight;
  Int_t id_iso_eleW;
  Int_t id_iso_eleH;
  Double_t pt_eW;
  Double_t pt_eH;
  Double_t pt_tH;
  Double_t pt_jet_eW;
  Double_t pt_jet_eH;
  Int_t njets;
  Double_t maxPt_eW;
  Double_t maxPt_eH;
  Double_t mass;
  Double_t LT;
  Int_t count;
  
  
  Int_t o_selected;
  Int_t o_isF3;
  Int_t o_run;
  Int_t o_lumi;
  Int_t o_event;
  Double_t o_weight;
  Int_t o_id_iso_eleW;
  Int_t o_id_iso_eleH;
  Double_t o_pt_eW;
  Double_t o_pt_eH;
  Double_t o_pt_tH;
  Double_t o_pt_jet_eW;
  Double_t o_pt_jet_eH;
  Int_t o_njets;
  Double_t o_maxPt_eW;
  Double_t o_maxPt_eH;
  Double_t o_mass;
  Double_t o_LT;
  Int_t o_count;
  
  Int_t o_BG_selected;
  Int_t o_BG_isF3;
  Int_t o_BG_run;
  Int_t o_BG_lumi;
  Int_t o_BG_event;
  Double_t o_BG_weight;
  Int_t o_BG_id_iso_eleW;
  Int_t o_BG_id_iso_eleH;
  Double_t o_BG_pt_eW;
  Double_t o_BG_pt_eH;
  Double_t o_BG_pt_tH;
  Double_t o_BG_pt_jet_eW;
  Double_t o_BG_pt_jet_eH;
  Int_t o_BG_njets;
  Double_t o_BG_maxPt_eW;
  Double_t o_BG_maxPt_eH;
  Double_t o_BG_mass;
  Double_t o_BG_LT;
  Int_t o_BG_count;
  
  Int_t o_Data_selected;
  Int_t o_Data_isF3;
  Int_t o_Data_run;
  Int_t o_Data_lumi;
  Int_t o_Data_event;
  Double_t o_Data_weight;
  Int_t o_Data_id_iso_eleW;
  Int_t o_Data_id_iso_eleH;
  Double_t o_Data_pt_eW;
  Double_t o_Data_pt_eH;
  Double_t o_Data_pt_tH;
  Double_t o_Data_pt_jet_eW;
  Double_t o_Data_pt_jet_eH;
  Int_t o_Data_njets;
  Double_t o_Data_maxPt_eW;
  Double_t o_Data_maxPt_eH;
  Double_t o_Data_mass;
  Double_t o_Data_LT;
  Int_t o_Data_count;
  
  inputTree->SetBranchAddress("selected", &selected);
  inputTree->SetBranchAddress("isF3", &isF3);
  inputTree->SetBranchAddress("run", &run);
  inputTree->SetBranchAddress("lumi", &lumi);
  inputTree->SetBranchAddress("event", &event);
  inputTree->SetBranchAddress("weight", &weight);
  inputTree->SetBranchAddress("id_iso_eleW", &id_iso_eleW);
  inputTree->SetBranchAddress("id_iso_eleH", &id_iso_eleH);
  inputTree->SetBranchAddress("pt_eW", &pt_eW);
  inputTree->SetBranchAddress("pt_eH", &pt_eH);
  inputTree->SetBranchAddress("pt_tH", &pt_tH);
  inputTree->SetBranchAddress("pt_jet_eW", &pt_jet_eW);
  inputTree->SetBranchAddress("pt_jet_eH", &pt_jet_eH);
  inputTree->SetBranchAddress("njets", &njets);
  inputTree->SetBranchAddress("maxPt_eW", &maxPt_eW);
  inputTree->SetBranchAddress("maxPt_eH", &maxPt_eH);
  inputTree->SetBranchAddress("mass", &mass);
  inputTree->SetBranchAddress("LT", &LT);
  inputTree->SetBranchAddress("count", &count);
  
  
  outTreeSig->Branch("selected", &o_selected, "o_selected/I");
  outTreeSig->Branch("isF3", &o_isF3, "o_isF3/I");
  outTreeSig->Branch("run", &o_run, "o_run/I");
  outTreeSig->Branch("lumi", &o_lumi, "o_lumi/I");
  outTreeSig->Branch("event", &o_event, "o_event/I");
  outTreeSig->Branch("weight", &o_weight, "o_weight/D");
  outTreeSig->Branch("id_iso_eleW", &o_id_iso_eleW, "o_id_iso_eleW/I");
  outTreeSig->Branch("id_iso_eleH", &o_id_iso_eleH, "o_id_iso_eleH/I");
  outTreeSig->Branch("pt_eW", &o_pt_eW, "o_pt_eW/D");
  outTreeSig->Branch("pt_eH", &o_pt_eH, "o_pt_eH/D");
  outTreeSig->Branch("pt_tH", &o_pt_tH, "o_pt_tH/D");
  outTreeSig->Branch("pt_jet_eW", &o_pt_jet_eW, "o_pt_jet_eW/D");
  outTreeSig->Branch("pt_jet_eH", &o_pt_jet_eH, "o_pt_jet_eH/D");
  outTreeSig->Branch("njets", &o_njets, "o_njets/I");
  outTreeSig->Branch("maxPt_eW", &o_maxPt_eW, "o_maxPt_eW/D");
  outTreeSig->Branch("maxPt_eH", &o_maxPt_eH, "o_maxPt_eH/D");
  outTreeSig->Branch("mass", &o_mass, "o_mass/D");
  outTreeSig->Branch("LT", &o_LT, "o_LT/D");
  outTreeSig->Branch("count", &o_count, "o_count/I");
  
  
    outTreeBG->Branch("selected", &o_BG_selected, "o_BG_selected/I");
  outTreeBG->Branch("isF3", &o_BG_isF3, "o_BG_isF3/I");
  outTreeBG->Branch("run", &o_BG_run, "o_BG_run/I");
  outTreeBG->Branch("lumi", &o_BG_lumi, "o_BG_lumi/I");
  outTreeBG->Branch("event", &o_BG_event, "o_BG_event/I");
  outTreeBG->Branch("weight", &o_BG_weight, "o_BG_weight/D");
  outTreeBG->Branch("id_iso_eleW", &o_BG_id_iso_eleW, "o_BG_id_iso_eleW/I");
  outTreeBG->Branch("id_iso_eleH", &o_BG_id_iso_eleH, "o_BG_id_iso_eleH/I");
  outTreeBG->Branch("pt_eW", &o_BG_pt_eW, "o_BG_pt_eW/D");
  outTreeBG->Branch("pt_eH", &o_BG_pt_eH, "o_BG_pt_eH/D");
  outTreeBG->Branch("pt_tH", &o_BG_pt_tH, "o_BG_pt_tH/D");
  outTreeBG->Branch("pt_jet_eW", &o_BG_pt_jet_eW, "o_BG_pt_jet_eW/D");
  outTreeBG->Branch("pt_jet_eH", &o_BG_pt_jet_eH, "o_BG_pt_jet_eH/D");
  outTreeBG->Branch("njets", &o_BG_njets, "o_BG_njets/I");
  outTreeBG->Branch("maxPt_eW", &o_BG_maxPt_eW, "o_BG_maxPt_eW/D");
  outTreeBG->Branch("maxPt_eH", &o_BG_maxPt_eH, "o_BG_maxPt_eH/D");
  outTreeBG->Branch("mass", &o_BG_mass, "o_BG_mass/D");
  outTreeBG->Branch("LT", &o_BG_LT, "o_BG_LT/D");
  outTreeBG->Branch("count", &o_BG_count, "o_BG_count/I");
  
      outTreeData->Branch("selected", &o_Data_selected, "o_Data_selected/I");
  outTreeData->Branch("isF3", &o_Data_isF3, "o_Data_isF3/I");
  outTreeData->Branch("run", &o_Data_run, "o_Data_run/I");
  outTreeData->Branch("lumi", &o_Data_lumi, "o_Data_lumi/I");
  outTreeData->Branch("event", &o_Data_event, "o_Data_event/I");
  outTreeData->Branch("weight", &o_Data_weight, "o_Data_weight/D");
  outTreeData->Branch("id_iso_eleW", &o_Data_id_iso_eleW, "o_Data_id_iso_eleW/I");
  outTreeData->Branch("id_iso_eleH", &o_Data_id_iso_eleH, "o_Data_id_iso_eleH/I");
  outTreeData->Branch("pt_eW", &o_Data_pt_eW, "o_Data_pt_eW/D");
  outTreeData->Branch("pt_eH", &o_Data_pt_eH, "o_Data_pt_eH/D");
  outTreeData->Branch("pt_tH", &o_Data_pt_tH, "o_Data_pt_tH/D");
  outTreeData->Branch("pt_jet_eW", &o_Data_pt_jet_eW, "o_Data_pt_jet_eW/D");
  outTreeData->Branch("pt_jet_eH", &o_Data_pt_jet_eH, "o_Data_pt_jet_eH/D");
  outTreeData->Branch("njets", &o_Data_njets, "o_Data_njets/I");
  outTreeData->Branch("maxPt_eW", &o_Data_maxPt_eW, "o_Data_maxPt_eW/D");
  outTreeData->Branch("maxPt_eH", &o_Data_maxPt_eH, "o_Data_maxPt_eH/D");
  outTreeData->Branch("mass", &o_Data_mass, "o_Data_mass/D");
  outTreeData->Branch("LT", &o_Data_LT, "o_Data_LT/D");
  outTreeData->Branch("count", &o_Data_count, "o_Data_count/I");
  
  for(long iEv=0; iEv < inputTree->GetEntries(); iEv++)
  {
	inputTree->GetEntry(iEv);
	if(!selected) continue;
	
	o_selected = selected;
	o_isF3 = isF3;
	o_run = run;
	o_lumi = lumi;
	o_event = event;
	o_weight = weight;
	o_id_iso_eleW = id_iso_eleW;
	o_id_iso_eleH = id_iso_eleH;
	o_pt_eW = pt_eW;
	o_pt_eH = pt_eH;
	o_pt_tH = pt_tH;
	o_pt_jet_eW = pt_jet_eW;
	o_pt_jet_eH = pt_jet_eH;
	o_njets = njets;
	o_maxPt_eW = maxPt_eW;
	o_maxPt_eH = maxPt_eH;
	o_mass = mass;
	o_LT = LT;
	o_count = count;
	
	o_BG_selected = selected;
	o_BG_isF3 = isF3;
	o_BG_run = run;
	o_BG_lumi = lumi;
	o_BG_event = event;
	o_BG_weight = weight;
	o_BG_id_iso_eleW = id_iso_eleW;
	o_BG_id_iso_eleH = id_iso_eleH;
	o_BG_pt_eW = pt_eW;
	o_BG_pt_eH = pt_eH;
	o_BG_pt_tH = pt_tH;
	o_BG_pt_jet_eW = pt_jet_eW;
	o_BG_pt_jet_eH = pt_jet_eH;
	o_BG_njets = njets;
	o_BG_maxPt_eW = maxPt_eW;
	o_BG_maxPt_eH = maxPt_eH;
	o_BG_mass = mass;
	o_BG_LT = LT;
	o_BG_count = count;
	
	o_Data_selected = selected;
	o_Data_isF3 = isF3;
	o_Data_run = run;
	o_Data_lumi = lumi;
	o_Data_event = event;
	o_Data_weight = weight;
	o_Data_id_iso_eleW = id_iso_eleW;
	o_Data_id_iso_eleH = id_iso_eleH;
	o_Data_pt_eW = pt_eW;
	o_Data_pt_eH = pt_eH;
	o_Data_pt_tH = pt_tH;
	o_Data_pt_jet_eW = pt_jet_eW;
	o_Data_pt_jet_eH = pt_jet_eH;
	o_Data_njets = njets;
	o_Data_maxPt_eW = maxPt_eW;
	o_Data_maxPt_eH = maxPt_eH;
	o_Data_mass = mass;
	o_Data_LT = LT;
	o_Data_count = count;
	
	if(id_iso_eleH) outTreeSig->Fill();
	else outTreeBG->Fill();
	
	outTreeData->Fill();
  }
  
  
  outTreeSig->Write();
  outTreeBG->Write();
  outTreeData->Write();
  
  outputFile->Close();
  
  
  
	return 0;
}
