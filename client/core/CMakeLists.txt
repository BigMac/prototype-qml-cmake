file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

add_library(libcore
	${SRCS}
	${HDRS}
)

target_link_libraries(libcore
	libcommon)
