#include "setupdialog.h"
#include "ui_setupdialog.h"

SetupDialog::SetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Network Config"));
    ipAddr      = ui->ipAddr->text();
    controlPort = ui->controlPort->text();
    videoPort   = ui->videoPort->text();
}

SetupDialog::~SetupDialog()
{
    delete ui;
}

void SetupDialog::on_saveButton_clicked()
{
    ipAddr      = ui->ipAddr->text();
    controlPort = ui->controlPort->text();
    videoPort   = ui->videoPort->text();
    close();
}

void SetupDialog::on_closeButton_clicked()
{
    close();
}
