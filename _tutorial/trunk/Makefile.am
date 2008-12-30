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

## This project does not use recursive make, but a single toplevel Makefile
## to build the entire tree (excluding the po subdirectory as gettext comes
## with its own build system).  Read Peter Miller's excellent paper to learn
## why recursive make invocations are both slow and error-prone:
## http://members.pcug.org.au/~millerp/rmch/recu-make-cons-harm.html

AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS  = -I m4 $(ACLOCAL_FLAGS)
DISTCHECK_CONFIGURE_FLAGS = --enable-warnings=fatal

bin_PROGRAMS =	\
	examples/actor/example			\
	examples/actor_group/example		\
	examples/actor_transformations/example	\
	examples/behaviour/example		\
	examples/custom_actor/example		\
	examples/custom_container/example	\
	examples/effects/example		\
	examples/full_example/example		\
	examples/score/example			\
	examples/scrolling/example		\
	examples/stage/example			\
	examples/stage_widget/example		\
	examples/timeline/example

examples_actor_example_SOURCES			= examples/actor/main.cc
examples_actor_group_example_SOURCES		= examples/actor_group/main.cc
examples_actor_transformations_example_SOURCES	= examples/actor_transformations/main.cc
examples_behaviour_example_SOURCES		= examples/behaviour/main.cc
examples_custom_actor_example_SOURCES =		\
	examples/custom_actor/main.cc		\
	examples/custom_actor/triangle_actor.cc	\
	examples/custom_actor/triangle_actor.h
examples_custom_container_example_SOURCES =	\
	examples/custom_container/examplebox.cc	\
	examples/custom_container/examplebox.h	\
	examples/custom_container/main.cc
examples_effects_example_SOURCES		= examples/effects/main.cc
examples_full_example_example_SOURCES		= examples/full_example/main.cc
examples_score_example_SOURCES			= examples/score/main.cc
examples_scrolling_example_SOURCES =		\
	examples/scrolling/main.cc		\
	examples/scrolling/scrollingcontainer.cc\
	examples/scrolling/scrollingcontainer.h
examples_stage_example_SOURCES			= examples/stage/main.cc
examples_stage_widget_example_SOURCES		= examples/stage_widget/main.cc
examples_timeline_example_SOURCES		= examples/timeline/main.cc

AM_CPPFLAGS = $(TUTORIAL_MODULES_CFLAGS)
AM_CXXFLAGS = $(TUTORIAL_WXXFLAGS)
LDADD = $(TUTORIAL_MODULES_LIBS)

dist_pkgdata_DATA =						\
	examples/full_example/images/alexander_larsson.jpg	\
	examples/full_example/images/andreas_nilsson.jpg	\
	examples/full_example/images/bastian_nocera.jpg		\
	examples/full_example/images/christian_kellner.jpg	\
	examples/full_example/images/david_zeuthen.jpg		\
	examples/full_example/images/john_palmieri.jpg		\
	examples/full_example/images/jonathan_blandford.jpg	\
	examples/full_example/images/matthew_allum.jpg		\
	examples/full_example/images/matthias_clasen.jpg	\
	examples/full_example/images/mikael_hallendal.jpg	\
	examples/full_example/images/ryan_lortie.jpg
