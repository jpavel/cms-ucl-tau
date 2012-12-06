#!/bin/bash

mkdir -p ${2}
pwd=$PWD
$ROOTSYS/bin/hadd ${2}/${1}_histo.root ${1}_job*/Filter.Data1.Reco.root
touch ${2}/${1}_total.txt
touch ${2}/${1}_lumi.csv
max=`ls | grep job | grep ${1}_job | wc -l`
echo ${max}
for block in  `seq -s ' ' 1 ${max}`; do
    cd ${1}_job${block}
#    more total.txt
    cat total.txt >> ../${2}/${1}_total.txt
    cat lumi.csv >> ../${2}/${1}_lumi.csv
    cd ${pwd}
done
gsum=0
while read -r line
do
  add=`echo $line`
#  echo $add
  gsum=`expr $gsum + $add`
done < <(more ${2}/${1}_total.txt)
echo $gsum > ${2}/${1}_sumEvents.txt
echo "Total events processed in filtering "${1}" is "${gsum} 