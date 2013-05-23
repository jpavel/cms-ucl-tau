#!/bin/bash
    
name=${1}
max=`ls | grep job | grep ${name} | wc -l`
echo "----${name}--------------------"
for block in  `seq -s ' ' 1 ${max}`; do
    echo "job ${block}:"
    more ${name}_job${block}/*stdout* | grep -i '(0)'
    #more ${name}_job${block}/*stderr*
    ls -ltrh ${name}_job${block} | grep root | grep Filter
    cd ${name}_job${block}
    more total.txt
    cd ..
done