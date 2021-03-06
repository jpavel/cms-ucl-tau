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


int MakeTable(bool useData = true)
{
	 gROOT->Reset();             
  //SetAtlasStyle();
  setTDRStyle();
  gStyle->SetPalette(1);
  TString inputDir="/home/jpavel/ntuples/CMS/analysis/ZHtautau/validation/";
  
  const int nFiles = useData ? 7 : 6;
  TFile * f[nFiles];  	
  
  
  vector<TString> fileNames;
  fileNames.clear();
  
  
  fileNames.push_back("53x/MC/NoPtSum_DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball");
  								fileNames.push_back("53x/MC/NoPtSum_WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola");
								fileNames.push_back("53x/MC/NoPtSum_TTZJets_8TeV-madgraph_v2");
								fileNames.push_back("53x/MC/NoPtSum_ZZTo4L_TuneZ2star_8TeV_pythia6_tauola");
								fileNames.push_back("53x/MC/NoPtSum_Htt120");
								fileNames.push_back("53x/MC/NoPtSum_Hww120");
  if(useData) 					fileNames.push_back("53x/Data/NoPtSum");
  vector<TString> names;
  names.clear();
  
  names.push_back("DYJets");
  names.push_back("WZJets");
  names.push_back("TTZ");  
  names.push_back("ZZ4L");
  names.push_back("Htt(120)");
  names.push_back("Hww(120)");
  if(useData) names.push_back("Data 2012");

  
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
	vector<double> xsec;
	xsec.clear();
	xsec.push_back(3503.7);
	xsec.push_back(1.057);
	//xsec.push_back(23.64);
	xsec.push_back(0.208);
	xsec.push_back(0.130);
	xsec.push_back(productionXS*BRtau);
	xsec.push_back(productionXS*BRw);
	if(useData) xsec.push_back(1.0);	 
	double total_lumi=12000;
	
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
			h_cut_flow_weight[iFile] = (TH1D*)f[iFile]->Get("h_cut_flow_weight");
			h_cut_flow_signal_weight[iFile] = (TH1D*)f[iFile]->Get("h_cut_flow_signal_weight");
			
			weight[iFile] = total_lumi*xsec[iFile]/entries[iFile];
			if(useData && iFile==nFiles-1) weight[iFile]=1.0;
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
	tab1.open("/home/jpavel/Documents/UCL/HiggsTauTau/ZH/cutflow/cutFlow_NoSumPt.tab");
		tab1 << "\\begin{sidewaystable}[h]" << std::endl;
	tab1 << "	\\begin{center}" << std::endl;
	tab1 << "		\\caption{event yield 2012 (no LT cut) (12 fb$^{-1}$)}\\label{tab:CutFlow_NoSumPt}" << std::endl;
	tab1 << "		\\begin{tabular}{l"; 
	for(uint i = 0; i < nFiles; i++) tab1 << "|r";
	tab1 << "} \\hline" << std::endl;
	tab1 << setiosflags(ios::fixed) << std::setprecision(1) << "		Cut ";
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


