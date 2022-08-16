# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################
message(STATUS "Extra includes: ${Qt5Widgets_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} ")
set(extra_includes ${Qt5Widgets_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
get_directory_property( DirDefs COMPILE_DEFINITIONS )
message(STATUS "COMPILE_DEFINITIONS = ${DirDefs}" )
set(define_symbols ${DirDefs};__PIC__)
message(STATUS "OLd defines: $CACHE{OLD_DEFINES}" )
message(STATUS "Definitions = ${define_symbols}" )
string(COMPARE NOTEQUAL "$CACHE{OLD_DEFINES}" "${define_symbols}" FORCE_REBUILD )
set(OLD_DEFINES "${define_symbols}" CACHE STRING "Save old defines" FORCE)

list(APPEND display_python_files
    display_text_msg_python.cc
    show_text_python.cc
    show_image_python.cc
    python_bindings.cc)

GR_PYBIND_MAKE_OOT(display
   ../..
   gr::display
   "${display_python_files}")

install(TARGETS display_python DESTINATION ${GR_PYTHON_DIR}/display COMPONENT pythonapi)
