i=0

#427

Folder_A="/Users/zhangce/hep_work/work_3770/job_num/run_num_txt"

while [ "$i" != "303" ]
do
i=$(($i+1))
#mkdir "./ana_cxx/${i}"
#j=0
echo '
//input data
#include "$RAWDATACNVROOT/share/ReadRawDatajobOptions.txt"
#include "$TRIGMAKERALGROOT/share/jobOptions_TrigMakerAlg.txt"
#include "$OFFLINEEVENTLOOPMGRROOT/share/OfflineEventLoopMgr_Option.txt"
#include "$CALIBSVCROOT/share/job-CalibData.txt"
#include "$MAGNETICFIELDROOT/share/MagneticField.txt"
#include "$ESTIMEALGROOT/share/job_EsTimeAlg.txt"

// PAT+TSF method for MDC reconstruction
#include "$MDCXRECOROOT/share/jobOptions_MdcPatTsfRec.txt"

#include "$KALFITALGROOT/share/job_kalfit_numf_data.txt"
#include "$MDCDEDXALGROOT/share/job_dedx_all.txt"
#include "$TRKEXTALGROOT/share/TrkExtAlgOption.txt"
#include "$TOFRECROOT/share/jobOptions_TofRec_Data.txt"
#include "$TOFENERGYRECROOT/share/TofEnergyRecOptions_Data.txt"
#include "$EMCRECROOT/share/EmcRecOptions.txt"
#include "$EMCTIMERECROOT/share/EmcTimeRecOptions.txt"

#include "$MUCRECALGROOT/share/jobOptions_MucRec.txt"

#include "$HLTMAKERALGROOT/share/jobOptions_HltMakerAlg.txt"

#include "$EVENTASSEMBLYROOT/share/EventAssembly.txt"
#include "$PRIMARYVERTEXALGROOT/share/jobOptions_kalman.txt"
#include "$VEEVERTEXALGROOT/share/jobOptions_veeVertex.txt"

//output ROOT DST data
#include "$EVENTPRESELECTROOT/share/jobOptions_EventPreSelect.txt"
//#include "$ROOTIOROOT/share/jobOptions_Dst2Root_data.txt"
#include "$ROOTIOROOT/share/jobOptions_Rec2Root_data.txt"
//configure for calibration constants
#include "$CALIBSVCROOT/share/calibConfig_rec_data.txt"


//Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL )
MessageSvc.OutputLevel = 5;

//input data file
RawDataInputSvc.InputFiles={

' >> "${Folder_A}/recraw_${i}.txtbak"


for file_a in ${Folder_A}/${i}/*.txt; do
temp_file1=`basename $file_a`

#if [ "$j" != "11" ]
#then
#mv "./ana_cxx/${temp_file1}" "./ana_cxx/$i"
echo ' 
"/afs/ihep.ac.cn/users/z/zhangce/WorkArea/TestRelease/TestRelease-00-00-80/run/recraw/run/_raw/\c' >> "${Folder_A}/recraw_${i}.txtbak"

echo "${temp_file1}.raw\c">>"${Folder_A}/recraw_${i}.txtbak"

echo '"'>>"${Folder_A}/recraw_${i}.txtbak"
echo ','>>"${Folder_A}/recraw_${i}.txtbak"
                   
done


#A=$(sed -n '$=' "${Folder_A}/${i}.txtbak")
#sed  $(($A-1+1)),${A}d "${Folder_A}/${i}.txtbak" >>"${Folder_A}/${i}.txt"
sed '$d' "${Folder_A}/recraw_${i}.txtbak">>"${Folder_A}/recraw_${i}.txt"
#sed '$d' "${Folder_A}/${i}.txt"
echo '};
//output data file
EventPreSelect.WriteRec=true;
WriteRec.digiRootOutputFile="/afs/ihep.ac.cn/users/z/zhangce/WorkArea/TestRelease/TestRelease-00-00-80/run/recraw/rec0517/rec_'>>"${Folder_A}/recraw_${i}.txt"
echo "${i}.rec">>"${Folder_A}/recraw_${i}.txt"
echo ' ";'>> "${Folder_A}/recraw_${i}.txt"
echo 'EventCnvSvc.digiRootOutputFile="/afs/ihep.ac.cn/users/z/zhangce/WorkArea/TestRelease/TestRelease-00-00-80/run/recraw/rec0517/rec_'>>"${Folder_A}/recraw_${i}.txt"
echo "${i}.tmp">>"${Folder_A}/recraw_${i}.txt"
echo '";
//Number of events to be processed (default is 10)
ApplicationMgr.EvtMax = 100000;'>>"${Folder_A}/recraw_${i}.txt"

done

#for file_a in ${Folder_A}/*; do
