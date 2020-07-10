

title: gr-display

brief: A small qt based addon for gnuradio

tags:

gui, display, png images, ascii, lcd display

author: - Volker Schroer
 
copyright_owner: - Volker Schroer

dependencies:

  - gnuradio (>= 3.9.0) with pybind
  - gr-qtgui
  - qt5

repo: https://github.com/dl1ksv/gr-display.git

gr-display is a small qt based addon for gnuradio.

It contains three components:

show_image   - to display png images.

show_text    - to display ascii characters as text in a qt window.

display_text_msg - display a message containing text
               
I use show_image to receive and display some weather- satellite pictures with the funcube dongle
and gnuradio.

You'll find them in
Custom - Display in grc.

