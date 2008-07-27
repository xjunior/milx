add_subdirectory (cgi)

set (LIB_SOURCES application.cpp controller.cpp response.cpp cookie.cpp)
set (LIB_HEADERS application.h callback.h controller.h request.h response.h cookie.h)
set (MILX_LIB milx)
# TODO: define a default bin dir for Milx (for cgi and fcgi, for example)

# Library
add_library (${MILX_LIB} SHARED ${LIB_SOURCES})
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

# Install
INSTALL ( TARGETS ${MILX_LIB} ${MILX_LIB}-static DESTINATION ${LIB_INSTALL_DIR} )
INSTALL ( FILES ${LIB_HEADERS} DESTINATION ${INCLUDE_INSTALL_DIR}/milx )

#src/application.cpp  src/callback.h       src/cgi_handler.h
#src/cgi_request.cpp  src/controller.cpp  src/request.h     src/response.h
#src/application.h    src/cgi_handler.cpp  src/cgi_main.cpp   src/cgi_request.h
#src/controller.h    src/response.cpp
