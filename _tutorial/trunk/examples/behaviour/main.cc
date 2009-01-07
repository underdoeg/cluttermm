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

/*
 * This must return a value between 0 and Clutter::Alpha::MAX_ALPHA, where
 * 0 means the start of the path, and Clutter::Alpha::MAX_ALPHA is the end
 * of the path.
 *
 * This will be called as many times per seconds as specified in our call
 * to Clutter::Timeline::create().
 *
 * See also, for instance Clutter::Alpha::SINE_HALF for a useful built-in
 * callback.
 */
static guint32 on_alpha(Glib::RefPtr<Clutter::Alpha> alpha)
{
  // Get the position in the timeline, so we can base our value upon it:
  const Glib::RefPtr<Clutter::Timeline> timeline = alpha->get_timeline();
  const int current_frame_num = timeline->get_current_frame();
  const int n_frames = timeline->get_n_frames();

  // Return a value that is simply proportional to the frame position:
  return Clutter::Alpha::MAX_ALPHA * current_frame_num / n_frames;
}

} // anonymous namespace

int main(int argc, char** argv)
{
  Clutter::init(&argc, &argv);

  // Get the stage and set its size and color:
  const Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default();
  stage->set_size(200, 200);
  stage->set_color(Clutter::Color(0x00, 0x00, 0x00, 0xFF)); // black

  // Add a rectangle to the stage:
  rect = Clutter::Rectangle::create(Clutter::Color(0xFF, 0xFF, 0xFF, 0x99));
  rect->set_size(40, 40);
  rect->set_position(10, 10);
  stage->add_actor(rect);
  rect->show();

  // Show the stage:
  stage->show();

  {
    const Glib::RefPtr<Clutter::Timeline>
      timeline = Clutter::Timeline::create(10 /*frames*/, 30 /*fps*/);
    timeline->set_loop(true);
    timeline->start();

    // Instead of our custom callback, we could use a standard callback.
    // For instance, Clutter::Alpha::sine_inc_func.
    const Glib::RefPtr<Clutter::Alpha>
      alpha = Clutter::Alpha::create(timeline, &on_alpha);

    std::vector<Clutter::Knot> knots (2);
    knots[0].set_xy(10, 10);
    knots[1].set_xy(150, 150);

    const Glib::RefPtr<Clutter::Behaviour>
      behaviour = Clutter::BehaviourPath::create_with_knots(alpha, knots);
    behaviour->apply(rect);
  }

  // Start the main loop, so we can respond to events:
  Clutter::main();

  return 0;
}
