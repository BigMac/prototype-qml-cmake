find_package(Boost COMPONENTS serialization REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

add_library(messages
	${SRCS}
	${HDRS}
)
link_directories ( ${Boost_LIBRARY_DIRS} )
add_definitions(-DBOOST_ALL_NO_LIB=1)
target_link_libraries(messages
	${Boost_LIBRARIES}
)
