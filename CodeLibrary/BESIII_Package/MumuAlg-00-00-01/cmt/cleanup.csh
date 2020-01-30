if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/boss.cern.ch/slc5_amd64_gcc43/6.6.4.p01/CMT/v1r20p20090520
endif
source ${CMTROOT}/mgr/setup.csh
set tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set tempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=MumuAlg -version=MumuAlg-00-00-01 -path=/home/zhangc/work14/work664/Analysis/Physics $* >${tempfile}; source ${tempfile}
/bin/rm -f ${tempfile}

