import os
import sys
argList=sys.argv
f=open('logFiles')
inPaths=f.readlines()
f.close()
r=open('resubmit')
resub_list=r.readlines()
r.close()
int_resub_list=[int(i) for i in resub_list]
print "Running jobs:"
for path in inPaths:
  jobNumber=int(path.split('/')[2][3:])
  taskName=path.split('/')[1]
  if taskName != argList[1]:
    continue
  print jobNumber
  int_resub_list.remove(jobNumber)
print "Those jobs will be resubmitted in the end: ", str(int_resub_list)
r2=open('resubmit','w')
for i in int_resub_list:
  r2.write(str(i)+"\n")
r2.close()
