#include "xml_serialization.h"

void xml_serialize(xmlDocPtr doc, xmlNodePtr parent, milx::view::BoundValue& n) {
  xmlNodePtr node = xmlNewDocNode(doc, NULL, BAD_CAST n.name().c_str(), BAD_CAST n.value().c_str());
  if (parent)
    xmlAddChild(parent, node);
  else
    xmlDocSetRootElement(doc, node);

  for (std::list<milx::view::BoundValue*>::const_iterator begin = n.children().begin();
      begin != n.children().end();
      begin++) {
    xml_serialize(doc, node, **begin);
  }
}

