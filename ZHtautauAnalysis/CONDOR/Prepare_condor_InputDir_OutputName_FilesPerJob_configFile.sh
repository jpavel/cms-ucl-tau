#!/bin/bash

if [ "${BASH_SOURCE[0]}" = "${0}" ]; then
  echo script not sourced! Exiting...
  exit 1
fi

if [ "$CMSSW_BASE" = "" ]; then
  echo \$CMSSW_BASE is NOT set! Exiting...
  return 1
fi

if [ "$SFRAME_DIR" = "" ]; then
  echo \$SFRAME_DIR is NOT set! Exiting...
  return 1
fi

if [ $# -ne 5 ]; then
    echo "Wrong number of input arguments!"
    echo "Usage: source Prepare_condor_InputDir_OutputName_FilesPerJob_configFile.sh <inputDir> <taskName> <filesPerJob> <configXML> <resultsOutputDir>"
    echo "e.g. source Prepare_condor_InputDir_OutputName_FilesPerJob_configFile.sh /storage/data/cms/store/user/jez/ZHttNtuples_v2/53X/Data/DoubleElectron_Run2012C-24Aug2012-v1/ 20130514_DoubleElectron_Run2012C-24Aug2012-v1 50 Analysis_config_T2.xml results"
    return 2
fi

mkdir -p ${2}
cd ${2}
cp ../MakeSFInputFile_condor2.sh .
source MakeSFInputFile_condor2.sh $1 $3
rm MakeSFInputFile_condor2.sh
cd ..
source Prepare_to_submit_fileNames_condor_2.sh $2 ${4}

touch ${2}_ShowStatus.sh
rm -f ${2}_ShowStatus.sh
touch ${2}_ShowStatus.sh

echo "source ShowStatus_condor.sh ${2} ${2} ${5}" >> ${2}_ShowStatus.sh

echo "To start condor, do"
echo "condor_submit ${2}.cmd"
