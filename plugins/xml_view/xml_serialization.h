#ifndef XMLSERIALIZATION_H
#define XMLSERIALIZATION_H

#include <libxml/tree.h>

#include <milx/views.h>

void xml_serialize(xmlDocPtr doc, xmlNodePtr parent, milx::view::BoundValue& n);

#endif
