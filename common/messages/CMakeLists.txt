file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

include_directories(../)
add_library(libmessages
	${SRCS}
	${HDRS}
)
