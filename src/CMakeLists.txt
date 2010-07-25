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

set (MILX_HOME ${EXEC_INSTALL_PREFIX}/${PROJECT_NAME})
set (MILX_HOME_BIN ${MILX_HOME}/bin)
 
# Library
set (LIB_SOURCES application.cpp controller.cpp cookie.cpp routing.cpp logger.cpp project_loader.cpp
module.cpp shared_module.cpp view/renderer.cpp view/renderer/plain.cpp web_call.cpp server/daemon.cpp
path.cpp)
set (LIB_HEADERS application.hpp controller.hpp cookie.hpp web_call.hpp project_loader.hpp
routing.hpp logger.hpp module.hpp shared_module.hpp view/context.hpp view/renderer.hpp view/renderer/base.hpp
view/renderer/plain.hpp server/daemon.hpp action_callback.hpp path.hpp)
set (LIB_DEPENDENCIES dl magic microhttpd)

# Shared Lib
add_library (${PROJECT_NAME}-lib SHARED ${LIB_SOURCES})
target_link_libraries (${PROJECT_NAME}-lib ${LIB_DEPENDENCIES})
set_target_properties (
  ${PROJECT_NAME}-lib
    PROPERTIES
        CLEAN_DIRECT_OUTPUT
            1
        OUTPUT_NAME
            ${PROJECT_NAME}
        VERSION
            ${MILX_VERSION}
)
INSTALL ( TARGETS ${PROJECT_NAME}-lib  DESTINATION ${LIB_INSTALL_DIR} )
INSTALL ( FILES ${LIB_HEADERS} DESTINATION ${INCLUDE_INSTALL_DIR}/${PROJECT_NAME} )

# Static Lib
add_library (${PROJECT_NAME}-static STATIC ${LIB_SOURCES})
# target_link_libraries (${PROJECT_NAME}-static ${LIB_DEPENDENCIES})
set_target_properties (
  ${PROJECT_NAME}-static
    PROPERTIES
        CLEAN_DIRECT_OUTPUT
            1
        OUTPUT_NAME
            ${PROJECT_NAME}
        VERSION
            ${MILX_VERSION}
)
INSTALL ( TARGETS ${PROJECT_NAME}-static DESTINATION ${LIB_INSTALL_DIR} )

# Executable

#set (BIN_SOURCES milx.cpp manipulators/base.cpp manipulators/project_manipulator.cpp manipulators/module_manipulator.cpp)
set (BIN_SOURCES cli/main.cpp cli/command.cpp cli/create_command.cpp cli/server_command.cpp)

add_executable (${PROJECT_NAME}-cli ${BIN_SOURCES})
add_dependencies(${PROJECT_NAME}-cli ${PROJECT_NAME}-lib)
set_target_properties (
  ${PROJECT_NAME}-cli
    PROPERTIES
        OUTPUT_NAME
            ${PROJECT_NAME}
        CLEAN_DIRECT_OUTPUT
            1
        VERSION
            ${MILX_VERSION}
)
TARGET_LINK_LIBRARIES (${PROJECT_NAME}-cli ${PROJECT_NAME}-lib)
INSTALL ( TARGETS ${PROJECT_NAME}-cli DESTINATION ${BIN_INSTALL_DIR} )
INSTALL ( CODE "FILE (MAKE_DIRECTORY ${MILX_HOME})" )
INSTALL ( CODE "FILE (COPY skeleton DESTINATION ${MILX_HOME})" )
