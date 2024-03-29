#
# Configuration file for SFGUI
#
# Define Alias library SFGUI::SFGUI

include( CMakeFindDependencyMacro )
find_dependency( SFML 2.5 COMPONENTS graphics window system)
find_dependency( OpenGL )

if( "${CMAKE_SYSTEM_NAME}" MATCHES "Linux" )
	find_dependency( X11 )
endif()

include( "${CMAKE_CURRENT_LIST_DIR}/SFGUITargets.cmake" )
