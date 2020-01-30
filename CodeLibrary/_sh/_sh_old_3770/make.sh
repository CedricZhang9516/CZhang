i=0

#427

Folder_A="/Users/zhangce/hep_work/work_3770/job_num/run_num_txt"

while [ "$i" != "300" ]
do
i=$(($i+1))
mkdir "./run_num_txt/${i}"
j=0

for file_a in ${Folder_A}/*.txt; do
temp_file1=`basename $file_a`

if [ "$j" != "11" ]
then
mv "./run_num_txt/${temp_file1}" "./run_num_txt/$i"
j=$(($j+1))
else
break
fi
                           
done


done

#for file_a in ${Folder_A}/*; do
