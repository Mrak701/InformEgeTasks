#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtWidgets>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private:
    QVBoxLayout* mainQvb;
    QWidget* form;
private slots:
    void startTest();
};
#endif // MAINWIDGET_H
