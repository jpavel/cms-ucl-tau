/* 
 * File:   jetVeto.h
 * Author: abdollah
 *
 * Created on July 21, 2010, 3:39 PM
 */






#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "../include/myevent.h"
//#include "ZHtautauAnalysis_LinkDef.h"
#include "TMath.h" //M_PI is in TMath
#include "TRandom3.h"
#include "../include/myobject.h"
#include <TLorentzVector.h>
//#include "Analysis.h"
using namespace std;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
bool isMC = true ;
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
          // *** 2011 *** //
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

double Cor_ID_Iso_Mu_Loose_2011(myobject const& a) {
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) < 1.5) return 0.9895;
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.1) return 1.0303;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) < 1.5) return 1.0168;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.1) return 1.0247;
    if (a.pt > 20 && fabs(a.eta) < 1.5) return 1.0061;
    if (a.pt > 20 && fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.1) return 1.0144;
    if (a.pt < 10 || a.pt >= 100 || fabs(a.eta) >= 2.10) return 1.000;
    return 1.0;
}

double Cor_ID_Iso_Mu_Tight_2011(myobject const& a) {
    if (a.pt > 17 && a.pt < 20 && fabs(a.eta) < 1.6) return 0.997*0.930;
    if (a.pt > 17 && a.pt < 20 && fabs(a.eta) > 1.6 && fabs(a.eta) < 2.1) return 0.986*0.929;
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) < 1.6) return 0.995*0.977;
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) > 1.6 && fabs(a.eta) < 2.1) return 0.986*0.984;
    if (a.pt > 30 && fabs(a.eta) < 1.6) return 1.030*1.010;
    if (a.pt > 30 && fabs(a.eta) > 1.6 && fabs(a.eta) < 2.1) return 0.990*0.997;
    if (a.pt < 17 || a.pt >= 100 || fabs(a.eta) >= 2.1) return 1.000;
    return 1.0;
}

double Cor_ID_Iso_Ele_Loose_2011(myobject const& a) {
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) < 1.479) return 1.0396;
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.1) return 0.9758;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) < 1.479) return 0.9622;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.1) return 1.1483;
    if (a.pt >= 20 && fabs(a.eta) < 1.479) return 0.9849;
    if (a.pt >= 20 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.1) return 1.0117;
    if (a.pt < 10 || a.pt >= 100 || fabs(a.eta) >= 2.1) return 1.000;
    return 1.0;
}

double Cor_ID_Iso_Ele_Tight_2011(myobject const& a) {
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) < 1.479) return 0.955*0.980;
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) > 1.479 && fabs(a.eta) < 2.1) return 0.938*0.967;
    if (a.pt > 30 && fabs(a.eta) < 1.479) return 1.044*0.984;
    if (a.pt > 30 && fabs(a.eta) > 1.479 && fabs(a.eta) < 2.1) return 0.977*0.989;
    if (a.pt < 20 || a.pt >= 100 || fabs(a.eta) >= 2.1) return 1.000;
    return 1.0;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
          // *** 2012 *** //
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

double Cor_ID_Iso_Mu_Loose_2012(myobject const& a) {
    if (a.pt > 15 && a.pt < 20 && fabs(a.eta) < 1.6) return 0.989*0.945;
    if (a.pt > 15 && a.pt < 20 && fabs(a.eta) > 1.6 && fabs(a.eta) < 2.1) return 0.977*1.047;
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) < 1.6) return 0.991*1.005;
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) > 1.6 && fabs(a.eta) < 2.1) return 0.974*0.992;
    if (a.pt > 30 && fabs(a.eta) < 1.6) return 0.989*0.993;
    if (a.pt > 30 && fabs(a.eta) > 1.6 && fabs(a.eta) < 2.1) return 0.989*1.005;
    if (a.pt < 15 || a.pt >= 100 || fabs(a.eta) >= 2.1) return 1.000;
    return 1.0;
}

double Cor_ID_Iso_Mu_Tight_2012(myobject const& a) {
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) < 0.8) return 0.9675;
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.5) return 0.9902;
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.1) return 0.9956;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) < 0.8) return 0.9841;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.5) return 0.9897;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.1) return 0.9891;
    if (a.pt > 20 && fabs(a.eta) < 0.8) return 0.9890;
    if (a.pt > 20 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.5) return 0.9910;
    if (a.pt > 20 && fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.1) return 0.9924;
    if (a.pt < 10 || a.pt >= 100 || fabs(a.eta) >= 2.1) return 1.000;
    return 1.0;
}

double Cor_ID_Iso_Ele_Loose_2012(myobject const& a) {
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) < 0.8) return 0.8500;
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.479) return 0.8995;
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.3) return 0.6683;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) < 0.8) return 0.9030;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.479) return 0.8623;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.3) return 0.7935;
    if (a.pt > 20 && fabs(a.eta) < 0.8) return 0.9562;
    if (a.pt > 20 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.479) return 0.9507;
    if (a.pt > 20 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.3) return 0.9584;
    if (a.pt < 10 || a.pt >= 100 || fabs(a.eta) >= 2.3) return 1.000;
    return 1.0;

}

double Cor_ID_Iso_Ele_Tight_2012(myobject const& a) {
	if (a.pt > 20 && a.pt < 30 && fabs(a.eta) < 1.479) return 0.922*0.974;
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) > 1.479 && fabs(a.eta) < 2.1) return 0.898*1.008;
    if (a.pt > 30 && fabs(a.eta) < 1.479) return 0.964*0.997;
    if (a.pt > 30 && fabs(a.eta) > 1.479 && fabs(a.eta) < 2.1) return 0.958*0.983;
    if (a.pt < 20 || a.pt >= 100 || fabs(a.eta) >= 2.1) return 1.000;
    return 1.0;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
          // *** 2012 53X *** //
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

double Cor_ID_Iso_Mu_Loose_2012_53X(myobject const& a) {
    if (a.pt > 10 && a.pt <= 15 && fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8) return 0.9845;
    if (a.pt > 10 && a.pt <= 15 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.2) return 0.9869;
    if (a.pt > 10 && a.pt <= 15 && fabs(a.eta) >= 1.2 && fabs(a.eta) < 2.1) return 0.9927;
    if (a.pt > 15 && a.pt <= 20 && fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8) return 0.9644;
    if (a.pt > 15 && a.pt <= 20 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.2) return 0.9800;
    if (a.pt > 15 && a.pt <= 20 && fabs(a.eta) >= 1.2 && fabs(a.eta) < 2.1) return 0.9961;
    if (a.pt > 20 && fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8) return 0.9884;
    if (a.pt > 20 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.2) return 0.9884;
    if (a.pt > 20 && fabs(a.eta) >= 1.2 && fabs(a.eta) < 2.1) return 0.9941;
    if (a.pt < 10 || a.pt >= 100 || fabs(a.eta) >= 2.1) return 1.000;
    return 1.0;
}

double Cor_ID_Iso_Mu_Tight_2012_53X(myobject const& a) {
    if (a.pt > 17 && a.pt < 20 && fabs(a.eta) < 1.6) return 0.997*0.930;
    if (a.pt > 17 && a.pt < 20 && fabs(a.eta) > 1.6 && fabs(a.eta) < 2.1) return 0.986*0.929;
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) < 1.6) return 0.995*0.977;
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) > 1.6 && fabs(a.eta) < 2.1) return 0.986*0.984;
    if (a.pt > 30 && fabs(a.eta) < 1.6) return 1.030*1.010;
    if (a.pt > 30 && fabs(a.eta) > 1.6 && fabs(a.eta) < 2.1) return 0.990*0.997;
    return 1.0;
}

double Cor_ID_Iso_Ele_Loose_2012_53X(myobject const& a) {
    if (a.pt > 10 && a.pt <= 15 && fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8) return 0.7893;
    if (a.pt > 10 && a.pt <= 15 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.479) return 0.7952;
    if (a.pt > 10 && a.pt <= 15 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.3) return 0.6519;
    if (a.pt > 15 && a.pt <= 20 && fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8) return 0.8506;
    if (a.pt > 15 && a.pt <= 20 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.479) return 0.8661;
    if (a.pt > 15 && a.pt <= 20 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.3) return 0.7816;
    if (a.pt > 20 && fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8) return 0.9534;
    if (a.pt > 20 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.479) return 0.9481;
    if (a.pt > 20 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.3) return 0.9378;
    if (a.pt < 10 || a.pt >= 100 || fabs(a.eta) >= 2.3) return 1.000;
    
    return 1.0;
}

double Cor_ID_Iso_Ele_Tight_2012_53X(myobject const& a) {
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) < 1.479) return 0.9126*0.9600;
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) > 1.479 && fabs(a.eta) < 2.1) return 0.8507*0.9677;
    if (a.pt > 30 && fabs(a.eta) < 1.479) return 0.9567*0.9858;
    if (a.pt > 30 && fabs(a.eta) > 1.479 && fabs(a.eta) < 2.1) return 0.9239*0.9942;
    return 1.0;
}




Double_t Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC(Double_t eta1, Double_t eta2) {
  if( eta1>=-2.4 && eta1<-2.1) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.962112;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.965597;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.96959;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.973002;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.973675;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.972823;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.954265;
    else if( eta2>=-0.2 && eta2<0) return 0.973641;
    else if( eta2>=0 && eta2<0.2) return 0.97504;
    else if( eta2>=0.2 && eta2<0.3) return 0.963274;
    else if( eta2>=0.3 && eta2<0.6) return 0.970394;
    else if( eta2>=0.6 && eta2<0.9) return 0.978703;
    else if( eta2>=0.9 && eta2<1.2) return 0.970745;
    else if( eta2>=1.2 && eta2<1.6) return 0.969005;
    else if( eta2>=1.6 && eta2<2.1) return 0.975571;
    else if( eta2>=2.1 && eta2<=2.4) return 0.967735;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-2.1 && eta1<-1.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.965597;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.969054;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.973061;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.976463;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.977139;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.97627;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.957652;
    else if( eta2>=-0.2 && eta2<0) return 0.977096;
    else if( eta2>=0 && eta2<0.2) return 0.978494;
    else if( eta2>=0.2 && eta2<0.3) return 0.966688;
    else if( eta2>=0.3 && eta2<0.6) return 0.973831;
    else if( eta2>=0.6 && eta2<0.9) return 0.982183;
    else if( eta2>=0.9 && eta2<1.2) return 0.974204;
    else if( eta2>=1.2 && eta2<1.6) return 0.972479;
    else if( eta2>=1.6 && eta2<2.1) return 0.979062;
    else if( eta2>=2.1 && eta2<=2.4) return 0.971235;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-1.6 && eta1<-1.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.96959;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.973061;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.977087;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.980499;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.981178;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.980302;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.961609;
    else if( eta2>=-0.2 && eta2<0) return 0.981132;
    else if( eta2>=0 && eta2<0.2) return 0.982535;
    else if( eta2>=0.2 && eta2<0.3) return 0.970681;
    else if( eta2>=0.3 && eta2<0.6) return 0.977852;
    else if( eta2>=0.6 && eta2<0.9) return 0.986242;
    else if( eta2>=0.9 && eta2<1.2) return 0.978231;
    else if( eta2>=1.2 && eta2<1.6) return 0.976504;
    else if( eta2>=1.6 && eta2<2.1) return 0.98311;
    else if( eta2>=2.1 && eta2<=2.4) return 0.975251;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-1.2 && eta1<-0.9) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.973002;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.976463;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.980499;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.98392;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.9846;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.98372;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.964962;
    else if( eta2>=-0.2 && eta2<0) return 0.984554;
    else if( eta2>=0 && eta2<0.2) return 0.985961;
    else if( eta2>=0.2 && eta2<0.3) return 0.974066;
    else if( eta2>=0.3 && eta2<0.6) return 0.981262;
    else if( eta2>=0.6 && eta2<0.9) return 0.989682;
    else if( eta2>=0.9 && eta2<1.2) return 0.981645;
    else if( eta2>=1.2 && eta2<1.6) return 0.979914;
    else if( eta2>=1.6 && eta2<2.1) return 0.986547;
    else if( eta2>=2.1 && eta2<=2.4) return 0.978681;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.9 && eta1<-0.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.973675;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.977139;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.981178;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.9846;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.985281;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.9844;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.965629;
    else if( eta2>=-0.2 && eta2<0) return 0.985234;
    else if( eta2>=0 && eta2<0.2) return 0.986642;
    else if( eta2>=0.2 && eta2<0.3) return 0.974739;
    else if( eta2>=0.3 && eta2<0.6) return 0.98194;
    else if( eta2>=0.6 && eta2<0.9) return 0.990366;
    else if( eta2>=0.9 && eta2<1.2) return 0.982324;
    else if( eta2>=1.2 && eta2<1.6) return 0.980593;
    else if( eta2>=1.6 && eta2<2.1) return 0.98723;
    else if( eta2>=2.1 && eta2<=2.4) return 0.979358;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.6 && eta1<-0.3) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.972823;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.97627;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.980302;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.98372;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.9844;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.983518;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.964765;
    else if( eta2>=-0.2 && eta2<0) return 0.984352;
    else if( eta2>=0 && eta2<0.2) return 0.985759;
    else if( eta2>=0.2 && eta2<0.3) return 0.973866;
    else if( eta2>=0.3 && eta2<0.6) return 0.98106;
    else if( eta2>=0.6 && eta2<0.9) return 0.98948;
    else if( eta2>=0.9 && eta2<1.2) return 0.981446;
    else if( eta2>=1.2 && eta2<1.6) return 0.979718;
    else if( eta2>=1.6 && eta2<2.1) return 0.986352;
    else if( eta2>=2.1 && eta2<=2.4) return 0.9785;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.3 && eta1<-0.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.954265;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.957652;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.961609;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.964962;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.965629;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.964765;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.946369;
    else if( eta2>=-0.2 && eta2<0) return 0.965582;
    else if( eta2>=0 && eta2<0.2) return 0.966963;
    else if( eta2>=0.2 && eta2<0.3) return 0.955296;
    else if( eta2>=0.3 && eta2<0.6) return 0.962354;
    else if( eta2>=0.6 && eta2<0.9) return 0.970612;
    else if( eta2>=0.9 && eta2<1.2) return 0.962731;
    else if( eta2>=1.2 && eta2<1.6) return 0.961036;
    else if( eta2>=1.6 && eta2<2.1) return 0.967542;
    else if( eta2>=2.1 && eta2<=2.4) return 0.959834;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.2 && eta1<0) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.973641;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.977096;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.981132;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.984554;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.985234;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.984352;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.965582;
    else if( eta2>=-0.2 && eta2<0) return 0.985186;
    else if( eta2>=0 && eta2<0.2) return 0.986594;
    else if( eta2>=0.2 && eta2<0.3) return 0.974691;
    else if( eta2>=0.3 && eta2<0.6) return 0.981892;
    else if( eta2>=0.6 && eta2<0.9) return 0.990318;
    else if( eta2>=0.9 && eta2<1.2) return 0.982277;
    else if( eta2>=1.2 && eta2<1.6) return 0.980548;
    else if( eta2>=1.6 && eta2<2.1) return 0.987186;
    else if( eta2>=2.1 && eta2<=2.4) return 0.979323;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0 && eta1<0.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.97504;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.978494;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.982535;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.985961;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.986642;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.985759;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.966963;
    else if( eta2>=-0.2 && eta2<0) return 0.986594;
    else if( eta2>=0 && eta2<0.2) return 0.988005;
    else if( eta2>=0.2 && eta2<0.3) return 0.976085;
    else if( eta2>=0.3 && eta2<0.6) return 0.983295;
    else if( eta2>=0.6 && eta2<0.9) return 0.991734;
    else if( eta2>=0.9 && eta2<1.2) return 0.983682;
    else if( eta2>=1.2 && eta2<1.6) return 0.98195;
    else if( eta2>=1.6 && eta2<2.1) return 0.9886;
    else if( eta2>=2.1 && eta2<=2.4) return 0.98073;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.2 && eta1<0.3) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.963274;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.966688;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.970681;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.974066;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.974739;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.973866;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.955296;
    else if( eta2>=-0.2 && eta2<0) return 0.974691;
    else if( eta2>=0 && eta2<0.2) return 0.976085;
    else if( eta2>=0.2 && eta2<0.3) return 0.964308;
    else if( eta2>=0.3 && eta2<0.6) return 0.971432;
    else if( eta2>=0.6 && eta2<0.9) return 0.979769;
    else if( eta2>=0.9 && eta2<1.2) return 0.971814;
    else if( eta2>=1.2 && eta2<1.6) return 0.970103;
    else if( eta2>=1.6 && eta2<2.1) return 0.976671;
    else if( eta2>=2.1 && eta2<=2.4) return 0.968895;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.3 && eta1<0.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.970394;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.973831;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.977852;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.981262;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.98194;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.98106;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.962354;
    else if( eta2>=-0.2 && eta2<0) return 0.981892;
    else if( eta2>=0 && eta2<0.2) return 0.983295;
    else if( eta2>=0.2 && eta2<0.3) return 0.971432;
    else if( eta2>=0.3 && eta2<0.6) return 0.978608;
    else if( eta2>=0.6 && eta2<0.9) return 0.987007;
    else if( eta2>=0.9 && eta2<1.2) return 0.978993;
    else if( eta2>=1.2 && eta2<1.6) return 0.97727;
    else if( eta2>=1.6 && eta2<2.1) return 0.983888;
    else if( eta2>=2.1 && eta2<=2.4) return 0.976057;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.6 && eta1<0.9) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.978703;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.982183;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.986242;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.989682;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.990366;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.98948;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.970612;
    else if( eta2>=-0.2 && eta2<0) return 0.990318;
    else if( eta2>=0 && eta2<0.2) return 0.991734;
    else if( eta2>=0.2 && eta2<0.3) return 0.979769;
    else if( eta2>=0.3 && eta2<0.6) return 0.987007;
    else if( eta2>=0.6 && eta2<0.9) return 0.995477;
    else if( eta2>=0.9 && eta2<1.2) return 0.987393;
    else if( eta2>=1.2 && eta2<1.6) return 0.985654;
    else if( eta2>=1.6 && eta2<2.1) return 0.992326;
    else if( eta2>=2.1 && eta2<=2.4) return 0.984415;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.9 && eta1<1.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.970745;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.974204;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.978231;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.981645;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.982324;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.981446;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.962731;
    else if( eta2>=-0.2 && eta2<0) return 0.982277;
    else if( eta2>=0 && eta2<0.2) return 0.983682;
    else if( eta2>=0.2 && eta2<0.3) return 0.971814;
    else if( eta2>=0.3 && eta2<0.6) return 0.978993;
    else if( eta2>=0.6 && eta2<0.9) return 0.987393;
    else if( eta2>=0.9 && eta2<1.2) return 0.979374;
    else if( eta2>=1.2 && eta2<1.6) return 0.977647;
    else if( eta2>=1.6 && eta2<2.1) return 0.984264;
    else if( eta2>=2.1 && eta2<=2.4) return 0.976411;
    else return 0.;
    return 0.;
  }
  else if( eta1>=1.2 && eta1<1.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.969005;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.972479;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.976504;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.979914;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.980593;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.979718;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.961036;
    else if( eta2>=-0.2 && eta2<0) return 0.980548;
    else if( eta2>=0 && eta2<0.2) return 0.98195;
    else if( eta2>=0.2 && eta2<0.3) return 0.970103;
    else if( eta2>=0.3 && eta2<0.6) return 0.97727;
    else if( eta2>=0.6 && eta2<0.9) return 0.985654;
    else if( eta2>=0.9 && eta2<1.2) return 0.977647;
    else if( eta2>=1.2 && eta2<1.6) return 0.975921;
    else if( eta2>=1.6 && eta2<2.1) return 0.982521;
    else if( eta2>=2.1 && eta2<=2.4) return 0.974662;
    else return 0.;
    return 0.;
  }
  else if( eta1>=1.6 && eta1<2.1) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.975571;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.979062;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.98311;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.986547;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.98723;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.986352;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.967542;
    else if( eta2>=-0.2 && eta2<0) return 0.987186;
    else if( eta2>=0 && eta2<0.2) return 0.9886;
    else if( eta2>=0.2 && eta2<0.3) return 0.976671;
    else if( eta2>=0.3 && eta2<0.6) return 0.983888;
    else if( eta2>=0.6 && eta2<0.9) return 0.992326;
    else if( eta2>=0.9 && eta2<1.2) return 0.984264;
    else if( eta2>=1.2 && eta2<1.6) return 0.982521;
    else if( eta2>=1.6 && eta2<2.1) return 0.989173;
    else if( eta2>=2.1 && eta2<=2.4) return 0.981267;
    else return 0.;
    return 0.;
  }
  else if( eta1>=2.1 && eta1<=2.4) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.967735;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.971235;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.975251;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.978681;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.979358;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.9785;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.959834;
    else if( eta2>=-0.2 && eta2<0) return 0.979323;
    else if( eta2>=0 && eta2<0.2) return 0.98073;
    else if( eta2>=0.2 && eta2<0.3) return 0.968895;
    else if( eta2>=0.3 && eta2<0.6) return 0.976057;
    else if( eta2>=0.6 && eta2<0.9) return 0.984415;
    else if( eta2>=0.9 && eta2<1.2) return 0.976411;
    else if( eta2>=1.2 && eta2<1.6) return 0.974662;
    else if( eta2>=1.6 && eta2<2.1) return 0.981267;
    else if( eta2>=2.1 && eta2<=2.4) return 0.973391;
    else return 0.;
    return 0.;
  }
  else return 0.;
  return 0.;
}

double Corr_trigger_Mu17_Mu8_2011(myobject const& a1, myobject const& a2 )
{
	return Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC(a1.eta,a2.eta);
}

double Cor_Total_Mu_Loose_2011(myobject const& a) {
    double cor_Id_Iso_Mu = Cor_ID_Iso_Mu_Loose_2011(a);
    //double cor_Trg_Mu = Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC(a);

    if (isMC)
        return cor_Id_Iso_Mu;
    else
        return 1.0;
}

double Cor_Total_Mu_Tight_2011(myobject const& a) {
    double cor_Id_Iso_Mu = Cor_ID_Iso_Mu_Tight_2011(a);
    //double cor_Trg_Mu = Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC(a);

    if (isMC)
        return cor_Id_Iso_Mu;
    else
        return 1.0;
}

double Cor_Total_Mu_Tight_2012(myobject const& a) {
    double cor_Id_Iso_Mu = Cor_ID_Iso_Mu_Tight_2012(a);
    //double cor_Trg_Mu = Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC(a);

    if (isMC)
        return cor_Id_Iso_Mu;
    else
        return 1.0;
}

double Cor_Total_Mu_Loose_2012(myobject const& a) {
    double cor_Id_Iso_Mu = Cor_ID_Iso_Mu_Loose_2012(a);
    //double cor_Trg_Mu = Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC(a);

    if (isMC)
        return cor_Id_Iso_Mu;
    else
        return 1.0;
}

double Cor_Total_Mu_Loose_2012_53X(myobject const& a) {
    double cor_Id_Iso_Mu = Cor_ID_Iso_Mu_Loose_2012_53X(a);
    //double cor_Trg_Mu = Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC(a);

    if (isMC)
        return cor_Id_Iso_Mu;
    else
        return 1.0;
}




