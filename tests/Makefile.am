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

check_PROGRAMS = \
test-alpha-creation test-alpha-func \
test-interval-creation test-point-class test-actor-box

local_includes = -I$(top_builddir)/clutter $(if $(srcdir:.=),-I$(top_srcdir)/clutter)
local_libs = $(top_builddir)/clutter/cluttermm/libcluttermm-$(CLUTTERMM_API_VERSION).la

AM_CPPFLAGS = -I$(top_builddir) $(local_includes) $(CLUTTERMM_CFLAGS)
AM_CXXFLAGS = $(CLUTTERMM_WXXFLAGS)
LDADD = $(CLUTTERMM_LIBS) $(local_libs)

test_alpha_creation_SOURCES    = test-alpha-creation.cc
test_alpha_func_SOURCES        = test-alpha-func.cc
test_interval_creation_SOURCES = test-interval-creation.cc
test_point_class_SOURCES    = test-point-class.cc
test_actor_box_SOURCES      = test-actor-box.cc

# Only tests that don't require user input are added here, as they will
# run automatically on building:

TESTS = test-interval-creation test-point-class test-actor-box
