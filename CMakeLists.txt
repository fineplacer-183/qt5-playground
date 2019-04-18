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

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Charts CONFIG REQUIRED)


add_executable(${PROJECT_NAME} main.cpp mainwindow.cpp fpchart.cpp)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Charts)

include(CTest)
enable_testing()
ADD_SUBDIRECTORY( tests )