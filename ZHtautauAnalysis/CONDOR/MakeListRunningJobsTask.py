import os
import sys
argList=sys.argv
f=open('logFiles')
inPaths=f.readlines()
f.close()
for path in inPaths:
  jobNumber=path.split('/')[2][3:]
  taskName=path.split('/')[1]
  if taskName != argList[1]:
    continue
  outName=taskName+'.running'
  out=open(outName,'a+')
  out.write(jobNumber+'\n')
