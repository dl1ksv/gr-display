INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_DISPLAY display)

FIND_PATH(
    DISPLAY_INCLUDE_DIRS
    NAMES display/api.h
    HINTS $ENV{DISPLAY_DIR}/include
        ${PC_DISPLAY_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    DISPLAY_LIBRARIES
    NAMES gnuradio-display
    HINTS $ENV{DISPLAY_DIR}/lib
        ${PC_DISPLAY_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/displayTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DISPLAY DEFAULT_MSG DISPLAY_LIBRARIES DISPLAY_INCLUDE_DIRS)
MARK_AS_ADVANCED(DISPLAY_LIBRARIES DISPLAY_INCLUDE_DIRS)
