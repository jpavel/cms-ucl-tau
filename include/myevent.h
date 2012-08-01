#ifndef __MYEVENT_HH__
#define __MYEVENT_HH__
#include "TObject.h"
using namespace std;
#include <vector>
#include <map>
#include <utility>
#include "myobject.h"

class myevent : public TObject {
public:

    myevent() {
        ;
    }

    ~myevent() {
        ;
    }

    vector<myobject> RecPFJetsAK5;
    vector<myobject> RecPFJetsAK5_Up_SubTotal;
    vector<myobject> RecPFJetsAK5_Down_SubTotal;
    vector<myobject> RecPFJetsAK5_Up_Total;
    vector<myobject> RecPFJetsAK5_Down_Total;
    vector<myobject> RecGenParticle;
    vector<myobject> RecGenMet;
    vector<myobject> RecGenJet;
    vector<myobject> PreSelectedElectrons;
    vector<myobject> PreSelectedMuons;
    vector<myobject> PreSelectedHPSTaus;
//    vector<myobject> PreSelectedTaNCTaus;
//    vector<myobject> RecMet;
    vector<myobject> RecPFMet;
    vector<myobject> RectcMet;
//    vector<myobject> mettopology;
//    vector<myobject> mettopologyTower;
    vector<myobject> Vertex;

    map<string, int> HLT;

    unsigned int runNumber;
    unsigned int eventNumber;
    unsigned int lumiNumber;
    unsigned int HLT_DiElectron;
    unsigned int HLT_DiMuon;
    int PUInfo;
    int PUInfo_true;
    int PUInfo_Bunch0;
    double RhoCorr;
    double RhoCenNeutral;
double RhoCenCharged;
double RhoCenNeutralTight;
//double RhoCenCharged;

//%/afs/cern.ch/user/a/abdollah/scratch0/CMSSW_5_2_3_patch3/src/Analysis/NtupleProducer/src/Jet.cc:10:9: error: 'class myevent' has no member named 'RhoCenCharged'
///afs/cern.ch/user/a/abdollah/scratch0/CMSSW_5_2_3_patch3/src/Analysis/NtupleProducer/src/Jet.cc:12:9: error: 'class myevent' has no member named 'RhoCenNeutralTight'
///afs/cern.ch/user/a/abdollah/scratch0/CMSSW_5_2_3_patch3/src/Analysis/NtupleProducer/src/Jet.cc:60:12: error: 'class myevent' has no member named 'RhoCenCharged'
///afs/cern.ch/cms/slc5_amd64_gcc462/external/clhep/2.0.4.6/include/CLHEP/Units/PhysicalConstants.h: At global scope:

private:

    ClassDef(myevent, 1)
};
#endif
