#include <cluttermm.h>
#include <iostream>

// This is the JSON node. Notice that all types are C-types.
// One can not currenty use C++-types.
static const Glib::ustring jsonNode("[                   \
  {                                                      \
    \"id\" : \"stage\",                                  \
    \"type\" : \"ClutterStage\",                         \
    \"width\" : 300,                                     \
    \"height\" : 300,                                    \
    \"color\" : \"#20456f\",                             \
    \"children\" : [ \"mybox\"]                          \
  },                                                     \
  {                                                      \
    \"id\" : \"mybox\",                                  \
    \"type\" : \"ClutterBox\",                           \
    \"width\" : 300,                                     \
    \"height\" : 300,                                    \
    \"layout-manager\": {                                \
               \"type\"  : \"ClutterFlowLayout\"         \
    },                                                   \
    \"children\" : [ \"text-box\", \"rect1\", \"rect2\"] \
  },                                                     \
  {                                                      \
    \"id\" : \"rect1\",                                  \
    \"type\" : \"ClutterRectangle\",                     \
    \"width\" : 100,                                     \
    \"height\" : 100,                                    \
    \"color\" : \"#523202\",                             \
    \"opacity\" : 127                                    \
  },                                                     \
  {                                                      \
    \"id\" : \"rect2\",                                  \
    \"type\" : \"ClutterRectangle\",                     \
    \"width\" : 100,                                     \
    \"height\" : 100,                                    \
    \"color\" : \"#cc99ee\"                              \
  },                                                     \
  {                                                      \
    \"id\" : \"text-box\",                               \
    \"type\" : \"ClutterText\",                          \
    \"width\" : 100,                                     \
    \"height\" : 60,                                     \
    \"text\" : \"This is text!\",                        \
    \"color\" : \"#ddeeee\"                              \
} \
]");

int main(int argc, char** argv)
{
  try
  {
    Clutter::init(&argc, &argv);

    Glib::RefPtr<Clutter::Script> script = Clutter::Script::create();

    // Load the JSON node from a string.
    script->load_from_data(jsonNode);

    // Get the stage by name, casting it to the correct C++-type.
    Glib::RefPtr<Clutter::Stage> stage;
    script->get_object("stage", stage);

    Glib::RefPtr<Clutter::Box> box;
    script->get_object("mybox", box);

    std::cout << "Box->width: "  << box->get_width() << std::endl;

    // Show the stage:
    stage->show();

    // Start the main loop, so we can respond to events:
    Clutter::main();
  }
  catch (const Glib::Error& error)
  {
      std::cerr << "Exception: " << error.what() << std::endl;
      return 1;
  }

  return 0;
}
