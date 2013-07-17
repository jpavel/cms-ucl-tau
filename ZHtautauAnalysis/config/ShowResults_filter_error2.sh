#!/bin/bash
    
name=${1}
max=`ls ${name} | wc -l`
echo "----${name}--------------------"
for block in  `seq -s ' ' 1 ${max}`; do
    echo "job ${block}:"
    more ${name}/job${block}/*stdout* | grep -i '(0)'
    more ${name}/job${block}/*stdout* | grep -i 'ERROR'
    more ${name}/job${block}/*stdout* | grep -i 'FATAL'
    #more ${name}_job${block}/*stderr*
    ls -ltrh ${name}/job${block} | grep root | grep Analysis
    #cd ${name}_job${block}
    more ${name}/job${block}/total.txt
    #    cd ..
done