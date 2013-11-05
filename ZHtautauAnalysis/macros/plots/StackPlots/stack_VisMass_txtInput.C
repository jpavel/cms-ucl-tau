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
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
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

  
  std::vector<TString> bg_names;
  std::vector<Double_t> bg_xsec;
 
  std::vector<Bool_t> bg_plot;
  std::vector<Bool_t> bg_save;
  std::vector<TString> bg_titles;
  
  std::ifstream myfile;
  myfile.open ("BGinput.txt");	
  if (myfile.is_open()){
	while ( myfile.good() ){
		TString name;
		myfile >> name;
		if(name.Length()==0) continue;
		bg_names.push_back(name);
		Double_t xsec;
		myfile >> xsec;
		bg_xsec.push_back(xsec);
		Bool_t plot;
		myfile >> plot;
		bg_plot.push_back(plot);
		Bool_t save;
		myfile >> save;
		bg_save.push_back(save);
		TString title;
		myfile >> title;
		bg_titles.push_back(title);
		std::cout << name << " " << xsec << " " 
		<< " " << plot << save << std::endl;  
	}
	myfile.close();
  }
  
  for (uint iVec=0; iVec < bg_names.size(); iVec++)
  {
		std::cout << iVec << ": " << bg_names[iVec] << " " << bg_xsec[iVec] << " " 
		<< " " << bg_plot[iVec] << bg_save[iVec] << std::endl;
  }
  
  std::vector<TString> data_names;
  std::vector<Double_t> data_lumi;
 
  
  std::ifstream datafile;
  datafile.open ("Datainput.txt");	
  if (datafile.is_open()){
	while ( datafile.good() ){
		TString name;
		datafile >> name;
		if(name.Length()==0) continue;
		data_names.push_back(name);
		Double_t xsec;
		datafile >> xsec;
		data_lumi.push_back(xsec);
		std::cout << name << " " << xsec << std::endl;  
	}
	datafile.close();
  }
  
  std::vector<TString> signal_names;
  std::vector<TString> signal_titles;
  
  std::vector<Double_t> signal_xsec;
 
  
  std::ifstream signalfile;
  signalfile.open ("Signalinput.txt");	
  if (signalfile.is_open()){
	while ( signalfile.good() ){
		TString title;
		signalfile >> title;
		if(title.Length()==0) continue;
		signal_titles.push_back(title);
		TString name;
		signalfile >> name;
		signal_names.push_back(name);
		Double_t xsec;
		signalfile >> xsec;
		signal_xsec.push_back(xsec);
		std::cout << title << " " << name << " " << xsec << std::endl;  
	}
	signalfile.close();
  }

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
  
  TString inputDir = "/home/jpavel/analysis/CMS/histograms/PostMoriod/20130918/MySummary11/";
  
  TString outputDir = "/home/jpavel/analysis/CMS/Plots/Stack/PostMoriond/20131104_MVis";
  gROOT->ProcessLine(".!mkdir -p "+outputDir+"/png");
  gROOT->ProcessLine(".!mkdir -p "+outputDir+"/pdf");
 
  
  std::vector<TFile*> f_bg;  	
  std::vector<TFile*> f_data;  	
  
    std::stringstream indexes;  
  for(int iFile = 0; iFile < data_names.size(); iFile++)
  {
	  indexes.str("");
	  indexes << inputDir << data_names[iFile] << "/Summary.root";
	  std::string input_file=indexes.str();
	  f_data.push_back(TFile::Open(input_file.c_str()));
	  if(!f_data[iFile]) {
		  std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
		  return 1;
	  } else std::cout << "File " << input_file << " succesfully opened!" << std::endl;
  }
  
  //f_data.push_back(TFile::Open("/home/jpavel/analysis/CMS/histograms/PostMoriod/20130918/PostAnalysisSummary/2012.root"));
  
  //~ if(!f_data[0]) {
		  //~ std::cerr << "Error: file " << "/home/jpavel/analysis/CMS/histograms/PostMoriod/20130918/PostAnalysisSummary/2012.root" << " could not be opened." << std::endl; 
		  //~ return 1;
	  //~ }
	  //~ else std::cout << "File " << "/home/jpavel/analysis/CMS/histograms/PostMoriod/20130918/PostAnalysisSummary/2012.root" << " succesfully opened!" << std::endl;
  //~ 


  for(int iFile = 0; iFile < bg_names.size(); iFile++)
  {
	  indexes.str("");
	  indexes << inputDir << bg_names[iFile] << "/Summary.root";
	  std::string input_file=indexes.str();
	  f_bg.push_back(TFile::Open(input_file.c_str()));
	  if(!f_bg[iFile]) {
		  std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
		  return 1;
	  } else std::cout << "File " << input_file << " succesfully opened!" << std::endl;
  }
  
  // tau ES
  
  TString tauESplusSuffix=	"TauESplus";
  TString tauESminusSuffix=	"TauESminus";

  std::vector<TFile*> f_bg_ESplus;
  std::vector<TFile*> f_bg_ESminus;
  
  for(int iFile = 0; iFile < bg_names.size(); iFile++)
  {
	  indexes.str("");
	  indexes << inputDir << bg_names[iFile] << "_" << tauESplusSuffix << "/Summary.root";
	  std::string input_file=indexes.str();
	  f_bg_ESplus.push_back(TFile::Open(input_file.c_str()));
	  if(!f_bg_ESplus[iFile]) {
		  std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
		  return 1;
	  } else std::cout << "File " << input_file << " succesfully opened!" << std::endl;
  }
  
  for(int iFile = 0; iFile < bg_names.size(); iFile++)
  {
	  indexes.str("");
	  indexes << inputDir << bg_names[iFile] << "_" << tauESminusSuffix << "/Summary.root";
	  std::string input_file=indexes.str();
	  f_bg_ESminus.push_back(TFile::Open(input_file.c_str()));
	  if(!f_bg_ESminus[iFile]) {
		  std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
		  return 1;
	  } else std::cout << "File " << input_file << " succesfully opened!" << std::endl;
  }
  
  // signal
  
  std::vector<TFile*> f_signal;  	
  
  for(int iFile = 0; iFile < signal_names.size(); iFile++)
  {
	  indexes.str("");
	  indexes << inputDir << signal_names[iFile] << "/Summary.root";
	  std::string input_file=indexes.str();
	  f_signal.push_back(TFile::Open(input_file.c_str()));
	  if(!f_signal[iFile]) {
		  std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
		  return 1;
	  } else std::cout << "File " << input_file << " succesfully opened!" << std::endl;
  }
  
  // tau ES
  
  

  std::vector<TFile*> f_signal_ESplus;
  std::vector<TFile*> f_signal_ESminus;
  
  for(int iFile = 0; iFile < signal_names.size(); iFile++)
  {
	  indexes.str("");
	  indexes << inputDir << signal_names[iFile] << "_" << tauESplusSuffix << "/Summary.root";
	  std::string input_file=indexes.str();
	  f_signal_ESplus.push_back(TFile::Open(input_file.c_str()));
	  if(!f_signal_ESplus[iFile]) {
		  std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
		  return 1;
	  } else std::cout << "File " << input_file << " succesfully opened!" << std::endl;
  }
  
  for(int iFile = 0; iFile < signal_names.size(); iFile++)
  {
	  indexes.str("");
	  indexes << inputDir << signal_names[iFile] << "_" << tauESminusSuffix << "/Summary.root";
	  std::string input_file=indexes.str();
	  f_signal_ESminus.push_back(TFile::Open(input_file.c_str()));
	  if(!f_signal_ESminus[iFile]) {
		  std::cerr << "Error: file " << input_file << " could not be opened." << std::endl; 
		  return 1;
	  } else std::cout << "File " << input_file << " succesfully opened!" << std::endl;
  }

  const int nHist1 = 9;
  //const int nHist1 = 44;


  TString histNames1[nHist1] = {"h_visMass","h_H_visMass_type_4","h_H_visMass_type_3","h_H_visMass_type_1","h_H_visMass_type_2","h_H_visMass_type_8","h_H_visMass_type_5","h_H_visMass_type_7","h_H_visMass_type_6"};
  TString histBGNames1[nHist1] = {"h_FR_visMass","h_H_FR_visMass_type_4","h_H_FR_visMass_type_3","h_H_FR_visMass_type_1","h_H_FR_visMass_type_2","h_H_FR_visMass_type_8","h_H_FR_visMass_type_5","h_H_FR_visMass_type_7","h_H_FR_visMass_type_6"};
  
  TString histTitles[nHist1] = {"M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]","M_{#tau#tau}[GeV]"};
  TString PaveText[nHist1]	= {"CMS preliminary 2012","MMTT","MMET","MMMT","MMME","EETT","EEMT","EEET","EEEM"};
 
  std::vector<std::vector<TH1F*>* > 	h_1d_bg;
  std::vector<std::vector<TH1F*>* > 	h_1d_bg_ESplus;
  std::vector<std::vector<TH1F*>* > 	h_1d_bg_ESminus; 
  
  std::vector<std::vector<TH1F*>* > 	h_1d_signal;
  std::vector<std::vector<TH1F*>* > 	h_1d_signal_ESplus;
  std::vector<std::vector<TH1F*>* > 	h_1d_signal_ESminus; 
  //std::vector<std::vector<TH1F*>* > 	h_1d_data;
  TH1F * 		h_1d_data[nHist1];
 
  TH1F * 		h_1BG[nHist1];
 
 // TH1F *                signal[nHist1];
  
  std::vector<Double_t> weights;
  std::vector<Double_t> weight_signal;
  
  //Double_t xsection[nFiles]={1.0, 0.130, 1.057, 23.64, 0.208, 0.01203, 0.0048}; // pb
  //Double_t events[nFiles]={1.0, 4989540, 2979624, 10783509, 210160, 400973, 548760}; // pb
  
  Color_t colors[6]={kRed,kYellow,kMagenta,kGreen,kBlack,kBlue};
  

  double total_lumi = 0;// 19711.2250; //// pb-1
  
  for(int iFile = 0; iFile < (data_names.size()/2); iFile++)
  {
	total_lumi+=data_lumi[iFile];
  }
  
  std::cout << "Total lumi is " << total_lumi << std::endl;
  for(int iFile = 0; iFile < bg_names.size(); iFile++)
	{
		TH1D * h_pu = (TH1D*)f_bg[iFile]->Get("AnalysisHistos/h_nPU_raw");
		std::cout << h_pu->Integral() << std::endl;
		double lumi =  h_pu->Integral()/bg_xsec[iFile];
		weights.push_back(total_lumi/lumi);
		std::cout << weights[iFile] << std::endl;
	}
	
	for(int iFile = 0; iFile < signal_names.size(); iFile++)
	{
		TH1D * h_pu = (TH1D*)f_signal[iFile]->Get("AnalysisHistos/h_nPU_raw");
		std::cout << h_pu->Integral() << std::endl;
		double lumi =  h_pu->Integral()/signal_xsec[iFile];
		weight_signal.push_back(total_lumi/lumi);
		std::cout << weight_signal[iFile] << std::endl;
	}

  for(int iFile = 0; iFile < bg_names.size(); iFile++)
  {
	  std::vector<TH1F*>* temp_vec = new std::vector<TH1F*>;
	  for(int iHist = 0; iHist < nHist1; iHist++)
	  {
		  TH1F* test = (TH1F*)f_bg[iFile]->Get(histNames1[iHist]);
		  temp_vec->push_back(test);
		  (*temp_vec)[iHist]->Draw();	
		 
		  (*temp_vec)[iHist]->Scale(weights[iFile]); 
		  (*temp_vec)[iHist]->Rebin(20);
	  }
	  h_1d_bg.push_back(temp_vec);
  }
  
   for(int iFile = 0; iFile < bg_names.size(); iFile++)
  {
	  std::vector<TH1F*>* temp_vec = new std::vector<TH1F*>;
	  for(int iHist = 0; iHist < nHist1; iHist++)
	  {
		  TH1F* test = (TH1F*)f_bg_ESplus[iFile]->Get(histNames1[iHist]);
		  temp_vec->push_back(test);
		  (*temp_vec)[iHist]->Draw();	
		 
		  (*temp_vec)[iHist]->Scale(weights[iFile]); 
		  (*temp_vec)[iHist]->Rebin(20);
	  }
	  h_1d_bg_ESplus.push_back(temp_vec);
  }
  
  for(int iFile = 0; iFile < bg_names.size(); iFile++)
  {
	  std::vector<TH1F*>* temp_vec = new std::vector<TH1F*>;
	  for(int iHist = 0; iHist < nHist1; iHist++)
	  {
		  TH1F* test = (TH1F*)f_bg_ESminus[iFile]->Get(histNames1[iHist]);
		  temp_vec->push_back(test);
		  (*temp_vec)[iHist]->Draw();	
		 
		  (*temp_vec)[iHist]->Scale(weights[iFile]); 
		  (*temp_vec)[iHist]->Rebin(20);
	  }
	  h_1d_bg_ESminus.push_back(temp_vec);
  }
  
  

// signal

for(int iFile = 0; iFile < signal_names.size(); iFile++)
  {
	  std::vector<TH1F*>* temp_vec = new std::vector<TH1F*>;
	  for(int iHist = 0; iHist < nHist1; iHist++)
	  {
		  TH1F* test = (TH1F*)f_signal[iFile]->Get(histNames1[iHist]);
		  temp_vec->push_back(test);
		  (*temp_vec)[iHist]->Draw();	
		 
		  (*temp_vec)[iHist]->Scale(weight_signal[iFile]); 
		  (*temp_vec)[iHist]->Rebin(20);
	  }
	  h_1d_signal.push_back(temp_vec);
  }
  
   for(int iFile = 0; iFile < signal_names.size(); iFile++)
  {
	  std::vector<TH1F*>* temp_vec = new std::vector<TH1F*>;
	  for(int iHist = 0; iHist < nHist1; iHist++)
	  {
		  TH1F* test = (TH1F*)f_signal_ESplus[iFile]->Get(histNames1[iHist]);
		  temp_vec->push_back(test);
		  (*temp_vec)[iHist]->Draw();	
		 
		  (*temp_vec)[iHist]->Scale(weight_signal[iFile]); 
		  (*temp_vec)[iHist]->Rebin(20);
	  }
	  h_1d_signal_ESplus.push_back(temp_vec);
  }
  
  for(int iFile = 0; iFile < signal_names.size(); iFile++)
  {
	  std::vector<TH1F*>* temp_vec = new std::vector<TH1F*>;
	  for(int iHist = 0; iHist < nHist1; iHist++)
	  {
		  TH1F* test = (TH1F*)f_signal_ESminus[iFile]->Get(histNames1[iHist]);
		  temp_vec->push_back(test);
		  (*temp_vec)[iHist]->Draw();	
		 
		  (*temp_vec)[iHist]->Scale(weight_signal[iFile]); 
		  (*temp_vec)[iHist]->Rebin(20);
	  }
	  h_1d_signal_ESminus.push_back(temp_vec);
  }

//data

  for(int iHist=0; iHist < nHist1; iHist++)
  {
	  for(int iFile=0; iFile < data_names.size(); iFile++)
	  {
		TH1F* test =(TH1F*)f_data[iFile]->Get(histNames1[iHist]);
		if(iFile==0) h_1d_data[iHist]=(TH1F*)test->Clone();
		else h_1d_data[iHist]->Add(test);
	  }
	 h_1d_data[iHist]->Rebin(20);
	 if(iHist==1) h_1d_data[0]=(TH1F*)h_1d_data[iHist]->Clone();
	 if(iHist>1) h_1d_data[0]->Add(h_1d_data[iHist]);				 
  }
  
  std::vector<double>* BGcounts = EstimateBackground("/home/jpavel/analysis/CMS/histograms/PostMoriod/20130918/AnalysisOutput_v2/2012.root",
		"/home/jpavel/analysis/CMS/histograms/PostMoriod/20130918/AnalysisOutput_v2/2012.root");
  //getting histograms for the background
  
  for(int iBG=0; iBG < BGcounts->size(); iBG++)
  {
	std::cout << BGcounts->at(iBG) << std::endl;
	
  } 
  
  uint MeToULBconv[8] = { 4,3,1,2,8,5,7,6};
// reducible
 
  for(int iHist=0; iHist < nHist1; iHist++)
  {
  
	  for(int iFile=0; iFile < data_names.size(); iFile++)
	  {
		TH1F* test =(TH1F*)f_data[iFile]->Get(histBGNames1[iHist]);
		if(iFile==0) h_1BG[iHist]=(TH1F*)test->Clone();
		else h_1BG[iHist]->Add(test);
	  }
	
	 if(iHist>0) h_1BG[iHist]->Scale(BGcounts->at(MeToULBconv[iHist-1]-1)/h_1BG[iHist]->Integral());
	 h_1BG[iHist]->Rebin(20);
	 if(iHist==1) h_1BG[0]=(TH1F*)h_1BG[iHist]->Clone();
	 if(iHist>1) h_1BG[0]->Add(h_1BG[iHist]);			
	
  }

  
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
h_1d_data[0]->Draw();
 
  //~ for(int iHist = 0; iHist < nHist1; iHist++){
	  //~ signal[iHist] = (TH1F*)h_1d[iHist][5]->Clone();}

  
  for(int iHist = 0; iHist < nHist1; iHist++) 
  {
	  THStack *hs = new THStack("hs","Stacked MC histograms");

	
	  for(int iFile=0; iFile < bg_names.size(); iFile++)
	  {
			
	  
		  (*(h_1d_bg[iFile]))[iHist]->SetLineWidth(0);
		  //h_1d[iFile][iHist]->SetFillStyle(3244);

		  (*(h_1d_bg[iFile]))[iHist]->SetFillColor(colors[iFile]);
		  //~ if(iFile == 1){   }
		  //~ else if(iFile == 2){  h_1d[iFile][iHist]->SetFillColor(WZ_Color); }
		  //~ else if(iFile == 3){  h_1d[iFile][iHist]->SetFillColor(TTbar_Color); }
		  //~ else if(iFile == 4){  h_1d[iFile][iHist]->SetFillColor(Zjet_Color); }
		  //~ else if(iFile == 5){
			  //~ signal[iFile]->Add(h_1d[iFile][iFile+1]);
                          //~ signal[iFile]->SetLineColor(kRed); 
                          //~ signal[iFile]->SetLineWidth(2.0); 
                          //~ 
                   //~ }

		  //if(iFile < 5) 
		 //if(iFile!=2 && iFile!=3)
		 if(bg_plot[iFile])	hs->Add((*(h_1d_bg[iFile]))[iHist],"hist");		

	  }
	 
	  
	  hs->Add(h_1BG[iHist],"hist");
	 
//~ 
		  //~ //hs->Add(signal[iFile],"hist");		
	  //~ 
	  h_1d_data[iHist]->SetMarkerStyle(21);
	  h_1d_data[iHist]->SetMarkerSize(0.7);
	  
//~ 
 TLegend* leg = new TLegend(0.65,0.60,0.88,0.88,NULL,"brNDC");
 leg->SetFillColor(0);
 leg->SetTextSize(0.035);
 leg->SetBorderSize(0);
			//~ 
			
	  leg->AddEntry(h_1d_data[iHist],"data 2012","p");   
	  for(uint iFile=0; iFile < bg_names.size(); iFile++)
	  {
		  if(bg_plot[iFile]) leg->AddEntry((*(h_1d_bg[iFile]))[iHist],bg_titles[iFile],"f");
	  }
	  
	  
	  leg->AddEntry(h_1BG[iHist],"reducible","f");
	   
	  //~ 
	  //~ leg->AddEntry(h_1d[iFile][4],"Z+jets","f");
	  //~ leg->AddEntry(signal[iFile],"ZH(125)","f");
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
   
	
//~ 
	h_1d_data[iHist]->Draw("PE01");
	  //~ double max = h_1d[iFile][0]->GetMaximum();
	  //~ h_1d[iFile][0]->GetYaxis()->SetRangeUser(1e-2,200*max);
	//~ // if(iHist > 0 && iHist < 4)  h_1d[iFile][0]->GetXaxis()->SetRangeUser(0,150);
	 //~ 
	h_1d_data[iHist]->GetXaxis()->SetTitle(histTitles[iHist]);
	   hs->Draw("same");
	 //~ // signal[iFile]->Scale(10.);
	  //~ signal[iFile]->Draw("histsame");
	h_1d_data[iHist]->Draw("samePE01");
      //~ 
	  //~ 
	  leg->Draw("same");
	  ll->Draw("same");
	  gPad->RedrawAxis();
//~ 
	  //~ c1->SetLogy();	
	   c1->Print(outputDir+"/png/"+histNames1[iHist]+".png");
       c1->Print(outputDir+"/pdf/"+histNames1[iHist]+".pdf");

	  //~ c1->Print("Moriond/Mu_"+histNames1[iFile]+"_all.eps");
	  //~ c1->SetLogy(0);
	  //~ h_1d[iFile][0]->GetYaxis()->SetRangeUser(0,1.5*max);
	//~ 
	  //~ c1->Print("Moriond/Mu_"+histNames1[iFile]+"_all_normal.png");
	  //~ c1->Print("Moriond/Mu_"+histNames1[iFile]+"_all_normal.eps");
	  	//~ 
	  //~ 
//~ 
//	   leg->Clear();
//	   hs->Clear();    

  }
  // saving stuff
  
  TString outputROOTDir = "/home/jpavel/analysis/CMS/SW/cms-ucl-tau/ZHtautauAnalysis/macros/LimitInput/";
 
  
  TFile out(outputROOTDir+"vhtt_llLL.inputsMVis2-sm-8TeV.root","RECREATE");
  TString dirNames[8] = { "mmtt_zh","mmet_zh","mmmt_zh","mmme_zh","eett_zh","eemt_zh","eeet_zh","eeem_zh"};
  TString upNames[8] = { "lltt","llet","llmt","llem","lltt","llmt","llet","llem"};
  TString nameES="_CMS_scale_t_";
  TString nameUp="Up";
  TString nameDown="Down";
  TString ZjetsName="Zjets";
  TString DataName="data_obs";
  
  for(uint iDir = 0; iDir < 8; iDir++)
  {
	out.mkdir(dirNames[iDir]);
	out.cd(dirNames[iDir]);
	
	//signal
	for(int iFile=0; iFile < signal_titles.size(); iFile++)
	{
		
		TH1D* hist = new TH1D(signal_titles[iFile],"",15,0,300);
		for(int iBin = 1; iBin <= (*(h_1d_signal[iFile]))[iDir+1]->GetNbinsX(); iBin++)
		{
			
			hist->SetBinContent(iBin,(*(h_1d_signal[iFile]))[iDir+1]->GetBinContent(iBin));
			hist->SetBinError(iBin,(*(h_1d_signal[iFile]))[iDir+1]->GetBinError(iBin));
		}
		hist->Write();
		
		TH1D* hist_Up = new TH1D(signal_titles[iFile]+nameES+upNames[iDir]+nameUp,"",15,0,300);
		for(int iBin = 1; iBin <= (*(h_1d_signal_ESplus[iFile]))[iDir+1]->GetNbinsX(); iBin++)
		{
			
			hist_Up->SetBinContent(iBin,(*(h_1d_signal_ESplus[iFile]))[iDir+1]->GetBinContent(iBin));
			hist_Up->SetBinError(iBin,(*(h_1d_signal_ESplus[iFile]))[iDir+1]->GetBinError(iBin));
		}
		hist_Up->Write();
		
		TH1D* hist_Down = new TH1D(signal_titles[iFile]+nameES+upNames[iDir]+nameDown,"",15,0,300);
		for(int iBin = 1; iBin <= (*(h_1d_signal_ESminus[iFile]))[iDir+1]->GetNbinsX(); iBin++)
		{
			
			hist_Down->SetBinContent(iBin,(*(h_1d_signal_ESminus[iFile]))[iDir+1]->GetBinContent(iBin));
			hist_Down->SetBinError(iBin,(*(h_1d_signal_ESminus[iFile]))[iDir+1]->GetBinError(iBin));
		}
		hist_Down->Write();
		
	}
	
	
	// reducible
	TH1D* hist_Zjets = new TH1D(ZjetsName,"",15,0,300);
	for(int iBin = 1; iBin <= h_1BG[iDir+1]->GetNbinsX(); iBin++)
		{
			
			hist_Zjets->SetBinContent(iBin,h_1BG[iDir+1]->GetBinContent(iBin));
			hist_Zjets->SetBinError(iBin,h_1BG[iDir+1]->GetBinError(iBin));
		}
		hist_Zjets->Write();
	
	// MC backgrounds
	for(int iFile=0; iFile < bg_titles.size(); iFile++)
	{
		if(!bg_save[iFile]) continue;
		TH1D* hist = new TH1D(bg_titles[iFile],"",15,0,300);
		for(int iBin = 1; iBin <= (*(h_1d_bg[iFile]))[iDir+1]->GetNbinsX(); iBin++)
		{
			
			hist->SetBinContent(iBin,(*(h_1d_bg[iFile]))[iDir+1]->GetBinContent(iBin));
			hist->SetBinError(iBin,(*(h_1d_bg[iFile]))[iDir+1]->GetBinError(iBin));
		}
		hist->Write();
		
		TH1D* hist_Up = new TH1D(bg_titles[iFile]+nameES+upNames[iDir]+nameUp,"",15,0,300);
		for(int iBin = 1; iBin <= (*(h_1d_bg_ESplus[iFile]))[iDir+1]->GetNbinsX(); iBin++)
		{
			
			hist_Up->SetBinContent(iBin,(*(h_1d_bg_ESplus[iFile]))[iDir+1]->GetBinContent(iBin));
			hist_Up->SetBinError(iBin,(*(h_1d_bg_ESplus[iFile]))[iDir+1]->GetBinError(iBin));
		}
		hist_Up->Write();
		
		TH1D* hist_Down = new TH1D(bg_titles[iFile]+nameES+upNames[iDir]+nameDown,"",15,0,300);
		for(int iBin = 1; iBin <= (*(h_1d_bg_ESminus[iFile]))[iDir+1]->GetNbinsX(); iBin++)
		{
			
			hist_Down->SetBinContent(iBin,(*(h_1d_bg_ESminus[iFile]))[iDir+1]->GetBinContent(iBin));
			hist_Down->SetBinError(iBin,(*(h_1d_bg_ESminus[iFile]))[iDir+1]->GetBinError(iBin));
		}
		hist_Down->Write();
		
	}
	
	//data
	TH1D* hist_data = new TH1D(DataName,"",15,0,300);
	for(int iBin = 1; iBin <= h_1d_data[iDir+1]->GetNbinsX(); iBin++)
	{
		
		hist_data->SetBinContent(iBin,h_1d_data[iDir+1]->GetBinContent(iBin));
		hist_data->SetBinError(iBin,h_1d_data[iDir+1]->GetBinError(iBin));
	}
	hist_data->Write();
	
	out.cd();
	
  }
  
  out.Close();

  return 0;

}
