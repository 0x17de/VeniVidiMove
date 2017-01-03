#include <QKeyEvent>
#include <QFileInfo>
#include <QFile>
#include <QFileDialog>
#include "MainWindow.hpp"
#include "GlobalData.hpp"
#include "Utils.hpp"


void MainWindow::keyPressEvent(QKeyEvent* event) {
    auto key = event->key();
    if (key == Qt::Key_Space) {
        event->accept();
        ++g.index;
        if (g.index > g.entries.count())
            g.index = g.entries.count(); // one after last;
        displayImage();
    } else if (key == Qt::Key_Backspace) {
        event->accept();
        --g.index;
        if (g.index < 0)
            g.index = 0;
        displayImage();
    } else if (key == Qt::Key_Return) {
        event->accept();
        if (g.index >= 0 && g.index < g.entries.count()) {
            QString source = g.entries[g.index];
            QFileInfo info(source);
            QFileDialog dialog;
            dialog.setDefaultSuffix(info.suffix());
            dialog.setAcceptMode(QFileDialog::AcceptSave);

            if (dialog.exec()) {
                QStringList results = dialog.selectedFiles();
                if (results.count() != 1)
                    throw std::runtime_error("Exactly one item must be selected");
                QString path = results[0];
                if (path == g.entries[g.index]) {
                    ++g.index;
                    displayImage();
                    return;
                }

                if (QFile::exists(path) && !QFile::remove(path))
                    throw std::runtime_error("Could not overwrite file");
                if (!QFile::copy(source, path))
                    throw std::runtime_error("Could not copy file");
                if (!QFile::remove(source))
                    throw std::runtime_error("Could not remove old file");
                g.entries[g.index] = path; // update path

                ++g.index;
                displayImage();
            }
        }
    }

}
