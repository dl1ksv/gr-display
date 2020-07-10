##gr-display is a small qt based addon for gnuradio.

It contains three components:

+  show_image       : display png images.

+  show_text        : display ascii characters as text in a qt window.

+  display_text_msg : display a message containing text


I use show_image to receive and display some weather- satellite pictures with the funcube dongle
and gnuradio.

All blocks are using the latest 3.9 api.

You'll find them in:


Custom

        Display


1. **Dependencies:**

     -- gnuradio (3.9) with pybind11

     -- gr-qtgui

     -- qt5


2. **Installation**

     get the latest code from https://github.com/dl1ksv/gr-display

     The build process is cmake based. So change to the code directory.

     There

     $mkdir build

     $cd build

     $cmake -DCMAKE_INSTALL_PREFIX=<where gnuradio is installed> ../

     $make

     $sudo make install

     ++++ If you are unsure about <where gnuradio is installed> run

     gnuradio-config-info --prefix


     After that you'll find in grc in Custom / Display a lcd display, a PNG Image sink and a Text sink.


3.    **To do**

      Perhaps do some simple image processing like rotating before saving.



