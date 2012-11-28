#!/bin/bash

# Script to prepare input files for SFrame analysis at ULB cluster. During its run it also checks the accessibility and readability of files and computes the total number of events.
# Prerequisities: 1) valid grid proxy (voms-proxy-init --voms cms:/cms/becms)  2) Set-up ROOT and SFrame environments

# Usage: source MakeSFInputFile.sh <directory with input ntuples> <name of output file with SFrame input>
# e.g. 
# source MakeSFInputFile.sh /pnfs/iihe/cms/store/user/jez/ZHTo2TauAna_53x_HToTauTau-140 53x_HToTauTau-140
#
# The result would be 53x_HToTauTau-140_input.xml containit config snippet that can be included to SFrame config file 

# Important parameters: names of ntuples (without suffix), server name and name of the tree inside ntuples

touch temp_input.1
rm -f temp_input.*

input_data=`echo $1`
output_name=`echo $2`
num_files=${3}
config_name=${4}

touch Prepare_${output_name}.sh
rm -f Prepare_${output_name}.sh

echo "touch Run_${output_name}.sh "  > Prepare_${output_name}.sh
echo "rm -f Run_${output_name}.sh " >> Prepare_${output_name}.sh
echo "touch Run_${output_name}.sh " >> Prepare_${output_name}.sh

ls ${input_data} | sort > temp_input.1
sed -i 's/\///g' temp_input.1
#more temp_input.1 | tr '/' '' > temp_input.2

more temp_input.1 |while read line
do
  file=`echo $line`
  echo "source PrepareJobs.sh ${input_data}/${file} ${output_name}_${file} ${num_files} ${config_name}" >> Prepare_${output_name}.sh
  echo "echo \"./SubmitAll_${output_name}_${file}.sh\" >> Run_${output_name}.sh" >> Prepare_${output_name}.sh
done
#source PrepareJobs.sh /pnfs/iihe/cms/store/user/jez/ZHttNtuples/53X/MC/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/ test 50 Analysis_config_T2_MC_53.xml

echo "chmod +x Run_${output_name}.sh " >> Prepare_${output_name}.sh
echo "echo \"To run all execute ./Run_${output_name}.sh\" " >> Prepare_${output_name}.sh

chmod +x Prepare_${output_name}.sh
echo "To prepare jobs do ./Prepare_${output_name}.sh"

rm -f temp_input*