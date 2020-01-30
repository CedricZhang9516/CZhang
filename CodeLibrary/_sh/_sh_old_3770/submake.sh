i=96

#427

while [ "$i" != "205" ]
do
i=$(($i+1))
echo " 
cd /afs/ihep.ac.cn/users/z/zhangce
source Setup.sh

cd /afs/ihep.ac.cn/users/z/zhangce/WorkArea/TestRelease/TestRelease-00-00-80/run/recraw/job
boss.exe ${i}.txt">>sub$i.sh
done

#for file_a in ${Folder_A}/*; do
