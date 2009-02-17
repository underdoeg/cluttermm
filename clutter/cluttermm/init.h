// -*- c++ -*-
#ifndef _LIBCLUTTERMM_INIT_H
#define _LIBCLUTTERMM_INIT_H
/*
 * Copyright 2008 Jonathon Jongsma
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <glibmm.h>

namespace Clutter
{

/** It will initialise everything needed to operate with Clutter and parses
 * some standard command line options. argc and argv are adjusted accordingly
 * so your own code will never see those standard arguments.
 *
 * @param argc a pointer to the number of command line arguments
 * @param argv a pointer to the array of comman line arguments
 * @throws InitError, Glib::OptionError
 */
void init(int* argc, gchar** argv[]);

/** It will initialise everything needed to operate with Clutter and parses
 * some standard command line options. argc and argv are adjusted accordingly
 * so your own code will never see those standard arguments.
 *
 * @param argc a reference to the number of command line arguments
 * @param argv a reference to the array of comman line arguments
 * @throws InitError, Glib::OptionError
 */
void init(int& argc, gchar**& argv);

// TODO: This does not work yet because because of clutter bug #1033. It has
// already been fixed in trunk but there was no release since. We can
// uncomment this as soon as clutter with that fix has been released.
#if 0
/** It will initialise everything needed to operate with Clutter and parses
 * some standard command line options and the options specified in your
 * @a option_context. Add a Glib::OptionGroup to the Glib::OptionContext to
 * parse your own command-line arguments.
 *
 * @param argc a pointer to the number of command line arguments
 * @param argv a pointer to the array of comman line arguments
 * @param option_context A Glib::OptionContext containing Glib::OptionGroups which described the command-line arguments taken by your program.
 * @throws InitError, Glib::OptionError
 */
void init(int* argc, char** argv[], Glib::OptionContext& option_context);

/** It will initialise everything needed to operate with Clutter and parses
 * some standard command line options and the options specified in your
 * @a option_context. Add a Glib::OptionGroup to the Glib::OptionContext to
 * parse your own command-line arguments.
 *
 * @param argc a reference to the number of command line arguments
 * @param argv a reference to the array of comman line arguments
 * @param option_context A Glib::OptionContext containing Glib::OptionGroups which described the command-line arguments taken by your program.
 * @throws InitError, Glib::OptionError
 */
void init(int& argc, char**& argv, Glib::OptionContext& option_context);
#endif

/** Adds a Glib::OptionGroup for the command line arguments recognized by
 * Clutter to the given context. This is useful if you are using
 * Glib::OptionContext::parse() to parse your commandline arguments.
 *
 * @param option_context a Glib::OptionContext to add the clutter option group to.
 */
void add_clutter_option_group(Glib::OptionContext& option_context);

} //namespace Clutter

#endif //_LIBCLUTTERMM_INIT_H

