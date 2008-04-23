## Copyright (c) 2008
## The cluttermm development team.

SUBDIRS			= private

sublib_name		= cluttermm
sublib_libname = cluttermm-$(API_VER)
sublib_libversion = $(CLUTTERMM_SO_VERSION)
sublib_namespace	= Clutter
sublib_cflags		= $(CLUTTERMM_CFLAGS)
sublib_topdir = clutter


files_extra_h	= init.h types.h wrap_init.h
files_extra_cc	= init.cc

include $(top_srcdir)/build_shared/Makefile_build_gensrc.am_fragment

lib_LTLIBRARIES = libcluttermm-@API_VER@.la
libcluttermm_@API_VER@_la_SOURCES = $(files_all_cc)
libcluttermm_@API_VER@_la_LDFLAGS = $(common_ldflags)
libcluttermm_@API_VER@_la_LIBADD = $(CLUTTERMM_LIBS)

