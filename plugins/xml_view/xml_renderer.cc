#include "xml_renderer.h"
#include "xml_serialization.h"

#include <milx/path.h>

bool XMLRenderer::accept(const std::string& mime) {
  return false; // mime.compare("application/xml") == 0;
}

void XMLRenderer::render(milx::Path &path, milx::view::BoundValue &bnd,
                          std::ostream &out) {

  xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
  xml_serialize(doc, NULL, bnd);
  xmlChar *buff;
  int buffsize;
  xmlDocDumpFormatMemory(doc, &buff, &buffsize, 1);

  out << (char *)buff;
}

