#include "pointtable.h"
#include "firsttask.h"

PointTable::PointTable(QLabel* hlbl,QLabel* vlbl){
    horlbl = hlbl;
    verlbl = vlbl;
    for(int i = 0; i < FirstTask::maxPoints;i++)
        bindings[i] = 0;
}
void PointTable::addLineEdit(TableLineEdit* ln){
    ln->setMaxLength(2);
    ln->resize(20,20);
    ln->show();
    tableEdits.append(ln);
}
void PointTable::bind(int newValue, unsigned char itPoint){
    bindings[itPoint] = newValue;    
}
unsigned char PointTable::getBindingsCount(){
    int retValue = 0;
    for(int i = 0; i < FirstTask::maxPoints;i++){
        if(bindings[i] > 0)
            retValue += bindings[i];
   }
    return retValue;
}
QList<TableLineEdit*> PointTable::getTableEdits(){
    return tableEdits;
}
int PointTable::getDistanceTo(unsigned char it){
    return bindings[it];
}
PointTable::~PointTable(){
    delete horlbl;
    delete verlbl;
    while(tableEdits.size()){
        delete tableEdits.last();
        tableEdits.removeLast();
    }
}
