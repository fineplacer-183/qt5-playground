cmake_minimum_required(VERSION 3.0.0)
project(fpcomiss VERSION 0.1.0)

find_program(CCACHE_EXECUTABLE ccache)
mark_as_advanced(CCACHE_EXECUTABLE)
if(CCACHE_EXECUTABLE)
  foreach(LANG C CXX)
    if(NOT DEFINED CMAKE_${LANG}_COMPILER_LAUNCHER AND NOT CMAKE_${LANG}_COMPILER MATCHES ".*/ccache$")
      message(STATUS "Enabling ccache for ${LANG}")
      set(CMAKE_${LANG}_COMPILER_LAUNCHER ${CCACHE_EXECUTABLE} CACHE STRING "")
    endif()
  endforeach()
endif()

set(CMAKE_CXX_FLAGS "-Wall -Werror")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/libs)

find_package(Qt5 COMPONENTS Core Widgets Charts REQUIRED)
find_package(ZLIB REQUIRED)

ADD_SUBDIRECTORY( fpchart )
ADD_SUBDIRECTORY( pakfile )

include_directories(fpchart pakfile)

add_executable(${PROJECT_NAME} main.cpp mainwindow.cpp)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Charts ${ZLIB_LIBRARIES} fpchart pakfile)

include(CTest)
enable_testing()
ADD_SUBDIRECTORY( tests )