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
output_name=${time}_$2
num_files=${3}
config_name=${4}
output_dir=${5}

sframe_dir=$PWD
# input datasets settings
ntuple_name=output_Ntuples
srm_server=dcap://maite.iihe.ac.be
inTreeName=t

voms-proxy-init --voms cms:/cms/becms -valid 48:00
export STORAGE=srm://maite.iihe.ac.be
cp $X509_USER_PROXY myProxy

full_path=${srm_server}${input_data}/
touch full_path
rm -f full_path
echo "Full path to data is "${full_path}
echo ${full_path} >> full_path

out_full_path=${srm_server}${output_dir}/

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
  mkdir ${output_name}_job${counter}
  cp script.sh ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "export X509_USER_PROXY=${sframe_dir}/myProxy" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "mkdir -p /scratch/${output_name}_input" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  cat  input_${counter}.1 >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  rm -f input_${counter}.1
  more input_${counter}.2 | tr '\n' ' ' > temp_input.2
  rm -f input_${counter}.2 
  echo "mkdir /scratch/${output_name}_${counter}_runDir" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "cd /scratch/${output_name}_${counter}_runDir"    >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo -n "sframe_input.py -r -x 1 -d -o input.xml -t ${inTreeName} " >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  more temp_input.2 >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "cp ${sframe_dir}/JobConfig.dtd ${sframe_dir}/${config_name} ${sframe_dir}/*.root ." >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "ls -ltrh" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "sframe_main ${config_name}" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "ls -ltrh" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "cp Filter.Data1.Reco.root ${sframe_dir}/${output_name}_job${counter}/" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "cp *.txt ${sframe_dir}/${output_name}_job${counter}/" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "cp *.csv ${sframe_dir}/${output_name}_job${counter}/" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "srmcp file:////scratch/${output_name}_${counter}_runDir/output.root ${STORAGE}/${output_dir}/output_Ntuples_${counter}_0_abc.root" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
#  echo "touch events.txt" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
#  echo "tar czvf events.tgz events.txt" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
#  echo "cp events.tgz ${sframe_dir}/${output_name}_job${counter}/" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo -n "rm -rf " >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  more temp_input.2 >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "cd /scratch" >>  ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "rm -rf ${output_name}_${counter}_runDir" >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "echo \"(0) Wrapper finished successfully. Exit code 0\" " >> ${output_name}_job${counter}/${output_name}_${counter}.sh
  echo "cd ${output_name}_job${counter}" >> ${output_name}_SubmitAll.sh
  echo "echo \"Submitting job no. ${counter}... \" " >> ${output_name}_SubmitAll.sh
  echo "qsub -q localgrid@cream02 -o script.stdout -e script.stderr ${output_name}_${counter}.sh" >> ${output_name}_SubmitAll.sh
  echo "cd .." >> ${output_name}_SubmitAll.sh
done 
rm -f temp_input*
rm -f full_path

chmod +x ${output_name}_SubmitAll.sh
echo "To submit jobs, do ./${output_name}_SubmitAll.sh"
echo "Duplicate input files are in ${output_name}_duplicates.list"