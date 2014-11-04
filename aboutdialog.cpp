#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap("D:/Embedded/projects/KYYANG/System/rt5350/app/qt4/wifiVehicleClient/wifiVehicleClient/image/wifiVehicle.jpg"));
    //ui->label->resize(100,100);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_closeButton_clicked()
{
    close();
}
