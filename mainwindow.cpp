#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QFile logininfo("username.txt");
    logininfo.open(QFile::ReadOnly);
    QTextStream in(&logininfo);
    userName = in.readLine();
    passwd = in.readLine();
    logininfo.close();

    s1 = new QTcpSocket(this);
    s2 = new QTcpSocket(this);
    s2->setProxy(QNetworkProxy::NoProxy);
    keepalive = new QTimer(this);
    cad = new changeAccountDialog(this);
    timecalc = new QTimer(this);

    ui->setupUi(this);
    ui->userTable->setColumnWidth(0, 40);
    ui->userTable->setColumnWidth(1, 159);

    connect(ui->action2_Dimensional_Center, SIGNAL(triggered()), this, SLOT(twodc()));
    connect(ui->actionPaper_Thin_City, SIGNAL(triggered()), this, SLOT(ptc()));
    connect(ui->actionFine_Line_Island, SIGNAL(triggered()), this, SLOT(fineline()));
    connect(ui->actionU_of_SA, SIGNAL(triggered()), this, SLOT(UofSA()));
    connect(ui->actionFlat_World, SIGNAL(triggered()), this, SLOT(flatWorld()));
    connect(ui->actionPlanar_Outpost, SIGNAL(triggered()), this, SLOT(planarOutpost()));
    connect(ui->actionMobius_Metropolis, SIGNAL(triggered()), this, SLOT(mobiusMetropolis()));
    connect(ui->actionAmsterdam, SIGNAL(triggered()), this, SLOT(euAmsterdam()));
    connect(ui->actionSticktopia, SIGNAL(triggered()), this, SLOT(sticktopia()));
    connect(ui->actionCartesian_Republic, SIGNAL(triggered()), this, SLOT(cartesian()));

    connect(ui->changeAccount, SIGNAL(clicked()), this, SLOT(showCADDialog()));
    connect(keepalive, SIGNAL(timeout()), this, SLOT(timeOutEnded()));
    connect(s1, SIGNAL(readyRead()), this, SLOT(recvFunction()));
    connect(ui->lineEdit_mainChat, SIGNAL(returnPressed()), this, SLOT(sendMsg()));
    connect(s1, SIGNAL(disconnected()), this, SLOT(reconnect()));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(setTabTextToDefault()));
    connect(ui->lineEdit_PM, SIGNAL(returnPressed()), this, SLOT(sendPM()));
    connect(timecalc, SIGNAL(timeout()), this, SLOT(setUptime()));
}

const char *IP; int port;
int pmcount, playercount = 0;
QString qlogin;
QString MainWindow::userName;
QString MainWindow::passwd;
QString pmMsg, qpmcount, qplayercount, currenttime;
char randhex[] = "08HxO9TdCC62Nwln1P";
char b03[] = "03_";

int row = 0;

int uptimeseconds = 0, uptimeminutes = 0, uptimehours = 0;
QString quptimeseconds, quptimeminutes, quptimehours;

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectFunction()
{
    if(s1->state() == QAbstractSocket::ConnectedState)
    {
        s1->close();
    }


    qlogin = "09" + userName + ';' + passwd;
    std::string strlogin = qlogin.toStdString().c_str();
    const char *login = strlogin.c_str();

    s1->connectToHost(IP, port);
    timecalc->start(1000);
    s1->write(randhex, strlen(randhex)+1);
    s1->write(login, strlen(login)+1);
    currenttime = QTime().currentTime().toString("h:mm:ss AP");
    ui->textBrowser_2->append("Connected at " + currenttime + " " + QDate().currentDate().toString("d/MM/yy"));
    keepalive->start(10000);
}

void MainWindow::recvFunction()
{
    QHash <QString, QString> users;
    QHashIterator <QString, QString> userIterator(users);
    QFile logs("logs.txt");
    QTextStream savelog(&logs);
    char buffer[1], nb[] = "\x00", zchar[] = "02Z900_";
    const char *hashtaglen;
    size_t start, end;
    std::string rdata, uid, tableuser, hashtag, msg, rgbcolor;
    QString quid, qtableuser, qmsg;
    QTableWidgetItem *ID, *NAME;
    QColor rgbvalue;
    int rlen;
    do
    {
        rlen = s1->read(buffer, 1);
        rdata += buffer[0];
        if(buffer[0] == '#')
        {
            hashtag += buffer[0];
            hashtaglen = hashtag.c_str();
        }
        if(buffer[0] == nb[0])
        {
            switch(rdata[0])
            {
            case 'C':
                playercount++;
                qplayercount = QString::number(playercount);
                ui->label->setText("Player count: " + qplayercount);
                break;
            case 'A':
                s1->write("0c", strlen("0c")+1);
                s1->write("01", strlen("01")+1);
                uid = rdata.substr(1, 3); quid = QString::fromStdString(uid);
                ID = new QTableWidgetItem(quid);
                ui->userTable->insertRow(row);
                ui->userTable->setItem(row, 0, ID);

                if(strlen(hashtaglen) == 0)
                {
                    start = 4;
                    end = strlen("")+24;
                    tableuser = rdata.substr(start, end - start); qtableuser = QString::fromStdString(tableuser);
                    users.insert(quid, qtableuser);
                    NAME = new QTableWidgetItem(qtableuser);
                    ui->userTable->setItem(row, 1, NAME);
                    row++;
                }
                else
                {
                    start = rdata.find(hashtaglen) + strlen(hashtaglen);
                    end = strlen("12345678901234567890") - strlen(hashtaglen);
                    tableuser = rdata.substr(start, end); qtableuser = QString::fromStdString(tableuser);
                    users.insert(quid, qtableuser);
                    NAME = new QTableWidgetItem(qtableuser);
                    ui->userTable->setItem(row, 1, NAME);
                    row++;
                }
                break;
            case 'U':
                uid = rdata.substr(1, 3); quid = QString::fromStdString(uid);
                ID = new QTableWidgetItem(quid);
                ui->userTable->insertRow(row);
                ui->userTable->setItem(row, 0, ID);

                if(strlen(hashtaglen) == 0)
                {
                    start = 4;
                    end = strlen("")+24;
                    tableuser = rdata.substr(start, end - start); qtableuser = QString::fromStdString(tableuser);
                    users.insert(quid, qtableuser);
                    NAME = new QTableWidgetItem(qtableuser);
                    ui->userTable->setItem(row, 1, NAME);
                    row++;
                }
                else
                {
                    start = rdata.find(hashtaglen) + strlen(hashtaglen);
                    end = strlen("12345678901234567890") - strlen(hashtaglen);
                    tableuser = rdata.substr(start, end); qtableuser = QString::fromStdString(tableuser);
                    NAME = new QTableWidgetItem(qtableuser);
                    ui->userTable->setItem(row, 1, NAME);
                    row++;
                }
                break;
            case 'D':
                uid = rdata.substr(1, 3); quid = QString::fromStdString(uid);

                for(int i = 0; i < ui->userTable->rowCount(); i++)
                {
                    if(ui->userTable->item(i, 0)->text() == quid)
                    {
                        ui->userTable->removeRow(i);
                        row--;
                        break;
                    }
                }
                playercount--;
                qplayercount = QString::number(playercount);
                ui->label->setText("Player count: " + qplayercount);
                break;
            case 'M':
                uid = rdata.substr(1, 3); quid = QString::fromStdString(uid);
                if(rdata[4] == '9')
                {
                    start = 5;
                    end = rdata.find(nb[0]);
                    msg = rdata.substr(start, end - start);
                    qmsg = QString::fromStdString(msg);


                    for(int i = 0; i < ui->userTable->rowCount(); i++)
                    {
                        if(ui->userTable->item(i, 0)->text() == quid)
                        {
                            currenttime = QTime().currentTime().toString("h:mm:ss AP");
                            qtableuser = ui->userTable->item(i, 1)->text();
                            if(qtableuser == MainWindow::userName)
                            {
                                ui->textBrowser->append('[' + currenttime + " " + QDate().currentDate().toString("d/MM/yy") + ']' + "<span style = \"color: #FA7070\">&lt;" + qtableuser + "&gt;</span>" + qmsg);
                            }
                            else
                            {
                                ui->textBrowser->append('[' + currenttime + " " + QDate().currentDate().toString("d/MM/yy") + ']' + "<span style = \"color: #6AB9C7\">&lt;" + qtableuser + "&gt;</span>" + qmsg);

                            }

                            if(ui->textBrowser->textCursor().position() != QTextCursor::End)
                            {
                                break;
                            }
                            else
                            {
                                QTextCursor c =  ui->textBrowser->textCursor();
                                c.movePosition(QTextCursor::End);
                                ui->textBrowser->setTextCursor(c);
                                break;
                            }
                        }
                    }
                }
                if(rdata[4] == 'P')
                {
                    start = 5;
                    end = rdata.find(nb[0]);
                    msg = rdata.substr(start, end - start);
                    qmsg = QString::fromStdString(msg);

                    for(int i = 0; i < ui->userTable->rowCount(); i++)
                    {
                        if(ui->userTable->item(i, 0)->text() == quid)
                        {
                            currenttime = QTime().currentTime().toString("h:mm:ss AP");
                            qtableuser = ui->userTable->item(i, 1)->text();
                            ui->textBrowser_PM->append('[' + currenttime + " " + QDate().currentDate().toString("d/MM/yy") + ']' + "<" + qtableuser + "> " + qmsg);
                            QTextCursor c =  ui->textBrowser_PM->textCursor();
                            c.movePosition(QTextCursor::End);
                            ui->textBrowser_PM->setTextCursor(c);

                            pmcount++;
                            qpmcount = QString::number(pmcount);
                            if(ui->tabWidget->currentIndex() != 1)
                            {
                                ui->tabWidget->setTabText(1, "*" + qpmcount + " Private");
                            }
                            break;
                        }
                    }
                }
                break;
            case '0':
                if(rdata[1] == '8')
                {
                    s1->write(b03, strlen(b03)+1);
                }
                //                if(rdata[1] == '1')
                //                {
                //                    s1->write(zchar, strlen(zchar)+1);
                //                }
                if(rdata[1] == 'c')
                {
                    s1->write(b03, strlen(b03)+1);
                }
            }
            rdata = "";
            hashtag = "";
        }
    }while(rlen > 0);
}

void MainWindow::showCADDialog()
{
    cad->show();
    cad->setInfo();
}

void MainWindow::timeOutEnded()
{
    s1->write("0010xHB", strlen("0010xHB")+1);
}

void MainWindow::sendMsg()
{
    QString QYourmsg = '9' + ui->lineEdit_mainChat->text();
    std::string yourmsgstr = QYourmsg.toStdString().c_str();
    const char *yourmsg = yourmsgstr.c_str();
    s1->write(yourmsg, strlen(yourmsg)+1);
    ui->lineEdit_mainChat->clear();
}

void MainWindow::clearRows()
{
    int rowcount = ui->userTable->rowCount();
    while(rowcount > 0)
    {
        ui->userTable->removeRow(0);
        rowcount--;
    }
    row = 0;
    playercount = 0;
}

void MainWindow::reconnect()
{
    keepalive->stop();
    timecalc->stop();
    clearRows();
    currenttime = QTime().currentTime().toString("h:m:s AP");
    ui->textBrowser_2->append("Disconnection detected at " + currenttime + '\n');
    connectFunction();
}

void MainWindow::setTabTextToDefault()
{
    if(ui->tabWidget->tabText(1) != "Private")
    {
        ui->tabWidget->setTabText(1, "Private");
        pmcount = 0;
    }
}

void MainWindow::sendPM()
{
    bool found = false;
    QString yourpm;
    std::string strpm;
    const char *cpm;

    int rowcount2 = ui->userTable->rowCount();
    for(int i = 0; i < rowcount2; i++)
    {
        if(ui->userTable->item(i, 1)->text() == ui->lineEdit_PMName->text())
        {
            found = true;
            ui->textBrowser_PM->append("(PM sent to " + ui->lineEdit_PMName->text() + "): " + ui->lineEdit_PM->text());
            yourpm = "00" + ui->userTable->item(i, 0)->text() + 'P' + ui->lineEdit_PM->text();
            strpm = yourpm.toStdString().c_str();
            cpm = strpm.c_str();
            s1->write(cpm, strlen(cpm)+1);
            ui->lineEdit_PM->clear();
            break;
        }
    }
    if(found == false)
    {
        ui->textBrowser_PM->append(ui->lineEdit_PMName->text() + " not found.");
    }
}

void MainWindow::setUptime()
{
    uptimeseconds++;
    if(uptimeseconds == 60)
    {
        uptimeseconds = 0;
        uptimeminutes++;
    }
    if(uptimeminutes == 60)
    {
        uptimeminutes = 0;
        uptimehours++;
    }
    quptimeseconds = QString::number(uptimeseconds);
    quptimeminutes = QString::number(uptimeminutes);
    quptimehours = QString::number(uptimehours);
    if(uptimeseconds < 10 && uptimeminutes < 10)
    {
        ui->label_upTime->setText("Uptime: " + quptimehours + ":0" + quptimeminutes + ":0" + quptimeseconds);
    }
    if(uptimeseconds >= 10 && uptimeminutes < 10)
    {
        ui->label_upTime->setText("Uptime: " + quptimehours + ":0" + quptimeminutes + ':' + quptimeseconds);
    }
    if(uptimeminutes >= 10 && uptimeseconds < 10)
    {
        ui->label_upTime->setText("Uptime: " + quptimehours + ':' + quptimeminutes + ":0" + quptimeseconds);
    }
    if(uptimeminutes >= 10 && uptimeseconds >= 10)
    {
        ui->label_upTime->setText("Uptime: " + quptimehours + ':' + quptimeminutes + ':' + quptimeseconds);
    }

}

void MainWindow::twodc()
{
    IP = "74.86.43.9"; port = 1138;
    ui->tabWidget->setTabText(0, "2-Dimensional Central");
    connectFunction();
}

void MainWindow::ptc()
{
    IP = "74.86.43.8"; port = 1138;
    ui->tabWidget->setTabText(0, "Paper Thin City");
    connectFunction();
}

void MainWindow::fineline()
{
    IP = "67.19.138.234"; port = 1138;
    ui->tabWidget->setTabText(0, "Fine Line Island");
    connectFunction();
}

void MainWindow::UofSA()
{
    IP = "67.19.138.236"; port = 1138;
    ui->tabWidget->setTabText(0, "U of SA");
    connectFunction();
}

void MainWindow::flatWorld()
{
    IP = "74.86.3.220"; port = 1138;
    ui->tabWidget->setTabText(0, "Flat World");
    connectFunction();
}

void MainWindow::planarOutpost()
{
    IP = "67.19.138.235"; port = 1138;
    ui->tabWidget->setTabText(0, "Planar Outpost");
    connectFunction();
}

void MainWindow::mobiusMetropolis()
{
    IP = "74.86.3.221"; port = 1138;
    ui->tabWidget->setTabText(0, "Mobius Metropolis");
    connectFunction();
}

void MainWindow::euAmsterdam()
{
    IP = "94.75.214.10"; port = 1138;
    ui->tabWidget->setTabText(0, "Amsterdam");
    connectFunction();
}

void MainWindow::sticktopia()
{
    IP = "74.86.3.222"; port = 1138;
    ui->tabWidget->setTabText(0, "Sticktopia");
    connectFunction();
}

void MainWindow::cartesian()
{
    IP = "67.19.138.234"; port = 1138;
    ui->tabWidget->setTabText(0, "Cartesian Republic");
    connectFunction();
}
