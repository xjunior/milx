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
//TODO: pass Milx::CookieList#getAllCookies and Milx::Cookie#toString to Milx::Response

#ifndef MILX_COOKIE_H
#define MILX_COOKIE_H

#include <string>
#include <sstream>
#include <vector>

namespace Milx
{
	class Cookie
	{
	private:
		std::string _name;
		std::string _value;
		std::string _version;
		std::string _domain;
		std::string _path;
		std::string _expires;
		bool _secure;
	public:
		Cookie(std::string="", std::string="");
		~Cookie() {}
		std::string name();
		std::string value();
		std::string version();
		std::string domain();
		std::string path();
		std::string expires();
		bool isSecure();
		std::string toString();

		void name(std::string);
		void value(std::string);
		void version(std::string);
		void domain(std::string);
		void path(std::string);
		void expires(std::string);
		void isSecure(bool);
	};
	
	class BadCookie { };

	class CookieList
	{
	private:
		std::vector<Cookie*> cookies;	
	public:
		CookieList() {}

                ~CookieList() { clearAll(); }

		Cookie *find(std::string cookieName) { 
			for(register int i=0; i<cookies.size(); i++) {
				if(cookies[i]->name().compare(cookieName)) return cookies[i];
			}
			return NULL;		
 		}

                Cookie* operator[](std::string cookieName) {
                        return find(cookieName);
                }

		void addCookie(Cookie *cookie) { cookies.push_back(cookie); }

		void clearAll() { cookies.clear(); }

		void clearCookie(std::string cookieName)
                {
			Cookie *c = find(cookieName);
			
			if(c == NULL) {
				throw BadCookie();
			}
			
			delete c;
		}

		std::string getAllCookies()
                {
			std::string result;
			register int i;

			if (cookies.empty())
				return "";

			for (i = 0; i < cookies.size() - 1; i++)
				result += cookies[i]->toString() + "\n";	
			result += cookies[i]->toString();

			return result;
		}
	};
}

#endif /* MILX_COOKIE_H */
