cmake_minimum_required(VERSION 3.0.2)

# Build Properties
set(CMAKE_INSTALL_INCLUDEDIR "include" CACHE PATH "Default relative include path.")
set(CMAKE_INSTALL_LIBDIR "lib" CACHE PATH "Default relative lib path.")

# Targets
# NOTE: Only static libs supported as STL are part of the interface.
project(clipper-lib)
add_library(${PROJECT_NAME} STATIC clipper.cpp clipper.hpp)
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

# Deployment
install (FILES clipper.hpp DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/clipper")
install (TARGETS ${PROJECT_NAME}
         ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
         LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
