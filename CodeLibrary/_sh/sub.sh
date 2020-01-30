i=96

while [ "$i" != "205" ]
do
i=$(($i+1))
cp "rec0515.sh" "./$i/rec0515_${i}.sh"
echo "
cd /afs/ihep.ac.cn/users/z/zhangce/
source Setup.sh
cd /afs/ihep.ac.cn/users/z/zhangce/WorkArea/TestRelease/TestRelease-00-00-80/run/recraw/run/srun/${i} 
source rec0515_${i}.sh
" >> "./$i/sub_${i}.sh"
done
