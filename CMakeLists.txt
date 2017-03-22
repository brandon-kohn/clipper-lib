CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

# Build Properties
SET(CMAKE_INSTALL_INCDIR "include/clipper" CACHE PATH "Default relative include path.")
SET(CMAKE_INSTALL_LIBDIR "lib${LIB_SUFFIX}" CACHE PATH "Default relative lib path.")

# Targets
# NOTE: Only static libs supported as STL are part of the interface.
PROJECT(clipper)
ADD_LIBRARY(clipper STATIC clipper.cpp)

# Deployment
INSTALL (FILES clipper.hpp DESTINATION "${CMAKE_INSTALL_INCDIR}")
INSTALL (TARGETS clipper
         ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
         LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
