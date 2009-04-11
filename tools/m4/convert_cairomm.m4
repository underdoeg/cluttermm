_CONVERSION(`const Glib::RefPtr<Cairo::Path>&',`const cairo_path_t*',`($3)->cobj()')
_CONVERSION(`Glib::RefPtr<Cairo::Context>&',`cairo_t*',`($3)->cobj()')
_CONVERSION(`Glib::RefPtr< ::Cairo::Context >&',`cairo_t*',`($3)->cobj()')
_CONVERSION(`cairo_t*',`Glib::RefPtr< ::Cairo::Context >',`$2(new ::Cairo::Context ($3, true))')

