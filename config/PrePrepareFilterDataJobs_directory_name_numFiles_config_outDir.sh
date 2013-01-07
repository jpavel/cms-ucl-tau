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

time=`date "+%Y%m%d"`
input_data=`echo $1`
output_name="FILTER_"$2
num_files=${3}
config_name=${4}
outDir=${5}

touch Prepare_${output_name}.sh
rm -f Prepare_${output_name}.sh

echo "touch Run_${output_name}.sh "  > Prepare_${output_name}.sh
echo "rm -f Run_${output_name}.sh " >> Prepare_${output_name}.sh
echo "touch Run_${output_name}.sh " >> Prepare_${output_name}.sh
echo "touch Show_${output_name}.sh " >> Prepare_${output_name}.sh
echo "rm -f Show_${output_name}.sh " >> Prepare_${output_name}.sh
echo "touch Show_${output_name}.sh " >> Prepare_${output_name}.sh
echo "touch Merge_${output_name}.sh "  > Prepare_${output_name}.sh
echo "rm -f Merge_${output_name}.sh " >> Prepare_${output_name}.sh
echo "touch Merge_${output_name}.sh " >> Prepare_${output_name}.sh
echo "touch Clean_${output_name}.sh "  > Prepare_${output_name}.sh
echo "rm -f Clean_${output_name}.sh " >> Prepare_${output_name}.sh
echo "touch Clean_${output_name}.sh " >> Prepare_${output_name}.sh

ls ${input_data} | sort > temp_input.1
sed -i 's/\///g' temp_input.1
#more temp_input.1 | tr '/' '' > temp_input.2
more temp_input.1 |while read line
do
  file=`echo $line`
  srmmkdir $STORAGE${outDir}/${file}
  echo "./PrepareJobs_filter.sh ${input_data}/${file} ${output_name}_${file} 2 ${config_name} ${outDir}/${file}" >> Prepare_${output_name}.sh
#  echo "source PrepareJobs.sh ${input_data}/${file} ${output_name}_${file} ${num_files} ${config_name}" >> Prepare_${output_name}.sh
  echo "echo \"./${time}_${output_name}_${file}_SubmitAll.sh\" >> Run_${output_name}.sh" >> Prepare_${output_name}.sh
  echo "echo \"source ShowResults_filter.sh ${output_name}_${file}\" >> Show_${output_name}.sh" >> Prepare_${output_name}.sh
  echo "echo \"source MergeOutput_filter.sh ${output_name}_${file} results/${output_name}_${file}\" >> Merge_${output_name}.sh" >> Prepare_${output_name}.sh
  echo "echo \"source CleanResults.sh ${output_name}_${file}\" >> Clean_${output_name}.sh" >> Prepare_${output_name}.sh
done
#source PrepareJobs.sh /pnfs/iihe/cms/store/user/jez/ZHttNtuples/53X/MC/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/ test 50 Analysis_config_T2_MC_53.xml

echo "chmod +x Run_${output_name}.sh " >> Prepare_${output_name}.sh
echo "echo \"To run all execute ./Run_${output_name}.sh\" " >> Prepare_${output_name}.sh

chmod +x Prepare_${output_name}.sh
echo "To prepare jobs do ./Prepare_${output_name}.sh"

rm -f temp_input*