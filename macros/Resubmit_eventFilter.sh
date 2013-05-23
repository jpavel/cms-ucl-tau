more ${1} |while read line
do
  file=`echo $line`
  cd ${2}/job${file}
  echo "Submitting job ${file} ... "
  qsub -q localgrid@cream02 -o script.stdout -e script.stderr ${2}_${file}.sh
  cd ../..
done
