file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

add_library(libcore
	${SRCS}
	${HDRS}
)
