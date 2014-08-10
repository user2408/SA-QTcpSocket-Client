#ifndef CHANGEACCOUNTDIALOG_H
#define CHANGEACCOUNTDIALOG_H

#include <QDialog>

namespace Ui {
class changeAccountDialog;
}

class changeAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit changeAccountDialog(QWidget *parent = 0);
    ~changeAccountDialog();
    void setInfo();
private slots:
    void setUsr();
    void setPass();
    void saveInfo();
private:
    Ui::changeAccountDialog *ui;
};

#endif // CHANGEACCOUNTDIALOG_H
