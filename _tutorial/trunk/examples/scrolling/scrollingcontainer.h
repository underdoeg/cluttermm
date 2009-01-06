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

#ifndef CLUTTER_TUTORIAL_SCROLLINGCONTAINER_H
#define CLUTTER_TUTORIAL_SCROLLINGCONTAINER_H

#include <cluttermm.h>

namespace Tutorial
{

class ScrollingContainer : public Clutter::Actor, public Clutter::Container
{
public:
  virtual ~ScrollingContainer();
  static Glib::RefPtr<ScrollingContainer> create();

  void scroll_left(int distance);

protected:
  ScrollingContainer();

  // Clutter::Container interface:
  virtual void add_vfunc(const Glib::RefPtr<Actor>& actor);
  virtual void remove_vfunc(const Glib::RefPtr<Actor>& actor);
  virtual void raise_vfunc(const Glib::RefPtr<Actor>& actor, const Glib::RefPtr<Actor>& sibling);
  virtual void lower_vfunc(const Glib::RefPtr<Actor>& actor, const Glib::RefPtr<Actor>& sibling);
  virtual void sort_depth_order_vfunc();
  virtual void foreach_vfunc(ClutterCallback callback, gpointer user_data);

  // Clutter::Actor interface:
  virtual void on_paint();
  virtual void on_show();
  virtual void on_hide();
  virtual void show_all_vfunc();
  virtual void hide_all_vfunc();
  virtual void pick_vfunc(const Clutter::Color& color);
  virtual void allocate_vfunc(const Clutter::ActorBox& box, bool absolute_origin_changed);

private:
  Glib::RefPtr<Clutter::Rectangle> border_;
  Glib::RefPtr<Clutter::Group> children_;
  int offset_;
};

} // namespace Tutorial

#endif /* CLUTTER_TUTORIAL_SCROLLINGCONTAINER_H */
