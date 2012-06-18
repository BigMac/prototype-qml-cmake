find_package(Boost COMPONENTS serialization REQUIRED)
file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

include_directories(../)
add_library(libmessages
	SHARED
	${SRCS}
	${HDRS}
)

target_link_libraries(libmessages
	${Boost_LIBRARIES}
)