#include "spdrglobal.h"
#include "SpdrSynchronize"

#include <QList>
#include <QVariant>
#include <QObject>
#include <QDebug>
#include <QTest>
#include <QSignalSpy>
#include <QDir>
#include <QFile>

class TstSpdrSynchronize : public QObject
{
    Q_OBJECT

private slots:
    void testDefaults();
    void testSetters();
    void testSignals();
    void testSimpleSynchronization();
    void testAdvancedSynchronization();

private:
    int createTestFiles(const QString &basePath, bool simplified);
};

void TstSpdrSynchronize::testDefaults()
{
    SpdrSynchronize testObject;
    QCOMPARE(testObject.options(), SpdrSynchronize::None);
    QCOMPARE(testObject.split(), 0);
}

void TstSpdrSynchronize::testSetters()
{
    SpdrSynchronize testObject;
    SpdrSynchronize::SynchronizationOptions options = SpdrSynchronize::Cache
            | SpdrSynchronize::DeepSearch;

    testObject.setOptions(options);
    QCOMPARE(testObject.options(), options);

    int propertyTestValue = 8;
    testObject.setSplit(propertyTestValue);
    QCOMPARE(testObject.split(), propertyTestValue);

    propertyTestValue = 3;
    testObject.setProperty("split", propertyTestValue);
    QCOMPARE(testObject.split(), propertyTestValue);
    QCOMPARE(testObject.property("split").toInt(), propertyTestValue);
}

void TstSpdrSynchronize::testSignals()
{
    SpdrSynchronize::registerMetatypes();
    SpdrSynchronize testObject;
    QSignalSpy spyOptions(&testObject, SIGNAL(optionsChanged(SpdrSynchronize::SynchronizationOptions)));
    QSignalSpy spySplit(&testObject, SIGNAL(splitChanged(int)));

    testObject.setOptions(SpdrSynchronize::Bidirectional);
    QCOMPARE(spyOptions.count(), 1);

    testObject.setSplit(5);
    testObject.setProperty("split", 7);
    QCOMPARE(spySplit.count(), 2);
    QList<QVariant> arguments = spySplit.takeLast();
    QCOMPARE(arguments.at(0).toInt(), 7);
}

void TstSpdrSynchronize::testSimpleSynchronization()
{
    QString testDataPath("testData");
    QDir(testDataPath).removeRecursively();

    QString testInputPath(testDataPath + QLatin1String("/input"));
    QString testOutputPath(testDataPath + QLatin1String("/output"));

    /*int numberOfFiles =*/ createTestFiles(testDataPath, true);

    SpdrSynchronize testObject;
    testObject.setLogLevel(Spdr::Error);
    testObject.setSimulate(true);
    testObject.setInputPath(testInputPath);
    testObject.setOutputPath(testOutputPath);
    QCOMPARE(testObject.synchronize(), true);

    QDir(testDataPath).removeRecursively();
}

void TstSpdrSynchronize::testAdvancedSynchronization()
{
    QString testDataPath("testData");
    QDir(testDataPath).removeRecursively();

    QString testInputPath(testDataPath + QLatin1String("/input"));
    QString testOutputPath(testDataPath + QLatin1String("/output"));

    /*int numberOfFiles =*/ createTestFiles(testDataPath, false);

    SpdrSynchronize testObject;
    testObject.setLogLevel(Spdr::Error);
    testObject.setOptions(SpdrSynchronize::RemoveMissingFiles);
    testObject.setSimulate(false);
    testObject.setInputPath(testInputPath);
    testObject.setOutputPath(testOutputPath);
    QCOMPARE(testObject.synchronize(), true);

    QDir(testDataPath).removeRecursively();
}

int TstSpdrSynchronize::createTestFiles(const QString &basePath, bool simplified)
{
    Q_UNUSED(simplified);

    QString inputPath(basePath + "/input");
    QString outputPath(basePath + "/output");
    QDir().mkpath(inputPath);
    QDir().mkpath(outputPath);

    int numberOfFiles = 10;

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
            if ((!simplified) && (i == 1)) {
                if (i == 1) {
                    QDir().mkpath(inputPath + "/moved");
                    QFile::copy(inputFilePath, outputPath + "/" + filename);
                    QFile::rename(inputFilePath, inputPath + "/moved/renamedFile1.txt");
                }
            } else {
                QFile::copy(inputFilePath, outputPath + "/" + filename);
            }
        }
    }

    return numberOfFiles;
}

QTEST_MAIN(TstSpdrSynchronize)
#include "tst_spdrsynchronize.moc"

