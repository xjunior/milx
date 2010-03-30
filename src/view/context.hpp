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

