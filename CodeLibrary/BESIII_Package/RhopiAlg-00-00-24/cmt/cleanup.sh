if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/boss.cern.ch/slc5_amd64_gcc43/6.6.4.p01/CMT/v1r20p20090520; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then tempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=RhopiAlg -version=RhopiAlg-00-00-24 -path=/home/zhangc/work14/work664/Analysis/Physics $* >${tempfile}; . ${tempfile}
/bin/rm -f ${tempfile}

