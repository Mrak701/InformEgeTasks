#ifndef POINTTABLE_H
#define POINTTABLE_H

#include <QLabel>
#include "tablelineedit.h"

class PointTable{
private:
    QLabel* horlbl, *verlbl;
    QList<TableLineEdit*> tableEdits;
    unsigned char bindings[8];
public:    
    PointTable(QLabel* hlbl,QLabel* vlbl);
    void addLineEdit(TableLineEdit* ln);
    void bind(int newValue, unsigned char itPoint);
    unsigned char getBindingsCount();
    QList<TableLineEdit*> getTableEdits();
    int getDistanceTo(unsigned char name);
    ~PointTable();
};

#endif // POINTTABLE_H
