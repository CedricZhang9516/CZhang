i=96

while [ "$i" != "205" ]
do
i=$(($i+1))
cd "/afs/ihep.ac.cn/users/z/zhangce/WorkArea/TestRelease/TestRelease-00-00-80/run/recraw/run/srun/$i" 
mv *.raw /afs/ihep.ac.cn/users/z/zhangce/WorkArea/TestRelease/TestRelease-00-00-80/run/recraw/run/_raw
#qsub -q besq sub_${i}.sh
#rm sub_*.sh
done
