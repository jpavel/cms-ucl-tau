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

if [ "${BASH_SOURCE[0]}" = "${0}" ]; then
  echo script not sourced! Exiting...
  exit 1
fi

if [ "${PWD##/localgrid/}" = "${PWD}" ]; then
    echo "Not in localgrid! It is not possible to submit to local queue unless you are in /localgrid directory! Exiting... "
    return 3
fi


if [ "$CMSSW_BASE" = "" ]; then
  echo \$CMSSW_BASE is NOT set! Exiting...
  return 1
fi

if [ $# -ne 5 ]; then
    echo "Wrong number of input arguments!"
    echo "Usage: source PrepareJobs_removeDuplicates_.sh <PNFSinput> <taskName> <filesPerJob> <configName> <resultsOutput>"
    echo "e.g. source PrepareJobs_removeDuplicates.sh /pnfs/iihe/cms/store/user/jez/ZHttNtuples/53X/Data/DoubleElectron_Run2012D-PromptReco-v1/ 20130514_DoubleElectron_Run2012C-24Aug2012-v1 50 Analysis_config_T2.xml results"
    return 2
fi

time=`date "+%Y%m%d"`
input_data=`echo $1`
output_name=${2}
num_files=${3}
config_name=${4}
results_dir=${5}

sframe_dir=$PWD
# input datasets settings
ntuple_name=output_Ntuples
srm_server=dcap://maite.iihe.ac.be
inTreeName=t

full_path=${srm_server}${input_data}/
touch full_path
rm -f full_path
echo "Full path to data is "${full_path}
echo ${full_path} >> full_path

touch ${output_name}_makeXML.sh
rm -f ${output_name}_*makeXML.sh


ls -1tr ${input_data} | grep root | sort > temp_input.1 
total=`more temp_input.1 | wc -l`
echo "Total number of input root files is" $total
counter=0

touch temp_input.1.1
touch temp_input.1.2

touch toKeep.list
rm -f toKeep.list
touch toKeep.list

touch ${output_name}_duplicates.list
rm -f ${output_name}_duplicates.list
touch ${output_name}_duplicates.list


#duplicate removal
for block in  `seq -s ' ' 1 ${total}`; do
    more temp_input.1 |  grep "_${block}_[0-9]\{1,\}_....root" > copies.list
    copies=`more copies.list | wc -l`
    toRemove=`expr $copies - 1`
    if [ $copies -gt 0 ]; then
      more copies.list | head -n ${toRemove} >> ${output_name}_duplicates.list
      more copies.list | tail -n 1 >> toKeep.list
    fi
    rm -f copies.list
done

rm -f temp_input.1
mv toKeep.list temp_input.1
total=`more temp_input.1 | wc -l`  #To update to the total number after the duplicate removal

more temp_input.1 |while read line
do
  file=`echo $line`
  echo "dccp ${full_path}${file} /scratch/${output_name}_input/" >> temp_input.1.1
  echo "/scratch/${output_name}_input/${file}" >> temp_input.1.2
done

echo "The full paths to all files are:"

rm -f temp_input.1
mv temp_input.1.1 temp_input.1

touch ${output_name}_SubmitAll.sh
rm -rf ${output_name}_SubmitAll.sh
touch ${output_name}_SubmitAll.sh

touch ${output_name}_ShowStatus.sh
rm -rf ${output_name}_ShowStatus.sh
touch ${output_name}_ShowStatus.sh

echo "source ShowStatus2.sh ${output_name} ${output_name} ${results_dir}" >>  ${output_name}_ShowStatus.sh
chmod +x ${output_name}_ShowStatus.sh

touch script2.sh
rm -f script2.sh
touch script2.sh

echo "cd "$CMSSW_BASE"/src" >> script2.sh
echo "eval \`scram runtime -sh\`" >> script2.sh
echo "cd SFrame" >> script2.sh
echo "source setup.sh" >> script2.sh
echo "cd \$pwd" >> script2.sh
echo "" >> script2.sh
echo "# staging-in input" >> script2.sh

sed -i 's/localgrid_mnt\///g' script2.sh # remove problematic line

cp script.sh script_temp.sh
cat script2.sh >> script_temp.sh



until [ $total -lt 1 ]
do
  echo "Total is" $total
  total=`expr $total - ${num_files}`
  echo "Subtracted total is" $total
  counter=`expr $counter + 1`
  head -n ${num_files} temp_input.1 > input_${counter}.1
  head -n ${num_files} temp_input.1.2 > input_${counter}.2
  tail -n $total temp_input.1 > temp_input_2_${counter}.1
  tail -n $total temp_input.1.2 > temp_input_2_${counter}.1.2
  rm -f temp_input.1
  mv temp_input_2_${counter}.1 temp_input.1
  rm -f temp_input.1.2
  mv temp_input_2_${counter}.1.2 temp_input.1.2
  mkdir -p ${output_name}/job${counter}
  cp script_temp.sh ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "mkdir -p /scratch/${output_name}_input" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  cat  input_${counter}.1 >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  rm -f input_${counter}.1
  more input_${counter}.2 | tr '\n' ' ' > temp_input.2
  rm -f input_${counter}.2 
  echo "mkdir /scratch/${output_name}_${counter}_runDir" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cd /scratch/${output_name}_${counter}_runDir"    >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo -n "sframe_input.py -r -x 1 -d -o input.xml -t ${inTreeName} " >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  more temp_input.2 >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cp ${sframe_dir}/JobConfig.dtd ${sframe_dir}/${config_name} ${sframe_dir}/*.root ." >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "ls -ltrh" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "sframe_main ${config_name}" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "ls -ltrh" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "touch events.txt" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "touch filelist.txt" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "tar czvf events.tgz events*.txt filelist.txt" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cp events.tgz ${sframe_dir}/${output_name}/job${counter}/" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cp total.txt ${sframe_dir}/${output_name}/job${counter}/" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cp *.csv ${sframe_dir}/${output_name}/job${counter}/" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "scramv1 project CMSSW CMSSW_5_3_3"  >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cd CMSSW_5_3_3/src"  >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "eval \`scram runtime -sh\`"  >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cp -r "$CMSSW_BASE"/src/TauAnalysis ."  >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  sed -i 's/localgrid_mnt\///g' ${output_name}/job${counter}/${output_name}_${counter}.sh # remove problematic line
  echo "scram b" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "eval \`scram runtime -sh\`"  >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cp /scratch/${output_name}_${counter}_runDir/Analysis.Data1.Reco.root ." >>  ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "nsvfitStandalone Analysis.Data1.Reco.root redtree" >> ${output_name}/job${counter}/${output_name}_${counter}.sh # svfit mass calculation
  echo "cp Analysis.Data1.Reco.root ${sframe_dir}/${output_name}/job${counter}/" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo -n "rm -rf " >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  more temp_input.2 >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cd /scratch" >>  ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "rm -rf ${output_name}_${counter}_runDir" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "echo \"(0) Wrapper finished successfully. Exit code 0\" " >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cd ${output_name}/job${counter}" >> ${output_name}_SubmitAll.sh
  echo "echo \"Submitting job no. ${counter}... \" " >> ${output_name}_SubmitAll.sh
  echo "qsub -q localgrid@cream02 -o script.stdout -e script.stderr ${output_name}_${counter}.sh" >> ${output_name}_SubmitAll.sh
  echo "cd ../.." >> ${output_name}_SubmitAll.sh
done 
rm -f temp_input*
rm -f full_path
rm -f script2.sh
rm -f script_temp.sh

chmod +x ${output_name}_SubmitAll.sh
echo "To submit jobs, do ./${output_name}_SubmitAll.sh"
echo "Duplicate input files are in ${output_name}_duplicates.list"