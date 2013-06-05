#!/bin/sh

time=`date "+%Y%m%d%H%M"`
task=${1}
output=${2}
outputDir=${3}

max=`ls ${task} |grep job | wc -l`
echo "There are ${max} jobs in the task ${task}"
source ShowResults_filter_error2.sh ${task} 1> results.out 2> results.err
echo "These jobs need to be re-submitted:"
source ShowResults_filter_good2.sh ${task} 2> resubmit.err | tee resubmit
resubtotal=`more resubmit | wc -l`
successful=`expr ${max} - ${resubtotal}`
echo "Total ${resubtotal}"
mkdir -p ${outputDir}/${output}
mkdir -p ${outputDir}/OLD/${output}_old_${time}
touch ${outputDir}/${output}/file
mv ${outputDir}/${output}/* ${outputDir}/OLD/${output}_old_${time}/
source MergeOutput_eventfilter.sh ${task} ${outputDir}/${output}/ 
finished=`more ${outputDir}/${output}/*_total.txt | wc -l`
echo "${finished} jobs produced output"

echo "---------SUMMARY----------"
echo "total: ${max}"
echo "successful: ${successful}"
echo "finished: ${finished}"

echo "Calculating lumi..."
lumiCalc2.py overview -i ${outputDir}/${output}/lumi.json 1>lumi.out 2>lumi.err
tail lumi.out -n 4
touch Resubmit_now.sh
rm -f Resubmit_now.sh 
echo "source Resubmit_eventFilter.sh resubmit ${task}" > Resubmit_now.sh
chmod +x Resubmit_now.sh
echo "To resubmit failed jobs do ./Resubmit_now.sh"
