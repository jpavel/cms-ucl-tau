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
 find -name *${file} >> logFiles
done
#rm *.running
#python MakeListRunningJobs.py

# head -n running.list 
# head -n 1 running.list 
# find -name '*lo g.3026451.1' 
# find -name '*log.3026451.1' | ls -l
# find -name '*log.3026451.1' 
# ls -l ./20130913_AD_DoubleElectron_Run2012D-22Jan2013-v1/job2/condor.log.3026451.1
# ls --helop
# ls --help
# ls -l ./20130913_AD_DoubleElectron_Run2012D-22Jan2013-v1/job2/condor.log.3026451.1
# time
# date
# ls -lu ./20130913_AD_DoubleElectron_Run2012D-22Jan2013-v1/job2/condor.log.3026451.1
# stat ./20130913_AD_DoubleElectron_Run2012D-22Jan2013-v1/job2/condor.log.3026451.1
# stat --he
# stat --format=%X ./20130913_AD_DoubleElectron_Run2012D-22Jan2013-v1/job2/condor.log.3026451.1
# stat --format=%Y ./20130913_AD_DoubleElectron_Run2012D-22Jan2013-v1/job2/condor.log.3026451.1
# stat --format=%Z ./20130913_AD_DoubleElectron_Run2012D-22Jan2013-v1/job2/condor.log.3026451.1
# data +%s
# date +%s
