/* -*- c++ -*- */
/* 
 * Copyright 2013 Volker Schroer, DL1KSV.
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
#include <display/api.h>
#include <gnuradio/sync_block.h>
#include <QWidget>


class QApplication;
class ShowPngPicture;

namespace gr {
  namespace display {

    /*!
     * \brief display a grayscaled ( png ) image
     * \ingroup display
     *
     */
   class DISPLAY_API show_image : virtual public sync_block
    {
     public:
      typedef boost::shared_ptr<show_image> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of display::show_image.
       *
       * To avoid accidental use of raw pointers, display::show_image's
       * constructor is in a private implementation
       * class. display::show_image::make is the public interface for
       * creating new instances.
       */
      static sptr make(int imagewidth,int imageheight,QWidget *parent=NULL);
      virtual PyObject* pyqwidget()=0;
    };

  } // namespace display
} // namespace gr

#endif /* INCLUDED_DISPLAY_SHOW_IMAGE_H */
