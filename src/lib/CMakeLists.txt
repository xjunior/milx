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
 
# Library
SET (LIB_SOURCES application.cc routing.cc logger.cc http/call.cc server/daemon.cc
plugin_manager.cc path.cc views.cc milx.cc callback.cc)

INCLUDE_DIRECTORIES (SYSTEM "${PROJECT_PUBLIC_INCLUDE_DIR}"
  "${MHD_INCLUDE_DIRS}")
SET (LIB_DEPENDENCIES dl magic "${MHD_LIBRARIES}")

ADD_LIBRARY (${PROJECT_NAME}-lib SHARED ${LIB_SOURCES})
ADD_LIBRARY (${PROJECT_NAME}-static STATIC ${LIB_SOURCES})
TARGET_LINK_LIBRARIES (${PROJECT_NAME}-lib ${LIB_DEPENDENCIES})
TARGET_LINK_LIBRARIES (${PROJECT_NAME}-static ${LIB_DEPENDENCIES})
SET_PROPERTY (TARGET ${PROJECT_NAME}-lib ${PROJECT_NAME}-static PROPERTY FRAMEWORK ON)

# General
SET_TARGET_PROPERTIES (${PROJECT_NAME}-lib ${PROJECT_NAME}-static
	PROPERTIES
		CLEAN_DIRECT_OUTPUT	1
	        OUTPUT_NAME		${PROJECT_NAME}
		VERSION			${PROJECT_VERSION}
)

# Install
INSTALL (TARGETS ${PROJECT_NAME}-lib DESTINATION lib)
INSTALL (TARGETS ${PROJECT_NAME}-static DESTINATION lib)
INSTALL (DIRECTORY "${PROJECT_PUBLIC_INCLUDE_DIR}/${PROJECT_NAME}" DESTINATION include/)
