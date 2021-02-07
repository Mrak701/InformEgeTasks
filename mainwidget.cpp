#include "mainwidget.h"
#include "firsttask.h"
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    mainQvb = new QVBoxLayout();
    QWidget* form  = new QWidget(this);
    setFixedSize(960, 540);
    form->setFixedSize(size());
    QWidget* btns = new QWidget(form);
    QHBoxLayout* btnsLayout = new QHBoxLayout;


    QLabel* hellowlbl = new QLabel(tr("Сдай ЕГЭ по информатике \n 2021"));
    QPushButton* startBtn = new QPushButton("Старт");
    QPushButton* quitBtn = new QPushButton("Выход");
    QFont font = hellowlbl->font();
    font.setPixelSize(25);
    hellowlbl->setAlignment(Qt::AlignCenter);

    hellowlbl->setFont(font);
    mainQvb->addWidget(hellowlbl);
    mainQvb->addWidget(btns);
    btnsLayout->addWidget(startBtn);
    btnsLayout->addWidget(quitBtn);



    form->setLayout(mainQvb);
    btns->setLayout(btnsLayout);

    connect(startBtn, SIGNAL(clicked()),SLOT(startTest()));
    connect(quitBtn, SIGNAL(clicked()),qApp,SLOT(quit()));
}

MainWidget::~MainWidget()
{
}
void MainWidget::startTest(){
   FirstTask* ft = new FirstTask();
   ft->show();
   ft->setFixedSize(size());
   ft->move(pos());
   hide();
}

