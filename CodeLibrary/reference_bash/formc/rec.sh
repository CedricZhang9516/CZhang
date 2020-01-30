#!/bin/bash
#Get rec_joboptions!

I=10101
C=100

for ((i=$I;i<$I+$C;++i))
do
    NUM=`echo $i |cut -c 3-5`
    name=rec.txt
    cat $name>rec_$NUM.txt
    sed "s/NUM/$NUM/g" rec_$NUM.txt -i
    boss -q rec_$NUM.txt
    echo $NUM
done


