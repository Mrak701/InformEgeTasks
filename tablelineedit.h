#ifndef TABLELINEEDIT_H
#define TABLELINEEDIT_H

#include "QLineEdit"

class TableLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    unsigned char myItPoint = 0;
    unsigned char myLine = 0;
    TableLineEdit(QWidget* parent, unsigned char itP, unsigned char itLine);
};

#endif // TABLELINEEDIT_H
