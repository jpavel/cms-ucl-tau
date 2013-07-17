#! /bin/sh

#configuration
release_path=/home/fynu/jpavel/scratch/PostMoriond/Application/CMSSW_5_3_3/src

source /nfs/soft/grid/ui/setup/grid-env.sh
source /nfs/soft/cms/cmsset_default.sh
export SCRAM_ARCH=slc5_amd64_gcc462

cd ${release_path}
cmsenv
cd -
cd ${release_path}/SFrame
source setup.sh
cd -

###JOB itself
sframe_main ${1}