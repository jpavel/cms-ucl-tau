input_data=`echo $1`
NAME=`echo $2`
input_list=`echo $3`
num_files=`echo $4`
config=`echo $5`
results=`echo $6`
time=`date "+%Y%m%d"`

if [ "${BASH_SOURCE[0]}" = "${0}" ]; then
  echo script not sourced! Exiting...
  exit 1
fi


if [ $# -ne 6 ]; then
    echo "Wrong number of input arguments!"
    echo "Usage: source Prepare_listdir.sh <inputDir> <taskName> <listOfSubdirs> <filesPerJob> <configXML> <resultsOutputDir>"
    echo "e.g. source source Prepare_listdir.sh /storage/data/cms/store/user/jez/ZHttNtuples_v2/53X/Data/ CD_2012 CD.condor.list 50 Analysis_config_T2.xml results"
    return 2
fi




total=`more ${input_list} | wc -l`
echo "Total number of input directories is" $total

touch ${time}_${NAME}_PrepareJobs.sh
rm -f ${time}_${NAME}_PrepareJobs.sh
touch ${time}_${NAME}_PrepareJobs.sh

echo "touch ${time}_${NAME}_RunAll.sh" >> ${time}_${NAME}_PrepareJobs.sh
echo "rm -f ${time}_${NAME}_RunAll.sh" >> ${time}_${NAME}_PrepareJobs.sh
echo "touch ${time}_${NAME}_RunAll.sh" >> ${time}_${NAME}_PrepareJobs.sh


more ${input_list} | while read line
do
 file=`echo ${line%/}`
 echo "source PrepareJobs_removeDuplicates.sh ${input_data}/${line} ${time}_${NAME}_${file} ${num_files} ${config} ${results}" >> ${time}_${NAME}_PrepareJobs.sh
 echo "echo \"./${time}_${NAME}_${file}_SubmitAll.sh\" >> ${time}_${NAME}_RunAll.sh"  >> ${time}_${NAME}_PrepareJobs.sh
done

chmod +x ${time}_${NAME}_PrepareJobs.sh
echo "chmod +x ${time}_${NAME}_RunAll.sh" >> ${time}_${NAME}_PrepareJobs.sh
echo "echo \"To submit all jobs run ./${time}_${NAME}_RunAll.sh\"" >> ${time}_${NAME}_PrepareJobs.sh
echo "To prepare jobs run ./${time}_${NAME}_PrepareJobs.sh"


