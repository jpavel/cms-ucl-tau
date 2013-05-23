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

int Compare(TString inputDir = "/home/jpavel/analysis/CMS/ZHtautau/histograms/PostMoriod/synctest/") {

  gROOT->Reset();             
  //SetAtlasStyle();
  setTDRStyle();
  gStyle->SetPalette(1);
   
  const uint rebinLeptonFR=10;	
  const uint rebinTauFR=5;	
	

  const uint nFiles = 2;
  TString fileNames[nFiles] = {
		"ZZ4l_old", "ZZ4l_new"
		};
   
  int colors[nFiles] = { kRed, kBlue};
  int markers[nFiles] = { 24, 25};
   

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
  const uint nHist = 10;
  TString histNames[nHist] = { 
	  "h_event_type" , "h_PU_weight", "h_total_weight", "h_Zmass_ee", "h_Zmass_mumu", "h_cut_flow", "h_Nvertex_AfterZ", "h_n_goodMu_Hcand", "h_n_goodEl_Hcand",
	  "h_n_goodTau_Hcand"
    };
  
  TH1D* h_hist[nFiles][nHist];
  
  
  for(uint iFile=0; iFile < nFiles; iFile++)
  {
	  for(uint iHist=0; iHist < nHist; iHist++)
	  {
		h_hist[iFile][iHist]= (TH1D*)f[iFile]->Get(histNames[iHist]);
	  }	
	  
  } 
//  h_hist[0][0]->Draw();
  TCanvas* c1 = new TCanvas("c1","c1", 1024,1024);
  TPad* histPad = new TPad("histPad","histPad",0.01,0.25,0.99,0.99);
  histPad->SetBottomMargin(0.02);
  histPad->Draw();
  
  TPad* diffPad = new TPad("diffPad","diffPad",0.01,0.01,0.99,0.25);
  diffPad->SetBottomMargin(0.3);
  diffPad->SetTopMargin(0.0);
  diffPad->Draw();	
  
  for(uint iHist=0; iHist < nHist; iHist++)
  {
	TLegend* legMT = new TLegend(0.6,0.7,0.8,0.9);
    legMT->SetBorderSize(0);
    legMT->SetFillColor(0);
    legMT->SetTextSize(legend_size);
	
	for(uint iFile=0; iFile < nFiles; iFile++)
	{
		h_hist[iFile][iHist]->SetLineColor(colors[iFile]);
		h_hist[iFile][iHist]->SetMarkerStyle(markers[iFile]);
		h_hist[iFile][iHist]->SetMarkerColor(colors[iFile]);
		h_hist[iFile][iHist]->SetMarkerSize(2.0);	
        h_hist[iFile][iHist]->GetXaxis()->SetLabelOffset(0.1);					
		if(iHist>0 && iHist<3) h_hist[iFile][iHist]->Rebin(4);
	}
	legMT->AddEntry(h_hist[0][iHist],fileNames[0],"l");
	legMT->AddEntry(h_hist[1][iHist],fileNames[1],"p");
	
	
	
	
	histPad->cd();		
	h_hist[0][iHist]->Draw("hist");
	h_hist[1][iHist]->Draw("same");
	legMT->Draw();  
	TH1D* h_diff=(TH1D*)h_hist[1][iHist]->Clone();
	h_diff->Divide(h_hist[0][iHist]);
	diffPad->cd();
	diffPad->SetGridy();
	diffPad->SetGridx();
	
	h_diff->GetYaxis()->SetLabelSize(0.1);
    h_diff->GetYaxis()->SetTitleOffset(0.55);
    h_diff->GetYaxis()->SetTitleSize(0.12);
    h_diff->GetYaxis()->SetTitle("new/old");
    h_diff->GetXaxis()->SetLabelSize(0.12);
    h_diff->GetXaxis()->SetLabelOffset(0.01);
    h_diff->GetXaxis()->SetTitleSize(0.15);
	h_diff->GetYaxis()->SetNdivisions(509);
	h_diff->SetMinimum(0.95);
	h_diff->SetMaximum(1.05);
	
	h_diff->Draw("hist");
	
	c1->Print(outputDir+"/png/"+histNames[iHist]+".png");
  }
  
   //~ 
  //~ 
  //~ // mutau FR
  //~ 
  
  //~ for(uint iFile=0; iFile < nFiles; iFile++)
	//~ {
		//~ //adding Zmumu and Zee togethger
		//~ h_denom_types[iFile][0]->Add(h_denom_types[iFile][4]);
		//~ h_loose_types[iFile][0]->Add(h_loose_types[iFile][4]);
		//~ TH1D* h_loose_FR = (TH1D*)h_loose_types[iFile][0]->Clone(); 
		//~ h_loose_FR->Divide(h_denom_types[iFile][0]);
		//~ 
		//~ h_loose_FR->Rebin(rebinLeptonFR);
		//~ h_loose_FR->Scale(1./rebinLeptonFR);
		//~ 
		//~ h_loose_FR->GetXaxis()->SetTitle("#mu P_{T}[GeV]");
		//~ h_loose_FR->GetYaxis()->SetTitle("loose fake rate");
		//~ 
		//~ h_loose_FR->SetLineColor(colors[iFile]);
		//~ h_loose_FR->SetMarkerStyle(markers[iFile]);
		//~ h_loose_FR->SetMarkerColor(colors[iFile]);
		//~ h_loose_FR->SetMarkerSize(2.0);
		//~ h_loose_FR->GetXaxis()->SetRangeUser(0.,50.);
		//~ h_loose_FR->SetMaximum(0.3);
		//~ 
		//~ 
		//~ legMT->AddEntry(h_loose_FR,fileNames[iFile],"lp");
		//~ 
		//~ if(iFile>0)h_loose_FR->Draw("same");
		//~ else h_loose_FR->Draw();
	//~ 
		//~ double sum=0.;
		//~ double err=0.;
		//~ for(uint iBin=2; iBin < 7; iBin++)
		//~ {
			//~ sum+=h_loose_FR->GetBinContent(iBin);
			//~ err+=(h_loose_FR->GetBinError(iBin)*h_loose_FR->GetBinError(iBin));
		//~ }
		//~ sum/=5.0;
		//~ err=sqrt(err)/5.0;
		//~ std::cout<< setiosflags(ios::fixed) << std::setprecision(3) << " Loose Muon " << fileNames[iFile] << " " << sum << "$\\pm$" << err << std::endl;
		//~ 
		//~ 
	//~ }
		//~ legMT->Draw();
		//~ c1->Print(outputDir+"/png/looseMuonFR.png");
		//~ c1->Print(outputDir+"/eps/looseMuonFR.eps");
		//~ c1->Print(outputDir+"/pdf/looseMuonFR.pdf");
		//~ 
	//~ for(uint iFile=0; iFile < nFiles; iFile++)
	//~ {
		//~ //adding Zmumu and Zee togethger
		//~ h_tight_types[iFile][0]->Add(h_tight_types[iFile][4]);
		//~ TH1D* h_tight_FR = (TH1D*)h_tight_types[iFile][0]->Clone(); 
		//~ h_tight_FR->Divide(h_denom_types[iFile][0]);
		//~ 
		//~ h_tight_FR->Rebin(rebinLeptonFR);
		//~ h_tight_FR->Scale(1./rebinLeptonFR);
		//~ 
		//~ h_tight_FR->GetXaxis()->SetTitle("#mu P_{T}[GeV]");
		//~ h_tight_FR->GetYaxis()->SetTitle("tight fake rate");
		//~ 
		//~ h_tight_FR->SetLineColor(colors[iFile]);
		//~ h_tight_FR->SetMarkerStyle(markers[iFile]);
		//~ h_tight_FR->SetMarkerColor(colors[iFile]);
		//~ h_tight_FR->GetXaxis()->SetRangeUser(0.,50.);
		//~ h_tight_FR->SetMarkerSize(2.0);
		//~ h_tight_FR->SetMaximum(0.3);
		//~ 
		//~ if(iFile>0)h_tight_FR->Draw("same");
		//~ else h_tight_FR->Draw();
		//~ 
		//~ double sum=0.;
		//~ double err=0.;
		//~ for(uint iBin=2; iBin < 7; iBin++)
		//~ {
			//~ sum+=h_tight_FR->GetBinContent(iBin);
			//~ err+=(h_tight_FR->GetBinError(iBin)*h_tight_FR->GetBinError(iBin));
		//~ }
		//~ sum/=5.0;
		//~ err=sqrt(err)/5.0;
		//~ std::cout<< setiosflags(ios::fixed) << std::setprecision(3) << " Tight Muon " << fileNames[iFile] << " " << sum << "$\\pm$" << err << std::endl;
		//~ 
		//~ 
	//~ }
		//~ legMT->Draw();
		//~ c1->Print(outputDir+"/png/tightMuonFR.png");
		//~ c1->Print(outputDir+"/eps/tightMuonFR.eps");
		//~ c1->Print(outputDir+"/pdf/tightMuonFR.pdf");
		//~ 
		//~ for(uint iFile=0; iFile < nFiles; iFile++)
	//~ {
		//~ //adding Zmumu and Zee togethger
		//~ h_denom_types[iFile][2]->Add(h_denom_types[iFile][6]);
		//~ h_loose_types[iFile][2]->Add(h_loose_types[iFile][6]);
		//~ TH1D* h_loose_FR = (TH1D*)h_loose_types[iFile][2]->Clone(); 
		//~ h_loose_FR->Divide(h_denom_types[iFile][2]);
		//~ 
		//~ h_loose_FR->Rebin(rebinLeptonFR);
		//~ h_loose_FR->Scale(1./rebinLeptonFR);
		//~ 
		//~ h_loose_FR->GetXaxis()->SetTitle("el P_{T}[GeV]");
		//~ h_loose_FR->GetYaxis()->SetTitle("loose fake rate");
		//~ 
		//~ h_loose_FR->SetLineColor(colors[iFile]);
		//~ h_loose_FR->SetMarkerStyle(markers[iFile]);
		//~ h_loose_FR->SetMarkerColor(colors[iFile]);
		//~ h_loose_FR->GetXaxis()->SetRangeUser(0.,50.);
		//~ h_loose_FR->SetMarkerSize(2.0);
		//~ h_loose_FR->SetMaximum(0.3);
		//~ 
		//~ if(iFile>0)h_loose_FR->Draw("same");
		//~ else h_loose_FR->Draw();
		//~ 
		//~ double sum=0.;
		//~ double err=0.;
		//~ for(uint iBin=2; iBin < 7; iBin++)
		//~ {
			//~ sum+=h_loose_FR->GetBinContent(iBin);
			//~ err+=(h_loose_FR->GetBinError(iBin)*h_loose_FR->GetBinError(iBin));
		//~ }
		//~ sum/=5.0;
		//~ err=sqrt(err)/5.0;
		//~ std::cout<< setiosflags(ios::fixed) << std::setprecision(3) << " Loose Electron " << fileNames[iFile] << " " << sum << "$\\pm$" << err << std::endl;
		//~ 
	//~ }
		//~ legMT->Draw();
		//~ c1->Print(outputDir+"/png/looseElectronFR.png");
		//~ c1->Print(outputDir+"/eps/looseElectronFR.eps");
		//~ c1->Print(outputDir+"/pdf/looseElectronFR.pdf");
		//~ 
	//~ for(uint iFile=0; iFile < nFiles; iFile++)
	//~ {
		//~ //adding Zmumu and Zee togethger
		//~ h_tight_types[iFile][2]->Add(h_tight_types[iFile][6]);
		//~ TH1D* h_tight_FR = (TH1D*)h_tight_types[iFile][2]->Clone(); 
		//~ h_tight_FR->Divide(h_denom_types[iFile][2]);
		//~ 
		//~ h_tight_FR->Rebin(rebinLeptonFR);
		//~ h_tight_FR->Scale(1./rebinLeptonFR);
		//~ 
		//~ h_tight_FR->GetXaxis()->SetTitle("el P_{T}[GeV]");
		//~ h_tight_FR->GetYaxis()->SetTitle("tight fake rate");
		//~ 
		//~ h_tight_FR->SetLineColor(colors[iFile]);
		//~ h_tight_FR->SetMarkerStyle(markers[iFile]);
		//~ h_tight_FR->SetMarkerColor(colors[iFile]);
		//~ h_tight_FR->GetXaxis()->SetRangeUser(0.,50.);
		//~ h_tight_FR->SetMaximum(0.3);
		//~ h_tight_FR->SetMarkerSize(2.0);
		//~ 
		//~ 
		//~ if(iFile>0)h_tight_FR->Draw("same");
		//~ else h_tight_FR->Draw();
		//~ 
		//~ double sum=0.;
		//~ double err=0.;
		//~ for(uint iBin=2; iBin < 7; iBin++)
		//~ {
			//~ sum+=h_tight_FR->GetBinContent(iBin);
			//~ err+=(h_tight_FR->GetBinError(iBin)*h_tight_FR->GetBinError(iBin));
		//~ }
		//~ sum/=5.0;
		//~ err=sqrt(err)/5.0;
		//~ std::cout<< setiosflags(ios::fixed) << std::setprecision(3) << " Tight Electron " << fileNames[iFile] << " " << sum << "$\\pm$" << err << std::endl;
		//~ 
		//~ 
	//~ }
		//~ legMT->Draw();
		//~ c1->Print(outputDir+"/png/tightElectronFR.png");
		//~ c1->Print(outputDir+"/eps/tightElectronFR.eps");
		//~ c1->Print(outputDir+"/pdf/tightElectronFR.pdf");
		//~ 
	//~ //tautau
	//~ TLegend* legTT = new TLegend(0.7,0.6,0.9,0.8);
  //~ legTT->SetBorderSize(0);
  //~ legTT->SetFillColor(0);
  //~ legTT->SetTextSize(legend_size);
  //~ for(uint iFile=0; iFile < nFiles; iFile++)
	//~ {
		//~ //adding Zmumu and Zee togethger
		//~ h_denom_types[iFile][3]->Add(h_denom_types[iFile][7]);
		//~ h_loose_types[iFile][3]->Add(h_loose_types[iFile][7]);
		//~ TH1D* h_loose_FR = (TH1D*)h_loose_types[iFile][3]->Clone(); 
		//~ h_loose_FR->Divide(h_denom_types[iFile][3]);
		//~ 
		//~ h_loose_FR->Rebin(rebinTauFR);
		//~ h_loose_FR->Scale(1./rebinTauFR);
		//~ 
		//~ h_loose_FR->GetXaxis()->SetTitle("#tau P_{T}[GeV]");
		//~ h_loose_FR->GetYaxis()->SetTitle("loose fake rate");
		//~ 
		//~ h_loose_FR->SetLineColor(colors[iFile]);
		//~ h_loose_FR->SetMarkerStyle(markers[iFile]);
		//~ h_loose_FR->SetMarkerColor(colors[iFile]);
		//~ h_loose_FR->SetMarkerSize(2.0);
		//~ h_loose_FR->GetXaxis()->SetRangeUser(0.,95.);
		//~ h_loose_FR->SetMaximum(0.1);
		//~ h_loose_FR->SetMinimum(0.);
		//~ 
		//~ 
		//~ TF1 *fit1 = new TF1("fit1","[0]+[1]*TMath::Exp([2]*x)",15.,80.);
		//~ fit1->SetParameters(0.015,0.2,-0.07);
		//~ fit1->SetLineColor(colors[iFile]);
		//~ h_loose_FR->Fit("fit1","RN");
		//~ 
		 //~ 
		//~ legTT->AddEntry(h_loose_FR,fileNames[iFile],"lp");
		//~ 
		//~ if(iFile>0)h_loose_FR->Draw("same");
		//~ else h_loose_FR->Draw();
		//~ 
		//~ fit1->Draw("same");
		//~ 
	//~ }
		//~ legTT->Draw();
		//~ c1->Print(outputDir+"/png/looseTauFR.png");
		//~ c1->Print(outputDir+"/eps/looseTauFR.eps");
		//~ c1->Print(outputDir+"/pdf/looseTauFR.pdf");
	//~ 
	//~ for(uint iFile=0; iFile < nFiles; iFile++)
	//~ {
		//~ //adding Zmumu and Zee togethger
		//~ h_medium_types[iFile][3]->Add(h_medium_types[iFile][7]);
		//~ TH1D* h_medium_FR = (TH1D*)h_medium_types[iFile][3]->Clone(); 
		//~ h_medium_FR->Divide(h_denom_types[iFile][3]);
		//~ 
		//~ h_medium_FR->Rebin(rebinTauFR);
		//~ h_medium_FR->Scale(1./rebinTauFR);
		//~ 
		//~ h_medium_FR->GetXaxis()->SetTitle("#tau P_{T}[GeV]");
		//~ h_medium_FR->GetYaxis()->SetTitle("medium fake rate");
		//~ 
		//~ h_medium_FR->SetLineColor(colors[iFile]);
		//~ h_medium_FR->SetMarkerStyle(markers[iFile]);
		//~ h_medium_FR->SetMarkerColor(colors[iFile]);
		//~ h_medium_FR->SetMarkerSize(2.0);
		//~ h_medium_FR->GetXaxis()->SetRangeUser(0.,95.);
		//~ h_medium_FR->SetMaximum(0.1);
		//~ h_medium_FR->SetMinimum(0.);
		//~ 
		//~ 
		//~ TF1 *fit1 = new TF1("fit1","[0]+[1]*TMath::Exp([2]*x)",15.,80.);
		//~ fit1->SetParameters(0.015,0.2,-0.07);
		//~ fit1->SetLineColor(colors[iFile]);
		//~ h_medium_FR->Fit("fit1","RN");
		//~ 
		 //~ 
		//~ 
		//~ if(iFile>0)h_medium_FR->Draw("same");
		//~ else h_medium_FR->Draw();
		//~ 
		//~ fit1->Draw("same");
		//~ 
	//~ }
		//~ legTT->Draw();
		//~ c1->Print(outputDir+"/png/mediumTauFR.png");
		//~ c1->Print(outputDir+"/eps/mediumTauFR.eps");
		//~ c1->Print(outputDir+"/pdf/mediumTauFR.pdf");
	//~ 
	//~ for(uint iFile=0; iFile < nFiles; iFile++)
	//~ {
		//~ //adding Zmumu and Zee togethger
		//~ h_tight_types[iFile][3]->Add(h_tight_types[iFile][7]);
		//~ TH1D* h_tight_FR = (TH1D*)h_tight_types[iFile][3]->Clone(); 
		//~ h_tight_FR->Divide(h_denom_types[iFile][3]);
		//~ 
		//~ h_tight_FR->Rebin(rebinTauFR);
		//~ h_tight_FR->Scale(1./rebinTauFR);
		//~ 
		//~ h_tight_FR->GetXaxis()->SetTitle("#tau P_{T}[GeV]");
		//~ h_tight_FR->GetYaxis()->SetTitle("tight fake rate");
		//~ 
		//~ h_tight_FR->SetLineColor(colors[iFile]);
		//~ h_tight_FR->SetMarkerStyle(markers[iFile]);
		//~ h_tight_FR->SetMarkerColor(colors[iFile]);
		//~ h_tight_FR->SetMarkerSize(2.0);
		//~ h_tight_FR->GetXaxis()->SetRangeUser(0.,95.);
		//~ h_tight_FR->SetMaximum(0.1);
		//~ h_tight_FR->SetMinimum(0.);
		//~ 
		//~ 
		//~ TF1 *fit1 = new TF1("fit1","[0]+[1]*TMath::Exp([2]*x)",15.,80.);
		//~ fit1->SetParameters(0.015,0.2,-0.07);
		//~ fit1->SetLineColor(colors[iFile]);
		//~ h_tight_FR->Fit("fit1","RN");
		//~ 
		 //~ 
		//~ 
		//~ if(iFile>0)h_tight_FR->Draw("same");
		//~ else h_tight_FR->Draw();
		//~ 
		//~ fit1->Draw("same");
		//~ 
	//~ }
		//~ legTT->Draw();
		//~ c1->Print(outputDir+"/png/tightTauFR.png");
		//~ c1->Print(outputDir+"/eps/tightTauFR.eps");
		//~ c1->Print(outputDir+"/pdf/tightTauFR.pdf");
	
	
		//~ // tautau FR
  //~ for(uint iFile=0; iFile < nFiles; iFile++)
	//~ {
		//~ //adding Zmumu and Zee togethger
		//~ h_denom_types[iFile][3]->Add(h_denom_types[iFile][7]);
		//~ h_loose_types[iFile][3]->Add(h_loose_types[iFile][7]);
		//~ h_medium_types[iFile][3]->Add(h_medium_types[iFile][7]);
		//~ h_tight_types[iFile][3]->Add(h_tight_types[iFile][7]); 
		//~ TH1D* h_loose_FR = (TH1D*)h_loose_types[iFile][3]->Clone(); 
		//~ h_loose_FR->Divide(h_denom_types[iFile][3]);
		//~ TH1D* h_medium_FR = (TH1D*)h_medium_types[iFile][3]->Clone(); 
		//~ h_medium_FR->Divide(h_denom_types[iFile][3]);
		//~ TH1D* h_tight_FR = (TH1D*)h_tight_types[iFile][3]->Clone(); 
		//~ h_tight_FR->Divide(h_denom_types[iFile][3]);
		//~ 
		//~ h_loose_FR->Rebin(rebinTauFR);
		//~ h_loose_FR->Scale(1./rebinTauFR);
		//~ h_medium_FR->Rebin(rebinTauFR);
		//~ h_medium_FR->Scale(1./rebinTauFR);
		//~ h_tight_FR->Rebin(rebinTauFR);
		//~ h_tight_FR->Scale(1./rebinTauFR);
		//~ 
		//~ h_loose_FR->GetXaxis()->SetTitle("P_{T}[GeV]");
		//~ h_loose_FR->GetYaxis()->SetTitle("loose fake rate");
		//~ h_medium_FR->GetXaxis()->SetTitle("P_{T}[GeV]");
		//~ h_medium_FR->GetYaxis()->SetTitle("medium fake rate");
		//~ h_tight_FR->GetXaxis()->SetTitle("P_{T}[GeV]");
		//~ h_tight_FR->GetYaxis()->SetTitle("tight fake rate");
		//~ 
		//~ h_loose_FR->Draw();
		//~ TF1 *fit1 = new TF1("fit1","[0]+[1]*TMath::Exp([2]*x)",15.,80.);
		//~ fit1->SetParameters(0.015,0.2,-0.07);
		//~ h_loose_FR->Fit("fit1","R");
		//~ 
		//~ c1->Print(outputDir+"/png/looseTauFR.png");
		//~ c1->Print(outputDir+"/eps/looseTauFR.eps");
		//~ c1->Print(outputDir+"/pdf/looseTauFR.pdf");
		//~ 
		//~ h_medium_FR->Draw();
		//~ h_medium_FR->Fit("fit1","R");
		//~ 
		//~ c1->Print(outputDir+"/png/mediumTauFR.png");
		//~ c1->Print(outputDir+"/eps/mediumTauFR.eps");
		//~ c1->Print(outputDir+"/pdf/mediumTauFR.pdf");
		//~ 
		//~ h_tight_FR->Draw();
		//~ h_tight_FR->Fit("fit1","R");
		//~ 
		//~ c1->Print(outputDir+"/png/tightTauFR.png");
		//~ c1->Print(outputDir+"/eps/tightTauFR.eps");
		//~ c1->Print(outputDir+"/pdf/tightTauFR.pdf");
	//~ }
  //~ 
 	
  return 0;
}
