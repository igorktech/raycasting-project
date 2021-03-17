#ifndef DRAWGAME_H
#define DRAWGAME_H

#include <QWidget>
#include <QResizeEvent>
#include "mainwindow.h"
#include "player.h"

#define  skyC QColor(128,205,242)
#define floorC QColor(51,153,102)
class DrawGame: public QWidget
{
     Q_OBJECT

    Player* ptrPl;
public:
    explicit DrawGame(QWidget *parent = nullptr);
    void setPl(Player* p);
    ~DrawGame();
protected:
 virtual void paintEvent(QPaintEvent* event) override;

};

#endif // DRAWGAME_H
