#!/bin/bash

i=0

#427

while [ "$i" != "427" ]
do
    
    p=$(( 200 * $i ))
    p=$(($p+1))
    q=200
    
    i=$(($i+1))
    
    touch $i.sh
    echo " 
cd /afs/ihep.ac.cn/users/z/zhangce
source Setup.sh
cd /afs/ihep.ac.cn/users/z/zhangce/WorkArea/Analysis/Psi3770piAlg/Psi3770piAlg-00-00-01/cmt
cmt br cmt config
cmt br make
cd /afs/ihep.ac.cn/users/z/zhangce/WorkArea/Analysis/Psi3770piAlg/Psi3770piAlg-00-00-01/run/job
boss.exe ${i}.txt">>$i.sh
done



