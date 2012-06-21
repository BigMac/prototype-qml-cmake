file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

add_library(libevents
	${SRCS}
	${HDRS}
)

