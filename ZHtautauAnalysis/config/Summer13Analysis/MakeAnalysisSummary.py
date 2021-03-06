import os
import sys
from subprocess import call
from subprocess import Popen

argList=sys.argv

if 'SFRAME_DIR' in os.environ:
	print 'Sframe defined!'
else:
	print 'Define SFrame first!'
	sys.exit(1)

if 'ROOTSYS' in os.environ:
	print 'ROOT defined!'
else:
	print 'Define ROOT first!'
	sys.exit(1)
		
if len(argList) < 2:
	print 'Please provide input directory!'
	sys.exit(1)

inputDir=argList[1]
sep='/'
MotherDir=sep.join(argList[1].split('/')[:-2])
outDir=''
if len(argList)> 2:
	outDir=argList[2]
else:
	outDir='MySummary'
print 'The input dir is '+inputDir
outFullDir=MotherDir+'/'+outDir
print 'The output will be saved in '+outFullDir


for subdir in os.listdir(inputDir):
	print subdir
	if os.path.isdir(inputDir+subdir):
		print subdir
		sep2='_'
		if len(subdir.split('_'))>2:
			sample=sep2.join(subdir.split('_')[2:])
		else:
			sample=sep2.join(subdir.split('_')[1:])
		print sample
		outSampleDir=outFullDir+'/'+sample
		call(['mkdir','-p',outSampleDir])
		infile=inputDir+subdir+'/'+subdir+'_histo.root'
		#print infile
		if not os.path.exists(infile):
			print 'File'+infile+' not found!'
			continue
		#print 'REPEAT2'+infile
		inputF = open('inputPA.xml', 'w')
		SFinLine='<In FileName="'+infile+'" Lumi="1.0" />\n'
		#print 'Writing'+SFinLine
		inputF.write(SFinLine)
		inputF.close()
		#call(['more','inputPA.xml'])
		call(['sframe_main','PostAnalysis_customInput_config.xml'])
		call(['cp', 'PostAnalysis.Data1.Reco.root',outSampleDir+'/Summary.root']) 



