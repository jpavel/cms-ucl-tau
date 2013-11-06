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
          // *** 2012 53X *** //
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

double Cor_ID_Iso_Mu_Loose_2012_53X(myobject const& a) {
       return 1;
}
double Cor_ID_Iso_Mu_Loose_2011(myobject const& a) {
       return 1;
}
double Cor_Trg_Mu_Loose_2011(myobject const& a) {
       return 1;
}
double Unc_ID_Iso_Mu_Loose_2012_53X(myobject const& a) {
       return 1;
}
double Cor_Trg_Mu_2012_53X(myobject const& a) {
       return 1;
}
double Unc_Trg_Mu_2012_53X(myobject const& a) {
       return 1;
}

double Corr_Trg_Mu_2012_53X(myobject const& a) {
       return 1;
}
double Corr_Trg_Mu_2011(myobject const& a) {
       return 1;
}
double Unc_ID_Iso_Ele_Loose_2012_53X(myobject const& a) {
       return 1;
}
double Unc_Trg_Ele_2012_53X(myobject const& a) {
       return 1;
}
double Corr_Trg_Ele_2011(myobject const& a) {
       return 1;
}
double Unc_ID_Iso_Mu_Tight_2012_53X(myobject const& a) {
       return 1;
}
double Cor_ID_Iso_Mu_Tight_2011(myobject const& a) {
       return 1;
}
double Unc_ID_Iso_Ele_Tight_2012_53X(myobject const& a) {
       return 1;
}
double Cor_ID_Iso_Ele_Tight_2011(myobject const& a) {
       return 1;
}
double Cor_ID_Iso_Ele_Loose_2011(myobject const& a) {
       return 1;
}

double Cor_ID_Iso_Mu_Tight_2012_53X(myobject const& a) {
       return 1;
}

double Corr_Trg_Ele_2012_53X(myobject const& a)
{
    if (a.pt >= 10 && a.pt < 15 && fabs(a.eta) >= 0 && fabs(a.eta)<0.8) return 0.9548;
    if (a.pt >= 10 && a.pt < 15 && 0.8 <= fabs(a.eta) && fabs(a.eta) < 1.5) return 0.9015;
    if (a.pt >= 10 && a.pt < 15 && 1.5 <= fabs(a.eta) && fabs(a.eta) < 2.3) return 0.9017;
    if (a.pt >= 15 && a.pt < 20 && fabs(a.eta) >= 0 && fabs(a.eta) < 0.8) return 0.9830;
    if (a.pt >= 15 && a.pt < 20 && 0.8 <= fabs(a.eta) && fabs(a.eta) < 1.5) return 0.9672;
    if (a.pt >= 15 && a.pt < 20 && 1.5 <= fabs(a.eta) && fabs(a.eta) < 2.3) return 0.9463;
    if (a.pt >= 20 && a.pt < 25 && fabs(a.eta)>=0 && fabs(a.eta) < 0.8) return 0.9707;
    if (a.pt >= 20 && a.pt < 25 && 0.8 <= fabs(a.eta) && fabs(a.eta) < 1.5) return 0.9731;
    if (a.pt >= 20 && a.pt < 25 && fabs(a.eta)>=1.5 && fabs(a.eta) < 2.3) return 0.9691;
    if (a.pt >= 25 && a.pt < 30 && fabs(a.eta)>=0 && fabs(a.eta) < 0.8) return 0.9768;
    if (a.pt >= 25 && a.pt < 30 && 0.8 <= fabs(a.eta) && fabs(a.eta) < 1.5) return 0.9870;
    if (a.pt >= 25 && a.pt < 30 && fabs(a.eta)>=1.5 && fabs(a.eta) < 2.3) return 0.9727;
    if (a.pt >= 30 && a.pt < 35 && fabs(a.eta)>=0 && fabs(a.eta) < 0.8) return 1.0047;
    if (a.pt >= 30 && a.pt < 35 && 0.8 <= fabs(a.eta) && fabs(a.eta) < 1.5) return 0.9891;
    if (a.pt >= 30 && a.pt < 35 && fabs(a.eta)>=1.5 && fabs(a.eta) < 2.3) return 0.9858;
    if (a.pt >= 35 && fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8) return 1.0063;
    if (a.pt >= 35 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.5) return 1.0047;
    if (a.pt >= 35 && fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.3) return 1.0015;
    return 1.0;
}

double Cor_ID_Iso_Ele_Loose_2012_53X(myobject const& a) {
	if(a.pt > 10.0 && a.pt <= 15.0 	&& fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8 ) return 0.7654;
	if(a.pt > 10.0 && a.pt <= 15.0 	&& fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.5 ) return 0.7693;
	if(a.pt > 10.0 && a.pt <= 15.0 	&& fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.3 ) return 0.5719;
	if(a.pt > 15.0 && a.pt <= 20.0 	&& fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8 ) return 0.8394;
	if(a.pt > 15.0 && a.pt <= 20.0 	&& fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.5 ) return 0.8457;
	if(a.pt > 15.0 && a.pt <= 20.0 	&& fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.3 ) return 0.7024;
	if(a.pt > 20.0 && a.pt <= 25.0 	&& fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8 ) return 0.8772;
	if(a.pt > 20.0 && a.pt <= 25.0 	&& fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.5 ) return 0.8530;
	if(a.pt > 20.0 && a.pt <= 25.0 	&& fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.3 ) return 0.7631;
	if(a.pt > 25.0 && a.pt <= 30.0 	&& fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8 ) return 0.9006;
	if(a.pt > 25.0 && a.pt <= 30.0 	&& fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.5 ) return 0.8874;
	if(a.pt > 25.0 && a.pt <= 30.0 	&& fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.3 ) return 0.8092;
	if(a.pt > 30.0 && a.pt <= 35.0 	&& fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8 ) return 0.9261;
	if(a.pt > 30.0 && a.pt <= 35.0 	&& fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.5 ) return 0.9199;
	if(a.pt > 30.0 && a.pt <= 35.0 	&& fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.3 ) return 0.8469;
	if(a.pt > 35.0 && fabs(a.eta) >= 0.0 && fabs(a.eta) < 0.8 ) return 0.9514;
	if(a.pt > 35.0 && fabs(a.eta) >= 0.8 && fabs(a.eta) < 1.5 ) return 0.9445;
	if(a.pt > 35.0 && fabs(a.eta) >= 1.5 && fabs(a.eta) < 2.3 ) return 0.9078;
	return 1.0;
}

double Cor_ID_Iso_Ele_Tight_2012_53X(myobject const& a) {
	if(a.pt > 24.0 && a.pt < 30.0 && fabs(a.eta) < 1.479 ) return 0.8999*0.9417;
	if(a.pt > 24.0 && a.pt < 30.0 && fabs(a.eta) > 1.479 && fabs(a.eta)< 2.1 ) return 0.7945*0.9417;
	if(a.pt > 30.0 && fabs(a.eta) < 1.479 ) return 0.9486*0.9804;
	if(a.pt > 30.0 && fabs(a.eta) > 1.479 && fabs(a.eta)< 2.1 ) return 0.8866*0.9900;
        return 1;	
}

