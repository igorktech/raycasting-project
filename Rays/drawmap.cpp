#include "drawmap.h"

DrawMap::DrawMap(QWidget *parent) : QWidget(parent)
{
    mp = new Map() ;
    interval = startTimer(30);
}

void  DrawMap::paintEvent(QPaintEvent* event){
    QPainter painter(this);
     if(show){
     // если карта не скрыта-выводим карту, игрока, лучи
     mp->paintMap(painter);

     }
}

DrawMap::~DrawMap(){
    delete mp;
}

    // если кнопка нажата- устанавливаем дельту
void DrawMap::keyPressEvent(QKeyEvent*event)
{

    if (event->key() == Qt::Key_Right ){
        mp->player()->setDAngle(1 * M_PI);
    }
    if (event->key() == Qt::Key_Left){
       mp->player()->setDAngle(-1 * M_PI);
    }
    if (event->key() == Qt::Key_Up){
        mp->player()->setStep(10.5);
    }
    if (event->key() == Qt::Key_Down){
        mp->player()->setStep(-4.5);
    }

}
    // при отжатии, если дельта соответствует нажатой кнопке- изменяем ее на ноль, если нет- оставляем прежней
void DrawMap::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left){
        (mp->player()->dAngle() < 0) ? mp->player()->setDAngle(0): mp->player()->setDAngle(mp->player()->dAngle());
    }
    if (event->key() == Qt::Key_Right){
         (mp->player()->dAngle() > 0) ? mp->player()->setDAngle(0) : mp->player()->setDAngle(mp->player()->dAngle());
    }
    if (event->key() == Qt::Key_Up){
        (mp->player()->step() > 0) ? mp->player()->setStep(0): mp->player()->setStep(mp->player()->step());
    }
    if (event->key() == Qt::Key_Down){
        (mp->player()->step() < 0) ? mp->player()->setStep(0): mp->player()->setStep(mp->player()->step());
    }
}

    // по событию таймера изменяем положение игрока
    //выводим
void DrawMap::timerEvent(QTimerEvent*) {
    //изменение положения игрока
    mp->player()->updatePlayer(mp->pMap());
    //рассчет лучей
    mp->Rays();
    //подсчет количества кадров в секунду
    showFps();
    // посылаем сигнал DrawGame для вывода изображения
    emit sendRepaint();
    if(show){
        //если карта открыта, изображаем ее
        repaint();
    }
}
    //подсчет FPS
void DrawMap::showFps() {
    static QTime frameTick;
    static int totalFrame = 0;
    if (!(totalFrame & 31)) {
        int elapsed = frameTick.elapsed();
        frameTick.start();
        int fps = 32 * 1000 / (1 + elapsed);
        emit sendFps(QString("%1 FPS | player position on map: x=%2, y=%3").arg(fps).arg(mp->player()->playerPos().x()).arg(mp->player()->playerPos().y()));
    }
    totalFrame++;
}
