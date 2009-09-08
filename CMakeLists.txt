cmake_minimum_required(VERSION 2.6)
project (MILX)

set(APPLICATION_NAME ${PROJECT_NAME})
set(APPLICATION_VERSION "0.5")

include(DefineInstallationPaths.cmake)

add_subdirectory (src)
