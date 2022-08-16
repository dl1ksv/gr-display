/* -*- c++ -*- */
/*
 * Copyright 2022 Volker Schroer, DL1KSV
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */


#ifndef INCLUDED_DISPLAY_SHOW_IMAGE_H
#define INCLUDED_DISPLAY_SHOW_IMAGE_H

#include <gnuradio/sync_block.h>
#include <display/api.h>
#include <QWidget>


class ShowPngPicture;

namespace gr {
namespace display {

/*!
 * \brief display a grayscaled ( png ) image
 * \ingroup display
 *
 * \details
 * This block displays an grayscaled image in a
 * scrollable window
 * The image may be saved as png image to the filesystem
 *
 */
class DISPLAY_API show_image : virtual public sync_block
{
public:
    typedef std::shared_ptr<show_image> sptr;

    /*!
     * \brief Build an image sink
     *
     * \param imagewidth Width of the image
     * \param imageheight Maximum height of image
     * \param parent a QWidget parent widget, may be nullptr
     *
     */
    static sptr make(int imagewidth, int imageheight, QWidget* parent = nullptr);

    virtual void exec_() = 0;
    virtual QWidget* qwidget() = 0;

    virtual void displayBottomUp(bool direction) = 0;
};

} // namespace display
} // namespace gr

#endif /* INCLUDED_DISPLAY_SHOW_IMAGE_H */
