#include "xslt_renderer.h"
#include "xml_renderer.h"

#include <milx/plugins.h>
#include <milx/application.h>
#include <milx/views.h>

void milx_plugin_load(milx::Application& app, milx::Plugin& p) {
  p.version = 1;
  p.name = "XML/XSLT View";
  milx::view::renderers.add<XSLTRenderer>();
  milx::view::renderers.add<XMLRenderer>();
}

