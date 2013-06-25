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

double Unc_ID_Iso_Mu_Loose_2011(myobject const& a) {
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) < 1.5) return 0.0141;
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.1) return 0.0177;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) < 1.5) return 0.0065;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.1) return 0.0100;
    if (a.pt > 20 && fabs(a.eta) < 1.5) return 0.0004;
    if (a.pt > 20 && fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.1) return 0.0010;
    if (a.pt < 10 || a.pt >= 100 || fabs(a.eta) >= 2.10) return 0.000;
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

double Unc_ID_Iso_Ele_Loose_2011(myobject const& a) {
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) < 1.479) return 0.0056;
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.1) return 0.1644;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) < 1.479) return 0.0670;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.1) return 0.0681;
    if (a.pt >= 20 && fabs(a.eta) < 1.479) return 0.0021;
    if (a.pt >= 20 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.1) return 0.0020;
    if (a.pt < 10 || a.pt >= 100 || fabs(a.eta) >= 2.1) return 0.000;
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
    if (a.pt >= 10 && a.pt < 20 && fabs(a.eta) < 0.8) return 0.987404*0.981105;
    if (a.pt >= 10 && a.pt < 20 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.976942*0.980886;
    if (a.pt >= 10 && a.pt < 20 && 1.2 <= fabs(a.eta) ) return 0.9931*0.998097; 
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) < 0.8) return 0.985313*0.993823;
    if (a.pt >= 20 && a.pt < 30 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.981847*1.0;
    if (a.pt >= 20 && a.pt < 30 && 1.2 <= fabs(a.eta) ) return 0.989903*0.999919;
    if (a.pt >= 30 && fabs(a.eta) < 0.8) return 0.985675*0.999024;
    if (a.pt >= 30 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.980492*0.999228;
    if (a.pt >= 30 && 1.2 <= fabs(a.eta) ) return 0.990018*0.998869;
    return 1.0;
}

double Unc_ID_Iso_Mu_Loose_2012_53X(myobject const& a) {
    if (a.pt >= 10 && a.pt < 20 && fabs(a.eta) < 0.8) return 0.0069793784;
    if (a.pt >= 10 && a.pt < 20 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.0035790204;
    if (a.pt >= 10 && a.pt < 20 && 1.2 <= fabs(a.eta) ) return 0.0022314511; 
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) < 0.8) return 0.0008508019;
    if (a.pt >= 20 && a.pt < 30 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.0012387535;
    if (a.pt >= 20 && a.pt < 30 && 1.2 <= fabs(a.eta) ) return 0.0007883148;
    if (a.pt >= 30 && fabs(a.eta) < 0.8) return 0.0001515083;
    if (a.pt >= 30 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.0001459491;
    if (a.pt >= 30 && 1.2 <= fabs(a.eta) ) return 0.0000902769;
    return 1.0;
}

double Cor_ID_Iso_Mu_Tight_2012_53X(myobject const& a) {
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) < 0.8) return 0.9818*0.9494;
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.2) return 0.9829*0.9835;
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) >= 1.2 && fabs(a.eta) < 2.1) return 0.9869*0.9923;
    if (a.pt > 30 && fabs(a.eta) < 0.8) return 0.9852*0.9883;
    if (a.pt > 30 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.2) return 0.9852*0.9937;
    if (a.pt > 30 && fabs(a.eta) >= 1.2 && fabs(a.eta) < 2.1) return 0.9884*0.9996;
    return 1.0;
}

double Unc_ID_Iso_Mu_Tight_2012_53X(myobject const& a) {
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) < 0.8) return 0.0015473155;
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.2) return 0.0021558896;
    if (a.pt > 20 && a.pt < 30 && fabs(a.eta) >= 1.2 && fabs(a.eta) < 2.1) return 0.0014589363;
    if (a.pt > 30 && fabs(a.eta) < 0.8) return 0.0003116458;
    if (a.pt > 30 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.2) return 0.0004413577;
    if (a.pt > 30 && fabs(a.eta) >= 1.2 && fabs(a.eta) < 2.1) return 0.0005042079;
    return 1.0;
}

double Cor_ID_Iso_Ele_Loose_2012_53X(myobject const& a) {
    if (a.pt >= 10 && a.pt < 20 && fabs(a.eta) >= 0 && fabs(a.eta)<1.479) return 0.9794*0.970332;
    if (a.pt >= 10 && a.pt < 20 && 1.479 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.942182*0.984779;
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) >= 0 && fabs(a.eta)<1.479) return 0.955022*0.987348;
    if (a.pt >= 20 && a.pt < 30 && 1.479 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.960961*0.99015;
    if (a.pt >= 30 && fabs(a.eta) >= 0 && fabs(a.eta)<1.479) return 0.964001*0.998837;
    if (a.pt >= 30 && 1.479 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.970416*0.999246;
    return 1.0;
}

double Unc_ID_Iso_Ele_Loose_2012_53X(myobject const& a) {
    if (a.pt >= 10 && a.pt < 20 && fabs(a.eta) >= 0 && fabs(a.eta)<1.479) return 0.0060146013;
    if (a.pt >= 10 && a.pt < 20 && 1.479 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.0149124752;
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) >= 0 && fabs(a.eta)<1.479) return 0.0025410892;
    if (a.pt >= 20 && a.pt < 30 && 1.479 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.0022000352;
    if (a.pt >= 30 && fabs(a.eta) >= 0 && fabs(a.eta)<1.479) return 0.0003105562;
    if (a.pt >= 30 && 1.479 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.0006458909;
    return 1.0;
}

double Cor_ID_Iso_Ele_Tight_2012_53X(myobject const& a) {
    if (a.pt >= 24 && a.pt < 30 && fabs(a.eta) < 1.479) return 0.8999*0.9417;
    if (a.pt >= 24 && a.pt < 30 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.1) return 0.7945*0.9471;
    if (a.pt >= 30 && fabs(a.eta) < 1.479) return 0.9486*0.9804;
    if (a.pt >= 30 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.1) return 0.8866*0.9900;
    return 1.0;
}

double Unc_ID_Iso_Ele_Tight_2012_53X(myobject const& a) {
    if (a.pt >= 24 && a.pt < 30 && fabs(a.eta) < 1.479) return 0.0024076293;
    if (a.pt >= 24 && a.pt < 30 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.1) return 0.0059812828;
    if (a.pt >= 30 && fabs(a.eta) < 1.479) return 0.0004092583;
    if (a.pt >= 30 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.1) return 0.0002030847;
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

double Cor_Trg_Mu_Lead_2011(myobject const& a) {
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) < 1.44) return 0.982;
    if (a.pt >= 30 && a.pt < 50 && fabs(a.eta) < 1.44) return 0.982;
    if (a.pt >= 50 && a.pt < 100 && fabs(a.eta) < 1.44) return 0.982;
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 2.40) return 0.955;
    if (a.pt >= 30 && a.pt < 50 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 2.40) return 0.960;
    if (a.pt >= 50 && a.pt < 100 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 2.40) return 0.960;
    if (a.pt < 20 || a.pt >= 100 || fabs(a.eta) >= 2.40) return 1.000;
    return 1.0;
}

double Cor_Trg_Mu_SubLead_2011(myobject const& a) {
    if (a.pt >= 10 && a.pt < 20 && fabs(a.eta) < 1.44) return 0.989;
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) < 1.44) return 0.986;
    if (a.pt >= 30 && a.pt < 50 && fabs(a.eta) < 1.44) return 0.985;
    if (a.pt >= 50 && a.pt < 100 && fabs(a.eta) < 1.44) return 0.985;
    if (a.pt >= 10 && a.pt < 20 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 2.40) return 0.988;
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 2.40) return 0.981;
    if (a.pt >= 30 && a.pt < 50 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 2.40) return 0.980;
    if (a.pt >= 50 && a.pt < 100 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 2.40) return 0.976;
    if (a.pt < 10 || a.pt >= 100 || fabs(a.eta) >= 2.40) return 1.000;
    return 1.0;
}

double Cor_Trg_Ele_Lead_2011(myobject const& a) {
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) < 1.44) return 0.996;
    if (a.pt >= 30 && a.pt < 40 && fabs(a.eta) < 1.44) return 1.000;
    if (a.pt >= 40 && a.pt < 50 && fabs(a.eta) < 1.44) return 0.999;
    if (a.pt >= 50 && a.pt < 60 && fabs(a.eta) < 1.44) return 0.998;
    if (a.pt >= 60 && a.pt < 100 && fabs(a.eta) < 1.44) return 0.997;
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 1.57) return 1.012;
    if (a.pt >= 30 && a.pt < 40 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 1.57) return 1.009;
    if (a.pt >= 40 && a.pt < 50 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 1.57) return 0.998;
    if (a.pt >= 50 && a.pt < 60 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 1.57) return 0.968;
    if (a.pt >= 60 && a.pt < 100 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 1.57) return 0.991;
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) >= 1.57 && fabs(a.eta) < 2.50) return 0.987;
    if (a.pt >= 30 && a.pt < 40 && fabs(a.eta) >= 1.57 && fabs(a.eta) < 2.50) return 1.001;
    if (a.pt >= 40 && a.pt < 50 && fabs(a.eta) >= 1.57 && fabs(a.eta) < 2.50) return 1.000;
    if (a.pt >= 50 && a.pt < 60 && fabs(a.eta) >= 1.57 && fabs(a.eta) < 2.50) return 1.002;
    if (a.pt >= 60 && a.pt < 100 && fabs(a.eta) >= 1.57 && fabs(a.eta) < 2.50) return 0.989;
    if (a.pt < 20 || a.pt >= 100 || fabs(a.eta) >= 2.50) return 1.000;
    return 1.0;
}

double Cor_Trg_Ele_SubLead_2011(myobject const& a) {
    if (a.pt >= 10 && a.pt < 20 && fabs(a.eta) < 1.44) return 0.991;
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) < 1.44) return 0.997;
    if (a.pt >= 30 && a.pt < 40 && fabs(a.eta) < 1.44) return 0.999;
    if (a.pt >= 40 && a.pt < 50 && fabs(a.eta) < 1.44) return 0.998;
    if (a.pt >= 50 && a.pt < 60 && fabs(a.eta) < 1.44) return 0.999;
    if (a.pt >= 60 && a.pt < 100 && fabs(a.eta) < 1.44) return 0.998;
    if (a.pt >= 10 && a.pt < 20 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 1.57) return 0.994;
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 1.57) return 1.006;
    if (a.pt >= 30 && a.pt < 40 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 1.57) return 1.021;
    if (a.pt >= 40 && a.pt < 50 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 1.57) return 1.004;
    if (a.pt >= 50 && a.pt < 60 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 1.57) return 0.983;
    if (a.pt >= 60 && a.pt < 100 && fabs(a.eta) >= 1.44 && fabs(a.eta) < 1.57) return 1.047;
    if (a.pt >= 10 && a.pt < 20 && fabs(a.eta) >= 1.57 && fabs(a.eta) < 2.50) return 0.980;
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) >= 1.57 && fabs(a.eta) < 2.50) return 0.999;
    if (a.pt >= 30 && a.pt < 40 && fabs(a.eta) >= 1.57 && fabs(a.eta) < 2.50) return 1.000;
    if (a.pt >= 40 && a.pt < 50 && fabs(a.eta) >= 1.57 && fabs(a.eta) < 2.50) return 0.999;
    if (a.pt >= 50 && a.pt < 60 && fabs(a.eta) >= 1.57 && fabs(a.eta) < 2.50) return 1.003;
    if (a.pt >= 60 && a.pt < 100 && fabs(a.eta) >= 1.57 && fabs(a.eta) < 2.50) return 0.989;
    if (a.pt < 10 || a.pt >= 100 || fabs(a.eta) >= 2.50) return 1.000;
    return 1.0;
}

double Corr_Trg_Mu_2011(myobject const& a)
{
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) < 1.5) return 1.01;
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) > 1.5) return 1.03;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) < 1.5) return 0.99;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) > 1.5) return 1.07;
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) < 1.5) return 0.99;
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) > 1.5) return 1.4;
    if (a.pt > 30 && fabs(a.eta) < 1.5) return 0.992;
    if (a.pt > 30 && fabs(a.eta) > 1.5) return 1.06;
    return 1.0;
}

double Corr_Trg_Ele_2011(myobject const& a)
{
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) < 1.479) return 0.98;
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) > 1.479) return 0.97;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) < 1.479) return 1.00;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) > 1.479) return 1.05;
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) < 1.479) return 1.001;
    if (a.pt >= 20 && a.pt < 30 && fabs(a.eta) > 1.479) return 1.00;
    if (a.pt > 30 && fabs(a.eta) < 1.479) return 1.003;
    if (a.pt > 30 && fabs(a.eta) > 1.479) return 1.008;
    return 1.0;
}

double Corr_Trg_Mu_2012_53X(myobject const& a)
{
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) < 0.8) return 0.9829;
    if (a.pt >= 10 && a.pt < 15 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.9745;
    if (a.pt >= 10 && a.pt < 15 && 1.2 <= fabs(a.eta) &&  fabs(a.eta) < 1.6) return 0.9943;
    if (a.pt >= 10 && a.pt < 15 && 1.6 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.9158;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) < 0.8) return 0.9850;
    if (a.pt >= 15 && a.pt < 20 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.9852;
    if (a.pt >= 15 && a.pt < 20 && 1.2 <= fabs(a.eta) &&  fabs(a.eta) < 1.6) return 0.9743;
    if (a.pt >= 15 && a.pt < 20 && 1.6 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.9333;    
    if (a.pt >= 20 && a.pt < 25 && fabs(a.eta) < 0.8) return 0.9951;
    if (a.pt >= 20 && a.pt < 25 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.9610;
    if (a.pt >= 20 && a.pt < 25 && 1.2 <= fabs(a.eta) &&  fabs(a.eta) < 1.6) return 0.9716;
    if (a.pt >= 20 && a.pt < 25 && 1.6 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.9459;
    if (a.pt >= 25 && a.pt < 30 && fabs(a.eta) < 0.8) return 0.9869;
    if (a.pt >= 25 && a.pt < 30 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.9779;
    if (a.pt >= 25 && a.pt < 30 && 1.2 <= fabs(a.eta) &&  fabs(a.eta) < 1.6) return 0.9665;
    if (a.pt >= 25 && a.pt < 30 && 1.6 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.9501;
    if (a.pt >= 30 && a.pt < 35 && fabs(a.eta) < 0.8) return 0.9959;
    if (a.pt >= 30 && a.pt < 35 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.9881;
    if (a.pt >= 30 && a.pt < 35 && 1.2 <= fabs(a.eta) &&  fabs(a.eta) < 1.6) return 0.9932;
    if (a.pt >= 30 && a.pt < 35 && 1.6 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.9391;
    if (a.pt >= 35 && fabs(a.eta) < 0.8) return 0.9986;
    if (a.pt >= 35 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.9540;
    if (a.pt >= 35 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.6) return 0.9549;
    if (a.pt >= 35 && 1.6 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.9386;
    return 1.0;
}

double Unc_Trg_Mu_2012_53X(myobject const& a)
{
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) < 0.8) return 0.0058;
    if (a.pt >= 10 && a.pt < 15 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.0124;
    if (a.pt >= 10 && a.pt < 15 && 1.2 <= fabs(a.eta) &&  fabs(a.eta) < 1.6) return 0.0164;
    if (a.pt >= 10 && a.pt < 15 && 1.6 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.0176;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) < 0.8) return 0.0056;
    if (a.pt >= 15 && a.pt < 20 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.0171;
    if (a.pt >= 15 && a.pt < 20 && 1.2 <= fabs(a.eta) &&  fabs(a.eta) < 1.6) return 0.0179;
    if (a.pt >= 15 && a.pt < 20 && 1.6 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.0162;    
    if (a.pt >= 20 && a.pt < 25 && fabs(a.eta) < 0.8) return 0.0060;
    if (a.pt >= 20 && a.pt < 25 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.0116;
    if (a.pt >= 20 && a.pt < 25 && 1.2 <= fabs(a.eta) &&  fabs(a.eta) < 1.6) return 0.0141;
    if (a.pt >= 20 && a.pt < 25 && 1.6 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.0159;
    if (a.pt >= 25 && a.pt < 30 && fabs(a.eta) < 0.8) return 0.0074;
    if (a.pt >= 25 && a.pt < 30 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.0187;
    if (a.pt >= 25 && a.pt < 30 && 1.2 <= fabs(a.eta) &&  fabs(a.eta) < 1.6) return 0.0184;
    if (a.pt >= 25 && a.pt < 30 && 1.6 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.0251;
    if (a.pt >= 30 && a.pt < 35 && fabs(a.eta) < 0.8) return 0.0085;
    if (a.pt >= 30 && a.pt < 35 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.0227;
    if (a.pt >= 30 && a.pt < 35 && 1.2 <= fabs(a.eta) &&  fabs(a.eta) < 1.6) return 0.0271;
    if (a.pt >= 30 && a.pt < 35 && 1.6 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.0307;
    if (a.pt >= 35 && fabs(a.eta) < 0.8) return 0.0087;
    if (a.pt >= 35 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.2) return 0.0165;
    if (a.pt >= 35 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.6) return 0.0211;
    if (a.pt >= 35 && 1.6 <= fabs(a.eta) &&  fabs(a.eta) < 2.1) return 0.0209;
    return 1.0;
}

double Corr_Trg_Ele_2012_53X(myobject const& a)
{
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) >= 0 && fabs(a.eta)<0.8) return 0.9548;
    if (a.pt >= 10 && a.pt < 15 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.5) return 0.9015;
    if (a.pt >= 10 && a.pt < 15 && 1.5 <= fabs(a.eta) &&  fabs(a.eta) < 2.3) return 0.9017;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) >= 0 && fabs(a.eta) < 0.8) return 0.9830;
    if (a.pt >= 15 && a.pt < 20 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.5) return 0.9672;
    if (a.pt >= 15 && a.pt < 20 && 1.5 <= fabs(a.eta) &&  fabs(a.eta) < 2.3) return 0.9463;
    if (a.pt >= 20 && a.pt < 25 && fabs(a.eta)>=0 && fabs(a.eta) < 0.8) return 0.9707;
    if (a.pt >= 20 && a.pt < 25 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.5) return 0.9731;
    if (a.pt >= 20 && a.pt < 25 && fabs(a.eta)>=1.5 && fabs(a.eta) < 2.3) return 0.9691;
    if (a.pt >= 25 && a.pt < 30 && fabs(a.eta)>=0 && fabs(a.eta) < 0.8) return 0.9768;
    if (a.pt >= 25 && a.pt < 30 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.5) return 0.9870;
    if (a.pt >= 25 && a.pt < 30 && fabs(a.eta)>=1.5 && fabs(a.eta) < 2.3) return 0.9727;
	if (a.pt >= 30 && a.pt < 35 && fabs(a.eta)>=0 && fabs(a.eta) < 0.8) return 1.0047;
    if (a.pt >= 30 && a.pt < 35 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.5) return 0.9891;
    if (a.pt >= 30 && a.pt < 35 && fabs(a.eta)>=1.5 && fabs(a.eta) < 2.3) return 0.9858;
    if (a.pt >= 35 && fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8) return 1.0063;
    if (a.pt >= 35 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.5) return 1.0047;
    if (a.pt >= 35 && fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.3) return 1.0015;
    return 1.0;
}

double Unc_Trg_Ele_2012_53X(myobject const& a)
{
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) >= 0 && fabs(a.eta)<0.8) return 0.0197;
    if (a.pt >= 10 && a.pt < 15 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.5) return 0.0205;
    if (a.pt >= 10 && a.pt < 15 && 1.5 <= fabs(a.eta) &&  fabs(a.eta) < 2.3) return 0.0470;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) >= 0 && fabs(a.eta) < 0.8) return 0.0115;
    if (a.pt >= 15 && a.pt < 20 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.5) return 0.0113;
    if (a.pt >= 15 && a.pt < 20 && 1.5 <= fabs(a.eta) &&  fabs(a.eta) < 2.3) return 0.0212;
    if (a.pt >= 20 && a.pt < 25 && fabs(a.eta)>=0 && fabs(a.eta) < 0.8) return 0.0087;
    if (a.pt >= 20 && a.pt < 25 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.5) return 0.0083;
    if (a.pt >= 20 && a.pt < 25 && fabs(a.eta)>=1.5 && fabs(a.eta) < 2.3) return 0.0149;
    if (a.pt >= 25 && a.pt < 30 && fabs(a.eta)>=0 && fabs(a.eta) < 0.8) return 0.0084;
    if (a.pt >= 25 && a.pt < 30 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.5) return 0.0083;
    if (a.pt >= 25 && a.pt < 30 && fabs(a.eta)>=1.5 && fabs(a.eta) < 2.3) return 0.0162;
	if (a.pt >= 30 && a.pt < 35 && fabs(a.eta)>=0 && fabs(a.eta) < 0.8) return 0.0100;
    if (a.pt >= 30 && a.pt < 35 && 0.8 <= fabs(a.eta) &&  fabs(a.eta) < 1.5) return 0.0111;
    if (a.pt >= 30 && a.pt < 35 && fabs(a.eta)>=1.5 && fabs(a.eta) < 2.3) return 0.0112;
    if (a.pt >= 35 && fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8) return 0.0078;
    if (a.pt >= 35 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.5) return 0.0073;
    if (a.pt >= 35 && fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.3) return 0.0135;
    return 1.0;
// Abdollah's numbers...
//~ double Corr_Trg_Mu_2012_53X(myobject const& a) {
    //~ if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) < 0.8) return 0.9818;
    //~ if (a.pt >= 10 && a.pt < 15 && 0.8 <= fabs(a.eta) && fabs(a.eta) < 1.2) return 0.9713;
    //~ if (a.pt >= 10 && a.pt < 15 && 1.2 <= fabs(a.eta) && fabs(a.eta) < 2.1) return 0.9675;
    //~ if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) < 0.8) return 0.9781;
    //~ if (a.pt >= 15 && a.pt < 20 && 0.8 <= fabs(a.eta) && fabs(a.eta) < 1.2) return 0.9782;
    //~ if (a.pt >= 15 && a.pt < 20 && 1.2 <= fabs(a.eta) && fabs(a.eta) < 2.1) return 0.9587;
    //~ if (a.pt >= 20 && a.pt < 25 && fabs(a.eta) < 0.8) return 0.9873;
    //~ if (a.pt >= 20 && a.pt < 25 && 0.8 <= fabs(a.eta) && fabs(a.eta) < 1.2) return 0.9532;
    //~ if (a.pt >= 20 && a.pt < 25 && 1.2 <= fabs(a.eta) && fabs(a.eta) < 2.1) return 0.9605;
    //~ if (a.pt >= 25 && a.pt < 30 && fabs(a.eta) < 0.8) return 0.9755;
    //~ if (a.pt >= 25 && a.pt < 30 && 0.8 <= fabs(a.eta) && fabs(a.eta) < 1.2) return 0.9818;
    //~ if (a.pt >= 25 && a.pt < 30 && 1.2 <= fabs(a.eta) && fabs(a.eta) < 2.1) return 0.9632;
    //~ if (a.pt >= 30 && fabs(a.eta) < 0.8) return 0.9956;
    //~ if (a.pt >= 30 && 0.8 <= fabs(a.eta) && fabs(a.eta) < 1.2) return 0.9644;
    //~ if (a.pt >= 30 && 1.2 <= fabs(a.eta) && fabs(a.eta) < 2.1) return 0.9530;
    //~ return 1.0;
//~ }
//~ 
//~ double Corr_Trg_Ele_2012_53X(myobject const& a) {
    //~ if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) >= 0 && fabs(a.eta) < 0.8) return 0.9639;
    //~ if (a.pt >= 10 && a.pt < 15 && 0.8 <= fabs(a.eta) && fabs(a.eta) < 1.479) return 0.8898;
    //~ if (a.pt >= 10 && a.pt < 15 && 1.479 <= fabs(a.eta) && fabs(a.eta) < 2.3) return 0.9228;
    //~ if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) >= 0 && fabs(a.eta) < 0.8) return 0.9762;
    //~ if (a.pt >= 15 && a.pt < 20 && 0.8 <= fabs(a.eta) && fabs(a.eta) < 1.479) return 0.9647;
    //~ if (a.pt >= 15 && a.pt < 20 && 1.479 <= fabs(a.eta) && fabs(a.eta) < 2.3) return 0.9199;
    //~ if (a.pt >= 20 && a.pt < 25 && fabs(a.eta) >= 0 && fabs(a.eta) < 0.8) return 0.9683;
    //~ if (a.pt >= 20 && a.pt < 25 && 0.8 <= fabs(a.eta) && fabs(a.eta) < 1.479) return 0.9666;
    //~ if (a.pt >= 20 && a.pt < 25 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.3) return 0.9679;
    //~ if (a.pt >= 25 && a.pt < 30 && fabs(a.eta) >= 0 && fabs(a.eta) < 0.8) return 0.9756;
    //~ if (a.pt >= 25 && a.pt < 30 && 0.8 <= fabs(a.eta) && fabs(a.eta) < 1.479) return 0.9896;
    //~ if (a.pt >= 25 && a.pt < 30 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.3) return 0.9473;
    //~ if (a.pt > 30 && fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8) return 1.0035;
    //~ if (a.pt > 30 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.479) return 0.9977;
    //~ if (a.pt > 30 && fabs(a.eta) >= 1.479 && fabs(a.eta) < 2.3) return 0.9885;
    //~ return 1;
//~ }
}




