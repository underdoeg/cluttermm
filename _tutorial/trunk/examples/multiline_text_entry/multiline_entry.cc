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

#include "multiline_entry.h"
#include <cogl/cogl.h>
#include <cogl/cogl-pango.h>

namespace
{

static const char *const default_font_name = "Sans 10";

enum { ENTRY_CURSOR_WIDTH = 1 };

static Glib::RefPtr<Pango::Context> ref_shared_context()
{
  static void* context = 0;

  if(context == 0)
  {
    double resolution = clutter_backend_get_resolution(clutter_get_default_backend());

    if(resolution < 0.0)
      resolution = 96.0; // fallback

    PangoFontMap *const fontmap = cogl_pango_font_map_new();
    cogl_pango_font_map_set_resolution(COGL_PANGO_FONT_MAP(fontmap), resolution);

    context = cogl_pango_font_map_create_context(COGL_PANGO_FONT_MAP(fontmap));

    // Clear the pointer when the object is destroyed:
    g_object_add_weak_pointer(static_cast<GObject*>(context), &context);

    // Transfer ownership:
    return Glib::wrap(static_cast<PangoContext*>(context), false);
  }

  // Increase reference count:
  return Glib::wrap(static_cast<PangoContext*>(context), true);
}

} // anonymous namespace

namespace Tutorial
{

/*
 * Example of a multi-line text entry actor, based on ClutterEntry.
 */

MultilineEntry::MultilineEntry()
:
  context_         (ref_shared_context()),
  font_            (default_font_name),
  fgcol_           (0x00, 0x00, 0x00, 0xFF),
  text_            (),
  width_           (0),
  position_        (Glib::ustring::npos),
  text_x_          (0),
  effective_attrs_ (),
  layout_          (),
  cursor_pos_      (),
  cursor_          (Clutter::Rectangle::create(fgcol_))
{
  signal_text_changed_.connect(sigc::mem_fun(*this, &MultilineEntry::on_text_changed));
  signal_cursor_event_.connect(sigc::mem_fun(*this, &MultilineEntry::on_cursor_event));
  signal_activate_    .connect(sigc::mem_fun(*this, &MultilineEntry::on_activate));

  cursor_->set_parent(Glib::RefPtr<Clutter::Actor>((reference(), this)));

  // We use the font size to set the default width and height, in case
  // the user doesn't call Clutter::Actor::set_size().
  const double font_size = font_.get_size() * context_->get_resolution() / (72.0 * Pango::SCALE);

  set_size(20 * int(font_size), 50);
}

MultilineEntry::~MultilineEntry()
{}

Glib::RefPtr<MultilineEntry> MultilineEntry::create()
{
  return Glib::RefPtr<MultilineEntry>(new MultilineEntry());
}

void MultilineEntry::set_text(const Glib::ustring& text)
{
  text_ = text;
  layout_.clear();
  cursor_pos_.set_width(0);

  if(is_visible())
    queue_redraw();

  signal_text_changed_.emit();
}

Glib::ustring MultilineEntry::get_text() const
{
  return text_;
}

/*
 * Sets font_name as the font used by entry.  font_name must be a string
 * containing the font name and its size, similarly to what you would feed
 * to the Pango::FontDescription constructor.
 */
void MultilineEntry::set_font_name(const Glib::ustring& font_name)
{
  Pango::FontDescription font ((font_name.empty()) ? Glib::ustring(default_font_name) : font_name);

  if(font == font_)
    return;

  swap(font_, font);

  if(!text_.empty())
  {
    layout_.clear();

    if(is_visible())
      queue_redraw();
  }
}

Glib::ustring MultilineEntry::get_font_name() const
{
  return font_.to_string();
}

void MultilineEntry::set_color(const Clutter::Color& color)
{
  fgcol_ = color;
  set_opacity(fgcol_.get_alpha());

  cursor_->set_color(fgcol_);

  if(is_visible())
    queue_redraw();
}

Clutter::Color MultilineEntry::get_color() const
{
  return fgcol_;
}

void MultilineEntry::on_text_changed()
{}

void MultilineEntry::on_cursor_event(Clutter::Geometry&)
{}

void MultilineEntry::on_activate()
{}

/*
 * Characters are removed from before the current position of the cursor.
 */
void MultilineEntry::delete_chars(Glib::ustring::size_type num)
{
  using Glib::ustring;

  const ustring::size_type len   = text_.length();
  const ustring::size_type end   = (position_ == ustring::npos) ? len : std::min(position_, len);
  const ustring::size_type start = (num < end) ? end - num : 0;

  set_text(ustring(text_).erase(start, end - start));

  if(position_ != ustring::npos)
    set_cursor_position(start);
}

void MultilineEntry::ensure_layout(int width)
{
  if(!layout_)
  {
    Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(context_);

    layout->set_attributes(effective_attrs_);
    layout->set_single_paragraph_mode(false);
    layout->set_font_description(font_);
    layout->set_wrap(Pango::WRAP_WORD);
    layout->set_width((width > 0) ? width * Pango::SCALE : -1);
    layout->set_text(text_);

    swap(layout_, layout);
  }
}

void MultilineEntry::ensure_cursor_position()
{
  Glib::ustring::iterator pos = text_.begin();

  if(position_ == Glib::ustring::npos)
    pos = text_.end();
  else
    std::advance(pos, position_);

  const Pango::Rectangle rect = layout_->get_cursor_strong_pos(pos.base() - text_.begin().base());

  cursor_pos_.set_xy(rect.get_x() / Pango::SCALE, rect.get_y() / Pango::SCALE);
  cursor_pos_.set_size(ENTRY_CURSOR_WIDTH, rect.get_height() / Pango::SCALE);

  signal_cursor_event_.emit(sigc::ref(cursor_pos_));
}

/*
 * Sets the position of the cursor. The position must be less than or
 * equal to the number of characters in the entry. A value of npos indicates
 * that the position should be set after the last character in the entry.
 * Note that this position is in characters, not in bytes.
 */
void MultilineEntry::set_cursor_position(Glib::ustring::size_type position)
{
  if(position < text_.length())
    position_ = position;
  else
    position_ = Glib::ustring::npos;

  cursor_pos_.set_width(0);

  if(is_visible())
    queue_redraw();
}

/*
 * Insert a character to the right of the current position of the cursor,
 * and update the position of the cursor.
 */
void MultilineEntry::insert_unichar(gunichar wc)
{
  g_return_if_fail(Glib::Unicode::validate(wc));

  if(wc == 0)
    return;

  using Glib::ustring;

  if(position_ == ustring::npos)
    set_text(text_ + wc);
  else
    set_text(ustring(text_).insert(position_, 1, wc));

  if(position_ != ustring::npos)
    set_cursor_position(position_ + 1);
}

/*
 * Deletes a sequence of characters. The characters that are deleted are
 * those characters at positions from start_pos up to, but not including,
 * end_pos. If end_pos is npos, then the characters deleted will be
 * those characters from start_pos to the end of the text.
 */
void MultilineEntry::delete_text(Glib::ustring::size_type start_pos,
                                 Glib::ustring::size_type end_pos)
{
  using Glib::ustring;

  set_text(ustring(text_).erase(start_pos, (end_pos == ustring::npos) ? ustring::npos
                                                                      : end_pos - start_pos));
}

void MultilineEntry::paint_cursor_vfunc()
{
  cursor_->set_geometry(cursor_pos_);
  cursor_->paint();
}

void MultilineEntry::on_paint()
{
  const int width = (width_ < 0) ? get_width() : width_;
  set_clip(0, 0, width, get_height());

  int actor_width = width;

  ensure_layout(actor_width);
  ensure_cursor_position();

  const Pango::Rectangle logical = layout_->get_logical_extents();
  int text_width = logical.get_width() / Pango::SCALE;

  if(actor_width < text_width)
  {
    // We need to do some scrolling:
    const int cursor_x = cursor_pos_.get_x();

    // If the cursor is at the begining or the end of the text, the placement
    // is easy, however, if the cursor is in the middle somewhere, we need to
    // make sure the text doesn't move until the cursor is either in the
    // far left or far right.
    if(position_ == 0)
    {
      text_x_ = 0;
    }
    else if(position_ == Glib::ustring::npos)
    {
      text_x_ = actor_width - text_width;
      cursor_pos_.set_x(cursor_x + text_x_);
    }
    else
    {
      if(text_x_ <= 0)
      {
        const int diff = -text_x_;

        if(cursor_x < diff)
          text_x_ += diff - cursor_x;
        else if(cursor_x > diff + actor_width)
          text_x_ -= cursor_x - (diff + actor_width);
      }
      cursor_pos_.set_x(cursor_x + text_x_);
    }
  }
  else
  {
    text_x_ = 0;
  }

  CoglColor color;

  cogl_color_set_from_4ub(&color, fgcol_.get_red(),
                                  fgcol_.get_green(),
                                  fgcol_.get_blue(),
                                  get_opacity());
  cogl_pango_render_layout(layout_->gobj(), text_x_, 0, &color, 0);

  paint_cursor_vfunc();
}

void MultilineEntry::allocate_vfunc(const Clutter::ActorBox& box, bool absolute_origin_changed)
{
  const int width = CLUTTER_UNITS_TO_DEVICE(box.get_x2() - box.get_x1());

  if(width_ != width)
  {
    layout_.clear();
    ensure_layout(width);

    width_ = width;
  }

  Clutter::Actor::allocate_vfunc(box, absolute_origin_changed);
}

/*
 * This method will handle a Clutter::KeyEvent, like those returned in a
 * key-press/release-event, and will translate it for the entry. This includes
 * non-alphanumeric keys, such as the arrows keys, which will move the
 * input cursor. You should use this function inside a handler for the
 * Clutter::Stage::signal_key_press_event() or
 * Clutter::Stage::signal_key_release_event().
 */
bool MultilineEntry::handle_key_event(Clutter::KeyEvent* event)
{
  switch(Clutter::key_event_symbol(event))
  {
    case CLUTTER_Escape:
    case CLUTTER_Shift_L:
    case CLUTTER_Shift_R:
      // Ignore these - Don't try to insert them as characters:
      return false;

    case CLUTTER_BackSpace:
      // Delete the current character:
      if(position_ != 0 && !text_.empty())
        delete_chars(1);
      break;

    case CLUTTER_Delete:
    case CLUTTER_KP_Delete:
      // Delete the current character:
      if(!text_.empty() && position_ != Glib::ustring::npos)
        delete_text(position_, position_ + 1);
      break;

    case CLUTTER_Left:
    case CLUTTER_KP_Left:
      // Move the cursor one character left:
      if(position_ != 0 && !text_.empty())
        set_cursor_position(((position_ == Glib::ustring::npos) ? text_.length() : position_) - 1);
      break;

    case CLUTTER_Right:
    case CLUTTER_KP_Right:
      // Move the cursor one character right:
      if(position_ != Glib::ustring::npos && !text_.empty() && position_ < text_.length())
        set_cursor_position(position_ + 1);
      break;

    case CLUTTER_Up:
    case CLUTTER_KP_Up:
      // TODO: Calculate the index of the position on the line above,
      // and set the cursor to it.
      break;

    case CLUTTER_Down:
    case CLUTTER_KP_Down:
      // TODO: Calculate the index of the position on the line below, 
      // and set the cursor to it.
      break;

    case CLUTTER_End:
    case CLUTTER_KP_End:
      // Move the cursor to the end of the text:
      set_cursor_position(Glib::ustring::npos);
      break;

    case CLUTTER_Begin:
    case CLUTTER_Home:
    case CLUTTER_KP_Home:
      // Move the cursor to the start of the text:
      set_cursor_position(0);
      break;
  
    default:
      insert_unichar(Clutter::key_event_unicode(event));
      break;
  }
  return true;
}

} // namespace Tutorial
