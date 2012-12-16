#!/bin/bash
    
name=${1}
max=`ls | grep job | grep ${name} | wc -l`
echo "----${name}--------------------"
for block in  `seq -s ' ' 1 ${max}`; do
    echo "job ${block}:"
    more ${name}_job${block}/*stdout* | grep -i '(0)'
    #more ${name}_job${block}/*stderr*
    ls -ltrh ${name}_job${block} | grep root | grep Analysis 
    ls -ltrh ${name}_job${block} | grep tgz
    cd ${name}_job${block}
    tar xzvf events.tgz
    more events.txt | wc -l 
    cd ..
done