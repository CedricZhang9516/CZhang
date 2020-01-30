#-- start of make_header -----------------

#====================================
#  Document MumuAlg_check_install_runtime
#
#   Generated Tue Oct 27 17:01:32 2015  by zhangc
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_MumuAlg_check_install_runtime_has_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MumuAlg_check_install_runtime_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MumuAlg_check_install_runtime

MumuAlg_tag = $(tag)

#cmt_local_tagfile_MumuAlg_check_install_runtime = $(MumuAlg_tag)_MumuAlg_check_install_runtime.make
cmt_local_tagfile_MumuAlg_check_install_runtime = $(bin)$(MumuAlg_tag)_MumuAlg_check_install_runtime.make

else

tags      = $(tag),$(CMTEXTRATAGS)

MumuAlg_tag = $(tag)

#cmt_local_tagfile_MumuAlg_check_install_runtime = $(MumuAlg_tag).make
cmt_local_tagfile_MumuAlg_check_install_runtime = $(bin)$(MumuAlg_tag).make

endif

include $(cmt_local_tagfile_MumuAlg_check_install_runtime)
#-include $(cmt_local_tagfile_MumuAlg_check_install_runtime)

ifdef cmt_MumuAlg_check_install_runtime_has_target_tag

cmt_final_setup_MumuAlg_check_install_runtime = $(bin)setup_MumuAlg_check_install_runtime.make
#cmt_final_setup_MumuAlg_check_install_runtime = $(bin)MumuAlg_MumuAlg_check_install_runtimesetup.make
cmt_local_MumuAlg_check_install_runtime_makefile = $(bin)MumuAlg_check_install_runtime.make

else

cmt_final_setup_MumuAlg_check_install_runtime = $(bin)setup.make
#cmt_final_setup_MumuAlg_check_install_runtime = $(bin)MumuAlgsetup.make
cmt_local_MumuAlg_check_install_runtime_makefile = $(bin)MumuAlg_check_install_runtime.make

endif

cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)MumuAlgsetup.make

#MumuAlg_check_install_runtime :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'MumuAlg_check_install_runtime'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MumuAlg_check_install_runtime/
#MumuAlg_check_install_runtime::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of cmt_action_runner_header ---------------

ifdef ONCE
MumuAlg_check_install_runtime_once = 1
endif

ifdef MumuAlg_check_install_runtime_once

MumuAlg_check_install_runtimeactionstamp = $(bin)MumuAlg_check_install_runtime.actionstamp
#MumuAlg_check_install_runtimeactionstamp = MumuAlg_check_install_runtime.actionstamp

MumuAlg_check_install_runtime :: $(MumuAlg_check_install_runtimeactionstamp)
	$(echo) "MumuAlg_check_install_runtime ok"
#	@echo MumuAlg_check_install_runtime ok

$(MumuAlg_check_install_runtimeactionstamp) :: $(MumuAlg_check_install_runtime_dependencies)
	$(silent) /cvmfs/boss.cern.ch/slc5_amd64_gcc43/6.6.4.p01/dist/6.6.4.p01/BesPolicy/BesPolicy-01-05-03/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/ClusterDisks/HDN14/WorkSpace/zhangc/work664/InstallArea/share
	$(silent) cat /dev/null > $(MumuAlg_check_install_runtimeactionstamp)
#	@echo ok > $(MumuAlg_check_install_runtimeactionstamp)

MumuAlg_check_install_runtimeclean ::
	$(cleanup_silent) /bin/rm -f $(MumuAlg_check_install_runtimeactionstamp)

else

MumuAlg_check_install_runtime :: $(MumuAlg_check_install_runtime_dependencies)
	$(silent) /cvmfs/boss.cern.ch/slc5_amd64_gcc43/6.6.4.p01/dist/6.6.4.p01/BesPolicy/BesPolicy-01-05-03/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/ClusterDisks/HDN14/WorkSpace/zhangc/work664/InstallArea/share

endif

install ::
uninstall ::

#-- end of cmt_action_runner_header -----------------
#-- start of cleanup_header --------------

clean :: MumuAlg_check_install_runtimeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(MumuAlg_check_install_runtime.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
	if echo $@ | grep '$(package)setup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(MumuAlg_check_install_runtime.make): $@: File no longer generated" >&2; exit 0; fi
else
.DEFAULT::
	$(echo) "(MumuAlg_check_install_runtime.make) PEDANTIC: $@: No rule for such target" >&2
	if echo $@ | grep '$(package)setup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(MumuAlg_check_install_runtime.make): $@: File no longer generated" >&2; exit 0;\
	 elif test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_MumuAlg_check_install_runtime)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(MumuAlg_check_install_runtime.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr $@ : '.*/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(MumuAlg_check_install_runtime.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(MumuAlg_check_install_runtime.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

MumuAlg_check_install_runtimeclean ::
#-- end of cleanup_header ---------------
