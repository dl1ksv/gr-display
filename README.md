##gr-display is a small qt based addon for gnuradio.

It contains three components:

+  show_image : display png images.

+  show_text  : display ascii characters as text in a qt window.

+  lcd_display: display and control numbers, that can be used control frequencies by sending messages

                 See the lcd_example in the examples directory to get an impression

I use show_image to receive and display some weather- satellite pictures with the funcube dongle
and gnuradio.

All blocks are using the latest 3.9- api.

You'll find them in:


Custom

        Display


1. **Dependencies:**

     -- gnuradio (3.9)

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


4.    **Using the example** 

      The example shows the usage of the show_image block and requires the gr-fcdproplus block.You have to run the decodeapt block and install it in your grc, first. You'll find this afterwards in the 'custom' section.

      An example for the usage of the show_text block can be found in the gr-ax25 block.
      
      The lcd_example..grc in the example folder demonstrates how to use the lcd display.  

5.    **Credits**

      The apt decoder part is based on an decoder prototype by  Alexandru Csete, OZ9AEC.

       lcd_display uses freqctrl.h and freqctrl.cpp which  were adopted from Cutesdr by Moe Weatley to gnuradio and these come with a Simplified BSD license.

