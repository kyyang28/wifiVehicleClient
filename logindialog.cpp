#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QPalette>

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);
    ui->logoLabel->setPixmap(QPixmap("D:/Embedded/projects/KYYANG/System/rt5350/app/qt4/wifiVehicleClient/wifiVehicleClient/image/wifiVehicle.jpg"));
    setObjectName("Login");
    setStyleSheet("#Login{border-image:url(:/wifiVehicleImages/image/loginBackground.png);}");
    ui->loginButton->setObjectName("loginButton");
    ui->loginButton->setStyleSheet("#loginButton{border-image:url(:/wifiVehicleImages/image/login.png);}");
    ui->exitButton->setObjectName("exitButton");
    ui->exitButton->setStyleSheet("#exitButton{border-image:url(:/wifiVehicleImages/image/exit.png);}");
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_exitButton_clicked()
{
    close();
}

void loginDialog::on_loginButton_clicked()
{
    if (ui->usrLineEdit->text().trimmed() == tr("wifivehicleclient") && ui->pwdLineEdit->text() == tr("1234")) {
        accept();
    }else {
        QMessageBox::warning(this, tr("Login warning"),
                             tr("The username or password is not matched, please re-enter the correct info or you forgot the info?"),
                             QMessageBox::Yes);
        //if (ui->usrLineEdit->text().trimmed() != tr("wifivehicleclient")) {
            ui->usrLineEdit->clear();
            ui->pwdLineEdit->clear();
            ui->usrLineEdit->setFocus();
        //}else if (ui->pwdLineEdit->text() != tr("1234")) {
        //    ui->pwdLineEdit->clear();
        //    ui->pwdLineEdit->setFocus();
        //}
    }
}
