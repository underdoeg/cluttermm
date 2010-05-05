## Copyright (c) 2009  Openismus GmbH <http://www.openismus.com/>
##
## This file is part of cluttermm.
##
## cluttermm is free software: you can redistribute it and/or modify it
## under the terms of the GNU Lesser General Public License as published
## by the Free Software Foundation, either version 2.1 of the License,
## or (at your option) any later version.
##
## cluttermm is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
## See the GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

AC_INIT([cluttermm], [0.9.6],
        [http://bugzilla.gnome.org/enter_bug.cgi?product=cluttermm],
        [cluttermm], [http://www.gtkmm.org/])
AC_PREREQ([2.59])

AC_CONFIG_SRCDIR([clutter/cluttermm.h])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build])
AC_CONFIG_HEADERS([build/config.h clutter/cluttermmconfig.h])

AM_INIT_AUTOMAKE([1.9 -Wno-portability check-news dist-bzip2 no-define nostdinc tar-pax])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES])
AM_MAINTAINER_MODE
AC_ARG_VAR([ACLOCAL_FLAGS], [aclocal flags, e.g. -I <macro dir>])

MM_PREREQ([0.8])
MM_INIT_MODULE([cluttermm-1.0])

# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
AC_SUBST([CLUTTERMM_SO_VERSION], [1:0:0])

AC_PROG_CXX
AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

AC_SUBST([CLUTTERMM_MODULES], ['clutter-1.0 >= 1.2.0 pangomm-1.4 >= 2.24'])
PKG_CHECK_MODULES([CLUTTERMM], [$CLUTTERMM_MODULES])
MM_PKG_CONFIG_SUBST([GMMPROC_DIR], [--variable=gmmprocdir glibmm-2.4])

MM_ARG_ENABLE_DOCUMENTATION
MM_ARG_WITH_TAGFILE_DOC([libstdc++.tag], [mm-common-libstdc++])
MM_ARG_WITH_TAGFILE_DOC([libsigc++-2.0.tag], [sigc++-2.0])
MM_ARG_WITH_TAGFILE_DOC([glibmm-2.4.tag], [glibmm-2.4])
MM_ARG_WITH_TAGFILE_DOC([cairomm-1.0.tag], [cairomm-1.0])
MM_ARG_WITH_TAGFILE_DOC([pangomm-1.4.tag], [pangomm-1.4])

AC_LANG([C++])
MM_ARG_ENABLE_WARNINGS([CLUTTERMM_WXXFLAGS],
                       [-Wall],
                       [-Wall -Wextra],
                       [G PANGO])

AC_CONFIG_FILES([Makefile
                 codegen/Makefile
                 clutter/${CLUTTERMM_MODULE_NAME}.pc:clutter/cluttermm.pc.in
                 clutter/${CLUTTERMM_MODULE_NAME}-uninstalled.pc:clutter/cluttermm-uninstalled.pc.in
                 clutter/src/Makefile
                 clutter/cluttermm/Makefile
                 examples/Makefile
                 tests/Makefile
                 doc/Makefile
                 doc/reference/Doxyfile])
AC_OUTPUT
