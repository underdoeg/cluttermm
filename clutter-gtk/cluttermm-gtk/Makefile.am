## Copyright (c) 2008
## The cluttermm development team.

SUBDIRS = private

sublib_name = cluttermm-gtk
sublib_libname = cluttermm-gtk-$(API_VER)
sublib_libversion = $(CLUTTERMM_SO_VERSION)
sublib_namespace = Clutter
sublib_cflags = $(CLUTTERMM_GTK_CFLAGS) -I$(top_srcdir)/clutter
sublib_topdir = clutter-gtk

files_extra_h = wrap_init.h init.h
files_extra_cc = init.cc

include $(top_srcdir)/build_shared/Makefile_build_gensrc.am_fragment

lib_LTLIBRARIES = libcluttermm-gtk-@API_VER@.la
libcluttermm_gtk_@API_VER@_la_SOURCES = $(files_all_cc)
libcluttermm_gtk_@API_VER@_la_LDFLAGS = $(common_ldflags)
libcluttermm_gtk_@API_VER@_la_LIBADD = $(CLUTTERMM_GTK_LIBS) \
	$(top_builddir)/clutter/cluttermm/libcluttermm-$(API_VER).la

