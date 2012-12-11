#!/bin/bash
    
#min=1
#max=${1}
name=${1}
max=`ls | grep job | grep ${name} | wc -l`
echo "----${name}--------------------"
time=`date "+%Y%m%d"`
for block in  `seq -s ' ' 1 ${max}`; do
    echo "job ${block}:"
    cd ${name}_job${block}
    tar czvf outputs_${time}.tgz script* 
    rm script*
    rm Analysis*root
    cd ..
done
