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


#ifndef INCLUDED_DISPLAY_SHOW_IMAGE_H
#define INCLUDED_DISPLAY_SHOW_IMAGE_H

#include <Python.h>
#include <display_api.h>
#include <gr_sync_block.h>
#include <qapplication.h>
#include <gruel/high_res_timer.h>

#include "showpngpicture.h"

class display_show_image;
typedef boost::shared_ptr<display_show_image> display_show_image_sptr;

DISPLAY_API display_show_image_sptr display_make_show_image (int imagewidth,
                                                             int imageheight,
                                                             QWidget *parent=NULL);

/*!
 * \brief display a grayscaled ( png ) image
 * \ingroup block
 *
 */
class DISPLAY_API display_show_image : public gr_sync_block
{
 private:
    friend DISPLAY_API display_show_image_sptr display_make_show_image (int imagewidth,
                                                                        int imageheight,
                                                                        QWidget *parent);

    display_show_image(int imagewidth,int imageheight,QWidget *parent);
  /* Variables */

   QWidget *d_parent;
   ShowPngPicture *d_main_gui;

   double d_update_time;
   gruel::high_res_timer_type d_current_time;
   gruel::high_res_timer_type  d_last_time;



   int nx_samples;
   int width;
   int height;

 public:
  ~display_show_image();
   void exec_();
 //  QWidget*  qwidget();
   PyObject* pyqwidget();
   QApplication *d_qApplication;

	// Where all the action really happens
	int work (int noutput_items,
	    gr_vector_const_void_star &input_items,
	    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_DISPLAY_SHOW_IMAGE_H */

