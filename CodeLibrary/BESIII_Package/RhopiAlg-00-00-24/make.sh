#!/bin/bash
#
#===============================================================================
#   FILENAME:         make.sh
#   AUTHOR:           Fengyun Li,lfypku@gmail.com
#   CREATED:          2014年09月17日 12时16分23秒 CST
#   DESCRIPTION: 
#===============================================================================

cd cmt
cmt br cmt config
cmt br make
source setup.sh

