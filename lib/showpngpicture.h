#ifndef SHOWPNGPICTURE_HH
#define SHOWPNGPICTURE_HH

#include <QWidget>

class bild;
class QTimer;

namespace Ui {
class ShowPngPicture;
}

class ShowPngPicture : public QWidget
{
    Q_OBJECT
    
public:
    explicit ShowPngPicture(int width,int height,QWidget *parent = 0);
    ~ShowPngPicture();
private:
    Ui::ShowPngPicture *ui;
    int picWidth;
    int picHeight;
    int col;
    int row;
    QRgb *line;
    bild *displayWidget;
    QTimer *displayTimer;


public slots:
    void setPixel(const unsigned char *,int);

protected:
   // void paintEvent(QPaintEvent *);
};

#endif // SHOWPNGPICTURE_HH
