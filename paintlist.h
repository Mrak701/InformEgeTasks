#ifndef PAINTLIST_H
#define PAINTLIST_H

#include <QtWidgets>
#include "qpointdrawing.h"

class PaintList : public QWidget
{
    Q_OBJECT
public:    
    PaintList(QWidget *parent, const unsigned char radiusDelete);

    void addPoint(QPointDrawing* nPoint);
    QList<QPointDrawing*> getPoints();
    void setItCircle(unsigned char it);
    unsigned char getItCircle();
    void deletePoint(unsigned char it);
    void bind2Points(unsigned char fIt, unsigned char sIt);        

protected:
    void paintEvent(QPaintEvent* event);
private:    
    QList<QPointDrawing*> points;
    QList<QPoint2*> lines;
    unsigned char itCircle = 255;
    unsigned char radiusDelete = 0;
    inline void deleteLines(unsigned char it);

};

#endif // PAINTLIST_H
