# Wrapper script for running analysis defined in Analysis_config_T2.xml for a data defined in ${1}_input.xml, where ${1} is command line parameter. 
# Example usage: source run_anal.sh 53x_HToTauTau-140_1  (this will run over files defined in 53x_HToTauTau-140_1_input.xml and produce outputfile 53x_HToTauTau-140_1.output.root
#cp ${1}_input.xml input.xml
sframe_main Analysis_config_T2.xml
mv Analysis.Data1.Reco.root ${1}.output.root
rm -f input.xml
