find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})

set(CORE_SRCS
	InventoryCore.cpp
)

link_directories ( ${Boost_LIBRARY_DIRS} )
add_library(libcore
	${CORE_SRCS})
target_link_libraries(libcore
	${Boost_SYSTEM_LIBRARY}
	${CMAKE_THREAD_LIBS_INIT}
)
