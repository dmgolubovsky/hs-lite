#include "globals.h"
#include "browser_wnd.h"
#include <gdk/gdkkeysyms.h>

browser_window::browser_window(litehtml::context* html_context) : m_html(html_context, this)
{
	set_title("litehtml");

	add(m_vbox);
	m_vbox.show();

	m_vbox.pack_start(m_scrolled_wnd, Gtk::PACK_EXPAND_WIDGET);
	m_scrolled_wnd.set_size_request(800, 600);
	m_scrolled_wnd.show();

	m_scrolled_wnd.add(m_html);
	m_html.show();
}

browser_window::~browser_window()
{

}

int browser_window::on_command_line(const Glib::RefPtr<Gio::ApplicationCommandLine>& command_line,
                    Glib::RefPtr<Gtk::Application>& app)
{
	int argc = 0;
	char** argv = command_line->get_arguments(argc);
	if(argc > 1) {
		m_html.open_page(argv[1]);
	}
	app->activate();
	return EXIT_SUCCESS;
}


void browser_window::open_url(const litehtml::tstring &url)
{
	m_html.open_page(url);
}

