/* Copyright (C) 1998-2006 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <glibmm_generate_extra_defs/generate_extra_defs.h>
#include <clutter/clutter.h>
#include <iostream>


int main (int argc, char *argv[])
{
  clutter_init(&argc, &argv) ;

  std::cout 
    << get_defs(CLUTTER_TYPE_ACTOR)
    << get_defs(CLUTTER_TYPE_ALPHA)
    << get_defs(CLUTTER_TYPE_BACKEND)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR_BSPLINE)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR_DEPTH)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR_ELLIPSE)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR_OPACITY)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR_PATH)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR_ROTATE)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR_SCALE)
//    << get_defs(CLUTTER_TYPE_BOX)
    << get_defs(CLUTTER_TYPE_CLONE_TEXTURE)
    << get_defs(CLUTTER_TYPE_COLOR)
//    << get_defs(CLUTTER_TYPE_CONTAINER)
    << get_defs(CLUTTER_TYPE_EFFECT_TEMPLATE)
    << get_defs(CLUTTER_TYPE_ENTRY)
    << get_defs(CLUTTER_TYPE_EVENT)
    << get_defs(CLUTTER_TYPE_GROUP)
//    << get_defs(CLUTTER_TYPE_HBOX)
    << get_defs(CLUTTER_TYPE_LABEL)
//    << get_defs(CLUTTER_TYPE_LAYOUT)
    << get_defs(CLUTTER_TYPE_MEDIA)
    << get_defs(CLUTTER_TYPE_RECTANGLE)
    << get_defs(CLUTTER_TYPE_SCORE)
    << get_defs(CLUTTER_TYPE_SCRIPT)
    << get_defs(CLUTTER_TYPE_STAGE)
    << get_defs(CLUTTER_TYPE_TEXTURE)
    << get_defs(CLUTTER_TYPE_TIMELINE)
    << get_defs(CLUTTER_TYPE_SCORE)
    << get_defs(CLUTTER_TYPE_SHADER)
    << get_defs(CLUTTER_TYPE_SCRIPT)
    ;
//    << get_defs(CLUTTER_TYPE_VBOX)
//    << get_defs(CLUTTER_TYPE_MARGIN);

  return 0;
}
