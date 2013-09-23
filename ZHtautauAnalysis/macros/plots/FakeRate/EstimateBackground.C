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

#include "../plotStyles/AtlasStyle.C"
#include "../plotStyles/AtlasUtils.h"
#include "../plotStyles/AtlasUtils.C"
#include "../plotStyles/TriggerPerfPaperConsts.h"
#include "../plotStyles/tdrstyle.C"

#include "MakeFakeRates.C"

using namespace std;

std::vector<double>* EstimateBackground(TString inputFile = "/home/jpavel/analysis/CMS/histograms/PostMoriod/20130918/2012.root") {

  gROOT->Reset();  
  //SetAtlasStyle();
  setTDRStyle();
  gStyle->SetPalette(1);
   
  const uint rebinLeptonFR=5;	
  const uint rebinTauFR=5;	
	

  const uint nFiles = 1;
  TString fileNames[nFiles] = {
		"2012"
		};
   

  TString outputDir = "/home/jpavel/analysis/CMS/Plots/20130918";
  gROOT->ProcessLine(".!mkdir -p "+outputDir+"/png");
  gROOT->ProcessLine(".!mkdir -p "+outputDir+"/pdf");
  
  
  	
  
       
  TFile * f[nFiles];  	

  
  std::stringstream indexes;
  for(uint iFile = 0; iFile < nFiles; iFile++)
  {
	indexes.str("");
  	indexes << inputFile;
  	
	std::string input_file=indexes.str();
	f[iFile] = TFile::Open(input_file.c_str());
	if(!f[iFile]) {
		std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
    return NULL;
	}
	else std::cout << "File " << input_file << " succesfully opened!" << std::endl;
  
  }
  
  TFile* g = TFile::Open("/home/jpavel/analysis/CMS/histograms/PostMoriod/20130918/2012.root");
  
  TF1 *tauFit = TauFakeRate(g,outputDir,0);
  TF1 *tauFit_EC = TauFakeRate(g,outputDir,1);
  TF1 *tauFitLT = TauFakeRate(g,outputDir,2);
  TF1 *tauFitLT_EC = TauFakeRate(g,outputDir,3);
  
  //~ 
  TF1 *muFit = TauFakeRate(g,outputDir,5);
  TF1 *elFit = TauFakeRate(g,outputDir,4);
  TF1 *muFitT = TauFakeRate(g,outputDir,7);
  TF1 *elFitT = TauFakeRate(g,outputDir,6);
  //~ 
  
  
  const uint nHist2 = 8;
  TString histNames2[nHist2] = {"h_jet_BB_category0_jet_BB_pt_", "h_jet_EB_category0_jet_EB_pt_", "h_jet_BE_category0_jet_BE_pt_", "h_jet_EE_category0_jet_EE_pt_", 
	"h_jet_category1_jet_pt_", "h_jet_EC_category1_jet_EC_pt_", "h_jet_category2_jet_pt_",  "h_jet_EC_category2_jet_EC_pt_"
	};	
	
	
  const uint nTypes = 8; 	
  TH1D* h_hist2[nHist2-4][nTypes];
  TH2D* h_hist2D[4][nTypes];
 
 for(uint iHist=0; iHist < nHist2; iHist++)
	{
		for(uint iType=1; iType <=nTypes; iType++)
		{
		
		indexes.str("");
			indexes << histNames2[iHist] << iType;
			std::string input_file=indexes.str();
			if(iHist<4) h_hist2D[iHist][iType-1]= (TH2D*)f[0]->Get(TString(input_file));
			else h_hist2[iHist-4][iType-1]= (TH1D*)f[0]->Get(TString(input_file));
		}
	}
  
  h_hist2[0][0]->Draw();
  
   double estimate_cat0[nTypes];
   double estimate_cat1[nTypes];
   double estimate_cat2[nTypes];
   std::vector<double>* estimate_BG;
   estimate_BG = new std::vector<double>;
   estimate_BG->clear();
   double total_cat0[nTypes];
   double total_cat1[nTypes];
   double total_cat2[nTypes];
   
      
   double sum_estimate[3];
   double cat_estimate=0;
   
   
   std::cout << "start BB" << std::endl;
   // BB
   for(uint iType=0; iType < nTypes; iType++){
	   double bg_estimate=0;		
	   total_cat0[iType]=0;
	    estimate_cat0[iType]=0;
	   for(int iBin = 1; iBin <= h_hist2D[0][iType]->GetNbinsX()+1; iBin++)
	   {
		   for(int jBin=1; jBin <= h_hist2D[0][iType]->GetNbinsY()+1;jBin++)
		   {
			double pt1 = h_hist2D[0][iType]->GetXaxis()->GetBinCenter(iBin); // tau or electron
			double pt2 = h_hist2D[0][iType]->GetYaxis()->GetBinCenter(jBin);
			
			//std::cout << setiosflags(ios::fixed) << std::setprecision(2) << iBin << " " << jBin << " " << iType << ":" << pt1 << " " << pt2 << std::endl;
			double fr1,fr2;
			switch(iType%4)
			{
				case 0: // MUTAU
					fr1=tauFitLT->Eval(pt1);
					fr2=muFitT->Eval(pt2);
					break;
				case 1: //EM
					fr1=elFit->Eval(pt1);
					fr2=muFit->Eval(pt2);
					break;
				case 2:
					fr1=tauFitLT->Eval(pt1);
					fr2=elFitT->Eval(pt2);
					break;
				case 3:
					fr1 = tauFit->Eval(pt1);
					fr2 = tauFit->Eval(pt2);
					break;
			}
			//std::cout << fr1 << " " << fr2 << " " << h_hist2D[0][iType]->GetBinContent(iBin,jBin) << std::endl;
			double estim = (fr1*fr2*h_hist2D[0][iType]->GetBinContent(iBin,jBin))/((1-fr1)*(1-fr2));
			bg_estimate+=estim;
		   }
	   }
	   estimate_cat0[iType]+=bg_estimate;
	   std::cout << " Type: " << iType << " total = " << total_cat0[iType] << " and I am adding " << h_hist2D[0][iType]->GetEntries() << std::endl;
	   total_cat0[iType]+=h_hist2D[0][iType]->GetEntries();
	   cat_estimate+=bg_estimate;
	   std::cout << setiosflags(ios::fixed) << std::setprecision(2) << bg_estimate << std::endl;
	}
	std::cout << "start EB" << std::endl;
	//EB
	for(uint iType=0; iType < nTypes; iType++){
	   double bg_estimate=0;		
	   for(int iBin = 1; iBin <= h_hist2D[1][iType]->GetNbinsX()+1; iBin++)
	   {
		   for(int jBin=1; jBin <= h_hist2D[1][iType]->GetNbinsY()+1;jBin++)
		   {
			double pt1 = h_hist2D[1][iType]->GetXaxis()->GetBinCenter(iBin); //endcap
			double pt2 = h_hist2D[1][iType]->GetYaxis()->GetBinCenter(jBin); //barrel
			
			//std::cout << setiosflags(ios::fixed) << std::setprecision(2) << iBin << " " << jBin << " " << iType << ":" << pt1 << " " << pt2 << std::endl;
			double fr1,fr2;
			switch(iType%4)
			{
				case 0:
					fr1=tauFitLT_EC->Eval(pt1);
					fr2=muFitT->Eval(pt2);
					break;
				case 1:
					fr1=elFit->Eval(pt1);
					fr2=muFit->Eval(pt2);
					break;
				case 2:
					fr1=tauFitLT_EC->Eval(pt1);
					fr2=elFitT->Eval(pt2);
					break;
				case 3:
					fr1 = tauFit_EC->Eval(pt1);
					fr2 = tauFit->Eval(pt2);
					break;
			}
			//std::cout << fr1 << " " << fr2 << " " << h_hist2D[0][0][iType]->GetBinContent(iBin,jBin) << std::endl;
			double estim = (fr1*fr2*h_hist2D[1][iType]->GetBinContent(iBin,jBin))/((1-fr1)*(1-fr2));
			bg_estimate+=estim;
		   }
	   }
	   estimate_cat0[iType]+=bg_estimate;
	   std::cout << " Type: " << iType << " total = " << total_cat0[iType] << " and I am adding " << h_hist2D[1][iType]->GetEntries() << std::endl;
	   total_cat0[iType]+=h_hist2D[1][iType]->GetEntries();
	   cat_estimate+=bg_estimate;
	   std::cout << setiosflags(ios::fixed) << std::setprecision(2) << bg_estimate << std::endl;
	}
	std::cout << "start BE" << std::endl;
	//BE
	for(uint iType=0; iType < nTypes; iType++){
	   double bg_estimate=0;		
	   for(int iBin = 1; iBin <= h_hist2D[2][iType]->GetNbinsX()+1; iBin++)
	   {
		   for(int jBin=1; jBin <= h_hist2D[2][iType]->GetNbinsY()+1;jBin++)
		   {
			double pt1 = h_hist2D[2][iType]->GetXaxis()->GetBinCenter(iBin); //barrel
			double pt2 = h_hist2D[2][iType]->GetYaxis()->GetBinCenter(jBin); //endcap
			
			//std::cout << setiosflags(ios::fixed) << std::setprecision(2) << iBin << " " << jBin << " " << iType << ":" << pt1 << " " << pt2 << std::endl;
			double fr1,fr2;
			switch(iType%4)
			{
				case 0:
					fr1=tauFitLT->Eval(pt1);
					fr2=muFitT->Eval(pt2);
					break;
				case 1:
					fr1=elFit->Eval(pt1);
					fr2=muFit->Eval(pt2);
					break;
				case 2:
					fr1=tauFitLT->Eval(pt1);
					fr2=elFitT->Eval(pt2);
					break;
				case 3:
					fr1 = tauFit->Eval(pt1);
					fr2 = tauFit_EC->Eval(pt2);
					break;
			}
			//std::cout << fr1 << " " << fr2 << " " << h_hist2D[0][0][iType]->GetBinContent(iBin,jBin) << std::endl;
			double estim = (fr1*fr2*h_hist2D[2][iType]->GetBinContent(iBin,jBin))/((1-fr1)*(1-fr2));
			bg_estimate+=estim;
		   }
	   }
	   estimate_cat0[iType]+=bg_estimate;
	   total_cat0[iType]+=h_hist2D[2][iType]->GetEntries();
	   cat_estimate+=bg_estimate;
	   std::cout << setiosflags(ios::fixed) << std::setprecision(2) << bg_estimate << std::endl;
	}
	std::cout << "start EE" << std::endl;
	//EE
	for(uint iType=0; iType < nTypes; iType++){
	   double bg_estimate=0;		
	   for(int iBin = 1; iBin <= h_hist2D[3][iType]->GetNbinsX()+1; iBin++)
	   {
		   for(int jBin=1; jBin <= h_hist2D[3][iType]->GetNbinsY()+1;jBin++)
		   {
			double pt1 = h_hist2D[3][iType]->GetXaxis()->GetBinCenter(iBin); //endcap
			double pt2 = h_hist2D[3][iType]->GetYaxis()->GetBinCenter(jBin); //endcap
			
			//std::cout << setiosflags(ios::fixed) << std::setprecision(2) << iBin << " " << jBin << " " << iType << ":" << pt1 << " " << pt2 << std::endl;
			double fr1,fr2;
			switch(iType%4)
			{
				case 0:
					fr1=tauFitLT_EC->Eval(pt1);
					fr2=muFitT->Eval(pt2);
					break;
				case 1:
					fr1=elFit->Eval(pt1);
					fr2=muFit->Eval(pt2);
					break;
				case 2:
					fr1=tauFitLT_EC->Eval(pt1);
					fr2=elFitT->Eval(pt2);
					break;
				case 3:
					fr1 = tauFit_EC->Eval(pt1);
					fr2 = tauFit_EC->Eval(pt2);
					break;
			}
			//std::cout << fr1 << " " << fr2 << " " << h_hist2D[0][0][iType]->GetBinContent(iBin,jBin) << std::endl;
			double estim = (fr1*fr2*h_hist2D[3][iType]->GetBinContent(iBin,jBin))/((1-fr1)*(1-fr2));
			bg_estimate+=estim;
		   }
	   }
	   estimate_cat0[iType]+=bg_estimate;
	   total_cat0[iType]+=h_hist2D[3][iType]->GetEntries();  
	   cat_estimate+=bg_estimate;
	   std::cout << setiosflags(ios::fixed) << std::setprecision(2) << bg_estimate << std::endl;
	}
  	
	   
   sum_estimate[0]=cat_estimate;
   cat_estimate=0;
   
   // Cat 1 barrel
   for(uint iType=0; iType < nTypes; iType++){
	   double bg_estimate=0;	
	    total_cat1[iType]=0;
	    estimate_cat1[iType]=0;	
	   for(int iBin = 1; iBin <= h_hist2[0][iType]->GetNbinsX()+1; iBin++)
	   {
		   double pt1 = h_hist2[0][iType]->GetXaxis()->GetBinCenter(iBin);
		   double fr1;
		   switch(iType%4)
			{
				case 0:
					fr1=tauFitLT->Eval(pt1);
					break;
				case 1:
					fr1=elFit->Eval(pt1);
					break;
				case 2:
					fr1=tauFitLT->Eval(pt1);
					break;
				case 3:
					fr1 = tauFit->Eval(pt1);
					break;
			}
			double estim = (fr1*h_hist2[0][iType]->GetBinContent(iBin))/((1-fr1));
			bg_estimate+=estim;
		   
	   }
	   estimate_cat1[iType]+=bg_estimate;
	   total_cat1[iType]+=h_hist2[0][iType]->GetEntries();
	  
	   cat_estimate+=bg_estimate;
	   std::cout << setiosflags(ios::fixed) << std::setprecision(2) << bg_estimate << std::endl;
   }
   
   // cat1 EC
   for(uint iType=0; iType < nTypes; iType++){
	   double bg_estimate=0;		
	   for(int iBin = 1; iBin <= h_hist2[1][iType]->GetNbinsX()+1; iBin++)
	   {
		   double pt1 = h_hist2[1][iType]->GetXaxis()->GetBinCenter(iBin);
		   double fr1;
		   switch(iType%4)
			{
				case 0:
					fr1=tauFitLT_EC->Eval(pt1);
					break;
				case 1:
					fr1=elFit->Eval(pt1);
					break;
				case 2:
					fr1=tauFitLT_EC->Eval(pt1);
					break;
				case 3:
					fr1 = tauFit_EC->Eval(pt1);
					break;
			}
			double estim = (fr1*h_hist2[1][iType]->GetBinContent(iBin))/((1-fr1));
			bg_estimate+=estim;
		   
	   }
	   estimate_cat1[iType]+=bg_estimate;
	   total_cat1[iType]+=h_hist2[1][iType]->GetEntries();
	  
	   cat_estimate+=bg_estimate;
	   std::cout << setiosflags(ios::fixed) << std::setprecision(2) << bg_estimate << std::endl;
   }
   
   sum_estimate[1]=cat_estimate;
   cat_estimate=0;
   
   // cat 2 barrel
   for(uint iType=0; iType < nTypes; iType++){
	    total_cat2[iType]=0;
	    estimate_cat2[iType]=0;
	   double bg_estimate=0;		
	   for(int iBin = 1; iBin <= h_hist2[2][iType]->GetNbinsX()+1; iBin++)
	   {
		   double pt1 = h_hist2[2][iType]->GetXaxis()->GetBinCenter(iBin);
		   double fr1;
		   switch(iType%4)
			{
				case 0:
					fr1=muFitT->Eval(pt1);
					break;
				case 1:
					fr1=muFit->Eval(pt1);
					break;
				case 2:
					fr1=elFitT->Eval(pt1);
					break;
				case 3:
					fr1 = tauFit->Eval(pt1);
					break;
			}
			double estim = (fr1*h_hist2[2][iType]->GetBinContent(iBin))/((1-fr1));
			bg_estimate+=estim;
		   
	   }
	   estimate_cat2[iType]+=bg_estimate;
	   total_cat2[iType]+=h_hist2[2][iType]->GetEntries();	
	   cat_estimate+=bg_estimate;
	   std::cout << setiosflags(ios::fixed) << std::setprecision(2) << bg_estimate << std::endl;
   }
   
   // cat 2 EC
   for(uint iType=0; iType < nTypes; iType++){
	   double bg_estimate=0;		
	   for(int iBin = 1; iBin <= h_hist2[3][iType]->GetNbinsX()+1; iBin++)
	   {
		   double pt1 = h_hist2[3][iType]->GetXaxis()->GetBinCenter(iBin);
		   double fr1;
		   switch(iType%4)
			{
				case 0:
					fr1=muFitT->Eval(pt1);
					break;
				case 1:
					fr1=muFit->Eval(pt1);
					break;
				case 2:
					fr1=elFitT->Eval(pt1);
					break;
				case 3:
					fr1 = tauFit_EC->Eval(pt1);
					break;
			}
			double estim = (fr1*h_hist2[3][iType]->GetBinContent(iBin))/((1-fr1));
			bg_estimate+=estim;
		   
	   }
	   estimate_cat2[iType]+=bg_estimate;
	   total_cat2[iType]+=h_hist2[3][iType]->GetEntries();	
	   cat_estimate+=bg_estimate;
	   std::cout << setiosflags(ios::fixed) << std::setprecision(2) << bg_estimate << std::endl;
   }
   
   
   sum_estimate[2]=cat_estimate;
   
   
   TString BinLabels[8] = { "$\\mu\\mu\\mu\\tau$", "$\\mu\\mu\\mu e$", "$\\mu\\mu e \\tau$", "$\\mu\\mu\\tau\\tau$",
							  "$ee\\mu\\tau$", "$ee\\mu e$", "$ee e \\tau$", "$ee\\tau\\tau$"};
	
	std::cout << "\\begin{table}[h]" << std::endl;
	std::cout << "	\\begin{center}" << std::endl;
	std::cout << "		\\caption{Signal and background yields}\\label{tab:yieldData}" << std::endl;
	std::cout << "		\\begin{tabular}{l|rrrr} \\hline" << std::endl;
	std::cout << setiosflags(ios::fixed) << std::setprecision(2) << " Event Type & category 0 & category 1 & category 2 & 1+2-0 \\\\ \\hline" << std::endl;
	for(uint i = 1; i < 9; i++){
		std::cout << BinLabels[i-1];
			//for(uint iHist=0; iHist< nHist2; iHist++){
				std::cout <<  " & " << setiosflags(ios::fixed) << std::setprecision(2)  << estimate_cat0[i-1] << setiosflags(ios::fixed) 
				<< std::setprecision(0)  << " (" << total_cat0[i-1] << ")" ;
				std::cout << " & " << setiosflags(ios::fixed) << std::setprecision(2)  << estimate_cat1[i-1] << setiosflags(ios::fixed) 
				<< std::setprecision(0)  << " (" << total_cat1[i-1] << ")" ;
				std::cout << " & " << setiosflags(ios::fixed) << std::setprecision(2)  << estimate_cat2[i-1] << setiosflags(ios::fixed) 
				<< std::setprecision(0)  << " (" << total_cat2[i-1] << ")" ;
			//}
			std::cout <<  " & " << setiosflags(ios::fixed) << std::setprecision(2)  << estimate_cat1[i-1]+estimate_cat2[i-1]-estimate_cat0[i-1] ;
		std::cout << " \\\\" << std::endl;
		estimate_BG->push_back(estimate_cat1[i-1]+estimate_cat2[i-1]-estimate_cat0[i-1]);
	}
	std::cout << "\\hline" << std::endl;
	std::cout << " Sum: & " << sum_estimate[0] << setiosflags(ios::fixed) << std::setprecision(2)  << " & " << sum_estimate[1] << " & " << sum_estimate[2] << "\\\\" << std::endl;
	std::cout << "		\\end{tabular}" << std::endl;
	std::cout << "	\\end{center}" << std::endl;
	std::cout << "\\end{table}" << std::endl; 
  
   
 //std::cout << h_hist[0][0]->GetSumOfWeights() << std::endl;

  //~ TH1D * h_denom = (TH1D*)f[0]->Get("h_FR_tau_denom");
  //~ TH1D * h_num = (TH1D*)f[0]->Get("h_FR_tau_num");
  //~ 
  //~ h_denom->Rebin(rebinTauFR);
  //~ h_num->Rebin(rebinTauFR);
	//~ 
  //~ TH1D*  h_FR = (TH1D*)h_num->Clone(); 
  //~ h_FR->Divide(h_denom);
  //~ 
  //~ TCanvas* c1 = new TCanvas("c1","c1", 1024,1024);
  //~ h_FR->Draw();
  //~ 
  //~ TF1 *fit1 = new TF1("fit1","[0]+[1]*TMath::Exp([2]*x)",fitMin,fitMax);
  //~ fit1->SetParameters(0.015,0.2,-0.07);
  //~ h_FR->Fit("fit1","R");
  //~ 
  //~ h_FR->GetXaxis()->SetRangeUser(0.,100.);
  //~ h_FR->GetYaxis()->SetTitle("tau fake rate");
  //~ 
  //~ c1->Print(outputDir+"/png/tauFR.png");
  //~ c1->Print(outputDir+"/pdf/tauFR.pdf");
  //~ 
  //~ 
  return estimate_BG;
}
