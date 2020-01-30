#!/bin/bash

cd cmt
cmt br cmt config
cmt br make
source setup.sh

#cd ../run/
#boss.exe job_001.txt
