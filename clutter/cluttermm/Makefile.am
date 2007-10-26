## Copyright (c) 2001
## The cluttermm development team.

SUBDIRS			= private

sublib_name		= cluttermm
sublib_libname = cluttermm-0.1
sublib_libversion = $(CLUTTERMM_SO_VERSION)
sublib_namespace	= Clutter
sublib_cflags		= $(CLUTTERMM_CFLAGS)
sublib_topdir = clutter


files_extra_h	= init.h wrap_init.h types.h 
files_extra_cc	= init.cc

include $(top_srcdir)/build_shared/Makefile_build_gensrc.am_fragment

lib_LTLIBRARIES			= libcluttermm-0.1.la
libcluttermm_0_1_la_SOURCES	= $(files_all_cc)
libcluttermm_0_1_la_LDFLAGS	= $(common_ldflags)
libcluttermm_0_1_la_LIBADD	= $(CLUTTERMM_LIBS)

