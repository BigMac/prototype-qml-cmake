find_package(Boost COMPONENTS system REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(SERVER_SRCS
		SimpleServer.cpp
		main.cpp
)

add_executable(server ${SERVER_SRCS})
