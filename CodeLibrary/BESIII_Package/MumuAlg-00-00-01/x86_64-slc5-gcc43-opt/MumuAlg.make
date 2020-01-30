#-- start of make_header -----------------

#====================================
#  Library MumuAlg
#
#   Generated Tue Oct 27 17:01:17 2015  by zhangc
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_MumuAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MumuAlg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MumuAlg

MumuAlg_tag = $(tag)

#cmt_local_tagfile_MumuAlg = $(MumuAlg_tag)_MumuAlg.make
cmt_local_tagfile_MumuAlg = $(bin)$(MumuAlg_tag)_MumuAlg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

MumuAlg_tag = $(tag)

#cmt_local_tagfile_MumuAlg = $(MumuAlg_tag).make
cmt_local_tagfile_MumuAlg = $(bin)$(MumuAlg_tag).make

endif

include $(cmt_local_tagfile_MumuAlg)
#-include $(cmt_local_tagfile_MumuAlg)

ifdef cmt_MumuAlg_has_target_tag

cmt_final_setup_MumuAlg = $(bin)setup_MumuAlg.make
#cmt_final_setup_MumuAlg = $(bin)MumuAlg_MumuAlgsetup.make
cmt_local_MumuAlg_makefile = $(bin)MumuAlg.make

else

cmt_final_setup_MumuAlg = $(bin)setup.make
#cmt_final_setup_MumuAlg = $(bin)MumuAlgsetup.make
cmt_local_MumuAlg_makefile = $(bin)MumuAlg.make

endif

cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)MumuAlgsetup.make

#MumuAlg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'MumuAlg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MumuAlg/
#MumuAlg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

MumuAlglibname   = $(bin)$(library_prefix)MumuAlg$(library_suffix)
MumuAlglib       = $(MumuAlglibname).a
MumuAlgstamp     = $(bin)MumuAlg.stamp
MumuAlgshstamp   = $(bin)MumuAlg.shstamp

MumuAlg :: dirs  MumuAlgLIB
	$(echo) "MumuAlg ok"

#-- end of libary_header ----------------

MumuAlgLIB :: $(MumuAlglib) $(MumuAlgshstamp)
	@/bin/echo "------> MumuAlg : library ok"

$(MumuAlglib) :: $(bin)Mumu.o $(bin)Mumu_entries.o $(bin)Mumu_load.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(MumuAlglib) $?
	$(lib_silent) $(ranlib) $(MumuAlglib)
	$(lib_silent) cat /dev/null >$(MumuAlgstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(MumuAlglibname).$(shlibsuffix) :: $(MumuAlglib) $(MumuAlgstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" MumuAlg $(MumuAlg_shlibflags)

$(MumuAlgshstamp) :: $(MumuAlglibname).$(shlibsuffix)
	@if test -f $(MumuAlglibname).$(shlibsuffix) ; then cat /dev/null >$(MumuAlgshstamp) ; fi

MumuAlgclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)Mumu.o $(bin)Mumu_entries.o $(bin)Mumu_load.o

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

ifeq ($(INSTALLAREA),)
installarea = $(CMTINSTALLAREA)
else
ifeq ($(findstring `,$(INSTALLAREA)),`)
installarea = $(shell $(subst `,, $(INSTALLAREA)))
else
installarea = $(INSTALLAREA)
endif
endif

install_dir = ${installarea}/${CMTCONFIG}/lib
MumuAlginstallname = $(library_prefix)MumuAlg$(library_suffix).$(shlibsuffix)

MumuAlg :: MumuAlginstall

install :: MumuAlginstall

MumuAlginstall :: $(install_dir)/$(MumuAlginstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(MumuAlginstallname) :: $(bin)$(MumuAlginstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(MumuAlginstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(MumuAlginstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(MumuAlginstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(MumuAlginstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(MumuAlginstallname) $(install_dir)/$(MumuAlginstallname); \
	      echo `pwd`/$(MumuAlginstallname) >$(install_dir)/$(MumuAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(MumuAlginstallname), no installation directory specified"; \
	  fi; \
	fi

MumuAlgclean :: MumuAlguninstall

uninstall :: MumuAlguninstall

MumuAlguninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(MumuAlginstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(MumuAlginstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(MumuAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(MumuAlginstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),MumuAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)

#$(bin)MumuAlg_dependencies.make :: dirs

ifndef QUICK
$(bin)MumuAlg_dependencies.make : $(src)Mumu.cxx $(src)components/Mumu_entries.cxx $(src)components/Mumu_load.cxx $(use_requirements) $(cmt_final_setup_MumuAlg)
	$(echo) "(MumuAlg.make) Rebuilding $@"; \
	  $(build_dependencies) MumuAlg -all_sources -out=$@ $(src)Mumu.cxx $(src)components/Mumu_entries.cxx $(src)components/Mumu_load.cxx
endif

#$(MumuAlg_dependencies)

-include $(bin)MumuAlg_dependencies.make

endif
endif
#-- end of dependency -------------------
#-- start of cpp_library -----------------

ifneq ($(cppdepflags),)

ifneq ($(MAKECMDGOALS),MumuAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Mumu.d

$(bin)$(binobj)Mumu.d : $(use_requirements) $(cmt_final_setup_MumuAlg)

$(bin)$(binobj)Mumu.d : $(src)Mumu.cxx
	$(dep_echo) $@
	$(cpp_silent) $(cppcomp) $(cppdepflags) -o $(@D)/Mumu.dep $(use_pp_cppflags) $(MumuAlg_pp_cppflags) $(lib_MumuAlg_pp_cppflags) $(Mumu_pp_cppflags) $(use_cppflags) $(MumuAlg_cppflags) $(lib_MumuAlg_cppflags) $(Mumu_cppflags) $(Mumu_cxx_cppflags)  $(src)Mumu.cxx
	$(cpp_silent) $(format_dependencies) $@ $(@D)/Mumu.o $(src)Mumu.cxx $(@D)/Mumu.dep
endif
endif

$(bin)$(binobj)Mumu.o : $(src)Mumu.cxx
else
$(bin)MumuAlg_dependencies.make : $(Mumu_cxx_dependencies)

$(bin)$(binobj)Mumu.o : $(Mumu_cxx_dependencies)
endif
	$(cpp_echo) $(src)Mumu.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(MumuAlg_pp_cppflags) $(lib_MumuAlg_pp_cppflags) $(Mumu_pp_cppflags) $(use_cppflags) $(MumuAlg_cppflags) $(lib_MumuAlg_cppflags) $(Mumu_cppflags) $(Mumu_cxx_cppflags)  $(src)Mumu.cxx

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq ($(cppdepflags),)

ifneq ($(MAKECMDGOALS),MumuAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Mumu_entries.d

$(bin)$(binobj)Mumu_entries.d : $(use_requirements) $(cmt_final_setup_MumuAlg)

$(bin)$(binobj)Mumu_entries.d : $(src)components/Mumu_entries.cxx
	$(dep_echo) $@
	$(cpp_silent) $(cppcomp) $(cppdepflags) -o $(@D)/Mumu_entries.dep $(use_pp_cppflags) $(MumuAlg_pp_cppflags) $(lib_MumuAlg_pp_cppflags) $(Mumu_entries_pp_cppflags) $(use_cppflags) $(MumuAlg_cppflags) $(lib_MumuAlg_cppflags) $(Mumu_entries_cppflags) $(Mumu_entries_cxx_cppflags) -I../src/components $(src)components/Mumu_entries.cxx
	$(cpp_silent) $(format_dependencies) $@ $(@D)/Mumu_entries.o $(src)components/Mumu_entries.cxx $(@D)/Mumu_entries.dep
endif
endif

$(bin)$(binobj)Mumu_entries.o : $(src)components/Mumu_entries.cxx
else
$(bin)MumuAlg_dependencies.make : $(Mumu_entries_cxx_dependencies)

$(bin)$(binobj)Mumu_entries.o : $(Mumu_entries_cxx_dependencies)
endif
	$(cpp_echo) $(src)components/Mumu_entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(MumuAlg_pp_cppflags) $(lib_MumuAlg_pp_cppflags) $(Mumu_entries_pp_cppflags) $(use_cppflags) $(MumuAlg_cppflags) $(lib_MumuAlg_cppflags) $(Mumu_entries_cppflags) $(Mumu_entries_cxx_cppflags) -I../src/components $(src)components/Mumu_entries.cxx

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq ($(cppdepflags),)

ifneq ($(MAKECMDGOALS),MumuAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Mumu_load.d

$(bin)$(binobj)Mumu_load.d : $(use_requirements) $(cmt_final_setup_MumuAlg)

$(bin)$(binobj)Mumu_load.d : $(src)components/Mumu_load.cxx
	$(dep_echo) $@
	$(cpp_silent) $(cppcomp) $(cppdepflags) -o $(@D)/Mumu_load.dep $(use_pp_cppflags) $(MumuAlg_pp_cppflags) $(lib_MumuAlg_pp_cppflags) $(Mumu_load_pp_cppflags) $(use_cppflags) $(MumuAlg_cppflags) $(lib_MumuAlg_cppflags) $(Mumu_load_cppflags) $(Mumu_load_cxx_cppflags) -I../src/components $(src)components/Mumu_load.cxx
	$(cpp_silent) $(format_dependencies) $@ $(@D)/Mumu_load.o $(src)components/Mumu_load.cxx $(@D)/Mumu_load.dep
endif
endif

$(bin)$(binobj)Mumu_load.o : $(src)components/Mumu_load.cxx
else
$(bin)MumuAlg_dependencies.make : $(Mumu_load_cxx_dependencies)

$(bin)$(binobj)Mumu_load.o : $(Mumu_load_cxx_dependencies)
endif
	$(cpp_echo) $(src)components/Mumu_load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(MumuAlg_pp_cppflags) $(lib_MumuAlg_pp_cppflags) $(Mumu_load_pp_cppflags) $(use_cppflags) $(MumuAlg_cppflags) $(lib_MumuAlg_cppflags) $(Mumu_load_cppflags) $(Mumu_load_cxx_cppflags) -I../src/components $(src)components/Mumu_load.cxx

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: MumuAlgclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(MumuAlg.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
	if echo $@ | grep '$(package)setup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(MumuAlg.make): $@: File no longer generated" >&2; exit 0; fi
else
.DEFAULT::
	$(echo) "(MumuAlg.make) PEDANTIC: $@: No rule for such target" >&2
	if echo $@ | grep '$(package)setup\.make$$' >/dev/null; then\
	 echo "$(CMTMSGPREFIX)" "(MumuAlg.make): $@: File no longer generated" >&2; exit 0;\
	 elif test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_MumuAlg)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(MumuAlg.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr $@ : '.*/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(MumuAlg.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(MumuAlg.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

MumuAlgclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library MumuAlg
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)MumuAlg$(library_suffix).a $(library_prefix)MumuAlg$(library_suffix).s? MumuAlg.stamp MumuAlg.shstamp
#-- end of cleanup_library ---------------
