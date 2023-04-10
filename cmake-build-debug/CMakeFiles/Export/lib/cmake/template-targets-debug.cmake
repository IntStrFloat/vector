#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "template::template" for configuration "Debug"
set_property(TARGET template::template APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(template::template PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libtemplated.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS template::template )
list(APPEND _IMPORT_CHECK_FILES_FOR_template::template "${_IMPORT_PREFIX}/lib/libtemplated.a" )

# Import target "template::demo" for configuration "Debug"
set_property(TARGET template::demo APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(template::demo PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/demo.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS template::demo )
list(APPEND _IMPORT_CHECK_FILES_FOR_template::demo "${_IMPORT_PREFIX}/bin/demo.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
