#!/bin/bash
#sum the results of all jobs if the job ends successfully.

I=10001
C=60
suma=0
am="ApplicationMgr       INFO Application Manager Stopped successfully"

for ((i=$I;i<$I+$C;++i))
do
    NUM=`echo $i |cut -c 3-5`
    name=job_$NUM.txt.bosslog
    ap=`tail -8 $name |head -1`
    if [ "$ap" = "$am" ];then
    a=`tail -7 $name |head -1 |cut -c 23-30`
    b=`tail -6 $name |head -1 |cut -c 23-30`
    c=`tail -5 $name |head -1 |cut -c 23-30`
    d=`tail -4 $name |head -1 |cut -c 23-30`
    suma=$((suma+$a))
    sumb=$((sumb+$b))
    sumc=$((sumc+$c))
    sumd=$((sumd+$d))
    fi
done
echo "suma=$suma"
echo "sumb=$sumb"
echo "sumc=$sumc"
echo "sumd=$sumd"


