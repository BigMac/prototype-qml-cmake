file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

add_library(libcore
	${SRCS}
	${HDRS}
)
add_subdirectory(network)
target_link_libraries(libcore
	libnetwork
)
