#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libpqxx::pqxx_shared" for configuration "Release"
set_property(TARGET libpqxx::pqxx_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libpqxx::pqxx_shared PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/pqxx.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/pqxx.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS libpqxx::pqxx_shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_libpqxx::pqxx_shared "${_IMPORT_PREFIX}/lib/pqxx.lib" "${_IMPORT_PREFIX}/bin/pqxx.dll" )

# Import target "libpqxx::pqxx_static" for configuration "Release"
set_property(TARGET libpqxx::pqxx_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libpqxx::pqxx_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/pqxx.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS libpqxx::pqxx_static )
list(APPEND _IMPORT_CHECK_FILES_FOR_libpqxx::pqxx_static "${_IMPORT_PREFIX}/lib/pqxx.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
