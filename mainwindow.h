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
#include <QKeyEvent>
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
    bool eventFilter(QObject *, QEvent *);
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
    void setPM();
    void setUsername();

private:
    Ui::MainWindow *ui;
    QTcpSocket *s1;
    QTimer *keepalive;
    QTimer *timecalc;
signals:
    void tabPressed();
};

#endif // MAINWINDOW_H
