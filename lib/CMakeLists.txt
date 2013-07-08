# Copyright 2011 Free Software Foundation, Inc.
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX
########################################################################
# Set QT generation stuff
########################################################################
set(display_moc_hdrs
    bild.h
    showpngpicture.h
    show_text_window.h
)

QT4_WRAP_CPP(display_moc_srcs ${display_moc_hdrs})
QT4_WRAP_UI(display_ui_hdrs showpngpicture.ui show_text_window.ui)

set(display_srcs
    ${display_moc_srcs}
    ${display_ui_hdrs}
    display_show_image.cc
    bild.cc
    showpngpicture.cc
    show_text_impl.cc
    show_text_window.cc
)
add_library(gnuradio-display SHARED ${display_srcs})
target_link_libraries(gnuradio-display ${Boost_LIBRARIES} ${GRUEL_LIBRARIES} ${GNURADIO_CORE_LIBRARIES} ${QT_LIBRARIES})
set_target_properties(gnuradio-display PROPERTIES DEFINE_SYMBOL "gnuradio_display_EXPORTS")

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-display
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
find_package(Boost COMPONENTS unit_test_framework)

#include(GrTest)
#set(GR_TEST_TARGET_DEPS gnuradio-display)
#turn each test cpp file into an executable with an int main() function
#add_definitions(-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN)

