#include <TFile.h>
#include <TKey.h>
#include <TH1D.h>
#include <TLegend.h>
#include <TPostScript.h>
#include <TPaveText.h>

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

int CompareAllHistos(TString input1 = "Abdollah.root", TString input2 = "mine.root") {
	
	gROOT->Reset();             
  //SetAtlasStyle();
  setTDRStyle();
  gStyle->SetPalette(1);
  gStyle->SetErrorX(0.5);
  
  TString Names[2] = { input1, input2};
  
  const uint nFiles = 2;
  TFile * f[nFiles];  	

  
  std::stringstream indexes;
  for(uint iFile = 0; iFile < nFiles; iFile++)
  {
	indexes.str("");
  	indexes << Names[iFile];
  	
	std::string input_file=indexes.str();
	f[iFile] = TFile::Open(input_file.c_str());
	if(!f[iFile]) {
		std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
    return 1;
	}
	else std::cout << "File " << input_file << " succesfully opened!" << std::endl;
  
  }
  
  TString dirNames[8] = { "mmtt_zh","mmet_zh","mmmt_zh","mmme_zh","eett_zh","eemt_zh","eeet_zh","eeem_zh"};
  
  TCanvas *c1 = new TCanvas("c1","",5,30,650,600);
  c1->SetGrid(0,0);
  c1->SetFillStyle(4000);
  c1->SetFillColor(10);
  c1->SetTicky();
  c1->SetObjectStat(0);
  
  
  TPostScript *ps[8];
  for(int iDir=0; iDir < 8; iDir++)
  { 
   ps[iDir] = new TPostScript(dirNames[iDir]+".ps",112);
   f[0]->cd(dirNames[iDir]);
   gDirectory->GetListOfKeys()->Print();
   TIter next(gDirectory->GetListOfKeys());
   TKey* key;
  	
  while ( (key = (TKey*)next())){
	std::cout << key->GetName() << std::endl;
	
	TH1D* hist = (TH1D*)f[0]->Get(dirNames[iDir]+"/"+key->GetName());
	TH1D* hist2 = (TH1D*)f[1]->Get(dirNames[iDir]+"/"+key->GetName());
	
	std::cout << hist << " " << hist2 << std::endl;
	if(!hist2) continue;
	int binmax = hist->GetMaximumBin();
	double max = 1.2*(hist->GetBinContent(binmax)+hist->GetBinError(binmax));
	int binmax2 = hist2->GetMaximumBin();
	double max2 = 1.2*(hist2->GetBinContent(binmax2)+hist2->GetBinError(binmax2));
	max = max2 > max ? max2 : max;
	
	hist->SetMaximum(max);
	hist->SetMarkerStyle(20);
	hist->SetMarkerSize(2);
	hist->SetLineWidth(2);
	
	ps[iDir]->NewPage();
	
	
	
	hist->Draw("e1");
	hist->GetXaxis()->SetTitle("m_{H}[GeV]");
	hist->GetYaxis()->SetTitle("Events/20 GeV");
	
	TLegend* leg = new TLegend(0.8,0.80,0.9,0.9,NULL,"brNDC");
	leg->SetFillColor(0);
	leg->SetTextSize(0.035);
	leg->SetBorderSize(0);
	
	leg->AddEntry(hist, "ULB", "lp");
	leg->AddEntry(hist2, "UCL", "lp");
	
	leg->Draw();
	
	hist2->SetLineColor(kRed);
	hist2->SetLineStyle(2);
	hist2->SetLineWidth(2);
	hist2->SetMarkerColor(kRed);
	hist2->SetMarkerStyle(25);
	hist2->SetMarkerSize(2);
	
	
	hist2->Draw("e1same");
	
	TString lumist="4.9 fb^{-1}";
	TPaveText *ll = new TPaveText(0.15, 0.95, 0.95, 0.99, "NDC");
	ll->SetTextSize(0.03);
	ll->SetTextFont(62);
	ll->SetFillColor(0);
	ll->SetBorderSize(0);
	ll->SetMargin(0.01);
	ll->SetTextAlign(12); // align left
	TString text = key->GetName();
	ll->AddText(0.01,0.7,text);
	text = "#sqrt{s} = 7 TeV  L = ";
	text = text + lumist;
	//  ll->SetTextAlign(32); // align right
	ll->AddText(0.7, 0.5, text);
	ll->Draw("same");
	  
	
	c1->Update();
  }
  
  ps[iDir]->Close();
	}
	
	return 0;
}
