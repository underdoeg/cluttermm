#include <gtkmm.h>
#include <cluttermm-gtk.h>

Glib::RefPtr<Clutter::Label> label;
Gtk::Entry *pentry;

void on_button_clicked()
{
	label->set_text(pentry->get_text());
}

int main(int argc, char** argv)
{
	// init cluttermm-gtk
	Clutter::Gtk::init(&argc, &argv);

	// init gtkmm
	Gtk::Main kit(argc, argv);

	Gtk::Window window;
	Gtk::VBox vbox;
	Gtk::HBox hbox;
	Gtk::Frame frame;
	Gtk::Entry entry;
	Gtk::Button button("Apply");

	button.signal_clicked().connect(sigc::ptr_fun(&on_button_clicked));

	pentry = &entry;

	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file("actor.png");

	Clutter::Gtk::Embed embed;

	Glib::RefPtr<Clutter::Texture> texture = Clutter::Texture::create(pixbuf);
	texture->set_opacity(50);

	label = Clutter::Label::create("Sans 10", "Enter some text in the Entry and click 'Apply' to update this text!");

	window.set_default_size(600, 320);
	window.add(vbox);

	vbox.set_border_width(10);
	vbox.set_spacing(5);
	vbox.pack_start(frame, Gtk::PACK_EXPAND_WIDGET);
	vbox.pack_start(hbox, Gtk::PACK_SHRINK);

	frame.add(embed);

	hbox.set_spacing(5);
	hbox.pack_start(entry, Gtk::PACK_EXPAND_WIDGET);
	hbox.pack_start(button, Gtk::PACK_SHRINK);

	// get the stage from the embed widget
	Glib::RefPtr<Clutter::Stage> stage = embed.get_stage();

	stage->add_actor(texture);
	stage->add_actor(label);

	texture->set_position(10, 10);
	label->set_position(40, 40);

	// Note: using show_all_children() causes corrupt results!
	window.show_all();
	stage->show_all();

	kit.run(window);

	return 0;
}
