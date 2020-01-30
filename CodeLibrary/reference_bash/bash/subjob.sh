#!/bin/bash
#sub jobs

I=10101
#The number of jobs
C=100

for ((i=$I;i<$I+$C;++i))
do
    NUM=`echo $i |cut -c 3-5`
    #The name of job,need to be changed
    boss -q ana_$NUM.txt
    echo $NUM
done
