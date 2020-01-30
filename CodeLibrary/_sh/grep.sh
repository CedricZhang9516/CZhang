i=0

#427

while [ "$i" != "92" ]
do
    i=$(($i+1))
   grep "After Kinematic Fit" $i.sh.o* >>4c.txt 
#After charged track cut: 1408642
#After photon cut: 443693
#After PID: 443075
#After Vertex Fit:443049
#After Kinematic Fit:2458 
done
