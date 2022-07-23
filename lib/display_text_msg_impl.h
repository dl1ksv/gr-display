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

#ifndef INCLUDED_DISPLAY_TEXT_MSG_IMPL_H
#define INCLUDED_DISPLAY_TEXT_MSG_IMPL_H

#include "show_text_window.h"
#include <display/display_text_msg.h>
#include <qapplication.h>

namespace gr {
namespace display {

class DISPLAY_API text_msg_impl : public text_msg
{

public:
    text_msg_impl(const std::string& label,
                  const std::string& message_key,
                  int splitlength,
                  int maxlines,
                  QWidget* parent);
    ~text_msg_impl();

    void exec_();
    QApplication* d_qApplication;
    QWidget* qwidget();

    PyObject* pyqwidget();

    void set_value(pmt::pmt_t val);

private:
    int d_argc;
    char* d_argv;
    show_text_window* d_text;
    int d_splitlength;
    pmt::pmt_t d_message_key;
};

} // namespace display
} /* namespace gr */

#endif /* INCLUDED_DISPLAY_TEXT_MSG_IMPL_H */
