#include "firsttask.h"
#include <QTimer>
const unsigned char FirstTask::maxPoints;
FirstTask::FirstTask(QWidget *parent) : QWidget(parent)
{
    QWidget* btnsPnt = new QWidget(this);
    QVBoxLayout* btnsLayout = new QVBoxLayout;
    modeBtns[0] = new QPushButton("добавить точку");
    modeBtns[1] = new QPushButton("связать точки");
    modeBtns[2] = new QPushButton("удалить точку");
    btnCalculate = new QPushButton("считать");
    for(unsigned long long i = 0; i < sizeof(modeBtns) / sizeof(modeBtns[0]); i++){
        modeBtns[i]->setStyleSheet("background-color : LightCyan;");
        btnsLayout->addWidget(modeBtns[i]);
    }
   btnsLayout->addWidget(btnCalculate);

    btnsPnt->setLayout(btnsLayout);

    connect(modeBtns[0], SIGNAL(clicked()), SLOT(setPaintMode()));
    connect(modeBtns[1], SIGNAL(clicked()), SLOT(setBindMode()));
    connect(modeBtns[2], SIGNAL(clicked()), SLOT(setDeleteMode()));
    connect(btnCalculate, SIGNAL(clicked()), SLOT(updateEdits()));



    pList = new PaintList(this, minDeleteDistance / 3);
    pList->move(x() + 100, y() + 50);
    pList->setFixedSize(350, 350);
    table = new QLabel(this);
    pList->move(x() + 100, y() + 50);
    table->setFixedSize(350, 350);
    table->setStyleSheet("background-color:gray;");
    table->move(pList->pos().x() + 400, pList->pos().y());
    QTimer* timer = new QTimer;
    connect(timer, SIGNAL(timeout()), SLOT(updateEvent()));
    timer->start(50);
    setMouseTracking(true);

    QLabel* startlbl = new QLabel("Откуда", this);
    QLabel* endlbl = new QLabel("Куда", this);
    QLabel* answerlbl = new QLabel("Итог", this);
    startDistLine = new QLineEdit(this);
    endDistLine = new QLineEdit(this);
    answerLine = new QLineEdit(this);
    startDistLine->move(pList->width() / 1.1f ,pList->pos().y() + 400);
    startlbl->move(startDistLine->x() + startDistLine->width()/2, startDistLine->y() - 20);

    endDistLine->move(table->pos().x() ,pList->pos().y() + 400);
    endlbl->move(endDistLine->x() + endDistLine->width()/2, startDistLine->y() - 20);

    answerLine->move(startDistLine->x() + ((endDistLine->x() - startDistLine->x()) / 2), 500);
    answerlbl->move(answerLine->x() + answerLine->width() / 2, answerLine->y() - 20);


    connect(startDistLine, SIGNAL(textChanged(const QString)), SLOT(calculateDistance(const QString)));
    connect(endDistLine, SIGNAL(textChanged(const QString)), SLOT(calculateDistance(const QString)));

    for(int i = 0; i < maxPoints; i++){
        tableAnswers[i] = new QLabel("N/A",table);
        tableAnswers[i]->move(305, (i + 1) * 40 + 5);
        tableAnswers[i]->setFixedWidth(40);
        tableAnswers[i]->show();
    }


    //create test points

    createPoint(QPoint(20,150));
    createPoint(QPoint(60,100));pList->bind2Points(0, 1);
    createPoint(QPoint(100,150));pList->bind2Points(1, 2);pList->bind2Points(0, 2);

    createPoint(QPoint(140,150));pList->bind2Points(2, 3);
    createPoint(QPoint(180,100));pList->bind2Points(3, 4);
    createPoint(QPoint(220,150));pList->bind2Points(3, 5);pList->bind2Points(4, 5);

    createPoint(QPoint(260,100));pList->bind2Points(4, 6);



}
void FirstTask::calculateDistance(const QString v){
    Q_UNUSED(v);
    bool isContains[1][2]  {{false, false}};
    for(unsigned long long i = 0; i < sizeof(tableAnswers) / sizeof(tableAnswers[0]); i ++){//проверки на легитимость введенных точек(если существуют)
        if(tableAnswers[i]->text() == startDistLine->text()){
            isContains[0][0] = true;
            break;
        }
    }
    for(unsigned long long i = 0; i < sizeof(tableAnswers) / sizeof(tableAnswers[0]); i ++){
        if(tableAnswers[i]->text() == endDistLine->text()){
            isContains[0][1] = true;
            break;
        }
    }
    int dist = -1;
    int startIt = -1;
    int endIt = -1;
    for(int i = 0; i < tablePoints.size() ;i++){
        if(pList->getPoints()[i]->getName() == startDistLine->text())
            startIt = endIt = pList->getPoints()[i]->myIt;
        if(pList->getPoints()[i]->getName() == endDistLine->text())
            endIt = pList->getPoints()[i]->myIt;
    }    
    if(isContains[0][0]&& isContains[0][1]){
        dist = tablePoints[startIt]->getDistanceTo(endIt);
    }

    answerLine->setText(QString::number(dist));
}

void FirstTask::mousePressEvent (QMouseEvent* event){
    if(modes[0]){
        createPoint(cursor().pos() - mapToGlobal(pList->pos()));
    }
    if(event->buttons() == Qt::LeftButton){
        mouseDown0 = true;
    }
}

void FirstTask::createPoint(QPoint position){
    if(lastTitlePoint > maxPoints)
        return;
    QLineEdit* pointEdit = new QLineEdit(pList);
    QPointDrawing* newPoint = new QPointDrawing(position, pointEdit, lastTitlePoint - 1);
    pList->addPoint(newPoint);
    QString lastStr = QString::number(lastTitlePoint);

    QLabel* newPointlblHor = new QLabel("П" + lastStr, table);
    QLabel* newPointlblVer = new QLabel("П" + lastStr, table);
    newPointlblHor->move(lastPos.x() + 35, newPointlblHor->y() + 5);
    newPointlblVer->move( 5, newPointlblHor->y() + lastPos.y() + 35);

    pointEdit->setText(lastStr);
    pointEdit->move(newPoint->x() * 1.05f, newPoint->y() * 1.05f);
    pointEdit->setMaxLength(1);
    pointEdit->resize(12,18);
    pointEdit->show();
    connect(pointEdit, SIGNAL(textChanged(const QString)), SLOT(updateEdits()));

    PointTable* newPt = new PointTable(newPointlblHor, newPointlblVer);

    for(int i = 0; i < lastTitlePoint; i++){
        TableLineEdit* tableEdit = new TableLineEdit(table, lastTitlePoint - i, lastTitlePoint);
        if(i == 0){
            tableEdit->setReadOnly(true);
            tableEdit->setAutoFillBackground(true);
            tableEdit->setStyleSheet("background-color: red");
        }
        tableEdit->move(newPointlblHor->x() - 35 * i, newPointlblVer->y());
        connect(tableEdit, SIGNAL(textEdited(const QString)),
                SLOT(changeTableValue(const QString)));
        newPt->addLineEdit(tableEdit);
    }
    for(int i = 1; i < lastTitlePoint; i++){
        TableLineEdit* tableEdit = new TableLineEdit(table, lastTitlePoint, lastTitlePoint - i);
        tableEdit->move(newPointlblHor->x()  , newPointlblVer->y() - 40 * i);
        connect(tableEdit, SIGNAL(textEdited(const QString)),
                SLOT(changeTableValue(const QString)));
        newPt->addLineEdit(tableEdit);
    }

    tablePoints.append(newPt);

    newPointlblHor->show();
    newPointlblVer->show();

    lastPos = QPoint(newPointlblHor->x(), newPointlblVer->y());

    lastTitlePoint++;
    updateEdits();
}

void FirstTask::setPaintMode(){
        modes[0] = !modes[0];
        disableModes(0);
}

void FirstTask::setBindMode(){
    modes[1] = !modes[1];
    disableModes(1);
}

void FirstTask::setDeleteMode(){
        modes[2] = !modes[2];
        disableModes(2);
}

void FirstTask::updateEvent(){
    if(modes[1] || modes[2]){
        unsigned short nearestId = 0;
        bool isFound = false;
        auto drawPoints = pList->getPoints();
        for(int i = 0; i< drawPoints.size(); i++){
            unsigned short dx = 0, dy = 0;

            dx = cursor().pos().x() - mapToGlobal(*drawPoints[i]).x() - 95;
            dy = cursor().pos().y() - mapToGlobal(*drawPoints[i]).y() - 40;

            if(dx < minDeleteDistance && dy < minDeleteDistance){
                if(drawPoints.size() > 1){
                    if(drawPoints[nearestId]->x() > dx && drawPoints[nearestId]->y() > dy)
                        nearestId = i;
                }
                else
                    nearestId = i;

                isFound = true;
            }
        }
        pList->setItCircle(isFound ? nearestId : 255);
    }

    if(pList->getItCircle() != 255){
        unsigned char curPoint = pList->getItCircle();
        if(mouseDown0){
            if (modes[1]){// binding points
                if(firstSelectedPoint == 255)//если 1 точку ещё не назначена
                    firstSelectedPoint = curPoint;
                else if(secondSelectedPoint == 255){ // если 2 точка ещё не назначена
                    secondSelectedPoint = curPoint;

                    if(secondSelectedPoint == firstSelectedPoint){//если назначаемые точки эквивалентны
                        secondSelectedPoint = 255;
                        return;
                    }
                    pList->bind2Points(firstSelectedPoint, secondSelectedPoint);// строим линию

                    //сбрасываем точки
                    firstSelectedPoint = 255;
                    secondSelectedPoint = 255;
                    updateEdits();//пересчитываем ответы
                }
            }//delete point
            else if(modes[2]){
                pList->deletePoint(curPoint);

                delete tablePoints[curPoint];
                tablePoints.removeAt(curPoint);                

                lastTitlePoint--;
                lastPos = QPoint(lastPos.x() - 35, lastPos.y() - 40);
                updateEdits();
            }            
        }
    }

    pList->repaint();
    mouseDown0 = false;
}

void FirstTask::disableModes(unsigned char curMode){
    for(unsigned long long i = 0; i < sizeof(modes) / sizeof (modes[0]); i++){
        modes[i] = i == curMode? modes[i] : false;// итератор попал на текущий режим? Если нет, то выключить. Иначе оставить без внимания.
    }

    for(unsigned long long i = 0; i < sizeof(modeBtns) / sizeof(modeBtns[0]); i++){
        modeBtns[i]->setStyleSheet(modes[i] ? "background-color : MediumSeaGreen;" : "background-color : LightCyan;");
    }
}

void FirstTask::findMinPoint(){
    for(int j = 0; j < tablePoints.size(); j++){//проходимся по всем столбцам
        for(int i = 0; i < listP.size(); i++){//проходимся по всем точкам
            if(tablePoints[j]->getBindingsCount() != listP[i]->getBindingsCount())//если кол-во соед. в столбце не равно кол-ву соед. точки
                continue;//пропускаем
            if(!(listP[i]->getBindingsCount() < minValue))//определяем самую мало-соед. точку
                continue;
            minValue = listP[i]->getBindingsCount();
            minPointIt = i;
        }
    }
    changeAnswer();
}
void FirstTask::changeAnswer(){
    if(minPointIt < maxPoints + 1){//если мин. точка нашлась
        tableAnswers[minPointIt]->setText(listP[minPointIt]->getName());//записываем в ответ имя точки
        bool isFound = false;        
        for(int i = 0; i < listP.size(); i++){//проходимся по всем точкам
            if(delPoints.contains(i - 1)|| i == minPointIt)
                continue;
            if(listP[i]->isConnectedTo(minPointIt)&& !connectors.contains(listP[i]->getName())){
                if(isFound){
                    if(!connectors.contains(listP[i]->getName())){
                        connectors.append(listP[i]->getName());
                     //   qDebug()<<"new connector"<<listP[i]->getName();
                    }
                    continue;
                }

                //qDebug()<<"was connect" << listP[i]->getName();//та точка, которая приклеена к наименьшей
                delPoints.append(i + 1);
                tableAnswers[i + 1]->setText(listP[i]->getName());
                isFound = true;
                connectors.append(listP[i]->getName());
                minPointIt = i;

            }
        }
    }
}

void FirstTask::updateEdits(){//главный алгоритм  
    listP = pList->getPoints();
    minValue = 100;
    minPointIt = 100;
    delPoints.clear();
    connectors.clear();//массив для тех точек, которые находятся позже, чем первая, и если начальная имеет более 1 соед.

    //for(int i = 0; i < listP.size(); i++){
    //    findMinPoint();
  //  }
     findMinPoint();
      findMinPoint();
    //   findMinPoint();

    for(int j = 0; j < tablePoints.size(); j++){//проходимся по всем столбцам
        QString names = "N/A";

        if(delPoints.contains(j))
            continue;

        for(int i = 0; i < listP.size(); i++){//проходимся по всем точкам
            if(tablePoints[j]->getBindingsCount() != listP[i]->getBindingsCount())//если кол-во соед. в столбце неравно кол-ву соед. точки
                continue;

            names = (names.left(3) != "N/A" ? names + "||" : "") + listP[i]->getName();
        }
        tableAnswers[j]->setText(names);//записываем в ответ имя точки
    }
}


void FirstTask::changeTableValue(const QString value){//добавление или удаление соед. точек в таблице
    TableLineEdit* sendEdit = static_cast<TableLineEdit*>(sender());//преобразование отправителя

    tablePoints[sendEdit->myItPoint - 1]->bind(value.toInt(), sendEdit->myLine - 1); // соед. табличную точку
    updateEdits();// сигнал для пересчёта ответов
}
