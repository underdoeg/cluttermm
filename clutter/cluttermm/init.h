// -*- c++ -*-
#ifndef _LIBCLUTTERMM_INIT_H
#define _LIBCLUTTERMM_INIT_H
/*
 * Copyright 2008 Jonathon Jongsma
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
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
 * @throws InitError
 */
void init(int* argc, gchar** argv[]);

/** It will initialise everything needed to operate with Clutter and parses
 * some standard command line options. argc and argv are adjusted accordingly
 * so your own code will never see those standard arguments.
 *
 * @param argc a pointer to the number of command line arguments
 * @param argv a pointer to the array of comman line arguments
 * @throws InitError
 */
void init(int& argc, gchar**& argv);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct OptionEntryTraits
{
  typedef Glib::OptionEntry CppType;
  typedef GOptionEntry CType;

  static CppType to_cpp_type(const CType& obj)
  {
    // We only convert the other way around:
    g_assert_not_reached();
    return CppType();
  }

  static CType to_c_type(CppType& obj) { return *obj.gobj(); }
};
#endif
typedef Glib::ArrayHandle<Glib::OptionEntry, OptionEntryTraits> ArrayHandle_OptionEntries;

/** This function does the same work as init(). Additionally, it
 * allows you to add your own command line options, and it automatically
 * generates nicely formatted --help output. Note that your program will be
 * terminated after writing out the help output. Also note that, in case of
 * error, the error message will be placed inside error instead of being
 * printed on the display.
 *
 * @param argc a pointer to the number of command line arguments
 * @param argv a pointer to the array of comman line arguments
 * @param parameter_string a string which is displayed in the first line of --help output, after programname [OPTION...]
 * @param entries an array of Glib::OptionEntrys describing the options of your program
 * @param translation_domain a translation domain to use for translating the --help output for the options in entries with gettext()
 * @throws InitError
 */
void init(int* argc, gchar** argv[], const Glib::ustring& parameter_string, const ArrayHandle_OptionEntries& entries, const std::string& translation_domain);

/** This function does the same work as init(). Additionally, it
 * allows you to add your own command line options, and it automatically
 * generates nicely formatted --help output. Note that your program will be
 * terminated after writing out the help output. Also note that, in case of
 * error, the error message will be placed inside error instead of being
 * printed on the display.
 *
 * @param argc a pointer to the number of command line arguments
 * @param argv a pointer to the array of comman line arguments
 * @param parameter_string a string which is displayed in the first line of --help output, after programname [OPTION...]
 * @param entries an array of Glib::OptionEntrys describing the options of your program
 * @param translation_domain a translation domain to use for translating the --help output for the options in entries with gettext()
 * @throws InitError
 */
void init(int& argc, gchar**& argv, const Glib::ustring& parameter_string, const ArrayHandle_OptionEntries& entries, const std::string& translation_domain);

/** Adds a Glib::OptionGroup for the command line arguments recognized by
 * Clutter to the given context. This is useful if you are using
 * Glib::OptionContext::parse() to parse your commandline arguments.
 *
 * @param option_context a Glib::OptionContext to add the clutter option group to.
 */
void add_clutter_option_group(Glib::OptionContext& option_context);

} //namespace Clutter

#endif //_LIBCLUTTERMM_INIT_H

