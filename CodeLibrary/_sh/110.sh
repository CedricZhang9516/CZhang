#!/bin/bash

k=1
i=0
m=0
p=1

while [ "$i" != "2" ]
do 
    m=$(($i+$p))
    echo $(( $m * 2 ))
    cat data_all.txt| tail -n +$p | head -n $m >>$m.txt
    i=$(($i+1))
done

