#include "mygraphicsview.h"

#include <QWheelEvent>
#include <QScrollBar>
#include <QDebug>

MyGraphicsView::MyGraphicsView(QWidget *parent) : QGraphicsView(parent) {

    setTransformationAnchor(QGraphicsView::AnchorViewCenter); // AnchorViewCenter); // );
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MyGraphicsView::setBackPhoto(QPixmap pix) {
    if (back != NULL) {
        delete back;
    }
    back = new QPixmap(pix);
    double  w = back->width(), h = back->height();
    this->setSceneRect(0, 0, w, h);

    int     margin = 10;
    double  f = 1; // 0.13
    fitInView(QRectF(0, 0, f*w, f*h).marginsAdded(QMargins(margin, margin, margin, margin)), Qt::KeepAspectRatio);
}

void MyGraphicsView::CenterOn(QPointF pos) {
    QPointF target_scene_pos, target_viewport_pos;
    target_viewport_pos = pos;
    target_scene_pos = this->mapToScene(pos.x(), pos.y());

    centerOn(target_scene_pos);
    QPointF delta_viewport_pos = target_viewport_pos - QPointF(viewport()->width() / 2.0,
                                                             viewport()->height() / 2.0);
    QPointF viewport_center = mapFromScene(target_scene_pos) - delta_viewport_pos;
    centerOn(mapToScene(viewport_center.toPoint()));
}


void MyGraphicsView::drawBackground(QPainter *painter, const QRectF &rect) {
    int     margin = 10;

    if (back != NULL) {
        int     h = back->height(), w =back->width();

        painter->drawPixmap(0, 0, *back);
        painter->setOpacity(1.0);
        this->scene()->setSceneRect(QRectF(0, 0, w, h).marginsAdded(QMargins(margin, margin, margin, margin)));
    }
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::MidButton) {
        _pan = true;
        _panPos = event->pos();
    }
    QGraphicsView::mousePressEvent(event);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event) {
    setFocus();
    if (_pan) {
        QPointF pos(event->pos()-_panPos);
        emit panSignal(pos);

        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->pos().x() - _panPos.x()));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->pos().y() - _panPos.y()));
        _panPos = event->pos();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::MidButton) {
        _pan = false;
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void MyGraphicsView::wheelEvent(QWheelEvent *event) {
    double s, scaleFactor = 1.15;

    if(event->delta() > 0) {
        s = scaleFactor;
    } else {
        s = 1.0/scaleFactor;
    }

    scale(s, s);
#if 0
    centerOn(event->pos());
#else
    // CenterOn(mapToScene(event->pos()));
#endif

    emit scaleSignal(s, event->pos());

    event->accept();

    // Don't call superclass handler here
    // as wheel is normally used for moving scrollbars
    // QGraphicsView::wheelEvent(event);
}

void MyGraphicsView::scaleSlot(double s, QPointF pos)  {
    int     w = this->width(), h = this->height();

    scale(s, s);
    // CenterOn(pos);
}

void MyGraphicsView::panSlot(QPointF pos) {
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() - pos.x());
    verticalScrollBar()->setValue(verticalScrollBar()->value() - pos.y());
}

void MyGraphicsView::wheelSlot(QWheelEvent *event) {
    // setFocus();
    wheelEvent(event);
}
