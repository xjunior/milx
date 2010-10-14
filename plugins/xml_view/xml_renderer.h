#ifndef MILX_VIEW_XML_RENDERER_H
#define MILX_VIEW_XML_RENDERER_H

#include <milx/views.h>
#include <ostream>

class XMLRenderer : public milx::view::Renderer {
 public:
  virtual bool accept(const std::string& mime);
  virtual void render(milx::Path &path, milx::view::BoundValue &bnd,
                                  std::ostream &out);
};

#endif
