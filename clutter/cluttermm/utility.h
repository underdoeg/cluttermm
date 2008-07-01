// -*- c++ -*-
#ifndef _LIBCLUTTERMM_UTILITY_H
#define _LIBCLUTTERMM_UTILITY_H
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

/** Check if clutter has debugging turned on.
 * @return true if debugging is turned on, false otherwise.
 */
bool get_debug_enabled();

/** Returns whether Clutter should print out the frames per second on the
 * console. You can enable this setting either using the CLUTTER_SHOW_FPS
 * environment variable or passing the --clutter-show-fps command line
 * argument.
 * @return true if Clutter should show the FPS.
 */
bool get_show_fps();

/** Returns the approximate number of microseconds passed since clutter was
 * intialised.
 * @return Number of microseconds since clutter_init() was called.
 */
gulong get_timestamp();

/** Retrieves the Actor with id.
 * @param id an Actor ID.
 * @return the actor with the passed id or a NULL RefPtr.
 */
Glib::RefPtr<Actor> get_actor_by_gid(guint32 id);

/** Sets the default frame rate to be used when creating Timeline objects.
 * @param frames_per_sec the new default frame rate
 */
void set_default_frame_rate(guint frames_per_sec);

/** Retrieves the default frame rate used when creating ClutterTimelines.
 *
 * This value is also used to compute the default frequency of motion events.
 * @return the default frame rate
 */
guint get_default_frame_rate();

/** Sets whether per-actor motion events should be enabled or not
 * (the default is to enable them).
 *
 * If enable is false the following events will not work:
 *
 * <ul>
 *  <li>ClutterActor::motion-event, unless on the ClutterStage</li>
 *  <li>ClutterActor::enter-event</li>
 *  <li>ClutterActor::leave-event</li>
 * </ul>
 *
 * @param enable true to enable per-actor motion events
 */
void set_motion_events_enabled(bool enable);

/** Gets whether the per-actor motion events are enabled.
 * @return true if the motion events are enabled
 */
bool get_motion_events_enabled();

/** Sets the motion events frequency. Setting this to a non-zero value will
 * override the default setting, so it should be rarely used.
 *
 * Motion events are delivered from the default backend to the stage and are
 * used to generate the enter/leave events pair. This might lead to a
 * performance penalty due to the way the actors are identified. Using this
 * function is possible to reduce the frequency of the motion events
 * delivery to the stage.
 *
 * @param frequency the number of motion events per second, or 0 for the default value
 */
void set_motion_events_frequency(guint frequency);

/** Retrieves the number of motion events per second that are delivered to
 * the stage.
 *
 * See set_motion_events_frequency().
 * @return the number of motion events per second
 */
guint get_motion_events_frequency();

/** Clears the internal cache of glyphs used by the Pango renderer. This will
 * free up some memory and GL texture resources. The cache will be
 * automatically refilled as more text is drawn.
 */
void clear_glyph_cache();

/** Sets whether subsequent text rendering operations will use mipmapped
 * textures or not. Using mipmapped textures will improve the quality for
 * scaled down text but will use more texture memory.
 * @param value true to enable mipmapping or false to disable.
 */
void set_use_mipmapped_text(bool value);

/** Gets whether mipmapped textures are used in text operations. See
 * set_use_mipmapped_text().
 * @return true if text operations should use mipmapped textures
 */
bool get_use_mipmapped_text();

} //namespace Clutter

#endif //_LIBCLUTTERMM_UTILITY_H

