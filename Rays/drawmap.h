#ifndef DRAWMAP_H
#define DRAWMAP_H

#include <QWidget>
#include <map.h>
#include <QEvent>
#include <QDebug>
#include <QFileDialog>
#include  "QTime"
#include "mainwindow.h"
#include <QEvent>
#include <QKeyEvent>
#include <QImage>
#include <QColor>

class DrawMap : public QWidget
{
    Q_OBJECT
    Map* mp;

    int interval;
    void showFps();
   bool show = 1;
public:
    explicit DrawMap(QWidget *parent = nullptr);
    ~DrawMap();
    Map* mpp(){
        return mp;
    }

signals:
    void sendFps(QString);
 void sendRepaint();
public slots:
 void setHide(){
     show = false;
 }
 void setShow(){
     show = true;
 }
protected:
 //перегруженные методы
 virtual void paintEvent(QPaintEvent* event) override;
    virtual void keyPressEvent(QKeyEvent*) override;
    virtual  void keyReleaseEvent(QKeyEvent *event) override;
     virtual void timerEvent(QTimerEvent*) override;
};

#endif // DRAWMAP_H
