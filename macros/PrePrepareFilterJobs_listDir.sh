input_data=`echo $1`
NAME=`echo $2`
input_list=`echo $3`
num_files=`echo $4`
config_FR=`echo $5`
config_2011=`echo $6`
output_data=`echo $7`
results=`echo $8`
time=`date "+%Y%m%d"`

total=`more ${input_list} | wc -l`
echo "Total number of input directories is" $total

touch ${time}_${NAME}_PrepareJobs.sh
rm -f ${time}_${NAME}_PrepareJobs.sh
touch ${time}_${NAME}_PrepareJobs.sh

echo "touch ${time}_${NAME}_RunAll.sh" >> ${time}_${NAME}_PrepareJobs.sh
echo "rm -f ${time}_${NAME}_RunAll.sh" >> ${time}_${NAME}_PrepareJobs.sh
echo "touch ${time}_${NAME}_RunAll.sh" >> ${time}_${NAME}_PrepareJobs.sh

cat makeProxy.sh >> ${time}_${NAME}_PrepareJobs.sh

more ${input_list} | while read line
do
 file=`echo ${line%/}`
 echo "source PrepareJobs_removeDuplicates_filter_mass.sh ${input_data}/${line} ${time}_${NAME}_${file} ${num_files} ${config_FR} ${config_2011} ${output_data}/${line} ${results}" >> ${time}_${NAME}_PrepareJobs.sh
 echo "echo \"./${time}_${NAME}_${file}_SubmitAll.sh\" >> ${time}_${NAME}_RunAll.sh"  >> ${time}_${NAME}_PrepareJobs.sh
done
echo "chmod +x ${time}_${NAME}_RunAll.sh" >> ${time}_${NAME}_PrepareJobs.sh
chmod +x ${time}_${NAME}_PrepareJobs.sh
echo "To prepare jobs run ./${time}_${NAME}_PrepareJobs.sh"