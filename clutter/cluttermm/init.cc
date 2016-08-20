// -*- c++ -*-
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

#include <cluttermmconfig.h> //For LIBCLUTTERMM_VERSION
#include <cluttermm/init.h>
#include <cluttermm/wrap_init.h>
#include <clutter/clutter.h>

namespace
{

void common_init()
{
  Glib::init(); //Sets up the g type system and the Glib::wrap() table.
  Clutter::wrap_init(); //Tells the Glib::wrap() table about the libcluttermm classes.
}

}

namespace Clutter
{

void init(int* argc, gchar **argv[])
{
  common_init();
  GError* error = NULL;
  const ClutterInitError result = clutter_init_with_args(argc, argv, NULL, NULL, NULL, &error);
  if(error)
    Glib::Error::throw_exception(error);

  if(result != CLUTTER_INIT_SUCCESS)
    throw Glib::Error(); //This should never happen. The GError should always be set.
}

void init(int& argc, gchar**& argv)
{
  init(&argc, &argv);
}

// TODO: This does not work yet because because of clutter bug #1033. It has
// already been fixed in trunk but there was no release since. We can
// uncomment this as soon as clutter with that fix has been released.
#if 0
void init(int* argc, gchar** argv[], Glib::OptionContext& option_context)
{
  common_init();
  GError* error = NULL;
  add_clutter_option_group(option_context);
  option_context.parse(*argc, *argv);
  // option_context_parse already parsed the clutter arguments:
  clutter_init_with_args(NULL, NULL, NULL, NULL, NULL, &error);
  if(error != NULL) Glib::Error::throw_exception(error);
}

void init(int& argc, gchar**& argv, Glib::OptionContext& option_context)
{
  init(&argc, &argv, option_context);
}
#endif

void add_clutter_option_group(Glib::OptionContext& option_context)
{
  // This returns a newly created option group of which we take ownership
  Glib::OptionGroup cluttergroup(clutter_get_option_group());
  option_context.add_group(cluttergroup);
}


} //namespace Clutter
