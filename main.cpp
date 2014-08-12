#include "mainwindow.h"
#include <QApplication>
#include "ui_mainwindow.h"

int main(int argc, char *argv[])
{
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::Socks5Proxy);
    proxy.setHostName("127.0.0.1");
    proxy.setPort(9050);
//    proxy.setApplicationProxy(proxy);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
