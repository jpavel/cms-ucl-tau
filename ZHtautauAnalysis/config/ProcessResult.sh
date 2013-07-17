time=` date "+%Y_%m_%d_%H%m"`
more events.txt | awk '{print $1 ,$2 ,$3 ,$4 ,$5 ,$6 ,$7 ,$8 }' > events_${time}.txt