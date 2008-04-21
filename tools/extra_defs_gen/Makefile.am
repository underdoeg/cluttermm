# Build the generate_extra_defs utility executable.
# This is not used directly to build the rest of the project.

LIBS = -lglibmm_generate_extra_defs-2.4

noinst_PROGRAMS = generate_extra_defs_clutter generate_extra_defs_clutter_cairo
generate_extra_defs_clutter_SOURCES = generate_defs_clutter.cc
generate_extra_defs_clutter_cairo_SOURCES = generate_defs_clutter_cairo.cc

generate_extra_defs_clutter_CXXFLAGS = $(CLUTTERMM_CFLAGS)
generate_extra_defs_clutter_LDADD = $(CLUTTERMM_LIBS)
generate_extra_defs_clutter_cairo_CXXFLAGS = $(CLUTTERMM_CAIRO_CFLAGS)
generate_extra_defs_clutter_cairo_LDADD = $(CLUTTERMM_CAIRO_LIBS)
