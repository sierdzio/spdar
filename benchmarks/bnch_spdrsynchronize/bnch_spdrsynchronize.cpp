#include "spdrglobal.h"
#include "SpdrSynchronize"

#include <QObject>
#include <QDebug>
#include <QTest>
#include <QFile>
#include <QDir>

class BnchSpdrSynchronize : public QObject
{
    Q_OBJECT

private slots:
    void simpleSynchronizationBenchmark_data();
    void simpleSynchronizationBenchmark();

private:
    int createTestFiles(const QString &basePath, bool simplified);
};

void BnchSpdrSynchronize::simpleSynchronizationBenchmark_data()
{
    QTest::addColumn<bool>("simulate");
    QTest::newRow("Simulation enabled") << true;
    QTest::newRow("Simulation disabled") << false;
}

void BnchSpdrSynchronize::simpleSynchronizationBenchmark()
{
    QFETCH(bool, simulate);
    QString testDataPath("testData");
    QDir(testDataPath).removeRecursively();

    QString testInputPath(testDataPath + QLatin1String("/input"));
    QString testOutputPath(testDataPath + QLatin1String("/output"));

    createTestFiles(testDataPath, false);

    SpdrSynchronize testObject;
    testObject.setLogLevel(Spdr::Error);
    testObject.setOptions(SpdrSynchronize::RemoveMissingFiles
                          | SpdrSynchronize::RemoveEmptyDirectories);
    testObject.setInputPath(testInputPath);
    testObject.setOutputPath(testOutputPath);

    testObject.setSimulate(simulate);

    QBENCHMARK {
        testObject.synchronize();
    }

    QDir(testDataPath).removeRecursively();
}

int BnchSpdrSynchronize::createTestFiles(const QString &basePath, bool simplified)
{
    QString inputPath(basePath + "/input");
    QString outputPath(basePath + "/output");
    QDir().mkpath(inputPath);
    QDir().mkpath(outputPath);

    if (!simplified) {
        QDir().mkdir(outputPath + "/emptyDir1");
        QDir().mkdir(outputPath + "/emptyDir2");
    }

    int numberOfFiles = 150;

    for (int i = 0; i < numberOfFiles; i++) {
        QString filename(QString("file%1.txt").arg(QString::number(i)));
        QString inputFilePath = inputPath + "/" + filename;

        QFile file(inputFilePath);

        if (!file.open(QFile::Text | QFile::WriteOnly)) {
            continue;
        }

        QString fileContent("Content of file number: ");
        fileContent += QString::number(i);
        fileContent += ". Random data: ";
        fileContent += QString::number(qrand());
        file.write(fileContent.toUtf8());
        file.close();

        if (i != 0) {
            if ((!simplified) && ((i == 1) || (i == 2))) {
                if (i == 1) {
                    // Moved file
                    QDir().mkpath(inputPath + "/moved");
                    QFile::copy(inputFilePath, outputPath + "/" + filename);
                    QFile::rename(inputFilePath, inputPath + "/moved/renamedFile1.txt");
                } else if (i == 2) {
                    // Missing file
                    QFile::copy(inputFilePath, outputPath + "/" + filename);
                    QFile::remove(inputFilePath);
                }
            } else {
                QFile::copy(inputFilePath, outputPath + "/" + filename);
            }
        }
    }

    return numberOfFiles;
}

QTEST_MAIN(BnchSpdrSynchronize)
#include "bnch_spdrsynchronize.moc"

