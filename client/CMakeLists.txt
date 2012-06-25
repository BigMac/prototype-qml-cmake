find_package(Boost COMPONENTS system thread REQUIRED)
find_package(Threads)
file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

include_directories(
	../common
	${Boost_INCLUDE_DIRS})
add_definitions(-DBOOST_ALL_NO_LIB=1)

add_subdirectory(gui)
add_subdirectory(events)

add_executable(client
	${SRCS}
	${HDRS}
)

target_link_libraries(client
	libevents
	libgui
	libcommon
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
)

