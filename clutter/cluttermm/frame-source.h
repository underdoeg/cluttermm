// -*- c++ -*-
#ifndef _LIBCLUTTERMM_FRAME_SOURCE_H
#define _LIBCLUTTERMM_FRAME_SOURCE_H
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

/** Sets a function to be called at regular intervals with the given priority.
 * The function is called repeatedly until it returns false, at which point
 * the timeout is automatically destroyed and the function will not be called
 * again. The first call to the function will be at the end of the first
 * interval.
 *
 * This function is similar to Glib::SignalTimeout except that it will try to
 * compensate for delays. For example, if func takes half the interval time to
 * execute then the function will be called again half the interval time after
 * it finished. In contrast Glib::SignalTimeout would not fire until a full
 * interval after the function completes so the delay between calls would be
 * interval * 1.5. This function does not however try to invoke the function
 * multiple times to catch up missing frames if callback takes more than
 * interval ms to execute.
 *
 * @param callback function to call
 * @param interval the time between calls to the function, in milliseconds
 * @param the priority of the timeout source. Typically this will be in the range between Glib::PRIORITY_DEFAULT and Glib::PRIORITY_HIGH.
 * @return A sigc::connection that can be used to disconnect the callback from the timeout source.
 */
sigc::connection frame_source_add(const sigc::slot<bool>& callback, guint interval, gint priority = Glib::PRIORITY_DEFAULT);

} //namespace Clutter

#endif //_LIBCLUTTERMM_FRAME_SOURCE_H

