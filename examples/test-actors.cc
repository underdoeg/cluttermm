#include <cluttermm.h>
#include <gdkmm/wrap_init.h>
#include <gdkmm/pixbuf.h>
#include <iostream>

namespace
{

Glib::RefPtr<Clutter::Stage> stage;
const unsigned int TRAILS = 0;
const unsigned int N_ACTORS = 6;

unsigned int get_radius(const Glib::RefPtr<Clutter::Stage>& stage, unsigned int num_actors)
{
  return (stage
    + stage) / num_actors;
}

class SuperOH
{
public:
  std::vector<Glib::RefPtr<Clutter::Actor> > hands;
  Glib::RefPtr<Clutter::Actor> bgtex;
  Glib::RefPtr<Clutter::Actor> group;
};

bool on_button_press(Clutter::ButtonEvent *event, const Glib::RefPtr<Clutter::Stage>& stage)
{
  g_print("*** button press event (button:%d) ***\n",
    event->button);

  Glib::RefPtr<Clutter::Actor> e = stage->get_actor_at_pos(Clutter::PICK_ALL, event->x, event->y);
  if(e)
    e->hide();

  return false;
}

bool on_key_release(Clutter::KeyEvent *event)
{
  g_print("*** key press event (key:%c) ***\n",
    Clutter::key_event_get_symbol(event));

  if(Clutter::key_event_get_symbol(event) == CLUTTER_KEY_q)
    Clutter::main_quit();

  return false;
}

// Timeline handler
void on_new_frame(int frame_num, SuperOH* oh)
{
  // Rotate everything clockwise about stage center
  oh->group->set_rotation_angle(Clutter::Z_AXIS,
    frame_num);
  oh->group->set_pivot_point(
    stage->get_width() / 2,
    stage->get_height() / 2);

  for(unsigned int i = 0; i < oh->hands.size(); i++)
  {
    double scale_x = 0;
    double scale_y = 0;
    oh->hands[i]->get_scale(scale_x, scale_y);

    /* Rotate each hand around their centers - to get this we need
     * to take into account any scaling.
     *
     * TODO: scaling causes drift so disabled for now. Need rotation
     * unit based functions to fix.
     */
    oh->hands[i]->set_rotation_angle(Clutter::Z_AXIS,
      - 6.0 * frame_num);
    oh->hands[i]->set_pivot_point(0, 0);
  }
}

} // anonymous namespace

int main(int argc, char *argv[])
{
  Glib::init(); //Otherwise Gdk::wrap_init() will fail.
  Gdk::wrap_init(); //TODO: Add a Gdk::init() in gtkmm?

  Glib::OptionEntry entry;
  entry.set_short_name('n');
  entry.set_long_name("num-actors");
  entry.set_description("Number of actors");
  entry.set_arg_description("ACTORS");

  Glib::OptionGroup group("actor", "Specifies actor properties");
  int num_actors = N_ACTORS;
  group.add_entry(entry, num_actors);

  Glib::OptionContext context;
  context.set_main_group(group);

  try
  {
    // initialize the C++ wrapper types
    Clutter::init(&argc, &argv, context);
  }
  catch(const Glib::Exception& ex)
  {
    std::cerr << "Failed to initialize clutter: " << ex.what() << std::endl;
    return -1;
  }

  Clutter::Color stage_color(0x61, 0x64, 0x8c, 0xff);
  stage = Clutter::Stage::create();
  stage->set_size(800, 600);

  stage->set_title("Actors Test");
  stage->set_background_color(stage_color);

  SuperOH oh;

  // Create a timeline to manage animation
  Glib::RefPtr<Clutter::Timeline> timeline =
    Clutter::Timeline::create(6000); // milliseconds
  timeline->set_repeat_count(-1); // have it loop

  // fire a callback for frame change
  timeline->signal_new_frame().connect
   (sigc::bind(sigc::ptr_fun(on_new_frame), &oh));

  // TODO: these next 3 objects are not currently used in the example, but
  // they cause problems on application exit.  If they are commented out, the
  // program runs and exits without problems.  There seems to be some sort of
  // reference-counting issue
  // Perhaps that's clutter bug #856.

  // Set up some behaviours to handle scaling
/* TODO:
  Glib::RefPtr<Clutter::Alpha> alpha =
    Clutter::Alpha::create(timeline, Clutter::EASE_IN_SINE);

  Glib::RefPtr<Clutter::BehaviourScale> scaler_1 =
    Clutter::BehaviourScale::create(alpha,
      0.5, 0.5,
      1.0, 1.0);

  Glib::RefPtr<Clutter::BehaviourScale> scaler_2 =
    Clutter::BehaviourScale::create(alpha,
      1.0, 1.0,
      0.5, 0.5);
*/

  // create a new group to hold multiple actors in a group
  oh.group = Clutter::Actor::create();

  oh.hands.reserve(num_actors);
  for(int i = 0; i < num_actors; i++)
  {
    int radius = get_radius(stage, num_actors);

    // Create an image from a file, then clone it to save resources
    if(i == 0)
    {
      Glib::RefPtr<Gdk::Pixbuf> pixbuf;
      try
      {
        pixbuf = Gdk::Pixbuf::create_from_file("actor.png");

        Glib::RefPtr<Clutter::Image> image = Clutter::Image::create();
        image->set_data(pixbuf->get_pixels(),
          (pixbuf->get_has_alpha() ? COGL_PIXEL_FORMAT_RGBA_8888 : COGL_PIXEL_FORMAT_RGB_888),
          pixbuf->get_width(),
          pixbuf->get_height(),
          pixbuf->get_rowstride());
        Glib::RefPtr<Clutter::Actor> actor = Clutter::Actor::create();
        actor->set_content(image);

        actor->set_content_scaling_filters(Clutter::SCALING_FILTER_TRILINEAR,
          Clutter::SCALING_FILTER_LINEAR);
        //TODO?: actor->set_content_gravity();

        oh.hands.push_back(actor);
      }
      catch(const Glib::Exception& ex)
      {
        std::cerr << "Could not load pixbuf: " << ex.what() << std::endl;
	return -1;
      }
    }
    else
    {
      oh.hands.push_back(Clutter::Clone::create
        (oh.hands[0]));
    }

    // Place around a circle
    int w = oh.hands[0]->get_width();
    int h = oh.hands[0]->get_height();

    int x = stage->get_width() / 2 
      + radius
      * cos(i * M_PI / (num_actors / 2))
      - w / 2;
    int y = stage->get_height() / 2 
      + radius
      * sin(i * M_PI / (num_actors / 2))
      - h / 2;

    oh.hands[i]->set_position(x, y);
    //TODO? oh.hands[i]->move_anchor_point_from_gravity(Clutter::GRAVITY_CENTER);

    // Add to our group group
    oh.group->add_child(oh.hands[i]);

#if 0 /* TODO: disabled as causes drift - see comment above */
    if(i % 2)
      scaler_1->apply(oh.hands[i]);
    else
      scaler_2->apply(oh.hands[i]);
#endif
  }

  // Add the group to the stage
  stage->add_child(oh.group);

  stage->show();

  stage->signal_button_press_event().connect(sigc::bind(sigc::ptr_fun
      (on_button_press), stage));

  stage->signal_key_release_event().connect(sigc::ptr_fun(on_key_release));

  // and start it
  timeline->start();

  // TODO: wrap clutter_main ?
  Clutter::main();

  return 0;
}
