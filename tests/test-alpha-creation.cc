#include <cluttermm.h>

int
main (int argc, char *argv[])
{
  // initialize the C++ wrapper types
  Clutter::init(&argc, &argv);

  Glib::RefPtr<Clutter::Timeline> timeline =
        Clutter::Timeline::create (360, 60); // num frames, fps
  Glib::RefPtr<Clutter::Alpha> alpha =
    Clutter::Alpha::create (timeline, Clutter::ALPHA_SINE);
  
  return 0;
}

