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

#include "triangle_actor.h"
#include <cluttermm.h>

int main(int argc, char** argv)
{
  Clutter::init(&argc, &argv);

  // Get the stage and set its size and color
  Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default();
  stage->set_size(200, 200);
  stage->set_color(Clutter::Color(0x00, 0x00, 0x00, 0xFF)); // black

  // Add our custom actor to the stage
  Glib::RefPtr<Tutorial::Triangle> actor =
      Tutorial::Triangle::create(Clutter::Color(0xFF, 0xFF, 0xFF, 0x99));
  actor->set_size(100, 100);
  actor->set_position(20, 20);
  stage->add_actor(actor);
  actor->show();

  // Show the stage
  stage->show();

  // Start the main loop, so we can respond to events
  Clutter::main();

  return 0;
}
