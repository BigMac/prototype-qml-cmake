set(SRCS
	main.cpp
)

add_subdirectory(gui)
add_subdirectory(core)
add_executable(client
	${SRCS}
)
target_link_libraries(client
	libcore
	libgui
)

