set (MILX_CGI_SOURCES cgi_request.cpp cgi_handler.cpp milx-cgi.cpp)
set (MILX_CGI_HEADERS cgi_handler.hpp cgi_request.hpp)
set (MILX_CGI_BIN milx.cgi)

# Executables
add_executable (${MILX_CGI_BIN} ${MILX_CGI_SOURCES})
target_link_libraries (${MILX_CGI_BIN} ${MILX_LIB} boost_filesystem)

# Install milx.cgi at the milx default bin dir
INSTALL ( FILES ${MILX_CGI_BIN} DESTINATION ${MILX_HOME_BIN} PERMISSIONS
OWNER_READ OWNER_EXECUTE OWNER_WRITE GROUP_READ GROUP_EXECUTE
GROUP_WRITE WORLD_EXECUTE WORLD_READ )
