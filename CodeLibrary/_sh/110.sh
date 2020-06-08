#!/bin/bash


i=100

while [ "$i" != "500" ]
do
    cat "bsub /home/had/zhangce/G-2Statistics/run_all.sh $i" >>sub_all.sh
    i=$(($i+1))
done

