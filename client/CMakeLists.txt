file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

include_directories(../common)
add_subdirectory(gui)
add_subdirectory(core)

add_executable(client
	${SRCS}
	${HDRS}
)
target_link_libraries(client
	libcore
	libgui
	libcommon
)

