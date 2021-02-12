#include "drawgame.h"
#include <QDebug>
DrawGame::DrawGame(QWidget *parent): QWidget(parent)
{
    mp = new Map() ;
    mp->setWSize(QWidget::rect());

    pl = new Player();
    pl->setPlayerPos(QPointF(mp->blockSize()+1,mp->blockSize()+1));
//update();

    interval = startTimer(30);
}
void DrawGame::paintEvent(QPaintEvent* event){
    m_width =this->rect().width();
    m_height =this->rect().height();
//qDebug() <<m_width;
    QPainter painter(this);
   emit sendRepaintMap(mp);
    pl->paintPlayer(painter);

    //painter.fillRect(0,m_height/2,m_width,m_height/2,Qt::green);
    //painter.fillRect(0,0,m_width,m_height/2,Qt::white);
    qreal c = 0,x,y, cx, cy;
    qreal fov = M_PI/3.;


    if(updt){
    for (size_t i=0; i<m_width; i++) {
            qreal angle = pl->angle()-fov/2 + fov*i/float(m_width);

           qreal column_height, length;

            for (qreal t=0; t<20; t+=0.05) {
                 cx = pl->playerPos().x() + t*qCos(angle);
                 cy = pl->playerPos().y() + t*qSin(angle);
                if (mp->map(int(cy/mp->blockSize()),int(cx/mp->blockSize()))!=0){

                  column_height = m_height/(t*qCos(angle-pl->angle()));

                    break;
                }
                column_height = m_height/(20*cos(angle-pl->angle()));


            }
            pl->setBrush(QBrush(QColor(255-512/qPow(column_height,0.5),255-512/qPow(column_height,0.5),255-512/qPow(column_height,0.5))),i);
            pl->setRect(QRectF(i,m_height/2-column_height/2,1,column_height),i);
            pl->setLine(QLineF(pl->playerPos(),QPointF(cx,cy)), i);
        }
    }
    painter.setPen(QPen(QBrush(QColor(0,0,150,90)),0.5));
             painter.drawLines(pl->lines(),m_width);
             for(int i = 0; i < m_width; i++){
                 painter.setPen(QPen(QBrush((pl->brush())[i]),1));
                 painter.setBrush(pl->brush()[i]);
                 painter.drawRect((pl->rects())[i]);
             }


}

DrawGame::~DrawGame(){
    delete mp;
    delete pl;
}

void  DrawGame::resizeEvent(QResizeEvent *event){

}
void DrawGame::keyPressEvent(QKeyEvent*event)
{

    updt = 1;
    if (event->key() == Qt::Key_Right ){
        pl->setDAngle(1.3 * M_PI);
    }
    if (event->key() == Qt::Key_Left){
       pl->setDAngle(-1.3 * M_PI);
    }
    if (event->key() == Qt::Key_Up){
        pl->setStep(4.5);
    }
    if (event->key() == Qt::Key_Down){
        pl->setStep(-2.5);
    }

}
void DrawGame::keyReleaseEvent(QKeyEvent *event) {
    updt  = 0;
    if (event->key() == Qt::Key_Left){
        (pl->dAngle() < 0) ? pl->setDAngle(0): pl->setDAngle(pl->dAngle());
    }
    if (event->key() == Qt::Key_Right){
         (pl->dAngle() > 0) ? pl->setDAngle(0) : pl->setDAngle(pl->dAngle());
    }
    if (event->key() == Qt::Key_Up){
        (pl->step() > 0) ? pl->setStep(0): pl->setStep(pl->step());
    }
    if (event->key() == Qt::Key_Down){
        (pl->step() < 0) ? pl->setStep(0): pl->setStep(pl->step());
    }
}

void DrawGame::timerEvent(QTimerEvent*) {
    pl->updatePlayer(mp->pMap());
    showFps();
    repaint();
}

void DrawGame::showFps() {
    static QTime frameTick;
    static int totalFrame = 0;
    if (!(totalFrame & 31)) {
        int elapsed = frameTick.elapsed();
        frameTick.start();
        int fps = 32 * 1000 / (1 + elapsed);
        sendFps(QString("%1 FPS").arg(fps));
    }
    totalFrame++;
}

