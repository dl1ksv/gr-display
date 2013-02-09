/* -*- c++ -*- */
/* 
 * Copyright 2013 Volker Schroer, DL1KSV
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gr_io_signature.h>
#include "display_show_image.h"


#include <cstdlib>
#include <iostream>


display_show_image_sptr
display_make_show_image (int imagewidth,int imageheight,QWidget *parent)
{
    return gnuradio::get_initial_sptr (new display_show_image(imagewidth, imageheight, parent));
}

/*
 * The private constructor
 */
display_show_image::display_show_image (int imagewidth,int imageheight,QWidget *parent)
  : gr_sync_block ("show_image",
		   gr_make_io_signature(1, 1, sizeof (char)),
		   gr_make_io_signature(0, 0, 0)),
		    width(imagewidth),height(imageheight),d_parent(parent)
{
    d_main_gui = NULL;
    if(qApp != NULL) {
      d_qApplication = qApp;
    }
    else {
      int argc=0;
      char **argv = NULL;
      d_qApplication = new QApplication(argc, argv);
    }
    d_main_gui = new ShowPngPicture(width,height,d_parent);

}


/*
 * Our virtual destructor.
 */
display_show_image::~display_show_image()
{
	// Put in <+destructor stuff+> here
}


int
display_show_image::work(int noutput_items,
		  gr_vector_const_void_star &input_items,
		  gr_vector_void_star &output_items)
{
        const unsigned char *in = (const unsigned char *) input_items[0];
        // Do signal processing
         d_main_gui->setPixel(in,noutput_items);
        // Tell runtime system how many output items we produced.
	return noutput_items;
}
/**
QWidget *display_show_image::qwidget()
{
  return d_main_gui;
}
**/
PyObject *display_show_image::pyqwidget()
{

 PyObject *w = PyLong_FromVoidPtr((void*)d_main_gui);
 PyObject *retarg = Py_BuildValue("N", w);
 return retarg;
}

void display_show_image::exec_()
{
std::cout << "Calling exec" << std::endl;
 d_qApplication->exec();
}
