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

  line[col]=qRgb(i,i,i);
  if(!reverseOrder)
  {
   col++;
   if(col >= picWidth)
   {
    col=0;
    row++;
    if(row >=picHeight)
      row= picHeight-1; // Later scroll up
   line = (QRgb *) p->scanLine(row);
   }
  }
  else
  {
   col--;
   if (col < 0)
   {
     col=picWidth-1;
     row--;
     if(row < 0)
         row=0;
     line = (QRgb *) p->scanLine(row);
   }
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
void bild::storeReverse(bool order)
{
 if(reverseOrder == order)
     return;
 reverseOrder=order;
 p->fill(64);
 if(reverseOrder)
 {
   row=picHeight-1;
   col=picWidth-1;
 }
 else
 {
   row=0;
   col=0;
 }
 line = (QRgb *) p->scanLine(row);
}
