find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})
add_definitions(-DBOOST_ALL_NO_LIB=1)
set(SERVER_SRCS
		Connection.cpp
		SimpleServer.cpp
		main.cpp
)

add_executable(server ${SERVER_SRCS})
link_directories ( ${Boost_LIBRARY_DIRS} )
target_link_libraries(server
	${Boost_SYSTEM_LIBRARY}
	${CMAKE_THREAD_LIBS_INIT}
)
