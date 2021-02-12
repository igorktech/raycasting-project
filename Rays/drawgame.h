#ifndef DRAWGAME_H
#define DRAWGAME_H

#include <QWidget>
#include "map.h"
#include <QResizeEvent>
#include "player.h"
#include  "QTime"
#include "mainwindow.h"
#include <QImage>
class DrawGame: public QWidget
{
     Q_OBJECT

    Map* mp;
    Player* pl;
    int interval;
    int m_width;
    int m_height;
    QImage image;
    void showFps();
    bool updt = 0;
public:

    explicit DrawGame(QWidget *parent = nullptr);

    ~DrawGame();
protected:
 virtual void paintEvent(QPaintEvent* event) override;
 virtual void  resizeEvent(QResizeEvent *event) override;
 virtual void keyPressEvent(QKeyEvent*event) override;
 virtual  void keyReleaseEvent(QKeyEvent *event) override;
 virtual void timerEvent(QTimerEvent*) override;
signals:
 void sendFps(QString);
 void sendRepaintMap(Map*);

};

#endif // DRAWGAME_H
