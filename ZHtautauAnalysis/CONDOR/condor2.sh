#! /bin/sh

#configuration
release_path=${2}

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
nsvfitStandalone Analysis.Data1.Reco.root redtree