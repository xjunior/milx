set (CGI_LIB_SOURCES cgi_request.cpp cgi_handler.cpp milx-cgi.cpp)
set (CGI_LIB_HEADERS cgi_handler.h cgi_request.h)
set (CGI_BIN milx.cgi)
set (MILX_LIB milx)

# Executables
add_executable (${CGI_BIN} ${CGI_LIB_SOURCES})
target_link_libraries (${CGI_BIN} ${MILX_LIB})

# TODO: install milx.cgi at the milx default bin dir
