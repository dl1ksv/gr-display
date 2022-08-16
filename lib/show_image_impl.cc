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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#include "show_image_impl.h"
#include "showpngpicture.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace display {

show_image::sptr show_image::make(int imagewidth, int imageheight, QWidget* parent)
{
    return gnuradio::get_initial_sptr(
        new show_image_impl(imagewidth, imageheight, parent));
}

/*
 * The private constructor
 */
show_image_impl::show_image_impl(int imagewidth, int imageheight, QWidget* parent)
    : gr::sync_block("show_image",
                     gr::io_signature::make(2, 2, sizeof(char)),
                     gr::io_signature::make(0, 0, 0)),
      d_width(imagewidth),
      d_height(imageheight),
      d_parent(parent)
{
    d_main_gui = NULL;
    if (qApp != NULL) {
        d_qApplication = qApp;
    } else {
        int argc = 1;
        char* argv = new char;
        argv[0] = '\0';
        d_qApplication = new QApplication(argc, &argv);
    }
    d_main_gui = new ShowPngPicture(d_width, d_height, d_parent);
    d_triggered = false;
}

/*
 * Our virtual destructor.
 */
show_image_impl::~show_image_impl() {}

int show_image_impl::work(int noutput_items,
                          gr_vector_const_void_star& input_items,
                          gr_vector_void_star& output_items)
{
    const unsigned char* in = (const unsigned char*)input_items[0];
    const char* ctrl = (const char*)input_items[1];

    gr::thread::scoped_lock lock(d_setlock);

    if (d_triggered) {
        // Do signal processing
        d_main_gui->setPixel(in, noutput_items);
    } else {
        int i = 0;
        while (i < noutput_items && ctrl[i] == 0) {
            i++;
        }
        if (i < noutput_items) {
            d_triggered = true;
            d_main_gui->setPixel(in + i, noutput_items - i);
        }
    }
    // Tell runtime system how many output items we produced.
    return noutput_items;
}

void show_image_impl::displayBottomUp(bool direction)
{
    d_main_gui->presetBottomUp(direction);
}

QWidget* show_image_impl::qwidget() { return d_main_gui; }

void show_image_impl::exec_() { d_qApplication->exec(); }

} /* namespace display */
} /* namespace gr */
