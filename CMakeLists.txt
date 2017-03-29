cmake_minimum_required(VERSION 3.0.2)

# Build Properties
set(CMAKE_INSTALL_INCLUDEDIR "include" CACHE PATH "Default relative include path.")
set(CMAKE_INSTALL_LIBDIR "lib" CACHE PATH "Default relative lib path.")

# Version 
# Find '#define CLIPPER_VERSION "x.x.z"' and extract version
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/clipper/clipper.hpp VERSION_FILE)
string(REGEX MATCH "#define[\\t\\ ]+CLIPPER_VERSION[\\t\\ ]+\"([0-9]+\\.[0-9]+\\.[0-9]+)\"" VERSION_STRING "${VERSION_FILE}")
string(REGEX REPLACE "([0-9]+)\\.([0-9]+)\\.([0-9]+)" "\\1;\\2;\\3" VERSION_RESULT "${CMAKE_MATCH_1}")
list(GET VERSION_RESULT 0 VERSION_MAJOR)
list(GET VERSION_RESULT 1 VERSION_MINOR)
list(GET VERSION_RESULT 2 VERSION_PATCH)
set (CLIPPER_VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
message(STATUS "Clipper version ${CLIPPER_VERSION_STRING}.")

# Targets
# NOTE: Only static libs supported as STL are part of the interface.
project(clipper-lib)
add_library(${PROJECT_NAME} STATIC clipper/clipper.cpp clipper/clipper.hpp)
set_target_properties (${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
set_target_properties (${PROJECT_NAME} PROPERTIES VERSION ${CLIPPER_VERSION_STRING})
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/clipper-lib>
  $<INSTALL_INTERFACE:include>
)

# Deployment
install (FILES clipper/clipper.hpp DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/clipper")
install (TARGETS ${PROJECT_NAME}
         ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
         LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
