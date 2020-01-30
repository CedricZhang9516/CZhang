i=53

#427

Folder_A="/Users/zhangce/hep_work/work_pe/root/bhabha_mc/bhabha2"


for file_a in ${Folder_A}/*; do
i=$(($i+1))

temp_file1=`basename $file_a`

mv "./bhabha_mc/bhabha2/${temp_file1}" "./bhabha_mc/bhabha2/bhabha_$i.root"
#echo ${temp_file1}
#echo ${file_a}
done

#for file_a in ${Folder_A}/*; do
