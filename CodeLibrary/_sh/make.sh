i=0

#427

Folder_A="/Users/zhangce/hep_work/work_etac/offline_ana/ana_cxx"

while [ "$i" != "200" ]
do
i=$(($i+1))
mkdir "./ana_cxx/${i}"
j=0

for file_a in ${Folder_A}/*.txt; do
temp_file1=`basename $file_a`

if [ "$j" != "11" ]
then
mv "./ana_cxx/${temp_file1}" "./ana_cxx/$i"
j=$(($j+1))
else
break
fi
                           
done


done

#for file_a in ${Folder_A}/*; do
