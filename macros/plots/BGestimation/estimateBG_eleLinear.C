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

using namespace std;

int estimateBG(TString inputDir = "/home/jpavel/analysis/CMS/histograms/PostMoriod/Application2/") {

  gROOT->Reset();             
  //SetAtlasStyle();
  setTDRStyle();
  gStyle->SetPalette(1);
   
  //~ const uint rebinLeptonFR=10;	
  //~ const uint rebinTauFR=5;	
	//~ 

  const uint nFiles = 1;
  TString fileNames[nFiles] = {
		"2012"
		};
   
  //~ int colors[nFiles] = { kRed};
  //~ int markers[nFiles] = { 24};
   

  TString outputDir = "/home/jpavel/analysis/CMS/Plots/BGestimate2";
	
  
       
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
  
  //~ std::vector<std::vector<TH1D*> >  h_denom_types;
  //~ std::vector<std::vector<TH1D*> >  h_loose_types;
  //~ std::vector<std::vector<TH1D*> >  h_medium_types;
  //~ std::vector<std::vector<TH1D*> >  h_tight_types;
  //~ 
  const uint nHist = 4;
  TString histNames[nHist] = {"h_H_mass_signal_type_", 
	"h_H_mass_cat0_type_", "h_H_mass_cat1_type_", "h_H_mass_cat2_type_"
	};
  const uint nHist2 = 3;
  TString histNames2[nHist2] = {"h_category0_pt_", 
	"h_category1_pt_", "h_category2_pt_"
	};	
	
  const uint nTypes = 8; 	
  TH1D* h_hist[nFiles][nHist][nTypes];
  TH1D* h_hist2[nFiles][nHist2-1][nTypes];
  TH2D* h_hist2D[nFiles][1][nTypes];
  
  
  for(uint iFile=0; iFile < nFiles; iFile++)
  {
	for(uint iHist=0; iHist < nHist; iHist++)
	{
		for(uint iType=1; iType <=nTypes; iType++)
		{
			indexes.str("");
			indexes << histNames[iHist] << iType;
			std::string input_file=indexes.str();
			h_hist[iFile][iHist][iType-1]= (TH1D*)f[iFile]->Get(TString(input_file));
		}
		
	}
	for(uint iHist=0; iHist < nHist2; iHist++)
	{
		for(uint iType=1; iType <=nTypes; iType++)
		{
		
		indexes.str("");
			indexes << histNames2[iHist] << iType;
			std::string input_file=indexes.str();
			if(iHist==0) h_hist2D[iFile][iHist][iType-1]= (TH2D*)f[iFile]->Get(TString(input_file));
			else h_hist2[iFile][iHist-1][iType-1]= (TH1D*)f[iFile]->Get(TString(input_file));
		}
	}
	  
  } 
  
  h_hist2[0][0][0]->Draw();
 std::cout << h_hist[0][0][0]->GetSumOfWeights() << std::endl;
   
   const double FR_ele_loose=0.0278039;
   const double FR_ele_tight=0.0111485;
   TF1 *ele_FR_loose = new TF1("eleFit","pol1");
   TF1 *ele_FR_medium = new TF1("eleFitM","pol1");
   ele_FR_loose->SetParameters(0.0100542,0.000860186);
   ele_FR_medium->SetParameters(0.00444696,0.000354056);
   
   const double FR_mu_loose=0.0379521;
   const double FR_mu_tight=0.035781;
   TF1 *FR_medium = new TF1("fit1","[0]+[1]*TMath::Exp([2]*x)",10.,90.);
   FR_medium->SetParameters(1.09956e-02,2.21698e-01,-8.16290e-02);
   //~ TF1 *FR_tight = new TF1("fit1","[0]+[1]*TMath::Exp([2]*x)",15.,80.);
   //~ FR_tight->SetParameters(0.0077,0.1174,-0.0784);
   
   double estimate_cat0[nTypes];
   double estimate_cat1[nTypes];
   double estimate_cat2[nTypes];
      
   double sum_estimate[3];
   double cat_estimate=0;
   for(uint iType=0; iType < nTypes; iType++){
	   double bg_estimate=0;		
	   for(int iBin = 1; iBin <= h_hist2D[0][0][iType]->GetNbinsX()+1; iBin++)
	   {
		   for(int jBin=1; jBin <= h_hist2D[0][0][iType]->GetNbinsY()+1;jBin++)
		   {
			double pt1 = h_hist2D[0][0][iType]->GetXaxis()->GetBinCenter(iBin);
			double pt2 = h_hist2D[0][0][iType]->GetYaxis()->GetBinCenter(jBin);
			
			//std::cout << setiosflags(ios::fixed) << std::setprecision(2) << iBin << " " << jBin << " " << iType << ":" << pt1 << " " << pt2 << std::endl;
			double fr1,fr2;
			switch(iType%4)
			{
				case 0:
					fr1=FR_medium->Eval(pt1);
					fr2=FR_mu_tight;
					break;
				case 1:
					fr1=ele_FR_loose->Eval(pt1);
					fr2=FR_mu_loose;
					break;
				case 2:
					fr1=FR_medium->Eval(pt1);
					fr2=ele_FR_medium->Eval(pt2);
					break;
				case 3:
					fr1 = FR_medium->Eval(pt1);
					fr2 = FR_medium->Eval(pt2);
					break;
			}
			//std::cout << fr1 << " " << fr2 << " " << h_hist2D[0][0][iType]->GetBinContent(iBin,jBin) << std::endl;
			double estim = (fr1*fr2*h_hist2D[0][0][iType]->GetBinContent(iBin,jBin))/((1-fr1)*(1-fr2));
			bg_estimate+=estim;
		   }
	   }
	   estimate_cat0[iType]=bg_estimate;
	   cat_estimate+=bg_estimate;
	   std::cout << setiosflags(ios::fixed) << std::setprecision(2) << bg_estimate << std::endl;
	}   
   sum_estimate[0]=cat_estimate;
   cat_estimate=0;
   
    for(uint iType=0; iType < nTypes; iType++){
	   double bg_estimate=0;		
	   for(int iBin = 1; iBin <= h_hist2[0][0][iType]->GetNbinsX()+1; iBin++)
	   {
		   double pt1 = h_hist2[0][0][iType]->GetXaxis()->GetBinCenter(iBin);
		   double fr1;
		   switch(iType%4)
			{
				case 0:
					fr1=FR_medium->Eval(pt1);
					break;
				case 1:
					fr1=ele_FR_loose->Eval(pt1);
					break;
				case 2:
					fr1=FR_medium->Eval(pt1);
					break;
				case 3:
					fr1 = FR_medium->Eval(pt1);
					break;
			}
			double estim = (fr1*h_hist2[0][0][iType]->GetBinContent(iBin))/((1-fr1));
			bg_estimate+=estim;
		   
	   }
	   estimate_cat1[iType]=bg_estimate;
	   cat_estimate+=bg_estimate;
	   std::cout << setiosflags(ios::fixed) << std::setprecision(2) << bg_estimate << std::endl;
   }
   
    sum_estimate[1]=cat_estimate;
   cat_estimate=0;
   
   //estimate_cat0[0]=
   
   for(uint iType=0; iType < nTypes; iType++){
	   double bg_estimate=0;		
	   for(int iBin = 1; iBin <= h_hist2[0][1][iType]->GetNbinsX()+1; iBin++)
	   {
		   double pt1 = h_hist2[0][1][iType]->GetXaxis()->GetBinCenter(iBin);
		   double fr1;
		   switch(iType%4)
			{
				case 0:
					fr1=FR_mu_tight;
					break;
				case 1:
					fr1=FR_mu_loose;
					break;
				case 2:
					fr1=ele_FR_medium->Eval(pt1);
					break;
				case 3:
					fr1 = FR_medium->Eval(pt1);
					break;
			}
			double estim = (fr1*h_hist2[0][1][iType]->GetBinContent(iBin))/((1-fr1));
			bg_estimate+=estim;
		   
	   }
	   estimate_cat2[iType]=bg_estimate;
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
	std::cout << setiosflags(ios::fixed) << std::setprecision(2) << " Event Type & signal & category 0 & category 1 & category 2 \\\\ \\hline" << std::endl;
	for(uint i = 1; i < 9; i++){
		std::cout << BinLabels[i-1];
		for(uint j =0; j < nFiles; j++){
			for(uint iHist=0; iHist< nHist; iHist++){
				std::cout << setiosflags(ios::fixed) << std::setprecision(0) <<  " & " << h_hist[j][iHist][i-1]->GetSumOfWeights() ;
			}
		}
		std::cout << " \\\\" << std::endl;
	}
	std::cout << "		\\end{tabular}" << std::endl;
	std::cout << "	\\end{center}" << std::endl;
	std::cout << "\\end{table}" << std::endl; 
	
	
	std::cout << "\\begin{table}[h]" << std::endl;
	std::cout << "	\\begin{center}" << std::endl;
	std::cout << "		\\caption{Signal and background yields}\\label{tab:yieldData}" << std::endl;
	std::cout << "		\\begin{tabular}{l|rrrr} \\hline" << std::endl;
	std::cout << setiosflags(ios::fixed) << std::setprecision(2) << " Event Type & category 0 & category 1 & category 2 & 1+2-0 \\\\ \\hline" << std::endl;
	for(uint i = 1; i < 9; i++){
		std::cout << BinLabels[i-1];
		for(uint j =0; j < nFiles; j++){
			for(uint iHist=0; iHist< nHist2; iHist++){
				if (iHist==0) std::cout <<  " & " << setiosflags(ios::fixed) << std::setprecision(2)  << estimate_cat0[i-1] << setiosflags(ios::fixed) << std::setprecision(0)  << " (" << h_hist2D[j][iHist][i-1]->GetEntries() << ")" ;
				else if(iHist==1) std::cout << " & " << setiosflags(ios::fixed) << std::setprecision(2)  << estimate_cat1[i-1] << setiosflags(ios::fixed) << std::setprecision(0)  << " (" << h_hist2[j][iHist-1][i-1]->GetEntries() << ")" ;
				else std::cout << " & " << setiosflags(ios::fixed) << std::setprecision(2)  << estimate_cat2[i-1] << setiosflags(ios::fixed) << std::setprecision(0)  << " (" << h_hist2[j][iHist-1][i-1]->GetEntries() << ")" ;
			}
			std::cout <<  " & " << setiosflags(ios::fixed) << std::setprecision(2)  << estimate_cat1[i-1]+estimate_cat2[i-1]-estimate_cat0[i-1] ;
		}
		std::cout << " \\\\" << std::endl;
	}
	std::cout << "\\hline" << std::endl;
	std::cout << " Sum: & " << sum_estimate[0] << setiosflags(ios::fixed) << std::setprecision(2)  << " & " << sum_estimate[1] << " & " << sum_estimate[2] << "\\\\" << std::endl;
	std::cout << "		\\end{tabular}" << std::endl;
	std::cout << "	\\end{center}" << std::endl;
	std::cout << "\\end{table}" << std::endl; 
  
  ofstream tab1;
	tab1.open(outputDir+"/bgestimate_eleLinear.tab");
	
	tab1 << "\\begin{table}[h]" << std::endl;
	tab1 << "	\\begin{center}" << std::endl;
	tab1 << "		\\caption{Signal and background yields}\\label{tab:yieldData}" << std::endl;
	tab1 << "		\\begin{tabular}{l|rrrr} \\hline" << std::endl;
	tab1 << setiosflags(ios::fixed) << std::setprecision(2) << " Event Type & category 0 & category 1 & category 2 & 1+2-0 \\\\ \\hline" << std::endl;
	for(uint i = 1; i < 9; i++){
		tab1 << BinLabels[i-1];
		for(uint j =0; j < nFiles; j++){
			for(uint iHist=0; iHist< nHist2; iHist++){
				if (iHist==0) tab1 <<  " & " << setiosflags(ios::fixed) << std::setprecision(2)  << estimate_cat0[i-1] << setiosflags(ios::fixed) << std::setprecision(0)  << " (" << h_hist2D[j][iHist][i-1]->GetEntries() << ")" ;
				else if(iHist==1) tab1 << " & " << setiosflags(ios::fixed) << std::setprecision(2)  << estimate_cat1[i-1] << setiosflags(ios::fixed) << std::setprecision(0)  << " (" << h_hist2[j][iHist-1][i-1]->GetEntries() << ")" ;
				else tab1 << " & " << setiosflags(ios::fixed) << std::setprecision(2)  << estimate_cat2[i-1] << setiosflags(ios::fixed) << std::setprecision(0)  << " (" << h_hist2[j][iHist-1][i-1]->GetEntries() << ")" ;
			}
			tab1 <<  " & " << setiosflags(ios::fixed) << std::setprecision(2)  << estimate_cat1[i-1]+estimate_cat2[i-1]-estimate_cat0[i-1] ;
		}
		tab1 << " \\\\" << std::endl;
	}
	tab1 << "\\hline" << std::endl;
	tab1 << " Sum: & " << sum_estimate[0] << setiosflags(ios::fixed) << std::setprecision(2)  << " & " << sum_estimate[1] << " & " << sum_estimate[2] << " & " << sum_estimate[1] + sum_estimate[2] - sum_estimate[0] << "\\\\" << std::endl;
	tab1 << "		\\end{tabular}" << std::endl;
	tab1 << "	\\end{center}" << std::endl;
	tab1 << "\\end{table}" << std::endl;
	tab1.close();

  
 	
  return 0;
}
