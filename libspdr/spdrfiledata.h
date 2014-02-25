#ifndef SPDRFILEDATA_H
#define SPDRFILEDATA_H

#include <QByteArray>
#include <QString>
#include <QDateTime>

class SpdrLog;

class SpdrFileData
{
public:
    SpdrFileData(const QString &filePath, const QString &relativePathBase,
                 bool deepSearch = false, const SpdrLog *logger = 0);

    bool isValid;
    QString name;
    QString path;
    QString absoluteFilePath;
    QByteArray checksumMd5;
    QByteArray checksumSha;
    QDateTime creationDate;
    qint64 size;

    bool operator ==(const SpdrFileData &other) const;
    bool isEqual(const SpdrFileData &other) const;
    bool isMoved(const SpdrFileData &other) const;
    bool readFileData(const QString &filePath, const QString &relativePathBase,
                      bool deepSearch = false, const SpdrLog *logger = 0);
    QString toString() const;
};

#endif // SPDRFILEDATA_H
