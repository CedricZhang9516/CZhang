#!/bin/bash
#Get sim_joboptions!

I=10101
C=100

for ((i=$I;i<$I+$C;++i))
do
    NUM=`echo $i |cut -c 3-5`
    SEED=`echo $i |cut -c 3-5`
    name=psipp_sim.txt
    cat $name>sim_$NUM.txt
    sed "s/NUM/$NUM/g" sim_$NUM.txt -i
    boss -q sim_$NUM.txt
    echo $NUM
done


