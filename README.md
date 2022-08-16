
## gr-display is a small qt based addon for gnuradio.

It contains three components:

+  show_image       : display png images.

+  show_text        : display ascii characters as text in a qt window.

+  display_text_msg : display a message containing text, or a message of type u8vector

 Messages of type u8vector are provided by gr_satellites decoder, for example.

I use show_image to receive and display some weather- satellite pictures with the funcube dongle
and gnuradio.


You'll find them in:


Custom

        Display


1. **Dependencies:**

     + gnuradio ( >= 3.10) with pybind11

     + gr-qtgui

     + qt5


2. **Installation**

     Get the latest code from https://github.com/dl1ksv/gr-display

     The build process is cmake based. So change to the code directory.

     There

     $mkdir build

     $cd build

     $cmake -DCMAKE_INSTALL_PREFIX=   < where gnuradio is installed > ../

     $make

     $sudo make install
     
     After that you'll find in grc in DL1KSV / Display
      
     - Display a text message 
     - PNG Image sink
     - Text sink.


 ++++ If you are unsure about where gnuradio is installed  run

     gnuradio-config-info --prefix


     **Hint:**  
     You can install gr-display to an other directory than gnuradio. But then you have to add
     the location of your python modules to the PYTHONPATH environment variable and add the location of
     the lib to the LD_LIBRARY_PATH environment variable.

     To see the newly created blocks in grc you have to set the local_blocks_path entry in ~/.gnuradio/config.conf.
     Example: If you choose /usr/local/oot as installation directory, you have to set 
     local_blocks_path = /usr/local/oot/share/gnuradio/grc/blocks
     

3.    **Changes**
 
      Two additional parameters where introduced:

      - splitlength  
If splitlength > 0 , a linebreak is inserted if the linelength exceeds splitlength characters.
      - maxlines  
Restricts the display height to maxlines rows

 These parameters where introduced to avoid display problems on heavy load and very long lines.

 An autofocus option was added, so you always see new text, if this option is enabled.

      
      
4.    **To do**

      Perhaps do some simple image processing like rotating before saving.



