/* Copyright (c) 2007-2009  The cluttermm Development Team
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

#ifndef CLUTTERMM_H_INCLUDED
#define CLUTTERMM_H_INCLUDED

/** @mainpage cluttermm Reference Manual
 *
 * @section description Description
 *
 * cluttermm is a C++ wrapper for <a href="http://www.clutter-project.org/">Clutter</a>.
 * See Clutter::Stage and Clutter::Actor, for instance, and see the
 * <a href="http://www.openismus.com/documents/cluttermm_tutorial/1.0/docs/tutorial/html/">Programming with cluttermm</a> tutorial.
 *
 * @section basics Basic Usage
 *
 * Include the cluttermm header:
 * @code
 * #include <cluttermm.h>
 * @endcode
 * (You may include individual headers, such as @c cluttermm/actor.h instead.)
 *
 * If your source file is @c program.cc, you can compile it with:
 * @code
 * g++ program.cc -o program `pkg-config --cflags --libs cluttermm-1.0`
 * @endcode
 *
 * Alternatively, if using autoconf, use the following in @c configure.ac:
 * @code
 * PKG_CHECK_MODULES([CLUTTERMM], [cluttermm-1.0])
 * @endcode
 * Then use the generated @c CLUTTERMM_CFLAGS and @c CLUTTERMM_LIBS variables
 * in the project @c Makefile.am files. For example:
 * @code
 * program_CPPFLAGS = $(CLUTTERMM_CFLAGS)
 * program_LDADD = $(CLUTTERMM_LIBS)
 * @endcode
 */

#include <glibmm.h>
#include <cluttermmconfig.h>
#include <cluttermm/action.h>
#include <cluttermm/actor.h>
#include <cluttermm/actor-box.h>
#include <cluttermm/actor-meta.h>
#include <cluttermm/align-constraint.h>
#include <cluttermm/alpha.h>
#include <cluttermm/animatable.h>
#include <cluttermm/animation.h>
#include <cluttermm/animator.h>
#include <cluttermm/behaviour.h>
#include <cluttermm/behaviour-depth.h>
#include <cluttermm/behaviour-ellipse.h>
#include <cluttermm/behaviour-opacity.h>
#include <cluttermm/behaviour-path.h>
#include <cluttermm/behaviour-rotate.h>
#include <cluttermm/behaviour-scale.h>
#include <cluttermm/bin-layout.h>
#include <cluttermm/bind-constraint.h>
#include <cluttermm/box.h>
#include <cluttermm/box-layout.h>
#include <cluttermm/blur-effect.h>
#include <cluttermm/brightness-contrast-effect.h>
#include <cluttermm/cairo-texture.h>
#include <cluttermm/canvas.h>
#include <cluttermm/childmeta.h>
#include <cluttermm/clone.h>
#include <cluttermm/color.h>
#include <cluttermm/colorize-effect.h>
#include <cluttermm/constraint.h>
#include <cluttermm/content.h>
#include <cluttermm/deform-effect.h>
#include <cluttermm/device-manager.h>
#include <cluttermm/desaturate-effect.h>
#include <cluttermm/effect.h>
#include <cluttermm/event.h>
#include <cluttermm/fixed-layout.h>
#include <cluttermm/flow-layout.h>
#include <cluttermm/frame-source.h>
#include <cluttermm/grid-layout.h>
#include <cluttermm/group.h>
#include <cluttermm/image.h>
#include <cluttermm/init.h>
#include <cluttermm/input-device.h>
#include <cluttermm/interval.h>
#include <cluttermm/keyframe-transition.h>
#include <cluttermm/layout-manager.h>
#include <cluttermm/layoutmeta.h>
#include <cluttermm/main.h>
#include <cluttermm/media.h>
#include <cluttermm/model.h>
#include <cluttermm/model-iter.h>
#include <cluttermm/offscreen-effect.h>
#include <cluttermm/page-turn-effect.h>
#include <cluttermm/path.h>
#include <cluttermm/path-constraint.h>
#include <cluttermm/property-transition.h>
#include <cluttermm/rectangle.h>
#include <cluttermm/score.h>
#include <cluttermm/script.h>
#include <cluttermm/scroll-actor.h>
#include <cluttermm/shader.h>
#include <cluttermm/shader-effect.h>
#include <cluttermm/size.h>
#include <cluttermm/snap-constraint.h>
#include <cluttermm/stage.h>
#include <cluttermm/text.h>
#include <cluttermm/text-buffer.h>
#include <cluttermm/texture.h>
#include <cluttermm/threads.h>
#include <cluttermm/timeline.h>
#include <cluttermm/transition.h>
#include <cluttermm/transition-group.h>
#include <cluttermm/types.h>

#endif /* !CLUTTERMM_H_INCLUDED */
