if [ $# -ne 1 ]; then
    echo "Wrong number of input arguments!"
    echo "Usage: source KillHangingJobs.sh <MaxAllowedTimeInS>"
    echo "e.g. source KillHangingJobs 7200"
    return 2
fi

limit=${1}

touch running.list
rm -f running.list
condor_q jpavel | grep jpavel | awk '{print $1 ,$6}' | grep 'R' | awk '{print $1}' > running.list
touch logFiles
rm -f logFiles
touch logFiles
currTime=`date +%s` # current time in seconds from Epoch
more running.list | while read line
do
 file=`echo ${line}`
 file=log.${file}
 logfile=`find -name *${file}`
 modTime=`stat --format=%Y ${logfile}`
 echo "mod time is " ${modTime} " and curr time is " ${currTime}
 age=`expr ${currTime} - ${modTime}`
 echo "the age is "${age}" s"
 if [ ${age} -gt ${limit} ]; then
   echo "Job ${line} is going to be killed! The command will be condor_rm ${line}"
   condor_rm ${line}
 fi
done
