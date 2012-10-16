#include "TH1F.h"
#include "TH2F.h"
#include "TGraphAsymmErrors.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TProfile.h"
#include "TPaveText.h"
#include "THStack.h"
#include "TCanvas.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;


int stack_upgrade_42X() {

	//gROOT->ProcessLine(".L ./tdrstyle.C");
	//setTDRStyle();
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetStatColor(0);
  gStyle->SetOptStat(0000000);
  gStyle->SetOptFit(0111);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetPalette(1);


  const int nFiles = 7;

  //Int_t r = 4;
  //DoubleEle + WZ
  //TString fileNames[nFiles] = {"DoubleEle","TT_42X_TruePU","WZ_42X_TruePU","ZZ_42X_TruePU","DY_42X_TruePU","Htt120_42X_TruePU","Hww120_42X_TruePU"};
  //DoubleEle + WZjets 
  TString fileNames[nFiles] = {"DoubleMu","ZZ_42X_TruePU","WZjets_42X_TruePU","TT_42X_TruePU","DY_42X_TruePU","Htt120_42X_TruePU_1","Hww120_42X_TruePU_1"};
  //DoubleMu + WZ 
  //TString fileNames[nFiles] = {"DoubleMu","TT_42X_TruePU","WZ_42X_TruePU","ZZ_42X_TruePU","DY_42X_TruePU","Htt120_42X_TruePU","Hww120_42X_TruePU"};
  //DoubleMu + WZjets 
  //TString fileNames[nFiles] = {"DoubleMu","TT_42X_TruePU","WZjets_42X_TruePU","ZZ_42X_TruePU","DY_42X_TruePU","Htt120_42X_TruePU","Hww120_42X_TruePU"};

  //DoubleEle + WZ
  //Double_t weights[nFiles] = {1.00, 0.01054, 0.0392, 0.00047967, 0.44927,0.0009171,0.000136};
  //DoubleEle + WZjets 
 // Double_t weights[nFiles] = {1.00, 0.0004796752, 0.003921881, 0.010544, 0.449278,0.00091718,0.000136};
  //DoubleMu + WZ 
  //Double_t weights[nFiles] = {1.00, 0.01054, 0.0392, 0.00047967, 0.44927,0.0009171,0.000136};
  //DoubleMu + WZjets 
  //Double_t weights[nFiles] = {1.00, 0.01054, 0.003525, 0.00047967, 0.44927,0.0009171,0.000136};
  
  TFile * f[nFiles];  	
  std::stringstream indexes;  

  for(int iFile = 0; iFile < nFiles; iFile++)

  {
	  indexes.str("");
	  indexes << fileNames[iFile];
	  std::string input_file="histo_42X_TruePU_v2/"+indexes.str()+".root";

	  f[iFile] = TFile::Open(input_file.c_str());

	  if(!f[iFile]) {
		  std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
		  return 1;
	  }
	  else std::cout << "File " << input_file << " succesfully opened!" << std::endl;
  }



  const int nHist1 = 5;
  //const int nHist1 = 44;


  TString histNames1[nHist1] = {"h_Zmass_mumu","h_H_mass_type_1","h_H_mass_type_2","h_H_mass_type_3","h_H_mass_type_4"};
  TString histTitles[nHist1] = {"M_{2#mu}[GeV]","M_{#mu#tau}[GeV]","M_{#mue}[GeV]","M_{e#tau}[GeV]","M_{#tau#tau}[GeV]"};
  TString PaveText[nHist1]	= {"Z#mu#mu","MMMT","MMME","MMET","MMTT"};
  
  //TString histNames1[nHist1] = {"h_mu1Z_pt", "h_mu2Z_pt", "h_Z_lep1_eta", "h_Z_lep2_eta", "h_Z_lep1_phi", "h_Z_lep2_phi", "h_Zmass_mumu", "h_Zmass_ee","h_Zpt_mumu", "h_Zpt_ee","h_Zmass", "h_Zpt","h_H_mass", "h_H_pt","h_H_eta", "h_H_phi", "h_H_mass_type_1", "h_H_mass_type_2", "h_H_mass_type_3", "h_H_mass_type_4", "h_H_mass_type_5", "h_H_mass_type_6", "h_H_mass_type_7", "h_H_mass_type_8", "h_Tmass","h_H_lep1_eta","h_H_lep2_eta","h_H_lep1_phi","h_H_lep2_phi","h_nbjets","h_nbjets_afterVeto","h_nbjetsVetoed","h_nPU_Info","h_nPU_InfoTrue","h_nPU_Bunch0","h_nPU_Info_W","h_nPU_InfoTrue_W","h_nPU_Bunch0_W","h_Nvertex_NoCut","h_Nvertex_NoCut_W","h_Nvertex_AfterZ","h_Nvertex_AfterZ_W","h_Nvertex_AfterZH","h_Nvertex_AfterZH_W"};

  TH1F * 		h_1d[nHist1][nFiles];
  TH1F *                signal[nHist1];
  
   Double_t weights[nFiles];
  Double_t xsection[nFiles]={1.0, 0.106, 0.868, 17.32, 3048, 0.0184915, 0.0039508088};
  
  
  
  const double total_lumi = 4960.0; // pb-1
  
  for(int iFile = 0; iFile < nFiles; iFile++)
	{
		TH1D * h_pu = (TH1D*)f[iFile]->Get("h_nPU_raw");		
		std::cout << h_pu->Integral() << std::endl;
		double lumi = h_pu->Integral()/xsection[iFile];
		if(iFile > 0) weights[iFile]=total_lumi/lumi;
		else weights[iFile] = 1.0;
		std::cout << weights[iFile] << std::endl;
	}

  for(int iFile = 0; iFile < nFiles; iFile++)
  {
	  for(int iHist = 0; iHist < nHist1; iHist++)
	  {
		  h_1d[iHist][iFile] = (TH1F*)f[iFile]->Get(histNames1[iHist]);
		  h_1d[iHist][iFile]->Scale(weights[iFile]); 
		  if(iHist > 0) h_1d[iHist][iFile]->Rebin(10);
	  }
  }

  TCanvas *c1 = new TCanvas("c1","",5,30,650,600);
  //gPad->SetLogy(); 
  c1->SetGrid(0,0);
  c1->SetFillStyle(4000);
  c1->SetFillColor(10);
  c1->SetTicky();
  c1->SetObjectStat(0);

  for(int iHist = 0; iHist < nHist1; iHist++){
	  signal[iHist] = (TH1F*)h_1d[iHist][5]->Clone();}

  for(int iHist = 0; iHist < nHist1; iHist++)

  {
	  THStack *hs = new THStack("hs","Stacked MC histograms");


	  for(int iFile=1; iFile < nFiles-1; iFile++)

	  {

		  h_1d[iHist][iFile]->SetLineWidth(0);
		  h_1d[iHist][iFile]->SetFillStyle(3244);

		  if(iFile == 1){ h_1d[iHist][iFile]->SetFillColor(kMagenta-8);  }
		  else if(iFile == 2){  h_1d[iHist][iFile]->SetFillColor(kRed); }
		  else if(iFile == 3){  h_1d[iHist][iFile]->SetFillColor(kGreen); }
		  else if(iFile == 4){  h_1d[iHist][iFile]->SetFillColor(kAzure+6); }
		  else if(iFile == 5){
			  signal[iHist]->Add(h_1d[iHist][iFile+1]);
                          signal[iHist]->SetLineColor(kRed); 
                          signal[iHist]->SetLineWidth(2.0); 
                          
                   }

		  if(iFile < 5) hs->Add(h_1d[iHist][iFile],"hist");		

	  }

		  //hs->Add(signal[iHist],"hist");		
	  
	  h_1d[iHist][0]->SetMarkerStyle(21);
	  h_1d[iHist][0]->SetMarkerSize(0.7);

 TLegend* leg = new TLegend(0.65,0.70,0.88,0.88,NULL,"brNDC");
 leg->SetFillColor(0);
 leg->SetTextSize(0.035);
 leg->SetBorderSize(0);
			
	  leg->AddEntry(h_1d[iHist][0],"data 2011","p");
	  leg->AddEntry(h_1d[iHist][1],"ZZ","f");
	  leg->AddEntry(h_1d[iHist][2],"WZ","f");
	  leg->AddEntry(h_1d[iHist][3],"t#bar{t}","f");
	  leg->AddEntry(h_1d[iHist][4],"Zjet","f");
	  leg->AddEntry(signal[iHist],"ZH(120)#times 5","f");

TString lumist="4.9 fb^{-1}";
  TPaveText *ll = new TPaveText(0.25, 0.95, 0.95, 0.99, "NDC");
  ll->SetTextSize(0.03);
  ll->SetTextFont(62);
  ll->SetFillColor(0);
  ll->SetBorderSize(0);
  ll->SetMargin(0.01);
  ll->SetTextAlign(12); // align left
  TString text = PaveText[iHist];
  ll->AddText(0.01,0.5,text);
  text = "#sqrt{s} = 7 TeV  L = ";
  text = text + lumist;
  //  ll->SetTextAlign(32); // align right
  ll->AddText(0.5, 0.5, text);
   
	  /*double max_dy = h_1d[iHist][4]->GetMaximum();
	  double max_data = h_1d[iHist][0]->GetMaximum();
	  double max = 0;

	  if (max_dy > max_data){
		  max = max_dy;}
	  else {
		  max = max_data;}
	  if (max != 0) hs->SetMaximum(max);

          cout << "max data: " << max_data << endl;
          cout << "max dy: " << max_dy << endl;
	  */

	  h_1d[iHist][0]->Draw("PE01");
	  double max = h_1d[iHist][0]->GetMaximum();
	  h_1d[iHist][0]->GetYaxis()->SetRangeUser(1e-2,200*max);
	 if(iHist > 0 && iHist < 4)  h_1d[iHist][0]->GetXaxis()->SetRangeUser(0,150);
	 
	  h_1d[iHist][0]->GetXaxis()->SetTitle(histTitles[iHist]);
	  hs->Draw("same");
	  signal[iHist]->Scale(10.);
	  signal[iHist]->Draw("histsame");
      h_1d[iHist][0]->Draw("samePE01");
      
	  
	  leg->Draw("same");
	  ll->Draw("same");
	  gPad->RedrawAxis();

	  c1->SetLogy();	
	  c1->Print(histNames1[iHist]+"_all.png");
	  c1->Print(histNames1[iHist]+"_all.eps");
	  c1->SetLogy(0);
	  h_1d[iHist][0]->GetYaxis()->SetRangeUser(0,1.2*max);
	
	  c1->Print(histNames1[iHist]+"_all_normal.png");
	  c1->Print(histNames1[iHist]+"_all_normal.eps");
	  	
	  

	  leg->Clear();
	  hs->Clear();    

  }

  return 0;

}
