/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
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

#ifndef INCLUDED_DISPLAY_SHOW_SYNCEDIMAGE_IMPL_H
#define INCLUDED_DISPLAY_SHOW_SYNCEDIMAGE_IMPL_H

#include <display/show_syncedimage.h>

#include <Python.h>
#include <QApplication>

namespace gr {
  namespace display {

    class show_syncedimage_impl : public show_syncedimage
    {
     private:
      /* Variables */

       QWidget *d_parent;

       int d_width;
       int d_height;
       bool d_first_sync;
       ShowPngPicture *d_main_gui;
       const std::string d_title;
       float *d_linebuffer;
       int d_linebuffer_pos;
       int d_linecount;
       int d_samples_since_last_sync;
       unsigned char *d_pixbuff;
       enum SyncStatus { // Synstatus
        None, //  No sync detected
        FirstSync, // First sync detected, has to be validated by an second sync
        InSync     // First sync has been  validated by another sync
        } d_sync_status;
       int d_lost_syncs;
       int d_continuos_syncs;
       /* Functions */
       
       void process_line();
       bool accept_sync(int count );


     public:
      show_syncedimage_impl(const std::string &title,int imagewidth,int imageheight,QWidget *parent=NULL);
      ~show_syncedimage_impl();

      void displayBottomUp(bool direction);

      QWidget*  qwidget();
      PyObject* pyqwidget();
      QApplication *d_qApplication;
      void set_title(const char *title);

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace display
} // namespace gr

#endif /* INCLUDED_DISPLAY_SHOW-IMAGE_IMPL_H */

