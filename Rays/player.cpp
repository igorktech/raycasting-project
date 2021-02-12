#include "player.h"
#include <QDebug>

Player::Player()
{

   //m_dX = (qCos(angle())*2);
   //m_dY = (qSin(angle())*2);
   watch.start();
}
void Player::paintPlayer(QPainter & painter){
    painter.setBrush(QBrush(Qt::cyan));
    painter.drawEllipse(m_playerPos,2,2);
    //painter.setPen();
    painter.setPen(QPen(QBrush(Qt::cyan),2));



}

void Player::setPlayerPos(QPointF Pos){
    m_playerPos = Pos;
}
QPointF Player::playerPos() {
    return m_playerPos;
}

qreal Player::dX(){
    return m_dX;
}
qreal Player::dY(){
    return m_dY;
}

void Player::setPlayerX(qreal x){
    m_playerPos.setX(x);
}
void Player::setPlayerY(qreal y){
    m_playerPos.setY(y);
}
qreal Player::angle(){
    return m_angle;
}
void Player::setAngle(qreal angle){
    m_angle = angle;
}
void Player::setDX(qreal dx){
    m_dX = dx;
}
void Player::setDY(qreal dy){
    m_dY = dy;
}
QLineF* Player::lines(){
    return m_Lines;
}
void Player::setLine(QLineF line , int i){
    m_Lines[i] = line;
}
QRectF* Player::rects(){
    return m_Rects;
}
void Player::setBrush(QBrush brush , int i){
    m_Brush[i] = brush;
}

QBrush* Player::brush(){
    return m_Brush;
}
void Player::setRect(QRectF rect , int i){
    m_Rects[i] = rect;
}
void Player::setStep(qreal step){
    m_step = step;
}
qreal Player::step(){
    return m_step;
}
void Player::setDAngle(qreal dangle){
    m_dAngle = dangle;
}
qreal Player::dAngle(){
    return m_dAngle;
}
void Player::updatePlayer(QVector<QVector<int>> map){
    int interval = qMax(20, qMin(watch.elapsed(), 250));
    //qDebug()<<interval;
    //qDebug()<< watch.elapsed();

    watch.start();
    m_angle += m_dAngle * interval / 1000;
     qreal step = m_step * interval / 1000;
    qreal dx = cos(m_angle) * step;
    qreal dy = sin(m_angle) * step;
    QPointF pos = m_playerPos + 2 * QPointF(dx, dy);

    if (map[(int)(pos.y()/8)][(int)(pos.x()/8)] == 0)
        m_playerPos = m_playerPos + QPointF(dx, dy);
}
