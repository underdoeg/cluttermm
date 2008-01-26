#include <cluttermm.h>
#include <clutter/clutter.h>
#include <iostream>

Glib::RefPtr<Clutter::Actor> hand;

guint32 alpha_val = 0;

guint32 on_alpha(const Glib::RefPtr<Clutter::Alpha>& alpha)
{
  return ++alpha_val;
}

int
main (int argc, char *argv[])
{
    // initialize the C++ wrapper types
    Clutter::init(&argc, &argv);

    Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default ();

    // Create a timeline to manage animation
    Glib::RefPtr<Clutter::Timeline> timeline =
        Clutter::Timeline::create (1000, 60); // num frames, fps
    timeline->set_loop();

    // Set up some behaviours to handle scaling
    //Causes a Gobject (refcount?) warning: Glib::RefPtr<Clutter::Alpha> alpha =
    //    Clutter::Alpha::create (timeline, Clutter::ALPHA_SINE);
    Glib::RefPtr<Clutter::Alpha> alpha =
        Clutter::Alpha::create (timeline, sigc::ptr_fun(&on_alpha));

    Glib::RefPtr<Clutter::BehaviourScale> scaler_1 =
        Clutter::BehaviourScale::create (alpha,
                0.5, 0.5,
                1.0, 1.0,
                Clutter::GRAVITY_CENTER);

    // Show everying ( and map window )
    stage->show ();

    // and start it
    timeline->start ();

    clutter_main ();

    return 0;
}

