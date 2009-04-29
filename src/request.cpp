/*
 * This file is part of Milx.
 *
 * Milx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Milx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Milx.  If not, see <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */
#include <sstream>
#include <boost/regex.hpp>
#include "request.hpp"

const boost::regex method_path_http("^(GET|POST|PUT|DELETE) (/.*) HTTP/([01][.][019]).*$"); // support 0.9, 1.0 and 1.1
const boost::regex header_value("^([[:alpha:]-]+): (.+?)$");

Milx::Request::Request(std::string method, std::string full_path, std::string version)
{
	this->_method = method;
	this->_full_path = full_path;
	this->_version = version;
	this->_action = "";
	this->_controller = "";
	
    int start = 1, tmp;
    do
    {
        tmp = full_path.find("/", start);
        this->path.push_back(full_path.substr(start, tmp - start));
        start = tmp + 1;
    } while (tmp < full_path.size());
}

Milx::Request* Milx::Request::parse(const std::string strreq)
{
    Milx::Request* req;
    std::string::const_iterator begin = strreq.begin(), end = strreq.end();
    boost::match_results<std::string::const_iterator> what;

    if (regex_search(begin, end, what, method_path_http))
    {
        req = new Milx::Request(std::string(what[1].first, what[1].second),
    							std::string(what[2].first, what[2].second),
    							std::string(what[3].first, what[3].second));
        begin = what[3].second;
    }
    // TODO else throw an error;

    while (regex_search(begin, end, what, header_value))
    {
        req->headers[std::string(what[1].first, what[1].second)] = std::string(what[2].first, what[2].second);
        begin = what[2].second;
    }

    return req;
}

/*Milx::Request::Request()
{
    std::string header = this->cookieHeader();

    if (!header.empty())
    {
        std::ostringstream namess, valuess;
        std::string name;
        char cur;
        for (register int i = 0; i < header.size(); i++)
        {
            cur = header.at(i);
            switch (cur)
            {
                case ';':
                    _cookies.addCookie(new Cookie(name, valuess.str()));
                    valuess.str("");
                    name = "";
                    break;
                case '=':
                    name = namess.str();
                    namess.str("");
                    break;
                default:
                    if (name.size() > 0)
                        valuess << cur;
                    else
                        namess << cur;
                    break;
            }
        }
    }
}
*/

