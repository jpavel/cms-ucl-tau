#!/bin/bash

# Script to prepare input files for filtering of ntuples at ULB cluster. 

# Input parameters: input directory with ntuples,
#                   name of task (any string), 
#                   number of input files per job (recommended 1-10, depending on input sample and filtering efficiency), 
#                   bool switch whether to prepare ntuples for fake rate estimation or not, 
#                   bool switch whether processing 2011 samples or not (different triggers)
#                   name of output directory at pnfs
#                   name of local directory where summary of results will be stored

# ex.: 
# source PrepareJobs_removeDuplicates_Eventfilter.sh /pnfs/iihe/cms/store/user/jez/ZHttNtuples/53X/Data/DoubleElectron_Run2012D-PromptReco-v1/ FILTER3_D_Ele 10 filelist.txt eventlist.txt results_filter/test 


touch temp_input.1
rm -f temp_input.*

time=`date "+%Y%m%d"`
input_data=`echo $1`
output_name=${time}_$2
num_files=${3}
fileList=${4}
eventList=${5}
results_dir=${6}

sframe_dir=$PWD
# input datasets settings
ntuple_name=output_Ntuples
srm_server=dcap://maite.iihe.ac.be
inTreeName=t

#voms-proxy-init --voms cms:/cms/becms -valid 48:00
export STORAGE=srm://maite.iihe.ac.be
#cp $X509_USER_PROXY myProxy

full_path=${srm_server}${input_data}/
touch full_path
rm -f full_path
echo "Full path to data is "${full_path}
echo ${full_path} >> full_path

out_full_path=${srm_server}${output_dir}/

#touch ${output_name}_makeXML.sh
#rm -f ${output_name}_*makeXML.sh


cp fileList temp_input.1 

touch temp_input.1.1
#~ touch temp_input.1.2
#~ 
#~ touch toKeep.list
#~ rm -f toKeep.list
#~ touch toKeep.list
#~ 
#~ touch ${output_name}_duplicates.list
#~ rm -f ${output_name}_duplicates.list
#~ touch ${output_name}_duplicates.list
#~ 
#~ 
#~ # duplicate removal
#~ for block in  `seq -s ' ' 1 ${total}`; do
    #~ more temp_input.1 |  grep "_${block}_[0-9]\{1,\}_....root" > copies.list
    #~ copies=`more copies.list | wc -l`
    #~ toRemove=`expr $copies - 1`
    #~ if [ $copies -gt 0 ]; then
      #~ more copies.list | head -n ${toRemove} >> ${output_name}_duplicates.list
      #~ more copies.list | tail -n 1 >> toKeep.list
    #~ fi
    #~ rm -f copies.list
#~ done
#~ 
#~ rm -f temp_input.1
#~ mv toKeep.list temp_input.1

currFile=""
more temp_input.1 |while read line
do
  file=`echo $line`
  if [ "${file}" != "${currFile}" ]; then
    echo "${file}" >> temp_input.1.1
    currFile=${file}
  fi
done

rm -f temp_input.1
mv temp_input.1.1 temp_input.1

more temp_input.1 |while read line
do
  file=`echo $line`
  echo "dccp ${full_path}${file} /scratch/${output_name}_input/" >> temp_input.1.1
  echo "/scratch/${output_name}_input/${file}" >> temp_input.1.2
done

echo "The full paths to all files are:"

rm -f temp_input.1
mv temp_input.1.1 temp_input.1

touch ${output_name}_run_filter_all.C
rm -f ${output_name}_run_filter_all.C
#touch ${output_name}_run_filter_all.C

#~ echo "#include <iostream>" >> ${output_name}_run_filter_all.C
#~ echo "void run_filter()" >> ${output_name}_run_filter_all.C
#~ echo "{" >> ${output_name}_run_filter_all.C
#~ echo "long n_evt=-1;" >> ${output_name}_run_filter_all.C
#~ echo "std::string input=\"fileList.txt\";" >> ${output_name}_run_filter_all.C
#~ echo "TString input=\"/scratch/${output_name}_input/\";" >> ${output_name}_run_filter_all.C
#~ echo "bool is2011 = ${config_2011};" >> ${output_name}_run_filter_all.C
#~ echo "bool isFR = ${config_FR};" >> ${output_name}_run_filter_all.C

cp run_filter_eventNumber.C >> ${output_name}_run_filter_eventNumber.C	

touch ${output_name}_SubmitAll.sh
rm -rf ${output_name}_SubmitAll.sh
touch ${output_name}_SubmitAll.sh

touch ${output_name}_ShowStatus.sh
rm -rf ${output_name}_ShowStatus.sh
touch ${output_name}_ShowStatus.sh

#cat makeProxy.sh >> ${output_name}_SubmitAll.sh

echo "source ShowStatus_eventFilter.sh ${output_name} ${output_name} ${results_dir}" >>  ${output_name}_ShowStatus.sh
chmod +x ${output_name}_ShowStatus.sh

mkdir -p ${output_name}
cp ${output_name}_run_filter_all.C ${output_name}/${output_name}_run_filter_all.C
rm -f ${output_name}_run_filter_all.C

total=`more temp_input.1 | wc -l`
echo "Total number of input root files is" $total
counter=0



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
  cp script.sh ${output_name}/job${counter}/${output_name}_${counter}.sh
#  echo "export X509_USER_PROXY=${sframe_dir}/myProxy" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "mkdir -p /scratch/${output_name}_input_${counter}" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  sed -i "s/_input/_input_${counter}/g" input_${counter}.*
  cat  input_${counter}.1 >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  rm -f input_${counter}.1
  cp input_${counter}.2 ${output_name}/job${counter}/filelist.txt
  input_${counter}.2 | tr '\n' ' ' > temp_input.2
  rm -f input_${counter}.2 
  echo "mkdir -p /scratch/${output_name}_${counter}_runDir" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cd /scratch/${output_name}_${counter}_runDir"    >> ${output_name}/job${counter}/${output_name}_${counter}.sh
#  echo -n "sframe_input.py -r -x 1 -d -o input.xml -t ${inTreeName} " >> ${output_name}/job${counter}/${output_name}_${counter}.sh
#  more temp_input.2 >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cp ${sframe_dir}/filter_eventNumber.C ${sframe_dir}/${output_name}/${output_name}_run_filter_eventNumber.C ${sframe_dir}/*.h ." >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cp ${sframe_dit}/${eventList} eventlist.txt" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cp ${sframe_dir}/${output_name}/${output_name}/job${counter}/filelist.txt ." >> ${sframe_dir}/${output_name}/${output_name}
  echo "cp ${output_name}_run_filter_eventNumber.C run_filter_eventNumber.C" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  #echo "sed -i 's/_input/_input_${counter}/g' run_filter.C"  >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "rm -f ${output_name}_run_filter_eventNumber.C" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "ls -ltrh" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "more run_filter_eventNumber.C" >> ${output_name}/job${counter}/${output_name}_${counter}.sh  
  echo "root -l -b -q -x run_filter_eventNumber.C" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "ls -ltrh" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  #echo "cp Filter.Data1.Reco.root ${sframe_dir}/${output_name}/job${counter}/" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cp *.txt ${sframe_dir}/${output_name}/job${counter}/" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cp *.csv ${sframe_dir}/${output_name}/job${counter}/" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
  echo "cp output.root ${sframe_dir}/${output_name}/job${counter}/" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
#  echo "touch events.txt" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
#  echo "tar czvf events.tgz events.txt" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
#  echo "cp events.tgz ${sframe_dir}/${output_name}/job${counter}/" >> ${output_name}/job${counter}/${output_name}_${counter}.sh
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

chmod +x ${output_name}_SubmitAll.sh
echo "To submit jobs, do ./${output_name}_SubmitAll.sh"
echo "Duplicate input files are in ${output_name}_duplicates.list"
