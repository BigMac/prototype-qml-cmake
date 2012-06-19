find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(../common)

set(RESOURCES_DIR
	resources
)

file(GLOB_RECURSE QML_FILES ${RESOURCES_DIR}/*.qml)
file(GLOB_RECURSE QMLDIR_FILES ${RESOURCES_DIR}/*qmldir)
file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

add_custom_target(copyresources ALL
	COMMENT "Copying Resources"
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES_DIR}
		${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES_DIR}
)

add_executable(server
	${SRCS}
	${HDRS}
	${QML_FILES} #This is so they're visible in a generated project
	${QMLDIR_FILES}
)

add_dependencies(server copyresources)

link_directories ( ${Boost_LIBRARY_DIRS} )
add_definitions(-DBOOST_ALL_NO_LIB=1)
target_link_libraries(server
	libcommon
	${Boost_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)
