//=============================================================
// run this example by doing "root plotExample.C++"
// - input is a root file with histograms
// - output is an 'example.eps' figure
// - this macro should not change the content of the histograms!
//=============================================================

#include "TH1F.h"
#include "TH2F.h"
#include "TGraphAsymmErrors.h"
#include "TFile.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TProfile.h"
#include "THStack.h"
#include "TH2D.h"
#include "TF1.h"

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "./plotStyles/AtlasStyle.C"
#include "./plotStyles/AtlasUtils.h"
#include "./plotStyles/AtlasUtils.C"
#include "./plotStyles/TriggerPerfPaperConsts.h"
#include "tdrstyle.C"

using namespace std;

int FRplots(TString inputDir = "../config/") {

  gROOT->Reset();             
  //SetAtlasStyle();
  setTDRStyle();
  gStyle->SetPalette(1);
   
  const uint rebinLeptonFR=10;	
  const uint rebinTauFR=5;	
	

  const uint nFiles = 1;
  TString fileNames[nFiles] = {
		"Analysis"
		};
   

  TString outputDir = "figs";
	
  
       
  TFile * f[nFiles];  	

  
  std::stringstream indexes;
  for(uint iFile = 0; iFile < nFiles; iFile++)
  {
	indexes.str("");
  	indexes << inputDir << fileNames[iFile];
  	
	std::string input_file=indexes.str()+".root";
	f[iFile] = TFile::Open(input_file.c_str());
	if(!f[iFile]) {
		std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
    return 1;
	}
	else std::cout << "File " << input_file << " succesfully opened!" << std::endl;
  
  }
  
  std::vector<std::vector<TH1D*> >  h_denom_types;
  std::vector<std::vector<TH1D*> >  h_loose_types;
  std::vector<std::vector<TH1D*> >  h_medium_types;
  std::vector<std::vector<TH1D*> >  h_tight_types;
  
  TH1D* h_event_type[nFiles];
  for(uint iFile=0; iFile < nFiles; iFile++)
  {
	  h_event_type[iFile]= (TH1D*)f[iFile]->Get("h_event_type");
  } 
  
  h_event_type[0]->Draw();
  
  h_denom_types.clear();
   
   for(uint iFile=0; iFile < nFiles; iFile++)
	{     
        std::vector<TH1D*> h_denom_types_temp;
        h_denom_types_temp.clear();
        for(uint i = 1; i <= (uint)h_event_type[iFile]->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_denom_type_" << i;
                std::string name = s.str();
                TH1D* h_temp =  (TH1D*)f[iFile]->Get(TString(name));
                h_denom_types_temp.push_back(h_temp);
        }
        h_denom_types.push_back(h_denom_types_temp);
        
        std::vector<TH1D*> h_loose_types_temp;
        h_loose_types_temp.clear();
        for(uint i = 1; i <= (uint)h_event_type[iFile]->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_loose_type_" << i;
                std::string name = s.str();
                TH1D* h_temp =  (TH1D*)f[iFile]->Get(TString(name));
                h_loose_types_temp.push_back(h_temp);
        }
        h_loose_types.push_back(h_loose_types_temp);
        
        std::vector<TH1D*> h_medium_types_temp;
        h_medium_types_temp.clear();
        for(uint i = 1; i <= (uint)h_event_type[iFile]->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_medium_type_" << i;
                std::string name = s.str();
                TH1D* h_temp =  (TH1D*)f[iFile]->Get(TString(name));
                h_medium_types_temp.push_back(h_temp);
        }
        h_medium_types.push_back(h_medium_types_temp);
        
        std::vector<TH1D*> h_tight_types_temp;
        h_tight_types_temp.clear();
        for(uint i = 1; i <= (uint)h_event_type[iFile]->GetNbinsX(); i++)
        {
                std::stringstream s;
                s << "h_tight_type_" << i;
                std::string name = s.str();
                TH1D* h_temp =  (TH1D*)f[iFile]->Get(TString(name));
                h_tight_types_temp.push_back(h_temp);
        }
        h_tight_types.push_back(h_tight_types_temp);
        
	}
  h_denom_types[0][0]->Draw();
  
  // mutau FR
  TCanvas* c1 = new TCanvas("c1","c1", 1024,1024);
  for(uint iFile=0; iFile < nFiles; iFile++)
	{
		//adding Zmumu and Zee togethger
		h_denom_types[iFile][0]->Add(h_denom_types[iFile][4]);
		h_loose_types[iFile][0]->Add(h_loose_types[iFile][4]);
		h_tight_types[iFile][0]->Add(h_tight_types[iFile][4]); 
		TH1D* h_loose_FR = (TH1D*)h_loose_types[iFile][0]->Clone(); 
		h_loose_FR->Divide(h_denom_types[iFile][0]);
		TH1D* h_tight_FR = (TH1D*)h_tight_types[iFile][0]->Clone(); 
		h_tight_FR->Divide(h_denom_types[iFile][0]);
		
		h_loose_FR->Rebin(rebinLeptonFR);
		h_loose_FR->Scale(1./rebinLeptonFR);
		h_tight_FR->Rebin(rebinLeptonFR);
		h_tight_FR->Scale(1./rebinLeptonFR);
		
		h_loose_FR->GetXaxis()->SetTitle("P_{T}[GeV]");
		h_loose_FR->GetYaxis()->SetTitle("loose fake rate");
		h_tight_FR->GetXaxis()->SetTitle("P_{T}[GeV]");
		h_tight_FR->GetYaxis()->SetTitle("tight fake rate");
		
		h_loose_FR->Draw();
		c1->Print(outputDir+"/png/looseMuonFR.png");
		c1->Print(outputDir+"/eps/looseMuonFR.eps");
		c1->Print(outputDir+"/pdf/looseMuonFR.pdf");
		
		h_tight_FR->Draw();
		c1->Print(outputDir+"/png/tightMuonFR.png");
		c1->Print(outputDir+"/eps/tightMuonFR.eps");
		c1->Print(outputDir+"/pdf/tightMuonFR.pdf");
	}
	
	// etau FR
  for(uint iFile=0; iFile < nFiles; iFile++)
	{
		//adding Zmumu and Zee togethger
		h_denom_types[iFile][2]->Add(h_denom_types[iFile][6]);
		h_loose_types[iFile][2]->Add(h_loose_types[iFile][6]);
		h_tight_types[iFile][2]->Add(h_tight_types[iFile][6]); 
		TH1D* h_loose_FR = (TH1D*)h_loose_types[iFile][2]->Clone(); 
		h_loose_FR->Divide(h_denom_types[iFile][2]);
		TH1D* h_tight_FR = (TH1D*)h_tight_types[iFile][2]->Clone(); 
		h_tight_FR->Divide(h_denom_types[iFile][2]);
		
		h_loose_FR->Rebin(rebinLeptonFR);
		h_loose_FR->Scale(1./rebinLeptonFR);
		h_tight_FR->Rebin(rebinLeptonFR);
		h_tight_FR->Scale(1./rebinLeptonFR);
		
		h_loose_FR->GetXaxis()->SetTitle("P_{T}[GeV]");
		h_loose_FR->GetYaxis()->SetTitle("loose fake rate");
		h_tight_FR->GetXaxis()->SetTitle("P_{T}[GeV]");
		h_tight_FR->GetYaxis()->SetTitle("tight fake rate");
		
		h_loose_FR->Draw();
		c1->Print(outputDir+"/png/looseElectronFR.png");
		c1->Print(outputDir+"/eps/looseElectronFR.eps");
		c1->Print(outputDir+"/pdf/looseElectronFR.pdf");
		
		h_tight_FR->Draw();
		c1->Print(outputDir+"/png/tightElectronFR.png");
		c1->Print(outputDir+"/eps/tightElectronFR.eps");
		c1->Print(outputDir+"/pdf/tightElectronFR.pdf");
	}
	
		// tautau FR
  for(uint iFile=0; iFile < nFiles; iFile++)
	{
		//adding Zmumu and Zee togethger
		h_denom_types[iFile][3]->Add(h_denom_types[iFile][7]);
		h_loose_types[iFile][3]->Add(h_loose_types[iFile][7]);
		h_medium_types[iFile][3]->Add(h_medium_types[iFile][7]);
		h_tight_types[iFile][3]->Add(h_tight_types[iFile][7]); 
		TH1D* h_loose_FR = (TH1D*)h_loose_types[iFile][3]->Clone(); 
		h_loose_FR->Divide(h_denom_types[iFile][3]);
		TH1D* h_medium_FR = (TH1D*)h_medium_types[iFile][3]->Clone(); 
		h_medium_FR->Divide(h_denom_types[iFile][3]);
		TH1D* h_tight_FR = (TH1D*)h_tight_types[iFile][3]->Clone(); 
		h_tight_FR->Divide(h_denom_types[iFile][3]);
		
		h_loose_FR->Rebin(rebinTauFR);
		h_loose_FR->Scale(1./rebinTauFR);
		h_medium_FR->Rebin(rebinTauFR);
		h_medium_FR->Scale(1./rebinTauFR);
		h_tight_FR->Rebin(rebinTauFR);
		h_tight_FR->Scale(1./rebinTauFR);
		
		h_loose_FR->GetXaxis()->SetTitle("P_{T}[GeV]");
		h_loose_FR->GetYaxis()->SetTitle("loose fake rate");
		h_medium_FR->GetXaxis()->SetTitle("P_{T}[GeV]");
		h_medium_FR->GetYaxis()->SetTitle("medium fake rate");
		h_tight_FR->GetXaxis()->SetTitle("P_{T}[GeV]");
		h_tight_FR->GetYaxis()->SetTitle("tight fake rate");
		
		h_loose_FR->Draw();
		TF1 *fit1 = new TF1("fit1","[0]+[1]*TMath::Exp([2]*x)",15.,80.);
		fit1->SetParameters(0.015,0.2,-0.07);
		h_loose_FR->Fit("fit1","R");
		
		c1->Print(outputDir+"/png/looseTauFR.png");
		c1->Print(outputDir+"/eps/looseTauFR.eps");
		c1->Print(outputDir+"/pdf/looseTauFR.pdf");
		
		h_medium_FR->Draw();
		h_medium_FR->Fit("fit1","R");
		
		c1->Print(outputDir+"/png/mediumTauFR.png");
		c1->Print(outputDir+"/eps/mediumTauFR.eps");
		c1->Print(outputDir+"/pdf/mediumTauFR.pdf");
		
		h_tight_FR->Draw();
		h_tight_FR->Fit("fit1","R");
		
		c1->Print(outputDir+"/png/tightTauFR.png");
		c1->Print(outputDir+"/eps/tightTauFR.eps");
		c1->Print(outputDir+"/pdf/tightTauFR.pdf");
	}
  
 	
  return 0;
}
