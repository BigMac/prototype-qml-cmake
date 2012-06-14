find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS}
)

file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

link_directories ( ${Boost_LIBRARY_DIRS} )
add_library(libcommon
	${SRCS}
	${HDRS}
)

link_directories ( ${Boost_LIBRARY_DIRS} )
add_definitions(-DBOOST_ALL_NO_LIB=1)
target_link_libraries(libcommon
	${Boost_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)
