#include "showpngpicture.h"
#include "ui_showpngpicture.h"
#include <QPainter>
#include <QTimer>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include "bild.h"

ShowPngPicture::ShowPngPicture(int width,int height,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowPngPicture)
{
    ui->setupUi(this);
    picWidth=width;
    picHeight=height;

    displayWidget= new bild(picWidth,picHeight);
    ui->displayArea->setWidget(displayWidget);
    displayTimer = new QTimer(this);
    connect(displayTimer, SIGNAL(timeout()),displayWidget,SLOT(update()));
    connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(saveImage2File()));
    connect(ui->reverse,SIGNAL(clicked(bool)),displayWidget,SLOT(storeReverse(bool)));
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
void ShowPngPicture::saveImage2File()
{
    QString fileName;
    QString dir;
    bool ok;
    dir=QDir::homePath();

    fileName = QFileDialog::getSaveFileName ( 0, tr ( "Save Image" ),dir , "*.png" );
    if ( !fileName.isEmpty() )
       ok= displayWidget->saveImage(fileName);
    if(ok)
        QMessageBox::information ( 0, "gr-display", QString("Image saved to file: ") + fileName);

}
