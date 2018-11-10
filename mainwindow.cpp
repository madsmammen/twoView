#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    scene = new MyScene(this);
    scene1 = new MyScene(this);
    ui->view1->setScene(scene);
    ui->view2->setScene(scene1);

    QString     fileName = ":/Images/House.jpg";
    QPixmap pix = QPixmap(fileName);
    ui->view1->setBackPhoto(pix);
    ui->view2->setBackPhoto(pix);

    connect(ui->view1, SIGNAL(scaleSignal(double, QPointF)), ui->view2, SLOT(scaleSlot(double, QPointF)));
    connect(ui->view1, SIGNAL(panSignal(QPointF)), ui->view2, SLOT(panSlot(QPointF)));
    connect(ui->view2, SIGNAL(scaleSignal(double, QPointF)), ui->view1, SLOT(scaleSlot(double, QPointF)));
    connect(ui->view2, SIGNAL(panSignal(QPointF)), ui->view1, SLOT(panSlot(QPointF)));

    resizeTimer.setSingleShot(true);
    connect( &resizeTimer, SIGNAL(timeout()), SLOT(resizeDone()) );

    resizeTimer.start(200);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionFit_triggered() {
    ui->view1->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    ui->view2->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::resizeDone() {
    on_actionFit_triggered();
}
