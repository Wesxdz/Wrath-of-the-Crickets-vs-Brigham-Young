#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SFGUI::SFGUI" for configuration "Debug"
set_property(TARGET SFGUI::SFGUI APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SFGUI::SFGUI PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libSFGUI-d.so"
  IMPORTED_SONAME_DEBUG "libSFGUI-d.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS SFGUI::SFGUI )
list(APPEND _IMPORT_CHECK_FILES_FOR_SFGUI::SFGUI "${_IMPORT_PREFIX}/lib/libSFGUI-d.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
