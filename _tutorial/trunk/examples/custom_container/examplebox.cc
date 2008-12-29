/*
 * Copyright (c) 2008 Openismus GmbH
 * Based on ClutterBox and ClutterHBox from Clutter 0.4.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "examplebox.h"
#include <cogl/cogl.h>

namespace Tutorial
{

/*
 * Simple example of a container actor.
 *
 * Tutorial::Box imposes a specific layout on its children, unlike
 * Clutter::Group which is a free-form container.
 *
 * Specifically, Tutorial::Box lays out its children along an imaginary
 * horizontal line.
 */

Box::Box()
:
  // Create a named GObject type for the custom container class
  Glib::ObjectBase(typeid(Box))
{
  property_request_mode() = Clutter::REQUEST_WIDTH_FOR_HEIGHT;
}

Box::~Box()
{
  remove_all();
}

Glib::RefPtr<Box> Box::create()
{
  return Glib::RefPtr<Box>(new Box());
}

void Box::remove_all()
{
  while (!children_.empty())
    remove_actor(children_.front());
}

void Box::add_vfunc(const Glib::RefPtr<Clutter::Actor>& actor)
{
  children_.push_front(actor);

  // Ugly but necessary:  Explicitely acquire an additional reference
  // because Glib::RefPtr assumes ownership.
  actor->set_parent(Glib::RefPtr<Clutter::Actor>((reference(), this)));
  actor_added(actor);
  queue_relayout();
}

void Box::remove_vfunc(const Glib::RefPtr<Clutter::Actor>& actor)
{
  const Glib::RefPtr<Clutter::Actor> element = actor;
  const ChildrenList::iterator p = std::find(children_.begin(), children_.end(), element);

  if (p != children_.end())
  {
    element->unparent();
    children_.erase(p);
    actor_removed(element);
    queue_relayout();
  }
}

void Box::raise_vfunc(const Glib::RefPtr<Clutter::Actor>&, const Glib::RefPtr<Clutter::Actor>&)
{
  g_assert_not_reached();
}

void Box::lower_vfunc(const Glib::RefPtr<Clutter::Actor>&, const Glib::RefPtr<Clutter::Actor>&)
{
  g_assert_not_reached();
}

void Box::sort_depth_order_vfunc()
{
  g_assert_not_reached();
}

void Box::foreach_vfunc(ClutterCallback callback, gpointer user_data)
{
  for (ChildrenList::iterator p = children_.begin(); p != children_.end(); ++p)
    callback((*p)->gobj(), user_data);
}

void Box::on_paint()
{
  cogl_push_matrix();

  for (ChildrenList::iterator p = children_.begin(); p != children_.end(); ++p)
  {
    if ((*p)->is_mapped())
      (*p)->paint();
  }

  cogl_pop_matrix();
}

void Box::show_all_vfunc()
{
  for (ChildrenList::iterator p = children_.begin(); p != children_.end(); ++p)
    (*p)->show();

  show();
}

void Box::hide_all_vfunc()
{
  hide();

  for (ChildrenList::iterator p = children_.begin(); p != children_.end(); ++p)
    (*p)->hide();
}

void Box::pick_vfunc(const Clutter::Color& color)
{
  for (ChildrenList::iterator p = children_.begin(); p != children_.end(); ++p)
  {
    if ((*p)->is_mapped())
      (*p)->pick(color);
  }
}

/*
 * For this container, the preferred width is the sum of the widths
 * of the children. The preferred width depends on the height provided
 * by for_height.
 */
void Box::get_preferred_width_vfunc(Clutter::Unit  for_height,
                                    Clutter::Unit& min_width_p,
                                    Clutter::Unit& natural_width_p)
{
  Clutter::Unit min_width     = 0;
  Clutter::Unit natural_width = 0;

  // Calculate the preferred width for this container, 
  // based on the preferred width requested by the children.
  for (ChildrenList::iterator p = children_.begin(); p != children_.end(); ++p)
    if ((*p)->is_visible())
    {
      Clutter::Unit child_min_width     = 0;
      Clutter::Unit child_natural_width = 0;

      (*p)->get_preferred_width(for_height, child_min_width, child_natural_width);

      min_width     += child_min_width;
      natural_width += child_natural_width;
    }

  min_width_p     = min_width;
  natural_width_p = natural_width;
}

/*
 * For this container, the preferred height is the maximum height
 * of the children. The preferred height is independent of the given width.
 */
void Box::get_preferred_height_vfunc(Clutter::Unit  for_width,
                                     Clutter::Unit& min_height_p,
                                     Clutter::Unit& natural_height_p)
{
  Clutter::Unit min_height     = 0;
  Clutter::Unit natural_height = 0;

  // Calculate the preferred height for this container,
  // based on the preferred height requested by the children.
  for (ChildrenList::iterator p = children_.begin(); p != children_.end(); ++p)
    if ((*p)->is_visible())
    {
      Clutter::Unit child_min_height     = 0;
      Clutter::Unit child_natural_height = 0;

      (*p)->get_preferred_height(-1, child_min_height, child_natural_height);

      min_height     = std::max(min_height,     child_min_height);
      natural_height = std::max(natural_height, child_natural_height);
    }

  min_height_p     = min_height;
  natural_height_p = natural_height;
}

void Box::allocate_vfunc(const Clutter::ActorBox& box, bool absolute_origin_changed)
{
  Clutter::Unit child_x = 0;

  for (ChildrenList::iterator p = children_.begin(); p != children_.end(); ++p)
  {
    Clutter::Unit min_width    = 0;
    Clutter::Unit min_height   = 0;
    Clutter::Unit child_width  = 0;
    Clutter::Unit child_height = 0;

    (*p)->get_preferred_size(min_width, min_height, child_width, child_height);

    // Calculate the position and size that the child may actually have.
    // Position the child just after the previous child, horizontally.
    const Clutter::ActorBox child_box (child_x, 0, child_x + child_width, child_height);
    child_x += child_width;

    // Tell the child what position and size it may actually have
    (*p)->allocate(child_box, absolute_origin_changed);
  }

  Clutter::Actor::allocate_vfunc(box, absolute_origin_changed);
}

} // namespace Tutorial
