## Copyright (c) 2008  Openismus GmbH  <danielk@openismus.com>
##
## This file is part of the Cluttermm Tutorial.
##
## The Cluttermm Tutorial is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License as published
## by the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## The Cluttermm Tutorial is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with the Cluttermm Tutorial; if not, write to the Free Software
## Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA

AC_INIT([cluttermm_tutorial], [0.9], [http://www.gtkmm.org/], [cluttermm_tutorial])
AC_PREREQ([2.58])

AC_CONFIG_SRCDIR([examples/custom_actor/triangle_actor.cc])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.8 -Wall gnu no-define nostdinc])
AC_ARG_VAR([ACLOCAL_FLAGS], [aclocal flags, e.g. -I <macro dir>])

AC_PROG_CXX()
PKG_CHECK_MODULES([TUTORIAL_MODULES], [cluttermm-0.9 >= 0.9.0 clutter-gtkmm-0.9 >= 0.9.0])

AC_LANG([C++])

# Disabling -Wnon-virtual-dtor is nasty, but unfortunately required due to
# a bug in gconfmm that triggers this warning.  Not disabling this warning
# would make --enable-warnings=fatal unusable.
DK_ARG_ENABLE_WARNINGS([TUTORIAL_WXXFLAGS],
                       [-Wall -w1 -Wno-non-virtual-dtor],
                       [-pedantic -Wall -Wextra -w1 -Wno-non-virtual-dtor],
                       [GLIBMM GTKMM])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT()
