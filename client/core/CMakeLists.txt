find_package(Boost COMPONENTS thread REQUIRED)
find_package(Threads)
file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

add_library(libcore
	${SRCS}
	${HDRS}
)

add_subdirectory(events)

target_link_libraries(libcore
	libcommon
        libevents
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT})
