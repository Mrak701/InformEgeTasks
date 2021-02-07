#include "qpointdrawing.h"
#include <QDebug>
#include <firsttask.h>

QPointDrawing::QPointDrawing(const QPoint pos, QLineEdit* nmEdit, unsigned char it):QPoint(pos)
{
    nameEdit = nmEdit;
    myIt = it;
    for(int i = 0; i < FirstTask::maxPoints;i++){
        bindings[i] = nullptr;            
    }
    connect(nameEdit,SIGNAL(textChanged(const QString)), SLOT(setName(const QString)));
}
void QPointDrawing::setName(const QString n){
    name = n;
}
void QPointDrawing::bind(QPointDrawing *p, unsigned char itPoint){
    bindings[itPoint] = p;
}
unsigned char QPointDrawing::getBindingsCount(){
    int retValue = 0;
    for(int i = 0; i < FirstTask::maxPoints;i++){
        if(bindings[i] != nullptr)
            retValue++;
    }
    return retValue;
}

QString QPointDrawing::getName(){
    return name;
}

bool QPointDrawing::isConnectedTo(unsigned char it){
    if(bindings[it])
        return true;

    return false;
}

QPointDrawing::~QPointDrawing(){
    delete nameEdit;
}
