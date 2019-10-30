

title: gr-display

brief: A small qt based addon for gnuradio

tags:

gui, display, png images, ascii, lcd display

author: - Volker Schroer
 
copyright_owner: - Volker Schroer

dependencies:

  - gnuradio (>= 3.9.0)
  - gr-qtgui
  - qt5

repo: https://github.com/dl1ksv/gr-display.git

gr-display is a small qt based addon for gnuradio.

It contains three components:

show_image   - to display png images.

show_text    - to display ascii characters as text in a qt window.

lcd_display  - to display and control numbers, that can be used control frequencies by sending messages
               See the lcd_example in the examples directory to get an impression
               
I use show_image to receive and display some weather- satellite pictures with the funcube dongle
and gnuradio.

You'll find them in
Custom - Display in grc.

