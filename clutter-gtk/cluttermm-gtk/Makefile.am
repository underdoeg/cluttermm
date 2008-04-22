## Copyright (c) 2001
## The cluttermm development team.

SUBDIRS			= private

sublib_name		= cluttermm-gtk
sublib_libname = cluttermm-gtk-1.0
sublib_libversion = $(CLUTTERMM_SO_VERSION)
sublib_namespace	= Clutter
sublib_cflags		= $(CLUTTERMM_GTK_CFLAGS) -I$(top_srcdir)/clutter
sublib_topdir = clutter-gtk


files_extra_h	= wrap_init.h init.h
files_extra_cc	= init.cc

include $(top_srcdir)/build_shared/Makefile_build_gensrc.am_fragment

lib_LTLIBRARIES			= libcluttermm-gtk-1.0.la
libcluttermm_gtk_1_0_la_SOURCES	= $(files_all_cc)
libcluttermm_gtk_1_0_la_LDFLAGS	= $(common_ldflags)
libcluttermm_gtk_1_0_la_LIBADD	= $(CLUTTERMM_GTK_LIBS) \
									  $(top_builddir)/clutter/cluttermm/libcluttermm-1.0.la

