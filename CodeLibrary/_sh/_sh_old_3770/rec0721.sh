

  
    Folder_B="/besfs/groups/grid/zhanggang/2013SepSimulation/psipp/664p01/mc/qqbar/round03/stream001/"
    temp_file3=""
    for file_b in ${Folder_B}/*; do
 	
	temp_file2=`basename $file_b`
	temp_file2="${temp_file2}" | rev | awk -F \_ '{print $3}' | rev	    
	temp_file2="${temp_file2#*_}"
	temp_file2="${temp_file2%%_*}"
	temp_file2="${temp_file2#*000}"
    if [ "${temp_file3}" != "${temp_file2}" ]
    echo "${temp_file2}"
	then
	temp_file3="${temp_file2}" 
	#run_ 23418 .txt
	if [ -f "run_${temp_file3}.txt"  ]
	then
	raw_evt_filter.exe "run_${temp_file3}.txt" "/besfs/groups/grid/zhanggang/2013SepSimulation/psipp/664p01/mc/qqbar/round03/stream001/664p01_psipp_qqbar_stream001_run${temp_file3}_file*.rtraw"
        fi
    fi    

    done
  
