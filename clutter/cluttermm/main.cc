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

#define CLUTTER_DISABLE_DEPRECATION_WARNINGS 1

#include <cluttermm/main.h>
#include <clutter/clutter.h>

namespace Clutter
{

void main()
{
  clutter_main();
}

void main_quit()
{
  clutter_main_quit();
}

int main_level()
{
  return clutter_main_level();
}

#ifndef CLUTTERMM_DISABLE_DEPRECATED
bool get_debug_enabled()
{
  return clutter_get_debug_enabled();
}

bool get_show_fps()
{
  return clutter_get_show_fps();
}

gulong get_timestamp()
{
  return clutter_get_timestamp();
}

Glib::RefPtr<Actor> get_actor_by_gid(guint32 id)
{
  return Glib::wrap(clutter_get_actor_by_gid(id), true);
}

void set_default_frame_rate(guint frames_per_sec)
{
  clutter_set_default_frame_rate(frames_per_sec);
}

guint get_default_frame_rate()
{
  return clutter_get_default_frame_rate();
}

void set_motion_events_enabled(bool enable)
{
  clutter_set_motion_events_enabled(enable);
}

bool get_motion_events_enabled()
{
  return clutter_get_motion_events_enabled();
}

void clear_glyph_cache()
{
  clutter_clear_glyph_cache();
}
#endif //CLUTTERMM_DISABLE_DEPRECATED


Glib::RefPtr<Pango::FontMap> get_font_map()
{
  return Glib::wrap(clutter_get_font_map());
}

Glib::RefPtr<Actor> get_keyboard_grab()
{
  return Glib::wrap(clutter_get_keyboard_grab(), true);
}

Glib::RefPtr<Actor> get_pointer_grab()
{
  return Glib::wrap(clutter_get_pointer_grab(), true);
}

void grab_keyboard(const Glib::RefPtr<Actor>& actor)
{
  clutter_grab_keyboard(actor->gobj());
}

void grab_pointer(const Glib::RefPtr<Actor>& actor)
{
  clutter_grab_pointer(actor->gobj());
}

void ungrab_keyboard()
{
  clutter_ungrab_keyboard();
}

void ungrab_pointer()
{
  clutter_ungrab_pointer();
}

#ifndef CLUTTERMM_DISABLE_DEPRECATED
void grab_pointer_for_device(const Glib::RefPtr<Actor>& actor, int id)
{
  clutter_grab_pointer_for_device(actor->gobj(), id);
}

void ungrab_pointer_for_device(int id)
{
  clutter_ungrab_pointer_for_device(id);
}
#endif //CLUTTERMM_DISABLE_DEPRECATED


} //namespace Clutter
