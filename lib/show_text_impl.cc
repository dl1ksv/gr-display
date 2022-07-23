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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#include "show_text_impl.h"
#include "show_text_window.h"
#include <gnuradio/io_signature.h>


#include <iostream>

namespace gr {
namespace display {

show_text::sptr
show_text::make(const std::string& label, int splitlength, int maxlines, QWidget* parent)
{
    return gnuradio::make_block_sptr<show_text_impl>(
        label, splitlength, maxlines, parent);
}

/*
 * The private constructor
 */
show_text_impl::show_text_impl(const std::string& label,
                               int splitlength,
                               int maxlines,
                               QWidget* parent)
    : gr::sync_block("show_text",
                     gr::io_signature::make(1, 1, sizeof(char)),
                     gr::io_signature::make(0, 0, 0)),
      d_splitlength(splitlength),
      d_parent(parent)
{
    d_main_gui = nullptr;
    d_argv = nullptr;
    if (qApp != nullptr) {
        d_qApplication = qApp;
    } else {
        int argc = 1;
        d_argv = new char;
        d_argv[0] = '\0';

        d_qApplication = new QApplication(argc, &d_argv);
    }
    d_main_gui = new show_text_window(d_splitlength, maxlines, d_parent);
    d_main_gui->setHeader(QString(label.c_str()));
}

/*
 * Our virtual destructor.
 */
show_text_impl::~show_text_impl()
{
    if (d_argv != nullptr)
        delete d_argv;
}

int show_text_impl::work(int noutput_items,
                         gr_vector_const_void_star& input_items,
                         gr_vector_void_star& output_items)
{
    const char* in = (const char*)input_items[0];

    gr::thread::scoped_lock lock(d_setlock);

    // Tell runtime system how many output items we produced.
    d_main_gui->set_text(in, noutput_items);
    return noutput_items;
}

void show_text_impl::exec_() { d_qApplication->exec(); }

QWidget* show_text_impl::qwidget() { return d_main_gui; }

} /* namespace display */
} /* namespace gr */
