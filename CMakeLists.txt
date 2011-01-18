cmake_minimum_required(VERSION 2.6)

# Project name.
project(PONG)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

# Set version number
set (MY_VERSION_MAJOR 0)
set (MY_VERSION_MINOR 0)

# Set default build type.
if (CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "[Debug|Release|RelWithDebInfo|MinSizeRel]" FORCE)
endif()

# Set default install prefix.
if (CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
  set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")
endif()

# Set flags.
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  /usr/include/SDL
)

set(HEADER_FILES
)

set(SOURCE_FILES
  src/engine.cc
  src/introscreen.cc
  src/main.cc
  src/playscreen.cc
  src/playstate.cc
  src/timer.cc
)

add_executable(pong
  ${SOURCE_FILES}
)

target_link_libraries(pong
  ${SDL_LIBRARY}
  ${SDLIMAGE_LIBRARY}
)
