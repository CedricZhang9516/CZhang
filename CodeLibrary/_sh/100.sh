#!/bin/bash

i=0

#427

while [ "$i" != "427" ]
do
    
    p=$(( 200 * $i ))
    p=$(($p+1))
    q=200
    
    i=$(($i+1))
    
    touch $i.txt
    echo '

#include "$ROOTIOROOT/share/jobOptions_ReadRec.txt"
#include "$VERTEXFITROOT/share/jobOptions_VertexDbSvc.txt"
#include "$MAGNETICFIELDROOT/share/MagneticField.txt"
#include "$ABSCORROOT/share/jobOptions_AbsCor.txt"
#include "/afs/ihep.ac.cn/users/z/zhangce/WorkArea/Analysis/Psi3770piAlg/Psi3770piAlg-00-00-01/share/jobOptions_Psi3770pi.txt"

EventCnvSvc.digiRootInputFile = {

    '>>$i.txt
     
    cat data_all.txt| tail -n +$p | head -n $q >>$i.txt         

    echo '
    };
    // Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL )
    MessageSvc.OutputLevel = 5;

    // Number of events to be processed (default is 10)
    ApplicationMgr.EvtMax = 100000000;

    ApplicationMgr.HistogramPersistency = "ROOT";
    Psi3770pi.OutputFileName = "pi0411_'>>$i.txt

    echo $i>>$i.txt
    
    echo '.root";'>>$i.txt
done


