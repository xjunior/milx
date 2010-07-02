set (MILX_HOME ${EXEC_INSTALL_PREFIX}/${PROJECT_NAME})
set (MILX_HOME_BIN ${MILX_HOME}/bin)
 
# Library
set (LIB_SOURCES application.cpp controller.cpp cookie.cpp routing.cpp logger.cpp project_loader.cpp
module.cpp shared_module.cpp view/renderer.cpp view/renderer/plain.cpp web_call.cpp server/daemon.cpp
cli/command.cpp path.cpp)
set (LIB_HEADERS application.hpp controller.hpp cookie.hpp web_call.hpp project_loader.hpp
routing.hpp logger.hpp module.hpp shared_module.hpp view/context.hpp view/renderer.hpp view/renderer/base.hpp
view/renderer/plain.hpp server/daemon.hpp cli/command.hpp action_callback.hpp path.hpp)
# set (LIB_DEPENDENCIES dl boost_regex-mt xml2 magic microhttpd)
set (LIB_DEPENDENCIES dl xml2 magic microhttpd)

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
#add_library (${MILX_LIB}-static STATIC ${LIB_SOURCES})
#set_target_properties (
#  ${MILX_LIB}-static
#    PROPERTIES
#        CLEAN_DIRECT_OUTPUT
#            1
#        OUTPUT_NAME
#            ${MILX_LIB}
#        VERSION
#            ${MILX_VERSION}
#)
#INSTALL ( TARGETS ${PROJECT_NAME}-static DESTINATION ${LIB_INSTALL_DIR} )

# Executable

#set (BIN_SOURCES milx.cpp manipulators/base.cpp manipulators/project_manipulator.cpp manipulators/module_manipulator.cpp)
set (BIN_SOURCES cli/main.cpp cli/server_command.cpp)

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
