project(qt-cmake)
#set(CMAKE_VERBOSE_MAKEFILE ON)
cmake_minimum_required(VERSION 2.6.0)

if(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions("-Wall")
	add_definitions("-Werror")
	add_definitions("-std=c++0x")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_subdirectory(client)
add_subdirectory(server)
