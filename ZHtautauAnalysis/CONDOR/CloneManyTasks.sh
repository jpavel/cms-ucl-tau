input_list=`echo $1`
suffix=`echo $2`
config=`echo $3`

if [ "${BASH_SOURCE[0]}" = "${0}" ]; then
  echo script not sourced! Exiting...
  exit 1
fi


if [ $# -ne 3 ]; then
    echo "Wrong number of input arguments!"
    echo "Usage: source CloneManyTasks.sh <ListOfInputTasks> <suffix> <NewConfig>"
    echo "e.g. source CloneManyTaks.sh inputs.list FRrev Analysis_config_T2_MC_FRrev.xml"
    return 2
fi




total=`more ${input_list} | wc -l`
echo "Total number of input directories is" $total

touch ${suffix}_CloneTasks.sh
rm -f ${suffix}_CloneTasks.sh
touch ${suffix}_CloneTasks.sh

echo "touch ${suffix}_RunAll.sh" >> ${suffix}_CloneTasks.sh
echo "rm -f ${suffix}_RunAll.sh" >> ${suffix}_CloneTasks.sh
echo "touch ${suffix}_RunAll.sh" >> ${suffix}_CloneTasks.sh


more ${input_list} | while read line
do
 file=`echo ${line%/}`
 echo "source CloneTask.sh ${file} ${file}_${suffix} ${config}" >> ${suffix}_CloneTasks.sh
 echo "echo \"condor_submit ${file}_${suffix}.cmd\" >> ${suffix}_RunAll.sh"  >> ${suffix}_CloneTasks.sh
done

chmod +x ${suffix}_CloneTasks.sh
echo "chmod +x ${suffix}_RunAll.sh" >> ${suffix}_CloneTasks.sh
echo "echo \"To submit all jobs run ./${suffix}_RunAll.sh\"" >> ${suffix}_CloneTasks.sh
echo "To prepare jobs run ./${suffix}_CloneTasks.sh"


