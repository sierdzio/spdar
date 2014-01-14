#ifdef TEMP_REMOVE

#ifndef PDMAINWINDOW_H
#define PDMAINWINDOW_H

#include <QString>
#include <QStringList>
#include <QVariant>
#include <QMap>

#include <QWidget>
#include <QMainWindow>

namespace Ui
{
    class PDMainWindow;
}

class pdSettingsDialog;

/*
 GUI backing class.
 Currently also responsible for redistributing (to be changed).
 TODO:
 - move redistributor to a separate class,
 - add QSettings functionality,
 - add translation support,
 - (maybe) write QML GUI.
 */
class PDMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    PDMainWindow(QWidget *parent = 0);
    ~PDMainWindow();

signals:
//    preferencesChanged(QStringList dPrefs, QStringList rPrefs);

private slots:
    void on_actionPreferences_triggered();
    void on_pushButtonTransferBack_clicked();
    void on_pushButtonTo_clicked();
    void on_pushButtonFrom_clicked();
    void on_pushButtonTransfer_clicked();
    void on_pushButtonExport_clicked();
    void on_pushButtonImport_clicked();
    void on_actionAbout_triggered();
    void on_actionExit_triggered();
    void updateDownloaderProgressBar(int val);
    void updateRedistributorProgressBar(int val);
    void on_settingsDialog_accepted();

private:
    Ui::PDMainWindow *ui;
    pdSettingsDialog *settingsDialog;
    void loadSettings();
    void saveSettings();
    void initFormatsListsFromSettings();

    QString appVersion;
    QStringList dFormatFilst, rFormatList;
    QMap<QString, QVariant> preferences;
};

#endif // PDMAINWINDOW_H

#endif
