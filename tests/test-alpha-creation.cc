#include <cluttermm.h>
#include <clutter/clutter.h>
#include <iostream>

int
main (int argc, char *argv[])
{
  // initialize the C++ wrapper types
  Clutter::init(&argc, &argv);

  Glib::RefPtr<Clutter::Timeline> timeline =
        Clutter::Timeline::create (360, 60); // num frames, fps
  Glib::RefPtr<Clutter::Alpha> alpha =
    Clutter::Alpha::create (timeline, Clutter::ALPHA_SINE);

  Glib::RefPtr<Clutter::BehaviourScale> scaler_1 =
    Clutter::BehaviourScale::create (alpha, 0.5, 1.0, Clutter::GRAVITY_CENTER);

  //The refcount should probably be 2 here (it is):
  std::cout << "alpha ref_count=" << G_OBJECT(alpha->gobj())->ref_count << std::endl;
  
  return 0;
}

