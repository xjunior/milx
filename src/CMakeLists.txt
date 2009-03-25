set (MILX_LIB milx)
set (MILX_BIN milx)
set (MILX_HOME ${EXEC_INSTALL_PREFIX}/milx)
set (MILX_HOME_BIN ${MILX_HOME}/bin)
 
add_subdirectory (cgi)

set (BIN_SOURCES milx.cpp)
set (LIB_SOURCES application.cpp controller.cpp request.cpp cookie.cpp
response.cpp routing.cpp)
set (LIB_HEADERS application.h controller.h request.h cookie.h response.h
routing.h)
set (MILX_LIB_DEPENDENCIES dl)
 
# Library
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
TARGET_LINK_LIBRARIES (${MILX_BIN}-exec boost_filesystem)
INSTALL ( TARGETS ${MILX_BIN}-exec DESTINATION ${BIN_INSTALL_DIR} )
