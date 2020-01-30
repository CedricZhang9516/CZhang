#!/bin/bash

i=0

#427

while [ "$i" != "855" ]
do
    p=$(( 200 * $i ))
    p=$(($p+1))
    q=100

    i=$(($i+1))

if [ "$i" == "785" ] || [ "$i" == "472" ] || [ "$i" == "532" ] || [ "$i" == "556" ] || [ "$i" == "10" ] || [ "$i" == "464" ] || [ "$i" == "501" ] || [ "$i" == "565" ] || [ "$i" == "695" ] || [ "$i" == "738" ] || [ "$i" == "21" ] || [ "$i" == "343" ] || [ "$i" == "128" ] || [ "$i" == "392" ] || [ "$i" == "529" ] || [ "$i" == "110" ] || [ "$i" == "475" ] || [ "$i" == "613" ] || [ "$i" == "385" ] || [ "$i" == "333" ] || [ "$i" == "346" ] || [ "$i" == "429" ] || [ "$i" == "736" ] || [ "$i" == "114" ] || [ "$i" == "533" ] || [ "$i" == "805" ] || [ "$i" == "134" ] || [ "$i" == "126" ] || [ "$i" == "562" ] || [ "$i" == "476" ] || [ "$i" == "558" ] || [ "$i" == "330" ] || [ "$i" == "149" ] || [ "$i" == "294" ] || [ "$i" == "804" ] || [ "$i" == "504" ] || [ "$i" == "741" ] || [ "$i" == "698" ] || [ "$i" == "828" ] || [ "$i" == "704" ] 
then


    touch job_$i.txt
    touch job_$i.txtbak

    touch job__$i.txt
    touch job__$i.txtbak
    
    echo '

#include "$ROOTIOROOT/share/jobOptions_ReadRec.txt"
#include "$VERTEXFITROOT/share/jobOptions_VertexDbSvc.txt"
#include "$MAGNETICFIELDROOT/share/MagneticField.txt"
#include "$ABSCORROOT/share/jobOptions_AbsCor.txt"
#include "/afs/ihep.ac.cn/users/z/zhangce/WorkArea/Analysis/Psi3770piAlg/Psi3770piAlg-00-00-01/share/jobOptions_Psi3770pi.txt"

// Input REC or DST file name

EventCnvSvc.digiRootInputFile = {

    '>>job_$i.txtbak

        echo '

#include "$ROOTIOROOT/share/jobOptions_ReadRec.txt"
#include "$VERTEXFITROOT/share/jobOptions_VertexDbSvc.txt"
#include "$MAGNETICFIELDROOT/share/MagneticField.txt"
#include "$ABSCORROOT/share/jobOptions_AbsCor.txt"
#include "/afs/ihep.ac.cn/users/z/zhangce/WorkArea/Analysis/Psi3770piAlg/Psi3770piAlg-00-00-01/share/jobOptions_Psi3770pi.txt"

// Input REC or DST file name

EventCnvSvc.digiRootInputFile = {

    '>>job__$i.txtbak
     
    cat data_all_3770.txt| tail -n +$p | head -n $q >>job_$i.txtbak

    pp=$(($p+100))

    cat data_all_3770.txt| tail -n +$pp | head -n $q >>job__$i.txtbak  

    sed '$d' "job_${i}.txtbak">>job_$i.txt
    sed '$d' "job__${i}.txtbak">>job__$i.txt       

    echo '
    };

// Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL )
MessageSvc.OutputLevel = 5;

// Number of events to be processed (default is 10)
ApplicationMgr.EvtMax = 80000000;

ApplicationMgr.HistogramPersistency = "ROOT";
Psi3770pi.OutputFileName = "/afs/ihep.ac.cn/users/z/zhangce/store/3770data_\c'>>job_$i.txt

    echo '
    };

// Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL )
MessageSvc.OutputLevel = 5;

// Number of events to be processed (default is 10)
ApplicationMgr.EvtMax = 80000000;

ApplicationMgr.HistogramPersistency = "ROOT";
Psi3770pi.OutputFileName = "/afs/ihep.ac.cn/users/z/zhangce/store/3770data_\c'>>job__$i.txt

    echo "${i}\c">>job_$i.txt
    echo "${i}_\c">>job__$i.txt
    
    echo '.root";'>>job_$i.txt
    echo '.root";'>>job__$i.txt
fi

done