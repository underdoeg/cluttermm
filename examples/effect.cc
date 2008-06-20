#include <cluttermm.h>
#include <cluttermm/init.h>
// FIXME: remove this when enough stuff is wrapped
#include <clutter/clutter.h>
#include <iostream>

#if defined (_MSC_VER) && !defined (_USE_MATH_DEFINES)
#define _USE_MATH_DEFINES
#endif

void move_finished(const Glib::RefPtr<Clutter::Actor>& actor, const Glib::RefPtr<Clutter::EffectTemplate>& effect)
{
  // Restart
  effect->move(actor, 450, 450, sigc::bind(sigc::ptr_fun(move_finished), effect));
}

int
main (int argc, char *argv[])
{
    // initialize the C++ wrapper types
    Clutter::init(&argc, &argv);

    Clutter::Color stage_color (0x61, 0x64, 0x8c, 0xff);
    Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default ();
    stage->set_size (800, 600);

    stage->set_title ("Effect Test");
    stage->set_color (stage_color);

    Glib::RefPtr<Clutter::Timeline> timeline =
        Clutter::Timeline::create (360, 60); // num frames, fps
    //timeline->set_loop (true); // have it loop
    Glib::RefPtr<Clutter::EffectTemplate> effect = Clutter::EffectTemplate::create(timeline, Clutter::ALPHA_RAMP);

    Glib::RefPtr<Clutter::Texture> texture(Clutter::Texture::create());
    texture->set_from_file("actor.png");

    stage->add_actor(texture);
    stage->show_all();

    timeline->start();
    effect->move(texture, 450, 450, sigc::bind(sigc::ptr_fun(move_finished), effect));

    clutter_main ();
    return 0;
}
