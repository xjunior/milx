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

#ifndef MILX_VIEW_CONTEXT_HPP
#define MILX_VIEW_CONTEXT_HPP

#include <sstream>
#include <iostream>
#include <string>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <libxml/parser.h>
#include <libxml/tree.h>

/*class xmlDoc;
class xmlNode;*/

namespace Milx
{
	namespace View
	{
	class Context
	{
		xmlDoc *_doc;
		xmlNode *_root;

	public:
		Context()
		{
			_doc = xmlNewDoc(BAD_CAST "1.0");
			_root = xmlNewNode(NULL, BAD_CAST "c"); // creates /c
			xmlDocSetRootElement(_doc, _root);
		}
		template <class T>
		void bind(const T &obj, const char *id)
		{
			std::stringstream ss;
			{
			boost::archive::xml_oarchive arch(ss);
			arch << boost::serialization::make_nvp(id, obj);
			}
			std::string xml = ss.str();
			std::cout << xml << std::endl;
			xmlDocPtr doc;
			doc = xmlReadMemory(xml.c_str(), (int)xml.size(), "xml", NULL, 0);
		}
	};
	}
}

#endif

