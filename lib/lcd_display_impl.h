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

#ifndef INCLUDED_DISPLAY_LCD_DISPLAY_IMPL_H
#define INCLUDED_DISPLAY_LCD_DISPLAY_IMPL_H

#include <display/lcd_display.h>

#include <qapplication.h>

class CFreqCtrl;

namespace gr {
  namespace display {

    class lcd_display_impl : public lcd_display
    {
     private:

      QWidget *d_parent;
      QApplication *d_qApplication;
      CFreqCtrl *d_lcd_display;  

      void set_frequency_msg(pmt::pmt_t msg);
      void set_freq(float f);

      qint64 d_old_freq;
     public:
      lcd_display_impl(int num_digits,float min_value,float max_value,float akt_value,int min_step,int unit_type,QWidget* parent = NULL);
      ~lcd_display_impl();
      PyObject* pyqwidget();
      void sendMsg(qint64 f);
typedef void (*sendmsg)(qint64);
    };

  } // namespace display
} // namespace gr



#endif /* INCLUDED_DISPLAY_LCD_DISPLAY_IMPL_H */

