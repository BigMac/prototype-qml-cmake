project(qt-cmake)
#set(CMAKE_VERBOSE_MAKEFILE ON)
cmake_minimum_required(VERSION 2.4.0)

find_package(Qt4 REQUIRED)

add_subdirectory(qml)
add_subdirectory(qmlapplicationviewer)
