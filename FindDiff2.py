import os,sys
from subprocess import call
argList=sys.argv
infile=open(argList[1])
per_row = []

eventlist =[]
for line in infile:
    eventlist.append(line)
    
#print per_row

#~ for row in per_row:
	#~ #print row
	#~ myevent = []
	#~ myevent.append(int(row[0]))
	#~ myevent.append(int(row[1]))
	#~ myevent.append(int(row[2]))
	#~ eventlist.append(myevent)
	


print eventlist
#~ 
infile2=open(argList[2])
#~ per_row2 = []
#~ 
eventlist2 =[]
for line in infile2:
    eventlist2.append(line)
    
#~ #print per_row2
#~ 
#~ for row in per_row2:
	#~ #print row
	#~ myevent = []
	#~ myevent.append(int(row[0]))
	#~ myevent.append(int(row[1]))
	#~ myevent.append(int(row[2]))
	#~ eventlist2.append(myevent)
	#~ 
#~ 
#~ 
print eventlist2
#~ 
commF = open('Common.list', 'w')
f1specific = open('File1Spec.list','w')
for val in eventlist:
	print val
	#~ comm=str(val[0])+':'+str(val[1])+':'+str(val[2])+'\n'
	if val in eventlist2:
		#print comm
		commF.write(val)
	else:
		f1specific.write(val)
		
commF2 = open('Common2.list', 'w')
f2specific = open('File2Spec.list','w')
for val in eventlist2:
	print val
	if val in eventlist:
		commF2.write(val)
	else:
		f2specific.write(val)
		


