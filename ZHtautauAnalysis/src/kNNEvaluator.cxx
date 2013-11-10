#include "../include/kNNEvaluator.h"

MVAEvaluator::MVAEvaluator(std::string data_era)//const char* data_era)
{
        if(data_era != "2012")
                throw std::runtime_error("Mauro kNN training only available for 2012 data");

        TMVA::Reader** readers[] = { &qcd_leading_electron, &qcd_subleading_electron, &wjets_leading_electron, &wjets_subleading_electron };
        const char* files[] = {
		"/storage/data/cms/store/user/lperrini/kNNEvaluator/ee_qcd_pt10_eid12Medium_h2taucuts020_electronInfo_k100.kNN.weights.xml",
		"/storage/data/cms/store/user/lperrini/kNNEvaluator/ee_qcd_pt10_eid12Tight_h2taucuts_electronInfo_k100.kNN.weights.xml",
		"/storage/data/cms/store/user/lperrini/kNNEvaluator/ee_wjetsNoZmass_pt10_eid12Medium_h2taucuts020_electronInfo_k100.kNN.weights.xml",
		"/storage/data/cms/store/user/lperrini/kNNEvaluator/ee_wjetsNoZmass_pt10_eid12Tight_h2taucuts_electronInfo_k100.kNN.weights.xml"
        };

        for(unsigned int i = 0; i < 4; ++i)
        {
                TMVA::Reader** reader = readers[i];
                *reader = new TMVA::Reader("Silent");

                // Register the variables with the reader
                (*reader)->AddVariable("electronJetPt", &jetPt_);
                (*reader)->AddVariable("electronPt", &leptonPt_);
                (*reader)->AddVariable("numJets20", &nJets20_);

                (*reader)->BookMVA("kNN", files[i]);
                std::cout << "Loaded Mauro kNN training from " << files[i] << std::endl;
        }
}

double MVAEvaluator::getQCDLeadingElectron(double lepPt, double jetPt, unsigned int nJets20) const
{
        jetPt_ = jetPt;
        leptonPt_ = lepPt;
        nJets20_ = nJets20;
        const double value = qcd_leading_electron->EvaluateMVA("kNN");
        return value;
}
double MVAEvaluator::getQCDSubleadingElectron(double lepPt, double jetPt, unsigned int nJets20) const
{
        jetPt_ = jetPt;
        leptonPt_ = lepPt;
        nJets20_ = nJets20;
        const double value = qcd_subleading_electron->EvaluateMVA("kNN");
        return value;
}

double MVAEvaluator::getWJetsLeadingElectron(double lepPt, double jetPt, unsigned int nJets20) const
{
        jetPt_ = jetPt;
        leptonPt_ = lepPt;
        nJets20_ = nJets20;
        const double value = wjets_leading_electron->EvaluateMVA("kNN");
        return value;
}

double MVAEvaluator::getWJetsSubleadingElectron(double lepPt, double jetPt, unsigned int nJets20) const
{
        jetPt_ = jetPt;
        leptonPt_ = lepPt;
        nJets20_ = nJets20;
        const double value = wjets_subleading_electron->EvaluateMVA("kNN");
        return value;
}

