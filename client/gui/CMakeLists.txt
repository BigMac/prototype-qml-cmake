find_package(Qt4 COMPONENTS QTCORE QTGUI QTDECLARATIVE REQUIRED)

include(${QT_USE_FILE})

include_directories(
	${QT_INCLUDE_DIR}
)

file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

set(MOC_HDRS
	NetworkReply.h
)

qt4_wrap_cpp(MOC_SRCS ${MOC_HDRS})

add_definitions(${QT_DEFINITIONS})
add_library(libgui
	${SRCS}
	${HDRS}
	${MOC_SRCS}
)
target_link_libraries(libgui
	libevents
	${QT_LIBRARIES}
)
