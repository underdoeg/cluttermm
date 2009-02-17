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
#include <iostream>

namespace
{

bool on_stage_button_press(Clutter::ButtonEvent* event)
{
  int x = 0;
  int y = 0;
  // TODO: Wrap properly
  clutter_event_get_coords(reinterpret_cast<Clutter::Event*>(event), &x, &y);

  std::cout << "Stage clicked at (" << x << ", " << y << ")\n";

  return true; // stop further handling of this event
}

} // anonymous namespace

int main(int argc, char** argv)
{
  try
  {
    Clutter::init(&argc, &argv);

    // Get the stage and set its size and color:
    Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default();
    stage->set_size(200, 200);
    stage->set_color(Clutter::Color(0, 0, 0)); // black

    stage->show();

    // Connect a signal handler to handle mouse clicks:
    stage->signal_button_press_event().connect(&on_stage_button_press);

    // Start the main loop, so we can respond to events:
    Clutter::main();
  }
  catch (const Glib::Error& error)
  {
    std::cerr << "Exception: " << error.what() << std::endl;
    return 1;
  }

  return 0;
}
