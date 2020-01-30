#!/bin/bash
#Get ana_joboptions!

I=10101
C=100


for ((i=$I;i<$I+$C;++i))
do
    NUM=`echo $i |cut -c 3-5`
    name=ana.txt
    cat $name>ana_$NUM.txt
    sed "s/NUM/$NUM/g" ana_$NUM.txt -i
    boss -q ana_$NUM.txt
    echo $NUM
done


