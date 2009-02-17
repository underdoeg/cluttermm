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

#include "multiline_entry.h"
#include <cluttermm.h>
#include <pangomm/init.h>

int main(int argc, char** argv)
{
  Pango::init();
  Clutter::init(&argc, &argv);

  // Get the stage and set its size and color:
  const Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default();
  stage->set_size(400, 400);
  stage->set_color(Clutter::Color(0x00, 0x00, 0x00, 0xFF)); // black

  // Add our multiline entry to the stage
  const Glib::RefPtr<Tutorial::MultilineEntry>
    multiline = Tutorial::MultilineEntry::create();
  multiline->set_text(
    "And as I sat there brooding on the old, unknown world, I thought of "
    "Gatsby's wonder when he first picked out the green light at the end of "
    "Daisy's dock. He had come a long way to this blue lawn and his dream "
    "must have seemed so close that he could hardly fail to grasp it. He did "
    "not know that it was already behind him, somewhere back in that vast "
    "obscurity beyond the city, where the dark fields of the republic rolled "
    "on under the night.");
  multiline->set_color(Clutter::Color(0xAE, 0xFF, 0x7F, 0xFF));
  multiline->set_size(380, 380);
  multiline->set_position(10, 10);
  stage->add_actor(multiline);
  multiline->show();

  // Connect signal handlers to handle key presses on the stage:
  stage->signal_key_press_event().connect(
    sigc::mem_fun(*multiline.operator->(), &Tutorial::MultilineEntry::handle_key_event));

  stage->show();

  // Start the main loop, so we can respond to events:
  Clutter::main();

  return 0;
}
