touch temp1.txt
rm -f temp1.txt
touch temp2.txt
rm -f temp2.txt
touch Diff_${2}.txt
rm -f Diff_${2}.txt
more ${1} | grep ${2} | sort > temp1.txt
more FakeRate_ulb.txt | grep ${2} | sort > temp2.txt
diff -d temp1.txt temp2.txt > Diff_${2}.txt
 
