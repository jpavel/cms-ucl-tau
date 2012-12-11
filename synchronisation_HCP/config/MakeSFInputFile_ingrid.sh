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

input_data=`echo $1`
output_name=`echo $2`
# input datasets settings
ntuple_name=output
#srm_server=dcap://maite.iihe.ac.be
inTreeName=t

full_path=${input_data}/
touch full_path
rm full_path
echo "Full path to data is "${full_path}
echo ${full_path} >> full_path

touch ${output_name}_makeXML.sh
rm ${output_name}_*makeXML.sh


ls ${input_data} | grep root | sort > temp_input.1 
total=`more temp_input.1 | wc -l`
echo "Total number of input root files is" $total
counter=0

touch temp_input.1.1
more temp_input.1 |while read line
do
  file=`echo $line`
  echo "${full_path}${file}" >> temp_input.1.1
done

echo "The full paths to all files are:"
more temp_input.1.1
mv temp_input.1.1 temp_input.1

until [ $total -lt 0 ]
do
  echo "Total is" $total
  total=`expr $total - 1`
  echo "Subtracted total is" $total
  counter=`expr $counter + 1`
  head -n 1 temp_input.1 > temp_input_${counter}.1
  tail -n $total temp_input.1 > temp_input_2_${counter}.1
  mv temp_input_2_${counter}.1 temp_input.1
  more temp_input_${counter}.1 | tr '\n' ' ' > temp_input.2
#  sed -i "s:out:${full_path}bla:g" temp_input.2
#   sed -i 's/srm.ndgf/ftp1.ndgf/g' temp_input.2
  touch ${output_name}_${counter}_makeXML.sh
echo "<In FileName=\"${full_path}${file}\" Lumi=\"1.0\" />" >> ${output_name}_${counter}_makeXML.sh
  more temp_input.2 >> ${output_name}_${counter}_makeXML.sh
  #rm temp_input.2
done 
#rm temp_input*

echo "The command now executed will be "
more ${output_name}_${counter}_makeXML.sh
source ${output_name}_${counter}_makeXML.sh

