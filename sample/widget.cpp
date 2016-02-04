#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QString>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include<QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <iostream>
using namespace std;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPixmap trainimage("/home/junsik/qt_workspace/sample/ucpAKPk.png");
    int w = ui->trainImage->width();
    int h  = ui->trainImage->height();
    ui->trainImage->setPixmap(trainimage.scaled(w*2,h,Qt::KeepAspectRatioByExpanding));
//    ui->subjectLabel->setStyleSheet("QLabel{ font: 20pt;}");

    ui->messageLabel->setStyleSheet("QLabel{background-color : skyblue; color : white}");
    ATCSpeed = new ManoMeter(ui->ATCspeedWidget);
    RSDSpeed = new ManoMeter(ui->RSDSpeedWidget);
    ATCSpeed->setValueFont(font());
    RSDSpeed->setValueFont(font());
    ATCSpeed->resize(ui->ATCspeedWidget->width(),ui->ATCspeedWidget->height());
    RSDSpeed->resize(ui->RSDSpeedWidget->width(),ui->RSDSpeedWidget->height());
    ATCSpeed->m_speedname = "ATC Speed";
    RSDSpeed->m_speedname = "RSD Speed";
    ATCSpeed->setNiddleColor("pink");
    RSDSpeed->setNiddleColor("darkgreen");
    ui->blueBlock->setStyleSheet("QLabel {background-color : blue;}");
    ui->whiteBlock->setStyleSheet("QLabel {background-color : white;}");
    ui->yelloBlock->setStyleSheet("QLabel {background-color : yellow;}");
    ui->redBlock->setStyleSheet("QLabel {background-color : red;}");

    ui->m_trainspeed->setStyleSheet("color: rgb(0,255,0); border: 1px solid #FFFFFF; font: 38pt;");
    ui->m_trollyvolt->setStyleSheet("color: rgb(255,0,0); border: 1px solid #FFFFFF; font: 38pt;");

    ui->m_trainspeed->setText("0");
    ui->m_trollyvolt->setText("0");
    str = "1000";
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeupdate()));
    timer->start(1000);
    update();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setValue(int value)
{
}
void Widget::timeupdate(){
    QString tmp_str;
    local = new QDateTime(QDateTime::currentDateTime());
    tmp_str = local->toString("yyyy-MM-dd\nhh:mm:ss");
    ui->timeLabel->setText(tmp_str.toUtf8().constData());
}


void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter;
    QPainterPath path;
    QPen pen(Qt::darkGray);
    painter.begin(this);
    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setBrush(Qt::darkGray);
    painter.drawRect(ui->crossBlock->x(),ui->crossBlock->y(),ui->crossBlock->width(),ui->crossBlock->height());
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawLine(ui->crossBlock->x()+1,ui->crossBlock->y()+1,ui->crossBlock->x()+ui->crossBlock->width(),ui->crossBlock->y()+ui->crossBlock->height());
    painter.drawLine(ui->crossBlock->x()+1,ui->crossBlock->y()+ui->crossBlock->height(),ui->crossBlock->x()+ui->crossBlock->width(),ui->crossBlock->y()+1);
    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    int mca_x = ui->mcaImage->x();
    int mca_y = ui->mcaImage->y();
    int mcb_x = ui->mcbImage->x();
    int mcb_y = ui->mcbImage->y();
    int mc_width = ui->mcaImage->width();
    int mc_height = ui->mcaImage->height();
    painter.setBrush(Qt::NoBrush);
//    painter.drawRoundedRect(mca_x,mca_y,mc_width,mc_height,5,5);
//    painter.drawRoundedRect(mcb_x,mcb_y,mc_width,mc_height,5,5);
    painter.drawRect(mca_x,mca_y,mc_width,mc_height);
    painter.drawRect(mcb_x,mcb_y,mc_width,mc_height);
//    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);
    painter.eraseRect(mca_x-5,mca_y-5,mc_width*0.1,mc_height*1.2);
    painter.eraseRect(mcb_x+mc_width*0.9+5,mcb_y-5,mc_width*0.1+2,mc_height*1.2);
    path.moveTo(mca_x+mc_width*0.1,mca_y);
    path.arcTo(QRectF(mca_x+mc_width*0.1-mc_height/2,mca_y,mc_height,mc_height),90,180);
    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    painter.drawPath(path);
    path.moveTo(mcb_x+mc_width*0.8,mcb_y);
    path.arcTo(QRectF(mcb_x+mc_width*0.9-mc_height/2,mcb_y,mc_height,mc_height),90,-180);
    painter.drawPath(path);
    int smallRectWidth =mc_width/6;
    int smallRectHeight= mc_height/4;
    painter.setBrush(Qt::yellow);
    painter.drawRect(mca_x+mc_width*0.3-smallRectWidth,mca_y+smallRectHeight*0.3,smallRectWidth,smallRectHeight);
    painter.drawRect(mca_x+mc_width-smallRectWidth*0.5-smallRectWidth,mca_y+smallRectHeight*0.3,smallRectWidth,smallRectHeight);
    painter.drawRect(mca_x+mc_width*0.3-smallRectWidth,mca_y+mc_height-smallRectHeight*1.3,smallRectWidth,smallRectHeight);
    painter.drawRect(mca_x+mc_width-smallRectWidth*0.5-smallRectWidth,mca_y+mc_height-smallRectHeight*1.3,smallRectWidth,smallRectHeight);
    painter.drawRect(QRectF(mcb_x+smallRectWidth*0.5,mcb_y+smallRectHeight*0.3,smallRectWidth,smallRectHeight));
    painter.drawRect(QRectF(mcb_x+smallRectWidth*0.5,mcb_y+mc_height-smallRectHeight*0.3-smallRectHeight,smallRectWidth,smallRectHeight));
    painter.drawRect(QRectF(mcb_x+mc_width*0.7,mcb_y+smallRectHeight*0.3,smallRectWidth,smallRectHeight));
    painter.drawRect(QRectF(mcb_x+mc_width*0.7,mcb_y+mc_height-smallRectHeight*0.3-smallRectHeight,smallRectWidth,smallRectHeight));
    QSize Size = painter.fontMetrics().size(Qt::TextSingleLine, str);
    painter.setPen(Qt::white);
    painter.drawText(QPointF(mca_x+mc_width/2-Size.width()/2,mca_y+mc_height/2+Size.height()/2),str);
    painter.drawText(QPointF(mcb_x+mc_width/2-Size.width()/2,mcb_y+mc_height/2+Size.height()/2),str);
    painter.end();

}

