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
  TString inputDir="/home/jpavel/ntuples/CMS/analysis/ZHtautau/validation/";
  
  const int nFiles = 6;
  TFile * f[nFiles];  	
  
  
  TString fileNames[nFiles] = {"42x/MC/2011Standard_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola",
								"42x/MC/2011Standard_WZJetsTo3LNu_TuneZ2_7TeV-madgraph-tauola",
								"42x/MC/2011Standard_TTTo2L2Nu2B_7TeV-powheg-pythia6",
								"42x/MC/2011Standard_ZZTo4L_TuneZ2_7TeV_pythia6_tauola",
								"42x/MC/2011Standard_WH_ZH_TTH_HToTauTau_M-120_lepdecay_7TeV-pythia6-tauola_v2",
								"42x/MC/2011Standard_WH_ZH_TTH_HToWW_M-120_lepdecay_7TeV-pythia6_v2"
  };
  TString names[nFiles] = {"DYJets","WZJets","TT","ZZ4L","Htt(120)","Hww(120)"};
  
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
	const double productionXS= 0.7966*0.3257 + 0.4483*0.10099 + 0.147*0.1060805; // WH+ZH+ttH
	const double BRtau = 7.04e-2;
	const double BRw = 1.41e-1*0.3257*0.3257;
	double xsec[nFiles] = {3048,0.868,17.32,0.106, 0.0185, 0.0039};
	double total_lumi=4900;
	
     double weight[nFiles];
	
	TH1D* h1d[nFiles];
	Double_t entries[nFiles];
	TH1D* h_cut_flow_weight[nFiles];
	TH1D* h_cut_flow_signal_weight[nFiles];

	for(int iFile = 0; iFile < nFiles; iFile++)
	{
			h1d[iFile] = (TH1D*)f[iFile]->Get("h_nPU_reweight");
			entries[iFile] = h1d[iFile]->GetSumOfWeights();
			std::cout << "There are " << entries[iFile] << " entries. " << std::endl;
			h_cut_flow_weight[iFile] = (TH1D*)f[iFile]->Get("h_cut_flow");
			h_cut_flow_signal_weight[iFile] = (TH1D*)f[iFile]->Get("h_cut_flow_signal");
			
			weight[iFile] = total_lumi*xsec[iFile]/entries[iFile];
	} 
	
	
 
   TString BinLabels[4] = { "Start", "Trigger", "good vx", "Z selected"};
   TString BinLabels2[4] = { "H selected", "Overlap cleaning", "Same vx", "B-tag veto"};
		
	
	std::cout << "\\begin{table}[h]" << std::endl;
	std::cout << "	\\begin{center}" << std::endl;
	std::cout << "		\\caption{event yield 2012 (12 fb$^{-1}$)}\\label{tab:CutFlow}" << std::endl;
	std::cout << "		\\begin{tabular}{l"; 
	for(uint i = 0; i < nFiles; i++) std::cout << "|r";
	std::cout << "} \\hline" << std::endl;
	std::cout << setiosflags(ios::fixed) << std::setprecision(2) << "		Cut ";
	for(uint i = 0; i < nFiles; i++) std::cout << "& " << names[i] << " ";  
	std::cout << " \\\\ \\hline" << std::endl;
	for(uint i = 1; i < 5; i++){
		std::cout << BinLabels[i-1];
		for(uint j =0; j < nFiles; j++){
			std::cout <<  " & " << h_cut_flow_weight[j]->GetBinContent(i)*weight[j] << "  $\\pm$ " 
			<< sqrt(h_cut_flow_weight[j]->GetBinContent(i)*(1-h_cut_flow_weight[j]->GetBinContent(i)/entries[j]))*weight[j];
		}
		std::cout << " \\\\" << std::endl;
	}
	for(uint i = 1; i < 5; i++){
		std::cout << BinLabels2[i-1];
		for(uint j =0; j < nFiles; j++){
			std::cout <<  " & " << h_cut_flow_signal_weight[j]->GetBinContent(i)*weight[j] << "  $\\pm$ " 
			<< sqrt(h_cut_flow_signal_weight[j]->GetBinContent(i)*(1-h_cut_flow_signal_weight[j]->GetBinContent(i)/entries[j]))*weight[j];
		}
		std::cout << " \\\\" << std::endl;
	}
	std::cout << "		\\end{tabular}" << std::endl;
	std::cout << "	\\end{center}" << std::endl;
	std::cout << "\\end{table}" << std::endl;
	

	ofstream tab1;
	tab1.open("/home/jpavel/Documents/UCL/HiggsTauTau/ZH/cutflow/2011_cutFlow_NoSF.tab");
		tab1 << "\\begin{sidewaystable}[h]" << std::endl;
	tab1 << "	\\begin{center}" << std::endl;
	tab1 << "		\\caption{event yield 2011 (no SF) (4.9 fb$^{-1}$)}\\label{tab:2011_CutFlow_NoSF}" << std::endl;
	tab1 << "		\\begin{tabular}{l"; 
	for(uint i = 0; i < nFiles; i++) tab1 << "|r";
	tab1 << "} \\hline" << std::endl;
	tab1 << setiosflags(ios::fixed) << std::setprecision(2) << "		Cut ";
	for(uint i = 0; i < nFiles; i++) tab1 << "& " << names[i] << " ";  
	tab1 << " \\\\ \\hline" << std::endl;
	for(uint i = 1; i < 5; i++){
		tab1 << BinLabels[i-1];
		for(uint j =0; j < nFiles; j++){
			tab1 <<  " & " << h_cut_flow_weight[j]->GetBinContent(i)*weight[j] << "  $\\pm$ " 
			<< sqrt(h_cut_flow_weight[j]->GetBinContent(i)*(1-h_cut_flow_weight[j]->GetBinContent(i)/entries[j]))*weight[j];
		}
		tab1 << " \\\\" << std::endl;
	}
	for(uint i = 1; i < 5; i++){
		tab1 << BinLabels2[i-1];
		for(uint j =0; j < nFiles; j++){
			tab1 <<  " & " << h_cut_flow_signal_weight[j]->GetBinContent(i)*weight[j] << "  $\\pm$ " 
			<< sqrt(h_cut_flow_signal_weight[j]->GetBinContent(i)*(1-h_cut_flow_signal_weight[j]->GetBinContent(i)/entries[j]))*weight[j];
		}
		tab1 << " \\\\" << std::endl;
	}
	tab1 << "		\\end{tabular}" << std::endl;
	tab1 << "	\\end{center}" << std::endl;
	tab1 << "\\end{sidewaystable}" << std::endl;
	
	tab1.close();
	
	
return 0;		
}


