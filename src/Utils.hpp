#ifndef UTILS_H
#define UTILS_H

#include <QPixmap>


QPixmap getPixmap(const QString& absoluteImagePath);
void displayImage();
void changeInputPath(const QString& path);

#endif
