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
rm temp_input.*

output_name='files'
ntuple_name=output_Ntuples
inTreeName=t
num_files=${2}

#~ full_path=${input_data}/
#~ touch full_path
#~ rm full_path
#~ echo "Full path to data is "${full_path}
#~ echo ${full_path} >> full_path

touch ${output_name}_makeXML.sh
rm ${output_name}_*makeXML.sh


cp ${1} temp_input.1 
total=`more temp_input.1 | wc -l`
echo "Total number of input root files is" $total
counter=0

touch temp_input.1.1

#~ touch toKeep.list
#~ rm -f toKeep.list
#~ touch toKeep.list
#~ 
#~ touch duplicates.list
#~ rm -f duplicates.list
#~ touch duplicates.list
#~ 
#~ 
#~ #duplicate removal
#~ for block in  `seq -s ' ' 1 ${total}`; do
    #~ more temp_input.1 |  grep "_${block}_[0-9]\{1,\}_....root" > copies.list
    #~ copies=`more copies.list | wc -l`
    #~ toRemove=`expr $copies - 1`
    #~ if [ $copies -gt 0 ]; then
      #~ more copies.list | head -n ${toRemove} >> duplicates.list
      #~ more copies.list | tail -n 1 >> toKeep.list
    #~ fi
    #~ rm -f copies.list
#~ done
#~ 
#~ rm -f temp_input.1
#~ mv toKeep.list temp_input.1

#~ 
#~ 
#~ 
#~ 
#~ 
#~ more temp_input.1 |while read line
#~ do
  #~ file=`echo $line`
  #~ echo "${full_path}${file}" >> temp_input.1.1
#~ done
#~ 
#~ #echo "The full paths to all files are:"
#~ #more temp_input.1.1
#~ mv temp_input.1.1 temp_input.1

until [ $total -lt 1 ]
do
  echo "Total is" $total
  total=`expr $total - ${num_files}`
  echo "Subtracted total is" $total
  counter=`expr $counter + 1`
  head -n ${num_files} temp_input.1 > temp_input_${counter}.1
  tail -n $total temp_input.1 > temp_input_2_${counter}.1
  mv temp_input_2_${counter}.1 temp_input.1
  mv temp_input_${counter}.1  temp_input.2
  more temp_input.2 >> ${output_name}_${counter}_inputFiles.txt
  rm temp_input.2
done 
rm temp_input*
ls | grep _inputFiles.txt | grep ${output_name} > input_${output_name}.txt

