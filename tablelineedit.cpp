#include "tablelineedit.h"

TableLineEdit::TableLineEdit(QWidget* parent, unsigned char itP, unsigned char itLine) : QLineEdit(parent)
{
    myItPoint = itP;
    myLine = itLine;
}
