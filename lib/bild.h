/* 
 * File:   bild.h
 * Author: schroer
 *
 * Created on 4. Oktober 2011, 11:57
 */

#ifndef BILD_H
#define	BILD_H
#include <QWidget>
class QImage;

class bild : public QWidget {
    Q_OBJECT
public:
    bild(int,int);
    virtual ~bild();
    bool saveImage(QString);
private:
    QImage *p;
    int picWidth;
    int picHeight;
    int col;
    int row;
    QRgb *line;
    bool reverseOrder;

public slots:
    void setNextPixel(int);
    void storeReverse(bool order);
protected:
    void paintEvent(QPaintEvent *);
};

#endif	/* BILD_H */

