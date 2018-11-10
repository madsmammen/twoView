#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView {
    Q_OBJECT

private:
    QPixmap    *back = NULL;
    bool       _pan = false;       // Panning on/off
    QPointF    _panPos;            // Panning  position

public:
    MyGraphicsView(QWidget* parent = 0);
    void    setBackPhoto(QPixmap pix);

private:
    void    CenterOn(QPointF pos);

protected:
    void    drawBackground(QPainter *painter, const QRectF &rect) override;
    void    mousePressEvent(QMouseEvent *event) override;
    void    mouseMoveEvent(QMouseEvent *event) override;
    void    mouseReleaseEvent(QMouseEvent *event) override;
    void    wheelEvent(QWheelEvent* event) override;

signals:
   void     scaleSignal(double s, QPointF pos);
   void     panSignal(QPointF pos);
   void     wheelSignal(QWheelEvent *event);

public slots:
   void     scaleSlot(double s, QPointF pos);
   void     panSlot(QPointF pos);
   void     wheelSlot(QWheelEvent *event);
};

#endif // MYGRAPHICSVIEW_H
