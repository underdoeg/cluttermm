// -*- c++ -*-
#ifndef _LIBCLUTTERMM_THREADS_H
#define _LIBCLUTTERMM_THREADS_H
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

// TODO: clutter_threads_set_lock_functions ()?

#ifndef CLUTTERMM_DISABLE_DEPRECATED

/** Initialises the Clutter threading mechanism, so that Clutter API can be 
 * called by multiple threads, using threads_enter() and
 * threads_leave() to mark the critical sections.
 *
 * You must call Glib::thread_init() before this function. 
 *
 * This function must be called before init().
 *
 * @deprecated This function does not do anything. Threading support is initialized when Clutter is initialized.
 */
void threads_init();

/** Locks the Clutter thread lock.
 *
 * @deprecated This function should not be used by application code. Marking critical sections is not portable on various platforms. Instead of acquiring the Clutter lock, schedule UI updates from the main loop using threads_add_idle() or threads_add_timeout().
 */
void threads_enter();

/** Unlocks the Clutter thread lock.
 *
 * @deprecated This function should not be used by application code. Marking critical sections is not portable on various platforms. Instead of acquiring the Clutter lock, schedule UI updates from the main loop using threads_add_idle() or threads_add_timeout().
 */
void threads_leave();

#endif //CLUTTERMM_DISABLE_DEPRECATED


// TODO: Should there be a SignalSomething class for these, so the
// sigc::connection makes more semantical sense?

/** Adds a function to be called whenever there are no higher priority events
 * pending. If the function returns false it is automatically removed from
 * the list of event sources and will not be called again.
 *
 * This variant of Glib::signal_idle calls function with the Clutter lock
 * held. It can be thought of a MT-safe version for Clutter actors for the
 * use case where you have to worry about idle_callback() running in thread A
 * and accessing self after it has been finalized in thread B.
 *
 * @param callback function to call
 * @param priority the priority of the timeout source. Typically this will be in the range between Glib::PRIORITY_DEFAULT_IDLE and Glib::PRIORITY_HIGH_IDLE
 * @return A sigc::connection that can be used to disconnect the callback
 * from the idle source.
 */
sigc::connection threads_add_idle(const sigc::slot<bool>& callback, int priority = Glib::PRIORITY_DEFAULT_IDLE);

/** Sets a function to be called at regular intervals holding the Clutter
 * lock, with the given priority. The function is called repeatedly until it
 * returns false, at which point the timeout is automatically destroyed and
 * the function will not be called again. The first call to the function will
 * be at the end of the first interval.
 *
 * Note that timeout functions may be delayed, due to the processing of other
 * event sources. Thus they should not be relied on for precise timing. After
 * each call to the timeout function, the time of the next timeout is
 * recalculated based on the current time and the given interval (it does not
 * try to 'catch up' time lost in delays).
 *
 * This variant of Glib::SignalTimeout can be thought of a MT-safe version
 * for Clutter actors. See also threads_add_idle().
 *
 * @param callback function to call
 * @param interval the time between calls to the function, in milliseconds
 * @param priority the priority of the timeout source. Typically this will be in the range between Glib::PRIORITY_DEFAULT and Glib::PRIORITY_HIGH.
 * @return A sigc::connection that can be used to disconnect the callback
 * from the timeout source.
 */
sigc::connection threads_add_timeout(const sigc::slot<bool>& callback, guint interval, gint priority = Glib::PRIORITY_DEFAULT);


#ifndef CLUTTERMM_DISABLE_DEPRECATED

/** Sets a function to be called at regular intervals holding the Clutter
 * lock, with the given priority. The function is called repeatedly until it
 * returns false, at which point the timeout is automatically destroyed and
 * the function will not be called again. The first call to the function will
 * be at the end of the first interval.
 *
 * This function is similar to threads_add_timeout_full() except
 * that it will try to compensate for delays. For example, if func takes half
 * the interval time to execute then the function will be called again half
 * the interval time after it finished. In contrast
 * threads_add_timeout() would not fire until a full interval after the
 * function completes so the delay between calls would be interval * 1.5.
 * This function does not however try to invoke the function multiple times
 * to catch up missing frames if func takes more than interval ms to execute.
 *
 * This variant of frame_source_add() can be thought of a MT-safe version for
 * Clutter actors.
 *
 * @param callback function to call
 * @param interval the time between calls to the function, in milliseconds
 * @param the priority of the timeout source. Typically this will be in the range between Glib::PRIORITY_DEFAULT and Glib::PRIORITY_HIGH.
 * @return A sigc::connection that can be used to disconnect the callback from the timeout source.
 *
 * @deprecated This function is no longer useful.
 */
sigc::connection threads_add_frame_source(const sigc::slot<bool>& callback, guint interval, gint priority = Glib::PRIORITY_DEFAULT);

#endif //CLUTTERMM_DISABLE_DEPRECATED

} //namespace Clutter

#endif //_LIBCLUTTERMM_THREADS_H

