/* -*- c++ -*- */
/*
 * Copyright 2019 dl1ksv.
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

#ifndef INCLUDED_DISPLAY_LCD_DISPLAY_H
#define INCLUDED_DISPLAY_LCD_DISPLAY_H

#include <display/api.h>
#include <gnuradio/block.h>
#include <Python.h>

class QWidget;

namespace gr {
  namespace display {

    /*!
     * \brief <+description of block+>
     * \ingroup display
     *
     */
    class DISPLAY_API lcd_display : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<lcd_display> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of display::lcd_display.
       *
       * To avoid accidental use of raw pointers, display::lcd_display's
       * constructor is in a private implementation
       * class. display::lcd_display::make is the public interface for
       * creating new instances.
       */
      static sptr make(int num_digits,float min_value,float max_value,float akt_value,int min_step,int unit_type,QWidget *parent=NULL);
      virtual PyObject* pyqwidget() =0;
    };

  } // namespace display
} // namespace gr

#endif /* INCLUDED_DISPLAY_LCD_DISPLAY_H */

