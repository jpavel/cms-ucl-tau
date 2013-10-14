#! /bin/bash

#configuration
release_path=${2}
more /etc/redhat-release
#source /nfs/soft/grid/ui/setup/grid-env.sh
#source /nfs/soft/grid/ui_sl6/setup/grid-env.sh
source /nfs/soft/cms/cmsset_default.sh
#export SCRAM_ARCH=slc5_amd64_gcc462
#setup-root
#source /nfs/soft/root/setup_sl6/root.sh 
echo $ROOTSYS

echo "going to ${release_path}"
cd ${release_path}
pwd
# instead of cmsenv
eval `scramv1 runtime -sh`
cd -
cd ${release_path}/SFrame
pwd
ls
source setup.sh
cd -

###JOB itself
sframe_main ${1}
#nsvfitStandalone Analysis.Data1.Reco.root redtree