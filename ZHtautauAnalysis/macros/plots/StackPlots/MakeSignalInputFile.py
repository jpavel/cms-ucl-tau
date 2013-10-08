import os,sys
from subprocess import call
argList=sys.argv
infile=open(argList[1])
per_row = []
for line in infile:
    per_row.append(line.split('\t'))

#print per_row
per_column=zip(*per_row)
#print per_column

ZH_prefix='signal_ZH_HToTauTau_M-'
ZH_suffix='_lepdecay_8TeV-pythia6-tauola'
ZH_short='ZH_htt'
outF = open('Signalinput.txt', 'w')
for row in per_row:
	mass=float(row[0])
	if mass%5==0:
		line=ZH_short+row[0]+" "+ZH_prefix+row[0]+ZH_suffix+" "+row[1]
		print line
		outF.write(line)

infileW=open(argList[2])
per_rowW = []
for line in infileW:
    per_rowW.append(line.split('\t'))
WW_prefix='signal_WH_ZH_TTH_HToWW_M-'
WW_suffix='_lepdecay_8TeV-pythia6-tauola'
WW_short='ZH_hww'
for rowW in per_rowW:
	massW=float(rowW[0])
	if (massW%10==0 or massW==125):
		line=WW_short+rowW[0]+" "+WW_prefix+rowW[0]+WW_suffix+" "+rowW[1]
		print line
		outF.write(line)




#inFiles=f.read().splitlines()
#print inFiles
