#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QStringList>
class QGraphicsScene;
class QGraphicsItem;

struct GlobalData {
    QGraphicsScene* scene;
    QGraphicsItem* currentImage = 0;
    //QString logPath;
    QStringList entries;
    long index = 0;
};
extern GlobalData g;

#endif
