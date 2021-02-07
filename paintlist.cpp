#include "paintlist.h"

PaintList::PaintList(QWidget *parent, unsigned char rDelete) : QWidget(parent)
{
    this->radiusDelete = rDelete;
}
void PaintList::paintEvent(QPaintEvent* event){
    Q_UNUSED(event);
    QPainter painter(this); // Создаём объект отрисовщика
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen;

    pen.setColor(Qt::blue);
    pen.setWidth(3); // толщина пера
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::black));

    for(int i = 0; i < points.size();i++){
        painter.drawPoint(*points[i]);
    }
    for(int i = 0; i < lines.size();i++){
        painter.drawLine(*lines[i]->first, *lines[i]->second);
    }
    pen.setColor(Qt::gray);//чертим рамку
    painter.setPen(pen);
    painter.drawLine(QPoint(0, 0), QPoint(0, height()));
    painter.drawLine(QPoint(0, 0), QPoint(width(), 0));
    painter.drawLine(QPoint(width(), 0), QPoint(width(),height()));
    painter.drawLine(QPoint(0, height()), QPoint(width(),height()));


    pen.setColor(Qt::cyan);
    painter.setPen(pen);

    if(itCircle != 255){
        painter.drawEllipse(*points[itCircle], radiusDelete, radiusDelete);
    }
    painter.end();
}

void  PaintList::addPoint(QPointDrawing* nPoint){
    points.append(nPoint);
}

void PaintList::setItCircle(unsigned char it){
    itCircle = it;
}
unsigned char PaintList::getItCircle(){
    return itCircle;
}
void PaintList::deletePoint(unsigned char it){
    itCircle = 255;

    deleteLines(it);
    delete  points[it];
    points.removeAt(it);
}

void PaintList::deleteLines(unsigned char it){//метод проверяет все линии, и уничтожает присоеденённые к точке.
    bool isChecked = false;
    while(true){
        for(int i = 0; i < lines.size(); i++){
            if(lines[i]->first == points[it] || lines[i]->second == points[it]){
                delete  lines[i];
                lines.removeAt(i);
                isChecked = true;
            }
        }
        if(isChecked == false)
            break;

        isChecked = false;
    }
}

void PaintList::bind2Points(unsigned char fIt, unsigned char sIt){
    QPoint2* newLine  = new QPoint2(points[fIt], points[sIt]);
    lines.append(newLine);
    points[fIt]->bind(points[sIt], sIt);
    points[sIt]->bind(points[fIt], fIt);
}

QList<QPointDrawing*> PaintList::getPoints(){
    return points;
}
