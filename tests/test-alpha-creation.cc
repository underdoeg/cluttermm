#include <cluttermm.h>
#include <clutter/clutter.h>
#include <iostream>

Glib::RefPtr<Clutter::Actor> hand;

int
main (int argc, char *argv[])
{
    // initialize the C++ wrapper types
    Clutter::init(&argc, &argv);

    Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default ();

    // Create a timeline to manage animation
    Glib::RefPtr<Clutter::Timeline> timeline =
        Clutter::Timeline::create (360, 60); // num frames, fps

    // Set up some behaviours to handle scaling
    //Causes a Gobject (refcount?) warning: Glib::RefPtr<Clutter::Alpha> alpha =
    //    Clutter::Alpha::create (timeline, Clutter::ALPHA_SINE);
    Glib::RefPtr<Clutter::Alpha> alpha =
        Clutter::Alpha::create(timeline, &Clutter::Alpha::sine_func);

    Glib::RefPtr<Clutter::BehaviourScale> scaler_1 =
        Clutter::BehaviourScale::create (alpha,
                0.5, 0.5,
                1.0, 1.0);

    // Show everying ( and map window )
    stage->show ();

    // and start it
    timeline->start ();

    clutter_main ();

    return 0;
}

