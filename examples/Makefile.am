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

check_PROGRAMS = actors stage

dist_noinst_DATA = actor.png test-boxes.cc

local_includes = -I$(top_builddir)/clutter $(if $(srcdir:.=),-I$(top_srcdir)/clutter)
local_libs = $(top_builddir)/clutter/cluttermm/libcluttermm-$(CLUTTERMM_API_VERSION).la

AM_CPPFLAGS = -I$(top_builddir) $(local_includes) $(CLUTTERMM_CFLAGS)
AM_CXXFLAGS = $(CLUTTERMM_WXXFLAGS) \
  -DGLIBMM_DISABLE_DEPRECATED -DGIOMM_DISABLE_DEPRECATED -DGTKMM_DISABLE_DEPRECATED -DGDKMM_DISABLE_DEPRECATED \
  -DCLUTTERMM_DISABLE_DEPRECATED
LDADD = $(CLUTTERMM_LIBS) $(local_libs)

actors_SOURCES = test-actors.cc
stage_SOURCES = example-stage.cc
