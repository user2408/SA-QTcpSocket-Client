#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QNetworkProxy>
#include <QHash>
#include <QDate>
#include <QColor>
#include <cstdlib>

#include "changeaccountdialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    changeAccountDialog *cad;
    static QString userName, passwd;
public slots:
    void twodc();
    void ptc();
    void fineline();
    void UofSA();
    void flatWorld();
    void planarOutpost();
    void mobiusMetropolis();
    void euAmsterdam();
    void sticktopia();
    void cartesian();

    void connectFunction();
    void showCADDialog();
    void timeOutEnded();
    void recvFunction();
    void sendMsg();
    void reconnect();
    void clearRows();
    void setTabTextToDefault();
    void sendPM();
    void setUptime();

private:
    Ui::MainWindow *ui;
    QTcpSocket *s1, *s2;
    QTimer *keepalive;
    QTimer *timecalc;
};

#endif // MAINWINDOW_H
