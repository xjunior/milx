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
SET (LIB_SOURCES application.cc controller.cc routing.cc logger.cc project_loader.cc
module.cc shared_module.cc http/call.cc server/daemon.cc path.cc view.cc view/renderer.cc
view/xslt_renderer.cc view/plain_renderer.cc serialization.cc milx.cc)
SET (LIB_HEADERS application.h controller.hpp http/call.hpp project_loader.hpp
routing.h logger.hpp module.hpp shared_module.hpp server/daemon.hpp action_callback.hpp path.hpp
view.h view/renderer.hpp view/xslt_renderer.hpp view/plain_renderer.hpp serialization.hpp
milx.h http.hpp)

FIND_PACKAGE (LibXml2 REQUIRED)
ADD_DEFINITIONS ("${LIBXML2_DEFINITIONS}")

INCLUDE_DIRECTORIES (SYSTEM "${LIBXML2_INCLUDE_DIR}")
SET (LIB_DEPENDENCIES dl magic microhttpd xml2 "${LIBXML2_LIBRARIES}")

ADD_LIBRARY (${PROJECT_NAME}-lib SHARED ${LIB_SOURCES})
ADD_LIBRARY (${PROJECT_NAME}-static STATIC ${LIB_SOURCES})
TARGET_LINK_LIBRARIES (${PROJECT_NAME}-lib ${LIB_DEPENDENCIES})
TARGET_LINK_LIBRARIES (${PROJECT_NAME}-static ${LIB_DEPENDENCIES})
SET_PROPERTY (TARGET ${PROJECT_NAME}-lib ${PROJECT_NAME}-static PROPERTY FRAMEWORK ON)

# Executable
SET (BIN_SOURCES cli/main.cc cli/command.cc cli/create_command.cc cli/server_command.cc)
ADD_EXECUTABLE (${PROJECT_NAME}-cli ${BIN_SOURCES})
ADD_DEPENDENCIES (${PROJECT_NAME}-cli ${PROJECT_NAME}-lib)
TARGET_LINK_LIBRARIES (${PROJECT_NAME}-cli ${PROJECT_NAME}-lib)

# General
SET_TARGET_PROPERTIES (${PROJECT_NAME}-lib ${PROJECT_NAME}-static ${PROJECT_NAME}-cli
	PROPERTIES
		CLEAN_DIRECT_OUTPUT	1
	        OUTPUT_NAME		${PROJECT_NAME}
		VERSION			${PROJECT_VERSION}
)

# Install
INSTALL (TARGETS ${PROJECT_NAME}-lib DESTINATION lib)
INSTALL (TARGETS ${PROJECT_NAME}-static DESTINATION lib)
INSTALL (TARGETS ${PROJECT_NAME}-cli DESTINATION bin)
INSTALL (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h" PATTERN "cli" EXCLUDE)
