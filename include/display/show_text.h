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

#ifndef INCLUDED_DISPLAY_SHOW_TEXT_H
#define INCLUDED_DISPLAY_SHOW_TEXT_H

#include <Python.h>
#include <display/api.h>
#include <gnuradio/sync_block.h>
#include <QWidget>


//class QApplication;

namespace gr {
  namespace display {

    /*!
     * \brief <+description of block+>
     * \ingroup display
     *
     */
    class DISPLAY_API show_text : virtual public sync_block
    {
     public:
      typedef boost::shared_ptr<show_text> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of display::show_text.
       *
       * To avoid accidental use of raw pointers, display::show_text's
       * constructor is in a private implementation
       * class. display::show_text::make is the public interface for
       * creating new instances.
       */
      static sptr make(QWidget *parent=NULL);
      virtual PyObject* pyqwidget()=0;
//      QApplication *d_qApplication;
    };

  } // namespace display
} // namespace gr

#endif /* INCLUDED_DISPLAY_SHOW_TEXT_H */

