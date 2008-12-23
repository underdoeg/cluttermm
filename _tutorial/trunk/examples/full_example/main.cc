/* Copyright 2007 Openismus GmbH
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
#include <glibmm.h>
#include <algorithm>
#include <list>
#include <string>
#include <cmath>

namespace
{

enum
{
  ELLIPSE_Y      = 390, // the y position of the ellipse of images
  ELLIPSE_HEIGHT = 450, // the distance from front to back when it's rotated 90 degrees
  IMAGE_HEIGHT   = 100
};

const double angle_step = 30.0;

struct Item
{
  std::string                             filepath;
  Glib::RefPtr<Clutter::Texture>          texture;
  Glib::RefPtr<Clutter::BehaviourEllipse> behaviour;

  Item() {}
  explicit Item(const std::string& path)
    : filepath (path), texture (Clutter::Texture::create_from_file(path)) {}
};

class Example : public sigc::trackable
{
public:
  Example();
  virtual ~Example();

private:
  std::list<Item>                   items_;
  std::list<Item>::iterator         front_item_;

  Glib::RefPtr<Clutter::Stage>      stage_;

  // For showing the filename:
  Glib::RefPtr<Clutter::Label>      label_filename_;

  // For rotating all images around an ellipse:
  Glib::RefPtr<Clutter::Timeline>   timeline_rotation_;

  // For moving one image up and scaling it:
  Glib::RefPtr<Clutter::Timeline>   timeline_moveup_;
  Glib::RefPtr<Clutter::Behaviour>  behaviour_scale_;
  Glib::RefPtr<Clutter::Behaviour>  behaviour_path_;
  Glib::RefPtr<Clutter::Behaviour>  behaviour_opacity_;

  void load_images(const std::string& directory_path);
  void add_image_actors();

  bool on_texture_button_press(Clutter::ButtonEvent* event, std::list<Item>::iterator pitem);
  void on_timeline_moveup_completed();
  void on_timeline_rotation_completed();
  void rotate_item_to_front(std::list<Item>::iterator pitem);
};

static void scale_texture_default(const Glib::RefPtr<Clutter::Texture>& texture)
{
  int width  = 0;
  int height = 0;
  texture->get_base_size(width, height);

  if (height > 0)
  {
    const double scale = IMAGE_HEIGHT / double(height);
    texture->set_scale(scale, scale);
  }
}

Example::Example()
:
  items_             (),
  front_item_        (items_.end()),
  stage_             (Clutter::Stage::get_default()),
  label_filename_    (Clutter::Label::create()),
  timeline_rotation_ (Clutter::Timeline::create(60 /*frames*/, 30 /*fps*/))
{
  stage_->set_size(800, 600);
  stage_->set_color(Clutter::Color(0xB0, 0xB0, 0xB0, 0xFF)); // light gray

  // Create and add a label actor, hidden at first
  label_filename_->set_color(Clutter::Color(0x60, 0x60, 0x90, 0xFF)); // blueish
  label_filename_->set_font_name("Sans 24");
  label_filename_->set_position(10, 10);
  label_filename_->set_opacity(0);
  stage_->add_actor(label_filename_);
  label_filename_->show();

  // Add a plane under the ellipse of images
  const Glib::RefPtr<Clutter::Actor> rect =
      Clutter::Rectangle::create(Clutter::Color(0xFF, 0xFF, 0xFF, 0xFF)); // white

  rect->set_width(stage_->get_width() + 100);
  rect->set_height(ELLIPSE_HEIGHT + 20);
  // Position it so that its center is under the images
  rect->set_position(-(rect->get_width() - stage_->get_width()) / 2,
                     ELLIPSE_Y + IMAGE_HEIGHT - rect->get_height() / 2);
  // Rotate it around its center
  rect->set_rotation(Clutter::X_AXIS, -90.0, 0, rect->get_height() / 2, 0);
  stage_->add_actor(rect);
  rect->show();

  // Show the stage
  stage_->show();

  timeline_rotation_->signal_completed()
    .connect(sigc::mem_fun(*this, &Example::on_timeline_rotation_completed));

  // Add an actor for each image
  load_images("images");
  add_image_actors();
#if 0
  timeline_rotation_->set_loop(true);
#endif
  // Move them a bit to start with
  if (!items_.empty())
    rotate_item_to_front(items_.begin());
}

Example::~Example()
{}

void Example::load_images(const std::string& directory_path)
{
  // Clear any existing images
  items_.clear();

  Glib::Dir dir (directory_path);

  for (Glib::Dir::iterator p = dir.begin(); p != dir.end(); ++p)
  {
    const std::string path = Glib::build_filename(directory_path, *p);
    try
    {
      const Item item (path);

      scale_texture_default(item.texture);
      items_.push_back(item);
    }
    catch (const Glib::Error&)
    {}
  }
}

void Example::add_image_actors()
{
  int x = 20;
  int y = 0;
  double angle = 0.0;

  for (std::list<Item>::iterator p = items_.begin(); p != items_.end(); ++p)
  {
    const Glib::RefPtr<Clutter::Actor> actor = p->texture;

    // Add the actor to the stage
    stage_->add_actor(actor);

    // Set an initial position
    actor->set_position(x, y);
    y += 100;

    // Allow the actor to emit events.  By default only the stage does this.
    actor->set_reactive(true);

    actor->signal_button_press_event().connect(
        sigc::bind(sigc::mem_fun(*this, &Example::on_texture_button_press), p));

    const Glib::RefPtr<Clutter::Alpha> alpha =
        Clutter::Alpha::create(timeline_rotation_, &Clutter::Alpha::sine_inc_func);

    p->behaviour = Clutter::BehaviourEllipse
        ::create(alpha, 320, ELLIPSE_Y, // x, y
                 ELLIPSE_HEIGHT, ELLIPSE_HEIGHT, // width, height
                 Clutter::ROTATE_CW,
                 angle, angle + 360.0);

    p->behaviour->set_angle_tilt(Clutter::X_AXIS, -90.0);
    p->behaviour->apply(actor);
    actor->show();

    angle += angle_step;
  }
}

/*
 * This signal handler is called when the item has finished
 * moving up and increasing in size.
 */
void Example::on_timeline_moveup_completed()
{
  // Unref this timeline because we have now finished with it
  timeline_moveup_.clear();
  behaviour_scale_.clear();
  behaviour_path_.clear();
  behaviour_opacity_.clear();
}

/*
 * This signal handler is called when the items have completely
 * rotated around the ellipse.
 */
void Example::on_timeline_rotation_completed()
{
  // All the items have now been rotated so that the clicked item is at the
  // front.  Now we transform just this one item gradually some more, and
  // show the filename.

  // Transform the image
  const Glib::RefPtr<Clutter::Actor> actor = front_item_->texture;
  timeline_moveup_ = Clutter::Timeline::create(60 /*frames*/, 30 /*fps*/);
  const Glib::RefPtr<Clutter::Alpha> alpha =
      Clutter::Alpha::create(timeline_moveup_, &Clutter::Alpha::sine_inc_func);
 
  // Scale the item from its normal scale to approximately twice the normal scale
  double scale_start = 0.0;
  actor->get_scale(scale_start, scale_start);
  const double scale_end = scale_start * 1.8;

  behaviour_scale_ = Clutter::BehaviourScale::create(alpha,
                                                     scale_start, scale_start,
                                                     scale_end, scale_end);
  behaviour_scale_->apply(actor);

  // Move the item up the y axis
  std::vector<Clutter::Knot> knots (2);
  knots[0].set_xy(actor->get_x(), actor->get_y());
  knots[1].set_xy(knots[0].get_x(), knots[0].get_y() - 250);

  behaviour_path_ = Clutter::BehaviourPath::create_with_knots(alpha, knots);
  behaviour_path_->apply(actor);

  // Show the filename gradually
  label_filename_->set_text(front_item_->filepath);
  behaviour_opacity_ = Clutter::BehaviourOpacity::create(alpha, 0, 255);
  behaviour_opacity_->apply(label_filename_);

  // Start the timeline and handle its "completed" signal so we can unref it
  timeline_moveup_->signal_completed()
    .connect(sigc::mem_fun(*this, &Example::on_timeline_moveup_completed));
  timeline_moveup_->start();
}

void Example::rotate_item_to_front(std::list<Item>::iterator pitem)
{
  g_return_if_fail(pitem != items_.end());

  timeline_rotation_->stop();

  // Stop the other timeline in case that is active at the same time
  if (timeline_moveup_)
    timeline_moveup_->stop();

  label_filename_->set_opacity(0);

  // Get the item's position in the list
  const int pos = std::distance(items_.begin(), pitem);

  if (front_item_ == items_.end())
    front_item_ = items_.begin();

  const int pos_front = std::distance(items_.begin(), front_item_);

  // Calculate the end angle of the first item
  const double angle_front = 180.0;
  double angle_start = std::fmod(angle_front - (angle_step * pos_front), 360.0);
  double angle_end   = angle_front - (angle_step * pos);

  double angle_diff = 0.0;

  // Set the end angles
  for (std::list<Item>::iterator p = items_.begin(); p != items_.end(); ++p)
  {
    // Reset its size
    scale_texture_default(p->texture);

    angle_start = std::fmod(angle_start, 360.0);
    angle_end   = std::fmod(angle_end,   360.0);

    // Move 360° instead of 0° when moving for the first time,
    // and when clicking on something that is already at the front.
    if (front_item_ == pitem)
      angle_end += 360.0;

    p->behaviour->set_angle_start(angle_start);
    p->behaviour->set_angle_end(angle_end);

    if (p == pitem)
    {
      if (angle_start < angle_end)
        angle_diff = angle_end - angle_start;
      else
        angle_diff = 360 - (angle_start - angle_end);
    }

    // TODO: Set the number of frames, depending on the angle.
    // otherwise the actor will take the same amount of time to reach 
    // the end angle regardless of how far it must move, causing it to 
    // move very slowly if it does not have far to move.
    angle_end   += angle_step;
    angle_start += angle_step;
  }

  // Set the number of frames to be proportional to the distance to travel,
  // so the speed is always the same
  const int pos_to_move = (pos_front < pos) ? items_.size() + (pos - pos_front)
                                            : pos_front - pos;
  timeline_rotation_->set_n_frames(angle_diff);

  // Remember what item will be at the front when this timeline finishes
  front_item_ = pitem;

  timeline_rotation_->start();
}

bool Example::on_texture_button_press(Clutter::ButtonEvent* event, std::list<Item>::iterator pitem)
{
  // Ignore the events if the timeline_rotation is running (meaning,
  // if the objects are moving), to simplify things.
  if (timeline_rotation_ && timeline_rotation_->is_playing())
  {
    g_print("on_texture_button_press(): ignoring\n");
    return false;
  }
  else
    g_print("on_texture_button_press(): handling\n");

  rotate_item_to_front(pitem);
  return true;
}

} // anonymous namespace

int main(int argc, char** argv)
{
  Clutter::init(&argc, &argv);

  Example example;

  // Start the main loop, so we can respond to events
  Clutter::main();

  return 0;
}
