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

#include "scrollingcontainer.h"
#include <cluttermm.h>
#include <iostream>

namespace
{

static bool on_stage_button_press(Clutter::ButtonEvent*,
                                  Glib::RefPtr<Tutorial::ScrollingContainer> scrolling)
{
  std::cout << "Scrolling\n";

  scrolling->scroll_left(10);

  return true; // stop further handling of this event
}

} // anonymous namespace

int main(int argc, char** argv)
{
  Clutter::init(&argc, &argv);

  // Get the stage and set its size and color
  const Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default();
  stage->set_size(200, 200);
  stage->set_color(Clutter::Color(0x00, 0x00, 0x00, 0xFF)); // black

  // Add our scrolling container to the stage
  const Glib::RefPtr<Tutorial::ScrollingContainer>
    scrolling = Tutorial::ScrollingContainer::create();
  scrolling->set_size(180, 100);
  scrolling->set_position(10, 10);
  stage->add_actor(scrolling);

  // Add some actors to our container
  {
    const Glib::RefPtr<Clutter::Actor>
      actor = Clutter::Rectangle::create(Clutter::Color(0x7F, 0xAE, 0xFF, 0xFF));
    actor->set_size(75, 75);
    scrolling->add_actor(actor);
  }
  {
    const Glib::RefPtr<Clutter::Actor>
      actor = Clutter::Rectangle::create(Clutter::Color(0xFF, 0x7F, 0xAE, 0xFF));
    actor->set_size(75, 75);
    scrolling->add_actor(actor);
  }
  {
    const Glib::RefPtr<Clutter::Actor>
      actor = Clutter::Rectangle::create(Clutter::Color(0xAE, 0xFF, 0x7F, 0xFF));
    actor->set_size(75, 75);
    scrolling->add_actor(actor);
  }

  scrolling->show_all();
  stage->show();

  // Connect signal handlers to handle mouse clicks on the stage
  stage->signal_button_press_event().connect(sigc::bind(&on_stage_button_press, scrolling));

  // Start the main loop, so we can respond to events
  Clutter::main();

  return 0;
}
