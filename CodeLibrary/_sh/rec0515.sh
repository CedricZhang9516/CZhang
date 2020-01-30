Folder_A="/bes3fs/offline/data/raw/round04/"  
for file_a in ${Folder_A}/*; do  
    temp_file1=`basename $file_a`
  
    Folder_B="/bes3fs/offline/data/raw/round04/${temp_file1}"
    temp_file3=""
    for file_b in ${Folder_B}/*; do
 	
	temp_file2=`basename $file_b`
	temp_file2="${temp_file2}" | rev | awk -F \_ '{print $1}' | rev	    
	temp_file2="${temp_file2#*_}"
	temp_file2="${temp_file2%%_*}"
	temp_file2="${temp_file2#*00}"
    if [ "${temp_file3}" != "${temp_file2}" ]
	then
	temp_file3="${temp_file2}" 
	#run_ 23418 .txt
	if [ -f "run_${temp_file3}.txt"  ]
	then
	raw_evt_filter.exe "run_${temp_file3}.txt" "/bes3fs/offline/data/raw/round04/${temp_file1}/run_00${temp_file3}_All_*.raw"
        fi
    fi    

    done
done  
