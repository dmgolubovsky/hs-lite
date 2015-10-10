#pragma once

#include "html_widget.h"

class browser_window : public Gtk::Window
{
public:
	browser_window(litehtml::context* html_context);
	virtual ~browser_window();

	void open_url(const litehtml::tstring& url);
	void set_url(const litehtml::tstring& url);
	int on_command_line(const Glib::RefPtr<Gio::ApplicationCommandLine>& command_line,
		Glib::RefPtr<Gtk::Application>& app);

private:
    void on_go_clicked();
    bool on_address_key_press(GdkEventKey* event);

protected:
	html_widget			m_html;
	Gtk::VBox			m_vbox;
	Gtk::ScrolledWindow	m_scrolled_wnd;
};


