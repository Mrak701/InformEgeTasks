#ifndef FIRSTTASK_H
#define FIRSTTASK_H

#include "paintlist.h"
#include "tablelineedit.h"
#include "pointtable.h"

class FirstTask : public QWidget
{
    Q_OBJECT
public:
    explicit FirstTask(QWidget *parent = nullptr);
    static const unsigned char maxPoints = 8;
private:
    QPushButton* modeBtns[3];
    QPushButton* btnCalculate;
    void mousePressEvent (QMouseEvent* event);
    bool modes[3]{false, false, false};
    PaintList* pList;
    QList<PointTable*> tablePoints;
    QLabel* table;
    QLabel* tableAnswers[8];

    QPoint lastPos;
    unsigned char lastTitlePoint = 1;
    unsigned char firstSelectedPoint = 255, secondSelectedPoint = 255;
    void disableModes(unsigned char curMode);    
    void createPoint(QPoint position);
    void findMinPoint();
    void changeAnswer();

    QLineEdit* startDistLine;
    QLineEdit* endDistLine;
    QLineEdit* answerLine;

private slots:
    void setPaintMode();
    void setBindMode();
    void setDeleteMode();
    void updateEvent();   
    void updateEdits();
    void changeTableValue(const QString v);
    void calculateDistance(const QString v);

private://properties
    const int minDeleteDistance = 20;
    bool mouseDown0;   
    int minPointIt;
    int minValue;
    QList<QPointDrawing*> listP;
    QList<int> delPoints;
    QList<QString> connectors;    
};

#endif // FIRSTTASK_H

