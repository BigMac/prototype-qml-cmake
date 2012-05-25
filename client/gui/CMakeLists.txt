find_package(Qt4 COMPONENTS QTCORE QTGUI QTDECLARATIVE REQUIRED)

include(${QT_USE_FILE})

include_directories(
	${QT_INCLUDE_DIR}
	#TODO rethink the entry point thing.
	.. #this is only here so that GuiEntryPoint can see core/InventoryCore
)

set(SRCS
	InventoryGUI.cpp
	GuiEntryPoint.cpp
)

set(MOC_HDRS
	InventoryGUI.h
)

file(GLOB QML_FILES *.qml)

qt4_wrap_cpp(MOC_SRCS ${MOC_HDRS})

add_definitions(${QT_DEFINITIONS})
add_library(libgui
	${SRCS}
	${MOC_SRCS}
	${QML_FILES} #This is so they're visible in a generated project
)
target_link_libraries(libgui
		${QT_LIBRARIES}
)

file(COPY main.qml DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )

