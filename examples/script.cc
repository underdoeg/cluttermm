#include <cluttermm.h>

// This is the JSON node. Notice that all types are C-types.
// One can not currenty use C++-types.
static const Glib::ustring jsonNode("[                   \
  {                                                      \
    \"id\" : \"stage\",                                  \
    \"type\" : \"ClutterStage\",                         \
    \"width\" : 200,                                     \
    \"height\" : 200,                                    \
    \"color\" : \"#20456f\",                             \
    \"children\" : [ \"text-box\", \"rect1\", \"rect2\"] \
  },                                                     \
  {                                                      \
    \"id\" : \"rect1\",                                  \
    \"type\" : \"ClutterRectangle\",                     \
    \"width\" :  100,                                    \
    \"height\" : 100,                                    \
    \"x\" : 10,                                          \
    \"y\" : 10,                                          \
    \"color\" : \"#523202\",                             \
    \"opacity\" : 127                                    \
  },                                                     \
  {                                                      \
    \"id\" : \"rect2\",                                  \
    \"type\" : \"ClutterRectangle\",                     \
    \"width\" :  100,                                    \
    \"height\" : 100,                                    \
    \"x\" : 50,                                          \
    \"y\" : 50,                                          \
    \"color\" : \"#cc99ee\"                              \
  },                                                     \
  {                                                      \
    \"id\" : \"text-box\",                               \
    \"type\" : \"ClutterText\",                          \
    \"width\" : 100,                                     \
    \"height\" : 60,                                     \
    \"x\" : 20,                                          \
    \"y\" : 20,                                          \
    \"text\" : \"This is text!\",                        \
    \"color\" : \"#ddeeee\"                              \
  }                                                      \
]");

int main(int argc, char** argv)
{
  Clutter::init(&argc, &argv);

  Glib::RefPtr<Clutter::Script> script = Clutter::Script::create();

  // Load the JSON node from a string.
  script->load_from_data(jsonNode);

  // Get the stage by name, casting it to the correct C++-type.
  const Glib::RefPtr<Clutter::Stage> stage =
    Glib::RefPtr<Clutter::Stage>::cast_static(script->get_object("stage"));

  // Show the stage:
  stage->show();

  // Start the main loop, so we can respond to events:
  Clutter::main();

  return 0;
}
