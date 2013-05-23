#!/bin/bash
    
name=${1}
max=`ls | grep job | grep ${name} | wc -l`
#echo "----${name}--------------------"
for block in  `seq -s ' ' 1 ${max}`; do
#    echo "job ${block}:"
#    more ${name}_job${block}/*stdout* | grep -i '(0)'
#    more ${name}_job${block}/*stdout* | grep -i 'ERROR'
#    more ${name}_job${block}/*stdout* | grep -i 'FATAL'
    #more ${name}_job${block}/*stderr*
    pass=`ls ${name}_job${block} | grep total | wc -l`
    pass1=`more ${name}_job${block}/*stdout* | grep -i 'ERROR' | wc -l`
    pass2=`more ${name}_job${block}/*stdout* | grep -i 'FATAL' | wc -l`
    pass1=`expr $pass1 + $pass2`
#    echo $pass1
#    cd ${name}_job${block}
    if [ $pass -eq 0 ] || [ $pass1 -gt 0 ]; then
      echo "${block}"
    fi
#    cd ..
done