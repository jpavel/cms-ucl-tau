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
#include "TColor.h"

//~ #include "../plotStyles/AtlasStyle.C"
//~ #include "../plotStyles/AtlasUtils.h"
//~ #include "../plotStyles/AtlasUtils.C"
//~ #include "../plotStyles/TriggerPerfPaperConsts.h"
//~ #include "../plotStyles/tdrstyle.C"

#include "../FakeRate/EstimateBackground.C"

using namespace std;


int stack_upgrade() {

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
  TString fileNames[nFiles] = {"2012",
  "ZZ",
  "WZ",
  "TT",
  "TTZ",
  "GG2L2L",
  "GG4L"};
  
  TString inputDir = "/home/jpavel/analysis/CMS/histograms/PostMoriod/20130918/PostAnalysisSummary/";
  
  TString outputDir = "/home/jpavel/analysis/CMS/Plots/Stack/PostMoriond/20130918";
  gROOT->ProcessLine(".!mkdir -p "+outputDir+"/png");
  gROOT->ProcessLine(".!mkdir -p "+outputDir+"/pdf");
 
  
  TFile * f[nFiles];  	
  std::stringstream indexes;  

  for(int iFile = 0; iFile < nFiles; iFile++)

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



  const int nHist1 = 9;
  //const int nHist1 = 44;


  TString histNames1[nHist1] = {"h_svMass","h_H_svMass_type_1","h_H_svMass_type_2","h_H_svMass_type_3","h_H_svMass_type_4","h_H_svMass_type_5","h_H_svMass_type_6","h_H_svMass_type_7","h_H_svMass_type_8"};
  TString histBGNames1[nHist1] = {"h_FR_svMass","h_H_FR_svMass_type_1","h_H_FR_svMass_type_2","h_H_FR_svMass_type_3","h_H_FR_svMass_type_4","h_H_FR_svMass_type_5","h_H_FR_svMass_type_6","h_H_FR_svMass_type_7","h_H_FR_svMass_type_8"};
  
  TString histTitles[nHist1] = {"M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]"};
  TString PaveText[nHist1]	= {"CMS preliminary 2012","MMMT","MMME","MMET","EETT","EEMT","EEME","EEET","EETT"};
 
  TH1F * 		h_1d[nHist1][nFiles];
  TH1F * 		h_1BG[nHist1];
 
 // TH1F *                signal[nHist1];
  
  Double_t weights[nFiles];
  Double_t xsection[nFiles]={1.0, 0.130, 1.057, 23.64, 0.208, 0.01203, 0.0048}; // pb
  Double_t events[nFiles]={1.0, 4989540, 2979624, 10783509, 210160, 400973, 548760}; // pb
  
  Color_t colors[nFiles]={kBlack,kRed,kYellow,kMagenta,kGreen,kBlack,kBlue};
  

  const double total_lumi = 19711.2250; //// pb-1
  
  for(int iFile = 0; iFile < nFiles; iFile++)
	{
		double lumi = events[iFile]/xsection[iFile];
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
		  h_1d[iHist][iFile]->Rebin(20);
	  }
  }
  
  
  std::vector<double>* BGcounts = EstimateBackground("/home/jpavel/analysis/CMS/histograms/PostMoriod/20130918/AnalysisOutput/2012.root",
		"/home/jpavel/analysis/CMS/histograms/PostMoriod/20130918/AnalysisOutput/2012.root");
  //getting histograms for the background
  
  for(int iBG=0; iBG < BGcounts->size(); iBG++)
  {
	std::cout << BGcounts->at(iBG) << std::endl;
	
  } 
  
  for(int iHist=0; iHist < nHist1; iHist++)
  {
	 h_1BG[iHist]=(TH1F*)f[0]->Get(histBGNames1[iHist]);
	 if(iHist>0) h_1BG[iHist]->Scale(BGcounts->at(iHist-1)/h_1BG[iHist]->Integral());
	 h_1BG[iHist]->Rebin(20);
	 if(iHist==1) h_1BG[0]=(TH1F*)h_1BG[iHist]->Clone();
	 if(iHist>1) h_1BG[0]->Add(h_1BG[iHist]);			
	 
  }
  h_1d[0][0]->Draw();
  
  
  //~ 
    //~ int ZZ_Color = TColor::GetColor("#99ff99");
    //~ int WZ_Color = TColor::GetColor("#660099");
    //~ int TTbar_Color = TColor::GetColor("#cc66cc");
    //~ int Zjet_Color = TColor::GetColor("#32c3ff");
//~ 
  TCanvas *c1 = new TCanvas("c1","",5,30,650,600);
  //gPad->SetLogy(); 
  c1->SetGrid(0,0);
  c1->SetFillStyle(4000);
  c1->SetFillColor(10);
  c1->SetTicky();
  c1->SetObjectStat(0);

  //~ for(int iHist = 0; iHist < nHist1; iHist++){
	  //~ signal[iHist] = (TH1F*)h_1d[iHist][5]->Clone();}

  for(int iHist = 0; iHist < nHist1; iHist++) 
  {
	  THStack *hs = new THStack("hs","Stacked MC histograms");


	  for(int iFile=1; iFile < nFiles; iFile++)
	  {

		  h_1d[iHist][iFile]->SetLineWidth(0);
		  //h_1d[iHist][iFile]->SetFillStyle(3244);

		  h_1d[iHist][iFile]->SetFillColor(colors[iFile]);
		  //~ if(iFile == 1){   }
		  //~ else if(iFile == 2){  h_1d[iHist][iFile]->SetFillColor(WZ_Color); }
		  //~ else if(iFile == 3){  h_1d[iHist][iFile]->SetFillColor(TTbar_Color); }
		  //~ else if(iFile == 4){  h_1d[iHist][iFile]->SetFillColor(Zjet_Color); }
		  //~ else if(iFile == 5){
			  //~ signal[iHist]->Add(h_1d[iHist][iFile+1]);
                          //~ signal[iHist]->SetLineColor(kRed); 
                          //~ signal[iHist]->SetLineWidth(2.0); 
                          //~ 
                   //~ }

		  //if(iFile < 5) 
		 //if(iFile!=2 && iFile!=3)
		  hs->Add(h_1d[iHist][iFile],"hist");		

	  }
	  hs->Add(h_1BG[iHist],"hist");
//~ 
		  //~ //hs->Add(signal[iHist],"hist");		
	  //~ 
	  h_1d[iHist][0]->SetMarkerStyle(21);
	  h_1d[iHist][0]->SetMarkerSize(0.7);
//~ 
 TLegend* leg = new TLegend(0.65,0.60,0.88,0.88,NULL,"brNDC");
 leg->SetFillColor(0);
 leg->SetTextSize(0.035);
 leg->SetBorderSize(0);
			//~ 
	  leg->AddEntry(h_1d[iHist][0],"data 2012","p");
	  leg->AddEntry(h_1d[iHist][1],"ppZZ","f");
	  leg->AddEntry(h_1d[iHist][2],"WZ","f");
	  leg->AddEntry(h_1d[iHist][3],"t#bar{t}","f");
	  leg->AddEntry(h_1d[iHist][4],"t#bar{t}Z","f");
	  leg->AddEntry(h_1d[iHist][5],"ggZZ2L2L","f");
	  leg->AddEntry(h_1d[iHist][6],"ggZZ4L","f");
	  leg->AddEntry(h_1BG[iHist],"reducible","f");
	  
	  //~ 
	  //~ leg->AddEntry(h_1d[iHist][4],"Z+jets","f");
	  //~ leg->AddEntry(signal[iHist],"ZH(125)","f");
//~ 
TString lumist="19.7 fb^{-1}";
  TPaveText *ll = new TPaveText(0.25, 0.95, 0.95, 0.99, "NDC");
  ll->SetTextSize(0.03);
  ll->SetTextFont(62);
  ll->SetFillColor(0);
  ll->SetBorderSize(0);
  ll->SetMargin(0.01);
  ll->SetTextAlign(12); // align left
  TString text = PaveText[iHist];
  ll->AddText(0.01,0.5,text);
  text = "#sqrt{s} = 8 TeV  L = ";
  text = text + lumist;
  //  ll->SetTextAlign(32); // align right
  ll->AddText(0.5, 0.5, text);
   
	  //~ /*double max_dy = h_1d[iHist][4]->GetMaximum();
	  //~ double max_data = h_1d[iHist][0]->GetMaximum();
	  //~ double max = 0;
//~ 
	  //~ if (max_dy > max_data){
		  //~ max = max_dy;}
	  //~ else {
		  //~ max = max_data;}
	  //~ if (max != 0) hs->SetMaximum(max);
//~ 
          //~ cout << "max data: " << max_data << endl;
          //~ cout << "max dy: " << max_dy << endl;
	  //~ */
//~ 
	  h_1d[iHist][0]->Draw("PE01");
	  //~ double max = h_1d[iHist][0]->GetMaximum();
	  //~ h_1d[iHist][0]->GetYaxis()->SetRangeUser(1e-2,200*max);
	//~ // if(iHist > 0 && iHist < 4)  h_1d[iHist][0]->GetXaxis()->SetRangeUser(0,150);
	 //~ 
	   h_1d[iHist][0]->GetXaxis()->SetTitle(histTitles[iHist]);
	   hs->Draw("same");
	 //~ // signal[iHist]->Scale(10.);
	  //~ signal[iHist]->Draw("histsame");
      h_1d[iHist][0]->Draw("samePE01");
      //~ 
	  //~ 
	  leg->Draw("same");
	  ll->Draw("same");
	  gPad->RedrawAxis();
//~ 
	  //~ c1->SetLogy();	
	   c1->Print(outputDir+"/png/"+histNames1[iHist]+".png");
       c1->Print(outputDir+"/pdf/"+histNames1[iHist]+".pdf");

	  //~ c1->Print("Moriond/Mu_"+histNames1[iHist]+"_all.eps");
	  //~ c1->SetLogy(0);
	  //~ h_1d[iHist][0]->GetYaxis()->SetRangeUser(0,1.5*max);
	//~ 
	  //~ c1->Print("Moriond/Mu_"+histNames1[iHist]+"_all_normal.png");
	  //~ c1->Print("Moriond/Mu_"+histNames1[iHist]+"_all_normal.eps");
	  	//~ 
	  //~ 
//~ 
	  //~ leg->Clear();
	  //~ hs->Clear();    

  }

  return 0;

}
