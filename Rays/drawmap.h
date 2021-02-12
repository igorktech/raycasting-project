#ifndef DRAWMAP_H
#define DRAWMAP_H

#include <QWidget>
#include <map.h>
class DrawMap : public QWidget
{
    Q_OBJECT
    Map* mp;

public:
    explicit DrawMap(QWidget *parent = nullptr);

signals:
public slots:
    void rePaint(Map* map);
protected:
 virtual void paintEvent(QPaintEvent* event) override;
};

#endif // DRAWMAP_H
