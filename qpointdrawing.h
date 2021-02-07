#ifndef QPOINTDRAWING_H
#define QPOINTDRAWING_H
#include <QObject>
#include <QPoint>
#include <QLineEdit>

struct QPoint2{
    QPoint* first, *second;
    QPoint2(QPoint* f, QPoint *s){
        this->first = f;
        this->second = s;
    }
};

class QPointDrawing : public QObject, public QPoint{
    Q_OBJECT
public slots:
    void setName(const QString n);

private:
    QString name;
    QLineEdit* nameEdit;
    QPointDrawing* bindings[8];    
public:
    unsigned char myIt = 100;
    QPointDrawing(const QPoint pos, QLineEdit* nmEdit, unsigned char it);
    void bind(QPointDrawing *p, unsigned char itPoint);
    unsigned char getBindingsCount();

    QString getName();
    bool isConnectedTo(unsigned char it);    
    ~QPointDrawing();
};
#endif // QPOINTDRAWING_H
