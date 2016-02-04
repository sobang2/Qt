#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QtSerialPort>
#include <QDebug>
#include <QThread>
#include <QSerialPort>
#include <QtGlobal>
#include <iostream>
#include <QPainter>
#include "qscale.h"
#include "manometer.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    ~Widget();
protected:
    void setValue(int value);
    void paintEvent(QPaintEvent *event);
private slots:
    void timeupdate();

private:
    Ui::Widget *ui;
    QScale *qscale1;
    QScale *qscale2;
    QScale *qscale3;
    ManoMeter *ATCSpeed;
    ManoMeter *RSDSpeed;
    QString str;
    QDateTime *local;
    QDateTime *UTC;
};

#endif // WIDGET_H
