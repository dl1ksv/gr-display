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

#ifndef INCLUDED_DISPLAY_TEXT_MSG_H
#define INCLUDED_DISPLAY_TEXT_MSG_H



#include <gnuradio/block.h>
#include <display/api.h>
#ifdef ENABLE_PYTHON
#include <Python.h>
#endif
#include <qapplication.h>
#include <QWidget>

#include <string>

namespace gr {
namespace display {

/*!
 * \brief Create a QT Text box widget (QLabel) where the values are posted as a message.
 * \ingroup display
 *
 * \details
 * This block creates a QT Text box widget that manages data
 * through message passing interfaces. It is derived from the 
 * gnuradio Message Edit Box
 *
 * Message Ports:
 *
 * - text (input):
 *       Accepts text messages to be displayed
 *
 */
class DISPLAY_API text_msg : virtual public block
{
public:

    typedef std::shared_ptr<text_msg> sptr;

    /*!
     * \brief Constructs the Edit box block.
     *
     * \param label a label to identify the box on screen.
     * \param message_key name of the message key or empty
     * \param splitlength split line after splitlength characters
     * \param parent a QWidget parent in the QT app.
     *
     */
    static sptr make(const std::string& label,const std::string& message_key,int splitlength, QWidget* parent = nullptr);

    virtual void exec_() = 0;
    virtual QWidget* qwidget() = 0;
#ifdef ENABLE_PYTHON
    virtual PyObject* pyqwidget() = 0;
#else
    virtual void* pyqwidget() = 0;
#endif

};

} /* namespace display */
} /* namespace gr */

#endif /* INCLUDED_DISPLAY_TEXT_MSG_H */
