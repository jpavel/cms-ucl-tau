#!/bin/bash
    
#min=1
#max=${1}
name=${1}
pwd=$PWD
max=`ls ${name} | grep job | wc -l`
echo "----${name}--------------------"
time=`date "+%Y%m%d"`
for block in  `seq -s ' ' 1 ${max}`; do
    echo "job ${block}:"
    cd ${name}/job${block}
    tar czvf outputs_${time}.tgz condor* 
    rm condor*
    rm Analysis*root
    cd ${pwd}
done
