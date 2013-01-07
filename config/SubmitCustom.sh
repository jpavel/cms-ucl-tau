more ${1} |while read line
do
  file=`echo $line`
  cd ${file}
  echo "Submitting job ${file} ... "
  sed -i 's/glidein/ZHttNtuples\/53X\/Data/g' ${file}.sh
#  cp *.sh ${file}.sh
  qsub -q localgrid@cream02 -o script.stdout -e script.stderr ${file}.sh
  cd ..
done
