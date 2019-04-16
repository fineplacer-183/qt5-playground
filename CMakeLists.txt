cmake_minimum_required(VERSION 3.0.0)
project(fpcomiss VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "-Wall -Werror")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Charts CONFIG REQUIRED)


add_executable(${PROJECT_NAME} main.cpp mainwindow.cpp)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Charts)