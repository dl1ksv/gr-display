/* -*- c++ -*- */
/*
 * Copyright 2016 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "display_text_msg_impl.h"

#include <gnuradio/io_signature.h>
#include <gnuradio/prefs.h>

#include <boost/lexical_cast.hpp>

namespace gr {
namespace display {

text_msg::sptr text_msg::make(const std::string& label,
                                      QWidget* parent)
{
    return gnuradio::get_initial_sptr(
        new text_msg_impl(label, parent));
}

text_msg_impl::text_msg_impl(const std::string& label,
                                     QWidget* parent)
    : block("text_msg", io_signature::make(0, 0, 0), io_signature::make(0, 0, 0))
{
    // Required now for Qt; argc must be greater than 0 and argv
    // must have at least one valid character. Must be valid through
    // life of the qApplication:
    // http://harmattan-dev.nokia.com/docs/library/html/qt4/qapplication.html
    d_argc = 1;
    d_argv = new char;
    d_argv[0] = '\0';

    if (qApp != NULL) {
        d_qApplication = qApp;
    } else {
        d_qApplication = new QApplication(d_argc, &d_argv);
    }

    d_text = new show_text_window(parent);
    d_text->setHeader(QString(label.c_str()));

    message_port_register_in(pmt::mp("text"));
    set_msg_handler(pmt::mp("text"), [this] (pmt::pmt_t msg) { this->text_msg_impl::set_value(msg);});
}

text_msg_impl::~text_msg_impl()
{
    delete d_argv;
    delete d_text;
}


void text_msg_impl::exec_() { d_qApplication->exec(); }

QWidget* text_msg_impl::qwidget() { return (QWidget*)d_text; }

PyObject* text_msg_impl::pyqwidget()
{
    PyObject* w = PyLong_FromVoidPtr((void*)d_text);
    PyObject* retarg = Py_BuildValue("N", w);
    return retarg;
}

void text_msg_impl::set_value(pmt::pmt_t val)
{

    std::string xs;
       
    if (pmt::is_pair(val))
       { // Check, if we received a pair
         pmt::pmt_t key = pmt::car(val);
         if(pmt::eq(key, pmt::intern("text")))
           {
             pmt::pmt_t msg = pmt::cdr(val);
             if (!pmt::is_symbol(msg))
                {
                   GR_LOG_WARN(d_logger, "Message pair did not contain a valid text message");
                   return;
                }
              xs = pmt::symbol_to_string(msg);
            }
            else 
              {
                GR_LOG_WARN(d_logger, boost::format("Message must have the key = 'text'; got '%1%'.")% pmt::write_string(key));
                return;
               }
        }
        else
         {
            if (pmt::is_symbol(val))
             {
               xs = pmt::symbol_to_string(val);
             }
            else
             {
                GR_LOG_WARN(d_logger, "Did not find a valid message");
                return;
             }
         }
       d_text->set_text(xs.c_str(),xs.size());
}


} /* namespace qtgui */
} /* namespace gr */
