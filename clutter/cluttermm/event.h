// -*- c++ -*-
#ifndef _LIBCLUTTERMM_EVENT_H
#define _LIBCLUTTERMM_EVENT_H
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
#include <cluttermm/types.h>
// We also need these in C++:
#include <clutter/clutter.h>

namespace Clutter
{

// TODO: Wrap the functions that take a ClutterEvent*. I guess we need proper
// C++ inheritance for the events to allow passing a ClutterEventButton* to
// a function taking a ClutterEvent*, for example.

/** Checks if events are pending in the event queue.
 * @return true if there are pending events, false otherwise.
 */
bool events_pending();

/** Retrieves the value of the key that caused @a keyev.
 * @param keyev A KeyEvent.
 * @return The keysym representing the key.
 */
guint key_event_symbol(KeyEvent* keyev);

/** Retrieves the keycode of the key that caused @a keyev.
 * @param keyev A KeyEvent.
 * @return The keycode representing the key
 */
guint16 key_event_code(KeyEvent* keyev);

/** Retrieves the unicode value for the key that caused @a keyev.
 * @param keyev A KeyEvent
 * @return The unicode value representing the key
 */
guint32 key_event_unicode(KeyEvent* keyev);

/** Convert from a Clutter key symbol to the corresponding ISO10646 (Unicode)
 * character.
 * @param keyval a clutter key symbol
 * @return the corresponding unicode character, or 0 if there is no
 * corresponding character.
 */
guint32 keysym_to_unicode(guint keyval);

} //namespace Clutter

#endif //_LIBCLUTTERMM_EVENT_H

