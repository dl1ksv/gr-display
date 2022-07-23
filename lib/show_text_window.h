/***************************************************************************
 *   Copyright (C) 2022 by Volker Schroer, DL1KSV                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef SHOW_TEXT_WINDOWS_H
#define SHOW_TEXT_WINDOWS_H

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>


class show_text_window : public QWidget
{
    Q_OBJECT

public:
    explicit show_text_window(int splitlength, int maxlines, QWidget* parent = 0);
    void set_text(const char* c, int count);
    void setHeader(QString header);

private:
    QVBoxLayout* d_vertical_layout;
    QLabel* d_label;
    QScrollArea* d_display_area;
    QHBoxLayout* d_horizontal_layout;
    QPushButton* d_clear;
    QSpacerItem* d_horizontal_spacer;
    QRadioButton* d_auto_focus;
    QSpacerItem* d_horizontal_spacer_2;
    QPushButton* d_save;
    QVBoxLayout* d_lines_layout;

    QString d_line;

    int d_splitlength;
    unsigned int d_linecount;
    unsigned int d_maxlines;
    bool d_line_to_be_continued;

    QWidget* d_d_display_box;
    QLabel** d_lines;
    bool d_autofocus;
    void insert_nl_into_line(int from);
    void move_input2lines();
    void scroll_up(unsigned int rows, bool d_clear);

private slots:
    void text2File();
    void clearText();
    void autofocus_enable(bool);
};

#endif // SHOW_TEXT_WINDOWS_H
