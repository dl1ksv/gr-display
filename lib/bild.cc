/*
 * File:   pngBild.cpp
 * Author: schroer
 *
 * Created on 4. Oktober 2011, 11:24
 */


#include "bild.h"
#include <QImage>
#include <QPainter>

bild::bild(int width,int height)
{
  picWidth=width;
  picHeight=height;
  p= 0;
  row=0;
  col=0;
  this->setFixedSize(picWidth+20,picHeight+20);
  p=new QImage(picWidth,picHeight,QImage::Format_RGB32);
  p->fill(64);
  line = (QRgb *) p->scanLine(row);
}

bild::~bild()
{
  
}

void bild::setNextPixel(int i)
{

  line[col++]=qRgb(i,i,i);
//  p->setPixel(col++,row,qRgb(i,i,i));
  if(col >= picWidth)
  {
    col=0;
    row++;
//    if ((row % 10) == 0 )
//      update();
    if(row >=picHeight)
      row= picHeight-1; // Later scroll up
   line = (QRgb *) p->scanLine(row);
  }
}

bool bild::saveImage(QString datei)
{
    return p->save(datei,"PNG");
}

void bild::paintEvent(QPaintEvent *)
{

  QPainter painter(this);
  if(p > 0)
    painter.drawImage(0,0,*p);
}
