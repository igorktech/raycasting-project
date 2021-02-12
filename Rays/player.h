#ifndef PLAYER_H
#define PLAYER_H
#include <QWidget>
#include <QVector>
#include <QColor>
#include <QSize>
#include <QEvent>
#include <QPointF>
#include <QPainter>
#include "map.h"
#include <QtMath>
#include <QLineF>
#include <QTime>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define RaySize 2560
class Player
{
    qreal m_dX= 0;
    qreal m_dY= 0;
    qreal m_step = 0;
    qreal m_dAngle = 0;
    qreal m_angle = 0;
    QPointF m_playerPos;
    QLineF m_Lines[RaySize];
    QRectF m_Rects[RaySize];
    QBrush m_Brush[RaySize];
    QTime watch;
public:
    Player();
    void updatePlayer(QVector<QVector<int>> map);
    void paintPlayer(QPainter & painter);
    void setPlayerPos(QPointF playerPos);
    QPointF playerPos();
    qreal dX();
    qreal dY();
    qreal angle();
    qreal step();
    qreal dAngle();
    QLineF* lines();
    QRectF* rects();
    QBrush* brush();
    void setPlayerX(qreal x);
    void setPlayerY(qreal y);
    void setAngle(qreal angle);
    void setDX(qreal dx);
    void setDY(qreal dy);
    void setLine(QLineF line , int i);
    void setBrush(QBrush brush , int i);
    void setRect(QRectF rect , int i);
    void setStep(qreal step);
    void setDAngle(qreal dangle);
};

#endif // PLAYER_H
