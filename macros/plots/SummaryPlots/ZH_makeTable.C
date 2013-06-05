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

int MakeTable(TString inputFile = "/home/jpavel/ntuples/CMS/analysis/ZHtautau/Lucia/histo_42X_TruePU_v2/ZZjets_42X_TruePU.root")
{
	 gROOT->Reset();             
  //SetAtlasStyle();
  setTDRStyle();
  gStyle->SetPalette(1);
  
  TFile* f;
  
  f = TFile::Open(inputFile);
		if(!f) {
			std::cerr << "Error: file " << inputFile << " could not be opened." << std::endl; 
	    return 1;
		}
		else std::cout << "File " << inputFile << " succesfully opened!" << std::endl;		
		
	TH1D* h1d = (TH1D*)f->Get("h_nPU_reweight");
	Double_t entries = h1d->Integral();
	std::cout << "There are " << entries << " entries. " << std::endl;
	
	TH1D* h_event_type = (TH1D*)f->Get("h_event_type");
	
	std::cout << "\\begin{table}[h]" << std::endl;
	std::cout << "	\\begin{center}" << std::endl;
	std::cout << "		\\caption{ZZ event yield 2011}\\label{tab:ZZyield}" << std::endl;
	std::cout << "		\\begin{tabular}{lrcl} \\hline" << std::endl;
	std::cout << "		Event Type & Expected number of events &  & \\\\ \\hline" << std::endl;
	
	double total_lumi=2741.0+2219.0+22.0;
	double xsec = 0.130;
	//xsec = (0.69669*0.32570 + 0.3943*0.100990 + 0.1302*0.1060805) *0.216; //*0.0632; 
	//xsec = 0.130;
	double sim_lumi= entries/xsec;
	double weight = total_lumi/sim_lumi;
	
	double total = 0.0;
	for(uint i =1; i < 9; i++)
		total+=h_event_type->GetBinContent(i);
	
	std::cout << setiosflags(ios::fixed) << std::setprecision(2) << "$\\mu\\mu\\mu\\tau$ & " << h_event_type->GetBinContent(1)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(1)*(1-h_event_type->GetBinContent(1)/entries))*weight << " \\\\" << std::endl;
	std::cout << "$\\mu\\mu\\mu e$ & " << h_event_type->GetBinContent(2)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(2)*(1-h_event_type->GetBinContent(2)/entries))*weight << " \\\\" << std::endl;
	std::cout << "$\\mu\\mu e \\tau$ & " << h_event_type->GetBinContent(3)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(3)*(1-h_event_type->GetBinContent(1)/entries))*weight << " \\\\" << std::endl;
	std::cout << "$\\mu\\mu\\tau\\tau$ & " << h_event_type->GetBinContent(4)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(4)*(1-h_event_type->GetBinContent(4)/entries))*weight << " \\\\" << std::endl;
	std::cout << "$ee\\mu\\tau$ & " << h_event_type->GetBinContent(5)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(5)*(1-h_event_type->GetBinContent(5)/entries))*weight << " \\\\" << std::endl;
	std::cout << "$ee\\mu e$ & " << h_event_type->GetBinContent(6)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(6)*(1-h_event_type->GetBinContent(6)/entries))*weight << " \\\\" << std::endl;
	std::cout << "$eee\\tau$ & " << h_event_type->GetBinContent(7)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(7)*(1-h_event_type->GetBinContent(7)/entries))*weight << " \\\\" << std::endl;
	std::cout << "$ee\\tau\\tau$ & " << h_event_type->GetBinContent(8)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(8)*(1-h_event_type->GetBinContent(8)/entries))*weight << " \\\\" << std::endl;
	std::cout << "TOTAL & " << total*weight << " & $\\pm$ & " 
		<< sqrt(total*(1-total/entries))*weight << " \\\\" << std::endl;
	std::cout << "		\\end{tabular}" << std::endl;
	std::cout << "	\\end{center}" << std::endl;
	std::cout << "\\end{table}" << std::endl;


	ofstream tab1;
	tab1.open("ZZJets4lOldCuts_yield.tab");
	
	tab1 << "\\begin{table}[h]" << std::endl;
	tab1 << "	\\begin{center}" << std::endl;
	tab1 << "		\\caption{Htt(120) event yield 2011}\\label{tab:ZZyield}" << std::endl;
	tab1 << "		\\begin{tabular}{lrcl} \\hline" << std::endl;
	tab1 << "		Event Type & \\multicolumn{3}{c}{Expected number of events}\\\\ \\hline" << std::endl;
	
	tab1 << setiosflags(ios::fixed) << std::setprecision(2) << "$\\mu\\mu\\mu\\tau$ & " << h_event_type->GetBinContent(1)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(1)*(1-h_event_type->GetBinContent(1)/entries))*weight << " \\\\" << std::endl;
	tab1 << "$\\mu\\mu\\mu e$ & " << h_event_type->GetBinContent(2)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(2)*(1-h_event_type->GetBinContent(2)/entries))*weight << " \\\\" << std::endl;
	tab1 << "$\\mu\\mu e \\tau$ & " << h_event_type->GetBinContent(3)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(3)*(1-h_event_type->GetBinContent(1)/entries))*weight << " \\\\" << std::endl;
	tab1 << "$\\mu\\mu\\tau\\tau$ & " << h_event_type->GetBinContent(4)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(4)*(1-h_event_type->GetBinContent(4)/entries))*weight << " \\\\" << std::endl;
	tab1 << "$ee\\mu\\tau$ & " << h_event_type->GetBinContent(5)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(5)*(1-h_event_type->GetBinContent(5)/entries))*weight << " \\\\" << std::endl;
	tab1 << "$ee\\mu e$ & " << h_event_type->GetBinContent(6)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(6)*(1-h_event_type->GetBinContent(6)/entries))*weight << " \\\\" << std::endl;
	tab1 << "$eee\\tau$ & " << h_event_type->GetBinContent(7)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(7)*(1-h_event_type->GetBinContent(7)/entries))*weight << " \\\\" << std::endl;
	tab1 << "$ee\\tau\\tau$ & " << h_event_type->GetBinContent(8)*weight << " & $\\pm$ & " 
		<< sqrt(h_event_type->GetBinContent(8)*(1-h_event_type->GetBinContent(8)/entries))*weight << " \\\\" << std::endl;
		tab1 << "TOTAL & " << total*weight << " & $\\pm$ & " 
		<< sqrt(total*(1-total/entries))*weight << " \\\\" << std::endl;
	tab1 << "		\\end{tabular}" << std::endl;
	tab1 << "	\\end{center}" << std::endl;
	tab1 << "\\end{table}" << std::endl;
	
	tab1.close();
	

return 0;		
}


