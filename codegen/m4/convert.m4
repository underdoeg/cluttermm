dnl Include gmmproc type conversion definitions:
m4_include(`convert_base.m4')
m4_include(`convert_glib.m4')
m4_include(`convert_cairo.m4')

# From pangomm. The path is discovered in configure.ac:
m4_include(`convert_pango.m4')

# From atkmm. The path is discovered in configure.ac:
m4_include(`convert_atk.m4')

m4_include(`convert_cogl.m4')
m4_include(`convert_clutter.m4')
