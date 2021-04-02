#include "map.h"
Map::Map()
{

    pl = new Player();
    bool flag = 1;
    //случайное задание координат
    while(flag){
        int plX, plY;
        qsrand(QTime::currentTime().msec());
        plX = qrand()%(m_blockSize*mapSize);
        plY = qrand()%(m_blockSize*mapSize);
        if(map(int(plY/m_blockSize),int(plX/m_blockSize))==0){
    pl->setPlayerPos(QPointF(plX,plY));
    flag = 0;
        }
    }

}

void Map::paintMap(QPainter & painter){

    //заполнение карты
    for(int i = 0; i < mapSize; i++){
        for(int j = 0; j < mapSize; j++){
            if(m_map[j][i]==0){
                  painter.fillRect((i)*m_blockSize,(j)*m_blockSize,m_blockSize,m_blockSize,FloorColor);
            }
            else{
                  painter.fillRect((i)*m_blockSize,(j)*m_blockSize,m_blockSize,m_blockSize,WallColor);
            }
        }
    }
     pl->paintPlayer(painter);

}


int Map::blockSize(){
    return m_blockSize;
}
int Map::map(int x, int y){
    return m_map[x][y];
}
QVector<QVector<int>>& Map::pMap(){
    return m_map;
}
void Map::Rays(){

    qreal fov = M_PI/3.;
    qreal rxV = 0,ryV = 0,dx = 0,dy = 0,rxH = 0,ryH = 0;
    int column_height = 0;
     //в зависимости от размеров окна для каждого луча ищем его пересечение со стеной
     for (int i=0; i<viewX; i++) {
     // для угла обзора = 60 градусов вычисляем угол пускаемого луча
             qreal angle = pl->angle()-fov/2 + fov*i/float(viewX);
             qreal dl = 0;
     //ищем пересечение с вертикальной частью препятствия
             if(qCos(angle)<= -0.01){ //y
                rxV =  (int(pl->playerPos().x()/blockSize()))*blockSize()-0.001;
                ryV = (rxV-pl->playerPos().x())*tan(angle)+pl->playerPos().y();
                dx = -blockSize();
                dy = dx*tan(angle);
             }
             else if(qCos(angle)>= 0.01){
                rxV = (int(pl->playerPos().x()/blockSize()))*blockSize()+blockSize();
                ryV = (rxV-pl->playerPos().x())*tan(angle)+pl->playerPos().y();
                dx = blockSize();
                dy = dx*tan(angle);
             }
             // так как cos = 0 при 90 и 270 градусах tg = бесконечности - дообределяем значени дельт по ближайшему значению 1.56 рад
             else{
                 rxV = (int(pl->playerPos().x()/blockSize()))*blockSize()+blockSize();
                 ryV = (rxV-pl->playerPos().x())*tan(1.56)+pl->playerPos().y();
                 dx = blockSize();
                 dy = dx*tan(1.56);
             }
             //увеличиваем длину луча, пока не найдем ближайшее пересечение
             while(dl <mapSize){
                 if((rxV >= blockSize() && rxV <20*blockSize())&&(ryV >= blockSize() && ryV <20*blockSize())){
                 if (map(int(ryV/blockSize()),int(rxV/blockSize()))!=0){
                     break;
                 }
                 else{
                     rxV += dx;
                     ryV += dy;
                     dl++;
                 }
                 }
                 else{
                     break;
                 }
             }

             //ищем пересечение с горизонтальной частью препятствия
             if(qSin(angle)<= -0.01){ //x
                 ryH = (int(pl->playerPos().y()/blockSize()))*blockSize()-0.001;
                 rxH = (ryH-pl->playerPos().y())/tan(angle)+pl->playerPos().x();
                 dy = -blockSize();
                 dx = dy/tan(angle);
             }
             else if(qSin(angle)>= 0.01){

                ryH =  (int(pl->playerPos().y()/blockSize()))*blockSize()+blockSize();
                rxH = (ryH-pl->playerPos().y())/tan(angle)+pl->playerPos().x();
                dy = blockSize();
                dx = dy/tan(angle);

             }
             // аналогично для sin 1/tg не определен при углах = 0  и 180 градусов
             else{ 
                 ryH =  (int(pl->playerPos().y()/blockSize()))*blockSize()+blockSize();
                 rxH = (ryH-pl->playerPos().y())/tan(0.01)+pl->playerPos().x();
                 dy = blockSize();
                 dx = dy/tan(0.01);
             }
             //увеличиваем длину луча, пока не найдем ближайшее пересечение
             while(dl <mapSize){
                 if((rxH >= blockSize() && rxH <20*blockSize())&&(ryH >=blockSize() && ryH <20*blockSize())){
                 if (map(int(ryH/blockSize()),int(rxH/blockSize()))!=0){
                     break;
                 }
                 else{
                     rxH += dx;
                     ryH += dy;
                     dl++;
                 }
                 }
                 else{
                     break;
                 }
             }
             //сравниваем длины
              qSqrt((pl->playerPos().x()-rxH)*(pl->playerPos().x()-rxH)+(pl->playerPos().y()-ryH)*(pl->playerPos().y()-ryH))>
                      qSqrt((pl->playerPos().x()-rxV)*(pl->playerPos().x()-rxV)+(pl->playerPos().y()-ryV)*(pl->playerPos().y()-ryV)) ?
                         pl->setLine(QLineF(pl->playerPos().x(),pl->playerPos().y(),rxV,ryV), i) :
                         pl->setLine(QLineF(pl->playerPos().x(),pl->playerPos().y(),rxH,ryH), i);
              // если угол определен- корректирыем рыбий глаз
              if(((qSin(angle)< -0.01) || (qSin(angle)> 0.01)) && ((qCos(angle)< -0.01) || (qCos(angle)> 0.01))){
              column_height = viewY*blockSize()/(pl->lineLength(i)*qCos(angle-pl->angle()));
              }
              // иначе берем предыдущую высоту стены
              else{
              }
              //если высота стены больше размера виджета- изменяем ее на длину виджета
              if(column_height > viewY){
                column_height = viewY;
              }
              // в зависимости от длины вычисляем тень
             pl->setBrush(QBrush(QColor(255-512/qPow(column_height,0.5),255-512*2/qPow(column_height,0.5),255-512*2/qPow(column_height,0.5))),i); 
             pl->setRect(QRectF(i,viewY/2-column_height/2,0.1,column_height),i);
         }
}
Map::~Map(){
        delete pl;
}
