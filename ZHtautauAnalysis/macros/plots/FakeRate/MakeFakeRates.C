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

//~ #include "../plotStyles/AtlasStyle.C"
//~ #include "../plotStyles/AtlasUtils.h"
//~ #include "../plotStyles/AtlasUtils.C"
//~ #include "../plotStyles/TriggerPerfPaperConsts.h"
//~ #include "../plotStyles/tdrstyle.C"

using namespace std;

TF1* TauFakeRate(TFile* f, TString outputDir, int type, bool log = true, double fitMin=10., double fitMax = 300.) {

  //~ gROOT->Reset();  
  //~ //SetAtlasStyle();
  //~ setTDRStyle();
  //~ gStyle->SetPalette(1);
   
  const uint rebinLeptonFR=5;	
  const uint rebinTauFR=5;	
	

  const uint nFiles = 1;
  TString fileNames[nFiles] = {
		"2012"
		};
   

  // TString outputDir = "/home/jpavel/analysis/CMS/Plots/FakeRate/Summer13_AfterSync";
  //~ gROOT->ProcessLine(".!mkdir -p "+outputDir+"/png");
  //~ gROOT->ProcessLine(".!mkdir -p "+outputDir+"/pdf");
  
  
  	
  
       
  //~ TFile * f[nFiles];  	
//~ 
  //~ 
  //~ std::stringstream indexes;
  //~ for(uint iFile = 0; iFile < nFiles; iFile++)
  //~ {
	//~ indexes.str("");
  	//~ indexes << inputFile;
  	//~ 
	//~ std::string input_file=indexes.str();
	//~ f[iFile] = TFile::Open(input_file.c_str());
	//~ if(!f[iFile]) {
		//~ std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
    //~ return 0;
	//~ }
	//~ else std::cout << "File " << input_file << " succesfully opened!" << std::endl;
  //~ 
  //~ }
  
  TString histName;
  TString histName2;
  TString suffix;
  
  switch(type)
  {
	case 0: //tau B
		histName=histName2="tau";
		suffix="";
		break;
	case 1: // tau EC
		histName=histName2="tau";
		suffix="_EC";
		break;
	case 2:
		histName="el";
		histName2="elT";
		suffix="";
		break;
	case 3:
		histName="mu";
		histName2="muT";
		suffix="";
		break;
  }
  
  std::stringstream denom, num;
  denom.str("");
  num.str("");
  denom << "h_FR_" << histName << "_denom" << suffix;
  num << "h_FR_" << histName2 << "_num" << suffix;
  std::string Denom_name=denom.str();
  std::string Num_name=num.str();
  
  
  TH1D * h_denom = (TH1D*)f->Get(TString(Denom_name));
  TH1D * h_num = (TH1D*)f->Get(TString(Num_name));
  
  // TH1D* h_d_EC,h_n_EC;
  
  if(type>1)
  {
	TH1D* h_d_EC = (TH1D*)f->Get(TString(Denom_name+"_EC"));
	TH1D* h_n_EC = (TH1D*)f->Get(TString(Num_name+"_EC"));
	h_denom->Add(h_d_EC);
	h_num->Add(h_n_EC);
  }
  
  h_denom->Rebin(rebinTauFR);
  h_num->Rebin(rebinTauFR);
	
  TH1D*  h_FR = (TH1D*)h_num->Clone(); 
  h_FR->Divide(h_denom);
  
  TCanvas* c1 = new TCanvas("c1","c1", 1024,1024);
  h_FR->Draw();
  
  TF1 *fit1 = new TF1("fit1","[0]+[1]*TMath::Exp([2]*x)",fitMin,fitMax);
  fit1->SetParameters(0.015,0.2,-0.07);
  h_FR->Fit("fit1","R");
  
  if(log) c1->SetLogy();
  
  h_FR->GetXaxis()->SetRangeUser(0.,150.);
  h_FR->GetYaxis()->SetTitle(histName+" fake rate "+suffix );
  
  c1->Print(outputDir+"/png/"+histName+suffix+"FR.png");
  c1->Print(outputDir+"/pdf/"+histName+suffix+"FR.pdf");
  
  c1->SetLogy(0);
  
  return fit1;
}
