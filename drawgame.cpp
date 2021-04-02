#include "drawgame.h"
#include <QDebug>
DrawGame::DrawGame(QWidget *parent): QWidget(parent)
{

}
void DrawGame::paintEvent(QPaintEvent* event){


    QPainter painter(this);
    painter.save();
    //растягиваем картинку, котору/ выведем на экран
    painter.scale( qreal(this->rect().width())/qreal(viewX),qreal(this->rect().height())/qreal(viewY));
    //добавление эффекта лампочки
    QRadialGradient linearGradient(viewX/2, 0, viewY/2);
    linearGradient.setColorAt(0.0, Qt::white);
    linearGradient.setColorAt(0.3, skyC);
    linearGradient.setColorAt(0.8, Qt::black);
    painter.setBrush((QBrush(linearGradient)));
    painter.drawRect(0,0,viewX,viewY/2);
    //рисуем пол
    painter.fillRect(0,viewY/2,viewX,viewY, floorC); 
    //отображаем стены с тенями
    for(int i = 0; i < viewX; i++){
         if(ptrPl){
             painter.setPen(QPen(QBrush((ptrPl->brush())[i]),1));
             painter.setBrush(ptrPl->brush()[i]);
             painter.drawRect(ptrPl->rects()[i]);
                 }
     }
             painter.restore();
}

DrawGame::~DrawGame(){


}

void DrawGame::setPl(Player* p){
   ptrPl =  p;
}




