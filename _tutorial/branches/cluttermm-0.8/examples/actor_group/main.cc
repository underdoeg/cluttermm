/*
 * Copyright (c) 2008 Openismus GmbH
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

#include <cluttermm.h>

int main(int argc, char** argv)
{
  Clutter::init(&argc, &argv);

  // Get the stage and set its size and color:
  const Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default();
  stage->set_size(200, 200);
  stage->set_color(Clutter::Color(0, 0, 0, 0xFF)); // black

  // Add a group to the stage:
  const Glib::RefPtr<Clutter::Group> group = Clutter::Group::create();
  group->set_position(40, 40);
  stage->add_actor(group);
  group->show();

  const Clutter::Color actor_color (0xFF, 0xFF, 0xFF, 0x99);

  // Add a rectangle to the group:
  const Glib::RefPtr<Clutter::Rectangle>
    rect = Clutter::Rectangle::create(actor_color);
  rect->set_size(50, 50);
  rect->set_position(0, 0);
  group->add_actor(rect);
  rect->show();

  // Add a label to the group:
  const Glib::RefPtr<Clutter::Label>
    label = Clutter::Label::create("Sans 9", "Some Text", actor_color);
  label->set_position(0, 60);
  group->add_actor (label);
  label->show();

  // Scale the group 120% along the x axis:
  group->set_scale(3.00, 1.0);

  // Rotate it around the z axis:
  group->set_rotation(Clutter::Z_AXIS, 10, 0, 0, 0);

  // Show the stage:
  stage->show();

  // Start the main loop, so we can respond to events:
  Clutter::main();

  return 0;
}
