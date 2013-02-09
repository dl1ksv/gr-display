/* -*- c++ -*- */

#define DISPLAY_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "display_swig_doc.i"


%{
#include "display_show_image.h"
%}

GR_SWIG_BLOCK_MAGIC(display,show_image)

display_show_image_sptr display_make_show_image(int imagewidth,
                                                int imageheight,
                                                QWidget *parent=NULL);

class display_show_image : public gr_block
{
private:
  friend display_show_image_sptr display_make_show_image(int imagewidth,
                                                          int imageheight,
                                                          QWidget *parent);

  display_show_image(int imagewidth,
                        int imageheight,
                        QWidget *parent);

public:
  void exec_();
  PyObject* pyqwidget();

};
