/*
 * Copyright 2010 Carlos Junior
 *
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

#include <libxml/tree.h>
#include <libxml/xmlsave.h>

#include "xslt_renderer.h"
#include "../serialization.h"

#define XML_VERSION "1.0"
#define XML_ENCODING "UTF-8"

void milx::view::XSLTRenderer::render(std::ostream& out) {
  xmlDocPtr doc = xmlNewDoc(BAD_CAST XML_VERSION);

  milx::Serialization::Serializer *xmlser;
  xmlser = new milx::Serialization::XMLSerializer(doc);
  xmlser->serialize(context());

  xmlBufferPtr buff = xmlBufferCreate();
  xmlSaveCtxtPtr save = xmlSaveToBuffer(buff, XML_ENCODING, XML_SAVE_FORMAT);
  xmlSaveDoc(save, doc);
  xmlSaveClose(save);

  out << buff->content;  // just to return something
  // TODO(xjunior) render XSLT
}

