#include "changeaccountdialog.h"
#include "ui_changeaccountdialog.h"
#include "mainwindow.h"

changeAccountDialog::changeAccountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeAccountDialog)
{
    ui->setupUi(this);
    connect(ui->userName, SIGNAL(textChanged(QString)), this, SLOT(setUsr()));
    connect(ui->passwd, SIGNAL(textChanged(QString)), this, SLOT(setPass()));
    connect(ui->saveLoginInformation, SIGNAL(clicked()), this, SLOT(saveInfo()));
}

changeAccountDialog::~changeAccountDialog()
{
    delete ui;
}

void changeAccountDialog::setUsr()
{
    MainWindow::userName = ui->userName->text();
}

void changeAccountDialog::setPass()
{
    MainWindow::passwd = ui->passwd->text();
}

void changeAccountDialog::saveInfo()
{
    QFile userFile("username.txt");
    userFile.open(QFile::WriteOnly);
    QTextStream out(&userFile);
    out << MainWindow::userName << '\n';
    out << MainWindow::passwd;
    userFile.close();
}

void changeAccountDialog::setInfo()
{
    ui->userName->setText(MainWindow::userName);
    ui->passwd->setText(MainWindow::passwd);
}
