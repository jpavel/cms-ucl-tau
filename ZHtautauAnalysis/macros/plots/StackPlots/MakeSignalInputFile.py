import os,sys
from subprocess import call
argList=sys.argv
f=open(argList[1])
inFiles=f.read().splitlines()
print inFiles
