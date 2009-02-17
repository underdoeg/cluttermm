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

#include <cluttermm/event.h>
#include <clutter/clutter.h>

namespace Clutter
{

bool events_pending()
{
  return clutter_events_pending();
}

guint key_event_symbol(KeyEvent* keyev)
{
  return clutter_key_event_symbol(keyev);
}

guint16 key_event_code(KeyEvent* keyev)
{
  return clutter_key_event_code(keyev);
}

guint32 key_event_unicode(KeyEvent* keyev)
{
  return clutter_key_event_unicode(keyev);
}

guint32 keysym_to_unicode(guint keyval)
{
  return clutter_keysym_to_unicode(keyval);
}

} //namespace Clutter
