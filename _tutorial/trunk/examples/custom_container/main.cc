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
#include <cluttermm.h>

int main(int argc, char** argv)
{
  Clutter::init(&argc, &argv);

  // Get the stage and set its size and color:
  const Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default();
  stage->set_size(200, 200);
  stage->set_color(Clutter::Color(0x00, 0x00, 0x00, 0xFF)); // black

  // Add our custom container to the stage:
  const Glib::RefPtr<Tutorial::Box> box = Tutorial::Box::create();

  // Set the size to the preferred size of the container:
  box->set_size(-1, -1);
  box->set_position(20, 20);

  // Add some actors to our container:
  const Glib::RefPtr<Clutter::Rectangle>
    rect1 = Clutter::Rectangle::create(Clutter::Color(0xFF, 0xFF, 0xFF, 0x99));
  rect1->set_size(75, 75);
  box->add_actor(rect1);

  const Glib::RefPtr<Clutter::Rectangle>
    rect2 = Clutter::Rectangle::create(Clutter::Color(0x10, 0x40, 0x90, 0xFF));
  rect2->set_size(75, 75);
  box->add_actor(rect2);

  stage->add_actor(box);
  box->show_all();
  stage->show();

  // Start the main loop, so we can respond to events:
  Clutter::main();

  return 0;
}
