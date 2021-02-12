#include "map.h"

Map::Map()
{

}

void Map::paintMap(QPainter & painter){


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

}

void Map::setWSize(QRect rect){
    widgetSize = rect;
}
uint Map::blockSize(){
    return m_blockSize;
}
