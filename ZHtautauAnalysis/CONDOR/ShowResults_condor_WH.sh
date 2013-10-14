#!/bin/bash

#min=1
#max=${1}
name=${1}
touch results.out
rm -f results.out
touch results.out
touch resubmit
rm -f resubmit
touch resubmit
max=`ls ${name} | grep job | wc -l`
good=0
echo "----${name}--------------------"
echo "These jobs probably needs to be resubmitted:"
for block in  `seq -s ' ' 1 ${max}`; do
    echo "-->job ${block}:" >> results.out
    status=`more ${name}/job${block}/*.log.* | grep -i '(1)'`
    status2=`echo ${status}`
    pass=0
    if [ "${status2}" == "(1) Normal termination (return value 0)" ]; then
      echo "Successful run" >> results.out
      good=`expr $good + 1`
      pass=1
    fi
    echo "---> stdout excerpt <----" >> results.out
    more ${name}/job${block}/*.out.* | grep -i '(0)' >> results.out
    more ${name}/job${block}/*.out.* | grep -i 'ERROR' >> results.out
    more ${name}/job${block}/*.out.* | grep -i 'FATAL' >> results.out
    echo " ------------------------" >> results.out
    ls -ltrh ${name}/job${block} | grep root | grep WHanalysis >> results.out
    more ${name}/job${block}/total.txt >> results.out
    pass1=`more ${name}/job${block}/*.out.* | grep -i 'ERROR' | wc -l`
    pass2=`more ${name}/job${block}/*.out.* | grep -i 'FATAL' | wc -l`
    pass1=`expr $pass1 + $pass2`
    if [ $pass -eq 0 ] || [ $pass1 -gt 0 ]; then
      echo "${block}" 
      echo "${block}" >> resubmit
    fi
done
resub_tot=`more resubmit | wc -l`
echo "----SUMMARY:-----"
echo "total jobs: ${max}"
echo "good jobs: ${good}"
echo "resubmit: ${resub_tot}"