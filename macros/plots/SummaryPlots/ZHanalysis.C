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
#include "TLine.h"
#include "TGraph.h"

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

int A1analysis(TString inputDir = "/home/jpavel/ntuples/CMS/analysis/ZHtautau/") {

  gROOT->Reset();             
  //SetAtlasStyle();
  setTDRStyle();
  gStyle->SetPalette(1);

const int nFiles = 5;
  TString fileNames[nFiles] = {"run_0/output_ntuples/42X/Data/Electron_2011A","output_ntuples/42X/MC/DY","output_ntuples/42X/MC/TT","output_ntuples/42X/MC/WZ3lnu",
								"output_ntuples/42X/MC/ZZ4l"};



	TString outputDir = "ZHanalysis";

  
     
  TFile * f[nFiles];  	

  // keep the figures in this directory
  std::string figure_dir = "./";
  
  std::stringstream indexes;  
  for(int iFile = 0; iFile < nFiles; iFile++)
  {
	indexes.str("");
  	indexes << inputDir << fileNames[iFile] << "_histo.root";
	std::string input_file=indexes.str();
	f[iFile] = TFile::Open(input_file.c_str());
	if(!f[iFile]) {
		std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
    return 1;
	}
	else std::cout << "File " << input_file << " succesfully opened!" << std::endl;
  
  }
  
  const int nHist1 = 1;
  TString histNames1[nHist1] = { "h_Zmass_ee"};
  TH1D * 		h_1d[nHist1][nFiles];     
  
  Double_t weights[nFiles];
  Double_t xsection[nFiles]={1.0, 3048, 17.32, 0.868,0.106};
  
  
  
  const double total_lumi = 2219.0; // pb-1
  
  for(int iFile = 0; iFile < nFiles; iFile++)
	{
		TH1D * h_pu = (TH1D*)f[iFile]->Get("h_nPU_raw");		
		std::cout << h_pu->Integral() << std::endl;
		double lumi = h_pu->Integral()/xsection[iFile];
		if(iFile > 0) weights[iFile]=total_lumi/lumi;
		else weights[iFile] = 1.0;
		std::cout << weights[iFile] << std::endl;
		for(int iHist = 0; iHist < nHist1; iHist++)
		{
			h_1d[iHist][iFile] = (TH1D*)f[iFile]->Get(histNames1[iHist]);
			h_1d[iHist][iFile]->Scale(weights[iFile]);
		}
	}
	
	 TCanvas* c1 = new TCanvas("c1","c1", 800,600);
     
    
  // this file should contain *ONLY* the histogram (or other ROOT objects) needed to make your plots!  
  
  
  for(int iHist = 0; iHist < nHist1; iHist++)
  {
	h_1d[iHist][0]->Sumw2();
	h_1d[iHist][0]->Rebin(2);
	h_1d[iHist][1]->Rebin(2);
	
	
	h_1d[iHist][0]->SetMarkerStyle(21);
	h_1d[iHist][0]->SetMarkerSize(0.7);
	
	//~ if(iHist!=2) h_1d[iHist][0]->GetXaxis()->SetRangeUser(0,50);
	//~ h_1d[iHist][0]->GetYaxis()->SetTitle("Events/0.4 GeV");
	//~ if(iHist > 0)h_1d[iHist][0]->GetYaxis()->SetTitle("Events");
	//~ if(iHist==2) h_1d[iHist][0]->GetYaxis()->SetTitle("Events/0.08");
	
	
	h_1d[iHist][0]->Draw();
	h_1d[iHist][1]->Draw("histsame");
	
  }
  
  return 0;
}
