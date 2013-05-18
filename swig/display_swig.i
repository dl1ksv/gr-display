/* -*- c++ -*- */

#define DISPLAY_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "display_swig_doc.i"

%{
#include "display/show_image.h"
#include "display/show_text.h"
%}


%include "display/show_image.h"
GR_SWIG_BLOCK_MAGIC2(display, show_image);
%include "display/show_text.h"
GR_SWIG_BLOCK_MAGIC2(display, show_text);
