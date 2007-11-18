#include <cluttermm.h>
#include <cluttermm/init.h>
// FIXME: remove this when enough stuff is wrapped
#include <clutter/clutter.h>

#if defined (_MSC_VER) && !defined (_USE_MATH_DEFINES)
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <errno.h>
#include <stdlib.h>
#include <glib.h>

#define TRAILS  0
#define NACTORS  6
#define RADIUS  ((CLUTTER_STAGE_WIDTH()+CLUTTER_STAGE_HEIGHT())/NACTORS)

typedef struct SuperOH
{
    std::vector<Glib::RefPtr<Clutter::Actor> > hands;
    Glib::RefPtr<Clutter::Actor> bgtex;
    Glib::RefPtr<Clutter::Group> group;
} SuperOH; 

static gint s_num_actors = NACTORS;

// FIXME: use glibmm types
static GOptionEntry super_oh_entries[] = {
    {
        "num-actors", 'n',
        0,
        G_OPTION_ARG_INT, &s_num_actors,
        "Number of actors", "ACTORS"
    },
    { NULL }
};

    static gint
get_radius (void)
{
    return (CLUTTER_STAGE_HEIGHT() + CLUTTER_STAGE_HEIGHT()) / s_num_actors ;
}

// FIXME: wrap these pre-defined alpha funcs as sigc::slots
static guint32 my_sine (const Glib::RefPtr<Clutter::Alpha>& alpha)
{
    return CLUTTER_ALPHA_SINE (alpha->gobj (), NULL);
}

bool on_button_press (Clutter::ButtonEvent *event, const Glib::RefPtr<Clutter::Stage>& stage)
{
    gint x, y;

    clutter_event_get_coords ((ClutterEvent*)event, &x, &y);

    g_print ("*** button press event (button:%d) ***\n",
            event->button);

    Glib::RefPtr<Clutter::Actor> e = stage->get_actor_at_pos (x, y);

    if (e)
        e->hide ();

    return false;
}

bool on_key_release (Clutter::KeyEvent *event)
{
    g_print ("*** key press event (key:%c) ***\n",
            clutter_key_event_symbol (event));

    if (clutter_key_event_symbol (event) == CLUTTER_q)
        clutter_main_quit ();

    return false;
}

/* Timeline handler */
    void
on_new_frame (int frame_num, SuperOH* oh)
{
    /* Rotate everything clockwise about stage center*/
    oh->group->rotate_z (frame_num,
            CLUTTER_STAGE_WIDTH() / 2,
            CLUTTER_STAGE_HEIGHT() / 2);

    for (int i = 0; i < s_num_actors; i++)
    {
        double scale_x, scale_y;

        oh->hands[i]->get_scale (scale_x, scale_y);

        /* Rotate each hand around their centers - to get this we need
         * to take into account any scaling.
         *
         * FIXME: scaling causes drift so disabled for now. Need rotation
         * unit based functions to fix.
         */
        oh->hands[i]->rotate_z (- 6.0 * frame_num,
#if 0
                (oh->hands[i]->get_width () / 2) * scale_x,
                (oh->hands[i]->get_height () / 2) * scale_y
#else
                (oh->hands[i]->get_width () / 2),
                (oh->hands[i]->get_height () / 2)
#endif
                );
    }
}

    int
main (int argc, char *argv[])
{
    // FIXME: wrap init function with args
    /*
       GError *error;

       error = NULL;

       clutter_init_with_args (&argc, &argv,
       NULL,
       super_oh_entries,
       NULL,
       &error);
       if (error)
       {
       g_warning ("Unable to initialise Clutter:\n%s",
       error->message);
       g_error_free (error);

       exit (1);
       }
       */

    // initialize the C++ wrapper types
    Clutter::init(&argc, &argv);

    Clutter::Color stage_color (0x61, 0x64, 0x8c, 0xff);
    Glib::RefPtr<Clutter::Stage> stage = Clutter::Stage::get_default ();
    stage->set_size (800, 600);

    Glib::RefPtr<Gdk::Pixbuf> pixbuf =
        Gdk::Pixbuf::create_from_file ("actor.png");

    if (!pixbuf)
        g_error("pixbuf load failed");

    stage->set_title ("Actors Test");
    stage->set_color (stage_color);

    SuperOH *oh = new SuperOH ();

    /* Create a timeline to manage animation */
    Glib::RefPtr<Clutter::Timeline> timeline = Clutter::Timeline::create (360, 60); /* num frames, fps */
    timeline->set_loop (true); /* have it loop */

    /* fire a callback for frame change */
    timeline->signal_new_frame ().connect (sigc::bind(sigc::ptr_fun(on_new_frame), oh));

    /* Set up some behaviours to handle scaling  */
    Glib::RefPtr<Clutter::Alpha> alpha = Clutter::Alpha::create (timeline,
            sigc::ptr_fun(my_sine));

    Glib::RefPtr<Clutter::BehaviourScale> scaler_1 =
        Clutter::BehaviourScale::create (alpha,
                0.5,
                1.0,
                Clutter::GRAVITY_CENTER);

    Glib::RefPtr<Clutter::BehaviourScale> scaler_2 =
        Clutter::BehaviourScale::create (alpha,
                1.0,
                0.5,
                Clutter::GRAVITY_CENTER);

    /* create a new group to hold multiple actors in a group */
    oh->group = Clutter::Group::create ();

    oh->hands.reserve (s_num_actors);
    for (int i = 0; i < s_num_actors; i++)
    {
        gint x, y, w, h;
        gint radius = get_radius ();

        /* Create a texture from pixbuf, then clone in to same resources */
        if (i == 0)
            oh->hands.push_back (Clutter::Texture::create (pixbuf));
        else
            oh->hands.push_back (Clutter::CloneTexture::create
                    (Glib::RefPtr<Clutter::Texture>::cast_dynamic
                     (oh->hands[0])));

        /* Place around a circle */
        w = oh->hands[0]->get_width ();
        h = oh->hands[0]->get_height ();

        x = CLUTTER_STAGE_WIDTH () / 2 
            + radius
            * cos (i * M_PI / (s_num_actors / 2))
            - w / 2;
        y = CLUTTER_STAGE_HEIGHT () / 2 
            + radius
            * sin (i * M_PI / (s_num_actors / 2))
            - h / 2;

        oh->hands[i]->set_position (x, y);

        /* Add to our group group */
        oh->group->add_actor (oh->hands[i]);

#if 0 /* FIXME: disabled as causes drift - see comment above */
        if (i % 2)
            scaler_1->apply (oh->hands[i]);
        else
            scaler_2->apply (oh->hands[i]);
#endif
    }

    oh->group->show_all ();

    /* Add the group to the stage */
    stage->add_actor (oh->group);

    /* Show everying ( and map window ) */
    stage->show_all ();

    stage->signal_button_press_event ().connect (sigc::bind (sigc::ptr_fun
                (on_button_press), stage));

    stage->signal_key_release_event ().connect (sigc::ptr_fun(on_key_release));

    /* and start it */
    timeline->start ();

    clutter_main ();

    delete oh;

    return 0;
}
