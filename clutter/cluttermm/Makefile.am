## Copyright (c) 2001
## The cluttermm development team.

SUBDIRS			= private

sublib_name		= cluttermm
sublib_libname = cluttermm-1.0
sublib_libversion = $(CLUTTERMM_SO_VERSION)
sublib_namespace	= Clutter
sublib_cflags		= $(CLUTTERMM_CFLAGS)
sublib_topdir = clutter


files_extra_h	= init.h types.h wrap_init.h 
files_extra_cc	= init.cc

include $(top_srcdir)/build_shared/Makefile_build_gensrc.am_fragment

lib_LTLIBRARIES			= libcluttermm-1.0.la
libcluttermm_1_0_la_SOURCES	= $(files_all_cc)
libcluttermm_1_0_la_LDFLAGS	= $(common_ldflags)
libcluttermm_1_0_la_LIBADD	= $(CLUTTERMM_LIBS)

