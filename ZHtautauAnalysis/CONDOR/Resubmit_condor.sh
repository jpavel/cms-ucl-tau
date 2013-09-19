head -n 21 ${2}.cmd > ${2}_resubmit.cmd
touch argu
rm -f argu
touch argu
head -n 23 ${2}.cmd | tail -n 1 > argu 
more ${1} |while read line
do
  file=`echo $line`
  echo "Submitting job ${file} ... "
  echo "Initialdir     = ${2}/job${file}" >>  ${2}_resubmit.cmd
  cat argu >> ${2}_resubmit.cmd
  echo " queue 1" >> ${2}_resubmit.cmd
  rm -f ${2}/job${file}/condor.*
  rm -f ${2}/job${file}/Analysis.Data1.Reco.root 
  rm -f ${2}/job${file}/*.txt
  rm -f ${2}/job${file}/*.csv
#  sed -i 's/glidein/ZHttNtuples\/52X\/Data/g' ${file}.sh
#  cp *.sh ${file}.sh
#  srmrm srm://maite.iihe.ac.be${3}/output_Ntuples_${file}_0_abc.root
#  qsub -q localgrid@cream02 -o script.stdout -e script.stderr ${2}_${file}.sh
#  cd ../..
done
rm argu
condor_submit ${2}_resubmit.cmd
