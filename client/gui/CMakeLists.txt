find_package(Qt4 COMPONENTS QTCORE QTGUI QTDECLARATIVE REQUIRED)

include(${QT_USE_FILE})

include_directories(
	${QT_INCLUDE_DIR}
	#TODO rethink the entry point thing.
	.. #this is only here so that GuiEntryPoint can see core/InventoryCore
)

file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)

set(MOC_HDRS
	InventoryGUI.h
	FileNetworkReply.h
)

set(QML_DIR
	qml
)

file(GLOB QML_FILES ${QML_DIR}/*.qml)

qt4_wrap_cpp(MOC_SRCS ${MOC_HDRS})

add_definitions(${QT_DEFINITIONS})
add_library(libgui
	${SRCS}
	${HDRS}
	${MOC_SRCS}
	${QML_FILES} #This is so they're visible in a generated project
)
target_link_libraries(libgui
		${QT_LIBRARIES}
)
add_custom_target(copyqml ALL
	COMMENT "Copying qmls"
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${QML_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${QML_DIR}
)
add_dependencies(libgui copyqml)
