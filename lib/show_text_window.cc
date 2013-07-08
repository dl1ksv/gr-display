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

#include "show_text_window.h"
#include "ui_show_text_window.h"

#include <QString>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>


show_text_window::show_text_window(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::show_text_window)
{
  ui->setupUi(this);
  ui->textDisplay->setText("");
  connect(ui->clear,SIGNAL(clicked()),this,SLOT(clearText()));
  connect(ui->save,SIGNAL(clicked()),this,SLOT(text2File()));
}

show_text_window::~show_text_window()
{
  delete ui;
}
void show_text_window::set_text(const char *c, int count)
{
  if(count == 0)
    return;
  QString s=ui->textDisplay->text()+QString::fromAscii(c,count);
  ui->textDisplay->setText(s);
  update();
}
void show_text_window::text2File()
{
    QString fileName;
    QString dir;
    bool ok;
    dir=QDir::homePath();

    fileName = QFileDialog::getSaveFileName ( 0, tr ( "Save Image" ),dir , "*.txt" );
    if ( !fileName.isEmpty() ) {
        QFile file( fileName );
        if ( file.open(QIODevice::WriteOnly) )
        {
            QTextStream stream( &file );
            stream << ui->textDisplay->text();
        QMessageBox::information ( 0, "gr-display", QString("Text saved to file: ") + fileName);
       }
    }

}
void show_text_window::clearText()
{

  ui->textDisplay->setText("");

}
