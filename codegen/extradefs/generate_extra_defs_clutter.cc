/* Copyright (c) 2007-2009  The gtkmm Development Team
 *
 * This file is part of cluttermm.
 *
 * cluttermm is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 2.1 of the License,
 * or (at your option) any later version.
 *
 * cluttermm is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glibmm_generate_extra_defs/generate_extra_defs.h>
#include <clutter/clutter.h>
#include <iostream>

int main(int argc, char** argv)
{
  clutter_init(&argc, &argv);

  std::cout
    << get_defs(CLUTTER_TYPE_ACTOR)
    << get_defs(CLUTTER_TYPE_ACTOR_META)
    << get_defs(CLUTTER_TYPE_ACTION)
    << get_defs(CLUTTER_TYPE_ALPHA)
    << get_defs(CLUTTER_TYPE_ANIMATION)
    << get_defs(CLUTTER_TYPE_BACKEND)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR_DEPTH)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR_ELLIPSE)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR_OPACITY)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR_PATH)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR_ROTATE)
    << get_defs(CLUTTER_TYPE_BEHAVIOUR_SCALE)
    << get_defs(CLUTTER_TYPE_BIN_LAYOUT)
    << get_defs(CLUTTER_TYPE_BOX)
    << get_defs(CLUTTER_TYPE_BOX_LAYOUT)
    << get_defs(CLUTTER_TYPE_CAIRO_TEXTURE)
    << get_defs(CLUTTER_TYPE_CHILD_META)
    << get_defs(CLUTTER_TYPE_CLONE)
    << get_defs(CLUTTER_TYPE_COLOR)
    << get_defs(CLUTTER_TYPE_CONTAINER)
    << get_defs(CLUTTER_TYPE_EFFECT)
    << get_defs(CLUTTER_TYPE_EVENT)
    << get_defs(CLUTTER_TYPE_FIXED_LAYOUT)
    << get_defs(CLUTTER_TYPE_GROUP)
    << get_defs(CLUTTER_TYPE_INTERVAL)
//    << get_defs(CLUTTER_TYPE_HBOX)
//    << get_defs(CLUTTER_TYPE_LAYOUT)
    << get_defs(CLUTTER_TYPE_LAYOUT_MANAGER)
    << get_defs(CLUTTER_TYPE_LAYOUT_META)
    << get_defs(CLUTTER_TYPE_MEDIA)
    << get_defs(CLUTTER_TYPE_PATH)
    << get_defs(CLUTTER_TYPE_RECTANGLE)
    << get_defs(CLUTTER_TYPE_SCORE)
    << get_defs(CLUTTER_TYPE_SCRIPT)
    << get_defs(CLUTTER_TYPE_STAGE)
    << get_defs(CLUTTER_TYPE_TEXT)
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
