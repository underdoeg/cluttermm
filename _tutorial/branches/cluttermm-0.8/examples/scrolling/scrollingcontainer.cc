/* Copyright 2008 Openismus GmbH, 
 * based on ClutterBox and ClutterHBox from Clutter 0.4
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

#include "scrollingcontainer.h"
#include <algorithm>

namespace
{

static void allocate_child(const Glib::RefPtr<Clutter::Actor>& actor,
  int& child_x, bool absolute_origin_changed)
{
  Clutter::Unit min_width  = 0;
  Clutter::Unit min_height = 0;
  Clutter::Unit width      = 0;
  Clutter::Unit height     = 0;

  actor->get_preferred_size(min_width, min_height, width, height);

  const Clutter::ActorBox child_box (CLUTTER_UNITS_FROM_DEVICE(child_x), 0,
    CLUTTER_UNITS_FROM_DEVICE(child_x) + width, height);

  actor->allocate(child_box, absolute_origin_changed);

  child_x += CLUTTER_UNITS_TO_DEVICE(width);
}

} // anonymous namespace

namespace Tutorial
{

/*
 * Tutorial::ScrollingContainer shows only a small area of its child
 * actors, and the child actors can be scrolled left under that area.
 */

ScrollingContainer::ScrollingContainer()
:
  Glib::ObjectBase(typeid(ScrollingContainer)),
  border_(Clutter::Rectangle::create(Clutter::Color(0xFF, 0xFF, 0xCC, 0xFF))),
  children_(Clutter::Group::create()),
  offset_(0)
{
  // Ugly but necessary: Explicitely acquire an additional reference
  // because Glib::RefPtr assumes ownership.
  const Glib::RefPtr<Clutter::Actor> self ((reference(), this));
  border_->set_parent(self);
  children_->set_parent(self);

  children_->signal_actor_added().connect(sigc::mem_fun(*this, &ScrollingContainer::actor_added));
  children_->signal_actor_removed().connect(sigc::mem_fun(*this, &ScrollingContainer::actor_removed));
}

ScrollingContainer::~ScrollingContainer()
{
  children_->unparent();
  border_->unparent();
}

Glib::RefPtr<ScrollingContainer> ScrollingContainer::create()
{
  return Glib::RefPtr<ScrollingContainer>(new ScrollingContainer());
}

/*
 * Scroll all the child widgets left, resulting in some parts
 * being hidden, and some parts becoming visible.
 */
void ScrollingContainer::scroll_left(int distance)
{
  offset_ += distance;
  queue_relayout();
}

void ScrollingContainer::add_vfunc(const Glib::RefPtr<Clutter::Actor>& actor)
{
  children_->add_actor(actor);
  queue_relayout();
}

void ScrollingContainer::remove_vfunc(const Glib::RefPtr<Clutter::Actor>& actor)
{
  children_->remove_actor(actor);
  queue_relayout();
}

void ScrollingContainer::raise_vfunc(const Glib::RefPtr<Clutter::Actor>&,
  const Glib::RefPtr<Clutter::Actor>&)
{
  g_assert_not_reached();
}

void ScrollingContainer::lower_vfunc(const Glib::RefPtr<Clutter::Actor>&,
  const Glib::RefPtr<Clutter::Actor>&)
{
  g_assert_not_reached();
}

void ScrollingContainer::sort_depth_order_vfunc()
{
  g_assert_not_reached();
}

void ScrollingContainer::foreach_vfunc(ClutterCallback callback, gpointer user_data)
{
  clutter_container_foreach(children_->Clutter::Container::gobj(), callback, user_data);
}

void ScrollingContainer::on_paint()
{
  border_  ->paint();
  children_->paint();
}

void ScrollingContainer::on_show()
{
  border_  ->show();
  children_->show();
  Clutter::Actor::on_show();
}

void ScrollingContainer::on_hide()
{
  Clutter::Actor::on_hide();
  children_->hide();
  border_  ->hide();
}

void ScrollingContainer::show_all_vfunc()
{
  children_->show_all();
  show();
}

void ScrollingContainer::hide_all_vfunc()
{
  hide();
  children_->hide_all();
}

void ScrollingContainer::pick_vfunc(const Clutter::Color& color)
{
  if(border_->is_mapped())
    border_->pick(color);

  children_->pick(color);
}

void ScrollingContainer::allocate_vfunc(const Clutter::ActorBox& box, bool absolute_origin_changed)
{
  const Clutter::Unit width  = std::max<Clutter::Unit>(0, box.get_x2() - box.get_x1());
  const Clutter::Unit height = std::max<Clutter::Unit>(0, box.get_y2() - box.get_y1());

  Clutter::ActorBox child_box (0, 0, width, height);

  // Position the child at the top of the container:
  children_->allocate(child_box, absolute_origin_changed);

  // Make sure that the group only shows the specified area, by clipping:
  children_->set_clip(0, 0, CLUTTER_UNITS_TO_DEVICE(width), CLUTTER_UNITS_TO_DEVICE(height));

  // Show a rectangle border to show the area:
  border_->allocate(child_box, absolute_origin_changed);

  int child_x = -offset_;
  children_->foreach(sigc::bind(&allocate_child, sigc::ref(child_x), absolute_origin_changed));

  Clutter::Actor::allocate_vfunc(box, absolute_origin_changed);
}

} // namespace Tutorial
