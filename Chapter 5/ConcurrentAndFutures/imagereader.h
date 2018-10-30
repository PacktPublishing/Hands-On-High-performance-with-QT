#ifndef IMAGEREADER_H
#define IMAGEREADER_H

#include <QFuture>
#include <QPair>
#include <QtConcurrent/QtConcurrentRun>
#include <QImage>
#include <QLabel>


class ImageReader : public QObject
{
public:
 QFuture<QPair<QImage, int>> read(const QString& fileName, int index)
 {
    auto readImageWorker =
            [](const QString &fileName, int index)
            {
               QImage image;
               image.load(fileName);
               return qMakePair(image, index);
            };

    return QtConcurrent::run(readImageWorker, fileName, index);
 }

 QFuture<QVector<QImage>> read(const QStringList& fileNames)
 {
    auto readImageWorker =
            [](const QStringList& fileNames)
            {
               QVector<QImage> images;
               for(auto& fname : fileNames)
               {
                   images.append(QImage());
                   images.back().load(fname);
               }

               return images;
            };

    return QtConcurrent::run(readImageWorker, fileNames);
 }
};

#endif // IMAGEREADER_H
