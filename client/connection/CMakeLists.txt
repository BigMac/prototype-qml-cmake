find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads)
file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

add_library(libconnection
	${SRCS}
	${HDRS}
)

target_link_libraries(libconnection
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
)