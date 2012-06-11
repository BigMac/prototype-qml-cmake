file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

add_subdirectory(gui)
add_subdirectory(core)
include_directories(../messages)

add_executable(client
	${SRCS}
	${HDRS}
)
target_link_libraries(client
	libcore
	libgui
	libmessages
)

