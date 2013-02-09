#include "showpngpicture.h"
//#include "showpngpicture.ui.h"
#include "ui_showpngpicture.h"
#include <QPainter>
#include <QTimer>

#include "bild.h"

ShowPngPicture::ShowPngPicture(int width,int height,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowPngPicture)
{
    ui->setupUi(this);
    picWidth=width;
    picHeight=height;

 //   this->setFixedSize(picWidth+10,picHeight+10);
    displayWidget= new bild(picWidth,picHeight);
    ui->displayArea->setWidget(displayWidget);
    displayTimer = new QTimer(this);
    connect(displayTimer, SIGNAL(timeout()),displayWidget,SLOT(update()));
    displayTimer->start(500);

}

ShowPngPicture::~ShowPngPicture()
{
    delete ui;
}

void ShowPngPicture::setPixel(const unsigned char *c,int items)
{
    int j;
    for(int i=0; i <items;i++)
    {
     j=c[i];
     displayWidget->setNextPixel(j);
    } 
}
