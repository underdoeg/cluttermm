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

namespace
{

static Glib::RefPtr<Clutter::Rectangle> rect;

static int rotation_angle = 0;
static int color_change_count = 0;

/*
 * Rotate the rectangle and alternate its color.
 */
static void on_timeline_rotation_new_frame(int frame_num,
  Glib::RefPtr<Clutter::Timeline> timeline)
{
  if(++rotation_angle >= 360)
    rotation_angle = 0;

  // Rotate the rectangle clockwise around the z axis, around
  // it's top-left corner:
  rect->set_rotation(Clutter::X_AXIS, rotation_angle, 0, 0, 0);

  // Change the color
  // (This is a silly example, making the rectangle flash)
  if(++color_change_count > 100)
    color_change_count = 0;

  if(color_change_count == 0)
    rect->set_color(Clutter::Color(0xFF, 0xFF, 0xFF, 0x99));
  else if(color_change_count == 50)
    rect->set_color(Clutter::Color(0x10, 0x40, 0x90, 0xFF));
}

/*
 * Move the rectangle.
 */
static void on_timeline_move_new_frame(int frame_num,
  Glib::RefPtr<Clutter::Timeline> timeline)
{
  int x_position = rect->get_x();

  if(++x_position >= 150)
    x_position = 0;

  rect->set_x(x_position);
}

} // anonymous namespace

int main(int argc, char** argv)
{
  Clutter::init(&argc, &argv);

  // Get the stage and set its size and color:
  const Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default();
  stage->set_size(200, 200);
  stage->set_color(Clutter::Color(0x00, 0x00, 0x00, 0xFF));

  // Add a rectangle to the stage:
  rect = Clutter::Rectangle::create(Clutter::Color(0xFF, 0xFF, 0xFF, 0x99));
  rect->set_size(70, 70);
  rect->set_position(50, 100);
  stage->add_actor(rect);
  rect->show();

  // Show the stage:
  stage->show();

  // Create a score and add two timelines to it,
  // so the second timeline starts when the first one stops:
  const Glib::RefPtr<Clutter::Score> score = Clutter::Score::create();
  score->set_loop(true);

  const Glib::RefPtr<Clutter::Timeline>
    timeline_rotation = Clutter::Timeline::create(200 /*frames*/, 120 /*fps*/);
  timeline_rotation->signal_new_frame()
    .connect(sigc::bind(&on_timeline_rotation_new_frame, timeline_rotation));
  score->append(timeline_rotation);

  const Glib::RefPtr<Clutter::Timeline>
    timeline_move = Clutter::Timeline::create(200 /*frames*/, 120 /*fps*/);
  timeline_move->signal_new_frame()
    .connect(sigc::bind(&on_timeline_move_new_frame, timeline_move));
  score->append(timeline_rotation, timeline_move);

  score->start();

  // Start the main loop, so we can respond to events:
  Clutter::main();

  return 0;
}
