#include <cluttermm.h>

int main(int argc, char** argv)
{
  // initialize the C++ wrapper types
  Clutter::init(&argc, &argv);

  Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default();

  // Create a timeline to manage animation
  Glib::RefPtr<Clutter::Timeline> timeline =
      Clutter::Timeline::create(6000); // milliseconds

  // Set up some behaviours to handle scaling
  Glib::RefPtr<Clutter::Alpha> alpha =
      Clutter::Alpha::create(timeline, Clutter::EASE_IN_SINE);

  Glib::RefPtr<Clutter::BehaviourScale> scaler_1 =
      Clutter::BehaviourScale::create(alpha, 0.5, 0.5, 1.0, 1.0);

  // Show everying ( and map window )
  stage->show();

  // and start it
  timeline->start();

  Clutter::main();

  return 0;
}
