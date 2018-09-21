title: gr-display
brief: A small qt based addon for gnuradio
tags:
  - gui
  - display
  - png
  - images
  - ascii
author:
  - Volker Schroer
copyright_owner:
  - Volker Schroer
dependencies:
  - gnuradio (>= 3.8.0)
  - gr-qtgui
  - qt5
repo: https://github.com/dl1ksv/gr-display.git
---
gr-display is a small qt based addon for gnuradio.

It contains two components:
show_image   - to display png images.
show_text    - to display ascii characters as text in a qt window.

I use show_image to receive and display some weather- satellite pictures with the funcube dongle
and gnuradio.

You'll find them in
Custom - Display in grc.

