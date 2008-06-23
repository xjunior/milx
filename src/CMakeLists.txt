set (lib_sources application.cpp cgi_request.cpp controller.cpp
cgi_handler.cpp response.cpp)

# Library
add_library (milx SHARED ${lib_sources})
add_library (milx-static STATIC ${lib_sources})
set_target_properties (milx-static PROPERTIES OUTPUT_NAME "milx")

add_executable (milx.cgi milx-cgi.cpp)
target_link_libraries (milx.cgi milx)

#src/application.cpp  src/callback.h       src/cgi_handler.h
#src/cgi_request.cpp  src/controller.cpp  src/request.h     src/response.h
#src/application.h    src/cgi_handler.cpp  src/cgi_main.cpp   src/cgi_request.h
#src/controller.h    src/response.cpp
