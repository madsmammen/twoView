#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}
class MyScene;

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    MyScene     *scene, *scene1;
    QTimer      resizeTimer;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void    on_actionFit_triggered();
    void    resizeDone();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
