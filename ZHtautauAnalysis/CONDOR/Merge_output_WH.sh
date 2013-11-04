#!/bin/bash

mkdir -p ${2}
pwd=$PWD
$ROOTSYS/bin/hadd ${2}/${1}_histo.root ${1}/job*/WHanalysis.Data1.Reco.root
tar czvf ${2}/${1}_condor.out ${1}/job*/condor.out.*
touch ${2}/${1}_total.txt
touch ${2}/${1}_lumi.csv
touch ${2}/${1}_event.list
max=`ls ${1} | grep job | wc -l`
echo "There is ${max} subjobs in task ${1}"
for block in  `seq -s ' ' 1 ${max}`; do
    cd ${1}/job${block}
#    more total.txt
    tail total.txt -n 1 >> ${pwd}/${2}/${1}_total.txt
    cat lumi.csv >> ${pwd}/${2}/${1}_lumi.csv
    cat event_mmt.list >> ${pwd}/${2}/${1}_event_mmt.list
    cat event_eet.list >> ${pwd}/${2}/${1}_event_eet.list
    cat overlap_eet.list >> ${pwd}/${2}/${1}_overlap_eet.list
    cat overlap_mmt.list >> ${pwd}/${2}/${1}_overlap_mmt.list
    cat fail.list >> ${pwd}/${2}/${1}_fail.list

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
echo "converting csv to json"
csv2json.py ${2}/${1}_lumi.csv --output ${2}/lumi.json
