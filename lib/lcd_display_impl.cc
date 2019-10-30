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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "lcd_display_impl.h"
#include <gnuradio/io_signature.h>
#include "freqctrl.h"

namespace gr {
  namespace display {

    lcd_display::sptr
    lcd_display::make(int num_digits,float min_value,float max_value,float akt_value,int min_step,int unit_type,QWidget *parent)
    {
      return gnuradio::get_initial_sptr
        (new lcd_display_impl(num_digits, min_value, max_value,akt_value, min_step, unit_type,parent));
    }


    /*
     * The private constructor
     */
    lcd_display_impl::lcd_display_impl(int num_digits,float min_value,float max_value,float akt_value,int min_step,int unit_type, QWidget *parent)
      : gr::block("lcd_display",
                   gr::io_signature::make(0, 0, 0),
                   gr::io_signature::make(0, 0, 0))
    {
        d_lcd_display = NULL;
        if(qApp != NULL) {
          d_qApplication = qApp;
         }
        else {
          int argc=1;
          char *argv =new char;
          argv[0] = '\0';

          d_qApplication = new QApplication(argc, &argv);
        }
        d_lcd_display = new CFreqCtrl(d_parent);
        message_port_register_in(pmt::mp("freq"));
        set_msg_handler(pmt::mp("freq"), boost::bind(&lcd_display_impl::set_frequency_msg, this, _1));
        message_port_register_out(pmt::intern("freq"));

        d_lcd_display->Setup(num_digits,(qint64)min_value,(qint64)max_value,min_step,(FUNITS) unit_type,this);
        d_old_freq=(qint64) akt_value;
        d_lcd_display->SetFrequency(d_old_freq);


    }

    /*
     * Our virtual destructor.
     */
    lcd_display_impl::~lcd_display_impl()
    {
    }

    PyObject *
    lcd_display_impl::pyqwidget()
    {

     PyObject *w = PyLong_FromVoidPtr((void*)d_lcd_display);
     PyObject *retarg = Py_BuildValue("N", w);
     return retarg;
    }
    void lcd_display_impl::set_frequency_msg(pmt::pmt_t msg)
    {
      // Accepts either a number that is assumed to be the new
      // frequency or a key:value pair message where the key must be
      // "freq" and the value is the new frequency.
      GR_LOG_DEBUG(d_logger,"LCD Display frequency message arrived");
      if(pmt::is_number(msg)) {
        set_freq(pmt::to_float(msg));
        GR_LOG_DEBUG(d_logger,boost::format("LCD Display set value to: %1%")%pmt::to_float(msg));
      }
      else if(pmt::is_pair(msg)) {
        GR_LOG_DEBUG(d_logger,"LCD Display frequency pair message");
        pmt::pmt_t key = pmt::car(msg);
        pmt::pmt_t val = pmt::cdr(msg);
        if(pmt::eq(key, pmt::intern("freq"))) {
          if(pmt::is_number(val)) {
              set_freq(pmt::to_float(val));
              GR_LOG_DEBUG(d_logger,boost::format("LCD Display set value to: %1%")%pmt::to_float(val));
          }
          else
              GR_LOG_DEBUG(d_logger,boost::format("LCD Display frequency message not a number: %1% ")% pmt::write_string(val));
        }
        else { 
          GR_LOG_WARN(d_logger, boost::format("Set Frequency Message must have the key = 'freq'; got %1%.")% pmt::write_string(key));
        }
      }
      else {
        GR_LOG_WARN(d_logger, "Set Frequency Message must be either a number or a key:value pair where the key is 'freq'.");
      }
   
    }

    void lcd_display_impl::set_freq(float f)
    {
      d_lcd_display->SetFrequency((qint64) f);
      message_port_pub(pmt::intern("freq"),pmt::cons( pmt::intern("freq"), pmt::from_float(f) ));
      GR_LOG_DEBUG(d_logger,boost::format("LCD Display push freq message with : %1%")%f);
    }
    void lcd_display_impl::sendMsg(qint64 f)
    {
      message_port_pub(pmt::intern("freq"),pmt::cons( pmt::intern("freq"), pmt::from_float((float)f) ));
      GR_LOG_DEBUG(d_logger,boost::format("LCD Display push freq message with : %1%")%pmt::from_float((float)f));
    }
  } /* namespace display */
} /* namespace gr */

