#!/bin/bash

i=0

#427

while [ "$i" != "855" ]
do
    
    
    i=$(($i+1))
 

if [ "$i" == "785" ] || [ "$i" == "472" ] || [ "$i" == "532" ] || [ "$i" == "556" ] || [ "$i" == "10" ] || [ "$i" == "464" ] || [ "$i" == "501" ] || [ "$i" == "565" ] || [ "$i" == "695" ] || [ "$i" == "738" ] || [ "$i" == "21" ] || [ "$i" == "343" ] || [ "$i" == "128" ] || [ "$i" == "392" ] || [ "$i" == "529" ] || [ "$i" == "110" ] || [ "$i" == "475" ] || [ "$i" == "613" ] || [ "$i" == "385" ] || [ "$i" == "333" ] || [ "$i" == "346" ] || [ "$i" == "429" ] || [ "$i" == "736" ] || [ "$i" == "114" ] || [ "$i" == "533" ] || [ "$i" == "805" ] || [ "$i" == "134" ] || [ "$i" == "126" ] || [ "$i" == "562" ] || [ "$i" == "476" ] || [ "$i" == "558" ] || [ "$i" == "330" ] || [ "$i" == "149" ] || [ "$i" == "294" ] || [ "$i" == "804" ] || [ "$i" == "504" ] || [ "$i" == "741" ] || [ "$i" == "698" ] || [ "$i" == "828" ] || [ "$i" == "704" ] 
then

    touch 3770_$i.sh
    touch 3770__$i.sh
    echo " 
cd /afs/ihep.ac.cn/users/z/zhangce
source Setup.sh
cd /afs/ihep.ac.cn/users/z/zhangce/WorkArea/Analysis/Psi3770piAlg/Psi3770piAlg-00-00-01/
sh make.sh
cd /afs/ihep.ac.cn/users/z/zhangce/WorkArea/Analysis/Psi3770piAlg/Psi3770piAlg-00-00-01/run/data/jobdata
boss.exe job_${i}.txt">>3770_$i.sh

echo " 
cd /afs/ihep.ac.cn/users/z/zhangce
source Setup.sh
cd /afs/ihep.ac.cn/users/z/zhangce/WorkArea/Analysis/Psi3770piAlg/Psi3770piAlg-00-00-01/
sh make.sh
cd /afs/ihep.ac.cn/users/z/zhangce/WorkArea/Analysis/Psi3770piAlg/Psi3770piAlg-00-00-01/run/data/jobdata
boss.exe job__${i}.txt">>3770__$i.sh
fi

done



