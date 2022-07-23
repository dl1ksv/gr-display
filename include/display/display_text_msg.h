/* -*- c++ -*- */
/*
 * Copyright 2022 Volker Schroer
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef INCLUDED_DISPLAY_TEXT_MSG_H
#define INCLUDED_DISPLAY_TEXT_MSG_H

#ifdef ENABLE_PYTHON
#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")
#endif

#include <gnuradio/block.h>
#include <display/api.h>
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
     * \param label Header text of the window
     *              usefull  if using several windows
     * \param message_key name of the message key or empty
     * \param splitlength enter newline after splitlength
     *                    characters without newline
     * \param maxlines maximum number of lines that
     *                  can be displayed in the scrollarea
     * \param parent a QWidget parent in the QT app.
     *
     */
    static sptr make(const std::string& label,
                     const std::string& message_key,
                     int splitlength = 80,
                     int maxlines = 100,
                     QWidget* parent = nullptr);

    virtual void exec_() = 0;
    virtual QWidget* qwidget() = 0;
};

} /* namespace display */
} /* namespace gr */

#endif /* INCLUDED_DISPLAY_TEXT_MSG_H */
