#include <memory>
#include <exception>
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QStringList>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QSettings>
#include <qt5/poppler-qt5.h>
#include "MainWindow.hpp"
#include "GlobalData.hpp"
#include "Utils.hpp"

GlobalData g;
QSettings settings("_0x17de", "VeniVidiMove");


void addMenus(QMainWindow& window) {
    QMenu* fileMenu = window.menuBar()->addMenu("&File");
    QAction* inputAction = fileMenu->addAction("Set &Input Directory");
    //QAction* logPathAction = fileMenu->addAction("Set &Log Directory");
    fileMenu->addSeparator();
    QAction* quitAction = fileMenu->addAction("&Quit");

    inputAction->connect(inputAction, &QAction::triggered, []{
            QFileDialog dialog;
            dialog.setAcceptMode(QFileDialog::AcceptOpen);
            dialog.setFileMode(QFileDialog::Directory);
            dialog.setOption(QFileDialog::ShowDirsOnly);
            if (dialog.exec()) {
                QStringList results = dialog.selectedFiles();
                if (results.count() == 1) {
                    QString inputPath = results[0];
                    changeInputPath(inputPath);
                    settings.setValue("inputPath", inputPath);
                }
            }
        });
    quitAction->connect(quitAction, &QAction::triggered, []{ QCoreApplication::quit(); });
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.setWindowTitle("VeniVidiMove");
    mainWindow.resize(400, 600);
    QWidget* central = new QWidget(&mainWindow);
    mainWindow.setCentralWidget(central);

    addMenus(mainWindow);

    QVBoxLayout* vbox = new QVBoxLayout(central);

    g.scene = new QGraphicsScene(central);
    QGraphicsView* view = new QGraphicsView(g.scene, central);
    vbox->addWidget(view);

    changeInputPath(settings.value("inputPath", "test").toString());
    //changeLogPath(settings.value("logPath", "").toString());

    central->setLayout(vbox);
    mainWindow.show();

    return app.exec();
}
