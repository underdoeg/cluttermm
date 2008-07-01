// -*- c++ -*-
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

#include <cluttermm/main.h>
#include <cluttermm/actor.h>
#include <clutter/clutter.h>

namespace Clutter
{

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

void set_motion_events_frequency(guint frequency)
{
  clutter_set_motion_events_frequency(frequency);
}

guint get_motion_events_frequency()
{
  return clutter_get_motion_events_frequency();
}

void clear_glyph_cache()
{
  clutter_clear_glyph_cache();
}

void set_use_mipmapped_text(bool value)
{
  clutter_set_use_mipmapped_text(value);
}

bool get_use_mipmapped_text()
{
  return clutter_get_use_mipmapped_text();
}

} //namespace Clutter
