#ifndef __MVAEVALUATOR_H__
#define __MVAEVALUATOR_H__

#include <TMVA/Reader.h>
using namespace std;

class MVAEvaluator
{
public:
  MVAEvaluator(std::string);//const char* data_era);

  double getQCDLeadingElectron(double lepPt, double jetPt, unsigned int nJets20) const;
  double getQCDSubleadingElectron(double lepPt, double jetPt, unsigned int nJets20) const;
  double getWJetsLeadingElectron(double lepPt, double jetPt, unsigned int nJets20) const;
  double getWJetsSubleadingElectron(double lepPt, double jetPt, unsigned int nJets20) const;

protected:

  TMVA::Reader* qcd_leading_electron; 
  TMVA::Reader* qcd_subleading_electron; 
  TMVA::Reader* wjets_leading_electron; 
  TMVA::Reader* wjets_subleading_electron; 

  mutable float leptonPt_;
  mutable float jetPt_;
  mutable float nJets20_;
};

#endif // _MVAEVALUATOR_H_                           
