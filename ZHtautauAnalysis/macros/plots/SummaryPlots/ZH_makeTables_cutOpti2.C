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

int MakeTable(TString inputFile = "Htt125")
{
	 gROOT->Reset();             
  //SetAtlasStyle();
  setTDRStyle();
  gStyle->SetPalette(1);
  TString inputDir="/home/jpavel/ntuples/CMS/analysis/ZHtautau/CutOpti2/CutOpti2/CutOpti2_";
  
  const int nFiles = 3;
  TFile * f[nFiles];  	

  std::stringstream indexes;  
  for(int iFile = 0; iFile < nFiles; iFile++)
  {
	indexes.str("");
  	indexes << inputDir << iFile +1 << "_histo.root";
	std::string input_file=indexes.str();
	f[iFile] = TFile::Open(input_file.c_str());
	if(!f[iFile]) {
		std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
    return 1;
	}
	else std::cout << "File " << input_file << " succesfully opened!" << std::endl;
  
  }
	
	
	if(inputFile=="Hww120") inputFile="Hww125";
	double total_lumi=12000;
	double xsec;
	if(inputFile=="Htt125") xsec = (0.69669*0.32570 + 0.3943*0.100990 + 0.1302*0.1060805) *0.0632;
	if(inputFile=="ZZJets4L" || inputFile=="ZZ4L") xsec = 0.130;
	if(inputFile=="Hww125") xsec = (0.69669*0.32570 + 0.3943*0.100990 + 0.1302*0.1060805)*0.216;
	double weight[nFiles];
	 
	
		
		
	TH1D* h1d[nFiles];
	Double_t entries[nFiles];
	TH1D* h_event_type[nFiles];
	
	for(int iFile = 0; iFile < nFiles; iFile++)
	{
			h1d[iFile] = (TH1D*)f[iFile]->Get("h_nPU_reweight");
			entries[iFile] = h1d[iFile]->GetSumOfWeights();
			std::cout << "There are " << entries[iFile] << " entries. " << std::endl;
			h_event_type[iFile] = (TH1D*)f[iFile]->Get("h_event_type");
			weight[iFile] = total_lumi*xsec/entries[iFile];
	} 
	
	
	 TString BinLabels[8] = { "$\\mu\\mu\\mu\\tau$", "$\\mu\\mu\\mu e$", "$\\mu\\mu e \\tau$", "$\\mu\\mu\\tau\\tau$",
							  "$ee\\mu\\tau$", "$ee\\mu e$", "$ee e \\tau$", "$ee\\tau\\tau$"};
	
	std::cout << "\\begin{table}[h]" << std::endl;
	std::cout << "	\\begin{center}" << std::endl;
	std::cout << "		\\caption{"<< inputFile << " event yield 2012 (12 fb$^{-1}$)}\\label{tab:"<< inputFile <<"}" << std::endl;
	std::cout << "		\\begin{tabular}{l|r|r|r} \\hline" << std::endl;
	std::cout << setiosflags(ios::fixed) << std::setprecision(2) << "		Event Type & type 0 & type 1 & type 2  \\\\ \\hline" << std::endl;
	for(uint i = 1; i < 9; i++){
		std::cout << BinLabels[i-1];
		for(uint j =0; j < nFiles; j++){
			std::cout <<  " & " << h_event_type[j]->GetBinContent(i)*weight[j] << "  $\\pm$ " 
			<< sqrt(h_event_type[j]->GetBinContent(i)*(1-h_event_type[j]->GetBinContent(i)/entries[j]))*weight[j];
		}
		std::cout << " \\\\" << std::endl;
	}
	std::cout << "		\\end{tabular}" << std::endl;
	std::cout << "	\\end{center}" << std::endl;
	std::cout << "\\end{table}" << std::endl;
	

	ofstream tab1;
	tab1.open(inputFile+".2.tab");
	
	tab1 << "\\begin{table}[h]" << std::endl;
	tab1 << "	\\begin{center}" << std::endl;
	tab1 << "		\\caption{"<< inputFile << " event yield 2012 (12 fb$^{-1}$)}\\label{tab:"<< inputFile <<"}" << std::endl;
	tab1 << "		\\begin{tabular}{l|r|r|r} \\hline" << std::endl;
	tab1 << setiosflags(ios::fixed) << std::setprecision(2) << "		Event Type & type 0 & type 1 & type 2  \\\\ \\hline" << std::endl;
	for(uint i = 1; i < 9; i++){
		tab1 << BinLabels[i-1];
		for(uint j =0; j < nFiles; j++){
			tab1 <<  " & " << h_event_type[j]->GetBinContent(i)*weight[j] << "  $\\pm$ " 
			<< sqrt(h_event_type[j]->GetBinContent(i)*(1-h_event_type[j]->GetBinContent(i)/entries[j]))*weight[j];
		}
		tab1 << " \\\\" << std::endl;
	}
	tab1 << "		\\end{tabular}" << std::endl;
	tab1 << "	\\end{center}" << std::endl;
	tab1 << "\\end{table}" << std::endl;
	
	tab1.close();
	
	
return 0;		
}


