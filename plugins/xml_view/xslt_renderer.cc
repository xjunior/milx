#include "xslt_renderer.h"
#include "xml_serialization.h"

#include <libxml/tree.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

#include <milx/path.h>
#include <iostream>

bool XSLTRenderer::accept(const std::string& mime) {
  static std::string mime_accepted = "application/xslt+xml";
  return !mime.compare(0, mime_accepted.size(), mime_accepted);
}

void XSLTRenderer::render(milx::Path &path, milx::view::BoundValue &bnd,
                          std::ostream &out) {
  xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
  xml_serialize(doc, NULL, bnd);

  xmlSubstituteEntitiesDefault(1);
  xmlLoadExtDtdDefaultValue = 1;
  xsltStylesheetPtr xslt = xsltParseStylesheetFile((const xmlChar *) path.str().c_str());
  xmlDocPtr result = xsltApplyStylesheet(xslt, doc, NULL);

  xmlChar *str_result;
  int result_len;
  xsltSaveResultToString(&str_result, &result_len, result, xslt);

  // Cleanup
  xsltFreeStylesheet(xslt);
  xmlFreeDoc(result);
  xmlFreeDoc(doc);
  
  xsltCleanupGlobals();
  xmlCleanupParser();

  // finish
  out << str_result;

  delete[] str_result;
}

