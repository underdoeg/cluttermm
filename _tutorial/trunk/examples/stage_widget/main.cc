/*
 * Copyright (c) 2008 Openismus GmbH
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

#include <gtkmm.h>
#include <clutter-gtkmm.h>
#include <iostream>

namespace
{

class StageWindow : public Gtk::Window
{
public:
  StageWindow();
  virtual ~StageWindow();

private:
  Clutter::Gtk::Embed*          embed_;
  Glib::RefPtr<Clutter::Stage>  stage_;
  bool                          colored_;

  void on_button_clicked();
  static bool on_stage_button_press(Clutter::ButtonEvent* event);
};

StageWindow::StageWindow()
:
  embed_   (0),
  colored_ (false)
{
  Gtk::Box *const box = new Gtk::VBox(false, 6);
  add(*Gtk::manage(box));

  Gtk::Button *const button = new Gtk::Button("Change color");
  box->pack_end(*Gtk::manage(button), Gtk::PACK_SHRINK);

  embed_ = new Clutter::Gtk::Embed();
  box->pack_start(*Gtk::manage(embed_), Gtk::PACK_EXPAND_WIDGET);
  embed_->set_size_request(200, 200);

  button->signal_clicked().connect(sigc::mem_fun(*this, &StageWindow::on_button_clicked));

  stage_ = embed_->get_stage();
  stage_->reference();
  stage_->set_color(Clutter::Color(0, 0, 0)); // black
  stage_->signal_button_press_event().connect(&StageWindow::on_stage_button_press);

  show_all();
  stage_->show();
}

StageWindow::~StageWindow()
{}

void StageWindow::on_button_clicked()
{
  colored_ = !colored_;
  stage_->set_color((colored_) ? Clutter::Color(32, 32, 160)
                               : Clutter::Color(0, 0, 0));
}

bool StageWindow::on_stage_button_press(Clutter::ButtonEvent* event)
{
  int x = 0;
  int y = 0;
  // TODO: Wrap properly
  clutter_event_get_coords(reinterpret_cast<Clutter::Event*>(event), &x, &y);

  std::cout << "Stage clicked at (" << x << ", " << y << ")\n";

  return true; // stop further handling of this event
}

} // anonymous namespace


int main(int argc, char** argv)
{
  try
  {
    Clutter::Gtk::init(&argc, &argv);
    Gtk::Main kit (&argc, &argv);

    StageWindow window;
    Gtk::Main::run(window);
  }
  catch (const Glib::Error& error)
  {
    std::cerr << "Exception: " << error.what() << std::endl;
    return 1;
  }

  return 0;
}
