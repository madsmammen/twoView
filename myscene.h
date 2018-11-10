#ifndef MYSCENE_H
#define MYSCENE_H

#include <QObject>
#include <QGraphicsScene>

class MyScene : public QGraphicsScene {
public:
    MyScene(QObject* parent = 0);
};

#endif // MYSCENE_H
