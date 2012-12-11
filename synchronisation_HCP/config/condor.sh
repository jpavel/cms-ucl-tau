#! /bin/sh

#configuration
release_path=/home/fynu/jpavel/scratch/analysis/CMSSW_5_3_3/src
#EventMax=${1}
#EventSkip=${2}


source setup_cms2.sh
cd ${release_path}
cmsenv
cd -
cd ${release_path}/SFrame
source setup.sh
cd -

###JOB itself
#cmsRun patTuple_tauId_MVAdisc_cfg.py inputFiles=${1} discriminator1=${2}
#source run_anal.sh
sframe_main Analysis_config_T2.xml