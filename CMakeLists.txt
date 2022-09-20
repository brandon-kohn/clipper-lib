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

if(MSVC AND NOT "${FORCE_MSVC_RUNTIME}" STREQUAL "")
    message(STATUS "Clipper: Forcing msvc runtime to ${FORCE_MSVC_RUNTIME}")
    force_msvc_runtime()
endif()

if(MSVC AND NOT "${FORCE_MSVC_DEBUG_DEFINE}" STREQUAL "")
    message(STATUS "clipper: Forcing msvc debug define to ${FORCE_MSVC_DEBUG_DEFINE}")
    force_msvc_debug_define()
endif()
# Targets
# NOTE: Only static libs supported as STL are part of the interface.
project(clipper)

set(CLIPPER_STATIC_LIBRARY ${PROJECT_NAME}_static)
set(CLIPPER_SHARED_LIBRARY ${PROJECT_NAME})

add_library(${CLIPPER_SHARED_LIBRARY} SHARED clipper/clipper.cpp clipper/clipper.hpp clipper/clipper_export.hpp)
set_target_properties (${CLIPPER_SHARED_LIBRARY} PROPERTIES DEBUG_POSTFIX "d")
set_target_properties (${CLIPPER_SHARED_LIBRARY} PROPERTIES VERSION ${CLIPPER_VERSION_STRING})
target_compile_definitions(${CLIPPER_SHARED_LIBRARY} PRIVATE -DCLIPPER_EXPORTS_API)
target_include_directories(${CLIPPER_SHARED_LIBRARY} INTERFACE $<BUILD_INTERFACE:${clipper_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)

add_library(${CLIPPER_STATIC_LIBRARY} STATIC clipper/clipper.cpp clipper/clipper.hpp clipper/clipper_export.hpp)
set_target_properties (${CLIPPER_STATIC_LIBRARY} PROPERTIES DEBUG_POSTFIX "d")
set_target_properties (${CLIPPER_STATIC_LIBRARY} PROPERTIES VERSION ${CLIPPER_VERSION_STRING})
target_compile_definitions(${CLIPPER_STATIC_LIBRARY} PUBLIC -DCLIPPER_STATIC_LIB)
target_include_directories(${CLIPPER_STATIC_LIBRARY} INTERFACE $<BUILD_INTERFACE:${clipper_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# the RPATH to be used when installing, but only if it's not a system directory
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
ENDIF("${isSystemDir}" STREQUAL "-1")

# Deployment
install (FILES clipper/clipper.hpp clipper/clipper_export.hpp DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/clipper")
install (TARGETS ${CLIPPER_SHARED_LIBRARY} ${CLIPPER_STATIC_LIBRARY}
         RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
         ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
         LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
