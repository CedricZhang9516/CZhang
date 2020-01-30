i=53

#427

Folder_A="/afs/ihep.ac.cn/users/z/zhangce/store/srun"


for file_a in ${Folder_A}/*; do

temp_file1=`basename $file_a`

echo "\"/afs/ihep.ac.cn/users/z/zhangce/store/srun/${temp_file1}\"," >>record.txt
#echo ${file_a}
done