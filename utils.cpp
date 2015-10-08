#include "globals.h"

std::string urljoin(const std::string &base, const std::string &relative)
{
    Poco::URI uri_base(base);
    Poco::URI uri_res(uri_base, relative);
    return  uri_res.toString();
}

