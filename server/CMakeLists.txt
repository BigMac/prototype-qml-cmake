find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})

set(SERVER_SRCS
		SimpleServer.cpp
		main.cpp
)

add_executable(server ${SERVER_SRCS})
target_link_libraries(server
	${Boost_SYSTEM_LIBRARY}
	${CMAKE_THREAD_LIBS_INIT}
)
