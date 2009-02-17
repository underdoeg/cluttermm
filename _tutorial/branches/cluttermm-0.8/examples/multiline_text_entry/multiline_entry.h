/* Copyright 2008 Openismus GmbH,
 * based on ClutterEntry in Clutter, Copyright OpenedHand
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef CLUTTER_TUTORIAL_MULTILINE_ENTRY_H
#define CLUTTER_TUTORIAL_MULTILINE_ENTRY_H

#include <cluttermm.h>
#include <pangomm.h>

namespace Tutorial
{

class MultilineEntry : public Clutter::Actor
{
public:
  virtual ~MultilineEntry();
  static Glib::RefPtr<MultilineEntry> create();

  sigc::signal<void>& signal_text_changed() { return signal_text_changed_; }
  sigc::signal<void, Clutter::Geometry&>& signal_cursor_event() { return signal_cursor_event_; }
  sigc::signal<void>& signal_activate() { return signal_activate_; }

  void set_text(const Glib::ustring& text);
  Glib::ustring get_text() const;

  void set_font_name(const Glib::ustring& font_name);
  Glib::ustring get_font_name() const;

  void set_color(const Clutter::Color& color);
  Clutter::Color get_color() const;

  bool handle_key_event(Clutter::KeyEvent* event);

protected:
  MultilineEntry();

  virtual void on_paint();
  virtual void allocate_vfunc(const Clutter::ActorBox& box, bool absolute_origin_changed);

  virtual void paint_cursor_vfunc();
  virtual void on_text_changed();
  virtual void on_cursor_event(Clutter::Geometry& geometry);
  virtual void on_activate();

private:
  sigc::signal<void> signal_text_changed_;
  sigc::signal<void, Clutter::Geometry&> signal_cursor_event_;
  sigc::signal<void> signal_activate_;

  Glib::RefPtr<Pango::Context> context_;
  Pango::FontDescription font_;

  Clutter::Color fgcol_;
  Glib::ustring text_;

  int width_;
  Glib::ustring::size_type position_;
  int text_x_;

  Pango::AttrList effective_attrs_;
  Glib::RefPtr<Pango::Layout> layout_;

  Clutter::Geometry cursor_pos_;
  Glib::RefPtr<Clutter::Rectangle> cursor_;

  void ensure_layout(int width);
  void ensure_cursor_position();
  void set_cursor_position(Glib::ustring::size_type position);
  void insert_unichar(gunichar wc);
  void delete_chars(Glib::ustring::size_type num);
  void delete_text(Glib::ustring::size_type start_pos, Glib::ustring::size_type end_pos);
};

} // namespace Tutorial

#endif /* !CLUTTER_TUTORIAL_MULTILINE_ENTRY_H */
