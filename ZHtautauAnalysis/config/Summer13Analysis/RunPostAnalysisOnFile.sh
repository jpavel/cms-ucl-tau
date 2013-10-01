inFile=${1}
touch inputPA.xml
rm -f inputPA.xml
touch inputPA.xml
echo "<In FileName=\"${1}\" Lumi=\"1.0\" />" >> inputPA.xml 
sframe_main PostAnalysis_customInput_config.xml

cp PostAnalysis.Data1.Reco.root ${1}_PA.root