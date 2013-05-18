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
#ifndef INCLUDED_DISPLAY_SHOW_TEXT_IMPL_H
#define INCLUDED_DISPLAY_SHOW_TEXT_IMPL_H

#include <display/show_text.h>
#include <QApplication>

class show_text_window;

namespace gr {
  namespace display {

    class show_text_impl : public show_text
    {
     private:
      QWidget *d_parent;
      QApplication *d_qApplication;
      show_text_window *d_main_gui;

     public:
      show_text_impl(QWidget *parent);
      ~show_text_impl();
      PyObject* pyqwidget();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace display
} // namespace gr

#endif /* INCLUDED_DISPLAY_SHOW_TEXT_IMPL_H */

