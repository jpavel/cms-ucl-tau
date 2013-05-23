#!/bin/bash

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
