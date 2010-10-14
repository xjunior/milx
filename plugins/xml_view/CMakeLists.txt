#
# This file is part of Milx.
#
# Milx is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Milx is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Milx.  If not, see <http://www.gnu.org/licenses/lgpl-3.0.txt>.
#

MESSAGE ("Building XML view plugin")

FIND_PACKAGE (LibXml2 REQUIRED)
FIND_PACKAGE (LibXslt REQUIRED)

INCLUDE_DIRECTORIES (SYSTEM "${PROJECT_PUBLIC_INCLUDE_DIR}"
  "${LIBXML2_INCLUDE_DIR}"
  "${LIBXSLT_INCLUDE_DIR}")

ADD_LIBRARY (milx-xmlview SHARED xslt_renderer.cc xml_renderer.cc xml_serialization.cc loader.cc)
TARGET_LINK_LIBRARIES (milx-xmlview "${LIBXML2_LIBRARIES}" "${LIBXSLT_LIBRARIES}")

INSTALL (TARGETS "milx-xmlview" DESTINATION "${PROJECT_HOME}/plugins")
