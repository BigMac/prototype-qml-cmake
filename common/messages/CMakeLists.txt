file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

include_directories(../)
add_library(libmessages
	SHARED
	${SRCS}
	${HDRS}
)
