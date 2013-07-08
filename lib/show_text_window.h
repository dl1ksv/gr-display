/***************************************************************************
 *   Copyright (C) 2013 by Volker Schroer, DL1KSV                          *
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

#include <QWidget>

namespace Ui {
  class show_text_window;
}

class show_text_window : public QWidget
{
  Q_OBJECT
  
public:
  explicit show_text_window(QWidget *parent = 0);
  ~show_text_window();
  void set_text(const char *c, int count);
  
private:
  Ui::show_text_window *ui;
private slots:
  void text2File();
  void clearText();
};

#endif // SHOW_TEXT_WINDOWS_H
