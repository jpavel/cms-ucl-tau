if [ "${BASH_SOURCE[0]}" = "${0}" ]; then
  echo script not sourced! Exiting...
  exit 1
fi


if [ $# -ne 3 ]; then
    echo "Wrong number of input arguments!"
    echo "Usage: source CloneTask.sh <oldName> <newName> <ConfigXML>"
    echo "e.g. source CloneTask.sh 20130918_AD_DoubleElectron_Run2012A-22Jan2013-v1 20130918_FRrev_DoubleElectron_Run2012A-22Jan2013-v1 Analysis_config_T2_MC_FRrev.xml"
    return 2
fi

oldName=${1}
newName=${2}
config=${3}

#copy submission script
#head  ${oldName}.cmd
source CleanJob.sh ${oldName}
cp ${oldName}.cmd ${newName}.cmd
sed -i 's/'${oldName}'/'${newName}'/g' ${newName}.cmd
oldConf=`ls ${oldName}/job1 | grep xml | grep Analysis`
echo "old config is " $oldConf
sed -i 's/'${oldConf}'/'${config}'/g' ${newName}.cmd 
cp -r ${oldName} ${newName}
cp ${oldName}_ShowStatus.sh ${newName}_ShowStatus.sh
sed -i 's/'${oldName}'/'${newName}'/g' ${newName}_ShowStatus.sh

# replace config files
touch files.tmp
rm -f files.tmp

find ${newName}* -name ${oldConf} > files.tmp

touch replace.sh
rm -f replace.sh
touch replace.sh

touch remove.sh
rm -f remove.sh
touch remove.sh

cp files.tmp files_n.tmp
sed -i 's/'${oldConf}'/'${config}'/g' files_n.tmp

more files.tmp | while read line
do
 file=`echo ${line}`
 echo "rm -f ${file}" >> remove.sh
done

more files_n.tmp | while read line
do
 file=`echo ${line}`
 echo "cp ${config} ${file}" >> replace.sh
done

chmod +x replace.sh
chmod +x remove.sh
./remove.sh
./replace.sh

rm -r replace.sh
rm -r remove.sh
rm -r files*tmp


