/* -*- c++ -*- */
/*
 * Copyright 2022 Volker Schroer, DL1KSV
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef INCLUDED_DISPLAY_SHOW_TEXT_H
#define INCLUDED_DISPLAY_SHOW_TEXT_H

#ifdef ENABLE_PYTHON
#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")
#endif

#include <gnuradio/sync_block.h>
#include <display/api.h>

#include <QWidget>

#include <string>

// class QApplication;

namespace gr {
namespace display {

/*!
 * \brief Create a QT Text sink, where the values are received as stream.
 * \ingroup display
 *
 * \details
 * This is a QT-based graphical sink that display simply ascii text in  a scrollable
 * window
 */
class DISPLAY_API show_text : virtual public sync_block
{
public:
    typedef std::shared_ptr<show_text> sptr;

    /*!
     * \brief Build a graphical sink to display ascii text
     *
     * \param label Header text of the window
     *              usefull  if using several windows
     * \param splitlength enter newline after splitlength
     *                    characters without newline
     * \param maxlines maximum number of lines that
     *                  can be displayed in the scrollarea
     * \param parent a QWidget parent in the QT app.
     */
    static sptr make(const std::string& label,
                     int splitlength = 80,
                     int maxlines = 100,
                     QWidget* parent = nullptr);
    virtual QWidget* qwidget() = 0;
    virtual void exec_() = 0;
};

} // namespace display
} // namespace gr

#endif /* INCLUDED_DISPLAY_SHOW_TEXT_H */
