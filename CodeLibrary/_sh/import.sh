#!/bin/bash

for file in `ls /bes3fs/offline/data/664-1/psipp/dst/`
do 
cd /bes3fs/offline/data/664-1/psipp/dst/"$file"
	for x in `ls /bes3fs/offline/data/664-1/psipp/dst/"$file"`
	do
	echo $PWD/"$x">>/afs/ihep.ac.cn/users/z/zhangce/store/data.txt	
done
done

echo "all is ok"
