file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

add_library(libresourcerepository
	${SRCS}
	${HDRS}
)
