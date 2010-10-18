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

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (milx CXX)

INCLUDE (MilxDefinitions.cmake)

SET (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}")
FIND_PACKAGE (LibMicroHTTPD REQUIRED)

ADD_DEFINITIONS ("-DMILX_VERSION=\"${PROJECT_VERSION}\"" "-DMILX_HOME=\"${PROJECT_HOME}\""
  "${MHD_DEFINITIONS}")

# Install skeleton and mime.types
INSTALL (DIRECTORY skeleton DESTINATION "${PROJECT_HOME}")
INSTALL (FILES "mime.types" DESTINATION "${PROJECT_HOME}")

INCLUDE (CPackDefinitions.cmake)

ADD_SUBDIRECTORY (src build-main)
ADD_SUBDIRECTORY (plugins build-plugins)
