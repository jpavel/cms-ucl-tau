name=${1}
output=${2}
outputDir=${3}

time=`date "+%Y%m%d%H%M"`

echo "killing jobs hanging for more than 2h:"
#source KillHangingJobs.sh 7200

all=`ls ${name} | grep job | wc -l`
echo "There are ${all} jobs in the task ${name}"

mkdir -p ${outputDir}/${output}
mkdir -p ${outputDir}/OLD/${output}_old_${time}
touch ${outputDir}/${output}/file
mv ${outputDir}/${output}/* ${outputDir}/OLD/${output}_old_${time}/


source Merge_output2.sh ${name} ${outputDir}/${output}/
finished=`more ${outputDir}/${output}/*_total.txt | wc -l`
echo "${finished} jobs produced output"

source ShowResults_condor.sh ${name}

echo "Calculating lumi..."
pixelLumiCalc.py overview -i ${outputDir}/${output}/lumi.json 1>lumi.out 2>lumi.err
tail lumi.out -n 4

touch Resubmit_now.sh
rm -f Resubmit_now.sh 
echo "source Resubmit_condor.sh resubmit ${name}" > Resubmit_now.sh
chmod +x Resubmit_now.sh
n_resub=`more resubmit | wc -l`
if [ $n_resub -gt 0 ]; then
  echo "Removing jobs which are still running from the resubmission..."
  source ListRunningJobs.sh
  python FilterResubmit_task.py ${name}
  touch logFiles
  rm logFiles
  echo "To resubmit failed jobs do ./Resubmit_now.sh"
fi
