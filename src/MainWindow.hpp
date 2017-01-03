#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class MainWindow : public QMainWindow {
protected:
    virtual void keyPressEvent(QKeyEvent* event) override;
};

#endif
