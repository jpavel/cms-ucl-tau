input_data=`echo $1`
NAME=`echo $2`
input_list=`echo $3`
num_files=`echo $4`
config=`echo $5`
results=`echo $6`
time=`date "+%Y%m%d"`

total=`more ${input_list} | wc -l`
echo "Total number of input directories is" $total

touch ${time}_${NAME}_PrepareJobs.sh
rm -f ${time}_${NAME}_PrepareJobs.sh
touch ${time}_${NAME}_PrepareJobs.sh

echo "touch {time}_${NAME}_RunAll.sh" >> ${time}_${NAME}_PrepareJobs.sh
echo "rm -f {time}_${NAME}_RunAll.sh" >> ${time}_${NAME}_PrepareJobs.sh
echo "touch {time}_${NAME}_RunAll.sh" >> ${time}_${NAME}_PrepareJobs.sh


more ${input_list} | while read line
do
 file=`echo ${line%/}`
 echo "source Prepare_condor_InputDir_OutputName_FilesPerJob_configFile.sh ${input_data}/${line} ${time}_${NAME}_${file} ${num_files} ${config} ${results}" >> ${time}_${NAME}_PrepareJobs.sh
 echo "echo \"condor_submit ${time}_${NAME}_${file}.cmd\" >> ${time}_${NAME}_RunAll.sh"  >> ${time}_${NAME}_PrepareJobs.sh
done

chmod +x ${time}_${NAME}_PrepareJobs.sh
echo "chmod +x ${time}_${NAME}_RunAll.sh" >> ${time}_${NAME}_PrepareJobs.sh
echo "echo \"To submit all jobs run ./${time}_${NAME}_RunAll.sh\"" >> ${time}_${NAME}_PrepareJobs.sh
echo "To prepare jobs run ./${time}_${NAME}_PrepareJobs.sh"


