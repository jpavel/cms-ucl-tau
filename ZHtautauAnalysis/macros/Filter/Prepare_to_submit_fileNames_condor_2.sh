#!/bin/bash

min=1
inFile=${1}/input_files.txt
max=`more ${inFile} | wc -l`
echo ${max}
cp condor2.cmd.fragment ${1}.cmd


echo "transfer_input_files = run_filter_eventNumber.C,filter_eventNumber.C,myevent.h,myobject.h,selection.h,helper.h,filelist.txt,eventlist.txt" >> ${1}.cmd

echo "universe       = vanilla" >> ${1}.cmd
echo "requirements   = (CMSFARM =?= TRUE)" >> ${1}.cmd


counter=0
more ${inFile} | while read line
do
  file=`echo $line`
  counter=`expr $counter + 1`
  mkdir ${1}/job${counter}
  cp run_filter_eventNumber.C filter_eventNumber.C myevent.h myobject.h selection.h helper.h  ${1}/job${counter}
  cp ${1}/${file} ${1}/job${counter}/filelist.txt
  cp ${2} ${1}/job${counter}/eventlist.txt
  echo "Initialdir     = ${1}/job${counter}" >> ${1}.cmd
  echo "queue 1" >> ${1}.cmd
  echo "" >> ${1}.cmd
done

