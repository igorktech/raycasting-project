#include "drawmap.h"

DrawMap::DrawMap(QWidget *parent) : QWidget(parent)
{

}

void DrawMap::rePaint(Map* map){
    mp = map;
    update();
}
void  DrawMap::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    mp->paintMap(painter);
}
