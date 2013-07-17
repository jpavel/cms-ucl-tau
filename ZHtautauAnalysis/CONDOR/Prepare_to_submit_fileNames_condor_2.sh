#!/bin/bash

min=1
inFile=${1}/input_files.txt
max=`more ${inFile} | wc -l`
echo ${max}
cp condor2.cmd.fragment ${1}.cmd


echo "transfer_input_files = JobConfig.dtd,${2},Fall11_PU.root,Summer12_PU_53X.root,dataPileUpHistogramABCD_True_2012.root,dataPileUpHistogram_True_2011.root,input.xml" >> ${1}.cmd

echo "universe       = vanilla" >> ${1}.cmd
echo "requirements   = (CMSFARM =?= TRUE)" >> ${1}.cmd


counter=0
more ${inFile} | while read line
do
  file=`echo $line`
  counter=`expr $counter + 1`
  mkdir ${1}/job${counter}
  cp JobConfig.dtd ${2} Fall11_PU.root Summer12_PU_53X.root dataPileUpHistogramABCD_True_2012.root dataPileUpHistogram_True_2011.root ${1}/job${counter}
  cp ${1}/${file} ${1}/job${counter}/input.xml
  echo "Initialdir     = ${1}/job${counter}" >> ${1}.cmd
  echo "Arguments      = ${2} $CMSSW_BASE/src" >> ${1}.cmd
  echo "queue 1" >> ${1}.cmd
  echo "" >> ${1}.cmd
done

