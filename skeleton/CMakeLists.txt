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
PROJECT (my-project CXX)
SET (PROJECT_VERSION 1)

ADD_DEFINITIONS ("-DPROJECT_NAME=\"${PROJECT_NAME}\"" "-DPROJECT_VERSION=${PROJECT_VERSION}")

SET (SOURCES boot.cc src/controller.cc)

ADD_LIBRARY (${PROJECT_NAME}-lib SHARED ${SOURCES})
SET_TARGET_PROPERTIES (${PROJECT_NAME}-lib
  PROPERTIES
    CLEAN_DIRECT_OUTPUT ON
    OUTPUT_NAME ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
)

