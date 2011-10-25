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
 
# Executable
SET (BIN_SOURCES main.cc command.cc create_command.cc server_command.cc)
ADD_EXECUTABLE (${PROJECT_NAME}-cli ${BIN_SOURCES})
ADD_DEPENDENCIES (${PROJECT_NAME}-cli ${PROJECT_NAME}-lib)
TARGET_LINK_LIBRARIES (${PROJECT_NAME}-cli ${PROJECT_NAME}-lib)
INCLUDE_DIRECTORIES (SYSTEM "${PROJECT_PUBLIC_INCLUDE_DIR}")

# General
SET_TARGET_PROPERTIES (${PROJECT_NAME}-cli
	PROPERTIES
		CLEAN_DIRECT_OUTPUT	1
	        OUTPUT_NAME		${PROJECT_NAME}
		VERSION			${PROJECT_VERSION}
)

# Install
INSTALL (TARGETS ${PROJECT_NAME}-cli DESTINATION bin)
