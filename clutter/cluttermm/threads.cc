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

#include <cluttermm/threads.h>
#include <clutter/clutter.h>

#ifndef CLUTTERMM_DISABLE_DEPRECATED

namespace
{

// Inspired by glibmm, see glibmm/main.cc
class SourceConnectionNode
{
public:
  explicit inline SourceConnectionNode(const sigc::slot_base& slot);

  static void* notify(void* data);
  static void destroy_notify_callback(void* data);
  inline void install(guint id);
  inline sigc::slot_base* get_slot();

private:
  sigc::slot_base slot_;
  guint           source_id_;
};

SourceConnectionNode::SourceConnectionNode(const sigc::slot_base& slot)
:
  slot_      (slot),
  source_id_ (0)
{
  slot_.set_parent(this, &SourceConnectionNode::notify);
}

void* SourceConnectionNode::notify(void* data)
{
  SourceConnectionNode* const self = static_cast<SourceConnectionNode*>(data);
  if(self->source_id_)
  {
    g_source_remove(self->source_id_);
    self->source_id_ = 0;

    // Removing the source triggers the destroy_notify_handler, wait until
    // that for deletion.
  }
  return 0;
}

void SourceConnectionNode::destroy_notify_callback(void* data)
{
  SourceConnectionNode* const self = static_cast<SourceConnectionNode*>(data);
  self->source_id_ = 0;
  delete self;
}

inline
void SourceConnectionNode::install(guint source_id)
{
  source_id_ = source_id;
}

inline
sigc::slot_base* SourceConnectionNode::get_slot()
{
  return &slot_;
}

static
gboolean source_callback(void* data)
{
  SourceConnectionNode* const conn_data = static_cast<SourceConnectionNode*>(data);
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
#endif
  {
    // Recreate the specific slot from the generic slot node
    return (*static_cast<sigc::slot<bool>*>(conn_data->get_slot()))();
  }
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  catch(...)
  {
    Glib::exception_handlers_invoke();
  }
#endif
  return FALSE;
}

} // anonymous namespace

#endif //CLUTTERMM_DISABLE_DEPRECATED

namespace Clutter
{

#ifndef CLUTTERMM_DISABLE_DEPRECATED

void threads_init()
{
  clutter_threads_init();
}

void threads_enter()
{
  clutter_threads_enter();
}

void threads_leave()
{
  clutter_threads_leave();
}
#endif //CLUTTERMM_DISABLE_DEPRECATED

// TODO: This is unlikely to be thread-safe because of the returned connection
// object.  It's the same problem as with the glibmm idle source.
sigc::connection threads_add_idle(const sigc::slot<bool>& callback, int priority)
{
  SourceConnectionNode* const conn_node = new SourceConnectionNode(callback);
  const sigc::connection connection (*conn_node->get_slot());

  conn_node->install(clutter_threads_add_idle_full(priority, &source_callback, conn_node,
                                                   &SourceConnectionNode::destroy_notify_callback));
  return connection;
}

sigc::connection threads_add_timeout(const sigc::slot<bool>& callback,
                                     guint interval, int priority)
{
  SourceConnectionNode* const conn_node = new SourceConnectionNode(callback);
  const sigc::connection connection (*conn_node->get_slot());

  conn_node->install(clutter_threads_add_timeout_full(
      priority, interval, &source_callback, conn_node,
      &SourceConnectionNode::destroy_notify_callback));
  return connection;
}


#ifndef CLUTTERMM_DISABLE_DEPRECATED

sigc::connection threads_add_frame_source(const sigc::slot<bool>& callback,
                                          guint interval, int priority)
{
  SourceConnectionNode* const conn_node = new SourceConnectionNode(callback);
  const sigc::connection connection (*conn_node->get_slot());

  conn_node->install(clutter_threads_add_frame_source_full(
      priority, interval, &source_callback, conn_node,
      &SourceConnectionNode::destroy_notify_callback));
  return connection;
}

#endif //CLUTTERMM_DISABLE_DEPRECATED


} // namespace Clutter
