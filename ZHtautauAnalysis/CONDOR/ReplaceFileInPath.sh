#!/bin/zsh

fileName=${1}
path=${2}
echo ${fileName}
find ${2}* -name ${fileName} > files.tmp

touch replace.sh
rm -f replace.sh
touch replace.sh

more files.tmp | while read line
do
 file=`echo ${line}`
 echo "cp ${fileName} ${file}" >> replace.sh
done

chmod +x replace.sh
./replace.sh

rm -r replace.sh
