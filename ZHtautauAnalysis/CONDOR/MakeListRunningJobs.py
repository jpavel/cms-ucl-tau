import os
f=open('logFiles')
inPaths=f.readlines()
f.close()
for path in inPaths:
  jobNumber=path.split('/')[2][3:]
  taskName=path.split('/')[1]
  outName=taskName+'.running'
  out=open(outName,'a+')
  out.write(jobNumber+'\n')
