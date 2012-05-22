find_package(Qt4 COMPONENTS QTCORE QTGUI QTDECLARATIVE REQUIRED)

include(${QT_USE_FILE})

include_directories(
		${QT_INCLUDE_DIR}
)

set(SRCS
		main.cpp
		qmlapplicationviewer.cpp
)

set(MOC_HDRS
		qmlapplicationviewer.h
)

file(GLOB QML_FILES *.qml)

qt4_wrap_cpp(MOC_SRCS ${MOC_HDRS})

add_definitions(${QT_DEFINITIONS})
add_executable(main
	${SRCS}
	${MOC_SRCS}
	${QML_FILES} #This is so they're visible in a generated project
)
target_link_libraries(main
		${QT_LIBRARIES}
)

file(COPY main.qml DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )

