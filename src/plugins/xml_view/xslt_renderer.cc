#include "xslt_renderer.h"
#include "xml_serialization.h"

#include <cstring>
#include <libxml/tree.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

#include <milx/path.h>
#include <iostream>
#include <string>

bool XSLTRenderer::accept(const std::string& mime) {
  static std::string mime_accepted = "application/xslt+xml";
  return !mime.compare(0, mime_accepted.size(), mime_accepted);
}

void XSLTRenderer::render(const std::string& tpl, milx::view::BoundValue &bnd,
                          std::ostream &out) {
  xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
  char *tpl_content = new char[tpl.size() + 2];
  strncpy(tpl_content, tpl.c_str(), tpl.size() + 2);
  xmlDocPtr xsl_doc = xmlReadMemory(tpl_content, tpl.size(), NULL, NULL, 0);
  xml_serialize(doc, NULL, bnd);

  xmlSubstituteEntitiesDefault(1);
  xmlLoadExtDtdDefaultValue = 1;
  xsltStylesheetPtr xslt = xsltParseStylesheetDoc(xsl_doc);
  xmlDocPtr result = xsltApplyStylesheet(xslt, doc, NULL);

  xmlChar *str_result;
  int result_len;
  xsltSaveResultToString(&str_result, &result_len, result, xslt);

  // Cleanup
  xsltFreeStylesheet(xslt);
  xmlFreeDoc(result);
  xmlFreeDoc(doc);
  //xmlFreeDoc(xsl_doc);
  
  xsltCleanupGlobals();
  xmlCleanupParser();

  // finish
  out << str_result;

  xmlFree(str_result);
}

