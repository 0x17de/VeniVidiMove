#include <memory>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDir>
#include <poppler-qt5.h>
#include "GlobalData.hpp"
#include "Utils.hpp"


QPixmap getPixmap(const QString& absoluteImagePath) {
    std::unique_ptr<Poppler::Document> document(Poppler::Document::load(absoluteImagePath));
    if (document && !document->isLocked()) {
        std::unique_ptr<Poppler::Page> page(document->page(0));
        QImage image = page->renderToImage();
        if (!image.isNull()) {
            return QPixmap::fromImage(image);
        }
    }
    throw std::runtime_error("Could not load pdf");
}

void displayImage() {
    if (g.currentImage) {
        g.scene->removeItem(g.currentImage);
        delete g.currentImage;
        g.currentImage = 0;
    }

    if (g.index >= g.entries.count()) {
        g.currentImage = g.scene->addText("EVERYTHING DONE");
        return;
    }

    g.currentImage = g.scene->addPixmap(getPixmap(g.entries[g.index]));
}

void changeInputPath(const QString& path) {
    QStringList nameFilters;
    nameFilters << "*.pdf";

    QDir inputDir(path);
    inputDir.setNameFilters(nameFilters);

    QStringList newEntries;
    for (QString& s : inputDir.entryList())
         newEntries.append(inputDir.absoluteFilePath(s));
    g.entries.swap(newEntries);
    g.index = 0;

    displayImage();
}
