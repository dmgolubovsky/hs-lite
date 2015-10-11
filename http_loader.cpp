#include "globals.h"
#include "http_loader.h"

http_loader::http_loader()
{
    m_curl = curl_easy_init();
    curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPALIVE, 1L);
    curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPIDLE, 120L);
    curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPINTVL, 60L);
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION,	http_loader::curlWriteFunction);
}

http_loader::~http_loader()
{
    curl_easy_cleanup(m_curl);
}

size_t http_loader::curlWriteFunction( void *ptr, size_t size, size_t nmemb, void *stream )
{
    Glib::RefPtr< Gio::MemoryInputStream >* s = (Glib::RefPtr< Gio::MemoryInputStream >*) stream;
    (*s)->add_data(ptr, size * nmemb);
    return size * nmemb;
}

Glib::RefPtr< Gio::InputStream > http_error(std::string s) {
    Glib::RefPtr< Gio::MemoryInputStream > stream = Gio::MemoryInputStream::create();
    stream->add_data(s);
    return stream;
}

Glib::RefPtr< Gio::InputStream > http_loader::load_file(const litehtml::tstring& url)
{
    m_url = url;

    Poco::URI uri(url);
    std::string sch(uri.getScheme());


    if (sch != "file" && sch != "") {
	return http_error("<h1>Scheme '" + sch + "' not supported</h1>");
    }

    if (sch == "") {
	uri.setScheme("file");
    }

    m_url = uri.toString();

    std::string path(uri.getPath());

    Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(path);
    if (!file->query_exists()) {
	return http_error("<h1>File '" + path + "' cannot be opened</h1>");
    }

    Glib::RefPtr< Gio::InputStream > stream = file->read();

    return stream;
}
