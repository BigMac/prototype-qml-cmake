find_package(Boost COMPONENTS thread REQUIRED)
find_package(Threads)
find_package(Qt4 COMPONENTS QTCORE QTGUI QTDECLARATIVE REQUIRED)

include(${QT_USE_FILE})

file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

include_directories(
	.
	../common
	${Boost_INCLUDE_DIRS}
	${QT_INCLUDE_DIR})
add_definitions(-DBOOST_ALL_NO_LIB=1)

add_subdirectory(connection)
add_subdirectory(events)
add_subdirectory(gui)
add_subdirectory(resourcerepository)

add_executable(client
	${SRCS}
	${HDRS}
)

target_link_libraries(client
	libcommon
	libconnection
	libevents
	libgui
	libresourcerepository
	${Boost_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
	${QT_LIBRARIES}
)

