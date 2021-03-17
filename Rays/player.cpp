#include "player.h"

Player::Player()
{
    v_lines = QVector<QLineF>(viewX);
     v_rects = QVector<QRectF>(viewX);
    v_brush = QVector<QBrush>(viewX);
   watch.start();
}
    //рисуем игрока и лучи
void Player::paintPlayer(QPainter & painter){
    painter.setBrush(QBrush(Qt::cyan));
    painter.drawEllipse(m_playerPos,2,2);
    painter.setPen(QPen(QBrush(Qt::cyan),2));
    painter.setPen(QPen(QBrush(QColor(0,0,150,90)),0.5));
    painter.drawLines(lines());


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
QVector<QLineF>& Player::lines(){
    return v_lines;
}
void Player::setLine(QLineF line , int i){
    v_lines[i] = line;
}
QVector<QRectF>& Player::rects(){
    return v_rects;
}
void Player::setBrush(QBrush brush , int i){
    v_brush[i] = brush;
}

QVector<QBrush>& Player::brush(){
    return v_brush;
}
void Player::setRect(QRectF rect , int i){
    v_rects[i] = rect;
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
    //изменение позиции игрока на поле в зависимости от скорости обновления изображения
void Player::updatePlayer(QVector<QVector<int>> map){
    int interval = qMax(20, qMin(watch.elapsed(), 250));
    watch.start();
    m_angle += m_dAngle * interval / 1000;
     qreal step = m_step * interval / 1000;
    qreal dx = cos(m_angle) * step;
    qreal dy = sin(m_angle) * step;
    QPointF pos = m_playerPos + 2 * QPointF(dx, dy);

    if (map[(int)(pos.y()/8)][(int)(pos.x()/8)] == 0)
        m_playerPos = m_playerPos + QPointF(dx, dy);
}

qreal Player::lineLength(int i){
   return v_lines[i].length();
}
