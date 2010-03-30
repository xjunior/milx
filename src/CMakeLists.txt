set (MILX_HOME ${EXEC_INSTALL_PREFIX}/${APPLICATION_NAME})
set (MILX_HOME_BIN ${MILX_HOME}/bin)
 
# Library
set (MILX_LIB milx)

set (LIB_SOURCES application.cpp controller.cpp cookie.cpp routing.cpp logger.cpp project_loader.cpp
module.cpp shared_module.cpp view/renderer.cpp view/renderer/plain.cpp web_call.cpp server/daemon.cpp)
set (LIB_HEADERS application.hpp controller.hpp cookie.hpp web_call.hpp project_loader.hpp
routing.hpp logger.hpp module.hpp shared_module.hpp view/context.hpp view/renderer.hpp view/renderer/base.hpp
view/renderer/plain.hpp server/daemon.hpp)
set (MILX_LIB_DEPENDENCIES dl boost_regex-mt xml2 magic)

add_library (${MILX_LIB} SHARED ${LIB_SOURCES})
target_link_libraries (${MILX_LIB} ${MILX_LIB_DEPENDENCIES})
add_library (${MILX_LIB}-static STATIC ${LIB_SOURCES})
set_target_properties (
  ${MILX_LIB}-static
    PROPERTIES
        CLEAN_DIRECT_OUTPUT
            1
        OUTPUT_NAME
            ${MILX_LIB}
        VERSION
            ${APPLICATION_VERSION}
)
set_target_properties (
  ${MILX_LIB}
    PROPERTIES
        CLEAN_DIRECT_OUTPUT
            1
        VERSION
            ${APPLICATION_VERSION}
)
INSTALL ( TARGETS ${MILX_LIB} ${MILX_LIB}-static DESTINATION ${LIB_INSTALL_DIR} )
INSTALL ( FILES ${LIB_HEADERS} DESTINATION ${INCLUDE_INSTALL_DIR}/${MILX_LIB} )

# Executable
set (MILX_BIN milx)

set (BIN_SOURCES milx.cpp manipulators/base.cpp manipulators/project_manipulator.cpp manipulators/module_manipulator.cpp)

add_executable (${MILX_BIN}-exec ${BIN_SOURCES})
set_target_properties (
  ${MILX_BIN}-exec
    PROPERTIES
        OUTPUT_NAME
            ${MILX_BIN}
        CLEAN_DIRECT_OUTPUT
            1
        VERSION
            ${APPLICATION_VERSION}
)
TARGET_LINK_LIBRARIES (${MILX_BIN}-exec boost_filesystem-mt)
INSTALL ( TARGETS ${MILX_BIN}-exec DESTINATION ${BIN_INSTALL_DIR} )

# Server Executable
set (MILX_SERVER_BIN milx-server)

set (SERVER_BIN_SOURCES server/milx-server-main.cpp)

add_executable (${MILX_SERVER_BIN} ${SERVER_BIN_SOURCES})
set_target_properties (
  ${MILX_SERVER_BIN}
    PROPERTIES
        OUTPUT_NAME
            ${MILX_SERVER_BIN}
        CLEAN_DIRECT_OUTPUT
            1
        VERSION
            ${APPLICATION_VERSION}
)
TARGET_LINK_LIBRARIES (${MILX_SERVER_BIN} ${MILX_LIB} microhttpd boost_program_options-mt boost_filesystem-mt)
INSTALL ( TARGETS ${MILX_SERVER_BIN} DESTINATION ${BIN_INSTALL_DIR} )
