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
	#InventoryGUI.h
	#RepositoryNetworkReply.h
)

qt4_wrap_cpp(MOC_SRCS ${MOC_HDRS})

add_definitions(${QT_DEFINITIONS})
add_library(libgui
	${SRCS}
	${HDRS}
	${MOC_SRCS}
)
target_link_libraries(libgui
		${QT_LIBRARIES}
)
