#include "spdrglobal.h"
#include "SpdrBase"

#include <QString>
#include <QObject>
#include <QDebug>
#include <QTest>
#include <QSignalSpy>

/*!
  \addtogroup tests Spdr library tests

  \brief Spdr comes bundled with a set of tests for all of it's library public
  classes and functionality.

  The test suite is being kept fairly up to date with the rest of the development
  efforts and when it runs successfuly it should mean that Spdr is fully
  operational.
  */

/*!
  \ingroup tests

  Test for SpdrBase. It verifies the operation of all SpdrBase properties
  and methods.
 */
class TstSpdrBase : public QObject
{
    Q_OBJECT

private slots:
    void testDefaults();
    void testSetters();
    void testSignals();
};

void TstSpdrBase::testDefaults()
{
    //qDebug() << "Testing defaults for SpdrBase";
    SpdrBase testObject;
    QCOMPARE(testObject.inputPath(), QString());
    QCOMPARE(testObject.outputPath(), QString());
    QCOMPARE(testObject.updateMode(), Spdr::Ask);
    QCOMPARE(testObject.logLevel(), Spdr::Error);
    QCOMPARE(testObject.isUsingLogFile(), false);
}

void TstSpdrBase::testSetters()
{
    SpdrBase testObject;

    QString pathTester("/some/path");
    testObject.setInputPath(pathTester);
    QCOMPARE(testObject.inputPath(), pathTester);

    testObject.setOutputPath(pathTester);
    QCOMPARE(testObject.outputPath(), pathTester);

    testObject.setUpdateMode(Spdr::Overwrite);
    QCOMPARE(testObject.updateMode(), Spdr::Overwrite);

    testObject.setLogLevel(Spdr::LogEverything);
    QCOMPARE(testObject.logLevel(), Spdr::LogEverything);

    QString randomPath("some/random/path");
    testObject.setLogFile(randomPath);
    QCOMPARE(testObject.isUsingLogFile(), false);
    QCOMPARE(testObject.logFile(), QString(""));
}

void TstSpdrBase::testSignals()
{
    Spdr::registerMetatypes();
    SpdrBase testObject;
    QSignalSpy spyInputPath(&testObject, SIGNAL(inputPathChanged(QString)));
    QSignalSpy spyOutputPath(&testObject, SIGNAL(outputPathChanged(QString)));
    QSignalSpy spyUpdateMode(&testObject, SIGNAL(updateModeChanged(Spdr::UpdateMode)));

    QString pathTester("/some/path");
    testObject.setInputPath(pathTester);
    testObject.setOutputPath(pathTester);
    testObject.setUpdateMode(Spdr::Ignore);

    QCOMPARE(spyInputPath.count(), 1);
    QCOMPARE(spyOutputPath.count(), 1);
    QCOMPARE(spyUpdateMode.count(), 1);
}

QTEST_MAIN(TstSpdrBase)
#include "tst_spdrbase.moc"
