#include "TFile.h"
#include "TH1F.h"
#include "TLegend.h"

#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "./plotStyles/AtlasStyle.C"
#include "./plotStyles/AtlasUtils.h"
#include "./plotStyles/AtlasUtils.C"
#include "./plotStyles/TriggerPerfPaperConsts.h"

using namespace std;

int makePWhisto(TString filename_MC="/home/jpavel/analysis/CMS/ZHtautau/histos/2012ABCD/mc/20130114_AnalFullMC_DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/20130114_AnalFullMC_DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_histo.root",TString filename_data="/home/jpavel/analysis/CMS/ZHtautau/ZHtautauAnalysis/config/dataPileUpHistogramABCD_True_2012.root")
{
	gROOT->Reset();             
   SetAtlasStyle();
   gStyle->SetPalette(1);

	
	TFile *f = TFile::Open(filename_MC);
	if(!f) {
		std::cerr << "Error: file " << filename_MC << " could not be opened." << std::endl; 
    return 1;
	}
	else std::cout << "File " << filename_MC << " succesfully opened!" << std::endl;
	
	TFile *g = TFile::Open(filename_data);
	if(!f) {
		std::cerr << "Error: file " << filename_data << " could not be opened." << std::endl; 
    return 1;
	}
	else std::cout << "File " << filename_data << " succesfully opened!" << std::endl;
	
	
	TH1F* mu_orig_import= (TH1F*)f->Get("h_nPU_raw");
	TH1F* mu_RW_import= (TH1F*)f->Get("h_nPU_reweight");
	
	TH1F* mu_data= (TH1F*)g->Get("pileup");
	
	
	mu_orig_import->Draw();
	
	TH1F* mu_orig_mine = new TH1F("mu_orig_mine","#mu distribution before reweighting;#mu;fraction of events",21,-0.5,20.5);
	TH1F* mu_RW_mine = new TH1F("mu_RW_mine","#mu distribution after reweighting;#mu;fraction of events",21,-0.5,20.5);
	TH1F* mu_data_mine = new TH1F("mu_data_mine","#mu distribution in data;#mu;fraction of events",21,-0.5,20.5);
	
	
	for(int iBin = 1; iBin <= mu_orig_mine->GetNbinsX(); iBin++)
	{
		mu_orig_mine->SetBinContent(iBin,mu_orig_import->GetBinContent(iBin));
		mu_RW_mine->SetBinContent(iBin,mu_RW_import->GetBinContent((iBin-1)*5+1));
		
		float dataMuLowEdge  = mu_orig_mine->GetBinLowEdge(iBin);
		float dataMuHighEdge = mu_orig_mine->GetBinLowEdge(iBin) + mu_orig_mine->GetBinWidth(iBin);
		int dataBinNumberLowEdge  = mu_data->GetXaxis()->FindFixBin(dataMuLowEdge);
		int dataBinNumberHighEdge = mu_data->GetXaxis()->FindFixBin(dataMuHighEdge);
		float dataBinContent = mu_data->Integral( dataBinNumberLowEdge, dataBinNumberHighEdge-1 );
		
		mu_data_mine->SetBinContent(iBin,dataBinContent);
		
		
	}
	mu_orig_mine->SetBinContent(1,mu_orig_import->GetBinContent(101));

	mu_orig_import->Scale(1./mu_orig_import->GetSumOfWeights());
	mu_RW_import->Scale(1./mu_RW_import->GetSumOfWeights());
	mu_data->Scale(1./mu_data->GetSumOfWeights());
	//mu_data->Scale(10./mu_data->GetSumOfWeights());
	
	
	TCanvas* c1 = new TCanvas("c1","c1", 800,600);
     
	mu_orig_import->Draw();
	
	c1->Print("mu_mc.png");
	c1->Print("mu_mc.eps");
	
	mu_data->GetXaxis()->SetTitle("#mu");
	mu_data->GetYaxis()->SetTitle("fraction of events");
	
	mu_data->Draw();
	
	c1->Print("mu_data.png");
	c1->Print("mu_data.eps");
	
	
	float myMax[] = {mu_RW_import->GetMaximum(),mu_data->GetMaximum()};
	
	float Max_h = *max_element(myMax,myMax+2);
	
	mu_RW_import->SetMaximum(1.2*Max_h);
	mu_RW_import->SetMarkerStyle(25);
	mu_RW_import->SetMarkerSize(1.5);
	mu_RW_import->GetXaxis()->SetTitle("True number of interactions per event");
	mu_RW_import->GetXaxis()->SetRangeUser(0,60);
	mu_RW_import->GetYaxis()->SetTitle("Fraction of events");
	
	mu_RW_import->Draw("phist");
	//~ 
	//~ //mu_data->SetLineColor(kRed);
	//~ //mu_data->Draw("same");
	mu_data->SetLineColor(kGreen);
	mu_data->SetMarkerStyle(22);
	mu_data->SetMarkerSize(1.5);
	
	mu_data->SetMarkerColor(kGreen);
	
	mu_data->Draw("phistsame");
	mu_data->Draw("same");
	mu_RW_import->Draw("same");
	mu_orig_import->SetLineColor(kRed);
	
	mu_orig_import->Draw("histsame");
	
	gPad->RedrawAxis();
	
	TLegend* leg = new TLegend(0.6,0.6,0.8,0.93);
	leg->SetBorderSize(0);
	leg->SetFillColor(0);
	leg->SetTextSize(legend_size);
	leg->AddEntry(mu_RW_import,"re-weighted MC","p");
	leg->AddEntry(mu_data,"data 2012ABCD","lp");
	leg->AddEntry(mu_orig_import,"Summer12 53x MC","l");
	
	leg->Draw();
	
	c1->Print("mu_reweight.png");
	c1->Print("mu_reweight.eps");
	
	c1->SetLogy();
	mu_RW_import->SetMaximum(12*Max_h);
	
	c1->Print("mu_reweight_log.png");
	c1->Print("mu_reweight_log.eps");
	
	//~ 

	return 0;
}
